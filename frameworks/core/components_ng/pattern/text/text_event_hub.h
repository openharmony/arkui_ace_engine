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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_TEXT_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_TEXT_EVENT_HUB_H

#include <cstdint>
#include <utility>

#include "base/memory/ace_type.h"
#include "base/utils/noncopyable.h"
#include "core/components_ng/event/event_hub.h"

namespace OHOS::Ace::NG {
class TextEventHub : public EventHub {
    DECLARE_ACE_TYPE(TextEventHub, EventHub)

public:
    TextEventHub() = default;
    ~TextEventHub() override = default;

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

    void SetOnSelectionChange(std::function<void(int32_t, int32_t)>&& func)
    {
        onSelectionChange_ = std::move(func);
    }

    void FireOnSelectionChange(int32_t selectionStart, int32_t selectionEnd)
    {
        if (onSelectionChange_) {
            onSelectionChange_(selectionStart, selectionEnd);
        }
    }

    void SetOnMarqueeStateChange(std::function<void(int32_t)>&& func)
    {
        onMarqueeStateChange_ = std::move(func);
    }

    void FireOnMarqueeStateChange(int32_t marqueeState)
    {
        if (onMarqueeStateChange_) {
            onMarqueeStateChange_(marqueeState);
        }
    }

private:
    std::function<void(const std::u16string&)> onCopy_;
    std::function<void(int32_t, int32_t)> onSelectionChange_;
    std::function<void(int32_t)> onMarqueeStateChange_;
    ACE_DISALLOW_COPY_AND_MOVE(TextEventHub);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_TEXT_EVENT_HUB_H