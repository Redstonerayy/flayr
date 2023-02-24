from PIL import Image

img = Image.open("0/0-crop.png")

twentysixthwidth = img.size[0] / 26
thirdheight = img.size[1] / 3
imgparts = []
for i in range(3):
    for j in range(26):
        imgparts.append(
            img.crop(
                j * twentysixthwidth, i * thirdheight, twentysixthwidth, thirdheight
            )
        )

for imgpart in imgparts:
    imgpart.save()
