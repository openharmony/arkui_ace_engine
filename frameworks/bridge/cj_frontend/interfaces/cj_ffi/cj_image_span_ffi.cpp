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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_image_span_ffi.h"

#include "core/components_ng/pattern/image/image_model.h"
#include "core/components_ng/pattern/text/image_span_view.h"

using namespace OHOS::Ace::Framework;
using namespace OHOS::Ace;

const std::vector<ImageFit> IMAGE_FITS = {
    ImageFit::FILL,
    ImageFit::CONTAIN,
    ImageFit::COVER,
    ImageFit::NONE,
    ImageFit::SCALE_DOWN,
    ImageFit::FITWIDTH
};

const std::vector<VerticalAlign> VERTICAL_ALIGNS = {
    VerticalAlign::TOP,
    VerticalAlign::CENTER,
    VerticalAlign::BOTTOM,
    VerticalAlign::BASELINE
};

TextBackgroundStyle ParseTextBackgroundStyle(uint32_t color, double radiusDouble, int32_t unit)
{
    TextBackgroundStyle textBackgroundStyle;
    Color colorVal = Color(color);
    Dimension value(radiusDouble, static_cast<DimensionUnit>(unit));
    CalcDimension radius = CalcDimension(value);
    if (radius.Unit() == DimensionUnit::PERCENT) {
        radius.Reset();
    }
    textBackgroundStyle.backgroundColor = colorVal;
    textBackgroundStyle.backgroundRadius = { radius, radius, radius, radius };
    textBackgroundStyle.backgroundRadius->multiValued = false;
    return textBackgroundStyle;
}

TextBackgroundStyle ParseTextBackgroundStyle(uint32_t color, CBorderRadiuses radiusValue)
{
    TextBackgroundStyle textBackgroundStyle;
    Color colorVal = Color(color);
    Dimension topLeftValue(radiusValue.topLeftRadiuses,
        static_cast<DimensionUnit>(radiusValue.topLeftUnit));
    CalcDimension topLeft = CalcDimension(topLeftValue);
    Dimension topRightValue(radiusValue.topRightRadiuses,
        static_cast<DimensionUnit>(radiusValue.topRightUnit));
    CalcDimension topRight = CalcDimension(topRightValue);
    Dimension bottomLeftValue(radiusValue.bottomLeftRadiuses,
        static_cast<DimensionUnit>(radiusValue.bottomLeftUnit));
    CalcDimension bottomLeft = CalcDimension(bottomLeftValue);
    Dimension bottomRightValue(radiusValue.bottomRightRadiuses,
        static_cast<DimensionUnit>(radiusValue.bottomRightUnit));
    CalcDimension bottomRight = CalcDimension(bottomRightValue);
    textBackgroundStyle.backgroundColor = colorVal;
    textBackgroundStyle.backgroundRadius = { topLeft, topRight, bottomRight, bottomLeft };
    textBackgroundStyle.backgroundRadius->multiValued = false;
    return textBackgroundStyle;
}

extern "C" {
void FfiOHOSAceFrameworkImageSpanCreateWithUrl(const char* url)
{
    if (!Container::IsCurrentUseNewPipeline()) {
        return;
    }
    FfiOHOSAceFrameworkImageCreateWithUrl(url);
    NG::ImageSpanView::Create();
}

void FfiOHOSAceFrameworkImageSpanCreateWithPixelMap(int64_t id)
{
    if (!Container::IsCurrentUseNewPipeline()) {
        return;
    }
    FfiOHOSAceFrameworkImageCreateWithPixelMap(id);
    NG::ImageSpanView::Create();
}

void FfiOHOSAceFrameworkImageSpanVerticalAlign(int32_t value)
{
    if (!OHOS::Ace::Framework::Utils::CheckParamsValid(value, VERTICAL_ALIGNS.size())) {
        LOGE("invalid value for vertical align");
        return;
    }
    NG::ImageSpanView::SetVerticalAlign(VERTICAL_ALIGNS[value]);
}

void FfiOHOSAceFrameworkImageSpanObjectFit(int32_t value)
{
    if (!OHOS::Ace::Framework::Utils::CheckParamsValid(value, IMAGE_FITS.size())) {
        LOGE("invalid value for image fit");
        return;
    }
    ImageModel::GetInstance()->SetImageFit(IMAGE_FITS[value]);
}

void FfiOHOSAceFrameworkImageSpanTextBackgroundStyle(uint32_t color, double radius, int32_t unit)
{
    auto textBackgroundStyle = ParseTextBackgroundStyle(color, radius, unit);
    NG::ImageSpanView::SetPlaceHolderStyle(textBackgroundStyle);
}

void FfiOHOSAceFrameworkImageSpanTextBackgroundStyleBorder(uint32_t color, CBorderRadiuses radius)
{
    auto textBackgroundStyle = ParseTextBackgroundStyle(color, radius);
    NG::ImageSpanView::SetPlaceHolderStyle(textBackgroundStyle);
}
}
