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

#include "modifiers_test_utils.h"

#include <fstream>
#include <iostream>

#include <gtest/gtest.h>

#include "base/utils/string_utils.h"

namespace OHOS::Ace::NG {
std::unique_ptr<JsonValue> GetJsonValue(Ark_NodeHandle node)
{
    static const InspectorFilter inspector;

    if (auto fnode = reinterpret_cast<FrameNode *>(node); fnode) {
        if (auto jsonVal = JsonUtil::Create(true); jsonVal) {
            fnode->ToJsonValue(jsonVal, inspector);
            return jsonVal;
        }
    }
    return nullptr;
}

std::unique_ptr<JsonValue> GetLayoutJsonValue(Ark_NodeHandle node)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto layout = frameNode->GetLayoutProperty();
    CHECK_NULL_RETURN(layout, nullptr);

    static const InspectorFilter inspector;

    if (auto jsonVal = JsonUtil::Create(true); jsonVal) {
        layout->ToJsonValue(jsonVal, inspector);
        return jsonVal;
    }
    return nullptr;
}

std::unique_ptr<JsonValue> GetPatternJsonValue(Ark_NodeHandle node)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_RETURN(pattern, nullptr);

    static const InspectorFilter inspector;

    if (auto jsonVal = JsonUtil::Create(true); jsonVal) {
        pattern->ToJsonValue(jsonVal, inspector);
        return jsonVal;
    }
    return nullptr;
}

template<>
std::optional<std::string> GetAttrValue(const std::unique_ptr<JsonValue> &jsonVal, const std::string &attrKey)
{
    if (jsonVal) {
        auto val = jsonVal->GetValue(attrKey);
        if (!val->IsValid()) {
            return std::nullopt;
        }
        if (val->IsObject() || val->IsArray() || val->IsBool() || val->IsNumber()) {
            return val->ToString();
        }
        return val->GetString();
    }
    return std::nullopt;
}

template<>
std::optional<int> GetAttrValue(const std::unique_ptr<JsonValue> &jsonVal, const std::string &attrKey)
{
    if (!jsonVal) {
        return std::nullopt;
    }
    auto val = jsonVal->GetValue(attrKey);
    if (!val->IsValid()) {
        return std::nullopt;
    }
    if (val->IsString()) {
        char* pEnd = nullptr;
        auto str = val->GetString();
        int64_t result = std::strtol(str.c_str(), &pEnd, 10);
        if (pEnd == str.c_str() || (result < INT_MIN || result > INT_MAX) || errno == ERANGE) {
            return std::nullopt;
        }
        return result;
    }
    return val->IsNumber() ? std::make_optional(val->GetInt()) : std::nullopt;
}

template<>
std::optional<double> GetAttrValue(const std::unique_ptr<JsonValue> &jsonVal, const std::string &attrKey)
{
    if (!jsonVal) {
        return std::nullopt;
    }
    auto val = jsonVal->GetValue(attrKey);
    if (!val->IsValid()) {
        return std::nullopt;
    }
    if (val->IsString()) {
        double result;
        return StringUtils::StringToDouble(val->GetString(), result) ? std::make_optional(result) : std::nullopt;
    }
    return val->IsNumber() ? std::make_optional(val->GetDouble()) : std::nullopt;
}

template<>
std::optional<bool> GetAttrValue(const std::unique_ptr<JsonValue> &jsonVal, const std::string &attrKey)
{
    if (!jsonVal) {
        return std::nullopt;
    }
    auto val = jsonVal->GetValue(attrKey);
    if (!val->IsValid()) {
        return std::nullopt;
    }
    if (val->IsString()) {
        auto result = val->GetString();
        if (result == "true") {
            return true;
        }
        if (result == "false") {
            return false;
        }
        return std::nullopt;
    }
    return val->IsBool() ? std::optional<bool>(val->GetBool()) : std::nullopt;
}

std::unique_ptr<JsonValue> GetAttrObject(const std::unique_ptr<JsonValue> &jsonVal, const std::string &attrKey)
{
    if (jsonVal) {
        auto result = jsonVal->GetValue(attrKey);
        if (!result) {
            return nullptr;
        }
        if (result->IsObject() || result->IsArray()) {
            return result;
        }
        if (result->IsString()) {
            return JsonUtil::ParseJsonData(result->GetString().c_str());
        }
    }
    return nullptr;
}

Ark_Resource CreateResource(int64_t id, ResourceType type)
{
    return Converter::ArkCreate<Ark_Resource>(id, type);
}

Ark_Resource CreateResource(const std::string& name, ResourceType type)
{
    static Converter::ConvContext s_ctx;
    return Converter::ArkCreate<Ark_Resource>(name, type, &s_ctx);
}

void DumpJsonToFile(Ark_NodeHandle node, int index)
{
    if (!::testing::Test::HasFailure()) {
        return;
    }
    std::stringstream fname;
    std::string name = ::testing::UnitTest::GetInstance()->current_test_info()->name();
    std::replace(name.begin(), name.end(), '/', '_');
    fname << name;
    if (index >= 0) {
        fname << index;
    }
    fname << ".json";
    std::fstream file(fname.str(), file.out);
    if (file.is_open()) {
        auto jsonVal = GetJsonValue(node);
        if (jsonVal) {
            file << jsonVal->ToString();
        }
    }
}
} // namespace OHOS::Ace::NG
