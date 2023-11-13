/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_UI_EXTENSION_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_UI_EXTENSION_MANAGER_H

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/want/want_wrap.h"
#include "core/common/container.h"

namespace OHOS::Ace::NG {
class UIExtensionPattern;
class UIExtensionManager : public AceType {
    DECLARE_ACE_TYPE(UIExtensionManager, AceType);
public:
    UIExtensionManager() = default;
    ~UIExtensionManager() override = default;

    void RegisterUIExtensionInFocus(const WeakPtr<UIExtensionPattern>& uiExtensionFocused);
    bool OnBackPressed();
    const RefPtr<FrameNode> GetFocusUiExtensionNode();
    bool IsWrapExtensionAbilityId(int32_t elementId);
    std::pair<int32_t, int32_t> UnWrapExtensionAbilityId(int32_t extensionOffset, int32_t elementId);

private:
    WeakPtr<UIExtensionPattern> uiExtensionFocused_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_UI_EXTENSION_MANAGER_H
