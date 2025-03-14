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
#include "canvas_path_peer_impl.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace CanvasPathAccessor {
void DestroyPeerImpl(Ark_CanvasPath peer)
{
    auto peerImpl = reinterpret_cast<CanvasPathPeerImpl*>(peer);
    if (peerImpl) {
        peerImpl->DecRefCount();
    }
}
Ark_CanvasPath CtorImpl()
{
    auto peerImpl = Referenced::MakeRefPtr<CanvasPathPeerImpl>();
    peerImpl->IncRefCount();
    return reinterpret_cast<CanvasPathPeer*>(Referenced::RawPtr(peerImpl));
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
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasPathPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    CHECK_NULL_VOID(x);
    CHECK_NULL_VOID(y);
    CHECK_NULL_VOID(radius);
    CHECK_NULL_VOID(startAngle);
    CHECK_NULL_VOID(endAngle);
    CanvasPathPeerImpl::ArcParam params = {
        .x = static_cast<double>(Converter::Convert<float>(*x)),
        .y = static_cast<double>(Converter::Convert<float>(*y)),
        .radius = static_cast<double>(Converter::Convert<float>(*radius)),
        .startAngle = static_cast<double>(Converter::Convert<float>(*startAngle)),
        .endAngle = static_cast<double>(Converter::Convert<float>(*endAngle)),
        .anticlockwise = Converter::OptConvert<bool>(*counterclockwise),
    };
    peerImpl->Path2DArc(params);
}
void ArcToImpl(Ark_CanvasPath peer,
               const Ark_Number* x1,
               const Ark_Number* y1,
               const Ark_Number* x2,
               const Ark_Number* y2,
               const Ark_Number* radius)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasPathPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    CHECK_NULL_VOID(x1);
    CHECK_NULL_VOID(y1);
    CHECK_NULL_VOID(x2);
    CHECK_NULL_VOID(y2);
    CHECK_NULL_VOID(radius);
    CanvasPathPeerImpl::ArcToParam params = {
        .x1 = static_cast<double>(Converter::Convert<float>(*x1)),
        .y1 = static_cast<double>(Converter::Convert<float>(*y1)),
        .x2 = static_cast<double>(Converter::Convert<float>(*x2)),
        .y2 = static_cast<double>(Converter::Convert<float>(*y2)),
        .radius = static_cast<double>(Converter::Convert<float>(*radius)),
    };
    peerImpl->Path2DArcTo(params);
}
void BezierCurveToImpl(Ark_CanvasPath peer,
                       const Ark_Number* cp1x,
                       const Ark_Number* cp1y,
                       const Ark_Number* cp2x,
                       const Ark_Number* cp2y,
                       const Ark_Number* x,
                       const Ark_Number* y)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasPathPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    CHECK_NULL_VOID(cp1x);
    CHECK_NULL_VOID(cp1y);
    CHECK_NULL_VOID(cp2x);
    CHECK_NULL_VOID(cp2y);
    CHECK_NULL_VOID(x);
    CHECK_NULL_VOID(y);
    CanvasPathPeerImpl::BezierCurveToParam params = {
        .cp1x = static_cast<double>(Converter::Convert<float>(*cp1x)),
        .cp1y = static_cast<double>(Converter::Convert<float>(*cp1y)),
        .cp2x = static_cast<double>(Converter::Convert<float>(*cp2x)),
        .cp2y = static_cast<double>(Converter::Convert<float>(*cp2y)),
        .x = static_cast<double>(Converter::Convert<float>(*x)),
        .y = static_cast<double>(Converter::Convert<float>(*y)),
    };
    peerImpl->Path2DBezierCurveTo(params);
}
void ClosePathImpl(Ark_CanvasPath peer)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasPathPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    peerImpl->Path2DClosePath();
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
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasPathPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    CHECK_NULL_VOID(x);
    CHECK_NULL_VOID(y);
    CHECK_NULL_VOID(radiusX);
    CHECK_NULL_VOID(radiusY);
    CHECK_NULL_VOID(rotation);
    CHECK_NULL_VOID(startAngle);
    CHECK_NULL_VOID(endAngle);
    CHECK_NULL_VOID(counterclockwise);
    CanvasPathPeerImpl::EllipseParam params = {
        .x = static_cast<double>(Converter::Convert<float>(*x)),
        .y = static_cast<double>(Converter::Convert<float>(*y)),
        .radiusX = static_cast<double>(Converter::Convert<float>(*radiusX)),
        .radiusY = static_cast<double>(Converter::Convert<float>(*radiusY)),
        .rotation = static_cast<double>(Converter::Convert<float>(*rotation)),
        .startAngle = static_cast<double>(Converter::Convert<float>(*startAngle)),
        .endAngle = static_cast<double>(Converter::Convert<float>(*endAngle)),
        .anticlockwise = Converter::OptConvert<bool>(*counterclockwise),
    };
    peerImpl->Path2DEllipse(params);
}
void LineToImpl(Ark_CanvasPath peer,
                const Ark_Number* x,
                const Ark_Number* y)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasPathPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    CHECK_NULL_VOID(x);
    CHECK_NULL_VOID(y);
    auto cx = static_cast<double>(Converter::Convert<float>(*x));
    auto cy = static_cast<double>(Converter::Convert<float>(*y));
    peerImpl->Path2DLineTo(cx, cy);
}
void MoveToImpl(Ark_CanvasPath peer,
                const Ark_Number* x,
                const Ark_Number* y)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasPathPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    CHECK_NULL_VOID(x);
    CHECK_NULL_VOID(y);
    auto cx = static_cast<double>(Converter::Convert<float>(*x));
    auto cy = static_cast<double>(Converter::Convert<float>(*y));
    peerImpl->Path2DMoveTo(cx, cy);
}
void QuadraticCurveToImpl(Ark_CanvasPath peer,
                          const Ark_Number* cpx,
                          const Ark_Number* cpy,
                          const Ark_Number* x,
                          const Ark_Number* y)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasPathPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    CHECK_NULL_VOID(cpx);
    CHECK_NULL_VOID(cpy);
    CHECK_NULL_VOID(x);
    CHECK_NULL_VOID(y);
    auto pcpx = static_cast<double>(Converter::Convert<float>(*cpx));
    auto pcpy = static_cast<double>(Converter::Convert<float>(*cpy));
    auto px = static_cast<double>(Converter::Convert<float>(*x));
    auto py = static_cast<double>(Converter::Convert<float>(*y));
    peerImpl->Path2DQuadraticCurveTo(pcpx, pcpy, px, py);
}
void RectImpl(Ark_CanvasPath peer,
              const Ark_Number* x,
              const Ark_Number* y,
              const Ark_Number* w,
              const Ark_Number* h)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasPathPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    CHECK_NULL_VOID(x);
    CHECK_NULL_VOID(y);
    CHECK_NULL_VOID(w);
    CHECK_NULL_VOID(h);
    auto px = static_cast<double>(Converter::Convert<float>(*x));
    auto py = static_cast<double>(Converter::Convert<float>(*y));
    auto pw = static_cast<double>(Converter::Convert<float>(*w));
    auto ph = static_cast<double>(Converter::Convert<float>(*h));
    peerImpl->Path2DRect(px, py, pw, ph);
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
