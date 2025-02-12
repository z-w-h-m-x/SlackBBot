#include "Plugin_Base.h"

iRF RegisterFunction;
iRSF RegisterSpecialFunction;
iSM SendMessage;
int index;

Plugin_Extern void iInit(int i,iRF rf, iRSF rsf,iSM sm)
{
    index = i;
    RegisterFunction = rf;
    RegisterSpecialFunction = rsf;
    SendMessage = sm;
}

void SubmitFunction(const char * name)
{
    RegisterFunction(index,name);
}
void SubmitSpecialFunction(SpecialType type,const char * name,const char * parm)
{
    RegisterSpecialFunction(index,name,type,parm);
}