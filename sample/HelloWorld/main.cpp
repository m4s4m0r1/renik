#pragma comment (lib, "renik.lib")
#define RENIK_STATIC
#include <renik\renik.h>

using namespace renik;
using namespace renik::Window;
using namespace renik::Graphic;

float vertices[] = {
	 0.0f,  0.5f, 0.0f, 
	 0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f,
};

float colors[] = {
	 1.0f, 0.0f, 0.0f, 1.0f, // Vertex 1: Red
	 0.0f, 1.0f, 0.0f, 1.0f, // Vertex 2: Green
	 0.0f, 0.0f, 1.0f, 1.0f,// Vertex 3: Blue
};

unsigned int indicies[] = {
	0, 1, 2
};

const char* vertexShader = R"glsl(
	#version 150 core
	in vec4 color;
	in vec3 vert;

	out vec4 Color;
	void main() {
		Color = color;
		gl_Position = vec4(vert, 1.0);
	}
)glsl";

const char* fragmentShader = R"glsl(
	#version 150 core
	in vec4 Color;

	out vec4 outColor;
	void main() {
		outColor = vec4(Color);
		//outColor = vec4(1.0, 1.0, 1.0, 1.0);
	}
)glsl";

void DebugGLog(int code, int graphic, std::string str) {
	printf("%s \n",str.c_str());
}

int main() {
	WindowDesc desc = {};
	desc.rect = RectI(0, 0, 800, 600);
	desc.title = L"Hello Renik";
	auto win = WindowMgr::Create(&desc);

	GraphicSurfaceData sData = {};
	sData.tgtGraphic = GraphicBackend::OPENGL;

	auto surface = GraphicMgr::CreateSurface(&sData);
	auto gHandle = GraphicMgr::ConnectSurface(surface, win->get_handle());
	gHandle->logCallback = DebugGLog;

	ArrayPtr<float> vertData = { vertices, sizeof(vertices), 3U };
	ArrayPtr<uint> idxData = { indicies, sizeof(indicies) };
	ArrayPtr<float> colorData = { colors, sizeof(colors), 4U};

	Mesh mesh = Mesh();
	mesh.add_vertex("vert", &vertData);
	mesh.add_vertex("color", &colorData);
	mesh.set_index(&idxData);
	mesh.material = new Material();

	auto shader = gHandle->CreateShader(vertexShader, fragmentShader);
	gHandle->AttachShaderToMaterial(shader, mesh.material);

	win->Show();
	while (true) {
		win->Update();
		gHandle->BeginRender();
		gHandle->DrawMesh(&mesh, GraphicDrawMode::TRIANGLES);
		gHandle->EndRender();
		Sleep(1);
	}
	return 0;
}