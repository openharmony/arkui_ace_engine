/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/menu/menu_manager.h"

#include <cstdint>
#include <string>
#include <utility>
#include <vector>

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/log/log.h"
#include "base/subwindow/subwindow_manager.h"
#include "core/animation/animation_pub.h"
#include "core/animation/spring_curve.h"
#include "core/common/ace_application_info.h"
#include "core/common/container.h"
#include "core/components/common/properties/color.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/focus_hub.h"
#include "core/components_ng/manager/drag_drop/drag_drop_func_wrapper.h"
#include "core/components_ng/manager/drag_drop/drag_drop_global_controller.h"

#include "core/components_ng/pattern/menu/menu_item/menu_item_model_ng.h"
#include "core/components_ng/pattern/menu/menu_item_group/menu_item_group_view.h"
#include "core/components_ng/pattern/menu/menu_theme.h"
#include "core/components_ng/pattern/menu/menu_view.h"
#include "core/components_ng/pattern/menu/preview/menu_preview_pattern.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"
#include "core/components_ng/pattern/scrollable/selectable_utils.h"
#include "core/components_ng/pattern/overlay/level_order.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components_ng/pattern/menu/menu_tag_constants.h"
#if defined(ANDROID_PLATFORM) || defined(IOS_PLATFORM)
#include "transaction/rs_transaction_proxy.h"
#endif

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t MENU_ANIMATION_DURATION = 150;
const RefPtr<InterpolatingSpring> MENU_ANIMATION_CURVE =
    AceType::MakeRefPtr<InterpolatingSpring>(0.0f, 1.0f, 528.0f, 35.0f);
const RefPtr<InterpolatingSpring> CUSTOM_PREVIEW_ANIMATION_CURVE =
    AceType::MakeRefPtr<InterpolatingSpring>(0.0f, 1.0f, 280.0f, 30.0f);

const float MINIMUM_AMPLITUDE_RATION = 0.08f;
const float PREVIEW_MINIMUM_AMPLITUDE_RATION = 0.015f;

void ShowPreviewBgDisappearAnimationProc(const RefPtr<RenderContext>& previewRenderContext,
    const RefPtr<MenuTheme>& menuTheme, bool isShowHoverImage, const RefPtr<PipelineBase>& context)
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
        previewOption.SetDuration(MENU_ANIMATION_DURATION);
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
    }, nullptr, nullptr, context);
}

void UpdateHoverImagePreviewOpacityAnimation(const RefPtr<MenuTheme>& menuTheme,
    const RefPtr<MenuPattern>& menuPattern, RefPtr<FrameNode>& previewChild)
{
    CHECK_NULL_VOID(menuPattern);
    CHECK_NULL_VOID(menuPattern->GetIsShowHoverImage());

    CHECK_NULL_VOID(previewChild);
    auto previewRenderContext = previewChild->GetRenderContext();
    CHECK_NULL_VOID(previewRenderContext);

    bool isCustomPreview = previewChild->GetTag() == MENU_PREVIEW_ETS_TAG;
    // only update custom preview opacity
    CHECK_NULL_VOID(isCustomPreview);

    AnimationOption option;
    option.SetDuration(menuTheme->GetHoverImagePreviewDisAppearDuration());
    option.SetCurve(Curves::FRICTION);
    AnimationUtils::Animate(
        option, [previewRenderContext]() {
            CHECK_NULL_VOID(previewRenderContext);
            previewRenderContext->UpdateOpacity(0.0);
        }, nullptr, nullptr, previewChild->GetContextRefPtr());
}

void ShowPreviewDisappearAnimationProc(const RefPtr<MenuWrapperPattern>& menuWrapperPattern,
    RefPtr<FrameNode>& previewChild)
{
    CHECK_NULL_VOID(menuWrapperPattern);
    CHECK_NULL_VOID(previewChild);
    auto previewRenderContext = previewChild->GetRenderContext();
    CHECK_NULL_VOID(previewRenderContext);
    auto context = previewChild->GetContextRefPtr();
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

    auto pipelineContext = previewChild->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto menuTheme = pipelineContext->GetTheme<MenuTheme>();
    CHECK_NULL_VOID(menuTheme);
    UpdateHoverImagePreviewOpacityAnimation(menuTheme, menuPattern, previewChild);

    auto springMotionResponse = menuTheme->GetPreviewDisappearSpringMotionResponse();
    auto springMotionDampingFraction = menuTheme->GetPreviewDisappearSpringMotionDampingFraction();
    AnimationOption scaleOption;
    auto motion = AceType::MakeRefPtr<ResponsiveSpringMotion>(springMotionResponse, springMotionDampingFraction);
    scaleOption.SetCurve(motion);
    scaleOption.SetDuration(MENU_ANIMATION_DURATION);
    float previewScale = 1.0f;
    if (menuPattern->GetPreviewMode() == MenuPreviewMode::IMAGE ||
        (menuWrapperPattern->GetMenuParam().isPreviewContainScale &&
            menuWrapperPattern->GetMenuParam().disappearScaleToTarget)) {
        auto previewGeometryNode = previewChild->GetGeometryNode();
        CHECK_NULL_VOID(previewGeometryNode);
        auto previewSize = previewGeometryNode->GetFrameSize();
        if (!NearEqual(menuPattern->GetTargetSize().Width(), previewSize.Width())) {
            previewScale = menuPattern->GetTargetSize().Width() / previewSize.Width();
        }
    }
    ShowPreviewBgDisappearAnimationProc(
        previewRenderContext, menuTheme, menuWrapperPattern->GetIsShowHoverImage(), context);

    CHECK_NULL_VOID(!menuPattern->GetIsShowHoverImage());
    AnimationUtils::Animate(scaleOption,
        [previewRenderContext, previewPosition, previewScale]() {
        CHECK_NULL_VOID(previewRenderContext);
        previewRenderContext->UpdatePosition(
            OffsetT<Dimension>(Dimension(previewPosition.GetX()), Dimension(previewPosition.GetY())));
        previewRenderContext->UpdateTransformScale(VectorF(previewScale, previewScale));
    }, nullptr, nullptr, context);
}

void StopHoverImageDelayAnimation(
    const RefPtr<MenuWrapperPattern>& menuWrapperPattern, const NG::OffsetF& previewOriginOffset)
{
    CHECK_NULL_VOID(menuWrapperPattern);
    auto flexNode = menuWrapperPattern->GetHoverImageFlexNode();
    CHECK_NULL_VOID(flexNode);
    // stop delay animation for preview position
    AnimationUtils::Animate(AnimationOption(Curves::LINEAR, 0), [menuWrapperPattern, previewOriginOffset]() {
        CHECK_NULL_VOID(menuWrapperPattern);
        auto flexNode = menuWrapperPattern->GetHoverImageFlexNode();
        CHECK_NULL_VOID(flexNode);
        auto flexContext = flexNode->GetRenderContext();
        CHECK_NULL_VOID(flexContext);
        flexContext->UpdatePosition(
            OffsetT<Dimension>(Dimension(previewOriginOffset.GetX()), Dimension(previewOriginOffset.GetY())));
    }, nullptr, nullptr, flexNode->GetContextRefPtr());
}

AnimationOption GetHoverImageAnimationOption(const RefPtr<MenuWrapperPattern>& menuWrapperPattern)
{
    AnimationOption option = AnimationOption();
    CUSTOM_PREVIEW_ANIMATION_CURVE->UpdateMinimumAmplitudeRatio(PREVIEW_MINIMUM_AMPLITUDE_RATION);
    option.SetCurve(CUSTOM_PREVIEW_ANIMATION_CURVE);
    option.SetDuration(MENU_ANIMATION_DURATION);
    option.SetOnFinishEvent([menuWrapperPattern] {
        TAG_LOGI(AceLogTag::ACE_OVERLAY, "hover Image animation finished");
        CHECK_NULL_VOID(menuWrapperPattern);
        menuWrapperPattern->SetOnPreviewDisappear(false);

        auto menuWrapper = menuWrapperPattern->GetHost();
        CHECK_NULL_VOID(menuWrapper);
        auto pipeline = menuWrapper->GetContextRefPtr();
        CHECK_NULL_VOID(pipeline);
        auto overlayManager = pipeline->GetOverlayManager();
        CHECK_NULL_VOID(overlayManager);
        if (overlayManager->RemoveMenuInSubWindow(menuWrapper)) {
            overlayManager->SetIsMenuShow(false);
            overlayManager->PublishMenuStatus(false);
        }
    });

    return option;
}

void UpdateHoverImageDisappearScaleAndPosition(const RefPtr<MenuWrapperPattern>& menuWrapperPattern,
    const RefPtr<MenuPreviewPattern>& previewPattern)
{
    CHECK_NULL_VOID(menuWrapperPattern);
    CHECK_NULL_VOID(menuWrapperPattern->GetIsShowHoverImage());

    CHECK_NULL_VOID(previewPattern);
    // reverse scale
    auto scaleTo = previewPattern->GetHoverImageScaleFrom();
    auto host = previewPattern->GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto menuTheme = pipelineContext->GetTheme<MenuTheme>();
    CHECK_NULL_VOID(menuTheme);
    auto scaleAfter = LessNotEqual(scaleTo, 0.0) ? menuTheme->GetPreviewBeforeAnimationScale() : scaleTo;

    auto stackNode = menuWrapperPattern->GetHoverImageStackNode();
    CHECK_NULL_VOID(stackNode);
    auto stackContext = stackNode->GetRenderContext();
    CHECK_NULL_VOID(stackContext);
    auto context = stackNode->GetContextRefPtr();

    auto flexNode = menuWrapperPattern->GetHoverImageFlexNode();
    CHECK_NULL_VOID(flexNode);
    auto flexContext = flexNode->GetRenderContext();
    CHECK_NULL_VOID(flexContext);

    auto menuChild = menuWrapperPattern->GetMenu();
    CHECK_NULL_VOID(menuChild);
    auto menuPattern = menuChild->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    auto previewPosition = menuPattern->GetPreviewOriginOffset();

    if (previewPattern->IsHoverImageScalePlaying()) {
        menuWrapperPattern->SetIsStopHoverImageAnimation(true);
        previewPattern->SetIsHoverImageScalePlaying(false);
        MenuView::ShowMenuTargetScaleToOrigin(menuWrapperPattern, previewPattern);
        StopHoverImageDelayAnimation(menuWrapperPattern, previewPosition);
    }

    auto offset = previewPattern->GetHoverImageAfterScaleOffset();
    auto width = previewPattern->GetHoverImageAfterScaleWidth();
    auto height = previewPattern->GetHoverImageAfterScaleHeight();
    auto clipRect = RectF(offset.GetX(), offset.GetY(), width - offset.GetX(), height - offset.GetY());

    menuWrapperPattern->SetOnPreviewDisappear(true);
    TAG_LOGI(AceLogTag::ACE_OVERLAY, "start hover Image animation");
    AnimationOption option = GetHoverImageAnimationOption(menuWrapperPattern);
    AnimationUtils::Animate(option, [stackContext, scaleAfter, flexContext, previewPosition, clipRect]() {
        CHECK_NULL_VOID(stackContext);
        stackContext->UpdateTransformScale(VectorF(scaleAfter, scaleAfter));
        stackContext->ClipWithRRect(clipRect, RadiusF(EdgeF(0.0f, 0.0f)));

        CHECK_NULL_VOID(flexContext);
        flexContext->UpdatePosition(
            OffsetT<Dimension>(Dimension(previewPosition.GetX()), Dimension(previewPosition.GetY())));
    }, option.GetOnFinishEvent(), nullptr, context);

    ShowPreviewBgDisappearAnimationProc(
        stackContext, menuTheme, menuWrapperPattern->GetHoverImageStackNode(), context);
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

    auto pipelineContext = menu->GetContext();
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
    }, nullptr, nullptr, menuChild->GetContextRefPtr());
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
        }, nullptr, nullptr, previewChild->GetContextRefPtr());
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

    if (previewPattern->IsHoverImagePreviewScalePlaying()) {
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

    auto pipelineContext = menu->GetContext();
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
        option.GetOnFinishEvent(), nullptr, previewChild->GetContextRefPtr());
}

void CancelMenuTransformScaleAnimation(const RefPtr<FrameNode>& menuNode, float scale)
{
    CHECK_NULL_VOID(menuNode);
    auto renderContext = menuNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    AnimationOption cancelOption = AnimationOption(Curves::FAST_OUT_LINEAR_IN, 0);
    AnimationUtils::Animate(cancelOption, [renderContext, scale]() {
        CHECK_NULL_VOID(renderContext);
        renderContext->UpdateTransformScale({ scale, scale });
    }, nullptr, nullptr, menuNode->GetContextRefPtr());
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

    auto pipelineContext = menuChild->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto menuTheme = pipelineContext->GetTheme<MenuTheme>();
    CHECK_NULL_VOID(menuTheme);
    if (startDrag) {
        CancelMenuTransformScaleAnimation(menuChild, menuTheme->GetMenuDragAnimationScale());
    }
    auto springMotionResponse = menuTheme->GetPreviewDisappearSpringMotionResponse();
    auto springMotionDampingFraction = menuTheme->GetPreviewDisappearSpringMotionDampingFraction();
    AnimationOption positionOption;
    auto motion = AceType::MakeRefPtr<ResponsiveSpringMotion>(springMotionResponse, springMotionDampingFraction);
    positionOption.SetCurve(motion);
    positionOption.SetDuration(MENU_ANIMATION_DURATION);
    AnimationUtils::Animate(positionOption, [menuRenderContext, menuPosition]() {
        CHECK_NULL_VOID(menuRenderContext);
        menuRenderContext->UpdatePosition(
            OffsetT<Dimension>(Dimension(menuPosition.GetX()), Dimension(menuPosition.GetY())));
    }, nullptr, nullptr, menuChild->GetContextRefPtr());

    auto disappearDuration = menuTheme->GetDisappearDuration();
    auto menuAnimationScale = menuTheme->GetMenuAnimationScale();
    AnimationOption scaleOption = AnimationOption(Curves::FAST_OUT_LINEAR_IN, disappearDuration);
    AnimationUtils::Animate(scaleOption, [menuRenderContext, menuAnimationScale]() {
        CHECK_NULL_VOID(menuRenderContext);
        menuRenderContext->UpdateTransformScale({ menuAnimationScale, menuAnimationScale });
    }, nullptr, nullptr, menuChild->GetContextRefPtr());

    option.SetDuration(disappearDuration);
    option.SetCurve(Curves::FRICTION);
    AnimationUtils::Animate(
        option,
        [menuRenderContext]() {
            CHECK_NULL_VOID(menuRenderContext);
            menuRenderContext->UpdateOpacity(0.0);
        },
        option.GetOnFinishEvent(), nullptr, menuChild->GetContextRefPtr());
}

void FireMenuDisappear(AnimationOption& option, const RefPtr<MenuWrapperPattern>& menuWrapperPattern)
{
    CHECK_NULL_VOID(menuWrapperPattern);
    auto menuNode = menuWrapperPattern->GetMenu();
    CHECK_NULL_VOID(menuNode);
    auto menuRenderContext = menuNode->GetRenderContext();
    CHECK_NULL_VOID(menuRenderContext);
    auto pipelineContext = menuNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto menuTheme = pipelineContext->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(menuTheme);
    if (menuTheme->GetMenuAnimationDuration()) {
        option.SetDuration(menuTheme->GetMenuAnimationDuration());
        option.SetCurve(menuTheme->GetMenuAnimationCurve());
    } else {
        MENU_ANIMATION_CURVE->UpdateMinimumAmplitudeRatio(MINIMUM_AMPLITUDE_RATION);
        option.SetCurve(MENU_ANIMATION_CURVE);
    }
    AnimationUtils::Animate(
        option,
        [menuRenderContext, menuTheme]() {
            if (menuRenderContext) {
                CHECK_NULL_VOID(menuTheme);
                menuRenderContext->UpdateTransformScale(
                    VectorF(menuTheme->GetMenuAnimationScale(), menuTheme->GetMenuAnimationScale()));
                menuRenderContext->UpdateOpacity(0.0f);
            }
        },
        option.GetOnFinishEvent(), nullptr, menuNode->GetContextRefPtr());
}

// when one process not suppose handle other page event, firstly add, then remove
static void HandleAccessibilityPageEventControl(const RefPtr<FrameNode>& node, bool isAdd)
{
    if (!AceApplicationInfo::GetInstance().IsAccessibilityEnabled()) {
        return;
    }
    CHECK_NULL_VOID(node);
    auto pipelineContext = node->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto frontend = pipelineContext->GetFrontend();
    CHECK_NULL_VOID(frontend);
    auto accessibilityManager = frontend->GetAccessibilityManager();
    CHECK_NULL_VOID(accessibilityManager);
    if (isAdd) {
        accessibilityManager->AddToPageEventController(node);
    } else {
        accessibilityManager->ReleasePageEvent(node, true, true);
    }
}
} // namespace

MenuManager::MenuManager(const RefPtr<FrameNode>& rootNode) : rootNodeWeak_(rootNode)
{
    if (rootNode) {
        context_ = rootNode->GetContext();
    }
}

MenuManager::~MenuManager()
{
    TAG_LOGI(AceLogTag::ACE_OVERLAY, "MenuManager destroyed");
    menuMap_.clear();
}

void MenuManager::UpdateContextMenuDisappearPosition(
    const NG::OffsetF& offset, float menuScale, bool isRedragStart, int32_t menuWrapperId)
{
    auto pipelineContext = GetPipelineContext();
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

    CHECK_NULL_VOID(menuWrapper && menuWrapper->GetTag() == MENU_WRAPPER_ETS_TAG);
    overlayManager->UpdateDragMoveVector(offset);

    if (overlayManager->IsOriginDragMoveVector() || !overlayManager->IsUpdateDragMoveVector()) {
        return;
    }

    UpdateContextMenuDisappearPositionAnimation(menuWrapper, overlayManager->GetUpdateDragMoveVector(), menuScale);
}

OffsetF MenuManager::CalculateMenuPosition(const RefPtr<FrameNode>& menuWrapperNode,
    const RefPtr<OverlayManager>& overlayManager, const OffsetF& offset)
{
    CHECK_NULL_RETURN(menuWrapperNode, OffsetF(0.0f, 0.0f));
    CHECK_NULL_RETURN(overlayManager, OffsetF(0.0f, 0.0f));
    if (overlayManager->IsContextMenuDragHideFinished()) {
        return OffsetF(0.0f, 0.0f);
    }
    auto updateOffset = DragDropFuncWrapper::GetPointRelativeToMainWindow({offset.GetX(), offset.GetY()});
    overlayManager->UpdateDragMoveVector(updateOffset);
    if (menuMap_.empty() || overlayManager->IsOriginDragMoveVector() ||
        !overlayManager->IsUpdateDragMoveVector()) {
        return OffsetF(0.0f, 0.0f);
    }

    auto menuWrapperPattern = menuWrapperNode->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_RETURN(menuWrapperPattern, OffsetF(0.0f, 0.0f));
    auto menuNode = menuWrapperPattern->GetMenu();
    CHECK_NULL_RETURN(menuNode, OffsetF(0.0f, 0.0f));
    auto menuOffset = overlayManager->GetUpdateDragMoveVector();
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

bool MenuManager::GetMenuPreviewCenter(NG::OffsetF& offset)
{
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_RETURN(rootNode, false);
    for (const auto& child : rootNode->GetChildren()) {
        auto node = DynamicCast<FrameNode>(child);
        if (node && node->GetTag() == MENU_WRAPPER_ETS_TAG) {
            auto menuWarpperPattern = node->GetPattern<MenuWrapperPattern>();
            CHECK_NULL_RETURN(menuWarpperPattern, false);
            auto previewChild = menuWarpperPattern->GetPreview();
            CHECK_NULL_RETURN(previewChild, false);
            auto geometryNode = previewChild->GetGeometryNode();
            if (geometryNode && geometryNode->GetFrameRect().IsEmpty()) {
                return false;
            }
            auto previewOffset = DragDropFuncWrapper::GetPaintRectCenterToScreen(previewChild);
            offset.SetX(previewOffset.GetX());
            offset.SetY(previewOffset.GetY());
            return true;
        }
    }
    return false;
}

void MenuManager::ContextMenuSwitchDragPreviewAnimation(const RefPtr<NG::FrameNode>& dragPreviewNode,
    const NG::OffsetF& offset)
{
    CHECK_NULL_VOID(dragPreviewNode);
    if (menuMap_.empty()) {
        return;
    }
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_VOID(rootNode);
    for (const auto& child : rootNode->GetChildren()) {
        auto node = DynamicCast<FrameNode>(child);
        if (node && node->GetTag() == MENU_WRAPPER_ETS_TAG) {
            UpdateContextMenuSwitchDragPreviewBefore(node);
            ContextMenuSwitchDragPreviewAnimationProc(node, dragPreviewNode, offset);
        }
    }
}

void MenuManager::UpdateMenuVisibility(const RefPtr<FrameNode>& menu)
{
    CHECK_NULL_VOID(menu);
    auto layoutProperty = menu->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateVisibility(VisibleType::VISIBLE, true);
}

void MenuManager::OnShowMenuAnimationFinished(const WeakPtr<FrameNode> menuWK, const WeakPtr<OverlayManager> weak,
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
    auto levelOrder = overlayManager->GetLevelOrder(menu);
    if (!menuLayoutProp->GetIsRectInTargetValue(false) && overlayManager->IsTopOrder(levelOrder)) {
        overlayManager->FocusOverlayNode(menu);
    }
    auto menuWrapperPattern = menu->GetPattern<MenuWrapperPattern>();
    menuWrapperPattern->CallMenuAppearCallback();
    menuWrapperPattern->CallMenuOnDidAppearCallback();
    if (!menuWrapperPattern->IsHide()) {
        menuWrapperPattern->SetMenuStatus(MenuStatus::SHOW);
    }
    overlayManager->ContentChangeReport(menu, true);
}

void MenuManager::SetPreviewFirstShow(const RefPtr<FrameNode>& menu, const RefPtr<OverlayManager>& overlayManager)
{
    CHECK_NULL_VOID(menu);
    auto wrapperPattern = menu->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(wrapperPattern);
    auto previewChild = wrapperPattern->GetPreview();
    CHECK_NULL_VOID(previewChild);
    auto previewPattern = AceType::DynamicCast<MenuPreviewPattern>(previewChild->GetPattern());
    CHECK_NULL_VOID(previewPattern);
    previewPattern->SetFirstShow();
    CHECK_NULL_VOID(overlayManager);
    overlayManager->ContentChangeReport(menu, true);
}

void MenuManager::ShowMenuAnimation(const RefPtr<FrameNode>& menu,
    const RefPtr<OverlayManager>& overlayManager)
{
    TAG_LOGI(AceLogTag::ACE_OVERLAY, "show menu animation enter");
    CHECK_NULL_VOID(menu);
    CHECK_NULL_VOID(overlayManager);
    overlayManager->BlurLowerNode(menu);
    auto wrapperPattern = menu->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(wrapperPattern);
    // delay until end of target hoverScale for interruption
    if (!wrapperPattern->GetHoverScaleInterruption()) {
        wrapperPattern->CallMenuAboutToAppearCallback();
    }

    wrapperPattern->SetMenuStatus(MenuStatus::ON_SHOW_ANIMATION);
    SetIsMenuShow(true, menu);
    PublishMenuStatus(true, menu);
    overlayManager->ResetContextMenuDragHideFinished();
    if (wrapperPattern->HasTransitionEffect()) {
        TAG_LOGD(AceLogTag::ACE_OVERLAY, "show menu animation with transition effect");
        UpdateMenuVisibility(menu);
        auto renderContext = menu->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        renderContext->SetTransitionInCallback(
            [menuManagerWeak = WeakClaim(this), menuWK = WeakClaim(RawPtr(menu)),
                id = Container::CurrentId(),
                overlayManagerWeak = AceType::WeakClaim(AceType::RawPtr(overlayManager))] {
                auto menuManager = menuManagerWeak.Upgrade();
                CHECK_NULL_VOID(menuManager);
                menuManager->OnShowMenuAnimationFinished(menuWK, overlayManagerWeak, id);
                menuManager->SendToAccessibility(menuWK, overlayManagerWeak, true);
            });
        if (wrapperPattern->GetPreviewMode() == MenuPreviewMode::CUSTOM) {
            SetPreviewFirstShow(menu, overlayManager);
        }
        SetPatternFirstShow(menu);
        return;
    }
    AnimationOption option;
    UpdateMenuAnimationOptions(menu, option, overlayManager);
    if (wrapperPattern->GetPreviewMode() == MenuPreviewMode::CUSTOM) {
        auto pipelineContext = GetPipelineContext();
        CHECK_NULL_VOID(pipelineContext);
        auto menuTheme = pipelineContext->GetTheme<NG::MenuTheme>();
        CHECK_NULL_VOID(menuTheme);
        option.SetDuration(menuTheme->GetContextMenuAppearDuration());
        SetPreviewFirstShow(menu, overlayManager);
    }
    wrapperPattern->SetAniamtinOption(option);
    SetPatternFirstShow(menu);
}

void MenuManager::UpdateMenuAnimationOptions(const RefPtr<FrameNode>& menu,
    AnimationOption& option, const RefPtr<OverlayManager>& overlayManager)
{
    CHECK_NULL_VOID(menu);
    auto pipelineContext = menu->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto menuTheme = pipelineContext->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(menuTheme);
    if (menuTheme->GetMenuAnimationDuration()) {
        option.SetDuration(menuTheme->GetMenuAnimationDuration());
    } else {
        option.SetDuration(MENU_ANIMATION_DURATION);
    }
    option.SetCurve(menuTheme->GetMenuAnimationCurve());
    option.SetFillMode(FillMode::FORWARDS);
    option.SetOnFinishEvent(
        [menuManagerWeak = WeakClaim(this), menuWK = WeakClaim(RawPtr(menu)),
            id = pipelineContext->GetInstanceId(),
            overlayManagerWeak = AceType::WeakClaim(AceType::RawPtr(overlayManager))] {
            auto menuManager = menuManagerWeak.Upgrade();
            CHECK_NULL_VOID(menuManager);
            menuManager->OnShowMenuAnimationFinished(menuWK, overlayManagerWeak, id);
            menuManager->SendToAccessibility(menuWK, overlayManagerWeak, true);
        });
}

void MenuManager::SendToAccessibility(const WeakPtr<FrameNode> node,
    const WeakPtr<OverlayManager> overlayWeak, bool isShow)
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
    auto overlayManager = overlayWeak.Upgrade();
    CHECK_NULL_VOID(overlayManager);
    if (isShow) {
        auto levelOrder = overlayManager->GetLevelOrder(menuWrapper);
        if (overlayManager->IsTopOrder(levelOrder)) {
            menu->OnAccessibilityEvent(AccessibilityEventType::PAGE_OPEN,
                WindowsContentChangeTypes::CONTENT_CHANGE_TYPE_SUBTREE);
            TAG_LOGI(AceLogTag::ACE_OVERLAY, "Send event to %{public}d",
                static_cast<int32_t>(AccessibilityEventType::PAGE_OPEN));
        }
    } else {
        HandleAccessibilityPageEventControl(menu, false);
        menu->OnAccessibilityEvent(AccessibilityEventType::PAGE_CLOSE,
            WindowsContentChangeTypes::CONTENT_CHANGE_TYPE_SUBTREE);
        TAG_LOGI(AceLogTag::ACE_OVERLAY, "Send event to %{public}d",
            static_cast<int32_t>(AccessibilityEventType::PAGE_CLOSE));
    }
}

void MenuManager::SetPatternFirstShow(const RefPtr<FrameNode>& menu)
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

void MenuManager::OnPopMenuAnimationFinished(const WeakPtr<FrameNode> menuWK, const WeakPtr<UINode> rootWeak,
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
    auto overlayManager = weak.Upgrade();
    CHECK_NULL_VOID(overlayManager);

    overlayManager->SetContextMenuDragHideFinished(true);
    overlayManager->ContentChangeReport(menu, false);
    DragEventActuator::ExecutePreDragAction(PreDragStatus::PREVIEW_LANDING_FINISHED);
    auto menuWrapperPattern = menu->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(menuWrapperPattern);
    if (MenuView::GetMenuHoverScaleStatus(menuWrapperPattern->GetTargetId()) != MenuHoverScaleStatus::INTERRUPT &&
        menuWrapperPattern->GetMenuStatus() != MenuStatus::HIDE) {
        menuWrapperPattern->CallMenuDisappearCallback();
        menuWrapperPattern->CallMenuOnDidDisappearCallback();
    }
    HandleMenuDisappearCallback(menu);
    // clear contextMenu then return
    auto pipeline = GetPipelineContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    auto expandDisplay = theme->GetExpandDisplay();
    auto menuLayoutProp = menuPattern->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_VOID(menuLayoutProp);
    bool isShowInSubWindow = menuLayoutProp->GetShowInSubWindowValue(true);
    auto targetId = menuWrapperPattern->GetTargetId();
    EraseMenuInfo(targetId);
    if ((menuWrapperPattern->IsContextMenu() ||
            (isShowInSubWindow && (expandDisplay || menuWrapperPattern->GetIsOpenMenu()))) &&
        (!menuPattern->IsSelectMenu())) {
        if (RemoveMenuInSubWindow(menu, overlayManager)) {
            SetIsMenuShow(false, nullptr);
        }
        return;
    }
    if (CheckSelectSubWindowToClose(menu, overlayManager, expandDisplay)) {
        return;
    }
    RemoveMenuNotInSubWindow(menuWK, rootWeak, weak);
    SetIsMenuShow(false, nullptr);
}

void MenuManager::HandleMenuDisappearCallback(const RefPtr<FrameNode>& menu)
{
    CHECK_NULL_VOID(menu);
    auto menuWrapperPattern = menu->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(menuWrapperPattern);
    menuWrapperPattern->SetMenuStatus(MenuStatus::HIDE);
    menuWrapperPattern->SetOnMenuDisappear(false);
    menuWrapperPattern->CallMenuStateChangeCallback("false");
    auto mainPipeline = PipelineContext::GetMainPipelineContext();
    if (mainPipeline && menuWrapperPattern->GetMenuDisappearCallback()) {
        ContainerScope scope(mainPipeline->GetInstanceId());
        mainPipeline->FlushPipelineImmediately();
    }
}

bool MenuManager::CheckSelectSubWindowToClose(
    const RefPtr<FrameNode>& menu, const RefPtr<OverlayManager>& overlayManager, bool expandDisplay)
{
    CHECK_NULL_RETURN(menu, false);
    CHECK_NULL_RETURN(overlayManager, false);
    auto menuNode = AceType::DynamicCast<FrameNode>(menu->GetChildAtIndex(0));
    CHECK_NULL_RETURN(menuNode, false);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    CHECK_NULL_RETURN(menuPattern, false);
    auto menuLayoutProp = menuPattern->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_RETURN(menuLayoutProp, false);
    if (expandDisplay && !menuPattern->IsSelectMenu() &&
        menuLayoutProp->GetShowInSubWindowValue(false)) {
        auto subWindowManager = SubwindowManager::GetInstance();
        CHECK_NULL_RETURN(subWindowManager, false);
        auto context = menu->GetContextRefPtr();
        CHECK_NULL_RETURN(context, false);
        auto containerid = context->GetInstanceId();
        auto subwindow = subWindowManager->GetSubwindowByType(containerid, SubwindowType::TYPE_MENU);
        if (subWindowManager->IsSubwindowExist(subwindow)) {
            if (RemoveMenuInSubWindow(menu, overlayManager)) {
                SetIsMenuShow(false, nullptr);
                PublishMenuStatus(false, nullptr);
                return true;
            }
        }
    }
    return false;
}

void MenuManager::PopMenuAnimation(const RefPtr<FrameNode>& menu,
    const RefPtr<OverlayManager>& overlayManager,
    bool showPreviewAnimation, bool startDrag)
{
    TAG_LOGI(AceLogTag::ACE_OVERLAY, "pop menu animation enter");
    CHECK_NULL_VOID(menu);
    auto wrapperPattern = menu->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(wrapperPattern);

    if (wrapperPattern->IsHide()) {
        return;
    }

    PublishMenuStatus(false, nullptr);
    CHECK_NULL_VOID(overlayManager);
    overlayManager->ResetLowerNodeFocusable(menu);
    overlayManager->ResetContextMenuDragHideFinished();
    RemoveMenuBadgeNode(menu);

    auto menuNode = AceType::DynamicCast<FrameNode>(menu->GetChildAtIndex(0));
    CHECK_NULL_VOID(menuNode);
    auto eventHub = menuNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabledInternal(false);

    if (MenuView::GetMenuHoverScaleStatus(wrapperPattern->GetTargetId()) != MenuHoverScaleStatus::INTERRUPT &&
        wrapperPattern->GetMenuStatus() != MenuStatus::HIDE) {
        wrapperPattern->CallMenuAboutToDisappearCallback();
        wrapperPattern->CallMenuOnWillDisappearCallback();
    }

    wrapperPattern->SetMenuStatus(MenuStatus::ON_HIDE_ANIMATION);
    wrapperPattern->SetOnMenuDisappear(true);
    if (wrapperPattern->HasTransitionEffect() || wrapperPattern->HasFoldModeChangedTransition()) {
        ShowMenuDisappearTransition(menu, overlayManager);
        return;
    }

    AnimationOption option;
    auto pipelineContext = menu->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto menuTheme = pipelineContext->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(menuTheme);
    if (menuTheme->GetMenuAnimationDuration()) {
        option.SetDuration(menuTheme->GetMenuAnimationDuration());
    } else {
        option.SetDuration(MENU_ANIMATION_DURATION);
    }
    option.SetCurve(menuTheme->GetMenuAnimationCurve());
    option.SetFillMode(FillMode::FORWARDS);
    if (!startDrag) {
        DragEventActuator::ExecutePreDragAction(PreDragStatus::PREVIEW_LANDING_STARTED);
    }
    option.SetOnFinishEvent([rootWeak = rootNodeWeak_, menuWK = WeakClaim(RawPtr(menu)), id = Container::CurrentId(),
                                menuManagerWeak = WeakClaim(this),
                                overlayManagerWeak = AceType::WeakClaim(AceType::RawPtr(overlayManager))] {
        ContainerScope scope(id);
        auto menuManager = menuManagerWeak.Upgrade();
        CHECK_NULL_VOID(menuManager);
        menuManager->SendToAccessibility(menuWK, overlayManagerWeak, false);
        menuManager->OnPopMenuAnimationFinished(menuWK, rootWeak, overlayManagerWeak, id);
    });
    HandleAccessibilityPageEventControl(menu, true);
    ShowMenuClearAnimation(menu, option, showPreviewAnimation, startDrag);
}

void MenuManager::ShowMenuDisappearTransition(const RefPtr<FrameNode>& menu,
    const RefPtr<OverlayManager>& overlayManager)
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
        HandleAccessibilityPageEventControl(menu, true);
        renderContext->SetTransitionOutCallback([rootWeak = rootNodeWeak_, menuWK = WeakClaim(RawPtr(menu)),
            id = Container::CurrentId(),
            menuManagerWeak = WeakClaim(this),
            overlayManagerWeak = AceType::WeakClaim(AceType::RawPtr(overlayManager))] {
            ContainerScope scope(id);
            auto menuManager = menuManagerWeak.Upgrade();
            CHECK_NULL_VOID(menuManager);
            menuManager->SendToAccessibility(menuWK, overlayManagerWeak, false);
            menuManager->OnPopMenuAnimationFinished(menuWK, rootWeak, overlayManagerWeak, id);
        });
    } else {
        auto context = GetPipelineContext();
        CHECK_NULL_VOID(context);
        auto taskExecutor = context->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        taskExecutor->PostTask(
            [rootWeak = rootNodeWeak_, menuWK = WeakClaim(RawPtr(menu)), id = Container::CurrentId(),
                menuManagerWeak = WeakClaim(this),
                overlayManagerWeak = AceType::WeakClaim(AceType::RawPtr(overlayManager))] {
                ContainerScope scope(id);
                auto menuManager = menuManagerWeak.Upgrade();
                CHECK_NULL_VOID(menuManager);
                menuManager->SendToAccessibility(menuWK, overlayManagerWeak, false);
                menuManager->OnPopMenuAnimationFinished(menuWK, rootWeak, overlayManagerWeak, id);
            },
            TaskExecutor::TaskType::UI, "ArkUIOverlayPopMenuAnimation");
    }
}

void MenuManager::ShowMenuClearAnimation(const RefPtr<FrameNode>& menuWrapper, AnimationOption& option,
    bool showPreviewAnimation, bool startDrag)
{
    TAG_LOGI(AceLogTag::ACE_OVERLAY, "show menuWrapper clear animation enter");
    CHECK_NULL_VOID(menuWrapper);
    auto context = menuWrapper->GetRenderContext();
    CHECK_NULL_VOID(context);
    auto pipeline = GetPipelineContext();
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
    auto menuTheme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(menuTheme);
    if (!isPreviewModeNone ||
        (isPreviewModeNone && IsContextMenuBindedOnOrigNode() && !showPreviewAnimation && startDrag)) {
        showPreviewAnimation ? ShowPreviewDisappearAnimation(menuWrapperPattern) : CleanPreviewInSubWindow();
        ShowContextMenuDisappearAnimation(option, menuWrapperPattern, startDrag);
    } else if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE) && isShow) {
        FireMenuDisappear(option, menuWrapperPattern);
    } else {
        AnimationUtils::Animate(
            option,
            [context, menuAnimationOffset, menuTheme]() {
                CHECK_NULL_VOID(context);
                context->UpdateOpacity(0.0);
                context->UpdateOffset(menuAnimationOffset);
                CHECK_NULL_VOID(menuTheme);
                if (menuTheme->GetMenuAnimationDuration()) {
                    context->UpdateTransformScale(
                        VectorF(menuTheme->GetMenuAnimationScale(), menuTheme->GetMenuAnimationScale()));
                }
            },
            option.GetOnFinishEvent(), nullptr, menuWrapper->GetContextRefPtr());
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
bool MenuManager::IsContextMenuBindedOnOrigNode()
{
    auto mainPipeline = PipelineContext::GetMainPipelineContext();
    CHECK_NULL_RETURN(mainPipeline, false);
    auto dragDropManager = mainPipeline->GetDragDropManager();
    CHECK_NULL_RETURN(dragDropManager, false);
    auto draggingNode = DragDropGlobalController::GetInstance().GetPrepareDragFrameNode().Upgrade();
    CHECK_NULL_RETURN(draggingNode, false);
    auto eventHub = draggingNode->GetEventHub<EventHub>();
    CHECK_NULL_RETURN(eventHub, false);
    auto frameNode = eventHub->GetFrameNode();
    CHECK_NULL_RETURN(frameNode, false);
    auto focusHub = frameNode->GetFocusHub();
    CHECK_NULL_RETURN(focusHub, false);
    return focusHub->FindContextMenuOnKeyEvent(OnKeyEventType::CONTEXT_MENU);
}

void MenuManager::HideAllMenusWithoutAnimation(const RefPtr<OverlayManager>& overlayManager, bool showInSubwindow)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "hide all menu without animation enter");
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_VOID(rootNode);
    auto tempMenuMap = menuMap_;
    CHECK_NULL_VOID(overlayManager);
    for (const auto& menu : tempMenuMap) {
        auto targetId = menu.first;
        auto menuNode = menu.second;
        CHECK_NULL_CONTINUE(menuNode);
        auto menuWrapperPattern = menuNode->GetPattern<MenuWrapperPattern>();
        CHECK_NULL_CONTINUE(menuWrapperPattern);
        CallMenuDisappearWithStatus(menuNode);
        menuWrapperPattern->SetOnMenuDisappear(false);
        menuWrapperPattern->CallMenuStateChangeCallback("false");
        auto containerId = menuWrapperPattern->GetContainerId();
        overlayManager->RemoveChildWithService(rootNode, menuNode);
        TAG_LOGI(AceLogTag::ACE_OVERLAY, "hide menu without animation, targetId: %{public}d", targetId);
        rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        if (showInSubwindow) {
            SubwindowManager::GetInstance()->DeleteHotAreas(containerId, menuNode->GetId(), SubwindowType::TYPE_MENU);
        }
        RemoveMenuFilter(menuNode, false);
        EraseMenuInfo(targetId);
        SetIsMenuShow(false, nullptr);
        PublishMenuStatus(false, nullptr);
        auto pipeline = menuNode->GetContext();
        CHECK_NULL_CONTINUE(pipeline);
        auto overlay = pipeline->GetOverlayManager();
        CHECK_NULL_CONTINUE(overlay);
        overlay->ContentChangeReport(menuNode, false);
    }
}

void MenuManager::ResetMenuWrapperVisibility(const RefPtr<FrameNode>& menuWrapper)
{
    CHECK_NULL_VOID(menuWrapper);
    auto menuWrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(menuWrapperPattern);
    menuWrapperPattern->SetHasFoldModeChangedTransition(false);
    auto layoutProperty = menuWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateVisibility(VisibleType::VISIBLE);
}

bool MenuManager::ShowMenuHelper(RefPtr<FrameNode>& menu, int32_t targetId, const NG::OffsetF& offset)
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
    ResetMenuWrapperVisibility(menu);
    RefPtr<FrameNode> menuFrameNode = menu;
    if (menu->GetTag() != MENU_ETS_TAG) {
        auto menuChild = menu->GetChildAtIndex(0);
        CHECK_NULL_RETURN(menuChild, false);
        menuFrameNode = DynamicCast<FrameNode>(menuChild);
    }
    CHECK_NULL_RETURN(menuFrameNode, false);
    auto props = menuFrameNode->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_RETURN(props, false);
    props->UpdateMenuOffset(offset);
    menuFrameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    return true;
}

void MenuManager::ShowMenu(const RefPtr<OverlayManager>& overlayManager,
    int32_t targetId, const NG::OffsetF& offset, RefPtr<FrameNode> menu)
{
    TAG_LOGI(AceLogTag::ACE_OVERLAY, "show menu enter");
    if (!ShowMenuHelper(menu, targetId, offset)) {
        TAG_LOGW(AceLogTag::ACE_OVERLAY, "show menu helper failed");
        return;
    }
    auto rootNode = rootNodeWeak_.Upgrade();
    auto container = Container::Current();
    CHECK_NULL_VOID(overlayManager);
    if (container && container->IsSceneBoardWindow()) {
        auto wrapperPattern = AceType::DynamicCast<MenuWrapperPattern>(menu->GetPattern());
        CHECK_NULL_VOID(wrapperPattern);
        auto menuChild = wrapperPattern->GetMenu();
        CHECK_NULL_VOID(menuChild);
        auto menuPattern = AceType::DynamicCast<MenuPattern>(menuChild->GetPattern());
        CHECK_NULL_VOID(menuPattern);
        rootNode = overlayManager->FindWindowScene(FrameNode::GetFrameNode(menuPattern->GetTargetTag(),
            menuPattern->GetTargetId()));
    }
    CHECK_NULL_VOID(rootNode);
    auto rootChildren = rootNode->GetChildren();
    auto iter = std::find(rootChildren.begin(), rootChildren.end(), menu);
    // menuNode already showing
    if (iter == rootChildren.end()) {
        auto levelOrder = overlayManager->GetLevelOrder(menu);
        overlayManager->MountToParentWithService(rootNode, menu, levelOrder);
        rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        menu->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        ShowMenuAnimation(menu, overlayManager);
        menu->MarkModifyDone();
    }
}

// subwindow only contains one menu instance.
void MenuManager::ShowMenuInSubWindow(const RefPtr<OverlayManager>& overlayManager,
    int32_t targetId, const NG::OffsetF& offset, RefPtr<FrameNode> menu)
{
    TAG_LOGI(AceLogTag::ACE_OVERLAY, "show menu insubwindow enter");
    if (!ShowMenuHelper(menu, targetId, offset)) {
        TAG_LOGW(AceLogTag::ACE_OVERLAY, "show menu helper failed");
        return;
    }
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_VOID(rootNode);
    auto pipeline = rootNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    RemoveMenuWrapperNode(rootNode, pipeline);

    auto menuWrapperPattern = menu->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(menuWrapperPattern);
    CHECK_NULL_VOID(overlayManager);
    if ((menuWrapperPattern->IsContextMenu() || menuWrapperPattern->GetIsOpenMenu()) &&
        (menuWrapperPattern->GetPreviewMode() != MenuPreviewMode::NONE || menuWrapperPattern->GetMenuMaskEnable())) {
        auto filterNode = menuWrapperPattern->GetFilterColumnNode();
        if (filterNode && menuWrapperPattern->GetIsFilterInSubwindow()) {
            overlayManager->SetHasFilter(true);
            overlayManager->SetFilterColumnNode(filterNode);
            filterNode->MountToParent(rootNode);
            ShowFilterAnimation(filterNode, menuWrapperPattern->GetHost(), overlayManager);
            filterNode->MarkModifyDone();
        }
    }
    menu->MountToParent(rootNode);
    ShowMenuAnimation(menu, overlayManager);
    menu->MarkModifyDone();
    rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    pipeline->FlushUITasks();

    // set subwindow container id in menu.
    auto menuPattern = menu->GetPattern<PopupBasePattern>();
    CHECK_NULL_VOID(menuPattern);
    menuPattern->SetContainerId(Container::CurrentId());
}

void MenuManager::HideMenuInSubWindow(const RefPtr<FrameNode>& menu,
    const RefPtr<OverlayManager>& overlayManager, int32_t targetId)
{
    TAG_LOGI(AceLogTag::ACE_OVERLAY, "hide menu insubwindow enter, id: %{public}d", menu ? menu->GetId() : -1);
    CHECK_NULL_VOID(menu);
    if (menu && menu->GetTag() == MENU_WRAPPER_ETS_TAG) {
        auto wrapperPattern = menu->GetPattern<MenuWrapperPattern>();
        CHECK_NULL_VOID(wrapperPattern);
        wrapperPattern->UpdateMenuAnimation(menu);
    }
    CHECK_NULL_VOID(overlayManager);
    PopMenuAnimation(menu, overlayManager);
    RemoveMenuFilter(menu);
}

void MenuManager::HideMenuInSubWindow(const RefPtr<OverlayManager>& overlayManager,
    bool showPreviewAnimation, bool startDrag)
{
    TAG_LOGI(AceLogTag::ACE_OVERLAY, "hide menu insubwindow enter");
    if (menuMap_.empty()) {
        return;
    }
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_VOID(rootNode);
    auto children = rootNode->GetChildren();
    CHECK_NULL_VOID(overlayManager);
    for (const auto& child : children) {
        auto node = DynamicCast<FrameNode>(child);
        if (node->GetTag() == MENU_WRAPPER_ETS_TAG) {
            PopMenuAnimation(node, overlayManager, showPreviewAnimation, startDrag);
            RemoveMenuFilter(node);
        }
    }
}

RefPtr<FrameNode> MenuManager::GetMenuNodeWithExistContent(const RefPtr<UINode>& node)
{
    CHECK_NULL_RETURN(node, nullptr);
    auto iter = menuMap_.begin();
    while (iter != menuMap_.end()) {
        auto menuNode = (*iter).second;
        CHECK_NULL_RETURN(menuNode, nullptr);
        auto menuWrapperPattern = menuNode->GetPattern<NG::MenuWrapperPattern>();
        CHECK_NULL_RETURN(menuWrapperPattern, nullptr);
        auto menu = menuWrapperPattern->GetMenu();
        CHECK_NULL_RETURN(menu, nullptr);
        auto menuPattern = AceType::DynamicCast<MenuPattern>(menu->GetPattern());
        CHECK_NULL_RETURN(menuPattern, nullptr);
        if (menuPattern->GetCustomNode() == node) {
            return menuNode;
        }
        iter++;
    }
    return nullptr;
}

RefPtr<FrameNode> MenuManager::GetMenuNode(int32_t targetId)
{
    auto it = menuMap_.find(targetId);
    if (it != menuMap_.end()) {
        return it->second;
    }
    return nullptr;
}

void MenuManager::HideMenu(
    const RefPtr<FrameNode>& menu, const RefPtr<OverlayManager>& overlayManager,
    int32_t targetId, bool isMenuOnTouch, const HideMenuType& reason)
{
    TAG_LOGI(AceLogTag::ACE_OVERLAY, "hide menu enter %{public}d", reason);
    CHECK_NULL_VOID(menu);
    auto wrapperPattern = menu->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(wrapperPattern);
    auto maskEnable = wrapperPattern->GetMenuMaskEnable();
    auto menuPreviewMode = wrapperPattern->GetPreviewMode();
    CHECK_NULL_VOID(overlayManager);
    PopMenuAnimation(menu, overlayManager);
    overlayManager->RemoveEventColumn();
    if (isMenuOnTouch) {
        overlayManager->RemovePixelMap();
        overlayManager->RemoveGatherNode();
    } else {
        overlayManager->RemovePixelMapAnimation(false, 0, 0);
        overlayManager->RemoveGatherNodeWithAnimation();
    }
    if (maskEnable || menuPreviewMode != MenuPreviewMode::NONE) {
        RemoveMenuFilter(menu);
    }
}

void MenuManager::HideAllMenus(const RefPtr<OverlayManager>& overlayManager)
{
    TAG_LOGI(AceLogTag::ACE_OVERLAY, "hide all menus enter");
    CHECK_NULL_VOID(overlayManager);
    auto container = Container::Current();
    if (container && container->IsSceneBoardWindow()) {
        auto windowScenes = overlayManager->GetwindowScenes();
        for (const auto& windowScene : windowScenes) {
            if (!windowScene.Upgrade()) {
                continue;
            }
            for (const auto& child : windowScene.Upgrade()->GetChildren()) {
                auto node = DynamicCast<FrameNode>(child);
                if (node && node->GetTag() == MENU_WRAPPER_ETS_TAG) {
                    TAG_LOGI(AceLogTag::ACE_OVERLAY, "will hide menu, menuNode id %{public}d", node->GetId());
                    PopMenuAnimation(node, overlayManager);
                }
            }
        }
        return;
    }

    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_VOID(rootNode);
    for (const auto& child : rootNode->GetChildren()) {
        auto node = DynamicCast<FrameNode>(child);
        if (node && node->GetTag() == MENU_WRAPPER_ETS_TAG) {
            auto wrapperPattern = node->GetPattern<MenuWrapperPattern>();
            CHECK_NULL_VOID(wrapperPattern);
            wrapperPattern->UpdateMenuAnimation(node);
            TAG_LOGI(AceLogTag::ACE_OVERLAY, "will hide menu, menuNode id %{public}d", node->GetId());
            PopMenuAnimation(node, overlayManager);
        }
    }
}

void MenuManager::DeleteMenu(int32_t targetId, const RefPtr<OverlayManager>& overlayManager)
{
    auto it = menuMap_.find(targetId);
    if (it == menuMap_.end()) {
        return;
    }
    TAG_LOGI(AceLogTag::ACE_OVERLAY, "delete menu enter");
    auto node = AceType::DynamicCast<FrameNode>(it->second);
    CHECK_NULL_VOID(node);
    CHECK_NULL_VOID(overlayManager);
    if (node->GetParent()) {
        auto id = Container::CurrentId();
        SubwindowManager::GetInstance()->ClearMenu();
        SubwindowManager::GetInstance()->ClearMenuNG(id, targetId);
        overlayManager->RemoveEventColumn();
        CallMenuDisappearOnlyNewLifeCycle(node);
        RemoveMenuNotInSubWindow(WeakClaim(RawPtr(node)), rootNodeWeak_, WeakClaim(AceType::RawPtr(overlayManager)));
    }
    EraseMenuInfo(targetId);
    SetIsMenuShow(false, nullptr);
    PublishMenuStatus(false, nullptr);
    overlayManager->ContentChangeReport(node, false);
}

void MenuManager::CleanMenuInSubWindowWithAnimation(const RefPtr<OverlayManager>& overlayManager)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "clean menu insubwindow with animation enter");
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_VOID(rootNode);
    RefPtr<FrameNode> menu;
    for (const auto& child : rootNode->GetChildren()) {
        auto node = DynamicCast<FrameNode>(child);
        if (node && node->GetTag() == MENU_WRAPPER_ETS_TAG) {
            menu = node;
            break;
        }
    }
    CHECK_NULL_VOID(menu);
    if (menu->GetTag() == MENU_WRAPPER_ETS_TAG) {
        auto wrapperPattern = menu->GetPattern<MenuWrapperPattern>();
        CHECK_NULL_VOID(wrapperPattern);
        wrapperPattern->UpdateMenuAnimation(menu);
    }
    CHECK_NULL_VOID(overlayManager);
    PopMenuAnimation(menu, overlayManager);
    RemoveMenuFilter(menu);
}

void MenuManager::CleanHoverImagePreviewInSubWindow(const RefPtr<FrameNode>& flexNode)
{
    CHECK_NULL_VOID(flexNode && flexNode->GetTag() == FLEX_ETS_TAG);
    for (const auto& child : flexNode->GetChildren()) {
        auto node = DynamicCast<FrameNode>(child);
        CHECK_NULL_VOID(node && node->GetTag() == STACK_ETS_TAG);

        auto previewNode = node->GetLastChild();
        if (previewNode && previewNode->GetTag() == MENU_PREVIEW_ETS_TAG) {
            node->RemoveChild(previewNode);
        }

        auto imageNode = node->GetFirstChild();
        if (imageNode && imageNode->GetTag() == IMAGE_ETS_TAG) {
            node->RemoveChild(imageNode);
        }

        flexNode->RemoveChild(node);
        flexNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        break;
    }
}

void MenuManager::CleanPreviewInSubWindow()
{
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_VOID(rootNode);
    for (const auto& child : rootNode->GetChildren()) {
        auto node = DynamicCast<FrameNode>(child);
        if (node && node->GetTag() == MENU_WRAPPER_ETS_TAG) {
            for (auto& childNode : node->GetChildren()) {
                auto frameNode = DynamicCast<FrameNode>(childNode);
                if (frameNode && (frameNode->GetTag() == FLEX_ETS_TAG ||
                    frameNode->GetTag() == MENU_PREVIEW_ETS_TAG || frameNode->GetTag() == IMAGE_ETS_TAG)) {
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

void MenuManager::CleanMenuInSubWindow(int32_t targetId)
{
    TAG_LOGI(AceLogTag::ACE_OVERLAY, "clean menu insubwindow enter");
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_VOID(rootNode);

    for (const auto& child : rootNode->GetChildren()) {
        auto node = DynamicCast<FrameNode>(child);
        CHECK_NULL_CONTINUE(node);
        if (node->GetTag() != MENU_WRAPPER_ETS_TAG) {
            continue;
        }

        auto menuWrapperPattern = node->GetPattern<MenuWrapperPattern>();
        CHECK_NULL_VOID(menuWrapperPattern);
        if (menuWrapperPattern->GetTargetId() != targetId) {
            continue;
        }

        for (auto& childNode : node->GetChildren()) {
            auto frameNode = DynamicCast<FrameNode>(childNode);
            if (frameNode && (frameNode->GetTag() == FLEX_ETS_TAG ||
                frameNode->GetTag() == MENU_PREVIEW_ETS_TAG || frameNode->GetTag() == IMAGE_ETS_TAG)) {
                CleanHoverImagePreviewInSubWindow(frameNode);
                node->RemoveChild(frameNode);
                break;
            }
        }
        CallMenuDisappearOnlyNewLifeCycle(node);
        rootNode->RemoveChild(node);
        rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        SetIsMenuShow(false, nullptr);
        PublishMenuStatus(false, nullptr);
        auto subwindowMgr = SubwindowManager::GetInstance();
        subwindowMgr->DeleteHotAreas(Container::CurrentId(), node->GetId(), SubwindowType::TYPE_MENU);
        RemoveMenuFilter(node, false);
        break;
    }
}

bool MenuManager::RemoveMenu(const RefPtr<FrameNode>& overlay)
{
    TAG_LOGI(AceLogTag::ACE_OVERLAY, "remove menu enter");
    CHECK_NULL_RETURN(overlay, false);
    auto menuWrapperPattern = overlay->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_RETURN(menuWrapperPattern, false);
    menuWrapperPattern->UpdateMenuAnimation(overlay);
    menuWrapperPattern->HideMenu(HideMenuType::REMOVE_MENU);
    return true;
}

void MenuManager::PublishMenuStatus(bool isMenuShow, const RefPtr<FrameNode>& menuNode)
{
    // notify drag manager the menu show status
    if (!menuNode) {
        DragDropGlobalController::GetInstance().PublishMenuStatusWithNode(isMenuShow);
        SelectableUtils::GetInstance().PublishMenuStatus(isMenuShow, menuNode);
        return;
    }
    auto menuWrapperPattern = menuNode->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(menuWrapperPattern);
    auto menu = menuWrapperPattern->GetMenu();
    CHECK_NULL_VOID(menu);
    auto menuPattern = menu->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    auto targetNode = FrameNode::GetFrameNode(menuPattern->GetTargetTag(), menuPattern->GetTargetId());
    CHECK_NULL_VOID(targetNode);
    DragDropGlobalController::GetInstance().PublishMenuStatusWithNode(isMenuShow, targetNode);
    SelectableUtils::GetInstance().PublishMenuStatus(isMenuShow, targetNode);
}

void MenuManager::SetIsMenuShow(bool isMenuShow, const RefPtr<FrameNode>& menuNode)
{
    isMenuShow_ = isMenuShow;
}

void MenuManager::RemoveMenuFilter(const RefPtr<FrameNode>& menuWrapper, bool hasAnimation)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "remove filter enter, hasAnimation: %{public}d", hasAnimation);
    CHECK_NULL_VOID(menuWrapper);
    auto warpperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(warpperPattern);
    auto filterNode = warpperPattern->GetFilterColumnNode();
    CHECK_NULL_VOID(filterNode);
    auto pipeline = filterNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    auto overlayManager = pipeline->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);

    if (!hasAnimation) {
        overlayManager->RemoveFilterWithNode(filterNode);
        return;
    }

    if (overlayManager->IsFilterOnDisappear(filterNode->GetId())) {
        TAG_LOGI(AceLogTag::ACE_OVERLAY, "filter is already disappearing, filterId: %{public}d", filterNode->GetId());
        return;
    }
    overlayManager->ShowFilterDisappearAnimation(filterNode);
}

RefPtr<FrameNode> MenuManager::BuildAIEntityMenu(
    const std::vector<std::pair<std::string, std::function<void()>>>& menuOptions)
{
    TAG_LOGI(AceLogTag::ACE_OVERLAY, "build AI entity menu enter");
    auto menuNode = FrameNode::CreateFrameNode(MENU_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<InnerMenuPattern>(-1, MENU_ETS_TAG, MenuType::MULTI_MENU));
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

RefPtr<FrameNode> MenuManager::CreateAIEntityMenu(
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

bool MenuManager::ShowAIEntityMenu(const std::vector<std::pair<std::string, std::function<void()>>>& menuOptions,
    const RectF& aiRect, const RefPtr<FrameNode>& targetNode, const RefPtr<OverlayManager>& overlayManager)
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
    CHECK_NULL_RETURN(overlayManager, false);
    wrapperPattern->RegisterMenuAppearCallback([menuManagerWeak = WeakClaim(this),
        overlayManagerWeak = AceType::WeakClaim(AceType::RawPtr(overlayManager)),
        safeAreaWK = WeakClaim(RawPtr(safeAreaManager)), targetId, containerId = Container::CurrentId()]() {
            ContainerScope scope(containerId);
            auto safeAreaManager = safeAreaWK.Upgrade();
            CHECK_NULL_VOID(safeAreaManager);
            safeAreaManager->AddKeyboardChangeCallbackConsideringUIExt(targetId, [menuManagerWeak,
                    overlayManagerWeak, targetId, containerId]() {
                    ContainerScope scope(containerId);
                    auto menuManager = menuManagerWeak.Upgrade();
                    CHECK_NULL_VOID(menuManager);
                    auto overlayManager = overlayManagerWeak.Upgrade();
                    CHECK_NULL_VOID(overlayManager);
                    menuManager->CloseAIEntityMenu(overlayManager, targetId);
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
        menuLayoutProperty->UpdateShowInSubWindow(false);
        ShowMenu(overlayManager, targetNode->GetId(), aiRect.GetOffset(), menuWrapperNode);
    }
    return true;
}

void MenuManager::CloseAIEntityMenu(const RefPtr<OverlayManager>& overlayManager, int32_t targetId)
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
        CHECK_NULL_VOID(overlayManager);
        HideMenu(menuNode, overlayManager, targetId, false, HideMenuType::CLOSE_AI_MENU);
    }
}

void MenuManager::RemoveMenuBadgeNode(const RefPtr<FrameNode>& menuWrapperNode)
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

void MenuManager::ShowFilterAnimation(const RefPtr<FrameNode>& columnNode,
    const RefPtr<FrameNode>& menuWrapperNode, const RefPtr<OverlayManager>& overlayManager)
{
    CHECK_NULL_VOID(columnNode);
    CHECK_NULL_VOID(menuWrapperNode);
    auto menuWrapperPattern = menuWrapperNode->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(menuWrapperPattern);
    auto pipelineContext = menuWrapperNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto menuTheme = pipelineContext->GetTheme<NG::MenuTheme>();
    CHECK_NULL_VOID(menuTheme);
    auto hoverDelay = menuWrapperPattern->GetHoverScaleInterruption();
    auto delay = hoverDelay ? menuTheme->GetHoverImageDelayDuration(true) : 0;
    CHECK_NULL_VOID(overlayManager);
    auto& previewFilterTask = overlayManager->GetPreviewFilterTask();
    if (delay > 0) {
        previewFilterTask.Reset([menuManagerWeak = WeakClaim(this),
                                     overlayManagerWeak = AceType::WeakClaim(AceType::RawPtr(overlayManager)),
                                     columnWeak = WeakClaim(RawPtr(columnNode)),
                                     wrapperWeak = WeakClaim(RawPtr(menuWrapperNode))]() {
            auto columnNode = columnWeak.Upgrade();
            auto menuWrapperNode = wrapperWeak.Upgrade();
            auto menuManager = menuManagerWeak.Upgrade();
            CHECK_NULL_VOID(menuManager);
            auto overlayManager = overlayManagerWeak.Upgrade();
            CHECK_NULL_VOID(overlayManager);
            menuManager->ExecuteFilterAnimation(columnNode, menuWrapperNode, overlayManager);
        });
        auto taskExecutor = pipelineContext->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        taskExecutor->PostDelayedTask(
            previewFilterTask, TaskExecutor::TaskType::UI, delay, "ArkUIShowFilterDelayTask");
    } else {
        ExecuteFilterAnimation(columnNode, menuWrapperNode, overlayManager);
    }
}

void MenuManager::ExecuteFilterAnimation(
    const RefPtr<FrameNode>& columnNode, const RefPtr<FrameNode>& menuWrapperNode,
    const RefPtr<OverlayManager>& overlayManager)
{
    CHECK_NULL_VOID(columnNode);

    auto filterRenderContext = columnNode->GetRenderContext();
    CHECK_NULL_VOID(filterRenderContext);

    CHECK_NULL_VOID(menuWrapperNode);
    auto pipelineContext = menuWrapperNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto menuTheme = pipelineContext->GetTheme<NG::MenuTheme>();
    CHECK_NULL_VOID(menuTheme);
    auto menuWrapperPattern = menuWrapperNode->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(menuWrapperPattern);
    auto maskEnable = menuWrapperPattern->GetMenuMaskEnable();
    auto maskColor = maskEnable ? menuWrapperPattern->GetMenuMaskColor() : menuTheme->GetPreviewMenuMaskColor();
    BlurStyleOption styleOption;
    styleOption.blurStyle = maskEnable ? menuWrapperPattern->GetMenuMaskBlurStyle() : BlurStyle::BACKGROUND_THIN;
    styleOption.colorMode = ThemeColorMode::SYSTEM;

    AnimationOption option;
    option.SetDuration(menuTheme->GetFilterAnimationDuration());
    option.SetCurve(Curves::SHARP);
    option.SetOnFinishEvent([overlayManagerWeak = AceType::WeakClaim(AceType::RawPtr(overlayManager)),
        filterId = columnNode->GetId()] {
        TAG_LOGI(AceLogTag::ACE_OVERLAY, "show filter animation finish");
        auto overlayManager = overlayManagerWeak.Upgrade();
        CHECK_NULL_VOID(overlayManager);
        overlayManager->SetFilterActive(false);
    });
    filterRenderContext->UpdateBackBlurRadius(Dimension(0.0f));
    if (maskEnable || !menuTheme->GetHasBackBlur()) {
        filterRenderContext->UpdateBackgroundColor(maskColor.ChangeOpacity(0.0f));
    }
    TAG_LOGI(AceLogTag::ACE_OVERLAY, "start show filter animation");
    AnimationUtils::Animate(
        option,
        [filterRenderContext, styleOption, maskColor, menuTheme, maskEnable]() {
            CHECK_NULL_VOID(filterRenderContext);
            if (maskEnable) {
                filterRenderContext->UpdateBackBlurStyle(styleOption);
                filterRenderContext->UpdateBackgroundColor(maskColor);
            } else if (menuTheme->GetHasBackBlur()) {
                filterRenderContext->UpdateBackBlurStyle(styleOption);
            } else {
                filterRenderContext->UpdateBackgroundColor(maskColor);
            }
        },
        option.GetOnFinishEvent(), nullptr, columnNode->GetContextRefPtr());
}

bool MenuManager::RemoveMenuInSubWindow(const RefPtr<FrameNode>& menuWrapper,
    const RefPtr<OverlayManager>& overlayManager)
{
    CHECK_NULL_RETURN(menuWrapper, false);
    auto wrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_RETURN(wrapperPattern, false);
    auto onHoverImageDisappear = wrapperPattern->GetIsShowHoverImage() &&
                                 (wrapperPattern->GetOnMenuDisappear() || wrapperPattern->GetOnPreviewDisappear());
    if (onHoverImageDisappear) {
        return false;
    }

    auto pipeline = menuWrapper->GetContextRefPtr();
    auto instanceId = pipeline ? pipeline->GetInstanceId() : Container::CurrentId();
    SubwindowManager::GetInstance()->ClearMenuNG(instanceId, wrapperPattern->GetTargetId());
    CHECK_NULL_RETURN(overlayManager, false);
    overlayManager->ResetContextMenuDragHideFinished();
    return true;
}

void MenuManager::RemoveMenuNotInSubWindow(
    const WeakPtr<FrameNode>& menuWK, const WeakPtr<UINode>& rootWeak, const WeakPtr<OverlayManager>& overlayWeak)
{
    auto menu = menuWK.Upgrade();
    CHECK_NULL_VOID(menu);
    auto rootNode = rootWeak.Upgrade();
    CHECK_NULL_VOID(rootNode);
    auto overlayManager = overlayWeak.Upgrade();
    CHECK_NULL_VOID(overlayManager);

    auto container = Container::Current();
    if (container && container->IsSceneBoardWindow()) {
        rootNode = overlayManager->FindWindowScene(menu);
    }
    CHECK_NULL_VOID(rootNode);
    auto menuWrapperPattern = menu->GetPattern<MenuWrapperPattern>();
    if (menuWrapperPattern && menuWrapperPattern->GetIsSelectOverlaySubWindowWrapper()) {
        SubwindowManager::GetInstance()->DeleteSelectOverlayHotAreas(
            menuWrapperPattern->GetContainerId(), menu->GetId());
    }
    overlayManager->RemoveChildWithService(rootNode, menu);
    rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void MenuManager::RemoveMenuWrapperNode(const RefPtr<UINode>& rootNode, const RefPtr<PipelineContext>& pipeline)
{
    CHECK_NULL_VOID(rootNode);
    CHECK_NULL_VOID(pipeline);
    std::vector<int32_t> idsNeedClean;
    bool needCallOldLifeCycle = OverlayManager::IsSceneBoardWindow();
    auto children = rootNode->GetChildren();
    for (const auto& child : children) {
        auto node = DynamicCast<FrameNode>(child);
        if (!node || node->GetTag() != MENU_WRAPPER_ETS_TAG) {
            continue;
        }
        idsNeedClean.push_back(child->GetId());
        if (needCallOldLifeCycle) {
            CallMenuDisappearWithStatus(node);
        } else {
            CallMenuDisappearOnlyNewLifeCycle(node);
        }
        EraseMenuInfoFromWrapper(node);
        rootNode->RemoveChild(node);
    }
    CHECK_EQUAL_VOID(idsNeedClean.empty(), true);
    pipeline->AddAfterLayoutTask([idsNeedClean, containerId = pipeline->GetInstanceId()] {
        auto subwindowMgr = SubwindowManager::GetInstance();
        for (auto child : idsNeedClean) {
            subwindowMgr->DeleteHotAreas(containerId, child, SubwindowType::TYPE_MENU);
        }
    });
}

void MenuManager::CallMenuDisappearOnlyNewLifeCycle(const RefPtr<FrameNode>& menuWrapperNode)
{
    CHECK_NULL_VOID(menuWrapperNode);
    auto menuWrapperPattern = menuWrapperNode->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(menuWrapperPattern);
    if (menuWrapperPattern->GetMenuStatus() == MenuStatus::ON_HIDE_ANIMATION) {
        // When the menu is forcibly removed during the disappearing process, the onDidDisappear life cycle needs to be
        // called back to the user.
        menuWrapperPattern->CallMenuOnDidDisappearCallback();
    } else if (menuWrapperPattern->IsShow()) {
        // When the menu is forcibly removed during display, the life cycle of onWillDisappear and
        // onDidDisappear needs to be called back to the user.
        menuWrapperPattern->CallMenuOnWillDisappearCallback();
        menuWrapperPattern->CallMenuOnDidDisappearCallback();
    }
    menuWrapperPattern->SetMenuStatus(MenuStatus::HIDE);
}

void MenuManager::CallMenuDisappearWithStatus(const RefPtr<FrameNode>& menuWrapperNode)
{
    CHECK_NULL_VOID(menuWrapperNode);
    auto menuWrapperPattern = menuWrapperNode->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(menuWrapperPattern);

    if (menuWrapperPattern->GetMenuStatus() == MenuStatus::ON_HIDE_ANIMATION) {
        // When the menu is forcibly removed during the disappearing process, the onDisappear life cycle needs to be
        // called back to the user.
        menuWrapperPattern->CallMenuDisappearCallback();
        menuWrapperPattern->CallMenuOnDidDisappearCallback();
    } else if (menuWrapperPattern->IsShow()) {
        // When the menu is forcibly removed during display, the life cycle of aboutToDisappear and
        // onDisappear needs to be called back to the user.
        menuWrapperPattern->CallMenuAboutToDisappearCallback();
        menuWrapperPattern->CallMenuOnWillDisappearCallback();
        menuWrapperPattern->CallMenuDisappearCallback();
        menuWrapperPattern->CallMenuOnDidDisappearCallback();
    }
    menuWrapperPattern->SetMenuStatus(MenuStatus::HIDE);
}

void MenuManager::SkipMenuShow(int32_t targetId)
{
    skipTargetIds_.insert(targetId);
}

void MenuManager::ResumeMenuShow(int32_t targetId)
{
    skipTargetIds_.erase(targetId);
}

bool MenuManager::CheckSkipMenuShow(int32_t targetId)
{
    return skipTargetIds_.find(targetId) != skipTargetIds_.end();
}

RefPtr<PipelineContext> MenuManager::GetPipelineContext() const
{
    auto context = context_.Upgrade();
    CHECK_NULL_RETURN(context, PipelineContext::GetCurrentContextSafelyWithCheck());
    return context;
}

void MenuManager::EraseMenuInfoFromWrapper(const RefPtr<FrameNode>& menuWrapperNode)
{
    CHECK_NULL_VOID(menuWrapperNode);
    auto pattern = menuWrapperNode->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(pattern);
    auto targetId = pattern->GetTargetId();
    auto currentMenuWrapper = menuMap_[targetId];
    CHECK_NULL_VOID(currentMenuWrapper);
    // When a menu is displayed for multiple times, if a menu is squeezed out, it is necessary to check whether the menu
    // is the current recorded menu
    if (currentMenuWrapper->GetId() == menuWrapperNode->GetId()) {
        EraseMenuInfo(targetId);
    }
}
} // namespace OHOS::Ace::NG
