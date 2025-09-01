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

#include "test/unittest/core/pattern/rich_editor/rich_editor_common_test_ng.h"
#include "test/mock/core/common/mock_udmf.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_clipboard.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/base/mock_task_executor.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model_ng.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
int32_t testOnReadyEvent = 0;
int32_t testAboutToIMEInput = 0;
int32_t testOnIMEInputComplete = 0;
int32_t testAboutToDelete = 0;
int32_t testOnDeleteComplete = 0;
} // namespace

class RichEditorCopyCutPasteTestNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
};

void RichEditorCopyCutPasteTestNg::SetUp()
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

void RichEditorCopyCutPasteTestNg::TearDown()
{
    richEditorNode_ = nullptr;
    testOnReadyEvent = 0;
    testAboutToIMEInput = 0;
    testOnIMEInputComplete = 0;
    testAboutToDelete = 0;
    testOnDeleteComplete = 0;
    MockParagraph::TearDown();
}

void RichEditorCopyCutPasteTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

/**
 * @tc.name: HandleOnCopy001
 * @tc.desc: test HandleOnCopy
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCopyCutPasteTestNg, HandleOnCopy001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto pipeline = MockPipelineContext::GetCurrent();
    auto clipboard = ClipboardProxy::GetInstance()->GetClipboard(pipeline->GetTaskExecutor());
    richEditorPattern->clipboard_ = clipboard;
    AddSpan("test1");
    richEditorPattern->HandleOnCopy();
    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 1;
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, 0);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, 1);
    richEditorPattern->HandleOnCopy();
    ClearSpan();
    AddImageSpan();
    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 1;
    richEditorPattern->HandleOnCopy();
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, 0);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, 1);
}

/**
 * @tc.name: HandleOnCopy002
 * @tc.desc: test InsertValueByPaste
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCopyCutPasteTestNg, HandleOnCopy002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init callback
     */
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    auto richEditorPattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto pipeline = MockPipelineContext::GetCurrent();
    auto clipboard = ClipboardProxy::GetInstance()->GetClipboard(pipeline->GetTaskExecutor());
    richEditorPattern->clipboard_ = clipboard;
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    bool isEventCalled = false;
    auto onCopyWithEvent = [&isEventCalled](NG::TextCommonEvent& event) { isEventCalled = true; };
    richEditorModel.SetOnCopy(std::move(onCopyWithEvent));

    /**
     * @tc.steps: step2. call the callback function
     * @tc.expected: UpdateType_ and isEventCalled is valid
     */
    richEditorPattern->copyOption_ = CopyOptions::InApp;
    richEditorPattern->caretPosition_ = 0;
    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 1;
    richEditorPattern->caretUpdateType_ = CaretUpdateType::PRESSED;
    richEditorPattern->HandleOnCopy();
    EXPECT_EQ(richEditorPattern->caretUpdateType_, CaretUpdateType::NONE);
    EXPECT_EQ(isEventCalled, true);
}

/**
 * @tc.name: HandleOnCopy003
 * @tc.desc: test InsertValueByPaste
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCopyCutPasteTestNg, HandleOnCopy003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init callback
     */
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    auto richEditorPattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto pipeline = MockPipelineContext::GetCurrent();
    auto clipboard = ClipboardProxy::GetInstance()->GetClipboard(pipeline->GetTaskExecutor());
    richEditorPattern->clipboard_ = clipboard;
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    bool isEventCalled = false;
    auto onCopyWithEvent = [&isEventCalled](NG::TextCommonEvent& event) {
        isEventCalled = true;
        event.SetPreventDefault(true);
    };
    richEditorModel.SetOnCopy(std::move(onCopyWithEvent));

    /**
     * @tc.steps: step2. call the callback function
     * @tc.expected: when PreventDefault is true, UpdateType_ and isEventCalled is valid
     */
    richEditorPattern->copyOption_ = CopyOptions::InApp;
    richEditorPattern->caretPosition_ = 0;
    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 1;
    richEditorPattern->HandleOnCopy();
    EXPECT_NE(richEditorPattern->caretUpdateType_, CaretUpdateType::PRESSED);
    EXPECT_EQ(isEventCalled, true);
}

/**
 * @tc.name: HandleOnCopy004
 * @tc.desc: test HandleOnCopy
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCopyCutPasteTestNg, HandleOnCopy004, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto taskExecutor = AceType::MakeRefPtr<MockTaskExecutor>();
    richEditorPattern->clipboard_ = AceType::MakeRefPtr<MockClipBoard>(taskExecutor);
    richEditorPattern->copyOption_ = CopyOptions::InApp;
    bool isUsingExternalKeyboard = true;
    richEditorPattern->selectOverlay_->isUsingMouse_ = true;
    richEditorPattern->ShowSelectOverlay(
        richEditorPattern->textSelector_.firstHandle, richEditorPattern->textSelector_.secondHandle, false);
    EXPECT_TRUE(richEditorPattern->SelectOverlayIsOn());
    richEditorPattern->HandleOnCopy(isUsingExternalKeyboard);
    EXPECT_FALSE(richEditorPattern->SelectOverlayIsOn());
}

/**
 * @tc.name: CopyGestureOption001
 * @tc.desc: test CopyGestureOption
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCopyCutPasteTestNg, CopyGestureOption001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    RefPtr<SpanNode> source = OHOS::Ace::NG::SpanNode::CreateSpanNode(1);
    RefPtr<SpanNode> target = OHOS::Ace::NG::SpanNode::CreateSpanNode(2);
    GestureEventFunc func = [](GestureEvent& info) {};
    source->GetSpanItem()->SetOnClickEvent(std::move(func));
    source->GetSpanItem()->SetLongPressEvent(std::move(func));
    richEditorPattern->CopyGestureOption(source, target);
    ASSERT_NE(source->GetSpanItem(), nullptr);
    ASSERT_NE(target->GetSpanItem(), nullptr);
}

/**
 * @tc.name: CopyGestureOption002
 * @tc.desc: test CopyGestureOption
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCopyCutPasteTestNg, CopyGestureOption002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    RefPtr<SpanNode> source = OHOS::Ace::NG::SpanNode::CreateSpanNode(1);
    RefPtr<SpanNode> target = OHOS::Ace::NG::SpanNode::CreateSpanNode(2);
    GestureEventFunc func1 = [](GestureEvent& info) {};
    OnHoverFunc func2 = [](bool, HoverInfo& info) {};
    source->GetSpanItem()->SetOnClickEvent(std::move(func1));
    source->GetSpanItem()->SetLongPressEvent(std::move(func1));
    source->GetSpanItem()->SetDoubleClickEvent(std::move(func1));
    source->GetSpanItem()->SetHoverEvent(std::move(func2));
    richEditorPattern->CopyGestureOption(source, target);
    EXPECT_TRUE(target->GetSpanItem()->onDoubleClick);
    EXPECT_TRUE(target->GetSpanItem()->onHover);
}

/**
 * @tc.name: HandleOnCopyStyledString001
 * @tc.desc: test HandleOnCopyStyledString
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCopyCutPasteTestNg, HandleOnCopyStyledString001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);

    richEditorPattern->OnModifyDone();
    richEditorPattern->SetSpanStringMode(true);
    richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(u"");
    richEditorPattern->styledString_->SetSpanWatcher(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
    richEditorPattern->OnCopyOperation();
    ASSERT_NE(richEditorPattern->GetClipboard(), nullptr);
}

/**
 * @tc.name: OnCopyOperationExt001
 * @tc.desc: test OnCopyOperationExt
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCopyCutPasteTestNg, OnCopyOperationExt001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);

    richEditorPattern->OnModifyDone();
    auto clipboard = richEditorPattern->GetClipboard();
    ASSERT_NE(clipboard, nullptr);
    auto pasteDataMix = clipboard->CreatePasteDataMix();
    richEditorPattern->OnCopyOperationExt(pasteDataMix);
}

/**
 * @tc.name: InsertValueByPaste001
 * @tc.desc: test InsertValueByPaste
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCopyCutPasteTestNg, InsertValueByPaste001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textFrameNode, geometryNode, textFrameNode->GetLayoutProperty());
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. construct spanItem_.
     */
    textPattern->isSpanStringMode_ = true;

    auto pasteStr = richEditorPattern->GetPasteStr();
    richEditorPattern->InsertValueByPaste(pasteStr);

    richEditorPattern->OnAreaChangedInner();
    OffsetF Offset = {1, 2};
    EXPECT_NE(richEditorPattern->GetPaintRectGlobalOffset(), Offset);
}

/**
 * @tc.name: HandleOnPaste001
 * @tc.desc: test HandleOnPaste
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCopyCutPasteTestNg, HandleOnPaste001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto taskExecutor = context->GetTaskExecutor();
    ASSERT_NE(taskExecutor, nullptr);
    auto clipboard = ClipboardProxy::GetInstance()->GetClipboard(taskExecutor);
    richEditorPattern->clipboard_ = clipboard;
    AddSpan("testHandleOnPaste1");
    richEditorPattern->HandleOnPaste();
    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 8;
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, 0);

    ClearSpan();
    AddImageSpan();
    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 1;
    richEditorPattern->OnCopyOperation(true);
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, 0);

    richEditorPattern->ResetSelection();
    richEditorPattern->OnCopyOperation(true);
    EXPECT_EQ(taskExecutor->GetTotalTaskNum(TaskExecutor::TaskType::BACKGROUND), 0);
}

/**
 * @tc.name: ResetAfterPaste001
 * @tc.desc: test RichEditorPattern ResetAfterPaste
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCopyCutPasteTestNg, ResetAfterPaste001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->previewLongPress_ = true;
    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->RequestFocusImmediately();
    richEditorPattern->isEditing_ = false;
    richEditorPattern->ResetAfterPaste();
    ASSERT_NE(richEditorPattern->previewLongPress_, true);
}

/**
 * @tc.name: PasteStr001
 * @tc.desc: test PasteStr
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCopyCutPasteTestNg, PasteStr001, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto changeReason = TextChangeReason::UNKNOWN;
    auto onWillChange = [&changeReason](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(changeValue.changeReason_, TextChangeReason::PASTE);
        changeReason = changeValue.changeReason_;
        return true;
    };
    eventHub->SetOnWillChange(onWillChange);

    ASSERT_NE(richEditorPattern, nullptr);
    std::string text = "text";
    richEditorPattern->PasteStr(text);
    EXPECT_EQ(changeReason, TextChangeReason::PASTE);
    EXPECT_FALSE(richEditorPattern->previewLongPress_);
}

/**
 * @tc.name: PasteStr002
 * @tc.desc: test PasteStr
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCopyCutPasteTestNg, PasteStr002, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    std::string text = "";
    auto str = richEditorPattern->pasteStr_;
    richEditorPattern->PasteStr(text);
    EXPECT_EQ(str, richEditorPattern->pasteStr_);
}

/**
 * @tc.name: HandleOnCut001
 * @tc.desc: test RichEditorPattern HandleOnCut
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCopyCutPasteTestNg, HandleOnCut001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->copyOption_ = CopyOptions::None;
    richEditorPattern->HandleOnCut();
    richEditorPattern->copyOption_ = CopyOptions::InApp;
    richEditorPattern->previewLongPress_ = true;
    richEditorPattern->HandleOnCut();
    ASSERT_EQ(richEditorPattern->textSelector_.IsValid(), false);
    richEditorPattern->textSelector_.baseOffset = -2;
    richEditorPattern->textSelector_.destinationOffset = -2;
    richEditorPattern->HandleOnCut();
    ASSERT_EQ(richEditorPattern->textSelector_.IsValid(), false);
}

/**
 * @tc.name: HandleOnCut002
 * @tc.desc: test InsertValueByPaste
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCopyCutPasteTestNg, HandleOnCut002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init callback
     */
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    auto richEditorPattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    bool isEventCalled = false;
    auto onCutWithEvent = [&isEventCalled](NG::TextCommonEvent& event) { isEventCalled = true; };
    richEditorModel.SetOnCut(std::move(onCutWithEvent));

    auto changeReason = TextChangeReason::UNKNOWN;
    auto onWillChange = [&changeReason](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(changeValue.changeReason_, TextChangeReason::CUT);
        changeReason = changeValue.changeReason_;
        return true;
    };
    richEditorModel.SetOnWillChange(onWillChange);

    std::string str = "testHandleOnCut";
    AddSpan(str);
    richEditorPattern->UpdateSelector(0, static_cast<int32_t>(str.length()));

    /**
     * @tc.steps: step2. call the callback function
     * @tc.expected: UpdateType_ and isEventCalled is valid
     */
    auto pipeline = MockPipelineContext::GetCurrent();
    auto clipboard = ClipboardProxy::GetInstance()->GetClipboard(pipeline->GetTaskExecutor());
    richEditorPattern->clipboard_ = clipboard;
    richEditorPattern->copyOption_ = CopyOptions::InApp;
    richEditorPattern->caretPosition_ = 0;
    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 1;
    richEditorPattern->caretUpdateType_ = CaretUpdateType::PRESSED;
    richEditorPattern->HandleOnCut();
    EXPECT_EQ(changeReason, TextChangeReason::CUT); // not preventDefault
    EXPECT_EQ(richEditorPattern->caretUpdateType_, CaretUpdateType::NONE);
    EXPECT_EQ(isEventCalled, true);
}

/**
 * @tc.name: HandleOnCut003
 * @tc.desc: test InsertValueByPaste
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCopyCutPasteTestNg, HandleOnCut003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init callback
     */
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    auto richEditorPattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    bool isEventCalled = false;
    auto onCutWithEvent = [&isEventCalled](NG::TextCommonEvent& event) {
        isEventCalled = true;
        event.SetPreventDefault(true);
    };
    richEditorModel.SetOnCut(std::move(onCutWithEvent));

    /**
     * @tc.steps: step2. call the callback function
     * @tc.expected: when PreventDefault is true, UpdateType_ and isEventCalled is valid
     */
    richEditorPattern->copyOption_ = CopyOptions::InApp;
    richEditorPattern->caretPosition_ = 0;
    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 1;
    richEditorPattern->HandleOnCut();
    EXPECT_NE(richEditorPattern->caretUpdateType_, CaretUpdateType::PRESSED);
    EXPECT_EQ(isEventCalled, true);
}

/**
 * @tc.name: HandleOnCut004
 * @tc.desc: test HandleOnCut
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCopyCutPasteTestNg, HandleOnCut004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init callback
     */
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    auto richEditorPattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    bool isEventCalled = false;
    auto onCutWithEvent = [&isEventCalled](NG::TextCommonEvent& event) {
        isEventCalled = true;
        event.SetPreventDefault(true);
    };
    richEditorModel.SetOnCut(std::move(onCutWithEvent));
    richEditorPattern->AddTextSpan(TEXT_SPAN_OPTIONS_1);

    auto changeReason = TextChangeReason::UNKNOWN;
    auto onWillChange = [&changeReason](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(changeValue.changeReason_, TextChangeReason::CUT);
        changeReason = changeValue.changeReason_;
        return true;
    };
    richEditorModel.SetOnWillChange(onWillChange);

    /**
     * @tc.steps: step2. call the callback function
     * @tc.expected: when PreventDefault is true, UpdateType_ and isEventCalled is valid
     */
    richEditorPattern->copyOption_ = CopyOptions::InApp;
    richEditorPattern->caretPosition_ = 0;
    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 1;
    richEditorPattern->previewLongPress_ = true;
    richEditorPattern->HandleOnCut();
    EXPECT_EQ(changeReason, TextChangeReason::UNKNOWN); // preventDefault
    EXPECT_NE(richEditorPattern->caretUpdateType_, CaretUpdateType::PRESSED);
    EXPECT_EQ(isEventCalled, true);
}

/**
 * @tc.name: SetSubSpans001
 * @tc.desc: test SetSubSpans
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCopyCutPasteTestNg, SetSubSpans001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    RefPtr<SpanItem> spanItem = AceType::MakeRefPtr<SpanItem>();
    RefPtr<SpanItem> spanItem1 = AceType::MakeRefPtr<SpanItem>();
    spanItem->spanItemType = SpanItemType::SYMBOL;
    spanItem1->spanItemType = SpanItemType::NORMAL;
    spanItem1->position = 0;
    richEditorPattern->spans_.push_back(spanItem);
    richEditorPattern->spans_.push_back(spanItem1);
    RefPtr<SpanString> spanString = AceType::MakeRefPtr<SpanString>(INIT_VALUE_1);
    richEditorPattern->SetSubSpans(spanString, 1, 1, spanString->spans_);
    EXPECT_EQ(spanString->spans_.size(), 0);
}

/**
 * @tc.name: CopySpansForClipboard
 * @tc.desc: test CopySpansForClipboard function
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCopyCutPasteTestNg, CopySpansForClipboard, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    RefPtr<SpanItem> spanItem = AceType::MakeRefPtr<SpanItem>();
    RefPtr<SpanItem> spanItem1 = AceType::MakeRefPtr<SpanItem>();
    spanItem->spanItemType = SpanItemType::SYMBOL;
    spanItem1->spanItemType = SpanItemType::NORMAL;
    int32_t position = 2;
    spanItem1->position = position;
    std::u16string content = u"123";
    spanItem1->content = content;
    richEditorPattern->spans_.push_back(spanItem);
    richEditorPattern->spans_.push_back(spanItem1);
    auto copySpans = richEditorPattern->CopySpansForClipboard(richEditorPattern->spans_);
    std::u16string resultContent = u"";
    int32_t resultPosition = -1;
    if (!copySpans.empty()) {
        for (const auto& spanItem : copySpans) {
            if (spanItem->spanItemType == SpanItemType::NORMAL) {
                resultContent = spanItem->content;
                resultPosition = spanItem->position;
            }
        }
    }
    EXPECT_EQ(resultContent, content);
    EXPECT_EQ(resultPosition, position);
}

/**
 * @tc.name: OnModifyDone001
 * @tc.desc: test OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCopyCutPasteTestNg, OnModifyDone001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->clipboard_ = nullptr;
    richEditorPattern->OnModifyDone();
    EXPECT_TRUE(richEditorPattern->clipboard_);
}

/**
 * @tc.name: AddUdmfData001
 * @tc.desc: test AddUdmfData
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCopyCutPasteTestNg, AddUdmfData001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    ResultObject resultObject;
    richEditorPattern->dragResultObjects_.emplace_back(resultObject);

    resultObject.type = SelectSpanType::TYPESYMBOLSPAN;
    richEditorPattern->dragResultObjects_.emplace_back(resultObject);

    resultObject.type = SelectSpanType::TYPEIMAGE;
    resultObject.valueString = INIT_VALUE_1;
    richEditorPattern->dragResultObjects_.emplace_back(resultObject);

    resultObject.type = SelectSpanType::TYPEIMAGE;
    resultObject.valueString.clear();
    richEditorPattern->dragResultObjects_.emplace_back(resultObject);

    resultObject.type = SelectSpanType::TYPEIMAGE;
    resultObject.valuePixelMap = PixelMap::CreatePixelMap(nullptr);
    ASSERT_NE(resultObject.valuePixelMap, nullptr);
    richEditorPattern->dragResultObjects_.emplace_back(resultObject);

    richEditorPattern->AddImageSpan(IMAGE_SPAN_OPTIONS_1);

    auto event = AceType::MakeRefPtr<Ace::DragEvent>();
    richEditorPattern->AddUdmfData(event);
    if (UdmfClient::GetInstance()->CreateUnifiedData()) {
        EXPECT_NE(event->GetData(), 0);
    } else {
        EXPECT_EQ(event->GetData(), 0);
    }
}

/**
 * @tc.name: AsyncHandleOnCopyStyledStringHtml
 * @tc.desc: Test AsyncHandleOnCopyStyledStringHtml.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCopyCutPasteTestNg, AsyncHandleOnCopyStyledStringHtml, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    /**
     * @tc.steps: step2. set AsyncHandleOnCopyStyledStringHtml func param.
     */
    auto spanString = AceType::MakeRefPtr<SpanString>(u"123456789");
    /**
     * @tc.steps: step3. Excute function for AsyncHandleOnCopyStyledStringHtml.
     */
    richEditorPattern->AsyncHandleOnCopyStyledStringHtml(spanString);
    EXPECT_EQ(spanString->GetString(), "123456789");
    EXPECT_EQ(spanString->GetLength(), 9);
}

}