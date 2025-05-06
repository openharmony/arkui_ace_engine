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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FORM_FORM_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FORM_FORM_EVENT_HUB_H

#include <functional>

#include "base/memory/ace_type.h"
#include "core/components_ng/event/event_hub.h"

namespace OHOS::Ace::NG {

using FormCallback = std::function<void(const std::string&)>;
using FormCacheCallback = std::function<void()>;

class FormEventHub : public EventHub {
    DECLARE_ACE_TYPE(FormEventHub, EventHub)

public:
    FormEventHub() = default;
    ~FormEventHub() override = default;

    void SetOnAcquired(FormCallback&& onAcquired)
    {
        onAcquired_ = std::move(onAcquired);
    }

    void SetOnError(FormCallback&& onError)
    {
        onError_ = std::move(onError);
    }

    void SetOnUninstall(FormCallback&& onUninstall)
    {
        onUninstall_ = std::move(onUninstall);
    }

    void SetOnRouter(FormCallback&& onRouter)
    {
        onRouter_ = std::move(onRouter);
    }

    void SetOnLoad(FormCallback&& onLoad)
    {
        onLoad_ = std::move(onLoad);
    }

    void SetOnUpdate(FormCallback&& onUpdate)
    {
        onUpdate_ = std::move(onUpdate);
    }

    void SetOnCache(FormCacheCallback&& onCache)
    {
        onCache_ = std::move(onCache);
    }

    void FireOnAcquired(const std::string& param) const
    {
        if (onAcquired_) {
            auto onAcquired = onAcquired_;
            onAcquired(param);
        }
    }

    void FireOnError(const std::string& param) const
    {
        if (onError_) {
            auto onError = onError_;
            onError(param);
        }
    }

    void FireOnUninstall(const std::string& param) const
    {
        if (onUninstall_) {
            auto onUninstall = onUninstall_;
            onUninstall(param);
        }
    }

    void FireOnRouter(const std::string& param) const
    {
        if (onRouter_) {
            auto onRouter = onRouter_;
            onRouter(param);
        }
    }

    void FireOnLoad(const std::string& param) const
    {
        if (onLoad_) {
            auto onLoad = onLoad_;
            onLoad(param);
        }
    }

    void FireOnUpdate(const std::string& param) const
    {
        if (onUpdate_) {
            auto onUpdate = onUpdate_;
            onUpdate(param);
        }
    }

    void FireOnCache() const
    {
        if (onCache_) {
            auto onCache = onCache_;
            onCache();
        }
    }

private:
    FormCallback onAcquired_;
    FormCallback onError_;
    FormCallback onUninstall_;
    FormCallback onRouter_;
    FormCallback onLoad_;
    FormCallback onUpdate_;
    FormCacheCallback onCache_;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FORM_FORM_EVENT_HUB_H