#include "Tfidfs.h"
#include "articles.h"
#include "stopwords.h"
#include "stemmingMain.h"
using namespace std;

int main(){
	articles A;
	Stopwords S;
	Tfidfs T;

	A.addArticle();

	S.initializeStopwords();

	T.calculateCollectionTfidf(Porter::runStemmerMultiple(S.rem(A)));
	T.calculateQueryTfidf();
	T.calculateCosineSimilarities(A);

    return 0;
}
