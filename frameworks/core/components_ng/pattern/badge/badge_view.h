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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BADGE_BADGE_VIEW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BADGE_BADGE_VIEW_H

#include <optional>

#include "base/geometry/dimension.h"
#include "core/components/common/properties/color.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT BadgeView {
public:
    struct BadgeParameters {
        std::optional<std::string> badgeValue;
        std::optional<int> badgeCount;
        std::optional<int> badgeMaxCount;
        std::optional<int> badgePosition;

        std::optional<Color> badgeColor;
        std::optional<Color> badgeTextColor;
        std::optional<Dimension> badgeFontSize;
        std::optional<Dimension> badgeCircleSize;
    };

    static void Create(BadgeParameters& badgeParameters);
    static void Pop();
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BADGE_BADGE_VIEW_H
