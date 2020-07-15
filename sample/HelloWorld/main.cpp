#pragma comment (lib, "renik.lib")
#define RENIK_STATIC
#include <renik\renik.h>

using namespace renik;
using namespace renik::Window;
using namespace renik::Graphic;

int main() {
	WindowDesc desc = {};
	desc.rect = RectI(0, 0, 800, 600);
	desc.title = L"Hello Renik";
	auto win = WindowMgr::Create(&desc);

	GraphicSurfaceData sData = {};
	sData.tgtGraphic = GraphicBackend::OPENGL;

	auto surface = GraphicMgr::CreateSurface(&sData);
	auto gHandle = GraphicMgr::ConnectSurface(surface, win->get_handle());

	win->Show();
	while (true) {
		win->Update();
		gHandle->BeginRender();
		gHandle->ClearColor(Color(1.0f, 0.0f, 1.0f, 1.0f));
		gHandle->EndRender();
		Sleep(1);
	}
	return 0;
}