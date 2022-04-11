let degree = 1;
let delay = 2;
let stop = false;

function animate() {
    if (stop)
        return;

    document.images.shop.src = `./shop/shop${degree}.png`; 
    degree++;
    if (degree == 360) {
        degree = 1;
    }
    setTimeout(animate, delay);
}

function stopAnimate() {
    stop = true;
    document.images.shop.src = './shop.png'; 
}

shop_link.onmouseenter = () => { stop = false; console.log("in"); animate() };
shop_link.onmouseleave = () => { console.log("out"); stopAnimate() };