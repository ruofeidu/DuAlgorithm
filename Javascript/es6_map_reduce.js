// Map / Reduce comes from Google's well-known paper “MapReduce: Simplified Data Processing on Large Clusters”
// Map can abstract a series operations upon an array via functions. For example, in Javascript

function pow(x) {
return x * x;
}
var arr = [1, 2, 3, 4, 5, 6, 7, 8, 9];
arr.map(pow); // [1, 4, 9, 16, 25, 36, 49, 64, 81]
arr.map(String); // ['1', '2', '3', '4', '5', '6', '7', '8', '9']

// Reduce can conduct series of functions onto an array. [x1, x2, x3, x4].reduce(f) = f(f(f(x1, x2), x3), x4). For instance, to sum up an Array

var arr = [1, 3, 5, 7, 9];
arr.reduce(function (x, y) {
return x + y;
}); // 25
Instead of parseInt, here is another string2int

function string2int(s) {
return s.split()
 .map(function(x){ return x - '0';})
 .reduce(function(x, y){ return x*10+y; });
}

// Literally, filter is used to filter out some elements from an array. For instance, to keep only even numbers from an array:

var arr = [1, 2, 4, 5, 6, 9, 10, 15];
arr.filter(function (x) {
return x % 2 === 1;
}); // [1, 5, 9, 15]

// Sort
['Google', 'Apple', 'Microsoft'].sort(); // ['Apple', 'Google', 'Microsoft'];
['Google', 'apple', 'Microsoft'].sort(); // ['Google', 'Microsoft", 'apple']
[10, 20, 1, 2].sort(); // [1, 10, 2, 20]
var arr = [10, 20, 1, 2];
arr.sort(function (x, y) {
   if (x < y) {
	   return -1;
   }
   if (x > y) {
	   return 1;
   }
   return 0;
}); // [1, 2, 10, 20]


var arr = [10, 20, 1, 2];
arr.sort(function (x, y) {
   if (x < y) {
	   return 1;
   }
   if (x > y) {
	   return -1;
   }
   return 0;
}); // [20, 10, 2, 1]