var util = require('util');
var helloworld = require('../helloworld');

var hello = new helloworld.HelloWorld();
hello.hi(function(data){
  console.log("after");
});

console.log("before");