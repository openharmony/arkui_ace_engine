/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/models/xcomponent_model_impl.h"

#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components/xcomponent/xcomponent_component_client.h"
#include "bridge/declarative_frontend/jsview/js_xcomponent.h"

namespace OHOS::Ace::Framework {

void XComponentModelImpl::Create(const std::optional<std::string>& id, XComponentType /* type */,
    const std::optional<std::string>& libraryname,
    const std::shared_ptr<InnerXComponentController>& xcomponentController)
{
    auto xcomponentComponent = AceType::MakeRefPtr<OHOS::Ace::XComponentComponent>("xcomponent");
    xcomponentComponent->SetId(id.value_or(""));
    xcomponentComponent->SetXComponentType("surface");
    xcomponentComponent->SetLibraryName(libraryname.value_or(""));
    if (xcomponentController) {
        xcomponentComponent->SetXComponentController(xcomponentController);
    }

    XComponentComponentClient::GetInstance().AddXComponentToXcomponentsMap(
        xcomponentComponent->GetId(), xcomponentComponent);
    auto deleteCallback = [xcId = id.value_or("")]() {
        XComponentComponentClient::GetInstance().DeleteFromXcomponentsMapById(xcId);
        XComponentClient::GetInstance().DeleteControllerFromJSXComponentControllersMap(xcId);
    };
    xcomponentComponent->RegisterDeleteCallback(std::move(deleteCallback));
    ViewStackProcessor::GetInstance()->Push(xcomponentComponent);
}

void XComponentModelImpl::SetSoPath(const std::string& soPath)
{
    auto xcomponentComponent =
        AceType::DynamicCast<XComponentComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(xcomponentComponent);
    xcomponentComponent->SetSoPath(soPath);
}

void XComponentModelImpl::SetOnLoad(LoadEvent&& onLoad)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto xcomponentComponent = AceType::DynamicCast<XComponentComponent>(stack->GetMainComponent());
    if (!xcomponentComponent) {
        LOGE("JSXComponent::JsOnLoad xcomponentComponent is null.");
        return;
    }
    auto xcomponentId = xcomponentComponent->GetId();
    xcomponentComponent->SetXComponentInitEventId(
        EventMarker([func = std::move(onLoad), xcomponentId](const std::string& param) { func(xcomponentId); }));
}

void XComponentModelImpl::SetOnDestroy(DestroyEvent&& onDestroy)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto xcomponentComponent = AceType::DynamicCast<XComponentComponent>(stack->GetMainComponent());
    if (!xcomponentComponent) {
        LOGE("JSXComponent::JsOnDestroy xcomponentComponent is null.");
        return;
    }
    xcomponentComponent->SetXComponentDestroyEventId(
        EventMarker([func = std::move(onDestroy)](const std::string& param) { func(""); }));
}
} // namespace OHOS::Ace::Framework
