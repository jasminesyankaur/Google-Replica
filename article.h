#ifndef _ARTICLE_H_
#define _ARTICLE_H_

#include<iostream>
#include<string>
#include<vector>
#include<fstream>

using namespace std;

class article
{
  private:
    string idnum;
    string title;                       //private variables for article class
    string authors;
    string abstract;
  public:
    void setID(string iDnum);             //set and get functions
    string getID();
    void setTitle(string Title);
    string getTitle();
    void setAuthor(string Authors);
    string getAuthor();
    void setAbstract(string Abstract);
    string getAbstract();
};

#endif
