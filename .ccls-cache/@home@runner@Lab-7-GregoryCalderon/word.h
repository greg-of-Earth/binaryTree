#ifndef WORD
#define WORD

#include <string>
using namespace std;


class Word {
  public:
    Word(string n_word="",int n_wrdCnt=0);
    void SetWord(string n_word);
    void SetCnt(int);
    string GetWord() const;
    int GetCnt() const;

    string ToString() const;



  private: 
    string word;
    int wrdCnt=-1;

  
};

#endif
