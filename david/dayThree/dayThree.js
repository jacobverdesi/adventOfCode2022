const co = require("../common");

// get single item in both compartments of rucksack
function getCommonItemQuestionOne(rucksack) {
  const middle = Math.floor(rucksack.length / 2);
  const firstHalf = rucksack.substr(0, middle);
  const secondHalf = rucksack.substr(middle);
  for (let i in firstHalf) {
    if (secondHalf.includes(firstHalf[i])) {
      return firstHalf[i];
    }
  }
  return null;
}

// get a dictionary of alphabet characters
function getAlphabetDictionary() {
  const alpha = Array.from(Array(26)).map((e, i) => i + 65);
  const alphabet = alpha.map((x) => String.fromCharCode(x));
  let alphaDictionary = {};
  for (let i = 0; i < alphabet.length; i++) {
    alphaDictionary[alphabet[i].toLowerCase()] = i + 1;
    alphaDictionary[alphabet[i]] = i + 27;
  }
  return alphaDictionary;
}

// get the sum of the common items in the rucksack
function getSumCommonItemsQuestionOne(rucksacks) {
  let result = 0;
  const alphaDictionary = getAlphabetDictionary();
  for (let i = 0; i < rucksacks.length; i++) {
    const item = getCommonItemQuestionOne(rucksacks[i]);
    if (item) {
      result += alphaDictionary[item];
    }
  }
  return result;
}

// returns the single common item between the three rucksacks
function getCommonItemQuestionTwo(rucksacks) {
  if (rucksacks.length != 3) {
    throw new Error("three rucksacks are required");
  }
  const firstItem = rucksacks[0];
  const secondItem = rucksacks[1];
  const thirdItem = rucksacks[2];
  let commonItems = [];
  for (let i in secondItem) {
    if (firstItem.includes(secondItem[i])) {
      commonItems.push(secondItem[i]);
    }
  }
  for (let i in thirdItem) {
    if (commonItems.includes(thirdItem[i])) {
      return thirdItem[i];
    }
  }
  return null;
}

// adds the sum of all the common item between pairs of three rucksacks
function getSumCommonItemsQuestionTwo(rucksacks) {
  let threeRucksacks = [];
  let result = 0;
  const alphaDictionary = getAlphabetDictionary();
  for (let i = 0; i < rucksacks.length; i++) {
    if (threeRucksacks.length != 3) {
      threeRucksacks.push(rucksacks[i]);
    } else {
      const number = alphaDictionary[getCommonItemQuestionTwo(threeRucksacks)];
      result += number;
      threeRucksacks = [];
      threeRucksacks.push(rucksacks[i])
    }
  }
  result += alphaDictionary[getCommonItemQuestionTwo(threeRucksacks)];
  return result;
}

const rucksacks = co.textFileToArray("./dayThree.txt");

console.log(getSumCommonItemsQuestionOne(rucksacks));
console.log(getSumCommonItemsQuestionTwo(rucksacks));
