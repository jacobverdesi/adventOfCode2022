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
        } else if (lineItems[2] != "..") {
          newDir = currentDir + lineItems[2] + "/";
          if (!directories.hasOwnProperty(newDir)) {
            directories[newDir] = {
              parent: currentDir,
              size: 0,
              children: [],
            };
          }
          currentDir = newDir;
        }
      } else {
        parentDir = directories[currentDir]["parent"];
        currentDir = parentDir;
      }
    } else if (lineItems[0] == "dir") {
      newDir = currentDir + lineItems[1] + "/";
      directories[currentDir]["children"].push(newDir);
      if (!directories.hasOwnProperty(newDir)) {
        directories[newDir] = {
          parent: currentDir,
          size: 0,
          children: [],
        };
      }
    } else if ((lineItems[0] != "$") & (lineItems[0] != "dir")) {
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

// find folders to delete
function freeSpace(totalSpace, spaceToFree, directories) {
  const totalUsedSpace = directories['/']["size"]
  const freeSpace = totalSpace - totalUsedSpace
  const limit = spaceToFree - freeSpace
  console.log(freeSpace)
  return getSmallestDirectoryToFree(directories, limit)
}

// return smallest amount to free
function getSmallestDirectoryToFree(directories, space) {
  let dirs = [];
  for (const directory in directories) {
    let size = directories[directory]["size"];
    if (size >= space) {
      dirs.push(size);
    }
  }
  console.log(dirs)
  return Math.min(...dirs);
}


const input = common.textFileToArray("./daySeven.txt");

const directories = getDirectorySizes(input);

updateDirSizes(directories, "/");

console.log(getSumOfSmallDirectories(directories, 100000));
console.log(freeSpace(70000000,30000000,directories))