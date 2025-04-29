/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/node_container/node_container_event_hub.h"

#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

void NodeContainerEventHub::FireOnAppear()
{
    if (onAppearCallback_) {
        auto host = GetFrameNode();
        CHECK_NULL_VOID(host);
        auto pipeline = host->GetContext();
        CHECK_NULL_VOID(pipeline);
        auto taskScheduler = pipeline->GetTaskExecutor();
        CHECK_NULL_VOID(taskScheduler);
        taskScheduler->PostTask(
            [weak = WeakClaim(this)]() {
                auto eventHub = weak.Upgrade();
                CHECK_NULL_VOID(eventHub);
                if (eventHub->onAppearCallback_) {
                    // callback may be overwritten in its invoke so we copy it first
                    auto onAppear = eventHub->onAppearCallback_;
                    onAppear();
                }
            },
            TaskExecutor::TaskType::UI, "ArkUINodeControllerAboutToAppearEvent");
    }
    EventHub::FireOnAppear();
}

void NodeContainerEventHub::FireOnDisappear()
{
    if (onDisAppearCallback_) {
        // callback may be overwritten in its invoke so we copy it first
        auto onDisappear = onDisAppearCallback_;
        onDisappear();
    }
    EventHub::FireOnDisappear();
}

void NodeContainerEventHub::FireOnWillBind(int32_t containerId)
{
    if (onWillBindCallback_) {
        auto onWillBind = onWillBindCallback_;
        onWillBind(containerId);
    }
    EventHub::FireOnWillBind(containerId);
}

void NodeContainerEventHub::FireOnWillUnbind(int32_t containerId)
{
    if (onWillUnbindCallback_) {
        auto onWillUnbind = onWillUnbindCallback_;
        onWillUnbind(containerId);
    }
    EventHub::FireOnWillUnbind(containerId);
}

void NodeContainerEventHub::FireOnBind(int32_t containerId)
{
    if (onBindCallback_) {
        auto onBind = onBindCallback_;
        onBind(containerId);
    }
    EventHub::FireOnBind(containerId);
}

void NodeContainerEventHub::FireOnUnbind(int32_t containerId)
{
    if (onUnbindCallback_) {
        auto onUnbind = onUnbindCallback_;
        onUnbind(containerId);
    }
    EventHub::FireOnUnbind(containerId);
}

void NodeContainerEventHub::FireOnAttach()
{
    if (onAttachCallback_) {
        auto onAttach = onAttachCallback_;
        onAttach();
    }
    EventHub::FireOnAttach();
}

void NodeContainerEventHub::FireOnDetach()
{
    if (onDetachCallback_) {
        auto onDetach = onDetachCallback_;
        onDetach();
    }
    EventHub::FireOnDetach();
}
} // namespace OHOS::Ace::NG
