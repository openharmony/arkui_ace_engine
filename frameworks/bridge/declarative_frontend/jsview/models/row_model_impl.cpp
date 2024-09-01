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

#include "bridge/declarative_frontend/jsview/models/row_model_impl.h"

#include "base/memory/referenced.h"
#include "core/components/wrap/wrap_component.h"
#include "core/components_ng/pattern/flex/flex_model.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {

void RowModelImpl::Create(const std::optional<Dimension>& space, AlignDeclaration* declaration, const std::string& tag)
{
    std::list<RefPtr<Component>> children;
    RefPtr<RowComponent> rowComponent =
        AceType::MakeRefPtr<OHOS::Ace::RowComponent>(FlexAlign::FLEX_START, FlexAlign::CENTER, children);
    ViewStackProcessor::GetInstance()->ClaimElementId(rowComponent);
    rowComponent->SetMainAxisSize(MainAxisSize::MIN);
    rowComponent->SetCrossAxisSize(CrossAxisSize::MIN);
    if (space.has_value() && space->Value() >= 0.0) {
        rowComponent->SetSpace(space.value());
    }
    if (declaration != nullptr) {
        rowComponent->SetAlignDeclarationPtr(declaration);
    }
    ViewStackProcessor::GetInstance()->Push(rowComponent);
}

void RowModelImpl::SetAlignItems(FlexAlign flexAlign)
{
    FlexModel::GetInstance()->SetAlignItems(static_cast<int32_t>(flexAlign));
}

void RowModelImpl::SetJustifyContent(FlexAlign flexAlign)
{
    FlexModel::GetInstance()->SetJustifyContent(static_cast<int32_t>(flexAlign));
}

void RowModelImpl::CreateWithWrap()
{
    std::list<RefPtr<Component>> children;
    RefPtr<OHOS::Ace::WrapComponent> component = AceType::MakeRefPtr<WrapComponent>(0.0, 0.0, children);

    component->SetDirection(WrapDirection::HORIZONTAL);
    component->SetMainAlignment(WrapAlignment::START);
    component->SetCrossAlignment(WrapAlignment::START);
    component->SetAlignment(WrapAlignment::START);
    component->SetDialogStretch(false);

    ViewStackProcessor::GetInstance()->Push(component);
}

} // namespace OHOS::Ace::Framework
