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
			return true;
		}

		Material* GraphicMgr::CreateMaterial() {
			Material mat = {};
			mat.shader = nullptr;
			mat.handler = std::unordered_map<std::string, GraphicShaderInputData>();

			materials.push_back(mat);
			return &materials[GraphicMgr::materials.size() - 1];
		}
		bool GraphicMgr::DestroyMaterial(Material* mat) {
			if (mat != nullptr)
			{
				mat->shader = nullptr;
				size_t len = materials.size();
				for (size_t i = 0; i < len; i++)
				{
					if (&materials[i] == mat) {
						materials.erase(materials.begin() + i);
						materials.shrink_to_fit();
						return true;
					}
				}
			}
			return false;
		}

		Mesh* GraphicMgr::CreateMesh(Array<Vec3F>& verticies, Array<uint>& index) {
			Mesh m = {};
			m.vertex = std::unordered_map <std::string , Array<float>> ();
			m.material = nullptr;
			m.vertex["vert"] = Array<float>((float*)verticies.ptr, verticies.size, 3U, sizeof(Vec3F));
			m.index = index;

			meshes.push_back(m);
			return &meshes[meshes.size() - 1];
		}
		bool GraphicMgr::DestroyMesh(Mesh* mesh) {
			if (mesh != nullptr) {
				auto len = meshes.size();
				for (size_t i = 0; i < len; i++) {
					if (&meshes[i] == mesh) {
						meshes.erase(meshes.begin() + i);
						mesh->material = nullptr;
						mesh->vertex.clear();
						return true;
					}
				}
			}
			return false;
		}
	}
}