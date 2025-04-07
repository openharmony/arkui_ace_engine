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

#include "core/components_ng/base/view_abstract.h"
#include <cstdint>
#include <functional>
#include <unordered_map>
#include "core/components_ng/pattern/overlay/overlay_manager.h"

#include "interfaces/inner_api/ui_session/ui_session_manager.h"

#include "base/error/error_code.h"
#include "base/subwindow/subwindow.h"
#include "base/utils/system_properties.h"
#include "base/utils/utils.h"
#include "core/common/ace_engine.h"
#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/shadow.h"
#include "core/components/theme/shadow_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/bubble/bubble_pattern.h"
#include "core/components_ng/pattern/bubble/bubble_view.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/menu/menu_view.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"
#include "core/components_ng/pattern/overlay/dialog_manager.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_event_hub.h"
#include "core/components_ng/pattern/list/list_event_hub.h"
#include "core/components_ng/pattern/scroll/scroll_event_hub.h"
#include "core/components_ng/pattern/grid/grid_event_hub.h"
#include "core/components_ng/pattern/waterflow/water_flow_event_hub.h"

namespace OHOS::Ace::NG {

void ViewAbstract::SetWidth(const CalcLength& width)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
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
        return;
    }
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, AspectRatio, ratio);
}

void ViewAbstract::ResetAspectRatio()
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_RESET_LAYOUT_PROPERTY(LayoutProperty, AspectRatio);
}

void ViewAbstract::SetBackgroundAlign(const Alignment& align)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(BackgroundAlign, align);
}

void ViewAbstract::SetBackgroundColor(const Color& color)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }

    Color updateColor = color;
    auto pipeline = PipelineContext::GetCurrentContext();
    if (pipeline != nullptr) {
        pipeline->CheckNeedUpdateBackgroundColor(updateColor);
    }

    ACE_UPDATE_RENDER_CONTEXT(BackgroundColor, updateColor);
}

void ViewAbstract::SetBackgroundColor(FrameNode* frameNode, const Color& color)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(BackgroundColor, color, frameNode);
}

void ViewAbstract::SetBackgroundImage(const ImageSourceInfo& src)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    auto pipeline = PipelineContext::GetCurrentContext();
    if (pipeline != nullptr) {
        bool disableSetImage = pipeline->CheckNeedDisableUpdateBackgroundImage();
        if (disableSetImage) {
            return;
        }
    }
    ACE_UPDATE_RENDER_CONTEXT(BackgroundImage, src);
}

void ViewAbstract::SetBackgroundImage(FrameNode* frameNode, const ImageSourceInfo& src)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(BackgroundImage, src, frameNode);
}

void ViewAbstract::SetBackgroundImageRepeat(const ImageRepeat& imageRepeat)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(BackgroundImageRepeat, imageRepeat);
}

void ViewAbstract::SetBackgroundImageRepeat(FrameNode* frameNode, const ImageRepeat& imageRepeat)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(BackgroundImageRepeat, imageRepeat, frameNode);
}

void ViewAbstract::SetBackgroundImageSyncMode(bool syncMode)
{
    ACE_UPDATE_RENDER_CONTEXT(BackgroundImageSyncMode, syncMode);
}

void ViewAbstract::SetBackgroundImageSyncMode(FrameNode* frameNode, bool syncMode)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(BackgroundImageSyncMode, syncMode, frameNode);
}

void ViewAbstract::SetBackgroundImageSize(const BackgroundImageSize& bgImgSize)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(BackgroundImageSize, bgImgSize);
}

void ViewAbstract::SetBackgroundImageSize(FrameNode* frameNode, const BackgroundImageSize& bgImgSize)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(BackgroundImageSize, bgImgSize, frameNode);
}

void ViewAbstract::SetBackgroundImagePosition(const BackgroundImagePosition& bgImgPosition)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(BackgroundImagePosition, bgImgPosition);
}

void ViewAbstract::SetBackgroundImagePosition(FrameNode* frameNode, const BackgroundImagePosition& bgImgPosition)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(BackgroundImagePosition, bgImgPosition, frameNode);
}

void ViewAbstract::SetBackgroundBlurStyle(const BlurStyleOption& bgBlurStyle, const SysOptions& sysOptions)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    SetBackgroundBlurStyle(frameNode, bgBlurStyle, sysOptions);
}

void ViewAbstract::SetForegroundEffect(float radius)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto target = frameNode->GetRenderContext();
    if (target) {
        target->UpdateForegroundEffect(radius);
    }
}

void ViewAbstract::SetMotionBlur(const MotionBlurOption &motionBlurOption)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(MotionBlur, motionBlurOption);
}

void ViewAbstract::SetBackgroundEffect(const EffectOption& effectOption, const SysOptions& sysOptions)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    SetBackgroundEffect(ViewStackProcessor::GetInstance()->GetMainFrameNode(), effectOption, sysOptions);
}

void ViewAbstract::SetForegroundBlurStyle(const BlurStyleOption& fgBlurStyle, const SysOptions& sysOptions)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto target = frameNode->GetRenderContext();
    if (target) {
        target->UpdateFrontBlurStyle(fgBlurStyle, sysOptions);
        if (target->GetFrontBlurRadius().has_value()) {
            target->UpdateFrontBlurRadius(Dimension());
        }
    }
}

void ViewAbstract::SetSphericalEffect(double radio)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(SphericalEffect, radio);
}

void ViewAbstract::SetPixelStretchEffect(PixStretchEffectOption& option)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(PixelStretchEffect, option);
}

void ViewAbstract::SetLightUpEffect(double radio)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(LightUpEffect, radio);
}

void ViewAbstract::SetLayoutWeight(float value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, LayoutWeight, static_cast<float>(value));
}

void ViewAbstract::SetChainWeight(const NG::ChainWeightPair& value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, ChainWeight, value);
}

void ViewAbstract::SetPixelRound(uint16_t value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, PixelRound, value);
}

void ViewAbstract::SetPixelRound(FrameNode* frameNode, uint16_t value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LayoutProperty, PixelRound, value, frameNode);
}

void ViewAbstract::SetLayoutDirection(TextDirection value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, LayoutDirection, value);
}

void ViewAbstract::SetAlignRules(const std::map<AlignDirection, AlignRule>& alignRules)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, AlignRules, alignRules);
}

void ViewAbstract::SetChainStyle(const ChainInfo& chainInfo)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, ChainStyle, chainInfo);
}

void ViewAbstract::SetBias(const BiasPair& biasPair)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, Bias, biasPair);
}

void ViewAbstract::SetAlignSelf(FlexAlign value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, AlignSelf, value);
}

void ViewAbstract::SetFlexShrink(float value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, FlexShrink, value);
}

void ViewAbstract::ResetFlexShrink()
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_RESET_LAYOUT_PROPERTY(LayoutProperty, FlexShrink);
}

void ViewAbstract::SetFlexGrow(float value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, FlexGrow, value);
}

void ViewAbstract::SetFlexBasis(const Dimension& value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
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
        return;
    }
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, DisplayIndex, value);
}

void ViewAbstract::SetPadding(const CalcLength& value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    PaddingProperty padding;
    padding.SetEdges(value);
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, Padding, padding);
}

void ViewAbstract::SetPadding(const PaddingProperty& value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, Padding, value);
}

void ViewAbstract::SetSafeAreaPadding(const CalcLength& value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    PaddingProperty padding;
    padding.SetEdges(value);
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, SafeAreaPadding, padding);
}

void ViewAbstract::SetSafeAreaPadding(const PaddingProperty& value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, SafeAreaPadding, value);
}

void ViewAbstract::ResetSafeAreaPadding()
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_RESET_LAYOUT_PROPERTY(LayoutProperty, SafeAreaPadding);
}

void ViewAbstract::SetSafeAreaPadding(FrameNode* frameNode, const CalcLength& value)
{
    CHECK_NULL_VOID(frameNode);
    PaddingProperty padding;
    padding.SetEdges(value);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LayoutProperty, SafeAreaPadding, padding, frameNode);
}

void ViewAbstract::SetSafeAreaPadding(FrameNode* frameNode, const PaddingProperty& value)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LayoutProperty, SafeAreaPadding, value, frameNode);
}

void ViewAbstract::ResetSafeAreaPadding(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    ACE_RESET_NODE_LAYOUT_PROPERTY(LayoutProperty, SafeAreaPadding, frameNode);
}

void ViewAbstract::SetMargin(const CalcLength& value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    MarginProperty margin;
    margin.SetEdges(value);
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, Margin, margin);
}

void ViewAbstract::SetMargin(const MarginProperty& value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, Margin, value);
}

void ViewAbstract::SetBorderRadius(const Dimension& value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
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
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(BorderRadius, value);
}

void ViewAbstract::SetBorderColor(const Color& value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    BorderColorProperty borderColor;
    borderColor.SetColor(value);
    ACE_UPDATE_RENDER_CONTEXT(BorderColor, borderColor);
}

void ViewAbstract::SetBorderColor(const BorderColorProperty& value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(BorderColor, value);
}

void ViewAbstract::SetBorderWidth(const Dimension& value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    BorderWidthProperty borderWidth;
    if (Negative(value.Value())) {
        borderWidth.SetBorderWidth(Dimension(0));
    } else {
        borderWidth.SetBorderWidth(value);
    }
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, BorderWidth, borderWidth);
    ACE_UPDATE_RENDER_CONTEXT(BorderWidth, borderWidth);
}

void ViewAbstract::SetBorderWidth(const BorderWidthProperty& value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, BorderWidth, value);
    ACE_UPDATE_RENDER_CONTEXT(BorderWidth, value);
}

void ViewAbstract::SetBorderStyle(const BorderStyle& value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    BorderStyleProperty borderStyle;
    borderStyle.SetBorderStyle(value);
    ACE_UPDATE_RENDER_CONTEXT(BorderStyle, borderStyle);
}

void ViewAbstract::SetBorderStyle(FrameNode* frameNode, const BorderStyle& value)
{
    BorderStyleProperty borderStyle;
    borderStyle.SetBorderStyle(value);
    ACE_UPDATE_NODE_RENDER_CONTEXT(BorderStyle, borderStyle, frameNode);
}

void ViewAbstract::SetBorderStyle(const BorderStyleProperty& value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(BorderStyle, value);
}

void ViewAbstract::SetBorderStyle(FrameNode* frameNode, const BorderStyleProperty& value)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(BorderStyle, value, frameNode);
}

void ViewAbstract::SetDashGap(const Dimension& value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    BorderWidthProperty dashGap;
    dashGap.SetBorderWidth(value);

    ACE_UPDATE_RENDER_CONTEXT(DashGap, dashGap);
}

void ViewAbstract::SetDashGap(FrameNode *frameNode, const Dimension& value)
{
    BorderWidthProperty dashGap;
    dashGap.SetBorderWidth(value);

    ACE_UPDATE_NODE_RENDER_CONTEXT(DashGap, dashGap, frameNode);
}

void ViewAbstract::SetDashGap(const BorderWidthProperty& value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(DashGap, value);
}

void ViewAbstract::SetDashGap(FrameNode *frameNode, const BorderWidthProperty& value)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(DashGap, value, frameNode);
}

void ViewAbstract::SetDashWidth(const Dimension& value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    BorderWidthProperty dashWidth;
    dashWidth.SetBorderWidth(value);

    ACE_UPDATE_RENDER_CONTEXT(DashWidth, dashWidth);
}

void ViewAbstract::SetDashWidth(FrameNode *frameNode, const Dimension& value)
{
    BorderWidthProperty dashWidth;
    dashWidth.SetBorderWidth(value);

    ACE_UPDATE_NODE_RENDER_CONTEXT(DashWidth, dashWidth, frameNode);
}

void ViewAbstract::SetDashWidth(const BorderWidthProperty& value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(DashWidth, value);
}

void ViewAbstract::SetDashWidth(FrameNode *frameNode, const BorderWidthProperty& value)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(DashWidth, value, frameNode);
}

void ViewAbstract::SetOuterBorderRadius(const Dimension& value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(value);
    borderRadius.multiValued = false;
    ACE_UPDATE_RENDER_CONTEXT(OuterBorderRadius, borderRadius);
}

void ViewAbstract::SetOuterBorderRadius(FrameNode* frameNode, const Dimension& value)
{
    BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(value);
    borderRadius.multiValued = false;
    ACE_UPDATE_NODE_RENDER_CONTEXT(OuterBorderRadius, borderRadius, frameNode);
}

void ViewAbstract::SetOuterBorderRadius(const BorderRadiusProperty& value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(OuterBorderRadius, value);
}

void ViewAbstract::SetOuterBorderRadius(FrameNode* frameNode, const BorderRadiusProperty& value)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(OuterBorderRadius, value, frameNode);
}

void ViewAbstract::SetOuterBorderColor(const Color& value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    BorderColorProperty borderColor;
    borderColor.SetColor(value);
    ACE_UPDATE_RENDER_CONTEXT(OuterBorderColor, borderColor);
}

void ViewAbstract::SetOuterBorderColor(FrameNode* frameNode, const Color& value)
{
    BorderColorProperty borderColor;
    borderColor.SetColor(value);
    ACE_UPDATE_NODE_RENDER_CONTEXT(OuterBorderColor, borderColor, frameNode);
}

void ViewAbstract::SetOuterBorderColor(const BorderColorProperty& value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(OuterBorderColor, value);
}

void ViewAbstract::SetOuterBorderColor(FrameNode* frameNode, const BorderColorProperty& value)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(OuterBorderColor, value, frameNode);
}

void ViewAbstract::SetOuterBorderWidth(const Dimension& value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    BorderWidthProperty borderWidth;
    if (Negative(value.Value())) {
        borderWidth.SetBorderWidth(Dimension(0));
    } else {
        borderWidth.SetBorderWidth(value);
    }
    ACE_UPDATE_RENDER_CONTEXT(OuterBorderWidth, borderWidth);
}

void ViewAbstract::SetOuterBorderWidth(FrameNode* frameNode, const Dimension& value)
{
    BorderWidthProperty borderWidth;
    if (Negative(value.Value())) {
        borderWidth.SetBorderWidth(Dimension(0));
    } else {
        borderWidth.SetBorderWidth(value);
    }
    ACE_UPDATE_NODE_RENDER_CONTEXT(OuterBorderWidth, borderWidth, frameNode);
}

void ViewAbstract::SetOuterBorderWidth(const BorderWidthProperty& value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(OuterBorderWidth, value);
}

void ViewAbstract::SetOuterBorderWidth(FrameNode* frameNode, const BorderWidthProperty& value)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(OuterBorderWidth, value, frameNode);
}

void ViewAbstract::SetOuterBorderStyle(const BorderStyleProperty& value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(OuterBorderStyle, value);
}

void ViewAbstract::SetOuterBorderStyle(FrameNode* frameNode, const BorderStyleProperty& value)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(OuterBorderStyle, value, frameNode);
}

void ViewAbstract::SetOuterBorderStyle(const BorderStyle& value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    BorderStyleProperty borderStyle;
    borderStyle.SetBorderStyle(value);
    ACE_UPDATE_RENDER_CONTEXT(OuterBorderStyle, borderStyle);
}

void ViewAbstract::SetOuterBorderStyle(FrameNode* frameNode, const BorderStyle& value)
{
    BorderStyleProperty borderStyle;
    borderStyle.SetBorderStyle(value);
    ACE_UPDATE_NODE_RENDER_CONTEXT(OuterBorderStyle, borderStyle, frameNode);
}

void ViewAbstract::DisableOnClick()
{
    auto gestureHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->ClearUserOnClick();
}

void ViewAbstract::DisableOnTouch()
{
    auto gestureHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->ClearUserOnTouch();
}

void ViewAbstract::DisableOnKeyEvent()
{
    auto focusHub = ViewStackProcessor::GetInstance()->GetOrCreateMainFrameNodeFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->ClearOnKeyCallback();
}

void ViewAbstract::DisableOnKeyEventDispatch()
{
    auto focusHub = ViewStackProcessor::GetInstance()->GetOrCreateMainFrameNodeFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->ClearOnKeyEventDispatchCallback();
}

#ifdef SUPPORT_DIGITAL_CROWN
void ViewAbstract::DisableOnCrownEvent()
{
    auto focusHub = ViewStackProcessor::GetInstance()->GetOrCreateMainFrameNodeFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->ClearOnCrownCallback();
}

void ViewAbstract::DisableOnCrownEvent(FrameNode* frameNode)
{
    auto focusHub = frameNode->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->ClearOnCrownCallback();
}

void ViewAbstract::SetOnCrownEvent(OnCrownCallbackFunc &&onCrownCallback)
{
    auto focusHub = ViewStackProcessor::GetInstance()->GetOrCreateMainFrameNodeFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->SetOnCrownCallback(std::move(onCrownCallback));
}

void ViewAbstract::SetOnCrownEvent(FrameNode* frameNode, OnCrownCallbackFunc &&onCrownCallback)
{
    CHECK_NULL_VOID(frameNode);
    auto focusHub = frameNode->GetOrCreateFocusHub();
    focusHub->SetOnCrownCallback(std::move(onCrownCallback));
}
#endif

void ViewAbstract::DisableOnHover()
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeInputEventHub();
    CHECK_NULL_VOID(eventHub);
    eventHub->ClearUserOnHover();
}

void ViewAbstract::DisableOnHoverMove()
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeInputEventHub();
    CHECK_NULL_VOID(eventHub);
    eventHub->ClearUserOnHoverMove();
}

void ViewAbstract::DisableOnAccessibilityHover()
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeInputEventHub();
    CHECK_NULL_VOID(eventHub);
    eventHub->ClearUserOnAccessibilityHover();
}

void ViewAbstract::DisableOnMouse()
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeInputEventHub();
    CHECK_NULL_VOID(eventHub);
    eventHub->ClearUserOnMouse();
}

void ViewAbstract::DisableOnAxisEvent()
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeInputEventHub();
    CHECK_NULL_VOID(eventHub);
    eventHub->ClearUserOnAxisEvent();
}

void ViewAbstract::DisableOnAppear()
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->ClearUserOnAppear();
}

void ViewAbstract::DisableOnDisAppear()
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->ClearUserOnDisAppear();
}

void ViewAbstract::DisableOnAttach()
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->ClearOnAttach();
}

void ViewAbstract::DisableOnDetach()
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->ClearOnDetach();
}

void ViewAbstract::DisableOnAreaChange()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    frameNode->ClearUserOnAreaChange();
}

void ViewAbstract::DisableOnFocus()
{
    auto focusHub = ViewStackProcessor::GetInstance()->GetOrCreateMainFrameNodeFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->ClearOnFocusCallback();
}

void ViewAbstract::DisableOnBlur()
{
    auto focusHub = ViewStackProcessor::GetInstance()->GetOrCreateMainFrameNodeFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->ClearOnBlurCallback();
}

void ViewAbstract::DisableOnFocusAxisEvent()
{
    auto focusHub = ViewStackProcessor::GetInstance()->GetOrCreateMainFrameNodeFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->ClearOnFocusAxisCallback();
}

void ViewAbstract::DisableOnFocusAxisEvent(FrameNode* frameNode)
{
    auto focusHub = frameNode->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->ClearOnFocusAxisCallback();
}

void ViewAbstract::DisableOnClick(FrameNode* frameNode)
{
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->ClearUserOnClick();
    auto* uiNode = reinterpret_cast<UINode*>(frameNode);
    CHECK_NULL_VOID(uiNode);
    uiNode->SetModifierEventRegistrationState(uiNode->IsCNode(), false);
}

void ViewAbstract::DisableOnDragStart(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->ClearCustomerOnDragStart();
}

void ViewAbstract::DisableOnDragEnter(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->ClearCustomerOnDragEnter();
}

void ViewAbstract::DisableOnDragMove(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->ClearCustomerOnDragMove();
}

void ViewAbstract::DisableOnDragLeave(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->ClearCustomerOnDragLeave();
}

void ViewAbstract::DisableOnDrop(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->ClearCustomerOnDrop();
}

void ViewAbstract::DisableOnDragEnd(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->ClearCustomerOnDragEnd();
}

void ViewAbstract::DisableOnTouch(FrameNode* frameNode)
{
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->ClearUserOnTouch();
}

void ViewAbstract::DisableOnKeyEvent(FrameNode* frameNode)
{
    auto focusHub = frameNode->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->ClearOnKeyCallback();
}

void ViewAbstract::DisableOnKeyEventDispatch(FrameNode* frameNode)
{
    auto focusHub = frameNode->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->ClearOnKeyEventDispatchCallback();
}

void ViewAbstract::DisableOnHover(FrameNode* frameNode)
{
    auto eventHub = frameNode->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(eventHub);
    eventHub->ClearUserOnHover();
}

void ViewAbstract::DisableOnHoverMove(FrameNode* frameNode)
{
    auto eventHub = frameNode->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(eventHub);
    eventHub->ClearUserOnHoverMove();
}

void ViewAbstract::DisableOnMouse(FrameNode* frameNode)
{
    auto eventHub = frameNode->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(eventHub);
    eventHub->ClearUserOnMouse();
}

void ViewAbstract::DisableOnAxisEvent(FrameNode* frameNode)
{
    auto eventHub = frameNode->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(eventHub);
    eventHub->ClearUserOnAxisEvent();
}

void ViewAbstract::DisableOnAppear(FrameNode* frameNode)
{
    auto eventHub = frameNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->ClearUserOnAppear();
}

void ViewAbstract::DisableOnDisappear(FrameNode* frameNode)
{
    auto eventHub = frameNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->ClearUserOnDisAppear();
}

void ViewAbstract::DisableOnAttach(FrameNode* frameNode)
{
    auto eventHub = frameNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->ClearOnAttach();
}

void ViewAbstract::DisableOnDetach(FrameNode* frameNode)
{
    auto eventHub = frameNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->ClearOnDetach();
}

void ViewAbstract::DisableOnPreDrag(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->ClearOnPreDrag();
}

void ViewAbstract::DisableOnFocus(FrameNode* frameNode)
{
    auto focusHub = frameNode->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->ClearOnFocusCallback();
}

void ViewAbstract::DisableOnBlur(FrameNode* frameNode)
{
    auto focusHub = frameNode->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->ClearOnBlurCallback();
}

void ViewAbstract::DisableOnAreaChange(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    frameNode->ClearUserOnAreaChange();
}

void ViewAbstract::SetOnClick(GestureEventFunc&& clickEventFunc, double distanceThreshold)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->SetUserOnClick(std::move(clickEventFunc), distanceThreshold);

    auto focusHub = frameNode->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->SetFocusable(true, false);

    auto* uiNode = reinterpret_cast<UINode*>(frameNode);
    CHECK_NULL_VOID(uiNode);
    uiNode->SetModifierEventRegistrationState(uiNode->IsCNode(), true);
}

void ViewAbstract::SetOnGestureJudgeBegin(GestureJudgeFunc&& gestureJudgeFunc)
{
    auto gestureHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->SetOnGestureJudgeBegin(std::move(gestureJudgeFunc));
}

void ViewAbstract::SetOnTouchIntercept(TouchInterceptFunc&& touchInterceptFunc)
{
    auto gestureHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->SetOnTouchIntercept(std::move(touchInterceptFunc));
}

void ViewAbstract::SetShouldBuiltInRecognizerParallelWith(
    NG::ShouldBuiltInRecognizerParallelWithFunc&& shouldBuiltInRecognizerParallelWithFunc)
{
    auto gestureHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->SetShouldBuildinRecognizerParallelWithFunc(std::move(shouldBuiltInRecognizerParallelWithFunc));
}

void ViewAbstract::SetOnGestureRecognizerJudgeBegin(
    GestureRecognizerJudgeFunc&& gestureRecognizerJudgeFunc, bool exposeInnerGestureFlag)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    frameNode->SetExposeInnerGestureFlag(exposeInnerGestureFlag);

    auto gestureHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->SetOnGestureRecognizerJudgeBegin(std::move(gestureRecognizerJudgeFunc));
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

void ViewAbstract::SetOnAxisEvent(OnAxisEventFunc&& onAxisEventFunc)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeInputEventHub();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetAxisEvent(std::move(onAxisEventFunc));
}

void ViewAbstract::SetOnHover(OnHoverFunc&& onHoverEventFunc)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeInputEventHub();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetHoverEvent(std::move(onHoverEventFunc));
}

void ViewAbstract::SetOnHoverMove(OnHoverMoveFunc&& onHoverMoveEventFunc)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeInputEventHub();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetHoverMoveEvent(std::move(onHoverMoveEventFunc));
}

void ViewAbstract::SetOnAccessibilityHover(OnAccessibilityHoverFunc &&onAccessibilityHoverEventFunc)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeInputEventHub();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetAccessibilityHoverEvent(std::move(onAccessibilityHoverEventFunc));
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
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    if (eventHub) {
        eventHub->SetEnabled(enabled);
    }

    // The SetEnabled of focusHub must be after at eventHub
    auto focusHub = frameNode->GetOrCreateFocusHub();
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

void ViewAbstract::SetTabStop(bool tabStop)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto focusHub = frameNode->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->SetTabStop(tabStop);
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

void ViewAbstract::SetOnKeyEvent(OnKeyConsumeFunc&& onKeyCallback)
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

void ViewAbstract::SetNextFocus(FocusIntension key, const std::string& nextFocus)
{
    auto focusHub = ViewStackProcessor::GetInstance()->GetOrCreateMainFrameNodeFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->SetNextFocus(key, nextFocus);
}

void ViewAbstract::ResetNextFocus()
{
    auto focusHub = ViewStackProcessor::GetInstance()->GetOrCreateMainFrameNodeFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->ResetNextFocus();
}

void ViewAbstract::SetFocusBoxStyle(const NG::FocusBoxStyle& style)
{
    auto focusHub = ViewStackProcessor::GetInstance()->GetOrCreateMainFrameNodeFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->GetFocusBox().SetStyle(style);
}

void ViewAbstract::SetClickDistance(FrameNode* frameNode, double clickDistance)
{
    CHECK_NULL_VOID(frameNode);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->SetNodeClickDistance(clickDistance);
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

void ViewAbstract::SetOnAttach(std::function<void()> &&onAttach)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnAttach(std::move(onAttach));
}

void ViewAbstract::SetOnDetach(std::function<void()> &&onDetach)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnDetach(std::move(onDetach));
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

void ViewAbstract::SetOnSizeChanged(std::function<void(const RectF &oldRect, const RectF &rect)> &&onSizeChanged)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    frameNode->SetOnSizeChangeCallback(std::move(onSizeChanged));
}

void ViewAbstract::SetOnVisibleChange(std::function<void(bool, double)> &&onVisibleChange,
    const std::vector<double> &ratioList)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    CHECK_NULL_VOID(frameNode);
    frameNode->CleanVisibleAreaUserCallback();
    pipeline->AddVisibleAreaChangeNode(frameNode, ratioList, onVisibleChange);
}

void ViewAbstract::SetResponseRegion(const std::vector<DimensionRect>& responseRegion)
{
    auto gestureHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->SetResponseRegion(responseRegion);
}

void ViewAbstract::SetMouseResponseRegion(const std::vector<DimensionRect>& mouseRegion)
{
    auto gestureHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->SetMouseResponseRegion(mouseRegion);
}

void ViewAbstract::SetTouchable(bool touchable)
{
    auto gestureHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->SetTouchable(touchable);
}

void ViewAbstract::SetMonopolizeEvents(bool monopolizeEvents)
{
    auto gestureHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->SetMonopolizeEvents(monopolizeEvents);
}

void ViewAbstract::SetHitTestMode(HitTestMode hitTestMode)
{
    auto gestureHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->SetHitTestMode(hitTestMode);
}

void ViewAbstract::SetOnTouchTestFunc(NG::OnChildTouchTestFunc&& onChildTouchTest)
{
    auto gestureHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->SetOnTouchTestFunc(std::move(onChildTouchTest));
}

void ViewAbstract::SetOnFocusAxisEvent(OnFocusAxisEventFunc&& onFocusAxisCallback)
{
    auto focusHub = ViewStackProcessor::GetInstance()->GetOrCreateMainFrameNodeFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->SetOnFocusAxisCallback(std::move(onFocusAxisCallback));
}

void ViewAbstract::SetOnFocusAxisEvent(FrameNode* frameNode, OnFocusAxisEventFunc &&onFocusAxisCallback)
{
    CHECK_NULL_VOID(frameNode);
    auto focusHub = frameNode->GetOrCreateFocusHub();
    focusHub->SetOnFocusAxisCallback(std::move(onFocusAxisCallback));
}

void ViewAbstract::AddDragFrameNodeToManager()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);

    dragDropManager->AddDragFrameNode(frameNode->GetId(), AceType::WeakClaim(frameNode));
}

void ViewAbstract::AddDragFrameNodeToManager(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);

    dragDropManager->AddDragFrameNode(frameNode->GetId(), AceType::WeakClaim(frameNode));
}

void ViewAbstract::NotifyDragStartRequest(DragStartRequestStatus dragStatus)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    dragDropManager->HandleSyncOnDragStart(dragStatus);
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
    frameNode->SetCustomerDraggable(draggable);
}

void ViewAbstract::SetDragPreviewOptions(const DragPreviewOption& previewOption)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    frameNode->SetDragPreviewOptions(previewOption, false);
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

void ViewAbstract::SetOnDragStart(FrameNode* frameNode,
    std::function<DragDropInfo(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&)>&& onDragStart)
{
    CHECK_NULL_VOID(frameNode);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->InitDragDropEvent();

    auto eventHub = frameNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnDragStart(std::move(onDragStart));
}

void ViewAbstract::SetOnDragEnter(FrameNode* frameNode,
    std::function<void(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&)>&& onDragEnter)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetCustomerOnDragFunc(DragFuncType::DRAG_ENTER, std::move(onDragEnter));

    AddDragFrameNodeToManager(frameNode);
}

void ViewAbstract::SetOnDragMove(FrameNode* frameNode,
    std::function<void(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&)>&& onDragMove)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetCustomerOnDragFunc(DragFuncType::DRAG_MOVE, std::move(onDragMove));

    AddDragFrameNodeToManager(frameNode);
}

void ViewAbstract::SetOnDragLeave(FrameNode* frameNode,
    std::function<void(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&)>&& onDragLeave)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetCustomerOnDragFunc(DragFuncType::DRAG_LEAVE, std::move(onDragLeave));

    AddDragFrameNodeToManager(frameNode);
}

void ViewAbstract::SetOnPreDrag(std::function<void(const PreDragStatus)>&& onPreDragFunc)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnPreDrag(std::move(onPreDragFunc));
}

void ViewAbstract::SetOnPreDrag(FrameNode* frameNode, std::function<void(const PreDragStatus)>&& onPreDragFunc)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnPreDrag(std::move(onPreDragFunc));
}

void ViewAbstract::SetOnDragEnter(
    std::function<void(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&)>&& onDragEnter)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetCustomerOnDragFunc(DragFuncType::DRAG_ENTER, std::move(onDragEnter));

    AddDragFrameNodeToManager();
}

void ViewAbstract::SetOnDragLeave(
    std::function<void(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&)>&& onDragLeave)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetCustomerOnDragFunc(DragFuncType::DRAG_LEAVE, std::move(onDragLeave));

    AddDragFrameNodeToManager();
}

void ViewAbstract::SetOnDragMove(
    std::function<void(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&)>&& onDragMove)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetCustomerOnDragFunc(DragFuncType::DRAG_MOVE, std::move(onDragMove));

    AddDragFrameNodeToManager();
}

void ViewAbstract::SetOnDrop(std::function<void(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&)>&& onDrop)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetCustomerOnDragFunc(DragFuncType::DRAG_DROP, std::move(onDrop));

    AddDragFrameNodeToManager();
}

void ViewAbstract::SetOnDragEnd(std::function<void(const RefPtr<OHOS::Ace::DragEvent>&)>&& onDragEnd)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetCustomerOnDragFunc(DragFuncType::DRAG_END, std::move(onDragEnd));

    AddDragFrameNodeToManager();
}

void ViewAbstract::SetOnDragEnd(
    FrameNode* frameNode, std::function<void(const RefPtr<OHOS::Ace::DragEvent>&)>&& onDragEnd)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetCustomerOnDragFunc(DragFuncType::DRAG_END, std::move(onDragEnd));

    AddDragFrameNodeToManager(frameNode);
}

void ViewAbstract::SetOnDrop(
    FrameNode* frameNode, std::function<void(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&)>&& onDrop)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);

    eventHub->SetCustomerOnDragFunc(DragFuncType::DRAG_DROP, std::move(onDrop));

    AddDragFrameNodeToManager(frameNode);
}

void ViewAbstract::SetAlign(Alignment alignment)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, Alignment, alignment);
}

void ViewAbstract::SetAlign(FrameNode* frameNode, Alignment alignment)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LayoutProperty, Alignment, alignment, frameNode);
}

void ViewAbstract::SetVisibility(VisibleType visible)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty();
    if (layoutProperty) {
        layoutProperty->UpdateVisibility(visible, true, true);
    }

    auto focusHub = frameNode->GetOrCreateFocusHub();
    if (focusHub) {
        focusHub->SetShow(visible == VisibleType::VISIBLE);
    }
}

void ViewAbstract::SetGeometryTransition(const std::string& id,
    bool followWithoutTransition, bool doRegisterSharedTransition)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty();
    if (layoutProperty) {
        layoutProperty->UpdateGeometryTransition(id, followWithoutTransition, doRegisterSharedTransition);
    }
}

void ViewAbstract::SetGeometryTransition(FrameNode *frameNode, const std::string& id,
    bool followWithoutTransition, bool doRegisterSharedTransition)
{
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty();
    if (layoutProperty) {
        layoutProperty->UpdateGeometryTransition(id, followWithoutTransition, doRegisterSharedTransition);
    }
}

const std::string ViewAbstract::GetGeometryTransition(FrameNode* frameNode,
    bool* followWithoutTransition, bool* doRegisterSharedTransition)
{
    CHECK_NULL_RETURN(frameNode, "");
    auto layoutProperty = frameNode->GetLayoutProperty();
    if (layoutProperty) {
        auto geometryTransition = layoutProperty->GetGeometryTransition();
        if (geometryTransition) {
            *followWithoutTransition = geometryTransition->GetFollowWithoutTransition();
            *doRegisterSharedTransition = geometryTransition->GetDoRegisterSharedTransition();
            return geometryTransition->GetId();
        }
    }
    return "";
}

void ViewAbstract::SetOpacity(double opacity)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
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

void ViewAbstract::SetDrawModifier(const RefPtr<NG::DrawModifier>& drawModifier)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    frameNode->SetDrawModifier(drawModifier);
}

void* ViewAbstract::GetFrameNode()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    return static_cast<void*>(frameNode);
}

void ViewAbstract::SetDragPreview(const NG::DragDropInfo& info)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    frameNode->SetDragPreview(info);
}

void ViewAbstract::SetPosition(const OffsetT<Dimension>& value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    CheckIfParentNeedMarkDirty(frameNode);
    ACE_RESET_RENDER_CONTEXT(RenderContext, PositionEdges);
    ACE_UPDATE_RENDER_CONTEXT(Position, value);
}

void ViewAbstract::SetPositionEdges(const EdgesParam& value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    CheckIfParentNeedMarkDirty(frameNode);
    ACE_RESET_RENDER_CONTEXT(RenderContext, Position);
    ACE_UPDATE_RENDER_CONTEXT(PositionEdges, value);
}

void ViewAbstract::CheckIfParentNeedMarkDirty(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto parentNode = frameNode->GetAncestorNodeOfFrame(false);
    CHECK_NULL_VOID(parentNode);
    // Row/Column/Flex measure and layout differently depending on whether the child nodes have position property,
    // need to remeasure in the dynamic switch scenario.
    if (parentNode->GetTag() == V2::COLUMN_ETS_TAG || parentNode->GetTag() == V2::ROW_ETS_TAG ||
        parentNode->GetTag() == V2::FLEX_ETS_TAG) {
        auto renderContext = frameNode->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        if (!renderContext->HasPositionEdges() && !renderContext->HasPosition()) {
            parentNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        }
    }
}

void ViewAbstract::SetOffset(const OffsetT<Dimension>& value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_RESET_RENDER_CONTEXT(RenderContext, OffsetEdges);
    ACE_UPDATE_RENDER_CONTEXT(Offset, value);
}

void ViewAbstract::SetOffsetEdges(const EdgesParam& value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_RESET_RENDER_CONTEXT(RenderContext, Offset);
    ACE_UPDATE_RENDER_CONTEXT(OffsetEdges, value);
}

void ViewAbstract::MarkAnchor(const OffsetT<Dimension>& value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(Anchor, value);
}

void ViewAbstract::ResetPosition()
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_RESET_RENDER_CONTEXT(RenderContext, Position);
    ACE_RESET_RENDER_CONTEXT(RenderContext, PositionEdges);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto parentNode = frameNode->GetAncestorNodeOfFrame(false);
    CHECK_NULL_VOID(parentNode);

    // Row/Column/Flex measure and layout differently depending on whether the child nodes have position property.
    if (parentNode->GetTag() == V2::COLUMN_ETS_TAG || parentNode->GetTag() == V2::ROW_ETS_TAG ||
        parentNode->GetTag() == V2::FLEX_ETS_TAG) {
        frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    } else {
        auto renderContext = frameNode->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        renderContext->RecalculatePosition();
    }
}

void ViewAbstract::SetZIndex(int32_t value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(ZIndex, value);
}

void ViewAbstract::SetScale(const NG::VectorF& value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(TransformScale, value);
}

void ViewAbstract::SetScale(FrameNode* frameNode, const NG::VectorF& value)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(TransformScale, value, frameNode);
}

void ViewAbstract::SetPivot(const DimensionOffset& value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(TransformCenter, value);
}

void ViewAbstract::SetPivot(FrameNode* frameNode, const DimensionOffset& value)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(TransformCenter, value, frameNode);
}

void ViewAbstract::SetTranslate(const NG::TranslateOptions& value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(TransformTranslate, value);
}

void ViewAbstract::SetTranslate(FrameNode* frameNode, const NG::TranslateOptions& value)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(TransformTranslate, value, frameNode);
}

void ViewAbstract::SetRotate(const NG::Vector5F& value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(TransformRotate, value);
}

void ViewAbstract::SetRotate(FrameNode* frameNode, const NG::Vector5F& value)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(TransformRotate, value, frameNode);
}

void ViewAbstract::SetTransformMatrix(const Matrix4& matrix)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(TransformMatrix, matrix);
}

void ViewAbstract::BindPopup(
    const RefPtr<PopupParam>& param, const RefPtr<FrameNode>& targetNode, const RefPtr<UINode>& customNode)
{
    TAG_LOGD(AceLogTag::ACE_DIALOG, "bind popup enter");
    CHECK_NULL_VOID(targetNode);
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto context = targetNode->GetContext();
    CHECK_NULL_VOID(context);
    auto instanceId = context->GetInstanceId();

    auto overlayManager = context->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    auto popupInfo = overlayManager->GetPopupInfo(targetId);
    auto isShow = param->IsShow();
    auto isUseCustom = param->IsUseCustom();
    auto showInSubWindow = param->IsShowInSubWindow();
    if (popupInfo.popupNode) {
        showInSubWindow = false;
    } else {
        // subwindow model needs to use subContainer to get popupInfo
        auto subwindow = SubwindowManager::GetInstance()->GetSubwindowByType(instanceId, SubwindowType::TYPE_POPUP);
        if (subwindow) {
            subwindow->GetPopupInfoNG(targetId, popupInfo);
        }
        if (popupInfo.popupNode) {
            if (popupInfo.isTips && subwindow) {
                auto overlayManager1 = subwindow->GetOverlayManager();
                CHECK_NULL_VOID(overlayManager1);
                overlayManager1->ErasePopup(targetId);
                popupInfo = {};
                overlayManager1->HideTips(targetId, popupInfo, 0);
            } else {
                showInSubWindow = true;
            }
        }
    }
    if (popupInfo.popupNode && popupInfo.isTips) {
        // subwindow need to handle
        overlayManager->ErasePopup(targetId);
        popupInfo = {};
        overlayManager->HideTips(targetId, popupInfo, 0);
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
        popupInfo.markNeedUpdate = popupShowing || !isShow;
    } else {
        // Invisable
        if (!isShow) {
            TAG_LOGD(AceLogTag::ACE_DIALOG, "Popup is already hidden");
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
        if (!showInSubWindow) {
            // erase popup when target node destroy
            auto destructor = [id = targetNode->GetId(), weak = AceType::WeakClaim(context)]() {
                auto pipeline = weak.Upgrade();
                CHECK_NULL_VOID(pipeline);
                auto overlayManager = pipeline->GetOverlayManager();
                CHECK_NULL_VOID(overlayManager);
                overlayManager->ErasePopup(id);
                SubwindowManager::GetInstance()->HideSubWindowNG();
            };
            targetNode->PushDestroyCallbackWithTag(destructor, std::to_string(popupId));
        } else {
            // erase popup in subwindow when target node destroy
            auto destructor = [id = targetNode->GetId(), containerId = instanceId]() {
                auto subwindow = SubwindowManager::GetInstance()->GetSubwindowByType(
                    containerId, SubwindowType::TYPE_POPUP);
                CHECK_NULL_VOID(subwindow);
                auto overlayManager = subwindow->GetOverlayManager();
                CHECK_NULL_VOID(overlayManager);
                overlayManager->ErasePopup(id);
                SubwindowManager::GetInstance()->HideSubWindowNG();
            };
            targetNode->PushDestroyCallbackWithTag(destructor, std::to_string(popupId));
        }
    } else {
        // use param to update PopupParm
        if (!isUseCustom) {
            BubbleView::UpdatePopupParam(popupId, param, targetNode);
            popupNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        } else {
            BubbleView::UpdateCustomPopupParam(popupId, param);
            popupNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        }
    }
    // update PopupInfo props
    popupInfo.popupId = popupId;
    popupInfo.popupNode = popupNode;
    popupInfo.isBlockEvent = param->IsBlockEvent();
    popupInfo.isAvoidKeyboard = param->GetKeyBoardAvoidMode() == PopupKeyboardAvoidMode::DEFAULT;
    if (popupNode) {
        popupNode->MarkModifyDone();
        popupPattern = popupNode->GetPattern<BubblePattern>();
        popupPattern->SetPopupParam(param);
        popupPattern->RegisterDoubleBindCallback(param->GetDoubleBindCallback());
        auto accessibilityProperty = popupNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
        if (accessibilityProperty) {
            accessibilityProperty->SetAccessibilityHoverPriority(param->IsBlockEvent());
        }
    }
    popupInfo.focusable = param->GetFocusable();
    popupInfo.target = AceType::WeakClaim(AceType::RawPtr(targetNode));
    popupInfo.targetSize = SizeF(param->GetTargetSize().Width(), param->GetTargetSize().Height());
    popupInfo.targetOffset = OffsetF(param->GetTargetOffset().GetX(), param->GetTargetOffset().GetY());
    if (showInSubWindow) {
        if (isShow) {
            SubwindowManager::GetInstance()->ShowPopupNG(
                targetNode, popupInfo, param->GetOnWillDismiss(), param->GetInteractiveDismiss());
        } else {
            SubwindowManager::GetInstance()->HidePopupNG(targetId);
        }
        return;
    }
    if (isShow) {
        if (popupInfo.isCurrentOnShow != isShow) {
            overlayManager->ShowPopup(targetId, popupInfo, param->GetOnWillDismiss(), param->GetInteractiveDismiss());
        }
    } else {
        overlayManager->HidePopup(targetId, popupInfo);
    }
}

void ViewAbstract::BindTips(
    const RefPtr<PopupParam>& param, const RefPtr<FrameNode>& targetNode, const RefPtr<SpanString>& spanString)
{
    CHECK_NULL_VOID(param);
    CHECK_NULL_VOID(targetNode);
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto context = targetNode->GetContext();
    CHECK_NULL_VOID(context);
    auto instanceId = context->GetInstanceId();
    auto overlayManager = context->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    auto tipsInfo = overlayManager->GetPopupInfo(targetId);
    if (tipsInfo.isTips) {
        return;
    }
    auto showInSubWindow = param->IsShowInSubWindow();
    if (tipsInfo.popupNode) {
        showInSubWindow = false;
    } else {
        auto subwindow = SubwindowManager::GetInstance()->GetSubwindowByType(instanceId, SubwindowType::TYPE_POPUP);
        if (subwindow) {
            subwindow->GetPopupInfoNG(targetId, tipsInfo);
        }
        if (tipsInfo.popupNode) {
            showInSubWindow = true;
        }
    }
    HandleHoverTipsInfo(param, targetNode, tipsInfo, showInSubWindow, spanString);
}

void ViewAbstract::HandleHoverTipsInfo(const RefPtr<PopupParam>& param, const RefPtr<FrameNode>& targetNode,
    PopupInfo& tipsInfo, bool showInSubWindow, const RefPtr<SpanString>& spanString)
{
    CHECK_NULL_VOID(param);
    CHECK_NULL_VOID(targetNode);
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = tipsInfo.popupId;
    auto popupNode = tipsInfo.popupNode;
    auto context = targetNode->GetContext();
    CHECK_NULL_VOID(context);
    auto instanceId = context->GetInstanceId();
    if (!tipsInfo.isTips && popupNode) {
        return;
    }
    RefPtr<BubblePattern> popupPattern;
    tipsInfo.markNeedUpdate = true;
    popupNode = BubbleView::CreateBubbleNode(targetTag, targetId, param, spanString);
    if (popupNode) {
        popupId = popupNode->GetId();
    }
    if (!showInSubWindow) {
        auto destructor = [id = targetNode->GetId()]() {
            auto pipeline = NG::PipelineContext::GetCurrentContext();
            CHECK_NULL_VOID(pipeline);
            auto overlayManager = pipeline->GetOverlayManager();
            CHECK_NULL_VOID(overlayManager);
            overlayManager->ErasePopup(id);
            SubwindowManager::GetInstance()->HideSubWindowNG();
        };
        targetNode->PushDestroyCallbackWithTag(destructor, std::to_string(popupId));
    } else {
        auto destructor = [id = targetNode->GetId(), containerId = instanceId]() {
            auto subwindow =
                SubwindowManager::GetInstance()->GetSubwindowByType(containerId, SubwindowType::TYPE_POPUP);
            CHECK_NULL_VOID(subwindow);
            auto overlayManager = subwindow->GetOverlayManager();
            CHECK_NULL_VOID(overlayManager);
            overlayManager->ErasePopup(id);
            SubwindowManager::GetInstance()->HideSubWindowNG();
        };
        targetNode->PushDestroyCallbackWithTag(destructor, std::to_string(popupId));
    }
    tipsInfo.popupId = popupId;
    tipsInfo.popupNode = popupNode;
    tipsInfo.isBlockEvent = param->IsBlockEvent();
    tipsInfo.isTips = true;
    if (popupNode) {
        popupNode->MarkModifyDone();
    }
    AddHoverEventForTips(param, targetNode, tipsInfo, showInSubWindow);
}

void ViewAbstract::AddHoverEventForTips(
    const RefPtr<PopupParam>& param, const RefPtr<FrameNode>& targetNode, PopupInfo& tipsInfo, bool showInSubWindow)
{
    tipsInfo.disappearingTimeWithContinuousOperation = param->GetDisappearingTimeWithContinuousOperation();
    tipsInfo.focusable = param->GetFocusable();
    tipsInfo.target = AceType::WeakClaim(AceType::RawPtr(targetNode));
    tipsInfo.targetSize = SizeF(param->GetTargetSize().Width(), param->GetTargetSize().Height());
    tipsInfo.targetOffset = OffsetF(param->GetTargetOffset().GetX(), param->GetTargetOffset().GetY());
    auto popupId = tipsInfo.popupId;
    auto popupNode = tipsInfo.popupNode;
    CHECK_NULL_VOID(popupNode);
    auto bubbleRenderProp = popupNode->GetPaintProperty<BubbleRenderProperty>();
    CHECK_NULL_VOID(bubbleRenderProp);
    bubbleRenderProp->UpdateAutoCancel(false);
    auto targetId = targetNode->GetId();
    auto context = targetNode->GetContext();
    CHECK_NULL_VOID(context);
    auto overlayManager = context->GetOverlayManager();
    auto eventHub = targetNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto inputHub = eventHub->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(inputHub);
    auto hoverTask = [targetNode, targetId, tipsInfo, param, overlayManager, showInSubWindow, popupId, popupNode](
                         bool isHover) {
        if (!overlayManager->GetPopupInfo(targetId).isTips && overlayManager->GetPopupInfo(targetId).popupNode) {
            return;
        }
        if (isHover) {
            BubbleView::UpdatePopupParam(popupId, param, targetNode);
            popupNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
            if (showInSubWindow) {
                SubwindowManager::GetInstance()->ShowTipsNG(
                    targetNode, tipsInfo, param->GetAppearingTime(), param->GetAppearingTimeWithContinuousOperation());
                return;
            }
            overlayManager->ShowTips(
                targetId, tipsInfo, param->GetAppearingTime(), param->GetAppearingTimeWithContinuousOperation(), false);
        } else {
            if (showInSubWindow) {
                SubwindowManager::GetInstance()->HideTipsNG(targetId, param->GetDisappearingTime());
                return;
            }
            overlayManager->HideTips(targetId, tipsInfo, param->GetDisappearingTime());
        }
    };
    auto hoverEvent = AceType::MakeRefPtr<InputEvent>(std::move(hoverTask));
    inputHub->AddOnHoverEvent(hoverEvent);
}

RefPtr<OverlayManager> ViewAbstract::GetCurOverlayManager(const RefPtr<UINode>& node)
{
    auto context = node->GetContextWithCheck();
    CHECK_NULL_RETURN(context, nullptr);
    if (GetTargetNodeIsInSubwindow(node)) {
        auto instanceId = context->GetInstanceId();
        auto subwindow = SubwindowManager::GetInstance()->GetSubwindowByType(instanceId, SubwindowType::TYPE_MENU);
        if (subwindow) {
            auto overlayManager = subwindow->GetOverlayManager();
            return overlayManager;
        } else {
            return nullptr;
        }
    }
    auto overlayManager = context->GetOverlayManager();
    return overlayManager;
}

bool ViewAbstract::GetTargetNodeIsInSubwindow(const RefPtr<UINode>& targetNode)
{
    CHECK_NULL_RETURN(targetNode, false);
    auto pipelineContext = targetNode->GetContext();
    CHECK_NULL_RETURN(pipelineContext, false);
    auto instanceId = pipelineContext->GetInstanceId();
    auto aceContainer = AceEngine::Get().GetContainer(instanceId);
    CHECK_NULL_RETURN(aceContainer, false);
    return aceContainer->IsSubContainer();
}

int32_t ViewAbstract::OpenPopup(const RefPtr<PopupParam>& param, const RefPtr<UINode>& customNode)
{
    if (!param) {
        TAG_LOGE(AceLogTag::ACE_DIALOG, "The param of popup is null.");
        return ERROR_CODE_INTERNAL_ERROR;
    }
    if (!customNode) {
        TAG_LOGE(AceLogTag::ACE_DIALOG, "The customNode of popup is null.");
        return ERROR_CODE_DIALOG_CONTENT_ERROR;
    }
    if (param->GetTargetId().empty() || std::stoi(param->GetTargetId()) < 0) {
        TAG_LOGE(AceLogTag::ACE_DIALOG, "The targetId is error.");
        return ERROR_CODE_TARGET_INFO_NOT_EXIST;
    }
    int32_t targetId = std::stoi(param->GetTargetId());
    auto targetNode = ElementRegister::GetInstance()->GetSpecificItemById<NG::FrameNode>(targetId);
    if (!targetNode) {
        TAG_LOGE(AceLogTag::ACE_DIALOG, "The targetNode does not exist when oepn popup.");
        return ERROR_CODE_TARGET_INFO_NOT_EXIST;
    }
    if (!targetNode->IsOnMainTree()) {
        TAG_LOGE(AceLogTag::ACE_DIALOG, "The targetNode does not on main tree.");
        return ERROR_CODE_TARGET_NOT_ON_COMPONENT_TREE;
    }
    auto popupInfo = BubbleView::GetPopupInfoWithCustomNode(customNode);
    if (popupInfo.popupNode) {
        TAG_LOGE(AceLogTag::ACE_DIALOG, "The customNode of popup is already existed.");
        return ERROR_CODE_DIALOG_CONTENT_ALREADY_EXIST;
    }
    auto overlayManager = BubbleView::GetPopupOverlayManager(customNode, targetId);
    if (overlayManager) {
        auto popupInfo = overlayManager->GetPopupInfo(targetId);
        if (popupInfo.popupNode) {
            popupInfo.markNeedUpdate = true;
            overlayManager->HidePopup(targetId, popupInfo, true);
        }
    }
    BindPopup(param, targetNode, customNode);
    popupInfo = BubbleView::GetPopupInfoWithTargetId(customNode, targetId);
    if (!popupInfo.popupNode) {
        TAG_LOGE(AceLogTag::ACE_DIALOG, "The popupNode of popup is null.");
        return ERROR_CODE_INTERNAL_ERROR;
    }
    auto popupPattern = popupInfo.popupNode->GetPattern<BubblePattern>();
    if (!popupPattern) {
        TAG_LOGE(AceLogTag::ACE_DIALOG, "The popupPattern does not exist.");
        return ERROR_CODE_INTERNAL_ERROR;
    }
    popupPattern->SetCustomNode(AceType::WeakClaim(AceType::RawPtr(customNode)));
    return ERROR_CODE_NO_ERROR;
}

int32_t ViewAbstract::UpdatePopup(const RefPtr<PopupParam>& param, const RefPtr<UINode>& customNode)
{
    if (!param) {
        TAG_LOGE(AceLogTag::ACE_DIALOG, "The param of popup is null.");
        return ERROR_CODE_INTERNAL_ERROR;
    }
    if (!customNode) {
        TAG_LOGE(AceLogTag::ACE_DIALOG, "The customNode of popup is null.");
        return ERROR_CODE_DIALOG_CONTENT_ERROR;
    }
    if (param->GetTargetId().empty() || std::stoi(param->GetTargetId()) < 0) {
        TAG_LOGE(AceLogTag::ACE_DIALOG, "The targetId is error.");
        return ERROR_CODE_INTERNAL_ERROR;
    }
    int32_t targetId = std::stoi(param->GetTargetId());
    auto targetNode = ElementRegister::GetInstance()->GetSpecificItemById<NG::FrameNode>(targetId);
    if (!targetNode) {
        TAG_LOGE(AceLogTag::ACE_DIALOG, "The targetNode does not exist when update popup.");
        return ERROR_CODE_INTERNAL_ERROR;
    }
    auto popupInfo = BubbleView::GetPopupInfoWithTargetId(customNode, targetId);
    if (!popupInfo.popupNode) {
        TAG_LOGE(AceLogTag::ACE_DIALOG, "The popupNode of popup is null.");
        return ERROR_CODE_INTERNAL_ERROR;
    }
    if (!popupInfo.isCurrentOnShow) {
        TAG_LOGE(AceLogTag::ACE_DIALOG, "The popup is not on show.");
        return ERROR_CODE_INTERNAL_ERROR;
    }
    BubbleView::ResetBubbleProperty(popupInfo.popupNode->GetId());
    BindPopup(param, targetNode, customNode);
    return ERROR_CODE_NO_ERROR;
}

int32_t ViewAbstract::ClosePopup(const RefPtr<UINode>& customNode)
{
    if (!customNode) {
        TAG_LOGE(AceLogTag::ACE_DIALOG, "The customNode of popup is null.");
        return ERROR_CODE_DIALOG_CONTENT_ERROR;
    }
    auto param = AceType::MakeRefPtr<PopupParam>();
    if (!param) {
        TAG_LOGE(AceLogTag::ACE_DIALOG, "The popupParam is null.");
        return ERROR_CODE_INTERNAL_ERROR;
    }
    auto result = GetPopupParam(param, customNode);
    if (result != ERROR_CODE_NO_ERROR) {
        TAG_LOGE(AceLogTag::ACE_DIALOG, "GetPopupParam failed");
        return result;
    }
    if (param->GetTargetId().empty() || std::stoi(param->GetTargetId()) < 0) {
        TAG_LOGE(AceLogTag::ACE_DIALOG, "The targetId is error.");
        return ERROR_CODE_INTERNAL_ERROR;
    }
    int32_t targetId = std::stoi(param->GetTargetId());
    auto overlayManager = BubbleView::GetPopupOverlayManager(customNode, targetId);
    if (!overlayManager) {
        TAG_LOGE(AceLogTag::ACE_DIALOG, "The overlayManager of popup is null.");
        return ERROR_CODE_INTERNAL_ERROR;
    }
    auto popupInfo = overlayManager->GetPopupInfo(targetId);
    if (!popupInfo.popupNode) {
        TAG_LOGE(AceLogTag::ACE_DIALOG, "The popupNode of popup is null.");
        return ERROR_CODE_INTERNAL_ERROR;
    }
    if (!popupInfo.isCurrentOnShow) {
        TAG_LOGE(AceLogTag::ACE_DIALOG, "The popup is not on show.");
        return ERROR_CODE_DIALOG_CONTENT_NOT_FOUND;
    }
    popupInfo.markNeedUpdate = true;
    overlayManager->HidePopup(targetId, popupInfo);
    return ERROR_CODE_NO_ERROR;
}

int32_t ViewAbstract::GetPopupParam(RefPtr<PopupParam>& param, const RefPtr<UINode>& customNode)
{
    CHECK_NULL_RETURN(param, ERROR_CODE_INTERNAL_ERROR);
    CHECK_NULL_RETURN(customNode, ERROR_CODE_DIALOG_CONTENT_ERROR);
    auto popupInfo = BubbleView::GetPopupInfoWithCustomNode(customNode);
    CHECK_NULL_RETURN(popupInfo.popupNode, ERROR_CODE_DIALOG_CONTENT_NOT_FOUND);
    auto popupPattern = popupInfo.popupNode->GetPattern<BubblePattern>();
    CHECK_NULL_RETURN(popupPattern, ERROR_CODE_INTERNAL_ERROR);
    param = popupPattern->GetPopupParam();
    CHECK_NULL_RETURN(param, ERROR_CODE_INTERNAL_ERROR);
    if (param->GetTargetId().empty() || std::stoi(param->GetTargetId()) < 0) {
        return ERROR_CODE_INTERNAL_ERROR;
    }
    return ERROR_CODE_NO_ERROR;
}

void ViewAbstract::DismissPopup()
{
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto overlayManager = context->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    overlayManager->DismissPopup();
}

void ViewAbstract::DismissDialog()
{
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto overlayManager = context->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    auto rootNode = overlayManager->GetRootNode().Upgrade();
    CHECK_NULL_VOID(rootNode);
    RefPtr<FrameNode> dialogNode;
    auto dialogId = DialogManager::GetInstance().GetDismissDialogId();
    auto dialogTag = DialogManager::GetInstance().GetDialogTag();
    if (dialogId && !dialogTag.empty()) {
        dialogNode = FrameNode::GetFrameNodeOnly(dialogTag, dialogId);
    }
    if (!dialogNode) {
        if (overlayManager->GetDismissDialogId()) {
            dialogNode = overlayManager->GetDialog(overlayManager->GetDismissDialogId());
        } else {
            dialogNode = AceType::DynamicCast<FrameNode>(rootNode->GetLastChild());
        }
    }
    CHECK_NULL_VOID(dialogNode);
    auto pattern = dialogNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    auto dialogPattern = AceType::DynamicCast<DialogPattern>(pattern);
    if (dialogPattern) {
        dialogPattern->OverlayDismissDialog(dialogNode);
        UiSessionManager::GetInstance()->ReportComponentChangeEvent("onVisibleChange", "destroy");
    }
}

void ViewAbstract::ShowMenuPreview(
    const RefPtr<FrameNode>& targetNode, const RefPtr<FrameNode>& wrapperNode, NG::MenuParam& menuParam)
{
#ifdef PREVIEW
    menuParam.previewMode = MenuPreviewMode::NONE;
#endif
    CHECK_NULL_VOID(targetNode);
    CHECK_NULL_VOID(wrapperNode);
    auto menuWrapperPattern = wrapperNode->GetPattern<NG::MenuWrapperPattern>();
    CHECK_NULL_VOID(menuWrapperPattern);
    if (menuParam.previewMode.value_or(MenuPreviewMode::NONE) == MenuPreviewMode::IMAGE || menuParam.isShowHoverImage) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(LayoutProperty, IsBindOverlay, true, targetNode);
        auto context = targetNode->GetRenderContext();
        CHECK_NULL_VOID(context);
        auto eventHub = targetNode->GetEventHub<EventHub>();
        CHECK_NULL_VOID(eventHub);
        auto gestureHub = eventHub->GetGestureEventHub();
        CHECK_NULL_VOID(gestureHub);
        auto pixelMap = context->GetThumbnailPixelMap();
        CHECK_NULL_VOID(pixelMap);
        gestureHub->SetPixelMap(pixelMap);
        menuWrapperPattern->SetIsShowFromUser(true);
        MenuView::GetMenuPixelMap(targetNode, menuParam, wrapperNode);
    }
}

int32_t ViewAbstract::OpenMenu(NG::MenuParam& menuParam, const RefPtr<NG::UINode>& customNode, const int32_t& targetId)
{
    if (!customNode) {
        TAG_LOGE(AceLogTag::ACE_DIALOG, "Content of menu is null.");
        return ERROR_CODE_DIALOG_CONTENT_ERROR;
    }
    auto targetNode = ElementRegister::GetInstance()->GetSpecificItemById<NG::FrameNode>(targetId);
    if (!targetNode) {
        TAG_LOGE(AceLogTag::ACE_DIALOG, "The targetNode does not exist.");
        return ERROR_CODE_TARGET_INFO_NOT_EXIST;
    }
    if (!targetNode->IsOnMainTree()) {
        TAG_LOGE(AceLogTag::ACE_DIALOG, "The targetNode does not on main tree.");
        return ERROR_CODE_TARGET_NOT_ON_COMPONENT_TREE;
    }
    auto overlayManager = GetCurOverlayManager(customNode);
    CHECK_NULL_RETURN(overlayManager, ERROR_CODE_INTERNAL_ERROR);
    if (overlayManager->GetMenuNodeWithExistContent(customNode)) {
        TAG_LOGW(AceLogTag::ACE_DIALOG, "Content of menu already existed.");
        return ERROR_CODE_DIALOG_CONTENT_ALREADY_EXIST;
    }
    auto isShowMenu = overlayManager->GetMenuNode(targetNode->GetId());
    if (isShowMenu) {
        // The menu is already opened, close the previous menu and open the new menu
        overlayManager->HideMenu(isShowMenu, targetNode->GetId(), false);
    }
    NG::MenuView::UpdatePreviewInfo(targetNode, menuParam);
    auto wrapperNode = NG::MenuView::Create(customNode, targetNode->GetId(), targetNode->GetTag(), menuParam);
    CHECK_NULL_RETURN(wrapperNode, ERROR_CODE_INTERNAL_ERROR);
    ShowMenuPreview(targetNode, wrapperNode, menuParam);
    auto menuWrapperPattern = wrapperNode->GetPattern<NG::MenuWrapperPattern>();
    CHECK_NULL_RETURN(menuWrapperPattern, ERROR_CODE_INTERNAL_ERROR);
    menuWrapperPattern->RegisterMenuCallback(wrapperNode, menuParam);
    menuWrapperPattern->SetMenuTransitionEffect(wrapperNode, menuParam);
    auto menu = menuWrapperPattern->GetMenu();
    CHECK_NULL_RETURN(menu, ERROR_CODE_INTERNAL_ERROR);
    auto menuPattern = AceType::DynamicCast<MenuPattern>(menu->GetPattern());
    CHECK_NULL_RETURN(menuPattern, ERROR_CODE_INTERNAL_ERROR);
    auto node = WeakPtr<UINode>(customNode);
    menuPattern->SetCustomNode(node);
    auto pipelineContext = targetNode->GetContext();
    CHECK_NULL_RETURN(pipelineContext, ERROR_CODE_INTERNAL_ERROR);
    auto theme = pipelineContext->GetTheme<SelectTheme>();
    CHECK_NULL_RETURN(theme, ERROR_CODE_INTERNAL_ERROR);
    menuWrapperPattern->SetIsOpenMenu(true);
    if (theme->GetExpandDisplay() && menuParam.isShowInSubWindow && targetNode->GetTag() != V2::SELECT_ETS_TAG) {
        SubwindowManager::GetInstance()->ShowMenuNG(wrapperNode, menuParam, targetNode, menuParam.positionOffset);
        return ERROR_CODE_NO_ERROR;
    }
    overlayManager->ShowMenu(targetNode->GetId(), menuParam.positionOffset, wrapperNode);
    return ERROR_CODE_NO_ERROR;
}

int32_t ViewAbstract::UpdateMenu(const NG::MenuParam& menuParam, const RefPtr<NG::UINode>& customNode)
{
    if (!customNode) {
        TAG_LOGE(AceLogTag::ACE_DIALOG, "Content of menu is null.");
        return ERROR_CODE_DIALOG_CONTENT_ERROR;
    }
    auto overlayManager = GetCurOverlayManager(customNode);
    if (!overlayManager) {
        return ERROR_CODE_INTERNAL_ERROR;
    }
    auto menuWrapperNode = overlayManager->GetMenuNodeWithExistContent(customNode);
    if (!menuWrapperNode) {
        return ERROR_CODE_DIALOG_CONTENT_NOT_FOUND;
    }
    auto wrapperPattern = AceType::DynamicCast<MenuWrapperPattern>(menuWrapperNode->GetPattern());
    CHECK_NULL_RETURN(wrapperPattern, ERROR_CODE_INTERNAL_ERROR);
    auto menu = wrapperPattern->GetMenu();
    CHECK_NULL_RETURN(menu, ERROR_CODE_INTERNAL_ERROR);
    wrapperPattern->SetMenuParam(menuParam);
    MenuView::UpdateMenuParam(menuWrapperNode, menu, menuParam);
    MenuView::UpdateMenuProperties(menuWrapperNode, menu, menuParam, menuParam.type);
    auto pipeline = menuWrapperNode->GetContextRefPtr();
    if (pipeline) {
        wrapperPattern->SetForceUpdateEmbeddedMenu(true);
    }
    auto menuPattern = AceType::DynamicCast<MenuPattern>(menu->GetPattern());
    CHECK_NULL_RETURN(menuPattern, ERROR_CODE_INTERNAL_ERROR);
    auto embeddedMenuItems = menuPattern->GetEmbeddedMenuItems();
    for (auto iter = embeddedMenuItems.begin(); iter != embeddedMenuItems.end(); ++iter) {
        auto menuItemPattern = (*iter)->GetPattern<MenuItemPattern>();
        if (!menuItemPattern) {
            continue;
        }
        menuItemPattern->HideEmbedded(false);
    }
    uint32_t minChildrenSize = 1;
    if (menuWrapperNode->GetChildren().size() > minChildrenSize) {
        auto subMenu = menuWrapperNode->GetChildren().back();
        if (subMenu && subMenu->GetTag() == V2::MENU_ETS_TAG) {
            wrapperPattern->HideSubMenu();
        }
    }
    menuWrapperNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    menu->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    if (pipeline) {
        pipeline->FlushUITasks();
        wrapperPattern->SetForceUpdateEmbeddedMenu(false);
    }
    return ERROR_CODE_NO_ERROR;
}

int32_t ViewAbstract::CloseMenu(const RefPtr<UINode>& customNode)
{
    if (!customNode) {
        TAG_LOGE(AceLogTag::ACE_DIALOG, "Content of menu is null.");
        return ERROR_CODE_DIALOG_CONTENT_ERROR;
    }
    auto overlayManager = GetCurOverlayManager(customNode);
    if (!overlayManager) {
        return ERROR_CODE_INTERNAL_ERROR;
    }
    auto menuWrapperNode = overlayManager->GetMenuNodeWithExistContent(customNode);
    if (!menuWrapperNode) {
        return ERROR_CODE_DIALOG_CONTENT_NOT_FOUND;
    }
    overlayManager->HideMenu(menuWrapperNode, customNode->GetId(), false);
    return ERROR_CODE_NO_ERROR;
}

void ViewAbstract::BindMenuWithItems(std::vector<OptionParam>&& params, const RefPtr<FrameNode>& targetNode,
    const NG::OffsetF& offset, const MenuParam& menuParam)
{
    TAG_LOGD(AceLogTag::ACE_DIALOG, "bind menu with items enter");
    CHECK_NULL_VOID(targetNode);

    if (params.empty()) {
        return;
    }
    auto menuNode =
        MenuView::Create(std::move(params), targetNode->GetId(), targetNode->GetTag(), MenuType::MENU, menuParam);
    CHECK_NULL_VOID(menuNode);
    auto menuWrapperPattern = menuNode->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(menuWrapperPattern);
    menuWrapperPattern->RegisterMenuCallback(menuNode, menuParam);
    menuWrapperPattern->SetMenuTransitionEffect(menuNode, menuParam);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    auto expandDisplay = theme->GetExpandDisplay();

    auto pipelineContext = targetNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto overlayManager = pipelineContext->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);

    if (expandDisplay && menuParam.isShowInSubWindow && targetNode->GetTag() != V2::SELECT_ETS_TAG) {
        SubwindowManager::GetInstance()->ShowMenuNG(menuNode, menuParam, targetNode, offset);
        return;
    }

    overlayManager->ShowMenu(targetNode->GetId(), offset, menuNode);
}

void ViewAbstract::BindMenuWithCustomNode(std::function<void()>&& buildFunc, const RefPtr<FrameNode>& targetNode,
    const NG::OffsetF& offset, MenuParam menuParam, std::function<void()>&& previewBuildFunc)
{
    if (!buildFunc || !targetNode) {
        return;
    }
#ifdef PREVIEW
    // unable to use the subWindow in the Previewer.
    menuParam.type = MenuType::MENU;
#endif
    TAG_LOGD(AceLogTag::ACE_DIALOG, "bind menu with custom node enter %{public}d", menuParam.type);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    auto expandDisplay = theme->GetExpandDisplay();
    auto pipelineContext = targetNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto overlayManager = pipelineContext->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    if (menuParam.type == MenuType::CONTEXT_MENU) {
        SubwindowManager::GetInstance()->ShowMenuNG(
            std::move(buildFunc), std::move(previewBuildFunc), menuParam, targetNode, offset);
        return;
    }
    if (menuParam.type == MenuType::MENU && expandDisplay && menuParam.isShowInSubWindow &&
        targetNode->GetTag() != V2::SELECT_ETS_TAG) {
        SubwindowManager::GetInstance()->ShowMenuNG(
            std::move(buildFunc), std::move(previewBuildFunc), menuParam, targetNode, offset);
        return;
    }
    NG::ScopedViewStackProcessor builderViewStackProcessor;
    buildFunc();
    auto customNode = NG::ViewStackProcessor::GetInstance()->Finish();
    RefPtr<NG::UINode> previewCustomNode;
    if (previewBuildFunc && menuParam.previewMode.value_or(MenuPreviewMode::NONE) == MenuPreviewMode::CUSTOM) {
        previewBuildFunc();
        previewCustomNode = NG::ViewStackProcessor::GetInstance()->Finish();
    }
    auto menuNode =
        NG::MenuView::Create(customNode, targetNode->GetId(), targetNode->GetTag(), menuParam, true, previewCustomNode);
    auto menuWrapperPattern = menuNode->GetPattern<NG::MenuWrapperPattern>();
    CHECK_NULL_VOID(menuWrapperPattern);
    menuWrapperPattern->RegisterMenuCallback(menuNode, menuParam);
    menuWrapperPattern->SetMenuTransitionEffect(menuNode, menuParam);
    overlayManager->ShowMenu(targetNode->GetId(), offset, menuNode);
}

void ViewAbstract::SetBackdropBlur(const Dimension& radius, const BlurOption& blurOption, const SysOptions& sysOptions)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto target = frameNode->GetRenderContext();
    if (target) {
        if (target->GetBackgroundEffect().has_value()) {
            target->UpdateBackgroundEffect(std::nullopt);
        }
        target->UpdateBackBlur(radius, blurOption, sysOptions);
        if (target->GetBackBlurStyle().has_value()) {
            target->UpdateBackBlurStyle(std::nullopt);
        }
    }
}

void ViewAbstract::SetNodeBackdropBlur(FrameNode *frameNode, const Dimension& radius, const BlurOption& blurOption)
{
    CHECK_NULL_VOID(frameNode);
    auto target = frameNode->GetRenderContext();
    if (target) {
        if (target->GetBackgroundEffect().has_value()) {
            target->UpdateBackgroundEffect(std::nullopt);
        }
        if (target->GetBackBlurStyle().has_value()) {
            target->UpdateBackBlurStyle(std::nullopt);
        }
        target->UpdateNodeBackBlur(radius, blurOption);
    }
}

void ViewAbstract::SetBackdropBlur(
    FrameNode* frameNode, const Dimension& radius, const BlurOption& blurOption, const SysOptions& sysOptions)
{
    CHECK_NULL_VOID(frameNode);
    auto target = frameNode->GetRenderContext();
    if (target) {
        if (target->GetBackgroundEffect().has_value()) {
            target->UpdateBackgroundEffect(std::nullopt);
        }
        target->UpdateBackBlur(radius, blurOption, sysOptions);
        if (target->GetBackBlurStyle().has_value()) {
            target->UpdateBackBlurStyle(std::nullopt);
        }
    }
}

void ViewAbstract::SetLinearGradientBlur(const NG::LinearGradientBlurPara& blurPara)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(LinearGradientBlur, blurPara);
}

void ViewAbstract::SetDynamicLightUp(float rate, float lightUpDegree)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(DynamicLightUpRate, rate);
    ACE_UPDATE_RENDER_CONTEXT(DynamicLightUpDegree, lightUpDegree);
}

void ViewAbstract::SetBgDynamicBrightness(const BrightnessOption& brightnessOption)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(BgDynamicBrightnessOption, brightnessOption);
}

void ViewAbstract::SetFgDynamicBrightness(const BrightnessOption& brightnessOption)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(FgDynamicBrightnessOption, brightnessOption);
}

void ViewAbstract::SetBrightnessBlender(const OHOS::Rosen::BrightnessBlender* brightnessBlender)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(BrightnessBlender, brightnessBlender);
}

void ViewAbstract::SetFrontBlur(const Dimension& radius, const BlurOption& blurOption, const SysOptions& sysOptions)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto target = frameNode->GetRenderContext();
    if (target) {
        target->UpdateFrontBlur(radius, blurOption, sysOptions);
        if (target->GetFrontBlurStyle().has_value()) {
            target->UpdateFrontBlurStyle(std::nullopt);
        }
    }
}

void ViewAbstract::SetDynamicDim(float DimDegree)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(DynamicDimDegree, DimDegree);
}

void ViewAbstract::SetFrontBlur(
    FrameNode* frameNode, const Dimension& radius, const BlurOption& blurOption, const SysOptions& sysOptions)
{
    CHECK_NULL_VOID(frameNode);
    auto target = frameNode->GetRenderContext();
    if (target) {
        target->UpdateFrontBlur(radius, blurOption, sysOptions);
        if (target->GetFrontBlurStyle().has_value()) {
            target->UpdateFrontBlurStyle(std::nullopt);
        }
    }
}

void ViewAbstract::SetBackShadow(const Shadow& shadow)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(BackShadow, shadow);
}

void ViewAbstract::SetBackShadow(FrameNode* frameNode, const Shadow& shadow)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(BackShadow, shadow, frameNode);
}

void ViewAbstract::SetBlendMode(BlendMode blendMode)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(BackBlendMode, blendMode);
}

void ViewAbstract::SetBlendApplyType(BlendApplyType blendApplyType)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(BackBlendApplyType, blendApplyType);
}

void ViewAbstract::SetLinearGradient(const NG::Gradient& gradient)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(LastGradientType, NG::GradientType::LINEAR);
    ACE_UPDATE_RENDER_CONTEXT(LinearGradient, gradient);
}

void ViewAbstract::SetSweepGradient(const NG::Gradient& gradient)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(LastGradientType, NG::GradientType::SWEEP);
    ACE_UPDATE_RENDER_CONTEXT(SweepGradient, gradient);
}

void ViewAbstract::SetRadialGradient(const NG::Gradient& gradient)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(LastGradientType, NG::GradientType::RADIAL);
    ACE_UPDATE_RENDER_CONTEXT(RadialGradient, gradient);
}

void ViewAbstract::SetInspectorId(const std::string& inspectorId)
{
    auto& uiNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
    if (uiNode) {
        if (uiNode->GetInspectorId().has_value() && uiNode->GetInspectorIdValue() != inspectorId) {
            ElementRegister::GetInstance()->RemoveFrameNodeByInspectorId(
                uiNode->GetInspectorIdValue(), uiNode->GetId());
        }
        uiNode->UpdateInspectorId(inspectorId);
    }
}

void ViewAbstract::SetAutoEventParam(const std::string& param)
{
    auto& uiNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
    if (uiNode) {
        uiNode->UpdateAutoEventParam(param);
    }
}

void ViewAbstract::SetRestoreId(int32_t restoreId)
{
    auto& uiNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
    if (uiNode) {
        uiNode->SetRestoreId(restoreId);
    }
}

void ViewAbstract::SetDebugLine(const std::string& line)
{
    auto& uiNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
    if (uiNode) {
        uiNode->SetDebugLine(line);
    }
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
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(Transition, options);
}

void ViewAbstract::CleanTransition()
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto target = frameNode->GetRenderContext();
    if (target) {
        target->CleanTransition();
    }
}

void ViewAbstract::SetChainedTransition(
    const RefPtr<NG::ChainedTransitionEffect>& effect, NG::TransitionFinishCallback&& finishCallback)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    const auto& target = frameNode->GetRenderContext();
    if (target) {
        target->UpdateChainedTransition(effect);
        target->SetTransitionUserCallback(std::move(finishCallback));
    }
}

void ViewAbstract::SetClipShape(const RefPtr<BasicShape>& basicShape)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto target = frameNode->GetRenderContext();
    if (target) {
        if (target->GetClipEdge().has_value()) {
            target->UpdateClipEdge(false);
        }
        target->UpdateClipShape(basicShape);
    }
}

void ViewAbstract::SetClipShape(FrameNode* frameNode, const RefPtr<BasicShape>& basicShape)
{
    CHECK_NULL_VOID(frameNode);
    auto target = frameNode->GetRenderContext();
    if (target) {
        if (target->GetClipEdge().has_value()) {
            target->UpdateClipEdge(false);
        }
        target->UpdateClipShape(basicShape);
    }
}

void ViewAbstract::SetClipEdge(bool isClip)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto target = frameNode->GetRenderContext();
    if (target) {
        if (target->GetClipShape().has_value()) {
            target->ResetClipShape();
            target->OnClipShapeUpdate(nullptr);
        }
        target->UpdateClipEdge(isClip);
    }
}

void ViewAbstract::SetClipEdge(FrameNode* frameNode, bool isClip)
{
    CHECK_NULL_VOID(frameNode);
    auto target = frameNode->GetRenderContext();
    if (target) {
        if (target->GetClipShape().has_value()) {
            target->ResetClipShape();
            target->OnClipShapeUpdate(nullptr);
        }
        target->UpdateClipEdge(isClip);
    }
}

void ViewAbstract::SetMask(const RefPtr<BasicShape>& basicShape)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto target = frameNode->GetRenderContext();
    if (target) {
        if (target->HasProgressMask()) {
            target->ResetProgressMask();
            target->OnProgressMaskUpdate(nullptr);
        }
        target->UpdateClipMask(basicShape);
    }
}

void ViewAbstract::SetProgressMask(const RefPtr<ProgressMaskProperty>& progress)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto target = frameNode->GetRenderContext();
    if (target) {
        if (target->HasClipMask()) {
            target->ResetClipMask();
            target->OnClipMaskUpdate(nullptr);
        }
        target->UpdateProgressMask(progress);
    }
}

void ViewAbstract::SetBrightness(const Dimension& brightness)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(FrontBrightness, brightness);
}

void ViewAbstract::SetBrightness(FrameNode* frameNode, const Dimension& brightness)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(FrontBrightness, brightness, frameNode);
}

void ViewAbstract::SetGrayScale(const Dimension& grayScale)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(FrontGrayScale, grayScale);
}

void ViewAbstract::SetGrayScale(FrameNode* frameNode, const Dimension& grayScale)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(FrontGrayScale, grayScale, frameNode);
}

void ViewAbstract::SetContrast(const Dimension& contrast)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(FrontContrast, contrast);
}

void ViewAbstract::SetContrast(FrameNode* frameNode, const Dimension& contrast)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(FrontContrast, contrast, frameNode);
}

void ViewAbstract::SetSaturate(const Dimension& saturate)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(FrontSaturate, saturate);
}

void ViewAbstract::SetSaturate(FrameNode* frameNode, const Dimension& saturate)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(FrontSaturate, saturate, frameNode);
}

void ViewAbstract::SetSepia(const Dimension& sepia)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(FrontSepia, sepia);
}

void ViewAbstract::SetSepia(FrameNode* frameNode, const Dimension& sepia)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(FrontSepia, sepia, frameNode);
}

void ViewAbstract::SetInvert(const InvertVariant& invert)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(FrontInvert, invert);
}

void ViewAbstract::SetInvert(FrameNode* frameNode, const InvertVariant& invert)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(FrontInvert, invert, frameNode);
}

void ViewAbstract::SetSystemBarEffect(bool systemBarEffect)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(SystemBarEffect, systemBarEffect);
}

void ViewAbstract::SetSystemBarEffect(FrameNode *frameNode, bool enable)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(SystemBarEffect, enable, frameNode);
}

void ViewAbstract::SetHueRotate(float hueRotate)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(FrontHueRotate, hueRotate);
}

void ViewAbstract::SetHueRotate(FrameNode* frameNode, float hueRotate)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(FrontHueRotate, hueRotate, frameNode);
}

void ViewAbstract::SetColorBlend(const Color& colorBlend)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(FrontColorBlend, colorBlend);
}

void ViewAbstract::SetColorBlend(FrameNode* frameNode, const Color& colorBlend)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(FrontColorBlend, colorBlend, frameNode);
}

void ViewAbstract::SetBorderImage(const RefPtr<BorderImage>& borderImage)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(BorderImage, borderImage);
}

void ViewAbstract::SetBorderImageSource(
    const std::string& bdImageSrc, const std::string& bundleName, const std::string& moduleName)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ImageSourceInfo imageSourceInfo(bdImageSrc, bundleName, moduleName);
    ACE_UPDATE_RENDER_CONTEXT(BorderImageSource, imageSourceInfo);
    ACE_UPDATE_RENDER_CONTEXT(BorderSourceFromImage, true);
}

void ViewAbstract::SetHasBorderImageSlice(bool tag)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(HasBorderImageSlice, tag);
}

void ViewAbstract::SetHasBorderImageWidth(bool tag)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(HasBorderImageWidth, tag);
}

void ViewAbstract::SetHasBorderImageOutset(bool tag)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(HasBorderImageOutset, tag);
}

void ViewAbstract::SetHasBorderImageRepeat(bool tag)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(HasBorderImageRepeat, tag);
}

void ViewAbstract::SetBorderImageGradient(const Gradient& gradient)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(BorderImageGradient, gradient);
    ACE_UPDATE_RENDER_CONTEXT(BorderSourceFromImage, false);
}

std::mutex ViewAbstract::visualEffectMutex_;
OEMVisualEffectFunc ViewAbstract::oemVisualEffectFunc = nullptr;
void ViewAbstract::RegisterOEMVisualEffect(OEMVisualEffectFunc func)
{
    std::lock_guard<std::mutex> lock(visualEffectMutex_);
    ViewAbstract::oemVisualEffectFunc = func;
}

void ViewAbstract::SetVisualEffect(const OHOS::Rosen::VisualEffect* visualEffect)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }

    std::lock_guard<std::mutex> lock(visualEffectMutex_);
    if (!oemVisualEffectFunc) {
        ACE_UPDATE_RENDER_CONTEXT(VisualEffect, visualEffect);
    } else {
        Rosen::VisualEffect* graphicVisualEffect = oemVisualEffectFunc(visualEffect);
        ACE_UPDATE_RENDER_CONTEXT(VisualEffect, graphicVisualEffect);
    }
}

void ViewAbstract::SetBackgroundFilter(const OHOS::Rosen::Filter* backgroundFilter)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(BackgroundFilter, backgroundFilter);
}

void ViewAbstract::SetForegroundFilter(const OHOS::Rosen::Filter* foregroundFilter)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(ForegroundFilter, foregroundFilter);
}

void ViewAbstract::SetCompositingFilter(const OHOS::Rosen::Filter* compositingFilter)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(CompositingFilter, compositingFilter);
}

void ViewAbstract::SetOverlay(const OverlayOptions& overlay)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(OverlayText, overlay);
}

void ViewAbstract::SetOverlayBuilder(std::function<void()>&& buildFunc,
    const std::optional<Alignment>& align, const std::optional<Dimension>& offsetX,
    const std::optional<Dimension>& offsetY)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    if (buildFunc) {
        auto buildNodeFunc = [func = std::move(buildFunc)]() -> RefPtr<UINode> {
            ScopedViewStackProcessor builderViewStackProcessor;
            func();
            auto customNode = ViewStackProcessor::GetInstance()->Finish();
            return customNode;
        };
        auto node = buildNodeFunc();
        auto overlayNode = AceType::DynamicCast<FrameNode>(node);
        if (!overlayNode && node) {
            auto* stack = ViewStackProcessor::GetInstance();
            auto nodeId = stack->ClaimNodeId();
            auto stackNode = FrameNode::CreateFrameNode(V2::STACK_ETS_TAG, nodeId, AceType::MakeRefPtr<StackPattern>());
            stackNode->AddChild(node);
            overlayNode = stackNode;
        }
        AddOverlayToFrameNode(overlayNode, align, offsetX, offsetY);
    } else {
        AddOverlayToFrameNode(nullptr, align, offsetX, offsetY);
    }
}

void ViewAbstract::SetOverlayComponentContent(const RefPtr<NG::FrameNode>& contentNode,
    const std::optional<Alignment>& align, const std::optional<Dimension>& offsetX,
    const std::optional<Dimension>& offsetY)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    AddOverlayToFrameNode(contentNode, align, offsetX, offsetY);
}

void ViewAbstract::AddOverlayToFrameNode(const RefPtr<NG::FrameNode>& overlayNode,
    const std::optional<Alignment>& align, const std::optional<Dimension>& offsetX,
    const std::optional<Dimension>& offsetY)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    if (overlayNode == nullptr) {
        frameNode->SetOverlayNode(nullptr);
        return;
    }
    frameNode->SetOverlayNode(overlayNode);
    overlayNode->SetParent(AceType::WeakClaim(frameNode));
    overlayNode->SetActive(true);
    overlayNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    auto layoutProperty = AceType::DynamicCast<LayoutProperty>(overlayNode->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->SetIsOverlayNode(true);
    layoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
    layoutProperty->UpdateAlignment(align.value_or(Alignment::TOP_LEFT));
    layoutProperty->SetOverlayOffset(offsetX, offsetY);
    auto renderContext = overlayNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateZIndex(INT32_MAX);
    auto focusHub = overlayNode->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->SetFocusable(false);
}

void ViewAbstract::SetMotionPath(const MotionPathOption& motionPath)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
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

void ViewAbstract::SetMask(FrameNode* frameNode, const RefPtr<BasicShape>& basicShape)
{
    CHECK_NULL_VOID(frameNode);
    auto target = frameNode->GetRenderContext();
    if (target) {
        if (target->HasProgressMask()) {
            target->ResetProgressMask();
            target->OnProgressMaskUpdate(nullptr);
        }
        target->UpdateClipMask(basicShape);
    }
}

void ViewAbstract::SetProgressMask(FrameNode* frameNode, const RefPtr<ProgressMaskProperty>& progress)
{
    CHECK_NULL_VOID(frameNode);
    auto target = frameNode->GetRenderContext();
    if (target) {
        if (target->HasClipMask()) {
            target->ResetClipMask();
            target->OnClipMaskUpdate(nullptr);
        }
        target->UpdateProgressMask(progress);
    }
}

void ViewAbstract::SetUseEffect(bool useEffect, EffectType effectType)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    SetUseEffect(frameNode, useEffect, effectType);
}

void ViewAbstract::SetFreeze(bool freeze)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(Freeze, freeze);
}

void ViewAbstract::SetUseShadowBatching(bool useShadowBatching)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(UseShadowBatching, useShadowBatching);
}

void ViewAbstract::SetForegroundColor(const Color& color)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    if (renderContext->GetForegroundColorStrategy().has_value()) {
        renderContext->UpdateForegroundColorStrategy(ForegroundColorStrategy::NONE);
        renderContext->ResetForegroundColorStrategy();
    }
    renderContext->UpdateForegroundColor(color);
    renderContext->UpdateForegroundColorFlag(true);
}

void ViewAbstract::SetForegroundColorStrategy(const ForegroundColorStrategy& strategy)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
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
    if (value.empty()) {
        eventHub->ClearSingleKeyboardShortcut();
        return;
    }
    auto key = eventManager->GetKeyboardShortcutKeys(keys);
    if ((key == 0 && value.length() == 1) || (key == 0 && keys.size() > 0 && value.length() > 1)) {
        return;
    }
    if (eventManager->IsSameKeyboardShortcutNode(value, key)) {
        return;
    }
    eventHub->SetKeyboardShortcut(value, key, std::move(onKeyboardShortcutAction));
    eventManager->AddKeyboardShortcutNode(AceType::WeakClaim(frameNode));
}

void ViewAbstract::CreateAnimatablePropertyFloat(
    const std::string& propertyName, float value, const std::function<void(float)>& onCallbackEvent)
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

void ViewAbstract::UpdateAnimatableArithmeticProperty(
    const std::string& propertyName, RefPtr<CustomAnimatableArithmetic>& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    frameNode->UpdateAnimatableArithmeticProperty(propertyName, value);
}

void ViewAbstract::SetObscured(const std::vector<ObscuredReasons>& reasons)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(Obscured, reasons);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void ViewAbstract::SetPrivacySensitive(bool flag)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    frameNode->SetPrivacySensitive(flag);
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void ViewAbstract::SetPrivacySensitive(FrameNode* frameNode, bool flag)
{
    CHECK_NULL_VOID(frameNode);
    frameNode->SetPrivacySensitive(flag);
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void ViewAbstract::UpdateSafeAreaExpandOpts(const SafeAreaExpandOpts& opts)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, SafeAreaExpandOpts, opts);
}

void ViewAbstract::SetRenderGroup(bool isRenderGroup)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(RenderGroup, isRenderGroup);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    frameNode->SetApplicationRenderGroupMarked(true);
}

void ViewAbstract::SetRenderFit(RenderFit renderFit)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(RenderFit, renderFit);
}

void ViewAbstract::SetAttractionEffect(const AttractionEffect& effect)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(AttractionEffect, effect);
}

void ViewAbstract::SetBorderRadius(FrameNode *frameNode, const BorderRadiusProperty& value)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(BorderRadius, value, frameNode);
}

void ViewAbstract::SetBorderRadius(FrameNode* frameNode, const Dimension& value)
{
    BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(value);
    borderRadius.multiValued = false;
    ACE_UPDATE_NODE_RENDER_CONTEXT(BorderRadius, borderRadius, frameNode);
}

void ViewAbstract::SetBorderWidth(FrameNode* frameNode, const BorderWidthProperty& value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LayoutProperty, BorderWidth, value, frameNode);
    ACE_UPDATE_NODE_RENDER_CONTEXT(BorderWidth, value, frameNode);
}

void ViewAbstract::SetBorderWidth(FrameNode* frameNode, const Dimension& value)
{
    BorderWidthProperty borderWidth;
    if (Negative(value.Value())) {
        borderWidth.SetBorderWidth(Dimension(0));
        LOGW("border width is negative, reset to 0");
    } else {
        borderWidth.SetBorderWidth(value);
    }
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LayoutProperty, BorderWidth, borderWidth, frameNode);
    ACE_UPDATE_NODE_RENDER_CONTEXT(BorderWidth, borderWidth, frameNode);
}

void ViewAbstract::SetBorderColor(FrameNode* frameNode, const BorderColorProperty& value)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(BorderColor, value, frameNode);
}

void ViewAbstract::SetBorderColor(FrameNode* frameNode, const Color& value)
{
    BorderColorProperty borderColor;
    borderColor.SetColor(value);
    ACE_UPDATE_NODE_RENDER_CONTEXT(BorderColor, borderColor, frameNode);
}

void ViewAbstract::SetWidth(FrameNode* frameNode, const CalcLength& width)
{
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

void ViewAbstract::SetHeight(FrameNode* frameNode, const CalcLength& height)
{
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    std::optional<CalcLength> width = std::nullopt;
    auto&& layoutConstraint = layoutProperty->GetCalcLayoutConstraint();
    if (layoutConstraint && layoutConstraint->selfIdealSize) {
        width = layoutConstraint->selfIdealSize->Width();
    }
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(width, height));
}

void ViewAbstract::ClearWidthOrHeight(FrameNode* frameNode, bool isWidth)
{
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->ClearUserDefinedIdealSize(isWidth, !isWidth);
}

void ViewAbstract::SetPosition(FrameNode* frameNode, const OffsetT<Dimension>& value)
{
    CHECK_NULL_VOID(frameNode);
    CheckIfParentNeedMarkDirty(frameNode);
    ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, PositionEdges, frameNode);
    ACE_UPDATE_NODE_RENDER_CONTEXT(Position, value, frameNode);
}

void ViewAbstract::SetPositionEdges(FrameNode* frameNode, const EdgesParam& value)
{
    CHECK_NULL_VOID(frameNode);
    CheckIfParentNeedMarkDirty(frameNode);
    ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, Position, frameNode);
    ACE_UPDATE_NODE_RENDER_CONTEXT(PositionEdges, value, frameNode);
}

void ViewAbstract::ResetPosition(FrameNode* frameNode)
{
    ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, Position, frameNode);
    ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, PositionEdges, frameNode);
    CHECK_NULL_VOID(frameNode);
    auto parentNode = frameNode->GetAncestorNodeOfFrame(false);
    CHECK_NULL_VOID(parentNode);
    auto parentPattern = parentNode->GetPattern();

    if (parentNode->GetTag() == V2::COLUMN_ETS_TAG || parentNode->GetTag() == V2::ROW_ETS_TAG ||
        parentNode->GetTag() == V2::FLEX_ETS_TAG) {
        frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    } else {
        auto renderContext = frameNode->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        renderContext->RecalculatePosition();
    }
}

void ViewAbstract::SetTransformMatrix(FrameNode* frameNode, const Matrix4& matrix)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(TransformMatrix, matrix, frameNode);
}

void ViewAbstract::SetHitTestMode(FrameNode* frameNode, HitTestMode hitTestMode)
{
    CHECK_NULL_VOID(frameNode);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->SetHitTestMode(hitTestMode);
}

void ViewAbstract::SetOpacity(FrameNode* frameNode, double opacity)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(Opacity, opacity, frameNode);
}

void ViewAbstract::SetZIndex(FrameNode* frameNode, int32_t value)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(ZIndex, value, frameNode);
}

void ViewAbstract::SetLinearGradient(FrameNode* frameNode, const NG::Gradient& gradient)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(LastGradientType, NG::GradientType::LINEAR, frameNode);
    ACE_UPDATE_NODE_RENDER_CONTEXT(LinearGradient, gradient, frameNode);
}

void ViewAbstract::SetSweepGradient(FrameNode* frameNode, const NG::Gradient& gradient)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(LastGradientType, NG::GradientType::SWEEP, frameNode);
    ACE_UPDATE_NODE_RENDER_CONTEXT(SweepGradient, gradient, frameNode);
}

void ViewAbstract::SetRadialGradient(FrameNode* frameNode, const NG::Gradient& gradient)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(LastGradientType, NG::GradientType::RADIAL, frameNode);
    ACE_UPDATE_NODE_RENDER_CONTEXT(RadialGradient, gradient, frameNode);
}

void ViewAbstract::SetOverlay(FrameNode* frameNode, const NG::OverlayOptions& overlay)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(OverlayText, overlay, frameNode);
}

void ViewAbstract::SetBorderImage(FrameNode* frameNode, const RefPtr<BorderImage>& borderImage)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(BorderImage, borderImage, frameNode);
}

void ViewAbstract::SetBorderImageSource(FrameNode* frameNode, const std::string& bdImageSrc)
{
    ImageSourceInfo imageSourceInfo(bdImageSrc);
    ACE_UPDATE_NODE_RENDER_CONTEXT(BorderImageSource, imageSourceInfo, frameNode);
    ACE_UPDATE_NODE_RENDER_CONTEXT(BorderSourceFromImage, true, frameNode);
}

void ViewAbstract::SetHasBorderImageSlice(FrameNode* frameNode, bool tag)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(HasBorderImageSlice, tag, frameNode);
}

void ViewAbstract::SetHasBorderImageWidth(FrameNode* frameNode, bool tag)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(HasBorderImageWidth, tag, frameNode);
}

void ViewAbstract::SetHasBorderImageOutset(FrameNode* frameNode, bool tag)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(HasBorderImageOutset, tag, frameNode);
}

void ViewAbstract::SetHasBorderImageRepeat(FrameNode* frameNode, bool tag)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(HasBorderImageRepeat, tag, frameNode);
}

void ViewAbstract::SetBorderImageGradient(FrameNode* frameNode, const NG::Gradient& gradient)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(BorderImageGradient, gradient, frameNode);
    ACE_UPDATE_NODE_RENDER_CONTEXT(BorderSourceFromImage, false, frameNode);
}

void ViewAbstract::SetForegroundBlurStyle(
    FrameNode* frameNode, const BlurStyleOption& fgBlurStyle, const SysOptions& sysOptions)
{
    const auto target = frameNode->GetRenderContext();
    if (target) {
        target->UpdateFrontBlurStyle(fgBlurStyle, sysOptions);
        if (target->GetFrontBlurRadius().has_value()) {
            target->UpdateFrontBlurRadius(Dimension());
        }
    }
}

void ViewAbstract::SetLinearGradientBlur(FrameNode *frameNode, const NG::LinearGradientBlurPara& blurPara)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(LinearGradientBlur, blurPara, frameNode);
}

void ViewAbstract::SetMagnifier(FrameNode* frameNode, const MagnifierParams& magnifierOffset)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(Magnifier, magnifierOffset, frameNode);
}

void ViewAbstract::ReSetMagnifier(FrameNode* frameNode)
{
    ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, Magnifier, frameNode);
}

void ViewAbstract::SetBackgroundBlurStyle(
    FrameNode* frameNode, const BlurStyleOption& bgBlurStyle, const SysOptions& sysOptions)
{
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    if (bgBlurStyle.policy == BlurStyleActivePolicy::FOLLOWS_WINDOW_ACTIVE_STATE) {
        pipeline->AddWindowFocusChangedCallback(frameNode->GetId());
    } else {
        pipeline->RemoveWindowFocusChangedCallback(frameNode->GetId());
    }
    auto target = frameNode->GetRenderContext();
    if (target) {
        if (target->GetBackgroundEffect().has_value()) {
            target->UpdateBackgroundEffect(std::nullopt);
        }
        target->UpdateBackBlurStyle(bgBlurStyle, sysOptions);
        if (target->GetBackBlurRadius().has_value()) {
            target->UpdateBackBlurRadius(Dimension());
        }
    }
}

void ViewAbstract::SetPixelStretchEffect(FrameNode* frameNode, PixStretchEffectOption& option)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(PixelStretchEffect, option, frameNode);
}

void ViewAbstract::SetLightUpEffect(FrameNode* frameNode, double radio)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(LightUpEffect, radio, frameNode);
}

void ViewAbstract::SetSphericalEffect(FrameNode* frameNode, double radio)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(SphericalEffect, radio, frameNode);
}

void ViewAbstract::SetRenderGroup(FrameNode* frameNode, bool isRenderGroup)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(RenderGroup, isRenderGroup, frameNode);
    CHECK_NULL_VOID(frameNode);
    frameNode->SetApplicationRenderGroupMarked(true);
}

void ViewAbstract::SetRenderFit(FrameNode* frameNode, RenderFit renderFit)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(RenderFit, renderFit, frameNode);
}

void ViewAbstract::SetUseEffect(FrameNode* frameNode, bool useEffect, EffectType effectType)
{
    CHECK_NULL_VOID(frameNode);
    auto* pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    if (useEffect && effectType == EffectType::WINDOW_EFFECT) {
        pipeline->AddWindowActivateChangedCallback(frameNode->GetId());
    } else {
        pipeline->RemoveWindowActivateChangedCallback(frameNode->GetId());
    }
    const auto& target = frameNode->GetRenderContext();
    if (target) {
        target->UpdateUseEffect(useEffect);
        target->UpdateUseEffectType(effectType);
    }
}

void ViewAbstract::SetForegroundColor(FrameNode* frameNode, const Color& color)
{
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    if (renderContext->GetForegroundColorStrategy().has_value()) {
        renderContext->UpdateForegroundColorStrategy(ForegroundColorStrategy::NONE);
        renderContext->ResetForegroundColorStrategy();
    }
    renderContext->UpdateForegroundColor(color);
    renderContext->UpdateForegroundColorFlag(true);
}

void ViewAbstract::SetForegroundColorStrategy(FrameNode* frameNode, const ForegroundColorStrategy& strategy)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(ForegroundColorStrategy, strategy, frameNode);
    ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, ForegroundColor, frameNode);
    ACE_UPDATE_NODE_RENDER_CONTEXT(ForegroundColorFlag, true, frameNode);
}

void ViewAbstract::SetLightPosition(
    const CalcDimension& positionX, const CalcDimension& positionY, const CalcDimension& positionZ)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(LightPosition, TranslateOptions(positionX, positionY, positionZ));
}

void ViewAbstract::SetLightIntensity(const float value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(LightIntensity, value);
}

void ViewAbstract::SetLightColor(const Color& value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(LightColor, value);
}

void ViewAbstract::SetLightIlluminated(const uint32_t value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(LightIlluminated, value);
}

void ViewAbstract::SetIlluminatedBorderWidth(const Dimension& value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(IlluminatedBorderWidth, value);
}

void ViewAbstract::SetBloom(const float value)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(Bloom, value);
}

void ViewAbstract::SetLightPosition(FrameNode* frameNode, const CalcDimension& positionX,
    const CalcDimension& positionY, const CalcDimension& positionZ)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_RENDER_CONTEXT(LightPosition, TranslateOptions(positionX, positionY, positionZ), frameNode);
}

void ViewAbstract::SetLightIntensity(FrameNode* frameNode, const float value)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_RENDER_CONTEXT(LightIntensity, value, frameNode);
}

void ViewAbstract::SetLightColor(FrameNode* frameNode, const Color& value)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_RENDER_CONTEXT(LightColor, value, frameNode);
}

void ViewAbstract::SetLightIlluminated(FrameNode* frameNode, const uint32_t value)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_RENDER_CONTEXT(LightIlluminated, value, frameNode);
}

void ViewAbstract::SetIlluminatedBorderWidth(FrameNode* frameNode, const Dimension& value)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_RENDER_CONTEXT(IlluminatedBorderWidth, value, frameNode);
}

void ViewAbstract::SetBloom(FrameNode* frameNode, const float value)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_RENDER_CONTEXT(Bloom, value, frameNode);
}

void ViewAbstract::SetMotionPath(FrameNode* frameNode, const MotionPathOption& motionPath)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(MotionPath, motionPath, frameNode);
}

void ViewAbstract::SetFocusOnTouch(FrameNode* frameNode, bool isSet)
{
    CHECK_NULL_VOID(frameNode);
    auto focusHub = frameNode->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->SetIsFocusOnTouch(isSet);
}

void ViewAbstract::SetGroupDefaultFocus(FrameNode* frameNode, bool isSet)
{
    CHECK_NULL_VOID(frameNode);
    auto focusHub = frameNode->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->SetIsDefaultGroupFocus(isSet);
}

void ViewAbstract::SetFocusable(FrameNode* frameNode, bool focusable)
{
    CHECK_NULL_VOID(frameNode);
    auto focusHub = frameNode->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->SetFocusable(focusable);
}

void ViewAbstract::SetTabStop(FrameNode* frameNode, bool tabStop)
{
    CHECK_NULL_VOID(frameNode);
    auto focusHub = frameNode->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->SetTabStop(tabStop);
}

void ViewAbstract::SetFocusType(FrameNode* frameNode, FocusType focusType)
{
    CHECK_NULL_VOID(frameNode);
    auto focusHub = frameNode->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->SetFocusType(focusType);
}

void ViewAbstract::SetTouchable(FrameNode* frameNode, bool touchable)
{
    CHECK_NULL_VOID(frameNode);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->SetTouchable(touchable);
}

void ViewAbstract::SetDefaultFocus(FrameNode* frameNode, bool isSet)
{
    CHECK_NULL_VOID(frameNode);
    auto focusHub = frameNode->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->SetIsDefaultFocus(isSet);
}

void ViewAbstract::SetDisplayIndex(FrameNode* frameNode, int32_t value)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LayoutProperty, DisplayIndex, value, frameNode);
}

void ViewAbstract::SetOffset(FrameNode* frameNode, const OffsetT<Dimension>& value)
{
    CHECK_NULL_VOID(frameNode);
    ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, OffsetEdges, frameNode);
    ACE_UPDATE_NODE_RENDER_CONTEXT(Offset, value, frameNode);
}

void ViewAbstract::SetOffsetEdges(FrameNode* frameNode, const EdgesParam& value)
{
    CHECK_NULL_VOID(frameNode);
    ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, Offset, frameNode);
    ACE_UPDATE_NODE_RENDER_CONTEXT(OffsetEdges, value, frameNode);
}

void ViewAbstract::MarkAnchor(FrameNode* frameNode, const OffsetT<Dimension>& value)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_RENDER_CONTEXT(Anchor, value, frameNode);
}

void ViewAbstract::SetVisibility(FrameNode* frameNode, VisibleType visible)
{
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty();
    if (layoutProperty) {
        layoutProperty->UpdateVisibility(visible, true, true);
    }

    auto focusHub = frameNode->GetOrCreateFocusHub();
    if (focusHub) {
        focusHub->SetShow(visible == VisibleType::VISIBLE);
    }
}

void ViewAbstract::SetPadding(FrameNode* frameNode, const CalcLength& value)
{
    CHECK_NULL_VOID(frameNode);
    PaddingProperty padding;
    padding.SetEdges(value);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LayoutProperty, Padding, padding, frameNode);
}

void ViewAbstract::SetPadding(FrameNode* frameNode, const PaddingProperty& value)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LayoutProperty, Padding, value, frameNode);
}

void ViewAbstract::SetMargin(FrameNode* frameNode, const CalcLength& value)
{
    CHECK_NULL_VOID(frameNode);
    MarginProperty margin;
    margin.SetEdges(value);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LayoutProperty, Margin, margin, frameNode);
}

void ViewAbstract::SetMargin(FrameNode* frameNode, const PaddingProperty& value)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LayoutProperty, Margin, value, frameNode);
}

void ViewAbstract::SetLayoutDirection(FrameNode* frameNode, TextDirection value)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LayoutProperty, LayoutDirection, value, frameNode);
}

void ViewAbstract::UpdateSafeAreaExpandOpts(FrameNode* frameNode, const SafeAreaExpandOpts& opts)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LayoutProperty, SafeAreaExpandOpts, opts, frameNode);
}

void ViewAbstract::SetAspectRatio(FrameNode* frameNode, float ratio)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LayoutProperty, AspectRatio, ratio, frameNode);
}

void ViewAbstract::SetAlignSelf(FrameNode* frameNode, FlexAlign value)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LayoutProperty, AlignSelf, value, frameNode);
}

void ViewAbstract::SetFlexBasis(FrameNode* frameNode, const Dimension& value)
{
    CHECK_NULL_VOID(frameNode);
    if (LessNotEqual(value.Value(), 0.0f)) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(LayoutProperty, FlexBasis, Dimension(), frameNode);
        return;
    }
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LayoutProperty, FlexBasis, value, frameNode);
}

void ViewAbstract::ResetFlexShrink(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    ACE_RESET_NODE_LAYOUT_PROPERTY(LayoutProperty, FlexShrink, frameNode);
}

void ViewAbstract::SetFlexShrink(FrameNode* frameNode, float value)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LayoutProperty, FlexShrink, value, frameNode);
}

void ViewAbstract::SetFlexGrow(FrameNode* frameNode, float value)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LayoutProperty, FlexGrow, value, frameNode);
}

void ViewAbstract::SetLayoutWeight(FrameNode* frameNode, float value)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LayoutProperty, LayoutWeight, value, frameNode);
}

void ViewAbstract::SetChainWeight(FrameNode* frameNode, const NG::ChainWeightPair& value)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LayoutProperty, ChainWeight, value, frameNode);
}

void ViewAbstract::ResetMaxSize(FrameNode* frameNode, bool resetWidth)
{
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->ResetCalcMaxSize(resetWidth);
}

void ViewAbstract::ResetMinSize(FrameNode* frameNode, bool resetWidth)
{
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->ResetCalcMinSize(resetWidth);
}

void ViewAbstract::SetMinWidth(FrameNode* frameNode, const CalcLength& minWidth)
{
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateCalcMinSize(CalcSize(minWidth, std::nullopt));
}

void ViewAbstract::SetMaxWidth(FrameNode* frameNode, const CalcLength& maxWidth)
{
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateCalcMaxSize(CalcSize(maxWidth, std::nullopt));
}

void ViewAbstract::SetMinHeight(FrameNode* frameNode, const CalcLength& minHeight)
{
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateCalcMinSize(CalcSize(std::nullopt, minHeight));
}

void ViewAbstract::SetMaxHeight(FrameNode* frameNode, const CalcLength& maxHeight)
{
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateCalcMaxSize(CalcSize(std::nullopt, maxHeight));
}

void ViewAbstract::SetAlignRules(FrameNode* frameNode, const std::map<AlignDirection, AlignRule>& alignRules)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LayoutProperty, AlignRules, alignRules, frameNode);
}

std::map<AlignDirection, AlignRule> ViewAbstract::GetAlignRules(FrameNode* frameNode)
{
    std::map<AlignDirection, AlignRule> alignRules;
    CHECK_NULL_RETURN(frameNode, alignRules);
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, alignRules);
    CHECK_NULL_RETURN(layoutProperty->GetFlexItemProperty(), alignRules);
    return layoutProperty->GetFlexItemProperty()->GetAlignRules().value_or(alignRules);
}

void ViewAbstract::ResetAlignRules(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    CHECK_NULL_VOID(layoutProperty->GetFlexItemProperty());
    return layoutProperty->GetFlexItemProperty()->ResetAlignRules();
}

void ViewAbstract::SetChainStyle(FrameNode* frameNode, const ChainInfo& chainInfo)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LayoutProperty, ChainStyle, chainInfo, frameNode);
}

ChainInfo ViewAbstract::GetChainStyle(FrameNode* frameNode)
{
    ChainInfo chainInfo;
    CHECK_NULL_RETURN(frameNode, chainInfo);
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty->GetFlexItemProperty(), chainInfo);
    layoutProperty->GetFlexItemProperty()->GetHorizontalChainStyle().value_or(chainInfo);
    if (chainInfo.direction.has_value()) {
        return chainInfo;
    }
    return layoutProperty->GetFlexItemProperty()->GetVerticalChainStyle().value_or(chainInfo);
}

void ViewAbstract::ResetChainStyle(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    ChainInfo nullChainInfo;
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty->GetFlexItemProperty());
    layoutProperty->GetFlexItemProperty()->UpdateHorizontalChainStyle(nullChainInfo);
    layoutProperty->GetFlexItemProperty()->UpdateVerticalChainStyle(nullChainInfo);
}

void ViewAbstract::SetGrid(
    FrameNode* frameNode, std::optional<int32_t> span, std::optional<int32_t> offset, GridSizeType type)
{
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    // frame node is mounted to parent when pop from stack later, no grid-container is added here
    layoutProperty->UpdateGridProperty(span, offset, type);
}

void ViewAbstract::ResetAspectRatio(FrameNode* frameNode)
{
    ACE_RESET_NODE_LAYOUT_PROPERTY(LayoutProperty, AspectRatio, frameNode);
}

void ViewAbstract::SetAllowDrop(FrameNode* frameNode, const std::set<std::string>& allowDrop)
{
    CHECK_NULL_VOID(frameNode);
    frameNode->SetAllowDrop(allowDrop);
}

void ViewAbstract::SetInspectorId(FrameNode* frameNode, const std::string& inspectorId)
{
    if (frameNode) {
        if (frameNode->GetInspectorId().has_value() && frameNode->GetInspectorIdValue() != inspectorId) {
            ElementRegister::GetInstance()->RemoveFrameNodeByInspectorId(
                frameNode->GetInspectorIdValue(), frameNode->GetId());
        }
        frameNode->UpdateInspectorId(inspectorId);
    }
}

void ViewAbstract::SetRestoreId(FrameNode* frameNode, int32_t restoreId)
{
    if (frameNode) {
        frameNode->SetRestoreId(restoreId);
    }
}

void ViewAbstract::SetTabIndex(FrameNode* frameNode, int32_t index)
{
    CHECK_NULL_VOID(frameNode);
    auto focusHub = frameNode->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->SetTabIndex(index);
}

void ViewAbstract::SetObscured(FrameNode* frameNode, const std::vector<ObscuredReasons>& reasons)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_RENDER_CONTEXT(Obscured, reasons, frameNode);
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void ViewAbstract::SetForegroundEffect(FrameNode* frameNode, float radius)
{
    CHECK_NULL_VOID(frameNode);
    auto target = frameNode->GetRenderContext();
    if (target) {
        target->UpdateForegroundEffect(radius);
    }
}

void ViewAbstract::SetMotionBlur(FrameNode* frameNode, const MotionBlurOption &motionBlurOption)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(MotionBlur, motionBlurOption, frameNode);
}

void ViewAbstract::SetBackgroundEffect(
    FrameNode* frameNode, const EffectOption& effectOption, const SysOptions& sysOptions)
{
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    if (effectOption.policy == BlurStyleActivePolicy::FOLLOWS_WINDOW_ACTIVE_STATE) {
        pipeline->AddWindowFocusChangedCallback(frameNode->GetId());
    } else {
        pipeline->RemoveWindowFocusChangedCallback(frameNode->GetId());
    }
    auto target = frameNode->GetRenderContext();
    if (target) {
        if (target->GetBackBlurRadius().has_value()) {
            target->UpdateBackBlurRadius(Dimension());
        }
        if (target->GetBackBlurStyle().has_value()) {
            target->UpdateBackBlurStyle(std::nullopt);
        }
        target->UpdateBackgroundEffect(effectOption, sysOptions);
    }
}

void ViewAbstract::SetDynamicLightUp(FrameNode* frameNode, float rate, float lightUpDegree)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(DynamicLightUpRate, rate, frameNode);
    ACE_UPDATE_NODE_RENDER_CONTEXT(DynamicLightUpDegree, lightUpDegree, frameNode);
}

void ViewAbstract::SetBgDynamicBrightness(FrameNode* frameNode, const BrightnessOption& brightnessOption)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_RENDER_CONTEXT(BgDynamicBrightnessOption, brightnessOption, frameNode);
}

void ViewAbstract::SetFgDynamicBrightness(FrameNode* frameNode, const BrightnessOption& brightnessOption)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_RENDER_CONTEXT(FgDynamicBrightnessOption, brightnessOption, frameNode);
}

void ViewAbstract::SetBrightnessBlender(FrameNode* frameNode, const OHOS::Rosen::BrightnessBlender* brightnessBlender)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_RENDER_CONTEXT(BrightnessBlender, brightnessBlender, frameNode);
}

void ViewAbstract::SetDragPreviewOptions(FrameNode* frameNode, const DragPreviewOption& previewOption)
{
    CHECK_NULL_VOID(frameNode);
    frameNode->SetDragPreviewOptions(previewOption, false);
}

void ViewAbstract::SetDragPreview(FrameNode* frameNode, const DragDropInfo& dragDropInfo)
{
    CHECK_NULL_VOID(frameNode);
    frameNode->SetDragPreview(dragDropInfo);
}

void ViewAbstract::SetResponseRegion(FrameNode* frameNode, const std::vector<DimensionRect>& responseRegion)
{
    CHECK_NULL_VOID(frameNode);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->SetResponseRegion(responseRegion);
}

void ViewAbstract::SetMouseResponseRegion(FrameNode* frameNode, const std::vector<DimensionRect>& mouseResponseRegion)
{
    CHECK_NULL_VOID(frameNode);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->SetMouseResponseRegion(mouseResponseRegion);
}

void ViewAbstract::SetSharedTransition(
    FrameNode* frameNode, const std::string& shareId, const std::shared_ptr<SharedTransitionOption>& option)
{
    CHECK_NULL_VOID(frameNode);
    const auto& target = frameNode->GetRenderContext();
    if (target) {
        target->SetSharedTransitionOptions(option);
        target->SetShareId(shareId);
    }
}

void ViewAbstract::SetTransition(FrameNode* frameNode, const TransitionOptions& options)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(Transition, options, frameNode);
}

void ViewAbstract::CleanTransition(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    const auto& renderContext = frameNode->GetRenderContext();
    if (renderContext) {
        renderContext->CleanTransition();
    }
}

void ViewAbstract::SetChainedTransition(FrameNode* frameNode, const RefPtr<NG::ChainedTransitionEffect>& effect,
    NG::TransitionFinishCallback&& finishCallback)
{
    CHECK_NULL_VOID(frameNode);
    const auto& target = frameNode->GetRenderContext();
    if (target) {
        target->UpdateChainedTransition(effect);
        target->SetTransitionUserCallback(std::move(finishCallback));
    }
}

void ViewAbstract::SetEnabled(FrameNode* frameNode, bool enabled)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    if (eventHub) {
        eventHub->SetEnabled(enabled);
    }
    auto focusHub = frameNode->GetOrCreateFocusHub();
    if (focusHub) {
        focusHub->SetEnabled(enabled);
    }
}

void ViewAbstract::SetUseShadowBatching(FrameNode* frameNode, bool useShadowBatching)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(UseShadowBatching, useShadowBatching, frameNode);
}

void ViewAbstract::SetBlendMode(FrameNode* frameNode, BlendMode blendMode)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(BackBlendMode, blendMode, frameNode);
}

void ViewAbstract::SetBlendApplyType(FrameNode* frameNode, BlendApplyType blendApplyType)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(BackBlendApplyType, blendApplyType, frameNode);
}

void ViewAbstract::SetMonopolizeEvents(FrameNode* frameNode, bool monopolizeEvents)
{
    CHECK_NULL_VOID(frameNode);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->SetMonopolizeEvents(monopolizeEvents);
}

void ViewAbstract::SetDraggable(FrameNode* frameNode, bool draggable)
{
    CHECK_NULL_VOID(frameNode);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    if (draggable) {
        if (!frameNode->IsDraggable()) {
            gestureHub->InitDragDropEvent();
        }
    } else {
        gestureHub->RemoveDragEvent();
    }
    frameNode->SetCustomerDraggable(draggable);
}

void ViewAbstract::SetHoverEffect(FrameNode* frameNode, HoverEffectType hoverEffect)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetHoverEffect(hoverEffect);
}

void ViewAbstract::SetClickEffectLevel(FrameNode* frameNode, const ClickEffectLevel& level, float scaleValue)
{
    ClickEffectInfo clickEffectInfo;
    clickEffectInfo.level = level;
    clickEffectInfo.scaleNumber = scaleValue;
    ACE_UPDATE_NODE_RENDER_CONTEXT(ClickEffectLevel, clickEffectInfo, frameNode);
}

void ViewAbstract::SetKeyboardShortcut(FrameNode* frameNode, const std::string& value,
    const std::vector<ModifierKey>& keys, std::function<void()>&& onKeyboardShortcutAction)
{
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto eventManager = pipeline->GetEventManager();
    CHECK_NULL_VOID(eventManager);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto frameNodeRef = AceType::Claim<FrameNode>(frameNode);
    if (value.empty() || keys.empty()) {
        eventHub->ClearSingleKeyboardShortcut();
        return;
    }
    auto key = eventManager->GetKeyboardShortcutKeys(keys);
    if ((key == 0 && value.length() == 1) || (key == 0 && !keys.empty() && value.length() > 1)) {
        return;
    }
    if (eventManager->IsSameKeyboardShortcutNode(value, key)) {
        return;
    }
    eventHub->SetKeyboardShortcut(value, key, onKeyboardShortcutAction);
    eventManager->AddKeyboardShortcutNode(WeakPtr<NG::FrameNode>(frameNodeRef));
}

void ViewAbstract::SetOnAppear(FrameNode* frameNode, std::function<void()> &&onAppear)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnAppear(std::move(onAppear));
}

void ViewAbstract::SetOnDisappear(FrameNode* frameNode, std::function<void()> &&onDisappear)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnDisappear(std::move(onDisappear));
}

void ViewAbstract::SetOnAttach(FrameNode* frameNode, std::function<void()> &&onAttach)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnAttach(std::move(onAttach));
}

void ViewAbstract::SetOnDetach(FrameNode* frameNode, std::function<void()> &&onDetach)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnDetach(std::move(onDetach));
}

void ViewAbstract::SetOnAreaChanged(FrameNode* frameNode, std::function<void(const RectF &oldRect,
    const OffsetF &oldOrigin, const RectF &rect, const OffsetF &origin)> &&onAreaChanged)
{
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    frameNode->SetOnAreaChangeCallback(std::move(onAreaChanged));
    pipeline->AddOnAreaChangeNode(frameNode->GetId());
}

void ViewAbstract::SetOnFocus(FrameNode* frameNode, OnFocusFunc &&onFocusCallback)
{
    CHECK_NULL_VOID(frameNode);
    auto focusHub = frameNode->GetOrCreateFocusHub();
    focusHub->SetOnFocusCallback(std::move(onFocusCallback));
}

void ViewAbstract::SetOnBlur(FrameNode* frameNode, OnBlurFunc &&onBlurCallback)
{
    CHECK_NULL_VOID(frameNode);
    auto focusHub = frameNode->GetOrCreateFocusHub();
    focusHub->SetOnBlurCallback(std::move(onBlurCallback));
}

void ViewAbstract::SetOnClick(FrameNode* frameNode, GestureEventFunc&& clickEventFunc, double distanceThreshold)
{
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->SetUserOnClick(std::move(clickEventFunc), distanceThreshold);

    auto focusHub = frameNode->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->SetFocusable(true, false);

    auto* uiNode = reinterpret_cast<UINode*>(frameNode);
    CHECK_NULL_VOID(uiNode);
    uiNode->SetModifierEventRegistrationState(uiNode->IsCNode(), true);
}

void ViewAbstract::SetOnTouch(FrameNode* frameNode, TouchEventFunc &&touchEventFunc)
{
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->SetTouchEvent(std::move(touchEventFunc));
}

void ViewAbstract::SetOnMouse(FrameNode* frameNode, OnMouseEventFunc &&onMouseEventFunc)
{
    auto eventHub = frameNode->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetMouseEvent(std::move(onMouseEventFunc));
}

void ViewAbstract::SetOnAxisEvent(FrameNode* frameNode, OnAxisEventFunc&& onAxisEventFunc)
{
    auto eventHub = frameNode->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetAxisEvent(std::move(onAxisEventFunc));
}

void ViewAbstract::SetOnHover(FrameNode* frameNode, OnHoverFunc &&onHoverEventFunc)
{
    auto eventHub = frameNode->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetHoverEvent(std::move(onHoverEventFunc));
}

void ViewAbstract::SetOnHoverMove(FrameNode* frameNode, OnHoverMoveFunc &&onHoverMoveEventFunc)
{
    auto eventHub = frameNode->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetHoverMoveEvent(std::move(onHoverMoveEventFunc));
}

void ViewAbstract::SetOnKeyEvent(FrameNode* frameNode, OnKeyConsumeFunc &&onKeyCallback)
{
    auto focusHub = frameNode->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->SetOnKeyCallback(std::move(onKeyCallback));
}

void ViewAbstract::SetOnKeyEventDispatch(OnKeyEventDispatchFunc&& onKeyDispatchCallback)
{
    auto focusHub = ViewStackProcessor::GetInstance()->GetOrCreateMainFrameNodeFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->SetOnKeyEventDispatchCallback(std::move(onKeyDispatchCallback));
}

void ViewAbstract::SetOnKeyEventDispatch(FrameNode* frameNode, OnKeyEventDispatchFunc&& onKeyDispatchCallback)
{
    CHECK_NULL_VOID(frameNode);
    auto focusHub = frameNode->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->SetOnKeyEventDispatchCallback(std::move(onKeyDispatchCallback));
}

void ViewAbstract::DispatchKeyEvent(FrameNode* frameNode, KeyEvent& keyEvent)
{
    CHECK_NULL_VOID(frameNode);
    auto focusHub = frameNode->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->HandleEvent(keyEvent);
}

bool ViewAbstract::GetFocusable(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto focusHub = frameNode->GetOrCreateFocusHub();
    CHECK_NULL_RETURN(focusHub, false);
    return focusHub->IsFocusable();
}

bool ViewAbstract::GetTabStop(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto focusHub = frameNode->GetOrCreateFocusHub();
    CHECK_NULL_RETURN(focusHub, false);
    return focusHub->IsTabStop();
}

bool ViewAbstract::GetDefaultFocus(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto focusHub = frameNode->GetOrCreateFocusHub();
    CHECK_NULL_RETURN(focusHub, false);
    return focusHub->IsDefaultFocus();
}

std::vector<DimensionRect> ViewAbstract::GetResponseRegion(FrameNode* frameNode)
{
    std::vector<DimensionRect> defaultRect;
    CHECK_NULL_RETURN(frameNode, defaultRect);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(gestureHub, defaultRect);
    return gestureHub->GetResponseRegion();
}

NG::OverlayOptions ViewAbstract::GetOverlay(FrameNode* frameNode)
{
    NG::OverlayOptions defaultOptions;
    const auto& target = frameNode->GetRenderContext();
    return target->GetOverlayTextValue(defaultOptions);
}

void ViewAbstract::SetNeedFocus(FrameNode* frameNode, bool value)
{
    CHECK_NULL_VOID(frameNode);
    auto focusHub = frameNode->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    if (value) {
        auto context = frameNode->GetContext();
        CHECK_NULL_VOID(context);
        auto instanceId = context->GetInstanceId();
        ContainerScope scope(instanceId);
        focusHub->RequestFocus();
    } else {
        auto context = frameNode->GetAttachedContext();
        if (!context) {
            TAG_LOGW(AceLogTag::ACE_FOCUS,
                "Can't find Node %{public}s/%{public}d attachedContext, please check the timing of the function call.",
                frameNode->GetTag().c_str(), frameNode->GetId());
            return;
        }
        auto instanceId = context->GetInstanceId();
        ContainerScope scope(instanceId);
        focusHub->LostFocusToViewRoot();
    }
}

bool ViewAbstract::GetNeedFocus(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto focusHub = frameNode->GetOrCreateFocusHub();
    CHECK_NULL_RETURN(focusHub, false);
    return focusHub->IsCurrentFocus();
}

int ViewAbstract::RequestFocus(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, ERROR_CODE_NON_EXIST);
    auto context = frameNode->GetContext();
    CHECK_NULL_RETURN(context, ERROR_CODE_NON_EXIST);
    auto instanceId = context->GetInstanceId();
    ContainerScope scope(instanceId);
    auto focusManager = context->GetOrCreateFocusManager();
    focusManager->ResetRequestFocusResult();
    auto focusHub = frameNode->GetOrCreateFocusHub();
    // check node focusable
    if (focusHub->IsSyncRequestFocusable()) {
        focusHub->RequestFocusImmediately();
    }
    auto retCode = focusManager->GetRequestFocusResult();
    focusManager->ResetRequestFocusResult();
    return retCode;
}

void ViewAbstract::ClearFocus(int32_t instanceId)
{
    auto context = PipelineContext::GetContextByContainerId(instanceId);
    if (!context) {
        TAG_LOGW(AceLogTag::ACE_FOCUS, "Can't find attachedContext, please check the timing of the function call.");
        return;
    }
    FocusHub::LostFocusToViewRoot();
}

void ViewAbstract::FocusActivate(int32_t instanceId, bool isActive, bool isAutoInactive)
{
    auto context = PipelineContext::GetContextByContainerId(instanceId);
    if (!context) {
        TAG_LOGW(AceLogTag::ACE_FOCUS, "Can't find attachedContext, please check the timing of the function call.");
        return;
    }
    context->SetIsFocusActive(isActive, NG::FocusActiveReason::USE_API, isAutoInactive);
}

void ViewAbstract::SetAutoFocusTransfer(int32_t instanceId, bool isAutoFocusTransfer)
{
    auto context = PipelineContext::GetContextByContainerId(instanceId);
    if (!context) {
        TAG_LOGW(AceLogTag::ACE_FOCUS, "Can't find attachedContext, please check the timing of the function call.");
        return;
    }
    auto focusManager = context->GetOrCreateFocusManager();
    CHECK_NULL_VOID(focusManager);
    focusManager->SetIsAutoFocusTransfer(isAutoFocusTransfer);
}

double ViewAbstract::GetOpacity(FrameNode* frameNode)
{
    double opacity = 1.0f;
    const auto& target = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(target, opacity);
    return target->GetOpacityValue(opacity);
}

BorderWidthProperty ViewAbstract::GetBorderWidth(FrameNode* frameNode)
{
    Dimension defaultDimension(0);
    BorderWidthProperty borderWidths = { defaultDimension, defaultDimension, defaultDimension, defaultDimension,
        std::nullopt, std::nullopt};
    const auto& target = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(target, borderWidths);
    return target->GetBorderWidthValue(borderWidths);
}

BorderWidthProperty ViewAbstract::GetLayoutBorderWidth(FrameNode* frameNode)
{
    Dimension defaultDimen = Dimension(0, DimensionUnit::VP);
    BorderWidthProperty borderWidths;
    borderWidths.topDimen = std::optional<Dimension>(defaultDimen);
    borderWidths.rightDimen = std::optional<Dimension>(defaultDimen);
    borderWidths.bottomDimen = std::optional<Dimension>(defaultDimen);
    borderWidths.leftDimen = std::optional<Dimension>(defaultDimen);
    const auto& layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, borderWidths);
    const auto& property = layoutProperty->GetBorderWidthProperty();
    CHECK_NULL_RETURN(property, borderWidths);
    borderWidths.topDimen = std::optional<Dimension>(property->topDimen);
    borderWidths.rightDimen = std::optional<Dimension>(property->rightDimen);
    borderWidths.bottomDimen = std::optional<Dimension>(property->bottomDimen);
    borderWidths.leftDimen = std::optional<Dimension>(property->leftDimen);
    return borderWidths;
}

BorderRadiusProperty ViewAbstract::GetBorderRadius(FrameNode* frameNode)
{
    Dimension defaultDimension(0);
    BorderRadiusProperty borderRadius = { defaultDimension, defaultDimension, defaultDimension, defaultDimension };
    const auto& target = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(target, borderRadius);
    return target->GetBorderRadiusValue(borderRadius);
}

BorderColorProperty ViewAbstract::GetBorderColor(FrameNode* frameNode)
{
    Color defaultColor(0xff000000);
    BorderColorProperty borderColors = { defaultColor, defaultColor, defaultColor, defaultColor,
        std::nullopt, std::nullopt };
    const auto& target = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(target, borderColors);
    return target->GetBorderColorValue(borderColors);
}

BorderStyleProperty ViewAbstract::GetBorderStyle(FrameNode* frameNode)
{
    BorderStyle defaultStyle = BorderStyle::SOLID;
    BorderStyleProperty borderStyles = { defaultStyle, defaultStyle, defaultStyle, defaultStyle };
    const auto& target = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(target, borderStyles);
    return target->GetBorderStyleValue(borderStyles);
}

int ViewAbstract::GetZIndex(FrameNode* frameNode)
{
    int zindex = 0;
    const auto& target = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(target, zindex);
    return target->GetZIndexValue(zindex);
}

VisibleType ViewAbstract::GetVisibility(FrameNode* frameNode)
{
    VisibleType visibility = VisibleType::VISIBLE;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(LayoutProperty, Visibility, visibility, frameNode, visibility);
    return visibility;
}

bool ViewAbstract::GetClip(FrameNode* frameNode)
{
    bool value = false;
    const auto& target = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(target, value);
    return target->GetClipEdgeValue(value);
}

RefPtr<BasicShape> ViewAbstract::GetClipShape(FrameNode* frameNode)
{
    RefPtr<BasicShape> value = AceType::MakeRefPtr<BasicShape>();
    const auto& target = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(target, value);
    return target->GetClipShapeValue(value);
}

Matrix4 ViewAbstract::GetTransform(FrameNode* frameNode)
{
    Matrix4 value;
    const auto& target = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(target, value);
    return target->GetTransformMatrixValue(value);
}

HitTestMode ViewAbstract::GetHitTestBehavior(FrameNode* frameNode)
{
    auto gestureHub = frameNode->GetHitTestMode();
    return gestureHub;
}

OffsetT<Dimension> ViewAbstract::GetPosition(FrameNode* frameNode)
{
    Dimension PositionX(0, DimensionUnit::VP);
    Dimension PositionY(0, DimensionUnit::VP);
    OffsetT<Dimension> position(PositionX, PositionY);
    const auto& target = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(target, position);
    return target->GetPositionValue(position);
}

std::optional<Shadow> ViewAbstract::GetShadow(FrameNode* frameNode)
{
    Shadow value;
    const auto& target = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(target, value);
    return target->GetBackShadowValue(value);
}

NG::Gradient ViewAbstract::GetSweepGradient(FrameNode* frameNode)
{
    Gradient value;
    value.CreateGradientWithType(NG::GradientType::SWEEP);
    const auto& target = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(target, value);
    return target->GetSweepGradientValue(value);
}

NG::Gradient ViewAbstract::GetRadialGradient(FrameNode* frameNode)
{
    Gradient value;
    value.CreateGradientWithType(NG::GradientType::RADIAL);
    const auto& target = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(target, value);
    return target->GetRadialGradientValue(value);
}

RefPtr<BasicShape> ViewAbstract::GetMask(FrameNode* frameNode)
{
    RefPtr<BasicShape> value = AceType::MakeRefPtr<BasicShape>();
    const auto& target = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(target, nullptr);
    if (target->HasClipMask()) {
        return target->GetClipMaskValue(value);
    }
    return nullptr;
}

RefPtr<ProgressMaskProperty> ViewAbstract::GetMaskProgress(FrameNode* frameNode)
{
    RefPtr<ProgressMaskProperty> value = AceType::MakeRefPtr<ProgressMaskProperty>();
    const auto& target = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(target, nullptr);
    if (target->HasProgressMask()) {
        return target->GetProgressMaskValue(value);
    }
    return nullptr;
}

BlendMode ViewAbstract::GetBlendMode(FrameNode* frameNode)
{
    BlendMode value = BlendMode::NONE;
    auto target = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(target, value);
    return target->GetBackBlendModeValue(value);
}

TextDirection ViewAbstract::GetDirection(FrameNode* frameNode)
{
    TextDirection direction = TextDirection::AUTO;
    auto target = frameNode->GetLayoutProperty<LayoutProperty>();
    direction = target->GetLayoutDirection();
    return direction;
}

FlexAlign ViewAbstract::GetAlignSelf(FrameNode* frameNode)
{
    FlexAlign value = FlexAlign::AUTO;
    const auto& flexItemProperty = frameNode->GetLayoutProperty()->GetFlexItemProperty();
    CHECK_NULL_RETURN(flexItemProperty, value);
    auto getValue = flexItemProperty->GetAlignSelf();
    if (getValue.has_value()) {
        return getValue.value();
    }
    return value;
}

float ViewAbstract::GetFlexGrow(FrameNode* frameNode)
{
    float value = 0.0f;
    const auto& layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, value);
    const auto& property = layoutProperty->GetFlexItemProperty();
    CHECK_NULL_RETURN(property, value);
    auto getValue = property->GetFlexGrow();
    if (getValue.has_value()) {
        return getValue.value();
    }
    return value;
}

float ViewAbstract::GetFlexShrink(FrameNode* frameNode)
{
    float value = 0.0f;
    const auto& layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, value);
    const auto& property = layoutProperty->GetFlexItemProperty();
    CHECK_NULL_RETURN(property, value);
    auto getValue = property->GetFlexShrink();
    if (getValue.has_value()) {
        return getValue.value();
    }
    return value;
}

Dimension ViewAbstract::GetFlexBasis(FrameNode* frameNode)
{
    Dimension value;
    const auto& layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, value);
    const auto& property = layoutProperty->GetFlexItemProperty();
    CHECK_NULL_RETURN(property, value);
    auto getValue = property->GetFlexBasis();
    if (getValue.has_value()) {
        return getValue.value();
    }
    return value;
}

Dimension ViewAbstract::GetMinWidth(FrameNode* frameNode)
{
    Dimension value = Dimension(0.0f);
    const auto& layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, value);
    const auto& property = layoutProperty->GetCalcLayoutConstraint();
    CHECK_NULL_RETURN(property, value);
    auto size = property->minSize;
    if (size.has_value()) {
        auto width = size->Width();
        if (width.has_value()) {
            return width.value().GetDimension();
        }
    }
    return value;
}

Dimension ViewAbstract::GetMaxWidth(FrameNode* frameNode)
{
    Dimension value = Dimension(0.0f);
    const auto& layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, value);
    const auto& property = layoutProperty->GetCalcLayoutConstraint();
    CHECK_NULL_RETURN(property, value);
    auto size = property->maxSize;
    if (size.has_value()) {
        auto width = size->Width();
        if (width.has_value()) {
            return width.value().GetDimension();
        }
    }
    return value;
}

Dimension ViewAbstract::GetMinHeight(FrameNode* frameNode)
{
    Dimension value = Dimension(0.0f);
    const auto& layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, value);
    const auto& property = layoutProperty->GetCalcLayoutConstraint();
    CHECK_NULL_RETURN(property, value);
    auto size = property->minSize;
    if (size.has_value()) {
        auto height = size->Height();
        if (height.has_value()) {
            return height.value().GetDimension();
        }
    }
    return value;
}

Dimension ViewAbstract::GetMaxHeight(FrameNode* frameNode)
{
    Dimension value = Dimension(0.0f);
    const auto& layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, value);
    const auto& property = layoutProperty->GetCalcLayoutConstraint();
    CHECK_NULL_RETURN(property, value);
    auto size = property->maxSize;
    if (size.has_value()) {
        auto height = size->Height();
        if (height.has_value()) {
            return height.value().GetDimension();
        }
    }
    return value;
}

Dimension ViewAbstract::GetGrayScale(FrameNode* frameNode)
{
    Dimension value;
    auto target = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(target, value);
    return target->GetFrontGrayScaleValue(value);
}

InvertVariant ViewAbstract::GetInvert(FrameNode* frameNode)
{
    InvertVariant value = 0.0f;
    auto target = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(target, value);
    return target->GetFrontInvertValue(value);
}

Dimension ViewAbstract::GetSepia(FrameNode* frameNode)
{
    Dimension value;
    auto target = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(target, value);
    return target->GetFrontSepiaValue(value);
}

Dimension ViewAbstract::GetContrast(FrameNode* frameNode)
{
    Dimension value(1.0f);
    auto target = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(target, value);
    return target->GetFrontContrastValue(value);
}

Color ViewAbstract::GetForegroundColor(FrameNode* frameNode)
{
    Color value;
    auto target = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(target, value);
    return target->GetForegroundColorValue(value);
}

NG::VectorF ViewAbstract::GetScale(FrameNode* frameNode)
{
    NG::VectorF defaultVector = { 1.0f, 1.0f };
    CHECK_NULL_RETURN(frameNode, defaultVector);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, defaultVector);
    return renderContext->GetTransformScale().value_or(defaultVector);
}

NG::Vector5F ViewAbstract::GetRotate(FrameNode* frameNode)
{
    NG::Vector5F defaultVector = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
    CHECK_NULL_RETURN(frameNode, defaultVector);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, defaultVector);
    return renderContext->GetTransformRotate().value_or(defaultVector);
}

Dimension ViewAbstract::GetBrightness(FrameNode* frameNode)
{
    Dimension defaultBrightness(1.0);
    CHECK_NULL_RETURN(frameNode, defaultBrightness);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, defaultBrightness);
    return renderContext->GetFrontBrightness().value_or(defaultBrightness);
}

Dimension ViewAbstract::GetSaturate(FrameNode* frameNode)
{
    Dimension defaultSaturate(1.0);
    CHECK_NULL_RETURN(frameNode, defaultSaturate);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, defaultSaturate);
    return renderContext->GetFrontSaturate().value_or(defaultSaturate);
}

BackgroundImagePosition ViewAbstract::GetBackgroundImagePosition(FrameNode* frameNode)
{
    BackgroundImagePosition defaultImagePosition;
    CHECK_NULL_RETURN(frameNode, defaultImagePosition);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, defaultImagePosition);
    return renderContext->GetBackgroundImagePosition().value_or(defaultImagePosition);
}

Dimension ViewAbstract::GetFrontBlur(FrameNode* frameNode)
{
    Dimension value;
    auto target = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(target, value);
    auto& property = target->GetForeground();
    CHECK_NULL_RETURN(property, value);
    auto getValue = property->propBlurRadius;
    if (getValue.has_value()) {
        return getValue.value();
    }
    return value;
}

NG::Gradient ViewAbstract::GetLinearGradient(FrameNode *frameNode)
{
    NG::Gradient value;
    value.CreateGradientWithType(NG::GradientType::LINEAR);
    auto target = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(target, value);
    return target->GetLinearGradientValue(value);
}

Alignment ViewAbstract::GetAlign(FrameNode *frameNode)
{
    Alignment value = Alignment::CENTER;
    const auto& layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, value);
    const auto& property = layoutProperty->GetPositionProperty();
    CHECK_NULL_RETURN(property, value);
    auto getValue = property->GetAlignment();
    if (getValue.has_value()) {
        return getValue.value();
    }
    return value;
}

Dimension ViewAbstract::GetWidth(FrameNode* frameNode)
{
    Dimension value = Dimension(-1.0f);
    const auto& layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, value);
    const auto& property = layoutProperty->GetCalcLayoutConstraint();
    CHECK_NULL_RETURN(property, value);
    auto size = property->selfIdealSize;
    if (size.has_value()) {
        auto width = size->Width();
        if (width.has_value()) {
            return width.value().GetDimension();
        }
    }
    return value;
}

Dimension ViewAbstract::GetHeight(FrameNode* frameNode)
{
    Dimension value = Dimension(-1.0f);
    const auto& layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, value);
    const auto& property = layoutProperty->GetCalcLayoutConstraint();
    CHECK_NULL_RETURN(property, value);
    auto size = property->selfIdealSize;
    if (size.has_value()) {
        auto height = size->Height();
        if (height.has_value()) {
            return height.value().GetDimension();
        }
    }
    return value;
}

Color ViewAbstract::GetBackgroundColor(FrameNode* frameNode)
{
    Color value;
    auto target = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(target, value);
    return target->GetBackgroundColorValue(value);
}

std::string ViewAbstract::GetBackgroundImageSrc(FrameNode* frameNode)
{
    auto target = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(target, "");
    if (target->GetBackgroundImage().has_value()) {
        return target->GetBackgroundImage()->GetSrc();
    }
    return "";
}

ImageRepeat ViewAbstract::GetBackgroundImageRepeat(FrameNode* frameNode)
{
    ImageRepeat value = ImageRepeat::NO_REPEAT;
    auto target = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(target, value);
    if (target->GetBackgroundImageRepeat().has_value()) {
        return target->GetBackgroundImageRepeat().value();
    }
    return value;
}

PaddingProperty ViewAbstract::GetPadding(FrameNode* frameNode)
{
    CalcLength defaultDimen = CalcLength(0, DimensionUnit::VP);
    PaddingProperty paddings;
    paddings.top = std::optional<CalcLength>(defaultDimen);
    paddings.right = std::optional<CalcLength>(defaultDimen);
    paddings.bottom = std::optional<CalcLength>(defaultDimen);
    paddings.left = std::optional<CalcLength>(defaultDimen);
    const auto& layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, paddings);
    const auto& property = layoutProperty->GetPaddingProperty();
    CHECK_NULL_RETURN(property, paddings);
    paddings.top = std::optional<CalcLength>(property->top);
    paddings.right = std::optional<CalcLength>(property->right);
    paddings.bottom = std::optional<CalcLength>(property->bottom);
    paddings.left = std::optional<CalcLength>(property->left);
    return paddings;
}

std::optional<CalcSize> ViewAbstract::GetConfigSize(FrameNode* frameNode)
{
    auto value = std::optional<CalcSize>();
    const auto& layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, value);
    const auto& property = layoutProperty->GetCalcLayoutConstraint();
    CHECK_NULL_RETURN(property, value);
    auto size = property->selfIdealSize;
    if (size.has_value()) {
        value = size;
    }
    return value;
}

std::string ViewAbstract::GetKey(FrameNode* frameNode)
{
    std::string value;
    CHECK_NULL_RETURN(frameNode, value);
    return value = frameNode->GetInspectorIdValue();
}

bool ViewAbstract::GetEnabled(FrameNode* frameNode)
{
    auto eventHub = frameNode->GetEventHub<EventHub>();
    CHECK_NULL_RETURN(eventHub, false);
    return eventHub->IsEnabled();
}

MarginProperty ViewAbstract::GetMargin(FrameNode* frameNode)
{
    CalcLength defaultDimen = CalcLength(0, DimensionUnit::VP);
    MarginProperty margins;
    margins.top = std::optional<CalcLength>(defaultDimen);
    margins.right = std::optional<CalcLength>(defaultDimen);
    margins.bottom = std::optional<CalcLength>(defaultDimen);
    margins.left = std::optional<CalcLength>(defaultDimen);
    const auto& layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, margins);
    const auto& property = layoutProperty->GetMarginProperty();
    CHECK_NULL_RETURN(property, margins);
    margins.top = std::optional<CalcLength>(property->top);
    margins.right = std::optional<CalcLength>(property->right);
    margins.bottom = std::optional<CalcLength>(property->bottom);
    margins.left = std::optional<CalcLength>(property->left);
    return margins;
}

TranslateOptions ViewAbstract::GetTranslate(FrameNode* frameNode)
{
    TranslateOptions value(0.0f, 0.0f, 0.0f);
    auto target = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(target, value);
    return target->GetTransformTranslateValue(value);
}

float ViewAbstract::GetAspectRatio(FrameNode* frameNode)
{
    float aspectRatio = 1.0f;
    const auto& layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, aspectRatio);
    aspectRatio = layoutProperty->GetAspectRatio();
    return aspectRatio;
}

void ViewAbstract::SetJSFrameNodeOnClick(FrameNode* frameNode, GestureEventFunc&& clickEventFunc)
{
    CHECK_NULL_VOID(frameNode);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->SetJSFrameNodeOnClick(std::move(clickEventFunc));
    auto focusHub = frameNode->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->SetFocusable(true, false);
    auto* uiNode = reinterpret_cast<UINode*>(frameNode);
    CHECK_NULL_VOID(uiNode);
    uiNode->SetNodeEventRegistrationState(true);
}

void ViewAbstract::ClearJSFrameNodeOnClick(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->ClearJSFrameNodeOnClick();
}

void ViewAbstract::SetJSFrameNodeOnTouch(FrameNode* frameNode, TouchEventFunc&& touchEventFunc)
{
    CHECK_NULL_VOID(frameNode);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->SetJSFrameNodeOnTouchEvent(std::move(touchEventFunc));
}

void ViewAbstract::ClearJSFrameNodeOnTouch(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->ClearJSFrameNodeOnTouch();
}

void ViewAbstract::SetJSFrameNodeOnAppear(FrameNode* frameNode, std::function<void()>&& onAppear)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetJSFrameNodeOnAppear(std::move(onAppear));
}

void ViewAbstract::ClearJSFrameNodeOnAppear(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->ClearJSFrameNodeOnAppear();
}

void ViewAbstract::SetJSFrameNodeOnDisappear(FrameNode* frameNode, std::function<void()>&& onDisappear)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetJSFrameNodeOnDisappear(std::move(onDisappear));
}

void ViewAbstract::ClearJSFrameNodeOnDisappear(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->ClearJSFrameNodeOnDisappear();
}

void ViewAbstract::SetJSFrameNodeOnKeyCallback(FrameNode* frameNode, OnKeyCallbackFunc&& onKeyCallback)
{
    CHECK_NULL_VOID(frameNode);
    auto focusHub = frameNode->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->SetJSFrameNodeOnKeyCallback(std::move(onKeyCallback));
}

void ViewAbstract::ClearJSFrameNodeOnKeyCallback(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto focusHub = frameNode->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->ClearJSFrameNodeOnKeyCallback();
}

void ViewAbstract::SetJSFrameNodeOnFocusCallback(FrameNode* frameNode, OnFocusFunc&& onFocusCallback)
{
    CHECK_NULL_VOID(frameNode);
    auto focusHub = frameNode->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->SetJSFrameNodeOnFocusCallback(std::move(onFocusCallback));
}

void ViewAbstract::ClearJSFrameNodeOnFocusCallback(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto focusHub = frameNode->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->ClearJSFrameNodeOnFocusCallback();
}

void ViewAbstract::SetJSFrameNodeOnBlurCallback(FrameNode* frameNode, OnBlurFunc&& onBlurCallback)
{
    CHECK_NULL_VOID(frameNode);
    auto focusHub = frameNode->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->SetJSFrameNodeOnBlurCallback(std::move(onBlurCallback));
}

void ViewAbstract::ClearJSFrameNodeOnBlurCallback(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto focusHub = frameNode->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->ClearJSFrameNodeOnBlurCallback();
}

void ViewAbstract::SetJSFrameNodeOnHover(FrameNode* frameNode, OnHoverFunc&& onHoverEventFunc)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetJSFrameNodeOnHoverEvent(std::move(onHoverEventFunc));
}

void ViewAbstract::ClearJSFrameNodeOnHover(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(eventHub);
    eventHub->ClearJSFrameNodeOnHover();
}

void ViewAbstract::SetJSFrameNodeOnHoverMove(FrameNode* frameNode, OnHoverMoveFunc&& onHoverMoveEventFunc)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetJSFrameNodeOnHoverMoveEvent(std::move(onHoverMoveEventFunc));
}

void ViewAbstract::ClearJSFrameNodeOnHoverMove(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(eventHub);
    eventHub->ClearJSFrameNodeOnHoverMove();
}

void ViewAbstract::SetJSFrameNodeOnMouse(FrameNode* frameNode, OnMouseEventFunc&& onMouseEventFunc)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetJSFrameNodeOnMouseEvent(std::move(onMouseEventFunc));
}

void ViewAbstract::ClearJSFrameNodeOnMouse(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(eventHub);
    eventHub->ClearJSFrameNodeOnMouse();
}

BlendApplyType ViewAbstract::GetBlendApplyType(FrameNode* frameNode)
{
    BlendApplyType value = BlendApplyType::FAST;
    const auto& target = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(target, value);
    return target->GetBackBlendApplyTypeValue(value);
}

void ViewAbstract::SetJSFrameNodeOnSizeChange(
    FrameNode* frameNode, std::function<void(const RectF& oldRect, const RectF& rect)>&& onSizeChanged)
{
    CHECK_NULL_VOID(frameNode);
    frameNode->SetJSFrameNodeOnSizeChangeCallback(std::move(onSizeChanged));
}

void ViewAbstract::ClearJSFrameNodeOnSizeChange(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->ClearJSFrameNodeOnSizeChange();
}

void ViewAbstract::SetJSFrameNodeOnVisibleAreaApproximateChange(FrameNode* frameNode,
    const std::function<void(bool, double)>&& jsCallback, const std::vector<double>& ratioList,
    int32_t interval)
{
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    frameNode->CleanVisibleAreaUserCallback(true);

    constexpr uint32_t minInterval = 100; // 100ms
    if (interval < 0 || static_cast<uint32_t>(interval) < minInterval) {
        interval = minInterval;
    }
    VisibleCallbackInfo callback;
    callback.callback = std::move(jsCallback);
    callback.isCurrentVisible = false;
    callback.period = static_cast<uint32_t>(interval);
    pipeline->AddVisibleAreaChangeNode(frameNode->GetId());
    frameNode->SetVisibleAreaUserCallback(ratioList, callback);
}

void ViewAbstract::ClearJSFrameNodeOnVisibleAreaApproximateChange(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    frameNode->CleanVisibleAreaUserCallback(true);
}

void ViewAbstract::SetOnGestureJudgeBegin(FrameNode* frameNode, GestureJudgeFunc&& gestureJudgeFunc)
{
    CHECK_NULL_VOID(frameNode);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->SetOnGestureJudgeBegin(std::move(gestureJudgeFunc));
}

void ViewAbstract::SetOnSizeChanged(
    FrameNode* frameNode, std::function<void(const RectF& oldRect, const RectF& rect)>&& onSizeChanged)
{
    CHECK_NULL_VOID(frameNode);
    frameNode->SetOnSizeChangeCallback(std::move(onSizeChanged));
}

void ViewAbstract::SetOnGestureRecognizerJudgeBegin(
    FrameNode* frameNode, GestureRecognizerJudgeFunc&& gestureRecognizerJudgeFunc)
{
    CHECK_NULL_VOID(frameNode);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->SetOnGestureRecognizerJudgeBegin(std::move(gestureRecognizerJudgeFunc));
}

void ViewAbstract::SetShouldBuiltInRecognizerParallelWith(
    FrameNode* frameNode, NG::ShouldBuiltInRecognizerParallelWithFunc&& shouldBuiltInRecognizerParallelWithFunc)
{
    CHECK_NULL_VOID(frameNode);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->SetShouldBuildinRecognizerParallelWithFunc(std::move(shouldBuiltInRecognizerParallelWithFunc));
}

void ViewAbstract::SetNextFocus(FrameNode* frameNode, FocusIntension key,
    std::variant<WeakPtr<AceType>, std::string> nextFocus)
{
    CHECK_NULL_VOID(frameNode);
    auto focusHub = frameNode->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->SetNextFocus(key, nextFocus);
}

void ViewAbstract::ResetNextFocus(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto focusHub = frameNode->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->ResetNextFocus();
}

void ViewAbstract::SetFocusBoxStyle(FrameNode* frameNode, const NG::FocusBoxStyle& style)
{
    CHECK_NULL_VOID(frameNode);
    auto focusHub = frameNode->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->GetFocusBox().SetStyle(style);
}

void ViewAbstract::SetDragEventStrictReportingEnabled(bool dragEventStrictReportingEnabled)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    dragDropManager->SetEventStrictReportingEnabled(dragEventStrictReportingEnabled);
}

void ViewAbstract::SetDragEventStrictReportingEnabled(int32_t instanceId, bool dragEventStrictReportingEnabled)
{
    auto pipeline = PipelineContext::GetContextByContainerId(instanceId);
    CHECK_NULL_VOID(pipeline);
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    dragDropManager->SetEventStrictReportingEnabled(dragEventStrictReportingEnabled);
}

void ViewAbstract::SetDisallowDropForcedly(bool isDisallowDropForcedly)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    frameNode->SetDisallowDropForcedly(isDisallowDropForcedly);
}

void ViewAbstract::SetBackgroundImageResizableSlice(const ImageResizableSlice& slice)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_RENDER_CONTEXT(BackgroundImageResizableSlice, slice);
}

void ViewAbstract::SetBackgroundImageResizableSlice(FrameNode* frameNode, const ImageResizableSlice& slice)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(BackgroundImageResizableSlice, slice, frameNode);
}

ImageResizableSlice ViewAbstract::GetBackgroundImageResizableSlice(FrameNode* frameNode)
{
    ImageResizableSlice slice;
    CHECK_NULL_RETURN(frameNode, slice);
    const auto& target = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(target, slice);
    return target->GetBackgroundImageResizableSliceValue(slice);
}

void ViewAbstract::SetOnTouchIntercept(FrameNode* frameNode, TouchInterceptFunc&& touchInterceptFunc)
{
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->SetOnTouchIntercept(std::move(touchInterceptFunc));
}

float ViewAbstract::GetLayoutWeight(FrameNode* frameNode)
{
    float layoutWeight = 0.0f;
    CHECK_NULL_RETURN(frameNode, layoutWeight);
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, layoutWeight);
    auto& magicItemProperty = layoutProperty->GetMagicItemProperty();
    if (magicItemProperty.HasLayoutWeight()) {
        return magicItemProperty.GetLayoutWeight().value_or(layoutWeight);
    }
    return layoutWeight;
}

int32_t ViewAbstract::GetDisplayIndex(FrameNode* frameNode)
{
    int32_t defaultDisplayIndex = 0;
    CHECK_NULL_RETURN(frameNode, defaultDisplayIndex);
    const auto& layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, defaultDisplayIndex);
    const auto& flexItemProperty = layoutProperty->GetFlexItemProperty();
    CHECK_NULL_RETURN(flexItemProperty, defaultDisplayIndex);
    return flexItemProperty->GetDisplayIndex().value_or(defaultDisplayIndex);
}

NG::BorderWidthProperty ViewAbstract::GetOuterBorderWidth(FrameNode* frameNode)
{
    BorderWidthProperty borderWidth;
    CHECK_NULL_RETURN(frameNode, borderWidth);
    auto context = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(context, borderWidth);
    auto outBorderWidth = context->GetOuterBorder()->GetOuterBorderWidth();
    CHECK_NULL_RETURN(outBorderWidth, borderWidth);
    return outBorderWidth.value_or(borderWidth);
}

void ViewAbstract::SetBias(FrameNode* frameNode, const BiasPair& biasPair)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LayoutProperty, Bias, biasPair, frameNode);
}

BiasPair ViewAbstract::GetBias(FrameNode* frameNode)
{
    BiasPair biasPair(-1.0f, -1.0f);
    CHECK_NULL_RETURN(frameNode, biasPair);
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, biasPair);
    CHECK_NULL_RETURN(layoutProperty->GetFlexItemProperty(), biasPair);
    return layoutProperty->GetFlexItemProperty()->GetBias().value_or(biasPair);
}

void ViewAbstract::ResetBias(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    CHECK_NULL_VOID(layoutProperty->GetFlexItemProperty());
    layoutProperty->GetFlexItemProperty()->ResetBias();
}

RenderFit ViewAbstract::GetRenderFit(FrameNode* frameNode)
{
    RenderFit defalutRenderFit = RenderFit::TOP_LEFT;
    CHECK_NULL_RETURN(frameNode, defalutRenderFit);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, defalutRenderFit);
    return renderContext->GetRenderFit().value_or(defalutRenderFit);
}

BorderColorProperty ViewAbstract::GetOuterBorderColor(FrameNode* frameNode)
{
    Color defaultColor(0xff000000);
    BorderColorProperty borderColors = { defaultColor, defaultColor, defaultColor, defaultColor,
        std::nullopt, std::nullopt };
    CHECK_NULL_RETURN(frameNode, borderColors);
    const auto& target = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(target, borderColors);
    return target->GetOuterBorderColorValue(borderColors);
}

bool ViewAbstract::GetRenderGroup(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, false);
    const auto& target = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(target, false);
    return target->GetRenderGroupValue(false);
}

void ViewAbstract::SetOnVisibleChange(FrameNode* frameNode, std::function<void(bool, double)>&& onVisibleChange,
    const std::vector<double> &ratioList)
{
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    frameNode->CleanVisibleAreaUserCallback();
    pipeline->AddVisibleAreaChangeNode(AceType::Claim<FrameNode>(frameNode), ratioList, onVisibleChange);
}

void ViewAbstract::SetOnVisibleAreaApproximateChange(FrameNode* frameNode,
    const std::function<void(bool, double)>&& onVisibleChange, const std::vector<double>& ratioList,
    int32_t expectedUpdateInterval)
{
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    frameNode->CleanVisibleAreaUserCallback(true);

    constexpr uint32_t minInterval = 100; // 100ms
    if (expectedUpdateInterval < 0 || static_cast<uint32_t>(expectedUpdateInterval) < minInterval) {
        expectedUpdateInterval = minInterval;
    }
    VisibleCallbackInfo callback;
    callback.callback = std::move(onVisibleChange);
    callback.isCurrentVisible = false;
    callback.period = static_cast<uint32_t>(expectedUpdateInterval);
    pipeline->AddVisibleAreaChangeNode(frameNode->GetId());
    frameNode->SetVisibleAreaUserCallback(ratioList, callback);
}

void ViewAbstract::SetOnVisibleAreaApproximateChange(const std::function<void(bool, double)>&& onVisibleChange,
    const std::vector<double>& ratioList, int32_t expectedUpdateInterval)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    CHECK_NULL_VOID(frameNode);
    frameNode->CleanVisibleAreaUserCallback(true);

    constexpr uint32_t minInterval = 100; // 100ms
    if (expectedUpdateInterval < 0 || static_cast<uint32_t>(expectedUpdateInterval) < minInterval) {
        expectedUpdateInterval = minInterval;
    }
    VisibleCallbackInfo callback;
    callback.callback = std::move(onVisibleChange);
    callback.isCurrentVisible = false;
    callback.period = static_cast<uint32_t>(expectedUpdateInterval);
    pipeline->AddVisibleAreaChangeNode(frameNode->GetId());
    frameNode->SetVisibleAreaUserCallback(ratioList, callback);
}

Color ViewAbstract::GetColorBlend(FrameNode* frameNode)
{
    Color defaultColor = Color::TRANSPARENT;
    CHECK_NULL_RETURN(frameNode, defaultColor);
    const auto& target = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(target, defaultColor);
    return target->GetFrontColorBlendValue(defaultColor);
}

void ViewAbstract::ResetAreaChanged(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    frameNode->ClearUserOnAreaChange();
    pipeline->RemoveOnAreaChangeNode(frameNode->GetId());
}

void ViewAbstract::ResetVisibleChange(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    frameNode->CleanVisibleAreaUserCallback();
    pipeline->RemoveVisibleAreaChangeNode(frameNode->GetId());
}

void ViewAbstract::SetLayoutRect(FrameNode* frameNode, const NG::RectF& rect)
{
    CHECK_NULL_VOID(frameNode);
    frameNode->SetIsMeasureBoundary(true);
    const auto& layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->SetLayoutRect(rect);
}

void ViewAbstract::ResetLayoutRect(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    frameNode->SetIsMeasureBoundary(false);
    const auto& layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->ResetLayoutRect();
}

NG::RectF ViewAbstract::GetLayoutRect(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, NG::RectF());
    const auto& layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, NG::RectF());
    return layoutProperty->GetLayoutRect().value_or(NG::RectF());
}

bool ViewAbstract::GetFocusOnTouch(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto focusHub = frameNode->GetFocusHub();
    CHECK_NULL_RETURN(focusHub, false);
    return focusHub->IsFocusOnTouch().value_or(false);
}

void ViewAbstract::SetFocusScopeId(const std::string& focusScopeId, bool isGroup, bool arrowKeyStepOut)
{
    auto focusHub = ViewStackProcessor::GetInstance()->GetOrCreateMainFrameNodeFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->SetFocusScopeId(focusScopeId, isGroup, arrowKeyStepOut);
}

void ViewAbstract::SetFocusScopePriority(const std::string& focusScopeId, const uint32_t focusPriority)
{
    auto focusHub = ViewStackProcessor::GetInstance()->GetOrCreateMainFrameNodeFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->SetFocusScopePriority(focusScopeId, focusPriority);
}

void ViewAbstract::SetFocusScopeId(FrameNode* frameNode, const std::string& focusScopeId, bool isGroup,
    bool arrowKeyStepOut)
{
    CHECK_NULL_VOID(frameNode);
    auto focusHub = frameNode->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->SetFocusScopeId(focusScopeId, isGroup, arrowKeyStepOut);
}

void ViewAbstract::SetFocusScopePriority(FrameNode* frameNode, const std::string& focusScopeId,
    const uint32_t focusPriority)
{
    CHECK_NULL_VOID(frameNode);
    auto focusHub = frameNode->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->SetFocusScopePriority(focusScopeId, focusPriority);
}

void ViewAbstract::FreezeUINodeById(const std::string& id, bool isFreeze)
{
    auto targetNode = ElementRegister::GetInstance()->GetAttachedFrameNodeById(id, true);
    CHECK_NULL_VOID(targetNode);
    auto pipeline = targetNode->GetContext();
    if (pipeline != nullptr) {
        pipeline->SetOpenInvisibleFreeze(true);
    }
    targetNode->SetFreeze(isFreeze, true, true);
}

void ViewAbstract::FreezeUINodeByUniqueId(const int32_t& uniqueId, bool isFreeze)
{
    auto targetNodeElement = ElementRegister::GetInstance()->GetNodeById(uniqueId);
    auto targetNode = AceType::DynamicCast<NG::FrameNode>(targetNodeElement);
    CHECK_NULL_VOID(targetNode);
    auto pipeline = targetNode->GetContext();
    if (pipeline != nullptr) {
        pipeline->SetOpenInvisibleFreeze(true);
    }
    targetNode->SetFreeze(isFreeze, true, true);
}

uint32_t ViewAbstract::GetSafeAreaExpandType(FrameNode* frameNode)
{
    uint32_t value = SAFE_AREA_TYPE_ALL;
    CHECK_NULL_RETURN(frameNode, value);
    const auto& layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, value);
    const auto& SafeAreaExpandOpts = layoutProperty->GetSafeAreaExpandOpts();
    CHECK_NULL_RETURN(SafeAreaExpandOpts, value);
    if (SafeAreaExpandOpts->type > 0) {
        value = SafeAreaExpandOpts->type;
    }
    return value;
}

uint32_t ViewAbstract::GetSafeAreaExpandEdges(FrameNode* frameNode)
{
    uint32_t value = SAFE_AREA_EDGE_ALL;
    CHECK_NULL_RETURN(frameNode, value);
    const auto& layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, value);
    const auto& SafeAreaExpandOpts = layoutProperty->GetSafeAreaExpandOpts();
    CHECK_NULL_RETURN(SafeAreaExpandOpts, value);
    if (SafeAreaExpandOpts->edges > 0) {
        value = SafeAreaExpandOpts->edges;
    }
    return value;
}

void ViewAbstract::SetPositionLocalizedEdges(bool needLocalized)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateNeedPositionLocalizedEdges(needLocalized);
}

void ViewAbstract::SetMarkAnchorStart(Dimension& markAnchorStart)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateMarkAnchorStart(markAnchorStart);
}

void ViewAbstract::ResetMarkAnchorStart()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->ResetMarkAnchorStart();
}

void ViewAbstract::SetOffsetLocalizedEdges(bool needLocalized)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateNeedOffsetLocalizedEdges(needLocalized);
}

void ViewAbstract::SetSystemColorModeChangeEvent(
    FrameNode* frameNode, std::function<void(int32_t)>&& onColorModeChange)
{
    CHECK_NULL_VOID(frameNode);
    frameNode->SetNDKColorModeUpdateCallback(std::move(onColorModeChange));
}

void ViewAbstract::SetSystemFontChangeEvent(FrameNode* frameNode, std::function<void(float, float)>&& onFontChange)
{
    CHECK_NULL_VOID(frameNode);
    frameNode->SetNDKFontUpdateCallback(std::move(onFontChange));
}

void ViewAbstract::SetDrawCompleteEvent(
    FrameNode* frameNode, std::function<void()>&& onDraw)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetNDKDrawCompletedCallback(std::move(onDraw));
}

void ViewAbstract::SetLayoutEvent(
    FrameNode* frameNode, std::function<void()>&& onLayout)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetNDKLayoutCallback(std::move(onLayout));
}

void ViewAbstract::AddCustomProperty(UINode* frameNode, const std::string& key, const std::string& value)
{
    CHECK_NULL_VOID(frameNode);
    frameNode->AddCustomProperty(key, value);
}

void ViewAbstract::RemoveCustomProperty(UINode* frameNode, const std::string& key)
{
    CHECK_NULL_VOID(frameNode);
    frameNode->RemoveCustomProperty(key);
}

int32_t ViewAbstract::CancelDataLoading(const std::string& key)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, -1);
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_RETURN(dragDropManager, -1);
    return dragDropManager->CancelUDMFDataLoading(key);
}

void ViewAbstract::SetDisableDataPrefetch(bool disableDataPrefetch)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetDisableDataPrefetch(disableDataPrefetch);
}

void ViewAbstract::SetDisableDataPrefetch(FrameNode* frameNode, bool disableDataPrefetch)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);

    eventHub->SetDisableDataPrefetch(disableDataPrefetch);
}

void ViewAbstract::SetJSFrameNodeOnReachStart(FrameNode* frameNode, OnReachEvent&& onReachStart)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollableEventHub>();
    CHECK_NULL_VOID(eventHub);

    eventHub->SetJSFrameNodeOnReachStart(std::move(onReachStart));
}

void ViewAbstract::ClearJSFrameNodeOnReachStart(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollableEventHub>();
    CHECK_NULL_VOID(eventHub);

    eventHub->ClearJSFrameNodeOnReachStart();
}

void ViewAbstract::SetJSFrameNodeOnReachEnd(FrameNode* frameNode, OnReachEvent&& onReachEnd)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollableEventHub>();
    CHECK_NULL_VOID(eventHub);

    eventHub->SetJSFrameNodeOnReachEnd(std::move(onReachEnd));
}

void ViewAbstract::ClearJSFrameNodeOnReachEnd(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollableEventHub>();
    CHECK_NULL_VOID(eventHub);

    eventHub->ClearJSFrameNodeOnReachEnd();
}

void ViewAbstract::SetJSFrameNodeOnScrollStart(FrameNode* frameNode, OnScrollStartEvent&& onScrollStart)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollableEventHub>();
    CHECK_NULL_VOID(eventHub);

    eventHub->SetJSFrameNodeOnScrollStart(std::move(onScrollStart));
}

void ViewAbstract::ClearJSFrameNodeOnScrollStart(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollableEventHub>();
    CHECK_NULL_VOID(eventHub);

    eventHub->ClearJSFrameNodeOnScrollStart();
}

void ViewAbstract::SetJSFrameNodeOnScrollStop(FrameNode* frameNode, OnScrollStopEvent&& onScrollStop)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollableEventHub>();
    CHECK_NULL_VOID(eventHub);

    eventHub->SetJSFrameNodeOnScrollStop(std::move(onScrollStop));
}

void ViewAbstract::ClearJSFrameNodeOnScrollStop(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollableEventHub>();
    CHECK_NULL_VOID(eventHub);

    eventHub->ClearJSFrameNodeOnScrollStop();
}

void ViewAbstract::SetJSFrameNodeOnScrollFrameBegin(FrameNode* frameNode, OnScrollFrameBeginEvent&& onScrollFrameBegin)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollableEventHub>();
    CHECK_NULL_VOID(eventHub);

    eventHub->SetJSFrameNodeOnScrollFrameBegin(std::move(onScrollFrameBegin));
}

void ViewAbstract::ClearJSFrameNodeOnScrollFrameBegin(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollableEventHub>();
    CHECK_NULL_VOID(eventHub);

    eventHub->ClearJSFrameNodeOnScrollFrameBegin();
}

void ViewAbstract::SetJSFrameNodeOnWillScroll(FrameNode* frameNode, OnWillScrollEvent&& onWillScroll)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollableEventHub>();
    CHECK_NULL_VOID(eventHub);

    eventHub->SetJSFrameNodeOnWillScroll(std::move(onWillScroll));
}

void ViewAbstract::ClearJSFrameNodeOnWillScroll(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollableEventHub>();
    CHECK_NULL_VOID(eventHub);

    eventHub->ClearJSFrameNodeOnWillScroll();
}

void ViewAbstract::SetJSFrameNodeOnDidScroll(FrameNode* frameNode, OnScrollEvent&& onDidScroll)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollableEventHub>();
    CHECK_NULL_VOID(eventHub);

    eventHub->SetJSFrameNodeOnDidScroll(std::move(onDidScroll));
}

void ViewAbstract::ClearJSFrameNodeOnDidScroll(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollableEventHub>();
    CHECK_NULL_VOID(eventHub);

    eventHub->ClearJSFrameNodeOnDidScroll();
}

void ViewAbstract::SetJSFrameNodeOnListScrollIndex(FrameNode* frameNode, OnScrollIndexEvent&& onScrollIndex)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ListEventHub>();
    CHECK_NULL_VOID(eventHub);

    eventHub->SetJSFrameNodeOnListScrollIndex(std::move(onScrollIndex));
}

void ViewAbstract::ClearJSFrameNodeOnListScrollIndex(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ListEventHub>();
    CHECK_NULL_VOID(eventHub);

    eventHub->ClearJSFrameNodeOnListScrollIndex();
}

void ViewAbstract::SetJSFrameNodeOnScrollVisibleContentChange(FrameNode* frameNode,
    OnScrollVisibleContentChangeEvent&& onScrollVisibleContentChange)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ListEventHub>();
    CHECK_NULL_VOID(eventHub);

    eventHub->SetJSFrameNodeOnScrollVisibleContentChange(std::move(onScrollVisibleContentChange));
}

void ViewAbstract::ClearJSFrameNodeOnScrollVisibleContentChange(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ListEventHub>();
    CHECK_NULL_VOID(eventHub);

    eventHub->ClearJSFrameNodeOnScrollVisibleContentChange();
}

void ViewAbstract::SetJSFrameNodeOnScrollWillScroll(FrameNode* frameNode, ScrollEventWithReturn&& onWillScroll)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollEventHub>();
    CHECK_NULL_VOID(eventHub);

    eventHub->SetJSFrameNodeOnScrollWillScroll(std::move(onWillScroll));
}

void ViewAbstract::ClearJSFrameNodeOnScrollWillScroll(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollEventHub>();
    CHECK_NULL_VOID(eventHub);

    eventHub->ClearJSFrameNodeOnScrollWillScroll();
}

void ViewAbstract::SetJSFrameNodeOnScrollDidScroll(FrameNode* frameNode, ScrollEventWithState&& onDidScroll)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollEventHub>();
    CHECK_NULL_VOID(eventHub);

    eventHub->SetJSFrameNodeOnScrollDidScroll(std::move(onDidScroll));
}

void ViewAbstract::ClearJSFrameNodeOnScrollDidScroll(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollEventHub>();
    CHECK_NULL_VOID(eventHub);

    eventHub->ClearJSFrameNodeOnScrollDidScroll();
}

void ViewAbstract::SetJSFrameNodeOnGridScrollIndex(FrameNode* frameNode, ScrollIndexFunc&& onScrollIndex)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<GridEventHub>();
    CHECK_NULL_VOID(eventHub);

    eventHub->SetJSFrameNodeOnGridScrollIndex(std::move(onScrollIndex));
}

void ViewAbstract::ClearJSFrameNodeOnGridScrollIndex(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<GridEventHub>();
    CHECK_NULL_VOID(eventHub);

    eventHub->ClearJSFrameNodeOnGridScrollIndex();
}

void ViewAbstract::SetJSFrameNodeOnWaterFlowScrollIndex(FrameNode* frameNode, ScrollIndexFunc&& onScrollIndex)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<WaterFlowEventHub>();
    CHECK_NULL_VOID(eventHub);

    eventHub->SetJSFrameNodeOnWaterFlowScrollIndex(std::move(onScrollIndex));
}

void ViewAbstract::ClearJSFrameNodeOnWaterFlowScrollIndex(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<WaterFlowEventHub>();
    CHECK_NULL_VOID(eventHub);

    eventHub->ClearJSFrameNodeOnWaterFlowScrollIndex();
}
} // namespace OHOS::Ace::NG
