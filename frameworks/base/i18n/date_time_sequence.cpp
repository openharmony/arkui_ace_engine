/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "base/i18n/date_time_sequence.h"
#include "unicode/dtptngen.h"
#include "unicode/smpdtfmt.h"
#include <regex>

namespace OHOS::Ace {

using namespace icu;

OrderResult DateTimeSequence::GetDateOrder(const std::string& locale)
{
    UErrorCode icuStatus = U_ZERO_ERROR;
    OrderResult orderResult;
    icu::Locale localeObj = icu::Locale::forLanguageTag(locale.data(), icuStatus);
    if (U_FAILURE(icuStatus)) {
        return orderResult;
    }
    const char* language = localeObj.getBaseName();
    if (language == nullptr) {
        return orderResult;
    }
    const std::unordered_map<std::string, std::string> DATE_ORDER_MAP = {
        { "ug", "M-d-y" },
        { "ar", "y-M-d" },
        { "fa", "y-M-d" },
        { "ur", "y-M-d" },
        { "iw", "y-M-d" },
        { "he", "y-M-d" },
    };
    std::string languageTag = language;
    if (DATE_ORDER_MAP.find(languageTag) != DATE_ORDER_MAP.end()) {
        orderResult.dateOrder = DATE_ORDER_MAP.find(languageTag)->second;
        return orderResult;
    }
    icu::SimpleDateFormat* formatter = static_cast<icu::SimpleDateFormat*>
        (icu::DateFormat::createDateInstance(icu::DateFormat::EStyle::kDefault, localeObj));
    if (U_FAILURE(icuStatus) || formatter == nullptr) {
        return orderResult;
    }
    std::string tempValue;
    icu::UnicodeString unistr;
    formatter->toPattern(unistr);
    unistr.toUTF8String<std::string>(tempValue);
    std::string value = ModifyOrder(tempValue);
    std::regex pattern("d+");
    std::regex reg("M+");
    value = regex_replace(value, pattern, "d");
    value = regex_replace(value, reg, "M");
    orderResult = {value};
    delete formatter;
    return orderResult;
}

OrderResult DateTimeSequence::GetDateTimeOrder(const std::string& locale)
{
    UErrorCode status = U_ZERO_ERROR;
    OrderResult orderResult;
    icu::Locale localeObj = icu::Locale::forLanguageTag(locale.data(), status);
    if (U_FAILURE(status)) {
        orderResult.dateTimeOrder = "-1";
        return orderResult;
    }
    const std::unordered_map<std::string, std::string> DATETIME_ORDER_MAP = {
        { "ug", "01" },
        { "ar", "10" },
        { "fa", "01" },
        { "ur", "10" },
        { "iw", "10" },
        { "he", "10" },
    };
    const char* language = localeObj.getBaseName();
    std::string languageTag = language == nullptr ? "" : language;
    if (DATETIME_ORDER_MAP.find(languageTag) != DATETIME_ORDER_MAP.end()) {
        orderResult.dateTimeOrder = DATETIME_ORDER_MAP.find(languageTag)->second;
        return orderResult;
    }
    icu::SimpleDateFormat* formatter = static_cast<icu::SimpleDateFormat*>
        (icu::DateFormat::createDateInstance(icu::DateFormat::EStyle::kDateTime, localeObj));
    if (status != U_ZERO_ERROR || formatter == nullptr) {
        orderResult.dateTimeOrder = "-1";
        return orderResult;
    }
    icu::UnicodeString pattern;
    formatter->toPattern(pattern);
    std::string result;
    pattern.toUTF8String<std::string>(result);

    std::regex pattrn("0([^01]+)1");
    std::smatch match;
    bool found = std::regex_search(result, match, pattrn);
    // 1 represent date position, 0 represent time position
    std::string dateTimeOrder = found ? "01" : "10";
    orderResult = {result, dateTimeOrder};
    delete formatter;
    return orderResult;
}

OrderResult DateTimeSequence::GetAmPmTimeOrder(const std::string& locale)
{
    UErrorCode status = U_ZERO_ERROR;
    OrderResult orderResult;
    icu::Locale localeObj = icu::Locale::forLanguageTag(locale.data(), status);
    if (status != U_ZERO_ERROR) {
        orderResult.amPmTimeOrder = "-1";
        return orderResult;
    }
    const char* language = localeObj.getBaseName();
    const std::unordered_map<std::string, std::string> AM_PM_TIME_ORDER_MAP = {
        { "ug", "10" },
        { "ar", "01" },
        { "fa", "01" },
        { "ur", "10" },
        { "iw", "01" },
        { "he", "01" },
        { "bo", "10" },
    };
    std::string languageTag = language == nullptr ? "" : language;
    if (AM_PM_TIME_ORDER_MAP.find(languageTag) != AM_PM_TIME_ORDER_MAP.end()) {
        orderResult.amPmTimeOrder = AM_PM_TIME_ORDER_MAP.find(languageTag)->second;
        return orderResult;
    }
    icu::DateTimePatternGenerator* gen = icu::DateTimePatternGenerator::createInstance(localeObj, status);
    icu::UnicodeString skeleton("h");
    if (gen == nullptr) {
        orderResult.amPmTimeOrder = "-1";
        return orderResult;
    }
    icu::UnicodeString resultStr = gen->getBestPattern(skeleton, status);
    if (U_FAILURE(status)) {
        orderResult.amPmTimeOrder = "-1";
        return orderResult;
    }
    std::string result;
    resultStr.toUTF8String<std::string>(result);
    std::regex pattrn("a[^ah]*h");
    std::smatch match;
    bool found = std::regex_search(result, match, pattrn);
    // 0 represent am/pm position
    std::string amPmTimeOrder = found ? "10" : "01"; // 1 represent time position
    orderResult = {result, "", amPmTimeOrder};
    delete gen;
    return orderResult;
}

std::string DateTimeSequence::ModifyOrder(std::string& pattern)
{
    int order[3] = { 0 }; // total 3 elements 'y', 'M'/'L', 'd'
    int lengths[4] = { 0 }; // first elements is the currently found elememnts, thus 4 elements totally.
    bool flag = true;
    for (size_t i = 0; i < pattern.length(); ++i) {
        char ch = pattern[i];
        if (flag && std::isalpha(ch)) {
            ProcessNormal(ch, order, 3, lengths, 4); // 3, 4 are lengths of these arrays
        } else if (ch == '\'') {
            flag = !flag;
        }
    }
    std::unordered_map<char, int> pattern2index = {
        { 'y', 1 },
        { 'M', 2 },
        { 'd', 3 },
    };
    std::string ret;
    for (int i = 0; i < 3; ++i) { // 3 is the size of orders
        auto it = pattern2index.find(order[i]);
        if (it == pattern2index.end()) {
            continue;
        }
        int index = it->second;
        if ((lengths[index] > 0) && (lengths[index] <= 6)) { // 6 is the max length of a filed
            ret.append(lengths[index], order[i]);
        }
        if (i < 2) { // 2 is the size of the order minus one
            ret.append(1, '-');
        }
    }
    return ret;
}

void DateTimeSequence::ProcessNormal(char ch, int* order, size_t orderSize, int* lengths, size_t lengsSize)
{
    char adjust;
    int index = -1;
    if (ch == 'd') {
        adjust = 'd';
        index = 3; // 3 is the index of 'd'
    } else if ((ch == 'L') || (ch == 'M')) {
        adjust = 'M';
        index = 2; // 2 is the index of 'M'
    } else if (ch == 'y') {
        adjust = 'y';
        index = 1;
    } else {
        return;
    }
    if ((index < 0) || (index >= static_cast<int>(lengsSize))) {
        return;
    }
    if (lengths[index] == 0) {
        if (lengths[0] >= 3) { // 3 is the index of order
            return;
        }
        order[lengths[0]] = static_cast<int>(adjust);
        ++lengths[0];
        lengths[index] = 1;
    } else {
        ++lengths[index];
    }
}

} // namespace OHOS::Ace