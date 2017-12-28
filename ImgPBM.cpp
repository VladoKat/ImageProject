#include<string>
#include "Image.h"
#include "ImgPBM.h"
#include "GeneralFunctions.h"

const std::string FORMAT_PBM = ".pbm";

ImgPBM::ImgPBM (std::string str){
	std::string substr = str.substr(str.length()-4);
	if(substr.compare(FORMAT_PBM) == 0){
		path = str;
	}
}
ImgPBM& ImgPBM::operator= (const ImgPBM& img){
	if(this != &img){
		this->path.assign(img.path);
	}
	return *this;
}
ImgPBM::ImgPBM(const ImgPBM& img) : Image(img){
	
}

Image* ImgPBM::monochrome(){
	return this;
}
