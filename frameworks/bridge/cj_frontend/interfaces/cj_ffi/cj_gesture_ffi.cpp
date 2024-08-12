/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_gesture_ffi.h"

#include "bridge/cj_frontend/cppview/gesture.h"
#include "cj_lambda.h"
#include "frameworks/core/components_ng/base/view_stack_processor.h"
#include "frameworks/core/components_ng/gestures/long_press_gesture.h"
#include "frameworks/core/components_ng/gestures/pinch_gesture.h"
#include "frameworks/core/components_ng/gestures/rotation_gesture.h"
#include "frameworks/core/components_ng/gestures/swipe_gesture.h"

using namespace OHOS::FFI;
using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;

namespace {
constexpr int32_t DEFAULT_TAP_FINGER = 1;
constexpr int32_t MAX_TAP_FINGER = 10;
constexpr int32_t DEFAULT_TAP_COUNT = 1;
constexpr int32_t DEFAULT_LONG_PRESS_FINGER = 1;
constexpr int32_t MAX_LONG_PRESS_FINGER = 10;
constexpr int32_t DEFAULT_PINCH_FINGER = 2;
constexpr int32_t MAX_PINCH_FINGER = 5;
constexpr double DEFAULT_PINCH_DISTANCE = 3.0;
constexpr int32_t DEFAULT_ROTATION_FINGER = 2;
constexpr int32_t MAX_ROTATION_FINGER = 5;
constexpr double DEFAULT_ROTATION_ANGLE = 1.0;
constexpr int32_t MAX_PAN_FINGER = 10;
constexpr int32_t MAX_SLIDE_FINGER = 10;

const std::vector<GesturePriority> GESTURE_PRIORITY = { GesturePriority::Low, GesturePriority::High,
    GesturePriority::Parallel };

const std::vector<GestureMask> GESTURE_MASK = { GestureMask::Normal, GestureMask::IgnoreInternal };

const std::vector<GestureMode> GROUP_GESTURE_MODE = { GestureMode::Sequence, GestureMode::Parallel,
    GestureMode::Exclusive };

enum class GestureEventType { ACTION, START, UPDATE, END, CANCEL };

std::function<void(const GestureEvent& event)> FormatGestureEvenFunction(void (*callback)(CJGestureEvent info))
{
    std::function<void(const GestureEvent& event)> result = [ffiOnAction = CJLambda::Create(callback)](
                                                                const GestureEvent& event) -> void {
        CJGestureEvent ffiGestureEvent {};
        CJEventTarget ffiEventTarget {};
        CJArea ffiArea {};
        CJPosition ffiPosition {};
        CJPosition ffiGlobalPosition {};

        const auto& eventTarget = event.GetTarget();
        ffiArea.width = eventTarget.area.GetWidth().ConvertToVp();
        ffiArea.height = eventTarget.area.GetHeight().ConvertToVp();
        const auto& localOffset = eventTarget.area.GetOffset();
        const auto& origin = eventTarget.origin;
        ffiPosition.x = localOffset.GetX().ConvertToVp();
        ffiPosition.y = localOffset.GetY().ConvertToVp();
        ffiGlobalPosition.x = origin.GetX().ConvertToVp() + localOffset.GetX().ConvertToVp();
        ffiGlobalPosition.y = origin.GetX().ConvertToVp() + localOffset.GetY().ConvertToVp();

        ffiArea.globalPosition = &ffiGlobalPosition;
        ffiArea.position = &ffiPosition;

        ffiEventTarget.area = &ffiArea;

        auto& fingerList = event.GetFingerList();
        ffiGestureEvent.fingerListSize = static_cast<int32_t>(fingerList.size());
        ffiGestureEvent.fingerList = new CJFingerInfo[fingerList.size()];
        TransformNativeCJFingerInfo(ffiGestureEvent.fingerList, fingerList);

        ffiGestureEvent.target = &ffiEventTarget;
        ffiGestureEvent.timestamp = event.GetTimeStamp().time_since_epoch().count();
        ffiGestureEvent.repeat = event.GetRepeat();
        ffiGestureEvent.source = static_cast<int32_t>(event.GetSourceDevice());
        ffiGestureEvent.offsetX = event.GetOffsetX();
        ffiGestureEvent.offsetY = event.GetOffsetY();
        ffiGestureEvent.scale = event.GetScale();
        ffiGestureEvent.pinchCenterX = event.GetPinchCenter().GetX();
        ffiGestureEvent.pinchCenterY = event.GetPinchCenter().GetY();
        ffiGestureEvent.angle = event.GetAngle();
        ffiGestureEvent.speed = event.GetSpeed();

        ffiOnAction(ffiGestureEvent);
    };
    return result;
}

std::function<void(const GestureEvent& event)> FormatGestureEvenFunction(void (*callback)())
{
    std::function<void(const GestureEvent& event)> result = [ffiOnAction = CJLambda::Create(callback)](
                                                                const GestureEvent& event) -> void { ffiOnAction(); };
    return result;
}

void HandlerOnGestureEvent(
    const GestureEventType& action, const std::function<void(const GestureEvent& event)>& callback)
{
    RefPtr<GestureProcessor> gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto gesture = gestureProcessor->TopGestureNG();
    if (!gesture) {
        LOGE("top gesture is illegal");
        return;
    }

    if (action == GestureEventType::CANCEL) {
        auto onActionCancelFunc = [callback = std::move(callback)]() {
            auto info = GestureEvent();
            callback(info);
        };
        gesture->SetOnActionCancelId(onActionCancelFunc);
        return;
    }

    auto onActionFunc = [callback = std::move(callback)](GestureEvent& info) {
        callback(info);
    };

    switch (action) {
        case GestureEventType::ACTION:
            gesture->SetOnActionId(onActionFunc);
            break;
        case GestureEventType::START:
            gesture->SetOnActionStartId(onActionFunc);
            break;
        case GestureEventType::UPDATE:
            gesture->SetOnActionUpdateId(onActionFunc);
            break;
        case GestureEventType::END:
            gesture->SetOnActionEndId(onActionFunc);
            break;
        default:
            LOGW("Gesture: Unknown gesture action %{public}d", action);
            break;
    }
}

} // namespace

extern "C" {
void FfiOHOSAceFrameworkGestureCreate(int32_t priority, int32_t mask)
{
    if (!Utils::CheckParamsValid(priority, GESTURE_PRIORITY.size())) {
        LOGE("invalid value for gesturePriority");
        return;
    }
    if (!Utils::CheckParamsValid(mask, GESTURE_MASK.size())) {
        LOGE("invalid value for gestureMask");
        return;
    }

    RefPtr<GestureProcessor> gestureProcessor =
            NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    gestureProcessor->SetPriority(GESTURE_PRIORITY[priority]);
    gestureProcessor->SetGestureMask(GESTURE_MASK[mask]);
}

void FfiOHOSAceFrameworkGestureOnAction(void (*callback)(CJGestureEvent info))
{
    HandlerOnGestureEvent(GestureEventType::ACTION, FormatGestureEvenFunction(callback));
}

void FfiOHOSAceFrameworkGestureOnActionStart(void (*callback)(CJGestureEvent info))
{
    HandlerOnGestureEvent(GestureEventType::START, FormatGestureEvenFunction(callback));
}

void FfiOHOSAceFrameworkGestureOnActionUpdate(void (*callback)(CJGestureEvent info))
{
    HandlerOnGestureEvent(GestureEventType::UPDATE, FormatGestureEvenFunction(callback));
}

void FfiOHOSAceFrameworkGestureOnActionEnd(void (*callback)(CJGestureEvent info))
{
    HandlerOnGestureEvent(GestureEventType::END, FormatGestureEvenFunction(callback));
}

void FfiOHOSAceFrameworkGestureOnActionCancel(void (*callback)())
{
    HandlerOnGestureEvent(GestureEventType::CANCEL, FormatGestureEvenFunction(callback));
}

void FfiOHOSAceFrameworkGestureFinish()
{
    RefPtr<GestureProcessor> gestureProcessor =
        NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    NG::ViewStackProcessor::GetInstance()->ResetGestureProcessor();

    auto gesture = gestureProcessor->FinishGestureNG();
    if (!gesture) {
        LOGE("gesture is not exist when component finish");
        return;
    }
    gesture->SetGestureMask(gestureProcessor->GetGestureMask());
    gesture->SetPriority(gestureProcessor->GetPriority());
    auto gestureEventHub = NG::ViewStackProcessor::GetInstance()->GetMainFrameNodeGestureEventHub();
    if (gestureEventHub) {
        gestureEventHub->AddGesture(gesture);
    }
}

void FfiOHOSAceFrameworkGesturePop()
{
    RefPtr<GestureProcessor> gestureProcessor =
        NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    gestureProcessor->PopGestureNG();
}

// tapGesture
void FfiOHOSAceFrameworkTapGestureCreate(int32_t count, int32_t fingers)
{
    RefPtr<GestureProcessor> gestureProcessor =
        NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();

    int32_t countNum = Utils::CheckMin(DEFAULT_TAP_COUNT, DEFAULT_TAP_COUNT, count);
    int32_t fingersNum = Utils::CheckRange(DEFAULT_TAP_FINGER, MAX_TAP_FINGER, DEFAULT_TAP_FINGER, fingers);

    auto gesture = AceType::MakeRefPtr<NG::TapGesture>(countNum, fingersNum);
    gestureProcessor->PushGestureNG(gesture);
}

// LongPressGesture
void FfiOHOSAceFrameworkLongPressGestureCreate(int32_t fingers, bool repeat, int32_t duration)
{
    RefPtr<GestureProcessor> gestureProcessor =
        NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();

    int32_t fingersNum =
        Utils::CheckRange(DEFAULT_LONG_PRESS_FINGER, MAX_LONG_PRESS_FINGER, DEFAULT_LONG_PRESS_FINGER, fingers);
    int32_t durationNum = Utils::CheckMin(0, DEFAULT_LONG_PRESS_DURATION, duration);

    auto gesture = AceType::MakeRefPtr<NG::LongPressGesture>(fingersNum, repeat, durationNum);
    gestureProcessor->PushGestureNG(gesture);
}

// PinchPressGesture
void FfiOHOSAceFrameworkPinchGestureCreate(int32_t fingers, double distance)
{
    RefPtr<GestureProcessor> gestureProcessor =
        NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();

    int32_t fingersNum =
        Utils::CheckRange(DEFAULT_PINCH_FINGER, MAX_PINCH_FINGER, DEFAULT_PINCH_FINGER, fingers);
    double distanceNum = Utils::CheckMin(0.0, DEFAULT_PINCH_DISTANCE, distance);

    auto gesture = AceType::MakeRefPtr<NG::PinchGesture>(fingersNum, distanceNum);
    gestureProcessor->PushGestureNG(gesture);
}

// SwipeGesture
void FfiOHOSAceFrameworkSwipeGestureCreate(int32_t fingers, uint32_t direction, double speed)
{
    OHOS::Ace::SwipeDirection swipeDirection;
    swipeDirection.type = direction;

    RefPtr<GestureProcessor> gestureProcessor =
        NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();

    int32_t fingersNum =
        Utils::CheckRange(DEFAULT_SLIDE_FINGER, MAX_SLIDE_FINGER, DEFAULT_SLIDE_FINGER, fingers);
    double speedNum = Utils::CheckMin(0.0, DEFAULT_SLIDE_SPEED, speed);

    auto gesture = AceType::MakeRefPtr<NG::SwipeGesture>(fingersNum, swipeDirection, speedNum);
    gestureProcessor->PushGestureNG(gesture);
}

// RotationGesture
void FfiOHOSAceFrameworkRotationGestureCreate(int32_t fingers, double angle)
{
    RefPtr<GestureProcessor> gestureProcessor =
        NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();

    int32_t fingersNum =
        Utils::CheckRange(DEFAULT_ROTATION_FINGER, MAX_ROTATION_FINGER, DEFAULT_ROTATION_FINGER, fingers);
    double angleNum = Utils::CheckMin(0.0, DEFAULT_ROTATION_ANGLE, angle);

    auto gesture = AceType::MakeRefPtr<NG::RotationGesture>(fingersNum, angleNum);
    gestureProcessor->PushGestureNG(gesture);
}

// PanGesture
void FfiOHOSAceFrameworkPanGestureCreate(int32_t fingers, uint32_t direction, double distance)
{
    OHOS::Ace::PanDirection panDirection;
    panDirection.type = direction;

    RefPtr<GestureProcessor> gestureProcessor =
        NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();

    int32_t fingersNum =
        Utils::CheckRange(DEFAULT_PAN_FINGER, MAX_PAN_FINGER, DEFAULT_PAN_FINGER, fingers);
    double distanceNum = Utils::CheckMin(0.0, DEFAULT_PAN_DISTANCE.Value(), distance);

    auto gesture = AceType::MakeRefPtr<NG::PanGesture>(fingersNum, panDirection, distanceNum);
    gestureProcessor->PushGestureNG(gesture);
}

void FfiOHOSAceFrameworkPanGestureCreateWithOptions(int64_t OptionID)
{
    auto panGestureOption = FFIData::GetData<NativePanGestureOption>(OptionID);
    if (panGestureOption == nullptr) {
        LOGE("FfiGesture: invalid PanGestureOptions ID");
    } else {
        RefPtr<GestureProcessor> gestureProcessor =
            NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();

        auto gesture = AceType::MakeRefPtr<NG::PanGesture>(panGestureOption->GetPanGestureOption());
        gestureProcessor->PushGestureNG(gesture);
    }
}

// GestureGroup
void FfiOHOSAceFrameworkGestureGroupCreate(int32_t mode)
{
    if (!Utils::CheckParamsValid(mode, GROUP_GESTURE_MODE.size())) {
        LOGE("invalid value for gesture group mode");
        return;
    }

    RefPtr<GestureProcessor> gestureProcessor =
        NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto gesture = AceType::MakeRefPtr<NG::GestureGroup>(GROUP_GESTURE_MODE[mode]);
    gestureProcessor->PushGestureNG(gesture);
}

int64_t FfiOHOSAceFrameworkPanGestureOptionsCtor(int32_t fingers, uint32_t direction, double distance)
{
    OHOS::Ace::PanDirection panDirection;
    panDirection.type = direction;

    int32_t fingersNum = Utils::CheckRange(DEFAULT_PAN_FINGER, MAX_PAN_FINGER, DEFAULT_PAN_FINGER, fingers);
    double distanceNum = Utils::CheckMin(0.0, DEFAULT_PAN_DISTANCE.Value(), distance);

    auto ret_ = FFIData::Create<NativePanGestureOption>(fingersNum, panDirection, distanceNum);
    if (ret_ == nullptr) {
        return FFI_ERROR_CODE;
    }
    return ret_->GetID();
}

void FfiOHOSAceFrameworkPanGestureOptionsSetFingers(int64_t selfID, int32_t fingers)
{
    auto self = FFIData::GetData<NativePanGestureOption>(selfID);
    if (self != nullptr) {
        self->SetFingers(fingers);
    } else {
        LOGE("FfiGesture: invalid PanGestureOptions ID");
    }
}

void FfiOHOSAceFrameworkPanGestureOptionsSetDirection(int64_t selfID, uint32_t direction)
{
    OHOS::Ace::PanDirection panDirection;
    panDirection.type = direction;

    auto self = FFIData::GetData<NativePanGestureOption>(selfID);
    if (self != nullptr) {
        self->SetDirection(panDirection);
    } else {
        LOGE("FfiGesture: invalid PanGestureOptions ID");
    }
}

void FfiOHOSAceFrameworkPanGestureOptionsSetDistance(int64_t selfID, double distance)
{
    auto self = FFIData::GetData<NativePanGestureOption>(selfID);
    if (self != nullptr) {
        self->SetDistance(distance);
    } else {
        LOGE("FfiGesture: invalid PanGestureOptions ID");
    }
}
}
