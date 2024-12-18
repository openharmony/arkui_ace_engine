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
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

#include "core/interfaces/native/implementation/text_menu_item_id_peer.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace TextMenuItemIdAccessor {
void DestroyPeerImpl(TextMenuItemIdPeer* peer)
{
    CHECK_NULL_VOID(peer);
    peer->id = std::nullopt;
    delete peer;
}
Ark_NativePointer CtorImpl()
{
    return new TextMenuItemIdPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_NativePointer OfImpl(const Ark_ResourceStr* id)
{
    auto peer = static_cast<TextMenuItemIdPeer *>(CtorImpl());
    peer->id = Converter::OptConvert<std::string>(*id);
    return reinterpret_cast<Ark_NativePointer>(peer);
}
Ark_Boolean EqualsImpl(TextMenuItemIdPeer* peer,
                       const Ark_TextMenuItemId* id)
{
    CHECK_NULL_RETURN(peer && id && id->ptr, false);
    auto peer2 = static_cast<TextMenuItemIdPeer*>(id->ptr);
    CHECK_NULL_RETURN(peer->id && peer2->id, false);
    return Converter::ArkValue<Ark_Boolean>(peer->id.value() == peer2->id.value());
}
} // TextMenuItemIdAccessor
const GENERATED_ArkUITextMenuItemIdAccessor* GetTextMenuItemIdAccessor()
{
    static const GENERATED_ArkUITextMenuItemIdAccessor TextMenuItemIdAccessorImpl {
        TextMenuItemIdAccessor::DestroyPeerImpl,
        TextMenuItemIdAccessor::CtorImpl,
        TextMenuItemIdAccessor::GetFinalizerImpl,
        TextMenuItemIdAccessor::OfImpl,
        TextMenuItemIdAccessor::EqualsImpl,
    };
    return &TextMenuItemIdAccessorImpl;
}

struct TextMenuItemIdPeer {
    virtual ~TextMenuItemIdPeer() = default;
};
}
