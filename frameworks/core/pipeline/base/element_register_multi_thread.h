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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_ELEMENT_REGISTER_MULTI_THREAD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_ELEMENT_REGISTER_MULTI_THREAD_H

#include <shared_mutex>
#include <unordered_map>
#include "base/memory/referenced.h"
#include "core/components_ng/base/ui_node.h"
#include "frameworks/base/memory/ace_type.h"

namespace OHOS::Ace {
using ElementIdType = int32_t;

class ACE_EXPORT ElementRegisterMultiThread {
public:
    ACE_FORCE_EXPORT static ElementRegisterMultiThread* GetInstance();
    bool AddUINodeMultiThread(const RefPtr<NG::UINode>& node);
    RefPtr<NG::UINode> GetThreadSafeNodeById(ElementIdType elementId);
    bool RemoveThreadSafeNode(ElementIdType elementId);
private:
    // private constructor
    ElementRegisterMultiThread() = default;
    bool AddThreadSafeNode(const RefPtr<NG::UINode>& node);

    std::shared_mutex threadSafeNodeMapMutex_;
    std::unordered_map<ElementIdType, WeakPtr<AceType>> threadSafeNodeMap_;

    ACE_DISALLOW_COPY_AND_MOVE(ElementRegisterMultiThread);
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_ELEMENT_REGISTER_MULTI_THREAD_H