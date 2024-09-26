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

#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_TEST_UNITTEST_CAPI_COMMON_MODIFIERS_TEST_UTILS_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_TEST_UNITTEST_CAPI_COMMON_MODIFIERS_TEST_UTILS_H

#include <string>

#include "arkoala_api.h"
#include "frameworks/core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {

std::string GetStringAttribute(ArkUINodeHandle node, const std::string &name);
std::unique_ptr<JsonValue> GetJsonValue(ArkUINodeHandle node);

template <typename T>
T GetAttrValue(const std::unique_ptr<JsonValue> &jsonVal, const std::string &attrKey) = delete;

template<>
inline int GetAttrValue(const std::unique_ptr<JsonValue> &jsonVal, const std::string &attrKey)
{
    return jsonVal ? jsonVal->GetInt(attrKey) : int();
}

template<>
inline std::string GetAttrValue(const std::unique_ptr<JsonValue> &jsonVal, const std::string &attrKey)
{
    return jsonVal ? jsonVal->GetString(attrKey) : std::string();
}

template<>
inline std::unique_ptr<JsonValue> GetAttrValue(const std::unique_ptr<JsonValue> &jsonVal, const std::string &attrKey)
{
    if (jsonVal) {
        auto result = jsonVal->GetValue(attrKey);
        if (result->IsObject() || result->IsArray()) {
            return result;
        }
        if (result->IsString()) {
            return JsonUtil::ParseJsonData(result->GetString().c_str());
        }
    }
    return nullptr;
}

template<>
inline bool GetAttrValue(const std::unique_ptr<JsonValue> &jsonVal, const std::string &attrKey)
{
    return jsonVal ? jsonVal->GetBool(attrKey) : bool();
}

template<>
inline double GetAttrValue(const std::unique_ptr<JsonValue> &jsonVal, const std::string &attrKey)
{
    return jsonVal ? jsonVal->GetDouble(attrKey) : double();
}

template<>
inline std::optional<bool> GetAttrValue(const std::unique_ptr<JsonValue> &jsonVal, const std::string &attrKey)
{
    if (!jsonVal)
    {
        return std::nullopt;
    }
    auto val = jsonVal->GetValue(attrKey);
    return val && val->IsBool() ? std::optional<bool>(val->GetBool()) : std::nullopt;
}

template <typename T>
inline T GetAttrValue(ArkUINodeHandle node, const std::string &attrKey)
{
    return GetAttrValue<T>(GetJsonValue(node), attrKey);
}

template <typename T>
inline T GetAttrValue(const std::string &jsonObjAsStr, const std::string &attrKey)
{
    return GetAttrValue<T>(JsonUtil::ParseJsonData(jsonObjAsStr.c_str()), attrKey);
}
} // namespace OHOS::Ace::NG
#endif