
import argparse
import logging
import pathlib

# =================================================================================================

file_glob_filter = "**/Challenge*.hpp"

includes_file_name = "ChallengeIncludes.inl"
includes_format = "{0}\n"
includes_item_format = "\n#include \"{0}\""

registration_file_name = "ChallengeRegistration.inl"
registration_format = "\n#define AUTO_GENERATED_CHALLENGE_REGISTRATION{0}\n"
registration_item_format = " \\\n    REGISTER_CHALLENGE({0})"

# =================================================================================================

def set_verbose(verbose):
    if verbose:
        logging.basicConfig(level = logging.DEBUG)
    else:
        logging.basicConfig(level = logging.INFO)

# =================================================================================================

def generate_includes_file(output_dir, root_dir, source_files):
    challenge_paths = [file.relative_to(root_dir) for file in source_files]
    logging.debug(f"{challenge_paths}")

    items = "".join([
        includes_item_format.format(item) for item in challenge_paths
    ])

    output_file_path = output_dir / includes_file_name
    with output_file_path.open(mode = "w") as f:
        f.write(includes_format.format(items))

# =================================================================================================

def generate_registration_file(output_dir, source_files):
    challenge_names = [file.stem for file in source_files]
    logging.debug(f"{challenge_names}")

    items = "".join([
        registration_item_format.format(item) for item in challenge_names
    ])

    output_file_path = output_dir / registration_file_name
    with output_file_path.open(mode = "w") as f:
        f.write(registration_format.format(items))

# =================================================================================================

parser = argparse.ArgumentParser(description = "AOC input downloader")
parser.add_argument(
    "-v",
    "--verbose",
    action = "store_true",
    help = "Display debug message from logging"
)
parser.add_argument(
    "source_dir",
    help = "Directory in which the challenge source files exist"
)
parser.add_argument(
    "output_dir",
    help = "Directory in which to generate the files"
)
args = parser.parse_args()

set_verbose(args.verbose)

source_dir = pathlib.Path(args.source_dir).resolve()
output_dir = pathlib.Path(args.output_dir).resolve()

source_files = list(source_dir.rglob(file_glob_filter))
output_dir.mkdir(parents = True, exist_ok = True)

generate_includes_file(output_dir, source_dir, source_files)
generate_registration_file(output_dir, source_files)

logging.info(f"Generated challenge registry files to {output_dir}")
