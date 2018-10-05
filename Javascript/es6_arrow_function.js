var fn = x => x * x;
fn = (x, y) => x * x + y * y; // two parameters
() => 3.14; // no parameter
// varying parameters
(x, y, ...rest) => {
   var i, sum = x + y;
   for (i=0; i<rest.length; i++) {
	   sum += rest[i];
   }
   return sum;
}
