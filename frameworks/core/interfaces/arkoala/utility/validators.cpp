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

#include "validators.h"

namespace OHOS::Ace::NG {
namespace Validator {
void ValidateNonNegative(std::optional<Dimension>& opt)
{
    if (opt.has_value() && opt.value().IsNegative()) {
        opt.reset();
    }
}
void ValidateNonPercent(std::optional<Dimension>& opt)
{
    if (opt.has_value() && (opt.value().Unit() == DimensionUnit::PERCENT)) {
        opt.reset();
    }
}
void ValidatePositive(std::optional<Dimension>& opt)
{
    if (opt.has_value() && opt.value().IsNonPositive()) {
        opt.reset();
    }
}
} // namespace OHOS::Ace::NG::Validator
} // namespace OHOS::Ace::NG