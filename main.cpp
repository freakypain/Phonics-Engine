#include "Main.hpp"
#include "Engine.hpp"
#include "RenderPoint.hpp"
#include "Renderer.hpp"


/*
int main()
{
    std::cout << "Starting Engine" << std::endl;

	
	Engine engine; //= new Engine();

	engine.build();
	engine.run();
	engine.stop();

    return 0;
}*/

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{ 
	MSG	msg = MSG();

	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow)) return FALSE;

	// Main execution loop
	while (msg.message != WM_QUIT)
	{
		renderer->initialize();

		// Render, breaking out for messages/drawing
		//while (!rayTracer->Render())
		while (!renderer->draw())
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			draw();
		}
	}
	return 1;
}

//  Registers the window class.
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "Renderer";

	return RegisterClass(&wc);
}

// Saves instance handle and creates/displays main window
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hWnd = CreateWindow(
		"Phonics Engine",
		"Phonics Engine",
		WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		SCREENWIDTH,
		SCREENHEIGHT,
		NULL, NULL,
		hInstance, NULL);

	ShowWindow( hWnd, SW_NORMAL );

	hdc = GetDC( hWnd );

	// Initialize raw pixel buffer
	//renderTarget = new RenderTarget(SCREENWIDTH, SCREENHEIGHT);
	//renderTarget->Clear(0);
	renderPoint = new RenderPoint( SCREENWIDTH, SCREENHEIGHT );
	renderPoint->clear(0);

	// Initialize RayTracer
	//rayTracer = new RayTracer(renderTarget);
	renderer = new Renderer( renderPoint );

	return true;
}

//  Processes messages for the main window.
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_CLOSE:
			ReleaseDC(hWnd, hdc);
			DestroyWindow(hWnd);
			ExitProcess(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// 
void draw()
{
	if (renderPoint->getBuffer())
	{
		StretchDIBits(hdc, 0, 0, SCREENWIDTH, SCREENHEIGHT, 0, 0, SCREENWIDTH, SCREENHEIGHT, renderPoint->getBuffer(), renderPoint->getBitmapInfo(), DIB_RGB_COLORS, SRCCOPY);
		ValidateRect(hWnd, NULL);
	}
}



