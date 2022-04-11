let degree = 1;
let delay = 2;
let stop = false;

function animate() {
  if (stop) return;

  document.images.shop.src = `./img/shop/shop${degree}.png`;
  degree++;
  if (degree == 360) {
    degree = 1;
  }
  setTimeout(animate, delay);
}

function stopAnimate() {
  stop = true;
  document.images.shop.src = "./img/icons/shop.png";
}

shop_link.onmouseenter = () => {
  stop = false;
  animate();
};
shop_link.onmouseleave = () => {
  stopAnimate();
};
