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

#include <cstddef>
#include <utility>

#include "gtest/gtest.h"

#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/swiper/swiper_event_hub.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/pattern/tabs/tab_content_model_ng.h"
#include "core/components_ng/pattern/tabs/tab_content_pattern.h"
#include "core/components_ng/pattern/tabs/tabs_model_ng.h"
#include "core/components_ng/pattern/tabs/tabs_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr Dimension TAB_BAR_WIDTH(50);
constexpr Dimension TAB_BAR_HEIGHT(20);
constexpr float ANIMATION_DURATION = 200.0f;
constexpr bool IS_VERTICAL = true;
constexpr bool SCROLLABLE = true;
constexpr char DEFAULT_TAB_BAR_NAME[] = "TabBar";
constexpr float SET_ANIMATION_DURATION = 500.0f;
} // namespace
class TabsPatternTestNg : public testing::Test {
public:
    void SetUp() override;
    void TearDown() override;
};

void TabsPatternTestNg::SetUp() {}

void TabsPatternTestNg::TearDown() {}

/**
 * @tc.name: TabsTest001
 * @tc.desc: Test setting of Tabs.
 * @tc.type: FUNC
 */
HWTEST_F(TabsPatternTestNg, TabsTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */
    TabsModelNG instance;
    instance.Create(BarPosition::START, 1, nullptr, nullptr);
    /**
     * @tc.steps: step2. create frameNode to get layout properties.
     * @tc.expected: step2. related function is called.
     */
    auto tabsFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    /**
     * @tc.steps: step3. get the properties of all settings.
     * @tc.expected: step3. check whether the properties is correct.
     */
    EXPECT_FALSE(tabsFrameNode == nullptr);
    EXPECT_EQ(tabsFrameNode->GetTag(), V2::TABS_ETS_TAG);
    auto tabsPattern = tabsFrameNode->GetPattern<TabsPattern>();
    EXPECT_FALSE(tabsPattern == nullptr);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildren().back());
    EXPECT_FALSE(swiperNode == nullptr);
    EXPECT_EQ(swiperNode->GetTag(), V2::SWIPER_ETS_TAG);
    auto swiperPaintProperty = swiperNode->GetPaintProperty<SwiperPaintProperty>();
    EXPECT_FALSE(swiperPaintProperty == nullptr);
    auto loop = swiperPaintProperty->GetLoop();
    EXPECT_EQ(loop, false);
    auto edgeEffect = swiperPaintProperty->GetEdgeEffect();
    EXPECT_EQ(edgeEffect, EdgeEffect::SPRING);
    auto swiperLayoutProperty = swiperNode->GetLayoutProperty<SwiperLayoutProperty>();
    EXPECT_FALSE(swiperLayoutProperty == nullptr);
    auto cacheCount = swiperLayoutProperty->GetCachedCount();
    EXPECT_EQ(cacheCount, 0);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    EXPECT_FALSE(swiperPattern == nullptr);
    auto swiperController = swiperPattern->GetSwiperController();
    EXPECT_FALSE(swiperController == nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildren().front());
    EXPECT_FALSE(tabBarNode == nullptr);
    EXPECT_EQ(tabBarNode->GetTag(), V2::TAB_BAR_ETS_TAG);
    auto tabsLayoutProperty = tabsFrameNode->GetLayoutProperty<TabsLayoutProperty>();
    EXPECT_FALSE(tabsLayoutProperty == nullptr);
    EXPECT_EQ(tabsLayoutProperty->GetTabBarPosition(), BarPosition::START);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    EXPECT_FALSE(tabBarLayoutProperty == nullptr);
    EXPECT_EQ(swiperLayoutProperty->GetIndex(), 1);
}

/**
 * @tc.name: TabsTest002
 * @tc.desc: Test properties set of tabs.
 * @tc.type: FUNC
 */
HWTEST_F(TabsPatternTestNg, TabsTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */
    TabsModelNG instance;
    instance.Create(BarPosition::START, 1, nullptr, nullptr);
    instance.SetTabBarPosition(BarPosition::END);
    instance.SetTabBarMode(TabBarMode::FIXED);
    instance.SetTabBarWidth(TAB_BAR_WIDTH);
    instance.SetTabBarHeight(TAB_BAR_HEIGHT);
    instance.SetIsVertical(IS_VERTICAL);
    instance.SetIndex(2);
    instance.SetScrollable(SCROLLABLE);
    instance.SetAnimationDuration(ANIMATION_DURATION);
    /**
     * @tc.steps: step2. create frameNode to get layout properties.
     * @tc.expected: step2. related function is called.
     */
    auto tabsFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(tabsFrameNode == nullptr);
    EXPECT_EQ(tabsFrameNode->GetTag(), V2::TABS_ETS_TAG);
    /**
     * @tc.steps: step3. get the properties of all settings.
     * @tc.expected: step3. check whether the properties is correct.
     */
    auto tabsLayoutProperty = tabsFrameNode->GetLayoutProperty<TabsLayoutProperty>();
    EXPECT_FALSE(tabsLayoutProperty == nullptr);
    EXPECT_EQ(tabsLayoutProperty->GetTabBarPosition(), BarPosition::END);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildren().front());
    EXPECT_FALSE(tabBarNode == nullptr);
    EXPECT_EQ(tabBarNode->GetTag(), V2::TAB_BAR_ETS_TAG);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    EXPECT_FALSE(tabBarLayoutProperty == nullptr);
    EXPECT_EQ(tabBarLayoutProperty->GetTabBarMode(), TabBarMode::FIXED);
    EXPECT_EQ(tabBarLayoutProperty->GetTabBarWidth(), TAB_BAR_WIDTH);
    EXPECT_EQ(tabBarLayoutProperty->GetTabBarHeight(), TAB_BAR_HEIGHT);
    auto axis = IS_VERTICAL ? Axis::VERTICAL : Axis::HORIZONTAL;
    EXPECT_EQ(tabBarLayoutProperty->GetAxis(), axis);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildren().back());
    EXPECT_FALSE(swiperNode == nullptr);
    EXPECT_EQ(swiperNode->GetTag(), V2::SWIPER_ETS_TAG);
    auto swiperLayoutProperty = swiperNode->GetLayoutProperty<SwiperLayoutProperty>();
    EXPECT_FALSE(swiperLayoutProperty == nullptr);
    EXPECT_EQ(swiperLayoutProperty->GetDirection(), axis);
    EXPECT_EQ(swiperLayoutProperty->GetIndex(), 2);
    auto swiperPaintProperty = swiperNode->GetPaintProperty<SwiperPaintProperty>();
    EXPECT_FALSE(swiperPaintProperty == nullptr);
    EXPECT_EQ(swiperPaintProperty->GetDisableSwipe(), !SCROLLABLE);
    EXPECT_EQ(swiperPaintProperty->GetDuration(), ANIMATION_DURATION);
}

/**
 * @tc.name: TabsTest003
 * @tc.desc: Test create of tab content.
 * @tc.type: FUNC
 */
HWTEST_F(TabsPatternTestNg, TabsTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */
    TabContentModelNG instance;
    auto func = []() {};
    instance.Create(func);
    /**
     * @tc.steps: step2. create frameNode to get layout properties.
     * @tc.expected: step2. related function is called.
     */
    auto tabContentFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    /**
     * @tc.steps: step3. get the properties of all settings.
     * @tc.expected: step3. check whether the properties is correct.
     */
    EXPECT_FALSE(tabContentFrameNode == nullptr);
    EXPECT_EQ(tabContentFrameNode->GetTag(), V2::TAB_CONTENT_ITEM_ETS_TAG);
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();
    EXPECT_FALSE(tabContentPattern == nullptr);
    const auto& tabBarParam = tabContentPattern->GetTabBarParam();
    EXPECT_EQ(tabBarParam.GetText(), DEFAULT_TAB_BAR_NAME);
    EXPECT_EQ(tabBarParam.GetIcon(), "");
    EXPECT_EQ(tabBarParam.HasBuilder(), false);

    auto tabContentLayoutProperty = tabContentFrameNode->GetLayoutProperty<TabContentLayoutProperty>();
    EXPECT_FALSE(tabContentLayoutProperty == nullptr);
    EXPECT_EQ(tabContentLayoutProperty->GetText(), DEFAULT_TAB_BAR_NAME);
}

/**
 * @tc.name: TabsTest004
 * @tc.desc: Test set of tabs pattern.
 * @tc.type: FUNC
 */
HWTEST_F(TabsPatternTestNg, TabsTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */
    TabsModelNG instance;
    instance.Create(BarPosition::START, 1, nullptr, nullptr);
    instance.SetTabBarPosition(BarPosition::START);
    instance.SetTabBarMode(TabBarMode::SCROLLABLE);
    /**
     * @tc.steps: step2. create frameNode to get layout properties.
     * @tc.expected: step2. related function is called.
     */
    auto tabsFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    /**
     * @tc.steps: step3. get the properties of all settings.
     * @tc.expected: step3. check whether the properties is correct.
     */
    EXPECT_FALSE(tabsFrameNode == nullptr);
    EXPECT_EQ(tabsFrameNode->GetTag(), V2::TABS_ETS_TAG);
    auto tabsPattern = tabsFrameNode->GetPattern<TabsPattern>();
    EXPECT_FALSE(tabsPattern == nullptr);
    EXPECT_EQ(tabsPattern->IsAtomicNode(), false);
    auto tabsLayoutProperty = tabsFrameNode->GetLayoutProperty<TabsLayoutProperty>();
    EXPECT_FALSE(tabsLayoutProperty == nullptr);
    EXPECT_EQ(tabsLayoutProperty->GetTabBarPosition(), BarPosition::START);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildren().front());
    EXPECT_FALSE(tabBarNode == nullptr);
    EXPECT_EQ(tabBarNode->GetTag(), V2::TAB_BAR_ETS_TAG);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    EXPECT_FALSE(tabBarLayoutProperty == nullptr);
    EXPECT_EQ(tabBarLayoutProperty->GetTabBarMode(), TabBarMode::SCROLLABLE);
    auto layoutAlgorithm = tabsPattern->CreateLayoutAlgorithm();
    EXPECT_FALSE(layoutAlgorithm == nullptr);
    auto onChange = [](const BaseEventInfo* info) {};
    tabsPattern->SetOnChangeEvent(std::move(onChange));
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildren().back());
    EXPECT_FALSE(swiperNode == nullptr);
    EXPECT_EQ(swiperNode->GetTag(), V2::SWIPER_ETS_TAG);
    auto swiperEventHub = swiperNode->GetEventHub<SwiperEventHub>();
    EXPECT_FALSE(swiperEventHub == nullptr);
    tabsPattern->OnModifyDone();
}

/**
 * @tc.name: TabsTest005
 * @tc.desc: Test tabs node.
 * @tc.type: FUNC
 */
HWTEST_F(TabsPatternTestNg, TabsTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */
    TabsModelNG instance;
    instance.Create(BarPosition::START, 1, nullptr, nullptr);
    instance.SetTabBarWidth(TAB_BAR_WIDTH);
    instance.SetTabBarHeight(TAB_BAR_HEIGHT);
    /**
     * @tc.steps: step2. create frameNode to get layout properties.
     * @tc.expected: step2. related function is called.
     */
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    /**
     * @tc.steps: step3. get the properties of all settings.
     * @tc.expected: step3. check whether the properties is correct.
     */
    EXPECT_FALSE(tabsFrameNode == nullptr);
    EXPECT_EQ(tabsFrameNode->GetTag(), V2::TABS_ETS_TAG);
    auto tabsPattern = tabsFrameNode->GetPattern<TabsPattern>();
    EXPECT_FALSE(tabsPattern == nullptr);
    EXPECT_EQ(tabsFrameNode->HasSwiperNode(), true);
    EXPECT_EQ(tabsFrameNode->HasTabBarNode(), true);
    EXPECT_FALSE(tabsFrameNode->GetSwiperId() == -1);
    EXPECT_FALSE(tabsFrameNode->GetTabBarId() == -1);
    EXPECT_FALSE(tabsFrameNode->GetTabBar() == nullptr);
    EXPECT_FALSE(tabsFrameNode->GetTabs() == nullptr);
}

/**
 * @tc.name: TabsTest006
 * @tc.desc: Test set index and animation duration.
 * @tc.type: FUNC
 */
HWTEST_F(TabsPatternTestNg, TabsTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */
    TabsModelNG instance;
    instance.Create(BarPosition::START, 1, nullptr, nullptr);
    /**
     * @tc.steps: step2. create frameNode to get layout properties.
     * @tc.expected: step2. related function is called.
     */
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    /**
     * @tc.steps: step3. get the properties of all settings.
     * @tc.expected: step3. check whether the properties is correct.
     */
    EXPECT_FALSE(tabsFrameNode == nullptr);
    EXPECT_EQ(tabsFrameNode->GetTag(), V2::TABS_ETS_TAG);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildren().back());
    EXPECT_FALSE(swiperNode == nullptr);
    EXPECT_EQ(swiperNode->GetTag(), V2::SWIPER_ETS_TAG);
    auto swiperLayoutProperty = swiperNode->GetLayoutProperty<SwiperLayoutProperty>();
    EXPECT_FALSE(swiperLayoutProperty == nullptr);
    EXPECT_EQ(swiperLayoutProperty->GetIndex(), 1);
    auto swiperPaintProperty = swiperNode->GetPaintProperty<SwiperPaintProperty>();
    EXPECT_FALSE(swiperPaintProperty == nullptr);
    EXPECT_EQ(swiperPaintProperty->GetDuration(), ANIMATION_DURATION);
    auto firstTabContentFrameNode =
        FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 20, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto secondTabContentFrameNode =
        FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 21, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto thirdTabContentFrameNode =
        FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 22, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    swiperNode->AddChild(firstTabContentFrameNode);
    swiperNode->AddChild(secondTabContentFrameNode);
    swiperNode->AddChild(thirdTabContentFrameNode);
    tabsFrameNode->MarkModifyDone();
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildren().front());
    EXPECT_FALSE(tabBarNode == nullptr);
    EXPECT_EQ(tabBarNode->GetTag(), V2::TAB_BAR_ETS_TAG);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    EXPECT_FALSE(tabBarPattern == nullptr);
    auto tabBarLayoutProperty = tabBarPattern->GetLayoutProperty<TabBarLayoutProperty>();
    EXPECT_FALSE(tabBarLayoutProperty == nullptr);
    EXPECT_EQ(tabBarLayoutProperty->GetIndicator().value_or(0), 0);
}

/**
 * @tc.name: TabsTest007
 * @tc.desc: Test set index and animation duration.
 * @tc.type: FUNC
 */
HWTEST_F(TabsPatternTestNg, TabsTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */
    TabsModelNG instance;
    instance.Create(BarPosition::START, 1, nullptr, nullptr);
    instance.SetIndex(4);
    instance.SetAnimationDuration(SET_ANIMATION_DURATION);
    /**
     * @tc.steps: step2. create frameNode to get layout properties.
     * @tc.expected: step2. related function is called.
     */
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    /**
     * @tc.steps: step3. get the properties of all settings.
     * @tc.expected: step3. check whether the properties is correct.
     */
    EXPECT_FALSE(tabsFrameNode == nullptr);
    EXPECT_EQ(tabsFrameNode->GetTag(), V2::TABS_ETS_TAG);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildren().back());
    EXPECT_FALSE(swiperNode == nullptr);
    EXPECT_EQ(swiperNode->GetTag(), V2::SWIPER_ETS_TAG);
    auto swiperLayoutProperty = swiperNode->GetLayoutProperty<SwiperLayoutProperty>();
    EXPECT_FALSE(swiperLayoutProperty == nullptr);
    auto swiperPaintProperty = swiperNode->GetPaintProperty<SwiperPaintProperty>();
    EXPECT_FALSE(swiperPaintProperty == nullptr);
    EXPECT_EQ(swiperLayoutProperty->GetIndex(), 4);
    EXPECT_EQ(swiperPaintProperty->GetDuration(), SET_ANIMATION_DURATION);
}

/**
 * @tc.name: TabsTest008
 * @tc.desc: Test set index and animation duration.
 * @tc.type: FUNC
 */
HWTEST_F(TabsPatternTestNg, TabsTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */
    TabsModelNG instance;
    instance.Create(BarPosition::START, 1, nullptr, nullptr);
    instance.SetIndex(4);
    /**
     * @tc.steps: step2. create frameNode to get layout properties.
     * @tc.expected: step2. related function is called.
     */
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    /**
     * @tc.steps: step3. get the properties of all settings.
     * @tc.expected: step3. check whether the properties is correct.
     */
    EXPECT_FALSE(tabsFrameNode == nullptr);
    EXPECT_EQ(tabsFrameNode->GetTag(), V2::TABS_ETS_TAG);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildren().back());
    EXPECT_FALSE(swiperNode == nullptr);
    EXPECT_EQ(swiperNode->GetTag(), V2::SWIPER_ETS_TAG);
    auto swiperLayoutProperty = swiperNode->GetLayoutProperty<SwiperLayoutProperty>();
    EXPECT_FALSE(swiperLayoutProperty == nullptr);
    EXPECT_EQ(swiperLayoutProperty->GetIndex(), 4);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildren().front());
    EXPECT_FALSE(tabBarNode == nullptr);
    EXPECT_EQ(tabBarNode->GetTag(), V2::TAB_BAR_ETS_TAG);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    EXPECT_FALSE(tabBarPattern == nullptr);
    auto tabBarLayoutProperty = tabBarPattern->GetLayoutProperty<TabBarLayoutProperty>();
    EXPECT_FALSE(tabBarLayoutProperty == nullptr);
    EXPECT_EQ(tabBarLayoutProperty->GetIndicator().value_or(0), 0);
}

/**
 * @tc.name: TabsTest009
 * @tc.desc: Test gestureHub.
 * @tc.type: FUNC
 */
HWTEST_F(TabsPatternTestNg, TabsTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */
    TabsModelNG instance;
    instance.Create(BarPosition::START, 1, nullptr, nullptr);

    /**
     * @tc.steps: step2. create frameNode to get layout properties.
     * @tc.expected: step2. related function is called.
     */
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    /**
     * @tc.steps: step3. get the properties of all settings.
     * @tc.expected: step3. check whether the properties is correct.
     */
    EXPECT_FALSE(tabsFrameNode == nullptr);
    EXPECT_EQ(tabsFrameNode->GetTag(), V2::TABS_ETS_TAG);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildren().back());
    EXPECT_FALSE(swiperNode == nullptr);
    EXPECT_EQ(swiperNode->GetTag(), V2::SWIPER_ETS_TAG);
    auto swiperLayoutProperty = swiperNode->GetLayoutProperty<SwiperLayoutProperty>();
    EXPECT_FALSE(swiperLayoutProperty == nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildren().front());
    EXPECT_FALSE(tabBarNode == nullptr);
    EXPECT_EQ(tabBarNode->GetTag(), V2::TAB_BAR_ETS_TAG);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    EXPECT_FALSE(tabBarPattern == nullptr);
    auto tabBarLayoutProperty = tabBarPattern->GetLayoutProperty<TabBarLayoutProperty>();
    EXPECT_FALSE(tabBarLayoutProperty == nullptr);
    EXPECT_EQ(tabBarLayoutProperty->GetIndicator().value_or(0), 0);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    EXPECT_FALSE(swiperPattern == nullptr);
    auto hub = tabBarPattern->GetEventHub<EventHub>();
    EXPECT_FALSE(hub == nullptr);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    EXPECT_FALSE(gestureHub == nullptr);
}

} // namespace OHOS::Ace::NG
