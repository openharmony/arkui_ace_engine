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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BADGE_BADGE_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BADGE_BADGE_MODEL_H

#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/badge/badge_data.h"

namespace OHOS::Ace {
class ACE_FORCE_EXPORT BadgeModel {
public:
    static BadgeModel* GetInstance();
    virtual ~BadgeModel() = default;

    virtual void Create(BadgeParameters& badgeParameters) = 0;
    virtual void CreateByFrameNode(const RefPtr<NG::FrameNode>& frameNode, BadgeParameters& badgeParameters) = 0;
    virtual RefPtr<NG::FrameNode> CreateBadgeFrameNode() = 0;
    virtual void SetIsDefault(bool isDefaultFontSize, bool isDefaultBadgeSize) = 0;

private:
    static std::unique_ptr<BadgeModel> instance_;
    static std::mutex mutex_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BADGE_BADGE_MODEL_H
