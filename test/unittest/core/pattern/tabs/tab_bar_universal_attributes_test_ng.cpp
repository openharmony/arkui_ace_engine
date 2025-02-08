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
#include "core/components/common/properties/alignment.h"

namespace OHOS::Ace::NG {
class TabBarUniversalAttributeTestNg : public TabsTestNg {
public:
};

/**
 * @tc.name: TabBarAlignTest001
 * @tc.desc: test align in horizontal direction
 * @tc.type: FUNC
 */
HWTEST_F(TabBarUniversalAttributeTestNg, TabBarAlignTest001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    model.SetTabBarMode(TabBarMode::SCROLLABLE);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    auto itemWidth = 20.0f;
    for (int32_t index = 0; index < TABCONTENT_NUMBER; index++) {
        auto child = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(index));
        ViewAbstract::SetWidth(AceType::RawPtr(child), CalcLength(itemWidth));
    }
    tabBarNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->second.startPos, 320.0f);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->second.endPos, 340.0f);

    ViewAbstract::SetAlign(AceType::RawPtr(tabBarNode_), Alignment::CENTER_LEFT);
    tabBarNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->second.startPos, 0.0f);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->second.endPos, 20.0f);

    ViewAbstract::SetAlign(AceType::RawPtr(tabBarNode_), Alignment::CENTER_RIGHT);
    tabBarNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->second.startPos, 640.0f);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->second.endPos, 660.0f);
}

/**
 * @tc.name: TabBarAlignTest002
 * @tc.desc: test align in horizontal direction with barMargin
 * @tc.type: FUNC
 */
HWTEST_F(TabBarUniversalAttributeTestNg, TabBarAlignTest002, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    model.SetTabBarMode(TabBarMode::SCROLLABLE);
    ScrollableBarModeOptions layoutStyle;
    layoutStyle.margin = 10.0_px;
    model.SetScrollableBarModeOptions(layoutStyle);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    auto itemWidth = 20.0f;
    for (int32_t index = 0; index < TABCONTENT_NUMBER; index++) {
        auto child = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(index));
        ViewAbstract::SetWidth(AceType::RawPtr(child), CalcLength(itemWidth));
    }
    tabBarNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->second.startPos, 320.0f);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->second.endPos, 340.0f);

    ViewAbstract::SetAlign(AceType::RawPtr(tabBarNode_), Alignment::CENTER_LEFT);
    tabBarNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->second.startPos, 10.0f);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->second.endPos, 30.0f);

    ViewAbstract::SetAlign(AceType::RawPtr(tabBarNode_), Alignment::CENTER_RIGHT);
    tabBarNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->second.startPos, 630.0f);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->second.endPos, 650.0f);
}

/**
 * @tc.name: TabBarAlignTest003
 * @tc.desc: test align in vertical direction
 * @tc.type: FUNC
 */
HWTEST_F(TabBarUniversalAttributeTestNg, TabBarAlignTest003, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    model.SetTabBarMode(TabBarMode::SCROLLABLE);
    ScrollableBarModeOptions layoutStyle;
    layoutStyle.margin = 10.0_px;
    layoutStyle.nonScrollableLayoutStyle = LayoutStyle::ALWAYS_AVERAGE_SPLIT;
    model.SetScrollableBarModeOptions(layoutStyle);
    model.SetIsVertical(true);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    auto itemHeight = 20.0f;
    for (int32_t index = 0; index < TABCONTENT_NUMBER; index++) {
        auto child = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(index));
        ViewAbstract::SetHeight(AceType::RawPtr(child), CalcLength(itemHeight));
    }
    tabBarNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->second.startPos, 160.0f);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->second.endPos, 180.0f);

    ViewAbstract::SetAlign(AceType::RawPtr(tabBarNode_), Alignment::TOP_CENTER);
    tabBarNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->second.startPos, 0.0f);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->second.endPos, 20.0f);

    ViewAbstract::SetAlign(AceType::RawPtr(tabBarNode_), Alignment::BOTTOM_CENTER);
    tabBarNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->second.startPos, 320.0f);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->second.endPos, 340.0f);
}

/**
 * @tc.name: TabBarAlignTest004
 * @tc.desc: test align in FIXED mode
 * @tc.type: FUNC
 */
HWTEST_F(TabBarUniversalAttributeTestNg, TabBarAlignTest004, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    model.SetTabBarMode(TabBarMode::FIXED);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    auto itemWidth = 20.0f;
    for (int32_t index = 0; index < TABCONTENT_NUMBER; index++) {
        auto child = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(index));
        ViewAbstract::SetWidth(AceType::RawPtr(child), CalcLength(itemWidth));
    }
    FlushUITasks();
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->second.startPos, 0.0f);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->second.endPos, 180.0f);

    ViewAbstract::SetAlign(AceType::RawPtr(tabBarNode_), Alignment::CENTER_LEFT);
    FlushUITasks();
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->second.startPos, 0.0f);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->second.endPos, 180.0f);

    ViewAbstract::SetAlign(AceType::RawPtr(tabBarNode_), Alignment::CENTER_RIGHT);
    FlushUITasks();
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->second.startPos, 0.0f);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->second.endPos, 180.0f);
}

/**
 * @tc.name: TabBarClipTest
 * @tc.desc: test clip
 * @tc.type: FUNC
 */
HWTEST_F(TabBarUniversalAttributeTestNg, TabBarClipTest, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    ViewAbstract::SetClipEdge(AceType::RawPtr(tabBarNode_), false);
    tabBarPattern_->OnModifyDone();
    EXPECT_FALSE(tabBarPattern_->clipEdge_);

    ViewAbstract::SetClipEdge(AceType::RawPtr(tabBarNode_), true);
    tabBarPattern_->OnModifyDone();
    EXPECT_TRUE(tabBarPattern_->clipEdge_);
}

/**
 * @tc.name: TabBarPaddingAndBorderTest001
 * @tc.desc: test padding and border
 * @tc.type: FUNC
 */
HWTEST_F(TabBarUniversalAttributeTestNg, TabBarPaddingAndBorderTest001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    model.SetTabBarHeight(50.0_px);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    ViewAbstract::SetPadding(AceType::RawPtr(tabBarNode_), CalcLength(5));
    FlushUITasks();
    EXPECT_EQ(tabBarPattern_->GetContentSize().Width(), 710.0f);
    EXPECT_EQ(tabBarPattern_->GetContentSize().Height(), 40.0f);
    auto childNode = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(0));
    EXPECT_NE(childNode, nullptr);
    auto childGeometryNode = childNode->GetGeometryNode();
    EXPECT_NE(childGeometryNode, nullptr);
    auto childOffset = childGeometryNode->GetMarginFrameOffset();
    EXPECT_EQ(childOffset.GetX(), 5.0f);
    EXPECT_EQ(childOffset.GetY(), 5.0f);

    ViewAbstract::SetSafeAreaPadding(AceType::RawPtr(tabBarNode_), CalcLength(5));
    FlushUITasks();
    EXPECT_EQ(tabBarPattern_->GetContentSize().Width(), 700.0f);
    EXPECT_EQ(tabBarPattern_->GetContentSize().Height(), 30.0f);
    childOffset = childGeometryNode->GetMarginFrameOffset();
    EXPECT_EQ(childOffset.GetX(), 10.0f);
    EXPECT_EQ(childOffset.GetY(), 10.0f);

    ViewAbstract::SetBorderWidth(AceType::RawPtr(tabBarNode_), 5.0_px);
    FlushUITasks();
    EXPECT_EQ(tabBarPattern_->GetContentSize().Width(), 690.0f);
    EXPECT_EQ(tabBarPattern_->GetContentSize().Height(), 20.0f);
    childOffset = childGeometryNode->GetMarginFrameOffset();
    EXPECT_EQ(childOffset.GetX(), 15.0f);
    EXPECT_EQ(childOffset.GetY(), 15.0f);
}

/**
 * @tc.name: TabBarPaddingAndBorderTest002
 * @tc.desc: test padding and border more than the frame size
 * @tc.type: FUNC
 */
HWTEST_F(TabBarUniversalAttributeTestNg, TabBarPaddingAndBorderTest002, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    auto geometryNode = tabBarNode_->GetGeometryNode();
    EXPECT_NE(geometryNode, nullptr);
    EXPECT_EQ(geometryNode->GetFrameSize().Width(), 720.0f);
    EXPECT_EQ(geometryNode->GetFrameSize().Height(), 56.0f);
    auto childNode = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(0));
    EXPECT_NE(childNode, nullptr);
    auto childGeometryNode = childNode->GetGeometryNode();
    EXPECT_NE(childGeometryNode, nullptr);

    ViewAbstract::SetPadding(AceType::RawPtr(tabBarNode_), CalcLength(30));
    FlushUITasks();
    EXPECT_EQ(geometryNode->GetFrameSize().Width(), 720.0f);
    EXPECT_EQ(geometryNode->GetFrameSize().Height(), 60.0f);
    EXPECT_EQ(tabBarPattern_->GetContentSize().Width(), 660.0f);
    EXPECT_EQ(tabBarPattern_->GetContentSize().Height(), 0.0f);
    auto childOffset = childGeometryNode->GetMarginFrameOffset();
    EXPECT_EQ(childOffset.GetX(), 30.0f);
    EXPECT_EQ(childOffset.GetY(), 30.0f);

    ViewAbstract::SetPadding(AceType::RawPtr(tabBarNode_), CalcLength(210));
    FlushUITasks();
    EXPECT_EQ(geometryNode->GetFrameSize().Width(), 720.0f);
    EXPECT_EQ(geometryNode->GetFrameSize().Height(), 420.0f);
    EXPECT_EQ(tabBarPattern_->GetContentSize().Width(), 300.0f);
    EXPECT_EQ(tabBarPattern_->GetContentSize().Height(), 0.0f);
    childOffset = childGeometryNode->GetMarginFrameOffset();
    EXPECT_EQ(childOffset.GetX(), 210.0f);
    EXPECT_EQ(childOffset.GetY(), 210.0f);

    ViewAbstract::SetBorderWidth(AceType::RawPtr(tabBarNode_), 170.0_px);
    FlushUITasks();
    EXPECT_EQ(geometryNode->GetFrameSize().Width(), 760.0f);
    EXPECT_EQ(geometryNode->GetFrameSize().Height(), 760.0f);
    EXPECT_EQ(tabBarPattern_->GetContentSize().Width(), 0.0f);
    EXPECT_EQ(tabBarPattern_->GetContentSize().Height(), 0.0f);
    childOffset = childGeometryNode->GetMarginFrameOffset();
    EXPECT_EQ(childOffset.GetX(), 380.0f);
    EXPECT_EQ(childOffset.GetY(), 380.0f);
}

/**
 * @tc.name: TabBarMarginTest001
 * @tc.desc: test margin
 * @tc.type: FUNC
 */
HWTEST_F(TabBarUniversalAttributeTestNg, TabBarMarginTest001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    FlushUITasks();
    auto geometryNode = tabBarNode_->GetGeometryNode();
    EXPECT_NE(geometryNode, nullptr);
    auto frameOffset = geometryNode->GetFrameOffset();
    EXPECT_EQ(frameOffset.GetX(), 0.0f);
    EXPECT_EQ(frameOffset.GetY(), 0.0f);

    ViewAbstract::SetMargin(AceType::RawPtr(tabBarNode_), CalcLength(10));
    FlushUITasks();
    frameOffset = geometryNode->GetFrameOffset();
    EXPECT_EQ(frameOffset.GetX(), 10.0f);
    EXPECT_EQ(frameOffset.GetY(), 10.0f);

    ViewAbstract::SetLayoutDirection(AceType::RawPtr(frameNode_), TextDirection::RTL);
    FlushUITasks();
    frameOffset = geometryNode->GetFrameOffset();
    EXPECT_EQ(frameOffset.GetX(), 10.0f);
    EXPECT_EQ(frameOffset.GetY(), 10.0f);
}
} // namespace OHOS::Ace::NG