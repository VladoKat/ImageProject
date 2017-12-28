#include<string>
#include "Image.h"
#include "ImgPGM.h"
#include "GeneralFunctions.h"

const std::string FORMAT_PGM = ".pgm";
const std::string HEADER_P2 = "P2";
ImgPGM::ImgPGM (std::string str){
	std::string substr = str.substr(str.length()-4);
	if(substr.compare(FORMAT_PGM) == 0){
		path = str;
	}
}
ImgPGM& ImgPGM::operator= (const ImgPGM& img){
	if(this != &img){
	this->path.assign(img.path);
	}
	return *this;
}
ImgPGM::ImgPGM(const ImgPGM& img): Image(img){
}

int turnMono(int color, int maxValue){
	if(color > (maxValue/2)){
		return maxValue;
	}
	return 0;
}
void fillGrayMatrix(int** gray, std::string line, int row, int col, 
					std::ifstream& readFile, int maxValue, bool& foundNonMonochrome ){
	for (int i = 0; i < row; ++i){
		checkForComments(readFile, line);
		for(int j = 0; j < col; ++j){
			int color;
			readFile >> color;
			if(color > 0 && color < maxValue){
				foundNonMonochrome = true;
			}
			gray[i][j] = turnMono(color, maxValue);
		}
	}
}

void generateFile(int** gray, std::string path, int row, int col, int maxValue){
	path = monochromePath(path);
	std::ofstream write;
	write.open(path.c_str());
	write << HEADER_P2 << ENDL << row << ONE_SPACE  << col << ENDL << maxValue << ENDL;
	for(int i = 0; i < row; ++i){
		for(int j = 0; j < col; ++j){
			std::string numSpaces = generateSpaces(gray[i][j]);
			write << numSpaces << gray[i][j] << ONE_SPACE;
		}
		write << ENDL;
	}
	write.close();
}
Image* ImgPGM::monochrome(){
	std::ifstream readFile;
	readFile.open(path.c_str(), std::ios::binary);
	if(readFile.is_open()){
		std::string line;
		int row, col, maxValue;
		getInitInfo(readFile, line, row, col, maxValue);
		int** gray = new int*[row];
		for(int i = 0; i < row; i++)
			gray[i] = new int[col];
		bool foundNonMonochrome = false;
		fillGrayMatrix(gray, path, row, col, readFile, maxValue ,foundNonMonochrome);
		if(foundNonMonochrome){
			generateFile(gray, path, row, col, maxValue);
		}
		delete[] gray;
		readFile.close();
	}
	return new ImgPGM(path);
}
