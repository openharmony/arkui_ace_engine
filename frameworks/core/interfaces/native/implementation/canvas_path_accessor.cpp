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
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"
#include "canvas_path_accessor_peer_impl.h"

namespace OHOS::Ace::NG {
    struct Ark_Helper_Rect {
    Ark_Number x;
    Ark_Number y;
    Ark_Number w;
    Ark_Number h;
};
namespace Converter {
template<>
Rect Convert(const Ark_Helper_Rect& src)
{
    return Rect(
        static_cast<double>(Converter::Convert<float>(src.x)),
        static_cast<double>(Converter::Convert<float>(src.y)),
        static_cast<double>(Converter::Convert<float>(src.w)),
        static_cast<double>(Converter::Convert<float>(src.h))
    );
}
} // namespace OHOS::Ace::NG::Converter
} // namespace OHOS::Ace::NG

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
    CHECK_NULL_VOID(peerImpl->path);
    CHECK_NULL_VOID(x);
    CHECK_NULL_VOID(y);
    CHECK_NULL_VOID(radius);
    CHECK_NULL_VOID(startAngle);
    CHECK_NULL_VOID(endAngle);
    auto clockwise = Converter::OptConvert<bool>(*counterclockwise);
    ArcParam params;
    params.x = Converter::Convert<float>(*x);
    params.y = Converter::Convert<float>(*y);
    params.radius = Converter::Convert<float>(*radius);
    params.startAngle = Converter::Convert<float>(*startAngle);
    params.endAngle = Converter::Convert<float>(*endAngle);
    params.anticlockwise = clockwise ? clockwise.value() : false;
    peerImpl->path->Arc(params);
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
    CHECK_NULL_VOID(peerImpl->path);
    CHECK_NULL_VOID(x1);
    CHECK_NULL_VOID(y1);
    CHECK_NULL_VOID(x2);
    CHECK_NULL_VOID(y2);
    CHECK_NULL_VOID(radius);
    ArcToParam params;
    params.x1 = Converter::Convert<float>(*x1);
    params.y1 = Converter::Convert<float>(*y1);
    params.x2 = Converter::Convert<float>(*x2);
    params.y2 = Converter::Convert<float>(*y2);
    params.radius = Converter::Convert<float>(*radius);
    peerImpl->path->ArcTo(params);
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
    CHECK_NULL_VOID(peerImpl->path);
    CHECK_NULL_VOID(cp1x);
    CHECK_NULL_VOID(cp1y);
    CHECK_NULL_VOID(cp2x);
    CHECK_NULL_VOID(cp2y);
    CHECK_NULL_VOID(x);
    CHECK_NULL_VOID(y);
    BezierCurveParam  params;
    params.cp1x = Converter::Convert<float>(*cp1x);
    params.cp1y = Converter::Convert<float>(*cp1y);
    params.cp2x = Converter::Convert<float>(*cp2x);
    params.cp2y = Converter::Convert<float>(*cp2y);
    params.x = Converter::Convert<float>(*x);
    params.y = Converter::Convert<float>(*y);
    peerImpl->path->BezierCurveTo(params);
}
void ClosePathImpl(CanvasPathPeer* peer)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasPathPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    CHECK_NULL_VOID(peerImpl->path);
    peerImpl->path->ClosePath();
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
    CHECK_NULL_VOID(peerImpl->path);
    CHECK_NULL_VOID(x);
    CHECK_NULL_VOID(y);
    CHECK_NULL_VOID(radiusX);
    CHECK_NULL_VOID(radiusY);
    CHECK_NULL_VOID(rotation);
    CHECK_NULL_VOID(startAngle);
    CHECK_NULL_VOID(endAngle);
    CHECK_NULL_VOID(counterclockwise);
    auto clockwise = Converter::OptConvert<bool>(*counterclockwise);
    EllipseParam params;
    params.x = Converter::Convert<float>(*x);
    params.y = Converter::Convert<float>(*y);
    params.radiusX = Converter::Convert<float>(*radiusX);
    params.radiusY = Converter::Convert<float>(*radiusY);
    params.rotation = Converter::Convert<float>(*rotation);
    params.startAngle = Converter::Convert<float>(*startAngle);
    params.endAngle = Converter::Convert<float>(*endAngle);
    params.anticlockwise = clockwise ? clockwise.value() : false;
    peerImpl->path->Ellipse(params);
}
void LineToImpl(CanvasPathPeer* peer,
                const Ark_Number* x,
                const Ark_Number* y)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasPathPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    CHECK_NULL_VOID(peerImpl->path);
    CHECK_NULL_VOID(x);
    CHECK_NULL_VOID(y);
    peerImpl->path->LineTo(Converter::Convert<float>(*x), Converter::Convert<float>(*y));
}
void MoveToImpl(CanvasPathPeer* peer,
                const Ark_Number* x,
                const Ark_Number* y)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasPathPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    CHECK_NULL_VOID(peerImpl->path);
    CHECK_NULL_VOID(x);
    CHECK_NULL_VOID(y);
    peerImpl->path->MoveTo(Converter::Convert<float>(*x), Converter::Convert<float>(*y));
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
    CHECK_NULL_VOID(peerImpl->path);
    CHECK_NULL_VOID(cpx);
    CHECK_NULL_VOID(cpy);
    CHECK_NULL_VOID(x);
    CHECK_NULL_VOID(y);
    QuadraticCurveParam params;
    params.cpx = Converter::Convert<float>(*cpx);
    params.cpy = Converter::Convert<float>(*cpy);
    params.x = Converter::Convert<float>(*x);
    params.y = Converter::Convert<float>(*y);
    peerImpl->path->QuadraticCurveTo(params);
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
    CHECK_NULL_VOID(peerImpl->path);
    CHECK_NULL_VOID(x);
    CHECK_NULL_VOID(y);
    CHECK_NULL_VOID(w);
    CHECK_NULL_VOID(h);
    auto arkRect = Ark_Helper_Rect {
        .x = *x,
        .y = *y,
        .w = *w,
        .h = *h
    };
    auto rect = Converter::Convert<Rect>(arkRect);
    peerImpl->path->AddRect(rect);
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
