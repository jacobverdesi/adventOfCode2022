const common = require("../common");

// populate directory map
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
    } else if (lineItems[0] != "$" & lineItems[0] != "dir") {
      let fileSize = parseInt(lineItems[0], 10);
      directories[currentDir]["size"] += fileSize;
    }
  }
  return directories;
}

// recursive update of file sizes
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

// get all directories of specified sizes
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
