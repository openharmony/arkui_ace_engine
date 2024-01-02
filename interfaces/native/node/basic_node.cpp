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

#include "basic_node.h"

#include "node_model.h"

#include "base/log/log_wrapper.h"

namespace {

constexpr int CURRENT_NDK_VERSION = 11;

ArkUI_BasicNodeAPI basicImpl_11 = {
    CURRENT_NDK_VERSION,
    OHOS::Ace::NodeModel::CreateNode,
    OHOS::Ace::NodeModel::DisposeNode,
    OHOS::Ace::NodeModel::AddChild,
    OHOS::Ace::NodeModel::RemoveChild,
    OHOS::Ace::NodeModel::InsertChildAfter,
    OHOS::Ace::NodeModel::SetAttribute,
    OHOS::Ace::NodeModel::GetAttribute,
    OHOS::Ace::NodeModel::ResetAttribute,
    OHOS::Ace::NodeModel::RegisterNodeEvent,
    OHOS::Ace::NodeModel::UnregisterNodeEvent,
    OHOS::Ace::NodeModel::RegisterOnEvent,
    OHOS::Ace::NodeModel::UnregisterOnEvent,
    OHOS::Ace::NodeModel::ApplyModifierFinish,
    OHOS::Ace::NodeModel::MarkDirty,
};

} // namespace

#ifdef __cplusplus
extern "C" {
#endif

ArkUI_AnyBasicNodeAPI* OH_ArkUI_GetBasicNodeAPI(int32_t version)
{
    switch (version) {
        case CURRENT_NDK_VERSION:
            return reinterpret_cast<ArkUI_AnyBasicNodeAPI*>(&basicImpl_11);
        default: {
            TAG_LOGE(OHOS::Ace::AceLogTag::ACE_NATIVE_NODE,
                "fail to get basic node api family, version is incorrect: %{public}d", version);
            return nullptr;
        }
    }
}

#ifdef __cplusplus
};
#endif
