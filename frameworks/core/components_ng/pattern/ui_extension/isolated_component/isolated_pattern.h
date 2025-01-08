/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_ISOLATED_COMPONENT_ISOLATED_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_ISOLATED_COMPONENT_ISOLATED_PATTERN_H

#include "core/common/dynamic_component_renderer.h"
#include "core/components_ng/pattern/ui_extension/accessibility_session_adapter_isolated_component.h"
#include "core/components_ng/pattern/ui_extension/platform_pattern.h"

namespace OHOS::Ace::NG {

struct IsolatedDumpInfo {
    int64_t createLimitedWorkerTime = 0;
};

class IsolatedPattern : public PlatformPattern {
    DECLARE_ACE_TYPE(IsolatedPattern, PlatformPattern);

public:
    IsolatedPattern();
    ~IsolatedPattern() override;

    void InitializeIsolatedComponent(
        const RefPtr<OHOS::Ace::WantWrap>& wantWrap, void* runtime);
    bool OnDirtyLayoutWrapperSwap(
        const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    void OnDetachFromFrameNode(FrameNode* frameNode) override;
    int32_t GetUiExtensionId() override;
    int64_t WrapExtensionAbilityId(int64_t extensionOffset, int64_t abilityId) override;
    RefPtr<AccessibilitySessionAdapter> GetAccessibilitySessionAdapter() override;
    void SetAdaptiveWidth(bool state);
    void SetAdaptiveHeight(bool state);

    void SearchExtensionElementInfoByAccessibilityId(
        int64_t elementId, int32_t mode, int64_t baseParent,
        std::list<Accessibility::AccessibilityElementInfo>& output) override;
    void SearchElementInfosByText(int64_t elementId, const std::string& text, int64_t baseParent,
        std::list<Accessibility::AccessibilityElementInfo>& output) override;
    void FindFocusedElementInfo(int64_t elementId, int32_t focusType, int64_t baseParent,
        Accessibility::AccessibilityElementInfo& output) override;
    void FocusMoveSearch(int64_t elementId, int32_t direction, int64_t baseParent,
        Accessibility::AccessibilityElementInfo& output) override;
    bool TransferExecuteAction(
        int64_t elementId, const std::map<std::string, std::string>& actionArguments,
        int32_t action, int64_t offset) override;

    void DumpInfo() override;
    void DumpInfo(std::unique_ptr<JsonValue>& json) override;
    void DumpSimplifyInfo(std::unique_ptr<JsonValue>& json) override {}
    void FireOnErrorCallbackOnUI(
        int32_t code, const std::string& name, const std::string& msg);

private:
    void InitializeRender(void* runtime);

    void DispatchPointerEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent) override;
    void DispatchFocusActiveEvent(bool isFocusActive) override;
    bool HandleKeyEvent(const KeyEvent& event) override;
    void HandleFocusEvent() override;
    void HandleBlurEvent() override;

    void OnAttachToFrameNode() override;

    RefPtr<DynamicComponentRenderer> dynamicComponentRenderer_;
    bool adaptiveWidth_ = true;
    bool adaptiveHeight_ = true;
    IsolatedInfo curIsolatedInfo_;
    IsolatedDumpInfo isolatedDumpInfo_;
    int32_t uiExtensionId_ = 0;
    RefPtr<AccessibilitySessionAdapterIsolatedComponent> accessibilitySessionAdapter_;

    static int32_t isolatedIdGenerator_; // only run on JS thread, and do not require mutex
    ACE_DISALLOW_COPY_AND_MOVE(IsolatedPattern);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_ISOLATED_PATTERN_H
