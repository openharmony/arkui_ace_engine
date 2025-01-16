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

#include "frameworks/bridge/common/utils/source_map.h"

#include "base/log/log.h"

namespace OHOS::Ace::Framework {

const char SOURCES[] = "sources";
const char NAMES[] = "names";
const char MAPPINGS[] = "mappings";
const char FILE[] = "file";
const char NAMEMAP[] = "nameMap";
const char SOURCE_CONTENT[] = "sourceContent";
const char SOURCE_ROOT[] = "sourceRoot";
const char DELIMITER_COMMA = ',';
const char DELIMITER_SEMICOLON = ';';
const char DOUBLE_SLASH = '\\';
const char WEBPACK[] = "webpack:///";
constexpr int32_t AFTER_COLUMN = 0;
constexpr int32_t SOURCES_VAL = 1;
constexpr int32_t BEFORE_ROW = 2;
constexpr int32_t BEFORE_COLUMN = 3;
constexpr int32_t NAMES_VAL = 4;

MappingInfo RevSourceMap::Find(int32_t row, int32_t col, bool isColPrecise)
{
    if (row < 1 || col < 1 || afterPos_.empty()) {
        return MappingInfo {};
    }
    row--;
    col--;
    // binary search
    int32_t left = 0;
    int32_t right = static_cast<int32_t>(afterPos_.size()) - 1;
    int32_t res = 0;
    bool isRightBig = false;
    if (row > afterPos_[afterPos_.size() - 1].afterRow) {
        return MappingInfo { row + 1, col + 1, files_[0] };
    }
    while (right - left >= 0) {
        int32_t mid = (right + left) / 2;
        if ((afterPos_[mid].afterRow == row && afterPos_[mid].afterColumn > col) || afterPos_[mid].afterRow > row) {
            right = mid - 1;
            isRightBig = true;
        } else {
            res = mid;
            left = mid + 1;
        }
    }

    /*
     * real:[56:7]->[250:21]
     * [row:col]->[afterRow:afterColumn]
     * 0:[53:14]->[237:77]
     * 1:[53:14]->[237:78]
     * 2:[56:7]->[250:39]
     * 3:[56:14]->[250:40]
    */
    if (!isColPrecise && isRightBig && right > 0 && afterPos_[right].afterRow < row) {
        res = right + 1;
    }

    int32_t sourcesSize = static_cast<int32_t>(sources_.size());
    if (afterPos_[res].sourcesVal < 0 || afterPos_[res].sourcesVal >= sourcesSize) {
        return MappingInfo {};
    }
    std::string sources = sources_[afterPos_[res].sourcesVal];
    auto pos = sources.find(WEBPACK);
    if (pos != std::string::npos) {
        sources.replace(pos, sizeof(WEBPACK) - 1, "");
    }

    return MappingInfo {
        .row = afterPos_[res].beforeRow + 1,
        .col = afterPos_[res].beforeColumn + 1,
        .sources = sources,
    };
}

std::string RevSourceMap::GetOriginalNames(const std::string& sourceCode, uint32_t& errorPos) const
{
    if (sourceCode.empty() || sourceCode.find("SourceCode:\n") == std::string::npos) {
        return sourceCode;
    }
    if (nameMap_.size() % 2 != 0) {
        return sourceCode;
    }
    std::string jsCode = sourceCode;
    int32_t posDiff = 0;
    for (uint32_t i = 0; i < nameMap_.size(); i += 2) {
        auto found = jsCode.find(nameMap_[i]);
        while (found != std::string::npos) {
            // nameMap_[i + 1] is the original name of nameMap_[i]
            jsCode.replace(found, nameMap_[i].length(), nameMap_[i + 1]);
            if (static_cast<uint32_t>(found) < errorPos) {
                // sum the errorPos differences to adjust position of ^
                posDiff += static_cast<int32_t>(nameMap_[i + 1].length()) - static_cast<int32_t>(nameMap_[i].length());
            }
            // In case there are other variable names not replaced.
            // example:var e = process.a.b + _ohos_process_1.a.b;
            found = jsCode.find(nameMap_[i], found + nameMap_[i + 1].length());
        }
    }
    auto lineBreakPos = jsCode.rfind('\n', jsCode.length() - 2);
    if (lineBreakPos == std::string::npos) {
        return jsCode;
    }
    // adjust position of ^ in dump file
    if (posDiff < 0) {
        int32_t flagPos = static_cast<int32_t>(lineBreakPos) + static_cast<int32_t>(errorPos);
        if (lineBreakPos > 0 && errorPos > 0 && flagPos < 0) {
            LOGW("Add overflow of sourceCode.");
            return jsCode;
        }
        if (flagPos < static_cast<int32_t>(jsCode.length()) && jsCode[flagPos] == '^' && flagPos + posDiff - 1 > 0) {
            jsCode.erase(flagPos + posDiff - 1, -posDiff);
        }
    } else if (posDiff > 0) {
        if (lineBreakPos + 1 < jsCode.length() - 1) {
            jsCode.insert(lineBreakPos + 1, posDiff, ' ');
        }
    }
    return jsCode;
}

void RevSourceMap::ExtractKeyInfo(const std::string& sourceMap, std::vector<std::string>& sourceKeyInfo)
{
    uint32_t cnt = 0;
    std::string tempStr;
    for (uint32_t i = 0; i < sourceMap.size(); i++) {
        // reslove json file
        if (sourceMap[i] == DOUBLE_SLASH) {
            i++;
            tempStr += sourceMap[i];
            continue;
        }
        // cnt is used to represent a pair of double quotation marks: ""
        if (sourceMap[i] == '"') {
            cnt++;
        }
        if (cnt == 2) {
            sourceKeyInfo.push_back(tempStr);
            tempStr = "";
            cnt = 0;
        } else if (cnt == 1) {
            if (sourceMap[i] != '"') {
                tempStr += sourceMap[i];
            }
        }
    }
}

void RevSourceMap::HandleKeyInfo(const std::string& keyInfo, std::string& mark)
{
    // first: find the key info and record the temp key info
    // second: add the detail into the keyinfo
    if (keyInfo == SOURCES || keyInfo == NAMES || keyInfo == MAPPINGS || keyInfo == FILE || keyInfo == SOURCE_CONTENT ||
        keyInfo == SOURCE_ROOT || keyInfo == NAMEMAP) {
        // record the temp key info
        mark = keyInfo;
    } else if (mark == SOURCES) {
        sources_.push_back(keyInfo);
    } else if (mark == NAMES) {
        names_.push_back(keyInfo);
    } else if (mark == MAPPINGS) {
        mappings_.push_back(keyInfo);
    } else if (mark == FILE) {
        files_.push_back(keyInfo);
    } else if (mark == NAMEMAP) {
        nameMap_.push_back(keyInfo);
    }
}

void RevSourceMap::Init(const std::string& sourceMap)
{
    std::vector<std::string> sourceKeyInfo;
    std::string mark = "";

    ExtractKeyInfo(sourceMap, sourceKeyInfo);

    // first: find the key info and record the temp key info
    // second: add the detail into the keyinfo
    for (auto keyInfo : sourceKeyInfo) {
        HandleKeyInfo(keyInfo, mark);
    }

    if (mappings_.empty()) {
        LOGW("Decode sourcemap fail, mapping: %{public}s is empty", sourceMap.c_str());
        return;
    }

    // transform to vector for mapping easily
    mappings_ = HandleMappings(mappings_[0]);

    // the first bit: the column after transferring.
    // the second bit: the source file.
    // the third bit: the row before transferring.
    // the fourth bit: the column before transferring.
    // the fifth bit: the variable name.
    for (const auto& mapping : mappings_) {
        if (mapping == ";") {
            // plus a line for each semicolon
            nowPos_.afterRow++, nowPos_.afterColumn = 0;
            continue;
        }
        // decode each mapping ";QAABC"
        std::vector<int32_t> ans;
        if (!VlqRevCode(mapping, ans)) {
            return;
        }
        if (ans.size() == 0) {
            LOGW("Decode sourcemap fail, mapping: %{public}s is empty", mapping.c_str());
            break;
        }
        if (ans.size() == 1) {
            nowPos_.afterColumn += ans[AFTER_COLUMN];
            continue;
        }
        // after decode, assgin each value to the position
        nowPos_.afterColumn += ans[AFTER_COLUMN];
        nowPos_.sourcesVal += ans[SOURCES_VAL];
        nowPos_.beforeRow += ans[BEFORE_ROW];
        nowPos_.beforeColumn += ans[BEFORE_COLUMN];
        if (ans.size() == 5) {
            nowPos_.namesVal += ans[NAMES_VAL];
        }
        afterPos_.push_back({ nowPos_.beforeRow, nowPos_.beforeColumn, nowPos_.afterRow, nowPos_.afterColumn,
            nowPos_.sourcesVal, nowPos_.namesVal });
    }
    mappings_.clear();
    mappings_.shrink_to_fit();
    sourceKeyInfo.clear();
    sourceKeyInfo.shrink_to_fit();
};

void RevSourceMap::MergeInit(const std::string& sourceMap,
    RefPtr<RevSourceMap>& curMapData)
{
    std::vector<std::string> sourceKey;
    std::string mark = "";
    ExtractKeyInfo(sourceMap, sourceKey);
    for (auto sourceKeyInfo : sourceKey) {
        if (sourceKeyInfo == SOURCES || sourceKeyInfo == NAMES ||
            sourceKeyInfo == MAPPINGS || sourceKeyInfo == FILE ||
            sourceKeyInfo == SOURCE_CONTENT ||  sourceKeyInfo == SOURCE_ROOT) {
            mark = sourceKeyInfo;
        } else if (mark == SOURCES) {
            curMapData->sources_.push_back(sourceKeyInfo);
        } else if (mark == NAMES) {
            curMapData->names_.push_back(sourceKeyInfo);
        } else if (mark == MAPPINGS) {
            curMapData->mappings_.push_back(sourceKeyInfo);
        } else if (mark == FILE) {
            curMapData->files_.push_back(sourceKeyInfo);
        } else {
            continue;
        }
    }

    if (curMapData->mappings_.empty()) {
        LOGW("MergeInit decode sourcemap fail, mapping: %{public}s", sourceMap.c_str());
        return;
    }

    // transform to vector for mapping easily
    curMapData->mappings_ = HandleMappings(curMapData->mappings_[0]);

    // the first bit: the column after transferring.
    // the second bit: the source file.
    // the third bit: the row before transferring.
    // the fourth bit: the column before transferring.
    // the fifth bit: the variable name.
    for (const auto& mapping : curMapData->mappings_) {
        if (mapping == ";") {
            // plus a line for each semicolon
            curMapData->nowPos_.afterRow++,
            curMapData->nowPos_.afterColumn = 0;
            continue;
        }
        std::vector<int32_t> ans;

        if (!VlqRevCode(mapping, ans)) {
            return;
        }
        if (ans.size() == 0) {
            break;
        }
        if (ans.size() == 1) {
            curMapData->nowPos_.afterColumn += ans[AFTER_COLUMN];
            continue;
        }
        // after decode, assgin each value to the position
        curMapData->nowPos_.afterColumn += ans[AFTER_COLUMN];
        curMapData->nowPos_.sourcesVal += ans[SOURCES_VAL];
        curMapData->nowPos_.beforeRow += ans[BEFORE_ROW];
        curMapData->nowPos_.beforeColumn += ans[BEFORE_COLUMN];
        if (ans.size() == 5) {
            curMapData->nowPos_.namesVal += ans[NAMES_VAL];
        }
        curMapData->afterPos_.push_back({
            curMapData->nowPos_.beforeRow,
            curMapData->nowPos_.beforeColumn,
            curMapData->nowPos_.afterRow,
            curMapData->nowPos_.afterColumn,
            curMapData->nowPos_.sourcesVal,
            curMapData->nowPos_.namesVal
        });
    }
    curMapData->mappings_.clear();
    curMapData->mappings_.shrink_to_fit();
    sourceKey.clear();
    sourceKey.shrink_to_fit();
};


std::vector<std::string> RevSourceMap::HandleMappings(const std::string& mapping)
{
    std::vector<std::string> keyInfo;
    std::string tempStr;
    for (uint32_t i = 0; i < mapping.size(); i++) {
        if (mapping[i] == DELIMITER_COMMA) {
            keyInfo.push_back(tempStr);
            tempStr = "";
        } else if (mapping[i] == DELIMITER_SEMICOLON) {
            if (tempStr != "") {
                keyInfo.push_back(tempStr);
            }
            tempStr = "";
            keyInfo.push_back(";");
        } else {
            tempStr += mapping[i];
        }
    }
    if (tempStr != "") {
        keyInfo.push_back(tempStr);
    }
    return keyInfo;
};

uint32_t RevSourceMap::Base64CharToInt(char charCode)
{
    if ('A' <= charCode && charCode <= 'Z') {
        // 0 - 25: ABCDEFGHIJKLMNOPQRSTUVWXYZ
        return charCode - 'A';
    } else if ('a' <= charCode && charCode <= 'z') {
        // 26 - 51: abcdefghijklmnopqrstuvwxyz
        return charCode - 'a' + 26;
    } else if ('0' <= charCode && charCode <= '9') {
        // 52 - 61: 0123456789
        return charCode - '0' + 52;
    } else if (charCode == '+') {
        // 62: +
        return 62;
    } else if (charCode == '/') {
        // 63: /
        return 63;
    }
    return 64;
};

bool RevSourceMap::VlqRevCode(const std::string& vStr, std::vector<int32_t>& ans)
{
    if (vStr.size() == 0) {
        return false;
    }
    const int32_t VLQ_BASE_SHIFT = 5;
    // binary: 100000
    uint32_t VLQ_BASE = 1 << VLQ_BASE_SHIFT;
    // binary: 011111
    uint32_t VLQ_BASE_MASK = VLQ_BASE - 1;
    // binary: 100000
    uint32_t VLQ_CONTINUATION_BIT = VLQ_BASE;
    uint32_t result = 0;
    uint32_t shift = 0;
    bool continuation = 0;
    for (uint32_t i = 0; i < vStr.size(); i++) {
        uint32_t digit = Base64CharToInt(vStr[i]);
        if (digit == 64) {
            return false;
        }
        continuation = digit & VLQ_CONTINUATION_BIT;
        digit &= VLQ_BASE_MASK;
        result += digit << shift;
        if (continuation) {
            shift += VLQ_BASE_SHIFT;
        } else {
            bool isOdd = result & 1;
            result >>= 1;
            ans.push_back(isOdd ? -result : result);
            result = 0;
            shift = 0;
        }
    }
    if (continuation) {
        return false;
    }
    return true;
};

// The function is used to prase the sourcemap of stage-model project on the previewer and will be abandoned later.
void RevSourceMap::StageModeSourceMapSplit(const std::string& sourceMap,
    std::unordered_map<std::string, RefPtr<RevSourceMap>>& sourceMaps)
{
    size_t leftBracket = 0;
    size_t rightBracket = 0;
    while ((leftBracket = sourceMap.find(": {", rightBracket)) != std::string::npos) {
        size_t urlLeft = leftBracket;
        size_t urlRight = sourceMap.find("  \"", rightBracket) + 3;
        if (urlRight == std::string::npos) {
            continue;
        }
        std::string key = sourceMap.substr(urlRight, urlLeft - urlRight - 1);
        rightBracket = sourceMap.find("},", leftBracket);
        std::string value = sourceMap.substr(leftBracket, rightBracket);
        RefPtr<RevSourceMap> curMapData = MakeRefPtr<RevSourceMap>();
        MergeInit(value, curMapData);
        sourceMaps.emplace(key, curMapData);
    }
}
} // namespace OHOS::Ace::Framework
