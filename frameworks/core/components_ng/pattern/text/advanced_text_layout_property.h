/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_ADVANCED_TEXT_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_ADVANCED_TEXT_LAYOUT_PROPERTY_H
#include "ui/base/ace_type.h"
#include "interfaces/inner_api/ace_kit/include/ui/properties/gradient_property.h"

namespace OHOS::Ace {
class AdvancedTextLayoutProperty : public AceType {
    DECLARE_ACE_TYPE(AdvancedTextLayoutProperty, AceType);

public:
    void SetGradientShaderStyle(const std::optional<NG::Gradient>& gradient)
    {
        gradientShaderStyle_ = gradient;
    }

    const std::optional<NG::Gradient>& GetGradientShaderStyle() const
    {
        return gradientShaderStyle_;
    }

    void ResetGradientShaderStyle()
    {
        return gradientShaderStyle_.reset();
    }
private:
    std::optional<NG::Gradient> gradientShaderStyle_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_ADVANCED_TEXT_LAYOUT_PROPERTY_H