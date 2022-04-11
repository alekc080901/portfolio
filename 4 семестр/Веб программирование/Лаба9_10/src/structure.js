"use strict";

function clearMain() {
  main.innerHTML = "";
}

function createSimpleFillword() {
  clearMain()

  let header = document.createElement("header");
  header.innerHTML = "Простой филворд";

  let fillwordContainer = document.createElement("div");
  fillwordContainer.classList.add("fillword-container");

  let fillwordTableContainer = document.createElement("div");
  fillwordTableContainer.classList.add("fillword-table-container");

  let likeButton = document.createElement("button");
  likeButton.classList.add("like-button");
  likeButton.innerText = "❤️";

  fillwordContainer.append(fillwordTableContainer, likeButton);

  let changeSizeContainer = document.createElement("div");

  let changeSizeLabel = document.createElement("p");
  changeSizeLabel.classList.add("change-size-label");
  changeSizeLabel.innerText = "Настроить размер";

  let changeSizeForm = document.createElement("select");
  changeSizeForm.id = "size_form";

  let options = [];
  for (let i = 4; i <= 10; i++) {
    let option = document.createElement("option");
    option.value = i;
    option.innerText = `${i}X${i}`;
    options.push(option);
  }

  options[2].selected = true;

  options.forEach((option) => changeSizeForm.append(option));

  changeSizeContainer.append(changeSizeLabel, changeSizeForm);

  main.append(header, fillwordContainer, changeSizeContainer);

  let tableClass = new Table(fillwordTableContainer);
  tableClass.refreshTable();

  size_form.addEventListener("change", (event) => tableClass.refreshTable());
}

function createTimeFillword() {
  clearMain();
  let header = document.createElement("header");
  header.innerHTML = "Филворд на время";

  let fillwordContainer = document.createElement("div");
  fillwordContainer.classList.add("fillword-container");

  let fillwordTableContainer = document.createElement("div");
  fillwordTableContainer.classList.add("fillword-table-container");

  let likeButton = document.createElement("button");
  likeButton.classList.add("like-button");
  likeButton.innerText = "❤️";

  fillwordContainer.append(fillwordTableContainer, likeButton);

  let changeSizeContainer = document.createElement("div");

  let changeSizeLabel = document.createElement("p");
  changeSizeLabel.classList.add("change-size-label");
  changeSizeLabel.innerText = "Настроить размер";

  let changeSizeForm = document.createElement("select");
  changeSizeForm.id = "size_form";

  let options = [];
  for (let i = 4; i <= 10; i++) {
    let option = document.createElement("option");
    option.value = i;
    option.innerText = `${i}X${i}`;
    options.push(option);
  }

  options[2].selected = true;

  let timeContainer = document.createElement("div");
  timeContainer.classList.add("time-label");
  timeContainer.innerText = "Время: 00:00";

  options.forEach((option) => changeSizeForm.append(option));

  changeSizeContainer.append(changeSizeLabel, changeSizeForm);

  main.append(header, fillwordContainer, timeContainer, changeSizeContainer);

  let tableClass = new Table(fillwordTableContainer);
  tableClass.refreshTable();

  size_form.addEventListener("change", (event) => tableClass.refreshTable());
}

function createLikedWindow() {
  clearMain();
  let header = document.createElement("header");
  header.innerHTML = "Любимые филворды";

  let favouritesContainer = document.createElement("div");
  favouritesContainer.classList.add("favourites-image-blocks");

  let favourite = document.createElement("div");

  let likeButton = document.createElement("button");
  likeButton.classList.add("like-button", "favourites-like-button");
  likeButton.innerText = "❤️";

  favouritesContainer.append(favourite, likeButton, favourite.cloneNode(true), likeButton.cloneNode(true));

  main.append(header, favouritesContainer);
}

function createShopWindow() {
  clearMain();
  let header = document.createElement("header");
  header.innerHTML = "Магазин";

  let shopContainer = document.createElement("div");
  shopContainer.classList.add("shop-variants");

  let variant = document.createElement("div");

  shopContainer.append(variant.cloneNode(true), variant.cloneNode(true), variant.cloneNode(true));

  main.append(header, shopContainer);
}

simple_fillword.addEventListener("click", createSimpleFillword);
time_fillword.addEventListener("click", createTimeFillword);
liked.addEventListener("click", createLikedWindow);
shop_link.addEventListener("click", createShopWindow);
