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

class RichEditorStyleTestNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
};

void RichEditorStyleTestNg::SetUp()
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

void RichEditorStyleTestNg::TearDown()
{
    richEditorNode_ = nullptr;
    MockParagraph::TearDown();
}

void RichEditorStyleTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

/**
 * @tc.name: TextbackgroundStyle001
 * @tc.desc: Test add span and get span with textBackgroundStyle.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyleTestNg, TextbackgroundStyle001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    /**
     * @tc.steps: step1. add span
     */
    TextStyle style;
    TextBackgroundStyle textBackgroundStyle;
    NG::BorderRadiusProperty borderRadius;
    borderRadius.radiusTopLeft = Dimension(5, OHOS::Ace::DimensionUnit::VP);
    borderRadius.radiusTopRight = Dimension(5, OHOS::Ace::DimensionUnit::VP);
    borderRadius.radiusBottomLeft = Dimension(5, OHOS::Ace::DimensionUnit::VP);
    borderRadius.radiusBottomRight = Dimension(5, OHOS::Ace::DimensionUnit::VP);
    textBackgroundStyle.backgroundColor = Color::RED;
    textBackgroundStyle.backgroundRadius = borderRadius;
    textBackgroundStyle.needCompareGroupId = false;
    style.SetTextBackgroundStyle(textBackgroundStyle);
    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    options.style = style;
    richEditorController->AddTextSpan(options);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    auto newSpan = AceType::DynamicCast<SpanNode>(contentNode->GetChildAtIndex(0));
    ASSERT_NE(newSpan, nullptr);
    EXPECT_TRUE(newSpan->GetTextBackgroundStyle().has_value());
    EXPECT_EQ(newSpan->GetTextBackgroundStyle().value(), textBackgroundStyle);
    
    /**
     * @tc.steps: step2. get span
     */
    auto info = richEditorController->GetSpansInfo(0, 1);
    auto spanTextBackground = info.selection_.resultObjects.front().textStyle.textBackgroundStyle;
    EXPECT_TRUE(spanTextBackground.has_value());
    EXPECT_EQ(spanTextBackground.value(), textBackgroundStyle);
}

/**
 * @tc.name: TextbackgroundStyle002
 * @tc.desc: Test set typing style with textBackgroundStyle.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyleTestNg, TextbackgroundStyle002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);

    /**
     * @tc.steps: step1. set typing style
     */
    TextStyle style;
    style.SetTextColor(TEXT_COLOR_VALUE);
    style.SetTextDecorationColor(TEXT_DECORATION_COLOR_VALUE);
    TextBackgroundStyle textBackgroundStyle;
    NG::BorderRadiusProperty borderRadius;
    borderRadius.radiusTopLeft = Dimension(5, OHOS::Ace::DimensionUnit::VP);
    borderRadius.radiusTopRight = Dimension(5, OHOS::Ace::DimensionUnit::VP);
    borderRadius.radiusBottomLeft = Dimension(5, OHOS::Ace::DimensionUnit::VP);
    borderRadius.radiusBottomRight = Dimension(5, OHOS::Ace::DimensionUnit::VP);
    textBackgroundStyle.backgroundColor = Color::RED;
    textBackgroundStyle.backgroundRadius = borderRadius;
    textBackgroundStyle.needCompareGroupId = false;
    style.SetTextBackgroundStyle(textBackgroundStyle);
    UpdateSpanStyle typingStyle;
    typingStyle.updateTextColor = TEXT_COLOR_VALUE;
    typingStyle.updateTextDecorationColor = TEXT_DECORATION_COLOR_VALUE;
    typingStyle.updateTextBackgroundStyle = textBackgroundStyle;
    richEditorController->SetTypingStyle(typingStyle, style);
    
    /**
     * @tc.steps: step2. get typing style
     */
    auto typingStyleResult = richEditorController->GetTypingStyle();
    EXPECT_TRUE(typingStyleResult.has_value());
    auto backgroundResult = typingStyleResult->updateTextBackgroundStyle;
    EXPECT_TRUE(backgroundResult.has_value());
    EXPECT_EQ(backgroundResult.value(), textBackgroundStyle);

    /**
     * @tc.steps: step3. insert value
     */
    richEditorPattern->caretPosition_ = 0;
    richEditorPattern->InsertValue(INIT_VALUE_1);
    auto newSpan = AceType::DynamicCast<SpanNode>(contentNode->GetChildAtIndex(0));
    ASSERT_NE(newSpan, nullptr);
    EXPECT_TRUE(newSpan->GetTextBackgroundStyle().has_value());
    EXPECT_EQ(newSpan->GetTextBackgroundStyle().value(), textBackgroundStyle);
    richEditorPattern->caretPosition_ = 6;
    richEditorPattern->InsertValue(INIT_VALUE_2);
    EXPECT_EQ(contentNode->GetChildren().size(), 1);
}

/**
 * @tc.name: TextbackgroundStyle003
 * @tc.desc: Test update span style with textBackgroundStyle.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyleTestNg, TextbackgroundStyle003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);

    /**
     * @tc.steps: step1. add span
     */
    TextStyle style;
    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    options.style = style;
    richEditorController->AddTextSpan(options);
    EXPECT_EQ(richEditorNode_->GetChildren().size(), 1);

    /**
     * @tc.steps: step2. update span style
     */
    TextBackgroundStyle textBackgroundStyle;
    NG::BorderRadiusProperty borderRadius;
    borderRadius.radiusTopLeft = Dimension(5, OHOS::Ace::DimensionUnit::VP);
    borderRadius.radiusTopRight = Dimension(5, OHOS::Ace::DimensionUnit::VP);
    borderRadius.radiusBottomLeft = Dimension(5, OHOS::Ace::DimensionUnit::VP);
    borderRadius.radiusBottomRight = Dimension(5, OHOS::Ace::DimensionUnit::VP);
    textBackgroundStyle.backgroundColor = Color::RED;
    textBackgroundStyle.backgroundRadius = borderRadius;
    textBackgroundStyle.needCompareGroupId = false;
    style.SetTextBackgroundStyle(textBackgroundStyle);
    struct UpdateSpanStyle updateSpanStyle;
    updateSpanStyle.updateTextBackgroundStyle = textBackgroundStyle;
    richEditorController->SetUpdateSpanStyle(updateSpanStyle);
    ImageSpanAttribute imageStyle;
    richEditorController->UpdateSpanStyle(0, 2, style, imageStyle);
    EXPECT_EQ(contentNode->GetChildren().size(), 2);
    auto newSpan = AceType::DynamicCast<SpanNode>(contentNode->GetChildAtIndex(0));
    ASSERT_NE(newSpan, nullptr);
    EXPECT_TRUE(newSpan->GetTextBackgroundStyle().has_value());
    EXPECT_EQ(newSpan->GetTextBackgroundStyle().value(), textBackgroundStyle);

    richEditorController->UpdateSpanStyle(0, 2, style, imageStyle);
    newSpan = AceType::DynamicCast<SpanNode>(contentNode->GetChildAtIndex(0));
    ASSERT_NE(newSpan, nullptr);
    EXPECT_TRUE(newSpan->GetTextBackgroundStyle().has_value());
    EXPECT_EQ(newSpan->GetTextBackgroundStyle().value().groupId, newSpan->groupId_);
}

/**
 * @tc.name: TextbackgroundStyle004
 * @tc.desc: Test toStyledString and fromStyledString with textBackgroundStyle.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyleTestNg, TextbackgroundStyle004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    /**
     * @tc.steps: step1. add span
     */
    TextStyle style;
    TextBackgroundStyle textBackgroundStyle;
    NG::BorderRadiusProperty borderRadius;
    borderRadius.radiusTopLeft = Dimension(5, OHOS::Ace::DimensionUnit::VP);
    borderRadius.radiusTopRight = Dimension(5, OHOS::Ace::DimensionUnit::VP);
    borderRadius.radiusBottomLeft = Dimension(5, OHOS::Ace::DimensionUnit::VP);
    borderRadius.radiusBottomRight = Dimension(5, OHOS::Ace::DimensionUnit::VP);
    textBackgroundStyle.backgroundColor = Color::RED;
    textBackgroundStyle.backgroundRadius = borderRadius;
    textBackgroundStyle.needCompareGroupId = false;
    style.SetTextBackgroundStyle(textBackgroundStyle);
    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    options.style = style;
    richEditorController->AddTextSpan(options);
    EXPECT_EQ(richEditorNode_->GetChildren().size(), 1);

    /**
     * @tc.steps: step2. toStyledString
     */
    auto spanString = richEditorPattern->ToStyledString(0, 6);
    ASSERT_NE(spanString, nullptr);
    auto spans = spanString->GetSpans(0, 6, SpanType::BackgroundColor);
    EXPECT_EQ(spans.size(), 1);
    auto backgroundSpan = AceType::DynamicCast<BackgroundColorSpan>(spans[0]);
    EXPECT_NE(backgroundSpan, nullptr);
    EXPECT_EQ(backgroundSpan->GetBackgroundColor(), textBackgroundStyle);

    /**
     * @tc.steps: step3. fromStyledString
     */
    auto info = richEditorPattern->FromStyledString(spanString);
    EXPECT_EQ(info.selection_.resultObjects.size(), 1);
    auto spanTextBackground = info.selection_.resultObjects.front().textStyle.textBackgroundStyle;
    EXPECT_TRUE(spanTextBackground.has_value());
    EXPECT_EQ(spanTextBackground.value(), textBackgroundStyle);
}

/**
 * @tc.name: TestRichEditorHandleSelectFontStyleWrapper001
 * @tc.desc: test HandleSelectFontStyleWrapper
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyleTestNg, TestRichEditorHandleSelectFontStyleWrapper001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and init variables and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    TextStyle spanStyle;
    KeyCode code = KeyCode::KEY_UNKNOWN;
    richEditorPattern->HandleSelectFontStyleWrapper(code, spanStyle);
    EXPECT_EQ(spanStyle.GetFontWeight(), FontWeight::NORMAL);
}

/**
 * @tc.name: TestRichEditorHandleSelectFontStyle001
 * @tc.desc: test HandleSelectFontStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyleTestNg, TestRichEditorHandleSelectFontStyle001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and init variables and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->isSpanStringMode_ = true;
    KeyCode code = KeyCode::KEY_UNKNOWN;
    richEditorPattern->HandleSelectFontStyle(code);
    EXPECT_EQ(richEditorPattern->isSpanStringMode_, true);
}

/**
 * @tc.name: UpdateTextStyle001
 * @tc.desc: test update span style
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyleTestNg, UpdateTextStyle001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    AddSpan(INIT_VALUE_1);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    auto newSpan1 = AceType::DynamicCast<SpanNode>(contentNode->GetChildAtIndex(0));
    TextStyle textStyle;
    ImageSpanAttribute imageStyle;
    textStyle.SetFontFeatures(TEXT_FONTFEATURE);
    textStyle.SetLineHeight(LINE_HEIGHT_VALUE);
    textStyle.SetLetterSpacing(LETTER_SPACING);

    struct UpdateSpanStyle updateSpanStyle;
    updateSpanStyle.updateLineHeight = LINE_HEIGHT_VALUE;
    updateSpanStyle.updateLetterSpacing = LETTER_SPACING;
    updateSpanStyle.updateFontFeature = TEXT_FONTFEATURE;

    richEditorPattern->UpdateTextStyle(newSpan1, updateSpanStyle, textStyle);
    ASSERT_NE(newSpan1, nullptr);
    EXPECT_EQ(newSpan1->GetLineHeight(), LINE_HEIGHT_VALUE);
    EXPECT_EQ(newSpan1->GetLetterSpacing(), LETTER_SPACING);
    for (const auto& pair : *newSpan1->GetFontFeature()) {
        EXPECT_EQ(pair.first, "subs");
        EXPECT_EQ(pair.second, 1);
    }
    ClearSpan();
}

/**
 * @tc.name: UpdateTextStyle002
 * @tc.desc: test update span style
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyleTestNg, UpdateTextStyle002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    AddSpan(INIT_VALUE_1);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    auto newSpan1 = AceType::DynamicCast<SpanNode>(contentNode->GetChildAtIndex(0));
    TextStyle textStyle;
    ImageSpanAttribute imageStyle;
    textStyle.SetFontFeatures(TEXT_FONTFEATURE_2);
    struct UpdateSpanStyle updateSpanStyle;
    updateSpanStyle.updateFontFeature = TEXT_FONTFEATURE;
    richEditorPattern->UpdateTextStyle(newSpan1, updateSpanStyle, textStyle);
    ASSERT_NE(newSpan1, nullptr);
    for (const auto& pair : *newSpan1->GetFontFeature()) {
        EXPECT_EQ(pair.first, "subs");
        EXPECT_EQ(pair.second, 0);
    }
    ClearSpan();
}

/**
 * @tc.name: SetTypingStyle001
 * @tc.desc: test Typing Style
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyleTestNg, SetTypingStyle001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richEditor controller
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    TextStyle style;
    style.SetLineHeight(LINE_HEIGHT_VALUE);
    style.SetLetterSpacing(LETTER_SPACING);
    style.SetFontFeatures(TEXT_FONTFEATURE);
    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    options.style = style;
    richEditorController->AddTextSpan(options);
    AddSpan(INIT_VALUE_1);
    auto info = richEditorController->GetSpansInfo(1, 5);
    ASSERT_NE(info.selection_.resultObjects.size(), 0);
    TextStyleResult textStyle1 = info.selection_.resultObjects.front().textStyle;
    UpdateSpanStyle typingStyle;
    richEditorPattern->SetTypingStyle(typingStyle, style);
    TextSpanOptions options1;
    options1.style = richEditorPattern->typingTextStyle_;
    AddSpan(INIT_VALUE_1);
    auto info1 = richEditorController->GetSpansInfo(1, 5);
    ASSERT_NE(info1.selection_.resultObjects.size(), 0);
    TextStyleResult textStyle2 = info1.selection_.resultObjects.front().textStyle;
    EXPECT_EQ(textStyle2.lineHeight, LINE_HEIGHT_VALUE.ConvertToVp());
    EXPECT_EQ(textStyle2.letterSpacing, LETTER_SPACING.ConvertToVp());
    for (const auto& pair : textStyle1.fontFeature) {
        EXPECT_EQ(pair.first, "subs");
        EXPECT_EQ(pair.second, 1);
    }
    ClearSpan();
}

/**
 * @tc.name: SetTypingStyle002
 * @tc.desc: test Typing Style
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyleTestNg, SetTypingStyle002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richEditor controller
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    TextStyle style;
    style.SetFontFeatures(TEXT_FONTFEATURE_2);
    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    options.style = style;
    richEditorController->AddTextSpan(options);
    auto info = richEditorController->GetSpansInfo(1, 5);
    ASSERT_NE(info.selection_.resultObjects.size(), 0);
    TextStyleResult textStyle1 = info.selection_.resultObjects.front().textStyle;
    UpdateSpanStyle typingStyle;
    richEditorPattern->SetTypingStyle(typingStyle, style);
    TextSpanOptions options1;
    options1.style = richEditorPattern->typingTextStyle_;
    auto info1 = richEditorController->GetSpansInfo(1, 5);
    ASSERT_NE(info1.selection_.resultObjects.size(), 0);
    TextStyleResult textStyle2 = info1.selection_.resultObjects.front().textStyle;
    for (const auto& pair : textStyle1.fontFeature) {
        EXPECT_EQ(pair.first, "subs");
        EXPECT_EQ(pair.second, 0);
    }
    ClearSpan();
}

/**
 * @tc.name: SetTypingStyle003
 * @tc.desc: test SetTypingStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyleTestNg, SetTypingStyle003, TestSize.Level0)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    UpdateSpanStyle typingStyle;
    TextStyle textStyle;
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    richEditorPattern->spans_.emplace_back(spanItem);
    richEditorPattern->previewTextRecord_.previewContent = u"";
    auto layout = richEditorNode_->layoutProperty_;
    richEditorPattern->SetTypingStyle(typingStyle, textStyle);
    EXPECT_TRUE(layout == richEditorNode_->layoutProperty_);
}

/**
 * @tc.name: UpdateCaretStyleByTypingStyleTest001
 * @tc.desc: test SetTypingStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyleTestNg, UpdateCaretStyleByTypingStyleTest001, TestSize.Level0)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->UpdateCaretStyleByTypingStyle(false);
    richEditorPattern->UpdateCaretStyleByTypingStyle(true);
}

/**
 * @tc.name: HasSameTypingStyle001
 * @tc.desc: test HasSameTypingStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyleTestNg, HasSameTypingStyle001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);
    richEditorPattern->caretPosition_ = 0;
    richEditorPattern->InsertValue(TEST_INSERT_VALUE);
    auto it = AceType::DynamicCast<SpanNode>(contentNode->GetLastChild());
    ASSERT_NE(it, nullptr);
    auto spanItem = it->GetSpanItem();

    spanItem->textStyle_ = std::nullopt;
    richEditorPattern->typingTextStyle_ = std::nullopt;
    auto ret = richEditorPattern->HasSameTypingStyle(it);
    EXPECT_TRUE(ret);

    spanItem->textStyle_ = TextStyle();
    richEditorPattern->typingTextStyle_ = std::nullopt;
    ret = richEditorPattern->HasSameTypingStyle(it);
    EXPECT_FALSE(ret);

    spanItem->textStyle_ = std::nullopt;
    richEditorPattern->typingTextStyle_ = TextStyle();
    ret = richEditorPattern->HasSameTypingStyle(it);
    EXPECT_FALSE(ret);

    spanItem->textStyle_ = TextStyle();
    richEditorPattern->typingTextStyle_ = TextStyle();
    ret = richEditorPattern->HasSameTypingStyle(it);
    EXPECT_TRUE(ret);

    spanItem->textStyle_.value().propFontFamilies_.push_back("test1");
    ret = richEditorPattern->HasSameTypingStyle(it);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: GetChangeSpanStyle001
 * @tc.desc: test GetChangeSpanStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyleTestNg, GetChangeSpanStyle001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init and call function.
    */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    struct UpdateParagraphStyle paragraphStyle;
    paragraphStyle.textAlign = TextAlign::END;
    paragraphStyle.leadingMargin = std::make_optional<NG::LeadingMargin>();
    paragraphStyle.leadingMargin->size = LeadingMarginSize(Dimension(5.0), Dimension(10.0));
    richEditorPattern->UpdateParagraphStyle(0, 6, paragraphStyle);
    std::optional<struct UpdateParagraphStyle> spanParaStyle = paragraphStyle;

    RichEditorChangeValue changeValue;
    RichEditorAbstractSpanResult span1;
    changeValue.originalSpans_.emplace_back(span1);
    RichEditorAbstractSpanResult span2;
    changeValue.originalSpans_.emplace_back(span2);

    RichEditorAbstractSpanResult& firstInfo = changeValue.originalSpans_.front();
    int32_t firstLength = static_cast<int32_t>(firstInfo.GetValue().length());
    firstInfo.SetEraseLength(firstLength);
    RichEditorAbstractSpanResult& lastInfo = changeValue.originalSpans_.back();
    int32_t lastLength = static_cast<int32_t>(lastInfo.GetValue().length());
    lastInfo.SetEraseLength(lastLength);

    std::optional<TextStyle> spanTextStyle;
    RefPtr<SpanNode> spanNode = OHOS::Ace::NG::SpanNode::CreateSpanNode(1);
    int32_t spanIndex = 0;
    richEditorPattern->spans_.clear();
    OHOS::Ace::RefPtr<OHOS::Ace::NG::SpanItem> spanItem1 = AceType::MakeRefPtr<ImageSpanItem>();
    richEditorPattern->spans_.emplace_back(spanItem1);
    OHOS::Ace::RefPtr<OHOS::Ace::NG::SpanItem> spanItem2 = AceType::MakeRefPtr<PlaceholderSpanItem>();
    richEditorPattern->spans_.emplace_back(spanItem2);
    std::optional<std::u16string> urlAddress;
    richEditorPattern->GetChangeSpanStyle(changeValue, spanTextStyle, spanParaStyle, urlAddress, spanNode, spanIndex);
    EXPECT_FALSE(spanTextStyle.has_value());
    /**
     * @tc.steps: step2. change parameter and call function.
    */
    OHOS::Ace::RefPtr<OHOS::Ace::NG::SpanItem> spanItem3 = AceType::MakeRefPtr<ImageSpanItem>();
    richEditorPattern->spans_.emplace_back(spanItem3);
    lastInfo.SetSpanIndex(richEditorPattern->spans_.size() - 1);
    richEditorPattern->GetChangeSpanStyle(changeValue, spanTextStyle, spanParaStyle, urlAddress, spanNode, spanIndex);
    EXPECT_FALSE(spanTextStyle.has_value());
    /**
     * @tc.steps: step4. change parameter and call function.
    */
    lastInfo.SetEraseLength(lastLength - 1);
    richEditorPattern->GetChangeSpanStyle(changeValue, spanTextStyle, spanParaStyle, urlAddress, spanNode, spanIndex);
    EXPECT_FALSE(spanTextStyle.has_value());
}

/**
 * @tc.name: GetChangeSpanStyle002
 * @tc.desc: test GetChangeSpanStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyleTestNg, GetChangeSpanStyle002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    struct UpdateParagraphStyle paragraphStyle;
    paragraphStyle.textAlign = TextAlign::END;
    paragraphStyle.leadingMargin = std::make_optional<NG::LeadingMargin>();
    paragraphStyle.leadingMargin->size = LeadingMarginSize(Dimension(5.0), Dimension(10.0));
    richEditorPattern->UpdateParagraphStyle(0, 6, paragraphStyle);
    std::optional<struct UpdateParagraphStyle> spanParaStyle = paragraphStyle;

    RichEditorChangeValue changeValue;
    RichEditorAbstractSpanResult span1;
    changeValue.originalSpans_.emplace_back(span1);
    RichEditorAbstractSpanResult span2;
    changeValue.originalSpans_.emplace_back(span2);

    RichEditorAbstractSpanResult& firstInfo = changeValue.originalSpans_.front();
    int32_t firstLength = static_cast<int32_t>(firstInfo.GetValue().length());
    firstInfo.SetEraseLength(firstLength);
    RichEditorAbstractSpanResult& lastInfo = changeValue.originalSpans_.back();
    int32_t lastLength = static_cast<int32_t>(lastInfo.GetValue().length());
    lastInfo.SetEraseLength(lastLength);

    std::optional<TextStyle> spanTextStyle;
    RefPtr<SpanNode> spanNode = OHOS::Ace::NG::SpanNode::CreateSpanNode(1);
    int32_t spanIndex = 0;
    richEditorPattern->spans_.clear();
    OHOS::Ace::RefPtr<OHOS::Ace::NG::SpanItem> spanItem1 = AceType::MakeRefPtr<ImageSpanItem>();
    richEditorPattern->spans_.emplace_back(spanItem1);
    OHOS::Ace::RefPtr<OHOS::Ace::NG::SpanItem> spanItem2 = AceType::MakeRefPtr<PlaceholderSpanItem>();
    richEditorPattern->spans_.emplace_back(spanItem2);
    OHOS::Ace::RefPtr<OHOS::Ace::NG::SpanItem> spanItem3 = AceType::MakeRefPtr<ImageSpanItem>();
    richEditorPattern->spans_.emplace_back(spanItem3);
    /**
     * @tc.steps: step2. change parameter and call function.
     */
    lastInfo.SetSpanIndex(richEditorPattern->spans_.size() - 2);
    std::optional<std::u16string> urlAddress;
    richEditorPattern->GetChangeSpanStyle(changeValue, spanTextStyle, spanParaStyle, urlAddress, spanNode, spanIndex);
    EXPECT_FALSE(spanTextStyle.has_value());
    CHECK_NULL_VOID(richEditorPattern->spans_.empty());
    auto firstSpanItem = richEditorPattern->spans_.front();
    CHECK_NULL_VOID(firstSpanItem);
    EXPECT_FALSE(firstSpanItem->urlAddress.has_value());
}

/**
 * @tc.name: HandleSelectFontStyleWrapper001
 * @tc.desc: test HandleSelectFontStyleWrapper
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyleTestNg, HandleSelectFontStyleWrapper001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and init variables and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    KeyCode code;
    TextStyle spanStyle;
    /**
     * @tc.steps: step2. change parameters and call function.
     */
    code = KeyCode::KEY_B;
    spanStyle.SetFontWeight(Ace::FontWeight::BOLD);
    richEditorPattern->HandleSelectFontStyleWrapper(code, spanStyle);
    EXPECT_EQ(spanStyle.GetFontWeight(), Ace::FontWeight::NORMAL);
    /**
     * @tc.steps: step3. change parameters and call function.
     */
    spanStyle.SetFontWeight(Ace::FontWeight::NORMAL);
    code = KeyCode::KEY_I;
    spanStyle.SetFontStyle(OHOS::Ace::FontStyle::ITALIC);
    richEditorPattern->HandleSelectFontStyleWrapper(code, spanStyle);
    EXPECT_EQ(spanStyle.GetFontStyle(), OHOS::Ace::FontStyle::NORMAL);
    /**
     * @tc.steps: step4. change parameters and call function.
     */
    spanStyle.SetFontStyle(OHOS::Ace::FontStyle::NORMAL);
    code = KeyCode::KEY_U;
    spanStyle.SetTextDecoration(TextDecoration::UNDERLINE);
    richEditorPattern->HandleSelectFontStyleWrapper(code, spanStyle);
    EXPECT_EQ(spanStyle.GetTextDecorationFirst(), TextDecoration::NONE);
}

/**
 * @tc.name: HandleSelectFontStyleWrapper002
 * @tc.desc: test HandleSelectFontStyleWrapper
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyleTestNg, HandleSelectFontStyleWrapper002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);
    KeyCode code = KeyCode::KEY_B;
    TextStyle spanStyle;
    spanStyle.fontWeight_ = Ace::FontWeight::BOLD;
    richEditorPattern->HandleSelectFontStyleWrapper(code, spanStyle);
    EXPECT_EQ(spanStyle.GetFontWeight(), Ace::FontWeight::NORMAL);
}

/**
 * @tc.name: HandleSelectFontStyleWrapper003
 * @tc.desc: test HandleSelectFontStyleWrapper
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyleTestNg, HandleSelectFontStyleWrapper003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);
    KeyCode code = KeyCode::KEY_I;
    TextStyle spanStyle;
    spanStyle.propFontStyle_ = OHOS::Ace::FontStyle::ITALIC;
    richEditorPattern->HandleSelectFontStyleWrapper(code, spanStyle);
    EXPECT_EQ(spanStyle.GetFontStyle(), OHOS::Ace::FontStyle::NORMAL);
}

/**
 * @tc.name: HandleSelectFontStyleWrapper004
 * @tc.desc: test HandleSelectFontStyleWrapper
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyleTestNg, HandleSelectFontStyleWrapper004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);
    KeyCode code = KeyCode::KEY_U;
    TextStyle spanStyle;
    spanStyle.propTextDecoration_ = std::vector<TextDecoration>({TextDecoration::UNDERLINE});
    richEditorPattern->HandleSelectFontStyleWrapper(code, spanStyle);
    EXPECT_EQ(spanStyle.GetTextDecorationFirst(), TextDecoration::NONE);
}

/**
 * @tc.name: HandleSelectFontStyleWrapper005
 * @tc.desc: test HandleSelectFontStyleWrapper
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyleTestNg, HandleSelectFontStyleWrapper005, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    KeyCode code = KeyCode::KEY_B;
    TextStyle style;
    style.SetFontWeight(Ace::FontWeight::NORMAL);
    richEditorPattern->HandleSelectFontStyleWrapper(code, style);
    EXPECT_EQ(style.GetFontWeight(), Ace::FontWeight::BOLD);
}

/**
 * @tc.name: HandleSelectFontStyleWrapper006
 * @tc.desc: test HandleSelectFontStyleWrapper
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyleTestNg, HandleSelectFontStyleWrapper006, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    KeyCode code = KeyCode::KEY_I;
    TextStyle style;
    style.SetFontStyle(OHOS::Ace::FontStyle::NORMAL);
    richEditorPattern->HandleSelectFontStyleWrapper(code, style);
    EXPECT_EQ(style.GetFontStyle(), OHOS::Ace::FontStyle::ITALIC);
}

/**
 * @tc.name: HandleSelectFontStyleWrapper003
 * @tc.desc: test HandleSelectFontStyleWrapper
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyleTestNg, HandleSelectFontStyleWrapper007, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    KeyCode code = KeyCode::KEY_U;
    TextStyle style;
    style.SetTextDecoration(TextDecoration::NONE);
    richEditorPattern->HandleSelectFontStyleWrapper(code, style);
    EXPECT_EQ(style.GetTextDecorationFirst(), TextDecoration::UNDERLINE);
}

/**
 * @tc.name: HandleSelectFontStyleWrapper004
 * @tc.desc: test HandleSelectFontStyleWrapper
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyleTestNg, HandleSelectFontStyleWrapper008, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    KeyCode code = KeyCode::KEY_HEADSETHOOK;
    TextStyle style;
    FontWeight result1 = style.GetFontWeight();
    TextDecoration result3 = style.GetTextDecorationFirst();
    richEditorPattern->HandleSelectFontStyleWrapper(code, style);
    EXPECT_EQ(style.GetFontWeight(), result1);
    EXPECT_EQ(style.GetTextDecorationFirst(), result3);
}

/**
 * @tc.name: SetTextStyleToRet001
 * @tc.desc: test SetTextStyleToRet
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyleTestNg, SetTextStyleToRet001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    RichEditorAbstractSpanResult retInfo;
    TextStyle textStyle;
    textStyle.propFontFamilies_.emplace_back(TEST_STR);
    textStyle.propFontFamilies_.emplace_back(TEST_STR);
    textStyle.propFontFamilies_.emplace_back(TEST_STR);
    richEditorPattern->SetTextStyleToRet(retInfo, textStyle);
    EXPECT_EQ(retInfo.GetFontSize(), textStyle.GetFontSize().ConvertToVp());
}

/**
 * @tc.name: HandleSelectFontStyle001
 * @tc.desc: test HandleSelectFontStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyleTestNg, HandleSelectFontStyle001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->textSelector_.baseOffset = -2;
    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->HandleSelectFontStyle(KeyCode::KEY_SEARCH);
    EXPECT_TRUE(richEditorPattern->textSelector_.SelectNothing());
}

/**
 * @tc.name: HandleSelectFontStyle002
 * @tc.desc: test HandleSelectFontStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyleTestNg, HandleSelectFontStyle002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->isSpanStringMode_ = false;
    KeyCode code = KeyCode::KEY_UNKNOWN;
    richEditorPattern->HandleSelectFontStyle(code);
    EXPECT_EQ(richEditorPattern->isSpanStringMode_, false);
}

/**
 * @tc.name: GetTextStyleBySpanItem001
 * @tc.desc: test GetTextStyleBySpanItem
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyleTestNg, GetTextStyleBySpanItem001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    spanItem->fontStyle = nullptr;
    spanItem->textLineStyle = nullptr;
    richEditorPattern->GetTextStyleBySpanItem(spanItem);
    ASSERT_EQ(spanItem->fontStyle, nullptr);
}

/**
 * @tc.name: GetImageStyleBySpanItem001
 * @tc.desc: test GetImageStyleBySpanItem
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyleTestNg, GetImageStyleBySpanItem001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto spanItem1 = AceType::MakeRefPtr<ImageSpanItem>();
    ImageSpanAttribute imageStyle;
    std::optional<Ace::NG::MarginProperty> marginProp = std::nullopt;
    std::optional<Ace::NG::BorderRadiusProperty> borderRadius = std::nullopt;
    marginProp = { CALC_LENGTH_CALC, CALC_LENGTH_CALC, CALC_LENGTH_CALC, CALC_LENGTH_CALC };
    borderRadius = { CALC_TEST, CALC_TEST, CALC_TEST, CALC_TEST };
    imageStyle.marginProp = marginProp;
    imageStyle.borderRadius = borderRadius;
    ImageSpanSize imageSize;
    CalcDimension imageSpanWidth;
    CalcDimension imageSpanHeight;
    imageSize.width = imageSpanWidth;
    imageSize.height = imageSpanHeight;
    imageStyle.size = imageSize;
    imageStyle.verticalAlign = VerticalAlign::TOP;
    imageStyle.objectFit = ImageFit::COVER;
    ImageSpanOptions option;
    option.imageAttribute = imageStyle;
    spanItem1->options = option;
    richEditorPattern->GetImageStyleBySpanItem(spanItem1);

    auto spanItem2 = AceType::MakeRefPtr<ImageSpanItem>();
    ImageSpanAttribute imageStyle2;
    ImageSpanOptions option2;
    option2.imageAttribute = imageStyle2;
    spanItem2->options = option2;
    richEditorPattern->GetImageStyleBySpanItem(spanItem2);

    ASSERT_EQ(spanItem1->options.imageAttribute.has_value(), true);
}

/**
 * @tc.name: GetImageStyleBySpanItem002
 * @tc.desc: test GetImageStyleBySpanItem
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyleTestNg, GetImageStyleBySpanItem002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    ImageSpanAttribute imageStyle;
    std::optional<Ace::NG::MarginProperty> marginProp = std::nullopt;
    std::optional<Ace::NG::BorderRadiusProperty> borderRadius = std::nullopt;
    marginProp = { CALC_LENGTH_CALC, CALC_LENGTH_CALC, CALC_LENGTH_CALC, CALC_LENGTH_CALC };
    borderRadius = { CALC_TEST, CALC_TEST, CALC_TEST, CALC_TEST };
    imageStyle.marginProp = marginProp;
    imageStyle.borderRadius = borderRadius;
    ImageSpanSize imageSize;
    imageSize.height = 1;
    imageStyle.size = imageSize;
    imageStyle.verticalAlign = VerticalAlign::TOP;
    imageStyle.objectFit = ImageFit::COVER;

    auto spanItem = AceType::MakeRefPtr<ImageSpanItem>();
    ImageSpanOptions option;
    option.imageAttribute = imageStyle;
    spanItem->options = option;
    auto imageSizeOp = spanItem->options.imageAttribute->size;
    auto ret = richEditorPattern->GetImageStyleBySpanItem(spanItem);
    EXPECT_NE(ret.size[RichEditorImageSize::SIZEHEIGHT], imageSizeOp->height->ConvertToPx());
}

/**
 * @tc.name: GetImageStyleBySpanItem003
 * @tc.desc: test GetImageStyleBySpanItem
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyleTestNg, GetImageStyleBySpanItem003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    ImageSpanAttribute imageStyle;
    std::optional<Ace::NG::MarginProperty> marginProp = std::nullopt;
    std::optional<Ace::NG::BorderRadiusProperty> borderRadius = std::nullopt;
    marginProp = { CALC_LENGTH_CALC, CALC_LENGTH_CALC, CALC_LENGTH_CALC, CALC_LENGTH_CALC };
    borderRadius = { CALC_TEST, CALC_TEST, CALC_TEST, CALC_TEST };
    imageStyle.marginProp = marginProp;
    imageStyle.borderRadius = borderRadius;
    ImageSpanSize imageSize;
    imageSize.width = 1;
    imageStyle.size = imageSize;
    imageStyle.verticalAlign = VerticalAlign::TOP;
    imageStyle.objectFit = ImageFit::COVER;

    auto spanItem = AceType::MakeRefPtr<ImageSpanItem>();
    ImageSpanOptions option;
    option.imageAttribute = imageStyle;
    spanItem->options = option;
    auto imageSizeOp = spanItem->options.imageAttribute->size;
    auto ret = richEditorPattern->GetImageStyleBySpanItem(spanItem);
    EXPECT_NE(ret.size[RichEditorImageSize::SIZEWIDTH], imageSizeOp->width->ConvertToPx());
}

/**
 * @tc.name: CopyTextSpanLineStyle001
 * @tc.desc: test CopyTextSpanLineStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyleTestNg, CopyTextSpanLineStyle001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    LeadingMargin margin;
    RefPtr<SpanNode> source = OHOS::Ace::NG::SpanNode::CreateSpanNode(1);
    RefPtr<SpanNode> target = OHOS::Ace::NG::SpanNode::CreateSpanNode(2);
    source->UpdateLeadingMargin(margin);

    richEditorPattern->CopyTextSpanLineStyle(source, target, false);
    richEditorPattern->CopyTextSpanLineStyle(source, target, true);
    ASSERT_EQ(richEditorPattern->spans_.empty(), true);

    margin.size = LeadingMarginSize(Dimension(5.0), Dimension(10.0));
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(voidPtr);
    ASSERT_NE(pixelMap, nullptr);
    margin.pixmap = pixelMap;
    source->UpdateLeadingMargin(margin);
    richEditorPattern->CopyTextSpanLineStyle(source, target, true);
    EXPECT_TRUE(target->HasLeadingMargin());
    auto leadingMargin = target->GetLeadingMarginValue({});
    ASSERT_NE(leadingMargin.pixmap, nullptr);

    richEditorPattern->CopyTextSpanLineStyle(source, target, false);
    EXPECT_TRUE(target->HasLeadingMargin());
    leadingMargin = target->GetLeadingMarginValue({});
    EXPECT_EQ(leadingMargin.pixmap, nullptr);
}

/**
 * @tc.name: CreateDecorationSpanByTextStyle001
 * @tc.desc: test RichEditorPattern CreateDecorationSpanByTextStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyleTestNg, CreateDecorationSpanByTextStyle001, TestSize.Level1)
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
    RefPtr<DecorationSpan> span = richEditorPattern->styleManager_->CreateDecorationSpanByTextStyle(updateSpanStyle, style, 0);
    ASSERT_NE(span, nullptr);
}

/**
 * @tc.name: UpdateImageStyle001
 * @tc.desc: test UpdateImageStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyleTestNg, UpdateImageStyle001, TestSize.Level1)
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
HWTEST_F(RichEditorStyleTestNg, SymbolSpanUpdateStyle001, TestSize.Level1)
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
 * @tc.name: SetSelectSpanStyle001
 * @tc.desc: test SetSelectSpanStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyleTestNg, SetSelectSpanStyle001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);
    int32_t start = 1;
    int32_t end = 4;
    KeyCode code = KeyCode::KEY_B;
    auto updateSpanStyle = richEditorPattern->GetUpdateSpanStyle();
    auto fontWeight = updateSpanStyle.updateFontWeight;
    richEditorPattern->UpdateSelectSpanStyle(start, end, code);
    richEditorPattern->UpdateSelectSpanStyle(start, end, code);
    EXPECT_NE(fontWeight, richEditorPattern->GetUpdateSpanStyle().updateFontWeight);
}

/**
 * @tc.name: SetSelectSpanStyle002
 * @tc.desc: test SetSelectSpanStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyleTestNg, SetSelectSpanStyle002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);
    int32_t start = 1;
    int32_t end = 4;
    KeyCode code = KeyCode::KEY_I;
    auto updateSpanStyle = richEditorPattern->GetUpdateSpanStyle();
    auto italicFontStyle = updateSpanStyle.updateItalicFontStyle;
    richEditorPattern->UpdateSelectSpanStyle(start, end, code);
    richEditorPattern->UpdateSelectSpanStyle(start, end, code);
    EXPECT_NE(italicFontStyle, richEditorPattern->GetUpdateSpanStyle().updateItalicFontStyle);
}

/**
 * @tc.name: SetSelectSpanStyle003
 * @tc.desc: test SetSelectSpanStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyleTestNg, SetSelectSpanStyle003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);
    int32_t start = 1;
    int32_t end = 4;
    KeyCode code = KeyCode::KEY_U;
    auto updateSpanStyle = richEditorPattern->GetUpdateSpanStyle();
    auto textDecoration = updateSpanStyle.updateTextDecoration;
    richEditorPattern->UpdateSelectSpanStyle(start, end, code);
    richEditorPattern->UpdateSelectSpanStyle(start, end, code);
    EXPECT_NE(textDecoration, richEditorPattern->GetUpdateSpanStyle().updateTextDecoration);
}

/**
 * @tc.name: SetSelectSpanStyle004
 * @tc.desc: test SetSelectSpanStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyleTestNg, SetSelectSpanStyle004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);
    int32_t start = 1;
    int32_t end = 4;
    KeyCode code = KeyCode::KEY_A;
    auto updateSpanStyle = richEditorPattern->GetUpdateSpanStyle();
    updateSpanStyle.updateTextDecoration = TextDecoration::NONE;
    richEditorPattern->UpdateSelectSpanStyle(start, end, code);
    richEditorPattern->UpdateSelectSpanStyle(start, end, code);
    EXPECT_EQ(TextDecoration::NONE, richEditorPattern->GetUpdateSpanStyle().updateTextDecoration);
}

/**
 * @tc.name: SetSelectSpanStyle005
 * @tc.desc: test SetSelectSpanStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyleTestNg, SetSelectSpanStyle005, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    int32_t start = 1;
    int32_t end = 4;
    KeyCode code = KeyCode::KEY_B;
    bool isStart = true;
    richEditorPattern->SetSelectSpanStyle(start, end, code, isStart);
    EXPECT_TRUE(richEditorPattern->spans_.empty());

    AddSpan(INIT_VALUE_1);
    richEditorPattern->spans_.front()->textStyle_ = TextStyle(1);
    auto size = richEditorPattern->spans_.front()->textStyle_->GetFontSize();
    richEditorPattern->SetSelectSpanStyle(start, end, code, isStart);
    EXPECT_EQ(size, richEditorPattern->GetUpdateSpanStyle().updateFontSize);
}

/**
 * @tc.name: UpdateDecorationStyle001
 * @tc.desc: test UpdateDecorationStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyleTestNg, UpdateDecorationStyle001, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto spanNode = AceType::MakeRefPtr<SpanNode>(0);
    auto spanItem = spanNode->GetSpanItem();
    TextStyle textStyle;
    struct UpdateSpanStyle updateSpanStyle;
    updateSpanStyle.updateTextDecoration = TextDecoration::UNDERLINE;
    richEditorPattern->UpdateDecoration(spanNode, updateSpanStyle, textStyle);
    EXPECT_EQ(spanItem->useThemeDecorationColor, true);

    updateSpanStyle.updateTextDecorationStyle = TextDecorationStyle::SOLID;
    richEditorPattern->UpdateDecoration(spanNode, updateSpanStyle, textStyle);
    EXPECT_EQ(spanItem->useThemeDecorationColor, true);

    updateSpanStyle.updateTextDecorationColor = Color::RED;
    richEditorPattern->UpdateDecoration(spanNode, updateSpanStyle, textStyle);
    EXPECT_EQ(spanItem->useThemeDecorationColor, false);
}

/**
 * @tc.name: UpdateDecoration001
 * @tc.desc: test UpdateDecoration
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyleTestNg, UpdateDecoration001, TestSize.Level1)
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
 * @tc.name: UpdateDecorationStyle002
 * @tc.desc: test UpdateDecorationStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyleTestNg, UpdateDecorationStyle002, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto spanNode = AceType::MakeRefPtr<SpanNode>(0);
    auto spanItem = spanNode->GetSpanItem();
    TextStyle textStyle;
    struct UpdateSpanStyle updateSpanStyle;

    updateSpanStyle.updateTextDecoration = TextDecoration::OVERLINE;
    richEditorPattern->UpdateDecoration(spanNode, updateSpanStyle, textStyle);
    EXPECT_EQ(spanItem->useThemeDecorationColor, true);

    updateSpanStyle.updateTextDecorationStyle = TextDecorationStyle::DOTTED;
    richEditorPattern->UpdateDecoration(spanNode, updateSpanStyle, textStyle);
    EXPECT_EQ(spanItem->useThemeDecorationColor, true);

    updateSpanStyle.updateTextDecorationColor = Color::RED;
    richEditorPattern->UpdateDecoration(spanNode, updateSpanStyle, textStyle);
    EXPECT_EQ(spanItem->useThemeDecorationColor, false);

    updateSpanStyle.updateLineThicknessScale = LINE_THICKNESS_SCALE;
    textStyle.SetLineThicknessScale(updateSpanStyle.updateLineThicknessScale);
    richEditorPattern->UpdateDecoration(spanNode, updateSpanStyle, textStyle);
    float spanLineThicknessScale = spanNode->GetLineThicknessScale().value();
    EXPECT_EQ(spanLineThicknessScale, updateSpanStyle.updateLineThicknessScale);
}

/**
 * @tc.name: UpdateDecorationStyle003
 * @tc.desc: test UpdateDecorationStyle when decoration properties are nullptr
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyleTestNg, UpdateDecorationStyle003, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto spanNode = AceType::MakeRefPtr<SpanNode>(0);
    auto spanItem = spanNode->GetSpanItem();
    TextStyle textStyle;
    struct UpdateSpanStyle updateSpanStyle;

    richEditorPattern->UpdateDecoration(spanNode, updateSpanStyle, textStyle);
    EXPECT_EQ(spanItem->useThemeDecorationColor, true);
    TextDecorationStyle spanDecorationStyle = spanNode->GetTextDecorationStyle().value_or(TextDecorationStyle::SOLID);
    EXPECT_EQ(spanDecorationStyle, TextDecorationStyle::SOLID);

    richEditorPattern->UpdateDecoration(spanNode, updateSpanStyle, textStyle);
    EXPECT_EQ(spanItem->useThemeDecorationColor, true);
    Color spanDecorationColor = spanNode->GetTextDecorationColor().value_or(Color::BLACK);
    EXPECT_EQ(spanDecorationColor, Color::BLACK);

    updateSpanStyle.updateLineThicknessScale = LINE_THICKNESS_SCALE;
    textStyle.SetLineThicknessScale(updateSpanStyle.updateLineThicknessScale);
    richEditorPattern->UpdateDecoration(spanNode, updateSpanStyle, textStyle);
    float spanLineThicknessScale = spanNode->GetLineThicknessScale().value();
    EXPECT_EQ(spanLineThicknessScale, updateSpanStyle.updateLineThicknessScale);
}

/**
 * @tc.name: HandleSelectFontStyleWrapper009
 * @tc.desc: test HandleSelectFontStyleWrapper
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyleTestNg, HandleSelectFontStyleWrapper009, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    KeyCode code1 = KeyCode::KEY_B;
    TextStyle style;
    style.SetFontWeight(Ace::FontWeight::NORMAL);
    richEditorPattern->HandleSelectFontStyleWrapper(code1, style);
    KeyCode code2 = KeyCode::KEY_U;
    style.SetTextDecoration(TextDecoration::NONE);
    richEditorPattern->HandleSelectFontStyleWrapper(code2, style);
    KeyCode code3 = KeyCode::KEY_I;
    style.SetFontStyle(OHOS::Ace::FontStyle::NORMAL);
    richEditorPattern->HandleSelectFontStyleWrapper(code3, style);
    EXPECT_EQ(style.GetFontWeight(), Ace::FontWeight::BOLD);
    EXPECT_EQ(style.GetTextDecorationFirst(), TextDecoration::UNDERLINE);
    EXPECT_EQ(style.GetFontStyle(), OHOS::Ace::FontStyle::ITALIC);
}

/**
 * @tc.name: SetSelectSpanStyle006
 * @tc.desc: test SetSelectSpanStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyleTestNg, SetSelectSpanStyle006, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);
    int32_t start = 1;
    int32_t end = 4;
    KeyCode code1 = KeyCode::KEY_B;
    KeyCode code2 = KeyCode::KEY_I;
    KeyCode code3 = KeyCode::KEY_U;
    auto updateSpanStyle = richEditorPattern->GetUpdateSpanStyle();
    auto fontWeight = updateSpanStyle.updateFontWeight;
    auto italicFontStyle = updateSpanStyle.updateItalicFontStyle;
    auto textDecoration = updateSpanStyle.updateTextDecoration;
    richEditorPattern->UpdateSelectSpanStyle(start, end, code1);
    richEditorPattern->UpdateSelectSpanStyle(start, end, code1);
    richEditorPattern->UpdateSelectSpanStyle(start, end, code2);
    richEditorPattern->UpdateSelectSpanStyle(start, end, code2);
    richEditorPattern->UpdateSelectSpanStyle(start, end, code3);
    richEditorPattern->UpdateSelectSpanStyle(start, end, code3);
    
    EXPECT_NE(fontWeight, richEditorPattern->GetUpdateSpanStyle().updateFontWeight);
    EXPECT_NE(italicFontStyle, richEditorPattern->GetUpdateSpanStyle().updateItalicFontStyle);
    EXPECT_NE(textDecoration, richEditorPattern->GetUpdateSpanStyle().updateTextDecoration);
}

}