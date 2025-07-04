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
void DestroyPeerImpl(Ark_ImageData peer)
{
}
Ark_ImageData ConstructImpl(const Ark_Number* width,
                            const Ark_Number* height,
                            const Opt_Buffer* data,
                            const Opt_LengthMetricsUnit* unit)
{
    return {};
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Buffer GetDataImpl(Ark_ImageData peer)
{
    return {};
}
void SetDataImpl(Ark_ImageData peer,
                 const Ark_Buffer* data)
{
}
Ark_Number GetHeightImpl(Ark_ImageData peer)
{
    return {};
}
void SetHeightImpl(Ark_ImageData peer,
                   const Ark_Number* height)
{
}
Ark_Number GetWidthImpl(Ark_ImageData peer)
{
    return {};
}
void SetWidthImpl(Ark_ImageData peer,
                  const Ark_Number* width)
{
}
} // ImageDataAccessor
const GENERATED_ArkUIImageDataAccessor* GetImageDataAccessor()
{
    static const GENERATED_ArkUIImageDataAccessor ImageDataAccessorImpl {
        ImageDataAccessor::DestroyPeerImpl,
        ImageDataAccessor::ConstructImpl,
        ImageDataAccessor::GetFinalizerImpl,
        ImageDataAccessor::GetDataImpl,
        ImageDataAccessor::SetDataImpl,
        ImageDataAccessor::GetHeightImpl,
        ImageDataAccessor::SetHeightImpl,
        ImageDataAccessor::GetWidthImpl,
        ImageDataAccessor::SetWidthImpl,
    };
    return &ImageDataAccessorImpl;
}

}
