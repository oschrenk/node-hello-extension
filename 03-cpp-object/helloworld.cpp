#include <v8.h>
#include <node.h>

using namespace node;
using namespace v8;

class HelloWorld: ObjectWrap
{

public:

  static Persistent<FunctionTemplate> s_ct;
  static void Init(Handle<Object> target)
  {
    s_ct = Persistent<FunctionTemplate>::New(FunctionTemplate::New(New));
    s_ct->InstanceTemplate()->SetInternalFieldCount(1);
    s_ct->SetClassName(String::NewSymbol("HelloWorld"));

	// bind Hello method to hi
    NODE_SET_PROTOTYPE_METHOD(s_ct, "hi", Hello);

	// expose class as HelloWorld
    target->Set(String::NewSymbol("HelloWorld"), s_ct->GetFunction());
  }

  // empty constructor
  HelloWorld()
  {
  }

  // empty destructor
  ~HelloWorld()
  {
  }

  // equivalent to the constructor of java script version
  static Handle<Value> New(const Arguments& args)
  {
    HelloWorld* hw = new HelloWorld();
    hw->Wrap(args.This());
    return args.This();
  }

  static Handle<Value> Hello(const Arguments& args)
  {
    HandleScope scope;
    HelloWorld* hw = ObjectWrap::Unwrap<HelloWorld>(args.This());
    Local<String> result = String::New("Hello World");
    return scope.Close(result);
  }

};

Persistent<FunctionTemplate> HelloWorld::s_ct;

extern "C" {
  static void init (Handle<Object> target)
  {
    HelloWorld::Init(target);
  }

  NODE_MODULE(helloworld, init);
}