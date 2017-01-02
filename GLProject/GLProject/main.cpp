#include "stdafx.h"
#include "GLFramework.h"

using namespace std;

namespace {
	CGLFramework framework;
};

int main(int argc, char* argv[]) 
  {
	srand(unsigned(time(NULL)));

	// framework initialize
	framework.Initialize();

	// callback function set
	framework.SetReshapeFunc	([] (int w, int h) {framework.Reshape(w, h); });
	framework.SetDrawFunc		([] () {framework.drawScene(); });
	framework.SetTimerFunc		([] (int val) {framework.Timer(val); });
	framework.SetSpecialKeyUpFunc([](int key, int x, int y) {framework.SpecialKeyUp(key, x, y); });
	framework.SetSpecialKeyboardFunc([](int key, int x, int y) {framework.SpecialKeyboard(key, x, y); });
	framework.SetKeyboardFunc	([] (unsigned char key, int x, int y) {framework.Keyboard(key, x, y); });
	framework.SetMouseFunc		([] (int button, int state, int x, int y) {framework.Mouse(button, state, x, y); });

	// framework run
	framework.Run();

	return 0;
}
