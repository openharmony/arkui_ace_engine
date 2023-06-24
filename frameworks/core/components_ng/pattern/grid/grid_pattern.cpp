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

#include "core/components_ng/pattern/grid/grid_pattern.h"

#include "base/geometry/axis.h"
#include "base/utils/utils.h"
#include "core/components_ng/pattern/grid/grid_adaptive/grid_adaptive_layout_algorithm.h"
#include "core/components_ng/pattern/grid/grid_item_pattern.h"
#include "core/components_ng/pattern/grid/grid_layout/grid_layout_algorithm.h"
#include "core/components_ng/pattern/grid/grid_scroll/grid_scroll_layout_algorithm.h"
#include "core/components_ng/pattern/grid/grid_utils.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/property/property.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

namespace {
constexpr Color SELECT_FILL_COLOR = Color(0x1A000000);
constexpr Color SELECT_STROKE_COLOR = Color(0x33FFFFFF);
const Color ITEM_FILL_COLOR = Color::TRANSPARENT;
constexpr float SCROLL_MAX_TIME = 300.0f; // Scroll Animate max time 0.3 second
} // namespace

RefPtr<LayoutAlgorithm> GridPattern::CreateLayoutAlgorithm()
{
    auto gridLayoutProperty = GetLayoutProperty<GridLayoutProperty>();
    CHECK_NULL_RETURN(gridLayoutProperty, nullptr);
    std::vector<std::string> cols;
    StringUtils::StringSplitter(gridLayoutProperty->GetColumnsTemplate().value_or(""), ' ', cols);
    std::vector<std::string> rows;
    StringUtils::StringSplitter(gridLayoutProperty->GetRowsTemplate().value_or(""), ' ', rows);
    auto crossCount = cols.empty() ? Infinity<int32_t>() : static_cast<int32_t>(cols.size());
    auto mainCount = rows.empty() ? Infinity<int32_t>() : static_cast<int32_t>(rows.size());
    if (!gridLayoutProperty->IsVertical()) {
        std::swap(crossCount, mainCount);
    }
    gridLayoutInfo_.crossCount_ = crossCount;

    // When rowsTemplate and columnsTemplate is both setting, use static layout algorithm.
    if (!rows.empty() && !cols.empty()) {
        return MakeRefPtr<GridLayoutAlgorithm>(gridLayoutInfo_, crossCount, mainCount);
    }

    // When rowsTemplate and columnsTemplate is both not setting, use adaptive layout algorithm.
    if (rows.empty() && cols.empty()) {
        return MakeRefPtr<GridAdaptiveLayoutAlgorithm>(gridLayoutInfo_);
    }

    // If only set one of rowTemplate and columnsTemplate, use scrollable layout algorithm.
    auto result = MakeRefPtr<GridScrollLayoutAlgorithm>(gridLayoutInfo_, crossCount, mainCount);

    auto effect = gridLayoutProperty->GetEdgeEffect().value_or(EdgeEffect::NONE);
    bool canOverScroll = (effect == EdgeEffect::SPRING) && scrollState_ != SCROLL_FROM_AXIS &&
                         scrollState_ != SCROLL_FROM_BAR && scrollable_;
    result->SetCanOverScroll(canOverScroll);

    return result;
}

RefPtr<NodePaintMethod> GridPattern::CreateNodePaintMethod()
{
    auto paint = MakeRefPtr<GridPaintMethod>(GetScrollBar());
    CHECK_NULL_RETURN(paint, nullptr);
    auto scrollEffect = GetScrollEdgeEffect();
    if (scrollEffect && scrollEffect->IsFadeEffect()) {
        paint->SetEdgeEffect(scrollEffect);
    }
    return paint;
}

void GridPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToBounds(true);
    host->GetRenderContext()->UpdateClipEdge(true);
}

void GridPattern::OnModifyDone()
{
    auto gridLayoutProperty = GetLayoutProperty<GridLayoutProperty>();
    CHECK_NULL_VOID(gridLayoutProperty);

    if (multiSelectable_ && !isMouseEventInit_) {
        InitMouseEvent();
    }

    if (!multiSelectable_ && isMouseEventInit_) {
        UninitMouseEvent();
    }

    gridLayoutInfo_.axis_ = gridLayoutProperty->IsVertical() ? Axis::VERTICAL : Axis::HORIZONTAL;
    isConfigScrollable_ = gridLayoutProperty->IsConfiguredScrollable();
    if (!isConfigScrollable_) {
        LOGD("use fixed grid template");
        return;
    }
    SetAxis(gridLayoutInfo_.axis_);
    AddScrollEvent();

    auto edgeEffect = gridLayoutProperty->GetEdgeEffect().value_or(EdgeEffect::NONE);
    SetEdgeEffect(edgeEffect);

    auto paintProperty = GetPaintProperty<ScrollablePaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    if (paintProperty->GetScrollBarProperty()) {
        SetScrollBar(paintProperty->GetScrollBarProperty());
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetFocusHub();
    if (focusHub) {
        InitOnKeyEvent(focusHub);
    }
    SetAccessibilityAction();
}

void GridPattern::UninitMouseEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto mouseEventHub = host->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(mouseEventHub);
    mouseEventHub->SetMouseEvent(nullptr);
    ClearMultiSelect();
    isMouseEventInit_ = false;
}

void GridPattern::InitMouseEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto mouseEventHub = host->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(mouseEventHub);
    mouseEventHub->SetMouseEvent([weak = WeakClaim(this)](MouseInfo& info) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleMouseEventWithoutKeyboard(info);
        }
    });
    isMouseEventInit_ = true;
}

void GridPattern::HandleMouseEventWithoutKeyboard(const MouseInfo& info)
{
    if (info.GetButton() != MouseButton::LEFT_BUTTON) {
        return;
    }

    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto manager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(manager);
    if (manager->IsDragged()) {
        return;
    }

    auto mouseOffsetX = static_cast<float>(info.GetLocalLocation().GetX());
    auto mouseOffsetY = static_cast<float>(info.GetLocalLocation().GetY());
    if (info.GetAction() == MouseAction::PRESS) {
        ClearMultiSelect();
        mouseStartOffset_ = OffsetF(mouseOffsetX, mouseOffsetY);
        mouseEndOffset_ = OffsetF(mouseOffsetX, mouseOffsetY);
        mousePressOffset_ = OffsetF(mouseOffsetX, mouseOffsetY);
        mousePressed_ = true;
        // do not select when click
    } else if (info.GetAction() == MouseAction::MOVE) {
        if (!mousePressed_) {
            return;
        }
        const static double FRAME_SELECTION_DISTANCE =
            pipeline->NormalizeToPx(Dimension(DEFAULT_PAN_DISTANCE, DimensionUnit::VP));
        auto delta = OffsetF(mouseOffsetX, mouseOffsetY) - mousePressOffset_;
        if (Offset(delta.GetX(), delta.GetY()).GetDistance() > FRAME_SELECTION_DISTANCE) {
            mouseEndOffset_ = OffsetF(mouseOffsetX, mouseOffsetY);
            auto selectedZone = ComputeSelectedZone(mouseStartOffset_, mouseEndOffset_);
            MultiSelectWithoutKeyboard(selectedZone);
        }
    } else if (info.GetAction() == MouseAction::RELEASE) {
        mouseStartOffset_.Reset();
        mouseEndOffset_.Reset();
        mousePressed_ = false;
        ClearSelectedZone();
    }
}

void GridPattern::MultiSelectWithoutKeyboard(const RectF& selectedZone)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    std::list<RefPtr<FrameNode>> children;
    host->GenerateOneDepthVisibleFrame(children);
    for (const auto& itemFrameNode : children) {
        auto itemEvent = itemFrameNode->GetEventHub<EventHub>();
        CHECK_NULL_VOID(itemEvent);
        if (!itemEvent->IsEnabled()) {
            continue;
        }

        auto itemPattern = itemFrameNode->GetPattern<GridItemPattern>();
        CHECK_NULL_VOID(itemPattern);
        if (!itemPattern->Selectable()) {
            continue;
        }
        auto itemGeometry = itemFrameNode->GetGeometryNode();
        CHECK_NULL_VOID(itemGeometry);
        auto context = itemFrameNode->GetRenderContext();
        CHECK_NULL_VOID(context);

        auto itemRect = itemGeometry->GetFrameRect();
        if (!selectedZone.IsIntersectWith(itemRect)) {
            itemPattern->MarkIsSelected(false);
            context->OnMouseSelectUpdate(false, ITEM_FILL_COLOR, ITEM_FILL_COLOR);
        } else {
            itemPattern->MarkIsSelected(true);
            context->OnMouseSelectUpdate(true, ITEM_FILL_COLOR, ITEM_FILL_COLOR);
        }
    }

    auto hostContext = host->GetRenderContext();
    CHECK_NULL_VOID(hostContext);
    hostContext->UpdateMouseSelectWithRect(selectedZone, SELECT_FILL_COLOR, SELECT_STROKE_COLOR);
}

void GridPattern::ClearMultiSelect()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    std::list<RefPtr<FrameNode>> children;
    host->GenerateOneDepthAllFrame(children);
    for (const auto& item : children) {
        if (!AceType::InstanceOf<FrameNode>(item)) {
            continue;
        }

        auto itemFrameNode = AceType::DynamicCast<FrameNode>(item);
        auto itemPattern = itemFrameNode->GetPattern<GridItemPattern>();
        CHECK_NULL_VOID(itemPattern);
        itemPattern->MarkIsSelected(false);
        auto renderContext = itemFrameNode->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        renderContext->OnMouseSelectUpdate(false, ITEM_FILL_COLOR, ITEM_FILL_COLOR);
    }

    ClearSelectedZone();
}

void GridPattern::ClearSelectedZone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hostContext = host->GetRenderContext();
    CHECK_NULL_VOID(hostContext);
    hostContext->UpdateMouseSelectWithRect(RectF(), SELECT_FILL_COLOR, SELECT_STROKE_COLOR);
}

RectF GridPattern::ComputeSelectedZone(const OffsetF& startOffset, const OffsetF& endOffset)
{
    RectF selectedZone;
    if (startOffset.GetX() <= endOffset.GetX()) {
        if (startOffset.GetY() <= endOffset.GetY()) {
            // bottom right
            selectedZone = RectF(startOffset.GetX(), startOffset.GetY(), endOffset.GetX() - startOffset.GetX(),
                endOffset.GetY() - startOffset.GetY());
        } else {
            // top right
            selectedZone = RectF(startOffset.GetX(), endOffset.GetY(), endOffset.GetX() - startOffset.GetX(),
                startOffset.GetY() - endOffset.GetY());
        }
    } else {
        if (startOffset.GetY() <= endOffset.GetY()) {
            // bottom left
            selectedZone = RectF(endOffset.GetX(), startOffset.GetY(), startOffset.GetX() - endOffset.GetX(),
                endOffset.GetY() - startOffset.GetY());
        } else {
            // top left
            selectedZone = RectF(endOffset.GetX(), endOffset.GetY(), startOffset.GetX() - endOffset.GetX(),
                startOffset.GetY() - endOffset.GetY());
        }
    }

    return selectedZone;
}

void GridPattern::OnMouseSelectAll()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);

    auto rect = geometryNode->GetFrameRect();
    rect.SetOffset(OffsetF());

    MultiSelectWithoutKeyboard(rect);
}

float GridPattern::GetMainContentSize() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, 0.0);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, 0.0);
    return geometryNode->GetPaddingSize().MainSize(gridLayoutInfo_.axis_);
}

bool GridPattern::OnScrollCallback(float offset, int32_t source)
{
    if (animator_) {
        animator_->Stop();
    }
    return ScrollablePattern::OnScrollCallback(offset, source);
}

SizeF GridPattern::GetContentSize() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, SizeF());
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, SizeF());
    return geometryNode->GetPaddingSize();
}

void GridPattern::CheckRestartSpring()
{
    if (!ScrollableIdle() || !IsOutOfBoundary()) {
        return;
    }
    auto edgeEffect = GetScrollEdgeEffect();
    if (!edgeEffect || !edgeEffect->IsSpringEffect()) {
        return;
    }
    if (animator_ && animator_->IsRunning()) {
        return;
    }
    edgeEffect->ProcessScrollOver(0);
}

float GridPattern::GetMainGap()
{
    float mainGap = 0.0;
    auto host = GetHost();
    CHECK_NULL_RETURN(host, 0.0);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, 0.0);
    auto viewScopeSize = geometryNode->GetPaddingSize();
    auto layoutProperty = host->GetLayoutProperty<GridLayoutProperty>();
    mainGap = GridUtils::GetMainGap(layoutProperty, viewScopeSize, gridLayoutInfo_.axis_);
    return mainGap;
}

bool GridPattern::UpdateCurrentOffset(float offset, int32_t source)
{
    if (!isConfigScrollable_ || !scrollable_) {
        return true;
    }
    // check edgeEffect is not springEffect
    if (!HandleEdgeEffect(offset, source, GetContentSize())) {
        return false;
    }
    SetScrollState(source);

    auto itemsHeight = gridLayoutInfo_.GetTotalHeightOfItemsInView(GetMainGap());
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    // When finger moves down, offset is positive.
    // When finger moves up, offset is negative.
    if (gridLayoutInfo_.offsetEnd_) {
        if (source == SCROLL_FROM_UPDATE) {
            auto overScroll = gridLayoutInfo_.currentOffset_ - (GetMainContentSize() - itemsHeight);
            auto friction = CalculateFriction(std::abs(overScroll) / GetMainContentSize());
            gridLayoutInfo_.prevOffset_ = gridLayoutInfo_.currentOffset_;
            gridLayoutInfo_.currentOffset_ = gridLayoutInfo_.currentOffset_ + offset * friction;
        } else {
            gridLayoutInfo_.prevOffset_ = gridLayoutInfo_.currentOffset_;
            gridLayoutInfo_.currentOffset_ += offset;
        }
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);

        if (GreatOrEqual(gridLayoutInfo_.currentOffset_, GetMainContentSize() - itemsHeight)) {
            gridLayoutInfo_.offsetEnd_ = false;
            gridLayoutInfo_.reachEnd_ = false;
        }
        return true;
    }
    if (gridLayoutInfo_.reachStart_) {
        if (source == SCROLL_FROM_UPDATE) {
            auto friction = CalculateFriction(std::abs(gridLayoutInfo_.currentOffset_) / GetMainContentSize());
            gridLayoutInfo_.prevOffset_ = gridLayoutInfo_.currentOffset_;
            gridLayoutInfo_.currentOffset_ = gridLayoutInfo_.currentOffset_ + offset * friction;
        } else {
            gridLayoutInfo_.prevOffset_ = gridLayoutInfo_.currentOffset_;
            gridLayoutInfo_.currentOffset_ += offset;
        }
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);

        if (LessOrEqual(gridLayoutInfo_.currentOffset_, 0.0)) {
            gridLayoutInfo_.reachStart_ = false;
        }
        return true;
    }
    gridLayoutInfo_.prevOffset_ = gridLayoutInfo_.currentOffset_;
    gridLayoutInfo_.currentOffset_ += offset;
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    return true;
}

bool GridPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure && config.skipLayout) {
        return false;
    }
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto gridLayoutAlgorithm = DynamicCast<GridLayoutBaseAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(gridLayoutAlgorithm, false);
    const auto& gridLayoutInfo = gridLayoutAlgorithm->GetGridLayoutInfo();
    auto eventhub = GetEventHub<GridEventHub>();
    CHECK_NULL_RETURN(eventhub, false);
    scrollbarInfo_ = eventhub->FireOnScrollBarUpdate(gridLayoutInfo.startIndex_, gridLayoutInfo.currentOffset_);
    if (gridLayoutInfo_.startMainLineIndex_ != gridLayoutInfo.startMainLineIndex_) {
        eventhub->FireOnScrollToIndex(gridLayoutInfo.startIndex_);
        FlushFocusOnScroll(gridLayoutInfo);
    }
    gridLayoutInfo_ = gridLayoutInfo;
    gridLayoutInfo_.childrenCount_ = dirty->GetTotalChildCount();

    SetScrollState(SCROLL_FROM_NONE);
    UpdateScrollBarOffset();
    CheckRestartSpring();
    CheckScrollable();
    FlushCurrentFocus();
    return false;
}

void GridPattern::CheckScrollable()
{
    if (((gridLayoutInfo_.endIndex_ - gridLayoutInfo_.startIndex_ + 1) < gridLayoutInfo_.childrenCount_) ||
        (gridLayoutInfo_.GetTotalHeightOfItemsInView(GetMainGap()) > GetMainContentSize())) {
        scrollable_ = true;
    } else {
        scrollable_ = false;
    }

    SetScrollEnable(scrollable_);
}

void GridPattern::FlushCurrentFocus()
{
    auto gridFrame = GetHost();
    CHECK_NULL_VOID(gridFrame);
    auto gridFocus = gridFrame->GetFocusHub();
    CHECK_NULL_VOID(gridFocus);
    if (!gridFocus->IsCurrentFocus()) {
        return;
    }
    auto childFocusList = gridFocus->GetChildren();
    for (const auto& childFocus : childFocusList) {
        if (childFocus->IsCurrentFocus()) {
            auto curFrame = childFocus->GetFrameNode();
            CHECK_NULL_VOID(curFrame);
            auto curPattern = curFrame->GetPattern();
            CHECK_NULL_VOID(curPattern);
            auto curItemPattern = AceType::DynamicCast<GridItemPattern>(curPattern);
            CHECK_NULL_VOID(curItemPattern);

            lastFocusItemMainIndex_ = curItemPattern->GetMainIndex();
            lastFocusItemCrossIndex_ = curItemPattern->GetCrossIndex();
            return;
        }
    }
    if (gridLayoutInfo_.gridMatrix_.find(lastFocusItemMainIndex_) == gridLayoutInfo_.gridMatrix_.end()) {
        LOGE("Can not find last focus item main index: %{public}d", lastFocusItemMainIndex_);
        return;
    }
    auto curCrossNum = static_cast<int32_t>(gridLayoutInfo_.gridMatrix_.at(lastFocusItemMainIndex_).size());
    auto weakChild = SearchFocusableChildInCross(lastFocusItemMainIndex_, lastFocusItemCrossIndex_, curCrossNum);
    auto child = weakChild.Upgrade();
    if (child) {
        child->RequestFocusImmediately();
    }
}

void GridPattern::FlushFocusOnScroll(const GridLayoutInfo& gridLayoutInfo)
{
    auto gridFrame = GetHost();
    CHECK_NULL_VOID(gridFrame);
    auto gridFocus = gridFrame->GetFocusHub();
    CHECK_NULL_VOID(gridFocus);
    if (!gridFocus->IsCurrentFocus()) {
        return;
    }
    auto childFocusList = gridFocus->GetChildren();
    if (std::any_of(childFocusList.begin(), childFocusList.end(),
            [](const RefPtr<FocusHub>& childFocus) { return childFocus->IsCurrentFocus(); })) {
        return;
    }
    int32_t curMainIndex = gridLayoutInfo.startMainLineIndex_;
    if (gridLayoutInfo.gridMatrix_.find(curMainIndex) == gridLayoutInfo.gridMatrix_.end()) {
        LOGE("Can not find main index: %{public}d", curMainIndex);
        return;
    }
    auto curCrossNum = static_cast<int32_t>(gridLayoutInfo.gridMatrix_.at(curMainIndex).size());
    auto weakChild = SearchFocusableChildInCross(curMainIndex, 0, curCrossNum);
    auto child = weakChild.Upgrade();
    if (child) {
        child->RequestFocusImmediately();
    }
}

std::pair<bool, bool> GridPattern::IsFirstOrLastFocusableChild(int32_t curMainIndex, int32_t curCrossIndex)
{
    auto crossIndexSet = GetFocusableChildCrossIndexesAt(curMainIndex);
    auto findLesser = std::find_if(crossIndexSet.begin(), crossIndexSet.end(),
        [curCrossIndex](int32_t crossIndex) { return curCrossIndex > crossIndex; });
    auto findGreater = std::find_if(crossIndexSet.begin(), crossIndexSet.end(),
        [curCrossIndex](int32_t crossIndex) { return curCrossIndex < crossIndex; });
    return { findLesser == crossIndexSet.end(), findGreater == crossIndexSet.end() };
}

std::pair<FocusStep, FocusStep> GridPattern::GetFocusSteps(int32_t curMainIndex, int32_t curCrossIndex, FocusStep step)
{
    auto firstStep = FocusStep::NONE;
    auto secondStep = FocusStep::NONE;
    auto isFirstOrLastFocusable = IsFirstOrLastFocusableChild(curMainIndex, curCrossIndex);
    auto isFirstFocusable = isFirstOrLastFocusable.first;
    auto isLastFocusable = isFirstOrLastFocusable.second;
    if (gridLayoutInfo_.axis_ == Axis::VERTICAL) {
        if (isFirstFocusable && step == FocusStep::LEFT) {
            firstStep = FocusStep::UP;
            secondStep = FocusStep::RIGHT_END;
        } else if (isLastFocusable && step == FocusStep::RIGHT) {
            firstStep = FocusStep::DOWN;
            secondStep = FocusStep::LEFT_END;
        }
    } else if (gridLayoutInfo_.axis_ == Axis::HORIZONTAL) {
        if (isFirstFocusable && step == FocusStep::UP) {
            firstStep = FocusStep::LEFT;
            secondStep = FocusStep::DOWN_END;
        } else if (isLastFocusable && step == FocusStep::DOWN) {
            firstStep = FocusStep::RIGHT;
            secondStep = FocusStep::UP_END;
        }
    }
    LOGI("Get focus steps. First step is %{public}d. Second step is %{public}d", firstStep, secondStep);
    return { firstStep, secondStep };
}

WeakPtr<FocusHub> GridPattern::GetNextFocusNode(FocusStep step, const WeakPtr<FocusHub>& currentFocusNode)
{
    auto curFocus = currentFocusNode.Upgrade();
    CHECK_NULL_RETURN(curFocus, nullptr);
    auto curFrame = curFocus->GetFrameNode();
    CHECK_NULL_RETURN(curFrame, nullptr);
    auto curPattern = curFrame->GetPattern();
    CHECK_NULL_RETURN(curPattern, nullptr);
    auto curItemPattern = AceType::DynamicCast<GridItemPattern>(curPattern);
    CHECK_NULL_RETURN(curItemPattern, nullptr);
    auto curItemProperty = curItemPattern->GetLayoutProperty<GridItemLayoutProperty>();
    CHECK_NULL_RETURN(curItemProperty, nullptr);

    auto curMainIndex = curItemPattern->GetMainIndex();
    auto curCrossIndex = curItemPattern->GetCrossIndex();
    auto curMainSpan = curItemProperty->GetMainSpan(gridLayoutInfo_.axis_);
    auto curCrossSpan = curItemProperty->GetCrossSpan(gridLayoutInfo_.axis_);
    if (curMainIndex < 0 || curCrossIndex < 0) {
        LOGE("can't find focused child.");
        return nullptr;
    }
    if (gridLayoutInfo_.gridMatrix_.find(curMainIndex) == gridLayoutInfo_.gridMatrix_.end()) {
        LOGE("Can not find current main index: %{public}d", curMainIndex);
        return nullptr;
    }
    LOGI("GetNextFocusNode: Current focused item is (%{public}d,%{public}d)-[%{public}d,%{public}d]. Focus step is "
         "%{public}d",
        curMainIndex, curCrossIndex, curMainSpan, curCrossSpan, step);
    auto focusSteps = GetFocusSteps(curMainIndex, curCrossIndex, step);
    if (focusSteps.first != FocusStep::NONE && focusSteps.second != FocusStep::NONE) {
        auto firstStepRes = GetNextFocusNode(focusSteps.first, currentFocusNode);
        if (!firstStepRes.Upgrade()) {
            return nullptr;
        }
        auto secondStepRes = GetNextFocusNode(focusSteps.second, firstStepRes);
        if (!secondStepRes.Upgrade()) {
            return firstStepRes;
        }
        return secondStepRes;
    }
    auto indexes = GetNextIndexByStep(curMainIndex, curCrossIndex, curMainSpan, curCrossSpan, step);
    auto nextMainIndex = indexes.first;
    auto nextCrossIndex = indexes.second;
    while (nextMainIndex >= 0 && nextCrossIndex >= 0) {
        if (gridLayoutInfo_.gridMatrix_.find(nextMainIndex) == gridLayoutInfo_.gridMatrix_.end()) {
            LOGE("Can not find next main index: %{public}d", nextMainIndex);
            return nullptr;
        }
        auto nextMaxCrossCount = static_cast<int32_t>((gridLayoutInfo_.gridMatrix_[nextMainIndex]).size());
        auto weakChild =
            SearchFocusableChildInCross(nextMainIndex, nextCrossIndex, nextMaxCrossCount, curMainIndex, curCrossIndex);
        auto child = weakChild.Upgrade();
        if (child && child->IsFocusable()) {
            ScrollToFocusNode(weakChild);
            return weakChild;
        }
        auto indexes = GetNextIndexByStep(nextMainIndex, nextCrossIndex, 1, 1, step);
        nextMainIndex = indexes.first;
        nextCrossIndex = indexes.second;
    }
    return nullptr;
}

std::pair<int32_t, int32_t> GridPattern::GetNextIndexByStep(
    int32_t curMainIndex, int32_t curCrossIndex, int32_t curMainSpan, int32_t curCrossSpan, FocusStep step)
{
    LOGI("Current item: (%{public}d,%{public}d)-[%{public}d,%{public}d]. Grid axis: %{public}d, step: %{public}d",
        curMainIndex, curCrossIndex, curMainSpan, curCrossSpan, gridLayoutInfo_.axis_, step);
    auto curMainStart = gridLayoutInfo_.startMainLineIndex_;
    auto curMainEnd = gridLayoutInfo_.endMainLineIndex_;
    auto curChildStartIndex = gridLayoutInfo_.startIndex_;
    auto curChildEndIndex = gridLayoutInfo_.endIndex_;
    auto childrenCount = gridLayoutInfo_.childrenCount_;
    if (gridLayoutInfo_.gridMatrix_.find(curMainIndex) == gridLayoutInfo_.gridMatrix_.end()) {
        LOGE("Can not find current main index: %{public}d", curMainIndex);
        return { -1, -1 };
    }
    auto curMaxCrossCount = static_cast<int32_t>((gridLayoutInfo_.gridMatrix_[curMainIndex]).size());
    LOGD("Current main index start-end: %{public}d-%{public}d, Current cross count: %{public}d, Current child "
         "index start-end: %{public}d-%{public}d, Total children count: %{public}d",
        curMainStart, curMainEnd, curMaxCrossCount, curChildStartIndex, curChildEndIndex, childrenCount);

    auto nextMainIndex = curMainIndex;
    auto nextCrossIndex = curCrossIndex;
    if ((step == FocusStep::UP_END && gridLayoutInfo_.axis_ == Axis::HORIZONTAL) ||
        (step == FocusStep::LEFT_END && gridLayoutInfo_.axis_ == Axis::VERTICAL)) {
        nextMainIndex = curMainIndex;
        nextCrossIndex = 0;
    } else if ((step == FocusStep::DOWN_END && gridLayoutInfo_.axis_ == Axis::HORIZONTAL) ||
               (step == FocusStep::RIGHT_END && gridLayoutInfo_.axis_ == Axis::VERTICAL)) {
        nextMainIndex = curMainIndex;
        nextCrossIndex = curMaxCrossCount - 1;
    } else if ((step == FocusStep::UP && gridLayoutInfo_.axis_ == Axis::HORIZONTAL) ||
               (step == FocusStep::LEFT && gridLayoutInfo_.axis_ == Axis::VERTICAL)) {
        nextMainIndex = curMainIndex;
        nextCrossIndex = curCrossIndex - 1;
    } else if ((step == FocusStep::UP && gridLayoutInfo_.axis_ == Axis::VERTICAL) ||
               (step == FocusStep::LEFT && gridLayoutInfo_.axis_ == Axis::HORIZONTAL)) {
        nextMainIndex = curMainIndex - 1;
        nextCrossIndex = curCrossIndex + static_cast<int32_t>((curCrossSpan - 1) / 2);
    } else if ((step == FocusStep::DOWN && gridLayoutInfo_.axis_ == Axis::HORIZONTAL) ||
               (step == FocusStep::RIGHT && gridLayoutInfo_.axis_ == Axis::VERTICAL)) {
        nextMainIndex = curMainIndex;
        nextCrossIndex = curCrossIndex + curCrossSpan;
    } else if ((step == FocusStep::DOWN && gridLayoutInfo_.axis_ == Axis::VERTICAL) ||
               (step == FocusStep::RIGHT && gridLayoutInfo_.axis_ == Axis::HORIZONTAL)) {
        nextMainIndex = curMainIndex + curMainSpan;
        nextCrossIndex = curCrossIndex + static_cast<int32_t>((curCrossSpan - 1) / 2);
    } else {
        LOGE("Next index return: Invalid step: %{public}d and axis: %{public}d", step, gridLayoutInfo_.axis_);
        return { -1, -1 };
    }
    if (curChildStartIndex == 0 && curMainIndex == 0 && nextMainIndex < curMainIndex) {
        LOGD("Item reach at grid top and next main index less than current main index. Reset next main index.");
        nextMainIndex = curMainIndex;
    }
    if (curChildEndIndex == childrenCount - 1 && curMainIndex == curMainEnd && nextMainIndex > curMainIndex) {
        LOGD("Item reach at grid top and next main index greater than current main index. Reset next main index.");
        nextMainIndex = curMainIndex;
    }
    if (nextMainIndex == curMainIndex && nextCrossIndex == curCrossIndex) {
        LOGI("Next index return: Move stoped. Next index: (%{public}d,%{public}d) is same as current.", nextMainIndex,
            nextCrossIndex);
        return { -1, -1 };
    }
    if (curChildStartIndex != 0 && curMainIndex == curMainStart && nextMainIndex < curMainIndex) {
        // Scroll item up.
        LOGD("Item donot reach top and next main index is less than current. Do UpdateStartIndex(%{public}d)",
            curChildStartIndex - 1);
        UpdateStartIndex(curChildStartIndex - 1);
        auto pipeline = PipelineContext::GetCurrentContext();
        if (pipeline) {
            pipeline->FlushUITasks();
        }
    } else if (curChildEndIndex != childrenCount - 1 && curMainIndex == curMainEnd && nextMainIndex > curMainIndex) {
        // Scroll item down.
        LOGD("Item donot reach bottom and next main index is greater than current. Do UpdateStartIndex(%{public}d)",
            curChildEndIndex + 1);
        UpdateStartIndex(curChildEndIndex + 1);
        auto pipeline = PipelineContext::GetCurrentContext();
        if (pipeline) {
            pipeline->FlushUITasks();
        }
    }
    curMainStart = gridLayoutInfo_.startMainLineIndex_;
    curMainEnd = gridLayoutInfo_.endMainLineIndex_;
    if (nextMainIndex < curMainStart || nextMainIndex > curMainEnd) {
        LOGW("Next index return: Error. Next main index is out of range(%{public}d,%{public}d)", curMainStart,
            curMainEnd);
        return { -1, -1 };
    }
    if (nextCrossIndex < 0) {
        LOGW("Next index return: Error. Next cross index is less than 0.");
        return { -1, -1 };
    }
    if (gridLayoutInfo_.gridMatrix_.find(nextMainIndex) == gridLayoutInfo_.gridMatrix_.end()) {
        LOGE("Can not find next main index: %{public}d", nextMainIndex);
        return { -1, -1 };
    }
    auto nextMaxCrossCount = static_cast<int32_t>((gridLayoutInfo_.gridMatrix_[nextMainIndex]).size());
    if (nextCrossIndex >= nextMaxCrossCount) {
        LOGI("Next index return: { %{public}d,%{public}d }. Next cross index is greater than max cross count",
            nextMainIndex, nextMaxCrossCount - 1);
        return { nextMainIndex, nextMaxCrossCount - 1 };
    }
    LOGI("Next index return: { %{public}d,%{public}d }.", nextMainIndex, nextCrossIndex);
    return { nextMainIndex, nextCrossIndex };
}

WeakPtr<FocusHub> GridPattern::SearchFocusableChildInCross(
    int32_t tarMainIndex, int32_t tarCrossIndex, int32_t maxCrossCount, int32_t curMainIndex, int32_t curCrossIndex)
{
    LOGD("Search child from index: (%{public}d,%{public}d). Current index: (%{public}d,%{public}d)", tarMainIndex,
        tarCrossIndex, curMainIndex, curCrossIndex);
    bool isDirectionLeft = true;
    auto indexLeft = tarCrossIndex;
    auto indexRight = tarCrossIndex;
    if (curMainIndex == tarMainIndex) {
        // Search on the same main index. Do not need search on both left and right side.
        if (tarCrossIndex > curCrossIndex) {
            // Only search on the right side.
            indexLeft = -1;
        } else if (tarCrossIndex < curCrossIndex) {
            // Only search on the left side.
            indexRight = maxCrossCount;
        } else {
            LOGE("Invalid search index: (%{public}d,%{public}d). It's same as current.", tarMainIndex, tarCrossIndex);
            return nullptr;
        }
    }
    while (indexLeft >= 0 || indexRight < maxCrossCount) {
        int32_t curIndex = indexLeft;
        if (indexLeft < 0) {
            curIndex = indexRight++;
        } else if (indexRight >= maxCrossCount) {
            curIndex = indexLeft--;
        } else {
            curIndex = isDirectionLeft ? indexLeft-- : indexRight++;
            isDirectionLeft = !isDirectionLeft;
        }
        auto weakChild = GetChildFocusNodeByIndex(tarMainIndex, curIndex);
        auto child = weakChild.Upgrade();
        if (child && child->IsFocusable()) {
            LOGI("Found child. Index: %{public}d,%{public}d", tarMainIndex, curIndex);
            return weakChild;
        }
    }
    LOGD("Child can not be found.");
    return nullptr;
}

WeakPtr<FocusHub> GridPattern::GetChildFocusNodeByIndex(int32_t tarMainIndex, int32_t tarCrossIndex)
{
    LOGD("Get target item location is (%{public}d,%{public}d)", tarMainIndex, tarCrossIndex);
    auto gridFrame = GetHost();
    CHECK_NULL_RETURN(gridFrame, nullptr);
    auto gridFocus = gridFrame->GetFocusHub();
    CHECK_NULL_RETURN(gridFocus, nullptr);
    auto childFocusList = gridFocus->GetChildren();
    for (const auto& childFocus : childFocusList) {
        auto childFrame = childFocus->GetFrameNode();
        if (!childFrame) {
            continue;
        }
        auto childPattern = childFrame->GetPattern();
        if (!childPattern) {
            continue;
        }
        auto childItemPattern = AceType::DynamicCast<GridItemPattern>(childPattern);
        if (!childItemPattern) {
            continue;
        }
        auto childItemProperty = childItemPattern->GetLayoutProperty<GridItemLayoutProperty>();
        if (!childItemProperty) {
            continue;
        }
        auto curMainIndex = childItemPattern->GetMainIndex();
        auto curCrossIndex = childItemPattern->GetCrossIndex();
        auto curMainSpan = childItemProperty->GetMainSpan(gridLayoutInfo_.axis_);
        auto curCrossSpan = childItemProperty->GetCrossSpan(gridLayoutInfo_.axis_);
        if (curMainIndex <= tarMainIndex && curMainIndex + curMainSpan > tarMainIndex &&
            curCrossIndex <= tarCrossIndex && curCrossIndex + curCrossSpan > tarCrossIndex) {
            return AceType::WeakClaim(AceType::RawPtr(childFocus));
        }
    }
    LOGW("The target item at location(%{public}d,%{public}d) can not found.", tarMainIndex, tarCrossIndex);
    return nullptr;
}

std::unordered_set<int32_t> GridPattern::GetFocusableChildCrossIndexesAt(int32_t tarMainIndex)
{
    std::unordered_set<int32_t> result;
    auto gridFrame = GetHost();
    CHECK_NULL_RETURN(gridFrame, result);
    auto gridFocus = gridFrame->GetFocusHub();
    CHECK_NULL_RETURN(gridFocus, result);
    auto childFocusList = gridFocus->GetChildren();
    for (const auto& childFocus : childFocusList) {
        if (!childFocus->IsFocusable()) {
            continue;
        }
        auto childFrame = childFocus->GetFrameNode();
        if (!childFrame) {
            continue;
        }
        auto childPattern = childFrame->GetPattern();
        if (!childPattern) {
            continue;
        }
        auto childItemPattern = AceType::DynamicCast<GridItemPattern>(childPattern);
        if (!childItemPattern) {
            continue;
        }
        auto curMainIndex = childItemPattern->GetMainIndex();
        auto curCrossIndex = childItemPattern->GetCrossIndex();
        if (curMainIndex == tarMainIndex) {
            result.emplace(curCrossIndex);
        }
    }
    std::string output;
    for (const auto& index : result) {
        output += std::to_string(index);
    }
    LOGD("Focusable child cross index list at main(%{public}d) is { %{public}s }", tarMainIndex, output.c_str());
    return result;
}

void GridPattern::ScrollToFocusNode(const WeakPtr<FocusHub>& focusNode)
{
    auto nextFocus = focusNode.Upgrade();
    CHECK_NULL_VOID(nextFocus);
    auto nextFrame = nextFocus->GetFrameNode();
    CHECK_NULL_VOID(nextFrame);
    auto nextPattern = nextFrame->GetPattern();
    CHECK_NULL_VOID(nextPattern);
    auto nextItemPattern = AceType::DynamicCast<GridItemPattern>(nextPattern);
    CHECK_NULL_VOID(nextItemPattern);
    auto nextMainIndex = nextItemPattern->GetMainIndex();
    auto nextCrossIndex = nextItemPattern->GetCrossIndex();
    if (gridLayoutInfo_.gridMatrix_.find(nextMainIndex) == gridLayoutInfo_.gridMatrix_.end()) {
        LOGE("Can not find next main index: %{public}d", nextMainIndex);
        return;
    }
    auto nextIndex = gridLayoutInfo_.gridMatrix_[nextMainIndex][nextCrossIndex];
    UpdateStartIndex(nextIndex);
}

void GridPattern::StopAnimate()
{
    if (!IsScrollableStopped()) {
        StopScrollable();
    }
    if (animator_ && !animator_->IsStopped()) {
        animator_->Stop();
    }
}

void GridPattern::ScrollBy(float offset)
{
    StopAnimate();
    UpdateCurrentOffset(-offset, SCROLL_FROM_JUMP);
    auto host = GetHost();
    CHECK_NULL_VOID_NOLOG(host);
    host->OnAccessibilityEvent(AccessibilityEventType::SCROLL_END);
}

void GridPattern::ToJsonValue(std::unique_ptr<JsonValue>& json) const
{
    Pattern::ToJsonValue(json);
    json->Put("multiSelectable", multiSelectable_ ? "true" : "false");
    json->Put("supportAnimation", supportAnimation_ ? "true" : "false");
}

void GridPattern::InitOnKeyEvent(const RefPtr<FocusHub>& focusHub)
{
    auto onKeyEvent = [wp = WeakClaim(this)](const KeyEvent& event) -> bool {
        auto pattern = wp.Upgrade();
        if (pattern) {
            return pattern->OnKeyEvent(event);
        }
        return false;
    };
    focusHub->SetOnKeyEventInternal(std::move(onKeyEvent));
}

bool GridPattern::OnKeyEvent(const KeyEvent& event)
{
    if (event.action != KeyAction::DOWN) {
        return false;
    }
    if ((event.code == KeyCode::KEY_PAGE_DOWN) || (event.code == KeyCode::KEY_PAGE_UP)) {
        ScrollPage(event.code == KeyCode::KEY_PAGE_UP);
    }
    return false;
}

bool GridPattern::HandleDirectionKey(KeyCode code)
{
    if (code == KeyCode::KEY_DPAD_UP) {
        // Need to update: current selection
        return true;
    }
    if (code == KeyCode::KEY_DPAD_DOWN) {
        // Need to update: current selection
        return true;
    }
    return false;
}

void GridPattern::SetPositionController(const RefPtr<ScrollController>& controller)
{
    positionController_ = DynamicCast<GridPositionController>(controller);
    if (controller) {
        controller->SetScrollPattern(AceType::WeakClaim<GridPattern>(this));
    }
}

void GridPattern::ScrollPage(bool reverse)
{
    if (!isConfigScrollable_) {
        return;
    }
    if (!reverse) {
        LOGD("PgDn. Scroll offset is %{public}f", -GetMainContentSize());
        UpdateCurrentOffset(-GetMainContentSize(), SCROLL_FROM_JUMP);
    } else {
        LOGD("PgUp. Scroll offset is %{public}f", GetMainContentSize());
        UpdateCurrentOffset(GetMainContentSize(), SCROLL_FROM_JUMP);
    }
    auto host = GetHost();
    CHECK_NULL_VOID_NOLOG(host);
    host->OnAccessibilityEvent(AccessibilityEventType::SCROLL_END);
}

bool GridPattern::UpdateStartIndex(int32_t index)
{
    if (!isConfigScrollable_) {
        return false;
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    gridLayoutInfo_.jumpIndex_ = index;
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    host->OnAccessibilityEvent(AccessibilityEventType::SCROLL_END);
    return true;
}

bool GridPattern::AnimateTo(float position, float duration, const RefPtr<Curve>& curve)
{
    if (!isConfigScrollable_) {
        return false;
    }
    if (!animator_) {
        animator_ = CREATE_ANIMATOR(PipelineBase::GetCurrentContext());
    }
    if (!animator_->IsStopped()) {
        animator_->Stop();
    }
    animatorOffset_ = 0;
    animator_->ClearInterpolators();

    auto animation = AceType::MakeRefPtr<CurveAnimation<float>>(0, position, curve);
    animation->AddListener(
        [offset = gridLayoutInfo_.currentOffset_, weakScroll = AceType::WeakClaim(this)](float value) {
            auto gridPattern = weakScroll.Upgrade();
            if (gridPattern) {
                gridPattern->UpdateCurrentOffset(value, SCROLL_FROM_JUMP);
            }
        });
    animator_->AddInterpolator(animation);
    animator_->SetDuration(std::min(duration, SCROLL_MAX_TIME));
    animator_->Play();
    auto host = GetHost();
    CHECK_NULL_RETURN_NOLOG(host, false);
    host->OnAccessibilityEvent(AccessibilityEventType::SCROLL_END);
    return true;
}

void GridPattern::UpdateScrollBarOffset()
{
    if (!GetScrollBar() && !GetScrollBarProxy()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    const auto& info = gridLayoutInfo_;
    auto viewScopeSize = geometryNode->GetPaddingSize();
    auto layoutProperty = host->GetLayoutProperty<GridLayoutProperty>();

    float heightSum = 0;
    int32_t itemCount = 0;
    float offset = 0;
    float estimatedHeight = 0.f;
    if (scrollbarInfo_.first.has_value() && scrollbarInfo_.second.has_value()) {
        offset = scrollbarInfo_.first.value();
        estimatedHeight = scrollbarInfo_.second.value();
    } else {
        auto mainGap = GridUtils::GetMainGap(layoutProperty, viewScopeSize, info.axis_);
        for (const auto& item : info.lineHeightMap_) {
            auto line = info.gridMatrix_.find(item.first);
            if (line == info.gridMatrix_.end()) {
                continue;
            }
            if (line->second.empty()) {
                continue;
            }
            auto lineStart = line->second.begin()->second;
            auto lineEnd = line->second.rbegin()->second;
            itemCount += (lineEnd - lineStart + 1);
            heightSum += item.second + mainGap;
        }

        auto averageHeight = heightSum / itemCount;
        offset = info.startIndex_ * averageHeight - info.currentOffset_;
        if (itemCount >= (info.childrenCount_ - 1)) {
            estimatedHeight = heightSum - mainGap;
            offset = info.GetStartLineOffset(mainGap);
        } else {
            estimatedHeight = heightSum + (info.childrenCount_ - itemCount) * averageHeight;
        }
    }
    auto viewSize = geometryNode->GetFrameSize();
    Size mainSize = { viewSize.Width(), viewSize.Height() };
    UpdateScrollBarRegion(offset, estimatedHeight, mainSize, Offset(0.0, 0.0));
}

RefPtr<PaintProperty> GridPattern::CreatePaintProperty()
{
    auto defaultDisplayMode = DisplayMode::OFF;
    const static int32_t PLATFORM_VERSION_TEN = 10;
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    if (pipeline->GetMinPlatformVersion() >= PLATFORM_VERSION_TEN) {
        defaultDisplayMode = DisplayMode::AUTO;
    }
    auto property = MakeRefPtr<ScrollablePaintProperty>();
    // default "scrollBar" attribute of Grid is BarState.Off
    property->UpdateScrollBarMode(defaultDisplayMode);
    return property;
}

int32_t GridPattern::GetOriginalIndex() const
{
    return gridLayoutInfo_.GetOriginalIndex();
}

int32_t GridPattern::GetCrossCount() const
{
    return gridLayoutInfo_.crossCount_;
}

int32_t GridPattern::GetChildrenCount() const
{
    return gridLayoutInfo_.childrenCount_;
}

void GridPattern::ClearDragState()
{
    gridLayoutInfo_.ClearDragState();
}

void GridPattern::UpdateRectOfDraggedInItem(int32_t insertIndex)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    std::list<RefPtr<FrameNode>> children;
    host->GenerateOneDepthAllFrame(children);
    for (const auto& item : children) {
        auto itemPattern = item->GetPattern<GridItemPattern>();
        CHECK_NULL_VOID(itemPattern);
        auto mainIndex = itemPattern->GetMainIndex();
        auto crossIndex = itemPattern->GetCrossIndex();
        if (mainIndex * gridLayoutInfo_.crossCount_ + crossIndex == insertIndex) {
            auto size = item->GetRenderContext()->GetPaintRectWithTransform();
            size.SetOffset(item->GetTransformRelativeOffset());
            gridLayoutInfo_.currentRect_ = size;
            break;
        }
    }
}

void GridPattern::MoveItems(int32_t itemIndex, int32_t insertIndex)
{
    if (insertIndex < 0 ||
        insertIndex >= ((itemIndex == -1) ? (gridLayoutInfo_.childrenCount_ + 1) : gridLayoutInfo_.childrenCount_)) {
        return;
    }

    if (itemIndex == -1) {
        UpdateRectOfDraggedInItem(insertIndex);
    }

    gridLayoutInfo_.SwapItems(itemIndex, insertIndex);

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    auto pipeline = PipelineContext::GetCurrentContext();
    if (pipeline) {
        pipeline->FlushUITasks();
    }
}

bool GridPattern::IsOutOfBoundary()
{
    return gridLayoutInfo_.reachStart_ || gridLayoutInfo_.offsetEnd_;
}

void GridPattern::SetEdgeEffectCallback(const RefPtr<ScrollEdgeEffect>& scrollEffect)
{
    scrollEffect->SetCurrentPositionCallback([weak = AceType::WeakClaim(this)]() -> double {
        auto grid = weak.Upgrade();
        CHECK_NULL_RETURN_NOLOG(grid, 0.0);
        return grid->gridLayoutInfo_.currentOffset_;
    });
    scrollEffect->SetLeadingCallback([weak = AceType::WeakClaim(this)]() -> double {
        auto grid = weak.Upgrade();
        CHECK_NULL_RETURN_NOLOG(grid, 0.0);
        return grid->GetMainContentSize() - grid->gridLayoutInfo_.GetTotalHeightOfItemsInView(grid->GetMainGap());
    });
    scrollEffect->SetTrailingCallback([]() -> double { return 0.0; });
    scrollEffect->SetInitLeadingCallback([weak = AceType::WeakClaim(this)]() -> double {
        auto grid = weak.Upgrade();
        CHECK_NULL_RETURN_NOLOG(grid, 0.0);
        return grid->GetMainContentSize() - grid->gridLayoutInfo_.GetTotalHeightOfItemsInView(grid->GetMainGap());
    });
    scrollEffect->SetInitTrailingCallback([]() -> double { return 0.0; });
}

bool GridPattern::OutBoundaryCallback()
{
    return IsOutOfBoundary();
}

OverScrollOffset GridPattern::GetOverScrollOffset(double delta) const
{
    OverScrollOffset offset = { 0, 0 };
    if (gridLayoutInfo_.startIndex_ == 0) {
        auto startPos = gridLayoutInfo_.currentOffset_;
        auto newStartPos = startPos + delta;
        if (startPos > 0 && newStartPos > 0) {
            offset.start = delta;
        }
        if (startPos > 0 && newStartPos <= 0) {
            offset.start = -startPos;
        }
        if (startPos <= 0 && newStartPos > 0) {
            offset.start = newStartPos;
        }
    }
    if (gridLayoutInfo_.endIndex_ == gridLayoutInfo_.childrenCount_ - 1) {
        auto endPos = gridLayoutInfo_.currentOffset_ + gridLayoutInfo_.totalHeightOfItemsInView_;
        auto newEndPos = endPos + delta;
        if (endPos < gridLayoutInfo_.lastMainSize_ && newEndPos < gridLayoutInfo_.lastMainSize_) {
            offset.end = delta;
        }
        if (endPos < gridLayoutInfo_.lastMainSize_ && newEndPos >= gridLayoutInfo_.lastMainSize_) {
            offset.end = gridLayoutInfo_.lastMainSize_ - endPos;
        }
        if (endPos >= gridLayoutInfo_.lastMainSize_ && newEndPos < gridLayoutInfo_.lastMainSize_) {
            offset.end = newEndPos - gridLayoutInfo_.lastMainSize_;
        }
    }
    return offset;
}

void GridPattern::SetAccessibilityAction()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto accessibilityProperty = host->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    accessibilityProperty->SetActionScrollForward([weakPtr = WeakClaim(this)]() {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (!pattern->IsScrollable()) {
            return;
        }
        pattern->ScrollPage(false);
    });

    accessibilityProperty->SetActionScrollBackward([weakPtr = WeakClaim(this)]() {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (!pattern->IsScrollable()) {
            return;
        }
        pattern->ScrollPage(true);
    });
}
} // namespace OHOS::Ace::NG
