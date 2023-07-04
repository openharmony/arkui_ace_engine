/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_ITEM_GROUP_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_ITEM_GROUP_PATTERN_H

#include "base/memory/referenced.h"
#include "base/utils/noncopyable.h"
#include "base/utils/utils.h"
#include "core/components_ng/pattern/list/list_item_group_accessibility_property.h"
#include "core/components_ng/pattern/list/list_item_group_layout_algorithm.h"
#include "core/components_ng/pattern/list/list_item_group_layout_property.h"
#include "core/components_ng/pattern/list/list_layout_property.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/syntax/shallow_builder.h"

namespace OHOS::Ace::NG {

struct ListItemGroupPaintInfo {
    bool vertical = false;
    int32_t lanes = 1;
    float spaceWidth = 0.0f;
    float laneGutter = 0.0f;
    float childCrossSize = 0.0f;
};

class ACE_EXPORT ListItemGroupPattern : public Pattern {
    DECLARE_ACE_TYPE(ListItemGroupPattern, Pattern);

public:
    explicit ListItemGroupPattern(
        const RefPtr<ShallowBuilder>& shallowBuilder, V2::ListItemGroupStyle listItemGroupStyle)
        : shallowBuilder_(shallowBuilder), listItemGroupStyle_(listItemGroupStyle)
    {}
    ~ListItemGroupPattern() override = default;

    bool IsAtomicNode() const override
    {
        return false;
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<ListItemGroupLayoutProperty>();
    }

    RefPtr<AccessibilityProperty> CreateAccessibilityProperty() override
    {
        return MakeRefPtr<ListItemGroupAccessibilityProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override;

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override;

    void AddHeader(const RefPtr<NG::UINode>& header)
    {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        if (headerIndex_ < 0) {
            headerIndex_ = itemStartIndex_;
            host->AddChild(header);
            itemStartIndex_++;
        } else {
            host->ReplaceChild(host->GetChildAtIndex(headerIndex_), header);
        }
        auto frameNode  = AceType::DynamicCast<FrameNode>(header);
        CHECK_NULL_VOID(frameNode);
        auto renderContext = frameNode->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        renderContext->UpdateZIndex(1);
    }

    void AddFooter(const RefPtr<NG::UINode>& footer)
    {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        if (footerIndex_ < 0) {
            footerIndex_ = itemStartIndex_;
            host->AddChild(footer);
            itemStartIndex_++;
        } else {
            host->ReplaceChild(host->GetChildAtIndex(footerIndex_), footer);
        }
        auto frameNode  = AceType::DynamicCast<FrameNode>(footer);
        CHECK_NULL_VOID(frameNode);
        auto renderContext = frameNode->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        renderContext->UpdateZIndex(1);
    }

    const ListItemGroupLayoutAlgorithm::PositionMap& GetItemPosition()
    {
        return itemPosition_;
    }

    void SetIndexInList(int32_t index)
    {
        indexInList_ = index;
    }

    int32_t GetIndexInList() const
    {
        return indexInList_;
    }

    int32_t GetDisplayEndIndexInGroup() const
    {
        return itemDisplayEndIndex_;
    }

    int32_t GetDiasplayStartIndexInGroup() const
    {
        return itemDiasplayStartIndex_;
    }

    int32_t GetEndIndexInGroup() const
    {
        return (itemTotalCount_ - 1);
    }

    int32_t GetLanesInGroup() const
    {
        return lanes_;
    }

    V2::ListItemGroupStyle GetListItemGroupStyle()
    {
        return listItemGroupStyle_;
    }

private:
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    void OnAttachToFrameNode() override;
    void SetListItemGroupDefaultAttributes(const RefPtr<FrameNode>& itemGroupNode);
    RefPtr<ShallowBuilder> shallowBuilder_;
    V2::ListItemGroupStyle listItemGroupStyle_ = V2::ListItemGroupStyle::NONE;

    int32_t indexInList_ = 0;

    int32_t headerIndex_ = -1;
    int32_t footerIndex_ = -1;
    int32_t itemStartIndex_ = 0;
    int32_t itemTotalCount_ = -1;
    int32_t itemDisplayEndIndex_ = -1;
    int32_t itemDiasplayStartIndex_ = -1;

    ListItemGroupLayoutAlgorithm::PositionMap itemPosition_;
    float spaceWidth_ = 0.0f;
    Axis axis_ = Axis::VERTICAL;
    int32_t lanes_ = 1;
    float laneGutter_ = 0.0f;
    float childCrossSize_ = 0.0f;
    ACE_DISALLOW_COPY_AND_MOVE(ListItemGroupPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_ITEM_PATTERN_H
