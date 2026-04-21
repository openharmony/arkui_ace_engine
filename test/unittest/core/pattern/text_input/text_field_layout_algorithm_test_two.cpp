/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/frameworks/core/components_ng/render/mock_paragraph.h"
#include "text_input_base.h"

#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/text/span/span_string.h"
#include "core/components_ng/pattern/text_field/text_field_layout_algorithm.h"

namespace OHOS::Ace::NG {

constexpr float INLINE_MIN_WIDTH_PX = 16.0f;

struct ParagraphConfig {
    float maxWidth = 100.0f;
    float height = 50.0f;
    float longestLine = 0.0f;
    float longestLineWithIndent = 0.0f;
    int32_t lineCount = 1;
    bool needLayout = false;
};

struct ConstraintConfig {
    float minWidth = 50.0f;
    float minHeight = 20.0f;
    float maxWidth = 300.0f;
    float maxHeight = 100.0f;
    float selfIdealWidth = 0.0f;
    float selfIdealHeight = 0.0f;
};

class TextFieldLayoutAlgorithmTestHelperTwo : public TextFieldLayoutAlgorithm {
public:
    static void SetParagraph(TextFieldLayoutAlgorithm* algorithm, const RefPtr<Paragraph>& paragraph)
    {
        auto* helper = reinterpret_cast<TextFieldLayoutAlgorithmTestHelperTwo*>(algorithm);
        helper->paragraph_ = paragraph;
    }

    static void SetAutoWidth(TextFieldLayoutAlgorithm* algorithm, bool autoWidth)
    {
        auto* helper = reinterpret_cast<TextFieldLayoutAlgorithmTestHelperTwo*>(algorithm);
        helper->autoWidth_ = autoWidth;
    }

    static void SetInlineFocus(TextFieldLayoutAlgorithm* algorithm, bool isInlineFocus)
    {
        auto* helper = reinterpret_cast<TextFieldLayoutAlgorithmTestHelperTwo*>(algorithm);
        helper->isInlineFocus_ = isInlineFocus;
    }

    static void SetPreferredHeight(TextFieldLayoutAlgorithm* algorithm, float preferredHeight)
    {
        auto* helper = reinterpret_cast<TextFieldLayoutAlgorithmTestHelperTwo*>(algorithm);
        helper->preferredHeight_ = preferredHeight;
    }
};

class TextFieldLayoutAlgorithmTestTwo : public TextInputBases {
protected:
    RefPtr<Paragraph> CreateMockParagraph(const ParagraphConfig& config)
    {
        auto mockParagraph = MockParagraph::GetOrCreateMockParagraph();
        testing::Mock::VerifyAndClear(mockParagraph.GetRawPtr());
        EXPECT_CALL(*mockParagraph, GetMaxWidth()).WillRepeatedly(Return(config.maxWidth));
        EXPECT_CALL(*mockParagraph, GetHeight()).WillRepeatedly(Return(config.height));
        EXPECT_CALL(*mockParagraph, GetLineCount()).WillRepeatedly(Return(config.lineCount));
        EXPECT_CALL(*mockParagraph, GetLongestLine()).WillRepeatedly(Return(config.longestLine));
        EXPECT_CALL(*mockParagraph, GetLongestLineWithIndent()).WillRepeatedly(Return(config.longestLineWithIndent));
        if (config.needLayout) {
            EXPECT_CALL(*mockParagraph, Layout(_)).Times(AtLeast(1));
        }
        return mockParagraph;
    }

    LayoutWrapper* CreateLayoutWrapper(const RefPtr<FrameNode>& frameNode)
    {
        layoutWrapper_ = frameNode->CreateLayoutWrapper(true, true);
        auto rawPtr = AceType::RawPtr(layoutWrapper_);
        UpdateLayoutAlgorithmFromWrapper();
        return rawPtr;
    }

    TextFieldLayoutAlgorithm* GetTextFieldLayoutAlgorithm()
    {
        UpdateLayoutAlgorithmFromWrapper();
        return layoutAlgorithm_.GetRawPtr();
    }

    void SetParagraphForTest(TextFieldLayoutAlgorithm* algorithm, const RefPtr<Paragraph>& paragraph)
    {
        TextFieldLayoutAlgorithmTestHelperTwo::SetParagraph(algorithm, paragraph);
    }

    void SetAutoWidthForTest(TextFieldLayoutAlgorithm* algorithm, bool autoWidth)
    {
        TextFieldLayoutAlgorithmTestHelperTwo::SetAutoWidth(algorithm, autoWidth);
    }

    void SetInlineFocusForTest(TextFieldLayoutAlgorithm* algorithm, bool isInlineFocus)
    {
        TextFieldLayoutAlgorithmTestHelperTwo::SetInlineFocus(algorithm, isInlineFocus);
    }

    void SetPreferredHeightForTest(TextFieldLayoutAlgorithm* algorithm, float preferredHeight)
    {
        TextFieldLayoutAlgorithmTestHelperTwo::SetPreferredHeight(algorithm, preferredHeight);
    }

    LayoutConstraintF CreateContentConstraint(const ConstraintConfig& config)
    {
        LayoutConstraintF constraint;
        constraint.minSize = SizeF(config.minWidth, config.minHeight);
        constraint.maxSize = SizeF(config.maxWidth, config.maxHeight);
        if (config.selfIdealWidth > 0.0f) {
            constraint.selfIdealSize.SetWidth(config.selfIdealWidth);
        }
        if (config.selfIdealHeight > 0.0f) {
            constraint.selfIdealSize.SetHeight(config.selfIdealHeight);
        }
        return constraint;
    }

    void SetupStyledPlaceholderTest(const std::string& placeholderText = "styled placeholder")
    {
        CreateTextField("", "placeholder");
        ASSERT_NE(pattern_, nullptr);
        RefPtr<SpanString> spanString = AceType::MakeRefPtr<SpanString>(StringUtils::Str8ToStr16(placeholderText));
        pattern_->SetPlaceholderStyledString(spanString);
        layoutWrapper_ = frameNode_->CreateLayoutWrapper(true, true);
        UpdateLayoutAlgorithmFromWrapper();
    }

    void SetupTextAreaTest(
        const std::string& text = DEFAULT_TEXT, std::function<void(TextFieldModelNG&)> setup = nullptr)
    {
        auto* stack = ViewStackProcessor::GetInstance();
        stack->StartGetAccessRecordingFor(DEFAULT_NODE_ID);
        TextFieldModelNG textFieldModelNG;
        textFieldModelNG.CreateTextArea(StringUtils::Str8ToStr16("placeholder"), StringUtils::Str8ToStr16(text));
        if (setup) {
            setup(textFieldModelNG);
        }
        stack->StopGetAccessRecording();
        frameNode_ = AceType::DynamicCast<FrameNode>(stack->Finish());
        ASSERT_NE(frameNode_, nullptr);
        pattern_ = frameNode_->GetPattern<TextFieldPattern>();
        ASSERT_NE(pattern_, nullptr);
        layoutProperty_ = frameNode_->GetLayoutProperty<TextFieldLayoutProperty>();
        layoutWrapper_ = frameNode_->CreateLayoutWrapper(true, true);
        UpdateLayoutAlgorithmFromWrapper();
    }

    void SetupTextFieldTest(
        const std::string& text = DEFAULT_TEXT, std::function<void(TextFieldModelNG&)> setup = nullptr)
    {
        CreateTextField(text, "", setup);
        ASSERT_NE(pattern_, nullptr);
        layoutWrapper_ = frameNode_->CreateLayoutWrapper(true, true);
        UpdateLayoutAlgorithmFromWrapper();
    }

private:
    void UpdateLayoutAlgorithmFromWrapper()
    {
        if (layoutWrapper_) {
            auto layoutAlgorithmWrapper =
                AceType::DynamicCast<LayoutAlgorithmWrapper>(layoutWrapper_->GetLayoutAlgorithm());
            if (layoutAlgorithmWrapper) {
                layoutAlgorithm_ =
                    AceType::DynamicCast<TextFieldLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
            }
        }
    }

    RefPtr<LayoutWrapper> layoutWrapper_;
    RefPtr<TextFieldLayoutAlgorithm> layoutAlgorithm_;
};

/**
 * @tc.name: StyledPlaceHolderMeasureContent001
 * @tc.desc: Test with autoWidth_ = true, triggers first branch where minSize.Width is set to
 *           max(INLINE_MIN_WITH, minSize.Width) and selfIdealSize.Width is set to nullopt.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTestTwo, StyledPlaceHolderMeasureContent001, TestSize.Level1)
{
    SetupStyledPlaceholderTest();
    auto algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);
    SetAutoWidthForTest(algorithm, true);
    SetParagraphForTest(algorithm, CreateMockParagraph({}));

    auto constraint = CreateContentConstraint({ .minWidth = 10.0f });
    EXPECT_TRUE(algorithm->MeasureContent(constraint, AceType::RawPtr(layoutWrapper_)).has_value());
}

/**
 * @tc.name: StyledPlaceHolderMeasureContent002
 * @tc.desc: Test with adapter = true, triggers first branch through adapter parameter.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTestTwo, StyledPlaceHolderMeasureContent002, TestSize.Level1)
{
    SetupStyledPlaceholderTest();
    auto algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);
    SetAutoWidthForTest(algorithm, false);
    SetParagraphForTest(algorithm, CreateMockParagraph({}));

    auto constraint = CreateContentConstraint({});
    EXPECT_TRUE(algorithm->MeasureContent(constraint, AceType::RawPtr(layoutWrapper_)).has_value());
}

/**
 * @tc.name: StyledPlaceHolderMeasureContent003
 * @tc.desc: Test with widthPolicy = WRAP_CONTENT, triggers first branch through widthPolicy.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTestTwo, StyledPlaceHolderMeasureContent003, TestSize.Level1)
{
    SetupStyledPlaceholderTest();
    auto layoutProperty = layoutWrapper_->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::WRAP_CONTENT, true);

    auto algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);
    SetAutoWidthForTest(algorithm, false);
    SetParagraphForTest(algorithm, CreateMockParagraph({}));

    auto constraint = CreateContentConstraint({});
    EXPECT_TRUE(algorithm->MeasureContent(constraint, AceType::RawPtr(layoutWrapper_)).has_value());
}

/**
 * @tc.name: StyledPlaceHolderMeasureContent004
 * @tc.desc: Test with widthPolicy = FIX_AT_IDEAL_SIZE and isInlineFocus_ = false,
 *           triggers selfIdealSize.Reset().
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTestTwo, StyledPlaceHolderMeasureContent004, TestSize.Level1)
{
    SetupStyledPlaceholderTest();
    auto layoutProperty = layoutWrapper_->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, true);

    auto algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);
    SetAutoWidthForTest(algorithm, false);
    SetInlineFocusForTest(algorithm, false);
    SetParagraphForTest(algorithm, CreateMockParagraph({ .maxWidth = 200.0f }));

    auto constraint = CreateContentConstraint({});
    EXPECT_TRUE(algorithm->MeasureContent(constraint, AceType::RawPtr(layoutWrapper_)).has_value());
}

/**
 * @tc.name: StyledPlaceHolderMeasureContent005
 * @tc.desc: Test with widthPolicy = FIX_AT_IDEAL_SIZE and isInlineFocus_ = true,
 *           falls through to else branch.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTestTwo, StyledPlaceHolderMeasureContent005, TestSize.Level1)
{
    SetupStyledPlaceholderTest();
    auto layoutProperty = layoutWrapper_->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, true);

    auto algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);
    SetAutoWidthForTest(algorithm, false);
    SetInlineFocusForTest(algorithm, true);
    SetParagraphForTest(algorithm, CreateMockParagraph({ .maxWidth = 300.0f }));

    auto constraint = CreateContentConstraint({});
    EXPECT_TRUE(algorithm->MeasureContent(constraint, AceType::RawPtr(layoutWrapper_)).has_value());
}

/**
 * @tc.name: StyledPlaceHolderMeasureContent006
 * @tc.desc: Test with widthPolicy = MATCH_PARENT, triggers else branch where
 *           selfIdealSize.SetWidth(contentConstraint.maxSize.Width()).
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTestTwo, StyledPlaceHolderMeasureContent006, TestSize.Level1)
{
    SetupStyledPlaceholderTest();
    auto layoutProperty = layoutWrapper_->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, true);

    auto algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);
    SetAutoWidthForTest(algorithm, false);
    SetParagraphForTest(algorithm, CreateMockParagraph({ .maxWidth = 300.0f }));

    auto constraint = CreateContentConstraint({});
    EXPECT_TRUE(algorithm->MeasureContent(constraint, AceType::RawPtr(layoutWrapper_)).has_value());
}

/**
 * @tc.name: StyledPlaceHolderMeasureContent007
 * @tc.desc: Test with widthPolicy = NO_MATCH, falls to else branch.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTestTwo, StyledPlaceHolderMeasureContent007, TestSize.Level1)
{
    SetupStyledPlaceholderTest();
    auto layoutProperty = layoutWrapper_->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, true);

    auto algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);
    SetAutoWidthForTest(algorithm, false);
    SetParagraphForTest(algorithm, CreateMockParagraph({ .maxWidth = 300.0f }));

    auto constraint = CreateContentConstraint({});
    EXPECT_TRUE(algorithm->MeasureContent(constraint, AceType::RawPtr(layoutWrapper_)).has_value());
}

/**
 * @tc.name: StyledPlaceHolderMeasureContent008
 * @tc.desc: Test with paragraph_ set, verifies paragraph_ is set to nullptr after StylePlaceHolderMeasure.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTestTwo, StyledPlaceHolderMeasureContent008, TestSize.Level1)
{
    SetupStyledPlaceholderTest();
    auto algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);
    SetParagraphForTest(algorithm, CreateMockParagraph({}));

    auto constraint = CreateContentConstraint({});
    EXPECT_TRUE(algorithm->MeasureContent(constraint, AceType::RawPtr(layoutWrapper_)).has_value());
}

/**
 * @tc.name: StyledPlaceHolderMeasureContent009
 * @tc.desc: Test with preferredHeight_ set and multiple lines, tests inlineMeasureItem_.inlineSizeHeight
 *           calculation with lineCount > 1.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTestTwo, StyledPlaceHolderMeasureContent009, TestSize.Level1)
{
    SetupStyledPlaceholderTest("styled placeholder with multiple lines");
    auto algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);
    SetPreferredHeightForTest(algorithm, 20.0f);
    SetParagraphForTest(algorithm, CreateMockParagraph({ .height = 100.0f, .lineCount = 3 }));

    auto constraint = CreateContentConstraint({});
    EXPECT_TRUE(algorithm->MeasureContent(constraint, AceType::RawPtr(layoutWrapper_)).has_value());
}

/**
 * @tc.name: StyledPlaceHolderMeasureContent010
 * @tc.desc: Test with minSize.Width smaller than INLINE_MIN_WITH, verifies max(INLINE_MIN_WITH, minSize.Width).
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTestTwo, StyledPlaceHolderMeasureContent010, TestSize.Level1)
{
    SetupStyledPlaceholderTest();
    auto algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);
    SetAutoWidthForTest(algorithm, true);
    SetParagraphForTest(algorithm, CreateMockParagraph({}));

    auto constraint = CreateContentConstraint({ .minWidth = 5.0f });
    EXPECT_TRUE(algorithm->MeasureContent(constraint, AceType::RawPtr(layoutWrapper_)).has_value());
}

/**
 * @tc.name: StyledPlaceHolderMeasureContent011
 * @tc.desc: Test with minSize.Width larger than INLINE_MIN_WITH, verifies max(INLINE_MIN_WITH, minSize.Width).
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTestTwo, StyledPlaceHolderMeasureContent011, TestSize.Level1)
{
    SetupStyledPlaceholderTest();
    auto algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);
    SetAutoWidthForTest(algorithm, true);
    SetParagraphForTest(algorithm, CreateMockParagraph({}));

    auto constraint = CreateContentConstraint({});
    EXPECT_TRUE(algorithm->MeasureContent(constraint, AceType::RawPtr(layoutWrapper_)).has_value());
}

/**
 * @tc.name: StyledPlaceHolderMeasureContent012
 * @tc.desc: Test with default layout policy (no policy set), falls to else branch.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTestTwo, StyledPlaceHolderMeasureContent012, TestSize.Level1)
{
    SetupStyledPlaceholderTest();
    auto algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);
    SetAutoWidthForTest(algorithm, false);
    SetParagraphForTest(algorithm, CreateMockParagraph({ .maxWidth = 300.0f }));

    auto constraint = CreateContentConstraint({});
    EXPECT_TRUE(algorithm->MeasureContent(constraint, AceType::RawPtr(layoutWrapper_)).has_value());
}

/**
 * @tc.name: StyledPlaceHolderMeasureContent013
 * @tc.desc: Test with lineCount exceeding MaxViewLines, tests min(lineCount, MaxViewLines) calculation.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTestTwo, StyledPlaceHolderMeasureContent013, TestSize.Level1)
{
    CreateTextField("", "placeholder", [](TextFieldModelNG& model) { model.SetMaxViewLines(2); });
    ASSERT_NE(pattern_, nullptr);
    RefPtr<SpanString> spanString = AceType::MakeRefPtr<SpanString>(u"styled placeholder with multiple lines");
    pattern_->SetPlaceholderStyledString(spanString);
    layoutWrapper_ = frameNode_->CreateLayoutWrapper(true, true);
    UpdateLayoutAlgorithmFromWrapper();

    auto algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);
    SetPreferredHeightForTest(algorithm, 25.0f);
    SetParagraphForTest(algorithm, CreateMockParagraph({ .height = 150.0f, .lineCount = 5 }));

    auto constraint = CreateContentConstraint({});
    EXPECT_TRUE(algorithm->MeasureContent(constraint, AceType::RawPtr(layoutWrapper_)).has_value());
}

/**
 * @tc.name: StyledPlaceHolderMeasureContent014
 * @tc.desc: Test with selfIdealSize already set, verifies selfIdealSize.Height is set to nullopt.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTestTwo, StyledPlaceHolderMeasureContent014, TestSize.Level1)
{
    SetupStyledPlaceholderTest();
    auto algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);
    SetAutoWidthForTest(algorithm, true);
    SetParagraphForTest(algorithm, CreateMockParagraph({}));

    auto constraint = CreateContentConstraint({ .selfIdealWidth = 200.0f, .selfIdealHeight = 80.0f });
    EXPECT_TRUE(algorithm->MeasureContent(constraint, AceType::RawPtr(layoutWrapper_)).has_value());
}

/**
 * @tc.name: StyledPlaceHolderMeasureContent015
 * @tc.desc: Test with zero preferredHeight_, tests inlineMeasureItem_.inlineSizeHeight with zero value.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTestTwo, StyledPlaceHolderMeasureContent015, TestSize.Level1)
{
    SetupStyledPlaceholderTest();
    auto algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);
    SetPreferredHeightForTest(algorithm, 0.0f);
    SetParagraphForTest(algorithm, CreateMockParagraph({}));

    auto constraint = CreateContentConstraint({});
    EXPECT_TRUE(algorithm->MeasureContent(constraint, AceType::RawPtr(layoutWrapper_)).has_value());
}

/**
 * @tc.name: TextAreaMeasureContent006
 * @tc.desc: Test TextAreaMeasureContent with horizontal scrolling enabled.
 *           Branch: isHorizontalScrolling = true, uses infinity layout then GetLongestLineWithIndent.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTestTwo, TextAreaMeasureContent006, TestSize.Level1)
{
    SetupTextAreaTest(DEFAULT_TEXT, [](TextFieldModelNG& model) { model.SetHorizontalScrolling(true); });

    auto algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);
    SetParagraphForTest(algorithm, CreateMockParagraph({ .maxWidth = 300.0f,
                                       .height = 100.0f,
                                       .longestLine = 250.0f,
                                       .longestLineWithIndent = 250.0f,
                                       .needLayout = true }));

    auto constraint = CreateContentConstraint({ .maxHeight = 200.0f });
    SizeF result = algorithm->TextAreaMeasureContent(constraint, AceType::RawPtr(layoutWrapper_));
    EXPECT_GT(result.Width(), 0.0f);
    EXPECT_GT(result.Height(), 0.0f);
}

/**
 * @tc.name: TextAreaMeasureContent007
 * @tc.desc: Test TextAreaMeasureContent with autoWidth and horizontal scrolling enabled.
 *           Branch: autoWidth_ = true, isHorizontalScrolling = true, should not enter autoWidth branch.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTestTwo, TextAreaMeasureContent007, TestSize.Level1)
{
    SetupTextAreaTest(DEFAULT_TEXT, [](TextFieldModelNG& model) { model.SetHorizontalScrolling(true); });

    auto algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);
    SetAutoWidthForTest(algorithm, true);
    SetParagraphForTest(algorithm, CreateMockParagraph({ .maxWidth = 300.0f,
                                       .height = 100.0f,
                                       .longestLine = 250.0f,
                                       .longestLineWithIndent = 250.0f,
                                       .needLayout = true }));

    auto constraint = CreateContentConstraint({ .maxHeight = 200.0f });
    SizeF result = algorithm->TextAreaMeasureContent(constraint, AceType::RawPtr(layoutWrapper_));
    EXPECT_GT(result.Width(), 0.0f);
    EXPECT_GT(result.Height(), 0.0f);
}

/**
 * @tc.name: TextAreaMeasureContent008
 * @tc.desc: Test TextAreaMeasureContent with NormalMaxViewLines but ShouldUseInfiniteMaxLines returns false.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTestTwo, TextAreaMeasureContent008, TestSize.Level1)
{
    SetupTextAreaTest(DEFAULT_TEXT, [](TextFieldModelNG& model) {
        model.SetNormalMaxViewLines(3);
        model.SetOverflowMode(OverflowMode::CLIP);
    });
    layoutProperty_->UpdateTextOverflow(TextOverflow::ELLIPSIS);

    auto algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);
    SetParagraphForTest(algorithm, CreateMockParagraph({ .maxWidth = 300.0f,
                                       .height = 150.0f,
                                       .longestLine = 250.0f,
                                       .longestLineWithIndent = 250.0f,
                                       .lineCount = 5,
                                       .needLayout = true }));

    auto constraint = CreateContentConstraint({ .maxHeight = 200.0f });
    SizeF result = algorithm->TextAreaMeasureContent(constraint, AceType::RawPtr(layoutWrapper_));
    EXPECT_GT(result.Width(), 0.0f);
    EXPECT_GT(result.Height(), 0.0f);
}

/**
 * @tc.name: TextAreaMeasureContent009
 * @tc.desc: Test TextAreaMeasureContent with NormalMaxViewLines and ShouldUseInfiniteMaxLines returns true.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTestTwo, TextAreaMeasureContent009, TestSize.Level1)
{
    SetupTextAreaTest(DEFAULT_TEXT, [](TextFieldModelNG& model) {
        model.SetNormalMaxViewLines(2);
        model.SetOverflowMode(OverflowMode::SCROLL);
    });
    layoutProperty_->UpdateTextOverflow(TextOverflow::NONE);

    auto algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);
    SetParagraphForTest(algorithm, CreateMockParagraph({ .maxWidth = 300.0f,
                                       .height = 150.0f,
                                       .longestLine = 250.0f,
                                       .longestLineWithIndent = 250.0f,
                                       .lineCount = 5,
                                       .needLayout = true }));

    auto constraint = CreateContentConstraint({ .maxHeight = 200.0f });
    SizeF result = algorithm->TextAreaMeasureContent(constraint, AceType::RawPtr(layoutWrapper_));
    EXPECT_GT(result.Width(), 0.0f);
    EXPECT_GT(result.Height(), 0.0f);
    EXPECT_LE(result.Height(), constraint.maxSize.Height());
}

/**
 * @tc.name: TextAreaMeasureContent010
 * @tc.desc: Test TextAreaMeasureContent height calculation with positive longestLine.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTestTwo, TextAreaMeasureContent010, TestSize.Level1)
{
    SetupTextAreaTest();

    auto algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);
    SetPreferredHeightForTest(algorithm, 50.0f);
    SetParagraphForTest(algorithm, CreateMockParagraph({ .maxWidth = 300.0f,
                                       .height = 100.0f,
                                       .longestLine = 250.0f,
                                       .longestLineWithIndent = 250.0f,
                                       .lineCount = 3,
                                       .needLayout = true }));

    auto constraint = CreateContentConstraint({ .maxHeight = 300.0f });
    SizeF result = algorithm->TextAreaMeasureContent(constraint, AceType::RawPtr(layoutWrapper_));
    EXPECT_GT(result.Width(), 0.0f);
    EXPECT_GT(result.Height(), 0.0f);
}

/**
 * @tc.name: TextAreaMeasureContent011
 * @tc.desc: Test TextAreaMeasureContent height calculation with zero longestLine.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTestTwo, TextAreaMeasureContent011, TestSize.Level1)
{
    SetupTextAreaTest("");

    auto algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);
    SetPreferredHeightForTest(algorithm, 50.0f);
    SetParagraphForTest(algorithm,
        CreateMockParagraph({ .maxWidth = 300.0f, .height = 20.0f, .longestLine = 0.0f, .needLayout = true }));

    auto constraint = CreateContentConstraint({ .maxHeight = 300.0f });
    SizeF result = algorithm->TextAreaMeasureContent(constraint, AceType::RawPtr(layoutWrapper_));
    EXPECT_GT(result.Width(), 0.0f);
    EXPECT_GE(result.Height(), 50.0f);
}

/**
 * @tc.name: TextAreaMeasureContent012
 * @tc.desc: Test TextAreaMeasureContent with autoWidth enabled for TextArea.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTestTwo, TextAreaMeasureContent012, TestSize.Level1)
{
    SetupTextAreaTest();

    auto algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);
    SetAutoWidthForTest(algorithm, true);
    SetParagraphForTest(algorithm, CreateMockParagraph({ .maxWidth = 200.0f,
                                       .height = 100.0f,
                                       .longestLine = 180.0f,
                                       .longestLineWithIndent = 180.0f,
                                       .lineCount = 3,
                                       .needLayout = true }));

    auto constraint = CreateContentConstraint({ .maxHeight = 200.0f });
    SizeF result = algorithm->TextAreaMeasureContent(constraint, AceType::RawPtr(layoutWrapper_));
    EXPECT_GT(result.Width(), 0.0f);
    EXPECT_GE(result.Width(), INLINE_MIN_WIDTH_PX);
    EXPECT_GT(result.Height(), 0.0f);
}

/**
 * @tc.name: TextAreaMeasureContent013
 * @tc.desc: Test TextAreaMeasureContent with zero lineCount.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTestTwo, TextAreaMeasureContent013, TestSize.Level1)
{
    SetupTextAreaTest("", [](TextFieldModelNG& model) {
        model.SetNormalMaxViewLines(2);
        model.SetOverflowMode(OverflowMode::SCROLL);
    });
    layoutProperty_->UpdateTextOverflow(TextOverflow::CLIP);

    auto algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);
    SetParagraphForTest(algorithm, CreateMockParagraph({ .maxWidth = 300.0f,
                                       .height = 100.0f,
                                       .longestLine = 250.0f,
                                       .longestLineWithIndent = 250.0f,
                                       .lineCount = 0,
                                       .needLayout = true }));

    auto constraint = CreateContentConstraint({ .maxHeight = 200.0f });
    SizeF result = algorithm->TextAreaMeasureContent(constraint, AceType::RawPtr(layoutWrapper_));
    EXPECT_GT(result.Width(), 0.0f);
    EXPECT_GT(result.Height(), 0.0f);
}

/**
 * @tc.name: TextAreaMeasureContent014
 * @tc.desc: Test TextAreaMeasureContent with contentHeight exceeding maxSize.Height.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTestTwo, TextAreaMeasureContent014, TestSize.Level1)
{
    SetupTextAreaTest();

    auto algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);
    SetParagraphForTest(algorithm, CreateMockParagraph({ .maxWidth = 300.0f,
                                       .height = 200.0f,
                                       .longestLine = 250.0f,
                                       .longestLineWithIndent = 250.0f,
                                       .lineCount = 5,
                                       .needLayout = true }));

    auto constraint = CreateContentConstraint({ .maxHeight = 100.0f });
    SizeF result = algorithm->TextAreaMeasureContent(constraint, AceType::RawPtr(layoutWrapper_));
    EXPECT_GT(result.Width(), 0.0f);
    EXPECT_LE(result.Height(), constraint.maxSize.Height());
}

/**
 * @tc.name: CalculateContentWidth008
 * @tc.desc: Test CalculateContentWidth with MATCH_PARENT policy.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTestTwo, CalculateContentWidth008, TestSize.Level1)
{
    SetupTextFieldTest();
    auto layoutProperty = layoutWrapper_->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, true);

    auto algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);
    SetAutoWidthForTest(algorithm, false);
    SetParagraphForTest(
        algorithm, CreateMockParagraph({ .maxWidth = 300.0f, .longestLineWithIndent = 200.0f, .needLayout = true }));

    auto constraint = CreateContentConstraint({});
    float result = algorithm->CalculateContentWidth(constraint, AceType::RawPtr(layoutWrapper_), 0.0f);
    EXPECT_GT(result, 0.0f);
    EXPECT_LE(result, constraint.maxSize.Width());
}

/**
 * @tc.name: CalculateContentWidth009
 * @tc.desc: Test CalculateContentWidth with contentWidth > minWidth.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTestTwo, CalculateContentWidth009, TestSize.Level1)
{
    SetupTextFieldTest();
    auto layoutProperty = layoutWrapper_->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::WRAP_CONTENT, true);

    auto algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);
    SetAutoWidthForTest(algorithm, false);
    SetParagraphForTest(
        algorithm, CreateMockParagraph({ .maxWidth = 400.0f, .longestLineWithIndent = 350.0f, .needLayout = true }));

    auto constraint = CreateContentConstraint({ .maxWidth = 500.0f });
    float result = algorithm->CalculateContentWidth(constraint, AceType::RawPtr(layoutWrapper_), 0.0f);
    EXPECT_GT(result, INLINE_MIN_WIDTH_PX);
    EXPECT_LE(result, 350.0f);
}

/**
 * @tc.name: CalculateContentWidth010
 * @tc.desc: Test CalculateContentWidth with API 11+ and non-zero imageWidth.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTestTwo, CalculateContentWidth010, TestSize.Level1)
{
    SetupTextFieldTest();
    auto layoutProperty = layoutWrapper_->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    CalcSize calcMinSize(CalcLength(150.0f), CalcLength(50.0f));
    layoutProperty->UpdateCalcMinSize(calcMinSize);

    auto algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);
    SetParagraphForTest(
        algorithm, CreateMockParagraph({ .maxWidth = 350.0f, .longestLineWithIndent = 300.0f, .needLayout = true }));

    auto constraint = CreateContentConstraint({ .maxWidth = 400.0f });
    float result = algorithm->CalculateContentWidth(constraint, AceType::RawPtr(layoutWrapper_), 50.0f);
    EXPECT_GT(result, 0.0f);
    EXPECT_LE(result, constraint.maxSize.Width() - 50.0f);
}

/**
 * @tc.name: CalculateContentWidth011
 * @tc.desc: Test CalculateContentWidth with API 11+ and WRAP_CONTENT policy combined.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTestTwo, CalculateContentWidth011, TestSize.Level1)
{
    SetupTextFieldTest();
    auto layoutProperty = layoutWrapper_->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    CalcSize calcMinSize(CalcLength(150.0f), CalcLength(50.0f));
    layoutProperty->UpdateCalcMinSize(calcMinSize);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::WRAP_CONTENT, true);

    auto algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);
    SetAutoWidthForTest(algorithm, false);
    SetParagraphForTest(
        algorithm, CreateMockParagraph({ .maxWidth = 350.0f, .longestLineWithIndent = 300.0f, .needLayout = true }));

    auto constraint = CreateContentConstraint({ .maxWidth = 400.0f });
    float result = algorithm->CalculateContentWidth(constraint, AceType::RawPtr(layoutWrapper_), 0.0f);
    EXPECT_GT(result, 0.0f);
    EXPECT_LE(result, constraint.maxSize.Width());
}

/**
 * @tc.name: CalculateContentWidth012
 * @tc.desc: Test CalculateContentWidth with longestLine > textFieldWidth.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTestTwo, CalculateContentWidth012, TestSize.Level1)
{
    SetupTextFieldTest();

    auto algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);
    SetAutoWidthForTest(algorithm, false);
    SetParagraphForTest(
        algorithm, CreateMockParagraph({ .maxWidth = 180.0f, .longestLineWithIndent = 350.0f, .needLayout = true }));

    auto constraint = CreateContentConstraint({ .minWidth = 50.0f, .maxWidth = 200.0f });
    float result = algorithm->CalculateContentWidth(constraint, AceType::RawPtr(layoutWrapper_), 0.0f);
    EXPECT_GT(result, 0.0f);
    EXPECT_LE(result, constraint.maxSize.Width());
}

/**
 * @tc.name: CalculateContentWidth013
 * @tc.desc: Test CalculateContentWidth with longestLine < textFieldWidth.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTestTwo, CalculateContentWidth013, TestSize.Level1)
{
    SetupTextFieldTest();

    auto algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);
    SetAutoWidthForTest(algorithm, false);
    SetParagraphForTest(
        algorithm, CreateMockParagraph({ .maxWidth = 500.0f, .longestLineWithIndent = 100.0f, .needLayout = true }));

    auto constraint = CreateContentConstraint({ .minWidth = 50.0f, .maxWidth = 500.0f });
    float result = algorithm->CalculateContentWidth(constraint, AceType::RawPtr(layoutWrapper_), 0.0f);
    EXPECT_GT(result, 0.0f);
    EXPECT_LE(result, constraint.maxSize.Width());
}

/**
 * @tc.name: CalculateContentWidth014
 * @tc.desc: Test CalculateContentWidth with autoWidth_ = true.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTestTwo, CalculateContentWidth014, TestSize.Level1)
{
    SetupTextFieldTest();

    auto algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);
    SetAutoWidthForTest(algorithm, true);
    SetParagraphForTest(
        algorithm, CreateMockParagraph({ .maxWidth = 300.0f, .longestLineWithIndent = 250.0f, .needLayout = true }));

    auto constraint = CreateContentConstraint({ .maxWidth = 500.0f });
    float result = algorithm->CalculateContentWidth(constraint, AceType::RawPtr(layoutWrapper_), 0.0f);
    EXPECT_GE(result, INLINE_MIN_WIDTH_PX);
}

/**
 * @tc.name: CalculateContentWidth015
 * @tc.desc: Test CalculateContentWidth with API 11+ where longestLine > minWidth.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTestTwo, CalculateContentWidth015, TestSize.Level1)
{
    SetupTextFieldTest();
    auto layoutProperty = layoutWrapper_->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    CalcSize calcMinSize(CalcLength(50.0f), CalcLength(50.0f));
    layoutProperty->UpdateCalcMinSize(calcMinSize);

    auto algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);
    SetParagraphForTest(
        algorithm, CreateMockParagraph({ .maxWidth = 400.0f, .longestLineWithIndent = 300.0f, .needLayout = true }));

    auto constraint = CreateContentConstraint({ .maxWidth = 500.0f });
    float result = algorithm->CalculateContentWidth(constraint, AceType::RawPtr(layoutWrapper_), 0.0f);
    EXPECT_GT(result, 0.0f);
    EXPECT_LE(result, constraint.maxSize.Width());
}

/**
 * @tc.name: CalculateContentWidth016
 * @tc.desc: Test CalculateContentWidth with API 11+ where minWidth > longestLine.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTestTwo, CalculateContentWidth016, TestSize.Level1)
{
    SetupTextFieldTest();
    auto layoutProperty = layoutWrapper_->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    CalcSize calcMinSize(CalcLength(400.0f), CalcLength(50.0f));
    layoutProperty->UpdateCalcMinSize(calcMinSize);

    auto algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);
    SetParagraphForTest(
        algorithm, CreateMockParagraph({ .maxWidth = 400.0f, .longestLineWithIndent = 100.0f, .needLayout = true }));

    auto constraint = CreateContentConstraint({ .minWidth = 400.0f, .maxWidth = 500.0f });
    float result = algorithm->CalculateContentWidth(constraint, AceType::RawPtr(layoutWrapper_), 0.0f);
    EXPECT_GT(result, 0.0f);
    EXPECT_GE(result, 100.0f);
}

/**
 * @tc.name: CalculateContentWidth017
 * @tc.desc: Test CalculateContentWidth with API 11+ and FIX_AT_IDEAL_SIZE policy.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTestTwo, CalculateContentWidth017, TestSize.Level1)
{
    SetupTextFieldTest();
    auto layoutProperty = layoutWrapper_->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    CalcSize calcMinSize(CalcLength(150.0f), CalcLength(50.0f));
    layoutProperty->UpdateCalcMinSize(calcMinSize);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, true);

    auto algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);
    SetAutoWidthForTest(algorithm, false);
    SetParagraphForTest(
        algorithm, CreateMockParagraph({ .maxWidth = 350.0f, .longestLineWithIndent = 300.0f, .needLayout = true }));

    auto constraint = CreateContentConstraint({ .maxWidth = 400.0f });
    float result = algorithm->CalculateContentWidth(constraint, AceType::RawPtr(layoutWrapper_), 0.0f);
    EXPECT_GT(result, 0.0f);
    EXPECT_LE(result, constraint.maxSize.Width());
}

/**
 * @tc.name: CalculateContentWidth018
 * @tc.desc: Test CalculateContentWidth with autoWidth and contentWidth > longestLine.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTestTwo, CalculateContentWidth018, TestSize.Level1)
{
    SetupTextFieldTest();

    auto algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);
    SetAutoWidthForTest(algorithm, true);
    SetParagraphForTest(
        algorithm, CreateMockParagraph({ .maxWidth = 200.0f, .longestLineWithIndent = 150.0f, .needLayout = true }));

    auto constraint = CreateContentConstraint({ .minWidth = 50.0f, .maxWidth = 500.0f });
    float result = algorithm->CalculateContentWidth(constraint, AceType::RawPtr(layoutWrapper_), 0.0f);
    EXPECT_GE(result, INLINE_MIN_WIDTH_PX);
    EXPECT_LE(result, 150.0f);
}

/**
 * @tc.name: CalculateContentWidth019
 * @tc.desc: Test CalculateContentWidth with NO_MATCH policy.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTestTwo, CalculateContentWidth019, TestSize.Level1)
{
    SetupTextFieldTest();
    auto layoutProperty = layoutWrapper_->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, true);

    auto algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);
    SetAutoWidthForTest(algorithm, false);
    SetParagraphForTest(
        algorithm, CreateMockParagraph({ .maxWidth = 300.0f, .longestLineWithIndent = 250.0f, .needLayout = true }));

    auto constraint = CreateContentConstraint({});
    float result = algorithm->CalculateContentWidth(constraint, AceType::RawPtr(layoutWrapper_), 0.0f);
    EXPECT_GT(result, 0.0f);
    EXPECT_LE(result, constraint.maxSize.Width());
}

/**
 * @tc.name: CalculateContentWidth020
 * @tc.desc: Test CalculateContentWidth with API 11+ and large imageWidth.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTestTwo, CalculateContentWidth020, TestSize.Level1)
{
    SetupTextFieldTest();
    auto layoutProperty = layoutWrapper_->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    CalcSize calcMinSize(CalcLength(200.0f), CalcLength(50.0f));
    layoutProperty->UpdateCalcMinSize(calcMinSize);

    auto algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);
    SetParagraphForTest(
        algorithm, CreateMockParagraph({ .maxWidth = 400.0f, .longestLineWithIndent = 300.0f, .needLayout = true }));

    auto constraint = CreateContentConstraint({ .maxWidth = 500.0f });
    float result = algorithm->CalculateContentWidth(constraint, AceType::RawPtr(layoutWrapper_), 100.0f);
    EXPECT_GT(result, 0.0f);
    EXPECT_LE(result, constraint.maxSize.Width() - 100.0f);
}

/**
 * @tc.name: GetSuitableSize001
 * @tc.desc: Test GetSuitableSize when HasFocus and IsInlineMode are both false.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTestTwo, GetSuitableSize001, TestSize.Level1)
{
    SetupTextFieldTest();
    auto algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    SizeF maxSize(300.0f, 100.0f);
    float originalWidth = maxSize.Width();
    auto focusHub = pattern_->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->currentFocus_ = false;

    algorithm->GetSuitableSize(maxSize, AceType::RawPtr(layoutWrapper_));
    EXPECT_EQ(maxSize.Width(), originalWidth);
}

/**
 * @tc.name: GetSuitableSize002
 * @tc.desc: Test GetSuitableSize when HasFocus is true but IsInlineMode is false.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTestTwo, GetSuitableSize002, TestSize.Level1)
{
    SetupTextFieldTest();
    auto algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    SizeF maxSize(300.0f, 100.0f);
    float originalWidth = maxSize.Width();
    auto focusHub = pattern_->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->currentFocus_ = true;

    algorithm->GetSuitableSize(maxSize, AceType::RawPtr(layoutWrapper_));
    EXPECT_EQ(maxSize.Width(), originalWidth);
}

/**
 * @tc.name: GetSuitableSize003
 * @tc.desc: Test GetSuitableSize when HasFocus is true and IsInlineMode is true.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTestTwo, GetSuitableSize003, TestSize.Level1)
{
    SetupTextFieldTest(DEFAULT_TEXT, [](TextFieldModelNG& model) { model.SetInputStyle(InputStyle::INLINE); });
    auto paintProperty = frameNode_->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_EQ(paintProperty->GetInputStyleValue(InputStyle::DEFAULT), InputStyle::INLINE);

    auto algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    SizeF maxSize(300.0f, 100.0f);
    float originalWidth = maxSize.Width();
    auto focusHub = pattern_->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->currentFocus_ = true;

    algorithm->GetSuitableSize(maxSize, AceType::RawPtr(layoutWrapper_));
    EXPECT_LT(maxSize.Width(), originalWidth);
    EXPECT_GT(maxSize.Width(), 0.0f);
}

/**
 * @tc.name: GetSuitableSize004
 * @tc.desc: Test GetSuitableSize with inline style but not focused.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTestTwo, GetSuitableSize004, TestSize.Level1)
{
    SetupTextFieldTest(DEFAULT_TEXT, [](TextFieldModelNG& model) { model.SetInputStyle(InputStyle::INLINE); });

    auto algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    SizeF maxSize(300.0f, 100.0f);
    float originalWidth = maxSize.Width();
    auto focusHub = pattern_->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->currentFocus_ = false;

    algorithm->GetSuitableSize(maxSize, AceType::RawPtr(layoutWrapper_));
    EXPECT_EQ(maxSize.Width(), originalWidth);
}

/**
 * @tc.name: IsNeedAdaptFontSize001
 * @tc.desc: Test IsNeedAdaptFontSize when GetAdaptTextSize returns false.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTestTwo, IsNeedAdaptFontSize001, TestSize.Level1)
{
    SetupTextFieldTest();
    auto textInputLayoutAlgorithm = AceType::DynamicCast<TextInputLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    ASSERT_NE(textInputLayoutAlgorithm, nullptr);

    TextStyle textStyle;
    textStyle.SetAdaptTextSize(false);
    auto textFieldLayoutProperty = frameNode_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);

    auto constraint = CreateContentConstraint({});
    EXPECT_FALSE(textInputLayoutAlgorithm->IsNeedAdaptFontSize(textStyle, textFieldLayoutProperty, constraint));
}

/**
 * @tc.name: IsNeedAdaptFontSize002
 * @tc.desc: Test IsNeedAdaptFontSize when adaptivePolicy is invalid.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTestTwo, IsNeedAdaptFontSize002, TestSize.Level1)
{
    SetupTextFieldTest();
    auto textInputLayoutAlgorithm = AceType::DynamicCast<TextInputLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    ASSERT_NE(textInputLayoutAlgorithm, nullptr);

    TextStyle textStyle;
    textStyle.SetAdaptTextSize(true);
    textStyle.SetAdaptMinFontSize(Dimension(10.0f, DimensionUnit::FP));
    textStyle.SetAdaptMaxFontSize(Dimension(30.0f, DimensionUnit::FP));

    auto textFieldLayoutProperty = frameNode_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);
    textFieldLayoutProperty->UpdateHeightAdaptivePolicy(static_cast<TextHeightAdaptivePolicy>(100));

    auto constraint = CreateContentConstraint({});
    EXPECT_FALSE(textInputLayoutAlgorithm->IsNeedAdaptFontSize(textStyle, textFieldLayoutProperty, constraint));
}

/**
 * @tc.name: IsNeedAdaptFontSize003
 * @tc.desc: Test IsNeedAdaptFontSize when minFontSize <= 0.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTestTwo, IsNeedAdaptFontSize003, TestSize.Level1)
{
    SetupTextFieldTest();
    auto textInputLayoutAlgorithm = AceType::DynamicCast<TextInputLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    ASSERT_NE(textInputLayoutAlgorithm, nullptr);

    TextStyle textStyle;
    textStyle.SetAdaptTextSize(true);
    textStyle.SetAdaptMinFontSize(Dimension(0.0f, DimensionUnit::FP));
    textStyle.SetAdaptMaxFontSize(Dimension(30.0f, DimensionUnit::FP));

    auto textFieldLayoutProperty = frameNode_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);

    auto constraint = CreateContentConstraint({});
    EXPECT_FALSE(textInputLayoutAlgorithm->IsNeedAdaptFontSize(textStyle, textFieldLayoutProperty, constraint));
}

/**
 * @tc.name: IsNeedAdaptFontSize004
 * @tc.desc: Test IsNeedAdaptFontSize when maxFontSize < minFontSize.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTestTwo, IsNeedAdaptFontSize004, TestSize.Level1)
{
    SetupTextFieldTest();
    auto textInputLayoutAlgorithm = AceType::DynamicCast<TextInputLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    ASSERT_NE(textInputLayoutAlgorithm, nullptr);

    TextStyle textStyle;
    textStyle.SetAdaptTextSize(true);
    textStyle.SetAdaptMinFontSize(Dimension(30.0f, DimensionUnit::FP));
    textStyle.SetAdaptMaxFontSize(Dimension(10.0f, DimensionUnit::FP));

    auto textFieldLayoutProperty = frameNode_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);

    auto constraint = CreateContentConstraint({});
    EXPECT_FALSE(textInputLayoutAlgorithm->IsNeedAdaptFontSize(textStyle, textFieldLayoutProperty, constraint));
}

/**
 * @tc.name: IsNeedAdaptFontSize005
 * @tc.desc: Test IsNeedAdaptFontSize with all valid conditions.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTestTwo, IsNeedAdaptFontSize005, TestSize.Level1)
{
    SetupTextFieldTest();
    auto textInputLayoutAlgorithm = AceType::DynamicCast<TextInputLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    ASSERT_NE(textInputLayoutAlgorithm, nullptr);

    TextStyle textStyle;
    textStyle.SetAdaptTextSize(true);
    textStyle.SetAdaptMinFontSize(Dimension(10.0f, DimensionUnit::FP));
    textStyle.SetAdaptMaxFontSize(Dimension(30.0f, DimensionUnit::FP));

    auto textFieldLayoutProperty = frameNode_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);

    auto constraint = CreateContentConstraint({});
    EXPECT_TRUE(textInputLayoutAlgorithm->IsNeedAdaptFontSize(textStyle, textFieldLayoutProperty, constraint));
}

/**
 * @tc.name: IsNeedAdaptFontSize006
 * @tc.desc: Test IsNeedAdaptFontSize with MAX_LINES_FIRST policy.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTestTwo, IsNeedAdaptFontSize006, TestSize.Level1)
{
    SetupTextFieldTest(DEFAULT_TEXT,
        [](TextFieldModelNG& model) { model.SetHeightAdaptivePolicy(TextHeightAdaptivePolicy::MAX_LINES_FIRST); });
    auto textInputLayoutAlgorithm = AceType::DynamicCast<TextInputLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    ASSERT_NE(textInputLayoutAlgorithm, nullptr);

    TextStyle textStyle;
    textStyle.SetAdaptTextSize(true);
    textStyle.SetAdaptMinFontSize(Dimension(10.0f, DimensionUnit::FP));
    textStyle.SetAdaptMaxFontSize(Dimension(30.0f, DimensionUnit::FP));

    auto textFieldLayoutProperty = frameNode_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);

    auto constraint = CreateContentConstraint({});
    EXPECT_TRUE(textInputLayoutAlgorithm->IsNeedAdaptFontSize(textStyle, textFieldLayoutProperty, constraint));
}

/**
 * @tc.name: IsNeedAdaptFontSize007
 * @tc.desc: Test IsNeedAdaptFontSize with MIN_FONT_SIZE_FIRST policy.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTestTwo, IsNeedAdaptFontSize007, TestSize.Level1)
{
    SetupTextFieldTest(DEFAULT_TEXT,
        [](TextFieldModelNG& model) { model.SetHeightAdaptivePolicy(TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST); });
    auto textInputLayoutAlgorithm = AceType::DynamicCast<TextInputLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    ASSERT_NE(textInputLayoutAlgorithm, nullptr);

    TextStyle textStyle;
    textStyle.SetAdaptTextSize(true);
    textStyle.SetAdaptMinFontSize(Dimension(10.0f, DimensionUnit::FP));
    textStyle.SetAdaptMaxFontSize(Dimension(30.0f, DimensionUnit::FP));

    auto textFieldLayoutProperty = frameNode_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);

    auto constraint = CreateContentConstraint({});
    EXPECT_TRUE(textInputLayoutAlgorithm->IsNeedAdaptFontSize(textStyle, textFieldLayoutProperty, constraint));
}

/**
 * @tc.name: IsNeedAdaptFontSize008
 * @tc.desc: Test IsNeedAdaptFontSize with LAYOUT_CONSTRAINT_FIRST policy.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTestTwo, IsNeedAdaptFontSize008, TestSize.Level1)
{
    SetupTextFieldTest(DEFAULT_TEXT, [](TextFieldModelNG& model) {
        model.SetHeightAdaptivePolicy(TextHeightAdaptivePolicy::LAYOUT_CONSTRAINT_FIRST);
    });
    auto textInputLayoutAlgorithm = AceType::DynamicCast<TextInputLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    ASSERT_NE(textInputLayoutAlgorithm, nullptr);

    TextStyle textStyle;
    textStyle.SetAdaptTextSize(true);
    textStyle.SetAdaptMinFontSize(Dimension(10.0f, DimensionUnit::FP));
    textStyle.SetAdaptMaxFontSize(Dimension(30.0f, DimensionUnit::FP));

    auto textFieldLayoutProperty = frameNode_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);

    auto constraint = CreateContentConstraint({});
    EXPECT_TRUE(textInputLayoutAlgorithm->IsNeedAdaptFontSize(textStyle, textFieldLayoutProperty, constraint));
}

/**
 * @tc.name: IsNeedAdaptFontSize009
 * @tc.desc: Test IsNeedAdaptFontSize with valid policy but GetAdaptTextSize false.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTestTwo, IsNeedAdaptFontSize009, TestSize.Level1)
{
    SetupTextFieldTest(DEFAULT_TEXT,
        [](TextFieldModelNG& model) { model.SetHeightAdaptivePolicy(TextHeightAdaptivePolicy::MAX_LINES_FIRST); });
    auto textInputLayoutAlgorithm = AceType::DynamicCast<TextInputLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    ASSERT_NE(textInputLayoutAlgorithm, nullptr);

    TextStyle textStyle;
    textStyle.SetAdaptTextSize(false);

    auto textFieldLayoutProperty = frameNode_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);

    auto constraint = CreateContentConstraint({});
    EXPECT_FALSE(textInputLayoutAlgorithm->IsNeedAdaptFontSize(textStyle, textFieldLayoutProperty, constraint));
}

/**
 * @tc.name: IsNeedAdaptFontSize010
 * @tc.desc: Test IsNeedAdaptFontSize with equal minFontSize and maxFontSize.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTestTwo, IsNeedAdaptFontSize010, TestSize.Level1)
{
    SetupTextFieldTest();
    auto textInputLayoutAlgorithm = AceType::DynamicCast<TextInputLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    ASSERT_NE(textInputLayoutAlgorithm, nullptr);

    TextStyle textStyle;
    textStyle.SetAdaptTextSize(true);
    textStyle.SetAdaptMinFontSize(Dimension(20.0f, DimensionUnit::FP));
    textStyle.SetAdaptMaxFontSize(Dimension(20.0f, DimensionUnit::FP));

    auto textFieldLayoutProperty = frameNode_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);

    auto constraint = CreateContentConstraint({});
    EXPECT_TRUE(textInputLayoutAlgorithm->IsNeedAdaptFontSize(textStyle, textFieldLayoutProperty, constraint));
}

/**
 * @tc.name: IsNeedAdaptFontSize011
 * @tc.desc: Test IsNeedAdaptFontSize with negative minFontSize.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTestTwo, IsNeedAdaptFontSize011, TestSize.Level1)
{
    SetupTextFieldTest();
    auto textInputLayoutAlgorithm = AceType::DynamicCast<TextInputLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    ASSERT_NE(textInputLayoutAlgorithm, nullptr);

    TextStyle textStyle;
    textStyle.SetAdaptTextSize(true);
    textStyle.SetAdaptMinFontSize(Dimension(-10.0f, DimensionUnit::FP));
    textStyle.SetAdaptMaxFontSize(Dimension(30.0f, DimensionUnit::FP));

    auto textFieldLayoutProperty = frameNode_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);

    auto constraint = CreateContentConstraint({});
    EXPECT_FALSE(textInputLayoutAlgorithm->IsNeedAdaptFontSize(textStyle, textFieldLayoutProperty, constraint));
}

/**
 * @tc.name: UpdatePlaceholderTextStyleMore001
 * @tc.desc: Test UpdatePlaceholderTextStyleMore with empty placeholder and HasAdaptMinFontSize.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTestTwo, UpdatePlaceholderTextStyleMore001, TestSize.Level1)
{
    SetupTextFieldTest(
        "", [](TextFieldModelNG& model) { model.SetAdaptMinFontSize(Dimension(10.0f, DimensionUnit::FP)); });
    auto pipeline = frameNode_->GetContext();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<TextFieldTheme>();
    ASSERT_NE(theme, nullptr);

    TextStyle placeholderTextStyle;
    auto layoutProperty = frameNode_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    TextFieldLayoutAlgorithm::UpdatePlaceholderTextStyleMore(
        frameNode_, layoutProperty, theme, placeholderTextStyle, false);

    EXPECT_EQ(placeholderTextStyle.GetAdaptMinFontSize(), Dimension(10.0f, DimensionUnit::FP));
}

/**
 * @tc.name: UpdatePlaceholderTextStyleMore002
 * @tc.desc: Test UpdatePlaceholderTextStyleMore with empty placeholder and HasAdaptMaxFontSize.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTestTwo, UpdatePlaceholderTextStyleMore002, TestSize.Level1)
{
    SetupTextFieldTest(
        "", [](TextFieldModelNG& model) { model.SetAdaptMaxFontSize(Dimension(30.0f, DimensionUnit::FP)); });
    auto pipeline = frameNode_->GetContext();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<TextFieldTheme>();
    ASSERT_NE(theme, nullptr);

    TextStyle placeholderTextStyle;
    auto layoutProperty = frameNode_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    TextFieldLayoutAlgorithm::UpdatePlaceholderTextStyleMore(
        frameNode_, layoutProperty, theme, placeholderTextStyle, false);

    EXPECT_EQ(placeholderTextStyle.GetAdaptMaxFontSize(), Dimension(30.0f, DimensionUnit::FP));
}

/**
 * @tc.name: UpdatePlaceholderTextStyleMore003
 * @tc.desc: Test UpdatePlaceholderTextStyleMore with empty placeholder and both AdaptMinFontSize and AdaptMaxFontSize.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTestTwo, UpdatePlaceholderTextStyleMore003, TestSize.Level1)
{
    SetupTextFieldTest("", [](TextFieldModelNG& model) {
        model.SetAdaptMinFontSize(Dimension(10.0f, DimensionUnit::FP));
        model.SetAdaptMaxFontSize(Dimension(30.0f, DimensionUnit::FP));
    });
    auto pipeline = frameNode_->GetContext();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<TextFieldTheme>();
    ASSERT_NE(theme, nullptr);

    TextStyle placeholderTextStyle;
    auto layoutProperty = frameNode_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    TextFieldLayoutAlgorithm::UpdatePlaceholderTextStyleMore(
        frameNode_, layoutProperty, theme, placeholderTextStyle, false);

    EXPECT_EQ(placeholderTextStyle.GetAdaptMinFontSize(), Dimension(10.0f, DimensionUnit::FP));
    EXPECT_EQ(placeholderTextStyle.GetAdaptMaxFontSize(), Dimension(30.0f, DimensionUnit::FP));
}

/**
 * @tc.name: UpdatePlaceholderTextStyleMore004
 * @tc.desc: Test UpdatePlaceholderTextStyleMore with non-empty placeholder, AdaptMinFontSize should not be set.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTestTwo, UpdatePlaceholderTextStyleMore004, TestSize.Level1)
{
    SetupTextFieldTest(DEFAULT_TEXT, [](TextFieldModelNG& model) {
        model.SetAdaptMinFontSize(Dimension(10.0f, DimensionUnit::FP));
        model.SetAdaptMaxFontSize(Dimension(30.0f, DimensionUnit::FP));
    });
    auto pipeline = frameNode_->GetContext();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<TextFieldTheme>();
    ASSERT_NE(theme, nullptr);

    TextStyle placeholderTextStyle;
    auto layoutProperty = frameNode_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdatePlaceholder(u"test placeholder");

    TextFieldLayoutAlgorithm::UpdatePlaceholderTextStyleMore(
        frameNode_, layoutProperty, theme, placeholderTextStyle, false);

    EXPECT_NE(placeholderTextStyle.GetAdaptMinFontSize(), Dimension(10.0f, DimensionUnit::FP));
}

/**
 * @tc.name: UpdatePlaceholderTextStyleMore005
 * @tc.desc: Test UpdatePlaceholderTextStyleMore with password mode, should return early without setting line spacing.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTestTwo, UpdatePlaceholderTextStyleMore005, TestSize.Level1)
{
    SetupTextFieldTest("", [](TextFieldModelNG& model) { model.SetType(TextInputType::VISIBLE_PASSWORD); });
    auto pipeline = frameNode_->GetContext();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<TextFieldTheme>();
    ASSERT_NE(theme, nullptr);

    TextStyle placeholderTextStyle;
    auto layoutProperty = frameNode_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    Dimension lineSpacingBefore = placeholderTextStyle.GetLineSpacing();
    TextFieldLayoutAlgorithm::UpdatePlaceholderTextStyleMore(
        frameNode_, layoutProperty, theme, placeholderTextStyle, false);

    EXPECT_EQ(placeholderTextStyle.GetLineSpacing(), lineSpacingBefore);
}

/**
 * @tc.name: UpdatePlaceholderTextStyleMore006
 * @tc.desc: Test UpdatePlaceholderTextStyleMore with HasLineHeight and percent unit.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTestTwo, UpdatePlaceholderTextStyleMore006, TestSize.Level1)
{
    SetupTextFieldTest("");
    auto pipeline = frameNode_->GetContext();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<TextFieldTheme>();
    ASSERT_NE(theme, nullptr);

    TextStyle placeholderTextStyle;
    auto layoutProperty = frameNode_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    Dimension lineHeightPercent(150.0f, DimensionUnit::PERCENT);
    layoutProperty->UpdateLineHeight(lineHeightPercent);

    TextFieldLayoutAlgorithm::UpdatePlaceholderTextStyleMore(
        frameNode_, layoutProperty, theme, placeholderTextStyle, false);

    EXPECT_TRUE(placeholderTextStyle.HasHeightOverride());
}

/**
 * @tc.name: UpdatePlaceholderTextStyleMore007
 * @tc.desc: Test UpdatePlaceholderTextStyleMore with HasLineHeight and non-percent unit.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTestTwo, UpdatePlaceholderTextStyleMore007, TestSize.Level1)
{
    SetupTextFieldTest("");
    auto pipeline = frameNode_->GetContext();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<TextFieldTheme>();
    ASSERT_NE(theme, nullptr);

    TextStyle placeholderTextStyle;
    auto layoutProperty = frameNode_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    Dimension lineHeightPx(30.0f, DimensionUnit::PX);
    layoutProperty->UpdateLineHeight(lineHeightPx);

    TextFieldLayoutAlgorithm::UpdatePlaceholderTextStyleMore(
        frameNode_, layoutProperty, theme, placeholderTextStyle, false);

    EXPECT_TRUE(placeholderTextStyle.HasHeightOverride());
}

/**
 * @tc.name: UpdatePlaceholderTextStyleMore008
 * @tc.desc: Test UpdatePlaceholderTextStyleMore with HasMaxFontScale.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTestTwo, UpdatePlaceholderTextStyleMore008, TestSize.Level1)
{
    SetupTextFieldTest("");
    auto pipeline = frameNode_->GetContext();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<TextFieldTheme>();
    ASSERT_NE(theme, nullptr);

    TextStyle placeholderTextStyle;
    auto layoutProperty = frameNode_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    float maxFontScale = 2.0f;
    layoutProperty->UpdateMaxFontScale(maxFontScale);

    TextFieldLayoutAlgorithm::UpdatePlaceholderTextStyleMore(
        frameNode_, layoutProperty, theme, placeholderTextStyle, false);

    EXPECT_TRUE(layoutProperty->HasMaxFontScale());
}

/**
 * @tc.name: UpdatePlaceholderTextStyleMore009
 * @tc.desc: Test UpdatePlaceholderTextStyleMore with HasMinFontScale.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTestTwo, UpdatePlaceholderTextStyleMore009, TestSize.Level1)
{
    SetupTextFieldTest("");
    auto pipeline = frameNode_->GetContext();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<TextFieldTheme>();
    ASSERT_NE(theme, nullptr);

    TextStyle placeholderTextStyle;
    auto layoutProperty = frameNode_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    float minFontScale = 0.5f;
    layoutProperty->UpdateMinFontScale(minFontScale);

    TextFieldLayoutAlgorithm::UpdatePlaceholderTextStyleMore(
        frameNode_, layoutProperty, theme, placeholderTextStyle, false);

    EXPECT_TRUE(layoutProperty->HasMinFontScale());
}

/**
 * @tc.name: UpdatePlaceholderTextStyleMore010
 * @tc.desc: Test UpdatePlaceholderTextStyleMore with both HasMaxFontScale and HasMinFontScale.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTestTwo, UpdatePlaceholderTextStyleMore010, TestSize.Level1)
{
    SetupTextFieldTest("");
    auto pipeline = frameNode_->GetContext();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<TextFieldTheme>();
    ASSERT_NE(theme, nullptr);

    TextStyle placeholderTextStyle;
    auto layoutProperty = frameNode_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    float maxFontScale = 2.0f;
    float minFontScale = 0.5f;
    layoutProperty->UpdateMaxFontScale(maxFontScale);
    layoutProperty->UpdateMinFontScale(minFontScale);

    TextFieldLayoutAlgorithm::UpdatePlaceholderTextStyleMore(
        frameNode_, layoutProperty, theme, placeholderTextStyle, false);

    EXPECT_TRUE(layoutProperty->HasMaxFontScale());
    EXPECT_TRUE(layoutProperty->HasMinFontScale());
}

/**
 * @tc.name: UpdatePlaceholderTextStyleMore011
 * @tc.desc: Test UpdatePlaceholderTextStyleMore sets line spacing from theme.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTestTwo, UpdatePlaceholderTextStyleMore011, TestSize.Level1)
{
    SetupTextFieldTest("");
    auto pipeline = frameNode_->GetContext();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<TextFieldTheme>();
    ASSERT_NE(theme, nullptr);

    TextStyle placeholderTextStyle;
    auto layoutProperty = frameNode_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    TextFieldLayoutAlgorithm::UpdatePlaceholderTextStyleMore(
        frameNode_, layoutProperty, theme, placeholderTextStyle, false);

    EXPECT_EQ(placeholderTextStyle.GetLineSpacing(), theme->GetPlaceholderLineSpacing());
}

/**
 * @tc.name: UpdatePlaceholderTextStyleMore012
 * @tc.desc: Test UpdatePlaceholderTextStyleMore with all properties set together.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTestTwo, UpdatePlaceholderTextStyleMore012, TestSize.Level1)
{
    SetupTextFieldTest("", [](TextFieldModelNG& model) {
        model.SetAdaptMinFontSize(Dimension(10.0f, DimensionUnit::FP));
        model.SetAdaptMaxFontSize(Dimension(30.0f, DimensionUnit::FP));
    });
    auto pipeline = frameNode_->GetContext();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<TextFieldTheme>();
    ASSERT_NE(theme, nullptr);

    TextStyle placeholderTextStyle;
    auto layoutProperty = frameNode_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    Dimension lineHeightPx(30.0f, DimensionUnit::PX);
    layoutProperty->UpdateLineHeight(lineHeightPx);
    layoutProperty->UpdateMaxFontScale(2.0f);
    layoutProperty->UpdateMinFontScale(0.5f);

    TextFieldLayoutAlgorithm::UpdatePlaceholderTextStyleMore(
        frameNode_, layoutProperty, theme, placeholderTextStyle, false);

    EXPECT_EQ(placeholderTextStyle.GetAdaptMinFontSize(), Dimension(10.0f, DimensionUnit::FP));
    EXPECT_EQ(placeholderTextStyle.GetAdaptMaxFontSize(), Dimension(30.0f, DimensionUnit::FP));
    EXPECT_TRUE(placeholderTextStyle.HasHeightOverride());
    EXPECT_EQ(placeholderTextStyle.GetLineSpacing(), theme->GetPlaceholderLineSpacing());
}

/**
 * @tc.name: UpdatePlaceholderTextStyleMore013
 * @tc.desc: Test UpdatePlaceholderTextStyleMore with isDisabled parameter true.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTestTwo, UpdatePlaceholderTextStyleMore013, TestSize.Level1)
{
    SetupTextFieldTest("");
    auto pipeline = frameNode_->GetContext();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<TextFieldTheme>();
    ASSERT_NE(theme, nullptr);

    TextStyle placeholderTextStyle;
    auto layoutProperty = frameNode_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    TextFieldLayoutAlgorithm::UpdatePlaceholderTextStyleMore(
        frameNode_, layoutProperty, theme, placeholderTextStyle, true);

    EXPECT_EQ(placeholderTextStyle.GetLineSpacing(), theme->GetPlaceholderLineSpacing());
}

/**
 * @tc.name: UpdatePlaceholderTextStyleMore014
 * @tc.desc: Test UpdatePlaceholderTextStyleMore with line height in VP unit.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTestTwo, UpdatePlaceholderTextStyleMore014, TestSize.Level1)
{
    SetupTextFieldTest("");
    auto pipeline = frameNode_->GetContext();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<TextFieldTheme>();
    ASSERT_NE(theme, nullptr);

    TextStyle placeholderTextStyle;
    auto layoutProperty = frameNode_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    Dimension lineHeightVp(20.0f, DimensionUnit::VP);
    layoutProperty->UpdateLineHeight(lineHeightVp);

    TextFieldLayoutAlgorithm::UpdatePlaceholderTextStyleMore(
        frameNode_, layoutProperty, theme, placeholderTextStyle, false);

    EXPECT_TRUE(placeholderTextStyle.HasHeightOverride());
}

/**
 * @tc.name: UpdatePlaceholderTextStyleMore015
 * @tc.desc: Test UpdatePlaceholderTextStyleMore with line height in FP unit.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTestTwo, UpdatePlaceholderTextStyleMore015, TestSize.Level1)
{
    SetupTextFieldTest("");
    auto pipeline = frameNode_->GetContext();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<TextFieldTheme>();
    ASSERT_NE(theme, nullptr);

    TextStyle placeholderTextStyle;
    auto layoutProperty = frameNode_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    Dimension lineHeightFp(18.0f, DimensionUnit::FP);
    layoutProperty->UpdateLineHeight(lineHeightFp);

    TextFieldLayoutAlgorithm::UpdatePlaceholderTextStyleMore(
        frameNode_, layoutProperty, theme, placeholderTextStyle, false);

    EXPECT_TRUE(placeholderTextStyle.HasHeightOverride());
}

} // namespace OHOS::Ace::NG
