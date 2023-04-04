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
    return MakeRefPtr<GridScrollLayoutAlgorithm>(gridLayoutInfo_, crossCount, mainCount);
}

RefPtr<NodePaintMethod> GridPattern::CreateNodePaintMethod()
{
    return MakeRefPtr<GridPaintMethod>(GetScrollBar());
}

void GridPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToBounds(true);
}

void GridPattern::OnModifyDone()
{
    if (multiSelectable_ && !isMouseEventInit_) {
        InitMouseEvent();
    }

    if (!multiSelectable_ && isMouseEventInit_) {
        UninitMouseEvent();
    }

    auto gridLayoutProperty = GetLayoutProperty<GridLayoutProperty>();
    CHECK_NULL_VOID(gridLayoutProperty);
    gridLayoutInfo_.axis_ = gridLayoutProperty->IsVertical() ? Axis::VERTICAL : Axis::HORIZONTAL;
    isConfigScrollable_ = gridLayoutProperty->IsConfiguredScrollable();
    if (!isConfigScrollable_) {
        LOGD("use fixed grid template");
        return;
    }
    SetAxis(gridLayoutInfo_.axis_);
    AddScrollEvent();

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
        auto mouseOffsetX = static_cast<float>(info.GetLocalLocation().GetX());
        auto mouseOffsetY = static_cast<float>(info.GetLocalLocation().GetY());
        auto selectedZone = ComputeSelectedZone(mouseStartOffset_, mouseEndOffset_);
        if (!selectedZone.IsInRegion(PointF(mouseOffsetX, mouseOffsetY))) {
            ClearMultiSelect();
        }
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
        auto selectedZone = ComputeSelectedZone(mouseStartOffset_, mouseEndOffset_);
        if (!selectedZone.IsInRegion(PointF(mouseOffsetX, mouseOffsetY))) {
            ClearMultiSelect();
            mouseStartOffset_ = OffsetF(mouseOffsetX, mouseOffsetY);
            mouseEndOffset_ = OffsetF(mouseOffsetX, mouseOffsetY);
        }
        mousePressOffset_ = OffsetF(mouseOffsetX, mouseOffsetY);
        // do not select when click
    } else if (info.GetAction() == MouseAction::MOVE) {
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

bool GridPattern::UpdateCurrentOffset(float offset, int32_t source)
{
    if (!isConfigScrollable_) {
        return false;
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    // When finger moves down, offset is positive.
    // When finger moves up, offset is negative.
    if (gridLayoutInfo_.offsetEnd_) {
        if (LessOrEqual(offset, 0)) {
            return false;
        }
        gridLayoutInfo_.offsetEnd_ = false;
        gridLayoutInfo_.reachEnd_ = false;
    }
    if (gridLayoutInfo_.reachStart_) {
        if (GreatOrEqual(offset, 0.0)) {
            return false;
        }
        gridLayoutInfo_.reachStart_ = false;
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
    if (gridLayoutInfo_.startMainLineIndex_ != gridLayoutInfo.startMainLineIndex_) {
        eventhub->FireOnScrollToIndex(gridLayoutInfo.startIndex_);
        FlushFocusOnScroll(gridLayoutInfo);
    }
    gridLayoutInfo_ = gridLayoutInfo;
    gridLayoutInfo_.childrenCount_ = dirty->GetTotalChildCount();

    UpdateScrollBarOffset();
    return false;
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

std::pair<FocusStep, FocusStep> GridPattern::GetFocusSteps(
    int32_t curCrossIndex, int32_t curMaxCrossCount, FocusStep step) const
{
    auto firstStep = FocusStep::NONE;
    auto secondStep = FocusStep::NONE;
    if (gridLayoutInfo_.axis_ == Axis::VERTICAL) {
        if (curCrossIndex == 0 && step == FocusStep::LEFT) {
            firstStep = FocusStep::UP;
            secondStep = FocusStep::RIGHT_END;
        } else if (curCrossIndex == curMaxCrossCount - 1 && step == FocusStep::RIGHT) {
            firstStep = FocusStep::DOWN;
            secondStep = FocusStep::LEFT_END;
        }
    } else if (gridLayoutInfo_.axis_ == Axis::HORIZONTAL) {
        if (curCrossIndex == 0 && step == FocusStep::UP) {
            firstStep = FocusStep::LEFT;
            secondStep = FocusStep::DOWN_END;
        } else if (curCrossIndex == curMaxCrossCount - 1 && step == FocusStep::DOWN) {
            firstStep = FocusStep::RIGHT;
            secondStep = FocusStep::UP_END;
        }
    }
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
    auto curMaxCrossCount = static_cast<int32_t>((gridLayoutInfo_.gridMatrix_[curMainIndex]).size());
    LOGD("Current focused item(%{public}d,%{public}d)-[%{public}d,%{public}d]'s cross count is %{public}d.",
        curMainIndex, curCrossIndex, curMainSpan, curCrossSpan, curMaxCrossCount);
    auto focusSteps = GetFocusSteps(curCrossIndex, curMaxCrossCount, step);
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
        auto nextMaxCrossCount = static_cast<int32_t>((gridLayoutInfo_.gridMatrix_[nextMainIndex]).size());
        auto weakChild = SearchFocusableChildInCross(nextMainIndex, nextCrossIndex, nextMaxCrossCount);
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
    LOGD("Current item: (%{public}d,%{public}d)-[%{public}d,%{public}d]. Grid axis: %{public}d, step: %{public}d",
        curMainIndex, curCrossIndex, curMainSpan, curCrossSpan, gridLayoutInfo_.axis_, step);
    auto curMainStart = gridLayoutInfo_.startMainLineIndex_;
    auto curMainEnd = gridLayoutInfo_.endMainLineIndex_;
    auto curChildStartIndex = gridLayoutInfo_.startIndex_;
    auto curChildEndIndex = gridLayoutInfo_.endIndex_;
    auto childrenCount = gridLayoutInfo_.childrenCount_;
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
        nextCrossIndex = curCrossIndex;
    } else if ((step == FocusStep::DOWN && gridLayoutInfo_.axis_ == Axis::HORIZONTAL) ||
               (step == FocusStep::RIGHT && gridLayoutInfo_.axis_ == Axis::VERTICAL)) {
        nextMainIndex = curMainIndex;
        nextCrossIndex = curCrossIndex + curCrossSpan;
    } else if ((step == FocusStep::DOWN && gridLayoutInfo_.axis_ == Axis::VERTICAL) ||
               (step == FocusStep::RIGHT && gridLayoutInfo_.axis_ == Axis::HORIZONTAL)) {
        nextMainIndex = curMainIndex + curMainSpan;
        nextCrossIndex = curCrossIndex;
    } else {
        LOGE("Return: Invalid step: %{public}d and axis: %{public}d", step, gridLayoutInfo_.axis_);
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
        LOGI("Return: Move stoped. Next index: (%{public}d,%{public}d) is same as current: (%{public}d,%{public}d).",
            nextMainIndex, nextCrossIndex, curMainIndex, curCrossIndex);
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
        LOGW("Return: Error. Next main index is out of range(%{public}d,%{public}d)", curMainStart, curMainEnd);
        return { -1, -1 };
    }
    if (nextCrossIndex < 0) {
        LOGW("Return: Error. Next cross index is less than 0.");
        return { -1, -1 };
    }
    auto nextMaxCrossCount = static_cast<int32_t>((gridLayoutInfo_.gridMatrix_[nextMainIndex]).size());
    if (nextCrossIndex >= nextMaxCrossCount) {
        LOGD("Return: { %{public}d,%{public}d }. Next cross index is greater than max cross count", nextMainIndex,
            nextMaxCrossCount - 1);
        return { nextMainIndex, nextMaxCrossCount - 1 };
    }
    LOGD("Return: { %{public}d,%{public}d }.", nextMainIndex, nextCrossIndex);
    return { nextMainIndex, nextCrossIndex };
}

WeakPtr<FocusHub> GridPattern::SearchFocusableChildInCross(int32_t mainIndex, int32_t crossIndex, int32_t maxCrossCount)
{
    LOGD("Search child from index: (%{public}d,%{public}d)", mainIndex, crossIndex);
    int32_t direction = 0;
    auto indexLeft = crossIndex;
    auto indexRight = crossIndex;
    while (indexLeft >= 0 || indexRight < maxCrossCount) {
        int32_t curIndex = indexLeft;
        if (indexLeft < 0) {
            curIndex = indexRight++;
        } else if (indexRight >= maxCrossCount) {
            curIndex = indexLeft--;
        } else {
            curIndex = direction++ % 2 == 0 ? indexLeft-- : indexRight--;
        }
        auto weakChild = GetChildFocusNodeByIndex(mainIndex, curIndex);
        auto child = weakChild.Upgrade();
        if (child && child->IsFocusable()) {
            LOGD("Found child. Index: %{public}d,%{public}d", mainIndex, curIndex);
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
    LOGD("The target item at location(%{public}d,%{public}d) can not found.", tarMainIndex, tarCrossIndex);
    return nullptr;
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
    auto nextIndex = gridLayoutInfo_.gridMatrix_[nextMainIndex][nextCrossIndex];
    UpdateStartIndex(nextIndex);
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
}

bool GridPattern::UpdateStartIndex(uint32_t index)
{
    if (!isConfigScrollable_) {
        return false;
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    gridLayoutInfo_.jumpIndex_ = index;
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    return true;
}

bool GridPattern::AnimateTo(float position, float duration, const RefPtr<Curve>& curve)
{
    if (!isConfigScrollable_) {
        return false;
    }
    if (!animator_) {
        animator_ = AceType::MakeRefPtr<Animator>(PipelineBase::GetCurrentContext());
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
    auto mainGap = GridUtils::GetMainGap(layoutProperty, viewScopeSize, info.axis_);
    for (const auto& item : info.lineHeightMap_) {
        auto line = info.gridMatrix_.find(item.first);
        if (line != info.gridMatrix_.end()) {
            itemCount += static_cast<int32_t>(line->second.size());
        } else {
            itemCount += info.crossCount_;
        }
        heightSum += item.second + mainGap;
    }

    float estimatedHeight = 0.f;
    auto averageHeight_ = heightSum / itemCount;
    if (itemCount >= (info.childrenCount_ - 1)) {
        estimatedHeight = heightSum - mainGap;
    } else {
        estimatedHeight = heightSum + (info.childrenCount_ - itemCount) * averageHeight_;
    }

    float offset = info.startIndex_ * averageHeight_ - info.currentOffset_;
    Size mainSize = { viewScopeSize.Width(), viewScopeSize.Height() };
    UpdateScrollBarRegion(offset, estimatedHeight, mainSize);
}

RefPtr<PaintProperty> GridPattern::CreatePaintProperty()
{
    auto property = MakeRefPtr<ScrollablePaintProperty>();
    // default "scrollBar" attribute of Grid is BarState.Off
    property->UpdateScrollBarMode(NG::DisplayMode::OFF);
    return property;
}
} // namespace OHOS::Ace::NG