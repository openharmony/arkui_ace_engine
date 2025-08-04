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
namespace drawing_PathAccessor {
void DestroyPeerImpl(Ark_drawing_Path peer)
{
}
Ark_drawing_Path Construct0Impl()
{
    return {};
}
Ark_drawing_Path Construct1Impl(Ark_drawing_Path path)
{
    return {};
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void MoveToImpl(Ark_drawing_Path peer,
                const Ark_Number* x,
                const Ark_Number* y)
{
}
void LineToImpl(Ark_drawing_Path peer,
                const Ark_Number* x,
                const Ark_Number* y)
{
}
void ArcToImpl(Ark_drawing_Path peer,
               const Ark_Number* x1,
               const Ark_Number* y1,
               const Ark_Number* x2,
               const Ark_Number* y2,
               const Ark_Number* startDeg,
               const Ark_Number* sweepDeg)
{
}
void QuadToImpl(Ark_drawing_Path peer,
                const Ark_Number* ctrlX,
                const Ark_Number* ctrlY,
                const Ark_Number* endX,
                const Ark_Number* endY)
{
}
void ConicToImpl(Ark_drawing_Path peer,
                 const Ark_Number* ctrlX,
                 const Ark_Number* ctrlY,
                 const Ark_Number* endX,
                 const Ark_Number* endY,
                 const Ark_Number* weight)
{
}
void CubicToImpl(Ark_drawing_Path peer,
                 const Ark_Number* ctrlX1,
                 const Ark_Number* ctrlY1,
                 const Ark_Number* ctrlX2,
                 const Ark_Number* ctrlY2,
                 const Ark_Number* endX,
                 const Ark_Number* endY)
{
}
void RMoveToImpl(Ark_drawing_Path peer,
                 const Ark_Number* dx,
                 const Ark_Number* dy)
{
}
void RLineToImpl(Ark_drawing_Path peer,
                 const Ark_Number* dx,
                 const Ark_Number* dy)
{
}
void RQuadToImpl(Ark_drawing_Path peer,
                 const Ark_Number* dx1,
                 const Ark_Number* dy1,
                 const Ark_Number* dx2,
                 const Ark_Number* dy2)
{
}
void RConicToImpl(Ark_drawing_Path peer,
                  const Ark_Number* ctrlX,
                  const Ark_Number* ctrlY,
                  const Ark_Number* endX,
                  const Ark_Number* endY,
                  const Ark_Number* weight)
{
}
void RCubicToImpl(Ark_drawing_Path peer,
                  const Ark_Number* ctrlX1,
                  const Ark_Number* ctrlY1,
                  const Ark_Number* ctrlX2,
                  const Ark_Number* ctrlY2,
                  const Ark_Number* endX,
                  const Ark_Number* endY)
{
}
void AddPolygonImpl(Ark_drawing_Path peer,
                    const Array_common2D_Point* points,
                    Ark_Boolean close)
{
}
Ark_Boolean OpImpl(Ark_drawing_Path peer,
                   Ark_drawing_Path path,
                   Ark_drawing_PathOp pathOp)
{
    return {};
}
void AddArcImpl(Ark_drawing_Path peer,
                const Ark_common2D_Rect* rect,
                const Ark_Number* startAngle,
                const Ark_Number* sweepAngle)
{
}
void AddCircleImpl(Ark_drawing_Path peer,
                   const Ark_Number* x,
                   const Ark_Number* y,
                   const Ark_Number* radius,
                   Ark_drawing_PathDirection pathDirection)
{
}
void AddOvalImpl(Ark_drawing_Path peer,
                 const Ark_common2D_Rect* rect,
                 const Ark_Number* start,
                 Ark_drawing_PathDirection pathDirection)
{
}
void AddRectImpl(Ark_drawing_Path peer,
                 const Ark_common2D_Rect* rect,
                 Ark_drawing_PathDirection pathDirection)
{
}
void AddRoundRectImpl(Ark_drawing_Path peer,
                      Ark_drawing_RoundRect roundRect,
                      Ark_drawing_PathDirection pathDirection)
{
}
void AddPathImpl(Ark_drawing_Path peer,
                 Ark_drawing_Path path,
                 const Opt_drawing_Matrix* matrix)
{
}
void TransformImpl(Ark_drawing_Path peer,
                   Ark_drawing_Matrix matrix)
{
}
Ark_Boolean ContainsImpl(Ark_drawing_Path peer,
                         const Ark_Number* x,
                         const Ark_Number* y)
{
    return {};
}
void SetFillTypeImpl(Ark_drawing_Path peer,
                     Ark_drawing_PathFillType pathFillType)
{
}
Ark_common2D_Rect GetBoundsImpl(Ark_drawing_Path peer)
{
    return {};
}
void CloseImpl(Ark_drawing_Path peer)
{
}
Ark_drawing_Path OffsetImpl(Ark_drawing_Path peer,
                            const Ark_Number* dx,
                            const Ark_Number* dy)
{
    return {};
}
void ResetImpl(Ark_drawing_Path peer)
{
}
Ark_Number GetLengthImpl(Ark_drawing_Path peer,
                         Ark_Boolean forceClosed)
{
    return {};
}
Ark_Boolean GetPositionAndTangentImpl(Ark_drawing_Path peer,
                                      Ark_Boolean forceClosed,
                                      const Ark_Number* distance,
                                      const Ark_common2D_Point* position,
                                      const Ark_common2D_Point* tangent)
{
    return {};
}
Ark_Boolean IsClosedImpl(Ark_drawing_Path peer)
{
    return {};
}
Ark_Boolean GetMatrixImpl(Ark_drawing_Path peer,
                          Ark_Boolean forceClosed,
                          const Ark_Number* distance,
                          Ark_drawing_Matrix matrix,
                          Ark_drawing_PathMeasureMatrixFlags flags)
{
    return {};
}
Ark_Boolean BuildFromSvgStringImpl(Ark_drawing_Path peer,
                                   const Ark_String* str)
{
    return {};
}
} // drawing_PathAccessor
const GENERATED_ArkUIDrawing_PathAccessor* GetDrawing_PathAccessor()
{
    static const GENERATED_ArkUIDrawing_PathAccessor Drawing_PathAccessorImpl {
        drawing_PathAccessor::DestroyPeerImpl,
        drawing_PathAccessor::Construct0Impl,
        drawing_PathAccessor::Construct1Impl,
        drawing_PathAccessor::GetFinalizerImpl,
        drawing_PathAccessor::MoveToImpl,
        drawing_PathAccessor::LineToImpl,
        drawing_PathAccessor::ArcToImpl,
        drawing_PathAccessor::QuadToImpl,
        drawing_PathAccessor::ConicToImpl,
        drawing_PathAccessor::CubicToImpl,
        drawing_PathAccessor::RMoveToImpl,
        drawing_PathAccessor::RLineToImpl,
        drawing_PathAccessor::RQuadToImpl,
        drawing_PathAccessor::RConicToImpl,
        drawing_PathAccessor::RCubicToImpl,
        drawing_PathAccessor::AddPolygonImpl,
        drawing_PathAccessor::OpImpl,
        drawing_PathAccessor::AddArcImpl,
        drawing_PathAccessor::AddCircleImpl,
        drawing_PathAccessor::AddOvalImpl,
        drawing_PathAccessor::AddRectImpl,
        drawing_PathAccessor::AddRoundRectImpl,
        drawing_PathAccessor::AddPathImpl,
        drawing_PathAccessor::TransformImpl,
        drawing_PathAccessor::ContainsImpl,
        drawing_PathAccessor::SetFillTypeImpl,
        drawing_PathAccessor::GetBoundsImpl,
        drawing_PathAccessor::CloseImpl,
        drawing_PathAccessor::OffsetImpl,
        drawing_PathAccessor::ResetImpl,
        drawing_PathAccessor::GetLengthImpl,
        drawing_PathAccessor::GetPositionAndTangentImpl,
        drawing_PathAccessor::IsClosedImpl,
        drawing_PathAccessor::GetMatrixImpl,
        drawing_PathAccessor::BuildFromSvgStringImpl,
    };
    return &Drawing_PathAccessorImpl;
}

}
