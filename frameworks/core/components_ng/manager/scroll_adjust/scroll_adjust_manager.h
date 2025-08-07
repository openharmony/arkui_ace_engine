/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SCROLLADJUST_SCROLL_ADJUST_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SCROLLADJUST_SCROLL_ADJUST_MANAGER_H

#include <string>
#include "core/components_ng/pattern/scrollable/scrollable_properties.h"

namespace OHOS::Ace::NG {
class ScrollAdjustmanager : public virtual AceType {
    DECLARE_ACE_TYPE(ScrollAdjustmanager, AceType);
public:
    static ScrollAdjustmanager& GetInstance();
    ScrollAdjustmanager() = default;
    ~ScrollAdjustmanager() = default;
    bool ChangeScrollStateIfNeed(ScrollState scrollState);
    int32_t AdjustEndIndex(int32_t endIndex);
    int32_t AdjustCachedCount(int32_t cachedCount);
private:
    bool idle_ = true;
};
} //namespace OHOS::ACE:NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SCROLLADJUST_SCROLL_ADJUST_MANAGER_H