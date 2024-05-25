/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "test/unittest/core/pattern/waterflow/water_flow_test_ng.h"

#include "core/components_ng/pattern/waterflow/layout/sliding_window/water_flow_layout_info_sw.h"
namespace OHOS::Ace::NG {
class WaterFlowSWTest : public WaterFlowTestNg {
protected:
    void GetInstance() override
    {
        WaterFlowTestNg::GetInstance();
        info_ = AceType::DynamicCast<WaterFlowLayoutInfoSW>(pattern_->layoutInfo_);
        EXPECT_TRUE(info_);
    }

    RefPtr<WaterFlowLayoutInfoSW> info_;
};

/**
 * @tc.name: Regular001
 * @tc.desc: waterFlow with fixed column
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, Regular001, TestSize.Level1)
{
    CreateWithItem([](WaterFlowModelNG model) {
        ViewAbstract::SetWidth(CalcLength(400.0f));
        ViewAbstract::SetHeight(CalcLength(200.f));
        model.SetColumnsTemplate("1fr 1fr 1fr");
    });
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(info_->lanes_[0].items_.size(), 2);
    EXPECT_EQ(info_->lanes_[0].items_.back().idx, 3);
    EXPECT_EQ(info_->lanes_[0].items_.back().mainSize, 200.0f);
    EXPECT_EQ(info_->lanes_[0].endPos, 300.0f);
    EXPECT_EQ(info_->lanes_[1].items_.back().idx, 1);
    EXPECT_EQ(info_->lanes_[1].endPos, 200.0f);
    EXPECT_EQ(info_->lanes_[2].endPos, 200.0f);
    EXPECT_EQ(info_->lanes_[2].items_.back().idx, 4);
    EXPECT_EQ(info_->startIndex_, 0);
    EXPECT_EQ(info_->endIndex_, 4);
}

/**
 * @tc.name: Reset001
 * @tc.desc: waterFlow children update
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, Reset001, TestSize.Level1)
{
    CreateWithItem([](WaterFlowModelNG model) {
        model.SetColumnsTemplate("1fr 1fr");
        model.SetFooter(GetDefaultHeaderBuilder());
    });
    pattern_->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(info_->startIndex_, 0);
    EXPECT_EQ(info_->endIndex_, 9);
    for (int i = 0; i < 5; i++) {
        frameNode_->RemoveChildAtIndex(6);
    }
    frameNode_->ChildrenUpdatedFrom(6);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(info_->startIndex_, 0);
    EXPECT_EQ(info_->endIndex_, 4);
    EXPECT_FALSE(info_->idxToLane_.count(5));
    EXPECT_EQ(GetChildY(frameNode_, 1), 0.0f);
    EXPECT_EQ(GetChildY(frameNode_, 5), 200.0f);
    EXPECT_EQ(GetChildY(frameNode_, 0), 400.0f);
}

/**
 * @tc.name: Reset002
 * @tc.desc: waterFlow children update before startIdx
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, Reset002, TestSize.Level1)
{
    CreateWithItem([](WaterFlowModelNG model) {
        model.SetColumnsTemplate("1fr 1fr");
        model.SetFooter(GetDefaultHeaderBuilder());
        CreateItem(100);
    });
    pattern_->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(info_->startIndex_, 99);
    EXPECT_EQ(info_->endIndex_, 109);
    for (int i = 0; i < 5; i++) {
        frameNode_->RemoveChildAtIndex(6);
    }
    frameNode_->ChildrenUpdatedFrom(6);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(info_->startIndex_, 95);
    EXPECT_EQ(info_->endIndex_, 104);
    EXPECT_TRUE(info_->offsetEnd_);
    EXPECT_EQ(GetChildY(frameNode_, 95), -150.0f);
    EXPECT_EQ(GetChildY(frameNode_, 0), 750.0f);
}

/**
 * @tc.name: Jump001
 * @tc.desc: waterFlow jump
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, Jump001, TestSize.Level1)
{
    CreateWithItem([](WaterFlowModelNG model) {
        ViewAbstract::SetWidth(CalcLength(400.0f));
        ViewAbstract::SetHeight(CalcLength(200.f));
        model.SetColumnsTemplate("1fr 1fr 1fr");
    });
    pattern_->ScrollToIndex(8);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(info_->startIndex_, 5);
    EXPECT_EQ(info_->endIndex_, 9);
    EXPECT_EQ(info_->idxToLane_.at(8), 2);
    EXPECT_EQ(info_->lanes_[0].endPos, 200.0f);
    EXPECT_EQ(info_->lanes_[1].startPos, -100.0f);
    EXPECT_EQ(info_->lanes_[1].endPos, 300.0f);
    EXPECT_EQ(info_->lanes_[2].endPos, 100.0f);
    EXPECT_EQ(info_->lanes_[0].items_.size(), 1);
    EXPECT_EQ(info_->lanes_[0].items_.front().idx, 7);
    EXPECT_EQ(info_->lanes_[1].items_.size(), 2);
    EXPECT_EQ(info_->lanes_[1].items_.front().idx, 5);
    EXPECT_EQ(info_->lanes_[1].items_.back().idx, 9);
    EXPECT_EQ(info_->lanes_[2].items_.size(), 2);
    EXPECT_TRUE(info_->itemEnd_);
    EXPECT_FALSE(info_->offsetEnd_);
    EXPECT_EQ(info_->startIndex_, 5);
    EXPECT_EQ(info_->endIndex_, 9);
}

/**
 * @tc.name: ChangeTemplate001
 * @tc.desc: waterFlow change lane count
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, ChangeTemplate001, TestSize.Level1)
{
    CreateWithItem([](WaterFlowModelNG model) {
        ViewAbstract::SetWidth(CalcLength(600.0f));
        ViewAbstract::SetHeight(CalcLength(200.f));
        model.SetColumnsTemplate("1fr 1fr 1fr");
    });
    UpdateCurrentOffset(-300.0f);
    EXPECT_EQ(info_->startIndex_, 5);
    EXPECT_EQ(info_->endIndex_, 9);
    EXPECT_EQ(GetChildOffset(frameNode_, 5), OffsetF(200.0f, -100.0f));
    EXPECT_EQ(GetChildOffset(frameNode_, 6), OffsetF(400.0f, -100.0f));
    EXPECT_EQ(GetChildOffset(frameNode_, 7), OffsetF(0.0f, 0.0f));
    EXPECT_EQ(GetChildOffset(frameNode_, 8), OffsetF(400.0f, 0.0f));
    EXPECT_EQ(GetChildOffset(frameNode_, 9), OffsetF(200.0f, 100.0f));
    layoutProperty_->UpdateColumnsTemplate("1fr 1fr");
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(info_->startIndex_, 5);
    EXPECT_EQ(info_->endIndex_, 8);
    EXPECT_EQ(GetChildOffset(frameNode_, 5), OffsetF(0.0f, -100.0f));
    EXPECT_EQ(GetChildOffset(frameNode_, 6), OffsetF(300.0f, -100.0f));
    EXPECT_EQ(GetChildOffset(frameNode_, 7), OffsetF(300.0f, 0.0f));
    EXPECT_EQ(GetChildOffset(frameNode_, 8), OffsetF(0.0f, 100.0f));
}

/**
 * @tc.name: ModifyItem002
 * @tc.desc: Test WaterFlow reacting to child height change.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, ModifyItem002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Calling the ScrollToIndex interface to set values to 20 and true.
     * @tc.expected: pattern_->targetIndex_ is 20
     */
    Create([](WaterFlowModelNG model) {
        model.SetColumnsTemplate("1fr 1fr");
        model.SetFooter(GetDefaultHeaderBuilder());
        CreateItem(80);
    });

    pattern_->ScrollToIndex(50, false, ScrollAlign::CENTER);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(info_->startIndex_, 44);
    EXPECT_EQ(GetChildY(frameNode_, 45), -50.0f);
    EXPECT_EQ(GetChildY(frameNode_, 51), 350.0f);
    auto child = GetChildFrameNode(frameNode_, 49);
    child->layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(300.0)));
    child->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(info_->startIndex_, 44);
    EXPECT_EQ(GetChildY(frameNode_, 45), -50.0f);
    EXPECT_EQ(GetChildHeight(frameNode_, 49), 300.0f);

    child = GetChildFrameNode(frameNode_, 40);
    child->layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(10.0)));
    child->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(info_->startIndex_, 44);
    EXPECT_EQ(GetChildY(frameNode_, 45), -50.0f);
    EXPECT_FALSE(child->IsActive());
    EXPECT_FALSE(info_->idxToLane_.count(40));

    // update footer
    pattern_->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(GetChildY(frameNode_, 80), 550.0f);

    child = GetChildFrameNode(frameNode_, 0);
    child->layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(1.0)));
    child->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(GetChildY(frameNode_, 80), 599.0f);
    EXPECT_EQ(GetChildHeight(frameNode_, 0), 1.0f);
}

/**
 * @tc.name: OverScroll001
 * @tc.desc: Test overScroll past limits
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, OverScroll001, TestSize.Level1)
{
    Create([](WaterFlowModelNG model) {
        model.SetColumnsTemplate("1fr 1fr");
        model.SetFooter(GetDefaultHeaderBuilder());
        model.SetEdgeEffect(EdgeEffect::SPRING, true);
        CreateItem(50);
    });
    pattern_->SetAnimateCanOverScroll(true);
    UpdateCurrentOffset(30000.0f);
    const float startPos = info_->StartPos();
    EXPECT_TRUE(info_->startIndex_ > info_->endIndex_);
    EXPECT_GT(info_->StartPos(), 2000.0f);
    EXPECT_TRUE(info_->lanes_[0].items_.empty());
    EXPECT_TRUE(info_->lanes_[1].items_.empty());

    info_->delta_ = -50.0f;
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(info_->StartPos(), startPos - 50.0f);
    EXPECT_TRUE(info_->startIndex_ > info_->endIndex_);
    EXPECT_TRUE(info_->lanes_[0].items_.empty());
    EXPECT_TRUE(info_->lanes_[1].items_.empty());

    UpdateCurrentOffset(-35000.0f);
    EXPECT_EQ(info_->startIndex_, 11);
    EXPECT_EQ(info_->endIndex_, 22);
    EXPECT_LT(info_->StartPos(), 0.0f);
    EXPECT_GT(info_->EndPos(), 800.0f);
}

/**
 * @tc.name: OverScroll002
 * @tc.desc: Test overScroll past limits
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, OverScroll002, TestSize.Level1)
{
    Create([](WaterFlowModelNG model) {
        model.SetColumnsTemplate("1fr 1fr");
        model.SetFooter(GetDefaultHeaderBuilder());
        model.SetEdgeEffect(EdgeEffect::SPRING, true);
        CreateItem(50);
    });
    pattern_->SetAnimateCanOverScroll(true);
    pattern_->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    FlushLayoutTask(frameNode_);

    UpdateCurrentOffset(-30000.0f);
    EXPECT_TRUE(info_->startIndex_ > info_->endIndex_);
    EXPECT_TRUE(info_->lanes_[0].items_.empty());
    EXPECT_TRUE(info_->lanes_[1].items_.empty());
    const float endPos = info_->EndPos();
    EXPECT_LT(info_->EndPos(), -2000.0f);

    info_->delta_ = 30.0f;
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(info_->EndPos(), endPos + 30.0f);
    EXPECT_TRUE(info_->startIndex_ > info_->endIndex_);
    EXPECT_TRUE(info_->lanes_[0].items_.empty());
    EXPECT_TRUE(info_->lanes_[1].items_.empty());

    UpdateCurrentOffset(35000.0f);
    EXPECT_EQ(info_->startIndex_, 28);
    EXPECT_EQ(info_->endIndex_, 41);
    EXPECT_LT(info_->StartPos(), 0.0f);
    EXPECT_GT(info_->EndPos(), 800.0f);
}

/**
 * @tc.name: Misaligned001
 * @tc.desc: Test misalignment and adjustment
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, Misaligned001, TestSize.Level1)
{
    Create([](WaterFlowModelNG model) {
        model.SetColumnsTemplate("1fr 1fr");
        model.SetFooter(GetDefaultHeaderBuilder());
        CreateItem(50);
    });
    EXPECT_FALSE(info_->IsMisaligned());
    pattern_->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    FlushLayoutTask(frameNode_);

    UpdateCurrentOffset(Infinity<float>());
    EXPECT_EQ(info_->startIndex_, 0);
    EXPECT_EQ(GetChildY(frameNode_, 1), 100.0f);
    EXPECT_EQ(GetChildX(frameNode_, 1), 240.0f);
    EXPECT_EQ(info_->jumpIndex_, 0);
    FlushLayoutTask(frameNode_);
    EXPECT_FALSE(info_->IsMisaligned());
    EXPECT_EQ(GetChildY(frameNode_, 1), 0.0f);
    EXPECT_EQ(GetChildX(frameNode_, 1), 0.0f);
    EXPECT_EQ(info_->lanes_[0].startPos, 0.0f);
    EXPECT_EQ(info_->lanes_[0].items_.front().idx, 0);
}

/**
 * @tc.name: PositionController100
 * @tc.desc: Test PositionController AnimateTo and ScrollTo, should be disabled
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, PositionController100, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List Item
     */
    Create([](WaterFlowModelNG model) {
        model.SetColumnsTemplate("1fr 1fr");
        CreateItem(TOTAL_LINE_NUMBER * 2);
    });
    auto controller = pattern_->positionController_;
    /**
     * @tc.steps: step8. Test AnimateTo function
     * @tc.expected: pattern_->isAnimationStop_ is false
     */
    pattern_->AnimateTo(1.5, 1.f, Curves::LINEAR, false, false);
    EXPECT_TRUE(pattern_->isAnimationStop_);

    /**
     * @tc.steps: step8. test event
     * @tc.expected: return the scroll event is ture.
     */
    bool isOnWillScrollCallBack = false;
    Dimension willScrollOffset;
    ScrollState willScrollState;
    auto onWillScroll = [&willScrollOffset, &willScrollState, &isOnWillScrollCallBack](
                            Dimension offset, ScrollState state, ScrollSource source) {
        willScrollOffset = offset;
        willScrollState = state;
        isOnWillScrollCallBack = true;
        ScrollFrameResult result;
        result.offset = offset;
        return result;
    };

    eventHub_->SetOnWillScroll(std::move(onWillScroll));
    pattern_->ScrollTo(ITEM_HEIGHT * 5);
    EXPECT_FALSE(isOnWillScrollCallBack);
}

/**
 * @tc.name: ScrollToEdge002
 * @tc.desc: ScrollToEdge and check overScroll
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, ScrollToEdge002, TestSize.Level1)
{
    Create([](WaterFlowModelNG model) {
        model.SetFooter(GetDefaultHeaderBuilder());
        model.SetColumnsTemplate("1fr 1fr 1fr");
        model.SetRowsGap(Dimension(5.0f));
        CreateRandomItem(100);
    });
    pattern_->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    FlushLayoutTask(frameNode_);
    auto info = pattern_->layoutInfo_;
    EXPECT_EQ(info->endIndex_, 99);
    EXPECT_EQ(GetChildOffset(frameNode_, info->footerIndex_), OffsetF(0.0f, 750.0f));
    EXPECT_EQ(info_->EndPos(), 750.0f);
    EXPECT_FALSE(info->OutOfBounds());
    EXPECT_EQ(info->GetOverScrolledDelta(20.0f).end, 0.0f);
    EXPECT_EQ(info->GetOverScrolledDelta(-10.0f).end, -10.0f);

    UpdateCurrentOffset(30.0f);
    EXPECT_EQ(info->GetOverScrolledDelta(-20.0f).end, 0.0f);
    EXPECT_EQ(info->GetOverScrolledDelta(20.0f).end, 0.0f);

    UpdateCurrentOffset(20.0f);
    EXPECT_EQ(info->GetOverScrolledDelta(-20.0f).end, 0.0f);
    EXPECT_EQ(info->GetOverScrolledDelta(20.0f).end, 0.0f);

    UpdateCurrentOffset(5.0f);
    EXPECT_FALSE(info->itemEnd_);
}
} // namespace OHOS::Ace::NG
