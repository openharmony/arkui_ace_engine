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
#include "arkoala_api_generated.h"

#include "core/interfaces/native/implementation/text_menu_item_id_peer.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace TextMenuItemIdAccessor {
void DestroyPeerImpl(Ark_TextMenuItemId peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_TextMenuItemId CtorImpl()
{
    return PeerUtils::CreatePeer<TextMenuItemIdPeer>();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_TextMenuItemId OfImpl(const Ark_ResourceStr* id)
{
    auto peer = CtorImpl();
    CHECK_NULL_RETURN(id, peer);
    peer->id = Converter::OptConvert<std::string>(*id);
    return peer;
}
Ark_Boolean EqualsImpl(Ark_TextMenuItemId peer,
                       Ark_TextMenuItemId id)
{
    return Converter::ArkValue<Ark_Boolean>(peer && id && peer->id && id->id && peer->id.value() == id->id.value());
}
Ark_TextMenuItemId GetCUTImpl()
{
    auto peer = CtorImpl();
    peer->id = "OH_DEFAULT_CUT";
    return peer;
}
void SetCUTImpl(Ark_TextMenuItemId CUT)
{
}
Ark_TextMenuItemId GetCOPYImpl()
{
    auto peer = CtorImpl();
    peer->id = "OH_DEFAULT_COPY";
    return peer;
}
void SetCOPYImpl(Ark_TextMenuItemId COPY)
{
}
Ark_TextMenuItemId GetPASTEImpl()
{
    auto peer = CtorImpl();
    peer->id = "OH_DEFAULT_PASTE";
    return peer;
}
void SetPASTEImpl(Ark_TextMenuItemId PASTE)
{
}
Ark_TextMenuItemId GetSELECT_ALLImpl()
{
    auto peer = CtorImpl();
    peer->id = "OH_DEFAULT_SELECT_ALL";
    return peer;
}
void SetSELECT_ALLImpl(Ark_TextMenuItemId SELECT_ALL)
{
}
Ark_TextMenuItemId GetCOLLABORATION_SERVICEImpl()
{
    auto peer = CtorImpl();
    peer->id = "OH_DEFAULT_COLLABORATION_SERVICE";
    return peer;
}
void SetCOLLABORATION_SERVICEImpl(Ark_TextMenuItemId COLLABORATION_SERVICE)
{
}
Ark_TextMenuItemId GetCAMERA_INPUTImpl()
{
    auto peer = CtorImpl();
    peer->id = "OH_DEFAULT_CAMERA_INPUT";
    return peer;
}
void SetCAMERA_INPUTImpl(Ark_TextMenuItemId CAMERA_INPUT)
{
}
Ark_TextMenuItemId GetAI_WRITERImpl()
{
    auto peer = CtorImpl();
    peer->id = "OH_DEFAULT_AI_WRITE";
    return peer;
}
void SetAI_WRITERImpl(Ark_TextMenuItemId AI_WRITER)
{
}
Ark_TextMenuItemId GetTRANSLATEImpl()
{
    auto peer = CtorImpl();
    peer->id = "OH_DEFAULT_TRANSLATE";
    return peer;
}
void SetTRANSLATEImpl(Ark_TextMenuItemId TRANSLATE)
{
}
Ark_TextMenuItemId GetSEARCHImpl()
{
    auto peer = CtorImpl();
    peer->id = "OH_DEFAULT_SEARCH";
    return peer;
}
void SetSEARCHImpl(Ark_TextMenuItemId SEARCH)
{
}
Ark_TextMenuItemId GetSHAREImpl()
{
    auto peer = CtorImpl();
    peer->id = "OH_DEFAULT_SHARE";
    return peer;
}
void SetSHAREImpl(Ark_TextMenuItemId SHARE)
{
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
        TextMenuItemIdAccessor::GetCUTImpl,
        TextMenuItemIdAccessor::SetCUTImpl,
        TextMenuItemIdAccessor::GetCOPYImpl,
        TextMenuItemIdAccessor::SetCOPYImpl,
        TextMenuItemIdAccessor::GetPASTEImpl,
        TextMenuItemIdAccessor::SetPASTEImpl,
        TextMenuItemIdAccessor::GetSELECT_ALLImpl,
        TextMenuItemIdAccessor::SetSELECT_ALLImpl,
        TextMenuItemIdAccessor::GetCOLLABORATION_SERVICEImpl,
        TextMenuItemIdAccessor::SetCOLLABORATION_SERVICEImpl,
        TextMenuItemIdAccessor::GetCAMERA_INPUTImpl,
        TextMenuItemIdAccessor::SetCAMERA_INPUTImpl,
        TextMenuItemIdAccessor::GetAI_WRITERImpl,
        TextMenuItemIdAccessor::SetAI_WRITERImpl,
        TextMenuItemIdAccessor::GetTRANSLATEImpl,
        TextMenuItemIdAccessor::SetTRANSLATEImpl,
        TextMenuItemIdAccessor::GetSEARCHImpl,
        TextMenuItemIdAccessor::SetSEARCHImpl,
        TextMenuItemIdAccessor::GetSHAREImpl,
        TextMenuItemIdAccessor::SetSHAREImpl,
    };
    return &TextMenuItemIdAccessorImpl;
}

}
