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

#include "tabs_test_ng.h"
#include "test/mock/base/mock_task_executor.h"

#include "core/components_ng/pattern/scroll/scroll_edge_effect.h"
#include "core/components_ng/pattern/text/text_layout_property.h"

namespace OHOS::Ace::NG {
class TabBarPatternThreeTestNg : public TabsTestNg {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void TabBarPatternThreeTestNg::SetUpTestSuite()
{
    TabsTestNg::SetUpTestSuite();
    MockAnimationManager::Enable(true);
    const int32_t ticks = 2;
    MockAnimationManager::GetInstance().SetTicks(ticks);
}

void TabBarPatternThreeTestNg::TearDownTestSuite()
{
    TabsTestNg::TearDownTestSuite();
    MockAnimationManager::GetInstance().Reset();
    MockAnimationManager::Enable(false);
}

/**
 * @tc.name: StartShowTabBarImmediately001
 * @tc.desc: test StartShowTabBarImmediately
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternThreeTestNg, StartShowTabBarImmediately001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    tabBarPattern->userDefinedTranslateY_ = 0.0f;
    auto context = tabBarNode->GetRenderContext();
    ASSERT_NE(context, nullptr);
    tabBarPattern->StartShowTabBarImmediately();
    tabBarPattern->userDefinedTranslateY_ = 10.0f;
    EXPECT_FALSE(tabBarPattern->isTabBarShowing_);
}

/**
 * @tc.name: InsideTabBarRegion001
 * @tc.desc: test InsideTabBarRegion
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternThreeTestNg, InsideTabBarRegion001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    TouchLocationInfo touchLocationInfo(0);
    touchLocationInfo.localLocation_ = Offset(10.0f, 10.0f);
    auto geometryNode = tabBarNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto rectf = geometryNode->frame_.rect_;
    rectf = RectF(0.0f, 0.0f, 100.0f, 50.0f);

    auto touchPoint = PointF(10.0f, 10.0f);
    auto ret = rectf.IsInRegion(touchPoint);
    EXPECT_TRUE(ret);

    auto res = tabBarPattern->InsideTabBarRegion(touchLocationInfo);
    EXPECT_TRUE(res);
}

/**
 * @tc.name: GetCurrentFocusNode001
 * @tc.desc: test GetCurrentFocusNode
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternThreeTestNg, GetCurrentFocusNode001, TestSize.Level1)
{
    auto tabBarPattern = AceType::MakeRefPtr<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    auto childFocusHub = tabBarPattern->GetCurrentFocusNode();
    CHECK_NULL_VOID(childFocusHub);
    EXPECT_EQ(childFocusHub->GetFocusDependence(), FocusDependence::SELF);
}

/**
 * @tc.name: GetNextFocusIndicator001
 * @tc.desc: test GetNextFocusIndicator
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternThreeTestNg, GetNextFocusIndicator001, TestSize.Level1)
{
    int32_t indicator = -1;
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    auto indicator1 = tabBarPattern->GetNextFocusIndicator(indicator, FocusStep::SHIFT_TAB);
    EXPECT_EQ(indicator1, std::nullopt);
}

/**
 * @tc.name: GetNextFocusIndicator002
 * @tc.desc: test GetNextFocusIndicator
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternThreeTestNg, GetNextFocusIndicator002, TestSize.Level1)
{
    int32_t indicator = 1;

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    auto indicator1 = tabBarPattern->GetNextFocusIndicator(indicator, FocusStep::SHIFT_TAB);
    EXPECT_EQ(indicator1, 0);
}

/**
 * @tc.name: GetNextFocusIndicator003
 * @tc.desc: test GetNextFocusIndicator
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternThreeTestNg, GetNextFocusIndicator003, TestSize.Level1)
{
    int32_t indicator = 1;
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    auto indicator1 = tabBarPattern->GetNextFocusIndicator(indicator, FocusStep::TAB);
    EXPECT_EQ(indicator1, 2);
}

/**
 * @tc.name: GetNextFocusIndicator004
 * @tc.desc: test GetNextFocusIndicator
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternThreeTestNg, GetNextFocusIndicator004, TestSize.Level1)
{
    int32_t indicator = 1;
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    auto indicator1 = tabBarPattern->GetNextFocusIndicator(indicator, FocusStep::UP_END);
    EXPECT_EQ(indicator1, 0);
}

/**
 * @tc.name: SetSurfaceChangeCallback001
 * @tc.desc: test SetSurfaceChangeCallback
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternThreeTestNg, SetSurfaceChangeCallback001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    tabBarPattern->SetSurfaceChangeCallback();
    EXPECT_NE(tabBarPattern->swiperController_, nullptr);
}

/**
 * @tc.name: CustomizeExpandSafeArea001
 * @tc.desc: test CustomizeExpandSafeArea
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternThreeTestNg, CustomizeExpandSafeArea001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    auto res = tabBarPattern->CustomizeExpandSafeArea();
    EXPECT_TRUE(res);
}

/**
 * @tc.name: CustomizeExpandSafeArea002
 * @tc.desc: test CustomizeExpandSafeArea
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternThreeTestNg, CustomizeExpandSafeArea002, TestSize.Level1)
{
    auto tabBarPattern = AceType::MakeRefPtr<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    auto res = tabBarPattern->CustomizeExpandSafeArea();
    EXPECT_FALSE(res);
}

/**
 * @tc.name: ClickTo001
 * @tc.desc: test ClickTo
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternThreeTestNg, ClickTo001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    ASSERT_NE(tabsNode, nullptr);
    auto tabPattern = tabsNode->GetPattern<TabsPattern>();
    ASSERT_NE(tabPattern, nullptr);
    auto host = FrameNode::CreateFrameNode(V2::TABS_ETS_TAG, -1, tabPattern, true);
    ASSERT_NE(host, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    ASSERT_NE(swiperNode, nullptr);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    tabsNode->AddChild(host);

    tabPattern->isCustomAnimation_ = true;
    swiperPattern->currentProxyInAnimation_ = AceType::MakeRefPtr<TabContentTransitionProxy>();

    int32_t index1 = 10;
    tabBarPattern->ClickTo(host, index1);
    EXPECT_EQ(swiperPattern->customAnimationToIndex_, 10);
}

/**
 * @tc.name: ClickTo002
 * @tc.desc: test ClickTo
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternThreeTestNg, ClickTo002, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    ASSERT_NE(tabsNode, nullptr);
    auto tabPattern = tabsNode->GetPattern<TabsPattern>();
    ASSERT_NE(tabPattern, nullptr);
    auto host = FrameNode::CreateFrameNode(V2::TABS_ETS_TAG, -1, tabPattern, true);
    ASSERT_NE(host, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    ASSERT_NE(swiperNode, nullptr);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    tabsNode->AddChild(host);

    tabPattern->isCustomAnimation_ = false;
    tabBarPattern->animationDuration_ = 300;
    tabPattern->animateMode_ = TabAnimateMode::ACTION_FIRST;
    swiperPattern->currentProxyInAnimation_ = AceType::MakeRefPtr<TabContentTransitionProxy>();
    int32_t index1 = 10;

    tabBarPattern->ClickTo(host, index1);
    EXPECT_TRUE(tabBarPattern->tabContentWillChangeFlag_);
}

/**
 * @tc.name: ClickTo003
 * @tc.desc: test ClickTo
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternThreeTestNg, ClickTo003, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    ASSERT_NE(tabsNode, nullptr);
    auto tabPattern = tabsNode->GetPattern<TabsPattern>();
    ASSERT_NE(tabPattern, nullptr);
    auto host = FrameNode::CreateFrameNode(V2::TABS_ETS_TAG, -1, tabPattern, true);
    ASSERT_NE(host, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    ASSERT_NE(swiperNode, nullptr);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    tabsNode->AddChild(host);

    tabPattern->isCustomAnimation_ = false;
    tabBarPattern->animationDuration_ = 300;
    tabPattern->animateMode_ = TabAnimateMode::NO_ANIMATION;
    swiperPattern->currentProxyInAnimation_ = AceType::MakeRefPtr<TabContentTransitionProxy>();
    int32_t index1 = 10;
    bool isCallbackCalled = false;

    tabBarPattern->swiperController_->SetSwipeToWithoutAnimationImpl([&](int32_t index) { isCallbackCalled = true; });
    tabBarPattern->ClickTo(host, index1);
    EXPECT_TRUE(isCallbackCalled);
}

/**
 * @tc.name: ClickTo004
 * @tc.desc: test ClickTo
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternThreeTestNg, ClickTo004, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    ASSERT_NE(tabsNode, nullptr);
    auto tabPattern = tabsNode->GetPattern<TabsPattern>();
    ASSERT_NE(tabPattern, nullptr);
    auto host = FrameNode::CreateFrameNode(V2::TABS_ETS_TAG, -1, tabPattern, true);
    ASSERT_NE(host, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    ASSERT_NE(swiperNode, nullptr);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);

    tabsNode->AddChild(host);

    tabPattern->isCustomAnimation_ = true;
    tabBarPattern->animationDuration_ = 300;
    int32_t index1 = 10;
    tabBarLayoutProperty->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    tabBarPattern->visibleItemPosition_ = { { 1, { 100, true } }, { 2, { 200, false } } };

    tabBarPattern->ClickTo(host, index1);
    EXPECT_EQ(tabBarPattern->targetIndex_, index1);
}

/**
 * @tc.name: ClickTo005
 * @tc.desc: test ClickTo
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternThreeTestNg, ClickTo005, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    ASSERT_NE(tabsNode, nullptr);
    auto tabPattern = tabsNode->GetPattern<TabsPattern>();
    ASSERT_NE(tabPattern, nullptr);
    auto host = FrameNode::CreateFrameNode(V2::TABS_ETS_TAG, -1, tabPattern, true);
    ASSERT_NE(host, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    ASSERT_NE(swiperNode, nullptr);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);

    tabsNode->AddChild(host);

    tabPattern->isCustomAnimation_ = true;
    tabBarPattern->animationDuration_ = 300;
    int32_t index1 = 10;

    tabBarPattern->ClickTo(host, index1);
    EXPECT_EQ(tabBarPattern->jumpIndex_, index1);
}

/**
 * @tc.name: ClickTo006
 * @tc.desc: test ClickTo
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternThreeTestNg, ClickTo006, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    ASSERT_NE(tabsNode, nullptr);
    auto tabPattern = tabsNode->GetPattern<TabsPattern>();
    ASSERT_NE(tabPattern, nullptr);
    auto host = FrameNode::CreateFrameNode(V2::TABS_ETS_TAG, -1, tabPattern, true);
    ASSERT_NE(host, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    ASSERT_NE(swiperNode, nullptr);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    tabsNode->AddChild(host);

    tabPattern->isCustomAnimation_ = true;
    tabBarPattern->animationDuration_ = 300;
    int32_t index1 = 10;
    auto pipeline = tabsNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    auto tabTheme = pipeline->GetTheme<TabTheme>();
    ASSERT_NE(tabTheme, nullptr);
    tabTheme->isChangeFocusTextStyle_ = true;

    tabBarPattern->ClickTo(host, index1);
    EXPECT_EQ(tabBarPattern->focusIndicator_, index1);
}

/**
 * @tc.name: IsContainsBuilder001
 * @tc.desc: test IsContainsBuilder
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternThreeTestNg, IsContainsBuilder001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    tabBarPattern->tabBarType_.clear();
    EXPECT_FALSE(tabBarPattern->IsContainsBuilder());
}

/**
 * @tc.name: IsContainsBuilder002
 * @tc.desc: test IsContainsBuilder
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternThreeTestNg, IsContainsBuilder002, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    int32_t tabs = 1;

    tabBarPattern->tabBarType_.emplace(tabs, TabBarParamType::CUSTOM_BUILDER);
    EXPECT_TRUE(tabBarPattern->IsContainsBuilder());
}

/**
 * @tc.name: IsContainsBuilder003
 * @tc.desc: test IsContainsBuilder
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternThreeTestNg, IsContainsBuilder003, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    int32_t tabs = 1;
    tabBarPattern->tabBarType_.emplace(tabs, TabBarParamType::COMPONENT_CONTENT);
    tabBarPattern->tabBarType_.emplace(tabs, TabBarParamType::SUB_COMPONENT_CONTENT);

    EXPECT_TRUE(tabBarPattern->IsContainsBuilder());
}

/**
 * @tc.name: IsContainsBuilder004
 * @tc.desc: test IsContainsBuilder
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternThreeTestNg, IsContainsBuilder004, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    int32_t tabs = 1;

    tabBarPattern->tabBarType_.emplace(tabs, TabBarParamType::NORMAL);
    tabBarPattern->tabBarType_.emplace(tabs, TabBarParamType::SUB_COMPONENT_CONTENT);

    EXPECT_FALSE(tabBarPattern->IsContainsBuilder());
}

/**
 * @tc.name: OnCustomContentTransition001
 * @tc.desc: test OnCustomContentTransition
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternThreeTestNg, OnCustomContentTransition001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    ASSERT_NE(swiperNode, nullptr);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    int32_t fromIndex = 1;
    int32_t toIndex = 10;
    tabBarPattern->OnCustomContentTransition(fromIndex, toIndex);

    EXPECT_EQ(swiperPattern->customAnimationToIndex_, toIndex);
}

/**
 * @tc.name: GetSwiperPattern001
 * @tc.desc: test GetSwiperPattern
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternThreeTestNg, GetSwiperPattern001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    auto swiperPattern = tabBarPattern->GetSwiperPattern();
    EXPECT_NE(swiperPattern, nullptr);
}

/**
 * @tc.name: SetSwiperCurve001
 * @tc.desc: test SetSwiperCurve
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternThreeTestNg, SetSwiperCurve001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    ASSERT_NE(swiperNode, nullptr);
    auto swiperPaintProperty = swiperNode->GetPaintProperty<SwiperPaintProperty>();
    ASSERT_NE(swiperPaintProperty, nullptr);

    RefPtr<Curve> expectedCurve = AceType::MakeRefPtr<CubicCurve>(0.25f, 0.1f, 0.25f, 1.0f);

    tabBarPattern->SetSwiperCurve(expectedCurve);
    EXPECT_EQ(swiperPaintProperty->GetCurveValue(nullptr), expectedCurve);
}

/**
 * @tc.name: SetTurnPageRateCallback001
 * @tc.desc: test SetTurnPageRateCallback
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternThreeTestNg, SetTurnPageRateCallback001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    ASSERT_NE(swiperNode, nullptr);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto swiperController = swiperPattern->GetSwiperController();
    ASSERT_NE(swiperController, nullptr);

    tabBarPattern->swiperController_ = swiperController;
    tabBarPattern->isTouchingSwiper_ = true;
    tabBarPattern->SetSurfaceChangeCallback();
    EXPECT_FALSE(tabBarPattern->isTouchingSwiper_);
}

/**
 * @tc.name: UpdateChildrenClipEdge001
 * @tc.desc: test UpdateChildrenClipEdge
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternThreeTestNg, UpdateChildrenClipEdge001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    auto pipeline = tabsNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    auto tabTheme = pipeline->GetTheme<TabTheme>();
    ASSERT_NE(tabTheme, nullptr);

    tabTheme->isChangeFocusTextStyle_ = true;
    tabBarPattern->UpdateChildrenClipEdge();
    EXPECT_FALSE(tabBarPattern->clipEdge_);
}

/**
 * @tc.name: UpdateChildrenClipEdge002
 * @tc.desc: test UpdateChildrenClipEdge
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternThreeTestNg, UpdateChildrenClipEdge002, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    auto pipeline = tabsNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    auto tabTheme = pipeline->GetTheme<TabTheme>();
    ASSERT_NE(tabTheme, nullptr);

    tabTheme->isChangeFocusTextStyle_ = false;
    tabBarPattern->UpdateChildrenClipEdge();
    EXPECT_TRUE(tabBarPattern->clipEdge_);
}

/**
 * @tc.name: ShowDialogWithNode001
 * @tc.desc: test ShowDialogWithNode
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternThreeTestNg, ShowDialogWithNode001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    auto pipeline = tabsNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    auto tabTheme = pipeline->GetTheme<TabTheme>();
    ASSERT_NE(tabTheme, nullptr);

    tabTheme->isChangeFocusTextStyle_ = false;
    tabBarPattern->UpdateChildrenClipEdge();
    EXPECT_TRUE(tabBarPattern->clipEdge_);
}

/**
 * @tc.name: UpdateCurrentOffset001
 * @tc.desc: test UpdateCurrentOffset
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternThreeTestNg, UpdateCurrentOffset001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    float offset = 0.0f;
    tabBarPattern->clickRepeat_ = true;
    tabBarPattern->UpdateCurrentOffset(offset);
    EXPECT_EQ(tabBarPattern->currentDelta_, offset);
    EXPECT_TRUE(tabBarPattern->clickRepeat_);
}

/**
 * @tc.name: UpdateCurrentOffset002
 * @tc.desc: test UpdateCurrentOffset
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternThreeTestNg, UpdateCurrentOffset002, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    float offset = 10.0f;
    tabBarPattern->clickRepeat_ = true;
    tabBarPattern->UpdateCurrentOffset(offset);
    EXPECT_EQ(tabBarPattern->currentDelta_, offset);
    EXPECT_FALSE(tabBarPattern->clickRepeat_);
}

/**
 * @tc.name: GetTabBarBackgroundColor001
 * @tc.desc: test GetTabBarBackgroundColor
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternThreeTestNg, GetTabBarBackgroundColor001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

        auto context = tabBarNode->GetRenderContext();
    ASSERT_NE(context, nullptr);

    context->propBackgroundColor_ = Color::RED;
    EXPECT_TRUE(context->HasBackgroundColor());

    auto color = tabBarPattern->GetTabBarBackgroundColor();
    EXPECT_EQ(color, Color::RED);
}

/**
 * @tc.name: GetTabBarBackgroundColor002
 * @tc.desc: test GetTabBarBackgroundColor
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternThreeTestNg, GetTabBarBackgroundColor002, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    auto context = tabsNode->GetRenderContext();
    ASSERT_NE(context, nullptr);

    context->propBackgroundColor_ = Color::BLUE;
    EXPECT_TRUE(context->HasBackgroundColor());

    auto color = tabBarPattern->GetTabBarBackgroundColor();
    EXPECT_EQ(color, Color::BLUE);
}

/**
 * @tc.name: GetTabBarBackgroundColor003
 * @tc.desc: test GetTabBarBackgroundColor
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternThreeTestNg, GetTabBarBackgroundColor003, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    auto pipeline = tabBarNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    auto tabTheme = pipeline->GetTheme<TabTheme>();
    ASSERT_NE(tabTheme, nullptr);

    tabTheme->backgroundColor_ = Color::GREEN;

    auto color = tabBarPattern->GetTabBarBackgroundColor();
    EXPECT_EQ(color, Color::GREEN);
}

/**
 * @tc.name: CalculateFrontChildrenMainSize001
 * @tc.desc: test CalculateFrontChildrenMainSize
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternThreeTestNg, CalculateFrontChildrenMainSize001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    tabBarPattern->scrollMargin_ = 50.0f;
    int32_t indicator = 2;
    tabBarPattern->visibleItemPosition_ = { { 0, { .startPos = 0.0f, .endPos = 100.0f } },
        { 1, { .startPos = 100.0f, .endPos = 250.0f } } };
    auto frontChildrenMainSize = tabBarPattern->CalculateFrontChildrenMainSize(indicator);
    EXPECT_FLOAT_EQ(frontChildrenMainSize, 300.0f);
}

/**
 * @tc.name: CalculateFrontChildrenMainSize002
 * @tc.desc: test CalculateFrontChildrenMainSize
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternThreeTestNg, CalculateFrontChildrenMainSize002, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    tabBarPattern->scrollMargin_ = 50.0f;
    int32_t indicator = 2;
    auto frontChildrenMainSize = tabBarPattern->CalculateFrontChildrenMainSize(indicator);
    EXPECT_FLOAT_EQ(frontChildrenMainSize, 50.0f);
}

/**
 * @tc.name: SetEdgeEffectCallback001
 * @tc.desc: test SetEdgeEffectCallback
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternThreeTestNg, SetEdgeEffectCallback001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    auto scrollEffect = AceType::MakeRefPtr<ScrollEdgeEffect>();

    auto count = 0.0;
    scrollEffect->SetCurrentPositionCallback(([&count]() { return count++; }));

    scrollEffect->SetLeadingCallback(([&count]() { return count++; }));

    scrollEffect->SetTrailingCallback(([&count]() { return count++; }));

    scrollEffect->SetInitLeadingCallback(([&count]() { return count++; }));

    scrollEffect->SetInitTrailingCallback(([&count]() { return count++; }));

    tabBarPattern->SetEdgeEffectCallback(scrollEffect);
    EXPECT_FLOAT_EQ(count, 5);
}

/**
 * @tc.name: SetAccessibilityAction001
 * @tc.desc: test SetAccessibilityAction
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternThreeTestNg, SetAccessibilityAction001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    auto count = 0;
    auto accessibilityProperty = tabBarNode->GetAccessibilityProperty<AccessibilityProperty>();
    accessibilityProperty->SetActionScrollForward(([&count]() { return count++; }));

    accessibilityProperty->SetActionScrollBackward(([&count]() { return count++; }));

    tabBarPattern->SetAccessibilityAction();
    EXPECT_FLOAT_EQ(count, 2);
}

/**
 * @tc.name: InitFocusEvent001
 * @tc.desc: test InitFocusEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternThreeTestNg, InitFocusEvent001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    auto focusHub = tabBarNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    auto count = 0;
    focusHub->SetOnFocusInternal([&count](FocusReason) { count++; });

    focusHub->SetOnBlurInternal(([&count]() { count++; }));

    focusHub->SetOnGetNextFocusNodeFunc([&count](FocusReason reason, FocusIntension intension) -> RefPtr<FocusHub> {
        count++;
        return nullptr;
    });

    tabBarPattern->InitFocusEvent();
    EXPECT_FLOAT_EQ(count, 3);
}

/**
 * @tc.name: AddIsFocusActiveUpdateEvent001
 * @tc.desc: test AddIsFocusActiveUpdateEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternThreeTestNg, AddIsFocusActiveUpdateEvent001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    auto count = 0;
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto callback = [&count](bool) { count++; };
    pipeline->AddIsFocusActiveUpdateEvent(tabBarNode, callback);

    tabBarPattern->AddIsFocusActiveUpdateEvent();
    EXPECT_FLOAT_EQ(count, 1);
}

/**
 * @tc.name: InitTabBarProperties001
 * @tc.desc: test InitTabBarProperties
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternThreeTestNg, InitTabBarProperties001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    auto pipeline = tabBarNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    auto tabTheme = pipeline->GetTheme<TabTheme>();
    ASSERT_NE(tabTheme, nullptr);

    tabTheme->subTabBarHoverColor_ = Color::BLACK;
    tabTheme->tabBarFocusedColor_ = Color::BLUE;

    tabBarPattern->InitTabBarProperties(tabTheme);
    EXPECT_EQ(tabBarPattern->tabBarItemHoverColor_, Color::BLACK);
    EXPECT_EQ(tabBarPattern->tabBarItemFocusBgColor_, Color::BLUE);
    EXPECT_EQ(tabBarPattern->tabBarItemDefaultBgColor_, Color::BLACK);
}
} // namespace OHOS::Ace::NG
