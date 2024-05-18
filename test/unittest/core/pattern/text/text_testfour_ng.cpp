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
} // namespace OHOS::Ace::NG
