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
#include "test/unittest/core/pattern/test_ng.h"

#include "core/components_ng/pattern/grid/grid_pattern.h"
#include "core/components_ng/pattern/grid/grid_scroll/grid_scroll_layout_algorithm.h"
#include "core/components_ng/pattern/scroll/scroll_event_hub.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;

class GridTestNg : public TestNG {
public:
};

/**
 * @tc.name: BuildScrollAlignInfo001
 * @tc.desc: Test GridPattern BuildScrollAlignInfo
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, BuildScrollAlignInfo001, TestSize.Level1)
{
    RefPtr<GridPattern> gridPattern = AceType::MakeRefPtr<GridPattern>();
    GridLayoutInfo info;
    info.scrollAlign_ = ScrollAlign::NONE;
    gridPattern->info_ = info;
    auto json = JsonUtil::Create(true);
    gridPattern->BuildScrollAlignInfo(json);
    EXPECT_EQ(json->GetString("ScrollAlign"), "NONE");
}

/**
 * @tc.name: BuildScrollAlignInfo002
 * @tc.desc: Test GridPattern BuildScrollAlignInfo
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, BuildScrollAlignInfo002, TestSize.Level1)
{
    RefPtr<GridPattern> gridPattern = AceType::MakeRefPtr<GridPattern>();
    GridLayoutInfo info;
    info.scrollAlign_ = ScrollAlign::CENTER;
    gridPattern->info_ = info;
    auto json = JsonUtil::Create(true);
    gridPattern->BuildScrollAlignInfo(json);
    EXPECT_EQ(json->GetString("ScrollAlign"), "CENTER");
}

/**
 * @tc.name: BuildScrollAlignInfo003
 * @tc.desc: Test GridPattern BuildScrollAlignInfo
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, BuildScrollAlignInfo003, TestSize.Level1)
{
    RefPtr<GridPattern> gridPattern = AceType::MakeRefPtr<GridPattern>();
    GridLayoutInfo info;
    info.scrollAlign_ = ScrollAlign::END;
    gridPattern->info_ = info;
    auto json = JsonUtil::Create(true);
    gridPattern->BuildScrollAlignInfo(json);
    EXPECT_EQ(json->GetString("ScrollAlign"), "END");
}

/**
 * @tc.name: BuildScrollAlignInfo004
 * @tc.desc: Test GridPattern BuildScrollAlignInfo
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, BuildScrollAlignInfo004, TestSize.Level1)
{
    RefPtr<GridPattern> gridPattern = AceType::MakeRefPtr<GridPattern>();
    GridLayoutInfo info;
    info.scrollAlign_ = ScrollAlign::START;
    gridPattern->info_ = info;
    auto json = JsonUtil::Create(true);
    gridPattern->BuildScrollAlignInfo(json);
    EXPECT_EQ(json->GetString("ScrollAlign"), "START");
}

/**
 * @tc.name: BuildScrollAlignInfo005
 * @tc.desc: Test GridPattern BuildScrollAlignInfo
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, BuildScrollAlignInfo005, TestSize.Level1)
{
    RefPtr<GridPattern> gridPattern = AceType::MakeRefPtr<GridPattern>();
    GridLayoutInfo info;
    gridPattern->info_ = info;
    auto json = JsonUtil::Create(true);
    gridPattern->BuildScrollAlignInfo(json);
    EXPECT_EQ(json->GetString("ScrollAlign"), "AUTO");
}

/**
 * @tc.name: BuildScrollAlignInfo006
 * @tc.desc: Test GridPattern BuildScrollAlignInfo
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, BuildScrollAlignInfo006, TestSize.Level1)
{
    RefPtr<GridPattern> gridPattern = AceType::MakeRefPtr<GridPattern>();
    GridLayoutInfo info;
    int32_t number = 6;
    info.scrollAlign_ = static_cast<ScrollAlign>(number);
    gridPattern->info_ = info;
    auto json = JsonUtil::Create(true);
    gridPattern->BuildScrollAlignInfo(json);
    EXPECT_NE(json->GetString("ScrollAlign"), "AUTO");
}

/**
 * @tc.name: GetIrregularIndexesString001
 * @tc.desc: Test GridPattern GetIrregularIndexesString
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GetIrregularIndexesString001, TestSize.Level1)
{
    RefPtr<GridPattern> gridPattern = AceType::MakeRefPtr<GridPattern>();
    auto result = gridPattern->GetIrregularIndexesString();
    EXPECT_EQ(result, "");
}

/**
 * @tc.name: GetIrregularIndexesString002
 * @tc.desc: Test GridPattern GetIrregularIndexesString
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GetIrregularIndexesString002, TestSize.Level1)
{
    RefPtr<GridPattern> gridPattern = AceType::MakeRefPtr<GridPattern>();
    ASSERT_NE(gridPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, gridPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GridLayoutProperty> gridLayoutProperty = AceType::MakeRefPtr<GridLayoutProperty>();
    frameNode->layoutProperty_ = gridLayoutProperty;
    gridPattern->frameNode_ = frameNode;
    auto result = gridPattern->GetIrregularIndexesString();
    EXPECT_EQ(result, "");
}

/**
 * @tc.name: DumpAdvanceInfo001
 * @tc.desc: Test GridPattern DumpAdvanceInfo
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, DumpAdvanceInfo001, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    RefPtr<GridPattern> gridPattern = AceType::MakeRefPtr<GridPattern>();
    ASSERT_NE(gridPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, gridPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GridLayoutProperty> gridLayoutProperty = AceType::MakeRefPtr<GridLayoutProperty>();
    frameNode->layoutProperty_ = gridLayoutProperty;
    gridPattern->frameNode_ = frameNode;
    gridPattern->DumpAdvanceInfo();
    EXPECT_EQ(DumpLog::GetInstance().description_[28], "GridLayoutOptions:null\n");
}

/**
 * @tc.name: DumpAdvanceInfo002
 * @tc.desc: Test GridPattern DumpAdvanceInfo
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, DumpAdvanceInfo002, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    RefPtr<GridPattern> gridPattern = AceType::MakeRefPtr<GridPattern>();
    ASSERT_NE(gridPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, gridPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GridLayoutProperty> gridLayoutProperty = AceType::MakeRefPtr<GridLayoutProperty>();
    frameNode->layoutProperty_ = gridLayoutProperty;
    gridPattern->frameNode_ = frameNode;
    GridLayoutInfo info;
    info.scrollAlign_ = ScrollAlign::NONE;
    gridPattern->info_ = info;
    gridPattern->DumpAdvanceInfo();
    EXPECT_EQ(DumpLog::GetInstance().description_[61], "ScrollAlign:NONE\n");
}

/**
 * @tc.name: DumpAdvanceInfo003
 * @tc.desc: Test GridPattern DumpAdvanceInfo
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, DumpAdvanceInfo003, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    RefPtr<GridPattern> gridPattern = AceType::MakeRefPtr<GridPattern>();
    ASSERT_NE(gridPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, gridPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GridLayoutProperty> gridLayoutProperty = AceType::MakeRefPtr<GridLayoutProperty>();
    frameNode->layoutProperty_ = gridLayoutProperty;
    gridPattern->frameNode_ = frameNode;
    GridLayoutInfo info;
    info.scrollAlign_ = ScrollAlign::CENTER;
    gridPattern->info_ = info;
    gridPattern->DumpAdvanceInfo();
    EXPECT_EQ(DumpLog::GetInstance().description_[61], "ScrollAlign:CENTER\n");
}

/**
 * @tc.name: DumpAdvanceInfo004
 * @tc.desc: Test GridPattern DumpAdvanceInfo
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, DumpAdvanceInfo004, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    RefPtr<GridPattern> gridPattern = AceType::MakeRefPtr<GridPattern>();
    ASSERT_NE(gridPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, gridPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GridLayoutProperty> gridLayoutProperty = AceType::MakeRefPtr<GridLayoutProperty>();
    frameNode->layoutProperty_ = gridLayoutProperty;
    gridPattern->frameNode_ = frameNode;
    GridLayoutInfo info;
    info.scrollAlign_ = ScrollAlign::END;
    gridPattern->info_ = info;
    gridPattern->DumpAdvanceInfo();
    EXPECT_EQ(DumpLog::GetInstance().description_[61], "ScrollAlign:END\n");
}

/**
 * @tc.name: DumpAdvanceInfo005
 * @tc.desc: Test GridPattern DumpAdvanceInfo
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, DumpAdvanceInfo005, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    RefPtr<GridPattern> gridPattern = AceType::MakeRefPtr<GridPattern>();
    ASSERT_NE(gridPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, gridPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GridLayoutProperty> gridLayoutProperty = AceType::MakeRefPtr<GridLayoutProperty>();
    frameNode->layoutProperty_ = gridLayoutProperty;
    gridPattern->frameNode_ = frameNode;
    GridLayoutInfo info;
    info.scrollAlign_ = ScrollAlign::START;
    gridPattern->info_ = info;
    gridPattern->DumpAdvanceInfo();
    EXPECT_EQ(DumpLog::GetInstance().description_[61], "ScrollAlign:START\n");
}

/**
 * @tc.name: DumpAdvanceInfo006
 * @tc.desc: Test GridPattern DumpAdvanceInfo
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, DumpAdvanceInfo006, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    RefPtr<GridPattern> gridPattern = AceType::MakeRefPtr<GridPattern>();
    ASSERT_NE(gridPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, gridPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GridLayoutProperty> gridLayoutProperty = AceType::MakeRefPtr<GridLayoutProperty>();
    frameNode->layoutProperty_ = gridLayoutProperty;
    gridPattern->frameNode_ = frameNode;
    GridLayoutInfo info;
    gridPattern->info_ = info;
    gridPattern->DumpAdvanceInfo();
    EXPECT_EQ(DumpLog::GetInstance().description_[61], "ScrollAlign:AUTO\n");
}

/**
 * @tc.name: DumpAdvanceInfo007
 * @tc.desc: Test GridPattern DumpAdvanceInfo
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, DumpAdvanceInfo007, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    RefPtr<GridPattern> gridPattern = AceType::MakeRefPtr<GridPattern>();
    ASSERT_NE(gridPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, gridPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GridLayoutProperty> gridLayoutProperty = AceType::MakeRefPtr<GridLayoutProperty>();
    frameNode->layoutProperty_ = gridLayoutProperty;
    gridPattern->frameNode_ = frameNode;
    gridPattern->DumpAdvanceInfo();
    EXPECT_EQ(DumpLog::GetInstance().description_[60], "AlignItems:GridItemAlignment.DEFAULT\n");
}

/**
 * @tc.name: DumpAdvanceInfo008
 * @tc.desc: Test GridPattern DumpAdvanceInfo
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, DumpAdvanceInfo008, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    RefPtr<GridPattern> gridPattern = AceType::MakeRefPtr<GridPattern>();
    ASSERT_NE(gridPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, gridPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GridLayoutProperty> gridLayoutProperty = AceType::MakeRefPtr<GridLayoutProperty>();
    frameNode->layoutProperty_ = gridLayoutProperty;
    gridPattern->frameNode_ = frameNode;
    GridLayoutInfo info;
    info.scrollAlign_ = ScrollAlign::START;
    std::map<int32_t, std::map<int32_t, int32_t>> gridMatrix;
    gridMatrix[0] = { { 1, 2 } };
    gridMatrix[1] = { { 3, 4 } };
    info.gridMatrix_ = gridMatrix;
    gridPattern->info_ = info;
    gridPattern->DumpAdvanceInfo();
    EXPECT_EQ(DumpLog::GetInstance().description_[62], "-----------start print gridMatrix------------\n");
}

/**
 * @tc.name: DumpAdvanceInfo009
 * @tc.desc: Test GridPattern DumpAdvanceInfo
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, DumpAdvanceInfo009, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    RefPtr<GridPattern> gridPattern = AceType::MakeRefPtr<GridPattern>();
    ASSERT_NE(gridPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, gridPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GridLayoutProperty> gridLayoutProperty = AceType::MakeRefPtr<GridLayoutProperty>();
    frameNode->layoutProperty_ = gridLayoutProperty;
    gridPattern->frameNode_ = frameNode;
    GridLayoutInfo info;
    info.scrollAlign_ = ScrollAlign::START;
    std::map<int32_t, float> lineHeightMap;
    lineHeightMap[0] = 1.0f;
    lineHeightMap[2] = 3.0f;
    info.lineHeightMap_ = lineHeightMap;
    gridPattern->info_ = info;
    gridPattern->DumpAdvanceInfo();
    EXPECT_NE(DumpLog::GetInstance().description_[62], "-----------start print gridMatrix------------\n");
}

/**
 * @tc.name: DumpAdvanceInfo010
 * @tc.desc: Test GridPattern DumpAdvanceInfo
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, DumpAdvanceInfo010, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    RefPtr<GridPattern> gridPattern = AceType::MakeRefPtr<GridPattern>();
    ASSERT_NE(gridPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, gridPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GridLayoutProperty> gridLayoutProperty = AceType::MakeRefPtr<GridLayoutProperty>();
    frameNode->layoutProperty_ = gridLayoutProperty;
    gridPattern->frameNode_ = frameNode;
    GridLayoutInfo info;
    info.scrollAlign_ = ScrollAlign::START;
    std::map<int32_t, float> lineHeightMap;
    lineHeightMap[0] = 1.0f;
    lineHeightMap[2] = 3.0f;
    info.lineHeightMap_ = lineHeightMap;
    gridPattern->info_ = info;
    gridPattern->DumpAdvanceInfo();
    EXPECT_EQ(DumpLog::GetInstance().description_[62], "-----------start print lineHeightMap------------\n");
}

/**
 * @tc.name: DumpAdvanceInfo011
 * @tc.desc: Test GridPattern DumpAdvanceInfo
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, DumpAdvanceInfo011, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    RefPtr<GridPattern> gridPattern = AceType::MakeRefPtr<GridPattern>();
    ASSERT_NE(gridPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, gridPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GridLayoutProperty> gridLayoutProperty = AceType::MakeRefPtr<GridLayoutProperty>();
    frameNode->layoutProperty_ = gridLayoutProperty;
    gridPattern->frameNode_ = frameNode;
    GridLayoutInfo info;
    info.scrollAlign_ = ScrollAlign::START;
    std::map<int32_t, int32_t> irregularItemsPosition;
    irregularItemsPosition[0] = 1;
    irregularItemsPosition[2] = 3;
    info.irregularItemsPosition_ = irregularItemsPosition;
    gridPattern->info_ = info;
    gridPattern->DumpAdvanceInfo();
    EXPECT_EQ(DumpLog::GetInstance().description_[62], "-----------start print irregularItemsPosition_------------\n");
}

/**
 * @tc.name: DumpAdvanceInfo012
 * @tc.desc: Test GridPattern DumpAdvanceInfo
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, DumpAdvanceInfo012, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    RefPtr<GridPattern> gridPattern = AceType::MakeRefPtr<GridPattern>();
    ASSERT_NE(gridPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, gridPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GridLayoutProperty> gridLayoutProperty = AceType::MakeRefPtr<GridLayoutProperty>();
    frameNode->layoutProperty_ = gridLayoutProperty;
    gridPattern->frameNode_ = frameNode;
    GridLayoutInfo info;
    info.scrollAlign_ = ScrollAlign::START;
    std::map<int32_t, int32_t> irregularItemsPosition;
    irregularItemsPosition[0] = 1;
    irregularItemsPosition[2] = 3;
    info.irregularItemsPosition_ = irregularItemsPosition;
    gridPattern->info_ = info;
    gridPattern->DumpAdvanceInfo();
    EXPECT_NE(DumpLog::GetInstance().description_[62], "-----------start print lineHeightMap------------\n");
}

/**
 * @tc.name: DumpAdvanceInfo013
 * @tc.desc: Test GridPattern DumpAdvanceInfo
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, DumpAdvanceInfo013, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    RefPtr<GridPattern> gridPattern = AceType::MakeRefPtr<GridPattern>();
    ASSERT_NE(gridPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, gridPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GridLayoutProperty> gridLayoutProperty = AceType::MakeRefPtr<GridLayoutProperty>();
    frameNode->layoutProperty_ = gridLayoutProperty;
    gridPattern->frameNode_ = frameNode;
    GridLayoutInfo info;
    info.scrollAlign_ = ScrollAlign::START;
    std::map<int32_t, std::map<int32_t, int32_t>> gridMatrix;
    gridMatrix[0] = { { 1, 2 } };
    info.gridMatrix_ = gridMatrix;
    std::map<int32_t, float> lineHeightMap;
    lineHeightMap[0] = 1.0f;
    info.lineHeightMap_ = lineHeightMap;
    gridPattern->info_ = info;
    gridPattern->DumpAdvanceInfo();
    EXPECT_NE(DumpLog::GetInstance().description_[64], "-----------start print irregularItemsPosition_------------\n");
}

/**
 * @tc.name: ToJsonValue001
 * @tc.desc: Test GridPattern ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, ToJsonValue001, TestSize.Level1)
{
    RefPtr<GridPattern> gridPattern = AceType::MakeRefPtr<GridPattern>();
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;
    filter.filterFixed = 3;
    gridPattern->multiSelectable_ = true;
    gridPattern->ToJsonValue(json, filter);
    EXPECT_NE(json->GetString("multiSelectable"), "true");
}

/**
 * @tc.name: ToJsonValue002
 * @tc.desc: Test GridPattern ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, ToJsonValue002, TestSize.Level1)
{
    RefPtr<GridPattern> gridPattern = AceType::MakeRefPtr<GridPattern>();
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;
    filter.filterFixed = 0;
    gridPattern->multiSelectable_ = true;
    gridPattern->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("multiSelectable"), "true");
}

/**
 * @tc.name: OnKeyEvent001
 * @tc.desc: Test GridPattern OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, OnKeyEvent001, TestSize.Level1)
{
    GridPattern gridPattern;
    KeyEvent event;
    event.action = KeyAction::DOWN;
    event.code = KeyCode::KEY_TAB;
    GridLayoutInfo info;
    gridPattern.info_ = info;
    auto result = gridPattern.OnKeyEvent(event);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: GetItemIndex001
 * @tc.desc: Test GridPattern GetItemIndex
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GetItemIndex001, TestSize.Level1)
{
    RefPtr<GridPattern> gridPattern = AceType::MakeRefPtr<GridPattern>();
    GridLayoutInfo info;
    info.startIndex_ = -2;
    info.endIndex_ = 1;
    gridPattern->info_ = info;
    auto result = gridPattern->GetItemIndex(2.F, 4.F);
    EXPECT_EQ(result, -1);
}

/**
 * @tc.name: BuildGridLayoutInfo001
 * @tc.desc: Test GridPattern BuildGridLayoutInfo
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, BuildGridLayoutInfo001, TestSize.Level1)
{
    RefPtr<GridPattern> gridPattern = AceType::MakeRefPtr<GridPattern>();
    ASSERT_NE(gridPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, gridPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GridLayoutProperty> gridLayoutProperty = AceType::MakeRefPtr<GridLayoutProperty>();
    frameNode->layoutProperty_ = gridLayoutProperty;
    gridPattern->frameNode_ = frameNode;
    GridLayoutInfo info;
    info.scrollAlign_ = ScrollAlign::START;
    std::map<int32_t, std::map<int32_t, int32_t>> gridMatrix;
    gridMatrix[0] = { { 1, 2 } };
    gridMatrix[1] = { { 3, 4 } };
    info.gridMatrix_ = gridMatrix;
    gridPattern->info_ = info;
    auto json = JsonUtil::Create(true);
    gridPattern->BuildGridLayoutInfo(json);
    EXPECT_EQ(json->GetString("gridMatrix"), "");
}

/**
 * @tc.name: BuildGridLayoutInfo002
 * @tc.desc: Test GridPattern BuildGridLayoutInfo
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, BuildGridLayoutInfo002, TestSize.Level1)
{
    RefPtr<GridPattern> gridPattern = AceType::MakeRefPtr<GridPattern>();
    ASSERT_NE(gridPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, gridPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GridLayoutProperty> gridLayoutProperty = AceType::MakeRefPtr<GridLayoutProperty>();
    frameNode->layoutProperty_ = gridLayoutProperty;
    gridPattern->frameNode_ = frameNode;
    GridLayoutInfo info;
    info.scrollAlign_ = ScrollAlign::START;
    std::map<int32_t, float> lineHeightMap;
    lineHeightMap[0] = 1.0f;
    lineHeightMap[2] = 3.0f;
    info.lineHeightMap_ = lineHeightMap;
    gridPattern->info_ = info;
    auto json = JsonUtil::Create(true);
    gridPattern->BuildGridLayoutInfo(json);
    EXPECT_EQ(json->GetString("gridMatrix"), "");
}

/**
 * @tc.name: BuildGridLayoutInfo003
 * @tc.desc: Test GridPattern BuildGridLayoutInfo
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, BuildGridLayoutInfo003, TestSize.Level1)
{
    RefPtr<GridPattern> gridPattern = AceType::MakeRefPtr<GridPattern>();
    ASSERT_NE(gridPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, gridPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GridLayoutProperty> gridLayoutProperty = AceType::MakeRefPtr<GridLayoutProperty>();
    frameNode->layoutProperty_ = gridLayoutProperty;
    gridPattern->frameNode_ = frameNode;
    GridLayoutInfo info;
    info.scrollAlign_ = ScrollAlign::START;
    std::map<int32_t, float> lineHeightMap;
    lineHeightMap[0] = 1.0f;
    lineHeightMap[2] = 3.0f;
    info.lineHeightMap_ = lineHeightMap;
    gridPattern->info_ = info;
    auto json = JsonUtil::Create(true);
    gridPattern->BuildGridLayoutInfo(json);
    EXPECT_EQ(json->GetString("lineHeightMap"), "");
}

/**
 * @tc.name: BuildGridLayoutInfo004
 * @tc.desc: Test GridPattern BuildGridLayoutInfo
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, BuildGridLayoutInfo004, TestSize.Level1)
{
    RefPtr<GridPattern> gridPattern = AceType::MakeRefPtr<GridPattern>();
    ASSERT_NE(gridPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, gridPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GridLayoutProperty> gridLayoutProperty = AceType::MakeRefPtr<GridLayoutProperty>();
    frameNode->layoutProperty_ = gridLayoutProperty;
    gridPattern->frameNode_ = frameNode;
    GridLayoutInfo info;
    info.scrollAlign_ = ScrollAlign::START;
    std::map<int32_t, int32_t> irregularItemsPosition;
    irregularItemsPosition[0] = 1;
    irregularItemsPosition[2] = 3;
    info.irregularItemsPosition_ = irregularItemsPosition;
    gridPattern->info_ = info;
    auto json = JsonUtil::Create(true);
    gridPattern->BuildGridLayoutInfo(json);
    EXPECT_EQ(json->GetString("lineHeightMap"), "");
}

/**
 * @tc.name: BuildGridLayoutInfo005
 * @tc.desc: Test GridPattern BuildGridLayoutInfo
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, BuildGridLayoutInfo005, TestSize.Level1)
{
    RefPtr<GridPattern> gridPattern = AceType::MakeRefPtr<GridPattern>();
    ASSERT_NE(gridPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, gridPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GridLayoutProperty> gridLayoutProperty = AceType::MakeRefPtr<GridLayoutProperty>();
    frameNode->layoutProperty_ = gridLayoutProperty;
    gridPattern->frameNode_ = frameNode;
    GridLayoutInfo info;
    info.scrollAlign_ = ScrollAlign::START;
    std::map<int32_t, int32_t> irregularItemsPosition;
    irregularItemsPosition[0] = 1;
    irregularItemsPosition[2] = 3;
    info.irregularItemsPosition_ = irregularItemsPosition;
    gridPattern->info_ = info;
    auto json = JsonUtil::Create(true);
    gridPattern->BuildGridLayoutInfo(json);
    EXPECT_EQ(json->GetString("irregularItemsPosition_"), "");
}

/**
 * @tc.name: BuildGridLayoutInfo006
 * @tc.desc: Test GridPattern BuildGridLayoutInfo
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, BuildGridLayoutInfo006, TestSize.Level1)
{
    RefPtr<GridPattern> gridPattern = AceType::MakeRefPtr<GridPattern>();
    ASSERT_NE(gridPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, gridPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GridLayoutProperty> gridLayoutProperty = AceType::MakeRefPtr<GridLayoutProperty>();
    frameNode->layoutProperty_ = gridLayoutProperty;
    gridPattern->frameNode_ = frameNode;
    GridLayoutInfo info;
    info.scrollAlign_ = ScrollAlign::START;
    std::map<int32_t, std::map<int32_t, int32_t>> gridMatrix;
    gridMatrix[0] = { { 1, 2 } };
    info.gridMatrix_ = gridMatrix;
    std::map<int32_t, float> lineHeightMap;
    lineHeightMap[0] = 1.0f;
    info.lineHeightMap_ = lineHeightMap;
    gridPattern->info_ = info;
    auto json = JsonUtil::Create(true);
    gridPattern->BuildGridLayoutInfo(json);
    EXPECT_EQ(json->GetString("irregularItemsPosition_"), "");
}

/**
 * @tc.name: SkipLargeLineHeightLines001
 * @tc.desc: Test GridScrollLayoutAlgorithm SkipLargeLineHeightLines
 */
HWTEST_F(GridTestNg, SkipLargeLineHeightLines001, TestSize.Level1)
{
    GridLayoutInfo gridLayoutInfo;
    gridLayoutInfo.startMainLineIndex_ = 0;
    gridLayoutInfo.endMainLineIndex_ = 2;
    gridLayoutInfo.currentOffset_ = 0.0f;
    gridLayoutInfo.prevOffset_ = 8.0f;
    gridLayoutInfo.lineHeightMap_[0] = 4.0f;
    gridLayoutInfo.lineHeightMap_[1] = 6.0f;
    RefPtr<GridScrollLayoutAlgorithm> layout = AceType::MakeRefPtr<GridScrollLayoutAlgorithm>(gridLayoutInfo, 0, 0);
    ASSERT_NE(layout, nullptr);
    layout->mainGap_ = 0.0f;
    auto result = layout->SkipLargeLineHeightLines(2.0f);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: SkipLargeLineHeightLines002
 * @tc.desc: Test GridScrollLayoutAlgorithm SkipLargeLineHeightLines
 */
HWTEST_F(GridTestNg, SkipLargeLineHeightLines002, TestSize.Level1)
{
    GridLayoutInfo gridLayoutInfo;
    gridLayoutInfo.startMainLineIndex_ = 0;
    gridLayoutInfo.endMainLineIndex_ = 2;
    gridLayoutInfo.currentOffset_ = -5.0f;
    gridLayoutInfo.prevOffset_ = -8.0f;
    gridLayoutInfo.lineHeightMap_[0] = 4.0f;
    gridLayoutInfo.lineHeightMap_[1] = 6.0f;
    RefPtr<GridScrollLayoutAlgorithm> layout = AceType::MakeRefPtr<GridScrollLayoutAlgorithm>(gridLayoutInfo, 0, 0);
    ASSERT_NE(layout, nullptr);
    layout->mainGap_ = 0.0f;
    auto result = layout->SkipLargeLineHeightLines(2.0f);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: SkipLargeLineHeightLines003
 * @tc.desc: Test GridScrollLayoutAlgorithm SkipLargeLineHeightLines
 */
HWTEST_F(GridTestNg, SkipLargeLineHeightLines003, TestSize.Level1)
{
    GridLayoutInfo gridLayoutInfo;
    gridLayoutInfo.startMainLineIndex_ = 0;
    gridLayoutInfo.endMainLineIndex_ = 2;
    gridLayoutInfo.currentOffset_ = -5.0f;
    gridLayoutInfo.prevOffset_ = -8.0f;
    gridLayoutInfo.lineHeightMap_[0] = 4.0f;
    gridLayoutInfo.lineHeightMap_[1] = 6.0f;
    std::map<int32_t, std::map<int32_t, int32_t>> gridMatrix;
    gridMatrix[0] = { { 1, 2 } };
    gridMatrix[1] = { { 3, 4 } };
    gridMatrix[2] = { { 5, 6 } };
    gridMatrix[3] = { { 7, 8 } };
    gridLayoutInfo.gridMatrix_ = gridMatrix;
    RefPtr<GridScrollLayoutAlgorithm> layout = AceType::MakeRefPtr<GridScrollLayoutAlgorithm>(gridLayoutInfo, 0, 0);
    ASSERT_NE(layout, nullptr);
    layout->mainGap_ = 0.0f;
    auto result = layout->SkipLargeLineHeightLines(2.0f);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: SkipLargeLineHeightLines004
 * @tc.desc: Test GridScrollLayoutAlgorithm SkipLargeLineHeightLines
 */
HWTEST_F(GridTestNg, SkipLargeLineHeightLines004, TestSize.Level1)
{
    GridLayoutInfo gridLayoutInfo;
    gridLayoutInfo.startMainLineIndex_ = 0;
    gridLayoutInfo.endMainLineIndex_ = 2;
    gridLayoutInfo.currentOffset_ = -5.0f;
    gridLayoutInfo.prevOffset_ = -8.0f;
    gridLayoutInfo.lineHeightMap_[0] = 4.0f;
    gridLayoutInfo.lineHeightMap_[1] = 6.0f;
    std::map<int32_t, std::map<int32_t, int32_t>> gridMatrix;
    gridMatrix[0] = { { 1, 2 } };
    gridMatrix[1] = { { 3, 4 } };
    gridMatrix[2] = { { 5, 6 } };
    gridMatrix.emplace();
    gridLayoutInfo.gridMatrix_ = gridMatrix;
    RefPtr<GridScrollLayoutAlgorithm> layout = AceType::MakeRefPtr<GridScrollLayoutAlgorithm>(gridLayoutInfo, 0, 0);
    ASSERT_NE(layout, nullptr);
    layout->mainGap_ = 0.0f;
    auto result = layout->SkipLargeLineHeightLines(2.0f);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: SkipLargeLineHeightLines005
 * @tc.desc: Test GridScrollLayoutAlgorithm SkipLargeLineHeightLines
 */
HWTEST_F(GridTestNg, SkipLargeLineHeightLines005, TestSize.Level1)
{
    GridLayoutInfo gridLayoutInfo;
    gridLayoutInfo.startMainLineIndex_ = 0;
    gridLayoutInfo.endMainLineIndex_ = 2;
    gridLayoutInfo.currentOffset_ = -5.0f;
    gridLayoutInfo.prevOffset_ = -8.0f;
    gridLayoutInfo.lineHeightMap_[0] = 4.0f;
    gridLayoutInfo.lineHeightMap_[1] = 6.0f;
    std::map<int32_t, std::map<int32_t, int32_t>> gridMatrix;
    gridMatrix[0] = { { 1, 2 } };
    gridMatrix[1] = { { 3, 4 } };
    gridLayoutInfo.gridMatrix_ = gridMatrix;
    RefPtr<GridScrollLayoutAlgorithm> layout = AceType::MakeRefPtr<GridScrollLayoutAlgorithm>(gridLayoutInfo, 0, 0);
    ASSERT_NE(layout, nullptr);
    layout->mainGap_ = 0.0f;
    auto result = layout->SkipLargeLineHeightLines(2.0f);
    EXPECT_TRUE(result);
}
} // namespace OHOS::Ace::NG