#include <v8.h>
#include <irrKlang.h>

using namespace irrklang;
using namespace v8;


Handle<Value> play(const Arguments& args) {
  HandleScope scope;

   // play a single sound
   engine->play2D("../../media/bell.wav");

  return ThrowException(Exception::Error(
  String::New("glGetShaderInfoLog is not implemented!")));
}


extern "C" void
init (Handle<Object> target)
{
  
  Local<FunctionTemplate> play = FunctionTemplate::New(gl_glVertex2dv);
  target->Set(String::New("glVertex2dv"), play->GetFunction());
  
  HandleScope scope;
  ISoundEngine* engine = createIrrKlangDevice();

  if (!engine)
     return 0; // error starting up the engine

  engine->play2D("../../media/getout.ogg", true);
  std::cout << "\nHello World!\n";

  char i = 0;

  while(i != 'q')
  {
     std::cout << "Press any key to play some sound, press 'q' to quit.\n";

		

     std::cin >> i; // wait for user to press some key
  }
  engine->drop(); // delete engine
  return 0;
  
}