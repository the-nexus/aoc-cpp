#pragma once

#include "../ChallengeAbstract.h"
#include <map>
#include <set>

namespace Year2022
{
    class Challenge03 final : public ChallengeAbstract
    {
    private:
        std::vector<std::string> m_bags;

    public:
        Challenge03(std::vector<std::string> const& inputLines)
        {
            m_bags = inputLines;
        }

        virtual void Run_PartOne() override
        {
            int priorities = 0;
            std::vector<std::string const*> compartments;
            compartments.resize(2);

            for (std::string const& bag : m_bags)
            {
                size_t const compartmentSize = bag.size() / 2;
                std::string const firstCompartment = bag.substr(0, compartmentSize);
                std::string const secondCompartment = bag.substr(compartmentSize, compartmentSize + compartmentSize);

                compartments[0] = &firstCompartment;
                compartments[1] = &secondCompartment;

                priorities += GetItemPriority(GetFirstCommonItem(compartments));
            }

            std::cout << priorities << std::endl;
        }

        virtual void Run_PartTwo() override
        {
            int priorities = 0;
            std::vector<std::string const*> compartments;
            compartments.resize(3);

            for (size_t bagIndex = 0; bagIndex < m_bags.size(); bagIndex += 3)
            {
                compartments[0] = &m_bags[bagIndex];
                compartments[1] = &m_bags[bagIndex + 1];
                compartments[2] = &m_bags[bagIndex + 2];

                priorities += GetItemPriority(GetFirstCommonItem(compartments));
            }

            std::cout << priorities << std::endl;
        }

    private:
        char GetFirstCommonItem(std::vector<std::string const*> const& containers) const
        {
            std::set<char> uniqueItems;
            std::map<char, size_t> itemCounts;
            for (std::string const* container : containers)
            {
                uniqueItems.clear();
                for (char const item : *container)
                {
                    if (uniqueItems.find(item) == uniqueItems.end())
                    {
                        uniqueItems.insert(item);
                        if (itemCounts.find(item) != itemCounts.end())
                        {
                            itemCounts[item] += 1;
                        }
                        else
                        {
                            itemCounts[item] = 1;
                        }
                    }
                }
            }

            for (std::pair<char, size_t> const& itemCount : itemCounts)
            {
                if (itemCount.second == containers.size())
                {
                    return itemCount.first;
                }
            }

            return '\0';
        }

        int GetItemPriority(char const item) const
        {
            if (item >= 'a' && item <= 'z')
            {
                return static_cast<int>(item - 'a') + 1;
            }
            else if (item >= 'A' && item <= 'Z')
            {
                return static_cast<int>(item - 'A') + 27;
            }
            else
            {
                return 0;
            }
        }
    };
}
