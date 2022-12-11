const common = require("../common");

function buildTreeMap(input) {
  let twoDArray = [];
  for (let i in input) {
    if (input[i]) {
      let oneDArray = [];
      for (let j in input[i]) {
        oneDArray.push(parseInt(input[i].charAt(j), 10));
      }
      twoDArray.push(oneDArray);
    }
  }
  return twoDArray;
}

function getTreeRowsAndColumns(treeMap) {
  let treeRows = {};
  let treeColumns = {};
  for (let row in treeMap) {
    for (let column in treeMap[row]) {
      if (!treeColumns.hasOwnProperty(column)) {
        treeColumns[column] = [treeMap[row][column]];
      } else {
        treeColumns[column].push(treeMap[row][column]);
      }
    }
    treeRows[row] = treeMap[row];
  }
  return [treeRows, treeColumns];
}

// adds 'i+j' if is a row input and 'j+i' if it is a column input
function addToVisibleTrees(visibleTrees, i, j, isRow) {
  if (isRow) {
    visibleTrees.add(i.toString() + "/" + j.toString());
  } else {
    visibleTrees.add(j.toString() + "/" + i.toString());
  }
}

function getVisibleTreesFromRows(rows, isRow = true) {
  let visibleTrees = new Set();
  for (let i = 0; i < Object.keys(rows).length; i++) {
    // add all from first row/column
    if (i == 0) {
      for (let j in rows[i]) {
        addToVisibleTrees(visibleTrees, i, j, isRow);
      }
      // add all from last row/column
    } else if (i == Object.keys(rows).length - 1) {
      for (let j in rows[i]) {
        addToVisibleTrees(visibleTrees, i, j, isRow);
      }
    } else {
      // iterate forward and add when greater then the max element
      let maxElement = rows[i][0];
      for (let j = 1; j < rows[i].length - 1; j++) {
        if (rows[i][j] > maxElement) {
          addToVisibleTrees(visibleTrees, i, j, isRow);
          maxElement = rows[i][j];
        }
      }
      // iterate backward and add when greater than the max element
      maxElement = rows[i][rows[i].length - 1];
      for (let j = rows[i].length - 2; j > 0; j--) {
        if (rows[i][j] > maxElement) {
          addToVisibleTrees(visibleTrees, i, j, isRow);
          maxElement = rows[i][j];
        }
      }
    }
  }
  return visibleTrees;
}

function getVisibleTrees(treeMap) {
  const rowsAndColumns = getTreeRowsAndColumns(buildTreeMap(treeMap));
  const rows = getVisibleTreesFromRows(rowsAndColumns[0]);
  const columns = getVisibleTreesFromRows(rowsAndColumns[1], false);
  const visibleTrees = new Set([...rows, ...columns]);
  return visibleTrees.size;
}

const treeMap = common.textFileToArray("./dayEight.txt");

console.log(getVisibleTrees(treeMap));
