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


#include "base/error/error_code.h"
#include "base/subwindow/subwindow_manager.h"
#include "core/common/ace_engine.h"
#include "core/common/container.h"
#include "frameworks/core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "core/components_ng/pattern/overlay/dialog_manager_static.h"
#include "core/components_ng/pattern/overlay/sheet_manager.h"
#include "core/components_ng/pattern/stage/page_pattern.h"

namespace OHOS::Ace {
SINGLETON_INSTANCE_IMPL(NG::DialogManagerStatic);
}

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t CALLBACK_ERRORCODE_CANCEL = 1;
constexpr int32_t CALLBACK_DATACODE_ZERO = 0;
} // namespace

DialogManagerStatic::DialogManagerStatic() = default;

DialogManagerStatic::~DialogManagerStatic() = default;

void DialogManagerStatic::ShowInEmbeddedOverlay(std::function<void(RefPtr<NG::OverlayManager>)>&& task,
    const std::string& name, int32_t uniqueId)
{
    auto currentId = Container::CurrentId();
    ContainerScope scope(currentId);
    auto context = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto overlayManager = context->GetOverlayManager();
    auto embeddedOverlay = GetEmbeddedOverlay(uniqueId, context);
    if (embeddedOverlay) {
        overlayManager = embeddedOverlay;
    }
    context->GetTaskExecutor()->PostTask(
        [task = std::move(task), weak = WeakPtr<NG::OverlayManager>(overlayManager)] {
            auto overlayManager = weak.Upgrade();
            task(overlayManager);
        },
        TaskExecutor::TaskType::UI, name);
}

RefPtr<OverlayManager> DialogManagerStatic::FindPageNodeOverlay(const RefPtr<FrameNode>& currentNode)
{
    if (currentNode == nullptr || !currentNode->IsOnMainTree()) {
        TAG_LOGE(AceLogTag::ACE_DIALOG, "dialog node does not exist or not on main tree.");
    } else {
        return SheetManager::FindPageNodeOverlay(currentNode, true, true);
    }
    return nullptr;
}

RefPtr<OverlayManager> DialogManagerStatic::GetEmbeddedOverlay(int32_t uniqueId, const RefPtr<PipelineContext>& context)
{
    CHECK_NULL_RETURN(context, nullptr);
    if (uniqueId >= 0) {
        auto currentNode = ElementRegister::GetInstance()->GetSpecificItemById<NG::FrameNode>(uniqueId);
        if (currentNode == nullptr || !currentNode->IsOnMainTree()) {
            TAG_LOGE(AceLogTag::ACE_DIALOG, "Level uniqueId/%{public}d does not exist or not on main tree.", uniqueId);
        } else {
            auto getOverlayManager = FindPageNodeOverlay(currentNode);
            if (getOverlayManager) {
                return getOverlayManager;
            } else {
                TAG_LOGE(AceLogTag::ACE_DIALOG, "Level uniqueId/%{public}d can not get overlay manager.", uniqueId);
            }
        }
    } else {
        auto stateMgr = context->GetStageManager();
        if (stateMgr && stateMgr->GetLastPage()) {
            auto pagePattern = stateMgr->GetLastPage()->GetPattern<NG::PagePattern>();
            if (pagePattern) {
                pagePattern->CreateOverlayManager(true);
                return pagePattern->GetOverlayManager();
            }
        } else {
            TAG_LOGE(AceLogTag::ACE_DIALOG, "Can not get current page");
        }
    }
    return nullptr;
}

RefPtr<OverlayManager> DialogManagerStatic::GetEmbeddedOverlayWithNode(const RefPtr<UINode>& dialogNode)
{
    CHECK_NULL_RETURN(dialogNode, nullptr);
    auto parent = dialogNode->GetParent();
    CHECK_NULL_RETURN(parent, nullptr);
    auto parentNode = AceType::DynamicCast<FrameNode>(parent);
    CHECK_NULL_RETURN(parentNode, nullptr);
    if (parentNode->GetTag() == V2::PAGE_ETS_TAG) {
        auto pattern = parentNode->GetPattern<PagePattern>();
        CHECK_NULL_RETURN(pattern, nullptr);
        return pattern->GetOverlayManager();
    } else if (parentNode->GetTag() == V2::NAVDESTINATION_VIEW_ETS_TAG) {
        auto pattern = parentNode->GetPattern<NavDestinationPattern>();
        CHECK_NULL_RETURN(pattern, nullptr);
        return pattern->GetOverlayManager();
    }
    return nullptr;
}

RefPtr<UINode> DialogManagerStatic::GetDialogNodeByContentNode(const RefPtr<UINode>& currentNode)
{
    RefPtr<UINode> parent = currentNode;
    while (parent) {
        if (parent->GetTag() == V2::DIALOG_ETS_TAG) {
            break;
        }
        parent = parent->GetParent();
    }
    return parent;
}

void DialogManagerStatic::MainWindowOverlayStatic(std::function<void(RefPtr<NG::OverlayManager>)>&& task,
    const std::string& name, const RefPtr<NG::OverlayManager>& overlay, const int32_t containerId)
{
    ContainerScope scope(containerId);
    auto context = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto overlayManager = context->GetOverlayManager();
    if (overlay) {
        overlayManager = overlay;
    }
    context->GetTaskExecutor()->PostTask(
        [task = std::move(task), weak = WeakPtr<NG::OverlayManager>(overlayManager)] {
            task(weak.Upgrade());
        },
        TaskExecutor::TaskType::UI, name);
}

void DialogManagerStatic::ShowToastStatic(const NG::ToastInfo& toastInfo, std::function<void(int32_t)>&& callback,
    const int32_t containerId)
{
    auto currentId = containerId;
    if (containerId < 0) {
        currentId = Container::CurrentId();
    }
    auto task = [toastInfo, callbackParam = std::move(callback), currentId](
        const RefPtr<NG::OverlayManager>& overlayManager) {
        CHECK_NULL_VOID(overlayManager);
        ContainerScope scope(currentId);
        overlayManager->ShowToast(
            toastInfo, std::move(const_cast<std::function<void(int32_t)>&&>(callbackParam)));
    };
    MainWindowOverlayStatic(std::move(task), "ArkUIOverlayShowToast", nullptr, currentId);
}

void DialogManagerStatic::CloseToastStatic(const int32_t toastId, std::function<void(int32_t)>&& callback,
    const int32_t containerId)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "close toast enter");
    auto currentId = containerId;
    if (containerId < 0) {
        currentId = Container::CurrentId();
    }
    ContainerScope scope(currentId);
    auto context = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto overlayManager = context->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    overlayManager->CloseToast(toastId, std::move(callback));
}

void DialogManagerStatic::ShowDialogStatic(DialogProperties& dialogProps,
    std::function<void(int32_t, int32_t)>&& callback, const int32_t containerId)
{
    TAG_LOGD(AceLogTag::ACE_DIALOG, "Show dialog static enter.");
    auto currentId = containerId;
    if (containerId < 0) {
        currentId = Container::CurrentId();
    }

    dialogProps.onSuccess = std::move(callback);
    dialogProps.onCancel = [callback, currentId] {
        ContainerScope scope(currentId);
        auto context = NG::PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(context);
        auto task = [callback]() {
            callback(CALLBACK_ERRORCODE_CANCEL, CALLBACK_DATACODE_ZERO);
        };
        context->GetTaskExecutor()->PostTask(
            std::move(task), TaskExecutor::TaskType::UI, "ArkUIOverlayShowDialogCancel");
    };

    auto task = [dialogProps, currentId](const RefPtr<NG::OverlayManager>& overlayManager) {
        TAG_LOGI(AceLogTag::ACE_DIALOG, "Begin to show dialog static.");
        CHECK_NULL_VOID(overlayManager);
        auto container = AceEngine::Get().GetContainer(currentId);
        CHECK_NULL_VOID(container);
        if (container->IsSubContainer()) {
            auto parentContainerId = SubwindowManager::GetInstance()->GetParentContainerId(currentId);
            container = AceEngine::Get().GetContainer(parentContainerId);
            CHECK_NULL_VOID(container);
        }

        if (!dialogProps.isShowInSubWindow) {
            overlayManager->ShowDialog(dialogProps, nullptr, AceApplicationInfo::GetInstance().IsRightToLeft());
            return;
        }

        auto dialog = SubwindowManager::GetInstance()->ShowDialogNG(dialogProps, nullptr);
        CHECK_NULL_VOID(dialog);
        if (dialogProps.isModal && !container->IsUIExtensionWindow()) {
            DialogProperties maskProps = {
                .autoCancel = dialogProps.autoCancel,
                .isMask = true,
            };
            auto mask = overlayManager->ShowDialog(maskProps, nullptr, false);
            CHECK_NULL_VOID(mask);
            overlayManager->SetMaskNodeId(dialog->GetId(), mask->GetId());
        }
    };

    if (dialogProps.dialogLevelMode == LevelMode::EMBEDDED) {
        ShowInEmbeddedOverlay(std::move(task), "ArkUIOverlayShowDialog", dialogProps.dialogLevelUniqueId);
    } else {
        MainWindowOverlayStatic(std::move(task), "ArkUIOverlayShowDialog", nullptr, currentId);
    }
}

void DialogManagerStatic::ShowActionMenuStatic(DialogProperties& dialogProps,
    std::function<void(int32_t, int32_t)>&& callback, const int32_t containerId)
{
    TAG_LOGD(AceLogTag::ACE_DIALOG, "Show dialog static enter.");
    auto currentId = containerId;
    if (containerId < 0) {
        currentId = Container::CurrentId();
    }

    dialogProps.onSuccess = std::move(callback);
    dialogProps.onCancel = [callback, currentId] {
        ContainerScope scope(currentId);
        auto context = NG::PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(context);
        auto task = [callback]() {
            callback(CALLBACK_ERRORCODE_CANCEL, CALLBACK_DATACODE_ZERO);
        };
        context->GetTaskExecutor()->PostTask(
            std::move(task), TaskExecutor::TaskType::UI, "ArkUIOverlayShowActionMenuCancel");
    };

    auto task = [dialogProps, currentId](const RefPtr<NG::OverlayManager>& overlayManager) {
        TAG_LOGI(AceLogTag::ACE_DIALOG, "Begin to show actionMenu static.");
        CHECK_NULL_VOID(overlayManager);
        auto container = AceEngine::Get().GetContainer(currentId);
        CHECK_NULL_VOID(container);
        if (container->IsSubContainer()) {
            auto parentContainerId = SubwindowManager::GetInstance()->GetParentContainerId(currentId);
            container = AceEngine::Get().GetContainer(parentContainerId);
            CHECK_NULL_VOID(container);
        }

        if (!dialogProps.isShowInSubWindow) {
            overlayManager->ShowDialog(dialogProps, nullptr, AceApplicationInfo::GetInstance().IsRightToLeft());
            return;
        }

        RefPtr<NG::FrameNode> dialog = SubwindowManager::GetInstance()->ShowDialogNG(dialogProps, nullptr);
        CHECK_NULL_VOID(dialog);
        if (dialogProps.isModal && !container->IsUIExtensionWindow()) {
            DialogProperties maskProps = {
                .autoCancel = dialogProps.autoCancel,
                .isMask = true,
            };
            auto mask = overlayManager->ShowDialog(maskProps, nullptr, false);
            CHECK_NULL_VOID(mask);
            overlayManager->SetMaskNodeId(dialog->GetId(), mask->GetId());
        }
    };

    if (dialogProps.dialogLevelMode == LevelMode::EMBEDDED) {
        ShowInEmbeddedOverlay(std::move(task), "ArkUIOverlayShowActionMenuInner", dialogProps.dialogLevelUniqueId);
    } else {
        MainWindowOverlayStatic(std::move(task), "ArkUIOverlayShowActionMenuInner", nullptr, currentId);
    }
}

void DialogManagerStatic::OpenCustomDialogStatic(DialogProperties& dialogProps,
    std::function<void(int32_t)>&& callback, const int32_t containerId)
{
    TAG_LOGD(AceLogTag::ACE_DIALOG, "Open custom dialog static enter.");
    auto currentId = containerId;
    if (containerId < 0) {
        currentId = Container::CurrentId();
    }

    auto task = [dialogProps, callback](const RefPtr<NG::OverlayManager>& overlayManager) mutable {
        CHECK_NULL_VOID(overlayManager);
        TAG_LOGI(AceLogTag::ACE_DIALOG, "Begin to open custom dialog static.");
        auto container = Container::Current();
        CHECK_NULL_VOID(container);
        if (dialogProps.isShowInSubWindow) {
            SubwindowManager::GetInstance()->OpenCustomDialogNG(dialogProps, std::move(callback));
            if (dialogProps.isModal) {
                TAG_LOGW(AceLogTag::ACE_OVERLAY, "Temporary not support isShowInSubWindow and isModal.");
            }
        } else {
            overlayManager->OpenCustomDialog(dialogProps, std::move(callback));
        }
    };

    if (dialogProps.dialogLevelMode == LevelMode::EMBEDDED) {
        ShowInEmbeddedOverlay(std::move(task), "ArkUIOverlayShowDialog", dialogProps.dialogLevelUniqueId);
    } else {
        MainWindowOverlayStatic(std::move(task), "ArkUIOverlayShowDialog", nullptr, currentId);
    }
}

void DialogManagerStatic::UpdateCustomDialogStatic(const WeakPtr<NG::UINode>& node, DialogProperties& dialogProps,
    std::function<void(int32_t)>&& callback)
{
    TAG_LOGD(AceLogTag::ACE_DIALOG, "Update custom dialog static enter.");
    auto nodePtr = node.Upgrade();
    CHECK_NULL_VOID(nodePtr);
    auto context = nodePtr->GetContextWithCheck();
    CHECK_NULL_VOID(context);
    auto overlayManager = context->GetOverlayManager();
    auto task = [node, dialogProps, callback, weak = WeakPtr<NG::OverlayManager>(overlayManager)]() mutable {
        auto overlayManager = weak.Upgrade();
        CHECK_NULL_VOID(overlayManager);
        TAG_LOGI(AceLogTag::ACE_OVERLAY, "Begin to update custom dialog static.");
        overlayManager->UpdateCustomDialog(node, dialogProps, std::move(callback));
    };
    context->GetTaskExecutor()->PostTask(
        std::move(task), TaskExecutor::TaskType::UI, "ArkUIOverlayUpdateCustomDialog");
}

void DialogManagerStatic::CloseCustomDialogStatic(const int32_t dialogId, const int32_t containerId)
{
    TAG_LOGD(AceLogTag::ACE_DIALOG, "Close custom dialog static enter.");
    auto currentId = containerId;
    if (containerId < 0) {
        currentId = Container::CurrentId();
    }

    auto task = [dialogId](const RefPtr<NG::OverlayManager>& overlayManager) {
        CHECK_NULL_VOID(overlayManager);
        TAG_LOGI(AceLogTag::ACE_OVERLAY, "Begin to close custom dialog static.");
        overlayManager->CloseCustomDialog(dialogId);
        SubwindowManager::GetInstance()->CloseCustomDialogNG(dialogId);
    };
    auto dialogNode = FrameNode::GetFrameNodeOnly(V2::DIALOG_ETS_TAG, dialogId);
    auto currentOverlay = GetEmbeddedOverlayWithNode(dialogNode);
    MainWindowOverlayStatic(std::move(task), "ArkUIOverlayCloseCustomDialog", currentOverlay, currentId);
}

void DialogManagerStatic::CloseCustomDialogStatic(const WeakPtr<NG::UINode>& node,
    std::function<void(int32_t)> &&callback)
{
    TAG_LOGD(AceLogTag::ACE_DIALOG, "Close custom dialog static enter.");
    auto nodePtr = node.Upgrade();
    CHECK_NULL_VOID(nodePtr);
    auto context = nodePtr->GetContextWithCheck();
    CHECK_NULL_VOID(context);
    auto overlayManager = context->GetOverlayManager();
    auto parent = GetDialogNodeByContentNode(nodePtr);
    if (parent) {
        auto currentOverlay = GetEmbeddedOverlayWithNode(parent);
        if (currentOverlay) {
            overlayManager = currentOverlay;
        }
    }

    auto task = [node, callback, weak = WeakPtr<NG::OverlayManager>(overlayManager)]() mutable {
        auto overlayManager = weak.Upgrade();
        CHECK_NULL_VOID(overlayManager);
        TAG_LOGI(AceLogTag::ACE_OVERLAY, "Begin to close custom dialog static.");
        overlayManager->CloseCustomDialog(node, std::move(callback));
    };
    context->GetTaskExecutor()->PostTask(std::move(task), TaskExecutor::TaskType::UI, "ArkUIOverlayCloseCustomDialog");
}

void DialogManagerStatic::RemoveCustomDialog(int32_t instanceId)
{
    TAG_LOGI(AceLogTag::ACE_DIALOG, "Dismiss custom dialog, instanceId: %{public}d", instanceId);
    ContainerScope scope(instanceId);
    NG::ViewAbstract::DismissDialog();
}
} // namespace OHOS::Ace::NG
