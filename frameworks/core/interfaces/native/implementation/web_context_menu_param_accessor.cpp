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
#include "core/interfaces/native/implementation/web_context_menu_param_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace WebContextMenuParamAccessor {
WebContextMenuParamPeer* CtorImpl()
{
    return new WebContextMenuParamPeer();
}
static void DestroyPeer(WebContextMenuParamPeer *peer)
{
    CHECK_NULL_VOID(peer);
    peer->handler = nullptr;
    delete peer;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<Ark_NativePointer>(DestroyPeer);
}
Ark_Int32 XImpl(WebContextMenuParamPeer* peer)
{
    CHECK_NULL_RETURN(peer && peer->handler, 0);
    return static_cast<Ark_Int32>(peer->handler->GetXCoord());
}
Ark_Int32 YImpl(WebContextMenuParamPeer* peer)
{
    CHECK_NULL_RETURN(peer && peer->handler, 0);
    return static_cast<Ark_Int32>(peer->handler->GetYCoord());
}
void GetLinkUrlImpl(WebContextMenuParamPeer* peer)
{
    CHECK_NULL_VOID(peer && peer->handler);
    peer->handler->GetLinkUrl();
    // value need to be returned
    LOGE("WebContextMenuParamAccessor::GetLinkUrlImpl - return value need to be supported");
}
void GetUnfilteredLinkUrlImpl(WebContextMenuParamPeer* peer)
{
    CHECK_NULL_VOID(peer && peer->handler);
    peer->handler->GetUnfilteredLinkUrl();
    // value need to be returned
    LOGE("WebContextMenuParamAccessor::GetUnfilteredLinkUrlImpl - return value need to be supported");
}
void GetSourceUrlImpl(WebContextMenuParamPeer* peer)
{
    CHECK_NULL_VOID(peer && peer->handler);
    peer->handler->GetSourceUrl();
    // value need to be returned
    LOGE("WebContextMenuParamAccessor::GetSourceUrlImpl - return value need to be supported");
}
Ark_Boolean ExistsImageContentsImpl(WebContextMenuParamPeer* peer)
{
    CHECK_NULL_RETURN(peer && peer->handler, false);
    return Converter::ArkValue<Ark_Boolean>(peer->handler->HasImageContents());
}
Ark_NativePointer GetMediaTypeImpl(WebContextMenuParamPeer* peer)
{
    CHECK_NULL_RETURN(peer && peer->handler, 0);
    peer->handler->GetMediaType();
    // correct value type need to be returned
    LOGE("WebContextMenuParamAccessor::GetMediaTypeImpl - return value need to be supported");
    return 0;
}
void GetSelectionTextImpl(WebContextMenuParamPeer* peer)
{
    CHECK_NULL_VOID(peer && peer->handler);
    peer->handler->GetSelectionText();
    // value need to be returned
    LOGE("WebContextMenuParamAccessor::GetSelectionTextImpl - return value need to be supported");
}
Ark_NativePointer GetSourceTypeImpl(WebContextMenuParamPeer* peer)
{
    CHECK_NULL_RETURN(peer && peer->handler, 0);
    peer->handler->GetSourceType();
    // correct value type need to be returned
    LOGE("WebContextMenuParamAccessor::GetSourceTypeImpl - return value need to be supported");
    return 0;
}
Ark_NativePointer GetInputFieldTypeImpl(WebContextMenuParamPeer* peer)
{
    CHECK_NULL_RETURN(peer && peer->handler, 0);
    peer->handler->GetInputFieldType();
    // correct value type need to be returned
    LOGE("WebContextMenuParamAccessor::GetInputFieldTypeImpl - return value need to be supported");
    return 0;
}
Ark_Boolean IsEditableImpl(WebContextMenuParamPeer* peer)
{
    CHECK_NULL_RETURN(peer && peer->handler, false);
    return Converter::ArkValue<Ark_Boolean>(peer->handler->IsEditable());
}
Ark_Int32 GetEditStateFlagsImpl(WebContextMenuParamPeer* peer)
{
    CHECK_NULL_RETURN(peer && peer->handler, 0);
    return static_cast<Ark_Int32>(peer->handler->GetEditStateFlags());
}
} // WebContextMenuParamAccessor
const GENERATED_ArkUIWebContextMenuParamAccessor* GetWebContextMenuParamAccessor()
{
    static const GENERATED_ArkUIWebContextMenuParamAccessor WebContextMenuParamAccessorImpl {
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
    };
    return &WebContextMenuParamAccessorImpl;
}

}
