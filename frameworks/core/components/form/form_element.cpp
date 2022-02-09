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

#include "core/components/form/form_element.h"

#include <string>

#include "core/common/form_manager.h"
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
        LOGE("could not get form componet for update");
        return;
    }

    auto info = form->GetFormRequestionInfo();
    if (info.bundleName != cardInfo_.bundleName || info.abilityName != cardInfo_.abilityName ||
        info.moduleName != cardInfo_.moduleName || info.cardName != cardInfo_.cardName ||
        info.dimension != cardInfo_.dimension) {
        cardInfo_ = info;
    } else {
        // for update form componet
        if (cardInfo_.allowUpate != info.allowUpate) {
            cardInfo_.allowUpate = info.allowUpate;
            LOGI(" update card allow info:%{public}d", cardInfo_.allowUpate);
            if (subContainer_) {
                subContainer_->SetAllowUpdate(cardInfo_.allowUpate);
            }
        }

        if (cardInfo_.width != info.width || cardInfo_.height != info.height) {
            LOGI("update card size old w:%lf,h:%lf", cardInfo_.width.Value(), cardInfo_.height.Value());
            LOGI("update card size new w:%lf,h:%lf", info.width.Value(), info.height.Value());
            cardInfo_.width = info.width;
            cardInfo_.height = info.height;
            GetRenderNode()->Update(component_);
            subContainer_->SetFormComponet(component_);
            subContainer_->UpdateRootElmentSize();
            subContainer_->UpdateSurfaceSize();
        }

        return;
    }

    GetRenderNode()->Update(component_);

    CreateCardContainer();

    if (formManagerBridge_) {
        formManagerBridge_->AddForm(GetContext(), info);
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

    if (!component->GetOnRouterEvent().IsEmpty()) {
        onRouterEvent_ = AceAsyncEvent<void(const std::string&)>::Create(component->GetOnRouterEvent(), context_);
    }
}

void FormElement::HandleOnAcquireEvent(int64_t id) const
{
    LOGD("HandleOnAcquireEvent acquire event id:%{public}d", static_cast<int32_t>(id));

    if (!onAcquireEvent_) {
        LOGE("could not find available event handle");
        return;
    }

    auto json = JsonUtil::Create(true);
    json->Put("id", std::to_string(id).c_str());
    onAcquireEvent_(json->ToString());
}

void FormElement::HandleOnRouterEvent(const std::unique_ptr<JsonValue>& action) const
{
    if (!onRouterEvent_) {
        LOGE("action could not find available event handle");
        return;
    }

    auto json = JsonUtil::Create(true);
    json->Put("action", action);
    onRouterEvent_(json->ToString());
}

void FormElement::HandleOnErrorEvent(const std::string code, const std::string msg) const
{
    LOGD("HandleOnErrorEvent msg:%{public}s", msg.c_str());

    if (!onErrorEvent_) {
        LOGE("could not find available event handle");
        return;
    }

    auto json = JsonUtil::Create(true);
    json->Put("errcode", code.c_str());
    json->Put("msg", msg.c_str());
    onErrorEvent_(json->ToString());
}

void FormElement::Prepare(const WeakPtr<Element>& parent)
{
    RenderElement::Prepare(parent);

    if (!formManagerBridge_) {
        formManagerBridge_ = AceType::MakeRefPtr<FormManagerDelegate>(GetContext());
        formManagerBridge_->AddFormAcquireCallback(
            [weak = WeakClaim(this)](int64_t id, std::string path, std::string module, std::string data,
                std::map<std::string, std::pair<int, int32_t>> imageDataMap) {
                auto element = weak.Upgrade();
                auto uiTaskExecutor = SingleTaskExecutor::Make(
                    element->GetContext().Upgrade()->GetTaskExecutor(), TaskExecutor::TaskType::UI);
                uiTaskExecutor.PostTask([id, path, module, data, imageDataMap, weak] {
                    auto form = weak.Upgrade();
                    if (form) {
                        auto container = form->GetSubContainer();
                        if (container) {
                            container->RunCard(id, path, module, data, imageDataMap);
                        }
                    }
                });
            });
        formManagerBridge_->AddFormUpdateCallback([weak = WeakClaim(this)](int64_t id, std::string data) {
            auto element = weak.Upgrade();
            auto uiTaskExecutor = SingleTaskExecutor::Make(
                element->GetContext().Upgrade()->GetTaskExecutor(), TaskExecutor::TaskType::UI);
            uiTaskExecutor.PostTask([id, data, weak] {
                auto form = weak.Upgrade();
                if (form) {
                    if (form->ISAllowUpdate()) {
                        form->GetSubContainer()->UpdateCard(data);
                    }
                }
            });
        });
        formManagerBridge_->AddFormErrorCallback([weak = WeakClaim(this)](std::string code, std::string msg) {
            auto element = weak.Upgrade();
            auto uiTaskExecutor = SingleTaskExecutor::Make(
                element->GetContext().Upgrade()->GetTaskExecutor(), TaskExecutor::TaskType::UI);
            uiTaskExecutor.PostTask([code, msg, weak] {
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
            });
        });
    }
}

void FormElement::OnActionEvent(const std::string& action) const
{
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

    if ("router" == type) {
#ifdef OHOS_STANDARD_SYSTEM
        auto context = GetContext().Upgrade();
        if (context) {
            LOGI("send action evetn to ability to process");
            context->OnActionEvent(action);
        }
#else
        HandleOnRouterEvent(eventAction);
#endif
        return;
    }

    if (formManagerBridge_) {
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
    subContainer_->SetFormComponet(component_);
    auto form = AceType::DynamicCast<FormComponent>(component_);
    if (!form) {
        LOGE("form componet is null when try adding nonmatched container to form manager.");
        return;
    }
    auto info = form->GetFormRequestionInfo();
    auto key = info.ToString();
    FormManager::GetInstance().AddNonmatchedContainer(key, subContainer_);

    auto formNode = AceType::DynamicCast<RenderForm>(renderNode_);
    if (!formNode) {
        LOGE("form node is null.");
        return;
    }
    formNode->SetSubContainer(subContainer_);

    subContainer_->AddFormAcquireCallback([weak = WeakClaim(this)](size_t id) {
        auto element = weak.Upgrade();
        auto uiTaskExecutor =
            SingleTaskExecutor::Make(element->GetContext().Upgrade()->GetTaskExecutor(), TaskExecutor::TaskType::UI);
        uiTaskExecutor.PostTask([id, weak] {
            auto form = weak.Upgrade();
            if (form) {
                LOGI("cardid id:%{public}zu", id);
                form->HandleOnAcquireEvent(id);
            }
        });
    });
}

RefPtr<RenderNode> FormElement::CreateRenderNode()
{
    return RenderForm::Create();
}

} // namespace OHOS::Ace
