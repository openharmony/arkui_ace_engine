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
#include "node_api.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components/tab_bar/tab_theme.h"
#include "core/components_ng/pattern/stage/page_event_hub.h"
#include "core/components_ng/pattern/tabs/tabs_model_ng.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {

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
} // namespace


class TabsModifierTest : public ModifierTestBase<GENERATED_ArkUITabsModifier,
                                 &GENERATED_ArkUINodeModifiers::getTabsModifier, GENERATED_ARKUI_TABS> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        SetupTheme<TabTheme>();
    }
};

/**
 * @tc.name: setVerticalTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITabsModifier.setVertical
 * @tc.type: FUNC
 */
HWTEST_F(TabsModifierTest, setVerticalTest, TestSize.Level1)
{
    const std::string PROP_NAME("vertical");
    ASSERT_NE(modifier_->setVertical, nullptr);
    auto checkVal = GetAttrValue<std::string>(GetJsonValue(node_), PROP_NAME);
    EXPECT_EQ(checkVal, "false");

    for (const auto& [value, expectVal] : BOOL_STR_TEST_PLAN) {
        modifier_->setVertical(node_, value);
        checkVal = GetAttrValue<std::string>(GetJsonValue(node_), PROP_NAME);
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
    const std::string PROP_NAME("fadingEdge");
    ASSERT_NE(modifier_->setFadingEdge, nullptr);
    auto checkVal = GetAttrValue<std::string>(GetJsonValue(node_), PROP_NAME);
    EXPECT_EQ(checkVal, "true");

    for (const auto& [value, expectVal] : BOOL_STR_TEST_PLAN) {
        modifier_->setFadingEdge(node_, value);
        checkVal = GetAttrValue<std::string>(GetJsonValue(node_), PROP_NAME);
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
    const std::string PROP_NAME("scrollable");
    ASSERT_NE(modifier_->setScrollable, nullptr);
    auto checkVal = GetAttrValue<bool>(GetJsonValue(node_), PROP_NAME);
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
        checkVal = GetAttrValue<bool>(json, PROP_NAME);
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
    const std::string PROP_NAME("barOverlap");
    ASSERT_NE(modifier_->setBarOverlap, nullptr);
    auto checkVal = GetAttrValue<std::string>(GetJsonValue(node_), PROP_NAME);
    EXPECT_EQ(checkVal, "false");

    for (const auto& [value, expectVal] : BOOL_STR_TEST_PLAN) {
        modifier_->setBarOverlap(node_, value);
        checkVal = GetAttrValue<std::string>(GetJsonValue(node_), PROP_NAME);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setAnimationDurationTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITabsModifier.setAnimationDuration
 * @tc.type: FUNC
 */
HWTEST_F(TabsModifierTest, DISABLED_setAnimationDurationTest, TestSize.Level1)
{
    const std::string PROP_NAME("animationDuration");
    ASSERT_NE(modifier_->setAnimationDuration, nullptr);
    auto checkVal = GetAttrValue<int>(GetJsonValue(node_), PROP_NAME);
    const int defaultDuration = 0;
    EXPECT_EQ(checkVal, defaultDuration);

    typedef std::pair<Ark_Number, int> ArkNumberTestStep;
    const std::vector<ArkNumberTestStep> arkNumberTestPlan = {
        { Converter::ArkValue<Ark_Number>(20), 20 },
        { Converter::ArkValue<Ark_Number>(0), 0 },
        { Converter::ArkValue<Ark_Number>(22.5f), 22 },
        // now next step is failed, because Tabs component used incorrect default value 200
        { Converter::ArkValue<Ark_Number>(-20), defaultDuration },
        { Converter::ArkValue<Ark_Number>(0.0f), 0 },
        // now next step is failed, because Tabs component used incorrect default value 200
        { Converter::ArkValue<Ark_Number>(-22.5f), defaultDuration },
        { Converter::ArkValue<Ark_Number>(20), 20 }};

    for (const auto& [value, expectVal] : arkNumberTestPlan) {
        modifier_->setAnimationDuration(node_, &value);
        checkVal = GetAttrValue<int>(GetJsonValue(node_), PROP_NAME);
        EXPECT_EQ(checkVal, expectVal);
    }

    //value should not be changed
    modifier_->setAnimationDuration(node_, nullptr);
    checkVal = GetAttrValue<int>(GetJsonValue(node_), PROP_NAME);
    EXPECT_EQ(checkVal, arkNumberTestPlan[arkNumberTestPlan.size()-1].second);
}

/**
 * @tc.name: setAnimationModeTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITabsModifier.setAnimationMode
 * @tc.type: FUNC
 */
HWTEST_F(TabsModifierTest, setAnimationModeTest, TestSize.Level1)
{
    const std::string PROP_NAME("animationMode");
    ASSERT_NE(modifier_->setAnimationMode, nullptr);
    auto checkVal = GetAttrValue<std::string>(GetJsonValue(node_), PROP_NAME);
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
        checkVal = GetAttrValue<std::string>(GetJsonValue(node_), PROP_NAME);
        EXPECT_EQ(checkVal, expectVal);
    }

    //value should not be changed
    modifier_->setAnimationMode(node_, nullptr);
    checkVal = GetAttrValue<std::string>(GetJsonValue(node_), PROP_NAME);
    EXPECT_EQ(checkVal, animationModeTestPlan[animationModeTestPlan.size()-1].second);
}

/**
 * @tc.name: setEdgeEffectTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITabsModifier.setEdgeEffect
 * @tc.type: FUNC
 */
HWTEST_F(TabsModifierTest, setEdgeEffectTest, TestSize.Level1)
{
    const std::string PROP_NAME("edgeEffect");
    ASSERT_NE(modifier_->setEdgeEffect, nullptr);
    auto checkVal = GetAttrValue<std::string>(GetJsonValue(node_), PROP_NAME);
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
        checkVal = GetAttrValue<std::string>(GetJsonValue(node_), PROP_NAME);
        EXPECT_EQ(checkVal, expectVal);
    }

    //value should not be changed
    modifier_->setEdgeEffect(node_, nullptr);
    checkVal = GetAttrValue<std::string>(GetJsonValue(node_), PROP_NAME);
    EXPECT_EQ(checkVal, edgeEffectTestPlan[edgeEffectTestPlan.size()-1].second);
}

/**
 * @tc.name: setBarPositionTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITabsModifier.setBarPosition
 * @tc.type: FUNC
 */
HWTEST_F(TabsModifierTest, setBarPositionTest, TestSize.Level1)
{
    const std::string PROP_NAME("barPosition");
    ASSERT_NE(modifier_->setBarPosition, nullptr);
    auto checkVal = GetAttrValue<std::string>(GetJsonValue(node_), PROP_NAME);
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
        checkVal = GetAttrValue<std::string>(GetJsonValue(node_), PROP_NAME);
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
    const std::string PROP_NAME("barMode");
    ASSERT_NE(modifier_->setBarMode0, nullptr);
    auto checkVal = GetAttrValue<std::string>(GetJsonValue(node_), PROP_NAME);
    EXPECT_EQ(checkVal, "BarMode.Fixed");

    std::string scrollableMode =
        "BarMode.Scrollable,{\"margin\":\"0.00vp\",\"nonScrollableLayoutStyle\":\"LayoutStyle.ALWAYS_CENTER\"}";
    typedef std::pair<Ark_BarMode, std::string> BarMode0TestStep;
    const std::vector<BarMode0TestStep> BarMode0TestPlan = {
        { ARK_BAR_MODE_SCROLLABLE, scrollableMode },
        { ARK_BAR_MODE_FIXED, "BarMode.Fixed" },
        { ARK_BAR_MODE_SCROLLABLE, scrollableMode },
        { static_cast<Ark_BarMode>(25), "BarMode.Fixed" }
    };

    for (const auto& [value, expectVal] : BarMode0TestPlan) {
        modifier_->setBarMode0(node_, value);
        checkVal = GetAttrValue<std::string>(GetJsonValue(node_), PROP_NAME);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setBarBackgroundBlurStyleTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITabsModifier.setBarBackgroundBlurStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabsModifierTest, setBarBackgroundBlurStyleTest, TestSize.Level1)
{
    const std::string PROP_NAME("barBackgroundBlurStyle");
    ASSERT_NE(modifier_->setBarBackgroundBlurStyle, nullptr);
    auto checkVal = GetAttrValue<std::string>(GetJsonValue(node_), PROP_NAME);
    EXPECT_EQ(checkVal, "BlurStyle.NONE");

    typedef std::pair<Ark_BlurStyle, std::string> BlurStyleTestStep;
    const std::vector<BlurStyleTestStep> BarMode0TestPlan = {
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

    for (const auto& [value, expectVal] : BarMode0TestPlan) {
        modifier_->setBarBackgroundBlurStyle(node_, value);
        checkVal = GetAttrValue<std::string>(GetJsonValue(node_), PROP_NAME);
        EXPECT_EQ(checkVal, expectVal);
    }
}

}