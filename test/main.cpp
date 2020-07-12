#define RENIK_STATIC
#define RENIK_INCLUDE_GRAPHIC_GL

#include <renik\renik.h>
#include <stdio.h>

using namespace renik;
using namespace renik::Window;
int main() {
	WindowDesc desc = {};
	desc.title = L"Renik Test";
	desc.rect = RectI(0, 0, 800, 600);
	auto win = WindowMgr::Create(&desc);
	win->Show();
	while (win->Update()) {
		Sleep(1);
	}
	return 0;
}