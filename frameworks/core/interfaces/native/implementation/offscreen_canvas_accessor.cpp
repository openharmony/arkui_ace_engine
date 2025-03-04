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
namespace OffscreenCanvasAccessor {
void DestroyPeerImpl(Ark_OffscreenCanvas peer)
{
}
Ark_OffscreenCanvas CtorImpl(const Ark_Number* width,
                             const Ark_Number* height)
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_ImageBitmap TransferToImageBitmapImpl(Ark_OffscreenCanvas peer)
{
    return {};
}
Ark_OffscreenCanvasRenderingContext2D GetContext2dImpl(Ark_OffscreenCanvas peer,
                                                       const Opt_RenderingContextSettings* options)
{
    return {};
}
Ark_Number GetHeightImpl(Ark_OffscreenCanvas peer)
{
    return {};
}
void SetHeightImpl(Ark_OffscreenCanvas peer,
                   const Ark_Number* height)
{
}
Ark_Number GetWidthImpl(Ark_OffscreenCanvas peer)
{
    return {};
}
void SetWidthImpl(Ark_OffscreenCanvas peer,
                  const Ark_Number* width)
{
}
} // OffscreenCanvasAccessor
const GENERATED_ArkUIOffscreenCanvasAccessor* GetOffscreenCanvasAccessor()
{
    static const GENERATED_ArkUIOffscreenCanvasAccessor OffscreenCanvasAccessorImpl {
        OffscreenCanvasAccessor::DestroyPeerImpl,
        OffscreenCanvasAccessor::CtorImpl,
        OffscreenCanvasAccessor::GetFinalizerImpl,
        OffscreenCanvasAccessor::TransferToImageBitmapImpl,
        OffscreenCanvasAccessor::GetContext2dImpl,
        OffscreenCanvasAccessor::GetHeightImpl,
        OffscreenCanvasAccessor::SetHeightImpl,
        OffscreenCanvasAccessor::GetWidthImpl,
        OffscreenCanvasAccessor::SetWidthImpl,
    };
    return &OffscreenCanvasAccessorImpl;
}

}
