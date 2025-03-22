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
#include "core/interfaces/native/utility/converter_union.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "canvas_renderer_peer_impl.h"
#include "canvas_path_peer_impl.h"
#include "canvas_pattern_peer.h"
#include "canvas_gradient_peer.h"
#include "matrix2d_peer_impl.h"
#include "image_bitmap_peer_impl.h"
#include "image_data_peer.h"
#include "base/utils/utils.h"
#include "pixel_map_peer.h"
#include "canvas_rendering_context2d_peer_impl.h"

namespace OHOS::Ace::NG::GeneratedModifier {
const GENERATED_ArkUICanvasGradientAccessor* GetCanvasGradientAccessor();
const GENERATED_ArkUICanvasPatternAccessor* GetCanvasPatternAccessor();
const GENERATED_ArkUICanvasRenderingContext2DAccessor* GetCanvasRenderingContext2DAccessor();
const GENERATED_ArkUIImageDataAccessor* GetImageDataAccessor();
const GENERATED_ArkUIMatrix2DAccessor* GetMatrix2DAccessor();
const GENERATED_ArkUIPixelMapAccessor* GetPixelMapAccessor();

namespace CanvasRendererAccessor {
void DestroyPeerImpl(Ark_CanvasRenderer peer)
{
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    if (peerImpl) {
        peerImpl->DecRefCount();
    }
}
Ark_CanvasRenderer CtorImpl()
{
    auto peerImpl = Referenced::MakeRefPtr<CanvasRendererPeerImpl>();
    peerImpl->IncRefCount();
    return reinterpret_cast<CanvasRendererPeer*>(Referenced::RawPtr(peerImpl));
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void DrawImage0Impl(Ark_CanvasRenderer peer,
                    const Ark_Union_ImageBitmap_PixelMap* image,
                    const Ark_Number* dx,
                    const Ark_Number* dy)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    CHECK_NULL_VOID(image);
    CHECK_NULL_VOID(dx);
    CHECK_NULL_VOID(dy);
    CanvasRendererPeerImpl::DrawImageParam params = {
        .dx = static_cast<double>(Converter::Convert<float>(*dx)),
        .dy = static_cast<double>(Converter::Convert<float>(*dy)),
        .size = CanvasRendererPeerImpl::SizeParam::TWO_ARGS,
    };
    Converter::VisitUnion(
        *image,
        [&params, peerImpl](const Ark_ImageBitmap& bitmap) {
            if (bitmap->IsSvg()) {
                peerImpl->DrawSvgImage(bitmap, params);
            } else {
                peerImpl->DrawImage(bitmap, params);
            }
        },
        [&params, peerImpl](const Ark_PixelMap& pixelMap) {
            CHECK_NULL_VOID(pixelMap);
            peerImpl->DrawPixelMap(pixelMap, params);
        },
        []() {});
}
void DrawImage1Impl(Ark_CanvasRenderer peer,
                    const Ark_Union_ImageBitmap_PixelMap* image,
                    const Ark_Number* dx,
                    const Ark_Number* dy,
                    const Ark_Number* dw,
                    const Ark_Number* dh)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    CHECK_NULL_VOID(image);
    CHECK_NULL_VOID(dx);
    CHECK_NULL_VOID(dy);
    CHECK_NULL_VOID(dw);
    CHECK_NULL_VOID(dh);
    CanvasRendererPeerImpl::DrawImageParam params = {
        .dx = static_cast<double>(Converter::Convert<float>(*dx)),
        .dy = static_cast<double>(Converter::Convert<float>(*dy)),
        .dWidth = static_cast<double>(Converter::Convert<float>(*dw)),
        .dHeight = static_cast<double>(Converter::Convert<float>(*dh)),
        .size = CanvasRendererPeerImpl::SizeParam::FOUR_ARGS,
    };
    Converter::VisitUnion(
        *image,
        [&params, peerImpl](const Ark_ImageBitmap& bitmap) {
            if (bitmap->IsSvg()) {
                peerImpl->DrawSvgImage(bitmap, params);
            } else {
                peerImpl->DrawImage(bitmap, params);
            }
        },
        [&params, peerImpl](const Ark_PixelMap& pixelMap) {
            CHECK_NULL_VOID(pixelMap);
            peerImpl->DrawPixelMap(pixelMap, params);
        },
        []() {});
}
void DrawImage2Impl(Ark_CanvasRenderer peer,
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
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    CHECK_NULL_VOID(image);
    CHECK_NULL_VOID(sx);
    CHECK_NULL_VOID(sy);
    CHECK_NULL_VOID(sw);
    CHECK_NULL_VOID(sh);
    CHECK_NULL_VOID(dx);
    CHECK_NULL_VOID(dy);
    CHECK_NULL_VOID(dw);
    CHECK_NULL_VOID(dh);
    CanvasRendererPeerImpl::DrawImageParam params = {
        .sx = static_cast<double>(Converter::Convert<float>(*sx)),
        .sy = static_cast<double>(Converter::Convert<float>(*sy)),
        .sWidth = static_cast<double>(Converter::Convert<float>(*sw)),
        .sHeight = static_cast<double>(Converter::Convert<float>(*sh)),
        .dx = static_cast<double>(Converter::Convert<float>(*dx)),
        .dy = static_cast<double>(Converter::Convert<float>(*dy)),
        .dWidth = static_cast<double>(Converter::Convert<float>(*dw)),
        .dHeight = static_cast<double>(Converter::Convert<float>(*dh)),
        .size = CanvasRendererPeerImpl::SizeParam::EIGHT_ARGS,
    };
    Converter::VisitUnion(
        *image,
        [&params, peerImpl](const Ark_ImageBitmap& bitmap) {
            if (bitmap->IsSvg()) {
                peerImpl->DrawSvgImage(bitmap, params);
            } else {
                peerImpl->DrawImage(bitmap, params);
            }
        },
        [&params, peerImpl](const Ark_PixelMap& pixelMap) {
            CHECK_NULL_VOID(pixelMap);
            peerImpl->DrawPixelMap(pixelMap, params);
        },
        []() {});
}
void BeginPathImpl(Ark_CanvasRenderer peer)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    peerImpl->BeginPath();
}
void Clip0Impl(Ark_CanvasRenderer peer,
               const Opt_String* fillRule)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    CHECK_NULL_VOID(fillRule);
    auto ruleStr = Converter::OptConvert<std::string>(*fillRule);
    peerImpl->Clip(ruleStr);
}
void Clip1Impl(Ark_CanvasRenderer peer,
               Ark_Path2D path,
               const Opt_String* fillRule)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    CHECK_NULL_VOID(path);
    CHECK_NULL_VOID(fillRule);
    auto pathImpl = reinterpret_cast<CanvasPathPeerImpl*>(path);
    CHECK_NULL_VOID(pathImpl);
    auto ruleStr = Converter::OptConvert<std::string>(*fillRule);
    peerImpl->Clip(ruleStr, pathImpl->GetCanvasPath2d());
}
void Fill0Impl(Ark_CanvasRenderer peer,
               const Opt_String* fillRule)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    CHECK_NULL_VOID(fillRule);
    auto ruleStr = Converter::OptConvert<std::string>(*fillRule);
    peerImpl->Fill(ruleStr);
}
void Fill1Impl(Ark_CanvasRenderer peer,
               Ark_Path2D path,
               const Opt_String* fillRule)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    CHECK_NULL_VOID(path);
    CHECK_NULL_VOID(fillRule);
    auto pathImpl = reinterpret_cast<CanvasPathPeerImpl*>(path);
    CHECK_NULL_VOID(pathImpl);
    auto ruleStr = Converter::OptConvert<std::string>(*fillRule);
    peerImpl->Fill(ruleStr, pathImpl->GetCanvasPath2d());
}
void Stroke0Impl(Ark_CanvasRenderer peer)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    peerImpl->Stroke();
}
void Stroke1Impl(Ark_CanvasRenderer peer,
                 Ark_Path2D path)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    CHECK_NULL_VOID(path);
    auto pathImpl = reinterpret_cast<CanvasPathPeerImpl*>(path);
    CHECK_NULL_VOID(pathImpl);
    peerImpl->Stroke(pathImpl->GetCanvasPath2d());
}
Ark_CanvasGradient CreateLinearGradientImpl(Ark_CanvasRenderer peer,
                                            const Ark_Number* x0,
                                            const Ark_Number* y0,
                                            const Ark_Number* x1,
                                            const Ark_Number* y1)
{
    CHECK_NULL_RETURN(peer, {});
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_RETURN(x0, {});
    CHECK_NULL_RETURN(y0, {});
    CHECK_NULL_RETURN(x1, {});
    CHECK_NULL_RETURN(y1, {});
    double cx0 = static_cast<double>(Converter::Convert<float>(*x0));
    double cy0 = static_cast<double>(Converter::Convert<float>(*y0));
    double cx1 = static_cast<double>(Converter::Convert<float>(*x1));
    double cy1 = static_cast<double>(Converter::Convert<float>(*y1));
    auto gradient = peerImpl->CreateLinearGradient(cx0, cy0, cx1, cy1);
    CHECK_NULL_RETURN(gradient, {});
    auto canvasGradientPeer = GetCanvasGradientAccessor()->ctor();
    CHECK_NULL_RETURN(canvasGradientPeer, {});
    canvasGradientPeer->SetGradient(gradient);
    return canvasGradientPeer;
}
Opt_CanvasPattern CreatePatternImpl(Ark_CanvasRenderer peer,
                                    Ark_ImageBitmap image,
                                    const Opt_String* repetition)
{
    auto invalid = Converter::ArkValue<Opt_CanvasPattern>();
    CHECK_NULL_RETURN(peer, invalid);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, invalid);
    CHECK_NULL_RETURN(image, invalid);
    CHECK_NULL_RETURN(repetition, invalid);
    auto repeat = Converter::OptConvert<std::string>(*repetition);
    auto pattern = GetCanvasPatternAccessor()->ctor();
    peerImpl->CreatePattern(image, pattern, repeat);
    return Converter::ArkValue<Opt_CanvasPattern>(pattern);
}
Ark_CanvasGradient CreateRadialGradientImpl(Ark_CanvasRenderer peer,
                                            const Ark_Number* x0,
                                            const Ark_Number* y0,
                                            const Ark_Number* r0,
                                            const Ark_Number* x1,
                                            const Ark_Number* y1,
                                            const Ark_Number* r1)
{
    CHECK_NULL_RETURN(peer, {});
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_RETURN(x0, {});
    CHECK_NULL_RETURN(y0, {});
    CHECK_NULL_RETURN(r0, {});
    CHECK_NULL_RETURN(x1, {});
    CHECK_NULL_RETURN(y1, {});
    CHECK_NULL_RETURN(r1, {});
    CanvasRendererPeerImpl::RadialGradientParam params = {
        .x0 = static_cast<double>(Converter::Convert<float>(*x0)),
        .y0 = static_cast<double>(Converter::Convert<float>(*y0)),
        .r0 = static_cast<double>(Converter::Convert<float>(*r0)),
        .x1 = static_cast<double>(Converter::Convert<float>(*x1)),
        .y1 = static_cast<double>(Converter::Convert<float>(*y1)),
        .r1 = static_cast<double>(Converter::Convert<float>(*r1)),
    };
    auto gradient = peerImpl->CreateRadialGradient(params);
    CHECK_NULL_RETURN(gradient, {});
    auto canvasGradientPeer = GetCanvasGradientAccessor()->ctor();
    CHECK_NULL_RETURN(canvasGradientPeer, {});
    canvasGradientPeer->SetGradient(gradient);
    return canvasGradientPeer;
}
Ark_CanvasGradient CreateConicGradientImpl(Ark_CanvasRenderer peer,
                                           const Ark_Number* startAngle,
                                           const Ark_Number* x,
                                           const Ark_Number* y)
{
    CHECK_NULL_RETURN(peer, {});
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_RETURN(startAngle, {});
    CHECK_NULL_RETURN(x, {});
    CHECK_NULL_RETURN(y, {});
    double ca = static_cast<double>(Converter::Convert<float>(*startAngle));
    double cx = static_cast<double>(Converter::Convert<float>(*x));
    double cy = static_cast<double>(Converter::Convert<float>(*y));
    auto gradient = peerImpl->CreateConicGradient(cx, cy, ca);
    CHECK_NULL_RETURN(gradient, {});
    auto canvasGradientPeer = GetCanvasGradientAccessor()->ctor();
    CHECK_NULL_RETURN(canvasGradientPeer, {});
    canvasGradientPeer->SetGradient(gradient);
    return canvasGradientPeer;
}
Ark_ImageData CreateImageData0Impl(Ark_CanvasRenderer peer,
                                   const Ark_Number* sw,
                                   const Ark_Number* sh)
{
    CHECK_NULL_RETURN(peer, {});
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, {});
    CHECK_NULL_RETURN(sw, {});
    CHECK_NULL_RETURN(sh, {});
    auto fWidth = static_cast<double>(Converter::Convert<float>(*sw));
    auto fHeight = static_cast<double>(Converter::Convert<float>(*sh));
    std::vector<uint8_t> vbuffer(0);
    uint32_t width = 0;
    uint32_t height = 0;
    peerImpl->CreateImageData(vbuffer, fWidth, fHeight, width, height);
    InteropBuffer interOpBuffer = {
        .data = vbuffer.data(),
        .length = vbuffer.size()
    };
    auto optBuffer = Converter::ArkValue<Opt_Buffer>(interOpBuffer);
    auto arkWidth = Converter::ArkValue<Ark_Number>(width);
    auto arkHeight = Converter::ArkValue<Ark_Number>(height);
    return GetImageDataAccessor()->ctor(&arkWidth, &arkHeight, &optBuffer);
}
Ark_ImageData CreateImageData1Impl(Ark_CanvasRenderer peer,
                                   Ark_ImageData imagedata)
{
    CHECK_NULL_RETURN(peer, {});
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, {});
    CHECK_NULL_RETURN(imagedata, {});
    std::vector<uint8_t> vbuffer(0);
    uint32_t width = 0;
    uint32_t height = 0;
    peerImpl->CreateImageData(vbuffer, imagedata->value, width, height);
    InteropBuffer interOpBuffer = {
        .data = vbuffer.data(),
        .length = vbuffer.size()
    };
    auto optBuffer = Converter::ArkValue<Opt_Buffer>(interOpBuffer);
    auto arkWidth = Converter::ArkValue<Ark_Number>(width);
    auto arkHeight = Converter::ArkValue<Ark_Number>(height);
    return GetImageDataAccessor()->ctor(&arkWidth, &arkHeight, &optBuffer);
}
Ark_ImageData GetImageDataImpl(Ark_CanvasRenderer peer,
                               const Ark_Number* sx,
                               const Ark_Number* sy,
                               const Ark_Number* sw,
                               const Ark_Number* sh)
{
    CHECK_NULL_RETURN(peer, {});
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, {});
    CHECK_NULL_RETURN(sx, {});
    CHECK_NULL_RETURN(sy, {});
    CHECK_NULL_RETURN(sw, {});
    CHECK_NULL_RETURN(sh, {});
    ImageSize imageSize = {
        .left = static_cast<double>(Converter::Convert<float>(*sx)),
        .top = static_cast<double>(Converter::Convert<float>(*sy)),
        .width = static_cast<double>(Converter::Convert<float>(*sw)),
        .height = static_cast<double>(Converter::Convert<float>(*sh))
    };
    std::vector<uint8_t> vbuffer(0);
    uint32_t width = 0;
    uint32_t height = 0;
    peerImpl->GetImageData(vbuffer, imageSize,  width, height);
    InteropBuffer interOpBuffer = {
        .data = vbuffer.data(),
        .length = vbuffer.size()
    };
    auto optBuffer = Converter::ArkValue<Opt_Buffer>(interOpBuffer);
    auto arkWidth = Converter::ArkValue<Ark_Number>(width);
    auto arkHeight = Converter::ArkValue<Ark_Number>(height);
    return GetImageDataAccessor()->ctor(&arkWidth, &arkHeight, &optBuffer);
}
Ark_PixelMap GetPixelMapImpl(Ark_CanvasRenderer peer,
                             const Ark_Number* sx,
                             const Ark_Number* sy,
                             const Ark_Number* sw,
                             const Ark_Number* sh)
{
    CHECK_NULL_RETURN(peer, {});
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, {});
    CHECK_NULL_RETURN(sx, {});
    CHECK_NULL_RETURN(sy, {});
    CHECK_NULL_RETURN(sw, {});
    CHECK_NULL_RETURN(sh, {});
    auto x = static_cast<double>(Converter::Convert<float>(*sx));
    auto y = static_cast<double>(Converter::Convert<float>(*sy));
    auto width = static_cast<double>(Converter::Convert<float>(*sw));
    auto height = static_cast<double>(Converter::Convert<float>(*sh));
    auto pixelMap = peerImpl->GetPixelMap(x, y, width, height);
    CHECK_NULL_RETURN(pixelMap, {});
    auto pixelMapPeer = GetPixelMapAccessor()->ctor();
    CHECK_NULL_RETURN(pixelMapPeer, {});
    pixelMapPeer->pixelMap = pixelMap;
    return pixelMapPeer;
}
void PutImageData0Impl(Ark_CanvasRenderer peer,
                       Ark_ImageData imagedata,
                       const Ark_Union_Number_String* dx,
                       const Ark_Union_Number_String* dy)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    CHECK_NULL_VOID(imagedata);
    CHECK_NULL_VOID(dx);
    CHECK_NULL_VOID(dy);
    CanvasRendererPeerImpl::PutImageDataParam params = {
        .x = Converter::OptConvert<Dimension>(*dx),
        .y = Converter::OptConvert<Dimension>(*dy),
        .size = CanvasRendererPeerImpl::SizeParam::TWO_ARGS,
    };
    auto src = imagedata->value;
    peerImpl->PutImageData(src, params);
}
void PutImageData1Impl(Ark_CanvasRenderer peer,
                       Ark_ImageData imagedata,
                       const Ark_Union_Number_String* dx,
                       const Ark_Union_Number_String* dy,
                       const Ark_Union_Number_String* dirtyX,
                       const Ark_Union_Number_String* dirtyY,
                       const Ark_Union_Number_String* dirtyWidth,
                       const Ark_Union_Number_String* dirtyHeight)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    CHECK_NULL_VOID(imagedata);
    CHECK_NULL_VOID(dx);
    CHECK_NULL_VOID(dy);
    CHECK_NULL_VOID(dirtyX);
    CHECK_NULL_VOID(dirtyY);
    CHECK_NULL_VOID(dirtyWidth);
    CHECK_NULL_VOID(dirtyHeight);
    CanvasRendererPeerImpl::PutImageDataParam params = {
        .x = Converter::OptConvert<Dimension>(*dx),
        .y = Converter::OptConvert<Dimension>(*dy),
        .dirtyX = Converter::OptConvert<Dimension>(*dirtyX),
        .dirtyY = Converter::OptConvert<Dimension>(*dirtyY),
        .dirtyWidth = Converter::OptConvert<Dimension>(*dirtyWidth),
        .dirtyHeight = Converter::OptConvert<Dimension>(*dirtyHeight),
        .size = CanvasRendererPeerImpl::SizeParam::SIX_ARGS,
    };
    auto src = imagedata->value;
    peerImpl->PutImageData(src, params);
}
Array_Number GetLineDashImpl(Ark_CanvasRenderer peer)
{
    CHECK_NULL_RETURN(peer, {});
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, {});
    auto lineDash = peerImpl->GetLineDash();
    return Converter::ArkValue<Array_Number>(lineDash, Converter::FC);
}
void SetLineDashImpl(Ark_CanvasRenderer peer,
                     const Array_Number* segments)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(segments);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    auto src = Converter::Convert<std::vector<float>>(*segments);
    std::vector<double> lineDash(src.begin(), src.end());
    peerImpl->SetLineDash(lineDash);
}
void ClearRectImpl(Ark_CanvasRenderer peer,
                   const Ark_Number* x,
                   const Ark_Number* y,
                   const Ark_Number* w,
                   const Ark_Number* h)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(x);
    CHECK_NULL_VOID(y);
    CHECK_NULL_VOID(w);
    CHECK_NULL_VOID(h);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    auto cx = static_cast<double>(Converter::Convert<float>(*x));
    auto cy = static_cast<double>(Converter::Convert<float>(*y));
    auto cw = static_cast<double>(Converter::Convert<float>(*w));
    auto ch = static_cast<double>(Converter::Convert<float>(*h));
    peerImpl->ClearRect(cx, cy, cw, ch);
}
void FillRectImpl(Ark_CanvasRenderer peer,
                  const Ark_Number* x,
                  const Ark_Number* y,
                  const Ark_Number* w,
                  const Ark_Number* h)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(x);
    CHECK_NULL_VOID(y);
    CHECK_NULL_VOID(w);
    CHECK_NULL_VOID(h);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    auto cx = static_cast<double>(Converter::Convert<float>(*x));
    auto cy = static_cast<double>(Converter::Convert<float>(*y));
    auto cw = static_cast<double>(Converter::Convert<float>(*w));
    auto ch = static_cast<double>(Converter::Convert<float>(*h));
    peerImpl->FillRect(cx, cy, cw, ch);
}
void StrokeRectImpl(Ark_CanvasRenderer peer,
                    const Ark_Number* x,
                    const Ark_Number* y,
                    const Ark_Number* w,
                    const Ark_Number* h)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(x);
    CHECK_NULL_VOID(y);
    CHECK_NULL_VOID(w);
    CHECK_NULL_VOID(h);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    auto cx = static_cast<double>(Converter::Convert<float>(*x));
    auto cy = static_cast<double>(Converter::Convert<float>(*y));
    auto cw = static_cast<double>(Converter::Convert<float>(*w));
    auto ch = static_cast<double>(Converter::Convert<float>(*h));
    peerImpl->StrokeRect(cx, cy, cw, ch);
}
void RestoreImpl(Ark_CanvasRenderer peer)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    peerImpl->Restore();
}
void SaveImpl(Ark_CanvasRenderer peer)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    peerImpl->Save();
}
void FillTextImpl(Ark_CanvasRenderer peer,
                  const Ark_String* text,
                  const Ark_Number* x,
                  const Ark_Number* y,
                  const Opt_Number* maxWidth)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(text);
    CHECK_NULL_VOID(x);
    CHECK_NULL_VOID(y);
    CHECK_NULL_VOID(maxWidth);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    auto valueText = Converter::Convert<std::string>(*text);
    auto valueX = static_cast<double>(Converter::Convert<float>(*x));
    auto valueY = static_cast<double>(Converter::Convert<float>(*y));
    auto optMaxWidth = Converter::OptConvert<float>(*maxWidth);
    peerImpl->FillText(valueText, valueX, valueY, optMaxWidth);
}
Ark_TextMetrics MeasureTextImpl(Ark_CanvasRenderer peer,
                                const Ark_String* text)
{
    CHECK_NULL_RETURN(peer, {});
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, {});
    CHECK_NULL_RETURN(text, {});
    auto content = Converter::Convert<std::string>(*text);
    Ace::TextMetrics textMetrics;
    peerImpl->MeasureText(textMetrics, content);
    return Converter::ArkValue<Ark_TextMetrics>(textMetrics);
}
void StrokeTextImpl(Ark_CanvasRenderer peer,
                    const Ark_String* text,
                    const Ark_Number* x,
                    const Ark_Number* y,
                    const Opt_Number* maxWidth)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(text);
    CHECK_NULL_VOID(x);
    CHECK_NULL_VOID(y);
    CHECK_NULL_VOID(maxWidth);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    auto valueText = Converter::Convert<std::string>(*text);
    auto valueX = static_cast<double>(Converter::Convert<float>(*x));
    auto valueY = static_cast<double>(Converter::Convert<float>(*y));
    auto optMaxWidth = Converter::OptConvert<float>(*maxWidth);
    peerImpl->StrokeText(valueText, valueX, valueY, optMaxWidth);
}
Ark_Matrix2D GetTransformImpl(Ark_CanvasRenderer peer)
{
    CHECK_NULL_RETURN(peer, {});
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, {});
    auto matrixPeer = reinterpret_cast<Matrix2DPeer*>(GetMatrix2DAccessor()->ctor());
    peerImpl->GetTransform(matrixPeer);
    return matrixPeer;
}
void ResetTransformImpl(Ark_CanvasRenderer peer)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    peerImpl->ResetTransform();
}
void RotateImpl(Ark_CanvasRenderer peer,
                const Ark_Number* angle)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(angle);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    auto rotateAngle = static_cast<double>(Converter::Convert<float>(*angle));
    peerImpl->Rotate(rotateAngle);
}
void ScaleImpl(Ark_CanvasRenderer peer,
               const Ark_Number* x,
               const Ark_Number* y)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(x);
    CHECK_NULL_VOID(y);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);

    auto scaleX = static_cast<double>(Converter::Convert<float>(*x));
    auto scaleY = static_cast<double>(Converter::Convert<float>(*y));
    peerImpl->Scale(scaleX, scaleY);
}
void SetTransform0Impl(Ark_CanvasRenderer peer,
                       const Ark_Number* a,
                       const Ark_Number* b,
                       const Ark_Number* c,
                       const Ark_Number* d,
                       const Ark_Number* e,
                       const Ark_Number* f)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    if (!a || !b || !c || !d || !e || !f) {
        peerImpl->ResetTransform();
        return;
    }
    auto param = TransformParam {
        .scaleX = static_cast<double>(Converter::Convert<float>(*a)),
        .skewX = static_cast<double>(Converter::Convert<float>(*b)),
        .skewY = static_cast<double>(Converter::Convert<float>(*c)),
        .scaleY = static_cast<double>(Converter::Convert<float>(*d)),
        .translateX = static_cast<double>(Converter::Convert<float>(*e)),
        .translateY = static_cast<double>(Converter::Convert<float>(*f)) };
    peerImpl->SetTransform(param);
}
void SetTransform1Impl(Ark_CanvasRenderer peer,
                       const Opt_Matrix2D* transform)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl && transform);
    auto optMatrix = Converter::OptConvert<Ark_Matrix2D>(*transform);
    peerImpl->SetTransform(optMatrix);
}
void TransformImpl(Ark_CanvasRenderer peer,
                   const Ark_Number* a,
                   const Ark_Number* b,
                   const Ark_Number* c,
                   const Ark_Number* d,
                   const Ark_Number* e,
                   const Ark_Number* f)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(a);
    CHECK_NULL_VOID(b);
    CHECK_NULL_VOID(c);
    CHECK_NULL_VOID(d);
    CHECK_NULL_VOID(e);
    CHECK_NULL_VOID(f);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    auto param = TransformParam {
        .scaleX = static_cast<double>(Converter::Convert<float>(*a)),
        .skewX = static_cast<double>(Converter::Convert<float>(*b)),
        .skewY = static_cast<double>(Converter::Convert<float>(*c)),
        .scaleY = static_cast<double>(Converter::Convert<float>(*d)),
        .translateX = static_cast<double>(Converter::Convert<float>(*e)),
        .translateY = static_cast<double>(Converter::Convert<float>(*f)) };
    peerImpl->Transform(param);
}
void TranslateImpl(Ark_CanvasRenderer peer,
                   const Ark_Number* x,
                   const Ark_Number* y)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(x);
    CHECK_NULL_VOID(y);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    auto transX = static_cast<double>(Converter::Convert<float>(*x));
    auto transY = static_cast<double>(Converter::Convert<float>(*y));
    peerImpl->Translate(transX, transY);
}
void SetPixelMapImpl(Ark_CanvasRenderer peer,
                     const Opt_PixelMap* value)
{
#ifdef PIXEL_MAP_SUPPORTED
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(value);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    auto opt = Converter::OptConvert<Ark_PixelMap>(*value);
    CHECK_NULL_VOID(opt);
    auto pixelMapPeer = opt.value();
    CHECK_NULL_VOID(pixelMapPeer);
    peerImpl->SetPixelMap(pixelMapPeer->pixelMap);
#else
    LOGE("ARKOALA CanvasRendererAccessor::SetPixelMapImpl function 'setPixelMap'"
         " is not supported on the current platform.");
#endif
}
void TransferFromImageBitmapImpl(Ark_CanvasRenderer peer,
                                 Ark_ImageBitmap bitmap)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    peerImpl->TransferFromImageBitmap(bitmap);
}
void SaveLayerImpl(Ark_CanvasRenderer peer)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    peerImpl->SaveLayer();
}
void RestoreLayerImpl(Ark_CanvasRenderer peer)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    peerImpl->RestoreLayer();
}
void ResetImpl(Ark_CanvasRenderer peer)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    peerImpl->Reset();
}
Ark_Union_LengthMetrics_String GetLetterSpacingImpl(Ark_CanvasRenderer peer)
{
    return {};
}
void SetLetterSpacingImpl(Ark_CanvasRenderer peer,
                          const Ark_Union_LengthMetrics_String* letterSpacing)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    CHECK_NULL_VOID(letterSpacing);
    Converter::VisitUnion(
        *letterSpacing,
        [peerImpl](const Ark_String& str) {
            auto spacing = Converter::Convert<std::string>(str);
            peerImpl->SetLetterSpacing(spacing);
        },
        [peerImpl](const Ark_LengthMetrics& metrics) {
            Dimension spacing = Converter::OptConvert<Dimension>(metrics).value_or(Dimension());
            peerImpl->SetLetterSpacing(spacing);
        },
        []() {});
}
Ark_Number GetGlobalAlphaImpl(Ark_CanvasRenderer peer)
{
    LOGE("ARKOALA CanvasRendererAccessor::GetGlobalAlphaImpl there is no implementation in controller "
        "for getter method of GlobalAlpha.");
    return {};
}
void SetGlobalAlphaImpl(Ark_CanvasRenderer peer,
                        const Ark_Number* globalAlpha)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(globalAlpha);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);

    auto alpha = static_cast<double>(Converter::Convert<float>(*globalAlpha));
    peerImpl->SetGlobalAlpha(alpha);
}
Ark_String GetGlobalCompositeOperationImpl(Ark_CanvasRenderer peer)
{
    LOGE("ARKOALA CanvasRendererAccessor::GetGlobalCompositeOperationImpl method should return "
        "object with specific type");
    return {};
}
void SetGlobalCompositeOperationImpl(Ark_CanvasRenderer peer,
                                     const Ark_String* globalCompositeOperation)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(globalCompositeOperation);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    auto compositeStr = Converter::Convert<std::string>(*globalCompositeOperation);
    peerImpl->SetGlobalCompositeOperation(compositeStr);
}
Ark_Union_String_Number_CanvasGradient_CanvasPattern GetFillStyleImpl(Ark_CanvasRenderer peer)
{
    LOGE("ARKOALA CanvasRendererAccessor::GetFillStyleImpl there is no implementation in controller "
        "for getter method of FillStyle.");
    return {};
}
void SetFillStyleImpl(Ark_CanvasRenderer peer,
                      const Ark_Union_String_Number_CanvasGradient_CanvasPattern* fillStyle)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    CHECK_NULL_VOID(fillStyle);
    Converter::VisitUnion(
        *fillStyle,
        [peerImpl](const Ark_String& style) {
            auto colorStr = Converter::Convert<std::string>(style);
            peerImpl->SetFillStyle(colorStr);
        },
        [peerImpl](const Ark_Number& style) {
            auto colorNum = Converter::Convert<uint32_t>(style);
            peerImpl->SetFillStyle(colorNum);
        },
        [peerImpl](const Ark_CanvasGradient& gradient) {
            CHECK_NULL_VOID(gradient);
            peerImpl->SetFillStyle(gradient->GetGradient());
        },
        [peerImpl](const Ark_CanvasPattern& pattern) {
            CHECK_NULL_VOID(pattern);
            peerImpl->SetFillStyle(pattern->GetId());
        },
        []() {});
}
Ark_Union_String_Number_CanvasGradient_CanvasPattern GetStrokeStyleImpl(Ark_CanvasRenderer peer)
{
    LOGE("ARKOALA CanvasRendererAccessor::GetStrokeStyleImpl there is no implementation in controller "
        "for getter method of StrokeStyle.");
    return {};
}
void SetStrokeStyleImpl(Ark_CanvasRenderer peer,
                        const Ark_Union_String_Number_CanvasGradient_CanvasPattern* strokeStyle)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    CHECK_NULL_VOID(strokeStyle);
    Converter::VisitUnion(
        *strokeStyle,
        [peerImpl](const Ark_String& style) {
            auto colorStr = Converter::Convert<std::string>(style);
            peerImpl->SetStrokeStyle(colorStr);
        },
        [peerImpl](const Ark_Number& style) {
            auto colorNum = Converter::Convert<uint32_t>(style);
            peerImpl->SetStrokeStyle(colorNum);
        },
        [peerImpl](const Ark_CanvasGradient& gradient) {
            CHECK_NULL_VOID(gradient);
            peerImpl->SetStrokeStyle(gradient->GetGradient());
        },
        [peerImpl](const Ark_CanvasPattern& pattern) {
            CHECK_NULL_VOID(pattern);
            peerImpl->SetStrokeStyle(pattern->GetId());
        },
        []() {});
}
Ark_String GetFilterImpl(Ark_CanvasRenderer peer)
{
    LOGE("ARKOALA CanvasRendererAccessor::GetFilterImpl method should return object with specific type");
    return {};
}
void SetFilterImpl(Ark_CanvasRenderer peer,
                   const Ark_String* filter)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(filter);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);

    auto filterStr = Converter::Convert<std::string>(*filter);
    peerImpl->SetFilter(filterStr);
}
Ark_Boolean GetImageSmoothingEnabledImpl(Ark_CanvasRenderer peer)
{
    LOGE("ARKOALA CanvasRendererAccessor::GetImageSmoothingEnabledImpl there is no implementation in controller "
        "for getter method of ImageSmoothingEnabled.");
    return {};
}
void SetImageSmoothingEnabledImpl(Ark_CanvasRenderer peer,
                                  Ark_Boolean imageSmoothingEnabled)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);

    auto enabled = Converter::Convert<bool>(imageSmoothingEnabled);
    peerImpl->SetImageSmoothingEnabled(enabled);
}
Ark_String GetImageSmoothingQualityImpl(Ark_CanvasRenderer peer)
{
    LOGE("ARKOALA CanvasRendererAccessor::GetImageSmoothingQualityImpl return type Ark_NativePointer "
        "should be replaced with a valid ark enum for ImageSmoothingQuality type.");
    return {};
}
void SetImageSmoothingQualityImpl(Ark_CanvasRenderer peer,
                                  const Ark_String* imageSmoothingQuality)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(imageSmoothingQuality);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    auto quality = Converter::Convert<std::string>(*imageSmoothingQuality);
    peerImpl->SetImageSmoothingQuality(quality);
}
Ark_String GetLineCapImpl(Ark_CanvasRenderer peer)
{
    LOGE("ARKOALA CanvasRendererAccessor::GetLineCapImpl there is no implementation in controller "
        "for getter method of LineCap.");
    return {};
}
void SetLineCapImpl(Ark_CanvasRenderer peer,
                    const Ark_String* lineCap)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(lineCap);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    auto capStr = Converter::Convert<std::string>(*lineCap);
    peerImpl->SetLineCap(capStr);
}
Ark_Number GetLineDashOffsetImpl(Ark_CanvasRenderer peer)
{
    LOGE("ARKOALA CanvasRendererAccessor::GetLineDashOffsetImpl there is no implementation in controller "
        "for getter method of LinewDashOffset.");
    return {};
}
void SetLineDashOffsetImpl(Ark_CanvasRenderer peer,
                           const Ark_Number* lineDashOffset)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(lineDashOffset);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    auto offset = static_cast<double>(Converter::Convert<float>(*lineDashOffset));
    peerImpl->SetLineDashOffset(offset);
}
Ark_String GetLineJoinImpl(Ark_CanvasRenderer peer)
{
    LOGE("ARKOALA CanvasRendererAccessor::GetLineJoinImpl there is no implementation in controller "
        "for getter method of LineJoin.");
    return {};
}
void SetLineJoinImpl(Ark_CanvasRenderer peer,
                     const Ark_String* lineJoin)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(lineJoin);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    auto joinStr = Converter::Convert<std::string>(*lineJoin);
    peerImpl->SetLineJoin(joinStr);
}
Ark_Number GetLineWidthImpl(Ark_CanvasRenderer peer)
{
    LOGE("ARKOALA CanvasRendererAccessor::GetLineWidthImpl there is no implementation in controller "
        "for getter method of LinewWidth.");
    return {};
}
void SetLineWidthImpl(Ark_CanvasRenderer peer,
                      const Ark_Number* lineWidth)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(lineWidth);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    auto width = static_cast<double>(Converter::Convert<float>(*lineWidth));
    peerImpl->SetLineWidth(width);
}
Ark_Number GetMiterLimitImpl(Ark_CanvasRenderer peer)
{
    LOGE("ARKOALA CanvasRendererAccessor::GetMiterLimitImpl there is no implementation in controller "
        "for getter method of MiterLimit.");
    return {};
}
void SetMiterLimitImpl(Ark_CanvasRenderer peer,
                       const Ark_Number* miterLimit)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(miterLimit);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);

    auto limit = static_cast<double>(Converter::Convert<float>(*miterLimit));
    peerImpl->SetMiterLimit(limit);
}
Ark_Number GetShadowBlurImpl(Ark_CanvasRenderer peer)
{
    LOGE("ARKOALA CanvasRendererAccessor::GetShadowBlurImpl there is no implementation in controller "
        "for getter method of ShadowBlur.");
    return {};
}
void SetShadowBlurImpl(Ark_CanvasRenderer peer,
                       const Ark_Number* shadowBlur)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(shadowBlur);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);

    auto blur = static_cast<double>(Converter::Convert<float>(*shadowBlur));
    peerImpl->SetShadowBlur(blur);
}
Ark_String GetShadowColorImpl(Ark_CanvasRenderer peer)
{
    LOGE("ARKOALA CanvasRendererAccessor::GetShadowColorImpl there is no implementation in controller "
        "for getter method of ShadowColor.");
    return {};
}
void SetShadowColorImpl(Ark_CanvasRenderer peer,
                        const Ark_String* shadowColor)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(shadowColor);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);

    auto colorStr = Converter::Convert<std::string>(*shadowColor);
    peerImpl->SetShadowColor(colorStr);
}
Ark_Number GetShadowOffsetXImpl(Ark_CanvasRenderer peer)
{
    LOGE("ARKOALA CanvasRendererAccessor::GetShadowOffsetXImpl there is no implementation in controller "
        "for getter method of ShadowOffsetXImpl.");
    return {};
}
void SetShadowOffsetXImpl(Ark_CanvasRenderer peer,
                          const Ark_Number* shadowOffsetX)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(shadowOffsetX);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    auto offsetX = static_cast<double>(Converter::Convert<float>(*shadowOffsetX));
    peerImpl->SetShadowOffsetX(offsetX);
}
Ark_Number GetShadowOffsetYImpl(Ark_CanvasRenderer peer)
{
    LOGE("ARKOALA CanvasRendererAccessor::GetShadowOffsetYImpl there is no implementation in controller "
        "for getter method of ShadowOffsetYImpl.");
    return {};
}
void SetShadowOffsetYImpl(Ark_CanvasRenderer peer,
                          const Ark_Number* shadowOffsetY)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(shadowOffsetY);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    auto offsetY = static_cast<double>(Converter::Convert<float>(*shadowOffsetY));
    peerImpl->SetShadowOffsetY(offsetY);
}
Ark_String GetDirectionImpl(Ark_CanvasRenderer peer)
{
    LOGE("ARKOALA CanvasRendererAccessor::GetDirectionImpl there is no implementation in controller "
        "for getter method of Direction.");
    return {};
}
void SetDirectionImpl(Ark_CanvasRenderer peer,
                      const Ark_String* direction)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(direction);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    auto directionStr = Converter::Convert<std::string>(*direction);
    peerImpl->SetTextDirection(directionStr);
}
Ark_String GetFontImpl(Ark_CanvasRenderer peer)
{
    LOGE("ARKOALA CanvasRendererAccessor::GetFontImpl there is no implementation in controller "
        "for getter method of Font.");
    return {};
}
void SetFontImpl(Ark_CanvasRenderer peer,
                 const Ark_String* font)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(font);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    auto fontStr = Converter::Convert<std::string>(*font);
    peerImpl->SetFont(fontStr);
}
Ark_String GetTextAlignImpl(Ark_CanvasRenderer peer)
{
    LOGE("ARKOALA CanvasRendererAccessor::GetTextAlignImpl there is no implementation in controller "
        "for getter method of TextAlign.");
    return {};
}
void SetTextAlignImpl(Ark_CanvasRenderer peer,
                      const Ark_String* textAlign)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(textAlign);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    auto alignStr = Converter::Convert<std::string>(*textAlign);
    peerImpl->SetTextAlign(alignStr);
}
Ark_String GetTextBaselineImpl(Ark_CanvasRenderer peer)
{
    LOGE("ARKOALA CanvasRendererAccessor::GetTextBaselineImpl there is no implementation in controller "
        "for getter method of TextBaseline.");
    return {};
}
void SetTextBaselineImpl(Ark_CanvasRenderer peer,
                         const Ark_String* textBaseline)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(textBaseline);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    auto baseLineStr = Converter::Convert<std::string>(*textBaseline);
    peerImpl->SetTextBaseline(baseLineStr);
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
        CanvasRendererAccessor::GetLetterSpacingImpl,
        CanvasRendererAccessor::SetLetterSpacingImpl,
        CanvasRendererAccessor::GetGlobalAlphaImpl,
        CanvasRendererAccessor::SetGlobalAlphaImpl,
        CanvasRendererAccessor::GetGlobalCompositeOperationImpl,
        CanvasRendererAccessor::SetGlobalCompositeOperationImpl,
        CanvasRendererAccessor::GetFillStyleImpl,
        CanvasRendererAccessor::SetFillStyleImpl,
        CanvasRendererAccessor::GetStrokeStyleImpl,
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
