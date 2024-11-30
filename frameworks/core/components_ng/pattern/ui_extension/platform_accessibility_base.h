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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_PLATFORM_ACCESSIBILITY_BASE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_PLATFORM_ACCESSIBILITY_BASE_H

#include "base/memory/ace_type.h"

namespace OHOS::Ace::NG {

class PlatformAccessibilityBase : public virtual AceType {
    DECLARE_ACE_TYPE(PlatformAccessibilityBase, AceType);

public:
    PlatformAccessibilityBase() = default;
    ~PlatformAccessibilityBase() override = default;
    virtual void OnAccessibilityChildTreeRegister(
        uint32_t windowId, int32_t treeId, int64_t accessibilityId) const = 0;
    virtual void OnAccessibilityChildTreeDeregister() const = 0;
    virtual void OnSetAccessibilityChildTree(int32_t childWindowId, int32_t childTreeId) const = 0;
    virtual void OnAccessibilityDumpChildInfo(
        const std::vector<std::string>& params, std::vector<std::string>& info) const = 0;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_PLATFORM_ACCESSIBILITY_BASE_H