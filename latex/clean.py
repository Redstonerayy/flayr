import os
import pathlib

blacklisted = [
    ".aux",
    ".fls",
    ".log",
    ".pdf",
    ".gz",
    ".fdb_latexmk"
]

if __name__ == "__main__":
    for (root,dirs,files) in os.walk('.', topdown=True):
        for file in files:
            if pathlib.Path(file).suffix in blacklisted:
                os.remove(os.path.join(root, file))