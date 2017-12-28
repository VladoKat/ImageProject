#include <iostream>
#include <fstream>
#include "Image.h"
#include "ImgPPM.h"
#include "ImgPBM.h"
#include "ImgPGM.h"
#include "GeneralFunctions.h"


void testTerOperator(){
	int red = 12;
	int green = 255;
	int blue = 255;
	((red + green + blue) / 3) < 127 ? std::cout << 0 : std::cout<<  255;
	
}

void test_grayscale(){
	
	ImgPPM img("newTest.ppm");
	//ImgPGM img2("pgm_test.pgm");
	//img2.monochrome();
	img.grayscale();
	//img.monochrome();
}
void test_histogram(){
	ImgPPM img("newTest.ppm");
	img.histogram(3);
}

const std::string GRAYSCALE_TEMP = "--grayscale";
const int GRAYSCALE_LEN = 11; 
const std::string MONOCHROME_TEMP = "--monochrome";
const int MONOCHROME_LEN = 12;
const std::string HISTOGRAM_TEMP = "--histogram=";
const int HISTOGRAM_LEN = 12;
const std::string RED = "red";
const int RED_LEN = 3;
const std::string GREEN = "green";
const int GREEN_LEN = 5;
const std::string BLUE = "blue";
const int BLUE_LEN = 4;

Image* recognizeFormat(std::string str){
	int pointPos = str.find(".");
	std::string format = str.substr(pointPos, 4);
	Image* image;
	if(format.compare(".ppm") == 0){
		image = new ImgPPM(str.substr(0, pointPos + 4));
	}
	if(format.compare(".pgm") == 0){
		image = new ImgPGM(str.substr(0, pointPos + 4));
	}
	if(format.compare(".pbm") == 0){
		image = new ImgPBM(str.substr(0, pointPos + 4));
	}
	return image;
}
void executeFunks(bool* functions, Image* image){
	if(functions[0]){
		image->grayscale();
	}
	if(functions[1]){
		image->monochrome();
	}
	if(functions[2]){
		image->histogram(Image::INT_RED);
	}
	if(functions[3]){
		image->histogram(Image::INT_GREEN);
	}
	if(functions[4]){
		image->histogram(Image::INT_BLUE);
	}
}
void recognizeFunks(std::string& str, std::string* funkCommands, int* lengths, bool* functions){
	size_t pos;
	for(int i = 0; i < 5; i++){
		pos = str.find(funkCommands[i]);
		while(pos != std::string::npos){
			functions[i] = 1;
			str.erase(pos, lengths[i]);
			pos = str.find(funkCommands[i]);
		}
	}
}
void eraseSpaces(std::string& str){
	int i = 0;
	while(str[i] == ' '){
		str.erase(i, 1);
	}
}
void recognize(std::string str){
	
	bool functions[5] = {0};
	int lengths[5] = {GRAYSCALE_LEN, MONOCHROME_LEN, HISTOGRAM_LEN + RED_LEN, HISTOGRAM_LEN + GREEN_LEN, HISTOGRAM_LEN + BLUE_LEN};
	std::string funkCommands[5] = {GRAYSCALE_TEMP, MONOCHROME_TEMP, HISTOGRAM_TEMP + RED, HISTOGRAM_TEMP + GREEN, HISTOGRAM_TEMP + BLUE};
	recognizeFunks(str, funkCommands, lengths, functions);
	eraseSpaces(str);
	
	Image *image = recognizeFormat(str);
	if(image != NULL){
		executeFunks(functions, image);
		delete &image;
	} else {
		std::cout << "Incorrect input!" << std::endl;
	}
	
}
void userInterface(){
	std::string enteredStr;
	std::getline(std::cin,enteredStr);
	recognize(enteredStr);
}
int main(){
	userInterface();
	return 0;
}
