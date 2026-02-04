/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

// Define _USE_MATH_DEFINES BEFORE including. any headers that might include <cmath>
#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

#include "base/utils/string_utils.h"

#ifndef WINDOWS_PLATFORM
#include "securec.h"
#endif

#include <algorithm>
#include <cerrno>
#include <cmath>
#include <cstdlib>
#include <iomanip>

#include "ui/properties/color.h"

namespace OHOS::Ace::StringUtils {
namespace {
const size_t MAX_STRING_SIZE = 256;
} // namespace
const double RADIANS_VALUE = 2 * M_PI; // one turn means 2*pi rad
const char DEFAULT_STRING[] = "error";
const std::wstring DEFAULT_WSTRING = L"error";
const std::u16string DEFAULT_USTRING = u"error";
const std::u32string DEFAULT_U32STRING = U"error";

const std::string FormatString(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    char name[MAX_STRING_SIZE] = { 0 };
    if (vsnprintf_s(name, sizeof(name), sizeof(name) - 1, fmt, args) < 0) {
        va_end(args);
        return "";
    }
    va_end(args);
    return name;
}

bool IsAscii(const std::string& str)
{
    for (const auto& c : str) {
        if (!isascii(c)) {
            return false;
        }
    }
    return true;
}

std::u16string Str8ToStr16(const std::string& str)
{
    if (str == DEFAULT_STRING) {
        return DEFAULT_USTRING;
    }
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> convert(DEFAULT_STRING, DEFAULT_USTRING);
    std::u16string result = convert.from_bytes(str);
    return result == DEFAULT_USTRING ? u"" : result;
}

std::string Str16ToStr8(const std::u16string& str)
{
    if (str == DEFAULT_USTRING) {
        return DEFAULT_STRING;
    }
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> convert(DEFAULT_STRING);
    std::string result = convert.to_bytes(str);
    return result == DEFAULT_STRING ? "" : result;
}

std::wstring ToWstring(const std::string& str)
{
    if (str == DEFAULT_STRING) {
        return DEFAULT_WSTRING;
    }
#ifdef PREVIEW
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> convert(DEFAULT_STRING, DEFAULT_WSTRING);
#elif WINDOWS_PLATFORM
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> convert(DEFAULT_STRING, DEFAULT_WSTRING);
#else
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> convert(DEFAULT_STRING, DEFAULT_WSTRING);
#endif
    std::wstring result = convert.from_bytes(str);
    return result == DEFAULT_WSTRING ? L"" : result;
}

std::string ToString(const std::wstring& str)
{
    if (str == DEFAULT_WSTRING) {
        return DEFAULT_STRING;
    }
#ifdef PREVIEW
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> convert(DEFAULT_STRING);
#elif WINDOWS_PLATFORM
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> convert(DEFAULT_STRING);
#else
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> convert(DEFAULT_STRING);
#endif
    std::string result = convert.to_bytes(str);
    return result == DEFAULT_STRING ? "" : result;
}

std::u32string ToU32string(const std::string& str)
{
    if (str == DEFAULT_STRING) {
        return DEFAULT_U32STRING;
    }
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> convert(DEFAULT_STRING, DEFAULT_U32STRING);
    std::u32string result = convert.from_bytes(str);
    return result == DEFAULT_U32STRING ? U"" : result;
}

std::string U32StringToString(const std::u32string& str)
{
    if (str == DEFAULT_U32STRING) {
        return DEFAULT_STRING;
    }
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> convert(DEFAULT_STRING);
    std::string result = convert.to_bytes(str);
    return result == DEFAULT_STRING ? "" : result;
}

bool IsNumber(const std::string& value)
{
    if (value.empty()) {
        return false;
    }
    return std::all_of(value.begin(), value.end(), [](char i) { return isdigit(i); });
}

bool IsFloat(const std::string& s)
{
    if (s.empty()) {
        return false;
    }
    int dot_count = 0;
    bool all_valid = std::all_of(s.begin(), s.end(), [&](char c) {
        if (c == '.') {
            dot_count++;
            return true;
        }
        return std::isdigit(static_cast<unsigned char>(c)) != 0;
    });
    if (!all_valid || dot_count > 1) {
        return false;
    }
    return s != "." && s != ".." && std::any_of(s.begin(), s.end(), ::isdigit);
}

void ReplaceSpace(std::string& data)
{
    bool isFirstSpace = true;
    auto iter = data.begin();
    while (iter != data.end()) {
        if (*iter == ' ') {
            if (isFirstSpace) {
                iter++;
                isFirstSpace = false;
            } else {
                iter = data.erase(iter);
            }
        } else if (*iter == '\t') {
            *iter = ' ';
        } else {
            isFirstSpace = true;
            iter++;
        }
    }
}

void ReplaceTabAndNewLine(std::string& data)
{
    for (auto& i : data) {
        if (i == '\r' || i == '\n') {
            i = ' ';
        }
    }
    ReplaceSpace(data);
}

std::string RestoreEscape(const std::string& src)
{
    std::string res;
    for (auto &c : src) {
        switch (c) {
            case '\n':
                res += "\\n";
                break;
            case '\r':
                res += "\\r";
                break;
            case '\t':
                res += "\\t";
                break;
            default:
                res.push_back(c);
                break;
        }
    }
    return res;
}

std::string RestoreBackslash(const std::string& src)
{
    std::string res;
    for (auto &c : src) {
        if (c != '\\') {
            res.push_back(c);
        }
    }
    return res;
}

int32_t StringToInt(const std::string& value, int64_t defaultErr)
{
    errno = 0;
    char* pEnd = nullptr;
    int64_t result = std::strtol(value.c_str(), &pEnd, 10);
    if (pEnd == value.c_str() || (result < INT_MIN || result > INT_MAX) || errno == ERANGE) {
        return defaultErr;
    } else {
        return result;
    }
}

int64_t StringToLongInt(const std::string& value, int64_t defaultErr)
{
    errno = 0;
    char* pEnd = nullptr;
    int64_t result = std::strtoll(value.c_str(), &pEnd, 10);
    if (pEnd == value.c_str() || errno == ERANGE) {
        return defaultErr;
    } else {
        return result;
    }
}

uint64_t StringToLongUint(const std::string& value, uint64_t defaultErr)
{
    errno = 0;
    char* pEnd = nullptr;
    uint64_t result = std::strtoull(value.c_str(), &pEnd, 10);
    if (pEnd == value.c_str() || errno == ERANGE) {
        return defaultErr;
    } else {
        return result;
    }
}

uint32_t StringToUintCheck(const std::string& value, uint32_t defaultErr)
{
    errno = 0;
    char* pEnd = nullptr;
    uint64_t result = std::strtoull(value.c_str(), &pEnd, 10);
    if ((pEnd == value.c_str()) || ((pEnd != nullptr) && (*pEnd != '\0')) || result > UINT32_MAX || errno == ERANGE) {
        return defaultErr;
    } else {
        return result;
    }
}

uint32_t StringToUint(const std::string& value, uint32_t defaultErr)
{
    errno = 0;
    char* pEnd = nullptr;
    uint64_t result = std::strtoull(value.c_str(), &pEnd, 10);
    if (pEnd == value.c_str() || result > UINT32_MAX || errno == ERANGE) {
        return defaultErr;
    } else {
        return result;
    }
}

double StringToDouble(const std::string& value)
{
    char* pEnd = nullptr;
    errno = 0;
    double result = std::strtod(value.c_str(), &pEnd);
    if (pEnd == value.c_str() || errno == ERANGE) {
        return 0.0;
    } else {
        return result;
    }
}

bool StringToDouble(const std::string& value, double& result)
{
    errno = 0;
    char* pEnd = nullptr;
    double res = std::strtod(value.c_str(), &pEnd);
    if (pEnd == value.c_str() || errno == ERANGE) {
        return false;
    } else if (pEnd != nullptr) {
        if (std::strcmp(pEnd, "%") == 0) {
            result = res / PERCENT_VALUE;
            return true;
        } else if (std::strcmp(pEnd, "") == 0) {
            result = res;
            return true;
        }
    }
    return false;
}

float StringToFloat(const std::string& value)
{
    errno = 0;
    char* pEnd = nullptr;
    float result = std::strtof(value.c_str(), &pEnd);
    if (pEnd == value.c_str() || errno == ERANGE) {
        return 0.0f;
    } else {
        return result;
    }
}

Dimension StringToDimensionWithUnit(const std::string& value, DimensionUnit defaultUnit,
    float defaultValue, bool isCalc)
{
    errno = 0;
    if (std::strcmp(value.c_str(), "auto") == 0) {
        return Dimension(defaultValue, DimensionUnit::AUTO);
    }
    char* pEnd = nullptr;
    double result = std::strtod(value.c_str(), &pEnd);
    if (pEnd == value.c_str() || errno == ERANGE) {
        return Dimension(defaultValue, defaultUnit);
    }
    if (pEnd != nullptr) {
        if (std::strcmp(pEnd, "%") == 0) {
            // Parse percent, transfer from [0, 100] to [0, 1]
            return Dimension(result / 100.0, DimensionUnit::PERCENT);
        }
        if (std::strcmp(pEnd, "px") == 0) {
            return Dimension(result, DimensionUnit::PX);
        }
        if (std::strcmp(pEnd, "vp") == 0) {
            return Dimension(result, DimensionUnit::VP);
        }
        if (std::strcmp(pEnd, "fp") == 0) {
            return Dimension(result, DimensionUnit::FP);
        }
        if (std::strcmp(pEnd, "lpx") == 0) {
            return Dimension(result, DimensionUnit::LPX);
        }
        if ((std::strcmp(pEnd, "\0") == 0) && isCalc) {
            return Dimension(result, DimensionUnit::NONE);
        }
        if (isCalc) {
            return Dimension(result, DimensionUnit::INVALID);
        }
    }
    return Dimension(result, defaultUnit);
}

CalcDimension StringToCalcDimension(
    const std::string& value, bool useVp, DimensionUnit defaultUnit)
{
    if (value.find("calc") != std::string::npos) {
        return CalcDimension(value, DimensionUnit::CALC);
    } else {
        if (useVp) {
            return StringToDimensionWithUnit(value, DimensionUnit::VP);
        }
        return StringToDimensionWithUnit(value, defaultUnit);
    }
}

Dimension StringToDimensionWithThemeValue(const std::string& value, bool useVp, const Dimension& themeValue)
{
    errno = 0;
    char* pEnd = nullptr;
    std::strtod(value.c_str(), &pEnd);
    if (pEnd == value.c_str() || errno == ERANGE) {
        return themeValue;
    }

    return StringToDimensionWithUnit(value, useVp ? DimensionUnit::VP : DimensionUnit::PX);
}

bool StringToDimensionWithUnitNG(const std::string& value, Dimension& dimensionResult,
    DimensionUnit defaultUnit, float defaultValue, bool isCalc)
{
    errno = 0;
    if (std::strcmp(value.c_str(), "auto") == 0) {
        dimensionResult = Dimension(defaultValue, DimensionUnit::AUTO);
        return true;
    }
    char* pEnd = nullptr;
    double result = std::strtod(value.c_str(), &pEnd);
    if (pEnd == value.c_str() || errno == ERANGE) {
        dimensionResult = Dimension(defaultValue, defaultUnit);
        return false;
    }
    if (pEnd != nullptr) {
        if (std::strcmp(pEnd, "%") == 0) {
            // Parse percent, transfer from [0, 100] to [0, 1]
            dimensionResult = Dimension(result / 100.0, DimensionUnit::PERCENT);
            return true;
        }
        if (std::strcmp(pEnd, "px") == 0) {
            dimensionResult = Dimension(result, DimensionUnit::PX);
            return true;
        }
        if (std::strcmp(pEnd, "vp") == 0) {
            dimensionResult = Dimension(result, DimensionUnit::VP);
            return true;
        }
        if (std::strcmp(pEnd, "fp") == 0) {
            dimensionResult = Dimension(result, DimensionUnit::FP);
            return true;
        }
        if (std::strcmp(pEnd, "lpx") == 0) {
            dimensionResult = Dimension(result, DimensionUnit::LPX);
            return true;
        }
        if ((std::strcmp(pEnd, "\0") == 0) && isCalc) {
            dimensionResult = Dimension(result, DimensionUnit::NONE);
            return true;
        }
        if (isCalc) {
            dimensionResult = Dimension(result, DimensionUnit::INVALID);
            return true;
        }
        if ((std::strcmp(pEnd, "\0") != 0)) {
            dimensionResult = Dimension(result, DimensionUnit::NONE);
            return false;
        }
    }
    dimensionResult = Dimension(result, defaultUnit);
    return true;
}

bool StringToCalcDimensionNG(
    const std::string& value, CalcDimension& result, bool useVp,
    DimensionUnit defaultUnit)
{
    if (value.find("calc") != std::string::npos) {
        result = CalcDimension(value, DimensionUnit::CALC);
        return true;
    } else {
        return StringToDimensionWithUnitNG(value, result, useVp ? DimensionUnit::VP : defaultUnit);
    }
}

bool UnstringifyCalcDimension(
    const std::string& value, CalcDimension& result, bool useVp,
    DimensionUnit defaultUnit)
{
    if (value.rfind("calc") != std::string::npos) {
        auto valueNum = value.substr(0, value.rfind("calc"));
        result = CalcDimension(valueNum, DimensionUnit::CALC);
        return true;
    } else if (value.rfind("auto") != std::string::npos) {
        result = Dimension(0.0f, DimensionUnit::AUTO);
        return true;
    } else {
        return StringToDimensionWithUnitNG(value, result, useVp ? DimensionUnit::VP : defaultUnit);
    }
}

std::string ReplaceChar(std::string str, char old_char, char new_char)
{
    for (char& it : str) {
        if (it == old_char) {
            it = new_char;
        }
    }
    return str;
}

double StringToDegree(const std::string& value)
{
    // https://developer.mozilla.org/zh-CN/docs/Web/CSS/angle

    errno = 0;
    char* pEnd = nullptr;
    double result = std::strtod(value.c_str(), &pEnd);
    if (pEnd == value.c_str() || errno == ERANGE) {
        return 0.0;
    } else if (pEnd) {
        if ((std::strcmp(pEnd, "deg")) == 0) {
            return result;
        } else if (std::strcmp(pEnd, "grad") == 0) {
            return result / GRADIANS_VALUE * DEGREES_VALUE;
        } else if (std::strcmp(pEnd, "rad") == 0) {
            return result / RADIANS_VALUE * DEGREES_VALUE;
        } else if (std::strcmp(pEnd, "turn") == 0) {
            return result * DEGREES_VALUE;
        }
    }
    return StringToDouble(value);
}

bool StringToDegree(const std::string& value, double& result)
{
    errno = 0;
    char* pEnd = nullptr;
    double temp = std::strtod(value.c_str(), &pEnd);
    if (pEnd == value.c_str() || errno == ERANGE) {
        return false;
    } else if (pEnd) {
        if (*pEnd == '\0') {
            result = temp;
            return true;
        }
        if (std::strcmp(pEnd, "deg") == 0) {
            result = temp;
            return true;
        }
        if (std::strcmp(pEnd, "grad") == 0) {
            result = temp / GRADIANS_VALUE * DEGREES_VALUE;
            return true;
        }
        if (std::strcmp(pEnd, "rad") == 0) {
            result = temp / RADIANS_VALUE * DEGREES_VALUE;
            return true;
        }
        if (std::strcmp(pEnd, "turn") == 0) {
            result = temp * DEGREES_VALUE;
            return true;
        }
    }
    return false;
}

bool ParseStringToArray(const std::string& input, std::vector<float>& output)
{
    std::istringstream iss(StringUtils::ReplaceChar(input, ',', ' '));
    std::string token;

    while (iss >> token) {
        double value;
        if (!StringToDouble(token, value)) {
            return false;
        }
        output.emplace_back(value);
    }

    return true;
}

std::string DoubleToString(double value, int32_t precision)
{
    std::ostringstream result;
    result.precision(precision);
    if (NearEqual(value, Infinity<double>())) {
        result << "Infinity";
    } else {
        result << std::fixed << value;
    }
    return result.str();
}

std::string TrimStr(const std::string& str, char cTrim)
{
    auto firstPos = str.find_first_not_of(cTrim);
    if (firstPos == std::string::npos) {
        return str;
    }
    auto endPos = str.find_last_not_of(cTrim);
    return str.substr(firstPos, endPos - firstPos + 1);
}

void TrimStrLeadingAndTrailing(std::string& str, char cTrim)
{
    auto firstIndexNotOfSpace = str.find_first_not_of(" ");
    if (firstIndexNotOfSpace == std::string::npos) {
        str = "";
        return;
    }
    str.erase(0, firstIndexNotOfSpace);
    auto lastIndexNotOfSpace = str.find_last_not_of(" ");
    if (lastIndexNotOfSpace == std::string::npos) {
        str = "";
        return;
    }
    str.erase(lastIndexNotOfSpace + 1);
}

void SplitStr(
    const std::string& str, const std::string& sep, std::vector<std::string>& out, bool needTrim)
{
    out.erase(out.begin(), out.end());

    if (str.empty() || sep.empty()) {
        return;
    }

    std::string strPart;
    std::string::size_type startPos = 0;
    std::string::size_type pos = str.find_first_of(sep, startPos);
    while (pos != std::string::npos) {
        if (pos > startPos) {
            strPart = needTrim ? TrimStr(str.substr(startPos, pos - startPos)) : str.substr(startPos, pos - startPos);
            out.emplace_back(std::move(strPart));
        }
        startPos = pos + sep.size();
        pos = str.find_first_of(sep, startPos);
    }

    if (startPos < str.size()) {
        strPart = needTrim ? TrimStr(str.substr(startPos)) : str.substr(startPos);
        out.emplace_back(std::move(strPart));
    }
}

void SplitStr(const std::string& str, const std::string& sep, std::vector<Dimension>& out, bool needTrim)
{
    out.erase(out.begin(), out.end());
    if (str.empty() || sep.empty()) {
        return;
    }
    std::string strPart;
    std::string::size_type startPos = 0;
    std::string::size_type pos = str.find_first_of(sep, startPos);
    while (pos != std::string::npos) {
        if (pos > startPos) {
            strPart = needTrim ? TrimStr(str.substr(startPos, pos - startPos)) : str.substr(startPos, pos - startPos);
            if (!strPart.empty()) {
                out.emplace_back(StringToDimension(std::move(strPart)));
            }
        }
        startPos = pos + sep.size();
        pos = str.find_first_of(sep, startPos);
    }
    if (startPos < str.size()) {
        strPart = needTrim ? TrimStr(str.substr(startPos)) : str.substr(startPos);
        if (!strPart.empty()) {
            out.emplace_back(StringToDimension(std::move(strPart)));
        }
    }
}

bool CStringEqual(const char* first, const char* second)
{
    if (first == nullptr && second == nullptr) {
        return true;
    }
    if (first && second) {
        return std::strcmp(first, second) == 0;
    }
    return false;
}

// StringSplitter template function implementation
template<class T>
ACE_FORCE_EXPORT
void StringSplitter(
    const std::string& source, char delimiter, T (*func)(const std::string&), std::vector<T>& out)
{
    out.erase(out.begin(), out.end());

    if (source.empty()) {
        return;
    }

    std::size_t startIndex = 0;
    for (std::size_t index = 0; index < source.size(); index++) {
        if (source[index] == delimiter) {
            if (startIndex < index) {
                out.emplace_back(func(source.substr(startIndex, index - startIndex)));
            }
            startIndex = index + 1;
        }
    }
    if (startIndex < source.size()) {
        out.emplace_back(func(source.substr(startIndex)));
    }
}

// Explicit template instantiations for StringSplitter
template void StringSplitter<std::string>(const std::string& source, char delimiter, std::string (*)(const std::string&), std::vector<std::string>& out);
template void StringSplitter<double>(const std::string& source, char delimiter, double (*)(const std::string&), std::vector<double>& out);
template void StringSplitter<float>(const std::string& source, char delimiter, float (*)(const std::string&), std::vector<float>& out);
template void StringSplitter<int32_t>(const std::string& source, char delimiter, int32_t (*)(const std::string&), std::vector<int32_t>& out);
template void StringSplitter<Dimension>(const std::string& source, char delimiter, Dimension (*)(const std::string&), std::vector<Dimension>& out);
template void StringSplitter<Color>(const std::string& source, char delimiter, Color (*)(const std::string&), std::vector<Color>& out);

// StringSplitter wrapper functions
void StringSplitter(const std::string& source, char delimiter, std::vector<std::string>& out)
{
    using Func = std::string (*)(const std::string&);
    Func func = [](const std::string& value) { return value; };
    StringSplitter(source, delimiter, func, out);
}

void StringSplitter(const std::string& source, char delimiter, std::vector<double>& out)
{
    using Func = double (*)(const std::string&);
    Func func = [](const std::string& value) { return StringToDouble(value); };
    StringSplitter(source, delimiter, func, out);
}

void StringSplitter(const std::string& source, char delimiter, std::vector<float>& out)
{
    using Func = float (*)(const std::string&);
    Func func = [](const std::string& value) { return StringToFloat(value); };
    StringSplitter(source, delimiter, func, out);
}

void StringSplitter(const std::string& source, char delimiter, std::vector<int>& out)
{
    using Func = int32_t (*)(const std::string&);
    Func func = [](const std::string& value) { return StringToInt(value); };
    StringSplitter(source, delimiter, func, out);
}

void StringSplitter(const std::string& source, char delimiter, std::vector<Dimension>& out)
{
    using Func = Dimension (*)(const std::string&);
    Func func = [](const std::string& value) { return StringToDimension(value); };
    StringSplitter(source, delimiter, func, out);
}

// Template function implementation
template<typename T>
ACE_FORCE_EXPORT
void TransformStrCase(T& str, int32_t textCase)
{
    if (str.empty()) {
        return;
    }

    switch (textCase) {
        case TEXT_CASE_LOWERCASE:
            std::transform(str.begin(), str.end(), str.begin(), ::tolower);
            break;
        case TEXT_CASE_UPPERCASE:
            std::transform(str.begin(), str.end(), str.begin(), ::toupper);
            break;
        default:
            break;
    }
}

// Explicit template instantiations
template void TransformStrCase(std::string& str, int32_t textCase);
template void TransformStrCase(std::wstring& str, int32_t textCase);
template void TransformStrCase(std::u16string& str, int32_t textCase);

} // namespace OHOS::Ace::StringUtils