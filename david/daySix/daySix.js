const common = require("../common");

// returns the character at the end of n unique characters 
function getEndOfPacket(text, numToFind) {
  for (let i = 0; i < text.length; i++) {
    try {
        let charToEval = new Set();
        for (let j = i; j < numToFind + i; j++) {
            charToEval.add(text[j])
        }
      if (charToEval.size > numToFind - 1) {
        return i + numToFind;
      }
    } catch (error) {
      concolse.log(error);
    }
  }
}

const text = common.textToString("./daySix.txt");

console.log(getEndOfPacket(text, 4));
console.log(getEndOfPacket(text, 14));