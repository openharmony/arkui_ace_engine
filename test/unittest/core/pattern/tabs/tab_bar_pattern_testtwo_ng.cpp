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

#include <iostream>

#include "gtest/gtest.h"
#include "tabs_test_ng.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;

class TabBarPatternTestNg : public TestNG {
public:
};

/**
 * @tc.name: GetOriginalPaintRect001
 * @tc.desc: Test TabBarPattern GetOriginalPaintRect
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, GetOriginalPaintRect001, TestSize.Level1)
{
    RefPtr<TabBarPattern> tabBarPattern = AceType::MakeRefPtr<TabBarPattern>();
    RefPtr<FrameNode> frameNode = AceType::MakeRefPtr<FrameNode>(V2::TABS_ETS_TAG, 2, tabBarPattern, true);
    ASSERT_NE(frameNode, nullptr);
    frameNode->children_.clear();
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    RefPtr<PipelineContext> pipe = AceType::MakeRefPtr<PipelineContext>();
    frameNode->context_ = AceType::RawPtr(pipe);
    GeometryProperty geometryProperty;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryProperty.rect_ = RectF(20.0f, 40.0f, 60.0f, 60.0f);
    geometryNode->frame_ = geometryProperty;
    frameNode->geometryNode_ = geometryNode;
    RefPtr<TabBarLayoutProperty> tabBarLayoutProperty = AceType::MakeRefPtr<TabBarLayoutProperty>();
    tabBarLayoutProperty->host_ = frameNode;
    frameNode->layoutProperty_ = tabBarLayoutProperty;
    tabBarPattern->frameNode_ = frameNode;
    tabBarPattern->barGridMargin_ = 50.0f;
    ItemInfo itemInfo;
    itemInfo.startPos = 2.0f;
    itemInfo.endPos = 8.0f;
    tabBarPattern->visibleItemPosition_[3] = itemInfo;
    tabBarPattern->isRTL_ = true;
    auto result = tabBarPattern->GetOriginalPaintRect(2);
    EXPECT_EQ(result.GetX(), -42.0f);
    EXPECT_EQ(tabBarPattern->currentIndicatorOffset_, -42.0f);
}

/**
 * @tc.name: GetOriginalPaintRect002
 * @tc.desc: Test TabBarPattern GetOriginalPaintRect
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, GetOriginalPaintRect002, TestSize.Level1)
{
    RefPtr<TabBarPattern> tabBarPattern = AceType::MakeRefPtr<TabBarPattern>();
    RefPtr<FrameNode> frameNode = AceType::MakeRefPtr<FrameNode>(V2::TABS_ETS_TAG, 2, tabBarPattern, true);
    ASSERT_NE(frameNode, nullptr);
    frameNode->children_.clear();
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    RefPtr<PipelineContext> pipe = AceType::MakeRefPtr<PipelineContext>();
    frameNode->context_ = AceType::RawPtr(pipe);
    GeometryProperty geometryProperty;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryProperty.rect_ = RectF(20.0f, 40.0f, 60.0f, 60.0f);
    geometryNode->frame_ = geometryProperty;
    frameNode->geometryNode_ = geometryNode;
    RefPtr<TabBarLayoutProperty> tabBarLayoutProperty = AceType::MakeRefPtr<TabBarLayoutProperty>();
    tabBarLayoutProperty->host_ = frameNode;
    frameNode->layoutProperty_ = tabBarLayoutProperty;
    tabBarPattern->frameNode_ = frameNode;
    tabBarPattern->barGridMargin_ = 50.0f;
    ItemInfo itemInfo;
    itemInfo.startPos = 2.0f;
    itemInfo.endPos = 8.0f;
    tabBarPattern->visibleItemPosition_[3] = itemInfo;
    tabBarPattern->isRTL_ = false;
    auto result = tabBarPattern->GetOriginalPaintRect(2);
    EXPECT_EQ(result.GetX(), 2.0f);
    EXPECT_EQ(tabBarPattern->currentIndicatorOffset_, 2.0f);
}

/**
 * @tc.name: GetOriginalPaintRect003
 * @tc.desc: Test TabBarPattern GetOriginalPaintRect
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, GetOriginalPaintRect003, TestSize.Level1)
{
    RefPtr<TabBarPattern> tabBarPattern = AceType::MakeRefPtr<TabBarPattern>();
    RefPtr<FrameNode> frameNode = AceType::MakeRefPtr<FrameNode>(V2::TABS_ETS_TAG, 2, tabBarPattern, true);
    ASSERT_NE(frameNode, nullptr);
    frameNode->children_.clear();
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    RefPtr<PipelineContext> pipe = AceType::MakeRefPtr<PipelineContext>();
    frameNode->context_ = AceType::RawPtr(pipe);
    GeometryProperty geometryProperty;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryProperty.rect_ = RectF(20.0f, 40.0f, 60.0f, 60.0f);
    geometryNode->frame_ = geometryProperty;
    frameNode->geometryNode_ = geometryNode;
    RefPtr<TabBarLayoutProperty> tabBarLayoutProperty = AceType::MakeRefPtr<TabBarLayoutProperty>();
    tabBarLayoutProperty->host_ = frameNode;
    frameNode->layoutProperty_ = tabBarLayoutProperty;
    tabBarPattern->frameNode_ = frameNode;
    tabBarPattern->barGridMargin_ = 40.0f;
    ItemInfo itemInfo;
    itemInfo.startPos = 2.0f;
    itemInfo.endPos = 8.0f;
    tabBarPattern->visibleItemPosition_[1] = itemInfo;
    tabBarPattern->isRTL_ = true;
    auto result = tabBarPattern->GetOriginalPaintRect(-1);
    EXPECT_EQ(result.GetX(), 0.0f);
    EXPECT_EQ(tabBarPattern->currentIndicatorOffset_, 0.0f);
}

/**
 * @tc.name: GetOriginalPaintRect004
 * @tc.desc: Test TabBarPattern GetOriginalPaintRect
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, GetOriginalPaintRect004, TestSize.Level1)
{
    RefPtr<TabBarPattern> tabBarPattern = AceType::MakeRefPtr<TabBarPattern>();
    RefPtr<FrameNode> frameNode = AceType::MakeRefPtr<FrameNode>(V2::TABS_ETS_TAG, 2, tabBarPattern, true);
    ASSERT_NE(frameNode, nullptr);
    frameNode->children_.clear();
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    RefPtr<PipelineContext> pipe = AceType::MakeRefPtr<PipelineContext>();
    frameNode->context_ = AceType::RawPtr(pipe);
    GeometryProperty geometryProperty;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryProperty.rect_ = RectF(20.0f, 40.0f, 60.0f, 60.0f);
    geometryNode->frame_ = geometryProperty;
    frameNode->geometryNode_ = geometryNode;
    RefPtr<TabBarLayoutProperty> tabBarLayoutProperty = AceType::MakeRefPtr<TabBarLayoutProperty>();
    tabBarLayoutProperty->host_ = frameNode;
    frameNode->layoutProperty_ = tabBarLayoutProperty;
    tabBarPattern->frameNode_ = frameNode;
    tabBarPattern->barGridMargin_ = 40.0f;
    ItemInfo itemInfo;
    itemInfo.startPos = 2.0f;
    itemInfo.endPos = 8.0f;
    tabBarPattern->visibleItemPosition_[0] = itemInfo;
    tabBarPattern->isRTL_ = true;
    auto result = tabBarPattern->GetOriginalPaintRect(1);
    EXPECT_EQ(result.GetX(), -28.0f);
    EXPECT_EQ(tabBarPattern->currentIndicatorOffset_, -28.0f);
}

/**
 * @tc.name: GetOriginalPaintRect005
 * @tc.desc: Test TabBarPattern GetOriginalPaintRect
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, GetOriginalPaintRect005, TestSize.Level1)
{
    RefPtr<TabBarPattern> tabBarPattern = AceType::MakeRefPtr<TabBarPattern>();
    RefPtr<FrameNode> frameNode = AceType::MakeRefPtr<FrameNode>(V2::TABS_ETS_TAG, 2, tabBarPattern, true);
    ASSERT_NE(frameNode, nullptr);
    frameNode->children_.clear();
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    RefPtr<PipelineContext> pipe = AceType::MakeRefPtr<PipelineContext>();
    frameNode->context_ = AceType::RawPtr(pipe);
    GeometryProperty geometryProperty;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryProperty.rect_ = RectF(20.0f, 40.0f, 60.0f, 60.0f);
    geometryNode->frame_ = geometryProperty;
    frameNode->geometryNode_ = geometryNode;
    RefPtr<TabBarLayoutProperty> tabBarLayoutProperty = AceType::MakeRefPtr<TabBarLayoutProperty>();
    tabBarLayoutProperty->host_ = frameNode;
    frameNode->layoutProperty_ = tabBarLayoutProperty;
    tabBarPattern->frameNode_ = frameNode;
    tabBarPattern->barGridMargin_ = 30.0f;
    ItemInfo itemInfo;
    itemInfo.startPos = 2.0f;
    itemInfo.endPos = 8.0f;
    tabBarPattern->visibleItemPosition_[0] = itemInfo;
    tabBarPattern->isRTL_ = false;
    auto result = tabBarPattern->GetOriginalPaintRect(1);
    EXPECT_EQ(result.GetX(), 8.0f);
    EXPECT_EQ(tabBarPattern->currentIndicatorOffset_, 8.0f);
}

/**
 * @tc.name: GetOriginalPaintRect006
 * @tc.desc: Test TabBarPattern GetOriginalPaintRect
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, GetOriginalPaintRect006, TestSize.Level1)
{
    RefPtr<TabBarPattern> tabBarPattern = AceType::MakeRefPtr<TabBarPattern>();
    RefPtr<FrameNode> frameNode = AceType::MakeRefPtr<FrameNode>(V2::TABS_ETS_TAG, 2, tabBarPattern, true);
    ASSERT_NE(frameNode, nullptr);
    frameNode->children_.clear();
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    RefPtr<PipelineContext> pipe = AceType::MakeRefPtr<PipelineContext>();
    frameNode->context_ = AceType::RawPtr(pipe);
    GeometryProperty geometryProperty;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryProperty.rect_ = RectF(20.0f, 40.0f, 60.0f, 60.0f);
    geometryNode->frame_ = geometryProperty;
    frameNode->geometryNode_ = geometryNode;
    RefPtr<TabBarLayoutProperty> tabBarLayoutProperty = AceType::MakeRefPtr<TabBarLayoutProperty>();
    tabBarLayoutProperty->host_ = frameNode;
    frameNode->layoutProperty_ = tabBarLayoutProperty;
    tabBarPattern->frameNode_ = frameNode;
    tabBarPattern->barGridMargin_ = 40.0f;
    ItemInfo itemInfo;
    itemInfo.startPos = 2.0f;
    itemInfo.endPos = 8.0f;
    tabBarPattern->visibleItemPosition_[0] = itemInfo;
    tabBarPattern->isRTL_ = true;
    auto result = tabBarPattern->GetOriginalPaintRect(4);
    EXPECT_EQ(result.GetX(), 0.0f);
    EXPECT_EQ(tabBarPattern->currentIndicatorOffset_, 0.0f);
}

/**
 * @tc.name: GetOriginalPaintRect007
 * @tc.desc: Test TabBarPattern GetOriginalPaintRect
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, GetOriginalPaintRect007, TestSize.Level1)
{
    RefPtr<TabBarPattern> tabBarPattern = AceType::MakeRefPtr<TabBarPattern>();
    RefPtr<FrameNode> frameNode = AceType::MakeRefPtr<FrameNode>(V2::TABS_ETS_TAG, 2, tabBarPattern, true);
    ASSERT_NE(frameNode, nullptr);
    frameNode->children_.clear();
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    RefPtr<PipelineContext> pipe = AceType::MakeRefPtr<PipelineContext>();
    frameNode->context_ = AceType::RawPtr(pipe);
    GeometryProperty geometryProperty;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryProperty.rect_ = RectF(20.0f, 40.0f, 60.0f, 60.0f);
    geometryNode->frame_ = geometryProperty;
    frameNode->geometryNode_ = geometryNode;
    RefPtr<TabBarLayoutProperty> tabBarLayoutProperty = AceType::MakeRefPtr<TabBarLayoutProperty>();
    tabBarLayoutProperty->host_ = frameNode;
    frameNode->layoutProperty_ = tabBarLayoutProperty;
    tabBarPattern->frameNode_ = frameNode;
    tabBarPattern->barGridMargin_ = 40.0f;
    ItemInfo itemInfo;
    itemInfo.startPos = 2.0f;
    itemInfo.endPos = 8.0f;
    tabBarPattern->visibleItemPosition_[0] = itemInfo;
    tabBarPattern->isRTL_ = false;
    auto result = tabBarPattern->GetOriginalPaintRect(-1);
    EXPECT_EQ(result.GetX(), 0.0f);
    EXPECT_EQ(tabBarPattern->currentIndicatorOffset_, 0.0f);
}

/**
 * @tc.name: GetTabBarAxis001
 * @tc.desc: Test TabContentNode GetTabBarAxis
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, GetTabBarAxis001, TestSize.Level1)
{
    RefPtr<TabBarPattern> tabBarPattern = AceType::MakeRefPtr<TabBarPattern>();
    RefPtr<TabContentNode> tabContentNode =
        AceType::MakeRefPtr<TabContentNode>(V2::TAB_BAR_ETS_TAG, 2, tabBarPattern, true);
    ASSERT_NE(tabContentNode, nullptr);
    tabContentNode->tabBarItemId_.reset();
    auto result = tabContentNode->GetTabBarAxis();
    EXPECT_EQ(result, Axis::HORIZONTAL);
}

/**
 * @tc.name: GetDefaultFontSize001
 * @tc.desc: Test TabContentNode GetDefaultFontSize
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, GetDefaultFontSize001, TestSize.Level1)
{
    RefPtr<TabBarPattern> tabBarPattern = AceType::MakeRefPtr<TabBarPattern>();
    RefPtr<TabContentNode> tabContentNode =
        AceType::MakeRefPtr<TabContentNode>(V2::TAB_BAR_ETS_TAG, 2, tabBarPattern, true);
    ASSERT_NE(tabContentNode, nullptr);
    tabContentNode->tabBarItemId_.reset();
    auto result = tabContentNode->GetDefaultFontSize();
    EXPECT_EQ(result.value_, 0);
}
} // namespace OHOS::Ace::NG