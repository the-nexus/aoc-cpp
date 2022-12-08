#pragma once

#include "../ChallengeAbstract.h"
#include "../tools/StringTool.h"
#include <functional>
#include <algorithm>

namespace Year2022
{
    class Challenge07 : public ChallengeAbstract
    {
    private:
        struct FileItem
        {
            std::string m_name = "";
            unsigned int m_size = 0;
        };

        struct DirectoryItem
        {
            std::vector<FileItem> m_files;
            std::vector<DirectoryItem> m_subDirectories;
            std::string m_name = "";
            DirectoryItem* m_parentDirectory = nullptr;
            unsigned int m_contentSize = 0;
        };

        DirectoryItem m_rootDirectory;

    public:
        virtual void SetUp(std::vector<std::string> const& inputLines) override
        {
            m_rootDirectory.m_name = "/";
            DirectoryItem* currentDirectory = &m_rootDirectory;

            std::vector<std::string> inputArgs;
            for (std::string const& inputLine : inputLines)
            {
                inputArgs.clear();
                StringTool::SplitString(inputLine, ' ', inputArgs);

                if (inputArgs[0][0] == '$') // New command
                {
                    if (inputArgs[1][0] == 'c') // Move to different directory ("CD")
                    {
                        if (inputArgs[2][0] == '/') // Move to the root directory
                        {
                            currentDirectory = &m_rootDirectory;
                        }
                        else if (inputArgs[2][0] == '.') // Move to the parent directory ("..")
                        {
                            currentDirectory = currentDirectory->m_parentDirectory;
                        }
                        else // Move to named child directory
                        {
                            currentDirectory = FindSubdirectoryByName(*currentDirectory, inputArgs[2]);
                        }
                    }
                }
                else if (inputArgs[0][0] == 'd') // Directyory listing ("dir")
                {
                    DirectoryItem& subDirectory = currentDirectory->m_subDirectories.emplace_back(); ;
                    subDirectory.m_name = inputArgs[1];
                    subDirectory.m_parentDirectory = currentDirectory;
                }
                else // File listing (size)
                {
                    FileItem& file = currentDirectory->m_files.emplace_back();
                    file.m_name = inputArgs[1];
                    file.m_size = atoi(inputArgs[0].c_str());

                    OnFileAdded(file, *currentDirectory);
                }
            }
        }

        virtual void Run_PartOne() override
        {
            std::vector<DirectoryItem const*> foundDirectories;
            FindAllMatchingDirectories(m_rootDirectory, foundDirectories, [](DirectoryItem const& subdirectory) -> bool {
                return subdirectory.m_contentSize <= 100000;
            });

            unsigned int contentSizeSum = 0;
            for (DirectoryItem const* directory : foundDirectories)
            {
                contentSizeSum += directory->m_contentSize;
            }

            std::cout << contentSizeSum << std::endl;
        }

        virtual void Run_PartTwo() override
        {
            unsigned int const availableSpace = 70000000 - m_rootDirectory.m_contentSize;
            unsigned int const requiredSpace = 30000000 - availableSpace;

            std::vector<DirectoryItem const*> foundDirectories;
            FindAllMatchingDirectories(m_rootDirectory, foundDirectories, [&requiredSpace](DirectoryItem const& subdirectory) -> bool {
                return subdirectory.m_contentSize >= requiredSpace;
            });

            std::sort(foundDirectories.begin(), foundDirectories.end(), [](DirectoryItem const* lhs, DirectoryItem const* rhs) -> bool {
                return lhs->m_contentSize < rhs->m_contentSize;
            });

            std::cout << foundDirectories[0]->m_contentSize << std::endl;
        }

        virtual void CleanUp() override {}

    private:

        void OnFileAdded(FileItem const& file, DirectoryItem& directory)
        {
            directory.m_contentSize += file.m_size;
            if (directory.m_parentDirectory)
            {
                OnFileAdded(file, *directory.m_parentDirectory);
            }
        }

        void OnFileRemoved(FileItem const& file, DirectoryItem& directory)
        {
            directory.m_contentSize -= file.m_size;
            if (directory.m_parentDirectory)
            {
                OnFileRemoved(file, *directory.m_parentDirectory);
            }
        }

        DirectoryItem* FindSubdirectoryByName(DirectoryItem& directory, std::string const& subdirectoryName) const
        {
            auto const it = std::find_if(directory.m_subDirectories.begin(), directory.m_subDirectories.end(), [&subdirectoryName](DirectoryItem const& subdirectory) {
                if (subdirectory.m_name.size() != subdirectoryName.size())
                {
                    return false;
                }

                for (size_t charIndex = 0; charIndex < subdirectoryName.size(); ++charIndex)
                {
                    if (subdirectoryName[charIndex] != subdirectory.m_name[charIndex])
                    {
                        return false;
                    }
                }

                return true;
            });

            return it != directory.m_subDirectories.end() ? &(*it) : nullptr;
        }

        void FindAllMatchingDirectories(DirectoryItem const& directory, std::vector<DirectoryItem const*>& outFoundDirectories, std::function<bool (DirectoryItem const&)> const& findPredicateFunction)
        {
            if (findPredicateFunction(directory))
            {
                outFoundDirectories.push_back(&directory);
            }

            for (DirectoryItem const& subDirectory : directory.m_subDirectories)
            {
                FindAllMatchingDirectories(subDirectory, outFoundDirectories, findPredicateFunction);
            }
        }
    };
}
