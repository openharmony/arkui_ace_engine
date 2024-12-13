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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_SUBWINDOW_SUBWINDOW_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_SUBWINDOW_SUBWINDOW_MANAGER_H

#include <mutex>
#include <set>
#include <unordered_map>
#include <array>
#include <functional>

#include "base/memory/referenced.h"
#include "base/subwindow/subwindow.h"
#include "base/utils/macros.h"
#include "base/utils/noncopyable.h"
#include "core/components/dialog/dialog_properties.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"

namespace OHOS::Ace {

struct SubwindowKey {
    int32_t instanceId;
    uint64_t displayId;

    bool operator==(const SubwindowKey& other) const
    {
        return other.instanceId == instanceId && other.displayId == displayId;
    }

    std::string ToString() const
    {
        auto json = JsonUtil::Create(true);
        json->Put("instanceId", instanceId);
        json->Put("displayId", (double)displayId);
        return json->ToString();
    }
};

struct SubwindowKeyHashFunc {
    std::size_t operator()(const SubwindowKey& key) const
    {
        return ((std::hash<uint64_t>()(key.instanceId) ^ (std::hash<uint64_t>()(key.displayId) << 1)) >> 1);
    }
};

using SubwindowMap = std::unordered_map<int32_t, RefPtr<Subwindow>>;
using SubwindowMixMap = std::unordered_map<SubwindowKey, RefPtr<Subwindow>, SubwindowKeyHashFunc>;

class ACE_EXPORT SubwindowManager final : public NonCopyable {
public:
    // Get the instance
    ACE_FORCE_EXPORT static std::shared_ptr<SubwindowManager> GetInstance();

    void AddContainerId(uint32_t windowId, int32_t containerId);
    void RemoveContainerId(uint32_t windowId);
    int32_t GetContainerId(uint32_t windowId);

    void AddParentContainerId(int32_t containerId, int32_t parentContainerId);
    void RemoveParentContainerId(int32_t containerId);
    int32_t GetParentContainerId(int32_t containerId);
    int32_t GetSubContainerId(int32_t parentContainerId);

    void AddSubwindow(int32_t instanceId, RefPtr<Subwindow>);
    void RemoveSubwindow(int32_t instanceId);

    // Get the subwindow of instance, return the window or nullptr.
    const RefPtr<Subwindow> GetSubwindow(int32_t instanceId);
    const RefPtr<Subwindow> GetSubwindow(int32_t instanceId, uint64_t displayId);
    const RefPtr<Subwindow> GetOrCreateSubwindow(int32_t instanceId);

    void SetCurrentSubwindow(const RefPtr<Subwindow>& subwindow);

    const RefPtr<Subwindow>& GetCurrentWindow();
    Rect GetParentWindowRect();

    RefPtr<Subwindow> ShowPreviewNG(bool isStartDraggingFromSubWindow);
    void HidePreviewNG();
    void ShowMenu(const RefPtr<Component>& newComponent);
    void ShowMenuNG(const RefPtr<NG::FrameNode>& menuNode, const NG::MenuParam& menuParam,
        const RefPtr<NG::FrameNode>& targetNode, const NG::OffsetF& offset);
    void ShowMenuNG(std::function<void()>&& buildFunc, std::function<void()>&& previewBuildFunc,
        const NG::MenuParam& menuParam, const RefPtr<NG::FrameNode>& targetNode, const NG::OffsetF& offset);
    ACE_FORCE_EXPORT void HideMenuNG(const RefPtr<NG::FrameNode>& menu, int32_t targetId);
    ACE_FORCE_EXPORT void HideMenuNG(bool showPreviewAnimation = true, bool startDrag = false);
    void UpdateHideMenuOffsetNG(const NG::OffsetF& offset = NG::OffsetF(0.0f, 0.0f), float menuScale = 1.0f,
        bool isRedragStart = false, int32_t menuWrapperId = -1);
    void ContextMenuSwitchDragPreviewAnimation(const RefPtr<NG::FrameNode>& dragPreviewNode,
        const NG::OffsetF& offset = NG::OffsetF(0.0f, 0.0f));
    void UpdatePreviewPosition();
    bool GetMenuPreviewCenter(NG::OffsetF& offset);
    void ShowPopup(const RefPtr<Component>& newComponent, bool disableTouchEvent = true);
    void ShowPopupNG(const RefPtr<NG::FrameNode>& targetNode, const NG::PopupInfo& popupInfo,
        const std::function<void(int32_t)>&& onWillDismiss = nullptr, bool interactiveDismiss = true);
    void HidePopupNG(int32_t targetId, int32_t instanceId = -1);
    bool CancelPopup(const std::string& id);
    void CloseMenu();
    void ClearMenu();
    void ClearMenuNG(int32_t instanceId = -1, int32_t targetId = -1, bool inWindow = true, bool showAnimation = false);
    void ClearPopupInSubwindow(int32_t instanceId = -1);
    ACE_FORCE_EXPORT RefPtr<NG::FrameNode> ShowDialogNG(
        const DialogProperties& dialogProps, std::function<void()>&& buildFunc);
    RefPtr<NG::FrameNode> ShowDialogNGWithNode(const DialogProperties& dialogProps,
        const RefPtr<NG::UINode>& customNode);
    void CloseDialogNG(const RefPtr<NG::FrameNode>& dialogNode);
    ACE_FORCE_EXPORT void OpenCustomDialogNG(
        const DialogProperties& dialogProps, std::function<void(int32_t)>&& callback);
    ACE_FORCE_EXPORT void CloseCustomDialogNG(int32_t dialogId);
    ACE_FORCE_EXPORT void CloseCustomDialogNG(const WeakPtr<NG::UINode>& node, std::function<void(int32_t)>&& callback);
    ACE_FORCE_EXPORT void UpdateCustomDialogNG(
        const WeakPtr<NG::UINode>& node, const PromptDialogAttr& dialogAttr, std::function<void(int32_t)>&& callback);
    void HideSubWindowNG();
    void HideDialogSubWindow(int32_t instanceId);
    void SetHotAreas(const std::vector<Rect>& rects, int32_t nodeId = -1, int32_t instanceId = -1);
    void AddDialogSubwindow(int32_t instanceId, const RefPtr<Subwindow>& subwindow);
    // Get the dialog subwindow of instance, return the window or nullptr.
    int32_t GetDialogSubwindowInstanceId(int32_t SubwindowId);
    const RefPtr<Subwindow> GetDialogSubwindow(int32_t instanceId);
    void SetCurrentDialogSubwindow(const RefPtr<Subwindow>& subwindow);
    const RefPtr<Subwindow>& GetCurrentDialogWindow();
    void DeleteHotAreas(int32_t subwindowId, int32_t nodeId);

    void ClearToastInSubwindow();
    ACE_FORCE_EXPORT void ShowToast(const NG::ToastInfo& toastInfo, std::function<void(int32_t)>&& callback);
    void ShowToastNG(const NG::ToastInfo& toastInfo, std::function<void(int32_t)>&& callback);
    const RefPtr<Subwindow> GetToastSubwindow(int32_t instanceId);
    void AddToastSubwindow(int32_t instanceId, RefPtr<Subwindow> subwindow);
    void HideToastSubWindowNG();
    ToastWindowType GetToastWindowType(int32_t instanceId);
    ACE_FORCE_EXPORT void CloseToast(
        const int32_t toastId, const NG::ToastShowMode& showMode, std::function<void(int32_t)>&& callback);
    ACE_FORCE_EXPORT void ShowDialog(const std::string& title, const std::string& message,
        const std::vector<ButtonInfo>& buttons, bool autoCancel, std::function<void(int32_t, int32_t)>&& napiCallback,
        const std::set<std::string>& dialogCallbacks);
    ACE_FORCE_EXPORT void ShowDialog(const PromptDialogAttr& dialogAttr, const std::vector<ButtonInfo>& buttons,
        std::function<void(int32_t, int32_t)>&& napiCallback, const std::set<std::string>& dialogCallbacks);
    ACE_FORCE_EXPORT void ShowActionMenu(const std::string& title, const std::vector<ButtonInfo>& button,
        std::function<void(int32_t, int32_t)>&& callback);
    void CloseDialog(int32_t instanceId);
    void RequestFocusSubwindow(int32_t instanceId);
    ACE_FORCE_EXPORT void OpenCustomDialog(const PromptDialogAttr &dialogAttr, std::function<void(int32_t)> &&callback);
    void CloseCustomDialog(const int32_t dialogId);
    void CloseCustomDialog(const WeakPtr<NG::UINode>& node, std::function<void(int32_t)> &&callback);

    bool GetShown();
    void ResizeWindowForFoldStatus(int32_t parentContainerId);
    void MarkDirtyDialogSafeArea();
    void HideSystemTopMostWindow();
    const RefPtr<Subwindow> GetSystemToastWindow(int32_t instanceId);
    void AddSystemToastWindow(int32_t instanceId, RefPtr<Subwindow> subwindow);
    void ClearToastInSystemSubwindow();
    void OnWindowSizeChanged(int32_t instanceId, Rect windowRect, WindowSizeChangeReason reason);
    bool IsFreeMultiWindow(int32_t instanceId) const;

    RefPtr<NG::FrameNode> GetSubwindowDialogNodeWithExistContent(const RefPtr<NG::UINode>& node);

    void SetRect(const NG::RectF& rect, int32_t instanceId);

private:
    RefPtr<Subwindow> GetOrCreateSubWindow();
    RefPtr<Subwindow> GetOrCreateSystemSubWindow(int32_t containerId);
    RefPtr<Subwindow> GetOrCreateToastWindow(int32_t containerId, const NG::ToastShowMode& showMode);
    RefPtr<Subwindow> GetOrCreateToastWindowNG(int32_t containerId, const ToastWindowType& windowType,
        uint32_t mainWindowId);
    const std::vector<RefPtr<NG::OverlayManager>> GetAllSubOverlayManager();
    SubwindowKey GetCurrentSubwindowKey(int32_t instanceId);
    static std::mutex instanceMutex_;
    static std::shared_ptr<SubwindowManager> instance_;

    std::mutex mutex_;
    std::unordered_map<uint32_t, int32_t> containerMap_;

    std::mutex parentMutex_;
    std::unordered_map<int32_t, int32_t> parentContainerMap_;

    // Used to save the relationship between container and subwindow, it is 1:1
    std::mutex subwindowMutex_;
    SubwindowMixMap subwindowMap_;
    static thread_local RefPtr<Subwindow> currentSubwindow_;

    std::mutex toastMutex_;
    SubwindowMixMap toastWindowMap_;
    // Used to save the relationship between container and dialog subwindow, it is 1:1
    std::mutex dialogSubwindowMutex_;
    SubwindowMap dialogSubwindowMap_;
    std::mutex currentDialogSubwindowMutex_;
    RefPtr<Subwindow> currentDialogSubwindow_;
    std::mutex systemToastMutex_;
    SubwindowMixMap systemToastWindowMap_;
    Rect uiExtensionWindowRect_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_SUBWINDOW_SUBWINDOW_MANAGER_H
