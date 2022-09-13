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
StageManager::StageManager(const RefPtr<FrameNode>& stage) : stageNode_(stage)
{
    stagePattern_ = DynamicCast<StagePattern>(stageNode_->GetPattern());
}

bool StageManager::PushPage(const RefPtr<FrameNode>& node, bool needHideLast)
{
    CHECK_NULL_RETURN(stageNode_, false);
    CHECK_NULL_RETURN(node, false);

    const auto& children = stageNode_->GetChildren();
    if (!children.empty() && needHideLast) {
        FirePageHide(children.back());
    }

    node->MountToParent(stageNode_);
    FirePageShow(node);

    auto pagePattern = node->GetPattern<PagePattern>();
    CHECK_NULL_RETURN(pagePattern, false);
    stagePattern_->currentPageIndex_ = pagePattern->GetPageInfo()->GetPageId();

    // flush layout task.
    if (stageNode_->GetGeometryNode()->GetFrameSize() == SizeF(0.0f, 0.0f)) {
        // in first load case, wait for window size.
        LOGI("waiting for window size");
        return true;
    }
    stageNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    return true;
}

bool StageManager::PopPage(bool needShowNext)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    CHECK_NULL_RETURN(stageNode_, false);
    const auto& children = stageNode_->GetChildren();
    if (children.empty()) {
        LOGE("fail to pop page due to children is null");
        return false;
    }
    auto pageNode = children.back();
    FirePageHide(pageNode);
    stageNode_->RemoveChild(pageNode);

    if (needShowNext) {
        const auto& newPageNode = children.back();
        FirePageShow(newPageNode);
    }
    stageNode_->RebuildRenderContextTree();
    pipeline->RequestFrame();
    return true;
}

bool StageManager::PopPageToIndex(int32_t index, bool needShowNext)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    CHECK_NULL_RETURN(stageNode_, false);
    const auto& children = stageNode_->GetChildren();
    if (children.empty()) {
        LOGE("fail to pop page due to children is null");
        return false;
    }
    int32_t popSize = static_cast<int32_t>(children.size()) - index - 1;
    if (popSize < 0) {
        LOGE("fail to pop page due to index is out of range");
        return false;
    }
    if (popSize == 0) {
        LOGD("already here");
        return true;
    }

    for (int32_t current = 0; current < popSize; ++current) {
        auto pageNode = children.back();
        FirePageHide(pageNode);
        stageNode_->RemoveChild(pageNode);
    }

    if (needShowNext) {
        const auto& newPageNode = children.back();
        FirePageShow(newPageNode);
    }

    stageNode_->RebuildRenderContextTree();
    pipeline->RequestFrame();
    return true;
}

bool StageManager::CleanPageStack()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    CHECK_NULL_RETURN(stageNode_, false);
    const auto& children = stageNode_->GetChildren();
    if (children.size() <= 1) {
        LOGE("fail to clean page stack due to children size is illegal");
        return false;
    }
    auto popSize = static_cast<int32_t>(children.size() - 1);
    for (int32_t count = 1; count <= popSize; ++count) {
        auto pageNode = children.back();
        stageNode_->RemoveChild(pageNode);
    }
    const auto& newPageNode = children.back();
    FirePageShow(newPageNode);

    stageNode_->RebuildRenderContextTree();
    pipeline->RequestFrame();
    return true;
}

bool StageManager::MovePageToFront(const RefPtr<FrameNode>& node, bool needHideLast)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    CHECK_NULL_RETURN(stageNode_, false);
    const auto& children = stageNode_->GetChildren();
    if (children.empty()) {
        LOGE("child is empty");
        return false;
    }
    const auto& lastPage = children.back();
    if (lastPage == node) {
        LOGD("page already on the top");
        return true;
    }
    if (needHideLast) {
        FirePageHide(lastPage);
    }
    node->MovePosition(static_cast<int32_t>(stageNode_->GetChildren().size() - 1));
    FirePageShow(node);

    stageNode_->RebuildRenderContextTree();
    pipeline->RequestFrame();
    return true;
}

void StageManager::FirePageHide(const RefPtr<UINode>& node)
{
    auto pageNode = DynamicCast<FrameNode>(node);
    CHECK_NULL_VOID(pageNode);
    auto pagePattern = pageNode->GetPattern<PagePattern>();
    CHECK_NULL_VOID(pagePattern);
    pagePattern->OnHide();
}

void StageManager::FirePageShow(const RefPtr<UINode>& node)
{
    auto pageNode = DynamicCast<FrameNode>(node);
    CHECK_NULL_VOID(pageNode);
    auto pagePattern = pageNode->GetPattern<PagePattern>();
    CHECK_NULL_VOID(pagePattern);
    pagePattern->OnShow();
}

RefPtr<FrameNode> StageManager::GetLastPage()
{
    CHECK_NULL_RETURN(stageNode_, nullptr);
    const auto& children = stageNode_->GetChildren();
    if (children.empty()) {
        LOGE("fail to return page due to children is null");
        return nullptr;
    }
    return DynamicCast<FrameNode>(children.back());
}

} // namespace OHOS::Ace::NG
