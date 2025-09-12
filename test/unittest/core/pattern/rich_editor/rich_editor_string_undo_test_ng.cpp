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
 
#include "test/unittest/core/pattern/rich_editor/rich_editor_common_test_ng.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/base/mock_task_executor.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_undo_manager.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class RichEditorStringUndoTestNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
};

void RichEditorStringUndoTestNg::SetUp()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    richEditorNode_ = FrameNode::GetOrCreateFrameNode(
        V2::RICH_EDITOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<RichEditorPattern>(); });
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    richEditorPattern->InitScrollablePattern();
    richEditorPattern->SetRichEditorController(AceType::MakeRefPtr<RichEditorController>());
    richEditorPattern->GetRichEditorController()->SetPattern(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
    richEditorPattern->CreateNodePaintMethod();
    richEditorNode_->GetGeometryNode()->SetContentSize({});
}

void RichEditorStringUndoTestNg::TearDown()
{
    richEditorNode_ = nullptr;
}

void RichEditorStringUndoTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

/**
 * @tc.name: GetStringFromOptionsList
 * @tc.desc: Test GetStringFromOptionsList.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStringUndoTestNg, GetStringFromOptionsList, TestSize.Level1)
{
    OptionsList optionsList;
    optionsList.push_back(TextSpanOptions{ .value = INIT_VALUE_1 });
    optionsList.push_back(ImageSpanOptions{});
    optionsList.push_back(SymbolSpanOptions{});
    optionsList.push_back(BuilderSpanOptions{});
    auto record = UndoRedoRecord{ .optionsListBefore = optionsList, .optionsListAfter = optionsList };
    EXPECT_EQ(record.GetStringBefore(), u"hello1    ");
    EXPECT_EQ(record.GetStringAfter(), u"hello1    ");
}

/**
 * @tc.name: ProcessDragDeleteRecord
 * @tc.desc: Test ProcessDragDeleteRecord.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStringUndoTestNg, ProcessDragDeleteRecord, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    StringUndoManager undoManager(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
    UndoRedoRecord record;
    record.rangeBefore = TextRange{ 0, 0 };
    record.rangeAfter = TextRange{ 0, 0 };
    record.restoreBuilderSpan = true;
    OptionsList optionsList;
    optionsList.push_back(SymbolSpanOptions{});
    optionsList.push_back(BuilderSpanOptions{});
    optionsList.push_back(TextSpanOptions{ .value = INIT_VALUE_1, .offset = 0 });
    record.optionsListAfter = optionsList;
    record.optionsListBefore = optionsList;
    undoManager.ProcessDragDeleteRecord(record);
    EXPECT_EQ(record.optionsListBefore->size(), 3);

    optionsList.push_back(BuilderSpanOptions{});
    record.optionsListBefore = optionsList;
    undoManager.ProcessDragDeleteRecord(record);
    EXPECT_EQ(record.optionsListBefore->size(), 4);

    optionsList.push_back(TextSpanOptions{ .value = INIT_VALUE_3, .offset = 0 });
    record.optionsListBefore = optionsList;
    undoManager.ProcessDragDeleteRecord(record);
    EXPECT_EQ(record.optionsListBefore->size(), 5);

    optionsList.push_back(ImageSpanOptions{});
    record.optionsListBefore = optionsList;
    undoManager.ProcessDragDeleteRecord(record);
    EXPECT_EQ(record.optionsListBefore->size(), 5);

    optionsList.push_back(SymbolSpanOptions{});
    record.optionsListBefore = optionsList;
    undoManager.ProcessDragDeleteRecord(record);
    EXPECT_EQ(record.optionsListBefore->size(), 6);
}

/**
 * @tc.name: ProcessStringUndo
 * @tc.desc: Test ProcessStringUndo.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStringUndoTestNg, ProcessStringUndo, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto& undoRecords = richEditorPattern->undoManager_->undoRecords_;

    // apply insert value record
    richEditorPattern->SetCaretPosition(0);
    richEditorPattern->InsertValue(INIT_VALUE_1);
    EXPECT_EQ(richEditorPattern->undoManager_->undoRecords_.size(), 1);
    auto undoRecord = undoRecords.back();
    EXPECT_EQ(undoRecord.rangeBefore.start, 0);
    EXPECT_EQ(undoRecord.rangeBefore.end, 0);
    EXPECT_EQ(undoRecord.rangeAfter.start, 0);
    EXPECT_EQ(undoRecord.rangeAfter.end, 6);
    richEditorPattern->undoManager_->ProcessStringUndo(undoRecord);
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 0);
    richEditorPattern->undoManager_->ProcessStringRedo(undoRecord);
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 6);

    // apply delete record
    richEditorPattern->SetCaretPosition(0);
    richEditorPattern->DeleteForward(1);
    EXPECT_EQ(richEditorPattern->undoManager_->undoRecords_.size(), 2);
    undoRecord = undoRecords.back();
    EXPECT_EQ(undoRecord.rangeBefore.start, 0);
    EXPECT_EQ(undoRecord.rangeBefore.end, 1);
    EXPECT_EQ(undoRecord.rangeAfter.start, 0);
    EXPECT_EQ(undoRecord.rangeAfter.end, 0);
    richEditorPattern->undoManager_->ProcessStringUndo(undoRecord);
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 6);
    richEditorPattern->undoManager_->ProcessStringRedo(undoRecord);
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 5);

    // apply drag record
    richEditorPattern->SetCaretPosition(0);
    richEditorPattern->InsertValueByPaste(INIT_VALUE_2);
    richEditorPattern->SetCaretPosition(8);
    richEditorPattern->dragRange_ = std::make_pair(0, 6);
    richEditorPattern->HandleOnDragDropTextOperation(INIT_VALUE_2, true, false);
    EXPECT_EQ(richEditorPattern->undoManager_->undoRecords_.size(), 5);
    undoRecord = undoRecords.back();
    EXPECT_TRUE(undoRecord.restoreBuilderSpan);
    EXPECT_EQ(undoRecord.rangeBefore.start, 0);
    EXPECT_EQ(undoRecord.rangeBefore.end, 6);
    EXPECT_EQ(undoRecord.rangeAfter.start, 0);
    EXPECT_EQ(undoRecord.rangeAfter.end, 0);
    richEditorPattern->undoManager_->ProcessStringUndo(undoRecord);
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 17);
    richEditorPattern->undoManager_->ProcessStringRedo(undoRecord);
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 11);
}

/**
 * @tc.name: BeforeChangeByRecord
 * @tc.desc: Test BeforeChangeByRecord.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStringUndoTestNg, BeforeChangeByRecord, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto& undoRecords = richEditorPattern->undoManager_->undoRecords_;

    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto aboutToDeleteFunc = [](const RichEditorDeleteValue& deleteValue) {
        return (deleteValue.direction_ == RichEditorDeleteDirection::BACKWARD) ? false : true;
    };
    auto changeReason = TextChangeReason::UNKNOWN;
    auto onWillChange = [&changeReason](const RichEditorChangeValue& changeValue) {
        changeReason = changeValue.changeReason_;
        return changeReason == TextChangeReason::REDO ? false : true;
    };
    richEditorPattern->SetCaretPosition(0);
    richEditorPattern->InsertValue(INIT_VALUE_1);
    EXPECT_EQ(richEditorPattern->undoManager_->undoRecords_.size(), 1);
    auto undoRecord = undoRecords.back();
    EXPECT_TRUE(richEditorPattern->undoManager_->BeforeChangeByRecord(undoRecord, true));
    EXPECT_EQ(changeReason, TextChangeReason::UNKNOWN);

    eventHub->SetAboutToDelete(std::move(aboutToDeleteFunc));
    eventHub->SetOnWillChange(onWillChange);
    richEditorPattern->SetCaretPosition(0);
    richEditorPattern->DeleteForward(1);
    EXPECT_EQ(richEditorPattern->undoManager_->undoRecords_.size(), 2);
    undoRecord = undoRecords.back();
    EXPECT_TRUE(richEditorPattern->undoManager_->BeforeChangeByRecord(undoRecord, true));
    EXPECT_EQ(changeReason, TextChangeReason::UNDO);

    richEditorPattern->SetCaretPosition(0);
    richEditorPattern->DeleteForward(1);
    EXPECT_EQ(richEditorPattern->undoManager_->undoRecords_.size(), 3);
    undoRecord = undoRecords.back();
    EXPECT_FALSE(richEditorPattern->undoManager_->BeforeChangeByRecord(undoRecord, false));
    EXPECT_EQ(changeReason, TextChangeReason::REDO);

    richEditorPattern->SetCaretPosition(0);
    richEditorPattern->InsertValue(INIT_VALUE_1);
    EXPECT_EQ(richEditorPattern->undoManager_->undoRecords_.size(), 4);
    undoRecord = undoRecords.back();
    EXPECT_FALSE(richEditorPattern->undoManager_->BeforeChangeByRecord(undoRecord, true));
}
}