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

#include "base/utils/utils.h"
#include "core/components/common/properties/color.h"
#include "core/components/toast/toast_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/custom/custom_node.h"
#include "core/components_ng/pattern/dialog/dialog_view.h"
#include "core/components_ng/pattern/menu/menu_layout_property.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/toast/toast_view.h"

namespace OHOS::Ace::NG {

void OverlayManager::ShowToast(
    const std::string& message, int32_t duration, const std::string& bottom, bool isRightToLeft)
{
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_VOID(rootNode);

    // only one toast
    if (toastInfo_.toastNode) {
        rootNode->RemoveChild(toastInfo_.toastNode);
        rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }

    auto toastNode = ToastView::CreateToastNode(message, bottom, isRightToLeft);
    auto toastId = toastNode->GetId();
    ToastInfo info = { toastId, toastNode };
    toastInfo_ = info;

    // mount to parent
    toastNode->MountToParent(rootNode);
    toastNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);

    context->GetTaskExecutor()->PostDelayedTask(
        [weak = WeakClaim(this), toastId] {
            LOGI("begin pop toast, id is %{public}d", toastId);
            auto overlayManager = weak.Upgrade();
            CHECK_NULL_VOID(overlayManager);
            overlayManager->PopToast(toastId);
        },
        TaskExecutor::TaskType::UI, duration);
}

void OverlayManager::PopToast(int32_t toastId)
{
    RefPtr<UINode> toastUnderPop;
    if (toastId != toastInfo_.toastId) {
        return;
    }
    toastUnderPop = toastInfo_.toastNode;
    if (!toastUnderPop) {
        LOGE("No toast under pop");
        return;
    }
    auto rootNode = rootNodeWeak_.Upgrade();
    if (!rootNode) {
        LOGE("No root node in OverlayManager");
        return;
    }
    LOGI("begin to pop toast, id is %{public}d", toastId);
    rootNode->RemoveChild(toastUnderPop);
    rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void OverlayManager::UpdatePopupNode(int32_t targetId, const PopupInfo& popup)
{
    popupMap_[targetId] = popup;
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_VOID(rootNode);
    if (!popup.markNeedUpdate || !popup.popupNode) {
        return;
    }
    popupMap_[targetId].markNeedUpdate = false;
    auto rootChildren = rootNode->GetChildren();
    auto iter = std::find(rootChildren.begin(), rootChildren.end(), popup.popupNode);
    if (iter != rootChildren.end()) {
        // Pop popup
        if (!popup.isCurrentOnShow) {
            return;
        }
        LOGI("begin pop");
        rootNode->RemoveChild(popup.popupNode);
    } else {
        // Push popup
        if (popup.isCurrentOnShow) {
            return;
        }
        LOGE("begin push");
        popupMap_[targetId].popupNode->MountToParent(rootNode);
    }
    popupMap_[targetId].isCurrentOnShow = !popup.isCurrentOnShow;
    rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void OverlayManager::ShowMenu(int32_t targetId, RefPtr<FrameNode> menu)
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
        rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        LOGI("menuNode mounted");
    }
}

void OverlayManager::HideMenu(int32_t targetId)
{
    LOGI("OverlayManager::HideMenuNode");
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_VOID(rootNode);
    if (menuMap_.find(targetId) == menuMap_.end()) {
        LOGE("OverlayManager: menuNode %{public}d not found in map", targetId);
    }
    rootNode->RemoveChild(menuMap_[targetId]);
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

void OverlayManager::CloseDialog(RefPtr<FrameNode> dialogNode)
{
    LOGI("OverlayManager::CloseDialog");
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_VOID(rootNode);
    rootNode->RemoveChild(dialogNode);
    rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

} // namespace OHOS::Ace::NG
