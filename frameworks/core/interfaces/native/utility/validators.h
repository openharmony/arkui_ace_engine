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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_UTILITY_VALIDATORS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_UTILITY_VALIDATORS_H

#include <optional>

#include "base/geometry/calc_dimension.h"
#include "base/geometry/dimension.h"
#include "core/components/common/properties/animation_option.h"
#include "core/components/picker/picker_data.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_v2/grid_layout/grid_container_util_class.h"

namespace OHOS::Ace::NG {
namespace Validator {
void ClampByRange(std::optional<float>& opt, const float& left, const float& right);
void ValidateNonNegative(std::optional<Dimension>& opt);
void ValidateNonPercent(std::optional<Dimension>& opt);
void ValidatePositive(std::optional<Dimension>& opt);
void ValidateOpacity(std::optional<float>& opt);
void ValidatePositive(std::optional<float>& value);
void ValidateNonNegative(std::optional<float>& value);
void ValidateGreatOrEqual(std::optional<float>& opt, const float& right);
void ValidateLessOrEqual(std::optional<float>& opt, const float& right);
void ValidateByRange(std::optional<float>& opt, const float& left, const float& right);
void ValidateNonNegative(std::optional<CalcDimension>& opt);
void ValidateNonPercent(std::optional<CalcDimension>& opt);
void ValidateNonEmpty(std::optional<CalcDimension>& opt);
void ValidateNonEmpty(std::optional<std::string>& opt);
template<class T> void ValidateNonEmpty(std::optional<T>& opt)
{
    if (opt.has_value() && opt.value().empty()) {
        opt.reset();
    }
}
void ValidateNonNegative(std::optional<int>& value);
void ValidateGreatOrEqual(std::optional<int32_t>& opt, const int32_t& right);
void ValidatePositive(std::optional<int>& value);
void ValidateNonNegative(std::optional<V2::GridContainerSize>& value);
void ValidateBloom(std::optional<float>& opt);
void ValidateIntensity(std::optional<float>& opt);
void ValidateNonNegative(std::optional<CalcLength>& opt);
void ValidateNonPercent(std::optional<CalcLength>& opt);
void ValidatePickerDate(PickerDate& date);
void ValidateAnimationOption(AnimationOption& opt, bool isForm);
} // namespace OHOS::Ace::NG::Validator
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_UTILITY_VALIDATORS_H
