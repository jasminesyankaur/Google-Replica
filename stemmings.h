#ifndef _STEMMINGMAIN_H_
#define _STEMMINGMAIN_H_

#include<vector>
#include<string>
#include <iostream>

namespace Porter
{
	std::vector<std::string> runStemmerSingle(std::vector<std::string> docIn); //the main driver for using my stemmer on one document
	std::vector<std::vector<std::string> > runStemmerMultiple(std::vector<std::string> docIn); //the main driver for using my stemmer on multiple documents
	
	namespace Builder
	{
		int unique(std::vector<std::string> document); //determines the number of unique strings in a vector
	}
}

#endif
