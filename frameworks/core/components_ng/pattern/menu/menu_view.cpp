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
#include "base/memory/ace_type.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/manager/drag_drop/utils/drag_animation_helper.h"
#include "core/components_ng/pattern/flex/flex_layout_pattern.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/menu/menu_layout_property.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/menu/menu_theme.h"
#include "core/components_ng/pattern/menu/preview/menu_preview_pattern.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"
#include "core/components_ng/pattern/option/option_paint_property.h"
#include "core/components_ng/pattern/option/option_view.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

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
    AceType::MakeRefPtr<InterpolatingSpring>(0.0f, 1.0f, 328.0f, 34.0f);
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
    previewNode->Measure(layoutProperty->GetLayoutConstraint());
    auto previewSize = previewNode->GetGeometryNode()->GetFrameSize();
    previewPattern->SetIsShowHoverImage(true);
    previewPattern->SetCustomPreviewWidth(previewSize.Width());
    previewPattern->SetCustomPreviewHeight(previewSize.Height());

    auto previewScaleTo = menuParam.previewAnimationOptions.scaleTo;
    CHECK_NULL_VOID(previewScaleTo);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
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
        styleOption.blurStyle = BlurStyle::COMPONENT_ULTRA_THICK;
        renderContext->UpdateBackgroundColor(Color::TRANSPARENT);
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

    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    auto padding = static_cast<float>(theme->GetMenuIconPadding().ConvertToPx()) -
                   static_cast<float>(theme->GetOutPadding().ConvertToPx());
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

    auto eventHub = textNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(false);

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
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto theme = pipeline->GetTheme<SelectTheme>();
    float contentPadding = 0.0f;
    if (theme) {
        contentPadding = static_cast<float>(theme->GetOutPadding().ConvertToPx());
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
    auto pattern = option->GetPattern<OptionPattern>();
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
    auto offsetToWindow = frameNode->GetPaintRectOffset();
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

void ShowBorderRadiusAndShadowAnimation(const RefPtr<MenuTheme>& menuTheme, const RefPtr<RenderContext>& imageContext,
    bool isShowHoverImage)
{
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
    AnimationUtils::Animate(
        option,
        [imageContext, previewBorderRadius, shadow, isShowHoverImage]() mutable {
            CHECK_NULL_VOID(imageContext);
            auto color = shadow->GetColor();
            auto newColor = Color::FromARGB(100, color.GetRed(), color.GetGreen(), color.GetBlue());
            shadow->SetColor(newColor);
            imageContext->UpdateBackShadow(shadow.value());

            CHECK_NULL_VOID(!isShowHoverImage);
            imageContext->UpdateBorderRadius(previewBorderRadius);
        },
        option.GetOnFinishEvent());
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

void SetHoverImageStackBorderRadius(const RefPtr<FrameNode>& hoverImageStackNode, const RefPtr<MenuTheme>& menuTheme,
    const RefPtr<RenderContext>& imageContext, bool isScaleNearEqual)
{
    CHECK_NULL_VOID(hoverImageStackNode);
    auto stackContext = hoverImageStackNode->GetRenderContext();
    CHECK_NULL_VOID(stackContext);

    auto stackLayoutProps = hoverImageStackNode->GetLayoutProperty<StackLayoutProperty>();
    CHECK_NULL_VOID(stackLayoutProps);
    BorderWidthProperty widthProp;
    widthProp.SetBorderWidth(Dimension(0.0f));
    stackLayoutProps->UpdateBorderWidth(widthProp);
    stackContext->UpdateBorderWidth(widthProp);
    
    AnimationOption option;
    option.SetCurve(CUSTOM_PREVIEW_ANIMATION_CURVE);
    if (isScaleNearEqual) {
        option.SetDelay(menuTheme->GetHoverImageDelayDuration());
    }
    auto previewBorderRadius = menuTheme->GetPreviewBorderRadius();
    AnimationUtils::Animate(
        option, [stackContext, imageContext, previewBorderRadius]() {
            CHECK_NULL_VOID(stackContext);
            BorderRadiusProperty borderRadius;
            borderRadius.SetRadius(previewBorderRadius);
            stackContext->UpdateBorderRadius(borderRadius);

            CHECK_NULL_VOID(imageContext);
            imageContext->UpdateBorderRadius(borderRadius);
        });
}

void UpdatePreivewVisibleAreaByFrame(const RefPtr<RenderContext>& clipContext, 
    const RefPtr<MenuPreviewPattern>& previewPattern, float value, float radius, float distVal)
{
    CHECK_NULL_VOID(previewPattern);
    CHECK_NULL_VOID(distVal);
    auto rate = (value - previewPattern->GetClipStartValue()) / distVal;
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

void UpdatePreivewVisibleArea(const RefPtr<FrameNode>& hoverImageStackNode, const RefPtr<FrameNode>& previewNode,
    const RefPtr<MenuTheme>& menuTheme, bool isScaleNearEqual)
{
    auto previewPattern = previewNode->GetPattern<MenuPreviewPattern>();
    CHECK_NULL_VOID(previewPattern);

    auto clipStartValue = previewPattern->GetClipStartValue();
    auto clipEndValue = previewPattern->GetClipEndValue();
    clipEndValue += NearEqual(clipStartValue, clipEndValue) ? 1.0f : 0;
    auto dist = clipEndValue - clipStartValue;
    
    CHECK_NULL_VOID(hoverImageStackNode);
    hoverImageStackNode->CreateAnimatablePropertyFloat(HOVER_IMAGE_CLIP_PROPERTY_NAME, 0,
        [weak = AceType::WeakClaim(AceType::RawPtr(hoverImageStackNode)),
            previewWeak = AceType::WeakClaim(AceType::RawPtr(previewNode)),
            radius = menuTheme->GetPreviewBorderRadius().ConvertToPx(), distVal = dist](float value) {
            auto clipNode = weak.Upgrade();
            CHECK_NULL_VOID(clipNode);
            auto clipContext = clipNode->GetRenderContext();
            CHECK_NULL_VOID(clipContext);

            auto preview = previewWeak.Upgrade();
            CHECK_NULL_VOID(preview);
            auto previewPattern = preview->GetPattern<MenuPreviewPattern>();

            UpdatePreivewVisibleAreaByFrame(clipContext, previewPattern, value, radius, distVal);
        });
    AnimationOption option;
    option.SetCurve(CUSTOM_PREVIEW_ANIMATION_CURVE);
    if (isScaleNearEqual) { option.SetDelay(menuTheme->GetHoverImageDelayDuration()); }
    hoverImageStackNode->UpdateAnimatablePropertyFloat(HOVER_IMAGE_CLIP_PROPERTY_NAME, clipStartValue);
    auto clipAnimation_ = AnimationUtils::StartAnimation(option, [hoverImageStackNode, clipEndValue]() {
            CHECK_NULL_VOID(hoverImageStackNode);
            hoverImageStackNode->UpdateAnimatablePropertyFloat(HOVER_IMAGE_CLIP_PROPERTY_NAME, clipEndValue);
        });
}

void UpdateHoverImagePreviewScale(const RefPtr<FrameNode>& hoverImageStackNode,
    const RefPtr<MenuPreviewPattern>& previewPattern, const RefPtr<MenuTheme>& menuTheme, bool isScaleNearEqual)
{
    CHECK_NULL_VOID(hoverImageStackNode);
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
    auto callback = [weak = AceType::WeakClaim(AceType::RawPtr(menuWrapperPattern)), scaleFrom, scaleTo](float rate) {
        auto menuWrapperPattern = weak.Upgrade();
        CHECK_NULL_VOID(menuWrapperPattern);
        menuWrapperPattern->SetHoverImageToPreviewRate(rate);
        menuWrapperPattern->SetHoverImageToPreviewScale((scaleTo - scaleFrom) * rate + scaleFrom);
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

    SetHoverImageStackBorderRadius(hoverImageStackNode, menuTheme, imageContext, isScaleNearEqual);

    UpdateOpacityInFinishEvent(previewNode, imageContext, menuTheme, isScaleNearEqual);

    UpdatePreivewVisibleArea(hoverImageStackNode, previewNode, menuTheme, isScaleNearEqual);

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

    auto pipeline = PipelineBase::GetCurrentContext();
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
    DragEventActuator::ExecutePreDragAction(PreDragStatus::PREVIEW_LIFT_STARTED);
    auto previewBeforeAnimationScale =
        LessNotEqual(scaleBefore, 0.0) ? menuTheme->GetPreviewBeforeAnimationScale() : scaleBefore;
    auto previewAfterAnimationScale =
        LessNotEqual(scaleAfter, 0.0) ? menuTheme->GetPreviewAfterAnimationScale() : scaleAfter;

    CHECK_NULL_VOID(imageNode);
    auto imagePattern = imageNode->GetPattern<ImagePattern>();
    CHECK_NULL_VOID(imagePattern);
    auto imageRawSize = imagePattern->GetRawImageSize();
    auto geometryNode = imageNode->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto geometrySize = geometryNode->GetFrameSize();
    if (geometrySize.IsPositive() && imageRawSize.IsPositive() && imageRawSize > geometrySize) {
        previewBeforeAnimationScale *= imageRawSize.Width() / geometrySize.Width();
    }

    auto imageContext = imageNode->GetRenderContext();
    CHECK_NULL_VOID(imageContext);
    imageContext->UpdateTransformScale(VectorF(previewBeforeAnimationScale, previewBeforeAnimationScale));

    AnimationOption scaleOption = AnimationOption();
    auto motion = AceType::MakeRefPtr<ResponsiveSpringMotion>(
        menuTheme->GetSpringMotionResponse(), menuTheme->GetSpringMotionDampingFraction());
    scaleOption.SetCurve(motion);
    scaleOption.SetOnFinishEvent(
        []() { DragEventActuator::ExecutePreDragAction(PreDragStatus::PREVIEW_LIFT_FINISHED); });
    AnimationUtils::Animate(
        scaleOption, [imageContext, previewAfterAnimationScale]() {
            CHECK_NULL_VOID(imageContext);
            imageContext->UpdateTransformScale(VectorF(previewAfterAnimationScale, previewAfterAnimationScale));
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
        auto touchPoint = Point(
            info.GetTouches().front().GetGlobalLocation().GetX(), info.GetTouches().front().GetGlobalLocation().GetY());
        if (info.GetTouches().front().GetTouchType() == TouchType::DOWN) {
            dragEventActuator->SetDragDampStartPointInfo(touchPoint, info.GetTouches().front().GetFingerId());
        } else if (info.GetTouches().front().GetTouchType() == TouchType::MOVE) {
            dragEventActuator->HandleDragDampingMove(touchPoint, info.GetTouches().front().GetFingerId(), true);
        }
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
        imageContext->UpdatePosition(OffsetT<Dimension>(Dimension(imageOffset.GetX()), Dimension(imageOffset.GetY())));
        if (menuParam.previewBorderRadius) {
            imageContext->UpdateBorderRadius(menuParam.previewBorderRadius.value());
        }
        imageNode->MarkModifyDone();
        imageNode->MountToParent(wrapperNode);
        DragAnimationHelper::UpdateGatherNodeToTop();
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
    ShowBorderRadiusAndShadowAnimation(menuTheme, imageContext, isShowHoverImage);
}

// create menu with MenuElement array
RefPtr<FrameNode> MenuView::Create(std::vector<OptionParam>&& params, int32_t targetId, const std::string& targetTag,
    MenuType type, const MenuParam& menuParam)
{
    auto [wrapperNode, menuNode] = CreateMenu(targetId, targetTag, type);
    UpdateMenuBackgroundStyle(menuNode, menuParam);
    auto column = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    if (!menuParam.title.empty()) {
        CreateTitleNode(menuParam.title, column);
    }
    SetHasCustomRadius(wrapperNode, menuNode, menuParam);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    CHECK_NULL_RETURN(menuPattern, nullptr);
    bool optionsHasIcon = GetHasIcon(params);
    bool optionsHasSymbol = GetHasSymbol(params);
    RefPtr<FrameNode> optionNode = nullptr;
    // append options to menu
    for (size_t i = 0; i < params.size(); ++i) {
        if (params[i].symbol != nullptr) {
            optionNode = OptionView::CreateMenuOption(optionsHasSymbol, params, i);
        } else {
            optionNode = OptionView::CreateMenuOption(
                optionsHasIcon, { params[i].value, params[i].isPasteOption }, params[i].action, i, params[i].icon);
            if (optionNode) {
                auto optionPattern = optionNode->GetPattern<OptionPattern>();
                optionPattern->SetBlockClick(params[i].disableSystemClick);
            }
        }
        if (!optionNode) {
            continue;
        }
        NeedAgingUpdateNode(optionNode);
        menuPattern->AddOptionNode(optionNode);
        auto menuWeak = AceType::WeakClaim(AceType::RawPtr(menuNode));
        auto eventHub = optionNode->GetEventHub<EventHub>();
        CHECK_NULL_RETURN(eventHub, nullptr);
        eventHub->SetEnabled(params[i].enabled);
        auto focusHub = optionNode->GetFocusHub();
        CHECK_NULL_RETURN(focusHub, nullptr);
        focusHub->SetEnabled(params[i].enabled);

        OptionKeepMenu(optionNode, menuWeak);
        // first node never paints divider
        auto props = optionNode->GetPaintProperty<OptionPaintProperty>();
        if (i == 0 && menuParam.title.empty()) {
            props->UpdateNeedDivider(false);
        }
        if (optionsHasIcon) {
            props->UpdateHasIcon(true);
        }
        optionNode->MountToParent(column);
        optionNode->MarkModifyDone();
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
    // create previewNode
    auto previewNode = FrameNode::CreateFrameNode(V2::MENU_PREVIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MenuPreviewPattern>());
    CHECK_NULL_RETURN(previewNode, nullptr);
    auto menuWrapperPattern = wrapperNode->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_RETURN(menuWrapperPattern, nullptr);
    menuWrapperPattern->SetMenuParam(menuParam);

    CustomPreviewNodeProc(previewNode, menuParam, previewCustomNode);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    CHECK_NULL_RETURN(menuPattern, nullptr);
    menuPattern->SetHoverMode(menuParam.enableHoverMode);
    UpdateMenuBackgroundStyle(menuNode, menuParam);
    SetPreviewTransitionEffect(wrapperNode, menuParam);
    SetHasCustomRadius(wrapperNode, menuNode, menuParam);

    SetPreviewScaleAndHoverImageScale(menuNode, menuParam);
    // put custom node in a scroll to limit its height
    auto scroll = CreateMenuScroll(customNode);
    CHECK_NULL_RETURN(scroll, nullptr);
    MountScrollToMenu(customNode, scroll, type, menuNode);

    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
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
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    CHECK_NULL_RETURN(menuPattern, nullptr);
    auto menuProperty = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_RETURN(menuProperty, nullptr);
    menuProperty->UpdateShowInSubWindow(false);
    for (size_t i = 0; i < params.size(); ++i) {
        auto optionNode = OptionView::CreateSelectOption(params[i], i);
        auto optionPattern = optionNode->GetPattern<OptionPattern>();
        CHECK_NULL_RETURN(optionPattern, nullptr);
        optionPattern->SetIsSelectOption(true);
        menuPattern->AddOptionNode(optionNode);
        auto menuWeak = AceType::WeakClaim(AceType::RawPtr(menuNode));
        OptionKeepMenu(optionNode, menuWeak);
        // first node never paints divider
        if (i == 0) {
            auto props = optionNode->GetPaintProperty<OptionPaintProperty>();
            props->UpdateNeedDivider(false);
            auto focusHub = optionNode->GetOrCreateFocusHub();
            CHECK_NULL_RETURN(focusHub, nullptr);
            focusHub->SetIsDefaultFocus(true);
        }
        optionNode->MarkModifyDone();
        optionNode->MountToParent(column);
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

void MenuView::UpdateMenuBackgroundEffect(const RefPtr<FrameNode>& menuNode)
{
    auto pipeLineContext = PipelineContext::GetCurrentContext();
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
        EffectOption option = { radius, saturation, brightness, color };
        renderContext->UpdateBackgroundColor(Color::TRANSPARENT);
        renderContext->UpdateBackgroundEffect(option);
    }
}

void MenuView::UpdateMenuBorderEffect(const RefPtr<FrameNode>& menuNode)
{
    auto pipeLineContext = PipelineContext::GetCurrentContext();
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
        BlurStyleOption styleOption;
        styleOption.blurStyle = static_cast<BlurStyle>(
            menuParam.backgroundBlurStyle.value_or(static_cast<int>(BlurStyle::COMPONENT_ULTRA_THICK)));
        menuNodeRenderContext->UpdateBackBlurStyle(styleOption);
        menuNodeRenderContext->UpdateBackgroundColor(menuParam.backgroundColor.value_or(Color::TRANSPARENT));
    } else if (menuParam.backgroundColor.has_value()) {
        menuNodeRenderContext->UpdateBackgroundColor(menuParam.backgroundColor.value());
    }
}

void MenuView::NeedAgingUpdateNode(const RefPtr<FrameNode>& optionNode)
{
    CHECK_NULL_VOID(optionNode);
    auto pipeline = NG::PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_VOID(pipeline);
    auto menuTheme = pipeline->GetTheme<NG::MenuTheme>();
    CHECK_NULL_VOID(menuTheme);
    auto fontScale = pipeline->GetFontScale();
    if (NearEqual(fontScale, menuTheme->GetBigFontSizeScale()) ||
        NearEqual(fontScale, menuTheme->GetLargeFontSizeScale()) ||
        NearEqual(fontScale, menuTheme->GetMaxFontSizeScale())) {
        auto optionPattern = optionNode->GetPattern<OptionPattern>();
        CHECK_NULL_VOID(optionPattern);
        auto textNode = AceType::DynamicCast<FrameNode>(optionPattern->GetTextNode());
        CHECK_NULL_VOID(textNode);
        auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textLayoutProperty);
        textLayoutProperty->UpdateMaxLines(menuTheme->GetTextMaxLines());
    }
}
} // namespace OHOS::Ace::NG
