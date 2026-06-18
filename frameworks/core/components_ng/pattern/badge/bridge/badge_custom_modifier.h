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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BADGE_BRIDGE_BADGE_CUSTOM_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BADGE_BRIDGE_BADGE_CUSTOM_MODIFIER_H

#include "core/interfaces/native/node/node_api.h"
#include "core/components_ng/pattern/badge/badge_model_ng.h"
#include "core/components_ng/pattern/badge/badge_pattern.h"
#include "core/interfaces/native/generated/interface/arkoala_api_generated.h"

namespace OHOS::Ace {
struct BadgeParameters;
namespace NG {
class FrameNode;
class BadgePattern;
}

struct ArkUIBadgeCustomModifier {
    void (*setBadgeParam)(
        NG::FrameNode* frameNode, BadgeParameters& badgeParameters, bool isDefaultFontSize, bool isDefaultBadgeSize);
    void (*updateBadgeColor)(const RefPtr<NG::BadgePattern>& selectPattern, const Color& badgeColor, bool isFirstLoad);
    void (*updateColor)(const RefPtr<NG::BadgePattern>& selectPattern, const Color& color, bool isFirstLoad);
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BADGE_BRIDGE_BADGE_CUSTOM_MODIFIER_H