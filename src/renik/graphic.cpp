#ifdef RENIK_ENABLE
#include <renik\cpp\graphic.h>

namespace renik {
	namespace Graphic {
		std::vector<IGraphic*> GraphicMgr::gInterfaces = std::vector<IGraphic*>();
		std::vector<Surface> GraphicMgr::surfaces = std::vector<Surface>();
		std::vector<Mesh> GraphicMgr::meshes = std::vector<Mesh>();
		std::vector<Texture> GraphicMgr::textures = std::vector<Texture>();
		std::vector<Material> GraphicMgr::materials = std::vector<Material>();

		Surface* GraphicMgr::CreateSurface(GraphicSurfaceData* surface) {
			if (surface == nullptr)
				return nullptr;

		}
		IGraphic* GraphicMgr::InitSurface(Surface* surface, void* winPtr) {
			if (surface == nullptr)
				return nullptr;
		}
		bool GraphicMgr::DestroySurface(Surface* surface) {
			if (surface == nullptr)
				return false;
		}
	}
}
#endif