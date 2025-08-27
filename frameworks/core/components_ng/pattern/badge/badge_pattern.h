/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BADGE_BADGE_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BADGE_BADGE_PATTERN_H

#include "base/memory/referenced.h"
#include "core/components_ng/pattern/badge/badge_accessibility_property.h"
#include "core/components_ng/pattern/badge/badge_layout_algorithm.h"
#include "core/components_ng/pattern/badge/badge_layout_property.h"
#include "core/components_ng/pattern/pattern.h"

namespace OHOS::Ace::NG {

class BadgePattern : public Pattern {
    DECLARE_ACE_TYPE(BadgePattern, Pattern);

public:
    BadgePattern() = default;
    ~BadgePattern() override = default;

    bool IsAtomicNode() const override
    {
        return false;
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<BadgeLayoutProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<BadgeLayoutAlgorithm>();
    }

    RefPtr<AccessibilityProperty> CreateAccessibilityProperty() override
    {
        return MakeRefPtr<BadgeAccessibilityProperty>();
    }
    void OnColorModeChange(uint32_t colorMode) override;
    void UpdateBadgeValue(const std::string& badgeValue, bool isFirstLoad = false);
    void UpdateColor(const Color& color, bool isFirstLoad = false);
    void UpdateBadgeColor(const Color& badgeColor, bool isFirstLoad = false);
    void UpdateBorderColor(const Color& borderColor, bool isFirstLoad = false);
    void UpdateFontWeight(FontWeight fontWeight, bool isFirstLoad = false);
    void UpdateFontSize(const CalcDimension& fontSize, bool isDefaultFontSize, bool isFirstLoad = false);
    void UpdateBadgeCircleSize(const CalcDimension& badgeCircleSize, bool isDefaultBadgeSize, bool isFirstLoad = false);
    void UpdateBadgePositionX(const CalcDimension& positionX, bool isFirstLoad = false);
    void UpdateBadgePositionY(const CalcDimension& positionY, bool isFirstLoad = false);
    void UpdateBorderWidth(const CalcDimension& borderWidth, bool isFirstLoad = false);
    void OnColorConfigurationUpdate() override;

private:
    void OnModifyDone() override;
    void DumpInfo() override;
    void DumpInfo(std::unique_ptr<JsonValue>& json) override;
    void DumpSimplifyInfo(std::shared_ptr<JsonValue>& json) override;
    int32_t textNodeId_ = -2;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BADGE_BADGE_PATTERN_H
