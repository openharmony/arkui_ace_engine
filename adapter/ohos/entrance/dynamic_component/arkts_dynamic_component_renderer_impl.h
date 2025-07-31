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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_DYNAMIC_COMPONENT_ARKTS_DYNAMIC_COMPONENT_RENDERER_H
#define FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_DYNAMIC_COMPONENT_ARKTS_DYNAMIC_COMPONENT_RENDERER_H

#include <cstdint>

#include "arkts_dynamic_uicontent_impl.h"

#include "adapter/ohos/entrance/ace_container.h"
#include "base/memory/ace_type.h"
#include "base/thread/task_executor.h"
#include "core/common/dynamic_component_renderer.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/window_scene/scene/system_window_scene.h"

namespace OHOS::Ace::NG {

class ArktsDynamicComponentRendererImpl : public DynamicComponentRenderer {
    DECLARE_ACE_TYPE(ArktsDynamicComponentRendererImpl, DynamicComponentRenderer);

public:
    ArktsDynamicComponentRendererImpl(const RefPtr<FrameNode>& host, const DynamicParam& dynamicParam);
    ~ArktsDynamicComponentRendererImpl() override = default;

    void SetAdaptiveSize(bool adaptiveWidth, bool adaptiveHeight) override;
    void SetBackgroundTransparent(bool backgroundTransparent) override;
    bool GetBackgroundTransparent() const override;
    void CreateContent() override;
    void DestroyContent() override;

    void UpdateViewportConfig(
        const SizeF& size, float density, int32_t orientation, AnimationOption animationOpt,
        const OffsetF& offset) override;

    void TransferPointerEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent) override;
    bool TransferKeyEvent(const KeyEvent& event) override;
    void TransferFocusState(bool isFocus) override;
    void TransferFocusActiveEvent(bool isFocus) override;
    void Dump(RendererDumpInfo &rendererDumpInfo) override;
    void RegisterErrorEventHandler();
    void FireOnErrorCallback(int32_t code, const std::string& name, const std::string& msg);
    void InitUiContent(OHOS::AbilityRuntime::Context *abilityContext);
    void SetUIContentType(UIContentType uIContentType) override;
    bool HasWorkerUsingByWorkerId(int32_t workerId) override;

    void SearchElementInfoByAccessibilityId(int64_t elementId, int32_t mode, int64_t baseParent,
        std::list<Accessibility::AccessibilityElementInfo>& output) override;
    void SearchElementInfosByText(int64_t elementId, const std::string& text, int64_t baseParent,
        std::list<Accessibility::AccessibilityElementInfo>& output) override;
    void FindFocusedElementInfo(int64_t elementId, int32_t focusType, int64_t baseParent,
        Accessibility::AccessibilityElementInfo& output) override;
    void FocusMoveSearch(int64_t elementId, int32_t direction, int64_t baseParent,
        Accessibility::AccessibilityElementInfo& output) override;
    bool NotifyExecuteAction(int64_t elementId, const std::map<std::string, std::string>& actionArguments,
        int32_t action, int64_t offset) override;
    void TransferAccessibilityHoverEvent(float pointX, float pointY, int32_t sourceType, int32_t eventType,
        int64_t timeMs) override;
    void TransferAccessibilityChildTreeRegister(uint32_t windowId, int32_t treeId, int64_t accessibilityId) override;
    void TransferAccessibilityChildTreeDeregister() override;
    void TransferAccessibilityDumpChildInfo(
        const std::vector<std::string>& params, std::vector<std::string>& info) override;
    void NotifyUieDump(const std::vector<std::string>& params, std::vector<std::string>& info) override;

    void UpdateParentOffsetToWindow(const OffsetF& offset) override;

    void NotifyForeground() override;
    void NotifyBackground() override;

private:
    RefPtr<TaskExecutor> GetTaskExecutor();
    RefPtr<TaskExecutor> GetHostTaskExecutor();
    static RefPtr<Platform::AceContainer> GetAceConainer(int32_t instanceId);
    void AddWorkerUsing(int32_t workerId);
    void DeleteWorkerUsing(int32_t workerId);
    void OnDestroyContent();
    void AfterDestroyContent();

    void CreateDynamicContent();
    void SetUIContentJsContext();
    void AttachRenderContext();
    void AttachRenderContextInDynamicComponent();
    void RegisterSizeChangedCallback();
    void RegisterConfigChangedCallback();
    void UnRegisterConfigChangedCallback();
    void RegisterContainerHandler();
    void BuildDynamicInitialConfig(DynamicInitialConfig& dynamicInitialConfig);
    RefPtr<SystemWindowScene> GetWindowScene();
    int32_t GetWindowSceneId();

    SizeF ComputeAdaptiveSize(const SizeF& size) const;
    void HandleCardSizeChangeEvent(const SizeF& size);
    void InitializeDynamicAccessibility();

    bool contentReady_ = false;
    std::function<void()> contentReadyCallback_;
    mutable std::mutex contentReadyMutex_;

    DynamicParam dynamicParam_;
    WeakPtr<FrameNode> host_;
    std::shared_ptr<ArktsDynamicUIContentImpl> uiContent_;
    int32_t hostInstanceId_ = -1;
    RendererDumpInfo rendererDumpInfo_;

    SizeT<int32_t> viewport_;
    bool adaptiveWidth_ = true;
    bool adaptiveHeight_ = true;
    bool backgroundTransparent_ = true;
    float density_ = 0;
    static std::set<int32_t> usingWorkers_;
    static std::mutex usingWorkerMutex_;
    UIContentType uIContentType_ = UIContentType::UNDEFINED;
    AceLogTag aceLogTag_ = AceLogTag::ACE_DEFAULT_DOMAIN;
    bool isForeground_ = true;
    std::weak_ptr<Framework::JsValue> hostJsContext_;

    ACE_DISALLOW_COPY_AND_MOVE(ArktsDynamicComponentRendererImpl);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_DYNAMIC_COMPONENT_ARKTS_DYNAMIC_COMPONENT_RENDERER_H
