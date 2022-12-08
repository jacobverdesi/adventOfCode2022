const common = require("../common");

function getDirectorySizes(input) {
  let parentDir = null;
  let currentDir = null;
  let directories = {};
  directories["/"] = { parent: null, size: 0, children: [] };
  for (let line in input) {
    const lineItems = input[line].split(" ");
    if (lineItems[1] == "cd") {
      console.log(lineItems);

      if (lineItems[2] != "..") {
        if (lineItems[2] == "/") {
          currentDir = "/";
          parentDir = null;
        } else if (!directories.hasOwnProperty(lineItems[2])) {
          directories[lineItems[2]] = {
            parent: currentDir,
            size: 0,
            children: [],
          };
          parentDir = currentDir;
          currentDir = lineItems[2];
        } else {
          currentDir = lineItems[2];
          parentDir = directories[lineItems[2]]["parent"];
        }
      } else if (lineItems[2] == "..") {
        if (currentDir == "/") {
          currentDir = "/";
          parentDir = null;
        } else {
          currentDir = directories[currentDir]["parent"];
          parentDir = directories[currentDir]["parent"];
        }
      }
      console.log("current " + currentDir, "parent " + parentDir);
    } else if (lineItems[0] == "dir") {
      if (directories[currentDir].hasOwnProperty("children")) {
        directories[currentDir]["children"].push(lineItems[1]);
      } else {
        directories[currentDir]["children"] = [lineItems[1]];
      }
    } else if ((lineItems[0] != "$") & (lineItems[0] != "dir")) {
      let fileSize = parseInt(lineItems[0], 10);
      directories[currentDir]["size"] += fileSize;
      let parent = directories[currentDir]["parent"];
      while (parent != null) {
        directories[parent]["size"] += fileSize;
        parent = directories[parent]["parent"];
      }
    } else {
    }
  }
  return directories;
}

function upDateDirectorySize(directory, directories, visited) {
  let size = 0;
  if (directories[directory].hasOwnProperty("size")) {
    size += directories[directory]["size"];
  }
  if (directories[directory].hasOwnProperty("children")) {
    for (const subDir in directories[directory]["children"]) {
      child = directories[directory]["children"][subDir];
      if (!visited.has(child)) {
        size += upDateDirectorySize(child, directories, visited);
        visited.add(child);
      }
    }
  }
  directories[directory]["size"] = size;
  return size;
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

const input = common.textFileToArray("./daySeven.txt");

const directories = getDirectorySizes(input);

console.log(directories);
// upDateDirectorySize("/", directories, new Set());

// console.log(directories)

console.log(getSumOfSmallDirectories(directories, 100000));
