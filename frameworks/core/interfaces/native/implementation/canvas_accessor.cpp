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
namespace Drawing_CanvasAccessor {
void DestroyPeerImpl(Ark_drawing_Canvas peer)
{
}
Ark_drawing_Canvas CtorImpl(Ark_image_PixelMap pixelmap)
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void DrawRect0Impl(Ark_drawing_Canvas peer,
                   const Ark_common2D_Rect* rect)
{
}
void DrawRect1Impl(Ark_drawing_Canvas peer,
                   const Ark_Number* left,
                   const Ark_Number* top,
                   const Ark_Number* right,
                   const Ark_Number* bottom)
{
}
void DrawRoundRectImpl(Ark_drawing_Canvas peer,
                       Ark_drawing_RoundRect roundRect)
{
}
void DrawNestedRoundRectImpl(Ark_drawing_Canvas peer,
                             Ark_drawing_RoundRect outer,
                             Ark_drawing_RoundRect inner)
{
}
void DrawBackgroundImpl(Ark_drawing_Canvas peer,
                        Ark_drawing_Brush brush)
{
}
void DrawShadow0Impl(Ark_drawing_Canvas peer,
                     Ark_drawing_Path path,
                     const Ark_common2D_Point3d* planeParams,
                     const Ark_common2D_Point3d* devLightPos,
                     const Ark_Number* lightRadius,
                     const Ark_common2D_Color* ambientColor,
                     const Ark_common2D_Color* spotColor,
                     Ark_drawing_ShadowFlag flag)
{
}
void DrawShadow1Impl(Ark_drawing_Canvas peer,
                     Ark_drawing_Path path,
                     const Ark_common2D_Point3d* planeParams,
                     const Ark_common2D_Point3d* devLightPos,
                     const Ark_Number* lightRadius,
                     const Ark_Number* ambientColor,
                     const Ark_Number* spotColor,
                     Ark_drawing_ShadowFlag flag)
{
}
void DrawCircleImpl(Ark_drawing_Canvas peer,
                    const Ark_Number* x,
                    const Ark_Number* y,
                    const Ark_Number* radius)
{
}
void DrawImageImpl(Ark_drawing_Canvas peer,
                   Ark_image_PixelMap pixelmap,
                   const Ark_Number* left,
                   const Ark_Number* top,
                   Ark_drawing_SamplingOptions samplingOptions)
{
}
void DrawImageRectImpl(Ark_drawing_Canvas peer,
                       Ark_image_PixelMap pixelmap,
                       const Ark_common2D_Rect* dstRect,
                       Ark_drawing_SamplingOptions samplingOptions)
{
}
void DrawImageRectWithSrcImpl(Ark_drawing_Canvas peer,
                              Ark_image_PixelMap pixelmap,
                              const Ark_common2D_Rect* srcRect,
                              const Ark_common2D_Rect* dstRect,
                              Ark_drawing_SamplingOptions samplingOptions,
                              Ark_drawing_SrcRectConstraint constraint)
{
}
void DrawColor0Impl(Ark_drawing_Canvas peer,
                    const Ark_common2D_Color* color,
                    Ark_drawing_BlendMode blendMode)
{
}
void DrawColor1Impl(Ark_drawing_Canvas peer,
                    const Ark_Number* color,
                    Ark_drawing_BlendMode blendMode)
{
}
void DrawColor2Impl(Ark_drawing_Canvas peer,
                    const Ark_Number* alpha,
                    const Ark_Number* red,
                    const Ark_Number* green,
                    const Ark_Number* blue,
                    Ark_drawing_BlendMode blendMode)
{
}
void DrawOvalImpl(Ark_drawing_Canvas peer,
                  const Ark_common2D_Rect* oval)
{
}
void DrawArcImpl(Ark_drawing_Canvas peer,
                 const Ark_common2D_Rect* arc,
                 const Ark_Number* startAngle,
                 const Ark_Number* sweepAngle)
{
}
void DrawPointImpl(Ark_drawing_Canvas peer,
                   const Ark_Number* x,
                   const Ark_Number* y)
{
}
void DrawPointsImpl(Ark_drawing_Canvas peer,
                    const Array_common2D_Point* points,
                    Ark_drawing_PointMode mode)
{
}
void DrawPathImpl(Ark_drawing_Canvas peer,
                  Ark_drawing_Path path)
{
}
void DrawLineImpl(Ark_drawing_Canvas peer,
                  const Ark_Number* x0,
                  const Ark_Number* y0,
                  const Ark_Number* x1,
                  const Ark_Number* y1)
{
}
void DrawSingleCharacterImpl(Ark_drawing_Canvas peer,
                             const Ark_String* text,
                             Ark_drawing_Font font,
                             const Ark_Number* x,
                             const Ark_Number* y)
{
}
void DrawTextBlobImpl(Ark_drawing_Canvas peer,
                      Ark_drawing_TextBlob blob,
                      const Ark_Number* x,
                      const Ark_Number* y)
{
}
void DrawPixelMapMeshImpl(Ark_drawing_Canvas peer,
                          Ark_image_PixelMap pixelmap,
                          const Ark_Number* meshWidth,
                          const Ark_Number* meshHeight,
                          const Array_Number* vertices,
                          const Ark_Number* vertOffset,
                          const Array_Number* colors,
                          const Ark_Number* colorOffset)
{
}
void DrawRegionImpl(Ark_drawing_Canvas peer,
                    Ark_drawing_Region region)
{
}
void AttachPenImpl(Ark_drawing_Canvas peer,
                   Ark_drawing_Pen pen)
{
}
void AttachBrushImpl(Ark_drawing_Canvas peer,
                     Ark_drawing_Brush brush)
{
}
void DetachPenImpl(Ark_drawing_Canvas peer)
{
}
void DetachBrushImpl(Ark_drawing_Canvas peer)
{
}
Ark_Number SaveImpl(Ark_drawing_Canvas peer)
{
    return {};
}
Ark_Number SaveLayerImpl(Ark_drawing_Canvas peer,
                         const Opt_common2D_Rect* rect,
                         const Opt_drawing_Brush* brush)
{
    return {};
}
void Clear0Impl(Ark_drawing_Canvas peer,
                const Ark_common2D_Color* color)
{
}
void Clear1Impl(Ark_drawing_Canvas peer,
                const Ark_Number* color)
{
}
void RestoreImpl(Ark_drawing_Canvas peer)
{
}
void RestoreToCountImpl(Ark_drawing_Canvas peer,
                        const Ark_Number* count)
{
}
Ark_Number GetSaveCountImpl(Ark_drawing_Canvas peer)
{
    return {};
}
Ark_Number GetWidthImpl(Ark_drawing_Canvas peer)
{
    return {};
}
Ark_Number GetHeightImpl(Ark_drawing_Canvas peer)
{
    return {};
}
Ark_common2D_Rect GetLocalClipBoundsImpl(Ark_drawing_Canvas peer)
{
    return {};
}
Ark_drawing_Matrix GetTotalMatrixImpl(Ark_drawing_Canvas peer)
{
    return {};
}
void ScaleImpl(Ark_drawing_Canvas peer,
               const Ark_Number* sx,
               const Ark_Number* sy)
{
}
void SkewImpl(Ark_drawing_Canvas peer,
              const Ark_Number* sx,
              const Ark_Number* sy)
{
}
void RotateImpl(Ark_drawing_Canvas peer,
                const Ark_Number* degrees,
                const Ark_Number* sx,
                const Ark_Number* sy)
{
}
void TranslateImpl(Ark_drawing_Canvas peer,
                   const Ark_Number* dx,
                   const Ark_Number* dy)
{
}
void ClipPathImpl(Ark_drawing_Canvas peer,
                  Ark_drawing_Path path,
                  Ark_drawing_ClipOp clipOp,
                  Ark_Boolean doAntiAlias)
{
}
void ClipRectImpl(Ark_drawing_Canvas peer,
                  const Ark_common2D_Rect* rect,
                  Ark_drawing_ClipOp clipOp,
                  Ark_Boolean doAntiAlias)
{
}
void ConcatMatrixImpl(Ark_drawing_Canvas peer,
                      Ark_drawing_Matrix matrix)
{
}
void ClipRegionImpl(Ark_drawing_Canvas peer,
                    Ark_drawing_Region region,
                    Ark_drawing_ClipOp clipOp)
{
}
void ClipRoundRectImpl(Ark_drawing_Canvas peer,
                       Ark_drawing_RoundRect roundRect,
                       Ark_drawing_ClipOp clipOp,
                       Ark_Boolean doAntiAlias)
{
}
Ark_Boolean IsClipEmptyImpl(Ark_drawing_Canvas peer)
{
    return {};
}
void SetMatrixImpl(Ark_drawing_Canvas peer,
                   Ark_drawing_Matrix matrix)
{
}
void ResetMatrixImpl(Ark_drawing_Canvas peer)
{
}
} // Drawing_CanvasAccessor
const GENERATED_ArkUIDrawing_CanvasAccessor* GetDrawing_CanvasAccessor()
{
    static const GENERATED_ArkUIDrawing_CanvasAccessor Drawing_CanvasAccessorImpl {
        Drawing_CanvasAccessor::DestroyPeerImpl,
        Drawing_CanvasAccessor::CtorImpl,
        Drawing_CanvasAccessor::GetFinalizerImpl,
        Drawing_CanvasAccessor::DrawRect0Impl,
        Drawing_CanvasAccessor::DrawRect1Impl,
        Drawing_CanvasAccessor::DrawRoundRectImpl,
        Drawing_CanvasAccessor::DrawNestedRoundRectImpl,
        Drawing_CanvasAccessor::DrawBackgroundImpl,
        Drawing_CanvasAccessor::DrawShadow0Impl,
        Drawing_CanvasAccessor::DrawShadow1Impl,
        Drawing_CanvasAccessor::DrawCircleImpl,
        Drawing_CanvasAccessor::DrawImageImpl,
        Drawing_CanvasAccessor::DrawImageRectImpl,
        Drawing_CanvasAccessor::DrawImageRectWithSrcImpl,
        Drawing_CanvasAccessor::DrawColor0Impl,
        Drawing_CanvasAccessor::DrawColor1Impl,
        Drawing_CanvasAccessor::DrawColor2Impl,
        Drawing_CanvasAccessor::DrawOvalImpl,
        Drawing_CanvasAccessor::DrawArcImpl,
        Drawing_CanvasAccessor::DrawPointImpl,
        Drawing_CanvasAccessor::DrawPointsImpl,
        Drawing_CanvasAccessor::DrawPathImpl,
        Drawing_CanvasAccessor::DrawLineImpl,
        Drawing_CanvasAccessor::DrawSingleCharacterImpl,
        Drawing_CanvasAccessor::DrawTextBlobImpl,
        Drawing_CanvasAccessor::DrawPixelMapMeshImpl,
        Drawing_CanvasAccessor::DrawRegionImpl,
        Drawing_CanvasAccessor::AttachPenImpl,
        Drawing_CanvasAccessor::AttachBrushImpl,
        Drawing_CanvasAccessor::DetachPenImpl,
        Drawing_CanvasAccessor::DetachBrushImpl,
        Drawing_CanvasAccessor::SaveImpl,
        Drawing_CanvasAccessor::SaveLayerImpl,
        Drawing_CanvasAccessor::Clear0Impl,
        Drawing_CanvasAccessor::Clear1Impl,
        Drawing_CanvasAccessor::RestoreImpl,
        Drawing_CanvasAccessor::RestoreToCountImpl,
        Drawing_CanvasAccessor::GetSaveCountImpl,
        Drawing_CanvasAccessor::GetWidthImpl,
        Drawing_CanvasAccessor::GetHeightImpl,
        Drawing_CanvasAccessor::GetLocalClipBoundsImpl,
        Drawing_CanvasAccessor::GetTotalMatrixImpl,
        Drawing_CanvasAccessor::ScaleImpl,
        Drawing_CanvasAccessor::SkewImpl,
        Drawing_CanvasAccessor::RotateImpl,
        Drawing_CanvasAccessor::TranslateImpl,
        Drawing_CanvasAccessor::ClipPathImpl,
        Drawing_CanvasAccessor::ClipRectImpl,
        Drawing_CanvasAccessor::ConcatMatrixImpl,
        Drawing_CanvasAccessor::ClipRegionImpl,
        Drawing_CanvasAccessor::ClipRoundRectImpl,
        Drawing_CanvasAccessor::IsClipEmptyImpl,
        Drawing_CanvasAccessor::SetMatrixImpl,
        Drawing_CanvasAccessor::ResetMatrixImpl,
    };
    return &Drawing_CanvasAccessorImpl;
}

}
