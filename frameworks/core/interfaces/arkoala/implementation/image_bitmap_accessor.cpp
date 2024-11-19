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
#include "core/interfaces/arkoala/implementation/image_bitmap_peer_impl.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ImageBitmapAccessor {
static void DestroyPeer(ImageBitmapPeer *peer)
{
    if (peer) {
        peer->Close();
        delete peer;
    }
}
ImageBitmapPeer* CtorImpl(const Ark_String* src)
{
    auto peer = new ImageBitmapPeer();
    auto stringSrc = Converter::Convert<std::string>(*src);
    if (!stringSrc.empty()) {
        peer->LoadImage(stringSrc);
    }
    return peer;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeer);
}
void CloseImpl(ImageBitmapPeer* peer)
{
    CHECK_NULL_VOID(peer);
    peer->Close();
}
Ark_Int32 GetHeightImpl(ImageBitmapPeer* peer)
{
    CHECK_NULL_RETURN(peer, 0);
    return peer->GetHeight();
}
Ark_Int32 GetWidthImpl(ImageBitmapPeer* peer)
{
    CHECK_NULL_RETURN(peer, 0);
    return peer->GetWidth();
}
} // ImageBitmapAccessor
const GENERATED_ArkUIImageBitmapAccessor* GetImageBitmapAccessor()
{
    static const GENERATED_ArkUIImageBitmapAccessor ImageBitmapAccessorImpl {
        ImageBitmapAccessor::CtorImpl,
        ImageBitmapAccessor::GetFinalizerImpl,
        ImageBitmapAccessor::CloseImpl,
        ImageBitmapAccessor::GetHeightImpl,
        ImageBitmapAccessor::GetWidthImpl,
    };
    return &ImageBitmapAccessorImpl;
}

}
