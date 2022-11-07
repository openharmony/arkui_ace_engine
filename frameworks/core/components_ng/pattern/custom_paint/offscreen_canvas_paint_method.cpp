/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/custom_paint/offscreen_canvas_paint_method.h"

#include "third_party/skia/include/effects/SkBlurImageFilter.h"
#include "flutter/third_party/txt/src/txt/paragraph_builder.h"
#include "flutter/third_party/txt/src/txt/paragraph_style.h"
#include "third_party/skia/include/core/SkMaskFilter.h"
#include "third_party/skia/include/encode/SkJpegEncoder.h"
#include "third_party/skia/include/encode/SkPngEncoder.h"
#include "third_party/skia/include/encode/SkWebpEncoder.h"
#include "third_party/skia/include/utils/SkBase64.h"

#include "base/i18n/localization.h"
#include "base/utils/utils.h"
#include "core/components/common/painter/flutter_decoration_painter.h"
#include "core/components/common/painter/rosen_decoration_painter.h"
#include "core/components/font/constants_converter.h"
#include "core/components/font/flutter_font_collection.h"
#include "core/components/font/rosen_font_collection.h"

namespace OHOS::Ace::NG {
namespace {
constexpr double HANGING_PERCENT = 0.8;
constexpr double DEFAULT_QUALITY = 0.92;
constexpr int32_t MAX_LENGTH = 2048 * 2048;
const std::string UNSUPPORTED = "data:image/png";
const std::string URL_PREFIX = "data:";
const std::string URL_SYMBOL = ";base64,";
const std::string IMAGE_PNG = "image/png";
const std::string IMAGE_JPEG = "image/jpeg";
const std::string IMAGE_WEBP = "image/webp";
// If args is empty or invalid format, use default: image/png
std::string GetMimeType(const std::string& args)
{
    std::string type = args;
    for (size_t i = 0; i < type.size(); ++i) {
        type[i] = static_cast<uint8_t>(tolower(type[i]));
    }
    return type;
}

// Quality need between 0.0 and 1.0 for MimeType jpeg and webp
double GetQuality(const std::string& args, const double quality)
{
    std::string type = args;
    auto mimeType = GetMimeType(type);
    if (mimeType != IMAGE_JPEG && mimeType != IMAGE_WEBP) {
        return DEFAULT_QUALITY;
    }
    if (quality < 0.0 || quality > 1.0) {
        return DEFAULT_QUALITY;
    }
    return quality;
}
} // namespace

OffscreenCanvasPaintMethod::OffscreenCanvasPaintMethod(
    const RefPtr<PipelineContext> context, int32_t width, int32_t height)
{
    isOffscreen_ = true;
    antiAlias_ = true;
    context_ = context;
    width_ = width;
    height_ = height;

    auto imageInfo =
        SkImageInfo::Make(width, height, SkColorType::kRGBA_8888_SkColorType, SkAlphaType::kUnpremul_SkAlphaType);
    canvasCache_.allocPixels(imageInfo);
    cacheBitmap_.allocPixels(imageInfo);
    canvasCache_.eraseColor(SK_ColorTRANSPARENT);
    cacheBitmap_.eraseColor(SK_ColorTRANSPARENT);
    skCanvas_ = std::make_unique<SkCanvas>(canvasCache_);
    cacheCanvas_ = std::make_unique<SkCanvas>(cacheBitmap_);

    auto currentDartState = flutter::UIDartState::Current();
    if (!currentDartState) {
        return;
    }

    InitFilterFunc();
    InitImageCallbacks();
}

void OffscreenCanvasPaintMethod::InitFilterFunc()
{
    filterFunc_["grayscale"] = [&](const std::string& percentage) {
        SetGrayFilter(percentage);
    };
    filterFunc_["sepia"] = [&](const std::string& percentage) {
        SetSepiaFilter(percentage);
    };
    filterFunc_["invert"] = [&](const std::string& percentage) {
        SetInvertFilter(percentage);
    };
    filterFunc_["opacity"] = [&](const std::string& percentage) {
        SetOpacityFilter(percentage);
    };
    filterFunc_["brightness"] = [&](const std::string& percentage) {
        SetBrightnessFilter(percentage);
    };
    filterFunc_["contrast"] = [&](const std::string& percentage) {
        SetContrastFilter(percentage);
    };
    filterFunc_["blur"] = [&](const std::string& percentage) {
        SetBlurFilter(percentage);
    };
    filterFunc_["drop-shadow"] = [&](const std::string& percentage) {
        SetDropShadowFilter(percentage);
    };
    filterFunc_["saturate"] = [&](const std::string& percentage) {
        SetSaturateFilter(percentage);
    };
    filterFunc_["hue-rotate"] = [&](const std::string& percentage) {
        SetHueRotateFilter(percentage);
    };
}

void OffscreenCanvasPaintMethod::SetGrayFilter(const std::string& percent)
{
    std::string percentage = percent;
    bool hasPercent = IsPercentStr(percentage);
    float percentNum = 0.0f;
    std::istringstream iss(percentage);
    iss >> percentNum;
    if (hasPercent) {
        percentNum = percentNum / 100;
    }
    if (percentNum > 1) {
        percentNum = 1;
    }
    float otherColor = percentNum / 3;
    float primColor = 1 - 2 * otherColor;
    float matrix[20] = { 0 };
    matrix[0] = matrix[6] = matrix[12] = primColor;
    matrix[1] = matrix[2] = matrix[5] = matrix[7] = matrix[10] = matrix[11] = otherColor;
    matrix[18] = 1.0f;
    SetColorFilter(matrix);
}

void OffscreenCanvasPaintMethod::SetSepiaFilter(const std::string& percent)
{
    std::string percentage = percent;
    bool hasPercent = IsPercentStr(percentage);
    float percentNum = 0.0f;
    std::istringstream iss(percentage);
    iss >> percentNum;
    if (hasPercent) {
        percentNum = percentNum / 100;
    }
    if (percentNum > 1) {
        percentNum = 1;
    }
    float matrix[20] = { 0 };
    matrix[0] = 1.0f - percentNum * 0.6412f;
    matrix[1] = percentNum * 0.7044f;
    matrix[2] = percentNum * 0.1368f;
    matrix[5] = percentNum * 0.2990f;
    matrix[6] = 1.0f - percentNum * 0.4130f;
    matrix[7] = percentNum * 0.1140f;
    matrix[10] = percentNum * 0.2392f;
    matrix[11] = percentNum * 0.4696f;
    matrix[12] = 1.0f - percentNum * 0.9088f;
    matrix[18] = 1.0f;
    SetColorFilter(matrix);
}

void OffscreenCanvasPaintMethod::SetInvertFilter(const std::string& filterParam)
{
    std::string percent = filterParam;
    bool hasPercent = IsPercentStr(percent);
    float percentage = 0.0f;
    std::istringstream iss(percent);
    iss >> percentage;
    if (hasPercent) {
        percentage = percentage / 100;
    }

    float matrix[20] = { 0 };
    matrix[0] = matrix[6] = matrix[12] = 1.0 - 2.0 * percentage;
    matrix[4] = matrix[9] = matrix[14] = percentage;
    matrix[18] = 1.0f;
    SetColorFilter(matrix);
}

void OffscreenCanvasPaintMethod::SetOpacityFilter(const std::string& filterParam)
{
    std::string percent = filterParam;
    bool hasPercent = IsPercentStr(percent);
    float percentage = 0.0f;
    std::istringstream iss(percent);
    iss >> percentage;
    if (hasPercent) {
        percentage = percentage / 100;
    }

    float matrix[20] = { 0 };
    matrix[0] = matrix[6] = matrix[12] = 1.0f;
    matrix[18] = percentage;
    SetColorFilter(matrix);
}

void OffscreenCanvasPaintMethod::SetBrightnessFilter(const std::string& percent)
{
    std::string perStr = percent;
    bool hasPercent = IsPercentStr(perStr);
    float percentage = 0.0f;
    std::istringstream iss(perStr);
    iss >> percentage;
    if (hasPercent) {
        percentage = percentage / 100;
    }

    if (percentage < 0) {
        return;
    }
    float matrix[20] = { 0 };
    matrix[0] = matrix[6] = matrix[12] = percentage;
    matrix[18] = 1.0f;
    SetColorFilter(matrix);
}

void OffscreenCanvasPaintMethod::SetContrastFilter(const std::string& percent)
{
    std::string perStr = percent;
    float percentage = 0.0f;
    bool hasPercent = IsPercentStr(perStr);
    std::istringstream iss(perStr);
    iss >> percentage;
    if (hasPercent) {
        percentage = percentage / 100;
    }

    float matrix[20] = { 0 };
    matrix[0] = matrix[6] = matrix[12] = percentage;
    matrix[4] = matrix[9] = matrix[14] = 0.5f * (1 - percentage);
    matrix[18] = 1;
    SetColorFilter(matrix);
}

void OffscreenCanvasPaintMethod::SetBlurFilter(const std::string& percent)
{
    imagePaint_.setImageFilter(SkBlurImageFilter::Make(BlurStrToDouble(percent), BlurStrToDouble(percent), nullptr));
}

void OffscreenCanvasPaintMethod::SetDropShadowFilter(const std::string& percent)
{
    std::vector<std::string> offsets;
    StringUtils::StringSplitter(percent, ' ', offsets);
    if (offsets.empty() || offsets.size() != 4) {
        return;
    }
    imageShadow_.SetOffsetX(PxStrToDouble(offsets[0]));
    imageShadow_.SetOffsetY(PxStrToDouble(offsets[1]));
    imageShadow_.SetBlurRadius(PxStrToDouble(offsets[2]));
    imageShadow_.SetColor(Color::FromString(offsets[3]));
}

void OffscreenCanvasPaintMethod::SetSaturateFilter(const std::string& filterParam)
{
    std::string percent = filterParam;
    bool hasPercent = IsPercentStr(percent);
    float percentage = 0.0f;
    std::istringstream iss(percent);
    iss >> percentage;
    if (hasPercent) {
        percentage = percentage / 100;
    }
    double N = percentage;
    float matrix[20] = { 0 };
    matrix[0] = 0.3086f * (1 - N) + N;
    matrix[1] = matrix[11] = 0.6094f * (1 - N);
    matrix[2] = matrix[7] = 0.0820f * (1 - N);
    matrix[5] = matrix[10] = 0.3086f * (1 - N);
    matrix[6] = 0.6094f * (1 - N) + N;
    matrix[12] = 0.0820f * (1 - N) + N;
    matrix[18] = 1.0f;
    SetColorFilter(matrix);
}

void OffscreenCanvasPaintMethod::SetHueRotateFilter(const std::string& filterParam)
{
    std::string percent = filterParam;
    float degree = 0.0f;
    if (percent.find("deg") != std::string::npos) {
        size_t index = percent.find("deg");
        percent = percent.substr(0, index);
        std::istringstream iss(percent);
        iss >> degree;
    }
    if (percent.find("turn") != std::string::npos) {
        size_t index = percent.find("turn");
        percent = percent.substr(0, index);
        std::istringstream iss(percent);
        iss >> degree;
        degree = degree * 360;
    }
    if (percent.find("rad") != std::string::npos) {
        size_t index = percent.find("rad");
        percent = percent.substr(0, index);
        std::istringstream iss(percent);
        iss >> degree;
        degree = degree * 180 / 3.142f;
    }

    while (GreatOrEqual(degree, 360)) {
        degree -= 360;
    }

    float matrix[20] = { 0 };
    int32_t type = degree / 120;
    float N = (degree - 120 * type) / 120;
    switch (type) {
        case 0:
            // degree is in 0-120
            matrix[0] = matrix[6] = matrix[12] = 1 - N;
            matrix[2] = matrix[5] = matrix[11] = N;
            matrix[18] = 1.0f;
            break;
        case 1:
            // degree is in 120-240
            matrix[1] = matrix[7] = matrix[10] = N;
            matrix[2] = matrix[5] = matrix[11] = 1 - N;
            matrix[18] = 1.0f;
            break;
        case 2:
            // degree is in 240-360
            matrix[0] = matrix[6] = matrix[11] = N;
            matrix[1] = matrix[7] = matrix[10] = 1 - N;
            matrix[18] = 1.0f;
            break;
        default:
            break;
    }
    SetColorFilter(matrix);
}

void OffscreenCanvasPaintMethod::SetColorFilter(float matrix[20])
{
#ifdef USE_SYSTEM_SKIA
    matrix[4] *= 255;
    matrix[9] *= 255;
    matrix[14] *= 255;
    matrix[19] *= 255;
    imagePaint_.setColorFilter(SkColorFilter::MakeMatrixFilterRowMajor255(matrix));
#else
    imagePaint_.setColorFilter(SkColorFilters::Matrix(matrix));
#endif
}

bool OffscreenCanvasPaintMethod::GetFilterType(std::string& filterType, std::string& filterParam)
{
    std::string paramData = filterParam_;
    size_t index = paramData.find("(");
    if (index == std::string::npos) {
        return false;
    }
    filterType = paramData.substr(0, index);
    filterParam = paramData.substr(index + 1);
    size_t endeIndex = filterParam.find(")");
    if (endeIndex  == std::string::npos) {
        return false;
    }
    filterParam.erase(endeIndex, 1);
    return true;
}

bool OffscreenCanvasPaintMethod::IsPercentStr(std::string& percent)
{
    if (percent.find("%") != std::string::npos) {
        size_t index = percent.find("%");
        percent = percent.substr(0, index);
        return true;
    }
    return false;
}

double OffscreenCanvasPaintMethod::PxStrToDouble(const std::string& str)
{
    double ret = 0;
    size_t index = str.find("px");
    if (index != std::string::npos) {
        std::string result = str.substr(0, index);
        std::istringstream iss(result);
        iss >> ret;
    }
    return ret;
}

double OffscreenCanvasPaintMethod::BlurStrToDouble(const std::string& str)
{
    double ret = 0;
    size_t index = str.find("px");
    size_t index1 = str.find("rem");
    size_t demIndex = std::string::npos;
    if (index != std::string::npos) {
        demIndex = index;
    }
    if (index1 != std::string::npos) {
        demIndex = index1;
    }
    if (demIndex != std::string::npos) {
        std::string result = str.substr(0, demIndex);
        std::istringstream iss(result);
        iss >> ret;
    }
    if (str.find("rem") != std::string::npos) {
        return ret * 15;
    }
    return ret;
}

void OffscreenCanvasPaintMethod::ImageObjReady(const RefPtr<ImageObject>& imageObj)
{
    if (imageObj->IsSvg()) {
        skiaDom_ = AceType::DynamicCast<SvgSkiaImageObject>(imageObj)->GetSkiaDom();
        currentSource_ = loadingSource_;
    } else {
        LOGE("image is not svg");
    }
}

void OffscreenCanvasPaintMethod::ImageObjFailed()
{
    loadingSource_.SetSrc("");
    currentSource_.SetSrc("");
    skiaDom_ = nullptr;
}

void OffscreenCanvasPaintMethod::DrawImage(
    PaintWrapper* paintWrapper, const Ace::CanvasImage& canvasImage, double width, double height)
{
    if (!flutter::UIDartState::Current()) {
        return;
    }

    std::string::size_type tmp = canvasImage.src.find(".svg");
    if (tmp != std::string::npos) {
        DrawSvgImage(paintWrapper, canvasImage);
        return;
    }

    auto image = GreatOrEqual(width, 0) && GreatOrEqual(height, 0)
                        ? ImageProvider::GetSkImage(canvasImage.src, context_, Size(width, height))
                        : ImageProvider::GetSkImage(canvasImage.src, context_);
    if (!image) {
        LOGE("image is null");
        return;
    }
    InitPaintBlend(cachePaint_);
    const auto skCanvas =
        globalState_.GetType() == CompositeOperation::SOURCE_OVER ? skCanvas_.get() : cacheCanvas_.get();
    InitImagePaint();
    if (HasImageShadow()) {
        SkRect skRect = SkRect::MakeXYWH(canvasImage.dx, canvasImage.dy, canvasImage.dWidth, canvasImage.dHeight);
        SkPath path;
        path.addRect(skRect);
        FlutterDecorationPainter::PaintShadow(path, imageShadow_, skCanvas);
    }
    switch (canvasImage.flag) {
        case 0:
            skCanvas->drawImage(image, canvasImage.dx, canvasImage.dy);
            break;
        case 1: {
            SkRect rect = SkRect::MakeXYWH(canvasImage.dx, canvasImage.dy, canvasImage.dWidth, canvasImage.dHeight);
            skCanvas->drawImageRect(image, rect, &imagePaint_);
            break;
        }
        case 2: {
            SkRect dstRect =
                SkRect::MakeXYWH(canvasImage.dx, canvasImage.dy, canvasImage.dWidth, canvasImage.dHeight);
            SkRect srcRect =
                SkRect::MakeXYWH(canvasImage.sx, canvasImage.sy, canvasImage.sWidth, canvasImage.sHeight);
            skCanvas->drawImageRect(image, srcRect, dstRect, &imagePaint_);
            break;
        }
        default:
            break;
    }
    if (globalState_.GetType() != CompositeOperation::SOURCE_OVER) {
        skCanvas_->drawBitmap(cacheBitmap_, 0, 0, &cachePaint_);
        cacheBitmap_.eraseColor(0);
    }
}

void OffscreenCanvasPaintMethod::DrawPixelMap(RefPtr<PixelMap> pixelMap, const Ace::CanvasImage& canvasImage)
{
    if (!flutter::UIDartState::Current()) {
        return;
    }

    // get skImage form pixelMap
    auto imageInfo = ImageProvider::MakeSkImageInfoFromPixelMap(pixelMap);
    SkPixmap imagePixmap(imageInfo, reinterpret_cast<const void*>(pixelMap->GetPixels()), pixelMap->GetRowBytes());

    // Step2: Create SkImage and draw it, using gpu or cpu
    sk_sp<SkImage> image;

    image = SkImage::MakeFromRaster(imagePixmap, nullptr, nullptr);
    if (!image) {
        LOGE("image is null");
        return;
    }

    InitPaintBlend(cachePaint_);
    const auto skCanvas =
        globalState_.GetType() == CompositeOperation::SOURCE_OVER ? skCanvas_.get() : cacheCanvas_.get();
    InitImagePaint();
    switch (canvasImage.flag) {
        case 0:
            skCanvas->drawImage(image, canvasImage.dx, canvasImage.dy);
            break;
        case 1: {
            SkRect rect = SkRect::MakeXYWH(canvasImage.dx, canvasImage.dy, canvasImage.dWidth, canvasImage.dHeight);
            skCanvas->drawImageRect(image, rect, &imagePaint_);
            break;
        }
        case 2: {
            SkRect dstRect =
                SkRect::MakeXYWH(canvasImage.dx, canvasImage.dy, canvasImage.dWidth, canvasImage.dHeight);
            SkRect srcRect =
                SkRect::MakeXYWH(canvasImage.sx, canvasImage.sy, canvasImage.sWidth, canvasImage.sHeight);
            skCanvas->drawImageRect(image, srcRect, dstRect, &imagePaint_);
            break;
        }
        default:
            break;
    }
    if (globalState_.GetType() != CompositeOperation::SOURCE_OVER) {
        skCanvas_->drawBitmap(cacheBitmap_, 0, 0, &cachePaint_);
        cacheBitmap_.eraseColor(0);
    }
}

bool OffscreenCanvasPaintMethod::HasImageShadow() const
{
    return !(NearZero(imageShadow_.GetOffset().GetX()) && NearZero(imageShadow_.GetOffset().GetY()) &&
         NearZero(imageShadow_.GetBlurRadius()));
}

void OffscreenCanvasPaintMethod::SetPaintImage()
{
    float matrix[20] = {0};
    matrix[0] = matrix[6] = matrix[12] = matrix[18] = 1.0f;
#ifdef USE_SYSTEM_SKIA
    imagePaint_.setColorFilter(SkColorFilter::MakeMatrixFilterRowMajor255(matrix));
#else
    imagePaint_.setColorFilter(SkColorFilters::Matrix(matrix));
#endif

    imagePaint_.setMaskFilter(SkMaskFilter::MakeBlur(SkBlurStyle::kNormal_SkBlurStyle, 0));
    imagePaint_.setImageFilter(SkBlurImageFilter::Make(0, 0, nullptr));

    SetDropShadowFilter("0px 0px 0px black");
    std::string filterType, filterParam;
    if (!GetFilterType(filterType, filterParam)) {
        return;
    }
    if (filterFunc_.find(filterType) != filterFunc_.end()) {
        filterFunc_[filterType](filterParam);
    }
}

std::unique_ptr<Ace::ImageData> OffscreenCanvasPaintMethod::GetImageData(
    double left, double top, double width, double height)
{
    double viewScale = 1.0;
    CHECK_NULL_RETURN(context_, std::unique_ptr<Ace::ImageData>());
    viewScale = context_->GetViewScale();

    // copy the bitmap to tempCanvas
    auto imageInfo =
        SkImageInfo::Make(width, height, SkColorType::kBGRA_8888_SkColorType, SkAlphaType::kOpaque_SkAlphaType);
    double scaledLeft = left * viewScale;
    double scaledTop = top * viewScale;
    double dirtyWidth = width >= 0 ? width : 0;
    double dirtyHeight = height >= 0 ? height : 0;
    int32_t size = dirtyWidth * dirtyHeight;
    auto srcRect = SkRect::MakeXYWH(scaledLeft, scaledTop, width * viewScale, height * viewScale);
    auto dstRect = SkRect::MakeXYWH(0.0, 0.0, dirtyWidth, dirtyHeight);
    SkBitmap tempCache;
    tempCache.allocPixels(imageInfo);
    SkCanvas tempCanvas(tempCache);
#ifdef USE_SYSTEM_SKIA_S
    tempCanvas.drawImageRect(
        canvasCache_.asImage(), srcRect, dstRect, SkSamplingOptions(), nullptr, SkCanvas::kFast_SrcRectConstraint);
#else
    tempCanvas.drawBitmapRect(canvasCache_, srcRect, dstRect, nullptr);
#endif
    // write color
    std::unique_ptr<uint8_t[]> pixels = std::make_unique<uint8_t[]>(size * 4);
    tempCanvas.readPixels(imageInfo, pixels.get(), dirtyWidth * imageInfo.bytesPerPixel(), 0, 0);
    std::unique_ptr<Ace::ImageData> imageData = std::make_unique<Ace::ImageData>();
    imageData->dirtyWidth = dirtyWidth;
    imageData->dirtyHeight = dirtyHeight;
    // a pixel include 4 data blue, green, red, alpha
    for (int i = 0; i < size * 4; i += 4) {
        auto blue = pixels[i];
        auto green = pixels[i + 1];
        auto red = pixels[i + 2];
        auto alpha = pixels[i + 3];
        imageData->data.emplace_back(Color::FromARGB(alpha, red, green, blue));
    }
    return imageData;
}

void OffscreenCanvasPaintMethod::FillText(const std::string& text, double x, double y, const PaintState& state)
{
    if (!UpdateOffParagraph(text, false, state)) {
        return;
    }
    PaintText(text, x, y, false);
}

void OffscreenCanvasPaintMethod::StrokeText(const std::string& text, double x, double y, const PaintState& state)
{
    if (HasShadow()) {
        if (!UpdateOffParagraph(text, true, state, true)) {
            return;
        }
        PaintText(text, x, y, true);
    }

    if (!UpdateOffParagraph(text, true, state)) {
        return;
    }
    PaintText(text, x, y, true);
}

double OffscreenCanvasPaintMethod::MeasureText(const std::string& text, const PaintState& state)
{
    using namespace Constants;
    txt::ParagraphStyle style;
    style.text_align = ConvertTxtTextAlign(state.GetTextAlign());
    style.text_direction = ConvertTxtTextDirection(state.GetOffTextDirection());
    auto fontCollection = FlutterFontCollection::GetInstance().GetFontCollection();
    if (!fontCollection) {
        LOGW("MeasureText: fontCollection is null");
        return 0.0;
    }
    std::unique_ptr<txt::ParagraphBuilder> builder = txt::ParagraphBuilder::CreateTxtBuilder(style, fontCollection);
    txt::TextStyle txtStyle;
    ConvertTxtStyle(state.GetTextStyle(), context_, txtStyle);
    txtStyle.font_size = state.GetTextStyle().GetFontSize().Value();
    builder->PushStyle(txtStyle);
    builder->AddText(StringUtils::Str8ToStr16(text));
    auto paragraph = builder->Build();
    paragraph->Layout(Size::INFINITE_SIZE);
    return paragraph->GetMaxIntrinsicWidth();
}

double OffscreenCanvasPaintMethod::MeasureTextHeight(const std::string& text, const PaintState& state)
{
    using namespace Constants;
    txt::ParagraphStyle style;
    style.text_align = ConvertTxtTextAlign(state.GetTextAlign());
    style.text_direction = ConvertTxtTextDirection(state.GetOffTextDirection());
    auto fontCollection = FlutterFontCollection::GetInstance().GetFontCollection();
    if (!fontCollection) {
        LOGW("MeasureText: fontCollection is null");
        return 0.0;
    }
    std::unique_ptr<txt::ParagraphBuilder> builder = txt::ParagraphBuilder::CreateTxtBuilder(style, fontCollection);
    txt::TextStyle txtStyle;
    ConvertTxtStyle(state.GetTextStyle(), context_, txtStyle);
    txtStyle.font_size = state.GetTextStyle().GetFontSize().Value();
    builder->PushStyle(txtStyle);
    builder->AddText(StringUtils::Str8ToStr16(text));
    auto paragraph = builder->Build();
    paragraph->Layout(Size::INFINITE_SIZE);
    return paragraph->GetHeight();
}

TextMetrics OffscreenCanvasPaintMethod::MeasureTextMetrics(const std::string& text, const PaintState& state)
{
    using namespace Constants;
    txt::ParagraphStyle style;
    style.text_align = ConvertTxtTextAlign(state.GetTextAlign());
    style.text_direction = ConvertTxtTextDirection(state.GetOffTextDirection());
    auto fontCollection = FlutterFontCollection::GetInstance().GetFontCollection();
    if (!fontCollection) {
        LOGW("MeasureText: fontCollection is null");
        return { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
    }
    std::unique_ptr<txt::ParagraphBuilder> builder = txt::ParagraphBuilder::CreateTxtBuilder(style, fontCollection);
    txt::TextStyle txtStyle;
    ConvertTxtStyle(state.GetTextStyle(), context_, txtStyle);
    txtStyle.font_size = state.GetTextStyle().GetFontSize().Value();
    builder->PushStyle(txtStyle);
    builder->AddText(StringUtils::Str8ToStr16(text));
    auto paragraph = builder->Build();
    paragraph->Layout(Size::INFINITE_SIZE);

    auto textAlign = state.GetTextAlign();
    auto textBaseLine = state.GetTextStyle().GetTextBaseline();

    auto width = paragraph->GetMaxIntrinsicWidth();
    auto height = paragraph->GetHeight();

    auto actualBoundingBoxLeft = -GetAlignOffset(text, textAlign, paragraph);
    auto actualBoundingBoxRight = width - actualBoundingBoxLeft;
    auto actualBoundingBoxAscent = -GetBaselineOffset(textBaseLine, paragraph);
    auto actualBoundingBoxDescent = height - actualBoundingBoxAscent;

    return { width, height, actualBoundingBoxLeft, actualBoundingBoxRight, actualBoundingBoxAscent,
        actualBoundingBoxDescent };
}

void OffscreenCanvasPaintMethod::PaintText(
    const std::string& text, double x, double y, bool isStroke, bool hasShadow)
{
    paragraph_->Layout(width_);
    if (width_ > paragraph_->GetMaxIntrinsicWidth()) {
        paragraph_->Layout(std::ceil(paragraph_->GetMaxIntrinsicWidth()));
    }
    auto align = isStroke ? strokeState_.GetTextAlign() : fillState_.GetTextAlign();
    double dx = x + GetAlignOffset(text, align, paragraph_);
    auto baseline =
        isStroke ? strokeState_.GetTextStyle().GetTextBaseline() : fillState_.GetTextStyle().GetTextBaseline();
    double dy = y + GetBaselineOffset(baseline, paragraph_);

    if (hasShadow) {
        skCanvas_->save();
        auto shadowOffsetX = shadow_.GetOffset().GetX();
        auto shadowOffsetY = shadow_.GetOffset().GetY();
        paragraph_->Paint(skCanvas_.get(), dx + shadowOffsetX, dy + shadowOffsetY);
        skCanvas_->restore();
        return;
    }
    paragraph_->Paint(skCanvas_.get(), dx, dy);
}

double OffscreenCanvasPaintMethod::GetAlignOffset(const std::string& text, TextAlign align, std::unique_ptr<txt::Paragraph>& paragraph)
{
    double x = 0.0;
    switch (align) {
        case TextAlign::LEFT:
            x = 0.0;
            break;
        case TextAlign::START:
            x = (GetTextDirection(text) == TextDirection::LTR) ? 0.0 : -paragraph->GetMaxIntrinsicWidth();
            break;
        case TextAlign::RIGHT:
            x = -paragraph->GetMaxIntrinsicWidth();
            break;
        case TextAlign::END:
            x = (GetTextDirection(text) == TextDirection::LTR) ? -paragraph->GetMaxIntrinsicWidth() : 0.0;
            break;
        case TextAlign::CENTER:
            x = -paragraph->GetMaxIntrinsicWidth() / 2;
            break;
        default:
            x = 0.0;
            break;
    }
    return x;
}

double OffscreenCanvasPaintMethod::GetBaselineOffset(TextBaseline baseline, std::unique_ptr<txt::Paragraph>& paragraph)
{
    double y = 0.0;
    switch (baseline) {
        case TextBaseline::ALPHABETIC:
            y = -paragraph->GetAlphabeticBaseline();
            break;
        case TextBaseline::IDEOGRAPHIC:
            y = -paragraph->GetIdeographicBaseline();
            break;
        case TextBaseline::BOTTOM:
            y = -paragraph->GetHeight();
            break;
        case TextBaseline::TOP:
            y = 0.0;
            break;
        case TextBaseline::MIDDLE:
            y = -paragraph->GetHeight() / 2;
            break;
        case TextBaseline::HANGING:
            y = -HANGING_PERCENT * (paragraph->GetHeight() - paragraph->GetAlphabeticBaseline());
            break;
        default:
            y = -paragraph->GetAlphabeticBaseline();
            break;
    }
    return y;
}

bool OffscreenCanvasPaintMethod::UpdateOffParagraph(const std::string& text, bool isStroke, const PaintState& state, bool hasShadow)
{
    using namespace Constants;
    txt::ParagraphStyle style;
    if (isStroke) {
        style.text_align = ConvertTxtTextAlign(strokeState_.GetTextAlign());
    } else {
        style.text_align = ConvertTxtTextAlign(fillState_.GetTextAlign());
    }
    style.text_direction = ConvertTxtTextDirection(state.GetOffTextDirection());
    auto fontCollection = FlutterFontCollection::GetInstance().GetFontCollection();
    if (!fontCollection) {
        return false;
    }
    std::unique_ptr<txt::ParagraphBuilder> builder = txt::ParagraphBuilder::CreateTxtBuilder(style, fontCollection);
    txt::TextStyle txtStyle;
    if (!isStroke && hasShadow) {
        txt::TextShadow txtShadow;
        txtShadow.color = shadow_.GetColor().GetValue();
        txtShadow.offset.fX = shadow_.GetOffset().GetX();
        txtShadow.offset.fY = shadow_.GetOffset().GetY();
        txtShadow.blur_radius = shadow_.GetBlurRadius();
        txtStyle.text_shadows.emplace_back(txtShadow);
    }
    txtStyle.locale = Localization::GetInstance()->GetFontLocale();
    UpdateTextStyleForeground(isStroke, txtStyle, hasShadow);
    builder->PushStyle(txtStyle);
    builder->AddText(StringUtils::Str8ToStr16(text));
    paragraph_ = builder->Build();
    return true;
}

void OffscreenCanvasPaintMethod::UpdateTextStyleForeground(bool isStroke, txt::TextStyle& txtStyle, bool hasShadow)
{
    using namespace Constants;
    if (!isStroke) {
        txtStyle.color = ConvertSkColor(fillState_.GetColor());
        txtStyle.font_size = fillState_.GetTextStyle().GetFontSize().Value();
        ConvertTxtStyle(fillState_.GetTextStyle(), context_, txtStyle);
        if (fillState_.GetGradient().IsValid()) {
            SkPaint paint;
            paint.setStyle(SkPaint::Style::kFill_Style);
            UpdatePaintShader(OffsetF(0, 0), paint, fillState_.GetGradient());
            txtStyle.foreground = paint;
            txtStyle.has_foreground = true;
        }
        if (globalState_.HasGlobalAlpha()) {
            if (txtStyle.has_foreground) {
                txtStyle.foreground.setColor(fillState_.GetColor().GetValue());
                txtStyle.foreground.setAlphaf(globalState_.GetAlpha()); // set alpha after color
            } else {
                SkPaint paint;
                paint.setColor(fillState_.GetColor().GetValue());
                paint.setAlphaf(globalState_.GetAlpha()); // set alpha after color
                txtStyle.foreground = paint;
                txtStyle.has_foreground = true;
            }
        }
    } else {
        // use foreground to draw stroke
        SkPaint paint = GetStrokePaint();
        ConvertTxtStyle(strokeState_.GetTextStyle(), context_, txtStyle);
        txtStyle.font_size = strokeState_.GetTextStyle().GetFontSize().Value();
        if (strokeState_.GetGradient().IsValid()) {
            UpdatePaintShader(OffsetF(0, 0), paint, strokeState_.GetGradient());
        }
        if (hasShadow) {
            paint.setColor(shadow_.GetColor().GetValue());
            paint.setMaskFilter(SkMaskFilter::MakeBlur(SkBlurStyle::kNormal_SkBlurStyle,
                FlutterDecorationPainter::ConvertRadiusToSigma(shadow_.GetBlurRadius())));
        }
        txtStyle.foreground = paint;
        txtStyle.has_foreground = true;
    }
}

TextDirection OffscreenCanvasPaintMethod::GetTextDirection(const std::string& content)
{
    TextDirection textDirection = TextDirection::LTR;
    auto showingTextForWString = StringUtils::ToWstring(content);
    for (const auto& charOfShowingText : showingTextForWString) {
        if (u_charDirection(charOfShowingText) == UCharDirection::U_LEFT_TO_RIGHT) {
            textDirection = TextDirection::LTR;
        } else if (u_charDirection(charOfShowingText) == UCharDirection::U_RIGHT_TO_LEFT) {
            textDirection = TextDirection::RTL;
        } else if (u_charDirection(charOfShowingText) == UCharDirection::U_RIGHT_TO_LEFT_ARABIC) {
            textDirection = TextDirection::RTL;
        }
    }
    return textDirection;
}

std::string OffscreenCanvasPaintMethod::ToDataURL(const std::string& type, const double quality)
{
    CHECK_NULL_RETURN(context_, UNSUPPORTED);
    std::string mimeType = GetMimeType(type);
    double qua = GetQuality(type, quality);
    SkBitmap tempCache;
    tempCache.allocPixels(SkImageInfo::Make(width_, height_, SkColorType::kBGRA_8888_SkColorType,
        (mimeType == IMAGE_JPEG) ? SkAlphaType::kOpaque_SkAlphaType : SkAlphaType::kUnpremul_SkAlphaType));
    SkCanvas tempCanvas(tempCache);
    double viewScale = context_->GetViewScale();
    tempCanvas.clear(SK_ColorTRANSPARENT);
    tempCanvas.scale(1.0 / viewScale, 1.0 / viewScale);
#ifdef USE_SYSTEM_SKIA_S
    //The return value of the dual framework interface has no alpha
    tempCanvas.drawImage(canvasCache_.asImage(), 0.0f, 0.0f);
#else
    tempCanvas.drawBitmap(canvasCache_, 0.0f, 0.0f);
#endif
    SkPixmap src;
    bool success = tempCache.peekPixels(&src);
    if (!success) {
        return UNSUPPORTED;
    }
    SkDynamicMemoryWStream dst;
    if (mimeType == IMAGE_JPEG) {
        SkJpegEncoder::Options options;
        options.fQuality = qua;
        success = SkJpegEncoder::Encode(&dst, src, options);
    } else if (mimeType == IMAGE_WEBP) {
        SkWebpEncoder::Options options;
        options.fQuality = qua * 100.0;
        success = SkWebpEncoder::Encode(&dst, src, options);
    } else {
        mimeType = IMAGE_PNG;
        SkPngEncoder::Options options;
        success = SkPngEncoder::Encode(&dst, src, options);
    }
    if (!success) {
        return UNSUPPORTED;
    }
    auto result = dst.detachAsData();
    if (result == nullptr) {
        return UNSUPPORTED;
    }
    size_t len = SkBase64::Encode(result->data(), result->size(), nullptr);
    if (len > MAX_LENGTH) {
        return UNSUPPORTED;
    }
    SkString info(len);
    SkBase64::Encode(result->data(), result->size(), info.writable_str());
    return std::string(URL_PREFIX).append(mimeType).append(URL_SYMBOL).append(info.c_str());
}
} // namespace OHOS::Ace::NG