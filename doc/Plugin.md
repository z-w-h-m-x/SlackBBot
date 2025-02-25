# Plugin

this is a doc to guide that how to create a plugin for this program

这是个指导如何创建插件的文档

## language / 语言

简体中文(在这)  [(WIP)English](./en/Plugin.md)

## （快速跳转）目录

- [前提条件](#前提条件)
- [插件分类](#插件分类)
- [结构定义](#结构定义)
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

## 方法/函数分类

附：这部分供统计使用。实际不需要用到。

|名称类别|枚举值|功能|备注|
|-|-|-|-|
|custom|0|功能为自定义插件|暂时保留|
|init|1|初始化函数
|filter|2|过滤器
|action|3|行为|例如戳一戳，好友添加申请
|message|4|聊天消息
|notice|5|系统消息

## 结构定义

### slb::

#### MessageContent

in MessageDefinition.h

## 插件接口定义

### Base

该部分已有在``Plugin_Base.h``中定义，引用该头文件只需要定义即可

|函数名|返回值类型|参数，<参数>...|作用（功能）|
|:-|:-:|:-:|:-|
PluginName|const char *|-|给主程序插件名
Init|void|-|插件初始化
~~Start~~|void|int index|~~插件启动~~

#### Start

无返回值

参数

|参数名|类型|作用
|-|-|-|
index|int|插件唯一序号，类似于ID

### fillter
|函数名|返回值类型|参数，<参数>...|作用（功能）|
|:-|:-:|:-:|:-|
[Fillter_AfterReceiveMessage](#fillter通用)|Bool|slb::MessageContent|作用于收到消息后
~~[Fillter_BeforeIntoRoom](#fillter通用)~~|Bool|slb::MessageContent|作用于消息进入“房间”之前
[Fillter_BeforeSendMessage](#fillter通用)|Bool|slb::MessageContent|作用于在发出消息

#### Fillter通用

|返回值|意义|
|-|-|
true|通过（允许向下传递）
false|过滤

```cpp
bool Fillter_XXXXX(MessageContent message)
{
    bool _returnValue = true;
    /*Code*/
    return _returnValue;
}
```

### 特殊

#### Message的关键词匹配相关

|函数名|返回值类型|参数，<参数>...|作用（功能）|
|:-|:-:|:-:|:-|
任意|void|slb::MessageContent|匹配到关键词触发调用

#### Message消息处理组相关

关键词无匹配则触发此分类，传递执行

|函数名|返回值类型|参数，<参数>...|作用（功能）|
|:-|:-:|:-:|:-|
任意|bool|slb::MessageContent|没匹配到关键词时触发（返回值为真允许传递执行下一个，逆否）

## 程序接口定义

### Room
|函数名|返回值类型|参数，<参数>...|作用（功能）|
|:-|:-:|:-:|:-|
~~[Room_RegisterNewStaus](#Room_RegisterNewStaus)~~|bool|String|注册状态

### Plugin

|函数名|返回值类型|参数，<参数>...|作用（功能）|
|:-|:-:|:-:|:-|
RegisterFunction|-|int index,const char * name|注册函数/功能