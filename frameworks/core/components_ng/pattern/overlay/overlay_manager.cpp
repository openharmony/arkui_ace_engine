/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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
#include "base/subwindow/subwindow_manager.h"
#include "base/utils/system_properties.h"
#include "base/utils/utils.h"
#include "core/animation/animation_pub.h"
#include "core/animation/spring_curve.h"
#include "core/common/ace_application_info.h"
#include "core/common/container.h"
#include "core/common/modal_ui_extension.h"
#include "core/components/common/properties/color.h"
#include "core/components/select/select_theme.h"
#include "core/components/toast/toast_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/bubble/bubble_event_hub.h"
#include "core/components_ng/pattern/bubble/bubble_pattern.h"
#include "core/components_ng/pattern/calendar_picker/calendar_dialog_view.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_view.h"
#include "core/components_ng/pattern/menu/menu_layout_property.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/menu/menu_theme.h"
#include "core/components_ng/pattern/menu/preview/menu_preview_pattern.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_group_node.h"
#include "core/components_ng/pattern/navrouter/navdestination_group_node.h"
#include "core/components_ng/pattern/overlay/keyboard_base_pattern.h"
#include "core/components_ng/pattern/overlay/keyboard_view.h"
#include "core/components_ng/pattern/overlay/modal_presentation_pattern.h"
#include "core/components_ng/pattern/overlay/popup_base_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_drag_bar_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_property.h"
#include "core/components_ng/pattern/overlay/sheet_view.h"
#include "core/components_ng/pattern/picker/datepicker_dialog_view.h"
#include "core/components_ng/pattern/stage/stage_pattern.h"
#include "core/components_ng/pattern/text_picker/textpicker_dialog_view.h"
#include "core/components_ng/pattern/time_picker/timepicker_dialog_view.h"
#include "core/components_ng/pattern/toast/toast_pattern.h"
#include "core/components_ng/property/property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/pipeline_base.h"
#include "core/pipeline/pipeline_context.h"

#ifdef ENABLE_DRAG_FRAMEWORK
#include "base/msdp/device_status/interfaces/innerkits/interaction/include/interaction_manager.h"
#endif // ENABLE_DRAG_FRAMEWORK

namespace OHOS::Ace::NG {
namespace {
// should be moved to theme.
constexpr int32_t TOAST_ANIMATION_DURATION = 100;
constexpr int32_t MENU_ANIMATION_DURATION = 150;
constexpr float TOAST_ANIMATION_POSITION = 15.0f;

#ifdef ENABLE_DRAG_FRAMEWORK
constexpr float PIXELMAP_DRAG_SCALE = 1.0f;
constexpr int32_t PIXELMAP_ANIMATION_DURATION = 250;
constexpr float PIXELMAP_ANIMATION_DEFAULT_LIMIT_SCALE = 0.5f;
#endif // ENABLE_DRAG_FRAMEWORK

constexpr int32_t FULL_MODAL_ALPHA_ANIMATION_DURATION = 200;

// dialog animation params
const RefPtr<Curve> SHOW_SCALE_ANIMATION_CURVE = AceType::MakeRefPtr<CubicCurve>(0.38f, 1.33f, 0.6f, 1.0f);

// custom keyboard animation params
const RefPtr<Curve> SHOW_CUSTOM_KEYBOARD_ANIMATION_CURVE =
    AceType::MakeRefPtr<InterpolatingSpring>(0.0f, 1.0f, 342.0f, 37.0f);
const RefPtr<Curve> HIDE_CUSTOM_KEYBOARD_ANIMATION_CURVE =
    AceType::MakeRefPtr<InterpolatingSpring>(4.0f, 1.0f, 342.0f, 37.0f);

RefPtr<FrameNode> GetLastPage()
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, nullptr);
    auto stageManager = pipelineContext->GetStageManager();
    CHECK_NULL_RETURN(stageManager, nullptr);
    auto pageNode = stageManager->GetLastPage();
    return pageNode;
}

void ShowPreviewDisappearAnimation(const RefPtr<MenuWrapperPattern>& menuWrapperPattern)
{
    CHECK_NULL_VOID(menuWrapperPattern);
    auto previewChild = menuWrapperPattern->GetPreview();
    CHECK_NULL_VOID(previewChild);
    auto previewRenderContext = previewChild->GetRenderContext();
    CHECK_NULL_VOID(previewRenderContext);

    auto menuChild = menuWrapperPattern->GetMenu();
    CHECK_NULL_VOID(menuChild);
    auto menuPattern = menuChild->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    auto previewPosition = menuPattern->GetPreviewOriginOffset();

    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto menuTheme = pipelineContext->GetTheme<MenuTheme>();
    CHECK_NULL_VOID(menuTheme);
    auto springMotionResponse = menuTheme->GetPreviewDisappearSpringMotionResponse();
    auto springMotionDampingFraction = menuTheme->GetPreviewDisappearSpringMotionDampingFraction();
    AnimationOption scaleOption;
    auto motion = AceType::MakeRefPtr<ResponsiveSpringMotion>(springMotionResponse, springMotionDampingFraction);
    scaleOption.SetCurve(motion);
    AnimationUtils::Animate(scaleOption, [previewRenderContext, previewPosition]() {
        if (previewRenderContext) {
            previewRenderContext->UpdateTransformScale(VectorF(1.0f, 1.0f));
            previewRenderContext->UpdatePosition(
                OffsetT<Dimension>(Dimension(previewPosition.GetX()), Dimension(previewPosition.GetY())));
        }
    });

    auto shadow = previewRenderContext->GetBackShadow();
    if (!shadow.has_value()) {
        shadow = Shadow::CreateShadow(ShadowStyle::None);
    }
    previewRenderContext->UpdateBackShadow(shadow.value());
    auto disappearDuration = menuTheme->GetDisappearDuration();
    AnimationOption previewOption;
    previewOption.SetCurve(Curves::SHARP);
    previewOption.SetDuration(disappearDuration);
    AnimationUtils::Animate(previewOption, [previewRenderContext, shadow]() mutable {
        if (previewRenderContext) {
            auto color = shadow->GetColor();
            auto newColor = Color::FromARGB(1, color.GetRed(), color.GetGreen(), color.GetBlue());
            shadow->SetColor(newColor);
            previewRenderContext->UpdateBackShadow(shadow.value());
            BorderRadiusProperty borderRadius;
            borderRadius.SetRadius(0.0_vp);
            previewRenderContext->UpdateBorderRadius(borderRadius);
        }
    });
}

void ShowContextMenuDisappearAnimation(AnimationOption& option, const RefPtr<MenuWrapperPattern>& menuWrapperPattern)
{
    CHECK_NULL_VOID(menuWrapperPattern);
    auto menuChild = menuWrapperPattern->GetMenu();
    CHECK_NULL_VOID(menuChild);
    auto menuRenderContext = menuChild->GetRenderContext();
    CHECK_NULL_VOID(menuRenderContext);
    auto menuPattern = menuChild->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    auto menuPosition = menuPattern->GetEndOffset();

    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto menuTheme = pipelineContext->GetTheme<MenuTheme>();
    CHECK_NULL_VOID(menuTheme);
    auto springMotionResponse = menuTheme->GetPreviewDisappearSpringMotionResponse();
    auto springMotionDampingFraction = menuTheme->GetPreviewDisappearSpringMotionDampingFraction();
    AnimationOption positionOption;
    auto motion = AceType::MakeRefPtr<ResponsiveSpringMotion>(springMotionResponse, springMotionDampingFraction);
    positionOption.SetCurve(motion);
    AnimationUtils::Animate(positionOption, [menuRenderContext, menuPosition]() {
        if (menuRenderContext) {
            menuRenderContext->UpdatePosition(
                OffsetT<Dimension>(Dimension(menuPosition.GetX()), Dimension(menuPosition.GetY())));
        }
    });

    auto disappearDuration = menuTheme->GetDisappearDuration();
    auto menuAnimationScale = menuTheme->GetMenuAnimationScale();
    AnimationOption scaleOption;
    scaleOption.SetCurve(Curves::FAST_OUT_LINEAR_IN);
    scaleOption.SetDuration(disappearDuration);
    AnimationUtils::Animate(scaleOption, [menuRenderContext, menuAnimationScale]() {
        if (menuRenderContext) {
            menuRenderContext->UpdateTransformScale({ menuAnimationScale, menuAnimationScale });
        }
    });

    option.SetDuration(disappearDuration);
    option.SetCurve(Curves::FRICTION);
    AnimationUtils::Animate(
        option,
        [menuRenderContext]() {
            if (menuRenderContext) {
                menuRenderContext->UpdateOpacity(0.0);
            }
        },
        option.GetOnFinishEvent());
}
} // namespace

void OverlayManager::PostDialogFinishEvent(const WeakPtr<FrameNode>& nodeWk)
{
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto taskExecutor = context->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    // animation finish event should be posted to UI thread.
    taskExecutor->PostTask(
        [weak = WeakClaim(this), nodeWk, id = Container::CurrentId()]() {
            ContainerScope scope(id);
            LOGD("Execute dialog OnDialogCloseEvent");
            auto overlayManager = weak.Upgrade();
            auto node = nodeWk.Upgrade();
            CHECK_NULL_VOID(overlayManager && node);
            SafeAreaExpandOpts opts = { .type = SAFE_AREA_TYPE_NONE };
            node->GetLayoutProperty()->UpdateSafeAreaExpandOpts(opts);
            overlayManager->OnDialogCloseEvent(node);
        },
        TaskExecutor::TaskType::UI);
}

void OverlayManager::OnDialogCloseEvent(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_VOID(node);

    BlurOverlayNode(node);

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

    auto root = node->GetParent();
    CHECK_NULL_VOID(root);
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
    CHECK_NULL_VOID(container);
    if (container->IsDialogContainer() || isShowInSubWindow) {
        SubwindowManager::GetInstance()->HideSubWindowNG();
    }
}

void OverlayManager::OpenDialogAnimation(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_VOID(node);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<DialogTheme>();
    CHECK_NULL_VOID(theme);
    auto root = rootNodeWeak_.Upgrade();
    auto dialogPattern = node->GetPattern<DialogPattern>();
    auto container = Container::Current();
    if (container && container->IsScenceBoardWindow()) {
        root = dialogPattern->GetDialogProperties().windowScene.Upgrade();
    }
    CHECK_NULL_VOID(root);
    node->MountToParent(root);
    root->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    BlurLowerNode(node);

    AnimationOption option;
    // default opacity animation params
    option.SetCurve(Curves::SHARP);
    option.SetDuration(theme->GetOpacityAnimationDurIn());
    option.SetFillMode(FillMode::FORWARDS);
    option = dialogPattern->GetOpenAnimation().value_or(option);
    option.SetIteration(1);
    option.SetAnimationDirection(AnimationDirection::NORMAL);
    auto onFinish = option.GetOnFinishEvent();
    option.SetOnFinishEvent(
        [weak = WeakClaim(this), nodeWK = WeakPtr<FrameNode>(node), id = Container::CurrentId(), onFinish] {
            ContainerScope scope(id);
            auto context = PipelineContext::GetCurrentContext();
            CHECK_NULL_VOID(context);
            auto taskExecutor = context->GetTaskExecutor();
            CHECK_NULL_VOID(taskExecutor);
            taskExecutor->PostTask(
                [id, weak, nodeWK, onFinish]() {
                    ContainerScope scope(id);
                    if (onFinish) {
                        onFinish();
                    }
                    auto overlayManager = weak.Upgrade();
                    auto node = nodeWK.Upgrade();
                    CHECK_NULL_VOID(overlayManager && node);
                    overlayManager->FocusOverlayNode(node);
                },
                TaskExecutor::TaskType::UI);
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
    option.SetDuration(dialogPattern->GetOpenAnimation().has_value()
                           ? dialogPattern->GetOpenAnimation().value().GetDuration()
                           : theme->GetAnimationDurationIn());
    ctx->ScaleAnimation(option, theme->GetScaleStart(), theme->GetScaleEnd());
    node->OnAccessibilityEvent(AccessibilityEventType::CHANGE, WindowsContentChangeTypes::CONTENT_CHANGE_TYPE_SUBTREE);
}

void OverlayManager::CloseDialogAnimation(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_VOID(node);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<DialogTheme>();
    CHECK_NULL_VOID(theme);

    ResetLowerNodeFocusable(node);
    SafeAreaExpandOpts opts = { .type = SAFE_AREA_TYPE_KEYBOARD };
    node->GetLayoutProperty()->UpdateSafeAreaExpandOpts(opts);

    // default opacity animation params
    AnimationOption option;
    option.SetFillMode(FillMode::FORWARDS);
    option.SetCurve(Curves::SHARP);

    option.SetDuration(theme->GetAnimationDurationOut());
    // get customized animation params
    auto dialogPattern = node->GetPattern<DialogPattern>();
    option = dialogPattern->GetCloseAnimation().value_or(option);
    option.SetIteration(1);
    option.SetAnimationDirection(AnimationDirection::NORMAL);

    option.SetOnFinishEvent([weak = WeakClaim(this), nodeWk = WeakPtr<FrameNode>(node), id = Container::CurrentId()] {
        ContainerScope scope(id);
        auto overlayManager = weak.Upgrade();
        CHECK_NULL_VOID(overlayManager);
        overlayManager->PostDialogFinishEvent(nodeWk);
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

void OverlayManager::SetContainerButtonEnable(bool isEnabled)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetCloseButtonStatus(isEnabled);
}

void OverlayManager::SetShowMenuAnimation(const RefPtr<FrameNode>& menu, bool isInSubWindow)
{
    BlurLowerNode(menu);

    AnimationOption option;
    option.SetCurve(Curves::FAST_OUT_SLOW_IN);
    option.SetDuration(MENU_ANIMATION_DURATION);
    option.SetFillMode(FillMode::FORWARDS);
    option.SetOnFinishEvent(
        [weak = WeakClaim(this), menuWK = WeakClaim(RawPtr(menu)), id = Container::CurrentId(), isInSubWindow] {
            ContainerScope scope(id);
            auto pipeline = PipelineBase::GetCurrentContext();
            CHECK_NULL_VOID(pipeline);
            auto taskExecutor = pipeline->GetTaskExecutor();
            CHECK_NULL_VOID(taskExecutor);
            taskExecutor->PostTask(
                [weak, menuWK, id, isInSubWindow]() {
                    auto menu = menuWK.Upgrade();
                    auto overlayManager = weak.Upgrade();
                    CHECK_NULL_VOID(menu && overlayManager);
                    ContainerScope scope(id);
                    if (isInSubWindow) {
                        SubwindowManager::GetInstance()->RequestFocusSubwindow(id);
                    } else {
                        overlayManager->FocusOverlayNode(menu);
                    }
                    overlayManager->CallOnShowMenuCallback();
                },
                TaskExecutor::TaskType::UI);
        });

    auto pattern = menu->GetPattern<MenuWrapperPattern>();
    if (pattern->GetPreviewMode() == MenuPreviewMode::CUSTOM) {
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        auto menuTheme = pipelineContext->GetTheme<NG::MenuTheme>();
        CHECK_NULL_VOID(menuTheme);
        option.SetDuration(menuTheme->GetContextMenuAppearDuration());
        auto previewChild = pattern->GetPreview();
        if (previewChild) {
            auto previewPattern = AceType::DynamicCast<MenuPreviewPattern>(previewChild->GetPattern());
            if (previewPattern) {
                previewPattern->SetFirstShow();
            }
        }
    }
    pattern->SetAniamtinOption(option);
    pattern->SetFirstShow();
    auto menuChild = pattern->GetMenu();
    CHECK_NULL_VOID(menuChild);
    auto menuPattern = AceType::DynamicCast<MenuPattern>(menuChild->GetPattern());
    CHECK_NULL_VOID(menuPattern);
    menuPattern->SetFirstShow();
}

void OverlayManager::PopMenuAnimation(const RefPtr<FrameNode>& menu, bool showPreviewAnimation)
{
    ResetLowerNodeFocusable(menu);

    AnimationOption option;
    option.SetCurve(Curves::FAST_OUT_SLOW_IN);
    option.SetDuration(MENU_ANIMATION_DURATION);
    option.SetFillMode(FillMode::FORWARDS);
    option.SetOnFinishEvent([rootWeak = rootNodeWeak_, menuWK = WeakClaim(RawPtr(menu)), id = Container::CurrentId(),
                                weak = WeakClaim(this)] {
        ContainerScope scope(id);
        auto pipeline = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto taskExecutor = pipeline->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        taskExecutor->PostTask(
            [rootWeak, menuWK, id, weak]() {
                auto menu = menuWK.Upgrade();
                auto root = rootWeak.Upgrade();
                auto overlayManager = weak.Upgrade();
                CHECK_NULL_VOID(menu && overlayManager);
                ContainerScope scope(id);
                auto container = Container::Current();
                if (container && container->IsScenceBoardWindow()) {
                    root = overlayManager->FindWindowScene(menu);
                }
                CHECK_NULL_VOID(root);
                overlayManager->CallOnHideMenuCallback();
                auto menuWrapperPattern = menu->GetPattern<MenuWrapperPattern>();
                // clear contextMenu then return
                if (menuWrapperPattern && menuWrapperPattern->IsContextMenu()) {
                    SubwindowManager::GetInstance()->ClearMenuNG(id);
                    return;
                }
                overlayManager->BlurOverlayNode(menu);
                root->RemoveChild(menu);
                root->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
            },
            TaskExecutor::TaskType::UI);
    });
    auto context = menu->GetRenderContext();
    CHECK_NULL_VOID(context);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto menuWrapperPattern = menu->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(menuWrapperPattern);
    auto menuAnimationOffset = menuWrapperPattern->GetAnimationOffset();
    if (menuWrapperPattern->GetPreviewMode() != MenuPreviewMode::NONE) {
        if (!showPreviewAnimation) {
            CleanPreviewInSubWindow();
        } else {
            ShowPreviewDisappearAnimation(menuWrapperPattern);
        }
        ShowContextMenuDisappearAnimation(option, menuWrapperPattern);
    } else {
        AnimationUtils::Animate(
            option,
            [context, menuAnimationOffset]() {
                context->UpdateOpacity(0.0);
                context->UpdateOffset(menuAnimationOffset);
            },
            option.GetOnFinishEvent());
    }
    // start animation immediately
    pipeline->RequestFrame();
}

void OverlayManager::ShowToast(const std::string& message, int32_t duration, const std::string& bottom,
    bool isRightToLeft, const ToastShowMode& showMode)
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

    auto toastNode = ToastView::CreateToastNode(message, bottom, isRightToLeft, showMode);
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
    duration = std::max(duration, AceApplicationInfo::GetInstance().GetBarrierfreeDuration());
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
        CHECK_NULL_VOID(context);
        auto taskExecutor = context->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        taskExecutor->PostDelayedTask(continuousTask, TaskExecutor::TaskType::UI, duration);
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
    toastNode->OnAccessibilityEvent(
        AccessibilityEventType::CHANGE, WindowsContentChangeTypes::CONTENT_CHANGE_TYPE_SUBTREE);
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
        CHECK_NULL_VOID(context);
        auto taskExecutor = context->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        taskExecutor->PostTask(
            [weak, toastId, id]() {
                ContainerScope scope(id);
                auto overlayManager = weak.Upgrade();
                CHECK_NULL_VOID(overlayManager);
                auto toastIter = overlayManager->toastMap_.find(toastId);
                if (toastIter == overlayManager->toastMap_.end()) {
                    LOGI("No toast under pop");
                    return;
                }
                auto toastUnderPop = toastIter->second.Upgrade();
                CHECK_NULL_VOID(toastUnderPop);
                LOGI("begin to pop toast, id is %{public}d", toastUnderPop->GetId());
                auto context = PipelineContext::GetCurrentContext();
                CHECK_NULL_VOID(context);
                auto rootNode = context->GetRootElement();
                CHECK_NULL_VOID(rootNode);
                rootNode->RemoveChild(toastUnderPop);
                overlayManager->toastMap_.erase(toastId);
                rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);

                auto container = Container::Current();
                CHECK_NULL_VOID(container);
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
    CHECK_NULL_VOID(toastUnderPop);
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
    AccessibilityEvent event;
    event.type = AccessibilityEventType::CHANGE;
    event.windowContentChangeTypes = WindowsContentChangeTypes::CONTENT_CHANGE_TYPE_SUBTREE;
    pipeline->SendEventToAccessibility(event);
}

void OverlayManager::ClearToast()
{
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto rootNode = context->GetRootElement();
    CHECK_NULL_VOID(rootNode);
    for (auto [id, toastNodeWeak] : toastMap_) {
        PopToast(id);
    }
    toastMap_.clear();
}

void OverlayManager::UpdatePopupNode(int32_t targetId, const PopupInfo& popupInfo)
{
    popupMap_[targetId] = popupInfo;
    auto rootNode = rootNodeWeak_.Upgrade();
    auto container = Container::Current();
    if (container && container->IsScenceBoardWindow()) {
        rootNode = FindWindowScene(popupInfo.target.Upgrade());
    }
    CHECK_NULL_VOID(rootNode);
    CHECK_NULL_VOID(popupInfo.markNeedUpdate);
    CHECK_NULL_VOID(popupInfo.popupNode);

    popupMap_[targetId].markNeedUpdate = false;
    auto rootChildren = rootNode->GetChildren();
    auto iter = std::find(rootChildren.begin(), rootChildren.end(), popupInfo.popupNode);
    if (iter != rootChildren.end()) {
        // Pop popup
        CHECK_NULL_VOID(popupInfo.isCurrentOnShow);
        LOGI("OverlayManager: Popup begin pop");
        popupInfo.popupNode->GetEventHub<BubbleEventHub>()->FireChangeEvent(false);
        rootNode->RemoveChild(popupMap_[targetId].popupNode);
        AccessibilityEvent event;
        event.type = AccessibilityEventType::CHANGE;
        event.windowContentChangeTypes = WindowsContentChangeTypes::CONTENT_CHANGE_TYPE_SUBTREE;
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        pipeline->SendEventToAccessibility(event);
#ifdef ENABLE_DRAG_FRAMEWORK
        RemoveEventColumn();
        RemovePixelMapAnimation(false, 0, 0);
        RemoveFilter();
#endif // ENABLE_DRAG_FRAMEWORK
    } else {
        // Push popup
        CHECK_NULL_VOID(!popupInfo.isCurrentOnShow);
        LOGI("OverlayManager: Popup begin push");
        popupInfo.popupNode->GetEventHub<BubbleEventHub>()->FireChangeEvent(true);
        auto hub = popupInfo.popupNode->GetEventHub<BubbleEventHub>();
        if (!popupInfo.isBlockEvent && hub) {
            auto ges = hub->GetOrCreateGestureEventHub();
            if (ges) {
                ges->SetHitTestMode(HitTestMode::HTMTRANSPARENT_SELF);
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

void OverlayManager::RemoveIndexerPopupById(int32_t targetId)
{
    if (customPopupMap_.empty()) {
        return;
    }
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_VOID(rootNode);
    auto iter = customPopupMap_.find(targetId);
    if (iter != customPopupMap_.end()) {
        rootNode->RemoveChild(iter->second);
        customPopupMap_.erase(iter);
        rootNode->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
    }
}

void OverlayManager::RemoveIndexerPopup()
{
    if (customPopupMap_.empty()) {
        return;
    }
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
    LOGI("OverlayManager:: Hide Popup");
    popupMap_[targetId] = popupInfo;
    CHECK_NULL_VOID(popupInfo.markNeedUpdate);
    popupMap_[targetId].markNeedUpdate = false;
    CHECK_NULL_VOID(popupInfo.popupNode);
    popupInfo.popupNode->GetEventHub<BubbleEventHub>()->FireChangeEvent(false);
    CHECK_NULL_VOID(popupInfo.isCurrentOnShow);
    popupMap_[targetId].isCurrentOnShow = !popupInfo.isCurrentOnShow;

    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_VOID(rootNode);
    auto rootChildren = rootNode->GetChildren();
    auto iter = std::find(rootChildren.begin(), rootChildren.end(), popupInfo.popupNode);
    if (iter != rootChildren.end()) {
        rootNode->RemoveChild(popupMap_[targetId].popupNode);
        rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }
}

void OverlayManager::HideCustomPopups()
{
    if (popupMap_.empty()) {
        LOGD("OverlayManager: popupMap is empty");
        return;
    }
    for (const auto& popup : popupMap_) {
        auto popupInfo = popup.second;
        if (popupInfo.isCurrentOnShow && popupInfo.target.Upgrade()) {
            auto targetNodeId = popupInfo.target.Upgrade()->GetId();
            auto popupNode = popupInfo.popupNode;
            CHECK_NULL_VOID(popupNode);
            auto layoutProp = popupNode->GetLayoutProperty<BubbleLayoutProperty>();
            CHECK_NULL_VOID(layoutProp);
            auto paintProperty = popupNode->GetPaintProperty<BubbleRenderProperty>();
            CHECK_NULL_VOID(paintProperty);
            auto isTypeWithOption = paintProperty->GetPrimaryButtonShow().value_or(false);
            // if use popup with option, skip
            if (isTypeWithOption) {
                continue;
            }
            popupInfo.markNeedUpdate = true;
            auto showInSubWindow = layoutProp->GetShowInSubWindow().value_or(false);
            if (showInSubWindow) {
                SubwindowManager::GetInstance()->HidePopupNG(targetNodeId);
            } else {
                UpdatePopupNode(targetNodeId, popupInfo);
                CHECK_NULL_VOID(popupInfo.popupNode);
                auto pattern = popupInfo.popupNode->GetPattern<BubblePattern>();
                CHECK_NULL_VOID(pattern);
                pattern->SetTransitionStatus(TransitionStatus::INVISIABLE);
            }
        }
    }
}

void OverlayManager::HideAllPopups()
{
    LOGD("OverlayManager::HideAllPopups");
    if (popupMap_.empty()) {
        LOGD("OverlayManager: popupMap is empty");
        return;
    }
    for (const auto& popup : popupMap_) {
        auto popupInfo = popup.second;
        if (popupInfo.isCurrentOnShow && popupInfo.target.Upgrade()) {
            auto targetNodeId = popupInfo.target.Upgrade()->GetId();
            auto popupNode = popupInfo.popupNode;
            CHECK_NULL_VOID(popupNode);
            auto layoutProp = popupNode->GetLayoutProperty<BubbleLayoutProperty>();
            CHECK_NULL_VOID(layoutProp);
            popupInfo.markNeedUpdate = true;
            auto showInSubWindow = layoutProp->GetShowInSubWindow().value_or(false);
            if (showInSubWindow) {
                SubwindowManager::GetInstance()->HidePopupNG(targetNodeId);
            } else {
                HidePopup(targetNodeId, popupInfo);
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
    menuFrameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    return true;
}

void OverlayManager::ShowMenu(int32_t targetId, const NG::OffsetF& offset, RefPtr<FrameNode> menu)
{
    if (!ShowMenuHelper(menu, targetId, offset)) {
        LOGW("show menu failed");
        return;
    }
    auto rootNode = rootNodeWeak_.Upgrade();
    auto container = Container::Current();
    if (container && container->IsScenceBoardWindow()) {
        auto wrapperPattern = AceType::DynamicCast<MenuWrapperPattern>(menu->GetPattern());
        CHECK_NULL_VOID(wrapperPattern);
        auto menuChild = wrapperPattern->GetMenu();
        CHECK_NULL_VOID(menuChild);
        auto menuPattern = AceType::DynamicCast<MenuPattern>(menuChild->GetPattern());
        CHECK_NULL_VOID(menuPattern);
        rootNode = FindWindowScene(FrameNode::GetFrameNode(menuPattern->GetTargetTag(), menuPattern->GetTargetId()));
    }
    CHECK_NULL_VOID(rootNode);
    auto rootChildren = rootNode->GetChildren();
    auto iter = std::find(rootChildren.begin(), rootChildren.end(), menu);
    // menuNode already showing
    if (iter != rootChildren.end()) {
        LOGW("menuNode already appended");
    } else {
        menu->MountToParent(rootNode);
        rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        menu->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        SetShowMenuAnimation(menu);
        menu->MarkModifyDone();
    }
    menu->OnAccessibilityEvent(AccessibilityEventType::CHANGE, WindowsContentChangeTypes::CONTENT_CHANGE_TYPE_SUBTREE);
}

// subwindow only contains one menu instance.
void OverlayManager::ShowMenuInSubWindow(int32_t targetId, const NG::OffsetF& offset, RefPtr<FrameNode> menu)
{
    auto menuOffset = offset;
    auto currentSubwindow = SubwindowManager::GetInstance()->GetCurrentWindow();
    if (currentSubwindow) {
        auto subwindowRect = currentSubwindow->GetRect();
        menuOffset -= subwindowRect.GetOffset();
    }
    if (!ShowMenuHelper(menu, targetId, menuOffset)) {
        LOGW("show menu failed");
        return;
    }
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_VOID(rootNode);
    rootNode->Clean();
    menu->MountToParent(rootNode);
    SetShowMenuAnimation(menu, true);
    menu->MarkModifyDone();
    rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);

    // set subwindow container id in menu.
    auto menuPattern = menu->GetPattern<PopupBasePattern>();
    CHECK_NULL_VOID(menuPattern);
    menuPattern->SetContainerId(Container::CurrentId());
    LOGI("menuNode mounted in subwindow");
}

void OverlayManager::HideMenuInSubWindow(const RefPtr<FrameNode>& menu, int32_t targetId)
{
    LOGI("OverlayManager::HideMenuInSubWindow");
    if (menuMap_.find(targetId) == menuMap_.end()) {
        LOGW("OverlayManager: menuNode %{public}d not found in map", targetId);
    }
    CHECK_NULL_VOID(menu);
    PopMenuAnimation(menu);
}

void OverlayManager::HideMenuInSubWindow(bool showPreviewAnimation)
{
    LOGI("OverlayManager::HideMenuInSubWindow from close");
    if (menuMap_.empty()) {
        LOGW("OverlayManager: menuMap is empty");
        return;
    }
    auto rootNode = rootNodeWeak_.Upgrade();
    for (const auto& child : rootNode->GetChildren()) {
        auto node = DynamicCast<FrameNode>(child);
        PopMenuAnimation(node, showPreviewAnimation);
    }
}

RefPtr<FrameNode> OverlayManager::GetMenuNode(int32_t targetId)
{
    auto it = menuMap_.find(targetId);
    if (it != menuMap_.end()) {
        return it->second;
    }
    LOGW("menuNode doesn't exists %{public}d", targetId);
    return nullptr;
}

void OverlayManager::HideMenu(const RefPtr<FrameNode>& menu, int32_t targetId, bool isMenuOnTouch)
{
    LOGI("OverlayManager::HideMenuNode menu targetId is %{public}d", targetId);
    if (menuMap_.find(targetId) == menuMap_.end()) {
        LOGW("OverlayManager: menuNode %{public}d not found in map", targetId);
    }
    PopMenuAnimation(menu);
    menu->OnAccessibilityEvent(AccessibilityEventType::CHANGE, WindowsContentChangeTypes::CONTENT_CHANGE_TYPE_SUBTREE);
#ifdef ENABLE_DRAG_FRAMEWORK
    RemoveEventColumn();
    if (isMenuOnTouch) {
        RemovePixelMap();
    } else {
        RemovePixelMapAnimation(false, 0, 0);
    }
    RemoveFilterAnimation();
#endif // ENABLE_DRAG_FRAMEWORK
}

void OverlayManager::HideAllMenus()
{
    LOGD("OverlayManager::HideAllMenus");
    auto container = Container::Current();
    if (container && container->IsScenceBoardWindow()) {
        for (const auto& windowScene : windowSceneSet_) {
            if (!windowScene.Upgrade()) {
                continue;
            }
            for (const auto& child : windowScene.Upgrade()->GetChildren()) {
                auto node = DynamicCast<FrameNode>(child);
                if (node && node->GetTag() == V2::MENU_WRAPPER_ETS_TAG) {
                    PopMenuAnimation(node);
                }
            }
        }
        return;
    }

    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_VOID(rootNode);
    for (const auto& child : rootNode->GetChildren()) {
        auto node = DynamicCast<FrameNode>(child);
        if (node && node->GetTag() == V2::MENU_WRAPPER_ETS_TAG) {
            PopMenuAnimation(node);
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

void OverlayManager::CleanMenuInSubWindowWithAnimation()
{
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_VOID(rootNode);
    RefPtr<FrameNode> menu;
    for (const auto& child : rootNode->GetChildren()) {
        auto node = DynamicCast<FrameNode>(child);
        if (node && node->GetTag() == V2::MENU_WRAPPER_ETS_TAG) {
            menu = node;
            break;
        }
    }
    CHECK_NULL_VOID(menu);
    AnimationOption option;
    option.SetCurve(Curves::FAST_OUT_SLOW_IN);
    option.SetDuration(MENU_ANIMATION_DURATION);
    option.SetFillMode(FillMode::FORWARDS);
    option.SetOnFinishEvent([weak = WeakClaim(this), id = Container::CurrentId()] {
        ContainerScope scope(id);
        auto context = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(context);
        context->GetTaskExecutor()->PostTask(
            [weak, id]() {
                ContainerScope scope(id);
                auto overlayManager = weak.Upgrade();
                overlayManager->CleanMenuInSubWindow();
            },
            TaskExecutor::TaskType::UI);
    });
    auto context = menu->GetRenderContext();
    CHECK_NULL_VOID(context);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto menuWrapperPattern = menu->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(menuWrapperPattern);
    auto menuAnimationOffset = menuWrapperPattern->GetAnimationOffset();
    if (menuWrapperPattern->GetPreviewMode() != MenuPreviewMode::NONE) {
        ShowPreviewDisappearAnimation(menuWrapperPattern);
        ShowContextMenuDisappearAnimation(option, menuWrapperPattern);
    } else {
        AnimationUtils::Animate(
            option,
            [context, menuAnimationOffset]() {
                context->UpdateOpacity(0.0);
                context->UpdateOffset(menuAnimationOffset);
            },
            option.GetOnFinishEvent());
    }
}

void OverlayManager::CleanPreviewInSubWindow()
{
    LOGD("OverlayManager::CleanPreviewInSubWindow");
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_VOID(rootNode);
    for (const auto& child : rootNode->GetChildren()) {
        auto node = DynamicCast<FrameNode>(child);
        if (node && node->GetTag() == V2::MENU_WRAPPER_ETS_TAG) {
            for (auto& childNode : node->GetChildren()) {
                auto frameNode = DynamicCast<FrameNode>(childNode);
                if (frameNode &&
                    (frameNode->GetTag() == V2::MENU_PREVIEW_ETS_TAG || frameNode->GetTag() == V2::IMAGE_ETS_TAG)) {
                    node->RemoveChild(frameNode);
                    break;
                }
            }
            break;
        }
    }
}

void OverlayManager::CleanMenuInSubWindow()
{
    LOGI("OverlayManager::CleanMenuInSubWindow");
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_VOID(rootNode);
    for (const auto& child : rootNode->GetChildren()) {
        auto node = DynamicCast<FrameNode>(child);
        if (node && node->GetTag() == V2::MENU_WRAPPER_ETS_TAG) {
            for (auto& childNode : node->GetChildren()) {
                auto frameNode = DynamicCast<FrameNode>(childNode);
                if (frameNode &&
                    (frameNode->GetTag() == V2::MENU_PREVIEW_ETS_TAG || frameNode->GetTag() == V2::IMAGE_ETS_TAG)) {
                    node->RemoveChild(frameNode);
                    break;
                }
            }
            rootNode->RemoveChild(node);
            rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
            break;
        }
    }

    for (const auto& child : rootNode->GetChildren()) {
        auto node = DynamicCast<FrameNode>(child);
        if (node && node->GetTag() == V2::COLUMN_ETS_TAG) {
            rootNode->RemoveChild(node);
            rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
            break;
        }
    }
}

void OverlayManager::BeforeShowDialog(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_VOID(node);
    if (dialogMap_.find(node->GetId()) != dialogMap_.end()) {
        LOGW("dialog #%{public}d exists", node->GetId());
        return;
    }
    dialogMap_[node->GetId()] = node;
}

RefPtr<FrameNode> OverlayManager::ShowDialog(
    const DialogProperties& dialogProps, std::function<void()>&& buildFunc, bool isRightToLeft)
{
    LOGI("OverlayManager::ShowDialog");
    RefPtr<UINode> customNode;
    // create custom builder content
    if (buildFunc) {
        NG::ScopedViewStackProcessor builderViewStackProcessor;
        buildFunc();
        customNode = NG::ViewStackProcessor::GetInstance()->Finish();
        CHECK_NULL_RETURN(customNode, nullptr);
    }

    auto dialog = DialogView::CreateDialogNode(dialogProps, customNode);
    BeforeShowDialog(dialog);
    OpenDialogAnimation(dialog);
    dialogCount_++;
    // set close button disable
    SetContainerButtonEnable(false);
    return dialog;
}

void OverlayManager::ShowCustomDialog(const RefPtr<FrameNode>& customNode)
{
    LOGI("OverlayManager::ShowCustomDialog");
    BeforeShowDialog(customNode);
    OpenDialogAnimation(customNode);
}

void OverlayManager::ShowDateDialog(const DialogProperties& dialogProps, const DatePickerSettingData& settingData,
    std::map<std::string, NG::DialogEvent> dialogEvent, std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent)
{
    LOGI("OverlayManager::ShowDateDialogPicker");
    auto dialogNode = DatePickerDialogView::Show(
        dialogProps, std::move(settingData), std::move(dialogEvent), std::move(dialogCancelEvent));
    BeforeShowDialog(dialogNode);
    OpenDialogAnimation(dialogNode);
}

void OverlayManager::ShowTimeDialog(const DialogProperties& dialogProps, const TimePickerSettingData& settingData,
    std::map<std::string, PickerTime> timePickerProperty, std::map<std::string, NG::DialogEvent> dialogEvent,
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent)
{
    LOGI("OverlayManager::ShowTimeDialogPicker");
    auto dialogNode = TimePickerDialogView::Show(
        dialogProps, settingData, std::move(timePickerProperty), std::move(dialogEvent), std::move(dialogCancelEvent));
    BeforeShowDialog(dialogNode);
    OpenDialogAnimation(dialogNode);
}

void OverlayManager::ShowTextDialog(const DialogProperties& dialogProps, const TextPickerSettingData& settingData,
    std::map<std::string, NG::DialogTextEvent> dialogEvent,
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent)
{
    LOGI("OverlayManager::ShowTextDialogPicker");
    auto dialogNode =
        TextPickerDialogView::Show(dialogProps, settingData, std::move(dialogEvent), std::move(dialogCancelEvent));
    BeforeShowDialog(dialogNode);
    OpenDialogAnimation(dialogNode);
}

void OverlayManager::ShowCalendarDialog(const DialogProperties& dialogProps, const CalendarSettingData& settingData,
    std::map<std::string, NG::DialogEvent> dialogEvent, std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent)
{
    auto dialogNode =
        CalendarDialogView::Show(dialogProps, settingData, std::move(dialogEvent), std::move(dialogCancelEvent));
    BeforeShowDialog(dialogNode);
    OpenDialogAnimation(dialogNode);
}

void OverlayManager::RemoveDialogFromMap(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_VOID(node);
    if (dialogMap_.find(node->GetId()) == dialogMap_.end()) {
        LOGW("dialog #%{public}d node in map", node->GetId());
        return;
    }
    dialogMap_.erase(node->GetId());
}

bool OverlayManager::DialogInMapHoldingFocus()
{
    if (dialogMap_.empty()) {
        return false;
    }
    auto iter = dialogMap_.begin();
    while (iter != dialogMap_.end()) {
        auto dialogNode = (*iter).second;
        if (dialogNode && dialogNode->GetFocusHub() && dialogNode->GetFocusHub()->IsCurrentFocus()) {
            return true;
        }
        iter++;
    }
    return false;
}

void OverlayManager::CloseDialog(const RefPtr<FrameNode>& dialogNode)
{
    LOGI("OverlayManager::CloseDialog");
    RemoveDialogFromMap(dialogNode);
    if (dialogNode->IsRemoving()) {
        // already in close animation
        return;
    }
    dialogNode->MarkRemoving();
    CloseDialogAnimation(dialogNode);
    dialogCount_--;
    // set close button enable
    if (dialogCount_ == 0) {
        SetContainerButtonEnable(true);
    }
    dialogNode->OnAccessibilityEvent(
        AccessibilityEventType::CHANGE, WindowsContentChangeTypes::CONTENT_CHANGE_TYPE_SUBTREE);
    CallOnHideDialogCallback();
}

bool OverlayManager::RemoveDialog(const RefPtr<FrameNode>& overlay, bool isBackPressed, bool isPageRouter)
{
    if (overlay->IsRemoving()) {
        return false;
    }
    if (FireBackPressEvent()) {
        return true;
    }
    auto hub = overlay->GetEventHub<DialogEventHub>();
    if (!isPageRouter && hub) {
        hub->FireCancelEvent();
    }
    CloseDialog(overlay);
    if (isBackPressed) {
        SetBackPressEvent(nullptr);
    }
    return true;
}

bool OverlayManager::RemoveBubble(const RefPtr<FrameNode>& overlay)
{
    auto bubbleEventHub = overlay->GetEventHub<BubbleEventHub>();
    CHECK_NULL_RETURN(bubbleEventHub, false);
    bubbleEventHub->FireChangeEvent(false);
    auto rootNode = overlay->GetParent();
    CHECK_NULL_RETURN(rootNode, false);
    for (const auto& popup : popupMap_) {
        auto targetId = popup.first;
        auto popupInfo = popup.second;
        if (overlay == popupInfo.popupNode) {
            popupMap_.erase(targetId);
            rootNode->RemoveChild(overlay);
            rootNode->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
            return true;
        }
    }
    return false;
}
bool OverlayManager::RemoveMenu(const RefPtr<FrameNode>& overlay)
{
    auto menuWrapperPattern = overlay->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_RETURN(menuWrapperPattern, false);
    menuWrapperPattern->HideMenu();
    return true;
}

bool OverlayManager::RemoveOverlay(bool isBackPressed, bool isPageRouter)
{
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_RETURN(rootNode, true);
    RemoveIndexerPopup();
    DestroyKeyboard();
    if (rootNode->GetChildren().size() > 1) {
        // stage node is at index 0, remove overlay at last
        auto overlay = DynamicCast<FrameNode>(rootNode->GetLastChild());
        CHECK_NULL_RETURN(overlay, false);
        // close dialog with animation
        auto pattern = overlay->GetPattern();
        if (InstanceOf<DialogPattern>(pattern)) {
            return RemoveDialog(overlay, isBackPressed, isPageRouter);
        }
        if (InstanceOf<BubblePattern>(pattern)) {
            return RemoveBubble(overlay);
        }
        if (InstanceOf<MenuWrapperPattern>(pattern)) {
            return RemoveMenu(overlay);
        }
        if (InstanceOf<ToastPattern>(pattern)) {
            return false;
        }
        // remove navDestination in navigation first
        do {
            auto pipeline = PipelineContext::GetCurrentContext();
            CHECK_NULL_BREAK(pipeline);
            auto navigationGroupNode =
                AceType::DynamicCast<NavigationGroupNode>(pipeline->FindNavigationNodeToHandleBack(overlay));
            CHECK_NULL_BREAK(navigationGroupNode);
            return true;
        } while (0);
        if (!modalStack_.empty()) {
            if (isPageRouter) {
                return RemoveAllModalInOverlay();
            } else {
                return RemoveModalInOverlay();
            }
        }
        rootNode->RemoveChild(overlay);
        rootNode->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
        LOGI("overlay removed successfully");
        return true;
    }
    LOGI("No overlay in this page.");
    return false;
}

bool OverlayManager::RemoveModalInOverlay()
{
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_RETURN(rootNode, true);
    auto topModalNode = modalStack_.top().Upgrade();
    CHECK_NULL_RETURN(topModalNode, false);
    ModalPageLostFocus(topModalNode);
    auto pattern = topModalNode->GetPattern<PopupBasePattern>();
    if (isProhibitBack_ && pattern->GetTargetId() < 0) {
        return true;
    }
    if (!ModalExitProcess(topModalNode)) {
        return false;
    }
    if (!modalStack_.empty()) {
        modalStack_.pop();
    }
    if (!modalList_.empty()) {
        modalList_.pop_back();
    }
    FireModalPageHide();
    SaveLastModalNode();
    return true;
}

bool OverlayManager::RemoveAllModalInOverlay()
{
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_RETURN(rootNode, true);
    while (!modalStack_.empty()) {
        auto topModalNode = modalStack_.top().Upgrade();
        if (!topModalNode) {
            modalStack_.pop();
            continue;
        }
        ModalPageLostFocus(topModalNode);
        if (!ModalExitProcess(topModalNode)) {
            continue;
        }
        if (!modalStack_.empty()) {
            modalStack_.pop();
        }
        if (!modalList_.empty()) {
            modalList_.pop_back();
        }
        FireModalPageHide();
        SaveLastModalNode();
    }
    return true;
}

bool OverlayManager::ModalExitProcess(const RefPtr<FrameNode>& topModalNode)
{
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_RETURN(rootNode, true);
    if (topModalNode->GetTag() == V2::MODAL_PAGE_TAG) {
        auto builder = AceType::DynamicCast<FrameNode>(topModalNode->GetFirstChild());
        CHECK_NULL_RETURN(builder, false);
        auto modalTransition = topModalNode->GetPattern<ModalPresentationPattern>()->GetType();
        if (builder->GetRenderContext()->HasTransition()) {
            if (!topModalNode->GetPattern<ModalPresentationPattern>()->IsExecuteOnDisappear()) {
                topModalNode->GetPattern<ModalPresentationPattern>()->OnDisappear();
            }
            topModalNode->Clean(false, true);
            topModalNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        }
        if (modalTransition == ModalTransition::DEFAULT) {
            PlayDefaultModalTransition(topModalNode, false);
        } else if (modalTransition == ModalTransition::ALPHA) {
            PlayAlphaModalTransition(topModalNode, false);
        } else if (!builder->GetRenderContext()->HasTransition()) {
            topModalNode->GetPattern<ModalPresentationPattern>()->OnDisappear();
            rootNode->RemoveChild(topModalNode);
            rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        }
        topModalNode->GetPattern<ModalPresentationPattern>()->FireCallback("false");
    } else if (topModalNode->GetTag() == V2::SHEET_PAGE_TAG) {
        auto builder = AceType::DynamicCast<FrameNode>(topModalNode->GetLastChild());
        CHECK_NULL_RETURN(builder, false);
        if (builder->GetRenderContext()->HasTransition()) {
            if (!topModalNode->GetPattern<SheetPresentationPattern>()->IsExecuteOnDisappear()) {
                topModalNode->GetPattern<SheetPresentationPattern>()->OnDisappear();
            }
            topModalNode->Clean(false, true);
            topModalNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        }
        auto maskNode = GetSheetMask(topModalNode);
        if (maskNode) {
            PlaySheetMaskTransition(maskNode, false);
        }
        PlaySheetTransition(topModalNode, false);
        topModalNode->GetPattern<SheetPresentationPattern>()->FireCallback("false");
    }
    return true;
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
    if (InstanceOf<DialogPattern>(pattern)) {
        return RemoveDialog(overlay, false, false);
    }
    if (InstanceOf<BubblePattern>(pattern)) {
        auto popupPattern = DynamicCast<BubblePattern>(pattern);
        overlay->GetEventHub<BubbleEventHub>()->FireChangeEvent(false);
        for (const auto& popup : popupMap_) {
            auto targetId = popup.first;
            auto popupInfo = popup.second;
            if (overlay == popupInfo.popupNode) {
                popupMap_.erase(targetId);
                rootNode->RemoveChild(overlay);
                rootNode->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
                if (rootNode->GetChildren().empty()) {
                    auto subwindow = SubwindowManager::GetInstance()->GetSubwindow(popupPattern->GetContainerId());
                    CHECK_NULL_RETURN(subwindow, false);
                    subwindow->HideSubWindowNG();
                }
                return true;
            }
        }
        return false;
    }
    if (InstanceOf<MenuWrapperPattern>(pattern)) {
        return RemoveMenu(overlay);
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
    focusHub->SetParentFocusable(true);
    focusHub->RequestFocusWithDefaultFocusFirstly();
}

void OverlayManager::BlurOverlayNode(const RefPtr<FrameNode>& currentOverlay, bool isInSubWindow)
{
    LOGI("OverlayManager::BlurOverlayNode");
    auto currentFocusHub = currentOverlay->GetOrCreateFocusHub();
    CHECK_NULL_VOID(currentFocusHub);
    currentFocusHub->SetParentFocusable(false);
    currentFocusHub->LostFocus();

    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_VOID(rootNode);
    if (rootNode->GetChildren().size() > 1) {
        auto collection = rootNode->GetChildren();
        for (auto iter = collection.rbegin(); iter != collection.rend(); ++iter) {
            auto overlay = DynamicCast<FrameNode>(*iter);
            CHECK_NULL_VOID(overlay);
            auto pattern = overlay->GetPattern();
            if (currentOverlay != overlay &&
                (InstanceOf<DialogPattern>(pattern) || InstanceOf<MenuWrapperPattern>(pattern)) &&
                !overlay->IsRemoving()) {
                FocusOverlayNode(overlay, isInSubWindow);
                return;
            }
        }
    }
    if (isInSubWindow) {
        // no need to set page request focus in sub window.
        return;
    }

    auto pageNode = GetLastPage();
    CHECK_NULL_VOID(pageNode);
    auto pageFocusHub = pageNode->GetFocusHub();
    CHECK_NULL_VOID(pageFocusHub);
    pageFocusHub->SetParentFocusable(true);
    pageFocusHub->RequestFocus();
}

void OverlayManager::BlurLowerNode(const RefPtr<FrameNode>& currentOverlay)
{
    auto root = DynamicCast<FrameNode>(currentOverlay->GetParent());
    CHECK_NULL_VOID(root);
    auto children = root->GetChildren();
    for (auto iter = children.rbegin(); iter != children.rend(); ++iter) {
        auto node = DynamicCast<FrameNode>(*iter);
        CHECK_NULL_VOID(node);
        if (currentOverlay == node) {
            continue;
        }
        if (node->GetTag() == V2::STAGE_ETS_TAG) {
            auto pageNode = GetLastPage();
            CHECK_NULL_VOID(pageNode);
            auto pageFocusHub = pageNode->GetFocusHub();
            CHECK_NULL_VOID(pageFocusHub);
            pageFocusHub->SetParentFocusable(false);
            pageFocusHub->LostFocus();
            return;
        }
        auto focusHub = node->GetOrCreateFocusHub();
        if (focusHub->IsCurrentFocus()) {
            focusHub->SetParentFocusable(false);
            focusHub->LostFocus();
            return;
        }
    }
}

void OverlayManager::ResetLowerNodeFocusable(const RefPtr<FrameNode>& currentOverlay)
{
    CHECK_NULL_VOID(currentOverlay);
    auto root = DynamicCast<FrameNode>(currentOverlay->GetParent());
    CHECK_NULL_VOID(root);
    auto children = root->GetChildren();
    for (auto iter = children.rbegin(); iter != children.rend(); ++iter) {
        auto node = DynamicCast<FrameNode>(*iter);
        CHECK_NULL_VOID(node);
        if (currentOverlay == node) {
            continue;
        }
        if (node->GetTag() == V2::STAGE_ETS_TAG) {
            auto pageNode = GetLastPage();
            CHECK_NULL_VOID(pageNode);
            auto pageFocusHub = pageNode->GetFocusHub();
            CHECK_NULL_VOID(pageFocusHub);
            pageFocusHub->SetParentFocusable(true);
            return;
        }
        auto focusHub = node->GetOrCreateFocusHub();
        if (focusHub->IsCurrentFocus()) {
            focusHub->SetParentFocusable(true);
            return;
        }
    }
}

void OverlayManager::SaveLastModalNode()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto stageManager = pipeline->GetStageManager();
    CHECK_NULL_VOID(stageManager);
    auto pageNode = stageManager->GetLastPage();
    CHECK_NULL_VOID(pageNode);
    if (modalStack_.empty()) {
        lastModalNode_ = WeakClaim(RawPtr(pageNode));
    } else {
        auto topModalNode = modalStack_.top().Upgrade();
        modalStack_.pop();
        if (modalStack_.empty()) {
            lastModalNode_ = WeakClaim(RawPtr(pageNode));
        } else {
            lastModalNode_ = modalStack_.top();
        }
        modalStack_.push(topModalNode);
    }
}

void OverlayManager::BindContentCover(bool isShow, std::function<void(const std::string&)>&& callback,
    std::function<RefPtr<UINode>()>&& buildNodeFunc, NG::ModalStyle& modalStyle, std::function<void()>&& onAppear,
    std::function<void()>&& onDisappear, int32_t targetId)
{
    LOGI("BindContentCover isShow: %{public}d, targetId: %{public}d", isShow, targetId);
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_VOID(rootNode);
    auto modalTransition = modalStyle.modalTransition;
    if (!modalTransition.has_value()) {
        modalTransition = ModalTransition::DEFAULT;
    }
    if (isShow) {
        if (!modalStack_.empty()) {
            auto topModalNode = modalStack_.top().Upgrade();
            CHECK_NULL_VOID(topModalNode);
            if (topModalNode->GetTag() == V2::MODAL_PAGE_TAG) {
                if (topModalNode->GetPattern<ModalPresentationPattern>()->GetTargetId() == targetId) {
                    if (modalStyle.backgroundColor.has_value()) {
                        topModalNode->GetRenderContext()->UpdateBackgroundColor(modalStyle.backgroundColor.value());
                    }
                    topModalNode->GetPattern<ModalPresentationPattern>()->UpdateOnDisappear(std::move(onDisappear));
                    topModalNode->GetPattern<ModalPresentationPattern>()->SetType(modalTransition.value());
                    return;
                }
            }
        }
        // builder content
        auto builder = AceType::DynamicCast<FrameNode>(buildNodeFunc());
        CHECK_NULL_VOID(builder);
        builder->GetRenderContext()->SetIsModalRootNode(true);

        // create modal page
        auto modalNode = FrameNode::CreateFrameNode(V2::MODAL_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            AceType::MakeRefPtr<ModalPresentationPattern>(
                targetId, static_cast<ModalTransition>(modalTransition.value()), std::move(callback)));
        if (modalStyle.backgroundColor.has_value()) {
            modalNode->GetRenderContext()->UpdateBackgroundColor(modalStyle.backgroundColor.value());
        }
        modalNode->GetPattern<ModalPresentationPattern>()->UpdateOnDisappear(std::move(onDisappear));
        modalStack_.push(WeakClaim(RawPtr(modalNode)));
        modalList_.emplace_back(WeakClaim(RawPtr(modalNode)));
        SaveLastModalNode();
        modalNode->MountToParent(rootNode);
        modalNode->AddChild(builder);
        FireModalPageShow();
        rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        if (onAppear != nullptr) {
            onAppear();
        }
        if (modalTransition == ModalTransition::DEFAULT) {
            PlayDefaultModalTransition(modalNode, true);
        } else if (modalTransition == ModalTransition::ALPHA) {
            PlayAlphaModalTransition(modalNode, true);
        }
        return;
    }
    if (!modalStack_.empty()) {
        auto topModalNode = modalStack_.top().Upgrade();
        CHECK_NULL_VOID(topModalNode);
        if (topModalNode->GetTag() != V2::MODAL_PAGE_TAG) {
            return;
        }
        if (topModalNode->GetPattern<ModalPresentationPattern>()->GetTargetId() != targetId) {
            DeleteModal(targetId);
            return;
        }
        auto builder = AceType::DynamicCast<FrameNode>(topModalNode->GetFirstChild());
        CHECK_NULL_VOID(builder);
        if (builder->GetRenderContext()->HasTransition()) {
            if (!topModalNode->GetPattern<ModalPresentationPattern>()->IsExecuteOnDisappear()) {
                topModalNode->GetPattern<ModalPresentationPattern>()->OnDisappear();
            }
            topModalNode->Clean(false, true);
            topModalNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        }
        auto modalPresentationPattern = topModalNode->GetPattern<ModalPresentationPattern>();
        CHECK_NULL_VOID(modalPresentationPattern);
        modalTransition = modalPresentationPattern->GetType();
        // lost focus
        ModalPageLostFocus(topModalNode);
        if (modalTransition == ModalTransition::DEFAULT) {
            PlayDefaultModalTransition(topModalNode, false);
        } else if (modalTransition == ModalTransition::ALPHA) {
            PlayAlphaModalTransition(topModalNode, false);
        } else if (!builder->GetRenderContext()->HasTransition()) {
            if (!modalPresentationPattern->IsExecuteOnDisappear()) {
                modalPresentationPattern->OnDisappear();
            }
            rootNode->RemoveChild(topModalNode);
            rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        }
        modalStack_.pop();
        if (!modalList_.empty()) {
            modalList_.pop_back();
        }
        FireModalPageHide();
        SaveLastModalNode();
    }
}

void OverlayManager::FireModalPageShow()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto pageNode = pipeline->GetStageManager()->GetLastPage();
    CHECK_NULL_VOID(pageNode);
    auto pageFocusHub = pageNode->GetFocusHub();
    CHECK_NULL_VOID(pageFocusHub);
    pageFocusHub->SetParentFocusable(false);
    pageFocusHub->LostFocus();
    for (auto modal = modalList_.begin(); modal != modalList_.end(); modal++) {
        auto modalNode = (*modal).Upgrade();
        CHECK_NULL_VOID(modalNode);
        auto modalFocusHub = modalNode->GetFocusHub();
        CHECK_NULL_VOID(modalFocusHub);
        modalFocusHub->SetParentFocusable(false);
        modalFocusHub->LostFocus();
    }
    if (modalList_.empty()) {
        return;
    }
    auto topModalNode = modalList_.back().Upgrade();
    CHECK_NULL_VOID(topModalNode);
    auto topModalFocusHub = topModalNode->GetFocusHub();
    CHECK_NULL_VOID(topModalFocusHub);
    topModalFocusHub->SetParentFocusable(true);
    topModalFocusHub->RequestFocusWithDefaultFocusFirstly();
}

void OverlayManager::ModalPageLostFocus(const RefPtr<FrameNode>& node)
{
    auto modalFocusHub = node->GetFocusHub();
    CHECK_NULL_VOID(modalFocusHub);
    modalFocusHub->SetParentFocusable(false);
    modalFocusHub->LostFocus();
}

void OverlayManager::FireModalPageHide()
{
    auto lastModalNode = lastModalNode_.Upgrade();
    CHECK_NULL_VOID(lastModalNode);
    auto lastModalFocusHub = lastModalNode->GetFocusHub();
    CHECK_NULL_VOID(lastModalFocusHub);
    lastModalFocusHub->SetParentFocusable(true);
    lastModalFocusHub->RequestFocus();
}

void OverlayManager::PlayDefaultModalTransition(const RefPtr<FrameNode>& modalNode, bool isTransitionIn)
{
    // current modal animation
    AnimationOption option;
    const RefPtr<InterpolatingSpring> curve = AceType::MakeRefPtr<InterpolatingSpring>(0.0f, 1.0f, 100.0f, 20.0f);
    option.SetCurve(curve);
    option.SetFillMode(FillMode::FORWARDS);
    auto context = modalNode->GetRenderContext();
    CHECK_NULL_VOID(context);

    auto rootHeight = GetRootHeight();
    auto modalPositionY = modalNode->GetGeometryNode()->GetFrameRect().GetY();
    auto showHeight = rootHeight - modalPositionY;

    if (isTransitionIn) {
        context->OnTransformTranslateUpdate({ 0.0f, showHeight, 0.0f });
        AnimationUtils::Animate(option, [context]() {
            if (context) {
                context->OnTransformTranslateUpdate({ 0.0f, 0.0f, 0.0f });
            }
        });
    } else {
        auto lastModalNode = lastModalNode_.Upgrade();
        CHECK_NULL_VOID(lastModalNode);
        auto lastModalContext = lastModalNode->GetRenderContext();
        CHECK_NULL_VOID(lastModalContext);
        lastModalContext->UpdateOpacity(1.0);
        option.SetOnFinishEvent(
            [rootWeak = rootNodeWeak_, modalWK = WeakClaim(RawPtr(modalNode)), id = Container::CurrentId()] {
                ContainerScope scope(id);
                auto context = PipelineContext::GetCurrentContext();
                CHECK_NULL_VOID(context);
                auto taskExecutor = context->GetTaskExecutor();
                CHECK_NULL_VOID(taskExecutor);
                // animation finish event should be posted to UI thread.
                taskExecutor->PostTask(
                    [rootWeak, modalWK, id]() {
                        auto modal = modalWK.Upgrade();
                        auto root = rootWeak.Upgrade();
                        CHECK_NULL_VOID(modal && root);
                        ContainerScope scope(id);
                        if (!modal->GetPattern<ModalPresentationPattern>()->IsExecuteOnDisappear()) {
                            modal->GetPattern<ModalPresentationPattern>()->OnDisappear();
                        }
                        root->RemoveChild(modal);
                        root->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
                    },
                    TaskExecutor::TaskType::UI);
            });
        context->OnTransformTranslateUpdate({ 0.0f, 0.0f, 0.0f });
        AnimationUtils::Animate(
            option,
            [context, showHeight]() {
                if (context) {
                    context->OnTransformTranslateUpdate({ 0.0f, showHeight, 0.0f });
                }
            },
            option.GetOnFinishEvent());
    }
}

void OverlayManager::PlayAlphaModalTransition(const RefPtr<FrameNode>& modalNode, bool isTransitionIn)
{
    AnimationOption option;
    option.SetCurve(Curves::FRICTION);
    option.SetDuration(FULL_MODAL_ALPHA_ANIMATION_DURATION);
    option.SetFillMode(FillMode::FORWARDS);
    auto lastModalNode = lastModalNode_.Upgrade();
    CHECK_NULL_VOID(lastModalNode);
    auto lastModalContext = lastModalNode->GetRenderContext();
    CHECK_NULL_VOID(lastModalContext);
    auto context = modalNode->GetRenderContext();
    CHECK_NULL_VOID(context);
    if (isTransitionIn) {
        // last page animation
        lastModalContext->OpacityAnimation(option, 1, 0);
        lastModalContext->UpdateOpacity(0);

        // current modal page animation
        context->OpacityAnimation(option, 0, 1);
    } else {
        // last page animation
        lastModalContext->OpacityAnimation(option, 0, 1);

        // current modal page animation
        option.SetOnFinishEvent(
            [rootWeak = rootNodeWeak_, modalWK = WeakClaim(RawPtr(modalNode)), id = Container::CurrentId()] {
                ContainerScope scope(id);
                auto context = PipelineContext::GetCurrentContext();
                CHECK_NULL_VOID(context);
                auto taskExecutor = context->GetTaskExecutor();
                CHECK_NULL_VOID(taskExecutor);
                // animation finish event should be posted to UI thread.
                taskExecutor->PostTask(
                    [rootWeak, modalWK, id]() {
                        auto modal = modalWK.Upgrade();
                        auto root = rootWeak.Upgrade();
                        CHECK_NULL_VOID(modal && root);
                        ContainerScope scope(id);
                        if (!modal->GetPattern<ModalPresentationPattern>()->IsExecuteOnDisappear()) {
                            modal->GetPattern<ModalPresentationPattern>()->OnDisappear();
                        }
                        root->RemoveChild(modal);
                        root->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
                    },
                    TaskExecutor::TaskType::UI);
            });
        context->OpacityAnimation(option, 1, 0);
    }
}

void OverlayManager::BindSheet(bool isShow, std::function<void(const std::string&)>&& callback,
    std::function<RefPtr<UINode>()>&& buildNodeFunc, NG::SheetStyle& sheetStyle, std::function<void()>&& onAppear,
    std::function<void()>&& onDisappear, int32_t targetId)
{
    LOGI("BindSheet isShow: %{public}d, targetId: %{public}d", isShow, targetId);
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_VOID(rootNode);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    if (isShow) {
        if (!modalStack_.empty()) {
            auto topModalNode = modalStack_.top().Upgrade();
            CHECK_NULL_VOID(topModalNode);
            if (topModalNode->GetTag() == V2::SHEET_PAGE_TAG) {
                if (topModalNode->GetPattern<SheetPresentationPattern>()->GetTargetId() == targetId) {
                    if (sheetStyle.backgroundColor.has_value()) {
                        topModalNode->GetRenderContext()->UpdateBackgroundColor(sheetStyle.backgroundColor.value());
                    }
                    topModalNode->GetPattern<SheetPresentationPattern>()->UpdateOnDisappear(std::move(onDisappear));
                    auto layoutProperty = topModalNode->GetLayoutProperty<SheetPresentationProperty>();
                    layoutProperty->UpdateSheetStyle(sheetStyle);
                    topModalNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
                    bool isModeChangeToAuto = false;
                    if (sheetStyle.sheetMode.has_value() && sheetStyle.sheetMode == SheetMode::AUTO) {
                        layoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT_CROSS_AXIS);
                        isModeChangeToAuto = true;
                    } else {
                        layoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
                    }
                    pipeline->FlushUITasks();
                    ComputeSheetOffset(sheetStyle, topModalNode);
                    PlaySheetTransition(topModalNode, true, false, isModeChangeToAuto);
                    return;
                }
            }
        }
        // builder content
        auto builder = AceType::DynamicCast<FrameNode>(buildNodeFunc());
        CHECK_NULL_VOID(builder);
        builder->GetRenderContext()->SetIsModalRootNode(true);
        // create modal page
        auto sheetNode = SheetView::CreateSheetPage(targetId, builder, std::move(callback), sheetStyle);
        if (sheetStyle.backgroundColor.has_value()) {
            sheetNode->GetRenderContext()->UpdateBackgroundColor(sheetStyle.backgroundColor.value());
        }
        sheetNode->GetPattern<SheetPresentationPattern>()->UpdateOnDisappear(std::move(onDisappear));
        modalStack_.push(WeakClaim(RawPtr(sheetNode)));
        SaveLastModalNode();
        // create maskColor node
        if (sheetStyle.maskColor.has_value()) {
            auto maskNode = FrameNode::CreateFrameNode(
                V2::SHEET_MASK_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
            maskNode->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_PARENT);
            maskNode->GetRenderContext()->UpdateBackgroundColor(sheetStyle.maskColor.value());
            maskNode->MountToParent(rootNode);
            PlaySheetMaskTransition(maskNode, true);
        }
        sheetNode->MountToParent(rootNode);
        modalList_.emplace_back(WeakClaim(RawPtr(sheetNode)));
        FireModalPageShow();
        rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        pipeline->FlushUITasks();
        ComputeSheetOffset(sheetStyle, sheetNode);
        if (onAppear != nullptr) {
            onAppear();
        }

        // start transition animation
        PlaySheetTransition(sheetNode, true);
        return;
    }

    if (!modalStack_.empty()) {
        auto topSheetNode = modalStack_.top().Upgrade();
        CHECK_NULL_VOID(topSheetNode);
        if (topSheetNode->GetTag() != V2::SHEET_PAGE_TAG) {
            return;
        }
        if (topSheetNode->GetPattern<SheetPresentationPattern>()->GetTargetId() != targetId) {
            DeleteModal(targetId);
            return;
        }
        auto builder = AceType::DynamicCast<FrameNode>(topSheetNode->GetLastChild());
        CHECK_NULL_VOID(builder);
        if (builder->GetRenderContext()->HasTransition()) {
            if (!topSheetNode->GetPattern<SheetPresentationPattern>()->IsExecuteOnDisappear()) {
                topSheetNode->GetPattern<SheetPresentationPattern>()->OnDisappear();
            }
            topSheetNode->GetPattern<SheetPresentationPattern>()->OnDisappear();
            topSheetNode->Clean(false, true);
            topSheetNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        }
        ModalPageLostFocus(topSheetNode);
        auto maskNode = GetSheetMask(topSheetNode);
        if (maskNode) {
            PlaySheetMaskTransition(maskNode, false);
        }
        PlaySheetTransition(topSheetNode, false);
        modalStack_.pop();
        if (!modalList_.empty()) {
            modalList_.pop_back();
        }
        FireModalPageHide();
        SaveLastModalNode();
    }
}

void OverlayManager::PlaySheetTransition(
    RefPtr<FrameNode> sheetNode, bool isTransitionIn, bool isFirstTransition, bool isModeChangeToAuto)
{
    // current sheet animation
    AnimationOption option;
    const RefPtr<InterpolatingSpring> curve = AceType::MakeRefPtr<InterpolatingSpring>(0.0f, 1.0f, 100.0f, 20.0f);
    option.SetCurve(curve);
    option.SetFillMode(FillMode::FORWARDS);
    auto context = sheetNode->GetRenderContext();
    CHECK_NULL_VOID(context);
    auto rootHeight = GetRootHeight();
    if (isTransitionIn) {
        auto offset = rootHeight - sheetHeight_;
        if (isFirstTransition) {
            context->OnTransformTranslateUpdate({ 0.0f, rootHeight, 0.0f });
        }
        if (isModeChangeToAuto) {
            option.SetDuration(0);
            option.SetCurve(Curves::LINEAR);
        }
        AnimationUtils::Animate(option, [context, offset]() {
            if (context) {
                context->OnTransformTranslateUpdate({ 0.0f, offset, 0.0f });
            }
        });
    } else {
        option.SetOnFinishEvent(
            [rootWeak = rootNodeWeak_, sheetWK = WeakClaim(RawPtr(sheetNode)), id = Container::CurrentId()] {
                ContainerScope scope(id);
                auto context = PipelineContext::GetCurrentContext();
                CHECK_NULL_VOID(context);
                auto taskExecutor = context->GetTaskExecutor();
                CHECK_NULL_VOID(taskExecutor);
                // animation finish event should be posted to UI thread.
                taskExecutor->PostTask(
                    [rootWeak, sheetWK, id]() {
                        auto sheet = sheetWK.Upgrade();
                        auto root = rootWeak.Upgrade();
                        CHECK_NULL_VOID(sheet && root);
                        ContainerScope scope(id);
                        if (!sheet->GetPattern<SheetPresentationPattern>()->IsExecuteOnDisappear()) {
                            sheet->GetPattern<SheetPresentationPattern>()->OnDisappear();
                        }
                        root->RemoveChild(sheet);
                        root->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
                    },
                    TaskExecutor::TaskType::UI);
            });
        AnimationUtils::Animate(
            option,
            [context, rootHeight]() {
                if (context) {
                    context->OnTransformTranslateUpdate({ 0.0f, rootHeight, 0.0f });
                }
            },
            option.GetOnFinishEvent());
    }
}

void OverlayManager::PlaySheetMaskTransition(RefPtr<FrameNode> maskNode, bool isTransitionIn)
{
    AnimationOption option;
    const RefPtr<InterpolatingSpring> curve = AceType::MakeRefPtr<InterpolatingSpring>(0.0f, 1.0f, 328.0f, 36.0f);
    option.SetCurve(curve);
    option.SetFillMode(FillMode::FORWARDS);
    auto context = maskNode->GetRenderContext();
    CHECK_NULL_VOID(context);
    if (isTransitionIn) {
        context->OpacityAnimation(option, 0.0, 1.0);
    } else {
        option.SetOnFinishEvent(
            [rootWeak = rootNodeWeak_, maskNodeWK = WeakClaim(RawPtr(maskNode)), id = Container::CurrentId()] {
                ContainerScope scope(id);
                auto context = PipelineContext::GetCurrentContext();
                CHECK_NULL_VOID(context);
                auto taskExecutor = context->GetTaskExecutor();
                CHECK_NULL_VOID(taskExecutor);
                // animation finish event should be posted to UI thread.
                taskExecutor->PostTask(
                    [rootWeak, maskNodeWK, id]() {
                        auto mask = maskNodeWK.Upgrade();
                        auto root = rootWeak.Upgrade();
                        CHECK_NULL_VOID(mask);
                        ContainerScope scope(id);
                        root->RemoveChild(mask);
                    },
                    TaskExecutor::TaskType::UI);
            });
        context->OpacityAnimation(option, 1.0, 0.0);
    }
}

void OverlayManager::ComputeSheetOffset(NG::SheetStyle& sheetStyle, RefPtr<FrameNode> sheetNode)
{
    auto sheetHeight = sheetNode->GetGeometryNode()->GetFrameSize().Height();
    auto largeHeight = sheetHeight - SHEET_BLANK_MINI_HEIGHT.ConvertToPx();
    if (sheetStyle.sheetMode.has_value()) {
        if (sheetStyle.sheetMode == SheetMode::MEDIUM) {
            sheetHeight_ = sheetHeight / 2; // 2 : half
        } else if (sheetStyle.sheetMode == SheetMode::LARGE) {
            sheetHeight_ = largeHeight;
        } else if (sheetStyle.sheetMode == SheetMode::AUTO) {
            sheetHeight_ = sheetHeight;
        }
    } else {
        double height = 0.0;
        if (sheetStyle.height->Unit() == DimensionUnit::PERCENT) {
            height = sheetStyle.height->ConvertToPxWithSize(sheetHeight);
        } else {
            height = sheetStyle.height->ConvertToPx();
        }
        if (height > largeHeight) {
            sheetHeight_ = largeHeight;
        } else if (height < 0) {
            sheetHeight_ = largeHeight;
        } else {
            sheetHeight_ = height;
        }
    }
}

void OverlayManager::DestroySheet(const RefPtr<FrameNode>& sheetNode, int32_t targetId)
{
    if (!modalStack_.empty()) {
        auto topSheetNode = modalStack_.top().Upgrade();
        CHECK_NULL_VOID(topSheetNode);
        if (topSheetNode->GetTag() != V2::SHEET_PAGE_TAG) {
            return;
        }
        if (topSheetNode->GetPattern<SheetPresentationPattern>()->GetTargetId() != targetId) {
            return;
        }
        auto rootNode = rootNodeWeak_.Upgrade();
        CHECK_NULL_VOID(rootNode);
        auto root = DynamicCast<FrameNode>(rootNode);
        ModalPageLostFocus(topSheetNode);
        auto maskNode = GetSheetMask(sheetNode);
        if (maskNode) {
            root->RemoveChild(maskNode);
        }
        sheetNode->GetPattern<SheetPresentationPattern>()->OnDisappear();
        root->RemoveChild(sheetNode);
        root->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        modalStack_.pop();
        modalList_.pop_back();
        FireModalPageHide();
        SaveLastModalNode();
    }
}

void OverlayManager::DeleteModal(int32_t targetId)
{
    LOGI("OverlayManager::DeleteModal");
    bool isDelete = false;
    bool isModal = true;
    for (auto modal = modalList_.begin(); modal != modalList_.end(); modal++) {
        auto modalNode = (*modal).Upgrade();
        if (!modalNode) {
            continue;
        }
        int32_t currentTargetId = -1;
        if (modalNode->GetTag() == V2::MODAL_PAGE_TAG) {
            isModal = true;
            currentTargetId = modalNode->GetPattern<ModalPresentationPattern>()->GetTargetId();
        } else if (modalNode->GetTag() == V2::SHEET_PAGE_TAG) {
            isModal = false;
            currentTargetId = modalNode->GetPattern<SheetPresentationPattern>()->GetTargetId();
        } else {
            LOGW("OverlayManager: modalNode %{public}d doesn't exist", targetId);
            return;
        }
        if (currentTargetId == targetId) {
            isDelete = true;
            modalList_.erase(modal);
            auto rootNode = rootNodeWeak_.Upgrade();
            CHECK_NULL_VOID(rootNode);
            if (isModal) {
                modalNode->GetPattern<ModalPresentationPattern>()->OnDisappear();
            } else {
                modalNode->GetPattern<SheetPresentationPattern>()->OnDisappear();
            }
            rootNode->RemoveChild(modalNode);
            rootNode->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
            break;
        }
    }
    if (isDelete) {
        while (!modalStack_.empty()) {
            modalStack_.pop();
        }
        for (auto modal = modalList_.begin(); modal != modalList_.end(); modal++) {
            modalStack_.push(*modal);
        }
        SaveLastModalNode();
    }
}

RefPtr<FrameNode> OverlayManager::GetSheetMask(const RefPtr<FrameNode>& sheetNode)
{
    // get bindsheet masknode
    CHECK_NULL_RETURN(sheetNode, NULL);
    auto rootNode = sheetNode->GetParent();
    CHECK_NULL_RETURN(rootNode, NULL);
    auto sheetChildIter = std::find(rootNode->GetChildren().begin(), rootNode->GetChildren().end(), sheetNode);
    if (sheetChildIter == rootNode->GetChildren().end()) {
        return NULL;
    }
    --sheetChildIter;
    CHECK_NULL_RETURN((*sheetChildIter), NULL);
    if (DynamicCast<FrameNode>(*sheetChildIter)->GetTag() != V2::SHEET_MASK_TAG) {
        return NULL;
    }
    return DynamicCast<FrameNode>(*sheetChildIter);
}

void OverlayManager::PlayKeyboardTransition(RefPtr<FrameNode> customKeyboard, bool isTransitionIn)
{
    CHECK_NULL_VOID(customKeyboard);
    AnimationOption option;
    if (isTransitionIn) {
        option.SetCurve(SHOW_CUSTOM_KEYBOARD_ANIMATION_CURVE);
    } else {
        option.SetCurve(HIDE_CUSTOM_KEYBOARD_ANIMATION_CURVE);
    }
    option.SetFillMode(FillMode::FORWARDS);
    auto context = customKeyboard->GetRenderContext();
    CHECK_NULL_VOID(context);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto pageNode = pipeline->GetStageManager()->GetLastPage();
    auto pageHeight = pageNode->GetGeometryNode()->GetFrameSize().Height();
    if (isTransitionIn) {
        context->OnTransformTranslateUpdate({ 0.0f, pageHeight, 0.0f });
        AnimationUtils::Animate(option, [context]() {
            if (context) {
                context->OnTransformTranslateUpdate({ 0.0f, 0.0f, 0.0f });
            }
        });
    } else {
        context->UpdateOpacity(1.0);
        option.SetOnFinishEvent([id = Container::CurrentId(), customKeyboard] {
            ContainerScope scope(id);
            auto taskExecutor = Container::CurrentTaskExecutor();
            CHECK_NULL_VOID(taskExecutor);
            // animation finish event should be posted to UI thread.
            taskExecutor->PostTask(
                [customKeyboard]() {
                    auto parent = customKeyboard->GetParent();
                    CHECK_NULL_VOID(parent);
                    parent->RemoveChild(customKeyboard);
                },
                TaskExecutor::TaskType::UI);
        });
        context->OnTransformTranslateUpdate({ 0.0f, 0.0f, 0.0f });
        AnimationUtils::Animate(
            option,
            [context, pageHeight]() {
                if (context) {
                    context->OnTransformTranslateUpdate({ 0.0f, pageHeight, 0.0f });
                }
            },
            option.GetOnFinishEvent());
    }
}

void OverlayManager::BindKeyboard(const std::function<void()>& keybordBuilder, int32_t targetId)
{
    if (customKeyboardMap_.find(targetId) != customKeyboardMap_.end()) {
        return;
    }
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_VOID(rootNode);
    auto customKeyboard = KeyboardView::CreateKeyboard(targetId, keybordBuilder);
    customKeyboard->MountToParent(rootNode);
    rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    customKeyboardMap_[targetId] = customKeyboard;
    PlayKeyboardTransition(customKeyboard, true);
}

void OverlayManager::CloseKeyboard(int32_t targetId)
{
    auto it = customKeyboardMap_.find(targetId);
    if (it == customKeyboardMap_.end()) {
        return;
    }
    auto customKeyboard = it->second;
    CHECK_NULL_VOID(customKeyboard);
    auto pattern = customKeyboard->GetPattern<KeyboardPattern>();
    CHECK_NULL_VOID(pattern);
    customKeyboardMap_.erase(pattern->GetTargetId());
    PlayKeyboardTransition(customKeyboard, false);
}

void OverlayManager::DestroyKeyboard()
{
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_VOID(rootNode);
    if (customKeyboardMap_.empty()) {
        return;
    }
    for (auto it = customKeyboardMap_.begin(); it != customKeyboardMap_.end();) {
        auto keyboard = it->second;
        rootNode->RemoveChild(keyboard);
        it = customKeyboardMap_.erase(it);
    }
    rootNode->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
}

// This function will be used in SceneBoard Thread only.
// if need to show the pop-up component,
//   it expects to receive the target component bound by the pop-up component to find the windowScene component.
// if need to hide the pop-up component,
//   it expects to receive the the pop-up component to return the parent component.
//   And the parent component will be the windowScene component exactly.
RefPtr<UINode> OverlayManager::FindWindowScene(RefPtr<FrameNode> targetNode)
{
    auto container = Container::Current();
    if (!container || !container->IsScenceBoardWindow()) {
        return rootNodeWeak_.Upgrade();
    }
    CHECK_NULL_RETURN(targetNode, nullptr);
    LOGI("FindWindowScene start");
    auto parent = targetNode->GetParent();
    while (parent && parent->GetTag() != V2::WINDOW_SCENE_ETS_TAG) {
        parent = parent->GetParent();
    }
    CHECK_NULL_RETURN(parent, nullptr);
    LOGI("FindWindowScene success");
    windowSceneSet_.insert(parent);
    return parent;
}

#ifdef ENABLE_DRAG_FRAMEWORK
void OverlayManager::MountFilterToWindowScene(const RefPtr<FrameNode>& columnNode, const RefPtr<UINode>& windowScene)
{
    CHECK_NULL_VOID(windowScene);
    columnNode->MountToParent(windowScene);
    columnNode->OnMountToParentDone();
    windowScene->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
    filterColumnNodeWeak_ = columnNode;
    hasFilter_ = true;
}

void OverlayManager::MountPixelMapToWindowScene(const RefPtr<FrameNode>& columnNode, const RefPtr<UINode>& windowScene)
{
    CHECK_NULL_VOID(windowScene);
    columnNode->MountToParent(windowScene);
    columnNode->OnMountToParentDone();
    windowScene->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
    pixmapColumnNodeWeak_ = columnNode;
    hasPixelMap_ = true;
}

void OverlayManager::MountEventToWindowScene(const RefPtr<FrameNode>& columnNode, const RefPtr<UINode>& windowScene)
{
    CHECK_NULL_VOID(windowScene);
    columnNode->MountToParent(windowScene);
    columnNode->OnMountToParentDone();
    eventColumnNodeWeak_ = columnNode;
    hasEvent_ = true;
}

void OverlayManager::MountPixelMapToRootNode(const RefPtr<FrameNode>& columnNode)
{
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_VOID(rootNode);
    columnNode->MountToParent(rootNode);
    columnNode->OnMountToParentDone();
    rootNode->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
    pixmapColumnNodeWeak_ = columnNode;
    hasPixelMap_ = true;
}

void OverlayManager::MountEventToRootNode(const RefPtr<FrameNode>& columnNode)
{
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_VOID(rootNode);
    columnNode->MountToParent(rootNode, 1);
    columnNode->OnMountToParentDone();
    eventColumnNodeWeak_ = columnNode;
    hasEvent_ = true;
}

void OverlayManager::RemovePixelMap()
{
    if (!hasPixelMap_) {
        return;
    }
    auto columnNode = pixmapColumnNodeWeak_.Upgrade();
    CHECK_NULL_VOID(columnNode);
    auto rootNode = columnNode->GetParent();
    CHECK_NULL_VOID(rootNode);
    rootNode->RemoveChild(columnNode);
    rootNode->RebuildRenderContextTree();
    rootNode->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
    hasPixelMap_ = false;
    isOnAnimation_ = false;
}

void OverlayManager::RemovePixelMapAnimation(bool startDrag, double x, double y)
{
    if (isOnAnimation_ || !hasPixelMap_) {
        return;
    }
    if (startDrag) {
        return;
    }
    auto columnNode = pixmapColumnNodeWeak_.Upgrade();
    CHECK_NULL_VOID(columnNode);
    auto imageNode = AceType::DynamicCast<FrameNode>(columnNode->GetFirstChild());
    CHECK_NULL_VOID(imageNode);
    auto imageContext = imageNode->GetRenderContext();
    CHECK_NULL_VOID(imageContext);
    auto hub = columnNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(hub);
    auto frameNode = hub->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    RefPtr<PixelMap> pixelMap = hub->GetPixelMap();
    CHECK_NULL_VOID(pixelMap);
    float scale = PIXELMAP_DRAG_SCALE;
    UpdatePixelMapScale(scale);
    int32_t width = pixelMap->GetWidth();
    int32_t height = pixelMap->GetHeight();

    auto shadow = imageContext->GetBackShadow();
    if (!shadow.has_value()) {
        shadow = Shadow::CreateShadow(ShadowStyle::None);
    }
    imageContext->UpdateBackShadow(shadow.value());
    AnimationOption option;
    option.SetCurve(Curves::SHARP);
    option.SetDuration(PIXELMAP_ANIMATION_DURATION);
    AnimationUtils::Animate(option, [imageContext, shadow]() mutable {
        if (imageContext) {
            auto color = shadow->GetColor();
            auto newColor = Color::FromARGB(1, color.GetRed(), color.GetGreen(), color.GetBlue());
            shadow->SetColor(newColor);
            imageContext->UpdateBackShadow(shadow.value());
            BorderRadiusProperty borderRadius;
            borderRadius.SetRadius(0.0_vp);
            imageContext->UpdateBorderRadius(borderRadius);
        }
    });

    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto menuTheme = pipelineContext->GetTheme<NG::MenuTheme>();
    CHECK_NULL_VOID(menuTheme);
    auto springMotionResponse = menuTheme->GetPreviewDisappearSpringMotionResponse();
    auto springMotionDampingFraction = menuTheme->GetPreviewDisappearSpringMotionDampingFraction();

    AnimationOption scaleOption;
    auto motion = AceType::MakeRefPtr<ResponsiveSpringMotion>(springMotionResponse, springMotionDampingFraction);
    scaleOption.SetCurve(motion);

    scaleOption.SetOnFinishEvent([this, id = Container::CurrentId()] {
        ContainerScope scope(id);
        LOGD("Drag window start with default pixelMap");
        Msdp::DeviceStatus::InteractionManager::GetInstance()->SetDragWindowVisible(true);
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto taskScheduler = pipeline->GetTaskExecutor();
        CHECK_NULL_VOID(taskScheduler);
        taskScheduler->PostTask(
            [overlayManager = AceType::Claim(this)]() {
                CHECK_NULL_VOID(overlayManager);
                overlayManager->RemovePixelMap();
            },
            TaskExecutor::TaskType::UI);
    });

    auto coordinateX = imageNode->GetOffsetRelativeToWindow().GetX() - frameNode->GetOffsetRelativeToWindow().GetX();
    auto coordinateY = imageNode->GetOffsetRelativeToWindow().GetY() - frameNode->GetOffsetRelativeToWindow().GetY();
    AnimationUtils::Animate(
        scaleOption,
        [imageContext, startDrag, x, y, width, height, scale, coordinateX, coordinateY]() {
            if (startDrag) {
                imageContext->UpdatePosition(OffsetT<Dimension>(
                    Dimension(x - (x - coordinateX) * scale +
                              PIXELMAP_ANIMATION_DEFAULT_LIMIT_SCALE * width * (scale - PIXELMAP_DRAG_SCALE)),
                    Dimension(y - (y - coordinateY) * scale +
                              PIXELMAP_ANIMATION_DEFAULT_LIMIT_SCALE * height * (scale - PIXELMAP_DRAG_SCALE))));
                imageContext->UpdateTransformScale({ scale, scale });
                imageContext->OnModifyDone();
            } else {
                imageContext->UpdateTransformScale(VectorF(1.0f, 1.0f));
            }
        },
        scaleOption.GetOnFinishEvent());
    isOnAnimation_ = true;
}

void OverlayManager::UpdatePixelMapScale(float& scale)
{
    auto columnNode = pixmapColumnNodeWeak_.Upgrade();
    CHECK_NULL_VOID(columnNode);
    auto hub = columnNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(hub);
    RefPtr<PixelMap> pixelMap = hub->GetPixelMap();
    CHECK_NULL_VOID(pixelMap);
    int32_t height = pixelMap->GetHeight();
    int32_t width = pixelMap->GetWidth();
    int32_t deviceWidth = SystemProperties::GetDeviceWidth();
    int32_t deviceHeight = SystemProperties::GetDeviceHeight();
    int32_t maxDeviceLength = std::max(deviceHeight, deviceWidth);
    int32_t minDeviceLength = std::min(deviceHeight, deviceWidth);
    if (maxDeviceLength * PIXELMAP_DEFALUT_LIMIT_SCALE > minDeviceLength) {
        if (height > minDeviceLength * PIXELMAP_DEFALUT_LIMIT_SCALE) {
            scale = static_cast<float>(minDeviceLength * PIXELMAP_DEFALUT_LIMIT_SCALE) / height;
        }
    } else {
        if (hub->GetTextDraggable() && height > minDeviceLength / PIXELMAP_DRAG_WGR_SCALE &&
            width > minDeviceLength * PIXELMAP_DRAG_WGR_TEXT_SCALE / PIXELMAP_DRAG_WGR_SCALE) {
            scale = fmin(static_cast<float>(minDeviceLength / PIXELMAP_DRAG_WGR_SCALE) / height,
                static_cast<float>(minDeviceLength * PIXELMAP_DRAG_WGR_TEXT_SCALE / PIXELMAP_DRAG_WGR_SCALE) / width);
        } else if (height > minDeviceLength / PIXELMAP_DRAG_WGR_SCALE &&
                   width > minDeviceLength / PIXELMAP_DRAG_WGR_SCALE) {
            scale = fmin(static_cast<float>(minDeviceLength / PIXELMAP_DRAG_WGR_SCALE) / height,
                static_cast<float>(minDeviceLength / PIXELMAP_DRAG_WGR_SCALE) / width);
        }
    }
}

void OverlayManager::RemoveFilterAnimation()
{
    if (!hasFilter_) {
        return;
    }
    auto filterNode = filterColumnNodeWeak_.Upgrade();
    CHECK_NULL_VOID(filterNode);
    auto filterContext = filterNode->GetRenderContext();
    CHECK_NULL_VOID(filterContext);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto menuTheme = pipelineContext->GetTheme<NG::MenuTheme>();
    CHECK_NULL_VOID(menuTheme);
    AnimationOption option;
    option.SetOnFinishEvent([weak = WeakClaim(this), id = Container::CurrentId()] {
        ContainerScope scope(id);
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto taskScheduler = pipeline->GetTaskExecutor();
        CHECK_NULL_VOID(taskScheduler);
        taskScheduler->PostTask(
            [weak]() {
                auto overlayManager = weak.Upgrade();
                CHECK_NULL_VOID(overlayManager);
                overlayManager->RemoveFilter();
            },
            TaskExecutor::TaskType::UI);
    });
    option.SetDuration(menuTheme->GetFilterAnimationDuration());
    option.SetCurve(Curves::SHARP);
    AnimationUtils::Animate(
        option,
        [filterContext]() {
            CHECK_NULL_VOID(filterContext);
            BlurStyleOption styleOption;
            styleOption.blurStyle = BlurStyle::NO_MATERIAL;
            filterContext->UpdateBackBlurStyle(styleOption);
        },
        option.GetOnFinishEvent());
}

void OverlayManager::RemoveFilter()
{
    if (!hasFilter_) {
        return;
    }
    auto columnNode = filterColumnNodeWeak_.Upgrade();
    CHECK_NULL_VOID(columnNode);
    auto rootNode = columnNode->GetParent();
    CHECK_NULL_VOID(rootNode);
    auto children = columnNode->GetChildren();
    rootNode->RemoveChild(columnNode);
    rootNode->RebuildRenderContextTree();
    hasFilter_ = false;
}

void OverlayManager::RemoveEventColumn()
{
    if (!hasEvent_) {
        return;
    }
    auto columnNode = eventColumnNodeWeak_.Upgrade();
    CHECK_NULL_VOID(columnNode);
    auto rootNode = columnNode->GetParent();
    CHECK_NULL_VOID(rootNode);
    rootNode->RemoveChild(columnNode);
    hasEvent_ = false;
}
#endif // ENABLE_DRAG_FRAMEWORK

int32_t OverlayManager::CreateModalUIExtension(
    const AAFwk::Want& want, const ModalUIExtensionCallbacks& callbacks, bool isProhibitBack)
{
    isProhibitBack_ = isProhibitBack;
    ModalStyle modalStyle;
    modalStyle.modalTransition = NG::ModalTransition::NONE;
    auto uiExtNode = ModalUIExtension::Create(want, callbacks);
    auto layoutProperty = uiExtNode->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, 0);
    auto full = CalcLength(Dimension(1.0, DimensionUnit::PERCENT));
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(full, full));
    auto buildNodeFunc = [uiExtNode]() -> RefPtr<UINode> {
        uiExtNode->MarkModifyDone();
        return uiExtNode;
    };
    auto sessionId = ModalUIExtension::GetSessionId(uiExtNode);
    // Convert the sessionId into a negative number to distinguish it from the targetId of other modal pages
    BindContentCover(true, nullptr, std::move(buildNodeFunc), modalStyle, nullptr, nullptr, -(sessionId));
    return sessionId;
}

void OverlayManager::CloseModalUIExtension(int32_t sessionId)
{
    ModalStyle modalStyle;
    modalStyle.modalTransition = NG::ModalTransition::NONE;
    BindContentCover(false, nullptr, nullptr, modalStyle, nullptr, nullptr, -(sessionId));
}

void OverlayManager::MarkDirty(PropertyChangeFlag flag)
{
    auto root = rootNodeWeak_.Upgrade();
    CHECK_NULL_VOID(root);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    for (auto&& child : root->GetChildren()) {
        // first child is Stage node in main window, subwindow not has Stage node.
        if (child != root->GetFirstChild() || pipeline->IsSubPipeline()) {
            child->MarkDirtyNode(flag);
        }
    }
}

float OverlayManager::GetRootHeight() const
{
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_RETURN(rootNode, 0.0);
    auto rootGeometryNode = AceType::DynamicCast<FrameNode>(rootNode)->GetGeometryNode();
    CHECK_NULL_RETURN(rootGeometryNode, 0.0);
    auto rootHeight = rootGeometryNode->GetFrameSize().Height();
    return rootHeight;
}
} // namespace OHOS::Ace::NG
