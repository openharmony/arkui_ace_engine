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

#include "core/components_ng/pattern/stage/stage_manager.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/page/page_pattern.h"
#include "core/components_ng/pattern/stage/stage_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {

StageManager::StageManager(const RefPtr<FrameNode>& root) : rootNode_(root)
{
    stagePattern_ = DynamicCast<StagePattern>(rootNode_->GetPattern());
}

void StageManager::PushPage(const RefPtr<ElementNode>& node)
{
    if (!rootNode_) {
        LOGE("the root node is nullptr");
        return;
    }

    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, MakeRefPtr<PagePattern>());
    pageNode->SetHostPageId(node->GetPageId());
    pageNode->SetHostRootId(rootNode_->GetRootId());
    node->MountToParent(pageNode);
    pageNode->MountToParent(rootNode_);
    // TODO: change page index
    stagePattern_->currentPageIndex_ = 0;
    UiTaskScheduler::GetInstance()->FlushTask();
}

} // namespace OHOS::Ace::NG
