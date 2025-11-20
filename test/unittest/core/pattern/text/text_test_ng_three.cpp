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

class TextTestNgThree : public TextBases {
public:
};

/**
 * @tc.name: TextCreateParagraph001
 * @tc.desc: Test CreateParagraph.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgThree, TextCreateParagraph001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init
     */
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    pattern->selectOverlayProxy_ = nullptr;
    auto rowLayoutAlgorithm = AceType::DynamicCast<TextLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    ASSERT_NE(rowLayoutAlgorithm, nullptr);
    /**
     * @tc.steps: step2. call function.
     */
    pattern->isSensitive_ = true;
    pattern->GetHost()->SetPrivacySensitive(true);
    TextStyle textStyle;
    LayoutConstraintF contentConstraint;
    auto maxSize = MultipleParagraphLayoutAlgorithm::GetMaxMeasureSize(contentConstraint);
    auto ret = rowLayoutAlgorithm->CreateParagraph(textStyle, u"", AceType::RawPtr(frameNode), maxSize.Width());
    EXPECT_EQ(ret, true);
}

/**
 * @tc.name: MeasureContent001
 * @tc.desc: Test MeasureContent.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgThree, MeasureContent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init
     */
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    pattern->selectOverlayProxy_ = nullptr;
    auto rowLayoutAlgorithm = AceType::DynamicCast<TextLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    ASSERT_NE(rowLayoutAlgorithm, nullptr);
    /**
     * @tc.steps: step2. change param and call function.
     */
    LayoutConstraintF contentConstraint;
    rowLayoutAlgorithm->isSpanStringMode_ = true;
    rowLayoutAlgorithm->spanStringHasMaxLines_ = true;
    contentConstraint.maxSize.SetHeight(0.0f);
    auto ret = rowLayoutAlgorithm->MeasureContent(contentConstraint, AceType::RawPtr(frameNode));
    EXPECT_EQ(ret.has_value(), true);
    /**
     * @tc.steps: step3. change param and call function.
     */
    rowLayoutAlgorithm->isSpanStringMode_ = false;
    ret = rowLayoutAlgorithm->MeasureContent(contentConstraint, AceType::RawPtr(frameNode));
    EXPECT_EQ(ret.has_value(), true);
}

/**
 * @tc.name: UpdateParagraphForAISpan001
 * @tc.desc: Test UpdateParagraphForAISpan
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgThree, UpdateParagraphForAISpan001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init.
     */
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    pattern->selectOverlayProxy_ = nullptr;
    auto rowLayoutAlgorithm = AceType::DynamicCast<TextLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    ASSERT_NE(rowLayoutAlgorithm, nullptr);
    TextStyle textStyle;
    ParagraphStyle paraStyle = { .direction = TextDirection::LTR,
        .align = textStyle.GetTextAlign(),
        .maxLines = textStyle.GetMaxLines(),
        .fontLocale = "zh-CN",
        .wordBreak = textStyle.GetWordBreak(),
        .textOverflow = textStyle.GetTextOverflow() };
    RefPtr<Paragraph> paragraph = Paragraph::Create(paraStyle, FontCollection::Current());
    ASSERT_NE(paragraph, nullptr);
    pattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 100 });
    /**
     * @tc.steps: step2. change param and call function.
     */
    std::map<int32_t, AISpan> aiSpanMap;
    AISpan aiSpan0;
    aiSpanMap[0] = aiSpan0;
    ASSERT_NE(pattern->GetDataDetectorAdapter(), nullptr);
    pattern->dataDetectorAdapter_->aiSpanMap_ = aiSpanMap;
    std::u16string textForAI = u"";
    pattern->dataDetectorAdapter_->textForAI_ = textForAI;
    rowLayoutAlgorithm->UpdateParagraphForAISpan(textStyle, AceType::RawPtr(frameNode), paragraph);
    EXPECT_EQ(StringUtils::Str16ToStr8(pattern->dataDetectorAdapter_->textForAI_), StringUtils::Str16ToStr8(textForAI));
    /**
     * @tc.steps: step3. change param and call function.
     */
    AISpan aiSpan1;
    aiSpan1.start = -1;
    aiSpan1.end = 0;
    aiSpan1.content = SPAN_PHONE;
    aiSpan1.type = TextDataDetectType::PHONE_NUMBER;
    aiSpanMap[1] = aiSpan1;
    pattern->dataDetectorAdapter_->aiSpanMap_ = aiSpanMap;
    pattern->dataDetectorAdapter_->textForAI_ = textForAI;
    rowLayoutAlgorithm->UpdateParagraphForAISpan(textStyle, AceType::RawPtr(frameNode), paragraph);
    EXPECT_EQ(StringUtils::Str16ToStr8(pattern->dataDetectorAdapter_->textForAI_), StringUtils::Str16ToStr8(textForAI));
    /**
     * @tc.steps: step4. change param and call function.
     */
    AISpan aiSpan2;
    aiSpan2.start = 2;
    aiSpan2.end = 5;
    aiSpan2.content = SPAN_PHONE;
    aiSpan2.type = TextDataDetectType::PHONE_NUMBER;
    aiSpanMap[2] = aiSpan2;
    pattern->dataDetectorAdapter_->aiSpanMap_ = aiSpanMap;
    textForAI = u"Test1234";
    pattern->dataDetectorAdapter_->textForAI_ = textForAI;
    rowLayoutAlgorithm->UpdateParagraphForAISpan(textStyle, AceType::RawPtr(frameNode), paragraph);
    EXPECT_EQ(StringUtils::Str16ToStr8(pattern->dataDetectorAdapter_->textForAI_), StringUtils::Str16ToStr8(textForAI));
}

/**
 * @tc.name: GrayDisplayAISpan001
 * @tc.desc: Test GrayDisplayAISpan
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgThree, GrayDisplayAISpan001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init.
     */
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
    ASSERT_NE(rowLayoutAlgorithm, nullptr);
    TextStyle textStyle;
    ParagraphStyle paragraphStyle = { .direction = TextDirection::LTR,
        .align = textStyle.GetTextAlign(),
        .maxLines = textStyle.GetMaxLines(),
        .fontLocale = "zh-CN",
        .wordBreak = textStyle.GetWordBreak(),
        .textOverflow = textStyle.GetTextOverflow() };
    RefPtr<Paragraph> paragraph = Paragraph::Create(paragraphStyle, FontCollection::Current());
    ASSERT_NE(paragraph, nullptr);
    pattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 100 });
    /**
     * @tc.steps: step2. change param and call function.
     * spanStart <= dragStart && spanEnd >= dragStart && spanEnd <= dragEnd
    */
    DragSpanPosition dragSpanPosition;
    dragSpanPosition.dragStart = 2;
    dragSpanPosition.dragEnd = 4;
    dragSpanPosition.spanStart = 1;
    dragSpanPosition.spanEnd = 3;
    std::string textForAI = "Test1234";
    auto wTextForAI = StringUtils::Str8ToStr16(textForAI);
    ASSERT_NE(pattern->GetDataDetectorAdapter(), nullptr);
    pattern->dataDetectorAdapter_->textForAI_ = wTextForAI;
    rowLayoutAlgorithm->GrayDisplayAISpan(dragSpanPosition, wTextForAI, textStyle, true, paragraph);
    EXPECT_EQ(StringUtils::Str16ToStr8(pattern->dataDetectorAdapter_->textForAI_), textForAI);
    /**
     * @tc.steps: step3. change param and call function.
     * spanStart >= dragStart && spanEnd <= dragEnd
    */
    dragSpanPosition.dragStart = 1;
    dragSpanPosition.dragEnd = 4;
    dragSpanPosition.spanStart = 2;
    dragSpanPosition.spanEnd = 3;
    textForAI = "Test1234";
    wTextForAI = StringUtils::Str8ToStr16(textForAI);
    pattern->dataDetectorAdapter_->textForAI_ = wTextForAI;
    rowLayoutAlgorithm->GrayDisplayAISpan(dragSpanPosition, wTextForAI, textStyle, true, paragraph);
    EXPECT_EQ(StringUtils::Str16ToStr8(pattern->dataDetectorAdapter_->textForAI_), textForAI);
}

/**
 * @tc.name: GrayDisplayAISpan002
 * @tc.desc: Test GrayDisplayAISpan
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgThree, GrayDisplayAISpan002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init.
     */
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
    ASSERT_NE(rowLayoutAlgorithm, nullptr);
    TextStyle textStyle;
    ParagraphStyle paragraphStyle = { .direction = TextDirection::LTR,
        .align = textStyle.GetTextAlign(),
        .maxLines = textStyle.GetMaxLines(),
        .fontLocale = "zh-CN",
        .wordBreak = textStyle.GetWordBreak(),
        .textOverflow = textStyle.GetTextOverflow() };
    RefPtr<Paragraph> paragraph = Paragraph::Create(paragraphStyle, FontCollection::Current());
    ASSERT_NE(paragraph, nullptr);
    pattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 100 });
    /**
     * @tc.steps: step2. change param and call function.
     * spanStart <= dragStart && spanEnd >= dragEnd
    */
    DragSpanPosition dragSpanPosition;
    dragSpanPosition.dragStart = 2;
    dragSpanPosition.dragEnd = 3;
    dragSpanPosition.spanStart = 1;
    dragSpanPosition.spanEnd = 4;
    std::string textForAI = "Test1234";
    auto wTextForAI = StringUtils::Str8ToStr16(textForAI);
    ASSERT_NE(pattern->GetDataDetectorAdapter(), nullptr);
    pattern->dataDetectorAdapter_->textForAI_ = wTextForAI;
    rowLayoutAlgorithm->GrayDisplayAISpan(dragSpanPosition, wTextForAI, textStyle, true, paragraph);
    EXPECT_EQ(StringUtils::Str16ToStr8(pattern->dataDetectorAdapter_->textForAI_), textForAI);
    /**
     * @tc.steps: step3. change param and call function.
     * default
    */
    dragSpanPosition.dragStart = 1;
    dragSpanPosition.dragEnd = 3;
    dragSpanPosition.spanStart = 2;
    dragSpanPosition.spanEnd = 4;
    textForAI = "Test1234";
    wTextForAI = StringUtils::Str8ToStr16(textForAI);
    pattern->dataDetectorAdapter_->textForAI_ = wTextForAI;
    rowLayoutAlgorithm->GrayDisplayAISpan(dragSpanPosition, wTextForAI, textStyle, true, paragraph);
    EXPECT_EQ(StringUtils::Str16ToStr8(pattern->dataDetectorAdapter_->textForAI_), textForAI);
}

/**
 * @tc.name: GrayDisplayAISpan003
 * @tc.desc: Test GrayDisplayAISpan
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgThree, GrayDisplayAISpan003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init.
     */
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
    ASSERT_NE(rowLayoutAlgorithm, nullptr);
    TextStyle textStyle;
    ParagraphStyle paragraphStyle = { .direction = TextDirection::LTR,
        .align = textStyle.GetTextAlign(),
        .maxLines = textStyle.GetMaxLines(),
        .fontLocale = "zh-CN",
        .wordBreak = textStyle.GetWordBreak(),
        .textOverflow = textStyle.GetTextOverflow() };
    RefPtr<Paragraph> paragraph = Paragraph::Create(paragraphStyle, FontCollection::Current());
    ASSERT_NE(paragraph, nullptr);
    pattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 100 });
    /**
     * @tc.steps: step2. change param and call function.
     * spanStart <= dragStart && spanEnd >= dragEnd
    */
    DragSpanPosition dragSpanPosition;
    dragSpanPosition.dragStart = 2;
    dragSpanPosition.dragEnd = 15;
    dragSpanPosition.spanStart = 1;
    dragSpanPosition.spanEnd = 20;
    std::string textForAI = "Test1234";
    auto wTextForAI = StringUtils::Str8ToStr16(textForAI);
    ASSERT_NE(pattern->GetDataDetectorAdapter(), nullptr);
    pattern->dataDetectorAdapter_->textForAI_ = wTextForAI;
    rowLayoutAlgorithm->GrayDisplayAISpan(dragSpanPosition, wTextForAI, textStyle, true, paragraph);
    EXPECT_EQ(StringUtils::Str16ToStr8(pattern->dataDetectorAdapter_->textForAI_), textForAI);
}

/**
 * @tc.name: BuildTextRaceParagraph001
 * @tc.desc: Test BuildTextRaceParagraph
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgThree, BuildTextRaceParagraph001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init and Create TextLayoutAlgorithm
     */
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
    ASSERT_NE(rowLayoutAlgorithm, nullptr);
    /**
     * @tc.steps: step2. change param and call function.
     */
    LayoutConstraintF contentConstraint;
    contentConstraint.selfIdealSize.width_ = 100.0f;
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<TextLayoutProperty> textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);
    TextStyle textStyle;
    textStyle.adaptTextSize_ = true;
    ParagraphStyle paragraphStyle = { .direction = TextDirection::LTR,
        .align = textStyle.GetTextAlign(),
        .maxLines = textStyle.GetMaxLines(),
        .fontLocale = "zh-CN",
        .wordBreak = textStyle.GetWordBreak(),
        .textOverflow = textStyle.GetTextOverflow() };
    RefPtr<Paragraph> paragraph = Paragraph::Create(paragraphStyle, FontCollection::Current());
    ASSERT_NE(paragraph, nullptr);
    rowLayoutAlgorithm->paragraphManager_->AddParagraph(
        { .paragraph = paragraph, .paragraphStyle = paragraphStyle, .start = 50.0f, .end = 150.0f });
    rowLayoutAlgorithm->BuildTextRaceParagraph(
        textStyle, textLayoutProperty, contentConstraint, AceType::RawPtr(frameNode));
    EXPECT_EQ(rowLayoutAlgorithm->textStyle_, textStyle);
    /**
     * @tc.steps: step3. change param and call function.
     */
    TextStyle textStyle1;
    textStyle1.adaptTextSize_ = true;
    LayoutConstraintF contentConstraint1;
    contentConstraint1.selfIdealSize.width_ = std::nullopt;
    rowLayoutAlgorithm->BuildTextRaceParagraph(
        textStyle1, textLayoutProperty, contentConstraint1, AceType::RawPtr(frameNode));
    EXPECT_EQ(rowLayoutAlgorithm->textStyle_, textStyle1);
    EXPECT_TRUE(textLayoutProperty->GetNeedReCreateParagraphValue(false));
}

/**
 * @tc.name: BeforeCreateLayoutWrapper003
 * @tc.desc: Test TextPattern BeforeCreateLayoutWrapper when paragraph is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgThree, BeforeCreateLayoutWrapper003, TestSize.Level1)
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
        rowLayoutAlgorithm->CreateParagraphAndLayout(textStyle, u"", contentConstraint, AceType::RawPtr(frameNode));
    EXPECT_TRUE(ret);

    DirtySwapConfig config;
    config.skipMeasure = false;
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, AceType::MakeRefPtr<GeometryNode>(), nullptr);
    ASSERT_NE(layoutWrapper, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));
    ret = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: OnHandleMove001
 * @tc.desc: Test TextPattern OnHandleMove when SelectOverlayProxy is not nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgThree, OnHandleMove001, TestSize.Level1)
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
    auto proxy = selectOverlayManager->CreateAndShowSelectOverlay(selectOverlayInfo, nullptr);
    pattern->selectOverlayProxy_ = proxy;
    EXPECT_NE(pattern->selectOverlayProxy_, nullptr);
}

/**
 * @tc.name: TextCreateParagraph002
 * @tc.desc: Correctly create Paragraph only Set content.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgThree, TextCreateParagraph002, TestSize.Level1)
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

    auto textFrameNode = FrameNode::CreateFrameNode(V2::TOAST_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
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

    textLayoutProperty->UpdateContent(CREATE_VALUE_W);

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
HWTEST_F(TextTestNgThree, TextLayoutTest001, TestSize.Level1)
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
     * content: CREATE_VALUE_W
     * width: 100.0f
     * height: 75.0f
     */

    textLayoutProperty->UpdateContent(CREATE_VALUE_W);
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
HWTEST_F(TextTestNgThree, TextLayoutTest002, TestSize.Level1)
{
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
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

    textLayoutProperty->UpdateContent(CREATE_VALUE_W);
    textLayoutProperty->UpdateBaselineOffset(BASELINE_OFFSET_VALUE);
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;

    /**
     * @tc.steps: step3. set theme.
     */
    auto pipeline = PipelineContext::GetCurrentContext();
    auto theme = AceType::MakeRefPtr<MockThemeManager>();
    pipeline->SetThemeManager(theme);
    EXPECT_CALL(*theme, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<TextTheme>()));

    /**
     * @tc.steps: step4. create textLayoutAlgorithm.
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
HWTEST_F(TextTestNgThree, TextLayoutTest003, TestSize.Level1)
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
        textStyle, CREATE_VALUE_W, parentLayoutConstraint, AceType::RawPtr(textFrameNode));

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
HWTEST_F(TextTestNgThree, TextLayoutTest004, TestSize.Level1)
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
        textStyle, CREATE_VALUE_W, parentLayoutConstraint, AceType::RawPtr(textFrameNode));

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
HWTEST_F(TextTestNgThree, TextLayoutTest005, TestSize.Level1)
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
        textStyle, CREATE_VALUE_W, parentLayoutConstraint, AceType::RawPtr(textFrameNode));

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
HWTEST_F(TextTestNgThree, TextLayoutTest006, TestSize.Level1)
{
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, GetMaxWidth).WillRepeatedly(Return(150));
    EXPECT_CALL(*paragraph, GetHeight).WillRepeatedly(Return(50));
    EXPECT_CALL(*paragraph, AddText).Times(1);
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

    textLayoutProperty->UpdateContent(CREATE_VALUE_W);
    textLayoutProperty->UpdateBaselineOffset(BASELINE_OFFSET_VALUE);
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;


    /**
     * @tc.steps: step3. set theme.
     */
    auto pipeline = PipelineContext::GetCurrentContext();
    auto theme = AceType::MakeRefPtr<MockThemeManager>();
    pipeline->SetThemeManager(theme);
    EXPECT_CALL(*theme, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<TextTheme>()));

    /**
     * @tc.steps: step4. create textLayoutAlgorithm.
     */

    auto textLayoutAlgorithm = AceType::MakeRefPtr<TextLayoutAlgorithm>();
    TextStyle textStyle;
    LayoutConstraintF contentConstraint;
    auto ret = textLayoutAlgorithm->CreateParagraphAndLayout(textStyle, u"", contentConstraint,
        AceType::RawPtr(textFrameNode));
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
HWTEST_F(TextTestNgThree, TextLayoutTest007, TestSize.Level1)
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

    textLayoutProperty->UpdateContent(CREATE_VALUE_W);
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
        textStyle, u"", parentLayoutConstraint, AceType::RawPtr(textFrameNode));
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
HWTEST_F(TextTestNgThree, TextLayoutTest008, TestSize.Level1)
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

    textLayoutProperty->UpdateContent(CREATE_VALUE_W);
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
        textStyle, u"", parentLayoutConstraint, AceType::RawPtr(textFrameNode));
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
HWTEST_F(TextTestNgThree, ToJsonValue001, TestSize.Level1)
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
HWTEST_F(TextTestNgThree, ToJsonValue002, TestSize.Level1)
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
HWTEST_F(TextTestNgThree, ToJsonValue003, TestSize.Level1)
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
HWTEST_F(TextTestNgThree, ToJsonValue004, TestSize.Level1)
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
HWTEST_F(TextTestNgThree, ToJsonValue005, TestSize.Level1)
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
HWTEST_F(TextTestNgThree, ToJsonValue006, TestSize.Level1)
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

} // namespace OHOS::Ace::NG