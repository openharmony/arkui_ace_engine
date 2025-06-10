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

#include "core/interfaces/native/implementation/text_base_controller_peer.h"
#include "core/interfaces/native/implementation/layout_manager_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
const GENERATED_ArkUILayoutManagerAccessor* GetLayoutManagerAccessor();
namespace TextBaseControllerAccessor {
void DestroyPeerImpl(Ark_TextBaseController peer)
{
    delete peer;
}
Ark_TextBaseController CtorImpl()
{
    LOGE("TextBaseControllerPeer is an abstract class.");
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void SetSelectionImpl(Ark_TextBaseController peer,
                      const Ark_Number* selectionStart,
                      const Ark_Number* selectionEnd,
                      const Opt_SelectionOptions* options)
{
    CHECK_NULL_VOID(peer && selectionStart && selectionEnd);
    auto selectionStartConv = Converter::Convert<int32_t>(*selectionStart);
    auto selectionEndConv = Converter::Convert<int32_t>(*selectionEnd);
    auto optionsConv = options ? Converter::OptConvert<SelectionOptions>(*options) : std::nullopt;
    peer->SetSelection(selectionStartConv, selectionEndConv, optionsConv);
}
void CloseSelectionMenuImpl(Ark_TextBaseController peer)
{
    CHECK_NULL_VOID(peer);
    peer->CloseSelectionMenu();
}
Ark_LayoutManager GetLayoutManagerImpl(Ark_TextBaseController peer)
{
    CHECK_NULL_RETURN(peer && GetLayoutManagerAccessor(), nullptr);
    auto layoutManagerPeer = reinterpret_cast<LayoutManagerPeer*>(GetLayoutManagerAccessor()->ctor());
    CHECK_NULL_RETURN(layoutManagerPeer, nullptr);
    layoutManagerPeer->handler = peer->GetLayoutInfoInterface();
    return layoutManagerPeer;
}
} // TextBaseControllerAccessor
const GENERATED_ArkUITextBaseControllerAccessor* GetTextBaseControllerAccessor()
{
    static const GENERATED_ArkUITextBaseControllerAccessor TextBaseControllerAccessorImpl {
        TextBaseControllerAccessor::DestroyPeerImpl,
        TextBaseControllerAccessor::CtorImpl,
        TextBaseControllerAccessor::GetFinalizerImpl,
        TextBaseControllerAccessor::SetSelectionImpl,
        TextBaseControllerAccessor::CloseSelectionMenuImpl,
        TextBaseControllerAccessor::GetLayoutManagerImpl,
    };
    return &TextBaseControllerAccessorImpl;
}

struct TextBaseControllerPeer {
    virtual ~TextBaseControllerPeer() = default;
};
}
