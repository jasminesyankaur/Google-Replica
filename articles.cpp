#include "articles.h"

int articles::Count(string numwords)          //will return num words in a string
{
  stringstream ss(numwords);
  int Words = 0;
  while(true)
  {
    ss >> numwords;                           //while ss can read in the string
    if(!ss)
    {
        break;
    }                                          //if it cant break
    Words++;                                  //incrament words
  }
  return Words;                               //return words
}

void articles::addArticle()
{
  string idnumber;
  string titles;
  string Authors;
  string paragraph;                             //temp variables needed to store data from file
  string temp;
  string temp1;
  ifstream in_s;

  char input_file[30];
	cout << "Enter the name of the input file: ";              //opening .txt file
	cin >> input_file;

	in_s.open(input_file);

	if(in_s.fail())
	{
		cout << "Unable to open input file " << input_file << endl;
		exit(EXIT_FAILURE);
	}


    in_s >> temp1;            //reading in .I


    while(!in_s.eof())        //until eof is reached
    {
      article* artptr = new article;      //create a new pointer of article

      idnumber = " ";
      titles = " ";                        //make sure all my strings are empty
      Authors = " ";
      paragraph = " ";

      if(temp1 == ".I")           //if temp1 is .I
      {
        in_s >> temp1;            //read in ID number
        idnumber = temp1;
        artptr->setID(idnumber);      //set pointer to ID number

        in_s >> temp1;        //read in .T from document
        if(temp1 == ".T")
        {
          getline(in_s, temp1);             //use getline to read in the titles
          while(temp1 != ".A")              //until temp reads a .A
          {
            titles += temp1;                  //assign title to temp variable
            getline(in_s, temp1);              //read in next line
            titles += " ";                    //add a space
          }
          artptr->setTitle(titles);           //set pointer to title variable

          if(temp1 == ".A")
          {
            getline(in_s, temp1);           //use getline to read in the authors
            while(temp1 != ".W")            //until temp reads a .W
            {
              Authors += temp1;              //assign authors to temp variable
              getline(in_s, temp1);           //read in next line
              Authors += " ";                   //add a space
            }
            artptr->setAuthor(Authors);       //set pointer to authors

            for(int i = 0; i < Count(titles); i++)
            {
              in_s >> temp;
            }

            if(temp1 == ".W")
            {
              in_s >> temp1;
              while((!in_s.eof()) && (temp1 != ".I"))   //until the document reaches a .I or EOF
              {
                paragraph += temp1;
                in_s >> temp1;
                paragraph += " ";
              }
              artptr->setAbstract(paragraph);               //set pointer to abstract
            }
          }
        }
      }
        articleList.push_back(artptr);              //push my pointer into vector

    }


      for(int i = 0; i < 1; i++)                 //print vector
      {
          cout << "ID: " << articleList.at(i)->getID() << endl;
          cout << "Title: " << articleList.at(i)->getTitle() << endl;
          cout << "Author: " << articleList.at(i)->getAuthor() << endl;
          cout << "Abstract: " << articleList.at(i)->getAbstract() << endl;
      }
}
