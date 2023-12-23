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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_TOOL_BAR_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_TOOL_BAR_NODE_H

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT NavToolbarNode : public FrameNode {
    DECLARE_ACE_TYPE(NavToolbarNode, FrameNode)
public:
    NavToolbarNode(const std::string& tag, int32_t nodeId);
    NavToolbarNode(const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern)
        : FrameNode(tag, nodeId, pattern)
    {}
    ~NavToolbarNode() override = default;
    static RefPtr<NavToolbarNode> GetOrCreateToolbarNode(
        const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator);

    bool IsAtomicNode() const override
    {
        return false;
    }

    void SetToolbarContainerNode(const RefPtr<UINode>& toolbarContainerNode)
    {
        toolbarContainerNode_ = toolbarContainerNode;
    }

    const RefPtr<UINode>& GetToolbarContainerNode() const
    {
        return toolbarContainerNode_;
    }

    void SetIsUseNewToolbar(bool isNewToolbar)
    {
        isNewToolbar_ = isNewToolbar;
    }

    bool IsUsedNewToolbar() const
    {
        return isNewToolbar_;
    }

    void SetHasValidContent(bool has)
    {
        hasValidContent_ = has;
    }

    bool HasValidContent() const
    {
        return hasValidContent_;
    }

private:
    RefPtr<UINode> toolbarContainerNode_;
    bool isNewToolbar_ = false;
    bool hasValidContent_ = false;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_TOOL_BAR_NODE_H
