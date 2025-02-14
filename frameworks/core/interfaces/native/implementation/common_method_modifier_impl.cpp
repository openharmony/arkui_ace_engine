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

void CreateGesture(FrameNode *frameNode,
    const Ark_GestureType* gesture, const GestureMask& mask, const GesturePriority& priority)
{
    CHECK_NULL_VOID(gesture);
    CHECK_NULL_VOID(frameNode);
    CreateGestureProcessor(priority, mask);

    Converter::VisitUnion(*gesture,
        [frameNode](const Ark_TapGestureInterface& value) {
            auto peer = reinterpret_cast<TapGestureEventPeer*>(value.handle);
            CreateTapGesture(peer);
        },
        [frameNode](const Ark_LongPressGestureInterface& value) {
            auto peer = reinterpret_cast<LongPressGestureEventPeer*>(value.handle);
            CreateLongPressGesture(peer);
        },
        [frameNode](const Ark_PanGestureInterface& value) {
            auto peer = reinterpret_cast<PanGestureEventPeer*>(value.handle);
            CreatePanGesture(peer);
        },
        [](const Ark_PinchGestureInterface& value) {
        },
        [](const Ark_SwipeGestureInterface& value) {
        },
        [](const Ark_RotationGestureInterface& value) {
        },
        [](const Ark_GestureGroupInterface& value) {
        },
        []() {});

    auto gmodel = GestureModel::GetInstance();
    if (gmodel) {
        gmodel->Pop();
    }
    FinishGestureProcessor(frameNode);
}

}
