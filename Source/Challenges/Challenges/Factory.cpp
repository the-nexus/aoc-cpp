
#include "Factory.hpp"

using namespace AOC::Challenges;

#if __has_include("Challenges/Autogen/Factory.autogen.inl") && __has_include("Challenges/Autogen/Factory.autogen.inl")
#include "Challenges/Autogen/Factory.autogen.inl"
#endif

void Factory::RegisterAll()
{
#ifdef AUTOGEN_CHALLENGE_REGISTRY
    AUTOGEN_CHALLENGE_REGISTRY
#undef AUTOGEN_CHALLENGE_REGISTRY
#endif
}
