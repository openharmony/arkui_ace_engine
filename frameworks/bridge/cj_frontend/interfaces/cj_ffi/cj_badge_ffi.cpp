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

#include "cj_badge_ffi.h"

#include "core/components_ng/pattern/badge/badge_model_ng.h"

using namespace OHOS::Ace;

namespace {
BadgeParameters CreateBase(CJBadgeStyle style, int32_t position)
{
    BadgeParameters badgeParameters;
    badgeParameters.badgePosition = position;
    badgeParameters.badgeTextColor = Color(style.color);
    badgeParameters.badgeFontSize = Dimension(style.fontSize, DimensionUnit::VP);
    badgeParameters.badgeCircleSize = Dimension(style.badgeSize, DimensionUnit::VP);
    badgeParameters.badgeColor = Color(style.badgeColor);
    return badgeParameters;
}
} // namespace

extern "C" {
void FfiOHOSAceFrameworkBadgeCreate(int32_t count, CJBadgeStyle style, int32_t position, int32_t maxCount)
{
    BadgeParameters badgeParameters = CreateBase(style, position);
    badgeParameters.badgeCount = count;
    badgeParameters.badgeMaxCount = maxCount;
    BadgeModel::GetInstance()->Create(badgeParameters);
}

void FfiOHOSAceFrameworkBadgeCreateText(const char* value, CJBadgeStyle style, int32_t position)
{
    BadgeParameters badgeParameters = CreateBase(style, position);
    badgeParameters.badgeValue = value;
    BadgeModel::GetInstance()->Create(badgeParameters);
}
}
