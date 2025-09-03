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
#include "core/interfaces/native/implementation/pan_gesture_event_peer.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace PanGestureEventAccessor {
void DestroyPeerImpl(Ark_PanGestureEvent peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_PanGestureEvent CtorImpl()
{
    return PeerUtils::CreatePeer<PanGestureEventPeer>();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Number GetOffsetXImpl(Ark_PanGestureEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer, errValue);
    auto* event = peer->GetEventInfo();
    CHECK_NULL_RETURN(event, errValue);
    PanGestureEvent* panGestureEvent = TypeInfoHelper::DynamicCast<PanGestureEvent>(event);
    CHECK_NULL_RETURN(panGestureEvent, errValue);

    double value = PipelineBase::Px2VpWithCurrentDensity(panGestureEvent->GetOffsetX());
    return Converter::ArkValue<Ark_Number>(value);
}
void SetOffsetXImpl(Ark_PanGestureEvent peer,
                    const Ark_Number* offsetX)
{
    CHECK_NULL_VOID(peer);
    auto* event = peer->GetEventInfo();
    CHECK_NULL_VOID(event);
    CHECK_NULL_VOID(offsetX);
    PanGestureEvent* panGestureEvent = TypeInfoHelper::DynamicCast<PanGestureEvent>(event);
    CHECK_NULL_VOID(panGestureEvent);

    auto convValue = Converter::Convert<float>(*offsetX);
    panGestureEvent->SetOffsetX(PipelineBase::Vp2PxWithCurrentDensity(convValue));
}
Ark_Number GetOffsetYImpl(Ark_PanGestureEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer, errValue);
    auto* event = peer->GetEventInfo();
    CHECK_NULL_RETURN(event, errValue);
    PanGestureEvent* panGestureEvent = TypeInfoHelper::DynamicCast<PanGestureEvent>(event);
    CHECK_NULL_RETURN(panGestureEvent, errValue);

    double value = PipelineBase::Px2VpWithCurrentDensity(panGestureEvent->GetOffsetY());
    return Converter::ArkValue<Ark_Number>(value);
}
void SetOffsetYImpl(Ark_PanGestureEvent peer,
                    const Ark_Number* offsetY)
{
    CHECK_NULL_VOID(peer);
    auto* event = peer->GetEventInfo();
    CHECK_NULL_VOID(event);
    CHECK_NULL_VOID(offsetY);
    PanGestureEvent* panGestureEvent = TypeInfoHelper::DynamicCast<PanGestureEvent>(event);
    CHECK_NULL_VOID(panGestureEvent);

    auto convValue = Converter::Convert<float>(*offsetY);
    panGestureEvent->SetOffsetY(PipelineBase::Vp2PxWithCurrentDensity(convValue));
}
Ark_Number GetVelocityXImpl(Ark_PanGestureEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer, errValue);
    auto* event = peer->GetEventInfo();
    CHECK_NULL_RETURN(event, errValue);
    PanGestureEvent* panGestureEvent = TypeInfoHelper::DynamicCast<PanGestureEvent>(event);
    CHECK_NULL_RETURN(panGestureEvent, errValue);

    double value = PipelineBase::Px2VpWithCurrentDensity(panGestureEvent->GetVelocity().GetVelocityX());
    return Converter::ArkValue<Ark_Number>(value);
}
void SetVelocityXImpl(Ark_PanGestureEvent peer,
                      const Ark_Number* velocityX)
{
    CHECK_NULL_VOID(peer);
    auto* event = peer->GetEventInfo();
    CHECK_NULL_VOID(event);
    CHECK_NULL_VOID(velocityX);
    PanGestureEvent* panGestureEvent = TypeInfoHelper::DynamicCast<PanGestureEvent>(event);
    CHECK_NULL_VOID(panGestureEvent);

    auto convValue = Converter::Convert<float>(*velocityX);
    Offset offsetPerSecond = panGestureEvent->GetVelocity().GetOffsetPerSecond();
    offsetPerSecond.SetX(PipelineBase::Vp2PxWithCurrentDensity(convValue));
    panGestureEvent->SetVelocity(Velocity(offsetPerSecond));
}
Ark_Number GetVelocityYImpl(Ark_PanGestureEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer, errValue);
    auto* event = peer->GetEventInfo();
    CHECK_NULL_RETURN(event, errValue);
    PanGestureEvent* panGestureEvent = TypeInfoHelper::DynamicCast<PanGestureEvent>(event);
    CHECK_NULL_RETURN(panGestureEvent, errValue);

    double value = PipelineBase::Px2VpWithCurrentDensity(panGestureEvent->GetVelocity().GetVelocityY());
    return Converter::ArkValue<Ark_Number>(value);
}
void SetVelocityYImpl(Ark_PanGestureEvent peer,
                      const Ark_Number* velocityY)
{
    CHECK_NULL_VOID(peer);
    auto* event = peer->GetEventInfo();
    CHECK_NULL_VOID(event);
    CHECK_NULL_VOID(velocityY);
    PanGestureEvent* panGestureEvent = TypeInfoHelper::DynamicCast<PanGestureEvent>(event);
    CHECK_NULL_VOID(panGestureEvent);

    auto convValue = Converter::Convert<float>(*velocityY);
    Offset offsetPerSecond = panGestureEvent->GetVelocity().GetOffsetPerSecond();
    offsetPerSecond.SetY(PipelineBase::Vp2PxWithCurrentDensity(convValue));
    panGestureEvent->SetVelocity(Velocity(offsetPerSecond));
}
Ark_Number GetVelocityImpl(Ark_PanGestureEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer, errValue);
    auto* event = peer->GetEventInfo();
    CHECK_NULL_RETURN(event, errValue);
    PanGestureEvent* panGestureEvent = TypeInfoHelper::DynamicCast<PanGestureEvent>(event);
    CHECK_NULL_RETURN(panGestureEvent, errValue);

    double value = PipelineBase::Px2VpWithCurrentDensity(panGestureEvent->GetVelocity().GetVelocityValue());
    return Converter::ArkValue<Ark_Number>(value);
}
void SetVelocityImpl(Ark_PanGestureEvent peer,
                     const Ark_Number* velocity)
{
    CHECK_NULL_VOID(peer);
    auto* event = peer->GetEventInfo();
    CHECK_NULL_VOID(event);
    CHECK_NULL_VOID(velocity);
    PanGestureEvent* panGestureEvent = TypeInfoHelper::DynamicCast<PanGestureEvent>(event);
    CHECK_NULL_VOID(panGestureEvent);

    auto convValue = Converter::Convert<float>(*velocity);
    Offset offsetPerSecond = panGestureEvent->GetVelocity().GetOffsetPerSecond();
    offsetPerSecond.SetX(PipelineBase::Vp2PxWithCurrentDensity(convValue));
    offsetPerSecond.SetY(PipelineBase::Vp2PxWithCurrentDensity(convValue));
    panGestureEvent->SetVelocity(Velocity(offsetPerSecond));
}
} // PanGestureEventAccessor
const GENERATED_ArkUIPanGestureEventAccessor* GetPanGestureEventAccessor()
{
    static const GENERATED_ArkUIPanGestureEventAccessor PanGestureEventAccessorImpl {
        PanGestureEventAccessor::DestroyPeerImpl,
        PanGestureEventAccessor::CtorImpl,
        PanGestureEventAccessor::GetFinalizerImpl,
        PanGestureEventAccessor::GetOffsetXImpl,
        PanGestureEventAccessor::SetOffsetXImpl,
        PanGestureEventAccessor::GetOffsetYImpl,
        PanGestureEventAccessor::SetOffsetYImpl,
        PanGestureEventAccessor::GetVelocityXImpl,
        PanGestureEventAccessor::SetVelocityXImpl,
        PanGestureEventAccessor::GetVelocityYImpl,
        PanGestureEventAccessor::SetVelocityYImpl,
        PanGestureEventAccessor::GetVelocityImpl,
        PanGestureEventAccessor::SetVelocityImpl,
    };
    return &PanGestureEventAccessorImpl;
}

}
