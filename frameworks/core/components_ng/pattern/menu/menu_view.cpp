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

#include "core/components_ng/pattern/menu/menu_view.h"

#include "base/geometry/dimension.h"
#include "base/i18n/localization.h"
#include "base/memory/ace_type.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/manager/drag_drop/drag_drop_func_wrapper.h"
#include "core/components_ng/manager/drag_drop/utils/drag_animation_helper.h"
#include "core/components_ng/pattern/flex/flex_layout_pattern.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_row_pattern.h"
#include "core/components_ng/pattern/menu/menu_layout_property.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/menu/menu_theme.h"
#include "core/components_ng/pattern/menu/preview/menu_preview_pattern.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components_ng/pattern/security_component/paste_button/paste_button_common.h"
#include "core/components_ng/pattern/security_component/paste_button/paste_button_model_ng.h"
#include "core/components_ng/pattern/security_component/security_component_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/components/text_overlay/text_overlay_theme.h"
#include "core/components_ng/manager/drag_drop/drag_drop_global_controller.h"

namespace OHOS::Ace::NG {

/**
 * The structure of menu is designed as follows :
 * |--menuWrapper(size is same as root)
 *   |--menu
 *      |--scroll
 *          |--column(for bindMenu/select)
 *            |--options
 *          |--customNode(for custom builder)
 */

namespace {
constexpr float PAN_MAX_VELOCITY = 2000.0f;
constexpr float HALF_DIVIDE = 2.0f;
constexpr float PREVIEW_ORIGIN_SCALE = 1.0f;
const RefPtr<Curve> CUSTOM_PREVIEW_ANIMATION_CURVE =
    AceType::MakeRefPtr<InterpolatingSpring>(0.0f, 1.0f, 380.0f, 34.0f);
const std::string HOVER_IMAGE_CLIP_PROPERTY_NAME = "hoverImageClip";

void MountTextNode(const RefPtr<FrameNode>& wrapperNode, const RefPtr<UINode>& previewCustomNode = nullptr)
{
    CHECK_NULL_VOID(previewCustomNode);
    auto pipeline = PipelineContext::GetMainPipelineContext();
    CHECK_NULL_VOID(pipeline);
    auto manager = pipeline->GetOverlayManager();
    CHECK_NULL_VOID(manager);
    auto gatherNode = manager->GetGatherNode();
    CHECK_NULL_VOID(gatherNode);
    auto textNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    CHECK_NULL_VOID(textNode);
    textNode->MountToParent(wrapperNode);
    textNode->MarkModifyDone();
}

LayoutConstraintF CreatePreviewLayoutConstraint(const RefPtr<LayoutProperty>& layoutProperty)
{
    CHECK_NULL_RETURN(layoutProperty, {});
    LayoutConstraintF constraint = layoutProperty->GetLayoutConstraint().value_or(LayoutConstraintF());

    auto currentId = Container::CurrentId();
    auto parentContainerId =
        currentId >= MIN_SUBCONTAINER_ID ? SubwindowManager::GetInstance()->GetParentContainerId(currentId) : currentId;
    auto subWindow = SubwindowManager::GetInstance()->GetSubwindow(parentContainerId);
    CHECK_NULL_RETURN(subWindow, constraint);
    auto subwindowSize = subWindow->GetRect().GetSize();
    if (!subwindowSize.IsPositive()) {
        return constraint;
    }

    if (subwindowSize != constraint.maxSize || subwindowSize != constraint.percentReference) {
        constraint.maxSize.SetSizeT(subwindowSize);
        constraint.percentReference.SetSizeT(subwindowSize);
    }
    return constraint;
}

void CustomPreviewNodeProc(const RefPtr<FrameNode>& previewNode, const MenuParam& menuParam,
    const RefPtr<UINode>& previewCustomNode = nullptr)
{
    CHECK_NULL_VOID(previewCustomNode);
    CHECK_NULL_VOID(previewNode);
    auto previewPattern = previewNode->GetPattern<MenuPreviewPattern>();
    CHECK_NULL_VOID(previewPattern);
    previewPattern->SetHasPreviewTransitionEffect(menuParam.hasPreviewTransitionEffect);
    auto layoutProperty = previewNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateVisibility(VisibleType::VISIBLE, true);
    previewNode->AddChild(previewCustomNode);

    CHECK_NULL_VOID(menuParam.isShowHoverImage);
    auto pipeline = previewNode->GetContextWithCheck();
    CHECK_NULL_VOID(pipeline);
    ScopedLayout scope(pipeline);
    auto layoutConstraint = CreatePreviewLayoutConstraint(layoutProperty);
    previewNode->Measure(layoutConstraint);
    auto previewSize = previewNode->GetGeometryNode()->GetFrameSize();
    previewPattern->SetIsShowHoverImage(true);
    previewPattern->SetCustomPreviewWidth(previewSize.Width());
    previewPattern->SetCustomPreviewHeight(previewSize.Height());

    auto previewScaleTo = menuParam.previewAnimationOptions.scaleTo;
    CHECK_NULL_VOID(previewScaleTo);
    auto menuTheme = pipeline->GetTheme<NG::MenuTheme>();
    CHECK_NULL_VOID(menuTheme);
    previewScaleTo = LessOrEqual(previewScaleTo, 0.0) ? menuTheme->GetPreviewAfterAnimationScale() : previewScaleTo;
    previewPattern->SetCustomPreviewScaleTo(previewScaleTo);
}

// create menuWrapper and menu node, update menu props
std::pair<RefPtr<FrameNode>, RefPtr<FrameNode>> CreateMenu(int32_t targetId, const std::string& targetTag = "",
    MenuType type = MenuType::MENU)
{
    // use wrapper to detect click events outside menu
    auto wrapperNode = FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MenuWrapperPattern>(targetId));

    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto menuNode = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, nodeId, AceType::MakeRefPtr<MenuPattern>(targetId, targetTag, type));

    auto renderContext = menuNode->GetRenderContext();
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN) && renderContext->IsUniRenderEnabled()) {
        BlurStyleOption styleOption;
        auto pipeLineContext = menuNode->GetContextWithCheck();
        if (!pipeLineContext) {
            return { wrapperNode, menuNode };
        }
        auto selectTheme = pipeLineContext->GetTheme<SelectTheme>();
        if (!selectTheme) {
            return { wrapperNode, menuNode };
        }
        if (selectTheme->GetMenuBlendBgColor()) {
            styleOption.blurStyle = static_cast<BlurStyle>(selectTheme->GetMenuNormalBackgroundBlurStyle());
            renderContext->UpdateBackgroundColor(selectTheme->GetBackgroundColor());
        } else {
            styleOption.blurStyle = static_cast<BlurStyle>(selectTheme->GetMenuBackgroundBlurStyle());
            renderContext->UpdateBackgroundColor(Color::TRANSPARENT);
        }
        renderContext->UpdateBackBlurStyle(styleOption);
    }

    menuNode->MountToParent(wrapperNode);

    return { wrapperNode, menuNode };
}

void CreateTitleNode(const std::string& title, RefPtr<FrameNode>& column)
{
    auto textNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_VOID(textNode);
    auto textProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textProperty);

    auto pipeline = textNode->GetContextWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    auto padding = static_cast<float>(theme->GetMenuItemHorIntervalPadding().ConvertToPx());
    PaddingProperty textPadding;
    textPadding.left = CalcLength(padding);
    textPadding.right = CalcLength(padding);
    textProperty->UpdatePadding(textPadding);
    textProperty->UpdateFontSize(theme->GetMenuTitleFontSize());
    textProperty->UpdateFontWeight(FontWeight::MEDIUM);
    textProperty->UpdateItalicFontStyle(Ace::FontStyle::NORMAL);
    textProperty->UpdateTextColor(theme->GetMenuTitleFontColor());
    textProperty->UpdateContent(title);
    textProperty->UpdateMaxLines(1);
    textProperty->UpdateTextOverflow(TextOverflow::ELLIPSIS);

    CalcSize idealSize;
    idealSize.SetHeight(CalcLength(theme->GetMenuTitleHeight()));
    MeasureProperty layoutConstraint;
    layoutConstraint.selfIdealSize = idealSize;
    textProperty->UpdateCalcLayoutProperty(layoutConstraint);

    textNode->MountToParent(column);
    textNode->MarkModifyDone();
}

RefPtr<FrameNode> CreateMenuScroll(const RefPtr<UINode>& node)
{
    auto scroll = FrameNode::CreateFrameNode(
        V2::SCROLL_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ScrollPattern>());
    CHECK_NULL_RETURN(scroll, nullptr);
    auto props = scroll->GetLayoutProperty<ScrollLayoutProperty>();
    props->UpdateAxis(Axis::VERTICAL);
    props->UpdateAlignment(Alignment::CENTER_LEFT);
    auto pipeline = scroll->GetContextWithCheck();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto theme = pipeline->GetTheme<SelectTheme>();
    float contentPadding = 0.0f;
    if (theme) {
        contentPadding = static_cast<float>(theme->GetMenuPadding().ConvertToPx());
    }
    PaddingProperty padding;
    padding.left = padding.right = padding.top = padding.bottom = CalcLength(contentPadding);
    props->UpdatePadding(padding);
    if (node) {
        node->MountToParent(scroll);
    }
    auto renderContext = scroll->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, nullptr);
    BorderRadiusProperty borderRadius;
    if (theme) {
        auto defaultRadius = Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE) ?
            theme->GetMenuDefaultRadius() : theme->GetMenuBorderRadius();
        borderRadius.SetRadius(defaultRadius);
    }
    renderContext->UpdateBorderRadius(borderRadius);
    return scroll;
}

void MountScrollToMenu(
    const RefPtr<UINode>& customNode, RefPtr<FrameNode> scroll, MenuType type, RefPtr<FrameNode> menuNode)
{
    auto customMenuNode = AceType::DynamicCast<FrameNode>(customNode);
    if (customMenuNode) {
        customMenuNode->SetDraggable(false);
    }
    scroll->MountToParent(menuNode);
    scroll->MarkModifyDone();
}

void OptionKeepMenu(RefPtr<FrameNode>& option, WeakPtr<FrameNode>& menuWeak)
{
    auto pattern = option->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetMenu(menuWeak);
}

bool GetHasIcon(const std::vector<OptionParam>& params)
{
    for (size_t i = 0; i < params.size(); ++i) {
        if (!params[i].icon.empty() || params[i].isPasteOption) {
            return true;
        }
    }
    return false;
}

bool GetHasSymbol(const std::vector<OptionParam>& params)
{
    for (size_t i = 0; i < params.size(); ++i) {
        if (params[i].symbol != nullptr) {
            return true;
        }
    }
    return false;
}

OffsetF GetFloatImageOffset(const RefPtr<FrameNode>& frameNode)
{
    auto offsetToWindow = frameNode->GetPaintRectOffset(false, true);
    auto offsetX = offsetToWindow.GetX();
    auto offsetY = offsetToWindow.GetY();
    return OffsetF(offsetX, offsetY);
}

void UpdateContainerIdealSizeConstraint(const RefPtr<FrameNode>& node, const CalcSize& idealSize)
{
    CHECK_NULL_VOID(node);
    MeasureProperty layoutConstraint;
    layoutConstraint.selfIdealSize = idealSize;
    auto nodeLayoutProperty = node->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_VOID(nodeLayoutProperty);
    nodeLayoutProperty->UpdateCalcLayoutProperty(layoutConstraint);
}

void ShowBorderRadiusAndShadowAnimation(
    const RefPtr<MenuTheme>& menuTheme, const RefPtr<FrameNode>& imageNode, bool isShowHoverImage)
{
    CHECK_NULL_VOID(imageNode);
    auto imageContext = imageNode->GetRenderContext();
    CHECK_NULL_VOID(imageContext);
    auto shadow = imageContext->GetBackShadow();
    if (!shadow.has_value()) {
        shadow = Shadow::CreateShadow(ShadowStyle::None);
    }
    AnimationOption option;
    option.SetDuration(menuTheme->GetPreviewAnimationDuration());
    option.SetCurve(Curves::SHARP);
    auto previewBorderRadius = BorderRadiusProperty(menuTheme->GetPreviewBorderRadius());
    if (auto presetRad = imageContext->GetBorderRadius(); presetRad) {
        previewBorderRadius = presetRad.value();
        imageContext->ResetBorderRadius();
    }

    imageContext->UpdateBorderRadius(imageContext->GetBorderRadius().value_or(BorderRadiusProperty()));
    auto pipelineContext = imageNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->AddAfterLayoutTask([option, imageContext, previewBorderRadius, shadow, isShowHoverImage]() {
        AnimationUtils::Animate(
            option,
            [imageContext, previewBorderRadius, shadow, isShowHoverImage]() mutable {
                CHECK_NULL_VOID(imageContext && shadow);
                auto color = shadow->GetColor();
                auto newColor = Color::FromARGB(100, color.GetRed(), color.GetGreen(), color.GetBlue());
                shadow->SetColor(newColor);
                imageContext->UpdateBackShadow(shadow.value());

                CHECK_NULL_VOID(!isShowHoverImage);
                imageContext->UpdateBorderRadius(previewBorderRadius);
            },
            option.GetOnFinishEvent());
    });
}

void UpdateOpacityInFinishEvent(const RefPtr<FrameNode>& previewNode, const RefPtr<RenderContext>& imageContext,
    const RefPtr<MenuTheme>& menuTheme, bool isScaleNearEqual = true)
{
    CHECK_NULL_VOID(imageContext && menuTheme);
    // hover image disappear opacity animation
    AnimationOption option;
    if (isScaleNearEqual) {
        option.SetDuration(menuTheme->GetPreviewAnimationDuration());
        option.SetCurve(Curves::SHARP);
        option.SetDelay(menuTheme->GetHoverImageDelayDuration());
    } else {
        option.SetDuration(menuTheme->GetHoverImageSwitchToPreviewOpacityDuration());
        option.SetCurve(Curves::FRICTION);
    }

    CHECK_NULL_VOID(previewNode);
    auto previewContext = previewNode->GetRenderContext();
    CHECK_NULL_VOID(previewContext);
    
    imageContext->UpdateOpacity(1.0);
    previewContext->UpdateOpacity(0.0);
    AnimationUtils::Animate(
        option, [previewContext]() {
            CHECK_NULL_VOID(previewContext);
            previewContext->UpdateOpacity(1.0);
        });
}

void UpdatePreviewVisibleAreaByFrame(const RefPtr<RenderContext>& clipContext,
    const RefPtr<MenuPreviewPattern>& previewPattern, float radius, float rate)
{
    CHECK_NULL_VOID(previewPattern && clipContext);
    // clip area start by actual image size after contain stack container and squeezed by parent proc
    auto clipStartWidth = previewPattern->GetHoverImageAfterScaleWidth();
    auto clipStartHeight = previewPattern->GetHoverImageAfterScaleHeight();
    // child stack node may be squeezed by parent flex node
    auto clipEndWidth = previewPattern->GetStackAfterScaleActualWidth();
    auto clipEndHeight = previewPattern->GetStackAfterScaleActualHeight();

    auto curentClipAreaWidth = rate * (clipEndWidth - clipStartWidth) + clipStartWidth;
    auto curentClipAreaHeight = rate * (clipEndHeight - clipStartHeight) + clipStartHeight;

    auto clipOffset = previewPattern->GetHoverImageAfterScaleOffset();
    RoundRect roundRectInstance;
    roundRectInstance.SetRect(RectF(OffsetF((1 - rate) * clipOffset.GetX(), (1 - rate) * clipOffset.GetY()),
        SizeF(curentClipAreaWidth, curentClipAreaHeight)));
    roundRectInstance.SetCornerRadius(rate * radius);
    clipContext->ClipWithRoundRect(roundRectInstance);
}

void UpdateHoverImagePreviewScale(const RefPtr<FrameNode>& hoverImageStackNode,
    const RefPtr<MenuPreviewPattern>& previewPattern, const RefPtr<MenuTheme>& menuTheme, bool isScaleNearEqual)
{
    CHECK_NULL_VOID(hoverImageStackNode && previewPattern && menuTheme);
    auto stackContext = hoverImageStackNode->GetRenderContext();
    CHECK_NULL_VOID(stackContext);

    auto scaleBefore = previewPattern->GetHoverImageScaleTo();
    auto scaleFrom =
        LessOrEqual(scaleBefore, 0.0) ? menuTheme->GetPreviewBeforeAnimationScale() : scaleBefore;
    stackContext->UpdateTransformScale(VectorF(scaleFrom, scaleFrom));

    auto scaleAfter = previewPattern->GetCustomPreviewScaleTo();
    auto scaleTo =
        LessOrEqual(scaleAfter, 0.0) ? menuTheme->GetPreviewAfterAnimationScale() : scaleAfter;
    
    AnimationOption scaleOption = AnimationOption();
    scaleOption.SetCurve(CUSTOM_PREVIEW_ANIMATION_CURVE);
    if (isScaleNearEqual) {
        scaleOption.SetDelay(menuTheme->GetHoverImageDelayDuration());
    }
    previewPattern->SetIsHoverImageScalePlaying(true);
    scaleOption.SetOnFinishEvent([weak = WeakPtr<MenuPreviewPattern>(previewPattern)] {
        auto previewPattern = weak.Upgrade();
        CHECK_NULL_VOID(previewPattern);
        previewPattern->SetIsHoverImageScalePlaying(false);
    });

    auto menuWrapper = previewPattern->GetMenuWrapper();
    CHECK_NULL_VOID(menuWrapper);
    auto menuWrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(menuWrapperPattern);
    auto radius = menuTheme->GetPreviewBorderRadius().ConvertToPx();
    auto callback = [menuWrapperPattern, previewPattern, stackContext, scaleFrom, scaleTo, radius](float rate) {
        CHECK_NULL_VOID(menuWrapperPattern && !menuWrapperPattern->IsHide());
        menuWrapperPattern->SetAnimationPreviewScale(rate * (scaleTo - scaleFrom) + scaleFrom);
        menuWrapperPattern->SetAnimationClipRate(rate);
        menuWrapperPattern->SetAnimationBorderRadius(rate * radius);
        UpdatePreviewVisibleAreaByFrame(stackContext, previewPattern, radius, rate);
    };

    auto animateProperty = AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(-1.0, std::move(callback));
    CHECK_NULL_VOID(animateProperty);
    stackContext->AttachNodeAnimatableProperty(animateProperty);
    animateProperty->Set(0.0);
    AnimationUtils::Animate(
        scaleOption,
        [stackContext, scaleTo, animateProperty]() {
            CHECK_NULL_VOID(stackContext);
            stackContext->UpdateTransformScale(VectorF(scaleTo, scaleTo));
            CHECK_NULL_VOID(animateProperty);
            animateProperty->Set(1.0);
        },
        scaleOption.GetOnFinishEvent());
}

void SetHoverImageFinishEvent(const RefPtr<FrameNode>& hoverImageStackNode, const RefPtr<FrameNode>& previewNode,
    const RefPtr<RenderContext>& imageContext, const RefPtr<MenuTheme>& menuTheme,
    const RefPtr<MenuWrapperPattern>& wrapperPattern)
{
    CHECK_NULL_VOID(previewNode);
    auto previewPattern = previewNode->GetPattern<MenuPreviewPattern>();
    CHECK_NULL_VOID(previewPattern);
    previewPattern->SetIsHoverImageAnimationPlaying(false);

    CHECK_NULL_VOID(wrapperPattern);
    // if the animation is interrupted during the image hover phase, the next dynamic effects are not processed.
    CHECK_NULL_VOID(!wrapperPattern->IsStopHoverImageAnimation());

    bool isScaleNearEqual = previewPattern->IsHoverImageScaleNearEqual();

    UpdateOpacityInFinishEvent(previewNode, imageContext, menuTheme, isScaleNearEqual);

    UpdateHoverImagePreviewScale(hoverImageStackNode, previewPattern, menuTheme, isScaleNearEqual);
}

void ShowHoverImageAnimationProc(const RefPtr<FrameNode>& hoverImageStackNode, const RefPtr<FrameNode>& previewNode,
    const RefPtr<RenderContext>& imageContext, const RefPtr<MenuWrapperPattern>& wrapperPattern)
{
    CHECK_NULL_VOID(wrapperPattern && wrapperPattern->GetIsShowHoverImage());
    CHECK_NULL_VOID(hoverImageStackNode && previewNode);
    auto stackContext = hoverImageStackNode->GetRenderContext();
    CHECK_NULL_VOID(stackContext);
    stackContext->UpdateClipEdge(true);
    auto previewPattern = previewNode->GetPattern<MenuPreviewPattern>();
    CHECK_NULL_VOID(previewPattern);
    auto pipeline = previewNode->GetContextWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto menuTheme = pipeline->GetTheme<NG::MenuTheme>();
    CHECK_NULL_VOID(menuTheme);

    DragEventActuator::ExecutePreDragAction(PreDragStatus::PREVIEW_LIFT_STARTED);
    auto scaleBefore = previewPattern->GetHoverImageScaleFrom();
    auto scaleFrom =
        LessOrEqual(scaleBefore, 0.0) ? menuTheme->GetPreviewBeforeAnimationScale() : scaleBefore;
    stackContext->UpdateTransformScale(VectorF(scaleFrom, scaleFrom));

    auto scaleAfter = previewPattern->GetHoverImageScaleTo();
    auto scaleTo =
        LessOrEqual(scaleAfter, 0.0) ? menuTheme->GetPreviewAfterAnimationScale() : scaleAfter;
    
    previewPattern->SetIsHoverImageAnimationPlaying(true);
    // when the scaling start and end sizes are the same, the end callback method should not be relied on
    AnimationOption scaleOption = AnimationOption();
    if (previewPattern->IsHoverImageScaleNearEqual()) {
        SetHoverImageFinishEvent(hoverImageStackNode, previewNode, imageContext, menuTheme, wrapperPattern);
        DragEventActuator::ExecutePreDragAction(PreDragStatus::PREVIEW_LIFT_FINISHED);
        return;
    } else {
        scaleOption.SetOnFinishEvent(
            [hoverImageStackNode, previewNode, imageContext, menuTheme, wrapperPattern]() {
                DragEventActuator::ExecutePreDragAction(PreDragStatus::PREVIEW_LIFT_FINISHED);
                SetHoverImageFinishEvent(hoverImageStackNode, previewNode, imageContext, menuTheme, wrapperPattern);
            });
    }
    scaleOption.SetDuration(menuTheme->GetHoverImageDelayDuration());
    scaleOption.SetCurve(Curves::SHARP);
    AnimationUtils::Animate(
        scaleOption, [stackContext, scaleTo]() {
            CHECK_NULL_VOID(stackContext);
            stackContext->UpdateTransformScale(VectorF(scaleTo, scaleTo));
        },
        scaleOption.GetOnFinishEvent());
}

void ShowPixelMapScaleAnimationProc(
    const RefPtr<MenuTheme>& menuTheme, const RefPtr<FrameNode>& imageNode, const RefPtr<MenuPattern>& menuPattern)
{
    CHECK_NULL_VOID(menuPattern && menuTheme);
    auto scaleBefore = menuPattern->GetPreviewBeforeAnimationScale();
    auto scaleAfter = menuPattern->GetPreviewAfterAnimationScale();
    auto previewBeforeAnimationScale =
        LessNotEqual(scaleBefore, 0.0) ? menuTheme->GetPreviewBeforeAnimationScale() : scaleBefore;
    auto previewAfterAnimationScale =
        LessNotEqual(scaleAfter, 0.0) ? menuTheme->GetPreviewAfterAnimationScale() : scaleAfter;

    auto imagePattern = imageNode->GetPattern<ImagePattern>();
    CHECK_NULL_VOID(imagePattern);
    DragEventActuator::ExecutePreDragAction(PreDragStatus::PREVIEW_LIFT_STARTED);
    auto imageRawSize = imagePattern->GetRawImageSize();
    auto geometryNode = imageNode->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto geometrySize = geometryNode->GetFrameSize();
    if (geometrySize.IsPositive() && imageRawSize.IsPositive() && imageRawSize > geometrySize) {
        previewBeforeAnimationScale *= imageRawSize.Width() / geometrySize.Width();
    }

    CHECK_NULL_VOID(imageNode);
    auto imageContext = imageNode->GetRenderContext();
    CHECK_NULL_VOID(imageContext);
    imageContext->UpdateTransformScale(VectorF(previewBeforeAnimationScale, previewBeforeAnimationScale));

    AnimationOption scaleOption = AnimationOption();
    auto motion = AceType::MakeRefPtr<ResponsiveSpringMotion>(
        menuTheme->GetSpringMotionResponse(), menuTheme->GetSpringMotionDampingFraction());
    scaleOption.SetCurve(motion);
    scaleOption.SetOnFinishEvent(
        []() { DragEventActuator::ExecutePreDragAction(PreDragStatus::PREVIEW_LIFT_FINISHED); });

    auto menuWrapper = menuPattern->GetMenuWrapper();
    CHECK_NULL_VOID(menuWrapper);
    auto menuWrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();

    auto callback = [menuWrapperPattern, scaleFrom = previewBeforeAnimationScale, scaleTo = previewAfterAnimationScale](
                        float rate) {
        CHECK_NULL_VOID(menuWrapperPattern && !menuWrapperPattern->IsHide());
        menuWrapperPattern->SetAnimationPreviewScale(rate * (scaleTo - scaleFrom) + scaleFrom);
    };
    auto animateProperty = AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(-1.0, std::move(callback));
    CHECK_NULL_VOID(animateProperty);
    imageContext->AttachNodeAnimatableProperty(animateProperty);
    animateProperty->Set(0.0);
    AnimationUtils::Animate(
        scaleOption,
        [imageContext, previewAfterAnimationScale, animateProperty]() {
            CHECK_NULL_VOID(imageContext);
            imageContext->UpdateTransformScale(VectorF(previewAfterAnimationScale, previewAfterAnimationScale));
            CHECK_NULL_VOID(animateProperty);
            animateProperty->Set(1.0);
        },
        scaleOption.GetOnFinishEvent());
}

void HandleDragEnd(float offsetX, float offsetY, float velocity, const RefPtr<FrameNode>& menuWrapper)
{
    if ((LessOrEqual(std::abs(offsetY), std::abs(offsetX)) || LessOrEqual(offsetY, 0.0f)) &&
        LessOrEqual(velocity, PAN_MAX_VELOCITY)) {
        return;
    }
    CHECK_NULL_VOID(menuWrapper);
    auto wrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(wrapperPattern);
    TAG_LOGI(AceLogTag::ACE_MENU, "will hide menu");
    wrapperPattern->HideMenu();
}

void InitPanEvent(const RefPtr<GestureEventHub>& targetGestureHub, const RefPtr<GestureEventHub>& gestureHub,
    const RefPtr<FrameNode>& menuWrapper)
{
    auto dragEventActuator = targetGestureHub->GetDragEventActuator();
    auto actionStartTask = [actuator = AceType::WeakClaim(AceType::RawPtr(dragEventActuator))](
                               const GestureEvent& info) {
        auto dragEventActuator = actuator.Upgrade();
        CHECK_NULL_VOID(dragEventActuator);
        dragEventActuator->RestartDragTask(info);
    };
    auto actionEndTask = [menuWrapper](const GestureEvent& info) {
        auto offsetX = static_cast<float>(info.GetOffsetX());
        auto offsetY = static_cast<float>(info.GetOffsetY());
        auto offsetPerSecondX = info.GetVelocity().GetOffsetPerSecond().GetX();
        auto offsetPerSecondY = info.GetVelocity().GetOffsetPerSecond().GetY();
        auto velocity =
            static_cast<float>(std::sqrt(offsetPerSecondX * offsetPerSecondX + offsetPerSecondY * offsetPerSecondY));
        HandleDragEnd(offsetX, offsetY, velocity, menuWrapper);
    };
    PanDirection panDirection;
    panDirection.type = PanDirection::ALL;
    auto panEvent =
        AceType::MakeRefPtr<PanEvent>(std::move(actionStartTask), nullptr, std::move(actionEndTask), nullptr);
    auto distance = SystemProperties::GetDragStartPanDistanceThreshold();
    gestureHub->AddPanEvent(panEvent, panDirection, 1, Dimension(distance, DimensionUnit::VP));

    // add TouchEvent for Menu dragStart Move
    auto touchTask = [actuator = AceType::WeakClaim(AceType::RawPtr(dragEventActuator))](const TouchEventInfo& info) {
        auto dragEventActuator = actuator.Upgrade();
        CHECK_NULL_VOID(dragEventActuator);
        dragEventActuator->HandleTouchEvent(info, true);
    };
    auto touchListener = AceType::MakeRefPtr<TouchEventImpl>(std::move(touchTask));
    gestureHub->AddTouchEvent(touchListener);
}

float GetHoverImageCustomPreviewBaseScaleInfo(const MenuParam& menuParam, int32_t width, int32_t height,
    const RefPtr<MenuPreviewPattern>& previewPattern)
{
    float scaleRet = PREVIEW_ORIGIN_SCALE;
    CHECK_NULL_RETURN(menuParam.isShowHoverImage, scaleRet);
    CHECK_NULL_RETURN(previewPattern, scaleRet);
    // if the parent container is smaller than the child component, the child container will be squeezed
    auto previewWidth = previewPattern->GetStackAfterScaleActualWidth();
    auto previewHeight = previewPattern->GetStackAfterScaleActualHeight();
    CHECK_NULL_RETURN(width > 0 && height > 0, scaleRet);
    if (LessOrEqual(previewWidth / width, previewHeight / height)) {
        CHECK_EQUAL_RETURN(previewWidth, 0, scaleRet);
        scaleRet = width / previewWidth;
        previewPattern->SetIsWidthDistLarger(false);
    } else {
        CHECK_EQUAL_RETURN(previewHeight, 0, scaleRet);
        scaleRet = height / previewHeight;
        previewPattern->SetIsWidthDistLarger(true);
    }
    return scaleRet;
}

void SetHoverImageCustomPreviewInfo(const RefPtr<FrameNode>& previewNode, const MenuParam& menuParam,
    int32_t width, int32_t height)
{
    CHECK_NULL_VOID(previewNode);
    auto previewPattern = previewNode->GetPattern<MenuPreviewPattern>();
    CHECK_NULL_VOID(previewPattern);
    auto baseScale = GetHoverImageCustomPreviewBaseScaleInfo(menuParam, width, height, previewPattern);
    CHECK_NULL_VOID(baseScale);

    auto hoverImageScaleFrom = menuParam.hoverImageAnimationOptions.scaleFrom;
    hoverImageScaleFrom = LessOrEqual(hoverImageScaleFrom, 0.0) ? PREVIEW_ORIGIN_SCALE : hoverImageScaleFrom;
    previewPattern->SetHoverImageScaleFrom(baseScale * hoverImageScaleFrom);

    auto hoverImageScaleTo = menuParam.hoverImageAnimationOptions.scaleTo;
    hoverImageScaleTo = LessOrEqual(hoverImageScaleTo, 0.0) ? PREVIEW_ORIGIN_SCALE : hoverImageScaleTo;
    auto hoverImageScaleToNew = baseScale * hoverImageScaleTo;
    previewPattern->SetHoverImageScaleTo(hoverImageScaleToNew);
    previewPattern->SetIsHoverImageScaleNearEqual(NearEqual(hoverImageScaleFrom, hoverImageScaleTo));

    // get actual area size for clip visible area
    previewPattern->SetHoverImageAfterScaleWidth(width / baseScale);
    previewPattern->SetHoverImageAfterScaleHeight(height  / baseScale);

    // stack attr will not changed by the scale animation, but a start cooradinate is required to calc the clip diff
    previewPattern->SetClipStartWidth(previewPattern->GetStackAfterScaleActualWidth() * hoverImageScaleToNew);
    previewPattern->SetClipStartHeight(previewPattern->GetStackAfterScaleActualHeight() * hoverImageScaleToNew);
    previewPattern->SetClipStartValue(previewPattern->GetIsWidthDistLarger() ? previewPattern->GetClipStartWidth() :
        previewPattern->GetClipStartHeight());
    previewPattern->SetClipEndValue(previewPattern->GetIsWidthDistLarger() ?
        previewPattern->GetStackAfterScaleActualWidth() : previewPattern->GetStackAfterScaleActualHeight());

    previewPattern->SetHoverImageAfterScaleOffset(OffsetF((previewPattern->GetStackAfterScaleActualWidth() -
        previewPattern->GetHoverImageAfterScaleWidth()) / HALF_DIVIDE,
        (previewPattern->GetStackAfterScaleActualHeight() -
        previewPattern->GetHoverImageAfterScaleHeight()) / HALF_DIVIDE));
}

void SetAccessibilityPixelMap(const RefPtr<FrameNode>& targetNode, RefPtr<FrameNode>& imageNode)
{
    auto targetProps = targetNode->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(targetProps);
    targetProps->SetOnAccessibilityFocusCallback([targetWK = AceType::WeakClaim(AceType::RawPtr(targetNode)),
        imageWK = AceType::WeakClaim(AceType::RawPtr(imageNode))](bool focus) {
        if (!focus) {
            auto targetNode = targetWK.Upgrade();
            CHECK_NULL_VOID(targetNode);
            auto context = targetNode->GetRenderContext();
            CHECK_NULL_VOID(context);
            auto pixelMap = context->GetThumbnailPixelMap();
            CHECK_NULL_VOID(pixelMap);
            auto imageNode = imageWK.Upgrade();
            CHECK_NULL_VOID(imageNode);
            auto props = imageNode->GetLayoutProperty<ImageLayoutProperty>();
            CHECK_NULL_VOID(props);
            props->UpdateAutoResize(false);
            props->UpdateImageSourceInfo(ImageSourceInfo(pixelMap));
            imageNode->MarkModifyDone();
        }
    });
}

void SetPixelMap(const RefPtr<FrameNode>& target, const RefPtr<FrameNode>& wrapperNode,
    const RefPtr<FrameNode>& hoverImageStackNode, const RefPtr<FrameNode>& previewNode, const MenuParam& menuParam)
{
    CHECK_NULL_VOID(target);
    auto eventHub = target->GetEventHub<NG::EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto gestureHub = eventHub->GetGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    RefPtr<PixelMap> pixelMap = gestureHub->GetPixelMap();
    CHECK_NULL_VOID(pixelMap);
    auto width = pixelMap->GetWidth();
    auto height = pixelMap->GetHeight();
    auto imageOffset = GetFloatImageOffset(target);
    auto imageNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    imageNode->GetPaintProperty<ImageRenderProperty>()->UpdateImageInterpolation(ImageInterpolation::HIGH);
    auto props = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    props->UpdateAutoResize(false);
    props->UpdateImageSourceInfo(ImageSourceInfo(pixelMap));
    imageNode->GetPattern<ImagePattern>()->SetSyncLoad(true);
    SetAccessibilityPixelMap(target, imageNode);
    auto hub = imageNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto imageGestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(imageGestureHub);
    InitPanEvent(gestureHub, imageGestureHub, wrapperNode);

    if (menuParam.isShowHoverImage) {
        props->UpdateImageFit(ImageFit::CONTAIN);

        imageNode->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_PARENT);
        imageNode->MarkModifyDone();
        imageNode->MountToParent(hoverImageStackNode);
    } else {
        auto targetSize = CalcSize(NG::CalcLength(width), NG::CalcLength(height));
        props->UpdateUserDefinedIdealSize(targetSize);
        props->UpdateImageFit(ImageFit::FILL);

        auto imageContext = imageNode->GetRenderContext();
        CHECK_NULL_VOID(imageContext);
        if (menuParam.previewBorderRadius) {
            imageContext->UpdateBorderRadius(menuParam.previewBorderRadius.value());
        }
        imageNode->MarkModifyDone();
        imageNode->MountToParent(wrapperNode);
        DragAnimationHelper::UpdateGatherNodeToTop();
        DragDropFuncWrapper::UpdatePositionFromFrameNode(imageNode, target, width, height);
        imageOffset = DragDropFuncWrapper::GetPaintRectCenterToScreen(target) -
            OffsetF(width / HALF_DIVIDE, height / HALF_DIVIDE);
        imageOffset -= DragDropFuncWrapper::GetCurrentWindowOffset(imageNode->GetContextRefPtr());
        MountTextNode(wrapperNode, previewNode);
    }

    auto geometryNode = imageNode->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    geometryNode->SetFrameOffset(imageOffset);
}

void SetFilter(const RefPtr<FrameNode>& targetNode, const RefPtr<FrameNode>& menuWrapperNode)
{
    auto parent = targetNode->GetParent();
    CHECK_NULL_VOID(parent);
    while (parent->GetDepth() != 1) {
        parent = parent->GetParent();
        CHECK_NULL_VOID(parent);
    }
    auto containerId = Container::CurrentId();
    if (containerId >= MIN_SUBCONTAINER_ID) {
        containerId = SubwindowManager::GetInstance()->GetParentContainerId(containerId);
    }
    ContainerScope scope(containerId);
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto pipelineContext = AceType::DynamicCast<PipelineContext>(container->GetPipelineContext());
    CHECK_NULL_VOID(pipelineContext);
    auto manager = pipelineContext->GetOverlayManager();
    CHECK_NULL_VOID(manager);
    auto menuTheme = pipelineContext->GetTheme<NG::MenuTheme>();
    CHECK_NULL_VOID(menuTheme);
    if (!manager->GetHasFilter() && !manager->GetIsOnAnimation()) {
        bool isBindOverlayValue = targetNode->GetLayoutProperty()->GetIsBindOverlayValue(false);
        CHECK_NULL_VOID(isBindOverlayValue && menuTheme->GetHasFilter());
        // insert columnNode to rootNode
        auto columnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            AceType::MakeRefPtr<LinearLayoutPattern>(true));
        columnNode->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_PARENT);
        auto accessibilityProperty = columnNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
        if (accessibilityProperty) {
            accessibilityProperty->SetAccessibilityHoverPriority(true); // consume barrierfree hover event
        }
        // set filter
        if (container->IsScenceBoardWindow()) {
            auto windowScene = manager->FindWindowScene(targetNode);
            manager->MountFilterToWindowScene(columnNode, windowScene);
            manager->ShowFilterAnimation(columnNode);
        } else if (container->IsUIExtensionWindow()) {
            // mount filter node on subwindow to ensure filter node's size equals to host window's size
            CHECK_NULL_VOID(menuWrapperNode);
            auto menuWrapperPattern = menuWrapperNode->GetPattern<MenuWrapperPattern>();
            CHECK_NULL_VOID(menuWrapperPattern);
            menuWrapperPattern->SetFilterColumnNode(columnNode);
        } else {
            columnNode->MountToParent(parent);
            columnNode->OnMountToParentDone();
            manager->SetHasFilter(true);
            manager->SetFilterActive(true);
            manager->SetFilterColumnNode(columnNode);
            parent->MarkDirtyNode(NG::PROPERTY_UPDATE_BY_CHILD_REQUEST);
            manager->ShowFilterAnimation(columnNode);
        }
    }
}

void SetPreviewInfoToMenu(const RefPtr<FrameNode>& targetNode, const RefPtr<FrameNode>& wrapperNode,
    const RefPtr<FrameNode>& hoverImageStackNode, const RefPtr<FrameNode>& previewNode, const MenuParam& menuParam)
{
    CHECK_NULL_VOID(targetNode);
    auto eventHub = targetNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto gestureEventHub = eventHub->GetGestureEventHub();
    CHECK_NULL_VOID(gestureEventHub);
    auto isAllowedDrag = gestureEventHub->IsAllowedDrag(eventHub) && !gestureEventHub->GetTextDraggable();
    if (targetNode->GetTag() == V2::TEXT_ETS_TAG && targetNode->IsDraggable() && !targetNode->IsCustomerSet()) {
        auto textPattern = targetNode->GetPattern<TextPattern>();
        if (textPattern && textPattern->GetCopyOptions() == CopyOptions::None) {
            isAllowedDrag = false;
        }
    }
    if (menuParam.previewMode != MenuPreviewMode::NONE || isAllowedDrag) {
        DragDropGlobalController::GetInstance().UpdateDragFilterShowingStatus(true);
        SetFilter(targetNode, wrapperNode);
    }
    if (menuParam.previewMode == MenuPreviewMode::IMAGE ||
        (menuParam.previewMode == MenuPreviewMode::NONE && menuParam.menuBindType == MenuBindingType::LONG_PRESS &&
            isAllowedDrag) ||
        menuParam.isShowHoverImage) {
        SetPixelMap(targetNode, wrapperNode, hoverImageStackNode, previewNode, menuParam);
    }
    if (menuParam.previewMode == MenuPreviewMode::NONE && isAllowedDrag) {
        CHECK_NULL_VOID(wrapperNode);
        auto pixelMapNode = AceType::DynamicCast<FrameNode>(wrapperNode->GetChildAtIndex(1));
        CHECK_NULL_VOID(pixelMapNode);
        auto renderContext = pixelMapNode->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        renderContext->UpdateZIndex(-1);
        auto menuNode = AceType::DynamicCast<FrameNode>(wrapperNode->GetChildAtIndex(0));
        if (menuNode) {
            MenuView::ShowPixelMapAnimation(menuNode);
        }
        // if filter set in subwindow, need to adjust zOrder to show in back.
        auto menuWrapperPattern = wrapperNode->GetPattern<MenuWrapperPattern>();
        CHECK_NULL_VOID(menuWrapperPattern);
        auto columnNode = menuWrapperPattern->GetFilterColumnNode();
        CHECK_NULL_VOID(columnNode);
        auto columnRenderContext = columnNode->GetRenderContext();
        CHECK_NULL_VOID(columnRenderContext);
        columnRenderContext->UpdateZIndex(-1);
    }
}

void SetHasCustomRadius(
    const RefPtr<FrameNode>& menuWrapperNode, const RefPtr<FrameNode>& menuNode, const MenuParam& menuParam)
{
    CHECK_NULL_VOID(menuWrapperNode);
    CHECK_NULL_VOID(menuNode);
    auto menuWrapperPattern = menuWrapperNode->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(menuWrapperPattern);
    if (menuParam.borderRadius.has_value()) {
        menuWrapperPattern->SetHasCustomRadius(true);
        auto menuProperty = menuNode->GetLayoutProperty<MenuLayoutProperty>();
        CHECK_NULL_VOID(menuProperty);
        menuProperty->UpdateBorderRadius(menuParam.borderRadius.value());
    } else {
        menuWrapperPattern->SetHasCustomRadius(false);
    }
}

void SetMenuFocusRule(const RefPtr<FrameNode>& menuNode)
{
    CHECK_NULL_VOID(menuNode);
    auto focusHub = menuNode->GetFocusHub();
    CHECK_NULL_VOID(focusHub);

    auto pipelineContext = menuNode->GetContextWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    auto menuTheme = pipelineContext->GetTheme<NG::MenuTheme>();
    CHECK_NULL_VOID(menuTheme);
    focusHub->SetDirectionalKeyFocus(menuTheme->GetEnableDirectionalKeyFocus());
}

Alignment ConvertTxtTextAlign(bool IsRightToLeft, TextAlign textAlign)
{
    Alignment convertValue;
    switch (textAlign) {
        case TextAlign::LEFT:
            convertValue = Alignment::CENTER_LEFT;
            break;
        case TextAlign::CENTER:
            convertValue = Alignment::CENTER;
            break;
        case TextAlign::RIGHT:
            convertValue = Alignment::CENTER_RIGHT;
            break;
        case TextAlign::START:
            convertValue = IsRightToLeft ? Alignment::CENTER_RIGHT : Alignment::CENTER_LEFT;
            break;
        case TextAlign::END:
            convertValue = IsRightToLeft ? Alignment::CENTER_LEFT : Alignment::CENTER_RIGHT;
            break;
        default:
            break;
    }
    return convertValue;
}
} // namespace

void MenuView::CalcHoverScaleInfo(const RefPtr<FrameNode>& menuNode)
{
    CHECK_NULL_VOID(menuNode);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    CHECK_NULL_VOID(menuPattern->GetIsShowHoverImage());

    auto wrapperNode = menuPattern->GetMenuWrapper();
    CHECK_NULL_VOID(wrapperNode);
    auto menuWrapperPattern = wrapperNode->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(menuWrapperPattern);
    auto imageNode = menuWrapperPattern->GetHoverImagePreview();
    CHECK_NULL_VOID(imageNode);
    auto imagePattern = imageNode->GetPattern<ImagePattern>();
    CHECK_NULL_VOID(imagePattern);

    auto preview = menuWrapperPattern->GetPreview();
    CHECK_NULL_VOID(preview);
    auto previewGeometryNode = preview->GetGeometryNode();
    CHECK_NULL_VOID(previewGeometryNode);
    auto previewPattern = preview->GetPattern<MenuPreviewPattern>();
    CHECK_NULL_VOID(previewPattern);
    auto previewSize = previewGeometryNode->GetMarginFrameSize();
    previewPattern->SetStackAfterScaleActualWidth(previewSize.Width());
    previewPattern->SetStackAfterScaleActualHeight(previewSize.Height());

    auto menuParam = menuWrapperPattern->GetMenuParam();
    auto imageRawSize = imagePattern->GetRawImageSize();
    SetHoverImageCustomPreviewInfo(preview, menuParam, imageRawSize.Width(), imageRawSize.Height());
}

void MenuView::ShowPixelMapAnimation(const RefPtr<FrameNode>& menuNode)
{
    CHECK_NULL_VOID(menuNode);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    auto wrapperNode = menuPattern->GetMenuWrapper();
    CHECK_NULL_VOID(wrapperNode);
    auto menuWrapperPattern = wrapperNode->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(menuWrapperPattern);

    auto preview = AceType::DynamicCast<FrameNode>(wrapperNode->GetChildAtIndex(1));
    CHECK_NULL_VOID(preview);
    auto imageNode = preview->GetTag() == V2::FLEX_ETS_TAG ? menuWrapperPattern->GetHoverImagePreview() : preview;
    CHECK_NULL_VOID(imageNode);
    auto imageContext = imageNode->GetRenderContext();
    CHECK_NULL_VOID(imageContext);
    imageContext->SetClipToBounds(true);

    auto pipelineContext = menuNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto menuTheme = pipelineContext->GetTheme<NG::MenuTheme>();
    CHECK_NULL_VOID(menuTheme);

    auto isShowHoverImage = menuPattern->GetIsShowHoverImage();
    if (menuWrapperPattern->HasPreviewTransitionEffect()) {
        auto layoutProperty = imageNode->GetLayoutProperty();
        layoutProperty->UpdateVisibility(VisibleType::VISIBLE, true);
    }
    if (isShowHoverImage) {
        auto hoverImageStackNode = menuWrapperPattern->GetHoverImageStackNode();
        auto previewNode = menuWrapperPattern->GetHoverImageCustomPreview();
        ShowHoverImageAnimationProc(hoverImageStackNode, previewNode, imageContext, menuWrapperPattern);
    } else {
        ShowPixelMapScaleAnimationProc(menuTheme, imageNode, menuPattern);
    }
    ShowBorderRadiusAndShadowAnimation(menuTheme, imageNode, isShowHoverImage);
}

// create menu with MenuElement array
RefPtr<FrameNode> MenuView::Create(std::vector<OptionParam>&& params, int32_t targetId, const std::string& targetTag,
    MenuType type, const MenuParam& menuParam)
{
    auto [wrapperNode, menuNode] = CreateMenu(targetId, targetTag, type);
    CHECK_NULL_RETURN(wrapperNode && menuNode, nullptr);
    UpdateMenuBackgroundStyle(menuNode, menuParam);
    auto column = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    if (!menuParam.title.empty()) {
        CreateTitleNode(menuParam.title, column);
    }
    SetHasCustomRadius(wrapperNode, menuNode, menuParam);
    SetMenuFocusRule(menuNode);
    MountOptionToColumn(params, menuNode, menuParam, column);
    auto menuWrapperPattern = wrapperNode->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_RETURN(menuWrapperPattern, nullptr);
    menuWrapperPattern->SetHoverMode(menuParam.enableHoverMode);
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN) && !menuParam.enableArrow.value_or(false)) {
        UpdateMenuBorderEffect(menuNode);
    }
    auto menuProperty = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    if (menuProperty) {
        menuProperty->UpdateTitle(menuParam.title);
        menuProperty->UpdatePositionOffset(menuParam.positionOffset);
        if (menuParam.placement.has_value()) {
            menuProperty->UpdateMenuPlacement(menuParam.placement.value_or(OHOS::Ace::Placement::BOTTOM));
        }
        menuProperty->UpdateShowInSubWindow(menuParam.isShowInSubWindow);
    }
    UpdateMenuPaintProperty(menuNode, menuParam, type);
    auto scroll = CreateMenuScroll(column);
    CHECK_NULL_RETURN(scroll, nullptr);
    scroll->MountToParent(menuNode);
    scroll->MarkModifyDone();
    menuNode->MarkModifyDone();
    return wrapperNode;
}

void SetPreviewTransitionEffect(const RefPtr<FrameNode> &menuWrapperNode, const MenuParam &menuParam)
{
    TAG_LOGD(AceLogTag::ACE_DIALOG, "set menu transition effect");
    CHECK_NULL_VOID(menuWrapperNode);
    auto pattern = menuWrapperNode->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetHasPreviewTransitionEffect(menuParam.hasPreviewTransitionEffect);
}

void SetPreviewScaleAndHoverImageScale(const RefPtr<FrameNode>& menuNode, const MenuParam& menuParam)
{
    auto pattern = menuNode->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetPreviewMode(menuParam.previewMode);
    pattern->SetPreviewBeforeAnimationScale(menuParam.previewAnimationOptions.scaleFrom);
    pattern->SetPreviewAfterAnimationScale(menuParam.previewAnimationOptions.scaleTo);
    pattern->SetIsShowHoverImage(menuParam.isShowHoverImage);
}

void MenuView::CustomPreviewParentNodeCreate(const RefPtr<FrameNode>& stackNode, const RefPtr<FrameNode>& posNode,
    const RefPtr<FrameNode>& wrapperNode, const RefPtr<FrameNode>& previewNode)
{
    CHECK_NULL_VOID(previewNode);
    auto previewPattern = previewNode->GetPattern<MenuPreviewPattern>();
    CHECK_NULL_VOID(previewPattern);
    auto previewWidth = previewPattern->GetCustomPreviewWidth();
    auto previewHeight = previewPattern->GetCustomPreviewHeight();
    CHECK_NULL_VOID(stackNode);
    CalcSize maxSize = { CalcLength(previewWidth), CalcLength(previewHeight) };

    CHECK_NULL_VOID(posNode);
    UpdateContainerIdealSizeConstraint(posNode, maxSize);
    auto posProps = posNode->GetLayoutProperty<FlexLayoutProperty>();
    CHECK_NULL_VOID(posProps);
    posProps->UpdateMainAxisAlign(FlexAlign::CENTER);
    posProps->UpdateCrossAxisAlign(FlexAlign::CENTER);
    stackNode->MountToParent(posNode);
    stackNode->MarkModifyDone();

    CHECK_NULL_VOID(wrapperNode);
    posNode->MountToParent(wrapperNode);
    posNode->MarkModifyDone();
}

// contextmenu mount info proc
void MenuView::ContextMenuChildMountProc(const RefPtr<FrameNode>& targetNode, const RefPtr<FrameNode>& wrapperNode,
    const RefPtr<FrameNode>& previewNode, const RefPtr<FrameNode>& menuNode, const MenuParam& menuParam)
{
    // stack to put image and custom preview and control visible area when hoverImage api is using
    auto hoverImageStackNode = FrameNode::GetOrCreateFrameNode(V2::STACK_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<StackPattern>(); });
    CHECK_NULL_VOID(hoverImageStackNode);

    // flex  to control visible area position
    auto hoverImagePosNode = FrameNode::CreateFrameNode(V2::FLEX_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<FlexLayoutPattern>(false));
    CHECK_NULL_VOID(hoverImagePosNode);

    if (menuParam.isShowHoverImage) {
        CustomPreviewParentNodeCreate(hoverImageStackNode, hoverImagePosNode, wrapperNode, previewNode);
        CHECK_NULL_VOID(wrapperNode);
        auto menuWrapperPattern = wrapperNode->GetPattern<MenuWrapperPattern>();
        CHECK_NULL_VOID(menuWrapperPattern);
        menuWrapperPattern->SetIsShowHoverImage(menuParam.isShowHoverImage);
        auto previewRenderContext = previewNode->GetRenderContext();
        CHECK_NULL_VOID(previewRenderContext);
        previewRenderContext->UpdateOpacity(0.0);
    }
    
    if (menuNode) {
        SetPreviewInfoToMenu(targetNode, wrapperNode, hoverImageStackNode, previewNode, menuParam);
    }
    
    if (menuParam.previewMode == MenuPreviewMode::CUSTOM) {
        previewNode->MountToParent(menuParam.isShowHoverImage ? hoverImageStackNode : wrapperNode);
        previewNode->MarkModifyDone();
    }
}

// create menu with custom node from a builder
RefPtr<FrameNode> MenuView::Create(const RefPtr<UINode>& customNode, int32_t targetId, const std::string& targetTag,
    const MenuParam& menuParam, bool withWrapper, const RefPtr<UINode>& previewCustomNode)
{
    auto type = menuParam.type;
    auto [wrapperNode, menuNode] = CreateMenu(targetId, targetTag, type);
    CHECK_NULL_RETURN(wrapperNode && menuNode, nullptr);
    // create previewNode
    auto previewNode = FrameNode::CreateFrameNode(V2::MENU_PREVIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MenuPreviewPattern>());
    CHECK_NULL_RETURN(previewNode, nullptr);
    auto menuWrapperPattern = wrapperNode->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_RETURN(menuWrapperPattern, nullptr);
    menuWrapperPattern->SetMenuParam(menuParam);
    menuWrapperPattern->SetHoverMode(menuParam.enableHoverMode);

    CustomPreviewNodeProc(previewNode, menuParam, previewCustomNode);
    UpdateMenuBackgroundStyle(menuNode, menuParam);
    SetPreviewTransitionEffect(wrapperNode, menuParam);
    SetHasCustomRadius(wrapperNode, menuNode, menuParam);
    SetMenuFocusRule(menuNode);

    SetPreviewScaleAndHoverImageScale(menuNode, menuParam);
    // put custom node in a scroll to limit its height
    auto scroll = CreateMenuScroll(customNode);
    CHECK_NULL_RETURN(scroll, nullptr);
    MountScrollToMenu(customNode, scroll, type, menuNode);

    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN) && !menuParam.enableArrow.value_or(false)) {
        UpdateMenuBorderEffect(menuNode);
    }
    menuNode->MarkModifyDone();

    auto menuProperty = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    if (menuProperty) {
        menuProperty->UpdateTitle(menuParam.title);
        menuProperty->UpdatePositionOffset(menuParam.positionOffset);
        if (menuParam.placement.has_value()) {
            menuProperty->UpdateMenuPlacement(menuParam.placement.value());
        }
        menuProperty->UpdateShowInSubWindow(menuParam.isShowInSubWindow);
    }
    UpdateMenuPaintProperty(menuNode, menuParam, type);
    if (type == MenuType::SUB_MENU || type == MenuType::SELECT_OVERLAY_SUB_MENU || !withWrapper) {
        wrapperNode->RemoveChild(menuNode);
        wrapperNode.Reset();
        return menuNode;
    }
    if (type == MenuType::CONTEXT_MENU) {
        auto targetNode = FrameNode::GetFrameNode(targetTag, targetId);
        ContextMenuChildMountProc(targetNode, wrapperNode, previewNode, menuNode, menuParam);
        MountTextNode(wrapperNode, previewCustomNode);
    }
    return wrapperNode;
}

void MenuView::UpdateMenuPaintProperty(
    const RefPtr<FrameNode>& menuNode, const MenuParam& menuParam, const MenuType& type)
{
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        if (!(type == MenuType::CONTEXT_MENU || type == MenuType::MENU)) {
            return;
        }
    } else {
        if (!(type == MenuType::CONTEXT_MENU)) {
            return;
        }
    }

    auto paintProperty = menuNode->GetPaintProperty<MenuPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    paintProperty->UpdateEnableArrow(menuParam.enableArrow.value_or(false));
    paintProperty->UpdateArrowOffset(menuParam.arrowOffset.value_or(Dimension(0)));
}

RefPtr<FrameNode> MenuView::Create(
    const std::vector<SelectParam>& params, int32_t targetId, const std::string& targetTag)
{
    auto [wrapperNode, menuNode] = CreateMenu(targetId, targetTag);
    auto column = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    CHECK_NULL_RETURN(wrapperNode && menuNode, nullptr);
    SetMenuFocusRule(menuNode);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    CHECK_NULL_RETURN(menuPattern, nullptr);
    auto menuProperty = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_RETURN(menuProperty, nullptr);
    menuProperty->UpdateShowInSubWindow(false);
    for (size_t i = 0; i < params.size(); ++i) {
        auto optionNode = CreateSelectOption(params[i], i);
        auto optionPattern = optionNode->GetPattern<MenuItemPattern>();
        CHECK_NULL_RETURN(optionPattern, nullptr);
        optionPattern->SetIsSelectOption(true);
        menuPattern->AddOptionNode(optionNode);
        auto menuWeak = AceType::WeakClaim(AceType::RawPtr(menuNode));
        OptionKeepMenu(optionNode, menuWeak);
        // first node never paints divider
        if (i == 0) {
            auto props = optionNode->GetPaintProperty<MenuItemPaintProperty>();
            props->UpdateNeedDivider(false);
            auto focusHub = optionNode->GetOrCreateFocusHub();
            CHECK_NULL_RETURN(focusHub, nullptr);
            focusHub->SetIsDefaultFocus(true);
        }
        optionNode->MarkModifyDone();
        optionNode->MountToParent(column);
    }
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        UpdateMenuBorderEffect(menuNode);
    }
    auto scroll = CreateMenuScroll(column);
    CHECK_NULL_RETURN(scroll, nullptr);
    auto scrollPattern = scroll->GetPattern<ScrollPattern>();
    CHECK_NULL_RETURN(scrollPattern, nullptr);
    scrollPattern->SetIsSelectScroll(true);
    scroll->MountToParent(menuNode);
    scroll->MarkModifyDone();
    menuNode->MarkModifyDone();

    menuPattern->SetIsSelectMenu(true);
    return wrapperNode;
}

EffectOption CreateEffectOption(Dimension radius, double saturation, double brightness, Color color)
{
    EffectOption option;
    option.radius = radius;
    option.saturation = saturation;
    option.brightness = brightness;
    option.color = color;
    return option;
}

void MenuView::UpdateMenuBackgroundEffect(const RefPtr<FrameNode>& menuNode)
{
    CHECK_NULL_VOID(menuNode);
    auto pipeLineContext = menuNode->GetContextWithCheck();
    CHECK_NULL_VOID(pipeLineContext);
    auto menuTheme = pipeLineContext->GetTheme<NG::MenuTheme>();
    CHECK_NULL_VOID(menuTheme);
    if (menuTheme->GetBgBlurEffectEnable()) {
        auto renderContext = menuNode->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        auto saturation = menuTheme->GetBgEffectSaturation();
        auto brightness = menuTheme->GetBgEffectBrightness();
        auto radius = menuTheme->GetBgEffectRadius();
        auto color = menuTheme->GetBgEffectColor();
        EffectOption option = CreateEffectOption(radius, saturation, brightness, color);
        renderContext->UpdateBackgroundColor(Color::TRANSPARENT);
        renderContext->UpdateBackgroundEffect(option);
    }
}

void MenuView::UpdateMenuBorderEffect(const RefPtr<FrameNode>& menuNode)
{
    CHECK_NULL_VOID(menuNode);
    auto pipeLineContext = menuNode->GetContextWithCheck();
    CHECK_NULL_VOID(pipeLineContext);
    auto menuTheme = pipeLineContext->GetTheme<NG::MenuTheme>();
    CHECK_NULL_VOID(menuTheme);
    if (menuTheme->GetDoubleBorderEnable()) {
        auto renderContext = menuNode->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        BorderStyleProperty styleProp;
        styleProp.SetBorderStyle(BorderStyle::SOLID);
        BorderColorProperty outerColorProp;
        outerColorProp.SetColor(menuTheme->GetOuterBorderColor());
        auto theme = pipeLineContext->GetTheme<SelectTheme>();
        CHECK_NULL_VOID(theme);
        BorderRadiusProperty outerRadiusProp;
        outerRadiusProp.SetRadius(Dimension(Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE) ?
            theme->GetMenuDefaultRadius() : theme->GetMenuBorderRadius()));
        BorderWidthProperty outerWidthProp;
        outerWidthProp.SetBorderWidth(Dimension(menuTheme->GetOuterBorderWidth()));
        renderContext->SetOuterBorderStyle(styleProp);
        renderContext->SetOuterBorderColor(outerColorProp);
        renderContext->UpdateOuterBorderRadius(outerRadiusProp);
        renderContext->SetOuterBorderWidth(outerWidthProp);
        BorderColorProperty innerColorProp;
        innerColorProp.SetColor(menuTheme->GetInnerBorderColor());
        BorderRadiusProperty innerRadiusProp;
        innerRadiusProp.SetRadius(Dimension(Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE) ?
            theme->GetMenuDefaultRadius() : theme->GetMenuBorderRadius()));
        BorderWidthProperty innerWidthProp;
        innerWidthProp.SetBorderWidth(Dimension(menuTheme->GetInnerBorderWidth()));
        renderContext->SetBorderStyle(styleProp);
        renderContext->SetBorderColor(innerColorProp);
        renderContext->UpdateBorderRadius(innerRadiusProp);
        renderContext->SetBorderWidth(innerWidthProp);
    }
}
void MenuView::UpdateMenuBackgroundStyle(const RefPtr<FrameNode>& menuNode, const MenuParam& menuParam)
{
    auto menuNodeRenderContext = menuNode->GetRenderContext();
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN) &&
        menuNodeRenderContext->IsUniRenderEnabled()) {
        auto pipeLineContext = menuNode->GetContextWithCheck();
        CHECK_NULL_VOID(pipeLineContext);
        auto selectTheme = pipeLineContext->GetTheme<SelectTheme>();
        CHECK_NULL_VOID(selectTheme);
        BlurStyleOption styleOption;
        if (menuParam.blurStyleOption.has_value()) {
            styleOption = menuParam.blurStyleOption.value();
            if (styleOption.policy == BlurStyleActivePolicy::FOLLOWS_WINDOW_ACTIVE_STATE) {
                pipeLineContext->AddWindowFocusChangedCallback(menuNode->GetId());
            } else {
                pipeLineContext->RemoveWindowFocusChangedCallback(menuNode->GetId());
            }
        }
        Color color;
        if (selectTheme->GetMenuBlendBgColor()) {
            styleOption.blurStyle = static_cast<BlurStyle>(
                menuParam.backgroundBlurStyle.value_or(selectTheme->GetMenuNormalBackgroundBlurStyle()));
            color = menuParam.backgroundColor.value_or(selectTheme->GetBackgroundColor());
        } else {
            auto menuTheme = pipeLineContext->GetTheme<NG::MenuTheme>();
            CHECK_NULL_VOID(menuTheme);
            styleOption.blurStyle = static_cast<BlurStyle>(
                menuParam.backgroundBlurStyle.value_or(menuTheme->GetMenuBackgroundBlurStyle()));
            color = menuParam.backgroundColor.value_or(Color::TRANSPARENT);
        }
        if (menuParam.blurStyleOption.has_value() && menuNodeRenderContext->GetBackgroundEffect().has_value()) {
            menuNodeRenderContext->UpdateBackgroundEffect(std::nullopt);
        }
        menuNodeRenderContext->UpdateBackBlurStyle(styleOption);
        menuNodeRenderContext->UpdateBackgroundColor(color);
        if (menuParam.effectOption.has_value()) {
            if (menuParam.effectOption->policy == BlurStyleActivePolicy::FOLLOWS_WINDOW_ACTIVE_STATE) {
                pipeLineContext->AddWindowFocusChangedCallback(menuNode->GetId());
            } else {
                pipeLineContext->RemoveWindowFocusChangedCallback(menuNode->GetId());
            }
            if (menuNodeRenderContext->GetBackBlurStyle().has_value()) {
                menuNodeRenderContext->UpdateBackBlurStyle(std::nullopt);
            }
            menuNodeRenderContext->UpdateBackgroundEffect(menuParam.effectOption.value());
        }
    } else if (menuParam.backgroundColor.has_value()) {
        menuNodeRenderContext->UpdateBackgroundColor(menuParam.backgroundColor.value());
    }
}

void MenuView::NeedAgingUpdateNode(const RefPtr<FrameNode>& optionNode)
{
    CHECK_NULL_VOID(optionNode);
    auto pipeline = optionNode->GetContextWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto menuTheme = pipeline->GetTheme<NG::MenuTheme>();
    CHECK_NULL_VOID(menuTheme);
    auto fontScale = pipeline->GetFontScale();
    if (NearEqual(fontScale, menuTheme->GetBigFontSizeScale()) ||
        NearEqual(fontScale, menuTheme->GetLargeFontSizeScale()) ||
        NearEqual(fontScale, menuTheme->GetMaxFontSizeScale())) {
        auto optionPattern = optionNode->GetPattern<MenuItemPattern>();
        CHECK_NULL_VOID(optionPattern);
        auto textNode = AceType::DynamicCast<FrameNode>(optionPattern->GetTextNode());
        CHECK_NULL_VOID(textNode);
        auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textLayoutProperty);
        textLayoutProperty->UpdateMaxLines(menuTheme->GetTextMaxLines());
    }
}

void MenuView::CreateOption(bool optionsHasIcon, std::vector<OptionParam>& params, int32_t index,
    const RefPtr<FrameNode>& row, const RefPtr<FrameNode>& option)
{
    auto pattern = option->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(pattern);
    if (optionsHasIcon) {
        auto iconNode = CreateSymbol(params[index].symbol, row, nullptr, params[index].symbolUserDefinedIdealFontSize);
        pattern->SetIconNode(iconNode);
    }
    auto textNode = CreateText(params[index].value, row);
    row->MountToParent(option);
    row->MarkModifyDone();
    pattern->SetTextNode(textNode);
    pattern->SetBlockClick(params[index].disableSystemClick);

    auto eventHub = option->GetEventHub<MenuItemEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetMenuOnClick(params[index].action);
}

void MenuView::CreateOption(bool optionsHasIcon, const std::string& value, const std::string& icon,
    const RefPtr<FrameNode>& row, const RefPtr<FrameNode>& option, const std::function<void()>& onClickFunc)
{
    auto pattern = option->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(pattern);
    if (optionsHasIcon) {
        auto iconNode = CreateIcon(icon, row);
        pattern->SetIconNode(iconNode);
        pattern->SetIcon(icon);
    }
    auto textNode = CreateText(value, row);
    row->MountToParent(option);
    row->MarkModifyDone();
    pattern->SetTextNode(textNode);

    auto eventHub = option->GetEventHub<MenuItemEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetMenuOnClick(onClickFunc);
}

RefPtr<FrameNode> MenuView::CreateMenuOption(bool optionsHasIcon, std::vector<OptionParam>& params, int32_t index)
{
    auto option = Create(index);
    CHECK_NULL_RETURN(option, nullptr);
    auto row = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<MenuItemRowPattern>());

#ifdef OHOS_PLATFORM
    constexpr char BUTTON_PASTE[] = "textoverlay.paste";
    if (params[index].value == Localization::GetInstance()->GetEntryLetters(BUTTON_PASTE)) {
        CreatePasteButton(optionsHasIcon, option, row, params[index].action);
    } else {
        CreateOption(optionsHasIcon, params, index, row, option);
    }
#else
    CreateOption(optionsHasIcon, params, index, row, option);
#endif
    return option;
}

RefPtr<FrameNode> MenuView::CreateMenuOption(bool optionsHasIcon, const OptionValueInfo& value,
    const std::function<void()>& onClickFunc, int32_t index, const std::string& icon)
{
    auto option = Create(index);
    CHECK_NULL_RETURN(option, nullptr);
    auto row = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<MenuItemRowPattern>());

#ifdef OHOS_PLATFORM
    constexpr char BUTTON_PASTE[] = "textoverlay.paste";
    if (value.value == Localization::GetInstance()->GetEntryLetters(BUTTON_PASTE)) {
        CreatePasteButton(optionsHasIcon, option, row, onClickFunc, icon);
    } else {
        CreateOption(optionsHasIcon, value.value, icon, row, option, onClickFunc);
    }
#else
    CreateOption(optionsHasIcon, value.value, icon, row, option, onClickFunc);
#endif
    return option;
}

void MenuView::MountOptionToColumn(std::vector<OptionParam>& params, const RefPtr<FrameNode>& menuNode,
    const MenuParam& menuParam, RefPtr<FrameNode> column)
{
    bool optionsHasIcon = GetHasIcon(params);
    bool optionsHasSymbol = GetHasSymbol(params);
    RefPtr<FrameNode> optionNode = nullptr;
    // append options to menu
    for (size_t i = 0; i < params.size(); ++i) {
        if (params[i].symbol != nullptr) {
            optionNode = CreateMenuOption(optionsHasSymbol, params, i);
        } else {
            optionNode = CreateMenuOption(
                optionsHasIcon, { params[i].value, params[i].isPasteOption }, params[i].action, i, params[i].icon);
            if (optionNode) {
                auto optionPattern = optionNode->GetPattern<MenuItemPattern>();
                optionPattern->SetBlockClick(params[i].disableSystemClick);
            }
        }
        if (!optionNode) {
            continue;
        }
        NeedAgingUpdateNode(optionNode);
        auto menuPattern = menuNode->GetPattern<MenuPattern>();
        CHECK_NULL_VOID(menuPattern);
        menuPattern->AddOptionNode(optionNode);
        auto menuWeak = AceType::WeakClaim(AceType::RawPtr(menuNode));
        auto eventHub = optionNode->GetEventHub<EventHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->SetEnabled(params[i].enabled);
        auto focusHub = optionNode->GetFocusHub();
        CHECK_NULL_VOID(focusHub);
        focusHub->SetEnabled(params[i].enabled);

        OptionKeepMenu(optionNode, menuWeak);
        // first node never paints divider
        auto props = optionNode->GetPaintProperty<MenuItemPaintProperty>();
        if (i == 0 && menuParam.title.empty()) {
            props->UpdateNeedDivider(false);
        }
        if (optionsHasIcon) {
            props->UpdateHasIcon(true);
        }
        optionNode->MountToParent(column);
        optionNode->MarkModifyDone();
    }
}

void MenuView::CreatePasteButton(bool optionsHasIcon, const RefPtr<FrameNode>& option, const RefPtr<FrameNode>& row,
    const std::function<void()>& onClickFunc, const std::string& icon)
{
    auto pipeline = PipelineBase::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    auto overlayTheme = pipeline->GetTheme<TextOverlayTheme>();
    CHECK_NULL_VOID(overlayTheme);
    RefPtr<FrameNode> pasteNode;
    pasteNode = PasteButtonModelNG::GetInstance()->CreateNode(static_cast<int32_t>(PasteButtonPasteDescription::PASTE),
        optionsHasIcon ? static_cast<int32_t>(PasteButtonIconStyle::ICON_LINE) :
        static_cast<int32_t>(PasteButtonIconStyle::ICON_NULL),
        static_cast<int32_t>(ButtonType::NORMAL),
        true,
        optionsHasIcon ? overlayTheme->GetPasteSymbolId() : static_cast<int32_t>(PasteButtonIconStyle::ICON_NULL));
    CHECK_NULL_VOID(pasteNode);
    auto pattern = option->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(pattern);
    auto pasteLayoutProperty = pasteNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    CHECK_NULL_VOID(pasteLayoutProperty);
    auto pastePaintProperty = pasteNode->GetPaintProperty<SecurityComponentPaintProperty>();
    CHECK_NULL_VOID(pastePaintProperty);

    pasteLayoutProperty->UpdateFontSize(theme->GetMenuFontSize());
    pasteLayoutProperty->UpdateFontWeight(FontWeight::REGULAR);
    pastePaintProperty->UpdateFontColor(theme->GetMenuFontColor());
    pastePaintProperty->UpdateBackgroundColor(Color::TRANSPARENT);
    pasteLayoutProperty->UpdateBackgroundBorderRadius(BorderRadiusProperty(theme->GetInnerBorderRadius()));
    pasteLayoutProperty->UpdateIconSize(theme->GetIconSideLength());
    pastePaintProperty->UpdateIconColor(theme->GetMenuIconColor());
    pasteLayoutProperty->UpdateStateEffect(false);
    pasteLayoutProperty->UpdateHoverEffect(HoverEffectType::NONE);
    if (optionsHasIcon) {
        pasteLayoutProperty->UpdateTextIconSpace(theme->GetIconContentPadding());
    }
    pasteNode->MountToParent(row);
    pasteNode->MarkModifyDone();
    row->MountToParent(option);
    row->MarkModifyDone();
    auto eventHub = option->GetEventHub<MenuItemEventHub>();
    CHECK_NULL_VOID(eventHub);
    pasteNode->GetOrCreateGestureEventHub()->SetUserOnClick([onClickFunc](GestureEvent& info) {
        if (!PasteButtonModelNG::GetInstance()->IsClickResultSuccess(info)) {
            return;
        }
        if (onClickFunc) {
            onClickFunc();
        }
    });
    pattern->SetPasteButton(pasteNode);
}

RefPtr<FrameNode> MenuView::CreateSymbol(const std::function<void(WeakPtr<NG::FrameNode>)>& symbolApply,
    const RefPtr<FrameNode>& parent, const RefPtr<FrameNode>& child,
    const std::optional<Dimension>& symbolUserDefinedIdealFontSize)
{
    auto iconNode = FrameNode::GetOrCreateFrameNode(V2::SYMBOL_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    CHECK_NULL_RETURN(iconNode, nullptr);
    auto props = iconNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(props, nullptr);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_RETURN(theme, nullptr);
    props->UpdateFontSize(theme->GetEndIconWidth());
    props->UpdateSymbolColorList({theme->GetMenuIconColor()});
    props->UpdateAlignment(Alignment::CENTER_LEFT);
    MarginProperty margin;
    margin.right = CalcLength(theme->GetIconContentPadding());
    props->UpdateMargin(margin);
    if (symbolApply != nullptr) {
        symbolApply(AccessibilityManager::WeakClaim(AccessibilityManager::RawPtr(iconNode)));
    }
    if (symbolUserDefinedIdealFontSize.has_value()) {
        props->UpdateFontSize(symbolUserDefinedIdealFontSize.value());
    }
    if (child) {
        parent->ReplaceChild(child, iconNode);
    } else {
        iconNode->MountToParent(parent, 0);
    }
    iconNode->MarkModifyDone();
    return iconNode;
}

RefPtr<FrameNode> MenuView::CreateText(const std::string& value, const RefPtr<FrameNode>& parent)
{
    // create child text node
    auto textId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, textId, AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_RETURN(textNode, nullptr);

    auto textProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textProperty, nullptr);

    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_RETURN(theme, nullptr);

    textProperty->UpdateMaxLines(1);
    textProperty->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    textProperty->UpdateFontSize(theme->GetMenuFontSize());
    textProperty->UpdateFontWeight(FontWeight::REGULAR);
    textProperty->UpdateTextColor(theme->GetMenuFontColor());
    // set default foregroundColor
    auto textRenderContext = textNode->GetRenderContext();
    textRenderContext->UpdateForegroundColor(theme->GetMenuFontColor());
    textProperty->UpdateContent(value);
    auto padding = theme->GetOptionContentNormalLeftRightPadding();
    PaddingProperty textPadding;
    textPadding.left = CalcLength(padding);
    textPadding.right = CalcLength(padding);
    textProperty->UpdatePadding(textPadding);
    auto layoutDirection = textProperty->GetNonAutoLayoutDirection();
    auto IsRightToLeft = layoutDirection == TextDirection::RTL;
    auto textAlign = static_cast<TextAlign>(theme->GetOptionContentNormalAlign());
    auto convertValue = ConvertTxtTextAlign(IsRightToLeft, textAlign);
    textProperty->UpdateAlignment(convertValue);
    textNode->MountToParent(parent);
    textNode->MarkModifyDone();

    return textNode;
}

RefPtr<FrameNode> MenuView::CreateIcon(const std::string& icon, const RefPtr<FrameNode>& parent,
    const RefPtr<FrameNode>& child)
{
    auto iconNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    CHECK_NULL_RETURN(iconNode, nullptr);
    auto props = iconNode->GetLayoutProperty<ImageLayoutProperty>();
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_RETURN(theme, nullptr);
    if (!icon.empty()) {
        ImageSourceInfo info(icon);
        props->UpdateImageSourceInfo(info);
    }
    props->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(theme->GetIconSideLength()), CalcLength(theme->GetIconSideLength())));
    props->UpdateAlignment(Alignment::CENTER_LEFT);

    if (child) {
        parent->ReplaceChild(child, iconNode);
    } else {
        iconNode->MountToParent(parent, 0);
    }
    iconNode->MarkModifyDone();
    return iconNode;
}

RefPtr<FrameNode> MenuView::CreateSelectOption(const SelectParam& param, int32_t index)
{
    auto option = Create(index);
    auto row = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<MenuItemRowPattern>());
    row->MountToParent(option);

    auto pattern = option->GetPattern<MenuItemPattern>();
    CHECK_NULL_RETURN(pattern, option);
    // create icon node
    RefPtr<FrameNode> iconNode;
    if (param.symbolIcon != nullptr) {
        iconNode = CreateSymbol(param.symbolIcon, row);
    } else if (!param.icon.empty()) {
        iconNode = CreateIcon(param.icon, row);
        pattern->SetIcon(param.icon);
    }
    pattern->SetIconNode(iconNode);

    auto text = CreateText(param.text, row);
    pattern->SetTextNode(text);
    return option;
}

RefPtr<FrameNode> MenuView::Create(int32_t index)
{
    auto Id = ElementRegister::GetInstance()->MakeUniqueId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::OPTION_ETS_TAG, Id);
    auto node = FrameNode::CreateFrameNode(V2::OPTION_ETS_TAG, Id, AceType::MakeRefPtr<MenuItemPattern>(true, index));
    CHECK_NULL_RETURN(node, nullptr);

    // set border radius
    auto renderContext = node->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, nullptr);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_RETURN(theme, nullptr);
    BorderRadiusProperty border;
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        border.SetRadius(theme->GetMenuDefaultInnerRadius());
    } else {
        border.SetRadius(theme->GetInnerBorderRadius());
    }
    renderContext->UpdateBorderRadius(border);

    auto props = node->GetPaintProperty<MenuItemPaintProperty>();
    CHECK_NULL_RETURN(props, nullptr);
    props->UpdateHover(false);
    props->UpdatePress(false);

    auto layoutProp = node->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProp, nullptr);
    MarginProperty margin;
    auto verticalMargin = CalcLength(theme->GetOptionNormalTopBottomMargin());
    auto leftRightMargin = CalcLength(theme->GetOptionFocusedLeftRightMargin());
    margin.SetEdges(leftRightMargin, leftRightMargin, verticalMargin, verticalMargin);
    layoutProp->UpdateMargin(margin);
    return node;
}
} // namespace OHOS::Ace::NG
