import subprocess
import os
import pathlib


if __name__ == "__main__":
    for (root,dirs,files) in os.walk('.', topdown=True):
        for file in files:
            if pathlib.Path(file).suffix == ".tex":
                subprocess.run(["pdflatex", os.path.join(root, file)])