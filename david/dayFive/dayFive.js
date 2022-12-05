const co = require("../common");

function parseStackInputs(row) {
  let stackRow = [];
  for (let i = 1; i < row[0].length; i += 4) {
    stackRow.push(row[0].charAt(i));
  }
  return stackRow;
}

function parseMoveInput(move) {
    const moveSentence = move.split(' ')
    return moveSentence.map(i => i.replace(/\D/g,'')).filter(i => i != '')
}

function modifyStacksUsingPop(move, stacks) {
  const itemsToMove = parseInt(move[0], 10)
  const moveFrom = parseInt(move[1], 10) -1
  const moveTo = parseInt(move[2], 10) -1
    for (let i = 0; i < itemsToMove; i++) {
        stacks[moveTo].push(stacks[moveFrom].pop());
    }
}

function modifyStacksUsingLoader(move, stacks) {
  const itemsToMove = parseInt(move[0], 10)
  const moveFrom = parseInt(move[1], 10) - 1
  const moveTo = parseInt(move[2], 10) - 1
  let loader = []
    for (let i = 0; i < itemsToMove; i++) {
        loader.push(stacks[moveFrom].pop());
    }
    for (let i = 0; i < itemsToMove; i ++) {
        stacks[moveTo].push(loader.pop())
    }
}

//
function getLastStackItems(textArray, moveLogic) {
  let result = [];
  let stacks = [];
  let moves = [];

  // initialize blank lists for stacks
  for (let i = 1; i < textArray[0].length; i += 4) {
    stacks.push([]);
  }

  // read all rows
  for (let i in textArray) {
    const row = textArray[i];
    if (row) {
      // if row includes stack inputs
      if (row.includes("[")) {
        let singleStack = parseStackInputs(row.split());
        for (let i in singleStack) {
          if (singleStack[i] != " ") {
            stacks[i].push(singleStack[i]);
          }
        }
      } else if (row.includes("move")) {
        moves.push(parseMoveInput(row)); // remove non numeric inputs
      }
    }
  }
  stacks.map((i) => i.reverse());
  for (let i in moves) {
    moveLogic(moves[i], stacks);
  }

  // add last element from all stacks into a final...stack
  for (let i in stacks) {
    result.push(stacks[i][stacks[i].length-1])
  }
  return result.join("");
}

const input = co.textFileToArray("./dayFive.txt");
console.log(getLastStackItems(input, modifyStacksUsingPop));
console.log(getLastStackItems(input, modifyStacksUsingLoader));

