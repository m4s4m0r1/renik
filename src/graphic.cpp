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
		std::vector<Texture> GraphicMgr::textures = std::vector<Texture>();

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

		//---- MESH ----
		int Mesh::set_index(ArrayPtr<uint>* indexArray) {
			if (indexArray == nullptr || indexArray->ptr == nullptr) {
				m_index.clear();
				m_index.shrink_to_fit();
				return true;
			}
			m_index.clear();
			m_index.shrink_to_fit();
			m_index.insert(m_index.begin(), indexArray->ptr, indexArray->ptr + indexArray->length());
			return true;
		}
		int Mesh::get_index(const uint* buffer, size_t bufferSize) {
			if (buffer == nullptr || bufferSize == 0U)
				return false;
			if (bufferSize > m_index.size())
				bufferSize = m_index.size();
			memcpy(&buffer, &m_index[0], bufferSize);
			return true;
		}
		size_t Mesh::get_indexLength() {
			return m_index.size();
		}
		ArrayPtr<uint> Mesh::get_indexPtr() {
			auto res = ArrayPtr<uint>();
			res.ptr = &m_index[0];
			res.size = m_index.size() * sizeof(uint);
			res.sizePerElement = sizeof(uint);
			return res;
		}

		int  Mesh::add_vertex(const char* name, ArrayPtr<float>* vertexData) {
			if (name == nullptr || vertexData == nullptr || vertexData->ptr == nullptr)
				return false;
			try {
				//if name is already registered
				//Modify the data
				auto arrPtr = m_vertexPtr.at(name);
				//if the target has a same size, copy it
				if (arrPtr.size == vertexData->size) {
					memcpy(arrPtr.ptr, vertexData->ptr, vertexData->length());
				}
				else {
					//else, we need to re-alocating new data
					size_t offset = 0U;
					for (auto& i : m_vertexPtr) {
						if (i.second.ptr == arrPtr.ptr) {
							break;
						}
						offset += i.second.size;
					}
					//TODO : Not so eficient but kinda work for now
					//Erase all data related start from this pointer
					m_vertex.erase(m_vertex.begin() + offset, m_vertex.begin() + offset + arrPtr.length());
					//Insert new data start from this pointer
					m_vertex.insert(m_vertex.begin() + offset, vertexData->ptr, vertexData->ptr + vertexData->length());
					m_vertex.shrink_to_fit();

					m_vertexPtr[name] = *vertexData;

					//Re-pointing all "Pointer" in vertexPtr
					offset = 0U;
					for (auto& i : m_vertexPtr) {
						i.second.ptr = &m_vertex[offset];
						offset += i.second.size;
					}
				}
				return true;
			}
			catch (std::out_of_range) {
				//If the name is not registered
				//Add it to vertex buffer
				m_vertex.insert(m_vertex.end(), vertexData->ptr, vertexData->ptr + vertexData->length());
				m_vertex.shrink_to_fit();
				m_vertexPtr[name] = *vertexData;

				//Re-pointing all "Pointer" in vertexPtr
				auto offset = 0U;
				for (auto& i : m_vertexPtr) {
					i.second.ptr = &m_vertex[offset];
					offset += i.second.length();
				}
				return true;
			}
			catch (const std::exception) {
				//Otherwise something wrong happened
				return false;
			}
		}
		int Mesh::get_vertex(const char* name, const float* buffer, size_t bufferSize) {
			if (name == nullptr || buffer == nullptr)
				return false;
			try {
				auto arr = m_vertexPtr.at(name);
				if (bufferSize > arr.size)
					bufferSize = arr.size;
				memcpy(&buffer, arr.ptr, bufferSize);
				return true;
			}
			catch (std::out_of_range e) {
				return false;
			}
		}
		int Mesh::remove_vertex(const char* name) {
			if (name == nullptr)
				return false;
			try {
				return true;
			}
			catch (const std::exception) {
				return false;
			}
		}
		size_t Mesh::get_vertexLength() {
			return m_vertex.size();
		}
		ArrayPtr<float> Mesh::get_vertexPtr(const char* name) {
			try {
				return m_vertexPtr.at(name);
			}
			catch (std::out_of_range) {
				return nullptr;
			}
		}
		std::vector<std::string> Mesh::get_vertexNames() {
			size_t len = m_vertexPtr.size();
			std::vector<std::string> res(len);
			size_t i = 0U;
			for (auto m : m_vertexPtr) {
				res[i] = m.first;
				i++;
			}
			return res;
		}
		std::vector<ArrayPtr<float>> Mesh::get_vertexPtrs() {
			size_t len = m_vertexPtr.size();
			std::vector<ArrayPtr<float>> res(len);
			size_t i = 0U;
			for (auto m : m_vertexPtr) {
				res[i] = m.second;
				i++;
			}
			return res;
		}
	}
}