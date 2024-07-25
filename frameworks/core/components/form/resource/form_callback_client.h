/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_FORM_RESOURCE_FORM_CALLBACK_CLIENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_FORM_RESOURCE_FORM_CALLBACK_CLIENT_H

#include "form_callback_interface.h"

#include "core/common/ace_engine.h"
namespace OHOS::Ace {

class FormCallbackClient : public OHOS::AppExecFwk::FormCallbackInterface,
    public std::enable_shared_from_this<FormCallbackClient> {
public:
    FormCallbackClient() = default;
    virtual ~FormCallbackClient() = default;

    void ProcessFormUpdate(const AppExecFwk::FormJsInfo& formJsInfo) override
    {
        auto container = AceEngine::Get().GetContainer(instanceId_);
        CHECK_NULL_VOID(container);
        ContainerScope scope(instanceId_);
        auto taskExecutor = container->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        taskExecutor->PostTask(
            [delegate = delegate_, formJsInfo]() {
                auto formManagerDelegate = delegate.Upgrade();
                if (formManagerDelegate) {
                    formManagerDelegate->ProcessFormUpdate(formJsInfo);
                }
            },
            TaskExecutor::TaskType::UI, "ArkUIFormProcessUpdate");
    }

    void ProcessFormUninstall(const int64_t formId) override
    {
        auto container = AceEngine::Get().GetContainer(instanceId_);
        CHECK_NULL_VOID(container);
        ContainerScope scope(instanceId_);
        auto taskExecutor = container->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        taskExecutor->PostTask(
            [delegate = delegate_, formId]() {
                auto formManagerDelegate = delegate.Upgrade();
                if (formManagerDelegate) {
                    formManagerDelegate->ProcessFormUninstall(formId);
                }
            },
            TaskExecutor::TaskType::UI, "ArkUIFormProcessUninstall");
    }

    void OnDeathReceived() override
    {
        auto container = AceEngine::Get().GetContainer(instanceId_);
        CHECK_NULL_VOID(container);
        ContainerScope scope(instanceId_);
        auto taskExecutor = container->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        taskExecutor->PostTask(
            [delegate = delegate_]() {
                auto formManagerDelegate = delegate.Upgrade();
                if (formManagerDelegate) {
                    formManagerDelegate->OnDeathReceived();
                }
            },
            TaskExecutor::TaskType::UI, "ArkUIFormDeathReceived");
    }

    void OnError(const int32_t errorCode, const std::string& errorMsg) override
    {
        auto container = AceEngine::Get().GetContainer(instanceId_);
        CHECK_NULL_VOID(container);
        ContainerScope scope(instanceId_);
        auto taskExecutor = container->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        taskExecutor->PostTask(
            [delegate = delegate_, errorCode, errorMsg]() {
                auto formManagerDelegate = delegate.Upgrade();
                if (formManagerDelegate) {
                    formManagerDelegate->OnFormError(std::to_string(errorCode), errorMsg);
                }
            },
            TaskExecutor::TaskType::UI, "ArkUIFormError");
    }

    void SetFormManagerDelegate(WeakPtr<FormManagerDelegate> delegate)
    {
        delegate_ = delegate;
    }

    void SetInstanceId(const int32_t instanceId)
    {
        instanceId_ = instanceId;
    }

    void ProcessRecycleForm() override
    {
        auto container = AceEngine::Get().GetContainer(instanceId_);
        CHECK_NULL_VOID(container);
        ContainerScope scope(instanceId_);
        auto taskExecutor = container->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        taskExecutor->PostTask(
            [delegate = delegate_]() {
                auto formManagerDelegate = delegate.Upgrade();
                if (formManagerDelegate) {
                    formManagerDelegate->ProcessRecycleForm();
                }
            },
            TaskExecutor::TaskType::UI, "ArkUIFormProcessRecycleForm");
    }

    void ProcessEnableForm(bool enable) override
    {
        TAG_LOGI(AceLogTag::ACE_FORM, "FormCallbackClient::ProcessEnableForm");
        auto container = AceEngine::Get().GetContainer(instanceId_);
        CHECK_NULL_VOID(container);
        ContainerScope scope(instanceId_);
        auto taskExecutor = container->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        taskExecutor->PostTask(
            [delegate = delegate_, enable]() {
                auto formManagerDelegate = delegate.Upgrade();
                if (!formManagerDelegate) {
                    TAG_LOGE(AceLogTag::ACE_FORM, "formManagerDelegate is nullptr");
                    return;
                }
                formManagerDelegate->ProcessEnableForm(enable);
            },
            TaskExecutor::TaskType::UI, "ArkUIFormProcessEnableForm");
    }

private:
    int32_t instanceId_ = -1;
    WeakPtr<FormManagerDelegate> delegate_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_FORM_RESOURCE_FORM_CALLBACK_CLIENT_H
