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

#include "text_base.h"

#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_paragraph.h"

#include "core/components/common/properties/text_style_parser.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/text/text_model_ng.h"


namespace OHOS::Ace::NG {

namespace {
const std::list<std::pair<std::string, int32_t>> FONT_FEATURE_VALUE_1 = ParseFontFeatureSettings("\"ss01\" 1");
} // namespace

class TextTestNgNine : public TextBases {
public:
};

/*
 * @tc.name: TextModelSetFont001
 * @tc.desc: Test if SetFont is successful
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgNine, TextModelSetFont001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textModelNG and FrameNode
     */
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE_W);
    Font font;
    font.fontSize = FONT_SIZE_VALUE;
    font.fontWeight = FontWeight::BOLD;
    font.fontFamilies = FONT_FAMILY_VALUE;
    font.fontStyle = ITALIC_FONT_STYLE_VALUE;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    auto textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. call SetFont and Gets the relevant properties of the Font
     * @tc.expected: step2. Check the font value
     */
    textModelNG.SetFont(font);
    EXPECT_EQ(textLayoutProperty->GetFontSize(), FONT_SIZE_VALUE);
    EXPECT_EQ(textLayoutProperty->GetFontWeight().value(), FontWeight::BOLD);
    EXPECT_EQ(textLayoutProperty->GetFontFamily(), FONT_FAMILY_VALUE);
    EXPECT_EQ(textLayoutProperty->GetItalicFontStyle(), ITALIC_FONT_STYLE_VALUE);
}

/**
 * @tc.name: TextModelGetFontInJson001
 * @tc.desc: Test if GetFontInJson is successful
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgNine, TextModelGetFontInJson001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textModelNG and FrameNode
     */
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE_W);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. not set and Gets the relevant properties of the Font
     * @tc.expected: step2. Check the font value
     */
    auto context = frameNode->GetContextRefPtr();
    ASSERT_NE(context, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    context->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextTheme>()));
    EXPECT_EQ(pattern->GetFontInJson(), WITH_THEME_CALL_TEXT_DEFAULT_VALUE);

    /**
     * @tc.steps: step2. call SetFont and Gets the relevant properties of the Font
     * @tc.expected: step2. Check the font value
     */
    Font font;
    font.fontSize = FONT_SIZE_VALUE;
    font.fontWeight = FontWeight::BOLD;
    font.fontFamilies = FONT_FAMILY_VALUE;
    font.fontStyle = ITALIC_FONT_STYLE_VALUE;
    textModelNG.SetFont(font);
    EXPECT_EQ(pattern->GetFontInJson(), TEXT_EQUALS_VALUE);
}

/**
 * @tc.name: BetweenSelectedPosition001
 * @tc.desc: test text_pattern.cpp BetweenSelectedPosition function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgNine, BetweenSelectedPosition001, TestSize.Level1)
{
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    std::vector<RectF> rects { RectF(0, 0, 20, 20) };
    EXPECT_CALL(*paragraph, GetRectsForRange(_, _, _)).WillRepeatedly(SetArgReferee<2>(rects));
    /**
     * @tc.steps: step1. create frameNode and pattern and some environment for running process.
     */
    auto [host, pattern] = Init();
    pattern->copyOption_ = CopyOptions::Distributed;
    host->draggable_ = true;
    host->GetEventHub<EventHub>()->SetOnDragStart(
        [](const RefPtr<Ace::DragEvent>&, const std::string&) -> DragDropInfo { return {}; });

    /**
     * @tc.steps: step2. set selected rect to [0, 0] - [20, 20]
     */
    pattern->textSelector_.Update(0, 20);
    pattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 100 });

    /**
     * @tc.steps: step3. construct 3 groups cases and corresponding expected results.
     * @tc.expected: Running the BetweenSelectedPosition function and check the result with expected results.
     */
    std::vector<Offset> cases = { Offset(1, 1), Offset(21, 21) };
    std::vector<bool> exceptResults = { true, false };
    for (uint32_t turn = 0; turn < cases.size(); ++turn) {
        EXPECT_EQ(pattern->BetweenSelectedPosition(cases[turn]), exceptResults[turn]);
    }
    pattern->pManager_->Reset();
}

/**
 * @tc.name: OnHandleMove002
 * @tc.desc: test text_pattern.cpp OnHandleMove function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgNine, OnHandleMove002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern and some environment for running process.
     */
    auto [host, pattern] = Init();
    auto pipeline = PipelineContext::GetCurrentContext();
    SelectOverlayInfo selectOverlayInfo;
    selectOverlayInfo.singleLineHeight = NODE_ID;
    auto root = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto selectOverlayManager = AceType::MakeRefPtr<SelectOverlayManager>(root);
    auto proxy = selectOverlayManager->CreateAndShowSelectOverlay(selectOverlayInfo, nullptr);
    pattern->selectOverlayProxy_ = proxy;
    pipeline->rootNode_->GetGeometryNode()->SetFrameOffset({ 3.0, 5.0 });

    /**
     * @tc.steps: step3. construct 3 groups cases and corresponding expected results.
     * @tc.expected: Running the OnHandleMove function and check the result with expected results.
     */
    std::vector<RectF> handleRects = { { 1.0, 2.0, 3.0, 4.0 }, { 5.0, 6.0, 7.0, 8.0 }, { -9.0, -10.0, 11.0, 12.0 } };
    std::vector<vector<TextSelector>> expectResults = { { TextSelector(0, -1), TextSelector(0, 0) },
        { TextSelector(0, 0), TextSelector(0, 0) }, { TextSelector(0, 0), TextSelector(0, 0) } };
    for (uint32_t turn = 0; turn < handleRects.size(); ++turn) {
        pattern->OnHandleMove(handleRects[turn], true);
        EXPECT_EQ(pattern->textSelector_, expectResults[turn][0]);
        pattern->OnHandleMove(handleRects[turn], false);
        EXPECT_EQ(pattern->textSelector_, expectResults[turn][1]);
    }
}

/**
 * @tc.name: GetGlobalOffset001
 * @tc.desc: test text_pattern.cpp GetGlobalOffset function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgNine, GetGlobalOffset001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern and some environment for running process.
     */
    auto [host, pattern] = Init();
    auto pipeline = PipelineContext::GetCurrentContext();

    /**
     * @tc.steps: step3. construct 3 groups cases and corresponding expected results.
     * @tc.expected: Running GetGlobalOffset function and check the result with expected results.
     */
    std::vector<OffsetF> offsetCases = { { 3.0, 5.0 }, { 4.0, 5.0 }, { 6.0, 7.0 } };
    std::vector<Offset> expectResults = { { -3.0, -5.0 }, { -4.0, -5.0 }, { -6.0, -7.0 } };
    for (uint32_t turn = 0; turn < offsetCases.size(); ++turn) {
        pipeline->rootNode_->GetGeometryNode()->SetFrameOffset(offsetCases[turn]);
        Offset tmp;
        pattern->GetGlobalOffset(tmp);
        EXPECT_EQ(tmp, expectResults[turn]);
    }
}

/**
 * @tc.name: ApplyIndents002
 * @tc.desc: test text_layout_algorithm.cpp ApplyIndents function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgNine, ApplyIndents002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern and some environment for running process.
     */
    auto [host, pattern] = Init();
    auto rowLayoutAlgorithm = AceType::DynamicCast<TextLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());

    /**
     * @tc.steps: step2. construct textStyle with TextIndent 5.
     */
    TextStyle textStyle;
    textStyle.SetTextIndent(Dimension(5));
    rowLayoutAlgorithm->CreateParagraph(textStyle, u"This is a test.", AceType::RawPtr(host));

    /**
     * @tc.steps: step3. run the ApplyIndents Func.
     * @tc.expected: paragraph_.rawPtr_ is nullptr.
     */
    EXPECT_NE(rowLayoutAlgorithm->paragraphManager_->GetParagraphs().front().paragraph, nullptr);
}

/**
 * @tc.name: ApplyIndents003
 * @tc.desc: test text_layout_algorithm.cpp ApplyIndents function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgNine, ApplyIndents003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern and some environment for running process.
     */
    auto [host, pattern] = Init();
    auto rowLayoutAlgorithm = AceType::DynamicCast<TextLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());

    /**
     * @tc.steps: step2. construct textStyle with TextIndent 5 and type is DimensionUnit::PERCENT.
     */
    TextStyle textStyle;
    textStyle.SetTextIndent(Dimension(5, DimensionUnit::PERCENT));
    rowLayoutAlgorithm->CreateParagraph(textStyle, u"This is a test.", AceType::RawPtr(host));

    /**
     * @tc.steps: step3. run the ApplyIndents Func.
     * @tc.expected: paragraph_.rawPtr_ is nullptr.
     */
    EXPECT_NE(rowLayoutAlgorithm->paragraphManager_->GetParagraphs().front().paragraph.rawPtr_, nullptr);
}

/**
 * @tc.name: ClearOnClick001
 * @tc.desc: test text_model_ng.cpp ClearOnClick function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgNine, ClearOnClick001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern and some environment for running process.
     */
    auto [host, pattern] = Init();
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE_W);

    /**
     * @tc.steps: step2. Running ClearOnClick function.
     * @tc.expected: the onClick_ will be nullptr.
     */
    textModelNG.ClearOnClick();
    EXPECT_EQ(pattern->onClick_, nullptr);
}

/**
 * @tc.name: SetFontSize001
 * @tc.desc: test text_model_ng.cpp SetFontSize function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgNine, SetFontSize001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern and some environment for running process.
     */
    auto [host, pattern] = Init();
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE_W);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();

    /**
     * @tc.steps: step2. Run SetFontSize with isvalid data.
     * @tc.expected: the fontsize will be Dimension(0).
     */
    textModelNG.SetFontSize(Dimension(-1));
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<TextLayoutProperty> textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);
    const std::unique_ptr<FontStyle>& fontStyle = textLayoutProperty->GetFontStyle();
    ASSERT_NE(fontStyle, nullptr);
    EXPECT_EQ(fontStyle->GetFontSize().value(), Dimension(0));
}

/**
 * @tc.name: SetTextCaretColor001
 * @tc.desc: test text_model_ng.cpp SetTextCaretColor function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgNine, SetTextCaretColor001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern and some environment for running process.
     */
    auto [host, pattern] = Init();
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE_W);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();

    /**
     * @tc.steps: step2. Run SetTextCaretColor with black color.
     * @tc.expected: the caretColor will be Color::BLACK.
     */
    textModelNG.SetTextCaretColor(Color::BLACK);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<TextLayoutProperty> textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);
    std::optional<Color> cursorColor = textLayoutProperty->GetCursorColorValue(Color::BLACK);
    ASSERT_NE(cursorColor, std::nullopt);
    EXPECT_EQ(cursorColor.value(), Color::BLACK);
}

/**
 * @tc.name: SetSelectedBackgroundColor001
 * @tc.desc: test text_model_ng.cpp SetSelectedBackgroundColor function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgNine, SetSelectedBackgroundColor001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern and some environment for running process.
     */
    auto [host, pattern] = Init();
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE_W);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();

    /**
     * @tc.steps: step2. Run SetSelectedBackgroundColor with black color.
     * @tc.expected: the selectedBackgroundColor will be Color::BLACK.
     */
    textModelNG.SetSelectedBackgroundColor(Color::BLACK);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<TextLayoutProperty> textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);
    std::optional<Color> selectedBackgroundColor = textLayoutProperty->GetSelectedBackgroundColorValue(Color::BLACK);
    ASSERT_NE(selectedBackgroundColor, std::nullopt);
    EXPECT_EQ(selectedBackgroundColor.value(), Color::BLACK);
}

/**
 * @tc.name: GetLineCount001
 * @tc.desc: test text_layout_algorithm.cpp GetLineCount function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgNine, GetLineCount001, TestSize.Level1)
{
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, AddText);
    EXPECT_CALL(*paragraph, GetLineCount).WillOnce(Return(1));
    /**
     * @tc.steps: step1. create frameNode and pattern and some environment for running process.
     */
    auto [frameNode, pattern] = Init();
    auto pipeline = frameNode->GetContextRefPtr();

    /**
     * @tc.steps: step2. Create Paragraph
     */
    auto rowLayoutAlgorithm = AceType::DynamicCast<TextLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    TextStyle textStyle;
    LayoutConstraintF contentConstraint;
    rowLayoutAlgorithm->CreateParagraph(textStyle, u"This is a test.", AceType::RawPtr(frameNode));

    /**
     * @tc.steps: step3. GetLineCount.
     * @tc.expected: linecount will be 1.
     */
    EXPECT_EQ(rowLayoutAlgorithm->GetLineCount(), 1);
}

/**
 * @tc.name: GetDragUpperLeftCoordinates001
 * @tc.desc: test text_layout_algorithm.cpp GetDragUpperLeftCoordinates function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgNine, GetDragUpperLeftCoordinates001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern and some environment for running process.
     */
    auto [frameNode, pattern] = Init();
    auto pipeline = frameNode->GetContextRefPtr();

    /**
     * @tc.steps: step3. run GetDragUpperLeftCoordinates func.
     */
    auto ret = pattern->GetDragUpperLeftCoordinates();
    EXPECT_EQ(ret, OffsetF(0, 0));

    pattern->dragBoxes_.push_back({});
    ret = pattern->GetDragUpperLeftCoordinates();
    EXPECT_EQ(ret, OffsetF(0, 0));

    pattern->dragBoxes_.push_back({ 1, 2, 3, 4 });
    ret = pattern->GetDragUpperLeftCoordinates();
    EXPECT_EQ(ret, OffsetF(0, 0));
}

/**
 * @tc.name: OnColorConfigurationUpdate001
 * @tc.desc: test on color configuration update
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgNine, OnColorConfigurationUpdate001, TestSize.Level1)
{
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto context = textFrameNode->GetContextRefPtr();
    ASSERT_NE(context, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    context->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextTheme>()));
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    textLayoutProperty->UpdateTextColorByRender(Color::BLACK);
    textPattern->OnColorConfigurationUpdate();
    EXPECT_EQ(textLayoutProperty->GetTextColor(), Color::BLACK);
}

/**
 * @tc.name: GetCopyOptionString001
 * @tc.desc: Test if GetCopyOptionString is successful
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgNine, GetCopyOptionString001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textModelNG and FrameNode
     */
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE_W);
    auto [frameNode, pattern] = Init();
    auto pipeline = frameNode->GetContextRefPtr();
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    auto textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. run GetCopyOptionString Func.
     */
    textLayoutProperty->UpdateCopyOption(CopyOptions::InApp);
    EXPECT_EQ(textLayoutProperty->GetCopyOptionString(), "CopyOptions.InApp");
    textLayoutProperty->UpdateCopyOption(CopyOptions::Local);
    EXPECT_EQ(textLayoutProperty->GetCopyOptionString(), "CopyOptions.Local");
    textLayoutProperty->UpdateCopyOption(CopyOptions::None);
    EXPECT_EQ(textLayoutProperty->GetCopyOptionString(), "CopyOptions.None");
    textLayoutProperty->UpdateCopyOption(CopyOptions::Distributed);
    EXPECT_EQ(textLayoutProperty->GetCopyOptionString(), "CopyOptions.Distributed");
    textLayoutProperty->UpdateCopyOption(CopyOptions(10));
    EXPECT_EQ(textLayoutProperty->GetCopyOptionString(), "CopyOptions.None");
}

/**
 * @tc.name: HandleTouchEvent001
 * @tc.desc: test test_pattern.h HandleTouchEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgNine, HandleTouchEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();

    /**
     * @tc.steps: step2. construct spanItemChildren
     */
    std::list<RefPtr<SpanItem>> spanItemChildren;
    auto spanItemChild1 = AceType::MakeRefPtr<SpanItem>();
    spanItemChildren.emplace_back(spanItemChild1);
    pattern->spans_ = spanItemChildren;

    /**
     * @tc.steps: step3. create paragraph
     */
    ParagraphStyle paragraphStyle;
    RefPtr<Paragraph> paragraph = Paragraph::Create(paragraphStyle, FontCollection::Current());
    ASSERT_NE(paragraph, nullptr);
    pattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 100 });

    /**
     * @tc.steps: step4. create GestureEvent and call HandleTouchEvent.
     * @tc.expected: function run rightly
     */
    pattern->textSelector_.Update(-2, -2);
    TouchEventInfo touchEventInfo = TouchEventInfo("touch");
    TouchLocationInfo touchLocationInfo = TouchLocationInfo(1);
    touchLocationInfo.SetLocalLocation(Offset(0, 0));
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    touchEventInfo.AddTouchLocationInfo(std::move(touchLocationInfo));

    pattern->HandleTouchEvent(touchEventInfo);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), -2);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), -2);
    pattern->pManager_->Reset();
}

/**
 * @tc.name: HandleDoubleClickEvent001
 * @tc.desc: test test_pattern.h HandleDoubleClickEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgNine, HandleDoubleClickEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();

    /**
     * @tc.steps: step2. construct spanItemChildren
     */
    std::list<RefPtr<SpanItem>> spanItemChildren;
    auto spanItemChild1 = AceType::MakeRefPtr<SpanItem>();
    spanItemChildren.emplace_back(spanItemChild1);
    pattern->spans_ = spanItemChildren;

    /**
     * @tc.steps: step3. create paragraph
     */
    ParagraphStyle paragraphStyle;
    RefPtr<Paragraph> paragraph = Paragraph::Create(paragraphStyle, FontCollection::Current());
    ASSERT_NE(paragraph, nullptr);
    pattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 100 });
    auto makeEvent = [](GestureEvent& info, bool first) {
        info.localLocation_ = Offset(0, first ? 0 : 10);
        info.globalLocation_ = info.localLocation_;
        TimeStamp timeStamp(std::chrono::nanoseconds(first ? 0 : 3000));
        info.SetTimeStamp(timeStamp);
    };

    /**
     * @tc.steps: step4. create GestureEvent and call HandleClickEvent function quickly to trigger doubleClick.
     * @tc.expected: function run rightly
     */
    pattern->textSelector_.Update(-2, -2);
    GestureEvent info;
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>(true);
    // test CopyOptions is None
    pattern->copyOption_ = CopyOptions::None;
    pattern->isDoubleClick_ = false;
    makeEvent(info, true);
    pattern->HandleClickEvent(info);
    EXPECT_TRUE(pattern->multipleClickRecognizer_->IsRunning());
    makeEvent(info, false);
    pattern->HandleClickEvent(info);
    EXPECT_FALSE(pattern->isDoubleClick_);

    // test mouse doubleClick
    pattern->isMousePressed_ = true;
    pattern->copyOption_ = CopyOptions::Local;
    pattern->isDoubleClick_ = false;
    makeEvent(info, true);
    pattern->HandleClickEvent(info);
    EXPECT_TRUE(pattern->multipleClickRecognizer_->IsRunning());
    makeEvent(info, false);
    pattern->textForDisplay_ = u"ABC";
    pattern->HandleClickEvent(info);
    EXPECT_TRUE(pattern->isDoubleClick_);

    // test gesture doubleClick
    pattern->isMousePressed_ = false;
    pattern->copyOption_ = CopyOptions::Local;
    pattern->isDoubleClick_ = false;
    makeEvent(info, true);
    pattern->HandleClickEvent(info);
    EXPECT_TRUE(pattern->multipleClickRecognizer_->IsRunning());
    makeEvent(info, false);
    pattern->HandleClickEvent(info);
    EXPECT_TRUE(pattern->isDoubleClick_);
    pattern->pManager_->Reset();
}

/**
 * @tc.name: HandleDoubleClickEvent002
 * @tc.desc: test test_pattern.h HandleDoubleClickEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgNine, HandleDoubleClickEvent002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern without any spanNodes.
     */
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE_W);
    textModelNG.SetCopyOption(CopyOptions::Local);
    std::function<void()> buildFunc = []() {};
    SelectMenuParam memuParam { .onAppear = [](int32_t, int32_t) {}, .onDisappear = []() {} };
    TextSpanType textSpanType = TextSpanType::TEXT;
    TextResponseType textResponseType = TextResponseType::LONG_PRESS;
    textModelNG.BindSelectionMenu(textSpanType, textResponseType, buildFunc, memuParam);
    auto spanNode = CreateSpanNodeWithSetDefaultProperty(u"Hello World");
    auto host = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    host->AddChild(spanNode);
    spanNode->SetParent(host);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    frameNode->Measure(LayoutConstraintF());

    /**
     * @tc.steps: step2. test Gesture double click.
     * @tc.expected: expect pattern isDoubleClick_ true, textResponseType_ NONE, textSelector valid,
     *     showOverlay selectInfo string not empty.
     */
    auto pattern = frameNode->GetPattern<TextPattern>();
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    pattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 100 });
    EXPECT_CALL(*paragraph, GetWordBoundary(_, _, _))
        .WillRepeatedly(DoAll(SetArgReferee<1>(0), SetArgReferee<2>(5), Return(true)));

    pattern->isMousePressed_ = false;
    GestureEvent info;
    info.localLocation_ = Offset(0, 0);
    info.globalLocation_ = Offset(0, 0);
    TimeStamp timeStamp(std::chrono::nanoseconds(0));
    info.SetTimeStamp(timeStamp);
    pattern->HandleClickEvent(info);
    info.localLocation_ = Offset(0, 10);
    info.globalLocation_ = Offset(0, 10);
    TimeStamp timeStamp0(std::chrono::nanoseconds(3000));
    info.SetTimeStamp(timeStamp0);
    pattern->HandleClickEvent(info);
    EXPECT_TRUE(pattern->isDoubleClick_);
    EXPECT_EQ(pattern->textResponseType_, TextResponseType::NONE);
    EXPECT_TRUE(pattern->textSelector_.IsValid());
    EXPECT_TRUE(pattern->selectOverlay_->SelectOverlayIsOn());
    pattern->pManager_->Reset();
}

/**
 * @tc.name: HandleClickEventTest001
 * @tc.desc: test test_pattern.h HandleClickEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgNine, HandleClickEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern with two  child spanNodes.
     */
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE_W);
    textModelNG.SetCopyOption(CopyOptions::Local);
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto pattern = host->GetPattern<TextPattern>();
    bool isSpanPhoneClicked = false;
    auto spanNode = CreateSpanNodeWithSetDefaultProperty(SPAN_PHONE_U16);
    spanNode->UpdateOnClickEvent([&isSpanPhoneClicked](GestureEvent& info) { isSpanPhoneClicked = true; });
    host->AddChild(spanNode);
    spanNode = CreateSpanNodeWithSetDefaultProperty(SPAN_URL_U16);
    host->AddChild(spanNode);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    frameNode->GetRenderContext()->UpdateClipEdge(false);

    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    std::vector<RectF> rects { RectF(0, 0, 20, 20), RectF(30, 30, 20, 20) };
    EXPECT_CALL(*paragraph, GetRectsForRange(_, _, _)).WillRepeatedly(SetArgReferee<2>(rects));
    EXPECT_CALL(*paragraph, GetLongestLine).WillRepeatedly(Return(100.f));
    EXPECT_CALL(*paragraph, GetHeight).WillRepeatedly(Return(100.f));
    pattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 100 });
    //set text component frame size [180, 60].
    LayoutConstraintF layoutConstraintF { .selfIdealSize = OptionalSizeF(180.f, 60.f) };
    frameNode->Measure(layoutConstraintF);
    //set boundsRect (0.00, 0.00) - [180.00 x 100.00]
    pattern->CreateNodePaintMethod();
    pattern->textSelector_.Update(0, 20);

    /**
     * @tc.steps: step2. Test HandleClickEvent.
     * @tc.expect: expect click event captured by spanNode, onClickEvent will be called,
     *     reset pattern textSelector.
     */
    GestureEvent info;
    // info location in region boundsRect.
    info.localLocation_ = Offset(10, 10);
    pattern->HandleClickEvent(info);
    EXPECT_TRUE(isSpanPhoneClicked);
    EXPECT_TRUE(!pattern->textSelector_.IsValid());
    pattern->pManager_->Reset();
}

/**
 * @tc.name: UpdateAIMenuOptions
 * @tc.desc: test test_pattern.h UpdateAIMenuOptions function with valid textSelector
 *           check multi ai entity in selection range
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgNine, UpdateAIMenuOptions001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and text textPattern
     */
    auto [frameNode, textPattern] = Init();
    textPattern->textSelector_.Update(0, 42);

    /**
     * @tc.steps: step2. prepare spanItem with at least 2 ai entity
     */
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    spanItem->content = std::get<std::u16string>(U16_TEXT_FOR_AI_INFO_2.content);
    spanItem->position = spanItem->content.length();
    textPattern->spans_.emplace_back(spanItem);

    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    std::vector<RectF> selectedRects { RectF(0, 0, 20, 20), RectF(30, 30, 20, 20), RectF(60, 60, 20, 20) };
    EXPECT_CALL(*paragraph, GetRectsForPlaceholders(_)).WillRepeatedly(SetArgReferee<0>(selectedRects));
    textPattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 100 });

    textPattern->SetTextDetectEnable(true);
    textPattern->copyOption_ = CopyOptions::InApp;

    auto aiSpan1 = U16_TEXT_FOR_AI_INFO_2.aiSpans[0];
    auto aiSpan2 = U16_TEXT_FOR_AI_INFO_2.aiSpans[1];
    std::map<int32_t, Ace::AISpan> aiSpanMap;
    aiSpanMap[aiSpan1.start] = aiSpan1;
    aiSpanMap[aiSpan2.start] = aiSpan2;
    textPattern->dataDetectorAdapter_->aiSpanMap_ = aiSpanMap;
    textPattern->textDetectEnable_ = true;
    textPattern->enabled_ = true;

    /**
     * @tc.steps: step3. create GestureEvent and call PrepareAIMenuOptions function.
     * @tc.expected: aiMenuOptions is been setted true.
     */
    textPattern->UpdateAIMenuOptions();
    EXPECT_EQ(textPattern->isAskCeliaEnabled_, false);
    EXPECT_EQ(textPattern->isShowAIMenuOption_, false);
    textPattern->pManager_->Reset();

    /**
     * @tc.steps: step4. unexpected input set 1.
     * @tc.expected: aiMenuOptions is been setted true.
     */
    textPattern->textSelector_.Update(-10, -42);
    textPattern->UpdateAIMenuOptions();
    EXPECT_EQ(textPattern->isAskCeliaEnabled_, false);
    EXPECT_EQ(textPattern->isShowAIMenuOption_, false);
    textPattern->pManager_->Reset();

    /**
     * @tc.steps: step5. unexpected input set 2.
     * @tc.expected: aiMenuOptions is been setted true.
     */
    textPattern->textSelector_.Update(42, 0);
    textPattern->UpdateAIMenuOptions();
    EXPECT_EQ(textPattern->isAskCeliaEnabled_, false);
    EXPECT_EQ(textPattern->isShowAIMenuOption_, false);
    textPattern->pManager_->Reset();
}

/**
 * @tc.name: IsNeedAskCelia
 * @tc.desc: test test_pattern.h IsNeedAskCelia function with valid textSelector
 *           check multi ai entity in selection range
 * @tc.type: FUNC
 */
 HWTEST_F(TextTestNgNine, IsNeedAskCelia001, TestSize.Level1)
 {
     /**
      * @tc.steps: step1. create frameNode and text textPattern
      */
     auto [frameNode, textPattern] = Init();
     EXPECT_FALSE(textPattern->IsNeedAskCelia());
 }

/**
 * @tc.name: SetTextSelection001
 * @tc.desc: test test_pattern.h SetTextSelection function.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgNine, SetTextSelection001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE_W);

    /**
     * @tc.steps: step2. call SetTextSelection with CopyOptions::None
     * @tc.expected: not selected
     */
    textModelNG.SetTextSelection(0, 4);
    EXPECT_EQ(pattern->textSelector_.GetStart(), -1);
    EXPECT_EQ(pattern->textSelector_.GetEnd(), -1);

    /**
     * @tc.steps: step3. Get LayoutProperty and update CopyOption
     * @tc.expected: textSelector_ updated successfully
     */
    auto textLayoutProperty = pattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    textLayoutProperty->UpdateTextOverflow(TextOverflow::MARQUEE);
    pattern->SetTextSelection(0, 4);
    EXPECT_EQ(pattern->textSelector_.GetStart(), -1);
    EXPECT_EQ(pattern->textSelector_.GetEnd(), -1);
    textLayoutProperty->UpdateCopyOption(CopyOptions::InApp);
    pattern->SetTextSelection(0, 4);
    EXPECT_EQ(pattern->textSelector_.GetStart(), -1);
    EXPECT_EQ(pattern->textSelector_.GetEnd(), -1);
    textLayoutProperty->UpdateTextOverflow(TextOverflow::NONE);
    pattern->SetTextSelection(0, 4);

    /**
     * @tc.steps: step4. enabled is false or obscured is true
     * @tc.expected: not selected
     */
    auto eventHub = pattern->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->enabled_ = false;
    pattern->SetTextSelection(0, 4);
    EXPECT_EQ(pattern->textSelector_.GetStart(), -1);
    EXPECT_EQ(pattern->textSelector_.GetEnd(), -1);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    std::vector<ObscuredReasons> reasons;
    reasons.push_back(ObscuredReasons::PLACEHOLDER);
    renderContext->UpdateObscured(reasons);
    pattern->SetTextSelection(0, 4);
    EXPECT_EQ(pattern->textSelector_.GetStart(), -1);
    EXPECT_EQ(pattern->textSelector_.GetEnd(), -1);
    eventHub->enabled_ = true;
    pattern->SetTextSelection(0, 4);
    EXPECT_EQ(pattern->textSelector_.GetStart(), -1);
    EXPECT_EQ(pattern->textSelector_.GetEnd(), -1);
}

/**
 * @tc.name: TextFrameNodeCreator004
 * @tc.desc: Test onCopy event of text.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgNine, TextFrameNodeCreator004, TestSize.Level1)
{
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE_W);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<TextEventHub>();
    EXPECT_TRUE(eventHub);
    std::u16string eventValue;
    auto event = [&eventValue](const std::u16string& param) { eventValue = param; };

    textModelNG.SetOnCopy(event);
    eventHub->SetOnCopy(std::move(event));
    EXPECT_TRUE(eventHub->onCopy_);
}

/**
 * @tc.name: BindSelectionMenu001
 * @tc.desc: Test BindSelectionMenu
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgNine, BindSelectionMenu001, TestSize.Level1)
{
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TOAST_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    auto pattern = textFrameNode->GetPattern<TextPattern>();
    int32_t callBack1 = 0;
    int32_t callBack2 = 0;
    int32_t callBack3 = 0;
    std::function<void()> buildFunc = [&callBack1]() {
        callBack1 = 1;
        return;
    };
    std::function<void(int32_t, int32_t)> onAppear = [&callBack2](int32_t a, int32_t b) {
        callBack2 = 2;
        return;
    };
    std::function<void()> onDisappear = [&callBack3]() {
        callBack3 = 3;
        return;
    };

    auto key = std::make_pair(TextSpanType::MIXED, TextResponseType::RIGHT_CLICK);
    std::shared_ptr<SelectionMenuParams> params1 = std::make_shared<SelectionMenuParams>(
        TextSpanType::MIXED, buildFunc, onAppear, onDisappear, TextResponseType::RIGHT_CLICK);
    pattern->selectionMenuMap_[key] = params1;

    std::function<void()> nullFunc = nullptr;

    pattern->BindSelectionMenu(TextSpanType::MIXED, TextResponseType::RIGHT_CLICK, nullFunc,
        { .onAppear = onAppear, .onDisappear = onDisappear });
    EXPECT_TRUE(pattern->selectionMenuMap_.empty());

    pattern->selectionMenuMap_[key] = params1;
    pattern->BindSelectionMenu(TextSpanType::MIXED, TextResponseType::RIGHT_CLICK, buildFunc,
        { .onAppear = onAppear, .onDisappear = onDisappear });
    EXPECT_FALSE(pattern->selectionMenuMap_.empty());

    pattern->BindSelectionMenu(TextSpanType::IMAGE, TextResponseType::RIGHT_CLICK, buildFunc,
        { .onAppear = onAppear, .onDisappear = onDisappear });
    EXPECT_FALSE(pattern->selectionMenuMap_.empty());
    pattern->selectionMenuMap_.clear();

    pattern->BindSelectionMenu(
        TextSpanType::TEXT, TextResponseType::NONE, buildFunc, { .onAppear = onAppear, .onDisappear = onDisappear });
    pattern->BindSelectionMenu(TextSpanType::NONE, TextResponseType::LONG_PRESS, buildFunc,
        { .onAppear = onAppear, .onDisappear = onDisappear });
    auto params = pattern->GetMenuParams(TextSpanType::TEXT, TextResponseType::RIGHT_CLICK);
    EXPECT_NE(params, nullptr);
    params = pattern->GetMenuParams(TextSpanType::IMAGE, TextResponseType::LONG_PRESS);
    EXPECT_NE(params, nullptr);
    params = pattern->GetMenuParams(TextSpanType::IMAGE, TextResponseType::RIGHT_CLICK);
    EXPECT_EQ(params, nullptr);

    pattern->selectionMenuMap_.clear();
    pattern->BindSelectionMenu(TextSpanType::TEXT, TextResponseType::LONG_PRESS, buildFunc,
        { .onAppear = onAppear, .onDisappear = onDisappear });
    pattern->BindSelectionMenu(TextSpanType::IMAGE, TextResponseType::LONG_PRESS, buildFunc,
        { .onAppear = onAppear, .onDisappear = onDisappear });
    params = pattern->GetMenuParams(TextSpanType::TEXT, TextResponseType::LONG_PRESS);
    EXPECT_NE(params, nullptr);
    params = pattern->GetMenuParams(TextSpanType::TEXT, TextResponseType::RIGHT_CLICK);
    EXPECT_EQ(params, nullptr);
    params = pattern->GetMenuParams(TextSpanType::IMAGE, TextResponseType::LONG_PRESS);
    EXPECT_NE(params, nullptr);
    params = pattern->GetMenuParams(TextSpanType::IMAGE, TextResponseType::RIGHT_CLICK);
    EXPECT_EQ(params, nullptr);

    pattern->selectionMenuMap_.clear();
    pattern->BindSelectionMenu(
        TextSpanType::NONE, TextResponseType::NONE, buildFunc, { .onAppear = onAppear, .onDisappear = onDisappear });
    params = pattern->GetMenuParams(TextSpanType::TEXT, TextResponseType::LONG_PRESS);
    EXPECT_NE(params, nullptr);
    params = pattern->GetMenuParams(TextSpanType::TEXT, TextResponseType::RIGHT_CLICK);
    EXPECT_NE(params, nullptr);
    params = pattern->GetMenuParams(TextSpanType::IMAGE, TextResponseType::NONE);
    EXPECT_NE(params, nullptr);
    params = pattern->GetMenuParams(TextSpanType::IMAGE, TextResponseType::RIGHT_CLICK);
    EXPECT_NE(params, nullptr);
    params = pattern->GetMenuParams(TextSpanType::MIXED, TextResponseType::SELECTED_BY_MOUSE);
    EXPECT_NE(params, nullptr);
}

/**
 * @tc.name: CloseSelectionMenu001
 * @tc.desc: Test CloseSelectionMenu
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgNine, CloseSelectionMenu001, TestSize.Level1)
{
    auto textFrameNode =
        FrameNode::GetOrCreateFrameNode(V2::TOAST_ETS_TAG, 1, []() { return AceType::MakeRefPtr<TextPattern>(); });
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, Content, CREATE_VALUE);
    auto pattern = textFrameNode->GetPattern<TextPattern>();
    pattern->SetTextController(AceType::MakeRefPtr<TextController>());
    pattern->GetTextController()->SetPattern(AceType::WeakClaim(AceType::RawPtr(pattern)));
    auto textController = pattern->GetTextController();
    textController->CloseSelectionMenu();
    int32_t callBack1 = 0;
    int32_t callBack2 = 0;
    int32_t callBack3 = 0;
    std::function<void()> buildFunc = [&callBack1]() {
        callBack1 = 1;
        return;
    };

    std::function<void(int32_t, int32_t)> onAppear = [&callBack2](int32_t a, int32_t b) {
        callBack2 = 2;
        return;
    };
    std::function<void()> onDisappear = [&callBack3]() {
        callBack3 = 3;
        return;
    };
    pattern->BindSelectionMenu(TextSpanType::MIXED, TextResponseType::LONG_PRESS, buildFunc,
        { .onAppear = onAppear, .onDisappear = onDisappear });
    GestureEvent info;
    info.localLocation_ = Offset(1, 1);
    // copyOption = None
    pattern->HandleLongPress(info);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), -1);
    pattern->copyOption_ = CopyOptions::Distributed;
    pattern->textForDisplay_ = CREATE_VALUE_W;
    pattern->textSelector_.Update(0, 20);
    pattern->ShowSelectOverlay();

    auto isClosed = !pattern->selectOverlay_->SelectOverlayIsOn();
    EXPECT_FALSE(isClosed);
    textController = pattern->GetTextController();
    textController->CloseSelectionMenu();
    isClosed = !pattern->selectOverlay_->SelectOverlayIsOn();
    EXPECT_TRUE(isClosed);
}

/**
 * @tc.name: OnTextSelectionChange001
 * @tc.desc: Test onTextSelectionChange
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgNine, OnTextSelectionChange001, TestSize.Level1)
{
    auto textFrameNode =
        FrameNode::GetOrCreateFrameNode(V2::TOAST_ETS_TAG, 2, []() { return AceType::MakeRefPtr<TextPattern>(); });
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, Content, CREATE_VALUE);
    auto pattern = textFrameNode->GetPattern<TextPattern>();
    pattern->SetTextController(AceType::MakeRefPtr<TextController>());
    pattern->GetTextController()->SetPattern(AceType::WeakClaim(AceType::RawPtr(pattern)));
    pattern->textForDisplay_ = CREATE_VALUE_W;
    pattern->selectOverlayProxy_ = nullptr;
    ParagraphStyle paragraphStyle;
    RefPtr<Paragraph> paragraph = Paragraph::Create(paragraphStyle, FontCollection::Current());
    pattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 100 });
    pattern->HandleOnSelectAll();
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), pattern->textForDisplay_.length());

    pattern->ResetSelection();
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), -1);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), -1);
    pattern->pManager_->Reset();
}

/**
 * @tc.name: OnTextSelectionChange002
 * @tc.desc: Test onTextSelectionChange.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgNine, OnTextSelectionChange002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE_W);
    /**
     * @tc.steps: step2. call SetTextSelection with CopyOptions::InApp
     * @tc.expected: longPress/gesture/input will be regist when CopyOptions not none.
     */
    textModelNG.SetCopyOption(CopyOptions::InApp);
    textModelNG.SetTextDetectEnable(true);
    bool isSelectChanged = false;
    auto onSelectionChanged = [&isSelectChanged](int32_t, int32_t) { isSelectChanged = true; };
    textModelNG.SetOnTextSelectionChange(onSelectionChanged);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    frameNode->draggable_ = true;
    auto pattern = frameNode->GetPattern<TextPattern>();
    auto gestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);
    EXPECT_NE(gestureEventHub->longPressEventActuator_->longPressEvent_, nullptr);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto inputHub = eventHub->GetOrCreateInputEventHub();
    EXPECT_TRUE(!inputHub->mouseEventActuator_->inputEvents_.empty());
    EXPECT_TRUE(!gestureEventHub->touchEventActuator_->touchEvents_.empty());

    /**
     * @tc.steps: step3. create paragraph
     */
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, GetGlyphIndexByCoordinate(_, _)).WillRepeatedly(Return(0));
    EXPECT_CALL(*paragraph, GetHeight()).WillRepeatedly(Return(10.f));
    EXPECT_CALL(*paragraph, GetWordBoundary(_, _, _))
        .WillRepeatedly(DoAll(SetArgReferee<1>(0), SetArgReferee<2>(2), Return(false)));
    pattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 100 });
    GestureEvent info;
    info.localLocation_ = Offset(1, 2);
    pattern->HandleLongPress(info);
    EXPECT_EQ(isSelectChanged, true);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), 1);

    EXPECT_CALL(*paragraph, GetWordBoundary(_, _, _))
        .WillRepeatedly(DoAll(SetArgReferee<1>(0), SetArgReferee<2>(2), Return(true)));
    pattern->HandleLongPress(info);
    EXPECT_EQ(isSelectChanged, true);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), 2);
    pattern->pManager_->Reset();
}

/**
 * @tc.name: OnTextSelectionChange003
 * @tc.desc: Test onTextSelectionChange.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgNine, OnTextSelectionChange003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE_W);
    /**
     * @tc.steps: step2. call SetTextSelection with CopyOptions::InApp
     * @tc.expected: longPress/gesture/input will be regist when CopyOptions not none.
     */
    textModelNG.SetCopyOption(CopyOptions::InApp);
    textModelNG.SetTextDetectEnable(true);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    frameNode->draggable_ = true;
    auto pattern = frameNode->GetPattern<TextPattern>();

    auto textSelectOverlay = pattern->selectOverlay_;
    ASSERT_NE(textSelectOverlay, nullptr);

    /**
     * @tc.steps: step3. create paragraph
     */
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, GetGlyphIndexByCoordinate(_, _)).WillRepeatedly(Return(2));
    EXPECT_CALL(*paragraph, GetHeight()).WillRepeatedly(Return(10.f));
    pattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 100 });

    /**
     * @tc.steps: step4. select range is 0-5
     */
    pattern->textSelector_.Update(0, 5);
    int32_t secondIndex = pattern->GetTextSelector().destinationOffset;

    /**
     * @tc.steps: step5. move secondHandle to index 2
     */
    OffsetF secondOffset(ADAPT_OFFSETY_VALUE, ADAPT_OFFSETX_VALUE);
    int32_t currentHaandleIndex = pattern->GetHandleIndex(Offset(ADAPT_OFFSETY_VALUE, ADAPT_OFFSETY_VALUE));
    textSelectOverlay->UpdateSelectorOnHandleMove(secondOffset, false);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), 2);
    EXPECT_NE(currentHaandleIndex, secondIndex);

    secondIndex = pattern->GetTextSelector().destinationOffset;
    currentHaandleIndex = pattern->GetHandleIndex(Offset(ADAPT_OFFSETY_VALUE, ADAPT_OFFSETY_VALUE));
    textSelectOverlay->UpdateSelectorOnHandleMove(secondOffset, false);
    EXPECT_EQ(currentHaandleIndex, secondIndex);

    pattern->pManager_->Reset();
}

/**
 * @tc.name: OnTextSelectionChange004
 * @tc.desc: Test onTextSelectionChange.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgNine, OnTextSelectionChange004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE_W);
    /**
     * @tc.steps: step2. call SetTextSelection with CopyOptions::InApp
     * @tc.expected: longPress/gesture/input will be regist when CopyOptions not none.
     */
    textModelNG.SetCopyOption(CopyOptions::InApp);
    textModelNG.SetTextDetectEnable(true);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    frameNode->draggable_ = true;
    auto pattern = frameNode->GetPattern<TextPattern>();

    auto textSelectOverlay = pattern->selectOverlay_;
    ASSERT_NE(textSelectOverlay, nullptr);

    /**
     * @tc.steps: step3. create paragraph
     */
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, GetGlyphIndexByCoordinate(_, _)).WillRepeatedly(Return(2));
    EXPECT_CALL(*paragraph, GetHeight()).WillRepeatedly(Return(10.f));
    pattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 100 });

    /**
     * @tc.steps: step4. select range is 0-5
     */
    pattern->textSelector_.Update(0, 5);
    int32_t firstIndex = pattern->GetTextSelector().baseOffset;

    /**
     * @tc.steps: step5. move firstHandle to index 2
     */
    OffsetF secondOffset(ADAPT_OFFSETY_VALUE, ADAPT_OFFSETX_VALUE);
    int32_t currentHaandleIndex = pattern->GetHandleIndex(Offset(ADAPT_OFFSETY_VALUE, ADAPT_OFFSETY_VALUE));
    textSelectOverlay->UpdateSelectorOnHandleMove(secondOffset, true);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 2);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), 5);
    EXPECT_NE(currentHaandleIndex, firstIndex);

    firstIndex = pattern->GetTextSelector().baseOffset;
    currentHaandleIndex = pattern->GetHandleIndex(Offset(ADAPT_OFFSETY_VALUE, ADAPT_OFFSETY_VALUE));
    textSelectOverlay->UpdateSelectorOnHandleMove(secondOffset, true);
    EXPECT_EQ(currentHaandleIndex, firstIndex);

    pattern->pManager_->Reset();
}

/**
 * @tc.name: OnTextSelectionChange005
 * @tc.desc: Test onTextSelectionChange.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgNine, OnTextSelectionChange005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE_W);
    /**
     * @tc.steps: step2. call SetTextSelection with CopyOptions::InApp
     * @tc.expected: longPress/gesture/input will be regist when CopyOptions not none.
     */
    textModelNG.SetCopyOption(CopyOptions::InApp);
    textModelNG.SetTextDetectEnable(true);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    frameNode->draggable_ = true;
    auto pattern = frameNode->GetPattern<TextPattern>();

    auto textSelectOverlay = pattern->selectOverlay_;
    ASSERT_NE(textSelectOverlay, nullptr);

    /**
     * @tc.steps: step3. create paragraph
     */
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, GetGlyphIndexByCoordinate(_, _)).WillRepeatedly(Return(10));
    EXPECT_CALL(*paragraph, GetHeight()).WillRepeatedly(Return(10.f));
    pattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 100 });

    /**
     * @tc.steps: step4. select range is 0-5
     */
    pattern->textSelector_.Update(0, 5);
    int32_t firstIndex = pattern->GetTextSelector().baseOffset;

    /**
     * @tc.steps: step5. move firstHandle to index 10
     */
    OffsetF secondOffset(ADAPT_OFFSETY_VALUE, ADAPT_OFFSETX_VALUE);
    int32_t currentHaandleIndex = pattern->GetHandleIndex(Offset(ADAPT_OFFSETY_VALUE, ADAPT_OFFSETY_VALUE));
    textSelectOverlay->UpdateSelectorOnHandleMove(secondOffset, true);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 5);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), 10);
    EXPECT_NE(currentHaandleIndex, firstIndex);

    firstIndex = pattern->GetTextSelector().baseOffset;
    currentHaandleIndex = pattern->GetHandleIndex(Offset(ADAPT_OFFSETY_VALUE, ADAPT_OFFSETY_VALUE));
    textSelectOverlay->UpdateSelectorOnHandleMove(secondOffset, true);
    EXPECT_EQ(currentHaandleIndex, firstIndex);

    pattern->pManager_->Reset();
}

/**
 * @tc.name: TextLayoutAlgorithmTest009
 * @tc.desc: test text_layout_algorithm.cpp: new method UpdateParagraphForAISpan001
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgNine, TextLayoutAlgorithmTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textFrameNode, geometryNode, textFrameNode->GetLayoutProperty());
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    textPattern->contentMod_ = AceType::MakeRefPtr<TextContentModifier>(std::optional<TextStyle>(TextStyle()));
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    TextStyle textStyle;
    textStyle.SetMaxLines(MAX_LINES);
    textStyle.SetTextCase(TextCase::NORMAL);
    LayoutConstraintF contentConstraint;
    ParagraphStyle paraStyle = { .direction = TextDirection::LTR,
        .align = textStyle.GetTextAlign(),
        .maxLines = textStyle.GetMaxLines(),
        .fontLocale = "zh-CN",
        .wordBreak = textStyle.GetWordBreak(),
        .lineBreakStrategy = textStyle.GetLineBreakStrategy(),
        .textOverflow = textStyle.GetTextOverflow() };
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();

    AISpan aiSpan1;
    aiSpan1.start = AI_SPAN_START;
    aiSpan1.end = AI_SPAN_END;
    aiSpan1.content = SPAN_PHONE;
    aiSpan1.type = TextDataDetectType::PHONE_NUMBER;
    AISpan aiSpan2;
    aiSpan2.start = AI_SPAN_START_II;
    aiSpan2.end = AI_SPAN_END_II;
    aiSpan2.content = SPAN_URL;
    aiSpan2.type = TextDataDetectType::URL;
    std::map<int32_t, AISpan> aiSpanMap;
    aiSpanMap[AI_SPAN_START] = aiSpan1;
    aiSpanMap[AI_SPAN_START_II] = aiSpan2;
    ASSERT_NE(textPattern->GetDataDetectorAdapter(), nullptr);
    textPattern->dataDetectorAdapter_->aiSpanMap_ = aiSpanMap;
    textPattern->dataDetectorAdapter_->textForAI_ = U16TEXT_FOR_AI;

    /**
     * @tc.steps: step2. Create textLayoutAlgorithm and call UpdateParagraphForAISpan function.
     * @tc.expected: textLayoutAlgorithm->paragraph_.rawPtr_ is nullptr.
     */
    auto textLayoutAlgorithm = AceType::DynamicCast<TextLayoutAlgorithm>(textPattern->CreateLayoutAlgorithm());
    textLayoutAlgorithm->paragraphManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 100 });
    textLayoutAlgorithm->UpdateParagraphForAISpan(textStyle, AccessibilityManager::RawPtr(layoutWrapper), paragraph);
    EXPECT_NE(textLayoutAlgorithm->paragraphManager_->GetParagraphs().front().paragraph.rawPtr_, nullptr);
}

/**
 * @tc.name: HandleClickAISpanEvent
 * @tc.desc: test test_pattern.h HandleClickAISpanEvent function with valid textSelector
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgNine, HandleClickAISpanEvent, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();
    pattern->textSelector_.Update(0, 20);

    /**
     * @tc.steps: step2. construct spanItemChildren
     */
    auto spanItemChild = AceType::MakeRefPtr<SpanItem>();
    spanItemChild->content = U16TEXT_FOR_AI;
    spanItemChild->position = spanItemChild->content.length();
    pattern->spans_.emplace_back(spanItemChild);

    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    std::vector<RectF> rects { RectF(0, 0, 20, 20) };
    EXPECT_CALL(*paragraph, GetRectsForRange(_, _, _)).WillRepeatedly(SetArgReferee<2>(rects));
    pattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 100 });

    pattern->SetTextDetectEnable(true);
    RectF textContentRect = CONTENT_RECT;
    pattern->copyOption_ = CopyOptions::Distributed;

    Ace::AISpan aiSpan1;
    aiSpan1.start = AI_SPAN_START;
    aiSpan1.end = AI_SPAN_END;
    aiSpan1.content = SPAN_PHONE;
    aiSpan1.type = TextDataDetectType::PHONE_NUMBER;
    Ace::AISpan aiSpan2;
    aiSpan2.start = AI_SPAN_START_II;
    aiSpan2.end = AI_SPAN_END_II;
    aiSpan2.content = SPAN_URL;
    aiSpan2.type = TextDataDetectType::URL;
    std::map<int32_t, Ace::AISpan> aiSpanMap;
    aiSpanMap[AI_SPAN_START] = aiSpan1;
    aiSpanMap[AI_SPAN_START_II] = aiSpan2;
    ASSERT_NE(pattern->GetDataDetectorAdapter(), nullptr);
    pattern->dataDetectorAdapter_->aiSpanMap_ = aiSpanMap;

    /**
     * @tc.steps: step3. create GestureEvent and call HandleClickAISpanEvent function.
     * @tc.expected: isClickOnAISpan is been setted true.
     */
    GestureEvent info;
    info.localLocation_ = Offset(3.0f, 3.0f);

    PointF textOffset = { info.GetLocalLocation().GetX() - textContentRect.GetX(),
        info.GetLocalLocation().GetY() - textContentRect.GetY() };

    pattern->HandleClickAISpanEvent(textOffset);
    EXPECT_TRUE(pattern->dataDetectorAdapter_->hasClickedAISpan_);
    pattern->pManager_->Reset();
}

/**
 * @tc.name: ShowAIEntityMenu
 * @tc.desc: test test_pattern.h ShowAIEntityMenu function with valid textSelector
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgNine, ShowAIEntityMenu, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();
    pattern->textSelector_.Update(0, 20);
    auto textSpanNode = CreateSpanNodeWithSetDefaultProperty(U16TEXT_FOR_AI);
    ASSERT_NE(textSpanNode, nullptr);
    pattern->AddChildSpanItem(textSpanNode);
    pattern->SetTextDetectEnable(true);

    Ace::AISpan aiSpan;
    aiSpan.start = AI_SPAN_START;
    aiSpan.end = AI_SPAN_END;
    aiSpan.content = SPAN_PHONE;
    aiSpan.type = TextDataDetectType::PHONE_NUMBER;

    /**
     * @tc.steps: step2. call ShowAIEntityMenu function
     * @tc.expected: ShowAIEntityMenu result is true.
     */
    EXPECT_TRUE(pattern->ShowAIEntityMenu(aiSpan, nullptr, nullptr));
}
} // namespace OHOS::Ace::NG