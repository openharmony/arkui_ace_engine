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
#include "core/interfaces/arkoala/arkoala_api.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

struct GestureOpsPeer {
    virtual ~GestureOpsPeer() = default;
};

namespace OHOS::Ace::NG::GeneratedModifier {
namespace GestureOpsAccessor {
Ark_GestureOps CtorImpl()
{
    return new GestureOpsPeer();
}

void DestroyPeerImpl(GestureOpsPeer* peer)
{
    delete peer;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void*>(&DestroyPeerImpl);
}

Ark_NativePointer CreateTapGestureImpl(const Ark_Number* fingers, const Ark_Number* count,
    const Ark_Number* distanceThreshold, Ark_Boolean isFingerCountLimited)
{
    int32_t fingerValue = Converter::Convert<int32_t>(*fingers);
    int32_t countValue = Converter::Convert<int32_t>(*count);
    auto tapGestureObject =
        AceType::MakeRefPtr<TapGesture>(countValue, fingerValue, std::numeric_limits<double>::infinity());
    tapGestureObject->IncRefCount();
    return AceType::RawPtr(tapGestureObject);
}
Ark_NativePointer CreateLongPressGestureImpl(
    const Ark_Number* fingers, Ark_Boolean repeat, const Ark_Number* duration, Ark_Boolean isFingerCountLimited)
{
    int32_t fingerValue = Converter::Convert<int32_t>(*fingers);
    bool repeatValue = Converter::Convert<bool>(repeat);
    int32_t durationValue = Converter::Convert<int32_t>(*duration);
    auto longPressGestureObject = AceType::MakeRefPtr<LongPressGesture>(fingerValue, repeatValue, durationValue);
    longPressGestureObject->IncRefCount();
    return AceType::RawPtr(longPressGestureObject);
}
Ark_NativePointer CreatePanGestureImpl(
    const Ark_Number* fingers, Ark_PanDirection direction, const Ark_Number* distance, Ark_Boolean isFingerCountLimited)
{
    int32_t fingerValue = Converter::Convert<int32_t>(*fingers);
    // TODO: direction need to adapt
    PanDirection panDirection;
    panDirection.type = PanDirection::ALL;
    double distanceValue = Converter::Convert<double>(*distance);
    auto panGestureObject = AceType::MakeRefPtr<PanGesture>(fingerValue, panDirection, distanceValue);
    panGestureObject->IncRefCount();
    return AceType::RawPtr(panGestureObject);
}
Ark_NativePointer CreatePinchGestureImpl(
    const Ark_Number* fingers, const Ark_Number* distance, Ark_Boolean isFingerCountLimited)
{
    int32_t fingerValue = Converter::Convert<int32_t>(*fingers);
    double distanceValue = Converter::Convert<double>(*distance);
    auto pinchGestureObject = AceType::MakeRefPtr<PinchGesture>(fingerValue, distanceValue);
    pinchGestureObject->IncRefCount();
    return AceType::RawPtr(pinchGestureObject);
}
Ark_NativePointer CreateRotationGestureImpl(
    const Ark_Number* fingers, const Ark_Number* angle, Ark_Boolean isFingerCountLimited)
{
    int32_t fingerValue = Converter::Convert<int32_t>(*fingers);
    double angleValue = Converter::Convert<double>(*angle);
    auto rotationGestureObject = AceType::MakeRefPtr<RotationGesture>(fingerValue, angleValue);
    rotationGestureObject->IncRefCount();
    return AceType::RawPtr(rotationGestureObject);
}
Ark_NativePointer CreateSwipeGestureImpl(
    const Ark_Number* fingers, Ark_SwipeDirection direction, const Ark_Number* speed, Ark_Boolean isFingerCountLimited)
{
    int32_t fingerValue = Converter::Convert<int32_t>(*fingers);
    // TODO: direction need to adapt
    SwipeDirection swipeDirection;
    swipeDirection.type = SwipeDirection::ALL;
    double speedValue = Converter::Convert<double>(*speed);
    auto swipeGestureObject = AceType::MakeRefPtr<SwipeGesture>(fingerValue, swipeDirection, speedValue);
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
void SetOnActionCancelImpl(Ark_NativePointer gesture, const Callback_Void* onActionCancel)
{
    // LOGE("zcb SetOnActionCancelImpl");
    // auto* gesturePtr = reinterpret_cast<Gesture*>(gesture);
    // CHECK_NULL_VOID(gesturePtr);
    // auto onActionCancelEvent = [callback = CallbackHelper(*onActionCancel)]() {
    //     LOGE("zcb SetOnActionCancelImpl onActionEvent trigger");
    //     callback.InvokeSync();
    // };
    // gesturePtr->SetOnActionCancelId(onActionCancelEvent);
}
void SetGestureTagImpl(Ark_NativePointer gesture, const Ark_String* tag)
{
    auto* gestureObject = reinterpret_cast<Gesture*>(gesture);
    CHECK_NULL_VOID(gestureObject);
    gestureObject->SetTag(Converter::Convert<std::string>(*tag));
}
void SetAllowedTypesImpl(Ark_NativePointer gesture, const Array_SourceTool* types) {}
void AddGestureToNodeImpl(
    Ark_NativePointer node, const Ark_Number* priority, Ark_GestureMask mask, Ark_NativePointer gesture)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    auto gesturePtr = Referenced::Claim(reinterpret_cast<Gesture*>(gesture));

    GesturePriority gesturePriority = static_cast<GesturePriority>(Converter::Convert<int32_t>(*priority));
    gesturePtr->SetPriority(gesturePriority);

    GestureMask gestureMask = Converter::Convert<std::optional<GestureMask>>(mask).value_or(GestureMask::Normal);
    gesturePtr->SetGestureMask(gestureMask);
    gestureHub->AttachGesture(gesturePtr);
    // Gesture ptr ref count is not decrease, so need to decrease after attach to gestureEventHub.
    gesturePtr->DecRefCount();
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
} // namespace GestureOpsAccessor

const GENERATED_ArkUIGestureOpsAccessor* GetGestureOpsAccessor()
{
    static const GENERATED_ArkUIGestureOpsAccessor GestureOpsAccessorImpl {
        GestureOpsAccessor::DestroyPeerImpl,
        GestureOpsAccessor::CtorImpl,
        GestureOpsAccessor::GetFinalizerImpl,
        GestureOpsAccessor::CreateTapGestureImpl,
        GestureOpsAccessor::CreateLongPressGestureImpl,
        GestureOpsAccessor::CreatePanGestureImpl,
        GestureOpsAccessor::CreatePinchGestureImpl,
        GestureOpsAccessor::CreateRotationGestureImpl,
        GestureOpsAccessor::CreateSwipeGestureImpl,
        GestureOpsAccessor::CreateGestureGroupImpl,
        GestureOpsAccessor::SetOnActionImpl,
        GestureOpsAccessor::SetOnActionStartImpl,
        GestureOpsAccessor::SetOnActionUpdateImpl,
        GestureOpsAccessor::SetOnActionEndImpl,
        GestureOpsAccessor::SetOnActionCancelImpl,
        GestureOpsAccessor::SetGestureTagImpl,
        GestureOpsAccessor::SetAllowedTypesImpl,
        GestureOpsAccessor::AddGestureToNodeImpl,
        GestureOpsAccessor::AddGestureToGroupImpl,
    };
    return &GestureOpsAccessorImpl;
}

} // namespace OHOS::Ace::NG::GeneratedModifier
