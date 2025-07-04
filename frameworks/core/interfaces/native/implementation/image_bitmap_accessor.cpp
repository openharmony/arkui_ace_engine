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

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ImageBitmapAccessor {
void DestroyPeerImpl(Ark_ImageBitmap peer)
{
    auto peerImpl = reinterpret_cast<ImageBitmapPeerImpl *>(peer);
    if (peerImpl) {
        delete peerImpl;
    }
}
Ark_ImageBitmap ConstructImpl(const Ark_Union_PixelMap_String* src,
                              const Opt_LengthMetricsUnit* unit)
{
    return {};
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void CloseImpl(Ark_ImageBitmap peer)
{
}
Ark_Number GetHeightImpl(Ark_ImageBitmap peer)
{
    return {};
}
void SetHeightImpl(Ark_ImageBitmap peer,
                   const Ark_Number* height)
{
}
Ark_Number GetWidthImpl(Ark_ImageBitmap peer)
{
    return {};
}
void SetWidthImpl(Ark_ImageBitmap peer,
                  const Ark_Number* width)
{
}
} // ImageBitmapAccessor
const GENERATED_ArkUIImageBitmapAccessor* GetImageBitmapAccessor()
{
    static const GENERATED_ArkUIImageBitmapAccessor ImageBitmapAccessorImpl {
        ImageBitmapAccessor::DestroyPeerImpl,
        ImageBitmapAccessor::ConstructImpl,
        ImageBitmapAccessor::GetFinalizerImpl,
        ImageBitmapAccessor::CloseImpl,
        ImageBitmapAccessor::GetHeightImpl,
        ImageBitmapAccessor::SetHeightImpl,
        ImageBitmapAccessor::GetWidthImpl,
        ImageBitmapAccessor::SetWidthImpl,
    };
    return &ImageBitmapAccessorImpl;
}

struct ImageBitmapPeer {
    virtual ~ImageBitmapPeer() = default;
};
}
