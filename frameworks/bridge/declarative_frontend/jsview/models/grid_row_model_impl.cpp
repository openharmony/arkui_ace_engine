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

#include "bridge/declarative_frontend/jsview/models/grid_row_model_impl.h"

#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components_v2/grid_layout/grid_row_component.h"

namespace OHOS::Ace::Framework {

void GridRowModelImpl::Create()
{
    auto component = AceType::MakeRefPtr<V2::GridRowComponent>();
    ViewStackProcessor::GetInstance()->Push(component);
}

void GridRowModelImpl::Create(const RefPtr<V2::GridContainerSize>& col, const RefPtr<V2::Gutter>& gutter,
    const RefPtr<V2::BreakPoints>& breakpoints, V2::GridRowDirection direction)
{
    auto component = AceType::MakeRefPtr<V2::GridRowComponent>();
    component->SetTotalCol(col);
    component->SetGutter(gutter);
    component->SetBreakPoints(breakpoints);
    component->SetDirection(direction);
    ViewStackProcessor::GetInstance()->Push(component);
}

void GridRowModelImpl::SetOnBreakPointChange(std::function<void(const std::string)>&& onChange)
{
    auto component = AceType::DynamicCast<V2::GridRowComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (component) {
        component->SetbreakPointChange(std::move(onChange));
    }
}

void GridRowModelImpl::SetHeight()
{
    auto component = AceType::DynamicCast<V2::GridRowComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (component) {
        component->SetHasContainerHeight(true);
    }
}

} // namespace OHOS::Ace::Framework
