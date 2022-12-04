const co = require("../common")


// return 1 if one set of tasks is completely encompassed by another
function getOverlapppingTasksQuestionOne(tasks1, tasks2) {
  let lower = Infinity
  let upper = 0
  const firstTaskLower = tasks1[0]
  const firstTaskUpper = tasks1[1]
  const secondTaskLower = tasks2[0]
  const secondTaskUpper = tasks2[1]
  if (firstTaskLower <= lower) {
    lower = firstTaskLower
  }
  if (secondTaskLower <= lower) {
    lower = secondTaskLower
  }
  if (firstTaskUpper >= upper) {
    upper = firstTaskUpper
  }
  if (secondTaskUpper >= upper) {
    upper = secondTaskUpper
  }
  if ((firstTaskLower == lower && firstTaskUpper == upper)
    || (secondTaskLower == lower && secondTaskUpper == upper)) {
    return 1
  }
  return 0;
}


// return 1 if the two sets of tasks intersect
function getOverlapppingTasksQuestionTwo(tasks1, tasks2) {
  const firstTaskLower = tasks1[0]
  const firstTaskUpper = tasks1[1]
  const secondTaskLower = tasks2[0]
  const secondTaskUpper = tasks2[1]
  if ((firstTaskLower >= secondTaskLower && firstTaskLower <= secondTaskUpper)
    || (secondTaskLower >= firstTaskLower && secondTaskLower <= firstTaskUpper)) {
    return 1
  }
  return 0;
}

function getOverlappingTasks(tasks, questionOne) {
  result = 0;
  for (let i = 0; i < tasks.length; i++) {
    if (tasks[i]) {
      const task1 = tasks[i].split(',')[0].split('-').map((x) => parseInt(x, 10))
      const task2 = tasks[i].split(',')[1].split('-').map((x) => parseInt(x, 10))
      if (questionOne) {
        result += getOverlapppingTasksQuestionOne(task1, task2)
      } else {
        result += getOverlapppingTasksQuestionTwo(task1, task2)
      }
    }
  }
  return result
}

const tasks = co.textFileToArray('./dayFour.txt')

console.log(getOverlappingTasks(tasks, true))
console.log(getOverlappingTasks(tasks, false))
