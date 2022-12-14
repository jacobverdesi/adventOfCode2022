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

// adds 'i+j' if is a row input and 'j+i' if it is a column input
function addToVisibleTreesForTreeHouse(
  visibleTrees,
  i,
  j,
  isRow,
  howManyVisible
) {
  if (isRow) {
    if (!visibleTrees.hasOwnProperty(i.toString() + "/" + j.toString())) {
      visibleTrees[i.toString() + "/" + j.toString()] = [howManyVisible];
    } else {
      visibleTrees[i.toString() + "/" + j.toString()].push(howManyVisible);
    }
  } else {
    if (!visibleTrees.hasOwnProperty(j.toString() + "/" + i.toString())) {
      visibleTrees[j.toString() + "/" + i.toString()] = [howManyVisible];
    } else {
      visibleTrees[j.toString() + "/" + i.toString()].push(howManyVisible);
    }
  }
}

function getVisibleTreesFromRowsForTreeHouse(rows, isRow = true, visibleTrees) {
  for (let i = 1; i < Object.keys(rows).length - 1; i++) {
    for (let j = 1; j < rows[i].length - 1; j++) {
      let howManyVisible = 1;
      let idxToTest = j + 1;
      if (j < rows[i].length - 2) {
        while (
          rows[i][j] > rows[i][idxToTest] &&
          idxToTest < rows[i].length - 1
        ) {
          howManyVisible += 1;
          idxToTest += 1;
        }
      }
      addToVisibleTreesForTreeHouse(visibleTrees, i, j, isRow, howManyVisible);
      howManyVisible = 1;
      idxToTest = j - 1;
      if (j > 1) {
        while (rows[i][j] > rows[i][idxToTest] && idxToTest > 0) {
          howManyVisible += 1;
          idxToTest -= 1;
        }
      }
      addToVisibleTreesForTreeHouse(visibleTrees, i, j, isRow, howManyVisible);
    }
  }
  return visibleTrees;
}

function getTreeHouseTreeMap(treeMap) {
  const rowsAndColumns = getTreeRowsAndColumns(buildTreeMap(treeMap));
  let visibleTrees = {};
  let visibleTreesFromRows = getVisibleTreesFromRowsForTreeHouse(
    rowsAndColumns[0],
    true,
    visibleTrees
  );
  let visibleTreesFromRowsAndColumns = getVisibleTreesFromRowsForTreeHouse(
    rowsAndColumns[1],
    false,
    visibleTreesFromRows
  );
  let allSums = [];
  for (let k in visibleTreesFromRowsAndColumns) {
    allSums.push(visibleTrees[k].reduce((x, y) => x * y));
  }
  return Math.max(...allSums);
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
console.log(getTreeHouseTreeMap(treeMap));
