#pragma once

#include <Windows.h>
#include <stdlib.h>
#include "winbase.h"
#include <cmath>
#include <tchar.h>

#include "Renderer.hpp"
#include "RenderPoint.hpp"

#define SCREENWIDTH 960	//  Screen Width 
#define SCREENHEIGHT 600 // Screen Height

static	WNDCLASS	wc;		// Window class data
static	HWND		hWnd;	// Window handle
static  HDC			hdc;	// Handle to device context (drawable renderTarget)
static HINSTANCE	hInst;	// Current Instance

RenderPoint*		renderPoint = 0; // 16-bit highcolor renderpoint
Renderer*			renderer =  0; // Ray tracing engine

// Forward method declarations
int					APIENTRY _tWinMain(HINSTANCE, HINSTANCE, LPSTR, int);
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
void				draw();


