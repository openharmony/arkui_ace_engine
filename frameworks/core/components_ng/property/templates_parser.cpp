/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/property/templates_parser.h"

#include <regex>

#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {
namespace {
constexpr double FULL_PERCENT = 100.0;
constexpr uint32_t REPEAT_MIN_SIZE = 6;
constexpr uint32_t CROSS_WIDTH = 2;
constexpr uint32_t STRETCH_MATCH_SIZE = 4;
const std::string UNIT_VP = "vp";
const std::string UNIT_PIXEL = "px";
const std::string UNIT_RATIO = "fr";
const std::string UNIT_PERCENT = "%";
const std::string REPEAT_PREFIX = "repeat";
const std::string UNIT_AUTO_FILL = "auto-fill";
const std::string UNIT_AUTO_FIT = "auto-fit";
const std::string UNIT_AUTO_STRETCH = "auto-stretch";
const std::string TRIM_TEMPLATE = "$1$2";
const std::string INVALID_PATTERN = R"(((repeat)\(\s{0,}((auto-fill)|(auto-fit))\s{0,},))";
const std::string SIZE_PATTERN = "\\s{0,}[0-9]+([.]{1}[0-9]+){0,1}(px|%|vp){0,1}";
const std::string PREFIX_PATTERN = R"(\S{1,}(repeat)|(px|%|vp)\d{1,}|\)\d{1,})";
const std::regex UNIT_PIXEL_REGEX(R"(^([0-9]\d*|[0-9]\d*.\d*|0\.\d*[0-9]\d*)px$)", std::regex::icase);
const std::regex UNIT_RATIO_REGEX(R"(^([0-9]\d*|[0-9]\d*.\d*|0\.\d*[0-9]\d*)fr$)", std::regex::icase);
const std::regex UNIT_PERCENT_REGEX(R"(^([0-9]\d*|[0-9]\d*.\d*|0\.\d*[0-9]\d*)%$)", std::regex::icase);
const std::regex AUTO_REGEX(R"(^repeat\((.+),(.+)\))", std::regex::icase);        // regex for "repeat(auto-fill, 10px)"
const std::regex REPEAT_NUM_REGEX(R"(^repeat\((\d+),(.+)\))", std::regex::icase); // regex for "repeat(2, 100px)"
const std::regex TRIM_REGEX(R"(^ +| +$|(\"[^\"\\\\]*(?:\\\\[\\s\\S][^\"\\\\]*)*\")|( ) +)", std::regex::icase);
const std::string REPEAT_WITH_AUTOFILL_OR_AUTOFIT =
    R"(((repeat)\(\s{0,}((auto-fill)|(auto-fit))\s{0,},(\s{0,}[0-9]+([.]{1}[0-9]+){0,1}(px|%|vp){0,1}){1,}\s{0,}\)))";
const std::string AUTO_STRETCH_REGEX = R"(^\s*repeat\(auto-stretch,\s*(\d+(\.\d+)?(vp|px)?)\)$)";

enum class RepeatType {
    NONE = 0,
    FIXED_COUNT,
    AUTO_FILL,
};

struct Repeat {
    std::string str;
    bool isRepeat = false;
};
using Value = Repeat;

double ConvertVirtualSize(const std::string& val, const DimensionUnit& unit, double size)
{
    double ret = StringUtils::StringToDouble(val);
    switch (unit) {
        case DimensionUnit::PERCENT:
            ret = ret / FULL_PERCENT * size;
            break;
        case DimensionUnit::VP: {
            auto pipelineContext = PipelineBase::GetCurrentContextSafelyWithCheck();
            if (pipelineContext) {
                ret = pipelineContext->NormalizeToPx(Dimension(ret, DimensionUnit::VP));
            } else {
                ret = Dimension(ret, DimensionUnit::VP).Value();
            }
        }
            break;
        case DimensionUnit::PX:
            break;
        default:
            ret = 0.0;
            break;
    }
    return ret;
}

double ParseUnit(const Value& val, double size)
{
    double ret = 0;
    std::regex pattern(R"(^\s{0,}[0-9]+([.]{1}[0-9]+){0,1}\s{0,})");
    std::smatch match;
    if (val.str.find(UNIT_PIXEL) != std::string::npos) {
        ret = ConvertVirtualSize(val.str, DimensionUnit::PX, size);
    } else if (val.str.find(UNIT_PERCENT) != std::string::npos) {
        ret = ConvertVirtualSize(val.str, DimensionUnit::PERCENT, size);
    } else if (val.str.find(UNIT_VP) != std::string::npos || std::regex_match(val.str, match, pattern)) {
        ret = ConvertVirtualSize(val.str, DimensionUnit::VP, size);
    }
    return ret;
}

std::string TrimTemplate(std::string& str)
{
    return std::regex_replace(str, TRIM_REGEX, TRIM_TEMPLATE);
}

void RTrim(std::string& str)
{
    str.erase(std::find_if(str.rbegin(), str.rend(), [](int ch) { return !std::isspace(ch); }).base(), str.end());
}

bool SplitTemplate(const std::string& str, std::vector<Value>& vec, bool isRepeat = false)
{
    std::string merge;
    std::string regexResult;
    std::smatch result;
    std::regex pattern(SIZE_PATTERN, std::regex::icase);
    std::string::const_iterator iterStart = str.begin();
    std::string::const_iterator iterEnd = str.end();

    while (std::regex_search(iterStart, iterEnd, result, pattern)) {
        regexResult = result[0];
        merge += regexResult;
        Value value;
        value.str = TrimTemplate(regexResult);
        value.isRepeat = isRepeat;
        vec.emplace_back(value);
        iterStart = result[0].second;
    }
    return (merge.length() == str.length());
}

std::string GetRepeat(const std::string& str)
{
    std::smatch result;
    std::regex pattern(REPEAT_WITH_AUTOFILL_OR_AUTOFIT, std::regex::icase);
    std::string::const_iterator iterStart = str.begin();
    std::string::const_iterator iterEnd = str.end();
    std::string regexResult;
    size_t count = 0;
    while (std::regex_search(iterStart, iterEnd, result, pattern)) {
        regexResult = result[0];
        iterStart = result[0].second;
        ++count;
    }
    if (count == 1) {
        return regexResult;
    }
    return { "" };
}

bool CheckRepeatAndSplitString(std::vector<std::string>& vec, std::string& repeat, std::vector<Value>& resultvec)
{
    if (repeat.length() == 0 && vec.empty()) {
        return false;
    }
    std::string regexResult;
    std::regex pattern(INVALID_PATTERN, std::regex::icase);

    for (auto it = vec.begin(); it != vec.end(); it++) {
        RTrim(*it);
        bool ret = SplitTemplate(*it, resultvec);
        if (!ret) {
            return ret;
        }
        if (it == vec.begin()) {
            regexResult = std::regex_replace(repeat, pattern, "");
            if (regexResult.length() == 0) {
                return false;
            }
            regexResult.erase(regexResult.end() - 1);
            RTrim(regexResult);
            ret = SplitTemplate(regexResult, resultvec, true);
            if (!ret) {
                return ret;
            }
        }
    }
    return true;
}

bool CheckAutoFillParameter(
    const std::string& args, double size, std::vector<double>& out, std::vector<Value>& resultvec)
{
    out.clear();
    if (args.empty()) {
        return false;
    }
    std::smatch result;
    std::regex patternFilter(PREFIX_PATTERN, std::regex::icase);
    if (std::regex_search(args, result, patternFilter)) {
        out.push_back(size);
        return false;
    }

    std::regex pattern(REPEAT_WITH_AUTOFILL_OR_AUTOFIT, std::regex::icase);
    std::vector<std::string> vec(
        std::sregex_token_iterator(args.begin(), args.end(), pattern, -1), std::sregex_token_iterator());

    std::string repeat = GetRepeat(args);
    bool invalidRepeatAutoFill = CheckRepeatAndSplitString(vec, repeat, resultvec);
    if (!invalidRepeatAutoFill && out.empty()) {
        out.push_back(size);
    }
    return invalidRepeatAutoFill;
}

std::pair<std::vector<double>, double> ParseArgsWithAutoFill(
    const std::string& args, double size, double gap, int32_t childrenCount)
{
    std::vector<double> lens;
    std::vector<Value> retTemplates;
    if (!CheckAutoFillParameter(args, size, lens, retTemplates)) {
        return std::make_pair(lens, gap);
    }
    int32_t countNonRepeat = 0;
    int countRepeat = 0;
    double sizeRepeat = 0.0;
    double sizeNonRepeat = 0.0;
    bool invalidRepeatAutoFill = false;
    std::vector<double> prefixLens;
    std::vector<double> repeatLens;
    std::vector<double> suffixLens;
    for (const auto& ret : retTemplates) {
        double sizeItem = ParseUnit(ret, size);
        if (ret.isRepeat) {
            invalidRepeatAutoFill = true;
            sizeRepeat += sizeItem;
            ++countRepeat;
            repeatLens.push_back(sizeItem);
        } else {
            ++countNonRepeat;
            sizeNonRepeat += sizeItem;
            if (invalidRepeatAutoFill) {
                suffixLens.push_back(sizeItem);
            } else {
                prefixLens.push_back(sizeItem);
            }
        }
    }
    if (countNonRepeat + countRepeat > 0 && (countNonRepeat + countRepeat - 1) * gap > size) {
        gap = 0.0;
    }
    double sizeNonRepeatGap = GreatNotEqual(countNonRepeat, 0) ? (countNonRepeat - 1) * gap : 0;
    double sizeLeft = size - sizeNonRepeatGap - sizeNonRepeat;
    double count = 0;
    if (!NearZero(sizeRepeat)) {
        count = (sizeLeft + gap) / (sizeRepeat + countRepeat * gap);
        count = LessOrEqual(count, 1) ? 1 : floor(count);
    } else {
        if (childrenCount >= countNonRepeat && !retTemplates.empty()) {
            count = ceil((size - countNonRepeat) * 1.0 / (static_cast<int32_t>(retTemplates.size()) - countNonRepeat));
        }
    }
    lens.insert(lens.end(), prefixLens.begin(), prefixLens.end());
    for (int i = 0; i < count; i++) {
        lens.insert(lens.end(), repeatLens.begin(), repeatLens.end());
    }
    lens.insert(lens.end(), suffixLens.begin(), suffixLens.end());
    return std::make_pair(lens, gap);
}

void ConvertRepeatArgs(std::string& handledArg, double size)
{
    if (handledArg.find(REPEAT_PREFIX) == std::string::npos) {
        return;
    }
    handledArg.erase(0, handledArg.find_first_not_of(' ')); // trim the input str
    std::smatch matches;
    if (handledArg.find(UNIT_AUTO_FILL) != std::string::npos) {
        if (handledArg.size() > REPEAT_MIN_SIZE && std::regex_match(handledArg, matches, AUTO_REGEX)) {
            handledArg = matches[1].str() + matches[CROSS_WIDTH].str();
        }
    } else {
        if (handledArg.size() > REPEAT_MIN_SIZE && std::regex_match(handledArg, matches, REPEAT_NUM_REGEX)) {
            auto count = StringUtils::StringToInt(matches[1].str());
            count = std::min(count, static_cast<int32_t>(size));
            std::string repeatString = matches[CROSS_WIDTH].str();
            while (count > 1) {
                repeatString.append(" " + std::string(matches[CROSS_WIDTH].str()));
                --count;
            }
            handledArg = repeatString;
        }
    }
}

std::pair<std::vector<double>, double> ParseAutoFill(const std::vector<std::string>& strs, double size, double gap)
{
    std::vector<double> lens;
    if (strs.size() <= 1) {
        return std::make_pair(lens, gap);
    }
    auto allocatedSize = size - (strs.size() - 2) * gap; // size() - 2 means 'auto-fill' should be erased.
    if (allocatedSize > size) {
        gap = 0.0;
    }
    double pxSum = 0.0;
    double peSum = 0.0;
    std::vector<double> newLens;
    for (const auto& str : strs) {
        auto num = StringUtils::StringToDouble(str);
        if (str.find(UNIT_PIXEL) != std::string::npos) {
            num = pxSum > allocatedSize ? 0.0 : num;
            pxSum += num;
            lens.emplace_back(num);
        } else if (str.find(UNIT_PERCENT) != std::string::npos) {
            // adjust invalid percent
            num = peSum >= FULL_PERCENT ? 0.0 : num;
            peSum += num;
            pxSum += num / FULL_PERCENT * size;
            lens.emplace_back(num / FULL_PERCENT * size);
        } else {
            LOGE("Unsupported type: %{public}s, and use 0.0", str.c_str());
            return std::make_pair(newLens, gap);
        }
    }
    allocatedSize -= pxSum;
    if (LessOrEqual(allocatedSize, 0.0)) {
        return std::make_pair(lens, gap);
    }
    pxSum += lens.size() * gap;
    auto repeatCount = static_cast<int32_t>(allocatedSize / pxSum);
    for (int32_t i = 0; i < repeatCount + 1; i++) {
        newLens.insert(newLens.end(), lens.begin(), lens.end());
    }
    allocatedSize -= pxSum * repeatCount;
    for (double& len : lens) {
        allocatedSize -= len + gap;
        if (LessNotEqual(allocatedSize, 0.0)) {
            break;
        }
        newLens.emplace_back(len);
    }
    return std::make_pair(newLens, gap);
}

std::pair<std::vector<double>, double> ParseArgsWithoutAutoFill(const std::string& args, double size, double gap)
{
    std::vector<double> lens;
    if (args.empty()) {
        return std::make_pair(lens, gap);
    }
    double pxSum = 0.0; // First priority: such as 50px
    double peSum = 0.0; // Second priority: such as 20%
    double frSum = 0.0; // Third priority: such as 2fr
    std::vector<std::string> strs;
    std::string handledArg = args;
    ConvertRepeatArgs(handledArg, size);
    StringUtils::StringSplitter(handledArg, ' ', strs);
    if (!strs.empty() && strs[0] == UNIT_AUTO_FILL) {
        return ParseAutoFill(strs, size, gap);
    }
    // first loop calculate all type sums.
    for (const auto& str : strs) {
        if (std::regex_match(str, UNIT_PIXEL_REGEX)) {
            pxSum += StringUtils::StringToDouble(str);
        } else if (std::regex_match(str, UNIT_PERCENT_REGEX)) {
            peSum += StringUtils::StringToDouble(str);
        } else if (std::regex_match(str, UNIT_RATIO_REGEX)) {
            frSum += StringUtils::StringToDouble(str);
        } else {
            return std::make_pair(lens, gap);
        }
    }
    peSum = GreatOrEqual(peSum, FULL_PERCENT) ? FULL_PERCENT : peSum;
    // Second loop calculate actual width or height.
    double sizeLeft = size > ((strs.size() - 1) * gap) ? size - (strs.size() - 1) * gap : size;
    gap = size > ((strs.size() - 1) * gap) ? gap : 0.0;
    double sizeNoGap = sizeLeft;
    double prSumLeft = FULL_PERCENT;
    double frSizeSum = sizeNoGap * (FULL_PERCENT - peSum) / FULL_PERCENT - pxSum;
    for (const auto& str : strs) {
        double num = StringUtils::StringToDouble(str);
        if (str.find(UNIT_PIXEL) != std::string::npos) {
            lens.push_back(sizeLeft < 0.0 ? 0.0 : std::clamp(num, 0.0, sizeLeft));
            sizeLeft -= num;
        } else if (str.find(UNIT_PERCENT) != std::string::npos) {
            num = prSumLeft < num ? prSumLeft : num;
            auto prSize = sizeNoGap * num / FULL_PERCENT;
            lens.push_back(prSize);
            prSumLeft -= num;
            sizeLeft -= prSize;
        } else if (str.find(UNIT_RATIO) != std::string::npos) {
            frSum = LessNotEqual(frSum, 1) ? 1 : frSum;
            lens.push_back(NearZero(frSum) ? 0.0 : frSizeSum / frSum * num);
        }
    }
    return std::make_pair(lens, gap);
}

std::pair<std::vector<double>, double> ParseArgsWithAutoFit(
    const std::string& args, double size, double gap, int32_t childrenCount)
{
    std::vector<double> lens;
    std::vector<Value> retTemplates;
    if (!CheckAutoFillParameter(args, size, lens, retTemplates)) {
        return std::make_pair(lens, gap);
    }

    size_t countNonRepeat = 0;
    int countRepeat = 0;
    double sizeRepeat = 0.0;
    double sizeNonRepeat = 0.0;
    bool invalidRepeatAutoFill = false;

    std::vector<double> prefixLens;
    std::vector<double> repeatLens;
    std::vector<double> suffixLens;

    for (const auto& ret : retTemplates) {
        double sizeItem = ParseUnit(ret, size);
        if (ret.isRepeat) {
            invalidRepeatAutoFill = true;
            sizeRepeat += sizeItem;
            ++countRepeat;
            repeatLens.push_back(sizeItem);
        } else {
            ++countNonRepeat;
            sizeNonRepeat += sizeItem;
            if (invalidRepeatAutoFill) {
                suffixLens.push_back(sizeItem);
            } else {
                prefixLens.push_back(sizeItem);
            }
        }
    }

    double sizeNonRepeatGap = GreatNotEqual(countNonRepeat, 0) ? (countNonRepeat - 1) * gap : 0;
    double sizeLeft = size - sizeNonRepeatGap - sizeNonRepeat;
    double count = 0;
    if (!NearZero(sizeRepeat)) {
        count = (sizeLeft + gap) / (sizeRepeat + countRepeat * gap);
        count = LessOrEqual(count, 1) ? 1 : floor(count);
    } else {
        if (childrenCount >= static_cast<int32_t>(countNonRepeat) && !retTemplates.empty()) {
            count = ceil((size - countNonRepeat) * 1.0 / (retTemplates.size() - countNonRepeat));
        }
    }
    if (!NearZero(count)) {
        double gridWidth = (sizeLeft + gap) / count - gap;
        lens.insert(lens.end(), prefixLens.begin(), prefixLens.end());
        for (int i = 0; i < count; i++) {
            lens.push_back(gridWidth);
        }
        lens.insert(lens.end(), suffixLens.begin(), suffixLens.end());
    }

    return std::make_pair(lens, gap);
}

bool CheckAutoStretchParameter(const std::string& args, Value& track)
{
    std::regex pattern(AUTO_STRETCH_REGEX, std::regex::icase);
    std::smatch match;
    if (std::regex_match(args, match, pattern)) {
        if (match.size() == STRETCH_MATCH_SIZE) {
            track.str = match[1].str();
            return true;
        }
    }
    return false;
}

std::pair<std::vector<double>, double> ParseArgsWithAutoStretch(const std::string& args, double size, double gap)
{
    std::vector<double> lens;
    Value track;
    if (!CheckAutoStretchParameter(args, track)) {
        return std::make_pair(lens, gap);
    }

    double trackSize = ParseUnit(track, size);
    float realGap = gap;
    int32_t columnCount = 1;
    if (trackSize + gap > 0) {
        columnCount = std::floor((size + gap) / (trackSize + gap));
        columnCount = std::max(columnCount, 1);
        if (columnCount > 1) {
            realGap = (size - columnCount * trackSize) / (columnCount - 1);
        }
    }

    for (int32_t i = 0; i < columnCount; i++) {
        lens.emplace_back(trackSize);
    }

    return std::make_pair(lens, realGap);
}
} // namespace

std::pair<std::vector<double>, double> ParseTemplateArgs(
    const std::string& args, double size, double gap, int32_t childrenCount)
{
    if (args.find(REPEAT_PREFIX) != std::string::npos) {
        if (args.find(UNIT_AUTO_FILL) != std::string::npos) {
            return ParseArgsWithAutoFill(args, size, gap, childrenCount);
        }
        if (args.find(UNIT_AUTO_FIT) != std::string::npos) {
            return ParseArgsWithAutoFit(args, size, gap, childrenCount);
        }
        if (args.find(UNIT_AUTO_STRETCH) != std::string::npos) {
            return ParseArgsWithAutoStretch(args, size, gap);
        }
    }
    return NG::ParseArgsWithoutAutoFill(args, size, gap);
}
} // namespace OHOS::Ace::NG
