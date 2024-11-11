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
namespace CanvasPathAccessor {
CanvasPathPeer* CtorImpl()
{
    return 0;
}
Ark_NativePointer GetFinalizerImpl()
{
    return 0;
}
void ArcImpl(CanvasPathPeer* peer,
             const Ark_Number* x,
             const Ark_Number* y,
             const Ark_Number* radius,
             const Ark_Number* startAngle,
             const Ark_Number* endAngle,
             const Opt_Boolean* counterclockwise)
{
}
void ArcToImpl(CanvasPathPeer* peer,
               const Ark_Number* x1,
               const Ark_Number* y1,
               const Ark_Number* x2,
               const Ark_Number* y2,
               const Ark_Number* radius)
{
}
void BezierCurveToImpl(CanvasPathPeer* peer,
                       const Ark_Number* cp1x,
                       const Ark_Number* cp1y,
                       const Ark_Number* cp2x,
                       const Ark_Number* cp2y,
                       const Ark_Number* x,
                       const Ark_Number* y)
{
}
void ClosePathImpl(CanvasPathPeer* peer)
{
}
void EllipseImpl(CanvasPathPeer* peer,
                 const Ark_Number* x,
                 const Ark_Number* y,
                 const Ark_Number* radiusX,
                 const Ark_Number* radiusY,
                 const Ark_Number* rotation,
                 const Ark_Number* startAngle,
                 const Ark_Number* endAngle,
                 const Opt_Boolean* counterclockwise)
{
}
void LineToImpl(CanvasPathPeer* peer,
                const Ark_Number* x,
                const Ark_Number* y)
{
}
void MoveToImpl(CanvasPathPeer* peer,
                const Ark_Number* x,
                const Ark_Number* y)
{
}
void QuadraticCurveToImpl(CanvasPathPeer* peer,
                          const Ark_Number* cpx,
                          const Ark_Number* cpy,
                          const Ark_Number* x,
                          const Ark_Number* y)
{
}
void RectImpl(CanvasPathPeer* peer,
              const Ark_Number* x,
              const Ark_Number* y,
              const Ark_Number* w,
              const Ark_Number* h)
{
}
} // CanvasPathAccessor
const GENERATED_ArkUICanvasPathAccessor* GetCanvasPathAccessor()
{
    static const GENERATED_ArkUICanvasPathAccessor CanvasPathAccessorImpl {
        CanvasPathAccessor::CtorImpl,
        CanvasPathAccessor::GetFinalizerImpl,
        CanvasPathAccessor::ArcImpl,
        CanvasPathAccessor::ArcToImpl,
        CanvasPathAccessor::BezierCurveToImpl,
        CanvasPathAccessor::ClosePathImpl,
        CanvasPathAccessor::EllipseImpl,
        CanvasPathAccessor::LineToImpl,
        CanvasPathAccessor::MoveToImpl,
        CanvasPathAccessor::QuadraticCurveToImpl,
        CanvasPathAccessor::RectImpl,
    };
    return &CanvasPathAccessorImpl;
}

}
