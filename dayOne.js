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


// function to return sum calories of top three calory carrying elves
function getElfCalories2(textArray) {
    let currentCalories = 0;
    let maxCalories = [0,0,0];
    for (let i=0; i< textArray.length; i++) {
        const item = textArray[i];
        if (item != '') {
            currentCalories += parseInt(item)
        } else {
            let min = Math.min(...maxCalories)
            if (currentCalories > min) {
                maxCalories.push(currentCalories)
                maxCalories = maxCalories.sort().filter((_,i) => i)
            }
            currentCalories = 0;
        }
    }
    return maxCalories.reduce((accumulator, value) => {
        return accumulator + value;
      }, 0);
}


// function to return elf calories and which elf is max calories
function getElfCalories(textArray) {
    let maxCalories = 0;
    let currentCalories = 0;
    for (let i=0; i< textArray.length; i++) {
        const item = textArray[i];
        if (item != '') {
            currentCalories += parseInt(item)
        } else {
            if (currentCalories > maxCalories) {
                maxCalories = currentCalories;
            }
            currentCalories = 0;
        }
    }
    return maxCalories;
}

const data =  textFileToArray('./dayOneInput.txt')

console.log(getElfCalories(data))
console.log(getElfCalories2(data))

