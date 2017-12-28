#ifndef IMAGE_H
#define IMAGE_H

#include<iostream>
#include <string.h>

class Image {
protected:
	std::string path;
public:
	static const int INT_RED = 1;
	static const int INT_GREEN = 2;
	static const int INT_BLUE = 3;
	static const std::string STR_RED; //= "red";
	static const std::string STR_GREEN; //= "green";
	static const std::string STR_BLUE; //= "blue";
	static const std::string STR_DEFAULT;// = "multi";
	
	void print();
	virtual Image* grayscale();
	virtual Image* monochrome() = 0;
	virtual Image* histogram(int);
	
	Image();
	Image (std::string);
	Image& operator= (const Image&);
	Image(const Image&);
};

#endif