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

#include "core/components_ng/property/constraint_flags.h"
namespace OHOS::Ace::NG {
void ConstraintFlags::UpdateFlags(
    const std::optional<LayoutConstraintF>& preConstraint, const std::optional<LayoutConstraintF>& constraint)
{
    if (preConstraint && constraint) {
        idealSize = preConstraint->selfIdealSize == constraint->selfIdealSize;
        parentIdealSize = preConstraint->parentIdealSize == constraint->parentIdealSize;
        minSize = preConstraint->minSize == constraint->minSize;
        maxSize = preConstraint->maxSize == constraint->maxSize;
        percentRef = preConstraint->percentReference == constraint->percentReference;
        scaleProperty = preConstraint->scaleProperty == constraint->scaleProperty;
    } else if (preConstraint || constraint) {
        idealSize = true;
        parentIdealSize = true;
        minSize = true;
        maxSize = true;
        percentRef = true;
        scaleProperty = true;
    }
}

std::string ConstraintFlags::ToString() const
{
    std::string result = "ConstraintFlags: ";
    result += "idealSize: " + std::to_string(idealSize) + ", ";
    result += "parentIdealSize: " + std::to_string(parentIdealSize) + ", ";
    result += "minSize: " + std::to_string(minSize) + ", ";
    result += "maxSize: " + std::to_string(maxSize) + ", ";
    result += "percentRef: " + std::to_string(percentRef) + ", ";
    result += "scaleProperty: " + std::to_string(scaleProperty);
    return result;
}
} // namespace OHOS::Ace::NG
