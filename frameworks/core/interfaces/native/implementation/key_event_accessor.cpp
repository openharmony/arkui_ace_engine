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
#include "core/interfaces/native/generated/interface/node_api.h"
#include "core/interfaces/native/implementation/key_event_peer.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace {
const auto DefaultValueInt32 = Converter::ArkValue<Ark_Int32>(0);
} // namespace

namespace KeyEventAccessor {
void DestroyPeerImpl(KeyEventPeer* peer)
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
Ark_Boolean GetModifierKeyStateImpl(KeyEventPeer* peer,
                                    const Array_String* keys)
{
    return GetFullAPI()->getAccessors()->getBaseEventAccessor()->getModifierKeyState(peer, keys);
}
Ark_NativePointer GetTypeImpl(KeyEventPeer* peer)
{
    CHECK_NULL_RETURN(peer, nullptr);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, nullptr);
    const auto keyType = info->GetKeyType();
    LOGE("ARKOALA KeyEventAccessor::GetTypeImpl is not implemented "
        "-> incorrect return Converter::ArkValue<Ark_KeyType>(keyType): %d", keyType);
    return {};
}
void SetTypeImpl(KeyEventPeer* peer,
                 Ark_KeyType type)
{
    LOGW("ARKOALA KeyEventAccessor::SetTypeImpl doesn't have sense.");
}
Ark_Int32 GetKeyCodeImpl(KeyEventPeer* peer)
{
    CHECK_NULL_RETURN(peer, DefaultValueInt32);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, DefaultValueInt32);
    const auto keyCode = info->GetKeyCode();
    return Converter::ArkValue<Ark_Int32>(static_cast<int32_t>(keyCode));
}
void SetKeyCodeImpl(KeyEventPeer* peer,
                    const Ark_Number* keyCode)
{
    LOGW("ARKOALA KeyEventAccessor::SetKeyCodeImpl doesn't have sense.");
}
void GetKeyTextImpl(KeyEventPeer* peer)
{
    CHECK_NULL_VOID(peer);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    const auto keyText = info->GetKeyText();
    LOGE("ARKOALA KeyEventAccessor::GetKeyTextImpl is not implemented "
        "-> incorrect return Converter::ArkValue<Ark_String>(keyText): %s", keyText);
}
void SetKeyTextImpl(KeyEventPeer* peer,
                    const Ark_String* keyText)
{
    LOGW("ARKOALA KeyEventAccessor::SetKeyTextImpl doesn't have sense.");
}
Ark_NativePointer GetKeySourceImpl(KeyEventPeer* peer)
{
    CHECK_NULL_RETURN(peer, nullptr);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, nullptr);
    const auto keySource = info->GetKeySource();
    LOGE("ARKOALA KeyEventAccessor::GetKeySourceImpl is not implemented "
        "-> incorrect return Converter::ArkValue<Ark_KeySource>(keySource): %d", keySource);
    return {};
}
void SetKeySourceImpl(KeyEventPeer* peer,
                      Ark_KeySource keySource)
{
    LOGW("ARKOALA KeyEventAccessor::SetKeySourceImpl doesn't have sense.");
}
Ark_Int32 GetDeviceIdImpl(KeyEventPeer* peer)
{
    return GetFullAPI()->getAccessors()->getBaseEventAccessor()->getDeviceId(peer);
}
void SetDeviceIdImpl(KeyEventPeer* peer,
                     const Ark_Number* deviceId)
{
    GetFullAPI()->getAccessors()->getBaseEventAccessor()->setDeviceId(peer, deviceId);
}
Ark_Int32 GetMetaKeyImpl(KeyEventPeer* peer)
{
    CHECK_NULL_RETURN(peer, DefaultValueInt32);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, DefaultValueInt32);
    const auto metaKey = info->GetMetaKey();
    return Converter::ArkValue<Ark_Int32>(metaKey);
}
void SetMetaKeyImpl(KeyEventPeer* peer,
                    const Ark_Number* metaKey)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(metaKey);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    const auto convMetaKey = Converter::Convert<int32_t>(*metaKey);
    info->SetMetaKey(convMetaKey);
}
Ark_Int32 GetTimestampImpl(KeyEventPeer* peer)
{
    return GetFullAPI()->getAccessors()->getBaseEventAccessor()->getTimestamp(peer);
}
void SetTimestampImpl(KeyEventPeer* peer,
                      const Ark_Number* timestamp)
{
    GetFullAPI()->getAccessors()->getBaseEventAccessor()->setTimestamp(peer, timestamp);
}
Callback_Void GetStopPropagationImpl(KeyEventPeer* peer)
{
    return {};
}
void SetStopPropagationImpl(KeyEventPeer* peer,
                            const Callback_Void* stopPropagation)
{
    LOGW("ARKOALA KeyEventAccessor::SetStopPropagation doesn't have sense.");
}
void SetIntentionCodeImpl(KeyEventPeer* peer,
                          const Ark_IntentionCode* intentionCode)
{
    LOGW("ARKOALA KeyEventAccessor::SetIntentionCodeImpl doesn't have sense.");
}
Ark_Int32 GetUnicodeImpl(KeyEventPeer* peer)
{
    CHECK_NULL_RETURN(peer, DefaultValueInt32);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, DefaultValueInt32);
    const auto unicode = info->GetUnicode();
    return Converter::ArkValue<Ark_Int32>(static_cast<int32_t>(unicode));
}
void SetUnicodeImpl(KeyEventPeer* peer,
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
        KeyEventAccessor::SetIntentionCodeImpl,
        KeyEventAccessor::GetUnicodeImpl,
        KeyEventAccessor::SetUnicodeImpl,
    };
    return &KeyEventAccessorImpl;
}
}
