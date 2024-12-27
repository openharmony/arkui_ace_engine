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

#include "bridge/cj_frontend/cppview/gesture.h"

#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/gestures/long_press_gesture.h"
#include "core/gestures/pan_gesture.h"
#include "core/gestures/pinch_gesture.h"
#include "core/gestures/rotation_gesture.h"
#include "core/gestures/slide_gesture.h"

namespace OHOS::Ace::Framework {

namespace {
constexpr int32_t DEFAULT_TAP_FINGER = 1;
constexpr int32_t DEFAULT_TAP_COUNT = 1;
constexpr int32_t DEFAULT_LONG_PRESS_FINGER = 1;
constexpr int32_t DEFAULT_LONG_PRESS_DURATION = 500;
constexpr int32_t DEFAULT_PINCH_FINGER = 2;
constexpr double DEFAULT_PINCH_DISTANCE = 3.0;
constexpr int32_t DEFAULT_PAN_FINGER = 1;
constexpr double DEFAULT_PAN_DISTANCE = 5.0;
constexpr int32_t DEFAULT_SLIDE_FINGER = DEFAULT_PAN_FINGER;
constexpr double DEFAULT_SLIDE_SPEED = 100.0;
constexpr int32_t DEFAULT_ROTATION_FINGER = 2;
constexpr double DEFAULT_ROTATION_ANGLE = 1.0;

} // namespace

void Gesture::Create(GesturePriority priority, GestureMask gestureMask)
{
    LOGD("gesture create");
    auto gestureComponent = ViewStackProcessor::GetInstance()->GetGestureComponent();
    gestureComponent->SetPriority(priority);
    gestureComponent->SetGestureMask(gestureMask);
}

void Gesture::Finish()
{
    LOGD("gesture finish");
    auto gestureComponent = ViewStackProcessor::GetInstance()->GetGestureComponent();
    auto gesture = gestureComponent->FinishGesture();
    if (!gesture) {
        LOGE("Gesture: gesture is not exist when component finish");
        return;
    }

    gesture->SetGestureMask(gestureComponent->GetGestureMask());

    auto boxComponent = ViewStackProcessor::GetInstance()->GetBoxComponent();

    boxComponent->AddGesture(gestureComponent->GetPriority(), gesture);
}

void Gesture::Pop()
{
    LOGD("gesture pop");
    auto gestureComponent = ViewStackProcessor::GetInstance()->GetGestureComponent();
    gestureComponent->PopGesture();
}

void Gesture::HandlerOnAction(const std::function<void(const GestureEvent& event)>& callback)
{
    Gesture::HandlerOnGestureEvent(CJGestureEvent::ACTION, callback);
}
void Gesture::HandlerOnActionStart(const std::function<void(const GestureEvent& event)>& callback)
{
    Gesture::HandlerOnGestureEvent(CJGestureEvent::START, callback);
}
void Gesture::HandlerOnActionUpdate(const std::function<void(const GestureEvent& event)>& callback)
{
    Gesture::HandlerOnGestureEvent(CJGestureEvent::UPDATE, callback);
}

void Gesture::HandlerOnActionEnd(const std::function<void(const GestureEvent& event)>& callback)
{
    Gesture::HandlerOnGestureEvent(CJGestureEvent::END, callback);
}
void Gesture::HandlerOnActionCancel(const std::function<void(const GestureEvent& event)>& callback)
{
    Gesture::HandlerOnGestureEvent(CJGestureEvent::CANCEL, callback);
}

void Gesture::HandlerOnGestureEvent(
    const CJGestureEvent& action, const std::function<void(const GestureEvent& event)>& callback)
{
    auto gestureComponent = ViewStackProcessor::GetInstance()->GetGestureComponent();
    auto gesture = gestureComponent->TopGesture();
    if (!gesture) {
        LOGE("Gesture: top gesture is illegal");
        return;
    }
    auto inspector = ViewStackProcessor::GetInstance()->GetInspectorComposedComponent();
    if (!inspector) {
        LOGE("Gesture: fail to get inspector for on handle event");
        return;
    }
    auto impl = inspector->GetInspectorFunctionImpl();

    if (action == CJGestureEvent::CANCEL) {
        auto onActionCancelFunc = [callback = std::move(callback), impl](GestureEvent& info) {
            if (impl) {
                impl->UpdateEventInfo(info);
            }
            ACE_SCORING_EVENT("Gesture.onCancel");
            callback(info);
        };
        gesture->SetOnActionCancelId(onActionCancelFunc);
        return;
    }
    auto onActionFunc = [callback = std::move(callback), impl](GestureEvent& info) {
        if (impl) {
            impl->UpdateEventInfo(info);
        }
        ACE_SCORING_EVENT("Gesture.onActionCancel");
        callback(info);
    };

    switch (action) {
        case CJGestureEvent::ACTION:
            gesture->SetOnActionId(onActionFunc);
            break;
        case CJGestureEvent::START:
            gesture->SetOnActionStartId(onActionFunc);
            break;
        case CJGestureEvent::UPDATE:
            gesture->SetOnActionUpdateId(onActionFunc);
            break;
        case CJGestureEvent::END:
            gesture->SetOnActionEndId(onActionFunc);
            break;
        default:
            LOGW("Gesture: Unknown gesture action %{public}d", action);
            break;
    }
}

void TapGesture::Create(int32_t count, int32_t fingers)
{
    int32_t countNum = DEFAULT_TAP_COUNT;
    int32_t fingersNum = DEFAULT_TAP_FINGER;

    countNum = count <= DEFAULT_TAP_COUNT ? DEFAULT_TAP_COUNT : count;
    fingersNum = fingers <= DEFAULT_TAP_FINGER ? DEFAULT_TAP_FINGER : fingers;

    auto gestureComponent = ViewStackProcessor::GetInstance()->GetGestureComponent();
    auto gesture = AceType::MakeRefPtr<OHOS::Ace::TapGesture>(countNum, fingersNum);
    gestureComponent->PushGesture(gesture);
}

void LongPressGesture::Create(int32_t fingers, bool repeat, int32_t duration)
{
    int32_t fingersNum = DEFAULT_LONG_PRESS_FINGER;
    int32_t durationNum = DEFAULT_LONG_PRESS_DURATION;

    fingersNum = fingers <= DEFAULT_LONG_PRESS_FINGER ? DEFAULT_LONG_PRESS_FINGER : fingers;
    durationNum = duration <= 0 ? DEFAULT_LONG_PRESS_DURATION : duration;

    auto gestureComponent = ViewStackProcessor::GetInstance()->GetGestureComponent();
    auto gesture = AceType::MakeRefPtr<OHOS::Ace::LongPressGesture>(fingersNum, repeat, durationNum);
    gestureComponent->PushGesture(gesture);
}

void PinchGesture::Create(int32_t fingers, double distance)
{
    int32_t fingersNum = DEFAULT_PINCH_FINGER;
    double distanceNum = DEFAULT_PINCH_DISTANCE;

    fingersNum = fingers <= DEFAULT_PINCH_FINGER ? DEFAULT_PINCH_FINGER : fingers;
    distanceNum = LessNotEqual(distance, 0.0) ? DEFAULT_PINCH_DISTANCE : distance;

    auto gestureComponent = ViewStackProcessor::GetInstance()->GetGestureComponent();
    auto gesture = AceType::MakeRefPtr<OHOS::Ace::PinchGesture>(fingersNum, distanceNum);
    gestureComponent->PushGesture(gesture);
}

void SwipeGesture::Create(int32_t fingers, const SwipeDirection& swipeDirection, double speed)
{
    int32_t fingersNum = DEFAULT_SLIDE_FINGER;
    double speedNum = DEFAULT_SLIDE_SPEED;

    fingersNum = fingers <= DEFAULT_PAN_FINGER ? DEFAULT_PAN_FINGER : fingers;
    speedNum = LessNotEqual(speed, 0.0) ? DEFAULT_SLIDE_SPEED : speed;

    auto gestureComponent = ViewStackProcessor::GetInstance()->GetGestureComponent();
    auto gesture = AceType::MakeRefPtr<OHOS::Ace::SwipeGesture>(fingersNum, swipeDirection, speedNum);
    gestureComponent->PushGesture(gesture);
}

void RotationGesture::Create(int32_t fingers, double angle)
{
    double angleNum = DEFAULT_ROTATION_ANGLE;
    int32_t fingersNum = DEFAULT_ROTATION_FINGER;

    fingersNum = fingers <= DEFAULT_ROTATION_FINGER ? DEFAULT_ROTATION_FINGER : fingers;
    angleNum = LessNotEqual(angle, 0.0) ? DEFAULT_ROTATION_ANGLE : angle;

    auto gestureComponent = ViewStackProcessor::GetInstance()->GetGestureComponent();
    auto gesture = AceType::MakeRefPtr<OHOS::Ace::RotationGesture>(fingersNum, angleNum);
    gestureComponent->PushGesture(gesture);
}

void GestureGroup::Create(const GestureMode& mode)
{
    auto gestureComponent = ViewStackProcessor::GetInstance()->GetGestureComponent();
    auto gesture = AceType::MakeRefPtr<OHOS::Ace::GestureGroup>(mode);
    gestureComponent->PushGesture(gesture);
}

void PanGesture::Create(int32_t fingers, const PanDirection& panDirection, double distance)
{
    int32_t fingersNum = DEFAULT_PAN_FINGER;
    double distanceNum = DEFAULT_PAN_DISTANCE;

    fingersNum = fingers <= DEFAULT_PAN_FINGER ? DEFAULT_PAN_FINGER : fingers;
    distanceNum = LessNotEqual(distance, 0.0) ? DEFAULT_PAN_DISTANCE : distance;

    auto gestureComponent = ViewStackProcessor::GetInstance()->GetGestureComponent();
    auto gesture = AceType::MakeRefPtr<OHOS::Ace::PanGesture>(fingersNum, panDirection, distanceNum);
    gestureComponent->PushGesture(gesture);
}

void PanGesture::Create(const sptr<NativePanGestureOption>& panGestureOption)
{
    auto gestureComponent = ViewStackProcessor::GetInstance()->GetGestureComponent();
    auto gesture = AceType::MakeRefPtr<OHOS::Ace::PanGesture>(panGestureOption->GetPanGestureOption());
    gestureComponent->PushGesture(gesture);
}

NativePanGestureOption::NativePanGestureOption(int32_t fingers, const PanDirection& panDirection, double distance)
    : FFIData()
{
    RefPtr<PanGestureOption> option = AceType::MakeRefPtr<PanGestureOption>();
    SetPanGestureOption(option);
    SetDirection(panDirection);
    SetDistance(distance);
    SetFingers(fingers);
    LOGI("NativePanGestureOption constructed: %{public}" PRId64, GetID());
}

NativePanGestureOption::~NativePanGestureOption()
{
    LOGI("NativePanGestureOption Destroyed: %{public}" PRId64, GetID());
}

void NativePanGestureOption::SetDirection(const PanDirection& panDirection)
{
    if (!panGestureOption_) {
        LOGE("NativePanGestureOption: Native panGestureOption_ is nullptr");
        return;
    }
    panGestureOption_->SetDirection(panDirection);
}

void NativePanGestureOption::SetDistance(double distance)
{
    if (!panGestureOption_) {
        LOGE("NativePanGestureOption: Native panGestureOption_ is nullptr");
        return;
    }
    panGestureOption_->SetDistance(distance);
}

void NativePanGestureOption::SetFingers(int32_t fingers)
{
    if (!panGestureOption_) {
        LOGE("NativePanGestureOption: Native panGestureOption_ is nullptr");
        return;
    }
    panGestureOption_->SetFingers(fingers);
}

} // namespace OHOS::Ace::Framework
