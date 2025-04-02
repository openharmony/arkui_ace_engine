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
    EXPECT_EQ(richEditorPattern->isEditing_, false);
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
 * @tc.name: HandleOnShare001
 * @tc.desc: test rich_editor_select_overlay.cpp HandleOnShare function
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestOneNg, HandleOnShare001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);

    richEditorPattern->HandleOnShare();
    auto value = richEditorPattern->selectOverlay_->GetSelectedText();
    int32_t ret = value.length();
    EXPECT_EQ(ret, 0);
}
} // namespace OHOS::Ace::NG