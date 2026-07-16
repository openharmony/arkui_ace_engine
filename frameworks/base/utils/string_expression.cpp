/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "base/utils/string_expression.h"

#include <regex>

#include "base/log/log_wrapper.h"
#include "base/utils/string_utils.h"

namespace OHOS::Ace::StringExpression {
void InitMapping(std::map<std::string, int>& mapping)
{
    mapping["+"] = 0;
    mapping["-"] = 0;
    mapping["*"] = 1;
    mapping["/"] = 1;
    mapping["("] = 2;
    mapping[")"] = 2;
}

bool CheckCalcIsValid(const std::string& formula)
{
    std::string formulaNoSpace;
    formulaNoSpace.reserve(formula.size());
    for (char c : formula) {
        if (c != ' ') {
            formulaNoSpace += c;
        }
    }

    auto isOperator = [](char c) { return c == '+' || c == '-' || c == '*' || c == '/'; };
    size_t pos = 0;
    while (pos < formulaNoSpace.size()) {
        size_t matchStart = std::string::npos;
        size_t matchEnd = 0;
        for (size_t i = pos; i < formulaNoSpace.size(); ++i) {
            if (!isOperator(formulaNoSpace[i])) {
                continue;
            }
            size_t j = i + 1;
            while (j < formulaNoSpace.size() && formulaNoSpace[j] == '(') {
                ++j;
            }
            if (j + 4 <= formulaNoSpace.size() && formulaNoSpace.compare(j, 4, "calc") == 0) {
                matchStart = i;
                matchEnd = j + 4;
                break;
            }
        }
        if (matchStart == std::string::npos) {
            return true;
        }
        size_t leftBracketCount = 0;
        size_t rightBracketCount = 0;
        for (size_t k = matchEnd; k < formulaNoSpace.size(); ++k) {
            if (formulaNoSpace[k] == '(') {
                ++leftBracketCount;
            } else if (formulaNoSpace[k] == ')') {
                ++rightBracketCount;
            }
        }
        if (leftBracketCount == rightBracketCount) {
            return false;
        }
        pos = matchEnd;
    }
    return true;
}

void ReplaceSignNumber(std::string& formula)
{
    std::regex pattern("(\\-|\\+)\\d+(\\.\\d+)?");
    std::smatch result;
    std::string matchStr;
    std::string catStr;
    std::string mergeStr;
    std::string leftstr = formula;
    while (std::regex_search(leftstr, result, pattern)) {
        if (result.size() == 0) {
            break;
        }
        matchStr = result[0];
        if (matchStr.empty()) {
            break;
        }
        catStr = matchStr[0];
        catStr = " (0 " + catStr;
        catStr = catStr + " " + matchStr.substr(1) + ")";
        mergeStr += result.prefix().str() + catStr;
        leftstr = result.suffix().str();
    }
    mergeStr += leftstr;
    if (!mergeStr.empty()) {
        formula = mergeStr;
    }
}

void ReplaceSignNumberWithUnit(std::string& formula)
{
    std::regex pattern("(\\-|\\+)\\d+(\\.\\d+)?(px|vp|%|fp|lpx)");
    std::smatch result;
    std::string matchStr;
    std::string catStr;
    std::string mergeStr;
    std::string leftstr = formula;
    while (std::regex_search(leftstr, result, pattern)) {
        if (result.size() == 0) {
            break;
        }
        matchStr = result[0];
        if (matchStr.empty()) {
            break;
        }
        catStr = matchStr[0];
        catStr = " (0px " + catStr;
        catStr = catStr + " " + matchStr.substr(1) + ")";
        mergeStr += result.prefix().str() + catStr;
        leftstr = result.suffix().str();
    }
    mergeStr += leftstr;
    if (!mergeStr.empty()) {
        formula = mergeStr;
    }
}

static int8_t GetOpPriority(char op)
{
    switch (op) {
        case '+':
        case '-':
            return 0;
        case '*':
        case '/':
            return 1;
        case '(':
        case ')':
            return 2;
        default:
            return -1;
    }
}

bool PushOpStack(const std::string& formula, std::string& curNum, std::vector<std::string>& result,
    std::vector<std::string>& opStack)
{
    std::string curOp;
    for (char i : formula) {
        if (GetOpPriority(i) < 0) {
            curNum += i;
        } else {
            if (!curNum.empty()) {
                result.emplace_back(curNum);
                curNum.clear();
            }
            curOp = i;
            if (opStack.empty()) {
                opStack.emplace_back(curOp);
            } else if (curOp == "(") {
                opStack.emplace_back(curOp);
            } else if (curOp == ")") {
                while (opStack.back() != "(") {
                    result.emplace_back(opStack.back());
                    opStack.pop_back();
                    if (opStack.empty()) {
                        LOGE("ExpressionError, opStack is empty");
                        result.emplace_back("0");
                        return false;
                    }
                }
                opStack.pop_back();
            } else if (opStack.back() == "(") {
                opStack.emplace_back(curOp);
            } else if (GetOpPriority(curOp[0]) > GetOpPriority(opStack.back()[0]) && (!opStack.empty())) {
                opStack.emplace_back(curOp);
            } else {
                while ((opStack.back() != "(") && (GetOpPriority(opStack.back()[0]) >= GetOpPriority(curOp[0]))) {
                    result.emplace_back(opStack.back());
                    opStack.pop_back();
                    if (opStack.empty())
                        break;
                }
                opStack.emplace_back(curOp);
            }
        }
    }
    return true;
}

bool FilterCalcSpecialString(const std::string& formula)
{
    if (formula.empty()) {
        return false;
    }
    // check calc(100%)/2
    size_t startPos = formula.find("calc");
    size_t endPos = formula.rfind(")");
    bool isSingleCalc = (startPos == 0) && (endPos == formula.size() - 1);
    // check calc(100%())
    size_t emptyBracketPos = formula.find("()");
    bool isNotIncludeEmptyBracket = (emptyBracketPos == std::string::npos);

    return (isSingleCalc && isNotIncludeEmptyBracket);
}

void ConvertDal2Rpn(std::string formula, std::vector<std::string> &result)
{
    result.clear();
    std::vector<std::string> opStack;
    std::string curNum;
    std::regex calc("calc");
    std::regex space(" ");
    bool isValid = CheckCalcIsValid(formula);
    if (!isValid) {
        return;
    }
    ReplaceSignNumberWithUnit(formula);
    ReplaceSignNumber(formula);
    formula = regex_replace(formula, space, "");
    isValid = FilterCalcSpecialString(formula);
    if (!isValid) {
        return;
    }
    formula = regex_replace(formula, calc, "");
    bool ret = PushOpStack(formula, curNum, result, opStack);
    if (!ret) {
        return;
    }
    if (!curNum.empty()) {
        result.emplace_back(curNum);
        curNum.clear();
    }
    while (!opStack.empty()) {
        result.emplace_back(opStack.back());
        opStack.pop_back();
    }
}

bool CalculateFourOperationsExp(const std::string& exp, const Dimension& num1, const Dimension& num2,
    const std::function<double(const Dimension&)>& calcFunc, double& opRes)
{
    if (exp == "+") {
        if ((num1.Unit() == DimensionUnit::NONE && num2.Unit() != DimensionUnit::NONE) ||
            (num1.Unit() != DimensionUnit::NONE && num2.Unit() == DimensionUnit::NONE)) {
            return false;
        }
        opRes = calcFunc(num2) + calcFunc(num1);
    } else if (exp == "-") {
        if ((num1.Unit() == DimensionUnit::NONE && num2.Unit() != DimensionUnit::NONE) ||
            (num1.Unit() != DimensionUnit::NONE && num2.Unit() == DimensionUnit::NONE)) {
            return false;
        }
        opRes = calcFunc(num2) - calcFunc(num1);
    } else if (exp == "*") {
        if (num1.Unit() != DimensionUnit::NONE && num2.Unit() != DimensionUnit::NONE) {
            return false;
        }
        opRes = calcFunc(num2) * calcFunc(num1);
    } else if (exp == "/") {
        if (NearZero(calcFunc(num1))) {
            return false;
        }
        if ((num1.Unit() != DimensionUnit::NONE)) {
            return false;
        }
        opRes = calcFunc(num2) / calcFunc(num1);
    }
    return true;
}

bool CalculateExpImpl(const std::vector<std::string>& rpnexp, const std::function<double(const Dimension&)>& calcFunc,
    std::vector<Dimension>& result, double& opRes)
{
    std::string ops = "+-*/()";
    for (auto& i : rpnexp) {
        if (ops.find(i) == ops.npos) {
            std::string value = i;
            Dimension dim = StringUtils::StringToDimensionWithUnit(value, DimensionUnit::PX, 0.0f, true);
            if (dim.Unit() == DimensionUnit::INVALID) {
                return false;
            }
            result.emplace_back(dim);
        } else {
            if (result.size() <= 1) {
                return false;
            }
            Dimension num1 = result.back();
            result.pop_back();
            Dimension num2 = result.back();
            result.pop_back();
            auto ret = CalculateFourOperationsExp(i, num1, num2, calcFunc, opRes);
            if (!ret) {
                return ret;
            }
            if (num1.Unit() == DimensionUnit::NONE && num2.Unit() == DimensionUnit::NONE) {
                result.emplace_back(Dimension(opRes, DimensionUnit::NONE));
                continue;
            }
            result.emplace_back(Dimension(opRes, DimensionUnit::PX));
        }
    }
    return true;
}

double CalculateExp(const std::string& expression, const std::function<double(const Dimension&)>& calcFunc,
    const std::vector<std::string>& lengthString)
{
    std::vector<std::string> rpnexp;
    if (!lengthString.empty()) {
        rpnexp = lengthString;
    } else {
        ConvertDal2Rpn(expression, rpnexp);
    }
    std::vector<Dimension> result;
    double opRes = 0.0;
    auto ret = CalculateExpImpl(rpnexp, calcFunc, result, opRes);
    if (!ret) {
        return 0.0;
    }
    if (result.size() == 1 && result.back().Unit() != DimensionUnit::NONE) {
        return calcFunc(result.back());
    }
    return 0.0;
}
} // namespace OHOS::Ace::StringExpression
