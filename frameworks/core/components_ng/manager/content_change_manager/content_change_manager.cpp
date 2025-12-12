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

#include "content_change_manager.h"
#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {
void ContentChangeManager::StartContentChangeReport(const ContentChangeConfig& config)
{
    currentContentChangeConfig_ = config;
    for (auto& weak : onContentChangeNodes_) {
        auto node = weak.Upgrade();
        if (!node) {
            continue;
        }
        node->OnContentChangeRegister(config);
    }
}

void ContentChangeManager::StopContentChangeReport()
{
    currentContentChangeConfig_.reset();
    for (auto& weak : onContentChangeNodes_) {
        auto node = weak.Upgrade();
        if (!node) {
            continue;
        }
        node->OnContentChangeUnregister();
    }
}

void ContentChangeManager::AddOnContentChangeNode(WeakPtr<FrameNode> node)
{
    onContentChangeNodes_.emplace(node);
    if (IsContentChangeDetectEnable()) {
        auto nodePtr = node.Upgrade();
        CHECK_NULL_VOID(nodePtr);
        nodePtr->OnContentChangeRegister(currentContentChangeConfig_.value());
    }
}

void ContentChangeManager::RemoveOnContentChangeNode(WeakPtr<FrameNode> node)
{
    onContentChangeNodes_.erase(node);
}
} // namespace OHOS::Ace::NG
