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
#include <string>
#include <utility>
#include <vector>
#if defined(OHOS_STANDARD_SYSTEM) and !defined(ACE_UNITTEST)
#include "want.h"
#endif

#include "base/error/error_code.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/log/dump_log.h"
#include "base/log/log.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/subwindow/subwindow_manager.h"
#include "base/utils/measure_util.h"
#include "base/utils/system_properties.h"
#include "base/utils/utils.h"
#include "base/window/foldable_window.h"
#include "core/animation/animation_pub.h"
#include "core/animation/spring_curve.h"
#include "core/common/ace_application_info.h"
#include "core/common/ace_engine.h"
#include "core/common/container.h"
#include "core/common/ime/input_method_manager.h"
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
#include "core/components_ng/manager/drag_drop/drag_drop_func_wrapper.h"
#include "core/components_ng/manager/drag_drop/drag_drop_global_controller.h"
#include "core/components_ng/manager/focus/focus_view.h"
#include "core/components_ng/pattern/bubble/bubble_event_hub.h"
#include "core/components_ng/pattern/bubble/bubble_pattern.h"
#include "core/components_ng/pattern/calendar_picker/calendar_dialog_view.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_view.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_model_ng.h"
#include "core/components_ng/pattern/menu/menu_item_group/menu_item_group_view.h"
#include "core/components_ng/pattern/menu/menu_theme.h"
#include "core/components_ng/pattern/menu/menu_view.h"
#include "core/components_ng/pattern/menu/preview/menu_preview_pattern.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/overlay/keyboard_view.h"
#include "core/components_ng/pattern/overlay/overlay_container_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_view.h"
#include "core/components_ng/pattern/overlay/sheet_wrapper_pattern.h"
#include "core/components_ng/pattern/picker/datepicker_dialog_view.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "core/components_ng/pattern/text_picker/textpicker_dialog_view.h"
#include "core/components_ng/pattern/time_picker/timepicker_dialog_view.h"
#include "core/components_ng/pattern/toast/toast_pattern.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_model.h"
#include "core/components_ng/pattern/video/video_full_screen_pattern.h"
#ifdef WEB_SUPPORTED
#if !defined(ANDROID_PLATFORM) && !defined(IOS_PLATFORM)
#include "core/components_ng/pattern/web/web_pattern.h"
#else
#include "core/components_ng/pattern/web/cross_platform/web_pattern.h"
#endif
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
constexpr int32_t ATOMIC_SERVICE_MIN_SIZE = 2;

//  OVERLAY_EXISTS:  overlay was removed
// OVERLAY_REMOVE:: overlay exists
// OVERLAY_NOTHING:nothing
constexpr int32_t OVERLAY_EXISTS = 0;
constexpr int32_t OVERLAY_REMOVE = 1;
constexpr int32_t OVERLAY_NOTHING = 2;

// custom keyboard animation params
const RefPtr<Curve> SHOW_CUSTOM_KEYBOARD_ANIMATION_CURVE =
    AceType::MakeRefPtr<InterpolatingSpring>(0.0f, 1.0f, 342.0f, 37.0f);
const RefPtr<Curve> HIDE_CUSTOM_KEYBOARD_ANIMATION_CURVE =
    AceType::MakeRefPtr<InterpolatingSpring>(4.0f, 1.0f, 342.0f, 37.0f);

const RefPtr<InterpolatingSpring> MENU_ANIMATION_CURVE =
    AceType::MakeRefPtr<InterpolatingSpring>(0.0f, 1.0f, 528.0f, 35.0f);

const RefPtr<Curve> CUSTOM_PREVIEW_ANIMATION_CURVE =
    AceType::MakeRefPtr<InterpolatingSpring>(0.0f, 1.0f, 280.0f, 30.0f);
const std::string HOVER_IMAGE_CLIP_DISAPPEAR_PROPERTY_NAME = "hoverImageClipDisAppear";
constexpr double MENU_ORIGINAL_SCALE = 0.6f;
constexpr int32_t DUMP_LOG_DEPTH_1 = 1;
constexpr int32_t DUMP_LOG_DEPTH_2 = 2;

constexpr int32_t EVENT_COLUMN_SLOT = -2;

const float MINIMUM_AMPLITUDE_RATION = 0.08f;

// UIExtensionComponent Transform param key
#if defined(OHOS_STANDARD_SYSTEM) and !defined(ACE_UNITTEST)
constexpr char WANT_PARAM_UIEXTNODE_ANGLE_KEY[] = "modalUIExtNodeAngle";
constexpr char WANT_PARAM_UIEXTNODE_WIDTH_KEY[] = "modalUIExtNodeWidth";
constexpr char WANT_PARAM_UIEXTNODE_HEIGHT_KEY[] = "modalUIExtNodeHeight";
#endif
constexpr int32_t UIEXTNODE_ANGLE_90 = 90;
constexpr int32_t UIEXTNODE_ANGLE_180 = 180;
constexpr int32_t UIEXTNODE_ANGLE_270 = 270;

constexpr double DISTANCE_THRESHOLD = 20.0;

RefPtr<FrameNode> GetLastPage()
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, nullptr);
    auto stageManager = pipelineContext->GetStageManager();
    CHECK_NULL_RETURN(stageManager, nullptr);
    auto pageNode = stageManager->GetLastPage();
    return pageNode;
}

void ShowPreviewBgDisappearAnimationProc(const RefPtr<RenderContext>& previewRenderContext,
    const RefPtr<MenuTheme>& menuTheme, bool isShowHoverImage)
{
    auto shadow = previewRenderContext->GetBackShadow();
    if (!shadow.has_value()) {
        shadow = Shadow::CreateShadow(ShadowStyle::None);
    }
    previewRenderContext->UpdateBackShadow(shadow.value());
    auto disappearDuration = menuTheme->GetDisappearDuration();
    AnimationOption previewOption;
    if (isShowHoverImage) {
        previewOption.SetCurve(CUSTOM_PREVIEW_ANIMATION_CURVE);
    } else {
        previewOption.SetCurve(Curves::SHARP);
        previewOption.SetDuration(disappearDuration);
    }
    AnimationUtils::Animate(previewOption, [previewRenderContext, shadow]() mutable {
        CHECK_NULL_VOID(previewRenderContext);
        auto color = shadow->GetColor();
        auto newColor = Color::FromARGB(1, color.GetRed(), color.GetGreen(), color.GetBlue());
        shadow->SetColor(newColor);
        previewRenderContext->UpdateBackShadow(shadow.value());
        BorderRadiusProperty borderRadius;
        borderRadius.SetRadius(0.0_vp);
        previewRenderContext->UpdateBorderRadius(borderRadius);
    });
}

void UpdateHoverImagePreviewOpacityAnimation(const RefPtr<MenuTheme>& menuTheme,
    const RefPtr<MenuPattern>& menuPattern, RefPtr<FrameNode>& previewChild)
{
    CHECK_NULL_VOID(menuPattern);
    CHECK_NULL_VOID(menuPattern->GetIsShowHoverImage());

    CHECK_NULL_VOID(previewChild);
    auto previewRenderContext = previewChild->GetRenderContext();
    CHECK_NULL_VOID(previewRenderContext);

    bool isCustomPreview = previewChild->GetTag() == V2::MENU_PREVIEW_ETS_TAG;
    // only update custom preview opacity
    CHECK_NULL_VOID(isCustomPreview);

    AnimationOption option;
    option.SetDuration(menuTheme->GetHoverImagePreviewDisAppearDuration());
    option.SetCurve(Curves::FRICTION);
    AnimationUtils::Animate(
        option, [previewRenderContext]() {
            CHECK_NULL_VOID(previewRenderContext);
            previewRenderContext->UpdateOpacity(0.0);
        });
}

void ShowPreviewDisappearAnimationProc(const RefPtr<MenuWrapperPattern>& menuWrapperPattern,
    RefPtr<FrameNode>& previewChild)
{
    CHECK_NULL_VOID(menuWrapperPattern);
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
    UpdateHoverImagePreviewOpacityAnimation(menuTheme, menuPattern, previewChild);

    auto springMotionResponse = menuTheme->GetPreviewDisappearSpringMotionResponse();
    auto springMotionDampingFraction = menuTheme->GetPreviewDisappearSpringMotionDampingFraction();
    AnimationOption scaleOption;
    auto motion = AceType::MakeRefPtr<ResponsiveSpringMotion>(springMotionResponse, springMotionDampingFraction);
    scaleOption.SetCurve(motion);
    float previewScale = 1.0f;
    if (menuPattern->GetPreviewMode() == MenuPreviewMode::IMAGE) {
        auto previewGeometryNode = previewChild->GetGeometryNode();
        CHECK_NULL_VOID(previewGeometryNode);
        auto previewSize = previewGeometryNode->GetFrameSize();
        if (!NearEqual(menuPattern->GetTargetSize().Width(), previewSize.Width())) {
            previewScale = menuPattern->GetTargetSize().Width() / previewSize.Width();
        }
    }
    ShowPreviewBgDisappearAnimationProc(previewRenderContext, menuTheme, menuWrapperPattern->GetIsShowHoverImage());

    CHECK_NULL_VOID(!menuPattern->GetIsShowHoverImage());
    menuWrapperPattern->StopPreviewMenuAnimation();
    AnimationUtils::Animate(scaleOption,
        [previewRenderContext, previewPosition, previewScale]() {
        CHECK_NULL_VOID(previewRenderContext);
        previewRenderContext->UpdatePosition(
            OffsetT<Dimension>(Dimension(previewPosition.GetX()), Dimension(previewPosition.GetY())));
        previewRenderContext->UpdateTransformScale(VectorF(previewScale, previewScale));
    });
}

RefPtr<NodeAnimatablePropertyFloat> CreateVisibleAreaClipAnimationWhenDisappear(
    const RefPtr<RenderContext>& clipContext, const RefPtr<MenuPreviewPattern>& previewPattern, float radius)
{
    CHECK_NULL_RETURN(clipContext && previewPattern, nullptr);

    auto callback = [clipContext, previewPattern, radius](float rate) {
        CHECK_NULL_VOID(clipContext && previewPattern);
        auto clipStartWidth = previewPattern->GetStackAfterScaleActualWidth();
        auto clipStartHeight = previewPattern->GetStackAfterScaleActualHeight();
        auto clipEndWidth = previewPattern->GetHoverImageAfterScaleWidth();
        auto clipEndHeight = previewPattern->GetHoverImageAfterScaleHeight();

        auto curentClipAreaWidth = rate * (clipEndWidth - clipStartWidth) + clipStartWidth;
        auto curentClipAreaHeight = rate * (clipEndHeight - clipStartHeight) + clipStartHeight;

        auto clipOffset = previewPattern->GetHoverImageAfterScaleOffset();

        RoundRect roundRectInstance;
        roundRectInstance.SetRect(RectF(OffsetF(rate * clipOffset.GetX(), rate * clipOffset.GetY()),
            SizeF(curentClipAreaWidth, curentClipAreaHeight)));
        roundRectInstance.SetCornerRadius((1 - rate) * radius);
        clipContext->ClipWithRoundRect(roundRectInstance);
    };
    return AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(-1.0, std::move(callback));
}

void UpdateHoverImageDisappearScaleAndPosition(const RefPtr<MenuWrapperPattern>& menuWrapperPattern,
    const RefPtr<MenuPreviewPattern>& previewPattern)
{
    CHECK_NULL_VOID(menuWrapperPattern);
    CHECK_NULL_VOID(menuWrapperPattern->GetIsShowHoverImage());

    CHECK_NULL_VOID(previewPattern);
    // reverse scale
    auto scaleTo = previewPattern->GetHoverImageScaleFrom();
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto menuTheme = pipelineContext->GetTheme<MenuTheme>();
    CHECK_NULL_VOID(menuTheme);
    auto scaleAfter = LessNotEqual(scaleTo, 0.0) ? menuTheme->GetPreviewBeforeAnimationScale() : scaleTo;

    auto stackNode = menuWrapperPattern->GetHoverImageStackNode();
    CHECK_NULL_VOID(stackNode);
    auto stackContext = stackNode->GetRenderContext();
    CHECK_NULL_VOID(stackContext);

    auto flexNode = menuWrapperPattern->GetHoverImageFlexNode();
    CHECK_NULL_VOID(flexNode);
    auto flexContext = flexNode->GetRenderContext();
    CHECK_NULL_VOID(flexContext);
    
    auto menuChild = menuWrapperPattern->GetMenu();
    CHECK_NULL_VOID(menuChild);
    auto menuPattern = menuChild->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    auto previewPosition = menuPattern->GetPreviewOriginOffset();

    menuWrapperPattern->StopPreviewMenuAnimation();
    AnimationOption option = AnimationOption();
    option.SetCurve(CUSTOM_PREVIEW_ANIMATION_CURVE);

    RefPtr<NodeAnimatablePropertyFloat> animateProperty;
    if (previewPattern->IsHoverImageAnimationPlaying()) {
        menuWrapperPattern->SetIsStopHoverImageAnimation(true);
        previewPattern->SetIsHoverImageAnimationPlaying(false);
    } else {
        auto radius = menuTheme->GetPreviewBorderRadius().ConvertToPx();
        animateProperty = CreateVisibleAreaClipAnimationWhenDisappear(stackContext, previewPattern, radius);
        CHECK_NULL_VOID(animateProperty);
        stackContext->AttachNodeAnimatableProperty(animateProperty);
        auto clipRate = std::min(1.0f, menuWrapperPattern->GetPreviewMenuAnimationInfo().clipRate);
        animateProperty->Set(NonNegative(clipRate) ? 1.0 - clipRate : 0.0);
    }

    AnimationUtils::Animate(
        option, [stackContext, scaleAfter, flexContext, previewPosition, animateProperty]() {
            CHECK_NULL_VOID(stackContext);
            stackContext->UpdateTransformScale(VectorF(scaleAfter, scaleAfter));

            CHECK_NULL_VOID(flexContext);
            flexContext->UpdatePosition(
                OffsetT<Dimension>(Dimension(previewPosition.GetX()), Dimension(previewPosition.GetY())));

            CHECK_NULL_VOID(animateProperty);
            animateProperty->Set(1.0);
        });

    ShowPreviewBgDisappearAnimationProc(stackContext, menuTheme, menuWrapperPattern->GetHoverImageStackNode());
}

void ShowPreviewDisappearAnimation(const RefPtr<MenuWrapperPattern>& menuWrapperPattern)
{
    CHECK_NULL_VOID(menuWrapperPattern);
    auto previewChild = menuWrapperPattern->GetPreview();
    CHECK_NULL_VOID(previewChild);
    ShowPreviewDisappearAnimationProc(menuWrapperPattern, previewChild);
    
    CHECK_NULL_VOID(menuWrapperPattern->GetIsShowHoverImage());
    auto hoverImagePreview = menuWrapperPattern->GetHoverImagePreview();
    CHECK_NULL_VOID(hoverImagePreview);
    ShowPreviewDisappearAnimationProc(menuWrapperPattern, hoverImagePreview);

    auto previewPattern = previewChild->GetPattern<MenuPreviewPattern>();
    CHECK_NULL_VOID(previewPattern);
    UpdateHoverImageDisappearScaleAndPosition(menuWrapperPattern, previewPattern);
}

void UpdateContextMenuDisappearPositionAnimation(const RefPtr<FrameNode>& menu, const NG::OffsetF& offset,
    float menuScale)
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
    auto menuPosition = menuChild->GetGeometryNode()->GetFrameOffset();
    menuPosition += offset;
    menuChild->GetGeometryNode()->SetFrameOffset(menuPosition);
    menuPattern->SetEndOffset(menuPosition);

    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto menuTheme = pipelineContext->GetTheme<MenuTheme>();
    CHECK_NULL_VOID(menuTheme);

    auto scaleAfter = LessNotEqual(menuScale, 0.0) ? 1.0f : menuScale;
    auto springMotionResponse = menuTheme->GetPreviewDisappearSpringMotionResponse();
    auto springMotionDampingFraction = menuTheme->GetPreviewDisappearSpringMotionDampingFraction();
    AnimationOption positionOption;
    auto motion = AceType::MakeRefPtr<ResponsiveSpringMotion>(springMotionResponse, springMotionDampingFraction);
    positionOption.SetCurve(motion);
    AnimationUtils::Animate(positionOption, [menuRenderContext, menuPosition, scaleAfter]() {
        CHECK_NULL_VOID(menuRenderContext);
        menuRenderContext->UpdatePosition(
            OffsetT<Dimension>(Dimension(menuPosition.GetX()), Dimension(menuPosition.GetY())));
        // menuScale default value is 1.0f, only update menu scale with not the default value
        if (scaleAfter != 1.0f) {
            menuRenderContext->UpdateTransformScale(VectorF(scaleAfter, scaleAfter));
        }
    });
}

void ContextMenuSwitchDragPreviewScaleAnimationProc(const RefPtr<RenderContext>& dragPreviewContext,
    const RefPtr<RenderContext>& previewRenderContext, const RefPtr<FrameNode>& previewChild,
    const NG::OffsetF& offset, int32_t duration)
{
    CHECK_NULL_VOID(previewChild);
    auto previewPattern = previewChild->GetPattern<MenuPreviewPattern>();
    CHECK_NULL_VOID(previewPattern);
    CHECK_NULL_VOID(previewPattern->GetIsShowHoverImage());
    
    CHECK_NULL_VOID(dragPreviewContext);
    auto width = dragPreviewContext->GetPaintRectWithTransform().Width();
    auto height = dragPreviewContext->GetPaintRectWithTransform().Height();

    CHECK_NULL_VOID(previewRenderContext);
    auto previewWidth = previewPattern->GetCustomPreviewWidth();
    auto previewHeight = previewPattern->GetCustomPreviewHeight();
    
    // reverse scale
    float scaleTo = 1.0f;
    if (previewWidth - width < previewHeight - height) {
        CHECK_EQUAL_VOID(previewWidth, 0);
        scaleTo = width / previewWidth;
    } else {
        CHECK_EQUAL_VOID(previewHeight, 0);
        scaleTo = height / previewHeight;
    }
    auto scaleAfter = LessNotEqual(scaleTo, 0.0) ? 1.0f : scaleTo;
    AnimationOption option = AnimationOption();
    option.SetDuration(duration);
    option.SetCurve(Curves::FRICTION);
    AnimationUtils::Animate(
        option,
        [previewRenderContext, dragPreviewContext, scaleAfter, offset]() {
            CHECK_NULL_VOID(previewRenderContext);
            previewRenderContext->UpdateTransformScale(VectorF(scaleAfter, scaleAfter));
            previewRenderContext->UpdateTransformTranslate({ offset.GetX(), offset.GetY(), 0.0f });

            CHECK_NULL_VOID(dragPreviewContext);
            dragPreviewContext->UpdateTransformTranslate({ offset.GetX(), offset.GetY(), 0.0f });
        });
}

void UpdateContextMenuSwitchDragPreviewBefore(const RefPtr<FrameNode>& menu)
{
    CHECK_NULL_VOID(menu);
    auto menuWrapperPattern = menu->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(menuWrapperPattern && menuWrapperPattern->GetIsShowHoverImage());
    auto previewChild = menuWrapperPattern->GetPreview();
    CHECK_NULL_VOID(previewChild);
    auto previewPattern = previewChild->GetPattern<MenuPreviewPattern>();
    CHECK_NULL_VOID(previewPattern);

    if (previewPattern->IsHoverImageScalePlaying()) {
        auto previewRenderContext = previewChild->GetRenderContext();
        CHECK_NULL_VOID(previewRenderContext);
        previewRenderContext->UpdateOpacity(0.0);
    }
}

void ContextMenuSwitchDragPreviewAnimationProc(const RefPtr<FrameNode>& menu,
    const RefPtr<NG::FrameNode>& dragPreviewNode, const NG::OffsetF& offset)
{
    CHECK_NULL_VOID(dragPreviewNode && menu);
    auto menuWrapperPattern = menu->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(menuWrapperPattern && menuWrapperPattern->GetIsShowHoverImage());

    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto menuTheme = pipelineContext->GetTheme<MenuTheme>();
    CHECK_NULL_VOID(menuTheme);
    // consistent with the menu disappear duration
    auto duration = menuTheme->GetDisappearDuration();

    auto previewChild = menuWrapperPattern->GetPreview();
    CHECK_NULL_VOID(previewChild);
    auto previewRenderContext = previewChild->GetRenderContext();
    CHECK_NULL_VOID(previewRenderContext);
    auto dragPreviewContext = dragPreviewNode->GetRenderContext();
    CHECK_NULL_VOID(dragPreviewContext);

    // update custom preview scale and position
    ContextMenuSwitchDragPreviewScaleAnimationProc(dragPreviewContext, previewRenderContext, previewChild, offset,
        duration);

    // custom preview and drag preview update Opacity
    CHECK_NULL_VOID(!menuWrapperPattern->GetIsShowHoverImagePreviewStartDrag());
    menuWrapperPattern->SetIsShowHoverImagePreviewStartDrag(true);
    auto imageNode = menuWrapperPattern->GetHoverImagePreview();
    CHECK_NULL_VOID(imageNode);
    auto imageContext = imageNode->GetRenderContext();
    CHECK_NULL_VOID(imageContext);
    imageContext->UpdateOpacity(0.0);

    previewRenderContext->UpdateOpacity(1.0);
    dragPreviewContext->UpdateOpacity(0.0);
    AnimationOption option;
    option.SetDuration(duration);
    option.SetCurve(Curves::FRICTION);
    option.SetOnFinishEvent(
        [id = Container::CurrentId(), menuWrapperPattern] {
            ContainerScope scope(id);
            menuWrapperPattern->SetIsShowHoverImagePreviewStartDrag(false);
        });
    AnimationUtils::Animate(
        option, [previewRenderContext, dragPreviewContext]() mutable {
            CHECK_NULL_VOID(previewRenderContext);
            previewRenderContext->UpdateOpacity(0.0);

            BorderRadiusProperty borderRadius;
            borderRadius.SetRadius(0.0_vp);
            previewRenderContext->UpdateBorderRadius(borderRadius);

            CHECK_NULL_VOID(dragPreviewContext);
            dragPreviewContext->UpdateOpacity(1.0);
        },
        option.GetOnFinishEvent());
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
    auto hasTransition = menuWrapperPattern->HasTransitionEffect() || menuWrapperPattern->HasPreviewTransitionEffect();
    auto isPreviewNone = menuWrapperPattern->GetPreviewMode() == MenuPreviewMode::NONE;
    auto menuPosition =
        (hasTransition || isPreviewNone) ? menuPattern->GetEndOffset() : menuPattern->GetPreviewMenuDisappearPosition();
    menuWrapperPattern->ClearAllSubMenu();

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
        CHECK_NULL_VOID(menuRenderContext);
        menuRenderContext->UpdatePosition(
            OffsetT<Dimension>(Dimension(menuPosition.GetX()), Dimension(menuPosition.GetY())));
    });

    auto disappearDuration = menuTheme->GetDisappearDuration();
    auto menuAnimationScale = menuTheme->GetMenuAnimationScale();
    AnimationOption scaleOption;
    scaleOption.SetCurve(Curves::FAST_OUT_LINEAR_IN);
    scaleOption.SetDuration(disappearDuration);
    AnimationUtils::Animate(scaleOption, [menuRenderContext, menuAnimationScale]() {
        CHECK_NULL_VOID(menuRenderContext);
        menuRenderContext->UpdateTransformScale({ menuAnimationScale, menuAnimationScale });
    });

    option.SetDuration(disappearDuration);
    option.SetCurve(Curves::FRICTION);
    AnimationUtils::Animate(
        option,
        [menuRenderContext]() {
            CHECK_NULL_VOID(menuRenderContext);
            menuRenderContext->UpdateOpacity(0.0);
        },
        option.GetOnFinishEvent());
}

void FireMenuDisappear(AnimationOption& option, const RefPtr<MenuWrapperPattern>& menuWrapperPattern)
{
    CHECK_NULL_VOID(menuWrapperPattern);
    auto menuNode = menuWrapperPattern->GetMenu();
    CHECK_NULL_VOID(menuNode);
    auto menuRenderContext = menuNode->GetRenderContext();
    CHECK_NULL_VOID(menuRenderContext);
    MENU_ANIMATION_CURVE->UpdateMinimumAmplitudeRatio(MINIMUM_AMPLITUDE_RATION);
    option.SetCurve(MENU_ANIMATION_CURVE);
    AnimationUtils::Animate(option, [menuRenderContext]() {
        if (menuRenderContext) {
            menuRenderContext->UpdateTransformScale(VectorF(MENU_ORIGINAL_SCALE, MENU_ORIGINAL_SCALE));
            menuRenderContext->UpdateOpacity(0.0f);
        }
    }, option.GetOnFinishEvent());
}
} // namespace

OverlayManager::~OverlayManager()
{
    TAG_LOGI(AceLogTag::ACE_OVERLAY, "OverlayManager destroyed");
    popupMap_.clear();
}

void OverlayManager::UpdateContextMenuDisappearPosition(
    const NG::OffsetF& offset, float menuScale, bool isRedragStart, int32_t menuWrapperId)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto overlayManager = pipelineContext->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    if (isRedragStart) {
        overlayManager->ResetContextMenuRestartDragVector();
    }

    if (menuMap_.empty()) {
        return;
    }

    RefPtr<FrameNode> menuWrapper = nullptr;
    for (auto [targetId, node] : menuMap_) {
        if (node && node->GetId() == menuWrapperId) {
            menuWrapper = node;
        }
    }

    CHECK_NULL_VOID(menuWrapper && menuWrapper->GetTag() == V2::MENU_WRAPPER_ETS_TAG);
    overlayManager->UpdateDragMoveVector(offset);

    if (overlayManager->IsOriginDragMoveVector() || !overlayManager->IsUpdateDragMoveVector()) {
        return;
    }

    UpdateContextMenuDisappearPositionAnimation(menuWrapper, overlayManager->GetUpdateDragMoveVector(), menuScale);
}

OffsetF OverlayManager::CalculateMenuPosition(const RefPtr<FrameNode>& menuWrapperNode, const OffsetF& offset)
{
    CHECK_NULL_RETURN(menuWrapperNode, OffsetF(0.0f, 0.0f));
    if (IsContextMenuDragHideFinished()) {
        return OffsetF(0.0f, 0.0f);
    }
    UpdateDragMoveVector(offset);
    if (menuMap_.empty() || IsOriginDragMoveVector() || !IsUpdateDragMoveVector()) {
        return OffsetF(0.0f, 0.0f);
    }

    auto menuWrapperPattern = menuWrapperNode->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_RETURN(menuWrapperPattern, OffsetF(0.0f, 0.0f));
    auto menuNode = menuWrapperPattern->GetMenu();
    CHECK_NULL_RETURN(menuNode, OffsetF(0.0f, 0.0f));
    auto menuOffset = GetUpdateDragMoveVector();
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    CHECK_NULL_RETURN(menuPattern, OffsetF(0.0f, 0.0f));
    auto menuGeometryNode = menuNode->GetGeometryNode();
    CHECK_NULL_RETURN(menuGeometryNode, OffsetF(0.0f, 0.0f));
    auto menuPosition = menuGeometryNode->GetFrameOffset();
    menuPosition += menuOffset;
    menuGeometryNode->SetFrameOffset(menuPosition);
    menuPattern->SetEndOffset(menuPosition);
    return menuPosition;
}

bool OverlayManager::GetMenuPreviewCenter(NG::OffsetF& offset)
{
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_RETURN(rootNode, false);
    for (const auto& child : rootNode->GetChildren()) {
        auto node = DynamicCast<FrameNode>(child);
        if (node && node->GetTag() == V2::MENU_WRAPPER_ETS_TAG) {
            auto menuWarpperPattern = node->GetPattern<MenuWrapperPattern>();
            CHECK_NULL_RETURN(menuWarpperPattern, false);
            auto previewChild = menuWarpperPattern->GetPreview();
            CHECK_NULL_RETURN(previewChild, false);
            auto geometryNode = previewChild->GetGeometryNode();
            if (geometryNode && geometryNode->GetFrameRect().IsEmpty()) {
                return false;
            }
            auto previewOffset = DragDropFuncWrapper::GetPaintRectCenter(previewChild);
            offset.SetX(previewOffset.GetX());
            offset.SetY(previewOffset.GetY());
            return true;
        }
    }
    return false;
}

void OverlayManager::ContextMenuSwitchDragPreviewAnimation(const RefPtr<NG::FrameNode>& dragPreviewNode,
    const NG::OffsetF& offset)
{
    CHECK_NULL_VOID(dragPreviewNode);
    if (menuMap_.empty()) {
        return;
    }
    auto rootNode = rootNodeWeak_.Upgrade();
    for (const auto& child : rootNode->GetChildren()) {
        auto node = DynamicCast<FrameNode>(child);
        if (node && node->GetTag() == V2::MENU_WRAPPER_ETS_TAG) {
            UpdateContextMenuSwitchDragPreviewBefore(node);
            ContextMenuSwitchDragPreviewAnimationProc(node, dragPreviewNode, offset);
        }
    }
}

void OverlayManager::PostDialogFinishEvent(const WeakPtr<FrameNode>& nodeWk)
{
    TAG_LOGI(AceLogTag::ACE_DIALOG, "post dialog finish event enter");
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

void OverlayManager::FireAutoSave(const RefPtr<FrameNode>& ContainerNode)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "fire auto save enter");
    CHECK_NULL_VOID(ContainerNode);
    if (!ContainerNode->NeedRequestAutoSave()) {
        return;
    }
    auto container = Container::Current();
    auto currentId = Container::CurrentId();
    CHECK_NULL_VOID(container);

    const auto& nodeTag = ContainerNode->GetTag();
    if (nodeTag == V2::SHEET_PAGE_TAG) {
        // BindSheet does not use subwindowManage. If use subwindow for display, autosave is started in the main window.
        auto layoutProperty = ContainerNode->GetLayoutProperty<SheetPresentationProperty>();
        CHECK_NULL_VOID(layoutProperty);
        auto currentStyle = layoutProperty->GetSheetStyleValue();
        if (currentStyle.instanceId.has_value()) {
            auto pattern = ContainerNode->GetPattern<SheetPresentationPattern>();
            auto targetNode = FrameNode::GetFrameNode(pattern->GetTargetTag(), pattern->GetTargetId());
            CHECK_NULL_VOID(targetNode);
            currentId = targetNode->GetInstanceId();
        }
    } else if (container->IsSubContainer()) {
        currentId = SubwindowManager::GetInstance()->GetParentContainerId(Container::CurrentId());
    }
    container->RequestAutoSave(ContainerNode, nullptr, nullptr, true, currentId);
}

void OverlayManager::OnDialogCloseEvent(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_VOID(node);
    TAG_LOGI(AceLogTag::ACE_DIALOG, "on dialog/%{public}d close event enter", node->GetId());

    BlurOverlayNode(node);
    FireAutoSave(node);

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

    auto container = Container::Current();
    auto currentId = Container::CurrentId();
    CHECK_NULL_VOID(container);
    if (isShowInSubWindow && !container->IsSubContainer()) {
        currentId = SubwindowManager::GetInstance()->GetSubContainerId(currentId);
    }

    ContainerScope scope(currentId);
    auto root = node->GetParent();
    CHECK_NULL_VOID(root);
    node->OnAccessibilityEvent(
        AccessibilityEventType::PAGE_CLOSE, WindowsContentChangeTypes::CONTENT_CHANGE_TYPE_SUBTREE);
    DeleteDialogHotAreas(node);
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "remove DialogNode/%{public}d from RootNode/%{public}d",
        node->GetId(), root->GetId());
    root->RemoveChild(node, node->GetIsUseTransitionAnimator());
    root->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);

    if (container->IsDialogContainer() || isShowInSubWindow) {
        SubwindowManager::GetInstance()->HideDialogSubWindow(currentId);
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
    MountToParentWithService(root, node);
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
    node->OnAccessibilityEvent(
        AccessibilityEventType::PAGE_OPEN, WindowsContentChangeTypes::CONTENT_CHANGE_TYPE_SUBTREE);
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
    option.SetOnFinishEvent(
        [weak = WeakClaim(this), nodeWk = WeakPtr<FrameNode>(node), dialogPattern, id = Container::CurrentId()] {
            ContainerScope scope(id);
            auto overlayManager = weak.Upgrade();
            CHECK_NULL_VOID(overlayManager);
            overlayManager->PostDialogFinishEvent(nodeWk);
            dialogPattern->CallDialogDidDisappearCallback();
        });
    auto ctx = node->GetRenderContext();
    if (!ctx) {
        TAG_LOGW(AceLogTag::ACE_OVERLAY, "not find render context when closing dialog");
        return;
    }
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
    MountToParentWithService(root, node);
    root->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    BlurLowerNode(node);
    node->OnAccessibilityEvent(
        AccessibilityEventType::PAGE_OPEN, WindowsContentChangeTypes::CONTENT_CHANGE_TYPE_SUBTREE);
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
    if (!ctx) {
        TAG_LOGW(AceLogTag::ACE_OVERLAY, "not find render context when closing dialog");
        return;
    }
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
    CHECK_NULL_VOID(menu);
    auto layoutProperty = menu->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateVisibility(VisibleType::VISIBLE, true);
}

void OverlayManager::OnShowMenuAnimationFinished(const WeakPtr<FrameNode> menuWK, const WeakPtr<OverlayManager> weak,
    int32_t instanceId)
{
    TAG_LOGI(AceLogTag::ACE_OVERLAY, "show menu animation finished");
    auto menu = menuWK.Upgrade();
    auto overlayManager = weak.Upgrade();
    CHECK_NULL_VOID(menu && overlayManager);
    ContainerScope scope(instanceId);
    auto menuNode = AceType::DynamicCast<FrameNode>(menu->GetChildAtIndex(0));
    CHECK_NULL_VOID(menuNode);
    auto menuLayoutProp = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_VOID(menuLayoutProp);
    if (!menuLayoutProp->GetIsRectInTargetValue(false)) {
        overlayManager->FocusOverlayNode(menu);
    }
    auto menuWrapperPattern = menu->GetPattern<MenuWrapperPattern>();
    menuWrapperPattern->CallMenuAppearCallback();
    if (!menuWrapperPattern->IsHide()) {
        menuWrapperPattern->SetMenuStatus(MenuStatus::SHOW);
    }
}

void OverlayManager::SetPreviewFirstShow(const RefPtr<FrameNode>& menu)
{
    CHECK_NULL_VOID(menu);
    auto wrapperPattern = menu->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(wrapperPattern);
    auto previewChild = wrapperPattern->GetPreview();
    CHECK_NULL_VOID(previewChild);
    auto previewPattern = AceType::DynamicCast<MenuPreviewPattern>(previewChild->GetPattern());
    CHECK_NULL_VOID(previewPattern);
    previewPattern->SetFirstShow();
}

void OverlayManager::ShowMenuAnimation(const RefPtr<FrameNode>& menu)
{
    TAG_LOGI(AceLogTag::ACE_OVERLAY, "show menu animation enter");
    CHECK_NULL_VOID(menu);
    BlurLowerNode(menu);
    auto wrapperPattern = menu->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(wrapperPattern);
    wrapperPattern->CallMenuAboutToAppearCallback();
    wrapperPattern->SetMenuStatus(MenuStatus::ON_SHOW_ANIMATION);
    SetIsMenuShow(true);
    ResetContextMenuDragHideFinished();
    if (wrapperPattern->HasTransitionEffect()) {
        UpdateMenuVisibility(menu);
        auto renderContext = menu->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        renderContext->SetTransitionInCallback(
            [weak = WeakClaim(this), menuWK = WeakClaim(RawPtr(menu)), id = Container::CurrentId()] {
                auto overlayManager = weak.Upgrade();
                CHECK_NULL_VOID(overlayManager);
                overlayManager->OnShowMenuAnimationFinished(menuWK, weak, id);
                overlayManager->SendToAccessibility(menuWK, true);
            });
        if (wrapperPattern->GetPreviewMode() == MenuPreviewMode::CUSTOM) {
            SetPreviewFirstShow(menu);
        }
        SetPatternFirstShow(menu);
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
            overlayManager->SendToAccessibility(menuWK, true);
        });
    if (wrapperPattern->GetPreviewMode() == MenuPreviewMode::CUSTOM) {
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        auto menuTheme = pipelineContext->GetTheme<NG::MenuTheme>();
        CHECK_NULL_VOID(menuTheme);
        option.SetDuration(menuTheme->GetContextMenuAppearDuration());
        SetPreviewFirstShow(menu);
    }
    wrapperPattern->SetAniamtinOption(option);
    SetPatternFirstShow(menu);
}

void OverlayManager::SendToAccessibility(const WeakPtr<FrameNode> node, bool isShow)
{
    auto menuWrapper = node.Upgrade();
    CHECK_NULL_VOID(menuWrapper);
    auto wrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(wrapperPattern);
    auto menu = wrapperPattern->GetMenu();
    CHECK_NULL_VOID(menu);
    auto accessibilityProperty = menu->GetAccessibilityProperty<MenuAccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    accessibilityProperty->SetAccessibilityIsShow(isShow);
    if (isShow) {
        menu->OnAccessibilityEvent(AccessibilityEventType::PAGE_OPEN,
            WindowsContentChangeTypes::CONTENT_CHANGE_TYPE_SUBTREE);
        TAG_LOGI(AceLogTag::ACE_OVERLAY, "Send event to %{public}d",
            static_cast<int32_t>(AccessibilityEventType::PAGE_OPEN));
    } else {
        menu->OnAccessibilityEvent(AccessibilityEventType::PAGE_CLOSE,
            WindowsContentChangeTypes::CONTENT_CHANGE_TYPE_SUBTREE);
        TAG_LOGI(AceLogTag::ACE_OVERLAY, "Send event to %{public}d",
            static_cast<int32_t>(AccessibilityEventType::PAGE_CLOSE));
    }
}

void OverlayManager::SetPatternFirstShow(const RefPtr<FrameNode>& menu)
{
    CHECK_NULL_VOID(menu);
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
    TAG_LOGI(AceLogTag::ACE_OVERLAY, "close menu animation finished");
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
    menuWrapperPattern->CallMenuStateChangeCallback("false");
    auto mainPipeline = PipelineContext::GetMainPipelineContext();
    if (mainPipeline && menuWrapperPattern->GetMenuDisappearCallback()) {
        ContainerScope scope(mainPipeline->GetInstanceId());
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
    auto targetId = menuWrapperPattern->GetTargetId();
    overlayManager->EraseMenuInfo(targetId);
    if (((menuWrapperPattern && menuWrapperPattern->IsContextMenu()) || (isShowInSubWindow && expandDisplay)) &&
        (menuPattern->GetTargetTag() != V2::SELECT_ETS_TAG)) {
        SubwindowManager::GetInstance()->ClearMenuNG(instanceId, menuWrapperPattern->GetTargetId());
        overlayManager->ResetContextMenuDragHideFinished();
        overlayManager->SetIsMenuShow(false);
        return;
    }
    overlayManager->RemoveMenuNotInSubWindow(menuWK, rootWeak, weak);
    overlayManager->SetIsMenuShow(false);
}

void OverlayManager::PopMenuAnimation(const RefPtr<FrameNode>& menu, bool showPreviewAnimation, bool startDrag)
{
    TAG_LOGI(AceLogTag::ACE_OVERLAY, "pop menu animation enter");
    CHECK_NULL_VOID(menu);
    auto wrapperPattern = menu->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(wrapperPattern);

    if (wrapperPattern->IsHide()) {
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
    if (wrapperPattern->HasTransitionEffect() || wrapperPattern->HasFoldModeChangedTransition()) {
        ShowMenuDisappearTransition(menu);
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
        overlayManager->SendToAccessibility(menuWK, false);
        overlayManager->OnPopMenuAnimationFinished(menuWK, rootWeak, weak, id);
    });
    ShowMenuClearAnimation(menu, option, showPreviewAnimation, startDrag);
}

void OverlayManager::ShowMenuDisappearTransition(const RefPtr<FrameNode>& menu)
{
    TAG_LOGI(AceLogTag::ACE_OVERLAY, "show menu disappear transition enter");
    CHECK_NULL_VOID(menu);
    auto wrapperPattern = menu->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(wrapperPattern);

    if (wrapperPattern->GetPreviewMode() != MenuPreviewMode::NONE) {
        ShowPreviewDisappearAnimation(wrapperPattern);
    }
    auto layoutProperty = menu->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateVisibility(VisibleType::INVISIBLE, true);
    auto renderContext = menu->GetRenderContext();

    if (wrapperPattern->HasFoldModeChangedTransition()) {
        TAG_LOGI(AceLogTag::ACE_OVERLAY, "Close menu when foldMode is changed, disappear transiton is %{public}d",
            renderContext->HasDisappearTransition());
    }

    if (renderContext->HasDisappearTransition()) {
        renderContext->SetTransitionOutCallback([rootWeak = rootNodeWeak_, menuWK = WeakClaim(RawPtr(menu)),
                                                    id = Container::CurrentId(), weak = WeakClaim(this)] {
            ContainerScope scope(id);
            auto overlayManager = weak.Upgrade();
            CHECK_NULL_VOID(overlayManager);
            overlayManager->SendToAccessibility(menuWK, false);
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
                overlayManager->SendToAccessibility(menuWK, false);
                overlayManager->OnPopMenuAnimationFinished(menuWK, rootWeak, weak, id);
            },
            TaskExecutor::TaskType::UI, "ArkUIOverlayPopMenuAnimation");
    }
}

void OverlayManager::ShowMenuClearAnimation(const RefPtr<FrameNode>& menuWrapper, AnimationOption& option,
    bool showPreviewAnimation, bool startDrag)
{
    TAG_LOGI(AceLogTag::ACE_OVERLAY, "show menuWrapper clear animation enter");
    CHECK_NULL_VOID(menuWrapper);
    auto context = menuWrapper->GetRenderContext();
    CHECK_NULL_VOID(context);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto menuWrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(menuWrapperPattern);
    auto menuAnimationOffset = menuWrapperPattern->GetAnimationOffset();
    auto outterMenu = menuWrapperPattern->GetMenu();
    CHECK_NULL_VOID(outterMenu);
    auto outterMenuPattern = outterMenu->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(outterMenuPattern);
    bool isShow = outterMenuPattern->GetDisappearAnimation();
    bool isPreviewModeNone = menuWrapperPattern->GetPreviewMode() == MenuPreviewMode::NONE;
    if (!isPreviewModeNone
        || (isPreviewModeNone && IsContextMenuBindedOnOrigNode() && !showPreviewAnimation && startDrag)) {
        if (!showPreviewAnimation) {
            CleanPreviewInSubWindow();
        } else {
            ShowPreviewDisappearAnimation(menuWrapperPattern);
        }
        ShowContextMenuDisappearAnimation(option, menuWrapperPattern, startDrag);
    } else if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE) && isShow) {
        FireMenuDisappear(option, menuWrapperPattern);
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

// check if there is a bound menu on the current floating node on the main window
bool OverlayManager::IsContextMenuBindedOnOrigNode()
{
    auto mainPipeline = PipelineContext::GetMainPipelineContext();
    CHECK_NULL_RETURN(mainPipeline, false);
    auto dragDropManager = mainPipeline->GetDragDropManager();
    CHECK_NULL_RETURN(dragDropManager, false);
    auto draggingNode = dragDropManager->GetPrepareDragFrameNode().Upgrade();
    CHECK_NULL_RETURN(draggingNode, false);
    auto eventHub = draggingNode->GetEventHub<EventHub>();
    CHECK_NULL_RETURN(eventHub, false);
    auto frameNode = eventHub->GetFrameNode();
    CHECK_NULL_RETURN(frameNode, false);
    auto focusHub = frameNode->GetFocusHub();
    CHECK_NULL_RETURN(focusHub, false);
    return focusHub->FindContextMenuOnKeyEvent(OnKeyEventType::CONTEXT_MENU);
}

void OverlayManager::ShowToast(const NG::ToastInfo& toastInfo, const std::function<void(int32_t)>& callback)
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
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    CHECK_NULL_VOID(toastNode);
    auto toastId = toastNode->GetId();
    // mount to parent
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "toast mount to root");
    toastNode->MountToParent(rootNode);
    rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    toastMap_[toastId] = toastNode;
    if (callback != nullptr && GreatOrEqual(toastId, 0)) {
        int32_t callbackToastId =
            ((static_cast<uint32_t>(toastId) << 3) | // 3 : Use the last 3 bits of callbackToastId to store showMode
                (static_cast<uint32_t>(toastInfo.showMode) & 0b111));
        callback(callbackToastId);
    }
    OpenToastAnimation(toastNode, toastInfo.duration);
    if (toastInfo.showMode == NG::ToastShowMode::DEFAULT) {
        TAG_LOGD(AceLogTag::ACE_OVERLAY, "show toast DEFAULT");
    } else if (toastInfo.showMode == NG::ToastShowMode::TOP_MOST) {
        TAG_LOGD(AceLogTag::ACE_OVERLAY, "show toast TOP_MOST");
    } else if (toastInfo.showMode == NG::ToastShowMode::SYSTEM_TOP_MOST) {
        TAG_LOGD(AceLogTag::ACE_OVERLAY, "show toast SYSTEM_TOP_MOST");
    }
}

void OverlayManager::CloseToast(int32_t toastId, const std::function<void(int32_t)>& callback)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "close toast enter");
    if (!callback) {
        TAG_LOGE(AceLogTag::ACE_OVERLAY, "Parameters of CloseToast are incomplete because of no callback.");
        return;
    }
    auto rootNode = rootNodeWeak_.Upgrade();
    if (!rootNode) {
        callback(ERROR_CODE_INTERNAL_ERROR);
        return;
    }
    for (auto [id, toastNodeWeak] : toastMap_) {
        if (id == toastId) {
            rootNode->RemoveChild(toastNodeWeak.Upgrade());
            rootNode->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
            toastMap_.erase(id);
            callback(ERROR_CODE_NO_ERROR);
            return;
        }
    }
    callback(ERROR_CODE_TOAST_NOT_FOUND);
}

void OverlayManager::OpenToastAnimation(const RefPtr<FrameNode>& toastNode, int32_t duration)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "open toast animation enter");
    auto toastId = toastNode->GetId();
    AnimationOption option;
    auto curve = AceType::MakeRefPtr<CubicCurve>(0.2f, 0.0f, 0.1f, 1.0f);
    option.SetCurve(curve);
    option.SetDuration(TOAST_ANIMATION_DURATION);
    option.SetFillMode(FillMode::FORWARDS);
    duration = std::max(duration, AceApplicationInfo::GetInstance().GetBarrierfreeDuration());
    continuousTask_.Reset([weak = WeakClaim(this), toastId, duration, id = Container::CurrentId()]() {
        auto overlayManager = weak.Upgrade();
        if (overlayManager) {
            ContainerScope scope(id);
            overlayManager->PopToast(toastId);
        } else {
            TAG_LOGW(AceLogTag::ACE_OVERLAY, "Can not get overlayManager, pop toast failed");
        }
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
    auto toastProperty = toastNode->GetLayoutProperty<ToastLayoutProperty>();
    CHECK_NULL_VOID(toastProperty);
    toastProperty->SetSelectStatus(ToastLayoutProperty::SelectStatus::ON);
    toastNode->OnAccessibilityEvent(
        AccessibilityEventType::PAGE_OPEN, WindowsContentChangeTypes::CONTENT_CHANGE_TYPE_SUBTREE);
}

void OverlayManager::PopToast(int32_t toastId)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "pop toast enter");
    AnimationOption option;
    auto curve = AceType::MakeRefPtr<CubicCurve>(0.2f, 0.0f, 0.1f, 1.0f);
    option.SetCurve(curve);
    option.SetDuration(TOAST_ANIMATION_DURATION);
    option.SetFillMode(FillMode::FORWARDS);
    // OnFinishEvent should be executed in UI thread.
    option.SetOnFinishEvent([weak = WeakClaim(this), toastId] {
        TAG_LOGD(AceLogTag::ACE_OVERLAY, "start toast exit finish event");
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
        TAG_LOGI(AceLogTag::ACE_OVERLAY, "toast remove from root");
        rootNode->RemoveChild(toastUnderPop);
        overlayManager->toastMap_.erase(toastId);
        rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);

        auto container = Container::Current();
        CHECK_NULL_VOID(container);
        if (container->IsDialogContainer() || (container->IsSubContainer() && rootNode->GetChildren().empty())) {
            auto pattern = toastUnderPop->GetPattern<ToastPattern>();
            CHECK_NULL_VOID(pattern);
            auto toastInfo = pattern->GetToastInfo();
            // hide window when toast show in subwindow.
            if (toastInfo.showMode == NG::ToastShowMode::SYSTEM_TOP_MOST) {
                SubwindowManager::GetInstance()->HideSystemTopMostWindow();
            } else {
                SubwindowManager::GetInstance()->HideToastSubWindowNG();
            }
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
    auto toastProperty = toastUnderPop->GetLayoutProperty<ToastLayoutProperty>();
    CHECK_NULL_VOID(toastProperty);
    toastProperty->SetSelectStatus(ToastLayoutProperty::SelectStatus::OFF);
    toastUnderPop->OnAccessibilityEvent(
        AccessibilityEventType::PAGE_CLOSE, WindowsContentChangeTypes::CONTENT_CHANGE_TYPE_SUBTREE);
}

void OverlayManager::ClearToastInSubwindow()
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "clear toast in subwindow enter");
    SubwindowManager::GetInstance()->ClearToastInSubwindow();
    SubwindowManager::GetInstance()->ClearToastInSystemSubwindow();
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
            if (finish) {
                finish();
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
        MountToParentWithService(rootNode, popupNode);
    }

    // attach popupNode before entering animation
    popupNode->GetEventHub<BubbleEventHub>()->FireChangeEvent(true);
    rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    popupMap_[targetId].isCurrentOnShow = true;

    auto popupPattern = popupNode->GetPattern<BubblePattern>();
    CHECK_NULL_VOID(popupPattern);
    popupPattern->AddPipelineCallBack();
    popupPattern->SetInteractiveDismiss(interactiveDismiss);
    popupPattern->UpdateOnWillDismiss(move(onWillDismiss));
    if ((isTypeWithOption && !isShowInSubWindow) ||
        (!Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN) && isUseCustom && popupInfo.focusable)) {
        ShowPopupAnimation(popupNode);
    } else {
        ShowPopupAnimationNG(popupNode);
    }
    SetPopupHotAreas(popupNode);
    auto accessibilityProperty = popupNode->GetAccessibilityProperty<BubbleAccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    accessibilityProperty->SetShowedState(1);
    popupNode->OnAccessibilityEvent(
        AccessibilityEventType::PAGE_OPEN, WindowsContentChangeTypes::CONTENT_CHANGE_TYPE_SUBTREE);
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
            auto parentWindowRect = popupPattern->GetHostWindowRect();
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

    auto pipeline = rootNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    const auto& rootChildren = rootNode->GetChildren();
    auto iter = std::find(rootChildren.rbegin(), rootChildren.rend(), popupNode);
    // There is no overlay under the root node or it is not in atomicservice
    if (iter == rootChildren.rend() && !pipeline->GetInstallationFree()) {
        popupMap_[targetId].isCurrentOnShow = false;
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
    auto accessibilityProperty = popupNode->GetAccessibilityProperty<BubbleAccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    accessibilityProperty->SetShowedState(0);
    popupNode->OnAccessibilityEvent(
        AccessibilityEventType::PAGE_CLOSE, WindowsContentChangeTypes::CONTENT_CHANGE_TYPE_SUBTREE);
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
        overlayManager->RemoveChildWithService(rootNode, popupNode);
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
        popupPattern->CallDoubleBindCallback("false");
    };
    HidePopupAnimation(popupNode, onFinish);
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
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "remove indexer popup by id enter");
    if (customPopupMap_.empty()) {
        return;
    }
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_VOID(rootNode);
    auto iter = customPopupMap_.find(targetId);
    if (iter != customPopupMap_.end()) {
        RemoveChildWithService(rootNode, iter->second);
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
        RemoveChildWithService(rootNode, popupNode);
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
    auto tempPopupMap = popupMap_;
    for (const auto& popup : tempPopupMap) {
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
        auto accessibilityProperty = popupNode->GetAccessibilityProperty<BubbleAccessibilityProperty>();
        CHECK_NULL_VOID(accessibilityProperty);
        accessibilityProperty->SetShowedState(0);
        popupNode->OnAccessibilityEvent(
            AccessibilityEventType::PAGE_CLOSE, WindowsContentChangeTypes::CONTENT_CHANGE_TYPE_SUBTREE);
        if (isShowInSubWindow) {
            auto subwindowMgr = SubwindowManager::GetInstance();
            subwindowMgr->DeleteHotAreas(Container::CurrentId(), popupNode->GetId());
        }
        RemoveChildWithService(rootNode, popupNode);
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
    TAG_LOGI(AceLogTag::ACE_OVERLAY, "show menu helper enter");
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
    TAG_LOGI(AceLogTag::ACE_OVERLAY, "show menu enter");
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
        MountToParentWithService(rootNode, menu);
        rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        menu->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        ShowMenuAnimation(menu);
        menu->MarkModifyDone();
    }
}

// subwindow only contains one menu instance.
void OverlayManager::ShowMenuInSubWindow(int32_t targetId, const NG::OffsetF& offset, RefPtr<FrameNode> menu)
{
    TAG_LOGI(AceLogTag::ACE_OVERLAY, "show menu insubwindow enter");
    if (!ShowMenuHelper(menu, targetId, offset)) {
        TAG_LOGW(AceLogTag::ACE_OVERLAY, "show menu helper failed");
        return;
    }
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_VOID(rootNode);

    std::vector<int32_t> idsNeedClean;
    for (auto child: rootNode->GetChildren()) {
        idsNeedClean.push_back(child->GetId());
    }
    auto pipeline = rootNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->AddAfterLayoutTask([idsNeedClean, containerId = Container::CurrentId()] {
        auto subwindowMgr = SubwindowManager::GetInstance();
        for (auto child : idsNeedClean) {
            subwindowMgr->DeleteHotAreas(containerId, child);
        }
    });
    hasDragPixelMap_ ? RemoveMenuWrapperNode(rootNode) : rootNode->Clean();

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
    pipeline->FlushUITasks();

    // set subwindow container id in menu.
    auto menuPattern = menu->GetPattern<PopupBasePattern>();
    CHECK_NULL_VOID(menuPattern);
    menuPattern->SetContainerId(Container::CurrentId());
}

void OverlayManager::HideMenuInSubWindow(const RefPtr<FrameNode>& menu, int32_t targetId)
{
    TAG_LOGI(AceLogTag::ACE_OVERLAY, "hide menu insubwindow enter");
    CHECK_NULL_VOID(menu);
    if (menu && menu->GetTag() == V2::MENU_WRAPPER_ETS_TAG) {
        auto wrapperPattern = menu->GetPattern<MenuWrapperPattern>();
        CHECK_NULL_VOID(wrapperPattern);
        wrapperPattern->UpdateMenuAnimation(menu);
    }
    PopMenuAnimation(menu);
}

void OverlayManager::HideMenuInSubWindow(bool showPreviewAnimation, bool startDrag)
{
    TAG_LOGI(AceLogTag::ACE_OVERLAY, "hide menu insubwindow enter");
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
    TAG_LOGI(AceLogTag::ACE_OVERLAY, "hide menu enter");
    PopMenuAnimation(menu);
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
    TAG_LOGI(AceLogTag::ACE_OVERLAY, "hide all menus enter");
    auto container = Container::Current();
    if (container && container->IsScenceBoardWindow()) {
        for (const auto& windowScene : windowSceneSet_) {
            if (!windowScene.Upgrade()) {
                continue;
            }
            for (const auto& child : windowScene.Upgrade()->GetChildren()) {
                auto node = DynamicCast<FrameNode>(child);
                if (node && node->GetTag() == V2::MENU_WRAPPER_ETS_TAG) {
                    TAG_LOGI(AceLogTag::ACE_OVERLAY, "will hide menu, menuNode id %{public}d", node->GetId());
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
            auto wrapperPattern = node->GetPattern<MenuWrapperPattern>();
            CHECK_NULL_VOID(wrapperPattern);
            wrapperPattern->UpdateMenuAnimation(node);
            TAG_LOGI(AceLogTag::ACE_OVERLAY, "will hide menu, menuNode id %{public}d", node->GetId());
            PopMenuAnimation(node);
        }
    }
}

void OverlayManager::DeleteMenu(int32_t targetId)
{
    TAG_LOGI(AceLogTag::ACE_OVERLAY, "delete menu enter");
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
    if (menu->GetTag() == V2::MENU_WRAPPER_ETS_TAG) {
        auto wrapperPattern = menu->GetPattern<MenuWrapperPattern>();
        CHECK_NULL_VOID(wrapperPattern);
        wrapperPattern->UpdateMenuAnimation(menu);
    }
    PopMenuAnimation(menu);
}

void OverlayManager::CleanHoverImagePreviewInSubWindow(const RefPtr<FrameNode>& flexNode)
{
    CHECK_NULL_VOID(flexNode && flexNode->GetTag() == V2::FLEX_ETS_TAG);
    for (const auto& child : flexNode->GetChildren()) {
        auto node = DynamicCast<FrameNode>(child);
        CHECK_NULL_VOID(node && node->GetTag() == V2::STACK_ETS_TAG);

        auto previewNode = node->GetLastChild();
        if (previewNode && previewNode->GetTag() == V2::MENU_PREVIEW_ETS_TAG) {
            node->RemoveChild(previewNode);
        }

        auto imageNode = node->GetFirstChild();
        if (imageNode && imageNode->GetTag() == V2::IMAGE_ETS_TAG) {
            node->RemoveChild(imageNode);
        }

        flexNode->RemoveChild(node);
        flexNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        break;
    }
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
                if (frameNode && (frameNode->GetTag() == V2::FLEX_ETS_TAG ||
                    frameNode->GetTag() == V2::MENU_PREVIEW_ETS_TAG || frameNode->GetTag() == V2::IMAGE_ETS_TAG)) {
                    CleanHoverImagePreviewInSubWindow(frameNode);
                    auto imagelayoutProperty = frameNode->GetLayoutProperty();
                    if (imagelayoutProperty) {
                        imagelayoutProperty->UpdateVisibility(VisibleType::GONE);
                    } else {
                        TAG_LOGW(AceLogTag::ACE_OVERLAY, "Preview image failed to set invisible.");
                    }
                    break;
                }
            }
            break;
        }
    }
}

void OverlayManager::CleanMenuInSubWindow(int32_t targetId)
{
    TAG_LOGI(AceLogTag::ACE_OVERLAY, "clean menu insubwindow enter");
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
            if (frameNode && (frameNode->GetTag() == V2::FLEX_ETS_TAG ||
                frameNode->GetTag() == V2::MENU_PREVIEW_ETS_TAG || frameNode->GetTag() == V2::IMAGE_ETS_TAG)) {
                CleanHoverImagePreviewInSubWindow(frameNode);
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
    std::vector<int32_t> targetList;
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
                targetList.emplace_back(target);
            }
            break;
        }
    }
    for (const auto& target : targetList) {
        auto removeNode = GetPopupInfo(target).popupNode;
        CHECK_NULL_VOID(removeNode);
        auto bubblePattern = removeNode->GetPattern<BubblePattern>();
        CHECK_NULL_VOID(bubblePattern);
        if (bubblePattern->HasOnWillDismiss()) {
            SetDismissPopupId(target);
            bubblePattern->CallOnWillDismiss(static_cast<int32_t>(DismissReason::TOUCH_OUTSIDE));
        } else {
            rootNode->RemoveChild(removeNode);
            auto subwindowMgr = SubwindowManager::GetInstance();
            subwindowMgr->DeleteHotAreas(Container::CurrentId(), removeNode->GetId());
            ErasePopupInfo(target);
        }
    }
    rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void OverlayManager::BeforeShowDialog(const RefPtr<FrameNode>& node)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "before show dialog");
    CHECK_NULL_VOID(node);
    if (dialogMap_.find(node->GetId()) != dialogMap_.end()) {
        TAG_LOGW(AceLogTag::ACE_OVERLAY, "dialog %{public}d already in dialog map", node->GetId());
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
        if (!customNode) {
            TAG_LOGE(AceLogTag::ACE_OVERLAY, "fail to build customNode");
            return nullptr;
        }
    }

    auto dialog = DialogView::CreateDialogNode(dialogProps, customNode);
    if (!dialog) {
        TAG_LOGE(AceLogTag::ACE_OVERLAY, "fail to create dialog node");
        return nullptr;
    }
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

RefPtr<UINode> OverlayManager::RebuildCustomBuilder(RefPtr<UINode>& contentNode)
{
    auto currentId = Container::CurrentId();
    if (!(currentId >= MIN_SUBCONTAINER_ID && currentId < MIN_PLUGIN_SUBCONTAINER_ID)) {
        return contentNode;
    }

    RefPtr<UINode> customNode;
    auto lazyBuilderFunc = contentNode->GetBuilderFunc();
    if (lazyBuilderFunc) {
        NG::ScopedViewStackProcessor builderViewStackProcessor;
        lazyBuilderFunc();
        customNode = NG::ViewStackProcessor::GetInstance()->Finish();
    } else {
        customNode = contentNode;
    }

    auto updateNodeFunc = contentNode->GetUpdateNodeFunc();
    if (updateNodeFunc) {
        updateNodeFunc(currentId, customNode);
    }
    auto updateNodeConfig = contentNode->GetUpdateNodeConfig();
    if (updateNodeConfig) {
        customNode->SetUpdateNodeConfig(std::move(updateNodeConfig));
    }
    return customNode;
}

void OverlayManager::ReloadBuilderNodeConfig()
{
    if (dialogMap_.empty()) {
        return;
    }
    auto iter = dialogMap_.begin();
    while (iter != dialogMap_.end()) {
        auto dialogNode = (*iter).second;
        if (dialogNode) {
            auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
            CHECK_NULL_VOID(dialogPattern);
            auto customNode = dialogPattern->GetCustomNode();
            if (customNode && customNode->GetUpdateNodeConfig()) {
                customNode->GetUpdateNodeConfig()();
            }
        }
        iter++;
    }
}

void OverlayManager::OpenCustomDialog(const DialogProperties& dialogProps, std::function<void(int32_t)> &&callback)
{
    RefPtr<UINode> customNode;
    bool showComponentContent = false;
    if (!callback) {
        TAG_LOGE(AceLogTag::ACE_DIALOG, "Parameters of OpenCustomDialog are incomplete because of no callback.");
        return;
    }
    if (dialogProps.customBuilder) {
        TAG_LOGD(AceLogTag::ACE_DIALOG, "open custom dialog with custom builder.");
        NG::ScopedViewStackProcessor builderViewStackProcessor(Container::CurrentId());
        dialogProps.customBuilder();
        customNode = NG::ViewStackProcessor::GetInstance()->Finish();
        if (!customNode) {
            TAG_LOGE(AceLogTag::ACE_DIALOG, "Fail to build custom node.");
            callback(-1);
            return;
        }
    } else {
        auto contentNode = dialogProps.contentNode.Upgrade();
        if (!contentNode) {
            TAG_LOGE(AceLogTag::ACE_DIALOG, "Content of custom dialog is null");
            callback(ERROR_CODE_DIALOG_CONTENT_ERROR);
            return;
        }
        if (GetDialogNodeWithExistContent(contentNode)) {
            TAG_LOGW(AceLogTag::ACE_DIALOG, "Content of custom dialog already existed.");
            callback(ERROR_CODE_DIALOG_CONTENT_ALREADY_EXIST);
            return;
        }
        TAG_LOGD(AceLogTag::ACE_DIALOG, "OpenCustomDialog ComponentContent id: %{public}d", contentNode->GetId());
        customNode = RebuildCustomBuilder(contentNode);
        showComponentContent = true;
    }
    auto dialog = DialogView::CreateDialogNode(dialogProps, customNode);
    if (!dialog) {
        TAG_LOGE(AceLogTag::ACE_DIALOG, "Fail to create dialog node.");
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
            TAG_LOGE(AceLogTag::ACE_DIALOG, "not find dialog when no dialog id");
        }
    } else {
        iter = dialogMap_.find(dialogId);
        if (iter == dialogMap_.end()) {
            TAG_LOGE(AceLogTag::ACE_DIALOG, "not find dialog by id %{public}d", dialogId);
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
        TAG_LOGE(AceLogTag::ACE_DIALOG, "Parameters of CloseCustomDialog are incomplete because of no callback.");
        return;
    }
    auto contentNode = node.Upgrade();
    if (!contentNode) {
        TAG_LOGE(AceLogTag::ACE_DIALOG, "Content of custom dialog is null");
        callback(ERROR_CODE_DIALOG_CONTENT_ERROR);
        return;
    }
    TAG_LOGD(AceLogTag::ACE_DIALOG, "CloseCustomDialog ComponentContent id: %{public}d", contentNode->GetId());
    auto dialogNode = GetDialogNodeWithExistContent(contentNode);
    if (!dialogNode) {
        dialogNode = SubwindowManager::GetInstance()->GetSubwindowDialogNodeWithExistContent(contentNode);
    }
    if (dialogNode) {
        DeleteDialogHotAreas(dialogNode);
        CloseDialogInner(dialogNode);
        callback(ERROR_CODE_NO_ERROR);
        return;
    }
    TAG_LOGE(AceLogTag::ACE_DIALOG, "CloseCustomDialog failed because cannot find dialog.");
    callback(ERROR_CODE_DIALOG_CONTENT_NOT_FOUND);
}

void OverlayManager::UpdateCustomDialog(
    const WeakPtr<NG::UINode>& node, const DialogProperties& dialogProps, std::function<void(int32_t)> &&callback)
{
    if (!callback) {
        TAG_LOGE(AceLogTag::ACE_DIALOG, "Parameters of UpdateCustomDialog are incomplete because of no callback.");
        return;
    }
    auto contentNode = node.Upgrade();
    if (!contentNode) {
        TAG_LOGE(AceLogTag::ACE_DIALOG, "Content of custom dialog is null");
        callback(ERROR_CODE_DIALOG_CONTENT_ERROR);
        return;
    }
    TAG_LOGD(AceLogTag::ACE_DIALOG, "UpdateCustomDialog ComponentContent id: %{public}d", contentNode->GetId());
    auto dialogNode = GetDialogNodeWithExistContent(contentNode);
    if (!dialogNode) {
        dialogNode = SubwindowManager::GetInstance()->GetSubwindowDialogNodeWithExistContent(contentNode);
    }
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
    TAG_LOGE(AceLogTag::ACE_DIALOG, "UpdateCustomDialog failed because cannot find dialog.");
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
    auto dialogNode = CalendarDialogView::Show(dialogProps, settingData,
        buttonInfos, std::move(dialogEvent), std::move(dialogCancelEvent));
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
        TAG_LOGW(AceLogTag::ACE_OVERLAY, "not find dialog %{public}d in dialog map", node->GetId());
        return;
    }
    dialogMap_.erase(node->GetId());
}

void OverlayManager::RemoveMaskFromMap(const RefPtr<FrameNode>& dialogNode)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "remove mask from map enter");
    CHECK_NULL_VOID(dialogNode);
    if (maskNodeIdMap_.find(dialogNode->GetId()) == maskNodeIdMap_.end()) {
        TAG_LOGW(AceLogTag::ACE_OVERLAY, "not find mask dialog %{public}d in maskNodeIdMap", dialogNode->GetId());
        return;
    }
    maskNodeIdMap_.erase(dialogNode->GetId());
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

bool OverlayManager::HasModalPage()
{
    if (modalList_.empty()) {
        return false;
    }
    for (auto modal : modalList_) {
        if (modal.Upgrade() && modal.Upgrade()->GetTag() == V2::MODAL_PAGE_TAG) {
            return true;
        }
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
        } else {
            TAG_LOGD(AceLogTag::ACE_OVERLAY, "no maskNode in currentDialog/%{public}d", dialogNode->GetId());
        }
    }
    CloseDialogInner(dialogNode);
}

void OverlayManager::DeleteDialogHotAreas(const RefPtr<FrameNode>& dialogNode)
{
    auto dialogLayoutProp = AceType::DynamicCast<DialogLayoutProperty>(dialogNode->GetLayoutProperty());
    CHECK_NULL_VOID(dialogLayoutProp);
    if (dialogLayoutProp->GetShowInSubWindowValue(false)) {
        auto container = Container::Current();
        CHECK_NULL_VOID(container);
        auto currentId = Container::CurrentId();
        if (!container->IsSubContainer()) {
            currentId = SubwindowManager::GetInstance()->GetSubContainerId(currentId);
        }

        SubwindowManager::GetInstance()->DeleteHotAreas(currentId, dialogNode->GetId());
        SubwindowManager::GetInstance()->HideDialogSubWindow(currentId);
    }
}

void OverlayManager::CloseDialogInner(const RefPtr<FrameNode>& dialogNode)
{
    RemoveDialogFromMap(dialogNode);
    if (dialogNode->IsRemoving()) {
        // already in close animation
        TAG_LOGW(AceLogTag::ACE_DIALOG, "dialogNode/%{public}d is removing", dialogNode->GetId());
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
    overlayManager->RemoveMaskFromMap(dialogNode);
    // set close button enable
    if (dialogCount_ == 0) {
        SetContainerButtonEnable(true);
    }
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
    TAG_LOGI(AceLogTag::ACE_OVERLAY, "remove menu enter");
    CHECK_NULL_RETURN(overlay, false);
    auto menuWrapperPattern = overlay->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_RETURN(menuWrapperPattern, false);
    menuWrapperPattern->UpdateMenuAnimation(overlay);
    menuWrapperPattern->HideMenu();
    return true;
}

bool OverlayManager::RemoveDragPreview(const RefPtr<FrameNode>& overlay)
{
    TAG_LOGI(AceLogTag::ACE_OVERLAY, "remove dragPreview enter");
    auto columnNode = pixmapColumnNodeWeak_.Upgrade();
    if (columnNode != overlay) {
        return false;
    }
    RemoveEventColumn();
    RemovePixelMap();
    RemoveGatherNode();
    return true;
}

void OverlayManager::SetIsMenuShow(bool isMenuShow)
{
    isMenuShow_ = isMenuShow;
    // notify drag manager the menu show status
    DragDropGlobalController::GetInstance().UpdateMenuShowingStatus(isMenuShow);
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

int32_t OverlayManager::RemoveOverlayCommon(const RefPtr<NG::UINode>& rootNode, RefPtr<NG::FrameNode>& overlay,
    RefPtr<Pattern>& pattern, bool isBackPressed, bool isPageRouter)
{
    const size_t size = rootNode->GetChildren().size();
    if (size == 0) {
        return OVERLAY_EXISTS;
    }
    auto currentIndex = size - 1;
    while (InstanceOf<ToastPattern>(pattern)) {
        // still have nodes on root expect stage and toast node.
        if (currentIndex > 0) {
            currentIndex = currentIndex - 1;
            overlay = DynamicCast<FrameNode>(rootNode->GetChildAtIndex(currentIndex));
            CHECK_NULL_RETURN(overlay, OVERLAY_EXISTS);
            pattern = overlay->GetPattern();
        } else {
            return OVERLAY_EXISTS;
        }
    }
    CHECK_EQUAL_RETURN(overlay->GetTag(), V2::STAGE_ETS_TAG, OVERLAY_EXISTS);
    CHECK_EQUAL_RETURN(overlay->GetTag(), V2::OVERLAY_ETS_TAG, OVERLAY_EXISTS);
    CHECK_EQUAL_RETURN(overlay->GetTag(), V2::ATOMIC_SERVICE_ETS_TAG, OVERLAY_EXISTS);
    // close dialog with animation
    if (InstanceOf<DialogPattern>(pattern)) {
        if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE) && isPageRouter) {
            return OVERLAY_EXISTS;
        }
        auto dialogPattern = DynamicCast<DialogPattern>(pattern);
        CHECK_NULL_RETURN(dialogPattern, OVERLAY_EXISTS);
        if (dialogPattern->CallDismissInNDK(static_cast<int32_t>(DialogDismissReason::DIALOG_PRESS_BACK))) {
            return OVERLAY_REMOVE;
        } else if (dialogPattern->ShouldDismiss()) {
            SetDismissDialogId(overlay->GetId());
            auto currentId = Container::CurrentId();
            dialogPattern->CallOnWillDismiss(static_cast<int32_t>(DialogDismissReason::DIALOG_PRESS_BACK), currentId);
            TAG_LOGI(AceLogTag::ACE_OVERLAY, "Dialog Should Dismiss, currentId: %{public}d", currentId);
            return OVERLAY_REMOVE;
        }
        return RemoveDialog(overlay, isBackPressed, isPageRouter) ? OVERLAY_REMOVE : OVERLAY_EXISTS;
    }
    if (InstanceOf<BubblePattern>(pattern)) {
        return RemoveBubble(overlay) ? OVERLAY_REMOVE : OVERLAY_EXISTS;
    }
    if (InstanceOf<MenuWrapperPattern>(pattern)) {
        SetDragNodeNeedClean();
        RemoveDragPreview(overlay);
        return RemoveMenu(overlay) ? OVERLAY_REMOVE : OVERLAY_EXISTS;
    }
    if (InstanceOf<LinearLayoutPattern>(pattern)) {
        return RemoveDragPreview(overlay) ? OVERLAY_REMOVE : OVERLAY_NOTHING;
    }
    return OVERLAY_NOTHING;
}

bool OverlayManager::RemoveOverlay(bool isBackPressed, bool isPageRouter)
{
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_RETURN(rootNode, true);
    RemoveIndexerPopup();
    SetDragNodeNeedClean();
    auto pipeline = rootNode->GetContextRefPtr();
    CHECK_NULL_RETURN(pipeline, false);
    // There is overlay under the root node or it is in atomicservice
    if (rootNode->GetChildren().size() > ROOT_MIN_NODE || pipeline->GetInstallationFree()) {
        // stage node is at index 0, remove overlay at last
        auto overlay = GetLastChildNotRemoving(rootNode);
        CHECK_NULL_RETURN(overlay, false);
        auto pattern = overlay->GetPattern();
        auto ret = RemoveOverlayCommon(rootNode, overlay, pattern, isBackPressed, isPageRouter);
        if (ret == OVERLAY_REMOVE) {
            return true;
        } else if (ret == OVERLAY_EXISTS) {
            return false;
        }
        ret = ExceptComponent(rootNode, overlay, isBackPressed, isPageRouter);
        if (ret == OVERLAY_REMOVE) {
            return true;
        } else if (ret == OVERLAY_EXISTS) {
            return false;
        }
        // remove navDestination in navigation first
        do {
            CHECK_NULL_BREAK(rootNode->GetTag() != V2::NAVDESTINATION_VIEW_ETS_TAG);
            bool isEntry = false;
            auto navigationGroupNode =
                AceType::DynamicCast<NavigationGroupNode>(pipeline->FindNavigationNodeToHandleBack(overlay, isEntry));
            CHECK_NULL_BREAK(navigationGroupNode);
            return true;
        } while (0);
        if (!modalStack_.empty()) {
            TAG_LOGI(AceLogTag::ACE_SHEET, "Modal consumed backpressed event");
            if (isPageRouter) {
                return RemoveAllModalInOverlay();
            } else {
                return RemoveModalInOverlay();
            }
        }
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

RefPtr<FrameNode> OverlayManager::GetOverlayFrameNode()
{
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_RETURN(rootNode, nullptr);
    auto pipeline = rootNode->GetContextRefPtr();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto overlay = DynamicCast<FrameNode>(rootNode->GetLastChild());
    // There is no overlay under the root node or it is not in atomicservice
    if (!pipeline->GetInstallationFree() || rootNode->GetChildren().size() > ROOT_MIN_NODE) {
        return overlay;
    }
    for (auto child : rootNode->GetChildren()) {
        if (child->GetTag() == V2::ATOMIC_SERVICE_ETS_TAG) {
            auto atomicNode = child;
            CHECK_NULL_RETURN(atomicNode, nullptr);
            if (atomicNode->GetChildren().size() <= ATOMIC_SERVICE_MIN_SIZE) {
                return nullptr;
            }
            overlay = DynamicCast<FrameNode>(
                atomicNode->GetChildAtIndex(atomicNode->GetChildren().size() - ATOMIC_SERVICE_MIN_SIZE));
            break;
        }
    }
    return overlay;
}

int32_t OverlayManager::ExceptComponent(const RefPtr<NG::UINode>& rootNode, RefPtr<NG::FrameNode>& overlay,
    bool isBackPressed, bool isPageRouter)
{
    auto pattern = overlay->GetPattern();
    if (InstanceOf<VideoFullScreenPattern>(pattern)) {
        auto videoPattern = DynamicCast<VideoFullScreenPattern>(pattern);
        CHECK_NULL_RETURN(videoPattern, OVERLAY_EXISTS);
        return videoPattern->ExitFullScreen() ? OVERLAY_REMOVE : OVERLAY_EXISTS;
    }
    // OVERLAY_REMOVE if popup was removed, OVERLAY_NOTHING if not handle it
    if (overlay->GetTag() == V2::SHEET_WRAPPER_TAG) {
        return WebBackward(overlay);
    }
    return OVERLAY_NOTHING;
}

int32_t OverlayManager::WebBackward(RefPtr<NG::FrameNode>& overlay)
{
#ifdef WEB_SUPPORTED
    RefPtr<NG::FrameNode> webNode;
    bool isNavDestination = false;
    FindWebNode(overlay, webNode, isNavDestination);
    if (webNode && InstanceOf<WebPattern>(webNode->GetPattern())) {
        auto webPattern = DynamicCast<WebPattern>(webNode->GetPattern());
        CHECK_NULL_RETURN(webPattern, OVERLAY_EXISTS);
        if (webPattern->Backward() && !isNavDestination) {
            return OVERLAY_REMOVE;
        }
    }
#endif
    return OVERLAY_NOTHING;
}

void OverlayManager::FindWebNode(const RefPtr<NG::UINode>& node, RefPtr<NG::FrameNode>& webNode,
    bool& isNavDestination)
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

    if (frameNode && frameNode->GetTag() == V2::NAVDESTINATION_VIEW_ETS_TAG && !isNavDestination) {
        isNavDestination = true;
        TAG_LOGI(AceLogTag::ACE_OVERLAY, "find NavDestination node.");
    }

    if (!node->GetChildren().empty()) {
        for (const auto& child : node->GetChildren()) {
            FindWebNode(child, webNode, isNavDestination);
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
        sheetPattern->SheetInteractiveDismiss(BindSheetDismissReason::BACK_PRESSED);
        return true;
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
        sheetMap_.erase(sheetPattern->GetSheetKey());
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

bool OverlayManager::RemoveAllModalInOverlay(bool isRouterTransition)
{
    if (modalStack_.empty()) {
        return true;
    }
    if (!isRouterTransition) {
        return true;
    }
    auto topModalNode = modalStack_.top().Upgrade();
    bool isModalUiextensionNode = IsModalUiextensionNode(topModalNode);
    bool isProhibitedRemoveByRouter = IsProhibitedRemoveByRouter(topModalNode);
    TAG_LOGI(AceLogTag::ACE_OVERLAY,
        "isModalUiextensionNode: %{public}d, isProhibitedRemoveByRouter: %{public}d,",
        isModalUiextensionNode, isProhibitedRemoveByRouter);
    if (isModalUiextensionNode && isProhibitedRemoveByRouter) {
        return RemoveAllModalInOverlayByList();
    }

    return RemoveAllModalInOverlayByStack();
}

bool OverlayManager::RemoveAllModalInOverlayByStack()
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
            sheetMap_.erase(sheetPattern->GetSheetKey());
        }
        FireModalPageHide();
        SaveLastModalNode();
    }
    return true;
}

bool OverlayManager::RemoveAllModalInOverlayByList()
{
    TAG_LOGI(AceLogTag::ACE_OVERLAY,
        "RemoveAllModalInOverlayByList modalStack size: %{public}zu, "
        "modalList size: %{public}zu", modalStack_.size(), modalList_.size());
    if (modalStack_.size() != modalList_.size()) {
        TAG_LOGI(AceLogTag::ACE_OVERLAY,
            "Not RemoveAllModalInOverlayByList due to modalStack not same with modalList.");
        return true;
    }

    bool ret = OnRemoveAllModalInOverlayByList();
    // To keep the modalStack consistent with the modalList
    AfterRemoveAllModalInOverlayByList();
    return ret;
}

bool OverlayManager::OnRemoveAllModalInOverlayByList()
{
    auto modalIter = modalList_.begin();
    while (modalIter != modalList_.end()) {
        auto topModalNode = (*modalIter).Upgrade();
        if (!topModalNode) {
            modalIter = modalList_.erase(modalIter);
            continue;
        }
        if (IsModalUiextensionNode(topModalNode)) {
            break;
        }
        auto rootNode = FindWindowScene(topModalNode);
        CHECK_NULL_RETURN(rootNode, true);
        auto builder = AceType::DynamicCast<FrameNode>(topModalNode->GetFirstChild());
        CHECK_NULL_RETURN(builder, false);
        ModalPageLostFocus(topModalNode);
        if (!ModalExitProcess(topModalNode)) {
            modalIter = modalList_.erase(modalIter);
            continue;
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
            sheetMap_.erase(sheetPattern->GetSheetKey());
        }
        modalIter = modalList_.erase(modalIter);
    }
    return true;
}

void OverlayManager::AfterRemoveAllModalInOverlayByList()
{
    TAG_LOGI(AceLogTag::ACE_OVERLAY,
        "AfterRemoveAllModalInOverlayByList modalList size: %{public}zu", modalList_.size());
    std::stack<WeakPtr<FrameNode>> modalStack;
    modalStack_.swap(modalStack);
    for (auto modal = modalList_.begin(); modal != modalList_.end(); ++modal) {
        modalStack_.push(*modal);
    }
}

bool OverlayManager::IsModalUiextensionNode(const RefPtr<FrameNode>& topModalNode)
{
    if (topModalNode == nullptr) {
        TAG_LOGI(AceLogTag::ACE_OVERLAY, "topModalNode is null,");
        return false;
    }

    if (topModalNode->GetTag() != V2::MODAL_PAGE_TAG) {
        TAG_LOGI(AceLogTag::ACE_OVERLAY, "topModalNode is not modalPage");
        return false;
    }

    auto modalPattern = topModalNode->GetPattern<ModalPresentationPattern>();
    CHECK_NULL_RETURN(modalPattern, false);
    return modalPattern->IsUIExtension();
}

bool OverlayManager::IsProhibitedRemoveByRouter(const RefPtr<FrameNode>& topModalNode)
{
    if (topModalNode == nullptr) {
        TAG_LOGI(AceLogTag::ACE_OVERLAY, "topModalNode is null,");
        return false;
    }

    if (topModalNode->GetTag() != V2::MODAL_PAGE_TAG) {
        TAG_LOGI(AceLogTag::ACE_OVERLAY, "topModalNode is not modalPage");
        return false;
    }

    auto modalPattern = topModalNode->GetPattern<ModalPresentationPattern>();
    CHECK_NULL_RETURN(modalPattern, false);
    return modalPattern->IsProhibitedRemoveByRouter();
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
        FireAutoSave(topModalNode);
        RemoveChildWithService(rootNode, topModalNode);
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
                overlayManager->FireAutoSave(modal);
                overlayManager->RemoveChildWithService(root, modal);
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
    topModalNode->OnAccessibilityEvent(
        AccessibilityEventType::PAGE_CLOSE, WindowsContentChangeTypes::CONTENT_CHANGE_TYPE_SUBTREE);
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
        FireAutoSave(topModalNode);
        RemoveChildWithService(rootNode, topModalNode);
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
        PlaySheetMaskTransition(maskNode, false);
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
    auto overlay = GetLastChildNotRemoving(rootNode);
    CHECK_NULL_RETURN(overlay, false);
    auto pattern = overlay->GetPattern();
    auto ret = RemoveOverlayCommon(rootNode, overlay, pattern, false, false);
    if (ret == OVERLAY_EXISTS) {
        return false;
    } else if (ret == OVERLAY_REMOVE) {
        return true;
    }
    rootNode->RemoveChild(overlay);
    rootNode->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
    if (rootNode->GetChildren().empty()) {
        SubwindowManager::GetInstance()->HideSubWindowNG();
    }
    if (InstanceOf<KeyboardPattern>(pattern)) {
        FocusHub::LostFocusToViewRoot();
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
    CHECK_NULL_VOID(lastPage);
    auto pagePattern = lastPage->GetPattern<PagePattern>();
    bool notTriggerNavigationStateChange = show && pagePattern && !pagePattern->IsOnShow();
    if (notTriggerNavigationStateChange) {
        // navdestination will not fire onShow When parent page is hide.
        return;
    }
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
        auto targetModalNode = GetModal(targetId);
        if (targetModalNode) {
            const auto& targetModalPattern = targetModalNode->GetPattern<ModalPresentationPattern>();
            CHECK_NULL_VOID(targetModalPattern);
            auto modalRenderContext = targetModalNode->GetRenderContext();
            CHECK_NULL_VOID(modalRenderContext);
            if (modalStyle.backgroundColor.has_value()) {
                modalRenderContext->UpdateBackgroundColor(modalStyle.backgroundColor.value());
            }
            targetModalPattern->UpdateOnDisappear(std::move(onDisappear));
            targetModalPattern->UpdateOnWillDisappear(std::move(onWillDisappear));
            targetModalPattern->UpdateOnAppear(std::move(onAppear));
            targetModalPattern->UpdateOnWillDismiss(std::move(contentCoverParam.onWillDismiss));
            targetModalPattern->SetType(modalTransition.value());
            targetModalPattern->SetHasTransitionEffect(contentCoverParam.transitionEffect != nullptr);
            modalRenderContext->UpdateChainedTransition(contentCoverParam.transitionEffect);
            return;
        }
        if (onWillAppear) {
            onWillAppear();
        }
        HandleModalShow(std::move(callback), std::move(buildNodeFunc), modalStyle, std::move(onAppear),
            std::move(onDisappear), std::move(onWillDisappear), rootNode, contentCoverParam, targetId, modalTransition);
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
    auto buildNode = buildNodeFunc();
    CHECK_NULL_VOID(buildNode);
    auto builder = AceType::DynamicCast<FrameNode>(buildNode->GetFrameChildByIndex(0, true));
    CHECK_NULL_VOID(builder);
    builder->GetRenderContext()->SetIsModalRootNode(true);

    // create modal page
    auto modalNode = FrameNode::CreateFrameNode(V2::MODAL_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<ModalPresentationPattern>(
            targetId, static_cast<ModalTransition>(modalTransition.value()), std::move(callback)));
    CHECK_NULL_VOID(modalNode);
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
    modalPagePattern->SetProhibitedRemoveByRouter(modalStyle.prohibitedRemoveByRouter);
    modalPagePattern->SetHasTransitionEffect(contentCoverParam.transitionEffect != nullptr);
    modalNode->GetRenderContext()->UpdateChainedTransition(contentCoverParam.transitionEffect);
    modalStack_.push(WeakClaim(RawPtr(modalNode)));
    modalList_.emplace_back(WeakClaim(RawPtr(modalNode)));
    SaveLastModalNode();
    if (targetId < 0) {
        // modaluiextention node mounting
        modalNode->MountToParent(rootNode, DEFAULT_NODE_SLOT, false, false, true);
    } else {
        MountToParentWithService(rootNode, modalNode);
    }
    modalNode->AddChild(builder);
    auto modalNodeParent = modalNode->GetParent();
    CHECK_NULL_VOID(modalNodeParent);
    if (!isAllowedBeCovered_) {
        TAG_LOGI(AceLogTag::ACE_OVERLAY,
            "modalNode->GetParent() %{public}d mark IsProhibitedAddChildNode when sessionId %{public}d,"
            "prohibitedRemoveByRouter: %{public}d, isAllowAddChildBelowModalUec: %{public}d.",
            modalNodeParent->GetId(), targetId, modalStyle.prohibitedRemoveByRouter,
            modalStyle.isAllowAddChildBelowModalUec);
        if (AddCurSessionId(targetId)) {
            modalNodeParent->UpdateModalUiextensionCount(true);
            modalNode->SetIsAllowAddChildBelowModalUec(modalStyle.isAllowAddChildBelowModalUec);
        }
    }

    FireModalPageShow();
    modalNodeParent->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
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
    modalNode->OnAccessibilityEvent(
        AccessibilityEventType::PAGE_OPEN, WindowsContentChangeTypes::CONTENT_CHANGE_TYPE_SUBTREE);
    if (modalTransition == ModalTransition::DEFAULT) {
        PlayDefaultModalTransition(modalNode, true);
    } else if (modalTransition == ModalTransition::ALPHA) {
        PlayAlphaModalTransition(modalNode, true);
    }
}

void OverlayManager::HandleModalPop(
    std::function<void()>&& onWillDisappear, const RefPtr<UINode> rootNode, int32_t targetId)
{
    auto topModalNode = GetModal(targetId);
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
    topModalNode->OnAccessibilityEvent(
        AccessibilityEventType::PAGE_CLOSE, WindowsContentChangeTypes::CONTENT_CHANGE_TYPE_SUBTREE);
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
        FireAutoSave(topModalNode);
        RemoveChildWithService(rootNode, topModalNode);
        rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }
    RemoveModal(targetId);
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
    InputMethodManager::GetInstance()->ProcessModalPageScene();
}

void OverlayManager::FireModalPageHide() {}

void OverlayManager::PlayDefaultModalTransition(const RefPtr<FrameNode>& modalNode, bool isTransitionIn)
{
    // current modal animation
    AnimationOption option;
    const RefPtr<InterpolatingSpring> curve =
        AceType::MakeRefPtr<InterpolatingSpring>(0.0f, CURVE_MASS, CURVE_STIFFNESS, CURVE_DAMPING);
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
            overlayManager->FireAutoSave(modal);
            overlayManager->RemoveChildWithService(root, modal);
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
                overlayManager->FireAutoSave(modal);
                overlayManager->RemoveChildWithService(root, modal);
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

void OverlayManager::UpdateSheetMaskBackgroundColor(
    const RefPtr<FrameNode>& maskNode, const RefPtr<RenderContext>& maskRenderContext, const SheetStyle& sheetStyle)
{
    if (sheetStyle.maskColor.has_value()) {
        maskRenderContext->UpdateBackgroundColor(sheetStyle.maskColor.value());
    } else {
        maskNode->GetEventHub<EventHub>()->GetOrCreateGestureEventHub()->SetHitTestMode(
            HitTestMode::HTMTRANSPARENT);
        maskRenderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    }
}

void OverlayManager::InitSheetMask(
    const RefPtr<FrameNode>& maskNode, const RefPtr<FrameNode>& sheetNode, const SheetStyle& sheetStyle)
{
    auto maskRenderContext = maskNode->GetRenderContext();
    CHECK_NULL_VOID(maskRenderContext);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto sheetTheme = pipeline->GetTheme<SheetTheme>();
    CHECK_NULL_VOID(sheetTheme);
    auto sheetLayoutProps = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    CHECK_NULL_VOID(sheetLayoutProps);
    maskNode->GetEventHub<EventHub>()->GetOrCreateGestureEventHub()->SetHitTestMode(HitTestMode::HTMDEFAULT);
    if (!AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        UpdateSheetMaskBackgroundColor(maskNode, maskRenderContext, sheetStyle);
    } else {
        auto eventConfirmHub = maskNode->GetOrCreateGestureEventHub();
        CHECK_NULL_VOID(eventConfirmHub);
        auto sheetMaskClickEvent = AceType::MakeRefPtr<NG::ClickEvent>(
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
        auto maskNodeId = maskNode->GetId();
        sheetMaskClickEventMap_.emplace(maskNodeId, sheetMaskClickEvent);
        eventConfirmHub->AddClickEvent(sheetMaskClickEvent);
        eventConfirmHub->SetNodeClickDistance(DISTANCE_THRESHOLD);
        if (!sheetStyle.interactive.has_value()) {
            if (sheetNode->GetPattern<SheetPresentationPattern>()->GetSheetType() == SheetType::SHEET_POPUP) {
                maskNode->GetEventHub<EventHub>()->GetOrCreateGestureEventHub()->SetHitTestMode(
                    HitTestMode::HTMTRANSPARENT);
                eventConfirmHub->RemoveClickEvent(sheetMaskClickEvent);
                sheetMaskClickEventMap_.erase(maskNodeId);
            }
        } else if (sheetStyle.interactive == true) {
            maskNode->GetEventHub<EventHub>()->GetOrCreateGestureEventHub()->SetHitTestMode(
                HitTestMode::HTMTRANSPARENT);
            eventConfirmHub->RemoveClickEvent(sheetMaskClickEvent);
            sheetMaskClickEventMap_.erase(maskNodeId);
        }
    }
}

void OverlayManager::CleanInvalidModalNode(const WeakPtr<FrameNode>& invalidNode)
{
    // When a modalNode.Upgrade() == nullptr, the modalNode is invalid
    modalList_.remove(invalidNode);
    std::vector<WeakPtr<FrameNode>> sheetVector;
    while (!modalStack_.empty()) {
        if (modalStack_.top() != invalidNode) {
            sheetVector.push_back(modalStack_.top());
        }
        modalStack_.pop();
    }
    for (auto iter = sheetVector.rbegin(); iter != sheetVector.rend(); ++iter) {
        modalStack_.push(*iter);
    }
}

void OverlayManager::CloseSheet(const SheetKey& sheetKey)
{
    if (modalStack_.empty()) {
        return;
    }
    auto iter = sheetMap_.find(sheetKey);
    if (sheetMap_.empty() || iter == sheetMap_.end()) {
        DeleteModal(sheetKey.targetId);
        return;
    }
    auto sheetNode = iter->second.Upgrade();
    if (sheetNode == nullptr) {
        TAG_LOGE(AceLogTag::ACE_SHEET, "The sheetNode is null, clean it.");
        CleanViewContextMap(Container::CurrentId(), sheetKey.contentId);
        CleanInvalidModalNode(iter->second);
        sheetMap_.erase(sheetKey);
        SaveLastModalNode();
        return;
    }
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    sheetPattern->SetShowState(false);
    auto buildContent = sheetPattern->GetFirstFrameNodeOfBuilder();
    CHECK_NULL_VOID(buildContent);
    sheetPattern->OnWillDisappear();
    if (buildContent->GetRenderContext()->HasDisappearTransition()) {
        if (!sheetPattern->IsExecuteOnDisappear()) {
            sheetPattern->OnDisappear();
        }
        sheetPattern->OnDisappear();
        sheetNode->Clean(false, true);
        sheetNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }
    ModalPageLostFocus(sheetNode);
    auto maskNode = GetSheetMask(sheetNode);
    if (maskNode) {
        PlaySheetMaskTransition(maskNode, false);
    }
    auto sheetType = sheetPattern->GetSheetType();
    if (sheetType == SheetType::SHEET_POPUP) {
        PlayBubbleStyleSheetTransition(sheetNode, false);
    } else {
        PlaySheetTransition(sheetNode, false);
    }
    sheetPattern->SetDismissProcess(true);
    sheetMap_.erase(sheetKey);
    CleanViewContextMap(Container::CurrentId(), sheetKey.contentId);
    RemoveSheetNode(sheetNode);
    FireModalPageHide();
    SaveLastModalNode();
}

void OverlayManager::DismissSheet()
{
    if (modalStack_.empty()) {
        return;
    }
    auto iter = sheetMap_.find(dismissTarget_.sheetKey);
    if (sheetMap_.empty() || iter == sheetMap_.end()) {
        DeleteModal(dismissTarget_.GetTargetId());
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
    const auto& modalNode = GetModal(dismissTarget_.GetTargetId());
    if (modalNode == nullptr) {
        DeleteModal(dismissTarget_.GetTargetId());
        return;
    }
    if (modalNode->GetTag() == V2::MODAL_PAGE_TAG) {
        ModalPageLostFocus(modalNode);
        auto builder = AceType::DynamicCast<FrameNode>(modalNode->GetFirstChild());
        if (!ModalPageExitProcess(modalNode)) {
            return;
        }
        RemoveModal(dismissTarget_.GetTargetId());
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
    auto sheetNode = sheetMap_[dismissTarget_.sheetKey].Upgrade();
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
        } else {
            continue;
        }
        if (modalTargetId == targetId) {
            isDelete = true;
            modalList_.erase(modal);
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
    for (auto iter = sheetVector.rbegin(); iter != sheetVector.rend(); ++iter) {
        modalStack_.push(*iter);
    }
}

void OverlayManager::PlaySheetTransition(
    RefPtr<FrameNode> sheetNode, bool isTransitionIn, bool isFirstTransition)
{
    CHECK_NULL_VOID(sheetNode);
    sheetNode->OnAccessibilityEvent(
        isTransitionIn ? AccessibilityEventType::PAGE_OPEN : AccessibilityEventType::PAGE_CLOSE,
        WindowsContentChangeTypes::CONTENT_CHANGE_TYPE_SUBTREE);

    // current sheet animation
    AnimationOption option;
    const RefPtr<InterpolatingSpring> curve =
        AceType::MakeRefPtr<InterpolatingSpring>(0.0f, CURVE_MASS, CURVE_STIFFNESS, CURVE_DAMPING);
    option.SetCurve(curve);
    option.SetFillMode(FillMode::FORWARDS);
    auto context = sheetNode->GetRenderContext();
    CHECK_NULL_VOID(context);
    context->UpdateRenderGroup(true, false, true);
    TAG_LOGD(AceLogTag::ACE_SHEET, "UpdateRenderGroup start");
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    auto sheetMaxHeight = sheetPattern->GetPageHeightWithoutOffset();
    auto sheetParent = DynamicCast<FrameNode>(sheetNode->GetParent());
    CHECK_NULL_VOID(sheetParent);
    if (isTransitionIn) {
        sheetPattern->SetCurrentHeight(sheetHeight_);
        float offset = 0.0f;
        auto sheetType = sheetPattern->GetSheetType();
        if (sheetType == SheetType::SHEET_POPUP ||
            sheetType == SheetType::SHEET_BOTTOM_OFFSET || sheetPattern->IsCurSheetNeedHalfFoldHover()) {
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
        if (sheetPattern->IsFoldStatusChanged()) {
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
                context->UpdateRenderGroup(false, false, true);
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
        ACE_SCOPED_TRACE("Sheet start admission");
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
                overlayManager->FireAutoSave(sheet);
                overlayManager->RemoveChildWithService(root, sheetParent);
                root->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
            });
        sheetParent->GetEventHub<EventHub>()->GetOrCreateGestureEventHub()->SetHitTestMode(HitTestMode::HTMTRANSPARENT);
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
    if (!isShow) {
        CloseSheet(SheetKey(targetId));
        return;
    }
    SheetKey sheetKey(targetId);
    auto iter = sheetMap_.find(sheetKey);
    if (iter != sheetMap_.end()) {
        auto sheetNode = iter->second.Upgrade();
        CHECK_NULL_VOID(sheetNode);
        UpdateSheetPage(sheetNode, sheetStyle, targetId, false, false,
            std::move(onAppear), std::move(onDisappear), std::move(shouldDismiss), std::move(onWillDismiss),
            std::move(onWillDisappear), std::move(onHeightDidChange),
            std::move(onDetentsDidChange), std::move(onWidthDidChange),
            std::move(onTypeDidChange), std::move(sheetSpringBack));
        return;
    }
    // build content
    RefPtr<UINode> sheetContentNode = buildNodeFunc();
    CHECK_NULL_VOID(sheetContentNode);
    auto frameChildNode = sheetContentNode->GetFrameChildByIndex(0, true);
    if (!frameChildNode) {
        // The function should return if the frameNodeChild of the builder is empty,
        // otherwise an exception will occur when unmount an empty node.
        TAG_LOGE(AceLogTag::ACE_SHEET, "sheet buildNode is nullptr");
        return;
    }
    OnBindSheetInner(std::move(callback), sheetContentNode, std::move(buildtitleNodeFunc),
        sheetStyle, std::move(onAppear), std::move(onDisappear), std::move(shouldDismiss), std::move(onWillDismiss),
        std::move(onWillAppear), std::move(onWillDisappear), std::move(onHeightDidChange),
        std::move(onDetentsDidChange), std::move(onWidthDidChange),
        std::move(onTypeDidChange), std::move(sheetSpringBack), targetNode);
}

void OverlayManager::OpenBindSheetByUIContext(
    const RefPtr<FrameNode>& sheetContentNode, std::function<RefPtr<UINode>()>&& buildtitleNodeFunc,
    NG::SheetStyle& sheetStyle, std::function<void()>&& onAppear, std::function<void()>&& onDisappear,
    std::function<void()>&& shouldDismiss, std::function<void(const int32_t)>&& onWillDismiss,
    std::function<void()>&& onWillAppear, std::function<void()>&& onWillDisappear,
    std::function<void(const float)>&& onHeightDidChange,
    std::function<void(const float)>&& onDetentsDidChange,
    std::function<void(const float)>&& onWidthDidChange,
    std::function<void(const float)>&& onTypeDidChange,
    std::function<void()>&& sheetSpringBack,
    std::function<void(const int32_t, const int32_t)> cleanViewContextMapCallback,
    const RefPtr<FrameNode>& targetNode)
{
    if (cleanViewContextMapCallback_ == nullptr) {
        cleanViewContextMapCallback_ = cleanViewContextMapCallback;
    }
    auto instanceId = sheetStyle.instanceId.has_value() ? sheetStyle.instanceId.value() : Container::CurrentId();
    ContainerScope scope(instanceId);
    OnBindSheetInner(nullptr, sheetContentNode, std::move(buildtitleNodeFunc),
        sheetStyle, std::move(onAppear), std::move(onDisappear), std::move(shouldDismiss), std::move(onWillDismiss),
        std::move(onWillAppear), std::move(onWillDisappear), std::move(onHeightDidChange),
        std::move(onDetentsDidChange), std::move(onWidthDidChange),
        std::move(onTypeDidChange), std::move(sheetSpringBack), targetNode, true);
}

void OverlayManager::UpdateBindSheetByUIContext(
    const RefPtr<NG::FrameNode>& sheetContentNode, NG::SheetStyle& sheetStyle, int32_t targetId, bool isPartialUpdate)
{
    SheetKey sheetKey;
    if (!CreateSheetKey(sheetContentNode, targetId, sheetKey)) {
        TAG_LOGE(AceLogTag::ACE_SHEET, "CreateSheetKey failed");
        return;
    }
    targetId = sheetKey.targetId;
    auto iter = sheetMap_.find(sheetKey);
    if (iter != sheetMap_.end()) {
        auto sheetNode = iter->second.Upgrade();
        CHECK_NULL_VOID(sheetNode);
        UpdateSheetPage(sheetNode, sheetStyle, targetId, true, isPartialUpdate);
    }
    TAG_LOGE(AceLogTag::ACE_SHEET, "Can not find sheet.");
    return;
}

void OverlayManager::UpdateSheetRender(
    const RefPtr<FrameNode>& sheetPageNode, NG::SheetStyle& sheetStyle, bool isPartialUpdate)
{
    CHECK_NULL_VOID(sheetPageNode);
    auto sheetRenderContext = sheetPageNode->GetRenderContext();
    CHECK_NULL_VOID(sheetRenderContext);
    auto pipeline = sheetPageNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto sheetTheme = pipeline->GetTheme<SheetTheme>();
    CHECK_NULL_VOID(sheetTheme);
    SetSheetBackgroundColor(sheetPageNode, sheetTheme, sheetStyle);
    if (sheetStyle.backgroundBlurStyle.has_value()) {
        SetSheetBackgroundBlurStyle(sheetPageNode, sheetStyle.backgroundBlurStyle.value());
    }
    auto sheetNodePattern = sheetPageNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetNodePattern);
    sheetNodePattern->SetSheetBorderWidth();
    if (sheetStyle.borderStyle.has_value()) {
        sheetRenderContext->UpdateBorderStyle(sheetStyle.borderStyle.value());
    }
    if (sheetStyle.borderColor.has_value()) {
        sheetRenderContext->UpdateBorderColor(sheetStyle.borderColor.value());
    }
    if (sheetStyle.shadow.has_value()) {
        sheetRenderContext->UpdateBackShadow(sheetStyle.shadow.value());
    } else if (sheetTheme->IsOuterBorderEnable()) {
        Shadow shadow = ShadowConfig::GetShadowConfig(sheetTheme->GetSheetShadowConfig());
        sheetRenderContext->UpdateBackShadow(shadow);
    } else if (!isPartialUpdate) {
        sheetRenderContext->UpdateBackShadow(ShadowConfig::NoneShadow);
    }
    sheetNodePattern->UpdateMaskBackgroundColor();
}
void OverlayManager::UpdateSheetProperty(const RefPtr<FrameNode>& sheetNode,
    NG::SheetStyle& currentStyle, bool isPartialUpdate)
{
    auto pipeline = sheetNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    UpdateSheetRender(sheetNode, currentStyle, isPartialUpdate);
    auto maskNode = GetSheetMask(sheetNode);
    if (maskNode) {
        UpdateSheetMask(maskNode, sheetNode, currentStyle, isPartialUpdate);
    }
    sheetNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    pipeline->FlushUITasks();
    ComputeSheetOffset(currentStyle, sheetNode);
}

void OverlayManager::UpdateSheetPage(const RefPtr<FrameNode>& sheetNode, NG::SheetStyle& sheetStyle,
    int32_t targetId, bool isStartByUIContext, bool isPartialUpdate,
    std::function<void()>&& onAppear, std::function<void()>&& onDisappear,
    std::function<void()>&& shouldDismiss, std::function<void(const int32_t)>&& onWillDismiss,
    std::function<void()>&& onWillDisappear, std::function<void(const float)>&& onHeightDidChange,
    std::function<void(const float)>&& onDetentsDidChange,
    std::function<void(const float)>&& onWidthDidChange,
    std::function<void(const float)>&& onTypeDidChange,
    std::function<void()>&& sheetSpringBack)
{
    if (sheetNode->GetTag() != V2::SHEET_PAGE_TAG ||
        sheetNode->GetPattern<SheetPresentationPattern>()->GetTargetId() != targetId) {
        return;
    }
    auto sheetNodePattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetNodePattern);
    auto customHeightOrDetentsChanged = sheetNodePattern->IsCustomHeightOrDetentsChanged(sheetStyle);
    if (isStartByUIContext) {
        auto currentStyle = UpdateSheetStyle(sheetNode, sheetStyle, isPartialUpdate);
        UpdateSheetProperty(sheetNode, currentStyle, isPartialUpdate);
    } else {
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
        auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
        layoutProperty->UpdateSheetStyle(sheetStyle);
        UpdateSheetProperty(sheetNode, sheetStyle, isPartialUpdate);
    }
    sheetNodePattern->SetBottomOffset(sheetStyle);
    sheetNode->MarkModifyDone();
    auto sheetType = sheetNodePattern->GetSheetType();
    if (sheetType != SheetType::SHEET_POPUP && !sheetNodePattern->GetDismissProcess() && customHeightOrDetentsChanged) {
        PlaySheetTransition(sheetNode, true, false);
    }
}

SheetStyle OverlayManager::UpdateSheetStyle(
    const RefPtr<FrameNode>& sheetNode, const SheetStyle& sheetStyle, bool isPartialUpdate)
{
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    CHECK_NULL_RETURN(layoutProperty, sheetStyle);
    auto currentStyle = layoutProperty->GetSheetStyleValue();
    if (isPartialUpdate) {
        currentStyle.PartialUpdate(sheetStyle);
    } else {
        auto currentShowInPage = currentStyle.showInPage;
        auto currentInstanceId = currentStyle.instanceId;
        currentStyle = sheetStyle;
        currentStyle.showInPage = currentShowInPage;
        currentStyle.instanceId = currentInstanceId;
    }
    layoutProperty->UpdateSheetStyle(currentStyle);
    return currentStyle;
}

void OverlayManager::CloseBindSheetByUIContext(const RefPtr<NG::FrameNode>& sheetContentNode, int32_t targetId)
{
    SheetKey sheetKey;
    if (!CreateSheetKey(sheetContentNode, targetId, sheetKey)) {
        TAG_LOGE(AceLogTag::ACE_SHEET, "CreateSheetKey failed");
        return;
    }
    CloseSheet(sheetKey);
}

void OverlayManager::OnBindSheetInner(std::function<void(const std::string&)>&& callback,
    const RefPtr<UINode>& sheetContentNode, std::function<RefPtr<UINode>()>&& buildtitleNodeFunc,
    NG::SheetStyle& sheetStyle, std::function<void()>&& onAppear, std::function<void()>&& onDisappear,
    std::function<void()>&& shouldDismiss, std::function<void(const int32_t)>&& onWillDismiss,
    std::function<void()>&& onWillAppear, std::function<void()>&& onWillDisappear,
    std::function<void(const float)>&& onHeightDidChange, std::function<void(const float)>&& onDetentsDidChange,
    std::function<void(const float)>&& onWidthDidChange,
    std::function<void(const float)>&& onTypeDidChange,
    std::function<void()>&& sheetSpringBack, const RefPtr<FrameNode>& targetNode, bool isStartByUIContext)
{
    CHECK_NULL_VOID(sheetContentNode);
    auto titleBuilder = AceType::DynamicCast<FrameNode>(buildtitleNodeFunc());
    if (titleBuilder) {
        titleBuilder->GetRenderContext()->SetIsModalRootNode(true);
    }

    CHECK_NULL_VOID(targetNode);
    auto sheetNode = SheetView::CreateSheetPage(
        targetNode->GetId(), targetNode->GetTag(), sheetContentNode, titleBuilder, std::move(callback), sheetStyle);
    CHECK_NULL_VOID(sheetNode);
    SetSheetProperty(sheetNode, sheetStyle, std::move(onAppear), std::move(onDisappear),
        std::move(shouldDismiss), std::move(onWillDismiss),
        std::move(onWillAppear), std::move(onWillDisappear), std::move(onHeightDidChange),
        std::move(onDetentsDidChange), std::move(onWidthDidChange),
        std::move(onTypeDidChange), std::move(sheetSpringBack));
    SaveSheePageNode(sheetNode, sheetContentNode, targetNode, isStartByUIContext);
    auto maskNode = CreateSheetMask(sheetNode, targetNode, sheetStyle);
    CHECK_NULL_VOID(maskNode);

    auto sheetNodePattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetNodePattern);
    if (onWillAppear) {
        TAG_LOGI(AceLogTag::ACE_SHEET, "bindSheet lifecycle change to onWillAppear state.");
        onWillAppear();
    }
    if (!AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        sheetNodePattern->OnAppear();
    }

    // start transition animation
    auto sheetType = sheetNodePattern->GetSheetType();
    if (sheetType == SheetType::SHEET_POPUP) {
        PlayBubbleStyleSheetTransition(sheetNode, true);
    } else {
        PlaySheetTransition(sheetNode, true);
    }

    auto pageNode = AceType::DynamicCast<FrameNode>(maskNode->GetParent());
    CHECK_NULL_VOID(pageNode);
    //when sheet shows in page
    if (pageNode->GetTag() == V2::PAGE_ETS_TAG) {
        //set focus on sheet when page has more than one child
        auto focusView = pageNode->GetPattern<FocusView>();
        CHECK_NULL_VOID(focusView);
        auto focusHub = sheetNode->GetFocusHub();
        CHECK_NULL_VOID(focusHub);
        focusView->SetViewRootScope(focusHub);
    }
}

void OverlayManager::SetSheetProperty(
    const RefPtr<FrameNode>& sheetPageNode,
    NG::SheetStyle& sheetStyle, std::function<void()>&& onAppear, std::function<void()>&& onDisappear,
    std::function<void()>&& shouldDismiss, std::function<void(const int32_t)>&& onWillDismiss,
    std::function<void()>&& onWillAppear, std::function<void()>&& onWillDisappear,
    std::function<void(const float)>&& onHeightDidChange, std::function<void(const float)>&& onDetentsDidChange,
    std::function<void(const float)>&& onWidthDidChange,
    std::function<void(const float)>&& onTypeDidChange,
    std::function<void()>&& sheetSpringBack)
{
    UpdateSheetRender(sheetPageNode, sheetStyle, true);
    auto sheetNodePattern = sheetPageNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetNodePattern);
    sheetNodePattern->SetBottomOffset(sheetStyle);
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
}

void OverlayManager::SaveSheePageNode(
    const RefPtr<FrameNode>& sheetPageNode, const RefPtr<UINode>& sheetContentNode,
    const RefPtr<FrameNode>& targetNode, bool isStartByUIContext)
{
    int32_t targetId = targetNode->GetId();
    auto root = AceType::DynamicCast<FrameNode>(rootNodeWeak_.Upgrade());
    CHECK_NULL_VOID(root);
    bool isValidTarget = CheckTargetIdIsValid(targetId);
    SheetKey sheetKey;
    if (isStartByUIContext) {
        sheetKey = SheetKey(isValidTarget, sheetContentNode->GetId(), targetId);
    } else {
        sheetKey = SheetKey(targetId);
    }
    auto sheetNodePattern = sheetPageNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetNodePattern);
    sheetNodePattern->SetSheetKey(sheetKey);
    sheetMap_.emplace(sheetKey, WeakClaim(RawPtr(sheetPageNode)));
    modalStack_.push(WeakClaim(RawPtr(sheetPageNode)));
    modalList_.emplace_back(WeakClaim(RawPtr(sheetPageNode)));
    SaveLastModalNode();
    sheetNodePattern->SetOverlay(AceType::WeakClaim(this));
}

bool OverlayManager::CheckTargetIdIsValid(int32_t targetId)
{
    if (targetId < 0) {
        return false;
    }
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_RETURN(rootNode, false);
    auto rootId = rootNode->GetId();
    return rootId != targetId;
}

RefPtr<FrameNode> OverlayManager::CreateSheetMask(const RefPtr<FrameNode>& sheetPageNode,
    const RefPtr<FrameNode>& targetNode, NG::SheetStyle& sheetStyle)
{
    // create maskColor node(sheetWrapper)
    auto maskNode = FrameNode::CreateFrameNode(V2::SHEET_WRAPPER_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetWrapperPattern>());
    CHECK_NULL_RETURN(maskNode, nullptr);
    auto maskLayoutProps = maskNode->GetLayoutProperty();
    CHECK_NULL_RETURN(maskLayoutProps, nullptr);
    maskLayoutProps->UpdateMeasureType(MeasureType::MATCH_PARENT);
    maskLayoutProps->UpdateAlignment(Alignment::TOP_LEFT);
    auto maskRenderContext = maskNode->GetRenderContext();
    CHECK_NULL_RETURN(maskRenderContext, nullptr);
    maskRenderContext->UpdateClipEdge(true);
    sheetPageNode->MountToParent(maskNode);
    InitSheetMask(maskNode, sheetPageNode, sheetStyle);
    auto rootNode = FindWindowScene(targetNode);
    CHECK_NULL_RETURN(rootNode, nullptr);
    MountToParentWithService(rootNode, maskNode);
    FireModalPageShow();
    rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    auto pipeline = sheetPageNode->GetContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    pipeline->FlushUITasks();
    PlaySheetMaskTransition(maskNode, true);
    ComputeSheetOffset(sheetStyle, sheetPageNode);
    return maskNode;
}

bool OverlayManager::CreateSheetKey(const RefPtr<NG::FrameNode>& sheetContentNode, int32_t targetId,
    SheetKey& sheetKey)
{
    CHECK_NULL_RETURN(sheetContentNode, false);
    bool isTargetIdValid = CheckTargetIdIsValid(targetId);
    if (!isTargetIdValid) {
        auto rootNode = rootNodeWeak_.Upgrade();
        CHECK_NULL_RETURN(rootNode, false);
        targetId = rootNode->GetId();
    }
    sheetKey = SheetKey(isTargetIdValid, sheetContentNode->GetId(), targetId);
    return true;
}

void OverlayManager::UpdateSheetMask(const RefPtr<FrameNode>& maskNode,
    const RefPtr<FrameNode>& sheetNode, const SheetStyle& sheetStyle, bool isPartialUpdate)
{
    auto maskRenderContext = maskNode->GetRenderContext();
    CHECK_NULL_VOID(maskRenderContext);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto sheetTheme = pipeline->GetTheme<SheetTheme>();
    CHECK_NULL_VOID(sheetTheme);
    auto sheetLayoutProps = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    CHECK_NULL_VOID(sheetLayoutProps);
    maskNode->GetEventHub<EventHub>()->GetOrCreateGestureEventHub()->SetHitTestMode(HitTestMode::HTMDEFAULT);

    if (!AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        UpdateSheetMaskBackgroundColor(maskNode, maskRenderContext, sheetStyle);
    } else {
        if (sheetStyle.maskColor.has_value() || !isPartialUpdate) {
            maskRenderContext->UpdateBackgroundColor(sheetStyle.maskColor.value_or(sheetTheme->GetMaskColor()));
        }
        auto eventConfirmHub = maskNode->GetOrCreateGestureEventHub();
        CHECK_NULL_VOID(eventConfirmHub);

        auto maskNodeId = maskNode->GetId();
        auto iter = sheetMaskClickEventMap_.find(maskNodeId);
        if (iter == sheetMaskClickEventMap_.end() &&
            sheetStyle.interactive.has_value() && !sheetStyle.interactive.value()) {
            auto sheetMaskClickEvent = AceType::MakeRefPtr<NG::ClickEvent>(
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
            sheetMaskClickEventMap_.emplace(maskNodeId, sheetMaskClickEvent);
            eventConfirmHub->AddClickEvent(sheetMaskClickEvent);
            eventConfirmHub->SetNodeClickDistance(DISTANCE_THRESHOLD);
            return;
        }

        if ((!sheetStyle.interactive.has_value() && !isPartialUpdate &&
                sheetNode->GetPattern<SheetPresentationPattern>()->GetSheetType() == SheetType::SHEET_POPUP) ||
            sheetStyle.interactive.value_or(false)) {
            maskNode->GetEventHub<EventHub>()->GetOrCreateGestureEventHub()->SetHitTestMode(
                HitTestMode::HTMTRANSPARENT);
            maskRenderContext->UpdateBackgroundColor(Color::TRANSPARENT);
            eventConfirmHub->RemoveClickEvent(iter->second);
            sheetMaskClickEventMap_.erase(maskNodeId);
        }
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
                        overlayManager->FireAutoSave(sheet);
                        overlayManager->RemoveChildWithService(root, sheetParent);
                        root->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
                    },
                    TaskExecutor::TaskType::UI, "ArkUIOverlaySheetExitingAnimation");
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
    auto sheetNode = AceType::DynamicCast<FrameNode>(maskNode->GetChildAtIndex(0));
    CHECK_NULL_VOID(sheetNode);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    auto backgroundColor = sheetPattern->GetMaskBackgroundColor();
    if (isTransitionIn) {
        context->UpdateBackgroundColor(backgroundColor.ChangeOpacity(0.0f));
        AnimationUtils::Animate(
            option,
            [context, backgroundColor]() {
                CHECK_NULL_VOID(context);
                context->UpdateBackgroundColor(backgroundColor);
            });
    } else {
        auto iter = sheetMaskClickEventMap_.find(maskNode->GetId());
        if (iter != sheetMaskClickEventMap_.end()) {
            auto eventConfirmHub = maskNode->GetOrCreateGestureEventHub();
            CHECK_NULL_VOID(eventConfirmHub);
            eventConfirmHub->RemoveClickEvent(iter->second);
        }
        maskNode->GetEventHub<EventHub>()->GetOrCreateGestureEventHub()->SetHitTestMode(HitTestMode::HTMTRANSPARENT);
        context->UpdateBackgroundColor(backgroundColor);
        AnimationUtils::Animate(
            option,
            [context, backgroundColor]() {
                CHECK_NULL_VOID(context);
                context->UpdateBackgroundColor(backgroundColor.ChangeOpacity(0.0f));
            });
    }
}

void OverlayManager::SetSheetBackgroundColor(const RefPtr<FrameNode>& sheetNode, const RefPtr<SheetTheme>& sheetTheme,
    const NG::SheetStyle& sheetStyle, bool isPartialUpdate)
{
    if (!AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        if (sheetStyle.backgroundColor.has_value()) {
            sheetNode->GetRenderContext()->UpdateBackgroundColor(sheetStyle.backgroundColor.value());
        }
    } else if (sheetStyle.backgroundColor.has_value() || !isPartialUpdate) {
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
        case SheetType::SHEET_BOTTOMLANDSPACE:
            if (!AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
                sheetHeight_ = largeHeight;
                break;
            }
        case SheetType::SHEET_BOTTOM:
        case SheetType::SHEET_BOTTOM_FREE_WINDOW:
        case SheetType::SHEET_BOTTOM_OFFSET:
            if (!sheetStyle.detents.empty()) {
                ComputeDetentsSheetOffset(sheetStyle, sheetNode);
            } else {
                ComputeSingleGearSheetOffset(sheetStyle, sheetNode);
            }
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

// if device is phone, fold status, screen is in landscape mode, preferType is BOTTOM
void OverlayManager::CheckDeviceInLandscape(
    NG::SheetStyle& sheetStyle, RefPtr<FrameNode> sheetNode, float& sheetTopSafeArea)
{
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    if (sheetStyle.sheetType.has_value() && sheetStyle.sheetType.value() == SheetType::SHEET_BOTTOM &&
        sheetPattern->IsPhoneInLandScape()) {
        sheetTopSafeArea = 0.0f;
    }
}

void OverlayManager::ComputeSingleGearSheetOffset(NG::SheetStyle& sheetStyle, RefPtr<FrameNode> sheetNode)
{
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    auto sheetMaxHeight = sheetPattern->GetPageHeightWithoutOffset();
    auto sheetTopSafeArea = sheetPattern->GetSheetTopSafeArea();

    auto largeHeight = sheetMaxHeight - SHEET_BLANK_MINI_HEIGHT.ConvertToPx() - sheetTopSafeArea;
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
            height = sheetStyle.height->ConvertToPxWithSize(sheetMaxHeight - sheetTopSafeArea);
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
    auto sheetTopSafeArea = sheetPattern->GetSheetTopSafeArea();
    auto largeHeight = sheetMaxHeight - SHEET_BLANK_MINI_HEIGHT.ConvertToPx() - sheetTopSafeArea;
    auto selection = sheetStyle.detents[sheetPattern->GetDetentsIndex()];
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
            height = selection.height->ConvertToPxWithSize(sheetMaxHeight - sheetTopSafeArea);
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

void OverlayManager::CleanSheet(const RefPtr<FrameNode>& sheetNode, const SheetKey& sheetKey)
{
    if (modalStack_.empty()) {
        return;
    }
    auto iter = sheetMap_.find(sheetKey);
    if (sheetMap_.empty() || iter == sheetMap_.end()) {
        DeleteModal(sheetKey.targetId, false);
        return;
    }
    auto mapSheetNode = iter->second.Upgrade();
    CHECK_NULL_VOID(mapSheetNode);
    if (mapSheetNode->GetTag() != V2::SHEET_PAGE_TAG) {
        return;
    }
    if (mapSheetNode->GetPattern<SheetPresentationPattern>()->GetTargetId() != sheetKey.targetId) {
        return;
    }
    ModalPageLostFocus(mapSheetNode);
    sheetMap_.erase(sheetKey);
    CleanViewContextMap(Container::CurrentId(), sheetKey.contentId);
    RemoveSheetNode(sheetNode);
    FireModalPageHide();
    SaveLastModalNode();
}

void OverlayManager::DestroySheet(const RefPtr<FrameNode>& sheetNode, const SheetKey& sheetKey)
{
    auto rootNode = FindWindowScene(sheetNode);
    CHECK_NULL_VOID(rootNode);
    auto root = DynamicCast<FrameNode>(rootNode);
    sheetNode->GetPattern<SheetPresentationPattern>()->OnDisappear();
    auto sheetParent = DynamicCast<FrameNode>(sheetNode->GetParent());
    CHECK_NULL_VOID(sheetParent);
    RemoveChildWithService(root, sheetParent);
    root->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
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
        if (isModal) {
            // Fire shown event of navdestination under the disappeared modal page
            FireNavigationStateChange(true);
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
        RemoveChildWithService(rootNode, modalNode);
    } else {
        auto sheetPattern = modalNode->GetPattern<SheetPresentationPattern>();
        CHECK_NULL_VOID(sheetPattern);
        if (needOnWillDisappear) {
            sheetPattern->OnWillDisappear();
        }
        sheetPattern->OnDisappear();
        sheetPattern->FireCallback("false");
        sheetMap_.erase(sheetPattern->GetSheetKey());
        auto sheetParent = DynamicCast<FrameNode>(modalNode->GetParent());
        CHECK_NULL_VOID(sheetParent);
        RemoveChildWithService(rootNode, sheetParent);
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

RefPtr<FrameNode> OverlayManager::GetSheetMask(const RefPtr<FrameNode>& sheetNode)
{
    // get bindsheet masknode
    CHECK_NULL_RETURN(sheetNode, nullptr);
    auto sheetParent = sheetNode->GetParent();
    CHECK_NULL_RETURN(sheetParent, nullptr);
    return DynamicCast<FrameNode>(sheetParent);
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
    auto keyboardOffsetInfo = CalcCustomKeyboardOffset(customKeyboard);
    if (isTransitionIn) {
        context->OnTransformTranslateUpdate({ 0.0f, keyboardOffsetInfo.inAniStartOffset, 0.0f });
        AnimationUtils::Animate(
            option,
            [context, finalOffset = keyboardOffsetInfo.finalOffset]() {
                if (context) {
                    context->OnTransformTranslateUpdate({ 0.0f, finalOffset, 0.0f });
                }
            },
            [weak = WeakClaim(customKeyboard.GetRawPtr())]() {
                auto keyboard = weak.Upgrade();
                CHECK_NULL_VOID(keyboard);
                auto pipeline = keyboard->GetContext();
                CHECK_NULL_VOID(pipeline);
                auto textFieldManagerNg = DynamicCast<TextFieldManagerNG>(pipeline->GetTextFieldManager());
                CHECK_NULL_VOID(textFieldManagerNg);
                textFieldManagerNg->OnAfterAvoidKeyboard(true);
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
            [context, outAniEndOffset = keyboardOffsetInfo.outAniEndOffset]() {
                if (context) {
                    context->OnTransformTranslateUpdate({ 0.0f, outAniEndOffset, 0.0f });
                }
            },
            option.GetOnFinishEvent());
    }
}

void OverlayManager::UpdateCustomKeyboardPosition()
{
    for (auto iter = customKeyboardMap_.begin(); iter != customKeyboardMap_.end(); iter++) {
        auto customKeyboardNode = iter->second;
        if (!customKeyboardNode) {
            continue;
        }
        auto parent = customKeyboardNode->GetParent();
        if (!parent) {
            continue;
        }
        auto renderContext = customKeyboardNode->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        auto keyboardOffsetInfo = CalcCustomKeyboardOffset(customKeyboardNode);
        renderContext->OnTransformTranslateUpdate({ 0.0f, keyboardOffsetInfo.finalOffset, 0.0f });
    }
}

CustomKeyboardOffsetInfo OverlayManager::CalcCustomKeyboardOffset(const RefPtr<FrameNode>& customKeyboard)
{
    CustomKeyboardOffsetInfo keyboardOffsetInfo;
    CHECK_NULL_RETURN(customKeyboard, keyboardOffsetInfo);
    auto pipeline = customKeyboard->GetContext();
    CHECK_NULL_RETURN(pipeline, keyboardOffsetInfo);
    auto pageNode = pipeline->GetStageManager()->GetLastPage();
    auto pageHeight = pageNode && pageNode->GetGeometryNode() ?
        pageNode->GetGeometryNode()->GetFrameSize().Height() : 0.0f;
    auto keyboardGeo = customKeyboard->GetGeometryNode();
    CHECK_NULL_RETURN(keyboardGeo, keyboardOffsetInfo);
    auto keyboardHeight = keyboardGeo->GetFrameSize().Height();
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_RETURN(rootNode, keyboardOffsetInfo);
    auto finalOffset = 0.0f;
    if (rootNode->GetTag() == V2::STACK_ETS_TAG) {
        auto rootNd = AceType::DynamicCast<FrameNode>(rootNode);
        CHECK_NULL_RETURN(rootNd, keyboardOffsetInfo);
        auto rootGeo = rootNd->GetGeometryNode();
        CHECK_NULL_RETURN(rootGeo, keyboardOffsetInfo);
        pageHeight = rootGeo->GetFrameSize().Height();
        finalOffset = (pageHeight - keyboardHeight) - (pageHeight - keyboardHeight) / NUM_FLOAT_2;
    } else if (!pageNode) {
        auto fatherNode = customKeyboard->GetAncestorNodeOfFrame();
        CHECK_NULL_RETURN(fatherNode, keyboardOffsetInfo);
        auto fatherGeoNode = fatherNode->GetGeometryNode();
        CHECK_NULL_RETURN(fatherGeoNode, keyboardOffsetInfo);
        pageHeight = fatherGeoNode->GetFrameSize().Height();
    }
    keyboardOffsetInfo.finalOffset = finalOffset;
    keyboardOffsetInfo.inAniStartOffset = pageHeight;
    keyboardOffsetInfo.outAniEndOffset = finalOffset + keyboardHeight;
    return keyboardOffsetInfo;
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
    ACE_LAYOUT_SCOPED_TRACE("BindKeyboard[targetId:%d]", targetId);
    customKeyboard->MountToParent(rootNode);
    rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    customKeyboardMap_[targetId] = customKeyboard;
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    TAG_LOGI(AceLogTag::ACE_KEYBOARD, "BindKeyboard targetId:%{public}d", targetId);
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
    ACE_LAYOUT_SCOPED_TRACE("BindKeyboardWithNode[targetId:%d]", targetId);
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_VOID(rootNode);
    auto customKeyboard = KeyboardView::CreateKeyboardWithNode(targetId, keyboard);
    if (!customKeyboard) {
        return;
    }
    TAG_LOGI(AceLogTag::ACE_KEYBOARD, "BindKeyboardWithNode targetId:%{public}d", targetId);
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
    ACE_LAYOUT_SCOPED_TRACE("CloseKeyboard[targetId:%d]", targetId);
    auto customKeyboard = it->second;
    CHECK_NULL_VOID(customKeyboard);
    auto pipeline = customKeyboard->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto pattern = customKeyboard->GetPattern<KeyboardPattern>();
    CHECK_NULL_VOID(pattern);
    customKeyboardMap_.erase(pattern->GetTargetId());
    customKeyboard->MarkRemoving();
    PlayKeyboardTransition(customKeyboard, false);
    Rect keyboardRect = Rect(0.0f, 0.0f, 0.0f, 0.0f);
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
    pattern->SetKeyboardSafeHeight(safeHeight);
    pattern->SetKeyboardOption(keyboardAvoidance_);
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
    if (!container || !container->IsScenceBoardWindow() || isAttachToCustomNode_) {
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

/**
 * Mount pixelMap to wndow scene for lifting or for drag moving.
 * When isDragPixelMap is true, the pixelMap is saved by dragPixmapColumnNodeWeak_ used for moving with drag finger or
 * mouse, etc.
 * When isDragPixelMap is false, the pixelMap is saved by pixmapColumnNodeWeak_ used for lifting.
 */
void OverlayManager::MountPixelMapToWindowScene(
    const RefPtr<FrameNode>& columnNode, const RefPtr<UINode>& windowScene, bool isDragPixelMap)
{
    CHECK_NULL_VOID(windowScene);
    columnNode->MountToParent(windowScene);
    columnNode->OnMountToParentDone();
    windowScene->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
    if (isDragPixelMap) {
        dragPixmapColumnNodeWeak_ = columnNode;
        hasDragPixelMap_ = true;
    } else {
        pixmapColumnNodeWeak_ = columnNode;
        hasPixelMap_ = true;
    }
}

void OverlayManager::MountEventToWindowScene(const RefPtr<FrameNode>& columnNode, const RefPtr<UINode>& windowScene)
{
    CHECK_NULL_VOID(windowScene);
    columnNode->MountToParent(windowScene);
    columnNode->OnMountToParentDone();
    eventColumnNodeWeak_ = columnNode;
    hasEvent_ = true;
}

/**
 * Mount pixelMap to root node for lifting or for drag moving.
 * When isDragPixelMap is true, the pixelMap is saved by dragPixmapColumnNodeWeak_ used for moving with drag finger or
 * mouse, etc.
 * When isDragPixelMap is false, the pixelMap is saved by pixmapColumnNodeWeak_ used for lifting.
 */
void OverlayManager::MountPixelMapToRootNode(const RefPtr<FrameNode>& columnNode, bool isDragPixelMap)
{
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_VOID(rootNode);
    columnNode->MountToParent(rootNode);
    columnNode->OnMountToParentDone();
    rootNode->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
    if (isDragPixelMap) {
        dragPixmapColumnNodeWeak_ = columnNode;
        hasDragPixelMap_ = true;
    } else {
        pixmapColumnNodeWeak_ = columnNode;
        hasPixelMap_ = true;
    }
}

void OverlayManager::MountEventToRootNode(const RefPtr<FrameNode>& columnNode)
{
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_VOID(rootNode);
    columnNode->MountToParent(rootNode, EVENT_COLUMN_SLOT);
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

void OverlayManager::RemovePixelMapAnimation(bool startDrag, double x, double y, bool isSubwindowOverlay)
{
    if (isOnAnimation_ || !hasPixelMap_) {
        return;
    }
    if (startDrag) {
        if (!isSubwindowOverlay) {
            RemovePixelMap();
        }
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
    auto targetBorderRadius = GetPrepareDragFrameNodeBorderRadius();
    AnimationOption option;
    option.SetCurve(Curves::SHARP);
    option.SetDuration(PIXELMAP_ANIMATION_DURATION);
    AnimationUtils::Animate(option, [imageContext, shadow, targetBorderRadius]() mutable {
        if (imageContext) {
            auto color = shadow->GetColor();
            auto newColor = Color::FromARGB(1, color.GetRed(), color.GetGreen(), color.GetBlue());
            shadow->SetColor(newColor);
            imageContext->UpdateBackShadow(shadow.value());
            imageContext->UpdateBorderRadius(targetBorderRadius);
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
    scaleOption.SetOnFinishEvent([weak = WeakClaim(this), isSubwindowOverlay] {
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto dragDropManager = pipeline->GetDragDropManager();
        CHECK_NULL_VOID(dragDropManager);
        DragEventActuator::ExecutePreDragAction(PreDragStatus::PREVIEW_LANDING_FINISHED);
        if (!dragDropManager->IsNeedDisplayInSubwindow() && !isSubwindowOverlay && dragDropManager->IsDragging()) {
            InteractionInterface::GetInstance()->SetDragWindowVisible(true);
        }
        auto overlayManager = weak.Upgrade();
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

void OverlayManager::RemoveDragPixelMap()
{
    TAG_LOGI(AceLogTag::ACE_DRAG, "remove drag pixelMap enter");
    if (!hasDragPixelMap_) {
        return;
    }
    auto columnNode = dragPixmapColumnNodeWeak_.Upgrade();
    if (!columnNode) {
        hasDragPixelMap_ = false;
        return;
    }
    auto rootNode = columnNode->GetParent();
    CHECK_NULL_VOID(rootNode);
    rootNode->RemoveChild(columnNode);
    rootNode->RebuildRenderContextTree();
    rootNode->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
    hasDragPixelMap_ = false;
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
        TAG_LOGI(AceLogTag::ACE_DRAG, "remove eventColumn, hasEvent is false.");
        return;
    }
    auto columnNode = eventColumnNodeWeak_.Upgrade();
    if (!columnNode) {
        hasEvent_ = false;
        TAG_LOGI(AceLogTag::ACE_DRAG, "remove eventColumn, columnNode is null.");
        return;
    }
    auto rootNode = columnNode->GetParent();
    CHECK_NULL_VOID(rootNode);
    rootNode->RemoveChild(columnNode);
    hasEvent_ = false;
    TAG_LOGI(AceLogTag::ACE_DRAG, "remove eventColumn success, id %{public}d.", columnNode->GetId());
}

void OverlayManager::ResetRootNode(int32_t sessionId)
{
    if (curSessionIds_.find(sessionId) == curSessionIds_.end()) {
        return;
    }

    TAG_LOGI(AceLogTag::ACE_OVERLAY, "ResetRootNode %{public}d.", sessionId);
    curSessionIds_.erase(sessionId);
    auto rootNode = FindWindowScene(nullptr);
    CHECK_NULL_VOID(rootNode);
    rootNode->UpdateModalUiextensionCount(false);
}

void OverlayManager::SetIsAllowedBeCovered(bool isAllowedBeCovered)
{
    isAllowedBeCovered_ = isAllowedBeCovered;
}

bool OverlayManager::AddCurSessionId(int32_t sessionId)
{
    if (curSessionIds_.find(sessionId) != curSessionIds_.end()) {
        return false;
    }

    curSessionIds_.insert(sessionId);
    return true;
}

int32_t OverlayManager::CreateModalUIExtension(const RefPtr<WantWrap>& wantWrap,
    const ModalUIExtensionCallbacks& callbacks, const ModalUIExtensionConfig& config)
{
    auto& want = wantWrap->GetWant();
    return CreateModalUIExtension(want, callbacks, config);
}

bool OverlayManager::HandleUIExtNodeSize(const AAFwk::Want& want, RefPtr<FrameNode> uiExtNode)
{
#if defined(OHOS_STANDARD_SYSTEM) and !defined(ACE_UNITTEST)
    auto uiExtNodeWidth = want.GetIntParam(WANT_PARAM_UIEXTNODE_WIDTH_KEY, 0);
    auto uiExtNodeHeight = want.GetIntParam(WANT_PARAM_UIEXTNODE_HEIGHT_KEY, 0);
#else
    auto uiExtNodeWidth = 0;
    auto uiExtNodeHeight = 0;
#endif
    auto layoutProperty = uiExtNode->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, false);
    auto calcWidth =
        CalcLength((uiExtNodeWidth > 0) ? Dimension(uiExtNodeWidth) : Dimension(1.0, DimensionUnit::PERCENT));
    auto calcHeight =
        CalcLength((uiExtNodeHeight > 0) ? Dimension(uiExtNodeHeight) : Dimension(1.0, DimensionUnit::PERCENT));
    TAG_LOGD(AceLogTag::ACE_UIEXTENSIONCOMPONENT,
        "UIExtensionNode Size[%{public}d, [%{public}d].", uiExtNodeWidth, uiExtNodeHeight);
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(calcWidth, calcHeight));
    return true;
}

bool OverlayManager::HandleUIExtNodeAngle(int32_t uiExtNodeAngle, RefPtr<FrameNode> uiExtNode)
{
    auto layoutProperty = uiExtNode->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, false);
    const auto& renderContext = uiExtNode->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, false);
    TAG_LOGD(AceLogTag::ACE_UIEXTENSIONCOMPONENT, "RootSize[%{public}f, %{public}f], Angle[%{public}d].",
        GetRootWidth(), GetRootHeight(), uiExtNodeAngle);
    switch (uiExtNodeAngle) {
        case UIEXTNODE_ANGLE_90: {
            layoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(Dimension(GetRootHeight())),
                CalcLength(Dimension(GetRootWidth()))));
            TranslateOptions translate(GetRootWidth(), 0, 0);
            renderContext->UpdateTransformTranslate(translate);
            NG::Vector5F rotate(0.0f, 0.0f, 1.0f, 90.0f, 0.0f);
            DimensionOffset offset(Dimension(0), Dimension(0));
            renderContext->UpdateTransformRotate(rotate);
            renderContext->UpdateTransformCenter(offset);
            break;
        }
        case UIEXTNODE_ANGLE_180: {
            auto full = CalcLength(Dimension(1.0, DimensionUnit::PERCENT));
            layoutProperty->UpdateUserDefinedIdealSize(CalcSize(full, full));
            NG::Vector5F rotate(0.0f, 0.0f, 1.0f, 180.0f, 0.0f);
            DimensionOffset offset(0.5_pct, 0.5_pct);
            renderContext->UpdateTransformRotate(rotate);
            renderContext->UpdateTransformCenter(offset);
            break;
        }
        case UIEXTNODE_ANGLE_270: {
            layoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(Dimension(GetRootHeight())),
                CalcLength(Dimension(GetRootWidth()))));
            TranslateOptions translate(0, GetRootHeight(), 0);
            renderContext->UpdateTransformTranslate(translate);
            NG::Vector5F rotate(0.0f, 0.0f, 1.0f, 270.0f, 0.0f);
            DimensionOffset offset(Dimension(0), Dimension(0));
            renderContext->UpdateTransformRotate(rotate);
            renderContext->UpdateTransformCenter(offset);
            break;
        }
    }
    return true;
}

bool OverlayManager::HandleUIExtNodeTransform(const AAFwk::Want& want, RefPtr<FrameNode> uiExtNode)
{
    auto containerId = Container::CurrentId();
    auto foldWindow = FoldableWindow::CreateFoldableWindow(containerId);
    bool isFoldExpand = foldWindow && (foldWindow->IsFoldExpand());
#if defined(OHOS_STANDARD_SYSTEM) and !defined(ACE_UNITTEST)
    auto uiExtNodeAngle = want.GetIntParam(WANT_PARAM_UIEXTNODE_ANGLE_KEY, 0);
#else
    auto uiExtNodeAngle = 0;
#endif
    if (!(isFoldExpand) && UIExtNodeAngleValid(uiExtNodeAngle)) {
        return HandleUIExtNodeAngle(uiExtNodeAngle, uiExtNode);
    } else if (!UIExtNodeAngleValid(uiExtNodeAngle)) {
        return HandleUIExtNodeSize(want, uiExtNode);
    }
    return true;
}

bool OverlayManager::UIExtNodeAngleValid(int32_t uiExtNodeAngle)
{
    return (uiExtNodeAngle == UIEXTNODE_ANGLE_90) ||
        (uiExtNodeAngle == UIEXTNODE_ANGLE_180) || (uiExtNodeAngle == UIEXTNODE_ANGLE_270);
}

int32_t OverlayManager::CreateModalUIExtension(
    const AAFwk::Want& want, const ModalUIExtensionCallbacks& callbacks,
    const ModalUIExtensionConfig& config)
{
    isProhibitBack_ = config.isProhibitBack;
    NG::InnerModalUIExtensionConfig innerModalUIExtensionConfig = { .isAsyncModalBinding = config.isAsyncModalBinding,
        .isDensityFollowHost = config.isDensityFollowHost };
    auto uiExtNode = ModalUIExtension::Create(want, callbacks, innerModalUIExtensionConfig);
    if (!HandleUIExtNodeTransform(want, uiExtNode)) {
        return 0;
    }
    auto buildNodeFunc = [uiExtNode]() -> RefPtr<UINode> {
        uiExtNode->MarkModifyDone();
        return uiExtNode;
    };
    auto sessionId = ModalUIExtension::GetSessionId(uiExtNode);
    if (!config.isAsyncModalBinding) {
        ModalStyle modalStyle;
        modalStyle.modalTransition = NG::ModalTransition::NONE;
        modalStyle.isUIExtension = true;
        modalStyle.prohibitedRemoveByRouter = config.prohibitedRemoveByRouter;
        modalStyle.isAllowAddChildBelowModalUec = config.isAllowAddChildBelowModalUec;
        SetIsAllowedBeCovered(config.isAllowedBeCovered);
        // Convert the sessionId into a negative number to distinguish it from the targetId of other modal pages
        BindContentCover(true, nullptr, std::move(buildNodeFunc), modalStyle, nullptr, nullptr, nullptr, nullptr,
            ContentCoverParam(), nullptr, -(sessionId));
        SetIsAllowedBeCovered(true); // Reset isAllowedBeCovered
    } else {
        auto bindModalCallback = [weak = WeakClaim(this), buildNodeFunc, sessionId, id = Container::CurrentId(),
            isAllowedBeCovered = config.isAllowedBeCovered,
            prohibitedRemoveByRouter = config.prohibitedRemoveByRouter,
            isAllowAddChildBelowModalUec = config.isAllowAddChildBelowModalUec,
            doAfterAsyncModalBinding = std::move(config.doAfterAsyncModalBinding)]() {
            ContainerScope scope(id);
            auto overlayManager = weak.Upgrade();
            CHECK_NULL_VOID(overlayManager);
            overlayManager->SetIsAllowedBeCovered(isAllowedBeCovered);
            ModalStyle modalStyle;
            modalStyle.modalTransition = NG::ModalTransition::NONE;
            modalStyle.isUIExtension = true;
            modalStyle.prohibitedRemoveByRouter = prohibitedRemoveByRouter;
            modalStyle.isAllowAddChildBelowModalUec = isAllowAddChildBelowModalUec;
            overlayManager->BindContentCover(true, nullptr, std::move(buildNodeFunc), modalStyle, nullptr, nullptr,
                nullptr, nullptr, ContentCoverParam(), nullptr, -(sessionId));
            overlayManager->SetIsAllowedBeCovered(true);
            if (doAfterAsyncModalBinding) {
                doAfterAsyncModalBinding();
            }
        };
        ModalUIExtension::SetBindModalCallback(uiExtNode, std::move(bindModalCallback));
        uiExtNodes_[sessionId] = WeakClaim(RawPtr(uiExtNode));
    }
    return sessionId;
}

void OverlayManager::ClearUIExtensionNode()
{
    for (auto& item: uiExtNodes_) {
        auto uiExtNode = item.second.Upgrade();
        if (uiExtNode) {
            ModalUIExtension::SetBindModalCallback(uiExtNode, nullptr);
        }
    }
    uiExtNodes_.clear();
}

void OverlayManager::DeleteUIExtensionNode(int32_t sessionId)
{
    auto iter = uiExtNodes_.find(sessionId);
    if (iter != uiExtNodes_.end()) {
        auto uiExtNode = iter->second.Upgrade();
        if (uiExtNode) {
            ModalUIExtension::SetBindModalCallback(uiExtNode, nullptr);
        }
        uiExtNodes_.erase(sessionId);
    }
}

void OverlayManager::CloseModalUIExtension(int32_t sessionId)
{
    DeleteUIExtensionNode(sessionId);
    ModalStyle modalStyle;
    modalStyle.modalTransition = NG::ModalTransition::NONE;
    BindContentCover(false, nullptr, nullptr, modalStyle, nullptr, nullptr, nullptr, nullptr, ContentCoverParam(),
        nullptr, -(sessionId));
    ResetRootNode(-(sessionId));
}

RefPtr<FrameNode> OverlayManager::BuildAIEntityMenu(
    const std::vector<std::pair<std::string, std::function<void()>>>& menuOptions)
{
    TAG_LOGI(AceLogTag::ACE_OVERLAY, "build AI entity menu enter");
    auto menuNode = FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<InnerMenuPattern>(-1, V2::MENU_ETS_TAG, MenuType::MULTI_MENU));
    CHECK_NULL_RETURN(menuNode, nullptr);
    for (const auto& menuOption : menuOptions) {
        MenuItemGroupView::Create();
        auto menuItemGroupNode = DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
        CHECK_NULL_RETURN(menuItemGroupNode, nullptr);
        MenuItemProperties menuItemProperties;
        menuItemProperties.content = menuOption.first;
        MenuItemModelNG menuItemModel;
        menuItemModel.Create(menuItemProperties);
        auto menuItemNode = DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
        CHECK_NULL_RETURN(menuItemNode, nullptr);
        auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
        CHECK_NULL_RETURN(menuItemPattern, nullptr);
        menuItemPattern->SetOnClickAIMenuItem(menuOption.second);
        menuItemNode->MountToParent(menuItemGroupNode);
        menuItemGroupNode->MountToParent(menuNode);
    }
    return menuNode;
}

RefPtr<FrameNode> OverlayManager::CreateAIEntityMenu(
    const std::vector<std::pair<std::string, std::function<void()>>>& menuOptions, const RefPtr<FrameNode>& targetNode)
{
    TAG_LOGI(AceLogTag::ACE_OVERLAY, "create AI entity menu enter");
    CHECK_NULL_RETURN(targetNode, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    MenuParam menuParam;
    menuParam.type = MenuType::MENU;
    menuParam.placement = Placement::BOTTOM_LEFT;
    auto menuWrapperNode =
        MenuView::Create(BuildAIEntityMenu(menuOptions), targetNode->GetId(), targetNode->GetTag(), menuParam, true);
    return menuWrapperNode;
}

bool OverlayManager::ShowAIEntityMenu(const std::vector<std::pair<std::string, std::function<void()>>>& menuOptions,
    const RectF& aiRect, const RefPtr<FrameNode>& targetNode)
{
    TAG_LOGI(AceLogTag::ACE_OVERLAY, "show AI entity menu enter");
    CHECK_NULL_RETURN(targetNode, false);
    auto menuWrapperNode = CreateAIEntityMenu(menuOptions, targetNode);
    CHECK_NULL_RETURN(menuWrapperNode, false);
    menuWrapperNode->GetOrCreateFocusHub()->SetFocusable(false);
    auto wrapperPattern = menuWrapperNode->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_RETURN(wrapperPattern, false);
    auto pipeline = targetNode->GetContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto safeAreaManager = pipeline->GetSafeAreaManager();
    CHECK_NULL_RETURN(safeAreaManager, false);
    auto targetId = targetNode->GetId();
    wrapperPattern->RegisterMenuAppearCallback([overlayWk = WeakClaim(this),
        safeAreaWK = WeakClaim(RawPtr(safeAreaManager)), targetId, containerId = Container::CurrentId()]() {
            ContainerScope scope(containerId);
            auto safeAreaManager = safeAreaWK.Upgrade();
            CHECK_NULL_VOID(safeAreaManager);
            safeAreaManager->AddKeyboardChangeCallbackConsideringUIExt(targetId, [overlayWk, targetId, containerId]() {
                    ContainerScope scope(containerId);
                    auto overlayManager = overlayWk.Upgrade();
                    CHECK_NULL_VOID(overlayManager);
                    overlayManager->CloseAIEntityMenu(targetId);
                });
        });
    wrapperPattern->RegisterMenuDisappearCallback(
        [safeAreaWK = WeakClaim(RawPtr(safeAreaManager)), targetId, containerId = Container::CurrentId()]() {
            ContainerScope scope(containerId);
            auto safeAreaManager = safeAreaWK.Upgrade();
            CHECK_NULL_VOID(safeAreaManager);
            safeAreaManager->RemoveKeyboardChangeCallbackConsideringUIExt(targetId);
        });
    auto menuNode = DynamicCast<FrameNode>(menuWrapperNode->GetFirstChild());
    CHECK_NULL_RETURN(menuNode, false);
    auto menuLayoutProperty = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_RETURN(menuLayoutProperty, false);
    menuLayoutProperty->UpdateIsRectInTarget(true);
    menuLayoutProperty->UpdateTargetSize(aiRect.GetSize());

    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_RETURN(theme, false);
    if (theme->GetExpandDisplay()) {
        MenuParam menuParam {};
        SubwindowManager::GetInstance()->ShowMenuNG(menuWrapperNode, menuParam, targetNode, aiRect.GetOffset());
    } else {
        ShowMenu(targetNode->GetId(), aiRect.GetOffset(), menuWrapperNode);
    }
    return true;
}

void OverlayManager::CloseAIEntityMenu(int32_t targetId)
{
    auto pipeline = PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    auto expandDisplay = theme->GetExpandDisplay();
    if (expandDisplay) {
        SubwindowManager::GetInstance()->ClearMenu();
        SubwindowManager::GetInstance()->ClearMenuNG(Container::CurrentId(), targetId);
    } else {
        auto menuNode = GetMenuNode(targetId);
        CHECK_NULL_VOID(menuNode);
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
    auto markNode = root;
    if (pipeline->GetInstallationFree()) {
        markNode = root->GetFirstChild();
        TAG_LOGD(AceLogTag::ACE_OVERLAY, "atomicService node need marked");
    }
    for (auto&& child : markNode->GetChildren()) {
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

    // markdirty toast node under pipeline root node
    auto rootNode = pipeline->GetRootElement();
    CHECK_NULL_VOID(rootNode);

    if (rootNode == markNode) {
        return;
    }

    for (auto&& child : rootNode->GetChildren()) {
        if (child->GetTag() == V2::TOAST_ETS_TAG && (child != root->GetFirstChild() || pipeline->IsSubPipeline())) {
            child->MarkDirtyNode(flag);
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

float OverlayManager::GetRootWidth() const
{
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_RETURN(rootNode, 0.0);
    auto rootGeometryNode = AceType::DynamicCast<FrameNode>(rootNode)->GetGeometryNode();
    CHECK_NULL_RETURN(rootGeometryNode, 0.0);
    auto rootWidth = rootGeometryNode->GetFrameSize().Width();
    return rootWidth;
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
    for (const auto& [key, value] : maskNodeIdMap_) {
        if (value == maskId) {
            return true;
        }
    }
    return false;
}

int32_t OverlayManager::GetMaskNodeIdWithDialogId(int32_t dialogId)
{
    auto iter = maskNodeIdMap_.find(dialogId);
    return (iter == maskNodeIdMap_.end()) ? -1 : iter->second;
}

void OverlayManager::MountGatherNodeToRootNode(const RefPtr<FrameNode>& frameNode,
    const std::vector<GatherNodeChildInfo>& gatherNodeChildrenInfo)
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
    const std::vector<GatherNodeChildInfo>& gatherNodeChildrenInfo,
    const RefPtr<UINode>& windowScene)
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
    CHECK_EQUAL_VOID(hasGatherNode_, false);
    auto frameNode = gatherNodeWeak_.Upgrade();
    if (!frameNode) {
        hasGatherNode_ = false;
        gatherNodeWeak_ = nullptr;
        gatherNodeChildrenInfo_.clear();
        return;
    }
    TAG_LOGI(AceLogTag::ACE_DRAG, "Remove gather node");
    auto rootNode = frameNode->GetParent();
    CHECK_NULL_VOID(rootNode);
    rootNode->RemoveChild(frameNode);
    rootNode->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
    hasGatherNode_ = false;
    gatherNodeWeak_ = nullptr;
    gatherNodeChildrenInfo_.clear();
}

void OverlayManager::RemoveGatherNodeWithAnimation()
{
    if (!hasGatherNode_ || DragDropGlobalController::GetInstance().IsInMoving()) {
        return;
    }
    TAG_LOGI(AceLogTag::ACE_DRAG, "Remove gather node with animation");
    AnimationOption option;
    option.SetDuration(PIXELMAP_ANIMATION_DURATION);
    option.SetCurve(Curves::SHARP);

    option.SetOnFinishEvent([weak = gatherNodeWeak_] {
        auto context = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(context);
        auto taskExecutor = context->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        // animation finish event should be posted to UI thread.
        taskExecutor->PostTask(
            [weak, id = Container::CurrentId()]() {
                ContainerScope scope(id);
                auto frameNode = weak.Upgrade();
                CHECK_NULL_VOID(frameNode);
                auto rootNode = frameNode->GetParent();
                CHECK_NULL_VOID(rootNode);
                rootNode->RemoveChild(frameNode);
                rootNode->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
            },
            TaskExecutor::TaskType::UI, "ArkUIOverlayRemoveGatherNodeEvent");
    });
    gatherNodeWeak_ = nullptr;
    hasGatherNode_ = false;
    AnimationUtils::Animate(
        option,
        [gatherNodeChildrenInfo = gatherNodeChildrenInfo_]() {
            for (auto& child : gatherNodeChildrenInfo) {
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

void OverlayManager::UpdateGatherNodeToTop()
{
    auto frameNode = gatherNodeWeak_.Upgrade();
    CHECK_NULL_VOID(frameNode);
    auto rootNode = frameNode->GetParent();
    CHECK_NULL_VOID(rootNode);
    rootNode->RemoveChild(frameNode);
    frameNode->MountToParent(rootNode);
    frameNode->OnMountToParentDone();
    rootNode->RebuildRenderContextTree();
    rootNode->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
}

RefPtr<FrameNode> OverlayManager::GetPixelMapContentNode(bool isSubwindowOverlay) const
{
    if (isSubwindowOverlay) {
        RefPtr<FrameNode> imageNode = GetPixelMapContentNodeForSubwindow();
        return imageNode;
    }
    auto column = pixmapColumnNodeWeak_.Upgrade();
    CHECK_NULL_RETURN(column, nullptr);
    auto imageNode = AceType::DynamicCast<FrameNode>(column->GetFirstChild());
    return imageNode;
}

RefPtr<FrameNode> OverlayManager::GetPixelMapContentNodeForSubwindow() const
{
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_RETURN(rootNode, nullptr);
    for (const auto& child : rootNode->GetChildren()) {
        auto node = DynamicCast<FrameNode>(child);
        if (node && node->GetTag() != V2::MENU_WRAPPER_ETS_TAG) {
            continue;
        }
        for (auto& childNode : node->GetChildren()) {
            auto frameNode = DynamicCast<FrameNode>(childNode);
            if (frameNode &&
                (frameNode->GetTag() == V2::MENU_PREVIEW_ETS_TAG || frameNode->GetTag() == V2::IMAGE_ETS_TAG)) {
                return frameNode;
            }
        }
    }
    return nullptr;
}

void OverlayManager::UpdatePixelMapPosition(bool isSubwindowOverlay)
{
    if (!isSubwindowOverlay && !hasPixelMap_) {
        return;
    }
    if (IsOriginDragMoveVector() || !IsUpdateDragMoveVector()) {
        return;
    }
    auto moveVector = GetUpdateDragMoveVector();
    RefPtr<FrameNode> imageNode = GetPixelMapContentNode(isSubwindowOverlay);
    CHECK_NULL_VOID(imageNode);
    auto imageContext = imageNode->GetRenderContext();
    CHECK_NULL_VOID(imageContext);
    auto rect = imageNode->GetOffsetRelativeToWindow();
    imageContext->UpdatePosition(OffsetT<Dimension>(Dimension(moveVector.GetX() + rect.GetX()),
        Dimension(moveVector.GetY() + rect.GetY())));
    imageContext->OnModifyDone();
}

RefPtr<FrameNode> OverlayManager::GetDragPixelMapContentNode() const
{
    auto column = dragPixmapColumnNodeWeak_.Upgrade();
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

RefPtr<FrameNode> OverlayManager::GetDragPixelMapBadgeNode() const
{
    auto column = dragPixmapColumnNodeWeak_.Upgrade();
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
        [filterRenderContext, styleOption, maskColor, menuTheme]() {
            CHECK_NULL_VOID(filterRenderContext);
            if (menuTheme->GetHasBackBlur()) {
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
    RemoveChildWithService(rootNode, menu);
    rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void OverlayManager::DumpOverlayInfo() const
{
    auto container = Container::Current();
    if (container) {
        DumpLog::GetInstance().Print("Container: ");
        DumpLog::GetInstance().Print(DUMP_LOG_DEPTH_1, "ContainerId: " + std::to_string(container->GetInstanceId()));
        DumpLog::GetInstance().Print(
            DUMP_LOG_DEPTH_1, "IsSubContainer: " + std::string(container->IsSubContainer() ? "true" : "false"));
    }

    DumpLog::GetInstance().Print("----------PopupMapInfo----------");
    DumpPopupMapInfo();

    DumpLog::GetInstance().Print("----------MenuMapInfo----------");
    DumpMapInfo(menuMap_, "MenuMap");

    DumpLog::GetInstance().Print("----------DialogMapInfo----------");
    DumpMapInfo(dialogMap_, "DialogMap", false);

    DumpLog::GetInstance().Print("----------CustomPopupMapInfo----------");
    DumpMapInfo(customPopupMap_, "CustomPopupMap");

    DumpLog::GetInstance().Print("----------CustomKeyboardMapInfo----------");
    DumpMapInfo(customKeyboardMap_, "CustomKeyboardMap");

    DumpLog::GetInstance().Print("----------ToastMapInfo----------");
    DumpMapInfo(toastMap_, "ToastMap", false);

    DumpLog::GetInstance().Print("----------SheetMapInfo----------");
    DumpSheetMapInfo(sheetMap_, "SheetMap");

    DumpLog::GetInstance().Print("----------MaskNodeIdMapInfo----------");
    DumpMaskNodeIdMapInfo();

    DumpLog::GetInstance().Print("----------ModalListInfo----------");
    DumpModalListInfo();
}

void OverlayManager::DumpPopupMapInfo() const
{
    DumpLog::GetInstance().Print("PopupMap: ");
    DumpLog::GetInstance().Print(DUMP_LOG_DEPTH_1, "Size: " + std::to_string(popupMap_.size()));
    DumpLog::GetInstance().Print(DUMP_LOG_DEPTH_1, "Entries: [");

    for (const auto& entry : popupMap_) {
        std::string entryLog = "";
        auto targetId = entry.first;
        auto targetNode = ElementRegister::GetInstance()->GetSpecificItemById<FrameNode>(targetId);
        auto popupInfo = entry.second;
        auto popupNode = popupInfo.popupNode;
        DumpEntry(targetNode, targetId, popupNode);
    }

    DumpLog::GetInstance().Print(DUMP_LOG_DEPTH_1, "]");
}

void OverlayManager::DumpMapInfo(
    std::unordered_map<int32_t, RefPtr<FrameNode>> map, const std::string mapName, bool hasTarget) const
{
    DumpLog::GetInstance().Print(mapName + ": ");
    DumpLog::GetInstance().Print(DUMP_LOG_DEPTH_1, "Size: " + std::to_string(map.size()));
    DumpLog::GetInstance().Print(DUMP_LOG_DEPTH_1, "Entries: [");

    for (const auto& entry : map) {
        auto targetId = entry.first;
        auto targetNode = ElementRegister::GetInstance()->GetSpecificItemById<FrameNode>(targetId);
        auto node = entry.second;

        if (hasTarget) {
            DumpEntry(targetNode, targetId, node);
        } else {
            std::string entryLog = GetMapNodeLog(node, hasTarget);
            DumpLog::GetInstance().Print(DUMP_LOG_DEPTH_2, entryLog);
        }
    }

    DumpLog::GetInstance().Print(DUMP_LOG_DEPTH_1, "]");
}

void OverlayManager::DumpMapInfo(
    std::unordered_map<int32_t, WeakPtr<FrameNode>> map, const std::string mapName, bool hasTarget) const
{
    DumpLog::GetInstance().Print(mapName + ": ");
    DumpLog::GetInstance().Print(DUMP_LOG_DEPTH_1, "Size: " + std::to_string(map.size()));
    DumpLog::GetInstance().Print(DUMP_LOG_DEPTH_1, "Entries: [");

    for (const auto& entry : map) {
        auto targetId = entry.first;
        auto targetNode = ElementRegister::GetInstance()->GetSpecificItemById<FrameNode>(targetId);
        auto node = entry.second.Upgrade();
        if (hasTarget) {
            DumpEntry(targetNode, targetId, node);
        } else {
            std::string entryLog = GetMapNodeLog(node, hasTarget);
            DumpLog::GetInstance().Print(DUMP_LOG_DEPTH_2, entryLog);
        }
    }

    DumpLog::GetInstance().Print(DUMP_LOG_DEPTH_1, "]");
}

void OverlayManager::DumpSheetMapInfo(
    const std::unordered_map<SheetKey, WeakPtr<FrameNode>, SheetKeyHash>& map,
    const std::string mapName) const
{
    DumpLog::GetInstance().Print(mapName + ": ");
    DumpLog::GetInstance().Print(DUMP_LOG_DEPTH_1, "Size: " + std::to_string(map.size()));
    DumpLog::GetInstance().Print(DUMP_LOG_DEPTH_1, "Entries: [");

    for (const auto& entry : map) {
        auto targetId = entry.first.targetId;
        auto targetNode = ElementRegister::GetInstance()->GetSpecificItemById<FrameNode>(targetId);
        auto node = entry.second.Upgrade();
        DumpEntry(targetNode, targetId, node);
    }

    DumpLog::GetInstance().Print(DUMP_LOG_DEPTH_1, "]");
}

void OverlayManager::DumpMaskNodeIdMapInfo() const
{
    DumpLog::GetInstance().Print("MaskNodeIdMap: ");
    DumpLog::GetInstance().Print(DUMP_LOG_DEPTH_1, "Size: " + std::to_string(maskNodeIdMap_.size()));
    DumpLog::GetInstance().Print(DUMP_LOG_DEPTH_1, "Entries: [");

    for (const auto& entry : maskNodeIdMap_) {
        auto targetId = entry.first;
        auto targetNode = ElementRegister::GetInstance()->GetSpecificItemById<FrameNode>(targetId);
        auto nodeId = entry.second;
        auto node = ElementRegister::GetInstance()->GetSpecificItemById<FrameNode>(nodeId);
        std::string entryLog = "DialogId: " + std::to_string(targetId);
        entryLog += ", DialogTag: " + (targetNode ? targetNode->GetTag() : "NULL");
        entryLog += ", NodeId: " + std::to_string(nodeId);
        entryLog += ", NodeTag: " + (node ? node->GetTag() : "NULL");
        DumpLog::GetInstance().Print(DUMP_LOG_DEPTH_2, entryLog);
    }

    DumpLog::GetInstance().Print(DUMP_LOG_DEPTH_1, "]");
}

void OverlayManager::DumpModalListInfo() const
{
    DumpLog::GetInstance().Print("ModalList: ");
    DumpLog::GetInstance().Print(DUMP_LOG_DEPTH_1, "Size: " + std::to_string(modalList_.size()));
    DumpLog::GetInstance().Print(DUMP_LOG_DEPTH_1, "Entries: [");

    for (auto modal = modalList_.begin(); modal != modalList_.end(); ++modal) {
        std::string entryLog = "";
        auto modalNode = modal->Upgrade();
        entryLog += GetMapNodeLog(modalNode, false);
        DumpLog::GetInstance().Print(DUMP_LOG_DEPTH_2, entryLog);
    }

    DumpLog::GetInstance().Print(DUMP_LOG_DEPTH_1, "]");
}

void OverlayManager::DumpEntry(
    const RefPtr<FrameNode>& targetNode, int32_t targetId, const RefPtr<FrameNode>& node) const
{
    std::string entryLog = "TargetId: " + std::to_string(targetId);
    entryLog += ", TargetTag: " + (targetNode ? targetNode->GetTag() : "NULL");
    entryLog += GetMapNodeLog(node);
    DumpLog::GetInstance().Print(DUMP_LOG_DEPTH_2, entryLog);
}

std::string OverlayManager::GetMapNodeLog(const RefPtr<FrameNode>& node, bool hasTarget) const
{
    CHECK_NULL_RETURN(node, "");
    std::string entryLog = (hasTarget ? ", " : "");
    entryLog += "NodeId: " + std::to_string(node->GetId()) + ", NodeTag: " + node->GetTag();
    return entryLog;
}

void OverlayManager::OnUIExtensionWindowSizeChange()
{
    for (auto iter = dialogMap_.begin(); iter != dialogMap_.end(); iter++) {
        auto dialogNode = (*iter).second;
        CHECK_NULL_VOID(dialogNode);
        auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
        CHECK_NULL_VOID(dialogPattern);
        dialogPattern->InitHostWindowRect();
        dialogNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
}

void OverlayManager::MountToParentWithService(const RefPtr<UINode>& rootNode, const RefPtr<FrameNode>& node)
{
    CHECK_NULL_VOID(node);
    CHECK_NULL_VOID(rootNode);
    auto pipeline = rootNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    if (pipeline->GetInstallationFree() && SetNodeBeforeAppbar(rootNode, node)) {
        // it is in atomicservice
        return;
    }
    node->MountToParent(rootNode);
}
 
void OverlayManager::RemoveChildWithService(const RefPtr<UINode>& rootNode, const RefPtr<FrameNode>& node)
{
    CHECK_NULL_VOID(rootNode);
    CHECK_NULL_VOID(node);
    auto parent = node->GetParent();
    CHECK_NULL_VOID(parent);
    parent->RemoveChild(node);
}
 
bool OverlayManager::SetNodeBeforeAppbar(const RefPtr<NG::UINode>& rootNode, const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(rootNode, false);
    CHECK_NULL_RETURN(node, false);
    for (auto child : rootNode->GetChildren()) {
        CHECK_NULL_RETURN(child, false);
        if (child->GetTag() != V2::ATOMIC_SERVICE_ETS_TAG) {
            continue;
        }
        for (auto childNode : child->GetChildren()) {
            CHECK_NULL_RETURN(childNode, false);
            if (childNode->GetTag() == V2::APP_BAR_ETS_TAG) {
                TAG_LOGD(AceLogTag::ACE_OVERLAY, "setNodeBeforeAppbar AddChildBefore");
                child->AddChildBefore(node, childNode);
                return true;
            }
        }
    }
    return false;
}

bool OverlayManager::IsRootExpansive() const
{
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_RETURN(rootNode, false);
    auto pipelineContext = rootNode->GetContext();
    CHECK_NULL_RETURN(pipelineContext, false);
    auto manager = pipelineContext->GetSafeAreaManager();
    CHECK_NULL_RETURN(manager, false);
    if (manager->IsFullScreen()) {
        // if window is full screen, sheetPage should layout under 8vp + status bar height under parent
        return false;
    }

    // if page parent is full screen, sheetPage should layout 8vp under parent
    auto layoutProp = DynamicCast<FrameNode>(rootNode)->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProp, false);
    const auto& opts = layoutProp->GetSafeAreaExpandOpts();
    return opts && opts->Expansive();
}

void OverlayManager::RemoveMenuWrapperNode(const RefPtr<UINode>& rootNode)
{
    CHECK_NULL_VOID(rootNode);
    for (const auto& child : rootNode->GetChildren()) {
        auto node = DynamicCast<FrameNode>(child);
        if (node && node->GetTag() == V2::MENU_WRAPPER_ETS_TAG) {
            rootNode->RemoveChild(node);
        }
    }
}

void OverlayManager::SetDragNodeNeedClean()
{
    auto mainPipeline = PipelineContext::GetMainPipelineContext();
    CHECK_NULL_VOID(mainPipeline);
    auto dragDropManager = mainPipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    dragDropManager->SetIsDragNodeNeedClean(true);
}

BorderRadiusProperty OverlayManager::GetPrepareDragFrameNodeBorderRadius() const
{
    Dimension defaultDimension(0);
    BorderRadiusProperty borderRadius = { defaultDimension, defaultDimension, defaultDimension, defaultDimension };
    auto mainPipeline = PipelineContext::GetMainPipelineContext();
    CHECK_NULL_RETURN(mainPipeline, borderRadius);
    auto dragDropManager = mainPipeline->GetDragDropManager();
    CHECK_NULL_RETURN(dragDropManager, borderRadius);
    auto dragFrameNode = dragDropManager->GetPrepareDragFrameNode().Upgrade();
    CHECK_NULL_RETURN(dragFrameNode, borderRadius);
    return DragEventActuator::GetDragFrameNodeBorderRadius(dragFrameNode);
}

RefPtr<FrameNode> OverlayManager::GetLastChildNotRemoving(const RefPtr<UINode>& rootNode)
{
    const auto& children = rootNode->GetChildren();
    for (auto iter = children.rbegin(); iter != children.rend(); ++iter) {
        auto& child = *iter;
        if (!child->IsRemoving()) {
            return DynamicCast<FrameNode>(child);
        }
    }
    return nullptr;
}
} // namespace OHOS::Ace::NG
