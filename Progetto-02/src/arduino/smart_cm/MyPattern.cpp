#include "MyPattern.h"

MyPattern::MyPattern(String c){
  this->c = c;
}

boolean MyPattern ::match(const Msg& m){
    return m.getContent().startsWith(this->c);
}
