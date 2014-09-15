#ifndef RENDERPOINT_H
#define RENDERPOINT_H

#include <Windows.h>
#include "stdafx.h"

class RenderPoint
{
public:
	RenderPoint(int width, int height);
	~RenderPoint();

	// Accessors
	BITMAPINFO* getBitmapInfo() const;
	Pixel*		getBuffer()		const;
	int			getWidth()		const;
	int			getHeight()		const;

	void setPixel(int index, Pixel pixel);
	void clear(Pixel colour);

private:
	Pixel* mBuffer;
	int mWidth;
	int mHeight;

	// properties of device independent bitmap
	BITMAPINFO* mBitmapInfo;
	char		mBitmapBuffer[sizeof(BITMAPINFO) + 16];

	void initializeBitmap();
};



#endif	// RENDERPOINT_H

