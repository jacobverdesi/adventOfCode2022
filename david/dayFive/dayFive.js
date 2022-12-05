const co = require("../common");

// get the stack elements from input
function parseStackInputs(row) {
  let stackRow = [];
  for (let i = 1; i < row[0].length; i += 4) {
    stackRow.push(row[0].charAt(i));
  }
  return stackRow;
}

// remove non-numerics and empty values from move input
function parseMoveInput(move) {
  const moveSentence = move.split(" ");
  return moveSentence.map((i) => i.replace(/\D/g, "")).filter((i) => i != "");
}

// move elements from one stack to another (Question 1)
function moveStackElements(move, stacks) {
  const itemsToMove = parseInt(move[0], 10);
  const moveFrom = parseInt(move[1], 10) - 1;
  const moveTo = parseInt(move[2], 10) - 1;
  for (let i = 0; i < itemsToMove; i++) {
    stacks[moveTo].push(stacks[moveFrom].pop());
  }
}

// move elements from one stack to intermediate stack to final stack (Question 2)
function moveStackElementsFromLoader(move, stacks) {
  const itemsToMove = parseInt(move[0], 10);
  const moveFrom = parseInt(move[1], 10) - 1;
  const moveTo = parseInt(move[2], 10) - 1;
  let loader = [];
  for (let i = 0; i < itemsToMove; i++) {
    loader.push(stacks[moveFrom].pop());
  }
  for (let i = 0; i < itemsToMove; i++) {
    stacks[moveTo].push(loader.pop());
  }
}

// process all element moves and read last element from each stack
function getLastStackItems(textArray, moveLogic) {
  let stacks = [];
  let moves = [];

  // initialize blank lists for each stack
  for (let i = 1; i < textArray[0].length; i += 4) {
    stacks.push([]);
  }

  // read all rows
  for (let i in textArray) {
    const row = textArray[i];
    if (row) {
      // if row includes stack inputs parse the stack
      if (row.includes("[")) {
        let singleStack = parseStackInputs(row.split());
        for (let i in singleStack) {
          if (singleStack[i] != " ") {
            stacks[i].push(singleStack[i]);
          }
        }
        // if row includes move instruction process moves
      } else if (row.includes("move")) {
        moves.push(parseMoveInput(row));
      }
    }
  }
  // reverse all stacks to first element read in as the last element in the stack
  stacks.map((i) => i.reverse());
  for (let i in moves) {
    // process all moves according to move logic function
    moveLogic(moves[i], stacks);
  }

  return stacks.map(i => i[i.length-1]).join("")
}

const input = co.textFileToArray("./dayFive.txt");

console.log(getLastStackItems(input, moveStackElements));
console.log(getLastStackItems(input, moveStackElementsFromLoader));
