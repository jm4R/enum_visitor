#include <enum_visitor/enum_visitor.hpp>

#include <cassert>
#include <iostream>
#include <string>

enum class ReadMethod {
    none = 0x00,
    unknown = 0x01,
    buffered = 0x02,
    unbuffered = 0x04
};

struct ReadMethodVisitor : public mj::enum_visitor<ReadMethod, ReadMethod::none, ReadMethod::unknown, ReadMethod::buffered, ReadMethod::unbuffered> {

    void operator()(enum_v<ReadMethod::buffered>)
    {
        currentName = "buffered";
    }

    void operator()(enum_v<ReadMethod::unbuffered>)
    {
        currentName = "unbuffered";
    }

    template <ReadMethod RM>
    void operator()(enum_v<RM>)
    {
        currentName = "unknown";
    }

    const char* currentName{ nullptr };
};

int main()
{
    ReadMethodVisitor rmv;

    mj::visit(rmv, ReadMethod::none);
    assert(rmv.currentName == std::string{ "unknown" });

    mj::visit(rmv, ReadMethod::unknown);
    assert(rmv.currentName == std::string{ "unknown" });

    mj::visit(rmv, ReadMethod::buffered);
    assert(rmv.currentName == std::string{ "buffered" });

    mj::visit(rmv, ReadMethod::unbuffered);
    assert(rmv.currentName == std::string{ "unbuffered" });
}
