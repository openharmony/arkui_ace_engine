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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_DISTRIBUTE_UI_MANAGER_H
#define FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_DISTRIBUTE_UI_MANAGER_H

#include "interfaces/inner_api/ace/serializeable_object.h"

#include "adapter/ohos/entrance/ace_container.h"
#include "core/common/container_scope.h"

namespace OHOS::Ace {
class DistributeUIManager {
public:
    explicit DistributeUIManager(int32_t instanceid) : instanceId_(instanceid) {}
    ~DistributeUIManager() = default;

    SerializeableObjectArray DumpUITree()
    {
        SerializeableObjectArray ret;
        auto task = [&ret]() {};
        PostSyncTaskToUI(task);
        return ret;
    }

    void SubscribeUpdate(const std::function<void(int32_t, SerializeableObjectArray&)>& onUpdate) {}

    void UnSubscribeUpdate() {}

    void ProcessSerializeableInputEvent(const SerializeableObjectArray& event)
    {
        auto task = [&event]() {};
        PostSyncTaskToUI(task);
    }

    void RestoreUITree(const SerializeableObjectArray& uiTree)
    {
        auto task = [&uiTree]() {};
        PostSyncTaskToUI(task);
    }

    void UpdateUITree(const SerializeableObjectArray& update)
    {
        auto task = [&update]() {};
        PostSyncTaskToUI(task);
    }

    void SubscribeInputEventProcess(const std::function<void(SerializeableObjectArray&)>& onEvent) {}

    void UnSubscribeInputEventProcess() {}

private:
    void PostSyncTaskToUI(const std::function<void()>& task)
    {
        auto container = Platform::AceContainer::GetContainer(instanceId_);
        CHECK_NULL_VOID(container);
        auto taskExecutor = container->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        ContainerScope scope(instanceId_);

        taskExecutor->PostSyncTask(task, TaskExecutor::TaskType::UI);
    }

    int32_t instanceId_ = -1;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_DISTRIBUTE_UI_MANAGER_H
