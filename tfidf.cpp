#include "Tfidf.h"

Tfidf::Tfidf(){
        word = "";
        docNum = 0.0;
        tf = 0.0;
        nt = 0.0;
        n = 0.0;
        tfidf = 0.0;
        cosineSimilarity.numerator = 0.0;
        cosineSimilarity.denominator = 0.0;
        cosineSimilarity.cosine = 0.0;

}

Tfidf::Tfidf(std::string cword, double cdocNum, double cN){
        word = cword;
        docNum = cdocNum;
        tf = 0.0;
        nt = 0.0;
        n = cN;
        tfidf = 0.0;
        cosineSimilarity.numerator = 0.0;
        cosineSimilarity.denominator = 0.0;
        cosineSimilarity.cosine = 0.0;

}
std::string Tfidf::getWord(){
    return word;
}

double Tfidf::getDocnum(){
    return docNum;
}

double Tfidf::getTf(){
    return tf;
}

double Tfidf::getNt(){
    return nt;
}

double Tfidf::getN(){
    return n;
}

double Tfidf::getTfidf(){
    return tfidf;
}

double Tfidf::getCosine(){
    return cosineSimilarity.cosine;
}

void Tfidf::setTf(double sTf){
    tf = sTf;
}

void Tfidf::setNt(double sNt){
    nt = sNt;
}

void Tfidf::setN(double sN){
    n = sN;
}
void Tfidf::setDocnum(int d){
	docNum = d;
}

void Tfidf::calculateTfidf(){	//calculates tfidf by using tf, n and nt. if nt is 0, tfidf is also 0 to protect against division by 0
	if(nt == 0)
	{
		tfidf = 0;
	}
	else
	{
		tfidf = tf * log(n/nt);
	}
}
