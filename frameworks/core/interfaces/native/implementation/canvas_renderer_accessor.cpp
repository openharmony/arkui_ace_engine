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
namespace CanvasRendererAccessor {
void DestroyPeerImpl(Ark_CanvasRenderer peer)
{
}
Ark_CanvasRenderer CtorImpl()
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void DrawImage0Impl(Ark_CanvasRenderer peer,
                    const Ark_Union_ImageBitmap_PixelMap* image,
                    const Ark_Number* dx,
                    const Ark_Number* dy)
{
}
void DrawImage1Impl(Ark_CanvasRenderer peer,
                    const Ark_Union_ImageBitmap_PixelMap* image,
                    const Ark_Number* dx,
                    const Ark_Number* dy,
                    const Ark_Number* dw,
                    const Ark_Number* dh)
{
}
void DrawImage2Impl(Ark_CanvasRenderer peer,
                    const Ark_Union_ImageBitmap_PixelMap* image,
                    const Ark_Number* sx,
                    const Ark_Number* sy,
                    const Ark_Number* sw,
                    const Ark_Number* sh,
                    const Ark_Number* dx,
                    const Ark_Number* dy,
                    const Ark_Number* dw,
                    const Ark_Number* dh)
{
}
void BeginPathImpl(Ark_CanvasRenderer peer)
{
}
void Clip0Impl(Ark_CanvasRenderer peer,
               const Opt_String* fillRule)
{
}
void Clip1Impl(Ark_CanvasRenderer peer,
               Ark_Path2D path,
               const Opt_String* fillRule)
{
}
void Fill0Impl(Ark_CanvasRenderer peer,
               const Opt_String* fillRule)
{
}
void Fill1Impl(Ark_CanvasRenderer peer,
               Ark_Path2D path,
               const Opt_String* fillRule)
{
}
void Stroke0Impl(Ark_CanvasRenderer peer)
{
}
void Stroke1Impl(Ark_CanvasRenderer peer,
                 Ark_Path2D path)
{
}
Ark_CanvasGradient CreateLinearGradientImpl(Ark_CanvasRenderer peer,
                                            const Ark_Number* x0,
                                            const Ark_Number* y0,
                                            const Ark_Number* x1,
                                            const Ark_Number* y1)
{
    return {};
}
Opt_CanvasPattern CreatePatternImpl(Ark_CanvasRenderer peer,
                                    Ark_ImageBitmap image,
                                    const Opt_String* repetition)
{
    return {};
}
Ark_CanvasGradient CreateRadialGradientImpl(Ark_CanvasRenderer peer,
                                            const Ark_Number* x0,
                                            const Ark_Number* y0,
                                            const Ark_Number* r0,
                                            const Ark_Number* x1,
                                            const Ark_Number* y1,
                                            const Ark_Number* r1)
{
    return {};
}
Ark_CanvasGradient CreateConicGradientImpl(Ark_CanvasRenderer peer,
                                           const Ark_Number* startAngle,
                                           const Ark_Number* x,
                                           const Ark_Number* y)
{
    return {};
}
Ark_ImageData CreateImageData0Impl(Ark_CanvasRenderer peer,
                                   const Ark_Number* sw,
                                   const Ark_Number* sh)
{
    return {};
}
Ark_ImageData CreateImageData1Impl(Ark_CanvasRenderer peer,
                                   Ark_ImageData imagedata)
{
    return {};
}
Ark_ImageData GetImageDataImpl(Ark_CanvasRenderer peer,
                               const Ark_Number* sx,
                               const Ark_Number* sy,
                               const Ark_Number* sw,
                               const Ark_Number* sh)
{
    return {};
}
Ark_PixelMap GetPixelMapImpl(Ark_CanvasRenderer peer,
                             const Ark_Number* sx,
                             const Ark_Number* sy,
                             const Ark_Number* sw,
                             const Ark_Number* sh)
{
    return {};
}
void PutImageData0Impl(Ark_CanvasRenderer peer,
                       Ark_ImageData imagedata,
                       const Ark_Union_Number_String* dx,
                       const Ark_Union_Number_String* dy)
{
}
void PutImageData1Impl(Ark_CanvasRenderer peer,
                       Ark_ImageData imagedata,
                       const Ark_Union_Number_String* dx,
                       const Ark_Union_Number_String* dy,
                       const Ark_Union_Number_String* dirtyX,
                       const Ark_Union_Number_String* dirtyY,
                       const Ark_Union_Number_String* dirtyWidth,
                       const Ark_Union_Number_String* dirtyHeight)
{
}
Array_Number GetLineDashImpl(Ark_CanvasRenderer peer)
{
    return {};
}
void SetLineDashImpl(Ark_CanvasRenderer peer,
                     const Array_Number* segments)
{
}
void ClearRectImpl(Ark_CanvasRenderer peer,
                   const Ark_Number* x,
                   const Ark_Number* y,
                   const Ark_Number* w,
                   const Ark_Number* h)
{
}
void FillRectImpl(Ark_CanvasRenderer peer,
                  const Ark_Number* x,
                  const Ark_Number* y,
                  const Ark_Number* w,
                  const Ark_Number* h)
{
}
void StrokeRectImpl(Ark_CanvasRenderer peer,
                    const Ark_Number* x,
                    const Ark_Number* y,
                    const Ark_Number* w,
                    const Ark_Number* h)
{
}
void RestoreImpl(Ark_CanvasRenderer peer)
{
}
void SaveImpl(Ark_CanvasRenderer peer)
{
}
void FillTextImpl(Ark_CanvasRenderer peer,
                  const Ark_String* text,
                  const Ark_Number* x,
                  const Ark_Number* y,
                  const Opt_Number* maxWidth)
{
}
Ark_TextMetrics MeasureTextImpl(Ark_CanvasRenderer peer,
                                const Ark_String* text)
{
    return {};
}
void StrokeTextImpl(Ark_CanvasRenderer peer,
                    const Ark_String* text,
                    const Ark_Number* x,
                    const Ark_Number* y,
                    const Opt_Number* maxWidth)
{
}
Ark_Matrix2D GetTransformImpl(Ark_CanvasRenderer peer)
{
    return {};
}
void ResetTransformImpl(Ark_CanvasRenderer peer)
{
}
void RotateImpl(Ark_CanvasRenderer peer,
                const Ark_Number* angle)
{
}
void ScaleImpl(Ark_CanvasRenderer peer,
               const Ark_Number* x,
               const Ark_Number* y)
{
}
void SetTransform0Impl(Ark_CanvasRenderer peer,
                       const Ark_Number* a,
                       const Ark_Number* b,
                       const Ark_Number* c,
                       const Ark_Number* d,
                       const Ark_Number* e,
                       const Ark_Number* f)
{
}
void SetTransform1Impl(Ark_CanvasRenderer peer,
                       const Opt_Matrix2D* transform)
{
}
void TransformImpl(Ark_CanvasRenderer peer,
                   const Ark_Number* a,
                   const Ark_Number* b,
                   const Ark_Number* c,
                   const Ark_Number* d,
                   const Ark_Number* e,
                   const Ark_Number* f)
{
}
void TranslateImpl(Ark_CanvasRenderer peer,
                   const Ark_Number* x,
                   const Ark_Number* y)
{
}
void SetPixelMapImpl(Ark_CanvasRenderer peer,
                     const Opt_PixelMap* value)
{
}
void TransferFromImageBitmapImpl(Ark_CanvasRenderer peer,
                                 Ark_ImageBitmap bitmap)
{
}
void SaveLayerImpl(Ark_CanvasRenderer peer)
{
}
void RestoreLayerImpl(Ark_CanvasRenderer peer)
{
}
void ResetImpl(Ark_CanvasRenderer peer)
{
}
void SetLetterSpacingImpl(Ark_CanvasRenderer peer,
                          const Ark_Union_LengthMetrics_String* letterSpacing)
{
}
Ark_Number GetGlobalAlphaImpl(Ark_CanvasRenderer peer)
{
    return {};
}
void SetGlobalAlphaImpl(Ark_CanvasRenderer peer,
                        const Ark_Number* globalAlpha)
{
}
Ark_String GetGlobalCompositeOperationImpl(Ark_CanvasRenderer peer)
{
    return {};
}
void SetGlobalCompositeOperationImpl(Ark_CanvasRenderer peer,
                                     const Ark_String* globalCompositeOperation)
{
}
void SetFillStyleImpl(Ark_CanvasRenderer peer,
                      const Ark_Union_String_Number_CanvasGradient_CanvasPattern* fillStyle)
{
}
void SetStrokeStyleImpl(Ark_CanvasRenderer peer,
                        const Ark_Union_String_Number_CanvasGradient_CanvasPattern* strokeStyle)
{
}
Ark_String GetFilterImpl(Ark_CanvasRenderer peer)
{
    return {};
}
void SetFilterImpl(Ark_CanvasRenderer peer,
                   const Ark_String* filter)
{
}
Ark_Boolean GetImageSmoothingEnabledImpl(Ark_CanvasRenderer peer)
{
    return {};
}
void SetImageSmoothingEnabledImpl(Ark_CanvasRenderer peer,
                                  Ark_Boolean imageSmoothingEnabled)
{
}
Ark_String GetImageSmoothingQualityImpl(Ark_CanvasRenderer peer)
{
    return {};
}
void SetImageSmoothingQualityImpl(Ark_CanvasRenderer peer,
                                  const Ark_String* imageSmoothingQuality)
{
}
Ark_String GetLineCapImpl(Ark_CanvasRenderer peer)
{
    return {};
}
void SetLineCapImpl(Ark_CanvasRenderer peer,
                    const Ark_String* lineCap)
{
}
Ark_Number GetLineDashOffsetImpl(Ark_CanvasRenderer peer)
{
    return {};
}
void SetLineDashOffsetImpl(Ark_CanvasRenderer peer,
                           const Ark_Number* lineDashOffset)
{
}
Ark_String GetLineJoinImpl(Ark_CanvasRenderer peer)
{
    return {};
}
void SetLineJoinImpl(Ark_CanvasRenderer peer,
                     const Ark_String* lineJoin)
{
}
Ark_Number GetLineWidthImpl(Ark_CanvasRenderer peer)
{
    return {};
}
void SetLineWidthImpl(Ark_CanvasRenderer peer,
                      const Ark_Number* lineWidth)
{
}
Ark_Number GetMiterLimitImpl(Ark_CanvasRenderer peer)
{
    return {};
}
void SetMiterLimitImpl(Ark_CanvasRenderer peer,
                       const Ark_Number* miterLimit)
{
}
Ark_Number GetShadowBlurImpl(Ark_CanvasRenderer peer)
{
    return {};
}
void SetShadowBlurImpl(Ark_CanvasRenderer peer,
                       const Ark_Number* shadowBlur)
{
}
Ark_String GetShadowColorImpl(Ark_CanvasRenderer peer)
{
    return {};
}
void SetShadowColorImpl(Ark_CanvasRenderer peer,
                        const Ark_String* shadowColor)
{
}
Ark_Number GetShadowOffsetXImpl(Ark_CanvasRenderer peer)
{
    return {};
}
void SetShadowOffsetXImpl(Ark_CanvasRenderer peer,
                          const Ark_Number* shadowOffsetX)
{
}
Ark_Number GetShadowOffsetYImpl(Ark_CanvasRenderer peer)
{
    return {};
}
void SetShadowOffsetYImpl(Ark_CanvasRenderer peer,
                          const Ark_Number* shadowOffsetY)
{
}
Ark_String GetDirectionImpl(Ark_CanvasRenderer peer)
{
    return {};
}
void SetDirectionImpl(Ark_CanvasRenderer peer,
                      const Ark_String* direction)
{
}
Ark_String GetFontImpl(Ark_CanvasRenderer peer)
{
    return {};
}
void SetFontImpl(Ark_CanvasRenderer peer,
                 const Ark_String* font)
{
}
Ark_String GetTextAlignImpl(Ark_CanvasRenderer peer)
{
    return {};
}
void SetTextAlignImpl(Ark_CanvasRenderer peer,
                      const Ark_String* textAlign)
{
}
Ark_String GetTextBaselineImpl(Ark_CanvasRenderer peer)
{
    return {};
}
void SetTextBaselineImpl(Ark_CanvasRenderer peer,
                         const Ark_String* textBaseline)
{
}
} // CanvasRendererAccessor
const GENERATED_ArkUICanvasRendererAccessor* GetCanvasRendererAccessor()
{
    static const GENERATED_ArkUICanvasRendererAccessor CanvasRendererAccessorImpl {
        CanvasRendererAccessor::DestroyPeerImpl,
        CanvasRendererAccessor::CtorImpl,
        CanvasRendererAccessor::GetFinalizerImpl,
        CanvasRendererAccessor::DrawImage0Impl,
        CanvasRendererAccessor::DrawImage1Impl,
        CanvasRendererAccessor::DrawImage2Impl,
        CanvasRendererAccessor::BeginPathImpl,
        CanvasRendererAccessor::Clip0Impl,
        CanvasRendererAccessor::Clip1Impl,
        CanvasRendererAccessor::Fill0Impl,
        CanvasRendererAccessor::Fill1Impl,
        CanvasRendererAccessor::Stroke0Impl,
        CanvasRendererAccessor::Stroke1Impl,
        CanvasRendererAccessor::CreateLinearGradientImpl,
        CanvasRendererAccessor::CreatePatternImpl,
        CanvasRendererAccessor::CreateRadialGradientImpl,
        CanvasRendererAccessor::CreateConicGradientImpl,
        CanvasRendererAccessor::CreateImageData0Impl,
        CanvasRendererAccessor::CreateImageData1Impl,
        CanvasRendererAccessor::GetImageDataImpl,
        CanvasRendererAccessor::GetPixelMapImpl,
        CanvasRendererAccessor::PutImageData0Impl,
        CanvasRendererAccessor::PutImageData1Impl,
        CanvasRendererAccessor::GetLineDashImpl,
        CanvasRendererAccessor::SetLineDashImpl,
        CanvasRendererAccessor::ClearRectImpl,
        CanvasRendererAccessor::FillRectImpl,
        CanvasRendererAccessor::StrokeRectImpl,
        CanvasRendererAccessor::RestoreImpl,
        CanvasRendererAccessor::SaveImpl,
        CanvasRendererAccessor::FillTextImpl,
        CanvasRendererAccessor::MeasureTextImpl,
        CanvasRendererAccessor::StrokeTextImpl,
        CanvasRendererAccessor::GetTransformImpl,
        CanvasRendererAccessor::ResetTransformImpl,
        CanvasRendererAccessor::RotateImpl,
        CanvasRendererAccessor::ScaleImpl,
        CanvasRendererAccessor::SetTransform0Impl,
        CanvasRendererAccessor::SetTransform1Impl,
        CanvasRendererAccessor::TransformImpl,
        CanvasRendererAccessor::TranslateImpl,
        CanvasRendererAccessor::SetPixelMapImpl,
        CanvasRendererAccessor::TransferFromImageBitmapImpl,
        CanvasRendererAccessor::SaveLayerImpl,
        CanvasRendererAccessor::RestoreLayerImpl,
        CanvasRendererAccessor::ResetImpl,
        CanvasRendererAccessor::SetLetterSpacingImpl,
        CanvasRendererAccessor::GetGlobalAlphaImpl,
        CanvasRendererAccessor::SetGlobalAlphaImpl,
        CanvasRendererAccessor::GetGlobalCompositeOperationImpl,
        CanvasRendererAccessor::SetGlobalCompositeOperationImpl,
        CanvasRendererAccessor::SetFillStyleImpl,
        CanvasRendererAccessor::SetStrokeStyleImpl,
        CanvasRendererAccessor::GetFilterImpl,
        CanvasRendererAccessor::SetFilterImpl,
        CanvasRendererAccessor::GetImageSmoothingEnabledImpl,
        CanvasRendererAccessor::SetImageSmoothingEnabledImpl,
        CanvasRendererAccessor::GetImageSmoothingQualityImpl,
        CanvasRendererAccessor::SetImageSmoothingQualityImpl,
        CanvasRendererAccessor::GetLineCapImpl,
        CanvasRendererAccessor::SetLineCapImpl,
        CanvasRendererAccessor::GetLineDashOffsetImpl,
        CanvasRendererAccessor::SetLineDashOffsetImpl,
        CanvasRendererAccessor::GetLineJoinImpl,
        CanvasRendererAccessor::SetLineJoinImpl,
        CanvasRendererAccessor::GetLineWidthImpl,
        CanvasRendererAccessor::SetLineWidthImpl,
        CanvasRendererAccessor::GetMiterLimitImpl,
        CanvasRendererAccessor::SetMiterLimitImpl,
        CanvasRendererAccessor::GetShadowBlurImpl,
        CanvasRendererAccessor::SetShadowBlurImpl,
        CanvasRendererAccessor::GetShadowColorImpl,
        CanvasRendererAccessor::SetShadowColorImpl,
        CanvasRendererAccessor::GetShadowOffsetXImpl,
        CanvasRendererAccessor::SetShadowOffsetXImpl,
        CanvasRendererAccessor::GetShadowOffsetYImpl,
        CanvasRendererAccessor::SetShadowOffsetYImpl,
        CanvasRendererAccessor::GetDirectionImpl,
        CanvasRendererAccessor::SetDirectionImpl,
        CanvasRendererAccessor::GetFontImpl,
        CanvasRendererAccessor::SetFontImpl,
        CanvasRendererAccessor::GetTextAlignImpl,
        CanvasRendererAccessor::SetTextAlignImpl,
        CanvasRendererAccessor::GetTextBaselineImpl,
        CanvasRendererAccessor::SetTextBaselineImpl,
    };
    return &CanvasRendererAccessorImpl;
}

}
