typeof 123; // 'number'
typeof NaN; // 'number'
typeof 'str'; // 'string'
typeof true; // 'boolean'
typeof undefined; // 'undefined'
typeof Math.abs; // 'function'
typeof null; // 'object'
typeof []; // 'object'
typeof {}; // 'object'
  function Student(props) {
   this.name = props.name || 'Unnamed';
}
Student.prototype.hello = function () {
   alert('Hello, ' + this.name + '!');
}

var jon = new Student('Jon'); 
jon.name; // 'Jon' 
jon.hello(); // Hello, Jon!
//Here is how extend is realized in JavaScript:

function extends(Child, Parent) {
   var F = function () {};
   F.prototype = Parent.prototype;
   Child.prototype = new F();
   Child.prototype.constructor = Child;
}
function PrimaryStudent(props) {
   Student.call(this, props);
   this.grade = props.grade || 1;
}
extends(PrimaryStudent, Student);
PrimaryStudent.prototype.getGrade = function () {
   return this.grade;
};