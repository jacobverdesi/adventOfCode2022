const co = require("../common");

// get output score for 2nd player
function player2Score(playerOne, playerTwo) {
  if (playerOne == 1 && playerTwo == 3) {
    return 0; // player 2 loses when player 1 is rock and player 2 is scissors
  } else if ((playerTwo == 1 && playerOne == 3) || playerTwo > playerOne) {
    return 6; // player2 wins
  } else if (playerOne > playerTwo) {
    return 0; // player 2 loses
  }
  return 3; // or a tie
}

// get total score of 2nd Player
function getTotalScore(rpsRounds, scoreMap, roundOfPlay) {
  let score = 0;
  for (let i = 0; i < rpsRounds.length; i++) {
    const round = rpsRounds[i];
    const playerOneLetter = round.split(" ")[0];
    const playerOne = scoreMap[playerOneLetter];
    let playerTwo = 0;
    if (roundOfPlay == 1) {
      playerTwo = scoreMap[round.split(" ")[1]];
    } else {
      playerTwo = scoreMap[round.split(" ")[1]][playerOneLetter];
    }
    score += playerTwo;
    score += player2Score(playerOne, playerTwo);
  }
  return score;
}

// parse text inot rounds of play
const rpsRounds = co.textFileToArray("./dayTwo.txt");

// A, X = rock
// B, Y = paper
// C, Z = scissors
const scoreMap1 = { A: 1, B: 2, C: 3, X: 1, Y: 2, Z: 3 };=

console.log(getTotalScore(rpsRounds, scoreMap1, 1));

// A=rock, X=scissor, Y=rock, Z=paper
// B=paper, X=rock,Y=paper, Z=scissor
// C=scissor, X=paper, Y=scissor, Z=rock
const scoreMap2 = {
  A: 1,
  B: 2,
  C: 3,
  X: { A: 3, B: 1, C: 2 },
  Y: { A: 1, B: 2, C: 3 },
  Z: { A: 2, B: 3, C: 1 },
};
console.log(getTotalScore(rpsRounds, scoreMap2, 2));

