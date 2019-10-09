#include "article.h"

void article::setID(string iDnum)                   //set and get functions for article class
{
  idnum = iDnum;
}
string article::getID()
{
  return idnum;
}
void article::setTitle(string Title)
{
  title = Title;
}
string article::getTitle()
{
  return title;
}
void article::setAuthor(string Authors)
{
  authors = Authors;
}
string article::getAuthor()
{
  return authors;
}
void article::setAbstract(string Abstract)
{
  abstract = Abstract;
}
string article::getAbstract()
{
  return abstract;
}
