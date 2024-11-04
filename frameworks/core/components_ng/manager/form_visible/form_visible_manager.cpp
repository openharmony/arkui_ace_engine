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

#include "core/components_ng/manager/form_visible/form_visible_manager.h"

namespace OHOS::Ace::NG {
void FormVisibleManager::AddFormVisibleChangeNode(const RefPtr<FrameNode>& node,
    const std::function<void(bool)>& callback)
{
    CHECK_NULL_VOID(node);
    onFormVisibleChangeNodeIds_.emplace(node->GetId());
    onFormVisibleChangeEvents_.insert_or_assign(node->GetId(), callback);
}

void FormVisibleManager::RemoveFormVisibleChangeNode(int32_t nodeId)
{
    onFormVisibleChangeNodeIds_.erase(nodeId);
    auto iter = onFormVisibleChangeEvents_.find(nodeId);
    if (iter != onFormVisibleChangeEvents_.end()) {
        onFormVisibleChangeEvents_.erase(iter);
    }
}

void FormVisibleManager::HandleFormVisibleChangeEvent(bool isVisible)
{
    auto nodes = FrameNode::GetNodesById(onFormVisibleChangeNodeIds_);
    for (auto& pair : onFormVisibleChangeEvents_) {
        if (pair.second) {
            pair.second(isVisible);
        }
    }
}

} // namespace OHOS::Ace::NG