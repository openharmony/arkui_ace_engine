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
#include "arkoala_api_generated.h"
#include "pixel_map_peer.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace Image_PixelMapAccessor {
void DestroyPeerImpl(Ark_image_PixelMap peer)
{
    image_PixelMapPeer::Destroy(peer);
}
Ark_image_PixelMap CtorImpl()
{
    return image_PixelMapPeer::Create({});
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void ReadPixelsToBufferSyncImpl(Ark_image_PixelMap peer,
                                const Ark_Buffer* dst)
{
}
void WriteBufferToPixelsImpl(Ark_image_PixelMap peer,
                             const Ark_Buffer* src)
{
}
Ark_Boolean GetIsEditableImpl(Ark_image_PixelMap peer)
{
    return {};
}
Ark_Boolean GetIsStrideAlignmentImpl(Ark_image_PixelMap peer)
{
    return {};
}
} // Image_PixelMapAccessor
const GENERATED_ArkUIImage_PixelMapAccessor* GetImage_PixelMapAccessor()
{
    static const GENERATED_ArkUIImage_PixelMapAccessor Image_PixelMapAccessorImpl {
        Image_PixelMapAccessor::DestroyPeerImpl,
        Image_PixelMapAccessor::CtorImpl,
        Image_PixelMapAccessor::GetFinalizerImpl,
        Image_PixelMapAccessor::ReadPixelsToBufferSyncImpl,
        Image_PixelMapAccessor::WriteBufferToPixelsImpl,
        Image_PixelMapAccessor::GetIsEditableImpl,
        Image_PixelMapAccessor::GetIsStrideAlignmentImpl,
    };
    return &Image_PixelMapAccessorImpl;
}

}
