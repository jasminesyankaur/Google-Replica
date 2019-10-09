#ifndef _STOPWORDS_H_
#define _STOPWORDS_H_

#include "articles.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctype.h>

class Stopwords
{
	public:
		std::vector<std::string> getStoppers(); //access the stoppers vector of strings
		
		std::vector<std::string> rem(articles A); //passbyreference a string and remove stopwords/punct/digits from it
		std::vector<std::string> remQ(std::vector<std::string> docs);
		
		void initializeStopwords(); //initialize the stopwords vector
		size_t countStopwords(); //returns the number of stopwords found
	
	protected:
	
	private:
		std::string word, fileName;
		std::ifstream fileIn;
		std::vector<std::string> stoppers;
};

#endif
