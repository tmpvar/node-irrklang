#include <v8.h>
#include <irrKlang.h>
using namespace irrklang;
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

extern "C" void
init (Handle<Object> target)
{
  
  //Local<FunctionTemplate> play = FunctionTemplate::New(gl_glVertex2dv);
  //target->Set(String::New("glVertex2dv"), play->GetFunction());
  
  HandleScope scope;
  ISoundEngine* engine = createIrrKlangDevice();
  //if (!engine)
  //   return 0; // error starting up the engine
  engine->play2D("../../media/getout.ogg", true);
  engine->drop(); // delete engine
}