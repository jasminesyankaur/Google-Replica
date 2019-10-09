#ifndef PARSE_H
#define PARSE_H
#include <sstream>
#include <vector>
#include <string>
namespace Parse
{
		/*
			This function takes a line and parses into separate strings based on a delimiter
		*/
		std::vector<std::string> cut(char delim, std::string line);
		/*
			This function takes a line and parses into separate strings, first a header based
			on delim 1 and then following strings based on delim 2
		*/
		std::vector<std::string> cut(std::string delim1, char delim2, std::string line);
};
#endif
