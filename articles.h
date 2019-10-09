#ifndef _ARTICLES_H_
#define _ARTICLES_H_

#include "article.h"
#include<sstream>

class articles
{
  public:
    vector<article*> articleList;         //Holds all the articles
    int Count(string numwords);           //returns num words in a string
    void addArticle();                    //add article function
};

#endif

