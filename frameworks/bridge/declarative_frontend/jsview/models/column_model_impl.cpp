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

#include "bridge/declarative_frontend/jsview/models/column_model_impl.h"

#include "base/memory/referenced.h"
#include "core/components/flex/flex_component.h"
#include "core/components/wrap/wrap_component.h"
#include "core/components_ng/pattern/flex/flex_model.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {

void ColumnModelImpl::Create(
    const std::optional<Dimension>& space, AlignDeclaration* declaration, const std::string& tag)
{
    std::list<RefPtr<Component>> children;
    RefPtr<ColumnComponent> columnComponent =
        AceType::MakeRefPtr<OHOS::Ace::ColumnComponent>(FlexAlign::FLEX_START, FlexAlign::CENTER, children);
    ViewStackProcessor::GetInstance()->ClaimElementId(columnComponent);
    columnComponent->SetMainAxisSize(MainAxisSize::MIN);
    columnComponent->SetCrossAxisSize(CrossAxisSize::MIN);
    if (space.has_value()) {
        columnComponent->SetSpace(space.value());
    }
    if (declaration != nullptr) {
        columnComponent->SetAlignDeclarationPtr(declaration);
    }

    columnComponent->SetInspectorTag(tag);
    ViewStackProcessor::GetInstance()->Push(columnComponent, false);
    JSInteractableView::SetFocusNode(true);
}

void ColumnModelImpl::SetAlignItems(FlexAlign flexAlign)
{
    FlexModel::GetInstance()->SetAlignItems(static_cast<int32_t>(flexAlign));
}

void ColumnModelImpl::SetJustifyContent(FlexAlign flexAlign)
{
    FlexModel::GetInstance()->SetJustifyContent(static_cast<int32_t>(flexAlign));
}

void ColumnModelImpl::CreateWithWrap()
{
    std::list<RefPtr<Component>> children;
    RefPtr<WrapComponent> component = AceType::MakeRefPtr<WrapComponent>(0.0, 0.0, children);
    ViewStackProcessor::GetInstance()->ClaimElementId(component);

    component->SetDirection(WrapDirection::VERTICAL);
    component->SetMainAlignment(WrapAlignment::START);
    component->SetCrossAlignment(WrapAlignment::START);
    component->SetAlignment(WrapAlignment::START);
    component->SetDialogStretch(false);

    ViewStackProcessor::GetInstance()->Push(component);
}

} // namespace OHOS::Ace::Framework
