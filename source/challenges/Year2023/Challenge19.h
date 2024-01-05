#pragma once

#include "../ChallengeAbstract.h"
#include <map>
#include <StringTool.h>

namespace Year2023
{
    class Challenge19 final : public ChallengeAbstract
    {
        typedef unsigned int WorkflowIdType;

        static constexpr WorkflowIdType REJECTED_ID = 0;
        static constexpr WorkflowIdType ACCEPTED_ID = 1;

        enum class EAttributeType
        {
            XtremelyCoolLooking = 0,
            Musical,
            Aerodynamic,
            Shiny,
            COUNT
        };

        struct Comparison
        {
            char m_operatorToken = '\0';
            int m_attributeIndex = static_cast<int>(EAttributeType::COUNT);
            int m_value = 0;
        };

        struct Rule
        {
            Comparison m_comparison;
            WorkflowIdType m_nextWorkflowId = REJECTED_ID;
        };

        struct Workflow
        {
            WorkflowIdType m_id = 0;
            std::vector<Rule> m_rules;
        };

        struct Part
        {
            int m_attributes[static_cast<int>(EAttributeType::COUNT)];
        };

        std::map<WorkflowIdType, Workflow> m_workflows;
        std::vector<Part> m_parts;

    public:
        Challenge19(std::vector<std::string> const& inputLines)
        {
            m_parts.reserve(inputLines.size());

            bool isBuildingWorkflows = true;
            for (std::string const& line : inputLines)
            {
                if (isBuildingWorkflows)
                {
                    if (line.empty())
                    {
                        isBuildingWorkflows = false;
                        continue;
                    }

                    size_t const bracketTokenPos = line.find('{');

                    std::vector<std::string> ruleSplit;
                    StringTool::SplitString(line.substr(bracketTokenPos + 1, line.size() - bracketTokenPos - 2), ',', ruleSplit);

                    Workflow workflow;
                    workflow.m_id = GetWorkflowId(line.substr(0, bracketTokenPos));

                    workflow.m_rules.reserve(ruleSplit.size());
                    for (std::string const& ruleStr : ruleSplit)
                    {
                        size_t const separatorToken = ruleStr.find(':');

                        Rule& rule = workflow.m_rules.emplace_back();
                        if (separatorToken < ruleStr.size())
                        {
                            rule.m_comparison.m_attributeIndex = static_cast<int>(GetAttributeType(ruleStr[0]));
                            rule.m_comparison.m_operatorToken = ruleStr[1];
                            rule.m_comparison.m_value = atoi(ruleStr.substr(2, separatorToken - 2).c_str());
                            rule.m_nextWorkflowId = GetWorkflowId(ruleStr.substr(separatorToken + 1));
                        }
                        else
                        {
                            rule.m_nextWorkflowId = GetWorkflowId(ruleStr);
                        }
                    }

                    m_workflows.emplace(workflow.m_id, std::move(workflow));
                }
                else
                {
                    std::vector<std::string> attributeSplit;
                    StringTool::SplitString(line.substr(1, line.size() - 2), ',', attributeSplit);

                    Part& part = m_parts.emplace_back();
                    for (std::string const& attributeStr : attributeSplit)
                    {
                        part.m_attributes[static_cast<int>(GetAttributeType(attributeStr[0]))] = atoi(attributeStr.substr(2).c_str());
                    }
                }
            }
        }

        virtual void Run_PartOne() override
        {
            int attributeSum = 0;
            for (Part const& part : m_parts)
            {
                if (IsAcceptedPart(part))
                {
                    int constexpr attributeCount = static_cast<int>(EAttributeType::COUNT);
                    for (int i = 0; i < attributeCount; ++i)
                    {
                        attributeSum += part.m_attributes[i];
                    }
                }
            }

            std::cout << attributeSum << std::endl;
        }

        virtual void Run_PartTwo() override
        {
            std::cout << "WARNING: Part Two Not Implemented" << std::endl;
        }

    private:
        static EAttributeType GetAttributeType(char const token)
        {
            switch (token)
            {
            case 'x': return EAttributeType::XtremelyCoolLooking;
            case 'm': return EAttributeType::Musical;
            case 'a': return EAttributeType::Aerodynamic;
            case 's': return EAttributeType::Shiny;
            default:  return EAttributeType::COUNT;
            }
        }

        static WorkflowIdType GetWorkflowId(std::string const& label)
        {
            if (label.size() == 1)
            {
                if (label[0] == 'R') return REJECTED_ID;
                if (label[0] == 'A') return ACCEPTED_ID;
            }

            WorkflowIdType id = 0;
            for (char const token : label)
            {
                id = id * 100 + static_cast<WorkflowIdType>(token - 'a') + 2;
            }

            return id;
        }

        bool IsAcceptedPart(Part const& part) const
        {
            static const WorkflowIdType startingWorkflowId = GetWorkflowId("in");

            WorkflowIdType currentWorkflowId = startingWorkflowId;
            while (currentWorkflowId != REJECTED_ID && currentWorkflowId != ACCEPTED_ID)
            {
                Workflow const& currentWorkflow = m_workflows.at(currentWorkflowId);
                for (Rule const& rule : currentWorkflow.m_rules)
                {
                    if (IsPartRespectingRule(part, rule.m_comparison))
                    {
                        currentWorkflowId = rule.m_nextWorkflowId;
                        break;
                    }
                }
            }

            return currentWorkflowId == ACCEPTED_ID;
        }

        static bool IsPartRespectingRule(Part const& part, Comparison const& comparison)
        {
            switch (comparison.m_operatorToken)
            {
            case '<': return part.m_attributes[static_cast<int>(comparison.m_attributeIndex)] < comparison.m_value;
            case '>': return part.m_attributes[static_cast<int>(comparison.m_attributeIndex)] > comparison.m_value;
            default: return true;
            }
        }
    };
}
