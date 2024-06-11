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
 * @tc.name: GetTextRacePercent001
 * @tc.desc: test GetTextRacePercent.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFourNg, GetTextRacePercent001, TestSize.Level1)
{
    RefPtr<TextContentModifier> textContentModifier =
        AceType::MakeRefPtr<TextContentModifier>(std::optional<TextStyle>(TextStyle()));
    ASSERT_NE(textContentModifier, nullptr);

    textContentModifier->GetTextRacePercent();
    textContentModifier->racePercentFloat_->Set(1.0f);
    auto ret = textContentModifier->GetTextRacePercent();
    EXPECT_EQ(ret, 1.0f);
}

/**
 * @tc.name: DetermineTextRace001
 * @tc.desc: test DetermineTextRace.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFourNg, DetermineTextRace001, TestSize.Level1)
{
    RefPtr<TextContentModifier> textContentModifier =
        AceType::MakeRefPtr<TextContentModifier>(std::optional<TextStyle>(TextStyle()));
    ASSERT_NE(textContentModifier, nullptr);

    textContentModifier->DetermineTextRace();
    textContentModifier->marqueeSet_ = false;
    textContentModifier->marqueeOption_.start = false;
    textContentModifier->marqueeOption_.startPolicy = MarqueeStartPolicy::DEFAULT;
    textContentModifier->DetermineTextRace();
    EXPECT_FALSE(textContentModifier->marqueeSet_);
}

/**
 * @tc.name: DetermineTextRace002
 * @tc.desc: test GetTextRacePercent.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFourNg, DetermineTextRace002, TestSize.Level1)
{
    RefPtr<TextContentModifier> textContentModifier =
        AceType::MakeRefPtr<TextContentModifier>(std::optional<TextStyle>(TextStyle()));
    ASSERT_NE(textContentModifier, nullptr);

    textContentModifier->marqueeSet_ = true;
    textContentModifier->marqueeOption_.start = true;
    textContentModifier->marqueeOption_.startPolicy = MarqueeStartPolicy::ON_FOCUS;
    textContentModifier->textRacing_ = true;
    textContentModifier->marqueeFocused_ = true;
    textContentModifier->marqueeHovered_ = true;
    textContentModifier->DetermineTextRace();
    textContentModifier->marqueeFocused_ = false;
    textContentModifier->marqueeHovered_ = false;
    textContentModifier->DetermineTextRace();
    EXPECT_TRUE(textContentModifier->marqueeSet_);

    textContentModifier->marqueeSet_ = true;
    textContentModifier->marqueeOption_.start = true;
    textContentModifier->marqueeOption_.startPolicy = MarqueeStartPolicy::ON_FOCUS;
    textContentModifier->textRacing_ = false;
    textContentModifier->marqueeFocused_ = true;
    textContentModifier->marqueeHovered_ = false;
    textContentModifier->DetermineTextRace();
    textContentModifier->marqueeFocused_ = false;
    textContentModifier->marqueeHovered_ = true;
    textContentModifier->DetermineTextRace();
    textContentModifier->marqueeFocused_ = true;
    textContentModifier->marqueeHovered_ = true;
    textContentModifier->DetermineTextRace();
    textContentModifier->marqueeFocused_ = false;
    textContentModifier->marqueeHovered_ = false;
    textContentModifier->DetermineTextRace();
    EXPECT_TRUE(textContentModifier->marqueeSet_);
}

/**
 * @tc.name: AllowTextRace001
 * @tc.desc: test AllowTextRace.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFourNg, AllowTextRace001, TestSize.Level1)
{
    RefPtr<TextContentModifier> textContentModifier =
        AceType::MakeRefPtr<TextContentModifier>(std::optional<TextStyle>(TextStyle()));
    ASSERT_NE(textContentModifier, nullptr);
    textContentModifier->AllowTextRace();

    textContentModifier->marqueeSet_ = false;
    textContentModifier->marqueeOption_.start = false;
    bool ret = textContentModifier->AllowTextRace();
    EXPECT_FALSE(ret);

    textContentModifier->marqueeSet_ = true;
    textContentModifier->marqueeOption_.start = true;
    textContentModifier->marqueeOption_.loop = 1;
    textContentModifier->marqueeCount_ = 2;
    ret = textContentModifier->AllowTextRace();
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: AllowTextRace002
 * @tc.desc: test AllowTextRace.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFourNg, AllowTextRace002, TestSize.Level1)
{
    RefPtr<TextContentModifier> textContentModifier =
        AceType::MakeRefPtr<TextContentModifier>(std::optional<TextStyle>(TextStyle()));
    ASSERT_NE(textContentModifier, nullptr);
    textContentModifier->AllowTextRace();

    textContentModifier->marqueeSet_ = true;
    textContentModifier->marqueeOption_.start = true;
    textContentModifier->marqueeOption_.loop = 0;
    textContentModifier->marqueeCount_ = -1;
    textContentModifier->marqueeOption_.startPolicy = MarqueeStartPolicy::ON_FOCUS;
    textContentModifier->marqueeFocused_ = false;
    textContentModifier->marqueeHovered_ = false;
    bool ret = textContentModifier->AllowTextRace();
    EXPECT_FALSE(ret);

    textContentModifier->marqueeOption_.startPolicy = MarqueeStartPolicy::DEFAULT;
    textContentModifier->marqueeFocused_ = true;
    textContentModifier->marqueeHovered_ = true;
    ret = textContentModifier->AllowTextRace();
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: PauseTextRace001
 * @tc.desc: test PauseTextRace.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFourNg, PauseTextRace001, TestSize.Level1)
{
    RefPtr<TextContentModifier> textContentModifier =
        AceType::MakeRefPtr<TextContentModifier>(std::optional<TextStyle>(TextStyle()));
    ASSERT_NE(textContentModifier, nullptr);

    textContentModifier->textRacing_ = false;
    textContentModifier->PauseTextRace();

    textContentModifier->textRacing_ = true;
    textContentModifier->PauseTextRace();
    EXPECT_FALSE(textContentModifier->textRacing_);
}

/**
 * @tc.name: SetTextRaceAnimation001
 * @tc.desc: test SetTextRaceAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFourNg, SetTextRaceAnimation001, TestSize.Level1)
{
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    RefPtr<TextContentModifier> textContentModifier =
        AceType::MakeRefPtr<TextContentModifier>(std::optional<TextStyle>(TextStyle()), textPattern);
    ASSERT_NE(textContentModifier, nullptr);
    AnimationOption option = AnimationOption();
    textContentModifier->SetTextRaceAnimation(option);
    textContentModifier->marqueeSet_ = false;
    textContentModifier->marqueeOption_.start = false;
    textContentModifier->racePercentFloat_->Set(100.0f);
    textContentModifier->SetTextRaceAnimation(option);

    textContentModifier->racePercentFloat_->Set(200.0f);
    textContentModifier->marqueeSet_ = true;
    textContentModifier->marqueeOption_.loop = 0;
    textContentModifier->marqueeCount_ = -1;
    textContentModifier->marqueeOption_.startPolicy = MarqueeStartPolicy::DEFAULT;
    textContentModifier->marqueeFocused_ = true;
    textContentModifier->marqueeHovered_ = true;
    textContentModifier->SetTextRaceAnimation(option);
    EXPECT_TRUE(textContentModifier->textRacing_);
}

/**
 * @tc.name: ResumeTextRace001
 * @tc.desc: test ResumeTextRace.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFourNg, ResumeTextRace001, TestSize.Level1)
{
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    RefPtr<TextContentModifier> textContentModifier =
        AceType::MakeRefPtr<TextContentModifier>(std::optional<TextStyle>(TextStyle()), textPattern);
    ASSERT_NE(textContentModifier, nullptr);

    textContentModifier->marqueeSet_ = false;
    textContentModifier->marqueeOption_.start = false;
    textContentModifier->ResumeTextRace(true);

    textContentModifier->marqueeSet_ = true;
    textContentModifier->marqueeOption_.loop = 0;
    textContentModifier->marqueeCount_ = -1;
    textContentModifier->marqueeOption_.startPolicy = MarqueeStartPolicy::DEFAULT;
    textContentModifier->marqueeFocused_ = true;
    textContentModifier->marqueeHovered_ = true;
    textContentModifier->ResumeTextRace(true);
    textContentModifier->ResumeTextRace(false);
    EXPECT_FALSE(textContentModifier->textRacing_);
}

/**
 * @tc.name: PauseAnimation001
 * @tc.desc: test PauseAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFourNg, PauseAnimation001, TestSize.Level1)
{
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    RefPtr<TextContentModifier> textContentModifier =
        AceType::MakeRefPtr<TextContentModifier>(std::optional<TextStyle>(TextStyle()), textPattern);
    ASSERT_NE(textContentModifier, nullptr);
    textContentModifier->PauseAnimation();

    AnimationOption option = AnimationOption();
    textContentModifier->SetTextRaceAnimation(option);
    textContentModifier->textRacing_ = false;
    textContentModifier->PauseAnimation();

    textContentModifier->textRacing_ = true;
    textContentModifier->PauseAnimation();
    EXPECT_FALSE(textContentModifier->textRacing_);
}

/**
 * @tc.name: ResumeAnimation001
 * @tc.desc: test ResumeAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFourNg, ResumeAnimation001, TestSize.Level1)
{
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    RefPtr<TextContentModifier> textContentModifier =
        AceType::MakeRefPtr<TextContentModifier>(std::optional<TextStyle>(TextStyle()), textPattern);
    ASSERT_NE(textContentModifier, nullptr);
    textContentModifier->ResumeAnimation();

    AnimationOption option = AnimationOption();
    textContentModifier->SetTextRaceAnimation(option);
    textContentModifier->textRacing_ = true;
    textContentModifier->ResumeAnimation();

    textContentModifier->textRacing_ = false;
    textContentModifier->ResumeAnimation();
    EXPECT_TRUE(textContentModifier->textRacing_);
}

/**
 * @tc.name: StartTextRace001
 * @tc.desc: test StartTextRace.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFourNg, StartTextRace001, TestSize.Level1)
{
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    RefPtr<TextContentModifier> textContentModifier =
        AceType::MakeRefPtr<TextContentModifier>(std::optional<TextStyle>(TextStyle()));
    ASSERT_NE(textContentModifier, nullptr);

    MarqueeOption option;
    textContentModifier->StartTextRace(option);
    textContentModifier->textRacing_ = true;
    textContentModifier->StartTextRace(option);
    textContentModifier->textRacing_ = false;
    textContentModifier->StartTextRace(option);
    EXPECT_FALSE(textContentModifier->marqueeSet_);
}

/**
 * @tc.name: SetTextRace001
 * @tc.desc: test SetTextRace.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFourNg, SetTextRace001, TestSize.Level1)
{
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    RefPtr<TextContentModifier> textContentModifier =
        AceType::MakeRefPtr<TextContentModifier>(std::optional<TextStyle>(TextStyle()), textPattern);
    ASSERT_NE(textContentModifier, nullptr);

    MarqueeOption option;
    textContentModifier->SetTextRace(option);
    textContentModifier->textRacing_ = true;
    textContentModifier->SetTextRace(option);
    textContentModifier->textRacing_ = false;
    bool ret = textContentModifier->SetTextRace(option);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: SetAdaptMaxFontSize001
 * @tc.desc: test SetAdaptMaxFontSize.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFourNg, SetAdaptMaxFontSize001, TestSize.Level1)
{
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    RefPtr<TextContentModifier> textContentModifier =
        AceType::MakeRefPtr<TextContentModifier>(std::optional<TextStyle>(TextStyle()), textPattern);
    ASSERT_NE(textContentModifier, nullptr);

    textContentModifier->SetAdaptMaxFontSize(ADAPT_MAX_FONT_SIZE_VALUE);
    EXPECT_EQ(textContentModifier->adaptMaxFontSize_, ADAPT_MAX_FONT_SIZE_VALUE);
}

/**
 * @tc.name: DrawNormal001
 * @tc.desc: test DrawNormal.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFourNg, DrawNormal001, TestSize.Level1)
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
    textContentModifier->textRacing_ = false;
    textContentModifier->DrawNormal(context);
    textContentModifier->textRacing_ = true;
    textContentModifier->DrawNormal(context);
    EXPECT_FALSE(textPattern->pManager_->GetParagraphs().empty());
}

/**
 * @tc.name: GetFadeoutInfo001
 * @tc.desc: test GetFadeoutInfo.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFourNg, GetFadeoutInfo001, TestSize.Level1)
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
    textContentModifier->marqueeSet_ = false;
    textContentModifier->marqueeOption_.fadeout = false;
    textContentModifier->GetFadeoutInfo(context);

    textContentModifier->marqueeSet_ = true;
    textContentModifier->marqueeOption_.fadeout = true;
    textContentModifier->marqueeGradientPercent_ = 1.0f;
    textContentModifier->GetFadeoutInfo(context);

    textContentModifier->marqueeGradientPercent_ = 0.1f;
    textContentModifier->marqueeOption_.start = false;
    textContentModifier->GetFadeoutInfo(context);

    textContentModifier->marqueeOption_.start = true;
    textContentModifier->textRacing_ = false;
    textContentModifier->marqueeOption_.direction = MarqueeDirection::RIGHT;
    textContentModifier->GetFadeoutInfo(context);
    textContentModifier->marqueeOption_.direction = MarqueeDirection::LEFT;
    textContentModifier->textRacing_ = true;
    textContentModifier->GetFadeoutInfo(context);
    EXPECT_EQ(textContentModifier->marqueeGradientPercent_, 0.1f);
}

/**
 * @tc.name: PaintCustomSpan001
 * @tc.desc: test PaintCustomSpan.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFourNg, PaintCustomSpan001, TestSize.Level1)
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
HWTEST_F(TextTestFourNg, PaintImage001, TestSize.Level1)
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
HWTEST_F(TextTestFourNg, SetClip001, TestSize.Level1)
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
HWTEST_F(TextTestFourNg, TypedText001, TestSize.Level1)
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

} // namespace OHOS::Ace::NG
