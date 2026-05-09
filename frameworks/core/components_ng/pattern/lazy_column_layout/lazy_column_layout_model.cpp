/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/lazy_column_layout/lazy_column_layout_model.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/lazy_layout/lazy_layout_utils.h"
#include "core/components_ng/pattern/lazy_column_layout/lazy_column_layout_pattern.h"

namespace OHOS::Ace::NG {

void LazyColumnLayoutModel::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", "LazyColumnLayout", nodeId);
    auto frameNode = FrameNode::GetOrCreateFrameNode("LazyColumnLayout", nodeId, []() {
        return AceType::MakeRefPtr<LazyColumnLayoutPattern>();
    });
    stack->Push(frameNode);
}

void LazyColumnLayoutModel::SetSpace(const Dimension& space)
{
    ACE_UPDATE_LAYOUT_PROPERTY(LazyColumnLayoutProperty, Space, space);
}

void LazyColumnLayoutModel::SetAlignItems(HorizontalAlign align)
{
    ACE_UPDATE_LAYOUT_PROPERTY(LazyColumnLayoutProperty, HorizontalAlign, align);
}

void LazyColumnLayoutModel::SetOnVisibleIndexesChange(VisibleIndexesChangeEvent&& onVisibleIndexesChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    SetOnVisibleIndexesChange(frameNode, std::move(onVisibleIndexesChange));
}

void LazyColumnLayoutModel::SetSpace(FrameNode* frameNode, const Dimension& space)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LazyColumnLayoutProperty, Space, space, frameNode);
}

void LazyColumnLayoutModel::SetAlignItems(FrameNode* frameNode, HorizontalAlign align)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LazyColumnLayoutProperty, HorizontalAlign, align, frameNode);
}

void LazyColumnLayoutModel::SetOnVisibleIndexesChange(
    FrameNode* frameNode, VisibleIndexesChangeEvent&& onVisibleIndexesChange)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<LazyColumnLayoutPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetOnVisibleIndexesChange(std::move(onVisibleIndexesChange));
}

} // namespace OHOS::Ace::NG
