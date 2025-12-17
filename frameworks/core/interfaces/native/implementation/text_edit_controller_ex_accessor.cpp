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

#include "core/interfaces/native/implementation/text_edit_controller_ex_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::Converter {
void AssignArkValue(Ark_PreviewText& dst, const PreviewTextInfo& src, ConvContext *ctx);
} // namespace OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
namespace TextEditControllerExAccessor {
void DestroyPeerImpl(Ark_TextEditControllerEx peer)
{
    delete peer;
}
Ark_TextEditControllerEx ConstructImpl()
{
    LOGE("TextEditControllerExPeer is an abstract class.");
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Opt_Boolean IsEditingImpl(Ark_TextEditControllerEx peer)
{
    CHECK_NULL_RETURN(peer, Converter::ArkValue<Opt_Boolean>(Ark_Empty()));
    return Converter::ArkValue<Opt_Boolean>(peer->IsEditing());
}
void StopEditingImpl(Ark_TextEditControllerEx peer)
{
    CHECK_NULL_VOID(peer);
    peer->StopEditing();
}
Opt_Boolean SetCaretOffsetImpl(Ark_TextEditControllerEx peer,
                               const Ark_Number* offset)
{
    CHECK_NULL_RETURN(peer && offset, Converter::ArkValue<Opt_Boolean>(Ark_Empty()));
    auto offsetConv = Converter::Convert<int32_t>(*offset);
    return Converter::ArkValue<Opt_Boolean>(peer->SetCaretOffset(offsetConv));
}
Opt_Number GetCaretOffsetImpl(Ark_TextEditControllerEx peer)
{
    CHECK_NULL_RETURN(peer, Converter::ArkValue<Opt_Number>(Ark_Empty()));
    return Converter::ArkValue<Opt_Number>(peer->GetCaretOffset());
}
Opt_PreviewText GetPreviewTextImpl(Ark_TextEditControllerEx peer)
{
    CHECK_NULL_RETURN(peer, Converter::ArkValue<Opt_PreviewText>(Ark_Empty()));
    auto result = peer->GetPreviewText();
    return Converter::ArkValue<Opt_PreviewText>(result, Converter::FC);
}
} // TextEditControllerExAccessor
const GENERATED_ArkUITextEditControllerExAccessor* GetTextEditControllerExAccessor()
{
    static const GENERATED_ArkUITextEditControllerExAccessor TextEditControllerExAccessorImpl {
        TextEditControllerExAccessor::DestroyPeerImpl,
        TextEditControllerExAccessor::ConstructImpl,
        TextEditControllerExAccessor::GetFinalizerImpl,
        TextEditControllerExAccessor::IsEditingImpl,
        TextEditControllerExAccessor::StopEditingImpl,
        TextEditControllerExAccessor::SetCaretOffsetImpl,
        TextEditControllerExAccessor::GetCaretOffsetImpl,
        TextEditControllerExAccessor::GetPreviewTextImpl,
    };
    return &TextEditControllerExAccessorImpl;
}

}
