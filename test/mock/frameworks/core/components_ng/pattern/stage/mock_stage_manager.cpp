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

#include "core/components_ng/pattern/stage/stage_manager.h"

namespace OHOS::Ace::NG {
StageManager::StageManager(const RefPtr<FrameNode>& stage) : stageNode_(stage) {}

bool StageManager::PushPage(const RefPtr<FrameNode>& node, bool needHideLast, bool needTransition,
    const std::function<bool()>&& pushIntentPageCallback)
{
    (void)needHideLast;
    (void)needTransition;
    (void)pushIntentPageCallback;
    if (!stageNode_ || !node) {
        return false;
    }
    stageNode_->AddChild(node);
    return true;
}

bool StageManager::InsertPage(const RefPtr<FrameNode>& node, bool bellowTopOrBottom)
{
    (void)bellowTopOrBottom;
    if (!stageNode_ || !node) {
        return false;
    }
    stageNode_->AddChild(node);
    return true;
}

bool StageManager::PopPage(const RefPtr<FrameNode>& inPageNode, bool needShowNext, bool needTransition)
{
    (void)needShowNext;
    (void)needTransition;
    if (!stageNode_ || !inPageNode) {
        return false;
    }
    stageNode_->RemoveChild(inPageNode);
    return true;
}

bool StageManager::PopPageToIndex(int32_t index, bool needShowNext, bool needTransition)
{
    (void)needShowNext;
    (void)needTransition;
    if (!stageNode_) {
        return false;
    }
    const auto children = stageNode_->GetChildren();
    int32_t size = static_cast<int32_t>(children.size());
    if (index < 0 || index >= size) {
        return false;
    }
    int32_t current = 0;
    for (auto it = children.begin(); it != children.end(); ++it, ++current) {
        if (current > index) {
            stageNode_->RemoveChild(*it);
        }
    }
    return true;
}

bool StageManager::CleanPageStack()
{
    if (!stageNode_) {
        return false;
    }
    auto children = stageNode_->GetChildren();
    for (const auto& child : children) {
        stageNode_->RemoveChild(child);
    }
    return true;
}

bool StageManager::MovePageToFront(const RefPtr<FrameNode>& node, bool needHideLast, bool needTransition)
{
    (void)needHideLast;
    (void)needTransition;
    if (!stageNode_ || !node) {
        return false;
    }
    stageNode_->RemoveChild(node);
    stageNode_->AddChild(node);
    return true;
}

void StageManager::StartTransition(const RefPtr<FrameNode>& srcPage, const RefPtr<FrameNode>& destPage, RouteType type)
{
    (void)srcPage;
    (void)destPage;
    (void)type;
}

RefPtr<FrameNode> StageManager::GetLastPage() const
{
    if (!stageNode_) {
        return nullptr;
    }
    const auto& children = stageNode_->GetChildren();
    if (children.empty()) {
        return nullptr;
    }
    return AceType::DynamicCast<FrameNode>(children.back());
}

RefPtr<FrameNode> StageManager::GetLastPageWithTransition() const
{
    return GetLastPage();
}

RefPtr<FrameNode> StageManager::GetPrevPageWithTransition() const
{
    if (!stageNode_) {
        return nullptr;
    }
    const auto& children = stageNode_->GetChildren();
    if (children.size() < 2) {
        return nullptr;
    }
    auto iter = children.end();
    --iter;
    --iter;
    return AceType::DynamicCast<FrameNode>(*iter);
}

void StageManager::SyncPageSafeArea(bool keyboardSafeArea)
{
    (void)keyboardSafeArea;
}

bool StageManager::CheckPageFocus()
{
    return false;
}

std::vector<RefPtr<FrameNode>> StageManager::GetTopPagesWithTransition() const
{
    std::vector<RefPtr<FrameNode>> pages;
    auto last = GetLastPage();
    if (last) {
        pages.emplace_back(last);
    }
    return pages;
}

void StageManager::ReloadStage() {}
} // namespace OHOS::Ace::NG
