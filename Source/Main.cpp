
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <Challenges/ChallengeFactory.h>
#include <Tools/FileReader.h>
#include <Tools/Time/ChronoTimer.h>

using namespace AOC;

//#define NO_TIMER

#ifdef NO_TIMER
    #define CHRONO_START(_name)
    #define CHRONO_STOP(_name)
    #define CHRONO_PRINT(_name, _description)
#else
    #define CHRONO_NAME(_name) timer_##_name
    #define CHRONO_START(_name) Tools::ChronoTimer CHRONO_NAME(_name);\
        CHRONO_NAME(_name).Start();
    #define CHRONO_STOP(_name, _description) CHRONO_NAME(_name).Stop(); \
        std::cout << _description << CHRONO_NAME(_name).GetElapsedTime() << " s" << std::endl << std::endl;
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
    if (!Tools::FileReader::GetLines(inputFilePath, inputLines))
    {
        std::cerr << "Could not read input file [" << inputFilePath << "]" << std::endl;
        return -1;
    }

    if (inputLines.empty())
    {
        std::cerr << "Input file was empty [" << inputFilePath << "]" << std::endl;
    }

    CHRONO_START(inputParsing);
    std::unique_ptr<Challenges::ChallengeAbstract> challenge = Challenges::ChallengeFactory::MakeChallenge(year, day, inputLines);
    CHRONO_STOP(inputParsing, "Input Parsing   ");

    if (!challenge)
    {
        std::cerr << "Unsupported challenge [Year=" << year << " Day=" << day << "]" << std::endl;
        return -1;
    }

    CHRONO_START(partOne);
    challenge->Run_PartOne();
    CHRONO_STOP(partOne, "Part One        ");

    CHRONO_START(partTwo);
    challenge->Run_PartTwo();
    CHRONO_STOP(partTwo, "Part Two        ");

    CHRONO_START(cleanUp);
    challenge->CleanUp();
    challenge.reset();
    CHRONO_STOP(cleanUp, "Clean Up        ");

    return 0;
}

int main(int argc, char* argv[])
{
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
}
