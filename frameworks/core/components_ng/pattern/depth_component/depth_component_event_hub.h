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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DEPTH_COMPONENT_DEPTH_COMPONENT_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DEPTH_COMPONENT_DEPTH_COMPONENT_EVENT_HUB_H

#include <functional>
#include <memory>

#include "base/memory/ace_type.h"
#include "core/components/common/properties/depth_option.h"
#include "core/components_ng/event/event_hub.h"

namespace OHOS::Ace::NG {

using DepthComponentCompleteEventFunc = std::function<void(const DepthComponentCompleteEvent&)>;
using DepthComponentErrorEventFunc = std::function<void(const DepthComponentErrorEvent&)>;
using DepthMapErrorEventFunc = std::function<void(int32_t, const std::string&)>;

class DepthComponentEventHub : public EventHub {
    DECLARE_ACE_TYPE(DepthComponentEventHub, EventHub);

public:
    DepthComponentEventHub() = default;
    ~DepthComponentEventHub() override = default;
    ACE_DISALLOW_COPY_AND_MOVE(DepthComponentEventHub);

    void SetOnComplete(DepthComponentCompleteEventFunc&& onComplete)
    {
        onComplete_ = std::move(onComplete);
    }

    const DepthComponentCompleteEventFunc& GetOnComplete() const
    {
        return onComplete_;
    }

    void FireCompleteEvent(const DepthComponentCompleteEvent& event) const
    {
        if (onComplete_) {
            onComplete_(event);
        }
    }

    void SetOnError(DepthComponentErrorEventFunc&& onError)
    {
        onError_ = std::move(onError);
    }

    const DepthComponentErrorEventFunc& GetOnError() const
    {
        return onError_;
    }

    void FireErrorEvent(const DepthComponentErrorEvent& event) const
    {
        if (onError_) {
            onError_(event);
        }
    }

    void SetOnDepthMapError(DepthMapErrorEventFunc&& onDepthMapError)
    {
        onDepthMapError_ = std::move(onDepthMapError);
    }

    const DepthMapErrorEventFunc& GetOnDepthMapError() const
    {
        return onDepthMapError_;
    }

    void FireDepthMapErrorEvent(int32_t errorCode, const std::string& errorMessage) const
    {
        if (onDepthMapError_) {
            onDepthMapError_(errorCode, errorMessage);
        }
    }

private:
    DepthComponentCompleteEventFunc onComplete_;
    DepthComponentErrorEventFunc onError_;
    DepthMapErrorEventFunc onDepthMapError_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DEPTH_COMPONENT_DEPTH_COMPONENT_EVENT_HUB_H
