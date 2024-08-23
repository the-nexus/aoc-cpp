
import argparse
import logging
import pathlib

# =================================================================================================

glob_filter = "**/Challenge_*_*.hpp"

autogen_file_name = "Factory.autogen.inl"
autogen_format = "{header}\n{includes}\n{registry}\n"

autogen_header = """
// ======================================================================
// THIS FILE WAS AUTOMATICALLY GENERATED WHEN BUILDING THE CMAKE PROJECT.
// PLEASE REBUILD THE CMAKE PROJECT IF YOU INTEND TO ADD NEW ITEMS.
// ======================================================================
"""

includes_format = "#include \"{path}\""
registry_format = "    RegisterChallenge<{name}>();"
registry_define_format = "#define AUTOGEN_CHALLENGE_REGISTRY \\\n{registry}"

# =================================================================================================

def set_verbose(verbose):
    if verbose:
        logging.basicConfig(level = logging.DEBUG)
    else:
        logging.basicConfig(level = logging.INFO)

# =================================================================================================

def make_includes(source_files):
    includes = "\n".join([
        includes_format.format(path = path) for path in source_files
    ])

    return includes

# =================================================================================================

def make_registry(source_files):
    if len(source_files) == 0:
        return ""

    challenge_names = [file.stem for file in source_files]
    logging.debug(f"{challenge_names}")

    registry = " \\\n".join([
        registry_format.format(name = name) for name in challenge_names
    ])

    return registry_define_format.format(registry = registry)

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

source_files_glob = list(source_dir.rglob(glob_filter))
source_files = [file.relative_to(source_dir) for file in source_files_glob]
source_files.sort()

output_dir.mkdir(parents = True, exist_ok = True)
output_file_path = output_dir / autogen_file_name

with output_file_path.open(mode = "w") as f:
    f.write(autogen_format.format(
        header = autogen_header,
        includes = make_includes(source_files),
        registry = make_registry(source_files)
    ))

logging.info(f"Generated challenge registry files to {output_file_path}")