
import os
import pathlib

project_dir = pathlib.Path(__file__).parents[1].resolve()
build_dir = project_dir / "build"

os.system(f"cmake -B{build_dir} -S{project_dir}")
