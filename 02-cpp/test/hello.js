var util = require('util');
var hello = require('../hello');

console.log(hello.foo());
console.log(util.inspect(hello, true, null));