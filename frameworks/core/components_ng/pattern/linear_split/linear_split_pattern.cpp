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

#include "base/memory/referenced.h"
#include "base/mousestyle/mouse_style.h"
#include "base/utils/utils.h"
#include "core/components_ng/event/input_event.h"
#include "core/components_ng/pattern/linear_split/linear_split_model.h"
#include "core/event/mouse_event.h"
#include "core/gestures/gesture_info.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

namespace {

constexpr std::size_t DEFAULT_DRAG_INDEX = -1;
constexpr std::size_t SPLIT_INDEX_INC_TWO = 2;
constexpr int32_t API10 = 10;

} // namespace

void LinearSplitPattern::InitPanEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    if (panEvent_) {
        return;
    }
    auto actionStartTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(pattern);
        pattern->HandlePanStart(info);
    };
    auto actionUpdateTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(pattern);
        pattern->HandlePanUpdate(info);
    };
    auto actionEndTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(pattern);
        pattern->HandlePanEnd(info);
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

void LinearSplitPattern::HandlePanStart(const GestureEvent& info)
{
    if (PipelineBase::GetCurrentContext() && PipelineBase::GetCurrentContext()->GetMinPlatformVersion() < API10) {
        HandlePanStartBeforeAPI10(info);
        return;
    }
    auto xOffset = static_cast<float>(info.GetOffsetX());
    auto yOffset = static_cast<float>(info.GetOffsetY());
    auto gestureOffsetX = static_cast<float>(info.GetLocalLocation().GetX());
    auto gestureOffsetY = static_cast<float>(info.GetLocalLocation().GetY());
    if (!resizeable_) {
        return;
    }
    isDraged_ = true;

    for (std::size_t i = 0; i < splitRects_.size(); i++) {
        if (splitRects_[i].IsInRegion(Point(gestureOffsetX, gestureOffsetY))) {
            dragedSplitIndex_ = i;
            break;
        }
    }

    if (dragedSplitIndex_ == DEFAULT_DRAG_INDEX) {
        return;
    }

    isDragedMoving_ = true;

    if (splitType_ == SplitType::ROW_SPLIT) {
        preOffset_ = xOffset;
        childrenDragPos_[dragedSplitIndex_ + 1] += xOffset;
    } else {
        preOffset_ = yOffset;
        childrenDragPos_[dragedSplitIndex_ + 1] += yOffset;
    }

    ConstrainDragRange();
}

void LinearSplitPattern::HandlePanStartBeforeAPI10(const GestureEvent& info)
{
    auto xOffset = static_cast<float>(info.GetOffsetX());
    auto yOffset = static_cast<float>(info.GetOffsetY());
    auto gestureOffsetX = static_cast<float>(info.GetLocalLocation().GetX());
    auto gestureOffsetY = static_cast<float>(info.GetLocalLocation().GetY());
    if (!resizeable_) {
        return;
    }
    isDraged_ = true;

    for (std::size_t i = 0; i < splitRects_.size(); i++) {
        if (splitRects_[i].IsInRegion(Point(gestureOffsetX, gestureOffsetY))) {
            dragedSplitIndex_ = i;
            break;
        }
    }

    if (dragedSplitIndex_ == DEFAULT_DRAG_INDEX) {
        return;
    }

    isDragedMoving_ = true;

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

float LinearSplitPattern::GetMinPosFromIndex(std::size_t index)
{
    auto preMin = childrenConstrains_[index];
    auto min = childrenDragPos_[index] + static_cast<float>(DEFAULT_SPLIT_HEIGHT) + preMin;
    return min;
}

float LinearSplitPattern::GetMaxPosFromIndex(std::size_t index)
{
    auto curMin = childrenConstrains_[index + 1];
    auto max = Infinity<float>();
    if (index + SPLIT_INDEX_INC_TWO < childrenDragPos_.size()) {
        max = childrenDragPos_[index + SPLIT_INDEX_INC_TWO] - static_cast<float>(DEFAULT_SPLIT_HEIGHT) - curMin;
    }
    return max;
}

void LinearSplitPattern::ConstrainDragRange()
{
    auto min = GetMinPosFromIndex(dragedSplitIndex_);
    auto max = GetMaxPosFromIndex(dragedSplitIndex_);
    auto &offset = childrenDragPos_[dragedSplitIndex_ + 1];
    if (offset < min) {
        offset = min;
    } else if (offset > max) {
        offset = max;
    }
}

bool LinearSplitPattern::IsStuck()
{
    auto min = GetMinPosFromIndex(mouseDragedSplitIndex_);
    auto max = GetMaxPosFromIndex(mouseDragedSplitIndex_);
    return NearZero(max - min);
}

bool LinearSplitPattern::ReachStart()
{
    auto min = GetMinPosFromIndex(mouseDragedSplitIndex_);
    auto offset = childrenDragPos_[mouseDragedSplitIndex_ + 1];
    return NearZero(offset - min);
}

bool LinearSplitPattern::ReachEnd()
{
    auto max = GetMaxPosFromIndex(mouseDragedSplitIndex_);
    auto offset = childrenDragPos_[mouseDragedSplitIndex_ + 1];
    return NearZero(max - offset);
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

void LinearSplitPattern::HandlePanUpdate(const GestureEvent& info)
{
    if (PipelineBase::GetCurrentContext() && PipelineBase::GetCurrentContext()->GetMinPlatformVersion() < API10) {
        HandlePanUpdateBeforeAPI10(info);
        return;
    }
    if (!resizeable_) {
        return;
    }
    auto xOffset = static_cast<float>(info.GetOffsetX());
    auto yOffset = static_cast<float>(info.GetOffsetY());
    auto gestureOffsetX = static_cast<float>(info.GetLocalLocation().GetX());
    auto gestureOffsetY = static_cast<float>(info.GetLocalLocation().GetY());
    if (dragedSplitIndex_ == DEFAULT_DRAG_INDEX || !isDragedMoving_) {
        GetdragedSplitIndexOrIsMoving(Point(gestureOffsetX, gestureOffsetY));
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
        childrenDragPos_[dragedSplitIndex_ + 1] += xOffset - preOffset_;
        preOffset_ = xOffset;
    } else {
        childrenDragPos_[dragedSplitIndex_ + 1] += yOffset - preOffset_;
        preOffset_ = yOffset;
    }

    ConstrainDragRange();

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void LinearSplitPattern::HandlePanUpdateBeforeAPI10(const GestureEvent& info)
{
    if (!resizeable_) {
        return;
    }
    auto xOffset = info.GetOffsetX();
    auto yOffset = info.GetOffsetY();
    if (isOverParent_) {
        isDragedMoving_ = false;
    }
    auto gestureOffsetX = static_cast<float>(info.GetLocalLocation().GetX());
    auto gestureOffsetY = static_cast<float>(info.GetLocalLocation().GetY());
    if (dragedSplitIndex_ == DEFAULT_DRAG_INDEX || !isDragedMoving_) {
        GetdragedSplitIndexOrIsMoving(Point(gestureOffsetX, gestureOffsetY));
    }

    if (dragedSplitIndex_ == DEFAULT_DRAG_INDEX || !isDragedMoving_) {
        preOffset_ = (splitType_ == SplitType::ROW_SPLIT) ? xOffset : yOffset;
        return;
    }

    if (splitType_ == SplitType::ROW_SPLIT) {
        if (isOverParent_) {
            if (dragSplitOffset_[dragedSplitIndex_] <= 0.0 || xOffset - preOffset_ >= 0.0) {
                preOffset_ = xOffset;
                return;
            }
            isOverParent_ = false;
        }
        dragSplitOffset_[dragedSplitIndex_] += xOffset - preOffset_;
        preOffset_ = xOffset;
    } else {
        if (isOverParent_) {
            if (dragSplitOffset_[dragedSplitIndex_] <= 0.0 || yOffset - preOffset_ >= 0.0) {
                preOffset_ = yOffset;
                return;
            }
            isOverParent_ = false;
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

void LinearSplitPattern::HandlePanEnd(const GestureEvent& info)
{
    isDragedMoving_ = false;
    isDraged_ = false;
    dragedSplitIndex_ = DEFAULT_DRAG_INDEX;
    mouseDragedSplitIndex_ = DEFAULT_DRAG_INDEX;

    if (info.GetSourceDevice() == SourceType::MOUSE) {
        auto gestureOffsetX = static_cast<float>(info.GetLocalLocation().GetX());
        auto gestureOffsetY = static_cast<float>(info.GetLocalLocation().GetY());
        GetdragedSplitIndexOrIsMoving(Point(gestureOffsetX, gestureOffsetY));
        if (dragedSplitIndex_ == DEFAULT_DRAG_INDEX) {
            auto pipeline = PipelineContext::GetCurrentContext();
            CHECK_NULL_VOID(pipeline);
            auto frame = GetHost();
            CHECK_NULL_VOID(frame);
            auto frameId = frame->GetId();
            pipeline->ChangeMouseStyle(frameId, MouseFormat::DEFAULT);
            pipeline->FreeMouseStyleHoldNode(frameId);
        }
        dragedSplitIndex_ = DEFAULT_DRAG_INDEX;
        isDragedMoving_ = false;
    }
}

void LinearSplitPattern::InitMouseEvent(const RefPtr<InputEventHub>& inputHub)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    CHECK_NULL_VOID(inputHub);

    if (!mouseEvent_) {
        auto mouseTask = [weak = WeakClaim(this)](MouseInfo& info) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID_NOLOG(pattern);
            pattern->HandleMouseEvent(info);
        };
        mouseEvent_ = MakeRefPtr<InputEvent>(std::move(mouseTask));
        inputHub->AddOnMouseEvent(mouseEvent_);
    }
    if (!hoverEvent_) {
        auto hoverTask = [weak = WeakClaim(this)](bool isHovered) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID_NOLOG(pattern);
            pattern->HandleHoverEvent(isHovered);
        };
        hoverEvent_ = MakeRefPtr<InputEvent>(std::move(hoverTask));
        inputHub->AddOnHoverEvent(hoverEvent_);
    }
}

void LinearSplitPattern::HandleMouseEvent(MouseInfo& info)
{
    if (!resizeable_) {
        return;
    }

    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto frame = GetHost();
    CHECK_NULL_VOID(frame);
    auto frameId = frame->GetId();
    pipeline->SetMouseStyleHoldNode(frameId);

    if (isDraged_) {
        if (mouseDragedSplitIndex_ == DEFAULT_DRAG_INDEX) {
            mouseDragedSplitIndex_ = dragedSplitIndex_;
        }
        if (mouseDragedSplitIndex_ != DEFAULT_DRAG_INDEX) {
            pipeline->ChangeMouseStyle(frameId, GetMouseFormat());
        }
        return;
    }
    auto mouseOffsetX = static_cast<float>(info.GetLocalLocation().GetX());
    auto mouseOffsetY = static_cast<float>(info.GetLocalLocation().GetY());

    mouseDragedSplitIndex_ = DEFAULT_DRAG_INDEX;
    for (std::size_t i = 0; i < splitRects_.size(); i++) {
        if (splitRects_[i].IsInRegion(Point(mouseOffsetX, mouseOffsetY))) {
            mouseDragedSplitIndex_ = i;
            if (info.GetButton() == MouseButton::LEFT_BUTTON && info.GetAction() == MouseAction::PRESS) {
                dragedSplitIndex_ = i;
                isDragedMoving_ = true;
            }
            break;
        }
    }

    if (mouseDragedSplitIndex_ != DEFAULT_DRAG_INDEX) {
        pipeline->ChangeMouseStyle(frameId, GetMouseFormat());
    } else {
        if (dragedSplitIndex_ == DEFAULT_DRAG_INDEX) {
            pipeline->ChangeMouseStyle(frameId, MouseFormat::DEFAULT);
        }
    }
    pipeline->FreeMouseStyleHoldNode(frameId);
}

void LinearSplitPattern::HandleHoverEvent(bool isHovered)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto frame = GetHost();
    CHECK_NULL_VOID(frame);
    auto frameId = frame->GetId();

    if (!isHovered && !isDraged_) {
        pipeline->SetMouseStyleHoldNode(frameId);
        pipeline->ChangeMouseStyle(frameId, MouseFormat::DEFAULT);
        pipeline->FreeMouseStyleHoldNode(frameId);
    }
}

MouseFormat LinearSplitPattern::GetMouseFormat()
{
    if (PipelineBase::GetCurrentContext() && PipelineBase::GetCurrentContext()->GetMinPlatformVersion() < API10) {
        return GetMouseFormatBeforeAPI10();
    }
    MouseFormat format = MouseFormat::DEFAULT;
    if (splitType_ == SplitType::ROW_SPLIT) {
        if (IsStuck()) {
            format = MouseFormat::DEFAULT;
        } else if (ReachStart()) {
            format = MouseFormat::EAST;
        } else if (ReachEnd()) {
            format = MouseFormat::WEST;
        } else {
            format = MouseFormat::WEST_EAST;
        }
    } else {
        if (IsStuck()) {
            format = MouseFormat::DEFAULT;
        } else if (ReachStart()) {
            format = MouseFormat::SOUTH;
        } else if (ReachEnd()) {
            format = MouseFormat::NORTH;
        } else {
            format = MouseFormat::NORTH_SOUTH;
        }
    }
    return format;
}

MouseFormat LinearSplitPattern::GetMouseFormatBeforeAPI10()
{
    MouseFormat format = MouseFormat::DEFAULT;
    if (splitType_ == SplitType::ROW_SPLIT) {
        if (isOverParent_ && NearZero(dragSplitOffset_[mouseDragedSplitIndex_])) {
            format = MouseFormat::DEFAULT;
        } else if (isOverParent_) {
            format = MouseFormat::WEST;
        } else if (NearZero(dragSplitOffset_[mouseDragedSplitIndex_])) {
            format = MouseFormat::EAST;
        } else {
            format = MouseFormat::WEST_EAST;
        }
    } else {
        if (isOverParent_ && NearZero(dragSplitOffset_[mouseDragedSplitIndex_])) {
            format = MouseFormat::DEFAULT;
        } else if (isOverParent_) {
            format = MouseFormat::NORTH;
        } else if (NearZero(dragSplitOffset_[mouseDragedSplitIndex_])) {
            format = MouseFormat::SOUTH;
        } else {
            format = MouseFormat::NORTH_SOUTH;
        }
    }
    return format;
}

void LinearSplitPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);

    auto layoutProperty = GetLayoutProperty<LinearSplitLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    resizeable_ = layoutProperty->GetResizeable().value_or(false);
    childrenDragPos_.clear();

    InitPanEvent(gestureHub);

    auto inputHub = hub->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(inputHub);
    InitMouseEvent(inputHub);
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
    childrenDragPos_ = linearSplitLayoutAlgorithm->GetChildrenDragPos();
    childrenConstrains_ = linearSplitLayoutAlgorithm->GetChildrenConstrains();
    isOverParent_ = linearSplitLayoutAlgorithm->GetIsOverParent();
    return true;
}

} // namespace OHOS::Ace::NG