#include<string>
#include<fstream>
#include "Image.h"
#include "ImgPPM.h"
#include "GeneralFunctions.h"

const std::string FORMAT = ".ppm";
const std::string HEADER = "P3";
const int HUNDRED = 100;

ImgPPM::ImgPPM (std::string str){
	if(str.length() > 4){
		std::string substr = str.substr(str.length()-4);
		if(substr.compare(FORMAT) == 0){
			path = str;
		}
	}
}
ImgPPM::ImgPPM(const ImgPPM& img) : Image(img){
}

ImgPPM& ImgPPM::operator= (const ImgPPM& img){
	if(this != &img){
		this->path.assign(img.path);
	}
	return *this;
}

//not in general
void generateFile(int** gray, std::string path, int row, int col, int maxValue, std::string (*pathMaker)(std::string)){
	path = pathMaker((std::string)path);
	std::ofstream write;
	write.open(path.c_str());
	write << HEADER << ENDL << row << ONE_SPACE  << col << ENDL << maxValue << ENDL;
	for(int i = 0; i < row; ++i){
		for(int j = 0; j < col; ++j){
			std::string numSpaces = generateSpaces(gray[i][j]);
			write << numSpaces << gray[i][j] << ONE_SPACE
				  << numSpaces << gray[i][j] << ONE_SPACE
				  << numSpaces << gray[i][j] << ONE_SPACE;
		}
		write << ENDL;
	}
	write.close();
}

bool isGrayscale(int red, int green, int blue, int maxValue){
	return !(red == green && red == blue);
}

bool isMonochrome(int red, int green, int blue, int maxValue){
	return!((red == green && red == blue) && (red == 0 || red == maxValue));
}

int makeGray(int red, int green, int blue, int maxValue){
	if(red >= green && red >= blue) return red;
	if(green >= red && green >= blue) return green;
	return blue;
}

int makeMonochrome(int red, int green, int blue, int maxValue){
	if(((red + green + blue) / 3) > (maxValue/2)) {
		return maxValue ;
	}		
	return 0;
}

void fillNewMatrix(std::ifstream& readFile, std::string& line, int** gray, int row, int col, int maxValue, 
					bool& nonGrayColorExists, int(*picker)(int, int, int, int), bool(*condition)(int, int, int, int)){
	for (int i = 0; i < row; ++i){
		checkForComments(readFile, line);
		for(int j = 0; j < col; ++j){
			int red, green, blue;
			readFile >> red >> green >> blue;
			if(!(red == green && red == blue)){
				nonGrayColorExists = condition(red, green, blue, maxValue);
			}
			gray[i][j] = picker(red, green, blue, maxValue); //maxValue not rly needed
		}
	}
}
Image* ImgPPM::grayscale(){
	std::ifstream readFile;
	readFile.open(path.c_str(), std::ios::binary);
	if(readFile.is_open()){
		std::string line;
		int row, col, maxValue;
		getInitInfo(readFile,line, row, col, maxValue);
		int** gray = new int*[row];
		for(int i = 0; i < row; i++)
			gray[i] = new int[col];
		bool nonGrayColorExists = false;
		fillNewMatrix(readFile, line, gray, row, col, maxValue, 
						nonGrayColorExists, makeGray, isGrayscale);
		if(nonGrayColorExists){
			generateFile(gray, path, row, col, maxValue, grayPath);
		}
		delete[] gray;
		readFile.close();
	}
	
	return new ImgPPM(path);
}

Image* ImgPPM::monochrome(){
	std::ifstream readFile;
	readFile.open(path.c_str(), std::ios::binary);
	if(readFile.is_open()){
		std::string line;
		int row, col, maxValue;
		getInitInfo(readFile,line, row, col, maxValue);
		int** gray = new int*[row];
		for(int i = 0; i < row; i++)
			gray[i] = new int[col];
		bool nonGrayColorExists = false;
		fillNewMatrix(readFile, line, gray, row, col, maxValue, 
						nonGrayColorExists, makeMonochrome, isMonochrome);
		if(nonGrayColorExists){
			generateFile(gray, path, row, col, maxValue, monochromePath);
		}
		delete[] gray;
		readFile.close();
	}
	return new ImgPPM(path);
}

void fillColoredMatrix(std::ifstream& readFile, std::string& line, 
						int* redArr, int* greenArr, int* blueArr, int row, int col){
	int red, green, blue;
	while(!readFile.eof()){
		checkForComments(readFile, line);
		readFile >> red >> green >> blue;
		redArr[red]++;
		greenArr[green]++;
		blueArr[blue]++;
	}
}

int* initArrAndChannel(int channel, std::string& strChannel, int& red, int& green, int& blue, int maxValue,
						int* redArr, int* greenArr, int* blueArr){
	switch(channel){
		case Image::INT_RED: {
			
			strChannel = Image::STR_RED;
			red = maxValue;
			green = 0;
			blue = 0;
			return redArr;
		}
		case Image::INT_GREEN: {
			strChannel = Image::STR_GREEN;
			red = 0;
			green = maxValue;
			blue = 0;
			return greenArr;
		}
		case Image::INT_BLUE: {
			strChannel = Image::STR_BLUE;
			red = 0;
			green = 0;
			blue = maxValue;
			return blueArr;
		}
		default: {
			strChannel = Image::STR_DEFAULT;
			red = 0;
			green = 0;
			blue = 0;
			return NULL;
		}
	}
}
int findMax(int* workingArr, int maxValue){
	int max = *workingArr;
	for(int i = 1; i < maxValue; ++i){
		if(max < workingArr[i]){
			max = workingArr[i];
		}
	}
	return max;
}
generateHistogram(int channel, int* redArr, int* greenArr, int* blueArr, int maxValue, std::string path, int numPixels){
	
	int red, green, blue;
	std::string strChannel;
	int* workingArr =  initArrAndChannel(channel, strChannel, red, green, blue, maxValue, redArr, greenArr, blueArr);
	
	std::ofstream write;
	write.open(histogramPath(path, strChannel).c_str());
	write << HEADER << ENDL << maxValue + 1<< ONE_SPACE  << HUNDRED << ENDL << maxValue << ENDL;
	//std::cout << ENDL;
	if(workingArr != NULL){
		int maxInArr = findMax(workingArr, maxValue);
		
		for(int i = HUNDRED - 1; i >= 0; --i){
			for(int j = 0; j <= maxValue; ++j){
				if (i <= (((double)workingArr[j] / numPixels)) * 100){
					//std::cout << workingArr[j] << " " << i << ENDL;
					write << generateSpaces(red) << red << ONE_SPACE 
						<< generateSpaces(green) << green << ONE_SPACE
						<< generateSpaces(blue) << blue << ONE_SPACE;
				} else {
					write << ZERO_SPACES << maxValue << ONE_SPACE
						<< ZERO_SPACES << maxValue << ONE_SPACE
						<< ZERO_SPACES << maxValue << ONE_SPACE;
				}
			}
			write << ENDL;
		}
		write.close();
	} else {
		/*
			TODO all in one
		*/
	}
}
Image* ImgPPM::histogram(int channel){
	std::ifstream readFile;
	readFile.open(path.c_str(), std::ios::binary);
	if(readFile.is_open()){
		std::string line;
		int row, col, maxValue;
		getInitInfo(readFile,line, row, col, maxValue);
		int numPixels = row*col;
		int* redArr = new int[maxValue+1]();
		int* greenArr = new int[maxValue+1]();
		int* blueArr = new int[maxValue+1]();
		fillColoredMatrix(readFile, line, redArr, greenArr, blueArr, row, col);
		generateHistogram(channel, redArr, greenArr, blueArr, maxValue, path, numPixels);
		delete[] redArr;
		delete[] greenArr;
		delete[] blueArr;
		readFile.close();
		return new ImgPPM(path);
	}
	return NULL;
}