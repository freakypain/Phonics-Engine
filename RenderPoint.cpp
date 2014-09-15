#include <Windows.h>
#include "stdafx.h"
#include "RenderPoint.hpp"


RenderPoint::RenderPoint( int width, int height ) : mWidth( width ), mHeight( height )
{
	mBuffer = new Pixel[width * height];
	initializeBitmap();
}


RenderPoint::~RenderPoint()
{
	delete[] mBuffer;
}


// Get Buffer
Pixel* RenderPoint::getBuffer() const
{
	return mBuffer;
}


// Get BitmapInfo
BITMAPINFO* RenderPoint::getBitmapInfo() const
{
	return mBitmapInfo;
}


// Get Width
int RenderPoint::getWidth() const
{
	return mWidth;
}
	

// Get Height
int RenderPoint::getHeight() const
{
	return mHeight;
}


// Set each pixel to  buffer
void RenderPoint::setPixel( int index, Pixel pixel )
{
	mBuffer[index] = pixel;
}


// Clear pixel buffer
void RenderPoint::clear( Pixel colour )
{
	int pixelCount = mWidth * mHeight;

	for (int i = 0; i < pixelCount; i++)
	{
		mBuffer[i] = colour;
	}
}


// DIB for Rendering http://msdn.microsoft.com/en-us/library/aa921550.aspx	
void RenderPoint::initializeBitmap()
{

	for ( int i = 0; i < sizeof(BITMAPINFOHEADER) + 16; i++ )
	{
		mBitmapBuffer[i] = 0;
	}

	mBitmapInfo = (BITMAPINFO*)&mBitmapBuffer;
	mBitmapInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	mBitmapInfo->bmiHeader.biPlanes = 1;
	mBitmapInfo->bmiHeader.biBitCount = 32;
	mBitmapInfo->bmiHeader.biCompression = BI_BITFIELDS;
	mBitmapInfo->bmiHeader.biWidth = mWidth;
	mBitmapInfo->bmiHeader.biHeight = -mHeight;	// Top-left == origin

	// Indicate where RGB values are stored in the buffer
	((ULONG*)mBitmapInfo->bmiColors)[0] = 255 << 16;
	((ULONG*)mBitmapInfo->bmiColors)[1] = 255 << 8;
	((ULONG*)mBitmapInfo->bmiColors)[2] = 255 << 0;
}


