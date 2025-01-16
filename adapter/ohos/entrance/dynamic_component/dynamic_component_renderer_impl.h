/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_DYNAMIC_COMPONENT_DYNAMIC_COMPONENT_RENDERER_H
#define FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_DYNAMIC_COMPONENT_DYNAMIC_COMPONENT_RENDERER_H

#include <cstdint>

#include "interfaces/inner_api/ace/ui_content.h"

#include "adapter/ohos/entrance/ace_container.h"
#include "base/memory/ace_type.h"
#include "base/thread/task_executor.h"
#include "core/common/dynamic_component_renderer.h"
#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {

class DynamicComponentRendererImpl : public DynamicComponentRenderer {
    DECLARE_ACE_TYPE(DynamicComponentRendererImpl, DynamicComponentRenderer);

public:
    DynamicComponentRendererImpl(const RefPtr<FrameNode>& host, void* runtime, const IsolatedInfo& isolatedInfo);
    ~DynamicComponentRendererImpl() override = default;

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
    void InitUiContent(
        OHOS::AbilityRuntime::Context *abilityContext, const std::shared_ptr<Framework::JsValue>& jsContext);
    void SetUIContentType(UIContentType uIContentType) override;
    bool IsRestrictedWorkerThread() override;
    bool HasWorkerUsing(void *worker) override;

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

private:
    RefPtr<TaskExecutor> GetTaskExecutor();
    RefPtr<TaskExecutor> GetHostTaskExecutor();
    void AddWorkerUsing(void *worker);
    void DeleteWorkerUsing(void *worker);

    void CreateIsolatedContent();
    void CreateDynamicContent();
    void SetUIContentJsContext(
        const std::shared_ptr<Framework::JsValue>& jsContext);

    void AttachRenderContext();
    void AttachRenderContextInIsolatedComponent();
    void AttachRenderContextInDynamicComponent();
    void RegisterSizeChangedCallback();
    void RegisterConfigChangedCallback();
    void UnRegisterConfigChangedCallback();
    void RegisterContainerHandler();

    SizeF ComputeAdaptiveSize(const SizeF& size) const;
    void HandleCardSizeChangeEvent(const SizeF& size);
    void InitializeDynamicAccessibility();

    bool contentReady_ = false;
    std::function<void()> contentReadyCallback_;
    mutable std::mutex contentReadyMutex_;

    IsolatedInfo isolatedInfo_;
    std::shared_ptr<UIContent> uiContent_;
    NativeEngine* runtime_ = nullptr;
    WeakPtr<FrameNode> host_;
    int32_t hostInstanceId_ = -1;
    RendererDumpInfo rendererDumpInfo_;

    SizeT<int32_t> viewport_;
    bool adaptiveWidth_ = true;
    bool adaptiveHeight_ = true;
    bool backgroundTransparent_ = true;
    float density_ = 0;
    static std::set<void *> usingWorkers_;
    static std::mutex usingWorkerMutex_;
    UIContentType uIContentType_ = UIContentType::UNDEFINED;
    AceLogTag aceLogTag_ = AceLogTag::ACE_DEFAULT_DOMAIN;

    ACE_DISALLOW_COPY_AND_MOVE(DynamicComponentRendererImpl);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_DYNAMIC_COMPONENT_DYNAMIC_COMPONENT_RENDERER_H
