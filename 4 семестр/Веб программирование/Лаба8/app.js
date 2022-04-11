"use strict";

function Person(name, age, isMarried = false) {
  this.name = name;
  this.age = age;
  this.married = isMarried;

  const names = {
    name: "Имя",
    age: "Возраст",
    married: (val) => (val ? "Женат" : "Не женат"),
  };

  this.toString = () =>
    Object.entries(names)
      .map(([key, val]) =>
        typeof val === "string" ? `${val}: ${this[key]}` : `${val(this[key])}`
      )
      .join("\n");
}

function a() {
    return this.age;
}

Array.prototype.mean = function() {
    return this.reduce((sum, cur) => sum + cur, 0) / this.length;
}

let obj = new Object();

const vasya = new Person('Василек Теребовльский', 22, false);

// console.log(vasya.toString());

// console.log([2, 3, 4, 5, 10].mean());