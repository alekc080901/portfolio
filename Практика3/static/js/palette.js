/**
 * Generates a random palette of HSV colors.  Attempts to pick colors
 * that are as distinct as possible within the desired HSV range.
 *
 * @param {number}    [options.numColors=10] - the number of colors to generate
 * @param {number[]}  [options.hRange=[0,1]] - the maximum range for generated hue
 * @param {number[]}  [options.sRange=[0,1]] - the maximum range for generated saturation
 * @param {number[]}  [options.vRange=[0,1]] - the maximum range for generated value
 * @param {number[][]}[options.exclude=[[0,0,0],[0,0,1]]] - colors to exclude
 *
 * @returns {number[][]} an array of HSV colors (each HSV color
 * is a [hue, saturation, value] array)
 */
function randomHSVPalette(options) {
    function random(min, max) {
        return min + Math.random() * (max - min);
    }

    function HSVtoXYZ(hsv) {
        var h = hsv[0];
        var s = hsv[1];
        var v = hsv[2];
        var angle = h * Math.PI * 2;
        return [Math.sin(angle) * s * v,
            Math.cos(angle) * s * v,
            v];
    }

    function distSq(a, b) {
        var dx = a[0] - b[0];
        var dy = a[1] - b[1];
        var dz = a[2] - b[2];
        return dx * dx + dy * dy + dz * dz;
    }

    if (!options) {
        options = {};
    }

    var numColors = options.numColors || 10;
    var hRange = options.hRange || [0, 1];
    var sRange = options.sRange || [0, 1];
    var vRange = options.vRange || [0, 1];
    var exclude = options.exclude || [[0, 0, 0], [0, 0, 1]];

    var points = exclude.map(HSVtoXYZ);
    var result = [];

    while (result.length < numColors) {
        var bestHSV;
        var bestXYZ;
        var bestDist = 0;
        for (var i = 0; i < 20; i++) {
            var hsv = [random(hRange[0], hRange[1]), random(sRange[0], sRange[1]), random(vRange[0], vRange[1])];
            var xyz = HSVtoXYZ(hsv);
            var minDist = 10;
            points.forEach(function (point) {
                minDist = Math.min(minDist, distSq(xyz, point));
            });
            if (minDist > bestDist) {
                bestHSV = hsv;
                bestXYZ = xyz;
                bestDist = minDist;
            }
        }
        points.push(bestXYZ);
        result.push(bestHSV);
    }

    return result;
}

function HSVtoRGB(hsv) {
    var h = hsv[0];
    var s = hsv[1];
    var v = hsv[2];

    var i = ~~(h * 6);
    var f = h * 6 - i;
    var p = v * (1 - s);
    var q = v * (1 - f * s);
    var t = v * (1 - (1 - f) * s);
    v = ~~(255 * v);
    p = ~~(255 * p);
    q = ~~(255 * q);
    t = ~~(255 * t);
    switch (i % 6) {
        case 0:
            return [v, t, p, 255];
        case 1:
            return [q, v, p, 255];
        case 2:
            return [p, v, t, 255];
        case 3:
            return [p, q, v, 255];
        case 4:
            return [t, p, v, 255];
        case 5:
            return [v, p, q, 255];
    }
}