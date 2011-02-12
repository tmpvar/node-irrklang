#include <v8.h>
#include <node.h>
#include <irrKlang.h>

using namespace irrklang;
using namespace node;
using namespace v8;

/*
class irrKlang {
  pubic:
    static void
    Initialize (v8::Handle<v8::Object> target)
    {
      HandleScope scope;

      Local<FunctionTemplate> t = FunctionTemplate::New(New);
    }
};
/*

Handle<Value> play(const Arguments& args) {
  HandleScope scope;

   // play a single sound
   engine->play2D("../../media/bell.wav");

  return ThrowException(Exception::Error(
  String::New("glGetShaderInfoLog is not implemented!")));
}
*/

class Irrkl: ObjectWrap
{
private:
  int m_count;
public:

  static Persistent<FunctionTemplate> s_ct;
  static void Init(Handle<Object> target)
  {
    HandleScope scope;

    Local<FunctionTemplate> t = FunctionTemplate::New(New);

    s_ct = Persistent<FunctionTemplate>::New(t);
    s_ct->InstanceTemplate()->SetInternalFieldCount(1);
    s_ct->SetClassName(String::NewSymbol("Irrkl"));

    NODE_SET_PROTOTYPE_METHOD(s_ct, "bell", Bell);

    target->Set(String::NewSymbol("Irrkl"),
                s_ct->GetFunction());
  }

  Irrkl() :
    m_count(0)
  {
  }

  ~Irrkl()
  {
  }

  static Handle<Value> New(const Arguments& args)
  {
    HandleScope scope;
    Irrkl* hw = new Irrkl();
    hw->Wrap(args.This());
    return args.This();
  }

  static Handle<Value> Bell(const Arguments& args)
  {
    HandleScope scope;
    Irrkl* hw = ObjectWrap::Unwrap<Irrkl>(args.This());
    hw->m_count++;
    ISoundEngine* engine = createIrrKlangDevice();
    //if (!engine)
    //   return 0; // error starting up the engine
    engine->play2D("../../media/bell.wav", true);
    engine->drop(); // delete engine
    return scope.Close(engine);
  }

};

Persistent<FunctionTemplate> Irrkl::s_ct;

extern "C" {
  static void init (Handle<Object> target) {
  
    //Local<FunctionTemplate> play = FunctionTemplate::New(gl_glVertex2dv);
    //target->Set(String::New("glVertex2dv"), play->GetFunction());

    // HandleScope scope;
    Irrkl::Init(target);

  }
  
  NODE_MODULE(Irrkl, init);  
}
