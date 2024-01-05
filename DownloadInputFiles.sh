#!/bin/sh
YEAR_ARG=${1}

if [[ -z $YEAR_ARG ]]; then
    echo "ERROR!  Invalid arguments."
    echo "        Command  ->  sh DownloadInputFiles.sh [YEAR]"
    echo "        Example  ->  sh DownloadInputFiles.sh 2015"
    exit 1
fi

YEAR=$(expr $YEAR_ARG + 0)

# Fetch the session key
SESSION_KEY_FILE_PATH="./SessionKey.txt"
SESSION_KEY=$(cat $SESSION_KEY_FILE_PATH)

if [[ -z "$SESSION_KEY" ]]; then
    echo "ERROR!  No session key specified. Check the README for project setup instructions."
    exit 1
fi

echo "Using session key $SESSION_KEY"

# Download the input file for each day
INPUT_DIR="input/$YEAR"

if [ ! -d $INPUT_DIR ]; then
    mkdir $INPUT_DIR
fi

DAY_NO_ZERO=1
while [ $DAY_NO_ZERO -le 25 ]
do
    if [ $DAY_NO_ZERO -lt 10 ]; then
        DAY_ZEROED="0$DAY_NO_ZERO"
    else
        DAY_ZEROED="$DAY_NO_ZERO"
    fi

    INPUT_FILE_PATH="$INPUT_DIR/$DAY_ZEROED.txt"
    URL="https://adventofcode.com/$YEAR/day/$DAY_NO_ZERO/input"

    echo "Downloading input file from $URL"
    curl $URL -H "cookie: session=$SESSION_KEY" -o $INPUT_FILE_PATH

    ((DAY_NO_ZERO++))
done
