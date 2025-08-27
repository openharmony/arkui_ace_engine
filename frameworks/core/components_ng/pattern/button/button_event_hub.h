/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BUTTON_BUTTON_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BUTTON_BUTTON_EVENT_HUB_H

#include "base/memory/ace_type.h"
#include "base/utils/noncopyable.h"
#include "core/components_ng/event/event_hub.h"

namespace OHOS::Ace::NG {

class ButtonEventHub : public EventHub {
    DECLARE_ACE_TYPE(ButtonEventHub, EventHub);

public:
    ButtonEventHub() = default;
    ~ButtonEventHub() override = default;

    void SetStateEffect(bool stateEffect)
    {
        stateEffect_ = stateEffect;
    }

    bool GetStateEffect() const
    {
        return stateEffect_.value_or(true);
    }

private:
    std::optional<bool> stateEffect_;

    ACE_DISALLOW_COPY_AND_MOVE(ButtonEventHub);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BUTTON_BUTTON_EVENT_HUB_H