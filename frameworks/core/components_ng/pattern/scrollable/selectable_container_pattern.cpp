/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/scrollable/selectable_container_pattern.h"

#include <cmath>

#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/gestures/recognizers/pan_recognizer.h"
#include "core/components_ng/pattern/scrollable/selectable_item_pattern.h"
#include "core/event/pointer_event.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr Color SELECT_FILL_COLOR = Color(0x1A000000);
constexpr Color SELECT_STROKE_COLOR = Color(0x33FFFFFF);
constexpr int32_t TWO_FINGER_COUNT = 2;
constexpr Dimension TWO_FINGER_SELECT_MAX_DISTANCE = 210.0_vp;

bool IsTwoFingerSelectAllowed(const std::shared_ptr<BaseGestureEvent>& event)
{
    CHECK_NULL_RETURN(event, false);
    const auto& fingers = event->GetFingerList();
    if (static_cast<int32_t>(fingers.size()) != TWO_FINGER_COUNT) {
        return false;
    }
    auto iter = fingers.begin();
    auto& finger0 = *iter;
    auto& finger1 = *(++iter);
    auto dx = finger0.globalLocation_.GetX() - finger1.globalLocation_.GetX();
    auto dy = finger0.globalLocation_.GetY() - finger1.globalLocation_.GetY();
    auto distance = std::sqrt(dx * dx + dy * dy);
    if (GreatNotEqual(distance, TWO_FINGER_SELECT_MAX_DISTANCE.ConvertToPx())) {
        TAG_LOGI(AceLogTag::ACE_SCROLLABLE,
            "TwoFingerSelect reject: distance=%{public}.1f, max=%{public}.1f",
            distance, TWO_FINGER_SELECT_MAX_DISTANCE.ConvertToPx());
        return false;
    }
    auto rawPointerEvent = event->GetRawInputEvent();
    if (rawPointerEvent) {
        int64_t timeDiffMs = GetPointerDownTimeDiffMs(rawPointerEvent, finger0.fingerId_, finger1.fingerId_);
        const static int64_t twoFingerSelectMaxTimeDiffMs = 80;
        if (timeDiffMs >= 0 && timeDiffMs > twoFingerSelectMaxTimeDiffMs) {
            TAG_LOGI(AceLogTag::ACE_SCROLLABLE,
                "TwoFingerSelect reject: timeDiff=%{public}" PRId64 "ms, max=%{public}" PRId64 "ms", timeDiffMs,
                twoFingerSelectMaxTimeDiffMs);
            return false;
        }
    }
    TAG_LOGI(AceLogTag::ACE_SCROLLABLE, "TwoFingerSelect allowed: distance=%{public}.1f", distance);
    return true;
}

PointF ConvertGlobalToHostLocalPoint(
    SelectableContainerPattern* pattern, const std::shared_ptr<BaseGestureEvent>& event)
{
    CHECK_NULL_RETURN(pattern, PointF());
    CHECK_NULL_RETURN(event, PointF());
    const auto& fingers = event->GetFingerList();
    CHECK_NULL_RETURN(!fingers.empty(), PointF());
    auto host = pattern->GetHost();
    CHECK_NULL_RETURN(host, PointF());
    auto hostOffset = host->GetTransformRelativeOffset();
    auto globalLocation = fingers.front().globalLocation_;
    return PointF(static_cast<float>(globalLocation.GetX() - hostOffset.GetX()),
        static_cast<float>(globalLocation.GetY() - hostOffset.GetY()));
}
} // namespace

void SelectableContainerPattern::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    ScrollablePattern::ToJsonValue(json, filter);
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }

    // Add edit mode options as a parent node
    auto editModeOptionsJson = JsonUtil::Create(true);
    editModeOptionsJson->PutExtAttr("enableGatherSelectedItemsAnimation",
        editModeOptions_.enableGatherSelectedItemsAnimation ? "true" : "false", filter);
    editModeOptionsJson->PutExtAttr("useDefaultMultiSelectStyle",
        editModeOptions_.useDefaultMultiSelectStyle ? "true" : "false", filter);
    editModeOptionsJson->PutExtAttr("enableFingerMultiSelect",
        editModeOptions_.enableFingerMultiSelect ? "true" : "false", filter);
    json->PutExtAttr("editModeOptions", editModeOptionsJson, filter);
    json->PutExtAttr("enableEditMode", enableEditMode_ ? "true" : "false", filter);
}

void SelectableContainerPattern::UninitMouseEvent()
{
    if (!boxSelectPanEvent_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gestureHub = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->RemovePanEvent(boxSelectPanEvent_);
    boxSelectPanEvent_.Reset();
    ClearMultiSelect();
    ClearInvisibleItemsSelectedStatus();
    isMouseEventInit_ = false;
    if (!swipeSelectPanEvent_) {
        gestureHub->SetOnGestureJudgeNativeBegin(nullptr);
    }
}

void SelectableContainerPattern::InitMouseEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gestureHub = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    if (!boxSelectPanEvent_) {
        auto actionStartTask = [weak = WeakClaim(this)](const GestureEvent& info) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->HandleDragStart(info);
        };

        auto actionUpdateTask = [weak = WeakClaim(this)](const GestureEvent& info) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->HandleDragUpdate(info);
        };

        auto actionEndTask = [weak = WeakClaim(this)](const GestureEvent& info) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->HandleDragEnd();
        };
        GestureEventNoParameter actionCancelTask = [weak = WeakClaim(this)]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->HandleDragEnd();
        };
        boxSelectPanEvent_ = MakeRefPtr<PanEvent>(std::move(actionStartTask), std::move(actionUpdateTask),
            std::move(actionEndTask), std::move(actionCancelTask));
    }
    PanDirection panDirection = { .type = PanDirection::ALL };
    PanDistanceMap distanceMap = { { SourceTool::UNKNOWN, DEFAULT_PAN_DISTANCE.ConvertToPx() },
        { SourceTool::PEN, DEFAULT_PEN_PAN_DISTANCE.ConvertToPx() } };
    gestureHub->AddPanEvent(boxSelectPanEvent_, panDirection, 1, distanceMap);
    gestureHub->SetPanEventType(GestureTypeName::BOXSELECT);
    gestureHub->SetExcludedAxisForPanEvent(true);
    if (!swipeSelectPanEvent_) {
        gestureHub->SetOnGestureJudgeNativeBegin(
            [](const RefPtr<NG::GestureInfo>& gestureInfo,
                const std::shared_ptr<BaseGestureEvent>& event) -> GestureJudgeResult {
                if (gestureInfo->GetType() == GestureTypeName::BOXSELECT &&
                    gestureInfo->GetInputEventType() != InputEventType::MOUSE_BUTTON) {
                    return GestureJudgeResult::REJECT;
                }
                return GestureJudgeResult::CONTINUE;
            });
    }
    isMouseEventInit_ = true;
}

void SelectableContainerPattern::HandleDragStart(const GestureEvent& info)
{
    if (swipeSelectPanEvent_ && info.GetInputEventType() != InputEventType::MOUSE_BUTTON) {
        return;
    }
    TAG_LOGI(AceLogTag::ACE_SCROLLABLE, "Box select start");
    auto mouseOffsetX = static_cast<float>(info.GetRawGlobalLocation().GetX());
    auto mouseOffsetY = static_cast<float>(info.GetRawGlobalLocation().GetY());
    mouseOffsetX -= info.GetOffsetX();
    mouseOffsetY -= info.GetOffsetY();
    SuggestOpIncGroup(true);
    if (!IsItemSelected(static_cast<float>(info.GetGlobalLocation().GetX()) - info.GetOffsetX(),
        static_cast<float>(info.GetGlobalLocation().GetY()) - info.GetOffsetY())) {
        ClearMultiSelect();
        ClearInvisibleItemsSelectedStatus();
        mouseStartOffset_ = OffsetF(mouseOffsetX, mouseOffsetY);
        lastMouseStart_ = mouseStartOffset_;
        mouseEndOffset_ = OffsetF(mouseOffsetX, mouseOffsetY);
        mousePressOffset_ = OffsetF(mouseOffsetX, mouseOffsetY);
        totalOffsetOfMousePressed_ = mousePressOffset_.GetMainOffset(GetAxis()) + GetTotalOffset();
        canMultiSelect_ = true;
    }
    mousePressed_ = true;
}

void SelectableContainerPattern::HandleDragUpdate(const GestureEvent& info)
{
    if (swipeSelectPanEvent_ && info.GetInputEventType() != InputEventType::MOUSE_BUTTON) {
        return;
    }
    auto mouseOffsetX = static_cast<float>(info.GetRawGlobalLocation().GetX());
    auto mouseOffsetY = static_cast<float>(info.GetRawGlobalLocation().GetY());
    if (!mousePressed_ || !canMultiSelect_) {
        return;
    }
    if (info.GetInputEventType() != InputEventType::MOUSE_BUTTON) {
        HandleDragEnd();
        return;
    }
    lastMouseMove_ = info;
    auto delta = OffsetF(mouseOffsetX, mouseOffsetY) - mousePressOffset_;
    if (Offset(delta.GetX(), delta.GetY()).GetDistance() > DEFAULT_PAN_DISTANCE.ConvertToPx()) {
        mouseEndOffset_ = OffsetF(mouseOffsetX, mouseOffsetY);
        // avoid large select zone
        LimitMouseEndOffset();
        auto selectedZone = ComputeSelectedZone(mouseStartOffset_, mouseEndOffset_);
        MultiSelectWithoutKeyboard(selectedZone);
        HandleInvisibleItemsSelectedStatus(selectedZone);
    }
    SelectWithScroll();
}

void SelectableContainerPattern::HandleDragEnd()
{
    TAG_LOGI(AceLogTag::ACE_SCROLLABLE, "Box select end");
    mouseStartOffset_.Reset();
    lastMouseStart_.Reset();
    mouseEndOffset_.Reset();
    mousePressed_ = false;
    canMultiSelect_ = false;
    ClearSelectedZone();
    itemToBeSelected_.clear();
    lastMouseMove_.SetLocalLocation(Offset::Zero());
}

void SelectableContainerPattern::ClearInvisibleItemsSelectedStatus()
{
    for (auto& item : itemToBeSelected_) {
        item.second.FireSelectChangeEvent(false);
    }
    itemToBeSelected_.clear();
}

void SelectableContainerPattern::HandleInvisibleItemsSelectedStatus(const RectF& selectedZone)
{
    auto newRect = selectedZone;
    auto startMainOffset = mouseStartOffset_.GetMainOffset(GetAxis());
    auto endMainOffset = mouseEndOffset_.GetMainOffset(GetAxis());
    SelectDirection oldDirection = selectDirection_;
    if (LessNotEqual(startMainOffset, endMainOffset)) {
        selectDirection_ = SELECT_DOWN;
        if (GetAxis() == Axis::VERTICAL) {
            newRect.SetOffset(OffsetF(selectedZone.Left(), totalOffsetOfMousePressed_));
        } else {
            newRect.SetOffset(OffsetF(totalOffsetOfMousePressed_, selectedZone.Top()));
        }
    } else {
        selectDirection_ = SELECT_UP;
        if (GetAxis() == Axis::VERTICAL) {
            newRect.SetOffset(
                OffsetF(selectedZone.Left(), totalOffsetOfMousePressed_ - (startMainOffset - endMainOffset)));
        } else {
            newRect.SetOffset(
                OffsetF(totalOffsetOfMousePressed_ - (startMainOffset - endMainOffset), selectedZone.Top()));
        }
    }
    oldDirection = oldDirection == SELECT_NONE ? selectDirection_ : oldDirection;

    for (auto& item : itemToBeSelected_) {
        item.second.FireSelectChangeEvent(newRect.IsIntersectWith(item.second.rect));
    }

    if (oldDirection != selectDirection_) {
        itemToBeSelected_.clear();
    }
}

void SelectableContainerPattern::SelectWithScroll()
{
    if (!IsScrollable()) {
        return;
    }
    auto offset = GetOutOfScrollableOffset();
    if (NearZero(offset)) {
        return;
    }

    if (AnimateRunning()) {
        return;
    }

    StopActiveScrollAnimation();

    auto animator = GetOrCreateAnimator();
    CHECK_NULL_VOID(animator);

    if (!selectMotion_) {
        selectMotion_ = AceType::MakeRefPtr<SelectMotion>(offset, [weak = WeakClaim(this)]() -> bool {
            auto pattern = weak.Upgrade();
            CHECK_NULL_RETURN(pattern, true);
            return pattern->ShouldSelectScrollBeStopped();
        });
        selectMotion_->AddListener([weakScroll = AceType::WeakClaim(this)](double offset) {
            auto pattern = weakScroll.Upgrade();
            CHECK_NULL_VOID(pattern);
            offset = pattern->GetOffsetWithLimit(offset);
            pattern->UpdateCurrentOffset(offset, SCROLL_FROM_AXIS);
            pattern->UpdateMouseStart(offset);
        });
    } else {
        selectMotion_->Reset(offset);
    }

    animator->PlayMotion(selectMotion_);

    FireOnScrollStart();
}

void SelectableContainerPattern::ClearSelectedZone()
{
    DrawSelectedZone(RectF());
    selectScrollOffset_ = 0.0f;
}

RectF SelectableContainerPattern::ComputeSelectedZone(const OffsetF& startOffset, const OffsetF& endOffset)
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

void SelectableContainerPattern::DrawSelectedZone(const RectF& selectedZone)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hostContext = host->GetRenderContext();
    CHECK_NULL_VOID(hostContext);
    hostContext->UpdateMouseSelectWithRect(selectedZone, SELECT_FILL_COLOR, SELECT_STROKE_COLOR);
}

void SelectableContainerPattern::MarkSelectedItems()
{
    if (multiSelectable_ && mousePressed_) {
        UpdateMouseStartOffset();
        auto selectedZone = ComputeSelectedZone(mouseStartOffset_, mouseEndOffset_);
        if (!selectedZone.IsEmpty()) {
            MultiSelectWithoutKeyboard(selectedZone);
            HandleInvisibleItemsSelectedStatus(selectedZone);
        }
    }
}

bool SelectableContainerPattern::ShouldSelectScrollBeStopped()
{
    if (!mousePressed_) {
        return true;
    }
    auto offset = GetOutOfScrollableOffset();
    if (NearZero(offset)) {
        return true;
    }

    if (selectMotion_) {
        selectMotion_->Reset(offset);
    }
    return false;
};

void SelectableContainerPattern::UpdateMouseStart(float offset)
{
    selectScrollOffset_ += offset;
}

float SelectableContainerPattern::GetOutOfScrollableOffset() const
{
    auto offset = 0.0f;
    auto mouseMainOffset = static_cast<float>(GetAxis() == Axis::VERTICAL ? lastMouseMove_.GetLocalLocation().GetY()
                                                                          : lastMouseMove_.GetLocalLocation().GetX());
    auto hostSize = GetViewSizeMinusPadding();
    auto mainTop = 0.0f;
    auto mainBottom = hostSize.MainSize(GetAxis());
    if (GreatOrEqual(mouseMainOffset, mainTop) && LessOrEqual(mouseMainOffset, mainBottom)) {
        return offset;
    }
    if (GreatNotEqual(mouseMainOffset, mainBottom)) {
        if (IsAtBottom()) {
            return offset;
        }
        offset = mainBottom - mouseMainOffset;
    }
    if (LessNotEqual(mouseMainOffset, mainTop)) {
        if (IsAtTop()) {
            return offset;
        }
        offset = mainTop - mouseMainOffset;
    }
    return offset;
}

float SelectableContainerPattern::GetOffsetWithLimit(float offset) const
{
    if (Positive(offset)) {
        float totalOffset = GetTotalOffset();
        return std::min(totalOffset, offset);
    } else if (Negative(offset)) {
        auto frameNode = GetHost();
        CHECK_NULL_RETURN(frameNode, 0.0f);
        auto hostSize = frameNode->GetGeometryNode()->GetFrameSize();
        float remainHeight = GetTotalHeight() - GetTotalOffset() - hostSize.MainSize(GetAxis());
        return std::max(offset, -remainHeight);
    }
    return 0.0f;
}

void SelectableContainerPattern::LimitMouseEndOffset()
{
    float limitedMainOffset = -1.0f;
    float limitedCrossOffset = -1.0f;
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    auto hostSize = frameNode->GetGeometryNode()->GetFrameSize();
    auto mainSize = hostSize.MainSize(GetAxis());
    auto crossSize = hostSize.CrossSize(GetAxis());
    auto mainOffset = mouseEndOffset_.GetMainOffset(GetAxis());
    auto crossOffset = mouseEndOffset_.GetCrossOffset(GetAxis());
    if (LessNotEqual(mainOffset, 0.0f)) {
        limitedMainOffset = 0.0f;
    }
    if (GreatNotEqual(mainOffset, mainSize)) {
        limitedMainOffset = mainSize;
    }
    if (LessNotEqual(crossOffset, 0.0f)) {
        limitedCrossOffset = 0.0f;
    }
    if (GreatNotEqual(crossOffset, crossSize)) {
        limitedCrossOffset = crossSize;
    }

    if (GetAxis() == Axis::VERTICAL) {
        mouseEndOffset_.SetX(LessNotEqual(limitedCrossOffset, 0.0f) ? mouseEndOffset_.GetX() : limitedCrossOffset);
        mouseEndOffset_.SetY(LessNotEqual(limitedMainOffset, 0.0f) ? mouseEndOffset_.GetY() : limitedMainOffset);
    } else {
        mouseEndOffset_.SetX(LessNotEqual(limitedMainOffset, 0.0f) ? mouseEndOffset_.GetX() : limitedMainOffset);
        mouseEndOffset_.SetY(LessNotEqual(limitedCrossOffset, 0.0f) ? mouseEndOffset_.GetY() : limitedCrossOffset);
    }
}

void SelectableContainerPattern::UpdateMouseStartOffset()
{
    auto context = GetContext();
    CHECK_NULL_VOID(context);
    uint64_t currentVsync = context->GetVsyncTime();
    if (currentVsync > GetLastVsyncTime()) {
        if (GetAxis() == Axis::VERTICAL) {
            mouseStartOffset_.AddY(selectScrollOffset_);
        } else {
            mouseStartOffset_.AddX(selectScrollOffset_);
        }
        selectScrollOffset_ = 0.0f;
    }
    UpdateSelectScrollVsync(currentVsync);
}

void SelectableContainerPattern::SetEnableEditMode(bool enable)
{
    bool changed = (enableEditMode_ != enable);
    enableEditMode_ = enable;
    if (changed) {
        editModeChanged_ = true;
        FireEnableEditModeChangeEvent(enable);
    }
}

bool SelectableContainerPattern::GetEnableEditMode() const
{
    return enableEditMode_;
}

RefPtr<FrameNode> SelectableContainerPattern::GetSelectableItemAtIndex(int32_t index) const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto node = host->GetChildByIndex(index);
    return AceType::DynamicCast<FrameNode>(node);
}

void SelectableContainerPattern::TryEnterEditModeForSwipeSelect()
{
    if (GetEnableEditMode()) {
        return;
    }
    enableEditMode_ = true;
    if (IsDefaultMultiSelectStyleEnabled()) {
        ApplyEditModeToVisibleItems();
    }
    FireEnableEditModeChangeEvent(true);
}

GestureJudgeResult SelectableContainerPattern::JudgeSwipeSelectGesture(
    const RefPtr<NG::GestureInfo>& gestureInfo, const std::shared_ptr<BaseGestureEvent>& event)
{
    CHECK_NULL_RETURN(gestureInfo, GestureJudgeResult::CONTINUE);
    if (gestureInfo->GetType() == GestureTypeName::BOXSELECT &&
        gestureInfo->GetInputEventType() == InputEventType::MOUSE_BUTTON && isMouseEventInit_) {
        return GestureJudgeResult::CONTINUE;
    }
    if (gestureInfo->GetRecognizerType() == GestureTypeName::PAN_GESTURE &&
        gestureInfo->GetType() != GestureTypeName::BOXSELECT &&
        gestureInfo->GetInputEventType() == InputEventType::TOUCH_SCREEN) {
        if (!GetEnableEditMode()) {
            return editModeOptions_.enableFingerMultiSelect && IsTwoFingerSelectAllowed(event) ?
                GestureJudgeResult::REJECT: GestureJudgeResult::CONTINUE;
        }
        if (NeedJudgeWithHotZone()) {
            return IsInEditModeHotZone(ConvertGlobalToHostLocalPoint(this, event)) ?
                GestureJudgeResult::REJECT : GestureJudgeResult::CONTINUE;
        }
    }
    if (gestureInfo->GetType() == GestureTypeName::BOXSELECT &&
        gestureInfo->GetInputEventType() == InputEventType::TOUCH_SCREEN) {
        if (!GetEnableEditMode()) {
            return IsTwoFingerSelectAllowed(event) ? GestureJudgeResult::CONTINUE : GestureJudgeResult::REJECT;
        }
        if (NeedJudgeWithHotZone()) {
            return IsInEditModeHotZone(ConvertGlobalToHostLocalPoint(this, event)) ?
                GestureJudgeResult::CONTINUE : GestureJudgeResult::REJECT;
        }
        return GestureJudgeResult::CONTINUE;
    }
    return GestureJudgeResult::CONTINUE;
}

void SelectableContainerPattern::InitSwipeSelectEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gestureHub = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    if (!swipeSelectPanEvent_) {
        auto actionStartTask = [weak = WeakClaim(this)](const GestureEvent& info) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->TryEnterEditModeForSwipeSelect();
            pattern->HandleSwipeSelectStart(info);
        };

        auto actionUpdateTask = [weak = WeakClaim(this)](const GestureEvent& info) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->HandleSwipeSelectUpdate(info);
        };

        auto actionEndTask = [weak = WeakClaim(this)](const GestureEvent& info) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->HandleSwipeSelectEnd();
        };
        GestureEventNoParameter actionCancelTask = [weak = WeakClaim(this)]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->HandleSwipeSelectCancel();
        };
        swipeSelectPanEvent_ = MakeRefPtr<PanEvent>(std::move(actionStartTask), std::move(actionUpdateTask),
            std::move(actionEndTask), std::move(actionCancelTask));
    }
    PanDirection panDirection = { .type = PanDirection::ALL };
    PanDistanceMap distanceMap = { { SourceTool::UNKNOWN, DEFAULT_PAN_DISTANCE.ConvertToPx() },
        { SourceTool::PEN, DEFAULT_PEN_PAN_DISTANCE.ConvertToPx() } };
    gestureHub->AddPanEvent(swipeSelectPanEvent_, panDirection, 1, distanceMap);
    gestureHub->SetPanEventType(GestureTypeName::BOXSELECT);
    gestureHub->SetPanEventTag("SWIPESELECT");
    gestureHub->SetExcludedAxisForPanEvent(true);
    gestureHub->SetOnGestureJudgeNativeBegin([weak = WeakClaim(this)](const RefPtr<NG::GestureInfo>& gestureInfo,
                                             const std::shared_ptr<BaseGestureEvent>& event) -> GestureJudgeResult {
        auto pattern = weak.Upgrade();
        CHECK_NULL_RETURN(pattern, GestureJudgeResult::CONTINUE);
        return pattern->JudgeSwipeSelectGesture(gestureInfo, event);
    });
}

void SelectableContainerPattern::UninitSwipeSelectEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gestureHub = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    if (swipeSelectPanEvent_) {
        gestureHub->RemovePanEvent(swipeSelectPanEvent_);
        swipeSelectPanEvent_.Reset();
    }
    if (isMouseEventInit_) {
        gestureHub->SetOnGestureJudgeNativeBegin(
            [](const RefPtr<NG::GestureInfo>& gestureInfo,
                const std::shared_ptr<BaseGestureEvent>& event) -> GestureJudgeResult {
                if (gestureInfo->GetType() == GestureTypeName::BOXSELECT &&
                    gestureInfo->GetInputEventType() != InputEventType::MOUSE_BUTTON) {
                    return GestureJudgeResult::REJECT;
                }
                return GestureJudgeResult::CONTINUE;
            });
    } else {
        gestureHub->SetOnGestureJudgeNativeBegin(nullptr);
    }
}

bool SelectableContainerPattern::ShouldEnableTwoFingerSelect() const
{
    return HasEnableEditModeBinding() && editModeOptions_.enableFingerMultiSelect && !enableEditMode_;
}

void SelectableContainerPattern::HandleSwipeSelectStart(const GestureEvent& info)
{
    if (multiSelectable_ && info.GetInputEventType() == InputEventType::MOUSE_BUTTON) {
        return;
    }
    TAG_LOGI(AceLogTag::ACE_SCROLLABLE, "Swipe select start");
    auto localPoint = info.GetLocalLocation();
    swipeStartStateKey_ = GetSwipeSelectStateKeyAtPosition(localPoint.GetX(), localPoint.GetY());
    swipeCurrentStateKey_ = swipeStartStateKey_;
    if (!swipeStartStateKey_.IsValid()) {
        swipeSelectState_ = SwipeSelectState::INACTIVE;
        return;
    }
    swipeOriginalStates_.clear();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto frameNode = GetSelectableItemAtStateKey(swipeStartStateKey_);
    CHECK_NULL_VOID(frameNode);
    auto itemPattern = frameNode->GetPattern<SelectableItemPattern>();
    if (!itemPattern || !itemPattern->Selectable()) {
        swipeSelectState_ = SwipeSelectState::INACTIVE;
        return;
    }
    swipeSelectState_ = itemPattern->IsSelected() ? SwipeSelectState::DESELECTING : SwipeSelectState::SELECTING;
    swipeOriginalStates_[swipeStartStateKey_] = itemPattern->IsSelected();
    MarkSwipeItemSelectedByStateKey(swipeStartStateKey_, swipeSelectState_ == SwipeSelectState::SELECTING);
}

void SelectableContainerPattern::HandleSwipeSelectUpdate(const GestureEvent& info)
{
    if (multiSelectable_ && info.GetInputEventType() == InputEventType::MOUSE_BUTTON) {
        return;
    }
    if (swipeSelectState_ == SwipeSelectState::INACTIVE || !swipeStartStateKey_.IsValid()) {
        return;
    }

    auto localPoint = info.GetLocalLocation();
    auto globalPoint = info.GetGlobalLocation();
    const auto& fingers = info.GetFingerList();
    if (fingers.size() >= TWO_FINGER_COUNT) {
        auto iter = fingers.begin();
        auto& f0 = *iter;
        auto& f1 = *(++iter);
        auto midLocalX = (f0.localLocation_.GetX() + f1.localLocation_.GetX()) / 2.0;
        auto midLocalY = (f0.localLocation_.GetY() + f1.localLocation_.GetY()) / 2.0;
        auto midGlobalX = (f0.globalLocation_.GetX() + f1.globalLocation_.GetX()) / 2.0;
        auto midGlobalY = (f0.globalLocation_.GetY() + f1.globalLocation_.GetY()) / 2.0;
        localPoint = Offset(midLocalX, midLocalY);
        globalPoint = Offset(midGlobalX, midGlobalY);
    }

    SwipeSelectAutoScroll(PointF(static_cast<float>(globalPoint.GetX()), static_cast<float>(globalPoint.GetY())));

    auto host = GetHost();
    if (host) {
        auto width = static_cast<float>(host->GetGeometryNode()->GetFrameRect().Width());
        lastSwipeSelectLocalX_ = std::clamp(static_cast<float>(localPoint.GetX()), 0.0f, width);
    }
    auto newStateKey = GetSwipeSelectStateKeyNearPosition(
        static_cast<float>(localPoint.GetX()), static_cast<float>(localPoint.GetY()));
    if (!newStateKey.IsValid() || newStateKey == swipeCurrentStateKey_) {
        return;
    }
    swipeCurrentStateKey_ = newStateKey;
    auto stateKey = swipeCurrentStateKey_;
    if (swipeOriginalStates_.find(stateKey) == swipeOriginalStates_.end()) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto frameNode = GetSelectableItemAtStateKey(stateKey);
        if (frameNode) {
            auto itemPattern = frameNode->GetPattern<SelectableItemPattern>();
            if (itemPattern && !itemPattern->Selectable()) {
                return;
            }
            swipeOriginalStates_[stateKey] = itemPattern ? itemPattern->IsSelected() : false;
        }
    }
    UpdateSwipeSelection();
}

void SelectableContainerPattern::HandleSwipeSelectEnd()
{
    TAG_LOGI(AceLogTag::ACE_SCROLLABLE, "Swipe select end");
    StopSwipeSelectAutoScroll();
    swipeSelectState_ = SwipeSelectState::INACTIVE;
    swipeOriginalStates_.clear();
    swipeStartStateKey_ = {};
    swipeCurrentStateKey_ = {};
    swipePrevRangeStartKey_ = {};
    swipePrevRangeEndKey_ = {};
    lastSwipeSelectLocalX_ = -1.0f;
}

void SelectableContainerPattern::HandleSwipeSelectCancel()
{
    TAG_LOGI(AceLogTag::ACE_SCROLLABLE, "Swipe select cancel");
    StopSwipeSelectAutoScroll();
    for (const auto& [stateKey, wasSelected] : swipeOriginalStates_) {
        MarkSwipeItemSelectedByStateKey(stateKey, wasSelected);
    }
    swipeSelectState_ = SwipeSelectState::INACTIVE;
    swipeOriginalStates_.clear();
    swipeStartStateKey_ = {};
    swipeCurrentStateKey_ = {};
    swipePrevRangeStartKey_ = {};
    swipePrevRangeEndKey_ = {};
    lastSwipeSelectLocalX_ = -1.0f;
}

void SelectableContainerPattern::RecordSwipeOriginalStatesInRange(
    const std::vector<SwipeSelectStateKey>& stateKeysInRange)
{
    for (const auto& stateKey : stateKeysInRange) {
        if (swipeOriginalStates_.find(stateKey) == swipeOriginalStates_.end()) {
            auto frameNode = GetSelectableItemAtStateKey(stateKey);
            if (!frameNode) {
                continue;
            }
            auto itemPattern = frameNode->GetPattern<SelectableItemPattern>();
            if (itemPattern && !itemPattern->Selectable()) {
                continue;
            }
            swipeOriginalStates_[stateKey] = itemPattern ? itemPattern->IsSelected() : false;
        }
    }
}

void SelectableContainerPattern::ApplySwipeSelectionForFirstRange(
    const std::vector<SwipeSelectStateKey>& stateKeysInRange, bool isSelected)
{
    for (const auto& stateKey : stateKeysInRange) {
        if (swipeOriginalStates_.find(stateKey) != swipeOriginalStates_.end()) {
            MarkSwipeItemSelectedByStateKey(stateKey, isSelected);
        }
    }
}

void SelectableContainerPattern::ApplySwipeSelectionForDeltaRange(
    const SwipeSelectStateKey& rangeStartKey, const SwipeSelectStateKey& rangeEndKey, bool isSelected)
{
    std::vector<SwipeSelectStateKey> newKeysInRange;
    BuildSwipeSelectStateKeysInRange(swipeStartStateKey_, swipeCurrentStateKey_, newKeysInRange);
    for (const auto& stateKey : newKeysInRange) {
        if (swipeOriginalStates_.find(stateKey) != swipeOriginalStates_.end() &&
            (stateKey < swipePrevRangeStartKey_ || swipePrevRangeEndKey_ < stateKey)) {
            MarkSwipeItemSelectedByStateKey(stateKey, isSelected);
        }
    }

    for (const auto& [stateKey, wasSelected] : swipeOriginalStates_) {
        if ((stateKey < rangeStartKey || rangeEndKey < stateKey) &&
            !(stateKey < swipePrevRangeStartKey_ || swipePrevRangeEndKey_ < stateKey)) {
            MarkSwipeItemSelectedByStateKey(stateKey, wasSelected);
        }
    }
}

void SelectableContainerPattern::UpdateSwipeSelection()
{
    auto rangeStartKey = swipeCurrentStateKey_ < swipeStartStateKey_ ? swipeCurrentStateKey_ : swipeStartStateKey_;
    auto rangeEndKey = swipeStartStateKey_ < swipeCurrentStateKey_ ? swipeCurrentStateKey_ : swipeStartStateKey_;
    if (swipePrevRangeStartKey_.IsValid() && swipePrevRangeEndKey_.IsValid() &&
        rangeStartKey == swipePrevRangeStartKey_ && rangeEndKey == swipePrevRangeEndKey_) {
        return;
    }
    bool isSelected = (swipeSelectState_ == SwipeSelectState::SELECTING);

    std::vector<SwipeSelectStateKey> stateKeysInRange;
    BuildSwipeSelectStateKeysInRange(swipeStartStateKey_, swipeCurrentStateKey_, stateKeysInRange);
    RecordSwipeOriginalStatesInRange(stateKeysInRange);

    if (!swipePrevRangeStartKey_.IsValid() || !swipePrevRangeEndKey_.IsValid()) {
        ApplySwipeSelectionForFirstRange(stateKeysInRange, isSelected);
    } else {
        ApplySwipeSelectionForDeltaRange(rangeStartKey, rangeEndKey, isSelected);
    }

    swipePrevRangeStartKey_ = rangeStartKey;
    swipePrevRangeEndKey_ = rangeEndKey;
}

void SelectableContainerPattern::SwipeSelectAutoScroll(const PointF& globalPoint)
{
    float offsetPct = IsInHotZone(globalPoint, true);
    if (NearZero(offsetPct)) {
        StopSwipeSelectAutoScroll();
        return;
    }
    if (!GetScrollable() || !IsScrollable()) {
        return;
    }
    float capturedOffsetPct = offsetPct;
    SetHotZoneScrollCallback([weak = WeakClaim(this), capturedOffsetPct]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (pattern->swipeSelectState_ == SwipeSelectState::INACTIVE) {
            return;
        }
        pattern->UpdateSwipeSelectStateKeyForAutoScroll(capturedOffsetPct);
        pattern->UpdateSwipeSelection();
    });
    HotZoneScroll(offsetPct);
}

void SelectableContainerPattern::StopSwipeSelectAutoScroll()
{
    StopHotzoneScroll();
    SetHotZoneScrollCallback(nullptr);
}

void SelectableContainerPattern::UpdateSwipeSelectStateKeyForAutoScroll(float offsetPct)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto frameRect = geometryNode->GetFrameRect();
    float edgeX = GreatOrEqual(lastSwipeSelectLocalX_, 0.0f)
        ? lastSwipeSelectLocalX_ : frameRect.Width() / 2.0f;
    float edgeY = GreatNotEqual(offsetPct, 0.0f)
        ? SWIPE_SELECT_EDGE_MARGIN_PX : frameRect.Height() - SWIPE_SELECT_EDGE_MARGIN_PX;
    auto newStateKey = GetSwipeSelectStateKeyNearPosition(edgeX, edgeY);
    if (!newStateKey.IsValid() || newStateKey == swipeCurrentStateKey_) {
        return;
    }
    swipeCurrentStateKey_ = newStateKey;
    if (swipeOriginalStates_.find(newStateKey) == swipeOriginalStates_.end()) {
        auto frameNode = GetSelectableItemAtStateKey(newStateKey);
        if (frameNode) {
            auto itemPattern = frameNode->GetPattern<SelectableItemPattern>();
            if (itemPattern && !itemPattern->Selectable()) {
                return;
            }
            swipeOriginalStates_[newStateKey] = itemPattern ? itemPattern->IsSelected() : false;
        }
    }
}

void SelectableContainerPattern::ApplyEditModeToVisibleItems()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    std::list<RefPtr<FrameNode>> children;
    host->GenerateOneDepthAllFrame(children);
    for (const auto& child : children) {
        auto itemPattern = child->GetPattern<SelectableItemPattern>();
        if (itemPattern) {
            itemPattern->SetEditModeEnabled(true);
        }
    }
    ApplyEditModeToCachedItems(true);
}

void SelectableContainerPattern::RemoveEditModeFromItems()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    std::list<RefPtr<FrameNode>> children;
    host->GenerateOneDepthAllFrame(children);
    for (const auto& child : children) {
        auto itemPattern = child->GetPattern<SelectableItemPattern>();
        if (itemPattern) {
            itemPattern->SetEditModeEnabled(false);
        }
    }
    ApplyEditModeToCachedItems(false);
}

} // namespace OHOS::Ace::NG
