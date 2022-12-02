#include <iostream>
#include <string>
#include <vector>

#include "challenges/ChallengeFactory.h"
#include "tools/FileTool.h"
#include "tools/TimeTool.h"
#include "tests/Tests.h"

//#define RUN_TOOLS_TESTS
//#define NO_TIMER

#ifdef NO_TIMER
    #define CHRONO_DECLARE(_name)
    #define CHRONO_START(_name)
    #define CHRONO_STOP(_name)
    #define CHRONO_PRINT(_name, _description)
#else
    #define CHRONO_NAME(_name) timer_##_name
    #define CHRONO_DECLARE(_name) TimeTool::ChronoTimer CHRONO_NAME(_name)
    #define CHRONO_START(_name) CHRONO_NAME(_name).Start();
    #define CHRONO_STOP(_name) CHRONO_NAME(_name).Stop();
    #define CHRONO_PRINT(_name, _description) std::cout << _description << CHRONO_NAME(_name).GetElapsedTime() << " s" << std::endl << std::endl
#endif // NO_TIMER

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

int RunAdventOfCode(int const year, int const day)
{
    std::string const inputFilePath = "../input/" + std::to_string(year) + "/" + (day < 10 ? "0" : "") + std::to_string(day) + ".txt";
    std::vector<std::string> inputLines;
    if (FileTool::ReadAllLines(inputFilePath, inputLines))
    {
        if (ChallengeAbstract* challenge = ChallengeFactory::MakeChallenge(year, day))
        {
            CHRONO_DECLARE(setUp);
            CHRONO_START(setUp);
            challenge->SetUp(inputLines);
            CHRONO_STOP(setUp);
            CHRONO_PRINT(setUp, "Setup       ");

            CHRONO_DECLARE(partOne);
            CHRONO_START(partOne);
            challenge->Run_PartOne();
            CHRONO_STOP(partOne);
            CHRONO_PRINT(partOne, "Part One    ");

            CHRONO_DECLARE(partTwo);
            CHRONO_START(partTwo);
            challenge->Run_PartTwo();
            CHRONO_STOP(partTwo);
            CHRONO_PRINT(partTwo, "Part Two    ");

            CHRONO_DECLARE(cleanUp);
            CHRONO_START(cleanUp);
            challenge->CleanUp();
            CHRONO_STOP(cleanUp);
            CHRONO_PRINT(cleanUp, "Clean Up    ");

            delete challenge;
        }
        else
        {
            std::cout << "ERROR: Unsupported challenge [Year=" << year << " Day=" << day << "]" << std::endl;
            return -1;
        }
    }
    else
    {
        std::cout << "ERROR: Could not read input file [" << inputFilePath << "]" << std::endl;
        return -1;
    }

    return 0;
}

int main(int argc, char* argv[])
{
#ifdef RUN_TOOLS_TESTS

    Tests::RunTests();
    return 0;

#else // RUN_TOOLS_TESTS

    int year, day;
    if (ParseArgs(argc, argv, year, day))
    {
        return RunAdventOfCode(year, day);
    }
    else
    {
        std::cout << "ERROR: Could not parse arguments" << std::endl;
        return -1;
    }

#endif // RUN_TOOLS_TESTS
}
