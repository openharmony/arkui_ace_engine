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

#include "core/components_ng/pattern/grid/grid_pattern.h"

#include "core/components_ng/pattern/grid/grid_adaptive/grid_adaptive_layout_algorithm.h"
#include "core/components_ng/pattern/grid/grid_item_pattern.h"
#include "core/components_ng/pattern/grid/grid_layout/grid_layout_algorithm.h"
#include "core/components_ng/pattern/grid/grid_scroll/grid_scroll_layout_algorithm.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {

namespace {
constexpr Color SELECT_FILL_COLOR = Color(0x1A000000);
constexpr Color SELECT_STROKE_COLOR = Color(0x33FFFFFF);
constexpr Color ITEM_FILL_COLOR = Color(0x1A0A59f7);
} // namespace

RefPtr<LayoutAlgorithm> GridPattern::CreateLayoutAlgorithm()
{
    auto gridLayoutProperty = GetLayoutProperty<GridLayoutProperty>();
    CHECK_NULL_RETURN(gridLayoutProperty, nullptr);
    std::vector<std::string> cols;
    StringUtils::StringSplitter(gridLayoutProperty->GetColumnsTemplate().value_or(""), ' ', cols);
    std::vector<std::string> rows;
    StringUtils::StringSplitter(gridLayoutProperty->GetRowsTemplate().value_or(""), ' ', rows);
    auto crossCount = cols.empty() ? Infinity<int32_t>() : cols.size();
    auto mainCount = rows.empty() ? Infinity<int32_t>() : rows.size();
    if (!gridLayoutProperty->IsVertical()) {
        std::swap(crossCount, mainCount);
    }

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

void GridPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToFrame(true);
}

void GridPattern::OnModifyDone()
{
    if (multiSelectable_ && !isMouseEventInit_) {
        InitMouseEvent();
    }

    auto gridLayoutProperty = GetLayoutProperty<GridLayoutProperty>();
    CHECK_NULL_VOID(gridLayoutProperty);
    gridLayoutInfo_.axis_ = gridLayoutProperty->IsVertical() ? Axis::VERTICAL : Axis::HORIZONTAL;
    isConfigScrollable_ = gridLayoutProperty->IsConfiguredScrollable();

    if (gridLayoutProperty->GetColumnsTemplate().has_value() && gridLayoutProperty->GetRowsTemplate().has_value()) {
        LOGD("use fixed grid template");
        return;
    }
    AddScrollEvent();

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetFocusHub();
    if (focusHub) {
        InitOnKeyEvent(focusHub);
    }
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
    auto mouseOffsetX = static_cast<float>(info.GetLocalLocation().GetX());
    auto mouseOffsetY = static_cast<float>(info.GetLocalLocation().GetY());

    if (info.GetButton() == MouseButton::LEFT_BUTTON) {
        if (info.GetAction() == MouseAction::PRESS) {
            ClearMultiSelect();
            mouseStartOffset_ = OffsetF(mouseOffsetX, mouseOffsetY);
            mouseEndOffset_ = OffsetF(mouseOffsetX, mouseOffsetY);
            auto selectedZone = ComputeSelectedZone(mouseStartOffset_, mouseEndOffset_);
            MultiSelectWithoutKeyboard(selectedZone);
        } else if (info.GetAction() == MouseAction::MOVE) {
            mouseEndOffset_ = OffsetF(mouseOffsetX, mouseOffsetY);
            auto selectedZone = ComputeSelectedZone(mouseStartOffset_, mouseEndOffset_);
            MultiSelectWithoutKeyboard(selectedZone);
        } else if (info.GetAction() == MouseAction::RELEASE) {
            mouseStartOffset_.Reset();
            mouseEndOffset_.Reset();
            ClearSelectedZone();
        }
    }
}

void GridPattern::MultiSelectWithoutKeyboard(const RectF& selectedZone)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    for (const auto& item : host->GetChildren()) {
        if (!AceType::InstanceOf<FrameNode>(item)) {
            continue;
        }

        auto itemFrameNode = AceType::DynamicCast<FrameNode>(item);
        auto itemPattern = itemFrameNode->GetPattern<GridItemPattern>();
        CHECK_NULL_VOID(itemPattern);

        if (!itemPattern->Selectable()) {
            continue;
        }

        auto itemGeometry = itemFrameNode->GetGeometryNode();
        CHECK_NULL_VOID(itemGeometry);

        auto itemRect = itemGeometry->GetFrameRect();
        if (!selectedZone.IsIntersectWith(itemRect)) {
            itemPattern->MarkIsSelected(false);
        } else {
            itemPattern->MarkIsSelected(true);
        }
        auto context = itemFrameNode->GetRenderContext();
        CHECK_NULL_VOID(context);
        context->OnMouseSelectUpdate(ITEM_FILL_COLOR, ITEM_FILL_COLOR);
    }

    auto hostContext = host->GetRenderContext();
    CHECK_NULL_VOID(hostContext);
    hostContext->UpdateMouseSelectWithRect(selectedZone, SELECT_FILL_COLOR, SELECT_STROKE_COLOR);
}

void GridPattern::ClearMultiSelect()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    for (const auto& item : host->GetChildren()) {
        if (!AceType::InstanceOf<FrameNode>(item)) {
            continue;
        }

        auto itemFrameNode = AceType::DynamicCast<FrameNode>(item);
        auto itemPattern = itemFrameNode->GetPattern<GridItemPattern>();
        CHECK_NULL_VOID(itemPattern);
        itemPattern->MarkIsSelected(false);
        auto renderContext = itemFrameNode->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        renderContext->OnMouseSelectUpdate(ITEM_FILL_COLOR, ITEM_FILL_COLOR);
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

void GridPattern::AddScrollEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    if (scrollableEvent_) {
        gestureHub->RemoveScrollableEvent(scrollableEvent_);
    }
    scrollableEvent_ = MakeRefPtr<ScrollableEvent>(gridLayoutInfo_.axis_);
    auto scrollCallback = [weak = WeakClaim(this)](double offset, int32_t source) {
        auto gridPattern = weak.Upgrade();
        if (!gridPattern) {
            LOGE("grid pattern upgrade fail when try handle scroll event.");
            return false;
        }
        return gridPattern->UpdateScrollPosition(static_cast<float>(offset), source);
    };
    scrollableEvent_->SetScrollPositionCallback(std::move(scrollCallback));
    gestureHub->AddScrollableEvent(scrollableEvent_);
}

bool GridPattern::UpdateScrollPosition(float offset, int32_t source)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    // When finger moves down, offset is positive.
    // When finger moves up, offset is negative.
    if (gridLayoutInfo_.reachEnd_) {
        if (LessOrEqual(offset, 0)) {
            return false;
        }
        gridLayoutInfo_.reachEnd_ = false;
    }
    if (gridLayoutInfo_.reachStart_) {
        if (GreatOrEqual(offset, 0.0)) {
            return false;
        }
        gridLayoutInfo_.reachStart_ = false;
    }
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
    gridLayoutInfo_ = gridLayoutAlgorithm->GetGridLayoutInfo();
    return false;
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

    auto curMainIndex = curItemPattern->GetMainIndex();
    auto curCrossIndex = curItemPattern->GetCrossIndex();
    if (curMainIndex < 0 || curCrossIndex < 0) {
        LOGE("can't find focused child.");
        return nullptr;
    }
    LOGD("Current item location is (%{public}d,%{public}d)", curMainIndex, curCrossIndex);

    auto nextMainIndex = curMainIndex;
    auto nextCrossIndex = curCrossIndex;
    switch (step) {
        case FocusStep::UP:
            gridLayoutInfo_.axis_ == Axis::HORIZONTAL ? --nextCrossIndex : --nextMainIndex;
            break;
        case FocusStep::DOWN:
            gridLayoutInfo_.axis_ == Axis::HORIZONTAL ? ++nextCrossIndex : ++nextMainIndex;
            break;
        case FocusStep::LEFT:
            gridLayoutInfo_.axis_ == Axis::HORIZONTAL ? --nextMainIndex : --nextCrossIndex;
            break;
        case FocusStep::RIGHT:
            gridLayoutInfo_.axis_ == Axis::HORIZONTAL ? ++nextMainIndex : ++nextCrossIndex;
            break;
        default:
            break;
    }
    LOGD("Next item location is (%{public}d,%{public}d)", nextMainIndex, nextCrossIndex);
    auto maxMainCount = static_cast<int32_t>((gridLayoutInfo_.gridMatrix_).size());
    auto maxCrossCount = static_cast<int32_t>((gridLayoutInfo_.gridMatrix_[nextMainIndex]).size());
    if (nextMainIndex < 0 || nextMainIndex >= maxMainCount || nextCrossIndex < 0 || nextCrossIndex >= maxCrossCount) {
        LOGD("Next item is not exist");
        return nullptr;
    }

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
        if (childItemPattern->GetMainIndex() == nextMainIndex && childItemPattern->GetCrossIndex() == nextCrossIndex) {
            return AceType::WeakClaim(AceType::RawPtr(childFocus));
        }
    }

    return nullptr;
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
    if (event.code == KeyCode::KEY_PAGE_DOWN) {
        if (!isConfigScrollable_) {
            return false;
        }
        LOGD("Keycode is PgDn. Scroll offset is %{public}f", -GetMainContentSize());
        UpdateScrollPosition(-GetMainContentSize(), SCROLL_FROM_UPDATE);
        return true;
    }
    if (event.code == KeyCode::KEY_PAGE_UP) {
        if (!isConfigScrollable_) {
            return false;
        }
        LOGD("Keycode is PgUp. Scroll offset is %{public}f", GetMainContentSize());
        UpdateScrollPosition(GetMainContentSize(), SCROLL_FROM_UPDATE);
        return true;
    }
    if (event.code == KeyCode::KEY_DPAD_UP || event.code == KeyCode::KEY_DPAD_DOWN) {
        HandleDirectionKey(event.code);
        return true;
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

} // namespace OHOS::Ace::NG