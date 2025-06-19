/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "adapter/ohos/entrance/event_pass_through_subscriber.h"

namespace OHOS::Ace {
namespace {
constexpr int32_t PUBLISHER_UID = 7800;
const std::string TOUCH_EVENTS_PASS_THROUGH = "touch.events.pass.through";
const std::string GAME_INFO_TO_GAME_RESAMPLE = "touch.events.game.resample";
const std::string TOUCH_EVENTS_UEGAME_START = "touch.events.uegame.start";
} // namespace

void EventPassThroughSubscribeProxy::SubscribeEvent(int32_t instanceId)
{
    TAG_LOGI(AceLogTag::ACE_INPUTKEYFLOW, "Subscribe touch.events.pass.through event");
    std::lock_guard<std::mutex> lock(mutex_);
    if (eventPassThroughReceiver_ == nullptr) {
        // create subscribe info
        MatchingSkills matchingSkills;
        // add common events
        matchingSkills.AddEvent(TOUCH_EVENTS_PASS_THROUGH);
        matchingSkills.AddEvent(GAME_INFO_TO_GAME_RESAMPLE);
        matchingSkills.AddEvent(TOUCH_EVENTS_UEGAME_START);
        CommonEventSubscribeInfo subscribeInfo(matchingSkills);
        subscribeInfo.SetPublisherUid(PUBLISHER_UID);
        subscribeInfo.SetThreadMode(EventFwk::CommonEventSubscribeInfo::ThreadMode::HANDLER);

        // init Receiver
        eventPassThroughReceiver_ = std::make_shared<EventPassThroughSubscriber>(subscribeInfo);
        eventPassThroughReceiver_->AddInstanceId(instanceId);
        eventReceiver_ = std::shared_ptr<CommonEventSubscriber>(eventPassThroughReceiver_);

        // create subscription
        CommonEventManager::SubscribeCommonEvent(eventReceiver_);
    } else {
        eventPassThroughReceiver_->AddInstanceId(instanceId);
    }
}

void EventPassThroughSubscribeProxy::UnSubscribeEvent()
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (eventReceiver_ != nullptr) {
        CommonEventManager::UnSubscribeCommonEvent(eventReceiver_);
        eventReceiver_ = nullptr;
        eventPassThroughReceiver_ = nullptr;
    }
}

void EventPassThroughSubscribeProxy::UnSubscribeEvent(int32_t instanceId)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (eventReceiver_ != nullptr) {
        if (eventPassThroughReceiver_->EraseContainerAddCheckUnSubscribe(instanceId)) {
            CommonEventManager::UnSubscribeCommonEvent(eventReceiver_);
            eventReceiver_ = nullptr;
            eventPassThroughReceiver_ = nullptr;
        }
    }
}

void EventPassThroughSubscriber::OnReceiveEvent(const CommonEventData& data)
{
    auto want = data.GetWant();
    std::string action = want.GetAction();
    std::string bundleName = want.GetBundle();
    if (bundleName.empty()) {
        TAG_LOGI(AceLogTag::ACE_INPUTKEYFLOW, "OnReceiveEvent empty bundleName");
        return;
    }
    bool needPassThrough = false;
    {
        std::lock_guard<std::mutex> lock(instanceMapMutex_);
        for (const auto& instanceId : instanceMap_) {
            auto container = Platform::AceContainer::GetContainer(instanceId);
            if (!container) {
                continue;
            }
            if (container->GetBundleName() == bundleName) {
                needPassThrough = true;
                break;
            }
        }
    }
    if (!needPassThrough) {
        TAG_LOGI(AceLogTag::ACE_INPUTKEYFLOW, "OnReceiveEvent no matched bundleName");
        return;
    }

    if (action == TOUCH_EVENTS_UEGAME_START) {
        TAG_LOGI(AceLogTag::ACE_INPUTKEYFLOW, "OnReceiveEvent %{public}s", action.c_str());
        AceApplicationInfo::GetInstance().SetTouchPadIdChanged(true);
        return;
    }
    if (action != TOUCH_EVENTS_PASS_THROUGH && action != GAME_INFO_TO_GAME_RESAMPLE) {
        return;
    }
    TAG_LOGI(AceLogTag::ACE_INPUTKEYFLOW, "OnReceiveEvent %{public}s", action.c_str());
    TouchPassMode mode =
        (action == TOUCH_EVENTS_PASS_THROUGH) ? TouchPassMode::PASS_THROUGH : TouchPassMode::ACCELERATE;
    AceApplicationInfo::GetInstance().SetTouchEventPassMode(mode);
    {
        std::lock_guard<std::mutex> lock(instanceMapMutex_);
        for (const auto& instanceId : instanceMap_) {
            auto container = Platform::AceContainer::GetContainer(instanceId);
            if (!container) {
                continue;
            }
            auto taskExecutor = container->GetTaskExecutor();
            CHECK_NULL_VOID(taskExecutor);
            taskExecutor->PostTask(
                [mode, instanceId]() {
                    auto container = Platform::AceContainer::GetContainer(instanceId);
                    CHECK_NULL_VOID(container);
                    auto pipeline = container->GetPipelineContext();
                    CHECK_NULL_VOID(pipeline);
                    if (mode == TouchPassMode::PASS_THROUGH) {
                        pipeline->SetTouchPassThrough(true);
                        pipeline->SetTouchAccelarate(false);
                    } else {
                        pipeline->SetTouchAccelarate(true);
                        pipeline->SetTouchPassThrough(false);
                    }
                },
                TaskExecutor::TaskType::UI, "ArkUIReceiveEventsPassThroughAsync");
        }
    }
}

void EventPassThroughSubscriber::AddInstanceId(int32_t instanceId)
{
    std::lock_guard<std::mutex> lock(instanceMapMutex_);
    instanceMap_.emplace(instanceId);
}

bool EventPassThroughSubscriber::EraseContainerAddCheckUnSubscribe(int32_t instanceId)
{
    std::lock_guard<std::mutex> lock(instanceMapMutex_);
    instanceMap_.erase(instanceId);
    return instanceMap_.empty();
}
} // namespace OHOS::Ace
