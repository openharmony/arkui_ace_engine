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
namespace {
    const std::string INIT_TEST_CONTENT = "RichEditor回调测试";
    const std::string INSERT_TEST_CONTENT = "你好";
}

class RichEditorStringUndoTestNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    void InitContent();
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

void RichEditorStringUndoTestNg::InitContent()
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto focusHub = richEditorPattern->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->RequestFocusImmediately();
    richEditorPattern->SetCaretPosition(0);
    richEditorPattern->InsertValue(INIT_TEST_CONTENT);
}

/**
 * @tc.name: GetStringFromOptionsList
 * @tc.desc: Test GetStringFromOptionsList.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStringUndoTestNg, GetStringFromOptionsList, TestSize.Level0)
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
HWTEST_F(RichEditorStringUndoTestNg, ProcessDragDeleteRecord, TestSize.Level0)
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
HWTEST_F(RichEditorStringUndoTestNg, ProcessStringUndo, TestSize.Level0)
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
HWTEST_F(RichEditorStringUndoTestNg, BeforeChangeByRecord, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto& undoRecords = richEditorPattern->undoManager_->undoRecords_;

    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
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
}

/**
 * @tc.name: UndoRedoCallBackTest001
 * @tc.desc: Test undo insert value.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStringUndoTestNg, UndoRedoCallBackTest001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    InitContent();
    richEditorPattern->SetCaretPosition(14);
    richEditorPattern->InsertValue(INSERT_TEST_CONTENT);
    richEditorPattern->SetCaretPosition(16);
    richEditorPattern->StartTwinkling();
    int32_t step = 0;
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto onWillChange = [&step](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(step, 0);
        EXPECT_EQ(changeValue.GetRangeBefore().start, 14);
        EXPECT_EQ(changeValue.GetRangeBefore().end, 16);
        step++;
        return true;
    };
    eventHub->SetOnWillChange(std::move(onWillChange));
    auto onAboutToDelete = [&step](const RichEditorDeleteValue& deleteValue) {
        EXPECT_EQ(step, 1);
        EXPECT_EQ(deleteValue.GetOffset(), 14);
        EXPECT_EQ(deleteValue.GetRichEditorDeleteDirection(), RichEditorDeleteDirection::BACKWARD);
        EXPECT_EQ(deleteValue.GetLength(), 2);
        step++;
        return true;
    };
    eventHub->SetAboutToDelete(std::move(onAboutToDelete));
    auto onSelectionChange = [&step](const BaseEventInfo* info) {
        EXPECT_EQ(step, 2);
        const auto* selectionRange = TypeInfoHelper::DynamicCast<SelectionRangeInfo>(info);
        ASSERT_NE(selectionRange, nullptr);
        EXPECT_EQ(selectionRange->start_, 14);
        EXPECT_EQ(selectionRange->end_, 14);
        step++;
    };
    eventHub->SetOnSelectionChange(std::move(onSelectionChange));
    auto onDidChange = [&step](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(step, 3);
        EXPECT_EQ(changeValue.GetRangeBefore().start, 14);
        EXPECT_EQ(changeValue.GetRangeBefore().end, 16);
        EXPECT_EQ(changeValue.GetRangeAfter().start, 14);
        EXPECT_EQ(changeValue.GetRangeAfter().end, 14);
    };
    eventHub->SetOnDidChange(std::move(onDidChange));
    richEditorPattern->HandleOnUndoAction();
}

/**
 * @tc.name: UndoRedoCallBackTest002
 * @tc.desc: Test redo insert value.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStringUndoTestNg, UndoRedoCallBackTest002, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    InitContent();
    richEditorPattern->SetCaretPosition(14);
    richEditorPattern->InsertValue(INSERT_TEST_CONTENT);
    richEditorPattern->HandleOnUndoAction();
    richEditorPattern->SetCaretPosition(14);
    richEditorPattern->StartTwinkling();
    int32_t step = 0;
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto onWillChange = [&step](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(step, 0);
        EXPECT_EQ(changeValue.GetRangeBefore().start, 14);
        EXPECT_EQ(changeValue.GetRangeBefore().end, 14);
        step++;
        return true;
    };
    eventHub->SetOnWillChange(std::move(onWillChange));
    auto onSelectionChange = [&step](const BaseEventInfo* info) {
        EXPECT_EQ(step, 1);
        const auto* selectionRange = TypeInfoHelper::DynamicCast<SelectionRangeInfo>(info);
        ASSERT_NE(selectionRange, nullptr);
        EXPECT_EQ(selectionRange->start_, 16);
        EXPECT_EQ(selectionRange->end_, 16);
        step++;
    };
    eventHub->SetOnSelectionChange(std::move(onSelectionChange));
    auto onIMEInputComplete = [&step](const RichEditorAbstractSpanResult& info) {
        EXPECT_EQ(step, 2);
        EXPECT_EQ(info.OffsetInSpan(), 14);
        EXPECT_EQ(info.GetEraseLength(), 2);
        step++;
    };
    eventHub->SetOnIMEInputComplete(std::move(onIMEInputComplete));
    auto onDidChange = [&step](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(step, 3);
        EXPECT_EQ(changeValue.GetRangeBefore().start, 14);
        EXPECT_EQ(changeValue.GetRangeBefore().end, 14);
        EXPECT_EQ(changeValue.GetRangeAfter().start, 14);
        EXPECT_EQ(changeValue.GetRangeAfter().end, 16);
    };
    eventHub->SetOnDidChange(std::move(onDidChange));
    richEditorPattern->HandleOnRedoAction();
}

/**
 * @tc.name: UndoRedoCallBackTest003
 * @tc.desc: Test undo insert with selection.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStringUndoTestNg, UndoRedoCallBackTest003, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    InitContent();
    richEditorPattern->textSelector_.Update(10, 12);
    richEditorPattern->InsertValue(INSERT_TEST_CONTENT);
    richEditorPattern->SetCaretPosition(12);
    richEditorPattern->StartTwinkling();
    int32_t step = 0;
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto onWillChange = [&step](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(step, 0);
        EXPECT_EQ(changeValue.GetRangeBefore().start, 10);
        EXPECT_EQ(changeValue.GetRangeBefore().end, 12);
        step++;
        return true;
    };
    eventHub->SetOnWillChange(std::move(onWillChange));
    auto onAboutToDelete = [&step](const RichEditorDeleteValue& deleteValue) {
        EXPECT_EQ(step, 1);
        EXPECT_EQ(deleteValue.GetOffset(), 10);
        EXPECT_EQ(deleteValue.GetRichEditorDeleteDirection(), RichEditorDeleteDirection::BACKWARD);
        EXPECT_EQ(deleteValue.GetLength(), 2);
        step++;
        return true;
    };
    eventHub->SetAboutToDelete(std::move(onAboutToDelete));
    int32_t onSelectionNum = 0;
    auto onSelectionChange = [&step, &onSelectionNum](const BaseEventInfo* info) {
        const auto* selectionRange = TypeInfoHelper::DynamicCast<SelectionRangeInfo>(info);
        ASSERT_NE(selectionRange, nullptr);
        if (onSelectionNum == 0) {
            EXPECT_EQ(step, 2);
            EXPECT_EQ(selectionRange->start_, 10);
            EXPECT_EQ(selectionRange->end_, 10);
        } else {
            EXPECT_EQ(step, 3);
            EXPECT_EQ(selectionRange->start_, 12);
            EXPECT_EQ(selectionRange->end_, 12);
        }
        onSelectionNum++;
        step++;
    };
    eventHub->SetOnSelectionChange(std::move(onSelectionChange));
    richEditorPattern->HandleOnUndoAction();
    EXPECT_EQ(onSelectionNum, 2);
}

/**
 * @tc.name: UndoRedoCallBackTest004
 * @tc.desc: Test undo insert with selection.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStringUndoTestNg, UndoRedoCallBackTest004, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    InitContent();
    richEditorPattern->textSelector_.Update(10, 12);
    richEditorPattern->InsertValue(INSERT_TEST_CONTENT);
    richEditorPattern->SetCaretPosition(12);
    richEditorPattern->StartTwinkling();
    int32_t step = 0;
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto onWillChange = [&step](const RichEditorChangeValue& changeValue) {
        step++;
        return true;
    };
    eventHub->SetOnWillChange(std::move(onWillChange));
    auto onAboutToDelete = [&step](const RichEditorDeleteValue& deleteValue) {
        step++;
        return true;
    };
    eventHub->SetAboutToDelete(std::move(onAboutToDelete));
    auto onSelectionChange = [&step](const BaseEventInfo* info) { step++; };
    eventHub->SetOnSelectionChange(std::move(onSelectionChange));
    auto onIMEInputComplete = [&step](const RichEditorAbstractSpanResult& info) {
        EXPECT_EQ(step, 4);
        EXPECT_EQ(info.OffsetInSpan(), 10);
        EXPECT_EQ(info.GetEraseLength(), 2);
        step++;
    };
    eventHub->SetOnIMEInputComplete(std::move(onIMEInputComplete));
    auto onDidChange = [&step](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(step, 5);
        EXPECT_EQ(changeValue.GetRangeBefore().start, 10);
        EXPECT_EQ(changeValue.GetRangeBefore().end, 12);
        EXPECT_EQ(changeValue.GetRangeAfter().start, 10);
        EXPECT_EQ(changeValue.GetRangeAfter().end, 12);
    };
    eventHub->SetOnDidChange(std::move(onDidChange));
    richEditorPattern->HandleOnUndoAction();
}

/**
 * @tc.name: UndoRedoCallBackTest005
 * @tc.desc: Test redo insert with selection.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStringUndoTestNg, UndoRedoCallBackTest005, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    InitContent();
    richEditorPattern->textSelector_.Update(10, 12);
    richEditorPattern->InsertValue(INSERT_TEST_CONTENT);
    richEditorPattern->HandleOnUndoAction();
    richEditorPattern->SetCaretPosition(12);
    richEditorPattern->StartTwinkling();
    int32_t step = 0;
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto onWillChange = [&step](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(step, 0);
        EXPECT_EQ(changeValue.GetRangeBefore().start, 10);
        EXPECT_EQ(changeValue.GetRangeBefore().end, 12);
        step++;
        return true;
    };
    eventHub->SetOnWillChange(std::move(onWillChange));
    int32_t onSelectionNum = 0;
    auto onSelectionChange = [&step, &onSelectionNum](const BaseEventInfo* info) {
        const auto* selectionRange = TypeInfoHelper::DynamicCast<SelectionRangeInfo>(info);
        ASSERT_NE(selectionRange, nullptr);
        if (onSelectionNum == 0) {
            EXPECT_EQ(step, 1);
            EXPECT_EQ(selectionRange->start_, 10);
            EXPECT_EQ(selectionRange->end_, 10);
        } else {
            EXPECT_EQ(step, 3);
            EXPECT_EQ(selectionRange->start_, 12);
            EXPECT_EQ(selectionRange->end_, 12);
        }
        onSelectionNum++;
        step++;
    };
    eventHub->SetOnSelectionChange(std::move(onSelectionChange));
    auto onAboutToDelete = [&step](const RichEditorDeleteValue& deleteValue) {
        EXPECT_EQ(step, 2);
        EXPECT_EQ(deleteValue.GetOffset(), 10);
        EXPECT_EQ(deleteValue.GetRichEditorDeleteDirection(), RichEditorDeleteDirection::FORWARD);
        EXPECT_EQ(deleteValue.GetLength(), 2);
        step++;
        return true;
    };
    eventHub->SetAboutToDelete(std::move(onAboutToDelete));
    richEditorPattern->HandleOnRedoAction();
    EXPECT_EQ(onSelectionNum, 2);
}

/**
 * @tc.name: UndoRedoCallBackTest006
 * @tc.desc: Test redo insert with selection.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStringUndoTestNg, UndoRedoCallBackTest006, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    InitContent();
    richEditorPattern->textSelector_.Update(10, 12);
    richEditorPattern->InsertValue(INSERT_TEST_CONTENT);
    richEditorPattern->HandleOnUndoAction();
    richEditorPattern->SetCaretPosition(12);
    richEditorPattern->StartTwinkling();
    int32_t step = 0;
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto onWillChange = [&step](const RichEditorChangeValue& changeValue) {
        step++;
        return true;
    };
    eventHub->SetOnWillChange(std::move(onWillChange));
    auto onSelectionChange = [&step](const BaseEventInfo* info) {
        step++;
    };
    eventHub->SetOnSelectionChange(std::move(onSelectionChange));
    auto onAboutToDelete = [&step](const RichEditorDeleteValue& deleteValue) {
        step++;
        return true;
    };
    eventHub->SetAboutToDelete(std::move(onAboutToDelete));
    auto onIMEInputComplete = [&step](const RichEditorAbstractSpanResult& info) {
        EXPECT_EQ(step, 4);
        EXPECT_EQ(info.OffsetInSpan(), 10);
        EXPECT_EQ(info.GetEraseLength(), 2);
        step++;
    };
    eventHub->SetOnIMEInputComplete(std::move(onIMEInputComplete));
    auto onDidChange = [&step](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(step, 5);
        EXPECT_EQ(changeValue.GetRangeBefore().start, 10);
        EXPECT_EQ(changeValue.GetRangeBefore().end, 12);
        EXPECT_EQ(changeValue.GetRangeAfter().start, 10);
        EXPECT_EQ(changeValue.GetRangeAfter().end, 12);
    };
    eventHub->SetOnDidChange(std::move(onDidChange));
    richEditorPattern->HandleOnRedoAction();
}

/**
 * @tc.name: UndoRedoCallBackTest007
 * @tc.desc: Test undo delete backward.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStringUndoTestNg, UndoRedoCallBackTest007, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    InitContent();
    richEditorPattern->SetCaretPosition(12);
    richEditorPattern->DeleteBackward(1);
    richEditorPattern->SetCaretPosition(11);
    richEditorPattern->StartTwinkling();
    int32_t step = 0;
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto onWillChange = [&step](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(step, 0);
        EXPECT_EQ(changeValue.GetRangeBefore().start, 11);
        EXPECT_EQ(changeValue.GetRangeBefore().end, 11);
        step++;
        return true;
    };
    eventHub->SetOnWillChange(std::move(onWillChange));
    auto onSelectionChange = [&step](const BaseEventInfo* info) {
        EXPECT_EQ(step, 1);
        const auto* selectionRange = TypeInfoHelper::DynamicCast<SelectionRangeInfo>(info);
        ASSERT_NE(selectionRange, nullptr);
        EXPECT_EQ(selectionRange->start_, 12);
        EXPECT_EQ(selectionRange->end_, 12);
        step++;
    };
    eventHub->SetOnSelectionChange(std::move(onSelectionChange));
    auto onIMEInputComplete = [&step](const RichEditorAbstractSpanResult& info) {
        EXPECT_EQ(step, 2);
        EXPECT_EQ(info.OffsetInSpan(), 11);
        EXPECT_EQ(info.GetEraseLength(), 1);
        step++;
    };
    eventHub->SetOnIMEInputComplete(std::move(onIMEInputComplete));
    auto onDidChange = [&step](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(step, 3);
        EXPECT_EQ(changeValue.GetRangeBefore().start, 11);
        EXPECT_EQ(changeValue.GetRangeBefore().end, 11);
        EXPECT_EQ(changeValue.GetRangeAfter().start, 11);
        EXPECT_EQ(changeValue.GetRangeAfter().end, 12);
    };
    eventHub->SetOnDidChange(std::move(onDidChange));
    richEditorPattern->HandleOnUndoAction();
}

/**
 * @tc.name: UndoRedoCallBackTest008
 * @tc.desc: Test redo delete backward.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStringUndoTestNg, UndoRedoCallBackTest008, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    InitContent();
    richEditorPattern->SetCaretPosition(12);
    richEditorPattern->DeleteBackward(1);
    richEditorPattern->HandleOnUndoAction();
    richEditorPattern->SetCaretPosition(12);
    richEditorPattern->StartTwinkling();
    int32_t step = 0;
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto onWillChange = [&step](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(step, 0);
        EXPECT_EQ(changeValue.GetRangeBefore().start, 11);
        EXPECT_EQ(changeValue.GetRangeBefore().end, 12);
        step++;
        return true;
    };
    eventHub->SetOnWillChange(std::move(onWillChange));
    auto onAboutToDelete = [&step](const RichEditorDeleteValue& deleteValue) {
        EXPECT_EQ(step, 1);
        EXPECT_EQ(deleteValue.GetOffset(), 11);
        EXPECT_EQ(deleteValue.GetRichEditorDeleteDirection(), RichEditorDeleteDirection::BACKWARD);
        EXPECT_EQ(deleteValue.GetLength(), 1);
        step++;
        return true;
    };
    eventHub->SetAboutToDelete(std::move(onAboutToDelete));
    auto onSelectionChange = [&step](const BaseEventInfo* info) {
        EXPECT_EQ(step, 2);
        const auto* selectionRange = TypeInfoHelper::DynamicCast<SelectionRangeInfo>(info);
        ASSERT_NE(selectionRange, nullptr);
        EXPECT_EQ(selectionRange->start_, 11);
        EXPECT_EQ(selectionRange->end_, 11);
        step++;
    };
    eventHub->SetOnSelectionChange(std::move(onSelectionChange));
    auto onDidChange = [&step](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(step, 3);
        EXPECT_EQ(changeValue.GetRangeBefore().start, 11);
        EXPECT_EQ(changeValue.GetRangeBefore().end, 12);
        EXPECT_EQ(changeValue.GetRangeAfter().start, 11);
        EXPECT_EQ(changeValue.GetRangeAfter().end, 11);
    };
    eventHub->SetOnDidChange(std::move(onDidChange));
    richEditorPattern->HandleOnRedoAction();
}

/**
 * @tc.name: UndoRedoCallBackTest009
 * @tc.desc: Test undo delete backward word
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStringUndoTestNg, UndoRedoCallBackTest009, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    InitContent();
    richEditorPattern->SetCaretPosition(14);
    richEditorPattern->DeleteBackward(2);
    richEditorPattern->SetCaretPosition(12);
    richEditorPattern->StartTwinkling();
    int32_t step = 0;
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto onWillChange = [&step](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(step, 0);
        EXPECT_EQ(changeValue.GetRangeBefore().start, 12);
        EXPECT_EQ(changeValue.GetRangeBefore().end, 12);
        step++;
        return true;
    };
    eventHub->SetOnWillChange(std::move(onWillChange));
    auto onSelectionChange = [&step](const BaseEventInfo* info) {
        EXPECT_EQ(step, 1);
        const auto* selectionRange = TypeInfoHelper::DynamicCast<SelectionRangeInfo>(info);
        ASSERT_NE(selectionRange, nullptr);
        EXPECT_EQ(selectionRange->start_, 14);
        EXPECT_EQ(selectionRange->end_, 14);
        step++;
    };
    eventHub->SetOnSelectionChange(std::move(onSelectionChange));
    auto onIMEInputComplete = [&step](const RichEditorAbstractSpanResult& info) {
        EXPECT_EQ(step, 2);
        EXPECT_EQ(info.OffsetInSpan(), 12);
        EXPECT_EQ(info.GetEraseLength(), 2);
        step++;
    };
    eventHub->SetOnIMEInputComplete(std::move(onIMEInputComplete));
    auto onDidChange = [&step](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(step, 3);
        EXPECT_EQ(changeValue.GetRangeBefore().start, 12);
        EXPECT_EQ(changeValue.GetRangeBefore().end, 12);
        EXPECT_EQ(changeValue.GetRangeAfter().start, 12);
        EXPECT_EQ(changeValue.GetRangeAfter().end, 14);
    };
    eventHub->SetOnDidChange(std::move(onDidChange));
    richEditorPattern->HandleOnUndoAction();
}

/**
 * @tc.name: UndoRedoCallBackTest010
 * @tc.desc: Test redo delete backward word
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStringUndoTestNg, UndoRedoCallBackTest010, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    InitContent();
    richEditorPattern->SetCaretPosition(14);
    richEditorPattern->DeleteBackward(2);
    richEditorPattern->HandleOnUndoAction();
    richEditorPattern->SetCaretPosition(14);
    richEditorPattern->StartTwinkling();
    int32_t step = 0;
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto onWillChange = [&step](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(step, 0);
        EXPECT_EQ(changeValue.GetRangeBefore().start, 12);
        EXPECT_EQ(changeValue.GetRangeBefore().end, 14);
        step++;
        return true;
    };
    eventHub->SetOnWillChange(std::move(onWillChange));
    auto onAboutToDelete = [&step](const RichEditorDeleteValue& deleteValue) {
        EXPECT_EQ(step, 1);
        EXPECT_EQ(deleteValue.GetOffset(), 12);
        EXPECT_EQ(deleteValue.GetRichEditorDeleteDirection(), RichEditorDeleteDirection::BACKWARD);
        EXPECT_EQ(deleteValue.GetLength(), 2);
        step++;
        return true;
    };
    eventHub->SetAboutToDelete(std::move(onAboutToDelete));
    auto onSelectionChange = [&step](const BaseEventInfo* info) {
        EXPECT_EQ(step, 2);
        const auto* selectionRange = TypeInfoHelper::DynamicCast<SelectionRangeInfo>(info);
        ASSERT_NE(selectionRange, nullptr);
        EXPECT_EQ(selectionRange->start_, 12);
        EXPECT_EQ(selectionRange->end_, 12);
        step++;
    };
    eventHub->SetOnSelectionChange(std::move(onSelectionChange));
    auto onDidChange = [&step](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(step, 3);
        EXPECT_EQ(changeValue.GetRangeBefore().start, 12);
        EXPECT_EQ(changeValue.GetRangeBefore().end, 14);
        EXPECT_EQ(changeValue.GetRangeAfter().start, 12);
        EXPECT_EQ(changeValue.GetRangeAfter().end, 12);
    };
    eventHub->SetOnDidChange(std::move(onDidChange));
    richEditorPattern->HandleOnRedoAction();
}

/**
 * @tc.name: UndoRedoCallBackTest011
 * @tc.desc: Test undo delete forward.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStringUndoTestNg, UndoRedoCallBackTest011, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    InitContent();
    richEditorPattern->SetCaretPosition(12);
    richEditorPattern->DeleteForward(1);
    richEditorPattern->SetCaretPosition(12);
    richEditorPattern->StartTwinkling();
    int32_t step = 0;
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto onWillChange = [&step](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(step, 0);
        EXPECT_EQ(changeValue.GetRangeBefore().start, 12);
        EXPECT_EQ(changeValue.GetRangeBefore().end, 12);
        step++;
        return true;
    };
    eventHub->SetOnWillChange(std::move(onWillChange));
    auto onSelectionChange = [&step](const BaseEventInfo* info) {
        EXPECT_EQ(step, 1);
        const auto* selectionRange = TypeInfoHelper::DynamicCast<SelectionRangeInfo>(info);
        ASSERT_NE(selectionRange, nullptr);
        EXPECT_EQ(selectionRange->start_, 13);
        EXPECT_EQ(selectionRange->end_, 13);
        step++;
    };
    eventHub->SetOnSelectionChange(std::move(onSelectionChange));
    auto onIMEInputComplete = [&step](const RichEditorAbstractSpanResult& info) {
        EXPECT_EQ(step, 2);
        EXPECT_EQ(info.OffsetInSpan(), 12);
        EXPECT_EQ(info.GetEraseLength(), 1);
        step++;
    };
    eventHub->SetOnIMEInputComplete(std::move(onIMEInputComplete));
    auto onDidChange = [&step](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(step, 3);
        EXPECT_EQ(changeValue.GetRangeBefore().start, 12);
        EXPECT_EQ(changeValue.GetRangeBefore().end, 12);
        EXPECT_EQ(changeValue.GetRangeAfter().start, 12);
        EXPECT_EQ(changeValue.GetRangeAfter().end, 13);
    };
    eventHub->SetOnDidChange(std::move(onDidChange));
    richEditorPattern->HandleOnUndoAction();
}

/**
 * @tc.name: UndoRedoCallBackTest012
 * @tc.desc: Test redo delete forward.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStringUndoTestNg, UndoRedoCallBackTest012, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    InitContent();
    richEditorPattern->SetCaretPosition(12);
    richEditorPattern->DeleteForward(1);
    richEditorPattern->HandleOnUndoAction();
    richEditorPattern->SetCaretPosition(13);
    richEditorPattern->StartTwinkling();
    int32_t step = 0;
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto onWillChange = [&step](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(step, 0);
        EXPECT_EQ(changeValue.GetRangeBefore().start, 12);
        EXPECT_EQ(changeValue.GetRangeBefore().end, 13);
        step++;
        return true;
    };
    eventHub->SetOnWillChange(std::move(onWillChange));
    auto onSelectionChange = [&step](const BaseEventInfo* info) {
        EXPECT_EQ(step, 1);
        const auto* selectionRange = TypeInfoHelper::DynamicCast<SelectionRangeInfo>(info);
        ASSERT_NE(selectionRange, nullptr);
        EXPECT_EQ(selectionRange->start_, 12);
        EXPECT_EQ(selectionRange->end_, 12);
        step++;
    };
    eventHub->SetOnSelectionChange(std::move(onSelectionChange));
    auto onAboutToDelete = [&step](const RichEditorDeleteValue& deleteValue) {
        EXPECT_EQ(step, 2);
        EXPECT_EQ(deleteValue.GetOffset(), 12);
        EXPECT_EQ(deleteValue.GetRichEditorDeleteDirection(), RichEditorDeleteDirection::FORWARD);
        EXPECT_EQ(deleteValue.GetLength(), 1);
        step++;
        return true;
    };
    eventHub->SetAboutToDelete(std::move(onAboutToDelete));
    auto onDidChange = [&step](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(step, 3);
        EXPECT_EQ(changeValue.GetRangeBefore().start, 12);
        EXPECT_EQ(changeValue.GetRangeBefore().end, 13);
        EXPECT_EQ(changeValue.GetRangeAfter().start, 12);
        EXPECT_EQ(changeValue.GetRangeAfter().end, 12);
    };
    eventHub->SetOnDidChange(std::move(onDidChange));
    richEditorPattern->HandleOnRedoAction();
}

/**
 * @tc.name: UndoRedoCallBackTest013
 * @tc.desc: Test undo delete forward word
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStringUndoTestNg, UndoRedoCallBackTest013, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    InitContent();
    richEditorPattern->SetCaretPosition(12);
    richEditorPattern->DeleteForward(2);
    richEditorPattern->SetCaretPosition(12);
    richEditorPattern->StartTwinkling();
    int32_t step = 0;
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto onWillChange = [&step](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(step, 0);
        EXPECT_EQ(changeValue.GetRangeBefore().start, 12);
        EXPECT_EQ(changeValue.GetRangeBefore().end, 12);
        step++;
        return true;
    };
    eventHub->SetOnWillChange(std::move(onWillChange));
    auto onSelectionChange = [&step](const BaseEventInfo* info) {
        EXPECT_EQ(step, 1);
        const auto* selectionRange = TypeInfoHelper::DynamicCast<SelectionRangeInfo>(info);
        ASSERT_NE(selectionRange, nullptr);
        EXPECT_EQ(selectionRange->start_, 14);
        EXPECT_EQ(selectionRange->end_, 14);
        step++;
    };
    eventHub->SetOnSelectionChange(std::move(onSelectionChange));
    auto onIMEInputComplete = [&step](const RichEditorAbstractSpanResult& info) {
        EXPECT_EQ(step, 2);
        EXPECT_EQ(info.OffsetInSpan(), 12);
        EXPECT_EQ(info.GetEraseLength(), 2);
        step++;
    };
    eventHub->SetOnIMEInputComplete(std::move(onIMEInputComplete));
    auto onDidChange = [&step](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(step, 3);
        EXPECT_EQ(changeValue.GetRangeBefore().start, 12);
        EXPECT_EQ(changeValue.GetRangeBefore().end, 12);
        EXPECT_EQ(changeValue.GetRangeAfter().start, 12);
        EXPECT_EQ(changeValue.GetRangeAfter().end, 14);
    };
    eventHub->SetOnDidChange(std::move(onDidChange));
    richEditorPattern->HandleOnUndoAction();
}

/**
 * @tc.name: UndoRedoCallBackTest014
 * @tc.desc: Test redo delete forward word
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStringUndoTestNg, UndoRedoCallBackTest014, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    InitContent();
    richEditorPattern->SetCaretPosition(12);
    richEditorPattern->DeleteForward(2);
    richEditorPattern->HandleOnUndoAction();
    richEditorPattern->SetCaretPosition(14);
    richEditorPattern->StartTwinkling();
    int32_t step = 0;
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto onWillChange = [&step](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(step, 0);
        EXPECT_EQ(changeValue.GetRangeBefore().start, 12);
        EXPECT_EQ(changeValue.GetRangeBefore().end, 14);
        step++;
        return true;
    };
    eventHub->SetOnWillChange(std::move(onWillChange));
    auto onSelectionChange = [&step](const BaseEventInfo* info) {
        EXPECT_EQ(step, 1);
        const auto* selectionRange = TypeInfoHelper::DynamicCast<SelectionRangeInfo>(info);
        ASSERT_NE(selectionRange, nullptr);
        EXPECT_EQ(selectionRange->start_, 12);
        EXPECT_EQ(selectionRange->end_, 12);
        step++;
    };
    eventHub->SetOnSelectionChange(std::move(onSelectionChange));
    auto onAboutToDelete = [&step](const RichEditorDeleteValue& deleteValue) {
        EXPECT_EQ(step, 2);
        EXPECT_EQ(deleteValue.GetOffset(), 12);
        EXPECT_EQ(deleteValue.GetRichEditorDeleteDirection(), RichEditorDeleteDirection::FORWARD);
        EXPECT_EQ(deleteValue.GetLength(), 2);
        step++;
        return true;
    };
    eventHub->SetAboutToDelete(std::move(onAboutToDelete));
    auto onDidChange = [&step](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(step, 3);
        EXPECT_EQ(changeValue.GetRangeBefore().start, 12);
        EXPECT_EQ(changeValue.GetRangeBefore().end, 14);
        EXPECT_EQ(changeValue.GetRangeAfter().start, 12);
        EXPECT_EQ(changeValue.GetRangeAfter().end, 12);
    };
    eventHub->SetOnDidChange(std::move(onDidChange));
    richEditorPattern->HandleOnRedoAction();
}

/**
 * @tc.name: UndoRedoCallBackTest0015
 * @tc.desc: Test undo delete backward with selection.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStringUndoTestNg, UndoRedoCallBackTest015, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    InitContent();
    richEditorPattern->textSelector_.Update(10, 12);
    richEditorPattern->DeleteBackward(1);
    richEditorPattern->SetCaretPosition(10);
    richEditorPattern->StartTwinkling();
    int32_t step = 0;
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto onWillChange = [&step](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(step, 0);
        EXPECT_EQ(changeValue.GetRangeBefore().start, 10);
        EXPECT_EQ(changeValue.GetRangeBefore().end, 10);
        step++;
        return true;
    };
    eventHub->SetOnWillChange(std::move(onWillChange));
    auto onSelectionChange = [&step](const BaseEventInfo* info) {
        EXPECT_EQ(step, 1);
        const auto* selectionRange = TypeInfoHelper::DynamicCast<SelectionRangeInfo>(info);
        ASSERT_NE(selectionRange, nullptr);
        EXPECT_EQ(selectionRange->start_, 12);
        EXPECT_EQ(selectionRange->end_, 12);
        step++;
    };
    eventHub->SetOnSelectionChange(std::move(onSelectionChange));
    auto onIMEInputComplete = [&step](const RichEditorAbstractSpanResult& info) {
        EXPECT_EQ(step, 2);
        EXPECT_EQ(info.OffsetInSpan(), 10);
        EXPECT_EQ(info.GetEraseLength(), 2);
        step++;
    };
    eventHub->SetOnIMEInputComplete(std::move(onIMEInputComplete));
    auto onDidChange = [&step](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(step, 3);
        EXPECT_EQ(changeValue.GetRangeBefore().start, 10);
        EXPECT_EQ(changeValue.GetRangeBefore().end, 10);
        EXPECT_EQ(changeValue.GetRangeAfter().start, 10);
        EXPECT_EQ(changeValue.GetRangeAfter().end, 12);
    };
    eventHub->SetOnDidChange(std::move(onDidChange));
    richEditorPattern->HandleOnUndoAction();
}

/**
 * @tc.name: UndoRedoCallBackTest016
 * @tc.desc: Test redo delete backward with selection.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStringUndoTestNg, UndoRedoCallBackTest016, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    InitContent();
    richEditorPattern->textSelector_.Update(10, 12);
    richEditorPattern->DeleteBackward(1);
    richEditorPattern->HandleOnUndoAction();
    richEditorPattern->SetCaretPosition(12);
    richEditorPattern->StartTwinkling();
    int32_t step = 0;
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto onWillChange = [&step](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(step, 0);
        EXPECT_EQ(changeValue.GetRangeBefore().start, 10);
        EXPECT_EQ(changeValue.GetRangeBefore().end, 12);
        step++;
        return true;
    };
    eventHub->SetOnWillChange(std::move(onWillChange));
    auto onAboutToDelete = [&step](const RichEditorDeleteValue& deleteValue) {
        EXPECT_EQ(step, 1);
        EXPECT_EQ(deleteValue.GetOffset(), 10);
        EXPECT_EQ(deleteValue.GetRichEditorDeleteDirection(), RichEditorDeleteDirection::BACKWARD);
        EXPECT_EQ(deleteValue.GetLength(), 2);
        step++;
        return true;
    };
    eventHub->SetAboutToDelete(std::move(onAboutToDelete));
    auto onSelectionChange = [&step](const BaseEventInfo* info) {
        EXPECT_EQ(step, 2);
        const auto* selectionRange = TypeInfoHelper::DynamicCast<SelectionRangeInfo>(info);
        ASSERT_NE(selectionRange, nullptr);
        EXPECT_EQ(selectionRange->start_, 10);
        EXPECT_EQ(selectionRange->end_, 10);
        step++;
    };
    eventHub->SetOnSelectionChange(std::move(onSelectionChange));
    auto onDidChange = [&step](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(step, 3);
        EXPECT_EQ(changeValue.GetRangeBefore().start, 10);
        EXPECT_EQ(changeValue.GetRangeBefore().end, 12);
        EXPECT_EQ(changeValue.GetRangeAfter().start, 10);
        EXPECT_EQ(changeValue.GetRangeAfter().end, 10);
    };
    eventHub->SetOnDidChange(std::move(onDidChange));
    richEditorPattern->HandleOnRedoAction();
}

/**
 * @tc.name: UndoRedoCallBackTest017
 * @tc.desc: Test undo delete forward with selection.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStringUndoTestNg, UndoRedoCallBackTest017, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    InitContent();
    richEditorPattern->textSelector_.Update(10, 12);
    richEditorPattern->DeleteForward(1);
    richEditorPattern->SetCaretPosition(10);
    richEditorPattern->StartTwinkling();
    int32_t step = 0;
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto onWillChange = [&step](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(step, 0);
        EXPECT_EQ(changeValue.GetRangeBefore().start, 10);
        EXPECT_EQ(changeValue.GetRangeBefore().end, 10);
        step++;
        return true;
    };
    eventHub->SetOnWillChange(std::move(onWillChange));
    auto onSelectionChange = [&step](const BaseEventInfo* info) {
        EXPECT_EQ(step, 1);
        const auto* selectionRange = TypeInfoHelper::DynamicCast<SelectionRangeInfo>(info);
        ASSERT_NE(selectionRange, nullptr);
        EXPECT_EQ(selectionRange->start_, 12);
        EXPECT_EQ(selectionRange->end_, 12);
        step++;
    };
    eventHub->SetOnSelectionChange(std::move(onSelectionChange));
    auto onIMEInputComplete = [&step](const RichEditorAbstractSpanResult& info) {
        EXPECT_EQ(step, 2);
        EXPECT_EQ(info.OffsetInSpan(), 10);
        EXPECT_EQ(info.GetEraseLength(), 2);
        step++;
    };
    eventHub->SetOnIMEInputComplete(std::move(onIMEInputComplete));
    auto onDidChange = [&step](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(step, 3);
        EXPECT_EQ(changeValue.GetRangeBefore().start, 10);
        EXPECT_EQ(changeValue.GetRangeBefore().end, 10);
        EXPECT_EQ(changeValue.GetRangeAfter().start, 10);
        EXPECT_EQ(changeValue.GetRangeAfter().end, 12);
    };
    eventHub->SetOnDidChange(std::move(onDidChange));
    richEditorPattern->HandleOnUndoAction();
}

/**
 * @tc.name: UndoRedoCallBackTest018
 * @tc.desc: Test redo delete forward with selection.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStringUndoTestNg, UndoRedoCallBackTest018, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    InitContent();
    richEditorPattern->textSelector_.Update(10, 12);
    richEditorPattern->DeleteForward(1);
    richEditorPattern->HandleOnUndoAction();
    richEditorPattern->SetCaretPosition(12);
    richEditorPattern->StartTwinkling();
    int32_t step = 0;
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto onWillChange = [&step](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(step, 0);
        EXPECT_EQ(changeValue.GetRangeBefore().start, 10);
        EXPECT_EQ(changeValue.GetRangeBefore().end, 12);
        step++;
        return true;
    };
    eventHub->SetOnWillChange(std::move(onWillChange));
    auto onAboutToDelete = [&step](const RichEditorDeleteValue& deleteValue) {
        EXPECT_EQ(step, 1);
        EXPECT_EQ(deleteValue.GetOffset(), 10);
        EXPECT_EQ(deleteValue.GetRichEditorDeleteDirection(), RichEditorDeleteDirection::BACKWARD);
        EXPECT_EQ(deleteValue.GetLength(), 2);
        step++;
        return true;
    };
    eventHub->SetAboutToDelete(std::move(onAboutToDelete));
    auto onSelectionChange = [&step](const BaseEventInfo* info) {
        EXPECT_EQ(step, 2);
        const auto* selectionRange = TypeInfoHelper::DynamicCast<SelectionRangeInfo>(info);
        ASSERT_NE(selectionRange, nullptr);
        EXPECT_EQ(selectionRange->start_, 10);
        EXPECT_EQ(selectionRange->end_, 10);
        step++;
    };
    eventHub->SetOnSelectionChange(std::move(onSelectionChange));
    auto onDidChange = [&step](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(step, 3);
        EXPECT_EQ(changeValue.GetRangeBefore().start, 10);
        EXPECT_EQ(changeValue.GetRangeBefore().end, 12);
        EXPECT_EQ(changeValue.GetRangeAfter().start, 10);
        EXPECT_EQ(changeValue.GetRangeAfter().end, 10);
    };
    eventHub->SetOnDidChange(std::move(onDidChange));
    richEditorPattern->HandleOnRedoAction();
}
}