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

#include "bridge/declarative_frontend/ng/entry_page_info.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/components_ng/pattern/stage/stage_manager.h"
#include "core/components_ng/pattern/stage/stage_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
StageManager::StageManager(const RefPtr<FrameNode>& stage) : stageNode_(stage)
{
    stagePattern_ = DynamicCast<StagePattern>(stageNode_->GetPattern());
}

RefPtr<FrameNode> StageManager::GetLastPage()
{
    auto entryPageInfo = AceType::MakeRefPtr<EntryPageInfo>(0, "", "", "");
    auto* stack = ViewStackProcessor::GetInstance();
    int32_t nodeId = (stack == nullptr ? 0 : stack->ClaimNodeId());
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::PAGE_ETS_TAG, nodeId, [entryPageInfo]() { return AceType::MakeRefPtr<PagePattern>(entryPageInfo); });
    stageNode_ = frameNode;
    return stageNode_;
}

RefPtr<FrameNode> StageManager::GetPageById(int32_t pageId)
{
    auto entryPageInfo = AceType::MakeRefPtr<EntryPageInfo>(0, "", "", "");
    auto* stack = ViewStackProcessor::GetInstance();
    int32_t nodeId = (stack == nullptr ? 0 : stack->ClaimNodeId());
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::PAGE_ETS_TAG, nodeId, [entryPageInfo]() { return AceType::MakeRefPtr<PagePattern>(entryPageInfo); });
    stageNode_ = frameNode;
    const auto& children = stageNode_->GetChildren();
    for (const auto& child : children) {
        if (child->GetPageId() == pageId) {
            return DynamicCast<FrameNode>(child);
        }
    }
    return nullptr;
}
} // namespace OHOS::Ace::NG
