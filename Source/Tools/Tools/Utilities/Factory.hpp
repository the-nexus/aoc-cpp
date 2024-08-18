
#pragma once

#include <algorithm>
#include <functional>
#include <map>
#include <memory>

namespace AOC::Tools
{
    template <typename IdentifierT, typename ProductT, typename... Args>
    class Factory
    {
    private:
        static std::map<IdentifierT, std::function<std::unique_ptr<ProductT>(Args&&...)>> sm_blueprints;

    public:
        static bool Register(IdentifierT const& identifier, std::function<std::unique_ptr<ProductT>(Args&&...)>&& blueprint)
        {
            sm_blueprints.emplace(identifier, std::move(blueprint));
            return true;
        }

        static std::unique_ptr<ProductT> Produce(IdentifierT const& identifier, Args&&... args) 
        {
            auto blueprintIt = std::find_if(std::cbegin(sm_blueprints), std::cend(sm_blueprints), [&identifier](std::pair<IdentifierT, std::function<std::unique_ptr<ProductT>(Args&&...)>> const& blueprint)
            {
                return blueprint.first == identifier;
            });

            if (blueprintIt == std::cend(sm_blueprints))
            {
                return nullptr;
            }

            return blueprintIt->second(std::forward<Args>(args)...);
        }
    };

    template <typename IdentifierT, typename ProductT, typename... Args>
    std::map<IdentifierT, std::function<std::unique_ptr<ProductT>(Args&&...)>> Factory<IdentifierT, ProductT, Args...>::sm_blueprints = {};
}
