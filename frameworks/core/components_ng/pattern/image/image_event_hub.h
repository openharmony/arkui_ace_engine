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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_IMAGE_IMAGE_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_IMAGE_IMAGE_EVENT_HUB_H

#include "base/memory/ace_type.h"
#include "core/components/image/image_event.h"
#include "core/components_ng/event/event_hub.h"

namespace OHOS::Ace::NG {

using CompleteEvent = std::function<void(const LoadImageSuccessEvent& info)>;
using ErrorEvent = std::function<void(const LoadImageFailEvent& info)>;
using FinishEvent = std::function<void()>;

class ImageEventHub : public EventHub {
    DECLARE_ACE_TYPE(ImageEventHub, EventHub);

public:
    ImageEventHub() = default;
    ~ImageEventHub() override = default;

    void SetOnError(ErrorEvent&& errorEvent)
    {
        errorEvent_ = std::move(errorEvent);
    }

    void FireErrorEvent(const LoadImageFailEvent& info) const
    {
        if (errorEvent_) {
            errorEvent_(info);
        }
    }

    void SetOnComplete(CompleteEvent&& completeEvent)
    {
        completeEvent_ = std::move(completeEvent);
    }

    void FireCompleteEvent(const LoadImageSuccessEvent& info) const
    {
        if (completeEvent_) {
            completeEvent_(info);
        }
    }
    
    void SetOnFinish(FinishEvent&& finishEvent)
    {
        finishEvent_ = std::move(finishEvent);
    }

    void FireFinishEvent() const
    {
        if (finishEvent_) {
            finishEvent_();
        }
    }

private:
    ErrorEvent errorEvent_;
    CompleteEvent completeEvent_;
    FinishEvent finishEvent_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_IMAGE_IMAGE_EVENT_HUB_H
