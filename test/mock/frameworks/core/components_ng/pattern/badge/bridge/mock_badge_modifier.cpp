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
#include "core/interfaces/native/node/badge_modifier.h"
#include "core/components_ng/pattern/badge/badge_model_ng.h"
namespace OHOS::Ace::NG {
ArkUINodeHandle CreateBadge(ArkUI_Uint32 nodeId)
{
    auto frameNode = BadgeModelNG::CreateFrameNode(static_cast<int32_t>(nodeId));
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode));
}
void SetBadgeParam(NG::FrameNode* frameNode, BadgeParameters& badgeParameters, bool isDefaultFontSize,
    bool isDefaultBadgeSize)
{
    CHECK_NULL_VOID(frameNode);
    BadgeModelNG::SetBadgeParam(frameNode, badgeParameters, isDefaultFontSize, isDefaultBadgeSize);
}

void UpdateBadgeColor(const RefPtr<BadgePattern>& badgePattern, const Color& badgeColor, bool isFirstLoad)
{
    CHECK_NULL_VOID(badgePattern);
    badgePattern->UpdateBadgeColor(badgeColor, isFirstLoad);
}

void UpdateColor(const RefPtr<BadgePattern>& badgePattern, const Color& color, bool isFirstLoad)
{
    CHECK_NULL_VOID(badgePattern);
    badgePattern->UpdateColor(color, isFirstLoad);
}
namespace NodeModifier {
const ArkUIBadgeModifier* GetBadgeModifier()
{
    static const ArkUIBadgeModifier modifier = {
        .createBadgeFrameNode = CreateBadge,
    };
    return &modifier;
}
const ArkUIBadgeCustomModifier* GetBadgeCustomModifier()
{
    static const ArkUIBadgeCustomModifier modifier = {
        .setBadgeParam = SetBadgeParam,
        .updateBadgeColor = UpdateBadgeColor,
        .updateColor = UpdateColor,
    };
    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG