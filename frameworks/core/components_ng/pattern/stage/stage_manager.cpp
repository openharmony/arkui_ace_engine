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

#include "base/geometry/ng/size_t.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/components_ng/pattern/stage/stage_pattern.h"
#include "core/components_ng/property/property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {
StageManager::StageManager(const RefPtr<FrameNode>& root) : rootNode_(root)
{
    stagePattern_ = DynamicCast<StagePattern>(rootNode_->GetPattern());
    overlayManager_ = MakeRefPtr<OverlayManager>();
}

bool StageManager::PushPage(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(rootNode_, false);
    CHECK_NULL_RETURN(node, false);

    node->MountToParent(rootNode_);
    auto pagePattern = node->GetPattern<PagePattern>();
    pagePattern->OnShow();
    CHECK_NULL_RETURN(pagePattern, false);
    stagePattern_->currentPageIndex_ = pagePattern->GetPageInfo()->GetPageId();

    // flush layout task.
    if (rootNode_->GetGeometryNode()->GetFrameSize() == SizeF(0.0f, 0.0f)) {
        // in first load case, wait for window size.
        LOGI("waiting for window size");
        return true;
    }
    rootNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    return true;
}

bool StageManager::PopPage()
{
    CHECK_NULL_RETURN(rootNode_, false);
    const auto& children = rootNode_->GetChildren();
    if (children.empty()) {
        LOGE("fail to pop page due to children is null");
        return false;
    }
    auto pageNode = DynamicCast<FrameNode>(children.back());
    CHECK_NULL_RETURN(pageNode, false);
    auto pagePattern = pageNode->GetPattern<PagePattern>();
    CHECK_NULL_RETURN(pagePattern, false);
    pagePattern->OnHide();
    rootNode_->RemoveChild(pageNode);
    rootNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    return true;
}

void StageManager::ShowToast(const std::string& message, int32_t duration, const std::string& bottom,
    bool isRightToLeft)
{
    auto context = NG::PipelineContext::GetCurrentContext();
    if (!context) {
        LOGE("No pipeline context");
        return;
    }
    if (overlayManager_) {
        auto toastId = ElementRegister::GetInstance()->MakeUniqueId();
        LOGI("begin to show toast, toast id is %{public}d, message is %{public}s", toastId, message.c_str());
        overlayManager_->ShowToast(rootNode_, toastId, message, bottom, isRightToLeft);
        context->GetTaskExecutor()->PostDelayedTask([overlayManager = overlayManager_, toastId] {
            LOGI("begin pop toast, id is %{public}d", toastId);
            if (!overlayManager) {
                LOGE("No Overlay manager");
                return;
            }
            overlayManager->PopToast(toastId);
        }, TaskExecutor::TaskType::UI, duration);
    }
}

} // namespace OHOS::Ace::NG
