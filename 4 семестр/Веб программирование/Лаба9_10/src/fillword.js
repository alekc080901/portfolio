"use strict";

let table = document.querySelector(".fillword-table-container");

let isPressed = false;
let prevButton = null;
class WordFiller {
  handleEvent(event) {
    switch (event.type) {
      case "mousedown":
        event.target.style.background = "red";
        prevButton = event.target;
        isPressed = true;
        break;

      case "mouseover":
        if (isPressed && event.target.style.background != "red") {
          let dx =
            event.target.getBoundingClientRect()["x"] -
            prevButton.getBoundingClientRect()["x"];
          let dy =
            event.target.getBoundingClientRect()["y"] -
            prevButton.getBoundingClientRect()["y"];
          if ((Math.abs(dx) != 0) ^ (Math.abs(dy) != 0)) {
            event.target.style.background = "red";
            prevButton = event.target;
          }
        }
        break;

      case "mouseup":
        isPressed = false;
        break;
    }
  }
}

class Table {
  constructor(table) {
    this.table = table;
    this.buttons = table.children;
  }
  
  freeTable() {
    this.table.innerHTML = "";
  }

  fillTable(size) {
    if (size < 4 && size > 10) {
      console.warn("Wrong size");
      return;
    }

    let r = document.querySelector(":root");
    r.style.setProperty("--tabel-rows-num", size);
    r.style.setProperty("--tabel-cols-num", size);
    this.table.innerHTML = `<button></button>\n`.repeat(size ** 2);
  }

  setListeners() {
    for (let button of this.buttons)
      button.addEventListener("mousedown", new WordFiller(button));

    for (let button of this.buttons)
      button.addEventListener("mouseup", new WordFiller(button));

    for (let button of this.buttons)
      button.addEventListener("mouseover", new WordFiller(button));
  }

  refreshTable() {
    const size = +size_form.selectedOptions[0].value;
    this.freeTable();
    this.fillTable(size);
    this.setListeners();
  }
}

let tableClass = new Table(table);
tableClass.refreshTable();

size_form.addEventListener("change", (event) => tableClass.refreshTable());
table.addEventListener("mouseleave", (event) => (isPressed = false));
