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

#include <cstdint>
#include <utility>

#include "base/geometry/ng/offset_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/animation/animation_pub.h"
#include "core/common/container.h"
#include "core/components/common/properties/color.h"
#include "core/components/select/select_theme.h"
#include "core/components/toast/toast_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/bubble/bubble_event_hub.h"
#include "core/components_ng/pattern/bubble/bubble_pattern.h"
#include "core/components_ng/pattern/custom/custom_node.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_view.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_pattern.h"
#include "core/components_ng/pattern/menu/menu_layout_property.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"
#include "core/components_ng/pattern/picker/datepicker_dialog_view.h"
#include "core/components_ng/pattern/stage/stage_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_picker/textpicker_dialog_view.h"
#include "core/components_ng/pattern/time_picker/timepicker_dialog_view.h"
#include "core/components_ng/pattern/toast/toast_view.h"
#include "core/components_ng/property/property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/pipeline_base.h"
#include "core/pipeline/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
// should be moved to theme.
constexpr int32_t TOAST_ANIMATION_DURATION = 100;
constexpr int32_t MENU_ANIMATION_DURATION = 150;
constexpr float TOAST_ANIMATION_POSITION = 15.0f;

// dialog animation params
const RefPtr<Curve> SHOW_SCALE_ANIMATION_CURVE = AceType::MakeRefPtr<CubicCurve>(0.38f, 1.33f, 0.6f, 1.0f);

void OnDialogCloseEvent(const RefPtr<UINode>& root, const RefPtr<FrameNode>& node)
{
    CHECK_NULL_VOID(root && node);
    auto dialogPattern = node->GetPattern<DialogPattern>();
    CHECK_NULL_VOID(dialogPattern);
    auto option = dialogPattern->GetCloseAnimation().value_or(AnimationOption());
    auto onFinish = option.GetOnFinishEvent();

    auto dialogLayoutProp = dialogPattern->GetLayoutProperty<DialogLayoutProperty>();
    bool isShowInSubWindow = false;
    if (dialogLayoutProp) {
        isShowInSubWindow = dialogLayoutProp->GetShowInSubWindowValue(false);
    }
    if (onFinish != nullptr) {
        onFinish();
    }

    root->RemoveChild(node);
    root->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    auto lastChild = AceType::DynamicCast<FrameNode>(root->GetLastChild());
    if (lastChild) {
        auto pattern = lastChild->GetPattern();
        if (!AceType::InstanceOf<StagePattern>(pattern)) {
            LOGI("root has other overlay children.");
            return;
        }
    }

    auto container = Container::Current();
    CHECK_NULL_VOID_NOLOG(container);
    if (container->IsDialogContainer() || (container->IsSubContainer() && isShowInSubWindow)) {
        SubwindowManager::GetInstance()->HideSubWindowNG();
    }
}
} // namespace

void OverlayManager::OpenDialogAnimation(const RefPtr<FrameNode>& node)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<DialogTheme>();
    CHECK_NULL_VOID(theme);

    auto root = rootNodeWeak_.Upgrade();
    CHECK_NULL_VOID(root && node);
    node->MountToParent(root);
    root->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);

    AnimationOption option;
    // default opacity animation params
    option.SetCurve(Curves::SHARP);
    option.SetDuration(theme->GetOpacityAnimationDurIn());
    option.SetFillMode(FillMode::FORWARDS);

    auto dialogPattern = node->GetPattern<DialogPattern>();
    option = dialogPattern->GetOpenAnimation().value_or(option);
    auto onFinish = option.GetOnFinishEvent();

    option.SetOnFinishEvent(
        [weak = WeakClaim(this), nodeWK = WeakClaim(RawPtr(node)), id = Container::CurrentId(), onFinish] {
            auto node = nodeWK.Upgrade();
            auto overlayManager = weak.Upgrade();
            CHECK_NULL_VOID(node && overlayManager);
            ContainerScope scope(id);
            overlayManager->FocusOverlayNode(node);

            if (onFinish != nullptr) {
                onFinish();
            }
        });
    auto ctx = node->GetRenderContext();
    CHECK_NULL_VOID(ctx);
    ctx->OpacityAnimation(option, theme->GetOpacityStart(), theme->GetOpacityEnd());

    // scale animation on dialog content
    auto contentNode = DynamicCast<FrameNode>(node->GetFirstChild());
    CHECK_NULL_VOID(contentNode);
    ctx = contentNode->GetRenderContext();
    CHECK_NULL_VOID(ctx);
    option.SetOnFinishEvent(nullptr);
    option.SetCurve(SHOW_SCALE_ANIMATION_CURVE);
    option.SetDuration(theme->GetAnimationDurationIn());
    ctx->ScaleAnimation(option, theme->GetScaleStart(), theme->GetScaleEnd());
}

void OverlayManager::CloseDialogAnimation(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_VOID(node);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<DialogTheme>();
    CHECK_NULL_VOID(theme);

    // default opacity animation params
    AnimationOption option;
    option.SetFillMode(FillMode::FORWARDS);
    option.SetCurve(Curves::SHARP);

    option.SetDuration(theme->GetAnimationDurationOut());
    // get customized animation params
    auto dialogPattern = node->GetPattern<DialogPattern>();
    option = dialogPattern->GetCloseAnimation().value_or(option);
    auto onFinish = option.GetOnFinishEvent();

    auto dialogLayoutProp = dialogPattern->GetLayoutProperty<DialogLayoutProperty>();
    bool isShowInSubWindow = false;
    if (dialogLayoutProp) {
        isShowInSubWindow = dialogLayoutProp->GetShowInSubWindowValue(false);
    }

    option.SetOnFinishEvent([rootWk = rootNodeWeak_, nodeWk = WeakClaim(RawPtr(node)), id = Container::CurrentId()] {
        ContainerScope scope(id);
        auto root = rootWk.Upgrade();
        auto node = nodeWk.Upgrade();
        CHECK_NULL_VOID(root && node);

        OnDialogCloseEvent(root, node);

        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto overlayManager = pipeline->GetOverlayManager();
        CHECK_NULL_VOID(overlayManager);
        overlayManager->BlurOverlayNode();
    });
    auto ctx = node->GetRenderContext();
    CHECK_NULL_VOID(ctx);
    ctx->OpacityAnimation(option, theme->GetOpacityEnd(), theme->GetOpacityStart());

    // scale animation
    auto contentNode = DynamicCast<FrameNode>(node->GetFirstChild());
    CHECK_NULL_VOID(contentNode);
    ctx = contentNode->GetRenderContext();
    CHECK_NULL_VOID(ctx);
    option.SetOnFinishEvent(nullptr);
    option.SetCurve(Curves::FRICTION);
    ctx->ScaleAnimation(option, theme->GetScaleEnd(), theme->GetScaleStart());
    // start animation immediately
    pipeline->RequestFrame();
}

void OverlayManager::ShowMenuAnimation(const RefPtr<FrameNode>& menu, bool isInSubWindow)
{
    AnimationOption option;
    option.SetCurve(Curves::FAST_OUT_SLOW_IN);
    option.SetDuration(MENU_ANIMATION_DURATION);
    option.SetFillMode(FillMode::FORWARDS);
    option.SetOnFinishEvent(
        [weak = WeakClaim(this), menuWK = WeakClaim(RawPtr(menu)), id = Container::CurrentId(), isInSubWindow] {
            auto menu = menuWK.Upgrade();
            auto overlayManager = weak.Upgrade();
            CHECK_NULL_VOID_NOLOG(menu && overlayManager);
            ContainerScope scope(id);
            overlayManager->FocusOverlayNode(menu, isInSubWindow);
        });

    auto context = menu->GetRenderContext();
    CHECK_NULL_VOID(context);
    context->UpdateOpacity(0.0);

    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    auto menuAnimationOffset = static_cast<float>(theme->GetMenuAnimationOffset().ConvertToPx());
    context->OnTransformTranslateUpdate({ 0.0f, -menuAnimationOffset, 0.0f });

    AnimationUtils::Animate(
        option,
        [context]() {
            if (context) {
                context->UpdateOpacity(1.0);
                context->OnTransformTranslateUpdate({ 0.0f, 0.0f, 0.0f });
            }
        },
        option.GetOnFinishEvent());
}

void OverlayManager::PopMenuAnimation(const RefPtr<FrameNode>& menu)
{
    AnimationOption option;
    option.SetCurve(Curves::FAST_OUT_SLOW_IN);
    option.SetDuration(MENU_ANIMATION_DURATION);
    option.SetFillMode(FillMode::FORWARDS);
    option.SetOnFinishEvent([rootWeak = rootNodeWeak_, menuWK = WeakClaim(RawPtr(menu)), id = Container::CurrentId()] {
        auto menu = menuWK.Upgrade();
        auto root = rootWeak.Upgrade();
        CHECK_NULL_VOID_NOLOG(menu && root);
        ContainerScope scope(id);
        auto menuWrapperPattern = menu->GetPattern<MenuWrapperPattern>();
        // clear contextMenu then return
        if (menuWrapperPattern && menuWrapperPattern->IsContextMenu()) {
            SubwindowManager::GetInstance()->ClearMenuNG();
            return;
        }
        root->RemoveChild(menu);
        root->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
    });

    auto context = menu->GetRenderContext();
    CHECK_NULL_VOID(context);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    auto menuAnimationOffset = static_cast<float>(theme->GetMenuAnimationOffset().ConvertToPx());
    AnimationUtils::Animate(
        option,
        [context, menuAnimationOffset]() {
            context->UpdateOpacity(0.0);
            context->OnTransformTranslateUpdate({ 0.0f, -menuAnimationOffset, 0.0f });
        },
        option.GetOnFinishEvent());

    // start animation immediately
    pipeline->RequestFrame();
}

void OverlayManager::ShowToast(
    const std::string& message, int32_t duration, const std::string& bottom, bool isRightToLeft)
{
    LOGI("OverlayManager::ShowToast");
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto rootNode = context->GetRootElement();
    CHECK_NULL_VOID(rootNode);

    // only one toast
    for (auto [id, toastNodeWeak] : toastMap_) {
        rootNode->RemoveChild(toastNodeWeak.Upgrade());
    }
    toastMap_.clear();

    auto toastNode = ToastView::CreateToastNode(message, bottom, isRightToLeft);
    CHECK_NULL_VOID(toastNode);
    auto toastId = toastNode->GetId();
    // mount to parent
    toastNode->MountToParent(rootNode);
    rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    toastMap_[toastId] = toastNode;
    AnimationOption option;
    auto curve = AceType::MakeRefPtr<CubicCurve>(0.2f, 0.0f, 0.1f, 1.0f);
    option.SetCurve(curve);
    option.SetDuration(TOAST_ANIMATION_DURATION);
    option.SetFillMode(FillMode::FORWARDS);
    auto&& callback = [weak = WeakClaim(this), toastId, duration, id = Container::CurrentId()]() {
        auto overlayManager = weak.Upgrade();
        CHECK_NULL_VOID(overlayManager);
        ContainerScope scope(id);
        overlayManager->PopToast(toastId);
    };
    continuousTask_.Reset(callback);
    option.SetOnFinishEvent([continuousTask = continuousTask_, duration, id = Container::CurrentId()] {
        ContainerScope scope(id);
        auto context = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID_NOLOG(context);
        context->GetTaskExecutor()->PostDelayedTask(continuousTask, TaskExecutor::TaskType::UI, duration);
    });
    auto ctx = toastNode->GetRenderContext();
    CHECK_NULL_VOID(ctx);
    ctx->UpdateOpacity(0.0);
    ctx->OnTransformTranslateUpdate({ 0.0f, TOAST_ANIMATION_POSITION, 0.0f });
    AnimationUtils::Animate(
        option,
        [ctx]() {
            if (ctx) {
                ctx->UpdateOpacity(1.0);
                ctx->OnTransformTranslateUpdate({ 0.0f, 0.0f, 0.0f });
            }
        },
        option.GetOnFinishEvent());
}

void OverlayManager::PopToast(int32_t toastId)
{
    LOGI("OverlayManager::PopToast");
    AnimationOption option;
    auto curve = AceType::MakeRefPtr<CubicCurve>(0.2f, 0.0f, 0.1f, 1.0f);
    option.SetCurve(curve);
    option.SetDuration(TOAST_ANIMATION_DURATION);
    option.SetFillMode(FillMode::FORWARDS);
    // OnFinishEvent should be executed in UI thread.
    option.SetOnFinishEvent([weak = WeakClaim(this), toastId, id = Container::CurrentId()] {
        ContainerScope scope(id);
        auto context = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID_NOLOG(context);
        context->GetTaskExecutor()->PostTask(
            [weak, toastId, id]() {
                ContainerScope scope(id);
                auto overlayManager = weak.Upgrade();
                CHECK_NULL_VOID_NOLOG(overlayManager);
                auto toastIter = overlayManager->toastMap_.find(toastId);
                if (toastIter == overlayManager->toastMap_.end()) {
                    LOGI("No toast under pop");
                    return;
                }
                auto toastUnderPop = toastIter->second.Upgrade();
                CHECK_NULL_VOID_NOLOG(toastUnderPop);
                LOGI("begin to pop toast, id is %{public}d", toastUnderPop->GetId());
                auto context = PipelineContext::GetCurrentContext();
                CHECK_NULL_VOID_NOLOG(context);
                auto rootNode = context->GetRootElement();
                CHECK_NULL_VOID_NOLOG(rootNode);
                rootNode->RemoveChild(toastUnderPop);
                overlayManager->toastMap_.erase(toastId);
                rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);

                auto container = Container::Current();
                CHECK_NULL_VOID_NOLOG(container);
                if (container->IsDialogContainer() ||
                    (container->IsSubContainer() && rootNode->GetChildren().empty())) {
                    // hide window when toast show in subwindow.
                    SubwindowManager::GetInstance()->HideSubWindowNG();
                }
            },
            TaskExecutor::TaskType::UI);
    });
    auto toastIter = toastMap_.find(toastId);
    if (toastIter == toastMap_.end()) {
        LOGI("No toast under pop");
        return;
    }
    auto toastUnderPop = toastIter->second.Upgrade();
    CHECK_NULL_VOID_NOLOG(toastUnderPop);
    auto ctx = toastUnderPop->GetRenderContext();
    CHECK_NULL_VOID(ctx);
    ctx->UpdateOpacity(1.0);
    ctx->OnTransformTranslateUpdate({ 0.0f, 0.0f, 0.0f });
    AnimationUtils::Animate(
        option,
        [ctx]() {
            if (ctx) {
                ctx->UpdateOpacity(0.0);
                ctx->OnTransformTranslateUpdate({ 0.0f, TOAST_ANIMATION_POSITION, 0.0f });
            }
        },
        option.GetOnFinishEvent());
    // start animation immediately
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->RequestFrame();
}

void OverlayManager::UpdatePopupNode(int32_t targetId, const PopupInfo& popupInfo)
{
    popupMap_[targetId] = popupInfo;
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_VOID(rootNode);
    CHECK_NULL_VOID_NOLOG(popupInfo.markNeedUpdate);
    CHECK_NULL_VOID_NOLOG(popupInfo.popupNode);

    popupMap_[targetId].markNeedUpdate = false;
    auto rootChildren = rootNode->GetChildren();
    auto iter = std::find(rootChildren.begin(), rootChildren.end(), popupInfo.popupNode);
    if (iter != rootChildren.end()) {
        // Pop popup
        CHECK_NULL_VOID_NOLOG(popupInfo.isCurrentOnShow);
        LOGI("OverlayManager: popup begin pop");
        popupInfo.popupNode->GetEventHub<BubbleEventHub>()->FireChangeEvent(false);
        rootNode->RemoveChild(popupMap_[targetId].popupNode);
    } else {
        // Push popup
        CHECK_NULL_VOID_NOLOG(!popupInfo.isCurrentOnShow);
        LOGI("OverlayManager: popup begin push");
        popupInfo.popupNode->GetEventHub<BubbleEventHub>()->FireChangeEvent(true);
        auto hub = popupInfo.popupNode->GetEventHub<BubbleEventHub>();
        if (!popupInfo.isBlockEvent && hub) {
            auto ges = hub->GetOrCreateGestureEventHub();
            if (ges) {
                ges->SetHitTestMode(HitTestMode::HTMTRANSPARENT);
            }
        }
        popupMap_[targetId].popupNode->MountToParent(rootNode);
    }
    popupMap_[targetId].isCurrentOnShow = !popupInfo.isCurrentOnShow;
    rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void OverlayManager::ShowIndexerPopup(int32_t targetId, RefPtr<FrameNode>& customNode)
{
    CHECK_NULL_VOID(customNode);
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_VOID(rootNode);
    if (!customPopupMap_[targetId] || customPopupMap_[targetId] != customNode) {
        customPopupMap_[targetId] = customNode;
        customNode->MountToParent(rootNode);
        customNode->MarkModifyDone();
        rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }
}

void OverlayManager::RemoveIndexerPopup()
{
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_VOID(rootNode);
    for (const auto& popup : customPopupMap_) {
        auto popupNode = popup.second;
        rootNode->RemoveChild(popupNode);
    }
    customPopupMap_.clear();
    rootNode->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
}

void OverlayManager::HidePopup(int32_t targetId, const PopupInfo& popupInfo)
{
    popupMap_[targetId] = popupInfo;
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_VOID(rootNode);
    CHECK_NULL_VOID_NOLOG(popupInfo.markNeedUpdate);
    CHECK_NULL_VOID_NOLOG(popupInfo.popupNode);
    popupMap_[targetId].markNeedUpdate = false;
    auto rootChildren = rootNode->GetChildren();
    auto iter = std::find(rootChildren.begin(), rootChildren.end(), popupInfo.popupNode);
    if (iter == rootChildren.end()) {
        LOGW("OverlayManager: popupNode is not found in rootChildren");
        return;
    }
    CHECK_NULL_VOID_NOLOG(popupInfo.isCurrentOnShow);
    LOGI("begin pop");
    popupInfo.popupNode->GetEventHub<BubbleEventHub>()->FireChangeEvent(false);
    rootNode->RemoveChild(popupMap_[targetId].popupNode);
    popupMap_[targetId].isCurrentOnShow = !popupInfo.isCurrentOnShow;
    rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void OverlayManager::HideAllPopups()
{
    LOGI("OverlayManager::HideAllPopups");
    if (popupMap_.empty()) {
        LOGW("OverlayManager: popupMap is empty");
        return;
    }
    for (const auto& popup : popupMap_) {
        auto popupInfo = popup.second;
        if (popupInfo.isCurrentOnShow && popupInfo.target.Upgrade()) {
            popupInfo.markNeedUpdate = true;
            popupInfo.popupId = -1;
            auto targetNodeId = popupInfo.target.Upgrade()->GetId();
            auto popupNode = popupInfo.popupNode;
            CHECK_NULL_VOID(popupNode);
            auto layoutProp = popupNode->GetLayoutProperty<BubbleLayoutProperty>();
            CHECK_NULL_VOID(layoutProp);
            auto showInSubWindow = layoutProp->GetShowInSubWindow().value_or(false);
            if (showInSubWindow) {
                SubwindowManager::GetInstance()->HidePopupNG(targetNodeId);
            } else {
                UpdatePopupNode(targetNodeId, popupInfo);
            }
        }
    }
}

void OverlayManager::ErasePopup(int32_t targetId)
{
    if (popupMap_.find(targetId) != popupMap_.end()) {
        LOGI("Erase popup id %{public}d when destroyed.", targetId);
        auto rootNode = rootNodeWeak_.Upgrade();
        CHECK_NULL_VOID(rootNode);
        rootNode->RemoveChild(popupMap_[targetId].popupNode);
        rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        popupMap_.erase(targetId);
    }
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

    RefPtr<FrameNode> menuFrameNode = menu;
    if (menu->GetTag() != V2::MENU_ETS_TAG) {
        auto menuChild = menu->GetChildAtIndex(0);
        CHECK_NULL_RETURN(menuChild, false);
        menuFrameNode = DynamicCast<FrameNode>(menuChild);
    }

    auto props = menuFrameNode->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_RETURN(props, false);
    props->UpdateMenuOffset(offset);
    menuFrameNode->MarkDirtyNode();
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
        rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);

        ShowMenuAnimation(menu);
        menu->MarkModifyDone();
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
    ShowMenuAnimation(menu, true);
    menu->MarkModifyDone();
    rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    LOGI("menuNode mounted in subwindow");
}

void OverlayManager::HideMenuInSubWindow(int32_t targetId)
{
    LOGI("OverlayManager::HideMenuInSubWindow");
    if (menuMap_.find(targetId) == menuMap_.end()) {
        LOGW("OverlayManager: menuNode %{public}d not found in map", targetId);
        return;
    }
    auto node = menuMap_[targetId];
    CHECK_NULL_VOID(node);
    PopMenuAnimation(node);
    BlurOverlayNode(true);
}

void OverlayManager::HideMenuInSubWindow()
{
    LOGI("OverlayManager::HideMenuInSubWindow from close");
    if (menuMap_.empty()) {
        LOGW("OverlayManager: menuMap is empty");
        return;
    }
    auto rootNode = rootNodeWeak_.Upgrade();
    for (const auto& child : rootNode->GetChildren()) {
        auto node = DynamicCast<FrameNode>(child);
        PopMenuAnimation(node);
    }
}

void OverlayManager::HideMenu(int32_t targetId)
{
    LOGI("OverlayManager::HideMenuNode menu targetId is %{public}d", targetId);
    if (menuMap_.find(targetId) == menuMap_.end()) {
        LOGW("OverlayManager: menuNode %{public}d not found in map", targetId);
        return;
    }
    PopMenuAnimation(menuMap_[targetId]);
    if (onHideMenuCallback_) {
        onHideMenuCallback_();
    }
    BlurOverlayNode();
}

void OverlayManager::HideAllMenus()
{
    LOGI("OverlayManager::HideAllMenus");
    if (menuMap_.empty()) {
        LOGW("OverlayManager: menuMap is empty");
        return;
    }
    auto rootNode = rootNodeWeak_.Upgrade();
    for (const auto& child : rootNode->GetChildren()) {
        auto node = DynamicCast<FrameNode>(child);
        if (node->GetTag() == V2::MENU_WRAPPER_ETS_TAG) {
            PopMenuAnimation(node);
            BlurOverlayNode();
        }
    }
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
    OpenDialogAnimation(dialog);
    return dialog;
}

void OverlayManager::ShowDateDialog(const DialogProperties& dialogProps,
    std::map<std::string, PickerDate> datePickerProperty, bool isLunar,
    std::map<std::string, NG::DialogEvent> dialogEvent, std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent)
{
    LOGI("OverlayManager::ShowDateDialogPicker");
    auto dialogNode = DatePickerDialogView::Show(
        dialogProps, std::move(datePickerProperty), isLunar, std::move(dialogEvent), std::move(dialogCancelEvent));
    OpenDialogAnimation(dialogNode);
}

void OverlayManager::ShowTimeDialog(const DialogProperties& dialogProps,
    std::map<std::string, PickerTime> timePickerProperty, bool isUseMilitaryTime, PickerDate dialogTitleDate,
    std::map<std::string, NG::DialogEvent> dialogEvent, std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent)
{
    LOGI("OverlayManager::ShowTimeDialogPicker");
    auto dialogNode = TimePickerDialogView::Show(dialogProps, std::move(timePickerProperty), isUseMilitaryTime,
        dialogTitleDate, std::move(dialogEvent), std::move(dialogCancelEvent));
    OpenDialogAnimation(dialogNode);
}

void OverlayManager::ShowTextDialog(const DialogProperties& dialogProps, uint32_t selected, const Dimension& height,
    const std::vector<std::string>& getRangeVector, std::map<std::string, NG::DialogTextEvent> dialogEvent,
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent)
{
    LOGI("OverlayManager::ShowTextDialogPicker");
    auto dialogNode = TextPickerDialogView::Show(
        dialogProps, selected, height, getRangeVector, std::move(dialogEvent), std::move(dialogCancelEvent));
    OpenDialogAnimation(dialogNode);
}

void OverlayManager::CloseDialog(const RefPtr<FrameNode>& dialogNode)
{
    LOGI("OverlayManager::CloseDialog");
    CloseDialogAnimation(dialogNode);
}

bool OverlayManager::RemoveOverlay()
{
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_RETURN(rootNode, true);
    RemoveIndexerPopup();
    auto childrenSize = rootNode->GetChildren().size();
    if (rootNode->GetChildren().size() > 1) {
        // stage node is at index 0, remove overlay at last
        auto overlay = DynamicCast<FrameNode>(rootNode->GetLastChild());
        CHECK_NULL_RETURN(overlay, false);
        // close dialog with animation
        auto pattern = overlay->GetPattern();
        if (AceType::DynamicCast<DialogPattern>(pattern)) {
            CloseDialog(overlay);
            return true;
        } else if (AceType::DynamicCast<BubblePattern>(pattern)) {
            auto popupNode = AceType::DynamicCast<NG::FrameNode>(rootNode->GetChildAtIndex(childrenSize - 1));
            popupNode->GetEventHub<BubbleEventHub>()->FireChangeEvent(false);
            for (const auto& popup : popupMap_) {
                auto targetId = popup.first;
                auto popupInfo = popup.second;
                if (popupNode == popupInfo.popupNode) {
                    popupMap_.erase(targetId);
                    rootNode->RemoveChild(popupNode);
                    rootNode->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
                    return true;
                }
            }
            return false;
        }
        rootNode->RemoveChild(overlay);
        rootNode->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
        LOGI("overlay removed successfully");
        return true;
    }
    return false;
}

bool OverlayManager::RemoveOverlayInSubwindow()
{
    LOGI("OverlayManager::RemoveOverlayInSubwindow");
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_RETURN(rootNode, false);
    if (rootNode->GetChildren().empty()) {
        LOGI("No overlay in this subwindow.");
        return false;
    }

    // remove the overlay node just mounted in subwindow
    auto overlay = DynamicCast<FrameNode>(rootNode->GetLastChild());
    CHECK_NULL_RETURN(overlay, false);
    // close dialog with animation
    auto pattern = overlay->GetPattern();
    if (AceType::InstanceOf<DialogPattern>(pattern)) {
        CloseDialog(overlay);
        return true;
    }
    if (AceType::InstanceOf<BubblePattern>(pattern)) {
        overlay->GetEventHub<BubbleEventHub>()->FireChangeEvent(false);
        for (const auto& popup : popupMap_) {
            auto targetId = popup.first;
            auto popupInfo = popup.second;
            if (overlay == popupInfo.popupNode) {
                popupMap_.erase(targetId);
                rootNode->RemoveChild(overlay);
                rootNode->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
                if (rootNode->GetChildren().empty()) {
                    SubwindowManager::GetInstance()->HideSubWindowNG();
                }
                return true;
            }
        }
        return false;
    }
    if (AceType::InstanceOf<MenuWrapperPattern>(pattern)) {
        HideMenuInSubWindow();
        return true;
    }
    rootNode->RemoveChild(overlay);
    rootNode->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
    if (rootNode->GetChildren().empty()) {
        SubwindowManager::GetInstance()->HideSubWindowNG();
    }
    LOGI("overlay removed successfully");
    return true;
}

void OverlayManager::FocusOverlayNode(const RefPtr<FrameNode>& overlayNode, bool isInSubWindow)
{
    LOGI("OverlayManager::FocusOverlayNode when overlay node show");
    CHECK_NULL_VOID(overlayNode);
    auto focusHub = overlayNode->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);

    focusHub->RequestFocusImmediately();
    if (isInSubWindow) {
        // no need to set page lost focus in sub window.
        return;
    }

    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto stageManager = pipelineContext->GetStageManager();
    CHECK_NULL_VOID(stageManager);
    auto pageNode = stageManager->GetLastPage();
    CHECK_NULL_VOID(pageNode);
    auto pageFocusHub = pageNode->GetFocusHub();
    CHECK_NULL_VOID(pageFocusHub);
    pageFocusHub->SetParentFocusable(false);
    pageFocusHub->LostFocus();
}

void OverlayManager::BlurOverlayNode(bool isInSubWindow)
{
    LOGI("OverlayManager::BlurOverlayNode");
    if (isInSubWindow) {
        // no need to set page request focus in sub window.
        return;
    }
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto stageManager = pipelineContext->GetStageManager();
    CHECK_NULL_VOID(stageManager);
    auto pageNode = stageManager->GetLastPage();
    CHECK_NULL_VOID(pageNode);
    auto pageFocusHub = pageNode->GetFocusHub();
    CHECK_NULL_VOID(pageFocusHub);
    pageFocusHub->SetParentFocusable(true);
    pageFocusHub->RequestFocus();
}

} // namespace OHOS::Ace::NG
