//Example:
//Hello Triangle

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
	 1.0f, 0.0f, 0.0f, 1.0f,
	 0.0f, 1.0f, 0.0f, 1.0f,
	 0.0f, 0.0f, 1.0f, 1.0f,
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
	}
)glsl";

int main() {
	//Create Window
	WindowDesc desc = {};
	desc.rect = RectI(0, 0, 800, 600);
	desc.title = L"Hello Renik";
	auto win = WindowMgr::Create(&desc);

	//Create a "Surface" for displaying the Graphic
	GraphicSurfaceData sData = {};
	sData.tgtGraphic = GraphicBackend::OPENGL;
	auto surface = GraphicMgr::CreateSurface(&sData);

	//Connect the Surface and Window to get the Graphic Handle
	auto gHandle = GraphicMgr::ConnectSurface(surface, win->get_handle());

	//Create Pointers of Data
	ArrayPtr<float> vertData = { vertices, sizeof(vertices), 3U };
	ArrayPtr<float> colorData = { colors, sizeof(colors), 4U };
	ArrayPtr<uint> idxData = { indicies, sizeof(indicies) };

	//Create Mesh and register the data
	Mesh mesh = Mesh();
	mesh.add_vertex("vert", &vertData);
	mesh.add_vertex("color", &colorData);
	mesh.set_index(&idxData);

	//Create a Material
	mesh.material = new Material();

	//Create a Shader
	auto shader = gHandle->CreateShader(vertexShader, fragmentShader);
	//Attach shader to Material to connect the Shader Input
	gHandle->AttachShaderToMaterial(shader, mesh.material);

	//Show The Window
	win->Show();
	while (true) {
		//Update and Draw
		win->Update();
		gHandle->BeginRender();
		gHandle->DrawMesh(&mesh, GraphicDrawMode::TRIANGLES);
		gHandle->EndRender();
		Sleep(1);
	}
	return 0;
}