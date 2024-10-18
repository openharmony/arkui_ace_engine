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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WATERFLOW_WATER_FLOW_ITEM_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WATERFLOW_WATER_FLOW_ITEM_NODE_H

#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {
class WaterFlowItemNode : public FrameNode {
    DECLARE_ACE_TYPE(WaterFlowItemNode, FrameNode);

public:
    WaterFlowItemNode(const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern)
        : FrameNode(tag, nodeId, pattern)
    {}

    static RefPtr<FrameNode> GetOrCreateFlowItem(
        const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator);
    static RefPtr<FrameNode> CreateFlowItem(
        const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern);

private:
    /**
     * @brief Mark Parent (WaterFlow) dirty with flag PROPERTY_UPDATE_BY_CHILD_REQUEST,
     * and also notify Parent the index of this child.
     *
     * @return true if Parent is marked dirty successfully
     */
    bool RequestParentDirty() override;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WATERFLOW_WATER_FLOW_ITEM_NODE_H
