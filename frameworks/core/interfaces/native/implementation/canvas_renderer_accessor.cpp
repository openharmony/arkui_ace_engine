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
const GENERATED_ArkUIMatrix2DAccessor* GetMatrix2DAccessor();

namespace CanvasRendererAccessor {
void DestroyPeerImpl(Ark_CanvasRenderer peer)
{
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    if (peerImpl) {
        peerImpl->DecRefCount();
    }
}
Ark_CanvasRenderer ConstructImpl()
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
                    Ark_Float64 dx,
                    Ark_Float64 dy)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    CHECK_NULL_VOID(image);
    CanvasRendererPeerImpl::DrawImageParam params = {
        .dx = Converter::Convert<double>(dx),
        .dy = Converter::Convert<double>(dy),
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
        [&params, peerImpl](const Ark_image_PixelMap& pixelMap) {
            CHECK_NULL_VOID(pixelMap);
            peerImpl->DrawPixelMap(pixelMap, params);
        },
        []() {});
}
void DrawImage1Impl(Ark_CanvasRenderer peer,
                    const Ark_Union_ImageBitmap_PixelMap* image,
                    Ark_Float64 dx,
                    Ark_Float64 dy,
                    Ark_Float64 dw,
                    Ark_Float64 dh)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    CHECK_NULL_VOID(image);
    CanvasRendererPeerImpl::DrawImageParam params = {
        .dx = Converter::Convert<double>(dx),
        .dy = Converter::Convert<double>(dy),
        .dWidth = Converter::Convert<double>(dw),
        .dHeight = Converter::Convert<double>(dh),
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
        [&params, peerImpl](const Ark_image_PixelMap& pixelMap) {
            CHECK_NULL_VOID(pixelMap);
            peerImpl->DrawPixelMap(pixelMap, params);
        },
        []() {});
}
void DrawImage2Impl(Ark_CanvasRenderer peer,
                    const Ark_Union_ImageBitmap_PixelMap* image,
                    Ark_Float64 sx,
                    Ark_Float64 sy,
                    Ark_Float64 sw,
                    Ark_Float64 sh,
                    Ark_Float64 dx,
                    Ark_Float64 dy,
                    Ark_Float64 dw,
                    Ark_Float64 dh)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    CHECK_NULL_VOID(image);
    CanvasRendererPeerImpl::DrawImageParam params = {
        .sx = Converter::Convert<double>(sx),
        .sy = Converter::Convert<double>(sy),
        .sWidth = Converter::Convert<double>(sw),
        .sHeight = Converter::Convert<double>(sh),
        .dx = Converter::Convert<double>(dx),
        .dy = Converter::Convert<double>(dy),
        .dWidth = Converter::Convert<double>(dw),
        .dHeight = Converter::Convert<double>(dh),
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
        [&params, peerImpl](const Ark_image_PixelMap& pixelMap) {
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
    auto ruleStr = Converter::OptConvertPtr<std::string>(fillRule);
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
    auto pathImpl = reinterpret_cast<CanvasPathPeerImpl*>(path);
    CHECK_NULL_VOID(pathImpl);
    auto ruleStr = Converter::OptConvertPtr<std::string>(fillRule);
    peerImpl->Clip(ruleStr, pathImpl->GetCanvasPath2d());
}
void Fill0Impl(Ark_CanvasRenderer peer,
               const Opt_String* fillRule)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    auto ruleStr = Converter::OptConvertPtr<std::string>(fillRule);
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
    auto pathImpl = reinterpret_cast<CanvasPathPeerImpl*>(path);
    CHECK_NULL_VOID(pathImpl);
    auto ruleStr = Converter::OptConvertPtr<std::string>(fillRule);
    peerImpl->Fill(ruleStr, pathImpl->GetCanvasPath2d());
}
void StrokeImpl(Ark_CanvasRenderer peer,
                const Opt_Path2D* path)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    auto optPath = Converter::GetOptPtr(path);
    RefPtr<CanvasPath2D> arg;
    if (optPath && optPath.value()) {
        auto pathImpl = reinterpret_cast<CanvasPathPeerImpl*>(optPath.value());
        arg = pathImpl->GetCanvasPath2d();
    }
    peerImpl->Stroke(arg);
}
Ark_CanvasGradient CreateLinearGradientImpl(Ark_CanvasRenderer peer,
                                            Ark_Float64 x0,
                                            Ark_Float64 y0,
                                            Ark_Float64 x1,
                                            Ark_Float64 y1)
{
    CHECK_NULL_RETURN(peer, {});
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    double cx0 = Converter::Convert<double>(x0);
    double cy0 = Converter::Convert<double>(y0);
    double cx1 = Converter::Convert<double>(x1);
    double cy1 = Converter::Convert<double>(y1);
    auto gradient = peerImpl->CreateLinearGradient(cx0, cy0, cx1, cy1);
    CHECK_NULL_RETURN(gradient, {});
    auto canvasGradientPeer = GetCanvasGradientAccessor()->construct();
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
    auto repeat = Converter::OptConvertPtr<std::string>(repetition);
    auto pattern = GetCanvasPatternAccessor()->construct();
    peerImpl->CreatePattern(image, pattern, repeat);
    return Converter::ArkValue<Opt_CanvasPattern>(pattern);
}
Ark_CanvasGradient CreateRadialGradientImpl(Ark_CanvasRenderer peer,
                                            Ark_Float64 x0,
                                            Ark_Float64 y0,
                                            Ark_Float64 r0,
                                            Ark_Float64 x1,
                                            Ark_Float64 y1,
                                            Ark_Float64 r1)
{
    CHECK_NULL_RETURN(peer, {});
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CanvasRendererPeerImpl::RadialGradientParam params = {
        .x0 = Converter::Convert<double>(x0),
        .y0 = Converter::Convert<double>(y0),
        .r0 = Converter::Convert<double>(r0),
        .x1 = Converter::Convert<double>(x1),
        .y1 = Converter::Convert<double>(y1),
        .r1 = Converter::Convert<double>(r1),
    };
    auto gradient = peerImpl->CreateRadialGradient(params);
    CHECK_NULL_RETURN(gradient, {});
    auto canvasGradientPeer = GetCanvasGradientAccessor()->construct();
    CHECK_NULL_RETURN(canvasGradientPeer, {});
    canvasGradientPeer->SetGradient(gradient);
    return canvasGradientPeer;
}
Ark_CanvasGradient CreateConicGradientImpl(Ark_CanvasRenderer peer,
                                           Ark_Float64 startAngle,
                                           Ark_Float64 x,
                                           Ark_Float64 y)
{
    CHECK_NULL_RETURN(peer, {});
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    double ca = Converter::Convert<double>(startAngle);
    double cx = Converter::Convert<double>(x);
    double cy = Converter::Convert<double>(y);
    auto gradient = peerImpl->CreateConicGradient(cx, cy, ca);
    CHECK_NULL_RETURN(gradient, {});
    auto canvasGradientPeer = GetCanvasGradientAccessor()->construct();
    CHECK_NULL_RETURN(canvasGradientPeer, {});
    canvasGradientPeer->SetGradient(gradient);
    return canvasGradientPeer;
}
Ark_image_PixelMap GetPixelMapImpl(Ark_CanvasRenderer peer,
                                   Ark_Float64 sx,
                                   Ark_Float64 sy,
                                   Ark_Float64 sw,
                                   Ark_Float64 sh)
{
    CHECK_NULL_RETURN(peer, {});
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, {});
    auto x = Converter::Convert<double>(sx);
    auto y = Converter::Convert<double>(sy);
    auto width = Converter::Convert<double>(sw);
    auto height = Converter::Convert<double>(sh);
    auto pixelMap = peerImpl->GetPixelMap(x, y, width, height);
    CHECK_NULL_RETURN(pixelMap, {});
    auto pixelMapPeer = PeerUtils::CreatePeer<image_PixelMapPeer>();
    CHECK_NULL_RETURN(pixelMapPeer, {});
    pixelMapPeer->pixelMap = pixelMap;
    return pixelMapPeer;
}
Array_Float64 GetLineDashImpl(Ark_CanvasRenderer peer)
{
    CHECK_NULL_RETURN(peer, {});
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, {});
    auto lineDash = peerImpl->GetLineDash();
    return Converter::ArkValue<Array_Float64>(lineDash, Converter::FC);
}
void SetLineDashImpl(Ark_CanvasRenderer peer,
                     const Array_Float64* segments)
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
                   Ark_Float64 x,
                   Ark_Float64 y,
                   Ark_Float64 w,
                   Ark_Float64 h)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    auto cx = Converter::Convert<double>(x);
    auto cy = Converter::Convert<double>(y);
    auto cw = Converter::Convert<double>(w);
    auto ch = Converter::Convert<double>(h);
    peerImpl->ClearRect(cx, cy, cw, ch);
}
void FillRectImpl(Ark_CanvasRenderer peer,
                  Ark_Float64 x,
                  Ark_Float64 y,
                  Ark_Float64 w,
                  Ark_Float64 h)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    auto cx = Converter::Convert<double>(x);
    auto cy = Converter::Convert<double>(y);
    auto cw = Converter::Convert<double>(w);
    auto ch = Converter::Convert<double>(h);
    peerImpl->FillRect(cx, cy, cw, ch);
}
void StrokeRectImpl(Ark_CanvasRenderer peer,
                    Ark_Float64 x,
                    Ark_Float64 y,
                    Ark_Float64 w,
                    Ark_Float64 h)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    auto cx = Converter::Convert<double>(x);
    auto cy = Converter::Convert<double>(y);
    auto cw = Converter::Convert<double>(w);
    auto ch = Converter::Convert<double>(h);
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
                  Ark_Float64 x,
                  Ark_Float64 y,
                  const Opt_Float64* maxWidth)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(text);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    auto valueText = Converter::Convert<std::string>(*text);
    auto valueX = Converter::Convert<double>(x);
    auto valueY = Converter::Convert<double>(y);
    auto optMaxWidth = Converter::OptConvertPtr<float>(maxWidth);
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
                    Ark_Float64 x,
                    Ark_Float64 y,
                    const Opt_Float64* maxWidth)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(text);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    auto valueText = Converter::Convert<std::string>(*text);
    auto valueX = Converter::Convert<double>(x);
    auto valueY = Converter::Convert<double>(y);
    auto optMaxWidth = Converter::OptConvertPtr<float>(maxWidth);
    peerImpl->StrokeText(valueText, valueX, valueY, optMaxWidth);
}
Ark_Matrix2D GetTransformImpl(Ark_CanvasRenderer peer)
{
    CHECK_NULL_RETURN(peer, {});
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, {});
    auto matrixPeer = PeerUtils::CreatePeer<Matrix2DPeer>();
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
                Ark_Float64 angle)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    auto rotateAngle = Converter::Convert<double>(angle);
    peerImpl->Rotate(rotateAngle);
}
void ScaleImpl(Ark_CanvasRenderer peer,
               Ark_Float64 x,
               Ark_Float64 y)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);

    auto scaleX = Converter::Convert<double>(x);
    auto scaleY = Converter::Convert<double>(y);
    peerImpl->Scale(scaleX, scaleY);
}
void SetTransform0Impl(Ark_CanvasRenderer peer,
                       Ark_Float64 a,
                       Ark_Float64 b,
                       Ark_Float64 c,
                       Ark_Float64 d,
                       Ark_Float64 e,
                       Ark_Float64 f)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    auto param = TransformParam {
        .scaleX = Converter::Convert<double>(a),
        .skewX = Converter::Convert<double>(c),
        .skewY = Converter::Convert<double>(b),
        .scaleY = Converter::Convert<double>(d),
        .translateX = Converter::Convert<double>(e),
        .translateY = Converter::Convert<double>(f) };
    peerImpl->SetTransform(param);
}
void SetTransform1Impl(Ark_CanvasRenderer peer,
                       const Opt_Matrix2D* transform)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    auto optMatrix = Converter::OptConvertPtr<Ark_Matrix2D>(transform);
    peerImpl->SetTransform(optMatrix);
}
void TransformImpl(Ark_CanvasRenderer peer,
                   Ark_Float64 a,
                   Ark_Float64 b,
                   Ark_Float64 c,
                   Ark_Float64 d,
                   Ark_Float64 e,
                   Ark_Float64 f)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    auto param = TransformParam {
        .scaleX = Converter::Convert<double>(a),
        .skewX = Converter::Convert<double>(b),
        .skewY = Converter::Convert<double>(c),
        .scaleY = Converter::Convert<double>(d),
        .translateX = Converter::Convert<double>(e),
        .translateY = Converter::Convert<double>(f) };
    peerImpl->Transform(param);
}
void TranslateImpl(Ark_CanvasRenderer peer,
                   Ark_Float64 x,
                   Ark_Float64 y)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    auto transX = Converter::Convert<double>(x);
    auto transY = Converter::Convert<double>(y);
    peerImpl->Translate(transX, transY);
}
void SetPixelMapImpl(Ark_CanvasRenderer peer,
                     const Opt_image_PixelMap* value)
{
#ifdef PIXEL_MAP_SUPPORTED
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    auto opt = Converter::OptConvertPtr<Ark_image_PixelMap>(value);
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
    auto defaultValue = Converter::ArkUnion<Ark_Union_LengthMetrics_String, Ark_LengthMetrics>(
        Converter::ArkValue<Ark_LengthMetrics>(0.0_vp));
    CHECK_NULL_RETURN(peer, defaultValue);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, defaultValue);
    return Converter::ArkUnion<Ark_Union_LengthMetrics_String, Ark_LengthMetrics>(
        Converter::ArkValue<Ark_LengthMetrics>(peerImpl->GetLetterSpacing()));
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
Ark_Float64 GetGlobalAlphaImpl(Ark_CanvasRenderer peer)
{
    auto defaultValue = Converter::ArkValue<Ark_Float64>(1.0);
    CHECK_NULL_RETURN(peer, defaultValue);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, defaultValue);
    return Converter::ArkValue<Ark_Float64>(peerImpl->GetGlobalAlpha());
}
void SetGlobalAlphaImpl(Ark_CanvasRenderer peer,
                        Ark_Float64 globalAlpha)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);

    auto alpha = Converter::Convert<double>(globalAlpha);
    peerImpl->SetGlobalAlpha(alpha);
}
Ark_String GetGlobalCompositeOperationImpl(Ark_CanvasRenderer peer)
{
    auto defaultValue = Converter::ArkValue<Ark_String>("source-over");
    CHECK_NULL_RETURN(peer, defaultValue);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, defaultValue);
    return Converter::ArkValue<Ark_String>(peerImpl->GetGlobalCompositeOperation());
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
Ark_Union_String_Color_I32_CanvasGradient_CanvasPattern GetFillStyleImpl(Ark_CanvasRenderer peer)
{
    auto defaultValue = Converter::ArkUnion<Ark_Union_String_Color_I32_CanvasGradient_CanvasPattern, Ark_String>(
        Converter::ArkValue<Ark_String>("#000000"));
    CHECK_NULL_RETURN(peer, defaultValue);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, defaultValue);
    auto type = peerImpl->GetFillStyleType();
    switch (type) {
        case ParamType::STRING:
        case ParamType::COLOR:
        case ParamType::INT32:
            return Converter::ArkUnion<Ark_Union_String_Color_I32_CanvasGradient_CanvasPattern, Ark_String>(
                Converter::ArkValue<Ark_String>(peerImpl->GetFillStyleString()));
        case ParamType::CANVAS_GRADIENT:
            return Converter::ArkUnion<Ark_Union_String_Color_I32_CanvasGradient_CanvasPattern, Ark_CanvasGradient>(
                peerImpl->GetFillStyleGradient());
        case ParamType::CANVAS_PATTERN:
            return Converter::ArkUnion<Ark_Union_String_Color_I32_CanvasGradient_CanvasPattern, Ark_CanvasPattern>(
                peerImpl->GetFillStylePattern());
        default:
            return defaultValue;
    }
}
void SetFillStyleImpl(Ark_CanvasRenderer peer,
                      const Ark_Union_String_Color_I32_CanvasGradient_CanvasPattern* fillStyle)
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
        [peerImpl](const Ark_Color& style) {
            auto color = Converter::OptConvert<Color>(style);
            peerImpl->SetFillStyle(color);
        },
        [peerImpl](const Ark_Int32& style) {
            auto colorNum = Converter::Convert<int32_t>(style);
            if (colorNum >= 0) {
                peerImpl->SetFillStyle(static_cast<uint32_t>(colorNum));
            }
        },
        [peerImpl](const Ark_CanvasGradient& gradient) {
            peerImpl->SetFillStyle(gradient);
        },
        [peerImpl](const Ark_CanvasPattern& pattern) {
            peerImpl->SetFillStyle(pattern);
        },
        []() {});
}
Ark_Union_String_Color_I32_CanvasGradient_CanvasPattern GetStrokeStyleImpl(Ark_CanvasRenderer peer)
{
    auto defaultValue = Converter::ArkUnion<Ark_Union_String_Color_I32_CanvasGradient_CanvasPattern, Ark_String>(
        Converter::ArkValue<Ark_String>("#000000"));
    CHECK_NULL_RETURN(peer, defaultValue);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, defaultValue);
    auto type = peerImpl->GetStrokeStyleType();
    switch (type) {
        case ParamType::STRING:
        case ParamType::COLOR:
        case ParamType::INT32:
            return Converter::ArkUnion<Ark_Union_String_Color_I32_CanvasGradient_CanvasPattern, Ark_String>(
                Converter::ArkValue<Ark_String>(peerImpl->GetStrokeStyleString()));
        case ParamType::CANVAS_GRADIENT:
            return Converter::ArkUnion<Ark_Union_String_Color_I32_CanvasGradient_CanvasPattern, Ark_CanvasGradient>(
                peerImpl->GetStrokeStyleGradient());
        case ParamType::CANVAS_PATTERN:
            return Converter::ArkUnion<Ark_Union_String_Color_I32_CanvasGradient_CanvasPattern, Ark_CanvasPattern>(
                peerImpl->GetStrokeStylePattern());
        default:
            return defaultValue;
    }
}
void SetStrokeStyleImpl(Ark_CanvasRenderer peer,
                        const Ark_Union_String_Color_I32_CanvasGradient_CanvasPattern* strokeStyle)
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
        [peerImpl](const Ark_Color& style) {
            auto color = Converter::OptConvert<Color>(style);
            peerImpl->SetStrokeStyle(color);
        },
        [peerImpl](const Ark_Int32& style) {
            auto colorNum = Converter::Convert<int32_t>(style);
            if (colorNum >= 0) {
                peerImpl->SetStrokeStyle(static_cast<uint32_t>(colorNum));
            }
        },
        [peerImpl](const Ark_CanvasGradient& gradient) {
            peerImpl->SetStrokeStyle(gradient);
        },
        [peerImpl](const Ark_CanvasPattern& pattern) {
            peerImpl->SetStrokeStyle(pattern);
        },
        []() {});
}
Ark_String GetFilterImpl(Ark_CanvasRenderer peer)
{
    auto defaultValue = Converter::ArkValue<Ark_String>("none");
    CHECK_NULL_RETURN(peer, defaultValue);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, defaultValue);
    return Converter::ArkValue<Ark_String>(peerImpl->GetFilter());
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
    auto defaultValue = Converter::ArkValue<Ark_Boolean>(false);
    CHECK_NULL_RETURN(peer, defaultValue);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, defaultValue);
    return Converter::ArkValue<Ark_Boolean>(peerImpl->GetImageSmoothingEnabled());
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
    auto defaultValue = Converter::ArkValue<Ark_String>("low");
    CHECK_NULL_RETURN(peer, defaultValue);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, defaultValue);
    return Converter::ArkValue<Ark_String>(peerImpl->GetImageSmoothingQuality());
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
    auto defaultValue = Converter::ArkValue<Ark_String>("butt");
    CHECK_NULL_RETURN(peer, defaultValue);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, defaultValue);
    return Converter::ArkValue<Ark_String>(peerImpl->GetLineCap());
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
Ark_Float64 GetLineDashOffsetImpl(Ark_CanvasRenderer peer)
{
    auto defaultValue = Converter::ArkValue<Ark_Float64>(0.0);
    CHECK_NULL_RETURN(peer, defaultValue);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, defaultValue);
    return Converter::ArkValue<Ark_Float64>(peerImpl->GetLineDashOffset());
}
void SetLineDashOffsetImpl(Ark_CanvasRenderer peer,
                           Ark_Float64 lineDashOffset)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    auto offset = Converter::Convert<double>(lineDashOffset);
    peerImpl->SetLineDashOffset(offset);
}
Ark_String GetLineJoinImpl(Ark_CanvasRenderer peer)
{
    auto defaultValue = Converter::ArkValue<Ark_String>("miter");
    CHECK_NULL_RETURN(peer, defaultValue);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, defaultValue);
    return Converter::ArkValue<Ark_String>(peerImpl->GetLineJoin());
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
Ark_Float64 GetLineWidthImpl(Ark_CanvasRenderer peer)
{
    auto defaultValue = Converter::ArkValue<Ark_Float64>(1.0);
    CHECK_NULL_RETURN(peer, defaultValue);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, defaultValue);
    return Converter::ArkValue<Ark_Float64>(peerImpl->GetLineWidth());
}
void SetLineWidthImpl(Ark_CanvasRenderer peer,
                      Ark_Float64 lineWidth)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    auto width = Converter::Convert<double>(lineWidth);
    peerImpl->SetLineWidth(width);
}
Ark_Float64 GetMiterLimitImpl(Ark_CanvasRenderer peer)
{
    auto defaultValue = Converter::ArkValue<Ark_Float64>(0.0);
    CHECK_NULL_RETURN(peer, defaultValue);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, defaultValue);
    return Converter::ArkValue<Ark_Float64>(peerImpl->GetMiterLimit());
}
void SetMiterLimitImpl(Ark_CanvasRenderer peer,
                       Ark_Float64 miterLimit)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);

    auto limit = Converter::Convert<double>(miterLimit);
    peerImpl->SetMiterLimit(limit);
}
Ark_Float64 GetShadowBlurImpl(Ark_CanvasRenderer peer)
{
    auto defaultValue = Converter::ArkValue<Ark_Float64>(0.0);
    CHECK_NULL_RETURN(peer, defaultValue);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, defaultValue);
    return Converter::ArkValue<Ark_Float64>(peerImpl->GetShadowBlur());
}
void SetShadowBlurImpl(Ark_CanvasRenderer peer,
                       Ark_Float64 shadowBlur)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);

    auto blur = Converter::Convert<double>(shadowBlur);
    peerImpl->SetShadowBlur(blur);
}
Ark_String GetShadowColorImpl(Ark_CanvasRenderer peer)
{
    auto defaultValue = Converter::ArkValue<Ark_String>("#00000000");
    CHECK_NULL_RETURN(peer, defaultValue);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, defaultValue);
    return Converter::ArkValue<Ark_String>(peerImpl->GetShadowColor());
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
Ark_Float64 GetShadowOffsetXImpl(Ark_CanvasRenderer peer)
{
    auto defaultValue = Converter::ArkValue<Ark_Float64>(0.0);
    CHECK_NULL_RETURN(peer, defaultValue);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, defaultValue);
    return Converter::ArkValue<Ark_Float64>(peerImpl->GetShadowOffsetX());
}
void SetShadowOffsetXImpl(Ark_CanvasRenderer peer,
                          Ark_Float64 shadowOffsetX)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    auto offsetX = Converter::Convert<double>(shadowOffsetX);
    peerImpl->SetShadowOffsetX(offsetX);
}
Ark_Float64 GetShadowOffsetYImpl(Ark_CanvasRenderer peer)
{
    auto defaultValue = Converter::ArkValue<Ark_Float64>(0.0);
    CHECK_NULL_RETURN(peer, defaultValue);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, defaultValue);
    return Converter::ArkValue<Ark_Float64>(peerImpl->GetShadowOffsetY());
}
void SetShadowOffsetYImpl(Ark_CanvasRenderer peer,
                          Ark_Float64 shadowOffsetY)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    auto offsetY = Converter::Convert<double>(shadowOffsetY);
    peerImpl->SetShadowOffsetY(offsetY);
}
Ark_String GetDirectionImpl(Ark_CanvasRenderer peer)
{
    auto defaultValue = Converter::ArkValue<Ark_String>("inherit");
    CHECK_NULL_RETURN(peer, defaultValue);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, defaultValue);
    return Converter::ArkValue<Ark_String>(peerImpl->GetDirection());
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
    auto defaultValue = Converter::ArkValue<Ark_String>("normal normal 14px sans-serif");
    CHECK_NULL_RETURN(peer, defaultValue);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, defaultValue);
    return Converter::ArkValue<Ark_String>(peerImpl->GetFont());
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
    auto defaultValue = Converter::ArkValue<Ark_String>("left");
    CHECK_NULL_RETURN(peer, defaultValue);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, defaultValue);
    return Converter::ArkValue<Ark_String>(peerImpl->GetTextAlign());
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
    auto defaultValue = Converter::ArkValue<Ark_String>("alphabetic");
    CHECK_NULL_RETURN(peer, defaultValue);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, defaultValue);
    return Converter::ArkValue<Ark_String>(peerImpl->GetTextBaseline());
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
        CanvasRendererAccessor::ConstructImpl,
        CanvasRendererAccessor::GetFinalizerImpl,
        CanvasRendererAccessor::DrawImage0Impl,
        CanvasRendererAccessor::DrawImage1Impl,
        CanvasRendererAccessor::DrawImage2Impl,
        CanvasRendererAccessor::BeginPathImpl,
        CanvasRendererAccessor::Clip0Impl,
        CanvasRendererAccessor::Clip1Impl,
        CanvasRendererAccessor::Fill0Impl,
        CanvasRendererAccessor::Fill1Impl,
        CanvasRendererAccessor::StrokeImpl,
        CanvasRendererAccessor::CreateLinearGradientImpl,
        CanvasRendererAccessor::CreatePatternImpl,
        CanvasRendererAccessor::CreateRadialGradientImpl,
        CanvasRendererAccessor::CreateConicGradientImpl,
        CanvasRendererAccessor::GetPixelMapImpl,
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
