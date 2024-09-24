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

namespace OHOS::Ace::NG {
std::string GetStringAttribute(ArkUINodeHandle node, const std::string &name)
{
    static const InspectorFilter inspector;
    if (auto fnode = reinterpret_cast<FrameNode *>(node); fnode) {
        if (auto jsonVal = JsonUtil::Create(true); jsonVal) {
            fnode->ToJsonValue(jsonVal, inspector);
            auto val = jsonVal->GetValue(name);
            return (val && (val->IsObject() || val->IsArray())) ? val->ToString() : jsonVal->GetString(name);
        }
    }
    return {};
}

std::optional<bool> GetBoolAttribute(ArkUINodeHandle node, const std::string &name)
{
    static const InspectorFilter inspector;
    std::optional<bool> retVal;

    if (auto fnode = reinterpret_cast<FrameNode *>(node); fnode) {
        if (auto jsonVal = JsonUtil::Create(true); jsonVal) {
            fnode->ToJsonValue(jsonVal, inspector);
            if (jsonVal->Contains(name))
            {
                auto val = jsonVal->GetValue(name);
                if (val->IsBool())
                {
                    retVal = val->GetBool();
                }
            }
        }
    }
    return retVal;
}

std::unique_ptr<JsonValue> GetJsonValue(ArkUINodeHandle node)
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

}