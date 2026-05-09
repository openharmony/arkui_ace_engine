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
#include "core/components_ng/pattern/rich_editor/rich_editor_model_ng.h"
#include "core/components_ng/pattern/rich_editor/style_manager.h"
#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/frameworks/core/components_ng/render/mock_paragraph.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const Dimension FONT_SIZE_LPX = Dimension(20.0, DimensionUnit::LPX);
const Dimension FONT_SIZE_PX = Dimension(20.0, DimensionUnit::PX);
const Dimension FONT_SIZE_VP = Dimension(20.0, DimensionUnit::VP);
const Dimension STROKE_WIDTH_LPX = Dimension(5.0, DimensionUnit::LPX);
const Dimension STROKE_WIDTH_PX = Dimension(5.0, DimensionUnit::PX);
const Dimension LETTER_SPACING_LPX = Dimension(10.0, DimensionUnit::LPX);
const Dimension LETTER_SPACING_PX = Dimension(10.0, DimensionUnit::PX);
const Dimension LINE_HEIGHT_LPX = Dimension(40.0, DimensionUnit::LPX);
const Dimension LINE_HEIGHT_PX = Dimension(40.0, DimensionUnit::PX);
const Dimension LINE_SPACING_LPX = Dimension(8.0, DimensionUnit::LPX);
const Dimension PARAGRAPH_SPACING_LPX = Dimension(15.0, DimensionUnit::LPX);
}

class RichEditorLpxTestNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
};

void RichEditorLpxTestNg::SetUp()
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

void RichEditorLpxTestNg::TearDown()
{
    richEditorNode_ = nullptr;
    MockParagraph::TearDown();
}

void RichEditorLpxTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

HWTEST_F(RichEditorLpxTestNg, SpanItemUpdateLpxUnitFlag001, TestSize.Level0)
{
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);
    EXPECT_FALSE(spanItem->HasLpxUnitStyle());

    spanItem->fontStyle->UpdateFontSize(FONT_SIZE_PX);
    spanItem->ClearLpxFlag(SpanItem::LPX_FLAG_FontSize);
    EXPECT_FALSE(spanItem->HasLpxUnitStyle());

    spanItem->fontStyle->UpdateFontSize(FONT_SIZE_LPX);
    spanItem->SetLpxFlag(SpanItem::LPX_FLAG_FontSize);
    EXPECT_TRUE(spanItem->HasLpxUnitStyle());

    spanItem->fontStyle->UpdateFontSize(FONT_SIZE_PX);
    spanItem->ClearLpxFlag(SpanItem::LPX_FLAG_FontSize);
    EXPECT_FALSE(spanItem->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, SpanItemUpdateLpxUnitFlag002, TestSize.Level0)
{
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);
    EXPECT_FALSE(spanItem->HasLpxUnitStyle());

    spanItem->fontStyle->UpdateStrokeWidth(STROKE_WIDTH_LPX);
    spanItem->SetLpxFlag(SpanItem::LPX_FLAG_StrokeWidth);
    EXPECT_TRUE(spanItem->HasLpxUnitStyle());

    spanItem->fontStyle->UpdateStrokeWidth(STROKE_WIDTH_PX);
    spanItem->ClearLpxFlag(SpanItem::LPX_FLAG_StrokeWidth);
    EXPECT_FALSE(spanItem->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, SpanItemUpdateLpxUnitFlag003, TestSize.Level0)
{
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);
    EXPECT_FALSE(spanItem->HasLpxUnitStyle());

    spanItem->fontStyle->UpdateLetterSpacing(LETTER_SPACING_LPX);
    spanItem->SetLpxFlag(SpanItem::LPX_FLAG_LetterSpacing);
    EXPECT_TRUE(spanItem->HasLpxUnitStyle());

    spanItem->fontStyle->UpdateLetterSpacing(LETTER_SPACING_PX);
    spanItem->ClearLpxFlag(SpanItem::LPX_FLAG_LetterSpacing);
    EXPECT_FALSE(spanItem->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, SpanItemUpdateLpxUnitFlagLineHeight001, TestSize.Level0)
{
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);
    EXPECT_FALSE(spanItem->HasLpxUnitStyle());

    spanItem->textLineStyle->UpdateLineHeight(LINE_HEIGHT_LPX);
    spanItem->SetLpxFlag(SpanItem::LPX_FLAG_LineHeight);
    EXPECT_TRUE(spanItem->HasLpxUnitStyle());

    spanItem->textLineStyle->UpdateLineHeight(LINE_HEIGHT_PX);
    spanItem->ClearLpxFlag(SpanItem::LPX_FLAG_LineHeight);
    EXPECT_FALSE(spanItem->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, SpanItemUpdateLpxUnitFlagLineSpacing001, TestSize.Level0)
{
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);
    EXPECT_FALSE(spanItem->HasLpxUnitStyle());

    spanItem->textLineStyle->UpdateLineSpacing(LINE_SPACING_LPX);
    spanItem->SetLpxFlag(SpanItem::LPX_FLAG_LineSpacing);
    EXPECT_TRUE(spanItem->HasLpxUnitStyle());

    spanItem->textLineStyle->ResetLineSpacing();
    spanItem->ClearLpxFlag(SpanItem::LPX_FLAG_LineSpacing);
    EXPECT_FALSE(spanItem->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, SpanItemUpdateLpxUnitFlagParagraphSpacing001, TestSize.Level0)
{
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);
    EXPECT_FALSE(spanItem->HasLpxUnitStyle());

    spanItem->textLineStyle->UpdateParagraphSpacing(PARAGRAPH_SPACING_LPX);
    spanItem->SetLpxFlag(SpanItem::LPX_FLAG_ParagraphSpacing);
    EXPECT_TRUE(spanItem->HasLpxUnitStyle());

    spanItem->textLineStyle->ResetParagraphSpacing();
    spanItem->ClearLpxFlag(SpanItem::LPX_FLAG_ParagraphSpacing);
    EXPECT_FALSE(spanItem->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, SpanItemUpdateLpxUnitFlagMultiple001, TestSize.Level0)
{
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);
    EXPECT_FALSE(spanItem->HasLpxUnitStyle());

    spanItem->fontStyle->UpdateFontSize(FONT_SIZE_PX);
    spanItem->fontStyle->UpdateLetterSpacing(LETTER_SPACING_PX);
    spanItem->textLineStyle->UpdateLineHeight(LINE_HEIGHT_PX);
    spanItem->ClearAllLpxFlags();
    EXPECT_FALSE(spanItem->HasLpxUnitStyle());

    spanItem->fontStyle->UpdateLetterSpacing(LETTER_SPACING_LPX);
    spanItem->SetLpxFlag(SpanItem::LPX_FLAG_LetterSpacing);
    EXPECT_TRUE(spanItem->HasLpxUnitStyle());

    spanItem->fontStyle->UpdateLetterSpacing(LETTER_SPACING_PX);
    spanItem->ClearLpxFlag(SpanItem::LPX_FLAG_LetterSpacing);
    EXPECT_FALSE(spanItem->HasLpxUnitStyle());

    spanItem->textLineStyle->UpdateLineHeight(LINE_HEIGHT_LPX);
    spanItem->SetLpxFlag(SpanItem::LPX_FLAG_LineHeight);
    EXPECT_TRUE(spanItem->HasLpxUnitStyle());

    spanItem->textLineStyle->UpdateLineHeight(LINE_HEIGHT_PX);
    spanItem->ClearLpxFlag(SpanItem::LPX_FLAG_LineHeight);
    EXPECT_FALSE(spanItem->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, SpanNodeUpdateFontSizeLpx001, TestSize.Level0)
{
    auto spanNode = SpanNode::GetOrCreateSpanNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(spanNode, nullptr);
    auto spanItem = spanNode->GetSpanItem();
    ASSERT_NE(spanItem, nullptr);
    EXPECT_FALSE(spanItem->HasLpxUnitStyle());

    spanNode->UpdateFontSize(FONT_SIZE_LPX);
    EXPECT_TRUE(spanItem->HasLpxUnitStyle());

    spanNode->UpdateFontSize(FONT_SIZE_PX);
    EXPECT_FALSE(spanItem->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, SpanNodeUpdateStrokeWidthLpx001, TestSize.Level0)
{
    auto spanNode = SpanNode::GetOrCreateSpanNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(spanNode, nullptr);
    auto spanItem = spanNode->GetSpanItem();
    ASSERT_NE(spanItem, nullptr);
    EXPECT_FALSE(spanItem->HasLpxUnitStyle());

    spanNode->UpdateStrokeWidth(STROKE_WIDTH_LPX);
    EXPECT_TRUE(spanItem->HasLpxUnitStyle());

    spanNode->UpdateStrokeWidth(STROKE_WIDTH_PX);
    EXPECT_FALSE(spanItem->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, SpanNodeUpdateLetterSpacingLpx001, TestSize.Level0)
{
    auto spanNode = SpanNode::GetOrCreateSpanNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(spanNode, nullptr);
    auto spanItem = spanNode->GetSpanItem();
    ASSERT_NE(spanItem, nullptr);
    EXPECT_FALSE(spanItem->HasLpxUnitStyle());

    spanNode->UpdateLetterSpacing(LETTER_SPACING_LPX);
    EXPECT_TRUE(spanItem->HasLpxUnitStyle());

    spanNode->UpdateLetterSpacing(LETTER_SPACING_PX);
    EXPECT_FALSE(spanItem->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, SpanNodeUpdateLineHeightLpx001, TestSize.Level0)
{
    auto spanNode = SpanNode::GetOrCreateSpanNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(spanNode, nullptr);
    auto spanItem = spanNode->GetSpanItem();
    ASSERT_NE(spanItem, nullptr);
    EXPECT_FALSE(spanItem->HasLpxUnitStyle());

    spanNode->UpdateLineHeight(LINE_HEIGHT_LPX);
    EXPECT_TRUE(spanItem->HasLpxUnitStyle());

    spanNode->UpdateLineHeight(LINE_HEIGHT_PX);
    EXPECT_FALSE(spanItem->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, SpanNodeResetFontSizeLpx001, TestSize.Level0)
{
    auto spanNode = SpanNode::GetOrCreateSpanNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(spanNode, nullptr);
    auto spanItem = spanNode->GetSpanItem();
    ASSERT_NE(spanItem, nullptr);

    spanNode->UpdateFontSize(FONT_SIZE_LPX);
    EXPECT_TRUE(spanItem->HasLpxUnitStyle());

    spanNode->ResetFontSize();
    EXPECT_FALSE(spanItem->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, SpanNodeResetLineHeightLpx001, TestSize.Level0)
{
    auto spanNode = SpanNode::GetOrCreateSpanNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(spanNode, nullptr);
    auto spanItem = spanNode->GetSpanItem();
    ASSERT_NE(spanItem, nullptr);

    spanNode->UpdateLineHeight(LINE_HEIGHT_LPX);
    EXPECT_TRUE(spanItem->HasLpxUnitStyle());

    spanNode->ResetLineHeight();
    EXPECT_FALSE(spanItem->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, RichEditorPatternLpxFlag001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    EXPECT_FALSE(richEditorPattern->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, RichEditorPatternLpxFlagAddTextSpan001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    EXPECT_FALSE(richEditorPattern->HasLpxUnitStyle());

    TextStyle style;
    style.SetFontSize(FONT_SIZE_LPX);
    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    options.style = style;
    richEditorController->AddTextSpan(options);
    EXPECT_TRUE(richEditorPattern->HasLpxUnitStyle());

    ClearSpan();
    richEditorPattern->UpdateLpxUnitFlag();
    EXPECT_FALSE(richEditorPattern->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, RichEditorPatternLpxFlagAddTextSpan002, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    EXPECT_FALSE(richEditorPattern->HasLpxUnitStyle());

    TextStyle style;
    style.SetFontSize(FONT_SIZE_PX);
    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    options.style = style;
    richEditorController->AddTextSpan(options);
    EXPECT_FALSE(richEditorPattern->HasLpxUnitStyle());

    ClearSpan();
    richEditorPattern->UpdateLpxUnitFlag();
    EXPECT_FALSE(richEditorPattern->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, RichEditorPatternLpxFlagAddTextSpan003, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    TextStyle styleNoLpx;
    styleNoLpx.SetFontSize(FONT_SIZE_PX);
    TextSpanOptions optionsNoLpx;
    optionsNoLpx.value = INIT_VALUE_1;
    optionsNoLpx.style = styleNoLpx;
    richEditorController->AddTextSpan(optionsNoLpx);
    EXPECT_FALSE(richEditorPattern->HasLpxUnitStyle());

    TextStyle styleLpx;
    styleLpx.SetFontSize(FONT_SIZE_LPX);
    TextSpanOptions optionsLpx;
    optionsLpx.value = INIT_VALUE_2;
    optionsLpx.style = styleLpx;
    richEditorController->AddTextSpan(optionsLpx);
    EXPECT_TRUE(richEditorPattern->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, RichEditorPatternLpxFlagAddTextSpanLetterSpacing001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    EXPECT_FALSE(richEditorPattern->HasLpxUnitStyle());

    TextStyle style;
    style.SetLetterSpacing(LETTER_SPACING_LPX);
    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    options.style = style;
    richEditorController->AddTextSpan(options);
    EXPECT_TRUE(richEditorPattern->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, RichEditorPatternLpxFlagAddTextSpanLineHeight001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    EXPECT_FALSE(richEditorPattern->HasLpxUnitStyle());

    TextStyle style;
    style.SetLineHeight(LINE_HEIGHT_LPX);
    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    options.style = style;
    richEditorController->AddTextSpan(options);
    EXPECT_TRUE(richEditorPattern->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, RichEditorPatternLpxFlagUpdateSpanStyle001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    TextStyle styleNoLpx;
    styleNoLpx.SetFontSize(FONT_SIZE_PX);
    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    options.style = styleNoLpx;
    richEditorController->AddTextSpan(options);
    EXPECT_FALSE(richEditorPattern->HasLpxUnitStyle());

    TextStyle textStyle;
    textStyle.SetFontSize(FONT_SIZE_LPX);
    struct UpdateSpanStyle updateSpanStyle;
    updateSpanStyle.updateFontSize = FONT_SIZE_LPX;
    richEditorController->SetUpdateSpanStyle(updateSpanStyle);
    ImageSpanAttribute imageStyle;
    richEditorController->UpdateSpanStyle(0, 6, textStyle, imageStyle);
    EXPECT_TRUE(richEditorPattern->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, RichEditorPatternLpxFlagUpdateSpanStyle002, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    TextStyle styleLpx;
    styleLpx.SetFontSize(FONT_SIZE_LPX);
    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    options.style = styleLpx;
    richEditorController->AddTextSpan(options);
    EXPECT_TRUE(richEditorPattern->HasLpxUnitStyle());

    TextStyle textStyle;
    textStyle.SetFontSize(FONT_SIZE_PX);
    struct UpdateSpanStyle updateSpanStyle;
    updateSpanStyle.updateFontSize = FONT_SIZE_PX;
    richEditorController->SetUpdateSpanStyle(updateSpanStyle);
    ImageSpanAttribute imageStyle;
    richEditorController->UpdateSpanStyle(0, 6, textStyle, imageStyle);
    EXPECT_FALSE(richEditorPattern->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, RichEditorPatternLpxFlagUpdateSpanStyleLetterSpacing001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    TextStyle styleNoLpx;
    styleNoLpx.SetFontSize(FONT_SIZE_PX);
    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    options.style = styleNoLpx;
    richEditorController->AddTextSpan(options);
    EXPECT_FALSE(richEditorPattern->HasLpxUnitStyle());

    TextStyle textStyle;
    textStyle.SetLetterSpacing(LETTER_SPACING_LPX);
    struct UpdateSpanStyle updateSpanStyle;
    updateSpanStyle.updateLetterSpacing = LETTER_SPACING_LPX;
    richEditorController->SetUpdateSpanStyle(updateSpanStyle);
    ImageSpanAttribute imageStyle;
    richEditorController->UpdateSpanStyle(0, 6, textStyle, imageStyle);
    EXPECT_TRUE(richEditorPattern->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, RichEditorPatternLpxFlagUpdateSpanStyleStrokeWidth001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    TextStyle styleNoLpx;
    styleNoLpx.SetFontSize(FONT_SIZE_PX);
    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    options.style = styleNoLpx;
    richEditorController->AddTextSpan(options);
    EXPECT_FALSE(richEditorPattern->HasLpxUnitStyle());

    TextStyle textStyle;
    textStyle.SetStrokeWidth(STROKE_WIDTH_LPX);
    struct UpdateSpanStyle updateSpanStyle;
    updateSpanStyle.updateStrokeWidth = STROKE_WIDTH_LPX;
    richEditorController->SetUpdateSpanStyle(updateSpanStyle);
    ImageSpanAttribute imageStyle;
    richEditorController->UpdateSpanStyle(0, 6, textStyle, imageStyle);
    EXPECT_TRUE(richEditorPattern->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, RichEditorPatternLpxFlagUpdateSpanStyleLineHeight001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    TextStyle styleNoLpx;
    styleNoLpx.SetFontSize(FONT_SIZE_PX);
    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    options.style = styleNoLpx;
    richEditorController->AddTextSpan(options);
    EXPECT_FALSE(richEditorPattern->HasLpxUnitStyle());

    TextStyle textStyle;
    textStyle.SetLineHeight(LINE_HEIGHT_LPX);
    struct UpdateSpanStyle updateSpanStyle;
    updateSpanStyle.updateLineHeight = LINE_HEIGHT_LPX;
    richEditorController->SetUpdateSpanStyle(updateSpanStyle);
    ImageSpanAttribute imageStyle;
    richEditorController->UpdateSpanStyle(0, 6, textStyle, imageStyle);
    EXPECT_TRUE(richEditorPattern->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, RichEditorPatternLpxFlagDeleteSpans001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    TextStyle styleLpx;
    styleLpx.SetFontSize(FONT_SIZE_LPX);
    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    options.style = styleLpx;
    richEditorController->AddTextSpan(options);
    EXPECT_TRUE(richEditorPattern->HasLpxUnitStyle());

    RangeOptions rangeOptions;
    rangeOptions.start = 0;
    rangeOptions.end = static_cast<int32_t>(INIT_VALUE_1.length());
    richEditorPattern->DeleteSpans(rangeOptions, TextChangeReason::UNKNOWN);
    EXPECT_FALSE(richEditorPattern->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, RichEditorPatternLpxFlagDeleteSpans002, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    TextStyle styleLpx;
    styleLpx.SetFontSize(FONT_SIZE_LPX);
    TextSpanOptions optionsLpx;
    optionsLpx.value = INIT_VALUE_1;
    optionsLpx.style = styleLpx;
    richEditorController->AddTextSpan(optionsLpx);

    TextStyle styleNoLpx;
    styleNoLpx.SetFontSize(FONT_SIZE_PX);
    TextSpanOptions optionsNoLpx;
    optionsNoLpx.value = INIT_VALUE_2;
    optionsNoLpx.style = styleNoLpx;
    richEditorController->AddTextSpan(optionsNoLpx);
    EXPECT_TRUE(richEditorPattern->HasLpxUnitStyle());

    RangeOptions rangeOptions;
    rangeOptions.start = 0;
    rangeOptions.end = static_cast<int32_t>(INIT_VALUE_1.length());
    richEditorPattern->DeleteSpans(rangeOptions, TextChangeReason::UNKNOWN);
    EXPECT_FALSE(richEditorPattern->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, RichEditorPatternLpxFlagDeleteSpans003, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    TextStyle styleNoLpx;
    styleNoLpx.SetFontSize(FONT_SIZE_PX);
    TextSpanOptions optionsNoLpx;
    optionsNoLpx.value = INIT_VALUE_1;
    optionsNoLpx.style = styleNoLpx;
    richEditorController->AddTextSpan(optionsNoLpx);

    TextStyle styleLpx;
    styleLpx.SetFontSize(FONT_SIZE_LPX);
    TextSpanOptions optionsLpx;
    optionsLpx.value = INIT_VALUE_2;
    optionsLpx.style = styleLpx;
    richEditorController->AddTextSpan(optionsLpx);
    EXPECT_TRUE(richEditorPattern->HasLpxUnitStyle());

    RangeOptions rangeOptions;
    int32_t start = static_cast<int32_t>(INIT_VALUE_1.length());
    int32_t end = start + static_cast<int32_t>(INIT_VALUE_2.length());
    rangeOptions.start = start;
    rangeOptions.end = end;
    richEditorPattern->DeleteSpans(rangeOptions, TextChangeReason::UNKNOWN);
    EXPECT_FALSE(richEditorPattern->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, RichEditorPatternLpxFlagMultipleSpans001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    TextStyle style1;
    style1.SetFontSize(FONT_SIZE_PX);
    TextSpanOptions options1;
    options1.value = INIT_VALUE_1;
    options1.style = style1;
    richEditorController->AddTextSpan(options1);
    EXPECT_FALSE(richEditorPattern->HasLpxUnitStyle());

    TextStyle style2;
    style2.SetFontSize(FONT_SIZE_VP);
    TextSpanOptions options2;
    options2.value = INIT_VALUE_2;
    options2.style = style2;
    richEditorController->AddTextSpan(options2);
    EXPECT_FALSE(richEditorPattern->HasLpxUnitStyle());

    TextStyle style3;
    style3.SetFontSize(FONT_SIZE_LPX);
    TextSpanOptions options3;
    options3.value = INIT_VALUE_3;
    options3.style = style3;
    richEditorController->AddTextSpan(options3);
    EXPECT_TRUE(richEditorPattern->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, SpanItemCopyBaseSpanItemLpx001, TestSize.Level0)
{
    auto sourceSpan = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(sourceSpan, nullptr);
    sourceSpan->fontStyle->UpdateFontSize(FONT_SIZE_LPX);
    sourceSpan->SetLpxFlag(SpanItem::LPX_FLAG_FontSize);
    EXPECT_TRUE(sourceSpan->HasLpxUnitStyle());

    auto targetSpan = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(targetSpan, nullptr);
    EXPECT_FALSE(targetSpan->HasLpxUnitStyle());

    sourceSpan->CopyBaseSpanItem(targetSpan);
    EXPECT_TRUE(targetSpan->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, SpanItemCopyBaseSpanItemLpx002, TestSize.Level0)
{
    auto sourceSpan = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(sourceSpan, nullptr);
    sourceSpan->fontStyle->UpdateFontSize(FONT_SIZE_PX);
    sourceSpan->ClearLpxFlag(SpanItem::LPX_FLAG_FontSize);
    EXPECT_FALSE(sourceSpan->HasLpxUnitStyle());

    auto targetSpan = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(targetSpan, nullptr);
    targetSpan->fontStyle->UpdateFontSize(FONT_SIZE_LPX);
    targetSpan->SetLpxFlag(SpanItem::LPX_FLAG_FontSize);
    EXPECT_TRUE(targetSpan->HasLpxUnitStyle());

    sourceSpan->CopyBaseSpanItem(targetSpan);
    EXPECT_FALSE(targetSpan->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, SpanItemGetSameStyleSpanItemLpx001, TestSize.Level0)
{
    auto sourceSpan = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(sourceSpan, nullptr);
    sourceSpan->fontStyle->UpdateFontSize(FONT_SIZE_LPX);
    sourceSpan->SetLpxFlag(SpanItem::LPX_FLAG_FontSize);
    EXPECT_TRUE(sourceSpan->HasLpxUnitStyle());

    auto sameSpan = sourceSpan->GetSameStyleSpanItem();
    ASSERT_NE(sameSpan, nullptr);
    EXPECT_TRUE(sameSpan->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, SpanNodeUpdateWithoutFlushDirtyLpx001, TestSize.Level0)
{
    auto spanNode = SpanNode::GetOrCreateSpanNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(spanNode, nullptr);
    auto spanItem = spanNode->GetSpanItem();
    ASSERT_NE(spanItem, nullptr);
    EXPECT_FALSE(spanItem->HasLpxUnitStyle());

    spanNode->UpdateFontSizeWithoutFlushDirty(FONT_SIZE_LPX);
    EXPECT_TRUE(spanItem->HasLpxUnitStyle());

    spanNode->UpdateFontSizeWithoutFlushDirty(FONT_SIZE_PX);
    EXPECT_FALSE(spanItem->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, SpanNodeUpdateLineHeightWithoutFlushDirtyLpx001, TestSize.Level0)
{
    auto spanNode = SpanNode::GetOrCreateSpanNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(spanNode, nullptr);
    auto spanItem = spanNode->GetSpanItem();
    ASSERT_NE(spanItem, nullptr);
    EXPECT_FALSE(spanItem->HasLpxUnitStyle());

    spanNode->UpdateLineHeightWithoutFlushDirty(LINE_HEIGHT_LPX);
    EXPECT_TRUE(spanItem->HasLpxUnitStyle());

    spanNode->UpdateLineHeightWithoutFlushDirty(LINE_HEIGHT_PX);
    EXPECT_FALSE(spanItem->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, RichEditorPatternUpdateLpxUnitFlag001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    EXPECT_FALSE(richEditorPattern->HasLpxUnitStyle());

    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    spanItem->content = INIT_VALUE_1;
    spanItem->fontStyle->UpdateFontSize(FONT_SIZE_LPX);
    spanItem->SetLpxFlag(SpanItem::LPX_FLAG_FontSize);
    richEditorPattern->spans_.emplace_back(spanItem);
    richEditorPattern->UpdateLpxUnitFlag();
    EXPECT_TRUE(richEditorPattern->HasLpxUnitStyle());

    richEditorPattern->spans_.clear();
    richEditorPattern->UpdateLpxUnitFlag();
    EXPECT_FALSE(richEditorPattern->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, RichEditorPatternUpdateLpxUnitFlag002, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto spanItem1 = AceType::MakeRefPtr<SpanItem>();
    spanItem1->content = INIT_VALUE_1;
    spanItem1->fontStyle->UpdateFontSize(FONT_SIZE_PX);
    spanItem1->ClearLpxFlag(SpanItem::LPX_FLAG_FontSize);
    richEditorPattern->spans_.emplace_back(spanItem1);
    richEditorPattern->UpdateLpxUnitFlag();
    EXPECT_FALSE(richEditorPattern->HasLpxUnitStyle());

    auto spanItem2 = AceType::MakeRefPtr<SpanItem>();
    spanItem2->content = INIT_VALUE_2;
    spanItem2->fontStyle->UpdateFontSize(FONT_SIZE_LPX);
    spanItem2->SetLpxFlag(SpanItem::LPX_FLAG_FontSize);
    richEditorPattern->spans_.emplace_back(spanItem2);
    richEditorPattern->UpdateLpxUnitFlag();
    EXPECT_TRUE(richEditorPattern->HasLpxUnitStyle());

    richEditorPattern->spans_.remove(spanItem2);
    richEditorPattern->UpdateLpxUnitFlag();
    EXPECT_FALSE(richEditorPattern->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, SpanNodeRecreateMacroLpx001, TestSize.Level0)
{
    auto spanNode = SpanNode::GetOrCreateSpanNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(spanNode, nullptr);
    auto spanItem = spanNode->GetSpanItem();
    ASSERT_NE(spanItem, nullptr);
    EXPECT_FALSE(spanItem->HasLpxUnitStyle());

    spanNode->UpdateTextCase(TextCase::LOWERCASE);
    EXPECT_FALSE(spanItem->HasLpxUnitStyle());

    spanNode->UpdateSymbolType(SymbolType::SYSTEM);
    EXPECT_FALSE(spanItem->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, SpanNodeResetStrokeWidthLpx001, TestSize.Level0)
{
    auto spanNode = SpanNode::GetOrCreateSpanNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(spanNode, nullptr);
    auto spanItem = spanNode->GetSpanItem();
    ASSERT_NE(spanItem, nullptr);

    spanNode->UpdateStrokeWidth(STROKE_WIDTH_LPX);
    EXPECT_TRUE(spanItem->HasLpxUnitStyle());

    spanNode->ResetStrokeWidth();
    EXPECT_FALSE(spanItem->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, SpanNodeResetLetterSpacingLpx001, TestSize.Level0)
{
    auto spanNode = SpanNode::GetOrCreateSpanNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(spanNode, nullptr);
    auto spanItem = spanNode->GetSpanItem();
    ASSERT_NE(spanItem, nullptr);

    spanNode->UpdateLetterSpacing(LETTER_SPACING_LPX);
    EXPECT_TRUE(spanItem->HasLpxUnitStyle());

    spanNode->ResetLetterSpacing();
    EXPECT_FALSE(spanItem->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, SpanNodeResetLineSpacingLpx001, TestSize.Level0)
{
    auto spanNode = SpanNode::GetOrCreateSpanNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(spanNode, nullptr);
    auto spanItem = spanNode->GetSpanItem();
    ASSERT_NE(spanItem, nullptr);

    spanNode->UpdateLineSpacing(LINE_SPACING_LPX);
    EXPECT_TRUE(spanItem->HasLpxUnitStyle());

    spanNode->ResetLineSpacing();
    EXPECT_FALSE(spanItem->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, SpanNodeResetParagraphSpacingLpx001, TestSize.Level0)
{
    auto spanNode = SpanNode::GetOrCreateSpanNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(spanNode, nullptr);
    auto spanItem = spanNode->GetSpanItem();
    ASSERT_NE(spanItem, nullptr);

    spanNode->UpdateParagraphSpacing(PARAGRAPH_SPACING_LPX);
    EXPECT_TRUE(spanItem->HasLpxUnitStyle());

    spanNode->ResetParagraphSpacing();
    EXPECT_FALSE(spanItem->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, SpanItemNullFontStyle001, TestSize.Level0)
{
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);
    spanItem->fontStyle = nullptr;
    EXPECT_FALSE(spanItem->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, SpanItemNullTextLineStyle001, TestSize.Level0)
{
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);
    spanItem->textLineStyle = nullptr;
    EXPECT_FALSE(spanItem->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, SpanItemBothNullStyle001, TestSize.Level0)
{
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);
    spanItem->fontStyle = nullptr;
    spanItem->textLineStyle = nullptr;
    EXPECT_FALSE(spanItem->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, RichEditorPatternLpxFlagAddSymbolSpan001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    EXPECT_FALSE(richEditorPattern->HasLpxUnitStyle());

    TextStyle style;
    style.SetFontSize(FONT_SIZE_LPX);
    SymbolSpanOptions options;
    options.symbolId = SYMBOL_ID;
    options.style = style;
    richEditorController->AddSymbolSpan(options);
    EXPECT_TRUE(richEditorPattern->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, RichEditorPatternLpxFlagAddSymbolSpan002, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    EXPECT_FALSE(richEditorPattern->HasLpxUnitStyle());

    TextStyle style;
    style.SetFontSize(FONT_SIZE_PX);
    SymbolSpanOptions options;
    options.symbolId = SYMBOL_ID;
    options.style = style;
    richEditorController->AddSymbolSpan(options);
    EXPECT_FALSE(richEditorPattern->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, RichEditorPatternLpxFlagUpdateParagraphStyle001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    TextStyle style;
    style.SetFontSize(FONT_SIZE_PX);
    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    options.style = style;
    richEditorController->AddTextSpan(options);
    EXPECT_FALSE(richEditorPattern->HasLpxUnitStyle());

    struct UpdateParagraphStyle paragraphStyle;
    paragraphStyle.paragraphSpacing = PARAGRAPH_SPACING_LPX;
    richEditorController->UpdateParagraphStyle(0, 6, paragraphStyle);
    EXPECT_TRUE(richEditorPattern->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, RichEditorPatternLpxFlagUpdateParagraphStyle002, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    TextStyle style;
    style.SetFontSize(FONT_SIZE_PX);
    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    options.style = style;
    richEditorController->AddTextSpan(options);
    EXPECT_FALSE(richEditorPattern->HasLpxUnitStyle());

    struct UpdateParagraphStyle paragraphStyle;
    paragraphStyle.paragraphSpacing = Dimension(15.0, DimensionUnit::PX);
    richEditorController->UpdateParagraphStyle(0, 6, paragraphStyle);
    EXPECT_FALSE(richEditorPattern->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, SpanNodeUpdateLineSpacingLpx001, TestSize.Level0)
{
    auto spanNode = SpanNode::GetOrCreateSpanNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(spanNode, nullptr);
    auto spanItem = spanNode->GetSpanItem();
    ASSERT_NE(spanItem, nullptr);
    EXPECT_FALSE(spanItem->HasLpxUnitStyle());

    spanNode->UpdateLineSpacing(LINE_SPACING_LPX);
    EXPECT_TRUE(spanItem->HasLpxUnitStyle());

    spanNode->UpdateLineSpacing(Dimension(8.0, DimensionUnit::PX));
    EXPECT_FALSE(spanItem->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, SpanNodeUpdateParagraphSpacingLpx001, TestSize.Level0)
{
    auto spanNode = SpanNode::GetOrCreateSpanNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(spanNode, nullptr);
    auto spanItem = spanNode->GetSpanItem();
    ASSERT_NE(spanItem, nullptr);
    EXPECT_FALSE(spanItem->HasLpxUnitStyle());

    spanNode->UpdateParagraphSpacing(PARAGRAPH_SPACING_LPX);
    EXPECT_TRUE(spanItem->HasLpxUnitStyle());

    spanNode->UpdateParagraphSpacing(Dimension(15.0, DimensionUnit::PX));
    EXPECT_FALSE(spanItem->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, SpanNodeUpdateLetterSpacingWithoutFlushDirty001, TestSize.Level0)
{
    auto spanNode = SpanNode::GetOrCreateSpanNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(spanNode, nullptr);
    auto spanItem = spanNode->GetSpanItem();
    ASSERT_NE(spanItem, nullptr);
    EXPECT_FALSE(spanItem->HasLpxUnitStyle());

    spanNode->UpdateLetterSpacingWithoutFlushDirty(LETTER_SPACING_LPX);
    EXPECT_TRUE(spanItem->HasLpxUnitStyle());

    spanNode->UpdateLetterSpacingWithoutFlushDirty(LETTER_SPACING_PX);
    EXPECT_FALSE(spanItem->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, SpanNodeUpdateStrokeWidthWithoutFlushDirty001, TestSize.Level0)
{
    auto spanNode = SpanNode::GetOrCreateSpanNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(spanNode, nullptr);
    auto spanItem = spanNode->GetSpanItem();
    ASSERT_NE(spanItem, nullptr);
    EXPECT_FALSE(spanItem->HasLpxUnitStyle());

    spanNode->UpdateStrokeWidthWithoutFlushDirty(STROKE_WIDTH_LPX);
    EXPECT_TRUE(spanItem->HasLpxUnitStyle());

    spanNode->UpdateStrokeWidthWithoutFlushDirty(STROKE_WIDTH_PX);
    EXPECT_FALSE(spanItem->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, SpanNodeUpdateLineSpacingWithoutFlushDirty001, TestSize.Level0)
{
    auto spanNode = SpanNode::GetOrCreateSpanNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(spanNode, nullptr);
    auto spanItem = spanNode->GetSpanItem();
    ASSERT_NE(spanItem, nullptr);
    EXPECT_FALSE(spanItem->HasLpxUnitStyle());

    spanNode->UpdateLineSpacingWithoutFlushDirty(LINE_SPACING_LPX);
    EXPECT_TRUE(spanItem->HasLpxUnitStyle());

    spanNode->UpdateLineSpacingWithoutFlushDirty(Dimension(8.0, DimensionUnit::PX));
    EXPECT_FALSE(spanItem->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, SpanNodeUpdateParagraphSpacingWithoutFlushDirty001, TestSize.Level0)
{
    auto spanNode = SpanNode::GetOrCreateSpanNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(spanNode, nullptr);
    auto spanItem = spanNode->GetSpanItem();
    ASSERT_NE(spanItem, nullptr);
    EXPECT_FALSE(spanItem->HasLpxUnitStyle());

    spanNode->UpdateParagraphSpacingWithoutFlushDirty(PARAGRAPH_SPACING_LPX);
    EXPECT_TRUE(spanItem->HasLpxUnitStyle());

    spanNode->UpdateParagraphSpacingWithoutFlushDirty(Dimension(15.0, DimensionUnit::PX));
    EXPECT_FALSE(spanItem->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, ImageSpanItemUpdateLpxUnitFlagMargin001, TestSize.Level0)
{
    auto imageSpanItem = AceType::MakeRefPtr<ImageSpanItem>();
    ASSERT_NE(imageSpanItem, nullptr);
    EXPECT_FALSE(imageSpanItem->HasLpxUnitStyle());

    ImageSpanOptions options;
    ImageSpanAttribute imageAttr;
    MarginProperty marginProp;
    marginProp.left = CalcLength(Dimension(10.0, DimensionUnit::LPX));
    imageAttr.marginProp = marginProp;
    options.imageAttribute = imageAttr;
    imageSpanItem->SetImageSpanOptions(options);
    EXPECT_TRUE(imageSpanItem->HasLpxUnitStyle());

    marginProp.left = CalcLength(Dimension(10.0, DimensionUnit::PX));
    imageAttr.marginProp = marginProp;
    options.imageAttribute = imageAttr;
    imageSpanItem->SetImageSpanOptions(options);
    EXPECT_FALSE(imageSpanItem->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, ImageSpanItemUpdateLpxUnitFlagMarginRight001, TestSize.Level0)
{
    auto imageSpanItem = AceType::MakeRefPtr<ImageSpanItem>();
    ASSERT_NE(imageSpanItem, nullptr);
    EXPECT_FALSE(imageSpanItem->HasLpxUnitStyle());

    ImageSpanOptions options;
    ImageSpanAttribute imageAttr;
    MarginProperty marginProp;
    marginProp.right = CalcLength(Dimension(10.0, DimensionUnit::LPX));
    imageAttr.marginProp = marginProp;
    options.imageAttribute = imageAttr;
    imageSpanItem->SetImageSpanOptions(options);
    EXPECT_TRUE(imageSpanItem->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, ImageSpanItemUpdateLpxUnitFlagMarginTop001, TestSize.Level0)
{
    auto imageSpanItem = AceType::MakeRefPtr<ImageSpanItem>();
    ASSERT_NE(imageSpanItem, nullptr);
    EXPECT_FALSE(imageSpanItem->HasLpxUnitStyle());

    ImageSpanOptions options;
    ImageSpanAttribute imageAttr;
    MarginProperty marginProp;
    marginProp.top = CalcLength(Dimension(10.0, DimensionUnit::LPX));
    imageAttr.marginProp = marginProp;
    options.imageAttribute = imageAttr;
    imageSpanItem->SetImageSpanOptions(options);
    EXPECT_TRUE(imageSpanItem->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, ImageSpanItemUpdateLpxUnitFlagMarginBottom001, TestSize.Level0)
{
    auto imageSpanItem = AceType::MakeRefPtr<ImageSpanItem>();
    ASSERT_NE(imageSpanItem, nullptr);
    EXPECT_FALSE(imageSpanItem->HasLpxUnitStyle());

    ImageSpanOptions options;
    ImageSpanAttribute imageAttr;
    MarginProperty marginProp;
    marginProp.bottom = CalcLength(Dimension(10.0, DimensionUnit::LPX));
    imageAttr.marginProp = marginProp;
    options.imageAttribute = imageAttr;
    imageSpanItem->SetImageSpanOptions(options);
    EXPECT_TRUE(imageSpanItem->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, ImageSpanItemUpdateLpxUnitFlagMarginStart001, TestSize.Level0)
{
    auto imageSpanItem = AceType::MakeRefPtr<ImageSpanItem>();
    ASSERT_NE(imageSpanItem, nullptr);
    EXPECT_FALSE(imageSpanItem->HasLpxUnitStyle());

    ImageSpanOptions options;
    ImageSpanAttribute imageAttr;
    MarginProperty marginProp;
    marginProp.start = CalcLength(Dimension(10.0, DimensionUnit::LPX));
    imageAttr.marginProp = marginProp;
    options.imageAttribute = imageAttr;
    imageSpanItem->SetImageSpanOptions(options);
    EXPECT_TRUE(imageSpanItem->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, ImageSpanItemUpdateLpxUnitFlagMarginEnd001, TestSize.Level0)
{
    auto imageSpanItem = AceType::MakeRefPtr<ImageSpanItem>();
    ASSERT_NE(imageSpanItem, nullptr);
    EXPECT_FALSE(imageSpanItem->HasLpxUnitStyle());

    ImageSpanOptions options;
    ImageSpanAttribute imageAttr;
    MarginProperty marginProp;
    marginProp.end = CalcLength(Dimension(10.0, DimensionUnit::LPX));
    imageAttr.marginProp = marginProp;
    options.imageAttribute = imageAttr;
    imageSpanItem->SetImageSpanOptions(options);
    EXPECT_TRUE(imageSpanItem->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, ImageSpanItemUpdateLpxUnitFlagPadding001, TestSize.Level0)
{
    auto imageSpanItem = AceType::MakeRefPtr<ImageSpanItem>();
    ASSERT_NE(imageSpanItem, nullptr);
    EXPECT_FALSE(imageSpanItem->HasLpxUnitStyle());

    ImageSpanOptions options;
    ImageSpanAttribute imageAttr;
    PaddingProperty paddingProp;
    paddingProp.left = CalcLength(Dimension(10.0, DimensionUnit::LPX));
    imageAttr.paddingProp = paddingProp;
    options.imageAttribute = imageAttr;
    imageSpanItem->SetImageSpanOptions(options);
    EXPECT_TRUE(imageSpanItem->HasLpxUnitStyle());

    paddingProp.left = CalcLength(Dimension(10.0, DimensionUnit::PX));
    imageAttr.paddingProp = paddingProp;
    options.imageAttribute = imageAttr;
    imageSpanItem->SetImageSpanOptions(options);
    EXPECT_FALSE(imageSpanItem->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, ImageSpanItemUpdateLpxUnitFlagPaddingRight001, TestSize.Level0)
{
    auto imageSpanItem = AceType::MakeRefPtr<ImageSpanItem>();
    ASSERT_NE(imageSpanItem, nullptr);
    EXPECT_FALSE(imageSpanItem->HasLpxUnitStyle());

    ImageSpanOptions options;
    ImageSpanAttribute imageAttr;
    PaddingProperty paddingProp;
    paddingProp.right = CalcLength(Dimension(10.0, DimensionUnit::LPX));
    imageAttr.paddingProp = paddingProp;
    options.imageAttribute = imageAttr;
    imageSpanItem->SetImageSpanOptions(options);
    EXPECT_TRUE(imageSpanItem->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, ImageSpanItemUpdateLpxUnitFlagPaddingTop001, TestSize.Level0)
{
    auto imageSpanItem = AceType::MakeRefPtr<ImageSpanItem>();
    ASSERT_NE(imageSpanItem, nullptr);
    EXPECT_FALSE(imageSpanItem->HasLpxUnitStyle());

    ImageSpanOptions options;
    ImageSpanAttribute imageAttr;
    PaddingProperty paddingProp;
    paddingProp.top = CalcLength(Dimension(10.0, DimensionUnit::LPX));
    imageAttr.paddingProp = paddingProp;
    options.imageAttribute = imageAttr;
    imageSpanItem->SetImageSpanOptions(options);
    EXPECT_TRUE(imageSpanItem->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, ImageSpanItemUpdateLpxUnitFlagPaddingBottom001, TestSize.Level0)
{
    auto imageSpanItem = AceType::MakeRefPtr<ImageSpanItem>();
    ASSERT_NE(imageSpanItem, nullptr);
    EXPECT_FALSE(imageSpanItem->HasLpxUnitStyle());

    ImageSpanOptions options;
    ImageSpanAttribute imageAttr;
    PaddingProperty paddingProp;
    paddingProp.bottom = CalcLength(Dimension(10.0, DimensionUnit::LPX));
    imageAttr.paddingProp = paddingProp;
    options.imageAttribute = imageAttr;
    imageSpanItem->SetImageSpanOptions(options);
    EXPECT_TRUE(imageSpanItem->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, ImageSpanItemUpdateLpxUnitFlagPaddingStart001, TestSize.Level0)
{
    auto imageSpanItem = AceType::MakeRefPtr<ImageSpanItem>();
    ASSERT_NE(imageSpanItem, nullptr);
    EXPECT_FALSE(imageSpanItem->HasLpxUnitStyle());

    ImageSpanOptions options;
    ImageSpanAttribute imageAttr;
    PaddingProperty paddingProp;
    paddingProp.start = CalcLength(Dimension(10.0, DimensionUnit::LPX));
    imageAttr.paddingProp = paddingProp;
    options.imageAttribute = imageAttr;
    imageSpanItem->SetImageSpanOptions(options);
    EXPECT_TRUE(imageSpanItem->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, ImageSpanItemUpdateLpxUnitFlagPaddingEnd001, TestSize.Level0)
{
    auto imageSpanItem = AceType::MakeRefPtr<ImageSpanItem>();
    ASSERT_NE(imageSpanItem, nullptr);
    EXPECT_FALSE(imageSpanItem->HasLpxUnitStyle());

    ImageSpanOptions options;
    ImageSpanAttribute imageAttr;
    PaddingProperty paddingProp;
    paddingProp.end = CalcLength(Dimension(10.0, DimensionUnit::LPX));
    imageAttr.paddingProp = paddingProp;
    options.imageAttribute = imageAttr;
    imageSpanItem->SetImageSpanOptions(options);
    EXPECT_TRUE(imageSpanItem->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, ImageSpanItemUpdateLpxUnitFlagBorderRadius001, TestSize.Level0)
{
    auto imageSpanItem = AceType::MakeRefPtr<ImageSpanItem>();
    ASSERT_NE(imageSpanItem, nullptr);
    EXPECT_FALSE(imageSpanItem->HasLpxUnitStyle());

    ImageSpanOptions options;
    ImageSpanAttribute imageAttr;
    BorderRadiusProperty borderRadius;
    borderRadius.radiusTopLeft = Dimension(10.0, DimensionUnit::LPX);
    imageAttr.borderRadius = borderRadius;
    options.imageAttribute = imageAttr;
    imageSpanItem->SetImageSpanOptions(options);
    EXPECT_TRUE(imageSpanItem->HasLpxUnitStyle());

    borderRadius.radiusTopLeft = Dimension(10.0, DimensionUnit::PX);
    imageAttr.borderRadius = borderRadius;
    options.imageAttribute = imageAttr;
    imageSpanItem->SetImageSpanOptions(options);
    EXPECT_FALSE(imageSpanItem->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, ImageSpanItemUpdateLpxUnitFlagBorderRadiusTopRight001, TestSize.Level0)
{
    auto imageSpanItem = AceType::MakeRefPtr<ImageSpanItem>();
    ASSERT_NE(imageSpanItem, nullptr);
    EXPECT_FALSE(imageSpanItem->HasLpxUnitStyle());

    ImageSpanOptions options;
    ImageSpanAttribute imageAttr;
    BorderRadiusProperty borderRadius;
    borderRadius.radiusTopRight = Dimension(10.0, DimensionUnit::LPX);
    imageAttr.borderRadius = borderRadius;
    options.imageAttribute = imageAttr;
    imageSpanItem->SetImageSpanOptions(options);
    EXPECT_TRUE(imageSpanItem->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, ImageSpanItemUpdateLpxUnitFlagBorderRadiusBottomLeft001, TestSize.Level0)
{
    auto imageSpanItem = AceType::MakeRefPtr<ImageSpanItem>();
    ASSERT_NE(imageSpanItem, nullptr);
    EXPECT_FALSE(imageSpanItem->HasLpxUnitStyle());

    ImageSpanOptions options;
    ImageSpanAttribute imageAttr;
    BorderRadiusProperty borderRadius;
    borderRadius.radiusBottomLeft = Dimension(10.0, DimensionUnit::LPX);
    imageAttr.borderRadius = borderRadius;
    options.imageAttribute = imageAttr;
    imageSpanItem->SetImageSpanOptions(options);
    EXPECT_TRUE(imageSpanItem->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, ImageSpanItemUpdateLpxUnitFlagBorderRadiusBottomRight001, TestSize.Level0)
{
    auto imageSpanItem = AceType::MakeRefPtr<ImageSpanItem>();
    ASSERT_NE(imageSpanItem, nullptr);
    EXPECT_FALSE(imageSpanItem->HasLpxUnitStyle());

    ImageSpanOptions options;
    ImageSpanAttribute imageAttr;
    BorderRadiusProperty borderRadius;
    borderRadius.radiusBottomRight = Dimension(10.0, DimensionUnit::LPX);
    imageAttr.borderRadius = borderRadius;
    options.imageAttribute = imageAttr;
    imageSpanItem->SetImageSpanOptions(options);
    EXPECT_TRUE(imageSpanItem->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, ImageSpanItemUpdateLpxUnitFlagBorderRadiusTopStart001, TestSize.Level0)
{
    auto imageSpanItem = AceType::MakeRefPtr<ImageSpanItem>();
    ASSERT_NE(imageSpanItem, nullptr);
    EXPECT_FALSE(imageSpanItem->HasLpxUnitStyle());

    ImageSpanOptions options;
    ImageSpanAttribute imageAttr;
    BorderRadiusProperty borderRadius;
    borderRadius.radiusTopStart = Dimension(10.0, DimensionUnit::LPX);
    imageAttr.borderRadius = borderRadius;
    options.imageAttribute = imageAttr;
    imageSpanItem->SetImageSpanOptions(options);
    EXPECT_TRUE(imageSpanItem->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, ImageSpanItemUpdateLpxUnitFlagBorderRadiusTopEnd001, TestSize.Level0)
{
    auto imageSpanItem = AceType::MakeRefPtr<ImageSpanItem>();
    ASSERT_NE(imageSpanItem, nullptr);
    EXPECT_FALSE(imageSpanItem->HasLpxUnitStyle());

    ImageSpanOptions options;
    ImageSpanAttribute imageAttr;
    BorderRadiusProperty borderRadius;
    borderRadius.radiusTopEnd = Dimension(10.0, DimensionUnit::LPX);
    imageAttr.borderRadius = borderRadius;
    options.imageAttribute = imageAttr;
    imageSpanItem->SetImageSpanOptions(options);
    EXPECT_TRUE(imageSpanItem->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, ImageSpanItemUpdateLpxUnitFlagBorderRadiusBottomStart001, TestSize.Level0)
{
    auto imageSpanItem = AceType::MakeRefPtr<ImageSpanItem>();
    ASSERT_NE(imageSpanItem, nullptr);
    EXPECT_FALSE(imageSpanItem->HasLpxUnitStyle());

    ImageSpanOptions options;
    ImageSpanAttribute imageAttr;
    BorderRadiusProperty borderRadius;
    borderRadius.radiusBottomStart = Dimension(10.0, DimensionUnit::LPX);
    imageAttr.borderRadius = borderRadius;
    options.imageAttribute = imageAttr;
    imageSpanItem->SetImageSpanOptions(options);
    EXPECT_TRUE(imageSpanItem->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, ImageSpanItemUpdateLpxUnitFlagBorderRadiusBottomEnd001, TestSize.Level0)
{
    auto imageSpanItem = AceType::MakeRefPtr<ImageSpanItem>();
    ASSERT_NE(imageSpanItem, nullptr);
    EXPECT_FALSE(imageSpanItem->HasLpxUnitStyle());

    ImageSpanOptions options;
    ImageSpanAttribute imageAttr;
    BorderRadiusProperty borderRadius;
    borderRadius.radiusBottomEnd = Dimension(10.0, DimensionUnit::LPX);
    imageAttr.borderRadius = borderRadius;
    options.imageAttribute = imageAttr;
    imageSpanItem->SetImageSpanOptions(options);
    EXPECT_TRUE(imageSpanItem->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, ImageSpanItemResetImageSpanOptions001, TestSize.Level0)
{
    auto imageSpanItem = AceType::MakeRefPtr<ImageSpanItem>();
    ASSERT_NE(imageSpanItem, nullptr);
    EXPECT_FALSE(imageSpanItem->HasLpxUnitStyle());

    ImageSpanOptions options;
    ImageSpanAttribute imageAttr;
    MarginProperty marginProp;
    marginProp.left = CalcLength(Dimension(10.0, DimensionUnit::LPX));
    imageAttr.marginProp = marginProp;
    options.imageAttribute = imageAttr;
    imageSpanItem->SetImageSpanOptions(options);
    EXPECT_TRUE(imageSpanItem->HasLpxUnitStyle());

    imageSpanItem->ResetImageSpanOptions();
    EXPECT_FALSE(imageSpanItem->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, ImageSpanItemGetSameStyleSpanItem001, TestSize.Level0)
{
    auto imageSpanItem = AceType::MakeRefPtr<ImageSpanItem>();
    ASSERT_NE(imageSpanItem, nullptr);
    EXPECT_FALSE(imageSpanItem->HasLpxUnitStyle());

    ImageSpanOptions options;
    ImageSpanAttribute imageAttr;
    MarginProperty marginProp;
    marginProp.left = CalcLength(Dimension(10.0, DimensionUnit::LPX));
    imageAttr.marginProp = marginProp;
    options.imageAttribute = imageAttr;
    imageSpanItem->SetImageSpanOptions(options);
    EXPECT_TRUE(imageSpanItem->HasLpxUnitStyle());

    auto sameSpan = AceType::DynamicCast<ImageSpanItem>(imageSpanItem->GetSameStyleSpanItem());
    ASSERT_NE(sameSpan, nullptr);
    EXPECT_TRUE(sameSpan->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, ImageSpanItemGetSameStyleSpanItem002, TestSize.Level0)
{
    auto imageSpanItem = AceType::MakeRefPtr<ImageSpanItem>();
    ASSERT_NE(imageSpanItem, nullptr);
    EXPECT_FALSE(imageSpanItem->HasLpxUnitStyle());

    ImageSpanOptions options;
    ImageSpanAttribute imageAttr;
    MarginProperty marginProp;
    marginProp.left = CalcLength(Dimension(10.0, DimensionUnit::PX));
    imageAttr.marginProp = marginProp;
    options.imageAttribute = imageAttr;
    imageSpanItem->SetImageSpanOptions(options);
    EXPECT_FALSE(imageSpanItem->HasLpxUnitStyle());

    auto sameSpan = AceType::DynamicCast<ImageSpanItem>(imageSpanItem->GetSameStyleSpanItem());
    ASSERT_NE(sameSpan, nullptr);
    EXPECT_FALSE(sameSpan->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, ImageSpanItemNoImageAttribute001, TestSize.Level0)
{
    auto imageSpanItem = AceType::MakeRefPtr<ImageSpanItem>();
    ASSERT_NE(imageSpanItem, nullptr);
    EXPECT_FALSE(imageSpanItem->HasLpxUnitStyle());

    ImageSpanOptions options;
    imageSpanItem->SetImageSpanOptions(options);
    EXPECT_FALSE(imageSpanItem->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, ImageSpanItemCombinedLpx001, TestSize.Level0)
{
    auto imageSpanItem = AceType::MakeRefPtr<ImageSpanItem>();
    ASSERT_NE(imageSpanItem, nullptr);
    EXPECT_FALSE(imageSpanItem->HasLpxUnitStyle());

    imageSpanItem->fontStyle->UpdateFontSize(FONT_SIZE_LPX);
    imageSpanItem->SetLpxFlag(SpanItem::LPX_FLAG_FontSize);
    EXPECT_TRUE(imageSpanItem->HasLpxUnitStyle());

    ImageSpanOptions options;
    ImageSpanAttribute imageAttr;
    MarginProperty marginProp;
    marginProp.left = CalcLength(Dimension(10.0, DimensionUnit::PX));
    imageAttr.marginProp = marginProp;
    options.imageAttribute = imageAttr;
    imageSpanItem->SetImageSpanOptions(options);
    EXPECT_TRUE(imageSpanItem->HasLpxUnitStyle());

    imageSpanItem->fontStyle->UpdateFontSize(FONT_SIZE_PX);
    imageSpanItem->ClearLpxFlag(SpanItem::LPX_FLAG_FontSize);
    imageSpanItem->SetImageSpanOptions(options);
    EXPECT_FALSE(imageSpanItem->HasLpxUnitStyle());
}

HWTEST_F(RichEditorLpxTestNg, ImageSpanItemMultiplePropertiesLpx001, TestSize.Level0)
{
    auto imageSpanItem = AceType::MakeRefPtr<ImageSpanItem>();
    ASSERT_NE(imageSpanItem, nullptr);
    EXPECT_FALSE(imageSpanItem->HasLpxUnitStyle());

    ImageSpanOptions options;
    ImageSpanAttribute imageAttr;
    MarginProperty marginProp;
    marginProp.left = CalcLength(Dimension(10.0, DimensionUnit::PX));
    marginProp.right = CalcLength(Dimension(10.0, DimensionUnit::PX));
    marginProp.top = CalcLength(Dimension(10.0, DimensionUnit::LPX));
    imageAttr.marginProp = marginProp;
    PaddingProperty paddingProp;
    paddingProp.left = CalcLength(Dimension(5.0, DimensionUnit::PX));
    imageAttr.paddingProp = paddingProp;
    BorderRadiusProperty borderRadius;
    borderRadius.radiusTopLeft = Dimension(8.0, DimensionUnit::PX);
    imageAttr.borderRadius = borderRadius;
    options.imageAttribute = imageAttr;
    imageSpanItem->SetImageSpanOptions(options);
    EXPECT_TRUE(imageSpanItem->HasLpxUnitStyle());

    marginProp.top = CalcLength(Dimension(10.0, DimensionUnit::PX));
    imageAttr.marginProp = marginProp;
    options.imageAttribute = imageAttr;
    imageSpanItem->SetImageSpanOptions(options);
    EXPECT_FALSE(imageSpanItem->HasLpxUnitStyle());
}
} // namespace OHOS::Ace::NG