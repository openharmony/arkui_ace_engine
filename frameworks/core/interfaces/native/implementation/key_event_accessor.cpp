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
#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/accessor_utils.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/implementation/key_event_peer.h"

namespace OHOS::Ace::NG::GeneratedModifier {
const GENERATED_ArkUIBaseEventAccessor* GetBaseEventAccessor();

namespace {
const auto DefaultValueInt32 = Converter::ArkValue<Ark_Int32>(0);
const Ark_Boolean DefaultValueBoolean = Converter::ArkValue<Ark_Boolean>(false);
} // namespace

namespace KeyEventAccessor {
void DestroyPeerImpl(Ark_KeyEvent peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_KeyEvent ConstructImpl()
{
    return PeerUtils::CreatePeer<KeyEventPeer>();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void StopPropagationImpl(Ark_KeyEvent peer)
{
    CHECK_NULL_VOID(peer);
    KeyEventInfo* info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    info->SetStopPropagation(true);
}
Ark_KeyType GetTypeImpl(Ark_KeyEvent peer)
{
    const auto errValue = static_cast<Ark_KeyType>(-1);
    CHECK_NULL_RETURN(peer, errValue);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    return Converter::ArkValue<Ark_KeyType>(info->GetKeyType());
}
void SetTypeImpl(Ark_KeyEvent peer,
                 Ark_KeyType type)
{
    CHECK_NULL_VOID(peer);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    info->SetKeyType(static_cast<KeyAction>(type));
}
Ark_Int32 GetKeyCodeImpl(Ark_KeyEvent peer)
{
    CHECK_NULL_RETURN(peer, DefaultValueInt32);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, DefaultValueInt32);
    const auto keyCode = info->GetKeyCode();
    return Converter::ArkValue<Ark_Int32>(static_cast<int32_t>(keyCode));
}
void SetKeyCodeImpl(Ark_KeyEvent peer, Ark_Int32 keyCode)
{
    CHECK_NULL_VOID(peer);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    info->SetKeyCode(static_cast<KeyCode>(keyCode));
}
Ark_String GetKeyTextImpl(Ark_KeyEvent peer)
{
    CHECK_NULL_RETURN(peer, {});
    const auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, {});
    const auto keyText = info->GetKeyText();
    return Converter::ArkValue<Ark_String>(keyText, Converter::FC);
}
void SetKeyTextImpl(Ark_KeyEvent peer,
                    const Ark_String* keyText)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(keyText);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    info->SetKeyText(Converter::Convert<std::string>(*keyText));
}
Ark_KeySource GetKeySourceImpl(Ark_KeyEvent peer)
{
    const auto errValue = static_cast<Ark_KeySource>(-1);
    CHECK_NULL_RETURN(peer, errValue);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    return Converter::ArkValue<Ark_KeySource>(info->GetKeySource());
}
void SetKeySourceImpl(Ark_KeyEvent peer,
                      Ark_KeySource keySource)
{
    CHECK_NULL_VOID(peer);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    info->SetKeySource(static_cast<SourceType>(keySource));
}
Ark_Int32 GetDeviceIdImpl(Ark_KeyEvent peer)
{
    auto id = GetBaseEventAccessor()->getDeviceId(peer);
    return Converter::GetOpt(id).value_or(Converter::ArkValue<Ark_Int32>(-1));
}
void SetDeviceIdImpl(Ark_KeyEvent peer, Ark_Int32 deviceId)
{
    CHECK_NULL_VOID(peer && peer->GetBaseInfo());
    peer->GetBaseInfo()->SetDeviceId(Converter::Convert<int>(deviceId));
}
Ark_Int32 GetMetaKeyImpl(Ark_KeyEvent peer)
{
    CHECK_NULL_RETURN(peer, DefaultValueInt32);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, DefaultValueInt32);
    const auto metaKey = info->GetMetaKey();
    return Converter::ArkValue<Ark_Int32>(metaKey);
}
void SetMetaKeyImpl(Ark_KeyEvent peer, Ark_Int32 metaKey)
{
    CHECK_NULL_VOID(peer);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    const auto convMetaKey = Converter::Convert<int32_t>(metaKey);
    info->SetMetaKey(convMetaKey);
}
Ark_Int64 GetTimestampImpl(Ark_KeyEvent peer)
{
    return GetBaseEventAccessor()->getTimestamp(peer);
}
void SetTimestampImpl(Ark_KeyEvent peer, Ark_Int64 timestamp)
{
    GetBaseEventAccessor()->setTimestamp(peer, timestamp);
}
Ark_IntentionCode GetIntentionCodeImpl(Ark_KeyEvent peer)
{
    static constexpr auto intentionCodeError = static_cast<Ark_IntentionCode>(-1);
    CHECK_NULL_RETURN(peer, intentionCodeError);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, intentionCodeError);
    return Converter::ArkValue<Ark_IntentionCode>(info->GetKeyIntention());
}
void SetIntentionCodeImpl(Ark_KeyEvent peer,
                          Ark_IntentionCode intentionCode)
{
    CHECK_NULL_VOID(peer);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    info->SetKeyIntention(static_cast<KeyIntention>(intentionCode));
}
void SetGetModifierKeyStateImpl(Ark_KeyEvent peer,
                                const Opt_ModifierKeyStateGetter* getModifierKeyState)
{
    LOGE("KeyEventAccessor.SetGetModifierKeyStateImpl does nothing");
}
Opt_Int64 GetUnicodeImpl(Ark_KeyEvent peer)
{
    auto invalid = Converter::ArkValue<Opt_Int64>();
    CHECK_NULL_RETURN(peer, invalid);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, invalid);
    const auto unicode = info->GetUnicode();
    return Converter::ArkValue<Opt_Int64>(static_cast<int64_t>(unicode));
}
void SetUnicodeImpl(Ark_KeyEvent peer,
                    const Opt_Int64* unicode)
{
    CHECK_NULL_VOID(peer);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    if (unicode != nullptr && unicode->tag != INTEROP_TAG_UNDEFINED) {
        info->SetUnicode(static_cast<uint32_t>(unicode->value));
    }
}
Opt_Boolean GetIsNumLockOnImpl(Ark_KeyEvent peer)
{
    auto invalid = Converter::ArkValue<Opt_Boolean>();
    CHECK_NULL_RETURN(peer, invalid);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, invalid);
    const auto isNumLockOn = info->GetNumLock();
    return Converter::ArkValue<Opt_Boolean>(isNumLockOn);
}

void SetIsNumLockOnImpl(Ark_KeyEvent peer,
                        const Opt_Boolean* isNumLockOn)
{
    CHECK_NULL_VOID(peer);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    if (isNumLockOn != nullptr && isNumLockOn->tag != INTEROP_TAG_UNDEFINED) {
        info->SetNumLock(isNumLockOn->value);
    }
}

Opt_Boolean GetIsCapsLockOnImpl(Ark_KeyEvent peer)
{
    auto invalid = Converter::ArkValue<Opt_Boolean>();
    CHECK_NULL_RETURN(peer, invalid);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, invalid);
    const auto isCapsLockOn = info->GetCapsLock();
    return Converter::ArkValue<Opt_Boolean>(isCapsLockOn);
}

void SetIsCapsLockOnImpl(Ark_KeyEvent peer,
                         const Opt_Boolean* isCapsLockOn)
{
    CHECK_NULL_VOID(peer);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    if (isCapsLockOn != nullptr && isCapsLockOn->tag != INTEROP_TAG_UNDEFINED) {
        info->SetCapsLock(isCapsLockOn->value);
    }
}

Opt_Boolean GetIsScrollLockOnImpl(Ark_KeyEvent peer)
{
    auto invalid = Converter::ArkValue<Opt_Boolean>();
    CHECK_NULL_RETURN(peer, invalid);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, invalid);
    const auto isScrollLockOn = info->GetScrollLock();
    return Converter::ArkValue<Opt_Boolean>(isScrollLockOn);
}

void SetIsScrollLockOnImpl(Ark_KeyEvent peer,
                           const Opt_Boolean* isScrollLockOn)
{
    CHECK_NULL_VOID(peer);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    if (isScrollLockOn != nullptr && isScrollLockOn->tag != INTEROP_TAG_UNDEFINED) {
        info->SetScrollLock(isScrollLockOn->value);
    }
}
} // KeyEventAccessor
const GENERATED_ArkUIKeyEventAccessor* GetKeyEventAccessor()
{
    static const GENERATED_ArkUIKeyEventAccessor KeyEventAccessorImpl {
        KeyEventAccessor::DestroyPeerImpl,
        KeyEventAccessor::ConstructImpl,
        KeyEventAccessor::GetFinalizerImpl,
        KeyEventAccessor::StopPropagationImpl,
        KeyEventAccessor::GetTypeImpl,
        KeyEventAccessor::SetTypeImpl,
        KeyEventAccessor::GetKeyCodeImpl,
        KeyEventAccessor::SetKeyCodeImpl,
        KeyEventAccessor::GetKeyTextImpl,
        KeyEventAccessor::SetKeyTextImpl,
        KeyEventAccessor::GetKeySourceImpl,
        KeyEventAccessor::SetKeySourceImpl,
        KeyEventAccessor::GetDeviceIdImpl,
        KeyEventAccessor::SetDeviceIdImpl,
        KeyEventAccessor::GetMetaKeyImpl,
        KeyEventAccessor::SetMetaKeyImpl,
        KeyEventAccessor::GetTimestampImpl,
        KeyEventAccessor::SetTimestampImpl,
        KeyEventAccessor::GetIntentionCodeImpl,
        KeyEventAccessor::SetIntentionCodeImpl,
        KeyEventAccessor::SetGetModifierKeyStateImpl,
        KeyEventAccessor::GetUnicodeImpl,
        KeyEventAccessor::SetUnicodeImpl,
        KeyEventAccessor::GetIsNumLockOnImpl,
        KeyEventAccessor::SetIsNumLockOnImpl,
        KeyEventAccessor::GetIsCapsLockOnImpl,
        KeyEventAccessor::SetIsCapsLockOnImpl,
        KeyEventAccessor::GetIsScrollLockOnImpl,
        KeyEventAccessor::SetIsScrollLockOnImpl,
    };
    return &KeyEventAccessorImpl;
}

}
