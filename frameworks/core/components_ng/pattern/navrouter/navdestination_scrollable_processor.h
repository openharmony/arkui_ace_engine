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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVROUTER_NAVDESTINATION_SCROLLABLE_PROCESSOR_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVROUTER_NAVDESTINATION_SCROLLABLE_PROCESSOR_H

#include "frameworks/base/memory/ace_type.h"

namespace OHOS::Ace::NG {
class NavDestinationPattern;

class NavDestinationScrollableProcessor : public AceType {
    DECLARE_ACE_TYPE(NavDestinationScrollableProcessor, AceType);

public:
    NavDestinationScrollableProcessor() = default;
    ~NavDestinationScrollableProcessor() override = default;

    virtual void UpdateBindingRelation() = 0;
    virtual void SetNodeId(int32_t id) = 0;
    virtual void SetNavDestinationPattern(WeakPtr<NavDestinationPattern> pattern) = 0;
    virtual void UnbindAllScrollers() = 0;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVROUTER_NAVDESTINATION_SCROLLABLE_PROCESSOR_H
