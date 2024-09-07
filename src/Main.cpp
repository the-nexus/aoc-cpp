
#include <runtime/Program.hpp>

int main(int argc, char* argv[])
{
    std::vector<std::string_view> args;
    args.reserve(argc);

    for (int index = 0; index < argc; ++index)
    {
        args.emplace_back(argv[index]);
    }

    return aoc::runtime::Program::Launch(args);
}