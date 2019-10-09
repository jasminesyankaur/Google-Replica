#include "stopwords.h"

std::vector<std::string> Stopwords::getStoppers()
{
	return stoppers;
}
std::vector<std::string> Stopwords::rem(articles A)
{
	std::vector<std::string> abstracts;
	
	for(size_t i = 0; i < A.articleList.size(); ++i)
	{
		std::string line = A.articleList[i]->getAbstract();
		
		//remove all stopwords
		for(size_t j = 0; j < stoppers.size(); ++j)
		{
			size_t index = line.find(stoppers[j]);
			while(index != std::string::npos)
			{
				if(!isalpha(line[index + stoppers[j].size()]) && !isalpha(line[index - 1]))
					line.erase(index, stoppers[j].size() + 1);
				index = line.find(stoppers[j], index + stoppers[j].size());
			}		
		}
		//iterates through each character in string line (abstract)
		for(size_t j = 0; j < line.size(); ++j)
		{
			if(!isalpha(line[j])) //if the char is punct and not a hyphen, erase it
			{
				if(line[j] == '-' && isalpha(line[j - 1]) && isalpha(line[j + 1]))
					continue;
				line[j] = ' ';
			}
			if(isdigit(line[j])) //if the char is a digit, erase it
				line[j] = ' ';
		}
		//removes all but one space between each word
		for(size_t j = 0; j < line.size(); ++j)
		{
			if(isspace(line[j]))
			{
				while(isspace(line[j + 1]))
					line.erase(line.begin() + j + 1);
			}
		}
		
		abstracts.push_back(line);
	}
	
	return abstracts;
}
std::vector<std::string> Stopwords::remQ(std::vector<std::string> docs)
{
	std::vector<std::string> documents;
	documents = docs;
	
	for(size_t i = 0; i < documents.size(); ++i)
	{
		//remove all stopwords
		for(size_t j = 0; j < stoppers.size(); ++j)
		{
			size_t index = documents[i].find(stoppers[j]);
			while(index != std::string::npos)
			{
				if(!isalpha(documents[i][index + stoppers[j].size()]) && !isalpha(documents[i][index - 1]))
					documents[i].erase(index, stoppers[j].size() + 1);
				index = documents[i].find(stoppers[j], index + stoppers[j].size());
			}
		}
		//iterates through each character in string documents[i] (abstract)
		for(size_t j = 0; j < documents[i].size(); ++j)
		{
			if(!isalpha(documents[i][j])) //if the char is punct and not a hyphen, erase it
			{
				if(documents[i][j] == '-' && isalpha(documents[i][j - 1]) && isalpha(documents[i][j + 1]))
					continue;
				documents[i][j] = ' ';
			}
			if(isdigit(documents[i][j])) //if the char is a digit, erase it
				documents[i][j] = ' ';
		}
		//removes all but one space between each word
		for(size_t j = 0; j < documents[i].size(); ++j)
		{
			if(isspace(documents[i][j]))
			{
				while(isspace(documents[i][j + 1]))
					documents[i].erase(documents[i].begin() + j + 1);
			}
		}
		if(isspace(documents[i][0]))
			documents[i].erase(documents[i].begin());
		if(isspace(documents[i][0 + documents[i].size()]))
			documents[i].erase(documents[i].begin() + documents[i].size());
	}
	
	return documents;
}
void Stopwords::initializeStopwords()
{	
	std::cout << "Enter name of stopwords file:: ";
	std::cin >> fileName;
	
	fileIn.open(fileName.c_str());
	if(!fileIn) //check for open success, throw error and exit if not
	{
		std::cerr << "Error opening file \"" << fileName << std::endl;
		std::exit(-1);
	}
	
	while(getline(fileIn, word)) //read in each line and store it as a 'word' (string) in vector stoppers
		stoppers.push_back(word);
	
	std::cout << "Number of stopwords found:: " << Stopwords::countStopwords() << std::endl;
	
	fileIn.close();
	fileName.clear();
	word.clear();
	return;
}
size_t Stopwords::countStopwords()
{
	return stoppers.size();
}
