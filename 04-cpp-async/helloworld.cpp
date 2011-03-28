#include <v8.h>
#include <node.h>

#include <unistd.h>

using namespace node;
using namespace v8;

#define REQ_FUN_ARG(I, VAR)                                             \
  if (args.Length() <= (I) || !args[I]->IsFunction())                   \
    return ThrowException(Exception::TypeError(                         \
                  String::New("Argument " #I " must be a function")));  \
  Local<Function> VAR = Local<Function>::Cast(args[I]);

class HelloWorld: ObjectWrap
{
public:

  static Persistent<FunctionTemplate> s_ct;
  static void Init(Handle<Object> target)
  {
    s_ct = Persistent<FunctionTemplate>::New(FunctionTemplate::New(New));
    s_ct->InstanceTemplate()->SetInternalFieldCount(1);
    s_ct->SetClassName(String::NewSymbol("HelloWorld"));

    NODE_SET_PROTOTYPE_METHOD(s_ct, "hi", Hello);

    target->Set(String::NewSymbol("HelloWorld"),
                s_ct->GetFunction());
  }

  // empty constructor
  HelloWorld()
  {
  }

  // empty destructor
  ~HelloWorld()
  {
  }

  static Handle<Value> New(const Arguments& args)
  {
    HelloWorld* hw = new HelloWorld();
    hw->Wrap(args.This());
    return args.This();
  }

  struct hello_baton_t {
    HelloWorld *hw;
    int sleep_for;
    Persistent<Function> cb;
  };

  static Handle<Value> Hello(const Arguments& args)
  {
    REQ_FUN_ARG(0, cb);

    HelloWorld* hw = ObjectWrap::Unwrap<HelloWorld>(args.This());

    hello_baton_t *baton = new hello_baton_t();
    baton->hw = hw;
	// sleep for x seconds
    baton->sleep_for = 5;
 	// reference to callback function
    baton->cb = Persistent<Function>::New(cb);

	// increase the reference count to the HelloWorld instance to not get gc
    hw->Ref();

    eio_custom(EIO_Hello, EIO_PRI_DEFAULT, EIO_AfterHello, baton);
    ev_ref(EV_DEFAULT_UC);

	// we return Undefined, since we want to do work in another thread.
    return Undefined();
  }

  // This callback will be ran inside a thread managed by libeio
  // When function returns, libeio will notify the main thread that it has code
  // to run on the main thread, at which point EIO_AfterHello will be ran in 
  // the main Node.js thread
  static int EIO_Hello(eio_req *req)
  {
	// extract the baton structure	
    hello_baton_t *baton = static_cast<hello_baton_t *>(req->data);

	// sleeping is safe, we are in a thread and do not block main thread
    sleep(baton->sleep_for);
    return 0;
  }

  
  static int EIO_AfterHello(eio_req *req)
  {
	
	// extract our baton structure
    hello_baton_t *baton = static_cast<hello_baton_t *>(req->data);

	// remove our reference to the event loop
    ev_unref(EV_DEFAULT_UC);

	// reduce the reference count to our HelloWorld object.
    baton->hw->Unref();

	// build up string to pass into the callback, stick it into an Args array
    Local<Value> argv[1];
    argv[0] = String::New("Hello World2");

	// call callback function with 1 param, checking for exc being thrown
    TryCatch try_catch;
    baton->cb->Call(Context::GetCurrent()->Global(), 1, argv);

    if (try_catch.HasCaught()) {
      FatalException(try_catch);
    }

	// we ran our callback, destroy the persistent reference
    baton->cb.Dispose();


    delete baton;
    return 0;
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
