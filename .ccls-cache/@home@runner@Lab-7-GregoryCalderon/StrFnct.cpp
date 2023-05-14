#include "StrFnct.h"

// transform to uppercase 
string TransformToUpper(string& term) {
  	transform(
 		term.begin(),
 		term.end(),
 		term.begin(),
 		::toupper);
  return term;
}