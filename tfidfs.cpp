#include "Tfidfs.h"


//Collection Functions


void Tfidfs::populateCollection(std::vector<std::vector<std::string>> words){  //Populates words with basic info like name, document number, and total documents by using tfidf class
    for(unsigned int i = 0; i < words.size(); i++)
    {
    	std::vector<Tfidf> vtemp;	//vector to hold each document word set
        for(unsigned int j = 0; j < words.at(i).size(); j++)
        {
            Tfidf temp(words.at(i).at(j), i, words.size()); // @suppress("Ambiguous problem") set constructor
            if(!temp.getWord().empty())
            	vtemp.push_back(temp);
        }
        collection.push_back(vtemp); //push back all elements
    }
}

void Tfidfs::assignCollectionTf(){	//assigns each tfidf class a tf
	int desiredDoc = 0;
	std::string desiredString = "";		//set default find variables

	for(unsigned int i = 0; i < collection.size(); i++)	//sort through each tfidf through the collection and increment if same word is found in same document, then assign
	{
		for(unsigned int j = 0; j < collection.at(i).size(); j++)
		{
			int tfCounter = 0;
			desiredDoc = collection.at(i).at(j).getDocnum();
			desiredString = collection.at(i).at(j).getWord();	//start of new word search for current collection element, set find variables and reset counter
			for(unsigned int k = 0; k < collection.at(i).size(); k++)
			{
				if(collection.at(i).at(k).getDocnum() == desiredDoc && collection.at(i).at(k).getWord() == desiredString) //if a word matches in document
				{
					tfCounter++;
				}
			}
			collection.at(i).at(j).setTf(tfCounter);
		}
	}
}

void Tfidfs::assignCollectionNt(){	//assigns each class a nt (number of times word shows up in any document)
	std::string desiredString = "";	//set default find variable

	for(unsigned int i = 0; i < collection.size(); i++)	// Multidimension loop to search through each i of collection vector
	{
		for(unsigned int j = 0; j < collection.at(i).size(); j++)
		{
			desiredString = collection.at(i).at(j).getWord();		//sets word we are looking for
			int ntCounter = 0;
			for(unsigned int k = 0; k < collection.size(); k++)	//I seriously should have made a function for this, or found an easier way, but i'm in too deep so i'm going to leave it as it works. 4D loop can't hurt performance that much, right?
			{
				for(unsigned int l = 0; l < collection.at(k).size(); l++)
				{
					if(collection.at(k).at(l).getWord() == desiredString)
					{
						ntCounter++;
						break;
					}
				}
			}
			collection.at(i).at(j).setNt(ntCounter);					//set collection element nt once calculated
		}
	}
}

void Tfidfs::printFirstDoc(){	//prints first set of documents
	for(unsigned int i = 0; i < 1; i++)
	{
		for(unsigned int j = 0; j < collection.at(i).size(); j++)
		{
			std::cout << "Word: " << collection.at(i).at(j).getWord() << "  TF: " << collection.at(i).at(j).getTf() << "  IDF: " << log(collection.at(i).at(j).getN()/collection.at(i).at(j).getNt()) << "  TFIDF: " << collection.at(i).at(j).getTfidf() << std::endl;

		}
		std::cout << std::endl;
	}
}

void Tfidfs::calculateCollectionTfidf(std::vector<std::vector<std::string>> temp){	//uses all assignment functions, calculates final tfidf, then prints first doc
	populateCollection(temp);
	assignCollectionTf();
	assignCollectionNt();
	for(unsigned int i = 0; i < collection.size(); i++)
	{
		for(unsigned int j = 0; j < collection.at(i).size(); j++)
		{
			collection.at(i).at(j).calculateTfidf();
		}
	}
	removeCollectionDuplicates();
	printFirstDoc();
}

void Tfidfs::removeCollectionDuplicates(){	//Sorts list alphabetically, then uses unique function to remove all duplicates in a document
std::vector<Tfidf>::iterator it;
	for(unsigned int i = 0; i < collection.size(); i++)
	{
			std::sort(collection.at(i).begin(), collection.at(i).end(), []( Tfidf a, Tfidf b ){ return a.getWord() < b.getWord(); } );	//one-line lambda sort function, alphabetical
			for(unsigned int j = 0; j < collection.at(i).size(); j++)
			{
					it = std::unique(collection.at(i).begin(), collection.at(i).end(),	//multi line lambda to set iterator to unique function with equality check, then resizes each document to the correct size using set iterator
							[](Tfidf c, Tfidf d)
							{
							if(c.getWord() != d.getWord())
							{
								return false;
							}
							return true;
							});
					collection.at(i).resize(std::distance(collection.at(i).begin(),it) );
			}
	}
}

//Query and Cosine Similarity Functions

void Tfidfs::addQuery()
{
  string allwords;

  cout << "Please enter a query to find related documents: ";
  cin.ignore();
  getline(cin, allwords);

  // Parse words into a vector
  vector<string> words;
  string word;


  istringstream iss(allwords);

  while( iss >> word )
  {
	  queryStrings.push_back(word);
  }



}

void Tfidfs::trimQuery()
{
	Stopwords s;
	queryStrings = Porter::runStemmerSingle(queryStrings);	//runs stemmer and porter on existing query string
	queryStrings = s.remQ(queryStrings);
	for(int i = 0; i < queryStrings.size(); i++)	//removes words not in collection
	{
		bool wordFound = false;
		for(int j = 0; j < collection.size(); j++)
		{
			for (int k = 0; k < collection.at(j).size(); k++)
			{
				if(queryStrings.at(i) == collection.at(j).at(k).getWord())
					wordFound = true;
			}
		}
		if(!wordFound)
		{
			cout << queryStrings.at(i) << " is not in any of the documents.\n";
			queryStrings.at(i).erase();

		}
	}
}

void Tfidfs::populateQuery(){	//creates tfidf based on word in string vector and pushes back on query tfidf collection
        for(unsigned int i = 0; i < queryStrings.size(); i++)
        {
            Tfidf temp(queryStrings.at(i), -1, 0); // @suppress("Ambiguous p$
            query.push_back(temp);
        }
}

void Tfidfs::assignQueryTf(){	//assigns each query tfidf amount of times word is in query
    int tfCounter = 0;
    std::string desiredWord = "";
    for(unsigned int i = 0; i < query.size(); i++)
    {
            tfCounter = 0;
            desiredWord = query.at(i).getWord();
            for(unsigned int j = 0; j < query.size(); j++)
            {
                    if(query.at(j).getWord() == desiredWord)
                    {
                                    tfCounter++;
                    }
            }
            query.at(i).setTf(tfCounter);
    }
}

void Tfidfs::assignQueryN(){	//sets query tfidf classes n to current amount of documents
	for(unsigned int i = 0; i < query.size(); i++)
	{
		query.at(i).setN(collection.at(0).at(0).getN());
	}
}

void Tfidfs::assignQueryNt(){	//assigns each query tfidf their nt based on collection
	for(unsigned int i = 0; i < query.size(); i++)	//loop through entire collection for each tfidf in query
	{
		std::string desiredWord = query.at(i).getWord();	//set word to alter
		for(unsigned int j = 0; j < collection.size(); j++)
		{
			for(unsigned int k = 0; k < collection.at(j).size(); k++)
			{
				if(collection.at(j).at(k).getWord() == desiredWord) //if current tfidf is the same word as query
				{
					query.at(i).setNt(collection.at(j).at(k).getNt());	//query nt is now collection nt
					break;	//exit collection loop
				}
			}
			if(query.at(i).getNt() != 0) //exit collection loop
				break;
		}
	}
}

void Tfidfs::calculateQueryTfidf(){	//uses all assignment functions, calculates tfidf for query
	addQuery();
	trimQuery();
	populateQuery();
	assignQueryTf();
	assignQueryN();
	assignQueryNt();
	for(unsigned int i = 0; i < query.size(); i++)
	{
		query.at(i).calculateTfidf();
	}
	removeQueryDuplicates();
}

void Tfidfs::removeQueryDuplicates(){	//Sorts list alphabetically, then uses unique function to remove all duplicates in query
	std::vector<Tfidf>::iterator it;	//Set iterator to traverse through vector
	std::sort(query.begin(), query.end(), []( Tfidf a, Tfidf b ){ return a.getWord() < b.getWord(); } );	//one-line lambda sort function, alphabetical
	it = std::unique(query.begin(), query.end(),	//multi line lambda to set iterator to unique function with equality check, then resizes each document to the correct size using set iterator
			[](Tfidf c, Tfidf d)
			{
			if(c.getWord() != d.getWord())
			{
				return false;
			}
				return true;
			});
	query.resize(std::distance(query.begin(),it) ); //resizes vector to fit thinned data
}

double Tfidfs::returnTfidfByWordAndDocument(std::string word, int document){	//returns specified tfidf by document and word
	for(unsigned int i = 0; i < collection.size(); i++)
	{
		for(unsigned int j = 0; j < collection.at(i).size(); j++)
		{
			if(collection.at(i).at(j).getWord() == word && collection.at(i).at(j).getDocnum() == document)
			{
				return collection.at(i).at(j).getTfidf();
			}
		}
	}
	return 0;
}

void Tfidfs::calculateCosineNumerators(){	//calculates dot product of query and collection document
	for(unsigned int i = 0; i < collection.size(); i++)	// i and j are used to traverse through each document in the collection
	{
		for(unsigned int j = 0; j < collection.at(i).size(); j++)
		{
			double sum = 0; //sum total for the numerator
			for(unsigned int k = 0; k < query.size(); k++)	//to iterate through each word in the query
			{
				sum += (query.at(k).getTfidf() * returnTfidfByWordAndDocument(query.at(k).getWord(), i)); //adds up tfidf of current query word, and the tfidf of word in document. if word doesnt exist in doc, return 0 for tfidf
			}
			collection.at(i).at(0).cosineSimilarity.numerator = sum;	//set the first element of each documents numerator
		}
	}
}

void Tfidfs::calculateCosineDenominators(){	//calculates series sum of query tfidf and document tfidf
	for(unsigned int i = 0; i < collection.size(); i++)	//go through each document
	{
		double asum = 0;
		double bsum = 0;
		for(unsigned int j = 0; j < collection.at(i).size(); j++) //in this document, go through each word
		{
			asum += (collection.at(i).at(j).getTfidf() * collection.at(i).at(j).getTfidf()); //add each squared tfidf to sum
		}
		asum = sqrt(asum); //sqrt the document tfidf sum

		for(unsigned int j = 0; j < query.size(); j++) //in this document, go through each query word
		{
			bsum += (query.at(j).getTfidf() * query.at(j).getTfidf());	//same as asum
		}
		bsum = sqrt(bsum);
		collection.at(i).at(0).cosineSimilarity.denominator = asum * bsum; //set denominator of first element of each document (asum times bsum equals denominator)
	}
}

void Tfidfs::printRelevantCosineSimilarity(articles A){
	std::sort(collection.begin(), collection.end(), []( std::vector<Tfidf> a, std::vector<Tfidf> b ){ return a.at(0).getCosine() > b.at(0).getCosine(); } ); //sorts each document by cosine similarity
	std::cout << "The top 5 most similar documents are:" << std::endl;

	for(unsigned int i = 0; i < collection.size(); i++)
	{
		for(unsigned int j = 0; j < collection.at(i).size(); j++)
		{
			for(unsigned int k = 0; k < A.articleList.size(); k++)
			{
				if(collection.at(i).at(j).getDocnum() == k)
					collection.at(i).at(j).setDocnum(stoi(A.articleList.at(k)->getID()) - 1);
			}
		}
	}


	for(unsigned int i = 0; i < 5 && i < collection.size(); i++)
	{
		if(collection.at(i).at(0).cosineSimilarity.cosine != 0)
		{
			std::cout << "Document " << collection.at(i).at(0).getDocnum()+1 << ": " << collection.at(i).at(0).cosineSimilarity.cosine	<< std::endl;
		}
	}
}

void Tfidfs::calculateCosineSimilarities(articles A){	//calculates numerator and denominator, then sets cosine similarity
	calculateCosineNumerators();
	calculateCosineDenominators();
	for(unsigned int i = 0; i < collection.size(); i++)
	{
		if(collection.at(i).at(0).cosineSimilarity.denominator == 0)
		{
			collection.at(i).at(0).cosineSimilarity.cosine = 0;
		}
		else
		{
			collection.at(i).at(0).cosineSimilarity.cosine = collection.at(i).at(0).cosineSimilarity.numerator / collection.at(i).at(0).cosineSimilarity.denominator; //just divides numerator by denominator
		}
	}
	printRelevantCosineSimilarity(A);
}
