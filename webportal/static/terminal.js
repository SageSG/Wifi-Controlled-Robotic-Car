var workspace = Blockly.inject('blocklyDiv',
{
    toolbox: document.getElementById('toolbox'
    ), trashcan: true,
    horizontalLayout: true,
    collapse: true
});

// One function 
// var map = {{ map| safe }};  // Get the map from Python 
var counter = 1;            // Counter is used to facilitate 
var path_start = 0;         // Start of the map path 
var path_end = 0;           // End of the map path
const path = [];            // List that contains the map path

var car_index = 0;          // Where the Car traveresed 
const car_path = [];        // Path the car traveresed 
var i = 0;                  // 

setInterval(function () {
numberofblockly = parseInt(workspace.getAllBlocks(false).length)
document.getElementById('totalCommands').innerText = 'No. of Blocks Used: ' + numberofblockly.toString();
}, 500);

var car_face_downwards, car_face_upwards, car_face_left, car_face_right;


// Check for the start flag 
for (let i = 0; i < map.length; i++) {
if (map[i].includes("1")) {
    index = map[i].indexOf("1") + counter;
    path_start = index;
    path.push(path_start);
    break;
}
counter = counter + 8;
}

if(path_start <= 8){
car_face_downwards = true;
car_face_upwards = false;
car_face_left = false;
car_face_right = false;
document.getElementById("grid" + path_start).innerHTML = '<img src="{{ url_for("static", filename="/img/carimg.png")}}" class="facedown" width="40" height="40">';
}
else if (path_start == 9 || path_start == 17 || path_start == 25 || path_start == 33 || path_start == 41 || path_start == 49){
car_face_downwards = false;
car_face_upwards = false;
car_face_left = false;
car_face_right = true;
document.getElementById("grid" + path_start).innerHTML = '<img src="{{ url_for("static", filename="/img/carimg.png")}}" class="faceright" width="40" height="40">';
}else if (path_start == 56 || path_start == 48 || path_start == 40 || path_start == 32 || path_start == 24 || path_start == 16){
car_face_downwards = false;
car_face_upwards = false;
car_face_left = true;
car_face_right = false;
document.getElementById("grid" + path_start).innerHTML = '<img src="{{ url_for("static", filename="/img/carimg.png")}}" class="faceleft" width="40" height="40">';
}
else if(path_start >= 57){
car_face_downwards = false;
car_face_upwards = true;
car_face_left = false;
car_face_right = false;
document.getElementById("grid" + path_start).innerHTML = '<img src="{{ url_for("static", filename="/img/carimg.png")}}" class="faceup" width="40" height="40">';
}



// Check for the tiles flag 
counter = 1;
for (let i = 0; i < map.length; i++) {
for (let y = 0; y < map[i].length; y++) {
    // console.log(map[i][y]);
    if (map[i][y] == "2") {
        index = y + counter;
        path.push(index);
    }
}
counter = counter + 8;
}

// Check for the end flag 
counter = 1;
for (let i = 0; i < map.length; i++) {
if (map[i].includes("3")) {
    index = map[i].indexOf("3") + counter;
    path_end = index;
    path.push(path_end);
    break;
}
counter = counter + 8;
}

// Function to process the car index if the car turns left 
function turnLeft(car_index) {
if (car_face_downwards == true) {
    car_index += 1;
    car_face_right = true;
    car_face_downwards = false;
    car_face_upwards = false;
    car_face_left = false;
    try {
        document.getElementById("grid" + car_index).innerHTML = '<img src="{{ url_for("static", filename="/img/carimg.png")}}" class="facedown" width="40" height="40">';
    } catch (error) {
        console.log(error)
    }
}

else if (car_face_upwards == true) {
    car_index -= 1;
    car_face_right = false;
    car_face_downwards = false;
    car_face_upwards = false;
    car_face_left = true;
    try {
        document.getElementById("grid" + car_index).innerHTML = '<img src="{{ url_for("static", filename="/img/carimg.png")}}" class="faceleft" width="40" height="40">';
    } catch (error) {
        console.log(error)
    }
}

else if (car_face_left == true) {
    car_index += 8;
    car_face_right = false;
    car_face_downwards = true;
    car_face_upwards = false;
    car_face_left = false;
    try {
        document.getElementById("grid" + car_index).innerHTML = '<img src="{{ url_for("static", filename="/img/carimg.png")}}" class="facedown" width="40" height="40">';
    } catch (error) {
        console.log(error)
    }
}

else if (car_face_right == true) {
    car_index -= 8;
    car_face_right = false;
    car_face_downwards = false;
    car_face_upwards = true;
    car_face_left = false;
    try {
        document.getElementById("grid" + car_index).innerHTML = '<img src="{{ url_for("static", filename="/img/carimg.png")}}" class="faceup" width="40" height="40">';
    } catch (error) {
        console.log(error)
    }
}
return car_index;
}


// Function to process the car index if the car turns right 
function turnRight(car_index) {
if (car_face_downwards == true) {
    car_index -= 1;
    car_face_right = false;
    car_face_downwards = false;
    car_face_upwards = false;
    car_face_left = true;
    try {
        document.getElementById("grid" + car_index).innerHTML = '<img src="{{ url_for("static", filename="/img/carimg.png")}}" class="faceleft" width="40" height="40">';
    } catch (error) {
        console.log(error)
    }
}

else if (car_face_upwards == true) {
    car_index += 1;
    car_face_right = true;
    car_face_downwards = false;
    car_face_upwards = false;
    car_face_left = false;
    try {
        document.getElementById("grid" + car_index).innerHTML = '<img src="{{ url_for("static", filename="/img/carimg.png")}}" class="faceright" width="40" height="40">';
    } catch (error) {
        console.log(error)
    }
}

else if (car_face_left == true) {
    car_index -= 8;
    car_face_right = false;
    car_face_downwards = false;
    car_face_upwards = true;
    car_face_left = false;
    try {
        document.getElementById("grid" + car_index).innerHTML = '<img src="{{ url_for("static", filename="/img/carimg.png")}}" class="faceup" width="40" height="40">';
    } catch (error) {
        console.log(error)
    }
}

else if (car_face_right == true) {
    car_index += 8;
    car_face_right = false;
    car_face_downwards = true;
    car_face_upwards = false;
    car_face_left = false;
    try {
        document.getElementById("grid" + car_index).innerHTML = '<img src="{{ url_for("static", filename="/img/carimg.png")}}" class="facedown" width="40" height="40">';
    } catch (error) {
        console.log(error)
    }
}
return car_index;
}

// Function to process the car index if the car moves forward 
function moveForward(car_index) {
if (car_face_downwards == true) {
    car_index += 8;
    car_face_right = false;
    car_face_downwards = true;
    car_face_upwards = false;
    car_face_left = false;
    try {
        document.getElementById("grid" + car_index).innerHTML = '<img src="{{ url_for("static", filename="/img/carimg.png")}}" class="facedown" width="40" height="40">';
    } catch (error) {
        console.log(error)
    }
}
else if (car_face_upwards == true) {
    car_index -= 8;
    car_face_right = false;
    car_face_downwards = false;
    car_face_upwards = true;
    car_face_left = false;
    try {
        document.getElementById("grid" + car_index).innerHTML = '<img src="{{ url_for("static", filename="/img/carimg.png")}}" class="faceup" width="40" height="40">';;
    } catch (error) {
        console.log(error)
    }
}
else if (car_face_left == true) {
    car_index -= 1;
    car_face_right = false;
    car_face_downwards = false;
    car_face_upwards = false;
    car_face_left = true;
    try {
        document.getElementById("grid" + car_index).innerHTML = '<img src="{{ url_for("static", filename="/img/carimg.png")}}" class="faceleft" width="40" height="40">';;
    } catch (error) {
        console.log(error)
    }
}
else if (car_face_right == true) {
    car_index += 1;
    car_face_right = true;
    car_face_downwards = false;
    car_face_upwards = false;
    car_face_left = false;
    try {
        document.getElementById("grid" + car_index).innerHTML = '<img src="{{ url_for("static", filename="/img/carimg.png")}}" class="faceright" width="40" height="40">';
    } catch (error) {
        console.log(error)
    }
}
return car_index;
}


// Move the car left
function Motor_Left() {
car_index = turnLeft(car_index);
if (!checkRoute(car_index)) {
    game_over = true
}
car_path.push(car_index);
}

// Move the car right 
function Motor_Right() {
car_index = turnRight(car_index);
if (!checkRoute(car_index)) {
    game_over = true
}
car_path.push(car_index);
}

// Move the car forward
function Motor_Start() {
car_index = moveForward(car_index);
if (!checkRoute(car_index)) {
    game_over = true
}
car_path.push(car_index);
}

function checkRoute(gridnum) {
let x = 0
let y = 0
x = Math.floor(gridnum / 8)
y = (gridnum - ((x) * 8)) - 1
if (map[x][y] == 2) {
    document.getElementById("grid" + gridnum).style.backgroundColor = "green"
    return true
} else if (map[x][y] == 3) {
    document.getElementById("grid" + gridnum).style.backgroundColor = "green"
    return true
}
else {
    document.getElementById("grid" + gridnum).style.backgroundColor = "red"
    return false
}

}
var game_over = false;
// Function to parse and execute the commands on the "Command List" textarea from the webpage.
function showCode() {
console.log(map)
// Generate code and display it.
while (directionArr.length > 0) {
    directionArr.pop();
}
result = "";
Blockly.JavaScript.INFINITE_LOOP_TRAP = null;
Blockly.JavaScript.addReservedWords('code');
var code = Blockly.JavaScript.workspaceToCode(workspace);
result = code.concat("\n", result);
document.getElementById('textArea').innerText = result;



// Parse the commands gotten from the 'textArea'
const commands = code.split("\n");
car_index = path_start;

//Run the command list using eval function
eval(code);

// Check to see if the car has reached the end point 
if (car_index == path_end) {
    document.getElementById("grid" + car_index).style.backgroundColor = "lightblue"
    $("#game_won_modal").modal({ backdrop: 'static', keyboard: false })
    $("#game_won_modal").modal("show");
    return;
}
else {
    try {
        document.getElementById("grid" + car_index).style.background = "red";
    } catch (err) {
        console.log(err)
    }
    $("#game_over_modal").modal({ backdrop: 'static', keyboard: false })
    $("#game_over_modal").modal("show");
    return;
}

}

function resetGame() {
car_face_downwards = false;
car_face_upwards = true;
car_face_left = false;
car_face_right = false;
clearCode();
document.getElementById('createMap').innerHTML = '<div class="card-body pb-4">\
            <div class="row">\
                <div class="col-12">\
                    <div class="numbers">\
                        <p id="changeTitle" class="text-sm mb-3 text-capitalize font-weight-bold" style="color: white;">\
                            <b>Game Map</b>\
                        </p>\
                    </div>\
                    {% set count = namespace(value=1) %}\
                    {% for map_list in map %}\
                    <div class="row">\
                        {% for map_coordinates in map_list %}\
                        {% if map_coordinates == "0" %}\
                        <div class="div1" id="grid{{count.value}}">\
                        </div>\
                        {% elif map_coordinates == "1" %}\
                        <div class="div1" id="grid{{count.value}}" style="background:lightblue;">\
                            <img id="carImg" src="{{ url_for("static", filename="/img/carimg.png")}}" width="40"\
                                height="40">\
                        </div>\
                        {% elif map_coordinates == "2" %}\
                        <div class="div1" id="grid{{count.value}}" style="background:yellow;">\
                        </div>\
                        {% elif map_coordinates == "3" %}\
                        <div class="div1" id="grid{{count.value}}" style="background:lightblue;">\
                            <img src="{{ url_for("static", filename="/img/end.jpg")}}" width="40" height="40">\
                        </div>\
                        {% endif %}\
                        {% set count.value = count.value + 1 %}\
                        {% endfor %}\
                    </div>\
                    {% endfor %}\
                </div>\
            </div>\
        </div>';
workspace.clear()
}

function generateBomb() {
workspace.clear()
clearCode();

let listofroute = []

for (let x = 0; x < map.length; x++) {
    for (let y = 0; y < map.length; y++) {
        if (map[x][y] == 2) {
            listofroute.push([x, y])
        }
    }
}

var randint = Math.floor(Math.random() * listofroute.length);

map[listofroute[randint][0]][listofroute[randint][1]] = '4'

for (let x = 1; x < 65; x++) {
    document.getElementById('grid' + x.toString()).style.background = "grey"
    document.getElementById('grid' + x.toString()).removeChild(document.getElementById('grid' + x.toString()).firstChild)
}

console.log(listofroute[randint])

for (let x = 0; x < listofroute.length; x ++){
    let oldroutes = (parseInt(listofroute[x][0]) * 8) + (parseInt([listofroute[x][1]]) + 1)
    document.getElementById('grid' + oldroutes.toString()).style.background = "yellow"
}

var bomb = (parseInt(listofroute[randint][0]) * 8) + (parseInt([listofroute[randint][1]]) + 1)
var imgBomb = '<img src="{{ url_for("static", filename="/img/bomb.png")}}" width="40" height="40">'
document.getElementById('grid' + bomb.toString()).innerHTML = imgBomb
document.getElementById('grid' + bomb.toString()).style.background = "black"


if (map[listofroute[randint][0]][listofroute[randint][1] - 1] == '0') {
    // left side
    map[listofroute[randint][0]][listofroute[randint][1] - 1] = '2'
    let value = (parseInt(listofroute[randint][0]) * 8) + (parseInt([listofroute[randint][1] - 1]) + 1)
    document.getElementById('grid' + value).style.background = "yellow"
}
if (map[listofroute[randint][0]][listofroute[randint][1] + 1] == '0') {
    // right side
    map[listofroute[randint][0]][listofroute[randint][1] + 1] = '2'
    let value = (parseInt(listofroute[randint][0]) * 8) + (parseInt([listofroute[randint][1] + 1]) + 1)
    document.getElementById('grid' + value).style.background = "yellow"
}
if (map[listofroute[randint][0] - 1][listofroute[randint][1]] == '0') {
    // top side
    map[listofroute[randint][0] - 1][listofroute[randint][1]] = '2'
    let value = (parseInt(listofroute[randint][0] - 1) * 8) + (parseInt([listofroute[randint][1]]) + 1)
    document.getElementById('grid' + value).style.background = "yellow"
}
if (map[listofroute[randint][0] + 1][listofroute[randint][1]] == '0') {
    // bottom side
    map[listofroute[randint][0] + 1][listofroute[randint][1]] = '2'
    let value = (parseInt(listofroute[randint][0] + 1) * 8) + (parseInt([listofroute[randint][1]]) + 1)
    document.getElementById('grid' + value).style.background = "yellow"
}
if (map[listofroute[randint][0] - 1][listofroute[randint][1] - 1] == '0') {
    // diagonal top left side
    map[listofroute[randint][0] - 1][listofroute[randint][1] - 1] = '2'

    let value = (parseInt(listofroute[randint][0] - 1) * 8) + (parseInt([listofroute[randint][1] -1]) + 1)
    document.getElementById('grid' + value).style.background = "yellow"
}
if (map[listofroute[randint][0] + 1][listofroute[randint][1] + 1] == '0') {
    // diagonal top right side
    map[listofroute[randint][0] + 1][listofroute[randint][1] + 1] = '2'

    let value = (parseInt(listofroute[randint][0] + 1) * 8) + (parseInt([listofroute[randint][1] + 1]) + 1)
    document.getElementById('grid' + value).style.background = "yellow"
}
if (map[listofroute[randint][0] + 1][listofroute[randint][1] - 1] == '0') {
    // diagonal bottom left side
    map[listofroute[randint][0] + 1][listofroute[randint][1] - 1] = '2'
    let value = (parseInt(listofroute[randint][0] + 1) * 8) + (parseInt([listofroute[randint][1]-1]) + 1)
    document.getElementById('grid' + value).style.background = "yellow"
}
if (map[listofroute[randint][0] - 1][listofroute[randint][1] + 1] == '0') {
    // diagonal bottom right side
    map[listofroute[randint][0] - 1][listofroute[randint][1] + 1] = '2'
    let value = (parseInt(listofroute[randint][0] - 1) * 8) + (parseInt([listofroute[randint][1]+1]) + 1)
    document.getElementById('grid' + value).style.background = "yellow"
}

console.log(map)

document.getElementById('grid' + path_start).style.background = "lightblue"
console.log(path_start)
if(path_start <= 8){
car_face_downwards = true;
car_face_upwards = false;
car_face_left = false;
car_face_right = false;
document.getElementById("grid" + path_start).innerHTML = '<img src="{{ url_for("static", filename="/img/carimg.png")}}" class="facedown" width="40" height="40">';
}
else if (path_start == 9 || path_start == 17 || path_start == 25 || path_start == 33 || path_start == 41 || path_start == 49){
car_face_downwards = false;
car_face_upwards = false;
car_face_left = false;
car_face_right = true;
document.getElementById("grid" + path_start).innerHTML = '<img src="{{ url_for("static", filename="/img/carimg.png")}}" class="faceright" width="40" height="40">';
}else if (path_start == 56 || path_start == 48 || path_start == 40 || path_start == 32 || path_start == 24 || path_start == 16){
car_face_downwards = false;
car_face_upwards = false;
car_face_left = true;
car_face_right = false;
document.getElementById("grid" + path_start).innerHTML = '<img src="{{ url_for("static", filename="/img/carimg.png")}}" class="faceleft" width="40" height="40">';
}
else if(path_start >= 57){
car_face_downwards = false;
car_face_upwards = true;
car_face_left = false;
car_face_right = false;
document.getElementById("grid" + path_start).innerHTML = '<img src="{{ url_for("static", filename="/img/carimg.png")}}" class="faceup" width="40" height="40">';
}
document.getElementById('grid' + path_end).style.background = "lightblue"
var imgEnd = '<img src="{{ url_for("static", filename="/img/end.jpg")}}" width="40" height="40">'
document.getElementById('grid' + path_end).innerHTML = imgEnd

document.getElementById("changeTitle").innerHTML = '<div style="color:red; font-weight:bold;"> Game Map (Challenge Mode) </div>'
}