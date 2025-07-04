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
namespace drawing_ImageFilterAccessor {
void DestroyPeerImpl(Ark_drawing_ImageFilter peer)
{
}
Ark_drawing_ImageFilter ConstructImpl()
{
    return {};
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_drawing_ImageFilter CreateBlurImageFilterImpl(const Ark_Number* sigmaX,
                                                  const Ark_Number* sigmaY,
                                                  Ark_drawing_TileMode tileMode,
                                                  const Opt_drawing_ImageFilter* imageFilter)
{
    return {};
}
Ark_drawing_ImageFilter CreateFromColorFilterImpl(Ark_drawing_ColorFilter colorFilter,
                                                  const Opt_drawing_ImageFilter* imageFilter)
{
    return {};
}
} // drawing_ImageFilterAccessor
const GENERATED_ArkUIDrawing_ImageFilterAccessor* GetDrawing_ImageFilterAccessor()
{
    static const GENERATED_ArkUIDrawing_ImageFilterAccessor Drawing_ImageFilterAccessorImpl {
        drawing_ImageFilterAccessor::DestroyPeerImpl,
        drawing_ImageFilterAccessor::ConstructImpl,
        drawing_ImageFilterAccessor::GetFinalizerImpl,
        drawing_ImageFilterAccessor::CreateBlurImageFilterImpl,
        drawing_ImageFilterAccessor::CreateFromColorFilterImpl,
    };
    return &Drawing_ImageFilterAccessorImpl;
}

}
