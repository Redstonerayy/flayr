#!/usr/bin/env python3

from flask import Flask, send_file, request
import os, sys
from PIL import Image

# flask app
app = Flask(__name__)

sourcefolder = sys.argv[1]
# create dest folder
destfolder = sys.argv[2]
if not os.path.exists(destfolder):
    os.makedirs(destfolder)


@app.route("/get-image", methods=["POST"])
def getimage():
    return send_file(request.json["filepath"], mimetype="image/jpg")


@app.route("/get-files", methods=["GET"])
def getfiles():
    files = os.listdir(sourcefolder)
    print(files)
    files = [
        file for file in files if file.split(".")[-1] in ["jpg", "jpeg", "png", "webp"]
    ]
    return {"folder": sourcefolder, "files": files}


@app.route("/crop-image", methods=["POST"])
def cropimage():
    print(request.json)
    # crop image in python
    sourcefile = request.json["filepath"]
    outpath = destfolder + "/" + os.path.basename(sourcefile).split(".")[0]
    if not os.path.exists(outpath):
        os.makedirs(outpath)
    # crop each image
    original = Image.open(sourcefile)
    for i, crop in enumerate(request.json["infos"]):
        newimg = original.crop(
            (
                original.size[0] * crop["startx"] / crop["width"],
                original.size[1] * crop["starty"] / crop["height"],
                original.size[0] * (crop["startx"] + crop["cropwidth"]) / crop["width"],
                original.size[1]
                * (crop["starty"] + crop["cropheight"])
                / crop["height"],
            )
        )
        newimg.save(os.path.join(outpath, f"{i}-crop.png"))

    return ["success"]


# index file
@app.route("/")
def hello_world():
    return app.send_static_file("index.html")


if __name__ == "__main__":
    app.run()
