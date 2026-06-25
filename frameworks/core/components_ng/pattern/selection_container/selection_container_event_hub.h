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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SELECTION_CONTAINER_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SELECTION_CONTAINER_EVENT_HUB_H

#include <functional>
#include <vector>

#include "base/utils/noncopyable.h"
#include "core/components_ng/event/event_hub.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT SelectionContainerEventHub : public EventHub {
    DECLARE_ACE_TYPE(SelectionContainerEventHub, EventHub);

public:
    SelectionContainerEventHub() = default;
    ~SelectionContainerEventHub() override = default;

    void SetOnWillCopy(std::function<bool(const std::u16string&)>&& func)
    {
        onWillCopy_ = std::move(func);
    }

    bool FireOnWillCopy(const std::u16string& value)
    {
        if (onWillCopy_) {
            return onWillCopy_(value);
        }
        return true;
    }

    void SetOnCopy(std::function<void(const std::u16string&)>&& func)
    {
        onCopy_ = std::move(func);
    }

    void FireOnCopy(const std::u16string& value)
    {
        if (onCopy_) {
            onCopy_(value);
        }
    }

    void SetOnTextSelectionChange(std::function<void(const std::vector<std::u16string>&)>&& func)
    {
        onTextSelectionChange_ = std::move(func);
    }

    void FireOnTextSelectionChange(const std::vector<std::u16string>& selectedTexts)
    {
        if (onTextSelectionChange_) {
            onTextSelectionChange_(selectedTexts);
        }
    }

private:
    std::function<bool(const std::u16string&)> onWillCopy_;
    std::function<void(const std::u16string&)> onCopy_;
    std::function<void(const std::vector<std::u16string>&)> onTextSelectionChange_;
    ACE_DISALLOW_COPY_AND_MOVE(SelectionContainerEventHub);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SELECTION_CONTAINER_EVENT_HUB_H
