

#include <iostream>
#include <fstream>
#include <string>
#include "PPM_image.h"

int main(int argv, char* argc[]) 
{
	std::fstream file;
	file.open("mario.ppm", std::ios_base::in);
	if (file.is_open()) 
	{
		std::cout << "File Loaded Successfully..." << std::endl;
		PPM image;
		//read in first two bytes of file 
		char buffer[512];
		memset(buffer, 0, 512);
		file.getline(buffer, 512);
		memcpy(&image.id, buffer, 2);
		if (image.id != 13904)
		{
			std::cout << "This is not a proper PPM file..." << buffer << std::endl;
		}
		memset(buffer, 0, 512);
		file.getline(buffer, 512);
		if (buffer[0] == '#')
		{
			memcpy(image.comment, buffer, 512);
			std::cout << image.comment << std::endl;
		}
		file >> image.width >> image.height;
		file >> image.maxColours;
		file.ignore(1);

		unsigned int pixelSize = 0;

		if (image.maxColours > 255) 
		{
			image.pixelData = new PPMPixel<unsigned short>[image.width * image.height];
			pixelSize = image.width * image.height * sizeof(PPMPixel<unsigned short>);
		}
		else 
		{
			image.pixelData = new PPMPixel<unsigned char>[image.width * image.height];
			pixelSize = image.width * image.height * sizeof(PPMPixel<unsigned char>);
		}

		file.read((char*)image.pixelData, pixelSize);

		file.close();

		for (int i = 0; i < image.width * image.height; ++i)
		{
			if (image.maxColours > 255)
			{
				PPMPixel<unsigned short>* pixelData = &((PPMPixel<unsigned short>*)image.pixelData)[i];
				pixelData->g = 0;
			}
			else
			{
				PPMPixel<unsigned char>* pixelData = &((PPMPixel<unsigned char>*)image.pixelData)[i];
				pixelData->g = 0;
			}
		}

		file.open("noGreen.ppm", std::ios_base::out | std::ios_base::binary);
		file << "P6" << std::endl;
		file << image.comment << std::endl;
		file << image.width << " " << image.height << std::endl;
		file << image.maxColours << std::endl;
		file.write((char*)image.pixelData, pixelSize);
		file.close();


	}
	else 
	{
		file.close();
	}

	return 0;
}