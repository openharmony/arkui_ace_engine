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
#define private public
#define protected public

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

class RichEditorPatternTestOneNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
};

void RichEditorPatternTestOneNg::SetUp()
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

void RichEditorPatternTestOneNg::TearDown()
{
    richEditorNode_ = nullptr;
    testOnReadyEvent = 0;
    testAboutToIMEInput = 0;
    testOnIMEInputComplete = 0;
    testAboutToDelete = 0;
    testOnDeleteComplete = 0;
    MockParagraph::TearDown();
}

void RichEditorPatternTestOneNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

/**
 * @tc.name: RemoveEmptySpanNodes001
 * @tc.desc: test RichEditorPattern RemoveEmptySpanNodes
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestOneNg, RemoveEmptySpanNodes001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->RemoveEmptySpanNodes();
    auto host = richEditorPattern->GetHost();
    ASSERT_NE(host, nullptr);
}

/**
 * @tc.name: GetParagraphLength001
 * @tc.desc: test RichEditorPattern GetParagraphLength
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestOneNg, GetParagraphLength001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    std::list<RefPtr<UINode>> spans;
    int32_t ret = richEditorPattern->GetParagraphLength(spans);
    ASSERT_EQ(ret, 0);
}

/**
 * @tc.name: HandleClickEvent002
 * @tc.desc: test RichEditorPattern HandleClickEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestOneNg, HandleClickEvent002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    GestureEvent info;
    info.localLocation_ = Offset(0, 0);
    ParagraphStyle paragraphStyle;
    auto paragraph = Paragraph::Create(paragraphStyle, FontCollection::Current());
    richEditorPattern->pManager_->AddParagraph({ .paragraph = paragraph, .paragraphStyle = paragraphStyle });
    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    richEditorPattern->GetFocusHub()->focusType_ = FocusType::DISABLE;
    richEditorPattern->dataDetectorAdapter_->hasClickedAISpan_ = true;
    richEditorPattern->HandleClickEvent(info);
    EXPECT_EQ(richEditorPattern->caretPosition_, 0);
}

/**
 * @tc.name: HandleSingleClickEvent001
 * @tc.desc: test RichEditorPattern HandleSingleClickEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestOneNg, HandleSingleClickEvent001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    RichEditorPattern::OperationRecord record;
    richEditorPattern->DeleteSelectOperation(&record);

    RectF rect(0, 0, 5, 5);
    richEditorPattern->CreateHandles();
    richEditorPattern->textSelector_.Update(0, 5);
    richEditorPattern->selectOverlay_->OnHandleMoveDone(rect, true);

    GestureEvent info;
    info.localLocation_ = Offset(0, 0);
    ParagraphStyle paragraphStyle;
    auto paragraph = Paragraph::Create(paragraphStyle, FontCollection::Current());
    richEditorPattern->pManager_->AddParagraph({ .paragraph = paragraph, .paragraphStyle = paragraphStyle });
    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    richEditorPattern->isMousePressed_ = true;

    richEditorPattern->dataDetectorAdapter_->hasClickedAISpan_ = true;
    richEditorPattern->dataDetectorAdapter_->pressedByLeftMouse_ = true;
    richEditorPattern->HandleSingleClickEvent(info);

    richEditorPattern->dataDetectorAdapter_->hasClickedAISpan_ = false;
    richEditorPattern->dataDetectorAdapter_->pressedByLeftMouse_ = false;
    richEditorPattern->HandleSingleClickEvent(info);

    richEditorPattern->dataDetectorAdapter_->hasClickedAISpan_ = true;
    richEditorPattern->dataDetectorAdapter_->pressedByLeftMouse_ = false;
    richEditorPattern->HandleSingleClickEvent(info);

    richEditorPattern->dataDetectorAdapter_->hasClickedAISpan_ = false;
    richEditorPattern->dataDetectorAdapter_->pressedByLeftMouse_ = true;
    richEditorPattern->HandleSingleClickEvent(info);
    EXPECT_EQ(richEditorPattern->caretPosition_, 0);
}

/**
 * @tc.name: ClickAISpan001
 * @tc.desc: test RichEditorPattern ClickAISpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestOneNg, ClickAISpan001, TestSize.Level1)
{
    AISpan aiSpan;
    aiSpan.start = 0;
    aiSpan.end = 10;
    aiSpan.content = "1234567";
    aiSpan.type = TextDataDetectType::PHONE_NUMBER;
    PointF textOffset = PointF(100, 100);
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    bool res = richEditorPattern->ClickAISpan(textOffset, aiSpan);
    EXPECT_EQ(res, false);
}

/**
 * @tc.name: CalculateEmptyValueCaretRect001
 * @tc.desc: test RichEditorPattern CalculateEmptyValueCaretRect
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestOneNg, CalculateEmptyValueCaretRect001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    EXPECT_CALL(*paragraph, PushStyle(_)).Times(AnyNumber());
    EXPECT_CALL(*paragraph, AddText(_)).Times(AnyNumber());
    EXPECT_CALL(*paragraph, PopStyle()).Times(AnyNumber());
    EXPECT_CALL(*paragraph, Build()).Times(AnyNumber());
    EXPECT_CALL(*paragraph, Layout(_)).Times(AnyNumber());
    TestParagraphItem testParagraphItem = {
        .start = 0, .end = 6, .indexOffsetMap = { { 0, Offset(0, 5) }, { 6, Offset(50, 0) } }
    };
    richEditorPattern->paragraphs_.AddParagraph({ .paragraph = paragraph, .start = 0, .end = 6 });
    CaretMetricsF metricsDown;
    CaretMetricsF metricsUp;
    for (const auto& [index, offset] : testParagraphItem.indexOffsetMap) {
        metricsDown.offset.SetX(offset.GetX());
        metricsDown.offset.SetY(offset.GetY());
        metricsUp.offset.SetX(offset.GetX());
        metricsUp.offset.SetY(offset.GetY());
        EXPECT_CALL(*paragraph, GetGlyphIndexByCoordinate(_, _)).WillRepeatedly(Return(6));
        EXPECT_CALL(*paragraph, GetMaxWidth).WillRepeatedly(Return(150));
        EXPECT_CALL(*paragraph, GetHeight).WillRepeatedly(Return(50));
        EXPECT_CALL(*paragraph, ComputeOffsetForCaretDownstream(index, _, _))
            .WillRepeatedly(DoAll(SetArgReferee<1>(metricsDown), Return(true)));
        EXPECT_CALL(*paragraph, ComputeOffsetForCaretUpstream(index, _, _))
            .WillRepeatedly(DoAll(SetArgReferee<1>(metricsUp), Return(true)));
    }

    TextStyle style;
    style.SetLineHeight(LINE_HEIGHT_VALUE);
    style.SetLetterSpacing(LETTER_SPACING);
    style.SetFontFeatures(TEXT_FONTFEATURE);
    auto layoutProperty = richEditorPattern->GetLayoutProperty<TextLayoutProperty>();
    layoutProperty->UpdateLayoutDirection(TextDirection::RTL);
    richEditorPattern->presetParagraph_ = paragraph;
    richEditorPattern->CalculateEmptyValueCaretRect();
    richEditorPattern->typingTextStyle_ = style;
    richEditorPattern->PreferredParagraph();
    EXPECT_NE(richEditorPattern->presetParagraph_, nullptr);
}

/**
 * @tc.name: HandleLongPress001
 * @tc.desc: test RichEditorPattern HandleLongPress
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestOneNg, HandleLongPress001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    GestureEvent info;
    info.localLocation_ = Offset(0, 0);
    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    richEditorPattern->HandleLongPress(info);
    focusHub->focusType_ = FocusType::DISABLE;
    richEditorPattern->HandleLongPress(info);
    ASSERT_EQ(richEditorPattern->caretUpdateType_, CaretUpdateType::NONE);
}

/**
 * @tc.name: HandleMenuCallbackOnSelectAll001
 * @tc.desc: test RichEditorPattern HandleMenuCallbackOnSelectAll
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestOneNg, HandleMenuCallbackOnSelectAll001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    /**
     * @tc.steps: step1. get richeditor pattern and add add text span
     */
    AddSpan("hello1");
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 6);

    /**
     * @tc.steps: step2. request focus
     */
    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    focusHub->RequestFocusImmediately();

    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);

    bool enabledCache = eventHub->IsEnabled();
    EXPECT_EQ(enabledCache, true);

    /**
     * @tc.step: step3. create a scene where the text menu has popped up
     */
    richEditorPattern->textDetectEnable_ = true;
    richEditorPattern->enabled_ = true;
    richEditorPattern->OnModifyDone();

    richEditorPattern->textDetectEnable_ = true;
    richEditorPattern->enabled_ = false;
    richEditorPattern->OnModifyDone();

    richEditorPattern->textDetectEnable_ = false;
    richEditorPattern->enabled_ = true;
    richEditorPattern->OnModifyDone();

    richEditorPattern->textDetectEnable_ = false;
    richEditorPattern->enabled_ = false;
    richEditorPattern->OnModifyDone();

    richEditorPattern->textSelector_.Update(1, 2);
    richEditorPattern->CalculateHandleOffsetAndShowOverlay();
    richEditorPattern->ShowSelectOverlay(
        richEditorPattern->textSelector_.firstHandle, richEditorPattern->textSelector_.secondHandle, false);
    EXPECT_TRUE(richEditorPattern->SelectOverlayIsOn());

    /**
     * @tc.step: step4. test OnMenuItemAction
     */
    richEditorPattern->selectOverlay_->OnMenuItemAction(OptionMenuActionId::COPY, OptionMenuType::TOUCH_MENU);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextStart(), 1);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextEnd(), 2);

    richEditorPattern->selectOverlay_->OnMenuItemAction(OptionMenuActionId::PASTE, OptionMenuType::NO_MENU);
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 6);

    richEditorPattern->selectOverlay_->isUsingMouse_ = true;
    richEditorPattern->HandleMenuCallbackOnSelectAll();
    ASSERT_EQ(richEditorPattern->IsUsingMouse(), false);
}

/**
 * @tc.name: InsertStyledStringByPaste001
 * @tc.desc: test RichEditorPattern InsertStyledStringByPaste
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestOneNg, InsertStyledStringByPaste001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richEditor pattern and controller
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    /**
     * @tc.steps: step2. add span and select text
     */
    AddSpan("test");
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 4);
    richEditorPattern->textSelector_.Update(3, 4);
    richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>("abc");
    std::string data = "abc";
    RefPtr<SpanString> spanString = AceType::MakeRefPtr<SpanString>(data);
    richEditorPattern->InsertStyledStringByPaste(spanString);

    ASSERT_EQ(richEditorPattern->textSelector_.IsValid(), false);
}

/**
 * @tc.name: AddSpansByPaste001
 * @tc.desc: test RichEditorPattern AddSpansByPaste
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestOneNg, AddSpansByPaste001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richEditor pattern and controller
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    /**
     * @tc.steps: step2. add span and select text
     */
    AddSpan("test");
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 4);
    richEditorPattern->textSelector_.Update(3, 4);
    std::list<RefPtr<NG::SpanItem>> spans;
    OHOS::Ace::RefPtr<OHOS::Ace::NG::SpanItem> spanItem1 = AceType::MakeRefPtr<ImageSpanItem>();
    spans.push_back(spanItem1);
    richEditorPattern->AddSpansByPaste(spans);
    ASSERT_EQ(richEditorPattern->textSelector_.IsValid(), false);
}

/**
 * @tc.name: UnableStandardInput001
 * @tc.desc: test RichEditorPattern UnableStandardInput
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestOneNg, UnableStandardInput001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->UnableStandardInput(true);
    bool res = richEditorPattern->UnableStandardInput(false);
    ASSERT_EQ(res, false);
}

/**
 * @tc.name: GetPreviewTextInfo001
 * @tc.desc: test RichEditorPattern GetPreviewTextInfo
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestOneNg, GetPreviewTextInfo001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    PreviewTextInfo info = richEditorPattern->GetPreviewTextInfo();
    ASSERT_EQ(richEditorPattern->previewTextRecord_.previewContent.empty(), true);

    richEditorPattern->previewTextRecord_.previewContent = "abc";
    info = richEditorPattern->GetPreviewTextInfo();
    ASSERT_EQ(richEditorPattern->previewTextRecord_.previewContent.empty(), false);
}

/**
 * @tc.name: HandleOnDelete001
 * @tc.desc: test RichEditorPattern HandleOnDelete
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestOneNg, HandleOnDelete001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->HandleOnDelete(true);
    richEditorPattern->HandleOnDelete(false);
}

/**
 * @tc.name: CursorMoveUp001
 * @tc.desc: test RichEditorPattern CursorMoveUp
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestOneNg, CursorMoveUp001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    /**
     * @tc.steps: step1. get richeditor pattern and add add text span
     */
    AddSpan("");
    richEditorPattern->CursorMoveUp();
    AddSpan("hello1");
    bool res = richEditorPattern->CursorMoveUp();
    res = richEditorPattern->CursorMoveDown();
    ASSERT_EQ(res, true);
}

/**
 * @tc.name: CursorMoveHome001
 * @tc.desc: test RichEditorPattern CursorMoveHome
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestOneNg, CursorMoveHome001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->caretPosition_ = 0;
    bool res = richEditorPattern->CursorMoveHome();
    ASSERT_EQ(res, false);
}

/**
 * @tc.name: ClearOperationRecords001
 * @tc.desc: test RichEditorPattern ClearOperationRecords
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestOneNg, ClearOperationRecords001, TestSize.Level1)
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
 * @tc.name: ResetAfterPaste001
 * @tc.desc: test RichEditorPattern ResetAfterPaste
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestOneNg, ResetAfterPaste001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->previewLongPress_ = true;
    richEditorPattern->ResetAfterPaste();
    ASSERT_NE(richEditorPattern->previewLongPress_, true);
}

/**
 * @tc.name: HandleOnCut001
 * @tc.desc: test RichEditorPattern HandleOnCut
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestOneNg, HandleOnCut001, TestSize.Level1)
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
 * @tc.name: HandleOnCut004
 * @tc.desc: test HandleOnCut
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestOneNg, HandleOnCut004, TestSize.Level1)
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
    richEditorPattern->caretUpdateType_ = CaretUpdateType::PRESSED;
    richEditorPattern->previewLongPress_ = true;
    richEditorPattern->HandleOnCut();
    EXPECT_EQ(richEditorPattern->caretUpdateType_, CaretUpdateType::PRESSED);
    EXPECT_EQ(isEventCalled, true);
}

/**
 * @tc.name: ShowHandles001
 * @tc.desc: test RichEditorPattern ShowHandles
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestOneNg, ShowHandles001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    /**
     * @tc.steps: step2. initalize span properties
     */
    TextSpanOptions options2;
    options2.value = INIT_VALUE_1;

    /**
     * @tc.steps: step3. test add span
     */
    richEditorController->AddTextSpan(options2);
    focusHub->RequestFocusImmediately();
    richEditorPattern->ShowHandles(true);
    richEditorPattern->ShowHandles(false);
    ASSERT_EQ(richEditorPattern->HasFocus(), true);
}

/**
 * @tc.name: UpdateTextFieldManager001
 * @tc.desc: test RichEditorPattern UpdateTextFieldManager
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestOneNg, UpdateTextFieldManager001, TestSize.Level1)
{
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));

    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    /**
     * @tc.steps: step2. initalize span properties
     */
    TextSpanOptions options2;
    options2.value = INIT_VALUE_1;

    /**
     * @tc.steps: step3. test add span
     */
    richEditorController->AddTextSpan(options2);
    focusHub->RequestFocusImmediately();
    richEditorPattern->ShowHandles(true);
    richEditorPattern->ShowHandles(false);

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));

    auto oldThemeManager = PipelineBase::GetCurrentContext()->themeManager_;
    PipelineBase::GetCurrentContext()->themeManager_ = themeManager;

    RichEditorTheme richEditorTheme;
    EXPECT_EQ(richEditorPattern->GetPreviewTextDecorationColor(), richEditorTheme.GetPreviewUnderLineColor());

    auto safeAreaManager = AceType::MakeRefPtr<SafeAreaManager>();
    MockPipelineContext::GetCurrent()->safeAreaManager_ = safeAreaManager;
    MockPipelineContext::GetCurrent()->SetRootSize(800, 2000);
    auto textFieldManager = AceType::MakeRefPtr<TextFieldManagerNG>();
    textFieldManager->SetHeight(20);
    MockPipelineContext::GetCurrent()->SetTextFieldManager(textFieldManager);

    Offset Offset = { 1, 4 };
    richEditorPattern->UpdateTextFieldManager(Offset, 1.0f);

    richEditorPattern->isTextChange_ = true;
    richEditorPattern->UpdateTextFieldManager(Offset, 1.0f);
    EXPECT_EQ(richEditorPattern->HasFocus(), true);
}

/**
 * @tc.name: JudgeSelectType001
 * @tc.desc: test RichEditorPattern JudgeSelectType
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestOneNg, JudgeSelectType001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);

    richEditorPattern->previewLongPress_ = true;
    auto offset = Offset(50.0, -80.0);
    AddSpan("hello1");
    PositionWithAffinity position = richEditorPattern->paragraphs_.GetGlyphPositionAtCoordinate(offset);
    SelectType type = richEditorPattern->JudgeSelectType(position);
    EXPECT_NE(type, SelectType::SELECT_FORWARD);
    richEditorPattern->previewLongPress_ = false;
    richEditorPattern->editingLongPress_ = true;
    type = richEditorPattern->JudgeSelectType(position);
    EXPECT_NE(type, SelectType::SELECT_FORWARD);
}

/**
 * @tc.name: HandleSelectOverlayWithOptions001
 * @tc.desc: test RichEditorPattern HandleSelectOverlayWithOptions
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestOneNg, HandleSelectOverlayWithOptions001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    SelectionOptions options;
    options.menuPolicy = MenuPolicy::SHOW;
    richEditorPattern->isMousePressed_ = true;
    richEditorPattern->sourceType_ = SourceType::MOUSE;
    richEditorPattern->HandleSelectOverlayWithOptions(options);
    richEditorPattern->isMousePressed_ = false;
    richEditorPattern->sourceType_ = SourceType::MOUSE;
    richEditorPattern->HandleSelectOverlayWithOptions(options);
    richEditorPattern->isMousePressed_ = true;
    richEditorPattern->sourceType_ = SourceType::TOUCH;
    richEditorPattern->HandleSelectOverlayWithOptions(options);
    richEditorPattern->isMousePressed_ = false;
    richEditorPattern->sourceType_ = SourceType::TOUCH;
    richEditorPattern->HandleSelectOverlayWithOptions(options);
    options.menuPolicy = MenuPolicy::DEFAULT;
    richEditorPattern->HandleSelectOverlayWithOptions(options);
    options.menuPolicy = MenuPolicy::HIDE;
    richEditorPattern->HandleSelectOverlayWithOptions(options);
    ClearSpan();
    richEditorPattern->HandleSelectOverlayWithOptions(options);
    ASSERT_EQ(richEditorPattern->SelectOverlayIsOn(), false);
}

/**
 * @tc.name: InsertValueInStyledString001
 * @tc.desc: test RichEditorPattern InsertValueInStyledString
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestOneNg, InsertValueInStyledString001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    TextStyle style;
    style.SetLineHeight(LINE_HEIGHT_VALUE);
    style.SetLetterSpacing(LETTER_SPACING);
    style.SetFontFeatures(TEXT_FONTFEATURE);

    UpdateSpanStyle updateSpanStyle;

    std::string content = "TEST123";
    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(content);

    richEditorPattern->typingStyle_ = std::nullopt;
    richEditorPattern->typingTextStyle_ = std::nullopt;
    richEditorPattern->InsertValueInStyledString("abc");

    richEditorPattern->typingStyle_ = std::nullopt;
    richEditorPattern->typingTextStyle_ = style;
    richEditorPattern->InsertValueInStyledString("abc");

    richEditorPattern->typingStyle_ = updateSpanStyle;
    richEditorPattern->typingTextStyle_ = std::nullopt;
    richEditorPattern->InsertValueInStyledString("abc");

    richEditorPattern->typingStyle_ = updateSpanStyle;
    richEditorPattern->typingTextStyle_ = style;
    richEditorPattern->InsertValueInStyledString("abc");

    ASSERT_EQ(richEditorPattern->typingTextStyle_.has_value(), true);
}

/**
 * @tc.name: InsertValueInStyledString002
 * @tc.desc: test RichEditorPattern InsertValueInStyledString
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestOneNg, InsertValueInStyledString002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    auto host = richEditorPattern->GetHost();
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    TextSpanOptions options2;
    options2.value = INIT_VALUE_1;
    richEditorController->AddTextSpan(options2);
    focusHub->RequestFocusImmediately();
    richEditorPattern->FireOnSelectionChange(-1, 0);
    richEditorPattern->FireOnSelectionChange(0, -1);
    richEditorPattern->FireOnSelectionChange(-1, -1);
    ASSERT_EQ(richEditorPattern->HasFocus(), true);
}

/**
 * @tc.name: CreateDecorationSpanByTextStyle001
 * @tc.desc: test RichEditorPattern CreateDecorationSpanByTextStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestOneNg, CreateDecorationSpanByTextStyle001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    UpdateSpanStyle updateSpanStyle;
    updateSpanStyle.updateTextDecorationStyle = TextDecorationStyle::DASHED;
    TextStyle style;
    style.SetLineHeight(LINE_HEIGHT_VALUE);
    style.SetLetterSpacing(LETTER_SPACING);
    style.SetFontFeatures(TEXT_FONTFEATURE);
    RefPtr<DecorationSpan> span = richEditorPattern->CreateDecorationSpanByTextStyle(updateSpanStyle, style, 0);
    ASSERT_NE(span, nullptr);
}

/**
 * @tc.name: DeleteValueInStyledString001
 * @tc.desc: test RichEditorPattern DeleteValueInStyledString
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestOneNg, DeleteValueInStyledString001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>("abc");
    richEditorPattern->caretVisible_ = false;
    richEditorPattern->previewLongPress_ = true;
    richEditorPattern->DeleteValueInStyledString(0, 10, true);
    richEditorPattern->previewLongPress_ = false;
    richEditorPattern->DeleteValueInStyledString(0, 10, true);
    richEditorPattern->previewLongPress_ = true;
    richEditorPattern->DeleteValueInStyledString(0, 10, false);
    richEditorPattern->previewLongPress_ = false;
    richEditorPattern->DeleteValueInStyledString(0, 10, false);
    ASSERT_EQ(!richEditorPattern->BeforeStyledStringChange(0, 10, ""), false);
}

/**
 * @tc.name: MouseDoubleClickParagraphEnd001
 * @tc.desc: test RichEditorPattern MouseDoubleClickParagraphEnd
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestOneNg, MouseDoubleClickParagraphEnd001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    AddSpan("TEST123");
    std::string content = "TEST123";
    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(content);

    richEditorPattern->typingStyle_ = std::nullopt;
    richEditorPattern->typingTextStyle_ = std::nullopt;
    richEditorPattern->InsertValueInStyledString("TEST123");

    richEditorPattern->caretUpdateType_ = CaretUpdateType::DOUBLE_CLICK;
    richEditorPattern->sourceType_ = SourceType::MOUSE;
    int32_t index = 7;
    int32_t index2 = 2;
    richEditorPattern->MouseDoubleClickParagraphEnd(index2);
    richEditorPattern->MouseDoubleClickParagraphEnd(index);
    EXPECT_EQ(richEditorPattern->GetParagraphEndPosition(index), 7);
}

/**
 * @tc.name: CreateImageSourceInfo002
 * @tc.desc: test CreateImageSourceInfo
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestOneNg, CreateImageSourceInfo002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateEventHub();
    ImageSpanOptions options;
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(voidPtr);
    ASSERT_NE(pixelMap, nullptr);
    options.imagePixelMap = pixelMap;
    richEditorPattern->CreateImageSourceInfo(options);
    EXPECT_EQ(options.imagePixelMap.has_value(), true);
}

/**
 * @tc.name: GetTextContentLength001
 * @tc.desc: test GetTextContentLength
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestOneNg, GetTextContentLength001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->styledString_ = nullptr;
    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->GetTextContentLength();

    richEditorPattern->styledString_ = nullptr;
    richEditorPattern->isSpanStringMode_ = false;
    richEditorPattern->GetTextContentLength();

    richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>("abc");
    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->GetTextContentLength();

    richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>("abc");
    richEditorPattern->isSpanStringMode_ = false;
    int32_t res = richEditorPattern->GetTextContentLength();
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: SetGestureOptions001
 * @tc.desc: test SetGestureOptions
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestOneNg, SetGestureOptions001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    OHOS::Ace::UserGestureOptions userGestureOptions;
    userGestureOptions.onLongPress = [](GestureEvent& info) {};
    auto spanItem = AceType::MakeRefPtr<SpanItem>();

    richEditorPattern->SetGestureOptions(userGestureOptions, spanItem);

    EXPECT_NE(userGestureOptions.onLongPress, nullptr);
}

/**
 * @tc.name: AddTextSpan001
 * @tc.desc: test AddTextSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestOneNg, AddTextSpan001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    TextSpanOptions options;
    richEditorPattern->previewTextRecord_.previewContent = "123";
    richEditorPattern->previewTextRecord_.isPreviewTextInputting = true;
    richEditorPattern->previewTextRecord_.startOffset = 0;
    richEditorPattern->previewTextRecord_.endOffset = 0;
    EXPECT_EQ(richEditorPattern->previewTextRecord_.IsValid(), true);
    int32_t res = richEditorPattern->AddTextSpan(options, true, 0);
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: DeleteSpansOperation001
 * @tc.desc: test DeleteSpansOperation
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestOneNg, DeleteSpansOperation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richEditor pattern and controller
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    AddSpan("test");
    richEditorPattern->textSelector_.Update(3, 4);
    richEditorPattern->DeleteSpansOperation(0, 0);
    EXPECT_FALSE(richEditorPattern->textSelector_.IsValid());
}

/**
 * @tc.name: DeleteSpansByRange001
 * @tc.desc: test DeleteSpansByRange
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestOneNg, DeleteSpansByRange001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    SpanPositionInfo startInfo;
    SpanPositionInfo endInfo;
    startInfo.spanIndex_ = -1;
    richEditorPattern->DeleteSpansByRange(0, 0, startInfo, endInfo);
    EXPECT_EQ(richEditorPattern->GetHost()->GetChildren().size(), 0);
}

/**
 * @tc.name: CopyGestureOption001
 * @tc.desc: test CopyGestureOption
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestOneNg, CopyGestureOption001, TestSize.Level1)
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
 * @tc.name: SetCaretOffset001
 * @tc.desc: test SetCaretOffset
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestOneNg, SetCaretOffset001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->previewTextRecord_.previewContent = "abc";
    richEditorPattern->previewTextRecord_.isPreviewTextInputting = true;
    richEditorPattern->previewTextRecord_.startOffset = 0;
    richEditorPattern->previewTextRecord_.endOffset = 0;

    bool res = richEditorPattern->SetCaretOffset(0);
    ASSERT_EQ(res, false);
}

/**
 * @tc.name: CalcCursorOffsetByPosition001
 * @tc.desc: test CalcCursorOffsetByPosition
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestOneNg, CalcCursorOffsetByPosition001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    float selectLineHeight = 0;
    richEditorPattern->CalcCursorOffsetByPosition(0, selectLineHeight, true, true);
    ASSERT_EQ(richEditorPattern->GetTextContentLength(), 0);
    AddSpan("hello1");
    ASSERT_NE(richEditorPattern->GetTextContentLength(), 0);
    richEditorPattern->CalcCursorOffsetByPosition(0, selectLineHeight, true, true);
    ASSERT_EQ(richEditorPattern->GetHost()->GetChildren().empty(), false);
}

/**
 * @tc.name: UpdateDecoration001
 * @tc.desc: test UpdateDecoration
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestOneNg, UpdateDecoration001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    RefPtr<SpanNode> spanNode = OHOS::Ace::NG::SpanNode::CreateSpanNode(1);
    UpdateSpanStyle updateSpanStyle;
    updateSpanStyle.updateTextDecorationStyle = TextDecorationStyle::DASHED;
    TextStyle textStyle;
    richEditorPattern->UpdateDecoration(spanNode, updateSpanStyle, textStyle);
    ASSERT_EQ(updateSpanStyle.updateTextDecoration.has_value(), false);
}

/**
 * @tc.name: UpdateImageStyle001
 * @tc.desc: test UpdateImageStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestOneNg, UpdateImageStyle001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    Dimension width = 50.0_vp;
    Dimension height = 50.0_vp;
    RefPtr<FrameNode> imageNode = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, 0, AceType::MakeRefPtr<ImagePattern>());
    ImageSpanAttribute imageStyle;
    richEditorPattern->updateSpanStyle_.updateImageWidth = std::nullopt;
    richEditorPattern->updateSpanStyle_.updateImageHeight = std::nullopt;
    richEditorPattern->UpdateImageStyle(imageNode, imageStyle);

    richEditorPattern->updateSpanStyle_.updateImageWidth = width;
    richEditorPattern->updateSpanStyle_.updateImageHeight = height;
    richEditorPattern->UpdateImageStyle(imageNode, imageStyle);

    richEditorPattern->updateSpanStyle_.updateImageWidth = width;
    richEditorPattern->updateSpanStyle_.updateImageHeight = std::nullopt;
    richEditorPattern->UpdateImageStyle(imageNode, imageStyle);

    richEditorPattern->updateSpanStyle_.updateImageWidth = std::nullopt;
    richEditorPattern->updateSpanStyle_.updateImageHeight = height;
    richEditorPattern->UpdateImageStyle(imageNode, imageStyle);
    ASSERT_EQ(richEditorPattern->updateSpanStyle_.updateImageHeight.has_value(), true);
}

/**
 * @tc.name: SymbolSpanUpdateStyle001
 * @tc.desc: test SymbolSpanUpdateStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestOneNg, SymbolSpanUpdateStyle001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto spanNode = SpanNode::GetOrCreateSpanNode(V2::SYMBOL_SPAN_ETS_TAG, 0);
    UpdateSpanStyle updateSpanStyle;
    updateSpanStyle.updateTextDecorationStyle = TextDecorationStyle::DASHED;
    TextStyle textStyle;

    bool res = richEditorPattern->SymbolSpanUpdateStyle(spanNode, updateSpanStyle, textStyle);
    ASSERT_EQ(res, true);
}

/**
 * @tc.name: CloseSystemMenu001
 * @tc.desc: test CloseSystemMenu
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestOneNg, CloseSystemMenu001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    /**
     * @tc.steps: step1. get richeditor pattern and add add text span
     */
    AddSpan("hello1");
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 6);

    /**
     * @tc.steps: step2. request focus
     */
    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    focusHub->RequestFocusImmediately();

    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);

    bool enabledCache = eventHub->IsEnabled();
    EXPECT_EQ(enabledCache, true);

    /**
     * @tc.step: step3. create a scene where the text menu has popped up
     */
    richEditorPattern->textDetectEnable_ = true;
    richEditorPattern->enabled_ = true;
    richEditorPattern->OnModifyDone();

    richEditorPattern->textDetectEnable_ = true;
    richEditorPattern->enabled_ = false;
    richEditorPattern->OnModifyDone();

    richEditorPattern->textDetectEnable_ = false;
    richEditorPattern->enabled_ = true;
    richEditorPattern->OnModifyDone();

    richEditorPattern->textDetectEnable_ = false;
    richEditorPattern->enabled_ = false;
    richEditorPattern->OnModifyDone();

    richEditorPattern->textSelector_.Update(1, 2);
    richEditorPattern->CalculateHandleOffsetAndShowOverlay();
    richEditorPattern->ShowSelectOverlay(
        richEditorPattern->textSelector_.firstHandle, richEditorPattern->textSelector_.secondHandle, false);

    richEditorPattern->CloseSystemMenu();

    EXPECT_EQ(richEditorPattern->SelectOverlayIsOn(), false);
}
} // namespace OHOS::Ace::NG