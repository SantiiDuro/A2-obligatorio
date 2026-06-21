#ifndef COMPETITOR_IMP
#define COMPETITOR_IMP

struct Competitior
{
    int time;
    int index;
    
    Competitior() : time(0), index(0) {}
    Competitior(int _t, int _i) : time(_t), index(_i) {}
};

#endif