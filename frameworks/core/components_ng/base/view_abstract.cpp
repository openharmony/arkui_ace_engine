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

#include "core/components_ng/base/view_abstract.h"

#include <cstdint>
#include <optional>
#include <utility>

#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/memory/ace_type.h"
#include "base/utils/system_properties.h"
#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/bubble/bubble_pattern.h"
#include "core/components_ng/pattern/bubble/bubble_view.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/menu/menu_view.h"
#include "core/components_ng/pattern/menu/preview/menu_preview_pattern.h"
#include "core/components_ng/pattern/option/option_paint_property.h"
#include "core/components_ng/pattern/text/span_node.h"
#include "core/components_ng/property/border_property.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/property/safe_area_insets.h"
#include "core/image/image_source_info.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {

namespace {

// common function to bind menu
void BindMenu(const RefPtr<FrameNode>& menuNode, int32_t targetId, const NG::OffsetF& offset)
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
    overlayManager->ShowMenu(targetId, offset, menuNode);
    LOGD("ViewAbstract BindMenu finished %{public}d", menuNode->GetId());
}
} // namespace

void ViewAbstract::SetWidth(const CalcLength& width)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    // get previously user defined ideal height
    std::optional<CalcLength> height = std::nullopt;
    auto&& layoutConstraint = layoutProperty->GetCalcLayoutConstraint();
    if (layoutConstraint && layoutConstraint->selfIdealSize) {
        height = layoutConstraint->selfIdealSize->Height();
    }
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(width, height));
}

void ViewAbstract::SetHeight(const CalcLength& height)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    // get previously user defined ideal width
    std::optional<CalcLength> width = std::nullopt;
    auto&& layoutConstraint = layoutProperty->GetCalcLayoutConstraint();
    if (layoutConstraint && layoutConstraint->selfIdealSize) {
        width = layoutConstraint->selfIdealSize->Width();
    }
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(width, height));
}

void ViewAbstract::SetClickEffectLevel(const ClickEffectLevel& level, float scaleValue)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ClickEffectInfo clickEffectInfo;
    clickEffectInfo.level = level;
    clickEffectInfo.scaleNumber = scaleValue;
    ACE_UPDATE_RENDER_CONTEXT(ClickEffectLevel, clickEffectInfo);
}

void ViewAbstract::ClearWidthOrHeight(bool isWidth)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->ClearUserDefinedIdealSize(isWidth, !isWidth);
}

void ViewAbstract::SetMinWidth(const CalcLength& width)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateCalcMinSize(CalcSize(width, std::nullopt));
}

void ViewAbstract::SetMinHeight(const CalcLength& height)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateCalcMinSize(CalcSize(std::nullopt, height));
}

void ViewAbstract::ResetMinSize(bool resetWidth)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->ResetCalcMinSize(resetWidth);
}

void ViewAbstract::SetMaxWidth(const CalcLength& width)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateCalcMaxSize(CalcSize(width, std::nullopt));
}

void ViewAbstract::SetMaxHeight(const CalcLength& height)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateCalcMaxSize(CalcSize(std::nullopt, height));
}

void ViewAbstract::ResetMaxSize(bool resetWidth)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->ResetCalcMaxSize(resetWidth);
}

void ViewAbstract::SetAspectRatio(float ratio)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, AspectRatio, ratio);
}

void ViewAbstract::ResetAspectRatio()
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_RESET_LAYOUT_PROPERTY(LayoutProperty, AspectRatio);
}

void ViewAbstract::SetBackgroundAlign(const Alignment& align)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(BackgroundAlign, align);
}

void ViewAbstract::SetBackgroundColor(const Color& color)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(BackgroundColor, color);
}

void ViewAbstract::SetBackgroundImage(const ImageSourceInfo& src)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(BackgroundImage, src);
}

void ViewAbstract::SetBackgroundImageRepeat(const ImageRepeat& imageRepeat)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(BackgroundImageRepeat, imageRepeat);
}

void ViewAbstract::SetBackgroundImageSize(const BackgroundImageSize& bgImgSize)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(BackgroundImageSize, bgImgSize);
}

void ViewAbstract::SetBackgroundImagePosition(const BackgroundImagePosition& bgImgPosition)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(BackgroundImagePosition, bgImgPosition);
}

void ViewAbstract::SetBackgroundBlurStyle(const BlurStyleOption& bgBlurStyle)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto target = frameNode->GetRenderContext();
    if (target) {
        if (target->GetBackgroundEffect().has_value()) {
            target->UpdateBackgroundEffect(std::nullopt);
        }
        target->UpdateBackBlurStyle(bgBlurStyle);
        if (target->GetBackBlurRadius().has_value()) {
            target->UpdateBackBlurRadius(Dimension());
        }
    }
}

void ViewAbstract::SetBackgroundEffect(const EffectOption& effectOption)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto target = frameNode->GetRenderContext();
    if (target) {
        if (target->GetBackBlurRadius().has_value()) {
            target->UpdateBackBlurRadius(Dimension());
        }
        if (target->GetBackBlurStyle().has_value()) {
            target->UpdateBackBlurStyle(std::nullopt);
        }
        target->UpdateBackgroundEffect(effectOption);
    }
}

void ViewAbstract::SetForegroundBlurStyle(const BlurStyleOption& fgBlurStyle)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto target = frameNode->GetRenderContext();
    if (target) {
        target->UpdateFrontBlurStyle(fgBlurStyle);
        if (target->GetFrontBlurRadius().has_value()) {
            target->UpdateFrontBlurRadius(Dimension());
        }
    }
}

void ViewAbstract::SetSphericalEffect(double radio)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(SphericalEffect, radio);
}

void ViewAbstract::SetPixelStretchEffect(PixStretchEffectOption& option)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(PixelStretchEffect, option);
}

void ViewAbstract::SetLightUpEffect(double radio)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(LightUpEffect, radio);
}

void ViewAbstract::SetLayoutWeight(int32_t value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, LayoutWeight, static_cast<float>(value));
}

void ViewAbstract::SetLayoutDirection(TextDirection value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, LayoutDirection, value);
}

void ViewAbstract::SetAlignRules(const std::map<AlignDirection, AlignRule>& alignRules)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, AlignRules, alignRules);
}

void ViewAbstract::SetAlignSelf(FlexAlign value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, AlignSelf, value);
}

void ViewAbstract::SetFlexShrink(float value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, FlexShrink, value);
}

void ViewAbstract::ResetFlexShrink()
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_RESET_LAYOUT_PROPERTY(LayoutProperty, FlexShrink);
}

void ViewAbstract::SetFlexGrow(float value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, FlexGrow, value);
}

void ViewAbstract::SetFlexBasis(const Dimension& value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    if (LessNotEqual(value.Value(), 0.0f)) {
        ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, FlexBasis, Dimension());
        return;
    }
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, FlexBasis, value);
}

void ViewAbstract::SetDisplayIndex(int32_t value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, DisplayIndex, value);
}

void ViewAbstract::SetPadding(const CalcLength& value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    PaddingProperty padding;
    padding.SetEdges(value);
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, Padding, padding);
}

void ViewAbstract::SetPadding(const PaddingProperty& value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, Padding, value);
}

void ViewAbstract::SetMargin(const CalcLength& value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    MarginProperty margin;
    margin.SetEdges(value);
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, Margin, margin);
}

void ViewAbstract::SetMargin(const MarginProperty& value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, Margin, value);
}

void ViewAbstract::SetBorderRadius(const Dimension& value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(value);
    borderRadius.multiValued = false;
    ACE_UPDATE_RENDER_CONTEXT(BorderRadius, borderRadius);
}

void ViewAbstract::SetBorderRadius(const BorderRadiusProperty& value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(BorderRadius, value);
}

void ViewAbstract::SetBorderColor(const Color& value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    BorderColorProperty borderColor;
    borderColor.SetColor(value);
    ACE_UPDATE_RENDER_CONTEXT(BorderColor, borderColor);
}

void ViewAbstract::SetBorderColor(const BorderColorProperty& value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(BorderColor, value);
}

void ViewAbstract::SetBorderWidth(const Dimension& value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    BorderWidthProperty borderWidth;
    if (Negative(value.Value())) {
        borderWidth.SetBorderWidth(Dimension(0));
        LOGW("border width is negative, reset to 0");
    } else {
        borderWidth.SetBorderWidth(value);
    }
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, BorderWidth, borderWidth);
    ACE_UPDATE_RENDER_CONTEXT(BorderWidth, borderWidth);
}

void ViewAbstract::SetBorderWidth(const BorderWidthProperty& value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, BorderWidth, value);
    ACE_UPDATE_RENDER_CONTEXT(BorderWidth, value);
}

void ViewAbstract::SetBorderStyle(const BorderStyle& value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    BorderStyleProperty borderStyle;
    borderStyle.SetBorderStyle(value);
    ACE_UPDATE_RENDER_CONTEXT(BorderStyle, borderStyle);
}

void ViewAbstract::SetBorderStyle(const BorderStyleProperty& value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(BorderStyle, value);
}

void ViewAbstract::DisableOnClick()
{
    LOGD("Disable OnClick event");
    auto gestureHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->ClearUserOnClick();
}

void ViewAbstract::DisableOnTouch()
{
    LOGD("Disable OnTouch event");
    auto gestureHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->ClearUserOnTouch();
}

void ViewAbstract::DisableOnKeyEvent()
{
    LOGD("Disable OnKey event");
    auto focusHub = ViewStackProcessor::GetInstance()->GetOrCreateMainFrameNodeFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->ClearUserOnKey();
}

void ViewAbstract::DisableOnHover()
{
    LOGD("Disable OnHover event");
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeInputEventHub();
    CHECK_NULL_VOID(eventHub);
    eventHub->ClearUserOnHover();
}

void ViewAbstract::DisableOnMouse()
{
    LOGD("Disable OnMouse event");
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeInputEventHub();
    CHECK_NULL_VOID(eventHub);
    eventHub->ClearUserOnMouse();
}

void ViewAbstract::DisableOnAppear()
{
    LOGD("Disable OnAppear event");
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->ClearUserOnAppear();
}

void ViewAbstract::DisableOnDisAppear()
{
    LOGD("Disable OnDisAppear event");
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->ClearUserOnDisAppear();
}

void ViewAbstract::DisableOnAreaChange()
{
    LOGD("Disable OnAreaChange event");
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    frameNode->ClearUserOnAreaChange();
}

void ViewAbstract::DisableOnFocus()
{
    LOGD("Disable OnFocus event");
    auto focusHub = ViewStackProcessor::GetInstance()->GetOrCreateMainFrameNodeFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->ClearUserOnFocus();
}

void ViewAbstract::DisableOnBlur()
{
    LOGD("Disable OnBlur event");
    auto focusHub = ViewStackProcessor::GetInstance()->GetOrCreateMainFrameNodeFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->ClearUserOnBlur();
}

void ViewAbstract::SetOnClick(GestureEventFunc&& clickEventFunc)
{
    auto gestureHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->SetUserOnClick(std::move(clickEventFunc));
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

void ViewAbstract::SetOnHover(OnHoverFunc&& onHoverEventFunc)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeInputEventHub();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetHoverEvent(std::move(onHoverEventFunc));
}

void ViewAbstract::SetHoverEffect(HoverEffectType hoverEffect)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeInputEventHub();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetHoverEffect(hoverEffect);
}

void ViewAbstract::SetHoverEffectAuto(HoverEffectType hoverEffect)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeInputEventHub();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetHoverEffectAuto(hoverEffect);
}

void ViewAbstract::SetEnabled(bool enabled)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<EventHub>();
    if (eventHub) {
        eventHub->SetEnabled(enabled);
    }

    // The SetEnabled of focusHub must be after at eventHub
    auto focusHub = ViewStackProcessor::GetInstance()->GetOrCreateMainFrameNodeFocusHub();
    if (focusHub) {
        focusHub->SetEnabled(enabled);
    }
}

void ViewAbstract::SetFocusable(bool focusable)
{
    auto focusHub = ViewStackProcessor::GetInstance()->GetOrCreateMainFrameNodeFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->SetFocusable(focusable);
}

void ViewAbstract::SetOnFocus(OnFocusFunc&& onFocusCallback)
{
    auto focusHub = ViewStackProcessor::GetInstance()->GetOrCreateMainFrameNodeFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->SetOnFocusCallback(std::move(onFocusCallback));
}

void ViewAbstract::SetOnBlur(OnBlurFunc&& onBlurCallback)
{
    auto focusHub = ViewStackProcessor::GetInstance()->GetOrCreateMainFrameNodeFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->SetOnBlurCallback(std::move(onBlurCallback));
}

void ViewAbstract::SetOnKeyEvent(OnKeyCallbackFunc&& onKeyCallback)
{
    auto focusHub = ViewStackProcessor::GetInstance()->GetOrCreateMainFrameNodeFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->SetOnKeyCallback(std::move(onKeyCallback));
}

void ViewAbstract::SetTabIndex(int32_t index)
{
    auto focusHub = ViewStackProcessor::GetInstance()->GetOrCreateMainFrameNodeFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->SetTabIndex(index);
}

void ViewAbstract::SetFocusOnTouch(bool isSet)
{
    auto focusHub = ViewStackProcessor::GetInstance()->GetOrCreateMainFrameNodeFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->SetIsFocusOnTouch(isSet);
}

void ViewAbstract::SetDefaultFocus(bool isSet)
{
    auto focusHub = ViewStackProcessor::GetInstance()->GetOrCreateMainFrameNodeFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->SetIsDefaultFocus(isSet);
}

void ViewAbstract::SetGroupDefaultFocus(bool isSet)
{
    auto focusHub = ViewStackProcessor::GetInstance()->GetOrCreateMainFrameNodeFocusHub();
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
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    frameNode->SetOnAreaChangeCallback(std::move(onAreaChanged));
    pipeline->AddOnAreaChangeNode(frameNode->GetId());
}

void ViewAbstract::SetOnVisibleChange(
    std::function<void(bool, double)>&& onVisibleChange, const std::vector<double>& ratioList)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    frameNode->ClearVisibleAreaUserCallback();

    for (const auto& ratio : ratioList) {
        pipeline->AddVisibleAreaChangeNode(frameNode, ratio, onVisibleChange);
    }
}

void ViewAbstract::SetResponseRegion(const std::vector<DimensionRect>& responseRegion)
{
    auto gestureHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->MarkResponseRegion(true);
    gestureHub->SetResponseRegion(responseRegion);
}

void ViewAbstract::SetMouseResponseRegion(const std::vector<DimensionRect>& mouseRegion)
{
    auto gestureHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->MarkResponseRegion(true);
    gestureHub->SetMouseResponseRegion(mouseRegion);
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

    dragDropManager->AddDragFrameNode(frameNode->GetId(), AceType::WeakClaim(AceType::RawPtr(frameNode)));
}

void ViewAbstract::SetDraggable(bool draggable)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto gestureHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    if (draggable) {
        if (!frameNode->IsDraggable()) {
            gestureHub->InitDragDropEvent();
        }
    } else {
        gestureHub->RemoveDragEvent();
    }
    frameNode->SetDraggable(draggable);
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

void ViewAbstract::SetOnDragEnd(std::function<void(const RefPtr<OHOS::Ace::DragEvent>&)>&& onDragEnd)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnDragEnd(std::move(onDragEnd));

    AddDragFrameNodeToManager();
}

void ViewAbstract::SetAlign(Alignment alignment)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, Alignment, alignment);
}

void ViewAbstract::SetVisibility(VisibleType visible)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty();
    if (layoutProperty) {
        layoutProperty->UpdateVisibility(visible, true);
    }

    auto focusHub = ViewStackProcessor::GetInstance()->GetOrCreateMainFrameNodeFocusHub();
    if (focusHub) {
        focusHub->SetShow(visible == VisibleType::VISIBLE);
    }
}

void ViewAbstract::SetGeometryTransition(const std::string& id, bool followWithoutTransition)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty();
    if (layoutProperty) {
        layoutProperty->UpdateGeometryTransition(id, followWithoutTransition);
    }
}

void ViewAbstract::SetOpacity(double opacity)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(Opacity, opacity);
}
void ViewAbstract::SetAllowDrop(const std::set<std::string>& allowDrop)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    frameNode->SetAllowDrop(allowDrop);
}

void ViewAbstract::SetPosition(const OffsetT<Dimension>& value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(Position, value);
}

void ViewAbstract::SetOffset(const OffsetT<Dimension>& value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(Offset, value);
}

void ViewAbstract::MarkAnchor(const OffsetT<Dimension>& value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(Anchor, value);
}

void ViewAbstract::SetZIndex(int32_t value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(ZIndex, value);
}

void ViewAbstract::SetScale(const NG::VectorF& value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(TransformScale, value);
}

void ViewAbstract::SetPivot(const DimensionOffset& value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(TransformCenter, value);
}

void ViewAbstract::SetTranslate(const NG::TranslateOptions& value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(TransformTranslate, value);
}

void ViewAbstract::SetRotate(const NG::Vector5F& value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(TransformRotate, value);
}

void ViewAbstract::SetTransformMatrix(const Matrix4& matrix)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(TransformMatrix, matrix);
}

void ViewAbstract::BindPopup(
    const RefPtr<PopupParam>& param, const RefPtr<FrameNode>& targetNode, const RefPtr<UINode>& customNode)
{
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
    auto isShow = param->IsShow();
    auto isUseCustom = param->IsUseCustom();
    auto showInSubWindow = param->IsShowInSubWindow();
    // subwindow model needs to use subContainer to get popupInfo
    if (showInSubWindow) {
        auto subwindow = SubwindowManager::GetInstance()->GetSubwindow(Container::CurrentId());
        if (subwindow) {
            subwindow->GetPopupInfoNG(targetId, popupInfo);
        }
    }

    auto popupId = popupInfo.popupId;
    auto popupNode = popupInfo.popupNode;
    RefPtr<BubblePattern> popupPattern;
    if (popupNode) {
        popupPattern = popupNode->GetPattern<BubblePattern>();
    }

    if (popupInfo.isCurrentOnShow) {
        // Entering / Normal / Exiting
        bool popupShowing = popupPattern ? popupPattern->IsOnShow() : false;
        if (popupShowing == isShow) {
            LOGI("No need to change popup show flag, current show %{public}d", isShow);
            return;
        }
        if (!popupShowing && isShow) {
            popupInfo.markNeedUpdate = false;
        } else {
            popupInfo.markNeedUpdate = true;
        }
    } else {
        // Invisable
        if (!isShow) {
            LOGI("No need to change popup show flag, current show %{public}d", isShow);
            return;
        }
        popupInfo.markNeedUpdate = true;
    }

    // Create new popup.
    if (popupInfo.popupId == -1 || !popupNode) {
        if (!isUseCustom) {
            popupNode = BubbleView::CreateBubbleNode(targetTag, targetId, param);
        } else {
            CHECK_NULL_VOID(customNode);
            popupNode = BubbleView::CreateCustomBubbleNode(targetTag, targetId, customNode, param);
        }
        if (popupNode) {
            popupId = popupNode->GetId();
        }
    } else {
        // use param to update PopupParm
        if (!isUseCustom) {
            BubbleView::UpdatePopupParam(popupId, param, targetNode);
            popupNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
            LOGI("Update normal Popup node.");
        } else {
            BubbleView::UpdateCustomPopupParam(popupId, param);
            popupNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
            LOGI("Update Custom Popup node.");
        }
    }
    // update PopupInfo props
    popupInfo.popupId = popupId;
    popupInfo.popupNode = popupNode;
    popupInfo.isBlockEvent = param->IsBlockEvent();
    if (popupNode) {
        popupNode->MarkModifyDone();
        popupPattern = popupNode->GetPattern<BubblePattern>();
    }
    popupInfo.target = AceType::WeakClaim(AceType::RawPtr(targetNode));
    popupInfo.targetSize = SizeF(param->GetTargetSize().Width(), param->GetTargetSize().Height());
    popupInfo.targetOffset = OffsetF(param->GetTargetOffset().GetX(), param->GetTargetOffset().GetY());
    if (showInSubWindow) {
        if (isShow) {
            LOGI("Popup now show in subwindow.");
            SubwindowManager::GetInstance()->ShowPopupNG(targetId, popupInfo);
            if (popupPattern) {
                popupPattern->SetContainerId(Container::CurrentId());
                popupPattern->StartEnteringAnimation(nullptr);
            }
        } else {
            if (popupPattern) {
                popupPattern->StartExitingAnimation([targetId]() {
                    LOGI("Popup now hide in subwindow.");
                    SubwindowManager::GetInstance()->HidePopupNG(targetId);
                });
            }
        }
        return;
    }
    auto destroyCallback = [weakOverlayManger = AceType::WeakClaim(AceType::RawPtr(overlayManager)), targetId]() {
        auto overlay = weakOverlayManger.Upgrade();
        CHECK_NULL_VOID(overlay);
        overlay->ErasePopup(targetId);
    };
    targetNode->PushDestroyCallback(destroyCallback);
    if (!popupInfo.isCurrentOnShow) {
        targetNode->OnAccessibilityEvent(
            AccessibilityEventType::CHANGE, WindowsContentChangeTypes::CONTENT_CHANGE_TYPE_SUBTREE);
    }
    if (isShow) {
        LOGI("begin to update popup node.");
        overlayManager->UpdatePopupNode(targetId, popupInfo);
        if (popupPattern) {
            popupPattern->StartEnteringAnimation(nullptr);
        }
    } else {
        if (popupPattern) {
            popupPattern->StartExitingAnimation(
                [targetId, popupInfo, weakOverlayManger = AceType::WeakClaim(AceType::RawPtr(overlayManager))]() {
                    auto overlay = weakOverlayManger.Upgrade();
                    CHECK_NULL_VOID(overlay);
                    LOGI("begin to update popup node.");
                    overlay->UpdatePopupNode(targetId, popupInfo);
                });
        }
    }
}

void ViewAbstract::BindMenuWithItems(std::vector<OptionParam>&& params,
    const RefPtr<FrameNode>& targetNode, const NG::OffsetF& offset, const MenuParam& menuParam)
{
    CHECK_NULL_VOID(targetNode);

    if (params.empty()) {
        LOGD("menu params is empty");
        return;
    }
    auto menuNode =
        MenuView::Create(std::move(params), targetNode->GetId(), targetNode->GetTag(), MenuType::MENU, menuParam);
    BindMenu(menuNode, targetNode->GetId(), offset);
}

void ViewAbstract::BindMenuWithCustomNode(const RefPtr<UINode>& customNode, const RefPtr<FrameNode>& targetNode,
    const NG::OffsetF& offset, const MenuParam& menuParam, const RefPtr<UINode>& previewCustomNode)
{
    LOGD("ViewAbstract::BindMenuWithCustomNode");
    CHECK_NULL_VOID(customNode);
    CHECK_NULL_VOID(targetNode);
    auto type = menuParam.type;
#ifdef PREVIEW
    // unable to use the subWindow in the Previewer.
    type = MenuType::MENU;
#endif
    auto menuNode =
        MenuView::Create(customNode, targetNode->GetId(), targetNode->GetTag(), menuParam, true, previewCustomNode);
    if (type == MenuType::CONTEXT_MENU) {
        SubwindowManager::GetInstance()->ShowMenuNG(menuNode, targetNode->GetId(), offset, menuParam.isAboveApps);
        return;
    }
    BindMenu(menuNode, targetNode->GetId(), offset);
}

void ViewAbstract::ShowMenu(int32_t targetId, const NG::OffsetF& offset, bool isContextMenu)
{
    if (isContextMenu) {
        SubwindowManager::GetInstance()->ShowMenuNG(nullptr, targetId, offset);
        return;
    }
    LOGD("ViewAbstract::ShowMenu");
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    CHECK_NULL_VOID(context);
    auto overlayManager = context->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);

    overlayManager->ShowMenu(targetId, offset, nullptr);
}

void ViewAbstract::SetBackdropBlur(const Dimension& radius)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto target = frameNode->GetRenderContext();
    if (target) {
        if (target->GetBackgroundEffect().has_value()) {
            target->UpdateBackgroundEffect(std::nullopt);
        }
        target->UpdateBackBlurRadius(radius);
        if (target->GetBackBlurStyle().has_value()) {
            target->UpdateBackBlurStyle(std::nullopt);
        }
    }
}

void ViewAbstract::SetLinearGradientBlur(NG::LinearGradientBlurPara blurPara)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(LinearGradientBlur, blurPara);
}

void ViewAbstract::SetDynamicLightUp(float rate, float lightUpDegree)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(DynamicLightUpRate, rate);
    ACE_UPDATE_RENDER_CONTEXT(DynamicLightUpDegree, lightUpDegree);
}

void ViewAbstract::SetFrontBlur(const Dimension& radius)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto target = frameNode->GetRenderContext();
    if (target) {
        target->UpdateFrontBlurRadius(radius);
        if (target->GetFrontBlurStyle().has_value()) {
            target->UpdateFrontBlurStyle(std::nullopt);
        }
    }
}

void ViewAbstract::SetBackShadow(const Shadow& shadow)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(BackShadow, shadow);
}

void ViewAbstract::SetLinearGradient(const NG::Gradient& gradient)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(LinearGradient, gradient);
}

void ViewAbstract::SetSweepGradient(const NG::Gradient& gradient)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(SweepGradient, gradient);
}

void ViewAbstract::SetRadialGradient(const NG::Gradient& gradient)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(RadialGradient, gradient);
}

void ViewAbstract::SetInspectorId(const std::string& inspectorId)
{
    auto uiNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
    if (uiNode) {
        uiNode->UpdateInspectorId(inspectorId);
    }
}

void ViewAbstract::SetRestoreId(int32_t restoreId)
{
    auto uiNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
    if (uiNode) {
        uiNode->SetRestoreId(restoreId);
    }
}

void ViewAbstract::SetDebugLine(const std::string& line)
{
#ifdef PREVIEW
    auto uiNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
    if (uiNode) {
        uiNode->SetDebugLine(line);
    }
#endif
}

void ViewAbstract::SetGrid(std::optional<int32_t> span, std::optional<int32_t> offset, GridSizeType type)
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
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(Transition, options);
}

void ViewAbstract::SetChainedTransition(const RefPtr<NG::ChainedTransitionEffect>& effect)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(ChainedTransition, effect);
}

void ViewAbstract::SetClipShape(const RefPtr<BasicShape>& basicShape)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(ClipShape, basicShape);
}

void ViewAbstract::SetClipEdge(bool isClip)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(ClipEdge, isClip);
}

void ViewAbstract::SetMask(const RefPtr<BasicShape>& basicShape)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(ClipMask, basicShape);
}

void ViewAbstract::SetProgressMask(const RefPtr<ProgressMaskProperty>& progress)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(ProgressMask, progress);
}

void ViewAbstract::SetBrightness(const Dimension& brightness)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(FrontBrightness, brightness);
}

void ViewAbstract::SetGrayScale(const Dimension& grayScale)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(FrontGrayScale, grayScale);
}

void ViewAbstract::SetContrast(const Dimension& contrast)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(FrontContrast, contrast);
}

void ViewAbstract::SetSaturate(const Dimension& saturate)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(FrontSaturate, saturate);
}

void ViewAbstract::SetSepia(const Dimension& sepia)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(FrontSepia, sepia);
}

void ViewAbstract::SetInvert(const Dimension& invert)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(FrontInvert, invert);
}

void ViewAbstract::SetHueRotate(float hueRotate)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(FrontHueRotate, hueRotate);
}

void ViewAbstract::SetColorBlend(const Color& colorBlend)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(FrontColorBlend, colorBlend);
}

void ViewAbstract::SetBorderImage(const RefPtr<BorderImage>& borderImage)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(BorderImage, borderImage);

    auto pipeline = PipelineContext::GetCurrentContext();
    if (pipeline && pipeline->GetMinPlatformVersion() >= 11) {
        BorderWidthProperty borderWidth;
        borderWidth.leftDimen = borderImage->GetBorderImageEdge(BorderImageDirection::LEFT).GetBorderImageWidth();
        borderWidth.rightDimen = borderImage->GetBorderImageEdge(BorderImageDirection::RIGHT).GetBorderImageWidth();
        borderWidth.topDimen = borderImage->GetBorderImageEdge(BorderImageDirection::TOP).GetBorderImageWidth();
        borderWidth.bottomDimen = borderImage->GetBorderImageEdge(BorderImageDirection::BOTTOM).GetBorderImageWidth();

        ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, BorderWidth, borderWidth);
    }
}

void ViewAbstract::SetBorderImageSource(const std::string& bdImageSrc)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ImageSourceInfo imageSourceInfo(bdImageSrc);
    ACE_UPDATE_RENDER_CONTEXT(BorderImageSource, imageSourceInfo);
}

void ViewAbstract::SetHasBorderImageSlice(bool tag)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(HasBorderImageSlice, tag);
}

void ViewAbstract::SetHasBorderImageWidth(bool tag)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(HasBorderImageWidth, tag);
}

void ViewAbstract::SetHasBorderImageOutset(bool tag)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(HasBorderImageOutset, tag);
}

void ViewAbstract::SetHasBorderImageRepeat(bool tag)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(HasBorderImageRepeat, tag);
}

void ViewAbstract::SetBorderImageGradient(const Gradient& gradient)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(BorderImageGradient, gradient);
}

void ViewAbstract::SetOverlay(const OverlayOptions& overlay)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(OverlayText, overlay);
}

void ViewAbstract::SetMotionPath(const MotionPathOption& motionPath)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(MotionPath, motionPath);
}

void ViewAbstract::SetSharedTransition(
    const std::string& shareId, const std::shared_ptr<SharedTransitionOption>& option)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto target = frameNode->GetRenderContext();
    if (target) {
        target->SetSharedTransitionOptions(option);
        target->SetShareId(shareId);
    }
}

void ViewAbstract::SetUseEffect(bool useEffect)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(UseEffect, useEffect);
}

void ViewAbstract::SetForegroundColor(const Color& color)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(ForegroundColor, color);
    ACE_RESET_RENDER_CONTEXT(RenderContext, ForegroundColorStrategy);
    ACE_UPDATE_RENDER_CONTEXT(ForegroundColorFlag, true);
}

void ViewAbstract::SetForegroundColorStrategy(const ForegroundColorStrategy& strategy)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(ForegroundColorStrategy, strategy);
    ACE_RESET_RENDER_CONTEXT(RenderContext, ForegroundColor);
    ACE_UPDATE_RENDER_CONTEXT(ForegroundColorFlag, true);
}

void ViewAbstract::SetKeyboardShortcut(
    const std::string& value, const std::vector<ModifierKey>& keys, std::function<void()>&& onKeyboardShortcutAction)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto eventManager = pipeline->GetEventManager();
    CHECK_NULL_VOID(eventManager);
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    if (value.empty() || (keys.size() == 0 && value.length() == 1)) {
        LOGI("KeyboardShortcut value and keys is invalid, return");
        eventHub->SetKeyboardShortcut("", 0, nullptr);
        return;
    }
    auto key = eventManager->GetKeyboardShortcutKeys(keys);
    if ((key == 0 && value.length() == 1) || (key == 0 && keys.size() > 0 && value.length() > 1)) {
        LOGI("KeyboardShortcut's keys are the same, return");
        return;
    }
    if (eventManager->IsSameKeyboardShortcutNode(value, key)) {
        LOGI("KeyboardShortcut is the same, return");
        return;
    }
    eventHub->SetKeyboardShortcut(value, key, std::move(onKeyboardShortcutAction));
    eventManager->AddKeyboardShortcutNode(WeakPtr<NG::FrameNode>(frameNode));
}

void ViewAbstract::CreateAnimatablePropertyFloat(const std::string& propertyName, float value,
    const std::function<void(float)>& onCallbackEvent)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    frameNode->CreateAnimatablePropertyFloat(propertyName, value, onCallbackEvent);
}

void ViewAbstract::UpdateAnimatablePropertyFloat(const std::string& propertyName, float value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    frameNode->UpdateAnimatablePropertyFloat(propertyName, value);
}

void ViewAbstract::CreateAnimatableArithmeticProperty(const std::string& propertyName,
    RefPtr<CustomAnimatableArithmetic>& value,
    std::function<void(const RefPtr<CustomAnimatableArithmetic>&)>& onCallbackEvent)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    frameNode->CreateAnimatableArithmeticProperty(propertyName, value, onCallbackEvent);
}

void ViewAbstract::UpdateAnimatableArithmeticProperty(const std::string& propertyName,
    RefPtr<CustomAnimatableArithmetic>& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    frameNode->UpdateAnimatableArithmeticProperty(propertyName, value);
}

void ViewAbstract::SetObscured(const std::vector<ObscuredReasons>& reasons)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(Obscured, reasons);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void ViewAbstract::UpdateSafeAreaExpandOpts(const SafeAreaExpandOpts& opts)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, SafeAreaExpandOpts, opts);
}

void ViewAbstract::SetRenderGroup(bool isRenderGroup)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(RenderGroup, isRenderGroup);
}

void ViewAbstract::SetRenderFit(RenderFit renderFit)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(RenderFit, renderFit);
}
} // namespace OHOS::Ace::NG
