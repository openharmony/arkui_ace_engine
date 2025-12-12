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
Ark_CanvasPath ConstructImpl()
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
             Ark_Float64 x,
             Ark_Float64 y,
             Ark_Float64 radius,
             Ark_Float64 startAngle,
             Ark_Float64 endAngle,
             const Opt_Boolean* counterclockwise)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasPathPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    CanvasPathPeerImpl::ArcParam params = {
        .x = Converter::Convert<double>(x),
        .y = Converter::Convert<double>(y),
        .radius = Converter::Convert<double>(radius),
        .startAngle = Converter::Convert<double>(startAngle),
        .endAngle = Converter::Convert<double>(endAngle),
        .anticlockwise = Converter::OptConvertPtr<bool>(counterclockwise),
    };
    peerImpl->Path2DArc(params);
}
void ArcToImpl(Ark_CanvasPath peer,
               Ark_Float64 x1,
               Ark_Float64 y1,
               Ark_Float64 x2,
               Ark_Float64 y2,
               Ark_Float64 radius)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasPathPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    CanvasPathPeerImpl::ArcToParam params = {
        .x1 = Converter::Convert<double>(x1),
        .y1 = Converter::Convert<double>(y1),
        .x2 = Converter::Convert<double>(x2),
        .y2 = Converter::Convert<double>(y2),
        .radius = Converter::Convert<double>(radius),
    };
    peerImpl->Path2DArcTo(params);
}
void BezierCurveToImpl(Ark_CanvasPath peer,
                       Ark_Float64 cp1x,
                       Ark_Float64 cp1y,
                       Ark_Float64 cp2x,
                       Ark_Float64 cp2y,
                       Ark_Float64 x,
                       Ark_Float64 y)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasPathPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    CanvasPathPeerImpl::BezierCurveToParam params = {
        .cp1x = Converter::Convert<double>(cp1x),
        .cp1y = Converter::Convert<double>(cp1y),
        .cp2x = Converter::Convert<double>(cp2x),
        .cp2y = Converter::Convert<double>(cp2y),
        .x = Converter::Convert<double>(x),
        .y = Converter::Convert<double>(y),
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
                 Ark_Float64 x,
                 Ark_Float64 y,
                 Ark_Float64 radiusX,
                 Ark_Float64 radiusY,
                 Ark_Float64 rotation,
                 Ark_Float64 startAngle,
                 Ark_Float64 endAngle,
                 const Opt_Boolean* counterclockwise)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasPathPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    CanvasPathPeerImpl::EllipseParam params = {
        .x = Converter::Convert<double>(x),
        .y = Converter::Convert<double>(y),
        .radiusX = Converter::Convert<double>(radiusX),
        .radiusY = Converter::Convert<double>(radiusY),
        .rotation = Converter::Convert<double>(rotation),
        .startAngle = Converter::Convert<double>(startAngle),
        .endAngle = Converter::Convert<double>(endAngle),
        .anticlockwise = Converter::OptConvertPtr<bool>(counterclockwise),
    };
    peerImpl->Path2DEllipse(params);
}
void LineToImpl(Ark_CanvasPath peer,
                Ark_Float64 x,
                Ark_Float64 y)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasPathPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    auto cx = Converter::Convert<double>(x);
    auto cy = Converter::Convert<double>(y);
    peerImpl->Path2DLineTo(cx, cy);
}
void MoveToImpl(Ark_CanvasPath peer,
                Ark_Float64 x,
                Ark_Float64 y)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasPathPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    auto cx = Converter::Convert<double>(x);
    auto cy = Converter::Convert<double>(y);
    peerImpl->Path2DMoveTo(cx, cy);
}
void QuadraticCurveToImpl(Ark_CanvasPath peer,
                          Ark_Float64 cpx,
                          Ark_Float64 cpy,
                          Ark_Float64 x,
                          Ark_Float64 y)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasPathPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    auto pcpx = Converter::Convert<double>(cpx);
    auto pcpy = Converter::Convert<double>(cpy);
    auto px = Converter::Convert<double>(x);
    auto py = Converter::Convert<double>(y);
    peerImpl->Path2DQuadraticCurveTo(pcpx, pcpy, px, py);
}
void RectImpl(Ark_CanvasPath peer,
              Ark_Float64 x,
              Ark_Float64 y,
              Ark_Float64 w,
              Ark_Float64 h)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasPathPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    auto px = Converter::Convert<double>(x);
    auto py = Converter::Convert<double>(y);
    auto pw = Converter::Convert<double>(w);
    auto ph = Converter::Convert<double>(h);
    peerImpl->Path2DRect(px, py, pw, ph);
}
} // CanvasPathAccessor
const GENERATED_ArkUICanvasPathAccessor* GetCanvasPathAccessor()
{
    static const GENERATED_ArkUICanvasPathAccessor CanvasPathAccessorImpl {
        CanvasPathAccessor::DestroyPeerImpl,
        CanvasPathAccessor::ConstructImpl,
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
