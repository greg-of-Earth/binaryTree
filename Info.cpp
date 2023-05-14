#include "Info.h"
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cctype>
#include "StrFnct.h"


using namespace std;

Info::Info(string n_word, int n_cnt) {
  word = n_word;
  wrdCnt = n_cnt;
}

void Info::SetWord(string n_word) {
  word = TransformToUpper(n_word);
}

void Info::SetCnt(int n_cnt) {
  wrdCnt = n_cnt;
}

void Info::IncrementCnt(){
  wrdCnt++;
}

string Info::GetWord() const {
  return word;
}

int Info::GetCnt() const {
  return wrdCnt;
}

string Info::ToString() const {
  stringstream info;
  info << word << " |" << wrdCnt;
  return info.str();
}

