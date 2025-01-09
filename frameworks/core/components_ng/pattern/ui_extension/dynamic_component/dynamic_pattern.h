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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_DYNAMIC_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_DYNAMIC_PATTERN_H

#include "core/common/dynamic_component_renderer.h"
#include "core/components_ng/pattern/ui_extension/accessibility_session_adapter_isolated_component.h"
#include "core/components_ng/pattern/ui_extension/platform_pattern.h"
#include "core/components_ng/pattern/ui_extension/platform_accessibility_child_tree_callback.h"

namespace OHOS::Ace::NG {

struct DynamicDumpInfo {
    int64_t createLimitedWorkerTime = 0;
};

class DynamicPattern : public PlatformPattern, public PlatformAccessibilityBase {
    DECLARE_ACE_TYPE(DynamicPattern, PlatformPattern, PlatformAccessibilityBase);

public:
    DynamicPattern();
    ~DynamicPattern() override;

    void InitializeDynamicComponent(const std::string& hapPath,
        const std::string& abcPath, const std::string& entryPoint, void* runtime);
    bool OnDirtyLayoutWrapperSwap(
        const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    void OnDetachFromFrameNode(FrameNode* frameNode) override;
    int64_t WrapExtensionAbilityId(int64_t extensionOffset, int64_t abilityId) override;
    RefPtr<AccessibilitySessionAdapter> GetAccessibilitySessionAdapter() override;
    void SetAdaptiveWidth(bool state);
    void SetAdaptiveHeight(bool state);
    void OnAttachContext(PipelineContext *context) override;
    void OnDetachContext(PipelineContext *context) override;
    void DumpDynamicRenderer(int32_t depth, bool hasJson);

    void DumpInfo() override;
    void DumpInfo(std::unique_ptr<JsonValue>& json) override;
    void DumpSimplifyInfo(std::unique_ptr<JsonValue>& json) override {}
    void FireOnErrorCallbackOnUI(
        int32_t code, const std::string& name, const std::string& msg);

    void OnAccessibilityChildTreeRegister(uint32_t windowId, int32_t treeId, int64_t accessibilityId) const override;
    void OnAccessibilityChildTreeDeregister() const override;
    void OnSetAccessibilityChildTree(int32_t childWindowId, int32_t childTreeId) const override;
    void OnAccessibilityDumpChildInfo(
        const std::vector<std::string>& params, std::vector<std::string>& info) const override;

    void InitializeAccessibility();
    void ResetAccessibilityChildTreeCallback();

    void SetBackgroundTransparent(bool backgroundTransparent);

private:
    void InitializeRender(void* runtime);

    void DispatchPointerEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent) override;
    void DispatchFocusActiveEvent(bool isFocusActive) override;
    bool HandleKeyEvent(const KeyEvent& event) override;
    void HandleFocusEvent() override;
    void HandleBlurEvent() override;

    void OnAttachToFrameNode() override;
    void RegisterPipelineEvent(int32_t instanceId);
    void UnRegisterPipelineEvent(int32_t instanceId);

    RefPtr<DynamicComponentRenderer> dynamicComponentRenderer_;
    bool adaptiveWidth_ = false;
    bool adaptiveHeight_ = false;
    bool backgroundTransparent_ = true;
    IsolatedInfo curDynamicInfo_;
    DynamicDumpInfo dynamicDumpInfo_;
    int32_t uiExtensionId_ = 0;
    RefPtr<AccessibilitySessionAdapterIsolatedComponent> accessibilitySessionAdapter_;
    std::shared_ptr<AccessibilityChildTreeCallback> accessibilityChildTreeCallback_ = nullptr;

    static int32_t dynamicGenerator_; // only run on JS thread, and do not require mutex
    ACE_DISALLOW_COPY_AND_MOVE(DynamicPattern);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_DYNAMIC_PATTERN_H
