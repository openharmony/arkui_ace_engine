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
#include "core/components_ng/pattern/tabs/tabs_model_ng.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"
#include "core/components_ng/pattern/swiper/swiper_event_hub.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/pattern/tabs/tabs_pattern.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
Opt_ScrollableBarModeOptions CreateScrollableMode(Opt_Length margin, Ark_LayoutStyle layoutStyle)
{
    Opt_LayoutStyle nonScrollableLayoutStyle = Converter::ArkValue<Opt_LayoutStyle>(layoutStyle);
    Ark_ScrollableBarModeOptions options = {
        .margin = margin,
        .nonScrollableLayoutStyle = nonScrollableLayoutStyle
    };
    auto optionsOpt = Converter::ArkValue<Opt_ScrollableBarModeOptions>(options);
    return optionsOpt;
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
const Ark_Int32 FAKE_RES_ID(1234);
const Ark_Length MARGIN_RES = { .type = ARK_TAG_RESOURCE, .resource = FAKE_RES_ID };
typedef std::pair<Opt_ScrollableBarModeOptions, std::string> ScrollableBarModeTestStep;
const std::vector<ScrollableBarModeTestStep> SCROLLABLE_BAR_MODE_TEST_PLAN = {
    { CreateScrollableMode(Converter::ArkValue<Opt_Length>(70), ARK_LAYOUT_STYLE_ALWAYS_AVERAGE_SPLIT),
        "BarMode.Scrollable,"
        "{\"margin\":\"70.00px\","
        "\"nonScrollableLayoutStyle\":\"LayoutStyle.ALWAYS_AVERAGE_SPLIT\"}" },
    { CreateScrollableMode(Converter::ArkValue<Opt_Length>(32.7f), ARK_LAYOUT_STYLE_SPACE_BETWEEN_OR_CENTER),
        "BarMode.Scrollable,"
        "{\"margin\":\"32.70vp\","
        "\"nonScrollableLayoutStyle\":\"LayoutStyle.SPACE_BETWEEN_OR_CENTER\"}" },
    { CreateScrollableMode(Converter::ArkValue<Opt_Length>(10.0_pct), static_cast<Ark_LayoutStyle>(25)),
        "BarMode.Scrollable,"
        "{\"margin\":\"0.00vp\","
        "\"nonScrollableLayoutStyle\":\"LayoutStyle.ALWAYS_CENTER\"}" },
    { CreateScrollableMode(Converter::ArkValue<Opt_Length>(-32.7f), ARK_LAYOUT_STYLE_ALWAYS_CENTER),
        "BarMode.Scrollable,"
        "{\"margin\":\"-32.70vp\","
        "\"nonScrollableLayoutStyle\":\"LayoutStyle.ALWAYS_CENTER\"}" },
    { CreateScrollableMode(Converter::ArkValue<Opt_Length>(std::optional<Ark_Length>(MARGIN_RES)),
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
int32_t g_fromValue(0);
int32_t g_toValue(0);
int32_t g_currentIndexValue(0);
int32_t g_comingIndexValue(0);

const int32_t INDEX(10);
const int32_t TARGET_INDEX(12);
const float CURRENT_OFFSET(0.2f);
const float TARGET_OFFSET(0.4f);
const float VELOCITY(0.6f);
const int32_t TO(16);
const int32_t CURRENT_INDEX(18);
const int32_t COMING_INDEX(20);

GENERATED_ArkUITabsEventsReceiver recv {
    .onChange =
        [](Ark_Int32 nodeId, const Ark_Number index) {
            g_indexValue = Converter::Convert<int32_t>(index);
        },
    .onTabBarClick =
        [](Ark_Int32 nodeId, const Ark_Number index) {
            g_indexValue = Converter::Convert<int32_t>(index);
        },
    .onAnimationStart =
        [](Ark_Int32 nodeId, const Ark_Number index, const Ark_Number targetIndex,
            const Ark_TabsAnimationEvent event) {
            g_indexValue = Converter::Convert<int32_t>(index);
            g_targetIndexValue = Converter::Convert<int32_t>(targetIndex);
            g_currentOffsetValue = Converter::Convert<float>(event.currentOffset);
            g_targetOffsetValue = Converter::Convert<float>(event.targetOffset);
            g_velocityValue = Converter::Convert<float>(event.velocity);
        },
    .onAnimationEnd =
        [](Ark_Int32 nodeId, const Ark_Number index, const Ark_TabsAnimationEvent event) {
            g_indexValue = Converter::Convert<int32_t>(index);
            g_currentOffsetValue = Converter::Convert<float>(event.currentOffset);
            g_targetOffsetValue = Converter::Convert<float>(event.targetOffset);
            g_velocityValue = Converter::Convert<float>(event.velocity);
        },
    .onGestureSwipe =
        [](Ark_Int32 nodeId, const Ark_Number index, const Ark_TabsAnimationEvent event) {
            g_indexValue = Converter::Convert<int32_t>(index);
            g_currentOffsetValue = Converter::Convert<float>(event.currentOffset);
            g_targetOffsetValue = Converter::Convert<float>(event.targetOffset);
            g_velocityValue = Converter::Convert<float>(event.velocity);
        },
    .customContentTransition =
        [](Ark_Int32 nodeId, const Ark_Number from, const Ark_Number to) {
            g_toValue = Converter::Convert<int32_t>(to);
            g_fromValue = Converter::Convert<int32_t>(from);
        },
    .onContentWillChange =
        [](Ark_Int32 nodeId, const Ark_Number currentIndex, const Ark_Number comingIndex) {
            g_currentIndexValue = Converter::Convert<int32_t>(currentIndex);
            g_comingIndexValue = Converter::Convert<int32_t>(comingIndex);
        }
};

const GENERATED_ArkUITabsEventsReceiver* getTabsEventsReceiverTest()
{
    return &recv;
};

static const GENERATED_ArkUIEventsAPI* GetArkUiEventsAPITest()
{
    static const GENERATED_ArkUIEventsAPI eventsImpl = { .getTabsEventsReceiver = getTabsEventsReceiverTest };
    return &eventsImpl;
};

} // namespace


class TabsModifierTest : public ModifierTestBase<GENERATED_ArkUITabsModifier,
                                 &GENERATED_ArkUINodeModifiers::getTabsModifier, GENERATED_ARKUI_TABS> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();
        SetupTheme<TabTheme>();
        fullAPI_->setArkUIEventsAPI(GetArkUiEventsAPITest());
        EXPECT_CALL(*MockPipelineContext::GetCurrent(), FlushUITasks(_)).Times(AnyNumber());
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
    ASSERT_NE(modifier_->setBarMode1, nullptr);
    auto checkVal = GetAttrValue<std::string>(GetJsonValue(node_), PROP_NAME);
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
        checkVal = GetAttrValue<std::string>(GetJsonValue(node_), PROP_NAME);
        EXPECT_EQ(checkVal, scrollableMode);

        modifier_->setBarMode0(node_, value);
        checkVal = GetAttrValue<std::string>(GetJsonValue(node_), PROP_NAME);
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
    const std::string PROP_NAME("barMode");
    ASSERT_NE(modifier_->setBarMode0, nullptr);
    ASSERT_NE(modifier_->setBarMode1, nullptr);
    auto checkVal = GetAttrValue<std::string>(GetJsonValue(node_), PROP_NAME);
    EXPECT_EQ(checkVal, "BarMode.Fixed");

    std::string scrollableMode =
        "BarMode.Scrollable,{\"margin\":\"0.00vp\",\"nonScrollableLayoutStyle\":\"LayoutStyle.ALWAYS_CENTER\"}";
    typedef std::pair<Ark_BarMode, std::string> BarMode0TestStep;
    const std::vector<BarMode0TestStep> BarMode1TestPlan = {
        { ARK_BAR_MODE_SCROLLABLE, scrollableMode },
        { ARK_BAR_MODE_FIXED, scrollableMode },
        { static_cast<Ark_BarMode>(25), scrollableMode }
    };

    for (const auto& [value, expectVal] : BarMode1TestPlan) {
        modifier_->setBarMode1(node_, value, nullptr);
        checkVal = GetAttrValue<std::string>(GetJsonValue(node_), PROP_NAME);
        EXPECT_EQ(checkVal, expectVal);
    
        modifier_->setBarMode0(node_, ARK_BAR_MODE_FIXED);
        checkVal = GetAttrValue<std::string>(GetJsonValue(node_), PROP_NAME);
        EXPECT_EQ(checkVal, "BarMode.Fixed");
    }

    Opt_Length margin = Converter::ArkValue<Opt_Length>(70);
    Opt_LayoutStyle nonScrollableLayoutStyle =
    Converter::ArkValue<Opt_LayoutStyle>(ARK_LAYOUT_STYLE_ALWAYS_AVERAGE_SPLIT);
    Ark_ScrollableBarModeOptions options = {.margin = margin, .nonScrollableLayoutStyle = nonScrollableLayoutStyle};
    std::string scrollableMode2 = "BarMode.Scrollable,"
        "{\"margin\":\"70.00px\","
        "\"nonScrollableLayoutStyle\":\"LayoutStyle.ALWAYS_AVERAGE_SPLIT\"}";
    modifier_->setBarMode1(node_, ARK_BAR_MODE_SCROLLABLE, &options);
    checkVal = GetAttrValue<std::string>(GetJsonValue(node_), PROP_NAME);
    EXPECT_EQ(checkVal, scrollableMode2);
}

/**
 * @tc.name: setBarMode2Test
 * @tc.desc: Check the functionality of GENERATED_ArkUITabsModifier.setBarMode2
 * @tc.type: FUNC
 */
HWTEST_F(TabsModifierTest, setBarMode2Test, TestSize.Level1)
{
    const std::string PROP_NAME("barMode");
    ASSERT_NE(modifier_->setBarMode2, nullptr);
    auto checkVal = GetAttrValue<std::string>(GetJsonValue(node_), PROP_NAME);
    EXPECT_EQ(checkVal, "BarMode.Fixed");

    for (const auto& [value, expectVal] : SCROLLABLE_BAR_MODE_TEST_PLAN) {
        modifier_->setBarMode2(node_, ARK_BAR_MODE_SCROLLABLE, &value);
        checkVal = GetAttrValue<std::string>(GetJsonValue(node_), PROP_NAME);
        EXPECT_EQ(checkVal, expectVal);
    
        modifier_->setBarMode2(node_, ARK_BAR_MODE_FIXED, &value);
        checkVal = GetAttrValue<std::string>(GetJsonValue(node_), PROP_NAME);
        EXPECT_EQ(checkVal, "BarMode.Fixed");
    }

    std::string defaultScrollableMode = "BarMode.Scrollable,"
        "{\"margin\":\"0.00vp\","
        "\"nonScrollableLayoutStyle\":\"LayoutStyle.ALWAYS_CENTER\"}";

    modifier_->setBarMode2(node_, ARK_BAR_MODE_SCROLLABLE, nullptr);
    checkVal = GetAttrValue<std::string>(GetJsonValue(node_), PROP_NAME);
    EXPECT_EQ(checkVal, defaultScrollableMode);
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
        modifier_->setBarBackgroundBlurStyle(node_, value);
        checkVal = GetAttrValue<std::string>(GetJsonValue(node_), PROP_NAME);
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
    Ark_Function func = {};
    ASSERT_NE(frameNode, nullptr);
    auto context = reinterpret_cast<PipelineContext*>(MockPipelineContext::GetCurrent().GetRawPtr());
    frameNode->AttachToMainTree(true, context);
    modifier_->setOnChange(node_, func);

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
    Ark_Function func = {};
    modifier_->setOnAnimationStart(node_, func);

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
    Ark_Function func = {};
    modifier_->setOnAnimationEnd(node_, func);

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
    Ark_Function func = {};
    modifier_->setOnGestureSwipe(node_, func);

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
    Ark_Function func = {};
    modifier_->setCustomContentTransition(node_, func);

    auto tabsNode = AceType::DynamicCast<TabsNode>(frameNode);
    ASSERT_NE(tabsNode, nullptr);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    ASSERT_NE(swiperNode, nullptr);
    EXPECT_EQ(g_toValue, 0);
    EXPECT_EQ(g_fromValue, 0);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    swiperPattern->OnCustomContentTransition(TO);
    EXPECT_EQ(g_toValue, TO);
    EXPECT_EQ(g_fromValue, 0);
    g_toValue = 0;
}

/**
 * @tc.name: setOnContentWillChangeTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITabsModifier.setOnContentWillChange
 * @tc.type: FUNC
 */
HWTEST_F(TabsModifierTest, setOnContentWillChangeTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    Ark_Function func = {};
    modifier_->setOnContentWillChange(node_, func);

    auto tabsNode = AceType::DynamicCast<TabsNode>(frameNode);
    ASSERT_NE(tabsNode, nullptr);
    auto tabPattern = tabsNode->GetPattern<TabsPattern>();
    ASSERT_NE(tabPattern, nullptr);
    EXPECT_EQ(g_comingIndexValue, 0);
    EXPECT_EQ(g_currentIndexValue, 0);
    tabPattern->OnContentWillChange(CURRENT_INDEX, COMING_INDEX);
    EXPECT_EQ(g_comingIndexValue, COMING_INDEX);
    EXPECT_EQ(g_currentIndexValue, CURRENT_INDEX);
    g_comingIndexValue = 0;
    g_currentIndexValue = 0;
}

/**
 * @tc.name: setOnTabBarClickTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITabsModifier.setOnTabBarClick
 * @tc.type: FUNC
 */
HWTEST_F(TabsModifierTest, setOnTabBarClickTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    Ark_Function func = {};
    modifier_->setOnTabBarClick(node_, func);
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
}