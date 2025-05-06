/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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
#include "bridge/declarative_frontend/jsview/models/form_model_impl.h"

#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components/form/form_component.h"

namespace OHOS::Ace::Framework {
void FormModelImpl::Create(const RequestFormInfo& info)
{
    RefPtr<FormComponent> form = AceType::MakeRefPtr<OHOS::Ace::FormComponent>();
    form->SetFormRequestInfo(info);
    form->SetInspectorTag("FormComponent");
    ViewStackProcessor::GetInstance()->Push(form, false);
    auto boxComponent = ViewStackProcessor::GetInstance()->GetBoxComponent();
    boxComponent->SetMouseAnimationType(HoverAnimationType::SCALE);
}

void FormModelImpl::SetSize(const Dimension& width, const Dimension& height)
{
    auto form = AceType::DynamicCast<FormComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (form) {
        form->SetCardSize(width.IsValid() ? width : 0.0_vp, height.IsValid() ? height : 0.0_vp);
    }
}

void FormModelImpl::SetDimension(int32_t value)
{
    auto form = AceType::DynamicCast<FormComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (form) {
        form->SetDimension(value);
    }
}

void FormModelImpl::AllowUpdate(bool value)
{
    auto form = AceType::DynamicCast<FormComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (form) {
        form->SetAllowUpdate(value);
    }
}

void FormModelImpl::SetVisible(VisibleType visible) {}

void FormModelImpl::SetVisibility(VisibleType visible)
{
    auto component = ViewStackProcessor::GetInstance()->GetDisplayComponent();
    auto display = AceType::DynamicCast<DisplayComponent>(component);
    display->SetVisible(visible);
}

void FormModelImpl::SetModuleName(const std::string& value)
{
    auto form = AceType::DynamicCast<FormComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (form) {
        form->SetModuleName(value);
    }
}

void FormModelImpl::SetOnAcquired(std::function<void(const std::string&)>&& onAcquired)
{
    auto form = AceType::DynamicCast<FormComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    auto onAppearId = EventMarker(std::move(onAcquired));
    if (form) {
        form->SetOnAcquireFormEventId(onAppearId);
    }
}

void FormModelImpl::SetOnError(std::function<void(const std::string&)>&& onError)
{
    auto form = AceType::DynamicCast<FormComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    auto onErrorId = EventMarker(std::move(onError));
    if (form) {
        form->SetOnErrorEventId(onErrorId);
    }
}

void FormModelImpl::SetOnUninstall(std::function<void(const std::string&)>&& onUninstall)
{
    auto form = AceType::DynamicCast<FormComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    auto onUninstallId = EventMarker(std::move(onUninstall));
    if (form) {
        form->SetOnUninstallEventId(onUninstallId);
    }
}

void FormModelImpl::SetOnRouter(std::function<void(const std::string&)>&& onRouter)
{
    auto form = AceType::DynamicCast<FormComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    auto onRouterId = EventMarker(std::move(onRouter));
    if (form) {
        form->SetOnRouterEventId(onRouterId);
    }
}

void FormModelImpl::SetOnLoad(std::function<void(const std::string&)>&& onLoad)
{
    LOGE("Not support onLoad in old pipeline");
}

void FormModelImpl::SetOnUpdate(std::function<void(const std::string&)>&& onUpdate)
{
    LOGE("Not support onUpdate in old pipeline");
}

void FormModelImpl::SetObscured(const std::vector<ObscuredReasons>& reasons)
{
    LOGE("Not support SetObscured in old pipeline");
}

int32_t FormModelImpl::RequestPublishFormWithSnapshot(const AAFwk::Want& want,
    const std::string& formBindingDataStr, int64_t& formId, std::string &errMsg)
{
    LOGE("Not support RequestPublishFormWithSnapshot in old pipeline");
    return 0;
}
} // namespace OHOS::Ace::Framework
