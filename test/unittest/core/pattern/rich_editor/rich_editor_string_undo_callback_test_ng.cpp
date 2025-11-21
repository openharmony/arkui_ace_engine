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
    const std::u16string INIT_TEST_CONTENT = u"RichEditor回调测试";
    const std::u16string PASTE_TEST_CONTENT = u"插入内容";
}

class RichEditorStringUndoCallBackTestNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    void InitContent();
    static void TearDownTestSuite();
};

void RichEditorStringUndoCallBackTestNg::SetUp()
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

void RichEditorStringUndoCallBackTestNg::TearDown()
{
    richEditorNode_ = nullptr;
}

void RichEditorStringUndoCallBackTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void RichEditorStringUndoCallBackTestNg::InitContent()
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
 * @tc.name: CallBackTest001
 * @tc.desc: Test undo paste value.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStringUndoCallBackTestNg, CallBackTest001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    InitContent();
    richEditorPattern->SetCaretPosition(10);
    richEditorPattern->InsertValueByPaste(PASTE_TEST_CONTENT);
    richEditorPattern->SetCaretPosition(14);
    richEditorPattern->StartTwinkling();
    int32_t step = 0;
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto onWillChange = [&step](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(step, 0);
        EXPECT_EQ(changeValue.GetRangeBefore().start, 10);
        EXPECT_EQ(changeValue.GetRangeBefore().end, 14);
        step++;
        return true;
    };
    eventHub->SetOnWillChange(std::move(onWillChange));
    auto onAboutToDelete = [&step](const RichEditorDeleteValue& deleteValue) {
        EXPECT_EQ(step, 1);
        EXPECT_EQ(deleteValue.GetOffset(), 10);
        EXPECT_EQ(deleteValue.GetRichEditorDeleteDirection(), RichEditorDeleteDirection::BACKWARD);
        EXPECT_EQ(deleteValue.GetLength(), 4);
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
        EXPECT_EQ(changeValue.GetRangeBefore().end, 14);
        EXPECT_EQ(changeValue.GetRangeAfter().start, 10);
        EXPECT_EQ(changeValue.GetRangeAfter().end, 10);
    };
    eventHub->SetOnDidChange(std::move(onDidChange));
    richEditorPattern->HandleOnUndoAction();
}

/**
 * @tc.name: CallBackTest002
 * @tc.desc: Test redo paste value.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStringUndoCallBackTestNg, CallBackTest002, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    InitContent();
    richEditorPattern->SetCaretPosition(10);
    richEditorPattern->InsertValueByPaste(PASTE_TEST_CONTENT);
    richEditorPattern->HandleOnUndoAction();
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
        EXPECT_EQ(selectionRange->start_, 14);
        EXPECT_EQ(selectionRange->end_, 14);
        step++;
    };
    eventHub->SetOnSelectionChange(std::move(onSelectionChange));
    auto onIMEInputComplete = [&step](const RichEditorAbstractSpanResult& info) {
        EXPECT_EQ(step, 2);
        EXPECT_EQ(info.OffsetInSpan(), 10);
        EXPECT_EQ(info.GetEraseLength(), 4);
        step++;
    };
    eventHub->SetOnIMEInputComplete(std::move(onIMEInputComplete));
    auto onDidChange = [&step](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(step, 3);
        EXPECT_EQ(changeValue.GetRangeBefore().start, 10);
        EXPECT_EQ(changeValue.GetRangeBefore().end, 10);
        EXPECT_EQ(changeValue.GetRangeAfter().start, 10);
        EXPECT_EQ(changeValue.GetRangeAfter().end, 14);
    };
    eventHub->SetOnDidChange(std::move(onDidChange));
    richEditorPattern->HandleOnRedoAction();
}

/**
 * @tc.name: CallBackTest003
 * @tc.desc: Test undo paste value with selection.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStringUndoCallBackTestNg, CallBackTest003, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    InitContent();
    richEditorPattern->textSelector_.Update(0, 10);
    richEditorPattern->InsertValueByPaste(PASTE_TEST_CONTENT);
    richEditorPattern->SetCaretPosition(4);
    richEditorPattern->StartTwinkling();
    int32_t step = 0;
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto onWillChange = [&step](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(step, 0);
        EXPECT_EQ(changeValue.GetRangeBefore().start, 0);
        EXPECT_EQ(changeValue.GetRangeBefore().end, 4);
        step++;
        return true;
    };
    eventHub->SetOnWillChange(std::move(onWillChange));
    auto onAboutToDelete = [&step](const RichEditorDeleteValue& deleteValue) {
        EXPECT_EQ(step, 1);
        EXPECT_EQ(deleteValue.GetOffset(), 0);
        EXPECT_EQ(deleteValue.GetRichEditorDeleteDirection(), RichEditorDeleteDirection::BACKWARD);
        EXPECT_EQ(deleteValue.GetLength(), 4);
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
            EXPECT_EQ(selectionRange->start_, 0);
            EXPECT_EQ(selectionRange->end_, 0);
        } else {
            EXPECT_EQ(step, 3);
            EXPECT_EQ(selectionRange->start_, 10);
            EXPECT_EQ(selectionRange->end_, 10);
        }
        onSelectionNum++;
        step++;
    };
    eventHub->SetOnSelectionChange(std::move(onSelectionChange));
    richEditorPattern->HandleOnUndoAction();
    EXPECT_EQ(onSelectionNum, 2);
}

/**
 * @tc.name: CallBackTest004
 * @tc.desc: Test undo paste value with selection.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStringUndoCallBackTestNg, CallBackTest004, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    InitContent();
    richEditorPattern->textSelector_.Update(0, 10);
    richEditorPattern->InsertValueByPaste(PASTE_TEST_CONTENT);
    richEditorPattern->SetCaretPosition(4);
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
    auto onSelectionChange = [&step](const BaseEventInfo* info) {
        step++;
    };
    eventHub->SetOnSelectionChange(std::move(onSelectionChange));
    auto onIMEInputComplete = [&step](const RichEditorAbstractSpanResult& info) {
        EXPECT_EQ(step, 4);
        EXPECT_EQ(info.OffsetInSpan(), 0);
        EXPECT_EQ(info.GetEraseLength(), 10);
        step++;
    };
    eventHub->SetOnIMEInputComplete(std::move(onIMEInputComplete));
    auto onDidChange = [&step](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(step, 5);
        EXPECT_EQ(changeValue.GetRangeBefore().start, 0);
        EXPECT_EQ(changeValue.GetRangeBefore().end, 4);
        EXPECT_EQ(changeValue.GetRangeAfter().start, 0);
        EXPECT_EQ(changeValue.GetRangeAfter().end, 10);
    };
    eventHub->SetOnDidChange(std::move(onDidChange));
    richEditorPattern->HandleOnUndoAction();
}

/**
 * @tc.name: CallBackTest005
 * @tc.desc: Test redo paste value with selection.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStringUndoCallBackTestNg, CallBackTest005, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    InitContent();
    richEditorPattern->textSelector_.Update(0, 10);
    richEditorPattern->InsertValueByPaste(PASTE_TEST_CONTENT);
    richEditorPattern->HandleOnUndoAction();
    richEditorPattern->SetCaretPosition(10);
    richEditorPattern->StartTwinkling();
    int32_t step = 0;
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto onWillChange = [&step](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(step, 0);
        EXPECT_EQ(changeValue.GetRangeBefore().start, 0);
        EXPECT_EQ(changeValue.GetRangeBefore().end, 10);
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
            EXPECT_EQ(selectionRange->start_, 0);
            EXPECT_EQ(selectionRange->end_, 0);
        } else {
            EXPECT_EQ(step, 3);
            EXPECT_EQ(selectionRange->start_, 4);
            EXPECT_EQ(selectionRange->end_, 4);
        }
        onSelectionNum++;
        step++;
    };
    eventHub->SetOnSelectionChange(std::move(onSelectionChange));
    auto onAboutToDelete = [&step](const RichEditorDeleteValue& deleteValue) {
        EXPECT_EQ(step, 2);
        EXPECT_EQ(deleteValue.GetOffset(), 0);
        EXPECT_EQ(deleteValue.GetRichEditorDeleteDirection(), RichEditorDeleteDirection::FORWARD);
        EXPECT_EQ(deleteValue.GetLength(), 10);
        step++;
        return true;
    };
    eventHub->SetAboutToDelete(std::move(onAboutToDelete));
    richEditorPattern->HandleOnRedoAction();
    EXPECT_EQ(onSelectionNum, 2);
}

/**
 * @tc.name: CallBackTest006
 * @tc.desc: Test redo paste value with selection.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStringUndoCallBackTestNg, CallBackTest006, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    InitContent();
    richEditorPattern->textSelector_.Update(0, 10);
    richEditorPattern->InsertValueByPaste(PASTE_TEST_CONTENT);
    richEditorPattern->HandleOnUndoAction();
    richEditorPattern->SetCaretPosition(10);
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
        EXPECT_EQ(info.OffsetInSpan(), 0);
        EXPECT_EQ(info.GetEraseLength(), 4);
        step++;
    };
    eventHub->SetOnIMEInputComplete(std::move(onIMEInputComplete));
    auto onDidChange = [&step](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(step, 5);
        EXPECT_EQ(changeValue.GetRangeBefore().start, 0);
        EXPECT_EQ(changeValue.GetRangeBefore().end, 10);
        EXPECT_EQ(changeValue.GetRangeAfter().start, 0);
        EXPECT_EQ(changeValue.GetRangeAfter().end, 4);
    };
    eventHub->SetOnDidChange(std::move(onDidChange));
    richEditorPattern->HandleOnRedoAction();
}

/**
 * @tc.name: CallBackTest007
 * @tc.desc: Test undo cut action.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStringUndoCallBackTestNg, CallBackTest007, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    InitContent();
    richEditorPattern->textSelector_.Update(0, 10);
    richEditorPattern->HandleOnCut();
    richEditorPattern->SetCaretPosition(0);
    richEditorPattern->StartTwinkling();
    int32_t step = 0;
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto onWillChange = [&step](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(step, 0);
        EXPECT_EQ(changeValue.GetRangeBefore().start, 0);
        EXPECT_EQ(changeValue.GetRangeBefore().end, 0);
        step++;
        return true;
    };
    eventHub->SetOnWillChange(std::move(onWillChange));
    auto onSelectionChange = [&step](const BaseEventInfo* info) {
        EXPECT_EQ(step, 1);
        const auto* selectionRange = TypeInfoHelper::DynamicCast<SelectionRangeInfo>(info);
        ASSERT_NE(selectionRange, nullptr);
        EXPECT_EQ(selectionRange->start_, 10);
        EXPECT_EQ(selectionRange->end_, 10);
        step++;
    };
    eventHub->SetOnSelectionChange(std::move(onSelectionChange));
    auto onIMEInputComplete = [&step](const RichEditorAbstractSpanResult& info) {
        EXPECT_EQ(step, 2);
        EXPECT_EQ(info.OffsetInSpan(), 0);
        EXPECT_EQ(info.GetEraseLength(), 10);
        step++;
    };
    eventHub->SetOnIMEInputComplete(std::move(onIMEInputComplete));
    auto onDidChange = [&step](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(step, 3);
        EXPECT_EQ(changeValue.GetRangeBefore().start, 0);
        EXPECT_EQ(changeValue.GetRangeBefore().end, 0);
        EXPECT_EQ(changeValue.GetRangeAfter().start, 0);
        EXPECT_EQ(changeValue.GetRangeAfter().end, 10);
    };
    eventHub->SetOnDidChange(std::move(onDidChange));
    richEditorPattern->HandleOnUndoAction();
}

/**
 * @tc.name: CallBackTest008
 * @tc.desc: Test redo cut action.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStringUndoCallBackTestNg, CallBackTest008, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    InitContent();
    richEditorPattern->textSelector_.Update(0, 10);
    richEditorPattern->HandleOnCut();
    richEditorPattern->HandleOnUndoAction();
    richEditorPattern->SetCaretPosition(10);
    richEditorPattern->StartTwinkling();
    int32_t step = 0;
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto onWillChange = [&step](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(step, 0);
        EXPECT_EQ(changeValue.GetRangeBefore().start, 0);
        EXPECT_EQ(changeValue.GetRangeBefore().end, 10);
        step++;
        return true;
    };
    eventHub->SetOnWillChange(std::move(onWillChange));
    auto onAboutToDelete = [&step](const RichEditorDeleteValue& deleteValue) {
        EXPECT_EQ(step, 1);
        EXPECT_EQ(deleteValue.GetOffset(), 0);
        EXPECT_EQ(deleteValue.GetRichEditorDeleteDirection(), RichEditorDeleteDirection::BACKWARD);
        EXPECT_EQ(deleteValue.GetLength(), 10);
        step++;
        return true;
    };
    eventHub->SetAboutToDelete(std::move(onAboutToDelete));
    auto onSelectionChange = [&step](const BaseEventInfo* info) {
        EXPECT_EQ(step, 2);
        const auto* selectionRange = TypeInfoHelper::DynamicCast<SelectionRangeInfo>(info);
        ASSERT_NE(selectionRange, nullptr);
        EXPECT_EQ(selectionRange->start_, 0);
        EXPECT_EQ(selectionRange->end_, 0);
        step++;
    };
    eventHub->SetOnSelectionChange(std::move(onSelectionChange));
    auto onDidChange = [&step](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(step, 3);
        EXPECT_EQ(changeValue.GetRangeBefore().start, 0);
        EXPECT_EQ(changeValue.GetRangeBefore().end, 10);
        EXPECT_EQ(changeValue.GetRangeAfter().start, 0);
        EXPECT_EQ(changeValue.GetRangeAfter().end, 0);
    };
    eventHub->SetOnDidChange(std::move(onDidChange));
    richEditorPattern->HandleOnRedoAction();
}

/**
 * @tc.name: CallBackTest009
 * @tc.desc: Test undo add text span.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStringUndoCallBackTestNg, CallBackTest009, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    InitContent();
    TextSpanOptions options;
    options.value = PASTE_TEST_CONTENT;
    richEditorPattern->AddTextSpan(options);
    richEditorPattern->SetCaretPosition(18);
    richEditorPattern->StartTwinkling();
    int32_t step = 0;
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto onWillChange = [&step](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(step, 0);
        EXPECT_EQ(changeValue.GetRangeBefore().start, 14);
        EXPECT_EQ(changeValue.GetRangeBefore().end, 18);
        step++;
        return true;
    };
    eventHub->SetOnWillChange(std::move(onWillChange));
    auto onAboutToDelete = [&step](const RichEditorDeleteValue& deleteValue) {
        EXPECT_EQ(step, 1);
        EXPECT_EQ(deleteValue.GetOffset(), 14);
        EXPECT_EQ(deleteValue.GetRichEditorDeleteDirection(), RichEditorDeleteDirection::BACKWARD);
        EXPECT_EQ(deleteValue.GetLength(), 4);
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
        EXPECT_EQ(changeValue.GetRangeBefore().end, 18);
        EXPECT_EQ(changeValue.GetRangeAfter().start, 14);
        EXPECT_EQ(changeValue.GetRangeAfter().end, 14);
    };
    eventHub->SetOnDidChange(std::move(onDidChange));
    richEditorPattern->HandleOnUndoAction();
}

/**
 * @tc.name: CallBackTest010
 * @tc.desc: Test redo add text span.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStringUndoCallBackTestNg, CallBackTest010, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    InitContent();
    TextSpanOptions options;
    options.value = PASTE_TEST_CONTENT;
    richEditorPattern->AddTextSpan(options);
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
        EXPECT_EQ(selectionRange->start_, 18);
        EXPECT_EQ(selectionRange->end_, 18);
        step++;
    };
    eventHub->SetOnSelectionChange(std::move(onSelectionChange));
    auto onIMEInputComplete = [&step](const RichEditorAbstractSpanResult& info) {
        EXPECT_EQ(step, 2);
        EXPECT_EQ(info.OffsetInSpan(), 14);
        EXPECT_EQ(info.GetEraseLength(), 4);
        step++;
    };
    eventHub->SetOnIMEInputComplete(std::move(onIMEInputComplete));
    auto onDidChange = [&step](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(step, 3);
        EXPECT_EQ(changeValue.GetRangeBefore().start, 14);
        EXPECT_EQ(changeValue.GetRangeBefore().end, 14);
        EXPECT_EQ(changeValue.GetRangeAfter().start, 14);
        EXPECT_EQ(changeValue.GetRangeAfter().end, 18);
    };
    eventHub->SetOnDidChange(std::move(onDidChange));
    richEditorPattern->HandleOnRedoAction();
}

/**
 * @tc.name: CallBackTest011
 * @tc.desc: Test undo add image span.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStringUndoCallBackTestNg, CallBackTest011, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    InitContent();
    richEditorPattern->AddImageSpan(IMAGE_SPAN_OPTIONS_1);
    richEditorPattern->SetCaretPosition(15);
    richEditorPattern->StartTwinkling();
    int32_t step = 0;
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto onWillChange = [&step](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(step, 0);
        EXPECT_EQ(changeValue.GetRangeBefore().start, 14);
        EXPECT_EQ(changeValue.GetRangeBefore().end, 15);
        step++;
        return true;
    };
    eventHub->SetOnWillChange(std::move(onWillChange));
    auto onAboutToDelete = [&step](const RichEditorDeleteValue& deleteValue) {
        EXPECT_EQ(step, 1);
        EXPECT_EQ(deleteValue.GetOffset(), 14);
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
        EXPECT_EQ(selectionRange->start_, 14);
        EXPECT_EQ(selectionRange->end_, 14);
        step++;
    };
    eventHub->SetOnSelectionChange(std::move(onSelectionChange));
    auto onDidChange = [&step](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(step, 3);
        EXPECT_EQ(changeValue.GetRangeBefore().start, 14);
        EXPECT_EQ(changeValue.GetRangeBefore().end, 15);
        EXPECT_EQ(changeValue.GetRangeAfter().start, 14);
        EXPECT_EQ(changeValue.GetRangeAfter().end, 14);
    };
    eventHub->SetOnDidChange(std::move(onDidChange));
    richEditorPattern->HandleOnUndoAction();
}

/**
 * @tc.name: CallBackTest012
 * @tc.desc: Test redo add text span.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStringUndoCallBackTestNg, CallBackTest012, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    InitContent();
    richEditorPattern->AddImageSpan(IMAGE_SPAN_OPTIONS_1);
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
        EXPECT_EQ(selectionRange->start_, 15);
        EXPECT_EQ(selectionRange->end_, 15);
        step++;
    };
    eventHub->SetOnSelectionChange(std::move(onSelectionChange));
    auto onIMEInputComplete = [&step](const RichEditorAbstractSpanResult& info) {
        EXPECT_EQ(step, 2);
        EXPECT_EQ(info.OffsetInSpan(), 14);
        EXPECT_EQ(info.GetEraseLength(), 1);
        step++;
    };
    eventHub->SetOnIMEInputComplete(std::move(onIMEInputComplete));
    auto onDidChange = [&step](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(step, 3);
        EXPECT_EQ(changeValue.GetRangeBefore().start, 14);
        EXPECT_EQ(changeValue.GetRangeBefore().end, 14);
        EXPECT_EQ(changeValue.GetRangeAfter().start, 14);
        EXPECT_EQ(changeValue.GetRangeAfter().end, 15);
    };
    eventHub->SetOnDidChange(std::move(onDidChange));
    richEditorPattern->HandleOnRedoAction();
}

/**
 * @tc.name: CallBackTest013
 * @tc.desc: Test undo add symbol span.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStringUndoCallBackTestNg, CallBackTest013, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    InitContent();
    richEditorPattern->AddSymbolSpan(SYMBOL_SPAN_OPTIONS_1);
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
 * @tc.name: CallBackTest014
 * @tc.desc: Test redo add symbol span.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStringUndoCallBackTestNg, CallBackTest014, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    InitContent();
    richEditorPattern->AddSymbolSpan(SYMBOL_SPAN_OPTIONS_1);
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
 * @tc.name: CallBackTest015
 * @tc.desc: Test undo add builder span.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStringUndoCallBackTestNg, CallBackTest015, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    InitContent();
    auto builderNode = FrameNode::GetOrCreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    richEditorPattern->AddPlaceholderSpan(builderNode, {});
    richEditorPattern->SetCaretPosition(15);
    richEditorPattern->StartTwinkling();
    int32_t step = 0;
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto onWillChange = [&step](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(step, 0);
        EXPECT_EQ(changeValue.GetRangeBefore().start, 14);
        EXPECT_EQ(changeValue.GetRangeBefore().end, 15);
        step++;
        return true;
    };
    eventHub->SetOnWillChange(std::move(onWillChange));
    auto onAboutToDelete = [&step](const RichEditorDeleteValue& deleteValue) {
        EXPECT_EQ(step, 1);
        EXPECT_EQ(deleteValue.GetOffset(), 14);
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
        EXPECT_EQ(selectionRange->start_, 14);
        EXPECT_EQ(selectionRange->end_, 14);
        step++;
    };
    eventHub->SetOnSelectionChange(std::move(onSelectionChange));
    auto onDidChange = [&step](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(step, 3);
        EXPECT_EQ(changeValue.GetRangeBefore().start, 14);
        EXPECT_EQ(changeValue.GetRangeBefore().end, 15);
        EXPECT_EQ(changeValue.GetRangeAfter().start, 14);
        EXPECT_EQ(changeValue.GetRangeAfter().end, 14);
    };
    eventHub->SetOnDidChange(std::move(onDidChange));
    richEditorPattern->HandleOnUndoAction();
}

/**
 * @tc.name: CallBackTest016
 * @tc.desc: Test redo add builder span.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStringUndoCallBackTestNg, CallBackTest016, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    InitContent();
    auto builderNode = FrameNode::GetOrCreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    richEditorPattern->AddPlaceholderSpan(builderNode, {});
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
        EXPECT_EQ(selectionRange->start_, 15);
        EXPECT_EQ(selectionRange->end_, 15);
        step++;
    };
    eventHub->SetOnSelectionChange(std::move(onSelectionChange));
    auto onIMEInputComplete = [&step](const RichEditorAbstractSpanResult& info) {
        EXPECT_EQ(step, 2);
        EXPECT_EQ(info.OffsetInSpan(), 14);
        EXPECT_EQ(info.GetEraseLength(), 1);
        step++;
    };
    eventHub->SetOnIMEInputComplete(std::move(onIMEInputComplete));
    auto onDidChange = [&step](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(step, 3);
        EXPECT_EQ(changeValue.GetRangeBefore().start, 14);
        EXPECT_EQ(changeValue.GetRangeBefore().end, 14);
        EXPECT_EQ(changeValue.GetRangeAfter().start, 14);
        EXPECT_EQ(changeValue.GetRangeAfter().end, 15);
    };
    eventHub->SetOnDidChange(std::move(onDidChange));
    richEditorPattern->HandleOnRedoAction();
}

/**
 * @tc.name: CallBackTest017
 * @tc.desc: Test undo delete spans.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStringUndoCallBackTestNg, CallBackTest017, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    InitContent();
    RangeOptions delOptions;
    delOptions.start = 10;
    delOptions.end = 12;
    richEditorPattern->DeleteSpans(delOptions);
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
 * @tc.name: CallBackTest018
 * @tc.desc: Test redo delete spans.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStringUndoCallBackTestNg, CallBackTest018, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    InitContent();
    RangeOptions delOptions{10, 12};
    richEditorPattern->DeleteSpans(delOptions);
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
    auto onSelectionChange = [&step](const BaseEventInfo* info) {
        EXPECT_EQ(step, 1);
        const auto* selectionRange = TypeInfoHelper::DynamicCast<SelectionRangeInfo>(info);
        ASSERT_NE(selectionRange, nullptr);
        EXPECT_EQ(selectionRange->start_, 10);
        EXPECT_EQ(selectionRange->end_, 10);
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