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

#include "test/unittest/core/pattern/test_ng.h"

#include "core/components_ng/property/measure_property.h"
#define protected public
#define private public
#include "water_flow_item_maps.h"

#include "core/components_ng/pattern/waterflow/layout/top_down/water_flow_layout_info.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
class WaterFlowLayoutInfoTest : public TestNG {
public:
    void InitLayoutInfoForOverScrolledDelta(WaterFlowLayoutInfo& layoutInfo);
};

void WaterFlowLayoutInfoTest::InitLayoutInfoForOverScrolledDelta(WaterFlowLayoutInfo& layoutInfo)
{
    layoutInfo.itemEnd_ = true;
    layoutInfo.currentOffset_ = 100.0f;
    layoutInfo.maxHeight_ = 400.0f;
    layoutInfo.lastMainSize_ = 600.0f;
}

/**
 * @tc.name: GetCrossIndexForNextItem001
 * @tc.desc: Test functions in WaterFlowLayoutInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowLayoutInfoTest, GetCrossIndexForNextItem001, TestSize.Level1)
{
    WaterFlowLayoutInfo info;
    info.items_ = ITEM_MAP_1;

    auto res = info.GetCrossIndexForNextItem(0);
    EXPECT_EQ(res.crossIndex, 2);
    EXPECT_EQ(res.lastItemIndex, 2);

    res = info.GetCrossIndexForNextItem(1);
    EXPECT_EQ(res.crossIndex, 0);
    EXPECT_EQ(res.lastItemIndex, -1);

    res = info.GetCrossIndexForNextItem(2);
    EXPECT_EQ(res.crossIndex, 2);
    EXPECT_EQ(res.lastItemIndex, 7);
}

/**
 * @tc.name: FastSolveStartIndex001
 * @tc.desc: Test FastSolveStartIndex in WaterFlowLayoutInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowLayoutInfoTest, FastSolveStartIndex001, TestSize.Level1)
{
    WaterFlowLayoutInfo info;
    EXPECT_EQ(info.FastSolveStartIndex(), 0);

    info.items_ = ITEM_MAP_1;
    info.endPosArray_ = END_POS_ARRAY_1;
    info.itemInfos_ = ITEM_INFO_1;

    info.currentOffset_ = -40.0f;
    EXPECT_EQ(info.FastSolveStartIndex(), 0);

    info.currentOffset_ = -90.0f;
    EXPECT_EQ(info.FastSolveStartIndex(), 5);

    info.currentOffset_ = -55.0f;
    EXPECT_EQ(info.FastSolveStartIndex(), 3);

    info.currentOffset_ = -20.0f;
    EXPECT_EQ(info.FastSolveStartIndex(), 0);

    info.currentOffset_ = -115.0f;
    EXPECT_EQ(info.FastSolveStartIndex(), 9);
}

/**
 * @tc.name: FastSolveStartIndex002
 * @tc.desc: Test FastSolveStartIndex in WaterFlowLayoutInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowLayoutInfoTest, FastSolveStartIndex002, TestSize.Level1)
{
    WaterFlowLayoutInfo info;

    info.items_ = ITEM_MAP_1;
    info.endPosArray_ = END_POS_ARRAY_1;
    info.itemInfos_ = ITEM_INFO_1;

    info.currentOffset_ = -1000.0f;
    EXPECT_EQ(info.FastSolveStartIndex(), 9);

    info.currentOffset_ = 1000.0f;
    EXPECT_EQ(info.FastSolveStartIndex(), 0);
}

/**
 * @tc.name: FastSolveStartIndex003
 * @tc.desc: Test return value when the height of first item is 0.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowLayoutInfoTest, FastSolveStartIndex003, TestSize.Level1)
{
    WaterFlowLayoutInfo info;

    info.items_ = ITEM_MAP_3;
    info.endPosArray_ = END_POS_ARRAY_3;

    info.currentOffset_ = 0.0f;
    EXPECT_EQ(info.FastSolveStartIndex(), 0);

    info.currentOffset_ = -1.0f;
    EXPECT_EQ(info.FastSolveStartIndex(), 1);

    info.currentOffset_ = 1.0f;
    EXPECT_EQ(info.FastSolveStartIndex(), 0);
}

/**
 * @tc.name: FastSolveStartIndex004
 * @tc.desc: Test return value when the height of first item is 0 and margin is not empty.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowLayoutInfoTest, FastSolveStartIndex004, TestSize.Level1)
{
    WaterFlowLayoutInfo info;

    info.items_ = ITEM_MAP_3;
    info.margins_ = { PaddingPropertyF { .top = 10.0f }};
    info.endPosArray_ = { { 10.0f, 0 }, { 30.0f, 1 }};

    EXPECT_EQ(info.TopMargin(), 10.0f);

    info.currentOffset_ = 0.0f;
    EXPECT_EQ(info.FastSolveStartIndex(), 0);

    info.currentOffset_ = -10.0f;
    EXPECT_EQ(info.FastSolveStartIndex(), 0);

    info.currentOffset_ = -11.0f;
    EXPECT_EQ(info.FastSolveStartIndex(), 1);
}

/**
 * @tc.name: FastSolveEndIndex001
 * @tc.desc: Test FastSolveEndIndex in WaterFlowLayoutInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowLayoutInfoTest, FastSolveEndIndex001, TestSize.Level1)
{
    WaterFlowLayoutInfo info;
    EXPECT_EQ(info.FastSolveEndIndex(50.0f), -1);

    info.items_ = ITEM_MAP_1;
    info.endPosArray_ = END_POS_ARRAY_1;
    info.itemInfos_ = ITEM_INFO_1;
    info.childrenCount_ = 10;

    info.currentOffset_ = -40.0f;
    EXPECT_EQ(info.FastSolveEndIndex(50.0f), 7);
    EXPECT_EQ(info.FastSolveEndIndex(10.0f), 4);

    info.currentOffset_ = -90.0f;
    EXPECT_EQ(info.FastSolveEndIndex(50.0f), 9);

    info.currentOffset_ = -55.0f;
    EXPECT_EQ(info.FastSolveEndIndex(10.0f), 4);
    EXPECT_EQ(info.FastSolveEndIndex(55.0f), 9);

    info.currentOffset_ = 0.0f;
    EXPECT_EQ(info.FastSolveEndIndex(35.0f), 3);
}

/**
 * @tc.name: FastSolveEndIndex002
 * @tc.desc: Test FastSolveEndIndex in WaterFlowLayoutInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowLayoutInfoTest, FastSolveEndIndex002, TestSize.Level1)
{
    WaterFlowLayoutInfo info;
    EXPECT_EQ(info.FastSolveEndIndex(50.0f), -1);

    info.items_ = ITEM_MAP_1;
    info.endPosArray_ = END_POS_ARRAY_1;
    info.itemInfos_ = ITEM_INFO_1;
    info.childrenCount_ = 10;

    info.currentOffset_ = -1000.0f;
    EXPECT_EQ(info.FastSolveEndIndex(50.0f), 9);

    info.currentOffset_ = 1000.0f;
    EXPECT_EQ(info.FastSolveEndIndex(50.0f), 0);
}

/**
 * @tc.name: GetSegment001
 * @tc.desc: Test GetSegment in WaterFlowLayoutInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowLayoutInfoTest, GetSegment001, TestSize.Level1)
{
    WaterFlowLayoutInfo info;
    info.childrenCount_ = 20;
    EXPECT_EQ(info.GetSegment(5), 0);
    EXPECT_EQ(info.GetSegment(0), 0);
    EXPECT_EQ(info.GetSegment(10), 0);

    info.segmentTails_ = { 5, 13, 18, 19 };
    for (int i = 0; i <= 2; ++i) {
        if (i == 2) {
            EXPECT_EQ(info.segmentCache_.size(), 6);
            EXPECT_EQ(info.segmentCache_.at(15), 2);
            info.segmentCache_.clear();
        }
        // test cache on the second iteration
        EXPECT_EQ(info.GetSegment(2), 0);
        EXPECT_EQ(info.GetSegment(3), 0);
        EXPECT_EQ(info.GetSegment(8), 1);
        EXPECT_EQ(info.GetSegment(15), 2);
        EXPECT_EQ(info.GetSegment(18), 2);
        EXPECT_EQ(info.GetSegment(19), 3);
    }
}

/**
 * @tc.name: GetSegment002
 * @tc.desc: Test GetSegment in WaterFlowLayoutInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowLayoutInfoTest, GetSegment002, TestSize.Level1)
{
    WaterFlowLayoutInfo info;

    info.segmentTails_ = SEGMENT_TAILS_1;
    EXPECT_EQ(info.GetSegment(0), 0);
    EXPECT_EQ(info.GetSegment(4), 0);
    EXPECT_EQ(info.GetSegment(5), 2);
    EXPECT_EQ(info.GetSegment(9), 2);
    EXPECT_EQ(info.GetSegment(15), 2);
}

/**
 * @tc.name: SetNextSegmentStartPos001
 * @tc.desc: Test SetNextSegmentStartPos in WaterFlowLayoutInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowLayoutInfoTest, SetNextSegmentStartPos001, TestSize.Level1)
{
    WaterFlowLayoutInfo info;

    info.segmentTails_ = { 3, 5, 5, 10 };
    info.segmentStartPos_ = { 5.0f };

    info.margins_ = { PaddingPropertyF { .top = 5.0f, .bottom = 1.0f },
        PaddingPropertyF { .top = 10.0f, .bottom = 5.0f }, PaddingPropertyF { .top = 1.0f, .bottom = 5.0f },
        PaddingPropertyF { .bottom = 5.0f } };

    info.endPosArray_ = { { 100.0f, 0 } };
    info.SetNextSegmentStartPos(2);
    const std::vector<float> CMP_0 = { 5.0f };
    EXPECT_EQ(info.segmentStartPos_, CMP_0);

    info.endPosArray_ = { { 100.0f, 0 }, { 120.0f, 3 } };
    const std::vector<float> CMP_1 = { 5.0f, 131.0f };
    for (int i = 0; i <= 1; ++i) {
        info.SetNextSegmentStartPos(3);
        EXPECT_EQ(info.segmentStartPos_, CMP_1);
    }

    info.endPosArray_ = { { 100.0f, 0 }, { 120.0f, 3 }, { 150.0f, 4 } };
    const std::vector<float> CMP_2 = { 5.0f, 131.0f, 156.0f, 161.0f };
    for (int i = 0; i <= 1; ++i) {
        info.SetNextSegmentStartPos(5);
        EXPECT_EQ(info.segmentStartPos_, CMP_2);
    }

    info.SetNextSegmentStartPos(6);
    EXPECT_EQ(info.segmentStartPos_, CMP_2);

    info.SetNextSegmentStartPos(10);
    EXPECT_EQ(info.segmentStartPos_, CMP_2);
}

/**
 * @tc.name: InitSegments
 * @tc.desc: Test InitSegments
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowLayoutInfoTest, InitSegments001, TestSize.Level1)
{
    WaterFlowLayoutInfo info;
    info.InitSegments(SECTION_7, 0);
    for (int i = 0; i < 2; ++i) {
        info.itemInfos_.resize(37);
        info.segmentStartPos_.resize(3);

        auto modSec = SECTION_7;
        modSec[i] = ADD_SECTION_6[0];
        info.InitSegments(modSec, i);
        EXPECT_EQ(info.segmentStartPos_.size(), i);
        if (i == 0) {
            EXPECT_TRUE(info.itemInfos_.empty());
        } else {
            EXPECT_EQ(info.itemInfos_.size(), info.segmentTails_[i - 1] + 1);
        }
        EXPECT_EQ(info.items_[i].size(), 2);
    }
    auto mod = SECTION_7;
    mod.push_back(ADD_SECTION_6[0]);
    info.InitSegments(mod, 2);
    EXPECT_EQ(info.items_.size(), 5);
    EXPECT_EQ(info.items_[1].size(), 2);
}

/**
 * @tc.name: UpdateStartIndexWhenMeasureInNextFrame
 * @tc.desc: Test UpdateStartIndex in WaterFlowLayoutInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowLayoutInfoTest, UpdateStartIndexWhenMeasureInNextFrame, TestSize.Level1)
{
    WaterFlowLayoutInfo info;
    info.childrenCount_ = 100;
    info.startIndex_ = 0;
    info.endIndex_ = 80;
    info.measureInNextFrame_ = true;
    info.UpdateStartIndex();
    EXPECT_EQ(info.startIndex_, info.endIndex_);
}

/**
 * @tc.name: ContentOffsetsAffectEndPosCalculation
 * @tc.desc: Test GetOverScrolledDelta with contentOffset.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowLayoutInfoTest, ContentOffsetsAffectEndPosCalculation, TestSize.Level1)
{
    WaterFlowLayoutInfo layoutInfo;
    InitLayoutInfoForOverScrolledDelta(layoutInfo);
    layoutInfo.contentStartOffset_ = 20.0f;
    layoutInfo.contentEndOffset_ = 30.0f;

    // endPos = 100 + 400 + 30 = 530
    // GreatNotEqual? : 600 - 20 = 580 > 530? true
    // endPos: 100 + 600 - 20 - 30 = 650
    float delta = -50.0f; // newEndPos = 650 - 50 = 600

    auto result = layoutInfo.GetOverScrolledDelta(delta);

    // endPos >= lastMainSize_ (650 >= 600) && newEndPos < lastMainSize_ (600 < 600)?
    // Note: 600 < 600 is false, so it should take another branch.
    // In reality, the condition endPos >= lastMainSize_ && newEndPos < lastMainSize_ does not hold.
    // Therefore, offset.end should be 0.
    EXPECT_FLOAT_EQ(result.end, 0.0f);
}

/**
 * @tc.name: ZeroContentStartOffset
 * @tc.desc: Test GetOverScrolledDelta with contentEndOffset.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowLayoutInfoTest, ZeroContentStartOffset, TestSize.Level1)
{
    WaterFlowLayoutInfo layoutInfo;
    InitLayoutInfoForOverScrolledDelta(layoutInfo);
    layoutInfo.contentStartOffset_ = 0.0f;
    layoutInfo.contentEndOffset_ = 10.0f;

    // endPos = 100 + 400 + 10 = 510
    // GreatNotEqual? : 600 - 0 = 600 > 510? true
    // So endPos will be recalculated as: 100 + 600 - 0 - 10 = 690
    float delta = -100.0f; // newEndPos = 690 - 100 = 590

    auto result = layoutInfo.GetOverScrolledDelta(delta);

    // endPos >= lastMainSize_ (690 >= 600) && newEndPos < lastMainSize_ (590 < 600)? true
    // offset.end = 590 - 600 = -10
    EXPECT_FLOAT_EQ(result.end, -10.0f);
}

/**
 * @tc.name: ZeroContentStartOffset
 * @tc.desc: Test GetOverScrolledDelta with contentStartOffset.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowLayoutInfoTest, ZeroContentEndOffset, TestSize.Level1)
{
    WaterFlowLayoutInfo layoutInfo;
    InitLayoutInfoForOverScrolledDelta(layoutInfo);
    layoutInfo.contentStartOffset_ = 15.0f;
    layoutInfo.contentEndOffset_ = 0.0f;

    // endPos = 100 + 400 + 0 = 500
    // GreatNotEqual? : 600 - 15 = 585 > 500? true
    // So endPos will be recalculated as: 100 + 600 - 0 - 15 = 685
    float delta = 50.0f; // newEndPos = 685 + 50 = 735

    auto result = layoutInfo.GetOverScrolledDelta(delta);

    // endPos >= lastMainSize_ (685 >= 600) && newEndPos < lastMainSize_ (735 < 600)? false
    // so offset.end should be 0
    EXPECT_FLOAT_EQ(result.end, 0.0f);
}

/**
 * @tc.name: LargeContentStartOffset
 * @tc.desc: Test GetOverScrolledDelta with large contentStartOffset.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowLayoutInfoTest, LargeContentStartOffset, TestSize.Level1)
{
    WaterFlowLayoutInfo layoutInfo;
    InitLayoutInfoForOverScrolledDelta(layoutInfo);
    layoutInfo.contentStartOffset_ = 200.0f;
    layoutInfo.contentEndOffset_ = 10.0f;

    // endPos = 100 + 400 + 10 = 510
    // GreatNotEqual? : 600 - 200 = 400 > 510? false
    float delta = 50.0f; // newEndPos = 510 + 50 = 560

    auto result = layoutInfo.GetOverScrolledDelta(delta);

    // endPos < lastMainSize_ (510 < 600) && newEndPos < lastMainSize_ (560 < 600)? true
    // offset.end = delta = 50
    EXPECT_FLOAT_EQ(result.end, 50.0f);
}

/**
 * @tc.name: LargeContentEndOffset
 * @tc.desc: Test GetOverScrolledDelta with large contentEndOffset.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowLayoutInfoTest, LargeContentEndOffset, TestSize.Level1)
{
    WaterFlowLayoutInfo layoutInfo;
    InitLayoutInfoForOverScrolledDelta(layoutInfo);
    layoutInfo.contentStartOffset_ = 10.0f;
    layoutInfo.contentEndOffset_ = 150.0f;

    // endPos = 100 + 400 + 150 = 650
    // GreatNotEqual? : 600 - 10 = 590 > 650? false
    float delta = -100.0f; // newEndPos = 650 - 100 = 550

    auto result = layoutInfo.GetOverScrolledDelta(delta);

    // endPos >= lastMainSize_ (650 >= 600) && newEndPos < lastMainSize_ (550 < 600)? true
    // offset.end = 550 - 600 = -50
    EXPECT_FLOAT_EQ(result.end, -50.0f);
}

/**
 * @tc.name: GreatNotEqualBoundary
 * @tc.desc: Test GetOverScrolledDelta with large contentEndOffset.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowLayoutInfoTest, GreatNotEqualBoundary, TestSize.Level1)
{
    WaterFlowLayoutInfo layoutInfo;
    InitLayoutInfoForOverScrolledDelta(layoutInfo);
    layoutInfo.contentStartOffset_ = 90.0f;
    layoutInfo.contentEndOffset_ = 10.0f;

    // endPos = 100 + 400 + 10 = 510
    // GreatNotEqual?: 600 - 90 = 510 > 510? false
    float delta = 50.0f; // newEndPos = 510 + 50 = 560

    auto result = layoutInfo.GetOverScrolledDelta(delta);

    // endPos < lastMainSize_ (510 < 600) && newEndPos < lastMainSize_ (560 < 600)? true
    // offset.end = delta = 50
    EXPECT_FLOAT_EQ(result.end, 50.0f);
}

/**
 * @tc.name: ContentOffsetsChangeGreatNotEqualCondition
 * @tc.desc: Test GetOverScrolledDelta with contentOffset.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowLayoutInfoTest, ContentOffsetsChangeGreatNotEqualCondition, TestSize.Level1)
{
    WaterFlowLayoutInfo layoutInfo;
    InitLayoutInfoForOverScrolledDelta(layoutInfo);
    // case1: GreatNotEqual is true
    layoutInfo.contentStartOffset_ = 50.0f;
    layoutInfo.contentEndOffset_ = 10.0f;

    // endPos = 100 + 400 + 10 = 510
    // GreatNotEqual? : 600 - 50 = 550 > 510? true
    float delta = 50.0f;
    auto result1 = layoutInfo.GetOverScrolledDelta(delta);

    // case2: Adjust contentStartOffset_ so that GreatNotEqual is false.
    layoutInfo.contentStartOffset_ = 100.0f;

    // endPos = 100 + 400 + 10 = 510
    // GreatNotEqual? : 600 - 100 = 500 > 510? false
    auto result2 = layoutInfo.GetOverScrolledDelta(delta);
    EXPECT_NE(result1.end, result2.end);
}

/**
 * @tc.name: ContentOffsetsAffectOverscrollBehavior
 * @tc.desc: Test GetOverScrolledDelta with large contentEndOffset.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowLayoutInfoTest, ContentOffsetsAffectOverscrollBehavior, TestSize.Level1)
{
    WaterFlowLayoutInfo layoutInfo;
    InitLayoutInfoForOverScrolledDelta(layoutInfo);
    layoutInfo.contentStartOffset_ = 20.0f;
    layoutInfo.contentEndOffset_ = 30.0f;
    layoutInfo.currentOffset_ = 0.0f;

    // Test overScroll with bottom
    // endPos = 0 + 400 + 30 = 430
    // GreatNotEqual?: 600 - 20 = 580 > 430? true
    // endPos = 0 + 600 - 20 - 30 = 550
    float delta = 100.0f; // scroll down 100

    // newEndPos = 550 + 100 = 650
    auto result = layoutInfo.GetOverScrolledDelta(delta);
    // endPos < lastMainSize_ (550 < 600) && newEndPos >= lastMainSize_ (650 >= 600)? true
    // offset.end = 600 - 550 = 50
    EXPECT_FLOAT_EQ(result.end, 50.0f);
}
} // namespace OHOS::Ace::NG
