#!/usr/bin/env python3

from flask import Flask, send_file, request
import os, sys

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
    print(request.json[0])

    return ["success"]


# index file
@app.route("/")
def hello_world():
    return app.send_static_file("index.html")


if __name__ == "__main__":
    app.run()
