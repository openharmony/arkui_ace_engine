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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_IMAGE_ANIMATOR_IMAGE_ANIMATOR_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_IMAGE_ANIMATOR_IMAGE_ANIMATOR_EVENT_HUB_H

#include "base/memory/ace_type.h"
#include "core/components_ng/event/event_hub.h"

namespace OHOS::Ace::NG {

using AnimatorEvent = std::function<void()>;

class ImageAnimatorEventHub : public EventHub {
    DECLARE_ACE_TYPE(ImageAnimatorEventHub, EventHub);

public:
    ImageAnimatorEventHub() = default;
    ~ImageAnimatorEventHub() override = default;

    void SetStartEvent(const AnimatorEvent& startEvent)
    {
        startEvent_ = startEvent;
    }

    const AnimatorEvent& GetStartEvent() const
    {
        return startEvent_;
    }

    void SetStopEvent(const AnimatorEvent& stopEvent)
    {
        stopEvent_ = stopEvent;
    }

    const AnimatorEvent& GetStopEvent() const
    {
        return stopEvent_;
    }

    void SetPauseEvent(const AnimatorEvent& pauseEvent)
    {
        pauseEvent_ = pauseEvent;
    }

    const AnimatorEvent& GetPauseEvent() const
    {
        return pauseEvent_;
    }

    void SetRepeatEvent(const AnimatorEvent& repeatEvent)
    {
        repeatEvent_ = repeatEvent;
    }

    const AnimatorEvent& GetRepeatEvent() const
    {
        return repeatEvent_;
    }

    void SetCancelEvent(const AnimatorEvent& cancelEvent)
    {
        cancelEvent_ = cancelEvent;
    }

    const AnimatorEvent& GetCancelEvent() const
    {
        return cancelEvent_;
    }

private:
    AnimatorEvent startEvent_;
    AnimatorEvent stopEvent_;
    AnimatorEvent pauseEvent_;
    AnimatorEvent repeatEvent_;
    AnimatorEvent cancelEvent_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_IMAGE_ANIMATOR_IMAGE_ANIMATOR_EVENT_HUB_H
