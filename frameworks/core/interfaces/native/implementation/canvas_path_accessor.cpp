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
#include "canvas_path_accessor_peer_impl.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace CanvasPathAccessor {
void DestroyPeerImpl(CanvasPathPeer* peer)
{
    auto peerImpl = reinterpret_cast<CanvasPathPeerImpl*>(peer);
    if (peerImpl) {
        peerImpl->DecRefCount();
    }
}
Ark_NativePointer CtorImpl()
{
    auto peerImpl = Referenced::MakeRefPtr<CanvasPathPeerImpl>();
    peerImpl->IncRefCount();
    return reinterpret_cast<CanvasPathPeer*>(Referenced::RawPtr(peerImpl));
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void ArcImpl(CanvasPathPeer* peer,
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
    auto clockwise = Converter::OptConvert<bool>(*counterclockwise);
    auto px = static_cast<double>(Converter::Convert<float>(*x));
    auto py = static_cast<double>(Converter::Convert<float>(*y));
    auto rad = static_cast<double>(Converter::Convert<float>(*radius));
    auto start = static_cast<double>(Converter::Convert<float>(*startAngle));
    auto end = static_cast<double>(Converter::Convert<float>(*endAngle));
    auto ccw = clockwise ? clockwise.value() : false;
    peerImpl->TriggerArcImpl(px, py, rad, start, end, ccw);
}
void ArcToImpl(CanvasPathPeer* peer,
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

    auto px1 = static_cast<double>(Converter::Convert<float>(*x1));
    auto py1 = static_cast<double>(Converter::Convert<float>(*y1));
    auto px2 = static_cast<double>(Converter::Convert<float>(*x2));
    auto py2 = static_cast<double>(Converter::Convert<float>(*y2));
    auto rad = static_cast<double>(Converter::Convert<float>(*radius));
    peerImpl->TriggerArcToImpl(px1, py1, px2, py2, rad);
}
void BezierCurveToImpl(CanvasPathPeer* peer,
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

    auto pcp1x = static_cast<double>(Converter::Convert<float>(*cp1x));
    auto pcp1y = static_cast<double>(Converter::Convert<float>(*cp1y));
    auto pcp2x = static_cast<double>(Converter::Convert<float>(*cp2x));
    auto pcp2y = static_cast<double>(Converter::Convert<float>(*cp2y));
    auto px = static_cast<double>(Converter::Convert<float>(*x));
    auto py = static_cast<double>(Converter::Convert<float>(*y));
    peerImpl->TriggerBezierCurveToImpl(pcp1x, pcp1y, pcp2x, pcp2y, px, py);
}
void ClosePathImpl(CanvasPathPeer* peer)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasPathPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    peerImpl->TriggerClosePathImpl();
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
    auto clockwise = Converter::OptConvert<bool>(*counterclockwise);

    auto px = static_cast<double>(Converter::Convert<float>(*x));
    auto py = static_cast<double>(Converter::Convert<float>(*y));
    auto radX = static_cast<double>(Converter::Convert<float>(*radiusX));
    auto radY = static_cast<double>(Converter::Convert<float>(*radiusY));
    auto rot = static_cast<double>(Converter::Convert<float>(*rotation));
    auto start = static_cast<double>(Converter::Convert<float>(*startAngle));
    auto end = static_cast<double>(Converter::Convert<float>(*endAngle));
    auto ccw = clockwise ? clockwise.value() : false;
    peerImpl->TriggerEllipseImpl(px, py, radX, radY, rot, start, end, ccw);
}
void LineToImpl(CanvasPathPeer* peer,
                const Ark_Number* x,
                const Ark_Number* y)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasPathPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    CHECK_NULL_VOID(x);
    CHECK_NULL_VOID(y);
    peerImpl->TriggerLineToImpl(static_cast<double>(Converter::Convert<float>(*x)),
                                static_cast<double>(Converter::Convert<float>(*y)));
}
void MoveToImpl(CanvasPathPeer* peer,
                const Ark_Number* x,
                const Ark_Number* y)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasPathPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    CHECK_NULL_VOID(x);
    CHECK_NULL_VOID(y);
    peerImpl->TriggerMoveToImpl(static_cast<double>(Converter::Convert<float>(*x)),
                                static_cast<double>(Converter::Convert<float>(*y)));
}
void QuadraticCurveToImpl(CanvasPathPeer* peer,
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
    QuadraticCurveParam params;
    auto pcpx = static_cast<double>(Converter::Convert<float>(*cpx));
    auto pcpy = static_cast<double>(Converter::Convert<float>(*cpy));
    auto px = static_cast<double>(Converter::Convert<float>(*x));
    auto py = static_cast<double>(Converter::Convert<float>(*y));
    peerImpl->TriggerQuadraticCurveToImpl(pcpx, pcpy, px, py);
}
void RectImpl(CanvasPathPeer* peer,
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
    peerImpl->TriggerRectImpl(px, py, pw, ph);
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

struct CanvasPathPeer {
    virtual ~CanvasPathPeer() = default;
};
}
