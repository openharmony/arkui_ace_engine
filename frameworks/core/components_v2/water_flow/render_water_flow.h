/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#include <map>
#include <set>
#include <unordered_map>
#include <vector>

#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/scroll_bar.h"
#include "core/components/positioned/positioned_component.h"
#include "core/components/scroll/scroll_bar_theme.h"
#include "core/components/scroll/scrollable.h"
#include "core/components_v2/water_flow/render_water_flow_item.h"
#include "core/components_v2/water_flow/water_flow_component.h"
#include "core/components_v2/water_flow/water_flow_item_generator.h"
#include "core/pipeline/base/render_node.h"

namespace OHOS::Ace::V2 {
enum class SCROLLABLE : uint32_t {
    NO_SCROLL = 0,
    VERTICAL,
    HORIZONTAL,
};

enum class WaterFlowEvents : uint32_t {
    NONE = 0,
    REACH_START,
    REACH_END,
};

using FlowStyle = struct {
    double mainPos = 0.0;   // position of main side
    double crossPos = 0.0;  // position of cross side
    double mainSize = 0.0;  // size of main side
    double crossSize = 0.0; // size of corss side
};

using ItemConstraintSize = struct {
    double minCrossSize = 0.0; // min cross Size
    double maxCrossSize = 0.0; // max cross Size
    double minMainSize = 0.0;  // min main Size
    double maxMainSize = 0.0;  // max cross Size
};

class RenderWaterFlow : public RenderNode {
    DECLARE_ACE_TYPE(RenderWaterFlow, RenderNode);

public:
    using BuildChildByIndex = std::function<bool(size_t)>;
    using DeleteChildByIndex = std::function<void(size_t)>;
    using UpdateTotalCount = std::function<size_t()>;

    RenderWaterFlow() = default;
    ~RenderWaterFlow() override;

    static RefPtr<RenderNode> Create();

    void Update(const RefPtr<Component>& component) override;
    void PerformLayout() override;
    void OnPredictLayout(int64_t deadline) override;

    inline void SetBuildChildByIndex(BuildChildByIndex func)
    {
        buildChildByIndex_ = std::move(func);
    }

    inline void SetDeleteChildByIndex(DeleteChildByIndex func)
    {
        deleteChildByIndex_ = std::move(func);
    }

    inline void SetGetTotalCount(UpdateTotalCount func)
    {
        getTotalCount_ = std::move(func);
    }

    void AddChildByIndex(size_t index, const RefPtr<RenderNode>& renderNode);
    inline void RemoveChildByIndex(size_t index)
    {
        auto item = items_.find(index);
        if (item != items_.end()) {
            RemoveChild(item->second);
            items_.erase(item);
        }
    }
    void ClearLayout(size_t index, bool clearAll = false);
    void ClearItems(size_t index = 0);
    void OnDataSourceUpdated(size_t index);

    inline void SetTotalCount(size_t totalCount)
    {
        if (totalCount_ != totalCount) {
            totalCount_ = totalCount;
        }
    }

    double GetEstimatedHeight();
    void ScrollToIndex(int32_t index);

    inline Axis GetAxis() const
    {
        return useScrollable_ == SCROLLABLE::VERTICAL ? Axis::VERTICAL : Axis::HORIZONTAL;
    }

    bool IsChildrenTouchEnable() override;
    inline Offset GetLastOffset() const
    {
        return useScrollable_ == SCROLLABLE::VERTICAL ? Offset(0.0, lastOffset_) : Offset(lastOffset_, 0.0);
    }

    void HandleAxisEvent(const AxisEvent& event) override;
    bool IsAxisScrollable(AxisDirection direction) override;
    WeakPtr<RenderNode> CheckAxisNode() override;
    void OnChildAdded(const RefPtr<RenderNode>& renderNode) override;
    bool IsUseOnly() override;
    void RequestWaterFlowFooter();
    inline void RegisterItemGenerator(WeakPtr<WaterFlowItemGenerator>&& waterFlowItemGenerator)
    {
        itemGenerator_ = std::move(waterFlowItemGenerator);
    }

    const std::string& GetColumnsArgs() const
    {
        return colsArgs_;
    }

    const std::string& GetRowsArgs() const
    {
        return rowsArgs_;
    }

    const Dimension& GetColumnsGap() const
    {
        return userColGap_;
    }

    const Dimension& GetRowsGap() const
    {
        return userRowGap_;
    }

    FlexDirection GetlayoutDirection() const
    {
        return direction_;
    }

    ItemConstraintSize GetItemConstraintSize() const
    {
        return itemConstraintSize_;
    }

protected:
    RefPtr<ScrollBarProxy> scrollBarProxy_;
    RefPtr<ScrollBar> scrollBar_;
    int32_t scrollBarOpacity_ = 0;
    SCROLLABLE useScrollable_ = SCROLLABLE::NO_SCROLL;
    double lastOffset_ = 0.0;

private:
    void HandleScrollEvent();
    LayoutParam MakeInnerLayoutParam(size_t itemIndex);

    // Sets child position, the mainAxis does not contain the offset.
    void SetChildPosition(const RefPtr<RenderNode>& child, size_t itemIndex);
    void CreateScrollable();
    void OnTouchTestHit(
        const Offset& coordinateOffset, const TouchRestrict& touchRestrict, TouchTestResult& result) override;
    bool UpdateScrollPosition(double offset, int32_t source);
    void CallGap();
    void CallItemConstraintSize();
    void InitialFlowProp();
    void GetFlowSize();
    void SupplyItems(size_t startIndex, double targetPos);
    void LayoutItems(std::set<size_t>& items);
    void GetFooterSize(double mainSize, double crossSize);
    void LayoutFooter();
    void SetFooterPosition();
    void UpdateCacheItems();
    std::set<size_t> GetShowItems();
    size_t GetLastSupplyedIndex();
    size_t GetNextSupplyedIndex();
    double GetLastSupplyedMainSize();
    Offset GetLastMainBlankPos();
    size_t GetLastMainBlankCross();
    Offset GetLastMainPos();
    void ClearFlowMatrix(size_t index, bool clearAll = false);
    void ClearItemsByCrossIndex(size_t index, bool clearAll = false);
    void InitMainSideEndPos();
    void UpdateMainSideEndPos();
    double GetCrossEndPos(size_t crossIndex);
    FlowStyle ConstraintItemSize(FlowStyle item, size_t crossIndex);
    static RefPtr<RenderWaterFlowItem> GetFlowItemByChild(const RefPtr<RenderNode>& child);
    double GetMainSize(const RefPtr<RenderNode>& item) const;
    double GetCrossSize(const RefPtr<RenderNode>& item) const;
    bool CheckReachHead();
    bool CheckReachTail();
    void AdjustViewPort();
    double GetTailPos();
    double GetTargetPos();
    double GetCacheTargetPos() const;
    void SetTargetPos(double targetPos);
    void DealCache();
    void DeleteItems(size_t index);
    bool GetItemMainCrossIndex(int32_t index, int32_t& mainIndex, int32_t& crossIndex);
    void InitScrollBar();
    void InitScrollBarProxy();
    void DoJump(double position, int32_t source);
    void SetScrollBarCallback();
    void AnimateToPos(const double& position, int32_t duration, const RefPtr<Curve>& curve);
    void OutputMatrix();
    void RemoveAllChild();
    bool NeedPredictLayout();
    static std::string PreParseArgs(const std::string& args);

    std::unordered_map<size_t, RefPtr<RenderNode>> items_;
    std::set<size_t> cacheItems_;

    RefPtr<Scrollable> scrollable_;
    bool reachHead_ = false;
    bool reachTail_ = false;
    int32_t targetIndex_ = -1; // target item index of supply items (for scrollToIndex)
    double viewportStartPos_ = 0.0;
    bool lastReachHead_ = false;
    bool lastReachTail_ = false;
    double mainSize_ = 0.0;  // size ot main side
    double crossSize_ = 0.0; // size of cross side
    double crossGap_ = 0.0;  // gap of cross side
    double mainGap_ = 0.0;   // gap of main side
    size_t crossCount_ = 0;  // splits count of cross side
    size_t totalCount_ = 0;  // ElementProxyHost::TotalCount()
    size_t totalCountBack_ = 0;

    // used for scrollbar
    double scrollBarExtent_ = 0.0;
    double mainScrollExtent_ = 0.0;
    double estimateHeight_ = 0.0;

    RefPtr<Animator> animator_;
    RefPtr<V2::WaterFlowComponent> component_;
    WeakPtr<WaterFlowItemGenerator> itemGenerator_;
    BuildChildByIndex buildChildByIndex_;
    DeleteChildByIndex deleteChildByIndex_;
    UpdateTotalCount getTotalCount_;

    double cacheSize_ = 0.0;
    bool updateFlag_ = false;
    FlexDirection direction_ = FlexDirection::COLUMN;
    ItemConstraintSize itemConstraintSize_ = { 0.0, 0.0, 0.0, 0.0 };
    double mainMaxConstraintSize_ = 0.0;
    double dVPStartPosBackup_ = -1;
    std::string colsArgs_;
    std::string rowsArgs_;

    Dimension userColGap_ = 0.0_px;
    Dimension userRowGap_ = 0.0_px;
    DisplayMode displayMode_ = DisplayMode::OFF;
    // Map structure: [Index - FlowStyle]
    std::map<size_t, FlowStyle> flowMatrix_;
    // Map structure: [crossIndex,  main side endPos of per splits]
    std::vector<double> mainSideEndPos_;
    // Map structure: [crossIndex, cross side size of per splits]
    std::vector<double> crossSideSize_;
    // Map structure: [crossIndex, item index]
    std::vector<std::vector<size_t>> itemsByCrossIndex_;

    std::map<WaterFlowEvents, bool> waterflowEventFlags_;
    RefPtr<RenderNode> footer_;
    Size footerMaxSize_;

    ACE_DISALLOW_COPY_AND_MOVE(RenderWaterFlow);
};
} // namespace OHOS::Ace::V2
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_WATER_FLOW_RENDER_WATER_FLOW_H
