/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_PICKER_CONTAINER_PICKER_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_PICKER_CONTAINER_PICKER_UTILS_H

#include <optional>

#include "base/geometry/axis.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/container_picker/container_picker_layout_property.h"
#include "core/components_ng/property/measure_utils.h"
namespace OHOS::Ace::NG {
namespace {
    const float PICKER_ITEM_DEFAULT_HEIGHT = 130.0f;
} // namespace
class ContainerPickerUtils {
public:
    ContainerPickerUtils() = delete;
    ~ContainerPickerUtils() = delete;

    static LayoutConstraintF CreateChildConstraint(
        const RefPtr<ContainerPickerLayoutProperty>& property, const OptionalSizeF& idealSize)
    {
        CHECK_NULL_RETURN(property, {});
        auto layoutConstraint = property->CreateChildConstraint();
        layoutConstraint.parentIdealSize = idealSize;
        auto displayCount = 7;
        if (NonPositive(static_cast<double>(displayCount))) {
            return layoutConstraint;
        }
        auto childSelfIdealSize = idealSize;
        childSelfIdealSize.SetHeight(PICKER_ITEM_DEFAULT_HEIGHT);
        return CheckLayoutPolicyConstraint(property, childSelfIdealSize, layoutConstraint);
    }

    static LayoutConstraintF CheckLayoutPolicyConstraint(const RefPtr<ContainerPickerLayoutProperty>& property,
        OptionalSizeF childSelfIdealSize, LayoutConstraintF layoutConstraint)
    {
        auto layoutPolicy = property->GetLayoutPolicyProperty();
        if (layoutPolicy.has_value()) {
            auto widthLayoutPolicy = layoutPolicy.value().widthLayoutPolicy_.value_or(LayoutCalPolicy::NO_MATCH);
            // crosss axis set maxSize and reset IdealSize'cross width/heigth, when layoutPolicy is matchParent
            if (widthLayoutPolicy == LayoutCalPolicy::MATCH_PARENT) {
                auto widthOpt = childSelfIdealSize.Width();
                if (widthOpt) {
                    layoutConstraint.maxSize.SetWidth(widthOpt.value());
                }
                auto height = childSelfIdealSize.Height();
                childSelfIdealSize.Reset();
                childSelfIdealSize.SetHeight(height);
            }
        }
        layoutConstraint.selfIdealSize = childSelfIdealSize;
        return layoutConstraint;
    }
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_PICKER_CONTAINER_PICKER_UTILS_H