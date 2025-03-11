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

#include "core/components_ng/pattern/lazy_layout/grid_layout/lazy_grid_layout_model.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/lazy_layout/grid_layout/lazy_grid_layout_pattern.h"

namespace OHOS::Ace::NG {

void LazyGridLayoutModel::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::LAZY_GRID_LAYOUT_ETS_TAG, nodeId);
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::LAZY_GRID_LAYOUT_ETS_TAG, nodeId, []() {
            return AceType::MakeRefPtr<LazyGridLayoutPattern>();
        });
    stack->Push(frameNode);
}

void LazyGridLayoutModel::SetRowGap(const Dimension& rowGap)
{
    ACE_UPDATE_LAYOUT_PROPERTY(LazyGridLayoutProperty, RowGap, rowGap);
}

void LazyGridLayoutModel::SetColumnGap(const Dimension& columnGap)
{
    ACE_UPDATE_LAYOUT_PROPERTY(LazyGridLayoutProperty, ColumnGap, columnGap);
}

void LazyVGridLayoutModel::SetColumnsTemplate(const std::string& value)
{
    if (value.empty()) {
        ACE_UPDATE_LAYOUT_PROPERTY(LazyGridLayoutProperty, ColumnsTemplate, "1fr");
        return;
    }
    ACE_UPDATE_LAYOUT_PROPERTY(LazyGridLayoutProperty, ColumnsTemplate, value);
}

void LazyGridLayoutModel::SetRowGap(FrameNode* frameNode, const Dimension& rowGap)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LazyGridLayoutProperty, RowGap, rowGap, frameNode);
}

void LazyGridLayoutModel::SetColumnGap(FrameNode* frameNode, const Dimension& columnGap)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LazyGridLayoutProperty, ColumnGap, columnGap, frameNode);
}

void LazyVGridLayoutModel::SetColumnsTemplate(FrameNode* frameNode, const std::string& value)
{
    if (value.empty()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(LazyGridLayoutProperty, ColumnsTemplate, "1fr", frameNode);
        return;
    }
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LazyGridLayoutProperty, ColumnsTemplate, value, frameNode);
}
} // namespace OHOS::Ace::NG
