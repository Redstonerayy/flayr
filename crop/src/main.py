#!/usr/bin/env python3

from flask import Flask, send_file, request
import os

# flask app
app = Flask(__name__)


@app.route("/get-image", methods=["POST"])
def getimage():
    print(request.json["filepath"])
    return send_file("0.jpg", mimetype="image/jpg")


@app.route("/crop-image", methods=["POST"])
def cropimage():
    print(request.json["filepath"])
    print(request.json["dimensions"])


# index file
@app.route("/")
def hello_world():
    return app.send_static_file("index.html")


if __name__ == "__main__":
    app.run()
