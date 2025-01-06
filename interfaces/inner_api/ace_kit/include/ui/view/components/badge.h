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

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_VIEW_COMPONENTS_BADGE_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_VIEW_COMPONENTS_BADGE_H

#include "ui/base/geometry/dimension.h"
#include "ui/base/macros.h"
#include "ui/view/view.h"
#include "ui/view/components/badge_data.h"

namespace OHOS::Ace::Kit {

class FrameNode;
class BadgePattern;

class ACE_FORCE_EXPORT Badge : public View {
public:
    static RefPtr<Badge> Create();
    static RefPtr<Badge> CreateCustom(const std::string& tag, const RefPtr<BadgePattern>& pattern);
    ~Badge();
    Badge();
    Badge(const std::string& tag, const RefPtr<BadgePattern>& pattern);

    void SetBadgeParam(BadgeParameters& params, bool isDefaultFontSize, bool isDefaultBadgeSize);
};

} // namespace OHOS::Ace::Kit
#endif // FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_VIEW_COMPONENTS_BADGE_H
