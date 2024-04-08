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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_PRIVACY_SENSITIVE_PRIVACY_SENSITIVE_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_PRIVACY_SENSITIVE_PRIVACY_SENSITIVE_MANAGER_H

#include <unordered_set>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/noncopyable.h"
#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {
// PrivacySensitiveManager stores sensitive node to apply style correctly.
class PrivacySensitiveManager : public virtual AceType {
    DECLARE_ACE_TYPE(PrivacySensitiveManager, AceType);

public:
    PrivacySensitiveManager() = default;
    ~PrivacySensitiveManager() override = default;
    void StoreNode(WeakPtr<FrameNode> node)
    {
        sensitiveNodes_.insert(node);
    }

    void RemoveNode(WeakPtr<FrameNode> node)
    {
        if (sensitiveNodes_.empty()) {
            return;
        }
        sensitiveNodes_.erase(node);
    }

    const std::set<WeakPtr<FrameNode>>& GetSensitiveNodes() const
    {
        return sensitiveNodes_;
    }

    void TriggerFrameNodesSensitive(bool sensitive)
    {
        if (sensitiveNodes_.empty()) {
            LOGI("Current no sensitive nodes.");
            return;
        }
        LOGI("Begin to ChangeSensitiveStyle");
        for (auto iter = sensitiveNodes_.begin(); iter != sensitiveNodes_.end();) {
            auto weakNode = *iter;
            auto sensitiveNode = weakNode.Upgrade();
            if (!sensitiveNode) {
                iter = sensitiveNodes_.erase(iter);
                continue;
            }
            sensitiveNode->ChangeSensitiveStyle(sensitive);
            iter++;
        }
    }

private:
    std::set<WeakPtr<FrameNode>> sensitiveNodes_;

    ACE_DISALLOW_COPY_AND_MOVE(PrivacySensitiveManager);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_PRIVACY_SENSITIVE_PRIVACY_SENSITIVE_MANAGER_H
