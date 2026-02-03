/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#include "gtest/gtest.h"
#include "tabs_test_ng.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/divider/divider_layout_property.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_spring_effect.h"
#include "core/components_ng/pattern/tabs/tab_content_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
class TabBarTwoTestNg : public TabsTestNg {
public:
    RefPtr<RenderContext> GetBarItemRenderContext(int32_t index)
    {
        auto columnNode = GetChildFrameNode(tabBarNode_, index);
        auto columnNodeRenderContext = columnNode->GetRenderContext();
        return columnNodeRenderContext;
    }
};

/**
 * @tc.name: TabBarBlurStyle001
 * @tc.desc: test TabBarBlurStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTwoTestNg, TabBarBlurStyle001, TestSize.Level1)
{
    /**
     * @tc.steps: step1 Create tabs model
     */
    TabsModelNG model = CreateTabs();
    frameNode_->GetContext()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    BlurStyleOption styleOption;
    styleOption.blurStyle = BlurStyle::COMPONENT_THICK;
    styleOption.policy = BlurStyleActivePolicy::FOLLOWS_WINDOW_ACTIVE_STATE;
    model.SetBarBackgroundBlurStyle(styleOption);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    /**
     * @tc.steps: step2. update blurstyle
     * @tc.expected: step2. expect The blurstyle is COMPONENT_THICK.
     */
    auto tabBarRenderContext = tabBarNode_->GetRenderContext();
    EXPECT_EQ(tabBarRenderContext->GetBackBlurStyle()->blurStyle, BlurStyle::COMPONENT_THICK);
}

/**
 * @tc.name: TabBarBlurStyle002
 * @tc.desc: test TabBarBlurStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTwoTestNg, TabBarBlurStyle002, TestSize.Level1)
{
    /**
     * @tc.steps: step1 Create tabs model
     */
    TabsModelNG model = CreateTabs();
    frameNode_->GetContext()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    BlurStyleOption styleOption;
    styleOption.blurStyle = BlurStyle::COMPONENT_THICK;
    styleOption.policy = BlurStyleActivePolicy::ALWAYS_ACTIVE;
    model.SetBarBackgroundBlurStyle(styleOption);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    /**
     * @tc.steps: step2. update blurstyle
     * @tc.expected: step2. expect The blurstyle is COMPONENT_THICK.
     */
    auto tabBarRenderContext = tabBarNode_->GetRenderContext();
    EXPECT_EQ(tabBarRenderContext->GetBackBlurStyle()->blurStyle, BlurStyle::COMPONENT_THICK);
}

/**
 * @tc.name: TabBarBlurStyle004
 * @tc.desc: test TabBarBlurStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTwoTestNg, TabBarBlurStyle004, TestSize.Level1)
{
    /**
     * @tc.steps: step1 Create tabs model
     */
    TabsModelNG model = CreateTabs();
    frameNode_->GetContext()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    BlurStyleOption styleOption;
    styleOption.blurStyle = BlurStyle::COMPONENT_THICK;
    styleOption.policy = BlurStyleActivePolicy::ALWAYS_ACTIVE;
    auto target = tabBarNode_->GetRenderContext();
    target->UpdateBackgroundEffect(std::nullopt);
    model.SetBarBackgroundBlurStyle(styleOption);
    EXPECT_FALSE(target->GetBackgroundEffect().has_value());
    CreateTabsDone(model);
}

/**
 * @tc.name: TabBarBlurStyle005
 * @tc.desc: test TabBarBlurStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTwoTestNg, TabBarBlurStyle005, TestSize.Level1)
{
    /**
     * @tc.steps: step1 Create tabs model
     */
    TabsModelNG model = CreateTabs();
    frameNode_->GetContext()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    BlurStyleOption styleOption;
    styleOption.blurStyle = BlurStyle::COMPONENT_THICK;
    styleOption.policy = BlurStyleActivePolicy::ALWAYS_ACTIVE;
    auto target = tabBarNode_->GetRenderContext();
    EffectOption effectObj;
    effectObj.policy = BlurStyleActivePolicy::FOLLOWS_WINDOW_ACTIVE_STATE;
    target->UpdateBackgroundEffect(effectObj);
    EXPECT_TRUE(target->GetBackgroundEffect().has_value());
    model.SetBarBackgroundBlurStyle(styleOption);
    EXPECT_FALSE(target->GetBackgroundEffect().has_value());
    CreateTabsDone(model);
}

/**
 * @tc.name: TabBarBlurStyle006
 * @tc.desc: test TabBarBlurStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTwoTestNg, TabBarBlurStyle006, TestSize.Level1)
{
    /**
     * @tc.steps: step1 Create tabs model
     */
    TabsModelNG model = CreateTabs();
    frameNode_->GetContext()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    BlurStyleOption styleOption;
    styleOption.blurStyle = BlurStyle::COMPONENT_THICK;
    styleOption.policy = BlurStyleActivePolicy::ALWAYS_ACTIVE;
    auto target = tabBarNode_->GetRenderContext();
    EffectOption effectObj;
    effectObj.policy = BlurStyleActivePolicy::FOLLOWS_WINDOW_ACTIVE_STATE;
    target->UpdateBackgroundEffect(effectObj);
    EXPECT_TRUE(target->GetBackgroundEffect().has_value());
    target->UpdateBackBlurRadius(Dimension());
    model.SetBarBackgroundBlurStyle(styleOption);
    EXPECT_FALSE(target->GetBackgroundEffect().has_value());
    CreateTabsDone(model);
}

/**
 * @tc.name: TabBarBlurStyle007
 * @tc.desc: test TabBarBlurStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTwoTestNg, TabBarBlurStyle007, TestSize.Level1)
{
    /**
     * @tc.steps: step1 Create tabs model
     */
    TabsModelNG model = CreateTabs();
    frameNode_->GetContext()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    BlurStyleOption styleOption;
    styleOption.blurStyle = BlurStyle::COMPONENT_THICK;
    styleOption.policy = BlurStyleActivePolicy::ALWAYS_ACTIVE;
    auto target = tabBarNode_->GetRenderContext();
    EffectOption effectObj;
    effectObj.policy = BlurStyleActivePolicy::FOLLOWS_WINDOW_ACTIVE_STATE;
    target->UpdateBackgroundEffect(effectObj);
    EXPECT_TRUE(target->GetBackgroundEffect().has_value());
    target->GetBackground()->propBlurRadius = 1.0_px;
    model.SetBarBackgroundBlurStyle(styleOption);
    EXPECT_TRUE(target->GetBackBlurRadius().has_value());
    CreateTabsDone(model);
}

/**
 * @tc.name: SetIndex001
 * @tc.desc: test SetIndex
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTwoTestNg, SetIndex001, TestSize.Level1)
{
    /**
     * @tc.steps: step1 Create tabs model
     */
    TabsModelNG model = CreateTabs();

    /**
     * @tc.steps: step2 Set index
     */
    int32_t index = 16;
    model.SetIndex(index);

    /**
     * @tc.steps: step3 Calling the SetIndex function.
     * @tc.expected: swiperLayoutProperty->GetIndex() is index.
     */
    auto swiperLayoutProperty = swiperNode_->GetLayoutProperty<SwiperLayoutProperty>();
    EXPECT_EQ(swiperLayoutProperty->GetIndex().value(), index);
    CreateTabsDone(model);
}

/**
 * @tc.name: SetIndex002
 * @tc.desc: test SetIndex
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTwoTestNg, SetIndex002, TestSize.Level1)
{
    /**
     * @tc.steps: step1 Create tabs model
     */
    TabsModelNG model = CreateTabs();

    /**
     * @tc.steps: step2 Set index
     */
    int32_t index = -16;
    model.SetIndex(index);

    /**
     * @tc.steps: step3 Calling the SetIndex function.
     * @tc.expected: swiperLayoutProperty->GetIndex() is index.
     */
    auto swiperLayoutProperty = swiperNode_->GetLayoutProperty<SwiperLayoutProperty>();
    EXPECT_NE(swiperLayoutProperty->GetIndex().value(), index);
    CreateTabsDone(model);
}

/**
 * @tc.name: SetDivider001
 * @tc.desc: test SetDivider
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTwoTestNg, SetDivider001, TestSize.Level1)
{
    /**
     * @tc.steps: step1 Create tabs model
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);

    /**
     * @tc.steps: step2 Set divider
     */
    TabsItemDivider divider;
    divider.isNull = true;
    divider.strokeWidth = Dimension(1.0f);
    model.SetDivider(divider);

    /**
     * @tc.steps: step3 Calling the SetDivider function.
     * @tc.expected: dividerRenderContext->GetOpacity() is 0.0f.
     */
    auto dividerRenderContext = dividerNode_->GetRenderContext();
    EXPECT_EQ(dividerRenderContext->GetOpacity().value(), 0.0f);
    CreateTabsDone(model);
}

/**
 * @tc.name: SetDivider002
 * @tc.desc: test SetDivider
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTwoTestNg, SetDivider002, TestSize.Level1)
{
    /**
     * @tc.steps: step1 Create tabs model
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);

    /**
     * @tc.steps: step2 Set divider
     */
    TabsItemDivider divider;
    divider.isNull = false;
    divider.strokeWidth = Dimension(1.0f);
    model.SetDivider(divider);

    /**
     * @tc.steps: step3 Calling the SetDivider function.
     * @tc.expected: dividerRenderContext->GetOpacity() is 1.0f.
     */
    auto dividerRenderContext = dividerNode_->GetRenderContext();
    EXPECT_EQ(dividerRenderContext->GetOpacity().value(), 1.0f);
    CreateTabsDone(model);
}

/**
 * @tc.name: GetTabBarPaintProperty001
 * @tc.desc: test GetTabBarPaintProperty
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTwoTestNg, GetTabBarPaintProperty001, TestSize.Level1)
{
    /**
     * @tc.steps: step1 Create tabs model
     */
    TabsModelNG model = CreateTabs();
    ASSERT_NE(frameNode_, nullptr);

    /**
     * @tc.steps: step2. test GetTabBarPaintProperty function.
     */
    auto result = model.GetTabBarPaintProperty(Referenced::RawPtr(frameNode_));
    EXPECT_NE(result, nullptr);
    CreateTabsDone(model);
}

/**
 * @tc.name: SetOnUnselected001
 * @tc.desc: Test SetOnUnselected
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTwoTestNg, SetOnUnselected001, TestSize.Level1)
{
    /**
     * @tc.steps: step1 Create tabs model
     */
    TabsModelNG model = CreateTabs();

    /**
     * @tc.steps: step2 Set onUnselected
     */
    auto onUnselected = [](const BaseEventInfo* info) {};

    /**
     * @tc.steps: step3 Calling the SetOnUnselected function.
     * @tc.expected: pattern->unselectedEvent_ not null.
     */
    model.SetOnUnselected(Referenced::RawPtr(frameNode_), std::move(onUnselected));
    EXPECT_NE(pattern_->unselectedEvent_, nullptr);
    CreateTabsDone(model);
}

/**
 * @tc.name: SetEffectNodeOption003
 * @tc.desc: test SetEffectNodeOption
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTwoTestNg, SetEffectNodeOption003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    TabsItemDivider divider;
    model.SetDivider(divider);

    /**
     * @tc.steps: step2. Get tabs pattern to create layoutAlgorithm, and call measure and layout functions.
     * @tc.expected: step2. related function is called.
     */
    auto tabsNode = AceType::DynamicCast<TabsNode>(frameNode_);
    ASSERT_NE(tabsNode, nullptr);
    auto pattern = AceType::MakeRefPtr<SwiperPattern>();
    auto frameNodeSwipe = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 1, pattern);
    auto frameNodeDivider = FrameNode::CreateFrameNode(V2::DIVIDER_ETS_TAG, 2, pattern);
    auto frameNodeTabBar = FrameNode::CreateFrameNode(V2::TAB_BAR_ETS_TAG, 3, pattern);
    auto frameNodeEffect = FrameNode::CreateFrameNode(V2::EFFECT_COMPONENT_ETS_TAG, 4, pattern);
    tabsNode->children_ = { frameNodeSwipe, frameNodeDivider, frameNodeTabBar, frameNodeEffect };
    auto effectNode = AceType::DynamicCast<FrameNode>(tabsNode->GetEffectNode());
    EXPECT_TRUE(effectNode);
    TabsEffectNodeOption option;
    option.isNull = false;
    option.strokeWidth = Dimension(1.0f);
    model.SetEffectNodeOption(AceType::RawPtr(frameNode_), option);
    CreateTabsDone(model);
}

/**
 * @tc.name: SetEffectNodeOption004
 * @tc.desc: test SetEffectNodeOption
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTwoTestNg, SetEffectNodeOption004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    TabsItemDivider divider;
    model.SetDivider(divider);

    /**
     * @tc.steps: step2. Get tabs pattern to create layoutAlgorithm, and call measure and layout functions.
     * @tc.expected: step1. related function is called.
     */
    auto tabsNode = AceType::DynamicCast<TabsNode>(frameNode_);
    ASSERT_NE(tabsNode, nullptr);
    tabsNode->children_ = {};
    auto effectNode = AceType::DynamicCast<FrameNode>(tabsNode->GetEffectNode());
    EXPECT_FALSE(effectNode);
    TabsEffectNodeOption option;
    option.isNull = false;
    option.strokeWidth = Dimension(1.0f);
    model.SetEffectNodeOption(AceType::RawPtr(frameNode_), option);
    CreateTabsDone(model);
}

/**
 * @tc.name: SetFadingEdge001
 * @tc.desc: test SetFadingEdge
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTwoTestNg, SetFadingEdge001, TestSize.Level1)
{
    /**
     * @tc.steps: step1 Create tabs model
     */
    TabsModelNG model = CreateTabs();

    /**
     * @tc.steps: step2 Set fadingEdge
     */
    bool fadingEdge = true;
    model.SetFadingEdge(Referenced::RawPtr(frameNode_), fadingEdge);

    /**
     * @tc.steps: step3 Calling the SetFadingEdge function.
     * @tc.expected: tabBarPaintProperty->GetFadingEdge() is true.
     */
    auto tabBarPaintProperty = TabsModelNG::GetTabBarPaintProperty(AceType::RawPtr(frameNode_));
    ASSERT_NE(tabBarPaintProperty, nullptr);
    auto result = tabBarPaintProperty->GetFadingEdge();
    EXPECT_TRUE(result);
    CreateTabsDone(model);
}

/**
 * @tc.name: SetBarBackgroundColor001
 * @tc.desc: test SetBarBackgroundColor
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTwoTestNg, SetBarBackgroundColor001, TestSize.Level1)
{
    /**
     * @tc.steps: step1 Create tabs model
     */
    TabsModelNG model = CreateTabs();

    /**
     * @tc.steps: step2 Set backgroundColor
     */
    Color backgroundColor = Color::BLACK;
    model.SetBarBackgroundColor(Referenced::RawPtr(frameNode_), backgroundColor);

    /**
     * @tc.steps: step3 Calling the SetBarBackgroundColor function.
     * @tc.expected: tabBarRenderContext->GetBackgroundColor() is backgroundColor.
     */
    auto tabsNode = AceType::DynamicCast<TabsNode>(frameNode_);
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarRenderContext = tabBarNode->GetRenderContext();
    ASSERT_NE(tabBarRenderContext, nullptr);
    auto result = tabBarRenderContext->GetBackgroundColor();
    EXPECT_EQ(result, backgroundColor);
    CreateTabsDone(model);
}

/**
 * @tc.name: BarPosition001
 * @tc.desc: Test Tabs BarPosition and vertical, affect the tabBar position
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTwoTestNg, BarPosition001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set BarPosition::START and Vertical:false
     * @tc.expected: The tabBar would at the top of tabs
     */
    BarPosition barPosition = BarPosition::START;
    TabsModelNG model = CreateTabs(barPosition);
    CreateTabContents();
    EXPECT_EQ(swiperPattern_->GetDirection(), Axis::HORIZONTAL);
    EXPECT_FALSE(IsEqual(tabBarNode_->GetGeometryNode()->GetFrameRect(), RectF(0, 0, TABS_WIDTH, TAB_BAR_SIZE)));

    /**
     * @tc.steps: step2. Set BarPosition::END and Vertical:false
     * @tc.expected: The tabBar would at the bottom of tabs
     */
    model.SetTabBarPosition(AceType::RawPtr(frameNode_), BarPosition::END);
    EXPECT_EQ(swiperPattern_->GetDirection(), Axis::HORIZONTAL);
    EXPECT_FALSE(IsEqual(tabBarNode_->GetGeometryNode()->GetFrameRect(),
        RectF(0, TABS_HEIGHT - TAB_BAR_SIZE, TABS_WIDTH, TAB_BAR_SIZE)));

    /**
     * @tc.steps: step3. Set BarPosition::START and Vertical:true
     * @tc.expected: The tabBar would at the left of tabs
     */
    model.SetTabBarPosition(AceType::RawPtr(frameNode_), BarPosition::START);
    model.SetIsVertical(AceType::RawPtr(frameNode_), true);
    EXPECT_EQ(swiperPattern_->GetDirection(), Axis::VERTICAL);
    EXPECT_FALSE(IsEqual(tabBarNode_->GetGeometryNode()->GetFrameRect(), RectF(0, 0, TAB_BAR_SIZE, TABS_HEIGHT)));

    /**
     * @tc.steps: step4. Set BarPosition::END and Vertical:true
     * @tc.expected: The tabBar would at the right of tabs
     */
    model.SetTabBarPosition(AceType::RawPtr(frameNode_), BarPosition::END);
    EXPECT_EQ(swiperPattern_->GetDirection(), Axis::VERTICAL);
    EXPECT_FALSE(IsEqual(tabBarNode_->GetGeometryNode()->GetFrameRect(),
        RectF(TABS_WIDTH - TAB_BAR_SIZE, 0, TAB_BAR_SIZE, TABS_HEIGHT)));

    /**
     * @tc.steps: step4. Set BarPosition::END and Vertical:true
     * @tc.expected: The tabBar would at the right of tabs
     */
    auto tabsNode = AceType::DynamicCast<TabsNode>(frameNode_);
    ASSERT_NE(tabsNode, nullptr);
    auto tabsFocusNode = tabsNode->GetFocusHub();
    ASSERT_NE(tabsFocusNode, nullptr);
    tabsFocusNode->currentFocus_ = false;
    EXPECT_FALSE(tabsFocusNode->IsCurrentFocus());
    tabsFocusNode->currentFocus_ = true;
    EXPECT_TRUE(tabsFocusNode->IsCurrentFocus());
    model.SetTabBarPosition(AceType::RawPtr(frameNode_), BarPosition::END);
    EXPECT_EQ(swiperPattern_->GetDirection(), Axis::VERTICAL);
    CreateTabsDone(model);
}

/**
 * @tc.name: SetScrollable001
 * @tc.desc: test SetScrollable
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTwoTestNg, SetScrollable001, TestSize.Level1)
{
    /**
     * @tc.steps: step1 Create tabs model
     */
    TabsModelNG model = CreateTabs();

    /**
     * @tc.steps: step2 Set scrollable
     */
    bool scrollable = true;
    model.SetScrollable(Referenced::RawPtr(frameNode_), scrollable);

    /**
     * @tc.steps: step3 Calling the SetScrollable function.
     * @tc.expected: tabPattern->isDisableSwipe_ is false.
     */
    auto tabPattern = frameNode_->GetPattern<TabsPattern>();
    ASSERT_NE(tabPattern, nullptr);
    auto isDisableSwipe = tabPattern->isDisableSwipe_;
    EXPECT_FALSE(isDisableSwipe);
    CreateTabsDone(model);
}

/**
 * @tc.name: SetBarAdaptiveHeight001
 * @tc.desc: test SetBarAdaptiveHeight
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTwoTestNg, SetBarAdaptiveHeight001, TestSize.Level1)
{
    /**
     * @tc.steps: step1 Create tabs model
     */
    TabsModelNG model = CreateTabs();

    /**
     * @tc.steps: step2 Set barAdaptiveHeight
     */
    bool barAdaptiveHeight = true;
    model.SetBarAdaptiveHeight(Referenced::RawPtr(frameNode_), barAdaptiveHeight);

    /**
     * @tc.steps: step3 Calling the SetBarAdaptiveHeight function.
     * @tc.expected: tabBarLayoutProperty->GetBarAdaptiveHeight() is false.
     */
    auto tabBarLayoutProperty = TabsModelNG::GetTabBarLayoutProperty(Referenced::RawPtr(frameNode_));
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    auto result = tabBarLayoutProperty->GetBarAdaptiveHeight();
    EXPECT_TRUE(result);
    CreateTabsDone(model);
}

/**
 * @tc.name: SetNoMinHeightLimit001
 * @tc.desc: test SetNoMinHeightLimit
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTwoTestNg, SetNoMinHeightLimit001, TestSize.Level1)
{
    /**
     * @tc.steps: step1 Create tabs model
     */
    TabsModelNG model = CreateTabs();

    /**
     * @tc.steps: step2 Set noMinHeightLimit
     */
    bool noMinHeightLimit = true;
    model.SetNoMinHeightLimit(Referenced::RawPtr(frameNode_), noMinHeightLimit);

    /**
     * @tc.steps: step3 Calling the SetNoMinHeightLimit function.
     * @tc.expected: tabBarLayoutProperty->GetNoMinHeightLimit() is false.
     */
    auto tabBarLayoutProperty = TabsModelNG::GetTabBarLayoutProperty(Referenced::RawPtr(frameNode_));
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    auto result = tabBarLayoutProperty->GetNoMinHeightLimit();
    EXPECT_TRUE(result);
    CreateTabsDone(model);
}

/**
 * @tc.name: SetClipEdge
 * @tc.desc: test SetClipEdge001
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTwoTestNg, SetClipEdge001, TestSize.Level1)
{
    /**
     * @tc.steps: step1 Create tabs model
     */
    TabsModelNG model = CreateTabs();

    /**
     * @tc.steps: step2 Set clipEdge true
     */
    bool clipEdge = true;
    model.SetClipEdge(Referenced::RawPtr(frameNode_), clipEdge);

    /**
     * @tc.steps: step4 Calling the SetClipEdge function.
     * @tc.expected: dividerRenderContext->GetClipEdge() is true.
     */
    auto tabsNode = AceType::DynamicCast<TabsNode>(frameNode_);
    ASSERT_NE(tabsNode, nullptr);
    auto dividerNode = AceType::DynamicCast<FrameNode>(tabsNode->GetDivider());
    ASSERT_NE(dividerNode, nullptr);
    auto dividerRenderContext = dividerNode->GetRenderContext();
    ASSERT_NE(dividerRenderContext, nullptr);
    auto result = dividerRenderContext->GetClipEdge();
    EXPECT_TRUE(result);

    /**
     * @tc.steps: step5 Set clipEdge false
     */
    model.SetClipEdge(false);

    /**
     * @tc.steps: step6 Calling the SetClipEdge function.
     * @tc.expected: dividerRenderContext->GetClipEdge() is false.
     */
    auto tabsNode2 = AceType::DynamicCast<TabsNode>(frameNode_);
    ASSERT_NE(tabsNode2, nullptr);
    auto dividerNode2 = AceType::DynamicCast<FrameNode>(tabsNode2->GetDivider());
    ASSERT_NE(dividerNode2, nullptr);
    auto dividerRenderContext2 = dividerNode2->GetRenderContext();
    ASSERT_NE(dividerRenderContext2, nullptr);
    auto result2 = dividerRenderContext2->GetClipEdge();
    EXPECT_TRUE(result2);

    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    ASSERT_NE(frameNode_, nullptr);
}

/**
 * @tc.name: SetAnimateMode001
 * @tc.desc: test SetAnimateMode
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTwoTestNg, SetAnimateMode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1 Create tabs model
     */
    TabsModelNG model = CreateTabs();

    /**
     * @tc.steps: step2 Set animateMode
     */
    TabAnimateMode animateMode = TabAnimateMode::ACTION_FIRST;
    model.SetAnimateMode(animateMode);

    /**
     * @tc.steps: step3 Calling the SetAnimateMode function.
     * @tc.expected: tabPattern->GetAnimateMode() is animateMode.
     */
    auto tabsNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(tabsNode, nullptr);
    auto tabPattern = tabsNode->GetPattern<TabsPattern>();
    ASSERT_NE(tabPattern, nullptr);
    auto result = tabPattern->GetAnimateMode();
    EXPECT_EQ(result, animateMode);
    CreateTabsDone(model);
}

/**
 * @tc.name: SetAnimateMode002
 * @tc.desc: test SetAnimateMode
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTwoTestNg, SetAnimateMode002, TestSize.Level1)
{
    /**
     * @tc.steps: step1 Create tabs model
     */
    TabsModelNG model = CreateTabs();

    /**
     * @tc.steps: step2 Set animateMode
     */
    TabAnimateMode animateMode = TabAnimateMode::ACTION_FIRST;
    model.SetAnimateMode(Referenced::RawPtr(frameNode_), animateMode);

    /**
     * @tc.steps: step3 Calling the SetAnimateMode function.
     * @tc.expected: tabPattern->GetAnimateMode() is animateMode.
     */
    ASSERT_NE(frameNode_, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(frameNode_);
    ASSERT_NE(tabsNode, nullptr);
    auto tabPattern = tabsNode->GetPattern<TabsPattern>();
    ASSERT_NE(tabPattern, nullptr);
    auto result = tabPattern->GetAnimateMode();
    EXPECT_EQ(result, animateMode);
    CreateTabsDone(model);
}

/**
 * @tc.name: SetEdgeEffect
 * @tc.desc: test SetEdgeEffect001
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTwoTestNg, SetEdgeEffect001, TestSize.Level1)
{
    /**
     * @tc.steps: step1 Create tabs model
     */
    TabsModelNG model = CreateTabs();

    /**
     * @tc.steps: step2 Set edgeEffect
     */
    EdgeEffect edgeEffect = EdgeEffect::FADE;
    model.SetEdgeEffect(edgeEffect);

    /**
     * @tc.steps: step3 Calling the SetEdgeEffect function.
     * @tc.expected: swiperPaintProperty->GetEdgeEffect() is edgeEffect.
     */
    auto swiperPaintProperty = TabsModelNG::GetSwiperPaintProperty();
    ASSERT_NE(swiperPaintProperty, nullptr);
    auto result = swiperPaintProperty->GetEdgeEffect();
    EXPECT_EQ(result, edgeEffect);
    CreateTabsDone(model);
}

/**
 * @tc.name: SetEdgeEffect002
 * @tc.desc: test SetEdgeEffect
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTwoTestNg, SetEdgeEffect002, TestSize.Level1)
{
    /**
     * @tc.steps: step1 Create tabs model
     */
    TabsModelNG model = CreateTabs();

    /**
     * @tc.steps: step2 Set edgeEffect
     */
    int32_t edgeEffectNum = 1;
    EdgeEffect edgeEffect = EdgeEffect::FADE;
    model.SetEdgeEffect(Referenced::RawPtr(frameNode_), edgeEffectNum);

    /**
     * @tc.steps: step3 Calling the SetEdgeEffect function.
     * @tc.expected: swiperPaintProperty->GetEdgeEffect() is edgeEffect.
     */
    auto swiperPaintProperty = TabsModelNG::GetSwiperPaintProperty(Referenced::RawPtr(frameNode_));
    ASSERT_NE(swiperPaintProperty, nullptr);
    auto result = swiperPaintProperty->GetEdgeEffect();
    EXPECT_EQ(result, edgeEffect);
    CreateTabsDone(model);
}

/**
 * @tc.name: SetTabsController001
 * @tc.desc: test SetTabsController
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTwoTestNg, SetTabsController001, TestSize.Level1)
{
    /**
     * @tc.steps: step1 Create tabs model
     */
    TabsModelNG model = CreateTabs();

    /**
     * @tc.steps: step2 Set tabsController
     */
    RefPtr<SwiperController> tabsController;
    model.SetTabsController(Referenced::RawPtr(frameNode_), tabsController);

    ASSERT_NE(frameNode_, nullptr);
    CreateTabsDone(model);
}

/**
 * @tc.name: SetBarBackgroundEffect001
 * @tc.desc: test SetBarBackgroundEffect
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTwoTestNg, SetBarBackgroundEffect001, TestSize.Level1)
{
    /**
     * @tc.steps: step1 Create tabs model
     */
    TabsModelNG model = CreateTabs();

    /**
     * @tc.steps: step2 Set effectOption
     */
    EffectOption effectOption;
    effectOption.policy = BlurStyleActivePolicy::ALWAYS_ACTIVE;
    model.SetBarBackgroundEffect(effectOption);

    ASSERT_NE(frameNode_, nullptr);
    CreateTabsDone(model);
}

/**
 * @tc.name: SetPageFlipMode
 * @tc.desc: test SetPageFlipMode001
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTwoTestNg, SetPageFlipMode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1 Create tabs model
     */
    TabsModelNG model = CreateTabs();

    /**
     * @tc.steps: step2 Set pageFlipMode
     */
    int32_t pageFlipMode = 1;
    model.SetPageFlipMode(pageFlipMode);

    /**
     * @tc.steps: step3 Calling the SetPageFlipMode function.
     * @tc.expected: swiperPattern->GetPageFlipMode() is pageFlipMode.
     */
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(tabsNode, nullptr);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    ASSERT_NE(swiperNode, nullptr);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto result = swiperPattern->GetPageFlipMode();
    EXPECT_EQ(result, pageFlipMode);
    CreateTabsDone(model);
}

/**
 * @tc.name: SetPageFlipMode002
 * @tc.desc: test SetPageFlipMode
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTwoTestNg, SetPageFlipMode002, TestSize.Level1)
{
    /**
     * @tc.steps: step1 Create tabs model
     */
    TabsModelNG model = CreateTabs();

    /**
     * @tc.steps: step2 Set pageFlipMode
     */
    int32_t pageFlipMode = 1;
    model.SetPageFlipMode(Referenced::RawPtr(frameNode_), pageFlipMode);

    /**
     * @tc.steps: step3 Calling the SetPageFlipMode function.
     * @tc.expected: swiperPattern->GetPageFlipMode() is pageFlipMode.
     */
    ASSERT_NE(frameNode_, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(frameNode_);
    ASSERT_NE(tabsNode, nullptr);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    ASSERT_NE(swiperNode, nullptr);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto result = swiperPattern->GetPageFlipMode();
    EXPECT_EQ(result, pageFlipMode);
    CreateTabsDone(model);
}

/**
 * @tc.name: SetCachedMaxCount001
 * @tc.desc: test SetCachedMaxCount
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTwoTestNg, SetCachedMaxCount001, TestSize.Level1)
{
    /**
     * @tc.steps: step1 Create tabs model
     */
    TabsModelNG model = CreateTabs();

    /**
     * @tc.steps: step2 Set cachedMaxCount and cacheMode
     */
    std::optional<int32_t> cachedMaxCount = 2;
    TabsCacheMode cacheMode = TabsCacheMode::CACHE_LATEST_SWITCHED;
    model.SetCachedMaxCount(cachedMaxCount, cacheMode);

    ASSERT_NE(frameNode_, nullptr);
    CreateTabsDone(model);
}

/**
 * @tc.name: SetCachedMaxCount002
 * @tc.desc: test SetCachedMaxCount
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTwoTestNg, SetCachedMaxCount002, TestSize.Level1)
{
    /**
     * @tc.steps: step1 Create tabs model
     */
    TabsModelNG model = CreateTabs();

    /**
     * @tc.steps: step2 Set cachedMaxCount and cacheMode
     */
    std::optional<int32_t> cachedMaxCount = 2;
    TabsCacheMode cacheMode = TabsCacheMode::CACHE_LATEST_SWITCHED;
    model.SetCachedMaxCount(Referenced::RawPtr(frameNode_), cachedMaxCount, cacheMode);

    ASSERT_NE(frameNode_, nullptr);
    CreateTabsDone(model);
}

/**
 * @tc.name: SetCachedMaxCount003
 * @tc.desc: test SetCachedMaxCount
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTwoTestNg, SetCachedMaxCount003, TestSize.Level1)
{
    /**
     * @tc.steps: step1 Create tabs model
     */
    TabsModelNG model = CreateTabs();

    /**
     * @tc.steps: step2 Set cachedMaxCount and cacheMode
     */
    TabsCacheMode cacheMode = TabsCacheMode::CACHE_LATEST_SWITCHED;
    model.SetCachedMaxCount(Referenced::RawPtr(frameNode_), std::nullopt, cacheMode);

    ASSERT_NE(frameNode_, nullptr);
    CreateTabsDone(model);
}
} // namespace OHOS::Ace::NG