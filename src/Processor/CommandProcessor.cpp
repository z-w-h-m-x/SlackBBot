#include "Processor/CommandProcessor.h"

#include <iostream>

#include "GlobalData.h"

#include "Config/CommandRuleConfig.h"

void RegisterCommandRule()
{
    using namespace qoe;
    //临时配置
    addCommandRule(ARG_Target_Port_ReportServer_T1,ARG_Port_ReportServer,ARG_RP_PRS);
    addCommandRule(ARG_Target_Port_ReportServer_T2,ARG_Port_ReportServer,ARG_RP_PRS);
    addCommandRule(ARG_Target_Port_NapServer,ARG_Port_NapServer,ARG_RP_NapP);

    addCommandRule(ARG_Target_Host_ReportServer_T1,ARG_Host_ReportServer,ARG_RP_HRS);
    addCommandRule(ARG_Target_Host_ReportServer_T2,ARG_Host_ReportServer,ARG_RP_HRS);
    addCommandRule(ARG_Target_Host_NapServer,ARG_Host_NapServer,ARG_RP_NapH);
    //测试
    addCommandRule("--test","t",false);
    //框架命令
    addCommandRule(ARG_Target_Save_Config,ARG_Save_Config,ARG_RP_Save);//保存配置
    addCommandRule(ARG_Target_DisableLogSaving,ARG_DisableLogSaving,ARG_RP_DisableLogSaving);//禁用文件日志
}

bool SetFollowCommand(qoe::commandArgData commandData)
{
    using namespace std;
    if (commandData["t"] == "1")
        cout<<"Hello,this test flag was target\n";
    //临时配置
    if (commandData[ARG_Port_ReportServer] != qoeCArgNull)
        serverConfig.port = stoi(commandData[ARG_Port_ReportServer]);
    if (commandData[ARG_Port_NapServer] != qoeCArgNull)
        serverConfig.port = stoi(commandData[ARG_Port_NapServer]);
    //命令
    if (commandData[ARG_DisableLogSaving] == "1")
        disableLogSaving = true;

    return true;
}