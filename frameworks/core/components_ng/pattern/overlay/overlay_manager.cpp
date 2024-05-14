/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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
#include <vector>

#include "base/error/error_code.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/log/log.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/subwindow/subwindow_manager.h"
#include "base/utils/measure_util.h"
#include "base/utils/system_properties.h"
#include "base/utils/utils.h"
#include "core/animation/animation_pub.h"
#include "core/animation/spring_curve.h"
#include "core/common/ace_application_info.h"
#include "core/common/ace_engine.h"
#include "core/common/container.h"
#include "core/common/interaction/interaction_interface.h"
#include "core/common/modal_ui_extension.h"
#include "core/common/recorder/event_recorder.h"
#include "core/components/common/properties/color.h"
#include "core/components/select/select_theme.h"
#include "core/components/text_overlay/text_overlay_theme.h"
#include "core/components/toast/toast_theme.h"
#include "core/components_ng/animation/geometry_transition.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/focus_hub.h"
#include "core/components_ng/pattern/bubble/bubble_event_hub.h"
#include "core/components_ng/pattern/bubble/bubble_pattern.h"
#include "core/components_ng/pattern/calendar_picker/calendar_dialog_view.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_view.h"
#include "core/components_ng/pattern/menu/menu_layout_property.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/menu/menu_theme.h"
#include "core/components_ng/pattern/menu/menu_view.h"
#include "core/components_ng/pattern/menu/preview/menu_preview_pattern.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_group_node.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/overlay/keyboard_base_pattern.h"
#include "core/components_ng/pattern/overlay/keyboard_view.h"
#include "core/components_ng/pattern/overlay/modal_presentation_pattern.h"
#include "core/components_ng/pattern/overlay/overlay_container_pattern.h"
#include "core/components_ng/pattern/overlay/popup_base_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_drag_bar_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_property.h"
#include "core/components_ng/pattern/overlay/sheet_view.h"
#include "core/components_ng/pattern/picker/datepicker_dialog_view.h"
#include "core/components_ng/pattern/stage/stage_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "core/components_ng/pattern/text_picker/textpicker_dialog_view.h"
#include "core/components_ng/pattern/time_picker/timepicker_dialog_view.h"
#include "core/components_ng/pattern/toast/toast_pattern.h"
#include "core/components_ng/pattern/video/video_full_screen_pattern.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/pipeline_base.h"
#include "core/pipeline/pipeline_context.h"
#ifdef WEB_SUPPORTED
#include "core/components_ng/pattern/web/web_pattern.h"
#endif

namespace OHOS::Ace::NG {
namespace {
// should be moved to theme.
constexpr int32_t TOAST_ANIMATION_DURATION = 100;
constexpr int32_t MENU_ANIMATION_DURATION = 150;
constexpr float TOAST_ANIMATION_POSITION = 15.0f;

constexpr float PIXELMAP_DRAG_SCALE = 1.0f;
constexpr float NUM_FLOAT_2 = 2.0f;
constexpr int32_t PIXELMAP_ANIMATION_DURATION = 250;
constexpr float PIXELMAP_ANIMATION_DEFAULT_LIMIT_SCALE = 0.5f;

constexpr int32_t FULL_MODAL_ALPHA_ANIMATION_DURATION = 200;

constexpr int32_t SHEET_HALF_SIZE = 2;
// dialog animation params
const RefPtr<Curve> SHOW_SCALE_ANIMATION_CURVE = AceType::MakeRefPtr<CubicCurve>(0.38f, 1.33f, 0.6f, 1.0f);

constexpr int32_t ROOT_MIN_NODE = 1;
constexpr int32_t TOAST_MIN_NODE = 2;

// custom keyboard animation params
const RefPtr<Curve> SHOW_CUSTOM_KEYBOARD_ANIMATION_CURVE =
    AceType::MakeRefPtr<InterpolatingSpring>(0.0f, 1.0f, 342.0f, 37.0f);
const RefPtr<Curve> HIDE_CUSTOM_KEYBOARD_ANIMATION_CURVE =
    AceType::MakeRefPtr<InterpolatingSpring>(4.0f, 1.0f, 342.0f, 37.0f);

const RefPtr<InterpolatingSpring> MENU_ANIMATION_CURVE =
    AceType::MakeRefPtr<InterpolatingSpring>(0.0f, 1.0f, 228.0f, 22.0f);
constexpr Dimension ORIGINAL_BLUR_RADIUS = 20.0_px;
constexpr double MENU_ORIGINAL_SCALE = 0.6f;

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
    if (menuWrapperPattern->HasPreviewTransitionEffect()) {
        auto layoutProperty = previewChild->GetLayoutProperty();
        layoutProperty->UpdateVisibility(VisibleType::INVISIBLE, true);
        return;
    }

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
    float previewScale = 1.0f;
    if (menuPattern->GetPreviewMode() == MenuPreviewMode::IMAGE) {
        auto previewGeometryNode = previewChild->GetGeometryNode();
        CHECK_NULL_VOID(previewGeometryNode);
        auto preivewSize = previewGeometryNode->GetFrameSize();
        if (!NearEqual(menuPattern->GetTargetSize().Width(), preivewSize.Width())) {
            previewScale = menuPattern->GetTargetSize().Width() / preivewSize.Width();
        }
    }
    AnimationUtils::Animate(scaleOption, [previewRenderContext, previewPosition, previewScale]() {
        if (previewRenderContext) {
            previewRenderContext->UpdateTransformScale(VectorF(previewScale, previewScale));
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

void UpdateContextMenuDisappearPositionAnimation(const RefPtr<FrameNode>& menu, const NG::OffsetF& offset)
{
    CHECK_NULL_VOID(menu);
    auto menuWrapperPattern = menu->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(menuWrapperPattern);
    auto menuChild = menuWrapperPattern->GetMenu();
    CHECK_NULL_VOID(menuChild);
    auto menuRenderContext = menuChild->GetRenderContext();
    CHECK_NULL_VOID(menuRenderContext);
    auto menuPattern = menuChild->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    auto menuPosition = menuPattern->GetEndOffset();
    menuPosition += offset;
    menuPattern->SetEndOffset(menuPosition);

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
}

void ShowContextMenuDisappearAnimation(
    AnimationOption& option, const RefPtr<MenuWrapperPattern>& menuWrapperPattern, bool startDrag = false)
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
    if (startDrag) {
        menuRenderContext->UpdateTransformScale(
            VectorF(menuTheme->GetMenuDragAnimationScale(), menuTheme->GetMenuDragAnimationScale()));
    }
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

void ShowMenuDisappearAnimation(AnimationOption& option, const RefPtr<MenuWrapperPattern>& menuWrapperPattern)
{
    CHECK_NULL_VOID(menuWrapperPattern);
    auto menuNode = menuWrapperPattern->GetMenu();
    CHECK_NULL_VOID(menuNode);
    auto menuRenderContext = menuNode->GetRenderContext();
    CHECK_NULL_VOID(menuRenderContext);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    auto menuPosition = menuPattern->GetEndOffset();
    option.SetCurve(MENU_ANIMATION_CURVE);
    AnimationUtils::Animate(option, [menuRenderContext, menuPosition]() {
        if (menuRenderContext) {
            menuRenderContext->UpdatePosition(
                OffsetT<Dimension>(Dimension(menuPosition.GetX()), Dimension(menuPosition.GetY())));
            menuRenderContext->UpdateTransformScale(VectorF(MENU_ORIGINAL_SCALE, MENU_ORIGINAL_SCALE));
            menuRenderContext->UpdateFrontBlurRadius(ORIGINAL_BLUR_RADIUS);
            menuRenderContext->UpdateOpacity(0.0f);
        }
    }, option.GetOnFinishEvent());
}
} // namespace

void OverlayManager::UpdateContextMenuDisappearPosition(const NG::OffsetF& offset)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto overlayManager = pipelineContext->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    overlayManager->UpdateDragMoveVector(offset);

    if (overlayManager->IsOriginDragMoveVector() || !overlayManager->IsUpdateDragMoveVector()) {
        return;
    }

    if (menuMap_.empty()) {
        return;
    }
    auto rootNode = rootNodeWeak_.Upgrade();
    for (const auto& child : rootNode->GetChildren()) {
        auto node = DynamicCast<FrameNode>(child);
        if (node && node->GetTag() == V2::MENU_WRAPPER_ETS_TAG) {
            UpdateContextMenuDisappearPositionAnimation(node, overlayManager->GetUpdateDragMoveVector());
        }
    }
}

void OverlayManager::PostDialogFinishEvent(const WeakPtr<FrameNode>& nodeWk)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "post dialog finishi event enter");
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto taskExecutor = context->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    // animation finish event should be posted to UI thread.
    taskExecutor->PostTask(
        [weak = WeakClaim(this), nodeWk, id = Container::CurrentId()]() {
            ContainerScope scope(id);
            auto overlayManager = weak.Upgrade();
            auto node = nodeWk.Upgrade();
            CHECK_NULL_VOID(overlayManager && node);
            SafeAreaExpandOpts opts = { .type = SAFE_AREA_TYPE_NONE };
            node->GetLayoutProperty()->UpdateSafeAreaExpandOpts(opts);
            overlayManager->OnDialogCloseEvent(node);
        },
        TaskExecutor::TaskType::UI, "ArkUIOverlayDialogCloseEvent");
}

void OverlayManager::OnDialogCloseEvent(const RefPtr<FrameNode>& node)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "on dialog close event enter");
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
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "open dialog animation");
    CHECK_NULL_VOID(node);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<DialogTheme>();
    CHECK_NULL_VOID(theme);
    auto root = rootNodeWeak_.Upgrade();
    auto dialogPattern = node->GetPattern<DialogPattern>();
    dialogPattern->CallDialogWillAppearCallback();
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
        [weak = WeakClaim(this), nodeWK = WeakPtr<FrameNode>(node), onFinish] {
            if (onFinish) {
                onFinish();
            }
            auto overlayManager = weak.Upgrade();
            auto node = nodeWK.Upgrade();
            CHECK_NULL_VOID(overlayManager && node);
            overlayManager->FocusOverlayNode(node);
            auto dialogPattern = node->GetPattern<DialogPattern>();
            dialogPattern->CallDialogDidAppearCallback();
        });
    auto ctx = node->GetRenderContext();
    option.SetFinishCallbackType(dialogPattern->GetOpenAnimation().has_value()
                            ? dialogPattern->GetOpenAnimation().value().GetFinishCallbackType()
                            : FinishCallbackType::REMOVED);
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
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "close dialog animation");
    CHECK_NULL_VOID(node);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<DialogTheme>();
    CHECK_NULL_VOID(theme);
    SafeAreaExpandOpts opts = { .type = SAFE_AREA_TYPE_KEYBOARD };
    node->GetLayoutProperty()->UpdateSafeAreaExpandOpts(opts);

    // default opacity animation params
    AnimationOption option;
    option.SetFillMode(FillMode::FORWARDS);
    option.SetCurve(Curves::SHARP);
    option.SetDuration(theme->GetAnimationDurationOut());
    // get customized animation params
    auto dialogPattern = node->GetPattern<DialogPattern>();
    dialogPattern->CallDialogWillDisappearCallback();
    option = dialogPattern->GetCloseAnimation().value_or(option);
    option.SetIteration(1);
    option.SetAnimationDirection(AnimationDirection::NORMAL);
    option.SetOnFinishEvent([weak = WeakClaim(this), nodeWk = WeakPtr<FrameNode>(node), id = Container::CurrentId()] {
        ContainerScope scope(id);
        auto overlayManager = weak.Upgrade();
        CHECK_NULL_VOID(overlayManager);
        overlayManager->PostDialogFinishEvent(nodeWk);
        auto node = nodeWk.Upgrade();
        CHECK_NULL_VOID(node);
        auto dialogPattern = node->GetPattern<DialogPattern>();
        dialogPattern->CallDialogDidDisappearCallback();
    });
    auto ctx = node->GetRenderContext();
    CHECK_NULL_VOID(ctx);
    option.SetFinishCallbackType(dialogPattern->GetOpenAnimation().has_value()
                            ? dialogPattern->GetOpenAnimation().value().GetFinishCallbackType()
                            : FinishCallbackType::REMOVED);
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

void OverlayManager::SetDialogTransitionEffect(const RefPtr<FrameNode>& node)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "set dialog transition");
    CHECK_NULL_VOID(node);
    auto root = rootNodeWeak_.Upgrade();
    auto dialogPattern = node->GetPattern<DialogPattern>();
    dialogPattern->CallDialogWillAppearCallback();

    auto layoutProperty = node->GetLayoutProperty();
    layoutProperty->UpdateVisibility(VisibleType::VISIBLE, true);

    auto ctx = node->GetRenderContext();
    CHECK_NULL_VOID(ctx);
    ctx->SetTransitionInCallback(
        [weak = WeakClaim(this), nodeWK = WeakPtr<FrameNode>(node)] {
            auto overlayManager = weak.Upgrade();
            auto node = nodeWK.Upgrade();
            CHECK_NULL_VOID(overlayManager && node);
            overlayManager->FocusOverlayNode(node);
            auto dialogPattern = node->GetPattern<DialogPattern>();
            dialogPattern->CallDialogDidAppearCallback();
        }
    );

    auto container = Container::Current();
    if (container && container->IsScenceBoardWindow()) {
        root = dialogPattern->GetDialogProperties().windowScene.Upgrade();
    }

    CHECK_NULL_VOID(root);
    node->MountToParent(root);
    root->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    BlurLowerNode(node);
    node->OnAccessibilityEvent(AccessibilityEventType::CHANGE, WindowsContentChangeTypes::CONTENT_CHANGE_TYPE_SUBTREE);
}

void OverlayManager::CloseDialogMatchTransition(const RefPtr<FrameNode>& node)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "close dialog match transition");
    CHECK_NULL_VOID(node);
    SafeAreaExpandOpts opts = { .type = SAFE_AREA_TYPE_KEYBOARD };
    node->GetLayoutProperty()->UpdateSafeAreaExpandOpts(opts);
    auto dialogPattern = node->GetPattern<DialogPattern>();
    dialogPattern->CallDialogWillDisappearCallback();

    auto ctx = node->GetRenderContext();
    CHECK_NULL_VOID(ctx);
    auto layoutProperty = node->GetLayoutProperty();
    layoutProperty->UpdateVisibility(VisibleType::INVISIBLE, true);
    if (ctx->HasDisappearTransition()) {
        ctx->SetTransitionOutCallback(
            [weak = WeakClaim(this), nodeWk = WeakPtr<FrameNode>(node), id = Container::CurrentId()] {
                ContainerScope scope(id);
                auto overlayManager = weak.Upgrade();
                CHECK_NULL_VOID(overlayManager);
                overlayManager->PostDialogFinishEvent(nodeWk);
                auto node = nodeWk.Upgrade();
                CHECK_NULL_VOID(node);
                auto dialogPattern = node->GetPattern<DialogPattern>();
                dialogPattern->CallDialogDidDisappearCallback();
        });
    } else {
        auto id = Container::CurrentId();
        ContainerScope scope(id);
        auto overlayManager = WeakClaim(this).Upgrade();
        CHECK_NULL_VOID(overlayManager);
        auto nodeWk = WeakPtr<FrameNode>(node);
        overlayManager->PostDialogFinishEvent(nodeWk);
        dialogPattern->CallDialogDidDisappearCallback();
    }
}

void OverlayManager::SetContainerButtonEnable(bool isEnabled)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetCloseButtonStatus(isEnabled);
}

void OverlayManager::UpdateMenuVisibility(const RefPtr<FrameNode>& menu)
{
    auto layoutProperty = menu->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateVisibility(VisibleType::VISIBLE, true);
}

void OverlayManager::OnShowMenuAnimationFinished(const WeakPtr<FrameNode> menuWK, const WeakPtr<OverlayManager> weak,
    int32_t instanceId)
{
    auto menu = menuWK.Upgrade();
    auto overlayManager = weak.Upgrade();
    CHECK_NULL_VOID(menu && overlayManager);
    ContainerScope scope(instanceId);
    overlayManager->FocusOverlayNode(menu);
    auto menuWrapperPattern = menu->GetPattern<MenuWrapperPattern>();
    menuWrapperPattern->CallMenuAppearCallback();
    menuWrapperPattern->SetMenuStatus(MenuStatus::SHOW);
}

void OverlayManager::ShowMenuAnimation(const RefPtr<FrameNode>& menu)
{
    BlurLowerNode(menu);
    auto wrapperPattern = menu->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(wrapperPattern);
    wrapperPattern->CallMenuAboutToAppearCallback();
    wrapperPattern->SetMenuStatus(MenuStatus::ON_SHOW_ANIMATION);
    if (wrapperPattern->HasTransitionEffect()) {
        UpdateMenuVisibility(menu);
        auto renderContext = menu->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        renderContext->SetTransitionInCallback(
            [weak = WeakClaim(this), menuWK = WeakClaim(RawPtr(menu)), id = Container::CurrentId()] {
                auto overlayManager = weak.Upgrade();
                CHECK_NULL_VOID(overlayManager);
                overlayManager->OnShowMenuAnimationFinished(menuWK, weak, id);
            });
        return;
    }
    AnimationOption option;
    option.SetCurve(Curves::FAST_OUT_SLOW_IN);
    option.SetDuration(MENU_ANIMATION_DURATION);
    option.SetFillMode(FillMode::FORWARDS);
    option.SetOnFinishEvent(
        [weak = WeakClaim(this), menuWK = WeakClaim(RawPtr(menu)), id = Container::CurrentId()] {
            auto overlayManager = weak.Upgrade();
            CHECK_NULL_VOID(overlayManager);
            overlayManager->OnShowMenuAnimationFinished(menuWK, weak, id);
        });

    if (wrapperPattern->GetPreviewMode() == MenuPreviewMode::CUSTOM) {
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        auto menuTheme = pipelineContext->GetTheme<NG::MenuTheme>();
        CHECK_NULL_VOID(menuTheme);
        option.SetDuration(menuTheme->GetContextMenuAppearDuration());
        auto previewChild = wrapperPattern->GetPreview();
        if (previewChild) {
            auto previewPattern = AceType::DynamicCast<MenuPreviewPattern>(previewChild->GetPattern());
            if (previewPattern) {
                previewPattern->SetFirstShow();
            }
        }
    }
    wrapperPattern->SetAniamtinOption(option);
    SetPatternFirstShow(menu);
}

void OverlayManager::SetPatternFirstShow(const RefPtr<FrameNode>& menu)
{
    auto wrapperPattern = menu->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(wrapperPattern);
    wrapperPattern->SetFirstShow();
    auto menuChild = wrapperPattern->GetMenu();
    CHECK_NULL_VOID(menuChild);
    auto menuPattern = AceType::DynamicCast<MenuPattern>(menuChild->GetPattern());
    CHECK_NULL_VOID(menuPattern);
    menuPattern->SetFirstShow();
    menuPattern->SetMenuShow();
}

void OverlayManager::OnPopMenuAnimationFinished(const WeakPtr<FrameNode> menuWK, const WeakPtr<UINode> rootWeak,
    const WeakPtr<OverlayManager> weak, int32_t instanceId)
{
    auto menu = menuWK.Upgrade();
    CHECK_NULL_VOID(menu);
    auto menuNode = AceType::DynamicCast<FrameNode>(menu->GetChildAtIndex(0));
    CHECK_NULL_VOID(menuNode);
    auto eventHub = menuNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabledInternal(true);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    auto root = rootWeak.Upgrade();
    auto overlayManager = weak.Upgrade();
    CHECK_NULL_VOID(overlayManager);

    overlayManager->SetContextMenuDragHideFinished(true);
    DragEventActuator::ExecutePreDragAction(PreDragStatus::PREVIEW_LANDING_FINISHED);
    auto menuWrapperPattern = menu->GetPattern<MenuWrapperPattern>();
    menuWrapperPattern->CallMenuDisappearCallback();
    menuWrapperPattern->SetMenuStatus(MenuStatus::HIDE);
    auto mainPipeline = PipelineContext::GetMainPipelineContext();
    if (mainPipeline && menuWrapperPattern->GetMenuDisappearCallback()) {
        mainPipeline->FlushPipelineImmediately();
    }
    // clear contextMenu then return
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    auto expandDisplay = theme->GetExpandDisplay();
    auto menuLayoutProp = menuPattern->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_VOID(menuLayoutProp);
    bool isShowInSubWindow = menuLayoutProp->GetShowInSubWindowValue(true);
    if (((menuWrapperPattern && menuWrapperPattern->IsContextMenu()) || (isShowInSubWindow && expandDisplay)) &&
        (menuPattern->GetTargetTag() != V2::SELECT_ETS_TAG)) {
        SubwindowManager::GetInstance()->ClearMenuNG(instanceId, menuWrapperPattern->GetTargetId());
        overlayManager->ResetContextMenuDragHideFinished();
        return;
    }
    overlayManager->RemoveMenuNotInSubWindow(menuWK, rootWeak, weak);
}

void OverlayManager::PopMenuAnimation(const RefPtr<FrameNode>& menu, bool showPreviewAnimation, bool startDrag)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "pop menu animation enter");
    auto wrapperPattern = menu->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(wrapperPattern);

    if (wrapperPattern->GetMenuStatus() == MenuStatus::ON_HIDE_ANIMATION) {
        return;
    }

    ResetLowerNodeFocusable(menu);
    ResetContextMenuDragHideFinished();
    RemoveMenuBadgeNode(menu);

    auto menuNode = AceType::DynamicCast<FrameNode>(menu->GetChildAtIndex(0));
    CHECK_NULL_VOID(menuNode);
    auto eventHub = menuNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabledInternal(false);

    wrapperPattern->CallMenuAboutToDisappearCallback();
    wrapperPattern->SetMenuStatus(MenuStatus::ON_HIDE_ANIMATION);
    if (wrapperPattern->HasTransitionEffect()) {
        if (wrapperPattern->GetPreviewMode() != MenuPreviewMode::NONE) {
            ShowPreviewDisappearAnimation(wrapperPattern);
        }
        auto renderContext = menu->GetRenderContext();
        if (renderContext->HasDisappearTransition()) {
            auto layoutProperty = menu->GetLayoutProperty();
            layoutProperty->UpdateVisibility(VisibleType::INVISIBLE, true);
            renderContext->SetTransitionOutCallback(
                [rootWeak = rootNodeWeak_, menuWK = WeakClaim(RawPtr(menu)), id = Container::CurrentId(),
                                    weak = WeakClaim(this)] {
                    ContainerScope scope(id);
                    auto overlayManager = weak.Upgrade();
                    CHECK_NULL_VOID(overlayManager);
                    overlayManager->OnPopMenuAnimationFinished(menuWK, rootWeak, weak, id);
                });
        } else {
            auto context = PipelineContext::GetCurrentContext();
            CHECK_NULL_VOID(context);
            auto taskExecutor = context->GetTaskExecutor();
            CHECK_NULL_VOID(taskExecutor);
            taskExecutor->PostTask(
                [rootWeak = rootNodeWeak_, menuWK = WeakClaim(RawPtr(menu)), id = Container::CurrentId(),
                    weak = WeakClaim(this)] {
                    ContainerScope scope(id);
                    auto overlayManager = weak.Upgrade();
                    CHECK_NULL_VOID(overlayManager);
                    overlayManager->OnPopMenuAnimationFinished(menuWK, rootWeak, weak, id);
                },
                TaskExecutor::TaskType::UI, "ArkUIOverlayPopMenuAnimation");
        }
        return;
    }

    AnimationOption option;
    option.SetCurve(Curves::FAST_OUT_SLOW_IN);
    option.SetDuration(MENU_ANIMATION_DURATION);
    option.SetFillMode(FillMode::FORWARDS);
    if (!startDrag) {
        DragEventActuator::ExecutePreDragAction(PreDragStatus::PREVIEW_LANDING_STARTED);
    }
    option.SetOnFinishEvent([rootWeak = rootNodeWeak_, menuWK = WeakClaim(RawPtr(menu)), id = Container::CurrentId(),
                                weak = WeakClaim(this)] {
        ContainerScope scope(id);
        auto overlayManager = weak.Upgrade();
        CHECK_NULL_VOID(overlayManager);
        overlayManager->OnPopMenuAnimationFinished(menuWK, rootWeak, weak, id);
    });
    ShowMenuClearAnimation(menu, option, showPreviewAnimation, startDrag);
}

void OverlayManager::ClearMenuAnimation(const RefPtr<FrameNode>& menu, bool showPreviewAnimation, bool startDrag)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "clear menu animation enter");
    ResetLowerNodeFocusable(menu);
    RemoveMenuBadgeNode(menu);
    AnimationOption option;
    option.SetCurve(Curves::FAST_OUT_SLOW_IN);
    option.SetDuration(MENU_ANIMATION_DURATION);
    option.SetFillMode(FillMode::FORWARDS);
    option.SetOnFinishEvent([rootWeak = rootNodeWeak_, menuWK = WeakClaim(RawPtr(menu)), id = Container::CurrentId(),
                                weak = WeakClaim(this)] {
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
        auto menuWrapperPattern = menu->GetPattern<MenuWrapperPattern>();
        // clear contextMenu then return
        if ((menuWrapperPattern && menuWrapperPattern->IsContextMenu())) {
            return;
        }
        overlayManager->BlurOverlayNode(menu);
        root->RemoveChild(menu);
        root->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    });
    ShowMenuClearAnimation(menu, option, showPreviewAnimation, startDrag);
}

void OverlayManager::ShowMenuClearAnimation(const RefPtr<FrameNode>& menu, AnimationOption& option,
    bool showPreviewAnimation, bool startDrag)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "show menu clear animation enter");
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
        ShowContextMenuDisappearAnimation(option, menuWrapperPattern, startDrag);
    } else if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        ShowMenuDisappearAnimation(option, menuWrapperPattern);
    } else {
        AnimationUtils::Animate(
            option,
            [context, menuAnimationOffset]() {
                context->UpdateOpacity(0.0);
                context->UpdateOffset(menuAnimationOffset);
            },
            option.GetOnFinishEvent());
#if defined(ANDROID_PLATFORM) || defined(IOS_PLATFORM)
        auto* transactionProxy = Rosen::RSTransactionProxy::GetInstance();
        if (transactionProxy != nullptr) {
            transactionProxy->FlushImplicitTransaction();
        }
#endif
    }
    // start animation immediately
    pipeline->RequestFrame();
}

void OverlayManager::ShowToast(const std::string& message, int32_t duration, const std::string& bottom,
    bool isRightToLeft, const ToastShowMode& showMode, int32_t alignment, std::optional<DimensionOffset> offset)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "show toast enter");
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto rootNode = context->GetRootElement();
    CHECK_NULL_VOID(rootNode);

    // only one toast
    for (auto [id, toastNodeWeak] : toastMap_) {
        rootNode->RemoveChild(toastNodeWeak.Upgrade());
    }
    toastMap_.clear();
    ToastInfo toastInfo = {message, duration, bottom, isRightToLeft, showMode, alignment, offset};
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    CHECK_NULL_VOID(toastNode);
    auto toastId = toastNode->GetId();
    // mount to parent
    toastNode->MountToParent(rootNode);
    rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    toastMap_[toastId] = toastNode;
    OpenToastAnimation(toastNode, duration);
}

void OverlayManager::OpenToastAnimation(const RefPtr<FrameNode>& toastNode, int32_t duration)
{
    auto toastId = toastNode->GetId();
    AnimationOption option;
    auto curve = AceType::MakeRefPtr<CubicCurve>(0.2f, 0.0f, 0.1f, 1.0f);
    option.SetCurve(curve);
    option.SetDuration(TOAST_ANIMATION_DURATION);
    option.SetFillMode(FillMode::FORWARDS);
    duration = std::max(duration, AceApplicationInfo::GetInstance().GetBarrierfreeDuration());
    continuousTask_.Reset([weak = WeakClaim(this), toastId, duration, id = Container::CurrentId()]() {
        auto overlayManager = weak.Upgrade();
        CHECK_NULL_VOID(overlayManager);
        ContainerScope scope(id);
        overlayManager->PopToast(toastId);
    });
    option.SetOnFinishEvent([continuousTask = continuousTask_, duration, id = Container::CurrentId()] {
        ContainerScope scope(id);
        auto context = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(context);
        auto taskExecutor = context->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        taskExecutor->PostDelayedTask(
            continuousTask, TaskExecutor::TaskType::UI, duration, "ArkUIOverlayContinuousPopToast");
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
    AnimationOption option;
    auto curve = AceType::MakeRefPtr<CubicCurve>(0.2f, 0.0f, 0.1f, 1.0f);
    option.SetCurve(curve);
    option.SetDuration(TOAST_ANIMATION_DURATION);
    option.SetFillMode(FillMode::FORWARDS);
    // OnFinishEvent should be executed in UI thread.
    option.SetOnFinishEvent([weak = WeakClaim(this), toastId] {
        auto overlayManager = weak.Upgrade();
        CHECK_NULL_VOID(overlayManager);
        auto toastIter = overlayManager->toastMap_.find(toastId);
        if (toastIter == overlayManager->toastMap_.end()) {
            return;
        }
        auto toastUnderPop = toastIter->second.Upgrade();
        CHECK_NULL_VOID(toastUnderPop);
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
    });
    auto toastIter = toastMap_.find(toastId);
    if (toastIter == toastMap_.end()) {
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
#if defined(ANDROID_PLATFORM) || defined(IOS_PLATFORM)
    auto* transactionProxy = Rosen::RSTransactionProxy::GetInstance();
    if (transactionProxy != nullptr) {
        transactionProxy->FlushImplicitTransaction();
    }
#endif
    // start animation immediately
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->RequestFrame();
    AccessibilityEvent event;
    event.type = AccessibilityEventType::CHANGE;
    event.windowContentChangeTypes = WindowsContentChangeTypes::CONTENT_CHANGE_TYPE_SUBTREE;
    pipeline->SendEventToAccessibility(event);
}

void OverlayManager::ClearToastInSubwindow()
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "clear toast in subwindow enter");
    SubwindowManager::GetInstance()->ClearToastInSubwindow();
}

void OverlayManager::ClearToast()
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "clear toast enter");
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto rootNode = context->GetRootElement();
    CHECK_NULL_VOID(rootNode);
    for (auto [id, toastNodeWeak] : toastMap_) {
        PopToast(id);
    }
}

void OverlayManager::ShowPopupAnimation(const RefPtr<FrameNode>& popupNode)
{
    auto popupPattern = popupNode->GetPattern<BubblePattern>();
    CHECK_NULL_VOID(popupPattern);
    popupPattern->ResetFocusState();
    BlurLowerNode(popupNode);
    auto onFinish = [popupNodeWk = WeakPtr<FrameNode>(popupNode), weak = WeakClaim(this)]() {
        auto overlayManager = weak.Upgrade();
        auto popupNode = popupNodeWk.Upgrade();
        CHECK_NULL_VOID(overlayManager && popupNode);
        overlayManager->FocusOverlayNode(popupNode);
    };
    if (popupPattern->GetHasTransition()) {
        popupPattern->StartEnteringTransitionEffects(popupNode, onFinish);
    } else {
        popupPattern->StartEnteringAnimation(onFinish);
    }
}

void OverlayManager::ShowPopupAnimationNG(const RefPtr<FrameNode>& popupNode)
{
    auto popupPattern = popupNode->GetPattern<BubblePattern>();
    CHECK_NULL_VOID(popupPattern);
    if (popupPattern->GetHasTransition()) {
        popupPattern->StartEnteringTransitionEffects(popupNode, nullptr);
    } else {
        popupPattern->StartEnteringAnimation(nullptr);
    }
}

void OverlayManager::HidePopupAnimation(const RefPtr<FrameNode>& popupNode, const std::function<void()>& finish)
{
    auto rootNode = rootNodeWeak_.Upgrade();
    auto popupPattern = popupNode->GetPattern<BubblePattern>();
    if (popupPattern->GetHasTransition()) {
        if (!popupNode->GetRenderContext()->HasDisappearTransition()) {
            popupPattern->SetTransitionStatus(TransitionStatus::INVISIABLE);
            popupNode->GetEventHub<BubbleEventHub>()->FireChangeEvent(false);
            rootNode->RemoveChild(popupNode);
            rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
            auto layoutProp = popupNode->GetLayoutProperty<BubbleLayoutProperty>();
            CHECK_NULL_VOID(layoutProp);
            auto isShowInSubWindow = layoutProp->GetShowInSubWindow().value_or(false);
            if (isShowInSubWindow) {
                auto subwindowMgr = SubwindowManager::GetInstance();
                subwindowMgr->DeleteHotAreas(Container::CurrentId(), popupNode->GetId());
            }
        } else {
            popupPattern->StartExitingTransitionEffects(popupNode, finish);
        }
    } else {
        popupPattern->StartExitingAnimation(finish);
    }
}

void OverlayManager::ShowPopup(int32_t targetId, const PopupInfo& popupInfo,
    const std::function<void(int32_t)>&& onWillDismiss, bool interactiveDismiss)
{
    if (!UpdatePopupMap(targetId, popupInfo)) {
        TAG_LOGE(AceLogTag::ACE_OVERLAY, "failed to update popup map, tag:%{public}s",
            popupInfo.target.Upgrade()->GetTag().c_str());
        return;
    }
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_VOID(rootNode);
    auto frameNode = AceType::DynamicCast<FrameNode>(rootNode);
    if (frameNode && !frameNode->IsLayoutComplete()) {
        auto context = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(context);
        auto taskExecutor = context->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        taskExecutor->PostTask(
            [targetId, popupInfo, weak = WeakClaim(this), callback = std::move(onWillDismiss), interactiveDismiss]() {
                auto overlayManager = weak.Upgrade();
                CHECK_NULL_VOID(overlayManager);
                overlayManager->MountPopup(targetId, popupInfo, std::move(callback), interactiveDismiss);
            },
            TaskExecutor::TaskType::UI, "ArkUIOverlayShowPopup");
    } else {
        MountPopup(targetId, popupInfo, std::move(onWillDismiss), interactiveDismiss);
    }
}

bool OverlayManager::UpdatePopupMap(int32_t targetId, const PopupInfo& popupInfo)
{
    popupMap_[targetId] = popupInfo;
    if (!popupInfo.markNeedUpdate) {
        TAG_LOGW(AceLogTag::ACE_OVERLAY, "mark need update failed");
        return false;
    }
    popupMap_[targetId].markNeedUpdate = false;
    return true;
}

void OverlayManager::MountPopup(int32_t targetId, const PopupInfo& popupInfo,
    const std::function<void(int32_t)>&& onWillDismiss, bool interactiveDismiss)
{
    // TargetNode may be destroyed when MontPopup is thrown thread.
    auto targetNode = popupInfo.target.Upgrade();
    CHECK_NULL_VOID(targetNode);
    auto popupNode = popupInfo.popupNode;
    CHECK_NULL_VOID(popupNode);
    auto layoutProp = popupNode->GetLayoutProperty<BubbleLayoutProperty>();
    CHECK_NULL_VOID(layoutProp);
    auto isShowInSubWindow = layoutProp->GetShowInSubWindow().value_or(false);
    auto paintProperty = popupNode->GetPaintProperty<BubbleRenderProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto isTypeWithOption = paintProperty->GetPrimaryButtonShow().value_or(false);
    auto isUseCustom = paintProperty->GetUseCustom().value_or(false);

    auto rootNode = rootNodeWeak_.Upgrade();
    auto container = Container::Current();
    if (container && container->IsScenceBoardWindow()) {
        rootNode = FindWindowScene(popupInfo.target.Upgrade());
    }
    CHECK_NULL_VOID(rootNode);
    CHECK_NULL_VOID(popupInfo.markNeedUpdate);
    CHECK_NULL_VOID(popupInfo.popupNode);

    const auto& rootChildren = rootNode->GetChildren();
    auto iter = std::find(rootChildren.rbegin(), rootChildren.rend(), popupNode);
    if (iter == rootChildren.rend()) {
        popupNode->MountToParent(rootNode);
    }

    // attach popupNode before entering animation
    popupNode->GetEventHub<BubbleEventHub>()->FireChangeEvent(true);
    rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    popupMap_[targetId].isCurrentOnShow = true;

    auto popupPattern = popupNode->GetPattern<BubblePattern>();
    CHECK_NULL_VOID(popupPattern);
    popupPattern->SetInteractiveDismiss(interactiveDismiss);
    popupPattern->UpdateOnWillDismiss(move(onWillDismiss));
    if ((isTypeWithOption && !isShowInSubWindow) ||
        (!Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN) && isUseCustom && popupInfo.focusable)) {
        ShowPopupAnimation(popupNode);
    } else {
        ShowPopupAnimationNG(popupNode);
    }
    SetPopupHotAreas(popupNode);
}

void OverlayManager::SetPopupHotAreas(RefPtr<FrameNode> popupNode)
{
    CHECK_NULL_VOID(popupNode);
    auto popupId = popupNode->GetId();
    auto popupPattern = popupNode->GetPattern<BubblePattern>();
    CHECK_NULL_VOID(popupPattern);
    auto layoutProp = popupNode->GetLayoutProperty<BubbleLayoutProperty>();
    CHECK_NULL_VOID(layoutProp);
    auto isBlock = layoutProp->GetBlockEventValue(true);
    auto isShowInSubWindow = layoutProp->GetShowInSubWindow().value_or(false);
    if (isShowInSubWindow && popupPattern->IsOnShow()) {
        std::vector<Rect> rects;
        if (!isBlock) {
            auto rect = Rect(popupPattern->GetChildOffset().GetX(), popupPattern->GetChildOffset().GetY(),
                popupPattern->GetChildSize().Width(), popupPattern->GetChildSize().Height());
            rects.emplace_back(rect);
        } else {
            auto parentWindowRect = SubwindowManager::GetInstance()->GetParentWindowRect();
            auto rect = Rect(popupPattern->GetChildOffset().GetX(), popupPattern->GetChildOffset().GetY(),
                popupPattern->GetChildSize().Width(), popupPattern->GetChildSize().Height());
            rects.emplace_back(parentWindowRect);
            rects.emplace_back(rect);
        }
        auto subWindowMgr = SubwindowManager::GetInstance();
        subWindowMgr->SetHotAreas(rects, popupId, popupPattern->GetContainerId());
    }
}

void OverlayManager::HidePopup(int32_t targetId, const PopupInfo& popupInfo)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "hide popup enter");
    popupMap_[targetId] = popupInfo;
    if (!popupInfo.markNeedUpdate) {
        TAG_LOGW(AceLogTag::ACE_OVERLAY, "mark need update failed");
        return;
    }
    popupMap_[targetId].markNeedUpdate = false;
    auto focusable = popupInfo.focusable;
    auto popupNode = popupInfo.popupNode;
    CHECK_NULL_VOID(popupNode);
    auto layoutProp = popupNode->GetLayoutProperty<BubbleLayoutProperty>();
    CHECK_NULL_VOID(layoutProp);
    auto isShowInSubWindow = layoutProp->GetShowInSubWindow().value_or(false);
    auto paintProperty = popupNode->GetPaintProperty<BubbleRenderProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto isTypeWithOption = paintProperty->GetPrimaryButtonShow().value_or(false);
    auto isUseCustom = paintProperty->GetUseCustom().value_or(false);

    auto rootNode = rootNodeWeak_.Upgrade();
    auto container = Container::Current();
    if (container && container->IsScenceBoardWindow()) {
        rootNode = FindWindowScene(popupInfo.target.Upgrade());
    }
    CHECK_NULL_VOID(rootNode);

    const auto& rootChildren = rootNode->GetChildren();
    auto iter = std::find(rootChildren.rbegin(), rootChildren.rend(), popupNode);
    if (iter == rootChildren.rend()) {
        return;
    }

    auto popupPattern = popupNode->GetPattern<BubblePattern>();
    CHECK_NULL_VOID(popupPattern);
    if (popupPattern->GetTransitionStatus() == TransitionStatus::EXITING) {
        return;
    }
    popupPattern->SetTransitionStatus(TransitionStatus::EXITING);
    if ((isTypeWithOption && !isShowInSubWindow) ||
        (!Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN) && isUseCustom && focusable)) {
        ResetLowerNodeFocusable(popupNode);
    }
    CheckReturnFocus(popupNode);
    // detach popupNode after exiting animation
    popupMap_[targetId].isCurrentOnShow = false;
    auto onFinish = [isShowInSubWindow, isTypeWithOption, isUseCustom, focusable,
        targetId, popupNodeWk = WeakPtr<FrameNode>(popupNode),
        rootNodeWk = WeakPtr<UINode>(rootNode), weak = WeakClaim(this)]() {
        auto rootNode = rootNodeWk.Upgrade();
        auto popupNode = popupNodeWk.Upgrade();
        auto overlayManager = weak.Upgrade();
        CHECK_NULL_VOID(rootNode && popupNode && overlayManager);
        if (overlayManager->popupMap_[targetId].isCurrentOnShow) {
            return;
        }
        auto popupPattern = popupNode->GetPattern<BubblePattern>();
        CHECK_NULL_VOID(popupPattern);
        popupPattern->SetTransitionStatus(TransitionStatus::INVISIABLE);
        popupNode->GetEventHub<BubbleEventHub>()->FireChangeEvent(false);
        popupNode->GetRenderContext()->UpdateChainedTransition(nullptr);
        rootNode->RemoveChild(popupNode);
        rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        overlayManager->ErasePopupInfo(targetId);
        if ((isTypeWithOption && !isShowInSubWindow) ||
            (!Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN) && isUseCustom && focusable)) {
            overlayManager->BlurOverlayNode(popupNode);
        }
        if (isShowInSubWindow) {
            auto subwindow = SubwindowManager::GetInstance();
            subwindow->DeleteHotAreas(Container::CurrentId(), popupNode->GetId());
            subwindow->HideSubWindowNG();
        }
    };
    HidePopupAnimation(popupNode, onFinish);
    popupNode->OnAccessibilityEvent(
        AccessibilityEventType::CHANGE, WindowsContentChangeTypes::CONTENT_CHANGE_TYPE_SUBTREE);
    RemoveEventColumn();
    RemovePixelMapAnimation(false, 0, 0);
    RemoveGatherNodeWithAnimation();
    RemoveFilter();
}

RefPtr<FrameNode> OverlayManager::HidePopupWithoutAnimation(int32_t targetId, const PopupInfo& popupInfo)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "hide popup without animation enter");
    popupMap_[targetId] = popupInfo;
    CHECK_NULL_RETURN(popupInfo.markNeedUpdate, nullptr);
    if (!popupInfo.markNeedUpdate) {
        TAG_LOGW(AceLogTag::ACE_OVERLAY, "mark need update failed");
        return nullptr;
    }
    CHECK_NULL_RETURN(popupInfo.popupNode, nullptr);
    auto bubbleRenderProp = popupInfo.popupNode->GetPaintProperty<BubbleRenderProperty>();
    CHECK_NULL_RETURN(bubbleRenderProp, nullptr);
    auto autoCancel = bubbleRenderProp->GetAutoCancel().value_or(true);
    if (!autoCancel) {
        return nullptr;
    }
    popupInfo.popupNode->GetEventHub<BubbleEventHub>()->FireChangeEvent(false);
    CHECK_NULL_RETURN(popupInfo.isCurrentOnShow, nullptr);
    popupMap_[targetId].isCurrentOnShow = false;
    auto pattern = popupInfo.popupNode->GetPattern<BubblePattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    pattern->SetTransitionStatus(TransitionStatus::INVISIABLE);
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_RETURN(rootNode, nullptr);
    auto rootChildren = rootNode->GetChildren();
    auto iter = std::find(rootChildren.begin(), rootChildren.end(), popupInfo.popupNode);
    if (iter != rootChildren.end()) {
        return popupMap_[targetId].popupNode;
    }
    return nullptr;
}

void OverlayManager::ShowIndexerPopup(int32_t targetId, RefPtr<FrameNode>& customNode)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "show indexer popup enter");
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
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "remove indexer popup byid enter");
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
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "remove indexer popup enter");
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

void OverlayManager::HideCustomPopups()
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "hide custom popup enter");
    if (popupMap_.empty()) {
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
            popupNode->GetEventHub<BubbleEventHub>()->FireChangeEvent(false);
            // if use popup with option, skip
            if (isTypeWithOption) {
                continue;
            }
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

void OverlayManager::HideAllPopups()
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "hide all popup enter");
    if (popupMap_.empty()) {
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
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "erase popup enter");
    auto it = popupMap_.find(targetId);
    if (it != popupMap_.end()) {
        auto rootNode = rootNodeWeak_.Upgrade();
        CHECK_NULL_VOID(rootNode);
        auto popupNode = it->second.popupNode;
        CHECK_NULL_VOID(popupNode);
        auto layoutProp = popupNode->GetLayoutProperty<BubbleLayoutProperty>();
        CHECK_NULL_VOID(layoutProp);
        auto isShowInSubWindow = layoutProp->GetShowInSubWindow().value_or(false);
        if (isShowInSubWindow) {
            auto subwindowMgr = SubwindowManager::GetInstance();
            subwindowMgr->DeleteHotAreas(Container::CurrentId(), popupNode->GetId());
        }
        rootNode->RemoveChild(popupNode);
        rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        popupMap_.erase(targetId);
    }
}

void OverlayManager::DismissPopup()
{
    auto iter = popupMap_.find(dismissPopupId_);
    if (iter == popupMap_.end()) {
        return;
    }
    auto popupInfo = iter->second;
    popupInfo.markNeedUpdate = true;
    HidePopup(dismissPopupId_, popupInfo);
}

bool OverlayManager::ShowMenuHelper(RefPtr<FrameNode>& menu, int32_t targetId, const NG::OffsetF& offset)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "show menu helper enter");
    if (!menu) {
        // get existing menuNode
        auto it = menuMap_.find(targetId);
        if (it != menuMap_.end()) {
            menu = it->second;
        }
    } else {
        // creating new menu
        menuMap_[targetId] = menu;
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
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "show menu enter");
    if (!ShowMenuHelper(menu, targetId, offset)) {
        TAG_LOGW(AceLogTag::ACE_OVERLAY, "show menu helper failed");
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
    if (iter == rootChildren.end()) {
        menu->MountToParent(rootNode);
        rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        menu->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        ShowMenuAnimation(menu);
        menu->MarkModifyDone();
    }
    menu->OnAccessibilityEvent(AccessibilityEventType::CHANGE, WindowsContentChangeTypes::CONTENT_CHANGE_TYPE_SUBTREE);
}

// subwindow only contains one menu instance.
void OverlayManager::ShowMenuInSubWindow(int32_t targetId, const NG::OffsetF& offset, RefPtr<FrameNode> menu)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "show menu insubwindow enter");
    auto menuOffset = offset;
    auto currentSubwindow = SubwindowManager::GetInstance()->GetCurrentWindow();
    if (currentSubwindow) {
        auto subwindowRect = currentSubwindow->GetRect();
        menuOffset -= subwindowRect.GetOffset();
    }
    if (!ShowMenuHelper(menu, targetId, menuOffset)) {
        TAG_LOGW(AceLogTag::ACE_OVERLAY, "show menu helper failed");
        return;
    }
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_VOID(rootNode);
    auto subwindowMgr = SubwindowManager::GetInstance();
    for (auto child: rootNode->GetChildren()) {
        subwindowMgr->DeleteHotAreas(Container::CurrentId(), child->GetId());
    }
    rootNode->Clean();
    auto menuWrapperPattern = menu->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(menuWrapperPattern);
    if (menuWrapperPattern->IsContextMenu() && menuWrapperPattern->GetPreviewMode() != MenuPreviewMode::NONE) {
        auto filterNode = menuWrapperPattern->GetFilterColumnNode();
        if (filterNode) {
            SetHasFilter(true);
            SetFilterColumnNode(filterNode);
            filterNode->MountToParent(rootNode);
            ShowFilterAnimation(filterNode);
            filterNode->MarkModifyDone();
        }
    }
    menu->MountToParent(rootNode);
    ShowMenuAnimation(menu);
    menu->MarkModifyDone();
    rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);

    // set subwindow container id in menu.
    auto menuPattern = menu->GetPattern<PopupBasePattern>();
    CHECK_NULL_VOID(menuPattern);
    menuPattern->SetContainerId(Container::CurrentId());
}

void OverlayManager::HideMenuInSubWindow(const RefPtr<FrameNode>& menu, int32_t targetId)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "hide menu insubwindow enter");
    CHECK_NULL_VOID(menu);
    PopMenuAnimation(menu);
}

void OverlayManager::HideMenuInSubWindow(bool showPreviewAnimation, bool startDrag)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "hide menu insubwindow enter");
    if (menuMap_.empty()) {
        return;
    }
    auto rootNode = rootNodeWeak_.Upgrade();
    for (const auto& child : rootNode->GetChildren()) {
        auto node = DynamicCast<FrameNode>(child);
        if (node->GetTag() == V2::MENU_WRAPPER_ETS_TAG) {
            PopMenuAnimation(node, showPreviewAnimation, startDrag);
        }
    }
}

RefPtr<FrameNode> OverlayManager::GetMenuNode(int32_t targetId)
{
    auto it = menuMap_.find(targetId);
    if (it != menuMap_.end()) {
        return it->second;
    }
    return nullptr;
}

void OverlayManager::HideMenu(const RefPtr<FrameNode>& menu, int32_t targetId, bool isMenuOnTouch)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "hide menu enter");
    PopMenuAnimation(menu);
    menu->OnAccessibilityEvent(AccessibilityEventType::CHANGE, WindowsContentChangeTypes::CONTENT_CHANGE_TYPE_SUBTREE);
    RemoveEventColumn();
    if (isMenuOnTouch) {
        RemovePixelMap();
        RemoveGatherNode();
    } else {
        RemovePixelMapAnimation(false, 0, 0);
        RemoveGatherNodeWithAnimation();
    }
    RemoveFilterAnimation();
}

void OverlayManager::HideAllMenus()
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "hide all menus enter");
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
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "delete menu enter");
    auto it = menuMap_.find(targetId);
    if (it == menuMap_.end()) {
        return;
    }
    auto node = AceType::DynamicCast<FrameNode>(it->second);
    if (node->GetParent()) {
        auto id = Container::CurrentId();
        SubwindowManager::GetInstance()->ClearMenu();
        SubwindowManager::GetInstance()->ClearMenuNG(id, targetId);

        if (node->GetParent()) {
            RemoveEventColumn();
            RemoveMenuNotInSubWindow(WeakClaim(RawPtr(node)), rootNodeWeak_, WeakClaim(this));
        }
    }
    EraseMenuInfo(targetId);
}

void OverlayManager::CleanMenuInSubWindowWithAnimation()
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "clean menu insubwindow with animation enter");
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
    PopMenuAnimation(menu);
}

void OverlayManager::CleanPreviewInSubWindow()
{
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

void OverlayManager::CleanMenuInSubWindow(int32_t targetId)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "clean menu insubwindow enter");
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_VOID(rootNode);

    for (const auto& child : rootNode->GetChildren()) {
        auto node = DynamicCast<FrameNode>(child);
        if (node && node->GetTag() != V2::MENU_WRAPPER_ETS_TAG) {
            continue;
        }

        auto menuWrapperPattern = node->GetPattern<MenuWrapperPattern>();
        CHECK_NULL_VOID(menuWrapperPattern);
        if (menuWrapperPattern->GetTargetId() != targetId) {
            continue;
        }

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
        auto subwindowMgr = SubwindowManager::GetInstance();
        subwindowMgr->DeleteHotAreas(Container::CurrentId(), node->GetId());
        menuWrapperPattern->SetMenuStatus(MenuStatus::HIDE);
        break;
    }
}

void OverlayManager::CleanPopupInSubWindow()
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "clean popup insubwindow enter");
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_VOID(rootNode);
    std::vector<RefPtr<FrameNode>> removeNodes;
    for (const auto& child : rootNode->GetChildren()) {
        if (!child || child->GetTag() != V2::POPUP_ETS_TAG) {
            continue;
        }
        auto id = child->GetId();
        for (const auto& popup : popupMap_) {
            auto popupInfo = popup.second;
            auto target = popup.first;
            if (id != popupInfo.popupId) {
                continue;
            }
            popupInfo.markNeedUpdate = true;
            auto removeNode = HidePopupWithoutAnimation(target, popupInfo);
            if (removeNode) {
                removeNodes.emplace_back(removeNode);
                auto subwindowMgr = SubwindowManager::GetInstance();
                subwindowMgr->DeleteHotAreas(Container::CurrentId(), removeNode->GetId());
                ErasePopupInfo(target);
            }
            break;
        }
    }
    for (const auto& removeNode : removeNodes) {
        rootNode->RemoveChild(removeNode);
    }
    rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void OverlayManager::BeforeShowDialog(const RefPtr<FrameNode>& node)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "before show dialog");
    CHECK_NULL_VOID(node);
    if (dialogMap_.find(node->GetId()) != dialogMap_.end()) {
        return;
    }
    dialogMap_[node->GetId()] = node;
}

RefPtr<FrameNode> OverlayManager::SetDialogMask(const DialogProperties& dialogProps)
{
    DialogProperties Maskarg;
    Maskarg.isMask = true;
    Maskarg.autoCancel = dialogProps.autoCancel;
    Maskarg.onWillDismiss = dialogProps.onWillDismiss;
    Maskarg.maskColor = dialogProps.maskColor;
    return ShowDialog(Maskarg, nullptr, false);
}

RefPtr<FrameNode> OverlayManager::ShowDialog(
    const DialogProperties& dialogProps, std::function<void()>&& buildFunc, bool isRightToLeft)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "show dialog enter");
    RefPtr<UINode> customNode;
    // create custom builder content
    if (buildFunc) {
        NG::ScopedViewStackProcessor builderViewStackProcessor;
        buildFunc();
        customNode = NG::ViewStackProcessor::GetInstance()->Finish();
        CHECK_NULL_RETURN(customNode, nullptr);
    }

    auto dialog = DialogView::CreateDialogNode(dialogProps, customNode);
    CHECK_NULL_RETURN(dialog, nullptr);
    BeforeShowDialog(dialog);
    if (dialogProps.transitionEffect != nullptr) {
        SetDialogTransitionEffect(dialog);
    } else {
        OpenDialogAnimation(dialog);
    }
    dialogCount_++;
    // set close button disable
    SetContainerButtonEnable(false);
    if (Recorder::EventRecorder::Get().IsComponentRecordEnable()) {
        Recorder::EventParamsBuilder builder;
        builder
            .SetType("Dialog")
            .SetEventType(Recorder::EventType::DIALOG_SHOW)
            .SetExtra(Recorder::KEY_TITLE, dialogProps.title)
            .SetExtra(Recorder::KEY_SUB_TITLE, dialogProps.subtitle);
        Recorder::EventRecorder::Get().OnEvent(std::move(builder));
    }
    return dialog;
}

RefPtr<FrameNode> OverlayManager::ShowDialogWithNode(
    const DialogProperties& dialogProps, const RefPtr<UINode>& customNode, bool isRightToLeft)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "show dialog enter");
    CHECK_NULL_RETURN(customNode, nullptr);
    auto dialog = DialogView::CreateDialogNode(dialogProps, customNode);
    CHECK_NULL_RETURN(dialog, nullptr);
    BeforeShowDialog(dialog);
    if (dialogProps.transitionEffect != nullptr) {
        SetDialogTransitionEffect(dialog);
    } else {
        OpenDialogAnimation(dialog);
    }
    dialogCount_++;
    // set close button disable
    SetContainerButtonEnable(false);
    if (Recorder::EventRecorder::Get().IsComponentRecordEnable()) {
        Recorder::EventParamsBuilder builder;
        builder
            .SetType("Dialog")
            .SetEventType(Recorder::EventType::DIALOG_SHOW)
            .SetExtra(Recorder::KEY_TITLE, dialogProps.title)
            .SetExtra(Recorder::KEY_SUB_TITLE, dialogProps.subtitle);
        Recorder::EventRecorder::Get().OnEvent(std::move(builder));
    }
    return dialog;
}

RefPtr<FrameNode> OverlayManager::GetDialogNodeWithExistContent(const RefPtr<UINode>& node)
{
    auto iter = dialogMap_.begin();
    while (iter != dialogMap_.end()) {
        auto dialogNode = (*iter).second;
        CHECK_NULL_RETURN(dialogNode, nullptr);
        auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
        CHECK_NULL_RETURN(dialogPattern, nullptr);
        if (dialogPattern->GetCustomNode() == node) {
            return dialogNode;
        }
        iter++;
    }
    return nullptr;
}

void OverlayManager::RegisterDialogLifeCycleCallback(
    const RefPtr<FrameNode>& dialog, const DialogProperties& dialogProps)
{
    auto dialogPattern = dialog->GetPattern<DialogPattern>();
    CHECK_NULL_VOID(dialogPattern);
    auto onDidAppearEvent = dialogProps.onDidAppear;
    dialogPattern->RegisterDialogDidAppearCallback(std::move(onDidAppearEvent));
    auto onDidDisappearEvent = dialogProps.onDidDisappear;
    dialogPattern->RegisterDialogDidDisappearCallback(std::move(onDidDisappearEvent));
    auto onWillAppearEvent = dialogProps.onWillAppear;
    dialogPattern->RegisterDialogWillAppearCallback(std::move(onWillAppearEvent));
    auto onWillDisappearEvent = dialogProps.onWillDisappear;
    dialogPattern->RegisterDialogWillDisappearCallback(std::move(onWillDisappearEvent));
}

void OverlayManager::CustomDialogRecordEvent(const DialogProperties& dialogProps)
{
    if (Recorder::EventRecorder::Get().IsComponentRecordEnable()) {
        Recorder::EventParamsBuilder builder;
        builder
            .SetType("Dialog")
            .SetEventType(Recorder::EventType::DIALOG_SHOW)
            .SetExtra(Recorder::KEY_TITLE, dialogProps.title)
            .SetExtra(Recorder::KEY_SUB_TITLE, dialogProps.subtitle);
        Recorder::EventRecorder::Get().OnEvent(std::move(builder));
    }
}

void OverlayManager::OpenCustomDialog(const DialogProperties& dialogProps, std::function<void(int32_t)> &&callback)
{
    RefPtr<UINode> customNode;
    bool showComponentContent = false;
    if (!callback) {
        TAG_LOGE(AceLogTag::ACE_OVERLAY, "Parameters of OpenCustomDialog are incomplete because of no callback.");
        return;
    }
    if (dialogProps.customBuilder) {
        TAG_LOGD(AceLogTag::ACE_OVERLAY, "open custom dialog with custom builder.");
        NG::ScopedViewStackProcessor builderViewStackProcessor;
        dialogProps.customBuilder();
        customNode = NG::ViewStackProcessor::GetInstance()->Finish();
        if (!customNode) {
            callback(-1);
            return;
        }
    } else {
        auto contentNode = dialogProps.contentNode.Upgrade();
        if (!contentNode) {
            callback(ERROR_CODE_DIALOG_CONTENT_ERROR);
            return;
        }
        if (GetDialogNodeWithExistContent(contentNode)) {
            callback(ERROR_CODE_DIALOG_CONTENT_ALREADY_EXIST);
            return;
        }
        TAG_LOGD(AceLogTag::ACE_OVERLAY, "OpenCustomDialog ComponentContent id: %{public}d", contentNode->GetId());
        customNode = contentNode;
        showComponentContent = true;
    }
    auto dialog = DialogView::CreateDialogNode(dialogProps, customNode);
    if (!dialog) {
        callback(showComponentContent ? ERROR_CODE_DIALOG_CONTENT_ERROR : -1);
        return;
    }
    RegisterDialogLifeCycleCallback(dialog, dialogProps);
    BeforeShowDialog(dialog);

    callback(showComponentContent ? ERROR_CODE_NO_ERROR : dialog->GetId());

    if (dialogProps.transitionEffect != nullptr) {
        SetDialogTransitionEffect(dialog);
    } else {
        OpenDialogAnimation(dialog);
    }

    dialogCount_++;
    CustomDialogRecordEvent(dialogProps);
    return;
}

void OverlayManager::CloseCustomDialog(const int32_t dialogId)
{
    auto iter = dialogMap_.end();
    if (dialogId == -1) {
        int32_t tmpNodeId = -1;
        RefPtr<FrameNode> tmpNode;
        iter = dialogMap_.begin();
        while (iter != dialogMap_.end()) {
            auto dialogNode = (*iter).second;
            if (dialogNode && dialogNode->GetId() > tmpNodeId) {
                tmpNodeId = dialogNode->GetId();
                tmpNode = dialogNode;
            }
            iter++;
        }
        if (tmpNode) {
            DeleteDialogHotAreas(tmpNode);
            CloseDialogInner(tmpNode);
        } else {
            LOGE("not find dialog when no dialog id");
        }
    } else {
        iter = dialogMap_.find(dialogId);
        if (iter == dialogMap_.end()) {
            LOGE("not find dialog by id %{public}d", dialogId);
            return;
        }
        RefPtr<FrameNode> tmpDialog = (*iter).second;
        DeleteDialogHotAreas(tmpDialog);
        CloseDialogInner(tmpDialog);
    }
    return;
}

void OverlayManager::CloseCustomDialog(const WeakPtr<NG::UINode>& node, std::function<void(int32_t)> &&callback)
{
    if (!callback) {
        TAG_LOGE(AceLogTag::ACE_OVERLAY, "Parameters of CloseCustomDialog are incomplete because of no callback.");
        return;
    }
    auto contentNode = node.Upgrade();
    if (!contentNode) {
        callback(ERROR_CODE_DIALOG_CONTENT_ERROR);
        return;
    }
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "CloseCustomDialog ComponentContent id: %{public}d", contentNode->GetId());
    auto dialogNode = GetDialogNodeWithExistContent(contentNode);
    if (dialogNode) {
        DeleteDialogHotAreas(dialogNode);
        CloseDialogInner(dialogNode);
        callback(ERROR_CODE_NO_ERROR);
        return;
    }

    callback(ERROR_CODE_DIALOG_CONTENT_NOT_FOUND);
}

void OverlayManager::UpdateCustomDialog(
    const WeakPtr<NG::UINode>& node, const DialogProperties& dialogProps, std::function<void(int32_t)> &&callback)
{
    if (!callback) {
        TAG_LOGE(AceLogTag::ACE_OVERLAY, "Parameters of UpdateCustomDialog are incomplete because of no callback.");
        return;
    }
    auto contentNode = node.Upgrade();
    if (!contentNode) {
        callback(ERROR_CODE_DIALOG_CONTENT_ERROR);
        return;
    }
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "UpdateCustomDialog ComponentContent id: %{public}d", contentNode->GetId());
    auto dialogNode = GetDialogNodeWithExistContent(contentNode);
    if (dialogNode) {
        auto dialogLayoutProp = AceType::DynamicCast<DialogLayoutProperty>(dialogNode->GetLayoutProperty());
        CHECK_NULL_VOID(dialogLayoutProp);
        dialogLayoutProp->UpdateDialogAlignment(dialogProps.alignment);
        dialogLayoutProp->UpdateDialogOffset(dialogProps.offset);
        dialogLayoutProp->UpdateAutoCancel(dialogProps.autoCancel);
        auto dialogContext = dialogNode->GetRenderContext();
        CHECK_NULL_VOID(dialogContext);
        auto pipelineContext = dialogNode->GetContext();
        CHECK_NULL_VOID(pipelineContext);
        auto dialogTheme = pipelineContext->GetTheme<DialogTheme>();
        CHECK_NULL_VOID(dialogTheme);
        dialogContext->UpdateBackgroundColor(dialogProps.maskColor.value_or(dialogTheme->GetMaskColorEnd()));
        dialogNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);

        callback(ERROR_CODE_NO_ERROR);
        return;
    }

    callback(ERROR_CODE_DIALOG_CONTENT_NOT_FOUND);
}

void OverlayManager::ShowCustomDialog(const RefPtr<FrameNode>& customNode)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "show custom dialog enter");
    BeforeShowDialog(customNode);
    OpenDialogAnimation(customNode);
}

void RegisterDialogCallback(
    const RefPtr<FrameNode>& node, std::map<std::string, NG::DialogCancelEvent> dialogLifeCycleEvent)
{
    CHECK_NULL_VOID(node);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<DialogTheme>();
    CHECK_NULL_VOID(theme);
    auto dialogPattern = node->GetPattern<DialogPattern>();
    if (!dialogLifeCycleEvent.empty()) {
        auto didAppearEvent = dialogLifeCycleEvent["didAppearId"];
        auto didDisappearEvent = dialogLifeCycleEvent["didDisappearId"];
        auto willAppearEvent = dialogLifeCycleEvent["willAppearId"];
        auto willDisappearEvent = dialogLifeCycleEvent["willDisappearId"];
        dialogPattern->RegisterDialogDidAppearCallback(std::move(didAppearEvent));
        dialogPattern->RegisterDialogDidDisappearCallback(std::move(didDisappearEvent));
        dialogPattern->RegisterDialogWillAppearCallback(std::move(willAppearEvent));
        dialogPattern->RegisterDialogWillDisappearCallback(std::move(willDisappearEvent));
    }
}

void OverlayManager::ShowDateDialog(const DialogProperties& dialogProps, const DatePickerSettingData& settingData,
    std::map<std::string, NG::DialogEvent> dialogEvent, std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent,
    std::map<std::string, NG::DialogCancelEvent> dialogLifeCycleEvent, const std::vector<ButtonInfo>& buttonInfos)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "show date dialog enter");
    auto dialogNode = DatePickerDialogView::Show(
        dialogProps, std::move(settingData), buttonInfos, std::move(dialogEvent), std::move(dialogCancelEvent));
    RegisterDialogCallback(dialogNode, std::move(dialogLifeCycleEvent));
    BeforeShowDialog(dialogNode);
    OpenDialogAnimation(dialogNode);
}

void OverlayManager::ShowTimeDialog(const DialogProperties& dialogProps, const TimePickerSettingData& settingData,
    std::map<std::string, PickerTime> timePickerProperty, std::map<std::string, NG::DialogEvent> dialogEvent,
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent,
    std::map<std::string, NG::DialogCancelEvent> dialogLifeCycleEvent, const std::vector<ButtonInfo>& buttonInfos)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "show time dialog enter");
    auto dialogNode = TimePickerDialogView::Show(dialogProps, settingData, buttonInfos, std::move(timePickerProperty),
        std::move(dialogEvent), std::move(dialogCancelEvent));
    RegisterDialogCallback(dialogNode, std::move(dialogLifeCycleEvent));
    BeforeShowDialog(dialogNode);
    OpenDialogAnimation(dialogNode);
}

void OverlayManager::ShowTextDialog(const DialogProperties& dialogProps, const TextPickerSettingData& settingData,
    std::map<std::string, NG::DialogTextEvent> dialogEvent,
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent,
    std::map<std::string, NG::DialogCancelEvent> dialogLifeCycleEvent, const std::vector<ButtonInfo>& buttonInfos)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "show text dialog enter");
    auto dialogNode = TextPickerDialogView::Show(
        dialogProps, settingData, buttonInfos, std::move(dialogEvent), std::move(dialogCancelEvent));
    RegisterDialogCallback(dialogNode, std::move(dialogLifeCycleEvent));
    BeforeShowDialog(dialogNode);
    OpenDialogAnimation(dialogNode);
    if (Recorder::EventRecorder::Get().IsComponentRecordEnable()) {
        Recorder::EventParamsBuilder builder;
        builder.SetType("TextPickerDialog").SetEventType(Recorder::EventType::DIALOG_SHOW);
        Recorder::EventRecorder::Get().OnEvent(std::move(builder));
    }
}

void OverlayManager::ShowCalendarDialog(const DialogProperties& dialogProps, const CalendarSettingData& settingData,
    std::map<std::string, NG::DialogEvent> dialogEvent, std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent,
    std::map<std::string, NG::DialogCancelEvent> dialogLifeCycleEvent, const std::vector<ButtonInfo>& buttonInfos)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "show calendar dialog enter");
    auto dialogNode = CalendarDialogView::Show(
        dialogProps, settingData, buttonInfos, std::move(dialogEvent), std::move(dialogCancelEvent));
    RegisterDialogCallback(dialogNode, std::move(dialogLifeCycleEvent));
    BeforeShowDialog(dialogNode);
    OpenDialogAnimation(dialogNode);
}

void OverlayManager::PopModalDialog(int32_t maskId)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "pop modal dialog enter");
    int32_t dialogId = -1;
    for (auto it = maskNodeIdMap_.begin(); it != maskNodeIdMap_.end(); it++) {
        if (maskId == it->second) {
            dialogId = it->first;
            break;
        }
    }
    auto subWindow = SubwindowManager::GetInstance()->GetSubwindow(subWindowId_);
    CHECK_NULL_VOID(subWindow);
    auto subOverlayManager = subWindow->GetOverlayManager();
    CHECK_NULL_VOID(subOverlayManager);
    std::map<int32_t, RefPtr<FrameNode>> DialogMap(
        subOverlayManager->GetDialogMap().begin(), subOverlayManager->GetDialogMap().end());
    for (auto it = DialogMap.begin(); it != DialogMap.end(); it++) {
        auto dialogProp = DynamicCast<DialogLayoutProperty>(it->second->GetLayoutProperty());
        if (dialogId == it->first) {
            auto hub = it->second->GetEventHub<DialogEventHub>();
            if (hub) {
                hub->FireCancelEvent();
            }
            subOverlayManager->CloseDialog(it->second);
        }
    }
}

void OverlayManager::RemoveDialogFromMap(const RefPtr<FrameNode>& node)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "remove dialog from map enter");
    CHECK_NULL_VOID(node);
    if (dialogMap_.find(node->GetId()) == dialogMap_.end()) {
        return;
    }
    dialogMap_.erase(node->GetId());
}

bool OverlayManager::DialogInMapHoldingFocus()
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "dialog in map holding focus enter");
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

RefPtr<FrameNode> OverlayManager::GetDialog(int32_t dialogId)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "get dialog enter");
    for (auto it = dialogMap_.begin(); it != dialogMap_.end(); it++) {
        if (dialogId == it->second->GetId()) {
            return it->second;
        }
    }
    return nullptr;
}

void OverlayManager::CloseDialog(const RefPtr<FrameNode>& dialogNode)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "close dialog enter");
    DeleteDialogHotAreas(dialogNode);
    auto dialogLayoutProp = AceType::DynamicCast<DialogLayoutProperty>(dialogNode->GetLayoutProperty());
    CHECK_NULL_VOID(dialogLayoutProp);
    if (dialogLayoutProp && dialogLayoutProp->GetShowInSubWindowValue(false) &&
        dialogLayoutProp->GetIsModal().value_or(true)) {
        RefPtr<OverlayManager> parentOverlayManager = nullptr;
#if defined(ANDROID_PLATFORM) || defined(IOS_PLATFORM)
        auto container = Container::Current();
        auto currentId = Container::CurrentId();
        CHECK_NULL_VOID(container);
        if (container->IsSubContainer()) {
            currentId = SubwindowManager::GetInstance()->GetParentContainerId(Container::CurrentId());
            container = AceEngine::Get().GetContainer(currentId);
            CHECK_NULL_VOID(container);
        }
        ContainerScope scope(currentId);
        auto pipelineContext = container->GetPipelineContext();
        CHECK_NULL_VOID(pipelineContext);
        auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
        CHECK_NULL_VOID(context);
        parentOverlayManager = context->GetOverlayManager();
#else
        auto parentPipelineContext = PipelineContext::GetMainPipelineContext();
        CHECK_NULL_VOID(parentPipelineContext);
        parentOverlayManager = parentPipelineContext->GetOverlayManager();
#endif
        CHECK_NULL_VOID(parentOverlayManager);
        RefPtr<FrameNode> maskNode =
            parentOverlayManager->GetDialog(parentOverlayManager->GetMaskNodeIdWithDialogId(dialogNode->GetId()));
        if (maskNode) {
            parentOverlayManager->CloseDialog(maskNode);
        }
    }
    CloseDialogInner(dialogNode);
}

void OverlayManager::DeleteDialogHotAreas(const RefPtr<FrameNode>& dialogNode)
{
    auto dialogLayoutProp = AceType::DynamicCast<DialogLayoutProperty>(dialogNode->GetLayoutProperty());
    CHECK_NULL_VOID(dialogLayoutProp);
    if (dialogLayoutProp->GetShowInSubWindowValue(false)) {
        SubwindowManager::GetInstance()->DeleteHotAreas(
            SubwindowManager::GetInstance()->GetDialogSubWindowId(), dialogNode->GetId());
        SubwindowManager::GetInstance()->HideDialogSubWindow(
            SubwindowManager::GetInstance()->GetDialogSubWindowId());
    }
}

void OverlayManager::CloseDialogInner(const RefPtr<FrameNode>& dialogNode)
{
    RemoveDialogFromMap(dialogNode);
    if (dialogNode->IsRemoving()) {
        // already in close animation
        return;
    }
    dialogNode->MarkRemoving();

    auto container = Container::Current();
    auto currentId = Container::CurrentId();
    CHECK_NULL_VOID(container);
    if (container->IsSubContainer()) {
        currentId = SubwindowManager::GetInstance()->GetParentContainerId(Container::CurrentId());
        container = AceEngine::Get().GetContainer(currentId);
        CHECK_NULL_VOID(container);
    }
    ContainerScope scope(currentId);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    CHECK_NULL_VOID(context);
    auto overlayManager = context->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    overlayManager->ResetLowerNodeFocusable(dialogNode);
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    CHECK_NULL_VOID(dialogPattern);
    auto transitionEffect = dialogPattern->GetDialogProperties().transitionEffect;
    if (transitionEffect != nullptr) {
        CloseDialogMatchTransition(dialogNode);
    } else {
        CloseDialogAnimation(dialogNode);
    }
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
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "remove dialog enter");
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

bool OverlayManager::PopupInteractiveDismiss(const RefPtr<FrameNode>& overlay)
{
    auto bubblePattern = overlay->GetPattern<BubblePattern>();
    CHECK_NULL_RETURN(bubblePattern, false);
    return !bubblePattern->GetInteractiveDismiss();
}

bool OverlayManager::PopupCallBackOnWillDismiss(const RefPtr<FrameNode>& overlay)
{
    auto bubblePattern = overlay->GetPattern<BubblePattern>();
    CHECK_NULL_RETURN(bubblePattern, false);
    if (bubblePattern->HasOnWillDismiss()) {
        int32_t dismissPopupId = GetPopupIdByNode(overlay);
        SetDismissPopupId(dismissPopupId);
        bubblePattern->CallOnWillDismiss(static_cast<int32_t>(DismissReason::BACK_PRESSED));
        return true;
    }
    return false;
}

bool OverlayManager::RemoveBubble(const RefPtr<FrameNode>& overlay)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "remove bubble enter");
    if (PopupInteractiveDismiss(overlay)) {
        return true;
    }
    if (PopupCallBackOnWillDismiss(overlay)) {
        return true;
    }
    for (const auto& popup : popupMap_) {
        auto targetId = popup.first;
        auto popupInfo = popup.second;
        if (overlay == popupInfo.popupNode) {
            popupInfo.markNeedUpdate = true;
            HidePopup(targetId, popupInfo);
            return true;
        }
    }
    return false;
}

bool OverlayManager::RemoveMenu(const RefPtr<FrameNode>& overlay)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "remove menu enter");
    auto menuWrapperPattern = overlay->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_RETURN(menuWrapperPattern, false);
    menuWrapperPattern->HideMenu();
    return true;
}

int32_t OverlayManager::GetPopupIdByNode(const RefPtr<FrameNode>& overlay)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "GetPopupIdByNode IN");
    int32_t targetId = -1;
    for (const auto& popup : popupMap_) {
        targetId = popup.first;
        auto popupInfo = popup.second;
        if (overlay == popupInfo.popupNode) {
            return targetId;
        }
    }
    return targetId;
}

bool OverlayManager::RemoveOverlay(bool isBackPressed, bool isPageRouter)
{
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_RETURN(rootNode, true);
    RemoveIndexerPopup();
    if (rootNode->GetChildren().size() > ROOT_MIN_NODE) {
        // stage node is at index 0, remove overlay at last
        auto overlay = DynamicCast<FrameNode>(rootNode->GetLastChild());
        CHECK_NULL_RETURN(overlay, false);
        // page crash when function return false
        if (ExceptComponent(rootNode, overlay, isBackPressed, isPageRouter)) {
            return true;
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
        auto pattern = overlay->GetPattern();
        if (!InstanceOf<KeyboardPattern>(pattern)) {
            if (overlay->GetTag() != V2::SHEET_WRAPPER_TAG) {
                rootNode->RemoveChild(overlay);
            }
            rootNode->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
            return true;
        }
    }
    return false;
}

bool OverlayManager::ExceptComponent(const RefPtr<NG::UINode>& rootNode, RefPtr<NG::FrameNode>& overlay,
    bool isBackPressed, bool isPageRouter)
{
    // close dialog with animation
    auto pattern = overlay->GetPattern();
    if (InstanceOf<ToastPattern>(pattern)) {
        // still have nodes on root expect stage and toast node.
        if (rootNode->GetChildren().size() > TOAST_MIN_NODE) {
            // If the current node is a toast, the last second overlay's node should be processed.
            overlay = DynamicCast<FrameNode>(rootNode->GetChildAtIndex(rootNode->GetChildren().size()
                                                                                            - TOAST_MIN_NODE));
            CHECK_NULL_RETURN(overlay, false);
            pattern = overlay->GetPattern();
        } else {
            return false;
        }
    }

    CHECK_EQUAL_RETURN(overlay->GetTag(),  V2::OVERLAY_ETS_TAG, false);

    if (InstanceOf<DialogPattern>(pattern)) {
        if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE) && isPageRouter) {
            return false;
        }
        auto dialogPattern = DynamicCast<DialogPattern>(pattern);
        CHECK_NULL_RETURN(dialogPattern, false);
        if (dialogPattern->ShouldDismiss()) {
            SetDismissDialogId(overlay->GetId());
            dialogPattern->CallOnWillDismiss(static_cast<int32_t>(DialogDismissReason::DIALOG_PRESS_BACK));
            TAG_LOGI(AceLogTag::ACE_OVERLAY, "Dialog Should Dismiss");
            return true;
        }
        return RemoveDialog(overlay, isBackPressed, isPageRouter);
    }
    if (InstanceOf<BubblePattern>(pattern)) {
        return RemoveBubble(overlay);
    }
    if (InstanceOf<MenuWrapperPattern>(pattern)) {
        return RemoveMenu(overlay);
    }
    if (InstanceOf<VideoFullScreenPattern>(pattern)) {
        auto videoPattern = DynamicCast<VideoFullScreenPattern>(pattern);
        CHECK_NULL_RETURN(videoPattern, false);
        return videoPattern->ExitFullScreen();
    }

    if (overlay->GetTag() == V2::SHEET_WRAPPER_TAG) {
        return WebBackward(overlay);
    }
    return false;
}

bool OverlayManager::WebBackward(RefPtr<NG::FrameNode>& overlay)
{
#ifdef WEB_SUPPORTED
    RefPtr<NG::FrameNode> webNode;
    FindWebNode(overlay, webNode);
    if (webNode && InstanceOf<WebPattern>(webNode->GetPattern())) {
        auto webPattern = DynamicCast<WebPattern>(webNode->GetPattern());
        CHECK_NULL_RETURN(webPattern, false);
        webPattern->Backward();
        return true;
    }
#endif
    return false;
}

void OverlayManager::FindWebNode(const RefPtr<NG::UINode>& node, RefPtr<NG::FrameNode>& webNode)
{
    CHECK_NULL_VOID(node);

    if (webNode) {
        return;
    }

    auto frameNode = AceType::DynamicCast<NG::FrameNode>(node);
    if (frameNode && !frameNode->IsInternal() && frameNode->GetTag() == V2::WEB_ETS_TAG) {
        webNode = frameNode;
        return;
    }

    if (!node->GetChildren().empty()) {
        for (const auto& child : node->GetChildren()) {
            FindWebNode(child, webNode);
        }
    }
}

bool OverlayManager::RemoveModalInOverlay()
{
    auto topModalNode = modalStack_.top().Upgrade();
    CHECK_NULL_RETURN(topModalNode, false);
    auto rootNode = FindWindowScene(topModalNode);
    CHECK_NULL_RETURN(rootNode, true);
    auto overlay = DynamicCast<FrameNode>(rootNode->GetLastChild());
    if (overlay && overlay->GetTag() == V2::SHEET_WRAPPER_TAG && overlay->GetFirstChild() != topModalNode) {
        TAG_LOGD(AceLogTag::ACE_SHEET, "Refuse to back because sheet is in animation");
        return true;
    }
    if (topModalNode->GetTag() == V2::SHEET_PAGE_TAG) {
        auto sheetPattern = topModalNode->GetPattern<SheetPresentationPattern>();
        CHECK_NULL_RETURN(sheetPattern, false);
        if (sheetPattern->HasShouldDismiss() || sheetPattern->HasOnWillDismiss()) {
            sheetPattern->SheetInteractiveDismiss(BindSheetDismissReason::BACK_PRESSED);
            return true;
        }
    } else if (topModalNode->GetTag() == V2::MODAL_PAGE_TAG) {
        auto modalPattern = topModalNode->GetPattern<ModalPresentationPattern>();
        CHECK_NULL_RETURN(modalPattern, false);
        if (modalPattern->HasOnWillDismiss()) {
            modalPattern->ModalInteractiveDismiss();
            return true;
        }
    }
    ModalPageLostFocus(topModalNode);
    auto pattern = topModalNode->GetPattern<PopupBasePattern>();
    if (isProhibitBack_ && pattern->GetTargetId() < 0) {
        return true;
    }
    auto builder = AceType::DynamicCast<FrameNode>(topModalNode->GetFirstChild());
    CHECK_NULL_RETURN(builder, false);
    if (!ModalExitProcess(topModalNode)) {
        return false;
    }
    PopTopModalNode();
    auto sheetPattern = topModalNode->GetPattern<SheetPresentationPattern>();
    if (topModalNode->GetTag() == V2::SHEET_PAGE_TAG && sheetPattern) {
        sheetMap_.erase(sheetPattern->GetTargetId());
    }
    if (topModalNode->GetTag() == V2::MODAL_PAGE_TAG) {
        auto modalPattern = AceType::DynamicCast<ModalPresentationPattern>(pattern);
        CHECK_NULL_RETURN(modalPattern, false);
        auto modalTransition = modalPattern->GetType();
        if (modalTransition == ModalTransition::NONE || builder->GetRenderContext()->HasDisappearTransition()) {
            // Fire shown event of navdestination under the disappeared modal
            FireNavigationStateChange(true);
        }
    }
    FireModalPageHide();
    SaveLastModalNode();
    return true;
}

bool OverlayManager::RemoveAllModalInOverlay()
{
    while (!modalStack_.empty()) {
        auto topModalNode = modalStack_.top().Upgrade();
        if (!topModalNode) {
            modalStack_.pop();
            continue;
        }
        auto rootNode = FindWindowScene(topModalNode);
        CHECK_NULL_RETURN(rootNode, true);
        auto builder = AceType::DynamicCast<FrameNode>(topModalNode->GetFirstChild());
        CHECK_NULL_RETURN(builder, false);
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

        if (topModalNode->GetTag() == V2::MODAL_PAGE_TAG) {
            auto modalPattern = topModalNode->GetPattern<ModalPresentationPattern>();
            CHECK_NULL_RETURN(modalPattern, false);
            auto modalTransition = modalPattern->GetType();
            if (modalTransition == ModalTransition::NONE || builder->GetRenderContext()->HasDisappearTransition()) {
                // Fire shown event of navdestination under the disappeared modal
                FireNavigationStateChange(true);
            }
        }
        auto sheetPattern = topModalNode->GetPattern<SheetPresentationPattern>();
        if (topModalNode->GetTag() == V2::SHEET_PAGE_TAG && sheetPattern) {
            sheetMap_.erase(sheetPattern->GetTargetId());
        }
        FireModalPageHide();
        SaveLastModalNode();
    }
    return true;
}

bool OverlayManager::ModalExitProcess(const RefPtr<FrameNode>& topModalNode)
{
    auto rootNode = FindWindowScene(topModalNode);
    CHECK_NULL_RETURN(rootNode, true);
    if (topModalNode->GetTag() == V2::MODAL_PAGE_TAG) {
        return ModalPageExitProcess(topModalNode);
    }
    if (topModalNode->GetTag() == V2::SHEET_PAGE_TAG) {
        return SheetPageExitProcess(topModalNode);
    }
    return true;
}

void OverlayManager::PlayTransitionEffectOut(const RefPtr<FrameNode>& topModalNode)
{
    const auto& layoutProperty = topModalNode->GetLayoutProperty();
    layoutProperty->UpdateVisibility(VisibleType::INVISIBLE, true);

    const auto& renderContext = topModalNode->GetRenderContext();
    if (!renderContext->HasDisappearTransition()) {
        const auto& topModalPattern = topModalNode->GetPattern<ModalPresentationPattern>();
        if (!topModalPattern->IsExecuteOnDisappear()) {
            topModalPattern->OnDisappear();
            // Fire hidden event of navdestination on the disappeared modal
            FireNavigationStateChange(false, topModalNode);
        }
        auto rootNode = FindWindowScene(topModalNode);
        rootNode->RemoveChild(topModalNode);
        rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        // Fire shown event of navdestination under the disappeared modal
        FireNavigationStateChange(true);
    } else {
        topModalNode->GetRenderContext()->SetTransitionOutCallback(
            [modalWK = WeakClaim(RawPtr(topModalNode)), overlayWeak = WeakClaim(this)] {
                auto modal = modalWK.Upgrade();
                auto overlayManager = overlayWeak.Upgrade();
                CHECK_NULL_VOID(modal && overlayManager);
                auto root = overlayManager->FindWindowScene(modal);
                CHECK_NULL_VOID(root);
                const auto& modalPattern = modal->GetPattern<ModalPresentationPattern>();
                if (!modalPattern->IsExecuteOnDisappear()) {
                    modalPattern->OnDisappear();
                    // Fire hidden event of navdestination on the disappeared modal
                    overlayManager->FireNavigationStateChange(false, modal);
                }
                root->RemoveChild(modal);
                root->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
                // Fire shown event of navdestination under the disappeared modal
                overlayManager->FireNavigationStateChange(true);
            });
    }
}

bool OverlayManager::ModalPageExitProcess(const RefPtr<FrameNode>& topModalNode)
{
    auto rootNode = FindWindowScene(topModalNode);
    CHECK_NULL_RETURN(rootNode, true);
    auto builder = AceType::DynamicCast<FrameNode>(topModalNode->GetFirstChild());
    CHECK_NULL_RETURN(builder, false);
    topModalNode->GetPattern<ModalPresentationPattern>()->OnWillDisappear();
    auto modalTransition = topModalNode->GetPattern<ModalPresentationPattern>()->GetType();
    if (builder->GetRenderContext()->HasDisappearTransition()) {
        if (!topModalNode->GetPattern<ModalPresentationPattern>()->IsExecuteOnDisappear()) {
            topModalNode->GetPattern<ModalPresentationPattern>()->OnDisappear();
            // Fire hidden event of navdestination on the disappeared modal
            FireNavigationStateChange(false, topModalNode);
        }
        topModalNode->Clean(false, true);
        topModalNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }
    if (topModalNode->GetPattern<ModalPresentationPattern>()->HasTransitionEffect()) {
        PlayTransitionEffectOut(topModalNode);
    } else if (modalTransition == ModalTransition::DEFAULT) {
        PlayDefaultModalTransition(topModalNode, false);
    } else if (modalTransition == ModalTransition::ALPHA) {
        PlayAlphaModalTransition(topModalNode, false);
    } else if (!builder->GetRenderContext()->HasDisappearTransition()) {
        topModalNode->GetPattern<ModalPresentationPattern>()->OnDisappear();
        // Fire hidden event of navdestination on the disappeared modal
        FireNavigationStateChange(false, topModalNode);
        rootNode->RemoveChild(topModalNode);
        rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }
    topModalNode->GetPattern<ModalPresentationPattern>()->FireCallback("false");
    return true;
}

bool OverlayManager::SheetPageExitProcess(const RefPtr<FrameNode>& topModalNode)
{
    auto builder = AceType::DynamicCast<FrameNode>(topModalNode->GetLastChild());
    CHECK_NULL_RETURN(builder, false);
    topModalNode->GetPattern<SheetPresentationPattern>()->OnWillDisappear();
    if (builder->GetRenderContext()->HasDisappearTransition()) {
        if (!topModalNode->GetPattern<SheetPresentationPattern>()->IsExecuteOnDisappear()) {
            topModalNode->GetPattern<SheetPresentationPattern>()->OnDisappear();
        }
        topModalNode->Clean(false, true);
        topModalNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }
    auto maskNode = GetSheetMask(topModalNode);
    if (maskNode) {
        PlaySheetMaskTransition(
            maskNode, false, topModalNode->GetPattern<SheetPresentationPattern>()->HasCallback());
    }
    auto sheetType = topModalNode->GetPattern<SheetPresentationPattern>()->GetSheetType();
    if (sheetType == SheetType::SHEET_POPUP) {
        PlayBubbleStyleSheetTransition(topModalNode, false);
    } else {
        PlaySheetTransition(topModalNode, false);
    }
    topModalNode->GetPattern<SheetPresentationPattern>()->FireCallback("false");
    return true;
}

bool OverlayManager::RemovePopupInSubwindow(const RefPtr<Pattern>& pattern, const RefPtr<FrameNode>& overlay,
    const RefPtr<UINode>& rootNode)
{
    if (PopupInteractiveDismiss(overlay)) {
        return true;
    }
    if (PopupCallBackOnWillDismiss(overlay)) {
        return true;
    }
    auto popupPattern = DynamicCast<BubblePattern>(pattern);
    overlay->GetEventHub<BubbleEventHub>()->FireChangeEvent(false);
    auto container = Container::Current();
    auto currentId = Container::CurrentId();
    CHECK_NULL_RETURN(container, false);
    if (container->IsSubContainer()) {
        currentId = SubwindowManager::GetInstance()->GetParentContainerId(Container::CurrentId());
    }
    ContainerScope scope(currentId);
    for (const auto& popup : popupMap_) {
        auto targetId = popup.first;
        auto popupInfo = popup.second;
        if (overlay == popupInfo.popupNode) {
            popupMap_.erase(targetId);
            rootNode->RemoveChild(overlay);
            rootNode->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
            auto subwindow = SubwindowManager::GetInstance()->GetSubwindow(currentId);
            CHECK_NULL_RETURN(subwindow, false);
            subwindow->DeleteHotAreas(overlay->GetId());
            if (rootNode->GetChildren().empty()) {
                subwindow->HideSubWindowNG();
            }
            return true;
        }
    }
    return false;
}

bool OverlayManager::RemoveOverlayInSubwindow()
{
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_RETURN(rootNode, false);
    if (rootNode->GetChildren().empty()) {
        return false;
    }

    // remove the overlay node just mounted in subwindow
    auto overlay = DynamicCast<FrameNode>(rootNode->GetLastChild());
    CHECK_NULL_RETURN(overlay, false);
    // close dialog with animation
    auto pattern = overlay->GetPattern();
    if (InstanceOf<DialogPattern>(pattern)) {
        auto dialogPattern = DynamicCast<DialogPattern>(pattern);
        CHECK_NULL_RETURN(dialogPattern, false);
        if (dialogPattern->ShouldDismiss()) {
            SetDismissDialogId(overlay->GetId());
            dialogPattern->CallOnWillDismiss(static_cast<int32_t>(DialogDismissReason::DIALOG_PRESS_BACK));
            TAG_LOGI(AceLogTag::ACE_OVERLAY, "Dialog Should Dismiss");
            return true;
        }
        return RemoveDialog(overlay, false);
    }
    if (InstanceOf<BubblePattern>(pattern)) {
        return RemovePopupInSubwindow(pattern, overlay, rootNode);
    }
    if (InstanceOf<MenuWrapperPattern>(pattern)) {
        return RemoveMenu(overlay);
    }
    rootNode->RemoveChild(overlay);
    rootNode->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
    if (rootNode->GetChildren().empty()) {
        SubwindowManager::GetInstance()->HideSubWindowNG();
    }
    return true;
}

void OverlayManager::FocusOverlayNode(const RefPtr<FrameNode>& overlayNode, bool isInSubWindow)
{
    CHECK_NULL_VOID(overlayNode);
    auto overlayHub = overlayNode->GetFocusHub();
    CHECK_NULL_VOID(overlayHub);
    auto focusView = overlayHub->GetFirstChildFocusView();
    CHECK_NULL_VOID(focusView);
    focusView->FocusViewShow();
}

void OverlayManager::BlurOverlayNode(const RefPtr<FrameNode>& currentOverlay, bool isInSubWindow) {}

void OverlayManager::BlurLowerNode(const RefPtr<FrameNode>& currentOverlay) {}

void OverlayManager::ResetLowerNodeFocusable(const RefPtr<FrameNode>& currentOverlay) {}

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

void OverlayManager::FireNavigationStateChange(bool show, const RefPtr<UINode>& node)
{
    if (!show && node) {
        // Only check node When it is appointed
        NavigationPattern::FireNavigationStateChange(node, show);
        return;
    }

    // Fire show event with non-empty stack. Only Check top modal node.
    RefPtr<FrameNode> topModalNode;
    if (!modalStack_.empty()) {
        topModalNode = GetModalNodeInStack(modalStack_);
    }
    if (show && topModalNode) {
        // Modal always displays on top of stage. If it existed, only need to check the top of modal stack.
        NavigationPattern::FireNavigationStateChange(topModalNode, show);
        return;
    }

    auto lastPage = GetLastPage();
    NavigationPattern::FireNavigationStateChange(lastPage, show);
}

RefPtr<FrameNode> OverlayManager::GetModalNodeInStack(std::stack<WeakPtr<FrameNode>>& stack)
{
    if (stack.empty()) {
        return nullptr;
    }
    auto topModalNode = stack.top().Upgrade();
    CHECK_NULL_RETURN(topModalNode, nullptr);
    if (topModalNode->GetTag() == V2::MODAL_PAGE_TAG) {
        return topModalNode;
    } else {
        stack.pop();
        auto modalNode = GetModalNodeInStack(stack);
        stack.push(topModalNode);
        return modalNode;
    }
}

void OverlayManager::PlayTransitionEffectIn(const RefPtr<FrameNode>& modalNode)
{
    const auto& layoutProperty = modalNode->GetLayoutProperty();
    layoutProperty->UpdateVisibility(VisibleType::VISIBLE, true);

    modalNode->GetRenderContext()->SetTransitionInCallback([modalWK = WeakClaim(RawPtr(modalNode))] {
        auto modal = modalWK.Upgrade();
        CHECK_NULL_VOID(modal);
        modal->GetPattern<ModalPresentationPattern>()->OnAppear();
    });

    // Fire hidden event of navdestination under the appeared modal
    FireNavigationStateChange(false);
}

void OverlayManager::BindContentCover(bool isShow, std::function<void(const std::string&)>&& callback,
    std::function<RefPtr<UINode>()>&& buildNodeFunc, NG::ModalStyle& modalStyle, std::function<void()>&& onAppear,
    std::function<void()>&& onDisappear, std::function<void()>&& onWillAppear, std::function<void()>&& onWillDisappear,
    const NG::ContentCoverParam& contentCoverParam, const RefPtr<FrameNode>& targetNode, int32_t sessionId)
{
    return OnBindContentCover(isShow, std::move(callback), std::move(buildNodeFunc), modalStyle,
        std::move(onAppear), std::move(onDisappear), std::move(onWillAppear), std::move(onWillDisappear),
        contentCoverParam, targetNode, sessionId);
}

void OverlayManager::OnBindContentCover(bool isShow, std::function<void(const std::string&)>&& callback,
    std::function<RefPtr<UINode>()>&& buildNodeFunc, NG::ModalStyle& modalStyle, std::function<void()>&& onAppear,
    std::function<void()>&& onDisappear, std::function<void()>&& onWillAppear, std::function<void()>&& onWillDisappear,
    const NG::ContentCoverParam& contentCoverParam, const RefPtr<FrameNode>& targetNode, int32_t sessionId)
{
    int32_t targetId = targetNode ? targetNode->GetId() : sessionId;
    auto rootNode = FindWindowScene(targetNode);
    CHECK_NULL_VOID(rootNode);
    if (isShow) {
        auto modalTransition = modalStyle.modalTransition;
        if (!modalTransition.has_value()) {
            modalTransition = ModalTransition::DEFAULT;
        }
        if (!modalStack_.empty()) {
            auto topModalNode = modalStack_.top().Upgrade();
            CHECK_NULL_VOID(topModalNode);
            if (topModalNode->GetTag() == V2::MODAL_PAGE_TAG) {
                const auto& topModalPattern = topModalNode->GetPattern<ModalPresentationPattern>();
                if (topModalPattern->GetTargetId() == targetId) {
                    if (modalStyle.backgroundColor.has_value()) {
                        topModalNode->GetRenderContext()->UpdateBackgroundColor(modalStyle.backgroundColor.value());
                    }
                    topModalPattern->UpdateOnDisappear(std::move(onDisappear));
                    topModalPattern->UpdateOnWillDisappear(std::move(onWillDisappear));
                    topModalPattern->UpdateOnAppear(std::move(onAppear));
                    topModalPattern->UpdateOnWillDismiss(std::move(contentCoverParam.onWillDismiss));
                    topModalPattern->SetType(modalTransition.value());
                    topModalPattern->SetHasTransitionEffect(contentCoverParam.transitionEffect != nullptr);
                    topModalNode->GetRenderContext()->UpdateChainedTransition(contentCoverParam.transitionEffect);
                    return;
                }
            }
        }
        if (onWillAppear) {
            onWillAppear();
        }
        HandleModalShow(std::move(callback), std::move(buildNodeFunc), modalStyle, std::move(onAppear),
            std::move(onDisappear), std::move(onWillDisappear), rootNode, contentCoverParam,
            targetId, modalTransition);
        return;
    }

    // isShow = false, Pop ModalPage
    if (!modalStack_.empty()) {
        HandleModalPop(std::move(onWillDisappear), rootNode, targetId);
    }
}

void OverlayManager::HandleModalShow(std::function<void(const std::string&)>&& callback,
    std::function<RefPtr<UINode>()>&& buildNodeFunc, NG::ModalStyle& modalStyle, std::function<void()>&& onAppear,
    std::function<void()>&& onDisappear, std::function<void()>&& onWillDisappear, const RefPtr<UINode> rootNode,
    const NG::ContentCoverParam& contentCoverParam, int32_t targetId, std::optional<ModalTransition> modalTransition)
{
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
    auto modalPagePattern = modalNode->GetPattern<ModalPresentationPattern>();
    CHECK_NULL_VOID(modalPagePattern);
    modalPagePattern->UpdateOnDisappear(std::move(onDisappear));
    modalPagePattern->UpdateOnWillDisappear(std::move(onWillDisappear));
    modalPagePattern->UpdateOnAppear(std::move(onAppear));
    modalPagePattern->UpdateOnWillDismiss(std::move(contentCoverParam.onWillDismiss));
    modalPagePattern->UpdateUIExtensionMode(modalStyle.isUIExtension);
    modalPagePattern->SetHasTransitionEffect(contentCoverParam.transitionEffect != nullptr);
    modalNode->GetRenderContext()->UpdateChainedTransition(contentCoverParam.transitionEffect);
    modalStack_.push(WeakClaim(RawPtr(modalNode)));
    modalList_.emplace_back(WeakClaim(RawPtr(modalNode)));
    SaveLastModalNode();
    modalNode->MountToParent(rootNode);
    modalNode->AddChild(builder);
    FireModalPageShow();
    rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    if (contentCoverParam.transitionEffect != nullptr) {
        PlayTransitionEffectIn(modalNode);
        return;
    }
    if (!AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE) ||
        modalTransition == ModalTransition::NONE) {
        modalPagePattern->OnAppear();
        // Fire hidden event of navdestination under the appeared modal
        FireNavigationStateChange(false);
    }
    if (modalTransition == ModalTransition::DEFAULT) {
        PlayDefaultModalTransition(modalNode, true);
    } else if (modalTransition == ModalTransition::ALPHA) {
        PlayAlphaModalTransition(modalNode, true);
    }
}

void OverlayManager::HandleModalPop(
    std::function<void()>&& onWillDisappear, const RefPtr<UINode> rootNode, int32_t targetId)
{
    auto topModalNode = modalStack_.top().Upgrade();
    CHECK_NULL_VOID(topModalNode);
    if (!CheckTopModalNode(topModalNode, targetId)) {
        return;
    }
    auto builder = AceType::DynamicCast<FrameNode>(topModalNode->GetFirstChild());
    CHECK_NULL_VOID(builder);
    if (builder->GetRenderContext()->HasDisappearTransition()) {
        if (!topModalNode->GetPattern<ModalPresentationPattern>()->IsExecuteOnDisappear()) {
            topModalNode->GetPattern<ModalPresentationPattern>()->OnDisappear();
            // Fire hidden event of navdestination on the disappeared modal
            FireNavigationStateChange(false, topModalNode);
        }
        topModalNode->Clean(false, true);
        topModalNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }
    auto modalPresentationPattern = topModalNode->GetPattern<ModalPresentationPattern>();
    CHECK_NULL_VOID(modalPresentationPattern);
    auto modalTransition = modalPresentationPattern->GetType();
    // lost focus
    ModalPageLostFocus(topModalNode);
    if (onWillDisappear) {
        onWillDisappear();
    }
    if (modalPresentationPattern->HasTransitionEffect()) {
        PlayTransitionEffectOut(topModalNode);
    } else if (modalTransition == ModalTransition::DEFAULT) {
        PlayDefaultModalTransition(topModalNode, false);
    } else if (modalTransition == ModalTransition::ALPHA) {
        PlayAlphaModalTransition(topModalNode, false);
    } else if (!builder->GetRenderContext()->HasDisappearTransition()) {
        if (!modalPresentationPattern->IsExecuteOnDisappear()) {
            modalPresentationPattern->OnDisappear();
            // Fire hidden event of navdestination on the disappeared modal
            FireNavigationStateChange(false, topModalNode);
        }
        rootNode->RemoveChild(topModalNode);
        rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }
    modalStack_.pop();
    if (!modalList_.empty()) {
        modalList_.pop_back();
    }
    if (modalTransition == ModalTransition::NONE || builder->GetRenderContext()->HasDisappearTransition()) {
        // Fire shown event of navdestination under the disappeared modal
        FireNavigationStateChange(true);
    }
    FireModalPageHide();
    SaveLastModalNode();
}

void OverlayManager::FireModalPageShow()
{
    auto topModalNode = modalList_.back().Upgrade();
    CHECK_NULL_VOID(topModalNode);
    auto topModalFocusView = topModalNode->GetPattern<FocusView>();
    CHECK_NULL_VOID(topModalFocusView);
    topModalFocusView->FocusViewShow();
}

void OverlayManager::ModalPageLostFocus(const RefPtr<FrameNode>& node)
{
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    if (container->IsUIExtensionWindow()) {
        FocusHub::NavCloseKeyboard();
    } else {
        auto pipeline = PipelineContext::GetCurrentContextSafely();
        CHECK_NULL_VOID(pipeline);
        auto textfieldManager = DynamicCast<TextFieldManagerNG>(pipeline->GetTextFieldManager());
        CHECK_NULL_VOID(textfieldManager);
        textfieldManager->ProcessNavKeyboard();
    }
}

void OverlayManager::FireModalPageHide() {}

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
        PlayDefaultModalIn(modalNode, context, option, showHeight);
    } else {
        PlayDefaultModalOut(modalNode, context, option, showHeight);
    }
}

void OverlayManager::PlayDefaultModalIn(
    const RefPtr<FrameNode>& modalNode, const RefPtr<RenderContext>& context, AnimationOption option, float showHeight)
{
    context->OnTransformTranslateUpdate({ 0.0f, showHeight, 0.0f });
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        option.SetOnFinishEvent([modalWK = WeakClaim(RawPtr(modalNode)), overlayWeak = WeakClaim(this)] {
            auto modal = modalWK.Upgrade();
            auto overlayManager = overlayWeak.Upgrade();
            CHECK_NULL_VOID(modal && overlayManager);
            modal->GetPattern<ModalPresentationPattern>()->OnAppear();
            // Fire hidden event of navdestination on the disappeared modal
            overlayManager->FireNavigationStateChange(false);
        });
    }
    AnimationUtils::Animate(
        option,
        [context]() {
            if (context) {
                context->OnTransformTranslateUpdate({ 0.0f, 0.0f, 0.0f });
            }
        },
        option.GetOnFinishEvent());
}

void OverlayManager::PlayDefaultModalOut(
    const RefPtr<FrameNode>& modalNode, const RefPtr<RenderContext>& context, AnimationOption option, float showHeight)
{
    auto lastModalNode = lastModalNode_.Upgrade();
    CHECK_NULL_VOID(lastModalNode);
    auto lastModalContext = lastModalNode->GetRenderContext();
    CHECK_NULL_VOID(lastModalContext);
    lastModalContext->UpdateOpacity(1.0);
    option.SetOnFinishEvent(
        [rootWeak = rootNodeWeak_, modalWK = WeakClaim(RawPtr(modalNode)), overlayWeak = WeakClaim(this)] {
            auto modal = modalWK.Upgrade();
            auto overlayManager = overlayWeak.Upgrade();
            CHECK_NULL_VOID(modal && overlayManager);
            auto root = overlayManager->FindWindowScene(modal);
            CHECK_NULL_VOID(root);
            if (!modal->GetPattern<ModalPresentationPattern>()->IsExecuteOnDisappear()) {
                modal->GetPattern<ModalPresentationPattern>()->OnDisappear();
                // Fire hidden event of navdestination on the disappeared modal
                overlayManager->FireNavigationStateChange(false, modal);
            }
            root->RemoveChild(modal);
            root->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
            // Fire shown event of navdestination under the disappeared modal
            overlayManager->FireNavigationStateChange(true);
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
        if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
            option.SetOnFinishEvent([modalWK = WeakClaim(RawPtr(modalNode)), overlayWeak = WeakClaim(this)] {
                auto modal = modalWK.Upgrade();
                auto overlayManager = overlayWeak.Upgrade();
                CHECK_NULL_VOID(modal && overlayManager);
                modal->GetPattern<ModalPresentationPattern>()->OnAppear();
                // Fire hidden event of navdestination on the disappeared modal
                overlayManager->FireNavigationStateChange(false);
            });
        }
        // current modal page animation
        context->OpacityAnimation(option, 0, 1);
    } else {
        // last page animation
        lastModalContext->OpacityAnimation(option, 0, 1);

        // current modal page animation
        option.SetOnFinishEvent(
            [rootWeak = rootNodeWeak_, modalWK = WeakClaim(RawPtr(modalNode)), overlayWeak = WeakClaim(this)] {
                auto modal = modalWK.Upgrade();
                auto overlayManager = overlayWeak.Upgrade();
                CHECK_NULL_VOID(modal && overlayManager);
                auto root = overlayManager->FindWindowScene(modal);
                CHECK_NULL_VOID(root);
                if (!modal->GetPattern<ModalPresentationPattern>()->IsExecuteOnDisappear()) {
                    modal->GetPattern<ModalPresentationPattern>()->OnDisappear();
                    // Fire hidden event of navdestination on the disappeared modal
                    overlayManager->FireNavigationStateChange(false, modal);
                }
                root->RemoveChild(modal);
                root->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
                // Fire shown event of navdestination under the disappeared modal
                overlayManager->FireNavigationStateChange(true);
            });
        context->OpacityAnimation(option, 1, 0);
    }
}

void OverlayManager::BindSheet(bool isShow, std::function<void(const std::string&)>&& callback,
    std::function<RefPtr<UINode>()>&& buildNodeFunc, std::function<RefPtr<UINode>()>&& buildtitleNodeFunc,
    NG::SheetStyle& sheetStyle, std::function<void()>&& onAppear, std::function<void()>&& onDisappear,
    std::function<void()>&& shouldDismiss, std::function<void(const int32_t)>&& onWillDismiss,
    std::function<void()>&& onWillAppear, std::function<void()>&& onWillDisappear,
    std::function<void(const float)>&& onHeightDidChange, std::function<void(const float)>&& onDetentsDidChange,
    std::function<void(const float)>&& onWidthDidChange, std::function<void(const float)>&& onTypeDidChange,
    std::function<void()>&& sheetSpringBack, const RefPtr<FrameNode>& targetNode)
{
    auto instanceId = sheetStyle.instanceId.has_value() ? sheetStyle.instanceId.value() : Container::CurrentId();
    ContainerScope scope(instanceId);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto bindSheetTask = [weak = AceType::WeakClaim(this), isShow, callback = std::move(callback),
                             buildNodeFunc = std::move(buildNodeFunc),
                             buildtitleNodeFunc = std::move(buildtitleNodeFunc), sheetStyle,
                             onAppear = std::move(onAppear), onDisappear = std::move(onDisappear),
                             shouldDismiss = std::move(shouldDismiss), onWillDismiss = std::move(onWillDismiss),
                             onWillAppear = std::move(onWillAppear), onWillDisappear = std::move(onWillDisappear),
                             onHeightDidChange = std::move(onHeightDidChange),
                             onDetentsDidChange = std::move(onDetentsDidChange),
                             onWidthDidChange = std::move(onWidthDidChange),
                             onTypeDidChange = std::move(onTypeDidChange), sheetSpringBack = std::move(sheetSpringBack),
                             targetNode, instanceId]() mutable {
        ContainerScope scope(instanceId);
        auto overlay = weak.Upgrade();
        CHECK_NULL_VOID(overlay);
        overlay->OnBindSheet(isShow, std::move(callback), std::move(buildNodeFunc), std::move(buildtitleNodeFunc),
            sheetStyle, std::move(onAppear), std::move(onDisappear), std::move(shouldDismiss), std::move(onWillDismiss),
            std::move(onWillAppear), std::move(onWillDisappear), std::move(onHeightDidChange),
            std::move(onDetentsDidChange), std::move(onWidthDidChange), std::move(onTypeDidChange),
            std::move(sheetSpringBack), targetNode);
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        pipeline->FlushUITasks();
    };
    pipeline->RequestFrame();
    pipeline->AddAnimationClosure(bindSheetTask);
}

void OverlayManager::OnBindSheet(bool isShow, std::function<void(const std::string&)>&& callback,
    std::function<RefPtr<UINode>()>&& buildNodeFunc, std::function<RefPtr<UINode>()>&& buildtitleNodeFunc,
    NG::SheetStyle& sheetStyle, std::function<void()>&& onAppear, std::function<void()>&& onDisappear,
    std::function<void()>&& shouldDismiss, std::function<void(const int32_t)>&& onWillDismiss,
    std::function<void()>&& onWillAppear, std::function<void()>&& onWillDisappear,
    std::function<void(const float)>&& onHeightDidChange, std::function<void(const float)>&& onDetentsDidChange,
    std::function<void(const float)>&& onWidthDidChange, std::function<void(const float)>&& onTypeDidChange,
    std::function<void()>&& sheetSpringBack, const RefPtr<FrameNode>& targetNode)
{
    int32_t targetId = targetNode->GetId();
    auto rootNode = FindWindowScene(targetNode);
    CHECK_NULL_VOID(rootNode);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto sheetTheme = pipeline->GetTheme<SheetTheme>();
    CHECK_NULL_VOID(sheetTheme);
    if (!isShow) {
        CloseSheet(targetId);
        return;
    }
    auto iter = sheetMap_.find(targetId);
    if (iter != sheetMap_.end()) {
        auto topModalNode = iter->second.Upgrade();
        CHECK_NULL_VOID(topModalNode);
        if (topModalNode->GetTag() == V2::SHEET_PAGE_TAG &&
            topModalNode->GetPattern<SheetPresentationPattern>()->GetTargetId() == targetId) {
            SetSheetBackgroundColor(topModalNode, sheetTheme, sheetStyle);
            auto topModalRenderContext = topModalNode->GetRenderContext();
            CHECK_NULL_VOID(topModalRenderContext);
            if (sheetStyle.backgroundBlurStyle.has_value()) {
                SetSheetBackgroundBlurStyle(topModalNode, sheetStyle.backgroundBlurStyle.value());
            }
            auto layoutProperty = topModalNode->GetLayoutProperty<SheetPresentationProperty>();
            if (sheetStyle.borderWidth.has_value()) {
                layoutProperty->UpdateBorderWidth(sheetStyle.borderWidth.value());
                topModalRenderContext->UpdateBorderWidth(sheetStyle.borderWidth.value());
            } else {
                BorderWidthProperty borderWidth;
                borderWidth.SetBorderWidth(0.0_vp);
                layoutProperty->UpdateBorderWidth(borderWidth);
                topModalRenderContext->UpdateBorderWidth(borderWidth);
            }
            if (sheetStyle.borderStyle.has_value()) {
                topModalRenderContext->UpdateBorderStyle(sheetStyle.borderStyle.value());
            }
            if (sheetStyle.borderColor.has_value()) {
                topModalRenderContext->UpdateBorderColor(sheetStyle.borderColor.value());
            }
            if (sheetStyle.shadow.has_value()) {
                topModalRenderContext->UpdateBackShadow(sheetStyle.shadow.value());
            } else {
                topModalRenderContext->UpdateBackShadow(ShadowConfig::NoneShadow);
            }
            auto maskNode = GetSheetMask(topModalNode);
            if (maskNode) {
                auto maskRenderContext = maskNode->GetRenderContext();
                CHECK_NULL_VOID(maskRenderContext);
                maskRenderContext->UpdateBackgroundColor(sheetStyle.maskColor.value_or(sheetTheme->GetMaskColor()));
            }
            auto topModalNodePattern = topModalNode->GetPattern<SheetPresentationPattern>();
            topModalNodePattern->UpdateOnAppear(std::move(onAppear));
            topModalNodePattern->UpdateOnDisappear(std::move(onDisappear));
            topModalNodePattern->UpdateShouldDismiss(std::move(shouldDismiss));
            topModalNodePattern->UpdateOnWillDismiss(std::move(onWillDismiss));
            topModalNodePattern->UpdateOnWillDisappear(std::move(onWillDisappear));
            topModalNodePattern->UpdateOnHeightDidChange(std::move(onHeightDidChange));
            topModalNodePattern->UpdateOnDetentsDidChange(std::move(onDetentsDidChange));
            topModalNodePattern->UpdateOnWidthDidChange(std::move(onWidthDidChange));
            topModalNodePattern->UpdateOnTypeDidChange(std::move(onTypeDidChange));
            topModalNodePattern->UpdateSheetSpringBack(std::move(sheetSpringBack));
            layoutProperty->UpdateSheetStyle(sheetStyle);
            topModalNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
            pipeline->FlushUITasks();
            ComputeSheetOffset(sheetStyle, topModalNode);
            auto sheetType = topModalNodePattern->GetSheetType();
            if (sheetType != SheetType::SHEET_POPUP && !topModalNodePattern->GetAnimationProcess()) {
                PlaySheetTransition(topModalNode, true, false, false);
            }
            return;
        }
    }
    // builder content
    auto builder = AceType::DynamicCast<FrameNode>(buildNodeFunc());
    CHECK_NULL_VOID(builder);
    builder->GetRenderContext()->SetIsModalRootNode(true);

    auto titlebuilder = AceType::DynamicCast<FrameNode>(buildtitleNodeFunc());
    if (titlebuilder) {
        titlebuilder->GetRenderContext()->SetIsModalRootNode(true);
    }
    // create modal page
    auto sheetNode = SheetView::CreateSheetPage(
        targetId, targetNode->GetTag(), builder, titlebuilder, std::move(callback), sheetStyle);
    CHECK_NULL_VOID(sheetNode);
    auto sheetRenderContext = sheetNode->GetRenderContext();
    CHECK_NULL_VOID(sheetRenderContext);
    if (sheetStyle.backgroundColor.has_value()) {
        sheetNode->GetRenderContext()->UpdateBackgroundColor(sheetStyle.backgroundColor.value());
    }
    if (sheetStyle.backgroundBlurStyle.has_value()) {
        SetSheetBackgroundBlurStyle(sheetNode, sheetStyle.backgroundBlurStyle.value());
    }
    if (sheetStyle.borderWidth.has_value()) {
        auto sheetLayoutProps = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
        sheetLayoutProps->UpdateBorderWidth(sheetStyle.borderWidth.value());
        sheetRenderContext->UpdateBorderWidth(sheetStyle.borderWidth.value());
    }
    if (sheetStyle.borderStyle.has_value()) {
        sheetRenderContext->UpdateBorderStyle(sheetStyle.borderStyle.value());
    }
    if (sheetStyle.borderColor.has_value()) {
        sheetRenderContext->UpdateBorderColor(sheetStyle.borderColor.value());
    }
    if (sheetStyle.shadow.has_value()) {
        sheetRenderContext->UpdateBackShadow(sheetStyle.shadow.value());
    }
    auto sheetNodePattern = sheetNode->GetPattern<SheetPresentationPattern>();
    sheetNodePattern->UpdateOnAppear(std::move(onAppear));
    sheetNodePattern->UpdateOnDisappear(std::move(onDisappear));
    sheetNodePattern->UpdateShouldDismiss(std::move(shouldDismiss));
    sheetNodePattern->UpdateOnWillDismiss(std::move(onWillDismiss));
    sheetNodePattern->UpdateOnWillDisappear(std::move(onWillDisappear));
    sheetNodePattern->UpdateOnHeightDidChange(std::move(onHeightDidChange));
    sheetNodePattern->UpdateOnDetentsDidChange(std::move(onDetentsDidChange));
    sheetNodePattern->UpdateOnWidthDidChange(std::move(onWidthDidChange));
    sheetNodePattern->UpdateOnTypeDidChange(std::move(onTypeDidChange));
    sheetNodePattern->UpdateSheetSpringBack(std::move(sheetSpringBack));
    sheetMap_[targetId] = WeakClaim(RawPtr(sheetNode));
    modalStack_.push(WeakClaim(RawPtr(sheetNode)));
    SaveLastModalNode();
    // create maskColor node
    auto sheetType = sheetNodePattern->GetSheetType();
    auto maskNode = FrameNode::CreateFrameNode(
        V2::SHEET_MASK_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    CHECK_NULL_VOID(maskNode);
    auto maskLayoutProps = maskNode->GetLayoutProperty();
    CHECK_NULL_VOID(maskLayoutProps);
    maskLayoutProps->UpdateMeasureType(MeasureType::MATCH_PARENT);
    auto maskRenderContext = maskNode->GetRenderContext();
    CHECK_NULL_VOID(maskRenderContext);
    if (!Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        if (sheetStyle.maskColor.has_value()) {
            maskRenderContext->UpdateBackgroundColor(sheetStyle.maskColor.value());
        } else {
            maskLayoutProps->UpdateVisibility(VisibleType::INVISIBLE);
        }
    } else {
        maskRenderContext->UpdateBackgroundColor(sheetStyle.maskColor.value_or(sheetTheme->GetMaskColor()));
        auto eventConfirmHub = maskNode->GetOrCreateGestureEventHub();
        CHECK_NULL_VOID(eventConfirmHub);
        sheetMaskClickEvent_ = AceType::MakeRefPtr<NG::ClickEvent>(
            [weak = AceType::WeakClaim(AceType::RawPtr(sheetNode))](const GestureEvent& /* info */) {
                auto sheet = weak.Upgrade();
                CHECK_NULL_VOID(sheet);
                auto sheetPattern = sheet->GetPattern<SheetPresentationPattern>();
                CHECK_NULL_VOID(sheetPattern);
                if (sheetPattern->IsDragging()) {
                    return;
                }
                sheetPattern->SheetInteractiveDismiss(BindSheetDismissReason::TOUCH_OUTSIDE);
            });
        eventConfirmHub->AddClickEvent(sheetMaskClickEvent_);
    }
    maskNode->MountToParent(rootNode);
    PlaySheetMaskTransition(maskNode, true, static_cast<bool>(callback));
    auto columnNode = FrameNode::CreateFrameNode(V2::SHEET_WRAPPER_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    CHECK_NULL_VOID(columnNode);
    auto columnLayoutProps = columnNode->GetLayoutProperty();
    CHECK_NULL_VOID(columnLayoutProps);
    columnLayoutProps->UpdateMeasureType(MeasureType::MATCH_PARENT);
    columnLayoutProps->UpdateAlignment(Alignment::TOP_LEFT);
    sheetNode->MountToParent(columnNode);
    columnNode->MountToParent(rootNode);
    modalList_.emplace_back(WeakClaim(RawPtr(sheetNode)));
    FireModalPageShow();
    rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    pipeline->FlushUITasks();
    ComputeSheetOffset(sheetStyle, sheetNode);
    if (onWillAppear) {
        TAG_LOGI(AceLogTag::ACE_SHEET, "bindsheet lifecycle change to onWillAppear state.");
        onWillAppear();
    }
    if (!AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
        CHECK_NULL_VOID(sheetPattern);
        sheetPattern->OnAppear();
    }

    // start transition animation
    if (sheetType == SheetType::SHEET_POPUP) {
        PlayBubbleStyleSheetTransition(sheetNode, true);
    } else {
        PlaySheetTransition(sheetNode, true);
    }
}

void OverlayManager::CloseSheet(int32_t targetId)
{
    if (modalStack_.empty()) {
        return;
    }
    auto iter = sheetMap_.find(targetId);
    if (sheetMap_.empty() || iter == sheetMap_.end()) {
        DeleteModal(targetId);
        return;
    }
    auto sheetNode = iter->second.Upgrade();
    CHECK_NULL_VOID(sheetNode);
    sheetNode->GetPattern<SheetPresentationPattern>()->SetShowState(false);
    auto scrollNode = AceType::DynamicCast<FrameNode>(sheetNode->GetChildAtIndex(1));
    CHECK_NULL_VOID(scrollNode);
    auto builder = AceType::DynamicCast<FrameNode>(scrollNode->GetChildAtIndex(0));
    CHECK_NULL_VOID(builder);
    sheetNode->GetPattern<SheetPresentationPattern>()->OnWillDisappear();
    if (builder->GetRenderContext()->HasDisappearTransition()) {
        if (!sheetNode->GetPattern<SheetPresentationPattern>()->IsExecuteOnDisappear()) {
            sheetNode->GetPattern<SheetPresentationPattern>()->OnDisappear();
        }
        sheetNode->GetPattern<SheetPresentationPattern>()->OnDisappear();
        sheetNode->Clean(false, true);
        sheetNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }
    ModalPageLostFocus(sheetNode);
    auto maskNode = GetSheetMask(sheetNode);
    if (maskNode) {
        PlaySheetMaskTransition(maskNode, false, sheetNode->GetPattern<SheetPresentationPattern>()->HasCallback());
    }
    auto sheetType = sheetNode->GetPattern<SheetPresentationPattern>()->GetSheetType();
    if (sheetType == SheetType::SHEET_POPUP) {
        PlayBubbleStyleSheetTransition(sheetNode, false);
    } else {
        PlaySheetTransition(sheetNode, false);
    }
    sheetMap_.erase(targetId);
    RemoveSheetNode(sheetNode);
    FireModalPageHide();
    SaveLastModalNode();
}

void OverlayManager::DismissSheet()
{
    if (modalStack_.empty()) {
        return;
    }
    auto iter = sheetMap_.find(dismissTargetId_);
    if (sheetMap_.empty() || iter == sheetMap_.end()) {
        DeleteModal(dismissTargetId_);
        return;
    }
    auto sheetNode = iter->second.Upgrade();
    CHECK_NULL_VOID(sheetNode);
    if (sheetNode->GetTag() == V2::SHEET_PAGE_TAG) {
        auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
        CHECK_NULL_VOID(sheetPattern);
        sheetPattern->DismissSheet();
    }
}

void OverlayManager::DismissContentCover()
{
    if (modalStack_.empty()) {
        return;
    }
    const auto& modalNode = GetModal(dismissTargetId_);
    if (modalNode == nullptr) {
        DeleteModal(dismissTargetId_);
        return;
    }
    if (modalNode->GetTag() == V2::MODAL_PAGE_TAG) {
        ModalPageLostFocus(modalNode);
        auto builder = AceType::DynamicCast<FrameNode>(modalNode->GetFirstChild());
        if (!ModalPageExitProcess(modalNode)) {
            return;
        }
        RemoveModal(dismissTargetId_);
        auto modalPattern = modalNode->GetPattern<ModalPresentationPattern>();
        CHECK_NULL_VOID(modalPattern);
        auto modalTransition = modalPattern->GetType();
        if (modalTransition == ModalTransition::NONE || builder->GetRenderContext()->HasDisappearTransition()) {
            FireNavigationStateChange(true);
        }
        FireModalPageHide();
        SaveLastModalNode();
    }
}

void OverlayManager::SheetSpringBack()
{
    auto sheetNode = sheetMap_[dismissTargetId_].Upgrade();
    CHECK_NULL_VOID(sheetNode);
    if (sheetNode->GetTag() == V2::SHEET_PAGE_TAG) {
        auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
        CHECK_NULL_VOID(sheetPattern);
        sheetPattern->SheetSpringBack();
    }
}

RefPtr<FrameNode> OverlayManager::GetModal(int32_t targetId)
{
    for (auto modal = modalList_.begin(); modal != modalList_.end(); modal++) {
        auto modalNode = (*modal).Upgrade();
        if (!modalNode) {
            continue;
        }
        int32_t modalTargetId = -1;
        if (modalNode->GetTag() == V2::MODAL_PAGE_TAG) {
            modalTargetId = modalNode->GetPattern<ModalPresentationPattern>()->GetTargetId();
        } else if (modalNode->GetTag() == V2::SHEET_PAGE_TAG) {
            modalTargetId = modalNode->GetPattern<SheetPresentationPattern>()->GetTargetId();
        } else {
            continue;
        }
        if (modalTargetId == targetId) {
            return modalNode;
        }
    }
    return nullptr;
}

void OverlayManager::RemoveModal(int32_t targetId)
{
    bool isDelete = false;
    for (auto modal = modalList_.begin(); modal != modalList_.end(); modal++) {
        auto modalNode = (*modal).Upgrade();
        if (!modalNode) {
            continue;
        }
        int32_t modalTargetId = -1;
        if (modalNode->GetTag() == V2::MODAL_PAGE_TAG) {
            modalTargetId = modalNode->GetPattern<ModalPresentationPattern>()->GetTargetId();
        } else if (modalNode->GetTag() == V2::SHEET_PAGE_TAG) {
            modalTargetId = modalNode->GetPattern<SheetPresentationPattern>()->GetTargetId();
        } else {
            continue;
        }
        if (modalTargetId == targetId) {
            isDelete = true;
            modalList_.erase(modal);
            break;
        } else {
            ++modal;
        }
    }
    if (isDelete) {
        while (!modalStack_.empty()) {
            modalStack_.pop();
        }
        for (auto modal = modalList_.begin(); modal != modalList_.end(); modal++) {
            modalStack_.push(*modal);
        }
    }
}

void OverlayManager::RemoveSheetNode(const RefPtr<FrameNode>& sheetNode)
{
    CHECK_NULL_VOID(sheetNode);
    if (!modalList_.empty()) {
        modalList_.remove(WeakClaim(RawPtr(sheetNode)));
    }
    std::vector<WeakPtr<FrameNode>> sheetVector;
    while (!modalStack_.empty()) {
        if (modalStack_.top() != WeakClaim(RawPtr(sheetNode))) {
            sheetVector.push_back(modalStack_.top());
        }
        modalStack_.pop();
    }
    for (auto iter : sheetVector) {
        modalStack_.push(iter);
    }
}

void OverlayManager::PlaySheetTransition(
    RefPtr<FrameNode> sheetNode, bool isTransitionIn, bool isFirstTransition, bool isModeChangeToAuto)
{
    // current sheet animation
    AnimationOption option;
    const RefPtr<InterpolatingSpring> curve =
        AceType::MakeRefPtr<InterpolatingSpring>(0.0f, CURVE_MASS, CURVE_STIFFNESS, CURVE_DAMPING);
    option.SetCurve(curve);
    option.SetFillMode(FillMode::FORWARDS);
    auto context = sheetNode->GetRenderContext();
    CHECK_NULL_VOID(context);
    context->UpdateRenderGroup(true, true, true);
    TAG_LOGD(AceLogTag::ACE_SHEET, "UpdateRenderGroup start");
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    auto sheetMaxHeight = sheetPattern->GetPageHeightWithoutOffset();
    auto sheetParent = DynamicCast<FrameNode>(sheetNode->GetParent());
    CHECK_NULL_VOID(sheetParent);
    if (isTransitionIn) {
        sheetPattern->SetCurrentHeight(sheetHeight_);
        float offset = 0.0f;
        if (sheetPattern->GetSheetType() == SheetType::SHEET_POPUP) {
            offset = sheetPattern->GetSheetOffset();
        } else {
            offset = sheetMaxHeight - sheetHeight_;
        }
        if (isFirstTransition) {
            context->UpdateTransformTranslate({ 0.0f, sheetMaxHeight, 0.0f });
            if (NearZero(sheetHeight_)) {
                return;
            }
        }
        if (isModeChangeToAuto) {
            option.SetDuration(0);
            option.SetCurve(Curves::LINEAR);
        }
        sheetPattern->FireOnTypeDidChange();
        sheetPattern->FireOnWidthDidChange(sheetNode);
        option.SetOnFinishEvent(
            [sheetWK = WeakClaim(RawPtr(sheetNode)), weak = AceType::WeakClaim(this), isFirst = isFirstTransition] {
                auto sheetNode = sheetWK.Upgrade();
                CHECK_NULL_VOID(sheetNode);
                auto context = sheetNode->GetRenderContext();
                CHECK_NULL_VOID(context);
                context->UpdateRenderGroup(false, true, true);
                TAG_LOGD(AceLogTag::ACE_SHEET, "UpdateRenderGroup finished");
                auto pattern = sheetNode->GetPattern<SheetPresentationPattern>();
                if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE) &&
                    isFirst) {
                    pattern->OnAppear();
                }
                pattern->AvoidAiBar();
                auto overlay = weak.Upgrade();
                CHECK_NULL_VOID(overlay);
                pattern->FireOnDetentsDidChange(overlay->sheetHeight_);
                pattern->FireOnHeightDidChange(overlay->sheetHeight_);
            });
        sheetParent->GetEventHub<EventHub>()->GetOrCreateGestureEventHub()->SetHitTestMode(HitTestMode::HTMDEFAULT);
        AnimationUtils::Animate(
            option,
            [context, offset]() {
                if (context) {
                    context->UpdateTransformTranslate({ 0.0f, offset, 0.0f });
                }
            },
            option.GetOnFinishEvent());
    } else {
        option.SetOnFinishEvent(
            [rootWeak = rootNodeWeak_, sheetWK = WeakClaim(RawPtr(sheetNode)), weakOverlayManager = WeakClaim(this)] {
                auto sheet = sheetWK.Upgrade();
                auto overlayManager = weakOverlayManager.Upgrade();
                CHECK_NULL_VOID(sheet && overlayManager);
                if (!sheet->GetPattern<SheetPresentationPattern>()->IsExecuteOnDisappear()) {
                    sheet->GetPattern<SheetPresentationPattern>()->OnDisappear();
                }
                auto root = overlayManager->FindWindowScene(sheet);
                CHECK_NULL_VOID(root);
                auto sheetParent = DynamicCast<FrameNode>(sheet->GetParent());
                CHECK_NULL_VOID(sheetParent);
                root->RemoveChild(sheetParent);
                root->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
            });
        if (sheetPattern->HasCallback()) {
            sheetParent->GetEventHub<EventHub>()->GetOrCreateGestureEventHub()->SetHitTestMode(
                HitTestMode::HTMTRANSPARENT);
        }
        AnimationUtils::Animate(
            option,
            [context, sheetMaxHeight]() {
                if (context) {
                    context->UpdateTransformTranslate({ 0.0f, sheetMaxHeight, 0.0f });
                }
            },
            option.GetOnFinishEvent());
    }
}

void OverlayManager::PlayBubbleStyleSheetTransition(RefPtr<FrameNode> sheetNode, bool isTransitionIn)
{
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    if (isTransitionIn) {
        sheetPattern->ResetToInvisible();
        sheetPattern->SetCurrentHeight(sheetHeight_);
        sheetPattern->StartOffsetEnteringAnimation();
        sheetPattern->FireOnHeightDidChange(sheetHeight_);
        sheetPattern->StartAlphaEnteringAnimation([sheetWK = WeakClaim(RawPtr(sheetNode))] {
            auto sheet = sheetWK.Upgrade();
            CHECK_NULL_VOID(sheet);
            auto sheetPattern = sheet->GetPattern<SheetPresentationPattern>();
            CHECK_NULL_VOID(sheetPattern);
            sheetPattern->ProcessColumnRect();
            if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
                sheetPattern->OnAppear();
            }
        });
    } else {
        sheetPattern->StartOffsetExitingAnimation();
        sheetPattern->StartAlphaExitingAnimation(
            [rootWeak = rootNodeWeak_, sheetWK = WeakClaim(RawPtr(sheetNode)), id = Container::CurrentId(),
                    weakOverlayManager = WeakClaim(this)] {
                ContainerScope scope(id);
                auto context = PipelineContext::GetCurrentContext();
                CHECK_NULL_VOID(context);
                auto taskExecutor = context->GetTaskExecutor();
                CHECK_NULL_VOID(taskExecutor);
                // animation finish event should be posted to UI thread.
                taskExecutor->PostTask(
                    [rootWeak, sheetWK, id, weakOverlayManager]() {
                        auto sheet = sheetWK.Upgrade();
                        auto overlayManager = weakOverlayManager.Upgrade();
                        CHECK_NULL_VOID(sheet && overlayManager);

                        ContainerScope scope(id);
                        if (!sheet->GetPattern<SheetPresentationPattern>()->IsExecuteOnDisappear()) {
                            sheet->GetPattern<SheetPresentationPattern>()->OnDisappear();
                        }
                        auto root = overlayManager->FindWindowScene(sheet);
                        CHECK_NULL_VOID(root);
                        auto sheetParent = DynamicCast<FrameNode>(sheet->GetParent());
                        CHECK_NULL_VOID(sheetParent);
                        root->RemoveChild(sheetParent);
                        root->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
                    },
                    TaskExecutor::TaskType::UI, "ArkUIOverlaySheetExitingAnimation");
            });
    }
}

void OverlayManager::PlaySheetMaskTransition(RefPtr<FrameNode> maskNode, bool isTransitionIn, bool needTransparent)
{
    AnimationOption option;
    const RefPtr<InterpolatingSpring> curve =
        AceType::MakeRefPtr<InterpolatingSpring>(0.0f, CURVE_MASS, CURVE_STIFFNESS, CURVE_DAMPING);
    option.SetCurve(curve);
    option.SetFillMode(FillMode::FORWARDS);
    auto context = maskNode->GetRenderContext();
    CHECK_NULL_VOID(context);
    if (isTransitionIn) {
        maskNode->GetEventHub<EventHub>()->GetOrCreateGestureEventHub()->SetHitTestMode(HitTestMode::HTMDEFAULT);
        context->OpacityAnimation(option, 0.0, 1.0);
    } else {
        if (sheetMaskClickEvent_) {
            auto eventConfirmHub = maskNode->GetOrCreateGestureEventHub();
            CHECK_NULL_VOID(eventConfirmHub);
            eventConfirmHub->RemoveClickEvent(sheetMaskClickEvent_);
        }
        option.SetOnFinishEvent(
            [rootWeak = rootNodeWeak_, maskNodeWK = WeakClaim(RawPtr(maskNode)),
                    weakOverlayManager = WeakClaim(this)] {
                auto mask = maskNodeWK.Upgrade();
                auto overlayManager = weakOverlayManager.Upgrade();
                CHECK_NULL_VOID(mask && overlayManager);

                auto root = overlayManager->FindWindowScene(mask);
                CHECK_NULL_VOID(root);
                root->RemoveChild(mask);
            });
        if (needTransparent) {
            maskNode->GetEventHub<EventHub>()->GetOrCreateGestureEventHub()->SetHitTestMode(
                HitTestMode::HTMTRANSPARENT);
        }
        context->OpacityAnimation(option, 1.0, 0.0);
    }
}

void OverlayManager::SetSheetBackgroundColor(const RefPtr<FrameNode>& sheetNode, const RefPtr<SheetTheme>& sheetTheme,
    const NG::SheetStyle& sheetStyle)
{
    if (!AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        if (sheetStyle.backgroundColor.has_value()) {
            sheetNode->GetRenderContext()->UpdateBackgroundColor(sheetStyle.backgroundColor.value());
        }
    } else {
        sheetNode->GetRenderContext()->UpdateBackgroundColor(sheetStyle.backgroundColor.value_or(
            sheetTheme->GetSheetBackgoundColor()));
    }
}

void OverlayManager::SetSheetBackgroundBlurStyle(const RefPtr<FrameNode>& sheetNode, const BlurStyleOption& bgBlurStyle)
{
    auto renderContext = sheetNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);

    if (renderContext->GetBackgroundEffect().has_value()) {
        renderContext->UpdateBackgroundEffect(std::nullopt);
    }
    renderContext->UpdateBackBlurStyle(bgBlurStyle);
    if (renderContext->GetBackBlurRadius().has_value()) {
        renderContext->UpdateBackBlurRadius(Dimension());
    }
}

bool OverlayManager::CheckTopModalNode(const RefPtr<FrameNode>& topModalNode, int32_t targetId)
{
    if (topModalNode->GetTag() != V2::SHEET_PAGE_TAG && topModalNode->GetTag() != V2::MODAL_PAGE_TAG) {
        return false;
    }
    if (topModalNode->GetTag() == V2::SHEET_PAGE_TAG ||
        topModalNode->GetPattern<ModalPresentationPattern>()->GetTargetId() != targetId) {
        DeleteModal(targetId);
        return false;
    }
    return true;
}

void OverlayManager::ComputeSheetOffset(NG::SheetStyle& sheetStyle, RefPtr<FrameNode> sheetNode)
{
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    auto sheetMaxHeight = sheetPattern->GetPageHeightWithoutOffset();
    auto largeHeight = sheetMaxHeight - SHEET_BLANK_MINI_HEIGHT.ConvertToPx();
    auto geometryNode = sheetNode->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto sheetHeight = geometryNode->GetFrameSize().Height();

    auto sheetType = sheetPattern->GetSheetType();
    switch (sheetType) {
        case SheetType::SHEET_BOTTOM:
        case SheetType::SHEET_BOTTOM_FREE_WINDOW:
            if (sheetStyle.detents.size() > 0) {
                ComputeDetentsSheetOffset(sheetStyle, sheetNode);
            } else {
                ComputeSingleGearSheetOffset(sheetStyle, sheetNode);
            }
            break;
        case SheetType::SHEET_BOTTOMLANDSPACE:
            sheetHeight_ = largeHeight;
            break;
        case SheetType::SHEET_CENTER:
            sheetHeight_ = (sheetHeight + sheetMaxHeight) / SHEET_HALF_SIZE;
            break;
        case SheetType::SHEET_POPUP:
            sheetHeight_ = sheetMaxHeight;
            break;
        default:
            break;
    }
}

void OverlayManager::ComputeSingleGearSheetOffset(NG::SheetStyle& sheetStyle, RefPtr<FrameNode> sheetNode)
{
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    auto sheetMaxHeight = sheetPattern->GetPageHeightWithoutOffset();
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto safeAreaInsets = pipelineContext->GetSafeAreaWithoutProcess();
    auto statusBarHeight = safeAreaInsets.top_.Length();
    auto windowManager = pipelineContext->GetWindowManager();
    if (windowManager && windowManager->GetWindowMode() == WindowMode::WINDOW_MODE_FLOATING) {
        statusBarHeight = SHEET_BLANK_FLOATING_STATUS_BAR.ConvertToPx();
    }
    auto largeHeight = sheetMaxHeight - SHEET_BLANK_MINI_HEIGHT.ConvertToPx() - statusBarHeight;
    if (sheetStyle.sheetMode.has_value()) {
        if (sheetStyle.sheetMode == SheetMode::MEDIUM) {
            sheetHeight_ = sheetMaxHeight * MEDIUM_SIZE;
            if (!Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
                sheetHeight_ = sheetMaxHeight * MEDIUM_SIZE_PRE;
            }
        } else if (sheetStyle.sheetMode == SheetMode::LARGE) {
            sheetHeight_ = largeHeight;
        } else if (sheetStyle.sheetMode == SheetMode::AUTO) {
            sheetHeight_ = sheetPattern->GetFitContentHeight();
            if (GreatNotEqual(sheetHeight_, largeHeight)) {
                sheetHeight_ = largeHeight;
            }
        }
    } else {
        float height = 0.0f;
        if (sheetStyle.height->Unit() == DimensionUnit::PERCENT) {
            height = sheetStyle.height->ConvertToPxWithSize(sheetMaxHeight - statusBarHeight);
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

void OverlayManager::ComputeDetentsSheetOffset(NG::SheetStyle& sheetStyle, RefPtr<FrameNode> sheetNode)
{
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    auto sheetMaxHeight = sheetPattern->GetPageHeightWithoutOffset();
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto safeAreaInsets = pipelineContext->GetSafeAreaWithoutProcess();
    auto statusBarHeight = safeAreaInsets.top_.Length();
    auto windowManager = pipelineContext->GetWindowManager();
    if (windowManager && windowManager->GetWindowMode() == WindowMode::WINDOW_MODE_FLOATING) {
        statusBarHeight = SHEET_BLANK_FLOATING_STATUS_BAR.ConvertToPx();
    }
    auto largeHeight = sheetMaxHeight - SHEET_BLANK_MINI_HEIGHT.ConvertToPx() - statusBarHeight;
    auto selection = sheetStyle.detents[0];
    if (selection.sheetMode.has_value()) {
        if (selection.sheetMode == SheetMode::MEDIUM) {
            sheetHeight_ = sheetMaxHeight * MEDIUM_SIZE;
            if (!Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
                sheetHeight_ = sheetMaxHeight * MEDIUM_SIZE_PRE;
            }
        } else if (selection.sheetMode == SheetMode::LARGE) {
            sheetHeight_ = largeHeight;
        } else if (selection.sheetMode == SheetMode::AUTO) {
            sheetHeight_ = sheetPattern->GetFitContentHeight();
            if (GreatNotEqual(sheetHeight_, largeHeight)) {
                sheetHeight_ = largeHeight;
            }
        }
    } else {
        float height = 0.0f;
        if (selection.height->Unit() == DimensionUnit::PERCENT) {
            height = selection.height->ConvertToPxWithSize(sheetMaxHeight - statusBarHeight);
        } else {
            height = selection.height->ConvertToPx();
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
    if (modalStack_.empty()) {
        return;
    }
    auto iter = sheetMap_.find(targetId);
    if (sheetMap_.empty() || iter == sheetMap_.end()) {
        DeleteModal(targetId, false);
        return;
    }
    auto mapSheetNode = iter->second.Upgrade();
    CHECK_NULL_VOID(mapSheetNode);
    if (mapSheetNode->GetTag() != V2::SHEET_PAGE_TAG) {
        return;
    }
    if (mapSheetNode->GetPattern<SheetPresentationPattern>()->GetTargetId() != targetId) {
        return;
    }
    auto rootNode = FindWindowScene(sheetNode);
    CHECK_NULL_VOID(rootNode);
    auto root = DynamicCast<FrameNode>(rootNode);
    ModalPageLostFocus(mapSheetNode);
    auto maskNode = GetSheetMask(sheetNode);
    if (maskNode) {
        root->RemoveChild(maskNode);
    }
    sheetNode->GetPattern<SheetPresentationPattern>()->OnDisappear();
    auto sheetParent = DynamicCast<FrameNode>(sheetNode->GetParent());
    CHECK_NULL_VOID(sheetParent);
    root->RemoveChild(sheetParent);
    root->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    sheetMap_.erase(targetId);
    RemoveSheetNode(sheetNode);
    FireModalPageHide();
    SaveLastModalNode();
}

void OverlayManager::DeleteModal(int32_t targetId, bool needOnWillDisappear)
{
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
            return;
        }
        if (currentTargetId == targetId) {
            isDelete = true;
            modalList_.erase(modal);
            DeleteModalNode(targetId, modalNode, isModal, needOnWillDisappear);
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

void OverlayManager::DeleteModalNode(
    int32_t targetId, RefPtr<FrameNode>& modalNode, bool isModal, bool needOnWillDisappear)
{
    auto rootNode = FindWindowScene(modalNode);
    CHECK_NULL_VOID(rootNode);
    if (isModal) {
        if (needOnWillDisappear) {
            modalNode->GetPattern<ModalPresentationPattern>()->OnWillDisappear();
        }
        modalNode->GetPattern<ModalPresentationPattern>()->OnDisappear();
        modalNode->GetPattern<ModalPresentationPattern>()->FireCallback("false");
        // Fire hidden event of navdestination on the disappeared modal
        FireNavigationStateChange(false, modalNode);
        rootNode->RemoveChild(modalNode);
    } else {
        if (needOnWillDisappear) {
            modalNode->GetPattern<SheetPresentationPattern>()->OnWillDisappear();
        }
        RemoveSheetMask(modalNode, rootNode);
        modalNode->GetPattern<SheetPresentationPattern>()->OnDisappear();
        modalNode->GetPattern<SheetPresentationPattern>()->FireCallback("false");
        sheetMap_.erase(targetId);
        auto sheetParent = DynamicCast<FrameNode>(modalNode->GetParent());
        CHECK_NULL_VOID(sheetParent);
        rootNode->RemoveChild(sheetParent);
    }
    rootNode->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
}

void OverlayManager::PopTopModalNode()
{
    if (!modalStack_.empty()) {
        modalStack_.pop();
    }
    if (!modalList_.empty()) {
        modalList_.pop_back();
    }
}

void OverlayManager::RemoveSheetMask(RefPtr<FrameNode>& sheetNode, RefPtr<UINode>& rootNode)
{
    auto maskNode = GetSheetMask(sheetNode);
    if (maskNode) {
        rootNode->RemoveChild(maskNode);
    }
}

RefPtr<FrameNode> OverlayManager::GetSheetMask(const RefPtr<FrameNode>& sheetNode)
{
    // get bindsheet masknode
    CHECK_NULL_RETURN(sheetNode, NULL);
    auto sheetParent = sheetNode->GetParent();
    CHECK_NULL_RETURN(sheetParent, NULL);
    auto rootNode = sheetParent->GetParent();
    CHECK_NULL_RETURN(rootNode, NULL);
    auto sheetChildIter = std::find(rootNode->GetChildren().begin(), rootNode->GetChildren().end(), sheetParent);
    if (sheetChildIter == rootNode->GetChildren().end()) {
        return NULL;
    }
    --sheetChildIter;
    CHECK_NULL_RETURN((*sheetChildIter), NULL);
    auto sheetChildFrameNode = DynamicCast<FrameNode>(*sheetChildIter);
    if (sheetChildFrameNode && sheetChildFrameNode->GetTag() != V2::SHEET_MASK_TAG) {
        return NULL;
    }
    return sheetChildFrameNode;
}

void OverlayManager::SetCustomKeyboardOption(bool supportAvoidance)
{
    auto pipeline = PipelineContext::GetMainPipelineContext();
    CHECK_NULL_VOID(pipeline);
    keyboardAvoidance_ = supportAvoidance;
}

void OverlayManager::PlayKeyboardTransition(const RefPtr<FrameNode>& customKeyboard, bool isTransitionIn)
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
    auto pipeline = PipelineContext::GetMainPipelineContext();
    CHECK_NULL_VOID(pipeline);
    auto pageNode = pipeline->GetStageManager()->GetLastPage();
    if (pageNode == nullptr) {
        auto parent = customKeyboard->GetParent();
        CHECK_NULL_VOID(parent);
        parent->RemoveChild(customKeyboard);
        return;
    }
    auto pageHeight = pageNode->GetGeometryNode()->GetFrameSize().Height();
    auto keyboardHeight = customKeyboard->GetGeometryNode()->GetFrameSize().Height();
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_VOID(rootNode);
    auto finalOffset = rootNode->GetTag() == "Stack"
                           ? (pageHeight - keyboardHeight) - (pageHeight - keyboardHeight) / NUM_FLOAT_2
                           : 0.0f;
    if (isTransitionIn) {
        context->OnTransformTranslateUpdate({ 0.0f, pageHeight, 0.0f });
        AnimationUtils::Animate(option, [context, finalOffset]() {
            if (context) {
                context->OnTransformTranslateUpdate({ 0.0f, finalOffset, 0.0f });
            }
        });
    } else {
        context->UpdateOpacity(1.0);
        option.SetOnFinishEvent([customKeyboard] {
            auto parent = customKeyboard->GetParent();
            CHECK_NULL_VOID(parent);
            parent->RemoveChild(customKeyboard);
        });
        AnimationUtils::Animate(
            option,
            [context, keyboardHeight, finalOffset]() {
                if (context) {
                    context->OnTransformTranslateUpdate({ 0.0f, finalOffset + keyboardHeight, 0.0f });
                }
            }, option.GetOnFinishEvent());
    }
}

void OverlayManager::BindKeyboard(const std::function<void()>& keyboardBuilder, int32_t targetId)
{
    if (customKeyboardMap_.find(targetId) != customKeyboardMap_.end()) {
        return;
    }
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_VOID(rootNode);
    auto customKeyboard = KeyboardView::CreateKeyboard(targetId, keyboardBuilder);
    if (!customKeyboard) {
        return;
    }
    customKeyboard->MountToParent(rootNode);
    rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    customKeyboardMap_[targetId] = customKeyboard;
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->AddAfterLayoutTask([weak = WeakClaim(this), customKeyboard] {
        auto overlayManager = weak.Upgrade();
        CHECK_NULL_VOID(overlayManager);
        overlayManager->PlayKeyboardTransition(customKeyboard, true);
    });
}

void OverlayManager::BindKeyboardWithNode(const RefPtr<UINode>& keyboard, int32_t targetId)
{
    if (customKeyboardMap_.find(targetId) != customKeyboardMap_.end()) {
        return;
    }
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_VOID(rootNode);
    auto customKeyboard = KeyboardView::CreateKeyboardWithNode(targetId, keyboard);
    if (!customKeyboard) {
        return;
    }
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

    auto pipeline = PipelineBase::GetCurrentContext();
    Rect keyboardRect = Rect(0.0f, 0.0f, 0.0f, 0.0f);
    CHECK_NULL_VOID(pipeline);
    pipeline->OnVirtualKeyboardAreaChange(keyboardRect);
}

void OverlayManager::AvoidCustomKeyboard(int32_t targetId, float safeHeight)
{
    auto it = customKeyboardMap_.find(targetId);
    if (it == customKeyboardMap_.end()) {
        return;
    }
    auto customKeyboard = it->second;
    CHECK_NULL_VOID(customKeyboard);
    auto pattern = customKeyboard->GetPattern<KeyboardPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetKeyboardAreaChange(keyboardAvoidance_);
    pattern->SetKeyboardOption(keyboardAvoidance_);
    pattern->SetKeyboardSafeHeight(safeHeight);
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
    auto parent = targetNode->GetParent();
    while (parent && parent->GetTag() != V2::WINDOW_SCENE_ETS_TAG) {
        parent = parent->GetParent();
    }
    CHECK_NULL_RETURN(parent, nullptr);
    windowSceneSet_.insert(parent);
    return parent;
}

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
    if (!columnNode) {
        hasPixelMap_ = false;
        isOnAnimation_ = false;
        return;
    }
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
    if (!columnNode) {
        RemoveEventColumn();
        hasPixelMap_ = false;
        return;
    }
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

    DragEventActuator::ExecutePreDragAction(PreDragStatus::PREVIEW_LANDING_STARTED);
    scaleOption.SetOnFinishEvent([this] {
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto dragDropManager = pipeline->GetDragDropManager();
        CHECK_NULL_VOID(dragDropManager);
        DragEventActuator::ExecutePreDragAction(PreDragStatus::PREVIEW_LANDING_FINISHED);
        if (!dragDropManager->IsNeedDisplayInSubwindow()) {
            InteractionInterface::GetInstance()->SetDragWindowVisible(true);
        }
        auto overlayManager = AceType::Claim(this);
        CHECK_NULL_VOID(overlayManager);
        if (overlayManager->hasEvent_) {
            overlayManager->RemoveEventColumn();
        }
        overlayManager->RemovePixelMap();
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
    if (height == 0 || width == 0) {
        return;
    }
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
    option.SetOnFinishEvent([weak = WeakClaim(this)] {
        auto overlayManager = weak.Upgrade();
        CHECK_NULL_VOID(overlayManager);
        if (!overlayManager->hasFilterActived) {
            overlayManager->RemoveFilter();
        }
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
    if (columnNode) {
        auto rootNode = columnNode->GetParent();
        CHECK_NULL_VOID(rootNode);
        rootNode->RemoveChild(columnNode);
        rootNode->RebuildRenderContextTree();
    }
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

int32_t OverlayManager::CreateModalUIExtension(
    const AAFwk::Want& want, const ModalUIExtensionCallbacks& callbacks, bool isProhibitBack, bool isAsyncModalBinding)
{
    isProhibitBack_ = isProhibitBack;
    auto uiExtNode = ModalUIExtension::Create(want, callbacks, isAsyncModalBinding);
    auto layoutProperty = uiExtNode->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, 0);
    auto full = CalcLength(Dimension(1.0, DimensionUnit::PERCENT));
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(full, full));
    auto buildNodeFunc = [uiExtNode]() -> RefPtr<UINode> {
        uiExtNode->MarkModifyDone();
        return uiExtNode;
    };
    auto sessionId = ModalUIExtension::GetSessionId(uiExtNode);
    if (!isAsyncModalBinding) {
        ModalStyle modalStyle;
        modalStyle.modalTransition = NG::ModalTransition::NONE;
        modalStyle.isUIExtension = true;
        // Convert the sessionId into a negative number to distinguish it from the targetId of other modal pages
        BindContentCover(true, nullptr, std::move(buildNodeFunc), modalStyle, nullptr, nullptr, nullptr, nullptr,
            ContentCoverParam(), nullptr, -(sessionId));
    } else {
        auto bindModalCallback = [weak = WeakClaim(this), buildNodeFunc, sessionId, id = Container::CurrentId()]() {
            ContainerScope scope(id);
            auto overlayManager = weak.Upgrade();
            CHECK_NULL_VOID(overlayManager);
            ModalStyle modalStyle;
            modalStyle.modalTransition = NG::ModalTransition::NONE;
            modalStyle.isUIExtension = true;
            overlayManager->BindContentCover(true, nullptr, std::move(buildNodeFunc), modalStyle, nullptr, nullptr,
                nullptr, nullptr, ContentCoverParam(), nullptr, -(sessionId));
        };
        ModalUIExtension::SetBindModalCallback(uiExtNode, std::move(bindModalCallback));
        uiExtNodes_[sessionId] = WeakClaim(RawPtr(uiExtNode));
    }
    return sessionId;
}

void OverlayManager::CloseModalUIExtension(int32_t sessionId)
{
    auto iter = uiExtNodes_.find(sessionId);
    if (iter != uiExtNodes_.end()) {
        auto uiExtNode = iter->second.Upgrade();
        if (uiExtNode) {
            ModalUIExtension::SetBindModalCallback(uiExtNode, nullptr);
        }
        uiExtNodes_.erase(sessionId);
    }
    ModalStyle modalStyle;
    modalStyle.modalTransition = NG::ModalTransition::NONE;
    BindContentCover(false, nullptr, nullptr, modalStyle, nullptr, nullptr, nullptr, nullptr, ContentCoverParam(),
        nullptr, -(sessionId));
}

RefPtr<FrameNode> OverlayManager::BindUIExtensionToMenu(const RefPtr<FrameNode>& uiExtNode,
    const RefPtr<NG::FrameNode>& targetNode, const std::string& longestContent, int32_t menuSize)
{
    CHECK_NULL_RETURN(uiExtNode, nullptr);
    CHECK_NULL_RETURN(targetNode, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    MenuParam menuParam;
    menuParam.type = MenuType::MENU;
    menuParam.placement = Placement::BOTTOM_LEFT;
    auto menuWrapperNode =
        MenuView::Create(uiExtNode, targetNode->GetId(), targetNode->GetTag(), menuParam, true);
    CHECK_NULL_RETURN(menuWrapperNode, nullptr);
    auto menuNode = DynamicCast<FrameNode>(menuWrapperNode->GetFirstChild());
    CHECK_NULL_RETURN(menuNode, nullptr);
    auto idealSize = CaculateMenuSize(menuNode, longestContent, menuSize);
    auto uiExtLayoutProperty = uiExtNode->GetLayoutProperty();
    CHECK_NULL_RETURN(uiExtLayoutProperty, nullptr);
    uiExtLayoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(idealSize.Width()),  CalcLength(idealSize.Height())));
    auto menuLayoutProperty = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_RETURN(menuLayoutProperty, nullptr);
    menuLayoutProperty->UpdateMargin(MarginProperty());
    menuLayoutProperty->UpdatePadding(PaddingProperty());
    auto scollNode = DynamicCast<FrameNode>(menuNode->GetFirstChild());
    CHECK_NULL_RETURN(scollNode, menuNode);
    auto scollLayoutProperty = scollNode->GetLayoutProperty();
    CHECK_NULL_RETURN(scollLayoutProperty, menuNode);
    scollLayoutProperty->UpdateMargin(MarginProperty());
    scollLayoutProperty->UpdatePadding(PaddingProperty());

    auto destructor = [id = targetNode->GetId()]() {
        auto pipeline = NG::PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto overlayManager = pipeline->GetOverlayManager();
        CHECK_NULL_VOID(overlayManager);
        overlayManager->DeleteMenu(id);
    };
    targetNode->PushDestroyCallback(destructor);
    return menuWrapperNode;
}

SizeF OverlayManager::CaculateMenuSize(
    const RefPtr<FrameNode>& menuNode, const std::string& longestContent, int32_t menuSize)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "caculate menu size enter");
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, SizeF());
    auto textTheme = pipeline->GetTheme<TextTheme>();
    CHECK_NULL_RETURN(textTheme, SizeF());
    TextStyle textStyle = textTheme ? textTheme->GetTextStyle() : TextStyle();
    MeasureContext measureContext;
    measureContext.textContent = longestContent;
    measureContext.fontSize = textStyle.GetFontSize();
    auto fontweight = StringUtils::FontWeightToString(textStyle.GetFontWeight());
    measureContext.fontWeight = fontweight;
    auto fontFamilies = textStyle.GetFontFamilies();
    measureContext.fontFamily = V2::ConvertFontFamily(fontFamilies);
    auto measureSize = MeasureUtil::MeasureTextSize(measureContext);
    auto selectTheme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_RETURN(selectTheme, SizeF());
    auto minItemHeight = static_cast<float>(selectTheme->GetOptionMinHeight().ConvertToPx());
    auto menuItemHeight = std::max(minItemHeight, static_cast<float>(measureSize.Height()));
    auto groupDividerPadding = static_cast<float>(selectTheme->GetDividerPaddingVertical().ConvertToPx()) * 2 +
                           static_cast<float>(selectTheme->GetDefaultDividerWidth().ConvertToPx());
    auto groupHeight = menuItemHeight + groupDividerPadding;

    auto menuLayoutProperty = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_RETURN(menuLayoutProperty, SizeF());
    const auto& padding = menuLayoutProperty->CreatePaddingAndBorder();
    auto middleSpace = static_cast<float>(selectTheme->GetIconContentPadding().ConvertToPx());
    float contentWidth = static_cast<float>(measureSize.Width()) + padding.Width() + middleSpace;

    auto childConstraint = menuLayoutProperty->CreateChildConstraint();
    auto columnInfo = GridSystemManager::GetInstance().GetInfoByType(GridColumnType::MENU);
    CHECK_NULL_RETURN(columnInfo, SizeF());
    CHECK_NULL_RETURN(columnInfo->GetParent(), SizeF());
    columnInfo->GetParent()->BuildColumnWidth();
    auto minWidth = static_cast<float>(columnInfo->GetWidth()) - padding.Width();
    childConstraint.minSize.SetWidth(minWidth);
    auto idealWidth = std::max(contentWidth, childConstraint.minSize.Width());
    auto idealHeight = groupHeight * (menuSize - 1) +
        menuItemHeight + static_cast<float>(selectTheme->GetOutPadding().ConvertToPx()) * 2;
    return SizeF(idealWidth, idealHeight);
}

bool OverlayManager::ShowUIExtensionMenu(const RefPtr<NG::FrameNode>& uiExtNode, const NG::RectF& aiRect,
    const std::string& longestContent, int32_t menuSize, const RefPtr<NG::FrameNode>& targetNode)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "show ui extension menu enter");
    CHECK_NULL_RETURN(uiExtNode, false);
    auto root = rootNodeWeak_.Upgrade();
    CHECK_NULL_RETURN(root, false);
    for (const auto& child : root->GetChildren()) {
        if (child->GetTag() == V2::MENU_WRAPPER_ETS_TAG) {
            return false;
        }
    }
    auto menuWrapperNode = BindUIExtensionToMenu(uiExtNode, targetNode, longestContent, menuSize);
    CHECK_NULL_RETURN(menuWrapperNode, false);
    auto menuNode = DynamicCast<FrameNode>(menuWrapperNode->GetFirstChild());
    CHECK_NULL_RETURN(menuNode, false);
    auto menuLayoutProperty = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_RETURN(menuLayoutProperty, false);
    menuLayoutProperty->UpdateIsRectInTarget(true);
    menuLayoutProperty->UpdateTargetSize(aiRect.GetSize());

    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_RETURN(theme, false);
    auto expandDisplay = theme->GetExpandDisplay();
    if (expandDisplay) {
        MenuParam menuParam {};
        SubwindowManager::GetInstance()->ShowMenuNG(menuWrapperNode, menuParam, targetNode, aiRect.GetOffset());
    } else {
        ShowMenu(targetNode->GetId(), aiRect.GetOffset(), menuWrapperNode);
    }
    return true;
}

void OverlayManager::CloseUIExtensionMenu(const std::function<void(const std::string&)>& onClickMenu, int32_t targetId)
{
    bool isShown = SubwindowManager::GetInstance()->GetShown();
    if (isShown) {
        CleanMenuInSubWindow(targetId);
    } else {
        auto menuNode = GetMenuNode(targetId);
        CHECK_NULL_VOID(menuNode);
        auto menuPattern = menuNode->GetPattern<NG::MenuWrapperPattern>();
        CHECK_NULL_VOID(menuPattern);
        HideMenu(menuNode, targetId);
    }
}

void OverlayManager::CreateOverlayNode()
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "create overlay node enter");
    if (overlayNode_) {
        return;
    }
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_VOID(rootNode);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto stageManager = pipelineContext->GetStageManager();
    CHECK_NULL_VOID(stageManager);
    auto stageNode = stageManager->GetStageNode();
    CHECK_NULL_VOID(stageNode);
    overlayNode_ = FrameNode::CreateFrameNode(V2::OVERLAY_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<OverlayContainerPattern>());
    CHECK_NULL_VOID(overlayNode_);
    overlayNode_->SetHitTestMode(HitTestMode::HTMTRANSPARENT_SELF);
    auto layoutProperty = overlayNode_->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto full = CalcLength(Dimension(1.0, DimensionUnit::PERCENT));
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(full, full));
    rootNode->AddChildAfter(overlayNode_, stageNode);
}

void OverlayManager::AddFrameNodeToOverlay(const RefPtr<NG::FrameNode>& node, std::optional<int32_t> index)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "add FrameNode to the overlay node enter");
    CHECK_NULL_VOID(node);
    int32_t level = -1;
    if (index.has_value() && index.value() >= 0) {
        level = index.value();
    }
    CreateOverlayNode();
    CHECK_NULL_VOID(overlayNode_);
    if (frameNodeMapOnOverlay_.find(node->GetId()) != frameNodeMapOnOverlay_.end()) {
        overlayNode_->RemoveChild(node);
        frameNodeMapOnOverlay_.erase(node->GetId());
    }
    const auto& children = overlayNode_->GetChildren();
    if (level == -1) {
        overlayNode_->AddChild(node);
    } else if (children.empty() || frameNodeMapOnOverlay_[overlayNode_->GetFirstChild()->GetId()] == -1 ||
               level < frameNodeMapOnOverlay_[overlayNode_->GetFirstChild()->GetId()]) {
        overlayNode_->AddChild(node, 0);
    } else {
        for (auto it = children.rbegin(); it != children.rend(); ++it) {
            auto childLevel = frameNodeMapOnOverlay_[(*it)->GetId()];
            if (childLevel < 0) {
                continue;
            }
            if (childLevel <= level) {
                auto beforeNode = DynamicCast<FrameNode>(*it);
                CHECK_NULL_VOID(beforeNode);
                overlayNode_->AddChildAfter(node, beforeNode);
                break;
            }
        }
    }
    overlayNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    frameNodeMapOnOverlay_[node->GetId()] = level;
    auto focusHub = node->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->RequestFocus();
}

void OverlayManager::RemoveFrameNodeOnOverlay(const RefPtr<NG::FrameNode>& node)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "delete the FrameNode on the overlay node enter");
    CHECK_NULL_VOID(node);
    if (frameNodeMapOnOverlay_.find(node->GetId()) == frameNodeMapOnOverlay_.end()) {
        TAG_LOGW(AceLogTag::ACE_OVERLAY, "the node does not exist in the overlay");
        return;
    }
    CHECK_NULL_VOID(overlayNode_);
    overlayNode_->RemoveChild(node);
    frameNodeMapOnOverlay_.erase(node->GetId());
    if (overlayNode_->GetChildren().empty()) {
        auto rootNode = rootNodeWeak_.Upgrade();
        CHECK_NULL_VOID(rootNode);
        rootNode->RemoveChild(overlayNode_);
        overlayNode_.Reset();
        frameNodeMapOnOverlay_.clear();
        rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
        return;
    }
    overlayNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
}

void OverlayManager::ShowNodeOnOverlay(const RefPtr<NG::FrameNode>& node)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "show the FrameNode on the overlay node enter");
    CHECK_NULL_VOID(node);
    CHECK_NULL_VOID(overlayNode_);
    auto layoutProperty = node->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    if (layoutProperty->GetVisibility().has_value() && layoutProperty->GetVisibilityValue() == VisibleType::VISIBLE) {
        return;
    }
    layoutProperty->UpdateVisibility(VisibleType::VISIBLE);
    node->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    auto focusHub = node->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->RequestFocus();
}

void OverlayManager::HideNodeOnOverlay(const RefPtr<NG::FrameNode>& node)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "hide the FrameNode on the overlay node enter");
    CHECK_NULL_VOID(node);
    CHECK_NULL_VOID(overlayNode_);
    auto layoutProperty = node->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    if (layoutProperty->GetVisibility().has_value() && layoutProperty->GetVisibilityValue() == VisibleType::GONE) {
        return;
    }
    layoutProperty->UpdateVisibility(VisibleType::GONE);
    node->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    auto focusHub = node->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->LostFocusToViewRoot();
}

void OverlayManager::ShowAllNodesOnOverlay()
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "show all FrameNodes on the overlay node enter");
    CHECK_NULL_VOID(overlayNode_);
    for (auto& child : overlayNode_->GetChildren()) {
        auto frameNode = DynamicCast<FrameNode>(child);
        CHECK_NULL_VOID(frameNode);
        auto layoutProperty = frameNode->GetLayoutProperty();
        CHECK_NULL_VOID(layoutProperty);
        layoutProperty->UpdateVisibility(VisibleType::VISIBLE);
    }
    overlayNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    auto focusView = overlayNode_->GetPattern<FocusView>();
    CHECK_NULL_VOID(focusView);
    focusView->FocusViewShow();
}

void OverlayManager::HideAllNodesOnOverlay()
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "hide all FrameNodes on the overlay node enter");
    CHECK_NULL_VOID(overlayNode_);
    for (auto& child : overlayNode_->GetChildren()) {
        auto frameNode = DynamicCast<FrameNode>(child);
        CHECK_NULL_VOID(frameNode);
        auto layoutProperty = frameNode->GetLayoutProperty();
        CHECK_NULL_VOID(layoutProperty);
        layoutProperty->UpdateVisibility(VisibleType::GONE);
    }
    overlayNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    auto focusView = overlayNode_->GetPattern<FocusView>();
    CHECK_NULL_VOID(focusView);
    focusView->FocusViewClose();
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
            // sheetPage Node will MarkDirty when VirtualKeyboard Height Changes
            auto sheetParent = DynamicCast<FrameNode>(child);
            if (sheetParent && sheetParent->GetTag() == V2::SHEET_WRAPPER_TAG) {
                auto sheet = sheetParent->GetChildAtIndex(0);
                if (sheet) {
                    sheet->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
                }
            }
        }
    }
}

void OverlayManager::MarkDirtyOverlay()
{
    auto root = rootNodeWeak_.Upgrade();
    CHECK_NULL_VOID(root);
    auto child = root->GetLastChild();
    CHECK_NULL_VOID(child);
    // sheetPage Node will MarkDirty when VirtualKeyboard Height Changes
    auto sheetParent = DynamicCast<FrameNode>(child);
    if (sheetParent && sheetParent->GetTag() == V2::SHEET_WRAPPER_TAG) {
        auto sheet = sheetParent->GetChildAtIndex(0);
        if (sheet) {
            sheet->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        }
    }
}

bool OverlayManager::CheckPageNeedAvoidKeyboard() const
{
    auto root = rootNodeWeak_.Upgrade();
    CHECK_NULL_RETURN(root, true);
    auto child = root->GetLastChild();
    CHECK_NULL_RETURN(child, true);
    // page will not avoid keyboard when lastChild is sheet
    if (child->GetTag() != V2::SHEET_WRAPPER_TAG) {
        return true;
    }
    auto frameNode = DynamicCast<FrameNode>(child);
    return !(frameNode && frameNode->GetFocusHub() && frameNode->GetFocusHub()->IsCurrentFocus());
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

void OverlayManager::CheckReturnFocus(RefPtr<FrameNode> node) {}

bool OverlayManager::isMaskNode(int32_t maskId)
{
    for (auto it = maskNodeIdMap_.begin(); it != maskNodeIdMap_.end(); it++) {
        if (it->second == maskId) {
            return true;
        }
    }
    return false;
}

int32_t OverlayManager::GetMaskNodeIdWithDialogId(int32_t dialogId)
{
    int32_t maskNodeId = -1;
    for (auto it = maskNodeIdMap_.begin(); it != maskNodeIdMap_.end(); it++) {
        if (it->first == dialogId) {
            maskNodeId = it->second;
            break;
        }
    }
    return maskNodeId;
}

void OverlayManager::MountGatherNodeToRootNode(const RefPtr<FrameNode>& frameNode,
    std::vector<GatherNodeChildInfo>& gatherNodeChildrenInfo)
{
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_VOID(rootNode);
    frameNode->MountToParent(rootNode);
    frameNode->OnMountToParentDone();
    rootNode->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
    gatherNodeWeak_ = frameNode;
    hasGatherNode_ = true;
    gatherNodeChildrenInfo_ = gatherNodeChildrenInfo;
}

void OverlayManager::MountGatherNodeToWindowScene(const RefPtr<FrameNode>& frameNode,
    std::vector<GatherNodeChildInfo>& gatherNodeChildrenInfo, const RefPtr<UINode>& windowScene)
{
    CHECK_NULL_VOID(windowScene);
    frameNode->MountToParent(windowScene);
    frameNode->OnMountToParentDone();
    windowScene->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
    gatherNodeWeak_ = frameNode;
    hasGatherNode_ = true;
    gatherNodeChildrenInfo_ = gatherNodeChildrenInfo;
}

void OverlayManager::RemoveGatherNode()
{
    if (!hasGatherNode_) {
        return;
    }
    auto frameNode = gatherNodeWeak_.Upgrade();
    CHECK_NULL_VOID(frameNode);
    auto rootNode = frameNode->GetParent();
    CHECK_NULL_VOID(rootNode);
    rootNode->RemoveChild(frameNode);
    rootNode->RebuildRenderContextTree();
    rootNode->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
    hasGatherNode_ = false;
    gatherNodeWeak_ = nullptr;
    gatherNodeChildrenInfo_.clear();
}

void OverlayManager::RemoveGatherNodeWithAnimation()
{
    if (!hasGatherNode_) {
        return;
    }
    AnimationOption option;
    option.SetDuration(PIXELMAP_ANIMATION_DURATION);
    option.SetCurve(Curves::SHARP);

    option.SetOnFinishEvent([weak = gatherNodeWeak_] {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto rootNode = frameNode->GetParent();
        CHECK_NULL_VOID(rootNode);
        rootNode->RemoveChild(frameNode);
        rootNode->RebuildRenderContextTree();
        rootNode->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
    });
    gatherNodeWeak_ = nullptr;
    hasGatherNode_ = false;
    AnimationUtils::Animate(
        option,
        [gatherNodeChildrenInfo = gatherNodeChildrenInfo_]() mutable {
            for (const auto& child : gatherNodeChildrenInfo) {
                auto imageNode = child.imageNode.Upgrade();
                CHECK_NULL_VOID(imageNode);
                auto imageContext = imageNode->GetRenderContext();
                CHECK_NULL_VOID(imageContext);
                imageContext->UpdatePosition(OffsetT<Dimension>(Dimension(child.offset.GetX()),
                    Dimension(child.offset.GetY())));
                imageContext->UpdateTransformScale({ 1.0f, 1.0f });
                Vector5F rotate = Vector5F(0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
                imageContext->UpdateTransformRotate(rotate);
                imageContext->UpdateOpacity(1.0);
                BorderRadiusProperty borderRadius;
                borderRadius.SetRadius(0.0_vp);
                imageContext->UpdateBorderRadius(borderRadius);
            }
        },
        option.GetOnFinishEvent());
}

RefPtr<FrameNode> OverlayManager::GetPixelMapContentNode() const
{
    auto column = pixmapColumnNodeWeak_.Upgrade();
    CHECK_NULL_RETURN(column, nullptr);
    auto imageNode = AceType::DynamicCast<FrameNode>(column->GetFirstChild());
    return imageNode;
}

RefPtr<FrameNode> OverlayManager::GetPixelMapBadgeNode() const
{
    auto column = pixmapColumnNodeWeak_.Upgrade();
    CHECK_NULL_RETURN(column, nullptr);
    auto textNode = AceType::DynamicCast<FrameNode>(column->GetLastChild());
    CHECK_NULL_RETURN(textNode, nullptr);
    return textNode;
}

void OverlayManager::RemoveMenuBadgeNode(const RefPtr<FrameNode>& menuWrapperNode)
{
    CHECK_NULL_VOID(menuWrapperNode);
    auto pattern = menuWrapperNode->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(pattern);
    auto badgeNode = pattern->GetBadgeNode();
    CHECK_NULL_VOID(badgeNode);
    menuWrapperNode->RemoveChild(badgeNode);
    menuWrapperNode->RebuildRenderContextTree();
    menuWrapperNode->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
}

void OverlayManager::RemovePreviewBadgeNode()
{
    auto columnNode = pixmapColumnNodeWeak_.Upgrade();
    CHECK_NULL_VOID(columnNode);
    auto textNode = AceType::DynamicCast<FrameNode>(columnNode->GetChildAtIndex(1));
    CHECK_NULL_VOID(textNode);
    columnNode->RemoveChild(textNode);
    columnNode->RebuildRenderContextTree();
    columnNode->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
}

const WeakPtr<UINode>& OverlayManager::GetRootNode() const
{
    return rootNodeWeak_;
}

const RefPtr<GroupManager>& OverlayManager::GetGroupManager() const
{
    return groupManager_;
}

void OverlayManager::ShowFilterAnimation(const RefPtr<FrameNode>& columnNode)
{
    CHECK_NULL_VOID(columnNode);

    auto filterRenderContext = columnNode->GetRenderContext();
    CHECK_NULL_VOID(filterRenderContext);

    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto menuTheme = pipelineContext->GetTheme<NG::MenuTheme>();
    CHECK_NULL_VOID(menuTheme);

    auto maskColor = menuTheme->GetPreviewMenuMaskColor();
    BlurStyleOption styleOption;
    styleOption.blurStyle = BlurStyle::BACKGROUND_THIN;
    styleOption.colorMode = ThemeColorMode::SYSTEM;

    AnimationOption option;
    option.SetDuration(menuTheme->GetFilterAnimationDuration());
    option.SetCurve(Curves::SHARP);
    option.SetOnFinishEvent([] {
        auto pipelineContext = PipelineContext::GetCurrentContext();
        auto manager = pipelineContext->GetOverlayManager();
        CHECK_NULL_VOID(manager);
        manager->SetFilterActive(false);
    });
    filterRenderContext->UpdateBackBlurRadius(Dimension(0.0f));
    AnimationUtils::Animate(
        option,
        [filterRenderContext, styleOption, maskColor]() {
            CHECK_NULL_VOID(filterRenderContext);
            if (SystemProperties::GetDeviceType() == DeviceType::PHONE) {
                filterRenderContext->UpdateBackBlurStyle(styleOption);
            } else {
                filterRenderContext->UpdateBackgroundColor(maskColor);
            }
        },
        option.GetOnFinishEvent());
}

void OverlayManager::RemoveMenuNotInSubWindow(
    const WeakPtr<FrameNode>& menuWK, const WeakPtr<UINode>& rootWeak, const WeakPtr<OverlayManager>& overlayWeak)
{
    auto menu = menuWK.Upgrade();
    CHECK_NULL_VOID(menu);
    auto rootNode = rootWeak.Upgrade();
    CHECK_NULL_VOID(rootNode);
    auto overlayManager = overlayWeak.Upgrade();
    CHECK_NULL_VOID(overlayManager);

    auto container = Container::Current();
    if (container && container->IsScenceBoardWindow()) {
        rootNode = overlayManager->FindWindowScene(menu);
    }
    CHECK_NULL_VOID(rootNode);
    rootNode->RemoveChild(menu);
    rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}
} // namespace OHOS::Ace::NG
