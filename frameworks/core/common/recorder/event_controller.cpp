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
#include "core/common/recorder/event_controller.h"

#include <algorithm>

#include "base/json/json_util.h"
#include "base/log/log_wrapper.h"
#include "base/thread/background_task_executor.h"
#include "core/common/recorder/node_data_cache.h"
#include "core/common/recorder/event_recorder.h"

namespace OHOS::Ace::Recorder {
EventController& EventController::Get()
{
    static EventController eventController;
    return eventController;
}

void EventController::Register(const std::string& config, const std::shared_ptr<UIEventObserver>& observer)
{
    UIEventClient client;
    client.config.Init(config);
    if (!client.config.IsEnable()) {
        return;
    }
    client.observer = observer;
    std::unique_lock<std::mutex> lock(cacheLock_);
    clientList_.emplace_back(std::move(client));
    NotifyConfigChange();
}

void EventController::NotifyConfigChange()
{
    auto mergedConfig = std::make_shared<MergedConfig>();
    EventSwitch eventSwitch;
    for (auto&& client : clientList_) {
        if (!client.config.IsEnable()) {
            continue;
        }
        eventSwitch.pageEnable = eventSwitch.pageEnable || client.config.IsCategoryEnable(EventCategory::CATEGORY_PAGE);
        eventSwitch.exposureEnable =
            eventSwitch.exposureEnable || client.config.IsCategoryEnable(EventCategory::CATEGORY_EXPOSURE);
        eventSwitch.componentEnable =
            eventSwitch.componentEnable || client.config.IsCategoryEnable(EventCategory::CATEGORY_COMPONENT);
        for (auto iter = client.config.GetConfig()->begin(); iter != client.config.GetConfig()->end(); iter++) {
            auto nodeIt = mergedConfig->shareNodes.find(iter->first);
            if (nodeIt != mergedConfig->shareNodes.end()) {
                std::for_each(iter->second.shareNodes.begin(), iter->second.shareNodes.end(),
                    [&nodeIt](const std::list<std::string>::value_type& id) { nodeIt->second.emplace(id); });
            } else {
                std::unordered_set<std::string> nodeSet;
                std::for_each(iter->second.shareNodes.begin(), iter->second.shareNodes.end(),
                    [&nodeSet](const std::list<std::string>::value_type& id) { nodeSet.emplace(id); });
                mergedConfig->shareNodes.emplace(iter->first, std::move(nodeSet));
            }

            auto exposureIt = mergedConfig->exposureNodes.find(iter->first);
            if (exposureIt != mergedConfig->exposureNodes.end()) {
                std::for_each(iter->second.exposureCfgs.begin(), iter->second.exposureCfgs.end(),
                    [&exposureIt](
                        const std::list<ExposureCfg>::value_type& cfg) { exposureIt->second.emplace(cfg); });
            } else {
                std::unordered_set<ExposureCfg, ExposureCfgHash> exposureSet;
                std::for_each(iter->second.exposureCfgs.begin(), iter->second.exposureCfgs.end(),
                    [&exposureSet](const std::list<ExposureCfg>::value_type& cfg) { exposureSet.emplace(cfg); });
                mergedConfig->exposureNodes.emplace(iter->first, std::move(exposureSet));
            }
        }
    }
    NodeDataCache::Get().UpdateConfig(std::move(mergedConfig));
    EventRecorder::Get().UpdateEventSwitch(eventSwitch);
}

void EventController::Unregister(const std::shared_ptr<UIEventObserver>& observer)
{
    std::unique_lock<std::mutex> lock(cacheLock_);
    auto iter = std::remove_if(clientList_.begin(), clientList_.end(),
        [&observer](UIEventClient client) { return client.observer == observer; });
    bool change = iter != clientList_.end();
    clientList_.erase(iter, clientList_.end());
    if (change) {
        NotifyConfigChange();
    }
}

void EventController::NotifyEvent(EventCategory category, int32_t eventType,
    const std::shared_ptr<std::unordered_map<std::string, std::string>>& eventParams)
{
    {
        std::unique_lock<std::mutex> lock(cacheLock_);
        if (clientList_.empty()) {
            return;
        }
    }
    BackgroundTaskExecutor::GetInstance().PostTask([category, eventType, eventParams]() {
        EventController::Get().NotifyEventSync(category, eventType, eventParams);
    });
}

void EventController::NotifyEventSync(EventCategory category, int32_t eventType,
    const std::shared_ptr<std::unordered_map<std::string, std::string>>& eventParams)
{
    std::unique_lock<std::mutex> lock(cacheLock_);
    for (auto&& client : clientList_) {
        if (client.config.IsEnable() && client.config.IsCategoryEnable(category)) {
            client.observer->NotifyUIEvent(eventType, *eventParams);
        }
    }
}
} // namespace OHOS::Ace::Recorder
