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

/**
 * @tc.name: InitTabBarProperty001
 * @tc.desc: test InitTabBarProperty
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternThreeTestNg, InitTabBarProperty001, TestSize.Level1)
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
    auto callback = [&count](float) { count++; };

    auto context = tabBarNode->GetRenderContext();
    ASSERT_NE(context, nullptr);
    tabBarPattern->tabBarProperty_ = AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0, std::move(callback));

    tabBarPattern->InitTabBarProperty();

    EXPECT_EQ(count, 1);
}

/**
 * @tc.name: OnAttachToFrameNode001
 * @tc.desc: test OnAttachToFrameNode
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternThreeTestNg, OnAttachToFrameNode001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    tabBarPattern->OnAttachToFrameNode();

    EXPECT_EQ(tabBarNode->layoutProperty_->safeAreaExpandOpts_->type, SAFE_AREA_TYPE_SYSTEM);
}

/**
 * @tc.name: SetTabBarFinishCallback001
 * @tc.desc: test SetTabBarFinishCallback
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternThreeTestNg, SetTabBarFinishCallback001, TestSize.Level1)
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

    auto count = 0;
    auto callback = [&count]() { count++; };

    tabBarPattern->swiperController_->SetTabBarFinishCallback(callback);
    tabBarPattern->SetTabBarFinishCallback();

    EXPECT_EQ(count, 1);
}

/**
 * @tc.name: InitSurfaceChangedCallback001
 * @tc.desc: test InitSurfaceChangedCallback
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternThreeTestNg, InitSurfaceChangedCallback001, TestSize.Level1)
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

    auto count = 0;
    auto callback = [&count](int32_t, int32_t, int32_t, int32_t, WindowSizeChangeReason) { count++; };

    pipeline->RegisterSurfaceChangedCallback(callback);
    tabBarPattern->InitSurfaceChangedCallback();

    EXPECT_EQ(count, 1);
}

/**
 * @tc.name: InitSurfaceChangedCallback002
 * @tc.desc: test InitSurfaceChangedCallback
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternThreeTestNg, InitSurfaceChangedCallback002, TestSize.Level1)
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

    tabBarPattern->surfaceChangedCallbackId_ = 1;
    auto count = 0;
    auto callback = [&count](int32_t, int32_t, int32_t, int32_t, WindowSizeChangeReason) { count++; };

    pipeline->RegisterSurfaceChangedCallback(callback);
    tabBarPattern->InitSurfaceChangedCallback();

    EXPECT_EQ(count, 0);
}

/**
 * @tc.name: AddTabBarItemClickAndTouchEvent001
 * @tc.desc: test AddTabBarItemClickAndTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternThreeTestNg, AddTabBarItemClickAndTouchEvent001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    auto tabBarItemNode = AceType::DynamicCast<FrameNode>(tabBarNode->GetChildAtIndex(0));
    auto count = 0;
    auto callback1 = [&count](GestureEvent) { count++; };
    auto callback2 = [&count](TouchEventInfo) { count++; };

    auto clickEvent = AceType::MakeRefPtr<ClickEvent>(std::move(callback1));
    auto touchEvent = AceType::MakeRefPtr<TouchEventImpl>(std::move(callback2));

    auto gestureHub = tabBarNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    gestureHub->AddClickEvent(clickEvent);
    gestureHub->AddTouchEvent(touchEvent);

    tabBarPattern->AddTabBarItemClickAndTouchEvent(tabBarItemNode);

    EXPECT_EQ(count, 2);
}

/**
 * @tc.name: AddMaskItemClickEvent001
 * @tc.desc: test AddMaskItemClickEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternThreeTestNg, AddMaskItemClickEvent001, TestSize.Level1)
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
    auto callback1 = [&count](GestureEvent) { count++; };

    auto clickEvent = AceType::MakeRefPtr<ClickEvent>(std::move(callback1));

    auto gestureHub = tabBarNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    gestureHub->AddClickEvent(clickEvent);

    tabBarPattern->AddMaskItemClickEvent();

    EXPECT_EQ(count, 1);
}

/**
 * @tc.name: FocusCurrentOffset001
 * @tc.desc: test FocusCurrentOffset
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternThreeTestNg, FocusCurrentOffset001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);

    tabBarLayoutProperty->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    int32_t index = 2;
    tabBarPattern->visibleItemPosition_.insert(
        { { 0, { 0.0f, 100.0f } }, { 1, { 100.0f, 200.0f } }, { 2, { 200.0f, 300.0f } } });
    tabBarPattern->FocusCurrentOffset(index);

    EXPECT_EQ(tabBarPattern->focusIndex_, 2);
}

/**
 * @tc.name: RemoveTabBarEventCallback001
 * @tc.desc: test RemoveTabBarEventCallback
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternThreeTestNg, RemoveTabBarEventCallback001, TestSize.Level1)
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

    auto count = 0;
    auto callback1 = [&count]() { count++; };
    tabBarPattern->swiperController_->SetRemoveTabBarEventCallback(callback1);
    tabBarPattern->RemoveTabBarEventCallback();

    EXPECT_EQ(count, 1);
}

/**
 * @tc.name: RemoveTabBarEventCallback002
 * @tc.desc: test RemoveTabBarEventCallback
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternThreeTestNg, RemoveTabBarEventCallback002, TestSize.Level1)
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

    auto count = 0;
    auto callback1 = [&count]() { count++; };
    tabBarPattern->swiperController_->SetRemoveTabBarEventCallback(callback1);
    tabBarPattern->RemoveTabBarEventCallback();

    EXPECT_EQ(count, 0);
}

/**
 * @tc.name: AddTabBarEventCallback001
 * @tc.desc: test AddTabBarEventCallback
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternThreeTestNg, AddTabBarEventCallback001, TestSize.Level1)
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
    auto count = 0;
    auto callback1 = [&count]() { count++; };
    tabBarPattern->swiperController_->SetAddTabBarEventCallback(callback1);
    tabBarPattern->RemoveTabBarEventCallback();

    EXPECT_EQ(count, 1);
}

/**
 * @tc.name: AddTabBarEventCallback002
 * @tc.desc: test AddTabBarEventCallback
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternThreeTestNg, AddTabBarEventCallback002, TestSize.Level1)
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

    auto count = 0;
    auto callback1 = [&count]() { count++; };
    tabBarPattern->swiperController_->SetAddTabBarEventCallback(callback1);
    tabBarPattern->RemoveTabBarEventCallback();

    EXPECT_EQ(count, 0);
}

/**
 * @tc.name: OnTabBarIndexChange001
 * @tc.desc: test OnTabBarIndexChange
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternThreeTestNg, OnTabBarIndexChange001, TestSize.Level1)
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

    auto count = 0;
    auto callback1 = [&count]() { count++; };

    int32_t index = 10;
    pipeline->AddAfterRenderTask(callback1);
    tabBarPattern->OnTabBarIndexChange(index);

    EXPECT_EQ(count, 1);
}

/**
 * @tc.name: StopTranslateAnimation001
 * @tc.desc: test StopTranslateAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternThreeTestNg, StopTranslateAnimation001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    bool isImmediately = true;
    AnimationOption option;
    option.SetDuration(0);
    option.SetCurve(Curves::LINEAR);
    auto count = 0;
    auto callback1 = [&count]() { count++; };

    AnimationUtils::Animate(option, callback1);

    tabBarPattern->StopTranslateAnimation(isImmediately);

    EXPECT_EQ(count, 1);
}

/**
 * @tc.name: StopTranslateAnimation002
 * @tc.desc: test StopTranslateAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternThreeTestNg, StopTranslateAnimation002, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    bool isImmediately = false;

    AnimationOption option;
    option.SetDuration(0);
    option.SetCurve(Curves::LINEAR);
    auto count = 0;
    auto callback1 = [&count]() { count++; };

    AnimationUtils::Animate(option, callback1);

    tabBarPattern->StopTranslateAnimation(isImmediately);

    EXPECT_EQ(count, 0);
}

/**
 * @tc.name: StopTranslateAnimation003
 * @tc.desc: test StopTranslateAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternThreeTestNg, StopTranslateAnimation003, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    bool isImmediately = false;

    AnimationOption option;
    option.SetDuration(0);
    option.SetCurve(Curves::LINEAR);
    auto count = 0;
    auto callback1 = [&count]() { count++; };
    tabBarPattern->translateAnimation_ = AnimationUtils::StartAnimation(option, callback1);

    tabBarPattern->StopTranslateAnimation(isImmediately);

    EXPECT_EQ(tabBarPattern->translateAnimation_, nullptr);
}

/**
 * @tc.name: StopTranslateAnimation004
 * @tc.desc: test StopTranslateAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternThreeTestNg, StopTranslateAnimation004, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    bool isImmediately = false;

    AnimationOption option;
    option.SetDuration(0);
    option.SetCurve(Curves::LINEAR);
    auto count = 0;
    auto callback1 = [&count]() { count++; };
    tabBarPattern->tabbarIndicatorAnimation_ = AnimationUtils::StartAnimation(option, callback1);

    tabBarPattern->StopTranslateAnimation(isImmediately);

    EXPECT_EQ(tabBarPattern->tabbarIndicatorAnimation_, nullptr);
}

/**
 * @tc.name: GetLeftPadding001
 * @tc.desc: test GetLeftPadding
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternThreeTestNg, GetLeftPadding001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    auto geometryNode = tabBarNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(200.0f, 100.0f));

    tabBarPattern->barGridMargin_ = 10.0f;
    geometryNode->padding_ = nullptr;
    auto result = tabBarPattern->GetLeftPadding();

    EXPECT_EQ(result, tabBarPattern->barGridMargin_);
}

/**
 * @tc.name: GetLeftPadding001
 * @tc.desc: test GetLeftPadding001
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternThreeTestNg, GetLeftPadding002, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    auto geometryNode = tabBarNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(200.0f, 100.0f));

    tabBarPattern->barGridMargin_ = 10.0f;
    geometryNode->padding_ = nullptr;
    auto result = tabBarPattern->GetLeftPadding();

    EXPECT_EQ(result, tabBarPattern->barGridMargin_);
}

/**
 * @tc.name: GetLeftPadding002
 * @tc.desc: test GetLeftPadding
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternThreeTestNg, GetLeftPadding003, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    auto geometryNode = tabBarNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(200.0f, 100.0f));

    tabBarPattern->barGridMargin_ = 10.0f;
    geometryNode->padding_ = std::make_unique<MarginPropertyF>();
    geometryNode->padding_->left = 10.0f;
    auto result = tabBarPattern->GetLeftPadding();

    EXPECT_EQ(result, 20.0f);
}

/**
 * @tc.name: GetLeftPadding003
 * @tc.desc: test GetLeftPadding
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternThreeTestNg, GetLeftPadding004, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    auto geometryNode = tabBarNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(200.0f, 100.0f));

    tabBarPattern->barGridMargin_ = 10.0f;
    geometryNode->padding_ = std::make_unique<MarginPropertyF>();
    auto result = tabBarPattern->GetLeftPadding();

    EXPECT_EQ(result, tabBarPattern->barGridMargin_);
}

/**
 * @tc.name: ContentWillChange001
 * @tc.desc: test ContentWillChange
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternThreeTestNg, ContentWillChange001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    int32_t currentIndex = 10;
    int32_t comingIndex = 10;
    auto res = tabBarPattern->ContentWillChange(currentIndex, comingIndex);

    EXPECT_TRUE(res);
}

/**
 * @tc.name: ContentWillChange002
 * @tc.desc: test ContentWillChange
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternThreeTestNg, ContentWillChange002, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    ASSERT_NE(tabsNode, nullptr);
    auto tabsPattern = tabsNode->GetPattern<TabsPattern>();
    ASSERT_NE(tabsPattern, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    int32_t currentIndex = 10;
    int32_t comingIndex = 5;
    tabsPattern->interceptStatus_ = true;
    tabsPattern->callback_ = nullptr;
    auto res = tabBarPattern->ContentWillChange(currentIndex, comingIndex);

    EXPECT_FALSE(res);
}

/**
 * @tc.name: ContentWillChange003
 * @tc.desc: test ContentWillChange
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternThreeTestNg, ContentWillChange003, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    ASSERT_NE(tabsNode, nullptr);
    auto tabsPattern = tabsNode->GetPattern<TabsPattern>();
    ASSERT_NE(tabsPattern, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    int32_t currentIndex = 10;
    int32_t comingIndex = 5;
    tabsPattern->interceptStatus_ = true;
    auto isfalg = false;
    tabsPattern->callback_ = [&isfalg](int32_t, int32_t) -> bool { return isfalg = true; };
    auto res = tabBarPattern->ContentWillChange(currentIndex, comingIndex);

    EXPECT_TRUE(isfalg);
    EXPECT_TRUE(res);
}

/**
 * @tc.name: UpdateFocusToSelectedNode001
 * @tc.desc: test UpdateFocusToSelectedNode
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternThreeTestNg, UpdateFocusToSelectedNode001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    ASSERT_NE(tabsNode, nullptr);
    auto tabsPattern = tabsNode->GetPattern<TabsPattern>();
    ASSERT_NE(tabsPattern, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    auto isFocusActive = true;
    auto childFocusNode = tabBarPattern->GetCurrentFocusNode();
    ASSERT_NE(childFocusNode, nullptr);

    childFocusNode->currentFocus_ = false;
    tabBarPattern->UpdateFocusToSelectedNode(isFocusActive);

    EXPECT_TRUE(childFocusNode->currentFocus_);
}

/**
 * @tc.name: UpdateFocusToSelectedNode002
 * @tc.desc: test UpdateFocusToSelectedNode
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternThreeTestNg, UpdateFocusToSelectedNode002, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    ASSERT_NE(tabsNode, nullptr);
    auto tabsPattern = tabsNode->GetPattern<TabsPattern>();
    ASSERT_NE(tabsPattern, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    auto isFocusActive = false;
    auto childFocusNode = tabBarPattern->GetCurrentFocusNode();
    ASSERT_NE(childFocusNode, nullptr);

    childFocusNode->currentFocus_ = false;
    tabBarPattern->UpdateFocusToSelectedNode(isFocusActive);

    EXPECT_FALSE(childFocusNode->currentFocus_);
}

/**
 * @tc.name: GetSubTabBarHoverColor001
 * @tc.desc: test GetSubTabBarHoverColor
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternThreeTestNg, GetSubTabBarHoverColor001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    ASSERT_NE(tabsNode, nullptr);
    auto tabsPattern = tabsNode->GetPattern<TabsPattern>();
    ASSERT_NE(tabsPattern, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    tabBarPattern->isTabBarFocusActive_ = true;
    tabBarPattern->focusIndicator_ = 10;
    tabBarPattern->tabBarStyle_ = TabBarStyle::SUBTABBATSTYLE;
    int32_t index = 10;
    tabBarPattern->tabBarItemFocusBgColor_ = Color::BLACK;
    auto color = tabBarPattern->GetSubTabBarHoverColor(index);

    EXPECT_NE(color, Color::BLACK);
}

/**
 * @tc.name: GetSubTabBarHoverColor002
 * @tc.desc: test GetSubTabBarHoverColor
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternThreeTestNg, GetSubTabBarHoverColor002, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    ASSERT_NE(tabsNode, nullptr);
    auto tabsPattern = tabsNode->GetPattern<TabsPattern>();
    ASSERT_NE(tabsPattern, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    tabBarPattern->isTabBarFocusActive_ = false;
    tabBarPattern->focusIndicator_ = 10;
    tabBarPattern->tabBarStyle_ = TabBarStyle::SUBTABBATSTYLE;
    int32_t index = 10;
    tabBarPattern->tabBarItemHoverColor_ = Color::BLUE;
    auto color = tabBarPattern->GetSubTabBarHoverColor(index);

    EXPECT_NE(color, Color::BLUE);
}
} // namespace OHOS::Ace::NG
