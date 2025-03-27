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

#include "test/unittest/core/pattern/test_ng.h"

#include "core/components_ng/pattern/grid/grid_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_event_hub.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;

class GridTestNg : public TestNG {
public:
};

/**
 * @tc.name: BuildScrollAlignInfo001
 * @tc.desc: Test ScrollablePattern BuildScrollAlignInfo
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
 * @tc.desc: Test ScrollablePattern BuildScrollAlignInfo
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
 * @tc.desc: Test ScrollablePattern BuildScrollAlignInfo
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
 * @tc.desc: Test ScrollablePattern BuildScrollAlignInfo
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
 * @tc.desc: Test ScrollablePattern BuildScrollAlignInfo
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
 * @tc.desc: Test ScrollablePattern BuildScrollAlignInfo
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
 * @tc.desc: Test ScrollablePattern GetIrregularIndexesString
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
 * @tc.desc: Test ScrollablePattern GetIrregularIndexesString
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
 * @tc.desc: Test ScrollablePattern DumpAdvanceInfo
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
 * @tc.desc: Test ScrollablePattern DumpAdvanceInfo
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
 * @tc.desc: Test ScrollablePattern DumpAdvanceInfo
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
 * @tc.desc: Test ScrollablePattern DumpAdvanceInfo
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
 * @tc.desc: Test ScrollablePattern DumpAdvanceInfo
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
 * @tc.desc: Test ScrollablePattern DumpAdvanceInfo
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
 * @tc.desc: Test ScrollablePattern DumpAdvanceInfo
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
 * @tc.desc: Test ScrollablePattern DumpAdvanceInfo8
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
 * @tc.desc: Test ScrollablePattern DumpAdvanceInfo
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
 * @tc.desc: Test ScrollablePattern DumpAdvanceInfo
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
 * @tc.desc: Test ScrollablePattern DumpAdvanceInfo
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
 * @tc.desc: Test ScrollablePattern DumpAdvanceInfo
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
 * @tc.desc: Test ScrollablePattern DumpAdvanceInfo
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
} // namespace OHOS::Ace::NG