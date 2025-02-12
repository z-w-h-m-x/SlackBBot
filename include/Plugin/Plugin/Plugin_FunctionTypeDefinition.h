#pragma once

/*
下划线前是返回类型，下划线后是参数类型（多个参数直接拼接）

V=void  B=bool  Str=string  I=int   D=double    F=float

*/

typedef void (*V_Str)(const char *);

typedef bool (*B_Str)(const char *);

typedef char * (C_V)();