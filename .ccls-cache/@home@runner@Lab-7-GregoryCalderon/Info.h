#ifndef INFO
#define INFO

#include <string>
using namespace std;


class Info {
  public:
    Info(string n_word="", int wrdCnt=0);
    void SetWord(string n_word);
    void SetCnt(int n_cnt);
    void IncrementCnt();
    string GetWord() const;
    int GetCnt() const;

    string ToString() const;



  private: 
    string word;
    int wrdCnt=0;

  
};

#endif
