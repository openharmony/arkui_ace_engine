/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DIALOG_BRIDGE_INNER_MODIFIER_DIALOG_INNER_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DIALOG_BRIDGE_INNER_MODIFIER_DIALOG_INNER_MODIFIER_H

#include <functional>
#include <map>
#include <string>
#include <vector>
namespace OHOS::Ace {
struct DialogProperties;
struct ButtonInfo;
class GestureEvent;
class PickerTime;
class AceType;
template<typename T>
class RefPtr;
template<typename T>
class WeakPtr;
namespace NG {
class FrameNode;
class UINode;
class Pattern;
class OverlayManager;
struct DatePickerSettingData;
struct TimePickerSettingData;
struct TextPickerSettingData;
struct CalendarSettingData;
using DialogEvent = std::function<void(const std::string&)>;
using DialogGestureEvent = std::function<void(const GestureEvent& info)>;
using DialogCancelEvent = std::function<void()>;
using DialogTextEvent = std::function<void(const std::string&)>;
struct ArkUIDialogInnerModifier {
    // CustomDialogControllerModelNG
    void (*setCloseDialogForNDK)(FrameNode* dialogNode);
    RefPtr<UINode> (*setOpenDialogWithNode)(DialogProperties& dialogProperties, const RefPtr<UINode>& customNode);
    // DialogView
    void (*dismissDialog)(const RefPtr<FrameNode>& node);
    bool (*isSupportBlurStyle)(const RefPtr<FrameNode>& node, bool isShowInSubwindow);
    RefPtr<FrameNode> (*createDialogNode)(const DialogProperties& param, const RefPtr<UINode>& customNode);
    RefPtr<FrameNode> (*createDialogNodeWithThemeNode)(
        const DialogProperties& param, const RefPtr<UINode>& customNode, const RefPtr<UINode>& themeNode);
    // OverlayManager
    RefPtr<AceType> (*getDialogInnerManager)(const RefPtr<UINode>& rootNode);
    RefPtr<FrameNode> (*showDialog)(const RefPtr<AceType>& dialogInnerManager,
        const RefPtr<OverlayManager>& overlayManager, const DialogProperties& dialogProps,
        std::function<void()>&& buildFunc, bool isRightToLeft);
    RefPtr<FrameNode> (*showDialogWithErrorCallback)(const RefPtr<AceType>& dialogInnerManager,
        const RefPtr<OverlayManager>& overlayManager, const DialogProperties& dialogProps,
        std::function<void()>&& buildFunc, bool isRightToLeft, std::function<void(int32_t, int32_t)> callback);
    RefPtr<FrameNode> (*showDialogWithNode)(const RefPtr<AceType>& dialogInnerManager,
        const RefPtr<OverlayManager>& overlayManager, const DialogProperties& dialogProps,
        const RefPtr<UINode>& customNode, bool isRightToLeft);
    RefPtr<FrameNode> (*showDialogWithNodeAndErrorCallback)(const RefPtr<AceType>& dialogInnerManager,
        const RefPtr<OverlayManager>& overlayManager, const DialogProperties& dialogProps,
        const RefPtr<UINode>& customNode, bool isRightToLeft, std::function<void(int32_t, int32_t)> callback);
    RefPtr<FrameNode> (*openCustomDialog)(const RefPtr<AceType>& dialogInnerManager,
        const RefPtr<OverlayManager>& overlayManager, const DialogProperties& dialogProps,
        std::function<void(int32_t)>&& callback);
    RefPtr<FrameNode> (*openCustomDialogWithErrorCallback)(const RefPtr<AceType>& dialogInnerManager,
        const RefPtr<OverlayManager>& overlayManager, const DialogProperties& dialogProps,
        std::function<void(int32_t errorCode, int32_t dialogId)>&& callback);
    void (*closeCustomDialogWithId)(const RefPtr<AceType>& dialogInnerManager,
        const RefPtr<OverlayManager>& overlayManager, const int32_t dialogId, std::function<void(int32_t)>&& callback);
    void (*closeCustomDialogWithNode)(const RefPtr<AceType>& dialogInnerManager,
        const RefPtr<OverlayManager>& overlayManager, const WeakPtr<NG::UINode>& node,
        std::function<void(int32_t)>&& callback);
    void (*updateCustomDialog)(const RefPtr<AceType>& dialogInnerManager, const WeakPtr<NG::UINode>& node,
        const DialogProperties& dialogProps, std::function<void(int32_t)>&& callback);
    void (*updateCustomDialogWithNode)(const RefPtr<AceType>& dialogInnerManager, const WeakPtr<NG::UINode>& node,
        const DialogProperties& dialogProps, std::function<void(int32_t)>&& callback);
    void (*showDateDialog)(const RefPtr<AceType>& dialogInnerManager, const RefPtr<OverlayManager>& overlayManager,
        const DialogProperties& dialogProps, const DatePickerSettingData& settingData,
        std::map<std::string, NG::DialogEvent> dialogEvent,
        std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent,
        std::map<std::string, NG::DialogCancelEvent> dialogLifeCycleEvent, const std::vector<ButtonInfo>& buttonInfos);
    void (*showTimeDialog)(const RefPtr<AceType>& dialogInnerManager, const RefPtr<OverlayManager>& overlayManager,
        const DialogProperties& dialogProps, const TimePickerSettingData& settingData,
        std::map<std::string, PickerTime> timePickerProperty, std::map<std::string, NG::DialogEvent> dialogEvent,
        std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent,
        std::map<std::string, NG::DialogCancelEvent> dialogLifeCycleEvent, const std::vector<ButtonInfo>& buttonInfos);
    void (*showTextDialog)(const RefPtr<AceType>& dialogInnerManager, const RefPtr<OverlayManager>& overlayManager,
        const DialogProperties& dialogProps, const TextPickerSettingData& settingData,
        std::map<std::string, NG::DialogTextEvent> dialogEvent,
        std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent,
        std::map<std::string, NG::DialogCancelEvent> dialogLifeCycleEvent, const std::vector<ButtonInfo>& buttonInfos);
    void (*showCalendarDialog)(const RefPtr<AceType>& dialogInnerManager, const RefPtr<OverlayManager>& overlayManager,
        const DialogProperties& dialogProps, const CalendarSettingData& settingData,
        std::map<std::string, NG::DialogEvent> dialogEvent,
        std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent,
        std::map<std::string, NG::DialogCancelEvent> dialogLifeCycleEvent, const std::vector<ButtonInfo>& buttonInfos);
    void (*closeDialog)(const RefPtr<AceType>& dialogInnerManager, const RefPtr<OverlayManager>& overlayManager,
        const RefPtr<FrameNode>& dialogNode);
    bool (*removeDialog)(const RefPtr<AceType>& dialogInnerManager, const RefPtr<OverlayManager>& overlayManager,
        const RefPtr<FrameNode>& overlay, bool isBackPressed, bool isPageRouter);
    bool (*removeDialogWithContent)(const RefPtr<AceType>& dialogInnerManager,
        const RefPtr<OverlayManager>& overlayManager, const RefPtr<FrameNode>& overlay, const DialogProperties& props,
        bool isBackPressed, bool isPageRouter, int32_t subWindowId);

    std::unordered_map<int32_t, RefPtr<FrameNode>> (*getDialogMap)(const RefPtr<AceType>& dialogInnerManager);
    RefPtr<FrameNode> (*getDialogNodeWithExistContent)(
        const RefPtr<AceType>& dialogInnerManager, const RefPtr<UINode>& node);
    void (*reloadBuilderNodeConfig)(const RefPtr<AceType>& dialogInnerManager);
    void (*removeDialogFromMapForcefully)(const RefPtr<AceType>& dialogInnerManager, const RefPtr<FrameNode>& node);
    RefPtr<FrameNode> (*getDialog)(const RefPtr<AceType>& dialogInnerManager, int32_t dialogId);
    void (*onUIExtensionWindowSizeChange)(const RefPtr<AceType>& dialogInnerManager);
    void (*setMaskNodeId)(const RefPtr<AceType>& dialogInnerManager, int32_t dialogId, int32_t maskId);
    bool (*isMaskNode)(const RefPtr<AceType>& dialogInnerManager, int32_t maskId);
    void (*popModalDialog)(const RefPtr<AceType>& dialogInnerManager, int32_t maskId, int32_t subWindowId);
    int32_t (*getMaskNodeIdWithDialogId)(const RefPtr<AceType>& dialogInnerManager, int32_t dialogId);
    void (*removeMaskFromMap)(const RefPtr<AceType>& dialogInnerManager, const RefPtr<FrameNode>& dialogNode);
    void (*dumpMaskNodeIdMapInfo)(const RefPtr<AceType>& dialogInnerManager);
    void (*registerOnHideDialog)(const RefPtr<AceType>& dialogInnerManager, std::function<void()> callback);
    void (*fireNavigationLifecycle)(const RefPtr<AceType>& dialogInnerManager, const RefPtr<UINode>& uiNode,
        int32_t lifecycleId, bool isLowerOnly, int32_t reason);
    void (*setBackPressEvent)(const RefPtr<AceType>& dialogInnerManager, std::function<bool()> event);
};
namespace InnerModifier {
const ArkUIDialogInnerModifier* GetDialogInnerModifier();
} // namespace InnerModifier
} // namespace NG
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DIALOG_BRIDGE_INNER_MODIFIER_DIALOG_INNER_MODIFIER_H
