#include "Plugin_Base.h"

iRF RegisterFunction;
iRSF RegisterSpecialFunction;
iSM BotSendMessage;
int pIndex;

Plugin_Extern void iInit(int i,iRF rf, iRSF rsf,iSM sm)
{
    pIndex = i;
    RegisterFunction = rf;
    RegisterSpecialFunction = rsf;
    BotSendMessage = sm;
}

void SubmitFunction(const char * name)
{
    RegisterFunction(pIndex,name);
}
void SubmitSpecialFunction(SpecialType type,const char * name,int parm)
{
    RegisterSpecialFunction(pIndex,name,type,parm);
}

void SubmitMessageTrigger(IMessageType mType,const char * name)
{
    RegisterSpecialFunction(pIndex,name,Message_Tirgger,mType);
}