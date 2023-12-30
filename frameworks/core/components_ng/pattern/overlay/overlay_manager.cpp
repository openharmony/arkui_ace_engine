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
#include <vector>

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
#include "core/components_ng/pattern/video/video_full_screen_pattern.h"
#include "core/components_ng/property/measure_property.h"
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

constexpr float PIXELMAP_DRAG_SCALE = 1.0f;
constexpr int32_t PIXELMAP_ANIMATION_DURATION = 250;
constexpr float PIXELMAP_ANIMATION_DEFAULT_LIMIT_SCALE = 0.5f;

constexpr int32_t FULL_MODAL_ALPHA_ANIMATION_DURATION = 200;

constexpr int32_t SHEET_HALF_SIZE = 2;
// dialog animation params
const RefPtr<Curve> SHOW_SCALE_ANIMATION_CURVE = AceType::MakeRefPtr<CubicCurve>(0.38f, 1.33f, 0.6f, 1.0f);

// custom keyboard animation params
const RefPtr<Curve> SHOW_CUSTOM_KEYBOARD_ANIMATION_CURVE =
    AceType::MakeRefPtr<InterpolatingSpring>(0.0f, 1.0f, 342.0f, 37.0f);
const RefPtr<Curve> HIDE_CUSTOM_KEYBOARD_ANIMATION_CURVE =
    AceType::MakeRefPtr<InterpolatingSpring>(4.0f, 1.0f, 342.0f, 37.0f);

const std::map<TextDataDetectType, std::string> TEXT_DETECT_MAP = {
    {TextDataDetectType::PHONE_NUMBER, "phoneNum"}, {TextDataDetectType::URL, "url"},
    {TextDataDetectType::EMAIL, "email"}, {TextDataDetectType::ADDRESS, "location"} };

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
        TaskExecutor::TaskType::UI);
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

void OverlayManager::SetContainerButtonEnable(bool isEnabled)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetCloseButtonStatus(isEnabled);
}

void OverlayManager::SetShowMenuAnimation(const RefPtr<FrameNode>& menu, bool isInSubWindow)
{
    BlurLowerNode(menu);
    auto menuWrapper = menu->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(menuWrapper);
    menuWrapper->CallMenuAboutToAppearCallback();
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
                    auto menuWrapperPattern = menu->GetPattern<MenuWrapperPattern>();
                    menuWrapperPattern->CallMenuAppearCallback();
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

void OverlayManager::PopMenuAnimation(const RefPtr<FrameNode>& menu, bool showPreviewAnimation, bool startDrag)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "pop menu animation enter");
    ResetLowerNodeFocusable(menu);
    ResetContextMenuDragHideFinished();

    auto menuWrapper = menu->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(menuWrapper);
    menuWrapper->CallMenuAboutToDisappearCallback();
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
                CHECK_NULL_VOID(menu);
                auto menuNode = AceType::DynamicCast<FrameNode>(menu->GetChildAtIndex(0));
                CHECK_NULL_VOID(menuNode);
                auto menuPattern = menuNode->GetPattern<MenuPattern>();
                CHECK_NULL_VOID(menuPattern);
                auto root = rootWeak.Upgrade();
                auto overlayManager = weak.Upgrade();
                CHECK_NULL_VOID(overlayManager);
                overlayManager->SetContextMenuDragHideFinished(true);
                auto menuWrapperPattern = menu->GetPattern<MenuWrapperPattern>();
                menuWrapperPattern->CallMenuDisappearCallback();
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
                if (((menuWrapperPattern && menuWrapperPattern->IsContextMenu()) || expandDisplay) &&
                    (menuPattern->GetTargetTag() != V2::SELECT_ETS_TAG)) {
                    SubwindowManager::GetInstance()->ClearMenuNG(id);
                    overlayManager->ResetContextMenuDragHideFinished();
                    return;
                }
                ContainerScope scope(id);
                auto container = Container::Current();
                if (container && container->IsScenceBoardWindow()) {
                    root = overlayManager->FindWindowScene(menu);
                }
                CHECK_NULL_VOID(root);
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
        ShowContextMenuDisappearAnimation(option, menuWrapperPattern, startDrag);
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

void OverlayManager::ClearMenuAnimation(const RefPtr<FrameNode>& menu, bool showPreviewAnimation, bool startDrag)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "clear menu animation enter");
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
                auto menuWrapperPattern = menu->GetPattern<MenuWrapperPattern>();
                // clear contextMenu then return
                if ((menuWrapperPattern && menuWrapperPattern->IsContextMenu())) {
                    return;
                }
                overlayManager->BlurOverlayNode(menu);
                root->RemoveChild(menu);
                root->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
            },
            TaskExecutor::TaskType::UI);
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
            },
            TaskExecutor::TaskType::UI);
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
    toastMap_.clear();
}

void OverlayManager::ShowPopup(int32_t targetId, const PopupInfo& popupInfo)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "show popup enter");
    popupMap_[targetId] = popupInfo;
    if (!popupInfo.markNeedUpdate) {
        TAG_LOGW(AceLogTag::ACE_OVERLAY, "mark need update failed");
        return;
    }
    popupMap_[targetId].markNeedUpdate = false;
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
    if (iter != rootChildren.rend()) {
        return;
    }

    // attach popupNode before entering animation
    popupNode->GetEventHub<BubbleEventHub>()->FireChangeEvent(true);
    popupNode->MountToParent(rootNode);
    rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    popupMap_[targetId].isCurrentOnShow = true;

    auto popupPattern = popupNode->GetPattern<BubblePattern>();
    CHECK_NULL_VOID(popupPattern);
    if ((isTypeWithOption && !isShowInSubWindow) ||
        (!Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN) && isUseCustom)) {
        BlurLowerNode(popupNode);
        auto onFinish = [popupNodeWk = WeakPtr<FrameNode>(popupNode), weak = WeakClaim(this)]() {
            auto overlayManager = weak.Upgrade();
            auto popupNode = popupNodeWk.Upgrade();
            CHECK_NULL_VOID(overlayManager && popupNode);
            overlayManager->FocusOverlayNode(popupNode);
        };
        popupPattern->StartEnteringAnimation(onFinish);
    } else {
        popupPattern->StartEnteringAnimation(nullptr);
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
        (!Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN) && isUseCustom)) {
        ResetLowerNodeFocusable(popupNode);
    }
    // detach popupNode after exiting animation
    popupMap_[targetId].isCurrentOnShow = false;
    popupPattern->StartExitingAnimation(
        [isShowInSubWindow, isTypeWithOption, isUseCustom, popupNodeWk = WeakPtr<FrameNode>(popupNode),
            rootNodeWk = WeakPtr<UINode>(rootNode), weak = WeakClaim(this)]() {
            auto rootNode = rootNodeWk.Upgrade();
            auto popupNode = popupNodeWk.Upgrade();
            auto overlayManager = weak.Upgrade();
            CHECK_NULL_VOID(rootNode && popupNode && overlayManager);

            auto popupPattern = popupNode->GetPattern<BubblePattern>();
            CHECK_NULL_VOID(popupPattern);
            popupPattern->SetTransitionStatus(TransitionStatus::INVISIABLE);
            popupNode->GetEventHub<BubbleEventHub>()->FireChangeEvent(false);
            rootNode->RemoveChild(popupNode);
            rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
            if ((isTypeWithOption && !isShowInSubWindow) ||
                (!Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN) && isUseCustom)) {
                overlayManager->BlurOverlayNode(popupNode);
            }
            if (isShowInSubWindow) {
                auto subwindow = SubwindowManager::GetInstance();
                CHECK_NULL_VOID(subwindow);
                subwindow->HideSubWindowNG();
            }
        });
    popupNode->OnAccessibilityEvent(
        AccessibilityEventType::CHANGE, WindowsContentChangeTypes::CONTENT_CHANGE_TYPE_SUBTREE);
    RemoveEventColumn();
    RemovePixelMapAnimation(false, 0, 0);
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
    if (popupMap_.find(targetId) != popupMap_.end()) {
        auto rootNode = rootNodeWeak_.Upgrade();
        CHECK_NULL_VOID(rootNode);
        rootNode->RemoveChild(popupMap_[targetId].popupNode);
        rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        popupMap_.erase(targetId);
    }
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
        SetShowMenuAnimation(menu);
        menu->MarkModifyDone();
    }
    menu->OnAccessibilityEvent(AccessibilityEventType::CHANGE, WindowsContentChangeTypes::CONTENT_CHANGE_TYPE_SUBTREE);
    auto pattern = menu->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetShow(true);
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
    rootNode->Clean();
    menu->MountToParent(rootNode);
    SetShowMenuAnimation(menu, true);
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
        PopMenuAnimation(node, showPreviewAnimation, startDrag);
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
    auto pattern = menu->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetShow(false);
    PopMenuAnimation(menu);
    menu->OnAccessibilityEvent(AccessibilityEventType::CHANGE, WindowsContentChangeTypes::CONTENT_CHANGE_TYPE_SUBTREE);
    RemoveEventColumn();
    if (isMenuOnTouch) {
        RemovePixelMap();
    } else {
        RemovePixelMapAnimation(false, 0, 0);
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
    HideAllMenus();
    HideMenuInSubWindow(false);
    menuMap_.erase(it);
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
    auto menuWrapperPattern = menu->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(menuWrapperPattern);
    menuWrapperPattern->SetMenuHide();
    if (menuWrapperPattern->GetPreviewMode() == MenuPreviewMode::NONE) {
        CleanMenuInSubWindow();
        menuWrapperPattern->CallMenuDisappearCallback();
        auto mainPipeline = PipelineContext::GetMainPipelineContext();
        if (mainPipeline && menuWrapperPattern->GetMenuDisappearCallback()) {
            mainPipeline->FlushPipelineImmediately();
        }
        return;
    }
    ClearMenuAnimation(menu);
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

void OverlayManager::CleanMenuInSubWindow()
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "clean menu insubwindow enter");
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
    OpenDialogAnimation(dialog);
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

void OverlayManager::OpenCustomDialog(const DialogProperties& dialogProps, std::function<void(int32_t)> &&callback)
{
    RefPtr<UINode> customNode;
    if (dialogProps.customBuilder) {
        NG::ScopedViewStackProcessor builderViewStackProcessor;
        dialogProps.customBuilder();
        customNode = NG::ViewStackProcessor::GetInstance()->Finish();
        CHECK_NULL_VOID(customNode);
    }
    auto dialog = DialogView::CreateDialogNode(dialogProps, customNode);
    CHECK_NULL_VOID(dialog);

    BeforeShowDialog(dialog);

    // callback dialogId
    if (callback) {
        callback(dialog->GetId());
    }

    OpenDialogAnimation(dialog);
    dialogCount_++;

    if (Recorder::EventRecorder::Get().IsComponentRecordEnable()) {
        Recorder::EventParamsBuilder builder;
        builder
            .SetType("Dialog")
            .SetEventType(Recorder::EventType::DIALOG_SHOW)
            .SetExtra(Recorder::KEY_TITLE, dialogProps.title)
            .SetExtra(Recorder::KEY_SUB_TITLE, dialogProps.subtitle);
        Recorder::EventRecorder::Get().OnEvent(std::move(builder));
    }
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
        CloseDialogInner(tmpDialog);
    }
    return;
}

void OverlayManager::ShowCustomDialog(const RefPtr<FrameNode>& customNode)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "show custom dialog enter");
    BeforeShowDialog(customNode);
    OpenDialogAnimation(customNode);
}

void OverlayManager::ShowDateDialog(const DialogProperties& dialogProps, const DatePickerSettingData& settingData,
    std::map<std::string, NG::DialogEvent> dialogEvent, std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "show date dialog enter");
    auto dialogNode = DatePickerDialogView::Show(
        dialogProps, std::move(settingData), std::move(dialogEvent), std::move(dialogCancelEvent));
    BeforeShowDialog(dialogNode);
    OpenDialogAnimation(dialogNode);
}

void OverlayManager::ShowTimeDialog(const DialogProperties& dialogProps, const TimePickerSettingData& settingData,
    std::map<std::string, PickerTime> timePickerProperty, std::map<std::string, NG::DialogEvent> dialogEvent,
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "show time dialog enter");
    auto dialogNode = TimePickerDialogView::Show(
        dialogProps, settingData, std::move(timePickerProperty), std::move(dialogEvent), std::move(dialogCancelEvent));
    BeforeShowDialog(dialogNode);
    OpenDialogAnimation(dialogNode);
}

void OverlayManager::ShowTextDialog(const DialogProperties& dialogProps, const TextPickerSettingData& settingData,
    std::map<std::string, NG::DialogTextEvent> dialogEvent,
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "show text dialog enter");
    auto dialogNode =
        TextPickerDialogView::Show(dialogProps, settingData, std::move(dialogEvent), std::move(dialogCancelEvent));
    BeforeShowDialog(dialogNode);
    OpenDialogAnimation(dialogNode);
    if (Recorder::EventRecorder::Get().IsComponentRecordEnable()) {
        Recorder::EventParamsBuilder builder;
        builder.SetType("TextPickerDialog").SetEventType(Recorder::EventType::DIALOG_SHOW);
        Recorder::EventRecorder::Get().OnEvent(std::move(builder));
    }
}

void OverlayManager::ShowCalendarDialog(const DialogProperties& dialogProps, const CalendarSettingData& settingData,
    std::map<std::string, NG::DialogEvent> dialogEvent, std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "show calendar dialog enter");
    auto dialogNode =
        CalendarDialogView::Show(dialogProps, settingData, std::move(dialogEvent), std::move(dialogCancelEvent));
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
    auto dialogLayoutProp = AceType::DynamicCast<DialogLayoutProperty>(dialogNode->GetLayoutProperty());
    CHECK_NULL_VOID(dialogLayoutProp);
    if (dialogLayoutProp->GetShowInSubWindowValue(false) && dialogLayoutProp->GetIsModal().value_or(true)) {
        auto parentPipelineContext = PipelineContext::GetMainPipelineContext();
        CHECK_NULL_VOID(parentPipelineContext);
        auto parentOverlayManager = parentPipelineContext->GetOverlayManager();
        CHECK_NULL_VOID(parentOverlayManager);
        RefPtr<FrameNode> maskNode =
            parentOverlayManager->GetDialog(parentOverlayManager->GetMaskNodeIdWithDialogId(dialogNode->GetId()));
        if (maskNode) {
            parentOverlayManager->CloseDialog(maskNode);
        }
    }
    CloseDialogInner(dialogNode);
}

void OverlayManager::CloseDialogInner(const RefPtr<FrameNode>& dialogNode)
{
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

bool OverlayManager::RemoveBubble(const RefPtr<FrameNode>& overlay)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "remove bubble enter");
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
        if (InstanceOf<ToastPattern>(pattern)) {
            // still have nodes on root expect stage and toast node.
            if (rootNode->GetChildren().size() > 2) {
                // If the current node is a toast, the last second overlay's node should be processed.
                overlay = DynamicCast<FrameNode>(rootNode->GetChildAtIndex(rootNode->GetChildren().size() - 2));
                CHECK_NULL_RETURN(overlay, false);
                pattern = overlay->GetPattern();
            } else {
                return false;
            }
        }
        if (InstanceOf<DialogPattern>(pattern)) {
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
        return true;
    }
    return false;
}

bool OverlayManager::RemoveModalInOverlay()
{
    auto topModalNode = modalStack_.top().Upgrade();
    CHECK_NULL_RETURN(topModalNode, false);
    if (topModalNode->GetTag() == V2::SHEET_PAGE_TAG) {
        auto sheetPattern = topModalNode->GetPattern<SheetPresentationPattern>();
        CHECK_NULL_RETURN(sheetPattern, false);
        if (sheetPattern->hasShouldDismiss()) {
            sheetPattern->CallShouldDismiss();
            return true;
        }
    }

    auto rootNode = FindWindowScene(topModalNode);
    CHECK_NULL_RETURN(rootNode, true);

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
    if (!modalStack_.empty()) {
        modalStack_.pop();
    }
    if (!modalList_.empty()) {
        modalList_.pop_back();
    }
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
            FireNavigationStateChange(rootNode, true);
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
                FireNavigationStateChange(rootNode, true);
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
        auto builder = AceType::DynamicCast<FrameNode>(topModalNode->GetFirstChild());
        CHECK_NULL_RETURN(builder, false);
        auto modalTransition = topModalNode->GetPattern<ModalPresentationPattern>()->GetType();
        if (builder->GetRenderContext()->HasDisappearTransition()) {
            if (!topModalNode->GetPattern<ModalPresentationPattern>()->IsExecuteOnDisappear()) {
                topModalNode->GetPattern<ModalPresentationPattern>()->OnDisappear();
                // Fire hidden event of navdestination on the disappeared modal
                FireNavigationStateChange(rootNode, false, topModalNode);
            }
            topModalNode->Clean(false, true);
            topModalNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        }
        if (modalTransition == ModalTransition::DEFAULT) {
            PlayDefaultModalTransition(topModalNode, false);
        } else if (modalTransition == ModalTransition::ALPHA) {
            PlayAlphaModalTransition(topModalNode, false);
        } else if (!builder->GetRenderContext()->HasDisappearTransition()) {
            topModalNode->GetPattern<ModalPresentationPattern>()->OnDisappear();
            // Fire hidden event of navdestination on the disappeared modal
            FireNavigationStateChange(rootNode, false, topModalNode);
            rootNode->RemoveChild(topModalNode);
            rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        }
        topModalNode->GetPattern<ModalPresentationPattern>()->FireCallback("false");
    } else if (topModalNode->GetTag() == V2::SHEET_PAGE_TAG) {
        auto builder = AceType::DynamicCast<FrameNode>(topModalNode->GetLastChild());
        CHECK_NULL_RETURN(builder, false);
        if (builder->GetRenderContext()->HasDisappearTransition()) {
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
        auto sheetType = topModalNode->GetPattern<SheetPresentationPattern>()->GetSheetType();
        if (sheetType == SheetType::SHEET_POPUP) {
            PlayBubbleStyleSheetTransition(topModalNode, false);
        } else {
            PlaySheetTransition(topModalNode, false);
        }
        topModalNode->GetPattern<SheetPresentationPattern>()->FireCallback("false");
    }
    return true;
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
    return true;
}

void OverlayManager::FocusOverlayNode(const RefPtr<FrameNode>& overlayNode, bool isInSubWindow)
{
    CHECK_NULL_VOID(overlayNode);
    auto focusHub = overlayNode->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->SetParentFocusable(true);
    focusHub->RequestFocusWithDefaultFocusFirstly();
}

void OverlayManager::BlurOverlayNode(const RefPtr<FrameNode>& currentOverlay, bool isInSubWindow)
{
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
                (InstanceOf<DialogPattern>(pattern) || InstanceOf<MenuWrapperPattern>(pattern) ||
                    InstanceOf<SheetPresentationPattern>(pattern) || InstanceOf<ModalPresentationPattern>(pattern)) &&
                !overlay->IsRemoving()) {
                // Focus returns to the previous in the overlay
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
            auto parent = node->GetParent();
            if (parent && parent->GetTag() != V2::PAGE_ETS_TAG) {
                return;
            }
            auto pageNode = GetLastPage();
            CHECK_NULL_VOID(pageNode);
            auto pageFocusHub = pageNode->GetFocusHub();
            CHECK_NULL_VOID(pageFocusHub);
            pageFocusHub->SetParentFocusable(true);
            return;
        }
        if (node->GetTag() == V2::ATOMIC_SERVICE_ETS_TAG) {
            auto serviceFocusHub = node->GetFocusHub();
            CHECK_NULL_VOID(serviceFocusHub);
            serviceFocusHub->SetParentFocusable(true);
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

void OverlayManager::FireNavigationStateChange(const RefPtr<UINode>& root, bool show, const RefPtr<UINode>& node)
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

    const auto& children = root->GetChildren();
    for (auto iter = children.begin(); iter != children.end(); ++iter) {
        auto& child = *iter;
        if (!show && child == topModalNode) {
            // Do not check top modal if firing hidden event
            continue;
        }
        NavigationPattern::FireNavigationStateChange(child, show);
    }
}

RefPtr<FrameNode> OverlayManager::GetModalNodeInStack(std::stack<WeakPtr<FrameNode>>& stack)
{
    if (stack.empty()) {
        return nullptr;
    }
    auto topModalNode = stack.top().Upgrade();
    if (topModalNode->GetTag() == V2::MODAL_PAGE_TAG) {
        return topModalNode;
    } else {
        stack.pop();
        auto modalNode = GetModalNodeInStack(stack);
        stack.push(topModalNode);
        return modalNode;
    }
}

void OverlayManager::BindContentCover(bool isShow, std::function<void(const std::string&)>&& callback,
    std::function<RefPtr<UINode>()>&& buildNodeFunc, NG::ModalStyle& modalStyle, std::function<void()>&& onAppear,
    std::function<void()>&& onDisappear, const RefPtr<FrameNode>& targetNode, int32_t sessionId)
{
    int32_t targetId = targetNode ? targetNode->GetId() : sessionId;
    auto rootNode = FindWindowScene(targetNode);
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
        auto modalPagePattern = modalNode->GetPattern<ModalPresentationPattern>();
        CHECK_NULL_VOID(modalPagePattern);
        modalPagePattern->UpdateOnDisappear(std::move(onDisappear));
        modalPagePattern->UpdateUIExtensionMode(modalStyle.isUIExtension);
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
        // Fire hidden event of navdestination under the appeared modal
        FireNavigationStateChange(rootNode, false);
        if (modalTransition == ModalTransition::DEFAULT) {
            PlayDefaultModalTransition(modalNode, true);
        } else if (modalTransition == ModalTransition::ALPHA) {
            PlayAlphaModalTransition(modalNode, true);
        }
        return;
    }

    // isShow = false, Pop ModalPage
    if (!modalStack_.empty()) {
        auto topModalNode = modalStack_.top().Upgrade();
        CHECK_NULL_VOID(topModalNode);
        if (topModalNode->GetTag() != V2::SHEET_PAGE_TAG && topModalNode->GetTag() != V2::MODAL_PAGE_TAG) {
            return;
        }
        if (topModalNode->GetTag() == V2::SHEET_PAGE_TAG ||
            topModalNode->GetPattern<ModalPresentationPattern>()->GetTargetId() != targetId) {
            DeleteModal(targetId);
            return;
        }
        auto builder = AceType::DynamicCast<FrameNode>(topModalNode->GetFirstChild());
        CHECK_NULL_VOID(builder);
        if (builder->GetRenderContext()->HasDisappearTransition()) {
            if (!topModalNode->GetPattern<ModalPresentationPattern>()->IsExecuteOnDisappear()) {
                topModalNode->GetPattern<ModalPresentationPattern>()->OnDisappear();
                // Fire hidden event of navdestination on the disappeared modal
                FireNavigationStateChange(rootNode, false, topModalNode);
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
        } else if (!builder->GetRenderContext()->HasDisappearTransition()) {
            if (!modalPresentationPattern->IsExecuteOnDisappear()) {
                modalPresentationPattern->OnDisappear();
                // Fire hidden event of navdestination on the disappeared modal
                FireNavigationStateChange(rootNode, false, topModalNode);
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
            FireNavigationStateChange(rootNode, true);
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
            [rootWeak = rootNodeWeak_, modalWK = WeakClaim(RawPtr(modalNode)), overlayWeak = WeakClaim(this),
                    id = Container::CurrentId()] {
                ContainerScope scope(id);
                auto context = PipelineContext::GetCurrentContext();
                CHECK_NULL_VOID(context);
                auto taskExecutor = context->GetTaskExecutor();
                CHECK_NULL_VOID(taskExecutor);
                // animation finish event should be posted to UI thread.
                taskExecutor->PostTask(
                    [rootWeak, modalWK, overlayWeak, id]() {
                        auto modal = modalWK.Upgrade();
                        auto overlayManager = overlayWeak.Upgrade();
                        CHECK_NULL_VOID(modal && overlayManager);
                        ContainerScope scope(id);
                        auto root = overlayManager->FindWindowScene(modal);
                        CHECK_NULL_VOID(root);
                        if (!modal->GetPattern<ModalPresentationPattern>()->IsExecuteOnDisappear()) {
                            modal->GetPattern<ModalPresentationPattern>()->OnDisappear();
                            // Fire hidden event of navdestination on the disappeared modal
                            overlayManager->FireNavigationStateChange(root, false, modal);
                        }
                        root->RemoveChild(modal);
                        root->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
                        // Fire shown event of navdestination under the disappeared modal
                        overlayManager->FireNavigationStateChange(root, true);
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
            [rootWeak = rootNodeWeak_, modalWK = WeakClaim(RawPtr(modalNode)), overlayWeak = WeakClaim(this),
                    id = Container::CurrentId()] {
                ContainerScope scope(id);
                auto context = PipelineContext::GetCurrentContext();
                CHECK_NULL_VOID(context);
                auto taskExecutor = context->GetTaskExecutor();
                CHECK_NULL_VOID(taskExecutor);
                // animation finish event should be posted to UI thread.
                taskExecutor->PostTask(
                    [rootWeak, modalWK, overlayWeak, id]() {
                        auto modal = modalWK.Upgrade();
                        auto overlayManager = overlayWeak.Upgrade();
                        CHECK_NULL_VOID(modal && overlayManager);
                        ContainerScope scope(id);
                        auto root = overlayManager->FindWindowScene(modal);
                        CHECK_NULL_VOID(root);
                        if (!modal->GetPattern<ModalPresentationPattern>()->IsExecuteOnDisappear()) {
                            modal->GetPattern<ModalPresentationPattern>()->OnDisappear();
                            // Fire hidden event of navdestination on the disappeared modal
                            overlayManager->FireNavigationStateChange(root, false, modal);
                        }
                        root->RemoveChild(modal);
                        root->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
                        // Fire shown event of navdestination under the disappeared modal
                        overlayManager->FireNavigationStateChange(root, true);
                    },
                    TaskExecutor::TaskType::UI);
            });
        context->OpacityAnimation(option, 1, 0);
    }
}

void OverlayManager::BindSheet(bool isShow, std::function<void(const std::string&)>&& callback,
    std::function<RefPtr<UINode>()>&& buildNodeFunc, std::function<RefPtr<UINode>()>&& buildtitleNodeFunc,
    NG::SheetStyle& sheetStyle, std::function<void()>&& onAppear, std::function<void()>&& onDisappear,
    std::function<void()>&& shouldDismiss, const RefPtr<FrameNode>& targetNode)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto bindSheetTask = [weak = AceType::WeakClaim(this), isShow, callback = std::move(callback),
                             buildNodeFunc = std::move(buildNodeFunc),
                             buildtitleNodeFunc = std::move(buildtitleNodeFunc), sheetStyle,
                             onAppear = std::move(onAppear), onDisappear = std::move(onDisappear),
                             shouldDismiss = std::move(shouldDismiss), targetNode]() mutable {
        auto overlay = weak.Upgrade();
        CHECK_NULL_VOID(overlay);
        overlay->OnBindSheet(isShow, std::move(callback), std::move(buildNodeFunc), std::move(buildtitleNodeFunc),
            sheetStyle, std::move(onAppear), std::move(onDisappear), std::move(shouldDismiss), targetNode);
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        pipeline->FlushUITasks();
    };
    pipeline->AddAnimationClosure(bindSheetTask);
}

void OverlayManager::OnBindSheet(bool isShow, std::function<void(const std::string&)>&& callback,
    std::function<RefPtr<UINode>()>&& buildNodeFunc, std::function<RefPtr<UINode>()>&& buildtitleNodeFunc,
    NG::SheetStyle& sheetStyle, std::function<void()>&& onAppear, std::function<void()>&& onDisappear,
    std::function<void()>&& shouldDismiss, const RefPtr<FrameNode>& targetNode)
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
    if (sheetMap_.count(targetId)) {
        auto topModalNode = sheetMap_[targetId].Upgrade();
        CHECK_NULL_VOID(topModalNode);
        if (topModalNode->GetTag() == V2::SHEET_PAGE_TAG &&
            topModalNode->GetPattern<SheetPresentationPattern>()->GetTargetId() == targetId) {
            if (sheetStyle.backgroundColor.has_value()) {
                topModalNode->GetRenderContext()->UpdateBackgroundColor(sheetStyle.backgroundColor.value());
            }
            if (sheetStyle.backgroundBlurStyle.has_value()) {
                SetSheetBackgroundBlurStyle(topModalNode, sheetStyle.backgroundBlurStyle.value());
            }
            auto maskNode = GetSheetMask(topModalNode);
            if (maskNode) {
                auto maskRenderContext = maskNode->GetRenderContext();
                CHECK_NULL_VOID(maskRenderContext);
                maskRenderContext->UpdateBackgroundColor(sheetStyle.maskColor.value_or(sheetTheme->GetMaskColor()));
            }
            topModalNode->GetPattern<SheetPresentationPattern>()->UpdateOnDisappear(std::move(onDisappear));
            topModalNode->GetPattern<SheetPresentationPattern>()->UpdateShouldDismiss(std::move(shouldDismiss));
            auto layoutProperty = topModalNode->GetLayoutProperty<SheetPresentationProperty>();
            layoutProperty->UpdateSheetStyle(sheetStyle);
            topModalNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
            pipeline->FlushUITasks();
            ComputeSheetOffset(sheetStyle, topModalNode);
            auto sheetType = topModalNode->GetPattern<SheetPresentationPattern>()->GetSheetType();
            if (sheetType != SheetType::SHEET_POPUP) {
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
    if (sheetStyle.backgroundColor.has_value()) {
        sheetNode->GetRenderContext()->UpdateBackgroundColor(sheetStyle.backgroundColor.value());
    }
    if (sheetStyle.backgroundBlurStyle.has_value()) {
        SetSheetBackgroundBlurStyle(sheetNode, sheetStyle.backgroundBlurStyle.value());
    }
    sheetNode->GetPattern<SheetPresentationPattern>()->UpdateOnDisappear(std::move(onDisappear));
    sheetNode->GetPattern<SheetPresentationPattern>()->UpdateShouldDismiss(std::move(shouldDismiss));
    sheetMap_[targetId] = WeakClaim(RawPtr(sheetNode));
    modalStack_.push(WeakClaim(RawPtr(sheetNode)));
    SaveLastModalNode();
    // create maskColor node
    auto sheetType = sheetNode->GetPattern<SheetPresentationPattern>()->GetSheetType();
    auto maskNode = FrameNode::CreateFrameNode(
        V2::SHEET_MASK_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    CHECK_NULL_VOID(maskNode);
    auto maskLayoutProps = maskNode->GetLayoutProperty();
    CHECK_NULL_VOID(maskLayoutProps);
    maskLayoutProps->UpdateMeasureType(MeasureType::MATCH_PARENT);
    auto maskRenderContext = maskNode->GetRenderContext();
    CHECK_NULL_VOID(maskRenderContext);
    maskRenderContext->UpdateBackgroundColor(sheetStyle.maskColor.value_or(sheetTheme->GetMaskColor()));
    maskNode->MountToParent(rootNode);
    auto eventConfirmHub = maskNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(eventConfirmHub);
    sheetMaskClickEvent_ = AceType::MakeRefPtr<NG::ClickEvent>(
        [weak = AceType::WeakClaim(AceType::RawPtr(sheetNode))](const GestureEvent& /* info */) {
            auto sheet = weak.Upgrade();
            CHECK_NULL_VOID(sheet);
            auto sheetPattern = sheet->GetPattern<SheetPresentationPattern>();
            CHECK_NULL_VOID(sheetPattern);
            sheetPattern->SheetInteractiveDismiss(false);
        });
    eventConfirmHub->AddClickEvent(sheetMaskClickEvent_);
    PlaySheetMaskTransition(maskNode, true);
    auto columnNode = FrameNode::CreateFrameNode(V2::SHEET_WRAPPER_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
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
    if (onAppear != nullptr) {
        onAppear();
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
    if (sheetMap_.empty() || !sheetMap_.count(targetId)) {
        DeleteModal(targetId);
        return;
    }
    auto sheetNode = sheetMap_[targetId].Upgrade();
    CHECK_NULL_VOID(sheetNode);
    auto scrollNode = AceType::DynamicCast<FrameNode>(sheetNode->GetChildAtIndex(1));
    CHECK_NULL_VOID(scrollNode);
    auto builder = AceType::DynamicCast<FrameNode>(scrollNode->GetChildAtIndex(0));
    CHECK_NULL_VOID(builder);
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
        PlaySheetMaskTransition(maskNode, false);
    }
    auto sheetType = sheetNode->GetPattern<SheetPresentationPattern>()->GetSheetType();
    if (sheetType == SheetType::SHEET_POPUP) {
        PlayBubbleStyleSheetTransition(sheetNode, false);
    } else {
        PlaySheetTransition(sheetNode, false);
    }
    sheetMap_.erase(targetId);
    modalStack_.pop();
    if (!modalList_.empty()) {
        modalList_.pop_back();
    }
    FireModalPageHide();
    SaveLastModalNode();
}

void OverlayManager::DismissSheet()
{
    if (!modalStack_.empty()) {
        auto topSheetNode = modalStack_.top().Upgrade();
        CHECK_NULL_VOID(topSheetNode);
        if (topSheetNode->GetTag() == V2::SHEET_PAGE_TAG) {
            auto sheetPattern = topSheetNode->GetPattern<SheetPresentationPattern>();
            CHECK_NULL_VOID(sheetPattern);
            sheetPattern->DismissSheet();
        }
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
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    auto sheetMaxHeight = sheetPattern->GetSheetMaxHeight();

    if (isTransitionIn) {
        sheetPattern->SetCurrentHeight(sheetHeight_);
        auto offset = sheetMaxHeight - sheetHeight_;
        if (isFirstTransition) {
            context->OnTransformTranslateUpdate({ 0.0f, sheetMaxHeight, 0.0f });
        }
        if (isModeChangeToAuto) {
            option.SetDuration(0);
            option.SetCurve(Curves::LINEAR);
        }
        option.SetOnFinishEvent(
            [sheetWK = WeakClaim(RawPtr(sheetNode)), height = sheetHeight_] {
                auto sheet = sheetWK.Upgrade();
                CHECK_NULL_VOID(sheet);
                auto sheetPattern = sheet->GetPattern<SheetPresentationPattern>();
                CHECK_NULL_VOID(sheetPattern);
                sheetPattern->ProcessColumnRect(height);
                sheetPattern->ChangeScrollHeight(height);
        });
        AnimationUtils::Animate(
            option,
            [context, offset]() {
                if (context) {
                    context->OnTransformTranslateUpdate({ 0.0f, offset, 0.0f });
                }
            },
            option.GetOnFinishEvent());
    } else {
        option.SetOnFinishEvent(
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
                    TaskExecutor::TaskType::UI);
            });
        AnimationUtils::Animate(
            option,
            [context, sheetMaxHeight]() {
                if (context) {
                    context->OnTransformTranslateUpdate({ 0.0f, sheetMaxHeight, 0.0f });
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
        sheetPattern->StartAlphaEnteringAnimation([sheetWK = WeakClaim(RawPtr(sheetNode))] {
            auto sheet = sheetWK.Upgrade();
            CHECK_NULL_VOID(sheet);
            auto sheetPattern = sheet->GetPattern<SheetPresentationPattern>();
            CHECK_NULL_VOID(sheetPattern);
            sheetPattern->ProcessColumnRect();
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
                    TaskExecutor::TaskType::UI);
            });
    }
}

void OverlayManager::PlaySheetMaskTransition(RefPtr<FrameNode> maskNode, bool isTransitionIn)
{
    AnimationOption option;
    const RefPtr<InterpolatingSpring> curve =
        AceType::MakeRefPtr<InterpolatingSpring>(0.0f, CURVE_MASS, CURVE_STIFFNESS, CURVE_DAMPING);
    option.SetCurve(curve);
    option.SetFillMode(FillMode::FORWARDS);
    auto context = maskNode->GetRenderContext();
    CHECK_NULL_VOID(context);
    if (isTransitionIn) {
        context->OpacityAnimation(option, 0.0, 1.0);
    } else {
        if (sheetMaskClickEvent_) {
            auto eventConfirmHub = maskNode->GetOrCreateGestureEventHub();
            CHECK_NULL_VOID(eventConfirmHub);
            eventConfirmHub->RemoveClickEvent(sheetMaskClickEvent_);
        }
        option.SetOnFinishEvent(
            [rootWeak = rootNodeWeak_, maskNodeWK = WeakClaim(RawPtr(maskNode)), id = Container::CurrentId(),
                    weakOverlayManager = WeakClaim(this)] {
                ContainerScope scope(id);
                auto context = PipelineContext::GetCurrentContext();
                CHECK_NULL_VOID(context);
                auto taskExecutor = context->GetTaskExecutor();
                CHECK_NULL_VOID(taskExecutor);
                // animation finish event should be posted to UI thread.
                taskExecutor->PostTask(
                    [rootWeak, maskNodeWK, id, weakOverlayManager]() {
                        auto mask = maskNodeWK.Upgrade();
                        auto overlayManager = weakOverlayManager.Upgrade();
                        CHECK_NULL_VOID(mask && overlayManager);

                        ContainerScope scope(id);
                        auto root = overlayManager->FindWindowScene(mask);
                        CHECK_NULL_VOID(root);
                        root->RemoveChild(mask);
                    },
                    TaskExecutor::TaskType::UI);
            });
        context->OpacityAnimation(option, 1.0, 0.0);
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

void OverlayManager::ComputeSheetOffset(NG::SheetStyle& sheetStyle, RefPtr<FrameNode> sheetNode)
{
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    auto sheetMaxHeight = sheetPattern->GetSheetMaxHeight();
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
    auto sheetMaxHeight = sheetPattern->GetSheetMaxHeight();
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto manager = context->GetSafeAreaManager();
    CHECK_NULL_VOID(manager);
    auto statusBarHeight = manager->GetSystemSafeArea().top_.Length();
    auto largeHeight = sheetMaxHeight - SHEET_BLANK_MINI_HEIGHT.ConvertToPx() - statusBarHeight;
    if (sheetStyle.sheetMode.has_value()) {
        if (sheetStyle.sheetMode == SheetMode::MEDIUM) {
            sheetHeight_ = sheetMaxHeight * MEDIUM_SIZE;
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
    auto sheetMaxHeight = sheetPattern->GetSheetMaxHeight();
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto manager = context->GetSafeAreaManager();
    CHECK_NULL_VOID(manager);
    auto statusBarHeight = manager->GetSystemSafeArea().top_.Length();
    auto largeHeight = sheetMaxHeight - SHEET_BLANK_MINI_HEIGHT.ConvertToPx() - statusBarHeight;
    auto selection = sheetStyle.detents[0];
    if (selection.sheetMode.has_value()) {
        if (selection.sheetMode == SheetMode::MEDIUM) {
            sheetHeight_ = sheetMaxHeight * MEDIUM_SIZE;
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
    if (!modalStack_.empty()) {
        auto topSheetNode = modalStack_.top().Upgrade();
        CHECK_NULL_VOID(topSheetNode);
        if (topSheetNode->GetTag() != V2::SHEET_PAGE_TAG) {
            return;
        }
        if (topSheetNode->GetPattern<SheetPresentationPattern>()->GetTargetId() != targetId) {
            return;
        }
        auto rootNode = FindWindowScene(sheetNode);
        CHECK_NULL_VOID(rootNode);
        auto root = DynamicCast<FrameNode>(rootNode);
        ModalPageLostFocus(topSheetNode);
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
        modalStack_.pop();
        modalList_.pop_back();
        FireModalPageHide();
        SaveLastModalNode();
    }
}

void OverlayManager::DeleteModal(int32_t targetId)
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
            auto rootNode = FindWindowScene(modalNode);
            CHECK_NULL_VOID(rootNode);
            if (isModal) {
                modalNode->GetPattern<ModalPresentationPattern>()->OnDisappear();
                modalNode->GetPattern<ModalPresentationPattern>()->FireCallback("false");
                // Fire hidden event of navdestination on the disappeared modal
                FireNavigationStateChange(rootNode, false, modalNode);
                rootNode->RemoveChild(modalNode);
            } else {
                modalNode->GetPattern<SheetPresentationPattern>()->OnDisappear();
                modalNode->GetPattern<SheetPresentationPattern>()->FireCallback("false");
                sheetMap_.erase(targetId);
                auto sheetParent = DynamicCast<FrameNode>(modalNode->GetParent());
                CHECK_NULL_VOID(sheetParent);
                rootNode->RemoveChild(sheetParent);
            }
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
    if (pageNode == nullptr) {
        auto parent = customKeyboard->GetParent();
        CHECK_NULL_VOID(parent);
        parent->RemoveChild(customKeyboard);
        return;
    }
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
        AnimationUtils::Animate(option, [context, pageHeight]() {
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
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto dragDropManager = pipeline->GetDragDropManager();
        CHECK_NULL_VOID(dragDropManager);
        if (!dragDropManager->IsNeedScaleDragPreview()) {
            InteractionInterface::GetInstance()->SetDragWindowVisible(true);
        }
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

int32_t OverlayManager::CreateModalUIExtension(
    const AAFwk::Want& want, const ModalUIExtensionCallbacks& callbacks, bool isProhibitBack)
{
    isProhibitBack_ = isProhibitBack;
    ModalStyle modalStyle;
    modalStyle.modalTransition = NG::ModalTransition::NONE;
    modalStyle.isUIExtension = true;
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
    BindContentCover(true, nullptr, std::move(buildNodeFunc), modalStyle, nullptr, nullptr, nullptr, -(sessionId));
    return sessionId;
}

void OverlayManager::CloseModalUIExtension(int32_t sessionId)
{
    ModalStyle modalStyle;
    modalStyle.modalTransition = NG::ModalTransition::NONE;
    BindContentCover(false, nullptr, nullptr, modalStyle, nullptr, nullptr, nullptr, -(sessionId));
}

RefPtr<FrameNode> OverlayManager::BindUIExtensionToMenu(const RefPtr<FrameNode>& uiExtNode,
    const RefPtr<NG::FrameNode>& targetNode, std::string longestContent, int32_t menuSize)
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
    CHECK_NULL_RETURN(scollNode, nullptr);
    auto scollLayoutProperty = scollNode->GetLayoutProperty();
    CHECK_NULL_RETURN(scollLayoutProperty, nullptr);
    scollLayoutProperty->UpdateMargin(MarginProperty());
    scollLayoutProperty->UpdatePadding(PaddingProperty());
    return menuNode;
}

SizeF OverlayManager::CaculateMenuSize(
    const RefPtr<FrameNode>& menuNode, std::string longestContent, int32_t menuSize)
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

bool OverlayManager::ShowUIExtensionMenu(const RefPtr<NG::FrameNode>& uiExtNode, NG::RectF aiRect,
    std::string longestContent, int32_t menuSize, const RefPtr<NG::FrameNode>& targetNode)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "show ui extension menu enter");
    CHECK_NULL_RETURN(uiExtNode, false);
    auto menuNode = BindUIExtensionToMenu(uiExtNode, targetNode, longestContent, menuSize);
    CHECK_NULL_RETURN(menuNode, false);
    auto menuLayoutProperty = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_RETURN(menuLayoutProperty, false);
    menuLayoutProperty->UpdateIsRectInTarget(true);
    menuLayoutProperty->UpdateTargetSize(aiRect.GetSize());
    auto menuWrapperNode = DynamicCast<FrameNode>(menuNode->GetParent());
    CHECK_NULL_RETURN(menuWrapperNode, false);
    ShowMenu(targetNode->GetId(), aiRect.GetOffset(), menuWrapperNode);
    return true;
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
