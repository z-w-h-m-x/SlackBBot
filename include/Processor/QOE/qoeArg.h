#pragma once

/*
这是一个史山，能用，也就仅限能用很多功能都没有（例如错误的tag提示、对于引号处理）
It works, but only if it works. Many features are missing (such as error tag hints, handling of quotation marks).
*/

#include <string>
#include <map>
#include <vector>

#define qoeCArgNull "qoe__NULL__ERROR__"

using std::map;
using std::string;
using std::vector;

namespace qoe
{
    using commandArgData = map<string, string>;

    struct qoeCommandArgRuleData
    {
        std::string argText;
        std::string argName;
        bool receiveParameters;
    };

    bool CommandInCommandArgRule(string text, vector<qoeCommandArgRuleData> &rules);

    qoeCommandArgRuleData _qoeCommandArgRuleData(std::string argText, std::string argName, bool receiveParameters);

    extern vector<qoeCommandArgRuleData> commandArgRule;

    void addCommandRule(string argText, string argName, bool receiveParameters);

    map<string, string> AnalysisArgOptToMap(int _argC, char *_argV[]);

    bool CommandInCommandArgRule(string text, vector<qoeCommandArgRuleData> &rules);

}
