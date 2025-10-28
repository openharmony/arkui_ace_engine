/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components/tab_bar/tab_theme.h"
#include "core/components_ng/pattern/tabs/tabs_model_ng.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/components_ng/pattern/swiper/swiper_event_hub.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/pattern/tabs/tabs_pattern.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace Converter {
inline void AssignArkValue(Ark_TabContentAnimatedTransition& dst, const TabContentAnimatedTransition& src,
    ConvContext *ctx)
{
    dst.timeout.value = Converter::ArkValue<Ark_Int32>(src.timeout);
}
template<> void AssignArkValue(Opt_PageFlipMode& dst, const PageFlipMode& src, ConvContext *ctx);
} // Converter

namespace {
const auto ATTRIBUTE_BAR_WIDTH_NAME = "barWidthAttr";
const auto ATTRIBUTE_BAR_WIDTH_DEFAULT_VALUE = "0.00vp";
const auto ATTRIBUTE_BAR_HEIGHT_NAME = "barHeightAttr";
const auto ATTRIBUTE_BAR_HEIGHT_DEFAULT_VALUE = "0.00vp";
const auto ATTRIBUTE_BAR_BACKGROUND_COLOR_NAME = "barBackgroundColor";
const auto ATTRIBUTE_BAR_BACKGROUND_COLOR_DEFAULT_VALUE = "#00000000";
const auto ATTRIBUTE_BAR_BACKGROUND_EFFECT = "barBackgroundEffect";
const auto ATTRIBUTE_BAR_BACKGROUND_EFFECT_RADIUS = "radius";
const auto DEFAULT_BAR_BACKGROUND_EFFECT_RADIUS = 0.0;
const auto ATTRIBUTE_BAR_BACKGROUND_EFFECT_SATURATION = "saturation";
const auto DEFAULT_BAR_BACKGROUND_EFFECT_SATURATION = 1.0;
const auto ATTRIBUTE_BAR_BACKGROUND_EFFECT_BRIGHTNESS = "brightness";
const auto DEFAULT_BAR_BACKGROUND_EFFECT_BRIGHTNESS = 1.0;
const auto ATTRIBUTE_BAR_BACKGROUND_EFFECT_COLOR = "color";
const auto DEFAULT_BAR_BACKGROUND_EFFECT_COLOR = "#00000000";
const auto ATTRIBUTE_ADAPTIVE_COLOR = "adaptiveColor";
const auto DEFAULT_ADAPTIVE_COLOR = "AdaptiveColor.Default";
const auto ATTRIBUTE_POLICY = "policy";
const auto DEFAULT_POLICY = "BlurStyleActivePolicy.ALWAYS_ACTIVE";
const auto ATTRIBUTE_BAR_BACKGROUND_EFFECT_TYPE = "TYPE";
const auto DEFAULT_BAR_BACKGROUND_EFFECT_TYPE = "WITHIN_WINDOW";
const auto ATTRIBUTE_INACTIVE_COLOR = "inactiveColor";
const auto DEFAULT_INACTIVE_COLOR = "#00000000";
const auto ATTRIBUTE_BAR_BACKGROUND_BLUR_STYLE_OPTIONS = "barBackgroundBlurStyleOptions";
const auto ATTRIBUTE_BLUR_OPTION = "blurOption";
const auto ATTRIBUTE_BLUR_OPTION_COUNT = 2;
const auto ATTRIBUTE_BLUR_OPTION_POS0 = 0;
const auto ATTRIBUTE_BLUR_OPTION_POS1 = 1;
const auto DEFAULT_BLUR_OPTION = 0;
const auto ATTRIBUTE_BAR_GRID_ALIGN_NAME = "barGridAlign";
const auto ATTRIBUTE_BAR_GRID_ALIGN_SM_NAME = "sm";
const auto ATTRIBUTE_BAR_GRID_ALIGN_SM_DEFAULT_VALUE = "-1";
const auto ATTRIBUTE_BAR_GRID_ALIGN_MD_NAME = "md";
const auto ATTRIBUTE_BAR_GRID_ALIGN_MD_DEFAULT_VALUE = "-1";
const auto ATTRIBUTE_BAR_GRID_ALIGN_LG_NAME = "lg";
const auto ATTRIBUTE_BAR_GRID_ALIGN_LG_DEFAULT_VALUE = "-1";
const auto ATTRIBUTE_BAR_GRID_ALIGN_MARGIN_NAME = "margin";
const auto ATTRIBUTE_BAR_GRID_ALIGN_MARGIN_DEFAULT_VALUE = "0.00vp";
const auto ATTRIBUTE_BAR_GRID_ALIGN_GUTTER_NAME = "gutter";
const auto ATTRIBUTE_BAR_GRID_ALIGN_GUTTER_DEFAULT_VALUE = "0.00vp";
const auto ATTRIBUTE_COLOR_MODE = "colorMode";
const auto DEFAULT_COLOR_MODE = "ThemeColorMode.System";
const auto ATTRIBUTE_SCALE = "scale";
const auto COLOR_BLUE = "#FF0000FF";
const auto COLOR_GREEN = "#FF00FF00";
const auto COLOR_RED = "#FFFF0000";
const auto COLOR_TRANSPARENT = "#00000000";
const auto RES_NAME = NamedResourceId{"RES_NAME", ResourceType::COLOR};
const auto RES_ID = IntResourceId{11111, ResourceType::COLOR};
const auto RES_STRING_FAKE_ID = IntResourceId{22222, ResourceType::STRING};
const auto RES_STRING_REGISTERED_ID = IntResourceId{33333, ResourceType::STRING};
constexpr int32_t ANIMATION_DURATION_DEFAULT = 300;
constexpr double COMPARING_DELTA = 0.0001;
constexpr double GRAY_SCALE0 = 20.0;
constexpr double GRAY_SCALE1 = 30.0;
const auto POLICY = "BlurStyleActivePolicy.ALWAYS_INACTIVE";
const auto ADAPTIVE_COLOR_AVERAGE = "AdaptiveColor.Average";
const auto COLOR_MODE_DARK = "ThemeColorMode.Dark";
const auto EFFECT_COLOR = "#FF123123";
constexpr double EFFECT_RADIUS = 123.45;
constexpr double EFFECT_SATURATION = 0.123;
constexpr double EFFECT_BRIGHTNESS = 100;
constexpr double SCALE = 0.123;
constexpr double DEFAULT_SCALE = 1.0;
const auto ATTRIBUTE_PAGE_FLIP_MODE_DEFAULT_VALUE = 0;

Opt_ScrollableBarModeOptions CreateScrollableMode(Opt_Dimension margin, Ark_LayoutStyle layoutStyle)
{
    Opt_LayoutStyle nonScrollableLayoutStyle = Converter::ArkValue<Opt_LayoutStyle>(layoutStyle);
    Ark_ScrollableBarModeOptions options = {
        .margin = margin,
        .nonScrollableLayoutStyle = nonScrollableLayoutStyle
    };
    return Converter::ArkValue<Opt_ScrollableBarModeOptions>(options);
}

typedef std::pair<Ark_Boolean, std::string> BoolStrTestStep;
const std::vector<BoolStrTestStep> BOOL_STR_TEST_PLAN = {
    { false, "false" },
    { true, "true" },
    { 0, "false" },
    { -25, "true" },
    { 0, "false" },
    { 25, "true" },
    { false, "false" }
};
const int64_t FAKE_RES_ID(1234);
const std::vector<std::pair<Opt_ScrollableBarModeOptions, std::string>> SCROLLABLE_BAR_MODE_TEST_PLAN = {
    { CreateScrollableMode(Converter::ArkValue<Opt_Dimension>("70px"), ARK_LAYOUT_STYLE_ALWAYS_AVERAGE_SPLIT),
        "BarMode.Scrollable,"
        "{\"margin\":\"70.00px\","
        "\"nonScrollableLayoutStyle\":\"LayoutStyle.ALWAYS_AVERAGE_SPLIT\"}" },
    { CreateScrollableMode(Converter::ArkValue<Opt_Dimension>(32.7f), ARK_LAYOUT_STYLE_SPACE_BETWEEN_OR_CENTER),
        "BarMode.Scrollable,"
        "{\"margin\":\"32.70vp\","
        "\"nonScrollableLayoutStyle\":\"LayoutStyle.SPACE_BETWEEN_OR_CENTER\"}" },
    { CreateScrollableMode(Converter::ArkValue<Opt_Dimension>("10.00%"), static_cast<Ark_LayoutStyle>(25)),
        "BarMode.Scrollable,"
        "{\"margin\":\"0.00vp\","
        "\"nonScrollableLayoutStyle\":\"LayoutStyle.ALWAYS_CENTER\"}" },
    { CreateScrollableMode(Converter::ArkValue<Opt_Dimension>(-32.7f), ARK_LAYOUT_STYLE_ALWAYS_CENTER),
        "BarMode.Scrollable,"
        "{\"margin\":\"-32.70vp\","
        "\"nonScrollableLayoutStyle\":\"LayoutStyle.ALWAYS_CENTER\"}" },
    { CreateScrollableMode(Converter::ArkValue<Opt_Dimension>(FAKE_RES_ID),
        ARK_LAYOUT_STYLE_ALWAYS_AVERAGE_SPLIT),
        "BarMode.Scrollable,"
        "{\"margin\":\"10.00px\","
        "\"nonScrollableLayoutStyle\":\"LayoutStyle.ALWAYS_AVERAGE_SPLIT\"}"}
};

const auto RES_ARK_LENGTH = Converter::ArkValue<Ark_Length>(FAKE_RES_ID);

int32_t g_indexValue(0);
int32_t g_targetIndexValue(0);
float g_currentOffsetValue(0.0f);
float g_targetOffsetValue(0.0f);
float g_velocityValue(0.0f);
const int32_t INDEX(10);
const int32_t TARGET_INDEX(12);
const float CURRENT_OFFSET(0.2f);
const float TARGET_OFFSET(0.4f);
const float VELOCITY(0.6f);
const int32_t TO(16);
const int32_t CURRENT_INDEX(18);
const int32_t COMING_INDEX(20);
const auto CONTEXT_ID = 123;
} // namespace


class TabsModifierTest : public ModifierTestBase<GENERATED_ArkUITabsModifier,
                                 &GENERATED_ArkUINodeModifiers::getTabsModifier, GENERATED_ARKUI_TABS> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();
        auto themeStyle = SetupThemeStyle(THEME_PATTERN_TAB);
        themeStyle->SetAttr("tab_content_animation_duration", { .value = ANIMATION_DURATION_DEFAULT });
        SetupTheme<TabTheme>();
        AddResource(RES_STRING_REGISTERED_ID, "#FF00FF00");
    }
};

/**
 * @tc.name: setVerticalTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITabsModifier.setVertical
 * @tc.type: FUNC
 */
HWTEST_F(TabsModifierTest, setVerticalTest, TestSize.Level1)
{
    const std::string propName = "vertical";
    ASSERT_NE(modifier_->setVertical, nullptr);
    auto checkVal = GetAttrValue<std::string>(GetJsonValue(node_), propName);
    EXPECT_EQ(checkVal, "false");

    for (const auto& [value, expectVal] : BOOL_STR_TEST_PLAN) {
        auto inputValue = Converter::ArkValue<Opt_Boolean>(value);
        modifier_->setVertical(node_, &inputValue);
        checkVal = GetAttrValue<std::string>(GetJsonValue(node_), propName);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setFadingEdgeTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITabsModifier.setFadingEdge
 * @tc.type: FUNC
 */
HWTEST_F(TabsModifierTest, setFadingEdgeTest, TestSize.Level1)
{
    const std::string propName = "fadingEdge";
    ASSERT_NE(modifier_->setFadingEdge, nullptr);
    auto checkVal = GetAttrValue<std::string>(GetJsonValue(node_), propName);
    EXPECT_EQ(checkVal, "true");

    for (const auto& [value, expectVal] : BOOL_STR_TEST_PLAN) {
        auto inputValue = Converter::ArkValue<Opt_Boolean>(value);
        modifier_->setFadingEdge(node_, &inputValue);
        checkVal = GetAttrValue<std::string>(GetJsonValue(node_), propName);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setScrollableTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITabsModifier.setScrollable
 * @tc.type: FUNC
 */
HWTEST_F(TabsModifierTest, setScrollableTest, TestSize.Level1)
{
    const std::string propName = "scrollable";
    ASSERT_NE(modifier_->setScrollable, nullptr);
    auto checkVal = GetAttrValue<bool>(GetJsonValue(node_), propName);
    EXPECT_EQ(checkVal, true);

    typedef std::pair<Ark_Boolean, bool> BoolTestStep;
    const std::vector<BoolTestStep> boolTestPlan = {
        { false, false },
        { true, true },
        { 0, false },
        { -25, true },
        { 0, false },
        { 25, true },
        { false, false }
    };

    for (const auto& [value, expectVal] : boolTestPlan) {
        auto inputValue = Converter::ArkValue<Opt_Boolean>(value);
        modifier_->setScrollable(node_, &inputValue);
        auto json = GetJsonValue(node_);
        checkVal = GetAttrValue<bool>(json, propName);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setBarOverlapTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITabsModifier.setBarOverlap
 * @tc.type: FUNC
 */
HWTEST_F(TabsModifierTest, setBarOverlapTest, TestSize.Level1)
{
    const std::string propName = "barOverlap";
    ASSERT_NE(modifier_->setBarOverlap, nullptr);
    auto checkVal = GetAttrValue<std::string>(GetJsonValue(node_), propName);
    EXPECT_EQ(checkVal, "false");

    for (const auto& [value, expectVal] : BOOL_STR_TEST_PLAN) {
        auto inputValue = Converter::ArkValue<Opt_Boolean>(value);
        modifier_->setBarOverlap(node_, &inputValue);
        checkVal = GetAttrValue<std::string>(GetJsonValue(node_), propName);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setAnimationDurationTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITabsModifier.setAnimationDuration
 * @tc.type: FUNC
 */
HWTEST_F(TabsModifierTest, setAnimationDurationTest, TestSize.Level1)
{
    const std::string propName = "animationDuration";
    ASSERT_NE(modifier_->setAnimationDuration, nullptr);
    auto checkVal = GetAttrValue<int>(GetJsonValue(node_), propName);
    EXPECT_EQ(checkVal, ANIMATION_DURATION_DEFAULT);

    const std::vector<std::pair<Opt_Int32, int>> arkNumberTestPlan = {
        { Converter::ArkValue<Opt_Int32>(20), 20 },
        { Converter::ArkValue<Opt_Int32>(0), 0 },
        // now next step is failed, because Tabs component used incorrect default value 200
        { Converter::ArkValue<Opt_Int32>(-20), ANIMATION_DURATION_DEFAULT },
    };

    for (const auto& [value, expectVal] : arkNumberTestPlan) {
        modifier_->setAnimationDuration(node_, &value);
        checkVal = GetAttrValue<int>(GetJsonValue(node_), propName);
        EXPECT_EQ(checkVal, expectVal);
    }

    //value should not be changed
    modifier_->setAnimationDuration(node_, nullptr);
    checkVal = GetAttrValue<int>(GetJsonValue(node_), propName);
    EXPECT_EQ(checkVal, arkNumberTestPlan[arkNumberTestPlan.size()-1].second);
}

/**
 * @tc.name: setAnimationModeTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITabsModifier.setAnimationMode
 * @tc.type: FUNC
 */
HWTEST_F(TabsModifierTest, setAnimationModeTest, TestSize.Level1)
{
    const std::string propName = "animationMode";
    const auto defaultValue = "AnimationMode.CONTENT_FIRST";
    ASSERT_NE(modifier_->setAnimationMode, nullptr);
    auto checkVal = GetAttrValue<std::string>(GetJsonValue(node_), propName);
    EXPECT_EQ(checkVal, defaultValue);

    typedef std::pair<Opt_AnimationMode, std::string> AnimationModeTestStep;
    const std::vector<AnimationModeTestStep> animationModeTestPlan = {
        { Converter::ArkValue<Opt_AnimationMode>(ARK_ANIMATION_MODE_ACTION_FIRST), "AnimationMode.ACTION_FIRST" },
        { Converter::ArkValue<Opt_AnimationMode>(ARK_ANIMATION_MODE_CONTENT_FIRST), "AnimationMode.CONTENT_FIRST" },
        { Converter::ArkValue<Opt_AnimationMode>(ARK_ANIMATION_MODE_NO_ANIMATION), "AnimationMode.NO_ANIMATION" },
        { Converter::ArkValue<Opt_AnimationMode>(static_cast<Ark_AnimationMode>(25)), defaultValue },
        { Converter::ArkValue<Opt_AnimationMode>(ARK_ANIMATION_MODE_NO_ANIMATION), "AnimationMode.NO_ANIMATION" },
    };

    for (const auto& [value, expectVal] : animationModeTestPlan) {
        modifier_->setAnimationMode(node_, &value);
        checkVal = GetAttrValue<std::string>(GetJsonValue(node_), propName);
        EXPECT_EQ(checkVal, expectVal);
    }

    modifier_->setAnimationMode(node_, nullptr);
    checkVal = GetAttrValue<std::string>(GetJsonValue(node_), propName);
    EXPECT_EQ(checkVal, defaultValue);
}

/**
 * @tc.name: setEdgeEffectTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITabsModifier.setEdgeEffect
 * @tc.type: FUNC
 */
HWTEST_F(TabsModifierTest, setEdgeEffectTest, TestSize.Level1)
{
    const std::string propName = "edgeEffect";
    const auto defaultValue = "EdgeEffect::SPRING";
    ASSERT_NE(modifier_->setEdgeEffect, nullptr);
    auto checkVal = GetAttrValue<std::string>(GetJsonValue(node_), propName);
    EXPECT_EQ(checkVal, defaultValue);
    typedef std::pair<Opt_EdgeEffect, std::string> EdgeEffectTestStep;
    const std::vector<EdgeEffectTestStep> edgeEffectTestPlan = {
        { Converter::ArkValue<Opt_EdgeEffect>(ARK_EDGE_EFFECT_FADE), "EdgeEffect::FADE" },
        { Converter::ArkValue<Opt_EdgeEffect>(ARK_EDGE_EFFECT_SPRING), "EdgeEffect::SPRING" },
        { Converter::ArkValue<Opt_EdgeEffect>(ARK_EDGE_EFFECT_NONE), "EdgeEffect::NONE" },
        { Converter::ArkValue<Opt_EdgeEffect>(static_cast<Ark_EdgeEffect>(25)), defaultValue },
        { Converter::ArkValue<Opt_EdgeEffect>(ARK_EDGE_EFFECT_NONE), "EdgeEffect::NONE" }
    };

    for (const auto& [value, expectVal] : edgeEffectTestPlan) {
        modifier_->setEdgeEffect(node_, &value);
        checkVal = GetAttrValue<std::string>(GetJsonValue(node_), propName);
        EXPECT_EQ(checkVal, expectVal);
    }

    modifier_->setEdgeEffect(node_, nullptr);
    checkVal = GetAttrValue<std::string>(GetJsonValue(node_), propName);
    EXPECT_EQ(checkVal, defaultValue);
}

/**
 * @tc.name: setBarPositionTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITabsModifier.setBarPosition
 * @tc.type: FUNC
 */
HWTEST_F(TabsModifierTest, setBarPositionTest, TestSize.Level1)
{
    const auto defaultValue = "BarPosition.Start";
    const std::string propName = "barPosition";
    ASSERT_NE(modifier_->setBarPosition, nullptr);
    auto checkVal = GetAttrValue<std::string>(GetJsonValue(node_), propName);
    EXPECT_EQ(checkVal, defaultValue);

    const std::vector<std::pair<Opt_BarPosition, std::string>> BarPositionTestPlan = {
        { Converter::ArkValue<Opt_BarPosition>(ARK_BAR_POSITION_END), "BarPosition.End" },
        { Converter::ArkValue<Opt_BarPosition>(ARK_BAR_POSITION_START), "BarPosition.Start" },
        { Converter::ArkValue<Opt_BarPosition>(ARK_BAR_POSITION_END), "BarPosition.End" },
        { Converter::ArkValue<Opt_BarPosition>(Converter::INVALID_ENUM_VAL<Ark_BarPosition>), defaultValue },
        { Converter::ArkValue<Opt_BarPosition>(ARK_BAR_POSITION_END), "BarPosition.End" },
        { Converter::ArkValue<Opt_BarPosition>(), defaultValue },
    };

    for (const auto& [value, expectVal] : BarPositionTestPlan) {
        modifier_->setBarPosition(node_, &value);
        checkVal = GetAttrValue<std::string>(GetJsonValue(node_), propName);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setBarModeTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITabsModifier.setBarMode
 * @tc.type: FUNC
 */
HWTEST_F(TabsModifierTest, setBarModeTest, TestSize.Level1)
{
    const auto defaultValue = "BarMode.Fixed";
    const std::string propName = "barMode";
    ASSERT_NE(modifier_->setBarMode, nullptr);
    auto checkVal = GetAttrValue<std::string>(GetJsonValue(node_), propName);
    EXPECT_EQ(checkVal, defaultValue);

    std::string scrollableMode =
        "BarMode.Scrollable,{\"margin\":\"0.00vp\",\"nonScrollableLayoutStyle\":\"LayoutStyle.ALWAYS_CENTER\"}";
    const std::vector<std::pair<Opt_BarMode, std::string>> BarModeTestPlan = {
        { Converter::ArkValue<Opt_BarMode>(ARK_BAR_MODE_FIXED), "BarMode.Fixed" },
        { Converter::ArkValue<Opt_BarMode>(ARK_BAR_MODE_SCROLLABLE), scrollableMode },
        { Converter::ArkValue<Opt_BarMode>(Converter::INVALID_ENUM_VAL<Ark_BarMode>), defaultValue },
        { Converter::ArkValue<Opt_BarMode>(ARK_BAR_MODE_SCROLLABLE), scrollableMode },
        { Converter::ArkValue<Opt_BarMode>(), defaultValue },
    };

    for (const auto& [value, expectVal] : SCROLLABLE_BAR_MODE_TEST_PLAN) {
        auto mode = Converter::ArkValue<Opt_BarMode>(ARK_BAR_MODE_SCROLLABLE);
        modifier_->setBarMode(node_, &mode, &value);
        checkVal = GetAttrValue<std::string>(GetJsonValue(node_), propName);
        EXPECT_EQ(checkVal, expectVal);
    }

    for (const auto& [value, expectVal] : BarModeTestPlan) {
        modifier_->setBarMode(node_, &value, nullptr);
        checkVal = GetAttrValue<std::string>(GetJsonValue(node_), propName);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setBarBackgroundBlurStyle0Test
 * @tc.desc: Check the functionality of GENERATED_ArkUITabsModifier.setBarBackgroundBlurStyle0
 * @tc.type: FUNC
 */
HWTEST_F(TabsModifierTest, setBarBackgroundBlurStyle0Test, TestSize.Level1)
{
    const auto defaultValue = "BlurStyle.NONE";
    const std::string propName = "barBackgroundBlurStyle";
    ASSERT_NE(modifier_->setBarBackgroundBlurStyle0, nullptr);
    auto checkVal = GetAttrValue<std::string>(GetJsonValue(node_), propName);
    EXPECT_EQ(checkVal, defaultValue);

    const std::vector<std::pair<Opt_BlurStyle, std::string>> BlurStyleTestPlan = {
        { Converter::ArkValue<Opt_BlurStyle>(ARK_BLUR_STYLE_THIN), "BlurStyle.Thin" },
        { Converter::ArkValue<Opt_BlurStyle>(ARK_BLUR_STYLE_REGULAR), "BlurStyle.Regular" },
        { Converter::ArkValue<Opt_BlurStyle>(ARK_BLUR_STYLE_THICK), "BlurStyle.Thick" },
        { Converter::ArkValue<Opt_BlurStyle>(ARK_BLUR_STYLE_BACKGROUND_THIN), "BlurStyle.BACKGROUND_THIN" },
        { Converter::ArkValue<Opt_BlurStyle>(ARK_BLUR_STYLE_BACKGROUND_REGULAR), "BlurStyle.BACKGROUND_REGULAR" },
        { Converter::ArkValue<Opt_BlurStyle>(ARK_BLUR_STYLE_BACKGROUND_THICK), "BlurStyle.BACKGROUND_THICK" },
        { Converter::ArkValue<Opt_BlurStyle>(ARK_BLUR_STYLE_BACKGROUND_ULTRA_THICK),
            "BlurStyle.BACKGROUND_ULTRA_THICK" },
        { Converter::ArkValue<Opt_BlurStyle>(ARK_BLUR_STYLE_NONE), "BlurStyle.NONE" },
        { Converter::ArkValue<Opt_BlurStyle>(ARK_BLUR_STYLE_COMPONENT_ULTRA_THIN), "BlurStyle.COMPONENT_ULTRA_THIN" },
        { Converter::ArkValue<Opt_BlurStyle>(ARK_BLUR_STYLE_COMPONENT_THIN), "BlurStyle.COMPONENT_THIN" },
        { Converter::ArkValue<Opt_BlurStyle>(ARK_BLUR_STYLE_COMPONENT_REGULAR), "BlurStyle.COMPONENT_REGULAR" },
        { Converter::ArkValue<Opt_BlurStyle>(ARK_BLUR_STYLE_COMPONENT_THICK), "BlurStyle.COMPONENT_THICK" },
        { Converter::ArkValue<Opt_BlurStyle>(ARK_BLUR_STYLE_COMPONENT_ULTRA_THICK), "BlurStyle.COMPONENT_ULTRA_THICK" },
        { Converter::ArkValue<Opt_BlurStyle>(Converter::INVALID_ENUM_VAL<Ark_BlurStyle>), defaultValue },
        { Converter::ArkValue<Opt_BlurStyle>(ARK_BLUR_STYLE_THIN), "BlurStyle.Thin" },
        { Converter::ArkValue<Opt_BlurStyle>(), defaultValue },
    };

    for (const auto& [value, expectVal] : BlurStyleTestPlan) {
        modifier_->setBarBackgroundBlurStyle0(node_, &value);
        checkVal = GetAttrValue<std::string>(GetJsonValue(node_), propName);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setOnChangeTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITabsModifier.setOnChange
 * @tc.type: FUNC
 */
HWTEST_F(TabsModifierTest, setOnChangeTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto onChange =
        [](Ark_Int32 nodeId, const Ark_Int32 index) {
            g_indexValue = Converter::Convert<int32_t>(index);
        };
    auto func = Converter::ArkCallback<Opt_Callback_I32_Void>(onChange, CONTEXT_ID);
    ASSERT_NE(frameNode, nullptr);
    auto context = MockPipelineContext::GetCurrent();
    frameNode->AttachToMainTree(true, Referenced::RawPtr(context));
    modifier_->setOnChange(node_, &func);

    auto tabsNode = AceType::DynamicCast<TabsNode>(frameNode);
    ASSERT_NE(tabsNode, nullptr);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    ASSERT_NE(swiperNode, nullptr);
    auto eventHub = swiperNode->GetEventHub<SwiperEventHub>();
    ASSERT_NE(eventHub, nullptr);
    EXPECT_EQ(g_indexValue, 0);
    eventHub->FireChangeEvent(INDEX - 1, INDEX, false);
    EXPECT_EQ(g_indexValue, INDEX);
    g_indexValue = 0;
}

/**
 * @tc.name: setOnAnimationStartTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITabsModifier.setOnAnimationStart
 * @tc.type: FUNC
 */
HWTEST_F(TabsModifierTest, setOnAnimationStartTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto onAnimationStart =
        [](Ark_Int32 nodeId, const Ark_Int32 index, const Ark_Int32 targetIndex,
            const Ark_TabsAnimationEvent event) {
            g_indexValue = Converter::Convert<int32_t>(index);
            g_targetIndexValue = Converter::Convert<int32_t>(targetIndex);
            g_currentOffsetValue = Converter::Convert<float>(event.currentOffset);
            g_targetOffsetValue = Converter::Convert<float>(event.targetOffset);
            g_velocityValue = Converter::Convert<float>(event.velocity);
        };
    auto func = Converter::ArkCallback<Opt_OnTabsAnimationStartCallback>(onAnimationStart, CONTEXT_ID);
    modifier_->setOnAnimationStart(node_, &func);

    auto tabsNode = AceType::DynamicCast<TabsNode>(frameNode);
    ASSERT_NE(tabsNode, nullptr);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    ASSERT_NE(swiperNode, nullptr);
    auto eventHub = swiperNode->GetEventHub<SwiperEventHub>();
    ASSERT_NE(eventHub, nullptr);
    EXPECT_EQ(g_indexValue, 0);
    EXPECT_EQ(g_targetIndexValue, 0);
    EXPECT_EQ(g_currentOffsetValue, 0.0f);
    EXPECT_EQ(g_targetOffsetValue, 0.0f);
    EXPECT_EQ(g_velocityValue, 0.0f);
    AnimationCallbackInfo info;
    info.currentOffset = CURRENT_OFFSET;
    info.targetOffset = TARGET_OFFSET;
    info.velocity = VELOCITY;
    eventHub->FireAnimationStartEvent(INDEX, TARGET_INDEX, info);
    EXPECT_EQ(g_indexValue, INDEX);
    EXPECT_EQ(g_targetIndexValue, TARGET_INDEX);
    EXPECT_EQ(g_currentOffsetValue, CURRENT_OFFSET);
    EXPECT_EQ(g_targetOffsetValue, TARGET_OFFSET);
    EXPECT_EQ(g_velocityValue, VELOCITY);

    g_indexValue = 0;
    g_targetIndexValue = 0;
    g_currentOffsetValue = 0.0f;
    g_targetOffsetValue = 0.0f;
    g_velocityValue = 0.0f;
}

/**
 * @tc.name: setOnAnimationEndTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITabsModifier.setOnAnimationEnd
 * @tc.type: FUNC
 */
HWTEST_F(TabsModifierTest, setOnAnimationEndTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto onAnimationEnd =
        [](Ark_Int32 nodeId, const Ark_Int32 index, const Ark_TabsAnimationEvent event) {
            g_indexValue = Converter::Convert<int32_t>(index);
            g_currentOffsetValue = Converter::Convert<float>(event.currentOffset);
            g_targetOffsetValue = Converter::Convert<float>(event.targetOffset);
            g_velocityValue = Converter::Convert<float>(event.velocity);
        };
    auto func = Converter::ArkCallback<Opt_OnTabsAnimationEndCallback>(onAnimationEnd, CONTEXT_ID);
    modifier_->setOnAnimationEnd(node_, &func);

    auto tabsNode = AceType::DynamicCast<TabsNode>(frameNode);
    ASSERT_NE(tabsNode, nullptr);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    ASSERT_NE(swiperNode, nullptr);
    auto eventHub = swiperNode->GetEventHub<SwiperEventHub>();
    ASSERT_NE(eventHub, nullptr);
    EXPECT_EQ(g_indexValue, 0);
    EXPECT_EQ(g_currentOffsetValue, 0.0f);
    EXPECT_EQ(g_targetOffsetValue, 0.0f);
    EXPECT_EQ(g_velocityValue, 0.0f);
    AnimationCallbackInfo info;
    info.currentOffset = CURRENT_OFFSET;
    info.targetOffset = TARGET_OFFSET;
    info.velocity = VELOCITY;
    // the start animation before is required for the end of animation testing
    eventHub->FireAnimationStartEvent(0, 0, {});
    eventHub->FireAnimationEndEvent(INDEX, info);
    EXPECT_EQ(g_indexValue, INDEX);
    EXPECT_EQ(g_currentOffsetValue, CURRENT_OFFSET);
    EXPECT_EQ(g_targetOffsetValue, TARGET_OFFSET);
    EXPECT_EQ(g_velocityValue, VELOCITY);

    g_indexValue = 0;
    g_currentOffsetValue = 0.0f;
    g_targetOffsetValue = 0.0f;
    g_velocityValue = 0.0f;
}

/**
 * @tc.name: setOnGestureSwipeTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITabsModifier.setOnGestureSwipe
 * @tc.type: FUNC
 */
HWTEST_F(TabsModifierTest, setOnGestureSwipeTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto onGestureSwipe =
        [](Ark_Int32 nodeId, const Ark_Int32 index, const Ark_TabsAnimationEvent event) {
            g_indexValue = Converter::Convert<int32_t>(index);
            g_currentOffsetValue = Converter::Convert<float>(event.currentOffset);
            g_targetOffsetValue = Converter::Convert<float>(event.targetOffset);
            g_velocityValue = Converter::Convert<float>(event.velocity);
        };
    auto func = Converter::ArkCallback<Opt_OnTabsGestureSwipeCallback>(onGestureSwipe, CONTEXT_ID);
    modifier_->setOnGestureSwipe(node_, &func);

    auto tabsNode = AceType::DynamicCast<TabsNode>(frameNode);
    ASSERT_NE(tabsNode, nullptr);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    ASSERT_NE(swiperNode, nullptr);
    auto eventHub = swiperNode->GetEventHub<SwiperEventHub>();
    ASSERT_NE(eventHub, nullptr);
    EXPECT_EQ(g_indexValue, 0);
    EXPECT_EQ(g_currentOffsetValue, 0.0f);
    EXPECT_EQ(g_targetOffsetValue, 0.0f);
    EXPECT_EQ(g_velocityValue, 0.0f);
    AnimationCallbackInfo info;
    info.currentOffset = CURRENT_OFFSET;
    info.targetOffset = TARGET_OFFSET;
    info.velocity = VELOCITY;
    eventHub->FireGestureSwipeEvent(INDEX, info);
    EXPECT_EQ(g_indexValue, INDEX);
    EXPECT_EQ(g_currentOffsetValue, CURRENT_OFFSET);
    EXPECT_EQ(g_targetOffsetValue, TARGET_OFFSET);
    EXPECT_EQ(g_velocityValue, VELOCITY);

    g_indexValue = 0;
    g_currentOffsetValue = 0.0f;
    g_targetOffsetValue = 0.0f;
    g_velocityValue = 0.0f;
}

/**
 * @tc.name: setCustomContentTransitionTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITabsModifier.setCustomContentTransition
 * @tc.type: FUNC
 */
HWTEST_F(TabsModifierTest, setCustomContentTransitionTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto tabsNode = AceType::DynamicCast<TabsNode>(frameNode);
    ASSERT_NE(tabsNode, nullptr);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    ASSERT_NE(swiperNode, nullptr);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    static const Ark_Int32 expectedResId = 123;
    static bool called = false;
    auto onTransition = [](Ark_VMContext context, const Ark_Int32 resourceId,
        const Ark_Int32 from, const Ark_Int32 to,
        const Callback_Opt_TabContentAnimatedTransition_Void cbReturn) {
        called = true;
        EXPECT_EQ(resourceId, expectedResId);
        EXPECT_EQ(Converter::Convert<int32_t>(to), TO);
        TabContentAnimatedTransition result;
        CallbackHelper(cbReturn).InvokeSync(Converter::ArkValue<Opt_TabContentAnimatedTransition>(result));
    };
    auto arkFunc = Converter::ArkCallback<Opt_TabsCustomContentTransitionCallback>(onTransition, expectedResId);
    modifier_->setCustomContentTransition(node_, &arkFunc);
    swiperPattern->OnCustomContentTransition(TO);
    EXPECT_TRUE(called);
}

/**
 * @tc.name: setOnContentWillChangeTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITabsModifier.setOnContentWillChange
 * @tc.type: FUNC
 */
HWTEST_F(TabsModifierTest, setOnContentWillChangeTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(frameNode);
    ASSERT_NE(tabsNode, nullptr);
    auto tabPattern = tabsNode->GetPattern<TabsPattern>();
    ASSERT_NE(tabPattern, nullptr);
    ASSERT_NE(modifier_->setOnContentWillChange, nullptr);
    modifier_->setOnContentWillChange(node_, nullptr);

    static const Ark_Int32 expectedResId = 123;
    auto onContentWillChange = [](Ark_VMContext context, const Ark_Int32 resourceId,
        const Ark_Int32 currentIndex, const Ark_Int32 comingIndex, const Callback_Boolean_Void cbReturn) {
        EXPECT_EQ(resourceId, expectedResId);
        EXPECT_EQ(Converter::Convert<int32_t>(currentIndex), CURRENT_INDEX);
        EXPECT_EQ(Converter::Convert<int32_t>(comingIndex), COMING_INDEX);
        bool result = Converter::Convert<int32_t>(comingIndex) > 0;
        CallbackHelper(cbReturn).InvokeSync(Converter::ArkValue<Ark_Boolean>(result));
    };
    auto arkFunc = Converter::ArkCallback<Opt_OnTabsContentWillChangeCallback>(onContentWillChange, expectedResId);
    modifier_->setOnContentWillChange(node_, &arkFunc);

    auto called = tabPattern->OnContentWillChange(CURRENT_INDEX, COMING_INDEX);
    EXPECT_TRUE(called);
}

/**
 * @tc.name: setOnTabBarClickTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITabsModifier.setOnTabBarClick
 * @tc.type: FUNC
 */
HWTEST_F(TabsModifierTest, setOnTabBarClickTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto onTabBarClick =
        [](Ark_Int32 nodeId, const Ark_Int32 index) {
            g_indexValue = Converter::Convert<int32_t>(index);
        };
    auto func = Converter::ArkCallback<Opt_Callback_I32_Void>(onTabBarClick);
    modifier_->setOnTabBarClick(node_, &func);
    EXPECT_EQ(g_indexValue, 0);

    auto tabsNode = AceType::DynamicCast<TabsNode>(frameNode);
    ASSERT_NE(tabsNode, nullptr);
    auto tabsPattern = tabsNode->GetPattern<TabsPattern>();
    ASSERT_NE(tabsPattern, nullptr);
    auto tabBarClickEvent = tabsPattern->GetTabBarClickEvent();
    ASSERT_NE(tabBarClickEvent, nullptr);
    auto event = *tabBarClickEvent;
    event(INDEX);
    EXPECT_EQ(g_indexValue, INDEX);
    g_indexValue = 0;
}

/*
 * @tc.name: setBarWidthTestDefaultValues
 * @tc.desc: Check the functionality of GENERATED_ArkUITabsModifier.setBarWidth
 * @tc.type: FUNC
 */
HWTEST_F(TabsModifierTest, setBarWidthTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BAR_WIDTH_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_BAR_WIDTH_DEFAULT_VALUE);
}

// Valid values for attribute 'barWidth' of method 'barWidth'
static std::vector<std::tuple<std::string, Opt_Length, std::string>> barSizeValidValues = {
    {"2.45", Converter::ArkValue<Opt_Length>(2.45), "2.45vp"},
    {"5.0px", Converter::ArkValue<Opt_Length>("5.0px"), "5.00px"},
    {"22.35px", Converter::ArkValue<Opt_Length>("22.35px"), "22.35px"},
    {"7.0vp", Converter::ArkValue<Opt_Length>("7.0vp"), "7.00vp"},
    {"1.65vp", Converter::ArkValue<Opt_Length>("1.65vp"), "1.65vp"},
    {"65.00fp", Converter::ArkValue<Opt_Length>("65.0fp"), "65.00fp"},
    {"4.3fp", Converter::ArkValue<Opt_Length>("4.3fp"), "4.30fp"},
    {"12%", Converter::ArkValue<Opt_Length>("12.00%"), "12.00%"},
    {"RES_ARK_LENGTH", Converter::ArkValue<Opt_Length>(RES_ARK_LENGTH), "10.00px"},
};

/*
 * @tc.name: setBarWidthTestValidValues
 * @tc.desc: Check the functionality of GENERATED_ArkUITabsModifier.setBarWidth
 * @tc.type: FUNC
 */
HWTEST_F(TabsModifierTest, setBarWidthTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;

    // Verifying attribute's  values
    for (auto&& value: barSizeValidValues) {
        auto inputValueBarWidth = std::get<1>(value);
        modifier_->setBarWidth(node_, &inputValueBarWidth);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BAR_WIDTH_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

// Invalid values for attribute 'barWidth' of method 'barWidth'
static std::vector<std::tuple<std::string, Opt_Length>> barSizeInvalidValues = {
    {"-2.45", Converter::ArkValue<Opt_Length>(-2.45)},
    {"-5.0px", Converter::ArkValue<Opt_Length>("-5.0px")},
    {"-22.35px", Converter::ArkValue<Opt_Length>("-22.35px")},
    {"-7.0vp", Converter::ArkValue<Opt_Length>("-7.0vp")},
    {"-1.65vp", Converter::ArkValue<Opt_Length>("-1.65vp")},
    {"-65.00fp", Converter::ArkValue<Opt_Length>("-65.0fp")},
    {"-4.3fp", Converter::ArkValue<Opt_Length>("-4.3fp")},
    {"-12%", Converter::ArkValue<Opt_Length>("-12%")},
};

/*
 * @tc.name: setBarWidthTestInvalidValues
 * @tc.desc: Check the functionality of GENERATED_ArkUITabsModifier.setBarWidth
 * @tc.type: FUNC
 */
HWTEST_F(TabsModifierTest, setBarWidthTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;

    // Initial setup
    auto initValueBarWidth = std::get<1>(barSizeValidValues[0]);

    // Verifying attribute's  values
    for (auto&& value: barSizeInvalidValues) {
        auto inputValueBarWidth = initValueBarWidth;
        modifier_->setBarWidth(node_, &inputValueBarWidth);
        inputValueBarWidth = std::get<1>(value);
        modifier_->setBarWidth(node_, &inputValueBarWidth);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BAR_WIDTH_NAME);
        expectedStr = ATTRIBUTE_BAR_WIDTH_DEFAULT_VALUE;
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setBarHeightTestDefaultValues
 * @tc.desc: Check the functionality of GENERATED_ArkUITabsModifier.setBarHeight
 * @tc.type: FUNC
 */
HWTEST_F(TabsModifierTest, setBarHeightTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BAR_HEIGHT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_BAR_HEIGHT_DEFAULT_VALUE);
}

// Valid values for attribute 'barHeight' of method 'barHeight'
static std::vector<std::tuple<std::string, Ark_Length, std::string>> barHeightBarHeightValidValues = {
};

/*
 * @tc.name: setBarHeightTestValidValues
 * @tc.desc: Check the functionality of GENERATED_ArkUITabsModifier.setBarHeight
 * @tc.type: FUNC
 */
HWTEST_F(TabsModifierTest, setBarHeightTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;

    // Verifying attribute's  values
    for (auto&& value: barSizeValidValues) {
        auto inputValueBarHeight = std::get<1>(value);
        modifier_->setBarHeight(node_, &inputValueBarHeight);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BAR_HEIGHT_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setBarHeightTestInvalidValues
 * @tc.desc: Check the functionality of GENERATED_ArkUITabsModifier.setBarHeight
 * @tc.type: FUNC
 */
HWTEST_F(TabsModifierTest, setBarHeightTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;

    // Initial setup
    auto initValueBarHeight = std::get<1>(barSizeValidValues[0]);

    // Verifying attribute's  values
    for (auto&& value: barSizeInvalidValues) {
        auto inputValueBarHeight = initValueBarHeight;
        modifier_->setBarHeight(node_, &inputValueBarHeight);
        inputValueBarHeight = std::get<1>(value);
        modifier_->setBarHeight(node_, &inputValueBarHeight);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BAR_HEIGHT_NAME);
        expectedStr = ATTRIBUTE_BAR_HEIGHT_DEFAULT_VALUE;
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/**
 * @tc.name: setDividerTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITabsModifier.setDivider
 * @tc.type: FUNC
 */
HWTEST_F(TabsModifierTest, setDividerTest, TestSize.Level1)
{
    // default values
    auto fullJson = GetJsonValue(node_);
    auto dividerObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "divider");
    auto dividerCheckValue = dividerObject->ToString();
    EXPECT_EQ(dividerCheckValue, "{}");

    // set valid values, color as Ark_Color aka int
    Ark_DividerStyle dividerOptions = {
        .strokeWidth = Converter::ArkValue<Opt_Length>("11px"),
        .startMargin = Converter::ArkValue<Opt_Length>(55.5),
        .endMargin = Converter::ArkValue<Opt_Length>("77px"),
        .color = Converter::ArkUnion<Opt_ResourceColor, Ark_Color>(ARK_COLOR_WHITE),
    };
    auto divider = Converter::ArkValue<Opt_DividerStyle>(dividerOptions);
    modifier_->setDivider(node_, &divider);
    fullJson = GetJsonValue(node_);
    dividerObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "divider");
    auto strokeWidthCheckValue = GetAttrValue<std::string>(dividerObject, "strokeWidth");
    EXPECT_EQ(strokeWidthCheckValue, "11.00px");
    auto startMarginCheckValue = GetAttrValue<std::string>(dividerObject, "startMargin");
    EXPECT_EQ(startMarginCheckValue, "55.50vp");
    auto endMarginCheckValue = GetAttrValue<std::string>(dividerObject, "endMargin");
    EXPECT_EQ(endMarginCheckValue, "77.00px");
    auto colorCheckValue = GetAttrValue<std::string>(dividerObject, "color");
    EXPECT_EQ(colorCheckValue, "#FFFFFFFF");

    // set color as Ark_Number
    dividerOptions.color = Converter::ArkUnion<Opt_ResourceColor, Ark_Int32>(0x123456);

    divider = Converter::ArkValue<Opt_DividerStyle>(dividerOptions);
    modifier_->setDivider(node_, &divider);
    fullJson = GetJsonValue(node_);
    dividerObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "divider");
    colorCheckValue = GetAttrValue<std::string>(dividerObject, "color");
    EXPECT_EQ(colorCheckValue, "#FF123456");
}

/**
 * @tc.name: setDividerUndefinedTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITabsModifier.setDivider
 * @tc.type: FUNC
 */
HWTEST_F(TabsModifierTest, setDividerUndefinedTest, TestSize.Level1)
{
    // set undefined values
    Ark_DividerStyle dividerOptions = {
        .strokeWidth = Converter::ArkValue<Opt_Length>("11px"),
        .startMargin = Converter::ArkValue<Opt_Length>(Ark_Empty()),
        .endMargin = Converter::ArkValue<Opt_Length>(Ark_Empty()),
        .color = Converter::ArkValue<Opt_ResourceColor>(),
    };
    auto divider = Converter::ArkValue<Opt_DividerStyle>(dividerOptions);
    modifier_->setDivider(node_, &divider);
    auto fullJson = GetJsonValue(node_);
    auto dividerObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "divider");
    auto strokeWidthCheckValue = GetAttrValue<std::string>(dividerObject, "strokeWidth");
    EXPECT_EQ(strokeWidthCheckValue, "11.00px");
    auto startMarginCheckValue = GetAttrValue<std::string>(dividerObject, "startMargin");
    EXPECT_EQ(startMarginCheckValue, "0.00vp");
    auto endMarginCheckValue = GetAttrValue<std::string>(dividerObject, "endMargin");
    EXPECT_EQ(endMarginCheckValue, "0.00vp");
    auto colorCheckValue = GetAttrValue<std::string>(dividerObject, "color");
    EXPECT_EQ(colorCheckValue, "#FF000000");
}

/**
 * @tc.name: setDividerColorStringTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITabsModifier.setDivider
 * @tc.type: FUNC
 */
HWTEST_F(TabsModifierTest, setDividerColorStringTest, TestSize.Level1)
{
    // set color as Ark_String
    Ark_DividerStyle dividerOptions = {
        .strokeWidth = Converter::ArkValue<Opt_Length>("11px"),
        .startMargin = Converter::ArkValue<Opt_Length>(55.5),
        .endMargin = Converter::ArkValue<Opt_Length>("77px"),
        .color = Converter::ArkUnion<Opt_ResourceColor, Ark_String>("#11223344"),
    };
    auto divider = Converter::ArkValue<Opt_DividerStyle>(dividerOptions);
    modifier_->setDivider(node_, &divider);
    auto fullJson = GetJsonValue(node_);
    auto dividerObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "divider");
    auto strokeWidthCheckValue = GetAttrValue<std::string>(dividerObject, "strokeWidth");
    EXPECT_EQ(strokeWidthCheckValue, "11.00px");
    auto startMarginCheckValue = GetAttrValue<std::string>(dividerObject, "startMargin");
    EXPECT_EQ(startMarginCheckValue, "55.50vp");
    auto endMarginCheckValue = GetAttrValue<std::string>(dividerObject, "endMargin");
    EXPECT_EQ(endMarginCheckValue, "77.00px");
    auto colorCheckValue = GetAttrValue<std::string>(dividerObject, "color");
    EXPECT_EQ(colorCheckValue, "#11223344");
}

/**
 * @tc.name: setDividerNullTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITabsModifier.setDivider
 * @tc.type: FUNC
 */
HWTEST_F(TabsModifierTest, setDividerNullTest, TestSize.Level1)
{
    auto divider = Converter::ArkValue<Opt_DividerStyle>();
    modifier_->setDivider(node_, &divider);
    auto fullJson = GetJsonValue(node_);
    auto dividerObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "divider");

    auto dividerCheckValue = dividerObject->ToString();
    EXPECT_EQ(dividerCheckValue, "{}");
}

/*
 * @tc.name: setBarBackgroundEffectTestDefaultValues
 * @tc.desc: Check the functionality of GENERATED_ArkUITabsModifier.setBarBackgroundEffect
 * @tc.type: FUNC
 */
HWTEST_F(TabsModifierTest, setBarBackgroundEffectTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    ASSERT_NE(jsonValue, nullptr);
    auto effect = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_BAR_BACKGROUND_EFFECT);
    ASSERT_NE(effect, nullptr);
    auto radius = GetAttrValue<double>(effect, ATTRIBUTE_BAR_BACKGROUND_EFFECT_RADIUS);
    ASSERT_NEAR(radius, DEFAULT_BAR_BACKGROUND_EFFECT_RADIUS, COMPARING_DELTA);
    auto saturation = GetAttrValue<double>(effect, ATTRIBUTE_BAR_BACKGROUND_EFFECT_SATURATION);
    ASSERT_NEAR(saturation, DEFAULT_BAR_BACKGROUND_EFFECT_SATURATION, COMPARING_DELTA);
    auto brightness = GetAttrValue<double>(effect, ATTRIBUTE_BAR_BACKGROUND_EFFECT_BRIGHTNESS);
    ASSERT_NEAR(brightness, DEFAULT_BAR_BACKGROUND_EFFECT_BRIGHTNESS, COMPARING_DELTA);
    auto color = GetAttrValue<std::string>(effect, ATTRIBUTE_BAR_BACKGROUND_EFFECT_COLOR);
    EXPECT_EQ(color, DEFAULT_BAR_BACKGROUND_EFFECT_COLOR);
    auto adaptiveColor = GetAttrValue<std::string>(effect, ATTRIBUTE_ADAPTIVE_COLOR);
    EXPECT_EQ(adaptiveColor, DEFAULT_ADAPTIVE_COLOR);
    auto policy = GetAttrValue<std::string>(effect, ATTRIBUTE_POLICY);
    EXPECT_EQ(policy, DEFAULT_POLICY);
    auto type = GetAttrValue<std::string>(effect, ATTRIBUTE_BAR_BACKGROUND_EFFECT_TYPE);
    EXPECT_EQ(type, DEFAULT_BAR_BACKGROUND_EFFECT_TYPE);
    auto inactiveColor = GetAttrValue<std::string>(effect, ATTRIBUTE_INACTIVE_COLOR);
    EXPECT_EQ(inactiveColor, DEFAULT_INACTIVE_COLOR);
    auto blurOption = GetAttrValue<std::unique_ptr<JsonValue>>(effect, ATTRIBUTE_BLUR_OPTION);
    ASSERT_NE(blurOption, nullptr);
    ASSERT_EQ(blurOption->GetArraySize(), ATTRIBUTE_BLUR_OPTION_COUNT);
    auto gray1 = blurOption->GetArrayItem(ATTRIBUTE_BLUR_OPTION_POS0);
    ASSERT_NE(gray1, nullptr);
    ASSERT_NEAR(gray1->GetDouble(), DEFAULT_BLUR_OPTION, COMPARING_DELTA);
    auto gray2 = blurOption->GetArrayItem(ATTRIBUTE_BLUR_OPTION_POS1);
    ASSERT_NE(gray2, nullptr);
    ASSERT_NEAR(gray2->GetDouble(), DEFAULT_BLUR_OPTION, COMPARING_DELTA);
}

/*
 * @tc.name: setBarBackgroundEffectTestValidValues
 * @tc.desc: Check the functionality of GENERATED_ArkUITabsModifier.setBarBackgroundEffect
 * @tc.type: FUNC
 */
HWTEST_F(TabsModifierTest, DISABLED_setBarBackgroundEffectTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setBarBackgroundEffect, nullptr);
    Ark_BackgroundEffectOptions inputValValid = {
        .radius = Converter::ArkValue<Ark_Float64>(EFFECT_RADIUS),
        .saturation = Converter::ArkValue<Opt_Float64>(EFFECT_SATURATION),
        .brightness = Converter::ArkValue<Opt_Float64>(EFFECT_BRIGHTNESS),
        .color = Converter::ArkUnion<Opt_ResourceColor, Ark_Int32>(0x123123),
        .adaptiveColor = Converter::ArkValue<Opt_AdaptiveColor>(ARK_ADAPTIVE_COLOR_AVERAGE),
        .blurOptions = Converter::ArkValue<Opt_BlurOptions>(Ark_BlurOptions{
            .grayscale = {Converter::ArkValue<Ark_Float64>(GRAY_SCALE0), Converter::ArkValue<Ark_Float64>(GRAY_SCALE1)}
        }),
        .policy = Converter::ArkValue<Opt_BlurStyleActivePolicy>(ARK_BLUR_STYLE_ACTIVE_POLICY_ALWAYS_INACTIVE),
        .inactiveColor = Converter::ArkUnion<Opt_ResourceColor, Ark_String>(COLOR_GREEN),
    };
    auto inputValue = Converter::ArkValue<Opt_BackgroundEffectOptions>(inputValValid);
    modifier_->setBarBackgroundEffect(node_, &inputValue);
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    ASSERT_NE(jsonValue, nullptr);
    auto effect = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_BAR_BACKGROUND_EFFECT);
    ASSERT_NE(effect, nullptr);
    auto radius = GetAttrValue<double>(effect, ATTRIBUTE_BAR_BACKGROUND_EFFECT_RADIUS);
    ASSERT_NEAR(radius, EFFECT_RADIUS, COMPARING_DELTA);
    auto saturation = GetAttrValue<double>(effect, ATTRIBUTE_BAR_BACKGROUND_EFFECT_SATURATION);
    ASSERT_NEAR(saturation, EFFECT_SATURATION, COMPARING_DELTA);
    auto brightness = GetAttrValue<double>(effect, ATTRIBUTE_BAR_BACKGROUND_EFFECT_BRIGHTNESS);
    ASSERT_NEAR(brightness, EFFECT_BRIGHTNESS, COMPARING_DELTA);
    auto color = GetAttrValue<std::string>(effect, ATTRIBUTE_BAR_BACKGROUND_EFFECT_COLOR);
    EXPECT_EQ(color, EFFECT_COLOR);
    auto adaptiveColor = GetAttrValue<std::string>(effect, ATTRIBUTE_ADAPTIVE_COLOR);
    EXPECT_EQ(adaptiveColor, ADAPTIVE_COLOR_AVERAGE);
    auto policy = GetAttrValue<std::string>(effect, ATTRIBUTE_POLICY);
    EXPECT_EQ(policy, POLICY);
    auto type = GetAttrValue<std::string>(effect, ATTRIBUTE_BAR_BACKGROUND_EFFECT_TYPE);
    EXPECT_EQ(type, DEFAULT_BAR_BACKGROUND_EFFECT_TYPE);
    auto inactiveColor = GetAttrValue<std::string>(effect, ATTRIBUTE_INACTIVE_COLOR);
    EXPECT_EQ(inactiveColor, COLOR_GREEN);
    auto blurOption = GetAttrValue<std::unique_ptr<JsonValue>>(effect, ATTRIBUTE_BLUR_OPTION);
    ASSERT_NE(blurOption, nullptr);
    ASSERT_EQ(blurOption->GetArraySize(), ATTRIBUTE_BLUR_OPTION_COUNT);
    auto gray1 = blurOption->GetArrayItem(ATTRIBUTE_BLUR_OPTION_POS0);
    ASSERT_NE(gray1, nullptr);
    ASSERT_NEAR(gray1->GetDouble(), GRAY_SCALE0, COMPARING_DELTA);
    auto gray2 = blurOption->GetArrayItem(ATTRIBUTE_BLUR_OPTION_POS1);
    ASSERT_NE(gray2, nullptr);
    ASSERT_NEAR(gray2->GetDouble(), GRAY_SCALE1, COMPARING_DELTA);
}

/*
 * @tc.name: DISABLED_setBarBackgroundEffectTestInvalidValues
 * @tc.desc: Check the functionality of GENERATED_ArkUITabsModifier.setBarBackgroundEffect
 * @tc.type: FUNC
 */
HWTEST_F(TabsModifierTest, DISABLED_setBarBackgroundEffectTestInvalidValues, TestSize.Level1)
{
    EXPECT_TRUE(true); // not implemented
}

/*
 * @tc.name: setBarBackgroundBlurStyle1TestDefaultValues
 * @tc.desc: Check the functionality of GENERATED_ArkUITabsModifier.setBarBackgroundBlurStyle1
 * @tc.type: FUNC
 */
HWTEST_F(TabsModifierTest, setBarBackgroundBlurStyle1TestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    ASSERT_NE(jsonValue, nullptr);
    auto option = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_BAR_BACKGROUND_BLUR_STYLE_OPTIONS);
    ASSERT_NE(option, nullptr);
    auto colorMode = GetAttrValue<std::string>(option, ATTRIBUTE_COLOR_MODE);
    EXPECT_EQ(colorMode, DEFAULT_COLOR_MODE);
    auto adaptiveColor = GetAttrValue<std::string>(option, ATTRIBUTE_ADAPTIVE_COLOR);
    EXPECT_EQ(adaptiveColor, DEFAULT_ADAPTIVE_COLOR);
    auto scale = GetAttrValue<double>(option, ATTRIBUTE_SCALE);
    ASSERT_NEAR(scale, DEFAULT_SCALE, COMPARING_DELTA);
    auto blurOption = GetAttrValue<std::unique_ptr<JsonValue>>(option, ATTRIBUTE_BLUR_OPTION);
    ASSERT_NE(blurOption, nullptr);
    ASSERT_EQ(blurOption->GetArraySize(), ATTRIBUTE_BLUR_OPTION_COUNT);
    auto gray1 = blurOption->GetArrayItem(ATTRIBUTE_BLUR_OPTION_POS0);
    ASSERT_NE(gray1, nullptr);
    ASSERT_NEAR(gray1->GetDouble(), DEFAULT_BLUR_OPTION, COMPARING_DELTA);
    auto gray2 = blurOption->GetArrayItem(ATTRIBUTE_BLUR_OPTION_POS1);
    ASSERT_NE(gray2, nullptr);
    ASSERT_NEAR(gray2->GetDouble(), DEFAULT_BLUR_OPTION, COMPARING_DELTA);
    auto policy = GetAttrValue<std::string>(option, ATTRIBUTE_POLICY);
    EXPECT_EQ(policy, DEFAULT_POLICY);
    auto inactiveColor = GetAttrValue<std::string>(option, ATTRIBUTE_INACTIVE_COLOR);
    EXPECT_EQ(inactiveColor, DEFAULT_INACTIVE_COLOR);
}

/*
 * @tc.name: setBarBackgroundBlurStyle1TestValidValues
 * @tc.desc: Check the functionality of GENERATED_ArkUITabsModifier.setBarBackgroundBlurStyle1
 * @tc.type: FUNC
 */
HWTEST_F(TabsModifierTest, setBarBackgroundBlurStyle1TestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setBarBackgroundBlurStyle1, nullptr);

    auto inputStyleValid = Converter::ArkValue<Opt_BlurStyle>(ARK_BLUR_STYLE_BACKGROUND_REGULAR);

    Ark_BackgroundBlurStyleOptions inputOptionValid = {
        .colorMode  = Converter::ArkValue<Opt_ThemeColorMode>(ARK_THEME_COLOR_MODE_DARK),
        .adaptiveColor = Converter::ArkValue<Opt_AdaptiveColor>(ARK_ADAPTIVE_COLOR_AVERAGE),
        .scale = Converter::ArkValue<Opt_Float64>(SCALE),
        .blurOptions = Converter::ArkValue<Opt_BlurOptions>(Ark_BlurOptions{
            .grayscale = {Converter::ArkValue<Ark_Float64>(GRAY_SCALE0), Converter::ArkValue<Ark_Float64>(GRAY_SCALE1)}
        }),
        .policy = Converter::ArkValue<Opt_BlurStyleActivePolicy>(ARK_BLUR_STYLE_ACTIVE_POLICY_ALWAYS_INACTIVE),
        .inactiveColor = Converter::ArkUnion<Opt_ResourceColor, Ark_String>(COLOR_GREEN),
    };

    auto optOptions = Converter::ArkValue<Opt_BackgroundBlurStyleOptions>(inputOptionValid);
    modifier_->setBarBackgroundBlurStyle1(node_, &inputStyleValid, &optOptions);

    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    ASSERT_NE(jsonValue, nullptr);
    auto option = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_BAR_BACKGROUND_BLUR_STYLE_OPTIONS);
    ASSERT_NE(option, nullptr);
    auto colorMode = GetAttrValue<std::string>(option, ATTRIBUTE_COLOR_MODE);
    EXPECT_EQ(colorMode, COLOR_MODE_DARK);
    auto adaptiveColor = GetAttrValue<std::string>(option, ATTRIBUTE_ADAPTIVE_COLOR);
    EXPECT_EQ(adaptiveColor, ADAPTIVE_COLOR_AVERAGE);
    auto scale = GetAttrValue<double>(option, ATTRIBUTE_SCALE);
    ASSERT_NEAR(scale, SCALE, COMPARING_DELTA);
    auto blurOption = GetAttrValue<std::unique_ptr<JsonValue>>(option, ATTRIBUTE_BLUR_OPTION);
    ASSERT_NE(blurOption, nullptr);
    ASSERT_EQ(blurOption->GetArraySize(), ATTRIBUTE_BLUR_OPTION_COUNT);
    auto gray1 = blurOption->GetArrayItem(ATTRIBUTE_BLUR_OPTION_POS0);
    ASSERT_NE(gray1, nullptr);
    ASSERT_NEAR(gray1->GetDouble(), GRAY_SCALE0, COMPARING_DELTA);
    auto gray2 = blurOption->GetArrayItem(ATTRIBUTE_BLUR_OPTION_POS1);
    ASSERT_NE(gray2, nullptr);
    ASSERT_NEAR(gray2->GetDouble(), GRAY_SCALE1, COMPARING_DELTA);
    auto policy = GetAttrValue<std::string>(option, ATTRIBUTE_POLICY);
    EXPECT_EQ(policy, POLICY);
    auto inactiveColor = GetAttrValue<std::string>(option, ATTRIBUTE_INACTIVE_COLOR);
    EXPECT_EQ(inactiveColor, COLOR_GREEN);
}

/*
 * @tc.name: DISABLED_setBarBackgroundBlurStyle1TestInvalidValues
 * @tc.desc: Check the functionality of GENERATED_ArkUITabsModifier.setBarBackgroundBlurStyle1
 * @tc.type: FUNC
 */
HWTEST_F(TabsModifierTest, DISABLED_setBarBackgroundBlurStyle1TestInvalidValues, TestSize.Level1)
{
    EXPECT_TRUE(true); // not implemented
}

/*
 * @tc.name: setBarBackgroundColorTestDefaultValues
 * @tc.desc: Check the functionality of GENERATED_ArkUITabsModifier.setBarBackgroundColor
 * @tc.type: FUNC
 */
HWTEST_F(TabsModifierTest, setBarBackgroundColorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BAR_BACKGROUND_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_BAR_BACKGROUND_COLOR_DEFAULT_VALUE);
}

// Color values for attribute 'barBackgroundColor' of method 'barBackgroundColor'
static std::vector<std::tuple<std::string, Opt_ResourceColor, std::string>> barBackgroundColorValues = {
    {"ARK_COLOR_BLUE", Converter::ArkUnion<Opt_ResourceColor, Ark_Color>(ARK_COLOR_BLUE), COLOR_BLUE},
    {"0x123456", Converter::ArkUnion<Opt_ResourceColor, Ark_Int32>(0x123456), "#FF123456"},
    {"#11223344", Converter::ArkUnion<Opt_ResourceColor, Ark_String>("#11223344"), "#11223344"},
    {"incorrect_color", Converter::ArkUnion<Opt_ResourceColor, Ark_String>("incorrect_color"), COLOR_TRANSPARENT},
    {"65535", Converter::ArkUnion<Opt_ResourceColor, Ark_String>("65535"), "#FF00FFFF"},
    {"empty string", Converter::ArkUnion<Opt_ResourceColor, Ark_String>(""), COLOR_TRANSPARENT},
    {"No res 1", CreateResourceUnion<Opt_ResourceColor>(RES_NAME), COLOR_RED}, // Color::RED is default mocked color
    {"TRANSPARENT res", CreateResourceUnion<Opt_ResourceColor>(RES_STRING_FAKE_ID), COLOR_TRANSPARENT},
    {"No res 2", CreateResourceUnion<Opt_ResourceColor>(RES_ID), COLOR_RED}, // Color::RED is default mocked color
    {"GREEN res", CreateResourceUnion<Opt_ResourceColor>(RES_STRING_REGISTERED_ID), COLOR_GREEN},
};

/*
 * @tc.name: setBarBackgroundColorTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITabsModifier.setBarBackgroundColor
 * @tc.type: FUNC
 */
HWTEST_F(TabsModifierTest, setBarBackgroundColorTest, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;

    for (auto&& value: barBackgroundColorValues) {
        auto inputValueBarBackgroundColor = std::get<1>(value);
        modifier_->setBarBackgroundColor(node_, &inputValueBarBackgroundColor);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BAR_BACKGROUND_COLOR_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setBarGridAlignTestDefaultValues
 * @tc.desc: Check the functionality of GENERATED_ArkUITabsModifier.setBarGridAlign
 * @tc.type: FUNC
 */
HWTEST_F(TabsModifierTest, setBarGridAlignTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultBarGridAlign =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_BAR_GRID_ALIGN_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultBarGridAlign, ATTRIBUTE_BAR_GRID_ALIGN_SM_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_BAR_GRID_ALIGN_SM_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(resultBarGridAlign, ATTRIBUTE_BAR_GRID_ALIGN_MD_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_BAR_GRID_ALIGN_MD_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(resultBarGridAlign, ATTRIBUTE_BAR_GRID_ALIGN_LG_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_BAR_GRID_ALIGN_LG_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(resultBarGridAlign, ATTRIBUTE_BAR_GRID_ALIGN_MARGIN_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_BAR_GRID_ALIGN_MARGIN_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(resultBarGridAlign, ATTRIBUTE_BAR_GRID_ALIGN_GUTTER_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_BAR_GRID_ALIGN_GUTTER_DEFAULT_VALUE);
}

// Valid values for attribute 'sm' of method 'barGridAlign'
static std::vector<std::tuple<std::string, Opt_Int32, std::string>> barGridAlignSmValidValues = {
    {"sm_0", Converter::ArkValue<Opt_Int32>(0), "0"},
    {"sm_2", Converter::ArkValue<Opt_Int32>(2), "2"},
    {"sm_4", Converter::ArkValue<Opt_Int32>(4), "4"}
};

// Valid values for attribute 'md' of method 'barGridAlign'
static std::vector<std::tuple<std::string, Opt_Int32, std::string>> barGridAlignMdValidValues = {
    {"md_0", Converter::ArkValue<Opt_Int32>(0), "0"},
    {"md_2", Converter::ArkValue<Opt_Int32>(2), "2"},
    {"md_4", Converter::ArkValue<Opt_Int32>(4), "4"},
    {"md_6", Converter::ArkValue<Opt_Int32>(6), "6"},
    {"md_8", Converter::ArkValue<Opt_Int32>(8), "8"}
};

// Valid values for attribute 'lg' of method 'barGridAlign'
static std::vector<std::tuple<std::string, Opt_Int32, std::string>> barGridAlignLgValidValues = {
    {"lg_0", Converter::ArkValue<Opt_Int32>(0), "0"},
    {"lg_2", Converter::ArkValue<Opt_Int32>(2), "2"},
    {"lg_4", Converter::ArkValue<Opt_Int32>(4), "4"},
    {"lg_6", Converter::ArkValue<Opt_Int32>(6), "6"},
    {"lg_8", Converter::ArkValue<Opt_Int32>(8), "8"},
    {"lg_10", Converter::ArkValue<Opt_Int32>(10), "10"},
    {"lg_12", Converter::ArkValue<Opt_Int32>(12), "12"}
};

// Valid values for attribute 'margin' of method 'barGridAlign'
static std::vector<std::tuple<std::string, Opt_Dimension, std::string>> barGridAlignMarginValidValues = {
    {"margin_2.45", Converter::ArkValue<Opt_Dimension>(2.45f), "2.45vp"},
    {"margin_5.0px", Converter::ArkValue<Opt_Dimension>("5.0px"), "5.00px"},
    {"margin_22.35px", Converter::ArkValue<Opt_Dimension>("22.35px"), "22.35px"},
    {"margin_7.0vp", Converter::ArkValue<Opt_Dimension>("7.0vp"), "7.00vp"},
    {"margin_1.65vp", Converter::ArkValue<Opt_Dimension>("1.65vp"), "1.65vp"},
    {"margin_65.00fp", Converter::ArkValue<Opt_Dimension>("65.0fp"), "65.00fp"},
    {"margin_4.3fp", Converter::ArkValue<Opt_Dimension>("4.3fp"), "4.30fp"},
    {"mocked res", Converter::ArkValue<Opt_Dimension>(FAKE_RES_ID), "10.00px"}
};

// Valid values for attribute 'gutter' of method 'barGridAlign'
static std::vector<std::tuple<std::string, Opt_Dimension, std::string>> barGridAlignGutterValidValues = {
    {"gutter_2.45", Converter::ArkValue<Opt_Dimension>(2.45f), "2.45vp"},
    {"gutter_5.0px", Converter::ArkValue<Opt_Dimension>("5.0px"), "5.00px"},
    {"gutter_22.35px", Converter::ArkValue<Opt_Dimension>("22.35px"), "22.35px"},
    {"gutter_7.0vp", Converter::ArkValue<Opt_Dimension>("7.0vp"), "7.00vp"},
    {"gutter_1.65vp", Converter::ArkValue<Opt_Dimension>("1.65vp"), "1.65vp"},
    {"gutter_65.00fp", Converter::ArkValue<Opt_Dimension>("65.0fp"), "65.00fp"},
    {"gutter_4.3fp", Converter::ArkValue<Opt_Dimension>("4.3fp"), "4.30fp"},
    {"mocked res", Converter::ArkValue<Opt_Dimension>(FAKE_RES_ID), "10.00px"}
};

/*
 * @tc.name: setBarGridAlignTestValidValues1
 * @tc.desc: Check the functionality of GENERATED_ArkUITabsModifier.setBarGridAlign
 * @tc.type: FUNC
 */
HWTEST_F(TabsModifierTest, setBarGridAlignTestValidValues1, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::unique_ptr<JsonValue> resultBarGridAlign;
    std::string resultStr;
    std::string expectedStr;
    Ark_BarGridColumnOptions inputValueBarGridAlign;
    Ark_BarGridColumnOptions initValueBarGridAlign;

    // Initial setup
    initValueBarGridAlign.sm = std::get<1>(barGridAlignSmValidValues[0]);
    initValueBarGridAlign.md = std::get<1>(barGridAlignMdValidValues[0]);
    initValueBarGridAlign.lg = std::get<1>(barGridAlignLgValidValues[0]);
    initValueBarGridAlign.margin = std::get<1>(barGridAlignMarginValidValues[0]);
    initValueBarGridAlign.gutter = std::get<1>(barGridAlignGutterValidValues[0]);

    // Verifying attribute's 'sm'  values
    inputValueBarGridAlign = initValueBarGridAlign;
    for (auto&& value: barGridAlignSmValidValues) {
        inputValueBarGridAlign.sm = std::get<1>(value);
        auto inputValue = Converter::ArkValue<Opt_BarGridColumnOptions>(inputValueBarGridAlign);
        modifier_->setBarGridAlign(node_, &inputValue);
        jsonValue = GetJsonValue(node_);
        resultBarGridAlign = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_BAR_GRID_ALIGN_NAME);
        resultStr = GetAttrValue<std::string>(resultBarGridAlign, ATTRIBUTE_BAR_GRID_ALIGN_SM_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }

    // Verifying attribute's 'md'  values
    inputValueBarGridAlign = initValueBarGridAlign;
    for (auto&& value: barGridAlignMdValidValues) {
        inputValueBarGridAlign.md = std::get<1>(value);
        auto inputValue = Converter::ArkValue<Opt_BarGridColumnOptions>(inputValueBarGridAlign);
        modifier_->setBarGridAlign(node_, &inputValue);
        jsonValue = GetJsonValue(node_);
        resultBarGridAlign = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_BAR_GRID_ALIGN_NAME);
        resultStr = GetAttrValue<std::string>(resultBarGridAlign, ATTRIBUTE_BAR_GRID_ALIGN_MD_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }

    // Verifying attribute's 'lg'  values
    inputValueBarGridAlign = initValueBarGridAlign;
    for (auto&& value: barGridAlignLgValidValues) {
        inputValueBarGridAlign.lg = std::get<1>(value);
        auto inputValue = Converter::ArkValue<Opt_BarGridColumnOptions>(inputValueBarGridAlign);
        modifier_->setBarGridAlign(node_, &inputValue);
        jsonValue = GetJsonValue(node_);
        resultBarGridAlign = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_BAR_GRID_ALIGN_NAME);
        resultStr = GetAttrValue<std::string>(resultBarGridAlign, ATTRIBUTE_BAR_GRID_ALIGN_LG_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setBarGridAlignTestValidValues2
 * @tc.desc: Check the functionality of GENERATED_ArkUITabsModifier.setBarGridAlign
 * @tc.type: FUNC
 */
HWTEST_F(TabsModifierTest, setBarGridAlignTestValidValues2, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::unique_ptr<JsonValue> resultBarGridAlign;
    std::string resultStr;
    std::string expectedStr;
    Ark_BarGridColumnOptions inputValueBarGridAlign;
    Ark_BarGridColumnOptions initValueBarGridAlign;

    // Initial setup
    initValueBarGridAlign.sm = std::get<1>(barGridAlignSmValidValues[0]);
    initValueBarGridAlign.md = std::get<1>(barGridAlignMdValidValues[0]);
    initValueBarGridAlign.lg = std::get<1>(barGridAlignLgValidValues[0]);
    initValueBarGridAlign.margin = std::get<1>(barGridAlignMarginValidValues[0]);
    initValueBarGridAlign.gutter = std::get<1>(barGridAlignGutterValidValues[0]);

    // Verifying attribute's 'margin'  values
    inputValueBarGridAlign = initValueBarGridAlign;
    for (auto&& value: barGridAlignMarginValidValues) {
        inputValueBarGridAlign.margin = std::get<1>(value);
        auto inputValue = Converter::ArkValue<Opt_BarGridColumnOptions>(inputValueBarGridAlign);
        modifier_->setBarGridAlign(node_, &inputValue);
        jsonValue = GetJsonValue(node_);
        resultBarGridAlign = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_BAR_GRID_ALIGN_NAME);
        resultStr = GetAttrValue<std::string>(resultBarGridAlign, ATTRIBUTE_BAR_GRID_ALIGN_MARGIN_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }

    // Verifying attribute's 'gutter'  values
    inputValueBarGridAlign = initValueBarGridAlign;
    for (auto&& value: barGridAlignGutterValidValues) {
        inputValueBarGridAlign.gutter = std::get<1>(value);
        auto inputValue = Converter::ArkValue<Opt_BarGridColumnOptions>(inputValueBarGridAlign);
        modifier_->setBarGridAlign(node_, &inputValue);
        jsonValue = GetJsonValue(node_);
        resultBarGridAlign = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_BAR_GRID_ALIGN_NAME);
        resultStr = GetAttrValue<std::string>(resultBarGridAlign, ATTRIBUTE_BAR_GRID_ALIGN_GUTTER_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

// Invalid values for attribute 'sm' of method 'barGridAlign'
static std::vector<std::tuple<std::string, Opt_Int32>> barGridAlignSmInvalidValues = {
    {"sm_Ark_Empty", Converter::ArkValue<Opt_Int32>(Ark_Empty())},
    {"sm_Negative", Converter::ArkValue<Opt_Int32>(-1)},
    {"sm_Invalid_14", Converter::ArkValue<Opt_Int32>(14)},
    {"sm_Invalid_3", Converter::ArkValue<Opt_Int32>(3)}
};

// Invalid values for attribute 'md' of method 'barGridAlign'
static std::vector<std::tuple<std::string, Opt_Int32>> barGridAlignMdInvalidValues = {
    {"md_Ark_Empty", Converter::ArkValue<Opt_Int32>(Ark_Empty())},
    {"md_negative", Converter::ArkValue<Opt_Int32>(-1)},
    {"md_invalid_14", Converter::ArkValue<Opt_Int32>(14)},
    {"md_invalid_3", Converter::ArkValue<Opt_Int32>(3)}
};

// Invalid values for attribute 'lg' of method 'barGridAlign'
static std::vector<std::tuple<std::string, Opt_Int32>> barGridAlignLgInvalidValues = {
    {"lg_Ark_Empty", Converter::ArkValue<Opt_Int32>(Ark_Empty())},
    {"lg_negative", Converter::ArkValue<Opt_Int32>(-1)},
    {"lg_invalid_14", Converter::ArkValue<Opt_Int32>(14)},
    {"lg_invalid_3", Converter::ArkValue<Opt_Int32>(3)}
};

// Invalid values for attribute 'margin' of method 'barGridAlign'
static std::vector<std::tuple<std::string, Opt_Dimension>> barGridAlignMarginInvalidValues = {
    {"margin_Ark_Empty", Converter::ArkValue<Opt_Dimension>(Ark_Empty())},
    {"margin_percent", Converter::ArkValue<Opt_Dimension>("12.00%")},
    {"margin_negative", Converter::ArkValue<Opt_Dimension>("-10px")}
};

// Invalid values for attribute 'gutter' of method 'barGridAlign'
static std::vector<std::tuple<std::string, Opt_Dimension>> barGridAlignGutterInvalidValues = {
    {"gutter_Ark_Empty", Converter::ArkValue<Opt_Dimension>(Ark_Empty())},
    {"gutter_percent", Converter::ArkValue<Opt_Dimension>("12.00%")},
    {"gutter_negative", Converter::ArkValue<Opt_Dimension>("-10px")}
};

/*
 * @tc.name: setBarGridAlignTestInvalidValues1
 * @tc.desc: Check the functionality of GENERATED_ArkUITabsModifier.setBarGridAlign
 * @tc.type: FUNC
 */
HWTEST_F(TabsModifierTest, setBarGridAlignTestInvalidValues1, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::unique_ptr<JsonValue> resultBarGridAlign;
    std::string resultStr;
    Ark_BarGridColumnOptions inputValueBarGridAlign;
    Ark_BarGridColumnOptions initValueBarGridAlign;

    // Initial setup
    initValueBarGridAlign.sm = std::get<1>(barGridAlignSmValidValues[0]);
    initValueBarGridAlign.md = std::get<1>(barGridAlignMdValidValues[0]);
    initValueBarGridAlign.lg = std::get<1>(barGridAlignLgValidValues[0]);
    initValueBarGridAlign.margin = std::get<1>(barGridAlignMarginValidValues[0]);
    initValueBarGridAlign.gutter = std::get<1>(barGridAlignGutterValidValues[0]);

    // Verifying attribute's 'sm' values
    for (auto&& value: barGridAlignSmInvalidValues) {
        inputValueBarGridAlign = initValueBarGridAlign;
        auto inputValue = Converter::ArkValue<Opt_BarGridColumnOptions>(inputValueBarGridAlign);
        modifier_->setBarGridAlign(node_, &inputValue);
        inputValueBarGridAlign.sm = std::get<1>(value);
        inputValue = Converter::ArkValue<Opt_BarGridColumnOptions>(inputValueBarGridAlign);
        modifier_->setBarGridAlign(node_, &inputValue);
        jsonValue = GetJsonValue(node_);
        resultBarGridAlign = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_BAR_GRID_ALIGN_NAME);
        resultStr = GetAttrValue<std::string>(resultBarGridAlign, ATTRIBUTE_BAR_GRID_ALIGN_SM_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_BAR_GRID_ALIGN_SM_DEFAULT_VALUE) << "Passed value is: " << std::get<0>(value);
    }

    // Verifying attribute's 'md' values
    for (auto&& value: barGridAlignMdInvalidValues) {
        inputValueBarGridAlign = initValueBarGridAlign;
        auto inputValue = Converter::ArkValue<Opt_BarGridColumnOptions>(inputValueBarGridAlign);
        modifier_->setBarGridAlign(node_, &inputValue);
        inputValueBarGridAlign.md = std::get<1>(value);
        inputValue = Converter::ArkValue<Opt_BarGridColumnOptions>(inputValueBarGridAlign);
        modifier_->setBarGridAlign(node_, &inputValue);
        jsonValue = GetJsonValue(node_);
        resultBarGridAlign = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_BAR_GRID_ALIGN_NAME);
        resultStr = GetAttrValue<std::string>(resultBarGridAlign, ATTRIBUTE_BAR_GRID_ALIGN_MD_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_BAR_GRID_ALIGN_MD_DEFAULT_VALUE) << "Passed value is: " << std::get<0>(value);
    }

    // Verifying attribute's 'lg' values
    for (auto&& value: barGridAlignLgInvalidValues) {
        inputValueBarGridAlign = initValueBarGridAlign;
        auto inputValue = Converter::ArkValue<Opt_BarGridColumnOptions>(inputValueBarGridAlign);
        modifier_->setBarGridAlign(node_, &inputValue);
        inputValueBarGridAlign.lg = std::get<1>(value);
        inputValue = Converter::ArkValue<Opt_BarGridColumnOptions>(inputValueBarGridAlign);
        modifier_->setBarGridAlign(node_, &inputValue);
        jsonValue = GetJsonValue(node_);
        resultBarGridAlign = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_BAR_GRID_ALIGN_NAME);
        resultStr = GetAttrValue<std::string>(resultBarGridAlign, ATTRIBUTE_BAR_GRID_ALIGN_LG_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_BAR_GRID_ALIGN_LG_DEFAULT_VALUE) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setBarGridAlignTestInvalidValues2
 * @tc.desc: Check the functionality of GENERATED_ArkUITabsModifier.setBarGridAlign
 * @tc.type: FUNC
 */
HWTEST_F(TabsModifierTest, setBarGridAlignTestInvalidValues2, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::unique_ptr<JsonValue> resultBarGridAlign;
    std::string resultStr;
    std::string expectedStr;
    Ark_BarGridColumnOptions inputValueBarGridAlign;
    Ark_BarGridColumnOptions initValueBarGridAlign;

    // Initial setup
    initValueBarGridAlign.sm = std::get<1>(barGridAlignSmValidValues[0]);
    initValueBarGridAlign.md = std::get<1>(barGridAlignMdValidValues[0]);
    initValueBarGridAlign.lg = std::get<1>(barGridAlignLgValidValues[0]);
    initValueBarGridAlign.margin = std::get<1>(barGridAlignMarginValidValues[0]);
    initValueBarGridAlign.gutter = std::get<1>(barGridAlignGutterValidValues[0]);

    // Verifying attribute's 'margin' values
    for (auto&& value: barGridAlignMarginInvalidValues) {
        inputValueBarGridAlign = initValueBarGridAlign;
        auto inputValue = Converter::ArkValue<Opt_BarGridColumnOptions>(inputValueBarGridAlign);
        modifier_->setBarGridAlign(node_, &inputValue);
        inputValueBarGridAlign.margin = std::get<1>(value);
        inputValue = Converter::ArkValue<Opt_BarGridColumnOptions>(inputValueBarGridAlign);
        modifier_->setBarGridAlign(node_, &inputValue);
        jsonValue = GetJsonValue(node_);
        resultBarGridAlign = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_BAR_GRID_ALIGN_NAME);
        resultStr = GetAttrValue<std::string>(resultBarGridAlign, ATTRIBUTE_BAR_GRID_ALIGN_MARGIN_NAME);
        expectedStr = ATTRIBUTE_BAR_GRID_ALIGN_MARGIN_DEFAULT_VALUE;
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }

    // Verifying attribute's 'gutter' values
    for (auto&& value: barGridAlignGutterInvalidValues) {
        inputValueBarGridAlign = initValueBarGridAlign;
        auto inputValue = Converter::ArkValue<Opt_BarGridColumnOptions>(inputValueBarGridAlign);
        modifier_->setBarGridAlign(node_, &inputValue);
        inputValueBarGridAlign.gutter = std::get<1>(value);
        inputValue = Converter::ArkValue<Opt_BarGridColumnOptions>(inputValueBarGridAlign);
        modifier_->setBarGridAlign(node_, &inputValue);
        jsonValue = GetJsonValue(node_);
        resultBarGridAlign = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_BAR_GRID_ALIGN_NAME);
        resultStr = GetAttrValue<std::string>(resultBarGridAlign, ATTRIBUTE_BAR_GRID_ALIGN_GUTTER_NAME);
        expectedStr = ATTRIBUTE_BAR_GRID_ALIGN_GUTTER_DEFAULT_VALUE;
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

#ifdef WRONG_OLD_CALLBACK
/*
 * @tc.name: setOnChangeEventIndexImpl
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TabsModifierTest, setOnChangeEventIndexImpl, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto tabsNode = AceType::DynamicCast<TabsNode>(frameNode);
    CHECK_NULL_VOID(tabsNode);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_VOID(swiperNode);
    auto eventHub = swiperNode->GetEventHub<SwiperEventHub>();
    ASSERT_NE(eventHub, nullptr);

    struct CheckEvent {
        int32_t nodeId;
        int32_t value;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;

    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_Number parameter) {
        checkEvent = {
            .nodeId = resourceId,
            .value = Converter::Convert<int32_t>(parameter)
        };
    };

    Callback_Number_Void arkCallback = Converter::ArkValue<Callback_Number_Void>(checkCallback, contextId);

    modifier_->set_onChangeEvent_index(node_, &arkCallback);

    ASSERT_EQ(checkEvent.has_value(), false);
    eventHub->FireChangeEvent(0, 1, false);
    ASSERT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, contextId);
    EXPECT_EQ(checkEvent->value, 1);
    eventHub->FireChangeEvent(1, 2, false);
    ASSERT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, contextId);
    EXPECT_EQ(checkEvent->value, 2);
}
#endif

/**
 * @tc.name: setPageFlipModeTestDefaultValue
 * @tc.desc: Check the functionality of SwiperInterfaceModifier.PageFlipModeImpl
 * @tc.type: FUNC
 */
HWTEST_F(TabsModifierTest, setPageFlipModeTestDefaultValue, TestSize.Level1)
{
    ASSERT_NE(modifier_->setPageFlipMode, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(frameNode);
    ASSERT_NE(tabsNode, nullptr);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    ASSERT_NE(swiperNode, nullptr);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    EXPECT_EQ(swiperPattern->GetPageFlipMode(), ATTRIBUTE_PAGE_FLIP_MODE_DEFAULT_VALUE);
}

/**
 * @tc.name: setPageFlipModeTestValidValue
 * @tc.desc: Check the functionality of SwiperInterfaceModifier.PageFlipModeImpl
 * @tc.type: FUNC
 */
HWTEST_F(TabsModifierTest, setPageFlipModeTestValidValue, TestSize.Level1)
{
    ASSERT_NE(modifier_->setPageFlipMode, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(frameNode);
    ASSERT_NE(tabsNode, nullptr);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    ASSERT_NE(swiperNode, nullptr);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    using OneTestStep = std::tuple<Opt_PageFlipMode, int32_t>;
    static const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Opt_PageFlipMode>(PageFlipMode::CONTINUOUS), ATTRIBUTE_PAGE_FLIP_MODE_DEFAULT_VALUE},
        {Converter::ArkValue<Opt_PageFlipMode>(PageFlipMode::SINGLE), static_cast<int32_t>(PageFlipMode::SINGLE)},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setPageFlipMode(node_, &inputValue);
        EXPECT_EQ(swiperPattern->GetPageFlipMode(), expectedValue) << "Passed value is: " << expectedValue;
    }
}

/**
 * @tc.name: setPageFlipModeTestInvalidValue
 * @tc.desc: Check the functionality of SwiperInterfaceModifier.PageFlipModeImpl
 * @tc.type: FUNC
 */
HWTEST_F(TabsModifierTest, setPageFlipModeTestInvalidValue, TestSize.Level1)
{
    ASSERT_NE(modifier_->setPageFlipMode, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(frameNode);
    ASSERT_NE(tabsNode, nullptr);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    ASSERT_NE(swiperNode, nullptr);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    using OneTestStep = std::tuple<Opt_PageFlipMode, int32_t>;
    static const std::vector<OneTestStep> testPlan = {
        {Opt_PageFlipMode{.tag = Ark_Tag::INTEROP_TAG_UNDEFINED}, ATTRIBUTE_PAGE_FLIP_MODE_DEFAULT_VALUE},
        {Converter::ArkValue<Opt_PageFlipMode>(static_cast<PageFlipMode>(-1)), ATTRIBUTE_PAGE_FLIP_MODE_DEFAULT_VALUE},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setPageFlipMode(node_, &inputValue);
        EXPECT_EQ(swiperPattern->GetPageFlipMode(), expectedValue) << "Passed value is: " << expectedValue;
    }
}

/**
 * @tc.name: setOnSelectedTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITabsModifier.setOnSelected
 * @tc.type: FUNC
 */
HWTEST_F(TabsModifierTest, setOnSelectedTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto onSelected =
        [](Ark_Int32 nodeId, const Ark_Int32 index) {
            g_indexValue = Converter::Convert<int32_t>(index);
        };
    auto func = Converter::ArkCallback<Opt_Callback_I32_Void>(onSelected);
    modifier_->setOnSelected(node_, &func);
    EXPECT_EQ(g_indexValue, 0);

    auto tabsNode = AceType::DynamicCast<TabsNode>(frameNode);
    ASSERT_NE(tabsNode, nullptr);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    ASSERT_NE(swiperNode, nullptr);
    auto eventHub = swiperNode->GetEventHub<SwiperEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->FireSelectedEvent(INDEX);
    EXPECT_EQ(g_indexValue, INDEX);
    g_indexValue = 0;
}

/**
 * @tc.name: setOnUnselectedTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITabsModifier.setOnUnselected
 * @tc.type: FUNC
 */
HWTEST_F(TabsModifierTest, setOnUnselectedTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto onUnselected =
        [](Ark_Int32 nodeId, const Ark_Int32 index) {
            g_indexValue = Converter::Convert<int32_t>(index);
        };
    auto func = Converter::ArkCallback<Opt_Callback_I32_Void>(onUnselected);
    modifier_->setOnUnselected(node_, &func);
    EXPECT_EQ(g_indexValue, 0);

    auto tabsNode = AceType::DynamicCast<TabsNode>(frameNode);
    ASSERT_NE(tabsNode, nullptr);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    ASSERT_NE(swiperNode, nullptr);
    auto eventHub = swiperNode->GetEventHub<SwiperEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->FireUnselectedEvent(INDEX);
    EXPECT_EQ(g_indexValue, INDEX);
    g_indexValue = 0;
}

/**
 * @tc.name: setCachedMaxCountValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TabsModifierTest, setCachedMaxCountValues, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    // default value
    auto json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    EXPECT_EQ("", GetAttrValue<std::string>(json, "cachedMaxCount"));

    // new values
    std::vector<std::tuple<std::string, Ark_TabsCacheMode, int32_t>> testMap = {
        {"TabsCacheMode.CACHE_BOTH_SIDE", ARK_TABS_CACHE_MODE_CACHE_BOTH_SIDE, 1},
        {"TabsCacheMode.CACHE_LATEST_SWITCHED", ARK_TABS_CACHE_MODE_CACHE_LATEST_SWITCHED, 2},
    };

    for (auto [expectedModeValue, modeValue, countValue]: testMap) {
        auto arkCount = Converter::ArkValue<Opt_Int32>(countValue);
        auto arkMode = Converter::ArkValue<Opt_TabsCacheMode>(modeValue);
        modifier_->setCachedMaxCount(frameNode, &arkCount, &arkMode);
        auto json = GetJsonValue(node_);
        ASSERT_TRUE(json);
        auto cachedMaxCount = GetAttrValue<std::unique_ptr<JsonValue>>(json, "cachedMaxCount");
        ASSERT_TRUE(cachedMaxCount);
        EXPECT_EQ(expectedModeValue, GetAttrValue<std::string>(cachedMaxCount, "mode"));
        EXPECT_EQ(countValue, GetAttrValue<int32_t>(cachedMaxCount, "count"));
    }

    auto arkMode = Converter::ArkValue<Opt_TabsCacheMode>(ARK_TABS_CACHE_MODE_CACHE_BOTH_SIDE);
    modifier_->setCachedMaxCount(frameNode, nullptr, &arkMode);
    json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    EXPECT_EQ("", GetAttrValue<std::string>(json, "cachedMaxCount"));
}
}
