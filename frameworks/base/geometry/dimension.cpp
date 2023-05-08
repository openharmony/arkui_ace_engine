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

#include <array>
#include <functional>

#include "base/utils/string_utils.h"
#include "base/utils/utils.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace {

namespace {
struct CalcDimensionParam {
    float value = 0.0f;
    float vpScale = 0.0f;
    float fpScale = 0.0f;
    float lpxScale = 0.0f;
    float parentLength = 0.0f;
    float rootWidth = 0.0f;
    float rootHeight = 0.0f;
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

bool CalcDimensionVw(const CalcDimensionParam& param, double& result)
{
    if (NearZero(param.rootWidth)) {
        LOGE("PipelineContext's RootWidth is 0");
        return false;
    }
    result = param.value * param.rootWidth;
    return true;
}

bool CalcDimensionVh(const CalcDimensionParam& param, double& result)
{
    if (NearZero(param.rootHeight)) {
        LOGE("PipelineContext's RootHeight is 0");
        return false;
    }
    result = param.value * param.rootHeight;
    return true;
}

std::unordered_map<DimensionUnit, CalcDimensionFunc> calcDimensionFuncMap_ = {
    { DimensionUnit::NONE, &CalcDimensionNone }, { DimensionUnit::PX, &CalcDimensionPx },
    { DimensionUnit::PERCENT, &CalcDimensionPercent }, { DimensionUnit::VP, &CalcDimensionVp },
    { DimensionUnit::FP, &CalcDimensionFp }, { DimensionUnit::LPX, &CalcDimensionLpx },
    { DimensionUnit::VW, &CalcDimensionVw }, { DimensionUnit::VH, &CalcDimensionVh }
};
} // namespace

double Dimension::ConvertToVp() const
{
    if (unit_ == DimensionUnit::VP) {
        return value_;
    }

    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, 0.0);
    if (unit_ == DimensionUnit::NONE) {
        return value_ / pipeline->GetDipScale();
    }
    if (unit_ == DimensionUnit::PX) {
        return value_ / pipeline->GetDipScale();
    }
    if (unit_ == DimensionUnit::FP) {
        return value_ * pipeline->GetFontScale();
    }
    if (unit_ == DimensionUnit::LPX) {
        return value_ * pipeline->GetLogicScale() / pipeline->GetDipScale();
    }
    LOGE("fail to ConvertToVp, %{public}f, %{public}d", value_, unit_);
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

    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, 0.0);
    if (unit_ == DimensionUnit::VP) {
        return value_ * pipeline->GetDipScale();
    }
    if (unit_ == DimensionUnit::FP) {
        return value_ * pipeline->GetDipScale() * pipeline->GetFontScale();
    }
    if (unit_ == DimensionUnit::LPX) {
        return value_ * pipeline->GetLogicScale();
    }
    LOGE("fail to ConvertToPx, %{public}f, %{public}d", value_, unit_);
    return 0.0;
}

double Dimension::ConvertToPxWithSize(double size) const
{
    if (unit_ == DimensionUnit::PERCENT) {
        return value_ * size;
    }
    return ConvertToPx();
}

std::string Dimension::ToString() const
{
    static const int32_t unitsNum = 8;
    static const int32_t percentIndex = 3;
    static const int32_t percentUnit = 100;
    static std::array<std::string, unitsNum> units = { "px", "vp", "fp", "%", "lpx", "auto", "vw", "vh" };
    if (units[static_cast<int>(unit_)] == units[percentIndex]) {
        return StringUtils::DoubleToString(value_ * percentUnit).append(units[static_cast<int>(unit_)]);
    }
    return StringUtils::DoubleToString(value_).append(units[static_cast<int>(unit_)]);
}

bool Dimension::NormalizeToPx(
    double vpScale, double fpScale, double lpxScale, double parentLength, double& result) const
{
    auto func = calcDimensionFuncMap_.find(unit_);
    if (func != calcDimensionFuncMap_.end()) {
        auto pipeline = PipelineBase::GetCurrentContext();
        CHECK_NULL_RETURN(pipeline, false);
        auto rootWidth = pipeline->GetRootWidth();
        auto rootHeight = pipeline->GetRootHeight();
        CalcDimensionParam param = { value_, vpScale, fpScale, lpxScale, parentLength, rootWidth, rootHeight };
        return func->second(param, result);
    }
    return false;
}
} // namespace OHOS::Ace
