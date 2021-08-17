/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_LIST_RENDER_LIST_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_LIST_RENDER_LIST_H

#include <functional>
#include <limits>
#include <list>

#include "core/components/scroll/scrollable.h"
#include "core/components_v2/list/list_component.h"
#include "core/components_v2/list/render_list_item.h"
#include "core/pipeline/base/render_node.h"

namespace OHOS::Ace::V2 {

class ListItemGenerator : virtual public Referenced {
public:
    static constexpr size_t INVALID_INDEX = std::numeric_limits<size_t>::max();

    virtual RefPtr<RenderListItem> RequestListItem(size_t index) = 0;
    virtual void RecycleListItem(size_t index, bool forceDelete) = 0;
    virtual size_t TotalCount() = 0;
    virtual size_t FindPreviousStickyListItem(size_t index) = 0;
};

class RenderList : public RenderNode {
    DECLARE_ACE_TYPE(V2::RenderList, RenderNode);

public:
    static RefPtr<RenderNode> Create();

    RenderList() = default;
    ~RenderList() = default;

    void Update(const RefPtr<Component>& component) override;

    void PerformLayout() override;

    void UpdateTouchRect() override;

    template<class T>
    T MakeValue(double mainValue, double crossValue) const
    {
        return vertical_ ? T(crossValue, mainValue) : T(mainValue, crossValue);
    }

    double GetMainSize(const Size& size) const
    {
        return vertical_ ? size.Height() : size.Width();
    }

    double GetCrossSize(const Size& size) const
    {
        return vertical_ ? size.Width() : size.Height();
    }

    double GetMainAxis(const Offset& size) const
    {
        return vertical_ ? size.GetY() : size.GetX();
    }

    double GetCrossAxis(const Offset& size) const
    {
        return vertical_ ? size.GetX() : size.GetY();
    }

    void RegisterItemGenerator(WeakPtr<ListItemGenerator>&& listItemGenerator)
    {
        itemGenerator_ = std::move(listItemGenerator);
    }

    void RemoveAllItems();

    void JumpToIndex(int32_t idx, int32_t source);

protected:
    LayoutParam MakeInnerLayout();
    Size SetItemsPosition(double mainSize, const LayoutParam& layoutParam);
    bool UpdateScrollPosition(double offset, int32_t source);

    void OnTouchTestHit(
        const Offset& coordinateOffset, const TouchRestrict& touchRestrict, TouchTestResult& result) override;

    double ApplyLayoutParam();
    double LayoutOrRecycleCurrentItems(const LayoutParam& layoutParam);
    RefPtr<RenderListItem> RequestAndLayoutNewItem(size_t index, const LayoutParam& layoutParam);

    RefPtr<RenderListItem> RequestListItem(size_t index);
    void RecycleListItem(size_t index, bool forceDelete = false);
    size_t TotalCount();
    size_t FindPreviousStickyListItem(size_t index);

    void OnItemDelete(const RefPtr<RenderListItem>& item);

    void UpdateStickyListItem(const RefPtr<RenderListItem>& newStickyItem, size_t newStickyItemIndex,
        const RefPtr<RenderListItem>& nextStickyItem, const LayoutParam& layoutParam);

    void ApplyPreviousStickyListItem(
        size_t index, bool forceLayout = false, const LayoutParam& layoutParam = LayoutParam());

    RefPtr<ListComponent> component_;

    static constexpr size_t INVALID_CHILD_INDEX = std::numeric_limits<size_t>::max();
    static constexpr size_t INITIAL_CHILD_INDEX = INVALID_CHILD_INDEX - 1;

    size_t startIndex_ = INITIAL_CHILD_INDEX;
    std::list<RefPtr<RenderListItem>> items_;

    double spaceWidth_ = 0.0;
    double startMainPos_ = 0.0;
    double endMainPos_ = 0.0;
    double currentOffset_ = 0.0;

    bool reachStart_ = false;
    bool reachEnd_ = false;
    bool vertical_ = true;
    bool fixedMainSize_ = true;
    bool fixedCrossSize_ = false;

    size_t firstDisplayIndex_ = INITIAL_CHILD_INDEX;
    size_t lastDisplayIndex_ = INITIAL_CHILD_INDEX;

    WeakPtr<ListItemGenerator> itemGenerator_;
    RefPtr<Scrollable> scrollable_;

    size_t currentStickyIndex_ = INITIAL_CHILD_INDEX;
    RefPtr<RenderListItem> currentStickyItem_;

private:
    ACE_DISALLOW_COPY_AND_MOVE(RenderList);
};

} // namespace OHOS::Ace::V2

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_LIST_RENDER_LIST_H
