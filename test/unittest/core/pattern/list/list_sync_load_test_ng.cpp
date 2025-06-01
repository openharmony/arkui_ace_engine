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

#include "list_test_ng.h"
#include "test/mock/core/animation/mock_animation_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

namespace OHOS::Ace::NG {
class ListSyncLoadTestNg : public ListTestNg {
public:
    void TearDown() override;
    ListItemModelNG CreateListItem();
    void CreateListItems(int32_t itemNumber);
};

void ListSyncLoadTestNg::TearDown()
{
    ListTestNg::TearDown();
    MockPipelineContext::GetCurrent()->SetResponseTime(INT32_MAX);
}

ListItemModelNG ListSyncLoadTestNg::CreateListItem()
{
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(GetElmtId());
    ListItemModelNG itemModel;
    itemModel.Create([](int32_t) {}, V2::ListItemStyle::NONE);
    Axis axis = layoutProperty_->GetListDirection().value_or(Axis::VERTICAL);
    SetSize(axis, CalcLength(FILL_LENGTH), CalcLength(ITEM_MAIN_SIZE));
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    frameNode->measureCallback_ = [](RefPtr<Kit::FrameNode>& node) {
        NG::MockPipelineContext::GetCurrent()->DecResponseTime();
    };
    return itemModel;
}

void ListSyncLoadTestNg::CreateListItems(int32_t itemNumber)
{
    for (int32_t index = 0; index < itemNumber; index++) {
        CreateListItem();
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
}

/**
 * @tc.name: SyncLoad001
 * @tc.desc: Test List sync load
 * @tc.type: FUNC
 */
HWTEST_F(ListSyncLoadTestNg, SyncLoad001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List
     * @tc.expected: List load 2 item in first frame
     */
    ListModelNG model = CreateList();
    CreateListItems(10);
    MockPipelineContext::GetCurrent()->SetResponseTime(2);
    CreateDone();
    EXPECT_EQ(pattern_->itemPosition_.size(), 2);
    EXPECT_TRUE(pattern_->prevMeasureBreak_);

    /**
     * @tc.steps: step1. Flush next frame
     * @tc.expected: List load 2 item in 2th frame
     */
    MockPipelineContext::GetCurrent()->SetResponseTime(2);
    FlushUITasks(frameNode_);
    EXPECT_EQ(pattern_->itemPosition_.size(), 4);
    EXPECT_FALSE(pattern_->prevMeasureBreak_);
}

/**
 * @tc.name: SyncLoad002
 * @tc.desc: Test List sync load, jump to index with end align
 * @tc.type: FUNC
 */
HWTEST_F(ListSyncLoadTestNg, SyncLoad002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List, jump to index with end align
     * @tc.expected: List load 2 item in first frame
     */
    ListModelNG model = CreateList();
    CreateListItems(10);
    MockPipelineContext::GetCurrent()->SetResponseTime(2);
    pattern_->jumpIndex_ = 0;
    pattern_->scrollAlign_ = ScrollAlign::END;
    CreateDone();
    EXPECT_EQ(pattern_->itemPosition_.size(), 2);
    EXPECT_TRUE(pattern_->prevMeasureBreak_);

    /**
     * @tc.steps: step1. Flush next frame
     * @tc.expected: List load 2 item in 2th frame
     */
    MockPipelineContext::GetCurrent()->SetResponseTime(2);
    FlushUITasks(frameNode_);
    EXPECT_EQ(pattern_->itemPosition_.size(), 4);
    EXPECT_FALSE(pattern_->prevMeasureBreak_);
}

/**
 * @tc.name: SyncLoad003
 * @tc.desc: Create List without height, List not sync load
 * @tc.type: FUNC
 */
HWTEST_F(ListSyncLoadTestNg, SyncLoad003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List without height
     * @tc.expected: List not sync load
     */
    ListModelNG model = CreateList();
    CreateListItems(6);
    layoutProperty_->ClearUserDefinedIdealSize(false, true);
    MockPipelineContext::GetCurrent()->SetResponseTime(2);
    CreateDone();
    EXPECT_EQ(pattern_->itemPosition_.size(), 6);
    EXPECT_FALSE(pattern_->prevMeasureBreak_);
}
}
