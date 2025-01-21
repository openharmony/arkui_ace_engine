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
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/base/mock_task_executor.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"

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
    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->RequestFocusImmediately();
    richEditorPattern->isEditing_ = false;
    richEditorPattern->ResetAfterPaste();
    ASSERT_NE(richEditorPattern->previewLongPress_, true);
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
    auto property = richEditorPattern->GetLayoutProperty<RichEditorLayoutProperty>();
    ASSERT_NE(property, nullptr);
    property->UpdatePreviewTextStyle("underline");
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
    auto selectType = richEditorPattern->JudgeSelectType(offset).second;
    EXPECT_NE(selectType, SelectType::SELECT_FORWARD);
    richEditorPattern->previewLongPress_ = false;
    richEditorPattern->editingLongPress_ = true;
    selectType = richEditorPattern->JudgeSelectType(offset).second;
    EXPECT_NE(selectType, SelectType::SELECT_FORWARD);
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
    std::u16string content = u"TEST123";
    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(content);

    richEditorPattern->typingStyle_ = std::nullopt;
    richEditorPattern->typingTextStyle_ = std::nullopt;
    richEditorPattern->InsertValueInStyledString(content);

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

    richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(u"abc");
    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->GetTextContentLength();

    richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(u"abc");
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
    richEditorPattern->previewTextRecord_.previewContent = u"123";
    richEditorPattern->previewTextRecord_.previewTextHasStarted = true;
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

    richEditorPattern->previewTextRecord_.previewContent = u"abc";
    richEditorPattern->previewTextRecord_.previewTextHasStarted = true;
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

/**
 * @tc.name: CreateAndShowSingleHandle001
 * @tc.desc: test CreateAndShowSingleHandle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestOneNg, CreateAndShowSingleHandle001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create richEditorPattern
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->caretPosition_ = -1;

    /**
     * @tc.steps: step2. Construct GestureEvent data and call CreatAndShowSingleHandle
     */
    ASSERT_NE(richEditorPattern->selectOverlay_, nullptr);
    richEditorPattern->previewTextRecord_.previewContent = u"abc";
    richEditorPattern->previewTextRecord_.previewTextHasStarted = true;
    richEditorPattern->previewTextRecord_.startOffset = 0;
    richEditorPattern->previewTextRecord_.endOffset = 0;
    richEditorPattern->CreateAndShowSingleHandle();
    EXPECT_FALSE(richEditorPattern->selectOverlay_->IsSingleHandle());
}

/**
 * @tc.name: MoveCaretAndStartFocus001
 * @tc.desc: test MoveCaretAndStartFocus
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestOneNg, MoveCaretAndStartFocus001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);

    Offset textOffset;
    richEditorPattern->overlayMod_ = nullptr;
    richEditorPattern->MoveCaretAndStartFocus(textOffset);
    EXPECT_TRUE(focusHub->RequestFocusImmediately());
}

/**
 * @tc.name: HandleBlurEvent001
 * @tc.desc: test HandleBlurEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestOneNg, HandleBlurEvent001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);

    auto func = []() {};

    richEditorPattern->customKeyboardBuilder_ = func;
    richEditorPattern->isCustomKeyboardAttached_ = true;
    focusHub->blurReason_ = BlurReason::FRAME_DESTROY;
    richEditorPattern->HandleBlurEvent();

    richEditorPattern->customKeyboardBuilder_ = nullptr;
    richEditorPattern->isCustomKeyboardAttached_ = true;
    focusHub->blurReason_ = BlurReason::FRAME_DESTROY;
    richEditorPattern->HandleBlurEvent();

    richEditorPattern->customKeyboardBuilder_ = func;
    richEditorPattern->isCustomKeyboardAttached_ = true;
    focusHub->blurReason_ = BlurReason::WINDOW_BLUR;
    richEditorPattern->HandleBlurEvent();

    richEditorPattern->customKeyboardBuilder_ = nullptr;
    richEditorPattern->isCustomKeyboardAttached_ = true;
    focusHub->blurReason_ = BlurReason::WINDOW_BLUR;
    richEditorPattern->HandleBlurEvent();
    EXPECT_EQ(richEditorPattern->isMoveCaretAnywhere_, false);
}

/**
 * @tc.name: HandleFocusEvent001
 * @tc.desc: test HandleFocusEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestOneNg, HandleFocusEvent001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->previewLongPress_ = true;
    richEditorPattern->HandleFocusEvent();

    richEditorPattern->previewLongPress_ = false;

    richEditorPattern->usingMouseRightButton_ = true;
    richEditorPattern->isLongPress_ = true;
    richEditorPattern->dataDetectorAdapter_->hasClickedMenuOption_ = true;
    richEditorPattern->HandleFocusEvent();

    richEditorPattern->usingMouseRightButton_ = false;
    richEditorPattern->isLongPress_ = true;
    richEditorPattern->dataDetectorAdapter_->hasClickedMenuOption_ = true;
    richEditorPattern->HandleFocusEvent();

    richEditorPattern->usingMouseRightButton_ = true;
    richEditorPattern->isLongPress_ = false;
    richEditorPattern->dataDetectorAdapter_->hasClickedMenuOption_ = true;
    richEditorPattern->HandleFocusEvent();

    richEditorPattern->usingMouseRightButton_ = true;
    richEditorPattern->isLongPress_ = true;
    richEditorPattern->dataDetectorAdapter_->hasClickedMenuOption_ = true;
    richEditorPattern->HandleFocusEvent();

    richEditorPattern->usingMouseRightButton_ = true;
    richEditorPattern->isLongPress_ = true;
    richEditorPattern->dataDetectorAdapter_->hasClickedMenuOption_ = false;
    richEditorPattern->HandleFocusEvent();

    richEditorPattern->usingMouseRightButton_ = false;
    richEditorPattern->isLongPress_ = false;
    richEditorPattern->dataDetectorAdapter_->hasClickedMenuOption_ = true;
    richEditorPattern->HandleFocusEvent();

    richEditorPattern->usingMouseRightButton_ = false;
    richEditorPattern->isLongPress_ = false;
    richEditorPattern->dataDetectorAdapter_->hasClickedMenuOption_ = true;
    richEditorPattern->HandleFocusEvent();

    richEditorPattern->usingMouseRightButton_ = false;
    richEditorPattern->isLongPress_ = false;
    richEditorPattern->dataDetectorAdapter_->hasClickedMenuOption_ = false;
    richEditorPattern->HandleFocusEvent();

    EXPECT_EQ(richEditorPattern->textSelector_.SelectNothing(), true);
}

/**
 * @tc.name: CloseKeyboard001
 * @tc.desc: test CloseKeyboard
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestOneNg, CloseKeyboard001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->CloseKeyboard(false);
    EXPECT_EQ(richEditorPattern->HasConnection(), false);
}

/**
 * @tc.name: CalculateEmptyValueCaretRect002
 * @tc.desc: test CalculateEmptyValueCaretRect
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestOneNg, CalculateEmptyValueCaretRect002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto layoutProperty = richEditorPattern->GetLayoutProperty<TextLayoutProperty>();

    layoutProperty->UpdateLayoutDirection(TextDirection::RTL);
    layoutProperty->UpdateTextAlign(TextAlign::LEFT);
    richEditorPattern->CalculateEmptyValueCaretRect();

    layoutProperty->UpdateLayoutDirection(TextDirection::INHERIT);
    layoutProperty->UpdateTextAlign(TextAlign::CENTER);
    richEditorPattern->CalculateEmptyValueCaretRect();

    layoutProperty->UpdateLayoutDirection(TextDirection::INHERIT);
    layoutProperty->UpdateTextAlign(TextAlign::LEFT);
    richEditorPattern->CalculateEmptyValueCaretRect();

    EXPECT_EQ(richEditorPattern->presetParagraph_, false);
}

/**
 * @tc.name: AdjustPlaceholderSelection001
 * @tc.desc: test AdjustPlaceholderSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestOneNg, AdjustPlaceholderSelection001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_NE(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    AddSpan(INIT_VALUE_1);
    OHOS::Ace::RefPtr<OHOS::Ace::NG::SpanItem> spanItem1 = AceType::MakeRefPtr<ImageSpanItem>();
    richEditorPattern->spans_.emplace_back(spanItem1);
    OHOS::Ace::RefPtr<OHOS::Ace::NG::SpanItem> spanItem2 = AceType::MakeRefPtr<PlaceholderSpanItem>();
    richEditorPattern->spans_.emplace_back(spanItem2);
    OHOS::Ace::RefPtr<OHOS::Ace::NG::SpanItem> spanItem3 = AceType::MakeRefPtr<PlaceholderSpanItem>();
    richEditorPattern->spans_.emplace_back(spanItem3);
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    EXPECT_CALL(*paragraph, GetHeight()).WillRepeatedly(Return(300.0f));
    EXPECT_CALL(*paragraph, GetGlyphIndexByCoordinate(_, _)).WillRepeatedly(Return(6));
    TestParagraphRect paragraphRect = { .start = 0, .end = 6, .rects = { { 10.0, 20.0, 30.0, 40.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 6, .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);
    CaretMetricsF metrics = { { 10.0f, 50.0f }, 20.0f };
    EXPECT_CALL(*paragraph, ComputeOffsetForCaretUpstream(_, _, _))
        .WillRepeatedly(DoAll(SetArgReferee<1>(metrics), Return(true)));
    EXPECT_CALL(*paragraph, ComputeOffsetForCaretDownstream(_, _, _))
        .WillRepeatedly(DoAll(SetArgReferee<1>(metrics), Return(true)));
    TestParagraphRect paragraphRectSec = { .start = 7, .end = 12, .rects = { { 40.0, 50.0, 60.0, 70.0 } } };
    TestParagraphItem paragraphItemSec = { .start = 7, .end = 12, .testParagraphRects = { paragraphRectSec } };
    AddParagraph(paragraphItemSec);
    TestParagraphRect paragraphRectThi = { .start = 13, .end = 18, .rects = { { 80.0, 90.0, 100.0, 110.0 } } };
    TestParagraphItem paragraphItemThi = { .start = 13, .end = 18, .testParagraphRects = { paragraphRectThi } };
    AddParagraph(paragraphItemThi);
    /**
     * @tc.steps: step2. change parameter and call function.
     */
    int32_t start = 8;
    int32_t end = 10;
    Offset touchPos(8.0f, 350.0f);
    richEditorPattern->AdjustPlaceholderSelection(start, end, touchPos);

    for (auto iter : richEditorPattern->spans_) {
        iter->position = start;
    }
    richEditorPattern->AdjustPlaceholderSelection(start, end, touchPos);
    EXPECT_NE(start, end);
}

/**
 * @tc.name: AddSpansAndReplacePlaceholder001
 * @tc.desc: test AddSpansAndReplacePlaceholder
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestOneNg, AddSpansAndReplacePlaceholder001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto spanString = AceType::MakeRefPtr<SpanString>(u"test![id1]");
    auto start = richEditorPattern->operationRecords_.size();
    richEditorPattern->AddSpansAndReplacePlaceholder(spanString);
    EXPECT_EQ(richEditorPattern->operationRecords_.size(), start + 2);
    richEditorPattern->ClearOperationRecords();

    spanString = AceType::MakeRefPtr<SpanString>(u"test![id2]");
    start = richEditorPattern->operationRecords_.size();
    richEditorPattern->AddSpansAndReplacePlaceholder(spanString);
    EXPECT_EQ(richEditorPattern->operationRecords_.size(), start + 2);
    richEditorPattern->ClearOperationRecords();

    richEditorPattern->placeholderSpansMap_[u"![id3]"] = nullptr;
    spanString = AceType::MakeRefPtr<SpanString>(u"test![id3]");
    start = richEditorPattern->operationRecords_.size();
    richEditorPattern->AddSpansAndReplacePlaceholder(spanString);
    EXPECT_EQ(richEditorPattern->operationRecords_.size(), start + 2);
    richEditorPattern->ClearOperationRecords();

    richEditorPattern->placeholderSpansMap_[u"![id4]"] = AceType::MakeRefPtr<SpanItem>();
    spanString = AceType::MakeRefPtr<SpanString>(u"test![id4]");
    start = richEditorPattern->operationRecords_.size();
    richEditorPattern->AddSpansAndReplacePlaceholder(spanString);
    EXPECT_EQ(richEditorPattern->operationRecords_.size(), start + 2);
    richEditorPattern->ClearOperationRecords();

    spanString = AceType::MakeRefPtr<SpanString>(u"![id5]");
    richEditorPattern->placeholderSpansMap_[u"![id5]"] = AceType::MakeRefPtr<SpanItem>();
    start = richEditorPattern->operationRecords_.size();
    richEditorPattern->AddSpansAndReplacePlaceholder(spanString);
    EXPECT_EQ(richEditorPattern->operationRecords_.size(), start + 1);
    richEditorPattern->ClearOperationRecords();

    spanString = AceType::MakeRefPtr<SpanString>(u"");
    start = richEditorPattern->operationRecords_.size();
    richEditorPattern->AddSpansAndReplacePlaceholder(spanString);
    EXPECT_EQ(richEditorPattern->operationRecords_.size(), start);
    richEditorPattern->ClearOperationRecords();
}

/**
 * @tc.name: InsertSpanByBackData001
 * @tc.desc: test InsertSpanByBackData
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestOneNg, InsertSpanByBackData001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto spanString = AceType::MakeRefPtr<SpanString>(u"");
    richEditorPattern->textSelector_ = TextSelector(0, 6);
    EXPECT_TRUE(richEditorPattern->textSelector_.IsValid());
    richEditorPattern->InsertSpanByBackData(spanString);
    EXPECT_FALSE(richEditorPattern->textSelector_.IsValid());
    richEditorPattern->ClearOperationRecords();

    richEditorPattern->placeholderSpansMap_[u"![id1]"] = AceType::MakeRefPtr<SpanItem>();
    spanString = AceType::MakeRefPtr<SpanString>(u"test![id1]");
    auto start = richEditorPattern->operationRecords_.size();
    richEditorPattern->InsertSpanByBackData(spanString);
    EXPECT_EQ(richEditorPattern->operationRecords_.size(), start + 2);
    richEditorPattern->ClearOperationRecords();
}

/**
 * @tc.name: IsShowAIWrite001
 * @tc.desc: test IsShowAIWrite
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestOneNg, IsShowAIWrite001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    TextSpanOptions options;
    options.value = INIT_VALUE_3;
    richEditorController->AddTextSpan(options);
    richEditorPattern->textSelector_.Update(0, 5);
    auto mockContainer = MockContainer::Current();
    mockContainer->SetIsScenceBoardWindow(true);
    auto result = richEditorPattern->IsShowAIWrite();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: IsShowAIWrite002
 * @tc.desc: test IsShowAIWrite
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestOneNg, IsShowAIWrite002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    TextSpanOptions options;
    options.value = INIT_VALUE_3;
    richEditorController->AddTextSpan(options);
    richEditorPattern->textSelector_.Update(0, 5);
    MockContainer::TearDown();
    auto result = richEditorPattern->IsShowAIWrite();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: IsShowAIWrite003
 * @tc.desc: test IsShowAIWrite
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestOneNg, IsShowAIWrite003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    TextSpanOptions options;
    options.value = INIT_VALUE_3;
    richEditorController->AddTextSpan(options);
    richEditorPattern->textSelector_.Update(0, 5);
    richEditorPattern->copyOption_ = CopyOptions::Local;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    PipelineBase::GetCurrentContext()->themeManager_ = themeManager;
    auto theme = AceType::MakeRefPtr<RichEditorTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));
    auto result = richEditorPattern->IsShowAIWrite();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: IsShowAIWrite004
 * @tc.desc: test IsShowAIWrite
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestOneNg, IsShowAIWrite004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    TextSpanOptions options;
    options.value = INIT_VALUE_3;
    richEditorController->AddTextSpan(options);
    richEditorPattern->textSelector_.Update(0, 5);
    richEditorPattern->copyOption_ = CopyOptions::Local;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    PipelineBase::GetCurrentContext()->themeManager_ = themeManager;
    auto theme = AceType::MakeRefPtr<RichEditorTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    theme->aiWriteBundleName_ = "bundleName";
    auto result = richEditorPattern->IsShowAIWrite();
    EXPECT_EQ("", richEditorPattern->aiWriteAdapter_->GetBundleName());
    EXPECT_FALSE(result);
}

/**
 * @tc.name: IsShowAIWrite005
 * @tc.desc: test IsShowAIWrite
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestOneNg, IsShowAIWrite005, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    TextSpanOptions options;
    options.value = INIT_VALUE_3;
    richEditorController->AddTextSpan(options);
    richEditorPattern->textSelector_.Update(0, 5);
    richEditorPattern->copyOption_ = CopyOptions::Local;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    PipelineBase::GetCurrentContext()->themeManager_ = themeManager;
    auto theme = AceType::MakeRefPtr<RichEditorTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    theme->aiWriteBundleName_ = "bundleName";
    theme->aiWriteAbilityName_ = "abilityName";
    auto result = richEditorPattern->IsShowAIWrite();
    EXPECT_EQ("bundleName", richEditorPattern->aiWriteAdapter_->GetBundleName());
    EXPECT_EQ("abilityName", richEditorPattern->aiWriteAdapter_->GetAbilityName());
    EXPECT_FALSE(result);
}

/**
 * @tc.name: IsShowAIWrite006
 * @tc.desc: test IsShowAIWrite
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestOneNg, IsShowAIWrite006, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    TextSpanOptions options;
    options.value = INIT_VALUE_3;
    richEditorController->AddTextSpan(options);
    richEditorPattern->textSelector_.Update(0, 5);
    richEditorPattern->copyOption_ = CopyOptions::Local;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    PipelineBase::GetCurrentContext()->themeManager_ = themeManager;
    auto theme = AceType::MakeRefPtr<RichEditorTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    theme->aiWriteBundleName_ = "bundleName";
    theme->aiWriteAbilityName_ = "abilityName";
    theme->aiWriteIsSupport_ = "true";
    auto result = richEditorPattern->IsShowAIWrite();
    EXPECT_EQ("bundleName", richEditorPattern->aiWriteAdapter_->GetBundleName());
    EXPECT_EQ("abilityName", richEditorPattern->aiWriteAdapter_->GetAbilityName());
    EXPECT_TRUE(result);
}

/**
 * @tc.name: IsMenuItemShow001
 * @tc.desc: test IsMenuItemShow
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestOneNg, IsMenuItemShow001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    PipelineBase::GetCurrentContext()->themeManager_ = themeManager;
    auto theme = AceType::MakeRefPtr<RichEditorTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    theme->searchIsSupport_ = true;
    theme->translateIsSupport_ = true;

    auto showSearch = richEditorPattern->IsShowSearch();
    EXPECT_TRUE(showSearch);
    auto showTranslate = richEditorPattern->IsShowTranslate();
    EXPECT_TRUE(showTranslate);
}

/**
 * @tc.name: IsMenuItemShow002
 * @tc.desc: test menu search and translate item
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestOneNg, IsMenuItemShow002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    /**
     * @tc.steps: step1. searchIsSupport_ set to true.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    PipelineBase::GetCurrentContext()->themeManager_ = themeManager;
    auto theme = AceType::MakeRefPtr<RichEditorTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    theme->searchIsSupport_ = true;
    auto showSearch = richEditorPattern->IsShowSearch();
    EXPECT_TRUE(showSearch);
    theme->translateIsSupport_ = true;
    auto showTranslate = richEditorPattern->IsShowTranslate();
    EXPECT_TRUE(showTranslate);

    auto selectOverlay = richEditorPattern->selectOverlay_;
    ASSERT_NE(selectOverlay, nullptr);

    /**
     * @tc.steps: step2. add text\image\symbol.
     */
    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    richEditorController->AddTextSpan(options);
    AddImageSpan();
    richEditorPattern->AddSymbolSpan(SYMBOL_SPAN_OPTIONS_1);

    /**
     * @tc.steps: step3. select text.
     */
    richEditorPattern->textSelector_.Update(0, 6);
    richEditorPattern->copyOption_ = CopyOptions::Local;
    SelectMenuInfo menuInfo;
    selectOverlay->OnUpdateMenuInfo(menuInfo, DIRTY_ALL_MENU_ITEM);
    ASSERT_EQ(menuInfo.showSearch, true);
    ASSERT_EQ(menuInfo.showTranslate, true);

    /**
     * @tc.steps: step4. select image.
     */
    richEditorPattern->textSelector_.Update(6, 7);
    selectOverlay->OnUpdateMenuInfo(menuInfo, DIRTY_ALL_MENU_ITEM);
    ASSERT_EQ(menuInfo.showSearch, false);
    ASSERT_EQ(menuInfo.showTranslate, false);

    /**
     * @tc.steps: step5. select symbol.
     */
    richEditorPattern->textSelector_.Update(7, 8);
    selectOverlay->OnUpdateMenuInfo(menuInfo, DIRTY_ALL_MENU_ITEM);
    ASSERT_EQ(menuInfo.showSearch, false);
    ASSERT_EQ(menuInfo.showTranslate, false);

    /**
     * @tc.steps: step6. mixed selection.
     */
    richEditorPattern->textSelector_.Update(0, 8);
    selectOverlay->OnUpdateMenuInfo(menuInfo, DIRTY_ALL_MENU_ITEM);
    ASSERT_EQ(menuInfo.showSearch, true);
    ASSERT_EQ(menuInfo.showTranslate, true);
}

/**
 * @tc.name: GetAIWriteInfo001
 * @tc.desc: test GetAIWriteInfo
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestOneNg, GetAIWriteInfo001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    TextSpanOptions options;
    options.value = INIT_VALUE_3;
    richEditorController->AddTextSpan(options);
    richEditorPattern->textSelector_.Update(0, 5);
    richEditorPattern->textForDisplay_ = u"testtesttest";
    AIWriteInfo info;
    richEditorPattern->GetAIWriteInfo(info);
    EXPECT_EQ(info.selectStart, 0);
    EXPECT_EQ(info.selectEnd, 5);
    EXPECT_EQ(info.selectLength, 5);
    EXPECT_EQ(info.firstHandle, richEditorPattern->textSelector_.firstHandle.ToString());
    EXPECT_EQ(info.secondHandle, richEditorPattern->textSelector_.secondHandle.ToString());
    RefPtr<SpanString> spanString = SpanString::DecodeTlv(info.selectBuffer);
    ASSERT_NE(spanString, nullptr);
    auto textContent = spanString->GetString();
    EXPECT_EQ(textContent.empty(), false);
}

/**
 * @tc.name: AIDeleteComb001
 * @tc.desc: test AIDeleteComb
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestOneNg, AIDeleteComb001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto spanString = AceType::MakeRefPtr<SpanString>(u"");
    richEditorPattern->textSelector_ = TextSelector(0, 6);
    EXPECT_TRUE(richEditorPattern->textSelector_.IsValid());
    richEditorPattern->InsertSpanByBackData(spanString);
    EXPECT_FALSE(richEditorPattern->textSelector_.IsValid());
    richEditorPattern->ClearOperationRecords();

    richEditorPattern->placeholderSpansMap_[u"![id1]"] = AceType::MakeRefPtr<SpanItem>();
    spanString = AceType::MakeRefPtr<SpanString>(u"test![id1]");
    auto start = richEditorPattern->operationRecords_.size();
    richEditorPattern->InsertSpanByBackData(spanString);
    EXPECT_EQ(richEditorPattern->operationRecords_.size(), start + 2);
    richEditorPattern->ClearOperationRecords();
}

/**
 * @tc.name: HandleOnDeleteComb001
 * @tc.desc: test HandleOnDeleteComb
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestOneNg, HandleOnDeleteComb001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    spanItem->rangeStart = 2;
    spanItem->position = 10;
    spanItem->unicode = 1;
    richEditorPattern->spans_.push_back(spanItem);
    richEditorPattern->caretPosition_ = 6;
    auto ret = richEditorPattern->HandleOnDeleteComb(true);
    EXPECT_TRUE(ret);
}
} // namespace OHOS::Ace::NG