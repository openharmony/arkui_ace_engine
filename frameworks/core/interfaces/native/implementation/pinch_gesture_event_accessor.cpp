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

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/implementation/pinch_gesture_event_peer.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace PinchGestureEventAccessor {
void DestroyPeerImpl(Ark_PinchGestureEvent peer)
{
    delete peer;
}
Ark_PinchGestureEvent CtorImpl()
{
    return new PinchGestureEventPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Number GetScaleImpl(Ark_PinchGestureEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer, errValue);
    PinchGestureEvent* event = peer->GetEventInfo();
    CHECK_NULL_RETURN(event, errValue);
    LOGW("ARKOALA PinchGestureEventAccessor::GetScaleImpl returns Ark_Int32, "
        "but should return Ark_Number.");
    double value = event->GetScale();
    return Converter::ArkValue<Ark_Number>(static_cast<int32_t>(value));
}
void SetScaleImpl(Ark_PinchGestureEvent peer,
                  const Ark_Number* scale)
{
    CHECK_NULL_VOID(peer);
    PinchGestureEvent* event = peer->GetEventInfo();
    CHECK_NULL_VOID(event);
    CHECK_NULL_VOID(scale);

    auto convValue = Converter::Convert<float>(*scale);
    event->SetScale(convValue);
}
Ark_Number GetPinchCenterXImpl(Ark_PinchGestureEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer, errValue);
    PinchGestureEvent* event = peer->GetEventInfo();
    CHECK_NULL_RETURN(event, errValue);
    LOGW("ARKOALA PinchGestureEventAccessor::GetPinchCenterXImpl returns Ark_Int32, "
        "but should return Ark_Number.");
    double value = PipelineBase::Px2VpWithCurrentDensity(event->GetPinchCenter().GetX());
    return Converter::ArkValue<Ark_Number>(static_cast<int32_t>(value));
}
void SetPinchCenterXImpl(Ark_PinchGestureEvent peer,
                         const Ark_Number* pinchCenterX)
{
    CHECK_NULL_VOID(peer);
    PinchGestureEvent* event = peer->GetEventInfo();
    CHECK_NULL_VOID(event);
    CHECK_NULL_VOID(pinchCenterX);

    auto convValue = Converter::Convert<float>(*pinchCenterX);
    Offset pinchCenter;
    pinchCenter.SetX(PipelineBase::Vp2PxWithCurrentDensity(convValue));
    pinchCenter.SetY(event->GetPinchCenter().GetY());
    event->SetPinchCenter(pinchCenter);
}
Ark_Number GetPinchCenterYImpl(Ark_PinchGestureEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer, errValue);
    PinchGestureEvent* event = peer->GetEventInfo();
    CHECK_NULL_RETURN(event, errValue);
    LOGW("ARKOALA PinchGestureEventAccessor::GetPinchCenterYImpl returns Ark_Int32, "
        "but should return Ark_Number.");
    double value = PipelineBase::Px2VpWithCurrentDensity(event->GetPinchCenter().GetY());
    return Converter::ArkValue<Ark_Number>(static_cast<int32_t>(value));
}
void SetPinchCenterYImpl(Ark_PinchGestureEvent peer,
                         const Ark_Number* pinchCenterY)
{
    CHECK_NULL_VOID(peer);
    PinchGestureEvent* event = peer->GetEventInfo();
    CHECK_NULL_VOID(event);
    CHECK_NULL_VOID(pinchCenterY);

    auto convValue = Converter::Convert<float>(*pinchCenterY);
    Offset pinchCenter;
    pinchCenter.SetX(event->GetPinchCenter().GetX());
    pinchCenter.SetY(PipelineBase::Vp2PxWithCurrentDensity(convValue));
    event->SetPinchCenter(pinchCenter);
}
} // PinchGestureEventAccessor
const GENERATED_ArkUIPinchGestureEventAccessor* GetPinchGestureEventAccessor()
{
    static const GENERATED_ArkUIPinchGestureEventAccessor PinchGestureEventAccessorImpl {
        PinchGestureEventAccessor::DestroyPeerImpl,
        PinchGestureEventAccessor::CtorImpl,
        PinchGestureEventAccessor::GetFinalizerImpl,
        PinchGestureEventAccessor::GetScaleImpl,
        PinchGestureEventAccessor::SetScaleImpl,
        PinchGestureEventAccessor::GetPinchCenterXImpl,
        PinchGestureEventAccessor::SetPinchCenterXImpl,
        PinchGestureEventAccessor::GetPinchCenterYImpl,
        PinchGestureEventAccessor::SetPinchCenterYImpl,
    };
    return &PinchGestureEventAccessorImpl;
}
}
