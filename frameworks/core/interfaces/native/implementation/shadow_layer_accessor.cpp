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
namespace drawing_ShadowLayerAccessor {
void DestroyPeerImpl(Ark_drawing_ShadowLayer peer)
{
}
Ark_drawing_ShadowLayer ConstructImpl()
{
    return {};
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_drawing_ShadowLayer Create0Impl(const Ark_Number* blurRadius,
                                    const Ark_Number* x,
                                    const Ark_Number* y,
                                    const Ark_common2D_Color* color)
{
    return {};
}
Ark_drawing_ShadowLayer Create1Impl(const Ark_Number* blurRadius,
                                    const Ark_Number* x,
                                    const Ark_Number* y,
                                    const Ark_Number* color)
{
    return {};
}
} // drawing_ShadowLayerAccessor
const GENERATED_ArkUIDrawing_ShadowLayerAccessor* GetDrawing_ShadowLayerAccessor()
{
    static const GENERATED_ArkUIDrawing_ShadowLayerAccessor Drawing_ShadowLayerAccessorImpl {
        drawing_ShadowLayerAccessor::DestroyPeerImpl,
        drawing_ShadowLayerAccessor::ConstructImpl,
        drawing_ShadowLayerAccessor::GetFinalizerImpl,
        drawing_ShadowLayerAccessor::Create0Impl,
        drawing_ShadowLayerAccessor::Create1Impl,
    };
    return &Drawing_ShadowLayerAccessorImpl;
}

}
