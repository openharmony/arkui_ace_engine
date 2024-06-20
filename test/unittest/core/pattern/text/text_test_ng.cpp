/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

namespace OHOS::Ace::NG {

namespace {} // namespace

class TextTestNg : public TextBases {
public:
};

/**
 * @tc.name: TextFrameNodeCreator001
 * @tc.desc: Test all the properties of text.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextFrameNodeCreator001, TestSize.Level1)
{
    TestProperty testProperty;
    testProperty.fontSizeValue = std::make_optional(FONT_SIZE_VALUE);
    testProperty.textColorValue = std::make_optional(TEXT_COLOR_VALUE);
    testProperty.italicFontStyleValue = std::make_optional(ITALIC_FONT_STYLE_VALUE);
    testProperty.fontWeightValue = std::make_optional(FONT_WEIGHT_VALUE);
    testProperty.fontFamilyValue = std::make_optional(FONT_FAMILY_VALUE);
    testProperty.textAlignValue = std::make_optional(TEXT_ALIGN_VALUE);
    testProperty.textOverflowValue = std::make_optional(TEXT_OVERFLOW_VALUE);
    testProperty.maxLinesValue = std::make_optional(MAX_LINES_VALUE);
    testProperty.lineHeightValue = std::make_optional(LINE_HEIGHT_VALUE);
    testProperty.lineSpacingValue = std::make_optional(LINE_SPACING_VALUE);
    testProperty.textDecorationValue = std::make_optional(TEXT_DECORATION_VALUE);
    testProperty.textDecorationColorValue = std::make_optional(TEXT_DECORATION_COLOR_VALUE);
    testProperty.baselineOffsetValue = std::make_optional(BASELINE_OFFSET_VALUE);
    testProperty.textCaseValue = std::make_optional(TEXT_CASE_VALUE);
    testProperty.adaptMinFontSize = std::make_optional(ADAPT_MIN_FONT_SIZE_VALUE);
    testProperty.adaptMaxFontSize = std::make_optional(ADAPT_MAX_FONT_SIZE_VALUE);
    testProperty.textIndent = std::make_optional(TEXT_INDENT);
    testProperty.wordBreak = std::make_optional(TEXT_WORD_BREAK);
    testProperty.lineBreakStrategy = std::make_optional(TEXT_LINE_BREAK_STRATEGY);

    RefPtr<FrameNode> frameNode = CreateTextParagraph(CREATE_VALUE, testProperty);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<TextLayoutProperty> textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_EQ(textLayoutProperty->GetContentValue(), CREATE_VALUE);
    const std::unique_ptr<FontStyle>& fontStyle = textLayoutProperty->GetFontStyle();
    ASSERT_NE(fontStyle, nullptr);
    const std::unique_ptr<TextLineStyle>& textLineStyle = textLayoutProperty->GetTextLineStyle();
    ASSERT_NE(textLineStyle, nullptr);
    TextStyle textStyle = CreateTextStyleUsingTheme(fontStyle, textLineStyle, nullptr);
    EXPECT_EQ(textStyle.GetFontSize(), FONT_SIZE_VALUE);
    EXPECT_EQ(textStyle.GetTextColor(), TEXT_COLOR_VALUE);
    EXPECT_EQ(textStyle.GetFontStyle(), ITALIC_FONT_STYLE_VALUE);
    EXPECT_EQ(textStyle.GetFontWeight(), FONT_WEIGHT_VALUE);
    EXPECT_EQ(textStyle.GetFontFamilies(), FONT_FAMILY_VALUE);
    EXPECT_EQ(textStyle.GetTextAlign(), TEXT_ALIGN_VALUE);
    EXPECT_EQ(textStyle.GetTextOverflow(), TEXT_OVERFLOW_VALUE);
    EXPECT_EQ(textStyle.GetMaxLines(), MAX_LINES_VALUE);
    EXPECT_EQ(textStyle.GetLineHeight(), LINE_HEIGHT_VALUE);
    EXPECT_EQ(textStyle.GetLineSpacing(), LINE_SPACING_VALUE);
    EXPECT_EQ(textStyle.GetTextDecoration(), TEXT_DECORATION_VALUE);
    EXPECT_EQ(textStyle.GetTextDecorationColor(), TEXT_DECORATION_COLOR_VALUE);
    EXPECT_EQ(textStyle.GetBaselineOffset(), BASELINE_OFFSET_VALUE);
    EXPECT_EQ(textStyle.GetTextCase(), TEXT_CASE_VALUE);
    EXPECT_EQ(textStyle.GetAdaptMinFontSize(), ADAPT_MIN_FONT_SIZE_VALUE);
    EXPECT_EQ(textStyle.GetAdaptMaxFontSize(), ADAPT_MAX_FONT_SIZE_VALUE);
    EXPECT_EQ(textStyle.GetAdaptTextSize(),
        testProperty.adaptMinFontSize.has_value() || testProperty.adaptMaxFontSize.has_value());
    EXPECT_EQ(textStyle.GetWordBreak(), TEXT_WORD_BREAK);
    EXPECT_EQ(textStyle.GetLineBreakStrategy(), TEXT_LINE_BREAK_STRATEGY);

    /**
     * @tc.cases: case2. renderContext has foreground color and modifier will foreground color flag
     */
    frameNode->GetRenderContext()->UpdateForegroundColor(Color::RED);
    textStyle = CreateTextStyleUsingThemeWithText(frameNode, fontStyle, textLineStyle, nullptr);
    EXPECT_EQ(textStyle.GetTextColor(), FOREGROUND_COLOR_VALUE);
}

/**
 * @tc.name: TextFrameNodeCreator002
 * @tc.desc: Test all the property of text.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextFrameNodeCreator002, TestSize.Level1)
{
    TestProperty testProperty;
    testProperty.letterSpacing = std::make_optional(LETTER_SPACING);
    testProperty.baselineOffsetValue = std::make_optional(BASELINE_OFFSET_VALUE);
    auto frameNode = CreateTextParagraph(CREATE_VALUE, testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    auto textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_EQ(textLayoutProperty->GetContentValue(), CREATE_VALUE);
    const std::unique_ptr<FontStyle>& fontStyle = textLayoutProperty->GetFontStyle();
    ASSERT_NE(fontStyle, nullptr);
    const std::unique_ptr<TextLineStyle>& textLineStyle = textLayoutProperty->GetTextLineStyle();
    ASSERT_NE(textLineStyle, nullptr);
    auto textStyle = CreateTextStyleUsingTheme(fontStyle, textLineStyle, nullptr);
    EXPECT_EQ(textStyle.GetLetterSpacing(), LETTER_SPACING);
}

/**
 * @tc.name: TextFrameNodeCreator003
 * @tc.desc: Test all the fontWeight and events of text.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextFrameNodeCreator003, TestSize.Level1)
{
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE);
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<TextLayoutProperty> textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_EQ(textLayoutProperty->GetContentValue(), CREATE_VALUE);
    textModelNG.SetFontWeight(FontWeight::LIGHTER);
    textModelNG.SetLineHeight(LINE_HEIGHT_VALUE);
    const std::unique_ptr<FontStyle>& fontStyle = textLayoutProperty->GetFontStyle();
    ASSERT_NE(textLayoutProperty, nullptr);
    const std::unique_ptr<TextLineStyle>& textLineStyle = textLayoutProperty->GetTextLineStyle();
    ASSERT_NE(textLayoutProperty, nullptr);
    TextStyle textStyle = CreateTextStyleUsingTheme(fontStyle, textLineStyle, nullptr);

    textModelNG.SetFontWeight(FontWeight::LIGHTER);
    textStyle.SetFontWeight(FontWeight::W100);
    EXPECT_EQ(textStyle.GetFontWeight(), FontWeight::W100);
    textModelNG.SetFontWeight(FontWeight::REGULAR);
    textStyle.SetFontWeight(FontWeight::W400);
    EXPECT_EQ(textStyle.GetFontWeight(), FontWeight::W400);
    textModelNG.SetFontWeight(FontWeight::NORMAL);
    textStyle.SetFontWeight(FontWeight::W400);
    EXPECT_EQ(textStyle.GetFontWeight(), FontWeight::W400);
    textModelNG.SetFontWeight(FontWeight::MEDIUM);
    textStyle.SetFontWeight(FontWeight::W500);
    EXPECT_EQ(textStyle.GetFontWeight(), FontWeight::W500);
    textModelNG.SetFontWeight(FontWeight::BOLD);
    textStyle.SetFontWeight(FontWeight::W700);
    EXPECT_EQ(textStyle.GetFontWeight(), FontWeight::W700);
    textModelNG.SetFontWeight(FontWeight::BOLDER);
    textStyle.SetFontWeight(FontWeight::W900);
    EXPECT_EQ(textStyle.GetFontWeight(), FontWeight::W900);
    textModelNG.SetFontWeight(FontWeight::W900);
    textStyle.SetFontWeight(FontWeight::W900);
    EXPECT_EQ(textStyle.GetFontWeight(), FontWeight::W900);

    textModelNG.SetOnClick(onClickFunc);
    textModelNG.SetRemoteMessage(onRemoteMessage);
    textModelNG.SetCopyOption(copyOption);
    textModelNG.SetOnDragStart(OnDragStartFunction);
    textModelNG.SetOnDragEnter(OnDragDropFunction);
    textModelNG.SetOnDragMove(OnDragDropFunction);
    textModelNG.SetOnDragLeave(OnDragDropFunction);
    textModelNG.SetOnDrop(OnDragDropFunction);
}

/**
 * @tc.name: OnAttachToFrameNode001
 * @tc.desc: Test TextPattern OnAttachToFrameNode when GetHost is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, OnAttachToFrameNode001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    pattern->OnAttachToFrameNode();
    EXPECT_EQ(pattern->longPressEvent_, nullptr);
}

/**
 * @tc.name: OnHandleMoveDone001
 * @tc.desc: Test TextPattern OnHandleMoveDone
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, OnHandleMoveDone001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();
    pattern->textSelector_.Update(0, TEXT_SIZE_INT);

    /**
     * @tc.steps: step2. call OnHandleMoveDone when SelectOverlay is off.
     * @tc.expected: the function exits normally
     */
    RectF handleRect = CONTENT_RECT;
    pattern->selectOverlay_->OnHandleMoveDone(handleRect, true);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), TEXT_SIZE_INT);

    /**
     * @tc.steps: step3. call OnHandleMoveDone when SelectOverlay is on.
     * @tc.expected: the OnHandleMoveDone function exits normally
     */
    pattern->ShowSelectOverlay();
    bool isFirstHandle[2] = { true, false };
    for (int i = 0; i < 2; i++) {
        pattern->textForDisplay_ = "abcdefghij";
        pattern->selectOverlay_->OnHandleMoveDone(handleRect, isFirstHandle[i]);
        EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
        EXPECT_EQ(pattern->textSelector_.GetTextEnd(), TEXT_SIZE_INT);
    }
}

/**
 * @tc.name: ShowSelectOverlay001
 * @tc.desc: Test TextPattern ShowSelectOverlay when SelectOverlayProxy is not nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, ShowSelectOverlay001, TestSize.Level1)
{
    auto [frameNode, pattern] = Init();
    /**
     * @tc.steps: step1. call ShowSelectOverlay
     * @tc.expected: select overlay is on.
     */
    pattern->ShowSelectOverlay();
    EXPECT_TRUE(pattern->selectOverlay_->SelectOverlayIsOn());
}

/**
 * @tc.name: OnModifyDone001
 * @tc.desc: Test TextPattern OnModifyDone when frameNode is not nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, OnModifyDone001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    pattern->selectOverlayProxy_ = nullptr;
    pattern->OnModifyDone();
    EXPECT_EQ(pattern->selectOverlayProxy_, nullptr);
}

/**
 * @tc.name: OnModifyDone002
 * @tc.desc: Test TextPattern OnModifyDone longPressEvent.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, OnModifyDone002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. set textLayoutProperty.
     * copyOption: CopyOptions::InApp
     */
    textLayoutProperty->UpdateCopyOption(CopyOptions::InApp);
    textLayoutProperty->UpdateContent(TEXT_CONTENT);

    /**
     * @tc.steps: step3. check the longPressEvent.
     * @tc.expected: longPressEvent is triggered
     */
    textPattern->OnModifyDone();
    EXPECT_NE(textPattern->longPressEvent_, nullptr);
    EXPECT_EQ(textPattern->textForDisplay_, TEXT_CONTENT);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap001
 * @tc.desc: Test TextPattern OnDirtyLayoutWrapperSwap when skipMeasure is true.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, OnDirtyLayoutWrapperSwap001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    pattern->selectOverlayProxy_ = nullptr;
    DirtySwapConfig config;
    config.skipMeasure = true;
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), frameNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    auto rowLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));
    auto ret = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(ret);
    EXPECT_EQ(pattern->selectOverlayProxy_, nullptr);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap002
 * @tc.desc: Test TextPattern OnDirtyLayoutWrapperSwap when skipMeasure is fasle.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, OnDirtyLayoutWrapperSwap002, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    pattern->selectOverlayProxy_ = nullptr;
    DirtySwapConfig config;
    config.skipMeasure = false;
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), frameNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    auto rowLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));
    auto ret = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_TRUE(ret);
    EXPECT_EQ(pattern->selectOverlayProxy_, nullptr);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap003
 * @tc.desc: Test TextPattern OnDirtyLayoutWrapperSwap when skipMeasure is fasle and paragraph is not nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, OnDirtyLayoutWrapperSwap003, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    pattern->selectOverlayProxy_ = nullptr;

    DirtySwapConfig config;
    config.skipMeasure = false;
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), frameNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);

    auto rowLayoutAlgorithm = AceType::DynamicCast<TextLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    TextStyle textStyle;
    LayoutConstraintF contentConstraint;
    auto ret =
        rowLayoutAlgorithm->CreateParagraphAndLayout(textStyle, "", contentConstraint, AceType::RawPtr(frameNode));
    EXPECT_TRUE(ret);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));
    ret = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_TRUE(ret);
    EXPECT_EQ(pattern->selectOverlayProxy_, nullptr);

    SelectOverlayInfo selectOverlayInfo;
    selectOverlayInfo.singleLineHeight = NODE_ID;
    auto root = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto selectOverlayManager = AceType::MakeRefPtr<SelectOverlayManager>(root);
    auto proxy = selectOverlayManager->CreateAndShowSelectOverlay(selectOverlayInfo, nullptr, false);
    pattern->selectOverlayProxy_ = proxy;
    ret = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: BeforeCreateLayoutWrapper001
 * @tc.desc: Test TextPattern BeforeCreateLayoutWrapper when paragraph is not nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, BeforeCreateLayoutWrapper001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    pattern->selectOverlayProxy_ = nullptr;

    auto rowLayoutAlgorithm = AceType::DynamicCast<TextLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    TextStyle textStyle;
    LayoutConstraintF contentConstraint;
    auto ret =
        rowLayoutAlgorithm->CreateParagraphAndLayout(textStyle, "", contentConstraint, AceType::RawPtr(frameNode));
    EXPECT_TRUE(ret);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), frameNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));
    pattern->BeforeCreateLayoutWrapper();
    EXPECT_EQ(pattern->selectOverlayProxy_, nullptr);
}

/**
 * @tc.name: BeforeCreateLayoutWrapper002
 * @tc.desc: Test TextPattern BeforeCreateLayoutWrapper when frameNode child is empty.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, BeforeCreateLayoutWrapper002, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);

    pattern->AttachToFrameNode(frameNode);
    pattern->selectOverlayProxy_ = nullptr;

    auto rowLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), frameNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));
    pattern->BeforeCreateLayoutWrapper();
    EXPECT_EQ(pattern->selectOverlayProxy_, nullptr);
}

/**
 * @tc.name: BeforeCreateLayoutWrapper003
 * @tc.desc: Test TextPattern BeforeCreateLayoutWrapper when paragraph is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, BeforeCreateLayoutWrapper003, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    pattern->selectOverlayProxy_ = nullptr;

    auto rowLayoutAlgorithm = AceType::DynamicCast<TextLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    TextStyle textStyle;
    LayoutConstraintF contentConstraint;
    auto ret =
        rowLayoutAlgorithm->CreateParagraphAndLayout(textStyle, "", contentConstraint, AceType::RawPtr(frameNode));
    EXPECT_TRUE(ret);

    DirtySwapConfig config;
    config.skipMeasure = false;
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, AceType::MakeRefPtr<GeometryNode>(), nullptr);
    ASSERT_NE(layoutWrapper, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));
    ret = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_TRUE(ret);
    pattern->BeforeCreateLayoutWrapper();
    EXPECT_EQ(pattern->selectOverlayProxy_, nullptr);
}

/**
 * @tc.name: BeforeCreateLayoutWrapper004
 * @tc.desc: Test TextPattern BeforeCreateLayoutWrapper when frameNode child is not empty.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, BeforeCreateLayoutWrapper004, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);

    auto patternChild = AceType::MakeRefPtr<TextPattern>();
    auto frameNodeChild = FrameNode::CreateFrameNode("Test", 1, patternChild);
    ASSERT_NE(frameNodeChild, nullptr);

    frameNode->AddChild(frameNodeChild);
    pattern->AttachToFrameNode(frameNode);
    pattern->selectOverlayProxy_ = nullptr;

    auto rowLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), frameNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));
    pattern->BeforeCreateLayoutWrapper();
    EXPECT_EQ(pattern->selectOverlayProxy_, nullptr);
}

/**
 * @tc.name: OnHandleMove001
 * @tc.desc: Test TextPattern OnHandleMove when SelectOverlayProxy is not nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, OnHandleMove001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    pattern->AttachToFrameNode(frameNode);
    /**
     * @tc.steps: step1. construct a SelectOverlayManager
     */
    SelectOverlayInfo selectOverlayInfo;
    selectOverlayInfo.singleLineHeight = NODE_ID;
    auto root = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto selectOverlayManager = AceType::MakeRefPtr<SelectOverlayManager>(root);

    /**
     * @tc.steps: step2. call CreateAndShowSelectOverlay
     * @tc.expected: return the proxy which has the right SelectOverlayId
     */
    auto proxy = selectOverlayManager->CreateAndShowSelectOverlay(selectOverlayInfo, nullptr, false);
    pattern->selectOverlayProxy_ = proxy;
    EXPECT_NE(pattern->selectOverlayProxy_, nullptr);
}

/**
 * @tc.name: TextCreateParagraph002
 * @tc.desc: Correctly create Paragraph only Set content.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextCreateParagraph002, TestSize.Level1)
{
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, GetMaxWidth).WillRepeatedly(Return(150));
    EXPECT_CALL(*paragraph, GetHeight).WillRepeatedly(Return(50));
    EXPECT_CALL(*paragraph, GetAlphabeticBaseline).WillOnce(Return(0));
    EXPECT_CALL(*paragraph, PushStyle);
    EXPECT_CALL(*paragraph, Build);
    // investigate why it layouts twice
    EXPECT_CALL(*paragraph, Layout).Times(2);

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
     * @tc.steps: step2. set Content.
     */

    textLayoutProperty->UpdateContent(CREATE_VALUE);

    /**
     * @tc.steps: step3. create textLayoutAlgorithm.
     */

    auto textLayoutAlgorithm = AceType::MakeRefPtr<TextLayoutAlgorithm>();
    EXPECT_FALSE(textLayoutAlgorithm == nullptr);
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    textLayoutAlgorithm->MeasureContent(parentLayoutConstraint, AccessibilityManager::RawPtr(layoutWrapper));

    textLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    textLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
}

/**
 * @tc.name: TextLayoutTest001
 * @tc.desc: Set content , width and height to Text and the check result.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextLayoutTest001, TestSize.Level1)
{
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, GetMaxWidth).WillRepeatedly(Return(TEXT_WIDTH));
    EXPECT_CALL(*paragraph, GetHeight).WillRepeatedly(Return(150));
    EXPECT_CALL(*paragraph, Layout);
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
     * content: CREATE_VALUE
     * width: 100.0f
     * height: 75.0f
     */

    textLayoutProperty->UpdateContent(CREATE_VALUE);
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.selfIdealSize.SetSize(TEXT_SIZE);
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;

    /**
     * @tc.steps: step3. create textLayoutAlgorithm.
     */

    auto textLayoutAlgorithm = AceType::MakeRefPtr<TextLayoutAlgorithm>();
    textLayoutAlgorithm->MeasureContent(parentLayoutConstraint, AccessibilityManager::RawPtr(layoutWrapper));
    textLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    textLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
}

/**
 * @tc.name: TextLayoutTest002
 * @tc.desc: set baselineOffset and maxsize of Text check height
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextLayoutTest002, TestSize.Level1)
{
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, GetLongestLine).WillRepeatedly(Return(100));
    EXPECT_CALL(*paragraph, GetMaxWidth).WillRepeatedly(Return(150));
    EXPECT_CALL(*paragraph, GetHeight).WillRepeatedly(Return(50));
    EXPECT_CALL(*paragraph, Layout).Times(2);
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

    textLayoutProperty->UpdateContent(CREATE_VALUE);
    textLayoutProperty->UpdateBaselineOffset(BASELINE_OFFSET_VALUE);
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;

    /**
     * @tc.steps: step3. create textLayoutAlgorithm.
     */

    auto textLayoutAlgorithm = AceType::MakeRefPtr<TextLayoutAlgorithm>();
    auto sizeX =
        textLayoutAlgorithm->MeasureContent(parentLayoutConstraint, AccessibilityManager::RawPtr(layoutWrapper));

    /**
     * @tc.steps: step4. check the size.
     */

    EXPECT_EQ(sizeX->Height(), BASELINE_OFFSET_VALUE.Value() + 50.0);
}

/**
 * @tc.name: TextLayoutTest003
 * @tc.desc: set minFontSize and maxFontSize of Text check then check
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextLayoutTest003, TestSize.Level1)
{
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, Build).Times(1);
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
     * minFontSize: 50_px
     * macFontSize: 80_px
     */

    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;

    TextStyle textStyle;
    textStyle.SetTextAlign(TextAlign::CENTER);
    textStyle.SetAdaptTextSize(ADAPT_MIN_FONT_SIZE_VALUE, ADAPT_MAX_FONT_SIZE_VALUE_S);
    textStyle.SetAdaptFontSizeStep(ADAPT_FONT_SIZE_STEP_VALUE);

    auto pipeline = textFrameNode->GetContextRefPtr();

    /**
     * @tc.steps: step3. create textLayoutAlgorithm.
     */

    auto textLayoutAlgorithm = AceType::MakeRefPtr<TextLayoutAlgorithm>();
    auto result = textLayoutAlgorithm->AdaptMinTextSize(
        textStyle, CREATE_VALUE, parentLayoutConstraint, AceType::RawPtr(textFrameNode));

    /**
     * @tc.steps: step4. check the fontSize.
     */

    EXPECT_TRUE(result);
}

/**
 * @tc.name: TextLayoutTest004
 * @tc.desc: set minFontSize and maxFontSize of Text check then check
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextLayoutTest004, TestSize.Level1)
{
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, Build).Times(1);
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
     * minFontSize: 50_px
     * macFontSize: 80_px
     */

    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;

    TextStyle textStyle;
    textStyle.SetMaxLines(MAX_LINES);
    textStyle.SetTextAlign(TextAlign::CENTER);
    textStyle.SetAdaptTextSize(ADAPT_MIN_FONT_SIZE_VALUE, ADAPT_MAX_FONT_SIZE_VALUE_S);
    textStyle.SetAdaptFontSizeStep(ADAPT_FONT_SIZE_STEP_VALUE);

    auto pipeline = textFrameNode->GetContextRefPtr();

    /**
     * @tc.steps: step3. create textLayoutAlgorithm.
     */

    auto textLayoutAlgorithm = AceType::MakeRefPtr<TextLayoutAlgorithm>();
    auto result = textLayoutAlgorithm->AdaptMinTextSize(
        textStyle, CREATE_VALUE, parentLayoutConstraint, AceType::RawPtr(textFrameNode));

    /**
     * @tc.steps: step4. check the fontSize.
     */

    EXPECT_TRUE(result);
}

/**
 * @tc.name: TextLayoutTest005
 * @tc.desc: set minFontSize and maxFontSize of Text check then check when maxFontSize >= minFontSize
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextLayoutTest005, TestSize.Level1)
{
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, Build).Times(1);
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
     * minFontSize: 50_px
     * macFontSize: 80_px
     */

    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;

    TextStyle textStyle;
    textStyle.SetMaxLines(MAX_LINES);
    textStyle.SetTextAlign(TextAlign::CENTER);
    textStyle.SetAdaptTextSize(ADAPT_MAX_FONT_SIZE_VALUE_S, ADAPT_MIN_FONT_SIZE_VALUE);
    textStyle.SetAdaptFontSizeStep(ADAPT_FONT_SIZE_STEP_VALUE);

    auto pipeline = textFrameNode->GetContextRefPtr();

    /**
     * @tc.steps: step3. create textLayoutAlgorithm.
     */

    auto textLayoutAlgorithm = AceType::MakeRefPtr<TextLayoutAlgorithm>();
    auto result = textLayoutAlgorithm->AdaptMinTextSize(
        textStyle, CREATE_VALUE, parentLayoutConstraint, AceType::RawPtr(textFrameNode));

    /**
     * @tc.steps: step4. check the fontSize.
     */

    EXPECT_TRUE(result);
}

/**
 * @tc.name: TextLayoutTest006
 * @tc.desc: set baselineOffset and maxsize of Text check height when paragraph_ is not nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextLayoutTest006, TestSize.Level1)
{
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, GetLongestLine).WillRepeatedly(Return(100));
    EXPECT_CALL(*paragraph, GetMaxWidth).WillRepeatedly(Return(150));
    EXPECT_CALL(*paragraph, GetHeight).WillRepeatedly(Return(50));
    EXPECT_CALL(*paragraph, AddText).Times(2);
    EXPECT_CALL(*paragraph, Layout).Times(3);
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

    textLayoutProperty->UpdateContent(CREATE_VALUE);
    textLayoutProperty->UpdateBaselineOffset(BASELINE_OFFSET_VALUE);
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;

    /**
     * @tc.steps: step3. create textLayoutAlgorithm.
     */

    auto textLayoutAlgorithm = AceType::MakeRefPtr<TextLayoutAlgorithm>();
    TextStyle textStyle;
    LayoutConstraintF contentConstraint;
    auto ret =
        textLayoutAlgorithm->CreateParagraphAndLayout(textStyle, "", contentConstraint, AceType::RawPtr(textFrameNode));
    EXPECT_TRUE(ret);
    auto sizeX =
        textLayoutAlgorithm->MeasureContent(parentLayoutConstraint, AccessibilityManager::RawPtr(layoutWrapper));

    /**
     * @tc.steps: step4. check the size.
     */

    EXPECT_EQ(sizeX->Height(), BASELINE_OFFSET_VALUE.Value() + 50.0);
}

/**
 * @tc.name: TextLayoutTest007
 * @tc.desc: set baselineOffset and maxsize of Text check height when AdaptTextSize is disable.
 *           contentConstraint.maxSize.IsPositive() is false.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextLayoutTest007, TestSize.Level1)
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
     * baselineOffset: 20_px
     */

    textLayoutProperty->UpdateContent(CREATE_VALUE);
    textLayoutProperty->UpdateBaselineOffset(BASELINE_OFFSET_VALUE);
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize.SetHeight(100.0);

    /**
     * @tc.steps: step3. create textLayoutAlgorithm.
     */

    auto textLayoutAlgorithm = AceType::MakeRefPtr<TextLayoutAlgorithm>();
    TextStyle textStyle;
    Dimension adaptMinFontSize(DIMENSION, DimensionUnit::PERCENT);
    textStyle.SetAdaptMinFontSize(adaptMinFontSize);
    auto ret = textLayoutAlgorithm->CreateParagraphAndLayout(
        textStyle, "", parentLayoutConstraint, AceType::RawPtr(textFrameNode));
    EXPECT_TRUE(ret);
    auto sizeX =
        textLayoutAlgorithm->MeasureContent(parentLayoutConstraint, AccessibilityManager::RawPtr(layoutWrapper));

    /**
     * @tc.steps: step4. check the size.
     */
    EXPECT_EQ(sizeX, SizeF(0.0f, 20.0f));
}

/**
 * @tc.name: TextLayoutTest008
 * @tc.desc: set baselineOffset and maxsize of Text check height when AdaptTextSize is disable.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextLayoutTest008, TestSize.Level1)
{
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
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

    /**
     * @tc.steps: step2. set textLayoutProperty.
     * baselineOffset: 20_px
     */

    textLayoutProperty->UpdateContent(CREATE_VALUE);
    textLayoutProperty->UpdateBaselineOffset(BASELINE_OFFSET_VALUE);
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.selfIdealSize.SetWidth(-1.0);
    parentLayoutConstraint.maxSize.SetHeight(1.0);
    parentLayoutConstraint.maxSize.SetWidth(1.0);

    /**
     * @tc.steps: step3. create textLayoutAlgorithm.
     */

    auto textLayoutAlgorithm = AceType::MakeRefPtr<TextLayoutAlgorithm>();
    TextStyle textStyle;
    Dimension adaptMinFontSize(DIMENSION, DimensionUnit::PERCENT);
    textStyle.SetAdaptMinFontSize(adaptMinFontSize);
    auto ret = textLayoutAlgorithm->CreateParagraphAndLayout(
        textStyle, "", parentLayoutConstraint, AceType::RawPtr(textFrameNode));
    EXPECT_TRUE(ret);
    auto sizeX =
        textLayoutAlgorithm->MeasureContent(parentLayoutConstraint, AccessibilityManager::RawPtr(layoutWrapper));

    /**
     * @tc.steps: step4. check the size.
     */

    EXPECT_EQ(sizeX->Height(), 1.0);
}

/**
 * @tc.name: ToJsonValue001
 * @tc.desc: Test TextLayoutProperty ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, ToJsonValue001, TestSize.Level1)
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
     * @tc.steps: step2. run ToJsonValue().
     */
    auto json = std::make_unique<JsonValue>();
    textLayoutProperty->ToJsonValue(json, filter);
}

/**
 * @tc.name: ToJsonValue002
 * @tc.desc: Test TextLayoutProperty ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, ToJsonValue002, TestSize.Level1)
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
     * @tc.steps: step2. run ToJsonValue().
     */
    Dimension dim(DIMENSION);
    textLayoutProperty->UpdateAdaptMinFontSize(dim);
    textLayoutProperty->UpdateAdaptMaxFontSize(dim);
    textLayoutProperty->UpdateLetterSpacing(dim);
    textLayoutProperty->UpdateTextBaseline(TextBaseline::IDEOGRAPHIC);
    auto json = std::make_unique<JsonValue>();
    textLayoutProperty->ToJsonValue(json, filter);
}

/**
 * @tc.name: ToJsonValue003
 * @tc.desc: Test TextLayoutProperty ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, ToJsonValue003, TestSize.Level1)
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
     * @tc.steps: step2. run ToJsonValue().
     */
    Dimension dim(DIMENSION);
    textLayoutProperty->UpdateAdaptMinFontSize(dim);
    textLayoutProperty->UpdateAdaptMaxFontSize(dim);
    textLayoutProperty->UpdateLetterSpacing(dim);
    textLayoutProperty->UpdateTextBaseline(TextBaseline::TOP);
    auto json = std::make_unique<JsonValue>();
    textLayoutProperty->ToJsonValue(json, filter);
}

/**
 * @tc.name: ToJsonValue004
 * @tc.desc: Test TextLayoutProperty ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, ToJsonValue004, TestSize.Level1)
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
     * @tc.steps: step2. run ToJsonValue().
     */
    Dimension dim(DIMENSION);
    textLayoutProperty->UpdateAdaptMinFontSize(dim);
    textLayoutProperty->UpdateAdaptMaxFontSize(dim);
    textLayoutProperty->UpdateLetterSpacing(dim);
    textLayoutProperty->UpdateTextBaseline(TextBaseline::BOTTOM);
    auto json = std::make_unique<JsonValue>();
    textLayoutProperty->ToJsonValue(json, filter);
}

/**
 * @tc.name: ToJsonValue005
 * @tc.desc: Test TextLayoutProperty ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, ToJsonValue005, TestSize.Level1)
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
     * @tc.steps: step2. run ToJsonValue().
     */
    Dimension dim(DIMENSION);
    textLayoutProperty->UpdateAdaptMinFontSize(dim);
    textLayoutProperty->UpdateAdaptMaxFontSize(dim);
    textLayoutProperty->UpdateLetterSpacing(dim);
    textLayoutProperty->UpdateTextBaseline(TextBaseline::MIDDLE);
    auto json = std::make_unique<JsonValue>();
    textLayoutProperty->ToJsonValue(json, filter);
}

/**
 * @tc.name: ToJsonValue006
 * @tc.desc: Test TextLayoutProperty ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, ToJsonValue006, TestSize.Level1)
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
     * @tc.steps: step2. run ToJsonValue().
     */
    Dimension dim(DIMENSION);
    textLayoutProperty->UpdateAdaptMinFontSize(dim);
    textLayoutProperty->UpdateAdaptMaxFontSize(dim);
    textLayoutProperty->UpdateLetterSpacing(dim);
    textLayoutProperty->UpdateTextBaseline(TextBaseline::HANGING);
    auto json = std::make_unique<JsonValue>();
    textLayoutProperty->ToJsonValue(json, filter);
}

/**
 * @tc.name: ToJsonValue007
 * @tc.desc: Test textPattern ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, ToJsonValue007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode.
     */
    TextModelNG textModelNG;
    textModelNG.Create("");
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    auto pattern = frameNode->GetPattern<TextPattern>();
    auto json = JsonUtil::Create(true);
    /**
     * @tc.steps: step2. expect default textDetectEnable_ false.
     */
    pattern->SetTextDetectEnable(true);
    pattern->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("enableDataDetector"), "true");
}

/**
 * @tc.name: DidExceedMaxLines001
 * @tc.desc: Test TextLayoutAlgorithm DidExceedMaxLines.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, DidExceedMaxLines001, TestSize.Level1)
{
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, Layout);
    EXPECT_CALL(*paragraph, DidExceedMaxLines).WillOnce(Return(true));
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

    textLayoutProperty->UpdateContent(CREATE_VALUE);
    textLayoutProperty->UpdateBaselineOffset(BASELINE_OFFSET_VALUE);
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;

    /**
     * @tc.steps: step3. create textLayoutAlgorithm.
     */

    auto textLayoutAlgorithm = AceType::MakeRefPtr<TextLayoutAlgorithm>();
    TextStyle textStyle;
    LayoutConstraintF contentConstraint;
    auto ret =
        textLayoutAlgorithm->CreateParagraphAndLayout(textStyle, "", contentConstraint, AceType::RawPtr(textFrameNode));
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
HWTEST_F(TextTestNg, DidExceedMaxLines002, TestSize.Level1)
{
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, DidExceedMaxLines).WillOnce(Return(true));
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

    textLayoutProperty->UpdateContent(CREATE_VALUE);
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
    auto ret =
        textLayoutAlgorithm->CreateParagraphAndLayout(textStyle, "", contentConstraint, AceType::RawPtr(textFrameNode));
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
HWTEST_F(TextTestNg, TextLayoutAlgorithmTest001, TestSize.Level1)
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
    textLayoutProperty->UpdateContent(CREATE_VALUE);
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
HWTEST_F(TextTestNg, TextLayoutAlgorithmTest002, TestSize.Level1)
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
    textLayoutProperty->UpdateContent(CREATE_VALUE);
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
    textLayoutProperty->UpdateTextDecoration(TextDecoration::OVERLINE);
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
    textLayoutAlgorithm->SetPropertyToModifier(textLayoutProperty, contentModifier);
    EXPECT_EQ(contentSize.value().Width(), textLayoutAlgorithm->paragraphManager_->GetMaxWidth());
}

/**
 * @tc.name: TextLayoutAlgorithmTest003
 * @tc.desc: test text_layout_algorithm.cpp:Set textHeightAdaptivePolicy to MIN_FONT_SIZE_FIRST, minFontSize and
 *           fontSize are equal
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextLayoutAlgorithmTest003, TestSize.Level1)
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
    textLayoutProperty->UpdateContent(CREATE_VALUE);
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
HWTEST_F(TextTestNg, TextLayoutAlgorithmTest004, TestSize.Level1)
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
    textLayoutProperty->UpdateContent(CREATE_VALUE);
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
HWTEST_F(TextTestNg, TextLayoutAlgorithmTest005, TestSize.Level1)
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
    textLayoutProperty->UpdateContent(CREATE_VALUE);
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
HWTEST_F(TextTestNg, TextPaintMethodTest001, TestSize.Level1)
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
HWTEST_F(TextTestNg, TextContentModifier001, TestSize.Level1)
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
    TextContentModifier textContentModifier(std::optional<TextStyle>(std::move(textStyle)));
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
    textContentModifier.SetFontSize(ADAPT_FONT_SIZE_VALUE);
    textContentModifier.SetBaselineOffset(BASELINE_OFFSET_VALUE);
    MockPipelineContext::SetUp();
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, ClipRect(_, _, _)).WillRepeatedly(Return());
    DrawingContext context { canvas, CONTEXT_WIDTH_VALUE, CONTEXT_HEIGHT_VALUE };
    textPattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 100 });
    // call onDraw function(textRacing_ = true)
    MarqueeOption option;
    textContentModifier.StartTextRace(option);
    context.width = CONTEXT_LARGE_WIDTH_VALUE;
    textContentModifier.onDraw(context);
    // call onDraw function(textRacing_ = false)
    textContentModifier.StopTextRace();
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
HWTEST_F(TextTestNg, TextContentModifier002, TestSize.Level1)
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
    TextContentModifier textContentModifier(std::optional<TextStyle>(std::move(textStyle)));
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
    textContentModifier.SetFontSize(ADAPT_FONT_SIZE_VALUE);
    textContentModifier.SetBaselineOffset(BASELINE_OFFSET_VALUE);
    MockPipelineContext::SetUp();
    // set textDecorationAnimatable_ true
    textContentModifier.textDecorationAnimatable_ = true;
    textContentModifier.textDecoration_ = TextDecoration::UNDERLINE;
    textContentModifier.SetTextDecoration(TextDecoration::NONE);
    textContentModifier.ModifyTextStyle(textStyle);
    // set textDecorationColorAlpha_ value
    textContentModifier.textDecorationColorAlpha_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(1000.0f);
    textContentModifier.ModifyTextStyle(textStyle);
    // set textDecorationAnimatable_ false
    textContentModifier.SetTextDecoration(TextDecoration::LINE_THROUGH);
    textContentModifier.ModifyTextStyle(textStyle);
    EXPECT_EQ(textContentModifier.fontSizeFloat_->Get(), ADAPT_FONT_SIZE_VALUE.Value());
    EXPECT_EQ(textContentModifier.baselineOffsetFloat_->Get(), BASELINE_OFFSET_VALUE.Value());
    EXPECT_EQ(textStyle.GetFontSize().Value(), textContentModifier.fontSizeFloat_->Get());
}

/**
 * @tc.name: TextLayoutAlgorithmTest006
 * @tc.desc: text_layout_algorithm.cpp:Set TextOverflow to MARQUEE
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextLayoutAlgorithmTest006, TestSize.Level1)
{
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, GetLongestLine).WillOnce(Return(100.0f));
    /**
     * @tc.steps: step1. create textFrameNode.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textFrameNode, geometryNode, textFrameNode->GetLayoutProperty());
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    textPattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 100 });

    /**
     * @tc.steps: step2. set textLayoutProperty.
     */
    textLayoutProperty->UpdateContent(CREATE_VALUE);
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
HWTEST_F(TextTestNg, TextLayoutAlgorithmTest007, TestSize.Level1)
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
    textLayoutProperty->UpdateContent(CREATE_VALUE);
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
HWTEST_F(TextTestNg, TextLayoutAlgorithmTest008, TestSize.Level1)
{
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, PushStyle).Times(2);
    EXPECT_CALL(*paragraph, AddText).Times(2);
    EXPECT_CALL(*paragraph, Layout).Times(2);
    EXPECT_CALL(*paragraph, Build).Times(2);
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
    EXPECT_EQ(
        textLayoutAlgorithm->AdaptMaxTextSize(textStyle, "abc", parentLayoutConstraint, AceType::RawPtr(textFrameNode)),
        true);

    // create paragraph failed
    MockParagraph::enabled_ = false;
    textStyle.SetAdaptMaxFontSize(ADAPT_MAX_FONT_SIZE_VALUE);
    textStyle.SetAdaptMinFontSize(ADAPT_MIN_FONT_SIZE_VALUE);
    EXPECT_EQ(
        textLayoutAlgorithm->AdaptMaxTextSize(textStyle, "abc", parentLayoutConstraint, AceType::RawPtr(textFrameNode)),
        false);
    MockParagraph::enabled_ = true;

    // increase font size
    EXPECT_EQ(
        textLayoutAlgorithm->AdaptMaxTextSize(textStyle, "abc", parentLayoutConstraint, AceType::RawPtr(textFrameNode)),
        true);

    // set NormalizeToPx false
    textStyle.adaptFontSizeStep_.SetUnit(DimensionUnit::CALC);
    EXPECT_EQ(
        textLayoutAlgorithm->AdaptMaxTextSize(textStyle, "abc", parentLayoutConstraint, AceType::RawPtr(textFrameNode)),
        false);
}

/**
 * @tc.name: UpdateSelectOverlayOrCreate001
 * @tc.desc: Test TextPattern UpdateSelectOverlayOrCreate.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, UpdateSelectOverlayOrCreate001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    /**
     * @tc.steps: step2. Construct data and call UpdateSelectOverlayOrCreate
     */
    SelectOverlayInfo selectOverlayInfo;
    selectOverlayInfo.singleLineHeight = NODE_ID;
    textPattern->UpdateSelectOverlayOrCreate(selectOverlayInfo, true);
    EXPECT_EQ(selectOverlayInfo.hitTestMode, HitTestMode::HTMDEFAULT);

    auto root = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto selectOverlayManager = AceType::MakeRefPtr<SelectOverlayManager>(root);
    auto proxy = selectOverlayManager->CreateAndShowSelectOverlay(selectOverlayInfo, nullptr, false);
    textPattern->selectOverlayProxy_ = proxy;
    textPattern->UpdateSelectOverlayOrCreate(selectOverlayInfo, true);
    EXPECT_TRUE(textPattern->selectOverlayProxy_ && !textPattern->selectOverlayProxy_->IsClosed());
}

/**
 * @tc.name: HandleOnSelectAll
 * @tc.desc: Test TextPattern HandleOnSelectAll
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, OnModifyDone003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textPattern.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    /**
     * @tc.steps: step2. Construct data and call HandleOnSelectAll
     */
    textPattern->sourceType_ = SourceType::MOUSE;
    textPattern->HandleOnSelectAll();
    EXPECT_TRUE(textPattern->IsUsingMouse());
}

/**
 * @tc.name: CreateImageSourceInfo001
 * @tc.desc: Test TextPattern HandleOnSelectAll
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, CreateImageSourceInfo001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textPattern.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    /**
     * @tc.steps: step2. Construct data and call CreatImageSourceInfo
     */
    ImageSpanOptions textOptions;
    textPattern->CreateImageSourceInfo(textOptions);
    textOptions.image = "textImage";
    textOptions.bundleName = "textBundleName";
    textOptions.moduleName = "textModuleName";
    textPattern->CreateImageSourceInfo(textOptions);
    EXPECT_TRUE(textOptions.image.has_value());
    EXPECT_TRUE(textOptions.bundleName.has_value());
    EXPECT_TRUE(textOptions.moduleName.has_value());
}

/**
 * @tc.name: create001
 * @tc.desc: Test create with spanstring.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextTestNg_create001, TestSize.Level1)
{
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE);
     /**
     * @tc.steps: step1. Create spanBases
     */
    auto spanStringWithSpans = AceType::MakeRefPtr<SpanString>("01234567891");
    /**
     * @tc.steps: step2. call spanBases
     */
    textModelNG.Create(spanStringWithSpans);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetTextSelectableMode001
 * @tc.desc: Test SetTextSelectableMode by frameNode..
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextTestNg_SetTextSelectableMode001, TestSize.Level1)
{
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<TextLayoutProperty> textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_EQ(textLayoutProperty->GetContentValue(), CREATE_VALUE);

    auto retFont = textModelNG.GetFont(frameNode);
    textModelNG.SetFontSize(ADAPT_ZERO_FONT_SIZE_VALUE);
    EXPECT_EQ(textModelNG.GetFontSize(frameNode), ADAPT_ZERO_FONT_SIZE_VALUE);

    textModelNG.SetTextSelectableMode(frameNode, TextSelectableMode::SELECTABLE_UNFOCUSABLE);
    textModelNG.SetTextSelectableMode(TextSelectableMode::SELECTABLE_UNFOCUSABLE);
    ASSERT_EQ(textModelNG.GetTextSelectableMode(frameNode), TextSelectableMode::SELECTABLE_UNFOCUSABLE);

    textModelNG.SetEllipsisMode(frameNode, EllipsisMode::HEAD);
    textModelNG.SetEllipsisMode(EllipsisMode::HEAD);
    ASSERT_EQ(textModelNG.GetEllipsisMode(frameNode), EllipsisMode::HEAD);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: InitSpanStringController001
 * @tc.desc: Test InitSpanStringController.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextTestNg_InitSpanStringController001, TestSize.Level1)
{
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<TextLayoutProperty> textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_EQ(textLayoutProperty->GetContentValue(), CREATE_VALUE);

    auto spanStringWithSpans = AceType::MakeRefPtr<SpanString>("01234567893421");

    textModelNG.InitSpanStringController(frameNode, spanStringWithSpans);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: InitTextController001
 * @tc.desc: Test InitTextController.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextTestNg_InitTextController001, TestSize.Level1)
{
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<TextLayoutProperty> textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_EQ(textLayoutProperty->GetContentValue(), CREATE_VALUE);

    auto ret = textModelNG.InitTextController(frameNode);
    EXPECT_NE(ret, nullptr);
}

/**
 * @tc.name: SetTextDetectEnable001
 * @tc.desc: Test SetTextDetectEnable.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextTestNg_SetTextDetectEnable001, TestSize.Level1)
{
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<TextLayoutProperty> textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_EQ(textLayoutProperty->GetContentValue(), CREATE_VALUE);

    textModelNG.SetTextDetectEnable(frameNode, true);
    ASSERT_NE(textModelNG.GetTextDetectEnable(frameNode), false);

    auto ret = textModelNG.GetTextController();
    EXPECT_NE(ret, nullptr);

    textModelNG.SetClipEdge(true);
    EXPECT_TRUE(true);

    auto strContent = textModelNG.GetContent(frameNode);
    EXPECT_EQ(strContent, CREATE_VALUE);

    auto retLineHeight = textModelNG.GetLineHeight(frameNode);
    EXPECT_EQ(retLineHeight, 0.0f);

    auto retLineSpacing = textModelNG.GetLineSpacing(frameNode);
    EXPECT_EQ(retLineSpacing, 0.0f);

    auto retDecoration = textModelNG.GetDecoration(frameNode);
    EXPECT_EQ(retDecoration, TextDecoration::NONE);

    auto retTextDecorationColor = textModelNG.GetTextDecorationColor(frameNode);
    EXPECT_EQ(retTextDecorationColor, Color::BLACK);

    auto retTextDecorationStyle = textModelNG.GetTextDecorationStyle(frameNode);
    EXPECT_EQ(retTextDecorationStyle, TextDecorationStyle::SOLID);

    auto retTextCase = textModelNG.GetTextCase(frameNode);
    EXPECT_EQ(retTextCase, TextCase::NORMAL);

    auto retLetterSpacing = textModelNG.GetLetterSpacing(frameNode);
    EXPECT_EQ(retLetterSpacing, ADAPT_ZERO_FONT_SIZE_VALUE);

    auto retMaxLines = textModelNG.GetMaxLines(frameNode);
    EXPECT_NE(retMaxLines, 0.0f);

    auto retTextAlign = textModelNG.GetTextAlign(frameNode);
    EXPECT_EQ(retTextAlign, TextAlign::START);
}
} // namespace OHOS::Ace::NG
