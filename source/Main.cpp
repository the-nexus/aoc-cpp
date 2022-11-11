#include <iostream>
#include <string>
#include <vector>

#include "challenges/ChallengeFactory.h"
#include "tools/FileTool.h"
#include "tools/TimeTool.h"

bool ParseArgs(int argc, char* argv[], int& outYear, int& outDay)
{
    outYear = outDay = 0;
    if (argc > 0)
    {
        std::string const absoluteExePath = argv[0];
        std::cout << absoluteExePath << std::endl;


        if (argc >= 3)
        {
            outYear = atoi(argv[1]);
            outDay = atoi(argv[2]);

            return true;
        }
        else if (argc == 1)
        {
            std::cout << "Enter challenge year: ";
            std::cin >> outYear;
            std::cout << "Enter challenge day: ";
            std::cin >> outDay;
            std::cout << std::endl;

            return true;
        }
    }

    return false;
}

int main(int argc, char* argv[])
{
    int year, day;

    if (ParseArgs(argc, argv, year, day))
    {
        std::string const inputFilePath = "../input/" + std::to_string(year) + "/" + (day < 10 ? "0" : "") + std::to_string(day) + ".txt";
        std::vector<std::string> inputLines;
        if (FileTool::ReadAllLines(inputFilePath, inputLines))
        {
            if (ChallengeAbstract* challenge = ChallengeFactory::MakeChallenge(year, day))
            {
                TimeTool::PersistentTimer timer;

                timer.Start();
                challenge->SetUp(inputLines);
                std::cout << "Setup       " << timer.GetElapsedTime() << " s" << std::endl << std::endl;

                timer.Start();
                challenge->Run_PartOne();
                std::cout << "Part One    " << timer.GetElapsedTime() << " s" << std::endl << std::endl;

                timer.Start();
                challenge->Run_PartTwo();
                std::cout << "Part Two    " << timer.GetElapsedTime() << " s" << std::endl << std::endl;

                timer.Start();
                challenge->CleanUp();
                std::cout << "Clean Up    " << timer.GetElapsedTime() << " s" << std::endl << std::endl;

                delete challenge;
                return 0;
            }
            else
            {
                std::cout << "ERROR: Unsupported challenge [Year=" << year << " Day=" << day << "]" << std::endl;
            }
        }
        else
        {
            std::cout << "ERROR: Could not read input file [" << inputFilePath << "]" << std::endl;
        }
    }
    else
    {
        std::cout << "ERROR: Could not parse arguments" << std::endl;
    }

    return -1;
}
