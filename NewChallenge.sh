#!/bin/sh

# Fetch the arguments and adjust them
YEAR_ARG=${1}
DAY_ARG=${2}

if [[ (-z $YEAR_ARG) || (-z $DAY_ARG) ]]; then
    echo "ERROR!  Invalid arguments."
    echo "        Command  ->  sh generate_challenge.sh [YEAR] [DAY_NO_ZERO]"
    echo "        Example  ->  sh generate_challenge.sh 2020 1"
    exit 1
fi

YEAR=$(expr $YEAR_ARG + 0)
DAY_NO_ZERO=$(expr $DAY_ARG + 0)

if [ $DAY_NO_ZERO -lt 10 ]; then
    DAY_ZEROED="0$DAY_NO_ZERO"
else
    DAY_ZEROED="$DAY_NO_ZERO"
fi


# Fetch the session key
SESSION_KEY_FILE_PATH="input/SessionKey.txt"
SESSION_KEY=$(<$SESSION_KEY_FILE_PATH)

if [[ -z "$SESSION_KEY" ]]; then
    echo "ERROR!  No session key specified. Check the README for project setup instructions."
    exit 1
fi


# Download the input file for the day
INPUT_DIR="input/$YEAR"
INPUT_FILE_PATH="$INPUT_DIR/$DAY_ZEROED.txt"

if [ ! -d $INPUT_DIR ]; then
    mkdir $INPUT_DIR
fi

URL="https://adventofcode.com/$YEAR/day/$DAY_NO_ZERO/input"
echo "Downloading input file from $URL"
curl $URL -H "cookie: session=$SESSION_KEY" -o $INPUT_FILE_PATH


# Copy the template files and create a new challenge if needed
TEMPLATE_DIR="source/challenges/templates"
YEAR_DIR="source/challenges/$YEAR"

YEAR_TEMPLATE_NAME="YearTemplate"
YEAR_TEMPLATE_FILE_PATH="$TEMPLATE_DIR/$YEAR_TEMPLATE_NAME.h"
YEAR_NAME="Year$YEAR"
YEAR_FILE_PATH="$YEAR_DIR/$YEAR_NAME.h"

if [ ! -d $YEAR_DIR ]; then
    mkdir $YEAR_DIR
fi

if [ ! -e $YEAR_FILE_PATH ]; then
    cp $YEAR_TEMPLATE_FILE_PATH $YEAR_FILE_PATH
    sed -i -e "s/YearTemplate/Year$YEAR/g" "$YEAR_FILE_PATH"

    echo ""
    echo "Created new year file from template as $YEAR_FILE_PATH"
    echo "IMPORTANT!  Remember to manually edit source/challenges/ChallengeFactory.h to be able to use the challenges from this new year"
fi

CHALLENGE_TEMPLATE_NAME="ChallengeTemplate"
CHALLENGE_TEMPLATE_FILE_PATH="$TEMPLATE_DIR/$CHALLENGE_TEMPLATE_NAME.h"
CHALLENGE_NAME="Challenge$DAY_ZEROED"
CHALLENGE_FILE_PATH="$YEAR_DIR/$CHALLENGE_NAME.h"

if [ ! -e $CHALLENGE_FILE_PATH ]; then
    cp $CHALLENGE_TEMPLATE_FILE_PATH $CHALLENGE_FILE_PATH
    sed -i -e "s/ChallengeTemplate/Challenge$DAY_ZEROED/g" "$CHALLENGE_FILE_PATH"

    echo ""
    echo "Created new challenge file from template as $CHALLENGE_FILE_PATH"
fi
