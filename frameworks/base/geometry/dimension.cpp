/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "base/geometry/dimension.h"

#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace {

namespace {
struct CalcDimensionParam {
    float value = 0.0f;
    float vpScale = 0.0f;
    float fpScale = 0.0f;
    float lpxScale = 0.0f;
    float parentLength = 0.0f;
};

using CalcDimensionFunc = std::function<bool(const CalcDimensionParam& param, double& result)>;
bool CalcDimensionNone(const CalcDimensionParam& param, double& result)
{
    result = param.value;
    return true;
}

bool CalcDimensionPx(const CalcDimensionParam& param, double& result)
{
    result = param.value;
    return true;
}

bool CalcDimensionPercent(const CalcDimensionParam& param, double& result)
{
    if (NonNegative(param.parentLength)) {
        result = param.value * param.parentLength;
        return true;
    }
    return false;
}

bool CalcDimensionVp(const CalcDimensionParam& param, double& result)
{
    if (Positive(param.vpScale)) {
        result = param.value * param.vpScale;
        return true;
    }
    return false;
}

bool CalcDimensionFp(const CalcDimensionParam& param, double& result)
{
    if (Positive(param.fpScale) && Positive(param.vpScale)) {
        result = param.value * param.fpScale * param.vpScale;
        return true;
    }
    return false;
}

bool CalcDimensionLpx(const CalcDimensionParam& param, double& result)
{
    if (Positive(param.lpxScale)) {
        result = param.value * param.lpxScale;
        return true;
    }
    return false;
}

std::unordered_map<DimensionUnit, CalcDimensionFunc> calcDimensionFuncMap_ = {
    { DimensionUnit::NONE, &CalcDimensionNone }, { DimensionUnit::PX, &CalcDimensionPx },
    { DimensionUnit::PERCENT, &CalcDimensionPercent }, { DimensionUnit::VP, &CalcDimensionVp },
    { DimensionUnit::FP, &CalcDimensionFp }, { DimensionUnit::LPX, &CalcDimensionLpx }
};
} // namespace

double Dimension::ConvertToVp() const
{
    if (unit_ == DimensionUnit::VP) {
        return value_;
    }

    auto pipeline = PipelineBase::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, 0.0);
    if (unit_ == DimensionUnit::NONE) {
        return value_ / pipeline->GetDipScale();
    }
    if (unit_ == DimensionUnit::PX) {
        return value_ / pipeline->GetDipScale();
    }
    if (unit_ == DimensionUnit::FP) {
        return ConvertToVpByAppFontScale();
    }
    if (unit_ == DimensionUnit::LPX) {
        return value_ * pipeline->GetLogicScale() / pipeline->GetDipScale();
    }
    return 0.0;
}

double Dimension::ConvertToPx() const
{
    if (unit_ == DimensionUnit::NONE) {
        return value_;
    }
    if (unit_ == DimensionUnit::PX) {
        return value_;
    }

    auto pipeline = PipelineBase::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, 0.0);
    if (unit_ == DimensionUnit::VP) {
        return value_ * pipeline->GetDipScale();
    }
    if (unit_ == DimensionUnit::FP) {
        return ConvertToPxByAppFontScale(0.0f);
    }
    if (unit_ == DimensionUnit::LPX) {
        return value_ * pipeline->GetLogicScale();
    }
    return 0.0;
}

double Dimension::ConvertToFp() const
{
    if (unit_ == DimensionUnit::FP) {
        return value_;
    }
    auto pipeline = PipelineBase::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, 0.0);
    auto fontScale = std::clamp(pipeline->GetFontScale(), 0.0f, pipeline->GetMaxAppFontScale());
    if (LessOrEqual(fontScale, 0.0)) {
        return 0.0;
    }
    if (unit_ == DimensionUnit::NONE) {
        return value_ / pipeline->GetDipScale() / fontScale;
    }
    if (unit_ == DimensionUnit::PX) {
        return value_ / pipeline->GetDipScale() / fontScale;
    }
    if (unit_ == DimensionUnit::VP) {
        return value_ / fontScale;
    }
    if (unit_ == DimensionUnit::LPX) {
        return value_ * pipeline->GetLogicScale() / pipeline->GetDipScale() / fontScale;
    }
    return 0.0;
}

double Dimension::ConvertToPxWithSize(double size) const
{
    if (unit_ == DimensionUnit::PERCENT) {
        return value_ * size;
    }
    return ConvertToPx();
}

DimensionUnit Dimension::GetAdaptDimensionUnit(const Dimension& dimension)
{
    return static_cast<int32_t>(unit_) <= static_cast<int32_t>(dimension.unit_) ? unit_ : dimension.unit_;
}

double Dimension::ConvertToPxDistribute(
    std::optional<float> minOptional, std::optional<float> maxOptional, bool allowScale) const
{
    if (unit_ != DimensionUnit::FP) {
        return ConvertToPx();
    }
    auto pipeline = PipelineBase::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, value_);
    if (!allowScale) {
        return value_ * pipeline->GetDipScale();
    }
    auto minFontScale = minOptional.value_or(0.0f);
    auto maxFontScale = maxOptional.value_or(static_cast<float>(INT32_MAX));
    if (!maxOptional.has_value()) {
        return ConvertToPxByAppFontScale(minFontScale);
    }
    return ConvertToPxByCustomFontScale(minFontScale, maxFontScale);
}

double Dimension::ConvertToPxByCustomFontScale(float minFontScale, float maxFontScale) const
{
    auto pipeline = PipelineBase::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, value_);
    float fontScale = std::clamp(pipeline->GetFontScale(), minFontScale, maxFontScale);
    return value_ * pipeline->GetDipScale() * fontScale;
}

double Dimension::ConvertToPxByAppFontScale(float minFontScale) const
{
    auto pipeline = PipelineBase::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, value_);
    float maxFontScale = pipeline->GetMaxAppFontScale();
    float fontScale = std::clamp(pipeline->GetFontScale(), minFontScale, maxFontScale);
    return value_ * pipeline->GetDipScale() * fontScale;
}

double Dimension::ConvertToVpByAppFontScale() const
{
    auto pipeline = PipelineBase::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, value_);
    CHECK_NULL_RETURN(pipeline->IsFollowSystem(), value_);
    float maxFontScale = pipeline->GetMaxAppFontScale();
    float fontScale = std::clamp(pipeline->GetFontScale(), 0.0f, maxFontScale);
    return value_ * fontScale;
}

std::string Dimension::ToString() const
{
    static const int32_t unitsNum = 6;
    static const int32_t percentIndex = 3;
    static const int32_t percentUnit = 100;
    static std::array<std::string, unitsNum> units = { "px", "vp", "fp", "%", "lpx", "auto" };
    if (static_cast<int32_t>(unit_) >= unitsNum ||
        static_cast<int32_t>(unit_) < static_cast<int32_t>(DimensionUnit::INVALID)) {
        return StringUtils::DoubleToString(value_).append("px");
    }
    if (unit_ == DimensionUnit::NONE) {
        return StringUtils::DoubleToString(value_).append("none");
    }
    if (unit_ == DimensionUnit::INVALID) {
        return StringUtils::DoubleToString(value_).append("invalid");
    }
    if (units[static_cast<int>(unit_)] == units[percentIndex]) {
        return StringUtils::DoubleToString(value_ * percentUnit).append(units[static_cast<int>(unit_)]);
    }
    return StringUtils::DoubleToString(value_).append(units[static_cast<int>(unit_)]);
}

// for example str = 0.00px
Dimension Dimension::FromString(const std::string& str)
{
    static const int32_t percentUnit = 100;
    static const std::unordered_map<std::string, DimensionUnit> uMap {
        { "px", DimensionUnit::PX },
        { "vp", DimensionUnit::VP },
        { "fp", DimensionUnit::FP },
        { "%", DimensionUnit::PERCENT },
        { "lpx", DimensionUnit::LPX },
        { "auto", DimensionUnit::AUTO },
    };

    double value = 0.0;
    DimensionUnit unit = DimensionUnit::FP;

    if (str.empty()) {
        LOGE("UITree |ERROR| empty string");
        return Dimension(value, unit);
    }

    for (int32_t i = static_cast<int32_t>(str.length() - 1); i >= 0; --i) {
        if (str[i] >= '0' && str[i] <= '9') {
            value = StringUtils::StringToDouble(str.substr(0, i + 1));
            auto subStr = str.substr(i + 1);
            auto iter = uMap.find(subStr);
            if (iter != uMap.end()) {
                unit = iter->second;
            }
            value = unit == DimensionUnit::PERCENT ? value / percentUnit : value;
            break;
        }
    }
    return Dimension(value, unit);
}

bool Dimension::NormalizeToPx(
    double vpScale, double fpScale, double lpxScale, double parentLength, double& result) const
{
    auto func = calcDimensionFuncMap_.find(unit_);
    if (func != calcDimensionFuncMap_.end()) {
        CalcDimensionParam param = { static_cast<float>(value_), static_cast<float>(vpScale),
            static_cast<float>(fpScale), static_cast<float>(lpxScale), static_cast<float>(parentLength) };
        return func->second(param, result);
    }
    return false;
}
} // namespace OHOS::Ace
