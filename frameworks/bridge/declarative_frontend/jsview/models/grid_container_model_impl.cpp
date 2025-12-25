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

#include "bridge/declarative_frontend/jsview/models/grid_container_model_impl.h"

#include "bridge/declarative_frontend/jsview/models/column_model_impl.h"
#include "bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {

thread_local std::vector<RefPtr<GridContainerInfo>> GridContainerModelImpl::gridContainerStack_;

void GridContainerModelImpl::Create(const RefPtr<GridContainerInfo>& containerInfo)
{
    ColumnModelImpl::GetInstance()->Create(std::nullopt, nullptr, V2::GRIDCONTAINER_ETS_TAG);
    gridContainerStack_.emplace_back(containerInfo);
    ViewStackProcessor::GetInstance()->GetBoxComponent()->SetGridLayoutInfo(containerInfo);

    auto main = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto column = AceType::DynamicCast<FlexComponent>(main);
    if (column) {
        column->SetCrossAxisSize(CrossAxisSize::MAX);
    }
}

void GridContainerModelImpl::Pop()
{
    gridContainerStack_.pop_back();
}

} // namespace OHOS::Ace::Framework