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
#include "core/interfaces/native/implementation/text_area_controller_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace TextAreaControllerAccessor {
static void DestroyPeer(TextAreaControllerPeer* peer)
{
    if (peer) {
        delete peer;
    }
}
TextAreaControllerPeer* CtorImpl()
{
    return new TextAreaControllerPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeer);
}
void CaretPositionImpl(TextAreaControllerPeer* peer,
                       const Ark_Number* value)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(peer->GetController());
    CHECK_NULL_VOID(value);
    peer->GetController()->CaretPosition(Converter::Convert<int32_t>(*value));
}
void SetTextSelectionImpl(TextAreaControllerPeer* peer,
                          const Ark_Number* selectionStart,
                          const Ark_Number* selectionEnd,
                          const Opt_SelectionOptions* options)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(peer->GetController());
    CHECK_NULL_VOID(selectionStart);
    CHECK_NULL_VOID(selectionEnd);
    std::optional<SelectionOptions> selectionOptions = std::nullopt;
    if (options) {
        selectionOptions = Converter::OptConvert<SelectionOptions>(*options);
    }
    peer->GetController()->SetTextSelection(
        Converter::Convert<int32_t>(*selectionStart),
        Converter::Convert<int32_t>(*selectionEnd),
        selectionOptions);
}
void StopEditingImpl(TextAreaControllerPeer* peer)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(peer->GetController());
    peer->GetController()->StopEditing();
}
} // TextAreaControllerAccessor
const GENERATED_ArkUITextAreaControllerAccessor* GetTextAreaControllerAccessor()
{
    static const GENERATED_ArkUITextAreaControllerAccessor TextAreaControllerAccessorImpl {
        TextAreaControllerAccessor::CtorImpl,
        TextAreaControllerAccessor::GetFinalizerImpl,
        TextAreaControllerAccessor::CaretPositionImpl,
        TextAreaControllerAccessor::SetTextSelectionImpl,
        TextAreaControllerAccessor::StopEditingImpl,
    };
    return &TextAreaControllerAccessorImpl;
}

}
