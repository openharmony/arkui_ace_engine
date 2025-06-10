/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "core/components_ng/manager/memory/memory_manager.h"

#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "frameworks/core/common/container.h"

namespace {
constexpr int32_t BACKGROUND_RECYCLE_WAIT_TIME_MS = 500;
constexpr int32_t RECYCLE_PAGE_IMAGE_NUM = 20;
}
namespace OHOS::Ace::NG {
MemoryManager::MemoryManager()
{
    isTrimMemWork_ = false;
}

void MemoryManager::AddRecyclePageNode(const RefPtr<FrameNode>& node)
{
    if (!isTrimMemWork_) {
        return;
    }
    CHECK_NULL_VOID(node);
    auto weak = WeakClaim(RawPtr(node));
    if (std::find(pageNodes_.begin(), pageNodes_.end(), weak) == pageNodes_.end()) {
        pageNodes_.emplace_back(weak);
    }
}

void MemoryManager::RemoveRecyclePageNode(int32_t nodeId)
{
    if (!isTrimMemWork_ || pageNodes_.empty()) {
        return;
    }
    pageNodes_.remove_if([nodeId](const WeakPtr<FrameNode>& node) {
        return !node.Upgrade() || nodeId == node.Upgrade()->GetId();
    });
}

void MemoryManager::RecycleImage(const RefPtr<UINode>& node, int& recycleNum)
{
    CHECK_NULL_VOID(node);
    const auto& children = node->GetChildren(true);
    if (children.empty() || (recycleNum <= 0)) {
        return;
    }
    for (const auto& child : children) {
        auto childNode = AceType::DynamicCast<FrameNode>(child);
        if (childNode && (childNode->GetTag() == V2::IMAGE_ETS_TAG)) {
            auto imagePattern = childNode->GetPattern<ImagePattern>();
            if ((!imagePattern) || (!imagePattern->RecycleImageData())) {
                continue;
            }
            recycleNum--;
            if (recycleNum <= 0) {
                return;
            }
        } else {
            RecycleImage(child, recycleNum);
        }
    }
}

void MemoryManager::RecycleImageByPage(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_VOID(node);
    node->SetTrimMemRecycle(true);
    int32_t recycleNum = RECYCLE_PAGE_IMAGE_NUM;
    RecycleImage(node, recycleNum);
}

void MemoryManager::RebuildImageByPage(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_VOID(node);
    if (!isTrimMemWork_ || !node->IsTrimMemRecycle()) {
        return;
    }
    ACE_SCOPED_TRACE("memory manager rebuild image by page");
    node->SetTrimMemRecycle(false);
    RebuildImage(node);
}

void MemoryManager::RebuildImage(const RefPtr<UINode>& node)
{
    CHECK_NULL_VOID(node);
    const auto& children = node->GetChildren(true);
    if (children.empty()) {
        return;
    }
    for (const auto& child : children) {
        auto childNode = AceType::DynamicCast<FrameNode>(child);
        if (childNode && childNode->GetTag() == V2::IMAGE_ETS_TAG) {
            auto imagePattern = childNode->GetPattern<ImagePattern>();
            if ((!imagePattern) || (!childNode->IsTrimMemRecycle())) {
                continue;
            }
            TAG_LOGI(AceLogTag::ACE_IMAGE, "start rebuild image: %{public}d", childNode->GetId());
            imagePattern->LoadImageDataIfNeed();
            childNode->SetTrimMemRecycle(false);
        } else {
            RebuildImage(child);
        }
    }
}

void MemoryManager::PostMemRecycleTask()
{
    auto container = Container::Current();
    if (!isTrimMemWork_ || (container && container->IsSceneBoardWindow())) {
        return;
    }
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto taskExecutor = pipeline->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostDelayedTask([weak = WeakClaim(this)] {
            auto memMgr = weak.Upgrade();
            CHECK_NULL_VOID(memMgr);
            memMgr->TrimMemRecycle();
        },
        TaskExecutor::TaskType::UI,
        BACKGROUND_RECYCLE_WAIT_TIME_MS,
        "TrimMemManagerToRecycleImage");
}

void MemoryManager::TrimMemRecycle()
{
    if (pageNodes_.empty()) {
        return;
    }
    TAG_LOGI(AceLogTag::ACE_IMAGE, "start recycle image from page");
    for (auto iter = pageNodes_.begin(); iter != pageNodes_.end(); ++iter) {
        auto frameNode = iter->Upgrade();
        if (!frameNode) {
            iter = pageNodes_.erase(iter);
            continue;
        }
        if (frameNode->IsVisible() || frameNode->IsTrimMemRecycle()) {
            continue;
        }
        RecycleImageByPage(frameNode);
    }
}

void MemoryManager::Reset()
{
    if (!isTrimMemWork_) {
        return;
    }
    pageNodes_.clear();
}
} // namespace OHOS::Ace::NG
