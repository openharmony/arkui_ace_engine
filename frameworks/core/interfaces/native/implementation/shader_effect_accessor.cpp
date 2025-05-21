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
namespace Drawing_ShaderEffectAccessor {
void DestroyPeerImpl(Ark_drawing_ShaderEffect peer)
{
}
Ark_drawing_ShaderEffect CtorImpl()
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_drawing_ShaderEffect CreateColorShaderImpl(const Ark_Number* color)
{
    return {};
}
Ark_drawing_ShaderEffect CreateLinearGradientImpl(const Ark_common2D_Point* startPt,
                                                  const Ark_common2D_Point* endPt,
                                                  const Array_Number* colors,
                                                  Ark_drawing_TileMode mode,
                                                  const Opt_Array_Number* pos,
                                                  const Opt_drawing_Matrix* matrix)
{
    return {};
}
Ark_drawing_ShaderEffect CreateRadialGradientImpl(const Ark_common2D_Point* centerPt,
                                                  const Ark_Number* radius,
                                                  const Array_Number* colors,
                                                  Ark_drawing_TileMode mode,
                                                  const Opt_Array_Number* pos,
                                                  const Opt_drawing_Matrix* matrix)
{
    return {};
}
Ark_drawing_ShaderEffect CreateSweepGradientImpl(const Ark_common2D_Point* centerPt,
                                                 const Array_Number* colors,
                                                 Ark_drawing_TileMode mode,
                                                 const Ark_Number* startAngle,
                                                 const Ark_Number* endAngle,
                                                 const Opt_Array_Number* pos,
                                                 const Opt_drawing_Matrix* matrix)
{
    return {};
}
Ark_drawing_ShaderEffect CreateConicalGradientImpl(const Ark_common2D_Point* startPt,
                                                   const Ark_Number* startRadius,
                                                   const Ark_common2D_Point* endPt,
                                                   const Ark_Number* endRadius,
                                                   const Array_Number* colors,
                                                   Ark_drawing_TileMode mode,
                                                   const Opt_Array_Number* pos,
                                                   const Opt_drawing_Matrix* matrix)
{
    return {};
}
} // Drawing_ShaderEffectAccessor
const GENERATED_ArkUIDrawing_ShaderEffectAccessor* GetDrawing_ShaderEffectAccessor()
{
    static const GENERATED_ArkUIDrawing_ShaderEffectAccessor Drawing_ShaderEffectAccessorImpl {
        Drawing_ShaderEffectAccessor::DestroyPeerImpl,
        Drawing_ShaderEffectAccessor::CtorImpl,
        Drawing_ShaderEffectAccessor::GetFinalizerImpl,
        Drawing_ShaderEffectAccessor::CreateColorShaderImpl,
        Drawing_ShaderEffectAccessor::CreateLinearGradientImpl,
        Drawing_ShaderEffectAccessor::CreateRadialGradientImpl,
        Drawing_ShaderEffectAccessor::CreateSweepGradientImpl,
        Drawing_ShaderEffectAccessor::CreateConicalGradientImpl,
    };
    return &Drawing_ShaderEffectAccessorImpl;
}

}
