/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_BUILDER_NODE_OPS_PEER_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_BUILDER_NODE_OPS_PEER_H

#include <vector>

#include "ui/base/referenced.h"

#include "core/components_ng/base/frame_node.h"

struct BuilderNodeOpsPeer {
    OHOS::Ace::NG::OptionalSizeF size_;
    OHOS::Ace::NodeRenderType renderType_ = OHOS::Ace::NodeRenderType::RENDER_TYPE_DISPLAY;
    std::string surfaceId_;
    OHOS::Ace::RefPtr<OHOS::Ace::NG::FrameNode> viewNode_;
    OHOS::Ace::RefPtr<OHOS::Ace::NG::UINode> realNode_;

    std::string ToString()
    {
        std::string result = "";
        result = result + "[size : " + size_.ToString() +
                 " ], [ renderType_: " + std::to_string(static_cast<uint32_t>(renderType_)) +
                 " ], [ surfaceId_ : " + surfaceId_ + "]";
        return result;
    }
    virtual ~BuilderNodeOpsPeer() = default;
};
#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_BUILDER_NODE_OPS_PEER_H