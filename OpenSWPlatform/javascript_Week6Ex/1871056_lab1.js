
function factorial(num){
    if (num==0){
        return 1;
    }
    return num*factorial(num-1);
}

console.log(factorial(0));
console.log(factorial(1));
console.log(factorial(2));
console.log(factorial(3));
console.log(factorial(4));
console.log(factorial(9));