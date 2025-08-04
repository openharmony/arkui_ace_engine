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

#include "core/interfaces/native/utility/converter.h"

#include "arkoala_api_generated.h"
#include "drawing_canvas_peer_impl.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace drawing_CanvasAccessor {
void DestroyPeerImpl(Ark_drawing_Canvas peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_drawing_Canvas ConstructImpl(Ark_image_PixelMap pixelmap)
{
    CHECK_NULL_RETURN(pixelmap, nullptr);
    return PeerUtils::CreatePeer<drawing_CanvasPeer>(pixelmap->pixelMap);
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
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(left && top && right && bottom);
    float x = Converter::Convert<float>(*left);
    float y = Converter::Convert<float>(*top);
    float w = Converter::Convert<float>(*right) - x;
    float h = Converter::Convert<float>(*bottom) - y;
    Rect rect(x, y, w, h);
    peer->FillRect(rect);
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
} // drawing_CanvasAccessor
const GENERATED_ArkUIDrawing_CanvasAccessor* GetDrawing_CanvasAccessor()
{
    static const GENERATED_ArkUIDrawing_CanvasAccessor Drawing_CanvasAccessorImpl {
        drawing_CanvasAccessor::DestroyPeerImpl,
        drawing_CanvasAccessor::ConstructImpl,
        drawing_CanvasAccessor::GetFinalizerImpl,
        drawing_CanvasAccessor::DrawRect0Impl,
        drawing_CanvasAccessor::DrawRect1Impl,
        drawing_CanvasAccessor::DrawRoundRectImpl,
        drawing_CanvasAccessor::DrawNestedRoundRectImpl,
        drawing_CanvasAccessor::DrawBackgroundImpl,
        drawing_CanvasAccessor::DrawShadow0Impl,
        drawing_CanvasAccessor::DrawShadow1Impl,
        drawing_CanvasAccessor::DrawCircleImpl,
        drawing_CanvasAccessor::DrawImageImpl,
        drawing_CanvasAccessor::DrawImageRectImpl,
        drawing_CanvasAccessor::DrawImageRectWithSrcImpl,
        drawing_CanvasAccessor::DrawColor0Impl,
        drawing_CanvasAccessor::DrawColor1Impl,
        drawing_CanvasAccessor::DrawColor2Impl,
        drawing_CanvasAccessor::DrawOvalImpl,
        drawing_CanvasAccessor::DrawArcImpl,
        drawing_CanvasAccessor::DrawPointImpl,
        drawing_CanvasAccessor::DrawPointsImpl,
        drawing_CanvasAccessor::DrawPathImpl,
        drawing_CanvasAccessor::DrawLineImpl,
        drawing_CanvasAccessor::DrawSingleCharacterImpl,
        drawing_CanvasAccessor::DrawTextBlobImpl,
        drawing_CanvasAccessor::DrawPixelMapMeshImpl,
        drawing_CanvasAccessor::DrawRegionImpl,
        drawing_CanvasAccessor::AttachPenImpl,
        drawing_CanvasAccessor::AttachBrushImpl,
        drawing_CanvasAccessor::DetachPenImpl,
        drawing_CanvasAccessor::DetachBrushImpl,
        drawing_CanvasAccessor::SaveImpl,
        drawing_CanvasAccessor::SaveLayerImpl,
        drawing_CanvasAccessor::Clear0Impl,
        drawing_CanvasAccessor::Clear1Impl,
        drawing_CanvasAccessor::RestoreImpl,
        drawing_CanvasAccessor::RestoreToCountImpl,
        drawing_CanvasAccessor::GetSaveCountImpl,
        drawing_CanvasAccessor::GetWidthImpl,
        drawing_CanvasAccessor::GetHeightImpl,
        drawing_CanvasAccessor::GetLocalClipBoundsImpl,
        drawing_CanvasAccessor::GetTotalMatrixImpl,
        drawing_CanvasAccessor::ScaleImpl,
        drawing_CanvasAccessor::SkewImpl,
        drawing_CanvasAccessor::RotateImpl,
        drawing_CanvasAccessor::TranslateImpl,
        drawing_CanvasAccessor::ClipPathImpl,
        drawing_CanvasAccessor::ClipRectImpl,
        drawing_CanvasAccessor::ConcatMatrixImpl,
        drawing_CanvasAccessor::ClipRegionImpl,
        drawing_CanvasAccessor::ClipRoundRectImpl,
        drawing_CanvasAccessor::IsClipEmptyImpl,
        drawing_CanvasAccessor::SetMatrixImpl,
        drawing_CanvasAccessor::ResetMatrixImpl,
    };
    return &Drawing_CanvasAccessorImpl;
}

}
