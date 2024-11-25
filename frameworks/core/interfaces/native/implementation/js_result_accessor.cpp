/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/implementation/js_result_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace JsResultAccessor {
JsResultPeer* CtorImpl()
{
    return new JsResultPeer();
}
static void DestroyPeer(JsResultPeer *peer)
{
    CHECK_NULL_VOID(peer);
    peer->result = nullptr;
    delete peer;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<Ark_NativePointer>(DestroyPeer);
}
void HandleCancelImpl(JsResultPeer* peer)
{
    CHECK_NULL_VOID(peer && peer->result);
    peer->result->Cancel();
}
void HandleConfirmImpl(JsResultPeer* peer)
{
    CHECK_NULL_VOID(peer && peer->result);
    peer->result->Confirm();
}
void HandlePromptConfirmImpl(JsResultPeer* peer,
                             const Ark_String* result)
{
    CHECK_NULL_VOID(peer && peer->result);
    CHECK_NULL_VOID(result);
    peer->result->Confirm(
        Converter::Convert<std::string>(*result)
    );
}
} // JsResultAccessor
const GENERATED_ArkUIJsResultAccessor* GetJsResultAccessor()
{
    static const GENERATED_ArkUIJsResultAccessor JsResultAccessorImpl {
        JsResultAccessor::CtorImpl,
        JsResultAccessor::GetFinalizerImpl,
        JsResultAccessor::HandleCancelImpl,
        JsResultAccessor::HandleConfirmImpl,
        JsResultAccessor::HandlePromptConfirmImpl,
    };
    return &JsResultAccessorImpl;
}

}
