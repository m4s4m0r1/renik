#include <renik\cpp\graphic.h>

namespace renik {
	namespace Graphic {
		inline IGraphic* __createGraphicInterface(Surface* surface) {
			switch ((GraphicBackend)surface->param.tgtGraphic) {
#if RENIK_GL
			case GraphicBackend::OPENGL:
				return new __internal__::IGraphic_OGL(surface);
#endif
#if RENIK_GLES
			case GraphicBackend::OPENGLES:
				return new __internal__::IGraphic_GLES(surface);
#endif
#if RENIK_DX9
			case GraphicBackend::D3D9:
				return new __internal__::IGraphic_DX9(surface);
#endif
#if RENIK_DX11
			case GraphicBackend::D3D11:
				return new __internal__::IGraphic_DX11(surface);
#endif
#if RENIK_VULKAN
			case GraphicBackend::VULKAN:
				return new __internal__::IGraphic_VULKAN(surface); */
#endif
			default:
				return nullptr;
			}
		}

		std::vector<Surface> GraphicMgr::surfaces = std::vector<Surface>();
		std::vector<Mesh> GraphicMgr::meshes = std::vector<Mesh>();
		std::vector<Texture> GraphicMgr::textures = std::vector<Texture>();
		std::vector<Material> GraphicMgr::materials = std::vector<Material>();

		Surface* GraphicMgr::CreateSurface(GraphicSurfaceData* surface) {
			if (surface == nullptr)
				return nullptr;
			Surface newSurface = Surface();
			newSurface.param = *surface;
			surfaces.push_back(newSurface);
			return &surfaces[surfaces.size() - 1];
		}
		IGraphic* GraphicMgr::ConnectSurface(Surface* surface, void* winPtr) {
			if (surface == nullptr || winPtr == nullptr)
				return nullptr;

			surface->winData = winPtr;
			auto gInterface = __createGraphicInterface(surface);
			if (gInterface->Init()) {
				return (IGraphic*)surface->gInterface;
			}
			surface->winData = nullptr;
			return nullptr;
		}
		bool GraphicMgr::DestroySurface(Surface* surface) {
			if (surface == nullptr)
				return false;
		}
	}
}