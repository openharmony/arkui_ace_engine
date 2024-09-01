/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/models/gesture_model_impl.h"

#include "core/gestures/long_press_gesture.h"
#include "core/gestures/rotation_gesture.h"
#include "core/gestures/pan_gesture.h"
#include "core/gestures/pinch_gesture.h"
#include "core/gestures/slide_gesture.h"
#include "core/gestures/tap_gesture.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {
void GestureModelImpl::Create(int32_t priorityNum, int32_t gestureMaskNum)
{
    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = ViewStackProcessor::GetInstance()->GetGestureComponent();

    GesturePriority priority = GesturePriority::Low;
    if (priorityNum > static_cast<int32_t>(GesturePriority::Begin) &&
        priorityNum < static_cast<int32_t>(GesturePriority::End)) {
        priority = static_cast<GesturePriority>(priorityNum);
    }
    gestureProcessor->SetPriority(priority);

    GestureMask gestureMask = GestureMask::Normal;
    if (gestureMaskNum > static_cast<int32_t>(GestureMask::Begin) &&
        gestureMaskNum < static_cast<int32_t>(GestureMask::End)) {
        gestureMask = static_cast<GestureMask>(gestureMaskNum);
    }
    gestureProcessor->SetGestureMask(gestureMask);
}

void GestureModelImpl::Finish()
{
    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = ViewStackProcessor::GetInstance()->GetGestureComponent();
    auto gesture = gestureProcessor->FinishGesture();
    CHECK_NULL_VOID(gesture);
    gesture->SetGestureMask(gestureProcessor->GetGestureMask());
    gesture->SetPriority(gestureProcessor->GetPriority());
    auto boxComponent = ViewStackProcessor::GetInstance()->GetBoxComponent();
    boxComponent->AddGesture(gestureProcessor->GetPriority(), gesture);
}

void GestureModelImpl::Pop()
{
    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = ViewStackProcessor::GetInstance()->GetGestureComponent();
    gestureProcessor->PopGesture();
}

void TapGestureModelImpl::Create(int32_t countNum, int32_t fingersNum, double distanceThreshold)
{
    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = ViewStackProcessor::GetInstance()->GetGestureComponent();
    auto gesture = AceType::MakeRefPtr<TapGesture>(countNum, fingersNum, distanceThreshold);
    gestureProcessor->PushGesture(gesture);
}

void LongPressGestureModelImpl::Create(int32_t fingersNum, bool repeatResult, int32_t durationNum)
{
    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = ViewStackProcessor::GetInstance()->GetGestureComponent();
    auto gesture = AceType::MakeRefPtr<LongPressGesture>(fingersNum, repeatResult, durationNum);
    gestureProcessor->PushGesture(gesture);
}

void PanGestureModelImpl::Create(int32_t fingersNum, const PanDirection& panDirection, double distanceNum)
{
    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = ViewStackProcessor::GetInstance()->GetGestureComponent();
    auto gesture = AceType::MakeRefPtr<PanGesture>(fingersNum, panDirection, distanceNum);
    gestureProcessor->PushGesture(gesture);
}

void PanGestureModelImpl::SetPanGestureOption(const RefPtr<PanGestureOption>& panGestureOption)
{
    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = ViewStackProcessor::GetInstance()->GetGestureComponent();
    auto gesture = AceType::MakeRefPtr<PanGesture>(panGestureOption);
    gestureProcessor->PushGesture(gesture);
}

void SwipeGestureModelImpl::Create(int32_t fingersNum, const SwipeDirection& slideDirection, double speedNum)
{
    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = ViewStackProcessor::GetInstance()->GetGestureComponent();
    auto gesture = AceType::MakeRefPtr<SwipeGesture>(fingersNum, slideDirection, speedNum);
    gestureProcessor->PushGesture(gesture);
}

void PinchGestureModelImpl::Create(int32_t fingersNum, double distanceNum)
{
    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = ViewStackProcessor::GetInstance()->GetGestureComponent();
    auto gesture = AceType::MakeRefPtr<PinchGesture>(fingersNum, distanceNum);
    gestureProcessor->PushGesture(gesture);
}

void RotationGestureModelImpl::Create(int32_t fingersNum, double angleNum)
{
    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = ViewStackProcessor::GetInstance()->GetGestureComponent();
    auto gesture = AceType::MakeRefPtr<RotationGesture>(fingersNum, angleNum);
    gestureProcessor->PushGesture(gesture);
}

void GestureGroupModelImpl::Create(int32_t gestureMode)
{
    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = ViewStackProcessor::GetInstance()->GetGestureComponent();
    auto gesture = AceType::MakeRefPtr<GestureGroup>(static_cast<GestureMode>(gestureMode));
    gestureProcessor->PushGesture(gesture);
}

RefPtr<GestureProcessor> TimeoutGestureModelImpl::GetGestureProcessor()
{
    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = ViewStackProcessor::GetInstance()->GetGestureComponent();
    return gestureProcessor;
}

void GestureModelImpl::SetOnGestureEvent(const GestureEventNoParameter& gestureEventNoParameter)
{
    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = ViewStackProcessor::GetInstance()->GetGestureComponent();
    auto gesture = gestureProcessor->TopGesture();
    CHECK_NULL_VOID(gesture);

    RefPtr<V2::InspectorFunctionImpl> impl;
    auto inspector = ViewStackProcessor::GetInstance()->GetInspectorComposedComponent();
    CHECK_NULL_VOID(inspector);
    impl = inspector->GetInspectorFunctionImpl();

    gesture->SetOnActionCancelId([func = std::move(gestureEventNoParameter), impl]() {
        auto info = GestureEvent();
        if (impl) {
            impl->UpdateEventInfo(info);
        }
        func();
    });
}

void GestureModelImpl::SetOnActionFunc(const GestureEventFunc& gestureEventFunc,
    const Ace::GestureEventAction& action)
{
    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = ViewStackProcessor::GetInstance()->GetGestureComponent();
    auto gesture = gestureProcessor->TopGesture();
    CHECK_NULL_VOID(gesture);

    RefPtr<V2::InspectorFunctionImpl> impl;
    auto inspector = ViewStackProcessor::GetInstance()->GetInspectorComposedComponent();
    CHECK_NULL_VOID(inspector);
    impl = inspector->GetInspectorFunctionImpl();

    auto onActionFunc = [func = std::move(gestureEventFunc), impl](GestureEvent& info) {
        if (impl) {
            impl->UpdateEventInfo(info);
        }
        func(info);
    };

    switch (action) {
        case Ace::GestureEventAction::ACTION:
            gesture->SetOnActionId(onActionFunc);
            break;
        case Ace::GestureEventAction::START:
            gesture->SetOnActionStartId(onActionFunc);
            break;
        case Ace::GestureEventAction::UPDATE:
            gesture->SetOnActionUpdateId(onActionFunc);
            break;
        case Ace::GestureEventAction::END:
            gesture->SetOnActionEndId(onActionFunc);
            break;
        default:
            LOGW("Unknown gesture action %{public}d", action);
            break;
    }
}
} // namespace OHOS::Ace::Framework
