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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_SECURITY_UI_EXTENSION_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_SECURITY_UI_EXTENSION_PATTERN_H

#include "core/common/dynamic_component_renderer.h"
#include "core/components_ng/pattern/ui_extension/accessibility_session_adapter_ui_extension.h"
#include "core/components_ng/pattern/ui_extension/platform_accessibility_child_tree_callback.h"
#include "core/components_ng/pattern/ui_extension/platform_event_proxy.h"
#include "core/components_ng/pattern/ui_extension/platform_pattern.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_hub.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_model_ng.h"

namespace OHOS::Ace::NG {
using BusinessDataUECConsumeCallback = std::function<int32_t(const AAFwk::Want&)>;
using BusinessDataUECConsumeReplyCallback = std::function<int32_t(const AAFwk::Want&, std::optional<AAFwk::Want>&)>;

class SecurityUIExtensionPattern : public PlatformPattern, public PlatformAccessibilityBase {
    DECLARE_ACE_TYPE(SecurityUIExtensionPattern, PlatformPattern, PlatformAccessibilityBase);

public:
    SecurityUIExtensionPattern();
    ~SecurityUIExtensionPattern() override;

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override;
    FocusPattern GetFocusPattern() const override;
    RefPtr<AccessibilitySessionAdapter> GetAccessibilitySessionAdapter() override;

    void SetPlaceholderNode(const RefPtr<FrameNode>& placeholderNode)
    {
        placeholderNode_ = placeholderNode;
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<UIExtensionHub>();
    }

    const std::string& GetUiExtensionType()
    {
        return uiExtensionType_;
    }

    void Initialize(const NG::UIExtensionConfig& config);
    void UnregisterResources();
    void UpdateWant(const RefPtr<OHOS::Ace::WantWrap>& wantWrap);
    void UpdateWant(const AAFwk::Want& want);
    void SetWantWrap(const RefPtr<OHOS::Ace::WantWrap>& wantWrap);
    RefPtr<OHOS::Ace::WantWrap> GetWantWrap();
    void MountPlaceholderNode();
    void RemovePlaceholderNode();
    void OnConnect();
    void OnDisconnect(bool isAbnormal);
    void NotifySizeChangeReason(
        WindowSizeChangeReason type, const std::shared_ptr<Rosen::RSTransaction>& rsTransaction);
    void NotifyForeground();
    void NotifyBackground();
    void NotifyDestroy();
    int32_t GetSessionId();
    int32_t GetNodeId();
    int32_t GetInstanceId();
    void SetEventProxyFlag(int32_t flag);
    void OnExtensionEvent(UIExtCallbackEventId eventId);
    void OnUeaAccessibilityEventAsync();
    void OnExtensionDetachToDisplay();

    void OnSyncGeometryNode(const DirtySwapConfig& config) override;
    void OnWindowShow() override;
    void OnWindowHide() override;
    void OnAttachToFrameNode() override;
    void OnDetachFromFrameNode(FrameNode* frameNode) override;
    void OnModifyDone() override;
    void OnVisibleChange(bool visible) override;
    void OnMountToParentDone() override;
    void OnLanguageConfigurationUpdate() override;
    void OnColorConfigurationUpdate() override;
    int32_t GetUiExtensionId() override;
    void DispatchDisplayArea(bool isForce = false);
    void RegisterVisibleAreaChange();
    void DispatchOriginAvoidArea(const Rosen::AvoidArea& avoidArea, uint32_t type);
    int64_t WrapExtensionAbilityId(int64_t extensionOffset, int64_t abilityId) override;
    void FireOnErrorCallback(
        int32_t code, const std::string& name, const std::string& message) override;
    void DumpInfo() override;
    void DumpInfo(std::unique_ptr<JsonValue>& json) override;

    void FireOnRemoteReadyCallback();
    void FireBindModalCallback();
    void FireOnTerminatedCallback(int32_t code, const RefPtr<WantWrap>& wantWrap);
    void FireOnReceiveCallback(const AAFwk::WantParams& params);
    void SetSyncCallbacks(
        const std::list<std::function<void(const RefPtr<NG::SecurityUIExtensionProxy>&)>>&& callbackList);
    void FireSyncCallbacks();
    void SetAsyncCallbacks(
        const std::list<std::function<void(const RefPtr<NG::SecurityUIExtensionProxy>&)>>&& callbackList);
    void FireAsyncCallbacks();

    // Dpi
    void SetDensityDpi(bool densityDpi);
    bool GetDensityDpi();
    void DispatchFollowHostDensity(bool densityDpi);
    void OnDpiConfigurationUpdate() override;

    void OnAccessibilityChildTreeRegister(uint32_t windowId, int32_t treeId, int64_t accessibilityId) const override;
    void OnAccessibilityChildTreeDeregister() const override;
    void OnSetAccessibilityChildTree(int32_t childWindowId, int32_t childTreeId) const override;
    void OnAccessibilityDumpChildInfo(
        const std::vector<std::string>& params, std::vector<std::string>& info) const override;
    
    int32_t GetInstanceIdFromHost() const;
    bool SendBusinessDataSyncReply(UIContentBusinessCode code, AAFwk::Want&& data, AAFwk::Want& reply);
    bool SendBusinessData(UIContentBusinessCode code, AAFwk::Want&& data, BusinessDataSendType type);
    void OnUIExtBusinessReceiveReply(
        UIContentBusinessCode code, const AAFwk::Want& data, std::optional<AAFwk::Want>& reply);
    void OnUIExtBusinessReceive(UIContentBusinessCode code, const AAFwk::Want& data);
    void RegisterUIExtBusinessConsumeCallback(UIContentBusinessCode code, BusinessDataUECConsumeCallback callback);
    void RegisterUIExtBusinessConsumeReplyCallback(
        UIContentBusinessCode code, BusinessDataUECConsumeReplyCallback callback);

private:
    void InitializeAccessibility();
    bool HandleKeyEvent(const KeyEvent& event) override;
    void HandleFocusEvent() override;
    void HandleBlurEvent() override;
    void DispatchFocusActiveEvent(bool isFocusActive) override;
    void HandleTouchEvent(const TouchEventInfo& info) override;
    void DispatchFocusState(bool focusState);
    void ResetAccessibilityChildTreeCallback();
    void RegisterEventProxyFlagCallback();

    enum class AbilityState {
        NONE = 0,
        FOREGROUND,
        BACKGROUND,
        DESTRUCTION,
    };

    const char* ToString(AbilityState state);
    bool CheckConstraint();

    RefPtr<FrameNode> placeholderNode_ = nullptr;
    RefPtr<OHOS::Ace::WantWrap> curWant_;
    RefPtr<FrameNode> contentNode_;
    RefPtr<SessionWrapper> sessionWrapper_;
    RefPtr<AccessibilitySessionAdapterUIExtension> accessibilitySessionAdapter_;
    RefPtr<PlatformEventProxy> platformEventProxy_;
    AbilityState state_ = AbilityState::NONE;
    bool isVisible_ = true;
    bool isShowPlaceholder_ = false;
    bool densityDpi_ = false;
    int32_t callbackId_ = 0;
    RectF displayArea_;
    SessionType sessionType_ = SessionType::UI_EXTENSION_ABILITY;
    int32_t uiExtensionId_ = 0;
    std::string uiExtensionType_;
    std::shared_ptr<AccessibilityChildTreeCallback> accessibilityChildTreeCallback_ = nullptr;

    std::list<std::function<void(const RefPtr<NG::SecurityUIExtensionProxy>&)>> onSyncOnCallbackList_;
    std::list<std::function<void(const RefPtr<NG::SecurityUIExtensionProxy>&)>> onAsyncOnCallbackList_;
    std::map<UIContentBusinessCode, BusinessDataUECConsumeCallback> businessDataUECConsumeCallbacks_;
    std::map<UIContentBusinessCode, BusinessDataUECConsumeReplyCallback> businessDataUECConsumeReplyCallbacks_;

    ACE_DISALLOW_COPY_AND_MOVE(SecurityUIExtensionPattern);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_SECURITY_UI_EXTENSION_PATTERN_H
