#ifndef __MYPATTERN__
#define __MYPATTERN__
#include "MsgService.h"

class MyPattern : public Pattern{
    String c;
    public:
    MyPattern(String c);
    boolean match(const Msg& m); 
};

#endif
