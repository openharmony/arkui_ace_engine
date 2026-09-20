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
#include "rich_editor_test_min.h"
#include "base/utils/utf_helper.h"
#include "core/components_ng/pattern/text/span_model_ng.h"
#include "test/mock/frameworks/core/components_ng/render/mock_paragraph.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/rosen/mock_canvas.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper_node.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace;

namespace OHOS::Ace::NG {
void RichEditorCommonTestNg::AddSpan(const std::string& content)
{
    AddSpan(UtfUtils::Str8ToStr16(content));
}

void RichEditorCommonTestNg::AddSpan(const std::u16string& content)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    SpanModelNG spanModelNG;
    spanModelNG.Create(content);
    spanModelNG.SetFontSize(FONT_SIZE_VALUE);
    spanModelNG.SetTextColor(TEXT_COLOR_VALUE);
    spanModelNG.SetItalicFontStyle(ITALIC_FONT_STYLE_VALUE);
    spanModelNG.SetFontWeight(FONT_WEIGHT_VALUE);
    spanModelNG.SetFontFamily(FONT_FAMILY_VALUE);
    spanModelNG.SetTextDecoration(TEXT_DECORATION_VALUE);
    spanModelNG.SetTextDecorationColor(TEXT_DECORATION_COLOR_VALUE);
    spanModelNG.SetTextCase(TEXT_CASE_VALUE);
    spanModelNG.SetLetterSpacing(LETTER_SPACING);
    spanModelNG.SetLineHeight(LINE_HEIGHT_VALUE);
    spanModelNG.SetTextShadow(SHADOWS);
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->Finish());
    spanNode->MountToParent(contentNode, contentNode->children_.size());
    richEditorPattern->spans_.emplace_back(spanNode->spanItem_);
    richEditorPattern->childNodes_.push_back(spanNode);
    richEditorPattern->UpdateSpanPosition();
}

void RichEditorCommonTestNg::AddImageSpan()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto imageNode = FrameNode::GetOrCreateFrameNode(
        V2::IMAGE_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<ImagePattern>(); });
    auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    ImageSourceInfo imageInfo(IMAGE_VALUE, BUNDLE_NAME, MODULE_NAME);
    imageLayoutProperty->UpdateImageSourceInfo(imageInfo);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);
    imageNode->MountToParent(contentNode, contentNode->children_.size());
    auto spanItem = AceType::MakeRefPtr<ImageSpanItem>();
    spanItem->content = u" ";
    spanItem->placeholderIndex = 0;
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->spans_.emplace_back(spanItem);
    int32_t spanTextLength = 0;
    for (auto& span : richEditorPattern->spans_) {
        spanTextLength += span->content.length();
        span->position = spanTextLength;
    }
}

void RichEditorCommonTestNg::AddParagraph(TestParagraphItem testParagraphItem)
{
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->paragraphs_.AddParagraph(
        { .paragraph = paragraph, .start = testParagraphItem.start, .end = testParagraphItem.end });
    for (const auto& [index, offset] : testParagraphItem.indexOffsetMap) {
        EXPECT_CALL(*paragraph, GetGlyphIndexByCoordinate(offset, _)).WillRepeatedly(Return(index));
        PositionWithAffinity positionWithAffinity(index, TextAffinity::UPSTREAM);
        EXPECT_CALL(*paragraph, GetGlyphPositionAtCoordinate(offset)).WillRepeatedly(Return(positionWithAffinity));
    }
    for (auto& cursorItem : testParagraphItem.testCursorItems) {
        EXPECT_CALL(*paragraph, ComputeOffsetForCaretDownstream(cursorItem.index, _, _))
            .WillRepeatedly(DoAll(SetArgReferee<1>(cursorItem.caretMetricsFDown), Return(true)));
        EXPECT_CALL(*paragraph, ComputeOffsetForCaretUpstream(cursorItem.index, _, _))
            .WillRepeatedly(DoAll(SetArgReferee<1>(cursorItem.caretMetricsFUp), Return(true)));
        float cursorHeight = 0.0f;
        EXPECT_EQ(richEditorPattern->paragraphs_.ComputeCursorOffset(cursorItem.index, cursorHeight, true),
            cursorItem.caretMetricsFDown.offset);
        EXPECT_EQ(richEditorPattern->paragraphs_.ComputeCursorOffset(cursorItem.index, cursorHeight, false),
            cursorItem.caretMetricsFUp.offset);
    }
    for (auto& paragraphRect : testParagraphItem.testParagraphRects) {
        EXPECT_CALL(*paragraph, GetRectsForRange(paragraphRect.start, paragraphRect.end, _))
            .WillRepeatedly(SetArgReferee<THIRD_PARAM>(paragraphRect.rects));
    }
}

void RichEditorCommonTestNg::ClearParagraph()
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->paragraphs_.Reset();
}

void RichEditorCommonTestNg::ClearSpan()
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);
    contentNode->children_.clear();
    richEditorPattern->spans_.clear();
    richEditorPattern->caretPosition_ = 0;
}

namespace {
constexpr int32_t TEST_MAX_LENGTH = 10;
constexpr float CONTEXT_WIDTH = 300.0f;
constexpr float CONTEXT_HEIGHT = 150.0f;

static void SetupCounterEnabled(const RefPtr<RichEditorPattern>& pattern)
{
    pattern->isSpanStringMode_ = true;
    pattern->maxLength_ = TEST_MAX_LENGTH;
    pattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(u"hello");
    auto layoutProperty = pattern->GetLayoutProperty<RichEditorLayoutProperty>();
    if (layoutProperty) {
        layoutProperty->UpdateShowCounter(true);
    }
}

static RefPtr<RichEditorPattern> CreateNapiPattern()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto node = FrameNode::GetOrCreateFrameNode(
        V2::RICH_EDITOR_ETS_TAG, nodeId,
        []() { return AceType::MakeRefPtr<NapiRichEditorPattern>(); });
    auto pattern = node->GetPattern<RichEditorPattern>();
    pattern->InitScrollablePattern();
    pattern->SetRichEditorController(AceType::MakeRefPtr<RichEditorController>());
    pattern->GetRichEditorController()->SetPattern(AceType::WeakClaim(AceType::RawPtr(pattern)));
    pattern->CreateNodePaintMethod();
    node->GetGeometryNode()->SetContentSize({});
    return pattern;
}
} // namespace

class RichEditorCounterTestCore : public RichEditorTestBase {
public:
    RefPtr<RichEditorPattern> pattern_;
    RefPtr<RichEditorPattern> napiPattern_;

    void SetUp() override
    {
        RichEditorTestBase::SetUp();
        pattern_ = richEditorNode_->GetPattern<RichEditorPattern>();
        napiPattern_ = CreateNapiPattern();
    }
    void TearDown() override
    {
        pattern_ = nullptr;
        napiPattern_ = nullptr;
        RichEditorTestBase::TearDown();
    }
};

HWTEST_F(RichEditorCounterTestCore, CounterStyle001, TestSize.Level1)
{
    EXPECT_FALSE(pattern_->GetShowCounterStyleValue());
    pattern_->SetShowCounterStyleValue(true);
    EXPECT_TRUE(pattern_->GetShowCounterStyleValue());
    pattern_->SetShowCounterStyleValue(false);
    EXPECT_FALSE(pattern_->GetShowCounterStyleValue());
}

HWTEST_F(RichEditorCounterTestCore, GetRealMaxLength001, TestSize.Level1)
{
    EXPECT_EQ(pattern_->GetRealMaxLength(), static_cast<uint32_t>(INT_MAX));
    pattern_->maxLength_ = TEST_MAX_LENGTH;
    EXPECT_EQ(pattern_->GetRealMaxLength(), static_cast<uint32_t>(TEST_MAX_LENGTH));
}

HWTEST_F(RichEditorCounterTestCore, HasMaxLength001, TestSize.Level1)
{
    EXPECT_FALSE(pattern_->HasMaxLength());
    pattern_->maxLength_ = TEST_MAX_LENGTH;
    EXPECT_TRUE(pattern_->HasMaxLength());
}

HWTEST_F(RichEditorCounterTestCore, GetTextLength001, TestSize.Level1)
{
    EXPECT_EQ(pattern_->GetTextLength(), 0u);
}

HWTEST_F(RichEditorCounterTestCore, GetTextValue001, TestSize.Level1)
{
    pattern_->isSpanStringMode_ = true;
    pattern_->styledString_ = AceType::MakeRefPtr<MutableSpanString>(u"hello");
    EXPECT_EQ(pattern_->GetTextValue(), "hello");
}

HWTEST_F(RichEditorCounterTestCore, GetTextValue002, TestSize.Level1)
{
    EXPECT_EQ(pattern_->GetTextValue(), "");
}

HWTEST_F(RichEditorCounterTestCore, GetShowCounterValue001, TestSize.Level1)
{
    EXPECT_FALSE(pattern_->GetShowCounterValue());
    auto layoutProperty = pattern_->GetLayoutProperty<RichEditorLayoutProperty>();
    layoutProperty->UpdateShowCounter(true);
    EXPECT_TRUE(pattern_->GetShowCounterValue());
}

HWTEST_F(RichEditorCounterTestCore, GetShowCounterValueNull001, TestSize.Level1)
{
    auto standalone = AceType::MakeRefPtr<RichEditorPattern>();
    EXPECT_FALSE(standalone->GetShowCounterValue());
}

HWTEST_F(RichEditorCounterTestCore, UpdateMargin001, TestSize.Level1)
{
    MarginProperty margin;
    margin.SetEdges(CalcLength(5.0_vp));
    pattern_->UpdateMargin(margin);
    auto layoutProperty = pattern_->GetLayoutProperty<RichEditorLayoutProperty>();
    EXPECT_TRUE(layoutProperty->HasMarginByUser());
}

HWTEST_F(RichEditorCounterTestCore, UpdateMarginNull001, TestSize.Level1)
{
    auto standalone = AceType::MakeRefPtr<RichEditorPattern>();
    MarginProperty margin;
    standalone->UpdateMargin(margin);
    EXPECT_FALSE(standalone->HasMarginByUser());
}

HWTEST_F(RichEditorCounterTestCore, MarginByUser001, TestSize.Level1)
{
    EXPECT_FALSE(pattern_->HasMarginByUser());
    auto defaultMargin = pattern_->GetMarginByUserValue();
    EXPECT_FALSE(defaultMargin.left.has_value());
}

HWTEST_F(RichEditorCounterTestCore, BorderWidthFlag001, TestSize.Level1)
{
    EXPECT_FALSE(pattern_->HasBorderWidthFlagByUser());
    auto val = pattern_->GetBorderWidthFlagByUserValue();
    EXPECT_FALSE(val.leftDimen.has_value());
    auto layoutProperty = pattern_->GetLayoutProperty<RichEditorLayoutProperty>();
    BorderWidthProperty bw;
    bw.SetBorderWidth(Dimension(2.0_vp));
    layoutProperty->UpdateBorderWidthFlagByUser(bw);
    EXPECT_TRUE(pattern_->HasBorderWidthFlagByUser());
}

HWTEST_F(RichEditorCounterTestCore, BorderColorFlag001, TestSize.Level1)
{
    EXPECT_FALSE(pattern_->HasBorderColorFlagByUser());
    auto val = pattern_->GetBorderColorFlagByUserValue();
    EXPECT_FALSE(val.leftColor.has_value());
    auto layoutProperty = pattern_->GetLayoutProperty<RichEditorLayoutProperty>();
    BorderColorProperty bc;
    bc.SetColor(Color::RED);
    layoutProperty->UpdateBorderColorFlagByUser(bc);
    EXPECT_TRUE(pattern_->HasBorderColorFlagByUser());
}

HWTEST_F(RichEditorCounterTestCore, BorderRadiusFlag001, TestSize.Level1)
{
    EXPECT_FALSE(pattern_->HasBorderRadiusFlagByUser());
    auto val = pattern_->GetBorderRadiusFlagByUserValue();
    EXPECT_FALSE(val.radiusTopLeft.has_value());
    auto layoutProperty = pattern_->GetLayoutProperty<RichEditorLayoutProperty>();
    BorderRadiusProperty br;
    br.SetRadius(Dimension(5.0_vp));
    layoutProperty->UpdateBorderRadiusFlagByUser(br);
    EXPECT_TRUE(pattern_->HasBorderRadiusFlagByUser());
}

HWTEST_F(RichEditorCounterTestCore, InnerBorder001, TestSize.Level1)
{
    EXPECT_FALSE(pattern_->HasInnerBorderColor());
    pattern_->UpdateInnerBorderWidth(2.0f);
    pattern_->UpdateInnerBorderColor(Color::RED);
    auto layoutProperty = pattern_->GetLayoutProperty<RichEditorLayoutProperty>();
    EXPECT_TRUE(layoutProperty->HasInnerBorderWidth());
    EXPECT_TRUE(layoutProperty->HasInnerBorderColor());
    EXPECT_FLOAT_EQ(pattern_->GetInnerBorderWidthValue().ConvertToPx(), 0.0f);
    EXPECT_EQ(pattern_->GetInnerBorderColorValue(Color::BLACK), Color::RED);
}

HWTEST_F(RichEditorCounterTestCore, InnerBorderNull001, TestSize.Level1)
{
    auto standalone = AceType::MakeRefPtr<RichEditorPattern>();
    standalone->UpdateInnerBorderWidth(2.0f);
    standalone->UpdateInnerBorderColor(Color::RED);
    EXPECT_FALSE(standalone->HasInnerBorderColor());
    EXPECT_EQ(standalone->GetInnerBorderWidthValue(), Dimension());
    EXPECT_EQ(standalone->GetInnerBorderColorValue(Color::BLACK), Color::BLACK);
}

HWTEST_F(RichEditorCounterTestCore, UpdateBorderColor001, TestSize.Level1)
{
    BorderColorProperty bc;
    bc.SetColor(Color::RED);
    pattern_->UpdateBorderColor(bc);
    auto rc = richEditorNode_->GetRenderContext();
    EXPECT_TRUE(rc->HasBorderColor());
}

HWTEST_F(RichEditorCounterTestCore, CounterType001, TestSize.Level1)
{
    EXPECT_EQ(pattern_->GetCounterType(), COUNTER_DEFAULT_MODE);
    auto layoutProperty = pattern_->GetLayoutProperty<RichEditorLayoutProperty>();
    layoutProperty->UpdateSetCounter(1);
    EXPECT_EQ(pattern_->GetCounterType(), 1);
}

HWTEST_F(RichEditorCounterTestCore, CounterTypeNull001, TestSize.Level1)
{
    auto standalone = AceType::MakeRefPtr<RichEditorPattern>();
    EXPECT_EQ(standalone->GetCounterType(), COUNTER_DEFAULT_MODE);
    EXPECT_TRUE(standalone->GetShowHighlightBorder());
}

HWTEST_F(RichEditorCounterTestCore, ShowHighlightBorder001, TestSize.Level1)
{
    EXPECT_TRUE(pattern_->GetShowHighlightBorder());
    auto layoutProperty = pattern_->GetLayoutProperty<RichEditorLayoutProperty>();
    layoutProperty->UpdateShowHighlightBorder(false);
    EXPECT_FALSE(pattern_->GetShowHighlightBorder());
}

HWTEST_F(RichEditorCounterTestCore, CounterTextColor001, TestSize.Level1)
{
    EXPECT_FALSE(pattern_->HasCounterTextColor());
    EXPECT_EQ(pattern_->GetCounterTextColor(), Color::BLACK);
    auto layoutProperty = pattern_->GetLayoutProperty<RichEditorLayoutProperty>();
    layoutProperty->UpdateCounterTextColor(Color::BLUE);
    EXPECT_TRUE(pattern_->HasCounterTextColor());
    EXPECT_EQ(pattern_->GetCounterTextColor(), Color::BLUE);
}

HWTEST_F(RichEditorCounterTestCore, CounterOverflowColor001, TestSize.Level1)
{
    EXPECT_FALSE(pattern_->HasCounterTextOverflowColor());
    EXPECT_EQ(pattern_->GetCounterTextOverflowColor(), Color::RED);
    auto layoutProperty = pattern_->GetLayoutProperty<RichEditorLayoutProperty>();
    layoutProperty->UpdateCounterTextOverflowColor(Color::GREEN);
    EXPECT_TRUE(pattern_->HasCounterTextOverflowColor());
    EXPECT_EQ(pattern_->GetCounterTextOverflowColor(), Color::GREEN);
}

HWTEST_F(RichEditorCounterTestCore, FontScaleFromEnv001, TestSize.Level1)
{
    auto scale = pattern_->GetFontScaleFromEnv(richEditorNode_);
    EXPECT_FLOAT_EQ(scale, 1.0f);
}

HWTEST_F(RichEditorCounterTestCore, FontScaleFromEnvNull001, TestSize.Level1)
{
    auto standalone = AceType::MakeRefPtr<RichEditorPattern>();
    auto scale = standalone->GetFontScaleFromEnv(nullptr);
    EXPECT_FLOAT_EQ(scale, 1.0f);
}

HWTEST_F(RichEditorCounterTestCore, NonAutoLayoutDirection001, TestSize.Level1)
{
    EXPECT_EQ(pattern_->GetNonAutoLayoutDirection(), TextDirection::LTR);
}

HWTEST_F(RichEditorCounterTestCore, MarginProperty001, TestSize.Level1)
{
    EXPECT_FALSE(pattern_->GetMarginProperty().has_value());
    MarginProperty margin;
    margin.SetEdges(CalcLength(5.0_vp));
    pattern_->UpdateMargin(margin);
    EXPECT_TRUE(pattern_->GetMarginProperty().has_value());
}

HWTEST_F(RichEditorCounterTestCore, NeedRestoreMeasure001, TestSize.Level1)
{
    EXPECT_TRUE(pattern_->NeedRestoreMeasureConstraint());
}

HWTEST_F(RichEditorCounterTestCore, GetCounterDecorator001, TestSize.Level1)
{
    EXPECT_FALSE(pattern_->GetCounterDecorator());
}

HWTEST_F(RichEditorCounterTestCore, IsShowCounterEnabled001, TestSize.Level1)
{
    EXPECT_FALSE(pattern_->IsShowCounterEnabled());
}

HWTEST_F(RichEditorCounterTestCore, IsShowCounterEnabled002, TestSize.Level1)
{
    SetupCounterEnabled(pattern_);
    EXPECT_TRUE(pattern_->IsShowCounterEnabled());
}

HWTEST_F(RichEditorCounterTestCore, IsShowCounterEnabled003, TestSize.Level1)
{
    pattern_->isSpanStringMode_ = true;
    pattern_->maxLength_ = TEST_MAX_LENGTH;
    pattern_->styledString_ = AceType::MakeRefPtr<MutableSpanString>(u"hello");
    EXPECT_FALSE(pattern_->IsShowCounterEnabled());
}

HWTEST_F(RichEditorCounterTestCore, IsShowCounterEnabled004, TestSize.Level1)
{
    pattern_->isSpanStringMode_ = true;
    pattern_->styledString_ = AceType::MakeRefPtr<MutableSpanString>(u"hello");
    auto layoutProperty = pattern_->GetLayoutProperty<RichEditorLayoutProperty>();
    layoutProperty->UpdateShowCounter(true);
    EXPECT_FALSE(pattern_->IsShowCounterEnabled());
}

HWTEST_F(RichEditorCounterTestCore, IsShowCounterEnabled005, TestSize.Level1)
{
    pattern_->maxLength_ = TEST_MAX_LENGTH;
    pattern_->styledString_ = AceType::MakeRefPtr<MutableSpanString>(u"hello");
    auto layoutProperty = pattern_->GetLayoutProperty<RichEditorLayoutProperty>();
    layoutProperty->UpdateShowCounter(true);
    EXPECT_FALSE(pattern_->IsShowCounterEnabled());
}

HWTEST_F(RichEditorCounterTestCore, ProcessCounter001, TestSize.Level1)
{
    pattern_->showCountBorderStyle_ = true;
    pattern_->ProcessCounter();
    EXPECT_FALSE(pattern_->showCountBorderStyle_);
    EXPECT_FALSE(pattern_->GetCounterDecorator());
}

HWTEST_F(RichEditorCounterTestCore, ProcessCounter002, TestSize.Level1)
{
    SetupCounterEnabled(napiPattern_);
    napiPattern_->ProcessCounter();
    EXPECT_TRUE(napiPattern_->GetCounterDecorator());
}

HWTEST_F(RichEditorCounterTestCore, AddCounterNode001, TestSize.Level1)
{
    pattern_->AddCounterNode();
    EXPECT_TRUE(pattern_->GetCounterDecorator());
    pattern_->AddCounterNode();
    EXPECT_TRUE(pattern_->GetCounterDecorator());
}

HWTEST_F(RichEditorCounterTestCore, CleanCounterNode001, TestSize.Level1)
{
    SetupCounterEnabled(pattern_);
    pattern_->AddCounterNode();
    EXPECT_TRUE(pattern_->GetCounterDecorator());
    pattern_->CleanCounterNode();
    EXPECT_FALSE(pattern_->GetCounterDecorator());
}

HWTEST_F(RichEditorCounterTestCore, CleanCounterNodeNull001, TestSize.Level1)
{
    auto standalone = AceType::MakeRefPtr<RichEditorPattern>();
    standalone->CleanCounterNode();
    EXPECT_FALSE(standalone->GetCounterDecorator());
}

HWTEST_F(RichEditorCounterTestCore, UpdateShowCountBorderStyle001, TestSize.Level1)
{
    pattern_->showCountBorderStyle_ = false;
    pattern_->UpdateShowCountBorderStyle();
    EXPECT_FALSE(pattern_->showCountBorderStyle_);
}

HWTEST_F(RichEditorCounterTestCore, UpdateShowCountBorderStyle002, TestSize.Level1)
{
    pattern_->maxLength_ = 5;
    pattern_->showCountBorderStyle_ = true;
    pattern_->UpdateShowCountBorderStyle();
    EXPECT_FALSE(pattern_->showCountBorderStyle_);
}

HWTEST_F(RichEditorCounterTestCore, UpdateShowCountBorderStyle003, TestSize.Level1)
{
    pattern_->maxLength_ = 3;
    pattern_->InsertValue(u"hello");
    pattern_->UpdateShowCountBorderStyle();
    EXPECT_TRUE(pattern_->showCountBorderStyle_);
}

HWTEST_F(RichEditorCounterTestCore, HandleCountStyle001, TestSize.Level1)
{
    pattern_->showCountBorderStyle_ = true;
    pattern_->HandleCountStyle();
    EXPECT_TRUE(pattern_->showCountBorderStyle_);
}

HWTEST_F(RichEditorCounterTestCore, HandleCountStyle002, TestSize.Level1)
{
    SetupCounterEnabled(napiPattern_);
    auto layoutProperty = napiPattern_->GetLayoutProperty<RichEditorLayoutProperty>();
    layoutProperty->UpdateShowHighlightBorder(true);
    napiPattern_->showCountBorderStyle_ = false;
    napiPattern_->HandleCountStyle();
    EXPECT_FALSE(napiPattern_->showCountBorderStyle_);

    layoutProperty->UpdateShowHighlightBorder(false);
    napiPattern_->showCountBorderStyle_ = true;
    napiPattern_->HandleCountStyle();
    EXPECT_TRUE(napiPattern_->showCountBorderStyle_);
}

HWTEST_F(RichEditorCounterTestCore, HandleCountStyle003, TestSize.Level1)
{
    SetupCounterEnabled(napiPattern_);
    auto layoutProperty = napiPattern_->GetLayoutProperty<RichEditorLayoutProperty>();
    layoutProperty->UpdateSetCounter(1);
    layoutProperty->UpdateShowHighlightBorder(true);
    napiPattern_->showCountBorderStyle_ = true;
    napiPattern_->HandleCountStyle();
    EXPECT_TRUE(napiPattern_->showCountBorderStyle_);

    layoutProperty->UpdateSetCounter(COUNTER_ILLEGAL_VALUE);
    napiPattern_->showCountBorderStyle_ = true;
    napiPattern_->HandleCountStyle();
    EXPECT_TRUE(napiPattern_->showCountBorderStyle_);
}

HWTEST_F(RichEditorCounterTestCore, HandleCounterBorder001, TestSize.Level1)
{
    pattern_->showCountBorderStyle_ = true;
    pattern_->HandleCounterBorder();
    EXPECT_TRUE(pattern_->showCountBorderStyle_);
}

HWTEST_F(RichEditorCounterTestCore, HandleCounterBorder002, TestSize.Level1)
{
    SetupCounterEnabled(napiPattern_);
    napiPattern_->showCountBorderStyle_ = true;
    napiPattern_->HandleCounterBorder();
    EXPECT_TRUE(napiPattern_->showCountBorderStyle_);

    napiPattern_->showCountBorderStyle_ = false;
    napiPattern_->HandleCounterBorder();
    EXPECT_FALSE(napiPattern_->showCountBorderStyle_);
}

HWTEST_F(RichEditorCounterTestCore, ApplyInnerBorderColor001, TestSize.Level1)
{
    SetupCounterEnabled(napiPattern_);
    napiPattern_->ApplyInnerBorderColor();
    auto layoutProperty = napiPattern_->GetLayoutProperty<RichEditorLayoutProperty>();
    EXPECT_TRUE(layoutProperty->HasInnerBorderWidth());
}

HWTEST_F(RichEditorCounterTestCore, ApplyInnerBorderColor002, TestSize.Level1)
{
    SetupCounterEnabled(napiPattern_);
    auto layoutProperty = napiPattern_->GetLayoutProperty<RichEditorLayoutProperty>();
    BorderWidthProperty bw;
    bw.SetBorderWidth(Dimension(2.0_vp));
    layoutProperty->UpdateBorderWidthFlagByUser(bw);
    napiPattern_->ApplyInnerBorderColor();
    auto rc = napiPattern_->GetHost()->GetRenderContext();
    EXPECT_TRUE(rc->HasBorderColor());
}

HWTEST_F(RichEditorCounterTestCore, ApplyInnerBorderColor003, TestSize.Level1)
{
    SetupCounterEnabled(napiPattern_);
    auto layoutProperty = napiPattern_->GetLayoutProperty<RichEditorLayoutProperty>();
    layoutProperty->UpdateCounterTextOverflowColor(Color::GREEN);
    napiPattern_->ApplyInnerBorderColor();
    EXPECT_TRUE(layoutProperty->HasInnerBorderColor());
}

HWTEST_F(RichEditorCounterTestCore, SetThemeBorderAttr001, TestSize.Level1)
{
    napiPattern_->SetThemeBorderAttr();
    auto rc = napiPattern_->GetHost()->GetRenderContext();
    EXPECT_FALSE(rc->HasBorderColor());
}

HWTEST_F(RichEditorCounterTestCore, SetThemeBorderAttr002, TestSize.Level1)
{
    auto layoutProperty = napiPattern_->GetLayoutProperty<RichEditorLayoutProperty>();
    BorderColorProperty bc;
    bc.SetColor(Color::RED);
    layoutProperty->UpdateBorderColorFlagByUser(bc);
    BorderRadiusProperty br;
    br.SetRadius(Dimension(5.0_vp));
    layoutProperty->UpdateBorderRadiusFlagByUser(br);
    BorderWidthProperty bw;
    bw.SetBorderWidth(Dimension(2.0_vp));
    layoutProperty->UpdateBorderWidthFlagByUser(bw);
    napiPattern_->SetThemeBorderAttr();
    auto rc = napiPattern_->GetHost()->GetRenderContext();
    EXPECT_TRUE(rc->HasBorderColor());
}

HWTEST_F(RichEditorCounterTestCore, SetThemeBorderAttrNull001, TestSize.Level1)
{
    auto standalone = AceType::MakeRefPtr<RichEditorPattern>();
    standalone->SetThemeBorderAttr();
    EXPECT_FALSE(standalone->GetHost());
}

HWTEST_F(RichEditorCounterTestCore, HandleCounterWithLength001, TestSize.Level1)
{
    pattern_->HandleCounterWithLength(5, TEST_MAX_LENGTH);
    EXPECT_FALSE(pattern_->showCountBorderStyle_);
}

HWTEST_F(RichEditorCounterTestCore, HandleCounterWithLength002, TestSize.Level1)
{
    SetupCounterEnabled(napiPattern_);
    napiPattern_->HandleCounterWithLength(10, TEST_MAX_LENGTH);
    EXPECT_FALSE(napiPattern_->showCountBorderStyle_);

    napiPattern_->HandleCounterWithLength(2, TEST_MAX_LENGTH);
    EXPECT_FALSE(napiPattern_->showCountBorderStyle_);
}

HWTEST_F(RichEditorCounterTestCore, HandleCounterWithLength003, TestSize.Level1)
{
    SetupCounterEnabled(napiPattern_);
    auto focusHub = napiPattern_->GetFocusHub();
    focusHub->currentFocus_ = true;
    napiPattern_->HandleCounterWithLength(10, TEST_MAX_LENGTH);
    EXPECT_TRUE(napiPattern_->showCountBorderStyle_);
}

HWTEST_F(RichEditorCounterTestCore, CalcCounterAfterFilterInsert001, TestSize.Level1)
{
    SetupCounterEnabled(napiPattern_);
    auto focusHub = napiPattern_->GetFocusHub();
    focusHub->currentFocus_ = true;
    napiPattern_->CalcCounterAfterFilterInsertValue(5, 10, TEST_MAX_LENGTH);
    EXPECT_TRUE(napiPattern_->showCountBorderStyle_);
}

HWTEST_F(RichEditorCounterTestCore, CalcCounterAfterFilterInsert002, TestSize.Level1)
{
    SetupCounterEnabled(napiPattern_);
    napiPattern_->CalcCounterAfterFilterInsertValue(5, 2, TEST_MAX_LENGTH);
    EXPECT_FALSE(napiPattern_->showCountBorderStyle_);
}

HWTEST_F(RichEditorCounterTestCore, ProcBorderInBlurEvent001, TestSize.Level1)
{
    pattern_->showCountBorderStyle_ = true;
    pattern_->ProcBorderInBlurEvent();
    EXPECT_TRUE(pattern_->showCountBorderStyle_);
}

HWTEST_F(RichEditorCounterTestCore, ProcBorderInBlurEvent002, TestSize.Level1)
{
    SetupCounterEnabled(napiPattern_);
    napiPattern_->showCountBorderStyle_ = true;
    napiPattern_->ProcBorderInBlurEvent();
    EXPECT_FALSE(napiPattern_->showCountBorderStyle_);

    napiPattern_->showCountBorderStyle_ = false;
    napiPattern_->ProcBorderInBlurEvent();
    EXPECT_FALSE(napiPattern_->showCountBorderStyle_);
}

HWTEST_F(RichEditorCounterTestCore, HandleDeleteOnCounterScene001, TestSize.Level1)
{
    pattern_->HandleDeleteOnCounterScene();
    EXPECT_FALSE(pattern_->showCountBorderStyle_);
}

HWTEST_F(RichEditorCounterTestCore, HandleDeleteOnCounterScene002, TestSize.Level1)
{
    pattern_->maxLength_ = TEST_MAX_LENGTH;
    pattern_->showCountBorderStyle_ = true;
    pattern_->HandleDeleteOnCounterScene();
    EXPECT_FALSE(pattern_->showCountBorderStyle_);
}

HWTEST_F(RichEditorCounterTestCore, UpdateCounterContent001, TestSize.Level1)
{
    pattern_->UpdateCounterContent();
    EXPECT_FALSE(pattern_->GetCounterDecorator());
}

HWTEST_F(RichEditorCounterTestCore, UpdateCounterContent002, TestSize.Level1)
{
    SetupCounterEnabled(pattern_);
    pattern_->AddCounterNode();
    EXPECT_TRUE(pattern_->GetCounterDecorator());
    pattern_->UpdateCounterContent();
    EXPECT_TRUE(pattern_->GetCounterDecorator());
}

HWTEST_F(RichEditorCounterTestCore, UltralimitShake001, TestSize.Level1)
{
    pattern_->UltralimitShake();
    EXPECT_FALSE(pattern_->GetCounterDecorator());
}

HWTEST_F(RichEditorCounterTestCore, UltralimitShake002, TestSize.Level1)
{
    SetupCounterEnabled(pattern_);
    pattern_->AddCounterNode();
    EXPECT_TRUE(pattern_->GetCounterDecorator());
    pattern_->UltralimitShake();
}

HWTEST_F(RichEditorCounterTestCore, InitMargin001, TestSize.Level1)
{
    pattern_->InitMargin();
    auto layoutProperty = pattern_->GetLayoutProperty<RichEditorLayoutProperty>();
    EXPECT_FALSE(layoutProperty->HasMarginByUser());
}

HWTEST_F(RichEditorCounterTestCore, InitMargin002, TestSize.Level1)
{
    napiPattern_->InitMargin();
    auto layoutProperty = napiPattern_->GetLayoutProperty<RichEditorLayoutProperty>();
    EXPECT_TRUE(layoutProperty->HasMarginByUser());
}

HWTEST_F(RichEditorCounterTestCore, InitMargin003, TestSize.Level1)
{
    auto layoutProperty = napiPattern_->GetLayoutProperty<RichEditorLayoutProperty>();
    MarginProperty margin;
    margin.SetEdges(CalcLength(10.0_vp));
    layoutProperty->UpdateMarginByUser(margin);
    napiPattern_->InitMargin();
    EXPECT_TRUE(layoutProperty->HasMarginByUser());
}

HWTEST_F(RichEditorCounterTestCore, CounterNodeMeasure001, TestSize.Level1)
{
    auto algo = AceType::MakeRefPtr<RichEditorLayoutAlgorithm>(pattern_);
    float result = algo->CounterNodeMeasure(300.0f, nullptr);
    EXPECT_FLOAT_EQ(result, 0.0f);
}

HWTEST_F(RichEditorCounterTestCore, CounterNodeMeasure002, TestSize.Level1)
{
    SetupCounterEnabled(pattern_);
    pattern_->AddCounterNode();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        richEditorNode_, AceType::MakeRefPtr<GeometryNode>(),
        richEditorNode_->GetLayoutProperty());
    auto algo = AceType::MakeRefPtr<RichEditorLayoutAlgorithm>(pattern_);
    float result = algo->CounterNodeMeasure(300.0f, AceType::RawPtr(layoutWrapper));
    EXPECT_GE(result, 0.0f);
}

HWTEST_F(RichEditorCounterTestCore, CounterNodeMeasureNull001, TestSize.Level1)
{
    auto algo = AceType::MakeRefPtr<RichEditorLayoutAlgorithm>(pattern_);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        richEditorNode_, AceType::MakeRefPtr<GeometryNode>(),
        richEditorNode_->GetLayoutProperty());
    float result = algo->CounterNodeMeasure(300.0f, AceType::RawPtr(layoutWrapper));
    EXPECT_FLOAT_EQ(result, 0.0f);
}

HWTEST_F(RichEditorCounterTestCore, CounterLayout001, TestSize.Level1)
{
    auto algo = AceType::MakeRefPtr<RichEditorLayoutAlgorithm>(pattern_);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        richEditorNode_, AceType::MakeRefPtr<GeometryNode>(),
        richEditorNode_->GetLayoutProperty());
    algo->CounterLayout(AceType::RawPtr(layoutWrapper));
    EXPECT_NE(algo, nullptr);
}

HWTEST_F(RichEditorCounterTestCore, CreateNodePaintMethod001, TestSize.Level1)
{
    pattern_->CreateNodePaintMethod();
    EXPECT_FALSE(pattern_->foregroundModifier_);
}

HWTEST_F(RichEditorCounterTestCore, CreateNodePaintMethod002, TestSize.Level1)
{
    SetupCounterEnabled(pattern_);
    pattern_->CreateNodePaintMethod();
    EXPECT_TRUE(pattern_->foregroundModifier_);
    pattern_->CreateNodePaintMethod();
    EXPECT_TRUE(pattern_->foregroundModifier_);
}

HWTEST_F(RichEditorCounterTestCore, PaintMethodGetForeground001, TestSize.Level1)
{
    auto paintMethod = AceType::MakeRefPtr<RichEditorPaintMethod>(
        WeakPtr<Pattern>(), nullptr, 0.0f, nullptr, nullptr, nullptr);
    auto mod = paintMethod->GetForegroundModifier(nullptr);
    EXPECT_FALSE(mod);
}

HWTEST_F(RichEditorCounterTestCore, PaintMethodUpdateForeground001, TestSize.Level1)
{
    auto paintMethod = AceType::MakeRefPtr<RichEditorPaintMethod>(
        WeakPtr<Pattern>(), nullptr, 0.0f, nullptr, nullptr, nullptr);
    paintMethod->UpdateForegroundModifier(nullptr);
    EXPECT_NE(paintMethod, nullptr);

    auto fgMod = AceType::MakeRefPtr<RichEditorForegroundModifier>(WeakPtr<Pattern>());
    auto paintMethod2 = AceType::MakeRefPtr<RichEditorPaintMethod>(
        WeakPtr<Pattern>(), nullptr, 0.0f, nullptr, nullptr, fgMod);
    paintMethod2->UpdateForegroundModifier(nullptr);
    EXPECT_NE(paintMethod2, nullptr);
}

HWTEST_F(RichEditorCounterTestCore, PaintMethodUpdateForeground002, TestSize.Level1)
{
    auto fgMod = AceType::MakeRefPtr<RichEditorForegroundModifier>(
        AceType::WeakClaim(AceType::RawPtr(pattern_)));
    auto paintMethod = AceType::MakeRefPtr<RichEditorPaintMethod>(
        AceType::WeakClaim(AceType::RawPtr(pattern_)), nullptr, 0.0f, nullptr, nullptr, fgMod);
    pattern_->UpdateInnerBorderWidth(2.0f);
    pattern_->UpdateInnerBorderColor(Color::RED);
    paintMethod->UpdateForegroundModifier(nullptr);
    EXPECT_NE(paintMethod, nullptr);
}

HWTEST_F(RichEditorCounterTestCore, ForegroundModifierOnDraw001, TestSize.Level1)
{
    auto fgMod = AceType::MakeRefPtr<RichEditorForegroundModifier>(WeakPtr<Pattern>());
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawRoundRect(_)).WillRepeatedly(Return());
    DrawingContext context { canvas, CONTEXT_WIDTH, CONTEXT_HEIGHT };
    fgMod->onDraw(context);
    EXPECT_NE(fgMod, nullptr);
}

HWTEST_F(RichEditorCounterTestCore, ForegroundModifierOnDraw002, TestSize.Level1)
{
    auto fgMod = AceType::MakeRefPtr<RichEditorForegroundModifier>(
        AceType::WeakClaim(AceType::RawPtr(pattern_)));
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, CONTEXT_WIDTH, CONTEXT_HEIGHT };
    fgMod->onDraw(context);
    EXPECT_NE(fgMod, nullptr);
}

HWTEST_F(RichEditorCounterTestCore, ForegroundModifierOnDraw003, TestSize.Level1)
{
    SetupCounterEnabled(pattern_);
    pattern_->UpdateInnerBorderWidth(2.0f);
    pattern_->UpdateInnerBorderColor(Color::RED);
    auto fgMod = AceType::MakeRefPtr<RichEditorForegroundModifier>(
        AceType::WeakClaim(AceType::RawPtr(pattern_)));
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawRoundRect(_)).WillRepeatedly(Return());
    DrawingContext context { canvas, CONTEXT_WIDTH, CONTEXT_HEIGHT };
    fgMod->onDraw(context);
    EXPECT_NE(fgMod, nullptr);
}

HWTEST_F(RichEditorCounterTestCore, ForegroundModifierOnDraw004, TestSize.Level1)
{
    auto fgMod = AceType::MakeRefPtr<RichEditorForegroundModifier>(
        AceType::WeakClaim(AceType::RawPtr(pattern_)));
    pattern_->UpdateInnerBorderWidth(2.0f);
    pattern_->UpdateInnerBorderColor(Color::RED);
    fgMod->innerBorderWidth_.Reset();
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, CONTEXT_WIDTH, CONTEXT_HEIGHT };
    fgMod->onDraw(context);
    EXPECT_NE(fgMod, nullptr);
}

HWTEST_F(RichEditorCounterTestCore, IsShowCount001, TestSize.Level1)
{
    auto accessibility = richEditorNode_->GetAccessibilityProperty<RichEditorAccessibilityProperty>();
    ASSERT_NE(accessibility, nullptr);
    EXPECT_FALSE(accessibility->IsShowCount());
}

HWTEST_F(RichEditorCounterTestCore, IsShowCount002, TestSize.Level1)
{
    SetupCounterEnabled(pattern_);
    pattern_->AddCounterNode();
    auto accessibility = richEditorNode_->GetAccessibilityProperty<RichEditorAccessibilityProperty>();
    ASSERT_NE(accessibility, nullptr);
    accessibility->IsShowCount();
}

HWTEST_F(RichEditorCounterTestCore, IsShowCountNull001, TestSize.Level1)
{
    SetupCounterEnabled(pattern_);
    auto accessibility = richEditorNode_->GetAccessibilityProperty<RichEditorAccessibilityProperty>();
    ASSERT_NE(accessibility, nullptr);
    EXPECT_FALSE(accessibility->IsShowCount());
}

HWTEST_F(RichEditorCounterTestCore, NapiPattern001, TestSize.Level1)
{
    EXPECT_FALSE(pattern_->IsNapiRichEditorPattern());
    EXPECT_TRUE(napiPattern_->IsNapiRichEditorPattern());
}

HWTEST_F(RichEditorCounterTestCore, SetMaxLength001, TestSize.Level1)
{
    pattern_->maxLength_ = TEST_MAX_LENGTH;
    pattern_->SetMaxLength(INT_MAX);
    EXPECT_EQ(pattern_->maxLength_.value_or(0), INT_MAX);
}

HWTEST_F(RichEditorCounterTestCore, SetMaxLength002, TestSize.Level1)
{
    SetupCounterEnabled(pattern_);
    pattern_->SetMaxLength(20);
    EXPECT_EQ(pattern_->maxLength_.value_or(0), 20);

    pattern_->SetMaxLength(5);
    EXPECT_EQ(pattern_->maxLength_.value_or(0), 5);
}

HWTEST_F(RichEditorCounterTestCore, SetMaxLength003, TestSize.Level1)
{
    pattern_->maxLength_ = TEST_MAX_LENGTH;
    pattern_->SetMaxLength(TEST_MAX_LENGTH);
    EXPECT_EQ(pattern_->maxLength_.value_or(0), TEST_MAX_LENGTH);
}

HWTEST_F(RichEditorCounterTestCore, SetMaxLength004, TestSize.Level1)
{
    pattern_->InsertValue(u"hello world!");
    pattern_->SetMaxLength(5);
    EXPECT_EQ(pattern_->maxLength_.value_or(0), 5);
}

HWTEST_F(RichEditorCounterTestCore, HandleBlurBorder001, TestSize.Level1)
{
    SetupCounterEnabled(pattern_);
    pattern_->showCountBorderStyle_ = true;
    auto focusHub = pattern_->GetFocusHub();
    focusHub->currentFocus_ = true;
    pattern_->HandleBlurEvent();
    EXPECT_FALSE(pattern_->HasFocus());
}

HWTEST_F(RichEditorCounterTestCore, HandleBlurBorder002, TestSize.Level1)
{
    SetupCounterEnabled(pattern_);
    pattern_->showCountBorderStyle_ = true;
    auto layoutProperty = pattern_->GetLayoutProperty<RichEditorLayoutProperty>();
    layoutProperty->UpdateCounterTextOverflowColor(Color::GREEN);
    auto focusHub = pattern_->GetFocusHub();
    focusHub->currentFocus_ = true;
    pattern_->HandleBlurEvent();
    EXPECT_FALSE(pattern_->HasFocus());
}

} // namespace OHOS::Ace::NG