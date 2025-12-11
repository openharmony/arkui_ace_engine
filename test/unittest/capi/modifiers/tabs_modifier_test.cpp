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
    dst.timeout.value = Converter::ArkValue<Ark_Number>(src.timeout);
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
constexpr double ANIMATION_DURATION_DEFAULT = 300.0;
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

Ark_ScrollableBarModeOptions CreateScrollableMode(Opt_Length margin, Ark_LayoutStyle layoutStyle)
{
    Opt_LayoutStyle nonScrollableLayoutStyle = Converter::ArkValue<Opt_LayoutStyle>(layoutStyle);
    Ark_ScrollableBarModeOptions options = {
        .margin = margin,
        .nonScrollableLayoutStyle = nonScrollableLayoutStyle
    };
    return options;
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
const Ark_Length RES_ARK_LENGTH = Converter::ArkValue<Ark_Length>(FAKE_RES_ID);
typedef std::pair<Ark_ScrollableBarModeOptions, std::string> ScrollableBarModeTestStep;
const std::vector<ScrollableBarModeTestStep> SCROLLABLE_BAR_MODE_TEST_PLAN = {
    { CreateScrollableMode(Converter::ArkValue<Opt_Length>("70.px"), ARK_LAYOUT_STYLE_ALWAYS_AVERAGE_SPLIT),
        "BarMode.Scrollable,"
        "{\"margin\":\"70.00px\","
        "\"nonScrollableLayoutStyle\":\"LayoutStyle.ALWAYS_AVERAGE_SPLIT\"}" },
    { CreateScrollableMode(Converter::ArkValue<Opt_Length>(32.7), ARK_LAYOUT_STYLE_SPACE_BETWEEN_OR_CENTER),
        "BarMode.Scrollable,"
        "{\"margin\":\"32.70vp\","
        "\"nonScrollableLayoutStyle\":\"LayoutStyle.SPACE_BETWEEN_OR_CENTER\"}" },
    { CreateScrollableMode(Converter::ArkValue<Opt_Length>("10.00%"), static_cast<Ark_LayoutStyle>(25)),
        "BarMode.Scrollable,"
        "{\"margin\":\"0.00vp\","
        "\"nonScrollableLayoutStyle\":\"LayoutStyle.ALWAYS_CENTER\"}" },
    { CreateScrollableMode(Converter::ArkValue<Opt_Length>(-32.7), ARK_LAYOUT_STYLE_ALWAYS_CENTER),
        "BarMode.Scrollable,"
        "{\"margin\":\"-32.70vp\","
        "\"nonScrollableLayoutStyle\":\"LayoutStyle.ALWAYS_CENTER\"}" },
    { CreateScrollableMode(Converter::ArkValue<Opt_Length>(RES_ARK_LENGTH),
        ARK_LAYOUT_STYLE_ALWAYS_AVERAGE_SPLIT),
        "BarMode.Scrollable,"
        "{\"margin\":\"10.00px\","
        "\"nonScrollableLayoutStyle\":\"LayoutStyle.ALWAYS_AVERAGE_SPLIT\"}"}
};

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
    constexpr auto propName = "vertical";
    ASSERT_NE(modifier_->setVertical, nullptr);
    auto checkVal = GetAttrValue<std::string>(GetJsonValue(node_), propName);
    EXPECT_EQ(checkVal, "false");

    for (const auto& [value, expectVal] : BOOL_STR_TEST_PLAN) {
        modifier_->setVertical(node_, value);
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
    constexpr auto propName = "fadingEdge";
    ASSERT_NE(modifier_->setFadingEdge, nullptr);
    auto checkVal = GetAttrValue<std::string>(GetJsonValue(node_), propName);
    EXPECT_EQ(checkVal, "true");

    for (const auto& [value, expectVal] : BOOL_STR_TEST_PLAN) {
        modifier_->setFadingEdge(node_, value);
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
    constexpr auto propName = "scrollable";
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
        modifier_->setScrollable(node_, value);
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
    constexpr auto propName = "barOverlap";
    ASSERT_NE(modifier_->setBarOverlap, nullptr);
    auto checkVal = GetAttrValue<std::string>(GetJsonValue(node_), propName);
    EXPECT_EQ(checkVal, "false");

    for (const auto& [value, expectVal] : BOOL_STR_TEST_PLAN) {
        modifier_->setBarOverlap(node_, value);
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
    constexpr auto propName = "animationDuration";
    ASSERT_NE(modifier_->setAnimationDuration, nullptr);
    auto checkVal = GetAttrValue<int>(GetJsonValue(node_), propName);
    EXPECT_EQ(checkVal, static_cast<int>(ANIMATION_DURATION_DEFAULT));

    typedef std::pair<Ark_Number, int> ArkNumberTestStep;
    const std::vector<ArkNumberTestStep> arkNumberTestPlan = {
        { Converter::ArkValue<Ark_Number>(20), 20 },
        { Converter::ArkValue<Ark_Number>(0), 0 },
        { Converter::ArkValue<Ark_Number>(22.5f), 22 },
        // now next step is failed, because Tabs component used incorrect default value 200
        { Converter::ArkValue<Ark_Number>(-20), static_cast<int>(ANIMATION_DURATION_DEFAULT) },
        { Converter::ArkValue<Ark_Number>(0.0f), 0 },
        // now next step is failed, because Tabs component used incorrect default value 200
        { Converter::ArkValue<Ark_Number>(-22.5f), static_cast<int>(ANIMATION_DURATION_DEFAULT) },
        { Converter::ArkValue<Ark_Number>(20), 20 }};

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
    constexpr auto propName = "animationMode";
    ASSERT_NE(modifier_->setAnimationMode, nullptr);
    auto checkVal = GetAttrValue<std::string>(GetJsonValue(node_), propName);
    EXPECT_EQ(checkVal, "AnimationMode.CONTENT_FIRST");

    typedef std::pair<Opt_AnimationMode, std::string> AnimationModeTestStep;
    const std::vector<AnimationModeTestStep> animationModeTestPlan = {
        { Converter::ArkValue<Opt_AnimationMode>(ARK_ANIMATION_MODE_ACTION_FIRST), "AnimationMode.ACTION_FIRST" },
        { Converter::ArkValue<Opt_AnimationMode>(ARK_ANIMATION_MODE_CONTENT_FIRST), "AnimationMode.CONTENT_FIRST" },
        { Converter::ArkValue<Opt_AnimationMode>(ARK_ANIMATION_MODE_NO_ANIMATION), "AnimationMode.NO_ANIMATION" },
        { Converter::ArkValue<Opt_AnimationMode>(static_cast<Ark_AnimationMode>(25)), "AnimationMode.CONTENT_FIRST" },
        { Converter::ArkValue<Opt_AnimationMode>(ARK_ANIMATION_MODE_NO_ANIMATION), "AnimationMode.NO_ANIMATION" },
    };

    for (const auto& [value, expectVal] : animationModeTestPlan) {
        modifier_->setAnimationMode(node_, &value);
        checkVal = GetAttrValue<std::string>(GetJsonValue(node_), propName);
        EXPECT_EQ(checkVal, expectVal);
    }

    //value should not be changed
    modifier_->setAnimationMode(node_, nullptr);
    checkVal = GetAttrValue<std::string>(GetJsonValue(node_), propName);
    EXPECT_EQ(checkVal, animationModeTestPlan[animationModeTestPlan.size()-1].second);
}

/**
 * @tc.name: setEdgeEffectTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITabsModifier.setEdgeEffect
 * @tc.type: FUNC
 */
HWTEST_F(TabsModifierTest, setEdgeEffectTest, TestSize.Level1)
{
    constexpr auto propName = "edgeEffect";
    ASSERT_NE(modifier_->setEdgeEffect, nullptr);
    auto checkVal = GetAttrValue<std::string>(GetJsonValue(node_), propName);
    EXPECT_EQ(checkVal, "EdgeEffect::SPRING");
    typedef std::pair<Opt_EdgeEffect, std::string> EdgeEffectTestStep;
    const std::vector<EdgeEffectTestStep> edgeEffectTestPlan = {
        { Converter::ArkValue<Opt_EdgeEffect>(ARK_EDGE_EFFECT_FADE), "EdgeEffect::FADE" },
        { Converter::ArkValue<Opt_EdgeEffect>(ARK_EDGE_EFFECT_SPRING), "EdgeEffect::SPRING" },
        { Converter::ArkValue<Opt_EdgeEffect>(ARK_EDGE_EFFECT_NONE), "EdgeEffect::NONE" },
        { Converter::ArkValue<Opt_EdgeEffect>(static_cast<Ark_EdgeEffect>(25)),  "EdgeEffect::SPRING" },
        { Converter::ArkValue<Opt_EdgeEffect>(ARK_EDGE_EFFECT_NONE), "EdgeEffect::NONE" }
    };

    for (const auto& [value, expectVal] : edgeEffectTestPlan) {
        modifier_->setEdgeEffect(node_, &value);
        checkVal = GetAttrValue<std::string>(GetJsonValue(node_), propName);
        EXPECT_EQ(checkVal, expectVal);
    }

    //value should not be changed
    modifier_->setEdgeEffect(node_, nullptr);
    checkVal = GetAttrValue<std::string>(GetJsonValue(node_), propName);
    EXPECT_EQ(checkVal, edgeEffectTestPlan[edgeEffectTestPlan.size()-1].second);
}

/**
 * @tc.name: setBarPositionTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITabsModifier.setBarPosition
 * @tc.type: FUNC
 */
HWTEST_F(TabsModifierTest, setBarPositionTest, TestSize.Level1)
{
    constexpr auto propName = "barPosition";
    ASSERT_NE(modifier_->setBarPosition, nullptr);
    auto checkVal = GetAttrValue<std::string>(GetJsonValue(node_), propName);
    EXPECT_EQ(checkVal, "BarPosition.Start");

    typedef std::pair<Ark_BarPosition, std::string> BarPositionTestStep;
    const std::vector<BarPositionTestStep> BarPositionTestPlan = {
        { ARK_BAR_POSITION_END, "BarPosition.End" },
        { ARK_BAR_POSITION_START, "BarPosition.Start" },
        { ARK_BAR_POSITION_END, "BarPosition.End" },
        { static_cast<Ark_BarPosition>(25), "BarPosition.Start" }
    };

    for (const auto& [value, expectVal] : BarPositionTestPlan) {
        modifier_->setBarPosition(node_, value);
        checkVal = GetAttrValue<std::string>(GetJsonValue(node_), propName);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setBarMode0Test
 * @tc.desc: Check the functionality of GENERATED_ArkUITabsModifier.setBarMode0
 * @tc.type: FUNC
 */
HWTEST_F(TabsModifierTest, setBarMode0Test, TestSize.Level1)
{
    constexpr auto propName = "barMode";
    ASSERT_NE(modifier_->setBarMode0, nullptr);
    ASSERT_NE(modifier_->setBarMode1, nullptr);
    auto checkVal = GetAttrValue<std::string>(GetJsonValue(node_), propName);
    EXPECT_EQ(checkVal, "BarMode.Fixed");

    typedef std::pair<Ark_BarMode, std::string> BarMode0TestStep;
    const std::vector<BarMode0TestStep> BarMode0TestPlan = {
        { ARK_BAR_MODE_SCROLLABLE, "BarMode.Fixed" },
        { ARK_BAR_MODE_FIXED, "BarMode.Fixed" },
        { static_cast<Ark_BarMode>(25), "BarMode.Fixed" }
    };
    std::string scrollableMode =
        "BarMode.Scrollable,{\"margin\":\"0.00vp\",\"nonScrollableLayoutStyle\":\"LayoutStyle.ALWAYS_CENTER\"}";

    for (const auto& [value, expectVal] : BarMode0TestPlan) {
        modifier_->setBarMode1(node_, ARK_BAR_MODE_SCROLLABLE, nullptr);
        checkVal = GetAttrValue<std::string>(GetJsonValue(node_), propName);
        EXPECT_EQ(checkVal, scrollableMode);

        modifier_->setBarMode0(node_, value);
        checkVal = GetAttrValue<std::string>(GetJsonValue(node_), propName);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setBarMode1Test
 * @tc.desc: Check the functionality of GENERATED_ArkUITabsModifier.setBarMode1
 * @tc.type: FUNC
 */
HWTEST_F(TabsModifierTest, setBarMode1Test, TestSize.Level1)
{
    constexpr auto propName = "barMode";
    ASSERT_NE(modifier_->setBarMode0, nullptr);
    ASSERT_NE(modifier_->setBarMode1, nullptr);
    auto checkVal = GetAttrValue<std::string>(GetJsonValue(node_), propName);
    EXPECT_EQ(checkVal, "BarMode.Fixed");

    std::string scrollableMode =
        "BarMode.Scrollable,{\"margin\":\"0.00vp\",\"nonScrollableLayoutStyle\":\"LayoutStyle.ALWAYS_CENTER\"}";
    typedef std::pair<Ark_BarMode, std::string> BarMode0TestStep;
    const std::vector<BarMode0TestStep> BarMode1TestPlan = {
        { ARK_BAR_MODE_SCROLLABLE, scrollableMode },
        { ARK_BAR_MODE_FIXED, "BarMode.Fixed" },
        { static_cast<Ark_BarMode>(25), "BarMode.Fixed" }
    };

    for (const auto& [value, expectVal] : BarMode1TestPlan) {
        modifier_->setBarMode1(node_, value, nullptr);
        checkVal = GetAttrValue<std::string>(GetJsonValue(node_), propName);
        EXPECT_EQ(checkVal, expectVal);

        modifier_->setBarMode0(node_, ARK_BAR_MODE_FIXED);
        checkVal = GetAttrValue<std::string>(GetJsonValue(node_), propName);
        EXPECT_EQ(checkVal, "BarMode.Fixed");
    }

    Opt_Length margin = Converter::ArkValue<Opt_Length>("70px");
    Opt_LayoutStyle nonScrollableLayoutStyle =
    Converter::ArkValue<Opt_LayoutStyle>(ARK_LAYOUT_STYLE_ALWAYS_AVERAGE_SPLIT);
    Ark_ScrollableBarModeOptions options = {.margin = margin, .nonScrollableLayoutStyle = nonScrollableLayoutStyle};
    std::string scrollableMode2 = "BarMode.Scrollable,"
        "{\"margin\":\"70.00px\","
        "\"nonScrollableLayoutStyle\":\"LayoutStyle.ALWAYS_AVERAGE_SPLIT\"}";
    auto optOptions = Converter::ArkValue<Opt_ScrollableBarModeOptions>(options);
    modifier_->setBarMode1(node_, ARK_BAR_MODE_SCROLLABLE, &optOptions);
    checkVal = GetAttrValue<std::string>(GetJsonValue(node_), propName);
    EXPECT_EQ(checkVal, scrollableMode2);
}

/**
 * @tc.name: setBarMode2Test
 * @tc.desc: Check the functionality of GENERATED_ArkUITabsModifier.setBarMode2
 * @tc.type: FUNC
 */
HWTEST_F(TabsModifierTest, setBarMode2Test, TestSize.Level1)
{
    constexpr auto propName = "barMode";
    ASSERT_NE(modifier_->setBarModeScrollable, nullptr);
    auto checkVal = GetAttrValue<std::string>(GetJsonValue(node_), propName);
    EXPECT_EQ(checkVal, "BarMode.Fixed");

    for (const auto& [value, expectVal] : SCROLLABLE_BAR_MODE_TEST_PLAN) {
        modifier_->setBarModeScrollable(node_, &value);
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
    constexpr auto propName = "barBackgroundBlurStyle";
    ASSERT_NE(modifier_->setBarBackgroundBlurStyle0, nullptr);
    auto checkVal = GetAttrValue<std::string>(GetJsonValue(node_), propName);
    EXPECT_EQ(checkVal, "BlurStyle.NONE");

    typedef std::pair<Ark_BlurStyle, std::string> BlurStyleTestStep;
    const std::vector<BlurStyleTestStep> BlurStyleTestPlan = {
        { ARK_BLUR_STYLE_THIN, "BlurStyle.Thin" },
        { ARK_BLUR_STYLE_REGULAR, "BlurStyle.Regular" },
        { ARK_BLUR_STYLE_THICK, "BlurStyle.Thick" },
        { ARK_BLUR_STYLE_BACKGROUND_THIN, "BlurStyle.BACKGROUND_THIN" },
        { ARK_BLUR_STYLE_BACKGROUND_REGULAR, "BlurStyle.BACKGROUND_REGULAR" },
        { ARK_BLUR_STYLE_BACKGROUND_THICK, "BlurStyle.BACKGROUND_THICK" },
        { ARK_BLUR_STYLE_BACKGROUND_ULTRA_THICK, "BlurStyle.BACKGROUND_ULTRA_THICK" },
        { ARK_BLUR_STYLE_NONE, "BlurStyle.NONE" },
        { ARK_BLUR_STYLE_COMPONENT_ULTRA_THIN, "BlurStyle.COMPONENT_ULTRA_THIN" },
        { ARK_BLUR_STYLE_COMPONENT_THIN, "BlurStyle.COMPONENT_THIN" },
        { ARK_BLUR_STYLE_COMPONENT_REGULAR, "BlurStyle.COMPONENT_REGULAR" },
        { ARK_BLUR_STYLE_COMPONENT_THICK, "BlurStyle.COMPONENT_THICK" },
        { ARK_BLUR_STYLE_COMPONENT_ULTRA_THICK, "BlurStyle.COMPONENT_ULTRA_THICK" },
        { static_cast<Ark_BlurStyle>(25), "BlurStyle.NONE" }
    };

    for (const auto& [value, expectVal] : BlurStyleTestPlan) {
        modifier_->setBarBackgroundBlurStyle0(node_, value);
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
        [](Ark_Int32 nodeId, const Ark_Number index) {
            g_indexValue = Converter::Convert<int32_t>(index);
        };
    auto func = Converter::ArkValue<Callback_Number_Void>(onChange, CONTEXT_ID);
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
        [](Ark_Int32 nodeId, const Ark_Number index, const Ark_Number targetIndex,
            const Ark_TabsAnimationEvent event) {
            g_indexValue = Converter::Convert<int32_t>(index);
            g_targetIndexValue = Converter::Convert<int32_t>(targetIndex);
            g_currentOffsetValue = Converter::Convert<float>(event.currentOffset);
            g_targetOffsetValue = Converter::Convert<float>(event.targetOffset);
            g_velocityValue = Converter::Convert<float>(event.velocity);
        };
    auto func = Converter::ArkValue<OnTabsAnimationStartCallback>(onAnimationStart, CONTEXT_ID);
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
        [](Ark_Int32 nodeId, const Ark_Number index, const Ark_TabsAnimationEvent event) {
            g_indexValue = Converter::Convert<int32_t>(index);
            g_currentOffsetValue = Converter::Convert<float>(event.currentOffset);
            g_targetOffsetValue = Converter::Convert<float>(event.targetOffset);
            g_velocityValue = Converter::Convert<float>(event.velocity);
        };
    auto func = Converter::ArkValue<OnTabsAnimationEndCallback>(onAnimationEnd, CONTEXT_ID);
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
        [](Ark_Int32 nodeId, const Ark_Number index, const Ark_TabsAnimationEvent event) {
            g_indexValue = Converter::Convert<int32_t>(index);
            g_currentOffsetValue = Converter::Convert<float>(event.currentOffset);
            g_targetOffsetValue = Converter::Convert<float>(event.targetOffset);
            g_velocityValue = Converter::Convert<float>(event.velocity);
        };
    auto func = Converter::ArkValue<OnTabsGestureSwipeCallback>(onGestureSwipe, CONTEXT_ID);
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
    auto onTransition = [](Ark_VMContext context, const Ark_Int32 resourceId,
        const Ark_Number from, const Ark_Number to,
        const Callback_Opt_TabContentAnimatedTransition_Void cbReturn) {
        EXPECT_EQ(resourceId, expectedResId);
        EXPECT_EQ(Converter::Convert<int32_t>(to), TO);
        TabContentAnimatedTransition result;
        CallbackHelper(cbReturn).InvokeSync(Converter::ArkValue<Opt_TabContentAnimatedTransition>(result));
    };
    auto arkFunc = Converter::ArkValue<TabsCustomContentTransitionCallback>(
        nullptr, onTransition, expectedResId);
    modifier_->setCustomContentTransition(node_, &arkFunc);
    swiperPattern->OnCustomContentTransition(TO);
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
        const Ark_Number currentIndex, const Ark_Number comingIndex, const Callback_Boolean_Void cbReturn) {
        EXPECT_EQ(resourceId, expectedResId);
        EXPECT_EQ(Converter::Convert<int32_t>(currentIndex), CURRENT_INDEX);
        EXPECT_EQ(Converter::Convert<int32_t>(comingIndex), COMING_INDEX);
        bool result = Converter::Convert<int32_t>(comingIndex) > 0;
        CallbackHelper(cbReturn).InvokeSync(Converter::ArkValue<Ark_Boolean>(result));
    };
    auto arkFunc = Converter::ArkValue<OnTabsContentWillChangeCallback>(
        nullptr, onContentWillChange, expectedResId);
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
        [](Ark_Int32 nodeId, const Ark_Number index) {
            g_indexValue = Converter::Convert<int32_t>(index);
        };
    auto func = Converter::ArkValue<Callback_Number_Void>(onTabBarClick, CONTEXT_ID);
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
static std::vector<std::tuple<std::string, Ark_Length, std::string>> barSizeValidValues = {
    {"2.45", Converter::ArkValue<Ark_Length>(2.45), "2.45vp"},
    {"5.0px", Converter::ArkValue<Ark_Length>("5.0px"), "5.00px"},
    {"22.35px", Converter::ArkValue<Ark_Length>("22.35px"), "22.35px"},
    {"7.0vp", Converter::ArkValue<Ark_Length>("7.0vp"), "7.00vp"},
    {"1.65vp", Converter::ArkValue<Ark_Length>("1.65vp"), "1.65vp"},
    {"65.00fp", Converter::ArkValue<Ark_Length>("65.0fp"), "65.00fp"},
    {"4.3fp", Converter::ArkValue<Ark_Length>("4.3fp"), "4.30fp"},
    {"12%", Converter::ArkValue<Ark_Length>("12.00%"), "12.00%"},
    {"RES_ARK_LENGTH", RES_ARK_LENGTH, "10.00px"}
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
    Ark_Length inputValueBarWidth;

    // Verifying attribute's  values
    for (auto&& value: barSizeValidValues) {
        inputValueBarWidth = std::get<1>(value);
        modifier_->setBarWidth(node_, &inputValueBarWidth);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BAR_WIDTH_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

// Invalid values for attribute 'barWidth' of method 'barWidth'
static std::vector<std::tuple<std::string, Ark_Length>> barSizeInvalidValues = {
    {"-2.45", Converter::ArkValue<Ark_Length>(-2.45)},
    {"-5.0px", Converter::ArkValue<Ark_Length>("-5.0px")},
    {"-22.35px", Converter::ArkValue<Ark_Length>("-22.35px")},
    {"-7.0vp", Converter::ArkValue<Ark_Length>("-7.0vp")},
    {"-1.65vp", Converter::ArkValue<Ark_Length>("-1.65vp")},
    {"-65.00fp", Converter::ArkValue<Ark_Length>("-65.0fp")},
    {"-4.3fp", Converter::ArkValue<Ark_Length>("-4.3fp")},
    {"-12%", Converter::ArkValue<Ark_Length>("-12.00%")}
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
    Ark_Length inputValueBarWidth;
    Ark_Length initValueBarWidth;

    // Initial setup
    initValueBarWidth = std::get<1>(barSizeValidValues[0]);

    // Verifying attribute's  values
    for (auto&& value: barSizeInvalidValues) {
        inputValueBarWidth = initValueBarWidth;
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
    Ark_Length inputValueBarHeight;

    // Verifying attribute's  values
    for (auto&& value: barSizeValidValues) {
        inputValueBarHeight = std::get<1>(value);
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
    Ark_Length inputValueBarHeight;
    Ark_Length initValueBarHeight;

    // Initial setup
    initValueBarHeight = std::get<1>(barSizeValidValues[0]);

    // Verifying attribute's  values
    for (auto&& value: barSizeInvalidValues) {
        inputValueBarHeight = initValueBarHeight;
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
        .strokeWidth = Converter::ArkValue<Ark_Length>("11px"),
        .startMargin = Converter::ArkValue<Opt_Length>(Converter::ArkValue<Ark_Length>(55.5)),
        .endMargin = Converter::ArkValue<Opt_Length>(Converter::ArkValue<Ark_Length>("77px")),
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
    dividerOptions = {
        .strokeWidth = Converter::ArkValue<Ark_Length>("11px"),
        .startMargin = Converter::ArkValue<Opt_Length>(Converter::ArkValue<Ark_Length>(55.5)),
        .endMargin = Converter::ArkValue<Opt_Length>(Converter::ArkValue<Ark_Length>("77px")),
        .color = Converter::ArkUnion<Opt_ResourceColor, Ark_Int32>(0x123456),
    };
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
        .strokeWidth = Converter::ArkValue<Ark_Length>("11px"),
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
        .strokeWidth = Converter::ArkValue<Ark_Length>("11px"),
        .startMargin = Converter::ArkValue<Opt_Length>(Converter::ArkValue<Ark_Length>(55.5)),
        .endMargin = Converter::ArkValue<Opt_Length>(Converter::ArkValue<Ark_Length>("77px")),
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
        .radius = Converter::ArkValue<Ark_Number>(EFFECT_RADIUS),
        .saturation = Converter::ArkValue<Opt_Number>(EFFECT_SATURATION),
        .brightness = Converter::ArkValue<Opt_Number>(EFFECT_BRIGHTNESS),
        .color = Converter::ArkUnion<Opt_ResourceColor, Ark_Int32>(0x123123),
        .adaptiveColor = Converter::ArkValue<Opt_AdaptiveColor>(ARK_ADAPTIVE_COLOR_AVERAGE),
        .blurOptions = Converter::ArkValue<Opt_BlurOptions>(Ark_BlurOptions{
            .grayscale = {Converter::ArkValue<Ark_Number>(GRAY_SCALE0), Converter::ArkValue<Ark_Number>(GRAY_SCALE1)}
        }),
        .policy = Converter::ArkValue<Opt_BlurStyleActivePolicy>(ARK_BLUR_STYLE_ACTIVE_POLICY_ALWAYS_INACTIVE),
        .inactiveColor = Converter::ArkUnion<Opt_ResourceColor, Ark_String>(COLOR_GREEN),
    };
    modifier_->setBarBackgroundEffect(node_, &inputValValid);
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
    FAIL() << "Test is not implemented yet";
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

    Ark_BlurStyle inputStyleValid = ARK_BLUR_STYLE_BACKGROUND_REGULAR;

    Ark_BackgroundBlurStyleOptions inputOptionValid = {
        .colorMode  = Converter::ArkValue<Opt_ThemeColorMode>(ARK_THEME_COLOR_MODE_DARK),
        .adaptiveColor = Converter::ArkValue<Opt_AdaptiveColor>(ARK_ADAPTIVE_COLOR_AVERAGE),
        .scale = Converter::ArkValue<Opt_Number>(SCALE),
        .blurOptions = Converter::ArkValue<Opt_BlurOptions>(Ark_BlurOptions{
            .grayscale = {Converter::ArkValue<Ark_Number>(GRAY_SCALE0), Converter::ArkValue<Ark_Number>(GRAY_SCALE1)}
        }),
        .policy = Converter::ArkValue<Opt_BlurStyleActivePolicy>(ARK_BLUR_STYLE_ACTIVE_POLICY_ALWAYS_INACTIVE),
        .inactiveColor = Converter::ArkUnion<Opt_ResourceColor, Ark_String>(COLOR_GREEN),
    };

    modifier_->setBarBackgroundBlurStyle1(node_, inputStyleValid, &inputOptionValid);

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
    FAIL() << "Test is not implemented yet";
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
static std::vector<std::tuple<std::string, Ark_ResourceColor, std::string>> barBackgroundColorValues = {
    {"ARK_COLOR_BLUE", Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_BLUE), COLOR_BLUE},
    {"0x123456", Converter::ArkUnion<Ark_ResourceColor, Ark_Int32>(0x123456), "#FF123456"},
    {"0.5f", Converter::ArkUnion<Ark_ResourceColor, Ark_Int32>(0.5f), COLOR_TRANSPARENT},
    {"#11223344", Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#11223344"), "#11223344"},
    {"65535", Converter::ArkUnion<Ark_ResourceColor, Ark_String>("65535"), "#FF00FFFF"},
    {"incorrect_color", Converter::ArkUnion<Ark_ResourceColor, Ark_String>("incorrect_color"), COLOR_TRANSPARENT},
    {"empty string", Converter::ArkUnion<Ark_ResourceColor, Ark_String>(""), COLOR_TRANSPARENT}
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
    Ark_ResourceColor inputValueBarBackgroundColor;

    for (auto&& value: barBackgroundColorValues) {
        inputValueBarBackgroundColor = std::get<1>(value);
        modifier_->setBarBackgroundColor(node_, &inputValueBarBackgroundColor);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BAR_BACKGROUND_COLOR_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

static std::vector<std::tuple<std::string, Ark_ResourceColor, std::string>> barBackgroundColorResourceValues = {
    {"RED1", Converter::ArkUnion<Ark_ResourceColor, struct Ark_Resource>(CreateResource(RES_NAME)),
        COLOR_RED}, // Color::RED is result of mocked ThemeConstants::GetColorByName
    {"TRANSPARENT", Converter::ArkUnion<Ark_ResourceColor, struct Ark_Resource>(CreateResource(RES_STRING_FAKE_ID)),
        COLOR_TRANSPARENT},
    {"RED2", Converter::ArkUnion<Ark_ResourceColor, struct Ark_Resource>(CreateResource(RES_ID)),
        COLOR_RED}, // Color::RED is result of mocked ThemeConstants::GetColor(int)
    {"GREEN", Converter::ArkUnion<Ark_ResourceColor, struct Ark_Resource>(CreateResource(RES_STRING_REGISTERED_ID)),
        COLOR_GREEN}
};

/*
 * @tc.name: setBarBackgroundColorTestResourceValues
 * @tc.desc: Check the functionality of GENERATED_ArkUITabsModifier.setBarBackgroundColor
 * @tc.type: FUNC
 */
HWTEST_F(TabsModifierTest, setBarBackgroundColorTestResourceValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_ResourceColor inputValueBarBackgroundColor;

    for (auto&& value: barBackgroundColorResourceValues) {
        inputValueBarBackgroundColor = std::get<1>(value);
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
static std::vector<std::tuple<std::string, Opt_Number, std::string>> barGridAlignSmValidValues = {
    {"sm_0", Converter::ArkValue<Opt_Number>(0), "0"},
    {"sm_2", Converter::ArkValue<Opt_Number>(2), "2"},
    {"sm_4", Converter::ArkValue<Opt_Number>(4), "4"}
};

// Valid values for attribute 'md' of method 'barGridAlign'
static std::vector<std::tuple<std::string, Opt_Number, std::string>> barGridAlignMdValidValues = {
    {"md_0", Converter::ArkValue<Opt_Number>(0), "0"},
    {"md_2", Converter::ArkValue<Opt_Number>(2), "2"},
    {"md_4", Converter::ArkValue<Opt_Number>(4), "4"},
    {"md_6", Converter::ArkValue<Opt_Number>(6), "6"},
    {"md_8", Converter::ArkValue<Opt_Number>(8), "8"}
};

// Valid values for attribute 'lg' of method 'barGridAlign'
static std::vector<std::tuple<std::string, Opt_Number, std::string>> barGridAlignLgValidValues = {
    {"lg_0", Converter::ArkValue<Opt_Number>(0), "0"},
    {"lg_2", Converter::ArkValue<Opt_Number>(2), "2"},
    {"lg_4", Converter::ArkValue<Opt_Number>(4), "4"},
    {"lg_6", Converter::ArkValue<Opt_Number>(6), "6"},
    {"lg_8", Converter::ArkValue<Opt_Number>(8), "8"},
    {"lg_10", Converter::ArkValue<Opt_Number>(10), "10"},
    {"lg_12", Converter::ArkValue<Opt_Number>(12), "12"}
};

// Valid values for attribute 'margin' of method 'barGridAlign'
static std::vector<std::tuple<std::string, Opt_Length, std::string>> barGridAlignMarginValidValues = {
    {"2.45", Converter::ArkValue<Opt_Length>(2.45), "2.45vp"},
    {"5.0px", Converter::ArkValue<Opt_Length>("5.0px"), "5.00px"},
    {"22.35px", Converter::ArkValue<Opt_Length>("22.35px"), "22.35px"},
    {"7.0vp", Converter::ArkValue<Opt_Length>("7.0vp"), "7.00vp"},
    {"1.65vp", Converter::ArkValue<Opt_Length>("1.65vp"), "1.65vp"},
    {"65.00fp", Converter::ArkValue<Opt_Length>("65.0fp"), "65.00fp"},
    {"4.3fp", Converter::ArkValue<Opt_Length>("4.3fp"), "4.30fp"},
    {"RES_ARK_LENGTH", Converter::ArkValue<Opt_Length>(RES_ARK_LENGTH), "10.00px"}
};

// Valid values for attribute 'gutter' of method 'barGridAlign'
static std::vector<std::tuple<std::string, Opt_Length, std::string>> barGridAlignGutterValidValues = {
    {"2.45", Converter::ArkValue<Opt_Length>(2.45), "2.45vp"},
    {"5.0px", Converter::ArkValue<Opt_Length>("5.0px"), "5.00px"},
    {"22.35px", Converter::ArkValue<Opt_Length>("22.35px"), "22.35px"},
    {"7.0vp", Converter::ArkValue<Opt_Length>("7.0vp"), "7.00vp"},
    {"1.65vp", Converter::ArkValue<Opt_Length>("1.65vp"), "1.65vp"},
    {"65.00fp", Converter::ArkValue<Opt_Length>("65.0fp"), "65.00fp"},
    {"4.3fp", Converter::ArkValue<Opt_Length>("4.3fp"), "4.30fp"},
    {"RES_ARK_LENGTH", Converter::ArkValue<Opt_Length>(RES_ARK_LENGTH), "10.00px"}
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
        modifier_->setBarGridAlign(node_, &inputValueBarGridAlign);
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
        modifier_->setBarGridAlign(node_, &inputValueBarGridAlign);
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
        modifier_->setBarGridAlign(node_, &inputValueBarGridAlign);
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
        modifier_->setBarGridAlign(node_, &inputValueBarGridAlign);
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
        modifier_->setBarGridAlign(node_, &inputValueBarGridAlign);
        jsonValue = GetJsonValue(node_);
        resultBarGridAlign = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_BAR_GRID_ALIGN_NAME);
        resultStr = GetAttrValue<std::string>(resultBarGridAlign, ATTRIBUTE_BAR_GRID_ALIGN_GUTTER_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

// Invalid values for attribute 'sm' of method 'barGridAlign'
static std::vector<std::tuple<std::string, Opt_Number>> barGridAlignSmInvalidValues = {
    {"sm_Ark_Empty", Converter::ArkValue<Opt_Number>(Ark_Empty())},
    {"sm_Negative", Converter::ArkValue<Opt_Number>(-1)},
    {"sm_Invalid_14", Converter::ArkValue<Opt_Number>(14)},
    {"sm_Invalid_3", Converter::ArkValue<Opt_Number>(3)}
};

// Invalid values for attribute 'md' of method 'barGridAlign'
static std::vector<std::tuple<std::string, Opt_Number>> barGridAlignMdInvalidValues = {
    {"md_Ark_Empty", Converter::ArkValue<Opt_Number>(Ark_Empty())},
    {"md_negative", Converter::ArkValue<Opt_Number>(-1)},
    {"md_invalid_14", Converter::ArkValue<Opt_Number>(14)},
    {"md_invalid_3", Converter::ArkValue<Opt_Number>(3)}
};

// Invalid values for attribute 'lg' of method 'barGridAlign'
static std::vector<std::tuple<std::string, Opt_Number>> barGridAlignLgInvalidValues = {
    {"lg_Ark_Empty", Converter::ArkValue<Opt_Number>(Ark_Empty())},
    {"lg_negative", Converter::ArkValue<Opt_Number>(-1)},
    {"lg_invalid_14", Converter::ArkValue<Opt_Number>(14)},
    {"lg_invalid_3", Converter::ArkValue<Opt_Number>(3)}
};

// Invalid values for attribute 'margin' of method 'barGridAlign'
static std::vector<std::tuple<std::string, Opt_Length>> barGridAlignMarginInvalidValues = {
    {"margin_Ark_Empty", Converter::ArkValue<Opt_Length>(Ark_Empty())},
    {"margin_percent", Converter::ArkValue<Opt_Length>("12.00%")},
    {"margin_negative", Converter::ArkValue<Opt_Length>("-10px")}
};

// Invalid values for attribute 'gutter' of method 'barGridAlign'
static std::vector<std::tuple<std::string, Opt_Length>> barGridAlignGutterInvalidValues = {
    {"gutter_Ark_Empty", Converter::ArkValue<Opt_Length>(Ark_Empty())},
    {"gutter_percent", Converter::ArkValue<Opt_Length>("12.00%")},
    {"gutter_negative", Converter::ArkValue<Opt_Length>("-10px")}
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
    std::string expectedStr;
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
        modifier_->setBarGridAlign(node_, &inputValueBarGridAlign);
        inputValueBarGridAlign.sm = std::get<1>(value);
        modifier_->setBarGridAlign(node_, &inputValueBarGridAlign);
        jsonValue = GetJsonValue(node_);
        resultBarGridAlign = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_BAR_GRID_ALIGN_NAME);
        resultStr = GetAttrValue<std::string>(resultBarGridAlign, ATTRIBUTE_BAR_GRID_ALIGN_SM_NAME);
        expectedStr = ATTRIBUTE_BAR_GRID_ALIGN_SM_DEFAULT_VALUE;
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }

    // Verifying attribute's 'md' values
    for (auto&& value: barGridAlignMdInvalidValues) {
        inputValueBarGridAlign = initValueBarGridAlign;
        modifier_->setBarGridAlign(node_, &inputValueBarGridAlign);
        inputValueBarGridAlign.md = std::get<1>(value);
        modifier_->setBarGridAlign(node_, &inputValueBarGridAlign);
        jsonValue = GetJsonValue(node_);
        resultBarGridAlign = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_BAR_GRID_ALIGN_NAME);
        resultStr = GetAttrValue<std::string>(resultBarGridAlign, ATTRIBUTE_BAR_GRID_ALIGN_MD_NAME);
        expectedStr = ATTRIBUTE_BAR_GRID_ALIGN_MD_DEFAULT_VALUE;
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }

    // Verifying attribute's 'lg' values
    for (auto&& value: barGridAlignLgInvalidValues) {
        inputValueBarGridAlign = initValueBarGridAlign;
        modifier_->setBarGridAlign(node_, &inputValueBarGridAlign);
        inputValueBarGridAlign.lg = std::get<1>(value);
        modifier_->setBarGridAlign(node_, &inputValueBarGridAlign);
        jsonValue = GetJsonValue(node_);
        resultBarGridAlign = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_BAR_GRID_ALIGN_NAME);
        resultStr = GetAttrValue<std::string>(resultBarGridAlign, ATTRIBUTE_BAR_GRID_ALIGN_LG_NAME);
        expectedStr = ATTRIBUTE_BAR_GRID_ALIGN_LG_DEFAULT_VALUE;
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
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
        modifier_->setBarGridAlign(node_, &inputValueBarGridAlign);
        inputValueBarGridAlign.margin = std::get<1>(value);
        modifier_->setBarGridAlign(node_, &inputValueBarGridAlign);
        jsonValue = GetJsonValue(node_);
        resultBarGridAlign = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_BAR_GRID_ALIGN_NAME);
        resultStr = GetAttrValue<std::string>(resultBarGridAlign, ATTRIBUTE_BAR_GRID_ALIGN_MARGIN_NAME);
        expectedStr = ATTRIBUTE_BAR_GRID_ALIGN_MARGIN_DEFAULT_VALUE;
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }

    // Verifying attribute's 'gutter' values
    for (auto&& value: barGridAlignGutterInvalidValues) {
        inputValueBarGridAlign = initValueBarGridAlign;
        modifier_->setBarGridAlign(node_, &inputValueBarGridAlign);
        inputValueBarGridAlign.gutter = std::get<1>(value);
        modifier_->setBarGridAlign(node_, &inputValueBarGridAlign);
        jsonValue = GetJsonValue(node_);
        resultBarGridAlign = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_BAR_GRID_ALIGN_NAME);
        resultStr = GetAttrValue<std::string>(resultBarGridAlign, ATTRIBUTE_BAR_GRID_ALIGN_GUTTER_NAME);
        expectedStr = ATTRIBUTE_BAR_GRID_ALIGN_GUTTER_DEFAULT_VALUE;
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

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
    const std::vector<OneTestStep> testPlan = {
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
    const std::vector<OneTestStep> testPlan = {
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
        [](Ark_Int32 nodeId, const Ark_Number index) {
            g_indexValue = Converter::Convert<int32_t>(index);
        };
    auto func = Converter::ArkValue<Callback_Number_Void>(onSelected, CONTEXT_ID);
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
        [](Ark_Int32 nodeId, const Ark_Number index) {
            g_indexValue = Converter::Convert<int32_t>(index);
        };
    auto func = Converter::ArkValue<Callback_Number_Void>(onUnselected, CONTEXT_ID);
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
        auto arkCount = Converter::ArkValue<Ark_Number>(countValue);
        modifier_->setCachedMaxCount(frameNode, &arkCount, modeValue);
        auto json = GetJsonValue(node_);
        ASSERT_TRUE(json);
        auto cachedMaxCount = GetAttrValue<std::unique_ptr<JsonValue>>(json, "cachedMaxCount");
        ASSERT_TRUE(cachedMaxCount);
        EXPECT_EQ(expectedModeValue, GetAttrValue<std::string>(cachedMaxCount, "mode"));
        EXPECT_EQ(countValue, GetAttrValue<int32_t>(cachedMaxCount, "count"));
    }

    modifier_->setCachedMaxCount(frameNode, nullptr, ARK_TABS_CACHE_MODE_CACHE_BOTH_SIDE);
    json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    EXPECT_EQ("", GetAttrValue<std::string>(json, "cachedMaxCount"));
}
}
