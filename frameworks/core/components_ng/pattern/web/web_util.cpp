/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#include "web_util.h"
#include <cctype>

namespace OHOS::Ace {

void WebUtil::SkipWhitespace(std::string_view json, size_t& i)
{
    while (i < json.length() && std::isspace(static_cast<unsigned char>(json[i]))) {
        i++;
    }
}

std::string WebUtil::ExtractString(std::string_view json, size_t& i)
{
    std::string res;
    if (i >= json.length()) { return res; }
    i++;
    while (i < json.length()) {
        if (json[i] == '\\' && i + 1 < json.length()) {
            res += json[++i];
        } else if (json[i] == '"') {
            i++;
            break;
        } else {
            res += json[i];
        }
        i++;
    }
    return res;
}

void WebUtil::SkipNestedStructure(std::string_view json, size_t& i)
{
    char startChar = json[i];
    char endChar = (startChar == '{' ? '}' : ']');
    int depth = 0;
    while (i < json.length()) {
        if (json[i] == '"') {
            ExtractString(json, i);
            continue;
        }
        if (json[i] == startChar) {
            depth++;
        } else if (json[i] == endChar) {
            depth--;
        }
        i++;
        if (depth <= 0) {
            break;
        }
    }
}

void WebUtil::SkipValue(std::string_view json, size_t& i)
{
    SkipWhitespace(json, i);
    if (i >= json.length()) {
        return;
    }
    char c = json[i];
    if (c == '"') {
        ExtractString(json, i);
    } else if (c == '{' || c == '[') {
        SkipNestedStructure(json, i);
    } else {
        while (i < json.length() && json[i] != ',' && json[i] != '}' && json[i] != ']') {
            i++;
        }
    }
}

bool WebUtil::HandleKeyDetection(std::string_view json, size_t& i,
                                 std::vector<std::unordered_set<std::string>>& stack)
{
    std::string key = ExtractString(json, i);
    SkipWhitespace(json, i);
    if (i >= json.length() || json[i] != ':') {
        return false;
    }
    i++;
    if (!stack.empty()) {
        if (!stack.back().insert(key).second) {
            return true;
        }
    }
    SkipValue(json, i);
    return false;
}

bool WebUtil::HasJSONDuplicateKeys(std::string_view json)
{
    std::vector<std::unordered_set<std::string>> stack;
    size_t i = 0;
    while (i < json.length()) {
        SkipWhitespace(json, i);
        if (i >= json.length()) { break; }
        char c = json[i];
        if (c == '{') {
            if (stack.size() >= maxJsonDepth) { return false; }
            stack.emplace_back();
            i++;
        } else if (c == '}') {
            if (!stack.empty()) { stack.pop_back(); }
            i++;
        } else if (c == '"') {
            if (HandleKeyDetection(json, i, stack)) { return true; }
        } else {
            i++;
        }
    }
    return false;
}
} // namespace OHOS::Ace