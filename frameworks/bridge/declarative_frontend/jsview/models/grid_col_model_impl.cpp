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

#include "bridge/declarative_frontend/jsview/models/grid_col_model_impl.h"

#include "core/components_v2/grid_layout/grid_col_component.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {

void GridColModelImpl::Create()
{
    auto component = AceType::MakeRefPtr<V2::GridColComponent>();
    ViewStackProcessor::GetInstance()->Push(component);
}

void GridColModelImpl::Create(const V2::GridContainerSize& span, const V2::GridContainerSize& offset,
    const V2::GridContainerSize& order)
{
    auto component = AceType::MakeRefPtr<V2::GridColComponent>();
    ViewStackProcessor::GetInstance()->Push(component);
    component->SetSpan(span);
    component->SetOffset(offset);
    component->SetOrder(order);
}

void GridColModelImpl::SetSpan(const V2::GridContainerSize& span)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto gridCol = AceType::DynamicCast<V2::GridColComponent>(component);
    if (gridCol) {
        gridCol->SetSpan(span);
    }
}

void GridColModelImpl::SetOffset(const V2::GridContainerSize& offset)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto gridCol = AceType::DynamicCast<V2::GridColComponent>(component);
    if (gridCol) {
        gridCol->SetOffset(offset);
    }
}

void GridColModelImpl::SetOrder(const V2::GridContainerSize& order)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto gridCol = AceType::DynamicCast<V2::GridColComponent>(component);
    if (gridCol) {
        gridCol->SetOrder(order);
    }
}

} // namespace OHOS::Ace::Framework
