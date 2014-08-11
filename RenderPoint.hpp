#ifndef RENDERPOINT_H
#define RENDERPOINT_H

#include "stdafx.h"

class RenderPoint
{
public:
	RenderPoint(int width, int height);
	~RenderPoint();

	// Accessors
	BITMAPINFO* getBitmapInfo() { return mBitmapInfo; };
	Pixel*		getBuffer()		{ return mBuffer;	 };
	int			getWidth()		{ return mWidth;		 };
	int			getHeight()		{ return mHeight;	 };

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

