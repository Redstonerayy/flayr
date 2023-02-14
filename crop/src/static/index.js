const btn = document.querySelector(".load-img");
const imgcanvas = document.querySelector(".img-canvas");
const imgctx = imgcanvas.getContext("2d");
const drawcanvas = document.querySelector(".draw-canvas");
const drawctx = drawcanvas.getContext("2d");

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

btn.addEventListener("click", async (ev) => {
    // get image
    let stringbase = await getImage("0.jpg");
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
    // console.log(ev);
    mousedown = true;
    // clientx is not the position, where the canvas was clicked
    // it's the overall position. this calculates the real position
    const rect = drawcanvas.getBoundingClientRect();
    startx = ev.clientX - rect.left;
    starty = ev.clientY - rect.top;
});

drawcanvas.addEventListener("mouseup", (ev) => {
    // console.log(ev);
    // ctx.clearRect(0, 0, canvas.width, canvas.height);
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
