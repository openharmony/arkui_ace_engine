/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "adapter/ohos/entrance/ui_session/ui_translate_request_util.h"

#include "interfaces/inner_api/ui_session/ui_session_json_util.h"

namespace OHOS::Ace::PageTranslateRequestUtil {
namespace {
int32_t GetHexValue(char ch)
{
    if (ch >= '0' && ch <= '9') {
        return ch - '0';
    }
    if (ch >= 'a' && ch <= 'f') {
        return ch - 'a' + 10;
    }
    if (ch >= 'A' && ch <= 'F') {
        return ch - 'A' + 10;
    }
    return -1;
}

bool ReadUnicodeEscape(const std::string& text, size_t pos, uint32_t& codePoint)
{
    constexpr size_t UNICODE_ESCAPE_LENGTH = 6;
    constexpr size_t HEX_DIGIT_COUNT = 4;
    if (pos + UNICODE_ESCAPE_LENGTH > text.size() || text[pos] != '\\' || text[pos + 1] != 'u') {
        return false;
    }
    uint32_t value = 0;
    for (size_t index = 0; index < HEX_DIGIT_COUNT; ++index) {
        auto hexValue = GetHexValue(text[pos + 2 + index]);
        if (hexValue < 0) {
            return false;
        }
        value = (value << 4) | static_cast<uint32_t>(hexValue);
    }
    codePoint = value;
    return true;
}

bool IsHighSurrogate(uint32_t codePoint)
{
    constexpr uint32_t HIGH_SURROGATE_BEGIN = 0xD800;
    constexpr uint32_t HIGH_SURROGATE_END = 0xDBFF;
    return codePoint >= HIGH_SURROGATE_BEGIN && codePoint <= HIGH_SURROGATE_END;
}

bool IsLowSurrogate(uint32_t codePoint)
{
    constexpr uint32_t LOW_SURROGATE_BEGIN = 0xDC00;
    constexpr uint32_t LOW_SURROGATE_END = 0xDFFF;
    return codePoint >= LOW_SURROGATE_BEGIN && codePoint <= LOW_SURROGATE_END;
}

uint32_t CombineSurrogatePair(uint32_t highSurrogate, uint32_t lowSurrogate)
{
    constexpr uint32_t HIGH_SURROGATE_BEGIN = 0xD800;
    constexpr uint32_t LOW_SURROGATE_BEGIN = 0xDC00;
    constexpr uint32_t SUPPLEMENTARY_PLANE_BEGIN = 0x10000;
    constexpr uint32_t SURROGATE_SHIFT = 10;
    return SUPPLEMENTARY_PLANE_BEGIN + ((highSurrogate - HIGH_SURROGATE_BEGIN) << SURROGATE_SHIFT) +
           (lowSurrogate - LOW_SURROGATE_BEGIN);
}

void AppendUtf8(std::string& output, uint32_t codePoint)
{
    constexpr uint32_t ONE_BYTE_LIMIT = 0x7F;
    constexpr uint32_t TWO_BYTE_LIMIT = 0x7FF;
    constexpr uint32_t THREE_BYTE_LIMIT = 0xFFFF;
    constexpr uint32_t FOUR_BYTE_LIMIT = 0x10FFFF;
    constexpr uint8_t CONTINUATION_MASK = 0x80;
    constexpr uint8_t CONTINUATION_BITS = 0x3F;
    if (codePoint <= ONE_BYTE_LIMIT) {
        output.push_back(static_cast<char>(codePoint));
    } else if (codePoint <= TWO_BYTE_LIMIT) {
        output.push_back(static_cast<char>(0xC0 | (codePoint >> 6)));
        output.push_back(static_cast<char>(CONTINUATION_MASK | (codePoint & CONTINUATION_BITS)));
    } else if (codePoint <= THREE_BYTE_LIMIT) {
        output.push_back(static_cast<char>(0xE0 | (codePoint >> 12)));
        output.push_back(static_cast<char>(CONTINUATION_MASK | ((codePoint >> 6) & CONTINUATION_BITS)));
        output.push_back(static_cast<char>(CONTINUATION_MASK | (codePoint & CONTINUATION_BITS)));
    } else if (codePoint <= FOUR_BYTE_LIMIT) {
        output.push_back(static_cast<char>(0xF0 | (codePoint >> 18)));
        output.push_back(static_cast<char>(CONTINUATION_MASK | ((codePoint >> 12) & CONTINUATION_BITS)));
        output.push_back(static_cast<char>(CONTINUATION_MASK | ((codePoint >> 6) & CONTINUATION_BITS)));
        output.push_back(static_cast<char>(CONTINUATION_MASK | (codePoint & CONTINUATION_BITS)));
    }
}

bool ParseTranslateResultItem(const std::unique_ptr<InspectorJsonValue>& json, TranslateResult& result)
{
    if (json == nullptr || !json->IsObject()) {
        return false;
    }
    auto nodeIdValue = json->GetValue("nodeId");
    auto versionValue = json->GetValue("version");
    if (nodeIdValue == nullptr || !nodeIdValue->IsNumber() || versionValue == nullptr || !versionValue->IsNumber()) {
        return false;
    }
    auto nodeId = nodeIdValue->GetInt();
    if (nodeId < 0) {
        return false;
    }
    std::string translatedText;
    auto translatedTextValue = json->GetValue("translatedText");
    if (translatedTextValue != nullptr && translatedTextValue->IsString()) {
        translatedText = translatedTextValue->GetString();
    }
    if (translatedText.empty()) {
        auto textValue = json->GetValue("text");
        if (textValue != nullptr && textValue->IsString()) {
            translatedText = textValue->GetString();
        }
    }
    translatedText = DecodeJsonUnicodeEscapes(translatedText);
    if (translatedText.empty()) {
        return false;
    }
    result.nodeId = nodeId;
    result.version = versionValue->GetInt64();
    result.translatedText = std::move(translatedText);
    return true;
}

bool ParseTranslateResultIdentityItem(
    const std::unique_ptr<InspectorJsonValue>& json, std::pair<int32_t, int64_t>& identity)
{
    if (json == nullptr || !json->IsObject()) {
        return false;
    }
    auto nodeId = json->GetInt("nodeId", -1);
    auto versionValue = json->GetValue("version");
    if (nodeId < 0 || versionValue == nullptr || !versionValue->IsNumber()) {
        return false;
    }
    identity = { nodeId, versionValue->GetInt64() };
    return true;
}

void ParseIdentityArray(const std::unique_ptr<InspectorJsonValue>& array,
    std::vector<std::pair<int32_t, int64_t>>& identities)
{
    if (array == nullptr || !array->IsArray()) {
        return;
    }
    for (int32_t index = 0; index < array->GetArraySize(); ++index) {
        std::pair<int32_t, int64_t> itemIdentity;
        if (ParseTranslateResultIdentityItem(array->GetArrayItem(index), itemIdentity)) {
            identities.emplace_back(itemIdentity);
        }
    }
}

bool ParseResultArray(const std::unique_ptr<InspectorJsonValue>& array, std::vector<TranslateResult>& results)
{
    if (array == nullptr || !array->IsArray()) {
        return false;
    }
    for (int32_t index = 0; index < array->GetArraySize(); ++index) {
        TranslateResult result;
        if (ParseTranslateResultItem(array->GetArrayItem(index), result)) {
            results.emplace_back(std::move(result));
        }
    }
    return !results.empty();
}
} // namespace

bool IsTranslateScopeValid(int32_t scope)
{
    return scope != 0 && (scope & ~PAGE_ALL_TRANSLATE_SCOPE) == 0;
}

bool IsPageTranslateRequestValid(const std::string& request)
{
    auto json = InspectorJsonUtil::ParseJsonString(request);
    if (json == nullptr || !json->IsObject()) {
        return true;
    }
    auto scopeValue = json->GetValue("scope");
    if (scopeValue == nullptr || scopeValue->IsNull()) {
        return true;
    }
    if (!scopeValue->IsNumber()) {
        return false;
    }
    return IsTranslateScopeValid(scopeValue->GetInt());
}

std::string DecodeJsonUnicodeEscapes(const std::string& text)
{
    constexpr size_t UNICODE_ESCAPE_LENGTH = 6;
    std::string output;
    output.reserve(text.size());
    for (size_t pos = 0; pos < text.size();) {
        uint32_t codePoint = 0;
        if (!ReadUnicodeEscape(text, pos, codePoint)) {
            output.push_back(text[pos++]);
            continue;
        }
        if (IsHighSurrogate(codePoint)) {
            uint32_t lowSurrogate = 0;
            auto lowSurrogatePos = pos + UNICODE_ESCAPE_LENGTH;
            if (ReadUnicodeEscape(text, lowSurrogatePos, lowSurrogate) && IsLowSurrogate(lowSurrogate)) {
                AppendUtf8(output, CombineSurrogatePair(codePoint, lowSurrogate));
                pos += UNICODE_ESCAPE_LENGTH * 2;
                continue;
            }
            output.append(text, pos, UNICODE_ESCAPE_LENGTH);
            pos += UNICODE_ESCAPE_LENGTH;
            continue;
        }
        if (IsLowSurrogate(codePoint)) {
            output.append(text, pos, UNICODE_ESCAPE_LENGTH);
            pos += UNICODE_ESCAPE_LENGTH;
            continue;
        }
        AppendUtf8(output, codePoint);
        pos += UNICODE_ESCAPE_LENGTH;
    }
    return output;
}

std::vector<std::pair<int32_t, int64_t>> ParseTranslateResultIdentities(const std::string& content)
{
    std::vector<std::pair<int32_t, int64_t>> identities;
    auto json = InspectorJsonUtil::ParseJsonString(content);
    std::pair<int32_t, int64_t> identity;
    if (ParseTranslateResultIdentityItem(json, identity)) {
        identities.emplace_back(identity);
        return identities;
    }
    if (json == nullptr) {
        return identities;
    }
    if (json->IsArray()) {
        ParseIdentityArray(json, identities);
        return identities;
    }
    ParseIdentityArray(json->GetValue("results"), identities);
    return identities;
}

bool ParseTranslateResults(const std::string& content, std::vector<TranslateResult>& results)
{
    results.clear();
    auto json = InspectorJsonUtil::ParseJsonString(content);
    if (json == nullptr) {
        return false;
    }
    if (json->IsArray()) {
        return ParseResultArray(json, results);
    }
    if (!json->IsObject()) {
        return false;
    }
    auto batchResults = json->GetValue("results");
    if (batchResults != nullptr && batchResults->IsArray()) {
        return ParseResultArray(batchResults, results);
    }
    TranslateResult result;
    if (!ParseTranslateResultItem(json, result)) {
        return false;
    }
    results.emplace_back(std::move(result));
    return true;
}
} // namespace OHOS::Ace::PageTranslateRequestUtil
