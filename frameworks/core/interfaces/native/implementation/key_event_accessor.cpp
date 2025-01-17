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

namespace OHOS::Ace::NG::GeneratedModifier {
namespace KeyEventAccessor {
void DestroyPeerImpl(KeyEventPeer* peer)
{
}
Ark_NativePointer CtorImpl()
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Boolean GetModifierKeyStateImpl(KeyEventPeer* peer,
                                    const Array_String* keys)
{
    return 0;
}
Ark_NativePointer GetTypeImpl(KeyEventPeer* peer)
{
    return nullptr;
}
void SetTypeImpl(KeyEventPeer* peer,
                 Ark_KeyType type)
{
}
Ark_Int32 GetKeyCodeImpl(KeyEventPeer* peer)
{
    return 0;
}
void SetKeyCodeImpl(KeyEventPeer* peer,
                    const Ark_Number* keyCode)
{
}
void GetKeyTextImpl(KeyEventPeer* peer)
{
}
void SetKeyTextImpl(KeyEventPeer* peer,
                    const Ark_String* keyText)
{
}
Ark_NativePointer GetKeySourceImpl(KeyEventPeer* peer)
{
    return nullptr;
}
void SetKeySourceImpl(KeyEventPeer* peer,
                      Ark_KeySource keySource)
{
}
Ark_Int32 GetDeviceIdImpl(KeyEventPeer* peer)
{
    return 0;
}
void SetDeviceIdImpl(KeyEventPeer* peer,
                     const Ark_Number* deviceId)
{
}
Ark_Int32 GetMetaKeyImpl(KeyEventPeer* peer)
{
    return 0;
}
void SetMetaKeyImpl(KeyEventPeer* peer,
                    const Ark_Number* metaKey)
{
}
Ark_Int32 GetTimestampImpl(KeyEventPeer* peer)
{
    return 0;
}
void SetTimestampImpl(KeyEventPeer* peer,
                      const Ark_Number* timestamp)
{
}
void SetStopPropagationImpl(KeyEventPeer* peer,
                            const Callback_Void* stopPropagation)
{
}
void SetIntentionCodeImpl(KeyEventPeer* peer,
                          const Ark_IntentionCode* intentionCode)
{
}
Ark_Int32 GetUnicodeImpl(KeyEventPeer* peer)
{
    return 0;
}
void SetUnicodeImpl(KeyEventPeer* peer,
                    const Ark_Number* unicode)
{
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
        KeyEventAccessor::SetStopPropagationImpl,
        KeyEventAccessor::SetIntentionCodeImpl,
        KeyEventAccessor::GetUnicodeImpl,
        KeyEventAccessor::SetUnicodeImpl,
    };
    return &KeyEventAccessorImpl;
}

}
