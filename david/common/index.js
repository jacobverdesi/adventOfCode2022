const fs = require("fs");


// func to parse a txt file to a string
function textFileToArray(text) {
  try {
    const data = fs.readFileSync(text, "utf8");
    return data.split('\n');
  } catch (err) {
    console.log(err);
  }
}

function textToString(text) {
  try {
    return fs.readFileSync(text, "utf8");
  } catch (err) {
    console.log(err);
  }
}

module.exports = { textFileToArray, textToString };