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
namespace Drawing_PenAccessor {
void DestroyPeerImpl(Ark_drawing_Pen peer)
{
}
Ark_drawing_Pen CtorImpl()
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void SetMiterLimitImpl(Ark_drawing_Pen peer,
                       const Ark_Number* miter)
{
}
Ark_Number GetMiterLimitImpl(Ark_drawing_Pen peer)
{
    return {};
}
void SetShaderEffectImpl(Ark_drawing_Pen peer,
                         Ark_drawing_ShaderEffect shaderEffect)
{
}
void SetColor0Impl(Ark_drawing_Pen peer,
                   const Ark_common2D_Color* color)
{
}
void SetColor1Impl(Ark_drawing_Pen peer,
                   const Ark_Number* color)
{
}
void SetColor2Impl(Ark_drawing_Pen peer,
                   const Ark_Number* alpha,
                   const Ark_Number* red,
                   const Ark_Number* green,
                   const Ark_Number* blue)
{
}
Ark_common2D_Color GetColorImpl(Ark_drawing_Pen peer)
{
    return {};
}
Ark_Number GetHexColorImpl(Ark_drawing_Pen peer)
{
    return {};
}
void SetStrokeWidthImpl(Ark_drawing_Pen peer,
                        const Ark_Number* width)
{
}
Ark_Number GetWidthImpl(Ark_drawing_Pen peer)
{
    return {};
}
void SetAntiAliasImpl(Ark_drawing_Pen peer,
                      Ark_Boolean aa)
{
}
Ark_Boolean IsAntiAliasImpl(Ark_drawing_Pen peer)
{
    return {};
}
void SetAlphaImpl(Ark_drawing_Pen peer,
                  const Ark_Number* alpha)
{
}
Ark_Number GetAlphaImpl(Ark_drawing_Pen peer)
{
    return {};
}
void SetColorFilterImpl(Ark_drawing_Pen peer,
                        Ark_drawing_ColorFilter filter)
{
}
Ark_drawing_ColorFilter GetColorFilterImpl(Ark_drawing_Pen peer)
{
    return {};
}
void SetImageFilterImpl(Ark_drawing_Pen peer,
                        const Opt_drawing_ImageFilter* filter)
{
}
void SetMaskFilterImpl(Ark_drawing_Pen peer,
                       Ark_drawing_MaskFilter filter)
{
}
void SetPathEffectImpl(Ark_drawing_Pen peer,
                       Ark_drawing_PathEffect effect)
{
}
void SetShadowLayerImpl(Ark_drawing_Pen peer,
                        Ark_drawing_ShadowLayer shadowLayer)
{
}
void SetBlendModeImpl(Ark_drawing_Pen peer,
                      Ark_drawing_BlendMode mode)
{
}
void SetDitherImpl(Ark_drawing_Pen peer,
                   Ark_Boolean dither)
{
}
void SetJoinStyleImpl(Ark_drawing_Pen peer,
                      Ark_drawing_JoinStyle style)
{
}
Ark_drawing_JoinStyle GetJoinStyleImpl(Ark_drawing_Pen peer)
{
    return {};
}
void SetCapStyleImpl(Ark_drawing_Pen peer,
                     Ark_drawing_CapStyle style)
{
}
Ark_drawing_CapStyle GetCapStyleImpl(Ark_drawing_Pen peer)
{
    return {};
}
void ResetImpl(Ark_drawing_Pen peer)
{
}
Ark_Boolean GetFillPathImpl(Ark_drawing_Pen peer,
                            Ark_drawing_Path src,
                            Ark_drawing_Path dst)
{
    return {};
}
} // Drawing_PenAccessor
const GENERATED_ArkUIDrawing_PenAccessor* GetDrawing_PenAccessor()
{
    static const GENERATED_ArkUIDrawing_PenAccessor Drawing_PenAccessorImpl {
        Drawing_PenAccessor::DestroyPeerImpl,
        Drawing_PenAccessor::CtorImpl,
        Drawing_PenAccessor::GetFinalizerImpl,
        Drawing_PenAccessor::SetMiterLimitImpl,
        Drawing_PenAccessor::GetMiterLimitImpl,
        Drawing_PenAccessor::SetShaderEffectImpl,
        Drawing_PenAccessor::SetColor0Impl,
        Drawing_PenAccessor::SetColor1Impl,
        Drawing_PenAccessor::SetColor2Impl,
        Drawing_PenAccessor::GetColorImpl,
        Drawing_PenAccessor::GetHexColorImpl,
        Drawing_PenAccessor::SetStrokeWidthImpl,
        Drawing_PenAccessor::GetWidthImpl,
        Drawing_PenAccessor::SetAntiAliasImpl,
        Drawing_PenAccessor::IsAntiAliasImpl,
        Drawing_PenAccessor::SetAlphaImpl,
        Drawing_PenAccessor::GetAlphaImpl,
        Drawing_PenAccessor::SetColorFilterImpl,
        Drawing_PenAccessor::GetColorFilterImpl,
        Drawing_PenAccessor::SetImageFilterImpl,
        Drawing_PenAccessor::SetMaskFilterImpl,
        Drawing_PenAccessor::SetPathEffectImpl,
        Drawing_PenAccessor::SetShadowLayerImpl,
        Drawing_PenAccessor::SetBlendModeImpl,
        Drawing_PenAccessor::SetDitherImpl,
        Drawing_PenAccessor::SetJoinStyleImpl,
        Drawing_PenAccessor::GetJoinStyleImpl,
        Drawing_PenAccessor::SetCapStyleImpl,
        Drawing_PenAccessor::GetCapStyleImpl,
        Drawing_PenAccessor::ResetImpl,
        Drawing_PenAccessor::GetFillPathImpl,
    };
    return &Drawing_PenAccessorImpl;
}

}
