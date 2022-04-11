'use strict';

// 3
function secondHighest(arr) {
    return arr.sort((a, b) => b - a)[1];
}

// 21
function sumOfEven(arr) {
    return arr.reduce((sum, cur) => sum += cur % 2 == 0 ? cur : 0, 0);
}

// 27
function twoDegreeBorder(arr) {
    return [Math.floor(Math.log(Math.min(...arr)) / Math.log(2)),
    Math.ceil(Math.log(Math.max(...arr)) / Math.log(2))];
}

console.log(secondHighest([4, 14, 5, 7, 2, 8]));
console.log(sumOfEven([4, 14, 5, 7, 2, 8]));
console.log(twoDegreeBorder([4, 14, 5, 7, 2, 8, 65]));