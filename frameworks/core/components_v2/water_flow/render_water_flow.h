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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_WATER_FLOW_RENDER_WATER_FLOW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_WATER_FLOW_RENDER_WATER_FLOW_H

#include <atomic>
#include <functional>
#include <list>
#include <map>
#include <mutex>
#include <set>
#include <unordered_map>
#include <utility>
#include <vector>

#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/scroll_bar.h"
#include "core/components/positioned/positioned_component.h"
#include "core/components/scroll/scroll_bar_theme.h"
#include "core/components/scroll/scrollable.h"
#include "core/components/stack/stack_element.h"
#include "core/components_v2/water_flow/render_water_flow_item.h"
#include "core/components_v2/water_flow/water_flow_component.h"
#include "core/pipeline/base/render_node.h"

namespace OHOS::Ace::V2 {
class WaterFlowEventInfo : public BaseEventInfo, public EventToJSONStringAdapter {
    DECLARE_RELATIONSHIP_OF_CLASSES(WaterFlowEventInfo, BaseEventInfo, EventToJSONStringAdapter);

public:
    explicit WaterFlowEventInfo(int32_t scrollIndex) : BaseEventInfo("waterflow"), scrollIndex_(scrollIndex) {}

    ~WaterFlowEventInfo() = default;

    std::string ToJSONString() const override;

    int32_t GetScrollIndex() const
    {
        return scrollIndex_;
    }

private:
    int32_t scrollIndex_ = 0;
};

typedef struct {
    int32_t rowSpan = 0;
    int32_t colSpan = 0;
} Span;

class RenderWaterFlow : public RenderNode {
    DECLARE_ACE_TYPE(RenderWaterFlow, RenderNode);

public:
    using BuildChildByIndex = std::function<bool(int32_t)>;
    using GetChildSpanByIndex = std::function<bool(int32_t, bool, int32_t&, int32_t&)>;
    using DeleteChildByIndex = std::function<void(int32_t)>;

    RenderWaterFlow() = default;
    ~RenderWaterFlow() override;

    static RefPtr<RenderNode> Create();

    void Update(const RefPtr<Component>& component) override;
    void CalAndPosItems(double& drawLength, int32_t& main);
    void PerformLayout() override;
    void OnPredictLayout(int64_t deadline) override;

    const std::list<RefPtr<RenderNode>>& GetChildren() const override
    {
        return childrenInRect_;
    }

    void SetBuildChildByIndex(BuildChildByIndex func)
    {
        buildChildByIndex_ = std::move(func);
    }

    void SetDeleteChildByIndex(DeleteChildByIndex func)
    {
        deleteChildByIndex_ = std::move(func);
    }

    void SetGetChildSpanByIndex(GetChildSpanByIndex func)
    {
        getChildSpanByIndex_ = std::move(func);
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
    void ClearLayout(int32_t index = -1);
    void ClearItems(int32_t index = 0);
    void OnDataSourceUpdated(int32_t index);
    bool CheckEndShowItemPlace(int32_t index);

    void SetTotalCount(int32_t totalCount)
    {
        if (totalCount_ == totalCount) {
            return;
        }
        totalCount_ = totalCount;
        totalCountFlag_ = true;
    }

    double GetEstimatedHeight();
    // Used in WaterFlowPositionController
    bool AnimateTo(const Dimension& position, float duration, const RefPtr<Curve>& curve);
    Offset CurrentOffset();
    void ScrollToEdge(ScrollEdgeType edgeType, bool smooth);

    Axis GetAxis() const
    {
        return useScrollable_ == SCROLLABLE::VERTICAL ? Axis::VERTICAL : Axis::HORIZONTAL;
    }

    void OnPaintFinish() override;

    bool IsChildrenTouchEnable() override;

    size_t GetCachedSize() const
    {
        return endShowItemIndex_ - startShowItemIndex_;
    }

    Offset GetLastOffset() const
    {
        return useScrollable_ == SCROLLABLE::VERTICAL ? Offset(0, lastOffset_) : Offset(lastOffset_, 0);
    }

    void HandleAxisEvent(const AxisEvent& event) override;

    bool IsAxisScrollable(AxisDirection direction) override;

    WeakPtr<RenderNode> CheckAxisNode() override;

    void OnChildAdded(const RefPtr<RenderNode>& renderNode) override;
    bool IsUseOnly() override;
    int32_t RequestNextFocus(bool vertical, bool reverse);
    void UpdateFocusInfo(int32_t focusIndex);

protected:
    int32_t GetItemSpan(const RefPtr<RenderNode>& child, bool isRow) const;
    bool GetItemSpanFromCache(int32_t index, int32_t& rowSpan, int32_t& colSpan);
    int32_t GetIndexByFlow(int32_t row, int32_t column) const;
    int32_t GetIndexByNode(const RefPtr<RenderNode>& child) const;
    // Handle direction key move
    int32_t focusMove(KeyDirection direction);
    void UpdateAccessibilityAttr();

    std::vector<double> ParseCrossLength(double size, double gap);
    int32_t GetItemMainIndex(int32_t index) const;
    void SetMainSize(Size& dst, const Size& src);
    double GetSize(const Size& src, bool isMain = true) const;
    void GetNextFlow(int32_t& curMain, int32_t& curCross) const;
    void GetPreviousFlow(int32_t& curMain, int32_t& curCross);
    LayoutParam MakeInnerLayoutParam(int32_t row, int32_t col, int32_t rowSpan, int32_t colSpan) const;
    void CalculateCrossSpan(int32_t mainIndex, int32_t cross, int32_t crossSpan, int32_t& calculateCrossSpan);
    bool CheckFlowPlaced(int32_t index, int32_t row, int32_t col, int32_t& rowSpan, int32_t& colSpan);

    // Sets child position, the mainAxis does not contain the offset.
    void SetChildPosition(const RefPtr<RenderNode>& child, int32_t row, int32_t col, int32_t rowSpan, int32_t colSpan);

    void CreateScrollable();
    void LayoutChild(const RefPtr<RenderNode>& child, int32_t row, int32_t col, int32_t rowSpan, int32_t colSpan,
        bool needPosition = true);
    void OnTouchTestHit(
        const Offset& coordinateOffset, const TouchRestrict& touchRestrict, TouchTestResult& result) override;
    bool UpdateScrollPosition(double offset, int32_t source);
    void RecordLocation();

    void CallGap();
    void InitialFlowProp();
    void CaculateViewPortSceneOne();
    bool CaculateViewPortSceneTwo(bool& NeedContinue);
    void CaculateViewPort();
    double BuildLazyFlowLayout(int32_t index, double sizeNeed);
    bool GetFlowSize();
    void BuildFlow(std::vector<double>& cols);
    double CalculateBlankOfEnd();
    double SupplyItems(bool& vailSupplyItem, int32_t mainIndex, int32_t itemIndex = -1, bool needPosition = true,
        bool needRank = true);
    bool CheckMainFull(int32_t mainIndex);
    int32_t CalItemIndexInRank(int32_t mainIndex);
    bool Rank(int32_t mainIndex, int32_t itemIndex = -1);
    void DealCache(int32_t start, int32_t end);
    void DeleteItems(int32_t index, bool isTail);

    void GetMinAndMaxIndex(int32_t& min, int32_t& max);
    bool GetItemMainCrossIndex(int32_t index, int32_t& mainIndex, int32_t& crossIndex);

    bool NeedUpdate(const RefPtr<Component>& component);

    void CalculateWholeSize(double drawLength);

    void InitScrollBar(const RefPtr<Component>& component);
    void InitScrollBarProxy();

    void DoJump(double position, int32_t source);
    void LoadForward();

    double GetCurrentOffset() const
    {
        return startMainPos_ + currentOffset_ - firstItemOffset_;
    }

    void SetScrollBarCallback();

    void SetItemCalSizeNeeded(const RefPtr<RenderNode>& child, bool need);

    bool GetItemCalSizeNeeded(const RefPtr<RenderNode>& child) const;

    void CheckAndInsertItems(int32_t mainIndex, int32_t itemIndex);

    void OutPutMarix(int32_t rows, bool before);

    bool DeleteItemsInMarix(int32_t rows, int32_t itemIndex);

    enum class SCROLLABLE : uint32_t {
        NO_SCROLL = 0,
        VERTICAL,
        HORIZONTAL,
    };

    SCROLLABLE useScrollable_ = SCROLLABLE::NO_SCROLL;

    std::unordered_map<int32_t, RefPtr<RenderNode>> items_;
    std::set<int32_t> showItem_;
    std::set<int32_t> inCache_;
    std::list<RefPtr<RenderNode>> childrenInRect_;
    // Map structure: [Index - (rowSpan, columnSpan)]
    std::map<int32_t, Span> itemSpanCache_;

    RefPtr<Scrollable> scrollable_;
    bool reachHead_ = false;
    bool reachTail_ = false;
    std::optional<bool> firstLineToBottom_;
    bool needCalculateViewPort_ = false;
    double startMainPos_ = 0.0;
    double endMainPos_ = 0.0;
    double currentOffset_ = 0.0;
    double animateDelta_ = 0.0;
    double lastOffset_ = 0.0;
    double firstItemOffset_ = 0.0;
    int32_t startIndex_ = 0;
    int32_t endIndex_ = -1;

    int32_t startShowItemIndex_ = 0;
    int32_t endShowItemIndex_ = -1;

    int32_t startRankItemIndex_ = 0;
    int32_t currentItemIndex_ = 0;

    double mainSize_ = 0.0;
    double crossSize_ = 0.0;
    int32_t mainCount_ = 0;
    int32_t crossCount_ = 0;
    double crossGap_ = 0.0;
    double mainGap_ = 0.0;
    int32_t totalCount_ = 0;

    // used for scrollbar
    double scrollBarExtent_ = 0.0;
    double mainScrollExtent_ = 0.0;
    int32_t scrollBarOpacity_ = 0;
    double estimateHeight_ = 0.0;
    bool totalCountFlag_ = false;
    Color scrollBarColor_;

    RefPtr<ScrollBarProxy> scrollBarProxy_;
    RefPtr<ScrollBar> scrollBar_;
    RefPtr<Animator> animator_;
    RefPtr<V2::WaterFlowComponent> component_;
    BuildChildByIndex buildChildByIndex_;
    DeleteChildByIndex deleteChildByIndex_;
    GetChildSpanByIndex getChildSpanByIndex_;

    int32_t loadingIndex_ = -1;

    int32_t cacheCount_ = 10;

    // add from RenderWaterFlowBase
    bool isVertical_ = false;
    bool updateFlag_ = false;
    FlexDirection direction_ = FlexDirection::ROW;
    FlexAlign crossAxisAlign_ = FlexAlign::CENTER;

    int32_t focusRow_ = -1;
    int32_t focusCol_ = -1;
    int32_t focusIndex_ = 0;

    double flowWidth_ = -1.0;
    double flowHeight_ = -1.0;
    double mainLength_ = 0.0;
    Dimension userColGap_ = 0.0_px;
    Dimension userRowGap_ = 0.0_px;
    Dimension userMainLength_ = 0.0_px;
    DisplayMode displayMode_ = DisplayMode::OFF;
    bool rightToLeft_ = false;
    // Map structure: [rowIndex - (columnIndex, index)]
    std::map<int32_t, std::map<int32_t, int32_t>> flowMatrix_;
    // Map structure: [Index - (rowIndex, columnIndex)]
    std::map<int32_t, std::map<int32_t, int32_t>> flowMatrixByIndex_;
    // Map structure: [rowIndex - columnIndex - (width, height)]
    Size flowCells_;
};
} // namespace OHOS::Ace::V2
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_WATER_FLOW_RENDER_WATER_FLOW_H