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

#include "frameworks/bridge/declarative_frontend/jsview/models/badge_model_impl.h"

#include "core/components/badge/badge_component.h"
#include "core/components/badge/badge_theme.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {
void BadgeModelImpl::Create(BadgeParameters& badgeParameters)
{
    auto badge = AceType::MakeRefPtr<OHOS::Ace::BadgeComponent>();
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto badgeTheme = pipeline->GetTheme<BadgeTheme>();

    if (badgeParameters.badgeValue.has_value()) {
        badge->SetBadgeLabel(badgeParameters.badgeValue.value());
    }

    if (badgeParameters.badgeCount.has_value()) {
        badge->SetMessageCount(badgeParameters.badgeCount.value());
    } else {
        badge->SetMessageCount(badgeTheme->GetMessageCount());
    }

    if (badgeParameters.badgeMaxCount.has_value()) {
        badge->SetMaxCount(badgeParameters.badgeMaxCount.value());
    }

    if (badgeParameters.badgeColor.has_value()) {
        badge->SetBadgeColor(badgeParameters.badgeColor.value());
    } else {
        badge->SetBadgeColor(badgeTheme->GetBadgeColor());
    }

    if (badgeParameters.badgeTextColor.has_value()) {
        badge->SetBadgeTextColor(badgeParameters.badgeTextColor.value());
    } else {
        badge->SetBadgeTextColor(badgeTheme->GetBadgeTextColor());
    }

    if (badgeParameters.badgeFontSize.has_value()) {
        badge->SetBadgeFontSize(badgeParameters.badgeFontSize.value());
    } else {
        badge->SetBadgeFontSize(badgeTheme->GetBadgeFontSize());
    }

    if (badgeParameters.badgeCircleSize.has_value()) {
        badge->SetBadgeCircleSize(badgeParameters.badgeCircleSize.value());
    } else {
        badge->SetBadgeCircleSize(badgeTheme->GetBadgeCircleSize());
    }

    SetPositionForBadge(badgeParameters);
    ViewStackProcessor::GetInstance()->ClaimElementId(badge);
    ViewStackProcessor::GetInstance()->Push(badge);
}

void BadgeModelImpl::SetPositionForBadge(BadgeParameters& badgeParameters)
{
    auto badge = AceType::MakeRefPtr<OHOS::Ace::BadgeComponent>();
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto badgeTheme = pipeline->GetTheme<BadgeTheme>();

    if (badgeParameters.badgePosition.has_value()) {
        badge->SetBadgePosition(static_cast<BadgePosition>(badgeParameters.badgePosition.value()));
    } else {
        badge->SetBadgePosition(badgeTheme->GetBadgePosition());
    }

    if (badgeParameters.badgePositionX.has_value()) {
        badge->SetBadgePositionX(badgeParameters.badgePositionX.value());
    } else {
        badge->SetBadgePositionX(badgeTheme->GetBadgePositionX());
    }

    if (badgeParameters.badgePositionY.has_value()) {
        badge->SetBadgePositionY(badgeParameters.badgePositionY.value());
    } else {
        badge->SetBadgePositionY(badgeTheme->GetBadgePositionY());
    }

    if (badgeParameters.isPositionXy.has_value()) {
        badge->SetIsPositionXy(badgeParameters.isPositionXy.value());
    } else {
        badge->SetIsPositionXy(badgeTheme->GetIsPositionXy());
    }
}
} // namespace OHOS::Ace::Framework
