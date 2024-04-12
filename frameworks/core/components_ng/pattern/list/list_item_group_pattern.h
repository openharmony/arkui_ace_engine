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
#include "core/components_ng/pattern/list/list_children_main_size.h"
#include "core/components_ng/pattern/list/list_item_group_layout_algorithm.h"
#include "core/components_ng/pattern/list/list_item_group_layout_property.h"
#include "core/components_ng/pattern/list/list_layout_property.h"
#include "core/components_ng/pattern/list/list_position_map.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/syntax/shallow_builder.h"

namespace OHOS::Ace::NG {

struct ListItemGroupPaintInfo {
    bool vertical = false;
    int32_t lanes = 1;
    float spaceWidth = 0.0f;
    float laneGutter = 0.0f;
    int32_t totalItemCount = 0;
};

enum ListItemGroupArea {
    NONE_AREA,
    IN_LIST_ITEM_AREA,
    IN_HEADER_AREA,
    IN_FOOTER_AREA
};

struct VisibleContentInfo {
    int32_t area = -1;
    int32_t indexInGroup = -1;
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
        auto prevHeader = header_.Upgrade();
        if (!prevHeader) {
            host->AddChild(header);
        } else {
            host->ReplaceChild(prevHeader, header);
            host->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
        }
        header_ = header;
    }

    void AddFooter(const RefPtr<NG::UINode>& footer)
    {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto prevFooter = footer_.Upgrade();
        if (!prevFooter) {
            host->AddChild(footer);
        } else {
            host->ReplaceChild(prevFooter, footer);
            host->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
        }
        footer_ = footer;
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

    int32_t GetDisplayStartIndexInGroup() const
    {
        return itemDisplayStartIndex_;
    }

    int32_t GetItemStartIndex() const
    {
        return itemStartIndex_;
    }

    int32_t GetEndIndexInGroup() const
    {
        return (itemTotalCount_ - 1);
    }

    int32_t GetTotalItemCount() const
    {
        return itemTotalCount_;
    }

    bool IsDisplayStart() const
    {
        return itemDisplayStartIndex_ == 0;
    }

    int32_t IsDisplayEnd() const
    {
        return itemTotalCount_ == 0 || itemDisplayEndIndex_ == (itemTotalCount_ - 1);
    }

    int32_t GetLanesInGroup() const
    {
        return lanes_;
    }

    V2::ListItemGroupStyle GetListItemGroupStyle()
    {
        return listItemGroupStyle_;
    }

    float GetHeaderMainSize() const
    {
        return headerMainSize_;
    }

    float GetFooterMainSize() const
    {
        return footerMainSize_;
    }

    float GetEstimateOffset(float height, const std::pair<float, float>& targetPos) const;
    float GetEstimateHeight(float& averageHeight) const;
    bool HasLayoutedItem() const
    {
        return layouted_ && (layoutedItemInfo_.has_value() || itemTotalCount_ == 0);
    }

    void SetItemPressed(bool isPressed, int32_t id)
    {
        if (isPressed) {
            pressedItem_.emplace(id);
        } else {
            pressedItem_.erase(id);
        }
    }

    RefPtr<ListChildrenMainSize> GetOrCreateListChildrenMainSize();
    void OnChildrenSizeChanged(std::tuple<int32_t, int32_t, int32_t> change, ListChangeFlag flag);
    bool ListChildrenSizeExist();
    RefPtr<FrameNode> GetListFrameNode() const;
    VisibleContentInfo GetStartListItemIndex();
    VisibleContentInfo GetEndListItemIndex();

private:
    bool IsNeedInitClickEventRecorder() const override
    {
        return true;
    }

    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    void OnAttachToFrameNode() override;
    void SetListItemGroupDefaultAttributes(const RefPtr<FrameNode>& itemGroupNode);
    void CheckListDirectionInCardStyle();
    RefPtr<ShallowBuilder> shallowBuilder_;
    RefPtr<ListPositionMap> posMap_;
    RefPtr<ListChildrenMainSize> childrenSize_;
    V2::ListItemGroupStyle listItemGroupStyle_ = V2::ListItemGroupStyle::NONE;

    int32_t indexInList_ = 0;

    WeakPtr<UINode> header_;
    WeakPtr<UINode> footer_;
    int32_t itemStartIndex_ = 0;
    int32_t itemTotalCount_ = -1;
    int32_t itemDisplayEndIndex_ = -1;
    int32_t itemDisplayStartIndex_ = -1;
    float_t headerMainSize_ = 0.0f;
    float_t footerMainSize_ = 0.0f;

    std::optional<LayoutedItemInfo> layoutedItemInfo_;
    std::set<int32_t> pressedItem_;
    bool layouted_ = false;

    ListItemGroupLayoutAlgorithm::PositionMap itemPosition_;
    float spaceWidth_ = 0.0f;
    Axis axis_ = Axis::VERTICAL;
    int32_t lanes_ = 1;
    float laneGutter_ = 0.0f;
    float startHeaderPos_ = 0.0f;
    float endFooterPos_ = 0.0f;
    ACE_DISALLOW_COPY_AND_MOVE(ListItemGroupPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_ITEM_PATTERN_H
