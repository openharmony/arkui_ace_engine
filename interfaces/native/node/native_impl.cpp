/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#include "native_interface.h"
#include "native_node.h"
#include "node/node_model.h"

#include "base/log/log_wrapper.h"

namespace {

constexpr int32_t CURRENT_NATIVE_NODE_API_VERSION = 1;
ArkUI_NativeNodeAPI_1 nodeImpl_1 = {
    CURRENT_NATIVE_NODE_API_VERSION,
    OHOS::Ace::NodeModel::CreateNode,
    OHOS::Ace::NodeModel::DisposeNode,
    OHOS::Ace::NodeModel::AddChild,
    OHOS::Ace::NodeModel::RemoveChild,
    OHOS::Ace::NodeModel::InsertChildAfter,
    nullptr,
    nullptr,
    OHOS::Ace::NodeModel::SetAttribute,
    OHOS::Ace::NodeModel::GetAttribute,
    OHOS::Ace::NodeModel::ResetAttribute,
    OHOS::Ace::NodeModel::RegisterNodeEvent,
    OHOS::Ace::NodeModel::UnregisterNodeEvent,
    OHOS::Ace::NodeModel::RegisterOnEvent,
    OHOS::Ace::NodeModel::UnregisterOnEvent,
    OHOS::Ace::NodeModel::MarkDirty,
};

} // namespace

#ifdef __cplusplus
extern "C" {
#endif

ArkUI_AnyNativeAPI* OH_ArkUI_GetNativeAPI(ArkUI_NativeAPIVariantKind type, int32_t version)
{
    if (!OHOS::Ace::NodeModel::GetFullImpl()) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_NATIVE_NODE,
            "fail to get %{public}d node api family of %{public}d version, impl library is not found", type, version);
        return nullptr;
    }
    switch (type) {
        case ARKUI_NATIVE_NODE: {
            switch (version) {
                case CURRENT_NATIVE_NODE_API_VERSION:
                    return reinterpret_cast<ArkUI_AnyNativeAPI*>(&nodeImpl_1);
                default: {
                    TAG_LOGE(OHOS::Ace::AceLogTag::ACE_NATIVE_NODE,
                        "fail to get basic node api family, version is incorrect: %{public}d", version);
                    return nullptr;
                }
            }
            break;
        }
        default: {
            TAG_LOGE(OHOS::Ace::AceLogTag::ACE_NATIVE_NODE,
                "fail to get %{public}d node api family, version is incorrect: %{public}d", type, version);
            return nullptr;
        }
    }
}

#ifdef __cplusplus
};
#endif
