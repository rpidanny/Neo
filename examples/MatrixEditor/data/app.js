var rows = 8;
var cells = 32;
var matrix;
var active = false;
var connection = new WebSocket('ws://' + location.hostname + ':81/', ['arduino']);

connection.onopen = function () {
  connection.send('Connect ' + new Date());
};

connection.onerror = function (error) {
  console.log('WebSocket Error ', error);
};

connection.onmessage = function (e) {
  console.log('Server: ', e.data);
};

connection.onclose = function () {
  console.log('WebSocket connection closed');
};

const onLoad = function () {
  var body = document.getElementsByTagName("BODY")[0];
  var grid = document.getElementById('_grid');
  var table = document.createElement('table');
  window.onmousedown = () => {
    active = true;
  };
  window.onmouseup = () => {
    active = false;
  };
  document.getElementById('generateButton').onclick = updateDisplay;
  document.getElementById('clearButton').onclick = clearDisplay;
  matrix = createArray(rows, cells);
  for (var i = 0; i < rows; ++i) {
    var row = document.createElement('tr');
    for (var j = 0; j < cells; ++j) {
      const elem = document.createElement('td');
      elem.setAttribute('data-row', i);
      elem.setAttribute('data-cell', j);
      elem.onmouseover = toggle;
      elem.onmousedown = function(e) {
        active = true;
        toggle(e);
      };
      elem.onmouseup = function(e) {
        active = false;
        toggle(e);
      };
      row.appendChild(elem);
    }
    table.appendChild(row);
  }
  grid.append(table);
}

function toggle(e) {
  if (active) {
    const element = e.path[0];
    const x = element.dataset.cell;
    const y = element.dataset.row;

    // if (hasClass(element, 'on')) {
    if (e.which == 3) {
      element.classList.remove('on');
      matrix[y][x] = 0;
    } else {
      matrix[y][x] = 1;
      element.classList.add('on');
    }
    console.log(e.which);
  }
}

function updateDisplay() {
  var xhttp = new XMLHttpRequest();
  const width = matrix[0].length;
  const height = matrix.length;
  const dispCount = width / 8;

  let results = [];
  console.log(matrix);
  for (var row = 0; row < height; row++) {
    for (var disp = 0; disp < dispCount; disp++) {
      let data = 0;
      for (var col = 0; col < 8; col++) {
        data += Math.pow(2, (7 - col)) * matrix[row][(disp * 8) + col];
      }
      results.push(('00' + data.toString()).slice(-3));
    }
  }
  // xhttp.onreadystatechange = function() {
  //   if (this.readyState == 4 && this.status == 200) {
  //     console.log(this.responseText);
  //   }
  // }
  console.log('#' + results.join(''));
  // xhttp.open("POST", "/render", true);
  // xhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
  // xhttp.send("frame="+results.join(''));
  connection.send('#' + results.join(''));
}

function clearDisplay() {
  const width = matrix[0].length;
  const height = matrix.length;

  for (var row = 0; row < height; row++) {
    for (var col = 0; col < width; col++) {
      matrix[row][col] = 0;
    }
  }
  let elements = document.getElementsByClassName('on');
  if (elements.length > 0) {
    for(var i =0; i < elements.length; i++){
      elements[i].classList.remove('on');
    }
    clearDisplay();
  } else {
    updateDisplay();
  }
}

function hasClass(element, className) {
  return (' ' + element.className + ' ').indexOf(' ' + className + ' ') > -1;
}

function createArray(length) {
  var arr = new Array(length || 0).fill(0),
    i = length;

  if (arguments.length > 1) {
    var args = Array.prototype.slice.call(arguments, 1);
    while (i--) arr[length - 1 - i] = createArray.apply(this, args);
  }

  return arr;
}