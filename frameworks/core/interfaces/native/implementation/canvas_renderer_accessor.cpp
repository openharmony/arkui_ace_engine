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
#include "canvas_path_accessor_peer_impl.h"
#include "canvas_pattern_peer.h"
#include "canvas_gradient_peer.h"
#include "matrix2d_peer.h"
#include "image_bitmap_peer_impl.h"
#include "image_data_peer.h"
#include "base/utils/utils.h"
#include "pixel_map_peer.h"

namespace OHOS::Ace::NG {
namespace {
const auto ALPHA_LIMIT_MIN = 0.0;
const auto ALPHA_LIMIT_MAX = 1.0;
const auto SIZE_LIMIT_MIN = 0.0;
const auto SEGMENT_LIMIT_MIN = 0.0;
const auto SCALE_LIMIT_MIN = 0.0;
constexpr uint32_t COLOR_WHITE = 0xffffffff;
constexpr uint32_t COLOR_ALPHA_OFFSET = 24;
constexpr uint32_t COLOR_ALPHA_VALUE = 0XFF000000;
constexpr double DIFF = 1e-10;
const auto EMPTY_STRING = "";
const auto FILL_RULE_EVEN_ODD = "evenodd";
const auto DIR_AUTO = "auto";
const auto DIR_INHERIT = "inherit";
const auto DIR_LTR = "ltr";
const auto DIR_RTL = "rtl";
const auto DOM_CENTER = "center";
const auto DOM_END = "end";
const auto DOM_JUSTIFY = "justify";
const auto DOM_LEFT = "left";
const auto DOM_RIGHT = "right";
const auto DOM_START = "start";
const auto DOM_ALPHABETIC = "alphabetic";
const auto DOM_BOTTOM = "bottom";
const auto DOM_HANGING = "hanging";
const auto DOM_IDEOGRAPHIC = "ideographic";
const auto DOM_MIDDLE = "middle";
const auto DOM_TOP = "top";
struct Ark_Custom_Rect {
    Ark_Number x;
    Ark_Number y;
    Ark_Number w;
    Ark_Number h;
};
const std::unordered_map<std::string, CompositeOperation> COMPOSITE_TABLE = {
    { "source-over", CompositeOperation::SOURCE_OVER },
    { "source-atop", CompositeOperation::SOURCE_ATOP },
    { "source-in", CompositeOperation::SOURCE_IN },
    { "source-out", CompositeOperation::SOURCE_OUT },
    { "destination-over", CompositeOperation::DESTINATION_OVER },
    { "destination-atop", CompositeOperation::DESTINATION_ATOP },
    { "destination-in", CompositeOperation::DESTINATION_IN },
    { "destination-out", CompositeOperation::DESTINATION_OUT },
    { "lighter", CompositeOperation::LIGHTER },
    { "copy", CompositeOperation::COPY },
    { "xor", CompositeOperation::XOR }
};
std::optional<double> ConvertDimension(
    GeneratedModifier::CanvasRendererPeerImpl* peerImpl, const Ark_Union_Number_String& src)
{
    std::optional<double> dst = std::nullopt;
    Converter::VisitUnion(
        src,
        [&dst, peerImpl](const Ark_String& value) {
            auto opt = Converter::OptConvert<Dimension>(value);
            if (opt) {
                dst = peerImpl->GetDimension(*opt, true);
            }
        },
        [&dst, peerImpl](const Ark_Number& value) {
            auto opt = Converter::OptConvert<Dimension>(value);
            if (opt) {
                dst = peerImpl->GetDimension(*opt);
            }
        },
        []() {});
    return dst;
}
uint32_t ColorAlphaAdapt(uint32_t origin)
{
    uint32_t result = origin;
    if ((origin >> COLOR_ALPHA_OFFSET) == 0) {
        result = origin | COLOR_ALPHA_VALUE;
    }
    return result;
}
} // namespace
namespace Converter {
template<>
TextBaseline Convert(const Ark_String& src)
{
    auto baseLine = Converter::Convert<std::string>(src);
    static const LinearMapNode<TextBaseline> textBaseAlignTable[] = {
        { DOM_ALPHABETIC, TextBaseline::ALPHABETIC },
        { DOM_BOTTOM, TextBaseline::BOTTOM },
        { DOM_HANGING, TextBaseline::HANGING },
        { DOM_IDEOGRAPHIC, TextBaseline::IDEOGRAPHIC },
        { DOM_MIDDLE, TextBaseline::MIDDLE },
        { DOM_TOP, TextBaseline::TOP },
    };
    auto index = BinarySearchFindIndex(textBaseAlignTable, ArraySize(textBaseAlignTable), baseLine.c_str());
    return index < 0 ? TextBaseline::ALPHABETIC : textBaseAlignTable[index].value;
}
template<>
TextAlign Convert(const Ark_String& src)
{
    auto align = Converter::Convert<std::string>(src);
    static const LinearMapNode<TextAlign> textAlignTable[] = {
        { DOM_CENTER, TextAlign::CENTER },
        { DOM_END, TextAlign::END },
        { DOM_JUSTIFY, TextAlign::JUSTIFY },
        { DOM_LEFT, TextAlign::LEFT },
        { DOM_RIGHT, TextAlign::RIGHT },
        { DOM_START, TextAlign::START },
    };
    auto index = BinarySearchFindIndex(textAlignTable, ArraySize(textAlignTable), align.c_str());
    return index < 0 ? TextAlign::CENTER : textAlignTable[index].value;
}
template<>
TextDirection Convert(const Ark_String& src)
{
    auto val = Converter::Convert<std::string>(src);
    static const LinearMapNode<TextDirection> textDirectionTable[] = {
        { DIR_AUTO, TextDirection::AUTO },
        { DIR_INHERIT, TextDirection::INHERIT },
        { DIR_LTR, TextDirection::LTR },
        { DIR_RTL, TextDirection::RTL },
    };
    auto index = BinarySearchFindIndex(textDirectionTable, ArraySize(textDirectionTable), val.c_str());
    return index < 0 ? TextDirection::LTR : textDirectionTable[index].value;
}
template<>
void AssignCast(std::optional<CompositeOperation>& dst, const Ark_String& src)
{
    auto str = Converter::Convert<std::string>(src);
    str = StringUtils::TrimStr(str);
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
const GENERATED_ArkUICanvasGradientAccessor* GetCanvasGradientAccessor();
const GENERATED_ArkUICanvasPatternAccessor* GetCanvasPatternAccessor();
const GENERATED_ArkUIMatrix2DAccessor* GetMatrix2DAccessor();

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
    LOGE("ARKOALA CanvasRendererAccessor::DrawImage0Impl where Ark_Union_ImageBitmap_PixelMap "
        " includes Ark_PixelMap which is partially implemented.");
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    if (!(peerImpl && image && dx && dy)) {
        LOGE("ARKOALA CanvasRendererAccessor::DrawImage0Impl Error Parameters");
        return;
    }
    double density = peerImpl->GetDensity();
    Ace::CanvasImage info {
        .flag = 0,
        .dx = static_cast<double>(Converter::Convert<float>(*dx)) * density,
        .dy = static_cast<double>(Converter::Convert<float>(*dy)) * density,
    };
    Converter::VisitUnion(
        *image,
        [peerImpl, info](const Ark_ImageBitmap& value) {
            ImageBitmapPeer* imageBitmapPeer = reinterpret_cast<ImageBitmapPeer*>(value);
            if (imageBitmapPeer) {
                peerImpl->TriggerDrawImageImpl(imageBitmapPeer->GetPixelMap(), info);
            }
        },
        [](const Ark_PixelMap& value) {
            LOGE("ARKOALA CanvasRendererAccessor::DrawImage0Impl PixelMap is not implemented");
        },
        []() {}
    );
}
void DrawImage1Impl(Ark_CanvasRenderer peer,
                    const Ark_Union_ImageBitmap_PixelMap* image,
                    const Ark_Number* dx,
                    const Ark_Number* dy,
                    const Ark_Number* dw,
                    const Ark_Number* dh)
{
    LOGE("ARKOALA CanvasRendererAccessor::DrawImage1Impl where Ark_Union_ImageBitmap_PixelMap "
        " includes Ark_PixelMap which is partially implemented.");
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    if (!(peerImpl && image && dx && dy && dw && dh)) {
        LOGE("ARKOALA CanvasRendererAccessor::DrawImage1Impl Error Parameters");
        return;
    }
    double density = peerImpl->GetDensity();
    Ace::CanvasImage info {
        .flag = 1,
        .dx = static_cast<double>(Converter::Convert<float>(*dx)) * density,
        .dy = static_cast<double>(Converter::Convert<float>(*dy)) * density,
        .dWidth = static_cast<double>(Converter::Convert<float>(*dw)) * density,
        .dHeight = static_cast<double>(Converter::Convert<float>(*dh)) * density,
    };
    Converter::VisitUnion(
        *image,
        [peerImpl, info](const Ark_ImageBitmap& value) {
            ImageBitmapPeer* imageBitmapPeer = reinterpret_cast<ImageBitmapPeer*>(value);
            if (imageBitmapPeer) {
                peerImpl->TriggerDrawImageImpl(imageBitmapPeer->GetPixelMap(), info);
            }
        },
        [](const Ark_PixelMap& value) {
            LOGE("ARKOALA CanvasRendererAccessor::DrawImage1Impl PixelMap is not implemented");
        },
        []() {}
    );
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
    LOGE("ARKOALA CanvasRendererAccessor::DrawImage2Impl where Ark_Union_ImageBitmap_PixelMap "
        " includes Ark_PixelMap which is partially implemented.");
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    if (!(peerImpl && image && sx && sy && sw && sh && dx && dy && dw && dh)) {
        LOGE("ARKOALA CanvasRendererAccessor::DrawImage2Impl Error Parameters");
        return;
    }
    double density = peerImpl->GetDensity();
    Ace::CanvasImage info {
        .flag = 2,
        .sx = static_cast<double>(Converter::Convert<float>(*sx)) * density,
        .sy = static_cast<double>(Converter::Convert<float>(*sy)) * density,
        .sWidth = static_cast<double>(Converter::Convert<float>(*sw)) * density,
        .sHeight = static_cast<double>(Converter::Convert<float>(*sh)) * density,
        .dx = static_cast<double>(Converter::Convert<float>(*dx)) * density,
        .dy = static_cast<double>(Converter::Convert<float>(*dy)) * density,
        .dWidth = static_cast<double>(Converter::Convert<float>(*dw)) * density,
        .dHeight = static_cast<double>(Converter::Convert<float>(*dh)) * density,
    };
    Converter::VisitUnion(
        *image,
        [peerImpl, info](const Ark_ImageBitmap& value) {
            ImageBitmapPeer* imageBitmapPeer = reinterpret_cast<ImageBitmapPeer*>(value);
            if (imageBitmapPeer) {
                peerImpl->TriggerDrawImageImpl(imageBitmapPeer->GetPixelMap(), info);
            }
        },
        [](const Ark_PixelMap& value) {
            LOGE("ARKOALA CanvasRendererAccessor::DrawImage2Impl PixelMap is not implemented");
        },
        []() {}
    );
}
void BeginPathImpl(Ark_CanvasRenderer peer)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    peerImpl->TriggerBeginPathImpl();
}
void Clip0Impl(Ark_CanvasRenderer peer,
               const Opt_String* fillRule)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    CHECK_NULL_VOID(fillRule);
    auto opt = Converter::OptConvert<std::string>(*fillRule);
    auto rule = opt && *opt == FILL_RULE_EVEN_ODD ? CanvasFillRule::EVENODD : CanvasFillRule::NONZERO;
    peerImpl->Clip(rule);
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
    auto opt = Converter::OptConvert<std::string>(*fillRule);
    auto rule = opt && *opt == FILL_RULE_EVEN_ODD ? CanvasFillRule::EVENODD : CanvasFillRule::NONZERO;
    auto pathImpl = reinterpret_cast<CanvasPathPeerImpl*>(path);
    CHECK_NULL_VOID(pathImpl);
    CHECK_NULL_VOID(pathImpl->path);
    peerImpl->Clip(rule, pathImpl->path);
}
void Fill0Impl(Ark_CanvasRenderer peer,
               const Opt_String* fillRule)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    CHECK_NULL_VOID(fillRule);
    auto opt = Converter::OptConvert<std::string>(*fillRule);
    auto rule = opt && *opt == FILL_RULE_EVEN_ODD ? CanvasFillRule::EVENODD : CanvasFillRule::NONZERO;
    peerImpl->Fill(rule);
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
    auto opt = Converter::OptConvert<std::string>(*fillRule);
    auto rule = opt && *opt == FILL_RULE_EVEN_ODD ? CanvasFillRule::EVENODD : CanvasFillRule::NONZERO;
    auto pathImpl = reinterpret_cast<CanvasPathPeerImpl*>(path);
    CHECK_NULL_VOID(pathImpl);
    CHECK_NULL_VOID(pathImpl->path);
    peerImpl->Fill(rule, pathImpl->path);
}
void Stroke0Impl(Ark_CanvasRenderer peer)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    peerImpl->TriggerStroke0Impl();
}
void Stroke1Impl(Ark_CanvasRenderer peer,
                 Ark_Path2D path)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    CHECK_NULL_VOID(path);
    CHECK_NULL_VOID(path);
    auto pathImpl = reinterpret_cast<CanvasPathPeerImpl*>(path);
    CHECK_NULL_VOID(pathImpl);
    CHECK_NULL_VOID(pathImpl->path);
    peerImpl->TriggerStroke1Impl(pathImpl->path);
}
Ark_CanvasGradient CreateLinearGradientImpl(Ark_CanvasRenderer peer,
                                            const Ark_Number* x0,
                                            const Ark_Number* y0,
                                            const Ark_Number* x1,
                                            const Ark_Number* y1)
{
    CHECK_NULL_RETURN(peer, nullptr);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_RETURN(x0, nullptr);
    CHECK_NULL_RETURN(y0, nullptr);
    CHECK_NULL_RETURN(x1, nullptr);
    CHECK_NULL_RETURN(y1, nullptr);
    double density = peerImpl->GetDensity();
    double cx0 = static_cast<double>(Converter::Convert<float>(*x0)) * density;
    double cy0 = static_cast<double>(Converter::Convert<float>(*y0)) * density;
    double cx1 = static_cast<double>(Converter::Convert<float>(*x1)) * density;
    double cy1 = static_cast<double>(Converter::Convert<float>(*y1)) * density;
    auto gradient = peerImpl->CreateLinearGradient(cx0, cy0, cx1, cy1);
    CHECK_NULL_RETURN(gradient, nullptr);
    auto canvasGradientPeer = reinterpret_cast<CanvasGradientPeer*>(GetCanvasGradientAccessor()->ctor());
    CHECK_NULL_RETURN(canvasGradientPeer, nullptr);
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
    auto bitmap = image;
    CHECK_NULL_RETURN(bitmap, invalid);
    auto opt = Converter::OptConvert<std::string>(*repetition);
    std::string repeat = opt ? *opt : EMPTY_STRING;
    auto pattern = std::make_shared<OHOS::Ace::Pattern>();
    pattern->SetImgSrc(bitmap->GetSrc());
    pattern->SetImageWidth(bitmap->GetWidth());
    pattern->SetImageHeight(bitmap->GetHeight());
    pattern->SetRepetition(repeat);
#if !defined(PREVIEW)
    auto pixelMap = bitmap->GetPixelMap();
    pattern->SetPixelMap(pixelMap);
#endif
    peerImpl->patterns[peerImpl->patternCount] = pattern;
    auto peerPattern = GetCanvasPatternAccessor()->ctor();
    CHECK_NULL_RETURN(peerPattern, invalid);
    peerPattern->SetCanvasRenderer(AceType::WeakClaim(peerImpl));
    peerPattern->SetId(peerImpl->patternCount);
    peerPattern->SetUnit(peerImpl->GetUnit());
    peerImpl->patternCount++;
    return Converter::ArkValue<Opt_CanvasPattern>(peerPattern);
}
Ark_CanvasGradient CreateRadialGradientImpl(Ark_CanvasRenderer peer,
                                            const Ark_Number* x0,
                                            const Ark_Number* y0,
                                            const Ark_Number* r0,
                                            const Ark_Number* x1,
                                            const Ark_Number* y1,
                                            const Ark_Number* r1)
{
    CHECK_NULL_RETURN(peer, nullptr);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_RETURN(x0, nullptr);
    CHECK_NULL_RETURN(y0, nullptr);
    CHECK_NULL_RETURN(r0, nullptr);
    CHECK_NULL_RETURN(x1, nullptr);
    CHECK_NULL_RETURN(y1, nullptr);
    CHECK_NULL_RETURN(r1, nullptr);
    double density = peerImpl->GetDensity();
    double cx0 = static_cast<double>(Converter::Convert<float>(*x0)) * density;
    double cy0 = static_cast<double>(Converter::Convert<float>(*y0)) * density;
    double cr0 = static_cast<double>(Converter::Convert<float>(*r0)) * density;
    double cx1 = static_cast<double>(Converter::Convert<float>(*x1)) * density;
    double cy1 = static_cast<double>(Converter::Convert<float>(*y1)) * density;
    double cr1 = static_cast<double>(Converter::Convert<float>(*r1)) * density;
    std::vector<double> params;
    params.insert(params.end(), { cx0, cy0, cr0, cx1, cy1, cr1 });
    auto gradient = peerImpl->CreateRadialGradient(params);
    CHECK_NULL_RETURN(gradient, nullptr);
    auto canvasGradientPeer = reinterpret_cast<CanvasGradientPeer*>(GetCanvasGradientAccessor()->ctor());
    CHECK_NULL_RETURN(canvasGradientPeer, nullptr);
    canvasGradientPeer->SetGradient(gradient);
    return canvasGradientPeer;
}
Ark_CanvasGradient CreateConicGradientImpl(Ark_CanvasRenderer peer,
                                           const Ark_Number* startAngle,
                                           const Ark_Number* x,
                                           const Ark_Number* y)
{
    CHECK_NULL_RETURN(peer, nullptr);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_RETURN(startAngle, nullptr);
    CHECK_NULL_RETURN(x, nullptr);
    CHECK_NULL_RETURN(y, nullptr);
    double density = peerImpl->GetDensity();
    double ca = static_cast<double>(Converter::Convert<float>(*startAngle));
    double cx = static_cast<double>(Converter::Convert<float>(*x)) * density;
    double cy = static_cast<double>(Converter::Convert<float>(*y)) * density;
    auto gradient = peerImpl->CreateConicGradient(ca, cx, cy);
    CHECK_NULL_RETURN(gradient, nullptr);
    auto canvasGradientPeer = reinterpret_cast<CanvasGradientPeer*>(GetCanvasGradientAccessor()->ctor());
    CHECK_NULL_RETURN(canvasGradientPeer, nullptr);
    canvasGradientPeer->SetGradient(gradient);
    return canvasGradientPeer;
}
Ark_ImageData CreateImageData0Impl(Ark_CanvasRenderer peer,
                                   const Ark_Number* sw,
                                   const Ark_Number* sh)
{
    CHECK_NULL_RETURN(peer, nullptr);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, nullptr);
    CHECK_NULL_RETURN(sw, nullptr);
    CHECK_NULL_RETURN(sh, nullptr);
    double density = peerImpl->GetDensity();
    auto width = static_cast<double>(Converter::Convert<float>(*sw)) * density + DIFF;
    auto height = static_cast<double>(Converter::Convert<float>(*sh)) * density + DIFF;
    ImageSize imageSize = peerImpl->GetImageSize(0, 0, width, height);
    auto finalWidth = static_cast<uint32_t>(std::abs(imageSize.width));
    auto finalHeight = static_cast<uint32_t>(std::abs(imageSize.height));
    peerImpl->ClearImageData();
    if (finalHeight > 0 && finalWidth > (UINT32_MAX / finalHeight)) {
        LOGE("ARKOALA CanvasRendererPeerImpl::GetImageDataImpl Integer Overflow!!! "
             "The product of finalHeight and finalWidth is too big.");
    } else {
        peerImpl->imageData.dirtyWidth = finalWidth;
        peerImpl->imageData.dirtyHeight = finalHeight;
        for (uint32_t idx = 0; idx < finalWidth * finalHeight; ++idx) {
            peerImpl->imageData.data.push_back(COLOR_WHITE);
        }
    }
    return ImageDataPeer::Create(peerImpl->imageData);
}
Ark_ImageData CreateImageData1Impl(Ark_CanvasRenderer peer,
                                   Ark_ImageData imagedata)
{
    CHECK_NULL_RETURN(peer, nullptr);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, nullptr);
    CHECK_NULL_RETURN(imagedata, nullptr);
    peerImpl->imageData = imagedata->value;
    return ImageDataPeer::Create(peerImpl->imageData);
}
Ark_ImageData GetImageDataImpl(Ark_CanvasRenderer peer,
                               const Ark_Number* sx,
                               const Ark_Number* sy,
                               const Ark_Number* sw,
                               const Ark_Number* sh)
{
    CHECK_NULL_RETURN(peer, nullptr);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, nullptr);
    CHECK_NULL_RETURN(sx, nullptr);
    CHECK_NULL_RETURN(sy, nullptr);
    CHECK_NULL_RETURN(sw, nullptr);
    CHECK_NULL_RETURN(sh, nullptr);
    double density = peerImpl->GetDensity();
    auto x = static_cast<double>(Converter::Convert<float>(*sx)) * density;
    auto y = static_cast<double>(Converter::Convert<float>(*sy)) * density;
    auto width = static_cast<double>(Converter::Convert<float>(*sw)) * density + DIFF;
    auto height = static_cast<double>(Converter::Convert<float>(*sh)) * density + DIFF;
    ImageSize imageSize = peerImpl->GetImageSize(x, y, width, height);
    auto finalWidth = static_cast<uint32_t>(std::abs(imageSize.width));
    auto finalHeight = static_cast<uint32_t>(std::abs(imageSize.height));
    peerImpl->ClearImageData();
    if (finalHeight > 0 && finalWidth > (UINT32_MAX / finalHeight)) {
        LOGE("ARKOALA CanvasRendererPeerImpl::GetImageDataImpl Integer Overflow!!! "
             "The product of finalHeight and finalWidth is too big.");
        return ImageDataPeer::Create(peerImpl->imageData);
    }
    std::unique_ptr<Ace::ImageData> canvasData = peerImpl->GetImageData(imageSize);
    CHECK_NULL_RETURN(canvasData, nullptr);
    if (canvasData) {
        peerImpl->imageData = *canvasData;
    }
    return ImageDataPeer::Create(peerImpl->imageData);
}
Ark_PixelMap GetPixelMapImpl(Ark_CanvasRenderer peer,
                             const Ark_Number* sx,
                             const Ark_Number* sy,
                             const Ark_Number* sw,
                             const Ark_Number* sh)
{
#ifdef PIXEL_MAP_SUPPORTED
    CHECK_NULL_RETURN(peer, nullptr);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, nullptr);
    CHECK_NULL_RETURN(sx, nullptr);
    CHECK_NULL_RETURN(sy, nullptr);
    CHECK_NULL_RETURN(sw, nullptr);
    CHECK_NULL_RETURN(sh, nullptr);
    double density = peerImpl->GetDensity();
    auto x = static_cast<double>(Converter::Convert<float>(*sx)) * density;
    auto y = static_cast<double>(Converter::Convert<float>(*sy)) * density;
    auto width = static_cast<double>(Converter::Convert<float>(*sw)) * density + DIFF;
    auto height = static_cast<double>(Converter::Convert<float>(*sh)) * density + DIFF;
    ImageSize imageSize = peerImpl->GetImageSize(x, y, width, height);
    peerImpl->ClearImageData();
    peerImpl->GetPixelMap(imageSize);
    return {};
#else
    LOGE("ARKOALA CanvasRendererAccessor::GetPixelMapImpl PixelMap is not supported on current platform.");
    return {};
#endif
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
    ImageSizeExt ext;
    auto src = imagedata->value;
    ext.x = ConvertDimension(peerImpl, *dx);
    ext.y = ConvertDimension(peerImpl, *dy);
    peerImpl->PutImageData(src, ext);
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
    ImageSizeExt ext;
    auto src = imagedata->value;
    ext.x = ConvertDimension(peerImpl, *dx);
    ext.y = ConvertDimension(peerImpl, *dy);
    ext.dirtyX = ConvertDimension(peerImpl, *dirtyX);
    ext.dirtyY = ConvertDimension(peerImpl, *dirtyY);
    ext.dirtyWidth = ConvertDimension(peerImpl, *dirtyWidth);
    ext.dirtyHeight = ConvertDimension(peerImpl, *dirtyHeight);
    peerImpl->PutImageData(src, ext);
}
Array_Number GetLineDashImpl(Ark_CanvasRenderer peer)
{
    CHECK_NULL_RETURN(peer, {});
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, {});
    peerImpl->TriggerGetLineDashImpl();
    LOGE("ARKOALA CanvasRendererAccessor::GetLineDashImpl method should return object with specific type");
    return {};
}
void SetLineDashImpl(Ark_CanvasRenderer peer,
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
    double density = peerImpl->GetDensity();
    std::vector<double> dst;
    std::transform(src.begin(), src.end(), std::back_inserter(dst),
        [density](auto val) { return static_cast<double>(val) * density; });
    peerImpl->TriggerSetLineDashImpl(dst);
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
    double density = peerImpl->GetDensity();
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
    peerImpl->TriggerClearRectImpl(rect * density);
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
    double density = peerImpl->GetDensity();
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
    peerImpl->TriggerFillRectImpl(rect * density);
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
    double density = peerImpl->GetDensity();
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
    peerImpl->TriggerStrokeRectImpl(rect * density);
}
void RestoreImpl(Ark_CanvasRenderer peer)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    peerImpl->TriggerRestoreImpl();
}
void SaveImpl(Ark_CanvasRenderer peer)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    peerImpl->TriggerSaveImpl();
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
    double density = peerImpl->GetDensity();
    auto valueText = Converter::Convert<std::string>(*text);
    auto valueX = static_cast<double>(Converter::Convert<float>(*x)) * density;
    auto valueY = static_cast<double>(Converter::Convert<float>(*y)) * density;
    auto opt = Converter::OptConvert<float>(*maxWidth);

    std::optional<double> optMaxWidth = std::nullopt;
    if (opt.has_value()) {
        optMaxWidth = static_cast<double>(*opt) * density;
    }
    peerImpl->TriggerFillTextImpl(valueText, valueX, valueY, optMaxWidth);
}
Ark_TextMetrics MeasureTextImpl(Ark_CanvasRenderer peer,
                                const Ark_String* text)
{
    CHECK_NULL_RETURN(peer, {});
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, {});
    CHECK_NULL_RETURN(text, {});
    auto content = Converter::Convert<std::string>(*text);
    auto opt = peerImpl->GetTextMetrics(content);
    if (opt.has_value()) {
        return Converter::ArkValue<Ark_TextMetrics>(opt.value());
    }
    LOGE("ARKOALA CanvasRendererAccessor::MeasureTextImpl return type Ark_NativePointer "
         "should be replaced with an accessor type for TextMetrics.");
    return {};
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
    double density = peerImpl->GetDensity();
    auto valueText = Converter::Convert<std::string>(*text);
    auto valueX = static_cast<double>(Converter::Convert<float>(*x)) * density;
    auto valueY = static_cast<double>(Converter::Convert<float>(*y)) * density;
    auto opt = Converter::OptConvert<float>(*maxWidth);

    std::optional<double> optMaxWidth = std::nullopt;
    if (opt.has_value()) {
        optMaxWidth = static_cast<double>(*opt) * density;
    }
    peerImpl->TriggerStrokeTextImpl(valueText, valueX, valueY, optMaxWidth);
}
Ark_Matrix2D GetTransformImpl(Ark_CanvasRenderer peer)
{
    CHECK_NULL_RETURN(peer, nullptr);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, nullptr);
    auto matrixPeer = reinterpret_cast<Matrix2DPeer*>(GetMatrix2DAccessor()->ctor());
    CHECK_NULL_RETURN(matrixPeer, nullptr);
    if (Container::IsCurrentUseNewPipeline()) {
        auto opt = peerImpl->GetTransform();
        if (opt) {
            matrixPeer->transform = *opt;
        }
    }
    return matrixPeer;
}
void ResetTransformImpl(Ark_CanvasRenderer peer)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    peerImpl->TriggerResetTransformImpl();
}
void RotateImpl(Ark_CanvasRenderer peer,
                const Ark_Number* angle)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(angle);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);

    auto rotateAngle = static_cast<double>(Converter::Convert<float>(*angle));
    peerImpl->TriggerRotateImpl(rotateAngle);
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
    if (scaleX < SCALE_LIMIT_MIN || scaleY < SCALE_LIMIT_MIN) {
        return;
    }
    peerImpl->TriggerScaleImpl(scaleX, scaleY);
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
    CHECK_NULL_VOID(a);
    CHECK_NULL_VOID(b);
    CHECK_NULL_VOID(c);
    CHECK_NULL_VOID(d);
    CHECK_NULL_VOID(e);
    CHECK_NULL_VOID(f);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    double density = peerImpl->GetDensity();
    auto param = TransformParam {
        .scaleX = static_cast<double>(Converter::Convert<float>(*a)),
        .skewX = static_cast<double>(Converter::Convert<float>(*c)),
        .skewY = static_cast<double>(Converter::Convert<float>(*b)),
        .scaleY = static_cast<double>(Converter::Convert<float>(*d)),
        .translateX = static_cast<double>(Converter::Convert<float>(*e)) * density,
        .translateY = static_cast<double>(Converter::Convert<float>(*f)) * density};
    if (param.scaleX < SCALE_LIMIT_MIN || param.scaleY < SCALE_LIMIT_MIN) {
        return;
    }
    peerImpl->TriggerSetTransformImpl(param);
}
void SetTransform1Impl(Ark_CanvasRenderer peer,
                       const Opt_Matrix2D* transform)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    CHECK_NULL_VOID(transform);
    auto opt = Converter::OptConvert<Ark_Matrix2D>(*transform);
    CHECK_NULL_VOID(opt);
    auto matrixPeer = opt.value();
    CHECK_NULL_VOID(matrixPeer);
    auto param = matrixPeer->transform;
    if (LessNotEqual(param.scaleX, SCALE_LIMIT_MIN) || LessNotEqual(param.scaleY, SCALE_LIMIT_MIN)) {
        return;
    }
    peerImpl->TriggerSetTransformImpl(param);
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
    double density = peerImpl->GetDensity();
    auto param = TransformParam {
        .scaleX = static_cast<double>(Converter::Convert<float>(*a)),
        .skewX = static_cast<double>(Converter::Convert<float>(*b)),
        .skewY = static_cast<double>(Converter::Convert<float>(*c)),
        .scaleY = static_cast<double>(Converter::Convert<float>(*d)),
        .translateX = static_cast<double>(Converter::Convert<float>(*e)) * density,
        .translateY = static_cast<double>(Converter::Convert<float>(*f)) * density};
    if (LessNotEqual(param.scaleX, SCALE_LIMIT_MIN) || LessNotEqual(param.scaleY, SCALE_LIMIT_MIN)) {
        return;
    }
    peerImpl->TriggerTransformImpl(param);
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
    double density = peerImpl->GetDensity();
    auto transX = static_cast<double>(Converter::Convert<float>(*x)) * density;
    auto transY = static_cast<double>(Converter::Convert<float>(*y)) * density;
    peerImpl->TriggerTranslateImpl(transX, transY);
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
    CHECK_NULL_VOID(bitmap);
    auto bitmapPeer = bitmap;
    CHECK_NULL_VOID(bitmapPeer);
#ifdef PIXEL_MAP_SUPPORTED
    auto pixelMap = bitmapPeer->GetPixelMap();
    CHECK_NULL_VOID(pixelMap);
    peerImpl->TriggerTransferFromImageBitmapImpl(pixelMap);
#else
    auto width = bitmapPeer->GetWidth();
    auto height = bitmapPeer->GetHeight();
    if (NonPositive(width) || (NonPositive(height))) {
        return;
    }
    peerImpl->TriggerTransferFromImageBitmapImpl(width, height);
#endif
}
void SaveLayerImpl(Ark_CanvasRenderer peer)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    peerImpl->TriggerSaveLayerImpl();
}
void RestoreLayerImpl(Ark_CanvasRenderer peer)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    peerImpl->TriggerRestoreLayerImpl();
}
void ResetImpl(Ark_CanvasRenderer peer)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    peerImpl->TriggerResetImpl();
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
    if (alpha < ALPHA_LIMIT_MIN || alpha > ALPHA_LIMIT_MAX) {
        return;
    }
    peerImpl->TriggerSetGlobalAlphaImpl(alpha);
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

    auto opt = Converter::OptConvert<CompositeOperation>(*globalCompositeOperation);
    CHECK_NULL_VOID(opt);
    peerImpl->TriggerSetGlobalCompositeOperationImpl(*opt);
}
Ark_Union_String_Number_CanvasGradient_CanvasPattern GetFillStyleImpl(Ark_CanvasRenderer peer)
{
    return {};
}
void SetFillStyleImpl(Ark_CanvasRenderer peer,
                      const Ark_Union_String_Number_CanvasGradient_CanvasPattern* fillStyle)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    CHECK_NULL_VOID(fillStyle);
    LOGE("ARKOALA CanvasRendererAccessor::SetStrokeStyleImpl input Union includes same type members");
    Converter::VisitUnion(
        *fillStyle,
        [peerImpl](const Ark_String& value) {
            auto colorStr = Converter::Convert<std::string>(value);
            Color color;
            if (Color::ParseColorString(colorStr, color)) {
                peerImpl->TriggerSetFillStyleImpl(color);
            }
        },
        [peerImpl](const Ark_Number& value) {
            auto colorNum = Converter::Convert<uint32_t>(value);
            peerImpl->TriggerSetFillStyleImpl(Color(ColorAlphaAdapt(colorNum)));
        },
        [peerImpl](const Ark_CanvasGradient& value) {
            auto gradientPeer = reinterpret_cast<CanvasGradientPeer*>(value);
            if (gradientPeer) {
                auto gradient = gradientPeer->GetGradient();
                peerImpl->TriggerSetFillStyleImpl(gradient);
            }
        },
        [peerImpl](const Ark_CanvasPattern& value) {
            auto canvasPatternPeer = reinterpret_cast<CanvasPatternPeer*>(value);
            if (canvasPatternPeer) {
                int32_t patternId = canvasPatternPeer->GetId();
                auto pattern = peerImpl->patterns[patternId];
                peerImpl->TriggerSetFillStyleImpl(pattern);
            }
        },
        []() {}
    );
}
Ark_Union_String_Number_CanvasGradient_CanvasPattern GetStrokeStyleImpl(Ark_CanvasRenderer peer)
{
    return {};
}
void SetStrokeStyleImpl(Ark_CanvasRenderer peer,
                        const Ark_Union_String_Number_CanvasGradient_CanvasPattern* strokeStyle)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    CHECK_NULL_VOID(strokeStyle);
    LOGE("ARKOALA CanvasRendererAccessor::SetStrokeStyleImpl input Union includes same type members");
    Converter::VisitUnion(
        *strokeStyle,
        [peerImpl](const Ark_String& value) {
            auto colorStr = Converter::Convert<std::string>(value);
            Color color;
            if (Color::ParseColorString(colorStr, color)) {
                peerImpl->TriggerSetStrokeStyleImpl(color);
            }
        },
        [peerImpl](const Ark_Number& value) {
            auto colorNum = Converter::Convert<uint32_t>(value);
            peerImpl->TriggerSetStrokeStyleImpl(Color(ColorAlphaAdapt(colorNum)));
        },
        [peerImpl](const Ark_CanvasGradient& value) {
            auto gradientPeer = reinterpret_cast<CanvasGradientPeer*>(value);
            if (gradientPeer) {
                auto gradient = gradientPeer->GetGradient();
                peerImpl->TriggerSetStrokeStyleImpl(gradient);
            }
        },
        [peerImpl](const Ark_CanvasPattern& value) {
            auto canvasPatternPeer = reinterpret_cast<CanvasPatternPeer*>(value);
            if (canvasPatternPeer) {
                int32_t patternId = canvasPatternPeer->GetId();
                auto pattern = peerImpl->patterns[patternId];
                peerImpl->TriggerSetStrokeStyleImpl(pattern);
            }
        },
        []() {}
    );
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

    auto filterValue = Converter::Convert<std::string>(*filter);
    if (filterValue.length() == 0) {
        return;
    }
    peerImpl->TriggerSetFilterImpl(filterValue);
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
    peerImpl->TriggerSetImageSmoothingEnabledImpl(enabled);
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
    LOGE("ARKOALA CanvasRendererAccessor::GetLineCapImpl return type Ark_NativePointer "
        "should be replaced with a valid ark enum for CanvasLineCap type.");
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
    CHECK_NULL_RETURN(peer, Converter::ArkValue<Ark_Number>(0));
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, Converter::ArkValue<Ark_Number>(0));

    double offset = peerImpl->TriggerGetLineDashOffsetImpl();
    LOGE("ARKOALA CanvasRendererAccessor::GetLineDashOffsetImpl return type Ark_Int32 "
         "should be replaced with a valid Ark_Number for LineDashParam offset double type.");
    return Converter::ArkValue<Ark_Number>(static_cast<int32_t>(offset));
}
void SetLineDashOffsetImpl(Ark_CanvasRenderer peer,
                           const Ark_Number* lineDashOffset)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(lineDashOffset);
    auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    double density = peerImpl->GetDensity();
    auto offset = static_cast<double>(Converter::Convert<float>(*lineDashOffset)) * density;
    peerImpl->TriggerSetLineDashOffsetImpl(offset);
}
Ark_String GetLineJoinImpl(Ark_CanvasRenderer peer)
{
    LOGE("ARKOALA CanvasRendererAccessor::GetLineJoinImpl return type Ark_NativePointer "
        "should be replaced with a valid ark enum for CanvasLineJoin type.");
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
    double density = peerImpl->GetDensity();
    auto width = static_cast<double>(Converter::Convert<float>(*lineWidth)) * density;
    peerImpl->TriggerSetLineWidthImpl(width);
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
    peerImpl->TriggerSetMiterLimitImpl(limit);
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
    peerImpl->TriggerSetShadowBlurImpl(blur);
}
Ark_String GetShadowColorImpl(Ark_CanvasRenderer peer)
{
    LOGE("ARKOALA CanvasRendererAccessor::GetShadowColorImpl method should return object with specific type");
    return {};
}
void SetShadowColorImpl(Ark_CanvasRenderer peer,
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
    double density = peerImpl->GetDensity();
    auto offsetX = static_cast<double>(Converter::Convert<float>(*shadowOffsetX)) * density;
    peerImpl->TriggerSetShadowOffsetXImpl(offsetX);
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
    double density = peerImpl->GetDensity();
    auto offsetY = static_cast<double>(Converter::Convert<float>(*shadowOffsetY)) * density;
    peerImpl->TriggerSetShadowOffsetYImpl(offsetY);
}
Ark_String GetDirectionImpl(Ark_CanvasRenderer peer)
{
    LOGE("ARKOALA CanvasRendererAccessor::GetDirectionImpl return type Ark_NativePointer "
        "should be replaced with a valid ark enum for CanvasDirection type.");
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
    auto dir = Converter::Convert<TextDirection>(*direction);
    peerImpl->SetTextDirection(dir);
}
Ark_String GetFontImpl(Ark_CanvasRenderer peer)
{
    LOGE("ARKOALA CanvasRendererAccessor::GetFontImpl method should return object with specific type");
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
    LOGE("ARKOALA CanvasRendererAccessor::GetTextAlignImpl return type Ark_NativePointer "
        "should be replaced with a valid ark enum for CanvasTextAlign type.");
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
    auto align = Converter::Convert<TextAlign>(*textAlign);
    peerImpl->SetTextAlign(align);
}
Ark_String GetTextBaselineImpl(Ark_CanvasRenderer peer)
{
    LOGE("ARKOALA CanvasRendererAccessor::GetTextBaselineImpl return type Ark_NativePointer "
        "should be replaced with a valid ark enum for CanvasTextBaseline type.");
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
    auto baseLine = Converter::Convert<TextBaseline>(*textBaseline);
    peerImpl->SetTextBaseline(baseLine);
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

struct CanvasRendererPeer {
    virtual ~CanvasRendererPeer() = default;
};
}
