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
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "test/mock/core/common/mock_udmf.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/base/mock_task_executor.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model_ng.h"
#include "core/components_ng/pattern/rich_editor/style_manager.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const LeadingMargin TEST_LEADING_MARGIN = {
    .size = LeadingMarginSize(Dimension(20, DimensionUnit::VP), Dimension(30, DimensionUnit::VP)),
    .pixmap = nullptr
};
const struct UpdateParagraphStyle TEST_TYPING_PARAGRAPH_STYLE = {
    .textAlign = TextAlign::CENTER,
    .leadingMargin = TEST_LEADING_MARGIN,
    .wordBreak = WordBreak::BREAK_WORD,
    .lineBreakStrategy = LineBreakStrategy::HIGH_QUALITY,
    .paragraphSpacing = Dimension(10, DimensionUnit::VP)
};
const struct UpdateSpanStyle TEST_TYPING_STYLE = {
    .updateTextColor = Color::RED,
    .updateFontSize = CalcDimension(1.0),
    .updateItalicFontStyle = OHOS::Ace::FontStyle::ITALIC,
    .updateFontWeight = FontWeight::BOLD,
    .updateTextShadows = SHADOWS,
};
}

class RichEditorTypingStyleTest : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
};

void RichEditorTypingStyleTest::SetUp()
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

void RichEditorTypingStyleTest::TearDown()
{
    richEditorNode_ = nullptr;
    MockParagraph::TearDown();
}

void RichEditorTypingStyleTest::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

/**
 * @tc.name: UseTypingParaStyle001
 * @tc.desc: test UseTypingParaStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTypingStyleTest, UseTypingParaStyle001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    std::optional<struct UpdateParagraphStyle> typingParagraphStyle = UpdateParagraphStyle();
    richEditorPattern->SetTypingParagraphStyle(typingParagraphStyle);
    auto& styleManager = richEditorPattern->styleManager_;
    std::list<RefPtr<SpanItem>> spans;
    int32_t caretPosition = 0;
    EXPECT_EQ(styleManager->HasTypingParagraphStyle(), true);
    EXPECT_EQ(styleManager->UseTypingParaStyle(spans, caretPosition), true);

    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    spanItem->content = u"123\n";
    spanItem->position = static_cast<int32_t>(spanItem->content.length());
    spans.push_back(spanItem);
    caretPosition = 4;
    EXPECT_EQ(styleManager->UseTypingParaStyle(spans, caretPosition), true);

    richEditorPattern->SetTypingParagraphStyle(std::nullopt);
}

/**
 * @tc.name: UseTypingParaStyle002
 * @tc.desc: test UseTypingParaStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTypingStyleTest, UseTypingParaStyle002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    std::optional<struct UpdateParagraphStyle> typingParagraphStyle = UpdateParagraphStyle();
    richEditorPattern->SetTypingParagraphStyle(typingParagraphStyle);
    auto& styleManager = richEditorPattern->styleManager_;
    std::list<RefPtr<SpanItem>> spans;
    RichEditorChangeValue changeValue;
    // empty
    EXPECT_EQ(styleManager->HasTypingParagraphStyle(), true);
    EXPECT_EQ(styleManager->UseTypingParaStyle(spans, changeValue), true);

    // delete to empty
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    spans.push_back(spanItem);
    spanItem->content = u"123";
    spanItem->position = static_cast<int32_t>(spanItem->content.length());
    changeValue.rangeBefore_.start = 0;
    changeValue.rangeBefore_.end = 3;
    EXPECT_EQ(styleManager->UseTypingParaStyle(spans, changeValue), true);

    // insert in last new line
    spanItem->content = u"123\n";
    spanItem->position = static_cast<int32_t>(spanItem->content.length());
    changeValue.rangeBefore_.start = 4;
    changeValue.rangeBefore_.end = 4;
    EXPECT_EQ(styleManager->UseTypingParaStyle(spans, changeValue), true);

    richEditorPattern->SetTypingParagraphStyle(std::nullopt);
}

/**
 * @tc.name: UseStyleByTypingParagraphStyle001
 * @tc.desc: test UseTypingParaStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTypingStyleTest, UseStyleByTypingParagraphStyle001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->SetTypingParagraphStyle(TEST_TYPING_PARAGRAPH_STYLE);
    auto spanItem = AceType::MakeRefPtr<SpanItem>();

    auto& styleManager = richEditorPattern->styleManager_;
    EXPECT_EQ(styleManager->HasTypingParagraphStyle(), true);
    ASSERT_NE(spanItem->textLineStyle, nullptr);
    styleManager->UpdateStyleByTypingParagraphStyle(spanItem);
    auto textAlign = spanItem->textLineStyle->GetTextAlign();
    auto leadingMargin = spanItem->textLineStyle->GetLeadingMargin();
    auto wordBreak = spanItem->textLineStyle->GetWordBreak();
    auto lineBreakStrategy = spanItem->textLineStyle->GetLineBreakStrategy();
    auto paragraphSpacing = spanItem->textLineStyle->GetParagraphSpacing();
    ASSERT_EQ(textAlign.has_value(), true);
    ASSERT_EQ(leadingMargin.has_value(), true);
    ASSERT_EQ(wordBreak.has_value(), true);
    ASSERT_EQ(lineBreakStrategy.has_value(), true);
    ASSERT_EQ(paragraphSpacing.has_value(), true);

    EXPECT_EQ(textAlign.value(), TEST_TYPING_PARAGRAPH_STYLE.textAlign.value());
    EXPECT_EQ(leadingMargin.value(), TEST_TYPING_PARAGRAPH_STYLE.leadingMargin.value());
    EXPECT_EQ(wordBreak.value(), TEST_TYPING_PARAGRAPH_STYLE.wordBreak.value());
    EXPECT_EQ(lineBreakStrategy.value(), TEST_TYPING_PARAGRAPH_STYLE.lineBreakStrategy.value());
    EXPECT_EQ(paragraphSpacing.value(), TEST_TYPING_PARAGRAPH_STYLE.paragraphSpacing.value());

    richEditorPattern->SetTypingParagraphStyle(std::nullopt);
}

/**
 * @tc.name: UpdateTextStyleByTypingStyle001
 * @tc.desc: test UseTypingParaStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTypingStyleTest, UpdateTextStyleByTypingStyle001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->SetTypingStyle(TEST_TYPING_STYLE, std::nullopt);
    auto spanItem = AceType::MakeRefPtr<SpanItem>();

    auto& styleManager = richEditorPattern->styleManager_;
    EXPECT_EQ(styleManager->typingFontStyle_.has_value(), true);
    ASSERT_NE(spanItem->fontStyle, nullptr);
    styleManager->UpdateTextStyleByTypingStyle(spanItem);
    auto updateTextColor = spanItem->fontStyle->GetTextColor();
    auto updateFontSize = spanItem->fontStyle->GetFontSize();
    auto updateItalicFontStyle = spanItem->fontStyle->GetItalicFontStyle();
    auto updateFontWeight = spanItem->fontStyle->GetFontWeight();
    ASSERT_EQ(updateTextColor.has_value(), true);
    ASSERT_EQ(updateFontSize.has_value(), true);
    ASSERT_EQ(updateItalicFontStyle.has_value(), true);
    ASSERT_EQ(updateFontWeight.has_value(), true);

    EXPECT_EQ(updateTextColor.value(), TEST_TYPING_STYLE.updateTextColor.value());
    EXPECT_EQ(updateFontSize.value(), TEST_TYPING_STYLE.updateFontSize.value());
    EXPECT_EQ(updateItalicFontStyle.value(), TEST_TYPING_STYLE.updateItalicFontStyle.value());
    EXPECT_EQ(updateFontWeight.value(), TEST_TYPING_STYLE.updateFontWeight.value());

    richEditorPattern->SetTypingStyle(std::nullopt, std::nullopt);
}

/**
 * @tc.name: GetTypingStyle001
 * @tc.desc: test GetTypingStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTypingStyleTest, GetTypingStyle001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    /**
     * @tc.steps: step1. get typing style
     */
    richEditorPattern->SetTypingStyle(TEST_TYPING_STYLE, std::nullopt);

    /**
     * @tc.steps: step2. get typing style
     */
    auto typingStyleResult = richEditorController->GetTypingStyle();
    EXPECT_TRUE(typingStyleResult.has_value());
    auto textShadows = typingStyleResult->updateTextShadows;
    EXPECT_TRUE(textShadows.has_value());

    richEditorPattern->SetTypingStyle(std::nullopt, std::nullopt);
}
}