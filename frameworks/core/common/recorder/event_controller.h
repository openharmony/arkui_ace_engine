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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_RECORDER_EVENT_CONTROLLER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_RECORDER_EVENT_CONTROLLER_H

#include <shared_mutex>
#include <string>
#include <unordered_map>
#include <vector>

#include "interfaces/inner_api/ace/ui_event_observer.h"
#include "base/utils/noncopyable.h"
#include "core/common/recorder/event_config.h"
#include "core/common/recorder/event_definition.h"

namespace OHOS::Ace::Recorder {
struct UIEventClient {
    std::shared_ptr<UIEventObserver> observer;
    EventConfig config;
};

class EventController final {
public:
    static EventController& Get();

    void Register(const std::string& config, const std::shared_ptr<UIEventObserver>& observer);
    void Unregister(const std::shared_ptr<UIEventObserver>& observer);

    void NotifyEvent(EventCategory category, int32_t eventType,
        const std::shared_ptr<std::unordered_map<std::string, std::string>>& eventParams);

    void NotifyEventSync(EventCategory category, int32_t eventType,
        const std::shared_ptr<std::unordered_map<std::string, std::string>>& eventParams);

    std::vector<std::string> GetWebJsCodeList();

    bool HasCached() const
    {
        return hasCached_;
    }

    bool HasWebProcessed() const
    {
        return hasWebProcessed_;
    }

    std::string GetCacheJsCode() const
    {
        return cacheJsCode_;
    }

private:
    struct CacheEvent {
        EventCategory category;
        int32_t eventType;
        std::shared_ptr<std::unordered_map<std::string, std::string>> eventParams;
    };
    EventController() = default;
    ~EventController() = default;
    void NotifyConfigChange();
    void ApplyNewestConfig(bool isExposureChanged, bool isWebChanged) const;
    void ApplyExposureCfgInner(const std::shared_ptr<Config>& config, bool isExposureChanged, bool isWebChanged) const;
    void CacheEventIfNeed(EventCategory category, int32_t eventType,
        const std::shared_ptr<std::unordered_map<std::string, std::string>>& eventParams);
    void NotifyCacheEventsIfNeed() const;

    std::shared_mutex mutable cacheLock_;
    std::vector<UIEventClient> clientList_;
    std::vector<CacheEvent> cacheEvents_;
    bool hasCached_ = false;
    bool hasWebProcessed_ = false;
    std::string cacheJsCode_;

    ACE_DISALLOW_COPY_AND_MOVE(EventController);
};
} // namespace OHOS::Ace::Recorder
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_RECORDER_EVENT_CONTROLLER_H
