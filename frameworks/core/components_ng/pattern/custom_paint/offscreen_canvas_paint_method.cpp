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

#include "base/utils/utils.h"
#include "core/components/common/painter/flutter_decoration_painter.h"

namespace OHOS::Ace::NG {
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
        cacheBitmap_.asImage(), srcRect, dstRect, SkSamplingOptions(), nullptr, SkCanvas::kFast_SrcRectConstraint);
#else
    tempCanvas.drawBitmapRect(cacheBitmap_, srcRect, dstRect, nullptr);
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
} // namespace OHOS::Ace::NG