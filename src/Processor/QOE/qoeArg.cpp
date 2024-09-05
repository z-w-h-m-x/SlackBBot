#include "Processor/QOE/qoeArg.h"

namespace qoe
{
    using commandArgData = map<string, string>;

    bool CommandInCommandArgRule(string text, vector<qoeCommandArgRuleData> &rules);

    qoeCommandArgRuleData _qoeCommandArgRuleData(std::string argText, std::string argName, bool receiveParameters)
    {
        qoeCommandArgRuleData a;
        a.argName = argName;
        a.argText = argText;
        a.receiveParameters = receiveParameters;
        return a;
    };

    vector<qoeCommandArgRuleData> commandArgRule;

    void addCommandRule(string argText, string argName, bool receiveParameters)
    {
        commandArgRule.push_back(_qoeCommandArgRuleData(argText, argName, receiveParameters));
    }

    map<string, string> AnalysisArgOptToMap(int _argC, char *_argV[])
    {
        map<string, string> _data;
        bool skip = false;

        if (_argC == 0)
        {
            return _data;
        }
        if (_argC == 1)//if dont have commands,set skip 
        {
            skip = true;
        }
        int configCount = commandArgRule.size();
        for (int p = 0, i = 1; p < configCount; p++)//根据规则遍历参数
        {
            i=1;//keep the line.编译器差异需要保底
            if (skip)//if dont have commands,skiped 
            {
                _data[commandArgRule[p].argName] = qoeCArgNull;
            }
            else
            {
                for (; i < _argC; i++)
                {
                    if (_argV[i] == commandArgRule[p].argText)//参数命中规则
                    {
                        if (commandArgRule[p].receiveParameters)//是否为开关
                        {
                            if (i == _argC)//寻找后面的参数
                            {
                                _data[commandArgRule[p].argName] = qoeCArgNull;
                                break;
                            }
                            else
                            {
                                int ix = i + 1;
                                if (ix >= _argC)
                                {
                                    _data[commandArgRule[p].argName] = qoeCArgNull;
                                    break;
                                }
                                else
                                {
                                    if (CommandInCommandArgRule(_argV[i + 1], commandArgRule))
                                    {
                                        _data[commandArgRule[p].argName] = qoeCArgNull;
                                        break;
                                    }
                                    else
                                    {
                                        _data[commandArgRule[p].argName] = _argV[i + 1];
                                        i++;
                                        break;
                                    }
                                }
                            }
                        }
                        else
                        {
                            _data[commandArgRule[p].argName] = "1";
                            break;
                        }
                    }
                    else
                    {
                        if (commandArgRule[p].receiveParameters)
                        {
                            if (_data.count(commandArgRule[p].argName) != 0) {/*skip*/}
                            else _data[commandArgRule[p].argName] = qoeCArgNull;//没有定义才赋值
                        }
                        else
                        {
                            if (_data.count(commandArgRule[p].argName) != 0) {/*skip*/}
                            else _data[commandArgRule[p].argName] = "0";//同上
                        }
                    }
                }
            }
        }

        return _data;
    }

    bool CommandInCommandArgRule(string text, vector<qoeCommandArgRuleData> &rules)
    {
        for (int i = 0; i < rules.size(); i++)
        {
            if (rules[i].argText == text)
            {
                return true;
            }
        }
        return false;
    }


}

