/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "common_method_modifier_impl.h"
#include "core/components_ng/pattern/gesture/gesture_model_ng.h"
#include "core/interfaces/native/implementation/pinch_gesture_event_peer.h"
#include "core/interfaces/native/implementation/rotation_gesture_event_peer.h"
#include "core/interfaces/native/implementation/swipe_gesture_event_peer.h"

using namespace OHOS::Ace::NG::Converter;

namespace OHOS::Ace::NG {

PanDirection DeterminePanDirection(float dx, float dy)
{
    PanDirection result;
    const float epsilon = 1e-5;

    if (std::abs(dx) < epsilon && std::abs(dy) < epsilon) {
        result.type = PanDirection::NONE;
    } else if (std::abs(dx) > epsilon && std::abs(dy) > epsilon) {
        result.type = PanDirection::ALL;
    } else if (std::abs(dx) > std::abs(dy)) {
        result.type = (dx > 0) ? PanDirection::RIGHT : PanDirection::LEFT;
    } else {
        result.type = (dy > 0) ? PanDirection::DOWN : PanDirection::UP;
    }
    return result;
};

SwipeDirection DetermineSwipeDirection(float dx, float dy)
{
    SwipeDirection result;
    const float epsilon = 1e-5;

    if (std::abs(dx) < epsilon && std::abs(dy) < epsilon) {
        result.type = SwipeDirection::NONE;
    } else if (std::abs(dx) > epsilon && std::abs(dy) > epsilon) {
        result.type = SwipeDirection::ALL;
    } else if (std::abs(dx) > std::abs(dy)) {
        result.type = SwipeDirection::HORIZONTAL;
    } else {
        result.type = SwipeDirection::VERTICAL;
    }
    return result;
}

void CreateGestureProcessor(GesturePriority priority, GestureMask gestureMask)
{
    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    gestureProcessor->SetPriority(priority);
    gestureProcessor->SetGestureMask(gestureMask);
}

void FinishGestureProcessor(FrameNode *frameNode)
{
    CHECK_NULL_VOID(frameNode);
    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    NG::ViewStackProcessor::GetInstance()->ResetGestureProcessor();

    auto gesture = gestureProcessor->FinishGestureNG();
    if (!gesture) {
        return;
    }
    gesture->SetGestureMask(gestureProcessor->GetGestureMask());
    gesture->SetPriority(gestureProcessor->GetPriority());
    auto gestureEventHub = frameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureEventHub);
    gestureEventHub->AddGesture(gesture);
}

void CreateTapGesture(TapGestureEventPeer *peer)
{
    CHECK_NULL_VOID(peer);
    auto event = peer->GetEventInfo();
    auto model = TapGestureModelNG::GetInstance();
    CHECK_NULL_VOID(event && model);
    constexpr int32_t countNum = 1;
    constexpr double distanceThreshold = std::numeric_limits<double>::infinity();
    model->Create(countNum, event->GetFingerList().size(), distanceThreshold);
}

void CreateLongPressGesture(LongPressGestureEventPeer* peer)
{
    CHECK_NULL_VOID(peer);
    auto event = peer->GetEventInfo();
    auto model = LongPressGestureModelNG::GetInstance();
    CHECK_NULL_VOID(event && model);

    TimeStamp start = event->GetTimeStamp();
    auto now = std::chrono::high_resolution_clock::now();
    auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now - start);
    model->Create(event->GetFingerList().size(), event->GetRepeat(), duration_ms.count());
}

void CreatePanGesture(PanGestureEventPeer* peer)
{
    CHECK_NULL_VOID(peer);
    auto event = peer->GetEventInfo();
    auto model = PanGestureModelNG::GetInstance();
    CHECK_NULL_VOID(event && model);
    PanDirection panDirection = DeterminePanDirection(event->GetOffsetX(), event->GetOffsetY());
    model->Create(event->GetFingerList().size(), panDirection, 0);
}

void CreatePinchGesture(PinchGestureEventPeer* peer)
{
    CHECK_NULL_VOID(peer);
    auto event = peer->GetEventInfo();
    auto model = PinchGestureModelNG::GetInstance();
    CHECK_NULL_VOID(event && model);
    constexpr double distanceNum = std::numeric_limits<double>::infinity();
    model->Create(event->GetFingerList().size(), distanceNum);
}

void CreateSwipeGesture(SwipeGestureEventPeer* peer)
{
    CHECK_NULL_VOID(peer);
    auto event = peer->GetEventInfo();
    auto model = SwipeGestureModelNG::GetInstance();
    CHECK_NULL_VOID(event && model);
    auto offset = event->GetTarget().origin;
    SwipeDirection direction = DetermineSwipeDirection(
        offset.GetX().ConvertToPx(), offset.GetY().ConvertToPx());
    model->Create(event->GetFingerList().size(), direction, event->GetSpeed());
}

void CreateRotationGesture(RotationGestureEventPeer* peer)
{
    CHECK_NULL_VOID(peer);
    auto event = peer->GetEventInfo();
    auto model = RotationGestureModelNG::GetInstance();
    CHECK_NULL_VOID(event && model);
    model->Create(event->GetFingerList().size(), event->GetAngle());
}

void CreateGroupGesture(BaseGestureEventPeer* peer)
{
    CHECK_NULL_VOID(peer);
    auto model = GestureGroupModelNG::GetInstance();
    CHECK_NULL_VOID(model);
    int32_t mode = static_cast<int32_t>(GestureMode::Sequence);
    model->Create(mode);
}

void CreateGesture(FrameNode *frameNode,
    const Ark_GestureType* gesture,
    const GestureMask& mask, const GesturePriority& priority)
{
    CHECK_NULL_VOID(gesture);
    CHECK_NULL_VOID(frameNode);
    CreateGestureProcessor(priority, mask);

    Converter::VisitUnion(*gesture,
        [](const Ark_TapGestureInterface& value) {
            CreateTapGesture(nullptr);
        },
        [](const Ark_LongPressGestureInterface& value) {
            CreateLongPressGesture(nullptr);
        },
        [](const Ark_PanGestureInterface& value) {
            CreatePanGesture(nullptr);
        },
        [](const Ark_PinchGestureInterface& value) {
            CreatePinchGesture(nullptr);
        },
        [](const Ark_SwipeGestureInterface& value) {
            CreateSwipeGesture(nullptr);
        },
        [](const Ark_RotationGestureInterface& value) {
            CreateRotationGesture(nullptr);
        },
        [](const Ark_GestureGroupInterface& value) {
            CreateGroupGesture(nullptr);
        },
        []() {});

    if (auto gmodel = GestureModel::GetInstance(); gmodel) {
        gmodel->Pop();
    }
    FinishGestureProcessor(frameNode);
}

}
