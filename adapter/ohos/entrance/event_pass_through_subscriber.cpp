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
const std::string TOUCH_EVENTS_PASS_THROUGH = "touch.events.pass.through";
namespace {
constexpr int32_t PUBLISHER_UID = 7800;
} // namespace

void EventPassThroughSubscribeProxy::SubscribeEvent(int32_t instanceId)
{
    TAG_LOGI(AceLogTag::ACE_INPUTKEYFLOW, "Subscribe touch.events.pass.through event");
    if (eventPassThroughReceiver_ == nullptr) {
        // create subscribe info
        MatchingSkills matchingSkills;
        // add common events
        matchingSkills.AddEvent(TOUCH_EVENTS_PASS_THROUGH);
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
    if (eventReceiver_ != nullptr) {
        CommonEventManager::UnSubscribeCommonEvent(eventReceiver_);
        eventReceiver_ = nullptr;
        eventPassThroughReceiver_ = nullptr;
    }
}

void EventPassThroughSubscribeProxy::UnSubscribeEvent(int32_t instanceId)
{
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
    if (action == TOUCH_EVENTS_PASS_THROUGH) {
        TAG_LOGI(AceLogTag::ACE_INPUTKEYFLOW, "OnReceiveEvent touch.events.pass.through event");
        AceApplicationInfo::GetInstance().SetTouchEventsPassThroughMode(true);
        for (const auto& instanceId : instanceMap_) {
            auto container = Platform::AceContainer::GetContainer(instanceId);
            if (!container) {
                continue;
            }
            auto taskExecutor = container->GetTaskExecutor();
            CHECK_NULL_VOID(taskExecutor);
            taskExecutor->PostTask(
                [instanceId]() {
                    auto container = Platform::AceContainer::GetContainer(instanceId);
                    CHECK_NULL_VOID(container);
                    container->SetTouchEventsPassThroughMode(true);
                },
                TaskExecutor::TaskType::UI, "ArkUIReceiveEventsPassThroughAsync");
        }
    }
}

void EventPassThroughSubscriber::AddInstanceId(int32_t instanceId)
{
    instanceMap_.emplace(instanceId);
}

bool EventPassThroughSubscriber::EraseContainerAddCheckUnSubscribe(int32_t instanceId)
{
    instanceMap_.erase(instanceId);
    return instanceMap_.empty();
}
} // namespace OHOS::Ace
