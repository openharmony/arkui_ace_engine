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

#include <fstream>

#include "gtest/gtest.h"

#include "modifiers_test_utils.h"
#include "iostream"

namespace OHOS::Ace::NG {

std::string GetStringAttribute(Ark_NodeHandle node, const std::string &name)
{
    static const InspectorFilter inspector;
    if (auto fnode = reinterpret_cast<FrameNode *>(node); fnode) {
        if (auto jsonVal = JsonUtil::Create(true); jsonVal) {
            fnode->ToJsonValue(jsonVal, inspector);
            auto val = jsonVal->GetValue(name);
            return (val &&
                (val->IsObject() || val->IsArray() || val->IsNumber() || val->IsBool()))
                    ? val->ToString() : jsonVal->GetString(name);
        }
    }
    return {};
}

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
std::string GetAttrValue(const std::unique_ptr<JsonValue> &jsonVal, const std::string &attrKey)
{
    if (jsonVal) {
        auto result = jsonVal->GetValue(attrKey);
        if (result->IsObject() || result->IsArray()) {
            return result->ToString();
        } else if (result->IsBool()) {
            return result->GetBool() ? "true" : "false";
        } else if (result->IsNumber()) {
            return StringUtils::DoubleToString(result->GetDouble());
        }
        return jsonVal->GetString(attrKey);
    }
    return std::string();
}

Ark_Resource CreateResource(uint32_t id, OHOS::Ace::NG::NodeModifier::ResourceType type)
{
    return {
        .id = Converter::ArkValue<Ark_Number>(id),
        .type = Converter::ArkValue<Opt_Number>(static_cast<uint32_t>(type)),
        .moduleName = Converter::ArkValue<Ark_String>(""),
        .bundleName = Converter::ArkValue<Ark_String>(""),
        .params = Converter::ArkValue<Opt_Array_String>(),
    };
}

Ark_Resource CreateResource(const char *name, OHOS::Ace::NG::NodeModifier::ResourceType type)
{
    static std::vector<std::unique_ptr<Ark_String>> s_strCache;
    s_strCache.emplace_back(std::make_unique<Ark_String>(Converter::ArkValue<Ark_String>(name)));
    Array_String params = {.length = 1, .array = s_strCache.back().get()};
    return {
        .id = Converter::ArkValue<Ark_Number>(-1),
        .type = Converter::ArkValue<Opt_Number>(static_cast<uint32_t>(type)),
        .moduleName = Converter::ArkValue<Ark_String>(""),
        .bundleName = Converter::ArkValue<Ark_String>(""),
        .params = Converter::ArkValue<Opt_Array_String>(params),
    };
}

void DumpJsonToFile(Ark_NodeHandle node, int index)
{
    if (!::testing::Test::HasFailure()) {
        return;
    }
    std::stringstream fname;
    fname << ::testing::UnitTest::GetInstance()->current_test_info()->name();
    if (index >= 0) {
        fname << index;
    }
    fname << ".json";
    std::fstream file(fname.str(), file.out);
    if (file.is_open()) {
        auto jsonVal = GetJsonValue(node);
        file << jsonVal->ToString();
    }
}
} // namespace OHOS::Ace::NG
