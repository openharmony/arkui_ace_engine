/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_VIEW_COMPONENTS_BADGE_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_VIEW_COMPONENTS_BADGE_H

#include "ui/base/geometry/dimension.h"
#include "ui/base/macros.h"
#include "ui/base/referenced.h"
#include "ui/view/view.h"
#include "ui/resource/resource_object.h"

namespace OHOS::Ace::Kit {

class FrameNode;

struct BadgeParametersKit {
    std::optional<std::string> badgeValue;
    std::optional<int32_t> badgeCount;
    std::optional<int32_t> badgeMaxCount;
    std::optional<int32_t> badgePosition;
    std::optional<bool> isPositionXy;
    std::optional<Dimension> badgePositionX;
    std::optional<Dimension> badgePositionY;

    std::optional<Color> badgeColor;
    std::optional<Color> badgeTextColor;
    std::optional<Color> badgeBorderColor;
    std::optional<Color> badgeOuterBorderColor;
    std::optional<Dimension> badgeFontSize;
    std::optional<Dimension> badgeCircleSize;
    std::optional<Dimension> badgeBorderWidth;
    std::optional<Dimension> badgeOuterBorderWidth;
    std::optional<int32_t> badgeFontWeight;
    std::optional<bool> isEnableAutoAvoidance;

    RefPtr<ResourceObject> resourceBadgeValueObject;
    RefPtr<ResourceObject> resourceColorObject;
    RefPtr<ResourceObject> resourceBadgeColorObject;
    RefPtr<ResourceObject> resourceBorderColorObject;
    RefPtr<ResourceObject> resourceOuterBorderColorObject;
    RefPtr<ResourceObject> resourceFontWeightObject;
    RefPtr<ResourceObject> resourceBadgeSizeObject;
    RefPtr<ResourceObject> resourceFontSizeObject;
    RefPtr<ResourceObject> resourceBadgePositionXObject;
    RefPtr<ResourceObject> resourceBadgePositionYObject;
    RefPtr<ResourceObject> resourceBorderWidthObject;
    RefPtr<ResourceObject> resourceOuterBorderWidthObject;
};

class ACE_FORCE_EXPORT Badge : public View {
public:
    static RefPtr<Badge> Create(const RefPtr<FrameNode>& node);
    Badge(const RefPtr<FrameNode>& node);
    ~Badge() override;

    void SetBadgeParams(BadgeParametersKit& style, bool isDefaultFontSize, bool isDefaultBadgeSize);
private:
    void UpdateBadgeUserFlags(BadgeParametersKit& badgeParameters);
    void HandleBadgeColor(const RefPtr<ResourceObject>& resourceObject);
    void HandleBadgeTextColor(const RefPtr<ResourceObject>& resourceObject);
};

} // namespace OHOS::Ace::Kit
#endif // FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_VIEW_COMPONENTS_BADGE_H
