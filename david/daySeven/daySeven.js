const common = require("../common");

function getDirectorySizes(input) {
  let directories = {};
  directories["/"] = { parent: null, size: 0, children: [] };
  let currentDir = "/";
  for (let line in input) {
    const lineItems = input[line].split(" ");
    if (lineItems[1] == "cd") {
      if (lineItems[2] != "..") {
        if (lineItems[2] == "/") {
          currentDir = "/";
        }
        if (!directories.hasOwnProperty(lineItems[2])) {
          directories[lineItems[2]] = {
            parent: currentDir,
            size: 0,
            children: [],
          };
        } 
        currentDir = lineItems[2];
      } else if (lineItems[2] == "..") {
        parentDir = directories[currentDir]["parent"];
        currentDir = parentDir
      }
    } else if (lineItems[0] == "dir") {
      directories[currentDir]["children"].push(lineItems[1]);
      if (!directories.hasOwnProperty(lineItems[1])) {
        directories[lineItems[1]] = {
          parent: currentDir,
          size: 0,
          children: [],
        };
      }
    } else if (lineItems[0] != "$") {
      let fileSize = parseInt(lineItems[0], 10);
      directories[currentDir]["size"] += fileSize;
    }
  }
  return directories;
}

function updateDirSizes(directories, root) {
  let children = directories[root]["children"];
  if (children.length < 1) {
    return directories[root]["size"];
  }
  for (let i in children) {
    directories[root]["size"] += updateDirSizes(directories, children[i]);
  }
  return directories[root]["size"];
}

function getSumOfSmallDirectories(directories, limit) {
  let sum = 0;
  for (const directory in directories) {
    let size = directories[directory]["size"];
    if (size <= limit) {
      sum += size;
    }
  }
  return sum;
}

const input = common.textFileToArray("./sample.txt");

const directories = getDirectorySizes(input);
// console.log(directories);
updateDirSizes(directories, "/");
console.log(directories)
console.log(getSumOfSmallDirectories(directories, 100000));
