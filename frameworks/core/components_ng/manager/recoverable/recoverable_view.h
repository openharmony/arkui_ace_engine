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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_RECOVERABLE_RECOVERABLE_VIEW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_RECOVERABLE_RECOVERABLE_VIEW_H

#include <functional>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"

namespace OHOS::Ace::NG {

class ACE_FORCE_EXPORT RecoverableView : public virtual AceType {
    DECLARE_ACE_TYPE(RecoverableView, AceType);

public:
    RecoverableView() = default;
    ~RecoverableView() override = default;

    // this function must called in OnAttachToFrameNode
    void SetRecoverableViewHostNode(const RefPtr<FrameNode>& host)
    {
        hostNode_ = WeakPtr(host);
    }

    /**
     * The subclass needs to override this method to assign the infomation that needs to be saved to data.
     * The function returns true, indicating that the information needs to be saved, and return false, indicating
     * that the information does not need to be saved.
     */
    virtual bool OnSaveData(std::string& data)
    {
        return false;
    }

    /**
     * this function can only called in OnAttachToMainTree
     * 1. use UINode.InspectorId
     * 2. use FrameNode's custom id
     */
    void GenerateGlobalComponentId(const std::string& customId = "");
    void RegisterRecoverable(const std::string& customId = "");
    void UnregisterRecoverable();
    // must used after RegisterRecoverable
    bool GetRestoreInfo(std::string& restoreInfo);

private:
    bool IsRecoverableNavDestination(const RefPtr<FrameNode>& node);
    const std::string& GetGlobalComponentId() const
    {
        return globalComponentId_;
    }

    int32_t pageId_ = -1;
    int32_t callbackId_ = -1;
    std::string globalComponentId_;
    bool isNavigationType_ = false;
    WeakPtr<FrameNode> hostNode_;

    ACE_DISALLOW_COPY_AND_MOVE(RecoverableView);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_RECOVERABLE_RECOVERABLE_VIEW_H
