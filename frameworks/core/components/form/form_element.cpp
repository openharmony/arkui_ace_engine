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

#include "core/common/form_manager.h"
#include "frameworks/base/utils/string_utils.h"
#include "frameworks/core/components/form/form_component.h"
#include "frameworks/core/components/form/resource/form_manager_delegate.h"

namespace OHOS::Ace {

FormElement::FormElement(const ComposeId& id) : ComposedElement(id) {}

FormElement::~FormElement()
{
    formManagerBridge_.Reset();
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
        cardInfo_.allowUpate = info.allowUpate;
        if (subContainer_) {
            subContainer_->SetAllowUpdate(cardInfo_.allowUpate);
        }
        double scale = subContainer_->GetRootElementScale();
        if (NearZero(scale)) {
            LOGE("scale value is near zero");
            return;
        }

        auto box = AceType::DynamicCast<BoxComponent>(form->GetChild());
        if (!box) {
            LOGE("could not get size box");
            return;
        }
        LOGD("rootbox width:%{public}f, height:%{public}f", box->GetWidth().Value(), box->GetHeight().Value());

        auto transform = AceType::DynamicCast<TransformComponent>(box->GetChild());
        if (transform) {
            transform->Scale(scale, scale, scale);
        }

        auto rootBox = AceType::DynamicCast<BoxComponent>(transform->GetChild());
        if (rootBox) {
            rootBox->SetWidth(box->GetWidth().Value() / scale, box->GetWidth().Unit());
            rootBox->SetHeight(box->GetHeight().Value() / scale, box->GetHeight().Unit());
        }
        return;
    }

    CreateCardContainer();

    if (formManagerBridge_) {
        formManagerBridge_->AddForm(GetContext(), info);
    }

    InitEvent(form);
}

void FormElement::PerformBuild()
{
    RefPtr<FormComponent> form = AceType::DynamicCast<FormComponent>(component_);
    if (form) {
        const auto& child = children_.empty() ? nullptr : children_.front();
        UpdateChild(child, form->GetChild());
    }

    auto box = GetFirstChild();
    if (!box) {
        LOGE("not got form child box");
        return;
    }

    auto boxElement = AceType::DynamicCast<BoxElement>(box);
    if (!boxElement) {
        LOGE("not got box element");
        return;
    }

    auto tarnsform = box->GetFirstChild();
    if (!tarnsform) {
        LOGE("not got transform elment");
        return;
    }

    auto rootBox = tarnsform->GetFirstChild();
    if (!rootBox) {
        LOGE("not got root box");
        return;
    }

    auto stage = rootBox->GetFirstChild();
    if (!stage) {
        LOGE("not got stage");
        return;
    }

    auto stageElement = AceType::DynamicCast<StageElement>(stage);
    if (stageElement) {
        stageElement->SetForCard();
    } else {
        LOGE("not got stage element");
    }

    subContainer_->SetFormElement(AceType::WeakClaim(this));
    subContainer_->SetStageElement(stageElement);
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
    LOGD("HandleOnAcquireEvent acquire event id:%{public}zu", id);

    if (!onAcquireEvent_) {
        LOGE("could not find available event handle");
        return;
    }

    auto json = JsonUtil::Create(true);
    json->Put("id", (size_t)id);
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
    ComposedElement::Prepare(parent);

    if (!formManagerBridge_) {
        formManagerBridge_ =
            AceType::MakeRefPtr<FormManagerDelegate>(GetContext());
        formManagerBridge_->AddFormAcquireCallback(
            [weak = WeakClaim(this)] (int64_t id, std::string path, std::string module, std::string data) {
            auto element = weak.Upgrade();
            auto uiTaskExecutor = SingleTaskExecutor::Make(
                element->GetContext().Upgrade()->GetTaskExecutor(), TaskExecutor::TaskType::UI);
            uiTaskExecutor.PostTask([id, path, module, data, weak] {
                auto form = weak.Upgrade();
                if (form) {
                    form->HandleOnAcquireEvent(id);
                    auto container = form->GetSubContainer();
                    if (container) {
                        container->RunCard(id, path, module, data);
                    }
                }
            });
        });
        formManagerBridge_->AddFormUpdateCallback(
            [weak = WeakClaim(this)] (int64_t id, std::string data) {
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
        formManagerBridge_->AddFormErrorCallback(
            [weak = WeakClaim(this)](std::string code, std::string msg) {
            auto element = weak.Upgrade();
            auto uiTaskExecutor = SingleTaskExecutor::Make(
                element->GetContext().Upgrade()->GetTaskExecutor(), TaskExecutor::TaskType::UI);
            uiTaskExecutor.PostTask([code, msg, weak] {
                auto form = weak.Upgrade();
                if (form) {
                    form->HandleOnErrorEvent(code, msg);
                }
                // when get error from form manager, remove the card
                auto child = form->GetFirstChild();
                if (child) {
                    form->RemoveChild(child);
                    form->MarkNeedRebuild();
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

    if (type == "router") {
        auto context = GetContext().Upgrade();
        if (context) {
            LOGI("send action evetn to ability to process");
            context->OnActionEvent(action);
        }
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

    subContainer_ = AceType::MakeRefPtr<SubContainer>(GetContext().Upgrade());
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

} // namespace OHOS::Ace
