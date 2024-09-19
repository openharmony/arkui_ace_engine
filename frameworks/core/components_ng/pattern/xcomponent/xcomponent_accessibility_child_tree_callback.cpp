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

#include "core/components_ng/pattern/xcomponent/xcomponent_accessibility_child_tree_callback.h"

#include "base/log/log_wrapper.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"

namespace OHOS::Ace::NG {
bool XComponentAccessibilityChildTreeCallback::OnRegister(
    uint32_t windowId, int32_t treeId)
{
    auto pattern = weakPattern_.Upgrade();
    if (pattern == nullptr) {
        return false;
    }

    if (isReg_) {
        return true;
    }

    if (!pattern->OnAccessibilityChildTreeRegister(windowId, treeId)) {
        return false;
    }

    pattern->SetAccessibilityState(true);
    isReg_ = true;
    return true;
}

bool XComponentAccessibilityChildTreeCallback::OnDeregister()
{
    auto pattern = weakPattern_.Upgrade();
    if (pattern == nullptr) {
        return false;
    }

    if (!isReg_) {
        return true;
    }

    if (!pattern->OnAccessibilityChildTreeDeregister()) {
        return false;
    }

    pattern->SetAccessibilityState(false);
    isReg_ = false;
    return true;
}

bool XComponentAccessibilityChildTreeCallback::OnSetChildTree(
    int32_t childWindowId, int32_t childTreeId)
{
    auto pattern = weakPattern_.Upgrade();
    if (pattern == nullptr) {
        return false;
    }

    pattern->OnSetAccessibilityChildTree(childWindowId, childTreeId);
    return true;
}

bool XComponentAccessibilityChildTreeCallback::OnDumpChildInfo(
    const std::vector<std::string>& params, std::vector<std::string>& info)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, true);
    auto host = pattern->GetHost();
    CHECK_NULL_RETURN(host, true);
    auto pipeline = host->GetContext();
    CHECK_NULL_RETURN(pipeline, true);
    auto accessibilityManager = pipeline->GetAccessibilityManager();
    CHECK_NULL_RETURN(accessibilityManager, true);
    return accessibilityManager->OnDumpChildInfoForThird(
        host->GetAccessibilityId(), params, info);
}

void XComponentAccessibilityChildTreeCallback::OnClearRegisterFlag()
{
    auto pattern = weakPattern_.Upgrade();
    if (pattern == nullptr) {
        return;
    }

    isReg_ = false;
}
} // namespace OHOS::Ace::NG
