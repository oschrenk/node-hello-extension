var
  util = require('util'),
  hello = require('../hello');

console.log(hello.foo());
console.log(util.inspect(hello, true, null));
