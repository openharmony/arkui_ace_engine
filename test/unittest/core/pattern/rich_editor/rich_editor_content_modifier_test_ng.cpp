/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/rich_editor/rich_editor_content_modifier.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/base/mock_task_executor.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::u16string INIT_STRING_1 = u"初始属性字符串";
const std::u16string INIT_STRING_2 = u"Hellow World";
const std::u16string INIT_STRING_3 = u"123456";
const std::string TEST_IMAGE_SOURCE = "src/image.png";
const int32_t TEST_MAX_LINE = 10;
const Dimension TEST_BASELINE_OFFSET = Dimension(5, DimensionUnit::PX);
const Dimension TEST_TEXT_INDENT = Dimension(20, DimensionUnit::PX);
const CalcLength TEST_MARGIN_CALC { 10.0, DimensionUnit::CALC };
const CalcLength TEST_PADDING_CALC { 5.0, DimensionUnit::CALC };
const ImageSpanSize TEST_IMAGE_SIZE = { .width = 50.0_vp, .height = 50.0_vp };
const BorderRadiusProperty TEST_BORDER_RADIUS = { 4.0_vp, 4.0_vp, 4.0_vp, 4.0_vp };
const LeadingMarginSize TEST_LEADING_MARGIN_SIZE = { Dimension(5.0), Dimension(10.0) };
const LeadingMargin TEST_LEADING_MARGIN = { .size = TEST_LEADING_MARGIN_SIZE };
const Font TEST_FONT = { FONT_WEIGHT_BOLD, FONT_SIZE_VALUE, ITALIC_FONT_STYLE_VALUE, FONT_FAMILY_VALUE,
    OHOS::Ace::Color::RED, FONT_FAMILY_VALUE};
const SpanParagraphStyle TEST_PARAGRAPH_STYLE = { TextAlign::END, TextVerticalAlign::BASELINE, TEST_MAX_LINE,
    WordBreak::BREAK_ALL, TextOverflow::ELLIPSIS, TEST_LEADING_MARGIN, TEST_TEXT_INDENT};
StyledStringChangeValue onStyledStringWillChangeValue;
StyledStringChangeValue onStyledStringDidChangeValue;
Testing::MockCanvas canvas;
const float TEXTRICHTEXTRECTX = 0.1f;
const float TEXTRICHTEXTRECTY = 0.1f;
} // namespace

class RichEditorContentModifierTestNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
    RefPtr<MutableSpanString> CreateTextStyledString(const std::u16string& content);
    RefPtr<MutableSpanString> CreateImageStyledString();
    RefPtr<MutableSpanString> CreateCustomSpanStyledString();
    void SetTypingStyle();
};

void RichEditorContentModifierTestNg::SetUp()
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
    richEditorPattern->SetSpanStringMode(true);
    richEditorPattern->SetRichEditorStyledStringController(AceType::MakeRefPtr<RichEditorStyledStringController>());
    richEditorPattern->GetRichEditorStyledStringController()->SetPattern(WeakPtr(richEditorPattern));
    richEditorPattern->CreateNodePaintMethod();
    richEditorNode_->GetGeometryNode()->SetContentSize({});
}

void RichEditorContentModifierTestNg::TearDown()
{
    richEditorNode_ = nullptr;
    MockParagraph::TearDown();
}

void RichEditorContentModifierTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

RefPtr<MutableSpanString> RichEditorContentModifierTestNg::CreateTextStyledString(const std::u16string& content)
{
    auto styledString = AceType::MakeRefPtr<MutableSpanString>(content);
    auto length = styledString->GetLength();
    styledString->AddSpan(AceType::MakeRefPtr<FontSpan>(TEST_FONT, 0, length));
    std::optional<TextDecorationOptions> options;
    styledString->AddSpan(AceType::MakeRefPtr<DecorationSpan>(std::vector<TextDecoration>({TEXT_DECORATION_VALUE}),
        TEXT_DECORATION_COLOR_VALUE, TextDecorationStyle::WAVY, options, 0, length));
    styledString->AddSpan(AceType::MakeRefPtr<BaselineOffsetSpan>(TEST_BASELINE_OFFSET, 0, length));
    styledString->AddSpan(AceType::MakeRefPtr<LetterSpacingSpan>(LETTER_SPACING, 0, length));
    styledString->AddSpan(AceType::MakeRefPtr<TextShadowSpan>(SHADOWS, 0, length));
    styledString->AddSpan(AceType::MakeRefPtr<ParagraphStyleSpan>(TEST_PARAGRAPH_STYLE, 0, length));
    styledString->AddSpan(AceType::MakeRefPtr<LineHeightSpan>(LINE_HEIGHT_VALUE, 0, length));
    return styledString;
}

RefPtr<MutableSpanString> RichEditorContentModifierTestNg::CreateImageStyledString()
{
    MarginProperty margins;
    margins.SetEdges(TEST_MARGIN_CALC);
    PaddingProperty paddings;
    paddings.SetEdges(TEST_PADDING_CALC);
    ImageSpanAttribute attr { .size = TEST_IMAGE_SIZE,
        .paddingProp = paddings,
        .marginProp = margins,
        .borderRadius = TEST_BORDER_RADIUS,
        .objectFit = ImageFit::COVER,
        .verticalAlign = VerticalAlign::BOTTOM };
    ImageSpanOptions imageOption { .image = TEST_IMAGE_SOURCE, .imageAttribute = attr };
    return AceType::MakeRefPtr<MutableSpanString>(imageOption);
}

RefPtr<MutableSpanString> RichEditorContentModifierTestNg::CreateCustomSpanStyledString()
{
    auto customSpan = AceType::MakeRefPtr<CustomSpan>();
    return AceType::MakeRefPtr<MutableSpanString>(customSpan);
}

void RichEditorContentModifierTestNg::SetTypingStyle()
{
    TextStyle textStyle;
    textStyle.SetTextColor(TEXT_COLOR_VALUE);
    textStyle.SetTextShadows(SHADOWS);
    textStyle.SetFontSize(FONT_SIZE_VALUE);
    textStyle.SetFontStyle(ITALIC_FONT_STYLE_VALUE);
    textStyle.SetFontWeight(FONT_WEIGHT_VALUE);
    textStyle.SetTextDecoration(TEXT_DECORATION_VALUE);
    textStyle.SetTextDecorationColor(TEXT_DECORATION_COLOR_VALUE);
    textStyle.SetLineHeight(LINE_HEIGHT_VALUE);
    textStyle.SetLetterSpacing(LETTER_SPACING);
    UpdateSpanStyle typingStyle;
    typingStyle.updateTextColor = TEXT_COLOR_VALUE;
    typingStyle.updateTextShadows = SHADOWS;
    typingStyle.updateFontSize = FONT_SIZE_VALUE;
    typingStyle.updateItalicFontStyle = ITALIC_FONT_STYLE_VALUE;
    typingStyle.updateFontWeight = FONT_WEIGHT_VALUE;
    typingStyle.updateTextDecoration = TEXT_DECORATION_VALUE;
    typingStyle.updateTextDecorationColor = TEXT_DECORATION_COLOR_VALUE;
    typingStyle.updateLineHeight = LINE_HEIGHT_VALUE;
    typingStyle.updateLetterSpacing = LETTER_SPACING;
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    richEditorPattern->SetTypingStyle(typingStyle, textStyle);
}

/**
 * @tc.name: onDraw001
 * @tc.desc: Test FromStyledString.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorContentModifierTestNg, onDraw001, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentPattern = richEditorPattern->contentPattern_;
    ASSERT_NE(contentPattern, nullptr);
    auto testContentModifier = AceType::MakeRefPtr<RichEditorContentModifier>(
        richEditorPattern->textStyle_, &richEditorPattern->paragraphs_, contentPattern);
    TestParagraphRect paragraphRect = { .start = 0, .end = 2, .rects = { { -400.0, -400.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 2,
        .indexOffsetMap = { { 0, Offset(0, 0) }, { 6, Offset(50, 0) } },
        .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);
    ASSERT_NE(testContentModifier, nullptr);
    DrawingContext context { canvas, CONTEXT_WIDTH_VALUE, CONTEXT_HEIGHT_VALUE };
    testContentModifier->onDraw(context);
}

/**
 * @tc.name: SetRichTextRectX001
 * @tc.desc: Test FromStyledString.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorContentModifierTestNg, SetRichTextRectX001, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentPattern = richEditorPattern->contentPattern_;
    ASSERT_NE(contentPattern, nullptr);
    auto testContentModifier = AceType::MakeRefPtr<RichEditorContentModifier>(
        richEditorPattern->textStyle_, &richEditorPattern->paragraphs_, contentPattern);

    ASSERT_NE(testContentModifier, nullptr);
    testContentModifier->SetRichTextRectX(TEXTRICHTEXTRECTX);
    ASSERT_EQ(TEXTRICHTEXTRECTX, testContentModifier->richTextRectX_->GetStagingValue());
}

/**
 * @tc.name: SetRichTextRectY001
 * @tc.desc: Test FromStyledString.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorContentModifierTestNg, SetRichTextRectY001, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentPattern = richEditorPattern->contentPattern_;
    ASSERT_NE(contentPattern, nullptr);
    auto testContentModifier = AceType::MakeRefPtr<RichEditorContentModifier>(
        richEditorPattern->textStyle_, &richEditorPattern->paragraphs_, contentPattern);

    ASSERT_NE(testContentModifier, nullptr);
    testContentModifier->SetRichTextRectY(TEXTRICHTEXTRECTY);
    ASSERT_EQ(TEXTRICHTEXTRECTY, testContentModifier->richTextRectY_->GetStagingValue());
}

/**
 * @tc.name: SetClipOffset001
 * @tc.desc: Test FromStyledString.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorContentModifierTestNg, SetClipOffset001, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentPattern = richEditorPattern->contentPattern_;
    ASSERT_NE(contentPattern, nullptr);
    auto testContentModifier = AceType::MakeRefPtr<RichEditorContentModifier>(
        richEditorPattern->textStyle_, &richEditorPattern->paragraphs_, contentPattern);
    OffsetF testOffset = {};
    ASSERT_NE(testContentModifier, nullptr);
    testContentModifier->SetClipOffset(testOffset);
    ASSERT_EQ(testOffset, testContentModifier->clipOffset_->GetStagingValue());
}

/**
 * @tc.name: SetClipSize001
 * @tc.desc: Test FromStyledString.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorContentModifierTestNg, SetClipSize001, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentPattern = richEditorPattern->contentPattern_;
    ASSERT_NE(contentPattern, nullptr);
    auto testContentModifier = AceType::MakeRefPtr<RichEditorContentModifier>(
        richEditorPattern->textStyle_, &richEditorPattern->paragraphs_, contentPattern);
    SizeF testSize = {};
    ASSERT_NE(testContentModifier, nullptr);
    testContentModifier->SetClipSize(testSize);
    ASSERT_EQ(testSize, testContentModifier->clipSize_->GetStagingValue());
}

/**
 * @tc.name: PaintCustomSpan001
 * @tc.desc: Test FromStyledString.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorContentModifierTestNg, PaintCustomSpan001, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentPattern = richEditorPattern->contentPattern_;
    ASSERT_NE(contentPattern, nullptr);
    richEditorPattern->contentMod_ = AceType::MakeRefPtr<RichEditorContentModifier>(
        richEditorPattern->textStyle_, &richEditorPattern->paragraphs_, contentPattern);
    TestParagraphRect paragraphRect = { .start = 0, .end = 2, .rects = { { -400.0, -400.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 2,
        .indexOffsetMap = { { 0, Offset(0, 0) }, { 6, Offset(50, 0) } },
        .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);
    ASSERT_NE(richEditorPattern->contentMod_, nullptr);
    DrawingContext context { canvas, CONTEXT_WIDTH_VALUE, CONTEXT_HEIGHT_VALUE };
    richEditorPattern->contentMod_->PaintCustomSpan(context);
}

/**
 * @tc.name: PaintCustomSpan002
 * @tc.desc: Test FromStyledString.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorContentModifierTestNg, PaintCustomSpan002, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentPattern = richEditorPattern->contentPattern_;
    ASSERT_NE(contentPattern, nullptr);
    auto testContentModifier = AceType::MakeRefPtr<RichEditorContentModifier>(
        richEditorPattern->textStyle_, &richEditorPattern->paragraphs_, contentPattern);
    DrawingContext context { canvas, CONTEXT_WIDTH_VALUE, CONTEXT_HEIGHT_VALUE };
    CustomSpanPlaceholderInfo info;
    richEditorPattern->customSpanPlaceholder_.emplace_back(info);
    testContentModifier->PaintCustomSpan(context);
    EXPECT_FALSE(info.onDraw);
}

/**
 * @tc.name: PaintCustomSpan003
 * @tc.desc: Test FromStyledString.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorContentModifierTestNg, PaintCustomSpan003, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentPattern = richEditorPattern->contentPattern_;
    ASSERT_NE(contentPattern, nullptr);
    auto testContentModifier = AceType::MakeRefPtr<RichEditorContentModifier>(
        richEditorPattern->textStyle_, &richEditorPattern->paragraphs_, contentPattern);
    DrawingContext context { canvas, CONTEXT_WIDTH_VALUE, CONTEXT_HEIGHT_VALUE };
    CustomSpanPlaceholderInfo info;
    info.onDraw = [](NG::DrawingContext& context, CustomSpanOptions options) {};
    richEditorPattern->customSpanPlaceholder_.emplace_back(info);
    testContentModifier->PaintCustomSpan(context);
    EXPECT_TRUE(info.onDraw);
}

/**
 * @tc.name: PaintCustomSpan004
 * @tc.desc: Test FromStyledString.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorContentModifierTestNg, PaintCustomSpan004, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentPattern = richEditorPattern->contentPattern_;
    ASSERT_NE(contentPattern, nullptr);
    auto testContentModifier = AceType::MakeRefPtr<RichEditorContentModifier>(
        richEditorPattern->textStyle_, &richEditorPattern->paragraphs_, contentPattern);
    DrawingContext context { canvas, CONTEXT_WIDTH_VALUE, CONTEXT_HEIGHT_VALUE };
    CustomSpanPlaceholderInfo info;
    info.customSpanIndex = 0;
    info.onDraw = [](NG::DrawingContext& context, CustomSpanOptions options) {};
    richEditorPattern->rectsForPlaceholders_.emplace_back();
    richEditorPattern->customSpanPlaceholder_.emplace_back(info);
    TestParagraphRect paragraphRect = { .start = 0, .end = 2, .rects = { { -400.0, -400.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0,
        .end = 2,
        .indexOffsetMap = { { 0, Offset(0, 0) }, { 6, Offset(50, 0) } },
        .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);
    testContentModifier->PaintCustomSpan(context);
    EXPECT_TRUE(info.onDraw);
}

/**
 * @tc.name: PaintCustomSpan005
 * @tc.desc: Test FromStyledString.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorContentModifierTestNg, PaintCustomSpan005, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentPattern = richEditorPattern->contentPattern_;
    ASSERT_NE(contentPattern, nullptr);
    auto testContentModifier = AceType::MakeRefPtr<RichEditorContentModifier>(
        richEditorPattern->textStyle_, &richEditorPattern->paragraphs_, contentPattern);
    DrawingContext context { canvas, CONTEXT_WIDTH_VALUE, CONTEXT_HEIGHT_VALUE };
    CustomSpanPlaceholderInfo info;
    info.customSpanIndex = -1;
    info.onDraw = [](NG::DrawingContext& context, CustomSpanOptions options) {};
    richEditorPattern->rectsForPlaceholders_.emplace_back();
    richEditorPattern->customSpanPlaceholder_.emplace_back(info);
    TestParagraphRect paragraphRect = { .start = 0, .end = 2, .rects = { { -400.0, -400.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0,
        .end = 2,
        .indexOffsetMap = { { 0, Offset(0, 0) }, { 6, Offset(50, 0) } },
        .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);
    auto rectsForPlaceholderSize = richEditorPattern->GetRectsForPlaceholders().size();
    testContentModifier->PaintCustomSpan(context);
    EXPECT_FALSE(info.customSpanIndex >= static_cast<int32_t>(rectsForPlaceholderSize));
}

/**
 * @tc.name: PaintCustomSpan006
 * @tc.desc: Test FromStyledString.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorContentModifierTestNg, PaintCustomSpan006, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentPattern = richEditorPattern->contentPattern_;
    ASSERT_NE(contentPattern, nullptr);
    auto testContentModifier = AceType::MakeRefPtr<RichEditorContentModifier>(
        richEditorPattern->textStyle_, &richEditorPattern->paragraphs_, contentPattern);
    DrawingContext context { canvas, CONTEXT_WIDTH_VALUE, CONTEXT_HEIGHT_VALUE };
    CustomSpanPlaceholderInfo info;
    info.customSpanIndex = 1;
    info.onDraw = [](NG::DrawingContext& context, CustomSpanOptions options) {};
    richEditorPattern->rectsForPlaceholders_.emplace_back();
    richEditorPattern->customSpanPlaceholder_.emplace_back(info);
    TestParagraphRect paragraphRect = { .start = 0, .end = 2, .rects = { { -400.0, -400.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0,
        .end = 2,
        .indexOffsetMap = { { 0, Offset(0, 0) }, { 6, Offset(50, 0) } },
        .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);
    auto rectsForPlaceholderSize = richEditorPattern->GetRectsForPlaceholders().size();
    testContentModifier->PaintCustomSpan(context);
    EXPECT_TRUE(info.customSpanIndex >= static_cast<int32_t>(rectsForPlaceholderSize));
}
} // namespace OHOS::Ace::NG
