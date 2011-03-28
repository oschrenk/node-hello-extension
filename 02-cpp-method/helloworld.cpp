#include <v8.h>
#include <node.h>

using namespace node;
using namespace v8;

static Handle<Value> hi(const Arguments& args)
{
  return String::New("Hello World");
}

extern "C" {
  static void init(Handle<Object> target)
  {
    NODE_SET_METHOD(target, "hi", hi);
  }

  NODE_MODULE(helloworld, init);
}
