#include "GeneralFunctions.h"
//#include<iostream>
#include <string>
#include <fstream>

std::string generateSpaces(int num){
	if(num < 100 && num > 9){
		return ONE_SPACE;
	}
	if(num < 10){
		return TWO_SPACES;
	}
	return ZERO_SPACES;
}
std::string grayPath(std::string path){
	path.insert(path.length()-4, GRAYSCALE);
	return path;
}
std::string monochromePath(std::string path){
	path.insert(path.length()-4, MONOCHROME);
	return path;
}

std::string histogramPath(std::string& path, std::string strChannel){
	path.insert(path.length()-4, HISTOGRAM + strChannel);
	return path;
}
void checkForComments(std::ifstream& readFile, std::string line){
	std::streampos pos = readFile.tellg();
	do{
		pos = readFile.tellg();
		getline(readFile, line);
	} while((line.compare(ZERO_SPACES) == 0 || line[0] == '#') && !readFile.eof());
	readFile.clear();
	readFile.seekg(pos);
}
void getInitInfo(std::ifstream& readFile, std::string& line, int& row, int& col, int& maxValue){
	checkForComments(readFile, line);
	getline(readFile, line); // header;
	
	checkForComments(readFile, line);
	readFile >> row >> col;
	getline(readFile, line); //dimensions
	
	checkForComments(readFile, line);
	readFile >> maxValue;
	getline(readFile, line);
	
	checkForComments(readFile, line);
}
