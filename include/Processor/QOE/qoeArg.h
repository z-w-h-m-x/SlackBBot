#pragma once

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
