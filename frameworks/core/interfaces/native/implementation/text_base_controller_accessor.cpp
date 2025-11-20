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
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
const GENERATED_ArkUILayoutManagerAccessor* GetLayoutManagerAccessor();
namespace TextBaseControllerAccessor {
void DestroyPeerImpl(Ark_TextBaseController peer)
{
    CHECK_NULL_VOID(peer);
    delete peer;
}
Ark_TextBaseController ConstructImpl()
{
    LOGE("TextBaseControllerPeer is an abstract class.");
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void SetSelectionImpl(Ark_TextBaseController peer,
                      Ark_Int32 selectionStart,
                      Ark_Int32 selectionEnd,
                      const Opt_SelectionOptions* options)
{
    CHECK_NULL_VOID(peer);
    auto selectionStartConv = Converter::Convert<int32_t>(selectionStart);
    auto selectionEndConv = Converter::Convert<int32_t>(selectionEnd);
    auto optionsConv = Converter::OptConvertPtr<SelectionOptions>(options);
    peer->SetSelection(selectionStartConv, selectionEndConv, optionsConv);
}
void CloseSelectionMenuImpl(Ark_TextBaseController peer)
{
    CHECK_NULL_VOID(peer);
    peer->CloseSelectionMenu();
}
Opt_LayoutManager GetLayoutManagerImpl(Ark_TextBaseController peer)
{
    CHECK_NULL_RETURN(peer && GetLayoutManagerAccessor(), Converter::ArkValue<Opt_LayoutManager>(Ark_Empty()));
    auto layoutManagerPeer = GetLayoutManagerAccessor()->construct();
    CHECK_NULL_RETURN(layoutManagerPeer,  Converter::ArkValue<Opt_LayoutManager>(Ark_Empty()));
    layoutManagerPeer->handler = peer->GetLayoutInfoInterface();
    return Converter::ArkValue<Opt_LayoutManager>(layoutManagerPeer);
}
} // TextBaseControllerAccessor
const GENERATED_ArkUITextBaseControllerAccessor* GetTextBaseControllerAccessor()
{
    static const GENERATED_ArkUITextBaseControllerAccessor TextBaseControllerAccessorImpl {
        TextBaseControllerAccessor::DestroyPeerImpl,
        TextBaseControllerAccessor::ConstructImpl,
        TextBaseControllerAccessor::GetFinalizerImpl,
        TextBaseControllerAccessor::SetSelectionImpl,
        TextBaseControllerAccessor::CloseSelectionMenuImpl,
        TextBaseControllerAccessor::GetLayoutManagerImpl,
    };
    return &TextBaseControllerAccessorImpl;
}

}
