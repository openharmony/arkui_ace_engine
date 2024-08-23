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
inline std::string GetStringAttribute(ArkUINodeHandle node, const std::string &name)
{
    static const InspectorFilter inspector;

    if (auto fnode = reinterpret_cast<FrameNode *>(node); fnode) {
        if (auto jsonVal = JsonUtil::Create(true); jsonVal) {
            fnode->ToJsonValue(jsonVal, inspector);
            auto val = jsonVal->GetValue(name);
            if (val) {
                if (val->IsString()) return jsonVal->GetString(name);
                if (val->IsNumber()) return std::to_string(jsonVal->GetInt(name));
            }
        }
    }
    return {};
}
} // namespace OHOS::Ace::NG
#endif