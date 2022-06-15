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

#include "base/utils/string_utils.h"
#include "base/utils/utils.h"

namespace OHOS::Ace {
std::string Dimension::ToString() const
{
    static const int32_t unitsNum = 6;
    static const int32_t percentIndex = 3;
    static const int32_t percentUnit = 100;
    static std::array<std::string, unitsNum> units = { "px", "vp", "fp", "%", "lpx", "auto" };
    if (units[static_cast<int>(unit_)] == units[percentIndex]) {
        return StringUtils::DoubleToString(value_ * percentUnit).append(units[static_cast<int>(unit_)]);
    }
    return StringUtils::DoubleToString(value_).append(units[static_cast<int>(unit_)]);
}

bool Dimension::NormalizeToPx(
    double vpScale, double fpScale, double lpxScale, double parentLength, double& result) const
{
    if (unit_ == DimensionUnit::PX) {
        result = value_;
        return true;
    }
    if (unit_ == DimensionUnit::PERCENT) {
        if (NonNegative(parentLength)) {
            result = value_ * parentLength;
            return true;
        }
        return false;
    }
    if (unit_ == DimensionUnit::VP) {
        if (Positive(vpScale)) {
            result = value_ * vpScale;
            return true;
        }
        return false;
    }
    if (unit_ == DimensionUnit::FP) {
        if (Positive(fpScale)) {
            result = value_ * fpScale;
            return true;
        }
        return false;
    }
    if (unit_ == DimensionUnit::LPX) {
        if (Positive(lpxScale)) {
            result = value_ * lpxScale;
            return true;
        }
        return false;
    }
    return false;
}
} // namespace OHOS::Ace