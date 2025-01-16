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

#include "text_base.h"

#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/rosen/mock_canvas.h"

#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/text/span_model_ng.h"
#include "core/components_ng/pattern/text/text_model_ng.h"

namespace OHOS::Ace::NG {

namespace {} // namespace

class TextTestTwoNg : public TextBases {
public:
};

/**
 * @tc.name: TextOverlayModifierTest001
 * @tc.desc: test text_overlay_modifier.cpp.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestTwoNg, TextOverlayModifierTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textOverlayModifier and call text_overlay_modifier.cpp function.
     * @tc.expected: The member variable value of textOverlayModifier is the value set above
     */
    TextOverlayModifier textOverlayModifier;
    OffsetF paintOffset;
    textOverlayModifier.SetPrintOffset(paintOffset);
    textOverlayModifier.SetCursorColor(CURSOR_COLOR);
    textOverlayModifier.SetSelectedColor(SELECTED_COLOR);
    std::vector<RectF> rectList;
    rectList.push_back(RectF(RECT_X_VALUE, RECT_Y_VALUE, RECT_WIDTH_VALUE, RECT_HEIGHT_VALUE));
    textOverlayModifier.SetSelectedRects(rectList);
    // change selectedRects_ and call IsSelectedRectsChanged function
    RectF secondRect(RECT_SECOND_X_VALUE, RECT_Y_VALUE, RECT_WIDTH_VALUE, RECT_HEIGHT_VALUE);
    textOverlayModifier.selectedRects_[0] = secondRect;
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, Save()).WillRepeatedly(Return());
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawRect(_)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, Restore()).WillRepeatedly(Return());
    DrawingContext context { canvas, CONTEXT_WIDTH_VALUE, CONTEXT_HEIGHT_VALUE };
    RectF contentRect;
    textOverlayModifier.SetContentRect(contentRect);
    textOverlayModifier.onDraw(context);
    EXPECT_EQ(textOverlayModifier.paintOffset_->Get(), paintOffset);
    EXPECT_EQ(textOverlayModifier.cursorColor_->Get(), CURSOR_COLOR);
    EXPECT_EQ(textOverlayModifier.selectedColor_->Get(), SELECTED_COLOR);
    EXPECT_EQ(textOverlayModifier.IsSelectedRectsChanged(rectList), true);
    EXPECT_EQ(textOverlayModifier.contentRect_, contentRect);
}

/**
 * @tc.name: TextPaintMethodTest002
 * @tc.desc: test text_paint_method.cpp without setting textOverflow
 * @tc.type: FUNC
 */
HWTEST_F(TextTestTwoNg, TextPaintMethodTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode and textLayoutProperty.
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
     * @tc.steps: step2. create textPaintMethod and update textLayoutProperty.
     */
    auto pattern = textFrameNode->GetPattern<Pattern>();
    ParagraphStyle paragraphStyle;
    RefPtr<Paragraph> paragraph = Paragraph::Create(paragraphStyle, FontCollection::Current());
    RefPtr<TextContentModifier> textContentModifier =
        AceType::MakeRefPtr<TextContentModifier>(std::optional<TextStyle>(TextStyle()));
    RefPtr<TextOverlayModifier> textOverlayModifier = AceType::MakeRefPtr<TextOverlayModifier>();
    TextPaintMethod textPaintMethod(pattern, BASE_LINE_OFFSET_VALUE, textContentModifier, textOverlayModifier);
    textLayoutProperty->UpdateFontSize(ADAPT_FONT_SIZE_VALUE);
    textLayoutProperty->UpdateFontWeight(Ace::FontWeight::W200);
    textLayoutProperty->UpdateTextColor(TEXT_COLOR_VALUE);
    Shadow textShadow;
    textShadow.SetBlurRadius(BLURRADIUS_VALUE);
    textShadow.SetColor(TEXT_COLOR_VALUE);
    textShadow.SetSpreadRadius(SPREADRADIUS_VALUE);
    textShadow.SetOffsetX(ADAPT_OFFSETX_VALUE);
    textShadow.SetOffsetY(ADAPT_OFFSETY_VALUE);
    textLayoutProperty->UpdateTextShadow({ textShadow });
    textLayoutProperty->UpdateTextDecorationColor(TEXT_COLOR_VALUE);
    textLayoutProperty->UpdateTextDecoration(TextDecoration::OVERLINE);
    textLayoutProperty->UpdateBaselineOffset(ADAPT_BASE_LINE_OFFSET_VALUE);

    /**
     * @tc.steps: step3. call UpdateContentModifier,UpdateOverlayModifier and GetOverlayModifier.
     * @tc.expected: The return value of GetOverlayModifier is not empty
     */
    RefPtr<RenderContext> renderContext = RenderContext::Create();
    auto paintProperty = textPattern->CreatePaintProperty();
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, paintProperty);
    textPaintMethod.UpdateContentModifier(AceType::RawPtr(paintWrapper));
    textPaintMethod.UpdateOverlayModifier(AceType::RawPtr(paintWrapper));
    auto OverlayModifier = textPaintMethod.GetOverlayModifier(AceType::RawPtr(paintWrapper));
    ASSERT_NE(OverlayModifier, nullptr);
}

/**
 * @tc.name: TextAccessibilityPropertyGetText001
 * @tc.desc: Test GetText of text.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestTwoNg, TextAccessibilityPropertyGetText001, TestSize.Level1)
{
    TextModelNG textModel;
    textModel.Create(CREATE_VALUE_W);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textAccessibilityProperty = frameNode->GetAccessibilityProperty<TextAccessibilityProperty>();
    ASSERT_NE(textAccessibilityProperty, nullptr);

    auto textLayoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    textLayoutProperty->UpdateContent(CREATE_VALUE_W);
    EXPECT_EQ(textAccessibilityProperty->GetText(), CREATE_VALUE);

    auto spanNode = SpanNode::GetOrCreateSpanNode(ElementRegister::GetInstance()->MakeUniqueId());
    frameNode->AddChild(spanNode);
    textPattern->textForDisplay_ = TEXT_U16CONTENT;
    EXPECT_EQ(textAccessibilityProperty->GetText(), TEXT_CONTENT);
}

/**
 * @tc.name: TextAccessibilityPropertyIsSelected001
 * @tc.desc: Test IsSelected of text.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestTwoNg, TextAccessibilityPropertyIsSelected001, TestSize.Level1)
{
    TextModelNG textModel;
    textModel.Create(CREATE_VALUE_W);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto textAccessibilityProperty = frameNode->GetAccessibilityProperty<TextAccessibilityProperty>();
    ASSERT_NE(textAccessibilityProperty, nullptr);
    EXPECT_FALSE(textAccessibilityProperty->IsSelected());
    textAccessibilityProperty->SetSelected(true);
    EXPECT_TRUE(textAccessibilityProperty->IsSelected());
}

/**
 * @tc.name: TextAccessibilityPropertyGetTextSelectionStart001
 * @tc.desc: Test GetTextSelectionStart of text.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestTwoNg, TextAccessibilityPropertyGetTextSelectionStart001, TestSize.Level1)
{
    TextModelNG textModel;
    textModel.Create(CREATE_VALUE_W);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textAccessibilityProperty = frameNode->GetAccessibilityProperty<TextAccessibilityProperty>();
    ASSERT_NE(textAccessibilityProperty, nullptr);
    EXPECT_EQ(textAccessibilityProperty->GetTextSelectionStart(), TEXT_ERROR);
    textPattern->textSelector_.Update(0, TEXT_SIZE_INT);
    EXPECT_EQ(textAccessibilityProperty->GetTextSelectionStart(), 0);
}

/**
 * @tc.name: TextAccessibilityPropertyGetTextSelectionEnd001
 * @tc.desc: Test GetTextSelectionEnd of text.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestTwoNg, TextAccessibilityPropertyGetTextSelectionEnd001, TestSize.Level1)
{
    TextModelNG textModel;
    textModel.Create(CREATE_VALUE_W);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textAccessibilityProperty = frameNode->GetAccessibilityProperty<TextAccessibilityProperty>();
    ASSERT_NE(textAccessibilityProperty, nullptr);
    EXPECT_EQ(textAccessibilityProperty->GetTextSelectionEnd(), TEXT_ERROR);
    textPattern->textSelector_.Update(0, TEXT_SIZE_INT);
    EXPECT_EQ(textAccessibilityProperty->GetTextSelectionEnd(), TEXT_SIZE_INT);
}

/**
 * @tc.name: TextAccessibilityPropertyGetSupportAction001
 * @tc.desc: Test GetSupportAction of text.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestTwoNg, TextAccessibilityPropertyGetSupportAction001, TestSize.Level1)
{
    TextModelNG textModel;
    textModel.Create(CREATE_VALUE_W);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textAccessibilityProperty = frameNode->GetAccessibilityProperty<TextAccessibilityProperty>();
    ASSERT_NE(textAccessibilityProperty, nullptr);
    auto textLayoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    textLayoutProperty->UpdateCopyOption(CopyOptions::InApp);
    textAccessibilityProperty->ResetSupportAction();
    std::unordered_set<AceAction> supportAceActions = textAccessibilityProperty->GetSupportAction();
    uint64_t actions = 0, expectActions = 0;
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_COPY);
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SET_SELECTION);
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_CLEAR_SELECTION);
    for (auto action : supportAceActions) {
        actions |= 1UL << static_cast<uint32_t>(action);
    }
    EXPECT_EQ(actions, expectActions);
}

/**
 * @tc.name: TextModelNgTest001
 * @tc.desc: test text_model_ng.cpp SetHeightAdaptivePolicy and SetTextShadow
 * @tc.type: FUNC
 */
HWTEST_F(TextTestTwoNg, TextModelNgTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. call SetHeightAdaptivePolicy and SetTextShadow.
     * @tc.expected: The HeightAdaptivePolicyValue of textLayoutProperty is MAX_LINES_FIRST.
     *               The TextShadowValue of textLayoutProperty is textShadow.
     */
    TextModelNG text;
    text.Create(u"text");
    text.SetHeightAdaptivePolicy(TextHeightAdaptivePolicy::MAX_LINES_FIRST);
    Shadow textShadow;
    text.SetTextShadow({ textShadow });
    EXPECT_EQ(textLayoutProperty->GetHeightAdaptivePolicyValue(TextHeightAdaptivePolicy::MAX_LINES_FIRST),
        TextHeightAdaptivePolicy::MAX_LINES_FIRST);
    EXPECT_EQ(*textLayoutProperty->GetTextShadowValue({ textShadow }).begin(), textShadow);
}

/**
 * @tc.name: TextPatternTest001
 * @tc.desc: test text_pattern.h CreateNodePaintMethod function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestTwoNg, TextPatternTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode and textPattern.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. call CreateNodePaintMethod function.
     * @tc.expected: The return value of CreateNodePaintMethod is not empty.
     *               textPattern's textContentModifier_ is not empty.
     *               textPattern's textOverlayModifier_ is not empty.
     */
    auto nodePaintMethod = textPattern->CreateNodePaintMethod();
    ASSERT_NE(nodePaintMethod, nullptr);
    ASSERT_NE(textPattern->contentMod_, nullptr);
    ASSERT_NE(textPattern->overlayMod_, nullptr);
}

/**
 * @tc.name: TextPatternTest002
 * @tc.desc: test text_pattern.h CreateNodePaintMethod function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestTwoNg, TextPatternTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode and textPattern.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. call CreateLayoutProperty function.
     * @tc.expected: The return value of CreateLayoutProperty is not empty.
     */
    RefPtr<LayoutProperty> textLayoutProperty = textPattern->CreateLayoutProperty();
    ASSERT_NE(textLayoutProperty, nullptr);
}

/**
 * @tc.name: TextPatternTest003
 * @tc.desc: test text_pattern.h CreateNodePaintMethod function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestTwoNg, TextPatternTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode and textPattern.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. call CreateLayoutAlgorithm function.
     * @tc.expected: The return value of CreateLayoutAlgorithm is not empty.
     */
    RefPtr<LayoutAlgorithm> textLayoutAlgorithm = textPattern->CreateLayoutAlgorithm();
    ASSERT_NE(textLayoutAlgorithm, nullptr);
}

/**
 * @tc.name: TextPatternTest004
 * @tc.desc: Test the CopyOption value while in Marquee state.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestTwoNg, TextPatternTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode and textPattern.
     */
    auto textFrameNode = FrameNode::CreateFrameNode("", 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. set the TextOverflow value to Marquee.
     */
    auto textLayoutProperty = textFrameNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    textLayoutProperty->UpdateCopyOption(CopyOptions::InApp);
    textLayoutProperty->UpdateTextOverflow(TextOverflow::MARQUEE);

    /**
     * @tc.steps: step3. call OnModifyDone function.
     * @tc.expected: The copyOption_ value is equal to CopyOptions::InApp.
     */
    textPattern->OnModifyDone();
}

/**
 * @tc.name: TextPatternTest005
 * @tc.desc: Test the SetImageSpanNodeList func of TextPattern.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestTwoNg, TextPatternTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode and textPattern.
     */
    auto textFrameNode = FrameNode::CreateFrameNode("", 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Create imageNodeList and add imageNode into imageNodeList.
     */
    std::vector<WeakPtr<FrameNode>> imageNodeList;
    auto imageNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG,
		ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    imageNodeList.emplace_back(AceType::WeakClaim(AceType::RawPtr(imageNode)));

    /**
     * @tc.steps: step3. call SetImageSpanNodeList.
     * @tc.expected: The imageNodeList_ size is equal to 1.
     */
    textPattern->SetImageSpanNodeList(imageNodeList);
    EXPECT_EQ(textPattern->imageNodeList_.size(), 1);
}

/**
 * @tc.name: TextPatternTest006
 * @tc.desc: Test the SetImageSpanNodeList func of TextPattern.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestTwoNg, TextPatternTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode and textPattern.
     */
    auto textFrameNode = FrameNode::CreateFrameNode("", 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Create imageNodeList and add imageNode into imageNodeList.
     */
    std::vector<WeakPtr<FrameNode>> imageNodeLocalList;
    std::vector<WeakPtr<FrameNode>> imageNodeList;
    for (int i = 0; i < 10; i++) {
        auto imageNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG,
			ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<ImagePattern>(); });
        imageNodeList.emplace_back(AceType::WeakClaim(AceType::RawPtr(imageNode)));
        imageNodeLocalList.emplace_back(imageNode);
    }

    /**
     * @tc.steps: step3. call SetImageSpanNodeList.
     * @tc.expected: The imageNodeList_ size is equal to 10.
     */
    textPattern->SetImageSpanNodeList(imageNodeList);
    EXPECT_EQ(textPattern->imageNodeList_.size(), 10);
}

/**
 * @tc.name: TextPatternTest007
 * @tc.desc: Test the SetImageSpanNodeList func of TextPattern.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestTwoNg, TextPatternTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode and textPattern.
     */
    auto textFrameNode = FrameNode::CreateFrameNode("", 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Create imageNodeList and add imageNode into imageNodeList.
     */
    std::vector<WeakPtr<FrameNode>> imageNodeLocalList;
    std::vector<WeakPtr<FrameNode>> imageNodeList;
    for (int i = 0; i < 100; i++) {
        auto imageNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(),
			[]() { return AceType::MakeRefPtr<ImagePattern>(); });
        imageNodeList.emplace_back(AceType::WeakClaim(AceType::RawPtr(imageNode)));
        imageNodeLocalList.emplace_back(imageNode);
    }

    /**
     * @tc.steps: step3. call SetImageSpanNodeList.
     * @tc.expected: The imageNodeList_ size is equal to 100.
     */
    textPattern->SetImageSpanNodeList(imageNodeList);
    EXPECT_EQ(textPattern->imageNodeList_.size(), 100);
}

/**
 * @tc.name: TextPatternTest008
 * @tc.desc: Test the SetImageSpanNodeList func of TextPattern.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestTwoNg, TextPatternTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode and textPattern.
     */
    auto textFrameNode = FrameNode::CreateFrameNode("", 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. call SetImageSpanNodeList.
     * @tc.expected: The imageNodeList_ size is equal to 0.
     */
    EXPECT_EQ(textPattern->imageNodeList_.size(), 0);
}

/**
 * @tc.name: TextPatternTest009
 * @tc.desc: Test the SetImageSpanNodeList func of TextPattern.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestTwoNg, TextPatternTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode and textPattern.
     */
    auto textFrameNode = FrameNode::CreateFrameNode("", 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Create imageNodeList and add imageNode into imageNodeList.
     */
    std::vector<WeakPtr<FrameNode>> imageNodeList;
    imageNodeList.emplace_back(nullptr);

    /**
     * @tc.steps: step3. call SetImageSpanNodeList.
     * @tc.expected: The imageNodeList_ size is equal to 1.
     */
    textPattern->SetImageSpanNodeList(imageNodeList);
    EXPECT_EQ(textPattern->imageNodeList_.size(), 1);
}

/**
 * @tc.name: TextPatternTest010
 * @tc.desc: Test the SetImageSpanNodeList func of TextPattern.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestTwoNg, TextPatternTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode and textPattern.
     */
    auto textFrameNode = FrameNode::CreateFrameNode("", 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Create imageNodeList and add imageNode into imageNodeList.
     */
    std::vector<WeakPtr<FrameNode>> imageNodeList;
    for (int i = 0; i < 10; i++) {
        imageNodeList.emplace_back(nullptr);
    }

    /**
     * @tc.steps: step3. call SetImageSpanNodeList.
     * @tc.expected: The imageNodeList_ size is equal to 10.
     */
    textPattern->SetImageSpanNodeList(imageNodeList);
    EXPECT_EQ(textPattern->imageNodeList_.size(), 10);
}

/**
 * @tc.name: TextPatternTest011
 * @tc.desc: Test the SetImageSpanNodeList func of TextPattern.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestTwoNg, TextPatternTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode and textPattern.
     */
    auto textFrameNode = FrameNode::CreateFrameNode("", 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Create imageNodeList and add imageNode into imageNodeList.
     */
    std::vector<WeakPtr<FrameNode>> imageNodeLocalList;
    std::vector<WeakPtr<FrameNode>> imageNodeList;
    for (int i = 0; i < 100; i++) {
        imageNodeList.emplace_back(nullptr);
    }

    /**
     * @tc.steps: step3. call SetImageSpanNodeList.
     * @tc.expected: The imageNodeList_ size is equal to 100.
     */
    textPattern->SetImageSpanNodeList(imageNodeList);
    EXPECT_EQ(textPattern->imageNodeList_.size(), 100);
}

/**
 * @tc.name: CreateParagraph001
 * @tc.desc: test text_pattern.h CreateNodePaintMethod function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestTwoNg, CreateParagraph001, TestSize.Level1)
{
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, PushStyle);
    EXPECT_CALL(*paragraph, AddText);
    EXPECT_CALL(*paragraph, Build);

    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);

    DirtySwapConfig config;
    config.skipMeasure = false;
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), frameNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    auto rowLayoutAlgorithm = AceType::DynamicCast<TextLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    TextStyle textStyle;
    LayoutConstraintF contentConstraint;
    auto ret = rowLayoutAlgorithm->CreateParagraph(textStyle, u"", AceType::RawPtr(frameNode));
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: Layout001
 * @tc.desc: test text_pattern.h CreateNodePaintMethod function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestTwoNg, Layout001, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);

    DirtySwapConfig config;
    config.skipMeasure = false;
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), frameNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);

    layoutWrapper->children_.push_back(layoutWrapper);
    auto imageSpanNode = FrameNode::GetOrCreateFrameNode(
        V2::IMAGE_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(imageSpanNode, nullptr);
}

/**
 * @tc.name: ApplyIndents001
 * @tc.desc: test text_pattern.h CreateNodePaintMethod function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestTwoNg, ApplyIndents001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);

    DirtySwapConfig config;
    config.skipMeasure = false;
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), frameNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    auto rowLayoutAlgorithm = AceType::DynamicCast<TextLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    TextStyle textStyle;
    LayoutConstraintF contentConstraint;
    auto ret = rowLayoutAlgorithm->CreateParagraph(textStyle, u"", AceType::RawPtr(frameNode));
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: AddChildSpanItem001
 * @tc.desc: test text_pattern.h CreateNodePaintMethod function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestTwoNg, AddChildSpanItem001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);

    DirtySwapConfig config;
    config.skipMeasure = false;
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), frameNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    auto rowLayoutAlgorithm = AceType::DynamicCast<TextLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE_W);
    TextStyle textStyle;
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    pattern->AddChildSpanItem(element);
    auto ret = rowLayoutAlgorithm->CreateParagraph(textStyle, u"", AceType::RawPtr(frameNode));
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: ShowSelectOverlay003
 * @tc.desc: test text_pattern.h ShowSelectOverlay function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestTwoNg, ShowSelectOverlay003, TestSize.Level1)
{
    auto [frameNode, pattern] = Init();
    GestureEvent info;
    info.localLocation_ = Offset(1, 1);
    // copyOption = None
    pattern->HandleLongPress(info);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), -1);

    pattern->copyOption_ = CopyOptions::Distributed;
    pattern->textForDisplay_ = u"test";
    pattern->textSelector_.Update(0, 20);

    pattern->ShowSelectOverlay();
    EXPECT_NE(pattern->textSelector_.GetTextStart(), -1);
    EXPECT_NE(pattern->textSelector_.GetTextEnd(), -1);
}

/**
 * @tc.name: ShowSelectOverlay004
 * @tc.desc: test text_pattern.h ShowSelectOverlay function when menuOptionItems_ is not nullptr
 * @tc.type: FUNC
 */
HWTEST_F(TextTestTwoNg, ShowSelectOverlay004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();
    GestureEvent info;
    info.localLocation_ = Offset(1, 1);
    pattern->HandleLongPress(info);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), -1);
    /**
     * @tc.steps: step2. construct menuOptionItems
     */
    pattern->copyOption_ = CopyOptions::InApp;
    pattern->textForDisplay_ = u"test";
    pattern->textSelector_.Update(0, 20);
    OnCreateMenuCallback onCreateMenuCallback;
    OnMenuItemClickCallback onMenuItemClick;
    pattern->selectOverlay_->OnSelectionMenuOptionsUpdate(std::move(onCreateMenuCallback), std::move(onMenuItemClick));

    /**
     * @tc.steps: step2. call ShowSelectOverlay function
     * @tc.expected: the property of selectInfo is assigned.
     */
    pattern->ShowSelectOverlay();
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), 20);
}

/**
 * @tc.name: IsDraggable001
 * @tc.desc: test text_pattern.h Draggable function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestTwoNg, IsDraggable001, TestSize.Level1)
{
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    std::vector<RectF> rects { RectF(0, 0, 20, 20) };
    EXPECT_CALL(*paragraph, GetRectsForRange(_, _, _)).WillRepeatedly(SetArgReferee<2>(rects));

    auto [host, pattern] = Init();
    pattern->copyOption_ = CopyOptions::Distributed;
    pattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 100 });
    host->draggable_ = true;
    host->eventHub_->SetOnDragStart(
        [](const RefPtr<Ace::DragEvent>&, const std::string&) -> DragDropInfo { return {}; });

    /**
     * @tc.steps: step1. set selected rect to [0, 0] - [20, 20]
     * @tc.expected: return true if the location is in region
     */
    pattern->textSelector_.Update(0, 20);
    EXPECT_TRUE(pattern->IsDraggable(Offset(1, 1)));

    /**
     * @tc.expected: return false if the location is not in region
     */
    EXPECT_FALSE(pattern->IsDraggable(Offset(21, 21)));

    /**
     * @tc.steps: step2. text not selected
     * @tc.expected: return false
     */
    pattern->textSelector_.Update(-1);
    EXPECT_FALSE(pattern->IsDraggable(Offset(1, 1)));
    pattern->pManager_->Reset();
}

/**
 * @tc.name: DragBase001
 * @tc.desc: test text_pattern.h DragBase function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestTwoNg, DragBase001, TestSize.Level1)
{
    auto [frameNode, pattern] = Init();

    // test ResetSelection should reset textSelector
    pattern->CreateHandles();
    pattern->textSelector_.Update(0, 20);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), 20);
    pattern->CloseSelectOverlay();
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), 20);
    pattern->ResetSelection();
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), -1);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), -1);

    // test GetTextBoxes and GetLineHeight
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    pattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 100 });
    std::vector<RectF> rects { RectF(0, 0, 20, 20) };
    EXPECT_CALL(*paragraph, GetRectsForRange(_, _, _)).WillRepeatedly(SetArgReferee<2>(rects));

    pattern->textSelector_.Update(0, 20);
    auto boxes = pattern->GetTextBoxes();
    EXPECT_EQ(boxes.size(), 1);
    EXPECT_EQ(boxes[0].Left(), 0);
    EXPECT_EQ(boxes[0].Right(), 20);

    auto height = pattern->GetLineHeight();
    EXPECT_EQ(height, 20);
    pattern->pManager_->Reset();
}

/**
 * @tc.name: TextDecorationStyleTest001
 * @tc.desc: test text_model_ng.cpp SetTextDecorationStyle
 * @tc.type: FUNC
 */
HWTEST_F(TextTestTwoNg, TextDecorationStyleTest001, TestSize.Level1)
{
    TextModelNG text;
    text.Create(CREATE_VALUE_W);
    text.SetTextDecorationStyle(TextDecorationStyle::DOUBLE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<TextLayoutProperty> textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_EQ(textLayoutProperty->GetTextDecorationStyle(), TextDecorationStyle::DOUBLE);
}

/**
 * @tc.name: TextDecorationStyleTest002
 * @tc.desc: Test TextDecorationStyle of Text will be inheritted by Span
 * @tc.type: FUNC
 */
HWTEST_F(TextTestTwoNg, TextDecorationStyleTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create text FrameNode and set TextDecoration values
     * @tc.expected: Successfully created parent Node
     */
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE_W);
    textModelNG.SetTextDecoration(TextDecoration::LINE_THROUGH);
    textModelNG.SetTextDecorationStyle(TextDecorationStyle::DOUBLE);
    textModelNG.SetFontSize(Dimension(10.0));
    auto textFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());

    /**
     * @tc.steps: step2. create spanNode without setting TextDecoration values
     * @tc.expected: Successfully created spanNode
     */
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE_W);
    spanModelNG.SetFontSize(Dimension(20.0));
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->Finish());

    /**
     * @tc.steps: step3. SpanNode mount to parent
     */
    textFrameNode->AddChild(spanNode);

    TextStyle textStyle;
    auto textLayoutProperty = textFrameNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(textFrameNode, AceType::MakeRefPtr<GeometryNode>(), textLayoutProperty);
    auto textLayoutAlgorithm = AccessibilityManager::MakeRefPtr<TextLayoutAlgorithm>();
    LayoutConstraintF layoutConstraint;
    textLayoutAlgorithm->ConstructTextStyles(layoutConstraint, &layoutWrapper, textStyle);
    ParagraphStyle paragraphStyle;
    RefPtr<Paragraph> paragraph = Paragraph::Create(paragraphStyle, FontCollection::Current());
    ASSERT_NE(paragraph, nullptr);

    auto spanItem = spanNode->spanItem_;
    spanItem->UpdateParagraph(textFrameNode, paragraph, textStyle);
    auto spanTextStyle = spanItem->GetTextStyle().value_or(TextStyle());

    /**
     * @tc.steps: step4. called BeforeCreateLayoutWrapper function to UpdateChildProperty
     * @tc.expected: spanNode inherits parent property
     */
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    textPattern->BeforeCreateLayoutWrapper();
    EXPECT_EQ(spanTextStyle.GetTextDecoration(), TextDecoration::LINE_THROUGH);
    EXPECT_EQ(spanTextStyle.GetTextDecorationStyle(), TextDecorationStyle::DOUBLE);
    EXPECT_EQ(spanTextStyle.GetFontSize(), Dimension(20.0));
}

/**
 * @tc.name: TextDecorationStyleTest003
 * @tc.desc: Test TextDecorationStyle of Text won't override that of Span
 * @tc.type: FUNC
 */
HWTEST_F(TextTestTwoNg, TextDecorationStyleTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create text FrameNode and set TextDecoration values
     * @tc.expected: Successfully created parent Node
     */
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE_W);
    textModelNG.SetTextDecoration(TextDecoration::LINE_THROUGH);
    textModelNG.SetTextDecorationStyle(TextDecorationStyle::DOUBLE);
    auto textFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());

    /**
     * @tc.steps: step2. create spanNode1 and set TextDecoration values
     * @tc.expected: Successfully created spanNode1
     */
    SpanModelNG spanModelNG1;
    spanModelNG1.Create(CREATE_VALUE_W);
    spanModelNG1.SetTextDecoration(TextDecoration::OVERLINE);
    spanModelNG1.SetTextDecorationStyle(TextDecorationStyle::WAVY);
    auto spanNode1 = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->Finish());

    /**
     * @tc.steps: step3. create spanNode2 without setting TextDecoration values
     * @tc.expected: Successfully created spanNode2
     */
    SpanModelNG spanModelNG2;
    spanModelNG2.Create(TEXT_U16CONTENT);
    auto spanNode2 = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->Finish());

    /**
     * @tc.steps: step4. SpanNode mount to parent
     */
    textFrameNode->AddChild(spanNode1);
    textFrameNode->AddChild(spanNode2);

    TextStyle textStyle;
    auto textLayoutProperty = textFrameNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(textFrameNode, AceType::MakeRefPtr<GeometryNode>(), textLayoutProperty);
    auto textLayoutAlgorithm = AccessibilityManager::MakeRefPtr<TextLayoutAlgorithm>();
    LayoutConstraintF layoutConstraint;
    textLayoutAlgorithm->ConstructTextStyles(layoutConstraint, &layoutWrapper, textStyle);
    ParagraphStyle paragraphStyle;
    RefPtr<Paragraph> paragraph = Paragraph::Create(paragraphStyle, FontCollection::Current());
    ASSERT_NE(paragraph, nullptr);

    auto spanItem1 = spanNode1->spanItem_;
    spanItem1->UpdateParagraph(textFrameNode, paragraph, textStyle);
    auto spanTextStyle1 = spanItem1->GetTextStyle().value_or(TextStyle());

    auto spanItem2 = spanNode2->spanItem_;
    spanItem2->UpdateParagraph(textFrameNode, paragraph, textStyle);
    auto spanTextStyle2 = spanItem2->GetTextStyle().value_or(TextStyle());

    /**
     * @tc.steps: step5. called BeforeCreateLayoutWrapper function to UpdateChildProperty
     * @tc.expected: spanNode1 uses own property and spanNode2 inherits parent property
     */
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    textPattern->BeforeCreateLayoutWrapper();
    EXPECT_EQ(spanTextStyle1.GetTextDecoration(), TextDecoration::OVERLINE);
    EXPECT_EQ(spanTextStyle1.GetTextDecorationStyle(), TextDecorationStyle::WAVY);
    EXPECT_EQ(spanTextStyle2.GetTextDecoration(), TextDecoration::LINE_THROUGH);
    EXPECT_EQ(spanTextStyle2.GetTextDecorationStyle(), TextDecorationStyle::DOUBLE);
}

/**
 * @tc.name: TextDecorationToJsonValue001
 * @tc.desc: Test Text Decoration ToJsonValue when values set.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestTwoNg, TextDecorationToJsonValue001, TestSize.Level1)
{
    TextModelNG text;
    text.Create(CREATE_VALUE_W);
    text.SetTextDecoration(TextDecoration::LINE_THROUGH);
    text.SetTextDecorationColor(TEXT_DECORATION_COLOR_VALUE);
    text.SetTextDecorationStyle(TextDecorationStyle::DOUBLE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<TextLayoutProperty> textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);
    auto json = JsonUtil::Create(true);
    textLayoutProperty->ToJsonValue(json, filter);
    EXPECT_TRUE(json->Contains("content"));
    EXPECT_TRUE(json->GetValue("content")->GetString() == CREATE_VALUE);
    EXPECT_TRUE(json->Contains("decoration"));
    std::string decorationStr = json->GetValue("decoration")->GetString();
    auto decorationJson = JsonUtil::ParseJsonString(decorationStr);
    ASSERT_NE(decorationJson, nullptr);
    EXPECT_TRUE(decorationJson->Contains("type"));
    EXPECT_TRUE(decorationJson->GetValue("type")->GetString() ==
                V2::ConvertWrapTextDecorationToStirng(TextDecoration::LINE_THROUGH));
    EXPECT_TRUE(decorationJson->Contains("color"));
    EXPECT_TRUE(decorationJson->GetValue("color")->GetString() == TEXT_COLOR_VALUE.ColorToString());
    EXPECT_TRUE(decorationJson->Contains("style"));
    EXPECT_TRUE(decorationJson->GetValue("style")->GetString() ==
                V2::ConvertWrapTextDecorationStyleToString(TextDecorationStyle::DOUBLE));
}

/**
 * @tc.name: TextDecorationToJsonValue002
 * @tc.desc: Test Text Decoration ToJsonValue when default values.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestTwoNg, TextDecorationToJsonValue002, TestSize.Level1)
{
    TextModelNG text;
    text.Create(CREATE_VALUE_W);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<TextLayoutProperty> textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);
    auto json = JsonUtil::Create(true);
    textLayoutProperty->ToJsonValue(json, filter);
    EXPECT_TRUE(json->Contains("content"));
    EXPECT_TRUE(json->GetValue("content")->GetString() == CREATE_VALUE);
    EXPECT_TRUE(json->Contains("decoration"));
    std::string decorationStr = json->GetValue("decoration")->GetString();
    auto decorationJson = JsonUtil::ParseJsonString(decorationStr);
    ASSERT_NE(decorationJson, nullptr);
    EXPECT_TRUE(decorationJson->Contains("type"));
    EXPECT_TRUE(
        decorationJson->GetValue("type")->GetString() == V2::ConvertWrapTextDecorationToStirng(TextDecoration::NONE));
    EXPECT_TRUE(decorationJson->Contains("color"));
    EXPECT_TRUE(decorationJson->GetValue("color")->GetString() == Color::BLACK.ColorToString());
    EXPECT_TRUE(decorationJson->Contains("style"));
    EXPECT_TRUE(decorationJson->GetValue("style")->GetString() ==
                V2::ConvertWrapTextDecorationStyleToString(TextDecorationStyle::SOLID));
}

/**
 * @tc.name: TextDecorationToJsonValue003
 * @tc.desc: Test Text Decoration ToJsonValue when set multiple textShadows.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestTwoNg, TextDecorationToJsonValue003, TestSize.Level1)
{
    TextModelNG text;
    text.Create(CREATE_VALUE_W);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<TextLayoutProperty> textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);
    Shadow textShadow1 = Shadow();
    Shadow textShadow2 = Shadow();
    textShadow1.SetColor(Color::RED);
    textShadow2.SetColor(Color::WHITE);
    std::vector<Shadow> shadows { textShadow1, textShadow2 };
    textLayoutProperty->UpdateTextShadow(shadows);
    auto json = JsonUtil::Create(true);
    textLayoutProperty->ToJsonValue(json, filter);
    EXPECT_TRUE(json->Contains("textShadow"));
    auto textShadowJson = json->GetValue("textShadow");
    EXPECT_TRUE(textShadowJson->IsArray());
}

/**
 * @tc.name: UpdateChildProperty001
 * @tc.desc: test UpdateChildProperty function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestTwoNg, UpdateChildProperty001, TestSize.Level1)
{
    TestProperty testProperty;
    testProperty.fontSizeValue = std::make_optional(FONT_SIZE_VALUE);
    testProperty.textColorValue = std::make_optional(TEXT_COLOR_VALUE);
    testProperty.italicFontStyleValue = std::make_optional(ITALIC_FONT_STYLE_VALUE);
    testProperty.fontWeightValue = std::make_optional(FONT_WEIGHT_VALUE);
    testProperty.textDecorationValue = std::make_optional(TEXT_DECORATION_VALUE);
    testProperty.textDecorationColorValue = std::make_optional(TEXT_DECORATION_COLOR_VALUE);
    testProperty.textCaseValue = std::make_optional(TEXT_CASE_VALUE);
    testProperty.letterSpacing = std::make_optional(LETTER_SPACING);
    testProperty.lineHeightValue = std::make_optional(LINE_HEIGHT_VALUE);
    testProperty.fontFamilyValue = std::make_optional(FONT_FAMILY_VALUE);
    testProperty.lineSpacingValue = std::make_optional(LINE_SPACING_VALUE);
    /**
     * @tc.steps: step1. create text FrameNode and SpanNode, Update parent FrameNode properties
     * @tc.expected: Successfully created parent Node and child Node
     */
    auto host = CreateTextParagraph(CREATE_VALUE_W, testProperty);
    ASSERT_NE(host, nullptr);
    SpanModelNG spanModelNG;
    spanModelNG.Create(u"span1");
    auto firstChild = ViewStackProcessor::GetInstance()->Finish();
    spanModelNG.Create(u"span2");
    auto secondChild = ViewStackProcessor::GetInstance()->Finish();

    /**
     * @tc.steps: step2. SpanNode mount to parent
     */
    host->AddChild(firstChild);
    host->AddChild(secondChild);

    /**
     * @tc.steps: step3. called BeforeCreateLayoutWrapper function to UpdateChildProperty
     * @tc.expected: child count is not empty, Child inherits parent property
     */
    auto pattern = host->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->BeforeCreateLayoutWrapper();
    EXPECT_EQ(host->GetChildren().size(), 2);

    TextStyle textStyle;
    auto textLayoutProperty = host->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(host, AceType::MakeRefPtr<GeometryNode>(), textLayoutProperty);
    auto textLayoutAlgorithm = AccessibilityManager::MakeRefPtr<TextLayoutAlgorithm>();
    LayoutConstraintF layoutConstraint;
    textLayoutAlgorithm->ConstructTextStyles(layoutConstraint, &layoutWrapper, textStyle);
    ParagraphStyle paragraphStyle;
    RefPtr<Paragraph> paragraph = Paragraph::Create(paragraphStyle, FontCollection::Current());
    ASSERT_NE(paragraph, nullptr);
    for (const auto& child : host->GetChildren()) {
        auto spanNode = AceType::DynamicCast<SpanNode>(child);
        ASSERT_NE(spanNode, nullptr);
        auto spanItem = spanNode->spanItem_;
        spanItem->UpdateParagraph(host, paragraph, textStyle);
        auto spanTextStyle = spanItem->GetTextStyle().value_or(TextStyle());
        EXPECT_EQ(spanTextStyle.GetFontSize(), FONT_SIZE_VALUE);
        EXPECT_EQ(spanTextStyle.GetTextColor(), TEXT_COLOR_VALUE);
        EXPECT_EQ(spanTextStyle.GetFontStyle(), ITALIC_FONT_STYLE_VALUE);
        EXPECT_EQ(spanTextStyle.GetFontWeight(), FONT_WEIGHT_VALUE);
        EXPECT_EQ(spanTextStyle.GetTextDecoration(), TEXT_DECORATION_VALUE);
        EXPECT_EQ(spanTextStyle.GetTextDecorationColor(), TEXT_DECORATION_COLOR_VALUE);
        EXPECT_EQ(spanTextStyle.GetTextCase(), TEXT_CASE_VALUE);
        EXPECT_EQ(spanTextStyle.GetLetterSpacing(), LETTER_SPACING);
        EXPECT_EQ(spanTextStyle.GetLineHeight(), LINE_HEIGHT_VALUE);
        EXPECT_EQ(spanTextStyle.GetFontFamilies(), FONT_FAMILY_VALUE);
        EXPECT_EQ(spanTextStyle.GetLineSpacing(), LINE_SPACING_VALUE);
    }
}

/**
 * @tc.name: UpdateChildProperty002
 * @tc.desc: test UpdateChildProperty function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestTwoNg, UpdateChildProperty002, TestSize.Level1)
{
    TestProperty testProperty;
    /**
     * @tc.steps: step1. create text FrameNode and SpanNode, Update child FrameNode properties
     * @tc.expected: Successfully created parent Node and child Node
     */
    auto host = CreateTextParagraph(CREATE_VALUE_W, testProperty);
    ASSERT_NE(host, nullptr);
    auto firstChild = CreateSpanNodeWithSetDefaultProperty(u"SPANNODE");
    auto secondChild = CreateSpanNodeWithSetDefaultProperty(u"spanNode");

    /**
     * @tc.steps: step2. SpanNode mount to parent
     */
    host->AddChild(firstChild);
    host->AddChild(secondChild);

    /**
     * @tc.steps: step3. called BeforeCreateLayoutWrapper function to UpdateChildProperty
     * @tc.expected: child count is not empty, Child use owner property
     */
    auto pattern = host->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->BeforeCreateLayoutWrapper();
    EXPECT_EQ(host->GetChildren().size(), 2);
    for (const auto& child : host->GetChildren()) {
        auto spanNode = AceType::DynamicCast<SpanNode>(child);
        ASSERT_NE(spanNode, nullptr);
        EXPECT_EQ(spanNode->GetFontSize().value(), FONT_SIZE_VALUE);
        EXPECT_EQ(spanNode->GetTextColor().value(), TEXT_COLOR_VALUE);
        EXPECT_EQ(spanNode->GetItalicFontStyle().value(), ITALIC_FONT_STYLE_VALUE);
        EXPECT_EQ(spanNode->GetFontWeight().value(), FONT_WEIGHT_VALUE);
        EXPECT_EQ(spanNode->GetTextDecoration().value(), TEXT_DECORATION_VALUE);
        EXPECT_EQ(spanNode->GetTextDecorationColor().value(), TEXT_DECORATION_COLOR_VALUE);
        EXPECT_EQ(spanNode->GetTextCase().value(), TEXT_CASE_VALUE);
        EXPECT_EQ(spanNode->GetLetterSpacing().value(), LETTER_SPACING);
        EXPECT_EQ(spanNode->GetLineHeight().value(), LINE_HEIGHT_VALUE);
        EXPECT_EQ(spanNode->GetFontFamily().value(), FONT_FAMILY_VALUE);
    }

    /**
     * @tc.steps: step4. Update parent fontsize property, called BeforeCreateLayoutWrapper again
     * @tc.expected: Child use owner property
     */
    TestUpdateScenario(pattern);
}

/**
 * @tc.name: InitSurfaceChangedTest001
 * @tc.desc: test InitSurfaceChangedCallback function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestTwoNg, InitSurfaceChangedTest001, TestSize.Level1)
{
    TestProperty testProperty;
    /**
     * @tc.steps: step1. create text FrameNode and SpanNode, Update child FrameNode properties
     * @tc.expected: Successfully created parent Node and child Node
     */
    auto host = CreateTextParagraph(CREATE_VALUE_W, testProperty);
    ASSERT_NE(host, nullptr);
    /**
     * @tc.steps: step2. get text pattern called InitSurfaceChangedCallback function.
     * @tc.expected: HasSurfaceChangedCallback return true.
     */
    auto pattern = host->GetPattern<TextPattern>();
    pattern->InitSurfaceChangedCallback();
    EXPECT_TRUE(pattern->HasSurfaceChangedCallback());
}

/**
 * @tc.name: HandleClickEvent001
 * @tc.desc: test test_pattern.h HandleClickEvent function with valid textSelector
 * @tc.type: FUNC
 */
HWTEST_F(TextTestTwoNg, HandleClickEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();
    pattern->textSelector_.Update(0, 20);

    /**
     * @tc.steps: step2. create GestureEvent and call HandleClickEvent function
     * @tc.expected: selectOverlay is closed
     */
    GestureEvent info;
    info.localLocation_ = Offset(0, 0);
    pattern->HandleClickEvent(info);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), -1);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), -1);
}

/**
 * @tc.name: HandleClickEvent002
 * @tc.desc: test test_pattern.h HandleClickEvent function when spanItemChildren is not nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestTwoNg, HandleClickEvent002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();

    /**
     * @tc.steps: step2. construct spanItemChildren
     */
    std::list<RefPtr<SpanItem>> spanItemChildren;
    auto spanItemChild1 = AceType::MakeRefPtr<SpanItem>();
    spanItemChildren.emplace_back(spanItemChild1);
    pattern->spans_ = spanItemChildren;

    /**
     * @tc.steps: step3. create paragraph
     */
    ParagraphStyle paragraphStyle;
    RefPtr<Paragraph> paragraph = Paragraph::Create(paragraphStyle, FontCollection::Current());
    ASSERT_NE(paragraph, nullptr);
    pattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 100 });

    /**
     * @tc.steps: step4. create GestureEvent and call HandleClickEvent function with invalid textSelector
     * @tc.expected: function run rightly
     */
    pattern->textSelector_.Update(-2, -2);
    GestureEvent info;
    info.localLocation_ = Offset(0, 0);
    pattern->HandleClickEvent(info);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), -2);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), -2);
    pattern->pManager_->Reset();
}

/**
 * @tc.name: HandleMouseEvent001
 * @tc.desc: test test_pattern.h HandleMouseEvent function when copyOption is none
 * @tc.type: FUNC
 */
HWTEST_F(TextTestTwoNg, HandleMouseEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();

    /**
     * @tc.steps: step2.call OnVisibleChange function
     * @tc.expected: selectOverlay is closed
     */
    pattern->CreateHandles();
    pattern->textSelector_.Update(0, 20);
    pattern->OnVisibleChange(false);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), -1);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), -1);

    /**
     * @tc.steps: step3. create MouseEvent and call HandleMouseEvent function when copyOption is none
     * @tc.expected: selectOverlay is closed
     */
    MouseInfo info;
    info.localLocation_ = Offset(1, 1);
    pattern->copyOption_ = copyOption;
    pattern->HandleMouseEvent(info);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), -1);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), -1);
}

/**
 * @tc.name: HandleMouseEvent002
 * @tc.desc: test test_pattern.h HandleMouseEvent function when copyOption is not none
 * @tc.type: FUNC
 */
HWTEST_F(TextTestTwoNg, HandleMouseEvent002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();
    pattern->textForDisplay_ = u"test";
    pattern->textSelector_.Update(0, 3);
    pattern->copyOption_ = CopyOptions::InApp;

    /**
     * @tc.steps: step2. create paragraph
     */
    ParagraphStyle paragraphStyle;
    RefPtr<Paragraph> paragraph = Paragraph::Create(paragraphStyle, FontCollection::Current());
    ASSERT_NE(paragraph, nullptr);
    pattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 100 });

    /**
     * @tc.steps: step3. create MouseInfo and call HandleMouseEvent function
     * @tc.expected: selectOverlay is not closed
     */
    MouseInfo info;
    info.localLocation_ = Offset(2, 2);
    info.button_ = MouseButton::RIGHT_BUTTON;
    info.action_ = MouseAction::PRESS;
    pattern->HandleMouseEvent(info);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), 3);
    pattern->pManager_->Reset();
}

/**
 * @tc.name: HandleMouseEvent003
 * @tc.desc: test test_pattern.h HandleMouseEvent function when copyOption is not none
 * @tc.type: FUNC
 */
HWTEST_F(TextTestTwoNg, HandleMouseEvent003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();
    pattern->textForDisplay_ = u"test";
    pattern->textSelector_.Update(0, 3);
    pattern->copyOption_ = CopyOptions::InApp;

    /**
     * @tc.steps: step2. create paragraph
     */
    ParagraphStyle paragraphStyle;
    RefPtr<Paragraph> paragraph = Paragraph::Create(paragraphStyle, FontCollection::Current());
    ASSERT_NE(paragraph, nullptr);
    pattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 0 });

    /**
     * @tc.steps: step3. create MouseInfo and call HandleMouseEvent function
     * @tc.expected: selectOverlay is not closed
     */
    MouseInfo info;
    // none none
    pattern->textSelector_.Update(0, 3);
    info.button_ = MouseButton::NONE_BUTTON;
    info.action_ = MouseAction::NONE;
    pattern->HandleMouseEvent(info);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), 3);

    // left none
    pattern->textSelector_.Update(0, 3);
    info.localLocation_ = Offset(2, 2);
    info.button_ = MouseButton::LEFT_BUTTON;
    info.action_ = MouseAction::NONE;
    pattern->HandleMouseEvent(info);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), 3);

    // right none
    pattern->textSelector_.Update(0, 3);
    info.button_ = MouseButton::RIGHT_BUTTON;
    info.action_ = MouseAction::NONE;
    pattern->HandleMouseEvent(info);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), 3);

    // left press
    pattern->textSelector_.Update(0, 3);
    info.button_ = MouseButton::LEFT_BUTTON;
    info.action_ = MouseAction::PRESS;
    pattern->HandleMouseEvent(info);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), 0);

    // left move
    pattern->textSelector_.Update(0, 3);
    info.button_ = MouseButton::LEFT_BUTTON;
    info.action_ = MouseAction::MOVE;
    pattern->blockPress_ = true;
    pattern->HandleMouseEvent(info);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), 3);

    pattern->textSelector_.Update(0, 3);
    pattern->blockPress_ = false;
    pattern->HandleMouseEvent(info);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), 0);

    // left RELEASE
    pattern->textSelector_.Update(0, 3);
    info.button_ = MouseButton::LEFT_BUTTON;
    info.action_ = MouseAction::RELEASE;
    pattern->blockPress_ = true;
    pattern->HandleMouseEvent(info);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), 3);

    pattern->textSelector_.Update(0, 3);
    pattern->blockPress_ = false;
    pattern->HandleMouseEvent(info);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), 3);
    pattern->pManager_->Reset();
}

/**
 * @tc.name: HandleMouseEvent004
 * @tc.desc: test test_pattern.h HandleMouseEvent function when isDoubleClick_ is true
 * @tc.type: FUNC
 */
HWTEST_F(TextTestTwoNg, HandleMouseEvent004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();
    pattern->textForDisplay_ = u"test";
    pattern->textSelector_.Update(0, 3);
    pattern->copyOption_ = CopyOptions::InApp;

    /**
     * @tc.steps: step2. create paragraph
     */
    ParagraphStyle paragraphStyle;
    RefPtr<Paragraph> paragraph = Paragraph::Create(paragraphStyle, FontCollection::Current());
    ASSERT_NE(paragraph, nullptr);
    pattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 100 });

    /**
     * @tc.steps: step3. create MouseInfo and call HandleMouseEvent function
     * @tc.expected: isDoubleClick_ is false
     */
    MouseInfo info;
    // left RELEASE
    info.button_ = MouseButton::LEFT_BUTTON;
    info.action_ = MouseAction::RELEASE;
    pattern->blockPress_ = true;
    pattern->isDoubleClick_ = true;
    pattern->HandleMouseEvent(info);
    EXPECT_FALSE(pattern->isDoubleClick_);
    pattern->pManager_->Reset();
}

/**
 * @tc.name: HandleMouseEvent005
 * @tc.desc: test test_pattern.h HandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextTestTwoNg, HandleMouseEvent005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern, InitMouseEvent.
     */
    TextModelNG textModelNG;
    textModelNG.Create(u"1234567890");
    textModelNG.SetCopyOption(CopyOptions::InApp);
    textModelNG.SetTextDetectEnable(true);
    auto host = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    auto pattern = host->GetPattern<TextPattern>();
    auto inputHub = host->GetEventHub<EventHub>()->GetOrCreateInputEventHub();
    inputHub->mouseEventActuator_->inputEvents_.clear();
    pattern->mouseEventInitialized_ = false;
    pattern->InitMouseEvent();
    auto mouseEvent = inputHub->mouseEventActuator_->inputEvents_.back();

    AISpan aiSpan1;
    aiSpan1.start = AI_SPAN_START;
    aiSpan1.end = AI_SPAN_END;
    aiSpan1.content = SPAN_PHONE;
    aiSpan1.type = TextDataDetectType::PHONE_NUMBER;
    AISpan aiSpan2;
    aiSpan2.start = AI_SPAN_START_II;
    aiSpan2.end = AI_SPAN_END_II;
    aiSpan2.content = SPAN_URL;
    aiSpan2.type = TextDataDetectType::URL;
    pattern->dataDetectorAdapter_->aiSpanMap_[AI_SPAN_START] = aiSpan1;
    pattern->dataDetectorAdapter_->aiSpanMap_[AI_SPAN_START_II] = aiSpan2;
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    std::vector<RectF> rects { RectF(0, 0, 40, 40) };
    EXPECT_CALL(*paragraph, GetRectsForRange(_, _, _)).WillRepeatedly(SetArgReferee<2>(rects));
    pattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 100 });
    pattern->CreateHandles();
    pattern->textSelector_.Update(0, 20);

    /**
     * @tc.steps: step2. test text_pattern.h HandleMouseRightButton function.
     * @tc.expect: MouseInfo localLocation is in GetRectsForRange region, expect MouseRightButton release event
     *     captured by AISpan.
     */
    MouseInfo info;
    info.button_ = MouseButton::LEFT_BUTTON;
    info.action_ = MouseAction::PRESS;
    (*mouseEvent)(info);
    info.SetLocalLocation(Offset(5.f, 5.f));
    info.button_ = MouseButton::RIGHT_BUTTON;
    info.action_ = MouseAction::RELEASE;
    (*mouseEvent)(info);
    EXPECT_TRUE(pattern->dataDetectorAdapter_->hasClickedAISpan_);

    /**
     * @tc.steps: step3. test text_pattern.h HandleMouseRightButton function.
     * @tc.expect: MouseInfo localLocation is not in GetRectsForRange region.
     */
    pattern->dataDetectorAdapter_->hasClickedAISpan_ = false;
    info.SetLocalLocation(Offset(60.f, 60.f));
    info.button_ = MouseButton::RIGHT_BUTTON;
    info.action_ = MouseAction::RELEASE;
    (*mouseEvent)(info);
    EXPECT_TRUE(!pattern->dataDetectorAdapter_->hasClickedAISpan_);
    EXPECT_EQ(pattern->textResponseType_, TextResponseType::RIGHT_CLICK);
    EXPECT_EQ(pattern->selectedType_, TextSpanType::TEXT);
    pattern->pManager_->Reset();
}

/**
 * @tc.name: HandleMouseEvent006
 * @tc.desc: test test_pattern.h HandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextTestTwoNg, HandleMouseEvent006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern, add child imageSpanNode.
     */
    SuppressMockParagraph();
    TextModelNG textModelNG;
    textModelNG.Create(u"1234567890");
    textModelNG.SetCopyOption(CopyOptions::InApp);
    textModelNG.SetTextDetectEnable(true);
    auto host = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto pattern = host->GetPattern<TextPattern>();
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    std::vector<RectF> rects { RectF(0, 0, 40, 40) };
    EXPECT_CALL(*paragraph, GetRectsForRange(_, _, _)).WillRepeatedly(SetArgReferee<2>(rects));
    ImageSpanNodeProperty firstProperty { .imageSrc = std::make_optional("image") };
    auto imageSpanNode = CreateImageSpanNode(firstProperty);
    host->AddChild(imageSpanNode);
    imageSpanNode->SetParent(host);
    ImageSpanNodeProperty secondProperty { .pixelMap = std::make_optional(PixelMap::CreatePixelMap(nullptr)),
        .imageFit = std::make_optional(ImageFit::FILL) };
    imageSpanNode = CreateImageSpanNode(secondProperty);
    host->AddChild(imageSpanNode);
    imageSpanNode->SetParent(host);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    LayoutConstraintF layoutConstraintF;
    frameNode->Measure(layoutConstraintF);
    pattern->CreateHandles();

    /**
     * @tc.steps: step2. test text_pattern.h HandleMouseRightButton function.
     * @tc.expect: expect selectedType_ IMAGE when mouse release offset not in textContentRect region.
     */
    pattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 30 });
    auto inputHub = host->GetEventHub<EventHub>()->GetOrCreateInputEventHub();
    inputHub->mouseEventActuator_->inputEvents_.clear();
    pattern->mouseEventInitialized_ = false;
    pattern->InitMouseEvent();
    auto mouseEvent = inputHub->mouseEventActuator_->inputEvents_.back();
    MouseInfo info;
    info.button_ = MouseButton::LEFT_BUTTON;
    info.action_ = MouseAction::PRESS;
    (*mouseEvent)(info);
    info.SetLocalLocation(Offset(40.f, 40.f));
    info.button_ = MouseButton::RIGHT_BUTTON;
    info.action_ = MouseAction::RELEASE;
    pattern->contentRect_ = { 30, 30, 20, 20 };
    (*mouseEvent)(info);
    EXPECT_EQ(pattern->textResponseType_, TextResponseType::RIGHT_CLICK);
    EXPECT_EQ(pattern->selectedType_, TextSpanType::IMAGE);
    pattern->pManager_->Reset();
}

/**
 * @tc.name: HandleOnCopy001
 * @tc.desc: test test_pattern.h HandleOnCopy function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestTwoNg, HandleOnCopy001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();

    /**
     * @tc.steps: step2. call HandleOnCopy function when textSelector is valid and textStart is equal to textEnd
     * @tc.steps: step3. call HandleOnCopy function when textSelector is not valid and textStart < 0
     * @tc.expected: selectOverlay is closed
     */
    std::vector<std::vector<int32_t>> params = { { 2, 2 }, { 1, 20 } };
    for (int turn = 0; turn < params.size(); turn++) {
        pattern->textSelector_.Update(params[turn][0], params[turn][1]);
        pattern->HandleOnCopy();
        if (turn == 0) {
            EXPECT_EQ(pattern->textSelector_.GetTextStart(), -1);
            EXPECT_EQ(pattern->textSelector_.GetTextEnd(), -1);
        } else {
            EXPECT_EQ(pattern->textSelector_.GetTextStart(), 1);
            EXPECT_EQ(pattern->textSelector_.GetTextEnd(), 20);
        }
    }
}

/**
 * @tc.name: HandleOnCopy002
 * @tc.desc: test test_pattern.h HandleOnCopy function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestTwoNg, HandleOnCopy002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();

    /**
     * @tc.steps: step2. call HandleOnCopy function with valid textSelector and copyOption
     * @tc.expected: selectOverlay is closed
     */
    pattern->textSelector_.Update(0, 6);
    pattern->textForDisplay_ = u"TestHandleOnCopy";
    pattern->copyOption_ = CopyOptions::InApp;
    pattern->HandleOnCopy();
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), 6);
}

/**
 * @tc.name: HandleLongPress001
 * @tc.desc: test text_pattern.h HandleLongPress function when IsDraggable is false
 * @tc.type: FUNC
 */
HWTEST_F(TextTestTwoNg, HandleLongPress001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();
    frameNode->draggable_ = false;
    pattern->copyOption_ = CopyOptions::InApp;
    pattern->textSelector_.Update(0, 3);
    pattern->textForDisplay_ = TEXT_U16CONTENT;
    GestureEvent info;
    info.localLocation_ = Offset(1, 1);
    EXPECT_FALSE(pattern->IsDraggable(info.GetLocalLocation()));

    /**
     * @tc.steps: step2. call HandleLongPress function
     * @tc.expected: The function exits normally
     */
    pattern->HandleLongPress(info);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), 1);
}

/**
 * @tc.name: HandleLongPress002
 * @tc.desc: test text_pattern.h HandleLongPress function when IsDraggable is true
 * @tc.type: FUNC
 */
HWTEST_F(TextTestTwoNg, HandleLongPress002, TestSize.Level1)
{
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, ComputeOffsetForCaretDownstream).WillRepeatedly(Return(true));
    EXPECT_CALL(*paragraph, ComputeOffsetForCaretUpstream).WillRepeatedly(Return(true));
    EXPECT_CALL(*paragraph, GetWordBoundary).WillRepeatedly(Return(false));
    std::vector<RectF> rects { RectF(0, 0, 20, 20) };
    EXPECT_CALL(*paragraph, GetRectsForRange(_, _, _)).Times(2).WillRepeatedly(SetArgReferee<2>(rects));
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();

    frameNode->draggable_ = true;
    frameNode->eventHub_->SetOnDragStart(
        [](const RefPtr<Ace::DragEvent>&, const std::string&) -> DragDropInfo { return {}; });
    pattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 100 });
    pattern->copyOption_ = CopyOptions::InApp;
    pattern->textSelector_.Update(0, 3);
    pattern->textForDisplay_ = TEXT_U16CONTENT;
    GestureEvent info;
    info.localLocation_ = Offset(1, 1);
    /**
     * @tc.steps: step2. call HandleLongPress function
     * @tc.expected: The function exits normally
     */
    pattern->HandleLongPress(info);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), 3);
    pattern->pManager_->Reset();
}

/**
 * @tc.name: HandleOnSelectAll001
 * @tc.desc: Test TextPattern HandleOnSelectAll when selectOverlayProxy is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestTwoNg, HandleOnSelectAll001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();
    pattern->textForDisplay_ = u"TestHandleOnSelectAll";
    pattern->selectOverlayProxy_ = nullptr;

    /**
     * @tc.steps: step2. create paragraph
     */
    ParagraphStyle paragraphStyle;
    RefPtr<Paragraph> paragraph = Paragraph::Create(paragraphStyle, FontCollection::Current());
    ASSERT_NE(paragraph, nullptr);
    pattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 100 });

    /**
     * @tc.steps: step3. call HandleOnSelectAll
     * @tc.expected:The function exits normally
     */
    pattern->HandleOnSelectAll();
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), pattern->textForDisplay_.length());
    pattern->pManager_->Reset();
}

/**
 * @tc.name: HandleOnSelectAll002
 * @tc.desc: Test TextPattern HandleOnSelectAll when selectOverlayProxy is not nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestTwoNg, HandleOnSelectAll002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();
    /**
     * @tc.steps: step2. construct a SelectOverlayManager and rootNode
     */
    SelectOverlayInfo selectOverlayInfo;
    selectOverlayInfo.singleLineHeight = NODE_ID;
    auto root = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto selectOverlayManager = AceType::MakeRefPtr<SelectOverlayManager>(root);

    /**
     * @tc.steps: step3. call CreateAndShowSelectOverlay
     * @tc.expected: return the proxy which has the right SelectOverlayId
     */
    auto proxy = selectOverlayManager->CreateAndShowSelectOverlay(selectOverlayInfo, nullptr, false);
    pattern->selectOverlayProxy_ = proxy;
    pattern->textForDisplay_ = u"TestHandleOnSelectAll";

    /**
     * @tc.steps: step4. call HandleOnSelectAll
     * @tc.expected:textSelector updates successfully
     */
    pattern->HandleOnSelectAll();
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), 21);

    /**
     * @tc.steps: step5. call CloseSelectOverlay
     * @tc.expected: Related function is called
     */
    pattern->CloseSelectOverlay();
    EXPECT_TRUE(pattern->selectOverlayProxy_->IsClosed());
}

/**
 * @tc.name: PerformActionTest001
 * @tc.desc: Text Accessibility PerformAction test Select ClearSelection and Copy.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestTwoNg, PerformActionTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create text, get text frameNode and pattern, set callback function.
     * @tc.expected: FrameNode and pattern is not null, related function is called.
     */
    MockPipelineContext::GetCurrent()->rootNode_ =
        FrameNode::CreateFrameNodeWithTree(V2::ROOT_ETS_TAG, 0, AceType::MakeRefPtr<RootPattern>());
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    textLayoutProperty->UpdateCopyOption(CopyOptions::None);
    textPattern->SetAccessibilityAction();

    /**
     * @tc.steps: step2. Get text accessibilityProperty to call callback function.
     * @tc.expected: Related function is called.
     */
    auto textAccessibilityProperty = frameNode->GetAccessibilityProperty<TextAccessibilityProperty>();
    ASSERT_NE(textAccessibilityProperty, nullptr);

    /**
     * @tc.steps: step3. When text CopyOptions is None, call the callback function in textAccessibilityProperty.
     * @tc.expected: Related function is called.
     */
    EXPECT_TRUE(textAccessibilityProperty->ActActionSetSelection(1, TEXT_SIZE_INT));
    EXPECT_TRUE(textAccessibilityProperty->ActActionClearSelection());
    EXPECT_TRUE(textAccessibilityProperty->ActActionCopy());

    /**
     * @tc.steps: step4. When text CopyOptions is InApp, call the callback function in textAccessibilityProperty.
     * @tc.expected: Related function is called.
     */
    textLayoutProperty->UpdateCopyOption(CopyOptions::InApp);
    EXPECT_TRUE(textAccessibilityProperty->ActActionSetSelection(-1, -1));
    EXPECT_TRUE(textAccessibilityProperty->ActActionSetSelection(1, TEXT_SIZE_INT));
    EXPECT_TRUE(textAccessibilityProperty->ActActionClearSelection());
    EXPECT_TRUE(textAccessibilityProperty->ActActionCopy());
}

/**
 * @tc.name: TextSelectorTest001
 * @tc.desc: test Update function in TextSelector
 * @tc.type: FUNC
 */
HWTEST_F(TextTestTwoNg, TextSelectorTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Text.
     */
    TextModelNG textModel;
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. set callback function.
     */
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    textLayoutProperty->UpdateCopyOption(CopyOptions::InApp);
    textPattern->OnModifyDone();

    /**
     * @tc.steps: step3. call callback function.
     * @tc.expected: textSelector_ update successfully.
     */
    textPattern->textSelector_.Update(0);
    EXPECT_EQ(textPattern->textSelector_.baseOffset, 0);

    textPattern->textSelector_.Update(0, TEXT_SIZE_INT);
    EXPECT_EQ(textPattern->textSelector_.baseOffset, 0);
    EXPECT_EQ(textPattern->textSelector_.destinationOffset, TEXT_SIZE_INT);
}

/**
 * @tc.name: TextPaintMethodTest003
 * @tc.desc: test text_paint_method.cpp UpdateContentModifier function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestTwoNg, TextPaintMethodTest003, TestSize.Level1)
{
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    std::vector<RectF> rects { RectF(0, 0, 20, 20) };
    EXPECT_CALL(*paragraph, GetRectsForRange(_, _, _)).WillRepeatedly(SetArgReferee<2>(rects));
    /**
     * @tc.steps: step1. create textFrameNode and geometryNode.
     */
    auto [host, pattern] = Init();
    pattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 100 });
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto renderContext = host->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto paintProperty = pattern->CreatePaintProperty();
    ASSERT_NE(paintProperty, nullptr);

    /**
     * @tc.steps: step2. set textForDisplay_ to EMPTY_TEXT.
     */
    pattern->textForDisplay_ = u"";

    /**
     * @tc.steps: step3. push UNKNOWN_REASON and PLACEHOLDER to reasons.
     *                   set obscured of renderContext to reasons.
     */
    std::vector<ObscuredReasons> reasons;
    reasons.push_back((ObscuredReasons)UNKNOWN_REASON);
    reasons.push_back(ObscuredReasons::PLACEHOLDER);
    renderContext->UpdateObscured(reasons);

    /**
     * @tc.steps: step4. create textPaintMethod and call UpdateContentModifier function.
     * @tc.expected: The drawObscuredRects_ of textContentModifier is empty.
     */
    RefPtr<TextContentModifier> textContentModifier =
        AceType::MakeRefPtr<TextContentModifier>(std::optional<TextStyle>(TextStyle()));
    RefPtr<TextOverlayModifier> textOverlayModifier = AceType::MakeRefPtr<TextOverlayModifier>();
    TextPaintMethod textPaintMethod(pattern, BASE_LINE_OFFSET_VALUE, textContentModifier, textOverlayModifier);
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, paintProperty);
    textPaintMethod.UpdateContentModifier(AceType::RawPtr(paintWrapper));
    EXPECT_EQ(textContentModifier->drawObscuredRects_, std::vector<RectF>());

    /**
     * @tc.steps: step5. set textForDisplay_ to CREATE_VALUE.
     */
    pattern->textForDisplay_ = CREATE_VALUE_W;

    /**
     * @tc.steps: step6. call UpdateContentModifier function.
     * @tc.expected: The drawObscuredRects_ of textContentModifier is not empty.
     */
    renderContext = host->GetRenderContext();
    paintProperty = pattern->CreatePaintProperty();
    paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, paintProperty);
    TextPaintMethod textPaintMethod1(pattern, BASE_LINE_OFFSET_VALUE, textContentModifier, textOverlayModifier);
    textPaintMethod1.UpdateContentModifier(AceType::RawPtr(paintWrapper));
    EXPECT_NE(textContentModifier->drawObscuredRects_, std::vector<RectF>());

    /**
     * @tc.steps: step7. call OnModifyDone function.
     * @tc.expected: The obscured of renderContext is reasons.
     */
    pattern->OnModifyDone();
    EXPECT_EQ(renderContext->GetObscured(), reasons);
    pattern->pManager_->Reset();
}

/**
 * @tc.name: TextContentModifier004
 * @tc.desc: test text_content_modifier.cpp DrawObscuration function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestTwoNg, TextContentModifier004, TestSize.Level1)
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
    textContentModifier->SetDefaultAnimatablePropertyValue(textStyle);
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

/**
 * @tc.name: TextContentModifier005
 * @tc.desc: test text_content_modifier.cpp SetImageSpanNodeList function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestTwoNg, TextContentModifier005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode and textPattern.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Create imageNodeList and add imageNode into imageNodeList.
     */
    ParagraphStyle paragraphStyle;
    RefPtr<Paragraph> paragraph = Paragraph::Create(paragraphStyle, FontCollection::Current());
    ASSERT_NE(paragraph, nullptr);
    textPattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 1 });
    std::vector<WeakPtr<FrameNode>> imageNodeList;
    auto imageNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    imageNodeList.emplace_back(AceType::WeakClaim(AceType::RawPtr(imageNode)));
    textPattern->SetImageSpanNodeList(imageNodeList);
    /**
     * @tc.steps: step3. call CreateNodePaintMethod func.
     * @tc.expected: The imageNodeList_ size is equal to 1.
     */
    auto textPaintMethod = AceType::DynamicCast<TextPaintMethod>(textPattern->CreateNodePaintMethod());
    ASSERT_NE(textPaintMethod, nullptr);
    RefPtr<RenderContext> renderContext = textFrameNode->GetRenderContext();
    auto paintProperty = textPattern->CreatePaintProperty();
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, paintProperty);
    textPaintMethod->UpdateContentModifier(AceType::RawPtr(paintWrapper));

    ASSERT_NE(textPaintMethod->textContentModifier_, nullptr);
    EXPECT_EQ(textPaintMethod->textContentModifier_->imageNodeList_.size(), 1);
    textPattern->pManager_->Reset();
}

/**
 * @tc.name: TextOverlayModifierTest002
 * @tc.desc: test IsSelectedRectsChanged function.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestTwoNg, TextOverlayModifierTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textOverlayModifier
     */
    TextOverlayModifier textOverlayModifier;
    std::vector<RectF> rectList;
    rectList.push_back(RectF(RECT_X_VALUE, RECT_Y_VALUE, RECT_WIDTH_VALUE, RECT_HEIGHT_VALUE));
    rectList.push_back(RectF(RECT_X_VALUE, RECT_Y_VALUE, RECT_WIDTH_VALUE, RECT_HEIGHT_VALUE));
    textOverlayModifier.SetSelectedRects(rectList);
    /**
     * @tc.steps: step2. test IsSelectedRectsChanged
     */
    RectF secondRect(RECT_SECOND_X_VALUE, RECT_Y_VALUE, RECT_WIDTH_VALUE, RECT_HEIGHT_VALUE);
    textOverlayModifier.selectedRects_[0] = secondRect;
    bool rectsChanged = textOverlayModifier.IsSelectedRectsChanged(rectList);
    EXPECT_EQ(rectsChanged, true);
}

/**
 * @tc.name: TextOverlayModifierTest003
 * @tc.desc: test TextOverlayModifier function.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestTwoNg, TextOverlayModifierTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textOverlayModifier
     */
    TextOverlayModifier textOverlayModifier;
    OffsetF paintOffset;
    textOverlayModifier.SetPrintOffset(paintOffset);
    textOverlayModifier.SetSelectedColor(SELECTED_COLOR);

    /**
     * @tc.steps: step2. change version and save initial version
     */
    int32_t settingHighApiVersion = 12;
    int32_t settingLowApiVersion = 10;
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(settingHighApiVersion);

    /**
     * @tc.steps: step3. test TextOverlayModifier
     */
    TextOverlayModifier();
    EXPECT_EQ(textOverlayModifier.isClip_->Get(), true);

    /**
     * @tc.steps: step4. test TextOverlayModifier again and reuse initial ApiTargetVersion
     */
    AceApplicationInfo::GetInstance().SetApiTargetVersion(settingLowApiVersion);
    TextOverlayModifier();
    EXPECT_EQ(textOverlayModifier.isClip_->Get(), true);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: TextOverlayModifierTest004
 * @tc.desc: test onDraw function.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestTwoNg, TextOverlayModifierTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textOverlayModifier
     */
    TextOverlayModifier textOverlayModifier;
    OffsetF paintOffset;
    textOverlayModifier.SetPrintOffset(paintOffset);
    textOverlayModifier.SetSelectedColor(SELECTED_COLOR);

    /**
     * @tc.steps: step1. create selectedRects_
     */
    std::vector<RectF> rectList;
    rectList.push_back(RectF(RECT_SECOND_X_VALUE, RECT_Y_VALUE, RECT_WIDTH_VALUE, RECT_HEIGHT_VALUE));
    textOverlayModifier.SetSelectedRects(rectList);

    /**
     * @tc.steps: step3. create canvas
     */

    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, Save()).WillRepeatedly(Return());
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawRect(_)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, Restore()).WillRepeatedly(Return());

    /**
     * @tc.steps: step4. change ApiVersion and set isClip_ is true
     */

    int32_t changeApiVersion = 12;
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(changeApiVersion);
    TextOverlayModifier();
    EXPECT_EQ(textOverlayModifier.isClip_->Get(), true);

    /**
     * @tc.steps: step5. create context and textContentRect
     */
    DrawingContext context { canvas, CONTEXT_WIDTH_VALUE, CONTEXT_HEIGHT_VALUE };
    RectF textContentRect = CONTENT_RECT;
    textOverlayModifier.SetContentRect(textContentRect);

    /**
     * @tc.steps: step6. test onDraw
     */
    textOverlayModifier.SetShowSelect(true);
    textOverlayModifier.onDraw(context);
    RectF finalSelectRect = textOverlayModifier.selectedRects_[0];
    EXPECT_EQ(textOverlayModifier.paintOffset_->Get(), paintOffset);
    EXPECT_EQ(finalSelectRect.Width(), 5);
    EXPECT_EQ(textOverlayModifier.contentRect_, textContentRect);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: TextPaintMethodTest004
 * @tc.desc: test text_paint_method.cpp UpdateOverlayModifier
 * @tc.type: FUNC
 */
HWTEST_F(TextTestTwoNg, TextPaintMethodTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode and textLayoutProperty.
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
     * @tc.steps: step2. create textPaintMethod and update textLayoutProperty.
     */
    auto pattern = textFrameNode->GetPattern<Pattern>();
    ParagraphStyle paragraphStyle;
    RefPtr<Paragraph> paragraph = Paragraph::Create(paragraphStyle, FontCollection::Current());
    RefPtr<TextContentModifier> textContentModifier =
        AceType::MakeRefPtr<TextContentModifier>(std::optional<TextStyle>(TextStyle()));
    RefPtr<TextOverlayModifier> textOverlayModifier = AceType::MakeRefPtr<TextOverlayModifier>();
    TextPaintMethod textPaintMethod(pattern, BASE_LINE_OFFSET_VALUE, textContentModifier, textOverlayModifier);
    textLayoutProperty->UpdateFontSize(ADAPT_FONT_SIZE_VALUE);
    textLayoutProperty->UpdateBaselineOffset(ADAPT_BASE_LINE_OFFSET_VALUE);

    /**
     * @tc.steps: step3. update ClipEdge and create textTheme.
     */
    RefPtr<RenderContext> renderContext = RenderContext::Create();
    renderContext->UpdateClipEdge(true);
    auto paintProperty = textPattern->CreatePaintProperty();
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, paintProperty);

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto textTheme = AceType::MakeRefPtr<TextTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(textTheme));
    ASSERT_NE(textTheme, nullptr);

    /**
     * @tc.steps: step4. call UpdateContentModifier and GetOverlayModifier.
     */
    textPaintMethod.UpdateOverlayModifier(AceType::RawPtr(paintWrapper));
    auto OverlayModifier = textPaintMethod.GetOverlayModifier(AceType::RawPtr(paintWrapper));
    ASSERT_NE(OverlayModifier, nullptr);
    EXPECT_EQ(textOverlayModifier->isClip_->Get(), true);
}
} // namespace OHOS::Ace::NG
