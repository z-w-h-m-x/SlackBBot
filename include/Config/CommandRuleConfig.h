/*# 命名规则
1.不同关键词之间用 ```_``` 连接
2.ARG作为主关键词，放在开头
    eg. ARG_XXX
3.二级关键词列表
|-  Name    参数名称
|-  Port    端口（同Name）
|-  Target  触发词（命令行）
|-  Host    主机(ip)(同Name)
|-  RP      ReceiveParameters
*/

//临时配置

//  上报服务器端口
#define ARG_Port_ReportServer "PRS"
#define ARG_Target_Port_ReportServer_T1 "--ReportServerPort"
#define ARG_Target_Port_ReportServer_T2 "-RSP"
#define ARG_RP_PRS true
#define ARG_Description_Port_ReportServer "上报事件的服务端口"

//  上报服务器主机host
#define ARG_Host_ReportServer "HRS"
#define ARG_Target_Host_ReportServer_T1 "--ReportServerHost"
#define ARG_Target_Host_ReportServer_T2 "-RSH"
#define ARG_RP_HRS true
#define ARG_Description_Host_ReportServer "上报事件的服务主机"

//  NapCatQQ端口
#define ARG_Port_NapServer "NAPP"
#define ARG_Target_Port_NapServer "--NapServerPort"
#define ARG_RP_NapP true
#define ARG_Description_Port_NapServer "NapCatQQ的连接端口"

//  NapCatQQ主机host
#define ARG_Host_NapServer "NAPH"
#define ARG_Target_Host_NapServer "--NapServerHost"
#define ARG_RP_NapH true
#define ARG_Description_Host_NapServer "NapCatQQ的连接主机"

//命令
#define ARG_Save_Config "SaveConfig"
#define ARG_Target_Save_Config "--save"
#define ARG_Description_Save_config "是否保存参数"
#define ARG_RP_Save false