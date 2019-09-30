# EnumVisitor

The header-only library with visitor for enum values that replaces redundant switch over enum. Requires C++17 support.

## Motivation

Writing switch for enum values with just function calls may be redundant in some cases:

```c++
enum class ReadMethod {
    none = 0x00,
    unknown = 0x01,
    buffered = 0x02,
    unbuffered = 0x04
};

class Processor
{
public:
    void processBuffered();
    void processUnbuffered();
    void handleError();
};

int main()
{
    auto method = ReadMethod::none;
    // modify values

    auto p = Processor{};
    switch(method)
    {
    case ReadMethod::buffered:
        p.processBuffered();
        break;
    case ReadMethod::unbuffered:
        p.processUnbuffered();
        break;
    default:
        p.handleError();
    }
}
```

This library helps to remove that boilerplate.

## Example
Here's how to use it with example:

```c++
#include <enum_visitor/enum_visitor.hpp>

enum class ReadMethod {
    none = 0x00,
    unknown = 0x01,
    buffered = 0x02,
    unbuffered = 0x04
};

//derive from enum_visitor<...>
class Processor : public mj::enum_visitor<ReadMethod, ReadMethod::none, ReadMethod::unknown, ReadMethod::buffered, ReadMethod::unbuffered>
{
public:
    void operator()(enum_v<ReadMethod::buffered>);
    void operator()(enum_v<ReadMethod::unbuffered>);
    template <ReadMethod RM>
    void operator()(enum_v<RM>); //instead of "default" case, not required
};

int main()
{
    auto method = ReadMethod::none;
	// modify values

	auto p = Processor{};
	mj::visit(p, method); //just call visit instead of writing switch
}
```
