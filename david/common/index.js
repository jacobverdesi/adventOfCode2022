const fs = require("fs");


// func to parse a txt file to an array
function textFileToArray(text) {
  try {
    const data = fs.readFileSync(text, "utf8");
    return data.split('\n');
  } catch (err) {
    console.log(err);
  }
}

module.exports = { textFileToArray };