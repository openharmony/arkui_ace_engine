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

#include "core/components_ng/pattern/linear_split/linear_split_pattern.h"

#include "base/geometry/axis.h"
#include "base/geometry/offset.h"
#include "base/memory/referenced.h"
#include "base/mousestyle/mouse_style.h"
#include "base/utils/utils.h"
#include "core/components_ng/pattern/linear_split/linear_split_model.h"
#include "core/gestures/gesture_info.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

namespace {

constexpr std::size_t DEFAULT_DRAG_INDEX = -1;

} // namespace

void LinearSplitPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToFrame(true);
}

void LinearSplitPattern::InitPanEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    if (panEvent_) {
        return;
    }
    auto actionStartTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(pattern);
        pattern->HandlePanStart(info.GetOffsetX(), info.GetOffsetY(), info.GetGlobalLocation());
    };
    auto actionUpdateTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(pattern);
        pattern->HandlePanUpdate(info.GetOffsetX(), info.GetOffsetY(), info.GetGlobalLocation());
    };
    auto actionEndTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(pattern);
        pattern->HandlePanEnd(info.GetGlobalLocation());
    };
    auto actionCancelTask = [weak = WeakClaim(this)]() {};
    if (panEvent_) {
        gestureHub->RemovePanEvent(panEvent_);
    }
    panEvent_ = MakeRefPtr<PanEvent>(
        std::move(actionStartTask), std::move(actionUpdateTask), std::move(actionEndTask), std::move(actionCancelTask));

    PanDirection panDirection;
    panDirection.type = PanDirection::ALL;
    gestureHub->AddPanEvent(panEvent_, panDirection, DEFAULT_PAN_FINGER, DEFAULT_PAN_DISTANCE);
}

void LinearSplitPattern::HandlePanStart(float xOffset, float yOffset, const Offset& globalLocation)
{
    auto localOffset = OffsetF(static_cast<float>(globalLocation.GetX()) - parentOffset_.GetX(),
        static_cast<float>(globalLocation.GetY()) - parentOffset_.GetY());
    if (!resizeable_) {
        return;
    }

    for (std::size_t i = 0; i < splitRects_.size(); i++) {
        if (splitRects_[i].IsInRegion(Point(localOffset.GetX(), localOffset.GetY()))) {
            dragedSplitIndex_ = i;
            break;
        }
    }

    if (dragedSplitIndex_ == DEFAULT_DRAG_INDEX) {
        return;
    }

    isDragedMoving_ = true;
    isDraged_ = true;

    if (splitType_ == SplitType::ROW_SPLIT) {
        preOffset_ = xOffset;
        if (isOverParent_) {
            if (xOffset > 0.0 || (xOffset < 0.0 && dragSplitOffset_[dragedSplitIndex_] <= 0.0)) {
                return;
            } else {
                isOverParent_ = false;
            }
        }
        dragSplitOffset_[dragedSplitIndex_] += xOffset;
    } else {
        preOffset_ = yOffset;
        if (isOverParent_) {
            if (yOffset > 0.0 || (yOffset < 0.0 && dragSplitOffset_[dragedSplitIndex_] <= 0.0)) {
                return;
            } else {
                isOverParent_ = false;
            }
        }
        dragSplitOffset_[dragedSplitIndex_] += yOffset;
    }

    if (dragSplitOffset_[dragedSplitIndex_] < 0.0) {
        isDragedMoving_ = false;
        dragSplitOffset_[dragedSplitIndex_] = dragSplitOffset_[dragedSplitIndex_] = 0.0;
    } else {
        dragSplitOffset_[dragedSplitIndex_] = dragSplitOffset_[dragedSplitIndex_];
    }
}

void LinearSplitPattern::GetdragedSplitIndexOrIsMoving(const Point& point)
{
    for (std::size_t i = 0; i < splitRects_.size(); i++) {
        if (splitRects_[i].IsInRegion(point)) {
            if (dragedSplitIndex_ == DEFAULT_DRAG_INDEX) {
                dragedSplitIndex_ = i;
                isDragedMoving_ = true;
                break;
            } else if (dragedSplitIndex_ == i) {
                isDragedMoving_ = true;
            }
        }
    }
}

void LinearSplitPattern::HandlePanUpdate(float xOffset, float yOffset, const Offset& globalLocation)
{
    if (!resizeable_) {
        return;
    }
    if (isOverParent_) {
        isDragedMoving_ = false;
    }
    auto localOffset = OffsetF(static_cast<float>(globalLocation.GetX()) - parentOffset_.GetX(),
        static_cast<float>(globalLocation.GetY()) - parentOffset_.GetY());
    if (dragedSplitIndex_ == DEFAULT_DRAG_INDEX || !isDragedMoving_) {
        GetdragedSplitIndexOrIsMoving(Point(localOffset.GetX(), localOffset.GetY()));
    }

    if (dragedSplitIndex_ == DEFAULT_DRAG_INDEX || !isDragedMoving_) {
        if (splitType_ == SplitType::ROW_SPLIT) {
            preOffset_ = xOffset;
        } else {
            preOffset_ = yOffset;
        }
        return;
    }

    if (splitType_ == SplitType::ROW_SPLIT) {
        if (isOverParent_) {
            if (dragSplitOffset_[dragedSplitIndex_] <= 0.0 || xOffset - preOffset_ >= 0.0) {
                preOffset_ = xOffset;
                return;
            } else {
                isOverParent_ = false;
            }
        }
        dragSplitOffset_[dragedSplitIndex_] += xOffset - preOffset_;
        preOffset_ = xOffset;
    } else {
        if (isOverParent_) {
            if (dragSplitOffset_[dragedSplitIndex_] <= 0.0 || yOffset - preOffset_ >= 0.0) {
                preOffset_ = yOffset;
                return;
            } else {
                isOverParent_ = false;
            }
        }
        dragSplitOffset_[dragedSplitIndex_] += yOffset - preOffset_;
        preOffset_ = yOffset;
    }

    if (dragSplitOffset_[dragedSplitIndex_] < 0.0) {
        isDragedMoving_ = false;
        dragSplitOffset_[dragedSplitIndex_] = dragSplitOffset_[dragedSplitIndex_] = 0.0;
    } else {
        dragSplitOffset_[dragedSplitIndex_] = dragSplitOffset_[dragedSplitIndex_];
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void LinearSplitPattern::HandlePanEnd(const Offset& globalLocation)
{
    isDragedMoving_ = false;
    isDraged_ = false;
    dragedSplitIndex_ = DEFAULT_DRAG_INDEX;
    mouseDragedSplitIndex_ = DEFAULT_DRAG_INDEX;
}

void LinearSplitPattern::InitMouseEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    if (mouseEvent_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto mouseEventHub = host->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(mouseEventHub);

    auto mouseTask = [weak = WeakClaim(this)](MouseInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(pattern);
        pattern->HandleMouseEvent(info.GetGlobalLocation());
    };
    mouseEvent_ = MakeRefPtr<InputEvent>(std::move(mouseTask));
    mouseEventHub->AddOnMouseEvent(mouseEvent_);
}

void LinearSplitPattern::HandleMouseEvent(const Offset& globalLocation)
{
    if (!resizeable_) {
        return;
    }
    auto mouseStyle = MouseStyle::CreateMouseStyle();
    CHECK_NULL_VOID(mouseStyle);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto windowId = pipeline->GetWindowId();
    int32_t pointerStyle = 0;
    MouseFormat mousePointerStyle;

    if (splitType_ == SplitType::ROW_SPLIT) {
        mousePointerStyle = MouseFormat::WEST_EAST;
    } else {
        mousePointerStyle = MouseFormat::NORTH_SOUTH;
    }

    if (isDraged_) {
        if (mouseDragedSplitIndex_ == DEFAULT_DRAG_INDEX) {
            mouseDragedSplitIndex_ = dragedSplitIndex_;
            mouseStyle->GetPointerStyle(windowId, pointerStyle);
            if (pointerStyle == static_cast<int32_t>(MouseFormat::DEFAULT)) {
                mouseStyle->SetPointerStyle(windowId, mousePointerStyle);
            }
        }
        return;
    }
    auto localOffset = OffsetF(static_cast<float>(globalLocation.GetX()) - parentOffset_.GetX(),
        static_cast<float>(globalLocation.GetY()) - parentOffset_.GetY());

    mouseDragedSplitIndex_ = DEFAULT_DRAG_INDEX;
    for (std::size_t i = 0; i < splitRects_.size(); i++) {
        if (splitRects_[i].IsInRegion(Point(localOffset.GetX(), localOffset.GetY()))) {
            mouseDragedSplitIndex_ = i;
            dragedSplitIndex_ = i;
            isDragedMoving_ = true;
            break;
        }
    }
    mouseStyle->GetPointerStyle(windowId, pointerStyle);

    if (splitType_ == SplitType::ROW_SPLIT) {
        if (mouseDragedSplitIndex_ != DEFAULT_DRAG_INDEX &&
            pointerStyle != static_cast<int32_t>(MouseFormat::WEST_EAST)) {
            mouseStyle->SetPointerStyle(windowId, mousePointerStyle);
        }
    } else {
        if (mouseDragedSplitIndex_ != DEFAULT_DRAG_INDEX &&
            pointerStyle != static_cast<int32_t>(MouseFormat::NORTH_SOUTH)) {
            mouseStyle->SetPointerStyle(windowId, mousePointerStyle);
        }
    }

    if (mouseDragedSplitIndex_ == DEFAULT_DRAG_INDEX && pointerStyle != static_cast<int32_t>(MouseFormat::DEFAULT)) {
        MouseFormat defaultStyle = MouseFormat::DEFAULT;
        mouseStyle->SetPointerStyle(windowId, defaultStyle);
    }
}

void LinearSplitPattern::OnModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);

    auto layoutProperty = GetLayoutProperty<LinearSplitLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    resizeable_ = layoutProperty->GetResizeable().value_or(false);

    InitPanEvent(gestureHub);
    InitMouseEvent(gestureHub);
}

bool LinearSplitPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, bool skipMeasure, bool skipLayout)
{
    CHECK_NULL_RETURN_NOLOG(!skipMeasure, false);
    if (dirty->SkipMeasureContent()) {
        return false;
    }
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto linearSplitLayoutAlgorithm =
        DynamicCast<LinearSplitLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(linearSplitLayoutAlgorithm, false);
    childrenOffset_ = linearSplitLayoutAlgorithm->GetChildrenOffset();
    splitLength_ = linearSplitLayoutAlgorithm->GetSplitLength();
    splitRects_ = linearSplitLayoutAlgorithm->GetSplitRects();
    parentOffset_ = linearSplitLayoutAlgorithm->GetParentOffset();
    if (dragSplitOffset_.empty()) {
        dragSplitOffset_ = std::vector<float>(splitRects_.size(), 0.0);
    }
    isOverParent_ = linearSplitLayoutAlgorithm->GetIsOverParent();
    return true;
}

} // namespace OHOS::Ace::NG