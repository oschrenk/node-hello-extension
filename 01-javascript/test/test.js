var util = require('util');
var hw = require('../helloworld');
var helloworld = new hw.HelloWorld();

console.log(helloworld.hi());
console.log(util.inspect(helloworld, true, null));