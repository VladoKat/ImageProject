#include "Image.h"
const std::string Image::STR_RED = "red";
const std::string Image::STR_GREEN = "green";
const std::string Image::STR_BLUE= "blue";
const std::string Image::STR_DEFAULT = "multi";


Image::Image(std::string path){
	this->path = path;
}

Image& Image::operator= (const Image& img){
	if(this != &img){
		this->path.assign(img.path);
	}
	return *this;
}

void Image::print(){
	std::cout << path << std::endl;
}

Image::Image(const Image& img) {
	this->path.assign(img.path);
}

Image::Image(){
	
}


Image* Image::grayscale(){
	return this;
}

Image* Image::histogram(int a){
	return this;
}
