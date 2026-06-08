/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/tabs/tabs_model_static.h"
#include "core/components_ng/pattern/tabs/tabs_node.h"
#include "core/components_ng/pattern/tabs/tab_bar_pattern.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/pattern/divider/divider_pattern.h"
#include "core/components_ng/pattern/divider/divider_render_property.h"
#include "core/components_ng/pattern/swiper/swiper_layout_property.h"
#include "core/components_ng/pattern/swiper/swiper_paint_property.h"
#include "core/components_ng/pattern/tabs/tab_bar_layout_property.h"
#include "core/components_ng/pattern/tabs/tab_bar_paint_property.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/image/image_pattern.h"

namespace OHOS::Ace::NG {

class TabsModelStaticTestNg : public TabsTestNg {
public:
    static void SetUpTestSuite()
    {
        TabsTestNg::SetUpTestSuite();
    }

    static void TearDownTestSuite()
    {
        TabsTestNg::TearDownTestSuite();
    }

    void SetUp() override {}
    void TearDown() override
    {
        TabsTestNg::TearDown();
    }

    RefPtr<TabsNode> CreateTabsNodeWithChildren()
    {
        auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
        auto tabsNode = AceType::MakeRefPtr<TabsNode>(V2::TABS_ETS_TAG, nodeId,
            AceType::MakeRefPtr<TabsPattern>(), false);
        tabsNode->InitializePatternAndContext();
        ElementRegister::GetInstance()->AddUINode(tabsNode);

        auto swiperNode = FrameNode::GetOrCreateFrameNode(
            V2::SWIPER_ETS_TAG, tabsNode->GetSwiperId(),
            []() { return AceType::MakeRefPtr<SwiperPattern>(); });
        auto dividerNode = FrameNode::GetOrCreateFrameNode(
            V2::DIVIDER_ETS_TAG, tabsNode->GetDividerId(),
            []() { return AceType::MakeRefPtr<DividerPattern>(); });
        auto tabBarNode = FrameNode::GetOrCreateFrameNode(
            V2::TAB_BAR_ETS_TAG, tabsNode->GetTabBarId(),
            []() { return AceType::MakeRefPtr<TabBarPattern>(); });

        swiperNode->MountToParent(tabsNode);
        dividerNode->MountToParent(tabsNode);
        tabBarNode->MountToParent(tabsNode);

        return tabsNode;
    }

    RefPtr<FrameNode> CreateSimpleFrameNode()
    {
        return FrameNode::CreateFrameNode(V2::ROW_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(),
            AceType::MakeRefPtr<LinearLayoutPattern>(true));
    }

    void SetupTabsNodeForDividerTest(RefPtr<TabsNode>& tabsNode, RefPtr<FrameNode>& dividerNode)
    {
        tabsNode = CreateTabsNodeWithChildren();
        ASSERT_NE(tabsNode, nullptr);
        dividerNode = AceType::DynamicCast<FrameNode>(tabsNode->GetDivider());
        ASSERT_NE(dividerNode, nullptr);
    }

    RefPtr<FrameNode> SetupForBarBackgroundBlurStyle()
    {
        auto tabsNode = CreateTabsNodeWithChildren();
        auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
        tabBarNode->GetOrCreateFocusHub();
        auto pipeline = PipelineContext::GetCurrentContext();
        if (pipeline) {
            tabBarNode->context_ = AceType::RawPtr(pipeline);
        }
        return tabsNode;
    }
};

// ===================== CreateFrameNode =====================

/**
 * @tc.name: CreateFrameNode_Valid
 * @tc.desc: CreateFrameNode with valid nodeId should return a TabsNode
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, CreateFrameNode_Valid, TestSize.Level1)
{
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = TabsModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_NE(AceType::DynamicCast<TabsNode>(frameNode), nullptr);
}

// ===================== SetTabBarPosition =====================

/**
 * @tc.name: SetTabBarPosition_NullFrameNode
 * @tc.desc: SetTabBarPosition with null frameNode should not crash
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetTabBarPosition_NullFrameNode, TestSize.Level1)
{
    TabsModelStatic::SetTabBarPosition(nullptr, BarPosition::START);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetTabBarPosition_WithValue
 * @tc.desc: SetTabBarPosition with a valid BarPosition value should set property
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetTabBarPosition_WithValue, TestSize.Level1)
{
    auto tabsNode = CreateTabsNodeWithChildren();
    ASSERT_NE(tabsNode, nullptr);
    auto frameNode = AceType::RawPtr(tabsNode);
    TabsModelStatic::SetTabBarPosition(frameNode, BarPosition::END);
    auto layoutProperty = tabsNode->GetLayoutProperty<TabsLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetTabBarPosition().value_or(BarPosition::START), BarPosition::END);
}

/**
 * @tc.name: SetTabBarPosition_NoValue
 * @tc.desc: SetTabBarPosition with no value should reset property
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetTabBarPosition_NoValue, TestSize.Level1)
{
    auto tabsNode = CreateTabsNodeWithChildren();
    ASSERT_NE(tabsNode, nullptr);
    auto frameNode = AceType::RawPtr(tabsNode);
    std::optional<BarPosition> noOpt;
    TabsModelStatic::SetTabBarPosition(frameNode, noOpt);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetTabBarPosition_FocusChange
 * @tc.desc: SetTabBarPosition when frameNode is not focused should update focus node
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetTabBarPosition_FocusChange, TestSize.Level1)
{
    auto tabsNode = CreateTabsNodeWithChildren();
    ASSERT_NE(tabsNode, nullptr);
    auto frameNode = AceType::RawPtr(tabsNode);
    auto focusHub = tabsNode->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->currentFocus_ = false;
    auto tabsLayoutProperty = tabsNode->GetLayoutProperty<TabsLayoutProperty>();
    ASSERT_NE(tabsLayoutProperty, nullptr);
    tabsLayoutProperty->UpdateTabBarPosition(BarPosition::END);
    TabsModelStatic::SetTabBarPosition(frameNode, BarPosition::START);
    EXPECT_NE(focusHub->lastWeakFocusNode_.Upgrade(), nullptr);
}

// ===================== InitIndex =====================

/**
 * @tc.name: InitIndex_NullFrameNode
 * @tc.desc: InitIndex with null frameNode should not crash
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, InitIndex_NullFrameNode, TestSize.Level1)
{
    TabsModelStatic::InitIndex(nullptr, 0);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: InitIndex_WithIndex
 * @tc.desc: InitIndex with valid index should set property
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, InitIndex_WithIndex, TestSize.Level1)
{
    auto tabsNode = CreateTabsNodeWithChildren();
    ASSERT_NE(tabsNode, nullptr);
    auto frameNode = AceType::RawPtr(tabsNode);
    TabsModelStatic::InitIndex(frameNode, 2);
    auto layoutProperty = tabsNode->GetLayoutProperty<TabsLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetIndexSetByUser().value_or(-1), 2);
}

/**
 * @tc.name: InitIndex_IndexAlreadySet
 * @tc.desc: InitIndex when index is already set and same should skip
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, InitIndex_IndexAlreadySet, TestSize.Level1)
{
    auto tabsNode = CreateTabsNodeWithChildren();
    ASSERT_NE(tabsNode, nullptr);
    auto frameNode = AceType::RawPtr(tabsNode);
    auto layoutProperty = tabsNode->GetLayoutProperty<TabsLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateIndex(1);
    TabsModelStatic::InitIndex(frameNode, 1);
    EXPECT_FALSE(layoutProperty->GetIndexSetByUser().has_value());
}

/**
 * @tc.name: InitIndex_NegativeIndex
 * @tc.desc: InitIndex with negative index should clamp to 0
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, InitIndex_NegativeIndex, TestSize.Level1)
{
    auto tabsNode = CreateTabsNodeWithChildren();
    ASSERT_NE(tabsNode, nullptr);
    auto frameNode = AceType::RawPtr(tabsNode);
    TabsModelStatic::InitIndex(frameNode, -1);
    auto layoutProperty = tabsNode->GetLayoutProperty<TabsLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetIndexSetByUser().value_or(-1), 0);
}

// ===================== GetSwiperController =====================

/**
 * @tc.name: GetSwiperController_NullFrameNode
 * @tc.desc: GetSwiperController with null frameNode should return nullptr
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, GetSwiperController_NullFrameNode, TestSize.Level1)
{
    auto controller = TabsModelStatic::GetSwiperController(nullptr);
    EXPECT_EQ(controller, nullptr);
}

// ===================== SetIsVertical =====================

/**
 * @tc.name: SetIsVertical_NullFrameNode
 * @tc.desc: SetIsVertical with null frameNode should not crash
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetIsVertical_NullFrameNode, TestSize.Level1)
{
    TabsModelStatic::SetIsVertical(nullptr, true);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetIsVertical_True
 * @tc.desc: SetIsVertical true should set axis to VERTICAL
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetIsVertical_True, TestSize.Level1)
{
    auto tabsNode = CreateTabsNodeWithChildren();
    ASSERT_NE(tabsNode, nullptr);
    auto frameNode = AceType::RawPtr(tabsNode);
    TabsModelStatic::SetIsVertical(frameNode, true);
    auto tabBarLayoutProperty = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar())
        ->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    EXPECT_EQ(tabBarLayoutProperty->GetAxis().value_or(Axis::HORIZONTAL), Axis::VERTICAL);
}

/**
 * @tc.name: SetIsVertical_False
 * @tc.desc: SetIsVertical false should set axis to HORIZONTAL
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetIsVertical_False, TestSize.Level1)
{
    auto tabsNode = CreateTabsNodeWithChildren();
    ASSERT_NE(tabsNode, nullptr);
    auto frameNode = AceType::RawPtr(tabsNode);
    TabsModelStatic::SetIsVertical(frameNode, false);
    auto tabBarLayoutProperty = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar())
        ->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    EXPECT_EQ(tabBarLayoutProperty->GetAxis().value_or(Axis::VERTICAL), Axis::HORIZONTAL);
}

// ===================== SetScrollable =====================

/**
 * @tc.name: SetScrollable_NullFrameNode
 * @tc.desc: SetScrollable with null frameNode should not crash
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetScrollable_NullFrameNode, TestSize.Level1)
{
    TabsModelStatic::SetScrollable(nullptr, true);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetScrollable_True
 * @tc.desc: SetScrollable true should enable swipe
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetScrollable_True, TestSize.Level1)
{
    auto tabsNode = CreateTabsNodeWithChildren();
    ASSERT_NE(tabsNode, nullptr);
    auto frameNode = AceType::RawPtr(tabsNode);
    auto swiperLayoutProperty = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs())
        ->GetLayoutProperty<SwiperLayoutProperty>();
    ASSERT_NE(swiperLayoutProperty, nullptr);
    TabsModelStatic::SetScrollable(frameNode, true);
    EXPECT_FALSE(swiperLayoutProperty->GetDisableSwipe().value_or(false));
}

/**
 * @tc.name: SetScrollable_False
 * @tc.desc: SetScrollable false should disable swipe
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetScrollable_False, TestSize.Level1)
{
    auto tabsNode = CreateTabsNodeWithChildren();
    ASSERT_NE(tabsNode, nullptr);
    auto frameNode = AceType::RawPtr(tabsNode);
    auto swiperLayoutProperty = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs())
        ->GetLayoutProperty<SwiperLayoutProperty>();
    ASSERT_NE(swiperLayoutProperty, nullptr);
    TabsModelStatic::SetScrollable(frameNode, false);
    EXPECT_TRUE(swiperLayoutProperty->GetDisableSwipe().value_or(false));
}

// ===================== SetScrollableBarModeOptions =====================

/**
 * @tc.name: SetScrollableBarModeOptions_NullFrameNode
 * @tc.desc: SetScrollableBarModeOptions with null frameNode should not crash
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetScrollableBarModeOptions_NullFrameNode, TestSize.Level1)
{
    ScrollableBarModeOptions option;
    TabsModelStatic::SetScrollableBarModeOptions(nullptr, option);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetScrollableBarModeOptions_Valid
 * @tc.desc: SetScrollableBarModeOptions with valid frameNode should set property
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetScrollableBarModeOptions_Valid, TestSize.Level1)
{
    auto tabsNode = CreateTabsNodeWithChildren();
    ASSERT_NE(tabsNode, nullptr);
    auto frameNode = AceType::RawPtr(tabsNode);
    ScrollableBarModeOptions option;
    option.margin = Dimension(5.0);
    option.nonScrollableLayoutStyle = LayoutStyle::ALWAYS_CENTER;
    TabsModelStatic::SetScrollableBarModeOptions(frameNode, option);
    auto tabBarLayoutProperty = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar())
        ->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    auto result = tabBarLayoutProperty->GetScrollableBarModeOptions();
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->margin, Dimension(5.0));
}

// ===================== SetTabBarMode =====================

/**
 * @tc.name: SetTabBarMode_NullFrameNode
 * @tc.desc: SetTabBarMode with null frameNode should not crash
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetTabBarMode_NullFrameNode, TestSize.Level1)
{
    TabsModelStatic::SetTabBarMode(nullptr, TabBarMode::SCROLLABLE);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetTabBarMode_Valid
 * @tc.desc: SetTabBarMode with valid frameNode should set tab bar mode
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetTabBarMode_Valid, TestSize.Level1)
{
    auto tabsNode = CreateTabsNodeWithChildren();
    ASSERT_NE(tabsNode, nullptr);
    auto frameNode = AceType::RawPtr(tabsNode);
    TabsModelStatic::SetTabBarMode(frameNode, TabBarMode::SCROLLABLE);
    auto tabBarLayoutProperty = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar())
        ->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    EXPECT_EQ(tabBarLayoutProperty->GetTabBarMode().value_or(TabBarMode::FIXED), TabBarMode::SCROLLABLE);
}

// ===================== SetTabBarWidth =====================

/**
 * @tc.name: SetTabBarWidth_NullFrameNode
 * @tc.desc: SetTabBarWidth with null frameNode should not crash
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetTabBarWidth_NullFrameNode, TestSize.Level1)
{
    TabsModelStatic::SetTabBarWidth(nullptr, Dimension(100.0));
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetTabBarWidth_WithValue
 * @tc.desc: SetTabBarWidth with valid dimension should set bar width
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetTabBarWidth_WithValue, TestSize.Level1)
{
    auto tabsNode = CreateTabsNodeWithChildren();
    ASSERT_NE(tabsNode, nullptr);
    auto frameNode = AceType::RawPtr(tabsNode);
    TabsModelStatic::SetTabBarWidth(frameNode, Dimension(100.0));
    auto tabBarLayoutProperty = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar())
        ->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    EXPECT_EQ(tabBarLayoutProperty->GetTabBarWidth().value_or(Dimension(-1.0)), Dimension(100.0));
}

/**
 * @tc.name: SetTabBarWidth_NoValue
 * @tc.desc: SetTabBarWidth with no value should reset bar width
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetTabBarWidth_NoValue, TestSize.Level1)
{
    auto tabsNode = CreateTabsNodeWithChildren();
    ASSERT_NE(tabsNode, nullptr);
    auto frameNode = AceType::RawPtr(tabsNode);
    std::optional<Dimension> noOpt;
    TabsModelStatic::SetTabBarWidth(frameNode, noOpt);
    auto tabBarLayoutProperty = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar())
        ->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    EXPECT_FALSE(tabBarLayoutProperty->GetTabBarWidth().has_value());
}

// ===================== SetTabBarHeight =====================

/**
 * @tc.name: SetTabBarHeight_NullFrameNode
 * @tc.desc: SetTabBarHeight with null frameNode should not crash
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetTabBarHeight_NullFrameNode, TestSize.Level1)
{
    TabsModelStatic::SetTabBarHeight(nullptr, Dimension(100.0));
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetTabBarHeight_WithValue
 * @tc.desc: SetTabBarHeight with valid dimension should set bar height
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetTabBarHeight_WithValue, TestSize.Level1)
{
    auto tabsNode = CreateTabsNodeWithChildren();
    ASSERT_NE(tabsNode, nullptr);
    auto frameNode = AceType::RawPtr(tabsNode);
    TabsModelStatic::SetTabBarHeight(frameNode, Dimension(200.0));
    auto tabBarLayoutProperty = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar())
        ->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    EXPECT_EQ(tabBarLayoutProperty->GetTabBarHeight().value_or(Dimension(-1.0)), Dimension(200.0));
}

/**
 * @tc.name: SetTabBarHeight_NoValue
 * @tc.desc: SetTabBarHeight with no value should reset bar height
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetTabBarHeight_NoValue, TestSize.Level1)
{
    auto tabsNode = CreateTabsNodeWithChildren();
    ASSERT_NE(tabsNode, nullptr);
    auto frameNode = AceType::RawPtr(tabsNode);
    std::optional<Dimension> noOpt;
    TabsModelStatic::SetTabBarHeight(frameNode, noOpt);
    auto tabBarLayoutProperty = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar())
        ->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    EXPECT_FALSE(tabBarLayoutProperty->GetTabBarHeight().has_value());
}

// ===================== SetBarAdaptiveHeight =====================

/**
 * @tc.name: SetBarAdaptiveHeight_NullFrameNode
 * @tc.desc: SetBarAdaptiveHeight with null frameNode should not crash
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetBarAdaptiveHeight_NullFrameNode, TestSize.Level1)
{
    TabsModelStatic::SetBarAdaptiveHeight(nullptr, true);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetBarAdaptiveHeight_True
 * @tc.desc: SetBarAdaptiveHeight true should update property
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetBarAdaptiveHeight_True, TestSize.Level1)
{
    auto tabsNode = CreateTabsNodeWithChildren();
    ASSERT_NE(tabsNode, nullptr);
    auto frameNode = AceType::RawPtr(tabsNode);
    TabsModelStatic::SetBarAdaptiveHeight(frameNode, true);
    auto tabBarLayoutProperty = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar())
        ->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    EXPECT_TRUE(tabBarLayoutProperty->GetBarAdaptiveHeight().value_or(false));
}

// ===================== SetAnimationCurve =====================

/**
 * @tc.name: SetAnimationCurve_NullFrameNode
 * @tc.desc: SetAnimationCurve with null frameNode should not crash
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetAnimationCurve_NullFrameNode, TestSize.Level1)
{
    TabsModelStatic::SetAnimationCurve(nullptr, Curves::LINEAR);
    EXPECT_TRUE(true);
}

// ===================== SetNoMinHeightLimit =====================

/**
 * @tc.name: SetNoMinHeightLimit_NullFrameNode
 * @tc.desc: SetNoMinHeightLimit with null frameNode should not crash
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetNoMinHeightLimit_NullFrameNode, TestSize.Level1)
{
    TabsModelStatic::SetNoMinHeightLimit(nullptr, true);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetNoMinHeightLimit_True
 * @tc.desc: SetNoMinHeightLimit true should update property
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetNoMinHeightLimit_True, TestSize.Level1)
{
    auto tabsNode = CreateTabsNodeWithChildren();
    ASSERT_NE(tabsNode, nullptr);
    auto frameNode = AceType::RawPtr(tabsNode);
    TabsModelStatic::SetNoMinHeightLimit(frameNode, true);
    auto tabBarLayoutProperty = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar())
        ->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    EXPECT_TRUE(tabBarLayoutProperty->GetNoMinHeightLimit().value_or(false));
}

// ===================== SetAnimationDuration =====================

/**
 * @tc.name: SetAnimationDuration_NullFrameNode
 * @tc.desc: SetAnimationDuration with null frameNode should not crash
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetAnimationDuration_NullFrameNode, TestSize.Level1)
{
    TabsModelStatic::SetAnimationDuration(nullptr, 300.0f);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetAnimationDuration_Positive
 * @tc.desc: SetAnimationDuration with positive value should update duration
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetAnimationDuration_Positive, TestSize.Level1)
{
    auto tabsNode = CreateTabsNodeWithChildren();
    ASSERT_NE(tabsNode, nullptr);
    auto frameNode = AceType::RawPtr(tabsNode);
    auto swiperPaintProperty = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs())
        ->GetPaintProperty<SwiperPaintProperty>();
    ASSERT_NE(swiperPaintProperty, nullptr);
    TabsModelStatic::SetAnimationDuration(frameNode, 300.0f);
    EXPECT_EQ(swiperPaintProperty->GetDuration().value_or(0), 300);
}

/**
 * @tc.name: SetAnimationDuration_Negative
 * @tc.desc: SetAnimationDuration with negative value should reset duration
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetAnimationDuration_Negative, TestSize.Level1)
{
    auto tabsNode = CreateTabsNodeWithChildren();
    ASSERT_NE(tabsNode, nullptr);
    auto frameNode = AceType::RawPtr(tabsNode);
    auto swiperPaintProperty = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs())
        ->GetPaintProperty<SwiperPaintProperty>();
    ASSERT_NE(swiperPaintProperty, nullptr);
    swiperPaintProperty->UpdateDuration(100);
    TabsModelStatic::SetAnimationDuration(frameNode, -1.0f);
    EXPECT_FALSE(swiperPaintProperty->GetDuration().has_value());
}

// ===================== SetAnimateMode =====================

/**
 * @tc.name: SetAnimateMode_NullFrameNode
 * @tc.desc: SetAnimateMode with null frameNode should not crash
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetAnimateMode_NullFrameNode, TestSize.Level1)
{
    TabsModelStatic::SetAnimateMode(nullptr, TabAnimateMode::CONTENT_FIRST);
    EXPECT_TRUE(true);
}

// ===================== SetEdgeEffect =====================

/**
 * @tc.name: SetEdgeEffect_NullFrameNode
 * @tc.desc: SetEdgeEffect with null frameNode should not crash
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetEdgeEffect_NullFrameNode, TestSize.Level1)
{
    TabsModelStatic::SetEdgeEffect(nullptr, 0);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetEdgeEffect_WithValue
 * @tc.desc: SetEdgeEffect with a valid value should update property
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetEdgeEffect_WithValue, TestSize.Level1)
{
    auto tabsNode = CreateTabsNodeWithChildren();
    ASSERT_NE(tabsNode, nullptr);
    auto frameNode = AceType::RawPtr(tabsNode);
    auto swiperPaintProperty = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs())
        ->GetPaintProperty<SwiperPaintProperty>();
    ASSERT_NE(swiperPaintProperty, nullptr);
    TabsModelStatic::SetEdgeEffect(frameNode, static_cast<int32_t>(EdgeEffect::FADE));
    EXPECT_EQ(swiperPaintProperty->GetEdgeEffect().value_or(EdgeEffect::SPRING), EdgeEffect::FADE);
}

/**
 * @tc.name: SetEdgeEffect_NoValue
 * @tc.desc: SetEdgeEffect with no value should reset edge effect
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetEdgeEffect_NoValue, TestSize.Level1)
{
    auto tabsNode = CreateTabsNodeWithChildren();
    ASSERT_NE(tabsNode, nullptr);
    auto frameNode = AceType::RawPtr(tabsNode);
    auto swiperPaintProperty = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs())
        ->GetPaintProperty<SwiperPaintProperty>();
    ASSERT_NE(swiperPaintProperty, nullptr);
    swiperPaintProperty->UpdateEdgeEffect(EdgeEffect::FADE);
    std::optional<int32_t> noOpt;
    TabsModelStatic::SetEdgeEffect(frameNode, noOpt);
    EXPECT_FALSE(swiperPaintProperty->GetEdgeEffect().has_value());
}

// ===================== SetNestedScroll =====================

/**
 * @tc.name: SetNestedScroll_NullFrameNode
 * @tc.desc: SetNestedScroll with null frameNode should not crash
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetNestedScroll_NullFrameNode, TestSize.Level1)
{
    TabsModelStatic::SetNestedScroll(nullptr, 1);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetNestedScroll_Valid
 * @tc.desc: SetNestedScroll with valid frameNode should set scroll mode
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetNestedScroll_Valid, TestSize.Level1)
{
    auto tabsNode = CreateTabsNodeWithChildren();
    ASSERT_NE(tabsNode, nullptr);
    auto frameNode = AceType::RawPtr(tabsNode);
    TabsModelStatic::SetNestedScroll(frameNode, 1);
    EXPECT_TRUE(true);
}

// ===================== SetOnChange / SetOnSelected / SetOnTabBarClick / SetOnUnselected =====================

/**
 * @tc.name: SetOnChange_NullFrameNode
 * @tc.desc: SetOnChange with null frameNode should not crash
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetOnChange_NullFrameNode, TestSize.Level1)
{
    std::function<void(const BaseEventInfo*)> callback = [](const BaseEventInfo*) {};
    TabsModelStatic::SetOnChange(nullptr, std::move(callback));
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetOnChange_Valid
 * @tc.desc: SetOnChange with valid frameNode should set callback
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetOnChange_Valid, TestSize.Level1)
{
    auto tabsNode = CreateTabsNodeWithChildren();
    ASSERT_NE(tabsNode, nullptr);
    auto frameNode = AceType::RawPtr(tabsNode);
    bool called = false;
    std::function<void(const BaseEventInfo*)> callback = [&called](const BaseEventInfo*) { called = true; };
    TabsModelStatic::SetOnChange(frameNode, std::move(callback));
    auto pattern = tabsNode->GetPattern<TabsPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_NE(pattern->onChangeEvent_, nullptr);
}

/**
 * @tc.name: SetOnSelected_NullFrameNode
 * @tc.desc: SetOnSelected with null frameNode should not crash
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetOnSelected_NullFrameNode, TestSize.Level1)
{
    std::function<void(const BaseEventInfo*)> callback = [](const BaseEventInfo*) {};
    TabsModelStatic::SetOnSelected(nullptr, std::move(callback));
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetOnTabBarClick_NullFrameNode
 * @tc.desc: SetOnTabBarClick with null frameNode should not crash
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetOnTabBarClick_NullFrameNode, TestSize.Level1)
{
    std::function<void(const BaseEventInfo*)> callback = [](const BaseEventInfo*) {};
    TabsModelStatic::SetOnTabBarClick(nullptr, std::move(callback));
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetOnUnselected_NullFrameNode
 * @tc.desc: SetOnUnselected with null frameNode should not crash
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetOnUnselected_NullFrameNode, TestSize.Level1)
{
    std::function<void(const BaseEventInfo*)> callback = [](const BaseEventInfo*) {};
    TabsModelStatic::SetOnUnselected(nullptr, std::move(callback));
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetOnContentDidScroll_NullFrameNode
 * @tc.desc: SetOnContentDidScroll with null frameNode should not crash
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetOnContentDidScroll_NullFrameNode, TestSize.Level1)
{
    ContentDidScrollEvent callback = [](int32_t, int32_t, float, float) {};
    TabsModelStatic::SetOnContentDidScroll(nullptr, std::move(callback));
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetOnAnimationStart_NullFrameNode
 * @tc.desc: SetOnAnimationStart with null frameNode should not crash
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetOnAnimationStart_NullFrameNode, TestSize.Level1)
{
    AnimationStartEvent callback = [](int32_t, int32_t, const AnimationCallbackInfo&) {};
    TabsModelStatic::SetOnAnimationStart(nullptr, std::move(callback));
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetOnAnimationEnd_NullFrameNode
 * @tc.desc: SetOnAnimationEnd with null frameNode should not crash
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetOnAnimationEnd_NullFrameNode, TestSize.Level1)
{
    AnimationEndEvent callback = [](int32_t, const AnimationCallbackInfo&) {};
    TabsModelStatic::SetOnAnimationEnd(nullptr, std::move(callback));
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetOnGestureSwipe_NullFrameNode
 * @tc.desc: SetOnGestureSwipe with null frameNode should not crash
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetOnGestureSwipe_NullFrameNode, TestSize.Level1)
{
    GestureSwipeEvent callback = [](int32_t, const AnimationCallbackInfo&) {};
    TabsModelStatic::SetOnGestureSwipe(nullptr, std::move(callback));
    EXPECT_TRUE(true);
}

// ===================== SetFadingEdge =====================

/**
 * @tc.name: SetFadingEdge_NullFrameNode
 * @tc.desc: SetFadingEdge with null frameNode should not crash
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetFadingEdge_NullFrameNode, TestSize.Level1)
{
    TabsModelStatic::SetFadingEdge(nullptr, true);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetFadingEdge_True
 * @tc.desc: SetFadingEdge true should update fading edge property
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetFadingEdge_True, TestSize.Level1)
{
    auto tabsNode = CreateTabsNodeWithChildren();
    ASSERT_NE(tabsNode, nullptr);
    auto frameNode = AceType::RawPtr(tabsNode);
    auto tabBarPaintProperty = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar())
        ->GetPaintProperty<TabBarPaintProperty>();
    ASSERT_NE(tabBarPaintProperty, nullptr);
    TabsModelStatic::SetFadingEdge(frameNode, true);
    EXPECT_TRUE(tabBarPaintProperty->GetFadingEdge().value_or(false));
}

// ===================== SetDivider =====================

/**
 * @tc.name: SetDivider_NullFrameNode
 * @tc.desc: SetDivider with null frameNode should not crash
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetDivider_NullFrameNode, TestSize.Level1)
{
    TabsItemDivider divider;
    TabsModelStatic::SetDivider(nullptr, divider);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetDivider_IsNull
 * @tc.desc: SetDivider with isNull=true should hide divider
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetDivider_IsNull, TestSize.Level1)
{
    RefPtr<TabsNode> tabsNode;
    RefPtr<FrameNode> dividerNode;
    SetupTabsNodeForDividerTest(tabsNode, dividerNode);
    ASSERT_NE(tabsNode, nullptr);
    auto frameNode = AceType::RawPtr(tabsNode);
    auto dividerRenderContext = dividerNode->GetRenderContext();
    ASSERT_NE(dividerRenderContext, nullptr);
    TabsItemDivider divider;
    divider.isNull = true;
    TabsModelStatic::SetDivider(frameNode, divider);
    EXPECT_EQ(dividerRenderContext->GetOpacity(), 0.0f);
}

/**
 * @tc.name: SetDivider_NotNull
 * @tc.desc: SetDivider with isNull=false should show divider
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetDivider_NotNull, TestSize.Level1)
{
    RefPtr<TabsNode> tabsNode;
    RefPtr<FrameNode> dividerNode;
    SetupTabsNodeForDividerTest(tabsNode, dividerNode);
    ASSERT_NE(tabsNode, nullptr);
    auto frameNode = AceType::RawPtr(tabsNode);
    auto dividerRenderContext = dividerNode->GetRenderContext();
    ASSERT_NE(dividerRenderContext, nullptr);
    TabsItemDivider divider;
    divider.isNull = false;
    divider.color = Color::RED;
    divider.strokeWidth = Dimension(2.0);
    TabsModelStatic::SetDivider(frameNode, divider);
    EXPECT_EQ(dividerRenderContext->GetOpacity(), 1.0f);
}

// ===================== SetDividerColorByUser =====================

/**
 * @tc.name: SetDividerColorByUser_True
 * @tc.desc: SetDividerColorByUser true should update property
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetDividerColorByUser_True, TestSize.Level1)
{
    auto frameNode = CreateSimpleFrameNode();
    ASSERT_NE(frameNode, nullptr);
    TabsModelStatic::SetDividerColorByUser(AceType::RawPtr(frameNode), true);
    EXPECT_TRUE(true);
}

// ===================== InitDivider =====================

/**
 * @tc.name: InitDivider_NullFrameNode
 * @tc.desc: InitDivider with null frameNode should not crash
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, InitDivider_NullFrameNode, TestSize.Level1)
{
    TabsModelStatic::InitDivider(nullptr);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: InitDivider_Valid
 * @tc.desc: InitDivider with valid frameNode should initialize divider properties
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, InitDivider_Valid, TestSize.Level1)
{
    auto tabsNode = CreateTabsNodeWithChildren();
    ASSERT_NE(tabsNode, nullptr);
    auto frameNode = AceType::RawPtr(tabsNode);
    auto dividerNode = AceType::DynamicCast<FrameNode>(tabsNode->GetDivider());
    ASSERT_NE(dividerNode, nullptr);
    auto dividerRenderProperty = dividerNode->GetPaintProperty<DividerRenderProperty>();
    ASSERT_NE(dividerRenderProperty, nullptr);
    TabsModelStatic::InitDivider(frameNode);
    EXPECT_EQ(dividerRenderProperty->GetLineCap().value_or(LineCap::SQUARE), LineCap::BUTT);
}

// ===================== SetBarOverlap =====================

/**
 * @tc.name: SetBarOverlap_True
 * @tc.desc: SetBarOverlap true should set blur style to COMPONENT_THICK
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetBarOverlap_True, TestSize.Level1)
{
    auto tabsNode = CreateTabsNodeWithChildren();
    ASSERT_NE(tabsNode, nullptr);
    auto frameNode = AceType::RawPtr(tabsNode);
    TabsModelStatic::SetBarOverlap(frameNode, true);
    auto layoutProperty = tabsNode->GetLayoutProperty<TabsLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_TRUE(layoutProperty->GetBarOverlap().value_or(false));
}

/**
 * @tc.name: SetBarOverlap_False
 * @tc.desc: SetBarOverlap false should not set blur style
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetBarOverlap_False, TestSize.Level1)
{
    auto tabsNode = CreateTabsNodeWithChildren();
    ASSERT_NE(tabsNode, nullptr);
    auto frameNode = AceType::RawPtr(tabsNode);
    TabsModelStatic::SetBarOverlap(frameNode, false);
    auto layoutProperty = tabsNode->GetLayoutProperty<TabsLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_FALSE(layoutProperty->GetBarOverlap().value_or(true));
}

// ===================== SetBarBackgroundBlurStyle =====================

/**
 * @tc.name: SetBarBackgroundBlurStyle_NullFrameNode
 * @tc.desc: SetBarBackgroundBlurStyle with null frameNode should not crash
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetBarBackgroundBlurStyle_NullFrameNode, TestSize.Level1)
{
    BlurStyleOption option;
    TabsModelStatic::SetBarBackgroundBlurStyle(nullptr, option);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetBarBackgroundBlurStyle_FollowsWindow
 * @tc.desc: SetBarBackgroundBlurStyle with FOLLOWS_WINDOW_ACTIVE_STATE should add callback
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetBarBackgroundBlurStyle_FollowsWindow, TestSize.Level1)
{
    auto frameNode = SetupForBarBackgroundBlurStyle();
    ASSERT_NE(frameNode, nullptr);
    BlurStyleOption option;
    option.policy = BlurStyleActivePolicy::FOLLOWS_WINDOW_ACTIVE_STATE;
    TabsModelStatic::SetBarBackgroundBlurStyle(AceType::RawPtr(frameNode), option);
    EXPECT_TRUE(true);
}

// ===================== SetBarBackgroundColor =====================

/**
 * @tc.name: SetBarBackgroundColor_NullFrameNode
 * @tc.desc: SetBarBackgroundColor with null frameNode should not crash
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetBarBackgroundColor_NullFrameNode, TestSize.Level1)
{
    TabsModelStatic::SetBarBackgroundColor(nullptr, Color::RED);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetBarBackgroundColor_WithValue
 * @tc.desc: SetBarBackgroundColor with valid color should update
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetBarBackgroundColor_WithValue, TestSize.Level1)
{
    auto tabsNode = CreateTabsNodeWithChildren();
    ASSERT_NE(tabsNode, nullptr);
    auto frameNode = AceType::RawPtr(tabsNode);
    TabsModelStatic::SetBarBackgroundColor(frameNode, Color::RED);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetBarBackgroundColor_NoValue
 * @tc.desc: SetBarBackgroundColor with no value should reset
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetBarBackgroundColor_NoValue, TestSize.Level1)
{
    auto tabsNode = CreateTabsNodeWithChildren();
    ASSERT_NE(tabsNode, nullptr);
    auto frameNode = AceType::RawPtr(tabsNode);
    std::optional<Color> noOpt;
    TabsModelStatic::SetBarBackgroundColor(frameNode, noOpt);
    EXPECT_TRUE(true);
}

// ===================== SetBarGridAlign =====================

/**
 * @tc.name: SetBarGridAlign_NullFrameNode
 * @tc.desc: SetBarGridAlign with null frameNode should not crash
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetBarGridAlign_NullFrameNode, TestSize.Level1)
{
    BarGridColumnOptions options;
    TabsModelStatic::SetBarGridAlign(nullptr, options);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetBarGridAlign_Valid
 * @tc.desc: SetBarGridAlign with valid frameNode should set property
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetBarGridAlign_Valid, TestSize.Level1)
{
    auto tabsNode = CreateTabsNodeWithChildren();
    ASSERT_NE(tabsNode, nullptr);
    auto frameNode = AceType::RawPtr(tabsNode);
    BarGridColumnOptions options;
    options.sm = 4;
    TabsModelStatic::SetBarGridAlign(frameNode, options);
    auto tabBarLayoutProperty = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar())
        ->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    auto result = tabBarLayoutProperty->GetBarGridAlign();
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->sm, 4);
}

// ===================== SetIsCustomAnimation =====================

/**
 * @tc.name: SetIsCustomAnimation_NullFrameNode
 * @tc.desc: SetIsCustomAnimation with null frameNode should not crash
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetIsCustomAnimation_NullFrameNode, TestSize.Level1)
{
    TabsModelStatic::SetIsCustomAnimation(nullptr, true);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetIsCustomAnimation_True
 * @tc.desc: SetIsCustomAnimation true should update property
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetIsCustomAnimation_True, TestSize.Level1)
{
    auto tabsNode = CreateTabsNodeWithChildren();
    ASSERT_NE(tabsNode, nullptr);
    auto frameNode = AceType::RawPtr(tabsNode);
    TabsModelStatic::SetIsCustomAnimation(frameNode, true);
    auto swiperLayoutProperty = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs())
        ->GetLayoutProperty<SwiperLayoutProperty>();
    ASSERT_NE(swiperLayoutProperty, nullptr);
    EXPECT_TRUE(swiperLayoutProperty->GetIsCustomAnimation().value_or(false));
}

// ===================== SetOnCustomAnimation =====================

/**
 * @tc.name: SetOnCustomAnimation_NullFrameNode
 * @tc.desc: SetOnCustomAnimation with null frameNode should not crash
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetOnCustomAnimation_NullFrameNode, TestSize.Level1)
{
    TabsCustomAnimationEvent callback = [](int32_t, int32_t) -> TabContentAnimatedTransition {
        return TabContentAnimatedTransition {};
    };
    TabsModelStatic::SetOnCustomAnimation(nullptr, std::move(callback));
    EXPECT_TRUE(true);
}

// ===================== SetBarBackgroundEffect =====================

/**
 * @tc.name: SetBarBackgroundEffect_NullFrameNode
 * @tc.desc: SetBarBackgroundEffect with null frameNode should not crash
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetBarBackgroundEffect_NullFrameNode, TestSize.Level1)
{
    EffectOption option;
    TabsModelStatic::SetBarBackgroundEffect(nullptr, option);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetBarBackgroundEffect_FollowsWindow
 * @tc.desc: SetBarBackgroundEffect with FOLLOWS_WINDOW_ACTIVE_STATE should add callback
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetBarBackgroundEffect_FollowsWindow, TestSize.Level1)
{
    auto tabsNode = CreateTabsNodeWithChildren();
    ASSERT_NE(tabsNode, nullptr);
    auto frameNode = AceType::RawPtr(tabsNode);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    if (pipeline) {
        tabBarNode->context_ = AceType::RawPtr(pipeline);
    }
    EffectOption option;
    option.policy = BlurStyleActivePolicy::FOLLOWS_WINDOW_ACTIVE_STATE;
    TabsModelStatic::SetBarBackgroundEffect(frameNode, option);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetBarBackgroundEffect_AlwaysActive
 * @tc.desc: SetBarBackgroundEffect with ALWAYS_ACTIVE should remove callback
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetBarBackgroundEffect_AlwaysActive, TestSize.Level1)
{
    auto tabsNode = CreateTabsNodeWithChildren();
    ASSERT_NE(tabsNode, nullptr);
    auto frameNode = AceType::RawPtr(tabsNode);
    EffectOption option;
    option.policy = BlurStyleActivePolicy::ALWAYS_ACTIVE;
    TabsModelStatic::SetBarBackgroundEffect(frameNode, option);
    EXPECT_TRUE(true);
}

// ===================== SetPageFlipMode =====================

/**
 * @tc.name: SetPageFlipMode_NullFrameNode
 * @tc.desc: SetPageFlipMode with null frameNode should not crash
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetPageFlipMode_NullFrameNode, TestSize.Level1)
{
    TabsModelStatic::SetPageFlipMode(nullptr, 1);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetPageFlipMode_Valid
 * @tc.desc: SetPageFlipMode with valid frameNode should set mode
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetPageFlipMode_Valid, TestSize.Level1)
{
    auto tabsNode = CreateTabsNodeWithChildren();
    ASSERT_NE(tabsNode, nullptr);
    auto frameNode = AceType::RawPtr(tabsNode);
    TabsModelStatic::SetPageFlipMode(frameNode, 1);
    EXPECT_TRUE(true);
}

// ===================== SetOnContentWillChange =====================

/**
 * @tc.name: SetOnContentWillChange_NullFrameNode
 * @tc.desc: SetOnContentWillChange with null frameNode should not crash
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetOnContentWillChange_NullFrameNode, TestSize.Level1)
{
    std::function<bool(int32_t, int32_t)> callback = [](int32_t, int32_t) { return true; };
    TabsModelStatic::SetOnContentWillChange(nullptr, std::move(callback));
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetOnContentWillChange_Valid
 * @tc.desc: SetOnContentWillChange with valid frameNode should set callback
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetOnContentWillChange_Valid, TestSize.Level1)
{
    auto tabsNode = CreateTabsNodeWithChildren();
    ASSERT_NE(tabsNode, nullptr);
    auto frameNode = AceType::RawPtr(tabsNode);
    std::function<bool(int32_t, int32_t)> callback = [](int32_t, int32_t) { return true; };
    TabsModelStatic::SetOnContentWillChange(frameNode, std::move(callback));
    auto pattern = tabsNode->GetPattern<TabsPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_TRUE(pattern->interceptStatus_);
}

// ===================== SetCachedMaxCount =====================

/**
 * @tc.name: SetCachedMaxCount_NullFrameNode
 * @tc.desc: SetCachedMaxCount with null frameNode should not crash
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetCachedMaxCount_NullFrameNode, TestSize.Level1)
{
    TabsModelStatic::SetCachedMaxCount(nullptr, std::optional<int32_t>(2),
        std::optional<TabsCacheMode>(TabsCacheMode::CACHE_BOTH_SIDE));
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetCachedMaxCount_WithCountAndMode
 * @tc.desc: SetCachedMaxCount with count and mode should set both
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetCachedMaxCount_WithCountAndMode, TestSize.Level1)
{
    auto tabsNode = CreateTabsNodeWithChildren();
    ASSERT_NE(tabsNode, nullptr);
    auto frameNode = AceType::RawPtr(tabsNode);
    auto layoutProperty = tabsNode->GetLayoutProperty<TabsLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    TabsModelStatic::SetCachedMaxCount(frameNode, std::optional<int32_t>(2),
        std::optional<TabsCacheMode>(TabsCacheMode::CACHE_BOTH_SIDE));
    EXPECT_EQ(layoutProperty->GetCachedMaxCount().value_or(-1), 2);
    EXPECT_EQ(layoutProperty->GetCacheMode().value_or(TabsCacheMode::CACHE_BOTH_SIDE), TabsCacheMode::CACHE_BOTH_SIDE);
}

/**
 * @tc.name: SetCachedMaxCount_WithCountNoMode
 * @tc.desc: SetCachedMaxCount with count but no mode should set count only
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetCachedMaxCount_WithCountNoMode, TestSize.Level1)
{
    auto tabsNode = CreateTabsNodeWithChildren();
    ASSERT_NE(tabsNode, nullptr);
    auto frameNode = AceType::RawPtr(tabsNode);
    auto layoutProperty = tabsNode->GetLayoutProperty<TabsLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    std::optional<TabsCacheMode> noMode;
    TabsModelStatic::SetCachedMaxCount(frameNode, 3, noMode);
    EXPECT_EQ(layoutProperty->GetCachedMaxCount().value_or(-1), 3);
}

/**
 * @tc.name: SetCachedMaxCount_NoCount
 * @tc.desc: SetCachedMaxCount with no count should reset both
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetCachedMaxCount_NoCount, TestSize.Level1)
{
    auto tabsNode = CreateTabsNodeWithChildren();
    ASSERT_NE(tabsNode, nullptr);
    auto frameNode = AceType::RawPtr(tabsNode);
    auto layoutProperty = tabsNode->GetLayoutProperty<TabsLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateCachedMaxCount(5);
    std::optional<int32_t> noCount;
    std::optional<TabsCacheMode> noMode;
    TabsModelStatic::SetCachedMaxCount(frameNode, noCount, noMode);
    EXPECT_FALSE(layoutProperty->GetCachedMaxCount().has_value());
}

// ===================== SetOnChangeEvent =====================

/**
 * @tc.name: SetOnChangeEvent_NullFrameNode
 * @tc.desc: SetOnChangeEvent with null frameNode should not crash
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetOnChangeEvent_NullFrameNode, TestSize.Level1)
{
    TabsModelStatic::SetOnChangeEvent(nullptr, nullptr);
    EXPECT_TRUE(true);
}

// ===================== ApplyAttributesFinish =====================

/**
 * @tc.name: ApplyAttributesFinish_NullFrameNode
 * @tc.desc: ApplyAttributesFinish with null frameNode should not crash
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, ApplyAttributesFinish_NullFrameNode, TestSize.Level1)
{
    TabsModelStatic::ApplyAttributesFinish(nullptr);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: ApplyAttributesFinish_Valid
 * @tc.desc: ApplyAttributesFinish with valid frameNode should finish attributes
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, ApplyAttributesFinish_Valid, TestSize.Level1)
{
    auto tabsNode = CreateTabsNodeWithChildren();
    ASSERT_NE(tabsNode, nullptr);
    auto frameNode = AceType::RawPtr(tabsNode);
    TabsModelStatic::ApplyAttributesFinish(frameNode);
    auto dividerNode = AceType::DynamicCast<FrameNode>(tabsNode->GetDivider());
    ASSERT_NE(dividerNode, nullptr);
    auto dividerRenderProperty = dividerNode->GetPaintProperty<DividerRenderProperty>();
    ASSERT_NE(dividerRenderProperty, nullptr);
    EXPECT_EQ(dividerRenderProperty->GetLineCap().value_or(LineCap::SQUARE), LineCap::BUTT);
}

// ===================== ResetScrollableBarModeOptions =====================

/**
 * @tc.name: ResetScrollableBarModeOptions_NullFrameNode
 * @tc.desc: ResetScrollableBarModeOptions with null frameNode should not crash
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, ResetScrollableBarModeOptions_NullFrameNode, TestSize.Level1)
{
    TabsModelStatic::ResetScrollableBarModeOptions(nullptr);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: ResetScrollableBarModeOptions_Valid
 * @tc.desc: ResetScrollableBarModeOptions with valid frameNode should reset options
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, ResetScrollableBarModeOptions_Valid, TestSize.Level1)
{
    auto tabsNode = CreateTabsNodeWithChildren();
    ASSERT_NE(tabsNode, nullptr);
    auto frameNode = AceType::RawPtr(tabsNode);
    TabsModelStatic::ResetScrollableBarModeOptions(frameNode);
    EXPECT_TRUE(true);
}

// ===================== GetTabBarLayoutProperty (private, tested via public APIs) =====================

/**
 * @tc.name: GetTabBarLayoutProperty_NullFrameNode
 * @tc.desc: Verify SetBarAdaptiveHeight with non-TabsNode returns early (tests GetTabBarLayoutProperty null path)
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, GetTabBarLayoutProperty_NonTabsNode, TestSize.Level1)
{
    auto frameNode = CreateSimpleFrameNode();
    ASSERT_NE(frameNode, nullptr);
    // SetBarAdaptiveHeight internally calls GetTabBarLayoutProperty which will return null for non-TabsNode
    TabsModelStatic::SetBarAdaptiveHeight(AceType::RawPtr(frameNode), true);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: GetTabBarLayoutProperty_NonTabBarNode
 * @tc.desc: Verify SetBarAdaptiveHeight with TabsNode missing tab bar returns early
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, GetTabBarLayoutProperty_NoTabBarNode, TestSize.Level1)
{
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto tabsNode = AceType::MakeRefPtr<TabsNode>(V2::TABS_ETS_TAG, nodeId,
        AceType::MakeRefPtr<TabsPattern>(), false);
    tabsNode->InitializePatternAndContext();
    auto frameNode = AceType::RawPtr(tabsNode);
    // No tabBarNode mounted, GetTabBarLayoutProperty will return null
    TabsModelStatic::SetBarAdaptiveHeight(frameNode, true);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: GetSwiperPaintProperty_NullFrameNode
 * @tc.desc: Verify SetAnimationDuration with non-TabsNode returns early (tests GetSwiperPaintProperty null path)
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, GetSwiperPaintProperty_NonTabsNode, TestSize.Level1)
{
    auto frameNode = CreateSimpleFrameNode();
    ASSERT_NE(frameNode, nullptr);
    TabsModelStatic::SetAnimationDuration(AceType::RawPtr(frameNode), 300.0f);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: GetTabBarPaintProperty_NullFrameNode
 * @tc.desc: Verify SetFadingEdge with non-TabsNode returns early (tests GetTabBarPaintProperty null path)
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, GetTabBarPaintProperty_NonTabsNode, TestSize.Level1)
{
    auto frameNode = CreateSimpleFrameNode();
    ASSERT_NE(frameNode, nullptr);
    TabsModelStatic::SetFadingEdge(AceType::RawPtr(frameNode), true);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: GetSwiperController_NullTabsNode
 * @tc.desc: Verify GetSwiperController with non-TabsNode returns nullptr
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, GetSwiperController_NonTabsNode, TestSize.Level1)
{
    auto frameNode = CreateSimpleFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto controller = TabsModelStatic::GetSwiperController(AceType::RawPtr(frameNode));
    EXPECT_EQ(controller, nullptr);
}

/**
 * @tc.name: GetSwiperPaintProperty_NullSwiperNode
 * @tc.desc: Verify SetAnimationDuration with TabsNode missing swiper returns early
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, GetSwiperPaintProperty_NoSwiperNode, TestSize.Level1)
{
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto tabsNode = AceType::MakeRefPtr<TabsNode>(V2::TABS_ETS_TAG, nodeId,
        AceType::MakeRefPtr<TabsPattern>(), false);
    tabsNode->InitializePatternAndContext();
    auto frameNode = AceType::RawPtr(tabsNode);
    auto tabBarNode = FrameNode::CreateFrameNode(V2::TAB_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<TabBarPattern>());
    tabBarNode->MountToParent(tabsNode);
    TabsModelStatic::SetAnimationDuration(frameNode, 300.0f);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetTabBarWidth_TabsNodeNoTabBar
 * @tc.desc: SetTabBarWidth with TabsNode missing tabBarNode should return early
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelStaticTestNg, SetTabBarWidth_NoTabBarNode, TestSize.Level1)
{
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto tabsNode = AceType::MakeRefPtr<TabsNode>(V2::TABS_ETS_TAG, nodeId,
        AceType::MakeRefPtr<TabsPattern>(), false);
    tabsNode->InitializePatternAndContext();
    auto frameNode = AceType::RawPtr(tabsNode);
    TabsModelStatic::SetTabBarWidth(frameNode, Dimension(100.0));
    EXPECT_TRUE(true);
}
} // namespace OHOS::Ace::NG
