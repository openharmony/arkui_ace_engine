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

#include "core/components_ng/pattern/linear_split/linear_split_model_ng.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/linear_split/linear_split_pattern.h"

namespace OHOS::Ace::NG {
void LinearSplitModelNG::Create(SplitType splitType)
{
    std::string tag = splitType == SplitType::ROW_SPLIT ? V2::ROW_SPLIT_ETS_TAG : V2::COLUMN_SPLIT_ETS_TAG;
    auto* stack = ViewStackProcessor::GetInstance();
    int32_t nodeId = (stack == nullptr ? 0 : stack->ClaimNodeId());
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", tag.c_str(), nodeId);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        tag, nodeId, [splitType]() { return AceType::MakeRefPtr<LinearSplitPattern>(splitType); });
    stack->Push(frameNode);
    ACE_UPDATE_RENDER_CONTEXT(ClipEdge, true);
}

void LinearSplitModelNG::SetResizable(NG::SplitType splitType, bool resizable)
{
    ACE_UPDATE_LAYOUT_PROPERTY(LinearSplitLayoutProperty, Resizable, resizable);
}

void LinearSplitModelNG::SetDivider(NG::SplitType splitType, const ColumnSplitDivider& divider)
{
    if (SystemProperties::ConfigChangePerform()) {
        auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
        CHECK_NULL_VOID(frameNode);
        auto pattern = frameNode->GetPattern<LinearSplitPattern>();
        CHECK_NULL_VOID(pattern);
        RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
        auto&& updateFunc = [divider, weak = AceType::WeakClaim(frameNode)](const RefPtr<ResourceObject>& resObj) {
            auto frameNode = weak.Upgrade();
            CHECK_NULL_VOID(frameNode);
            ColumnSplitDivider &value = const_cast<ColumnSplitDivider &>(divider);
            value.ReloadResources();
            ACE_UPDATE_NODE_LAYOUT_PROPERTY(LinearSplitLayoutProperty, Divider, value, frameNode);
            frameNode->MarkModifyDone();
            frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        };
        pattern->AddResObj("ColumnSplit.divider", resObj, std::move(updateFunc));
    }
    ACE_UPDATE_LAYOUT_PROPERTY(LinearSplitLayoutProperty, Divider, divider);
}

void LinearSplitModelNG::SetResizable(FrameNode* frameNode, NG::SplitType splitType, bool resizable)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LinearSplitLayoutProperty, Resizable, resizable, frameNode);
}
void LinearSplitModelNG::SetDivider(FrameNode* frameNode, NG::SplitType splitType, const ColumnSplitDivider& divider)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LinearSplitLayoutProperty, Divider, divider, frameNode);
}
}
// namespace OHOS::Ace::NG
