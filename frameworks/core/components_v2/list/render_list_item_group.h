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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_LIST_RENDER_LIST_ITEM_GROUP_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_LIST_RENDER_LIST_ITEM_GROUP_H

#include <stdint.h>
#include "core/components_v2/list/list_item_group_component.h"
#include "base/geometry/dimension.h"
#include "core/components_v2/list/list_component.h"
#include "core/components_v2/list/list_item_component.h"
#include "core/components_v2/list/list_item_generator.h"
#include "core/components_v2/list/render_list_item.h"
#include "core/gestures/long_press_recognizer.h"

namespace OHOS::Ace::V2 {

struct ListItemLayoutParam {
    size_t startCacheCount;
    size_t endCacheCount;
    double startMainPos;
    double endMainPos;
    double listMainSize;
    double referencePos;
    double maxLaneLength;
    bool forwardLayout;
    bool isVertical;
    StickyStyle sticky;
    int32_t lanes;
    ListItemAlign align;
};

class RenderListItemGroup : public RenderListItem {
    DECLARE_ACE_TYPE(V2::RenderListItemGroup, V2::RenderListItem);

public:
    static RefPtr<RenderNode> Create();

    RenderListItemGroup() = default;
    ~RenderListItemGroup() override = default;

    void Update(const RefPtr<Component>& component) override;
    void Paint(RenderContext& context, const Offset& offset) override;
    void PerformLayout() override;
    bool IsForwardLayout() const override
    {
        return forwardLayout_;
    }
    void RegisterItemGenerator(WeakPtr<ListItemGenerator>&& listItemGenerator)
    {
        itemGenerator_ = std::move(listItemGenerator);
    }

    double GetMainSize(const Size& size) const
    {
        return vertical_ ? size.Height() : size.Width();
    }

    double GetMainAxis(const Offset& size) const
    {
        return vertical_ ? size.GetY() : size.GetX();
    }

    double GetCrossSize(const Size& size) const
    {
        return vertical_ ? size.Width() : size.Height();
    }

    double GetSpace() const
    {
        return spaceWidth_;
    }

    Dimension GetListSpace() const
    {
        return listSpace_;
    }

    size_t GetCurrStartCacheCount() const
    {
        return currStartCacheCount_;
    }

    size_t GetCurrEndCacheCount() const
    {
        return currEndCacheCount_;
    }

    bool IsVertical() const
    {
        return vertical_;
    }

    size_t GetStartIndex() const
    {
        return startIndex_;
    }

    double GetStartIndexOffset() const
    {
        return startIndexOffset_;
    }

    double GetReferencePos() const
    {
        return forwardLayout_ ? forwardReferencePos_ : backwardReferencePos_;
    }

    size_t GetLanes() const
    {
        return lanes_;
    }

    template<class T>
    T MakeValue(double mainValue, double crossValue) const
    {
        return vertical_ ? T(crossValue, mainValue) : T(mainValue, crossValue);
    }

    void RemoveAllItems();
    RefPtr<RenderListItem> RequestListItem(size_t index, bool atStart);
    RefPtr<RenderNode> RequestListItemHeader();
    RefPtr<RenderNode> RequestListItemFooter();
    void RecycleListItem(size_t index);
    size_t TotalCount();
    RefPtr<RenderNode> GetRenderNode();
    void SetItemGroupLayoutParam(const ListItemLayoutParam &param);
    void SetChainOffset(double offset);
    void SetRenderNode(const WeakPtr<RenderNode>& renderNode)
    {
        renderNode_ = renderNode;
    }
    void SetNeedLayoutDeep();

protected:
    virtual void PaintDivider(RenderContext& context) {}

    const std::unique_ptr<ItemDivider>& GetItemDivider() const
    {
        return component_->GetItemDivider();
    }

    const std::list<RefPtr<RenderListItem>>& GetItems() const
    {
        return items_;
    }

private:
    LayoutParam MakeInnerLayout();
    double LayoutOrRecycleCurrentItems();
    void RecycleStartCacheItems();
    double LayoutALine(std::list<RefPtr<RenderListItem>>::iterator& it);
    void RequestNewItemsAtEnd(double& curMainPos);
    void RequestNewItemsAtStart();
    void LayoutHeaderFooter(bool reachEnd);
    void SetItemsPostion();
    double CalculateCrossOffset(double crossSize, double childCrossSize);

    WeakPtr<ListItemGenerator> itemGenerator_;
    RefPtr<ListItemGroupComponent> component_;
    std::list<RefPtr<RenderListItem>> items_;
    RefPtr<RenderNode> header_;
    RefPtr<RenderNode> footer_;
    double spaceWidth_ = 0.0;

    // param for frontend
    Dimension listSpace_;
    bool stickyHeader_ = false;
    bool stickyFooter_ = false;
    WeakPtr<RenderNode> renderNode_;

    // layout param
    bool forwardLayout_ = true;
    double forwardReferencePos_ = 0.0;
    double backwardReferencePos_ = 0.0;
    double startMainPos_ = 0.0;
    double endMainPos_ = 0.0;
    double listMainSize_ = 0.0;
    double maxLaneLength_ = 0.0;
    size_t startCacheCount_ = 0;
    size_t endCacheCount_ = 0;
    size_t lanes_ = 1;
    bool vertical_ = true;
    ListItemAlign align_ = V2::ListItemAlign::START;

    // layout status
    bool isInitialized_ = false;
    size_t startIndex_ = 0;
    double startIndexOffset_ = 0.0;
    double endIndexOffset_ = 0.0;
    size_t currStartCacheCount_ = 0;
    size_t currEndCacheCount_ = 0;

    ACE_DISALLOW_COPY_AND_MOVE(RenderListItemGroup);
};

} // namespace OHOS::Ace::V2

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_LIST_RENDER_LIST_ITEM_GROUP_H
