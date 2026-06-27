/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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

#include "bridge/common/utils/utils.h"
#include "core/components_ng/pattern/progress/progress_model_ng.h"
#include "core/components/progress/progress_theme.h"
#include "core/common/dynamic_module_helper.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::NG;
using namespace OHOS::Ace::Framework;

namespace {
const std::vector<ProgressType> PROGRESS_TYPES = { ProgressType::LINEAR, ProgressType::RING, ProgressType::MOON,
    ProgressType::SCALE, ProgressType::CAPSULE };

const std::vector<NG::ProgressType> PROGRESS_TYPES_NG = { NG::ProgressType::LINEAR, NG::ProgressType::RING,
    NG::ProgressType::MOON, NG::ProgressType::SCALE, NG::ProgressType::CAPSULE };

} // namespace

namespace OHOS::Ace {

NG::ProgressModelNG* GetProgressModel()
{
    static NG::ProgressModelNG* cachedModel = nullptr;
    if (cachedModel == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Progress");
        if (module == nullptr) {
            LOGF_ABORT("Can't find progress dynamic module");
        }
        cachedModel = reinterpret_cast<NG::ProgressModelNG*>(module->GetModel());
    }
    return cachedModel;
}
} // namespace OHOS::Ace

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

    GetProgressModel()->Create(0.0, realValue, 0.0, realTotal, PROGRESS_TYPES_NG[type]);
}

void FfiOHOSAceFrameworkProgressSetValue(double value)
{
    double realValue = value;
    if (value < 0) {
        realValue = 0;
    }

    GetProgressModel()->SetValue(realValue);
}

void FfiOHOSAceFrameworkProgressSetColor(uint32_t color)
{
    GetProgressModel()->SetColor(Color(color));
}

void FfiOHOSAceFrameworkProgressResetColor(int32_t type)
{
    if (!Utils::CheckParamsValid(type, PROGRESS_TYPES.size())) {
        LOGE("invalid value for progress type");
        return;
    }
    Color colorVal;
    NG::Gradient gradient;
    bool gradientColorByUser = true;
    RefPtr<ProgressTheme> theme = OHOS::Ace::Framework::GetTheme<ProgressTheme>();
    CHECK_NULL_VOID(theme);
    Color endColor;
    Color beginColor;
    colorVal = (PROGRESS_TYPES[type] == ProgressType::CAPSULE) ? theme->GetCapsuleSelectColor()
                                                               : theme->GetTrackSelectedColor();

    endColor = theme->GetRingProgressEndSideColor();
    beginColor = theme->GetRingProgressBeginSideColor();
    gradientColorByUser = false;
    NG::GradientColor endSideColor;
    NG::GradientColor beginSideColor;
    endSideColor.SetLinearColor(LinearColor(endColor));
    endSideColor.SetDimension(Dimension(0.0f));
    beginSideColor.SetLinearColor(LinearColor(beginColor));
    beginSideColor.SetDimension(Dimension(1.0f));
    gradient.AddColor(endSideColor);
    gradient.AddColor(beginSideColor);
    GetProgressModel()->SetGradientColor(gradient);
    GetProgressModel()->SetColor(colorVal);
}

void FfiOHOSAceFrameworkProgressSetBackgroundColor(uint32_t color)
{
    GetProgressModel()->SetBackgroundColor(Color(color));
}

void FfiOHOSAceFrameworkProgressResetBackgroundColor(int32_t type)
{
    if (!Utils::CheckParamsValid(type, PROGRESS_TYPES.size())) {
        LOGE("invalid value for progress type");
        return;
    }
    Color colorVal;
    RefPtr<ProgressTheme> theme = OHOS::Ace::Framework::GetTheme<ProgressTheme>();
    CHECK_NULL_VOID(theme);
    colorVal = (PROGRESS_TYPES[type] == ProgressType::CAPSULE) ? theme->GetCapsuleBgColor()
               : (PROGRESS_TYPES[type] == ProgressType::RING)  ? theme->GetRingProgressBgColor()
                                                               : theme->GetTrackBgColor();
    GetProgressModel()->SetBackgroundColor(colorVal);
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
        GetProgressModel()->SetGradientColor(gradient);
        return;
    }

    for (size_t colorIndex = 0; colorIndex < size; colorIndex++) {
        NG::GradientColor gradientColor;
        gradientColor.SetLinearColor(LinearColor(color[colorIndex]));
        CalcDimension colorDimension(number[colorIndex], static_cast<DimensionUnit>(unitType[colorIndex]));
        gradientColor.SetDimension(colorDimension);
        gradient.AddColor(gradientColor);
    }
    GetProgressModel()->SetGradientColor(gradient);
}

void FfiOHOSAceFrameworkProgressSetStyle(
    double strokeWidth, int32_t strokeWidthUnit, int32_t scaleCount, double scaleWidth, int32_t scaleWidthUnit)
{
    Dimension strokeWidthValue(strokeWidth, static_cast<DimensionUnit>(strokeWidthUnit));
    Dimension scaleWidthValue(scaleWidth, static_cast<DimensionUnit>(scaleWidthUnit));

    GetProgressModel()->SetStrokeWidth(strokeWidthValue);
    GetProgressModel()->SetScaleCount(scaleCount);
    GetProgressModel()->SetScaleWidth(scaleWidthValue);
}

void FfiOHOSAceFrameworkProgressSetLinearStyle(LinearStyle linearStyle)
{
    CalcDimension strokeWidthDimension(linearStyle.widthValue, static_cast<DimensionUnit>(linearStyle.widthUnitType));
    GetProgressModel()->SetStrokeWidth(strokeWidthDimension);
    GetProgressModel()->SetLinearSweepingEffect(linearStyle.enableScanEffect);
    CalcDimension strokeRadiusDimension(
        linearStyle.radiusValue, static_cast<DimensionUnit>(linearStyle.radiusUnitType));
    if (LessNotEqual(strokeRadiusDimension.Value(), 0.0f) || strokeRadiusDimension.Unit() == DimensionUnit::PERCENT) {
        GetProgressModel()->ResetStrokeRadius();
        return;
    }
    GetProgressModel()->SetStrokeRadius(strokeRadiusDimension);
}

void FfiOHOSAceFrameworkProgressSetCapsuleStyle(CapsuleStyle capsuleStyle, const char* family)
{
    CalcDimension borderWidth(capsuleStyle.borderWidthValue, static_cast<DimensionUnit>(capsuleStyle.borderWidthUnit));
    GetProgressModel()->SetBorderWidth(borderWidth);
    GetProgressModel()->SetBorderColor(static_cast<const OHOS::Ace::Color>(capsuleStyle.borderColor));
    GetProgressModel()->SetSweepingEffect(capsuleStyle.enableScanEffect);
    GetProgressModel()->SetShowText(capsuleStyle.showDefaultPercentage);
    capsuleStyle.content == NULL ? GetProgressModel()->SetText(std::nullopt)
                                 : GetProgressModel()->SetText(capsuleStyle.content);
    GetProgressModel()->SetFontColor(Color(capsuleStyle.fontColor));
    CalcDimension fontSize(capsuleStyle.fontSizeValue, static_cast<DimensionUnit>(capsuleStyle.fontSizeUnit));
    GetProgressModel()->SetFontSize(fontSize);
    GetProgressModel()->SetFontWeight(static_cast<FontWeight>(capsuleStyle.fontWeight));
    GetProgressModel()->SetFontFamily(ConvertStrToFontFamilies(family));
    GetProgressModel()->SetItalicFontStyle(static_cast<OHOS::Ace::FontStyle>(capsuleStyle.fontStyle));
    GetProgressModel()->SetSmoothEffect(capsuleStyle.enableSmoothEffect);
}

void FfiOHOSAceFrameworkProgressSetScaleRingStyle(ScaleRingStyle scaleRingStyle)
{
    CalcDimension strokeWidthDimension(
        scaleRingStyle.strokeWidthValue, static_cast<DimensionUnit>(scaleRingStyle.strokeWidthUnit));
    GetProgressModel()->SetStrokeWidth(strokeWidthDimension);
    GetProgressModel()->SetScaleCount(scaleRingStyle.scaleCount);

    GetProgressModel()->SetSmoothEffect(scaleRingStyle.enableSmoothEffect);
    CalcDimension scaleWidthDimension(
        scaleRingStyle.scaleWidthValue, static_cast<DimensionUnit>(scaleRingStyle.scaleWidthUnit));
    GetProgressModel()->SetScaleWidth(scaleWidthDimension);
}

void FfiOHOSAceFrameworkProgressSetRingStyle(RingStyle ringStyle)
{
    CalcDimension strokeWidthDimension(ringStyle.value, static_cast<DimensionUnit>(ringStyle.unitType));
    GetProgressModel()->SetStrokeWidth(strokeWidthDimension);
    GetProgressModel()->SetPaintShadow(ringStyle.shadow);

    GetProgressModel()->SetProgressStatus(static_cast<ProgressStatus>(ringStyle.status));
    GetProgressModel()->SetRingSweepingEffect(ringStyle.enableScanEffect);
    GetProgressModel()->SetSmoothEffect(ringStyle.enableSmoothEffect);
}

void FfiOHOSAceFrameworkProgressSetEclipseStyle(bool enableSmoothEffect)
{
    GetProgressModel()->SetSmoothEffect(enableSmoothEffect);
}
}
