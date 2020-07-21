#pragma once
#ifndef RENIK_WINDOW_CPP_H
#define RENIK_WINDOW_CPP_H
#include <renik\cpp\common.h>

#define RENIK_IWINDOW(className)\
	class className : public IWindow {\
	public:\
		className(WindowDesc* desc,IWindow* parent);\
		~className();\
		int Show() override;\
		int Close() override;\
		int Update() override;\
		int Release() override;\
	};\

namespace renik {
	namespace Window {
		//Predefined Class
		class IWindow;

		//----WINDOW PARAMETER----
		struct WinHandle {
			void* hwnd = nullptr;
			void* hwndDC = nullptr;
			void* hwndInst = nullptr;
		};

		struct WindowDesc {
			const wchar_t* title = nullptr;
			void* hInstance = nullptr;
			RectI rect = RectI();
			bool fullScreen = false;
		};

		//----WINDOW ABSTRACTION----
		class IWindow : public BaseObject<id_t, IWindow> {
		protected:
			WindowDesc _desc;
			WinHandle _handle;
			IWindow* _parent = nullptr;
			std::vector<IWindow*> _childs;
		public:
			IWindow(WindowDesc* desc, IWindow* parent) {
				_desc = *desc;
				_parent = parent;
				_childs = std::vector<IWindow*>();
			}
			WindowDesc* get_desc() { return &_desc; }
			WinHandle* get_handle() {return &_handle;}
			IWindow* get_parent() { return _parent; }
			std::vector<IWindow*> get_childs() { return _childs; }

			virtual int Show() { return false; }
			virtual int Close() { return false; }
			virtual int Update() { return false; }
			virtual int Release() { return false; }
		};

		namespace __internal__ {
		#if RENIK_PLATFORM_WIN
			//Generated Script for Windows windowing Server
			RENIK_IWINDOW(IWindow_Win);
		#endif
		}
		//----WINDOW MANAGER----
		class WindowMgr final {
		private:
			static std::vector<IWindow*> m_listWin;
		public:
			static IWindow* get_window(uint id);
			static IWindow* Create(WindowDesc* param, IWindow* parent = nullptr);
			static int Release(IWindow* window);
		};
	}
}

#undef RENIK_IWINDOW

#endif