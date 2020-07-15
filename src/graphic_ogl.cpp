#include <renik\cpp\graphic.h>
#include <renik\cpp\window.h>

#ifdef RENIK_GL
#define GLEW_STATIC
#include <GLEW\glew.h>
#include <GLEW\wglew.h>
#include "utility.h"

namespace renik {
	namespace Graphic {
		namespace __internal__ {
			inline bool __checkShaderCompilation(uint shaderHandler, int type) {
				int res;
				int InfoLogLength;

				glGetShaderiv(shaderHandler, GL_COMPILE_STATUS, &res);
				glGetShaderiv(shaderHandler, GL_INFO_LOG_LENGTH, &InfoLogLength);
				if (InfoLogLength > 0) {
					std::vector<char> ErrorMessage(InfoLogLength + 1);
					glGetShaderInfoLog(shaderHandler, InfoLogLength, NULL, &ErrorMessage[0]);
					RENIK_GPrintLog((int)GraphicBackend::OPENGL, -1, "Failed to Compile %s Shader: %s", type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT", &ErrorMessage[0]);
					return false;
				}
				RENIK_GPrintLog((int)GraphicBackend::OPENGL, 0, "%s Shader Compiled!", type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT");
				return true;
			}
			inline bool __checkShaderInfo(uint programHandler, uint statusMode, gLogCallback callback) {
				GLint res;
				glGetProgramiv(programHandler, statusMode, &res);
				if (res != GL_TRUE) {
					int log_length = 1024;
					GLchar message[1024];
					glGetProgramInfoLog(programHandler, 1024, &log_length, message);
					RENIK_GPrintLog((int)GraphicBackend::OPENGL, -1, "Failed to %s Shader: %s", statusMode == GL_LINK_STATUS ? "LINK" : "VALIDATE", message);
					glDeleteProgram(programHandler);
					return false;
				}
				RENIK_GPrintLog((int)GraphicBackend::OPENGL, 0, "Shader %s !", statusMode == GL_LINK_STATUS ? "LINKED" : "VALIDATED");
				return true;
			}
			inline GraphicShaderInputType __getShaderInputDataType(uint code) {
				switch (code) {
				case GL_FLOAT:			return GraphicShaderInputType::FLOAT;
				case GL_FLOAT_VEC2:		return GraphicShaderInputType::VEC2;
				case GL_FLOAT_VEC3:		return GraphicShaderInputType::VEC3;
				case GL_FLOAT_VEC4:		return GraphicShaderInputType::VEC4;
				case GL_FLOAT_MAT2:		return GraphicShaderInputType::MAT2X2;
				case GL_FLOAT_MAT3:		return GraphicShaderInputType::MAT3X3;
				case GL_FLOAT_MAT4:		return GraphicShaderInputType::MAT4X4;
				}
				return GraphicShaderInputType::UNKNOWN;
			}

			IGraphic_OGL::IGraphic_OGL(Surface* surface) : IGraphic::IGraphic(surface) { 
				if (surface != nullptr)
					this->m_surface = surface;
			}
			IGraphic_OGL::~IGraphic_OGL() {
				m_libShader.clear();
				m_gctx = nullptr;
				m_surface = nullptr;
			}

			int IGraphic_OGL::get_GraphicType() { return (int)GraphicBackend::OPENGL; }
			bool IGraphic_OGL::get_IsInitialized() { return IGraphic::get_IsInitialized(); }
			Surface* IGraphic_OGL::get_Surface() { return IGraphic::get_Surface(); }
			std::vector<Shader> IGraphic_OGL::get_Shaders() { return IGraphic::get_Shaders(); }
			Shader* IGraphic_OGL::get_Shader(uint shaderID) { return IGraphic::get_Shader(shaderID); }

			int IGraphic_OGL::Init() {
				m_initialized = false;
				PIXELFORMATDESCRIPTOR pDesc = {
					sizeof(PIXELFORMATDESCRIPTOR),
					1,
					PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
					PFD_TYPE_RGBA,	      // The kind of framebuffer. RGBA or palette.
					32,					  // Colordepth of the framebuffer.
					0, 0, 0, 0, 0, 0,
					0,
					0,
					0,
					0, 0, 0, 0,
					24,                   // Number of bits for the depthbuffer
					8,                    // Number of bits for the stencilbuffer
					0,                    // Number of Aux buffers in the framebuffer. (NOT SUPPORTED,,,, WTF?)
					0,				      // Not Supported
					0,					  // Not Supported
					0, 0, 0				  // Not Supported
				};
				Window::WinHandle* winSurface = (Window::WinHandle*)m_surface->winData;

				int pixFmt = ChoosePixelFormat((HDC)winSurface->hwndDC, &pDesc);
				if (!pixFmt) {
					if (logCallback)
						logCallback((IGraphic*)this, Util::Concat("Failed to Choose Pixel Format: %S", Util::LastSysErr()));
					return false;
				}
				SetPixelFormat((HDC)winSurface->hwndDC, pixFmt, &pDesc);
				this->m_gctx = wglCreateContext((HDC)winSurface->hwndDC);
				if (!this->m_gctx) {
					if (logCallback)
						logCallback((IGraphic*)this, Util::Concat("Failed to create Context: %S", Util::LastSysErr()));
					return false;
				}
				wglMakeCurrent((HDC)winSurface->hwndDC, (HGLRC)this->m_gctx);

				if (glewInit() != GLEW_OK) {
					if (logCallback)
						logCallback((IGraphic*)this, Util::Concat("Failed to initializing GLEW: %S", Util::LastSysErr()));
					return false;
				}

				//Initializing Some Handler
				/*glGetIntegerv(GL_FRAMEBUFFER_BINDING, &__frameBuff);
				glGenVertexArrays(1, &__vao);*/
				//__tryDEBUG("glGenVertexArrays: %s");

				m_surface->gInterface = this;
				m_initialized = true;
				m_surface->gInterface = this;


				m_initialized = true;
			}
			int IGraphic_OGL::Release() { 
				m_initialized = false;
				m_surface->gInterface = nullptr;
				return true;
			}
			
			bool IGraphic_OGL::CheckFeature(int feature) { 
				return glIsEnabled((GLenum)feature);
			}
			int IGraphic_OGL::EnableFeature(int feature) {
				glEnable((GLenum)feature);
				return true;
			}
			int IGraphic_OGL::DisableFeature(int feature) { 
				glDisable((GLenum)feature);
				return true;
			}
			
			uint IGraphic_OGL::CreateFrameBuffer() {
				return 0U;
			}
			int IGraphic_OGL::DeleteFrameBuffer(uint handler) { 
				return 0;
			}
			int IGraphic_OGL::BindFrameBuffer(uint handler) {
				return 0;
			}
			
			uint IGraphic_OGL::CreateRenderBuffer() { 
				return 0U;
			}
			int IGraphic_OGL::DeleteRenderBuffer(uint handler) {
				return 0;
			}
			int IGraphic_OGL::BindRenderBuffer(uint handler) { 
				return 0;
			}
			
			int IGraphic_OGL::BindMesh(Mesh* mesh) { 
				return false;
			}
			int IGraphic_OGL::UnbindMesh(Mesh* mesh) { 
				return false;
			}
			
			uint IGraphic_OGL::BindTexture(Texture* tex) {
				return false;
			}
			int IGraphic_OGL::UnbindTexture(uint handler) {
				return false;
			}

			int IGraphic_OGL::AttachMaterial(Material* material, Mesh* mesh) {
				return false;
			}
			int IGraphic_OGL::DestroyMaterial(Material* material) { 
				return false;
			}
			
			Shader* IGraphic_OGL::CreateShader(const char* vertexShaderSrc, const char* fragmentShaderSrc) { 
				if (vertexShaderSrc == nullptr || fragmentShaderSrc == nullptr) {
					return false;
				}
				//Compile Vertex Shader
				auto vHandle = glCreateShader(GL_VERTEX_SHADER);
				glShaderSource(vHandle, 1, &vertexShaderSrc, NULL);
				glCompileShader(vHandle);
				if (!__checkShaderCompilation(vHandle, GL_VERTEX_SHADER))
					return false;

				//Compile Fragment Shader
				auto fHandle = glCreateShader(GL_FRAGMENT_SHADER);
				glShaderSource(fHandle, 1, &fragmentShaderSrc, NULL);
				glCompileShader(fHandle);
				if (!__checkShaderCompilation(fHandle, GL_FRAGMENT_SHADER))
					return false;

				//Linking Program
				auto shaderHandler = glCreateProgram();
				glAttachShader(shaderHandler, vHandle);
				glAttachShader(shaderHandler, fHandle);
				glLinkProgram(shaderHandler);
				if (!__checkShaderInfo(shaderHandler, GL_LINK_STATUS))
					return false;

				//Validating Program
				glValidateProgram(shaderHandler);
				if (!__checkShaderInfo(shaderHandler, GL_VALIDATE_STATUS))
					return false;

				glDetachShader(shaderHandler, vHandle);
				glDetachShader(shaderHandler, fHandle);

				glDeleteShader(vHandle);
				glDeleteShader(fHandle);

				Shader newShader = Shader();
				newShader.handleGL = (void*)shaderHandler;
				newShader.input = std::unordered_map<const char*, GraphicShaderInputType>();

				int maxlength = 0;
				int count = 0;

				//Get Exposed Attributes
				glGetProgramiv(shaderHandler, GL_ACTIVE_ATTRIBUTES, &count);
				glGetProgramiv(shaderHandler, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxlength);
				std::vector<char> buffer(maxlength);
				for (int i = 0; i < count; i++) {
					int size = 0;
					int len = 0;
					uint type = 0;
					glGetActiveAttrib(shaderHandler, 0, buffer.size(), &len, &size, &type, &buffer[0]);
					std::string name((char*)&buffer[0], len);
					newShader.input[name.c_str()] = __getShaderInputDataType(type);
				}

				//Get Exposed Uniform
				glGetProgramiv(shaderHandler, GL_ACTIVE_UNIFORMS, &count);
				buffer = std::vector<char>(256);
				for (int i = 0; i < count; i++) {
					int size = 0;
					int len = 0;
					uint type = 0;
					glGetActiveUniform(shaderHandler, count, 256, &len, &size, &type, &buffer[0]);
					std::string name((char*)&buffer[0], len - 1);
					newShader.input[name.c_str()] = __getShaderInputDataType(type);
				}

				m_libShader.push_back(newShader);
				return &m_libShader[m_libShader.size() - 1];

				return nullptr;
			}
			int IGraphic_OGL::AttachShader(Shader* shader, Material* material){ 
				return false;
			}
			int IGraphic_OGL::DestroyShader(Shader* shader){
				return false;
			}
			
			int IGraphic_OGL::ApplyTransform(const Vec3F& pos, const Vec3F& rot, const Vec3F& scl) {
				return false;
			} 
			int IGraphic_OGL::ApplyProjection(const SizeF& size, float nearClip, float farClip) {
				return false;
			} 
			
			int IGraphic_OGL::DrawMesh(Mesh* mesh, int drawMode) {
				return false;
			} 
			int IGraphic_OGL::DrawViewPort() { 
				return false;
			} 
			int IGraphic_OGL::DrawPoint(int drawMode) {
				return false;
			} 
			int IGraphic_OGL::DrawLine(int drawMode) {
				return false;
			} 
			
			int IGraphic_OGL::ClearColor(const Color& color) {
				glClearColor(color.r, color.g, color.b, color.a);
				return false;
			} 
			int IGraphic_OGL::ClearDepth(const float& depth) { 
				glClearDepthf(depth);
				return false;
			} 
			int IGraphic_OGL::ClearStencil(const int& stencil) { 
				glClearStencil(stencil);
				return false;
			} 
			
			int IGraphic_OGL::BeginRender() { 
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				return true;
			} 
			int IGraphic_OGL::EndRender() {
				SwapBuffers((HDC)((Window::WinHandle*)m_surface->winData)->hwndDC);
				return true;
			} 
		}
	}
}
#endif