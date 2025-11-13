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

#include "gtest/gtest.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "text_base.h"
#include "ui/base/geometry/dimension.h"

#include "core/components/common/layout/constants.h"
#include "core/components/text_overlay/text_overlay_theme.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/text/span_model_ng.h"
#include "core/components_ng/pattern/text/text_model_ng.h"
#include "core/components_ng/pattern/text/paragraph_util.h"
#include "core/components_v2/inspector/inspector_constants.h"


namespace OHOS::Ace::NG {

namespace {
constexpr uint32_t DEFAULT_NODE_ID = 0;
} // namespace

class TextTestNgTwo : public TextBases {
public:
};

/**
 * @tc.name: DidExceedMaxLines001
 * @tc.desc: Test TextLayoutAlgorithm DidExceedMaxLines.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgTwo, DidExceedMaxLines001, TestSize.Level1)
{
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, Layout);
    EXPECT_CALL(*paragraph, DidExceedMaxLinesInner).WillOnce(Return(true));
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
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. set textLayoutProperty.
     * baselineOffset: 20_px
     */

    textLayoutProperty->UpdateContent(CREATE_VALUE_W);
    textLayoutProperty->UpdateBaselineOffset(BASELINE_OFFSET_VALUE);
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;

    /**
     * @tc.steps: step3. create textLayoutAlgorithm.
     */

    auto textLayoutAlgorithm = AceType::MakeRefPtr<TextLayoutAlgorithm>();
    TextStyle textStyle;
    LayoutConstraintF contentConstraint;
    auto ret = textLayoutAlgorithm->CreateParagraphAndLayout(textStyle, u"", contentConstraint,
        AceType::RawPtr(textFrameNode));
    EXPECT_TRUE(ret);
    SizeF maxSize;
    ret = textLayoutAlgorithm->DidExceedMaxLines(maxSize);

    /**
     * @tc.steps: step4. check the size.
     */

    EXPECT_TRUE(ret);
}

/**
 * @tc.name: DidExceedMaxLines002
 * @tc.desc: Test TextLayoutAlgorithm DidExceedMaxLines.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgTwo, DidExceedMaxLines002, TestSize.Level1)
{
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, DidExceedMaxLinesInner).WillOnce(Return(true));
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
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. set textLayoutProperty.
     * baselineOffset: 20_px
     */

    textLayoutProperty->UpdateContent(CREATE_VALUE_W);
    textLayoutProperty->UpdateBaselineOffset(BASELINE_OFFSET_VALUE);
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;

    /**
     * @tc.steps: step3. create textLayoutAlgorithm.
     */

    auto textLayoutAlgorithm = AceType::MakeRefPtr<TextLayoutAlgorithm>();
    TextStyle textStyle;
    textStyle.SetMaxLines(MAX_LINES);
    LayoutConstraintF contentConstraint;
    auto ret = textLayoutAlgorithm->CreateParagraphAndLayout(textStyle, u"", contentConstraint,
        AceType::RawPtr(textFrameNode));
    EXPECT_TRUE(ret);
    SizeF maxSize;
    ret = textLayoutAlgorithm->DidExceedMaxLines(maxSize);

    /**
     * @tc.steps: step4. check the size.
     */

    EXPECT_TRUE(ret);
}

/**
 * @tc.name: TextLayoutAlgorithmTest001
 * @tc.desc: test text_layout_algorithm.cpp:Set textHeightAdaptivePolicy to MIN_FONT_SIZE_FIRST
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgTwo, TextLayoutAlgorithmTest001, TestSize.Level1)
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

    /**
     * @tc.steps: step2. set textLayoutProperty.
     */
    textLayoutProperty->UpdateContent(CREATE_VALUE_W);
    textLayoutProperty->UpdateHeightAdaptivePolicy(TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST);
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.selfIdealSize.SetSize(TEXT_SIZE);
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;

    /**
     * @tc.steps: step3. create textLayoutAlgorithm and call MeasureContent function.
     * @tc.expected: The width of the return value of MeasureContent is equal to maxWidth of paragraph_
     */
    auto textLayoutAlgorithm = AceType::MakeRefPtr<TextLayoutAlgorithm>();
    // set TextHeightAdaptivePolicy MAX_LINES_FIRST
    textLayoutProperty->UpdateHeightAdaptivePolicy(TextHeightAdaptivePolicy::MAX_LINES_FIRST);
    // MockTxtParagraph::SetCanConstruct(false);
    textLayoutAlgorithm->MeasureContent(parentLayoutConstraint, AccessibilityManager::RawPtr(layoutWrapper));
    // set SetCanConstruct true
    // MockTxtParagraph::SetCanConstruct(true);
    auto contentSize =
        textLayoutAlgorithm->MeasureContent(parentLayoutConstraint, AccessibilityManager::RawPtr(layoutWrapper));
    textLayoutAlgorithm->baselineOffset_ = BASE_LINE_OFFSET;
    textLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    textLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(contentSize.value().Width(), textLayoutAlgorithm->paragraphManager_->GetMaxWidth());
}

/**
 * @tc.name: TextLayoutAlgorithmTest002
 * @tc.desc: test text_layout_algorithm.cpp:Set textHeightAdaptivePolicy to LAYOUT_CONSTRAINT_FIRST and set lineHeight
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgTwo, TextLayoutAlgorithmTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto textLayoutProperty = textFrameNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textFrameNode, geometryNode, textLayoutProperty);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. set textLayoutProperty.
     */
    textLayoutProperty->UpdateContent(CREATE_VALUE_W);
    textLayoutProperty->UpdateHeightAdaptivePolicy(TextHeightAdaptivePolicy::LAYOUT_CONSTRAINT_FIRST);
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.selfIdealSize.SetSize(TEXT_SIZE);
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    textLayoutProperty->UpdateAdaptMinFontSize(ADAPT_MIN_FONT_SIZE_VALUE);
    textLayoutProperty->UpdateLineHeight(ADAPT_LINE_HEIGHT_VALUE);
    textLayoutProperty->UpdateFontSize(ADAPT_FONT_SIZE_VALUE);
    textLayoutProperty->UpdateFontWeight(Ace::FontWeight::W200);
    textLayoutProperty->UpdateTextColor(TEXT_COLOR_VALUE);
    Shadow textShadow;
    textLayoutProperty->UpdateTextShadow({ textShadow });
    textLayoutProperty->UpdateTextDecorationColor(TEXT_COLOR_VALUE);
    textLayoutProperty->UpdateTextDecoration({TextDecoration::OVERLINE});
    textLayoutProperty->UpdateBaselineOffset(BASELINE_OFFSET_VALUE);

    /**
     * @tc.steps: step3. create textLayoutAlgorithm and call MeasureContent/SetPropertyToModifier function.
     * @tc.expected: The width of the return value of MeasureContent is equal to maxWidth of paragraph_
     */
    auto textLayoutAlgorithm = AceType::MakeRefPtr<TextLayoutAlgorithm>();
    auto contentSize =
        textLayoutAlgorithm->MeasureContent(parentLayoutConstraint, AccessibilityManager::RawPtr(layoutWrapper));
    textLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    textLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    auto frameNode = layoutWrapper->GetHostNode();
    auto pipeline = frameNode->GetContextRefPtr();
    TextStyle textStyle = CreateTextStyleUsingTheme(
        textLayoutProperty->GetFontStyle(), textLayoutProperty->GetTextLineStyle(), pipeline->GetTheme<TextTheme>());
    textPattern->contentMod_ = AceType::MakeRefPtr<TextContentModifier>(std::optional<TextStyle>(std::move(textStyle)));
    auto contentModifier = textPattern->GetContentModifier();
    textLayoutAlgorithm->SetPropertyToModifier(
        textLayoutProperty, contentModifier, textStyle, textFrameNode, Color::BLACK);
    EXPECT_EQ(contentSize.value().Width(), textLayoutAlgorithm->paragraphManager_->GetMaxWidth());
}

/**
 * @tc.name: TextLayoutAlgorithmTest003
 * @tc.desc: test text_layout_algorithm.cpp:Set textHeightAdaptivePolicy to MIN_FONT_SIZE_FIRST, minFontSize and
 *           fontSize are equal
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgTwo, TextLayoutAlgorithmTest003, TestSize.Level1)
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
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. set textLayoutProperty.
     */
    textLayoutProperty->UpdateContent(CREATE_VALUE_W);
    textLayoutProperty->UpdateHeightAdaptivePolicy(TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST);
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.selfIdealSize.SetSize(TEXT_SIZE);
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    textLayoutProperty->UpdateAdaptMinFontSize(ADAPT_MIN_FONT_SIZE_VALUE);
    textLayoutProperty->UpdateFontSize(ADAPT_MIN_FONT_SIZE_VALUE);
    textLayoutProperty->UpdateLineHeight(ADAPT_LINE_HEIGHT_VALUE);

    /**
     * @tc.steps: step3. create textLayoutAlgorithm and call MeasureContent function.
     * @tc.expected: The width of the return value of MeasureContent is equal to maxWidth of paragraph_
     */
    auto textLayoutAlgorithm = AceType::MakeRefPtr<TextLayoutAlgorithm>();
    auto contentSize =
        textLayoutAlgorithm->MeasureContent(parentLayoutConstraint, AccessibilityManager::RawPtr(layoutWrapper));
    textLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    textLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(contentSize.value().Width(), textLayoutAlgorithm->paragraphManager_->GetMaxWidth());
}

/**
 * @tc.name: TextLayoutAlgorithmTest004
 * @tc.desc: test text_layout_algorithm.cpp:Set textHeightAdaptivePolicy to LAYOUT_CONSTRAINT_FIRST and set lineHeight,
 *     the height of text is bigger than the height of container
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgTwo, TextLayoutAlgorithmTest004, TestSize.Level1)
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
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. set textLayoutProperty.
     */
    textLayoutProperty->UpdateContent(CREATE_VALUE_W);
    textLayoutProperty->UpdateHeightAdaptivePolicy(TextHeightAdaptivePolicy::LAYOUT_CONSTRAINT_FIRST);
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.selfIdealSize.SetSize(TEXT_SIZE);
    parentLayoutConstraint.maxSize = CONTAINER_LOW_SIZE;
    textLayoutProperty->UpdateAdaptMinFontSize(ADAPT_OVER_MIN_FONT_SIZE_VALUE);
    textLayoutProperty->UpdateLineHeight(ADAPT_LINE_HEIGHT_VALUE);

    /**
     * @tc.steps: step3. create textLayoutAlgorithm and call MeasureContent function.
     * @tc.expected: The width of the return value of MeasureContent is equal to maxWidth of paragraph_
     */
    auto textLayoutAlgorithm = AceType::MakeRefPtr<TextLayoutAlgorithm>();
    auto contentSize =
        textLayoutAlgorithm->MeasureContent(parentLayoutConstraint, AccessibilityManager::RawPtr(layoutWrapper));
    textLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    textLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(contentSize.value().Width(), textLayoutAlgorithm->paragraphManager_->GetMaxWidth());
}

/**
 * @tc.name: TextLayoutAlgorithmTest005
 * @tc.desc: test text_layout_algorithm.cpp:Set textHeightAdaptivePolicy to LAYOUT_CONSTRAINT_FIRST and set lineHeight,
 *     the height of text is bigger than the height of container,set maxlines.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgTwo, TextLayoutAlgorithmTest005, TestSize.Level1)
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
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. set textLayoutProperty.
     */
    textLayoutProperty->UpdateContent(CREATE_VALUE_W);
    textLayoutProperty->UpdateHeightAdaptivePolicy(TextHeightAdaptivePolicy::LAYOUT_CONSTRAINT_FIRST);
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.selfIdealSize.SetSize(TEXT_SIZE);
    parentLayoutConstraint.maxSize = CONTAINER_LOW_SIZE;
    textLayoutProperty->UpdateAdaptMinFontSize(ADAPT_OVER_MIN_FONT_SIZE_VALUE);
    textLayoutProperty->UpdateLineHeight(ADAPT_LINE_HEIGHT_VALUE);
    textLayoutProperty->UpdateMaxLines(MAX_LINES);

    /**
     * @tc.steps: step3. create textLayoutAlgorithm and call MeasureContent function.
     * @tc.expected: The width of the return value of MeasureContent is equal to maxWidth of paragraph_
     */
    auto textLayoutAlgorithm = AceType::MakeRefPtr<TextLayoutAlgorithm>();
    auto contentSize =
        textLayoutAlgorithm->MeasureContent(parentLayoutConstraint, AccessibilityManager::RawPtr(layoutWrapper));
    textLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    textLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(contentSize.value().Width(), textLayoutAlgorithm->paragraphManager_->GetMaxWidth());
}

/**
 * @tc.name: TextPaintMethodTest001
 * @tc.desc: test text_paint_method.cpp :set textOverflow to MARQUEE
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgTwo, TextPaintMethodTest001, TestSize.Level1)
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
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. set theme.
     */
    auto pipeline = PipelineContext::GetCurrentContext();
    auto theme = AceType::MakeRefPtr<MockThemeManager>();
    pipeline->SetThemeManager(theme);
    EXPECT_CALL(*theme, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextTheme>()));

    /**
     * @tc.steps: step3. create textPaintMethod and call UpdateContentModifier function.
     * @tc.expected: The return value of GetOverlayModifier is not null.
     */
    auto pattern = textFrameNode->GetPattern<Pattern>();
    AceType::DynamicCast<TextPattern>(pattern)->textSelector_.Update(0, -1);
    ParagraphStyle paragraphStyle;
    RefPtr<Paragraph> paragraph = Paragraph::Create(paragraphStyle, FontCollection::Current());
    RefPtr<TextContentModifier> textContentModifier =
        AceType::MakeRefPtr<TextContentModifier>(std::optional<TextStyle>(TextStyle()));
    RefPtr<TextOverlayModifier> textOverlayModifier = AceType::MakeRefPtr<TextOverlayModifier>();
    TextPaintMethod textPaintMethod(pattern, BASE_LINE_OFFSET_VALUE, textContentModifier, textOverlayModifier);
    UpdateTextLayoutProperty(textLayoutProperty);
    RefPtr<RenderContext> renderContext = RenderContext::Create();
    auto paintProperty = textPattern->CreatePaintProperty();
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, paintProperty);
    textPaintMethod.UpdateContentModifier(AceType::RawPtr(paintWrapper));
    SetPaintMethodModifier(textPaintMethod);
    textPaintMethod.UpdateContentModifier(AceType::RawPtr(paintWrapper));
    textPaintMethod.textContentModifier_->textDecoration_ = TextDecoration::UNDERLINE;
    textPaintMethod.UpdateContentModifier(AceType::RawPtr(paintWrapper));
    ASSERT_NE(textPaintMethod.GetOverlayModifier(AceType::RawPtr(paintWrapper)), nullptr);
}

/**
 * @tc.name: TextContentModifier001
 * @tc.desc: test text_content_modifier.cpp onDraw function.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgTwo, TextContentModifier001, TestSize.Level1)
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
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. call onDraw function.
     * @tc.expected: The member variable value of textContentModifier is the value set above
     */
    auto frameNode = layoutWrapper->GetHostNode();
    auto pipeline = frameNode->GetContextRefPtr();
    TextStyle textStyle = CreateTextStyleUsingTheme(
        textLayoutProperty->GetFontStyle(), textLayoutProperty->GetTextLineStyle(), pipeline->GetTheme<TextTheme>());
    TextContentModifier textContentModifier(std::optional<TextStyle>(std::move(textStyle)), textPattern);
    textStyle.SetTextDecorationColor(TEXT_COLOR_VALUE);
    SetContentModifier(textContentModifier);
    auto pattern = textFrameNode->GetPattern<Pattern>();
    ParagraphStyle paragraphStyle;
    RefPtr<Paragraph> paragraph = Paragraph::Create(paragraphStyle, FontCollection::Current());
    RefPtr<TextContentModifier> contentModifier =
        AceType::MakeRefPtr<TextContentModifier>(std::optional<TextStyle>(TextStyle()));
    RefPtr<TextOverlayModifier> textOverlayModifier = AceType::MakeRefPtr<TextOverlayModifier>();
    TextPaintMethod textPaintMethod(pattern, BASE_LINE_OFFSET_VALUE, contentModifier, textOverlayModifier);
    // set pipelineContext nullptr
    MockPipelineContext::TearDown();
    textContentModifier.SetFontSize(ADAPT_FONT_SIZE_VALUE, textStyle);
    textContentModifier.SetBaselineOffset(BASELINE_OFFSET_VALUE, textStyle);
    MockPipelineContext::SetUp();
    MockPipelineContext::GetCurrent()->onShow_ = true;
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, ClipRect(_, _, _)).WillRepeatedly(Return());
    DrawingContext context { canvas, CONTEXT_WIDTH_VALUE, CONTEXT_HEIGHT_VALUE };
    textPattern->pManager_->AddParagraph({ .paragraph = paragraph });
    // call onDraw function(MarqueeState::RUNNING == marqueeState_)
    MarqueeOption option;
    textPattern->GetHost()->onMainTree_ = true;
    auto mockRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    mockRenderContext->SetPaintRectWithTransform(RectF(0, 0, 100, 100));
    textPattern->GetHost()->renderContext_ = mockRenderContext;
    auto mockParent = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 1, AceType::MakeRefPtr<TextPattern>());
    mockParent->isActive_ = true;
    textPattern->GetHost()->isActive_ = true;
    textPattern->GetHost()->parent_ = mockParent;
    textPattern->GetHost()->isCalculateInnerVisibleRectClip_ = false;
    auto mockParentRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    mockParentRenderContext->SetPaintRectWithTransform(RectF(0, 0, 100, 100));
    mockParent->renderContext_ = mockParentRenderContext;
    textContentModifier.StartTextRace(option);
    EXPECT_EQ(textContentModifier.marqueeState_, MarqueeState::RUNNING);
    context.width = CONTEXT_LARGE_WIDTH_VALUE;
    textContentModifier.onDraw(context);
    // call onDraw function(MarqueeState::STOPPED == marqueeState_)
    textContentModifier.StopTextRace();
    EXPECT_EQ(textContentModifier.marqueeState_, MarqueeState::STOPPED);
    textContentModifier.onDraw(context);
    EXPECT_EQ(textContentModifier.fontSizeFloat_->Get(), ADAPT_FONT_SIZE_VALUE.Value());
    EXPECT_EQ(textContentModifier.baselineOffsetFloat_->Get(), BASELINE_OFFSET_VALUE.Value());
    textPattern->pManager_->Reset();
}

/**
 * @tc.name: TextContentModifier002
 * @tc.desc: test text_content_modifier.cpp ModifyTextStyle function.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgTwo, TextContentModifier002, TestSize.Level1)
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
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. call ModifyTextStyle function.
     * @tc.expected: The member variable value of textContentModifier is the value set above
     */
    auto frameNode = layoutWrapper->GetHostNode();
    auto pipeline = frameNode->GetContextRefPtr();
    TextStyle textStyle = CreateTextStyleUsingTheme(
        textLayoutProperty->GetFontStyle(), textLayoutProperty->GetTextLineStyle(), pipeline->GetTheme<TextTheme>());
    TextContentModifier textContentModifier(std::optional<TextStyle>(std::move(textStyle)), textPattern);
    textStyle.SetTextDecorationColor(TEXT_COLOR_VALUE);
    SetContentModifier(textContentModifier);
    auto pattern = textFrameNode->GetPattern<Pattern>();
    ParagraphStyle paragraphStyle;
    RefPtr<Paragraph> paragraph = Paragraph::Create(paragraphStyle, FontCollection::Current());
    RefPtr<TextContentModifier> contentModifier =
        AceType::MakeRefPtr<TextContentModifier>(std::optional<TextStyle>(TextStyle()));
    RefPtr<TextOverlayModifier> textOverlayModifier = AceType::MakeRefPtr<TextOverlayModifier>();
    TextPaintMethod textPaintMethod(pattern, BASE_LINE_OFFSET_VALUE, contentModifier, textOverlayModifier);
    // set pipelineContext nullptr
    MockPipelineContext::TearDown();
    textContentModifier.SetFontSize(ADAPT_FONT_SIZE_VALUE, textStyle);
    PropertyChangeFlag flag = 0;
    textContentModifier.UpdateFontSizeMeasureFlag(flag);
    EXPECT_EQ(flag & PROPERTY_UPDATE_MEASURE, PROPERTY_UPDATE_MEASURE);
    textContentModifier.SetBaselineOffset(BASELINE_OFFSET_VALUE, textStyle);
    MockPipelineContext::SetUp();
    // set textDecorationAnimatable_ true
    textContentModifier.textDecorationAnimatable_ = true;
    textContentModifier.textDecoration_ = TextDecoration::UNDERLINE;
    textContentModifier.SetTextDecoration(TextDecoration::NONE);
    Color textColor;
    textContentModifier.ModifyTextStyle(textStyle, textColor);
    // set textDecorationColorAlpha_ value
    textContentModifier.textDecorationColorAlpha_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(1000.0f);
    textContentModifier.ModifyTextStyle(textStyle, textColor);
    // set textDecorationAnimatable_ false
    textContentModifier.SetTextDecoration(TextDecoration::LINE_THROUGH);
    textContentModifier.ModifyTextStyle(textStyle, textColor);
    EXPECT_EQ(textContentModifier.fontSizeFloat_->Get(), ADAPT_FONT_SIZE_VALUE.Value());
    EXPECT_EQ(textContentModifier.baselineOffsetFloat_->Get(), BASELINE_OFFSET_VALUE.Value());
    EXPECT_EQ(textStyle.GetFontSize().Value(), textContentModifier.fontSizeFloat_->Get());

    textContentModifier.SetTextDecorationColor(Color::ColorFromString("#55FFFFFF"), false);
    textContentModifier.textDecoration_ = TextDecoration::LINE_THROUGH;
    textContentModifier.SetTextDecoration(TextDecoration::LINE_THROUGH);
    EXPECT_EQ(textContentModifier.textDecorationColorAlpha_->Get(), 85.0f);
}

/**
 * @tc.name: TextContentModifier003
 * @tc.desc: test text_content_modifier.cpp .
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgTwo, TextContentModifier003, TestSize.Level1)
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
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    auto frameNode = layoutWrapper->GetHostNode();
    auto pipeline = frameNode->GetContextRefPtr();
    TextStyle textStyle = CreateTextStyleUsingTheme(
        textLayoutProperty->GetFontStyle(), textLayoutProperty->GetTextLineStyle(), pipeline->GetTheme<TextTheme>());
    TextContentModifier textContentModifier(std::optional<TextStyle>(std::move(textStyle)));
    textStyle.SetTextDecorationColor(TEXT_COLOR_VALUE);
    SetContentModifier(textContentModifier);
    auto pattern = textFrameNode->GetPattern<Pattern>();

    textStyle.SetAllowScale(true);
    Dimension fontSize;
    fontSize.SetUnit(DimensionUnit::FP);
    textStyle.SetFontSize(fontSize);
    textContentModifier.SetDefaultFontSize(textStyle);

    Dimension adaptMinFontSize;
    adaptMinFontSize.SetUnit(DimensionUnit::FP);
    textStyle.SetAdaptMinFontSize(adaptMinFontSize);
    textContentModifier.SetDefaultAdaptMinFontSize(textStyle);

    Dimension adaptMaxFontSize;
    adaptMaxFontSize.SetUnit(DimensionUnit::FP);
    textStyle.SetAdaptMaxFontSize(adaptMaxFontSize);
    textContentModifier.SetDefaultAdaptMaxFontSize(textStyle);
}

/**
 * @tc.name: TextContentModifier004
 * @tc.desc: test text_content_modifier.cpp .
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgTwo, TextContentModifier004, TestSize.Level1)
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
    ASSERT_NE(textFrameNode->geometryNode_, nullptr);
    textFrameNode->geometryNode_->SetContentOffset(OffsetF(TEXT_CONTENT_OFFSET, TEXT_CONTENT_OFFSET));
    textFrameNode->geometryNode_->SetContentSize(SizeF(TEXT_CONTENT_SIZE, TEXT_CONTENT_SIZE));
    ASSERT_NE(textPattern, nullptr);
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    auto frameNode = layoutWrapper->GetHostNode();
    auto pipeline = frameNode->GetContextRefPtr();
    TextStyle textStyle;
    textStyle.SetFontSize(Dimension(DIMENSION, DimensionUnit::FP));
    textStyle.SetTextColor(Color::RED);
    textStyle.SetAdaptMaxFontSize(Dimension(DIMENSION, DimensionUnit::FP));
    textStyle.SetAdaptMinFontSize(Dimension(DIMENSION, DimensionUnit::FP));
    textStyle.SetFontWeight(FontWeight::BOLD);
    Shadow textShadow;
    textShadow.SetBlurRadius(0.0);
    textShadow.SetColor(Color::BLUE);
    textShadow.SetOffsetX(DIMENSION);
    textShadow.SetOffsetY(DIMENSION);
    vector<Shadow> textShadows { textShadow };
    textStyle.SetTextShadows(textShadows);
    textStyle.SetTextDecorationStyle(TextDecorationStyle::DOTTED);
    textStyle.SetTextDecoration(TextDecoration::UNDERLINE);
    textStyle.SetTextDecorationColor(Color::BLUE);
    textStyle.SetBaselineOffset(Dimension(DIMENSION, DimensionUnit::FP));
    textStyle.SetLineHeight(Dimension(DIMENSION, DimensionUnit::FP));

    TextContentModifier textContentModifier(std::optional<TextStyle>(std::move(textStyle)), textPattern);

    EXPECT_EQ(textContentModifier.fontSizeFloat_->Get(), DIMENSION);
    EXPECT_EQ(Color(textContentModifier.animatableTextColor_->Get().GetValue()), Color::RED);
    EXPECT_EQ(textContentModifier.adaptMaxFontSizeFloat_->Get(), DIMENSION);
    EXPECT_EQ(textContentModifier.fontWeightFloat_->Get(), TEXT_FONT_WEIGHT);

    EXPECT_EQ(textContentModifier.contentOffset_->Get().GetX(), TEXT_CONTENT_OFFSET);
    EXPECT_EQ(textContentModifier.contentOffset_->Get().GetY(), TEXT_CONTENT_OFFSET);
    EXPECT_EQ(textContentModifier.contentSize_->Get().Height(), TEXT_CONTENT_SIZE);
    EXPECT_EQ(textContentModifier.contentSize_->Get().Width(), TEXT_CONTENT_SIZE);
}

/**
 * @tc.name: TextContentModifier005
 * @tc.desc: test text_content_modifier.cpp .
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgTwo, TextContentModifier005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    textFrameNode->geometryNode_ = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(textFrameNode->geometryNode_, nullptr);
    textFrameNode->geometryNode_->SetContentOffset(OffsetF(TEXT_CONTENT_OFFSET, TEXT_CONTENT_OFFSET));
    textFrameNode->geometryNode_->SetContentSize(SizeF(TEXT_CONTENT_SIZE, TEXT_CONTENT_SIZE));
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textFrameNode, geometryNode, textFrameNode->GetLayoutProperty());
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    auto frameNode = layoutWrapper->GetHostNode();
    auto pipeline = frameNode->GetContextRefPtr();
    TextStyle textStyle = CreateTextStyleUsingTheme(
        textLayoutProperty->GetFontStyle(), textLayoutProperty->GetTextLineStyle(), pipeline->GetTheme<TextTheme>());
    TextContentModifier textContentModifier(std::optional<TextStyle>(std::move(textStyle)));
    textStyle.SetTextDecorationColor(TEXT_COLOR_VALUE);
    SetContentModifier(textContentModifier);
    auto pattern = textFrameNode->GetPattern<Pattern>();

    textContentModifier.clip_ = nullptr;
    textContentModifier.SetClip(true);
    textContentModifier.fontReady_ = nullptr;
    textContentModifier.SetFontReady(true);
}

/**
 * @tc.name: TextContentModifier006
 * @tc.desc: test text_content_modifier.cpp .
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgTwo, TextContentModifier006, TestSize.Level1)
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
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    auto frameNode = layoutWrapper->GetHostNode();
    auto pipeline = frameNode->GetContextRefPtr();
    TextStyle textStyle = CreateTextStyleUsingTheme(
        textLayoutProperty->GetFontStyle(), textLayoutProperty->GetTextLineStyle(), pipeline->GetTheme<TextTheme>());
    TextContentModifier textContentModifier(std::optional<TextStyle>(std::move(textStyle)));
    textStyle.SetTextDecorationColor(TEXT_COLOR_VALUE);
    SetContentModifier(textContentModifier);
    auto pattern = textFrameNode->GetPattern<Pattern>();

    RSCanvas canvas;
    float x = 0.0;
    float y = 0.0;
    textContentModifier.PaintImage(canvas, x, y);
}

/**
 * @tc.name: TextContentModifier007
 * @tc.desc: test text_content_modifier.cpp .
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgTwo, TextContentModifier007, TestSize.Level1)
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
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    auto frameNode = layoutWrapper->GetHostNode();
    auto pipeline = frameNode->GetContextRefPtr();
    TextStyle textStyle = CreateTextStyleUsingTheme(
        textLayoutProperty->GetFontStyle(), textLayoutProperty->GetTextLineStyle(), pipeline->GetTheme<TextTheme>());
    TextContentModifier textContentModifier(std::optional<TextStyle>(std::move(textStyle)));
    textStyle.SetTextDecorationColor(TEXT_COLOR_VALUE);
    SetContentModifier(textContentModifier);

    RSCanvas canvas;
    float x = 0.0;
    float y = 0.0;
    RectF rect;
    textContentModifier.DrawImage(textFrameNode, canvas, x, y, rect);
}

/**
 * @tc.name: TextContentModifier008
 * @tc.desc: test text_content_modifier.cpp .
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgTwo, TextContentModifier008, TestSize.Level1)
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
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    auto frameNode = layoutWrapper->GetHostNode();
    auto pipeline = frameNode->GetContextRefPtr();
    TextStyle textStyle = CreateTextStyleUsingTheme(
        textLayoutProperty->GetFontStyle(), textLayoutProperty->GetTextLineStyle(), pipeline->GetTheme<TextTheme>());
    TextContentModifier textContentModifier(std::optional<TextStyle>(std::move(textStyle)));
    textStyle.SetTextDecorationColor(TEXT_COLOR_VALUE);
    SetContentModifier(textContentModifier);

    textContentModifier.ResumeAnimation();
    textContentModifier.ResumeAnimation();
    textContentModifier.PauseAnimation();
    textContentModifier.PauseAnimation();
    textContentModifier.racePercentFloat_ = nullptr;
    textContentModifier.GetTextRacePercent();
}

/**
 * @tc.name: TextContentAlign001
 * @tc.desc: test text_content_modifier.cpp .
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgTwo, TextContentAlign001, TestSize.Level1)
{
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, GetMaxWidth).WillRepeatedly(Return(100.0f));
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
    textPattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 100 });
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. set textLayoutProperty.
     */
    textLayoutProperty->UpdateContent(CREATE_VALUE_W);
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.selfIdealSize.SetSize(TEXT_SIZE);
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;

    /**
     * @tc.steps: step3. create textLayoutAlgorithm and call MeasureContent function.
     * @tc.expected: The width of the return value of MeasureContent is equal to 100.0f
     */
    auto textLayoutAlgorithm = AceType::MakeRefPtr<TextLayoutAlgorithm>();
    auto contentSize =
        textLayoutAlgorithm->MeasureContent(parentLayoutConstraint, AccessibilityManager::RawPtr(layoutWrapper));
    textLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    textLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(contentSize.value().Width(), 100.0f);
    textLayoutProperty->UpdateTextContentAlign(TextContentAlign::TOP);
    auto contentOffset = textLayoutAlgorithm->GetContentOffset(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(contentOffset.GetY(), 0.0f);
    textPattern->pManager_->Reset();
}

/**
 * @tc.name: TextContentAlign002
 * @tc.desc: test text_content_modifier.cpp .
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgTwo, TextContentAlign002, TestSize.Level1)
{
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, GetMaxWidth).WillRepeatedly(Return(100.0f));
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
    textPattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 100 });
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. set textLayoutProperty.
     */
    textLayoutProperty->UpdateContent(CREATE_VALUE_W);
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.selfIdealSize.SetSize(TEXT_SIZE);
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;

    /**
     * @tc.steps: step3. create textLayoutAlgorithm and call MeasureContent function.
     * @tc.expected: The width of the return value of MeasureContent is equal to 100.0f
     */
    auto textLayoutAlgorithm = AceType::MakeRefPtr<TextLayoutAlgorithm>();
    auto contentSize =
        textLayoutAlgorithm->MeasureContent(parentLayoutConstraint, AccessibilityManager::RawPtr(layoutWrapper));
    textLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    textLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(contentSize.value().Width(), 100.0f);
    textLayoutProperty->UpdateTextContentAlign(TextContentAlign::TOP);
    auto contentOffset = textLayoutAlgorithm->GetContentOffset(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(contentOffset.GetY(), 0.0f);
    textLayoutProperty->ResetTextContentAlign();
    contentOffset = textLayoutAlgorithm->GetContentOffset(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(contentOffset.GetY(), 0.0f);
    textPattern->pManager_->Reset();
}

/**
 * @tc.name: TextLayoutAlgorithmTest006
 * @tc.desc: text_layout_algorithm.cpp:Set TextOverflow to MARQUEE
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgTwo, TextLayoutAlgorithmTest006, TestSize.Level1)
{
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, GetMaxWidth).WillRepeatedly(Return(100.0f));
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
    textPattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 100 });
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. set textLayoutProperty.
     */
    textLayoutProperty->UpdateContent(CREATE_VALUE_W);
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.selfIdealSize.SetSize(TEXT_SIZE);
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    textLayoutProperty->UpdateTextOverflow(TextOverflow::MARQUEE);

    /**
     * @tc.steps: step3. create textLayoutAlgorithm and call MeasureContent function.
     * @tc.expected: The width of the return value of MeasureContent is equal to 100.0f
     */
    auto textLayoutAlgorithm = textPattern->CreateLayoutAlgorithm();
    auto contentSize =
        textLayoutAlgorithm->MeasureContent(parentLayoutConstraint, AccessibilityManager::RawPtr(layoutWrapper));
    textLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    textLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(contentSize.value().Width(), 100.0f);
    textPattern->pManager_->Reset();
}

/**
 * @tc.name: TextLayoutAlgorithmTest007
 * @tc.desc: text_layout_algorithm.cpp:set TextHeightAdaptivePolicy to LAYOUT_CONSTRAINT_FIRST and set minFontSize to
 *           zero. ADAPT_ZERO_FONT_SIZE_VALUE
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgTwo, TextLayoutAlgorithmTest007, TestSize.Level1)
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
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. set textLayoutProperty.
     */
    textLayoutProperty->UpdateContent(CREATE_VALUE_W);
    textLayoutProperty->UpdateHeightAdaptivePolicy(TextHeightAdaptivePolicy::LAYOUT_CONSTRAINT_FIRST);
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.selfIdealSize.SetSize(TEXT_SIZE);
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    textLayoutProperty->UpdateAdaptMinFontSize(ADAPT_ZERO_FONT_SIZE_VALUE);
    textLayoutProperty->UpdateLineHeight(ADAPT_LINE_HEIGHT_VALUE);
    textLayoutProperty->UpdateMaxLines(MAX_LINES);

    /**
     * @tc.steps: step3. create textLayoutAlgorithm.
     * @tc.expected: The width of the return value of MeasureContent is equal to maxWidth of paragraph_
     */
    auto textLayoutAlgorithm = AceType::MakeRefPtr<TextLayoutAlgorithm>();
    auto contentSize =
        textLayoutAlgorithm->MeasureContent(parentLayoutConstraint, AccessibilityManager::RawPtr(layoutWrapper));
    textLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    textLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(contentSize.value().Width(), textLayoutAlgorithm->paragraphManager_->GetMaxWidth());
}

/**
 * @tc.name: TextLayoutAlgorithmTest008
 * @tc.desc: text_layout_algorithm.cpp:call AdaptMaxTextSize
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgTwo, TextLayoutAlgorithmTest008, TestSize.Level1)
{
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, PushStyle).Times(1);
    EXPECT_CALL(*paragraph, AddText).Times(1);
    EXPECT_CALL(*paragraph, Build).Times(1);
    EXPECT_CALL(*paragraph, GetLineCount).WillRepeatedly(Return(2));
    EXPECT_CALL(*paragraph, GetLongestLine).WillRepeatedly(Return(100));

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
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    auto frameNode = layoutWrapper->GetHostNode();
    auto pipeline = frameNode->GetContextRefPtr();
    TextStyle textStyle = CreateTextStyleUsingTheme(
        textLayoutProperty->GetFontStyle(), textLayoutProperty->GetTextLineStyle(), pipeline->GetTheme<TextTheme>());
    textStyle.SetAdaptFontSizeStep(ADAPT_FONT_SIZE_STEP_VALUE);

    /**
     * @tc.steps: step2. create textLayoutAlgorithm and call AdaptMaxTextSize.
     * @tc.expected: when maxFontSize < minFontSize,The return value of AdaptMaxTextSize is false.
     *               when create paragraph failed,The return value of AdaptMaxTextSize is false.
     *               when increase font size,The return value of AdaptMaxTextSize is true.
     *               when set NormalizeToPx false,The return value of AdaptMaxTextSize is false.
     */
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.selfIdealSize.SetSize(TEXT_SIZE);
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    auto textLayoutAlgorithm = AceType::MakeRefPtr<TextLayoutAlgorithm>();

    // maxFontSize < minFontSize
    textStyle.SetAdaptMaxFontSize(ADAPT_MIN_FONT_SIZE_VALUE);
    textStyle.SetAdaptMinFontSize(ADAPT_MAX_FONT_SIZE_VALUE);
    EXPECT_EQ(textLayoutAlgorithm->AdaptMaxTextSize(textStyle, u"abc", parentLayoutConstraint,
        AceType::RawPtr(textFrameNode)), true);

    // create paragraph failed
    MockParagraph::enabled_ = false;
    textStyle.SetAdaptMaxFontSize(ADAPT_MAX_FONT_SIZE_VALUE);
    textStyle.SetAdaptMinFontSize(ADAPT_MIN_FONT_SIZE_VALUE);
    EXPECT_EQ(
        textLayoutAlgorithm->AdaptMaxTextSize(textStyle, u"abc", parentLayoutConstraint,
        AceType::RawPtr(textFrameNode)),
        true);
    MockParagraph::enabled_ = true;

    // increase font size
    EXPECT_EQ(
        textLayoutAlgorithm->AdaptMaxTextSize(textStyle, u"abc", parentLayoutConstraint,
        AceType::RawPtr(textFrameNode)),
        true);
}

/**
 * @tc.name: CreateTextStyleUsingTheme001
 * @tc.desc: test CreateTextStyleUsingTheme().
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgTwo, CreateTextStyleUsingTheme001, TestSize.Level1)
{
    auto textFrameNode = FrameNode::CreateFrameNode(V2::SYMBOL_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    textLayoutProperty->UpdateTextAlign(TextAlign::CENTER);
    auto pipeline = textFrameNode->GetContextRefPtr();
    TextStyle textStyle = CreateTextStyleUsingTheme(
        textLayoutProperty->GetFontStyle(), textLayoutProperty->GetTextLineStyle(), pipeline->GetTheme<TextTheme>(), true);
    EXPECT_EQ(textStyle.GetTextAlign(), TextAlign::CENTER);
}

/**
 * @tc.name: TextSelectOverlayTestGetFirstHandleInfo001
 * @tc.desc: Verify GetFirstHandleInfo
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgTwo, TextSelectOverlayTestGetFirstHandleInfo001, TestSize.Level1)
{
    WeakPtr<TextBase> textBase = nullptr;
    TextSelectOverlay textSelectOverlay(textBase);

    ASSERT_EQ(textSelectOverlay.GetFirstHandleInfo(), std::nullopt);
}

/**
 * @tc.name: TextSelectOverlayTestGetSecondHandleInfo001
 * @tc.desc: Verify GetSecondHandleInfo
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgTwo, TextSelectOverlayTestGetSecondHandleInfo001, TestSize.Level1)
{
    WeakPtr<TextBase> textBase = nullptr;
    TextSelectOverlay textSelectOverlay(textBase);

    ASSERT_EQ(textSelectOverlay.GetSecondHandleInfo(), std::nullopt);
}

/**
 * @tc.name: TextSelectOverlayTestCheckAndAdjustHandle001
 * @tc.desc: Verify CheckAndAdjustHandle
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgTwo, TextSelectOverlayTestCheckAndAdjustHandle001, TestSize.Level1)
{
    /**
     * @tc.steps: set theme, used in CheckAndAdjustHandle.
     */
    auto pipeline = PipelineContext::GetCurrentContext();
    auto theme = AceType::MakeRefPtr<MockThemeManager>();
    pipeline->SetThemeManager(theme);
    EXPECT_CALL(*theme, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
 
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto textSelectOverlay = pattern->selectOverlay_;
    ASSERT_NE(textSelectOverlay, nullptr);

    RectF paintRect(RECT_X_VALUE, RECT_Y_VALUE, RECT_WIDTH_VALUE, RECT_HEIGHT_VALUE);

    textSelectOverlay->hostTextBase_ = nullptr;
    ASSERT_EQ(textSelectOverlay->CheckAndAdjustHandle(paintRect), false);
    textSelectOverlay->hostTextBase_ = pattern;

    ASSERT_EQ(textSelectOverlay->CheckAndAdjustHandle(paintRect), false);

    auto frameNode = FrameNode::CreateFrameNode("Test", DEFAULT_NODE_ID, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);

    auto renderContext = frameNode->renderContext_;
    frameNode->renderContext_ = nullptr;
    ASSERT_EQ(textSelectOverlay->CheckAndAdjustHandle(paintRect), false);
    frameNode->renderContext_ = renderContext;
}

/**
 * @tc.name: TextSelectOverlayTestCheckAndAdjustHandle002
 * @tc.desc: Verify CheckAndAdjustHandle
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgTwo, TextSelectOverlayTestCheckAndAdjustHandle002, TestSize.Level1)
{
    /**
     * @tc.steps: set theme, used in CheckAndAdjustHandle.
     */
    auto pipeline = PipelineContext::GetCurrentContext();
    auto theme = AceType::MakeRefPtr<MockThemeManager>();
    pipeline->SetThemeManager(theme);
    EXPECT_CALL(*theme, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
 
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", DEFAULT_NODE_ID, pattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->geometryNode_ = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(frameNode->geometryNode_, nullptr);
    pattern->AttachToFrameNode(frameNode);
    auto textSelectOverlay = pattern->selectOverlay_;
    ASSERT_NE(textSelectOverlay, nullptr);

    RectF paintRect;
    pattern->contentRect_.SetRect(RECT_X_VALUE, RECT_Y_VALUE, RECT_WIDTH_VALUE, RECT_HEIGHT_VALUE);

    paintRect.SetRect(RECT_X_VALUE, RECT_Y_VALUE - RECT_Y_VALUE, RECT_WIDTH_VALUE, RECT_HEIGHT_VALUE + RECT_Y_VALUE);
    ASSERT_EQ(textSelectOverlay->CheckAndAdjustHandle(paintRect), true);

    paintRect.SetRect(RECT_X_VALUE, RECT_Y_VALUE + RECT_Y_VALUE, RECT_WIDTH_VALUE, RECT_HEIGHT_VALUE - RECT_Y_VALUE);
    ASSERT_EQ(textSelectOverlay->CheckAndAdjustHandle(paintRect), true);
}

/**
 * @tc.name: TextSelectOverlayTestCheckHandleVisible001
 * @tc.desc: Verify CheckHandleVisible
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgTwo, TextSelectOverlayTestCheckHandleVisible001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", DEFAULT_NODE_ID, pattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->geometryNode_ = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(frameNode->geometryNode_, nullptr);
    pattern->AttachToFrameNode(frameNode);
    auto textSelectOverlay = pattern->selectOverlay_;
    ASSERT_NE(textSelectOverlay, nullptr);

    RectF paintRect(RECT_X_VALUE, RECT_Y_VALUE, RECT_WIDTH_VALUE, RECT_HEIGHT_VALUE);
    ASSERT_EQ(textSelectOverlay->CheckHandleVisible(paintRect), false);
}

/**
 * @tc.name: TextSelectOverlayTestCheckHandleVisible002
 * @tc.desc: Verify CheckHandleVisible
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgTwo, TextSelectOverlayTestCheckHandleVisible002, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto textSelectOverlay = pattern->selectOverlay_;
    ASSERT_NE(textSelectOverlay, nullptr);

    RectF paintRect(RECT_X_VALUE, RECT_Y_VALUE, RECT_WIDTH_VALUE, RECT_HEIGHT_VALUE);

    textSelectOverlay->hostTextBase_ = nullptr;
    ASSERT_EQ(textSelectOverlay->CheckHandleVisible(paintRect), false);
    textSelectOverlay->hostTextBase_ = pattern;

    ASSERT_EQ(textSelectOverlay->CheckHandleVisible(paintRect), false);

    auto frameNode = FrameNode::CreateFrameNode("Test", DEFAULT_NODE_ID, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);

    auto renderContext = frameNode->renderContext_;
    frameNode->renderContext_ = nullptr;
    ASSERT_EQ(textSelectOverlay->CheckHandleVisible(paintRect), false);
    frameNode->renderContext_ = renderContext;
}

/**
 * @tc.name: TextSelectOverlayTestOnResetTextSelection001
 * @tc.desc: Verify OnResetTextSelection
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgTwo, TextSelectOverlayTestOnResetTextSelection001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", DEFAULT_NODE_ID, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto textSelectOverlay = pattern->selectOverlay_;
    ASSERT_NE(textSelectOverlay, nullptr);
    auto textPattern = textSelectOverlay->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    OffsetF firstOffset(ADAPT_OFFSETY_VALUE, ADAPT_OFFSETX_VALUE);
    OffsetF secondOffset(ADAPT_OFFSETY_VALUE + ADAPT_OFFSETY_VALUE, ADAPT_OFFSETX_VALUE + ADAPT_OFFSETX_VALUE);

    textSelectOverlay->UpdateSelectorOnHandleMove(firstOffset, true);
    textSelectOverlay->UpdateSelectorOnHandleMove(secondOffset, false);
    ASSERT_NE(textPattern->textSelector_.GetStart(), TEXT_ERROR);
    textSelectOverlay->OnResetTextSelection();
    ASSERT_EQ(textPattern->textSelector_.GetStart(), TEXT_ERROR);
}

/**
 * @tc.name: TextSelectOverlayTestOnHandleMove001
 * @tc.desc: Verify OnHandleMove
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgTwo, TextSelectOverlayTestOnHandleMove001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", DEFAULT_NODE_ID, pattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->geometryNode_ = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(frameNode->geometryNode_, nullptr);
    pattern->AttachToFrameNode(frameNode);
    auto textSelectOverlay = pattern->selectOverlay_;
    ASSERT_NE(textSelectOverlay, nullptr);

    RectF handleRect(RECT_X_VALUE, RECT_Y_VALUE, RECT_WIDTH_VALUE, RECT_HEIGHT_VALUE);

    SelectOverlayInfo overlayInfo;
    auto shareOverlayInfo = std::make_shared<SelectOverlayInfo>(overlayInfo);
    auto overlayNode = SelectOverlayNode::CreateSelectOverlayNode(shareOverlayInfo);
    ASSERT_NE(overlayNode, nullptr);
    overlayNode->MountToParent(frameNode);
    auto manager = SelectContentOverlayManager::GetOverlayManager();
    ASSERT_NE(manager, nullptr);
    manager->selectOverlayNode_ = overlayNode;
    pattern->selectOverlay_->OnBind(manager);

    ASSERT_EQ(pattern->textSelector_.GetStart(), TEXT_ERROR);
    ASSERT_EQ(pattern->textSelector_.GetEnd(), TEXT_ERROR);
    textSelectOverlay->OnHandleMove(handleRect, true);
    ASSERT_EQ(pattern->textSelector_.GetStart(), 0);
    ASSERT_EQ(pattern->textSelector_.GetEnd(), TEXT_ERROR);
    textSelectOverlay->OnHandleMove(handleRect, false);
    ASSERT_EQ(pattern->textSelector_.GetStart(), 0);
    ASSERT_EQ(pattern->textSelector_.GetEnd(), 0);

    manager->selectOverlayNode_ = nullptr;
}

/**
 * @tc.name: TextSelectOverlayTestUpdateSelectorOnHandleMove001
 * @tc.desc: Verify UpdateSelectorOnHandleMove
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgTwo, TextSelectOverlayTestUpdateSelectorOnHandleMove001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", DEFAULT_NODE_ID, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto textSelectOverlay = pattern->selectOverlay_;
    ASSERT_NE(textSelectOverlay, nullptr);

    OffsetF handleOffset(ADAPT_OFFSETY_VALUE, ADAPT_OFFSETX_VALUE);

    ASSERT_EQ(pattern->textSelector_.GetStart(), TEXT_ERROR);
    ASSERT_EQ(pattern->textSelector_.GetEnd(), TEXT_ERROR);
    textSelectOverlay->UpdateSelectorOnHandleMove(handleOffset, true);
    textSelectOverlay->UpdateSelectorOnHandleMove(handleOffset, false);
    ASSERT_EQ(pattern->textSelector_.GetStart(), 0);
    ASSERT_EQ(pattern->textSelector_.GetEnd(), 0);
}

/**
 * @tc.name: TextSelectOverlayTestGetSelectedText001
 * @tc.desc: Verify GetSelectedText
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgTwo, TextSelectOverlayTestGetSelectedText001, TestSize.Level1)
{
    WeakPtr<TextBase> textBase = nullptr;
    TextSelectOverlay textSelectOverlay(textBase);

    ASSERT_EQ(textSelectOverlay.GetSelectedText(), "");
}

/**
 * @tc.name: TextSelectOverlayTestGetSelectArea001
 * @tc.desc: Verify GetSelectArea
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgTwo, TextSelectOverlayTestGetSelectArea001, TestSize.Level1)
{
    /**
     * @tc.steps: set theme, used in CheckAndAdjustHandle.
     */
    auto pipeline = PipelineContext::GetCurrentContext();
    auto theme = AceType::MakeRefPtr<MockThemeManager>();
    pipeline->SetThemeManager(theme);
    EXPECT_CALL(*theme, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));

    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", DEFAULT_NODE_ID, pattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->geometryNode_ = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(frameNode->geometryNode_, nullptr);
    pattern->AttachToFrameNode(frameNode);
    auto textSelectOverlay = pattern->selectOverlay_;
    ASSERT_NE(textSelectOverlay, nullptr);

    bool hasTransform = textSelectOverlay->hasTransform_;
    textSelectOverlay->hasTransform_ = true;
    ASSERT_EQ(textSelectOverlay->GetSelectArea(), RectF());
    textSelectOverlay->hasTransform_ = hasTransform;
}
} // namespace OHOS::Ace::NG