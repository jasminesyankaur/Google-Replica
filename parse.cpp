#include "parse.h"

//Cut (no header)
std::vector<std::string> Parse::cut(char delim, std::string line)
{
	std::vector<std::string> result; //initialize result vector
	std::istringstream newline;
	std::string temp = "";
	newline.str(line); //initialize istringstream to line param
	while(getline(newline, temp, delim)) //read until eos
	{
		result.push_back(temp); //add parsed string to container
	}
	newline.clear(); //clear bits on istream
	
	return result;
}
//Cut (header)
std::vector<std::string> Parse::cut(std::string delim1, char delim2, std::string line)
{
	std::vector<std::string> result; //initialize result vector
	std::istringstream newline;
	std::string temp = "";
	
	result.push_back(line.substr(0, line.find(delim1))); //finds header string until delim1 and adds to container at index 0
	line.erase(0, line.find(delim1) + 1); //erase up to and including delim1
	
	newline.str(line); //initialize istringstream to line param
	while(getline(newline, temp, delim2)) //read until eos
	{
		result.push_back(temp); //add parsed string to container
	}
	newline.clear(); //clear bits on istream
	
	return result;
}
