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
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/base/mock_task_executor.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model_ng.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_undo_manager.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class RichEditorUndoRedoTest : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
private:
    RefPtr<RichEditorPattern> GetRichEditorPattern();
};

void RichEditorUndoRedoTest::SetUp()
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

void RichEditorUndoRedoTest::TearDown()
{
    richEditorNode_ = nullptr;
    MockParagraph::TearDown();
}

void RichEditorUndoRedoTest::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

RefPtr<RichEditorPattern> RichEditorUndoRedoTest::GetRichEditorPattern()
{
    CHECK_NULL_RETURN(richEditorNode_, nullptr);
    return richEditorNode_->GetPattern<RichEditorPattern>();
}

/**
 * @tc.name: RedoDrag001
 * @tc.desc: test RedoDrag
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUndoRedoTest, RedoDrag001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. init and call function.
    */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    RichEditorPattern::OperationRecord record;
    record.beforeCaretPosition = 0;
    record.addText = u"test123";
    richEditorPattern->RedoDrag(record);
    EXPECT_EQ(richEditorPattern->caretPosition_, 0);
}

/**
 * @tc.name: UndoDrag001
 * @tc.desc: test UndoDrag
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUndoRedoTest, UndoDrag001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. init and call function.
    */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    RichEditorPattern::OperationRecord record;
    record.deleteCaretPosition = 0;
    record.addText = u"test123";
    richEditorPattern->UndoDrag(record);
    EXPECT_EQ(richEditorPattern->caretPosition_, 7);
}


/**
 * @tc.name: RedoDrag002
 * @tc.desc: test RedoDrag
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUndoRedoTest, RedoDrag002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. init and call function.
    */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto changeReason = TextChangeReason::UNKNOWN;
    auto onWillChange = [&changeReason](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(changeValue.changeReason_, TextChangeReason::REDO);
        changeReason = changeValue.changeReason_;
        return true;
    };
    eventHub->SetOnWillChange(onWillChange);

    RichEditorPattern::OperationRecord record;
    record.deleteCaretPosition = 0;
    record.addText = u"test123";
    richEditorPattern->RedoDrag(record);
    EXPECT_EQ(richEditorPattern->caretPosition_, 6);
    EXPECT_EQ(changeReason, TextChangeReason::REDO);
}


/**
 * @tc.name: UndoDrag003
 * @tc.desc: test UndoDrag
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUndoRedoTest, UndoDrag003, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    RichEditorPattern::OperationRecord record;
    record.addText = u"test123\n";
    record.deleteCaretPosition = 1;
    auto caretPosition = richEditorPattern->caretPosition_;
    richEditorPattern->UndoDrag(record);
    EXPECT_NE(richEditorPattern->caretPosition_, caretPosition);
}

/**
 * @tc.name: RedoDrag003
 * @tc.desc: test RedoDrag
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUndoRedoTest, RedoDrag003, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    RichEditorPattern::OperationRecord record;
    record.deleteCaretPosition = 1;
    richEditorPattern->RedoDrag(record);
    EXPECT_EQ(richEditorPattern->caretPosition_, 0);
}


/**
 * @tc.name: HandleOnRedoAction001
 * @tc.desc: test HandleOnRedoAction
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUndoRedoTest, HandleOnRedoAction001, TestSize.Level2)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto changeReason = TextChangeReason::UNKNOWN;
    auto onWillChange = [&changeReason](const RichEditorChangeValue& changeValue) {
        changeReason = changeValue.changeReason_;
        return true;
    };
    eventHub->SetOnWillChange(onWillChange);

    richEditorPattern->SetCaretPosition(0);
    richEditorPattern->InsertValue(INIT_VALUE_1);
    richEditorPattern->HandleOnUndoAction();
    richEditorPattern->HandleOnRedoAction();
    EXPECT_EQ(changeReason, TextChangeReason::REDO);

    richEditorPattern->textSelector_.Update(0, 2);
    richEditorPattern->InsertValue(INIT_VALUE_2);
    richEditorPattern->HandleOnUndoAction();
    richEditorPattern->HandleOnRedoAction();
    EXPECT_EQ(changeReason, TextChangeReason::REDO);

    richEditorPattern->SetCaretPosition(0);
    richEditorPattern->DeleteForward(1);
    richEditorPattern->HandleOnUndoAction();
    richEditorPattern->HandleOnRedoAction();
    EXPECT_EQ(changeReason, TextChangeReason::REDO);
}


/**
 * @tc.name: HandleOnRedoAction002
 * @tc.desc: test HandleOnRedoAction
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUndoRedoTest, HandleOnRedoAction002, TestSize.Level2)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->undoManager_ =
        std::make_unique<StyledStringUndoManager>(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
    ASSERT_NE(richEditorPattern->undoManager_, nullptr);
    
    richEditorPattern->SetCaretPosition(0);
    richEditorPattern->InsertValue(INIT_VALUE_1);
    richEditorPattern->HandleOnUndoAction();

    richEditorPattern->HandleOnRedoAction();
    EXPECT_TRUE(true);
}

/**
 * @tc.name: HandleOnRedoAction003
 * @tc.desc: test HandleOnRedoAction
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUndoRedoTest, HandleOnRedoAction003, TestSize.Level2)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    auto changeReason = TextChangeReason::UNKNOWN;
    richEditorPattern->undoManager_.reset();
    richEditorPattern->redoOperationRecords_.clear();

    richEditorPattern->HandleOnRedoAction();
    EXPECT_EQ(changeReason, TextChangeReason::UNKNOWN);
}

/**
 * @tc.name: HandleOnRedoAction004
 * @tc.desc: test HandleOnRedoAction
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUndoRedoTest, HandleOnRedoAction004, TestSize.Level2)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    
    richEditorPattern->undoManager_.reset();
    richEditorPattern->operationRecords_.clear();
    richEditorPattern->redoOperationRecords_.clear();

    RichEditorPattern::OperationRecord record;
    record.addText = INIT_VALUE_1;
    record.deleteText = std::nullopt;
    record.deleteCaretPosition = 5;
    record.beforeCaretPosition = 0;
    record.afterCaretPosition = 5;
    
    richEditorPattern->redoOperationRecords_.push_back(record);
    auto operationCountBefore = richEditorPattern->operationRecords_.size();
    richEditorPattern->HandleOnRedoAction();

    EXPECT_TRUE(richEditorPattern->redoOperationRecords_.empty());
    EXPECT_EQ(richEditorPattern->operationRecords_.size(), operationCountBefore);
}

/**
 * @tc.name: HandleOnRedoAction005
 * @tc.desc: test HandleOnRedoAction
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUndoRedoTest, HandleOnRedoAction005, TestSize.Level2)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    
    richEditorPattern->undoManager_.reset();
    richEditorPattern->operationRecords_.clear();
    richEditorPattern->redoOperationRecords_.clear();

    RichEditorPattern::OperationRecord record;
    record.addText = INIT_VALUE_2;
    record.deleteText = std::nullopt;
    record.deleteCaretPosition = -1;
    record.beforeCaretPosition = 0;
    record.afterCaretPosition = 0;
    
    richEditorPattern->redoOperationRecords_.push_back(record);
    auto contentLengthBefore = richEditorPattern->GetTextContentLength();
    auto operationCountBefore = richEditorPattern->operationRecords_.size();
    richEditorPattern->HandleOnRedoAction();

    EXPECT_TRUE(richEditorPattern->redoOperationRecords_.empty());
    EXPECT_EQ(richEditorPattern->operationRecords_.size(), operationCountBefore + 1);
    auto contentLengthAfter = richEditorPattern->GetTextContentLength();
    EXPECT_NE(contentLengthBefore, contentLengthAfter);
}

/**
 * @tc.name: HandleOnRedoAction006
 * @tc.desc: test HandleOnRedoAction
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUndoRedoTest, HandleOnRedoAction006, TestSize.Level2)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    
    richEditorPattern->undoManager_.reset();
    richEditorPattern->operationRecords_.clear();
    richEditorPattern->redoOperationRecords_.clear();

    RichEditorPattern::OperationRecord record;
    record.addText = std::nullopt;
    record.deleteText = std::nullopt;
    record.deleteCaretPosition = -1;
    record.beforeCaretPosition = 0;
    record.afterCaretPosition = 0;

    richEditorPattern->redoOperationRecords_.push_back(record);
    auto operationCountBefore = richEditorPattern->operationRecords_.size();
    richEditorPattern->HandleOnRedoAction();

    EXPECT_TRUE(richEditorPattern->redoOperationRecords_.empty());
    EXPECT_FALSE(richEditorPattern->operationRecords_.empty());
    EXPECT_EQ(richEditorPattern->operationRecords_.size(), operationCountBefore + 1);
}


/**
 * @tc.name: UndoDrag002
 * @tc.desc: test UndoDrag
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUndoRedoTest, UndoDrag002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. init and call function.
    */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);

    RichEditorPattern::OperationRecord record;
    record.deleteCaretPosition = -1;
    richEditorPattern->UndoDrag(record);
    EXPECT_FALSE(record.addText.has_value());
}


/**
 * @tc.name: HandleOnUndoAction001
 * @tc.desc: test HandleOnUndoAction
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUndoRedoTest, HandleOnUndoAction001, TestSize.Level2)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto changeReason = TextChangeReason::UNKNOWN;
    auto onWillChange = [&changeReason](const RichEditorChangeValue& changeValue) {
        changeReason = changeValue.changeReason_;
        return true;
    };
    eventHub->SetOnWillChange(onWillChange);

    richEditorPattern->SetCaretPosition(0);
    richEditorPattern->InsertValue(INIT_VALUE_1);
    richEditorPattern->HandleOnUndoAction();
    EXPECT_EQ(changeReason, TextChangeReason::UNDO);

    richEditorPattern->textSelector_.Update(0, 2);
    richEditorPattern->InsertValue(INIT_VALUE_2);
    richEditorPattern->HandleOnUndoAction();
    EXPECT_EQ(changeReason, TextChangeReason::UNDO);
}

/**
 * @tc.name: HandleOnUndoAction002
 * @tc.desc: test HandleOnUndoAction
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUndoRedoTest, HandleOnUndoAction002, TestSize.Level2)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto changeReason = TextChangeReason::UNKNOWN;

    auto onWillChange = [&changeReason](const RichEditorChangeValue& changeValue) {
        changeReason = changeValue.changeReason_;
        return true;
    };
    eventHub->SetOnWillChange(onWillChange);
    richEditorPattern->undoManager_.reset();
    richEditorPattern->operationRecords_.clear();
    richEditorPattern->HandleOnUndoAction();
    EXPECT_EQ(changeReason, TextChangeReason::UNKNOWN);
}

/**
 * @tc.name: HandleOnUndoAction003
 * @tc.desc: test HandleOnUndoAction
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUndoRedoTest, HandleOnUndoAction003, TestSize.Level2)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->undoManager_.reset();
    richEditorPattern->operationRecords_.clear();
    richEditorPattern->redoOperationRecords_.clear();

    richEditorPattern->SetCaretPosition(0);
    richEditorPattern->InsertValue(INIT_VALUE_1, true);

    const size_t RECORD_MAX_LENGTH = 20;
    for (size_t i = 0; i < RECORD_MAX_LENGTH + 1; ++i) {
        RichEditorPattern::OperationRecord record;
        record.addText = u"test";
        record.beforeCaretPosition = static_cast<int32_t>(i);
        record.afterCaretPosition = static_cast<int32_t>(i + 1);
        record.deleteCaretPosition = 5;
        richEditorPattern->redoOperationRecords_.push_back(record);
        richEditorPattern->operationRecords_.push_back(record);
    }
    richEditorPattern->HandleOnUndoAction();
    EXPECT_GT(richEditorPattern->redoOperationRecords_.size(), RECORD_MAX_LENGTH);
}

/**
 * @tc.name: HandleOnUndoAction004
 * @tc.desc: test HandleOnUndoAction
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUndoRedoTest, HandleOnUndoAction004, TestSize.Level2)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    
    richEditorPattern->undoManager_.reset();
    richEditorPattern->operationRecords_.clear();
    richEditorPattern->redoOperationRecords_.clear();

    RichEditorPattern::OperationRecord record;
    record.addText = INIT_VALUE_1;
    record.deleteCaretPosition = 5;
    record.beforeCaretPosition = 0;
    record.afterCaretPosition = 5;
    richEditorPattern->operationRecords_.push_back(record);

    richEditorPattern->HandleOnUndoAction();
    EXPECT_TRUE(richEditorPattern->operationRecords_.empty());
    EXPECT_FALSE(richEditorPattern->redoOperationRecords_.empty());
}

/**
 * @tc.name: HandleOnUndoAction005
 * @tc.desc: test HandleOnUndoAction
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUndoRedoTest, HandleOnUndoAction005, TestSize.Level2)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    
    richEditorPattern->undoManager_.reset();
    richEditorPattern->operationRecords_.clear();
    richEditorPattern->redoOperationRecords_.clear();

    RichEditorPattern::OperationRecord record;
    record.addText = std::nullopt;
    record.deleteText = std::nullopt;
    record.deleteCaretPosition = -1;
    record.beforeCaretPosition = 0;
    record.afterCaretPosition = 0;
    
    richEditorPattern->operationRecords_.push_back(record);
    richEditorPattern->HandleOnUndoAction();

    EXPECT_TRUE(richEditorPattern->operationRecords_.empty());
    EXPECT_FALSE(richEditorPattern->redoOperationRecords_.empty());
}

/**
 * @tc.name: InsertValueOperation
 * @tc.desc: test InsertValueOperation
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUndoRedoTest, InsertValueOperation, TestSize.Level2)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto changeReason = TextChangeReason::UNKNOWN;
    auto onWillChange = [&changeReason](const RichEditorChangeValue& changeValue) {
        changeReason = changeValue.changeReason_;
        return true;
    };
    eventHub->SetOnWillChange(onWillChange);

    richEditorPattern->SetCaretPosition(0);
    richEditorPattern->InsertValue(INIT_VALUE_1);
    richEditorPattern->HandleOnUndoAction();
    EXPECT_EQ(changeReason, TextChangeReason::UNDO);

    struct UpdateSpanStyle typingStyle;
    TextStyle textStyle(5);
    richEditorPattern->SetTypingStyle(typingStyle, textStyle);
    richEditorPattern->textSelector_.Update(0, 2);
    richEditorPattern->InsertValue(INIT_VALUE_2);
    richEditorPattern->HandleOnUndoAction();
    EXPECT_EQ(changeReason, TextChangeReason::UNDO);
}

/**
 * @tc.name: ClearOperationRecords001
 * @tc.desc: test RichEditorPattern ClearOperationRecords
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUndoRedoTest, ClearOperationRecords001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    RichEditorPattern::OperationRecord record;
    richEditorPattern->redoOperationRecords_.push_back(record);
    richEditorPattern->ClearRedoOperationRecords();
    richEditorPattern->redoOperationRecords_.clear();
    richEditorPattern->HandleOnRedoAction();
    ASSERT_EQ(richEditorPattern->redoOperationRecords_.empty(), true);
    richEditorPattern->operationRecords_.push_back(record);
    richEditorPattern->ClearOperationRecords();
    richEditorPattern->operationRecords_.clear();
    richEditorPattern->HandleOnUndoAction();
    ASSERT_EQ(richEditorPattern->operationRecords_.empty(), true);
}

/**
 * @tc.name: SetUndoStyle001
 * @tc.desc: test set UndoStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUndoRedoTest, SetUndoStyle001, TestSize.Level0)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();

    auto richEditorNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    EXPECT_EQ(richEditorPattern->isStyledUndoSupported_, false);
    RichEditorPattern::OperationRecord record;
    richEditorPattern->operationRecords_.push_back(record);
    richEditorPattern->redoOperationRecords_.push_back(record);
    EXPECT_EQ(richEditorPattern->operationRecords_.size(), 1);
    EXPECT_EQ(richEditorPattern->redoOperationRecords_.size(), 1);

    richEditorModel.SetSupportStyledUndo(true);
    EXPECT_EQ(richEditorPattern->isStyledUndoSupported_, true);
    EXPECT_TRUE(richEditorPattern->operationRecords_.empty());
    EXPECT_TRUE(richEditorPattern->redoOperationRecords_.empty());
}

/**
 * @tc.name: BeforeRedo001
 * @tc.desc: test BeforeRedo
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUndoRedoTest, BeforeRedo001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. declare and init variables and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    RichEditorChangeValue changeValue;
    int32_t innerPosition = 0;
    RichEditorPattern::OperationRecord record;
    record.addText = u"test123\n";
    record.beforeCaretPosition = 20;
    /**
     * @tc.steps: step2. change parameters and call function.
     */
    record.deleteCaretPosition = 0;
    richEditorPattern->BeforeRedo(changeValue, innerPosition, record);
    EXPECT_NE(innerPosition, 0);
    /**
     * @tc.steps: step3. change parameters and call function.
     */
    record.deleteCaretPosition = -1;
    record.deleteText = u"test\n";
    richEditorPattern->BeforeRedo(changeValue, innerPosition, record);
    EXPECT_NE(innerPosition, 0);
}

/**
 * @tc.name: BeforeUndo001
 * @tc.desc: test BeforeUndo
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUndoRedoTest, BeforeUndo001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. declare and init variables and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    RichEditorChangeValue changeValue;
    int32_t innerPosition = 0;
    RichEditorPattern::OperationRecord record;
    record.addText = u"test123\n";
    record.afterCaretPosition = 1;
    /**
     * @tc.steps: step2. change parameters and call function.
     */
    record.deleteCaretPosition = 0;
    richEditorPattern->BeforeUndo(changeValue, innerPosition, record);
    EXPECT_NE(innerPosition, 0);
    /**
     * @tc.steps: step3. change parameters and call function.
     */
    record.deleteCaretPosition = -1;
    record.deleteText = u"test\n";
    richEditorPattern->BeforeUndo(changeValue, innerPosition, record);
    EXPECT_NE(innerPosition, 0);
}

/**
 * @tc.name: AddInsertOperationRecord
 * @tc.desc: test AddInsertOperationRecord With PreviewInput
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUndoRedoTest, AddInsertOperationRecord, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    richEditorPattern->isEditing_ = true;

    // step1 insert value with shouldCommitInput is false
    richEditorPattern->SetCaretPosition(0);
    richEditorPattern->ProcessInsertValue(INIT_VALUE_1, OperationType::IME, false);
    EXPECT_TRUE(richEditorPattern->operationRecords_.empty());

    // step2 insert value with shouldCommitInput is true
    richEditorPattern->DeleteForward(0, 6);
    richEditorPattern->SetCaretPosition(0);
    richEditorPattern->ProcessInsertValue(INIT_VALUE_1, OperationType::IME, true);
    EXPECT_EQ(richEditorPattern->operationRecords_.size(), 1);

    // step3 insert value with selection and shouldCommitInput is false
    richEditorPattern->ClearOperationRecords();
    richEditorPattern->textSelector_.Update(0, 6);
    richEditorPattern->SetCaretPosition(0);
    richEditorPattern->ProcessInsertValue(INIT_VALUE_2, OperationType::IME, false);
    ASSERT_TRUE(richEditorPattern->previewInputRecord_.deleteText.has_value());
    EXPECT_EQ(richEditorPattern->previewInputRecord_.deleteText.value(), INIT_VALUE_1);
    EXPECT_EQ(richEditorPattern->previewInputRecord_.beforeCaretPosition, 0);

    // step4 AddInsertOperationRecord with previewInputRecord has value
    RichEditorPattern::OperationRecord record;
    record.addText = INIT_VALUE_1;
    record.afterCaretPosition = 6;
    richEditorPattern->AddInsertOperationRecord(record);
    ASSERT_EQ(richEditorPattern->operationRecords_.size(), 1);
    auto firstRecord = richEditorPattern->operationRecords_.back();
    ASSERT_TRUE(firstRecord.deleteText.has_value());
    EXPECT_EQ(firstRecord.deleteText.value(), INIT_VALUE_1);
    EXPECT_EQ(firstRecord.beforeCaretPosition, 0);
}

} // namespace OHOS::Ace::NG