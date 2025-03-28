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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_progress_ffi.h"

#include "core/components_ng/pattern/progress/progress_model_ng.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::NG;
using namespace OHOS::Ace::Framework;

namespace {
const std::vector<ProgressType> PROGRESS_TYPES = { ProgressType::LINEAR, ProgressType::RING, ProgressType::MOON,
    ProgressType::SCALE, ProgressType::CAPSULE };

const std::vector<NG::ProgressType> PROGRESS_TYPES_NG = { NG::ProgressType::LINEAR, NG::ProgressType::RING,
    NG::ProgressType::MOON, NG::ProgressType::SCALE, NG::ProgressType::CAPSULE };

} // namespace

extern "C" {
void FfiOHOSAceFrameworkProgressCreate(double value, double total, int32_t type)
{
    if (!Utils::CheckParamsValid(type, PROGRESS_TYPES.size())) {
        LOGE("invalid value for progress type");
        return;
    }

    double realTotal = total > 0 ? total : 100;
    double realValue = value;
    if (value > realTotal) {
        realValue = realTotal;
    } else if (value < 0) {
        realValue = 0;
    }

    ProgressModel::GetInstance()->Create(0.0, realValue, 0.0, realTotal, PROGRESS_TYPES_NG[type]);
}

void FfiOHOSAceFrameworkProgressSetValue(double value)
{
    double realValue = value;
    if (value < 0) {
        realValue = 0;
    }

    ProgressModel::GetInstance()->SetValue(realValue);
}

void FfiOHOSAceFrameworkProgressSetColor(uint32_t color)
{
    ProgressModel::GetInstance()->SetColor(Color(color));
}

void FfiOHOSAceFrameworkProgressSetBackgroundColor(uint32_t color)
{
    ProgressModel::GetInstance()->SetBackgroundColor(Color(color));
}

void FfiOHOSAceFrameworkProgressSetGradientColor(
    std::vector<uint32_t> color, std::vector<double> number, std::vector<int32_t> unitType)
{
    size_t size = color.size();
    NG::Gradient gradient;
    if (size == 1) {
        NG::GradientColor gradientColor;
        gradientColor.SetLinearColor(LinearColor(color[0]));
        CalcDimension colorDimension(number[0], static_cast<DimensionUnit>(unitType[0]));
        gradientColor.SetDimension(colorDimension);
        gradient.AddColor(gradientColor);
        gradient.AddColor(gradientColor);
        ProgressModel::GetInstance()->SetGradientColor(gradient);
        return;
    }

    for (size_t colorIndex = 0; colorIndex < size; colorIndex++) {
        NG::GradientColor gradientColor;
        gradientColor.SetLinearColor(LinearColor(color[colorIndex]));
        CalcDimension colorDimension(number[colorIndex], static_cast<DimensionUnit>(unitType[colorIndex]));
        gradientColor.SetDimension(colorDimension);
        gradient.AddColor(gradientColor);
    }
    ProgressModel::GetInstance()->SetGradientColor(gradient);
}

void FfiOHOSAceFrameworkProgressSetStyle(
    double strokeWidth, int32_t strokeWidthUnit, int32_t scaleCount, double scaleWidth, int32_t scaleWidthUnit)
{
    Dimension strokeWidthValue(strokeWidth, static_cast<DimensionUnit>(strokeWidthUnit));
    Dimension scaleWidthValue(scaleWidth, static_cast<DimensionUnit>(scaleWidthUnit));

    ProgressModel::GetInstance()->SetStrokeWidth(strokeWidthValue);
    ProgressModel::GetInstance()->SetScaleCount(scaleCount);
    ProgressModel::GetInstance()->SetScaleWidth(scaleWidthValue);
}

void FfiOHOSAceFrameworkProgressSetLinearStyle(LinearStyle linearStyle)
{
    CalcDimension strokeWidthDimension(linearStyle.widthValue, static_cast<DimensionUnit>(linearStyle.widthUnitType));
    ProgressModel::GetInstance()->SetStrokeWidth(strokeWidthDimension);
    ProgressModel::GetInstance()->SetLinearSweepingEffect(linearStyle.enableScanEffect);
    CalcDimension strokeRadiusDimension(
        linearStyle.radiusValue, static_cast<DimensionUnit>(linearStyle.radiusUnitType));
    if (LessNotEqual(strokeRadiusDimension.Value(), 0.0f) || strokeRadiusDimension.Unit() == DimensionUnit::PERCENT) {
        ProgressModel::GetInstance()->ResetStrokeRadius();
        return;
    }
    ProgressModel::GetInstance()->SetStrokeRadius(strokeRadiusDimension);
}

void FfiOHOSAceFrameworkProgressSetCapsuleStyle(CapsuleStyle capsuleStyle, const char* family)
{
    CalcDimension borderWidth(capsuleStyle.borderWidthValue, static_cast<DimensionUnit>(capsuleStyle.borderWidthUnit));
    ProgressModel::GetInstance()->SetBorderWidth(borderWidth);
    ProgressModel::GetInstance()->SetBorderColor(static_cast<const OHOS::Ace::Color>(capsuleStyle.borderColor));
    ProgressModel::GetInstance()->SetSweepingEffect(capsuleStyle.enableScanEffect);
    ProgressModel::GetInstance()->SetShowText(capsuleStyle.showDefaultPercentage);
    capsuleStyle.content == NULL ? ProgressModel::GetInstance()->SetText(std::nullopt)
                                 : ProgressModel::GetInstance()->SetText(capsuleStyle.content);
    ProgressModel::GetInstance()->SetFontColor(Color(capsuleStyle.fontColor));
    CalcDimension fontSize(capsuleStyle.fontSizeValue, static_cast<DimensionUnit>(capsuleStyle.fontSizeUnit));
    ProgressModel::GetInstance()->SetFontSize(fontSize);
    ProgressModel::GetInstance()->SetFontWeight(static_cast<FontWeight>(capsuleStyle.fontWeight));
    ProgressModel::GetInstance()->SetFontFamily(ConvertStrToFontFamilies(family));
    ProgressModel::GetInstance()->SetItalicFontStyle(static_cast<OHOS::Ace::FontStyle>(capsuleStyle.fontStyle));
    ProgressModel::GetInstance()->SetSmoothEffect(capsuleStyle.enableSmoothEffect);
}

void FfiOHOSAceFrameworkProgressSetScaleRingStyle(ScaleRingStyle scaleRingStyle)
{
    CalcDimension strokeWidthDimension(
        scaleRingStyle.strokeWidthValue, static_cast<DimensionUnit>(scaleRingStyle.strokeWidthUnit));
    ProgressModel::GetInstance()->SetStrokeWidth(strokeWidthDimension);
    ProgressModel::GetInstance()->SetScaleCount(scaleRingStyle.scaleCount);

    ProgressModel::GetInstance()->SetSmoothEffect(scaleRingStyle.enableSmoothEffect);
    CalcDimension scaleWidthDimension(
        scaleRingStyle.scaleWidthValue, static_cast<DimensionUnit>(scaleRingStyle.scaleWidthUnit));
    ProgressModel::GetInstance()->SetScaleWidth(scaleWidthDimension);
}

void FfiOHOSAceFrameworkProgressSetRingStyle(RingStyle ringStyle)
{
    CalcDimension strokeWidthDimension(ringStyle.value, static_cast<DimensionUnit>(ringStyle.unitType));
    ProgressModel::GetInstance()->SetStrokeWidth(strokeWidthDimension);
    ProgressModel::GetInstance()->SetPaintShadow(ringStyle.shadow);

    ProgressModel::GetInstance()->SetProgressStatus(static_cast<ProgressStatus>(ringStyle.status));
    ProgressModel::GetInstance()->SetRingSweepingEffect(ringStyle.enableScanEffect);
    ProgressModel::GetInstance()->SetSmoothEffect(ringStyle.enableSmoothEffect);
}

void FfiOHOSAceFrameworkProgressSetEclipseStyle(bool enableSmoothEffect)
{
    ProgressModel::GetInstance()->SetSmoothEffect(enableSmoothEffect);
}
}
