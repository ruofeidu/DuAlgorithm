// RegExp
// To create a new regular expression:

var re1 = /ABC\-001/;
var re2 = new RegExp('ABC\\-001');

// To test whether a regular expression matches a string:

var re = /^\d{3}\-\d{3,8}$/;
re.test('010-12345'); // true
re.test('010-1234x'); // false
re.test('010 12345'); // false
re1; // /ABC\-001/
re2; // /ABC\-001/

// To split a string using regular expression:

'a b   c'.split(' '); // ['a', 'b', , , 'c']
'a b   c'.split(/\s+/); // ['a', 'b', 'c']
'a,b;; c  d'.split(/[\s\,\;]+/); // ['a', 'b', 'c', 'd']

// By default, test only matches as many characters as possible. Global match via exec will match one by one.

var s = 'JavaScript, VBScript, JScript and ECMAScript';
var re=/[a-zA-Z]+Script/g; // is equivalent to re = new RegExp('test', 'g');
re.exec(s); // ['JavaScript']
re.lastIndex; // 10
re.exec(s); // ['VBScript']
re.lastIndex; // 20
re.exec(s); // ['JScript']
re.lastIndex; // 29
re.exec(s); // ['ECMAScript']
re.lastIndex; // 44
re.exec(s); // null