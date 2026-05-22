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

#include "core/components_ng/pattern/lazy_column_layout/lazy_column_layout_model_static.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/lazy_column_layout/lazy_column_layout_pattern.h"
#include "core/components_ng/pattern/lazy_column_layout/lazy_column_layout_property.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

RefPtr<FrameNode> LazyColumnLayoutModelStatic::CreateFrameNode(int32_t nodeId)
{
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", "LazyColumnLayout", nodeId);
    auto frameNode = FrameNode::GetOrCreateFrameNode("LazyColumnLayout", nodeId, []() {
        return AceType::MakeRefPtr<LazyColumnLayoutPattern>();
    });
    return frameNode;
}

void LazyColumnLayoutModelStatic::SetSpace(FrameNode* frameNode, const std::optional<Dimension>& space)
{
    if (space) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(LazyColumnLayoutProperty, Space, space.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY_WITH_FLAG(LazyColumnLayoutProperty, Space, PROPERTY_UPDATE_MEASURE, frameNode);
    }
}

void LazyColumnLayoutModelStatic::SetAlignItems(FrameNode* frameNode, std::optional<HorizontalAlign> align)
{
    if (align) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(LazyColumnLayoutProperty, HorizontalAlign, align.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY_WITH_FLAG(
            LazyColumnLayoutProperty, HorizontalAlign, PROPERTY_UPDATE_MEASURE, frameNode);
    }
}

void LazyColumnLayoutModelStatic::SetOnVisibleIndexesChange(
    FrameNode* frameNode, VisibleIndexesChangeEvent&& onVisibleIndexesChange)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<LazyColumnLayoutPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetOnVisibleIndexesChange(std::move(onVisibleIndexesChange));
}

} // namespace OHOS::Ace::NG
