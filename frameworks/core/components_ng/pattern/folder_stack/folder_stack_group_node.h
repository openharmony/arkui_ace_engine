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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FOLDER_STACK_GROUP_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FOLDER_STACK_GROUP_NODE_H

#include <cstdint>
#include <list>
#include <variant>
#include <vector>

#include "base/memory/referenced.h"
#include "base/utils/macros.h"
#include "core/animation/page_transition_common.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/group_node.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT FolderStackGroupNode : public GroupNode {
    DECLARE_ACE_TYPE(FolderStackGroupNode, GroupNode)
public:
    FolderStackGroupNode(const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern)
        : GroupNode(tag, nodeId, pattern)
    {}
    ~FolderStackGroupNode() override = default;
    static RefPtr<FolderStackGroupNode> GetOrCreateGroupNode(
        const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator);
    void AddChildToGroup(const RefPtr<UINode>& child, int32_t slot = DEFAULT_NODE_SLOT) override;
    const RefPtr<UINode>& GetHoverNode() const
    {
        return hoverNode_;
    }

    void SetHoverNode(const RefPtr<UINode>& hoverNode)
    {
        hoverNode_ = hoverNode;
    }
    const RefPtr<UINode>& GetControlPartsStackNode() const
    {
        return desktopNode_;
    }
    void SetControlPartsStackNode(const RefPtr<UINode>& desktopNode)
    {
        desktopNode_ = desktopNode;
    }
    const std::vector<std::string>& GetItemId() const
    {
        return itemId_;
    }
    void SetItemId(const std::vector<std::string>& itemId)
    {
        itemId_ = itemId;
        isChangeItemId_ = true;
    }

    bool GetIsChangeItemId()
    {
        return isChangeItemId_;
    }

    void SetIsChangeItemId(bool isChangeItemId)
    {
        isChangeItemId_ = isChangeItemId;
    }

    const std::vector<RefPtr<UINode>>& GetChildNode() const
    {
        return childNode_;
    }

private:
    RefPtr<UINode> hoverNode_;
    RefPtr<UINode> desktopNode_;
    std::vector<std::string> itemId_;
    std::vector<RefPtr<UINode>> childNode_;
    bool isChangeItemId_ = false;
};
} // namespace OHOS::Ace::NG
#endif