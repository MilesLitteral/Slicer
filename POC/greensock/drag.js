var fus = $("#box")[0];
var bucket = $("#bucket");

var changeColor = function () {
    d3.select("#box").attr("fill", "red");
};

var createDraggable = function () {

    Draggable.create(box, {
        trigger: box,
        type: "x,y",
        edgeResistance: 0.65,
        bounds: {
            minY: 0,
            maxY: 700,
            minX: 0,
            maxX: 700
        },
        onDrag: function () {
            d3.select("#box").attr("fill", "blue");


            var sound = $("#box")[0];
            var bucket = $("#bucket")[0];
            console.log (intersectRect(sound, bucket));
        },
        onRelease: function () {


            changeColor();


        }

    })
};

function intersectRect(_sound, _bucket) {



    box = _sound.getBoundingClientRect(); //BOUNDING BOX OF THE FIRST OBJECT
    bucket = _bucket.getBoundingClientRect(); //BOUNDING BOX OF THE SECOND OBJECT

    
    //CHECK IF THE TWO BOUNDING BOXES OVERLAP
    return !(bucket.left > box.right ||
        bucket.right < box.left ||
        bucket.top > box.bottom ||
        bucket.bottom < box.top);



}

$(document).ready(function () {



    createDraggable();



})