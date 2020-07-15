#pragma once
#ifndef RENIK_GRAPHIC_CPP_H
#define RENIK_GRAPHIC_CPP_H
#include <renik\cpp\common.h>

#define RENIK_IGRAPHIC(className) \
	class className : public IGraphic {\
	protected:\
		bool checkShaderProgram(Shader* shader) override;\
		bool checkShaderCompilation(Shader* shader) override;\
	public:\
		className(Surface* surface);\
		~className();\
		int get_GraphicType() override;\
		bool get_IsInitialized() override;\
		Surface* get_Surface() override;\
		std::vector<Shader> get_Shaders() override;\
		Shader* get_Shader(uint shaderID) override;\
		int Init() override;\
		int Release() override;\
		bool CheckFeature(int feature) override;\
		int EnableFeature(int feature) override;\
		int DisableFeature(int feature) override;\
		uint CreateFrameBuffer() override;\
		int DeleteFrameBuffer(uint handler) override;\
		int BindFrameBuffer(uint handler) override;\
		uint CreateRenderBuffer() override;\
		int DeleteRenderBuffer(uint handler) override;\
		int BindRenderBuffer(uint handler) override;\
		int BindMesh(Mesh* mesh) override;\
		int UnbindMesh(Mesh* mesh) override;\
		uint BindTexture(Texture* texture) override;\
		int UnbindTexture(uint handler) override;\
		int AttachMaterial(Material* material, Mesh* mesh) override;\
		int DestroyMaterial(Material* material) override;\
		Shader* CreateShader(const char* vertexShaderSrc, const char* fragmentShaderSrc) override;\
		int AttachShader(Shader* shader, Material* material)override;\
		int DestroyShader(Shader* shader)override;\
		int ApplyTransform(const Vec3F& pos, const Vec3F& rot, const Vec3F& scl) override;\
		int ApplyProjection(const SizeF& size, float nearClip, float farClip) override;\
		int DrawMesh(Mesh* mesh, int drawMode) override;\
		int DrawViewPort() override;\
		int DrawPoint(int drawMode) override;\
		int DrawLine(int drawMode) override;\
		int ClearColor(const Color& color) override;\
		int ClearDepth(const float& depth) override;\
		int ClearStencil(const int& stencil) override;\
		int BeginRender() override;\
		int EndRender() override;\
	};\

namespace renik {
	namespace Graphic {
		class IGraphic;
		typedef RENFUNC(gLogCallback, void, IGraphic*, std::string);

		//----GRAPHIC PARAMETER---
		enum class GraphicBackend {
			UNKNOWN = -1,
			DEFAULT,
			OPENGL,
			OPENGLES,
			D3D9,
			D3D11,
			D3D12,
			VULKAN,
		};
		enum class GraphicPixelFormat {
			UNKNOWN = -1,
			R1,
			A8,
			R8,
			R8I,
			R8U,
			R8S,
			R16,
			R16I,
			R16U,
			R16F,
			R16S,
			R32I,
			R32U,
			R32F,
			RG8,
			RG8I,
			RG8U,
			RG8S,
			RG16,
			RG16I,
			RG16U,
			RG16F,
			RG16S,
			RG32I,
			RG32U,
			RG32F,
			RGB8,
			RGB8I,
			RGB8U,
			RGB8S,
			RGB9E5F,
			BGRA8,
			RGBA8,
			RGBA8I,
			RGBA8U,
			RGBA8S,
			RGBA16,
			RGBA16I,
			RGBA16U,
			RGBA16F,
			RGBA16S,
			RGBA32I,
			RGBA32U,
			RGBA32F,
			R5G6B5,
			RGBA4,
			RGB5A1,
			RGB10A2,
			RG11B10F,
		};
		enum class GraphicTextureFormat {
			UNKNOWN = -1,
			DXT1,          //!< DXT1
			DXT3,          //!< DXT3
			DXT5,          //!< DXT5
			LATC1,         //!< LATC1/ATI1
			LATC2,         //!< LATC2/ATI2
			BC6H,          //!< BC6H
			BC7,           //!< BC7
			ETC1,          //!< ETC1 RGB8
			ETC2,          //!< ETC2 RGB8
			ETC2A,         //!< ETC2 RGBA8
			ETC2A1,        //!< ETC2 RGB8A1
			PTC12,         //!< PVRTC1 RGB 2BPP
			PTC14,         //!< PVRTC1 RGB 4BPP
			PTC12A,        //!< PVRTC1 RGBA 2BPP
			PTC14A,        //!< PVRTC1 RGBA 4BPP
			PTC22,         //!< PVRTC2 RGBA 2BPP
			PTC24,         //!< PVRTC2 RGBA 4BPP
			ATC,           //!< ATC RGB 4BPP
			ATCE,          //!< ATCE RGBA 8 BPP explicit alpha
			ATCI,          //!< ATCI RGBA 8 BPP interpolated alpha
			ASTC4x4,       //!< ASTC 4x4 8.0 BPP
			ASTC5x5,       //!< ASTC 5x5 5.12 BPP
			ASTC6x6,       //!< ASTC 6x6 3.56 BPP
			ASTC8x5,       //!< ASTC 8x5 3.20 BPP
			ASTC8x6,       //!< ASTC 8x6 2.67 BPP
			ASTC10x5,      //!< ASTC 10x5 2.56 BPP
		};
		enum class GraphicDepthFormat {
			UNKNOWN = -1,
			D16,
			D24,
			D24S8,
			D32,
			D16F,
			D24F,
			D32F,
			D0S8,
		};
		enum class GraphicPresentInterval {
			UNKNOWN = -1,
			DEFAULT,
			ONE,
			TWO,
			THREE,
			FOUR,
			IMMEDIATE
		};
		enum class GraphicDisplayOrientation {
			UNKNOWN = -1,
			DEFAULT,
			LANDSCAPELEFT,
			LANDSCAPERIGHT,
			PORTRAIT
		};
		enum class GraphicBufferHandlerType {
			VERTEXARRAY,
			VERTEXBUFFER,
			INDEXBUFFER,
			FRAMEBUFFER,
			RENDERBUFFER,
			CUSTOM
		};
		enum class GraphicShaderInputType {
			UNKNOWN = 0,
			FLOAT = sizeof(float),
			VEC2 = sizeof(Vec2F),
			VEC3 = sizeof(Vec3F),
			VEC4 = sizeof(Vec4F),
			MAT2X2 = VEC2 * 2 + 1,
			MAT3X3 = VEC3 * 3,
			MAT4X4 = VEC4 * 4
		};

		struct GraphicSurfaceData {
			//Surface Param
			GraphicBackend tgtGraphic;
			GraphicPixelFormat pixFormat;
			GraphicDepthFormat depthFmt;
			GraphicPresentInterval presentInterval;
			GraphicDisplayOrientation dispOrient;
			SizeI backBuffSize;
			int multiSampleCount;
			bool fullScreen;

			GraphicSurfaceData() {
				tgtGraphic = (GraphicBackend)0;
				pixFormat = (GraphicPixelFormat)0;
				depthFmt = (GraphicDepthFormat)0;
				presentInterval = (GraphicPresentInterval)0;
				dispOrient = (GraphicDisplayOrientation)0;
				multiSampleCount = 0;
				backBuffSize = SizeI();
				fullScreen = true;
			}
		};
		struct GraphicShaderInputData {
			GraphicShaderInputType type = GraphicShaderInputType::UNKNOWN;
			const char* name = nullptr;
		};

		//----GRAPHIC RESOURCE---
		struct Surface : public BaseObject<ulong, Surface> {
			GraphicSurfaceData param;
			void* winData;
			void* gInterface;
			RectI rect;
			Surface() {
				gInterface = nullptr;
				rect = RectI(0, 0, 0, 0);
			}
		};
		struct Shader : public BaseObject<ulong, Shader> {
			const char* name = nullptr;
			void* handleGL = nullptr;
			void* handleDX = nullptr;
			std::unordered_map<const char*, GraphicShaderInputType> input;
		};
		struct Material : public BaseObject<ulong, Shader> {
			Shader* material = nullptr;
		};
		struct Mesh : public BaseObject<ulong, Shader> {
			Material* material = nullptr;
			std::vector<Array<Vec3F>> data;
			bool isStatic = false;
		};
		struct Texture : public BaseObject<ulong, Shader> {
			SizeI size = SizeI();
		};

		//----GRAPHIC ABSTRACTION---
		class IGraphic {
		protected:
			bool m_initialized;
			void* m_gctx;
			Surface* m_surface;
			std::vector<Shader> m_libShader;

			virtual bool checkShaderProgram(Shader* shader) { return false; };
			virtual bool checkShaderCompilation(Shader* shader) { return false; };
		public:
			gLogCallback logCallback;

			IGraphic(Surface* surface) {}
			virtual ~IGraphic() {}

			//Property-Like Function
			virtual int get_GraphicType() { return -1; }
			virtual bool get_IsInitialized() { return m_initialized; }
			virtual Surface* get_Surface() { return m_surface; }
			virtual std::vector<Shader> get_Shaders() { return m_libShader; }
			virtual Shader* get_Shader(uint shaderID) {
				auto len = m_libShader.size();
				for (size_t i = 0; i < len; i++)
				{
					if (m_libShader[i].get_id() == shaderID)
						return &m_libShader[i];
				}
				return nullptr;
			}
			//Base Function
			virtual int Init() { return false; }
			virtual int Release() { return false; }
			//Backend Feature
			virtual bool CheckFeature(int feature) { return false; }
			virtual int EnableFeature(int feature) { return false; }
			virtual int DisableFeature(int feature) { return false; }
			//Frame Array
			virtual uint CreateFrameBuffer() { return 0U; }
			virtual int DeleteFrameBuffer(uint handler) { return false; }
			virtual int BindFrameBuffer(uint handler) { return false; }
			//Render Array
			virtual uint CreateRenderBuffer() { return 0U; }
			virtual int DeleteRenderBuffer(uint handler) { return false; }
			virtual int BindRenderBuffer(uint handler) { return false; }
			//Mesh Creation
			virtual int BindMesh(Mesh* mesh) { return false; }
			virtual int UnbindMesh(Mesh* mesh) { return false; }
			//Texture
			virtual uint BindTexture(Texture* texture) { return 0U; }
			virtual int UnbindTexture(uint handler) { return false; }
			//Material
			virtual int AttachMaterial(Material* material, Mesh* mesh) { return false; }
			virtual int DestroyMaterial(Material* material) { return false; }
			//Shader
			virtual Shader* CreateShader(const char* vertexShaderSrc, const char* fragmentShaderSrc) { return false; }
			virtual int AttachShader(Shader* shader, Material* material) { return false; }
			virtual int DestroyShader(Shader* shader) { return false; }
			//Transform
			virtual int ApplyTransform(const Vec3F& pos, const Vec3F& rot, const Vec3F& scl) { return false; }
			virtual int ApplyProjection(const SizeF& size, float nearClip, float farClip) { return false; }
			//Render
			virtual int DrawMesh(Mesh* mesh, int drawMode) { return false; }
			virtual int DrawViewPort() { return false; }
			virtual int DrawPoint(int drawMode) { return false; }
			virtual int DrawLine(int drawMode) { return false; }
			virtual int ClearColor(const Color& color) { return false; };
			virtual int ClearDepth(const float& depth) { return false; };
			virtual int ClearStencil(const int& stencil) { return false; };
			virtual int Clear(const Color& color, float depth, int stencil) {
				ClearColor(color);
				ClearDepth(depth);
				ClearStencil(stencil);
				return true;
			}
			virtual int BeginRender() { return false; }
			virtual int EndRender() { return false; }
		};

		namespace __internal__ {
		#ifdef RENIK_INCLUDE_GRAPHIC_GL
				//Generated Script for OpenGL Graphic
				RENIK_IGRAPHIC(IGraphic_OGL);
		#endif
		#ifdef RENIK_INCLUDE_GRAPHIC_GLES
				//Generated Script for OpenGL ES Graphic
				RENIK_IGRAPHIC(IGraphic_GLES);
		#endif
		#ifdef RENIK_INCLUDE_GRAPHIC_VULKAN
				//Generated Script for Vulkan Graphic
				RENIK_IGRAPHIC(IGraphic_VULKAN);
		#endif
		#ifdef RENIK_INCLUDE_GRAPHIC_DX9
				//Generated Script for DirectX 9 Graphic
				RENIK_IGRAPHIC(IGraphic_DX9);
		#endif
		#ifdef RENIK_INCLUDE_GRAPHIC_DX11
				//Generated Script for DirectX 11 Graphic
				RENIK_IGRAPHIC(IGraphic_DX11);
		#endif
		#ifdef RENIK_INCLUDE_GRAPHIC_DX12
				//Generated Script for DirectX 12 Graphic
				RENIK_IGRAPHIC(IGraphic_DX12);
		#endif
		}


		//----GRAPHIC MANAGER----
		class GraphicMgr final {
		public:
			static std::vector<Surface> surfaces;
			static std::vector<Mesh> meshes;
			static std::vector<Texture> textures;
			static std::vector<Material> materials;

			static Surface* CreateSurface(GraphicSurfaceData* surface);
			static IGraphic* ConnectSurface(Surface* surface, void* winPtr);
			static bool DestroySurface(Surface* surface);
		};
	}
}

#undef RENIK_IGRAPHIC

#endif