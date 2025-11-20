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
    LOGW("ARKOALA KeyEventAccessor::SetTypeImpl doesn't have sense.");
}
Ark_Int32 GetKeyCodeImpl(Ark_KeyEvent peer)
{
    CHECK_NULL_RETURN(peer, DefaultValueInt32);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, DefaultValueInt32);
    const auto keyCode = info->GetKeyCode();
    return Converter::ArkValue<Ark_Int32>(static_cast<int32_t>(keyCode));
}
void SetKeyCodeImpl(Ark_KeyEvent peer,
                    Ark_Int32 keyCode)
{
    LOGW("ARKOALA KeyEventAccessor::SetKeyCodeImpl doesn't have sense.");
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
    LOGW("ARKOALA KeyEventAccessor::SetKeyTextImpl doesn't have sense.");
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
    LOGW("ARKOALA KeyEventAccessor::SetKeySourceImpl doesn't have sense.");
}
Ark_Int32 GetDeviceIdImpl(Ark_KeyEvent peer)
{
    auto id = GetBaseEventAccessor()->getDeviceId(peer);
    return Converter::GetOpt(id).value_or(Converter::ArkValue<Ark_Int32>(-1));
}
void SetDeviceIdImpl(Ark_KeyEvent peer,
                     Ark_Int32 deviceId)
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
void SetMetaKeyImpl(Ark_KeyEvent peer,
                    Ark_Int32 metaKey)
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
void SetTimestampImpl(Ark_KeyEvent peer,
                      Ark_Int64 timestamp)
{
    GetBaseEventAccessor()->setTimestamp(peer, timestamp);
}
Callback_Void GetStopPropagationImpl(Ark_KeyEvent peer)
{
    CHECK_NULL_RETURN(peer, {});
    auto callback = CallbackKeeper::ReturnReverseCallback<Callback_Void>([peer]() {
        KeyEventInfo* info = peer->GetEventInfo();
        CHECK_NULL_VOID(info);
        info->SetStopPropagation(true);
    });
    return callback;
}
void SetStopPropagationImpl(Ark_KeyEvent peer,
                            const Callback_Void* stopPropagation)
{
    LOGW("ARKOALA KeyEventAccessor::SetStopPropagation doesn't have sense.");
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
    LOGW("ARKOALA KeyEventAccessor::SetIntentionCodeImpl doesn't have sense.");
}
Opt_ModifierKeyStateGetter GetGetModifierKeyStateImpl(Ark_KeyEvent peer)
{
    const auto invalid = Converter::ArkValue<Opt_ModifierKeyStateGetter>(Ark_Empty());
    CHECK_NULL_RETURN(peer, invalid);
    auto info = peer->GetBaseInfo();
    CHECK_NULL_RETURN(info, invalid);
    auto getter = CallbackKeeper::ReturnReverseCallback<ModifierKeyStateGetter,
            std::function<void(const Array_String, const Callback_Boolean_Void)>>([info]
            (const Array_String keys, const Callback_Boolean_Void continuation) {
        auto eventKeys = info->GetPressedKeyCodes();
        auto keysStr = Converter::Convert<std::vector<std::string>>(keys);
        Ark_Boolean arkResult = Converter::ArkValue<Ark_Boolean>(AccessorUtils::CheckKeysPressed(keysStr, eventKeys));
        CallbackHelper(continuation).InvokeSync(arkResult);
    });
    return Converter::ArkValue<Opt_ModifierKeyStateGetter, ModifierKeyStateGetter>(getter);
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
    LOGW("ARKOALA KeyEventAccessor::SetUnicodeImpl doesn't have sense.");
}
} // KeyEventAccessor
const GENERATED_ArkUIKeyEventAccessor* GetKeyEventAccessor()
{
    static const GENERATED_ArkUIKeyEventAccessor KeyEventAccessorImpl {
        KeyEventAccessor::DestroyPeerImpl,
        KeyEventAccessor::ConstructImpl,
        KeyEventAccessor::GetFinalizerImpl,
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
        KeyEventAccessor::GetStopPropagationImpl,
        KeyEventAccessor::SetStopPropagationImpl,
        KeyEventAccessor::GetIntentionCodeImpl,
        KeyEventAccessor::SetIntentionCodeImpl,
        KeyEventAccessor::GetGetModifierKeyStateImpl,
        KeyEventAccessor::SetGetModifierKeyStateImpl,
        KeyEventAccessor::GetUnicodeImpl,
        KeyEventAccessor::SetUnicodeImpl,
    };
    return &KeyEventAccessorImpl;
}

}
