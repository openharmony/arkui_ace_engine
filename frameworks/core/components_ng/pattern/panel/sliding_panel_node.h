/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PANEL_PANEL_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PANEL_PANEL_NODE_H

#include <optional>

#include "core/components_ng/base/group_node.h"
#include "core/components_ng/pattern/panel/sliding_panel_pattern.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT SlidingPanelNode : public GroupNode {
    DECLARE_ACE_TYPE(SlidingPanelNode, GroupNode);

public:
    SlidingPanelNode() = delete;
    SlidingPanelNode(const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern, bool isRoot = false)
        : GroupNode(tag, nodeId, pattern, isRoot)
    {}
    ~SlidingPanelNode() override = default;
    void AddChildToGroup(const RefPtr<UINode>& child, int32_t slot = DEFAULT_NODE_SLOT) override;
    bool HasColumnNode() const
    {
        return columnId_.has_value();
    }

    int32_t GetColumnId()
    {
        if (!columnId_.has_value()) {
            columnId_ = ElementRegister::GetInstance()->MakeUniqueId();
        }
        return columnId_.value();
    }

    int32_t GetDragBarId()
    {
        if (!dragBarId_.has_value()) {
            dragBarId_ = ElementRegister::GetInstance()->MakeUniqueId();
        }
        return dragBarId_.value();
    }

    int32_t GetContentId()
    {
        if (!contentId_.has_value()) {
            contentId_ = ElementRegister::GetInstance()->MakeUniqueId();
        }
        return contentId_.value();
    }

private:
    std::optional<int32_t> columnId_;
    std::optional<int32_t> dragBarId_;
    std::optional<int32_t> contentId_;
    std::set<int32_t> columnChildren_;
    std::map<int32_t, RefPtr<UINode>> builderNode_;

    ACE_DISALLOW_COPY_AND_MOVE(SlidingPanelNode);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PANEL_PANEL_NODE_H