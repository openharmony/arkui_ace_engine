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
namespace CanvasPathAccessor {
void DestroyPeerImpl(Ark_CanvasPath peer)
{
}
Ark_CanvasPath CtorImpl()
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void ArcImpl(Ark_CanvasPath peer,
             const Ark_Number* x,
             const Ark_Number* y,
             const Ark_Number* radius,
             const Ark_Number* startAngle,
             const Ark_Number* endAngle,
             const Opt_Boolean* counterclockwise)
{
}
void ArcToImpl(Ark_CanvasPath peer,
               const Ark_Number* x1,
               const Ark_Number* y1,
               const Ark_Number* x2,
               const Ark_Number* y2,
               const Ark_Number* radius)
{
}
void BezierCurveToImpl(Ark_CanvasPath peer,
                       const Ark_Number* cp1x,
                       const Ark_Number* cp1y,
                       const Ark_Number* cp2x,
                       const Ark_Number* cp2y,
                       const Ark_Number* x,
                       const Ark_Number* y)
{
}
void ClosePathImpl(Ark_CanvasPath peer)
{
}
void EllipseImpl(Ark_CanvasPath peer,
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
void LineToImpl(Ark_CanvasPath peer,
                const Ark_Number* x,
                const Ark_Number* y)
{
}
void MoveToImpl(Ark_CanvasPath peer,
                const Ark_Number* x,
                const Ark_Number* y)
{
}
void QuadraticCurveToImpl(Ark_CanvasPath peer,
                          const Ark_Number* cpx,
                          const Ark_Number* cpy,
                          const Ark_Number* x,
                          const Ark_Number* y)
{
}
void RectImpl(Ark_CanvasPath peer,
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
        CanvasPathAccessor::DestroyPeerImpl,
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
