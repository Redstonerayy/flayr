const btn = document.querySelector(".load-img");
const imgcanvas = document.querySelector(".img-canvas");
const imgctx = imgcanvas.getContext("2d");
const drawcanvas = document.querySelector(".draw-canvas");
const drawctx = drawcanvas.getContext("2d");
const previewimgcontainer = document.querySelector(".preview-images");
const cropbtn = document.querySelector(".confirm-button");
const clearbtn = document.querySelector(".clear-button");
const currvalue = document.querySelector(".imagepos");
const fileshow = document.querySelector(".cur-file");

let currentcropinfos = [];
let files = undefined;
let index;

// creates a qr code from the value of the input field and shows it
async function getImage(filepath) {
    let imgbase64string = "";
    // fetch image from server
    await fetch("/get-image", {
        method: "POST",
        headers: {
            "Content-Type": "application/json",
        },
        body: JSON.stringify({ filepath: filepath }),
    })
        // get image data and convert to base64
        .then(async (res) => {
            let buffer = await res.arrayBuffer();
            var base64 = btoa(
                new Uint8Array(buffer).reduce(
                    (data, byte) => data + String.fromCharCode(byte),
                    ""
                )
            );
            // set variable name
            imgbase64string = "data:image/jpg;base64," + base64;
        })
        // some error idk
        .catch((res) => {
            console.log(res);
        });
    return imgbase64string;
}

const init = async () => {
    // load files
    await fetch("/get-files", {
        method: "GET",
    })
        // get image data and convert to base64
        .then(async (res) => {
            let jsonres = await res.json();
            files = jsonres;
        })
        // some error idk
        .catch((res) => {
            console.log(res);
        });
};

btn.addEventListener("click", async (ev) => {
    // get image
    index = Number(currvalue.value);
    let stringbase = await getImage(files.folder + "/" + files.files[index]);
    fileshow.textContent = files.files[index];
    let image = new Image();
    image.src = stringbase;
    // wait for image to load, else width and height are both 0
    image.onload = () => {
        // calculate aspect ratio
        let aspect = image.width / image.height;
        let height = imgcanvas.width / aspect;
        // set canvas stuff
        imgcanvas.height = height;
        drawcanvas.height = height;
        // draw image
        imgctx.drawImage(
            image,
            0,
            0,
            image.width,
            image.height,
            0,
            0,
            imgcanvas.width,
            imgcanvas.height
        );
    };
});

let mousedown = false;
let startx = 0;
let starty = 0;

drawcanvas.addEventListener("mousedown", (ev) => {
    mousedown = true;
    // clientx is not the position, where the canvas was clicked
    // it's the overall position. this calculates the real position
    const rect = drawcanvas.getBoundingClientRect();
    startx = ev.clientX - rect.left;
    starty = ev.clientY - rect.top;
});

drawcanvas.addEventListener("mouseup", (ev) => {
    // get current position
    const rect = imgcanvas.getBoundingClientRect();
    let xpos = ev.clientX - rect.left;
    let ypos = ev.clientY - rect.top;
    // save cropped image
    // create in memory canvas
    let buffer = document.createElement("canvas");
    let b_ctx = buffer.getContext("2d");
    // set dimensions
    let croppedwidth = Math.abs(xpos - startx);
    let croppedheight = Math.abs(ypos - starty);
    buffer.width = croppedwidth;
    buffer.height = croppedheight;
    // draw the main canvas on the buffer
    b_ctx.drawImage(
        imgcanvas,
        startx,
        starty,
        croppedwidth,
        croppedheight,
        0,
        0,
        buffer.width,
        buffer.height
    );
    // generate data url for preview
    let cropinfo = {
        width: drawcanvas.width,
        height: drawcanvas.height,
        startx: startx,
        starty: starty,
        cropwidth: croppedwidth,
        cropheight: croppedheight,
    };
    currentcropinfos.push(cropinfo);
    let dataurl = buffer.toDataURL();
    // add to preview images
    let previewimg = document.createElement("img");
    previewimg.src = dataurl;
    previewimgcontainer.appendChild(previewimg);
    // clear old react
    drawctx.clearRect(0, 0, drawcanvas.width, drawcanvas.height);
    // reset variables
    mousedown = false;
    startx = 0;
    starty = 0;
});

drawcanvas.addEventListener("mousemove", (ev) => {
    if (mousedown) {
        const rect = drawcanvas.getBoundingClientRect();
        let xpos = ev.clientX - rect.left;
        let ypos = ev.clientY - rect.top;
        // clear old react
        drawctx.clearRect(0, 0, drawcanvas.width, drawcanvas.height);
        // draw hightlight rect
        drawctx.beginPath();
        drawctx.lineWidth = "1";
        drawctx.rect(startx, starty, xpos - startx, ypos - starty);
        drawctx.stroke();
    }
});

cropbtn.addEventListener("click", async (ev) => {
    // reset application
    imgctx.clearRect(0, 0, imgcanvas.width, imgcanvas.height);
    // get next image
    previewimgcontainer.innerHTML = "";
    // send crop data
    await fetch("/crop-image", {
        method: "POST",
        headers: {
            "Content-Type": "application/json",
        },
        body: JSON.stringify({
            infos: currentcropinfos,
            filepath: files.folder + "/" + files.files[index],
        }),
    })
        .then(async (res) => {
            console.log(res);
        })
        // some error idk
        .catch((res) => {
            console.log(res);
        });
    // reset data
    currentcropinfos = [];
});

clearbtn.addEventListener("click", async (ev) => {
    previewimgcontainer.innerHTML = "";
    // reset data
    currentcropinfos = [];
});

document.addEventListener("keydown", async (ev) => {
    if (ev.key == "ArrowLeft") {
        if (!(index - 1 < 0)) {
            index--;
        }
    } else if (ev.key == "ArrowRight") {
        if (!(index + 1 > files.files.length - 1)) {
            index++;
        }
    }

    // clear old react
    drawctx.clearRect(0, 0, drawcanvas.width, drawcanvas.height);

    let stringbase = await getImage(files.folder + "/" + files.files[index]);
    fileshow.textContent = files.files[index];
    let image = new Image();
    image.src = stringbase;
    // wait for image to load, else width and height are both 0
    image.onload = () => {
        // calculate aspect ratio
        let aspect = image.width / image.height;
        let height = imgcanvas.width / aspect;
        // set canvas stuff
        imgcanvas.height = height;
        drawcanvas.height = height;
        // draw image
        imgctx.drawImage(
            image,
            0,
            0,
            image.width,
            image.height,
            0,
            0,
            imgcanvas.width,
            imgcanvas.height
        );
    };
});

init();
