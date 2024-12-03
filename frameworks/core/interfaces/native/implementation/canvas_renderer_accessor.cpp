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
#include "core/interfaces/native/utility/converter_union.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "canvas_renderer_peer_impl.h"
#include "canvas_path_peer.h"
#include "canvas_pattern_peer.h"
#include "canvas_gradient_peer.h"
#include "matrix2d_peer.h"
#include "image_bitmap_peer_impl.h"

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

const std::set<std::string> FONT_WEIGHTS = {
    "100", "200", "300", "400", "500", "600", "700", "800", "900",
    "bold", "bolder", "lighter", "medium", "normal", "regular",
};
const std::set<std::string> FONT_STYLES = { "italic", "oblique", "normal" };
const std::set<std::string> FONT_FAMILIES = { "sans-serif", "serif", "monospace" };
const std::set<std::string> QUALITY_TYPE = { "low", "medium", "high" }; // Default value is low.
constexpr Dimension DEFAULT_FONT_SIZE = 14.0_px;
constexpr double DEFAULT_QUALITY = 0.92;
constexpr uint32_t COLOR_ALPHA_OFFSET = 24;
constexpr uint32_t COLOR_ALPHA_VALUE = 0xFF000000;
constexpr double DIFF = 1e-10;

void FontParseSize(GeneratedModifier::CanvasRendererPeerImpl* peerImpl, std::string fontProp)
{
    if (fontProp.find("vp") != std::string::npos) {
        Dimension dimension = StringUtils::StringToDimension(fontProp);
        if (dimension.IsNegative()) {
            return;
        }
        if ((dimension.Unit() == DimensionUnit::NONE) || (dimension.Unit() == DimensionUnit::PX)) {
            peerImpl->TriggerUpdateFontSize(Dimension(dimension.Value()));
        } else if (dimension.Unit() == DimensionUnit::VP) {
            if (dimension.IsNegative()) {
                return;
            }
            peerImpl->TriggerUpdateFontSize(Dimension(dimension.Value()));
            LOGE("ARKOALA CanvasRendererAccessor::SetFontImpl there is no implementation in controller "
                 "for getter method of Dimension density.");
        }
        peerImpl->TriggerUpdateFontSize(Dimension(0.0));
    } else {
        std::string fontSize = fontProp.substr(0, fontProp.size() - 2);
        Dimension dimension = Dimension(StringUtils::StringToDouble(fontProp));
        if (dimension.IsNegative()) {
            return;
        }
        peerImpl->TriggerUpdateFontSize(dimension);
    }
}
void FontParseFamilies(GeneratedModifier::CanvasRendererPeerImpl* peerImpl, std::string fontProp)
{
    std::vector<std::string> fontFamilies;
    std::stringstream stream(fontProp);
    std::string fontFamily;
    while (getline(stream, fontFamily, ',')) {
        fontFamilies.emplace_back(fontFamily);
    }
    peerImpl->TriggerUpdateFontFamilies(fontFamilies);
}
void FontParseStyle(GeneratedModifier::CanvasRendererPeerImpl* peerImpl, std::string fontProp)
{
    auto fontStyle = fontProp == DOM_TEXT_FONT_STYLE_ITALIC ? OHOS::Ace::FontStyle::ITALIC : Ace::FontStyle::NORMAL;
    peerImpl->TriggerUpdateFontStyle(fontStyle);
}
void FontParseWeight(GeneratedModifier::CanvasRendererPeerImpl* peerImpl, std::string fontProp)
{
    auto weight = StringUtils::StringToFontWeight(fontProp, Ace::FontWeight::NORMAL);
    peerImpl->TriggerUpdateFontWeight(weight);
}
void FontParser(GeneratedModifier::CanvasRendererPeerImpl* peerImpl, std::string fontStr)
{
    bool updateFontweight = false;
    bool updateFontStyle = false;
    std::vector<std::string> fontProps;
    StringUtils::StringSplitter(fontStr.c_str(), ' ', fontProps);
    for (const auto& fontProp : fontProps) {
        if (FONT_WEIGHTS.find(fontProp) != FONT_WEIGHTS.end()) {
            updateFontweight = true;
            FontParseWeight(peerImpl, fontProp);
        } else if (FONT_STYLES.find(fontProp) != FONT_STYLES.end()) {
            updateFontStyle = true;
            FontParseStyle(peerImpl, fontProp);
        } else if (FONT_FAMILIES.find(fontProp) != FONT_FAMILIES.end()) {
            FontParseFamilies(peerImpl, fontProp);
        } else if (fontProp.find("px") != std::string::npos || fontProp.find("vp") != std::string::npos) {
            FontParseSize(peerImpl, fontProp);
        }
    }
    if (!updateFontStyle) {
        peerImpl->TriggerUpdateFontStyle(Ace::FontStyle::NORMAL);
    }
    if (!updateFontweight) {
        peerImpl->TriggerUpdateFontWeight(Ace::FontWeight::NORMAL);
    }
}

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
        " includes Ark_PixelMap which is partially implemented.");
}
void DrawImage1Impl(CanvasRendererPeer* peer,
                    const Ark_Union_ImageBitmap_PixelMap* image,
                    const Ark_Number* dx,
                    const Ark_Number* dy,
                    const Ark_Number* dw,
                    const Ark_Number* dh)
{
    LOGE("ARKOALA CanvasRendererAccessor::DrawImage1Impl where Ark_Union_ImageBitmap_PixelMap "
        " includes Ark_PixelMap which is partially implemented.");
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
    LOGE("ARKOALA CanvasRendererAccessor::DrawImage2Impl where Ark_Union_ImageBitmap_PixelMap "
        " includes Ark_PixelMap which is partially implemented.");
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
    LOGE("ARKOALA CanvasRendererAccessor::Clip0Impl Opt_String parameter "
        "should be replaced with a valid ark enum for CanvasFillRule type.");
}
void Clip1Impl(CanvasRendererPeer* peer,
               const Ark_Materialized* path,
               const Opt_String* fillRule)
{
    LOGE("ARKOALA CanvasRendererAccessor::Clip1Impl Opt_String parameter "
        "should be replaced with a valid ark enum for CanvasFillRule type.");
}
void Fill0Impl(CanvasRendererPeer* peer,
               const Opt_String* fillRule)
{
    LOGE("ARKOALA CanvasRendererAccessor::Fill0Impl Opt_String parameter "
        "should be replaced with a valid ark enum for CanvasFillRule type.");
}
void Fill1Impl(CanvasRendererPeer* peer,
               const Ark_Materialized* path,
               const Opt_String* fillRule)
{
    LOGE("ARKOALA CanvasRendererAccessor::Fill1Impl Opt_String parameter "
        "should be replaced with a valid ark enum for CanvasFillRule type.");
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
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    CHECK_NULL_VOID(path);
    auto pathPeer = reinterpret_cast<CanvasPathPeer*>(path->ptr);
    CHECK_NULL_VOID(pathPeer);
    auto path2D = pathPeer->GetCanvasPath2D();
    CHECK_NULL_VOID(path2D);
    peerImpl->TriggerStroke1Impl(path2D);
}
Ark_NativePointer CreateLinearGradientImpl(CanvasRendererPeer* peer,
                                           const Ark_Number* x0,
                                           const Ark_Number* y0,
                                           const Ark_Number* x1,
                                           const Ark_Number* y1)
{
    LOGE("ARKOALA CanvasRendererAccessor::CreateLinearGradientImpl return type Ark_NativePointer "
        "should be replaced with a valid ark type for CanvasGradient.");
    return 0;
}
Ark_NativePointer CreatePatternImpl(CanvasRendererPeer* peer,
                                    const Ark_Materialized* image,
                                    const Ark_Union_String_Undefined* repetition)
{
    LOGE("ARKOALA CanvasRendererAccessor::CreatePatternImpl return type Ark_NativePointer "
        "should be replaced with a valid ark type for CanvasPattern.");
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
    LOGE("ARKOALA CanvasRendererAccessor::CreateRadialGradientImpl return type Ark_NativePointer "
        "should be replaced with a valid ark enum for CanvasGradient type.");
    return 0;
}
Ark_NativePointer CreateConicGradientImpl(CanvasRendererPeer* peer,
                                          const Ark_Number* startAngle,
                                          const Ark_Number* x,
                                          const Ark_Number* y)
{
    LOGE("ARKOALA CanvasRendererAccessor::CreateConicGradientImpl return type Ark_NativePointer "
        "should be replaced with a valid ark enum for CanvasGradient type.");
    return 0;
}
Ark_NativePointer CreateImageData0Impl(CanvasRendererPeer* peer,
                                       const Ark_Number* sw,
                                       const Ark_Number* sh)
{
    LOGE("ARKOALA CanvasRendererAccessor::CreateImageData0Impl return type Ark_NativePointer "
        "should be replaced with a valid ark type for ImageData.");
    return 0;
}
Ark_NativePointer CreateImageData1Impl(CanvasRendererPeer* peer,
                                       const Ark_ImageData* imagedata)
{
    LOGE("ARKOALA CanvasRendererAccessor::CreateImageData1Impl return type Ark_NativePointer "
        "should be replaced with a valid ark type for ImageData.");
    LOGE("ARKOALA CanvasRendererAccessor::CreateImageData1Impl Ark_ImageData includes Ark_ArrayBuffer "
        "which is partially implemented.");
    return 0;
}
Ark_NativePointer GetImageDataImpl(CanvasRendererPeer* peer,
                                   const Ark_Number* sx,
                                   const Ark_Number* sy,
                                   const Ark_Number* sw,
                                   const Ark_Number* sh)
{
    LOGE("ARKOALA CanvasRendererAccessor::GetImageDataImpl return type Ark_NativePointer "
        "should be replaced with a valid ark type for ImageData.");
    return 0;
}
Ark_NativePointer GetPixelMapImpl(CanvasRendererPeer* peer,
                                  const Ark_Number* sx,
                                  const Ark_Number* sy,
                                  const Ark_Number* sw,
                                  const Ark_Number* sh)
{
    LOGE("ARKOALA CanvasRendererAccessor::GetPixelMapImpl return type Ark_NativePointer "
        "should be replaced with a valid ark type for PixelMap.");
    return 0;
}
void PutImageData0Impl(CanvasRendererPeer* peer,
                       const Ark_ImageData* imagedata,
                       const Ark_Union_Number_String* dx,
                       const Ark_Union_Number_String* dy)
{
    LOGE("ARKOALA CanvasRendererAccessor::PutImageData0Impl Ark_ImageData includes Ark_ArrayBuffer "
        "which is partially implemented.");
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
    LOGE("ARKOALA CanvasRendererAccessor::PutImageData1Impl Ark_ImageData includes Ark_ArrayBuffer "
        "which is partially implemented.");
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
    LOGE("ARKOALA CanvasRendererAccessor::MeasureTextImpl return type Ark_NativePointer "
        "should be replaced with a valid ark type for TextMetrics.");
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
    LOGE("ARKOALA CanvasRendererAccessor::GetTransformImpl return type Ark_NativePointer "
        "should be replaced with a valid ark type for Matrix2D.");
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
    peerImpl->TriggerSetTransformImpl(param);
}
void SetTransform1Impl(CanvasRendererPeer* peer,
                       const Opt_Matrix2D* transform)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    CHECK_NULL_VOID(transform);
    auto opt = Converter::OptConvert<Ark_Matrix2D>(*transform);
    CHECK_NULL_VOID(opt);
    auto matrixPeer = reinterpret_cast<Matrix2DPeer*>(opt->ptr);
    CHECK_NULL_VOID(matrixPeer);
    auto param = matrixPeer->GetTransformParam();
    CHECK_NULL_VOID(param);
    if (param->scaleX < SCALE_LIMIT_MIN || param->scaleY < SCALE_LIMIT_MIN) {
        return;
    }
    peerImpl->TriggerSetTransformImpl(*param);
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
    peerImpl->TriggerTransformImpl(param);
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
}
void TransferFromImageBitmapImpl(CanvasRendererPeer* peer,
                                 const Ark_Materialized* bitmap)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    CHECK_NULL_VOID(bitmap);
    auto bitmapPeer = reinterpret_cast<ImageBitmapPeer*>(bitmap->ptr);
    CHECK_NULL_VOID(bitmapPeer);
#ifdef PIXEL_MAP_SUPPORTED
    auto canvasImage = bitmapPeer->GetCanvasImage();
    CHECK_NULL_VOID(canvasImage);
    auto pixelMap = canvasImage->GetPixelMap();
    CHECK_NULL_VOID(pixelMap);
    peerImpl->TriggerTransferFromImageBitmapImpl(pixelMap);
#else 
    auto width = bitmapPeer->GetWidth();
    auto height = bitmapPeer->GetHeight();
    peerImpl->TriggerTransferFromImageBitmapImpl(width, height);
#endif
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
    LOGE("ARKOALA CanvasRendererAccessor::GetGlobalAlphaImpl there is no implementation in controller "
        "for getter method of GlobalAlpha.");
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
    CHECK_NULL_VOID(opt);
    peerImpl->TriggerSetGlobalCompositeOperationImpl(*opt);
}
void SetFillStyleImpl(CanvasRendererPeer* peer,
                      const Ark_Union_String_Number_CanvasGradient_CanvasPattern* fillStyle)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    CHECK_NULL_VOID(fillStyle);
    LOGE("ARKOALA CanvasRendererAccessor::SetStrokeStyleImpl input Union includes same type members");
}
void SetStrokeStyleImpl(CanvasRendererPeer* peer,
                        const Ark_Union_String_Number_CanvasGradient_CanvasPattern* strokeStyle)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    CHECK_NULL_VOID(strokeStyle);
    LOGE("ARKOALA CanvasRendererAccessor::SetStrokeStyleImpl input Union includes same type members");
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
    LOGE("ARKOALA CanvasRendererAccessor::GetImageSmoothingEnabledImpl there is no implementation in controller "
        "for getter method of ImageSmoothingEnabled.");
    return 0;
}
void SetImageSmoothingEnabledImpl(CanvasRendererPeer* peer,
                                  Ark_Boolean imageSmoothingEnabled)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);

    auto enabled = Converter::Convert<bool>(imageSmoothingEnabled);
    peerImpl->TriggerSetImageSmoothingEnabledImpl(enabled);
}
Ark_NativePointer GetImageSmoothingQualityImpl(CanvasRendererPeer* peer)
{
    LOGE("ARKOALA CanvasRendererAccessor::GetImageSmoothingQualityImpl return type Ark_NativePointer "
        "should be replaced with a valid ark enum for ImageSmoothingQuality type.");
    return 0;
}
void SetImageSmoothingQualityImpl(CanvasRendererPeer* peer,
                                  const Ark_String* imageSmoothingQuality)
{
    LOGE("ARKOALA CanvasRendererAccessor::SetImageSmoothingQualityImpl Ark_String type parameter "
        "should be replaced with a valid ark enum for ImageSmoothingQuality type.");
}
Ark_NativePointer GetLineCapImpl(CanvasRendererPeer* peer)
{
    LOGE("ARKOALA CanvasRendererAccessor::GetLineCapImpl return type Ark_NativePointer "
        "should be replaced with a valid ark enum for CanvasLineCap type.");
    LOGE("ARKOALA CanvasRendererAccessor::GetLineCapImpl there is no implementation in controller "
        "for getter method of LineCap.");
    return 0;
}
void SetLineCapImpl(CanvasRendererPeer* peer,
                    const Ark_String* lineCap)
{
    LOGE("ARKOALA CanvasRendererAccessor::SetLineCapImpl return type Ark_NativePointer "
        "should be replaced with a valid ark enum for CanvasLineCap type.");
}
Ark_Int32 GetLineDashOffsetImpl(CanvasRendererPeer* peer)
{
    LOGE("ARKOALA CanvasRendererAccessor::GetLineDashOffsetImpl there is no implementation in controller "
        "for getter method of LineDashOffset.");
    return 0;
}
void SetLineDashOffsetImpl(CanvasRendererPeer* peer,
                           const Ark_Number* lineDashOffset)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(lineDashOffset);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);

    auto offset = static_cast<double>(Converter::Convert<float>(*lineDashOffset));
    peerImpl->TriggerSetLineDashOffsetImpl(offset);
}
Ark_NativePointer GetLineJoinImpl(CanvasRendererPeer* peer)
{
    LOGE("ARKOALA CanvasRendererAccessor::GetLineJoinImpl return type Ark_NativePointer "
        "should be replaced with a valid ark enum for CanvasLineJoin type.");
    LOGE("ARKOALA CanvasRendererAccessor::GetLineJoinImpl there is no implementation in controller "
        "for getter method of LineJoin.");
    return 0;
}
void SetLineJoinImpl(CanvasRendererPeer* peer,
                     const Ark_String* lineJoin)
{
    LOGE("ARKOALA CanvasRendererAccessor::SetLineJoinImpl Ark_String type parameter "
        "should be replaced with a valid ark enum for CanvasLineJoin type.");
}
Ark_Int32 GetLineWidthImpl(CanvasRendererPeer* peer)
{
    LOGE("ARKOALA CanvasRendererAccessor::GetLineWidthImpl there is no implementation in controller "
        "for getter method of LinewWidth.");
    return 0;
}
void SetLineWidthImpl(CanvasRendererPeer* peer,
                      const Ark_Number* lineWidth)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(lineWidth);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);

    auto width = static_cast<double>(Converter::Convert<float>(*lineWidth));
    peerImpl->TriggerSetLineWidthImpl(width);
}
Ark_Int32 GetMiterLimitImpl(CanvasRendererPeer* peer)
{
    LOGE("ARKOALA CanvasRendererAccessor::GetMiterLimitImpl there is no implementation in controller "
        "for getter method of MiterLimit.");
    return 0;
}
void SetMiterLimitImpl(CanvasRendererPeer* peer,
                       const Ark_Number* miterLimit)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(miterLimit);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);

    auto limit = static_cast<double>(Converter::Convert<float>(*miterLimit));
    peerImpl->TriggerSetMiterLimitImpl(limit);
}
Ark_Int32 GetShadowBlurImpl(CanvasRendererPeer* peer)
{
    LOGE("ARKOALA CanvasRendererAccessor::GetShadowBlurImpl there is no implementation in controller "
        "for getter method of ShadowBlur.");
    return 0;
}
void SetShadowBlurImpl(CanvasRendererPeer* peer,
                       const Ark_Number* shadowBlur)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(shadowBlur);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);

    auto blur = static_cast<double>(Converter::Convert<float>(*shadowBlur));
    peerImpl->TriggerSetShadowBlurImpl(blur);
}
void GetShadowColorImpl(CanvasRendererPeer* peer)
{
    LOGE("ARKOALA CanvasRendererAccessor::GetShadowColorImpl method should return object with specific type");
}
void SetShadowColorImpl(CanvasRendererPeer* peer,
                        const Ark_String* shadowColor)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(shadowColor);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);

    auto opt = Converter::OptConvert<Color>(*shadowColor);
    CHECK_NULL_VOID(opt);
    peerImpl->TriggerSetShadowColorImpl(*opt);
}
Ark_Int32 GetShadowOffsetXImpl(CanvasRendererPeer* peer)
{
    LOGE("ARKOALA CanvasRendererAccessor::GetShadowOffsetXImpl there is no implementation in controller "
        "for getter method of ShadowOffsetXImpl.");
    return 0;
}
void SetShadowOffsetXImpl(CanvasRendererPeer* peer,
                          const Ark_Number* shadowOffsetX)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(shadowOffsetX);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);

    auto offsetX = static_cast<double>(Converter::Convert<float>(*shadowOffsetX));
    peerImpl->TriggerSetShadowOffsetXImpl(offsetX);
}
Ark_Int32 GetShadowOffsetYImpl(CanvasRendererPeer* peer)
{
    LOGE("ARKOALA CanvasRendererAccessor::GetShadowOffsetYImpl there is no implementation in controller "
        "for getter method of ShadowOffsetYImpl.");
    return 0;
}
void SetShadowOffsetYImpl(CanvasRendererPeer* peer,
                          const Ark_Number* shadowOffsetY)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(shadowOffsetY);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);

    auto offsetY = static_cast<double>(Converter::Convert<float>(*shadowOffsetY));
    peerImpl->TriggerSetShadowOffsetYImpl(offsetY);
}
Ark_NativePointer GetDirectionImpl(CanvasRendererPeer* peer)
{
    LOGE("ARKOALA CanvasRendererAccessor::GetDirectionImpl return type Ark_NativePointer "
        "should be replaced with a valid ark enum for CanvasDirection type.");
    LOGE("ARKOALA CanvasRendererAccessor::GetDirectionImpl there is no implementation in controller "
        "for getter method of Direction.");
    return 0;
}
void SetDirectionImpl(CanvasRendererPeer* peer,
                      const Ark_String* direction)
{
    LOGE("ARKOALA CanvasRendererAccessor::SetDirectionImpl Ark_String type parameter "
        "should be replaced with a valid ark enum for CanvasDirection type.");
}
void GetFontImpl(CanvasRendererPeer* peer)
{
    LOGE("ARKOALA CanvasRendererAccessor::GetFontImpl method should return object with specific type");
}
void SetFontImpl(CanvasRendererPeer* peer,
                 const Ark_String* font)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(font);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    auto fontStr = Converter::Convert<std::string>(*font);

    FontParser(peerImpl, fontStr);
}
Ark_NativePointer GetTextAlignImpl(CanvasRendererPeer* peer)
{
    LOGE("ARKOALA CanvasRendererAccessor::GetTextAlignImpl return type Ark_NativePointer "
        "should be replaced with a valid ark enum for CanvasTextAlign type.");
    LOGE("ARKOALA CanvasRendererAccessor::GetTextAlignImpl there is no implementation in controller "
        "for getter method of TextAlign.");
    return 0;
}
void SetTextAlignImpl(CanvasRendererPeer* peer,
                      const Ark_String* textAlign)
{
    LOGE("ARKOALA CanvasRendererAccessor::SetTextAlignImpl Ark_String type parameter "
        "should be replaced with a valid ark enum for CanvasTextAlign type.");
}
Ark_NativePointer GetTextBaselineImpl(CanvasRendererPeer* peer)
{
    LOGE("ARKOALA CanvasRendererAccessor::GetTextBaselineImpl return type Ark_NativePointer "
        "should be replaced with a valid ark enum for CanvasTextBaseline type.");
    LOGE("ARKOALA CanvasRendererAccessor::GetTextBaselineImpl there is no implementation in controller "
        "for getter method of TextBaseline.");
    return 0;
}
void SetTextBaselineImpl(CanvasRendererPeer* peer,
                         const Ark_String* textBaseline)
{
    LOGE("ARKOALA CanvasRendererAccessor::SetTextBaselineImpl Ark_String type parameter "
        "should be replaced with a valid ark enum for CanvasTextBaseline type.");
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
