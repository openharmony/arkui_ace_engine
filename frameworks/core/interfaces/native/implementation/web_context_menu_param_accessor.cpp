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
#include "core/interfaces/native/implementation/web_context_menu_param_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace WebContextMenuParamAccessor {
void DestroyPeerImpl(Ark_WebContextMenuParam peer)
{
    CHECK_NULL_VOID(peer);
    peer->handler = nullptr;
    delete peer;
}
Ark_WebContextMenuParam CtorImpl()
{
    return new WebContextMenuParamPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Number XImpl(Ark_WebContextMenuParam peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer && peer->handler, errValue);
    return Converter::ArkValue<Ark_Number>(peer->handler->GetXCoord());
}
Ark_Number YImpl(Ark_WebContextMenuParam peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer && peer->handler, errValue);
    return Converter::ArkValue<Ark_Number>(peer->handler->GetYCoord());
}
Ark_String GetLinkUrlImpl(Ark_WebContextMenuParam peer)
{
    CHECK_NULL_RETURN(peer && peer->handler, {});
    peer->handler->GetLinkUrl();
    // value need to be returned
    LOGE("WebContextMenuParamAccessor::GetLinkUrlImpl - return value need to be supported");
    return {};
}
Ark_String GetUnfilteredLinkUrlImpl(Ark_WebContextMenuParam peer)
{
    CHECK_NULL_RETURN(peer && peer->handler, {});
    peer->handler->GetUnfilteredLinkUrl();
    // value need to be returned
    LOGE("WebContextMenuParamAccessor::GetUnfilteredLinkUrlImpl - return value need to be supported");
    return {};
}
Ark_String GetSourceUrlImpl(Ark_WebContextMenuParam peer)
{
    CHECK_NULL_RETURN(peer && peer->handler, {});
    peer->handler->GetSourceUrl();
    // value need to be returned
    LOGE("WebContextMenuParamAccessor::GetSourceUrlImpl - return value need to be supported");
    return {};
}
Ark_Boolean ExistsImageContentsImpl(Ark_WebContextMenuParam peer)
{
    CHECK_NULL_RETURN(peer && peer->handler, false);
    return Converter::ArkValue<Ark_Boolean>(peer->handler->HasImageContents());
}
Ark_ContextMenuMediaType GetMediaTypeImpl(Ark_WebContextMenuParam peer)
{
    CHECK_NULL_RETURN(peer && peer->handler, {});
    peer->handler->GetMediaType();
    // correct value type need to be returned
    LOGE("WebContextMenuParamAccessor::GetMediaTypeImpl - return value need to be supported");
    return {};
}
Ark_String GetSelectionTextImpl(Ark_WebContextMenuParam peer)
{
    CHECK_NULL_RETURN(peer && peer->handler, {});
    peer->handler->GetSelectionText();
    // value need to be returned
    LOGE("WebContextMenuParamAccessor::GetSelectionTextImpl - return value need to be supported");
    return {};
}
Ark_ContextMenuSourceType GetSourceTypeImpl(Ark_WebContextMenuParam peer)
{
    CHECK_NULL_RETURN(peer && peer->handler, {});
    peer->handler->GetSourceType();
    // correct value type need to be returned
    LOGE("WebContextMenuParamAccessor::GetSourceTypeImpl - return value need to be supported");
    return {};
}
Ark_ContextMenuInputFieldType GetInputFieldTypeImpl(Ark_WebContextMenuParam peer)
{
    CHECK_NULL_RETURN(peer && peer->handler, {});
    peer->handler->GetInputFieldType();
    // correct value type need to be returned
    LOGE("WebContextMenuParamAccessor::GetInputFieldTypeImpl - return value need to be supported");
    return {};
}
Ark_Boolean IsEditableImpl(Ark_WebContextMenuParam peer)
{
    CHECK_NULL_RETURN(peer && peer->handler, false);
    return Converter::ArkValue<Ark_Boolean>(peer->handler->IsEditable());
}
Ark_Number GetEditStateFlagsImpl(Ark_WebContextMenuParam peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer && peer->handler, errValue);
    return Converter::ArkValue<Ark_Number>(peer->handler->GetEditStateFlags());
}
Ark_Number GetPreviewWidthImpl(Ark_WebContextMenuParam peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer && peer->handler, errValue);
    return Converter::ArkValue<Ark_Number>(peer->GetPreviewWidth());
}
Ark_Number GetPreviewHeightImpl(Ark_WebContextMenuParam peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer && peer->handler, errValue);
    return Converter::ArkValue<Ark_Number>(peer->GetPreviewHeight());
}
} // WebContextMenuParamAccessor
const GENERATED_ArkUIWebContextMenuParamAccessor* GetWebContextMenuParamAccessor()
{
    static const GENERATED_ArkUIWebContextMenuParamAccessor WebContextMenuParamAccessorImpl {
        WebContextMenuParamAccessor::DestroyPeerImpl,
        WebContextMenuParamAccessor::CtorImpl,
        WebContextMenuParamAccessor::GetFinalizerImpl,
        WebContextMenuParamAccessor::XImpl,
        WebContextMenuParamAccessor::YImpl,
        WebContextMenuParamAccessor::GetLinkUrlImpl,
        WebContextMenuParamAccessor::GetUnfilteredLinkUrlImpl,
        WebContextMenuParamAccessor::GetSourceUrlImpl,
        WebContextMenuParamAccessor::ExistsImageContentsImpl,
        WebContextMenuParamAccessor::GetMediaTypeImpl,
        WebContextMenuParamAccessor::GetSelectionTextImpl,
        WebContextMenuParamAccessor::GetSourceTypeImpl,
        WebContextMenuParamAccessor::GetInputFieldTypeImpl,
        WebContextMenuParamAccessor::IsEditableImpl,
        WebContextMenuParamAccessor::GetEditStateFlagsImpl,
        WebContextMenuParamAccessor::GetPreviewWidthImpl,
        WebContextMenuParamAccessor::GetPreviewHeightImpl,
    };
    return &WebContextMenuParamAccessorImpl;
}

struct WebContextMenuParamPeer {
    virtual ~WebContextMenuParamPeer() = default;
};
}
