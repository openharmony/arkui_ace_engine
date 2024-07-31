/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/common/accessibility/accessibility_node_manager.h"

namespace OHOS::Ace::Framework {
class FakeAccessibilityManager : public AccessibilityNodeManager {
    void SearchElementInfoByAccessibilityIdNG(int64_t elementId, int32_t mode,
        std::list<Accessibility::AccessibilityElementInfo>& infos, const RefPtr<PipelineBase>& context,
        int64_t uiExtensionOffset) override;
    void SearchElementInfosByTextNG(int64_t elementId, const std::string& text,
        std::list<Accessibility::AccessibilityElementInfo>& infos, const RefPtr<PipelineBase>& context,
        const int64_t uiExtensionOffset = 0) override;
    void FindFocusedElementInfoNG(int64_t elementId, int32_t focusType,
        Accessibility::AccessibilityElementInfo& info, const RefPtr<PipelineBase>& context,
        const int64_t uiExtensionOffset = 0) override;
    void FocusMoveSearchNG(int64_t elementId, int32_t direction, Accessibility::AccessibilityElementInfo& info,
        const RefPtr<PipelineBase>& context, const int64_t uiExtensionOffset = 0) override;
    bool ExecuteExtensionActionNG(int64_t elementId, const std::map<std::string, std::string>& actionArguments,
        int32_t action, const RefPtr<PipelineBase>& context, int64_t uiExtensionOffset) override;
};

void FakeAccessibilityManager::SearchElementInfoByAccessibilityIdNG(
    int64_t elementId,
    int32_t mode,
    std::list<AccessibilityElementInfo>& infos,
    const RefPtr<PipelineBase>& context,
    int64_t uiExtensionOffset
)
{
}

void FakeAccessibilityManager::SearchElementInfosByTextNG(
    int64_t elementId,
    const std::string& text,
    std::list<Accessibility::AccessibilityElementInfo>& infos,
    const RefPtr<PipelineBase>& context,
    const int64_t uiExtensionOffset
)
{
}

void FakeAccessibilityManager::FindFocusedElementInfoNG(
    int64_t elementId,
    int32_t focusType,
    Accessibility::AccessibilityElementInfo& info,
    const RefPtr<PipelineBase>& context,
    const int64_t uiExtensionOffset
)
{
}

void FakeAccessibilityManager::FocusMoveSearchNG(
    int64_t elementId,
    int32_t direction,
    Accessibility::AccessibilityElementInfo& info,
    const RefPtr<PipelineBase>& context,
    const int64_t uiExtensionOffset
)
{
}

bool FakeAccessibilityManager::ExecuteExtensionActionNG(
    int64_t elementId,
    const std::map<std::string, std::string>& actionArguments,
    int32_t action,
    const RefPtr<PipelineBase>& context,
    int64_t uiExtensionOffset
)
{
    return false;
}

RefPtr<AccessibilityNodeManager> AccessibilityNodeManager::Create()
{
    return AceType::MakeRefPtr<FakeAccessibilityManager>();
}
} // namespace OHOS::Ace::Framework
