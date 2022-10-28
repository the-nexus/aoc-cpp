#include <iostream>
#include <string>
#include <vector>

#include "challenges/ChallengeFactory.h"
#include "tools/FileTool.h"
#include "tools/TimeTool.h"

#if defined(_DEBUG) && (defined(_WIN32) || defined(_WIN64))
    #define USE_LOCAL_ARGS 1
#endif

bool ParseArgs(int argc, char* argv[], int& outYear, int& outDay, bool& outRunPartOne, bool& outRunPartTwo)
{
#ifdef USE_LOCAL_ARGS

    outYear = 2021;
    outDay = 01;
    runPartOne = true;
    runPartTwo = true;
    return true;

#else

    outYear = outDay = 0;
    outRunPartOne = outRunPartTwo = true;

    if (argc > 2)
    {
        outYear = atoi(argv[1]);
        outDay = atoi(argv[2]);

        if (argc > 3)
        {
            int const partNumber = argc > 1 ? atoi(argv[3]) : -1;
            outRunPartOne = partNumber != 2;
            outRunPartTwo = partNumber != 1;
        }

        return true;
    }

    return false;

#endif // USE_LOCAL_ARGS
}

int main(int argc, char* argv[])
{
    int year, day;
    bool runPartOne, runPartTwo;

    if (ParseArgs(argc, argv, year, day, runPartOne, runPartTwo))
    {
        std::string const inputFilePath = "../input/" + std::to_string(year) + "/" + (day < 10 ? "0" : "") + std::to_string(day) + ".txt";
        std::vector<std::string> inputLines;
        if (FileTool::ReadAllLines(inputFilePath, inputLines))
        {
            if (ChallengeAbstract* challenge = ChallengeFactory::MakeChallenge(year, day))
            {
                TimeTool::PersistentTimer timer;

                std::cout << "<==========>  Set Up  <==========>" << std::endl;
                timer.Start();
                challenge->SetUp(inputLines);
                std::cout << "(" << timer.GetElapsedTime() << " s)" << std::endl << std::endl;

                if (runPartOne)
                {
                    std::cout << "<==========> Part One <==========>" << std::endl;
                    timer.Start();
                    challenge->Run_PartOne();
                    std::cout << "(" << timer.GetElapsedTime() << " s)" << std::endl << std::endl;
                }

                if (runPartTwo)
                {
                    std::cout << "<==========> Part Two <==========>" << std::endl;
                    timer.Start();
                    challenge->Run_PartTwo();
                    std::cout << "(" << timer.GetElapsedTime() << " s)" << std::endl << std::endl;
                }

                std::cout << "<==========> Clean Up <==========>" << std::endl;
                timer.Start();
                challenge->CleanUp();
                std::cout << "(" << timer.GetElapsedTime() << " s)" << std::endl << std::endl;

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
