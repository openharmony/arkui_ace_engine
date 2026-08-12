/*
 * Copyright (c) 2023-2026 Huawei Device Co., Ltd.
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

const char BADGE_ETS_TAG[] = "Badge";
class ACE_EXPORT BadgeModelNG : public OHOS::Ace::BadgeModel {
public:
    void Create(BadgeParameters& badgeParameters) override;
    void CreateByFrameNode(const RefPtr<FrameNode>& frameNode, BadgeParameters& badgeParameters) override;
    RefPtr<FrameNode> CreateBadgeFrameNode() override;
    void SetIsDefault(bool isDefaultFontSize, bool isDefaultBadgeSize) override
    {
        isDefaultFontSize_ = isDefaultFontSize;
        isDefaultBadgeSize_ = isDefaultBadgeSize;
    };
    void CreateWithResourceObj(const RefPtr<FrameNode>& frameNode, BadgeParameters& badgeParameters);
    void CreateWithResourceObjFlag(const RefPtr<FrameNode>& frameNode, BadgeParameters& badgeParameters);
    void ProcessBadgeValue(const RefPtr<BadgePattern>& badgePattern, const RefPtr<ResourceObject>& resourceObject);
    void ProcessBadgeTextColor(const RefPtr<BadgePattern>& badgePattern, const RefPtr<ResourceObject>& resourceObject,
        const RefPtr<FrameNode>& frameNode);
    void ProcessBadgeColor(const RefPtr<BadgePattern>& badgePattern, const RefPtr<ResourceObject>& resourceObject,
        const RefPtr<FrameNode>& frameNode);
    void ProcessBorderColor(const RefPtr<BadgePattern>& badgePattern, const RefPtr<ResourceObject>& resourceObject,
        const RefPtr<FrameNode>& frameNode);
    void ProcessOuterBorderColor(
        const RefPtr<BadgePattern>& badgePattern, const RefPtr<ResourceObject>& resourceObject);
    void ProcessFontWeight(const RefPtr<BadgePattern>& badgePattern, const RefPtr<ResourceObject>& resourceObject);
    void ProcessFontSize(const RefPtr<BadgePattern>& badgePattern, const RefPtr<ResourceObject>& resourceObject);
    void ProcessBadgeSize(const RefPtr<BadgePattern>& badgePattern, const RefPtr<ResourceObject>& resourceObject);
    void ProcessBadgePositionX(const RefPtr<BadgePattern>& badgePattern, const RefPtr<ResourceObject>& resourceObject);
    void ProcessBadgePositionY(const RefPtr<BadgePattern>& badgePattern, const RefPtr<ResourceObject>& resourceObject);
    void ProcessBorderWidth(const RefPtr<BadgePattern>& badgePattern, const RefPtr<ResourceObject>& resourceObject);
    void ProcessOuterBorderWidth(
        const RefPtr<BadgePattern>& badgePattern, const RefPtr<ResourceObject>& resourceObject);
    static void CreateModel(
        BadgeParameters& badgeParameters, bool isDefaultFontSize = true, bool isDefaultBadgeSize = true);
    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static void CreateJSBadgeByFrameNode(const RefPtr<FrameNode>& frameNode, BadgeParameters& badgeParameters,
        bool isDefaultFontSize, bool isDefaultBadgeSize);
    static void SetBadgeParam(
        FrameNode* frameNode, BadgeParameters& badgeParameters, bool isDefaultFontSize, bool isDefaultBadgeSize);
    static void CreateWithResObj(const RefPtr<FrameNode>& frameNode, BadgeParameters& badgeParameters);
    static void ProcessBadgeValueStatic(
        const RefPtr<BadgePattern>& badgePattern, const RefPtr<ResourceObject>& resourceObject);
    static void ProcessBadgeTextColorStatic(const RefPtr<BadgePattern>& BadgePattern,
        RefPtr<ResourceObject>& resourceObject, const RefPtr<FrameNode>& frameNode);
    static void ProcessBadgeColorStatic(const RefPtr<BadgePattern>& badgePattern,
        RefPtr<ResourceObject>& resourceObject, const RefPtr<FrameNode>& frameNode);
    static void ProcessBorderColorStatic(const RefPtr<BadgePattern>& BadgePattern,
        RefPtr<ResourceObject>& resourceObject, const RefPtr<FrameNode>& frameNode);
    static void ProcessOuterBorderColorStatic(
        const RefPtr<BadgePattern>& badgePattern, RefPtr<ResourceObject>& resourceObject);
    static void ProcessFontWeightStatic(
        const RefPtr<BadgePattern>& badgePattern, const RefPtr<ResourceObject>& resourceObject);
    static void ProcessFontSizeStatic(
        const RefPtr<BadgePattern>& badgePattern, const RefPtr<ResourceObject>& resourceObject);
    static void ProcessBadgeSizeStatic(
        const RefPtr<BadgePattern>& badgePattern, const RefPtr<ResourceObject>& resourceObject);
    static void ProcessBadgePositionXStatic(
        const RefPtr<BadgePattern>& badgePattern, const RefPtr<ResourceObject>& resourceObject);
    static void ProcessBadgePositionYStatic(
        const RefPtr<BadgePattern>& badgePattern, const RefPtr<ResourceObject>& resourceObject);
    static void ProcessBorderWidthStatic(
        const RefPtr<BadgePattern>& badgePattern, const RefPtr<ResourceObject>& resourceObject);
    static void ProcessOuterBorderWidthStatic(
        const RefPtr<BadgePattern>& badgePattern, const RefPtr<ResourceObject>& resourceObject);

private:
    static void UpdateBadgeStyle(BadgeParameters& badgeParameters, const RefPtr<FrameNode>& frameNode);
    bool isDefaultFontSize_ = true;
    bool isDefaultBadgeSize_ = true;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BADGE_BADGE_MODEL_NG_H
