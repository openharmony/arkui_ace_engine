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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PROPERTIES_CONSTRAINT_FLAGS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PROPERTIES_CONSTRAINT_FLAGS_H
#include "core/components_ng/property/layout_constraint.h"
namespace OHOS::Ace::NG {
struct ConstraintFlags {
    /**
    * @brief Compare previous layout constraint and current layout constraint to update flags.
    *
    * @param preConstraint previous layout constraint
    * @param constraint current layout constraint
    */
    void UpdateFlags(
        const std::optional<LayoutConstraintF>& preConstraint, const std::optional<LayoutConstraintF>& constraint);

    std::string ToString() const;

    bool idealSize = false;
    bool parentIdealSize = false;
    bool minSize = false;
    bool maxSize = false;
    bool percentRef = false;
    bool scaleProperty = false;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PROPERTIES_CONSTRAINT_FLAGS_H
