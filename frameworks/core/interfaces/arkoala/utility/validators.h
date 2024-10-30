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

#include "base/geometry/dimension.h"
#include "base/geometry/calc_dimension.h"

namespace OHOS::Ace::NG {
namespace Validator {
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
void ValidateNonNegative(std::optional<int>& value);
} // namespace OHOS::Ace::NG::Validator
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_UTILITY_VALIDATORS_H
