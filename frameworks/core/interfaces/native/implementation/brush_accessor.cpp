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
namespace drawing_BrushAccessor {
void DestroyPeerImpl(Ark_drawing_Brush peer)
{
}
Ark_drawing_Brush Construct0Impl()
{
    return {};
}
Ark_drawing_Brush Construct1Impl(Ark_drawing_Brush brush)
{
    return {};
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void SetColor0Impl(Ark_drawing_Brush peer,
                   const Ark_common2D_Color* color)
{
}
void SetColor1Impl(Ark_drawing_Brush peer,
                   const Ark_Number* color)
{
}
void SetColor2Impl(Ark_drawing_Brush peer,
                   const Ark_Number* alpha,
                   const Ark_Number* red,
                   const Ark_Number* green,
                   const Ark_Number* blue)
{
}
Ark_common2D_Color GetColorImpl(Ark_drawing_Brush peer)
{
    return {};
}
Ark_Number GetHexColorImpl(Ark_drawing_Brush peer)
{
    return {};
}
void SetAntiAliasImpl(Ark_drawing_Brush peer,
                      Ark_Boolean aa)
{
}
Ark_Boolean IsAntiAliasImpl(Ark_drawing_Brush peer)
{
    return {};
}
void SetAlphaImpl(Ark_drawing_Brush peer,
                  const Ark_Number* alpha)
{
}
Ark_Number GetAlphaImpl(Ark_drawing_Brush peer)
{
    return {};
}
void SetColorFilterImpl(Ark_drawing_Brush peer,
                        Ark_drawing_ColorFilter filter)
{
}
Ark_drawing_ColorFilter GetColorFilterImpl(Ark_drawing_Brush peer)
{
    return {};
}
void SetImageFilterImpl(Ark_drawing_Brush peer,
                        const Opt_drawing_ImageFilter* filter)
{
}
void SetMaskFilterImpl(Ark_drawing_Brush peer,
                       Ark_drawing_MaskFilter filter)
{
}
void SetShadowLayerImpl(Ark_drawing_Brush peer,
                        Ark_drawing_ShadowLayer shadowLayer)
{
}
void SetShaderEffectImpl(Ark_drawing_Brush peer,
                         Ark_drawing_ShaderEffect shaderEffect)
{
}
void SetBlendModeImpl(Ark_drawing_Brush peer,
                      Ark_drawing_BlendMode mode)
{
}
void ResetImpl(Ark_drawing_Brush peer)
{
}
} // drawing_BrushAccessor
const GENERATED_ArkUIDrawing_BrushAccessor* GetDrawing_BrushAccessor()
{
    static const GENERATED_ArkUIDrawing_BrushAccessor Drawing_BrushAccessorImpl {
        drawing_BrushAccessor::DestroyPeerImpl,
        drawing_BrushAccessor::Construct0Impl,
        drawing_BrushAccessor::Construct1Impl,
        drawing_BrushAccessor::GetFinalizerImpl,
        drawing_BrushAccessor::SetColor0Impl,
        drawing_BrushAccessor::SetColor1Impl,
        drawing_BrushAccessor::SetColor2Impl,
        drawing_BrushAccessor::GetColorImpl,
        drawing_BrushAccessor::GetHexColorImpl,
        drawing_BrushAccessor::SetAntiAliasImpl,
        drawing_BrushAccessor::IsAntiAliasImpl,
        drawing_BrushAccessor::SetAlphaImpl,
        drawing_BrushAccessor::GetAlphaImpl,
        drawing_BrushAccessor::SetColorFilterImpl,
        drawing_BrushAccessor::GetColorFilterImpl,
        drawing_BrushAccessor::SetImageFilterImpl,
        drawing_BrushAccessor::SetMaskFilterImpl,
        drawing_BrushAccessor::SetShadowLayerImpl,
        drawing_BrushAccessor::SetShaderEffectImpl,
        drawing_BrushAccessor::SetBlendModeImpl,
        drawing_BrushAccessor::ResetImpl,
    };
    return &Drawing_BrushAccessorImpl;
}

}
