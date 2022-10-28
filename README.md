# aoc-cpp
This project contains code for the yearly Advent of Code challenges (https://adventofcode.com/). It uses C++ to solve the challenges and this project provides tools to automate the setup of new days and simplify the setup of new years of challenges.

When cloning this repository, you'll need to do a few things to get things to work properly.

## External requirements
Make sure you have CMake installed on your machine so you can use the **'cmake'** command. You can test if CMake is installed by running the command **'cmake --version'**. Using CMake to setup the project allows for easy setup on on any platform.

You will also need a compiler. On Windows, you can use Visual Studio with C++ 17 or higher. On Linux, you can use the package '**g++**' (may also require **'build-essential'**) to compile using makefiles.

For instance, on Windows, if Visual Studio is installed, CMake will create the .sln and .vcxproj files. On Linux, CMake will create the makefile project. You will find the generated project files in the folder **'bin/'**. This is also where the project will be compiled and where you will find the executables.

## Finding your session key
If you need a visual example, please follow [this link](https://github.com/wimglenn/advent-of-code-wim/issues/1).

You'll need to set up your session key when you first pull this project, or if any of the input files shows an error message. To find your session key, open up a webpage containing your input data for any of the days. Then inspect the page and go to the network section to view your cookies (if none of your cookies are visible in that page, reload the webpage by pressing the F5 key).

The session cookie will look something like "cookie: session=9u312097re453490237ty5t4537274h3097a40270" (this is an example key, not a real one). You want to pick what comes after "session=" and place it in the file **'input/SessionKey.txt'** that is provided.

## Using the scripts
First, you have the **'GenerateSolution.sh'** script. It will generate the project solution (or regenerate if it already exists) using CMake into the folder **'bin/'**. The command is **'sh GenerateSolution.sh'**.

Second, you have the **'GenerateChallenge.sh'** script. It will create a new challenge file (and a new year file if required) for the desired challenge parameters passed in. The command is **'sh GenerateChallenge.sh [Year] [Day]'**.

**Note:** When adding a new year, you need to edit **'source/challenges/ChallengeFactory.h'** and follow the instructions from the comment at the top of the file to be able to use the newly created year file from the script **'GenerateChallenge.sh'**.

## Running the solution
Once compiled, you can run the app in 2 ways. If on Windows in Visual Studio with the Debug profile, you can edit the parameters in Main.cpp. From Release (or if you disable the macro for Debug), you can run the .exe from the cmd and pass it arguments. On linux, you just need to run ./AdventOfCode from the terminal and pass it arguments.

The program takes 2 arguments at minimum and can take a 3rd argument optionally. The first argument is the year, the second is the day, and the 3rd is the part. For instance: **'./AdventOfCode 2021 01 1'** will run Part 1 of Day 1 of Year 2021. Not passing a 3rd argument or passing an invalid argument (a.k.a not 1 and not 2) will run both parts by default.
