var util = require('util');
var helloworld = require('../helloworld');

console.log(helloworld.hi());
console.log(util.inspect(helloworld, true, null));