"use strict";

function newMaze(x, y) {
    var totalCells = x*y;
    var cells = new Array();
    var unvis = new Array();

    for(var i = 0; i < y; i++) {
        cells[i] = new Array();
        unvis[i] = new Array();
        for(var j = 0; j < x; j++) {
            cells[i][j] = [0,0,0,0];
            unvis[i][j] = true;
        }
    }

    var currentCell = [0, 0];
    var path = [currentCell];

    unvis[currentCell[0]][currentCell[1]] = false;
    var visited = 1;

    while(visited < totalCells) {
        var potential =
            [
                [currentCell[0]-1, currentCell[1], 0, 2],  //top
                [currentCell[0], currentCell[1]+1, 1, 3],  //right
                [currentCell[0]+1, currentCell[1], 2, 0],  //bottom
                [currentCell[0], currentCell[1]-1, 3, 1]   //left
            ];

        var neighbors = new Array();

        for(var l = 0; l < 4; l++) {
            if(
                potential[l][0] > -1 &&                     // Is the y value of the neighbor inside the maze?
                potential[l][0] < y &&
                potential[l][1] > -1 &&                     // Is the x value of the neighbor inside the maze?
                potential[l][1] < x &&
                unvis[potential[l][0]][potential[l][1]]     // Has the neighbor already been visited?
            ) {
                neighbors.push(potential[l])
            }
        }

        if(neighbors.length) {

            var next = neighbors[Math.floor(Math.random()*neighbors.length)];
            cells[currentCell[0]][currentCell[1]][next[2]] = 1;
            cells[next[0]][next[1]][next[3]] = 1;
            unvis[next[0]][next[1]] = false;
            visited++;
            currentCell = [next[0], next[1]];
            path.push(currentCell)

        } else {
            currentCell = path.pop();
        }
    }
    return cells;
}

function drawMaze() {
    var x = document.forms["options"]["x"].value;
    var y = document.forms["options"]["y"].value;
    var maze = newMaze(x, y);
    var text = new Array();
    var c;
    var d;

    for(var a = 0; a < y; a++) {
        for(var b = 0; b < x; b++) {
            c = (a*2) + 1;
            d = (b*2) + 1;
            if(text[c - 1] === undefined) {
                text[c - 1] = new Array();
            }
            if(text[c] === undefined) {
                text[c] = new Array();
            }
            if(text[c + 1] === undefined) {
                text[c + 1] = new Array();
            }
            if (maze[a][b][0] === 0) {
                text[c - 1][d] = "-";
            } else {
                text[c - 1][d] = " ";
            }

            if (maze[a][b][1] === 0) {
                text[c][d + 1] = "|";
            } else {
                text[c][d + 1] = " ";
            }

            if (maze[a][b][2] === 0) {
                text[c + 1][d] = "-";
            } else {
                text[c + 1][d] = " ";
            }

            if (maze[a][b][3] === 0) {
                text[c][d - 1] = "|";
            } else {
                text[c][d - 1] = " ";
            }
            text[c][d] = " ";
        }
    }

    for(var z = 0; z < text.length; z += 2) {
        text[z][text[z].length] = "+";
    }

    text[1][0] = " ";
    text[text.length - 2][text[0].length - 1] = " ";

    var table = "";
    for(var e = 0; e < text.length; e++) {
        for(var f = 0; f < text[e].length; f++) {
            if(text[e][f] === undefined) {
                table += "+";
            } else {
                table += text[e][f];
            }
        }
        table += "\n";
    }
    document.getElementById("maze").innerHTML = table;
}

function copyToClipboard() {
    var textArea = document.getElementById("maze");
    textArea.select();
    document.execCommand('copy');
}