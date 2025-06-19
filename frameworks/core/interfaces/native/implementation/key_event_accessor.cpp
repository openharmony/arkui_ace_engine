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
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/generated/interface/node_api.h"
#include "core/interfaces/native/implementation/key_event_peer.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace {
const auto DefaultValueInt32 = Converter::ArkValue<Ark_Number>(0);
} // namespace

namespace KeyEventAccessor {
void DestroyPeerImpl(Ark_KeyEvent peer)
{
    delete peer;
}
Ark_KeyEvent CtorImpl()
{
    return new KeyEventPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Boolean GetModifierKeyStateImpl(Ark_VMContext vmContext,
                                    Ark_KeyEvent peer,
                                    const Array_String* keys)
{
    return GetFullAPI()->getAccessors()->getBaseEventAccessor()->getModifierKeyState(vmContext, peer, keys);
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
Ark_Number GetKeyCodeImpl(Ark_KeyEvent peer)
{
    CHECK_NULL_RETURN(peer, DefaultValueInt32);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, DefaultValueInt32);
    const auto keyCode = info->GetKeyCode();
    return Converter::ArkValue<Ark_Number>(static_cast<int32_t>(keyCode));
}
void SetKeyCodeImpl(Ark_KeyEvent peer,
                    const Ark_Number* keyCode)
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
Ark_Number GetDeviceIdImpl(Ark_KeyEvent peer)
{
    return GetFullAPI()->getAccessors()->getBaseEventAccessor()->getDeviceId(peer);
}
void SetDeviceIdImpl(Ark_KeyEvent peer,
                     const Ark_Number* deviceId)
{
    GetFullAPI()->getAccessors()->getBaseEventAccessor()->setDeviceId(peer, deviceId);
}
Ark_Number GetMetaKeyImpl(Ark_KeyEvent peer)
{
    CHECK_NULL_RETURN(peer, DefaultValueInt32);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, DefaultValueInt32);
    const auto metaKey = info->GetMetaKey();
    return Converter::ArkValue<Ark_Number>(metaKey);
}
void SetMetaKeyImpl(Ark_KeyEvent peer,
                    const Ark_Number* metaKey)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(metaKey);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    const auto convMetaKey = Converter::Convert<int32_t>(*metaKey);
    info->SetMetaKey(convMetaKey);
}
Ark_Number GetTimestampImpl(Ark_KeyEvent peer)
{
    return GetFullAPI()->getAccessors()->getBaseEventAccessor()->getTimestamp(peer);
}
void SetTimestampImpl(Ark_KeyEvent peer,
                      const Ark_Number* timestamp)
{
    GetFullAPI()->getAccessors()->getBaseEventAccessor()->setTimestamp(peer, timestamp);
}
Callback_Void GetStopPropagationImpl(Ark_KeyEvent peer)
{
    CHECK_NULL_RETURN(peer, {});
    auto callback = CallbackKeeper::DefineReverseCallback<Callback_Void>([peer]() {
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
    return {};
}
void SetIntentionCodeImpl(Ark_KeyEvent peer,
                          const Ark_IntentionCode* intentionCode)
{
    LOGW("ARKOALA KeyEventAccessor::SetIntentionCodeImpl doesn't have sense.");
}
Ark_Number GetUnicodeImpl(Ark_KeyEvent peer)
{
    CHECK_NULL_RETURN(peer, DefaultValueInt32);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, DefaultValueInt32);
    const auto unicode = info->GetUnicode();
    return Converter::ArkValue<Ark_Number>(static_cast<int32_t>(unicode));
}
void SetUnicodeImpl(Ark_KeyEvent peer,
                    const Ark_Number* unicode)
{
    LOGW("ARKOALA KeyEventAccessor::SetUnicodeImpl doesn't have sense.");
}
} // KeyEventAccessor
const GENERATED_ArkUIKeyEventAccessor* GetKeyEventAccessor()
{
    static const GENERATED_ArkUIKeyEventAccessor KeyEventAccessorImpl {
        KeyEventAccessor::DestroyPeerImpl,
        KeyEventAccessor::CtorImpl,
        KeyEventAccessor::GetFinalizerImpl,
        KeyEventAccessor::GetModifierKeyStateImpl,
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
        KeyEventAccessor::GetUnicodeImpl,
        KeyEventAccessor::SetUnicodeImpl,
    };
    return &KeyEventAccessorImpl;
}
}
