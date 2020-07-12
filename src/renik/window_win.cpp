#ifdef RENIK_ENABLE
#include <renik\cpp\window.h>

#if RENIK_PLATFORM_WIN
namespace renik {
	namespace Window {
		namespace __internal__ {
			LRESULT CALLBACK __WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
				return DefWindowProc(hwnd, uMsg, wParam, lParam);
			}

			IWindow_Win::IWindow_Win(WindowDesc* desc, IWindow* parent) : IWindow::IWindow(desc, parent) {
				if (parent != nullptr) {
					parent->get_Childs().push_back(this);
				}
				WNDCLASS wc = {};
				wc.lpfnWndProc = __WindowProc;
				wc.lpszClassName =  desc->title;
				if (desc->hInstance == nullptr)
					wc.hInstance = GetModuleHandle(nullptr);
				else
					wc.hInstance = (HINSTANCE)desc->hInstance;
				wc.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;

				if (!RegisterClass(&wc)) {
					MessageBoxA(NULL,"Failed to Create Window","Error", MB_OK | MB_ICONERROR);
					return;
				}

				HWND parentHWND = nullptr;
				if (parent != nullptr) {
					parentHWND = (HWND)parent->get_Handle()->hwnd;
				}

				HWND handle = CreateWindow(wc.lpszClassName,
					desc->title, 
					WS_OVERLAPPEDWINDOW,
					desc->rect.x, desc->rect.y,
					desc->rect.width, desc->rect.height,
					parentHWND,
					NULL, 
					wc.hInstance, 
					NULL);
				if (handle) {
					this->_handle.hwnd = handle;
					this->_handle.hwndDC = GetDC(handle);
				}
				else {
					MessageBoxA(NULL, "Failed to Create Window", "Error", MB_OK | MB_ICONERROR);
					return;
				}
			}
			
			int IWindow_Win::Show() {
				ShowWindow((HWND)_handle.hwnd, 1);
				return true;
			}
			
			int IWindow_Win::Close() {
				CloseWindow((HWND)_handle.hwnd);
				return true;
			}

			int IWindow_Win::Update() {
				if (_handle.hwnd != nullptr)
					UpdateWindow((HWND)_handle.hwnd);

				MSG msg;
				int result;
				if (_handle.hwndInst == nullptr)
					result = GetMessageW(&msg, NULL, 0, 0);
				else
					result = GetMessageW(&msg, (HWND)_handle.hwndInst, 0, 0);

				if (result) {
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				return true;
			}
			
			int IWindow_Win::Release() {
				DestroyWindow((HWND)_handle.hwnd);
				return true;
			}
		}
	}
}
#endif

#endif