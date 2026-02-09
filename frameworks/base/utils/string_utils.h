/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_UTILS_STRING_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_UTILS_STRING_UTILS_H

#include <algorithm>
#include <climits>
#include <codecvt>
#include <cstring>
#include <sstream>
#include <string>
#include <vector>

#include "base/geometry/calc_dimension.h"
#include "base/geometry/dimension.h"
#include "base/utils/utils.h"

namespace OHOS::Ace {
class Color;
}

namespace OHOS::Ace::StringUtils {

ACE_FORCE_EXPORT  extern const char DEFAULT_STRING[];
ACE_FORCE_EXPORT extern const std::wstring DEFAULT_WSTRING;
ACE_FORCE_EXPORT  extern const std::u16string DEFAULT_USTRING;
ACE_EXPORT extern const std::u32string DEFAULT_U32STRING;
constexpr int32_t TEXT_CASE_LOWERCASE = 1;
constexpr int32_t TEXT_CASE_UPPERCASE = 2;
constexpr double PERCENT_VALUE = 100.0;
constexpr double DEGREES_VALUE = 360.0; // one turn means 360 deg
constexpr double GRADIANS_VALUE = 400.0; // one turn means 400 grad
const extern double RADIANS_VALUE; // one turn means 2*pi rad
const char ELLIPSIS[] = "...";

ACE_FORCE_EXPORT std::u16string Str8ToStr16(const std::string& str);

ACE_FORCE_EXPORT std::string Str16ToStr8(const std::u16string& str);

ACE_FORCE_EXPORT std::wstring ToWstring(const std::string& str);

inline bool IsLetterOrNumberForWchar(wchar_t chr)
{
    return (chr >= L'0' && chr <= L'9') || (chr >= L'a' && chr <= L'z') || (chr >= L'A' && chr <= L'Z');
}

inline bool IsLetterOrNumberForChar16(char16_t chr)
{
    return (chr >= u'0' && chr <= u'9') || (chr >= u'a' && chr <= u'z') || (chr >= u'A' && chr <= u'Z');
}

ACE_FORCE_EXPORT std::string ToString(const std::wstring& str);

std::u32string ToU32string(const std::string& str);

std::string U32StringToString(const std::u32string& str);

inline bool NotInUtf16Bmp(char16_t c)
{
    return (c & 0xF800) == 0xD800;
}

inline bool NotInBmp(wchar_t ch)
{
    return ch >= 0xD800 && ch <= 0xDBFF;
}

ACE_FORCE_EXPORT bool IsNumber(const std::string& value);
ACE_FORCE_EXPORT bool IsFloat(const std::string& s);

void ReplaceSpace(std::string& data);
void ReplaceTabAndNewLine(std::string& data);

ACE_FORCE_EXPORT std::string RestoreEscape(const std::string& src);
ACE_FORCE_EXPORT std::string RestoreBackslash(const std::string& src);

ACE_FORCE_EXPORT int32_t StringToInt(const std::string& value, int64_t defaultErr = 0);
ACE_FORCE_EXPORT int64_t StringToLongInt(const std::string& value, int64_t defaultErr = 0);
ACE_FORCE_EXPORT uint64_t StringToLongUint(const std::string& value, uint64_t defaultErr = 0);
uint32_t StringToUintCheck(const std::string& value, uint32_t defaultErr = 0);
ACE_FORCE_EXPORT uint32_t StringToUint(const std::string& value, uint32_t defaultErr = 0);

// generic string to double value method without success check
ACE_FORCE_EXPORT double StringToDouble(const std::string& value);
// string to double method with success check, and support for parsing number string with percentage case
ACE_FORCE_EXPORT bool StringToDouble(const std::string& value, double& result);
ACE_FORCE_EXPORT float StringToFloat(const std::string& value);

ACE_FORCE_EXPORT Dimension StringToDimensionWithUnit(const std::string& value, DimensionUnit defaultUnit = DimensionUnit::PX,
    float defaultValue = 0.0f, bool isCalc = false);

ACE_FORCE_EXPORT CalcDimension StringToCalcDimension(
    const std::string& value, bool useVp = false, DimensionUnit defaultUnit = DimensionUnit::PX);

inline Dimension StringToDimension(const std::string& value, bool useVp = false)
{
    return StringToDimensionWithUnit(value, useVp ? DimensionUnit::VP : DimensionUnit::PX);
}

Dimension StringToDimensionWithThemeValue(const std::string& value, bool useVp, const Dimension& themeValue);

ACE_FORCE_EXPORT bool StringToDimensionWithUnitNG(const std::string& value, Dimension& dimensionResult,
    DimensionUnit defaultUnit = DimensionUnit::PX, float defaultValue = 0.0f, bool isCalc = false);
ACE_FORCE_EXPORT bool StringToCalcDimensionNG(
    const std::string& value, CalcDimension& result, bool useVp = false,
    DimensionUnit defaultUnit = DimensionUnit::PX);
bool UnstringifyCalcDimension(
    const std::string& value, CalcDimension& result, bool useVp = false,
    DimensionUnit defaultUnit = DimensionUnit::PX);

ACE_FORCE_EXPORT std::string ReplaceChar(std::string str, char old_char, char new_char);

double StringToDegree(const std::string& value);
// StringToDegree with check. If the string is valid, change result and return true, otherwise return false.
bool StringToDegree(const std::string& value, double& result);

// Template function declaration - implementation with explicit instantiation in cpp
template<class T>
ACE_FORCE_EXPORT
void StringSplitter(
    const std::string& source, char delimiter, T (*func)(const std::string&), std::vector<T>& out);

// Explicit instantiations for common types
extern template void StringSplitter<std::string>(const std::string& source, char delimiter, std::string (*)(const std::string&), std::vector<std::string>& out);
extern template void StringSplitter<double>(const std::string& source, char delimiter, double (*)(const std::string&), std::vector<double>& out);
extern template void StringSplitter<float>(const std::string& source, char delimiter, float (*)(const std::string&), std::vector<float>& out);
extern template void StringSplitter<int32_t>(const std::string& source, char delimiter, int32_t (*)(const std::string&), std::vector<int32_t>& out);
extern template void StringSplitter<Dimension>(const std::string& source, char delimiter, Dimension (*)(const std::string&), std::vector<Dimension>& out);
extern template void StringSplitter<Color>(const std::string& source, char delimiter, Color (*)(const std::string&), std::vector<Color>& out);

ACE_FORCE_EXPORT bool ParseStringToArray(const std::string& input, std::vector<float>& output);

// Wrapper functions for StringSplitter - convenience overloads
ACE_FORCE_EXPORT void StringSplitter(const std::string& source, char delimiter, std::vector<std::string>& out);
ACE_FORCE_EXPORT void StringSplitter(const std::string& source, char delimiter, std::vector<double>& out);
ACE_FORCE_EXPORT void StringSplitter(const std::string& source, char delimiter, std::vector<float>& out);
ACE_FORCE_EXPORT void StringSplitter(const std::string& source, char delimiter, std::vector<int>& out);
ACE_FORCE_EXPORT void StringSplitter(const std::string& source, char delimiter, std::vector<Dimension>& out);

ACE_FORCE_EXPORT std::string DoubleToString(double value, int32_t precision = 2);

inline void DeleteAllMark(std::string& str, const char mark)
{
    str.erase(std::remove(str.begin(), str.end(), mark), str.end());
}

ACE_FORCE_EXPORT std::string TrimStr(const std::string& str, char cTrim = ' ');
void TrimStrLeadingAndTrailing(std::string& str, char cTrim = ' ');

ACE_FORCE_EXPORT void SplitStr(
    const std::string& str, const std::string& sep, std::vector<std::string>& out, bool needTrim = true);
ACE_FORCE_EXPORT void SplitStr(const std::string& str, const std::string& sep, std::vector<Dimension>& out, bool needTrim = true);

bool CStringEqual(const char* first, const char* second);

const std::string ACE_FORCE_EXPORT FormatString(const char* fmt, ...);

inline bool StartWith(const std::string& dst, const std::string& prefix)
{
    return dst.compare(0, prefix.size(), prefix) == 0;
}

inline bool StartWith(const std::string& str, const char* prefix, size_t prefixLen)
{
    return ((str.length() >= prefixLen) && (str.compare(0, prefixLen, prefix) == 0));
}

inline bool EndWith(const std::string& dst, const std::string& suffix)
{
    return (dst.size() >= suffix.size()) && dst.compare(dst.size() - suffix.size(), suffix.size(), suffix) == 0;
}

inline bool EndWith(const std::string& str, const char* suffix, size_t suffixLen)
{
    size_t len = str.length();
    return ((len >= suffixLen) && (str.compare(len - suffixLen, suffixLen, suffix) == 0));
}

// Template function declaration - implementation in cpp with explicit instantiation
template<typename T>
ACE_FORCE_EXPORT
void TransformStrCase(T& str, int32_t textCase);

ACE_FORCE_EXPORT bool IsAscii(const std::string& str);
} // namespace OHOS::Ace::StringUtils

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_UTILS_STRING_UTILS_H
