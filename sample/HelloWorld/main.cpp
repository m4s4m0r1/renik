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
	 1.0f, 0.0f, 0.0f, // Vertex 1: Red
	 0.0f, 1.0f, 0.0f, // Vertex 2: Green
	 0.0f, 0.0f, 1.0f, // Vertex 3: Blue
};

float colors2[] = {
	 1.0f, 1.0f, 0.0f, // Vertex 1: Red
	 1.0f, 0.0f, 1.0f, // Vertex 2: Green
	 1.0f, 1.0f, 1.0f, // Vertex 3: Blue
};

unsigned int indicies[] = {
	0, 1, 2
};

const char* vertexShader = R"glsl(
	#version 150 core
	in vec3 vert;
	in vec3 color;

	out vec3 Color;
	void main() {
		Color = color;
		gl_Position = vec4(vert, 1.0);
	}
)glsl";

const char* fragmentShader = R"glsl(
	#version 150 core
	in vec3 Color;

	out vec4 outColor;
	void main() {
		outColor = vec4(Color, 1.0);
		//outColor = vec4(1.0, 1.0, 1.0, 1.0);
	}
)glsl";

void DebugGLog(IGraphic* gPtr, std::string str) {
	printf(str.c_str());
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

	Array<float> vertData = { vertices, sizeof(vertices), 3U };
	Array<uint> idxData = { indicies, sizeof(indicies) };
	//Array<float> colorData = { colors, sizeof(colors), 3U};
	Array<float> colorData2 = { colors2, sizeof(colors2), 3U };

	//auto mesh = GraphicMgr::CreateMesh(vertData, idxData);
	/*Mesh mesh = Mesh();
	mesh.vertex["vert"] = vertData;
	mesh.vertex["color"] = colorData;
	mesh.index = idxData;*/

	//auto mesh2 = GraphicMgr::CreateMesh(vertData, idxData);
	Mesh mesh2 = Mesh();
	mesh2.vertex["vert"] = vertData;
	mesh2.vertex["color"] = colorData2;
	mesh2.index = idxData;

	auto material = GraphicMgr::CreateMaterial();
	auto shader = gHandle->CreateShader(vertexShader, fragmentShader);
	gHandle->AttachShader(shader, material);

	//gHandle->AttachMaterial(material, &mesh);
	gHandle->AttachMaterial(material, &mesh2);

	win->Show();
	while (true) {
		win->Update();
		gHandle->BeginRender();
		//gHandle->DrawMesh(&mesh, GraphicDrawMode::TRIANGLES);
		gHandle->DrawMesh(&mesh2, GraphicDrawMode::TRIANGLES);
		gHandle->EndRender();
		Sleep(1);
	}
	return 0;
}