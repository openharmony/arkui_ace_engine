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
#include <cstdint>
#include <vector>

#include "base/thread/background_task_executor.h"
#include "core/common/recorder/event_definition.h"
#include "core/common/recorder/event_recorder.h"
#include "core/common/recorder/node_data_cache.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::Recorder {
constexpr uint32_t EXPOSURE_REGISTER_DELAY = 500;
constexpr int32_t MAX_CACHE_SIZE = 5;

struct ExposureWrapper {
    WeakPtr<NG::FrameNode> node;
    RefPtr<ExposureProcessor> processor;

    ExposureWrapper(const WeakPtr<NG::FrameNode>& node, RefPtr<ExposureProcessor>&& processor)
        : node(node), processor(processor)
    {}
};

EventController& EventController::Get()
{
    static EventController eventController;
    return eventController;
}

void EventController::Register(const std::string& config, const std::shared_ptr<UIEventObserver>& observer)
{
    TAG_LOGI(AceLogTag::ACE_UIEVENT, "Register config");
    CHECK_NULL_VOID(observer);
    UIEventClient client;
    client.config.Init(config);
    if (!client.config.IsEnable()) {
        return;
    }
    client.observer = observer;
    std::unique_lock<std::shared_mutex> lock(cacheLock_);
    clientList_.emplace_back(client);
    lock.unlock();
    bool isOriginExposureEnable = EventRecorder::Get().IsExposureRecordEnable();
    NotifyConfigChange();
    bool isExposureChanged = EventRecorder::Get().IsExposureRecordEnable() && !isOriginExposureEnable;
    if (isExposureChanged) {
        ApplyNewestConfig(isExposureChanged);
    }
    NotifyCacheEventsIfNeed(client);
    TAG_LOGI(AceLogTag::ACE_UIEVENT, "Register config end");
}

void EventController::NotifyConfigChange()
{
    std::shared_lock<std::shared_mutex> lock(cacheLock_);
    auto mergedConfig = std::make_shared<MergedConfig>();
    int32_t size = static_cast<int32_t>(EventCategory::CATEGORY_END);
    std::vector<bool> eventSwitch;
    eventSwitch.resize(size, false);
    eventSwitch[static_cast<int32_t>(EventCategory::CATEGORY_PAGE)] = true;
    std::unordered_map<std::string, std::string> webIdentifierMap;
    for (auto&& client : clientList_) {
        if (!client.config.IsEnable()) {
            continue;
        }
        for (int32_t i = 0; i < size; i++) {
            eventSwitch[i] = eventSwitch[i] || client.config.IsCategoryEnable(i);
        }
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
        if (!client.config.GetWebCategory().empty()) {
            webIdentifierMap[client.config.GetWebCategory()] = client.config.GetWebIdentifier();
        }
    }
    NodeDataCache::Get().UpdateConfig(std::move(mergedConfig));
    EventRecorder::Get().UpdateEventSwitch(eventSwitch);
    EventRecorder::Get().UpdateWebIdentifier(webIdentifierMap);
}

bool IsAllowNotify(const EventConfig& config, EventCategory category, int32_t eventType,
    const std::shared_ptr<std::unordered_map<std::string, std::string>>& eventParams)
{
    CHECK_NULL_RETURN(eventParams, false);
    auto enable = config.IsEnable() && config.IsCategoryEnable(static_cast<int32_t>(category));
    if (!enable) {
        return false;
    }
    if (eventType == EventType::WEB_ACTION) {
        return eventParams->count(KEY_WEB_CATEGORY) > 0 && eventParams->at(KEY_WEB_CATEGORY) == config.GetWebCategory();
    }
    return true;
}

void EventController::NotifyCacheEventsIfNeed(const UIEventClient& client) const
{
    std::shared_lock<std::shared_mutex> lock(cacheEventLock_);
    if (cacheEvents_.empty()) {
        return;
    }
    BackgroundTaskExecutor::GetInstance().PostTask([events = cacheEvents_, client]() {
        for (const auto& event : events) {
            if (IsAllowNotify(client.config, event.category, event.eventType, event.eventParams)) {
                client.observer->NotifyUIEvent(event.eventType, event.eventParams);
            }
        }
    });
}

void GetMatchedNodes(const std::string& pageUrl, const RefPtr<NG::UINode>& root,
    const std::unordered_set<ExposureCfg, ExposureCfgHash>& exposureSet, std::list<ExposureWrapper>& outputList)
{
    std::queue<RefPtr<NG::UINode>> elements;
    ExposureCfg targetCfg = { "", 0.0, 0 };
    elements.push(root);
    while (!elements.empty()) {
        auto current = elements.front();
        elements.pop();
        targetCfg.id = current->GetInspectorIdValue("");
        if (!targetCfg.id.empty() && AceType::InstanceOf<NG::FrameNode>(current)) {
            auto frameNode = AceType::DynamicCast<NG::FrameNode>(current);
            auto cfgIter = exposureSet.find(targetCfg);
            if (cfgIter != exposureSet.end()) {
                outputList.emplace_back(ExposureWrapper(Referenced::WeakClaim(Referenced::RawPtr(frameNode)),
                    Referenced::MakeRefPtr<ExposureProcessor>(
                        pageUrl, targetCfg.id, cfgIter->ratio, cfgIter->duration)));
            }
        }
        for (const auto& child : current->GetChildren()) {
            elements.push(child);
        }
    }
}

void EventController::ApplyNewestConfig(bool isExposureChanged) const
{
    TAG_LOGI(AceLogTag::ACE_UIEVENT, "ApplyNewestConfig isExposureChanged:%{public}d", isExposureChanged);
    std::shared_lock<std::shared_mutex> lock(cacheLock_);
    if (clientList_.empty()) {
        return;
    }
    auto containerId = EventRecorder::Get().GetContainerId();
    auto config = clientList_.back().config.GetConfig();

    auto context = NG::PipelineContext::GetContextByContainerId(containerId);
    CHECK_NULL_VOID(context);
    auto taskExecutor = context->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostDelayedTask(
        [config, isExposureChanged]() {
            EventController::Get().ApplyExposureCfgInner(config, isExposureChanged);
        },
        TaskExecutor::TaskType::UI, EXPOSURE_REGISTER_DELAY, "EventController");
}

void EventController::ApplyExposureCfgInner(const std::shared_ptr<Config>& config, bool isExposureChanged) const
{
    auto containerId = EventRecorder::Get().GetContainerId();
    auto pageUrl = GetPageUrlByContainerId(containerId);
    if (pageUrl.empty()) {
        return;
    }
    auto context = NG::PipelineContext::GetContextByContainerId(containerId);
    CHECK_NULL_VOID(context);
    auto rootNode = context->GetRootElement();
    CHECK_NULL_VOID(rootNode);
    std::unordered_set<ExposureCfg, ExposureCfgHash> exposureSet;
    std::list<ExposureWrapper> targets;

    if (isExposureChanged) {
        auto pageIter = config->find(pageUrl);
        if (pageIter != config->end() && pageIter->second.exposureCfgs.size() > 0) {
            std::for_each(pageIter->second.exposureCfgs.begin(), pageIter->second.exposureCfgs.end(),
                [&exposureSet](const std::list<ExposureCfg>::value_type& cfg) { exposureSet.emplace(cfg); });
        }
    }
    GetMatchedNodes(pageUrl, rootNode, exposureSet, targets);
    for (auto& item : targets) {
        item.processor->SetContainerId(containerId);
        auto node = item.node.Upgrade();
        CHECK_NULL_VOID(node);
        node->SetExposureProcessor(item.processor);
    }
}

void EventController::Unregister(const std::shared_ptr<UIEventObserver>& observer)
{
    std::unique_lock<std::shared_mutex> lock(cacheLock_);
    auto iter = std::remove_if(clientList_.begin(), clientList_.end(),
        [&observer](const UIEventClient& client) { return client.observer == observer; });
    bool change = iter != clientList_.end();
    clientList_.erase(iter, clientList_.end());
    lock.unlock();
    if (change) {
        NotifyConfigChange();
    }
}

void EventController::CacheEventIfNeed(EventCategory category, int32_t eventType,
    const std::shared_ptr<std::unordered_map<std::string, std::string>>& eventParams)
{
    std::unique_lock<std::shared_mutex> lock(cacheEventLock_);
    if (cacheEvents_.empty()) {
        if (hasCached_) {
            return;
        } else {
            cacheEvents_.emplace_back(CacheEvent { category, eventType, eventParams });
        }
    } else if (cacheEvents_.size() < MAX_CACHE_SIZE) {
        cacheEvents_.emplace_back(CacheEvent { category, eventType, eventParams });
    } else {
        hasCached_ = true;
        cacheEvents_.clear();
        EventRecorder::Get().NotifyEventCacheEnd();
    }
}

void EventController::NotifyEvent(EventCategory category, int32_t eventType,
    const std::shared_ptr<std::unordered_map<std::string, std::string>>& eventParams)
{
    CacheEventIfNeed(category, eventType, eventParams);
    {
        std::shared_lock<std::shared_mutex> lock(cacheLock_);
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
    std::shared_lock<std::shared_mutex> lock(cacheLock_);
    for (auto&& client : clientList_) {
        if (IsAllowNotify(client.config, category, eventType, eventParams)) {
            client.observer->NotifyUIEvent(eventType, eventParams);
        }
    }
}

std::vector<std::string> EventController::GetWebJsCodeList()
{
    std::vector<std::string> codeList;
    std::shared_lock<std::shared_mutex> lock(cacheLock_);
    for (auto&& client : clientList_) {
        if (client.config.IsCategoryEnable(static_cast<int32_t>(EventCategory::CATEGORY_WEB)) &&
            !client.config.GetWebJsCode().empty()) {
            codeList.emplace_back(client.config.GetWebJsCode());
        }
    }
    return codeList;
}
} // namespace OHOS::Ace::Recorder
