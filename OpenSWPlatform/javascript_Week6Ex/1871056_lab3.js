
function sort(list){
    let len = list.length;
    for (let i=0;i<len;i++) {
      for (let j = 0; j< len-i;j++) {
        if (j+1 < len && list[j] > list[j+1]) {
          let tmp = list[j];
          list[j] = list[j+1];
          list[j+1] = tmp;
        }
      }
    }
    return list;
}

console.log("sort([]) should return %O",sort([]));
console.log("sort([5]) should return %O",sort([5]));
console.log("sort([4, 1]) should return %O",sort([4, 1]));
console.log("sort([3, 2, 3]) should return %O",sort([3, 2, 3]));
console.log("sort([5, 3, 8, 9, 4, 1]) should return %O",sort([5, 3, 8, 9, 4, 1]));