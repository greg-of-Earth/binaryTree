#include "word.h"
#include <string>
#include <sstream>


using namespace std;

Word::Word(string n_word, int n_wrdCnt) {
  this->word = n_word;
  this->wrdCnt = n_wrdCnt;
}

void Word::SetWord(string n_word) {
  this->word = n_word;
}

void Word::SetCnt(int n_wrdCnt) {
  this->wrdCnt = n_wrdCnt;
}

string Word::GetWord() const {
  return word;
}

int Word::GetCnt() const {
  return wrdCnt;
}

string Word::ToString() const {
  stringstream info;
  info << "Word: " << word << " Count: " << wrdCnt;
  return info.str();
}