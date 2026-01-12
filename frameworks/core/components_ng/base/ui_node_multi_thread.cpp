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

#include "core/components_ng/base/ui_node.h"

#include "core/common/multi_thread_build_manager.h"
#include "frameworks/core/pipeline/base/element_register.h"
#include "frameworks/core/pipeline/base/element_register_multi_thread.h"

namespace OHOS::Ace::NG {
void UINode::MarkNodeTreeNotFree()
{
    if (!IsFree()) {
        return;
    }
    auto root = Claim(this);
    auto parent = GetParent();
    while (parent && (parent->IsFree() || !IsBuildByUser())) {
        root = parent;
        parent = parent->GetParent();
    }
    CHECK_NULL_VOID(root);
    root->MarkNodeNotFree();
}

void UINode::MarkNodeNotFree()
{
    if (!IsFree() && IsBuildByUser()) {
        return;
    }
    for (const auto& child : GetChildren()) {
        child->MarkNodeNotFree();
    }
    if (IsFree()) {
        SetIsFree(false);
        ElementRegister::GetInstance()->AddUINode(Claim(this));
        ExecuteAfterAttachMainTreeTasks();
    }
}

bool UINode::CheckThreadSafeNodeTree()
{
    for (const auto& child : GetChildren()) {
        if (!child->IsThreadSafeNode() && child->IsBuildByUser()) {
            // Remind developers that it is unsafe to operate node trees containing attached nodes on non UI threads.
            TAG_LOGI(AceLogTag::ACE_NATIVE_NODE,
                "CheckIsFreeNodeTree failed. node tree contains attached node: %{public}d", child->GetId());
            return false;
        }
        if (!child->CheckThreadSafeNodeTree()) {
            return false;
        }
    }
    return true;
}

void UINode::MarkNodeTreeFree(bool isNeedMarkNodeTreeFree)
{
    if (IsFree() || !IsThreadSafeNode()) {
        return;
    }
    if (!isNeedMarkNodeTreeFree && !MultiThreadBuildManager::IsNeedMarkNodeTreeFree()) {
        return;
    }
    auto root = Claim(this);
    auto parent = GetParent();
    while (parent) {
        if (!parent->IsThreadSafeNode() && IsBuildByUser()) {
            return;
        }
        root = parent;
        parent = parent->GetParent();
    }
    CHECK_NULL_VOID(root);
    if (!root->CheckThreadSafeNodeTree()) {
        return;
    }
    root->MarkNodeFree();
}

void UINode::MarkNodeFree()
{
    if (!IsFree() && IsThreadSafeNode()) {
        ElementRegister::GetInstance()->RemoveItemSilently(GetId());
        SetIsFree(true);
    }
    for (const auto& child : GetChildren()) {
        child->MarkNodeFree();
    }
}

void UINode::PostAfterAttachMainTreeTask(std::function<void()>&& task)
{
    if (isRunningPendingUnsafeTask_) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE,
            "PostPendingFreeNodeTask failed, node: %{public}d is running pending task", GetId());
        return;
    }
    if (!IsFree()) {
        TAG_LOGW(AceLogTag::ACE_NATIVE_NODE,
            "PostPendingFreeNodeTask failed, node: %{public}d is not free", GetId());
        return;
    }
    afterAttachMainTreeTasks_.emplace_back(std::move(task));
}

void UINode::ExecuteAfterAttachMainTreeTasks()
{
    isRunningPendingUnsafeTask_ = true;
    decltype(afterAttachMainTreeTasks_) pendingUnsafeTasks(std::move(afterAttachMainTreeTasks_));
    for (const auto& task : pendingUnsafeTasks) {
        if (task) {
            task();
        }
    }
    isRunningPendingUnsafeTask_ = false;
}
} // namespace OHOS::Ace::NG