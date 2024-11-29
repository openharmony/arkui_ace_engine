/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "core/interfaces/arkoala/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace CanvasRendererAccessor {
void DestroyPeerImpl(CanvasRendererPeer* peer)
{
}
CanvasRendererPeer* CtorImpl()
{
    return new CanvasRendererPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void DrawImage0Impl(CanvasRendererPeer* peer,
                    const Ark_Union_ImageBitmap_PixelMap* image,
                    const Ark_Number* dx,
                    const Ark_Number* dy)
{
}
void DrawImage1Impl(CanvasRendererPeer* peer,
                    const Ark_Union_ImageBitmap_PixelMap* image,
                    const Ark_Number* dx,
                    const Ark_Number* dy,
                    const Ark_Number* dw,
                    const Ark_Number* dh)
{
}
void DrawImage2Impl(CanvasRendererPeer* peer,
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
void BeginPathImpl(CanvasRendererPeer* peer)
{
}
void Clip0Impl(CanvasRendererPeer* peer,
               const Opt_String* fillRule)
{
}
void Clip1Impl(CanvasRendererPeer* peer,
               const Ark_Path2D* path,
               const Opt_String* fillRule)
{
}
void Fill0Impl(CanvasRendererPeer* peer,
               const Opt_String* fillRule)
{
}
void Fill1Impl(CanvasRendererPeer* peer,
               const Ark_Path2D* path,
               const Opt_String* fillRule)
{
}
void Stroke0Impl(CanvasRendererPeer* peer)
{
}
void Stroke1Impl(CanvasRendererPeer* peer,
                 const Ark_Path2D* path)
{
}
Ark_NativePointer CreateLinearGradientImpl(CanvasRendererPeer* peer,
                                           const Ark_Number* x0,
                                           const Ark_Number* y0,
                                           const Ark_Number* x1,
                                           const Ark_Number* y1)
{
    return 0;
}
Ark_NativePointer CreatePatternImpl(CanvasRendererPeer* peer,
                                    const Ark_ImageBitmap* image,
                                    const Ark_Union_String_Null* repetition)
{
    return 0;
}
Ark_NativePointer CreateRadialGradientImpl(CanvasRendererPeer* peer,
                                           const Ark_Number* x0,
                                           const Ark_Number* y0,
                                           const Ark_Number* r0,
                                           const Ark_Number* x1,
                                           const Ark_Number* y1,
                                           const Ark_Number* r1)
{
    return 0;
}
Ark_NativePointer CreateConicGradientImpl(CanvasRendererPeer* peer,
                                          const Ark_Number* startAngle,
                                          const Ark_Number* x,
                                          const Ark_Number* y)
{
    return 0;
}
Ark_NativePointer CreateImageData0Impl(CanvasRendererPeer* peer,
                                       const Ark_Number* sw,
                                       const Ark_Number* sh)
{
    return 0;
}
Ark_NativePointer CreateImageData1Impl(CanvasRendererPeer* peer,
                                       const Ark_ImageData* imagedata)
{
    return 0;
}
Ark_NativePointer GetImageDataImpl(CanvasRendererPeer* peer,
                                   const Ark_Number* sx,
                                   const Ark_Number* sy,
                                   const Ark_Number* sw,
                                   const Ark_Number* sh)
{
    return 0;
}
Ark_NativePointer GetPixelMapImpl(CanvasRendererPeer* peer,
                                  const Ark_Number* sx,
                                  const Ark_Number* sy,
                                  const Ark_Number* sw,
                                  const Ark_Number* sh)
{
    return 0;
}
void PutImageData0Impl(CanvasRendererPeer* peer,
                       const Ark_ImageData* imagedata,
                       const Ark_Union_Number_String* dx,
                       const Ark_Union_Number_String* dy)
{
}
void PutImageData1Impl(CanvasRendererPeer* peer,
                       const Ark_ImageData* imagedata,
                       const Ark_Union_Number_String* dx,
                       const Ark_Union_Number_String* dy,
                       const Ark_Union_Number_String* dirtyX,
                       const Ark_Union_Number_String* dirtyY,
                       const Ark_Union_Number_String* dirtyWidth,
                       const Ark_Union_Number_String* dirtyHeight)
{
}
void GetLineDashImpl(CanvasRendererPeer* peer)
{
}
void SetLineDashImpl(CanvasRendererPeer* peer,
                     const Array_Number* segments)
{
}
void ClearRectImpl(CanvasRendererPeer* peer,
                   const Ark_Number* x,
                   const Ark_Number* y,
                   const Ark_Number* w,
                   const Ark_Number* h)
{
}
void FillRectImpl(CanvasRendererPeer* peer,
                  const Ark_Number* x,
                  const Ark_Number* y,
                  const Ark_Number* w,
                  const Ark_Number* h)
{
}
void StrokeRectImpl(CanvasRendererPeer* peer,
                    const Ark_Number* x,
                    const Ark_Number* y,
                    const Ark_Number* w,
                    const Ark_Number* h)
{
}
void RestoreImpl(CanvasRendererPeer* peer)
{
}
void SaveImpl(CanvasRendererPeer* peer)
{
}
void FillTextImpl(CanvasRendererPeer* peer,
                  const Ark_String* text,
                  const Ark_Number* x,
                  const Ark_Number* y,
                  const Opt_Number* maxWidth)
{
}
Ark_NativePointer MeasureTextImpl(CanvasRendererPeer* peer,
                                  const Ark_String* text)
{
    return 0;
}
void StrokeTextImpl(CanvasRendererPeer* peer,
                    const Ark_String* text,
                    const Ark_Number* x,
                    const Ark_Number* y,
                    const Opt_Number* maxWidth)
{
}
Ark_NativePointer GetTransformImpl(CanvasRendererPeer* peer)
{
    return 0;
}
void ResetTransformImpl(CanvasRendererPeer* peer)
{
}
void RotateImpl(CanvasRendererPeer* peer,
                const Ark_Number* angle)
{
}
void ScaleImpl(CanvasRendererPeer* peer,
               const Ark_Number* x,
               const Ark_Number* y)
{
}
void SetTransform0Impl(CanvasRendererPeer* peer,
                       const Ark_Number* a,
                       const Ark_Number* b,
                       const Ark_Number* c,
                       const Ark_Number* d,
                       const Ark_Number* e,
                       const Ark_Number* f)
{
}
void SetTransform1Impl(CanvasRendererPeer* peer,
                       const Opt_Matrix2D* transform)
{
}
void TransformImpl(CanvasRendererPeer* peer,
                   const Ark_Number* a,
                   const Ark_Number* b,
                   const Ark_Number* c,
                   const Ark_Number* d,
                   const Ark_Number* e,
                   const Ark_Number* f)
{
}
void TranslateImpl(CanvasRendererPeer* peer,
                   const Ark_Number* x,
                   const Ark_Number* y)
{
}
void SetPixelMapImpl(CanvasRendererPeer* peer,
                     const Opt_PixelMap* value)
{
}
void TransferFromImageBitmapImpl(CanvasRendererPeer* peer,
                                 const Ark_ImageBitmap* bitmap)
{
}
void SaveLayerImpl(CanvasRendererPeer* peer)
{
}
void RestoreLayerImpl(CanvasRendererPeer* peer)
{
}
void ResetImpl(CanvasRendererPeer* peer)
{
}
Ark_Int32 GetGlobalAlphaImpl(CanvasRendererPeer* peer)
{
    return 0;
}
void SetGlobalAlphaImpl(CanvasRendererPeer* peer,
                        const Ark_Number* globalAlpha)
{
}
void GetGlobalCompositeOperationImpl(CanvasRendererPeer* peer)
{
}
void SetGlobalCompositeOperationImpl(CanvasRendererPeer* peer,
                                     const Ark_String* globalCompositeOperation)
{
}
void SetFillStyleImpl(CanvasRendererPeer* peer,
                      const Ark_Union_String_Number_CanvasGradient_CanvasPattern* fillStyle)
{
}
void SetStrokeStyleImpl(CanvasRendererPeer* peer,
                        const Ark_Union_String_Number_CanvasGradient_CanvasPattern* strokeStyle)
{
}
void GetFilterImpl(CanvasRendererPeer* peer)
{
}
void SetFilterImpl(CanvasRendererPeer* peer,
                   const Ark_String* filter)
{
}
Ark_Boolean GetImageSmoothingEnabledImpl(CanvasRendererPeer* peer)
{
    return 0;
}
void SetImageSmoothingEnabledImpl(CanvasRendererPeer* peer,
                                  Ark_Boolean imageSmoothingEnabled)
{
}
Ark_NativePointer GetImageSmoothingQualityImpl(CanvasRendererPeer* peer)
{
    return 0;
}
void SetImageSmoothingQualityImpl(CanvasRendererPeer* peer,
                                  const Ark_String* imageSmoothingQuality)
{
}
Ark_NativePointer GetLineCapImpl(CanvasRendererPeer* peer)
{
    return 0;
}
void SetLineCapImpl(CanvasRendererPeer* peer,
                    const Ark_String* lineCap)
{
}
Ark_Int32 GetLineDashOffsetImpl(CanvasRendererPeer* peer)
{
    return 0;
}
void SetLineDashOffsetImpl(CanvasRendererPeer* peer,
                           const Ark_Number* lineDashOffset)
{
}
Ark_NativePointer GetLineJoinImpl(CanvasRendererPeer* peer)
{
    return 0;
}
void SetLineJoinImpl(CanvasRendererPeer* peer,
                     const Ark_String* lineJoin)
{
}
Ark_Int32 GetLineWidthImpl(CanvasRendererPeer* peer)
{
    return 0;
}
void SetLineWidthImpl(CanvasRendererPeer* peer,
                      const Ark_Number* lineWidth)
{
}
Ark_Int32 GetMiterLimitImpl(CanvasRendererPeer* peer)
{
    return 0;
}
void SetMiterLimitImpl(CanvasRendererPeer* peer,
                       const Ark_Number* miterLimit)
{
}
Ark_Int32 GetShadowBlurImpl(CanvasRendererPeer* peer)
{
    return 0;
}
void SetShadowBlurImpl(CanvasRendererPeer* peer,
                       const Ark_Number* shadowBlur)
{
}
void GetShadowColorImpl(CanvasRendererPeer* peer)
{
}
void SetShadowColorImpl(CanvasRendererPeer* peer,
                        const Ark_String* shadowColor)
{
}
Ark_Int32 GetShadowOffsetXImpl(CanvasRendererPeer* peer)
{
    return 0;
}
void SetShadowOffsetXImpl(CanvasRendererPeer* peer,
                          const Ark_Number* shadowOffsetX)
{
}
Ark_Int32 GetShadowOffsetYImpl(CanvasRendererPeer* peer)
{
    return 0;
}
void SetShadowOffsetYImpl(CanvasRendererPeer* peer,
                          const Ark_Number* shadowOffsetY)
{
}
Ark_NativePointer GetDirectionImpl(CanvasRendererPeer* peer)
{
    return 0;
}
void SetDirectionImpl(CanvasRendererPeer* peer,
                      const Ark_String* direction)
{
}
void GetFontImpl(CanvasRendererPeer* peer)
{
}
void SetFontImpl(CanvasRendererPeer* peer,
                 const Ark_String* font)
{
}
Ark_NativePointer GetTextAlignImpl(CanvasRendererPeer* peer)
{
    return 0;
}
void SetTextAlignImpl(CanvasRendererPeer* peer,
                      const Ark_String* textAlign)
{
}
Ark_NativePointer GetTextBaselineImpl(CanvasRendererPeer* peer)
{
    return 0;
}
void SetTextBaselineImpl(CanvasRendererPeer* peer,
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
