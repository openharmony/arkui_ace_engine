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

#include <cstddef>
#include <cstdint>

#include "gtest/gtest.h"
#include "tabs_test_ng.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "core/components_ng/base/observer_handler.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/tabs/tabs_node.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
class TabPatternTestNg : public TabsTestNg {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void TabPatternTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    GTEST_LOG_(INFO) << "FocusAreaTestNG SetUpTestCase";
}

void TabPatternTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    GTEST_LOG_(INFO) << "FocusAreaTestNG TearDownTestCase";
}

/**
 * @tc.name: UpdateSwiperDisableSwipeTest001
 * @tc.desc: UpdateSwiperDisableSwipe
 * @tc.type: FUNC
 */
HWTEST_F(TabPatternTestNg, UpdateSwiperDisableSwipeTest001, TestSize.Level1)
{
    auto tabsPattern = AceType::MakeRefPtr<TabsPattern>();
    ASSERT_NE(tabsPattern, nullptr);

    auto tabsNode = AceType::MakeRefPtr<TabsNode>(V2::TABS_ETS_TAG, 2, tabsPattern, true);
    ASSERT_NE(tabsNode, nullptr);

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_VOID(swiperNode);

    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    tabsPattern->UpdateSwiperDisableSwipe(true);
    EXPECT_NE(swiperPattern->swiperController_->removeSwiperEventCallback_, nullptr);
}

/**
 * @tc.name: SetAnimateModeTest001
 * @tc.desc: SetAnimateMode
 * @tc.type: FUNC
 */
HWTEST_F(TabPatternTestNg, SetAnimateModeTest001, TestSize.Level1)
{
    auto tabsPattern = AceType::MakeRefPtr<TabsPattern>();
    ASSERT_NE(tabsPattern, nullptr);

    auto tabsNode = AceType::MakeRefPtr<TabsNode>(V2::TABS_ETS_TAG, 2, tabsPattern, true);
    ASSERT_NE(tabsNode, nullptr);

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_VOID(swiperNode);

    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    tabsPattern->SetAnimateMode(TabAnimateMode::ACTION_FIRST_WITH_JUMP);
    EXPECT_NE(swiperPattern->tabAnimationMode_, TabAnimateMode::ACTION_FIRST_WITH_JUMP);
}

/**
 * @tc.name: UpdateSelectedStateTest001
 * @tc.desc: UpdateSelectedState
 * @tc.type: FUNC
 */
HWTEST_F(TabPatternTestNg, UpdateSelectedStateTest001, TestSize.Level1)
{
    auto tabsPattern = AceType::MakeRefPtr<TabsPattern>();
    ASSERT_NE(tabsPattern, nullptr);

    auto tabsNode = AceType::MakeRefPtr<TabsNode>(V2::TABS_ETS_TAG, 2, tabsPattern, true);
    ASSERT_NE(tabsNode, nullptr);

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_VOID(swiperNode);

    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    auto tabsLayoutProperty = AceType::MakeRefPtr<TabsLayoutProperty>();
    ASSERT_NE(tabsLayoutProperty, nullptr);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);

    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    tabsPattern->UpdateSelectedState(swiperNode, tabBarPattern, tabsLayoutProperty, 100);

    int32_t defaultIndexValue = 0;
    auto indexValue = tabsLayoutProperty->GetIndexValue(defaultIndexValue);
    EXPECT_NE(indexValue, 100);
}

/**
 * @tc.name: UpdateSelectedStateTest002
 * @tc.desc: UpdateSelectedState
 * @tc.type: FUNC
 */
HWTEST_F(TabPatternTestNg, UpdateSelectedStateTest002, TestSize.Level1)
{
    auto tabsPattern = AceType::MakeRefPtr<TabsPattern>();
    ASSERT_NE(tabsPattern, nullptr);

    auto tabsNode = AceType::MakeRefPtr<TabsNode>(V2::TABS_ETS_TAG, 2, tabsPattern, true);
    ASSERT_NE(tabsNode, nullptr);

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_VOID(swiperNode);

    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    auto tabsLayoutProperty = AceType::MakeRefPtr<TabsLayoutProperty>();
    ASSERT_NE(tabsLayoutProperty, nullptr);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);

    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    swiperPattern->propertyAnimationIsRunning_ = true;
    tabsPattern->UpdateSelectedState(swiperNode, tabBarPattern, tabsLayoutProperty, 101);

    auto swiperLayoutProperty = swiperNode->GetLayoutProperty<SwiperLayoutProperty>();
    ASSERT_NE(swiperLayoutProperty, nullptr);

    int32_t defaultIndexValue = 0;
    auto indexValue = swiperLayoutProperty->GetIndexValue(defaultIndexValue);
    EXPECT_NE(indexValue, 101);
}

/**
 * @tc.name: AddInnerOnGestureRecognizerJudgeBeginTest001
 * @tc.desc: AddInnerOnGestureRecognizerJudgeBegin
 * @tc.type: FUNC
 */
HWTEST_F(TabPatternTestNg, AddInnerOnGestureRecognizerJudgeBeginTest001, TestSize.Level1)
{
    auto tabsPattern = AceType::MakeRefPtr<TabsPattern>();
    ASSERT_NE(tabsPattern, nullptr);

    auto tabsNode = AceType::MakeRefPtr<TabsNode>(V2::TABS_ETS_TAG, 2, tabsPattern, true);
    ASSERT_NE(tabsNode, nullptr);

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_VOID(swiperNode);

    auto targetComponent = swiperNode->GetTargetComponent().Upgrade();
    CHECK_NULL_VOID(targetComponent);

    GestureRecognizerJudgeFunc gestureRecognizerJudgeFunc;
    tabsPattern->AddInnerOnGestureRecognizerJudgeBegin(std::move(gestureRecognizerJudgeFunc));
    EXPECT_TRUE(targetComponent->isInnerNodeGestureRecognizerJudgeSet_);
}

/**
 * @tc.name: RecoverInnerOnGestureRecognizerJudgeBeginTest001
 * @tc.desc: RecoverInnerOnGestureRecognizerJudgeBegin
 * @tc.type: FUNC
 */
HWTEST_F(TabPatternTestNg, RecoverInnerOnGestureRecognizerJudgeBeginTest001, TestSize.Level1)
{
    auto tabsPattern = AceType::MakeRefPtr<TabsPattern>();
    ASSERT_NE(tabsPattern, nullptr);

    auto tabsNode = AceType::MakeRefPtr<TabsNode>(V2::TABS_ETS_TAG, 2, tabsPattern, true);
    ASSERT_NE(tabsNode, nullptr);

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_VOID(swiperNode);

    auto targetComponent = swiperNode->GetTargetComponent().Upgrade();
    CHECK_NULL_VOID(targetComponent);

    targetComponent->isInnerNodeGestureRecognizerJudgeSet_ = true;
    tabsPattern->RecoverInnerOnGestureRecognizerJudgeBegin();
    EXPECT_FALSE(targetComponent->isInnerNodeGestureRecognizerJudgeSet_);
}

/**
 * @tc.name: CalculateFrontChildrenMainSizeTest001
 * @tc.desc: test CalculateFrontChildrenMainSize
 * @tc.type: FUNC
 */
HWTEST_F(TabPatternTestNg, CalculateFrontChildrenMainSizeTest001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    model.SetTabBarMode(TabBarMode::SCROLLABLE);
    model.SetIsVertical(false);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    tabBarPattern_->visibleItemPosition_.clear();
    tabBarPattern_->visibleItemPosition_[0] = { -1.0f, 1.0f };
    tabBarPattern_->visibleItemPosition_[1] = { 1.0f, 2.0f };
    tabBarPattern_->CalculateTargetOffset(0);
    EXPECT_NE(tabBarPattern_->visibleItemPosition_.find(0), tabBarPattern_->visibleItemPosition_.end());

    tabBarPattern_->visibleItemPosition_.clear();
    tabBarPattern_->scrollMargin_ = 365.0f;
    tabBarPattern_->CalculateTargetOffset(1);
    auto backChildrenMainSize = tabBarPattern_->CalculateFrontChildrenMainSize(1);
    auto space = tabBarPattern_->GetSpace(1);
    EXPECT_EQ(LessOrEqual(backChildrenMainSize, space), false);
}

/**
 * @tc.name: InitFocusEvent001
 * @tc.desc: GetTargetIndex
 * @tc.type: FUNC
 */
HWTEST_F(TabPatternTestNg, InitFocusEvent001, TestSize.Level1)
{
    auto tabsPattern = AceType::MakeRefPtr<TabsPattern>();
    ASSERT_NE(tabsPattern, nullptr);

    auto tabsNode = AceType::MakeRefPtr<TabsNode>(V2::TABS_ETS_TAG, 2, tabsPattern, true);
    ASSERT_NE(tabsNode, nullptr);

    auto tabsFocusHub = tabsNode->GetFocusHub();
    CHECK_NULL_VOID(tabsFocusHub);

    tabsPattern->InitFocusEvent();
    EXPECT_NE(tabsFocusHub->onGetNextFocusNodeFunc_, nullptr);
}

/**
 * @tc.name: InitFocusEvent001
 * @tc.desc: GetTargetIndex
 * @tc.type: FUNC
 */
HWTEST_F(TabPatternTestNg, GetCurrentFocusNode001, TestSize.Level1)
{
    auto tabsPattern = AceType::MakeRefPtr<TabsPattern>();
    ASSERT_NE(tabsPattern, nullptr);

    auto tabsNode = AceType::MakeRefPtr<TabsNode>(V2::TABS_ETS_TAG, 2, tabsPattern, true);
    ASSERT_NE(tabsNode, nullptr);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_VOID(tabBarNode);

    auto tabBarFocusHub = tabBarNode->GetFocusHub();
    CHECK_NULL_VOID(tabBarFocusHub);

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_VOID(swiperNode);

    auto swiperFocusHub = swiperNode->GetFocusHub();
    ASSERT_NE(swiperFocusHub, nullptr);

    auto property = tabsNode->GetLayoutProperty<TabsLayoutProperty>();
    ASSERT_NE(property, nullptr);

    property->propTabBarPosition_ = BarPosition::START;
    auto firstFocusHub = tabsPattern->GetCurrentFocusNode(FocusIntension::TAB);
    EXPECT_EQ(firstFocusHub, tabBarFocusHub);
}

/**
 * @tc.name: InitFocusEvent001
 * @tc.desc: GetTargetIndex
 * @tc.type: FUNC
 */
HWTEST_F(TabPatternTestNg, GetCurrentFocusNode002, TestSize.Level1)
{
    auto tabsPattern = AceType::MakeRefPtr<TabsPattern>();
    ASSERT_NE(tabsPattern, nullptr);

    auto tabsNode = AceType::MakeRefPtr<TabsNode>(V2::TABS_ETS_TAG, 2, tabsPattern, true);
    ASSERT_NE(tabsNode, nullptr);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_VOID(tabBarNode);

    auto tabBarFocusHub = tabBarNode->GetFocusHub();
    CHECK_NULL_VOID(tabBarFocusHub);

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_VOID(swiperNode);

    auto swiperFocusHub = swiperNode->GetFocusHub();
    ASSERT_NE(swiperFocusHub, nullptr);

    auto property = tabsNode->GetLayoutProperty<TabsLayoutProperty>();
    ASSERT_NE(property, nullptr);

    property->propTabBarPosition_ = BarPosition::END;
    auto firstFocusHub = tabsPattern->GetCurrentFocusNode(FocusIntension::TAB);
    EXPECT_EQ(firstFocusHub, swiperFocusHub);
}

/**
 * @tc.name: InitFocusEvent001
 * @tc.desc: GetTargetIndex
 * @tc.type: FUNC
 */
HWTEST_F(TabPatternTestNg, GetCurrentFocusNode003, TestSize.Level1)
{
    auto tabsPattern = AceType::MakeRefPtr<TabsPattern>();
    ASSERT_NE(tabsPattern, nullptr);

    auto tabsNode = AceType::MakeRefPtr<TabsNode>(V2::TABS_ETS_TAG, 2, tabsPattern, true);
    ASSERT_NE(tabsNode, nullptr);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_VOID(tabBarNode);

    auto tabBarFocusHub = tabBarNode->GetFocusHub();
    CHECK_NULL_VOID(tabBarFocusHub);

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_VOID(swiperNode);

    auto swiperFocusHub = swiperNode->GetFocusHub();
    CHECK_NULL_VOID(swiperFocusHub);

    auto property = tabsNode->GetLayoutProperty<TabsLayoutProperty>();
    ASSERT_NE(property, nullptr);

    property->propTabBarPosition_ = BarPosition::START;
    auto lastFocusHub = tabsPattern->GetCurrentFocusNode(FocusIntension::RIGHT);
    EXPECT_EQ(lastFocusHub, swiperFocusHub);
}

/**
 * @tc.name: InitFocusEvent001
 * @tc.desc: GetTargetIndex
 * @tc.type: FUNC
 */
HWTEST_F(TabPatternTestNg, GetCurrentFocusNode004, TestSize.Level1)
{
    auto tabsPattern = AceType::MakeRefPtr<TabsPattern>();
    ASSERT_NE(tabsPattern, nullptr);

    auto tabsNode = AceType::MakeRefPtr<TabsNode>(V2::TABS_ETS_TAG, 2, tabsPattern, true);
    ASSERT_NE(tabsNode, nullptr);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_VOID(tabBarNode);

    auto tabBarFocusHub = tabBarNode->GetFocusHub();
    CHECK_NULL_VOID(tabBarFocusHub);

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_VOID(swiperNode);

    auto swiperFocusHub = swiperNode->GetFocusHub();
    ASSERT_NE(swiperFocusHub, nullptr);

    auto property = tabsNode->GetLayoutProperty<TabsLayoutProperty>();
    ASSERT_NE(property, nullptr);

    property->propTabBarPosition_ = BarPosition::END;
    auto lastFocusHub = tabsPattern->GetCurrentFocusNode(FocusIntension::RIGHT);
    EXPECT_EQ(lastFocusHub, tabBarFocusHub);
}

/**
 * @tc.name: InitFocusEvent001
 * @tc.desc: GetTargetIndex
 * @tc.type: FUNC
 */
HWTEST_F(TabPatternTestNg, InitAccessibilityZIndexTest001, TestSize.Level1)
{
    auto tabsPattern = AceType::MakeRefPtr<TabsPattern>();
    ASSERT_NE(tabsPattern, nullptr);

    auto tabsNode = AceType::MakeRefPtr<TabsNode>(V2::TABS_ETS_TAG, 2, tabsPattern, true);
    ASSERT_NE(tabsNode, nullptr);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_VOID(tabBarNode);

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_VOID(swiperNode);

    auto swiperAccessibilityProperty = swiperNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
    ASSERT_NE(swiperAccessibilityProperty, nullptr);

    auto property = tabsNode->GetLayoutProperty<TabsLayoutProperty>();
    ASSERT_NE(property, nullptr);

    property->propTabBarPosition_ = BarPosition::START;
    tabsPattern->InitAccessibilityZIndex();
    auto index = swiperAccessibilityProperty->GetAccessibilityZIndex();
    EXPECT_EQ(index, 1);
}

/**
 * @tc.name: InitFocusEvent001
 * @tc.desc: GetTargetIndex
 * @tc.type: FUNC
 */
HWTEST_F(TabPatternTestNg, InitAccessibilityZIndexTest002, TestSize.Level1)
{
    auto tabsPattern = AceType::MakeRefPtr<TabsPattern>();
    ASSERT_NE(tabsPattern, nullptr);

    auto tabsNode = AceType::MakeRefPtr<TabsNode>(V2::TABS_ETS_TAG, 2, tabsPattern, true);
    ASSERT_NE(tabsNode, nullptr);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_VOID(tabBarNode);

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_VOID(swiperNode);

    auto swiperAccessibilityProperty = swiperNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
    ASSERT_NE(swiperAccessibilityProperty, nullptr);

    auto property = tabsNode->GetLayoutProperty<TabsLayoutProperty>();
    ASSERT_NE(property, nullptr);

    property->propTabBarPosition_ = BarPosition::END;
    tabsPattern->InitAccessibilityZIndex();
    auto index = swiperAccessibilityProperty->GetAccessibilityZIndex();
    EXPECT_EQ(index, 0);
}

/**
 * @tc.name: InitFocusEvent001
 * @tc.desc: GetTargetIndex
 * @tc.type: FUNC
 */
HWTEST_F(TabPatternTestNg, InitAccessibilityZIndexTest003, TestSize.Level1)
{
    auto tabsPattern = AceType::MakeRefPtr<TabsPattern>();
    ASSERT_NE(tabsPattern, nullptr);

    auto tabsNode = AceType::MakeRefPtr<TabsNode>(V2::TABS_ETS_TAG, 2, tabsPattern, true);
    ASSERT_NE(tabsNode, nullptr);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_VOID(tabBarNode);

    auto tabBarFocusHub = tabBarNode->GetFocusHub();
    ASSERT_NE(tabBarFocusHub, nullptr);

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_VOID(swiperNode);

    auto tabBarAccessibilityProperty = tabBarNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
    ASSERT_NE(tabBarAccessibilityProperty, nullptr);

    auto property = tabsNode->GetLayoutProperty<TabsLayoutProperty>();
    ASSERT_NE(property, nullptr);

    property->propTabBarPosition_ = BarPosition::START;
    tabsPattern->InitAccessibilityZIndex();
    auto index = tabBarAccessibilityProperty->GetAccessibilityZIndex();
    EXPECT_EQ(index, 0);
}

/**
 * @tc.name: InitFocusEvent001
 * @tc.desc: GetTargetIndex
 * @tc.type: FUNC
 */
HWTEST_F(TabPatternTestNg, InitAccessibilityZIndexTest004, TestSize.Level1)
{
    auto tabsPattern = AceType::MakeRefPtr<TabsPattern>();
    ASSERT_NE(tabsPattern, nullptr);

    auto tabsNode = AceType::MakeRefPtr<TabsNode>(V2::TABS_ETS_TAG, 2, tabsPattern, true);
    ASSERT_NE(tabsNode, nullptr);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_VOID(tabBarNode);

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_VOID(swiperNode);

    auto tabBarAccessibilityProperty = tabBarNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
    ASSERT_NE(tabBarAccessibilityProperty, nullptr);

    auto property = tabsNode->GetLayoutProperty<TabsLayoutProperty>();
    ASSERT_NE(property, nullptr);

    property->propTabBarPosition_ = BarPosition::END;
    tabsPattern->InitAccessibilityZIndex();
    auto index = tabBarAccessibilityProperty->GetAccessibilityZIndex();
    EXPECT_EQ(index, 1);
}

/**
 * @tc.name: InitFocusEvent001
 * @tc.desc: GetTargetIndex
 * @tc.type: FUNC
 */
HWTEST_F(TabPatternTestNg, FireTabContentStateCallbackTest001, TestSize.Level1)
{
    auto tabsPattern = AceType::MakeRefPtr<TabsPattern>();
    ASSERT_NE(tabsPattern, nullptr);

    auto tabsNode = AceType::MakeRefPtr<TabsNode>(V2::TABS_ETS_TAG, 2, tabsPattern, true);
    ASSERT_NE(tabsNode, nullptr);

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_VOID(swiperNode);

    int32_t oldIndex = 1;
    int32_t nextIndex = 1;

    tabsPattern->FireTabContentStateCallback(oldIndex, nextIndex);
    auto oldTabContentFunc = UIObserverHandler::GetInstance().tabContentStateHandleFunc_;
    EXPECT_NE(oldTabContentFunc, nullptr);

    auto nextTabContentFunc = UIObserverHandler::GetInstance().tabContentStateHandleFunc_;
    EXPECT_NE(nextTabContentFunc, nullptr);
}

/**
 * @tc.name: InitFocusEvent001
 * @tc.desc: GetTargetIndex
 * @tc.type: FUNC
 */
HWTEST_F(TabPatternTestNg, FireTabContentStateCallbackTest002, TestSize.Level1)
{
    auto tabsPattern = AceType::MakeRefPtr<TabsPattern>();
    ASSERT_NE(tabsPattern, nullptr);

    auto tabsNode = AceType::MakeRefPtr<TabsNode>(V2::TABS_ETS_TAG, 2, tabsPattern, true);
    ASSERT_NE(tabsNode, nullptr);

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_VOID(swiperNode);

    int32_t oldIndex = -1;
    int32_t nextIndex = -1;

    tabsPattern->FireTabContentStateCallback(oldIndex, nextIndex);
    auto oldTabContentFunc = UIObserverHandler::GetInstance().tabContentStateHandleFunc_;
    EXPECT_EQ(oldTabContentFunc, nullptr);

    auto nextTabContentFunc = UIObserverHandler::GetInstance().tabContentStateHandleFunc_;
    EXPECT_EQ(nextTabContentFunc, nullptr);
}

/**
 * @tc.name: InitFocusEvent001
 * @tc.desc: GetTargetIndex
 * @tc.type: FUNC
 */
HWTEST_F(TabPatternTestNg, FireTabContentStateCallbackTest003, TestSize.Level1)
{
    auto tabsPattern = AceType::MakeRefPtr<TabsPattern>();
    ASSERT_NE(tabsPattern, nullptr);

    auto tabsNode = AceType::MakeRefPtr<TabsNode>(V2::TABS_ETS_TAG, 2, tabsPattern, true);
    ASSERT_NE(tabsNode, nullptr);

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_VOID(swiperNode);

    auto child = swiperNode->GetChildren();
    auto oldIndex = static_cast<int32_t>(child.size());
    int32_t nextIndex = 1;

    tabsPattern->FireTabContentStateCallback(oldIndex, nextIndex);
    auto oldTabContentFunc = UIObserverHandler::GetInstance().tabContentStateHandleFunc_;
    EXPECT_EQ(oldTabContentFunc, nullptr);

    auto nextTabContentFunc = UIObserverHandler::GetInstance().tabContentStateHandleFunc_;
    EXPECT_NE(nextTabContentFunc, nullptr);
}

/**
 * @tc.name: InitFocusEvent001
 * @tc.desc: GetTargetIndex
 * @tc.type: FUNC
 */
HWTEST_F(TabPatternTestNg, FireTabContentStateCallbackTest004, TestSize.Level1)
{
    auto tabsPattern = AceType::MakeRefPtr<TabsPattern>();
    ASSERT_NE(tabsPattern, nullptr);

    auto tabsNode = AceType::MakeRefPtr<TabsNode>(V2::TABS_ETS_TAG, 2, tabsPattern, true);
    ASSERT_NE(tabsNode, nullptr);

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_VOID(swiperNode);

    auto child = swiperNode->GetChildren();
    auto oldIndex = 1;
    auto nextIndex = static_cast<int32_t>(child.size());

    tabsPattern->FireTabContentStateCallback(oldIndex, nextIndex);
    auto oldTabContentFunc = UIObserverHandler::GetInstance().tabContentStateHandleFunc_;
    EXPECT_NE(oldTabContentFunc, nullptr);

    auto nextTabContentFunc = UIObserverHandler::GetInstance().tabContentStateHandleFunc_;
    EXPECT_EQ(nextTabContentFunc, nullptr);
}

/**
 * @tc.name: InitFocusEvent001
 * @tc.desc: GetTargetIndex
 * @tc.type: FUNC
 */
HWTEST_F(TabPatternTestNg, RecordChangeEventTest001, TestSize.Level1)
{
    auto tabsPattern = AceType::MakeRefPtr<TabsPattern>();
    ASSERT_NE(tabsPattern, nullptr);

    auto tabsNode = AceType::MakeRefPtr<TabsNode>(V2::TABS_ETS_TAG, 2, tabsPattern, true);
    ASSERT_NE(tabsNode, nullptr);

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_VOID(swiperNode);

    int32_t index = 1;
    auto indexStr = tabsPattern->GetTabBarTextByIndex(index);

    EXPECT_NE(indexStr.c_str(), "");
}

/**
 * @tc.name: ProvideRestoreInfoTest001
 * @tc.desc: GetTargetIndex
 * @tc.type: FUNC
 */
HWTEST_F(TabPatternTestNg, ProvideRestoreInfoTest001, TestSize.Level1)
{
    auto tabsPattern = AceType::MakeRefPtr<TabsPattern>();
    ASSERT_NE(tabsPattern, nullptr);

    auto tabsNode = AceType::MakeRefPtr<TabsNode>(V2::TABS_ETS_TAG, 2, tabsPattern, true);
    ASSERT_NE(tabsNode, nullptr);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_VOID(tabBarNode);

    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    CHECK_NULL_VOID(tabBarPattern);

    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_VOID(tabBarLayoutProperty);

    int32_t index = 0;
    tabBarPattern->SetIndicator(index);
    auto indexStr = tabsPattern->ProvideRestoreInfo();
    EXPECT_NE(indexStr.c_str(), "{index: 1}");
}

/**
 * @tc.name: OnColorModeChangeTest001
 * @tc.desc: OnColorModeChange
 * @tc.type: FUNC
 */
HWTEST_F(TabPatternTestNg, OnColorModeChangeTest001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);

    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    ASSERT_NE(tabsNode, nullptr);

    auto tabsPattern = tabsNode->GetPattern<TabsPattern>();
    ASSERT_NE(tabsPattern, nullptr);

    auto tabsLayoutProperty = tabsNode->GetLayoutProperty<TabsLayoutProperty>();
    ASSERT_NE(tabsLayoutProperty, nullptr);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);

    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    auto pipeline = PipelineContext::GetCurrentContextPtrSafelyWithCheck();
    ASSERT_NE(pipeline, nullptr);

    auto dividerFrameNode = AceType::DynamicCast<FrameNode>(tabsNode->GetDivider());
    ASSERT_NE(dividerFrameNode, nullptr);

    auto dividerRenderProperty = dividerFrameNode->GetPaintProperty<DividerRenderProperty>();
    ASSERT_NE(dividerRenderProperty, nullptr);

    int32_t colorMode = static_cast<int32_t>(ColorMode::DARK);
    tabsPattern->OnColorModeChange(colorMode);
    tabsLayoutProperty->propDividerColorSetByUser_ = false;
    auto value = dividerRenderProperty->GetDividerColorSetByUserValue(false);
    EXPECT_EQ(value, true);

    tabsPattern->OnColorModeChange(colorMode);
    tabsLayoutProperty->propDividerColorSetByUser_ = true;
    auto newValue = dividerRenderProperty->GetDividerColorSetByUserValue(true);
    EXPECT_EQ(newValue, false);
}

/**
 * @tc.name: OnColorModeChangeTest002
 * @tc.desc: OnColorModeChange
 * @tc.type: FUNC
 */
HWTEST_F(TabPatternTestNg, OnColorModeChangeTest002, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);

    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    ASSERT_NE(tabsNode, nullptr);

    auto tabsPattern = tabsNode->GetPattern<TabsPattern>();
    ASSERT_NE(tabsPattern, nullptr);

    auto tabsLayoutProperty = tabsNode->GetLayoutProperty<TabsLayoutProperty>();
    ASSERT_NE(tabsLayoutProperty, nullptr);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);

    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    auto pipeline = PipelineContext::GetCurrentContextPtrSafelyWithCheck();
    ASSERT_NE(pipeline, nullptr);

    auto dividerFrameNode = AceType::DynamicCast<FrameNode>(tabsNode->GetDivider());
    ASSERT_NE(dividerFrameNode, nullptr);

    auto dividerRenderProperty = dividerFrameNode->GetPaintProperty<DividerRenderProperty>();
    ASSERT_NE(dividerRenderProperty, nullptr);

    int32_t colorMode = static_cast<int32_t>(ColorMode::DARK);
    tabsPattern->OnColorModeChange(colorMode);

    auto tabBarRenderContext = tabBarNode->GetRenderContext();
    ASSERT_NE(tabBarRenderContext, nullptr);

    auto result = tabBarRenderContext->HasBackgroundColor();
    EXPECT_EQ(result, true);

    Color defaultColor = Color::BLUE;
    auto value = tabBarRenderContext->GetBackgroundColorValue(defaultColor);
    EXPECT_EQ(value, Color::BLACK);
}

/**
 * @tc.name: GetAnimationModeTest001
 * @tc.desc: GetAnimationMode
 * @tc.type: FUNC
 */
HWTEST_F(TabPatternTestNg, GetAnimationModeTest001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);

    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    ASSERT_NE(tabsNode, nullptr);

    auto tabsPattern = tabsNode->GetPattern<TabsPattern>();
    ASSERT_NE(tabsPattern, nullptr);

    tabsPattern->animateMode_ = TabAnimateMode::CONTENT_FIRST;
    auto result = tabsNode->GetAnimationMode();
    EXPECT_EQ(result, "AnimationMode.CONTENT_FIRST");
}

/**
 * @tc.name: GetAnimationModeTest002
 * @tc.desc: GetAnimationMode
 * @tc.type: FUNC
 */
HWTEST_F(TabPatternTestNg, GetAnimationModeTest002, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);

    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    ASSERT_NE(tabsNode, nullptr);

    auto tabsPattern = tabsNode->GetPattern<TabsPattern>();
    ASSERT_NE(tabsPattern, nullptr);

    tabsPattern->animateMode_ = TabAnimateMode::ACTION_FIRST;
    auto result = tabsNode->GetAnimationMode();
    EXPECT_EQ(result, "AnimationMode.ACTION_FIRST");
}

/**
 * @tc.name: GetAnimationModeTest003
 * @tc.desc: GetAnimationMode
 * @tc.type: FUNC
 */
HWTEST_F(TabPatternTestNg, GetAnimationModeTest003, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);

    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    ASSERT_NE(tabsNode, nullptr);

    auto tabsPattern = tabsNode->GetPattern<TabsPattern>();
    ASSERT_NE(tabsPattern, nullptr);

    tabsPattern->animateMode_ = TabAnimateMode::NO_ANIMATION;
    auto result = tabsNode->GetAnimationMode();
    EXPECT_EQ(result, "AnimationMode.NO_ANIMATION");
}

/**
 * @tc.name: GetAnimationModeTest004
 * @tc.desc: GetAnimationMode
 * @tc.type: FUNC
 */
HWTEST_F(TabPatternTestNg, GetAnimationModeTest004, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);

    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    ASSERT_NE(tabsNode, nullptr);

    auto tabsPattern = tabsNode->GetPattern<TabsPattern>();
    ASSERT_NE(tabsPattern, nullptr);

    tabsPattern->animateMode_ = TabAnimateMode::CONTENT_FIRST_WITH_JUMP;
    auto result = tabsNode->GetAnimationMode();
    EXPECT_EQ(result, "AnimationMode.CONTENT_FIRST_WITH_JUMP");
}

/**
 * @tc.name: GetAnimationModeTest004
 * @tc.desc: GetAnimationMode
 * @tc.type: FUNC
 */
HWTEST_F(TabPatternTestNg, GetAnimationModeTest005, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);

    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    ASSERT_NE(tabsNode, nullptr);

    auto tabsPattern = tabsNode->GetPattern<TabsPattern>();
    ASSERT_NE(tabsPattern, nullptr);

    tabsPattern->animateMode_ = TabAnimateMode::ACTION_FIRST_WITH_JUMP;
    auto result = tabsNode->GetAnimationMode();
    EXPECT_EQ(result, "AnimationMode.ACTION_FIRST_WITH_JUMP");
}

/**
 * @tc.name: GetAnimationModeTest005
 * @tc.desc: GetAnimationMode
 * @tc.type: FUNC
 */
HWTEST_F(TabPatternTestNg, GetAnimationModeTest006, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);

    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    ASSERT_NE(tabsNode, nullptr);

    auto tabsPattern = tabsNode->GetPattern<TabsPattern>();
    ASSERT_NE(tabsPattern, nullptr);

    tabsPattern->animateMode_ = TabAnimateMode::MAX_VALUE;
    auto result = tabsNode->GetAnimationMode();
    EXPECT_EQ(result, "AnimationMode.CONTENT_FIRST");
}

/**
 * @tc.name: GetEdgeEffectTest001
 * @tc.desc: GetEdgeEffect
 * @tc.type: FUNC
 */
HWTEST_F(TabPatternTestNg, GetEdgeEffectTest001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);

    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    ASSERT_NE(tabsNode, nullptr);

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    ASSERT_NE(swiperNode, nullptr);

    auto swiperPaintProperty = swiperNode->GetPaintProperty<SwiperPaintProperty>();
    ASSERT_NE(swiperPaintProperty, nullptr);

    swiperPaintProperty->propEdgeEffect_ = EdgeEffect::SPRING;
    auto result = tabsNode->GetEdgeEffect();
    EXPECT_NE(result, "EdgeEffect::SPRING");
}

/**
 * @tc.name: GetEdgeEffectTest002
 * @tc.desc: GetEdgeEffect
 * @tc.type: FUNC
 */
HWTEST_F(TabPatternTestNg, GetEdgeEffectTest002, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);

    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    ASSERT_NE(tabsNode, nullptr);

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    ASSERT_NE(swiperNode, nullptr);

    auto swiperPaintProperty = swiperNode->GetPaintProperty<SwiperPaintProperty>();
    ASSERT_NE(swiperPaintProperty, nullptr);

    swiperPaintProperty->propEdgeEffect_ = EdgeEffect::FADE;
    auto result = tabsNode->GetEdgeEffect();
    EXPECT_NE(result, "EdgeEffect::FADE");
}

/**
 * @tc.name: GetEdgeEffectTest002
 * @tc.desc: GetEdgeEffect
 * @tc.type: FUNC
 */
HWTEST_F(TabPatternTestNg, GetEdgeEffectTest003, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);

    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    ASSERT_NE(tabsNode, nullptr);

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    ASSERT_NE(swiperNode, nullptr);

    auto swiperPaintProperty = swiperNode->GetPaintProperty<SwiperPaintProperty>();
    ASSERT_NE(swiperPaintProperty, nullptr);

    swiperPaintProperty->propEdgeEffect_ = EdgeEffect::NONE;
    auto result = tabsNode->GetEdgeEffect();
    EXPECT_NE(result, "EdgeEffect::NONE");
}

/**
 * @tc.name: GetEdgeEffectTest001
 * @tc.desc: GetEdgeEffect
 * @tc.type: FUNC
 */
HWTEST_F(TabPatternTestNg, GetEdgeEffectTest004, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);

    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    ASSERT_NE(tabsNode, nullptr);

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    ASSERT_NE(swiperNode, nullptr);

    auto swiperPaintProperty = swiperNode->GetPaintProperty<SwiperPaintProperty>();
    ASSERT_NE(swiperPaintProperty, nullptr);

    auto result = swiperPaintProperty->propEdgeEffect_.has_value();
    ;
    EXPECT_NE(result, false);
}

/**
 * @tc.name: GetCurrentOffset001
 * @tc.desc: GetCurrentOffset
 * @tc.type: FUNC
 */
HWTEST_F(TabPatternTestNg, GetCurrentOffsetTest001, TestSize.Level1)
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

    auto tabbarLayoutAlgorithm =
        AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarNode->GetPattern<TabBarPattern>()->CreateLayoutAlgorithm());
    ASSERT_NE(tabbarLayoutAlgorithm, nullptr);

    ScrollableBarModeOptions layoutStyle;
    layoutStyle.nonScrollableLayoutStyle = LayoutStyle::ALWAYS_AVERAGE_SPLIT;
    tabbarLayoutAlgorithm->contentMainSize_ = 100.0f;
    tabbarLayoutAlgorithm->visibleChildrenMainSize_ = 20.0f;
    auto currentOffset = tabbarLayoutAlgorithm->GetCurrentOffset(tabBarLayoutProperty, layoutStyle);
    EXPECT_EQ(currentOffset, 40.0f);
}

/**
 * @tc.name: GetCurrentOffset002
 * @tc.desc: GetCurrentOffset
 * @tc.type: FUNC
 */
HWTEST_F(TabPatternTestNg, GetCurrentOffsetTest002, TestSize.Level1)
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

    auto tabbarLayoutAlgorithm =
        AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarNode->GetPattern<TabBarPattern>()->CreateLayoutAlgorithm());
    ASSERT_NE(tabbarLayoutAlgorithm, nullptr);

    auto margin = 100.0f;
    ScrollableBarModeOptions option;
    option.margin = Dimension(margin);

    ScrollableBarModeOptions layoutStyle;
    tabbarLayoutAlgorithm->axis_ = Axis::HORIZONTAL;
    tabbarLayoutAlgorithm->contentMainSize_ = 100.0f;
    tabbarLayoutAlgorithm->visibleChildrenMainSize_ = 20.0f;
    auto currentOffset = tabbarLayoutAlgorithm->GetCurrentOffset(tabBarLayoutProperty, layoutStyle);
    EXPECT_EQ(currentOffset, 1.0f);
}

/**
 * @tc.name: GetCurrentOffset003
 * @tc.desc: GetCurrentOffset
 * @tc.type: FUNC
 */
HWTEST_F(TabPatternTestNg, GetCurrentOffsetTest003, TestSize.Level1)
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

    auto tabbarLayoutAlgorithm =
        AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarNode->GetPattern<TabBarPattern>()->CreateLayoutAlgorithm());
    ASSERT_NE(tabbarLayoutAlgorithm, nullptr);

    auto margin = 100.0f;
    ScrollableBarModeOptions option;
    option.margin = Dimension(margin);

    ScrollableBarModeOptions layoutStyle;
    tabbarLayoutAlgorithm->axis_ = Axis::VERTICAL;
    tabbarLayoutAlgorithm->contentMainSize_ = 100.0f;
    tabbarLayoutAlgorithm->visibleChildrenMainSize_ = 20.0f;
    auto currentOffset = tabbarLayoutAlgorithm->GetCurrentOffset(tabBarLayoutProperty, layoutStyle);
    EXPECT_EQ(currentOffset, 40.0f);
}

/**
 * @tc.name: CheckBorderAndPaddingTest001
 * @tc.desc: CheckBorderAndPadding
 * @tc.type: FUNC
 */
HWTEST_F(TabPatternTestNg, CheckBorderAndPaddingTest001, TestSize.Level1)
{
    auto nodeId = ViewStackProcessor::GetInstance()->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::TABS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TabsPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(frameNode);

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);

    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    CHECK_NULL_VOID(tabsNode);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);

    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    auto tabbarLayoutAlgorithm =
        AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarNode->GetPattern<TabBarPattern>()->CreateLayoutAlgorithm());
    ASSERT_NE(tabbarLayoutAlgorithm, nullptr);

    SizeF frameSize;
    float width = 1.0f;
    float height = 1.0f;
    frameSize.SetWidth(width);
    frameSize.SetWidth(height);

    PaddingPropertyF padding = { 1.0f, 1.0f, 1.0f, 1.0f };
    tabbarLayoutAlgorithm->CheckBorderAndPadding(frameSize, padding);
    EXPECT_EQ(frameSize.Width(), 2.0f);
    EXPECT_EQ(frameSize.Height(), 2.0f);
}

/**
 * @tc.name: CheckBorderAndPaddingTest002
 * @tc.desc: CheckBorderAndPadding
 * @tc.type: FUNC
 */
HWTEST_F(TabPatternTestNg, CheckBorderAndPaddingTest002, TestSize.Level1)
{
    auto nodeId = ViewStackProcessor::GetInstance()->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::TABS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TabsPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(frameNode);

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);

    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    CHECK_NULL_VOID(tabsNode);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);

    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    auto tabbarLayoutAlgorithm =
        AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarNode->GetPattern<TabBarPattern>()->CreateLayoutAlgorithm());
    ASSERT_NE(tabbarLayoutAlgorithm, nullptr);

    SizeF frameSize;
    float width = 2.0f;
    float height = 2.0f;
    frameSize.SetWidth(width);
    frameSize.SetWidth(height);

    PaddingPropertyF padding = { -1.0f, -1.0f, -1.0f, -1.0f };
    tabbarLayoutAlgorithm->CheckBorderAndPadding(frameSize, padding);
    EXPECT_EQ(frameSize.Width(), 2.0f);
    EXPECT_EQ(frameSize.Height(), 2.0f);
}

/**
 * @tc.name: NeedAdaptForAgingTest001
 * @tc.desc: NeedAdaptForAging
 * @tc.type: FUNC
 */
HWTEST_F(TabPatternTestNg, NeedAdaptForAgingTest001, TestSize.Level1)
{
    auto nodeId = ViewStackProcessor::GetInstance()->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::TABS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TabsPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(frameNode);

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);

    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    CHECK_NULL_VOID(tabsNode);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);

    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    auto tabbarLayoutAlgorithm =
        AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarNode->GetPattern<TabBarPattern>()->CreateLayoutAlgorithm());
    ASSERT_NE(tabbarLayoutAlgorithm, nullptr);

    auto pipeline = tabBarNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->fontScale_ = 1.0f;

    auto result = tabbarLayoutAlgorithm->NeedAdaptForAging(tabBarNode);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: NeedAdaptForAgingTest002
 * @tc.desc: NeedAdaptForAging
 * @tc.type: FUNC
 */
HWTEST_F(TabPatternTestNg, NeedAdaptForAgingTest002, TestSize.Level1)
{
    auto nodeId = ViewStackProcessor::GetInstance()->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::TABS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TabsPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(frameNode);

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);

    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    CHECK_NULL_VOID(tabsNode);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);

    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    auto tabbarLayoutAlgorithm =
        AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarNode->GetPattern<TabBarPattern>()->CreateLayoutAlgorithm());
    ASSERT_NE(tabbarLayoutAlgorithm, nullptr);

    auto pipeline = tabBarNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->fontScale_ = 2.0f;

    auto result = tabbarLayoutAlgorithm->NeedAdaptForAging(tabBarNode);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: GetNoMinHeightLimitTest001
 * @tc.desc: GetNoMinHeightLimit
 * @tc.type: FUNC
 */
HWTEST_F(TabPatternTestNg, GetNoMinHeightLimitTest001, TestSize.Level1)
{
    auto nodeId = ViewStackProcessor::GetInstance()->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::TABS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TabsPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(frameNode);

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);

    auto tabsNode = AceType::DynamicCast<TabsNode>(element);
    CHECK_NULL_VOID(tabsNode);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);

    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);

    auto tabbarLayoutAlgorithm =
        AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarNode->GetPattern<TabBarPattern>()->CreateLayoutAlgorithm());
    ASSERT_NE(tabbarLayoutAlgorithm, nullptr);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);

    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(tabBarNode, geometryNode, tabBarNode->GetLayoutProperty());
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabbarLayoutAlgorithm));

    auto pipeline = tabBarNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->fontScale_ = 2.0f;

    bool result = false;
    tabbarLayoutAlgorithm->tabBarStyle_ = TabBarStyle::SUBTABBATSTYLE;
    result = tabbarLayoutAlgorithm->GetNoMinHeightLimit(&layoutWrapper);
    EXPECT_EQ(result, true);

    tabbarLayoutAlgorithm->tabBarStyle_ = TabBarStyle::BOTTOMTABBATSTYLE;
    result = tabbarLayoutAlgorithm->GetNoMinHeightLimit(&layoutWrapper);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: GetIsCustomAnimationTest001
 * @tc.desc: GetIsCustomAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TabPatternTestNg, GetIsCustomAnimationTest001, TestSize.Level1)
{
    auto tabsPattern = AceType::MakeRefPtr<TabsPattern>();
    ASSERT_NE(tabsPattern, nullptr);

    bool isCustomAnimation = true;
    tabsPattern->SetIsCustomAnimation(isCustomAnimation);

    EXPECT_EQ(tabsPattern->GetIsCustomAnimation(), true);
}
} // namespace OHOS::Ace::NG