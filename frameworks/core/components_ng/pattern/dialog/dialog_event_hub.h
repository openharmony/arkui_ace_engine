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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DIALOG_DIALOG_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DIALOG_DIALOG_EVENT_HUB_H

#include "base/memory/ace_type.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/gesture_event_hub.h"

namespace OHOS::Ace::NG {

using DialogOnCancelEvent = std::function<void()>;

class DialogEventHub : public EventHub {
    DECLARE_ACE_TYPE(DialogEventHub, EventHub)

public:
    DialogEventHub() = default;
    ~DialogEventHub() override = default;

    void SetOnCancel(const DialogOnCancelEvent& event)
    {
        onCancel_ = event;
    }

    void FireCancelEvent() const;

    void SetOnSuccess(const std::function<void(int32_t, int32_t)>& event)
    {
        onSuccess_ = event;
    }

    void FireSuccessEvent(int32_t buttonIdx);

private:
    DialogOnCancelEvent onCancel_;
    // used in Prompt to return promise
    std::function<void(int32_t, int32_t)> onSuccess_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DIALOG_DIALOG_EVENT_HUB_H