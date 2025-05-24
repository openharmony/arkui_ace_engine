/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BADGE_BADGE_DATA_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BADGE_BADGE_DATA_H

#include <optional>

#include "base/geometry/dimension.h"
#include "core/common/resource/resource_object.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/badge/badge_layout_property.h"

namespace OHOS::Ace {
struct BadgeParameters {
    std::optional<std::string> badgeValue;
    std::optional<int> badgeCount;
    std::optional<int> badgeMaxCount;
    std::optional<int> badgePosition;
    std::optional<bool> isPositionXy;
    std::optional<Dimension> badgePositionX;
    std::optional<Dimension> badgePositionY;

    std::optional<Color> badgeColor;
    std::optional<Color> badgeTextColor;
    std::optional<Color> badgeBorderColor;
    std::optional<Dimension> badgeFontSize;
    std::optional<Dimension> badgeCircleSize;
    std::optional<Dimension> badgeBorderWidth;
    std::optional<FontWeight> badgeFontWeight;

    RefPtr<ResourceObject> resourceBadgeValueObject;
    RefPtr<ResourceObject> resourceColorObject;
    RefPtr<ResourceObject> resourceBadgeColorObject;
    RefPtr<ResourceObject> resourceBorderColorObject;
    RefPtr<ResourceObject> resourceFontWeightObject;
    RefPtr<ResourceObject> resourceBadgeSizeObject;
    RefPtr<ResourceObject> resourceFontSizeObject;
    RefPtr<ResourceObject> resourceBadgePositionXObject;
    RefPtr<ResourceObject> resourceBadgePositionYObject;
    RefPtr<ResourceObject> resourceBorderWidthObject;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BADGE_BADGE_DATA_H