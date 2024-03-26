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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CUSTOM_FRAME_NODE_CUSTOM_FRAME_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CUSTOM_FRAME_NODE_CUSTOM_FRAME_NODE_H

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/custom_frame_node/custom_frame_node_pattern.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT CustomFrameNode : public FrameNode {
    DECLARE_ACE_TYPE(CustomFrameNode, FrameNode);

public:
    CustomFrameNode(const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern, bool isRoot = false)
        : FrameNode(tag, nodeId, pattern, isRoot)
    {}
    ~CustomFrameNode() override = default;

    static RefPtr<FrameNode> GetOrCreateCustomFrameNode(int32_t nodeId)
    {
        std::string tag = "CustomFrameNode";
        auto frameNode = GetFrameNode(tag, nodeId);
        if (frameNode) {
            return frameNode;
        }
        auto pattern = AceType::MakeRefPtr<CustomFrameNodePattern>();
        frameNode = AceType::MakeRefPtr<CustomFrameNode>(tag, nodeId, pattern, false);
        ElementRegister::GetInstance()->AddUINode(frameNode);
        frameNode->InitializePatternAndContext();
        return frameNode;
    }
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CUSTOM_FRAME_NODE_CUSTOM_FRAME_NODE_H
