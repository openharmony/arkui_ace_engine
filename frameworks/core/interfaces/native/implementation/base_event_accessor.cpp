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

#include <optional>
#include <vector>

#include "core/components_ng/base/frame_node.h"
#include "core/event/ace_events.h"
#include "core/interfaces/native/utility/accessor_utils.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/implementation/base_event_peer.h"

namespace OHOS::Ace::NG {
namespace GeneratedModifier {
namespace BaseEventAccessor {

namespace {
const Ark_Boolean DefaultValueBoolean = Converter::ArkValue<Ark_Boolean>(false);
const Ark_Float64 DefaultValueArkNumber = Converter::ArkValue<Ark_Float64>(0);
}  // namespace

Ark_Boolean GetModifierKeyStateImpl(Ark_VMContext vmContext,
                                    Ark_BaseEvent peer,
                                    const Array_String* keys)
{
    CHECK_NULL_RETURN(peer && peer->GetBaseInfo(), DefaultValueBoolean);
    CHECK_NULL_RETURN(keys, DefaultValueBoolean);
    auto eventKeys = peer->GetBaseInfo()->GetPressedKeyCodes();
    auto keysStr = Converter::Convert<std::vector<std::string>>(*keys);
    return Converter::ArkValue<Ark_Boolean>(OHOS::Ace::NG::AccessorUtils::CheckKeysPressed(keysStr, eventKeys));
}
void DestroyPeerImpl(Ark_BaseEvent peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_BaseEvent ConstructImpl()
{
    return PeerUtils::CreatePeer<BaseEventPeerImpl>();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_EventTarget GetTargetImpl(Ark_BaseEvent peer)
{
    CHECK_NULL_RETURN(peer && peer->GetBaseInfo(), {});
    return Converter::ArkValue<Ark_EventTarget>(peer->GetBaseInfo()->GetTarget(), Converter::FC);
}
void SetTargetImpl(Ark_BaseEvent peer,
                   const Ark_EventTarget* target)
{
    CHECK_NULL_VOID(peer && peer->GetBaseInfo());
    CHECK_NULL_VOID(target);
    peer->GetBaseInfo()->SetTarget(Converter::Convert<EventTarget>(*target));
}
Ark_Int64 GetTimestampImpl(Ark_BaseEvent peer)
{
    auto errValue = Converter::ArkValue<Ark_Int64>(static_cast<int64_t>(-1));
    CHECK_NULL_RETURN(peer && peer->GetBaseInfo(), errValue);
    auto tstamp = std::chrono::duration_cast<std::chrono::nanoseconds>(
        peer->GetBaseInfo()->GetTimeStamp().time_since_epoch()).count();
    return Converter::ArkValue<Ark_Int64>(static_cast<int64_t>(tstamp));
}
void SetTimestampImpl(Ark_BaseEvent peer, Ark_Int64 timestamp)
{
    CHECK_NULL_VOID(peer && peer->GetBaseInfo());
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
Opt_Float64 GetAxisHorizontalImpl(Ark_BaseEvent peer)
{
    auto invalid = Converter::ArkValue<Opt_Float64>();
    CHECK_NULL_RETURN(peer && peer->GetBaseInfo(), invalid);
    float value = peer->GetBaseInfo()->GetHorizontalAxis();
    return Converter::ArkValue<Opt_Float64>(value);
}
void SetAxisHorizontalImpl(Ark_BaseEvent peer,
                           const Opt_Float64* axisHorizontal)
{
    CHECK_NULL_VOID(peer && peer->GetBaseInfo());
    auto value = Converter::OptConvertPtr<float>(axisHorizontal).value_or(0.f);
    peer->GetBaseInfo()->SetHorizontalAxis(value);
}
Opt_Float64 GetAxisVerticalImpl(Ark_BaseEvent peer)
{
    auto invalid = Converter::ArkValue<Opt_Float64>();
    CHECK_NULL_RETURN(peer && peer->GetBaseInfo(), invalid);
    float value = peer->GetBaseInfo()->GetVerticalAxis();
    return Converter::ArkValue<Opt_Float64>(value);
}
void SetAxisVerticalImpl(Ark_BaseEvent peer,
                         const Opt_Float64* axisVertical)
{
    CHECK_NULL_VOID(peer && peer->GetBaseInfo());
    CHECK_NULL_VOID(axisVertical);
    auto value = Converter::OptConvertPtr<float>(axisVertical).value_or(0.f);
    peer->GetBaseInfo()->SetVerticalAxis(value);
}
Ark_Float64 GetPressureImpl(Ark_BaseEvent peer)
{
    CHECK_NULL_RETURN(peer && peer->GetBaseInfo(), DefaultValueArkNumber);
    return Converter::ArkValue<Ark_Float64>(static_cast<float>(peer->GetBaseInfo()->GetForce()));
}
void SetPressureImpl(Ark_BaseEvent peer, Ark_Float64 pressure)
{
    CHECK_NULL_VOID(peer && peer->GetBaseInfo());
    peer->GetBaseInfo()->SetForce(Converter::Convert<float>(pressure));
}
Ark_Float64 GetTiltXImpl(Ark_BaseEvent peer)
{
    CHECK_NULL_RETURN(peer && peer->GetBaseInfo(), DefaultValueArkNumber);
    auto value = peer->GetBaseInfo()->GetTiltX();
    return Converter::ArkValue<Ark_Float64>(static_cast<int32_t>(value.value_or(0)));
}
void SetTiltXImpl(Ark_BaseEvent peer, Ark_Float64 tiltX)
{
    CHECK_NULL_VOID(peer && peer->GetBaseInfo());
    peer->GetBaseInfo()->SetTiltX(Converter::Convert<float>(tiltX));
}
Ark_Float64 GetTiltYImpl(Ark_BaseEvent peer)
{
    CHECK_NULL_RETURN(peer && peer->GetBaseInfo(), DefaultValueArkNumber);
    auto value = peer->GetBaseInfo()->GetTiltY();
    return Converter::ArkValue<Ark_Float64>(static_cast<int32_t>(value.value_or(0)));
}
void SetTiltYImpl(Ark_BaseEvent peer, Ark_Float64 tiltY)
{
    CHECK_NULL_VOID(peer && peer->GetBaseInfo());
    peer->GetBaseInfo()->SetTiltY(Converter::Convert<float>(tiltY));
}
Opt_Float64 GetRollAngleImpl(Ark_BaseEvent peer)
{
    auto invalid = Converter::ArkValue<Opt_Float64>();
    CHECK_NULL_RETURN(peer && peer->GetBaseInfo(), invalid);
    return Converter::ArkValue<Opt_Float64>(peer->GetBaseInfo()->GetRollAngle().value_or(0.0f));
}
void SetRollAngleImpl(Ark_BaseEvent peer,
                      const Opt_Float64* rollAngle)
{
    CHECK_NULL_VOID(peer && peer->GetBaseInfo());
    CHECK_NULL_VOID(rollAngle);
    peer->GetBaseInfo()->SetRollAngle(Converter::OptConvertPtr<float>(rollAngle).value_or(0));
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
Opt_ModifierKeyStateGetter GetGetModifierKeyStateImpl(Ark_BaseEvent peer)
{
    const auto invalid = Converter::ArkValue<Opt_ModifierKeyStateGetter>(Ark_Empty());
    CHECK_NULL_RETURN(peer, invalid);
    auto info = peer->GetBaseInfo();
    CHECK_NULL_RETURN(info, invalid);
    auto getter = CallbackKeeper::RegisterReverseCallback<ModifierKeyStateGetter,
            std::function<void(const Array_String, const Callback_Boolean_Void)>>([info]
            (const Array_String keys, const Callback_Boolean_Void continuation) {
        auto eventKeys = info->GetPressedKeyCodes();
        auto keysStr = Converter::Convert<std::vector<std::string>>(keys);
        Ark_Boolean arkResult = Converter::ArkValue<Ark_Boolean>(AccessorUtils::CheckKeysPressed(keysStr, eventKeys));
        CallbackHelper(continuation).InvokeSync(arkResult);
    });
    return Converter::ArkValue<Opt_ModifierKeyStateGetter, ModifierKeyStateGetter>(getter);
}
void SetGetModifierKeyStateImpl(Ark_BaseEvent peer,
                                const Opt_ModifierKeyStateGetter* getModifierKeyState)
{
    LOGE("BaseEventAccessor.SetGetModifierKeyStateImpl does nothing");
}
Opt_Int32 GetDeviceIdImpl(Ark_BaseEvent peer)
{
    auto invalid = Converter::ArkValue<Opt_Int32>();
    CHECK_NULL_RETURN(peer && peer->GetBaseInfo(), invalid);
    // GetDeviceId returns int64_t, but it is int32_t in MMI
    // Need to change return type if int64_t is ever required
    int32_t value = static_cast<int32_t>(peer->GetBaseInfo()->GetDeviceId());
    return Converter::ArkValue<Opt_Int32>(value);
}
void SetDeviceIdImpl(Ark_BaseEvent peer,
                     const Opt_Int32* deviceId)
{
    CHECK_NULL_VOID(peer && peer->GetBaseInfo());
    CHECK_NULL_VOID(deviceId);
    peer->GetBaseInfo()->SetDeviceId(Converter::OptConvertPtr<int>(deviceId).value_or(0));
}
Opt_Int32 GetTargetDisplayIdImpl(Ark_BaseEvent peer)
{
    auto invalid = Converter::ArkValue<Opt_Int32>();
    CHECK_NULL_RETURN(peer && peer->GetBaseInfo(), invalid);
    int32_t value = peer->GetBaseInfo()->GetTargetDisplayId();
    return Converter::ArkValue<Opt_Int32>(value);
}
void SetTargetDisplayIdImpl(Ark_BaseEvent peer,
                            const Opt_Int32* targetDisplayId)
{
    CHECK_NULL_VOID(peer && peer->GetBaseInfo());
    CHECK_NULL_VOID(targetDisplayId);
    auto id = Converter::OptConvertPtr<int32_t>(targetDisplayId);
    if (id) {
        peer->GetBaseInfo()->SetTargetDisplayId(id.value());
    }
}
} // BaseEventAccessor

const GENERATED_ArkUIBaseEventAccessor* GetBaseEventAccessor()
{
    static const GENERATED_ArkUIBaseEventAccessor BaseEventAccessorImpl {
        BaseEventAccessor::DestroyPeerImpl,
        BaseEventAccessor::ConstructImpl,
        BaseEventAccessor::GetFinalizerImpl,
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
        BaseEventAccessor::GetGetModifierKeyStateImpl,
        BaseEventAccessor::SetGetModifierKeyStateImpl,
        BaseEventAccessor::GetDeviceIdImpl,
        BaseEventAccessor::SetDeviceIdImpl,
        BaseEventAccessor::GetTargetDisplayIdImpl,
        BaseEventAccessor::SetTargetDisplayIdImpl,
    };
    return &BaseEventAccessorImpl;
}
}
}
