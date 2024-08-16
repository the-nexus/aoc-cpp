
#pragma once

#include <algorithm>
#include <functional>
#include <map>
#include <memory>

namespace AOC::Tools
{
    template <typename ProductT>
    class FactoryBlueprint : public std::function<std::unique_ptr<ProductT>()> {};

    template <typename IdentifierT, typename ProductT>
    class Factory
    {
    private:
        static std::map<IdentifierT, FactoryBlueprint<ProductT>> sm_blueprints;

    public:
        static bool Register(IdentifierT const& identifier, FactoryBlueprint<ProductT>&& blueprint)
        {
            sm_blueprints.emplace(identifier, blueprint);
            return true;
        }

        static std::unique_ptr<ProductT> Produce(IdentifierT const& identifier) 
        {
            auto blueprintIt = std::find_if(std::cbegin(sm_blueprints), std::cend(sm_blueprints), [&identifier](std::pair<IdentifierT, FactoryBlueprint<ProductT>> const& blueprint)
            {
                return blueprint.first == identifier;
            });

            if (blueprintIt == std::cend(sm_blueprints))
            {
                return nullptr;
            }

            return blueprintIt->second();
        }
    };

    template <typename IdentifierT, typename ProductT>
    std::map<IdentifierT, FactoryBlueprint<ProductT>> Factory<IdentifierT, ProductT>::sm_blueprints = {};
}
