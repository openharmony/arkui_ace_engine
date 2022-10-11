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

#include "core/components_ng/base/view_abstract.h"

#include <cstdint>
#include <optional>
#include <utility>

#include "base/geometry/ng/offset_t.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/bubble/bubble_view.h"
#include "core/components_ng/pattern/menu/menu_view.h"
#include "core/components_ng/pattern/option/option_paint_property.h"
#include "core/components_ng/pattern/option/option_view.h"
#include "core/image/image_source_info.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {
void ViewAbstract::SetWidth(const CalcLength& width)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(width, std::nullopt));
}

void ViewAbstract::SetHeight(const CalcLength& height)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, height));
}

void ViewAbstract::SetMinWidth(const CalcLength& width)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateCalcMinSize(CalcSize(width, std::nullopt));
}

void ViewAbstract::SetMinHeight(const CalcLength& height)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateCalcMinSize(CalcSize(std::nullopt, height));
}

void ViewAbstract::SetMaxWidth(const CalcLength& width)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateCalcMaxSize(CalcSize(width, std::nullopt));
}

void ViewAbstract::SetMaxHeight(const CalcLength& height)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateCalcMaxSize(CalcSize(std::nullopt, height));
}

void ViewAbstract::SetAspectRatio(float ratio)
{
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, AspectRatio, ratio);
}

void ViewAbstract::SetBackgroundColor(const Color& color)
{
    ACE_UPDATE_RENDER_CONTEXT(BackgroundColor, color);
}

void ViewAbstract::SetBackgroundImage(const std::string& src)
{
    ImageSourceInfo imageSourceInfo(src);
    ACE_UPDATE_RENDER_CONTEXT(BackgroundImage, imageSourceInfo);
}

void ViewAbstract::SetBackgroundImageRepeat(const ImageRepeat& imageRepeat)
{
    ACE_UPDATE_RENDER_CONTEXT(BackgroundImageRepeat, imageRepeat);
}

void ViewAbstract::SetBackgroundImageSize(const BackgroundImageSize& bgImgSize)
{
    ACE_UPDATE_RENDER_CONTEXT(BackgroundImageSize, bgImgSize);
}

void ViewAbstract::SetBackgroundImagePosition(const BackgroundImagePosition& bgImgPosition)
{
    ACE_UPDATE_RENDER_CONTEXT(BackgroundImagePosition, bgImgPosition);
}

void ViewAbstract::SetBackgroundBlurStyle(const BlurStyle& bgBlurStyle)
{
    ACE_UPDATE_RENDER_CONTEXT(BackgroundBlurStyle, bgBlurStyle);
}

void ViewAbstract::SetLayoutWeight(int32_t value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, LayoutWeight, static_cast<float>(value));
}

void ViewAbstract::SetLayoutDirection(TextDirection value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, LayoutDirection, value);
}

void ViewAbstract::SetAlignRules(const std::map<AlignDirection, AlignRule>& alignRules)
{
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, AlignRules, alignRules);
}

void ViewAbstract::SetAlignSelf(int32_t value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, AlignSelf, static_cast<FlexAlign>(value));
}

void ViewAbstract::SetFlexShrink(float value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, FlexShrink, value);
}

void ViewAbstract::SetFlexGrow(float value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, FlexGrow, value);
}

void ViewAbstract::SetFlexBasis(const Dimension& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, FlexBasis, value);
}

void ViewAbstract::SetDisplayIndex(int32_t value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, DisplayIndex, value);
}

void ViewAbstract::SetPadding(const CalcLength& value)
{
    PaddingProperty padding;
    padding.SetEdges(value);
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, Padding, padding);
}

void ViewAbstract::SetPadding(const PaddingProperty& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, Padding, value);
}

void ViewAbstract::SetMargin(const CalcLength& value)
{
    MarginProperty margin;
    margin.SetEdges(value);
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, Margin, margin);
}

void ViewAbstract::SetMargin(const MarginProperty& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, Margin, value);
}

void ViewAbstract::SetBorderRadius(const Dimension& value)
{
    BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(value);
    ACE_UPDATE_RENDER_CONTEXT(BorderRadius, borderRadius);
}

void ViewAbstract::SetBorderRadius(const BorderRadiusProperty& value)
{
    ACE_UPDATE_RENDER_CONTEXT(BorderRadius, value);
}

void ViewAbstract::SetBorderColor(const Color& value)
{
    BorderColorProperty borderColor;
    borderColor.SetColor(value);
    ACE_UPDATE_RENDER_CONTEXT(BorderColor, borderColor);
}

void ViewAbstract::SetBorderColor(const BorderColorProperty& value)
{
    ACE_UPDATE_RENDER_CONTEXT(BorderColor, value);
}

void ViewAbstract::SetBorderWidth(const Dimension& value)
{
    BorderWidthProperty borderWidth;
    borderWidth.SetBorderWidth(value);
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, BorderWidth, borderWidth);
}

void ViewAbstract::SetBorderWidth(const BorderWidthProperty& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, BorderWidth, value);
}

void ViewAbstract::SetBorderStyle(const BorderStyle& value)
{
    BorderStyleProperty borderStyle;
    borderStyle.SetBorderStyle(value);
    ACE_UPDATE_RENDER_CONTEXT(BorderStyle, borderStyle);
}

void ViewAbstract::SetBorderStyle(const BorderStyleProperty& value)
{
    ACE_UPDATE_RENDER_CONTEXT(BorderStyle, value);
}

void ViewAbstract::SetOnClick(GestureEventFunc&& clickEventFunc)
{
    auto gestureHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->SetClickEvent(std::move(clickEventFunc));
}

void ViewAbstract::SetOnTouch(TouchEventFunc&& touchEventFunc)
{
    auto gestureHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->SetTouchEvent(std::move(touchEventFunc));
}

void ViewAbstract::SetOnMouse(OnMouseEventFunc&& onMouseEventFunc)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeInputEventHub();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetMouseEvent(std::move(onMouseEventFunc));
}

void ViewAbstract::SetOnHover(OnHoverEventFunc&& onHoverEventFunc)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeInputEventHub();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetHoverEvent(std::move(onHoverEventFunc));
}

void ViewAbstract::SetHoverEffect(HoverEffectType hoverEffect)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeInputEventHub();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetHoverAnimation(hoverEffect);
}

void ViewAbstract::SetEnabled(bool enabled)
{
    auto focusHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->SetEnabled(enabled);
}

void ViewAbstract::SetFocusable(bool focusable)
{
    auto focusHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->SetFocusable(focusable);
}

void ViewAbstract::SetOnFocus(OnFocusFunc&& onFocusCallback)
{
    auto focusHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->SetOnFocusCallback(std::move(onFocusCallback));
}

void ViewAbstract::SetOnBlur(OnBlurFunc&& onBlurCallback)
{
    auto focusHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->SetOnBlurCallback(std::move(onBlurCallback));
}

void ViewAbstract::SetOnKeyEvent(OnKeyCallbackFunc&& onKeyCallback)
{
    auto focusHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->SetOnKeyCallback(std::move(onKeyCallback));
}

void ViewAbstract::SetTabIndex(int32_t index)
{
    auto focusHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->SetTabIndex(index);
}

void ViewAbstract::SetFocusOnTouch(bool isSet)
{
    auto focusHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->SetIsFocusOnTouch(isSet);
}

void ViewAbstract::SetDefaultFocus(bool isSet)
{
    auto focusHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->SetIsDefaultFocus(isSet);
}

void ViewAbstract::SetGroupDefaultFocus(bool isSet)
{
    auto focusHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->SetIsDefaultGroupFocus(isSet);
}

void ViewAbstract::SetOnAppear(std::function<void()>&& onAppear)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnAppear(std::move(onAppear));
}

void ViewAbstract::SetOnDisappear(std::function<void()>&& onDisappear)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnDisappear(std::move(onDisappear));
}

void ViewAbstract::SetOnAreaChanged(
    std::function<void(const RectF& oldRect, const OffsetF& oldOrigin, const RectF& rect, const OffsetF& origin)>&&
        onAreaChanged)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnAreaChanged(std::move(onAreaChanged));
}

void ViewAbstract::SetResponseRegion(const std::vector<DimensionRect>& responseRegion)
{
    auto gestureHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->MarkResponseRegion(true);
    gestureHub->SetResponseRegion(responseRegion);
}

void ViewAbstract::SetTouchable(bool touchable)
{
    auto gestureHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->SetTouchable(touchable);
}

void ViewAbstract::SetHitTestMode(HitTestMode hitTestMode)
{
    auto gestureHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->SetHitTestMode(hitTestMode);
}

void ViewAbstract::AddDragFrameNodeToManager()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);

    dragDropManager->AddDragFrameNode(AceType::WeakClaim(AceType::RawPtr(frameNode)));
}

void ViewAbstract::SetOnDragStart(
    std::function<DragDropInfo(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&)>&& onDragStart)
{
    auto gestureHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->InitDragDropEvent();

    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnDragStart(std::move(onDragStart));

    AddDragFrameNodeToManager();
}

void ViewAbstract::SetOnDragEnter(
    std::function<void(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&)>&& onDragEnter)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnDragEnter(std::move(onDragEnter));

    AddDragFrameNodeToManager();
}

void ViewAbstract::SetOnDragLeave(
    std::function<void(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&)>&& onDragLeave)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnDragLeave(std::move(onDragLeave));

    AddDragFrameNodeToManager();
}

void ViewAbstract::SetOnDragMove(
    std::function<void(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&)>&& onDragMove)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnDragMove(std::move(onDragMove));

    AddDragFrameNodeToManager();
}

void ViewAbstract::SetOnDrop(std::function<void(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&)>&& onDrop)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnDrop(std::move(onDrop));

    AddDragFrameNodeToManager();
}

void ViewAbstract::SetAlign(Alignment alignment)
{
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, Alignment, alignment);
}

void ViewAbstract::SetVisibility(VisibleType visible)
{
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, Visibility, visible);
}

void ViewAbstract::SetOpacity(double opacity)
{
    ACE_UPDATE_RENDER_CONTEXT(Opacity, opacity);
}

void ViewAbstract::SetPosition(const OffsetT<Dimension>& value)
{
    ACE_UPDATE_RENDER_CONTEXT(Position, value);
}

void ViewAbstract::SetOffset(const OffsetT<Dimension>& value)
{
    ACE_UPDATE_RENDER_CONTEXT(Offset, value);
}

void ViewAbstract::MarkAnchor(const OffsetT<Dimension>& value)
{
    ACE_UPDATE_RENDER_CONTEXT(Anchor, value);
}

void ViewAbstract::SetZIndex(int32_t value)
{
    ACE_UPDATE_RENDER_CONTEXT(ZIndex, value);
}

void ViewAbstract::SetScale(const NG::VectorF& value)
{
    ACE_UPDATE_RENDER_CONTEXT(TransformScale, value);
}

void ViewAbstract::SetPivot(const DimensionOffset& value)
{
    ACE_UPDATE_RENDER_CONTEXT(TransformCenter, value);
}

void ViewAbstract::SetTranslate(const NG::Vector3F& value)
{
    ACE_UPDATE_RENDER_CONTEXT(TransformTranslate, value);
}

void ViewAbstract::SetRotate(const NG::Vector4F& value)
{
    ACE_UPDATE_RENDER_CONTEXT(TransformRotate, value);
}

void ViewAbstract::SetTransformMatrix(const Matrix4& matrix)
{
    ACE_UPDATE_RENDER_CONTEXT(TransformMatrix, matrix);
}

void ViewAbstract::BindPopup(const RefPtr<PopupParam>& param)
{
    auto msg = param->GetMessage();
    auto isShow = param->IsShow();
    LOGI("ViewAbstract::BindPopup, msg is %{public}s", msg.c_str());
    auto targetNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(targetNode);
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    CHECK_NULL_VOID(context);
    auto overlayManager = context->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    auto popupInfo = overlayManager->GetPopupInfo(targetId);
    if (popupInfo.isCurrentOnShow == isShow) {
        LOGI("No need to change popup show flag.");
        return;
    }
    popupInfo.markNeedUpdate = true;
    auto popupId = popupInfo.popupId;
    auto popupNode = popupInfo.popupNode;
    // Create new popup.
    if (popupInfo.popupId == -1 || !popupNode) {
        popupNode = BubbleView::CreateBubbleNode(targetTag, targetId, param);
        popupId = popupNode->GetId();
    } else {
        // TODO: update is not completed.
        LOGI("Update pop node.");
    }
    // update PopupInfo props
    popupInfo.popupId = popupId;
    popupInfo.markNeedUpdate = isShow;
    popupInfo.popupNode = popupNode;
    popupNode->MarkModifyDone();
    popupInfo.target = AceType::WeakClaim(AceType::RawPtr(targetNode));
    overlayManager->UpdatePopupNode(targetId, popupInfo);
}

// common function to bind menu
void BindMenu(const RefPtr<FrameNode> menuNode, int32_t targetId)
{
    LOGD("ViewAbstract::BindMenu");
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    CHECK_NULL_VOID(context);
    auto overlayManager = context->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);

    // pass in menuNode to register it in OverlayManager
    overlayManager->ShowMenu(targetId, menuNode);
    LOGD("ViewAbstract BindMenu finished %{public}p", AceType::RawPtr(menuNode));
}

void ViewAbstract::BindMenuWithItems(const std::vector<OptionParam>& params, const RefPtr<FrameNode>& targetNode)
{
    CHECK_NULL_VOID(targetNode);

    if (params.empty()) {
        LOGD("menu params is empty");
        return;
    }
    auto menuNode = MenuView::Create(params, targetNode->GetTag(), targetNode->GetId());
    BindMenu(menuNode, targetNode->GetId());
}

void ViewAbstract::BindMenuWithCustomNode(const RefPtr<UINode>& customNode, const RefPtr<FrameNode>& targetNode)
{
    LOGD("ViewAbstract::BindMenuWithCustomNode");
    CHECK_NULL_VOID(customNode);
    CHECK_NULL_VOID(targetNode);

    auto menuNode = MenuView::Create(customNode, targetNode->GetTag(), targetNode->GetId());
    BindMenu(menuNode, targetNode->GetId());
}

void ViewAbstract::ShowMenu(int32_t targetId)
{
    LOGD("ViewAbstract::ShowMenu");
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    CHECK_NULL_VOID(context);
    auto overlayManager = context->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);

    overlayManager->ShowMenu(targetId);
}

void ViewAbstract::SetBackdropBlur(const Dimension& radius)
{
    ACE_UPDATE_RENDER_CONTEXT(BackBlurRadius, radius);
}

void ViewAbstract::SetFrontBlur(const Dimension& radius)
{
    ACE_UPDATE_RENDER_CONTEXT(FrontBlurRadius, radius);
}

void ViewAbstract::SetBackShadow(const Shadow& shadow)
{
    ACE_UPDATE_RENDER_CONTEXT(BackShadow, shadow);
}

void ViewAbstract::SetLinearGradient(const NG::Gradient& gradient)
{
    ACE_UPDATE_RENDER_CONTEXT(LinearGradient, gradient);
}

void ViewAbstract::SetSweepGradient(const NG::Gradient& gradient)
{
    ACE_UPDATE_RENDER_CONTEXT(SweepGradient, gradient);
}

void ViewAbstract::SetRadialGradient(const NG::Gradient& gradient)
{
    ACE_UPDATE_RENDER_CONTEXT(RadialGradient, gradient);
}

void ViewAbstract::SetInspectorId(const std::string& inspectorId)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    frameNode->UpdateInspectorId(inspectorId);
}

void ViewAbstract::SetGrid(std::optional<uint32_t> span, std::optional<int32_t> offset, GridSizeType type)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    // frame node is mounted to parent when pop from stack later, no grid-container is added here
    layoutProperty->UpdateGridProperty(span, offset, type);
}

void ViewAbstract::Pop()
{
    ViewStackProcessor::GetInstance()->Pop();
}

void ViewAbstract::SetTransition(const TransitionOptions& options)
{
    ACE_UPDATE_RENDER_CONTEXT(Transition, options);
}

void ViewAbstract::SetClipPath(const ClipPathNG& clipPath)
{
    ACE_UPDATE_RENDER_CONTEXT(ClipShape, clipPath);
}

void ViewAbstract::SetEdgeClip(bool isClip)
{
    ACE_UPDATE_RENDER_CONTEXT(ClipEdge, isClip);
}

void ViewAbstract::SetBrightness(const Dimension& brightness)
{
    ACE_UPDATE_RENDER_CONTEXT(FrontBrightness, brightness);
}

void ViewAbstract::SetGrayScale(const Dimension& grayScale)
{
    ACE_UPDATE_RENDER_CONTEXT(FrontGrayScale, grayScale);
}

void ViewAbstract::SetContrast(const Dimension& contrast)
{
    ACE_UPDATE_RENDER_CONTEXT(FrontContrast, contrast);
}

void ViewAbstract::SetSaturate(const Dimension& saturate)
{
    ACE_UPDATE_RENDER_CONTEXT(FrontSaturate, saturate);
}

void ViewAbstract::SetSepia(const Dimension& sepia)
{
    ACE_UPDATE_RENDER_CONTEXT(FrontSepia, sepia);
}

void ViewAbstract::SetInvert(const Dimension& invert)
{
    ACE_UPDATE_RENDER_CONTEXT(FrontInvert, invert);
}

void ViewAbstract::SetHueRotate(float hueRotate)
{
    ACE_UPDATE_RENDER_CONTEXT(FrontHueRotate, hueRotate);
}

void ViewAbstract::SetColorBlend(const Color& colorBlend)
{
    ACE_UPDATE_RENDER_CONTEXT(FrontColorBlend, colorBlend);
}

void ViewAbstract::SetBorderImage(const RefPtr<BorderImage>& borderImage)
{
    ACE_UPDATE_RENDER_CONTEXT(BorderImage, borderImage);
}

void ViewAbstract::SetBorderImageSource(const std::string& bdImageSrc)
{
    ImageSourceInfo imageSourceInfo(bdImageSrc);
    ACE_UPDATE_RENDER_CONTEXT(BorderImageSource, imageSourceInfo);
}

void ViewAbstract::SetHasBorderImageSlice(bool tag)
{
    ACE_UPDATE_RENDER_CONTEXT(HasBorderImageSlice, tag);
}

void ViewAbstract::SetHasBorderImageWidth(bool tag)
{
    ACE_UPDATE_RENDER_CONTEXT(HasBorderImageWidth, tag);
}

void ViewAbstract::SetHasBorderImageOutset(bool tag)
{
    ACE_UPDATE_RENDER_CONTEXT(HasBorderImageOutset, tag);
}

void ViewAbstract::SetHasBorderImageRepeat(bool tag)
{
    ACE_UPDATE_RENDER_CONTEXT(HasBorderImageRepeat, tag);
}

void ViewAbstract::SetBorderImageGradient(const Gradient& gradient)
{
    ACE_UPDATE_RENDER_CONTEXT(BorderImageGradient, gradient);
}

} // namespace OHOS::Ace::NG
