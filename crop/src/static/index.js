let mainimg = document.querySelector(".main-image");

let btn = document.querySelector(".load-img");

// creates a qr code from the value of the input field and shows it
async function getImage(filepath, imgel) {
    return fetch("/get-image", {
        method: "POST",
        headers: {
            "Content-Type": "application/json",
        },
        body: JSON.stringify({ filepath: filepath }),
    })
        .then(async (res) => {
            let buffer = await res.arrayBuffer();
            var base64 = btoa(
                new Uint8Array(buffer).reduce(
                    (data, byte) => data + String.fromCharCode(byte),
                    ""
                )
            );
            imgel.src = "data:image/jpg;base64," + base64;
        })
        .catch((res) => {
            console.log(res);
        });
}

btn.addEventListener("click", (ev) => {
    getImage("0.jpg", mainimg);
});
