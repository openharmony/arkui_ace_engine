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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CONTAINER_PICKER_ACCESSIBILITY_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CONTAINER_PICKER_ACCESSIBILITY_PROPERTY_H

#include "core/components_ng/property/accessibility_property.h"

namespace OHOS::Ace::NG {
class ContainerPickerAccessibilityProperty : public AccessibilityProperty {
    DECLARE_ACE_TYPE(ContainerPickerAccessibilityProperty, AccessibilityProperty);

public:
    ContainerPickerAccessibilityProperty() = default;

    ~ContainerPickerAccessibilityProperty() override = default;

    std::string GetText() const override;

    int32_t GetCurrentIndex() const override;

    int32_t GetBeginIndex() const override;

    int32_t GetEndIndex() const override;

    bool HasRange() const override
    {
        return true;
    }

    AccessibilityValue GetAccessibilityValue() const override;

    bool IsScrollable() const override;

    int32_t GetCollectionItemCounts() const override;

protected:
    void SetSpecificSupportAction() override;

private:
    ACE_DISALLOW_COPY_AND_MOVE(ContainerPickerAccessibilityProperty);
};
} // namespace OHOS::Ace::NG

#endif
