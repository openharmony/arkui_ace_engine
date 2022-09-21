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

#include <optional>
#include <utility>

#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/bubble/bubble_view.h"
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

void ViewAbstract::SetAlignSelf(int32_t value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, AlignSelf, static_cast<FlexAlign>(value));
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

void ViewAbstract::SetHoverEffect(HoverEffectType hoverEffect)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeInputEventHub();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetHoverAnimation(hoverEffect);
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

void ViewAbstract::SetBackdropBlur(const Dimension& radius)
{
    ACE_UPDATE_RENDER_CONTEXT(BackBlurRadius, radius);
}

void ViewAbstract::SetInspectorId(const std::string& inspectorId)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    frameNode->UpdateInspectorId(inspectorId);
}

void ViewAbstract::Pop()
{
    ViewStackProcessor::GetInstance()->Pop();
}
} // namespace OHOS::Ace::NG
