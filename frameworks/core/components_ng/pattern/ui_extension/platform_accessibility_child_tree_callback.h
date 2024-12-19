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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PLATFORM_ACCESSIBILITY_CHILD_TREE_CALLBACK_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PLATFORM_ACCESSIBILITY_CHILD_TREE_CALLBACK_H

#include "frameworks/core/components_ng/pattern/ui_extension/platform_accessibility_base.h"

namespace OHOS::Ace::NG {

class PlatformAccessibilityChildTreeCallback : public AccessibilityChildTreeCallback {
public:
    PlatformAccessibilityChildTreeCallback(
        const WeakPtr<PlatformAccessibilityBase> &weakPattern, int64_t accessibilityId)
        : AccessibilityChildTreeCallback(accessibilityId), weakPattern_(weakPattern)
    {}

    ~PlatformAccessibilityChildTreeCallback() override = default;

    bool OnRegister(uint32_t windowId, int32_t treeId) override
    {
        auto pattern = weakPattern_.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        if (isReg_) {
            return true;
        }
        pattern->OnAccessibilityChildTreeRegister(windowId, treeId, GetAccessibilityId());
        isReg_ = true;
        return true;
    }

    bool OnDeregister() override
    {
        auto pattern = weakPattern_.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        if (!isReg_) {
            return true;
        }
        pattern->OnAccessibilityChildTreeDeregister();
        isReg_ = false;
        return true;
    }

    bool OnSetChildTree(int32_t childWindowId, int32_t childTreeId) override
    {
        auto pattern = weakPattern_.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        pattern->OnSetAccessibilityChildTree(childWindowId, childTreeId);
        return true;
    }

    bool OnDumpChildInfo(const std::vector<std::string>& params, std::vector<std::string>& info) override
    {
        auto pattern = weakPattern_.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        pattern->OnAccessibilityDumpChildInfo(params, info);
        return true;
    }

    void OnClearRegisterFlag() override
    {
        isReg_ = false;
    }

private:
    bool isReg_ = false;
    WeakPtr<PlatformAccessibilityBase> weakPattern_;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PLATFORM_ACCESSIBILITY_CHILD_TREE_CALLBACK_H