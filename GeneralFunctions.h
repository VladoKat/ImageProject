#ifndef GENERAL_FUNCTIONS
#define GENERAL_FUNCTIONS

#include<string>
#include<fstream>

const std::string TWO_SPACES = "  ";
const std::string ONE_SPACE = " ";
const std::string ZERO_SPACES = "";
const std::string ENDL = "\n";
const std::string GRAYSCALE = "_grayscale";
const std::string MONOCHROME = "_monochrome";
const std::string HISTOGRAM = "_histogram_";

std::string generateSpaces(int);
std::string grayPath(std::string);
std::string monochromePath(std::string);
std::string histogramPath(std::string&, std::string);
void checkForComments(std::ifstream& , std::string );
void getInitInfo(std::ifstream& , std::string& , int& , int& , int& );
#endif