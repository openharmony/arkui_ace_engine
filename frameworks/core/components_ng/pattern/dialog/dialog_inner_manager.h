/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DIALOG_DIALOG_INNER_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DIALOG_DIALOG_INNER_MANAGER_H

#include <functional>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

#include "base/memory/ace_type.h"
namespace OHOS::Ace {
struct DialogProperties;
struct ButtonInfo;
class GestureEvent;
class PickerTime;
enum class AccessibilityEventType : size_t;
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
class FrameNode;
class PipelineContext;
class OverlayManager;
class UINode;

struct DatePickerSettingData;
struct TimePickerSettingData;
struct TextPickerSettingData;
struct CalendarSettingData;
using DialogEvent = std::function<void(const std::string&)>;
using DialogGestureEvent = std::function<void(const GestureEvent& info)>;
using DialogCancelEvent = std::function<void()>;
using DialogTextEvent = std::function<void(const std::string&)>;

class ACE_EXPORT DialogInnerManager : public virtual AceType {
    DECLARE_ACE_TYPE(DialogInnerManager, AceType);

public:
    explicit DialogInnerManager(const RefPtr<UINode>& rootNode);
    ~DialogInnerManager() override;
    RefPtr<FrameNode> ShowDialog(const RefPtr<OverlayManager>& overlayManager, const DialogProperties& dialogProps,
        std::function<void()>&& buildFunc, bool isRightToLeft);
    RefPtr<FrameNode> ShowDialogWithErrorCallback(const RefPtr<OverlayManager>& overlayManager,
        const DialogProperties& dialogProps, std::function<void()>&& buildFunc, bool isRightToLeft,
        std::function<void(int32_t, int32_t)> callback);
    RefPtr<FrameNode> ShowDialogWithNode(const RefPtr<OverlayManager>& overlayManager,
        const DialogProperties& dialogProps, const RefPtr<UINode>& customNode, bool isRightToLeft);
    RefPtr<FrameNode> ShowDialogWithNodeAndErrorCallback(const RefPtr<OverlayManager>& overlayManager,
        const DialogProperties& dialogProps, const RefPtr<UINode>& customNode, bool isRightToLeft,
        std::function<void(int32_t, int32_t)> callback);
    RefPtr<FrameNode> OpenCustomDialog(const RefPtr<OverlayManager>& overlayManager,
        const DialogProperties& dialogProps, std::function<void(int32_t)>&& callback);
    RefPtr<FrameNode> OpenCustomDialogWithErrorCallback(const RefPtr<OverlayManager>& overlayManager,
        const DialogProperties& dialogProps, std::function<void(int32_t errorCode, int32_t dialogId)>&& callback);
    void CloseCustomDialogWithId(const RefPtr<OverlayManager>& overlayManager, const int32_t dialogId,
        std::function<void(int32_t)>&& callback = nullptr);
    void CloseCustomDialogWithNode(const RefPtr<OverlayManager>& overlayManager, const WeakPtr<NG::UINode>& node,
        std::function<void(int32_t)>&& callback);
    void UpdateCustomDialog(
        const WeakPtr<NG::UINode>& node, const DialogProperties& dialogProps, std::function<void(int32_t)>&& callback);
    void UpdateCustomDialogWithNode(
        const WeakPtr<NG::UINode>& node, const DialogProperties& dialogProps, std::function<void(int32_t)>&& callback);
    void ShowDateDialog(const RefPtr<OverlayManager>& overlayManager, const DialogProperties& dialogProps,
        const DatePickerSettingData& settingData, std::map<std::string, NG::DialogEvent> dialogEvent,
        std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent,
        std::map<std::string, NG::DialogCancelEvent> dialogLifeCycleEvent, const std::vector<ButtonInfo>& buttonInfos);
    void ShowTimeDialog(const RefPtr<OverlayManager>& overlayManager, const DialogProperties& dialogProps,
        const TimePickerSettingData& settingData, std::map<std::string, PickerTime> timePickerProperty,
        std::map<std::string, NG::DialogEvent> dialogEvent,
        std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent,
        std::map<std::string, NG::DialogCancelEvent> dialogLifeCycleEvent, const std::vector<ButtonInfo>& buttonInfos);
    void ShowTextDialog(const RefPtr<OverlayManager>& overlayManager, const DialogProperties& dialogProps,
        const TextPickerSettingData& settingData, std::map<std::string, NG::DialogTextEvent> dialogEvent,
        std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent,
        std::map<std::string, NG::DialogCancelEvent> dialogLifeCycleEvent, const std::vector<ButtonInfo>& buttonInfos);
    void ShowCalendarDialog(const RefPtr<OverlayManager>& overlayManager, const DialogProperties& dialogProps,
        const CalendarSettingData& settingData, std::map<std::string, NG::DialogEvent> dialogEvent,
        std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent,
        std::map<std::string, NG::DialogCancelEvent> dialogLifeCycleEvent, const std::vector<ButtonInfo>& buttonInfos);
    void CloseDialog(const RefPtr<OverlayManager>& overlayManager, const RefPtr<FrameNode>& dialogNode);
    bool RemoveDialog(const RefPtr<OverlayManager>& overlayManager, const RefPtr<FrameNode>& overlay,
        bool isBackPressed, bool isPageRouter);
    bool RemoveDialogWithContent(const RefPtr<OverlayManager>& overlayManager, const RefPtr<FrameNode>& overlay,
        const DialogProperties& props, bool isBackPressed, bool isPageRouter, int32_t subWindowId);

    std::unordered_map<int32_t, RefPtr<FrameNode>> GetDialogMap();
    RefPtr<FrameNode> GetDialogNodeWithExistContent(const RefPtr<UINode>& node);
    void ReloadBuilderNodeConfig();
    void RemoveDialogFromMapForcefully(const RefPtr<FrameNode>& node);
    RefPtr<FrameNode> GetDialog(int32_t dialogId);
    void OnUIExtensionWindowSizeChange();
    void SetMaskNodeId(int32_t dialogId, int32_t maskId);
    bool IsMaskNode(int32_t maskId);
    void PopModalDialog(int32_t maskId, int32_t subWindowId);
    int32_t GetMaskNodeIdWithDialogId(int32_t dialogId);
    void RemoveMaskFromMap(const RefPtr<FrameNode>& dialogNode);
    void DumpMaskNodeIdMapInfo() const;
    void RegisterOnHideDialog(std::function<void()> callback);
    void FireNavigationLifecycle(const RefPtr<UINode>& uiNode, int32_t lifecycleId, bool isLowerOnly, int32_t reason);
    void SetBackPressEvent(std::function<bool()> event);

private:
    RefPtr<PipelineContext> GetPipelineContext() const;
    void RemoveDialogFromMap(const RefPtr<FrameNode>& node);
    void CallOnHideDialogCallback();
    bool FireBackPressEvent() const;
    void RegisterDialogLifeCycleCallback(const RefPtr<FrameNode>& dialog, const DialogProperties& dialogProps);
    void UpdateChildVisible(const RefPtr<OverlayManager>& overlayManager, const RefPtr<FrameNode>& node,
        const RefPtr<FrameNode>& childNode);
    void SetTransitionCallbacks(const RefPtr<OverlayManager>& overlayManager, const RefPtr<FrameNode>& node,
        const RefPtr<FrameNode>& contentNode, const RefPtr<FrameNode>& maskNode, const DialogProperties& dialogProps);
    void SendDialogAccessibilityEvent(const RefPtr<FrameNode>& node, AccessibilityEventType eventType);
    void SetDialogTransitionEffect(const RefPtr<OverlayManager>& overlayManager, const RefPtr<FrameNode>& node,
        const DialogProperties& dialogProps, std::function<void(int32_t)> mountCallback = nullptr);
    void BeforeShowDialog(const RefPtr<FrameNode>& dialogNode);
    void OpenDialogAnimationInner(const RefPtr<OverlayManager>& overlayManager, const RefPtr<FrameNode>& node,
        const DialogProperties& dialogProps, bool isReadFirstNode = true);
    void OpenDialogAnimation(const RefPtr<OverlayManager>& overlayManager, const RefPtr<FrameNode>& node,
        const DialogProperties& dialogProps, bool isReadFirstNode = true,
        std::function<void(int32_t)> mountCallback = nullptr);
    void SetContainerButtonEnable(bool isEnabled);
    RefPtr<UINode> RebuildCustomBuilder(RefPtr<UINode>& contentNode);
    void CustomDialogRecordEvent(const DialogProperties& dialogProps);
    void OpenCustomDialogInner(const RefPtr<OverlayManager>& overlayManager, const DialogProperties& dialogProps,
        std::function<void(int32_t)>&& callback, const RefPtr<FrameNode>& dialog, bool showComponentContent);
    void OpenCustomDialogInner(const RefPtr<OverlayManager>& overlayManager, const DialogProperties& dialogProps,
        std::function<void(int32_t errorCode, int32_t dialogId)>&& callback, const RefPtr<FrameNode> dialog,
        bool showComponentContent);
    void DeleteDialogHotAreas(const RefPtr<FrameNode>& dialogNode);
    void OnDialogCloseEvent(const RefPtr<OverlayManager>& overlayManager, const RefPtr<FrameNode>& node);
    void PostDialogFinishEvent(const RefPtr<OverlayManager>& overlayManager, const WeakPtr<FrameNode>& nodeWk);
    void UpdateChildInvisible(
        const RefPtr<OverlayManager>& overlayManager, const RefPtr<FrameNode>& node, const RefPtr<FrameNode>& child);
    void CloseMaskAndContentMatchTransition(
        const RefPtr<OverlayManager>& overlayManager, const RefPtr<FrameNode>& node);
    void CloseDialogMatchTransition(const RefPtr<OverlayManager>& overlayManager, const RefPtr<FrameNode>& node);
    void CloseDialogAnimation(const RefPtr<OverlayManager>& overlayManager, const RefPtr<FrameNode>& node);
    void CloseDialogInner(const RefPtr<OverlayManager>& overlayManager, const RefPtr<FrameNode>& dialogNode);
    RefPtr<FrameNode> UpdateCustomDialogInner(const WeakPtr<NG::UINode>& node, const DialogProperties& dialogProps,
        const std::function<void(int32_t)>& callback);
    void RegisterDialogCallback(
        const RefPtr<FrameNode>& node, std::map<std::string, NG::DialogCancelEvent> dialogLifeCycleEvent);

    WeakPtr<UINode> rootNodeWeak_;
    WeakPtr<PipelineContext> context_;
    std::unordered_map<int32_t, RefPtr<FrameNode>> dialogMap_;
    std::unordered_map<int32_t, int32_t> maskNodeIdMap_;
    int32_t dialogCount_ = 0;
    std::function<void()> onHideDialogCallback_ = nullptr;
    std::function<bool()> backPressEvent_ = nullptr;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DIALOG_DIALOG_INNER_MANAGER_H
