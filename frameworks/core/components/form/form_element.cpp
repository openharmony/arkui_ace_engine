/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "core/components/form/form_element.h"

#include "core/common/container_scope.h"
#include "core/common/form_manager.h"
#ifdef OHOS_STANDARD_SYSTEM
#include "form_info.h"
#endif
#include "frameworks/base/utils/string_utils.h"
#include "frameworks/core/components/form/form_component.h"
#include "frameworks/core/components/form/render_form.h"
#include "frameworks/core/components/form/resource/form_manager_delegate.h"

namespace OHOS::Ace {

FormElement::~FormElement()
{
    formManagerBridge_.Reset();

    auto id = subContainer_->GetRunningCardId();
    FormManager::GetInstance().RemoveSubContainer(id);

    subContainer_->Destroy();
    subContainer_.Reset();
}

void FormElement::Update()
{
    auto form = AceType::DynamicCast<FormComponent>(component_);
    if (!form) {
        LOGE("could not get form component for update");
        return;
    }
    SetElementId(form->GetElementId());

    auto info = form->GetFormRequestInfo();
    if (info.bundleName != cardInfo_.bundleName || info.abilityName != cardInfo_.abilityName ||
        info.moduleName != cardInfo_.moduleName || info.cardName != cardInfo_.cardName ||
        info.dimension != cardInfo_.dimension) {
        cardInfo_ = info;
    } else {
        // for update form component
        UpdateInner(info);
        return;
    }

    GetRenderNode()->Update(component_);

#if OHOS_STANDARD_SYSTEM
    AppExecFwk::FormInfo formInfo;
    if (!FormManagerDelegate::GetFormInfo(info.bundleName, info.moduleName, info.cardName, formInfo)) {
        LOGE("failed to get formInfo with bundleName: %{public}s, moduleName: %{public}s, cardName: %{public}s",
            info.bundleName.c_str(), info.moduleName.c_str(), info.cardName.c_str());
    }
#endif

    CreateCardContainer();

    if (formManagerBridge_) {
#if OHOS_STANDARD_SYSTEM
        formManagerBridge_->AddForm(GetContext(), info, formInfo);
#else
        formManagerBridge_->AddForm(GetContext(), info);
#endif
    }

    InitEvent(form);
}

void FormElement::PerformBuild()
{
    subContainer_->SetFormElement(AceType::WeakClaim(this));
}

void FormElement::InitEvent(const RefPtr<FormComponent>& component)
{
    if (!component->GetOnAcquireFormEventId().IsEmpty()) {
        onAcquireEvent_ =
            AceAsyncEvent<void(const std::string&)>::Create(component->GetOnAcquireFormEventId(), context_);
    }

    if (!component->GetOnErrorEvent().IsEmpty()) {
        onErrorEvent_ = AceAsyncEvent<void(const std::string&)>::Create(component->GetOnErrorEvent(), context_);
    }

    if (!component->GetOnUninstallEvent().IsEmpty()) {
        onUninstallEvent_ =
            AceAsyncEvent<void(const std::string&)>::Create(component->GetOnUninstallEvent(), context_);
    }

    if (!component->GetOnRouterEvent().IsEmpty()) {
        onRouterEvent_ = AceAsyncEvent<void(const std::string&)>::Create(component->GetOnRouterEvent(), context_);
    }
}

void FormElement::UpdateInner(const RequestFormInfo& info)
{
    if (cardInfo_.allowUpdate != info.allowUpdate) {
        cardInfo_.allowUpdate = info.allowUpdate;
        LOGI(" update card allow info:%{public}d", cardInfo_.allowUpdate);
        if (subContainer_) {
            subContainer_->SetAllowUpdate(cardInfo_.allowUpdate);
        }
    }

    if (cardInfo_.width != info.width || cardInfo_.height != info.height) {
        LOGI("update card size old w:%lf,h:%lf", cardInfo_.width.Value(), cardInfo_.height.Value());
        LOGI("update card size new w:%lf,h:%lf", info.width.Value(), info.height.Value());
        cardInfo_.width = info.width;
        cardInfo_.height = info.height;
        GetRenderNode()->Update(component_);
        subContainer_->SetFormComponent(component_);
        subContainer_->UpdateRootElementSize();
        subContainer_->UpdateSurfaceSize();
    }
}

void FormElement::HandleOnAcquireEvent(int64_t id)
{
    if (!onAcquireEvent_) {
        LOGE("could not find available event handle");
        return;
    }
    auto context = context_.Upgrade();
    if (!context) {
        LOGE("fail to get context, onAcquire failed.");
        return;
    }

    auto json = JsonUtil::Create(true);
    json->Put("id", std::to_string(id).c_str());
    LOGI("HandleOnAcquireEvent msg:%{public}s", json->ToString().c_str());
    int32_t instance = context->GetInstanceId();
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), info = json->ToString(), instance] {
            auto element = weak.Upgrade();
            if (element != nullptr && element->onAcquireEvent_ != nullptr) {
                ContainerScope scope(instance);
                element->onAcquireEvent_(info);
            }
        },
        TaskExecutor::TaskType::JS, "ArkUIFormHandleOnAcquireEvent");
}

void FormElement::HandleOnRouterEvent(const std::unique_ptr<JsonValue>& action)
{
    if (!onRouterEvent_) {
        LOGE("action could not find available event handle");
        return;
    }
    auto context = context_.Upgrade();
    if (!context) {
        LOGE("fail to get context, onRouter failed.");
        return;
    }

    auto json = JsonUtil::Create(true);
    json->Put("action", action);

    LOGI("HandleOnRouterEvent msg:%{public}s", json->ToString().c_str());
    int32_t instance = context->GetInstanceId();
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), info = json->ToString(), instance] {
            auto element = weak.Upgrade();
            if (element != nullptr && element->onRouterEvent_ != nullptr) {
                ContainerScope scope(instance);
                element->onRouterEvent_(info);
            }
        },
        TaskExecutor::TaskType::JS, "ArkUIFormHandleOnRouterEvent");
}

void FormElement::HandleOnErrorEvent(const std::string code, const std::string msg)
{
    if (!onErrorEvent_) {
        LOGE("could not find available event handle");
        return;
    }
    auto context = context_.Upgrade();
    if (!context) {
        LOGE("fail to get context, onError failed.");
        return;
    }

    auto json = JsonUtil::Create(true);
    json->Put("errcode", code.c_str());
    json->Put("msg", msg.c_str());

    LOGI("HandleOnErrorEvent msg:%{public}s", msg.c_str());
    int32_t instance = context->GetInstanceId();
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), info = json->ToString(), instance] {
            auto element = weak.Upgrade();
            if (element != nullptr && element->onErrorEvent_ != nullptr) {
                ContainerScope scope(instance);
                element->onErrorEvent_(info);
            }
        },
        TaskExecutor::TaskType::JS, "ArkUIFormHandleOnErrorEvent");
}

void FormElement::HandleOnUninstallEvent(int64_t formId)
{
    if (!onUninstallEvent_) {
        LOGE("could not find available event handle");
        return;
    }
    auto context = context_.Upgrade();
    if (!context) {
        LOGE("fail to get context, onUninstall failed.");
        return;
    }

    auto json = JsonUtil::Create(true);
    json->Put("id", std::to_string(formId).c_str());
    LOGI("HandleOnUninstallEvent formId:%{public}s", std::to_string(formId).c_str());
    int32_t instance = context->GetInstanceId();
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), info = json->ToString(), instance] {
            auto element = weak.Upgrade();
            if (element != nullptr && element->onUninstallEvent_ != nullptr) {
                ContainerScope scope(instance);
                element->onUninstallEvent_(info);
            }
        },
        TaskExecutor::TaskType::JS, "ArkUIFormHandleOnUninstallEvent");
}

void FormElement::Prepare(const WeakPtr<Element>& parent)
{
    RenderElement::Prepare(parent);
    auto context = context_.Upgrade();
    if (!context) {
        LOGE("fail to get context, onUninstall failed.");
        return;
    }

    if (!formManagerBridge_) {
        formManagerBridge_ = AceType::MakeRefPtr<FormManagerDelegate>(GetContext());
        int32_t instanceID = context->GetInstanceId();
        auto formUtils = FormManager::GetInstance().GetFormUtils();
        if (formUtils) {
            formManagerBridge_->SetFormUtils(formUtils);
        }
        formManagerBridge_->AddFormAcquireCallback(
            [weak = WeakClaim(this), instanceID](int64_t id, std::string path, std::string module, std::string data,
                std::map<std::string, sptr<AppExecFwk::FormAshmem>> imageDataMap, AppExecFwk::FormJsInfo formJsInfo,
                const FrontendType& frontendType, const FrontendType& uiSyntax) {
                ContainerScope scope(instanceID);
                auto element = weak.Upgrade();
                auto uiTaskExecutor = SingleTaskExecutor::Make(
                    element->GetContext().Upgrade()->GetTaskExecutor(), TaskExecutor::TaskType::UI);
                uiTaskExecutor.PostTask([id, path, module, data, imageDataMap, formJsInfo, weak,
                                        instanceID, frontendType, uiSyntax] {
                    ContainerScope scope(instanceID);
                    auto form = weak.Upgrade();
                    if (form) {
                        auto container = form->GetSubContainer();
                        if (container) {
                            container->SetWindowConfig(
                                { formJsInfo.formWindow.designWidth, formJsInfo.formWindow.autoDesignWidth });
                            container->RunCard(id, path, module, data, imageDataMap,
                                               formJsInfo.formSrc, frontendType, uiSyntax);
                        }
                    }
                }, "ArkUIFormAcquireAndRunCard");
            });
        formManagerBridge_->AddFormUpdateCallback([weak = WeakClaim(this), instanceID](int64_t id, std::string data,
            std::map<std::string, sptr<AppExecFwk::FormAshmem>> imageDataMap) {
            ContainerScope scope(instanceID);
            auto element = weak.Upgrade();
            auto uiTaskExecutor = SingleTaskExecutor::Make(
                element->GetContext().Upgrade()->GetTaskExecutor(), TaskExecutor::TaskType::UI);
            uiTaskExecutor.PostTask([id, data, imageDataMap, weak, instanceID] {
                ContainerScope scope(instanceID);
                auto form = weak.Upgrade();
                if (form) {
                    if (form->ISAllowUpdate()) {
                        form->GetSubContainer()->UpdateCard(data, imageDataMap);
                    }
                }
            }, "ArkUIFormUpdateCard");
        });
        formManagerBridge_->AddFormErrorCallback(
            [weak = WeakClaim(this), instanceID](std::string code, std::string msg) {
                ContainerScope scope(instanceID);
                auto element = weak.Upgrade();
                auto uiTaskExecutor = SingleTaskExecutor::Make(
                    element->GetContext().Upgrade()->GetTaskExecutor(), TaskExecutor::TaskType::UI);
                uiTaskExecutor.PostTask([code, msg, weak, instanceID] {
                    ContainerScope scope(instanceID);
                    auto form = weak.Upgrade();
                    if (form) {
                        form->HandleOnErrorEvent(code, msg);
                    }

                    auto render = form->GetRenderNode();
                    if (!render) {
                        LOGE("remove card from screen fail, due to could not get card render node");
                        return;
                    }
                    auto renderForm = AceType::DynamicCast<RenderForm>(render);
                    if (renderForm) {
                        renderForm->RemoveChildren();
                    }
                }, "ArkUIFormRemoveCard");
            });
        formManagerBridge_->AddFormUninstallCallback(
            [weak = WeakClaim(this), instanceID](int64_t formId) {
                ContainerScope scope(instanceID);
                auto element = weak.Upgrade();
                auto uiTaskExecutor = SingleTaskExecutor::Make(
                    element->GetContext().Upgrade()->GetTaskExecutor(), TaskExecutor::TaskType::UI);
                uiTaskExecutor.PostTask(
                    [formId, weak, instanceID] {
                        ContainerScope scope(instanceID);
                        auto form = weak.Upgrade();
                        if (form) {
                            form->HandleOnUninstallEvent(formId);
                        }
                    }, "ArkUIFormUninstall");
            });
    }
}

void FormElement::OnActionEvent(const std::string& action) const
{
    LOGI("begin action event");
    auto eventAction = JsonUtil::ParseJsonString(action);
    if (!eventAction->IsValid()) {
        LOGE("get event action failed");
        return;
    }
    auto actionType = eventAction->GetValue("action");
    if (!actionType->IsValid()) {
        LOGE("get event key failed");
        return;
    }

    auto type = actionType->GetString();
    if (type != "router" && type != "message") {
        LOGE("undefined event type");
        return;
    }

#ifndef OHOS_STANDARD_SYSTEM
    if ("router" == type) {
        HandleOnRouterEvent(eventAction);
        return;
    }
#endif

    if (formManagerBridge_) {
        LOGI("send action event to ability.");
        formManagerBridge_->OnActionEvent(action);
    }
}

void FormElement::CreateCardContainer()
{
    if (subContainer_) {
        auto id = subContainer_->GetRunningCardId();
        FormManager::GetInstance().RemoveSubContainer(id);

        subContainer_->Destroy();
        subContainer_.Reset();
    }

    auto context = GetContext().Upgrade();
    if (!context) {
        LOGE("get context fail.");
        return;
    }
    subContainer_ = AceType::MakeRefPtr<SubContainer>(context, context->GetInstanceId());
    if (!subContainer_) {
        LOGE("create card container fail.");
        return;
    }
    subContainer_->Initialize();
    subContainer_->SetFormComponent(component_);
    auto form = AceType::DynamicCast<FormComponent>(component_);
    if (!form) {
        LOGE("form component is null when try adding nonmatched container to form manager.");
        return;
    }

    auto formNode = AceType::DynamicCast<RenderForm>(renderNode_);
    if (!formNode) {
        LOGE("form node is null.");
        return;
    }
    formNode->SetSubContainer(subContainer_);

    subContainer_->AddFormAcquireCallback([weak = WeakClaim(this)](int64_t id) {
        auto element = weak.Upgrade();
        auto uiTaskExecutor =
            SingleTaskExecutor::Make(element->GetContext().Upgrade()->GetTaskExecutor(), TaskExecutor::TaskType::UI);
        uiTaskExecutor.PostTask([id, weak] {
            auto form = weak.Upgrade();
            if (form) {
                LOGI("card id:%{public}" PRId64, id);
                form->HandleOnAcquireEvent(id);
            }
        }, "ArkUIFormAcquire");
    });
}

RefPtr<RenderNode> FormElement::CreateRenderNode()
{
    return RenderForm::Create();
}

} // namespace OHOS::Ace
