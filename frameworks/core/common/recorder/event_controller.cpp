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

#include "base/thread/background_task_executor.h"
#include "core/common/recorder/node_data_cache.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::Recorder {
constexpr int32_t PAGE_URL_SUFFIX_LENGTH = 3;
constexpr uint32_t EXPOSURE_REGISTER_DELAY = 500;

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
    UIEventClient client;
    client.config.Init(config);
    if (!client.config.IsEnable()) {
        return;
    }
    client.observer = observer;
    std::unique_lock<std::shared_mutex> lock(cacheLock_);
    clientList_.emplace_back(std::move(client));
    lock.unlock();
    bool isOriginEnable = EventRecorder::Get().IsExposureRecordEnable();
    NotifyConfigChange();
    bool isCurrentEnable = EventRecorder::Get().IsExposureRecordEnable();
    if (!isOriginEnable && isCurrentEnable) {
        ApplyNewestConfig();
    }
    TAG_LOGI(AceLogTag::ACE_UIEVENT, "Register config end");
}

void EventController::NotifyConfigChange()
{
    std::shared_lock<std::shared_mutex> lock(cacheLock_);
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
        eventSwitch.pageParamEnable =
            eventSwitch.pageParamEnable || client.config.IsCategoryEnable(EventCategory::CATEGORY_PAGE_PARAM);
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

std::string GetPageUrlByContainerId(const int32_t containerId)
{
    auto container = Container::GetContainer(containerId);
    CHECK_NULL_RETURN(container, "");
    if (!container->IsUseNewPipeline()) {
        return "";
    }
    auto frontEnd = container->GetFrontend();
    CHECK_NULL_RETURN(frontEnd, "");
    auto pageUrl = frontEnd->GetCurrentPageUrl();
    if (StringUtils::EndWith(pageUrl, ".js")) {
        pageUrl = pageUrl.substr(0, pageUrl.length() - PAGE_URL_SUFFIX_LENGTH);
    }
    return pageUrl;
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

void EventController::ApplyNewestConfig()
{
    std::shared_lock<std::shared_mutex> lock(cacheLock_);
    if (clientList_.empty()) {
        return;
    }
    auto containerId = EventRecorder::Get().GetContainerId();
    auto pageUrl = GetPageUrlByContainerId(containerId);
    if (pageUrl.empty()) {
        return;
    }
    auto config = clientList_.back().config.GetConfig();
    lock.unlock();
    auto pageIter = config->find(pageUrl);
    if (pageIter == config->end()) {
        return;
    }
    if (pageIter->second.exposureCfgs.empty()) {
        return;
    }
    auto context = NG::PipelineContext::GetContextByContainerId(containerId);
    CHECK_NULL_VOID(context);
    auto rootNode = context->GetRootElement();
    CHECK_NULL_VOID(rootNode);
    std::unordered_set<ExposureCfg, ExposureCfgHash> exposureSet;
    std::for_each(pageIter->second.exposureCfgs.begin(), pageIter->second.exposureCfgs.end(),
        [&exposureSet](const std::list<ExposureCfg>::value_type& cfg) { exposureSet.emplace(cfg); });
    std::list<ExposureWrapper> targets;
    GetMatchedNodes(pageUrl, rootNode, exposureSet, targets);
    auto taskExecutor = context->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostDelayedTask(
        [containerId, wrapperList = std::move(targets)]() {
            for (auto& item : wrapperList) {
                item.processor->SetContainerId(containerId);
                auto node = item.node.Upgrade();
                CHECK_NULL_VOID(node);
                node->SetExposureProcessor(item.processor);
            }
        },
        TaskExecutor::TaskType::UI, EXPOSURE_REGISTER_DELAY, "EventController");
}

void EventController::Unregister(const std::shared_ptr<UIEventObserver>& observer)
{
    std::unique_lock<std::shared_mutex> lock(cacheLock_);
    auto iter = std::remove_if(clientList_.begin(), clientList_.end(),
        [&observer](UIEventClient client) { return client.observer == observer; });
    bool change = iter != clientList_.end();
    clientList_.erase(iter, clientList_.end());
    lock.unlock();
    if (change) {
        NotifyConfigChange();
    }
}

void EventController::NotifyEvent(EventCategory category, int32_t eventType,
    const std::shared_ptr<std::unordered_map<std::string, std::string>>& eventParams)
{
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
        if (client.config.IsEnable() && client.config.IsCategoryEnable(category)) {
            client.observer->NotifyUIEvent(eventType, *eventParams);
        }
    }
}
} // namespace OHOS::Ace::Recorder
