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

#include "bridge/declarative_frontend/jsview/models/linear_split_model_impl.h"

#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components/split_container/column_split_component.h"
#include "core/components/split_container/row_split_component.h"

namespace OHOS::Ace::Framework {

void LinearSplitModelImpl::Create(NG::SplitType splitType)
{
    if (splitType == NG::SplitType::ROW_SPLIT) {
        std::list<RefPtr<OHOS::Ace::Component>> componentChildren;
        auto rowSplit = AceType::MakeRefPtr<RowSplitComponent>(componentChildren);
        ViewStackProcessor::GetInstance()->Push(rowSplit);
        auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
        box->SetBoxClipFlag(true);
    } else if (splitType == NG::SplitType::COLUMN_SPLIT) {
        std::list<RefPtr<OHOS::Ace::Component>> componentChildren;
        auto columnSplit = AceType::MakeRefPtr<ColumnSplitComponent>(componentChildren);
        ViewStackProcessor::GetInstance()->ClaimElementId(columnSplit);
        ViewStackProcessor::GetInstance()->Push(columnSplit);
        auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
        box->SetBoxClipFlag(true);
    }
}

void LinearSplitModelImpl::SetResizable(NG::SplitType splitType, bool resizable)
{
    if (splitType == NG::SplitType::ROW_SPLIT) {
        auto rowSplit = AceType::DynamicCast<RowSplitComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
        if (rowSplit) {
            rowSplit->SetResizable(resizable);
        }
    } else if (splitType == NG::SplitType::COLUMN_SPLIT) {
        auto columnSplit =
            AceType::DynamicCast<ColumnSplitComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
        if (columnSplit) {
            columnSplit->SetResizable(resizable);
        }
    }
}

void LinearSplitModelImpl::SetDivider(NG::SplitType splitType, const NG::ColumnSplitDivider& divider)
{
}


} // namespace OHOS::Ace::Framework