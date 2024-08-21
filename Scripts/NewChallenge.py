
import argparse
import datetime
import logging
import pathlib

# =================================================================================================

today = datetime.datetime.now()
day_first = 1
day_last = 25
month_december = 12

project_dir_path = pathlib.Path(__file__).parents[1].resolve()
challenges_dir_path = project_dir_path/"Source/Challenges/Challenges"
template_file_path = project_dir_path/"Scripts/Templates/Challenge.txt"
template_year_token = "##__YEAR__##"
template_day_token = "##__DAY__##"

challenge_file_name_format = "Challenge_{year}_{day}.hpp"

# =================================================================================================

def set_verbose(verbose):
    if verbose:
        logging.basicConfig(level = logging.DEBUG)
    else:
        logging.basicConfig(level = logging.INFO)

# =================================================================================================

def instantiate_template(year, day, force):
    if not template_file_path.exists():
        logging.error(f"Template file is missing [path={template_file_path}]")
        quit()

    file_template = ""
    with template_file_path.open(mode = "r") as f:
        file_template = f.read()

    file_content = file_template.replace(template_year_token, f"{year}").replace(template_day_token, f"{day}")

    file_dir_path = challenges_dir_path / f"{year}"
    file_dir_path.mkdir(parents = True, exist_ok = True)

    file_name = challenge_file_name_format.format(year = year, day = day);
    file_path = file_dir_path / file_name
    if file_path.exists() and not force:
        logging.error(f"Challenge file already exists [path={file_path}]")
        quit()

    with file_path.open(mode = "w") as f:
        f.write(file_content)

    logging.info(f"Created challenge file \"{file_name}\"")

# =================================================================================================

parser = argparse.ArgumentParser(description = "AOC input downloader")
parser.add_argument(
    "-v",
    "--verbose",
    action = "store_true",
    help = "Display debug message from logging"
)
parser.add_argument(
    "-f",
    "--force",
    action = "store_true",
    help = "Overwrites existing challenge file"
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

if args.year and args.day:
    # Instantiate the challenge template for the specified year and day
    logging.debug(f"year={args.year}, day={args.day}")
    instantiate_template(args.year, args.day, args.force)
    quit()

if today.month == month_december:
    # Instantiate the challenge template for the current year and day
    logging.debug(f"year={today.year}, day={today.day}")
    instantiate_template(today.year, today.day, args.force)
    quit()

logging.error("Can't create a challenge for today. Please specify a valid year and day.")
parser.print_usage()