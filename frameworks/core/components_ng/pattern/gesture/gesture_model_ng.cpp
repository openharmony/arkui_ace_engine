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

#include "core/components_ng/pattern/gesture/gesture_model_ng.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/gestures/gesture_group.h"
#include "core/components_ng/gestures/long_press_gesture.h"
#include "core/components_ng/gestures/rotation_gesture.h"
#include "core/components_ng/gestures/pan_gesture.h"
#include "core/components_ng/gestures/pinch_gesture.h"
#include "core/components_ng/gestures/swipe_gesture.h"
#include "core/components_ng/gestures/tap_gesture.h"
#include "core/gestures/gesture_processor.h"

namespace OHOS::Ace::NG {
void GestureModelNG::Create(int32_t priorityNum, int32_t gestureMaskNum)
{
    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();

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

void GestureModelNG::Finish()
{
    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    NG::ViewStackProcessor::GetInstance()->ResetGestureProcessor();

    auto gesture = gestureProcessor->FinishGestureNG();
    if (!gesture) {
        TAG_LOGW(AceLogTag::ACE_GESTURE, "gesture is not exist when component finish");
        return;
    }
    gesture->SetGestureMask(gestureProcessor->GetGestureMask());
    gesture->SetPriority(gestureProcessor->GetPriority());
    auto gestureEventHub = NG::ViewStackProcessor::GetInstance()->GetMainFrameNodeGestureEventHub();
    if (gestureEventHub) {
        gestureEventHub->AddGesture(gesture);
    }
}

void GestureModelNG::Pop()
{
    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    gestureProcessor->PopGestureNG();
}

void TapGestureModelNG::Create(int32_t countNum, int32_t fingersNum)
{
    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto gesture = AceType::MakeRefPtr<NG::TapGesture>(countNum, fingersNum);
    gestureProcessor->PushGestureNG(gesture);
}

void LongPressGestureModelNG::Create(int32_t fingersNum, bool repeatResult, int32_t durationNum)
{
    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto gesture = AceType::MakeRefPtr<NG::LongPressGesture>(fingersNum, repeatResult, durationNum);
    gestureProcessor->PushGestureNG(gesture);
}

void PanGestureModelNG::Create(int32_t fingersNum, const PanDirection& panDirection, double distanceNum)
{
    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto gesture = AceType::MakeRefPtr<NG::PanGesture>(fingersNum, panDirection, distanceNum);
    gestureProcessor->PushGestureNG(gesture);
}

void PanGestureModelNG::SetPanGestureOption(const RefPtr<PanGestureOption>& panGestureOption)
{
    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto gesture = AceType::MakeRefPtr<NG::PanGesture>(panGestureOption);
    gestureProcessor->PushGestureNG(gesture);
}

void SwipeGestureModelNG::Create(int32_t fingersNum, const SwipeDirection& slideDirection, double speedNum)
{
    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto gesture = AceType::MakeRefPtr<NG::SwipeGesture>(fingersNum, slideDirection, speedNum);
    gestureProcessor->PushGestureNG(gesture);
}

void PinchGestureModelNG::Create(int32_t fingersNum, double distanceNum)
{
    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto gesture = AceType::MakeRefPtr<NG::PinchGesture>(fingersNum, distanceNum);
    gestureProcessor->PushGestureNG(gesture);
}

void RotationGestureModelNG::Create(int32_t fingersNum, double angleNum)
{
    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto gesture = AceType::MakeRefPtr<NG::RotationGesture>(fingersNum, angleNum);
    gestureProcessor->PushGestureNG(gesture);
}

void GestureGroupModelNG::Create(int32_t gestureMode)
{
    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto gesture = AceType::MakeRefPtr<NG::GestureGroup>(static_cast<GestureMode>(gestureMode));
    gestureProcessor->PushGestureNG(gesture);
}

RefPtr<GestureProcessor> TimeoutGestureModelNG::GetGestureProcessor()
{
    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    return gestureProcessor;
}

void GestureModelNG::SetOnGestureEvent(const GestureEventNoParameter& gestureEventNoParameter)
{
    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto gesture = gestureProcessor->TopGestureNG();
    CHECK_NULL_VOID(gesture);
    gesture->SetOnActionCancelId(gestureEventNoParameter);
}

void GestureModelNG::SetOnActionFunc(const GestureEventFunc& gestureEventFunc, const Ace::GestureEventAction& action)
{
    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto gesture = gestureProcessor->TopGestureNG();
    CHECK_NULL_VOID(gesture);

    switch (action) {
        case Ace::GestureEventAction::ACTION:
            gesture->SetOnActionId(gestureEventFunc);
            break;
        case Ace::GestureEventAction::START:
            gesture->SetOnActionStartId(gestureEventFunc);
            break;
        case Ace::GestureEventAction::UPDATE:
            gesture->SetOnActionUpdateId(gestureEventFunc);
            break;
        case Ace::GestureEventAction::END:
            gesture->SetOnActionEndId(gestureEventFunc);
            break;
        default:
            TAG_LOGW(AceLogTag::ACE_GESTURE, "Unknown gesture action %{public}d", action);
            break;
    }
}
} // namespace OHOS::Ace::NG
