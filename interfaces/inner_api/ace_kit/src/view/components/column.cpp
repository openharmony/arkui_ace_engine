/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "ui/view/components/column.h"

#include "interfaces/inner_api/ace_kit/src/view/frame_node_impl.h"
#include "ui/base/referenced.h"
#include "ui/view_stack/view_stack_processor.h"

#include "core/components_ng/pattern/linear_layout/column_model_ng.h"

namespace OHOS::Ace::Kit {

Column::Column()
{
    int32_t nodeId = Ace::Kit::ViewStackProcessor::ClaimNodeId();
    auto aceNode = NG::ColumnModelNG::CreateFrameNode(nodeId);
    node_ = AceType::MakeRefPtr<FrameNodeImpl>(aceNode);
}

Column::~Column() = default;

RefPtr<Column> Column::Create()
{
    return Referenced::MakeRefPtr<Column>();
}

void Column::SetSpace(const std::optional<Dimension>& space)
{
    NG::ColumnModelNG::SetSpace(reinterpret_cast<AceNode*>(node_->GetHandle()), space);
}

void Column::SetJustifyContent(FlexAlign flexAlign)
{
    NG::ColumnModelNG::SetJustifyContent(reinterpret_cast<AceNode*>(node_->GetHandle()), flexAlign);
}

void Column::SetAlignItems(FlexAlign flexAlign)
{
    NG::ColumnModelNG::SetAlignItems(reinterpret_cast<AceNode*>(node_->GetHandle()), flexAlign);
}

void Column::SetIsReverse(bool isReverse)
{
    NG::ColumnModelNG::SetIsReverse(reinterpret_cast<AceNode*>(node_->GetHandle()), isReverse);
}

FlexAlign Column::GetJustifyContent()
{
    return NG::ColumnModelNG::GetJustifyContent(reinterpret_cast<AceNode*>(node_->GetHandle()));
}

FlexAlign Column::GetAlignItems()
{
    return NG::ColumnModelNG::GetAlignItems(reinterpret_cast<AceNode*>(node_->GetHandle()));
}

} // namespace OHOS::Ace::Kit
