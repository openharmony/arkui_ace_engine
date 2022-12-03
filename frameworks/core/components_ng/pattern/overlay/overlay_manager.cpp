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

#include "core/components_ng/pattern/overlay/overlay_manager.h"

#include <utility>

#include "base/utils/utils.h"
#include "core/components/common/properties/color.h"
#include "core/components/toast/toast_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/bubble/bubble_event_hub.h"
#include "core/components_ng/pattern/custom/custom_node.h"
#include "core/components_ng/pattern/dialog/dialog_view.h"
#include "core/components_ng/pattern/menu/menu_layout_property.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/picker/datepicker_dialog_view.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_picker/textpicker_dialog_view.h"
#include "core/components_ng/pattern/time_picker/timepicker_dialog_view.h"
#include "core/components_ng/pattern/time_picker/timepicker_view.h"
#include "core/components_ng/pattern/toast/toast_view.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {

void OverlayManager::ShowToast(
    const std::string& message, int32_t duration, const std::string& bottom, bool isRightToLeft)
{
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_VOID(rootNode);

    // only one toast
    if (!toast_.Invalid()) {
        rootNode->RemoveChild(toast_.Upgrade());
        rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }

    auto toastNode = ToastView::CreateToastNode(message, bottom, isRightToLeft);
    CHECK_NULL_VOID(toastNode);

    // mount to parent
    toastNode->MountToParent(rootNode);
    rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    toast_ = toastNode;

    context->GetTaskExecutor()->PostDelayedTask(
        [weak = WeakClaim(this)] {
            auto overlayManager = weak.Upgrade();
            CHECK_NULL_VOID(overlayManager);
            overlayManager->PopToast();
        },
        TaskExecutor::TaskType::UI, duration);
}

void OverlayManager::PopToast()
{
    auto toastUnderPop = toast_.Upgrade();
    CHECK_NULL_VOID(toastUnderPop);
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_VOID(rootNode);
    LOGI("begin to pop toast, id is %{public}d", toastUnderPop->GetId());
    rootNode->RemoveChild(toastUnderPop);
    rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void OverlayManager::UpdatePopupNode(int32_t targetId, const PopupInfo& popupInfo)
{
    popupMap_[targetId] = popupInfo;
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_VOID(rootNode);
    if (!popupInfo.markNeedUpdate || !popupInfo.popupNode) {
        return;
    }
    popupMap_[targetId].markNeedUpdate = false;
    auto rootChildren = rootNode->GetChildren();
    auto iter = std::find(rootChildren.begin(), rootChildren.end(), popupInfo.popupNode);
    if (iter != rootChildren.end()) {
        // Pop popup
        if (!popupInfo.isCurrentOnShow) {
            return;
        }
        LOGI("begin pop");
        popupInfo.popupNode->GetEventHub<BubbleEventHub>()->FireChangeEvent(false);
        rootNode->RemoveChild(popupMap_[targetId].popupNode);
    } else {
        // Push popup
        if (popupInfo.isCurrentOnShow) {
            return;
        }
        LOGI("begin push");
        popupInfo.popupNode->GetEventHub<BubbleEventHub>()->FireChangeEvent(true);
        popupMap_[targetId].popupNode->MountToParent(rootNode);
    }
    popupMap_[targetId].isCurrentOnShow = !popupInfo.isCurrentOnShow;
    rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void OverlayManager::HidePopup(int32_t targetId, const PopupInfo& popupInfo)
{
    popupMap_[targetId] = popupInfo;
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_VOID(rootNode);
    if (!popupInfo.markNeedUpdate || !popupInfo.popupNode) {
        return;
    }
    popupMap_[targetId].markNeedUpdate = false;
    auto rootChildren = rootNode->GetChildren();
    auto iter = std::find(rootChildren.begin(), rootChildren.end(), popupInfo.popupNode);
    if (iter == rootChildren.end()) {
        LOGW("OverlayManager: popupNode is not found in rootChildren");
        return;
    }
    if (!popupInfo.isCurrentOnShow) {
        return;
    }
    LOGI("begin pop");
    popupInfo.popupNode->GetEventHub<BubbleEventHub>()->FireChangeEvent(false);
    rootNode->RemoveChild(popupMap_[targetId].popupNode);
    popupMap_[targetId].isCurrentOnShow = !popupInfo.isCurrentOnShow;
    rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

bool OverlayManager::ShowMenuHelper(RefPtr<FrameNode>& menu, int32_t targetId, const NG::OffsetF& offset)
{
    if (!menu) {
        // get existing menuNode
        auto it = menuMap_.find(targetId);
        if (it != menuMap_.end()) {
            menu = it->second;
        } else {
            LOGW("menuNode doesn't exists %{public}d", targetId);
        }
    } else {
        // creating new menu
        menuMap_[targetId] = menu;
        LOGI("menuNode %{public}d added to map", targetId);
    }
    CHECK_NULL_RETURN(menu, false);
    auto menuChild = menu->GetChildAtIndex(0);
    CHECK_NULL_RETURN(menuChild, false);
    auto menuFrameNode = DynamicCast<FrameNode>(menuChild);

    auto props = menuFrameNode->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_RETURN(props, false);
    props->UpdateMenuOffset(offset);
    menuFrameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    return true;
}

void OverlayManager::ShowMenu(int32_t targetId, const NG::OffsetF& offset, RefPtr<FrameNode> menu)
{
    if (!ShowMenuHelper(menu, targetId, offset)) {
        LOGW("show menu failed");
        return;
    }
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_VOID(rootNode);
    auto rootChildren = rootNode->GetChildren();
    auto iter = std::find(rootChildren.begin(), rootChildren.end(), menu);
    // menuNode already showing
    if (iter != rootChildren.end()) {
        LOGW("menuNode already appended");
    } else {
        menu->MountToParent(rootNode);
        menu->MarkModifyDone();
        rootNode->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
        LOGI("menuNode mounted");
    }
}

// subwindow only contains one menu instance.
void OverlayManager::ShowMenuInSubWindow(int32_t targetId, const NG::OffsetF& offset, RefPtr<FrameNode> menu)
{
    if (!ShowMenuHelper(menu, targetId, offset)) {
        LOGW("show menu failed");
        return;
    }
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_VOID(rootNode);
    rootNode->Clean();
    menu->MountToParent(rootNode);
    menu->MarkModifyDone();
    rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    LOGI("menuNode mounted in subwindow");
}

void OverlayManager::HideMenu(int32_t targetId)
{
    LOGI("OverlayManager::HideMenuNode");
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_VOID(rootNode);
    if (menuMap_.find(targetId) == menuMap_.end()) {
        LOGW("OverlayManager: menuNode %{public}d not found in map", targetId);
        return;
    }
    rootNode->RemoveChild(menuMap_[targetId]);
    rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void OverlayManager::DeleteMenu(int32_t targetId)
{
    LOGI("OverlayManager::DeleteMenuNode");
    auto it = menuMap_.find(targetId);
    if (it == menuMap_.end()) {
        LOGW("OverlayManager: menuNode %{public}d doesn't exist", targetId);
        return;
    }
    menuMap_.erase(it);
}

void OverlayManager::CleanMenuInSubWindow()
{
    LOGI("OverlayManager::CleanMenuInSubWindow");
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_VOID(rootNode);
    rootNode->Clean();
    rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

RefPtr<FrameNode> OverlayManager::ShowDialog(
    const DialogProperties& dialogProps, const RefPtr<UINode>& customNode, bool isRightToLeft)
{
    LOGI("OverlayManager::ShowDialog");
    auto dialog = DialogView::CreateDialogNode(dialogProps, customNode);
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_RETURN(rootNode, nullptr);
    dialog->MountToParent(rootNode);
    LOGD("dialog mounted to root node");
    rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    return dialog;
}

void OverlayManager::ShowDateDialog(const DialogProperties& dialogProps,
    std::map<std::string, PickerDate> datePickerProperty, bool isLunar,
    std::map<std::string, NG::DialogEvent> dialogEvent, std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent)
{
    auto dialogNode = DatePickerDialogView::Show(
        dialogProps, std::move(datePickerProperty), isLunar, std::move(dialogEvent), std::move(dialogCancelEvent));
    CHECK_NULL_VOID(dialogNode);
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_VOID(rootNode);
    dialogNode->MountToParent(rootNode);
    rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void OverlayManager::ShowTimeDialog(const DialogProperties& dialogProps,
    std::map<std::string, PickerTime> timePickerProperty, bool isUseMilitaryTime,
    std::map<std::string, NG::DialogEvent> dialogEvent, std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent)
{
    auto dialogNode = TimePickerDialogView::Show(dialogProps, std::move(timePickerProperty), isUseMilitaryTime,
        std::move(dialogEvent), std::move(dialogCancelEvent));
    CHECK_NULL_VOID(dialogNode);
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_VOID(rootNode);
    dialogNode->MountToParent(rootNode);
    rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void OverlayManager::ShowTextDialog(const DialogProperties& dialogProps, uint32_t selected, const Dimension& height,
    const std::vector<std::string>& getRangeVector, std::map<std::string, NG::DialogTextEvent> dialogEvent,
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent)
{
    auto dialogNode = TextPickerDialogView::Show(
        dialogProps, selected, height, getRangeVector, std::move(dialogEvent), std::move(dialogCancelEvent));
    CHECK_NULL_VOID(dialogNode);
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_VOID(rootNode);
    dialogNode->MountToParent(rootNode);
    rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void OverlayManager::CloseDialog(const RefPtr<FrameNode>& dialogNode)
{
    LOGI("OverlayManager::CloseDialog");
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_VOID(rootNode);
    rootNode->RemoveChild(dialogNode);
    rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void OverlayManager::CloseDialog(int32_t id)
{
    LOGI("OverlayManager::CloseDialog");
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_VOID(rootNode);
    auto index = rootNode->GetChildIndexById(id);
    if (index >= 0) {
        rootNode->RemoveChildAtIndex(index);
    }
    rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

bool OverlayManager::RemoveOverlay()
{
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_RETURN(rootNode, true);
    if (rootNode->GetChildren().size() > 1) {
        // stage node is at index 0
        rootNode->RemoveChildAtIndex(1);
        rootNode->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
        LOGI("overlay removed successfully");
        return true;
    }
    return false;
}

} // namespace OHOS::Ace::NG
