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

#include "test/unittest/core/pattern/rich_editor/rich_editor_styled_string_common_test_ng.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/base/mock_task_executor.h"
 
using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
void RichEditorStyledStringCommonTestNg::SetUp()
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
    richEditorPattern->SetRichEditorController(AceType::MakeRefPtr<RichEditorController>());
    richEditorPattern->GetRichEditorController()->SetPattern(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
    richEditorPattern->CreateNodePaintMethod();
    richEditorNode_->GetGeometryNode()->SetContentSize({});
}

void RichEditorStyledStringCommonTestNg::TearDown()
{
    richEditorNode_ = nullptr;
    MockParagraph::TearDown();
}

void RichEditorStyledStringCommonTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}
    
RefPtr<MutableSpanString> RichEditorStyledStringCommonTestNg::CreateTextStyledString(const std::u16string& content)
{
    auto styledString = AceType::MakeRefPtr<MutableSpanString>(content);
    auto length = styledString->GetLength();
    styledString->AddSpan(AceType::MakeRefPtr<FontSpan>(TEST_FONT, 0, length));
    styledString->AddSpan(AceType::MakeRefPtr<DecorationSpan>(TEXT_DECORATION_VALUE, TEXT_DECORATION_COLOR_VALUE,
        TextDecorationStyle::WAVY, 0, length));
    styledString->AddSpan(AceType::MakeRefPtr<BaselineOffsetSpan>(TEST_BASELINE_OFFSET, 0, length));
    styledString->AddSpan(AceType::MakeRefPtr<LetterSpacingSpan>(LETTER_SPACING, 0, length));
    styledString->AddSpan(AceType::MakeRefPtr<TextShadowSpan>(SHADOWS, 0, length));
    styledString->AddSpan(AceType::MakeRefPtr<ParagraphStyleSpan>(TEST_PARAGRAPH_STYLE, 0, length));
    styledString->AddSpan(AceType::MakeRefPtr<LineHeightSpan>(LINE_HEIGHT_VALUE, 0, length));
    return styledString;
}

RefPtr<MutableSpanString> RichEditorStyledStringCommonTestNg::CreateImageStyledString()
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

RefPtr<MutableSpanString> RichEditorStyledStringCommonTestNg::CreateCustomSpanStyledString()
{
    auto customSpan = AceType::MakeRefPtr<CustomSpan>();
    return AceType::MakeRefPtr<MutableSpanString>(customSpan);
}

void RichEditorStyledStringCommonTestNg::SetTypingStyle()
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
} // namespace OHOS::Ace::NG