#include "Main.hpp"
#include "Engine.hpp"
#include "RenderPoint.hpp"
#include "Renderer.hpp"
#include "Debug.hpp"

#include <iostream>


//int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
int APIENTRY _tWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPTSTR    lpCmdLine, _In_ int nCmdShow = true)
{ 
	MSG	msg = MSG();

	MyRegisterClass(hInstance);


	// TODO remove temp code
	Engine engine;
	engine.build();

	// Show debug output
	if (DEBUG == true)
	{
		Debug debug;
		debug.showConsole();
	}

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow)) return FALSE;

	// Main execution loop
	while (msg.message != WM_QUIT)
	{
		renderer->initialize();

		// Render, breaking out for messages/drawing		
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
	wc.hIcon = LoadIcon( NULL, MAKEINTRESOURCE( IDI_APPLICATION ) );
	wc.hCursor = LoadCursor( NULL, IDC_ARROW );
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszMenuName = "MainMenu";
	wc.lpszClassName = "PhonicsEngine";

	return RegisterClass(&wc);
}


//Forward declaration of the WndProc function
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Saves instance handle and creates/displays main window
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable


	hWnd = CreateWindow(
		"PhonicsEngine",
		"Phonics Engine",
		WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		SCREENWIDTH,
		SCREENHEIGHT,
		NULL, NULL,
		hInstance, NULL);
	
	//ShowWindow( hWnd, SW_NORMAL );


   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);


	hdc = GetDC( hWnd );

	// Initialize raw pixel buffer
	renderPoint = new RenderPoint( SCREENWIDTH, SCREENHEIGHT );
	renderPoint->clear(0);

	// Initialize RayTracer
	renderer = new Renderer( renderPoint );
	

	return true;
}

//  Processes messages for the main window.
LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	switch ( message )
	{
		case WM_CLOSE:
			ReleaseDC( hWnd, hdc );
			DestroyWindow( hWnd );
			ExitProcess( 0 );
			break;
		default:
			return DefWindowProc( hWnd, message, wParam, lParam );
	}
	return 0;
}

// 
void draw()
{
	if ( renderPoint->getBuffer() )
	{
		StretchDIBits( hdc, 0, 0, SCREENWIDTH, SCREENHEIGHT, 0, 0, SCREENWIDTH, SCREENHEIGHT, renderPoint->getBuffer(), renderPoint->getBitmapInfo(), DIB_RGB_COLORS, SRCCOPY );
		ValidateRect( hWnd, NULL );
	}
}



