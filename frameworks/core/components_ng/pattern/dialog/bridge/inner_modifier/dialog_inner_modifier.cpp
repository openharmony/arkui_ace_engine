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

#include "core/components_ng/pattern/dialog/bridge/inner_modifier/dialog_inner_modifier.h"

#include "interfaces/inner_api/ui_session/ui_session_manager.h"

#include "bridge/common/utils/utils.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/dialog/custom_dialog/custom_dialog_controller_model_ng.h"
#include "core/components_ng/pattern/dialog/dialog_inner_manager.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_view.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"

namespace OHOS::Ace::NG {
namespace {
void DismissDialog(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_VOID(node);
    auto pattern = node->GetPattern();
    CHECK_NULL_VOID(pattern);
    auto dialogPattern = AceType::DynamicCast<DialogPattern>(pattern);
    CHECK_NULL_VOID(dialogPattern);
    dialogPattern->OverlayDismissDialog(node);
    UiSessionManager::GetInstance()->ReportComponentChangeEvent(
        "onVisibleChange", "destroy", ComponentEventType::COMPONENT_EVENT_DIALOG);
}

RefPtr<FrameNode> CreateDialogNode(const DialogProperties& param, const RefPtr<UINode>& customNode)
{
    return DialogView::CreateDialogNode(param, customNode);
}

RefPtr<FrameNode> CreateDialogNodeWithThemeNode(
    const DialogProperties& param, const RefPtr<UINode>& customNode, const RefPtr<UINode>& themeNode)
{
    return DialogView::CreateDialogNode(param, customNode, themeNode);
}

void SetIsPickerDialog(const RefPtr<FrameNode>& dialogNode, bool value)
{
    CHECK_NULL_VOID(dialogNode);
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    CHECK_NULL_VOID(dialogPattern);
    dialogPattern->SetIsPickerDialog(value);
}

void SetState(const RefPtr<FrameNode>& dialogNode)
{
    CHECK_NULL_VOID(dialogNode);
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    CHECK_NULL_VOID(dialogPattern);
    if (dialogPattern->GetState() == PromptActionCommonState::UNINITIALIZED) {
        dialogPattern->SetState(PromptActionCommonState::INITIALIZED);
        TAG_LOGI(AceLogTag::ACE_DIALOG, "The current state of the dialog is INITIALIZED.");
    }
}

PromptActionCommonState GetState(const RefPtr<FrameNode>& dialogNode, PromptActionCommonState defaultState)
{
    CHECK_NULL_RETURN(dialogNode, defaultState);
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    CHECK_NULL_RETURN(dialogPattern, defaultState);
    return dialogPattern->GetState();
}

bool IsCustomDialogValid(const RefPtr<UINode>& node)
{
    auto frameNode = AceType::DynamicCast<FrameNode>(node);
    CHECK_NULL_RETURN(frameNode, false);
    // if lower layer is dialog, don't need to trigger lifecycle
    auto pattern = frameNode->GetPattern();
    CHECK_EQUAL_RETURN(AceType::InstanceOf<DialogPattern>(pattern), false, false);
    auto dialogPattern = AceType::DynamicCast<DialogPattern>(pattern);
    CHECK_NULL_RETURN(dialogPattern, false);
    auto dialogProperty = dialogPattern->GetDialogProperties();
    // if dialog is custom dialog, don't need to trigger active lifecycle, it triggers when dialog closed
    return dialogProperty.isUserCreatedDialog;
}

void OnThemeScopeUpdate(const WeakPtr<FrameNode>& weakDialogNode, int32_t themeScopeId)
{
    auto dialogNode = weakDialogNode.Upgrade();
    CHECK_NULL_VOID(dialogNode);
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    CHECK_NULL_VOID(dialogPattern);
    dialogPattern->OnThemeScopeUpdate(themeScopeId);
}

void UpdateDialogOffset(const RefPtr<FrameNode>& dialogNode, const DimensionOffset& value)
{
    CHECK_NULL_VOID(dialogNode);
    auto dialogLayoutProp = dialogNode->GetLayoutProperty<DialogLayoutProperty>();
    CHECK_NULL_VOID(dialogLayoutProp);
    dialogLayoutProp->UpdateDialogOffset(value);
}

bool GetSubwindowShouldUseNodeId(const RefPtr<FrameNode>& dialogNode)
{
    CHECK_NULL_RETURN(dialogNode, false);
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    CHECK_NULL_RETURN(dialogPattern, false);
    auto dialogProps = dialogNode->GetLayoutProperty<DialogLayoutProperty>();
    CHECK_NULL_RETURN(dialogProps, false);
    return dialogPattern->IsUIExtensionSubWindow() && dialogProps->GetIsModal().value_or(true);
}

bool IsDialogNode(const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_RETURN(frameNode, false);
    return frameNode->GetPattern<DialogPattern>() != nullptr;
}

RefPtr<AceType> GetDialogInnerManager(const RefPtr<UINode>& rootNode)
{
    CHECK_NULL_RETURN(rootNode, nullptr);
    return AceType::MakeRefPtr<DialogInnerManager>(rootNode);
}

RefPtr<FrameNode> ShowDialog(const RefPtr<AceType>& dialogInnerManager, const RefPtr<OverlayManager>& overlayManager,
    const DialogProperties& dialogProps, std::function<void()>&& buildFunc, bool isRightToLeft)
{
    CHECK_NULL_RETURN(dialogInnerManager && overlayManager, nullptr);
    auto manager = AceType::DynamicCast<DialogInnerManager>(dialogInnerManager);
    CHECK_NULL_RETURN(manager, nullptr);
    return manager->ShowDialog(overlayManager, dialogProps, std::move(buildFunc), isRightToLeft);
}

RefPtr<FrameNode> ShowDialogWithErrorCallback(const RefPtr<AceType>& dialogInnerManager,
    const RefPtr<OverlayManager>& overlayManager, const DialogProperties& dialogProps,
    std::function<void()>&& buildFunc, bool isRightToLeft, std::function<void(int32_t, int32_t)> callback)
{
    CHECK_NULL_RETURN(dialogInnerManager && overlayManager, nullptr);
    auto manager = AceType::DynamicCast<DialogInnerManager>(dialogInnerManager);
    CHECK_NULL_RETURN(manager, nullptr);
    return manager->ShowDialogWithErrorCallback(
        overlayManager, dialogProps, std::move(buildFunc), isRightToLeft, std::move(callback));
}

RefPtr<FrameNode> ShowDialogWithNode(const RefPtr<AceType>& dialogInnerManager,
    const RefPtr<OverlayManager>& overlayManager, const DialogProperties& dialogProps, const RefPtr<UINode>& customNode,
    bool isRightToLeft)
{
    CHECK_NULL_RETURN(dialogInnerManager && overlayManager, nullptr);
    auto manager = AceType::DynamicCast<DialogInnerManager>(dialogInnerManager);
    CHECK_NULL_RETURN(manager, nullptr);
    return manager->ShowDialogWithNode(overlayManager, dialogProps, customNode, isRightToLeft);
}

RefPtr<FrameNode> ShowDialogWithNodeAndErrorCallback(const RefPtr<AceType>& dialogInnerManager,
    const RefPtr<OverlayManager>& overlayManager, const DialogProperties& dialogProps, const RefPtr<UINode>& customNode,
    bool isRightToLeft, std::function<void(int32_t, int32_t)> callback)
{
    CHECK_NULL_RETURN(dialogInnerManager && overlayManager, nullptr);
    auto manager = AceType::DynamicCast<DialogInnerManager>(dialogInnerManager);
    CHECK_NULL_RETURN(manager, nullptr);
    return manager->ShowDialogWithNodeAndErrorCallback(
        overlayManager, dialogProps, customNode, isRightToLeft, std::move(callback));
}

RefPtr<FrameNode> OpenCustomDialog(const RefPtr<AceType>& dialogInnerManager,
    const RefPtr<OverlayManager>& overlayManager, const DialogProperties& dialogProps,
    std::function<void(int32_t)>&& callback)
{
    CHECK_NULL_RETURN(dialogInnerManager && overlayManager, nullptr);
    auto manager = AceType::DynamicCast<DialogInnerManager>(dialogInnerManager);
    CHECK_NULL_RETURN(manager, nullptr);
    return manager->OpenCustomDialog(overlayManager, dialogProps, std::move(callback));
}

RefPtr<FrameNode> OpenCustomDialogWithErrorCallback(const RefPtr<AceType>& dialogInnerManager,
    const RefPtr<OverlayManager>& overlayManager, const DialogProperties& dialogProps,
    std::function<void(int32_t errorCode, int32_t dialogId)>&& callback)
{
    CHECK_NULL_RETURN(dialogInnerManager && overlayManager, nullptr);
    auto manager = AceType::DynamicCast<DialogInnerManager>(dialogInnerManager);
    CHECK_NULL_RETURN(manager, nullptr);
    return manager->OpenCustomDialogWithErrorCallback(overlayManager, dialogProps, std::move(callback));
}

void CloseCustomDialogWithId(const RefPtr<AceType>& dialogInnerManager, const RefPtr<OverlayManager>& overlayManager,
    const int32_t dialogId, std::function<void(int32_t)>&& callback)
{
    CHECK_NULL_VOID(dialogInnerManager && overlayManager);
    auto manager = AceType::DynamicCast<DialogInnerManager>(dialogInnerManager);
    CHECK_NULL_VOID(manager);
    manager->CloseCustomDialogWithId(overlayManager, dialogId, std::move(callback));
}

void CloseCustomDialogWithNode(const RefPtr<AceType>& dialogInnerManager, const RefPtr<OverlayManager>& overlayManager,
    const WeakPtr<NG::UINode>& node, std::function<void(int32_t)>&& callback)
{
    CHECK_NULL_VOID(dialogInnerManager && overlayManager);
    auto manager = AceType::DynamicCast<DialogInnerManager>(dialogInnerManager);
    CHECK_NULL_VOID(manager);
    manager->CloseCustomDialogWithNode(overlayManager, node, std::move(callback));
}

void UpdateCustomDialog(const RefPtr<AceType>& dialogInnerManager, const WeakPtr<NG::UINode>& node,
    const DialogProperties& dialogProps, std::function<void(int32_t)>&& callback)
{
    CHECK_NULL_VOID(dialogInnerManager);
    auto manager = AceType::DynamicCast<DialogInnerManager>(dialogInnerManager);
    CHECK_NULL_VOID(manager);
    manager->UpdateCustomDialog(node, dialogProps, std::move(callback));
}

void UpdateCustomDialogWithNode(const RefPtr<AceType>& dialogInnerManager, const WeakPtr<NG::UINode>& node,
    const DialogProperties& dialogProps, std::function<void(int32_t)>&& callback)
{
    CHECK_NULL_VOID(dialogInnerManager);
    auto manager = AceType::DynamicCast<DialogInnerManager>(dialogInnerManager);
    CHECK_NULL_VOID(manager);
    manager->UpdateCustomDialogWithNode(node, dialogProps, std::move(callback));
}

void ShowDateDialog(const RefPtr<AceType>& dialogInnerManager, const RefPtr<OverlayManager>& overlayManager,
    const DialogProperties& dialogProps, const DatePickerSettingData& settingData,
    std::map<std::string, NG::DialogEvent> dialogEvent, std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent,
    std::map<std::string, NG::DialogCancelEvent> dialogLifeCycleEvent, const std::vector<ButtonInfo>& buttonInfos)
{
    CHECK_NULL_VOID(dialogInnerManager && overlayManager);
    auto manager = AceType::DynamicCast<DialogInnerManager>(dialogInnerManager);
    CHECK_NULL_VOID(manager);
    manager->ShowDateDialog(overlayManager, dialogProps, settingData, std::move(dialogEvent),
        std::move(dialogCancelEvent), std::move(dialogLifeCycleEvent), buttonInfos);
}

void ShowTimeDialog(const RefPtr<AceType>& dialogInnerManager, const RefPtr<OverlayManager>& overlayManager,
    const DialogProperties& dialogProps, const TimePickerSettingData& settingData,
    std::map<std::string, PickerTime> timePickerProperty, std::map<std::string, NG::DialogEvent> dialogEvent,
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent,
    std::map<std::string, NG::DialogCancelEvent> dialogLifeCycleEvent, const std::vector<ButtonInfo>& buttonInfos)
{
    CHECK_NULL_VOID(dialogInnerManager && overlayManager);
    auto manager = AceType::DynamicCast<DialogInnerManager>(dialogInnerManager);
    CHECK_NULL_VOID(manager);
    manager->ShowTimeDialog(overlayManager, dialogProps, settingData, std::move(timePickerProperty),
        std::move(dialogEvent), std::move(dialogCancelEvent), std::move(dialogLifeCycleEvent), buttonInfos);
}

void ShowTextDialog(const RefPtr<AceType>& dialogInnerManager, const RefPtr<OverlayManager>& overlayManager,
    const DialogProperties& dialogProps, const TextPickerSettingData& settingData,
    std::map<std::string, NG::DialogTextEvent> dialogEvent,
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent,
    std::map<std::string, NG::DialogCancelEvent> dialogLifeCycleEvent, const std::vector<ButtonInfo>& buttonInfos)
{
    CHECK_NULL_VOID(dialogInnerManager && overlayManager);
    auto manager = AceType::DynamicCast<DialogInnerManager>(dialogInnerManager);
    CHECK_NULL_VOID(manager);
    manager->ShowTextDialog(overlayManager, dialogProps, settingData, std::move(dialogEvent),
        std::move(dialogCancelEvent), std::move(dialogLifeCycleEvent), buttonInfos);
}

void ShowCalendarDialog(const RefPtr<AceType>& dialogInnerManager, const RefPtr<OverlayManager>& overlayManager,
    const DialogProperties& dialogProps, const CalendarSettingData& settingData,
    std::map<std::string, NG::DialogEvent> dialogEvent, std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent,
    std::map<std::string, NG::DialogCancelEvent> dialogLifeCycleEvent, const std::vector<ButtonInfo>& buttonInfos)
{
    CHECK_NULL_VOID(dialogInnerManager && overlayManager);
    auto manager = AceType::DynamicCast<DialogInnerManager>(dialogInnerManager);
    CHECK_NULL_VOID(manager);
    manager->ShowCalendarDialog(overlayManager, dialogProps, settingData, std::move(dialogEvent),
        std::move(dialogCancelEvent), std::move(dialogLifeCycleEvent), buttonInfos);
}

void CloseDialog(const RefPtr<AceType>& dialogInnerManager, const RefPtr<OverlayManager>& overlayManager,
    const RefPtr<FrameNode>& dialogNode)
{
    CHECK_NULL_VOID(dialogInnerManager && overlayManager);
    auto manager = AceType::DynamicCast<DialogInnerManager>(dialogInnerManager);
    CHECK_NULL_VOID(manager);
    manager->CloseDialog(overlayManager, dialogNode);
}

bool RemoveDialog(const RefPtr<AceType>& dialogInnerManager, const RefPtr<OverlayManager>& overlayManager,
    const RefPtr<FrameNode>& overlay, bool isBackPressed, bool isPageRouter)
{
    CHECK_NULL_RETURN(dialogInnerManager && overlayManager, false);
    auto manager = AceType::DynamicCast<DialogInnerManager>(dialogInnerManager);
    CHECK_NULL_RETURN(manager, false);
    return manager->RemoveDialog(overlayManager, overlay, isBackPressed, isPageRouter);
}

bool RemoveDialogWithContent(const RefPtr<AceType>& dialogInnerManager, const RefPtr<OverlayManager>& overlayManager,
    const RefPtr<FrameNode>& overlay, const DialogProperties& props, bool isBackPressed, bool isPageRouter,
    int32_t subWindowId)
{
    CHECK_NULL_RETURN(dialogInnerManager && overlayManager, false);
    auto manager = AceType::DynamicCast<DialogInnerManager>(dialogInnerManager);
    CHECK_NULL_RETURN(manager, false);
    return manager->RemoveDialogWithContent(overlayManager, overlay, props, isBackPressed, isPageRouter, subWindowId);
}

bool RemoveDialogWithPressBack(const RefPtr<AceType>& dialogInnerManager, const RefPtr<OverlayManager>& overlayManager,
    const RefPtr<FrameNode>& overlay, const RefPtr<Pattern>& pattern, bool isBackPressed, bool isPageRouter,
    int32_t subWindowId)
{
    CHECK_NULL_RETURN(dialogInnerManager && overlayManager, false);
    auto manager = AceType::DynamicCast<DialogInnerManager>(dialogInnerManager);
    CHECK_NULL_RETURN(manager, false);
    return manager->RemoveDialogWithPressBack(
        overlayManager, overlay, pattern, isBackPressed, isPageRouter, subWindowId);
}

std::unordered_map<int32_t, RefPtr<FrameNode>> GetDialogMap(const RefPtr<AceType>& dialogInnerManager)
{
    CHECK_NULL_RETURN(dialogInnerManager, {});
    auto manager = AceType::DynamicCast<DialogInnerManager>(dialogInnerManager);
    CHECK_NULL_RETURN(manager, {});
    return manager->GetDialogMap();
}

RefPtr<FrameNode> GetDialogNodeWithExistContent(const RefPtr<AceType>& dialogInnerManager, const RefPtr<UINode>& node)
{
    CHECK_NULL_RETURN(dialogInnerManager, nullptr);
    auto manager = AceType::DynamicCast<DialogInnerManager>(dialogInnerManager);
    CHECK_NULL_RETURN(manager, nullptr);
    return manager->GetDialogNodeWithExistContent(node);
}

void ReloadBuilderNodeConfig(const RefPtr<AceType>& dialogInnerManager)
{
    CHECK_NULL_VOID(dialogInnerManager);
    auto manager = AceType::DynamicCast<DialogInnerManager>(dialogInnerManager);
    CHECK_NULL_VOID(manager);
    manager->ReloadBuilderNodeConfig();
}

void RemoveDialogFromMapForcefully(const RefPtr<AceType>& dialogInnerManager, const RefPtr<FrameNode>& node)
{
    CHECK_NULL_VOID(dialogInnerManager);
    auto manager = AceType::DynamicCast<DialogInnerManager>(dialogInnerManager);
    CHECK_NULL_VOID(manager);
    manager->RemoveDialogFromMapForcefully(node);
}

RefPtr<FrameNode> GetDialog(const RefPtr<AceType>& dialogInnerManager, int32_t dialogId)
{
    CHECK_NULL_RETURN(dialogInnerManager, nullptr);
    auto manager = AceType::DynamicCast<DialogInnerManager>(dialogInnerManager);
    CHECK_NULL_RETURN(manager, nullptr);
    return manager->GetDialog(dialogId);
}

void OnUIExtensionWindowSizeChange(const RefPtr<AceType>& dialogInnerManager)
{
    CHECK_NULL_VOID(dialogInnerManager);
    auto manager = AceType::DynamicCast<DialogInnerManager>(dialogInnerManager);
    CHECK_NULL_VOID(manager);
    manager->OnUIExtensionWindowSizeChange();
}

void SetMaskNodeId(const RefPtr<AceType>& dialogInnerManager, int32_t dialogId, int32_t maskId)
{
    CHECK_NULL_VOID(dialogInnerManager);
    auto manager = AceType::DynamicCast<DialogInnerManager>(dialogInnerManager);
    CHECK_NULL_VOID(manager);
    manager->SetMaskNodeId(dialogId, maskId);
}

bool IsMaskNode(const RefPtr<AceType>& dialogInnerManager, int32_t maskId)
{
    CHECK_NULL_RETURN(dialogInnerManager, false);
    auto manager = AceType::DynamicCast<DialogInnerManager>(dialogInnerManager);
    CHECK_NULL_RETURN(manager, false);
    return manager->IsMaskNode(maskId);
}

void PopModalDialog(const RefPtr<AceType>& dialogInnerManager, int32_t maskId, int32_t subWindowId)
{
    CHECK_NULL_VOID(dialogInnerManager);
    auto manager = AceType::DynamicCast<DialogInnerManager>(dialogInnerManager);
    CHECK_NULL_VOID(manager);
    manager->PopModalDialog(maskId, subWindowId);
}

int32_t GetMaskNodeIdWithDialogId(const RefPtr<AceType>& dialogInnerManager, int32_t dialogId)
{
    CHECK_NULL_RETURN(dialogInnerManager, -1);
    auto manager = AceType::DynamicCast<DialogInnerManager>(dialogInnerManager);
    CHECK_NULL_RETURN(manager, -1);
    return manager->GetMaskNodeIdWithDialogId(dialogId);
}

void RemoveMaskFromMap(const RefPtr<AceType>& dialogInnerManager, const RefPtr<FrameNode>& dialogNode)
{
    CHECK_NULL_VOID(dialogInnerManager);
    auto manager = AceType::DynamicCast<DialogInnerManager>(dialogInnerManager);
    CHECK_NULL_VOID(manager);
    manager->RemoveMaskFromMap(dialogNode);
}

void DumpMaskNodeIdMapInfo(const RefPtr<AceType>& dialogInnerManager)
{
    CHECK_NULL_VOID(dialogInnerManager);
    auto manager = AceType::DynamicCast<DialogInnerManager>(dialogInnerManager);
    CHECK_NULL_VOID(manager);
    manager->DumpMaskNodeIdMapInfo();
}

void RegisterOnHideDialog(const RefPtr<AceType>& dialogInnerManager, std::function<void()> callback)
{
    CHECK_NULL_VOID(dialogInnerManager);
    auto manager = AceType::DynamicCast<DialogInnerManager>(dialogInnerManager);
    CHECK_NULL_VOID(manager);
    manager->RegisterOnHideDialog(std::move(callback));
}

void FireNavigationLifecycle(const RefPtr<AceType>& dialogInnerManager, const RefPtr<UINode>& uiNode,
    int32_t lifecycleId, bool isLowerOnly, int32_t reason)
{
    CHECK_NULL_VOID(dialogInnerManager);
    auto manager = AceType::DynamicCast<DialogInnerManager>(dialogInnerManager);
    CHECK_NULL_VOID(manager);
    manager->FireNavigationLifecycle(uiNode, lifecycleId, isLowerOnly, reason);
}

void SetBackPressEvent(const RefPtr<AceType>& dialogInnerManager, std::function<bool()> event)
{
    CHECK_NULL_VOID(dialogInnerManager);
    auto manager = AceType::DynamicCast<DialogInnerManager>(dialogInnerManager);
    CHECK_NULL_VOID(manager);
    manager->SetBackPressEvent(std::move(event));
}

bool GetDialogFocusable(const RefPtr<FrameNode>& dialogNode)
{
    CHECK_NULL_RETURN(dialogNode, true);
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    CHECK_NULL_RETURN(dialogPattern, true);
    return dialogPattern->GetDialogProperties().focusable;
}

bool IsDialogPattern(const RefPtr<Pattern>& pattern)
{
    return AceType::InstanceOf<DialogPattern>(pattern);
}
} // namespace
namespace InnerModifier {

const ArkUIDialogInnerModifier* GetDialogInnerModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIDialogInnerModifier modifier = {
        .setCloseDialogForNDK = CustomDialogControllerModelNG::SetCloseDialogForNDK,
        .setOpenDialogWithNode = CustomDialogControllerModelNG::SetOpenDialogWithNode,
        .dismissDialog = DismissDialog,
        .isSupportBlurStyle = DialogView::IsSupportBlurStyle,
        .createDialogNode = CreateDialogNode,
        .createDialogNodeWithThemeNode = CreateDialogNodeWithThemeNode,
        .setIsPickerDialog = SetIsPickerDialog,
        .setState = SetState,
        .getState = GetState,
        .isCustomDialogValid = IsCustomDialogValid,
        .onThemeScopeUpdate = OnThemeScopeUpdate,
        .updateDialogOffset = UpdateDialogOffset,
        .getSubwindowShouldUseNodeId = GetSubwindowShouldUseNodeId,
        .isDialogNode = IsDialogNode,
        .getDialogInnerManager = GetDialogInnerManager,
        .showDialog = ShowDialog,
        .showDialogWithErrorCallback = ShowDialogWithErrorCallback,
        .showDialogWithNode = ShowDialogWithNode,
        .showDialogWithNodeAndErrorCallback = ShowDialogWithNodeAndErrorCallback,
        .openCustomDialog = OpenCustomDialog,
        .openCustomDialogWithErrorCallback = OpenCustomDialogWithErrorCallback,
        .closeCustomDialogWithId = CloseCustomDialogWithId,
        .closeCustomDialogWithNode = CloseCustomDialogWithNode,
        .updateCustomDialog = UpdateCustomDialog,
        .updateCustomDialogWithNode = UpdateCustomDialogWithNode,
        .showDateDialog = ShowDateDialog,
        .showTimeDialog = ShowTimeDialog,
        .showTextDialog = ShowTextDialog,
        .showCalendarDialog = ShowCalendarDialog,
        .closeDialog = CloseDialog,
        .removeDialog = RemoveDialog,
        .removeDialogWithContent = RemoveDialogWithContent,
        .removeDialogWithPressBack = RemoveDialogWithPressBack,
        .getDialogMap = GetDialogMap,
        .getDialogNodeWithExistContent = GetDialogNodeWithExistContent,
        .reloadBuilderNodeConfig = ReloadBuilderNodeConfig,
        .removeDialogFromMapForcefully = RemoveDialogFromMapForcefully,
        .getDialog = GetDialog,
        .onUIExtensionWindowSizeChange = OnUIExtensionWindowSizeChange,
        .setMaskNodeId = SetMaskNodeId,
        .isMaskNode = IsMaskNode,
        .popModalDialog = PopModalDialog,
        .getMaskNodeIdWithDialogId = GetMaskNodeIdWithDialogId,
        .removeMaskFromMap = RemoveMaskFromMap,
        .dumpMaskNodeIdMapInfo = DumpMaskNodeIdMapInfo,
        .registerOnHideDialog = RegisterOnHideDialog,
        .fireNavigationLifecycle = FireNavigationLifecycle,
        .setBackPressEvent = SetBackPressEvent,
        .getDialogFocusable = GetDialogFocusable,
        .isDialogPattern = IsDialogPattern,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}
} // namespace InnerModifier
} // namespace OHOS::Ace::NG
