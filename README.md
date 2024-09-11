# aoc-cpp
A framework implemented using C++ to solve the the challenges from the [**Advent of Code**](https://adventofcode.com/) yearly event.

## Generating the solution
The main dependencies of this project are CMake, Python 3 and a C++ compiler of choice that supports C++20.

**NOTE:** Python is mandatory for CMake to be able to generate the solution properly as it uses scripts to automatically generate code. The scripts have been written using Python 3. The commands ```python``` and ```python3``` can be used alternatively as long as they run Python 3.

### Windows
On Windows, this repo has been tested for both MSVC, using Visual Studio 2022, and on WSL2 with a Ubuntu distro, using the steps listed in the **Linux** section below.

You should install the following software:
- [CMake](https://cmake.org/download/)
- [Python3](https://www.python.org/downloads/)
- [Visual Studio](https://visualstudio.microsoft.com/vs/)

From a terminal like Powershell or Git Bash, you can run the following command to setup the solution:

```cmake -S . -B build```

This will generate a .sln for Visual Studio 2022. From there, you can set the **AdventOfCode** project as your startup project to be able to build and run the solution.

### Linux
This repo was built on Ubuntu. No other distro has been tested, but you should be able to reproduce the steps with equivalent commands and packages. As such, on Ubuntu, you should install the following packages:
- g++
- gdb
- build-essential
- cmake
- python3

```sudo apt-get install g++ gdb build-essential cmake python3```

The simplest way to run the repo is to open it from its root with VS Code. With the CMake extension installed and any compiler of choice (though, only g++ has been tested on Linux), you can then use the CMake extension to generate the solution from within VS Code. Then, you can use VS Code to build, run and debug the generated project.

Alternatively, if you want to build and run the solution using other text editors, you can achieve similar results using the following commands from the root directory of the project:
1) Generate the CMake solution

    ```cmake -S . -B build```

2) Compile the code

    ```make -C build```

3) Run the executable

    ```./build/AdventOfCode```


## Session Key
To be able to download the input text as a file, you will need to provide your user-unique session key.

This session key needs to be placed in a text file residing in ```./res/SessionKey.txt```. This file is included in the ```.gitignore``` definition as it is unique to you and should not be used by anyone else.

If the following instructions are unclear, please checkout [this guide](https://github.com/wimglenn/advent-of-code-wim/issues/1).

1) Open a web browser (ex. Firefox, Chrome, ...).
2) Head to the [Advent of Code](https://adventofcode.com/) website.
3) Log in using your choice of credentials.
4) Head to any available challenge page (ex. [The very first challenge!](https://adventofcode.com/2015/day/1)).
5) Inspect the page and go to the **Network** tab so that you can monitor web traffic.
6) Refresh the page to populate the tab.
7) From the received documents, select the file that has the same name as the day of the opened challenge webpage.
8) Within its list of cookies, there should be a cookie with the name ```session```.
9) Copy the value of the cookie (without the prefix ```session``` or any quotation) into the file ```./res/SessionKey.txt```.


## Downloading input files
After setting up your session key, you can use python scripts to download the input files. The input files live at the following path:

```./res/input/YEAR/```

**NOTE:** The content of the input files are intellectual property of the creators of the **Advent of Code** event. They can be used freely within the context of solving challenges but, in respect of the hard work of their creators, they should never be pushed to any source control. With that in mind, their directory has been added to the ```.gitignore``` definition to prevent them from being pushed.

You can use the provided python script in a few different ways to download input files.
1) By specifying both the year and day arguments, you will download your input file for that specific challenge.

    ```python script/DownloadInput.py -y YEAR -d DAY```

2) By specifying only the year argument, you will download all the input files for the available challenges of that year.

    ```python script/DownloadInput.py -y YEAR```

3) By not specifying any year or day argument, if the event is active (during the first 25 days of december), you can download the input file for the current day.

    ```python script/DownloadInput.py```

## Setting up a new challenge
You can create the necessary code to setup a new day quickly using the following command, with the desired day and year specified:
```python scripts/NewChallenge.py -y YEAR -d DAY```

Alternatively, if the event is active (during the first 25 days of december), you can run the script without arguments to generate the code for the current day.

The challenge file template will be instantiated at the following path:
```./src/challenges/challenges/YEAR/Challenge_YEAR_DAY.hpp```

You should re-run the CMake project generation anytime you add/remove/generate files within the ```./src``` directory.

## Architecture
The framework is devided in a few modules:
1) **Core:** Contains all reusable code that could be ported in other projects. This code is not specifically tied to the Advent of Code event but improves the quality of life for the user.
2) **Challenges:** Contains all implemented programs for the daily challenges of the event. Those programs are then automatically registered to a factory so that they can be instantiated using a pair of values representing the Year and Day of a challenge.
3) **Runtime:** Defines the program to run from ```Main.cpp```. It receives arguments, parses them into a config, generates a challenge instance from a factory using the config, reads the appropriate input text file, then runs the challenge's code against the input text to obtain the challenge's answer.
