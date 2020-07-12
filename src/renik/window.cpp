#ifdef RENIK_ENABLE
#include <renik\cpp\window.h>

namespace renik {
	namespace Window {
		using namespace __internal__;

		//----WINDOW MANAGER----
		std::vector<IWindow*> WindowMgr::m_listWin = std::vector<IWindow*>();
		IWindow* WindowMgr::get_Window(uint window) {
			for (auto win : m_listWin) {
				if (win->get_id() == window) {
					return win;
				}
			}
		}
		IWindow* WindowMgr::Create(WindowDesc* desc, IWindow* parent) {
			IWindow* newWindow = nullptr;
#if RENIK_PLATFORM_WIN
			newWindow = new IWindow_Win(desc, parent);
#endif
			m_listWin.push_back(newWindow);
			return m_listWin[m_listWin.size() - 1];
		}
		int WindowMgr::Release(IWindow* window) {
			size_t len = m_listWin.size();
			for (size_t i = 0; i < len; i++)
			{
				if (m_listWin[i] == window || m_listWin[i]->get_id() == window->get_id()) {
					m_listWin[i]->Release();
					m_listWin.erase(m_listWin.begin() + i);
					return true;
				}
			}
			return false;
		}
	}
}

#endif