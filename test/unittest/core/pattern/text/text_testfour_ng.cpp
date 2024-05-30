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

namespace OHOS::Ace::NG {

namespace {} // namespace

class TextTestFourNg : public TextBases {
public:
};

/**
 * @tc.name: UpdateFontFeature
 * @tc.desc: test fontFeature.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFourNg, UpdateFontFeature002, TestSize.Level1)
{
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE);
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
HWTEST_F(TextTestFourNg, SetLineSpacing001, TestSize.Level1)
{
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<TextLayoutProperty> textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);

    textModelNG.SetLineSpacing(LINE_SPACING_VALUE);
    EXPECT_EQ(textLayoutProperty->GetLineSpacing(), LINE_SPACING_VALUE);
    TextModelNG::SetLineSpacing(frameNode, LINE_SPACING_VALUE_1);
    EXPECT_EQ(textLayoutProperty->GetLineSpacing(), LINE_SPACING_VALUE_1);
}

/**
 * @tc.name: TextLayoutAlgorithm
 * @tc.desc: test TextLayoutAlgorithm.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFourNg, TextLayoutAlgorithm001, TestSize.Level1)
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
HWTEST_F(TextTestFourNg, UpdateParagraphBySpan001, TestSize.Level1)
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
HWTEST_F(TextTestFourNg, InitKeyEvent001, TestSize.Level1)
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
    textModelNG.Create("123456789");
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
HWTEST_F(TextTestFourNg, HandleKeyEvent001, TestSize.Level1)
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
    textModelNG.Create("123456789");
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
 * @tc.name: UpdateMarqueeOptions001
 * @tc.desc: test MarqueeOptions.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFourNg, UpdateMarqueeOptions001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode and textPattern.
     */
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<TextLayoutProperty> textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. test property.
     * @tc.expect： expect property as expect.
     */
    TextMarqueeOptions options;
    options.UpdateTextMarqueeStart(true);
    options.UpdateTextMarqueeStep(3);
    options.UpdateTextMarqueeLoop(3);
    options.UpdateTextMarqueeDirection(MarqueeDirection::RIGHT);
    options.UpdateTextMarqueeDelay(3);
    options.UpdateTextMarqueeFadeout(false);
    options.UpdateTextMarqueeStartPolicy(MarqueeStartPolicy::ON_FOCUS);
    textModelNG.SetMarqueeOptions(options);
    EXPECT_EQ(textLayoutProperty->GetTextMarqueeStart().value(), true);
    EXPECT_EQ(textLayoutProperty->GetTextMarqueeStep().value(), 3);
    EXPECT_EQ(textLayoutProperty->GetTextMarqueeLoop().value(), 3);
    EXPECT_EQ(textLayoutProperty->GetTextMarqueeDirection().value(), MarqueeDirection::RIGHT);
    EXPECT_EQ(textLayoutProperty->GetTextMarqueeDelay().value(), 3);
    EXPECT_EQ(textLayoutProperty->GetTextMarqueeFadeout().value(), false);
    EXPECT_EQ(textLayoutProperty->GetTextMarqueeStartPolicy().value(), MarqueeStartPolicy::ON_FOCUS);

    TextMarqueeOptions defaultOptions;
    textModelNG.SetMarqueeOptions(defaultOptions);
    EXPECT_EQ(textLayoutProperty->GetTextMarqueeStart().value_or(true), true);
    EXPECT_EQ(textLayoutProperty->GetTextMarqueeStep().value_or(6), 6);
    EXPECT_EQ(textLayoutProperty->GetTextMarqueeLoop().value_or(6), 6);
    EXPECT_EQ(textLayoutProperty->GetTextMarqueeDirection().value_or(MarqueeDirection::LEFT), MarqueeDirection::LEFT);
    EXPECT_EQ(textLayoutProperty->GetTextMarqueeDelay().value_or(6), 6);
    EXPECT_EQ(textLayoutProperty->GetTextMarqueeFadeout().value_or(true), true);
    EXPECT_EQ(textLayoutProperty->GetTextMarqueeStartPolicy().value_or(MarqueeStartPolicy::DEFAULT),
        MarqueeStartPolicy::DEFAULT);
}

/**
 * @tc.name: TextInitEvents001
 * @tc.desc: Test initializing focus and hover events.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFourNg, TextInitializingEvents001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode and textPattern.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textLayoutProperty = textFrameNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. set the TextOverflow value to Marquee.
     */
    textLayoutProperty->UpdateTextOverflow(TextOverflow::MARQUEE);
    textLayoutProperty->UpdateTextMarqueeStartPolicy(MarqueeStartPolicy::ON_FOCUS);

    /**
     * @tc.steps: step3. call OnModifyDone function.
     * @tc.expected: The focus and hover events are initialized.
     */
    textPattern->OnModifyDone();
    EXPECT_EQ(textPattern->focusInitialized_, true);
    EXPECT_EQ(textPattern->hoverInitialized_, true);
}

/**
 * @tc.name: TextRace001
 * @tc.desc: test TextRace.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFourNg, TextRace001, TestSize.Level1)
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
     * @tc.steps: step2. set MARQUEE.
     */
    textLayoutProperty->UpdateTextOverflow(TextOverflow::MARQUEE);

    /**
     * @tc.steps: step3. create textPaintMethod and call DoStartTextRace
     */
    RefPtr<TextContentModifier> textContentModifier =
        AceType::MakeRefPtr<TextContentModifier>(std::optional<TextStyle>(TextStyle()));
    RefPtr<TextOverlayModifier> textOverlayModifier = AceType::MakeRefPtr<TextOverlayModifier>();
    TextPaintMethod textPaintMethod(textPattern, BASE_LINE_OFFSET_VALUE, textContentModifier, textOverlayModifier);
    textPaintMethod.DoStartTextRace();
    textContentModifier->StopTextRace();
}

/**
 * @tc.name: TextSetFadeout001
 * @tc.desc: test text_pattern.cpp SetFadeout function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFourNg, TextSetFadeout001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();

    /**
     * @tc.steps: step2. Set default fadeout
     * @tc.expected: step2. Check the overlay node, it should not be created by EnsureOverlayExists()
     */
    pattern->SetFadeout(false, false, 0.0f);
    auto overlayNode = frameNode->GetOverlayNode();
    EXPECT_EQ(overlayNode, nullptr);

    /**
     * @tc.steps: step3. Set common fadeout values
     * @tc.expected: step3. Check the overlay node
     */
    pattern->EnsureOverlayExists();
    pattern->SetFadeout(true, false, 0.04f);
    overlayNode = frameNode->GetOverlayNode();
    ASSERT_NE(overlayNode, nullptr);

    pattern->SetFadeout(false, true, 0.04f);
    overlayNode = frameNode->GetOverlayNode();
    ASSERT_NE(overlayNode, nullptr);

    pattern->SetFadeout(true, true, 0.04f);
    overlayNode = frameNode->GetOverlayNode();
    ASSERT_NE(overlayNode, nullptr);
}

} // namespace OHOS::Ace::NG
