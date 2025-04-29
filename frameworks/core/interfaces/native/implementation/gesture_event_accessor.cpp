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
#include "core/interfaces/native/implementation/gesture_event_peer.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace GestureEventAccessor {
void DestroyPeerImpl(Ark_GestureEvent peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_GestureEvent CtorImpl()
{
    return PeerUtils::CreatePeer<GestureEventPeer>();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Boolean GetRepeatImpl(Ark_GestureEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Boolean>(false);
    CHECK_NULL_RETURN(peer, errValue);
    GestureEvent* event = peer->GetEventInfo();
    CHECK_NULL_RETURN(event, errValue);

    return event->GetRepeat();
}
void SetRepeatImpl(Ark_GestureEvent peer,
                   Ark_Boolean repeat)
{
    CHECK_NULL_VOID(peer);
    GestureEvent* event = peer->GetEventInfo();
    CHECK_NULL_VOID(event);

    auto convValue = Converter::Convert<bool>(repeat);
    event->SetRepeat(convValue);
}
Array_FingerInfo GetFingerListImpl(Ark_GestureEvent peer)
{
    CHECK_NULL_RETURN(peer, {});
    auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, {});
    const std::list<FingerInfo>& fingerList = info->GetFingerList();
    return Converter::ArkValue<Array_FingerInfo>(fingerList, Converter::FC);
}
void SetFingerListImpl(Ark_GestureEvent peer,
                       const Array_FingerInfo* fingerList)
{
    CHECK_NULL_VOID(peer);
    GestureEvent* event = peer->GetEventInfo();
    CHECK_NULL_VOID(event);
    CHECK_NULL_VOID(fingerList);

    auto convValue = Converter::Convert<std::list<FingerInfo>>(*fingerList);
    event->SetFingerList(convValue);
}
Ark_Number GetOffsetXImpl(Ark_GestureEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer, errValue);
    GestureEvent* event = peer->GetEventInfo();
    CHECK_NULL_RETURN(event, errValue);

    double value = PipelineBase::Px2VpWithCurrentDensity(event->GetOffsetX());
    return Converter::ArkValue<Ark_Number>(value);
}
void SetOffsetXImpl(Ark_GestureEvent peer,
                    const Ark_Number* offsetX)
{
    CHECK_NULL_VOID(peer);
    GestureEvent* event = peer->GetEventInfo();
    CHECK_NULL_VOID(event);
    CHECK_NULL_VOID(offsetX);

    auto convValue = Converter::Convert<float>(*offsetX);
    event->SetOffsetX(PipelineBase::Vp2PxWithCurrentDensity(convValue));
}
Ark_Number GetOffsetYImpl(Ark_GestureEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer, errValue);
    GestureEvent* event = peer->GetEventInfo();
    CHECK_NULL_RETURN(event, errValue);

    double value = PipelineBase::Px2VpWithCurrentDensity(event->GetOffsetY());
    return Converter::ArkValue<Ark_Number>(value);
}
void SetOffsetYImpl(Ark_GestureEvent peer,
                    const Ark_Number* offsetY)
{
    CHECK_NULL_VOID(peer);
    GestureEvent* event = peer->GetEventInfo();
    CHECK_NULL_VOID(event);
    CHECK_NULL_VOID(offsetY);

    auto convValue = Converter::Convert<float>(*offsetY);
    event->SetOffsetY(PipelineBase::Vp2PxWithCurrentDensity(convValue));
}
Ark_Number GetAngleImpl(Ark_GestureEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer, errValue);
    GestureEvent* event = peer->GetEventInfo();
    CHECK_NULL_RETURN(event, errValue);

    double value = event->GetAngle();
    return Converter::ArkValue<Ark_Number>(value);
}
void SetAngleImpl(Ark_GestureEvent peer,
                  const Ark_Number* angle)
{
    CHECK_NULL_VOID(peer);
    GestureEvent* event = peer->GetEventInfo();
    CHECK_NULL_VOID(event);
    CHECK_NULL_VOID(angle);

    auto convValue = Converter::Convert<float>(*angle);
    event->SetAngle(convValue);
}
Ark_Number GetSpeedImpl(Ark_GestureEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer, errValue);
    GestureEvent* event = peer->GetEventInfo();
    CHECK_NULL_RETURN(event, errValue);

    double value = event->GetSpeed();
    return Converter::ArkValue<Ark_Number>(value);
}
void SetSpeedImpl(Ark_GestureEvent peer,
                  const Ark_Number* speed)
{
    CHECK_NULL_VOID(peer);
    GestureEvent* event = peer->GetEventInfo();
    CHECK_NULL_VOID(event);
    CHECK_NULL_VOID(speed);

    auto convValue = Converter::Convert<float>(*speed);
    event->SetSpeed(convValue);
}
Ark_Number GetScaleImpl(Ark_GestureEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer, errValue);
    GestureEvent* event = peer->GetEventInfo();
    CHECK_NULL_RETURN(event, errValue);

    double value = event->GetScale();
    return Converter::ArkValue<Ark_Number>(value);
}
void SetScaleImpl(Ark_GestureEvent peer,
                  const Ark_Number* scale)
{
    CHECK_NULL_VOID(peer);
    GestureEvent* event = peer->GetEventInfo();
    CHECK_NULL_VOID(event);
    CHECK_NULL_VOID(scale);

    auto convValue = Converter::Convert<float>(*scale);
    event->SetScale(convValue);
}
Ark_Number GetPinchCenterXImpl(Ark_GestureEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer, errValue);
    GestureEvent* event = peer->GetEventInfo();
    CHECK_NULL_RETURN(event, errValue);

    double value = PipelineBase::Px2VpWithCurrentDensity(event->GetPinchCenter().GetX());
    return Converter::ArkValue<Ark_Number>(value);
}
void SetPinchCenterXImpl(Ark_GestureEvent peer,
                         const Ark_Number* pinchCenterX)
{
    CHECK_NULL_VOID(peer);
    GestureEvent* event = peer->GetEventInfo();
    CHECK_NULL_VOID(event);
    CHECK_NULL_VOID(pinchCenterX);

    auto convValue = Converter::Convert<float>(*pinchCenterX);
    Offset pinchCenter;
    pinchCenter.SetX(PipelineBase::Vp2PxWithCurrentDensity(convValue));
    pinchCenter.SetY(event->GetPinchCenter().GetY());
    event->SetPinchCenter(pinchCenter);
}
Ark_Number GetPinchCenterYImpl(Ark_GestureEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer, errValue);
    GestureEvent* event = peer->GetEventInfo();
    CHECK_NULL_RETURN(event, errValue);

    double value = PipelineBase::Px2VpWithCurrentDensity(event->GetPinchCenter().GetY());
    return Converter::ArkValue<Ark_Number>(value);
}
void SetPinchCenterYImpl(Ark_GestureEvent peer,
                         const Ark_Number* pinchCenterY)
{
    CHECK_NULL_VOID(peer);
    GestureEvent* event = peer->GetEventInfo();
    CHECK_NULL_VOID(event);
    CHECK_NULL_VOID(pinchCenterY);

    auto convValue = Converter::Convert<float>(*pinchCenterY);
    Offset pinchCenter;
    pinchCenter.SetX(event->GetPinchCenter().GetX());
    pinchCenter.SetY(PipelineBase::Vp2PxWithCurrentDensity(convValue));
    event->SetPinchCenter(pinchCenter);
}
Ark_Number GetVelocityXImpl(Ark_GestureEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer, errValue);
    GestureEvent* event = peer->GetEventInfo();
    CHECK_NULL_RETURN(event, errValue);

    double value = PipelineBase::Px2VpWithCurrentDensity(event->GetVelocity().GetVelocityX());
    return Converter::ArkValue<Ark_Number>(value);
}
void SetVelocityXImpl(Ark_GestureEvent peer,
                      const Ark_Number* velocityX)
{
    CHECK_NULL_VOID(peer);
    GestureEvent* event = peer->GetEventInfo();
    CHECK_NULL_VOID(event);
    CHECK_NULL_VOID(velocityX);

    auto convValue = Converter::Convert<float>(*velocityX);
    Offset offsetPerSecond = event->GetVelocity().GetOffsetPerSecond();
    offsetPerSecond.SetX(PipelineBase::Vp2PxWithCurrentDensity(convValue));
    event->SetVelocity(Velocity(offsetPerSecond));
}
Ark_Number GetVelocityYImpl(Ark_GestureEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer, errValue);
    GestureEvent* event = peer->GetEventInfo();
    CHECK_NULL_RETURN(event, errValue);

    double value = PipelineBase::Px2VpWithCurrentDensity(event->GetVelocity().GetVelocityY());
    return Converter::ArkValue<Ark_Number>(value);
}
void SetVelocityYImpl(Ark_GestureEvent peer,
                      const Ark_Number* velocityY)
{
    CHECK_NULL_VOID(peer);
    GestureEvent* event = peer->GetEventInfo();
    CHECK_NULL_VOID(event);
    CHECK_NULL_VOID(velocityY);

    auto convValue = Converter::Convert<float>(*velocityY);
    Offset offsetPerSecond = event->GetVelocity().GetOffsetPerSecond();
    offsetPerSecond.SetY(PipelineBase::Vp2PxWithCurrentDensity(convValue));
    event->SetVelocity(Velocity(offsetPerSecond));
}
Ark_Number GetVelocityImpl(Ark_GestureEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer, errValue);
    GestureEvent* event = peer->GetEventInfo();
    CHECK_NULL_RETURN(event, errValue);

    double value = PipelineBase::Px2VpWithCurrentDensity(event->GetVelocity().GetVelocityValue());
    return Converter::ArkValue<Ark_Number>(value);
}
void SetVelocityImpl(Ark_GestureEvent peer,
                     const Ark_Number* velocity)
{
    LOGE("GestureEventAccessor::SetVelocityImpl not implemented");
}
} // GestureEventAccessor
const GENERATED_ArkUIGestureEventAccessor* GetGestureEventAccessor()
{
    static const GENERATED_ArkUIGestureEventAccessor GestureEventAccessorImpl {
        GestureEventAccessor::DestroyPeerImpl,
        GestureEventAccessor::CtorImpl,
        GestureEventAccessor::GetFinalizerImpl,
        GestureEventAccessor::GetRepeatImpl,
        GestureEventAccessor::SetRepeatImpl,
        GestureEventAccessor::GetFingerListImpl,
        GestureEventAccessor::SetFingerListImpl,
        GestureEventAccessor::GetOffsetXImpl,
        GestureEventAccessor::SetOffsetXImpl,
        GestureEventAccessor::GetOffsetYImpl,
        GestureEventAccessor::SetOffsetYImpl,
        GestureEventAccessor::GetAngleImpl,
        GestureEventAccessor::SetAngleImpl,
        GestureEventAccessor::GetSpeedImpl,
        GestureEventAccessor::SetSpeedImpl,
        GestureEventAccessor::GetScaleImpl,
        GestureEventAccessor::SetScaleImpl,
        GestureEventAccessor::GetPinchCenterXImpl,
        GestureEventAccessor::SetPinchCenterXImpl,
        GestureEventAccessor::GetPinchCenterYImpl,
        GestureEventAccessor::SetPinchCenterYImpl,
        GestureEventAccessor::GetVelocityXImpl,
        GestureEventAccessor::SetVelocityXImpl,
        GestureEventAccessor::GetVelocityYImpl,
        GestureEventAccessor::SetVelocityYImpl,
        GestureEventAccessor::GetVelocityImpl,
        GestureEventAccessor::SetVelocityImpl,
    };
    return &GestureEventAccessorImpl;
}

}
