#include "stemming.h"
#include "parse.h"
#include "stemmingMain.h"

std::vector<std::string> Porter::runStemmerSingle(std::vector<std::string> docIn)
{	
	std::vector<std::string> document = docIn;
	
	for(size_t i = 0; i < document.size(); ++i) //iterate through each word in document and stem
		Stemming::stem(document[i]);
	
	return document;
}
std::vector<std::vector<std::string> > Porter::runStemmerMultiple(std::vector<std::string> docIn)
{
	std::vector<std::vector<std::string> > documents;
	
	for(size_t i = 0; i < docIn.size(); ++i)
		documents.push_back(Parse::cut(' ', docIn[i]));
	
	std::cout << "Number of unique, unstemmed words:: " << Porter::Builder::unique(documents[0]) << std::endl;
	
	for(size_t i = 0; i < documents.size(); ++i) //iterate through each vector in documents
	{
		for(size_t j = 0; j < documents[i].size(); ++j) //iterate through each string in documents[i] and stem
			Stemming::stem(documents[i][j]);
	}
	
	std::cout << "Number of unique, stemmed words:: " << Porter::Builder::unique(documents[0]) << std::endl;
	
	return documents;
}
int Porter::Builder::unique(std::vector<std::string> document)
{
	int counter = 0;
	
	std::vector<std::string> uniqueStrings; //this container grows as an already used word is found
	
	for(size_t i = 0; i < document.size(); ++i) //iterate through each word in the document
	{
		bool used = false;
		for(size_t j = 0; j < uniqueStrings.size(); ++j) //iterate through each word in the already used container
		{
			if(document[i] == uniqueStrings[j]) //if a word already used is found in the document, set bool used to true and break out of the loop for efficiency
			{
				used = true;
				break;
			}
		}
		if(!used) //if the word was not already used, add it to the container and increment counter
		{
			uniqueStrings.push_back(document[i]);
			counter++;
		}
	}
	
	return counter - 1;
}
