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
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components/common/properties/placement.h"
#include "core/components_ng/manager/drag_drop/utils/drag_animation_helper.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
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
constexpr float HALF_DIVIDER_VALUE = 2.0f;

void SetSelfAndChildDraggableFalse(const RefPtr<UINode>& customNode)
{
    CHECK_NULL_VOID(customNode);
    auto frameNode = AceType::DynamicCast<FrameNode>(customNode);
    if (frameNode) {
        auto eventHub = frameNode->GetEventHub<EventHub>();
        CHECK_NULL_VOID(eventHub);
        auto gestureEventHub = eventHub->GetGestureEventHub();
        CHECK_NULL_VOID(gestureEventHub);
        gestureEventHub->SetDragForbiddenForcely(true);
    }
    for (const auto& child : customNode->GetChildren()) {
        SetSelfAndChildDraggableFalse(child);
    }
}

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
        borderRadius.SetRadius(theme->GetMenuBorderRadius());
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
        if (!params[i].icon.empty()) {
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

OffsetF GetFloatImageOffset(const RefPtr<FrameNode>& frameNode, const RefPtr<PixelMap>& pixelMap = nullptr)
{
    if (pixelMap) {
        CHECK_NULL_RETURN(frameNode, OffsetF());
        auto centerPosition = frameNode->GetPaintRectCenter(true);
        float width = 0.0f;
        float height = 0.0f;
        if (pixelMap) {
            width = pixelMap->GetWidth();
            height = pixelMap->GetHeight();
        }
        auto offsetX = centerPosition.GetX() - width / 2.0f;
        auto offsetY = centerPosition.GetY() - height / 2.0f;
        return OffsetF(offsetX, offsetY);
    }
    auto offsetToWindow = frameNode->GetPaintRectOffset();
    auto offsetX = offsetToWindow.GetX();
    auto offsetY = offsetToWindow.GetY();
    return OffsetF(offsetX, offsetY);
}

RefPtr<MenuPattern> GetMenuPattern(const RefPtr<FrameNode>& menuNode)
{
    CHECK_NULL_RETURN(menuNode, nullptr);
    auto menuHostNode = menuNode->GetChildByIndex(0)->GetHostNode();
    CHECK_NULL_RETURN(menuHostNode, nullptr);
    return menuHostNode->GetPattern<MenuPattern>();
}

void ShowBorderRadiusAndShadowAnimation(const RefPtr<MenuTheme>& menuTheme, const RefPtr<RenderContext>& imageContext)
{
    auto shadow = imageContext->GetBackShadow();
    if (!shadow.has_value()) {
        shadow = Shadow::CreateShadow(ShadowStyle::None);
    }
    AnimationOption option;
    option.SetDuration(menuTheme->GetPreviewAnimationDuration());
    option.SetCurve(Curves::SHARP);
    auto previewBorderRadius = menuTheme->GetPreviewBorderRadius();
    AnimationUtils::Animate(
        option,
        [imageContext, previewBorderRadius, shadow]() mutable {
            if (imageContext) {
                auto color = shadow->GetColor();
                auto newColor = Color::FromARGB(100, color.GetRed(), color.GetGreen(), color.GetBlue());
                shadow->SetColor(newColor);
                imageContext->UpdateBackShadow(shadow.value());
                BorderRadiusProperty borderRadius;
                borderRadius.SetRadius(previewBorderRadius);
                imageContext->UpdateBorderRadius(borderRadius);
            }
        },
        option.GetOnFinishEvent());
}

void SetHoverImageFinishEvent(const RefPtr<RenderContext>& imageContext, const RefPtr<MenuTheme>& menuTheme,
    bool isShow, bool isScaleNearEqual = true)
{
    CHECK_NULL_VOID(isShow);
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
    imageContext->UpdateOpacity(1.0);
    AnimationUtils::Animate(
        option, [imageContext]() {
            if (imageContext) {
                imageContext->UpdateOpacity(0.0);
            }
        },
        option.GetOnFinishEvent());
}

void ShowPixelMapScaleAnimationProc(const RefPtr<MenuTheme>& menuTheme, const RefPtr<RenderContext>& imageContext,
    const RefPtr<MenuPattern>& menuPattern, const MenuParam& menuParam)
{
    auto scaleBefore = menuParam.isShowHoverImage ? menuParam.hoverImageAnimationOptions.scaleFrom :
        menuPattern->GetPreviewBeforeAnimationScale();
    auto scaleAfter = menuParam.isShowHoverImage ? menuParam.hoverImageAnimationOptions.scaleTo :
        menuPattern->GetPreviewAfterAnimationScale();
    DragEventActuator::ExecutePreDragAction(PreDragStatus::PREVIEW_LIFT_STARTED);
    auto previewBeforeAnimationScale =
        LessNotEqual(scaleBefore, 0.0) ? menuTheme->GetPreviewBeforeAnimationScale() : scaleBefore;
    auto previewAfterAnimationScale =
        LessNotEqual(scaleAfter, 0.0) ? menuTheme->GetPreviewAfterAnimationScale() : scaleAfter;

    imageContext->UpdateTransformScale(VectorF(previewBeforeAnimationScale, previewBeforeAnimationScale));

    AnimationOption scaleOption = AnimationOption();
    if (menuParam.isShowHoverImage) {
        scaleOption.SetDuration(menuTheme->GetHoverImageDelayDuration());
        scaleOption.SetCurve(Curves::SHARP);
    } else {
        auto motion = AceType::MakeRefPtr<ResponsiveSpringMotion>(
            menuTheme->GetSpringMotionResponse(), menuTheme->GetSpringMotionDampingFraction());
        scaleOption.SetCurve(motion);
    }

    // when the scaling start and end sizes are the same, the end callback method should not be relied on
    bool isScaleNearEqual = NearEqual(previewBeforeAnimationScale, previewAfterAnimationScale);
    if (isScaleNearEqual) {
        SetHoverImageFinishEvent(imageContext, menuTheme, menuParam.isShowHoverImage);
        scaleOption.SetOnFinishEvent([]() {
            DragEventActuator::ExecutePreDragAction(PreDragStatus::PREVIEW_LIFT_FINISHED);
            });
    } else {
        scaleOption.SetOnFinishEvent(
            [imageContext, menuTheme, isShow = menuParam.isShowHoverImage, isScaleNearEqual]() {
                DragEventActuator::ExecutePreDragAction(PreDragStatus::PREVIEW_LIFT_FINISHED);
                SetHoverImageFinishEvent(imageContext, menuTheme, isShow, isScaleNearEqual);
            });
    }
    AnimationUtils::Animate(
        scaleOption,
        [imageContext, previewAfterAnimationScale]() {
            if (imageContext) {
                imageContext->UpdateTransformScale(VectorF(previewAfterAnimationScale, previewAfterAnimationScale));
            }
        },
        scaleOption.GetOnFinishEvent());
}

void ShowPixelMapAnimation(const RefPtr<FrameNode>& imageNode, const RefPtr<FrameNode>& wrapperNode,
    const RefPtr<FrameNode>& previewNode, const MenuParam& menuParam)
{
    auto menuPattern = GetMenuPattern(wrapperNode);
    CHECK_NULL_VOID(menuPattern);
    auto imageContext = imageNode->GetRenderContext();
    CHECK_NULL_VOID(imageContext);
    imageContext->SetClipToBounds(true);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto menuTheme = pipeline->GetTheme<NG::MenuTheme>();
    CHECK_NULL_VOID(menuTheme);
    auto menuWrapperPattern = wrapperNode->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(menuWrapperPattern);
    if (menuWrapperPattern->HasPreviewTransitionEffect()) {
        auto layoutProperty = imageNode->GetLayoutProperty();
        layoutProperty->UpdateVisibility(VisibleType::VISIBLE, true);
    } else {
        ShowPixelMapScaleAnimationProc(menuTheme, imageContext, menuPattern, menuParam);
    }

    ShowBorderRadiusAndShadowAnimation(menuTheme, imageContext);
}

void ShowGatherAnimation(const RefPtr<FrameNode>& imageNode, const RefPtr<FrameNode>& menuNode)
{
    auto mainPipeline = PipelineContext::GetMainPipelineContext();
    CHECK_NULL_VOID(mainPipeline);
    auto manager = mainPipeline->GetOverlayManager();
    CHECK_NULL_VOID(manager);
    manager->UpdateGatherNodeToTop();
    auto gatherNode = manager->GetGatherNode();
    CHECK_NULL_VOID(gatherNode);
    auto textNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    CHECK_NULL_VOID(textNode);
    textNode->MountToParent(menuNode);
    textNode->MarkModifyDone();
    auto menuPattern = GetMenuPattern(menuNode);
    CHECK_NULL_VOID(menuPattern);
    mainPipeline->AddAfterRenderTask([weakImageNode = AceType::WeakClaim(AceType::RawPtr(imageNode)),
        weakManager = AceType::WeakClaim(AceType::RawPtr(manager)),
        weakTextNode = AceType::WeakClaim(AceType::RawPtr(textNode)),
        weakMenuPattern = AceType::WeakClaim(AceType::RawPtr(menuPattern))]() {
        auto imageNode = weakImageNode.Upgrade();
        auto manager = weakManager.Upgrade();
        auto textNode = weakTextNode.Upgrade();
        auto menuPattern = weakMenuPattern.Upgrade();
        DragAnimationHelper::PlayGatherAnimation(imageNode, manager);
        DragAnimationHelper::CalcBadgeTextPosition(menuPattern, manager, imageNode, textNode);
        DragAnimationHelper::ShowBadgeAnimation(textNode);
    });
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
    float previewWidth, float previewHeight)
{
    float scaleRet = 1.0f;
    CHECK_NULL_RETURN(menuParam.isShowHoverImage, scaleRet);
    if (previewWidth - width < previewHeight - height) {
        CHECK_EQUAL_RETURN(previewWidth, 0, scaleRet);
        scaleRet = width / previewWidth;
    } else {
        CHECK_EQUAL_RETURN(previewHeight, 0, scaleRet);
        scaleRet = height / previewHeight;
    }
    return scaleRet;
}

void SetHoverImageCustomPreviewInfo(const RefPtr<FrameNode>& previewNode, const MenuParam& menuParam,
    int32_t width, int32_t height)
{
    CHECK_NULL_VOID(previewNode);
    auto previewPattern = previewNode->GetPattern<MenuPreviewPattern>();
    CHECK_NULL_VOID(previewPattern);
    auto previewWidth = previewPattern->GetCustomPreviewWidth();
    auto previewHeight = previewPattern->GetCustomPreviewHeight();
    auto scale = GetHoverImageCustomPreviewBaseScaleInfo(menuParam, width, height, previewWidth, previewHeight);
    CHECK_NULL_VOID(scale);
    auto hoverImageScaleTo = menuParam.hoverImageAnimationOptions.scaleTo;
    hoverImageScaleTo = LessOrEqual(hoverImageScaleTo, 0.0) ? hoverImageScaleTo : 1.0f;
    auto previewScaleFrom = LessOrEqual(menuParam.previewAnimationOptions.scaleFrom, 0.0) ? scale * hoverImageScaleTo :
        menuParam.previewAnimationOptions.scaleFrom;
    previewPattern->SetCustomPreviewScaleFrom(previewScaleFrom);

    auto previewScaleTo = menuParam.previewAnimationOptions.scaleTo;
    CHECK_NULL_VOID(previewScaleTo);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto menuTheme = pipeline->GetTheme<NG::MenuTheme>();
    CHECK_NULL_VOID(menuTheme);
    previewScaleTo = LessOrEqual(previewScaleTo, 0.0) ? menuTheme->GetPreviewAfterAnimationScale() : previewScaleTo;
    previewPattern->SetCustomPreviewScaleTo(previewScaleTo);
    previewPattern->SetHoverImageDisAppearScaleTo(previewScaleTo / scale);

    auto previewPositionXDist = (previewWidth - width) / HALF_DIVIDER_VALUE;
    auto previewPositionYDist = (previewHeight - height) / HALF_DIVIDER_VALUE;
    previewPattern->SetCustomPreviewPositionXDist(previewPositionXDist);
    previewPattern->SetCustomPreviewPositionYDist(previewPositionYDist);
}

void SetPixelMap(const RefPtr<FrameNode>& target, const RefPtr<FrameNode>& wrapperNode,
    const RefPtr<FrameNode>& previewNode, const MenuParam& menuParam)
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
    SetHoverImageCustomPreviewInfo(previewNode, menuParam, width, height);
    auto imageOffset = GetFloatImageOffset(target, pixelMap);
    auto imageNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    auto renderProps = imageNode->GetPaintProperty<ImageRenderProperty>();
    renderProps->UpdateImageInterpolation(ImageInterpolation::HIGH);
    auto props = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    props->UpdateAutoResize(false);
    props->UpdateImageSourceInfo(ImageSourceInfo(pixelMap));
    auto targetSize = CalcSize(NG::CalcLength(width), NG::CalcLength(height));
    props->UpdateUserDefinedIdealSize(targetSize);
    props->UpdateImageFit(ImageFit::FILL);
    auto hub = imageNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto imageGestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(imageGestureHub);
    InitPanEvent(gestureHub, imageGestureHub, wrapperNode);

    if (!menuParam.isShowHoverImage) {
        ShowGatherAnimation(target, wrapperNode);
    }
    auto imageContext = imageNode->GetRenderContext();
    CHECK_NULL_VOID(imageContext);
    imageContext->UpdatePosition(OffsetT<Dimension>(Dimension(imageOffset.GetX()), Dimension(imageOffset.GetY())));
    imageNode->MarkModifyDone();
    imageNode->MountToParent(wrapperNode);
    auto geometryNode = imageNode->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    geometryNode->SetFrameOffset(imageOffset);
    auto menuWrapperPattern = wrapperNode->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(menuWrapperPattern);
    ShowPixelMapAnimation(imageNode, wrapperNode, previewNode, menuParam);
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
    const RefPtr<FrameNode>& previewNode, const RefPtr<FrameNode>& menuNode, const MenuParam& menuParam)
{
    CHECK_NULL_VOID(menuNode);
    CHECK_NULL_VOID(targetNode);
    if (menuParam.previewMode != MenuPreviewMode::NONE || targetNode->IsDraggable()) {
        SetFilter(targetNode, wrapperNode);
    }
    if (menuParam.previewMode == MenuPreviewMode::IMAGE || menuParam.previewMode == MenuPreviewMode::NONE ||
        menuParam.isShowHoverImage) {
        SetPixelMap(targetNode, wrapperNode, previewNode, menuParam);
    }
    if (menuParam.previewMode == MenuPreviewMode::NONE) {
        auto renderContext = menuNode->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        renderContext->UpdateZIndex(1);
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
            optionNode = OptionView::CreateMenuOption(
                optionsHasSymbol, params[i].value, params[i].action, i, params[i].symbol);
        } else {
            optionNode = OptionView::CreateMenuOption(
                optionsHasIcon, params[i].value, params[i].action, i, params[i].icon);
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
    pattern->SetHoverImageBeforeAnimationScale(menuParam.hoverImageAnimationOptions.scaleFrom);
    pattern->SetHoverImageAfterAnimationScale(menuParam.hoverImageAnimationOptions.scaleTo);
}

void SetCustomPreviewOpacityWhenHoverImage(const RefPtr<FrameNode>& menuWrapperNode, const MenuParam& menuParam)
{
    CHECK_NULL_VOID(menuParam.isShowHoverImage);
    CHECK_NULL_VOID(menuWrapperNode);
    auto menuWrapperPattern = menuWrapperNode->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(menuWrapperPattern);
    menuWrapperPattern->SetIsShowHoverImage(menuParam.isShowHoverImage);
    auto preview = menuWrapperPattern->GetPreview();
    CHECK_NULL_VOID(preview);
    auto previewRenderContext = preview->GetRenderContext();
    CHECK_NULL_VOID(previewRenderContext);
    previewRenderContext->UpdateOpacity(0.0);
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
    CustomPreviewNodeProc(previewNode, menuParam, previewCustomNode);

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
        SetPreviewInfoToMenu(targetNode, wrapperNode, previewNode, menuNode, menuParam);
        if (menuParam.previewMode == MenuPreviewMode::CUSTOM) {
            previewNode->MountToParent(wrapperNode);
            previewNode->MarkModifyDone();
            SetSelfAndChildDraggableFalse(previewCustomNode);
            MountTextNode(wrapperNode, previewCustomNode);
            SetCustomPreviewOpacityWhenHoverImage(wrapperNode, menuParam);
        }
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
        outerRadiusProp.SetRadius(Dimension(theme->GetMenuBorderRadius()));
        BorderWidthProperty outerWidthProp;
        outerWidthProp.SetBorderWidth(Dimension(menuTheme->GetOuterBorderWidth()));
        renderContext->SetOuterBorderStyle(styleProp);
        renderContext->SetOuterBorderColor(outerColorProp);
        renderContext->UpdateOuterBorderRadius(outerRadiusProp);
        renderContext->SetOuterBorderWidth(outerWidthProp);
        BorderColorProperty innerColorProp;
        innerColorProp.SetColor(menuTheme->GetInnerBorderColor());
        BorderRadiusProperty innerRadiusProp;
        innerRadiusProp.SetRadius(Dimension(theme->GetMenuBorderRadius()));
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
