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
#include "core/interfaces/arkoala/utility/reverse_converter.h"
#include "canvas_renderer_peer_impl.h"

namespace OHOS::Ace::NG {
namespace {
const auto ALPHA_LIMIT_MIN = 0.0;
const auto ALPHA_LIMIT_MAX = 1.0;
const auto SIZE_LIMIT_MIN = 0.0;
const auto SEGMENT_LIMIT_MIN = 0.0;
const auto SCALE_LIMIT_MIN = 0.0;
struct Ark_Custom_Rect {
    Ark_Number x;
    Ark_Number y;
    Ark_Number w;
    Ark_Number h;
};
const std::unordered_map<std::string, CompositeOperation> COMPOSITE_TABLE = {
    { "SOURCE_OVER", CompositeOperation::SOURCE_OVER },
    { "SOURCE_ATOP", CompositeOperation::SOURCE_ATOP },
    { "SOURCE_IN", CompositeOperation::SOURCE_IN },
    { "SOURCE_OUT", CompositeOperation::SOURCE_OUT },
    { "DESTINATION_OVER", CompositeOperation::DESTINATION_OVER },
    { "DESTINATION_ATOP", CompositeOperation::DESTINATION_ATOP },
    { "DESTINATION_IN", CompositeOperation::DESTINATION_IN },
    { "DESTINATION_OUT", CompositeOperation::DESTINATION_OUT },
    { "LIGHTER", CompositeOperation::LIGHTER },
    { "COPY", CompositeOperation::COPY },
    { "XOR", CompositeOperation::XOR }
};
} // namespace
namespace Converter {
template<>
void AssignCast(std::optional<CompositeOperation>& dst, const Ark_String& src)
{
    auto str = Converter::Convert<std::string>(src);
    str = StringUtils::TrimStr(str);
    StringUtils::TransformStrCase(str, StringUtils::TEXT_CASE_UPPERCASE);
    auto item = COMPOSITE_TABLE.find(str);
    if (item != COMPOSITE_TABLE.end()) {
        dst = item->second;
    } else {
        LOGE("Unexpected enum value in Ark_String: %{public}s", str.c_str());
    }
}

template<>
Rect Convert(const Ark_Custom_Rect& src)
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
namespace CanvasRendererAccessor {
static void DestroyPeer(CanvasRendererPeerImpl* peerImpl)
{
    if (peerImpl) {
        peerImpl->DecRefCount();
    }
}
CanvasRendererPeer* CtorImpl()
{
    auto peerImpl = Referenced::MakeRefPtr<CanvasRendererPeerImpl>();
    peerImpl->IncRefCount();
    return reinterpret_cast<CanvasRendererPeer*>(Referenced::RawPtr(peerImpl));
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void*>(&DestroyPeer);
}
void DrawImage0Impl(CanvasRendererPeer* peer,
                    const Ark_Union_ImageBitmap_PixelMap* image,
                    const Ark_Number* dx,
                    const Ark_Number* dy)
{
    LOGE("ARKOALA CanvasRendererAccessor::DrawImage0Impl where Ark_Union_ImageBitmap_PixelMap "
        " includes Opt_CustomObject which is not implemented.");
}
void DrawImage1Impl(CanvasRendererPeer* peer,
                    const Ark_Union_ImageBitmap_PixelMap* image,
                    const Ark_Number* dx,
                    const Ark_Number* dy,
                    const Ark_Number* dw,
                    const Ark_Number* dh)
{
    LOGE("ARKOALA CanvasRendererAccessor::DrawImage0Impl where Ark_Union_ImageBitmap_PixelMap "
        " includes Opt_CustomObject which is not implemented.");
}
void DrawImage2Impl(CanvasRendererPeer* peer,
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
    LOGE("ARKOALA CanvasRendererAccessor::DrawImage0Impl where Ark_Union_ImageBitmap_PixelMap "
        " includes Opt_CustomObject which is not implemented.");
}
void BeginPathImpl(CanvasRendererPeer* peer)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    peerImpl->TriggerBeginPathImpl();
}
void Clip0Impl(CanvasRendererPeer* peer,
               const Opt_String* fillRule)
{
}
void Clip1Impl(CanvasRendererPeer* peer,
               const Ark_Materialized* path,
               const Opt_String* fillRule)
{
}
void Fill0Impl(CanvasRendererPeer* peer,
               const Opt_String* fillRule)
{
}
void Fill1Impl(CanvasRendererPeer* peer,
               const Ark_Materialized* path,
               const Opt_String* fillRule)
{
}
void Stroke0Impl(CanvasRendererPeer* peer)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    peerImpl->TriggerStroke0Impl();
}
void Stroke1Impl(CanvasRendererPeer* peer,
                 const Ark_Materialized* path)
{
}
Ark_NativePointer CreateLinearGradientImpl(CanvasRendererPeer* peer,
                                           const Ark_Number* x0,
                                           const Ark_Number* y0,
                                           const Ark_Number* x1,
                                           const Ark_Number* y1)
{
    return 0;
}
Ark_NativePointer CreatePatternImpl(CanvasRendererPeer* peer,
                                    const Ark_Materialized* image,
                                    const Ark_Union_String_Undefined* repetition)
{
    return 0;
}
Ark_NativePointer CreateRadialGradientImpl(CanvasRendererPeer* peer,
                                           const Ark_Number* x0,
                                           const Ark_Number* y0,
                                           const Ark_Number* r0,
                                           const Ark_Number* x1,
                                           const Ark_Number* y1,
                                           const Ark_Number* r1)
{
    return 0;
}
Ark_NativePointer CreateConicGradientImpl(CanvasRendererPeer* peer,
                                          const Ark_Number* startAngle,
                                          const Ark_Number* x,
                                          const Ark_Number* y)
{
    return 0;
}
Ark_NativePointer CreateImageData0Impl(CanvasRendererPeer* peer,
                                       const Ark_Number* sw,
                                       const Ark_Number* sh)
{
    LOGE("ARKOALA CanvasRendererAccessor::CreateImageData0Impl should return Ark_ImageData "
        "object that should include Opt_CustomObject which is not implemented.");
    return 0;
}
Ark_NativePointer CreateImageData1Impl(CanvasRendererPeer* peer,
                                       const Ark_ImageData* imagedata)
{
    LOGE("ARKOALA CanvasRendererAccessor::CreateImageData1Impl Ark_ImageData includes Opt_CustomObject "
        "which is not implemented.");
    return 0;
}
Ark_NativePointer GetImageDataImpl(CanvasRendererPeer* peer,
                                   const Ark_Number* sx,
                                   const Ark_Number* sy,
                                   const Ark_Number* sw,
                                   const Ark_Number* sh)
{
    LOGE("ARKOALA CanvasRendererAccessor::GetImageDataImpl Ark_ImageData includes Opt_CustomObject "
        "which is not implemented.");
    return 0;
}
Ark_NativePointer GetPixelMapImpl(CanvasRendererPeer* peer,
                                  const Ark_Number* sx,
                                  const Ark_Number* sy,
                                  const Ark_Number* sw,
                                  const Ark_Number* sh)
{
    return 0;
}
void PutImageData0Impl(CanvasRendererPeer* peer,
                       const Ark_ImageData* imagedata,
                       const Ark_Union_Number_String* dx,
                       const Ark_Union_Number_String* dy)
{
    LOGE("ARKOALA CanvasRendererAccessor::PutImageData0Impl Ark_ImageData includes Opt_CustomObject "
        "which is not implemented.");
}
void PutImageData1Impl(CanvasRendererPeer* peer,
                       const Ark_ImageData* imagedata,
                       const Ark_Union_Number_String* dx,
                       const Ark_Union_Number_String* dy,
                       const Ark_Union_Number_String* dirtyX,
                       const Ark_Union_Number_String* dirtyY,
                       const Ark_Union_Number_String* dirtyWidth,
                       const Ark_Union_Number_String* dirtyHeight)
{
    LOGE("ARKOALA CanvasRendererAccessor::PutImageData1Impl Ark_ImageData includes Opt_CustomObject "
        "which is not implemented.");
}
void GetLineDashImpl(CanvasRendererPeer* peer)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    peerImpl->TriggerGetLineDashImpl();
    LOGE("ARKOALA CanvasRendererAccessor::GetLineDashImpl method should return object with specific type");
}
void SetLineDashImpl(CanvasRendererPeer* peer,
                     const Array_Number* segments)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(segments);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);

    auto src = Converter::Convert<std::vector<float>>(*segments);
    if (src.size() == SIZE_LIMIT_MIN) {
        return;
    }
    for (const auto& segment : src) {
        if (segment < SEGMENT_LIMIT_MIN) {
            return;
        }
    }
    std::vector<double> dst;
    std::transform(src.begin(), src.end(), std::back_inserter(dst), [](auto val) { return static_cast<double>(val); });
    peerImpl->TriggerSetLineDashImpl(dst);
}
void ClearRectImpl(CanvasRendererPeer* peer,
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

    auto arkRect = Ark_Custom_Rect {
        .x = *x,
        .y = *y,
        .w = *w,
        .h = *h
    };
    auto rect = Converter::Convert<Rect>(arkRect);
    if (!rect.IsValid()) {
        return;
    }
    peerImpl->TriggerClearRectImpl(rect);
}
void FillRectImpl(CanvasRendererPeer* peer,
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

    auto arkRect = Ark_Custom_Rect {
        .x = *x,
        .y = *y,
        .w = *w,
        .h = *h
    };
    auto rect = Converter::Convert<Rect>(arkRect);
    if (!rect.IsValid()) {
        return;
    }
    peerImpl->TriggerFillRectImpl(rect);
}
void StrokeRectImpl(CanvasRendererPeer* peer,
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

    auto arkRect = Ark_Custom_Rect {
        .x = *x,
        .y = *y,
        .w = *w,
        .h = *h
    };
    auto rect = Converter::Convert<Rect>(arkRect);
    if (!rect.IsValid()) {
        return;
    }
    peerImpl->TriggerStrokeRectImpl(rect);
}
void RestoreImpl(CanvasRendererPeer* peer)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    peerImpl->TriggerRestoreImpl();
}
void SaveImpl(CanvasRendererPeer* peer)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    peerImpl->TriggerSaveImpl();
}
void FillTextImpl(CanvasRendererPeer* peer,
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
    auto opt = Converter::OptConvert<float>(*maxWidth);

    auto optMaxWidth = std::make_optional<double>();
    if (opt.has_value()) {
        *optMaxWidth = static_cast<double>(*opt);
    }
    peerImpl->TriggerFillTextImpl(valueText, valueX, valueY, optMaxWidth);
}
Ark_NativePointer MeasureTextImpl(CanvasRendererPeer* peer,
                                  const Ark_String* text)
{
    return 0;
}
void StrokeTextImpl(CanvasRendererPeer* peer,
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
    auto opt = Converter::OptConvert<float>(*maxWidth);

    auto optMaxWidth = std::make_optional<double>();
    if (opt.has_value()) {
        *optMaxWidth = static_cast<double>(*opt);
    }
    peerImpl->TriggerStrokeTextImpl(valueText, valueX, valueY, optMaxWidth);
}
Ark_NativePointer GetTransformImpl(CanvasRendererPeer* peer)
{
    return 0;
}
void ResetTransformImpl(CanvasRendererPeer* peer)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    peerImpl->TriggerResetTransformImpl();
}
void RotateImpl(CanvasRendererPeer* peer,
                const Ark_Number* angle)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(angle);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);

    auto rotateAngle = static_cast<double>(Converter::Convert<float>(*angle));
    peerImpl->TriggerRotateImpl(rotateAngle);
}
void ScaleImpl(CanvasRendererPeer* peer,
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
    if (scaleX < SCALE_LIMIT_MIN || scaleY < SCALE_LIMIT_MIN) {
        return;
    }
    peerImpl->TriggerScaleImpl(scaleX, scaleY);
}
void SetTransform0Impl(CanvasRendererPeer* peer,
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
    if (param.scaleX < SCALE_LIMIT_MIN || param.scaleY < SCALE_LIMIT_MIN) {
        return;
    }
    peerImpl->TriggerSetTransform0Impl(param);
}
void SetTransform1Impl(CanvasRendererPeer* peer,
                       const Opt_Matrix2D* transform)
{
}
void TransformImpl(CanvasRendererPeer* peer,
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
    if (param.scaleX < SCALE_LIMIT_MIN || param.scaleY < SCALE_LIMIT_MIN) {
        return;
    }
    peerImpl->TriggerSetTransform0Impl(param);
}
void TranslateImpl(CanvasRendererPeer* peer,
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
    peerImpl->TriggerTranslateImpl(transX, transY);
}
void SetPixelMapImpl(CanvasRendererPeer* peer,
                     const Opt_PixelMap* value)
{
    LOGE("ARKOALA CanvasRendererAccessor::SetPixelMapImpl Opt_CustomObject is not implemented.");
}
void TransferFromImageBitmapImpl(CanvasRendererPeer* peer,
                                 const Ark_Materialized* bitmap)
{
}
void SaveLayerImpl(CanvasRendererPeer* peer)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    peerImpl->TriggerSaveLayerImpl();
}
void RestoreLayerImpl(CanvasRendererPeer* peer)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    peerImpl->TriggerRestoreLayerImpl();
}
void ResetImpl(CanvasRendererPeer* peer)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    peerImpl->TriggerResetImpl();
}
Ark_Int32 GetGlobalAlphaImpl(CanvasRendererPeer* peer)
{
    return 0;
}
void SetGlobalAlphaImpl(CanvasRendererPeer* peer,
                        const Ark_Number* globalAlpha)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(globalAlpha);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);

    auto alpha = static_cast<double>(Converter::Convert<float>(*globalAlpha));
    if (alpha < ALPHA_LIMIT_MIN || alpha > ALPHA_LIMIT_MAX) {
        return;
    }
    peerImpl->TriggerSetGlobalAlphaImpl(alpha);
}
void GetGlobalCompositeOperationImpl(CanvasRendererPeer* peer)
{
    LOGE("ARKOALA CanvasRendererAccessor::GetGlobalCompositeOperationImpl method should return "
        "object with specific type");
}
void SetGlobalCompositeOperationImpl(CanvasRendererPeer* peer,
                                     const Ark_String* globalCompositeOperation)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(globalCompositeOperation);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);

    auto opt = Converter::OptConvert<CompositeOperation>(*globalCompositeOperation);
    if (!opt) {
        return;
    }
    peerImpl->TriggerSetGlobalCompositeOperationImpl(*opt);
}
void SetFillStyleImpl(CanvasRendererPeer* peer,
                      const Ark_Union_String_Number_CanvasGradient_CanvasPattern* fillStyle)
{
}
void SetStrokeStyleImpl(CanvasRendererPeer* peer,
                        const Ark_Union_String_Number_CanvasGradient_CanvasPattern* strokeStyle)
{
}
void GetFilterImpl(CanvasRendererPeer* peer)
{
    LOGE("ARKOALA CanvasRendererAccessor::GetFilterImpl method should return object with specific type");
}
void SetFilterImpl(CanvasRendererPeer* peer,
                   const Ark_String* filter)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(filter);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);

    auto filterValue = Converter::Convert<std::string>(*filter);
    if (filterValue.length() == 0) {
        return;
    }
    peerImpl->TriggerSetFilterImpl(filterValue);
}
Ark_Boolean GetImageSmoothingEnabledImpl(CanvasRendererPeer* peer)
{
    return 0;
}
void SetImageSmoothingEnabledImpl(CanvasRendererPeer* peer,
                                  Ark_Boolean imageSmoothingEnabled)
{
}
Ark_NativePointer GetImageSmoothingQualityImpl(CanvasRendererPeer* peer)
{
    return 0;
}
void SetImageSmoothingQualityImpl(CanvasRendererPeer* peer,
                                  const Ark_String* imageSmoothingQuality)
{
}
Ark_NativePointer GetLineCapImpl(CanvasRendererPeer* peer)
{
    return 0;
}
void SetLineCapImpl(CanvasRendererPeer* peer,
                    const Ark_String* lineCap)
{
}
Ark_Int32 GetLineDashOffsetImpl(CanvasRendererPeer* peer)
{
    return 0;
}
void SetLineDashOffsetImpl(CanvasRendererPeer* peer,
                           const Ark_Number* lineDashOffset)
{
}
Ark_NativePointer GetLineJoinImpl(CanvasRendererPeer* peer)
{
    return 0;
}
void SetLineJoinImpl(CanvasRendererPeer* peer,
                     const Ark_String* lineJoin)
{
}
Ark_Int32 GetLineWidthImpl(CanvasRendererPeer* peer)
{
    return 0;
}
void SetLineWidthImpl(CanvasRendererPeer* peer,
                      const Ark_Number* lineWidth)
{
}
Ark_Int32 GetMiterLimitImpl(CanvasRendererPeer* peer)
{
    return 0;
}
void SetMiterLimitImpl(CanvasRendererPeer* peer,
                       const Ark_Number* miterLimit)
{
}
Ark_Int32 GetShadowBlurImpl(CanvasRendererPeer* peer)
{
    return 0;
}
void SetShadowBlurImpl(CanvasRendererPeer* peer,
                       const Ark_Number* shadowBlur)
{
}
void GetShadowColorImpl(CanvasRendererPeer* peer)
{
    LOGE("ARKOALA CanvasRendererAccessor::GetShadowColorImpl method should return object with specific type");
}
void SetShadowColorImpl(CanvasRendererPeer* peer,
                        const Ark_String* shadowColor)
{
}
Ark_Int32 GetShadowOffsetXImpl(CanvasRendererPeer* peer)
{
    return 0;
}
void SetShadowOffsetXImpl(CanvasRendererPeer* peer,
                          const Ark_Number* shadowOffsetX)
{
}
Ark_Int32 GetShadowOffsetYImpl(CanvasRendererPeer* peer)
{
    return 0;
}
void SetShadowOffsetYImpl(CanvasRendererPeer* peer,
                          const Ark_Number* shadowOffsetY)
{
}
Ark_NativePointer GetDirectionImpl(CanvasRendererPeer* peer)
{
    return 0;
}
void SetDirectionImpl(CanvasRendererPeer* peer,
                      const Ark_String* direction)
{
}
void GetFontImpl(CanvasRendererPeer* peer)
{
    LOGE("ARKOALA CanvasRendererAccessor::GetFontImpl method should return object with specific type");
}
void SetFontImpl(CanvasRendererPeer* peer,
                 const Ark_String* font)
{
}
Ark_NativePointer GetTextAlignImpl(CanvasRendererPeer* peer)
{
    return 0;
}
void SetTextAlignImpl(CanvasRendererPeer* peer,
                      const Ark_String* textAlign)
{
}
Ark_NativePointer GetTextBaselineImpl(CanvasRendererPeer* peer)
{
    return 0;
}
void SetTextBaselineImpl(CanvasRendererPeer* peer,
                         const Ark_String* textBaseline)
{
}
} // CanvasRendererAccessor
const GENERATED_ArkUICanvasRendererAccessor* GetCanvasRendererAccessor()
{
    static const GENERATED_ArkUICanvasRendererAccessor CanvasRendererAccessorImpl {
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
        CanvasRendererAccessor::GetGlobalAlphaImpl,
        CanvasRendererAccessor::SetGlobalAlphaImpl,
        CanvasRendererAccessor::GetGlobalCompositeOperationImpl,
        CanvasRendererAccessor::SetGlobalCompositeOperationImpl,
        CanvasRendererAccessor::SetFillStyleImpl,
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
