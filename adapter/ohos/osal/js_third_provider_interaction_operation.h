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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_COMMON_ACCESSIBILITY_JS_THIRD_PROVIDER_INTERATION_OPERATION_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_COMMON_ACCESSIBILITY_JS_THIRD_PROVIDER_INTERATION_OPERATION_H


#include "core/accessibility/accessibility_provider.h"
#include "core/accessibility/third_accessibility_manager.h"
#include "js_accessibility_manager.h"


namespace OHOS::Ace::Framework {
struct NodeConfig {
    OHOS::Ace::NG::OffsetF offset;
    int32_t pageId = -1;
    int32_t windowId = -1;
    int32_t belongTreeId = AccessibilityElementInfo::UNDEFINED_TREE_ID;
    int32_t childTreeId = AccessibilityElementInfo::UNDEFINED_TREE_ID;
    int32_t childWindowId = AccessibilityElementInfo::UNDEFINED_WINID_ID;
    int32_t parentWindowId = AccessibilityElementInfo::UNDEFINED_WINID_ID;
    std::string bundleName;
    std::string inspectorKey;
};

class JsThirdProviderInteractionOperation : public Accessibility::AccessibilityElementOperator,
    public ThirdAccessibilityManager {
public:
    JsThirdProviderInteractionOperation(
        const WeakPtr<AccessibilityProvider>& accessibilityProvider,
        const WeakPtr<JsAccessibilityManager>& jsAccessibilityManager,
        WeakPtr<NG::FrameNode> host);
    ~JsThirdProviderInteractionOperation() override;
    void Initialize();
    // Accessibility override.
    void SearchElementInfoByAccessibilityId(
        const int64_t elementId, const int32_t requestId,
        Accessibility::AccessibilityElementOperatorCallback& callback,
        const int32_t mode) override;
    void SearchElementInfosByText(
        const int64_t elementId, const std::string& text, const int32_t requestId,
        Accessibility::AccessibilityElementOperatorCallback& callback) override;
    void FindFocusedElementInfo(
        const int64_t elementId, const int32_t focusType, const int32_t requestId,
        Accessibility::AccessibilityElementOperatorCallback& callback) override;
    void FocusMoveSearch(
        const int64_t elementId, const int32_t direction, const int32_t requestId,
        Accessibility::AccessibilityElementOperatorCallback& callback) override;
    void ExecuteAction(const int64_t elementId, const int32_t action,
        const std::map<std::string, std::string>& actionArguments, const int32_t requestId,
        Accessibility::AccessibilityElementOperatorCallback& callback) override;
    void ClearFocus() override;
    void OutsideTouch() override;
    void GetCursorPosition(const int64_t elementId, const int32_t requestId,
        Accessibility::AccessibilityElementOperatorCallback &callback) override;
    void SetChildTreeIdAndWinId(
        const int64_t nodeId, const int32_t treeId, const int32_t childWindowId) override;
    void SetBelongTreeId(const int32_t treeId) override;
    int32_t SendAccessibilityAsyncEvent(
        const ArkUI_AccessibilityEventInfo& nativeAccessibilityEvent,
        void (*callback)(int32_t errorCode)) override;
    int32_t SendAccessibilityAsyncEventForThird(
        int64_t thirdElementId,
        Accessibility::EventType eventType);
    bool FindAccessibilityNodeInfosByIdFromProvider(
        const int64_t splitElementId, const int32_t mode, const int32_t requestId,
        std::list<Accessibility::AccessibilityElementInfo>& infos);
    const WeakPtr<JsAccessibilityManager>& GetHandler() const
    {
        return jsAccessibilityManager_;
    }

    const RefPtr<NG::FrameNode> GetHost() const
    {
        return host_.Upgrade();
    }

    int32_t GetBelongTreeId() const
    {
        return belongTreeId_;
    }

private:
    void GetNodeConfig(NodeConfig& nodeConfig);
    void SetSearchElementInfoByAccessibilityIdResult(
        AccessibilityElementOperatorCallback& callback,
        std::list<AccessibilityElementInfo>&& infos,
        const int32_t requestId);
    void SetSearchElementInfoByTextResult(
        AccessibilityElementOperatorCallback& callback,
        std::list<AccessibilityElementInfo>&& infos,
        const int32_t requestId);
    void SetFindFocusedElementInfoResult(
        AccessibilityElementOperatorCallback& callback,
        AccessibilityElementInfo& info,
        const int32_t requestId);
    void SetFocusMoveSearchResult(
        AccessibilityElementOperatorCallback& callback,
        AccessibilityElementInfo& info,
        const int32_t requestId);
    void SetExecuteActionResult(
        AccessibilityElementOperatorCallback& callback,
        const bool succeeded, const int32_t requestId);
    bool FindAccessibilityNodeInfosByTextFromProvider(
        const int64_t splitElementId, const std::string& text, const int32_t requestId,
        std::list<Accessibility::AccessibilityElementInfo>& infos);
    bool ExecuteActionForThird(
        int64_t elementId, const AccessibilityElementInfo& nodeInfo, const int32_t action);
    void GetAccessibilityEventInfoFromNativeEvent(
        const ArkUI_AccessibilityEventInfo& nativeEventInfo,
        OHOS::Accessibility::AccessibilityEventInfo& accessibilityEventInfo);
    void GetAccessibilityEventInfoFromNativeEvent(
        OHOS::Accessibility::AccessibilityEventInfo& accessibilityEventInfo);
    bool SendAccessibilitySyncEventToService(
        const OHOS::Accessibility::AccessibilityEventInfo& eventInfo,
        void (*callback)(int32_t errorCode));
    bool FindFocusedElementInfoFromProvider(
        int64_t elementId, const int32_t focusType, const int32_t requestId,
        Accessibility::AccessibilityElementInfo& info);
    bool ExecuteActionFromProvider(
        int64_t elementId, const int32_t action,
        const std::map<std::string, std::string>& actionArguments, const int32_t requestId);
    bool FocusMoveSearchProvider(
        int64_t elementId, const int32_t direction, const int32_t requestId,
        Accessibility::AccessibilityElementInfo& info);
    bool ClearFocusFromProvider();
    bool ClearDrawBound();

    bool HandleNativeFocusUpdate(
        int64_t elementId,
        Accessibility::AccessibilityEventInfo& accessibilityEventInfo);
    bool HandleEventByFramework(
        const ArkUI_AccessibilityEventInfo& nativeAccessibilityEvent,
        Accessibility::AccessibilityEventInfo& accessibilityEventInfo);

    WeakPtr<AccessibilityProvider> accessibilityProvider_;
    WeakPtr<JsAccessibilityManager> jsAccessibilityManager_;
    WeakPtr<NG::FrameNode> host_;
    int32_t belongTreeId_ = AccessibilityElementInfo::UNDEFINED_TREE_ID;
};
} // namespace OHOS::Ace::Framework

#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_COMMON_ACCESSIBILITY_JS_THIRD_PROVIDER_INTERATION_OPERATION_H
