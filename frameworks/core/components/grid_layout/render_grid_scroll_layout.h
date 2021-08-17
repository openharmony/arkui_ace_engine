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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_GRID_LAYOUT_RENDER_GRID_SCROLL_LAYOUT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_GRID_LAYOUT_RENDER_GRID_SCROLL_LAYOUT_H

#include <list>
#include <map>
#include <set>
#include <unordered_map>

#include "core/components/common/layout/constants.h"
#include "core/components/grid_layout/render_grid_layout.h"
#include "core/components/scroll/scrollable.h"
#include "core/components_v2/foreach/lazy_foreach_component.h"
#include "core/pipeline/base/render_node.h"

namespace OHOS::Ace {

class RenderGridScrollLayout : public RenderGridLayout {
    DECLARE_ACE_TYPE(RenderGridScrollLayout, RenderGridLayout);

public:
    using BuildChildByIndex = std::function<bool(int32_t)>;
    using DeleteChildByIndex = std::function<void(int32_t)>;
    static RefPtr<RenderNode> Create();

    void Update(const RefPtr<Component>& component) override;

    void PerformLayout() override;

    void UpdateTouchRect() override;

    // Adjust focus index when grid_item request focus itself.
    void UpdateFocusInfo(int32_t focusIndex);

    // Support to grid element response focus event.
    int32_t RequestNextFocus(bool vertical, bool reverse);

    const std::list<RefPtr<RenderNode>>& GetChildren() const override
    {
        return childrenInRect_;
    }

    void SetBuildChildByIndex(BuildChildByIndex buildChildByIndex)
    {
        buildChildByIndex_ = buildChildByIndex;
    }

    void SetDeleteChildByIndex(DeleteChildByIndex deleteChildByIndex)
    {
        deleteChildByIndex_ = deleteChildByIndex;
    }

    void AddChildByIndex(int32_t index, const RefPtr<RenderNode>& renderNode);
    void RemoveChildByIndex(int32_t index)
    {
        auto item = items_.find(index);
        if (item != items_.end()) {
            RemoveChild(item->second);
            items_.erase(item);
        }
    }
    void ClearLayout();
    void ClearItems();
    void OnReload();
    void OnItemAdded(int32_t index);
    void OnItemDeleted(int32_t index);
    void OnItemChanged(int32_t index);
    void OnItemMoved(int32_t from, int32_t to);

protected:
    int32_t GetItemMainIndex(const RefPtr<RenderNode>& child, bool isMain) const;
    void SetMainSize(Size& dst, const Size& src);
    double GetSize(const Size& src, bool isMain = true) const;
    void GetNextGird(int32_t& curMain, int32_t& curCross) const;
    LayoutParam MakeInnerLayoutParam(int32_t row, int32_t col, int32_t rowSpan, int32_t colSpan) const;
    bool CheckGridPlaced(int32_t index, int32_t row, int32_t col, int32_t& rowSpan, int32_t& colSpan);

    // Sets child position, the mainAxis does not contain the offset.
    void SetChildPosition(const RefPtr<RenderNode>& child, int32_t row, int32_t col, int32_t rowSpan, int32_t colSpan);

    void CreateScrollable();
    void LayoutChild(const RefPtr<RenderNode>& child, int32_t row, int32_t col, int32_t rowSpan, int32_t colSpan);
    void OnTouchTestHit(
        const Offset& coordinateOffset, const TouchRestrict& touchRestrict, TouchTestResult& result) override;
    bool UpdateScrollPosition(double offset, int32_t source);

    void InitialGridProp();
    void CaculateViewPort();
    void BuildNoLazyGridLayout();
    double BuildLazyGridLayout(int32_t index, double sizeNeed);
    bool GetGridSize();
    void BuildGrid(std::vector<double>& rows, std::vector<double>& cols);
    double CalculateBlankOfEnd();
    double SupplementItems(int32_t index, bool needGridLayout = false);
    void DealCache(int32_t start, int32_t end);
    void DeleteItems(int32_t index, bool isTail);

    void GetMinAndMaxIndex(int32_t& min, int32_t& max);
    int32_t GetItemMainIndex(int32_t index);

    bool NeedUpdate(const RefPtr<Component>& component);

    enum class SCROLLABLE : uint32_t {
        NO_SCROLL = 0,
        VERTICAL,
        HORIZONTAL,
    };

    SCROLLABLE useScrollable_ = SCROLLABLE::NO_SCROLL;

    std::map<int32_t, Size> metaData_;
    std::unordered_map<int32_t, RefPtr<RenderNode>> items_;
    std::set<int32_t> showItem_;
    std::set<int32_t> inCache_;
    std::list<RefPtr<RenderNode>> childrenInRect_;

    RefPtr<Scrollable> scrollable_;
    bool reachHead_ = false;
    bool reachTail_ = false;
    double startMainPos_ = 0.0;
    double endMainPos_ = 0.0;
    double currentOffset_ = 0.0;
    double firstItemOffset_ = 0.0;
    int32_t startIndex_ = 0;
    int32_t endIndex_ = -1;

    double* mainSize_ = &rowSize_;
    double* crossSize_ = &colSize_;
    int32_t* mainCount_ = &rowCount_;
    int32_t* crossCount_ = &colCount_;
    double* crossGap_ = &colGap_;
    double* mainGap_ = &rowGap_;

    BuildChildByIndex buildChildByIndex_;
    DeleteChildByIndex deleteChildByIndex_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_GRID_LAYOUT_RENDER_GRID_SCROLL_LAYOUT_H