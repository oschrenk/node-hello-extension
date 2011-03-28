var util = require('util');
var helloworld = require('../helloworld');

var hello = new helloworld.HelloWorld();

console.log(hello.hi());
console.log(util.inspect(hello, true, null));