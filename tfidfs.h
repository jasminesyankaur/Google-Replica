#ifndef TFIDFS_H
#define TFIDFS_H
#include "Tfidf.h"


class Tfidfs{

public:
void populateCollection(std::vector<std::vector<std::string>> wordsIn);
void assignCollectionTf();
void assignCollectionNt();
void printFirstDoc();
void calculateCollectionTfidf(std::vector<std::vector<std::string>> temp);
void removeCollectionDuplicates();

void addQuery();
void trimQuery();
void populateQuery();
void assignQueryTf();
void assignQueryN();
void assignQueryNt();
void removeQueryDuplicates();
void calculateQueryTfidf();

double returnTfidfByWordAndDocument(std::string word, int document);
void calculateCosineNumerators();
void calculateCosineDenominators();
void printRelevantCosineSimilarity(articles A);
void calculateCosineSimilarities(articles A);

private:
std::vector<std::vector<Tfidf>> collection;    //list of tfidf classes
std::vector<Tfidf> query;						//list of tfidf classes for query
std::vector<std::vector<std::string>> words;	// list of each document and their words
std::vector<std::string> queryStrings;
};
#endif

