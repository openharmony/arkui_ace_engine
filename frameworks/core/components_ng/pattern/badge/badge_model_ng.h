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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BADGE_BADGE_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BADGE_BADGE_MODEL_NG_H

#include "core/components_ng/pattern/badge/badge_model.h"
#include "core/components_ng/pattern/badge/badge_pattern.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT BadgeModelNG : public OHOS::Ace::BadgeModel {
public:
    void Create(BadgeParameters& badgeParameters) override;
    void SetIsDefault(bool isDefaultFontSize, bool isDefaultBadgeSize) override
    {
        isDefaultFontSize_ = isDefaultFontSize;
        isDefaultBadgeSize_ = isDefaultBadgeSize;
    };
    void CreateWithResourceObj(const RefPtr<FrameNode>& frameNode, BadgeParameters& badgeParameters);
    void ProcessBadgeValue(const RefPtr<BadgePattern>& badgePattern, const RefPtr<ResourceObject>& resourceObject);
    void ProcessBadgeTextColor(const RefPtr<BadgePattern>& badgePattern, const RefPtr<ResourceObject>& resourceObject);
    void ProcessBadgeColor(const RefPtr<BadgePattern>& badgePattern, const RefPtr<ResourceObject>& resourceObject);
    void ProcessBorderColor(const RefPtr<BadgePattern>& badgePattern, const RefPtr<ResourceObject>& resourceObject);
    void ProcessFontWeight(const RefPtr<BadgePattern>& badgePattern, const RefPtr<ResourceObject>& resourceObject);
    void ProcessFontSize(const RefPtr<BadgePattern>& badgePattern, const RefPtr<ResourceObject>& resourceObject);
    void ProcessBadgeSize(const RefPtr<BadgePattern>& badgePattern, const RefPtr<ResourceObject>& resourceObject);
    void ProcessBadgePositionX(const RefPtr<BadgePattern>& badgePattern, const RefPtr<ResourceObject>& resourceObject);
    void ProcessBadgePositionY(const RefPtr<BadgePattern>& badgePattern, const RefPtr<ResourceObject>& resourceObject);
    void ProcessBorderWidth(const RefPtr<BadgePattern>& badgePattern, const RefPtr<ResourceObject>& resourceObject);
    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static void SetBadgeParam(
        FrameNode* frameNode, BadgeParameters& badgeParameters, bool isDefaultFontSize, bool isDefaultBadgeSize);

private:
    static void UpdateBadgeStyle(BadgeParameters& badgeParameters, const RefPtr<FrameNode>& frameNode);
    bool isDefaultFontSize_ = true;
    bool isDefaultBadgeSize_ = true;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BADGE_BADGE_MODEL_NG_H
