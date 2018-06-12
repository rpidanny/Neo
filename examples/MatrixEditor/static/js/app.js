var matrix;

function toggle(e) {
  const element = e.path[0];
  const x = element.dataset.cell;
  const y = element.dataset.row;
  if (hasClass(element, 'on')) {
    element.classList.remove('on');
    matrix[y][x] = 0;
  } else {
    matrix[y][x] = 1;
    element.classList.add('on');
  }
  console.log(x, y);
}

const onLoad = function () {
  var grid = document.getElementById('_grid');
  var table = document.createElement('table');
  document.getElementById('generateButton').onclick = generateByteArray;
  var rows = 8;
  var cells = 32;
  matrix = createArray(rows, cells);
  for (var i = 0; i < rows; ++i) {
    var row = document.createElement('tr');
    for (var j = 0; j < cells; ++j) {
      const elem = document.createElement('td');
      elem.setAttribute('data-row', i);
      elem.setAttribute('data-cell', j);
      elem.onmousedown = toggle;
      row.appendChild(elem);
    }
    table.appendChild(row);
  }
  grid.append(table);
}

function generateByteArray() {
  const width = matrix[0].length;
  const height = matrix.length;
  console.log(matrix);
  // TODO: convert matrix to byteArray
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