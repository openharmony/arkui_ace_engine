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
#include "core/components_ng/base/distributed_ui.h"

namespace OHOS::Ace {
class DistributedUIManager {
public:
    DistributedUIManager(int32_t instanceid, const std::shared_ptr<NG::DistributedUI>& distributedUI)
        : instanceId_(instanceid), distributedUI_(distributedUI)
    {}
    ~DistributedUIManager() = default;

    SerializeableObjectArray DumpUITree()
    {
        SerializeableObjectArray ret;
        auto task = [this, &ret]() { ret = distributedUI_->DumpUITree(); };
        PostSyncTaskToUI(task, "ArkUIDistributedDumpUITree");
        return ret;
    }

    void SubscribeUpdate(const std::function<void(int32_t, SerializeableObjectArray&)>& onUpdate)
    {
        distributedUI_->SubscribeUpdate(onUpdate);
    }

    void UnSubscribeUpdate()
    {
        distributedUI_->UnSubscribeUpdate();
    }

    void ProcessSerializeableInputEvent(const SerializeableObjectArray& event)
    {
        auto task = [this, &event]() { distributedUI_->ProcessSerializeableInputEvent(event); };
        PostSyncTaskToUI(task, "ArkUIDistributedProcessSerializeableInput");
    }

    void RestoreUITree(const SerializeableObjectArray& uiTree)
    {
        auto task = [this, &uiTree]() { distributedUI_->RestoreUITree(uiTree); };
        PostSyncTaskToUI(task, "ArkUIDistributedRestoreUITree");
    }

    void UpdateUITree(const SerializeableObjectArray& update)
    {
        auto task = [this, &update]() { distributedUI_->UpdateUITree(update); };
        PostSyncTaskToUI(task, "ArkUIDistributedUpdateUITree");
    }

    void SubscribeInputEventProcess(const std::function<void(SerializeableObjectArray&)>& onEvent)
    {
        distributedUI_->SubscribeInputEventProcess(onEvent);
    }

    void UnSubscribeInputEventProcess()
    {
        distributedUI_->UnSubscribeInputEventProcess();
    }

private:
    void PostSyncTaskToUI(const std::function<void()>& task, const std::string& name)
    {
        auto container = Platform::AceContainer::GetContainer(instanceId_);
        CHECK_NULL_VOID(container);
        auto taskExecutor = container->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        ContainerScope scope(instanceId_);
        taskExecutor->PostSyncTask(task, TaskExecutor::TaskType::UI, name);
    }

    int32_t instanceId_ = -1;
    std::shared_ptr<NG::DistributedUI> distributedUI_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_DISTRIBUTE_UI_MANAGER_H
