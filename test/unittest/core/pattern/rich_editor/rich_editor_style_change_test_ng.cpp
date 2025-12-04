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
const Dimension IMAGE_WIDTH = 50.0_vp;
const Dimension IMAGE_HEIGHT = 50.0_vp;
const ImageSpanSize TEST_IMAGE_SIZE_1 = { .width = 50.0_vp, .height = 50.0_vp };

const LeadingMargin TEST_LEADING_MARGIN = {
    .size = LeadingMarginSize(Dimension(20, DimensionUnit::VP), Dimension(30, DimensionUnit::VP)),
    .pixmap = nullptr
};
const struct UpdateParagraphStyle TEST_PARAGRAPH_STYLE_1 = {
    .textAlign = TextAlign::CENTER,
    .leadingMargin = TEST_LEADING_MARGIN,
    .wordBreak = WordBreak::BREAK_WORD,
    .lineBreakStrategy = LineBreakStrategy::HIGH_QUALITY,
    .paragraphSpacing = Dimension(10, DimensionUnit::VP),
    .textDirection = TextDirection::RTL,
};
const struct UpdateParagraphStyle TEST_PARAGRAPH_STYLE_2 = {
    .textAlign = TextAlign::END,
    .leadingMargin = TEST_LEADING_MARGIN,
    .textDirection = TextDirection::LTR,
};
}

class RichEditorStyleChangeTestNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
};

void RichEditorStyleChangeTestNg::SetUp()
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

void RichEditorStyleChangeTestNg::TearDown()
{
    richEditorNode_ = nullptr;
    MockParagraph::TearDown();
}

void RichEditorStyleChangeTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

/**
 * @tc.name: TextStyle001
 * @tc.desc: test update span style
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyleChangeTestNg, TextStyle001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);
    AddSpan(INIT_VALUE_1);
    AddImageSpan();
    AddSpan(INIT_VALUE_2);
    TextStyle textStyle;
    ImageSpanAttribute imageStyle;
    textStyle.SetTextColor(TEXT_COLOR_VALUE);
    textStyle.SetTextShadows(SHADOWS);
    textStyle.SetFontSize(FONT_SIZE_VALUE);
    textStyle.SetFontStyle(ITALIC_FONT_STYLE_VALUE);
    textStyle.SetFontWeight(FONT_WEIGHT_VALUE);
    textStyle.SetFontFamilies(FONT_FAMILY_VALUE);
    textStyle.SetTextDecoration(TEXT_DECORATION_VALUE);
    textStyle.SetTextDecorationColor(TEXT_DECORATION_COLOR_VALUE);
    textStyle.SetLineThicknessScale(TEXT_DECORATION_THICKNESS_SCALE);
    struct UpdateSpanStyle updateSpanStyle;
    updateSpanStyle.updateTextColor = TEXT_COLOR_VALUE;
    updateSpanStyle.updateTextShadows = SHADOWS;
    updateSpanStyle.updateFontSize = FONT_SIZE_VALUE;
    updateSpanStyle.updateItalicFontStyle = ITALIC_FONT_STYLE_VALUE;
    updateSpanStyle.updateFontWeight = FONT_WEIGHT_VALUE;
    updateSpanStyle.updateFontFamily = FONT_FAMILY_VALUE;
    updateSpanStyle.updateTextDecoration = TEXT_DECORATION_VALUE;
    updateSpanStyle.updateTextDecorationColor = TEXT_DECORATION_COLOR_VALUE;
    updateSpanStyle.updateLineThicknessScale = TEXT_DECORATION_THICKNESS_SCALE;
    richEditorController->SetUpdateSpanStyle(updateSpanStyle);
    richEditorController->UpdateSpanStyle(5, 10, textStyle, imageStyle);
    EXPECT_EQ(contentNode->GetChildren().size(), 5);
    auto newSpan1 = AceType::DynamicCast<SpanNode>(contentNode->GetChildAtIndex(1));
    ASSERT_NE(newSpan1, nullptr);
    EXPECT_EQ(newSpan1->GetFontSize(), FONT_SIZE_VALUE);
    EXPECT_EQ(newSpan1->GetTextColor(), TEXT_COLOR_VALUE);
    EXPECT_EQ(newSpan1->GetTextShadow(), SHADOWS);
    EXPECT_EQ(newSpan1->GetItalicFontStyle(), ITALIC_FONT_STYLE_VALUE);
    EXPECT_EQ(newSpan1->GetFontWeight(), FONT_WEIGHT_VALUE);
    EXPECT_EQ(newSpan1->GetFontFamily(), FONT_FAMILY_VALUE);
    EXPECT_EQ(newSpan1->GetTextDecorationFirst(), TEXT_DECORATION_VALUE);
    EXPECT_EQ(newSpan1->GetTextDecorationColor(), TEXT_DECORATION_COLOR_VALUE);
    EXPECT_EQ(newSpan1->GetLineThicknessScale(), TEXT_DECORATION_THICKNESS_SCALE);
}

/**
 * @tc.name: UpdateSpanStyle001
 * @tc.desc: test update span style
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyleChangeTestNg, UpdateSpanStyle001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. get richEditor controller
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);

    /**
     * @tc.steps: step2. test add span
     */
    AddSpan(INIT_VALUE_1);
    AddImageSpan();
    AddSpan(INIT_VALUE_2);
    EXPECT_EQ(static_cast<int32_t>(contentNode->GetChildren().size()), 3);

    /**
     * @tc.steps: step3. test update span
     */
    TextStyle textStyle;
    textStyle.SetFontSize(FONT_SIZE_VALUE);
    TextStyle textStyle2;
    textStyle2.SetFontSize(FONT_SIZE_VALUE_2);
    struct UpdateSpanStyle updateSpanStyle;
    updateSpanStyle.updateFontSize = FONT_SIZE_VALUE_2;
    richEditorController->SetUpdateSpanStyle(updateSpanStyle);
    ImageSpanAttribute imageStyle;

    /**
     * @tc.cases: case. call UpdateSpanStyle(), cover branch end < 0
     * @tc.expected: expect GetFontSize() is equal to FONT_SIZE_VALUE
     */
    richEditorController->UpdateSpanStyle(0, -1, textStyle, imageStyle);
    auto newSpan1 = AceType::DynamicCast<SpanNode>(contentNode->GetChildAtIndex(0));
    ASSERT_NE(newSpan1, nullptr);
    EXPECT_EQ(newSpan1->GetFontSize(), FONT_SIZE_VALUE);

    /**
     * @tc.cases: case. call UpdateSpanStyle(), update FontSize to FONT_SIZE_VALUE_2, cover branch end > length
     * @tc.expected: expect GetFontSize() is equal to FONT_SIZE_VALUE_2
     */
    richEditorController->UpdateSpanStyle(0, 20, textStyle2, imageStyle);
    EXPECT_EQ(newSpan1->GetFontSize(), FONT_SIZE_VALUE_2);

    /**
     * @tc.cases: case. call UpdateSpanStyle(), update FontSize to FONT_SIZE_VALUE, cover branch start > end
     * @tc.expected: expect GetFontSize() is equal to FONT_SIZE_VALUE
     */
    richEditorController->UpdateSpanStyle(10, 0, textStyle, imageStyle);
    EXPECT_EQ(newSpan1->GetFontSize(), FONT_SIZE_VALUE);

    /**
     * @tc.cases: case. call UpdateSpanStyle(), update FontSize to FONT_SIZE_VALUE_2, cover branch start == end
     * @tc.expected: expect GetFontSize() is still equal to FONT_SIZE_VALUE
     */
    richEditorController->UpdateSpanStyle(0, 0, textStyle2, imageStyle);
    EXPECT_EQ(newSpan1->GetFontSize(), FONT_SIZE_VALUE);

    /**
     * @tc.cases: case. call UpdateSpanStyle(), update FontSize to FONT_SIZE_VALUE_2, cover branch start > length
     * @tc.expected: expect GetFontSize() is still equal to FONT_SIZE_VALUE
     */
    richEditorController->UpdateSpanStyle(20, 30, textStyle2, imageStyle);
    EXPECT_EQ(newSpan1->GetFontSize(), FONT_SIZE_VALUE);
    ClearSpan();
}

/**
 * @tc.name: UpdateSpanStyle002
 * @tc.desc: test UpdateImageStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyleChangeTestNg, UpdateSpanStyle002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. get richEditor controller
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);

    /**
     * @tc.steps: step2. initalize span properties and add image span
     */
    AddImageSpan();
    AddSpan(INIT_VALUE_1);
    EXPECT_EQ(contentNode->GetChildren().size(), 2);

    /**
     * @tc.steps: step3. test UpdateImageStyle
     */
    struct UpdateSpanStyle updateSpanStyle;
    updateSpanStyle.updateImageWidth = IMAGE_WIDTH;
    updateSpanStyle.updateImageHeight = IMAGE_HEIGHT;
    updateSpanStyle.updateImageFit = ImageFit::CONTAIN;
    updateSpanStyle.updateImageVerticalAlign = VerticalAlign::BOTTOM;
    std::optional<Ace::NG::MarginProperty> marginProp = std::nullopt;
    std::optional<Ace::NG::BorderRadiusProperty> borderRadius = std::nullopt;
    marginProp = { CALC_LENGTH_CALC, CALC_LENGTH_CALC, CALC_LENGTH_CALC, CALC_LENGTH_CALC };
    borderRadius = { CALC_TEST, CALC_TEST, CALC_TEST, CALC_TEST };
    updateSpanStyle.borderRadius = borderRadius;
    updateSpanStyle.marginProp = marginProp;
    richEditorController->SetUpdateSpanStyle(updateSpanStyle);

    ImageSpanAttribute imageStyle;
    imageStyle.size = TEST_IMAGE_SIZE_1;
    imageStyle.verticalAlign = VerticalAlign::BOTTOM;
    imageStyle.objectFit = ImageFit::CONTAIN;
    imageStyle.marginProp = marginProp;
    imageStyle.borderRadius = borderRadius;
    TextStyle style;
    richEditorController->UpdateSpanStyle(0, 2, style, imageStyle);

    /**
     * @tc.steps: step4. test image span style
     */
    auto host = richEditorPattern->GetContentHost();
    ASSERT_NE(host, nullptr);
    auto child = host->GetChildren().begin();
    auto imageNode = AceType::DynamicCast<FrameNode>(*child);
    ASSERT_NE(imageNode, nullptr);
    auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    EXPECT_EQ(imageLayoutProperty->calcLayoutConstraint_->selfIdealSize, TEST_IMAGE_SIZE_1.GetSize());
    EXPECT_EQ(imageLayoutProperty->GetVerticalAlignValue(), VerticalAlign::BOTTOM);
    EXPECT_EQ(imageLayoutProperty->GetImageFitValue(), ImageFit::CONTAIN);
    EXPECT_EQ(imageLayoutProperty->GetMarginProperty()->left->ToString(), CALC_LENGTH_CALC.ToString());

    auto imageRenderCtx = imageNode->GetRenderContext();
    ASSERT_NE(imageRenderCtx, nullptr);
    EXPECT_EQ(imageRenderCtx->GetBorderRadius(), borderRadius);

    ClearSpan();
}

/**
 * @tc.name: UpdateSpanStyle003
 * @tc.desc: test update span style
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyleChangeTestNg, UpdateSpanStyle003, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);
    AddSpan(INIT_VALUE_1);
    AddImageSpan();
    AddSpan(INIT_VALUE_2);
    TextStyle textStyle;
    ImageSpanAttribute imageStyle;
    textStyle.SetTextColor(TEXT_COLOR_VALUE);
    textStyle.SetTextShadows(SHADOWS);
    textStyle.SetFontSize(FONT_SIZE_VALUE);
    textStyle.SetFontStyle(ITALIC_FONT_STYLE_VALUE);
    textStyle.SetFontWeight(FONT_WEIGHT_VALUE);
    textStyle.SetFontFamilies(FONT_FAMILY_VALUE);
    textStyle.SetTextDecoration(TEXT_DECORATION_VALUE);
    textStyle.SetTextDecorationColor(TEXT_DECORATION_COLOR_VALUE);
    textStyle.SetLineThicknessScale(TEXT_DECORATION_THICKNESS_SCALE);
    struct UpdateSpanStyle updateSpanStyle;
    updateSpanStyle.updateTextColor = TEXT_COLOR_VALUE;
    updateSpanStyle.updateTextShadows = SHADOWS;
    updateSpanStyle.updateFontSize = FONT_SIZE_VALUE;
    updateSpanStyle.updateItalicFontStyle = ITALIC_FONT_STYLE_VALUE;
    updateSpanStyle.updateFontWeight = FONT_WEIGHT_VALUE;
    updateSpanStyle.updateFontFamily = FONT_FAMILY_VALUE;
    updateSpanStyle.updateTextDecoration = TEXT_DECORATION_VALUE;
    updateSpanStyle.updateTextDecorationColor = TEXT_DECORATION_COLOR_VALUE;
    updateSpanStyle.updateLineThicknessScale = TEXT_DECORATION_THICKNESS_SCALE;
    richEditorController->SetUpdateSpanStyle(updateSpanStyle);
    richEditorController->UpdateSpanStyle(5, 10, textStyle, imageStyle);
    EXPECT_EQ(contentNode->GetChildren().size(), 5);
    auto newSpan2 = AceType::DynamicCast<SpanNode>(contentNode->GetChildAtIndex(3));
    ASSERT_NE(newSpan2, nullptr);
    EXPECT_EQ(newSpan2->GetFontSize(), FONT_SIZE_VALUE);
    EXPECT_EQ(newSpan2->GetTextColor(), TEXT_COLOR_VALUE);
    EXPECT_EQ(newSpan2->GetTextShadow(), SHADOWS);
    EXPECT_EQ(newSpan2->GetItalicFontStyle(), ITALIC_FONT_STYLE_VALUE);
    EXPECT_EQ(newSpan2->GetFontWeight(), FONT_WEIGHT_VALUE);
    EXPECT_EQ(newSpan2->GetFontFamily(), FONT_FAMILY_VALUE);
    EXPECT_EQ(newSpan2->GetTextDecorationFirst(), TEXT_DECORATION_VALUE);
    EXPECT_EQ(newSpan2->GetTextDecorationColor(), TEXT_DECORATION_COLOR_VALUE);
    EXPECT_EQ(newSpan2->GetLineThicknessScale(), TEXT_DECORATION_THICKNESS_SCALE);
}

/**
 * @tc.name: UpdateParagraphStyle001
 * @tc.desc: test AddTextSpan with UpdateParagraphStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyleChangeTestNg, UpdateParagraphStyle001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. get richEditor controller
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    /**
     * @tc.steps: step2. add span and initalize UpdateParagraphStyle
     */
    AddSpan("test");
    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    TextStyle style;
    options.style = style;
    struct UpdateParagraphStyle paragraphStyle;
    paragraphStyle.wordBreak = WordBreak::NORMAL;
    paragraphStyle.textAlign = TextAlign::END;
    paragraphStyle.paragraphSpacing = Dimension(10.0f, DimensionUnit::PX);
    options.paraStyle = paragraphStyle;

    /**
     * @tc.steps: step3. set userGestureOption
     */
    GestureEventFunc callback2 = [](GestureEvent& info) {};
    options.userGestureOption.onClick = callback2;

    /**
     * @tc.steps: step4. test AddTextSpan
     */
    auto index = richEditorPattern->AddTextSpan(options, TextChangeReason::UNKNOWN, true, 5);
    EXPECT_EQ(index, 5);
    auto info = richEditorController->GetSpansInfo(5, sizeof(INIT_VALUE_1));
    EXPECT_EQ(info.selection_.resultObjects.size(), 1);
    auto textStyle = info.selection_.resultObjects.begin()->textStyle;
    EXPECT_EQ(textStyle.wordBreak, int(WordBreak::NORMAL));
    EXPECT_EQ(textStyle.textAlign, int(TextAlign::END));
    EXPECT_NE(textStyle.paragraphSpacing, std::nullopt);
    EXPECT_EQ(textStyle.paragraphSpacing.value().Value(), 10.0f);
}

/**
 * @tc.name: UpdateParagraphStyle002
 * @tc.desc: test paragraph style
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyleChangeTestNg, UpdateParagraphStyle002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richEditor controller
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    /**
     * @tc.steps: step2. initalize UpdateParagraphStyle
     */
    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    TextStyle style;
    options.style = style;
    options.paraStyle = TEST_PARAGRAPH_STYLE_1;

    /**
     * @tc.steps: step3. test AddTextSpan
     */
    auto index = richEditorPattern->AddTextSpan(options, TextChangeReason::UNKNOWN, true, 5);
    EXPECT_EQ(index, 5);

    /**
     * @tc.steps: step4. check paragraph style
     */
    auto info = richEditorController->GetSpansInfo(5, sizeof(INIT_VALUE_1));
    EXPECT_EQ(info.selection_.resultObjects.size(), 1);
    auto textStyle = info.selection_.resultObjects.begin()->textStyle;
    EXPECT_EQ(static_cast<TextAlign>(textStyle.textAlign), TextAlign::CENTER);
    EXPECT_EQ(static_cast<WordBreak>(textStyle.wordBreak), WordBreak::BREAK_WORD);
    EXPECT_NE(textStyle.paragraphSpacing, std::nullopt);
    EXPECT_EQ(textStyle.paragraphSpacing.value().Value(), 10.0f);
    EXPECT_EQ(static_cast<TextDirection>(textStyle.textDirection.value()), TextDirection::RTL);

    /**
     * @tc.steps: step5. update paragraph style and check it
     */
    richEditorController->UpdateParagraphStyle(0, sizeof(INIT_VALUE_1), TEST_PARAGRAPH_STYLE_2);
    auto paragraphInfo = richEditorController->GetParagraphsInfo(1, sizeof(INIT_VALUE_1));
    EXPECT_EQ(static_cast<TextAlign>(paragraphInfo[0].textAlign), TextAlign::END);
    EXPECT_EQ(static_cast<TextDirection>(paragraphInfo[0].textDirection.value()), TextDirection::LTR);
}
}