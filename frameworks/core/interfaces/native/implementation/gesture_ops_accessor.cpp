/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#include <cstdint>
#include <utility>

#include "arkoala_api_generated.h"

#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/gestures/long_press_gesture.h"
#include "core/components_ng/gestures/pan_gesture.h"
#include "core/components_ng/gestures/pinch_gesture.h"
#include "core/components_ng/gestures/rotation_gesture.h"
#include "core/components_ng/gestures/swipe_gesture.h"
#include "core/components_ng/gestures/tap_gesture.h"
#include "core/components_ng/pattern/gesture/gesture_model_ng.h"
#include "core/interfaces/arkoala/arkoala_api.h"
#include "core/interfaces/native/implementation/pan_gesture_options_peer.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

struct GestureOpsPeer {
    virtual ~GestureOpsPeer() = default;
};

namespace OHOS::Ace::NG::GeneratedModifier {
namespace {
constexpr int32_t DEFAULT_TAP_FINGER = 1;
constexpr int32_t DEFAULT_TAP_COUNT = 1;
constexpr double DEFAULT_TAP_DISTANCE = std::numeric_limits<double>::infinity();
constexpr int32_t DEFAULT_LONG_PRESS_FINGER = 1;
constexpr int32_t DEFAULT_LONG_PRESS_DURATION = 500;
constexpr int32_t DEFAULT_PINCH_FINGER = 2;
constexpr int32_t DEFAULT_MAX_PINCH_FINGER = 5;
constexpr double DEFAULT_PINCH_DISTANCE = 5.0;
constexpr int32_t DEFAULT_PAN_FINGER = 1;
constexpr int32_t DEFAULT_MAX_FINGERS = 10;
constexpr OHOS::Ace::Dimension DEFAULT_PAN_DISTANCE = 5.0_vp;
constexpr int32_t DEFAULT_SLIDE_FINGER = DEFAULT_PAN_FINGER;
constexpr double DEFAULT_SLIDE_SPEED = 100.0;
constexpr int32_t DEFAULT_ROTATION_FINGER = 2;
constexpr int32_t DEFAULT_MAX_ROTATION_FINGER = 5;
constexpr double DEFAULT_ROTATION_ANGLE = 1.0;
constexpr double DEFAULT_MAX_ROTATION_ANGLE = 360.0;
} // namespace
namespace GestureOpsAccessor {
Ark_NativePointer CreateTapGestureImpl(const Ark_Number* fingers, const Ark_Number* count,
    const Ark_Number* distanceThreshold, Ark_Boolean isFingerCountLimited)
{
    int32_t fingerValue = Converter::Convert<int32_t>(*fingers);
    if (fingerValue > DEFAULT_MAX_FINGERS || fingerValue < DEFAULT_TAP_FINGER) {
        fingerValue = DEFAULT_TAP_FINGER;
    }
    int32_t countValue = Converter::Convert<int32_t>(*count);
    countValue = countValue < DEFAULT_TAP_COUNT ? DEFAULT_TAP_COUNT : countValue;
    float distanceThresholdValue = Converter::Convert<float>(*distanceThreshold);
    distanceThresholdValue = distanceThresholdValue < 0 ? DEFAULT_TAP_DISTANCE : distanceThresholdValue;
    distanceThresholdValue = Dimension(distanceThresholdValue, DimensionUnit::VP).ConvertToPx();
    bool isFingerCountLimitedValue = Converter::Convert<bool>(isFingerCountLimited);
    auto tapGestureObject =
        AceType::MakeRefPtr<TapGesture>(countValue, fingerValue, distanceThresholdValue, isFingerCountLimitedValue);
    tapGestureObject->IncRefCount();
    return AceType::RawPtr(tapGestureObject);
}
Ark_NativePointer CreateLongPressGestureImpl(
    const Ark_Number* fingers, Ark_Boolean repeat, const Ark_Number* duration, Ark_Boolean isFingerCountLimited)
{
    int32_t fingerValue = Converter::Convert<int32_t>(*fingers);
    if (fingerValue > DEFAULT_MAX_FINGERS || fingerValue < DEFAULT_TAP_FINGER) {
        fingerValue = DEFAULT_TAP_FINGER;
    }
    bool repeatValue = Converter::Convert<bool>(repeat);
    int32_t durationValue = Converter::Convert<int32_t>(*duration);
    durationValue = durationValue <= 0 ? DEFAULT_LONG_PRESS_DURATION : durationValue;
    bool isFingerCountLimitedValue = Converter::Convert<bool>(isFingerCountLimited);
    auto longPressGestureObject = AceType::MakeRefPtr<LongPressGesture>(
        fingerValue, repeatValue, durationValue, false, false, isFingerCountLimitedValue);
    longPressGestureObject->IncRefCount();
    return AceType::RawPtr(longPressGestureObject);
}
Ark_NativePointer CreatePanGestureImpl(
    const Ark_Number* fingers, Ark_PanDirection direction, const Ark_Number* distance, Ark_Boolean isFingerCountLimited)
{
    int32_t fingerValue = Converter::Convert<int32_t>(*fingers);
    if (fingerValue > DEFAULT_MAX_FINGERS || fingerValue < DEFAULT_TAP_FINGER) {
        fingerValue = DEFAULT_TAP_FINGER;
    }
    PanDirection defaultPanDirection;
    defaultPanDirection.type = PanDirection::ALL;
    auto panDirection = Converter::Convert<std::optional<PanDirection>>(direction).value_or(defaultPanDirection);
    double distanceValue = Converter::Convert<double>(*distance);
    distanceValue =
        (LessNotEqual(distanceValue, 0.0) ? DEFAULT_PAN_DISTANCE : Dimension(distanceValue, DimensionUnit::VP))
            .ConvertToPx();
    bool isFingerCountLimitedValue = Converter::Convert<bool>(isFingerCountLimited);
    auto panGestureObject =
        AceType::MakeRefPtr<PanGesture>(fingerValue, panDirection, distanceValue, isFingerCountLimitedValue);
    panGestureObject->IncRefCount();
    return AceType::RawPtr(panGestureObject);
}
Ark_NativePointer CreatePanGestureWithPanGestureOptionsImpl(Ark_NativePointer panGestureOptions)
{
    Ark_PanGestureOptions peer = reinterpret_cast<Ark_PanGestureOptions>(panGestureOptions);
    CHECK_NULL_RETURN(peer, nullptr);
    CHECK_NULL_RETURN(peer->handler, nullptr);
    auto direction = peer->handler->GetDirection();
    auto distance = peer->handler->GetDistance();
    auto fingers = peer->handler->GetFingers();
    auto isFingerCountLimited = peer->handler->GetIsLimitFingerCount();
    auto panGestureObject = AceType::MakeRefPtr<PanGesture>(fingers, direction, distance, isFingerCountLimited);
    panGestureObject->IncRefCount();
    return AceType::RawPtr(panGestureObject);
}
Ark_NativePointer CreatePinchGestureImpl(
    const Ark_Number* fingers, const Ark_Number* distance, Ark_Boolean isFingerCountLimited)
{
    int32_t fingerValue = Converter::Convert<int32_t>(*fingers);
    if (fingerValue > DEFAULT_MAX_FINGERS || fingerValue < DEFAULT_TAP_FINGER) {
        fingerValue = DEFAULT_TAP_FINGER;
    }
    double distanceValue = Converter::Convert<double>(*distance);
    distanceValue = LessNotEqual(distanceValue, 0.0) ? DEFAULT_PINCH_DISTANCE : distanceValue;
    bool isFingerCountLimitedValue = Converter::Convert<bool>(isFingerCountLimited);
    auto pinchGestureObject = AceType::MakeRefPtr<PinchGesture>(fingerValue, distanceValue, isFingerCountLimitedValue);
    pinchGestureObject->IncRefCount();
    return AceType::RawPtr(pinchGestureObject);
}
Ark_NativePointer CreateRotationGestureImpl(
    const Ark_Number* fingers, const Ark_Number* angle, Ark_Boolean isFingerCountLimited)
{
    int32_t fingerValue = Converter::Convert<int32_t>(*fingers);
    if (fingerValue > DEFAULT_MAX_FINGERS || fingerValue < DEFAULT_TAP_FINGER) {
        fingerValue = DEFAULT_TAP_FINGER;
    }
    double angleValue = Converter::Convert<double>(*angle);
    if (GreatNotEqual(angleValue, DEFAULT_MAX_ROTATION_ANGLE) || LessNotEqual(angleValue, 0.0)) {
        angleValue = DEFAULT_ROTATION_ANGLE;
    }
    bool isFingerCountLimitedValue = Converter::Convert<bool>(isFingerCountLimited);
    auto rotationGestureObject =
        AceType::MakeRefPtr<RotationGesture>(fingerValue, angleValue, isFingerCountLimitedValue);
    rotationGestureObject->IncRefCount();
    return AceType::RawPtr(rotationGestureObject);
}
Ark_NativePointer CreateSwipeGestureImpl(
    const Ark_Number* fingers, Ark_SwipeDirection direction, const Ark_Number* speed, Ark_Boolean isFingerCountLimited)
{
    int32_t fingerValue = Converter::Convert<int32_t>(*fingers);
    if (fingerValue > DEFAULT_MAX_FINGERS || fingerValue < DEFAULT_TAP_FINGER) {
        fingerValue = DEFAULT_TAP_FINGER;
    }
    SwipeDirection defaultDirection;
    defaultDirection.type = SwipeDirection::ALL;
    auto swipeDirection = Converter::Convert<std::optional<SwipeDirection>>(direction).value_or(defaultDirection);
    double speedValue = Converter::Convert<double>(*speed);
    speedValue = LessOrEqual(speedValue, 0.0) ? DEFAULT_SLIDE_SPEED : speedValue;
    bool isFingerCountLimitedValue = Converter::Convert<bool>(isFingerCountLimited);
    auto swipeGestureObject =
        AceType::MakeRefPtr<SwipeGesture>(fingerValue, swipeDirection, speedValue, isFingerCountLimitedValue);
    swipeGestureObject->IncRefCount();
    return AceType::RawPtr(swipeGestureObject);
}
Ark_NativePointer CreateGestureGroupImpl(Ark_GestureMode mode)
{
    auto gestureMode = Converter::Convert<std::optional<GestureMode>>(mode).value_or(GestureMode::Exclusive);
    auto gestureGroupObject = AceType::MakeRefPtr<GestureGroup>(gestureMode);
    gestureGroupObject->IncRefCount();
    return AceType::RawPtr(gestureGroupObject);
}
void SetOnActionImpl(Ark_NativePointer gesture, const Callback_GestureEvent_Void* onAction)
{
    auto* gesturePtr = reinterpret_cast<Gesture*>(gesture);
    CHECK_NULL_VOID(gesturePtr);
    auto onActionEvent = [callback = CallbackHelper(*onAction)](GestureEvent& info) {
        const auto gestureEvent = Converter::ArkGestureEventSync(info);
        callback.InvokeSync(gestureEvent.ArkValue());
    };
    gesturePtr->SetOnActionId(onActionEvent);
}
void SetOnActionStartImpl(Ark_NativePointer gesture, const Callback_GestureEvent_Void* onActionStart)
{
    auto* gesturePtr = reinterpret_cast<Gesture*>(gesture);
    CHECK_NULL_VOID(gesturePtr);
    auto onActionStartEvent = [callback = CallbackHelper(*onActionStart)](GestureEvent& info) {
        const auto gestureEvent = Converter::ArkGestureEventSync(info);
        callback.InvokeSync(gestureEvent.ArkValue());
    };
    gesturePtr->SetOnActionStartId(onActionStartEvent);
}
void SetOnActionUpdateImpl(Ark_NativePointer gesture, const Callback_GestureEvent_Void* onActionUpdate)
{
    auto* gesturePtr = reinterpret_cast<Gesture*>(gesture);
    CHECK_NULL_VOID(gesturePtr);
    auto onActionUpdateEvent = [callback = CallbackHelper(*onActionUpdate)](GestureEvent& info) {
        const auto gestureEvent = Converter::ArkGestureEventSync(info);
        callback.InvokeSync(gestureEvent.ArkValue());
    };
    gesturePtr->SetOnActionUpdateId(onActionUpdateEvent);
}
void SetOnActionEndImpl(Ark_NativePointer gesture, const Callback_GestureEvent_Void* onActionEnd)
{
    auto* gesturePtr = reinterpret_cast<Gesture*>(gesture);
    CHECK_NULL_VOID(gesturePtr);
    auto onActionEndEvent = [callback = CallbackHelper(*onActionEnd)](GestureEvent& info) {
        const auto gestureEvent = Converter::ArkGestureEventSync(info);
        callback.InvokeSync(gestureEvent.ArkValue());
    };
    gesturePtr->SetOnActionEndId(onActionEndEvent);
}
void SetOnActionCancelImpl(Ark_NativePointer gesture, const Callback_GestureEvent_Void* onActionCancel)
{
    auto* gesturePtr = reinterpret_cast<Gesture*>(gesture);
    CHECK_NULL_VOID(gesturePtr);
    auto onActionCancelEvent = [callback = CallbackHelper(*onActionCancel)](GestureEvent& info) {
        const auto gestureEvent = Converter::ArkGestureEventSync(info);
        callback.InvokeSync(gestureEvent.ArkValue());
    };
    gesturePtr->SetOnActionCancelId(onActionCancelEvent);
}
void SetOnCancelImpl(Ark_NativePointer gesture, const Callback_Void* onCancel)
{
    auto* gesturePtr = reinterpret_cast<Gesture*>(gesture);
    CHECK_NULL_VOID(gesturePtr);
    auto onCancelEvent = [callback = CallbackHelper(*onCancel)](GestureEvent& info) { callback.InvokeSync(); };
    gesturePtr->SetOnActionCancelId(onCancelEvent);
}
void SetGestureTagImpl(Ark_NativePointer gesture, const Ark_String* tag)
{
    auto* gestureObject = reinterpret_cast<Gesture*>(gesture);
    CHECK_NULL_VOID(gestureObject);
    gestureObject->SetTag(Converter::Convert<std::string>(*tag));
}
void SetAllowedTypesImpl(Ark_NativePointer gesture, const Array_SourceTool* types)
{
    auto* gestureObject = reinterpret_cast<Gesture*>(gesture);
    CHECK_NULL_VOID(gestureObject);
    gestureObject->SetAllowedTypes(Converter::Convert<std::set<SourceTool>>(*types));
}
void AddGestureToNodeImpl(Ark_NativePointer node, const Ark_Number* priority, Ark_GestureMask mask,
    Ark_NativePointer gesture, Ark_Boolean isModifier)
{
    // auto* frameNode = reinterpret_cast<FrameNode*>(node);
    // CHECK_NULL_VOID(frameNode);
    // auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    // auto gesturePtr = Referenced::Claim(reinterpret_cast<Gesture*>(gesture));
    // bool isModifierValue = Converter::Convert<bool>(isModifier);
    // GesturePriority gesturePriority = static_cast<GesturePriority>(Converter::Convert<int32_t>(*priority));
    // gesturePtr->SetPriority(gesturePriority);

    // GestureMask gestureMask = Converter::Convert<std::optional<GestureMask>>(mask).value_or(GestureMask::Normal);
    // gesturePtr->SetGestureMask(gestureMask);
    // if (isModifierValue) {
    //     gestureHub->AttachGesture(gesturePtr);
    // } else {
    //     gestureHub->AddGesture(gesturePtr);
    //     GestureEventFunc clickEvent = GestureModelNG::GetTapGestureEventFunc(gesturePtr);
    //     if (clickEvent) {
    //         auto focusHub = frameNode->GetOrCreateFocusHub();
    //         CHECK_NULL_VOID(focusHub);
    //         focusHub->SetFocusable(true, false);
    //         focusHub->SetOnClickCallback(std::move(clickEvent));
    //     }
    // }
    // // Gesture ptr ref count is not decrease, so need to decrease after attach to gestureEventHub.
    // gesturePtr->DecRefCount();
}
void AddGestureToGroupImpl(Ark_NativePointer group, Ark_NativePointer gesture)
{
    auto* gestureGroup = reinterpret_cast<GestureGroup*>(group);
    CHECK_NULL_VOID(gestureGroup);
    auto* gesturePtr = reinterpret_cast<Gesture*>(gesture);
    CHECK_NULL_VOID(gesturePtr);
    gestureGroup->AddGesture(AceType::Claim(gesturePtr));
    gesturePtr->DecRefCount();
}
void RemoveGestureByTagImpl(Ark_NativePointer node, const Ark_String* tag)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    std::string gestureTag = Converter::Convert<std::string>(*tag);
    gestureHub->RemoveGesturesByTag(gestureTag);
}
void ClearGesturesImpl(Ark_NativePointer node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    gestureHub->ClearModifierGesture();
}
} // namespace GestureOpsAccessor

const GENERATED_ArkUIGestureOpsAccessor* GetGestureOpsAccessor()
{
    static const GENERATED_ArkUIGestureOpsAccessor GestureOpsAccessorImpl {
        GestureOpsAccessor::CreateTapGestureImpl,
        GestureOpsAccessor::CreateLongPressGestureImpl,
        GestureOpsAccessor::CreatePanGestureImpl,
        GestureOpsAccessor::CreatePanGestureWithPanGestureOptionsImpl,
        GestureOpsAccessor::CreatePinchGestureImpl,
        GestureOpsAccessor::CreateRotationGestureImpl,
        GestureOpsAccessor::CreateSwipeGestureImpl,
        GestureOpsAccessor::CreateGestureGroupImpl,
        GestureOpsAccessor::SetOnActionImpl,
        GestureOpsAccessor::SetOnActionStartImpl,
        GestureOpsAccessor::SetOnActionUpdateImpl,
        GestureOpsAccessor::SetOnActionEndImpl,
        GestureOpsAccessor::SetOnActionCancelImpl,
        GestureOpsAccessor::SetOnCancelImpl,
        GestureOpsAccessor::SetGestureTagImpl,
        GestureOpsAccessor::SetAllowedTypesImpl,
        GestureOpsAccessor::AddGestureToNodeImpl,
        GestureOpsAccessor::AddGestureToGroupImpl,
        GestureOpsAccessor::RemoveGestureByTagImpl,
        GestureOpsAccessor::ClearGesturesImpl,
    };
    return &GestureOpsAccessorImpl;
}

} // namespace OHOS::Ace::NG::GeneratedModifier
