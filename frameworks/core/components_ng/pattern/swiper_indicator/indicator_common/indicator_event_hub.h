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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_INDICATOR_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_INDICATOR_EVENT_HUB_H

namespace OHOS::Ace::NG {

using ChangeEvent = std::function<void(int32_t index)>;
using ChangeEventPtr = std::shared_ptr<ChangeEvent>;

class IndicatorEventHub : public EventHub {
    DECLARE_ACE_TYPE(IndicatorEventHub, EventHub);

public:
    IndicatorEventHub() = default;
    ~IndicatorEventHub() override = default;

    /* Using shared_ptr to enable event modification without adding again */
    void AddOnChangeEvent(const ChangeEventPtr& changeEvent)
    {
        changeEvents_.emplace_back(changeEvent);
    }

    void FireChangeEvent(int32_t index) const
    {
        if (!changeEvents_.empty()) {
            std::for_each(changeEvents_.begin(), changeEvents_.end(), [index](const ChangeEventPtr& changeEvent) {
                auto event = *changeEvent;
                event(index);
            });
        }
    }

private:
    std::list<ChangeEventPtr> changeEvents_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_INDICATOR_EVENT_HUB_H