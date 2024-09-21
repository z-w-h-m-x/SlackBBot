# Plugin

this is a doc to guide that how to create a plugin for this program

这是个指导如何创建插件的文档

## language / 语言

简体中文(在这)  [(WIP)English](./en/Plugin.md)

## （快速跳转）目录

- [前提条件](#前提条件)
- [插件分类](#插件分类)
- [插件接口定义](#插件接口定义)
- [程序接口定义](#程序接口定义)

## 免责声明

- 软件并不提供任何可以使用的API，并不具备实际性应答能力，请勿用于违法犯罪

- 代码仅供交流学习，后果自负，作者概不负责

## 前提条件

任意C/C++开发环境，本程序完整版（指需要有include目录）

当然你也可以选择其他语言。但是比较麻烦（需另外实现读取）

## 安全提醒

请勿使用你不信任的插件，因为插件的特殊性可能有点```问题```。使用过程须注意信息安全，记得防毒。

## 提示

> 题外话，为什么不用插件工厂？ 对啊，为什么啊。可能是自由度不太高吧

插件开发常用功能和插件必须已经提供在程序目录下的 include/${ProjectName}/Plugin 下

当前版本ProjectName为SlackBot

头文件中已定义导出，还有程序的API

看不懂写什么？去看示例！

## 插件分类

|名称类别|枚举值|功能|备注|
|-|-|-|-|
|custom|0|功能为自定义插件|暂时保留|
|filter|2|过滤器
|action|3|行为|例如戳一戳，好友添加申请

## 插件接口定义

对应[分类](#插件分类)所须实现的函数

custom可定义以下的一个或多个任意函数

### fillter
|函数名|返回值类型|参数，<参数>...|作用（功能）|
|:-|:-:|:-:|:-|
[Fillter_AfterReceiveMessage](#fillter通用)|Bool|slb::ChatMessage|作用于收到消息后
[Fillter_BeforeIntoRoom](#fillter通用)|Bool|slb::ChatMessage|作用于消息进入房间之前

#### Fillter通用

|返回值|意义|
|-|-|
true|通过（允许向下传递）
false|过滤

```cpp
bool Fillter_XXXXX(ChatMessage message)
{
    bool _returnValue = true;
    /*Code*/
    return _returnValue;
}
```

## 程序接口定义

### Room
|函数名|返回值类型|参数，<参数>...|作用（功能）|
|:-|:-:|:-:|:-|
[Room_RegisterNewStaus](#Room_RegisterNewStaus)|bool|String|注册状态

#### Room_RegisterNewStaus

|返回值|意义|
|-|-|
true|成功
false|失败（存在冲突）

```cpp
bool Room_RegisterNewStaus(string stausName);
```