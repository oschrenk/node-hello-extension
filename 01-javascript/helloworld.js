HelloWorld = function() {
};

HelloWorld.prototype.hi = function()
{
  return "Hello World";
};

// expose the constructor
exports.HelloWorld = HelloWorld;