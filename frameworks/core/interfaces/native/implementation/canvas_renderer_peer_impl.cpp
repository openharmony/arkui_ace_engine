/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "canvas_renderer_peer_impl.h"

#include "arkoala_api_generated.h"
#include "canvas_pattern_peer.h"
#include "image_bitmap_peer_impl.h"
#include "pixel_map_peer.h"
#include "core/pipeline/base/constants.h"

namespace OHOS::Ace::NG {
namespace {
const std::set<std::string> FONT_WEIGHTS = {
    "100",
    "200",
    "300",
    "400",
    "500",
    "600",
    "700",
    "800",
    "900",
    "bold",
    "bolder",
    "lighter",
    "medium",
    "normal",
    "regular",
};
const std::set<std::string> FONT_STYLES = { "italic", "oblique", "normal" };
const std::set<std::string> FONT_FAMILIES = { "sans-serif", "serif", "monospace" };
const std::set<std::string> QUALITY_TYPE = { "low", "medium", "high" };
constexpr Dimension DEFAULT_FONT_SIZE = 14.0_px;
constexpr double DEFAULT_QUALITY = 0.92;
constexpr uint32_t COLOR_ALPHA_OFFSET = 24;
constexpr uint32_t COLOR_ALPHA_VALUE = 0xFF000000;
constexpr double DIFF = 1e-10;
constexpr uint32_t PIXEL_SIZE = 4;
constexpr int32_t ALPHA_INDEX = 3;
constexpr auto TEXT_FONT_STYLE_ITALIC = "italic";
const std::unordered_map<std::string, LineCapStyle> LINE_CAP_MAP = {
    { "butt", LineCapStyle::BUTT },
    { "round", LineCapStyle::ROUND },
    { "square", LineCapStyle::SQUARE },
};
const std::unordered_map<std::string, LineJoinStyle> LINE_JOIN_MAP = {
    { "bevel", LineJoinStyle::BEVEL },
    { "miter", LineJoinStyle::MITER },
    { "round", LineJoinStyle::ROUND },
};
const double ERROR_VALUE = 0;
const std::string ERROR_STRING = "";
const auto MULTI_BY_2 = 2;
const auto EVEN_BY_2 = 2;

template<typename T>
inline T ConvertStrToEnum(const char* key, const LinearMapNode<T>* map, size_t length, T defaultValue)
{
    int64_t index = BinarySearchFindIndex(map, length, key);
    return index != -1 ? map[index].value : defaultValue;
}
uint32_t ColorAlphaAdapt(uint32_t origin)
{
    uint32_t result = origin;
    if ((origin >> COLOR_ALPHA_OFFSET) == 0) {
        result = origin | COLOR_ALPHA_VALUE;
    }
    return result;
}
Ace::FontWeight ConvertStrToFontWeight(
    const std::string& weight, Ace::FontWeight defaultFontWeight = FontWeight::NORMAL)
{
    return StringUtils::StringToFontWeight(weight, defaultFontWeight);
}
Ace::FontStyle ConvertStrToFontStyle(const std::string& fontStyle)
{
    return fontStyle == TEXT_FONT_STYLE_ITALIC ? Ace::FontStyle::ITALIC : Ace::FontStyle::NORMAL;
}
inline std::vector<std::string> ConvertStrToFontFamilies(const std::string& family)
{
    std::vector<std::string> fontFamilies;
    std::stringstream stream(family);
    std::string fontFamily;
    while (getline(stream, fontFamily, ',')) {
        fontFamilies.emplace_back(fontFamily);
    }
    return fontFamilies;
}
} // namespace
} // namespace OHOS::Ace::NG
namespace OHOS::Ace::NG::GeneratedModifier {
std::unordered_map<int32_t, std::shared_ptr<Ace::Pattern>> CanvasRendererPeerImpl::pattern_;
unsigned int CanvasRendererPeerImpl::patternCount_ = 0;
CanvasRendererPeerImpl::CanvasRendererPeerImpl()
{
    instanceId_ = Container::CurrentIdSafely();
    density_ = PipelineBase::GetCurrentDensity();
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_THIRTEEN)) {
    }
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_FOURTEEN)) {
        isJudgeSpecialValue_ = true;
    }
    auto pipeline = PipelineBase::GetCurrentContextSafely();
    if (pipeline) {
        densityCallbackId_ = pipeline->RegisterDensityChangedCallback([self = WeakClaim(this)](double density) {
            auto canvasRender = self.Upgrade();
            CHECK_NULL_VOID(canvasRender);
            canvasRender->density_ = density;
            canvasRender->SetDensity();
        });
    }
}
CanvasRendererPeerImpl::~CanvasRendererPeerImpl()
{
    ContainerScope scope(instanceId_);
    auto pipeline = PipelineBase::GetCurrentContextSafely();
    if (pipeline) {
        pipeline->UnregisterDensityChangedCallback(densityCallbackId_);
    }
}
RefPtr<CanvasPath2D> CanvasRendererPeerImpl::MakePath2D()
{
    return AceType::MakeRefPtr<CanvasPath2D>();
}
void CanvasRendererPeerImpl::DrawImage(ImageBitmapPeer* bitmap, const DrawImageParam& params)
{
    CHECK_NULL_VOID(renderingContext2DModel_);
    Ace::CanvasImage image;
    ExtractInfoToImage(image, params, true);
    image.instanceId = bitmap->GetInstanceId();

    Ace::ImageInfo imageInfo;
#if !defined(PREVIEW)
    imageInfo.pixelMap = bitmap->GetPixelMap();
    CHECK_NULL_VOID(imageInfo.pixelMap);
    imageInfo.image = image;
    renderingContext2DModel_->DrawPixelMap(imageInfo);
#else
    image.src = bitmap->GetSrc();
    image.imageData = bitmap->GetImageData();
    imageInfo.image = image;
    imageInfo.imgWidth = bitmap->GetWidth();
    imageInfo.imgHeight = bitmap->GetHeight();
    renderingContext2DModel_->DrawImage(imageInfo);
#endif
}
void CanvasRendererPeerImpl::DrawSvgImage(ImageBitmapPeer* bitmap, const DrawImageParam& params)
{
    CHECK_NULL_VOID(renderingContext2DModel_);
    Ace::CanvasImage image;
    ExtractInfoToImage(image, params, true);
    image.instanceId = bitmap->GetInstanceId();

    Ace::ImageInfo imageInfo;
    imageInfo.image = image;
    imageInfo.svgDom = bitmap->GetSvgDom();
    CHECK_NULL_VOID(imageInfo.svgDom);
    imageInfo.imageFit = bitmap->GetImageFit();
    renderingContext2DModel_->DrawSvgImage(imageInfo);
}
void CanvasRendererPeerImpl::DrawPixelMap(PixelMapPeer* pixelMap, const DrawImageParam& params)
{
    CHECK_NULL_VOID(renderingContext2DModel_);
    CHECK_NULL_VOID(pixelMap);
#if !defined(PREVIEW)
    Ace::CanvasImage image;
    ExtractInfoToImage(image, params, false);

    Ace::ImageInfo imageInfo;
    imageInfo.image = image;
    imageInfo.pixelMap = pixelMap->pixelMap;
    CHECK_NULL_VOID(imageInfo.pixelMap);
    renderingContext2DModel_->DrawPixelMap(imageInfo);
#endif
}
void CanvasRendererPeerImpl::BeginPath()
{
    CHECK_NULL_VOID(renderingContext2DModel_);
    renderingContext2DModel_->BeginPath();
}
void CanvasRendererPeerImpl::Clip(const std::optional<std::string>& ruleStr)
{
    CHECK_NULL_VOID(renderingContext2DModel_);
    auto fillRule = CanvasFillRule::NONZERO;
    // clip(fillRule?: CanvasFillRule): void
    if (ruleStr) {
        fillRule = *ruleStr == "evenodd" ? CanvasFillRule::EVENODD : CanvasFillRule::NONZERO;
    }
    renderingContext2DModel_->SetClipRuleForPath(fillRule);
}
void CanvasRendererPeerImpl::Clip(const std::optional<std::string>& ruleStr, const RefPtr<CanvasPath2D>& path)
{
    CHECK_NULL_VOID(renderingContext2DModel_);
    auto fillRule = CanvasFillRule::NONZERO;
    if (!path) {
        // clip(fillRule?: CanvasFillRule): void
        if (ruleStr) {
            fillRule = *ruleStr == "evenodd" ? CanvasFillRule::EVENODD : CanvasFillRule::NONZERO;
        }
        renderingContext2DModel_->SetClipRuleForPath(fillRule);
    } else {
        // clip(path: Path2D, fillRule?: CanvasFillRule): void
        if (ruleStr) {
            fillRule = *ruleStr == "evenodd" ? CanvasFillRule::EVENODD : CanvasFillRule::NONZERO;
        }
        renderingContext2DModel_->SetClipRuleForPath2D(fillRule, path);
    }
}
void CanvasRendererPeerImpl::Fill(const std::optional<std::string>& ruleStr)
{
    CHECK_NULL_VOID(renderingContext2DModel_);
    auto fillRule = CanvasFillRule::NONZERO;
    // fill(fillRule?: CanvasFillRule): void
    if (ruleStr) {
        fillRule = *ruleStr == "evenodd" ? CanvasFillRule::EVENODD : CanvasFillRule::NONZERO;
    }
    renderingContext2DModel_->SetFillRuleForPath(fillRule);
}
void CanvasRendererPeerImpl::Fill(const std::optional<std::string>& ruleStr, const RefPtr<CanvasPath2D>& path)
{
    CHECK_NULL_VOID(renderingContext2DModel_);
    auto fillRule = CanvasFillRule::NONZERO;
    if (!path) {
        // fill(fillRule?: CanvasFillRule): void
        if (ruleStr) {
            fillRule = *ruleStr == "evenodd" ? CanvasFillRule::EVENODD : CanvasFillRule::NONZERO;
        }
        renderingContext2DModel_->SetFillRuleForPath(fillRule);
    } else {
        // fill(path: Path2D, fillRule?: CanvasFillRule): void
        if (ruleStr) {
            fillRule = *ruleStr == "evenodd" ? CanvasFillRule::EVENODD : CanvasFillRule::NONZERO;
        }
        renderingContext2DModel_->SetFillRuleForPath2D(fillRule, path);
    }
}
void CanvasRendererPeerImpl::Stroke()
{
    CHECK_NULL_VOID(renderingContext2DModel_);
    renderingContext2DModel_->SetStrokeRuleForPath(CanvasFillRule::NONZERO);
}
void CanvasRendererPeerImpl::Stroke(const RefPtr<CanvasPath2D>& path)
{
    CHECK_NULL_VOID(renderingContext2DModel_);
    if (!path) {
        renderingContext2DModel_->SetStrokeRuleForPath(CanvasFillRule::NONZERO);
    } else {
        renderingContext2DModel_->SetStrokeRuleForPath2D(CanvasFillRule::NONZERO, path);
    }
}
std::shared_ptr<OHOS::Ace::Gradient> CanvasRendererPeerImpl::CreateLinearGradient(
    double x0, double y0, double x1, double y1)
{
    if (IfJudgeSpecialValue(x0) && IfJudgeSpecialValue(y0) && IfJudgeSpecialValue(x1) && IfJudgeSpecialValue(y1)) {
        double density = GetDensity();
        auto gradient = std::make_shared<Ace::Gradient>();
        gradient->SetType(Ace::GradientType::LINEAR);
        gradient->SetBeginOffset(Offset(x0 * density, y0 * density));
        gradient->SetEndOffset(Offset(x1 * density, y1 * density));
        return gradient;
    }
    return nullptr;
}
void CanvasRendererPeerImpl::CreatePattern(
    ImageBitmapPeer* bitmap, CanvasPatternPeer* canvasPattern, std::optional<std::string>& repetition)
{
    CHECK_NULL_VOID(bitmap);
    CHECK_NULL_VOID(canvasPattern);
    std::string repeat;
    if (repetition) {
        repeat = repetition.value();
    }
    auto pattern = std::make_shared<Ace::Pattern>();
    pattern->SetImgSrc(bitmap->GetSrc());
    pattern->SetImageWidth(bitmap->GetWidth());
    pattern->SetImageHeight(bitmap->GetHeight());
    pattern->SetRepetition(repeat);
#if !defined(PREVIEW)
    auto pixelMap = bitmap->GetPixelMap();
    pattern->SetPixelMap(pixelMap);
#endif
    pattern_[patternCount_] = pattern;
    canvasPattern->SetCanvasRenderer(AceType::WeakClaim(this));
    canvasPattern->SetId(patternCount_);
    canvasPattern->SetUnit(GetUnit());
    patternCount_++;
}
std::shared_ptr<OHOS::Ace::Gradient> CanvasRendererPeerImpl::CreateRadialGradient(const RadialGradientParam& params)
{
    double x0 = 0;
    double y0 = 0;
    double r0 = 0;
    double x1 = 0;
    double y1 = 0;
    double r1 = 0;
    if (GetDoubleArg(x0, params.x0) && GetDoubleArg(y0, params.y0) && GetDoubleArg(r0, params.r0) &&
        GetDoubleArg(x1, params.x1) && GetDoubleArg(y1, params.y1) && GetDoubleArg(r1, params.r1)) {
        double density = GetDensity();
        auto gradient = std::make_shared<Ace::Gradient>();
        gradient->SetType(Ace::GradientType::RADIAL);
        gradient->SetBeginOffset(Offset(x0 * density, y0 * density));
        gradient->SetEndOffset(Offset(x1 * density, y1 * density));
        gradient->SetInnerRadius(r0 * density);
        gradient->SetOuterRadius(r1 * density);
        return gradient;
    }
    return nullptr;
}
std::shared_ptr<OHOS::Ace::Gradient> CanvasRendererPeerImpl::CreateConicGradient(double x, double y, double startAngle)
{
    if (IfJudgeSpecialValue(x) && IfJudgeSpecialValue(y) && IfJudgeSpecialValue(startAngle)) {
        double density = GetDensity();
        auto gradient = std::make_shared<OHOS::Ace::Gradient>();
        gradient->SetType(Ace::GradientType::CONIC);
        gradient->GetConicGradient().startAngle =
            Ace::AnimatableDimension(Ace::Dimension(fmod(startAngle, (MULTI_BY_2 * ACE_PI))));
        gradient->GetConicGradient().centerX = Ace::AnimatableDimension(Ace::Dimension(x * density));
        gradient->GetConicGradient().centerY = Ace::AnimatableDimension(Ace::Dimension(y * density));
        return gradient;
    }
    return nullptr;
}
void CanvasRendererPeerImpl::CreateImageData(
    std::vector<uint8_t>& vbuffer, double fWidth, double fHeight, uint32_t& width, uint32_t& height)
{
    double density = GetDensity();
    fWidth *= density;
    fHeight *= density;
    uint32_t finalWidth = static_cast<uint32_t>(std::abs(fWidth + DIFF));
    uint32_t finalHeight = static_cast<uint32_t>(std::abs(fHeight + DIFF));
    vbuffer.resize(finalWidth * finalHeight * PIXEL_SIZE);
    uint32_t* buffer = (uint32_t*)vbuffer.data();
    if (!buffer || (finalHeight > 0 && finalWidth > (UINT32_MAX / finalHeight))) {
        vbuffer.clear();
        width = 0;
        height = 0;
        return;
    }
    for (uint32_t idx = 0; idx < finalWidth * finalHeight; ++idx) {
        buffer[idx] = 0xffffffff;
    }
    width = finalWidth;
    height = finalHeight;
}
void CanvasRendererPeerImpl::CreateImageData(
    std::vector<uint8_t>& vbuffer, const Ace::ImageData& imageData, uint32_t& width, uint32_t& height)
{
    uint32_t finalWidth = static_cast<uint32_t>(std::abs(imageData.dirtyWidth));
    uint32_t finalHeight = static_cast<uint32_t>(std::abs(imageData.dirtyHeight));
    vbuffer.resize(finalWidth * finalHeight * PIXEL_SIZE);
    uint32_t* buffer = (uint32_t*)vbuffer.data();
    if (!buffer || (finalHeight > 0 && finalWidth > (UINT32_MAX / finalHeight))) {
        vbuffer.clear();
        width = 0;
        height = 0;
        return;
    }
    for (uint32_t idx = 0; idx < finalWidth * finalHeight; ++idx) {
        buffer[idx] = 0xffffffff;
    }
    width = finalWidth;
    height = finalHeight;
}
void CanvasRendererPeerImpl::GetImageData(
    std::vector<uint8_t>& vbuffer, Ace::ImageSize& imageSize, uint32_t& width, uint32_t& height)
{
    CHECK_NULL_VOID(renderingContext2DModel_);
    double density = GetDensity();
    imageSize.left *= density;
    imageSize.top *= density;
    imageSize.width = imageSize.width * density + DIFF;
    imageSize.height = imageSize.height * density + DIFF;

    uint32_t finalWidth = static_cast<uint32_t>(std::abs(imageSize.width));
    uint32_t finalHeight = static_cast<uint32_t>(std::abs(imageSize.height));
    vbuffer.resize(finalWidth * finalHeight * PIXEL_SIZE);
    uint8_t* buffer = vbuffer.data();
    if (!buffer || (finalHeight > 0 && finalWidth > (UINT32_MAX / finalHeight))) {
        vbuffer.clear();
        width = 0;
        height = 0;
        return;
    }
    renderingContext2DModel_->GetImageDataModel(imageSize, buffer);
    width = finalWidth;
    height = finalHeight;
}
RefPtr<Ace::PixelMap> CanvasRendererPeerImpl::GetPixelMap(
    const double x, const double y, const double width, const double height)
{
#ifdef PIXEL_MAP_SUPPORTED
    CHECK_NULL_RETURN(renderingContext2DModel_, nullptr);
    double density = GetDensity();
    ImageSize imageSize = { .left = x, .top = y, .width = width, .height = height };
    imageSize.left *= density;
    imageSize.top *= density;
    imageSize.width = imageSize.width * density + DIFF;
    imageSize.height = imageSize.height * density + DIFF;
    auto finalHeight = static_cast<uint32_t>(std::abs(imageSize.height));
    auto finalWidth = static_cast<uint32_t>(std::abs(imageSize.width));
    if (finalHeight > 0 && finalWidth > (UINT32_MAX / finalHeight)) {
        return nullptr;
    }
    return renderingContext2DModel_->GetPixelMap(imageSize);
#else
    LOGE("ARKOALA CanvasRendererPeerImpl::GetPixelMap PixelMap is not supported on current platform.");
    return nullptr;
#endif
}
void CanvasRendererPeerImpl::PutImageData(Ace::ImageData& src, const PutImageDataParam& params)
{
    CHECK_NULL_VOID(renderingContext2DModel_);
    int32_t imgWidth = src.dirtyWidth;
    int32_t imgHeight = src.dirtyHeight;
    // Parse other parameters
    Ace::ImageData imageData = { .dirtyWidth = imgWidth, .dirtyHeight = imgHeight };
    ParseImageData(imageData, params);
    imageData.dirtyWidth = imageData.dirtyX < 0 ? std::min(imageData.dirtyX + imageData.dirtyWidth, imgWidth)
                                                : std::min(imgWidth - imageData.dirtyX, imageData.dirtyWidth);
    imageData.dirtyHeight = imageData.dirtyY < 0 ? std::min(imageData.dirtyY + imageData.dirtyHeight, imgHeight)
                                                 : std::min(imgHeight - imageData.dirtyY, imageData.dirtyHeight);
    // copy the data from the image data.
    std::vector<uint32_t> vbuffer = src.data;
    auto* buffer = (uint8_t*)vbuffer.data();
    int32_t bufferLength = static_cast<int32_t>(vbuffer.size() * sizeof(uint32_t));
    imageData.data = std::vector<uint32_t>();
    for (int32_t i = std::max(imageData.dirtyY, 0); i < imageData.dirtyY + imageData.dirtyHeight; ++i) {
        for (int32_t j = std::max(imageData.dirtyX, 0); j < imageData.dirtyX + imageData.dirtyWidth; ++j) {
            uint32_t idx = static_cast<uint32_t>(4 * (j + imgWidth * i));
            if (bufferLength > static_cast<int32_t>(idx + ALPHA_INDEX)) {
                uint8_t alpha = buffer[idx + 3]; // idx + 3: The 4th byte format: alpha
                uint8_t red = buffer[idx];       // idx: the 1st byte format: red
                uint8_t green = buffer[idx + 1]; // idx + 1: The 2nd byte format: green
                uint8_t blue = buffer[idx + 2];  // idx + 2: The 3rd byte format: blue
                imageData.data.emplace_back(Color::FromARGB(alpha, red, green, blue).GetValue());
            }
        }
    }
    renderingContext2DModel_->PutImageData(imageData);
}
std::vector<double> CanvasRendererPeerImpl::GetLineDash()
{
    std::vector<double> segments;
    CHECK_NULL_RETURN(renderingContext2DModel_, segments);
    double density = GetDensity();
    if (density == 0) {
        return segments;
    }
    auto lineDash = renderingContext2DModel_->GetLineDash();
    for (auto i = 0U; i < lineDash.size(); i++) {
        segments.push_back(lineDash[i] /= density);
    }
    return segments;
}
void CanvasRendererPeerImpl::SetLineDash(const std::vector<double>& segments)
{
    CHECK_NULL_VOID(renderingContext2DModel_);
    std::vector<double> lineDash;
    if (!GetDoubleArgArray(lineDash, segments)) {
        return;
    }
    if (lineDash.size() % EVEN_BY_2 != 0) {
        lineDash.insert(lineDash.end(), lineDash.begin(), lineDash.end());
    }
    double density = GetDensity();
    if (!Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TEN)) {
        for (auto i = 0U; i < lineDash.size(); i++) {
            lineDash[i] *= density;
        }
    }
    renderingContext2DModel_->SetLineDash(lineDash);
}
void CanvasRendererPeerImpl::ClearRect(const double x, const double y, const double width, const double height)
{
    CHECK_NULL_VOID(renderingContext2DModel_);
    if (IfJudgeSpecialValue(x) && IfJudgeSpecialValue(y) && IfJudgeSpecialValue(width) && IfJudgeSpecialValue(height)) {
        renderingContext2DModel_->ClearRect(Rect(x, y, width, height) * GetDensity());
    }
}
void CanvasRendererPeerImpl::FillRect(const double x, const double y, const double width, const double height)
{
    CHECK_NULL_VOID(renderingContext2DModel_);
    if (IfJudgeSpecialValue(x) && IfJudgeSpecialValue(y) && IfJudgeSpecialValue(width) && IfJudgeSpecialValue(height)) {
        renderingContext2DModel_->FillRect(Rect(x, y, width, height) * GetDensity());
    }
}
void CanvasRendererPeerImpl::StrokeRect(const double x, const double y, const double width, const double height)
{
    CHECK_NULL_VOID(renderingContext2DModel_);
    if (IfJudgeSpecialValue(x) && IfJudgeSpecialValue(y) && IfJudgeSpecialValue(width) && IfJudgeSpecialValue(height)) {
        renderingContext2DModel_->StrokeRect(Rect(x, y, width, height) * GetDensity());
    }
}
void CanvasRendererPeerImpl::Restore()
{
    CHECK_NULL_VOID(renderingContext2DModel_);
    if (!savePaintState_.empty()) {
        paintState_ = savePaintState_.back();
        savePaintState_.pop_back();
    }
    renderingContext2DModel_->Restore();
}
void CanvasRendererPeerImpl::Save()
{
    CHECK_NULL_VOID(renderingContext2DModel_);
    savePaintState_.push_back(paintState_);
    renderingContext2DModel_->CanvasRendererSave();
}
void CanvasRendererPeerImpl::FillText(const std::string& text, double x, double y, const std::optional<float>& optWidth)
{
    CHECK_NULL_VOID(renderingContext2DModel_);
    if (IfJudgeSpecialValue(x) && IfJudgeSpecialValue(y)) {
        FillTextInfo textInfo;
        textInfo.text = text;
        double density = GetDensity();
        textInfo.x = x * density;
        textInfo.y = y * density;
        double maxWidth = 0.0;
        if (optWidth) {
            maxWidth = optWidth.value() * density;
        } else if (!optWidth) {
            maxWidth = FLT_MAX;
        }
        if (maxWidth < 0) {
            return;
        }
        textInfo.maxWidth = maxWidth;
        renderingContext2DModel_->SetFillText(paintState_, textInfo);
    }
}
void CanvasRendererPeerImpl::MeasureText(Ace::TextMetrics& textMetrics, const std::string& text)
{
    CHECK_NULL_VOID(renderingContext2DModel_);
    double density = GetDensity();
    if (Positive(density)) {
        textMetrics = renderingContext2DModel_->GetMeasureTextMetrics(paintState_, text);
    }
}
void CanvasRendererPeerImpl::StrokeText(
    const std::string& text, double x, double y, const std::optional<float>& optWidth)
{
    CHECK_NULL_VOID(renderingContext2DModel_);
    if (IfJudgeSpecialValue(x) && IfJudgeSpecialValue(y)) {
        FillTextInfo textInfo;
        textInfo.text = text;
        double density = GetDensity();
        textInfo.x = x * density;
        textInfo.y = y * density;
        double maxWidth = 0.0;
        if (optWidth) {
            maxWidth = optWidth.value() * density;
        } else if (!optWidth) {
            maxWidth = FLT_MAX;
        }
        if (maxWidth < 0) {
            return;
        }
        textInfo.maxWidth = maxWidth;
        renderingContext2DModel_->SetStrokeText(paintState_, textInfo);
    }
}
void CanvasRendererPeerImpl::GetTransform(Matrix2DPeer* matrix)
{
    CHECK_NULL_VOID(renderingContext2DModel_);
    CHECK_NULL_VOID(matrix);
    ContainerScope scope(instanceId_);
    if (Container::IsCurrentUseNewPipeline()) {
        auto transform = renderingContext2DModel_->GetTransform();
        matrix->SetTransform(transform);
    }
}
void CanvasRendererPeerImpl::ResetTransform()
{
    CHECK_NULL_VOID(renderingContext2DModel_);
    renderingContext2DModel_->ResetTransform();
}
void CanvasRendererPeerImpl::Rotate(double angle)
{
    CHECK_NULL_VOID(renderingContext2DModel_);
    if (IfJudgeSpecialValue(angle)) {
        renderingContext2DModel_->CanvasRendererRotate(angle);
    }
}
void CanvasRendererPeerImpl::Scale(double x, double y)
{
    CHECK_NULL_VOID(renderingContext2DModel_);
    if (IfJudgeSpecialValue(x) && IfJudgeSpecialValue(y)) {
        renderingContext2DModel_->CanvasRendererScale(x, y);
    }
}
void CanvasRendererPeerImpl::SetTransform(TransformParam& param)
{
    CHECK_NULL_VOID(renderingContext2DModel_);
    if (IfJudgeSpecialValue(param.scaleX) && IfJudgeSpecialValue(param.skewY) && IfJudgeSpecialValue(param.skewX) &&
        IfJudgeSpecialValue(param.scaleY) && IfJudgeSpecialValue(param.translateX) &&
        IfJudgeSpecialValue(param.translateY)) {
        double density = GetDensity();
        param.translateX *= density;
        param.translateY *= density;
        renderingContext2DModel_->SetTransform(param, true);
    }
}
void CanvasRendererPeerImpl::SetTransform(const std::optional<Matrix2DPeer*>& optMatrix)
{
    CHECK_NULL_VOID(renderingContext2DModel_);
    if (!(optMatrix && optMatrix.value())) {
        renderingContext2DModel_->ResetTransform();
        return;
    }
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TEN)) {
        CHECK_NULL_VOID(optMatrix && optMatrix.value());
        auto matrix = optMatrix.value();
        auto param = matrix->GetTransform();
        renderingContext2DModel_->SetTransform(param, false);
    }
}
void CanvasRendererPeerImpl::SetTransform(unsigned int id, const TransformParam& transform)
{
    CHECK_NULL_VOID(renderingContext2DModel_);
    if (id >= 0 && id <= patternCount_) {
        renderingContext2DModel_->SetTransform(pattern_[id], transform);
    }
}
void CanvasRendererPeerImpl::Transform(TransformParam& param)
{
    CHECK_NULL_VOID(renderingContext2DModel_);
    if (IfJudgeSpecialValue(param.scaleX) && IfJudgeSpecialValue(param.skewY) && IfJudgeSpecialValue(param.skewX) &&
        IfJudgeSpecialValue(param.scaleY) && IfJudgeSpecialValue(param.translateX) &&
        IfJudgeSpecialValue(param.translateY)) {
        double density = GetDensity();
        param.translateX *= density;
        param.translateY *= density;
        renderingContext2DModel_->Transform(param);
    }
}
void CanvasRendererPeerImpl::Translate(double x, double y)
{
    CHECK_NULL_VOID(renderingContext2DModel_);
    if (IfJudgeSpecialValue(x) && IfJudgeSpecialValue(y)) {
        double density = GetDensity();
        renderingContext2DModel_->Translate(x * density, y * density);
    }
}
void CanvasRendererPeerImpl::SetPixelMap(const RefPtr<Ace::PixelMap>& pixelMap)
{
    CHECK_NULL_VOID(renderingContext2DModel_);
    CHECK_NULL_VOID(pixelMap);
    ImageInfo imageInfo = { .pixelMap = pixelMap };
    renderingContext2DModel_->DrawPixelMap(imageInfo);
}
void CanvasRendererPeerImpl::TransferFromImageBitmap(ImageBitmapPeer* bitmap)
{
    CHECK_NULL_VOID(renderingContext2DModel_);
    auto canvasRenderingContext2DModel = AceType::DynamicCast<CanvasRenderingContext2DModel>(renderingContext2DModel_);
    CHECK_NULL_VOID(canvasRenderingContext2DModel);
    CHECK_NULL_VOID(bitmap);
#ifdef PIXEL_MAP_SUPPORTED
    auto pixelMap = bitmap->GetPixelMap();
    CHECK_NULL_VOID(pixelMap);
    canvasRenderingContext2DModel->TransferFromImageBitmap(pixelMap);
#else
    auto imageData = bitmap->GetImageData();
    CHECK_NULL_VOID(imageData);
    canvasRenderingContext2DModel->TransferFromImageBitmap(imageData);
#endif
}
void CanvasRendererPeerImpl::SaveLayer()
{
    CHECK_NULL_VOID(renderingContext2DModel_);
    renderingContext2DModel_->SaveLayer();
}
void CanvasRendererPeerImpl::RestoreLayer()
{
    CHECK_NULL_VOID(renderingContext2DModel_);
    renderingContext2DModel_->RestoreLayer();
}
void CanvasRendererPeerImpl::Reset()
{
    CHECK_NULL_VOID(renderingContext2DModel_);
    ResetPaintState();
    renderingContext2DModel_->Reset();
}
void CanvasRendererPeerImpl::SetGlobalAlpha(double alpha)
{
    CHECK_NULL_VOID(renderingContext2DModel_);
    if (IfJudgeSpecialValue(alpha)) {
        renderingContext2DModel_->SetGlobalAlpha(alpha);
    }
}
void CanvasRendererPeerImpl::SetGlobalCompositeOperation(const std::string& compositeStr)
{
    CHECK_NULL_VOID(renderingContext2DModel_);
    static const LinearMapNode<CompositeOperation> compositeOperationTable[] = {
        { "copy", CompositeOperation::COPY },
        { "destination-atop", CompositeOperation::DESTINATION_ATOP },
        { "destination-in", CompositeOperation::DESTINATION_IN },
        { "destination-out", CompositeOperation::DESTINATION_OUT },
        { "destination-over", CompositeOperation::DESTINATION_OVER },
        { "lighter", CompositeOperation::LIGHTER },
        { "source-atop", CompositeOperation::SOURCE_ATOP },

        { "source-in", CompositeOperation::SOURCE_IN },
        { "source-out", CompositeOperation::SOURCE_OUT },
        { "source-over", CompositeOperation::SOURCE_OVER },
        { "xor", CompositeOperation::XOR },
    };
    auto type = ConvertStrToEnum(compositeStr.c_str(), compositeOperationTable, ArraySize(compositeOperationTable),
        CompositeOperation::SOURCE_OVER);
    renderingContext2DModel_->SetCompositeType(type);
}
void CanvasRendererPeerImpl::SetFillStyle(const std::string& colorStr)
{
    CHECK_NULL_VOID(renderingContext2DModel_);
    Color color;
    if (Color::ParseColorString(colorStr, color)) {
        renderingContext2DModel_->SetFillColor(color, true);
    }
}
void CanvasRendererPeerImpl::SetFillStyle(const uint32_t colorNum)
{
    CHECK_NULL_VOID(renderingContext2DModel_);
    renderingContext2DModel_->SetFillColor(Color(colorNum), false);
}
void CanvasRendererPeerImpl::SetFillStyle(const std::shared_ptr<Ace::Gradient>& gradient)
{
    CHECK_NULL_VOID(renderingContext2DModel_);
    CHECK_NULL_VOID(gradient);
    renderingContext2DModel_->SetFillGradient(gradient);
}

void CanvasRendererPeerImpl::SetFillStyle(int32_t id)
{
    CHECK_NULL_VOID(renderingContext2DModel_);
    renderingContext2DModel_->SetFillPattern(GetPatternPtr(id));
}
void CanvasRendererPeerImpl::SetStrokeStyle(const std::string& colorStr)
{
    CHECK_NULL_VOID(renderingContext2DModel_);
    Color color;
    if (Color::ParseColorString(colorStr, color)) {
        renderingContext2DModel_->SetStrokeColor(color, true);
    }
}
void CanvasRendererPeerImpl::SetStrokeStyle(const uint32_t colorNum)
{
    CHECK_NULL_VOID(renderingContext2DModel_);
    renderingContext2DModel_->SetStrokeColor(Color(ColorAlphaAdapt(colorNum)), false);
}
void CanvasRendererPeerImpl::SetStrokeStyle(const std::shared_ptr<Ace::Gradient>& gradient)
{
    CHECK_NULL_VOID(renderingContext2DModel_);
    CHECK_NULL_VOID(gradient);
    renderingContext2DModel_->SetStrokeGradient(gradient);
}
void CanvasRendererPeerImpl::SetStrokeStyle(int32_t id)
{
    CHECK_NULL_VOID(renderingContext2DModel_);
    renderingContext2DModel_->SetStrokePattern(GetPatternPtr(id));
}
void CanvasRendererPeerImpl::SetFilter(const std::string& filterStr)
{
    CHECK_NULL_VOID(renderingContext2DModel_);
    if (!filterStr.empty()) {
        renderingContext2DModel_->SetFilterParam(filterStr);
    }
}
void CanvasRendererPeerImpl::SetImageSmoothingEnabled(bool enabled)
{
    CHECK_NULL_VOID(renderingContext2DModel_);
    renderingContext2DModel_->SetSmoothingEnabled(enabled);
}
void CanvasRendererPeerImpl::SetImageSmoothingQuality(const std::string& quality)
{
    CHECK_NULL_VOID(renderingContext2DModel_);
    if (QUALITY_TYPE.find(quality) != QUALITY_TYPE.end()) {
        renderingContext2DModel_->SetSmoothingQuality(quality);
    }
}
void CanvasRendererPeerImpl::SetLineCap(const std::string& capStr)
{
    CHECK_NULL_VOID(renderingContext2DModel_);
    static const LinearMapNode<LineCapStyle> lineCapTable[] = {
        { "butt", LineCapStyle::BUTT },
        { "round", LineCapStyle::ROUND },
        { "square", LineCapStyle::SQUARE },
    };
    auto lineCap = ConvertStrToEnum(capStr.c_str(), lineCapTable, ArraySize(lineCapTable), LineCapStyle::BUTT);
    renderingContext2DModel_->SetLineCap(lineCap);
}
void CanvasRendererPeerImpl::SetLineDashOffset(double lineDashOffset)
{
    CHECK_NULL_VOID(renderingContext2DModel_);
    if (IfJudgeSpecialValue(lineDashOffset)) {
        renderingContext2DModel_->SetLineDashOffset(lineDashOffset * GetDensity());
    }
}
void CanvasRendererPeerImpl::SetLineJoin(const std::string& joinStr)
{
    CHECK_NULL_VOID(renderingContext2DModel_);
    static const LinearMapNode<LineJoinStyle> lineJoinTable[3] = {
        { "bevel", LineJoinStyle::BEVEL },
        { "miter", LineJoinStyle::MITER },
        { "round", LineJoinStyle::ROUND },
    };
    auto lineJoin = ConvertStrToEnum(joinStr.c_str(), lineJoinTable, ArraySize(lineJoinTable), LineJoinStyle::MITER);
    renderingContext2DModel_->SetLineJoin(lineJoin);
}
void CanvasRendererPeerImpl::SetLineWidth(double lineWidth)
{
    CHECK_NULL_VOID(renderingContext2DModel_);
    if (IfJudgeSpecialValue(lineWidth)) {
        renderingContext2DModel_->SetLineWidth(lineWidth * GetDensity());
    }
}
void CanvasRendererPeerImpl::SetMiterLimit(double limit)
{
    CHECK_NULL_VOID(renderingContext2DModel_);
    if (IfJudgeSpecialValue(limit)) {
        renderingContext2DModel_->SetMiterLimit(limit);
    }
}
void CanvasRendererPeerImpl::SetShadowBlur(double blur)
{
    CHECK_NULL_VOID(renderingContext2DModel_);
    if (IfJudgeSpecialValue(blur)) {
        renderingContext2DModel_->SetShadowBlur(blur);
    }
}
void CanvasRendererPeerImpl::SetShadowColor(const std::string& colorStr)
{
    CHECK_NULL_VOID(renderingContext2DModel_);
    renderingContext2DModel_->SetShadowColor(Color::FromString(colorStr));
}
void CanvasRendererPeerImpl::SetShadowOffsetX(double offsetX)
{
    CHECK_NULL_VOID(renderingContext2DModel_);
    if (IfJudgeSpecialValue(offsetX)) {
        renderingContext2DModel_->SetShadowOffsetX(offsetX * GetDensity());
    }
}
void CanvasRendererPeerImpl::SetShadowOffsetY(double offsetY)
{
    CHECK_NULL_VOID(renderingContext2DModel_);
    if (IfJudgeSpecialValue(offsetY)) {
        renderingContext2DModel_->SetShadowOffsetY(offsetY * GetDensity());
    }
}
void CanvasRendererPeerImpl::SetTextDirection(const std::string& directionStr)
{
    CHECK_NULL_VOID(renderingContext2DModel_);
    const LinearMapNode<TextDirection> textDirectionTable[] = {
        { "auto", TextDirection::AUTO },
        { "inherit", TextDirection::INHERIT },
        { "ltr", TextDirection::LTR },
        { "rtl", TextDirection::RTL },
    };
    auto direction =
        ConvertStrToEnum(directionStr.c_str(), textDirectionTable, ArraySize(textDirectionTable), TextDirection::LTR);
    renderingContext2DModel_->SetTextDirection(direction);
}
void CanvasRendererPeerImpl::SetFont(std::string fontStr)
{
    CHECK_NULL_VOID(renderingContext2DModel_);
    std::vector<std::string> fontProps;
    StringUtils::StringSplitter(fontStr.c_str(), ' ', fontProps);
    bool updateFontweight = false;
    bool updateFontStyle = false;
    for (const auto& fontProp : fontProps) {
        if (FONT_WEIGHTS.find(fontProp) != FONT_WEIGHTS.end()) {
            updateFontweight = true;
            auto weight = ConvertStrToFontWeight(fontProp);
            paintState_.SetFontWeight(weight);
            renderingContext2DModel_->SetFontWeight(weight);
        } else if (FONT_STYLES.find(fontProp) != FONT_STYLES.end()) {
            updateFontStyle = true;
            auto fontStyle = ConvertStrToFontStyle(fontProp);
            paintState_.SetFontStyle(fontStyle);
            renderingContext2DModel_->SetFontStyle(fontStyle);
        } else if (FONT_FAMILIES.find(fontProp) != FONT_FAMILIES.end()) {
            auto families = ConvertStrToFontFamilies(fontProp);
            paintState_.SetFontFamilies(families);
            renderingContext2DModel_->SetFontFamilies(families);
        } else if (fontProp.find("px") != std::string::npos || fontProp.find("vp") != std::string::npos) {
            Ace::Dimension size;
            if (fontProp.find("vp") != std::string::npos) {
                size = GetDimensionValue(fontProp);
            } else {
                std::string fontSize = fontProp.substr(0, fontProp.size() - 2);
                size = Ace::Dimension(StringUtils::StringToDouble(fontProp));
            }
            paintState_.SetFontSize(size);
            renderingContext2DModel_->SetFontSize(size);
        }
    }
    if (!updateFontStyle) {
        renderingContext2DModel_->SetFontStyle(Ace::FontStyle::NORMAL);
    }
    if (!updateFontweight) {
        renderingContext2DModel_->SetFontWeight(Ace::FontWeight::NORMAL);
    }
}
void CanvasRendererPeerImpl::SetTextAlign(const std::string& alignStr)
{
    CHECK_NULL_VOID(renderingContext2DModel_);
    static const LinearMapNode<TextAlign> textAlignTable[] = {
        { "center", TextAlign::CENTER },
        { "end", TextAlign::END },
        { "justify", TextAlign::JUSTIFY },
        { "left", TextAlign::LEFT },
        { "right", TextAlign::RIGHT },
        { "start", TextAlign::START },
    };
    auto align = ConvertStrToEnum(alignStr.c_str(), textAlignTable, ArraySize(textAlignTable), TextAlign::CENTER);
    paintState_.SetTextAlign(align);
    renderingContext2DModel_->SetTextAlign(align);
}
void CanvasRendererPeerImpl::SetTextBaseline(const std::string& baselineStr)
{
    CHECK_NULL_VOID(renderingContext2DModel_);
    static const LinearMapNode<TextBaseline> BASELINE_TABLE[] = {
        { "alphabetic", TextBaseline::ALPHABETIC },
        { "bottom", TextBaseline::BOTTOM },
        { "hanging", TextBaseline::HANGING },
        { "ideographic", TextBaseline::IDEOGRAPHIC },
        { "middle", TextBaseline::MIDDLE },
        { "top", TextBaseline::TOP },
    };
    auto baseline =
        ConvertStrToEnum(baselineStr.c_str(), BASELINE_TABLE, ArraySize(BASELINE_TABLE), TextBaseline::ALPHABETIC);
    paintState_.SetTextBaseline(baseline);
    renderingContext2DModel_->SetTextBaseline(baseline);
}
// inheritance
void CanvasRendererPeerImpl::ResetPaintState()
{
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_THIRTEEN)) {
    } else {
        paintState_ = PaintState();
    }
    std::vector<PaintState>().swap(savePaintState_);
    isInitializeShadow_ = false;
    isOffscreenInitializeShadow_ = false;
}
void CanvasRendererPeerImpl::SetAntiAlias()
{
    CHECK_NULL_VOID(renderingContext2DModel_);
    renderingContext2DModel_->SetAntiAlias(anti_);
}
void CanvasRendererPeerImpl::SetDensity()
{
    CHECK_NULL_VOID(renderingContext2DModel_);
    double density = GetDensity(true);
    renderingContext2DModel_->SetDensity(density);
}
std::string CanvasRendererPeerImpl::ToDataURL(
    const std::optional<std::string>& optType, const std::optional<float>& optQuality)
{
    CHECK_NULL_RETURN(renderingContext2DModel_, ERROR_STRING);
    std::string type;
    double quality = DEFAULT_QUALITY;
    if (optType) {
        type = optType.value();
    }
    if (optQuality && IfJudgeSpecialValue(optQuality.value())) {
        quality = optQuality.value();
    }
    return renderingContext2DModel_->ToDataURL(type, quality);
}
// private
void CanvasRendererPeerImpl::ExtractInfoToImage(Ace::CanvasImage& image, const DrawImageParam& params, bool isImage)
{
    double density = GetDensity();
    switch (params.size) {
        case SizeParam::TWO_ARGS:
            image.flag = IMAGE_FLAG_0;
            GetDoubleArg(image.dx, params.dx);
            GetDoubleArg(image.dy, params.dy);
            image.dx *= density;
            image.dy *= density;
            break;
        // 5 parameters: drawImage(image, dx, dy, dWidth, dHeight)
        case SizeParam::FOUR_ARGS:
            image.flag = IMAGE_FLAG_1;
            GetDoubleArg(image.dx, params.dx);
            GetDoubleArg(image.dy, params.dy);
            GetDoubleArg(image.dWidth, params.dWidth);
            GetDoubleArg(image.dHeight, params.dHeight);
            image.dx *= density;
            image.dy *= density;
            image.dWidth *= density;
            image.dHeight *= density;
            break;
        // 9 parameters: drawImage(image, sx, sy, sWidth, sHeight, dx, dy, dWidth, dHeight)
        case SizeParam::EIGHT_ARGS:
            image.flag = IMAGE_FLAG_2;
            GetDoubleArg(image.sx, params.sx);
            GetDoubleArg(image.sy, params.sy);
            GetDoubleArg(image.sWidth, params.sWidth);
            GetDoubleArg(image.sHeight, params.sHeight);
            GetDoubleArg(image.dx, params.dx);
            GetDoubleArg(image.dy, params.dy);
            GetDoubleArg(image.dWidth, params.dWidth);
            GetDoubleArg(image.dHeight, params.dHeight);
            // In higher versions, sx, sy, sWidth, sHeight are parsed in VP units
            // In lower versions, sx, sy, sWidth, sHeight are parsed in PX units
            if (isImage || Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_FOURTEEN)) {
                image.sx *= density;
                image.sy *= density;
                image.sWidth *= density;
                image.sHeight *= density;
            }
            image.dx *= density;
            image.dy *= density;
            image.dWidth *= density;
            image.dHeight *= density;
            break;
        default:
            break;
    }
}
Dimension CanvasRendererPeerImpl::GetDimensionValue(const std::string& str)
{
    return (StringUtils::StringToDimension(str));
}
Dimension CanvasRendererPeerImpl::GetDimensionValue(const Dimension& dimension)
{
    if ((dimension.Unit() == DimensionUnit::NONE) || (dimension.Unit() == DimensionUnit::PX)) {
        return Dimension(dimension.Value());
    }
    if (dimension.Unit() == DimensionUnit::VP) {
        return Dimension(dimension.Value() * GetDensity(true));
    }
    return Dimension(0.0);
}
Ace::Pattern CanvasRendererPeerImpl::GetPattern(unsigned int id)
{
    if (id < 0 || id >= pattern_.size()) {
        return Ace::Pattern();
    }
    return *(pattern_[id].get());
}
std::shared_ptr<Ace::Pattern> CanvasRendererPeerImpl::GetPatternPtr(int32_t id)
{
    if (id < 0 || id >= static_cast<int32_t>(pattern_.size())) {
        return std::shared_ptr<Ace::Pattern>();
    }
    return pattern_[id];
}
void CanvasRendererPeerImpl::ParseImageData(Ace::ImageData& imageData, const PutImageDataParam& params)
{
    if (params.x) {
        imageData.x = static_cast<int32_t>(GetDimensionValue(*params.x).Value());
    }
    if (params.y) {
        imageData.y = static_cast<int32_t>(GetDimensionValue(*params.y).Value());
    }
    if (params.size != SizeParam::SIX_ARGS) {
        return;
    }
    if (params.dirtyX) {
        imageData.dirtyX = static_cast<int32_t>(GetDimensionValue(*params.dirtyX).Value());
    }
    if (params.dirtyY) {
        imageData.dirtyY = static_cast<int32_t>(GetDimensionValue(*params.dirtyY).Value());
    }
    if (params.dirtyWidth) {
        imageData.dirtyWidth = static_cast<int32_t>(GetDimensionValue(*params.dirtyWidth).Value());
    }
    if (params.dirtyHeight) {
        imageData.dirtyHeight = static_cast<int32_t>(GetDimensionValue(*params.dirtyHeight).Value());
    }
}
} // namespace OHOS::Ace::NG::GeneratedModifier
