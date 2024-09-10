
import argparse
import datetime
import logging
import pathlib
import requests

# =================================================================================================

today = datetime.datetime.now()
day_first = 1
day_last = 25
month_december = 12

project_dir_path = pathlib.Path(__file__).parents[1].resolve()
resource_dir_path = project_dir_path / "res"
input_dir_path = resource_dir_path / "input"
session_key_file_path = resource_dir_path / "SessionKey.txt"

url_template = "https://adventofcode.com/{0}/day/{1}/input"
input_file_name_template = "Input_{0}_{1}.txt"

# =================================================================================================

def set_verbose(verbose):
    if verbose:
        logging.basicConfig(level = logging.DEBUG)
    else:
        logging.basicConfig(level = logging.INFO)

# =================================================================================================

def get_session_key():
    if not session_key_file_path.exists():
        logging.error(f"Session key file not found [path={session_key_file_path}]")
        quit()

    session_key = ""
    with session_key_file_path.open(mode = "r") as f:
        session_key = f.readline()

    if not session_key:
        logging.error(f"Session key file is empty [path={session_key_file_path}]")
        quit()

    return session_key

# =================================================================================================

def download_input(year, day, session_key):
    if day < day_first or day > day_last:
        logging.error(f"Day {day} is invalid.")
        quit()

    if year == today.year and day > today.day:
        logging.error(f"Day {day} is not available yet.")
        quit()

    if year > today.year or (year == today.year and today.month != month_december):
        logging.error(f"Year {year} is not available yet.")
        quit()

    url = url_template.format(year, day)
    response = requests.get(url, cookies = dict(session = session_key))

    if not response.ok:
        logging.error(f"Failed to download input text [status_code={response.status_code}] [url={url}]")
        quit()

    file_dir = input_dir_path / f"{year}"
    file_dir.mkdir(parents = True, exist_ok = True)

    file_name = input_file_name_template.format(year, day)
    file_path = file_dir / file_name

    with file_path.open(mode = "w") as f:
        f.write(response.text)

    logging.info(f"Downloaded input file \"{file_name}\"")

# =================================================================================================

parser = argparse.ArgumentParser(description = "AOC input downloader")
parser.add_argument(
    "-v",
    "--verbose",
    action = "store_true",
    help = "Display debug message from logging"
)
parser.add_argument(
    "-y",
    "--year",
    type = int,
    help = "Year of the input to download"
)
parser.add_argument(
    "-d",
    "--day",
    type = int,
    help = "Day of the input to download"
)
args = parser.parse_args()

set_verbose(args.verbose)

session_key = get_session_key()
logging.debug(f"session_key={session_key}")

if args.year and args.day:
    # Download the challenge for the specified year and day
    logging.debug(f"year={args.year}, day={args.day}")
    download_input(args.year, args.day, session_key)
    quit()

if args.year:
    # Download all challenges for the specified year
    start_day = day_first
    end_day = day_last

    if args.year == today.year and today.day < day_last:
        end_day = today.day

    logging.debug(f"year={args.year}, day={start_day}...{end_day}")
    for day in range(start_day, end_day + 1):
        download_input(args.year, day, session_key)
    quit()

if today.month == month_december:
    # Download the challenge for the current year and day
    logging.debug(f"year={today.year}, day={today.day}")
    download_input(today.year, today.day, session_key)
    quit()

logging.error("Can't download a challenge for today. Please specify a valid year and/or day.")
parser.print_usage()
