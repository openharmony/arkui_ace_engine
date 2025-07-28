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
#include "core/interfaces/native/implementation/web_keyboard_controller_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/validators.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace WebKeyboardControllerAccessor {
void DestroyPeerImpl(Ark_WebKeyboardController peer)
{
    delete peer;
}
Ark_WebKeyboardController CtorImpl()
{
    return new WebKeyboardControllerPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void InsertTextImpl(Ark_WebKeyboardController peer,
                    const Ark_String* text)
{
    CHECK_NULL_VOID(peer && peer->handler);
    CHECK_NULL_VOID(text);
    peer->handler->InsertText(
        Converter::Convert<std::string>(*text)
    );
}
void DeleteForwardImpl(Ark_WebKeyboardController peer,
                       const Ark_Number* length)
{
    CHECK_NULL_VOID(peer && peer->handler);
    CHECK_NULL_VOID(length);
    auto lengthOpt = Converter::OptConvert<int32_t>(*length);
    Validator::ValidatePositive(lengthOpt);
    if (lengthOpt) {
        peer->handler->DeleteForward(lengthOpt.value());
    }
}
void DeleteBackwardImpl(Ark_WebKeyboardController peer,
                        const Ark_Number* length)
{
    CHECK_NULL_VOID(peer && peer->handler);
    CHECK_NULL_VOID(length);
    auto lengthOpt = Converter::OptConvert<int32_t>(*length);
    Validator::ValidatePositive(lengthOpt);
    if (lengthOpt) {
        peer->handler->DeleteBackward(lengthOpt.value());
    }
}
void SendFunctionKeyImpl(Ark_WebKeyboardController peer,
                         const Ark_Number* key)
{
    CHECK_NULL_VOID(peer && peer->handler);
    CHECK_NULL_VOID(key);
    peer->handler->SendFunctionKey(
        Converter::Convert<int32_t>(*key)
    );
}
void CloseImpl(Ark_WebKeyboardController peer)
{
    CHECK_NULL_VOID(peer && peer->handler);
    peer->handler->Close();
}
} // WebKeyboardControllerAccessor
const GENERATED_ArkUIWebKeyboardControllerAccessor* GetWebKeyboardControllerAccessor()
{
    static const GENERATED_ArkUIWebKeyboardControllerAccessor WebKeyboardControllerAccessorImpl {
        WebKeyboardControllerAccessor::DestroyPeerImpl,
        WebKeyboardControllerAccessor::CtorImpl,
        WebKeyboardControllerAccessor::GetFinalizerImpl,
        WebKeyboardControllerAccessor::InsertTextImpl,
        WebKeyboardControllerAccessor::DeleteForwardImpl,
        WebKeyboardControllerAccessor::DeleteBackwardImpl,
        WebKeyboardControllerAccessor::SendFunctionKeyImpl,
        WebKeyboardControllerAccessor::CloseImpl,
    };
    return &WebKeyboardControllerAccessorImpl;
}

}
