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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_INDICATOR_ACCESSIBILITY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_INDICATOR_ACCESSIBILITY_H

#include "base/utils/utils.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_indicator_accessibility_property.h"

namespace OHOS::Ace::NG {
class IndicatorAccessibilityProperty : public SwiperIndicatorAccessibilityProperty {
    DECLARE_ACE_TYPE(IndicatorAccessibilityProperty, SwiperIndicatorAccessibilityProperty);

public:
    IndicatorAccessibilityProperty() = default;

    ~IndicatorAccessibilityProperty() override = default;

    int32_t GetCurrentIndex() const override;

    int32_t GetBeginIndex() const override;

    int32_t GetEndIndex() const override;

    int32_t GetCollectionItemCounts() const override;

    AccessibilityValue GetAccessibilityValue() const override;

    std::string GetAccessibilityLevel() const override
    {
        return Level::AUTO;
    }

protected:
    RefPtr<FrameNode> GetSwiperNode() const override;

private:
    ACE_DISALLOW_COPY_AND_MOVE(IndicatorAccessibilityProperty);
};
} // namespace OHOS::Ace::NG

#endif
