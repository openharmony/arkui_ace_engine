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

#include "core/components_ng/pattern/tabs/tabs_node.h"

#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/pattern/swiper/swiper_layout_property.h"
#include "core/components_ng/pattern/swiper/swiper_paint_property.h"
#include "core/components_ng/pattern/tabs/tab_bar_layout_algorithm.h"
#include "core/components_ng/pattern/tabs/tab_bar_pattern.h"
#include "core/components_ng/pattern/tabs/tabs_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {

const std::string BAR_BLURSTYLE[] = {
    "BlurStyle.NONE",
    "BlurStyle.Thin",
    "BlurStyle.Regular",
    "BlurStyle.Thick",
    "BlurStyle.BACKGROUND_THIN",
    "BlurStyle.BACKGROUND_REGULAR",
    "BlurStyle.BACKGROUND_THICK",
    "BlurStyle.BACKGROUND_ULTRA_THICK",
    "BlurStyle.COMPONENT_ULTRA_THIN",
    "BlurStyle.COMPONENT_THIN",
    "BlurStyle.COMPONENT_REGULAR",
    "BlurStyle.COMPONENT_THICK",
    "BlurStyle.COMPONENT_ULTRA_THICK"
};

} // namespace

void TabsNode::AddChildToGroup(const RefPtr<UINode>& child, int32_t slot)
{
    if (swiperChildren_.find(child->GetId()) != swiperChildren_.end()) {
        return;
    }

    swiperChildren_.emplace(child->GetId());
    auto swiperNode = GetTabs();
    if (swiperNode) {
        child->MountToParent(swiperNode);
    }
}

void TabsNode::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    FrameNode::ToJsonValue(json, filter);
    json->PutFixedAttr("scrollable", Scrollable(), filter, FIXED_ATTR_SCROLLABLE);
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    json->PutExtAttr("index", std::to_string(GetIndex()).c_str(), filter);
    json->PutExtAttr("animationCurve", GetAnimationCurveStr(TabBarPhysicalCurve).c_str(), filter);
    json->PutExtAttr("animationDuration", GetAnimationDuration(), filter);
    if (GetTabBarMode() == TabBarMode::SCROLLABLE) {
        auto optionsJson = JsonUtil::Create(true);
        auto options = GetScrollableBarModeOptions();
        optionsJson->Put("margin", options.margin.ToString().c_str());
        if (options.nonScrollableLayoutStyle.value_or(LayoutStyle::ALWAYS_CENTER) == LayoutStyle::ALWAYS_CENTER) {
            optionsJson->Put("nonScrollableLayoutStyle", "LayoutStyle.ALWAYS_CENTER");
        } else if (options.nonScrollableLayoutStyle.value() == LayoutStyle::ALWAYS_AVERAGE_SPLIT) {
            optionsJson->Put("nonScrollableLayoutStyle", "LayoutStyle.ALWAYS_AVERAGE_SPLIT");
        } else if (options.nonScrollableLayoutStyle.value() == LayoutStyle::SPACE_BETWEEN_OR_CENTER) {
            optionsJson->Put("nonScrollableLayoutStyle", "LayoutStyle.SPACE_BETWEEN_OR_CENTER");
        }
        std::string barMode = "BarMode.Scrollable," + optionsJson->ToString();
        json->PutExtAttr("barMode", barMode.c_str(), filter);
    } else {
        json->PutExtAttr("barMode", "BarMode.Fixed", filter);
    }
    json->PutExtAttr("barWidth", std::to_string(GetBarWidth().Value()).c_str(), filter);
    json->PutExtAttr("barHeight",
        GetBarAdaptiveHeight() ? "auto" : std::to_string(GetBarHeight().Value()).c_str(), filter);
    json->PutExtAttr("fadingEdge", GetFadingEdge() ? "true" : "false", filter);
    json->PutExtAttr("barBackgroundColor", GetBarBackgroundColor().ColorToString().c_str(), filter);
    json->PutExtAttr("barBackgroundBlurStyle",
        BAR_BLURSTYLE[static_cast<int32_t>(GetBarBackgroundBlurStyle())].c_str(), filter);
    json->PutExtAttr("barBackgroundBlurStyleOptions", GetBarBackgroundBlurStyleOptions(), filter);
    json->PutExtAttr("animationMode", GetAnimationMode().c_str(), filter);
    json->PutExtAttr("edgeEffect", GetEdgeEffect().c_str(), filter);
    json->PutExtAttr("barBackgroundEffect", GetBarBackgroundEffect(), filter);

    auto barGridAlignJson = JsonUtil::Create(true);
    auto barGridAlign = GetBarGridAlign();
    barGridAlignJson->Put("gutter", barGridAlign.gutter.ToString().c_str());
    barGridAlignJson->Put("margin", barGridAlign.margin.ToString().c_str());
    barGridAlignJson->Put("sm", std::to_string(barGridAlign.sm).c_str());
    barGridAlignJson->Put("md", std::to_string(barGridAlign.md).c_str());
    barGridAlignJson->Put("lg", std::to_string(barGridAlign.lg).c_str());

    json->PutExtAttr("barGridAlign", barGridAlignJson, filter);
}

bool TabsNode::Scrollable() const
{
    if (!swiperId_.has_value()) {
        return true;
    }
    auto swiperNode = GetFrameNode(V2::SWIPER_ETS_TAG, swiperId_.value());
    CHECK_NULL_RETURN(swiperNode, true);
    auto props = swiperNode->GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(props, true);
    return !props->GetDisableSwipe().value_or(false);
}

const RefPtr<Curve> TabsNode::GetAnimationCurve(const RefPtr<Curve>& defaultCurve) const
{
    if (!swiperId_.has_value()) {
        return defaultCurve;
    }
    auto swiperNode = GetFrameNode(V2::SWIPER_ETS_TAG, swiperId_.value());
    CHECK_NULL_RETURN(swiperNode, defaultCurve);
    auto swiperPaintProperty = swiperNode->GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_RETURN(swiperPaintProperty, defaultCurve);
    auto curve = swiperPaintProperty->GetCurve().value_or(nullptr);
    CHECK_NULL_RETURN(curve, defaultCurve);
    return curve;
}

std::string TabsNode::GetAnimationCurveStr(const RefPtr<Curve>& defaultCurve) const
{
    auto curve = GetAnimationCurve(defaultCurve);
    return curve ? curve->ToString() : "null";
}

int32_t TabsNode::GetAnimationDuration() const
{
    int32_t duration = 0;
    if (!tabBarId_.has_value()) {
        return duration;
    }
    auto tabBarNode = GetFrameNode(V2::TAB_BAR_ETS_TAG, tabBarId_.value());
    CHECK_NULL_RETURN(tabBarNode, duration);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    CHECK_NULL_RETURN(tabBarPattern, duration);
    tabBarPattern->UpdateAnimationDuration();
    return tabBarPattern->GetAnimationDuration().value_or(duration);
}

int32_t TabsNode::GetIndex() const
{
    if (!swiperId_.has_value()) {
        return 0;
    }
    auto swiperNode = GetFrameNode(V2::SWIPER_ETS_TAG, swiperId_.value());
    CHECK_NULL_RETURN(swiperNode, 0);
    auto layoutProperty = swiperNode->GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, 0);
    return layoutProperty->GetIndex().value_or(0);
}

TabBarMode TabsNode::GetTabBarMode() const
{
    if (!tabBarId_.has_value()) {
        return TabBarMode::FIXED;
    }
    auto tabBarNode = GetFrameNode(V2::TAB_BAR_ETS_TAG, tabBarId_.value());
    CHECK_NULL_RETURN(tabBarNode, TabBarMode::FIXED);
    auto tabBarProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_RETURN(tabBarProperty, TabBarMode::FIXED);
    return tabBarProperty->GetTabBarMode().value_or(TabBarMode::FIXED);
}

Dimension TabsNode::GetBarWidth() const
{
    if (!tabBarId_.has_value()) {
        return 0.0_vp;
    }
    auto tabBarNode = GetFrameNode(V2::TAB_BAR_ETS_TAG, tabBarId_.value());
    CHECK_NULL_RETURN(tabBarNode, 0.0_vp);
    auto geometryNode = tabBarNode->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, 0.0_vp);
    auto frameSize = geometryNode->GetFrameSize();
    return Dimension(PipelineBase::Px2VpWithCurrentDensity(frameSize.Width()), DimensionUnit::VP);
}

bool TabsNode::GetBarAdaptiveHeight() const
{
    if (!tabBarId_.has_value()) {
        return false;
    }
    auto tabBarNode = GetFrameNode(V2::TAB_BAR_ETS_TAG, tabBarId_.value());
    CHECK_NULL_RETURN(tabBarNode, false);
    auto tabBarProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_RETURN(tabBarProperty, false);
    return tabBarProperty->GetBarAdaptiveHeight().value_or(false);
}

Dimension TabsNode::GetBarHeight() const
{
    if (!tabBarId_.has_value()) {
        return 0.0_vp;
    }
    auto tabBarNode = GetFrameNode(V2::TAB_BAR_ETS_TAG, tabBarId_.value());
    CHECK_NULL_RETURN(tabBarNode, 0.0_vp);
    auto geometryNode = tabBarNode->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, 0.0_vp);
    auto frameSize = geometryNode->GetFrameSize();
    return Dimension(PipelineBase::Px2VpWithCurrentDensity(frameSize.Height()), DimensionUnit::VP);
}

Color TabsNode::GetBarBackgroundColor() const
{
    auto backgroundColor = Color::BLACK.BlendOpacity(0.0f);
    if (!tabBarId_.has_value()) {
        return backgroundColor;
    }
    auto tabBarNode = GetFrameNode(V2::TAB_BAR_ETS_TAG, tabBarId_.value());
    CHECK_NULL_RETURN(tabBarNode, backgroundColor);
    auto tabBarRenderContext = tabBarNode->GetRenderContext();
    CHECK_NULL_RETURN(tabBarRenderContext, backgroundColor);
    return tabBarRenderContext->GetBackgroundColor().value_or(backgroundColor);
}

BlurStyle TabsNode::GetBarBackgroundBlurStyle() const
{
    auto barBackgroundBlurStyle = BlurStyle::NO_MATERIAL;
    if (!tabBarId_.has_value()) {
        return barBackgroundBlurStyle;
    }
    auto tabBarNode = GetFrameNode(V2::TAB_BAR_ETS_TAG, tabBarId_.value());
    CHECK_NULL_RETURN(tabBarNode, barBackgroundBlurStyle);
    auto tabBarRenderContext = tabBarNode->GetRenderContext();
    CHECK_NULL_RETURN(tabBarRenderContext, barBackgroundBlurStyle);
    auto styleOption = tabBarRenderContext->GetBackBlurStyle().value_or(BlurStyleOption{});
    return styleOption.blurStyle;
}

std::unique_ptr<JsonValue> TabsNode::GetBarBackgroundBlurStyleOptions() const
{
    auto jsonBlurStyle = JsonUtil::Create(true);
    if (!tabBarId_.has_value()) {
        return jsonBlurStyle;
    }
    static const char* COLOR_MODE[] = { "ThemeColorMode.System", "ThemeColorMode.Light", "ThemeColorMode.Dark" };
    static const char* ADAPTIVE_COLOR[] = { "AdaptiveColor.Default", "AdaptiveColor.Average" };
    static const char* POLICY[] = { "BlurStyleActivePolicy.FOLLOWS_WINDOW_ACTIVE_STATE",
        "BlurStyleActivePolicy.ALWAYS_ACTIVE", "BlurStyleActivePolicy.ALWAYS_INACTIVE" };
    static const char* BLUR_TYPE[] = { "BlurType.WITHIN_WINDOW", "BlurType.BEHIND_WINDOW" };
    auto tabBarNode = GetFrameNode(V2::TAB_BAR_ETS_TAG, tabBarId_.value());
    CHECK_NULL_RETURN(tabBarNode, jsonBlurStyle);
    auto tabBarRenderContext = tabBarNode->GetRenderContext();
    CHECK_NULL_RETURN(tabBarRenderContext, jsonBlurStyle);
    auto styleOption = tabBarRenderContext->GetBackBlurStyle().value_or(BlurStyleOption{});
    jsonBlurStyle->Put("colorMode", COLOR_MODE[static_cast<int>(styleOption.colorMode)]);
    jsonBlurStyle->Put("adaptiveColor",
        ADAPTIVE_COLOR[static_cast<int>(styleOption.adaptiveColor)]);
    jsonBlurStyle->Put("policy", POLICY[static_cast<int>(styleOption.policy)]);
    jsonBlurStyle->Put("type", BLUR_TYPE[static_cast<int>(styleOption.blurType)]);
    jsonBlurStyle->Put("inactiveColor", styleOption.inactiveColor.ColorToString().c_str());
    jsonBlurStyle->Put("scale", styleOption.scale);
    return jsonBlurStyle;
}

bool TabsNode::GetFadingEdge() const
{
    if (!tabBarId_.has_value()) {
        return true;
    }
    auto tabBarNode = GetFrameNode(V2::TAB_BAR_ETS_TAG, tabBarId_.value());
    CHECK_NULL_RETURN(tabBarNode, true);
    auto tabBarProperty = tabBarNode->GetPaintProperty<TabBarPaintProperty>();
    CHECK_NULL_RETURN(tabBarProperty, true);
    return tabBarProperty->GetFadingEdge().value_or(true);
}

BarGridColumnOptions TabsNode::GetBarGridAlign() const
{
    BarGridColumnOptions option;
    if (!tabBarId_.has_value()) {
        return option;
    }
    auto tabBarNode = GetFrameNode(V2::TAB_BAR_ETS_TAG, tabBarId_.value());
    CHECK_NULL_RETURN(tabBarNode, option);
    auto tabBarProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_RETURN(tabBarProperty, option);
    return tabBarProperty->GetBarGridAlign().value_or(option);
}

ScrollableBarModeOptions TabsNode::GetScrollableBarModeOptions() const
{
    ScrollableBarModeOptions option;
    if (!tabBarId_.has_value()) {
        return option;
    }
    auto tabBarNode = GetFrameNode(V2::TAB_BAR_ETS_TAG, tabBarId_.value());
    CHECK_NULL_RETURN(tabBarNode, option);
    auto tabBarProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_RETURN(tabBarProperty, option);
    return tabBarProperty->GetScrollableBarModeOptions().value_or(option);
}

std::string TabsNode::GetAnimationMode() const
{
    std::string ret = "AnimationMode.CONTENT_FIRST";
    auto tabsPattern = GetPattern<TabsPattern>();
    CHECK_NULL_RETURN(tabsPattern, ret);
    TabAnimateMode mode = tabsPattern->GetAnimateMode();
    switch (mode) {
        case TabAnimateMode::CONTENT_FIRST:
            ret = "AnimationMode.CONTENT_FIRST";
            break;
        case TabAnimateMode::ACTION_FIRST:
            ret = "AnimationMode.ACTION_FIRST";
            break;
        case TabAnimateMode::NO_ANIMATION:
            ret = "AnimationMode.NO_ANIMATION";
            break;
        case TabAnimateMode::CONTENT_FIRST_WITH_JUMP:
            ret = "AnimationMode.CONTENT_FIRST_WITH_JUMP";
            break;
        case TabAnimateMode::ACTION_FIRST_WITH_JUMP:
            ret = "AnimationMode.ACTION_FIRST_WITH_JUMP";
            break;
        default:
            ret = "AnimationMode.CONTENT_FIRST";
            break;
    }
    return ret;
}

std::string TabsNode::GetEdgeEffect() const
{
    std::string ret = "EdgeEffect::SPRING";
    if (!swiperId_.has_value()) {
        return ret;
    }
    auto swiperNode = GetFrameNode(V2::SWIPER_ETS_TAG, swiperId_.value());
    CHECK_NULL_RETURN(swiperNode, ret);
    auto paintProperty = swiperNode->GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_RETURN(paintProperty, ret);
    EdgeEffect edgeEffect = paintProperty->GetEdgeEffect().value();
    switch (edgeEffect) {
        case EdgeEffect::SPRING:
            ret = "EdgeEffect::SPRING";
            break;
        case EdgeEffect::FADE:
            ret = "EdgeEffect::FADE";
            break;
        case EdgeEffect::NONE:
            ret = "EdgeEffect::NONE";
            break;
        default:
            ret = "EdgeEffect::SPRING";
            break;
    }
    return ret;
}

std::unique_ptr<JsonValue> TabsNode::GetBarBackgroundEffect() const
{
    auto jsonEffect = JsonUtil::Create(true);
    if (!tabBarId_.has_value()) {
        return jsonEffect;
    }
    static const char* ADAPTIVE_COLOR[] = { "AdaptiveColor.Default", "AdaptiveColor.Average" };
    static const char* POLICY[] = { "BlurStyleActivePolicy.FOLLOWS_WINDOW_ACTIVE_STATE",
        "BlurStyleActivePolicy.ALWAYS_ACTIVE", "BlurStyleActivePolicy.ALWAYS_INACTIVE" };
    static const char* BLUR_TYPE[] = { "WITHIN_WINDOW", "BEHIND_WINDOW" };
    auto tabBarNode = GetFrameNode(V2::TAB_BAR_ETS_TAG, tabBarId_.value());
    CHECK_NULL_RETURN(tabBarNode, jsonEffect);
    auto tabBarRenderContext = tabBarNode->GetRenderContext();
    CHECK_NULL_RETURN(tabBarRenderContext, jsonEffect);
    EffectOption effectOption = tabBarRenderContext->GetBackgroundEffect().value_or(effectOption);
    jsonEffect->Put("radius", effectOption.radius.Value());
    jsonEffect->Put("saturation", effectOption.saturation);
    jsonEffect->Put("brightness", effectOption.brightness);
    jsonEffect->Put("color", effectOption.color.ColorToString().c_str());
    jsonEffect->Put("adaptiveColor", ADAPTIVE_COLOR[static_cast<int32_t>(effectOption.adaptiveColor)]);
    jsonEffect->Put("policy", POLICY[static_cast<int>(effectOption.policy)]);
    jsonEffect->Put("type", BLUR_TYPE[static_cast<int>(effectOption.blurType)]);
    jsonEffect->Put("inactiveColor", effectOption.inactiveColor.ColorToString().c_str());
    auto grayscale = "[0,0]";
    if (effectOption.blurOption.grayscale.size() > 1) {
        grayscale = ("[" + std::to_string(effectOption.blurOption.grayscale[0]) + "," +
            std::to_string(effectOption.blurOption.grayscale[1]) + "]").c_str();
    }
    jsonEffect->Put("blurOption", grayscale);
    return jsonEffect;
}
} // namespace OHOS::Ace::NG
