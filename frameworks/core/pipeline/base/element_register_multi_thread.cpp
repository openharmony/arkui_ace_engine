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

#include "frameworks/core/pipeline/base/element_register_multi_thread.h"

#include "core/components_ng/base/ui_node.h"
#include "frameworks/core/pipeline/base/element_register.h"

namespace OHOS::Ace {
ElementRegisterMultiThread* ElementRegisterMultiThread::GetInstance()
{
    static ElementRegisterMultiThread instance;
    return &instance;
}

bool ElementRegisterMultiThread::AddUINodeMultiThread(const RefPtr<NG::UINode>& node)
{
    if (!node || (node->GetId() == ElementRegister::UndefinedElementId)) {
        return false;
    }
    return AddThreadSafeNode(node);
}

bool ElementRegisterMultiThread::AddThreadSafeNode(const RefPtr<NG::UINode>& node)
{
    std::unique_lock<std::shared_mutex> lock(threadSafeNodeMapMutex_);
    auto result = threadSafeNodeMap_.emplace(node->GetId(), node);
    if (!result.second) {
        LOGE("Duplicate elmtId %{public}d error.", node->GetId());
    }
    return result.second;
}

RefPtr<NG::UINode> ElementRegisterMultiThread::GetThreadSafeNodeById(ElementIdType elementId)
{
    if (elementId == ElementRegister::UndefinedElementId) {
        return nullptr;
    }
    std::shared_lock<std::shared_mutex> lock(threadSafeNodeMapMutex_);
    auto iter = threadSafeNodeMap_.find(elementId);
    return iter == threadSafeNodeMap_.end() ? nullptr :
        AceType::DynamicCast<NG::UINode>(iter->second).Upgrade();
}

bool ElementRegisterMultiThread::RemoveThreadSafeNode(ElementIdType elementId)
{
    if (elementId == ElementRegister::UndefinedElementId) {
        return false;
    }
    std::unique_lock<std::shared_mutex> lock(threadSafeNodeMapMutex_);
    return threadSafeNodeMap_.erase(elementId);
}
} // namespace OHOS::Ace