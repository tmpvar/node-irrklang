#include <v8.h>
#include <node.h>
#include <dlfcn.h>
#include <iostream>

#define IRRKLANG_STATIC
#include <irrKlang.h>

using namespace node;
using namespace v8;
using namespace irrklang;
using namespace std;

class irrKlang: ObjectWrap
{
private:
  int m_count;
  ISoundEngine* engine;
public:
  
  static Persistent<FunctionTemplate> s_ct;
  static void Init(Handle<Object> target)
  {
    HandleScope scope;

    Local<FunctionTemplate> t = FunctionTemplate::New(New);

    s_ct = Persistent<FunctionTemplate>::New(t);
    s_ct->InstanceTemplate()->SetInternalFieldCount(1);
    s_ct->SetClassName(String::NewSymbol("irrKlang"));

    NODE_SET_PROTOTYPE_METHOD(s_ct, "play", Play);

    target->Set(String::NewSymbol("irrKlang"),
                s_ct->GetFunction());
  }

  irrKlang() :
    m_count(0)
  {

    // create the engine
    this->engine = createIrrKlangDevice();
    if (!this->engine) {
      cout << "BORKED";
    }
  }

  ~irrKlang()
  {
    this->engine->drop();
  }

  static Handle<Value> New(const Arguments& args)
  {
    HandleScope scope;
    irrKlang* hw = new irrKlang();
    hw->Wrap(args.This());
    return args.This();
  }

  static Handle<Value> Play(const Arguments& args)
  {
    HandleScope scope;
    String::AsciiValue filename(args[0]->ToString());
    irrKlang* hw = ObjectWrap::Unwrap<irrKlang>(args.This());
    ISound *clip = hw->engine->play2D(*filename, false, false, true);

    if (clip == NULL) {
      cout << "NO CLIP \n\n";
      return Undefined();
    }

    clip->setVolume(1);

    return args.This();
  }

};

Persistent<FunctionTemplate> irrKlang::s_ct;
extern "C" void init (Handle<Object> target) {
  void *handle = dlopen("libirrklang.dylib", RTLD_NOW | RTLD_GLOBAL);

  if (handle == NULL) {
    cout << "ERROR: " << dlerror() << "\n\n";
  }
  irrKlang::Init(target);
}
