
#pragma once

#include <algorithm>
#include <functional>
#include <map>
#include <memory>

namespace AOC::Tools
{
    template <typename IdentifierT, typename ProductT>
    class Factory
    {
        using WorkerT = std::function<std::unique_ptr<ProductT>()>;

    public:
        static bool Register(IdentifierT const& identifier, WorkerT&& worker)
        {
            sm_workers.emplace(identifier, worker);
            return true;
        }

        static std::unique_ptr<ProductT> Produce(IdentifierT const& identifier) 
        {
            auto it = std::find(std::begin(sm_workers), std::end(sm_workers), [&identifier](IdentifierT const& key)
            {
                return key == identifier;
            });

            if (it == std::end(sm_workers))
            {
                return nullptr;
            }

            return it->second();
        }

    private:
        static std::map<IdentifierT, WorkerT> sm_workers;
    };
}
