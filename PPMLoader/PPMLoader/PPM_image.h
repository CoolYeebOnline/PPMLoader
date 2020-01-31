#pragma once
#ifndef __PPM_IMAGE_H__
#define __PPM_IMAGE_H__

//PPM image definition
//


template <typename T>
struct PPMPixel 
{
	T r;
	T g;
	T b;
};


struct PPM
{
	unsigned short id;
	char comment[512];
	unsigned int height;
	unsigned int width;
	unsigned int maxColours;

	void* pixelData;
};


#endif __PPM_IMAGE_H__
