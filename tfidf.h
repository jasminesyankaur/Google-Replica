#ifndef TFIDF_H
#define TFIDF_H

#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iterator>
#include "articles.h"
#include "stemmingMain.h"
#include "stopwords.h"

class Tfidf{
friend class Tfidfs;

public:	//Constructors and getters/setters
Tfidf();
Tfidf(std::string cword, double cdocNum, double cN);  //Builds default class with 2d vector info
struct cosineFraction {		//struct template for cosine similarity needs
	double numerator;
	double denominator;
	double cosine;
};
std::string getWord();
double getDocnum();
double getTf();
double getNt();
double getN();
double getTfidf();
double getCosine();
void setTf(double sTf);
void setNt(double sNt);
void setN(double sN);
void setDocnum(int d);
void calculateTfidf();

private:
std::string word;
int docNum;     //Document number word is in
double tf;         //Amount of times word is in current document
double nt;         //Amount of documents the word is in
double n;          //Amount of documents
double tfidf;	//Final tfidf score
cosineFraction cosineSimilarity; //struct variable for cosine similarity
};
#endif

