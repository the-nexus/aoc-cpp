
import argparse
import logging
import pathlib
import requests

# =================================================================================================

project_dir_path = pathlib.Path(__file__).parents[1].resolve()
session_key_file_path = project_dir_path / "SessionKey.txt"
input_dir_path = project_dir_path / "Input"

url_template= "https://adventofcode.com/{year}/day/{day}/input"

# =================================================================================================

def get_arguments():
    parser = argparse.ArgumentParser(description = "AOC input downloader")
    parser.add_argument("-v", "--verbose", action = "store_true", help = "Display debug message from logging")
    parser.add_argument("year", type = int, help = "Year of the input to download")
    parser.add_argument("day", type = int, help = "Day of the input to download")
    args = parser.parse_args()

    if args.verbose:
        logging.basicConfig(level = logging.DEBUG)
    else:
        logging.basicConfig(level = logging.INFO)

    if not args.year or not args.day:
        logging.error("Invalid date. Make sure you specify a year and a day in the month of december.")
        quit()

    return args.year, args.day

# =================================================================================================

def get_session_key(file_path):
    if not file_path.exists():
        logging.error(f"Session key file not found [file_path={file_path}]")
        quit()

    session_key = ""
    with file_path.open(mode = "r") as f:
        session_key = f.readline()

    if not session_key:
        logging.error(f"Session key file is empty [file_path={file_path}]")
        quit()

    return session_key

# =================================================================================================

def download_input(year, day, session_key):
    response = requests.get(url_template.format(year, day), cookies = dict(session = session_key))

    if not response.ok:
        logging.error(f"Failed to download input text [status_code={response.status_code}] [url={file_path}]")
        quit()

    input_dir_path.mkdir(parents = True, exist_ok = True)
    input_file_path = input_dir_path / f"Input_{year}_{day}.txt"

    if input_file_path.exists:
        input_file_path.remove()
        
    with input_file_path.open(mode = "w") as f:
        f.write(response.text)


# =================================================================================================

year, day = get_arguments()
logging.debug(f"year={year}")
logging.debug(f"day={day}")

session_key = get_session_key(session_key_file_path)
logging.debug(f"session_key={session_key}")

download_input(year, day, session_key)
