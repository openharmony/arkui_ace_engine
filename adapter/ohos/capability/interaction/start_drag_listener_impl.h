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

#ifndef FOUNDATION_ACE_ACE_ENGINE_ADAPTER_OHOS_CAPABILITY_INTERACTION_START_DRAG_LISTENER_IMPL_H
#define FOUNDATION_ACE_ACE_ENGINE_ADAPTER_OHOS_CAPABILITY_INTERACTION_START_DRAG_LISTENER_IMPL_H

#include <functional>
#include <memory>
#include <mutex>

#include "i_start_drag_listener.h"

#include "core/common/ace_engine.h"
#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "base/thread/task_executor.h"

using DragEndingCallback = std::function<void(const OHOS::Msdp::DeviceStatus::DragNotifyMsg&)>;

namespace OHOS::Ace {
class StartDragListenerImpl : public OHOS::Msdp::DeviceStatus::IStartDragListener {
public:
    StartDragListenerImpl() = default;
    explicit StartDragListenerImpl(DragEndingCallback callback, int32_t instanceId = -1)
        : callback_(std::move(callback)),
          instanceId_(instanceId >= 0 ? instanceId : ContainerScope::CurrentId())
    {
        auto container = AceEngine::Get().GetContainer(instanceId_);
        taskExecutor_ = container != nullptr ? container->GetTaskExecutor() : nullptr;
    }

    ~StartDragListenerImpl() override
    {
        if (callback_ == nullptr) {
            return;
        }
        // Already on the JS thread — callback_ destroyed here directly.
        if (taskExecutor_ && taskExecutor_->WillRunOnCurrentThread(TaskExecutor::TaskType::JS)) {
            return;
        }
        if (!taskExecutor_) {
            return;
        }
        // Not on JS thread — post callback destruction to the JS thread with mutex to ensure
        // the posted task waits for this destructor to complete before destroying the callback.
        auto mutex = std::make_shared<std::mutex>();
        std::lock_guard lock(*mutex);
        taskExecutor_->PostTask(
            [callback = callback_, mutex]() mutable {
                std::lock_guard lock(*mutex);
                // callback destroyed here on the JS thread.
            },
            TaskExecutor::TaskType::JS, "ArkUIDragCallbackRelease", PriorityType::VIP);
        callback_ = nullptr;
    }

    void OnDragEndMessage(const OHOS::Msdp::DeviceStatus::DragNotifyMsg &msg) override
    {
        if (callback_ != nullptr) {
            callback_(msg);
        }
    }
    void OnHideIconMessage() override
    {
    }
private:
    DragEndingCallback callback_;
    int32_t instanceId_ = -1;
    RefPtr<TaskExecutor> taskExecutor_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_ACE_ENGINE_ADAPTER_OHOS_CAPABILITY_INTERACTION_START_DRAG_LISTENER_IMPL_H
