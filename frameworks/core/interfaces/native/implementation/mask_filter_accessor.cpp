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
namespace drawing_MaskFilterAccessor {
void DestroyPeerImpl(Ark_drawing_MaskFilter peer)
{
}
Ark_drawing_MaskFilter ConstructImpl()
{
    return {};
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_drawing_MaskFilter CreateBlurMaskFilterImpl(Ark_drawing_BlurType blurType,
                                                const Ark_Number* sigma)
{
    return {};
}
} // drawing_MaskFilterAccessor
const GENERATED_ArkUIDrawing_MaskFilterAccessor* GetDrawing_MaskFilterAccessor()
{
    static const GENERATED_ArkUIDrawing_MaskFilterAccessor Drawing_MaskFilterAccessorImpl {
        drawing_MaskFilterAccessor::DestroyPeerImpl,
        drawing_MaskFilterAccessor::ConstructImpl,
        drawing_MaskFilterAccessor::GetFinalizerImpl,
        drawing_MaskFilterAccessor::CreateBlurMaskFilterImpl,
    };
    return &Drawing_MaskFilterAccessorImpl;
}

}
