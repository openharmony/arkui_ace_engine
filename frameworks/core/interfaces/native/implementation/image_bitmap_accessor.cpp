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
#include "core/interfaces/native/implementation/image_bitmap_peer_impl.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ImageBitmapAccessor {
const auto ARK_ERROR_VALUE = Converter::ArkValue<Ark_Number>(0);
void DestroyPeerImpl(Ark_ImageBitmap peer)
{
    if (peer) {
        peer->DecRefCount();
    }
}
Ark_ImageBitmap CtorImpl(const Ark_String* src)
{
    auto peer = Referenced::MakeRefPtr<ImageBitmapPeer>();
    peer->IncRefCount();
    std::string stringSrc;
    if (src) {
        stringSrc = Converter::Convert<std::string>(*src);
    }
    peer->SetOptions(stringSrc);
    return reinterpret_cast<ImageBitmapPeer*>(Referenced::RawPtr(peer));
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void CloseImpl(Ark_ImageBitmap peer)
{
    CHECK_NULL_VOID(peer);
    peer->OnClose();
}
Ark_Number GetHeightImpl(Ark_ImageBitmap peer)
{
    CHECK_NULL_RETURN(peer, ARK_ERROR_VALUE);
    auto height = peer->OnGetHeight();
    return NG::Converter::ArkValue<Ark_Number>(static_cast<int32_t>(height));
}
Ark_Number GetWidthImpl(Ark_ImageBitmap peer)
{
    CHECK_NULL_RETURN(peer, ARK_ERROR_VALUE);
    double width = peer->OnGetWidth();
    return NG::Converter::ArkValue<Ark_Number>(static_cast<int32_t>(width));
}
} // ImageBitmapAccessor
const GENERATED_ArkUIImageBitmapAccessor* GetImageBitmapAccessor()
{
    static const GENERATED_ArkUIImageBitmapAccessor ImageBitmapAccessorImpl {
        ImageBitmapAccessor::DestroyPeerImpl,
        ImageBitmapAccessor::CtorImpl,
        ImageBitmapAccessor::GetFinalizerImpl,
        ImageBitmapAccessor::CloseImpl,
        ImageBitmapAccessor::GetHeightImpl,
        ImageBitmapAccessor::GetWidthImpl,
    };
    return &ImageBitmapAccessorImpl;
}
}
