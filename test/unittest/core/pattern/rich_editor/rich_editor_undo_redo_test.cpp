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

using namespace testing;
using namespace testing::ext;
namespace {
constexpr uint32_t RECORD_MAX_LENGTH = 20;
}

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
HWTEST_F(RichEditorUndoRedoTest, RedoDrag001, TestSize.Level1)
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
HWTEST_F(RichEditorUndoRedoTest, UndoDrag001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init and call function.
    */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    RichEditorPattern::OperationRecord record;
    record.deleteCaretPostion = 0;
    record.addText = u"test123";
    richEditorPattern->UndoDrag(record);
    EXPECT_EQ(richEditorPattern->caretPosition_, 7);
}


/**
 * @tc.name: RedoDrag002
 * @tc.desc: test RedoDrag
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUndoRedoTest, RedoDrag002, TestSize.Level1)
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
    record.deleteCaretPostion = 0;
    record.addText = u"test123";
    richEditorPattern->RedoDrag(record);
    EXPECT_EQ(richEditorPattern->caretPosition_, 6);
}


/**
 * @tc.name: UndoDrag003
 * @tc.desc: test UndoDrag
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUndoRedoTest, UndoDrag003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    RichEditorPattern::OperationRecord record;
    record.addText = u"test123\n";
    record.deleteCaretPostion = 1;
    auto caretPosition = richEditorPattern->caretPosition_;
    richEditorPattern->UndoDrag(record);
    EXPECT_NE(richEditorPattern->caretPosition_, caretPosition);
}

/**
 * @tc.name: RedoDrag003
 * @tc.desc: test RedoDrag
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUndoRedoTest, RedoDrag003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    RichEditorPattern::OperationRecord record;
    record.deleteCaretPostion = 1;
    auto caretPosition = richEditorPattern->caretPosition_;
    richEditorPattern->RedoDrag(record);
    EXPECT_EQ(richEditorPattern->caretPosition_, caretPosition);
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
    richEditorPattern->HandleOnRedoAction();
    RichEditorPattern::OperationRecord firstRecord;
    firstRecord.addText = u"first Record helloWorld";
    firstRecord.deleteCaretPostion = 3;
    richEditorPattern->redoOperationRecords_.emplace_back(firstRecord);
    richEditorPattern->HandleOnRedoAction();
    EXPECT_TRUE(richEditorPattern->redoOperationRecords_.empty());

    RichEditorPattern::OperationRecord secondRecord;
    secondRecord.addText = u"second Record helloWorld";
    secondRecord.deleteText = u"helloWorld";
    richEditorPattern->redoOperationRecords_.clear();
    richEditorPattern->redoOperationRecords_.emplace_back(secondRecord);
    richEditorPattern->HandleOnRedoAction();
    EXPECT_TRUE(richEditorPattern->redoOperationRecords_.empty());

    RichEditorPattern::OperationRecord thridRecord;
    thridRecord.deleteText = u"helloWorld";
    thridRecord.beforeCaretPosition = 10;
    thridRecord.afterCaretPosition = 15;
    richEditorPattern->redoOperationRecords_.clear();
    richEditorPattern->redoOperationRecords_.emplace_back(thridRecord);
    richEditorPattern->HandleOnRedoAction();
    EXPECT_TRUE(richEditorPattern->redoOperationRecords_.empty());
}


/**
 * @tc.name: UndoDrag002
 * @tc.desc: test UndoDrag
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUndoRedoTest, UndoDrag002, TestSize.Level1)
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
    record.deleteCaretPostion = -1;
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
    RichEditorPattern::OperationRecord firstRecord;
    firstRecord.addText = u"first Record helloWorld";
    firstRecord.deleteText = u"helloWorld";
    richEditorPattern->operationRecords_.emplace_back(firstRecord);
    richEditorPattern->redoOperationRecords_.clear();
    for (uint32_t count = 0; count < RECORD_MAX_LENGTH; ++count) {
        RichEditorPattern::OperationRecord emptyRecord;
        richEditorPattern->redoOperationRecords_.emplace_back(emptyRecord);
    }
    richEditorPattern->HandleOnUndoAction();
    EXPECT_TRUE(richEditorPattern->operationRecords_.empty());

    RichEditorPattern::OperationRecord secondRecord;
    secondRecord.addText = u"second Record helloWorld";
    secondRecord.deleteCaretPostion = 3;
    richEditorPattern->operationRecords_.clear();
    richEditorPattern->operationRecords_.emplace_back(secondRecord);
    richEditorPattern->HandleOnExtendUndoAction();
    EXPECT_TRUE(richEditorPattern->operationRecords_.empty());
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
    RichEditorPattern::OperationRecord firstRecord;
    firstRecord.addText = u"first Record helloWorld";
    firstRecord.deleteText = u"helloWorld";
    richEditorPattern->operationRecords_.emplace_back(firstRecord);
    richEditorPattern->redoOperationRecords_.clear();
    for (uint32_t count = 0; count < RECORD_MAX_LENGTH; ++count) {
        RichEditorPattern::OperationRecord emptyRecord;
        richEditorPattern->redoOperationRecords_.emplace_back(emptyRecord);
    }
    richEditorPattern->HandleOnUndoAction();
    EXPECT_TRUE(richEditorPattern->operationRecords_.empty());

    struct UpdateSpanStyle typingStyle;
    TextStyle textStyle(5);
    richEditorPattern->SetTypingStyle(typingStyle, textStyle);

    RichEditorPattern::OperationRecord secondRecord;
    secondRecord.addText = u"second Record helloWorld";
    secondRecord.deleteCaretPostion = 3;
    richEditorPattern->operationRecords_.clear();
    richEditorPattern->operationRecords_.emplace_back(secondRecord);
    richEditorPattern->HandleOnUndoAction();
    EXPECT_TRUE(richEditorPattern->operationRecords_.empty());
}

/**
 * @tc.name: ClearOperationRecords001
 * @tc.desc: test RichEditorPattern ClearOperationRecords
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUndoRedoTest, ClearOperationRecords001, TestSize.Level1)
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
HWTEST_F(RichEditorUndoRedoTest, SetUndoStyle001, TestSize.Level1)
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
HWTEST_F(RichEditorUndoRedoTest, BeforeRedo001, TestSize.Level1)
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
    record.deleteCaretPostion = 0;
    richEditorPattern->BeforeRedo(changeValue, innerPosition, record);
    EXPECT_NE(innerPosition, 0);
    /**
     * @tc.steps: step3. change parameters and call function.
     */
    record.deleteCaretPostion = -1;
    record.deleteText = u"test\n";
    richEditorPattern->BeforeRedo(changeValue, innerPosition, record);
    EXPECT_NE(innerPosition, 0);
}

/**
 * @tc.name: BeforeUndo001
 * @tc.desc: test BeforeUndo
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUndoRedoTest, BeforeUndo001, TestSize.Level1)
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
    record.deleteCaretPostion = 0;
    richEditorPattern->BeforeUndo(changeValue, innerPosition, record);
    EXPECT_NE(innerPosition, 0);
    /**
     * @tc.steps: step3. change parameters and call function.
     */
    record.deleteCaretPostion = -1;
    record.deleteText = u"test\n";
    richEditorPattern->BeforeUndo(changeValue, innerPosition, record);
    EXPECT_NE(innerPosition, 0);
}


} // namespace OHOS::Ace::NG