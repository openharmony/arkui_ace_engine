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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_SWIPER_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_SWIPER_NODE_H

#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT SwiperNode : public FrameNode {
    DECLARE_ACE_TYPE(SwiperNode, FrameNode);

public:
    SwiperNode(const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern) : FrameNode(tag, nodeId, pattern)
    {}
    ~SwiperNode() override = default;

    void SetSpecialItemCount(int32_t specialItemCount)
    {
        specialItemCount_ = specialItemCount;
    }

    void AddChild(const RefPtr<UINode>& child, int32_t slot = DEFAULT_NODE_SLOT, bool silently = false,
        bool addDefaultTransition = false, bool addModalUiextension = false) override
    {
        if (slot == DEFAULT_NODE_SLOT) {
            UINode::AddChild(child, slot - specialItemCount_, silently, addDefaultTransition, addModalUiextension);
        } else {
            UINode::AddChild(child, slot, silently, addDefaultTransition, addModalUiextension);
        }
    }

private:
    int32_t specialItemCount_ = 0;

    ACE_DISALLOW_COPY_AND_MOVE(SwiperNode);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_SWIPER_NODE_H
