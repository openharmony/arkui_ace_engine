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
#include "core/interfaces/arkoala/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace WebContextMenuParamAccessor {
void DestroyPeerImpl(WebContextMenuParamPeer* peer)
{
}
WebContextMenuParamPeer* CtorImpl()
{
    return new WebContextMenuParamPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Int32 XImpl(WebContextMenuParamPeer* peer)
{
    return 0;
}
Ark_Int32 YImpl(WebContextMenuParamPeer* peer)
{
    return 0;
}
void GetLinkUrlImpl(WebContextMenuParamPeer* peer)
{
}
void GetUnfilteredLinkUrlImpl(WebContextMenuParamPeer* peer)
{
}
void GetSourceUrlImpl(WebContextMenuParamPeer* peer)
{
}
Ark_Boolean ExistsImageContentsImpl(WebContextMenuParamPeer* peer)
{
    return 0;
}
Ark_NativePointer GetMediaTypeImpl(WebContextMenuParamPeer* peer)
{
    return 0;
}
void GetSelectionTextImpl(WebContextMenuParamPeer* peer)
{
}
Ark_NativePointer GetSourceTypeImpl(WebContextMenuParamPeer* peer)
{
    return 0;
}
Ark_NativePointer GetInputFieldTypeImpl(WebContextMenuParamPeer* peer)
{
    return 0;
}
Ark_Boolean IsEditableImpl(WebContextMenuParamPeer* peer)
{
    return 0;
}
Ark_Int32 GetEditStateFlagsImpl(WebContextMenuParamPeer* peer)
{
    return 0;
}
Ark_Int32 GetPreviewWidthImpl(WebContextMenuParamPeer* peer)
{
    return 0;
}
Ark_Int32 GetPreviewHeightImpl(WebContextMenuParamPeer* peer)
{
    return 0;
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

}
