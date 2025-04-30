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
#include "arkoala_api_generated.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/implementation/base_event_peer.h"

namespace OHOS::Ace::NG {

namespace Converter {
template<>
void AssignCast(std::optional<SourceType>& dst, const Ark_SourceType& src)
{
    switch (src) {
        case ARK_SOURCE_TYPE_UNKNOWN: dst = SourceType::NONE; break;
        case ARK_SOURCE_TYPE_MOUSE: dst = SourceType::MOUSE; break;
        case ARK_SOURCE_TYPE_TOUCH_SCREEN: dst = SourceType::TOUCH; break;
        default: LOGE("Unexpected enum value in Ark_SourceType: %{public}d", src);
    }
}
template<>
void AssignCast(std::optional<SourceTool>& dst, const Ark_SourceTool& src)
{
    switch (src) {
        case ARK_SOURCE_TOOL_UNKNOWN: dst = SourceTool::UNKNOWN; break;
        case ARK_SOURCE_TOOL_FINGER: dst = SourceTool::FINGER; break;
        case ARK_SOURCE_TOOL_PEN: dst = SourceTool::PEN; break;
        case ARK_SOURCE_TOOL_MOUSE: dst = SourceTool::MOUSE; break;
        case ARK_SOURCE_TOOL_TOUCHPAD: dst = SourceTool::TOUCHPAD; break;
        case ARK_SOURCE_TOOL_JOYSTICK: dst = SourceTool::JOYSTICK; break;
        default: LOGE("Unexpected enum value in Ark_SourceTool: %{public}d", src);
    }
}
} // namespace Converter

namespace GeneratedModifier {

namespace BaseEventAccessor {

namespace {
const Ark_Boolean DefaultValueBoolean = Converter::ArkValue<Ark_Boolean>(false);
const Ark_Number DefaultValueArkNumber = Converter::ArkValue<Ark_Number>(0);
const Ark_Int64 DefaultValueArkInt = Converter::ArkValue<Ark_Int64>(0);
}  // namespace

void DestroyPeerImpl(Ark_BaseEvent peer)
{
    delete peer;
}
Ark_BaseEvent CtorImpl()
{
    return new BaseEventPeerImpl();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Boolean GetModifierKeyStateImpl(Ark_VMContext vmContext,
                                    Ark_BaseEvent peer,
                                    const Array_String* keys)
{
    return {};
}
Ark_EventTarget GetTargetImpl(Ark_BaseEvent peer)
{
    CHECK_NULL_RETURN(peer && peer->GetBaseInfo(), {});
    return Converter::ArkValue<Ark_EventTarget>(peer->GetBaseInfo()->GetTarget());
}
void SetTargetImpl(Ark_BaseEvent peer,
                   const Ark_EventTarget* target)
{
}
Ark_Int64 GetTimestampImpl(Ark_BaseEvent peer)
{
    CHECK_NULL_RETURN(peer && peer->GetBaseInfo(), DefaultValueArkInt);
    auto tstamp = std::chrono::duration_cast<std::chrono::nanoseconds>(
        peer->GetBaseInfo()->GetTimeStamp().time_since_epoch()).count();
    LOGE("BaseEventAccessor.GetTimestampImpl returns Ark_Int64");
    return Converter::ArkValue<Ark_Int64>(static_cast<int32_t>(tstamp));
}
void SetTimestampImpl(Ark_BaseEvent peer,
                      Ark_Int64 timestamp)
{
    CHECK_NULL_VOID(peer && peer->GetBaseInfo());
    CHECK_NULL_VOID(timestamp);
    LOGE("BaseEventAccessor.SetTimestampImpl uses Ark_Int64");
    int64_t value = Converter::Convert<int64_t>(timestamp);
    std::chrono::high_resolution_clock::duration duration = std::chrono::nanoseconds(value);
    std::chrono::time_point<std::chrono::high_resolution_clock> time_point(duration);
    peer->GetBaseInfo()->SetTimeStamp(time_point);
}
Ark_SourceType GetSourceImpl(Ark_BaseEvent peer)
{
    CHECK_NULL_RETURN(peer && peer->GetBaseInfo(), static_cast<Ark_SourceType>(-1));
    auto value = peer->GetBaseInfo()->GetSourceDevice();
    return Converter::ArkValue<Ark_SourceType>(value);
}
void SetSourceImpl(Ark_BaseEvent peer,
                   Ark_SourceType source)
{
    CHECK_NULL_VOID(peer && peer->GetBaseInfo());
    auto value = Converter::OptConvert<SourceType>(source);
    if (value) {
        peer->GetBaseInfo()->SetSourceDevice(*value);
    }
}
Opt_Number GetAxisHorizontalImpl(Ark_BaseEvent peer)
{
    LOGE("BaseEventAccessor.GetAxisHorizontalImpl does nothing");
    return {};
}
void SetAxisHorizontalImpl(Ark_BaseEvent peer,
                           const Ark_Number* axisHorizontal)
{
    LOGE("BaseEventAccessor.SetAxisHorizontalImpl does nothing");
}
Opt_Number GetAxisVerticalImpl(Ark_BaseEvent peer)
{
    LOGE("BaseEventAccessor.GetAxisVerticalImpl does nothing");
    return {};
}
void SetAxisVerticalImpl(Ark_BaseEvent peer,
                         const Ark_Number* axisVertical)
{
    LOGE("BaseEventAccessor.SetAxisVerticalImpl does nothing");
}
Ark_Number GetPressureImpl(Ark_BaseEvent peer)
{
    CHECK_NULL_RETURN(peer && peer->GetBaseInfo(), DefaultValueArkNumber);
    return Converter::ArkValue<Ark_Number>(static_cast<int32_t>(peer->GetBaseInfo()->GetForce()));
}
void SetPressureImpl(Ark_BaseEvent peer,
                     const Ark_Number* pressure)
{
    CHECK_NULL_VOID(peer && peer->GetBaseInfo());
    CHECK_NULL_VOID(pressure);
    peer->GetBaseInfo()->SetForce(Converter::Convert<float>(*pressure));
}
Ark_Number GetTiltXImpl(Ark_BaseEvent peer)
{
    CHECK_NULL_RETURN(peer && peer->GetBaseInfo(), DefaultValueArkNumber);
    auto value = peer->GetBaseInfo()->GetTiltX();
    return Converter::ArkValue<Ark_Number>(static_cast<int32_t>(value.value_or(0)));
}
void SetTiltXImpl(Ark_BaseEvent peer,
                  const Ark_Number* tiltX)
{
    CHECK_NULL_VOID(peer && peer->GetBaseInfo());
    CHECK_NULL_VOID(tiltX);
    peer->GetBaseInfo()->SetTiltX(Converter::Convert<float>(*tiltX));
}
Ark_Number GetTiltYImpl(Ark_BaseEvent peer)
{
    CHECK_NULL_RETURN(peer && peer->GetBaseInfo(), DefaultValueArkNumber);
    auto value = peer->GetBaseInfo()->GetTiltY();
    return Converter::ArkValue<Ark_Number>(static_cast<int32_t>(value.value_or(0)));
}
void SetTiltYImpl(Ark_BaseEvent peer,
                  const Ark_Number* tiltY)
{
    CHECK_NULL_VOID(peer && peer->GetBaseInfo());
    CHECK_NULL_VOID(tiltY);
    peer->GetBaseInfo()->SetTiltY(Converter::Convert<float>(*tiltY));
}
Opt_Number GetRollAngleImpl(Ark_BaseEvent peer)
{
    return {};
}
void SetRollAngleImpl(Ark_BaseEvent peer,
                      const Ark_Number* rollAngle)
{
}
Ark_SourceTool GetSourceToolImpl(Ark_BaseEvent peer)
{
    CHECK_NULL_RETURN(peer && peer->GetBaseInfo(), static_cast<Ark_SourceTool>(-1));
    auto value = peer->GetBaseInfo()->GetSourceTool();
    return Converter::ArkValue<Ark_SourceTool>(value);
}
void SetSourceToolImpl(Ark_BaseEvent peer,
                       Ark_SourceTool sourceTool)
{
    CHECK_NULL_VOID(peer && peer->GetBaseInfo());
    auto value = Converter::OptConvert<SourceTool>(sourceTool);
    if (value) {
        peer->GetBaseInfo()->SetSourceTool(*value);
    }
}
Opt_Number GetDeviceIdImpl(Ark_BaseEvent peer)
{
    return {};
}
void SetDeviceIdImpl(Ark_BaseEvent peer,
                     const Ark_Number* deviceId)
{
    CHECK_NULL_VOID(peer && peer->GetBaseInfo());
    CHECK_NULL_VOID(deviceId);
    peer->GetBaseInfo()->SetDeviceId(Converter::Convert<int>(*deviceId));
}
Opt_Number GetTargetDisplayIdImpl(Ark_BaseEvent peer)
{
    return {};
}
void SetTargetDisplayIdImpl(Ark_BaseEvent peer,
                            const Ark_Number* targetDisplayId)
{
}
} // BaseEventAccessor
const GENERATED_ArkUIBaseEventAccessor* GetBaseEventAccessor()
{
    static const GENERATED_ArkUIBaseEventAccessor BaseEventAccessorImpl {
        BaseEventAccessor::DestroyPeerImpl,
        BaseEventAccessor::CtorImpl,
        BaseEventAccessor::GetFinalizerImpl,
        BaseEventAccessor::GetModifierKeyStateImpl,
        BaseEventAccessor::GetTargetImpl,
        BaseEventAccessor::SetTargetImpl,
        BaseEventAccessor::GetTimestampImpl,
        BaseEventAccessor::SetTimestampImpl,
        BaseEventAccessor::GetSourceImpl,
        BaseEventAccessor::SetSourceImpl,
        BaseEventAccessor::GetAxisHorizontalImpl,
        BaseEventAccessor::SetAxisHorizontalImpl,
        BaseEventAccessor::GetAxisVerticalImpl,
        BaseEventAccessor::SetAxisVerticalImpl,
        BaseEventAccessor::GetPressureImpl,
        BaseEventAccessor::SetPressureImpl,
        BaseEventAccessor::GetTiltXImpl,
        BaseEventAccessor::SetTiltXImpl,
        BaseEventAccessor::GetTiltYImpl,
        BaseEventAccessor::SetTiltYImpl,
        BaseEventAccessor::GetRollAngleImpl,
        BaseEventAccessor::SetRollAngleImpl,
        BaseEventAccessor::GetSourceToolImpl,
        BaseEventAccessor::SetSourceToolImpl,
        BaseEventAccessor::GetDeviceIdImpl,
        BaseEventAccessor::SetDeviceIdImpl,
        BaseEventAccessor::GetTargetDisplayIdImpl,
        BaseEventAccessor::SetTargetDisplayIdImpl,
    };
    return &BaseEventAccessorImpl;
}

struct BaseEventPeer {
    virtual ~BaseEventPeer() = default;
};
}
}
