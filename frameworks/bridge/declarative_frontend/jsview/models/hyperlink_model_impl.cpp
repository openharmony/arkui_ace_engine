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

#include "bridge/declarative_frontend/jsview/models/hyperlink_model_impl.h"

#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "core/components/hyperlink/hyperlink_component.h"
#include "core/components/text/text_component.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_container_base.h"

namespace OHOS::Ace::Framework {
void HyperlinkModelImpl::Create(const std::string& address, const std::string& summary)
{
    std::list<RefPtr<Component>> children;
    RefPtr<OHOS::Ace::HyperlinkComponent> component = AceType::MakeRefPtr<HyperlinkComponent>(children);
    component->SetAddress(address);
    if (!summary.empty()) {
        component->SetSummary(summary);
    }

    ViewStackProcessor::GetInstance()->Push(component);
    JSInteractableView::SetFocusable(false);
    JSInteractableView::SetFocusNode(true);
}

void HyperlinkModelImpl::Pop()
{
    auto hyperlink =
        AceType::DynamicCast<OHOS::Ace::HyperlinkComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    JSContainerBase::Pop();
    if (hyperlink) {
        std::string summary = hyperlink->GetSummary();
        std::list<RefPtr<Component>> children = hyperlink->GetChildren();
        std::list<RefPtr<Component>> flexChild;
        if (!summary.empty()) {
            RefPtr<OHOS::Ace::TextComponent> text = AceType::MakeRefPtr<TextComponent>(summary);
            flexChild.emplace_back(text);
        }
        for (const auto& child : children) {
            flexChild.emplace_back(child);
        }
        RefPtr<OHOS::Ace::ColumnComponent> columnComponent =
            AceType::MakeRefPtr<OHOS::Ace::ColumnComponent>(FlexAlign::FLEX_START, FlexAlign::CENTER, flexChild);
        columnComponent->SetMainAxisSize(MainAxisSize::MIN);
        columnComponent->SetCrossAxisSize(CrossAxisSize::MIN);
        hyperlink->ClearChildren();
        hyperlink->AppendChild(columnComponent);
    }
}

void HyperlinkModelImpl::SetColor(const Color& value)
{
    auto component = GetComponent();
    if (!component) {
        LOGE("component is not valid");
        return;
    }
    component->SetColor(value);
}

RefPtr<HyperlinkComponent> HyperlinkModelImpl::GetComponent()
{
    auto stack = ViewStackProcessor::GetInstance();
    if (!stack) {
        return nullptr;
    }
    return AceType::DynamicCast<HyperlinkComponent>(stack->GetMainComponent());
}
} // namespace OHOS::Ace::Framework