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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_NAVIGATION_MODEL_DATA_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_NAVIGATION_MODEL_DATA_H

#include "frameworks/base/utils/macros.h"
#include "frameworks/core/event/ace_events.h"

namespace OHOS::Ace {
class ACE_EXPORT NavigationTitleModeChangeEvent : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(NavigationTitleModeChangeEvent, BaseEventInfo);

public:
    explicit NavigationTitleModeChangeEvent(bool isMiniBar)
        : BaseEventInfo("NavigationTitleModeChangeEvent"), isMiniBar_(isMiniBar)
    {}
    ~NavigationTitleModeChangeEvent() = default;

    bool IsMiniBar() const
    {
        return isMiniBar_;
    }

private:
    bool isMiniBar_ = 0;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_NAVIGATION_MODEL_DATA_H