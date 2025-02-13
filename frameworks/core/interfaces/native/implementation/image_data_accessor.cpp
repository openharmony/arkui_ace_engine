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
namespace ImageDataAccessor {
void DestroyPeerImpl(ImageDataPeer* peer)
{
}
Ark_ImageData CtorImpl(const Ark_Number* width,
                       const Ark_Number* height,
                       const Opt_Buffer* data)
{
    return {};
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Int32 GetHeightImpl(ImageDataPeer* peer)
{
    return {};
}
Ark_Int32 GetWidthImpl(ImageDataPeer* peer)
{
    return {};
}
} // ImageDataAccessor
const GENERATED_ArkUIImageDataAccessor* GetImageDataAccessor()
{
    static const GENERATED_ArkUIImageDataAccessor ImageDataAccessorImpl {
        ImageDataAccessor::DestroyPeerImpl,
        ImageDataAccessor::CtorImpl,
        ImageDataAccessor::GetFinalizerImpl,
        ImageDataAccessor::GetHeightImpl,
        ImageDataAccessor::GetWidthImpl,
    };
    return &ImageDataAccessorImpl;
}

struct ImageDataPeer {
    virtual ~ImageDataPeer() = default;
};
}
