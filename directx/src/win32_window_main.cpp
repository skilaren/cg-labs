
#include "renderer.h"
#include "win32_window.h"


int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
	try
	{
		OutputDebugString(L"Start the application\n");
		Renderer render(1920, 1080);
		return Win32Window::Run(&render, hInstance, nCmdShow);
	}
	catch (com_exception e)
	{
		OutputDebugString(L"Exception:\n");
		OutputDebugString(e.get_wstring());
		return 1;
	}
}