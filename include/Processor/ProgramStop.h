#pragma once

/*--------------------------
 define in ProgramStop.cpp
--------------------------*/

//因为发生影响程序运行的错误而停止
extern void Stop_Error();

/*--------------------------
     define in main.cpp
--------------------------*/

//正常停止
extern void Stop();

//程序退出
extern void ProgramQuit();