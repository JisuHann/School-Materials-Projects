
function factorial(num){
    let result = 1;
    for(let i=1;i<= num;i++){
        result = result * i;
    }
    return result;
}

console.log("factorial(0) returns %O", factorial(0));
console.log("factorial(1) returns %O",factorial(1));
console.log("factorial(2) returns %O",factorial(2));
console.log("factorial(3) returns %O",factorial(3));
console.log("factorial(4) returns %O",factorial(4));
console.log("factorial(9) returns %O",factorial(9));
