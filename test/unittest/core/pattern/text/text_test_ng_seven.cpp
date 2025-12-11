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

#include "test/mock/core/common/mock_font_manager.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pattern/mock_nestable_scroll_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_canvas_image.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "text_base.h"

#include "core/components/common/properties/text_style_parser.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/text/paragraph_util.h"
#include "core/components_ng/pattern/text/span_model_ng.h"
#include "core/components_ng/pattern/text/typed_text.h"
#include "core/components_ng/render/adapter/pixelmap_image.h"


namespace OHOS::Ace::NG {

namespace {
const std::list<std::pair<std::string, int32_t>> FONT_FEATURE_VALUE_0 = ParseFontFeatureSettings("\"ss01\" 0");
} // namespace

class TextTestNgSeven : public TextBases {
public:
};

/**
 * @tc.name: PaintCustomSpan001
 * @tc.desc: test text_content_modifier.cpp PaintCustomSpan function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgSeven, PaintCustomSpan001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->CreateModifier();
    auto textContentModifier = pattern->contentMod_;
    ASSERT_NE(textContentModifier, nullptr);

    ParagraphStyle paragraphStyle;
    auto paragraph = Paragraph::Create(paragraphStyle, FontCollection::Current());
    ASSERT_NE(paragraph, nullptr);
    pattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 1 });

    int32_t callOnDrawCount = 0;
    std::vector<CustomSpanPlaceholderInfo> customSpanPlaceholder;
    CustomSpanPlaceholderInfo customSpanPlaceholderInfo0;
    CustomSpanPlaceholderInfo customSpanPlaceholderInfo1 {
        .customSpanIndex = 0,
        .onDraw = [&callOnDrawCount](NG::DrawingContext&, CustomSpanOptions) {
            callOnDrawCount++;
        }
    };
    CustomSpanPlaceholderInfo customSpanPlaceholderInfo2 {
        .customSpanIndex = 1,
        .onDraw = [&callOnDrawCount](NG::DrawingContext&, CustomSpanOptions) {
            callOnDrawCount++;
        }
    };
    customSpanPlaceholder.emplace_back(customSpanPlaceholderInfo0);
    customSpanPlaceholder.emplace_back(customSpanPlaceholderInfo1);
    customSpanPlaceholder.emplace_back(customSpanPlaceholderInfo2);
    pattern->InitCustomSpanPlaceholderInfo(customSpanPlaceholder);
    std::vector<int32_t> placeholderIndex = { 0 };
    std::vector<RectF> rectsForPlaceholders = { RectF(0, 0, 10, 10) };
    OffsetF contentOffset(0, 0);
    pattern->InitSpanImageLayout(placeholderIndex, rectsForPlaceholders, contentOffset);

    RSCanvas canvas;
    DrawingContext drawingContext = { canvas, 10, 10 };

    textContentModifier->PaintCustomSpan(drawingContext);
    EXPECT_EQ(callOnDrawCount, 1);
}

/**
 * @tc.name: PaintLeadingMarginSpan001
 * @tc.desc: test text_content_modifier.cpp PaintLeadingMarginSpan function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgSeven, PaintLeadingMarginSpan001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->CreateModifier();
    auto textContentModifier = pattern->contentMod_;
    ASSERT_NE(textContentModifier, nullptr);

    /**
     * @tc.steps: step1. add paragraph
     */
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    EXPECT_CALL(*paragraph, GetLineCount()).WillRepeatedly(Return(2));
    TextLineMetrics textLineMetrics;
    EXPECT_CALL(*paragraph, GetLineMetrics(_)).WillRepeatedly(Return(textLineMetrics));
    pattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 1 });

    /**
     * @tc.steps: step2. test PaintLeadingMarginSpan without drawableLeadingMargin
     */
    auto pManager = pattern->GetParagraphManager();
    ASSERT_NE(pManager, nullptr);
    RSCanvas canvas;
    DrawingContext drawingContext = { canvas, 10, 10 };
    textContentModifier->PaintLeadingMarginSpan(pattern, drawingContext, pManager);

    /**
     * @tc.steps: step3. test PaintLeadingMarginSpan
     */
    ParagraphStyle paraStyle;
    DrawableLeadingMargin leadingMargin;
    leadingMargin.onDraw_ = [](NG::DrawingContext& context, NG::LeadingMarginSpanOptions options) {};
    paraStyle.drawableLeadingMargin = std::make_optional<NG::DrawableLeadingMargin>(leadingMargin);
    pattern->pManager_->AddParagraph({ .paragraph = paragraph, .paragraphStyle = paraStyle, .start = 0, .end = 1 });
    textContentModifier->PaintLeadingMarginSpan(pattern, drawingContext, pManager);

    EXPECT_CALL(*paragraph, empty()).WillRepeatedly(Return(true));
    textContentModifier->PaintLeadingMarginSpan(pattern, drawingContext, pManager);
}

/**
 * @tc.name: onDraw001
 * @tc.desc: test text_content_modifier.cpp onDraw function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgSeven, onDraw001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->CreateModifier();
    auto textContentModifier = pattern->contentMod_;
    ASSERT_NE(textContentModifier, nullptr);

    ParagraphStyle paragraphStyle;
    auto paragraph = Paragraph::Create(paragraphStyle, FontCollection::Global());
    ASSERT_NE(paragraph, nullptr);
    pattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 1 });

    bool calledClipRect = false;
    bool calledAttachBrush = false;
    Testing::TestingCanvas retCanvas;
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, ClipRect(_, _, _)).WillRepeatedly([&calledClipRect]() { calledClipRect = true; });
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(
        [&calledAttachBrush, &retCanvas](const Testing::TestingBrush& brush)->Testing::TestingCanvas& {
            calledAttachBrush = true;
            return retCanvas;
            }
        );
    DrawingContext drawingContext = { canvas, 10, 10 };

    textContentModifier->onDraw(drawingContext);
    EXPECT_EQ(calledClipRect, true);

    textContentModifier->animatableTextColor_ =
        AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(Color::TRANSPARENT));
    textContentModifier->ifPaintObscuration_ = true;
    textContentModifier->drawObscuredRects_.emplace_back(RectF(0, 0, 10, 10));

    textContentModifier->onDraw(drawingContext);
    EXPECT_EQ(calledAttachBrush, true);
}

/**
 * @tc.name: ModifyAdaptMinFontSizeInTextStyle001
 * @tc.desc: test text_content_modifier.cpp ModifyAdaptMinFontSizeInTextStyle function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgSeven, ModifyAdaptMinFontSizeInTextStyle001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->CreateModifier();
    auto textContentModifier = pattern->contentMod_;
    ASSERT_NE(textContentModifier, nullptr);

    TextStyle textStyle;

    textContentModifier->adaptMinFontSize_ = Dimension(10);
    textContentModifier->ModifyAdaptMinFontSizeInTextStyle(textStyle);
    EXPECT_EQ(textStyle.GetAdaptMinFontSize().Value(), 0);

    textContentModifier->adaptMinFontSizeFloat_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(10);
    textContentModifier->ModifyAdaptMinFontSizeInTextStyle(textStyle);
    EXPECT_EQ(textStyle.GetAdaptMinFontSize().Value(), 10);
}

/**
 * @tc.name: ModifyAdaptMaxFontSizeInTextStyle001
 * @tc.desc: test text_content_modifier.cpp ModifyAdaptMaxFontSizeInTextStyle function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgSeven, ModifyAdaptMaxFontSizeInTextStyle001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->CreateModifier();
    auto textContentModifier = pattern->contentMod_;
    ASSERT_NE(textContentModifier, nullptr);

    TextStyle textStyle;

    textContentModifier->adaptMaxFontSize_ = Dimension(10);
    textContentModifier->ModifyAdaptMaxFontSizeInTextStyle(textStyle);
    EXPECT_EQ(textStyle.GetAdaptMaxFontSize().Value(), 0);

    textContentModifier->adaptMaxFontSizeFloat_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(10);
    textContentModifier->ModifyAdaptMaxFontSizeInTextStyle(textStyle);
    EXPECT_EQ(textStyle.GetAdaptMaxFontSize().Value(), 10);
}

/**
 * @tc.name: UpdateAdaptMinFontSizeMeasureFlag001
 * @tc.desc: test text_content_modifier.cpp UpdateAdaptMinFontSizeMeasureFlag function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgSeven, UpdateAdaptMinFontSizeMeasureFlag001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->CreateModifier();
    auto textContentModifier = pattern->contentMod_;
    ASSERT_NE(textContentModifier, nullptr);

    PropertyChangeFlag flag = PROPERTY_UPDATE_NORMAL;

    textContentModifier->adaptMinFontSize_ = Dimension(10);
    textContentModifier->UpdateAdaptMinFontSizeMeasureFlag(flag);
    EXPECT_EQ(flag, PROPERTY_UPDATE_NORMAL);

    textContentModifier->adaptMinFontSizeFloat_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(20);
    textContentModifier->UpdateAdaptMinFontSizeMeasureFlag(flag);
    EXPECT_EQ(flag, PROPERTY_UPDATE_MEASURE);
}

/**
 * @tc.name: UpdateAdaptMaxFontSizeMeasureFlag001
 * @tc.desc: test text_content_modifier.cpp UpdateAdaptMaxFontSizeMeasureFlag function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgSeven, UpdateAdaptMaxFontSizeMeasureFlag001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->CreateModifier();
    auto textContentModifier = pattern->contentMod_;
    ASSERT_NE(textContentModifier, nullptr);

    PropertyChangeFlag flag = PROPERTY_UPDATE_NORMAL;

    textContentModifier->adaptMaxFontSize_ = Dimension(10);
    textContentModifier->UpdateAdaptMaxFontSizeMeasureFlag(flag);
    EXPECT_EQ(flag, PROPERTY_UPDATE_NORMAL);

    textContentModifier->adaptMaxFontSizeFloat_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(20);
    textContentModifier->UpdateAdaptMaxFontSizeMeasureFlag(flag);
    EXPECT_EQ(flag, PROPERTY_UPDATE_MEASURE);
}

/**
 * @tc.name: ResumeAnimation001
 * @tc.desc: test text_content_modifier.cpp ResumeAnimation function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgSeven, ResumeAnimation001, TestSize.Level1)
{
    MockPipelineContext::SetUp();
    MockPipelineContext::GetCurrent()->onShow_ = true;
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    frameNode->onMainTree_ = true;
    auto mockRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    mockRenderContext->SetPaintRectWithTransform(RectF(0, 0, 100, 100));
    frameNode->renderContext_ = mockRenderContext;
    auto mockParent = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 1, AceType::MakeRefPtr<TextPattern>());
    auto mockParentRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    mockParentRenderContext->SetPaintRectWithTransform(RectF(0, 0, 100, 100));
    mockParent->renderContext_ = mockParentRenderContext;
    mockParent->isActive_ = true;
    frameNode->isActive_ = true;
    frameNode->parent_ = mockParent;
    frameNode->isCalculateInnerVisibleRectClip_ = false;
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->CreateModifier();
    auto textContentModifier = pattern->contentMod_;
    ASSERT_NE(textContentModifier, nullptr);

    AnimationOption option = AnimationOption();
    textContentModifier->raceAnimation_ = AnimationUtils::StartAnimation(option, [&]() {}, []() {});

    textContentModifier->marqueeState_ = MarqueeState::PAUSED;
    textContentModifier->ResumeAnimation();
    EXPECT_EQ(textContentModifier->marqueeState_, MarqueeState::RUNNING);
    textContentModifier->PauseAnimation();
    EXPECT_EQ(textContentModifier->marqueeState_, MarqueeState::PAUSED);
}

/**
 * @tc.name: UseSelfStyle001
 * @tc.desc: test text_styles.cpp UseSelfStyle function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgSeven, UseSelfStyle001, TestSize.Level1)
{
    auto fontStyle = std::make_unique<FontStyle>();
    TextStyle textStyle;

    fontStyle->UpdateFontSize(Dimension(10.0, DimensionUnit::PX));
    fontStyle->UpdateTextColor(Color::WHITE);
    Shadow textShadow;
    textShadow.SetBlurRadius(BLURRADIUS_VALUE);
    textShadow.SetColor(TEXT_COLOR_VALUE);
    textShadow.SetSpreadRadius(SPREADRADIUS_VALUE);
    textShadow.SetOffsetX(ADAPT_OFFSETX_VALUE);
    textShadow.SetOffsetY(ADAPT_OFFSETY_VALUE);
    fontStyle->UpdateTextShadow({ textShadow });
    fontStyle->UpdateItalicFontStyle(Ace::FontStyle::ITALIC);
    fontStyle->UpdateFontWeight(Ace::FontWeight::W200);
    std::vector<std::string> fontFamilies;
    fontFamilies.emplace_back("Arial");
    fontFamilies.emplace_back("Calibri");
    fontStyle->UpdateFontFamily(fontFamilies);
    fontStyle->UpdateFontFeature(ParseFontFeatureSettings("\"ss01\" 0"));
    fontStyle->UpdateTextDecoration({TextDecoration::OVERLINE});
    fontStyle->UpdateTextDecorationColor(Color::WHITE);
    fontStyle->UpdateTextDecorationStyle(TextDecorationStyle::SOLID);
    fontStyle->UpdateTextCase(TextCase::LOWERCASE);
    fontStyle->UpdateAdaptMinFontSize(12.0_fp);
    fontStyle->UpdateAdaptMaxFontSize(10.0_fp);
    fontStyle->UpdateLetterSpacing(Dimension(10.0, DimensionUnit::PX));
    std::vector<Color> colorList;
    colorList.emplace_back(Color::WHITE);
    colorList.emplace_back(Color::BLACK);
    fontStyle->UpdateSymbolColorList(colorList);
    fontStyle->UpdateSymbolRenderingStrategy(2);
    fontStyle->UpdateSymbolEffectStrategy(0);
    fontStyle->UpdateSymbolEffectOptions(SymbolEffectOptions(SymbolEffectType::BOUNCE));
    fontStyle->UpdateMinFontScale(1.0);
    fontStyle->UpdateMaxFontScale(2.0);

    EXPECT_EQ(textStyle.GetSymbolEffectOptions().has_value(), false);
    UseSelfStyle(fontStyle, nullptr, textStyle, true);
    EXPECT_EQ(textStyle.GetSymbolEffectOptions().has_value(), true);
}

/**
 * @tc.name: UseSelfStyle002
 * @tc.desc: test text_styles.cpp UseSelfStyle function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgSeven, UseSelfStyle002, TestSize.Level1)
{
    auto textLineStyle = std::make_unique<TextLineStyle>();
    TextStyle textStyle;

    textLineStyle->UpdateLineHeight(Dimension(10.0, DimensionUnit::PX));
    textLineStyle->UpdateLineSpacing(Dimension(1.0, DimensionUnit::PX));
    textLineStyle->UpdateTextBaseline(TextBaseline::MIDDLE);
    textLineStyle->UpdateBaselineOffset(Dimension(20.0, DimensionUnit::PX));
    textLineStyle->UpdateTextOverflow(TextOverflow::DEFAULT);
    textLineStyle->UpdateTextAlign(TextAlign::LEFT);
    textLineStyle->UpdateMaxLines(1024);
    textLineStyle->UpdateTextIndent(Dimension(40, DimensionUnit::PX));
    textLineStyle->UpdateWordBreak(WordBreak::NORMAL);
    textLineStyle->UpdateEllipsisMode(EllipsisMode::HEAD);
    textLineStyle->UpdateIsOnlyBetweenLines(true);

    UseSelfStyle(nullptr, textLineStyle, textStyle);
    EXPECT_EQ(textStyle.GetLineSpacing(), Dimension(1.0, DimensionUnit::PX));
    EXPECT_EQ(textStyle.GetIsOnlyBetweenLines(), true);
}

/**
 * @tc.name: GetLineBreakStrategyInJson001
 * @tc.desc: test text_styles.cpp GetLineBreakStrategyInJson function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgSeven, GetLineBreakStrategyInJson001, TestSize.Level1)
{
    std::optional<Ace::LineBreakStrategy> value = Ace::LineBreakStrategy::HIGH_QUALITY;
    EXPECT_EQ(GetLineBreakStrategyInJson(value), "HIGH_QUALITY");
    value = Ace::LineBreakStrategy::BALANCED;
    EXPECT_EQ(GetLineBreakStrategyInJson(value), "BALANCED");
    value = Ace::LineBreakStrategy::GREEDY;
    EXPECT_EQ(GetLineBreakStrategyInJson(value), "GREEDY");
}

/**
 * @tc.name: TxtParagraphUpdateColor001
 * @tc.desc: test txt_paragraph.cpp UpdateColor function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgSeven, TxtParagraphUpdateColor001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    pattern->UpdateFontColor(Color::BLACK);

    RefPtr<Paragraph> paragraph = Paragraph::Create(nullptr);
    ASSERT_NE(paragraph, nullptr);
    pattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 1 });
    pattern->UpdateFontColor(Color::BLACK);
}

/**
 * @tc.name: UnRegisterAfterLayoutCallback001
 * @tc.desc: test text_pattern.cpp UnRegisterAfterLayoutCallback function.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgSeven, UnRegisterAfterLayoutCallback001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->RegisterAfterLayoutCallback([]() {});
    EXPECT_EQ(pattern->afterLayoutCallback_.has_value(), true);
    pattern->UnRegisterAfterLayoutCallback();
    EXPECT_EQ(pattern->afterLayoutCallback_.has_value(), false);
}

/**
 * @tc.name: TextShiftMultipleSelection001
 * @tc.desc: test text_pattern.cpp shift multiple selection function.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgSeven, TextShiftMultipleSelection001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    KeyEvent keyEvent;
    keyEvent.code = KeyCode::KEY_SHIFT_LEFT;
    keyEvent.action = KeyAction::DOWN;
    keyEvent.pressedCodes.push_back(KeyCode::KEY_SHIFT_LEFT);
    pattern->HandleKeyEvent(keyEvent);
    pattern->UpdateShiftFlag(keyEvent);

    MouseInfo info;
    info.SetButton(MouseButton::LEFT_BUTTON);
    info.SetAction(MouseAction::PRESS);
    Offset offset(0.0, 0.0);
    info.SetGlobalLocation(offset);
    pattern->HandleMouseEvent(info);
    pattern->ResetSelection();

    EXPECT_EQ(pattern->IsSelected(), false);
}

/**
 * @tc.name: TextEnableAutoSpacing
 * @tc.desc: Test the enable or disable the EnableAutoSpacing attribute.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgSeven, TextEnableAutoSpacing, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default text and placeholder
     */
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE_W);
    textModelNG.SetEnableAutoSpacing(true);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<TextLayoutProperty> textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.expected: Get EnableAutoSpacing Value.
     */
    EXPECT_EQ(textLayoutProperty->GetEnableAutoSpacing(), true);
    EXPECT_EQ(TextModelNG::GetEnableAutoSpacing(frameNode), true);
    /**
     * @tc.expected: Set EnableAutoSpacing False.
     */
    TextModelNG::SetEnableAutoSpacing(frameNode, false);
    /**
     * @tc.expected: Get EnableAutoSpacing Value.
     */
    EXPECT_EQ(textLayoutProperty->GetEnableAutoSpacing(), false);
    EXPECT_EQ(TextModelNG::GetEnableAutoSpacing(frameNode), false);
}

/**
 * @tc.name: TextIncludeFontPadding
 * @tc.desc: Test the enable or disable the IncludeFontPadding attribute.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgSeven, TextIncludeFontPadding, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text node with default text
     */
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE_W);
    textModelNG.SetIncludeFontPadding(true);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<TextLayoutProperty> textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.expected: Get IncludeFontPadding Value.
     */
    EXPECT_EQ(textLayoutProperty->GetIncludeFontPadding(), true);
    EXPECT_EQ(TextModelNG::GetIncludeFontPadding(frameNode), true);
    /**
     * @tc.expected: Set IncludeFontPadding False.
     */
    TextModelNG::SetIncludeFontPadding(frameNode, false);
    /**
     * @tc.expected: Get IncludeFontPadding Value.
     */
    EXPECT_EQ(textLayoutProperty->GetIncludeFontPadding(), false);
    EXPECT_EQ(TextModelNG::GetIncludeFontPadding(frameNode), false);
}

/**
 * @tc.name: TextFallbackLineSpacing
 * @tc.desc: Test the enable or disable the FallbackLineSpacing attribute.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgSeven, TextFallbackLineSpacing, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text node with default text
     */
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE_W);
    textModelNG.SetFallbackLineSpacing(true);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<TextLayoutProperty> textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.expected: Get FallbackLineSpacing Value.
     */
    EXPECT_EQ(textLayoutProperty->GetFallbackLineSpacing(), true);
    EXPECT_EQ(TextModelNG::GetFallbackLineSpacing(frameNode), true);
    /**
     * @tc.expected: Set FallbackLineSpacing False.
     */
    TextModelNG::SetFallbackLineSpacing(frameNode, false);
    /**
     * @tc.expected: Get FallbackLineSpacing Value.
     */
    EXPECT_EQ(textLayoutProperty->GetFallbackLineSpacing(), false);
    EXPECT_EQ(TextModelNG::GetFallbackLineSpacing(frameNode), false);
}

/**
 * @tc.name: TextParagraphVerticalAlign
 * @tc.desc: Test the setting for paragragph vertical align attribute.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgSeven, TextParagraphVerticalAlign, TestSize.Level1)
{
    /**
     * @tc.steps: Create text node and set textVerticalAlign value
     */
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE_W);
    textModelNG.SetTextVerticalAlign(TextVerticalAlign::BASELINE);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<TextLayoutProperty> textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);
    /**
     * @tc.expected: Get textVerticalAlign value
     */
    EXPECT_EQ(textLayoutProperty->GetTextVerticalAlign(), TextVerticalAlign::BASELINE);
    EXPECT_EQ(TextModelNG::GetTextVerticalAlign(frameNode), TextVerticalAlign::BASELINE);
    /**
     * @tc.expected: Set textVerticalAlign TextVerticalAlign::CENTER
     */
    TextModelNG::SetTextVerticalAlign(frameNode, TextVerticalAlign::CENTER);
    /**
     * @tc.expected: Get textVerticalAlign value
     */
    EXPECT_EQ(textLayoutProperty->GetTextVerticalAlign(), TextVerticalAlign::CENTER);
    EXPECT_EQ(TextModelNG::GetTextVerticalAlign(frameNode), TextVerticalAlign::CENTER);
}

/**
 * @tc.name: UpdateFontFeature
 * @tc.desc: test fontFeature.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgSeven, UpdateFontFeature002, TestSize.Level1)
{
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE_W);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<TextLayoutProperty> textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);

    textModelNG.SetFontFeature(FONT_FEATURE_VALUE_0);
    EXPECT_EQ(textLayoutProperty->GetFontFeature(), FONT_FEATURE_VALUE_0);
    textLayoutProperty->UpdateFontFeature(ParseFontFeatureSettings("\"ss01\" 1"));
    TextModelNG::SetFontFeature(frameNode, FONT_FEATURE_VALUE_0);
    EXPECT_EQ(textLayoutProperty->GetFontFeature(), FONT_FEATURE_VALUE_0);
}

/**
 * @tc.name: SetLineSpacing
 * @tc.desc: test setLineSpacing.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgSeven, SetLineSpacing001, TestSize.Level1)
{
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE_W);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<TextLayoutProperty> textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);

    textModelNG.SetLineSpacing(LINE_SPACING_VALUE);
    EXPECT_EQ(textLayoutProperty->GetLineSpacing(), LINE_SPACING_VALUE);
    textModelNG.SetIsOnlyBetweenLines(true);
    EXPECT_EQ(textLayoutProperty->GetIsOnlyBetweenLines(), true);
    TextModelNG::SetLineSpacing(frameNode, LINE_SPACING_VALUE_1, true);
    EXPECT_EQ(textLayoutProperty->GetLineSpacing(), LINE_SPACING_VALUE_1);
    EXPECT_EQ(textLayoutProperty->GetIsOnlyBetweenLines(), true);
    textModelNG.SetIsOnlyBetweenLines(false);
    EXPECT_EQ(textLayoutProperty->GetIsOnlyBetweenLines(), false);
}

/**
 * @tc.name: TextLayoutAlgorithm
 * @tc.desc: test TextLayoutAlgorithm.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgSeven, TextLayoutAlgorithm001, TestSize.Level1)
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

    /**
     * @tc.steps: step2. construct spanItem_.
     */
    std::list<RefPtr<SpanItem>> spans;
    ConstructSpanItemList1(spans);
    EXPECT_EQ(spans.size(), 4);
    textPattern->spans_ = spans;
    textPattern->isSpanStringMode_ = true;

    /**
     * @tc.steps: step3. call TextLayoutAlgorithm.
     * @tc.expected: the spans of each paragraph are split correctly.
     */
    auto textLayoutAlgorithm = AceType::DynamicCast<TextLayoutAlgorithm>(textPattern->CreateLayoutAlgorithm());
    auto size = textLayoutAlgorithm->spans_.size();
    EXPECT_EQ(size, 3);

    auto firstSpans = textLayoutAlgorithm->spans_.front();
    EXPECT_EQ(firstSpans.size(), 2);

    auto endSpans = textLayoutAlgorithm->spans_.back();
    EXPECT_EQ(endSpans.size(), 1);
}

/**
 * @tc.name: TextLayoutAlgorithm
 * @tc.desc: test UpdateParagraphBySpan of MultipleParagraphLayoutAlgorithm.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgSeven, UpdateParagraphBySpan001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textLayoutAlgorithm.
     * @tc.expected: the spans of each paragraph are split correctly.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textFrameNode, geometryNode, textFrameNode->GetLayoutProperty());
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    std::list<RefPtr<SpanItem>> spans;
    ConstructSpanItemList1(spans);
    textPattern->spans_ = spans;
    textPattern->isSpanStringMode_ = true;
    auto textLayoutAlgorithm = AceType::DynamicCast<TextLayoutAlgorithm>(textPattern->CreateLayoutAlgorithm());
    EXPECT_EQ(textLayoutAlgorithm->spans_.size(), 3);

    /**
     * @tc.steps: step2. call MeasureContent.
     * @tc.expected: the paragraphs are and paragraph style created correctly.
     */
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    textLayoutAlgorithm->MeasureContent(parentLayoutConstraint, AccessibilityManager::RawPtr(layoutWrapper));
    auto paragraphs = textLayoutAlgorithm->paragraphManager_->GetParagraphs();
    EXPECT_EQ(paragraphs.size(), 3);

    auto iter = paragraphs.begin();

    auto firstParagraph = *(iter);
    ASSERT_NE(firstParagraph.paragraph, nullptr);

    auto paragraphStyle = firstParagraph.paragraphStyle;
    EXPECT_EQ(paragraphStyle.align, TextAlign::START);
    EXPECT_EQ(paragraphStyle.maxLines, UINT32_MAX);

    iter++;
    auto secondParagraph = *(iter);
    ASSERT_NE(secondParagraph.paragraph, nullptr);
    paragraphStyle = secondParagraph.paragraphStyle;
    EXPECT_EQ(paragraphStyle.align, TextAlign::END);
    EXPECT_EQ(paragraphStyle.indent, Dimension(20.0f));
    EXPECT_EQ(paragraphStyle.wordBreak, WordBreak::BREAK_ALL);
    EXPECT_EQ(paragraphStyle.textOverflow, TextOverflow::ELLIPSIS);

    iter++;
    auto thirdParagraph = *(iter);
    ASSERT_NE(thirdParagraph.paragraph, nullptr);
}

/**
 * @tc.name: InitKeyEvent001
 * @tc.desc: test test_pattern.h InitKeyEvent.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgSeven, InitKeyEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Initialize text and copyOption.
     */
    TextModelNG textModelNG;
    textModelNG.Create(u"123456789");
    textModelNG.SetCopyOption(CopyOptions::InApp);

    /**
     * @tc.steps: step3. test the param keyEventInitialized_ is or not true.
     * @tc.expect: expect keyEventInitialized_ is true.
     */
    textPattern->InitKeyEvent();
    EXPECT_TRUE(textPattern->keyEventInitialized_);
}

/**
 * @tc.name: HandleKeyEvent001
 * @tc.desc: test test_pattern.h HandleKeyEvent.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgSeven, HandleKeyEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    textPattern->pManager_->Reset();
    textPattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 1 });

    /**
     * @tc.steps: step2. Initialize text and textSelector_.
     */
    TextModelNG textModelNG;
    textModelNG.Create(u"123456789");
    textPattern->copyOption_ = CopyOptions::InApp;
    textPattern->textSelector_.Update(2, 6);

    /**
     * @tc.steps: step3. test the enter key is or not legal.
     * @tc.expect: expect the key is legal.
     */
    KeyEvent event;
    event.action = KeyAction::UP;
    EXPECT_FALSE(textPattern->HandleKeyEvent(event));
    event.action = KeyAction::DOWN;
    std::vector<KeyCode> pressCodes = {};
    event.pressedCodes = pressCodes;
    std::vector<KeyCode> ctrlCodes = { KeyCode::KEY_CTRL_LEFT, KeyCode::KEY_CTRL_RIGHT };
    for (auto ctrl : ctrlCodes) {
        event.pressedCodes.clear();
        event.pressedCodes.push_back(ctrl);
        event.pressedCodes.push_back(KeyCode::KEY_C);
        event.code = KeyCode::KEY_C;
        EXPECT_TRUE(textPattern->HandleKeyEvent(event));
    }

    std::vector<KeyCode> shiftCodes = { KeyCode::KEY_SHIFT_LEFT, KeyCode::KEY_SHIFT_RIGHT };
    std::vector<KeyCode> eventCodes = {
        KeyCode::KEY_DPAD_RIGHT,
        KeyCode::KEY_DPAD_LEFT,
        KeyCode::KEY_DPAD_UP,
        KeyCode::KEY_DPAD_DOWN,
    };
    for (auto shift : shiftCodes) {
        for (auto code : eventCodes) {
            event.pressedCodes.clear();
            event.pressedCodes.push_back(shift);
            event.pressedCodes.push_back(code);
            event.code = code;
            EXPECT_TRUE(textPattern->HandleKeyEvent(event));
        }
    }
}

/**
 * @tc.name: GetTextRacePercent001
 * @tc.desc: test GetTextRacePercent.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgSeven, GetTextRacePercent001, TestSize.Level1)
{
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textFrameNode, geometryNode, textFrameNode->GetLayoutProperty());
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    RefPtr<TextContentModifier> textContentModifier =
        AceType::MakeRefPtr<TextContentModifier>(std::optional<TextStyle>(TextStyle()), textPattern);
    ASSERT_NE(textContentModifier, nullptr);

    textContentModifier->GetTextRacePercent();
    textContentModifier->racePercentFloat_->Set(1.0f);
    auto ret = textContentModifier->GetTextRacePercent();
    EXPECT_EQ(ret, 1.0f);
}

/**
 * @tc.name: GetTextRacePercent002
 * @tc.desc: test GetTextRacePercent.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgSeven, GetTextRacePercent002, TestSize.Level1)
{
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textFrameNode, geometryNode, textFrameNode->GetLayoutProperty());
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    RefPtr<TextContentModifier> textContentModifier =
        AceType::MakeRefPtr<TextContentModifier>(std::optional<TextStyle>(TextStyle()), textPattern);
    ASSERT_NE(textContentModifier, nullptr);

    textContentModifier->racePercentFloat_->Set(50.0f);
    textContentModifier->ResetTextRacePercent();
    auto ret = textContentModifier->GetTextRacePercent();
    EXPECT_EQ(ret, 0.0f);
}

/**
 * @tc.name: SetAdaptMaxFontSize001
 * @tc.desc: test SetAdaptMaxFontSize.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgSeven, SetAdaptMaxFontSize001, TestSize.Level1)
{
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

    RefPtr<TextContentModifier> textContentModifier =
        AceType::MakeRefPtr<TextContentModifier>(std::optional<TextStyle>(TextStyle()), textPattern);
    ASSERT_NE(textContentModifier, nullptr);

    textContentModifier->SetAdaptMaxFontSize(ADAPT_MAX_FONT_SIZE_VALUE, textStyle);
    EXPECT_EQ(textContentModifier->adaptMaxFontSize_, ADAPT_MAX_FONT_SIZE_VALUE);
}

/**
 * @tc.name: PaintCustomSpan002
 * @tc.desc: test PaintCustomSpan.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgSeven, PaintCustomSpan002, TestSize.Level1)
{
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    RefPtr<TextContentModifier> textContentModifier =
        AceType::MakeRefPtr<TextContentModifier>(std::optional<TextStyle>(TextStyle()), textPattern);
    ASSERT_NE(textContentModifier, nullptr);

    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, ClipRect(_, _, _)).WillRepeatedly(Return());
    DrawingContext context { canvas, CONTEXT_WIDTH_VALUE, CONTEXT_HEIGHT_VALUE };
    ParagraphStyle paragraphStyle;
    RefPtr<Paragraph> paragraph = Paragraph::Create(paragraphStyle, FontCollection::Current());
    textPattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 100 });
    textContentModifier->PaintCustomSpan(context);
    EXPECT_FALSE(textPattern->pManager_->GetParagraphs().empty());
}

/**
 * @tc.name: PaintImage001
 * @tc.desc: test PaintImage
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgSeven, PaintImage001, TestSize.Level1)
{
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    RefPtr<TextContentModifier> textContentModifier =
        AceType::MakeRefPtr<TextContentModifier>(std::optional<TextStyle>(TextStyle()), textPattern);
    ASSERT_NE(textContentModifier, nullptr);
    int32_t apiVersion = 12;
    AceApplicationInfo::GetInstance().SetApiTargetVersion(apiVersion);
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, ClipRect(_, _, _)).WillRepeatedly(Return());
    DrawingContext context { canvas, CONTEXT_WIDTH_VALUE, CONTEXT_HEIGHT_VALUE };
    RSCanvas& rsCanvas = context.canvas;
    float x = 50.0f;
    float y = 100.0f;
    textContentModifier->PaintImage(rsCanvas, x, y);
    EXPECT_EQ(AceApplicationInfo::GetInstance().GetApiTargetVersion(), 12);
}

/**
 * @tc.name: SetClip001
 * @tc.desc: test SetClip
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgSeven, SetClip001, TestSize.Level1)
{
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    RefPtr<TextContentModifier> textContentModifier =
        AceType::MakeRefPtr<TextContentModifier>(std::optional<TextStyle>(TextStyle()), textPattern);
    ASSERT_NE(textContentModifier, nullptr);
    textContentModifier->clip_ = AccessibilityManager::MakeRefPtr<PropertyBool>(true);
    textContentModifier->SetClip(true);
    textContentModifier->clip_ = AccessibilityManager::MakeRefPtr<PropertyBool>(false);
    textContentModifier->SetClip(true);
    EXPECT_TRUE(textContentModifier->clip_);
}

/**
 * @tc.name: TypedText001
 * @tc.desc: test typed_text.h static functions.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgSeven, TypedText001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create TypedText and create value.
     */
    TypedText typedText;
    const char* test = nullptr;

    /**
     * @tc.steps: step2. test GetUTF8OneCharacterSize and GetUTF8Next.
     */
    uint32_t nextIndex = 2;
    EXPECT_EQ(typedText.GetUTF8OneCharacterSize(test), 0);
    EXPECT_EQ(typedText.GetUTF8Next(test, 1, nextIndex), 0);

    /**
     * @tc.steps: step3. change value and test again.
     */
    const char* test1 = TEXT_CONTENT1;
    EXPECT_EQ(typedText.GetUTF8OneCharacterSize(test1), 1);
    EXPECT_EQ(typedText.GetUTF8Next(test1, 1, nextIndex), 105);

    const char* test2 = TEXT_CONTENT2;
    EXPECT_EQ(typedText.GetUTF8OneCharacterSize(test2), 1);
    EXPECT_EQ(typedText.GetUTF8Next(test2, 1, nextIndex), 101);

    /**
     * @tc.steps: step4. test IsEmoji.
     */
    EXPECT_EQ(typedText.IsEmoji(CODE1), false);
    EXPECT_EQ(typedText.IsEmoji(CODE2), true);
    EXPECT_EQ(typedText.IsEmoji(CODE3), true);
}

/**
 * @tc.name: TextContentModifier003
 * @tc.desc: test text_content_modifier.cpp onDraw function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgSeven, TextContentModifier003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode and geometryNode.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TOAST_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textPaintMethod = textPattern->CreateNodePaintMethod();
    ASSERT_NE(textPaintMethod, nullptr);
    auto textContentModifier = textPattern->GetContentModifier();
    ASSERT_NE(textContentModifier, nullptr);

    /**
     * @tc.steps: step2. set context.
     */
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, ClipRect(_, _, _)).WillRepeatedly(Return());
    DrawingContext context { canvas, CONTEXT_WIDTH_VALUE, CONTEXT_HEIGHT_VALUE };

    /**
     * @tc.steps: step3. call onDraw function of textContentModifier.
     *               The ifPaintObscuration_ of textContentModifier is false.
     */
    textContentModifier->onDraw(context);
    EXPECT_EQ(textContentModifier->ifPaintObscuration_, false);

    /**
     * @tc.steps: step4. set ifPaintObscuration_ to true.
     */
    textContentModifier->SetIfPaintObscuration(true);

    /**
     * @tc.steps: step5. call onDraw function of textContentModifier.
     *               The ifPaintObscuration_ of textContentModifier is true.
     */
    textContentModifier->onDraw(context);
    EXPECT_EQ(textContentModifier->ifPaintObscuration_, true);

    /**
     * @tc.steps: step6. call onDraw function of textContentModifier.
     *               The ifPaintObscuration_ of textContentModifier is true.
     */
    textContentModifier->onDraw(context);
    EXPECT_EQ(textContentModifier->ifPaintObscuration_, true);

    /**
     * @tc.steps: step7. set ifPaintObscuration_ to false.
     */
    textContentModifier->SetIfPaintObscuration(false);

    /**
     * @tc.steps: step8. call onDraw function of textContentModifier.
     *               The ifPaintObscuration_ of textContentModifier is false.
     */
    textContentModifier->onDraw(context);
    EXPECT_EQ(textContentModifier->ifPaintObscuration_, false);
}

/**
 * @tc.name: TextContentModifier004
 * @tc.desc: test text_content_modifier.cpp DrawObscuration function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgSeven, TextContentModifier004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TOAST_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textPaintMethod = textPattern->CreateNodePaintMethod();
    ASSERT_NE(textPaintMethod, nullptr);
    auto textContentModifier = textPattern->GetContentModifier();
    ASSERT_NE(textContentModifier, nullptr);

    /**
     * @tc.steps: step2. set context and paragraph.
     *                   set defaultFontSize defaultTextColor and contentSize of textContentModifier.
     *                   push one rect to drawObscuredRects and set drawObscuredRects_ to drawObscuredRects.
     */
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, ClipRect(_, _, _)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    DrawingContext context { canvas, CONTEXT_WIDTH_VALUE, CONTEXT_HEIGHT_VALUE };
    ParagraphStyle paragraphStyle;
    RefPtr<Paragraph> paragraph = Paragraph::Create(paragraphStyle, FontCollection::Current());
    textPattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 100 });
    TextStyle textStyle;
    textStyle.SetFontSize(ADAPT_FONT_SIZE_VALUE);
    textStyle.SetTextColor(TEXT_COLOR_VALUE);
    textContentModifier->SetDefaultAnimatablePropertyValue(textStyle, textFrameNode);
    SizeF contentSize(TEXT_CONTENT_SIZE, TEXT_CONTENT_SIZE);
    textContentModifier->SetContentSize(contentSize);
    std::vector<RectF> drawObscuredRects;
    RectF textRect;
    textRect.SetHeight(TEXT_RECT_WIDTH);
    textRect.SetWidth(TEXT_RECT_WIDTH);
    textRect.SetTop(TEXT_RECT_TOP_ONE);
    drawObscuredRects.push_back(textRect);
    textContentModifier->SetDrawObscuredRects(drawObscuredRects);

    /**
     * @tc.steps: step3. call DrawObscuration function of textContentModifier.
     * @tc.expected: The drawObscuredRects_ of textContentModifier is drawObscuredRects.
     */
    textContentModifier->DrawObscuration(context);
    EXPECT_EQ(textContentModifier->drawObscuredRects_, drawObscuredRects);

    /**
     * @tc.steps: step4. push two rect to drawObscuredRects and set drawObscuredRects_ to drawObscuredRects.
     */
    drawObscuredRects.push_back(textRect);
    textRect.SetTop(TEXT_RECT_TOP_TWO);
    drawObscuredRects.push_back(textRect);
    textContentModifier->SetDrawObscuredRects(drawObscuredRects);

    /**
     * @tc.steps: step5. call DrawObscuration function of textContentModifier.
     * @tc.expected: The drawObscuredRects_ of textContentModifier is drawObscuredRects.
     */
    textContentModifier->DrawObscuration(context);
    EXPECT_EQ(textContentModifier->drawObscuredRects_, drawObscuredRects);

    /**
     * @tc.steps: step6. push three rect to drawObscuredRects and set drawObscuredRects_ to drawObscuredRects.
     */
    textRect.SetHeight(TEXT_RECT_SIZE_ZEOR);
    drawObscuredRects.push_back(textRect);
    textContentModifier->SetDrawObscuredRects(drawObscuredRects);

    /**
     * @tc.steps: step7. call DrawObscuration function of textContentModifier.
     * @tc.expected: The drawObscuredRects_ of textContentModifier is drawObscuredRects.
     */
    textContentModifier->DrawObscuration(context);
    EXPECT_EQ(textContentModifier->drawObscuredRects_, drawObscuredRects);

    /**
     * @tc.steps: step8. push four rect to drawObscuredRects and set drawObscuredRects_ to drawObscuredRects.
     */
    textRect.SetWidth(TEXT_RECT_SIZE_ZEOR);
    drawObscuredRects.push_back(textRect);
    textContentModifier->SetDrawObscuredRects(drawObscuredRects);

    /**
     * @tc.steps: step9. call DrawObscuration function of textContentModifier.
     * @tc.expected: The drawObscuredRects_ of textContentModifier is drawObscuredRects.
     */
    textContentModifier->DrawObscuration(context);
    EXPECT_EQ(textContentModifier->drawObscuredRects_, drawObscuredRects);
    textPattern->pManager_->Reset();
}
} // namespace OHOS::Ace::NG