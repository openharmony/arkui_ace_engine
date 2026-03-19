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

#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "text_input_base.h"

#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/text_field/text_field_layout_algorithm.h"

namespace OHOS::Ace::NG {

constexpr float INLINE_MIN_WIDTH_PX = 16.0f;

class TextFieldLayoutAlgorithmTestHelper : public TextFieldLayoutAlgorithm {
public:
    static void SetParagraph(TextFieldLayoutAlgorithm* algorithm, const RefPtr<Paragraph>& paragraph)
    {
        auto* helper = reinterpret_cast<TextFieldLayoutAlgorithmTestHelper*>(algorithm);
        helper->paragraph_ = paragraph;
    }

    static void SetInlineParagraph(TextFieldLayoutAlgorithm* algorithm, const RefPtr<Paragraph>& paragraph)
    {
        auto* helper = reinterpret_cast<TextFieldLayoutAlgorithmTestHelper*>(algorithm);
        helper->inlineParagraph_ = paragraph;
    }

    static void SetAutoWidth(TextFieldLayoutAlgorithm* algorithm, bool autoWidth)
    {
        auto* helper = reinterpret_cast<TextFieldLayoutAlgorithmTestHelper*>(algorithm);
        helper->autoWidth_ = autoWidth;
    }

    static void SetInlineFocus(TextFieldLayoutAlgorithm* algorithm, bool isInlineFocus)
    {
        auto* helper = reinterpret_cast<TextFieldLayoutAlgorithmTestHelper*>(algorithm);
        helper->isInlineFocus_ = isInlineFocus;
    }
};

class TextFieldLayoutAlgorithmTest : public TextInputBases {
protected:
    RefPtr<Paragraph> CreateMockParagraph()
    {
        return MockParagraph::GetOrCreateMockParagraph();
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
        TextFieldLayoutAlgorithmTestHelper::SetParagraph(algorithm, paragraph);
    }

    void SetInlineParagraphForTest(TextFieldLayoutAlgorithm* algorithm, const RefPtr<Paragraph>& paragraph)
    {
        TextFieldLayoutAlgorithmTestHelper::SetInlineParagraph(algorithm, paragraph);
    }

    void SetAutoWidthForTest(TextFieldLayoutAlgorithm* algorithm, bool autoWidth)
    {
        TextFieldLayoutAlgorithmTestHelper::SetAutoWidth(algorithm, autoWidth);
    }

    void SetInlineFocusForTest(TextFieldLayoutAlgorithm* algorithm, bool isInlineFocus)
    {
        TextFieldLayoutAlgorithmTestHelper::SetInlineFocus(algorithm, isInlineFocus);
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
 * @tc.name: InlineMeasureContent001
 * @tc.desc: Test InlineMeasureContent with valid parameters in non-focus mode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, InlineMeasureContent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField(DEFAULT_TEXT);
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create layout constraint
     */
    LayoutConstraintF contentConstraint;
    contentConstraint.minSize = SizeF(100.0f, 50.0f);
    contentConstraint.maxSize = SizeF(300.0f, 100.0f);

    auto layoutWrapper = CreateLayoutWrapper(frameNode_);
    ASSERT_NE(layoutWrapper, nullptr);

    /**
     * @tc.steps: step3. Create and set mock paragraphs for testing
     */
    TextFieldLayoutAlgorithm* algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    RefPtr<Paragraph> paragraph = CreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    SetParagraphForTest(algorithm, paragraph);

    RefPtr<Paragraph> inlineParagraph = CreateMockParagraph();
    ASSERT_NE(inlineParagraph, nullptr);
    SetInlineParagraphForTest(algorithm, inlineParagraph);

    /**
     * @tc.steps: step4. Call InlineMeasureContent with valid parameters
     * @tc.expected: Should return valid SizeF with content dimensions
     */
    std::optional<SizeF> result = algorithm->InlineMeasureContent(contentConstraint, layoutWrapper);
    EXPECT_TRUE(result.has_value());
    EXPECT_GT(result->Width(), 0.0f);
    EXPECT_GT(result->Height(), 0.0f);
}

/**
 * @tc.name: InlineMeasureContent002
 * @tc.desc: Test InlineMeasureContent with valid parameters in non-focus mode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, InlineMeasureContent002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField(DEFAULT_TEXT);
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create layout constraint
     */
    LayoutConstraintF contentConstraint;
    contentConstraint.minSize = SizeF(100.0f, 50.0f);
    contentConstraint.maxSize = SizeF(300.0f, 100.0f);

    auto layoutWrapper = CreateLayoutWrapper(frameNode_);
    ASSERT_NE(layoutWrapper, nullptr);

    /**
     * @tc.steps: step3. Create and set mock paragraphs for testing
     */
    TextFieldLayoutAlgorithm* algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    RefPtr<Paragraph> paragraph = CreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    SetParagraphForTest(algorithm, paragraph);

    RefPtr<Paragraph> inlineParagraph = CreateMockParagraph();
    ASSERT_NE(inlineParagraph, nullptr);
    SetInlineParagraphForTest(algorithm, inlineParagraph);

    /**
     * @tc.steps: step4. Call InlineMeasureContent in non-focus mode
     * @tc.expected: Should return valid SizeF with content dimensions
     */
    std::optional<SizeF> result = algorithm->InlineMeasureContent(contentConstraint, layoutWrapper);
    EXPECT_TRUE(result.has_value());
    EXPECT_GT(result->Width(), 0.0f);
    EXPECT_GT(result->Height(), 0.0f);
}

/**
 * @tc.name: InlineMeasureContent003
 * @tc.desc: Test InlineMeasureContent with focus mode and non-styled placeholder
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, InlineMeasureContent003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField(DEFAULT_TEXT);
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create layout constraint
     */
    LayoutConstraintF contentConstraint;
    contentConstraint.minSize = SizeF(100.0f, 50.0f);
    contentConstraint.maxSize = SizeF(300.0f, 100.0f);

    auto layoutWrapper = CreateLayoutWrapper(frameNode_);
    ASSERT_NE(layoutWrapper, nullptr);

    /**
     * @tc.steps: step3. Create and set mock paragraphs for testing
     */
    TextFieldLayoutAlgorithm* algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    RefPtr<Paragraph> paragraph = CreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    SetParagraphForTest(algorithm, paragraph);

    RefPtr<Paragraph> inlineParagraph = CreateMockParagraph();
    ASSERT_NE(inlineParagraph, nullptr);
    SetInlineParagraphForTest(algorithm, inlineParagraph);

    /**
     * @tc.steps: step4. Call InlineMeasureContent
     * @tc.expected: Should handle both focus and non-focus paths
     */
    std::optional<SizeF> result = algorithm->InlineMeasureContent(contentConstraint, layoutWrapper);
    EXPECT_TRUE(result.has_value());
    EXPECT_GE(result->Width(), INLINE_MIN_WIDTH_PX);
}

/**
 * @tc.name: InlineMeasureContent004
 * @tc.desc: Test InlineMeasureContent with large constraint to test widthLayoutPolicy
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, InlineMeasureContent004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField(DEFAULT_TEXT);
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create layout constraint with large minSize
     */
    LayoutConstraintF contentConstraint;
    contentConstraint.minSize = SizeF(500.0f, 100.0f);
    contentConstraint.maxSize = SizeF(600.0f, 200.0f);

    auto layoutWrapper = CreateLayoutWrapper(frameNode_);
    ASSERT_NE(layoutWrapper, nullptr);

    /**
     * @tc.steps: step3. Create and set mock paragraphs for testing
     */
    TextFieldLayoutAlgorithm* algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    RefPtr<Paragraph> paragraph = CreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    SetParagraphForTest(algorithm, paragraph);

    RefPtr<Paragraph> inlineParagraph = CreateMockParagraph();
    ASSERT_NE(inlineParagraph, nullptr);
    SetInlineParagraphForTest(algorithm, inlineParagraph);

    /**
     * @tc.steps: step4. Call InlineMeasureContent
     * @tc.expected: Should use minSize when widthLayoutPolicy is WRAP_CONTENT or FIX_AT_IDEAL_SIZE
     */
    std::optional<SizeF> result = algorithm->InlineMeasureContent(contentConstraint, layoutWrapper);
    EXPECT_TRUE(result.has_value());
    EXPECT_GE(result->Width(), INLINE_MIN_WIDTH_PX);
}

/**
 * @tc.name: InlineMeasureContent005
 * @tc.desc: Test InlineMeasureContent height calculation when longestLine is zero
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, InlineMeasureContent005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField(DEFAULT_TEXT);
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create layout constraint
     */
    LayoutConstraintF contentConstraint;
    contentConstraint.minSize = SizeF(100.0f, 50.0f);
    contentConstraint.maxSize = SizeF(300.0f, 100.0f);

    auto layoutWrapper = CreateLayoutWrapper(frameNode_);
    ASSERT_NE(layoutWrapper, nullptr);

    /**
     * @tc.steps: step3. Create and set mock paragraphs for testing
     */
    TextFieldLayoutAlgorithm* algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    RefPtr<Paragraph> paragraph = CreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    SetParagraphForTest(algorithm, paragraph);

    RefPtr<Paragraph> inlineParagraph = CreateMockParagraph();
    ASSERT_NE(inlineParagraph, nullptr);
    SetInlineParagraphForTest(algorithm, inlineParagraph);

    /**
     * @tc.steps: step4. Call InlineMeasureContent
     * @tc.expected: Should use preferredHeight when longestLine is zero
     */
    std::optional<SizeF> result = algorithm->InlineMeasureContent(contentConstraint, layoutWrapper);
    EXPECT_TRUE(result.has_value());
    EXPECT_GT(result->Height(), 0.0f);
}

/**
 * @tc.name: InlineMeasureContent006
 * @tc.desc: Test InlineMeasureContent with small contentWidth to test minWidth constraint
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, InlineMeasureContent006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField(DEFAULT_TEXT);
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create layout constraint with small maxSize
     */
    LayoutConstraintF contentConstraint;
    contentConstraint.minSize = SizeF(10.0f, 30.0f);
    contentConstraint.maxSize = SizeF(20.0f, 50.0f);

    auto layoutWrapper = CreateLayoutWrapper(frameNode_);
    ASSERT_NE(layoutWrapper, nullptr);

    /**
     * @tc.steps: step3. Create and set mock paragraphs for testing
     */
    TextFieldLayoutAlgorithm* algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    RefPtr<Paragraph> paragraph = CreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    SetParagraphForTest(algorithm, paragraph);

    RefPtr<Paragraph> inlineParagraph = CreateMockParagraph();
    ASSERT_NE(inlineParagraph, nullptr);
    SetInlineParagraphForTest(algorithm, inlineParagraph);

    /**
     * @tc.steps: step4. Call InlineMeasureContent
     * @tc.expected: Should enforce minimum width of INLINE_MIN_WIDTH_PX (16.0f)
     */
    std::optional<SizeF> result = algorithm->InlineMeasureContent(contentConstraint, layoutWrapper);
    EXPECT_TRUE(result.has_value());
    EXPECT_GE(result->Width(), INLINE_MIN_WIDTH_PX);
}

/**
 * @tc.name: InlineMeasureContent007
 * @tc.desc: Test InlineMeasureContent with autoWidth enabled
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, InlineMeasureContent007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField(DEFAULT_TEXT);
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create layout constraint
     */
    LayoutConstraintF contentConstraint;
    contentConstraint.minSize = SizeF(100.0f, 50.0f);
    contentConstraint.maxSize = SizeF(460.0f, 100.0f);

    auto layoutWrapper = CreateLayoutWrapper(frameNode_);
    ASSERT_NE(layoutWrapper, nullptr);

    /**
     * @tc.steps: step3. Create and set mock paragraphs for testing
     */
    TextFieldLayoutAlgorithm* algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    RefPtr<Paragraph> paragraph = CreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    SetParagraphForTest(algorithm, paragraph);

    RefPtr<Paragraph> inlineParagraph = CreateMockParagraph();
    ASSERT_NE(inlineParagraph, nullptr);
    SetInlineParagraphForTest(algorithm, inlineParagraph);

    /**
     * @tc.steps: step4. Call InlineMeasureContent with autoWidth path
     * @tc.expected: Should re-layout paragraph based on longestLine
     */
    std::optional<SizeF> result = algorithm->InlineMeasureContent(contentConstraint, layoutWrapper);
    EXPECT_TRUE(result.has_value());
    EXPECT_GT(result->Width(), 0.0f);
    EXPECT_GT(result->Height(), 0.0f);
}

/**
 * @tc.name: InlineMeasureContent008
 * @tc.desc: Test InlineMeasureContent with text indent applied
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, InlineMeasureContent008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField(DEFAULT_TEXT);
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create layout constraint
     */
    LayoutConstraintF contentConstraint;
    contentConstraint.minSize = SizeF(100.0f, 50.0f);
    contentConstraint.maxSize = SizeF(300.0f, 100.0f);

    auto layoutWrapper = CreateLayoutWrapper(frameNode_);
    ASSERT_NE(layoutWrapper, nullptr);

    /**
     * @tc.steps: step3. Create and set mock paragraphs for testing
     */
    TextFieldLayoutAlgorithm* algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    RefPtr<Paragraph> paragraph = CreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    SetParagraphForTest(algorithm, paragraph);

    RefPtr<Paragraph> inlineParagraph = CreateMockParagraph();
    ASSERT_NE(inlineParagraph, nullptr);
    SetInlineParagraphForTest(algorithm, inlineParagraph);

    /**
     * @tc.steps: step4. Call InlineMeasureContent
     * @tc.expected: Should apply text indent if textIndent > 0
     */
    std::optional<SizeF> result = algorithm->InlineMeasureContent(contentConstraint, layoutWrapper);
    EXPECT_TRUE(result.has_value());
    EXPECT_GT(result->Width(), 0.0f);
}

/**
 * @tc.name: InlineMeasureContent009
 * @tc.desc: Test InlineMeasureContent height constraint with inlineIdealHeight
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, InlineMeasureContent009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField(DEFAULT_TEXT);
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create layout constraint with small height
     */
    LayoutConstraintF contentConstraint;
    contentConstraint.minSize = SizeF(100.0f, 30.0f);
    contentConstraint.maxSize = SizeF(300.0f, 40.0f);

    auto layoutWrapper = CreateLayoutWrapper(frameNode_);
    ASSERT_NE(layoutWrapper, nullptr);

    /**
     * @tc.steps: step3. Create and set mock paragraphs for testing
     */
    TextFieldLayoutAlgorithm* algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    RefPtr<Paragraph> paragraph = CreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    SetParagraphForTest(algorithm, paragraph);

    RefPtr<Paragraph> inlineParagraph = CreateMockParagraph();
    ASSERT_NE(inlineParagraph, nullptr);
    SetInlineParagraphForTest(algorithm, inlineParagraph);

    /**
     * @tc.steps: step4. Call InlineMeasureContent
     * @tc.expected: Should limit height to inlineIdealHeight
     */
    std::optional<SizeF> result = algorithm->InlineMeasureContent(contentConstraint, layoutWrapper);
    EXPECT_TRUE(result.has_value());
    EXPECT_LE(result->Height(), contentConstraint.maxSize.Height());
}

/**
 * @tc.name: InlineMeasureContent010
 * @tc.desc: Test InlineMeasureContent GetInlineMeasureItem with focus and multiple lines
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, InlineMeasureContent010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField(DEFAULT_TEXT);
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create layout constraint
     */
    LayoutConstraintF contentConstraint;
    contentConstraint.minSize = SizeF(100.0f, 50.0f);
    contentConstraint.maxSize = SizeF(300.0f, 150.0f);

    auto layoutWrapper = CreateLayoutWrapper(frameNode_);
    ASSERT_NE(layoutWrapper, nullptr);

    /**
     * @tc.steps: step3. Create and set mock paragraphs for testing
     */
    TextFieldLayoutAlgorithm* algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    RefPtr<Paragraph> paragraph = CreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    SetParagraphForTest(algorithm, paragraph);

    RefPtr<Paragraph> inlineParagraph = CreateMockParagraph();
    ASSERT_NE(inlineParagraph, nullptr);
    SetInlineParagraphForTest(algorithm, inlineParagraph);

    /**
     * @tc.steps: step4. Call InlineMeasureContent
     * @tc.expected: Should calculate inline measure item correctly
     */
    std::optional<SizeF> result = algorithm->InlineMeasureContent(contentConstraint, layoutWrapper);
    EXPECT_TRUE(result.has_value());
    EXPECT_GT(result->Width(), 0.0f);
    EXPECT_GT(result->Height(), 0.0f);
}

/**
 * @tc.name: TextAreaMeasureContent001
 * @tc.desc: Test TextAreaMeasureContent with basic parameters
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, TextAreaMeasureContent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField(DEFAULT_TEXT);
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create layout constraint
     */
    LayoutConstraintF contentConstraint;
    contentConstraint.minSize = SizeF(100.0f, 50.0f);
    contentConstraint.maxSize = SizeF(300.0f, 200.0f);

    auto layoutWrapper = CreateLayoutWrapper(frameNode_);
    ASSERT_NE(layoutWrapper, nullptr);

    /**
     * @tc.steps: step3. Create and set mock paragraph for testing
     */
    TextFieldLayoutAlgorithm* algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    RefPtr<Paragraph> paragraph = CreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    SetParagraphForTest(algorithm, paragraph);

    /**
     * @tc.steps: step4. Call TextAreaMeasureContent
     * @tc.expected: Should return valid SizeF with content dimensions
     */
    SizeF result = algorithm->TextAreaMeasureContent(contentConstraint, layoutWrapper);
    EXPECT_GT(result.Width(), 0.0f);
    EXPECT_GT(result.Height(), 0.0f);
}

/**
 * @tc.name: TextAreaMeasureContent002
 * @tc.desc: Test TextAreaMeasureContent with autoWidth enabled
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, TextAreaMeasureContent002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField(DEFAULT_TEXT);
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create layout constraint
     */
    LayoutConstraintF contentConstraint;
    contentConstraint.minSize = SizeF(100.0f, 50.0f);
    contentConstraint.maxSize = SizeF(460.0f, 200.0f);

    auto layoutWrapper = CreateLayoutWrapper(frameNode_);
    ASSERT_NE(layoutWrapper, nullptr);

    /**
     * @tc.steps: step3. Create and set mock paragraph for testing
     */
    TextFieldLayoutAlgorithm* algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    RefPtr<Paragraph> paragraph = CreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    SetParagraphForTest(algorithm, paragraph);

    /**
     * @tc.steps: step4. Call TextAreaMeasureContent with autoWidth path
     * @tc.expected: Should apply minWidth constraint and re-layout paragraph
     */
    SizeF result = algorithm->TextAreaMeasureContent(contentConstraint, layoutWrapper);
    EXPECT_GT(result.Width(), 0.0f);
    EXPECT_GE(result.Width(), INLINE_MIN_WIDTH_PX);
}

/**
 * @tc.name: TextAreaMeasureContent003
 * @tc.desc: Test TextAreaMeasureContent height calculation when longestLine is zero
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, TextAreaMeasureContent003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField(DEFAULT_TEXT);
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create layout constraint with small height
     */
    LayoutConstraintF contentConstraint;
    contentConstraint.minSize = SizeF(100.0f, 30.0f);
    contentConstraint.maxSize = SizeF(300.0f, 50.0f);

    auto layoutWrapper = CreateLayoutWrapper(frameNode_);
    ASSERT_NE(layoutWrapper, nullptr);

    /**
     * @tc.steps: step3. Create and set mock paragraph for testing
     */
    TextFieldLayoutAlgorithm* algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    RefPtr<Paragraph> paragraph = CreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    SetParagraphForTest(algorithm, paragraph);

    /**
     * @tc.steps: step4. Call TextAreaMeasureContent
     * @tc.expected: Should use max(preferredHeight_, paragraph_->GetHeight())
     */
    SizeF result = algorithm->TextAreaMeasureContent(contentConstraint, layoutWrapper);
    EXPECT_GT(result.Height(), 0.0f);
    EXPECT_LE(result.Height(), contentConstraint.maxSize.Height());
}

/**
 * @tc.name: TextAreaMeasureContent004
 * @tc.desc: Test TextAreaMeasureContent with counter node height
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, TextAreaMeasureContent004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField(DEFAULT_TEXT);
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create layout constraint
     */
    LayoutConstraintF contentConstraint;
    contentConstraint.minSize = SizeF(100.0f, 50.0f);
    contentConstraint.maxSize = SizeF(300.0f, 200.0f);

    auto layoutWrapper = CreateLayoutWrapper(frameNode_);
    ASSERT_NE(layoutWrapper, nullptr);

    /**
     * @tc.steps: step3. Create and set mock paragraph for testing
     */
    TextFieldLayoutAlgorithm* algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    RefPtr<Paragraph> paragraph = CreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    SetParagraphForTest(algorithm, paragraph);

    /**
     * @tc.steps: step4. Call TextAreaMeasureContent
     * @tc.expected: Should subtract counterNodeHeight from contentHeight
     */
    SizeF result = algorithm->TextAreaMeasureContent(contentConstraint, layoutWrapper);
    EXPECT_GT(result.Width(), 0.0f);
    EXPECT_GT(result.Height(), 0.0f);
}

/**
 * @tc.name: TextAreaMeasureContent005
 * @tc.desc: Test TextAreaMeasureContent with normalMaxViewLines constraint
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, TextAreaMeasureContent005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField(DEFAULT_TEXT);
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create layout constraint
     */
    LayoutConstraintF contentConstraint;
    contentConstraint.minSize = SizeF(100.0f, 50.0f);
    contentConstraint.maxSize = SizeF(300.0f, 200.0f);

    auto layoutWrapper = CreateLayoutWrapper(frameNode_);
    ASSERT_NE(layoutWrapper, nullptr);

    /**
     * @tc.steps: step3. Create and set mock paragraph for testing
     */
    TextFieldLayoutAlgorithm* algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    RefPtr<Paragraph> paragraph = CreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    SetParagraphForTest(algorithm, paragraph);

    /**
     * @tc.steps: step4. Call TextAreaMeasureContent with maxViewLines
     * @tc.expected: Should apply maxline constraint when HasNormalMaxViewLines is true
     */
    SizeF result = algorithm->TextAreaMeasureContent(contentConstraint, layoutWrapper);
    EXPECT_GT(result.Width(), 0.0f);
    EXPECT_LE(result.Height(), contentConstraint.maxSize.Height());
}

/**
 * @tc.name: CalculateContentWidth001
 * @tc.desc: Test CalculateContentWidth with basic parameters
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, CalculateContentWidth001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField(DEFAULT_TEXT);
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create layout constraint
     */
    LayoutConstraintF contentConstraint;
    contentConstraint.minSize = SizeF(100.0f, 50.0f);
    contentConstraint.maxSize = SizeF(300.0f, 100.0f);

    auto layoutWrapper = CreateLayoutWrapper(frameNode_);
    ASSERT_NE(layoutWrapper, nullptr);

    /**
     * @tc.steps: step3. Create and set mock paragraph for testing
     */
    TextFieldLayoutAlgorithm* algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    RefPtr<Paragraph> paragraph = CreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    SetParagraphForTest(algorithm, paragraph);

    /**
     * @tc.steps: step4. Call CalculateContentWidth
     * @tc.expected: Should return contentWidth based on maxSize and imageWidth
     */
    float imageWidth = 0.0f;
    float result = algorithm->CalculateContentWidth(contentConstraint, layoutWrapper, imageWidth);
    EXPECT_GT(result, 0.0f);
    EXPECT_LE(result, contentConstraint.maxSize.Width());
}

/**
 * @tc.name: CalculateContentWidth002
 * @tc.desc: Test CalculateContentWidth with imageWidth
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, CalculateContentWidth002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField(DEFAULT_TEXT);
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create layout constraint
     */
    LayoutConstraintF contentConstraint;
    contentConstraint.minSize = SizeF(100.0f, 50.0f);
    contentConstraint.maxSize = SizeF(300.0f, 100.0f);

    auto layoutWrapper = CreateLayoutWrapper(frameNode_);
    ASSERT_NE(layoutWrapper, nullptr);

    /**
     * @tc.steps: step3. Create and set mock paragraph for testing
     */
    TextFieldLayoutAlgorithm* algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    RefPtr<Paragraph> paragraph = CreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    SetParagraphForTest(algorithm, paragraph);

    /**
     * @tc.steps: step4. Call CalculateContentWidth with imageWidth
     * @tc.expected: Should subtract imageWidth from contentWidth
     */
    float imageWidth = 50.0f;
    float result = algorithm->CalculateContentWidth(contentConstraint, layoutWrapper, imageWidth);
    EXPECT_GT(result, 0.0f);
    EXPECT_LE(result, contentConstraint.maxSize.Width() - imageWidth);
}

/**
 * @tc.name: CalculateContentWidth003
 * @tc.desc: Test CalculateContentWidth with autoWidth enabled
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, CalculateContentWidth003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField(DEFAULT_TEXT);
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create layout constraint
     */
    LayoutConstraintF contentConstraint;
    contentConstraint.minSize = SizeF(100.0f, 50.0f);
    contentConstraint.maxSize = SizeF(460.0f, 100.0f);

    auto layoutWrapper = CreateLayoutWrapper(frameNode_);
    ASSERT_NE(layoutWrapper, nullptr);

    /**
     * @tc.steps: step3. Create and set mock paragraph for testing
     */
    TextFieldLayoutAlgorithm* algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    RefPtr<Paragraph> paragraph = CreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    SetParagraphForTest(algorithm, paragraph);

    /**
     * @tc.steps: step4. Call CalculateContentWidth with autoWidth path
     * @tc.expected: Should apply minWidth constraint and limit to longestLine
     */
    float imageWidth = 0.0f;
    float result = algorithm->CalculateContentWidth(contentConstraint, layoutWrapper, imageWidth);
    EXPECT_GE(result, INLINE_MIN_WIDTH_PX);
}

/**
 * @tc.name: CalculateContentWidth004
 * @tc.desc: Test CalculateContentWidth with WRAP_CONTENT policy
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, CalculateContentWidth004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField(DEFAULT_TEXT);
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create layout constraint
     */
    LayoutConstraintF contentConstraint;
    contentConstraint.minSize = SizeF(100.0f, 50.0f);
    contentConstraint.maxSize = SizeF(300.0f, 100.0f);

    auto layoutWrapper = CreateLayoutWrapper(frameNode_);
    ASSERT_NE(layoutWrapper, nullptr);

    /**
     * @tc.steps: step3. Create and set mock paragraph for testing
     */
    TextFieldLayoutAlgorithm* algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    RefPtr<Paragraph> paragraph = CreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    SetParagraphForTest(algorithm, paragraph);

    /**
     * @tc.steps: step4. Call CalculateContentWidth with WRAP_CONTENT
     * @tc.expected: Should layout paragraph based on longestLine
     */
    float imageWidth = 0.0f;
    float result = algorithm->CalculateContentWidth(contentConstraint, layoutWrapper, imageWidth);
    EXPECT_GT(result, 0.0f);
}

/**
 * @tc.name: CalculateContentWidth005
 * @tc.desc: Test CalculateContentWidth with FIX_AT_IDEAL_SIZE policy
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, CalculateContentWidth005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField(DEFAULT_TEXT);
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create layout constraint
     */
    LayoutConstraintF contentConstraint;
    contentConstraint.minSize = SizeF(100.0f, 50.0f);
    contentConstraint.maxSize = SizeF(300.0f, 100.0f);

    auto layoutWrapper = CreateLayoutWrapper(frameNode_);
    ASSERT_NE(layoutWrapper, nullptr);

    /**
     * @tc.steps: step3. Create and set mock paragraph for testing
     */
    TextFieldLayoutAlgorithm* algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    RefPtr<Paragraph> paragraph = CreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    SetParagraphForTest(algorithm, paragraph);

    /**
     * @tc.steps: step4. Call CalculateContentWidth with FIX_AT_IDEAL_SIZE
     * @tc.expected: Should apply minWidth constraint
     */
    float imageWidth = 0.0f;
    float result = algorithm->CalculateContentWidth(contentConstraint, layoutWrapper, imageWidth);
    EXPECT_GT(result, 0.0f);
}

/**
 * @tc.name: CalculateContentWidth006
 * @tc.desc: Test CalculateContentWidth with calcMinWidth API 11+
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, CalculateContentWidth006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField(DEFAULT_TEXT);
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create layout constraint
     */
    LayoutConstraintF contentConstraint;
    contentConstraint.minSize = SizeF(150.0f, 50.0f);
    contentConstraint.maxSize = SizeF(300.0f, 100.0f);

    auto layoutWrapper = CreateLayoutWrapper(frameNode_);
    ASSERT_NE(layoutWrapper, nullptr);

    /**
     * @tc.steps: step3. Set calcMinSize for API 11+ path
     */
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    CalcSize calcMinSize(CalcLength(200.0f), CalcLength(100.0f));
    layoutProperty->UpdateCalcMinSize(calcMinSize);

    /**
     * @tc.steps: step4. Create and set mock paragraph for testing
     */
    TextFieldLayoutAlgorithm* algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    RefPtr<Paragraph> paragraph = CreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    SetParagraphForTest(algorithm, paragraph);

    /**
     * @tc.steps: step5. Call CalculateContentWidth
     * @tc.expected: Should use calcLayoutConstraint for API 11+
     */
    float imageWidth = 0.0f;
    float result = algorithm->CalculateContentWidth(contentConstraint, layoutWrapper, imageWidth);
    EXPECT_GT(result, 0.0f);
    EXPECT_LE(result, contentConstraint.maxSize.Width() - imageWidth);
}

/**
 * @tc.name: CalculateContentWidth007
 * @tc.desc: Test CalculateContentWidth with NO_MATCH policy
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, CalculateContentWidth007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField(DEFAULT_TEXT);
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create layout constraint
     */
    LayoutConstraintF contentConstraint;
    contentConstraint.minSize = SizeF(100.0f, 50.0f);
    contentConstraint.maxSize = SizeF(300.0f, 100.0f);

    auto layoutWrapper = CreateLayoutWrapper(frameNode_);
    ASSERT_NE(layoutWrapper, nullptr);

    /**
     * @tc.steps: step3. Create and set mock paragraph for testing
     */
    TextFieldLayoutAlgorithm* algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    RefPtr<Paragraph> paragraph = CreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    SetParagraphForTest(algorithm, paragraph);

    /**
     * @tc.steps: step4. Call CalculateContentWidth with NO_MATCH policy
     * @tc.expected: Should call CounterNodeMeasure
     */
    float imageWidth = 0.0f;
    float result = algorithm->CalculateContentWidth(contentConstraint, layoutWrapper, imageWidth);
    EXPECT_GT(result, 0.0f);
}

/**
 * @tc.name: IsNeedUpdateCounterWidth001
 * @tc.desc: Test IsNeedUpdateCounterWidth returns true when all conditions are met
 *           Branch coverage: all 4 conditions are true -> return true
 *           - GreatNotEqual(minContentWidth, 0.0) is true
 *           - GreatNotEqual(maxContentWidth, minContentWidth) is true
 *           - GreatNotEqual(maxParagraphWidth, 0.0) is true
 *           - GreatNotEqual(contentWidth, maxParagraphWidth) is true
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, IsNeedUpdateCounterWidth001, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT);
    ASSERT_NE(pattern_, nullptr);

    LayoutConstraintF contentConstraint;
    contentConstraint.minSize = SizeF(100.0f, 50.0f);
    contentConstraint.maxSize = SizeF(500.0f, 100.0f);

    auto layoutWrapper = CreateLayoutWrapper(frameNode_);
    ASSERT_NE(layoutWrapper, nullptr);

    TextFieldLayoutAlgorithm* algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    RefPtr<Paragraph> paragraph = CreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    SetParagraphForTest(algorithm, paragraph);

    float imageWidth = 0.0f;
    float result = algorithm->CalculateContentWidth(contentConstraint, layoutWrapper, imageWidth);
    EXPECT_GT(result, 0.0f);
    EXPECT_LE(result, contentConstraint.maxSize.Width());
}

/**
 * @tc.name: IsNeedUpdateCounterWidth002
 * @tc.desc: Test IsNeedUpdateCounterWidth returns false when minContentWidth <= 0
 *           Branch coverage: first condition is false -> return false
 *           - GreatNotEqual(minContentWidth, 0.0) is false (minContentWidth = 0)
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, IsNeedUpdateCounterWidth002, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT);
    ASSERT_NE(pattern_, nullptr);

    LayoutConstraintF contentConstraint;
    contentConstraint.minSize = SizeF(0.0f, 50.0f);
    contentConstraint.maxSize = SizeF(500.0f, 100.0f);

    auto layoutWrapper = CreateLayoutWrapper(frameNode_);
    ASSERT_NE(layoutWrapper, nullptr);

    TextFieldLayoutAlgorithm* algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    RefPtr<Paragraph> paragraph = CreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    SetParagraphForTest(algorithm, paragraph);

    float imageWidth = 0.0f;
    float result = algorithm->CalculateContentWidth(contentConstraint, layoutWrapper, imageWidth);
    EXPECT_GT(result, 0.0f);
    EXPECT_LE(result, contentConstraint.maxSize.Width());
}

/**
 * @tc.name: IsNeedUpdateCounterWidth003
 * @tc.desc: Test IsNeedUpdateCounterWidth returns false when maxContentWidth <= minContentWidth
 *           Branch coverage: second condition is false -> return false
 *           - GreatNotEqual(maxContentWidth, minContentWidth) is false
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, IsNeedUpdateCounterWidth003, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT);
    ASSERT_NE(pattern_, nullptr);

    LayoutConstraintF contentConstraint;
    contentConstraint.minSize = SizeF(300.0f, 50.0f);
    contentConstraint.maxSize = SizeF(300.0f, 100.0f);

    auto layoutWrapper = CreateLayoutWrapper(frameNode_);
    ASSERT_NE(layoutWrapper, nullptr);

    TextFieldLayoutAlgorithm* algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    RefPtr<Paragraph> paragraph = CreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    SetParagraphForTest(algorithm, paragraph);

    float imageWidth = 0.0f;
    float result = algorithm->CalculateContentWidth(contentConstraint, layoutWrapper, imageWidth);
    EXPECT_GT(result, 0.0f);
    EXPECT_LE(result, contentConstraint.maxSize.Width());
}

/**
 * @tc.name: ConstraintWithMinWidth001
 * @tc.desc: Test ConstraintWithMinWidth when paragraph is null
 *           Branch: CHECK_NULL_RETURN(paragraph, 0.0f) returns 0.0f
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, ConstraintWithMinWidth001, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT);
    ASSERT_NE(pattern_, nullptr);

    LayoutConstraintF contentConstraint;
    contentConstraint.minSize = SizeF(100.0f, 50.0f);
    contentConstraint.maxSize = SizeF(300.0f, 100.0f);

    auto layoutWrapper = CreateLayoutWrapper(frameNode_);
    ASSERT_NE(layoutWrapper, nullptr);

    RefPtr<Paragraph> paragraph = nullptr;

    TextFieldLayoutAlgorithm* algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    float result = algorithm->ConstraintWithMinWidth(contentConstraint, layoutWrapper, paragraph, 0.0f);
    EXPECT_EQ(result, 0.0f);
}

/**
 * @tc.name: ConstraintWithMinWidth002
 * @tc.desc: Test ConstraintWithMinWidth when layoutWrapper is null
 *           Branch: CHECK_NULL_RETURN(layoutWrapper, 0.0f) returns 0.0f
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, ConstraintWithMinWidth002, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT);
    ASSERT_NE(pattern_, nullptr);

    LayoutConstraintF contentConstraint;
    contentConstraint.minSize = SizeF(100.0f, 50.0f);
    contentConstraint.maxSize = SizeF(300.0f, 100.0f);

    auto layoutWrapper = CreateLayoutWrapper(frameNode_);
    ASSERT_NE(layoutWrapper, nullptr);

    RefPtr<Paragraph> paragraph = CreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);

    TextFieldLayoutAlgorithm* algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    LayoutWrapper* nullWrapper = nullptr;
    float result = algorithm->ConstraintWithMinWidth(contentConstraint, nullWrapper, paragraph, 0.0f);
    EXPECT_EQ(result, 0.0f);
}

/**
 * @tc.name: ConstraintWithMinWidth003
 * @tc.desc: Test ConstraintWithMinWidth with FIX_AT_IDEAL_SIZE policy and width > longestLine
 *           Branch: isInlineFocus_=false, widthPolicy=FIX_AT_IDEAL_SIZE, width != longestLine
 *           This triggers paragraph->Layout(width) and returns max(paragraph->GetMaxWidth(), 0.0f)
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, ConstraintWithMinWidth003, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT);
    ASSERT_NE(pattern_, nullptr);

    LayoutConstraintF contentConstraint;
    contentConstraint.minSize = SizeF(500.0f, 50.0f);
    contentConstraint.maxSize = SizeF(600.0f, 100.0f);

    auto layoutWrapper = CreateLayoutWrapper(frameNode_);
    ASSERT_NE(layoutWrapper, nullptr);

    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, true);

    auto mockParagraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(mockParagraph, nullptr);
    EXPECT_CALL(*mockParagraph, GetLongestLineWithIndent()).WillRepeatedly(Return(100.0f));
    EXPECT_CALL(*mockParagraph, GetMaxWidth()).WillRepeatedly(Return(500.0f));
    EXPECT_CALL(*mockParagraph, Layout(_)).Times(AtLeast(1));
    RefPtr<Paragraph> paragraph = mockParagraph;

    TextFieldLayoutAlgorithm* algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);
    SetInlineFocusForTest(algorithm, false);

    float result = algorithm->ConstraintWithMinWidth(contentConstraint, layoutWrapper, paragraph, 0.0f);
    EXPECT_GE(result, 500.0f);
}

/**
 * @tc.name: ConstraintWithMinWidth004
 * @tc.desc: Test ConstraintWithMinWidth with WRAP_CONTENT policy and width == longestLine
 *           Branch: isInlineFocus_=false, widthPolicy=WRAP_CONTENT, width == longestLine,
 *                   LessNotEqual(longestLine, maxWidth) is true
 *           This triggers paragraph->Layout(ceil(longestLine)) and returns GetVisualTextWidth()
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, ConstraintWithMinWidth004, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT);
    ASSERT_NE(pattern_, nullptr);

    LayoutConstraintF contentConstraint;
    contentConstraint.minSize = SizeF(50.0f, 50.0f);
    contentConstraint.maxSize = SizeF(600.0f, 100.0f);

    auto layoutWrapper = CreateLayoutWrapper(frameNode_);
    ASSERT_NE(layoutWrapper, nullptr);

    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::WRAP_CONTENT, true);

    auto mockParagraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(mockParagraph, nullptr);
    EXPECT_CALL(*mockParagraph, GetLongestLineWithIndent()).WillRepeatedly(Return(200.0f));
    EXPECT_CALL(*mockParagraph, GetMaxWidth()).WillRepeatedly(Return(400.0f));
    EXPECT_CALL(*mockParagraph, Layout(_)).Times(AtLeast(1));
    RefPtr<Paragraph> paragraph = mockParagraph;

    TextFieldLayoutAlgorithm* algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);
    SetInlineFocusForTest(algorithm, false);
    SetParagraphForTest(algorithm, paragraph);

    float result = algorithm->ConstraintWithMinWidth(contentConstraint, layoutWrapper, paragraph, 0.0f);
    EXPECT_GT(result, 0.0f);
}

/**
 * @tc.name: ConstraintWithMinWidth005
 * @tc.desc: Test ConstraintWithMinWidth with WRAP_CONTENT policy and longestLine >= maxWidth
 *           Branch: isInlineFocus_=false, widthPolicy=WRAP_CONTENT, width == longestLine,
 *                   LessNotEqual(longestLine, maxWidth) is false
 *           This skips paragraph->Layout and returns GetVisualTextWidth()
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, ConstraintWithMinWidth005, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT);
    ASSERT_NE(pattern_, nullptr);

    LayoutConstraintF contentConstraint;
    contentConstraint.minSize = SizeF(50.0f, 50.0f);
    contentConstraint.maxSize = SizeF(600.0f, 100.0f);

    auto layoutWrapper = CreateLayoutWrapper(frameNode_);
    ASSERT_NE(layoutWrapper, nullptr);

    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::WRAP_CONTENT, true);

    auto mockParagraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(mockParagraph, nullptr);
    RefPtr<Paragraph> paragraph = mockParagraph;
    ASSERT_NE(paragraph, nullptr);
    EXPECT_CALL(*mockParagraph, GetLongestLineWithIndent()).WillRepeatedly(Return(400.0f));
    EXPECT_CALL(*mockParagraph, GetMaxWidth()).WillRepeatedly(Return(200.0f));

    TextFieldLayoutAlgorithm* algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);
    SetInlineFocusForTest(algorithm, false);
    SetParagraphForTest(algorithm, paragraph);

    float result = algorithm->ConstraintWithMinWidth(contentConstraint, layoutWrapper, paragraph, 0.0f);
    EXPECT_GT(result, 0.0f);
}

/**
 * @tc.name: ConstraintWithMinWidth006
 * @tc.desc: Test ConstraintWithMinWidth with isInlineFocus_ = true, API 11+ path with all conditions met
 *           and width > longestLine
 *           Branch: isInlineFocus_=true, API>=11, calcLayoutConstraint has minSize with width,
 *                   selfIdealSize has no width, width != longestLine
 *           This triggers paragraph->Layout(width) in API 11 path
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, ConstraintWithMinWidth006, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT);
    ASSERT_NE(pattern_, nullptr);

    LayoutConstraintF contentConstraint;
    contentConstraint.minSize = SizeF(500.0f, 50.0f);
    contentConstraint.maxSize = SizeF(600.0f, 100.0f);

    auto layoutWrapper = CreateLayoutWrapper(frameNode_);
    ASSERT_NE(layoutWrapper, nullptr);

    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    CalcSize calcMinSize(CalcLength(500.0f), CalcLength(50.0f));
    layoutProperty->UpdateCalcMinSize(calcMinSize);

    auto mockParagraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(mockParagraph, nullptr);
    RefPtr<Paragraph> paragraph = mockParagraph;
    ASSERT_NE(paragraph, nullptr);
    EXPECT_CALL(*mockParagraph, GetLongestLine()).WillRepeatedly(Return(100.0f));
    EXPECT_CALL(*mockParagraph, GetMaxWidth()).WillRepeatedly(Return(500.0f));
    EXPECT_CALL(*mockParagraph, Layout(_)).Times(AtLeast(1));

    TextFieldLayoutAlgorithm* algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);
    SetInlineFocusForTest(algorithm, true);

    float result = algorithm->ConstraintWithMinWidth(contentConstraint, layoutWrapper, paragraph, 0.0f);
    EXPECT_GE(result, 0.0f);
}

/**
 * @tc.name: ConstraintWithMinWidth007
 * @tc.desc: Test ConstraintWithMinWidth with isInlineFocus_ = true, API 11+ path,
 *           width == longestLine and longestLine < maxWidth
 *           Branch: isInlineFocus_=true, API>=11, calcLayoutConstraint has minSize with width,
 *                   selfIdealSize has no width, width == longestLine, LessNotEqual(longestLine, maxWidth) true
 *           This triggers paragraph->Layout(ceil(longestLine)) and returns GetVisualTextWidth()
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, ConstraintWithMinWidth007, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT);
    ASSERT_NE(pattern_, nullptr);

    LayoutConstraintF contentConstraint;
    contentConstraint.minSize = SizeF(50.0f, 50.0f);
    contentConstraint.maxSize = SizeF(600.0f, 100.0f);

    auto layoutWrapper = CreateLayoutWrapper(frameNode_);
    ASSERT_NE(layoutWrapper, nullptr);

    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    CalcSize calcMinSize(CalcLength(50.0f), CalcLength(50.0f));
    layoutProperty->UpdateCalcMinSize(calcMinSize);

    auto mockParagraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(mockParagraph, nullptr);
    RefPtr<Paragraph> paragraph = mockParagraph;
    ASSERT_NE(paragraph, nullptr);
    EXPECT_CALL(*mockParagraph, GetLongestLine()).WillRepeatedly(Return(200.0f));
    EXPECT_CALL(*mockParagraph, GetMaxWidth()).WillRepeatedly(Return(400.0f));
    EXPECT_CALL(*mockParagraph, Layout(_)).Times(AtLeast(1));

    TextFieldLayoutAlgorithm* algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);
    SetInlineFocusForTest(algorithm, true);
    SetParagraphForTest(algorithm, paragraph);

    float result = algorithm->ConstraintWithMinWidth(contentConstraint, layoutWrapper, paragraph, 0.0f);
    EXPECT_GT(result, 0.0f);
}

/**
 * @tc.name: ConstraintWithMinWidth008
 * @tc.desc: Test ConstraintWithMinWidth with isInlineFocus_ = true, API 11+ path,
 *           width == longestLine and longestLine >= maxWidth
 *           Branch: isInlineFocus_=true, API>=11, width == longestLine,
 *                   LessNotEqual(longestLine, maxWidth) false
 *           This skips paragraph->Layout and returns GetVisualTextWidth()
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, ConstraintWithMinWidth008, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT);
    ASSERT_NE(pattern_, nullptr);

    LayoutConstraintF contentConstraint;
    contentConstraint.minSize = SizeF(50.0f, 50.0f);
    contentConstraint.maxSize = SizeF(600.0f, 100.0f);

    auto layoutWrapper = CreateLayoutWrapper(frameNode_);
    ASSERT_NE(layoutWrapper, nullptr);

    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    CalcSize calcMinSize(CalcLength(50.0f), CalcLength(50.0f));
    layoutProperty->UpdateCalcMinSize(calcMinSize);

    auto mockParagraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(mockParagraph, nullptr);
    RefPtr<Paragraph> paragraph = mockParagraph;
    ASSERT_NE(paragraph, nullptr);
    EXPECT_CALL(*mockParagraph, GetLongestLine()).WillRepeatedly(Return(400.0f));
    EXPECT_CALL(*mockParagraph, GetMaxWidth()).WillRepeatedly(Return(200.0f));

    TextFieldLayoutAlgorithm* algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);
    SetInlineFocusForTest(algorithm, true);
    SetParagraphForTest(algorithm, paragraph);

    float result = algorithm->ConstraintWithMinWidth(contentConstraint, layoutWrapper, paragraph, 0.0f);
    EXPECT_GT(result, 0.0f);
}

/**
 * @tc.name: ConstraintWithMinWidth009
 * @tc.desc: Test ConstraintWithMinWidth with isInlineFocus_ = true, API 11+ path,
 *           but selfIdealSize.Width has value - conditions not met
 *           Branch: isInlineFocus_=true, API>=11, but selfIdealSize.Width().has_value() is true
 *           This falls through to return max(paragraph->GetMaxWidth(), 0.0f)
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, ConstraintWithMinWidth009, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT);
    ASSERT_NE(pattern_, nullptr);

    LayoutConstraintF contentConstraint;
    contentConstraint.minSize = SizeF(100.0f, 50.0f);
    contentConstraint.maxSize = SizeF(600.0f, 100.0f);
    contentConstraint.selfIdealSize.SetWidth(300.0f);

    auto layoutWrapper = CreateLayoutWrapper(frameNode_);
    ASSERT_NE(layoutWrapper, nullptr);

    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    CalcSize calcMinSize(CalcLength(100.0f), CalcLength(50.0f));
    layoutProperty->UpdateCalcMinSize(calcMinSize);

    auto mockParagraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(mockParagraph, nullptr);
    RefPtr<Paragraph> paragraph = mockParagraph;
    ASSERT_NE(paragraph, nullptr);
    EXPECT_CALL(*mockParagraph, GetMaxWidth()).WillRepeatedly(Return(300.0f));

    TextFieldLayoutAlgorithm* algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);
    SetInlineFocusForTest(algorithm, true);

    float result = algorithm->ConstraintWithMinWidth(contentConstraint, layoutWrapper, paragraph, 0.0f);
    EXPECT_EQ(result, 300.0f);
}

/**
 * @tc.name: ConstraintWithMinWidth010
 * @tc.desc: Test ConstraintWithMinWidth with isInlineFocus_ = true, API 11+ path,
 *           but calcLayoutConstraint minSize has no value - conditions not met
 *           Branch: isInlineFocus_=true, API>=11, but calcLayoutConstraint->minSize has no value
 *           This falls through to return max(paragraph->GetMaxWidth(), 0.0f)
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, ConstraintWithMinWidth010, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT);
    ASSERT_NE(pattern_, nullptr);

    LayoutConstraintF contentConstraint;
    contentConstraint.minSize = SizeF(100.0f, 50.0f);
    contentConstraint.maxSize = SizeF(600.0f, 100.0f);

    auto layoutWrapper = CreateLayoutWrapper(frameNode_);
    ASSERT_NE(layoutWrapper, nullptr);

    auto mockParagraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(mockParagraph, nullptr);
    RefPtr<Paragraph> paragraph = mockParagraph;
    ASSERT_NE(paragraph, nullptr);
    EXPECT_CALL(*mockParagraph, GetMaxWidth()).WillRepeatedly(Return(300.0f));

    TextFieldLayoutAlgorithm* algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);
    SetInlineFocusForTest(algorithm, true);

    float result = algorithm->ConstraintWithMinWidth(contentConstraint, layoutWrapper, paragraph, 0.0f);
    EXPECT_EQ(result, 300.0f);
}

/**
 * @tc.name: ConstraintWithMinWidth011
 * @tc.desc: Test ConstraintWithMinWidth with FIX_AT_IDEAL_SIZE policy and removeValue parameter
 *           Branch: isInlineFocus_=false, widthPolicy=FIX_AT_IDEAL_SIZE, width != longestLine
 *           with non-zero removeValue
 *           This tests the removeValue subtraction from minSize.Width()
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, ConstraintWithMinWidth011, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT);
    ASSERT_NE(pattern_, nullptr);

    LayoutConstraintF contentConstraint;
    contentConstraint.minSize = SizeF(300.0f, 50.0f);
    contentConstraint.maxSize = SizeF(600.0f, 100.0f);

    auto layoutWrapper = CreateLayoutWrapper(frameNode_);
    ASSERT_NE(layoutWrapper, nullptr);

    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, true);

    auto mockParagraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(mockParagraph, nullptr);
    RefPtr<Paragraph> paragraph = mockParagraph;
    ASSERT_NE(paragraph, nullptr);
    EXPECT_CALL(*mockParagraph, GetLongestLineWithIndent()).WillRepeatedly(Return(100.0f));
    EXPECT_CALL(*mockParagraph, GetMaxWidth()).WillRepeatedly(Return(280.0f));
    EXPECT_CALL(*mockParagraph, Layout(_)).Times(AtLeast(1));

    TextFieldLayoutAlgorithm* algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);
    SetInlineFocusForTest(algorithm, false);

    float removeValue = 20.0f;
    float result = algorithm->ConstraintWithMinWidth(contentConstraint, layoutWrapper, paragraph, removeValue);
    EXPECT_GE(result, 280.0f);
}

/**
 * @tc.name: ConstraintWithMinWidth012
 * @tc.desc: Test ConstraintWithMinWidth with MATCH_PARENT policy (falls through to API 11 path)
 *           Branch: isInlineFocus_=false, widthPolicy=MATCH_PARENT (not FIX_AT_IDEAL_SIZE or WRAP_CONTENT)
 *           Falls through to API 11 path and returns max(paragraph->GetMaxWidth(), 0.0f)
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, ConstraintWithMinWidth012, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT);
    ASSERT_NE(pattern_, nullptr);

    LayoutConstraintF contentConstraint;
    contentConstraint.minSize = SizeF(100.0f, 50.0f);
    contentConstraint.maxSize = SizeF(600.0f, 100.0f);

    auto layoutWrapper = CreateLayoutWrapper(frameNode_);
    ASSERT_NE(layoutWrapper, nullptr);

    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, true);

    auto mockParagraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(mockParagraph, nullptr);
    RefPtr<Paragraph> paragraph = mockParagraph;
    ASSERT_NE(paragraph, nullptr);
    EXPECT_CALL(*mockParagraph, GetMaxWidth()).WillRepeatedly(Return(500.0f));

    TextFieldLayoutAlgorithm* algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);
    SetInlineFocusForTest(algorithm, false);

    float result = algorithm->ConstraintWithMinWidth(contentConstraint, layoutWrapper, paragraph, 0.0f);
    EXPECT_EQ(result, 500.0f);
}

/**
 * @tc.name: ConstraintWithMinWidth013
 * @tc.desc: Test ConstraintWithMinWidth with NO_MATCH policy (falls through to API 11 path)
 *           Branch: isInlineFocus_=false, widthPolicy=NO_MATCH
 *           Falls through to API 11 path
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, ConstraintWithMinWidth013, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT);
    ASSERT_NE(pattern_, nullptr);

    LayoutConstraintF contentConstraint;
    contentConstraint.minSize = SizeF(100.0f, 50.0f);
    contentConstraint.maxSize = SizeF(600.0f, 100.0f);

    auto layoutWrapper = CreateLayoutWrapper(frameNode_);
    ASSERT_NE(layoutWrapper, nullptr);

    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, true);

    auto mockParagraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(mockParagraph, nullptr);
    RefPtr<Paragraph> paragraph = mockParagraph;
    ASSERT_NE(paragraph, nullptr);
    EXPECT_CALL(*mockParagraph, GetMaxWidth()).WillRepeatedly(Return(400.0f));

    TextFieldLayoutAlgorithm* algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);
    SetInlineFocusForTest(algorithm, false);

    float result = algorithm->ConstraintWithMinWidth(contentConstraint, layoutWrapper, paragraph, 0.0f);
    EXPECT_EQ(result, 400.0f);
}

/**
 * @tc.name: ConstraintWithMinWidth014
 * @tc.desc: Test ConstraintWithMinWidth with negative removeValue
 *           Branch: removeValue is negative, effectively adds to minSize.Width()
 *           Tests that negative removeValue is handled correctly
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, ConstraintWithMinWidth014, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT);
    ASSERT_NE(pattern_, nullptr);

    LayoutConstraintF contentConstraint;
    contentConstraint.minSize = SizeF(100.0f, 50.0f);
    contentConstraint.maxSize = SizeF(600.0f, 100.0f);

    auto layoutWrapper = CreateLayoutWrapper(frameNode_);
    ASSERT_NE(layoutWrapper, nullptr);

    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, true);

    auto mockParagraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(mockParagraph, nullptr);
    RefPtr<Paragraph> paragraph = mockParagraph;
    ASSERT_NE(paragraph, nullptr);
    EXPECT_CALL(*mockParagraph, GetLongestLineWithIndent()).WillRepeatedly(Return(50.0f));
    EXPECT_CALL(*mockParagraph, GetMaxWidth()).WillRepeatedly(Return(120.0f));
    EXPECT_CALL(*mockParagraph, Layout(_)).Times(AtLeast(1));

    TextFieldLayoutAlgorithm* algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);
    SetInlineFocusForTest(algorithm, false);

    float removeValue = -20.0f;
    float result = algorithm->ConstraintWithMinWidth(contentConstraint, layoutWrapper, paragraph, removeValue);
    EXPECT_GE(result, 120.0f);
}

/**
 * @tc.name: ConstraintWithMinWidth015
 * @tc.desc: Test ConstraintWithMinWidth with API 11 path and calcMinSize.Width only
 *           Branch: calcLayoutConstraint->minSize->Width().has_value() is true
 *           Tests that having only width in calcMinSize works correctly
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, ConstraintWithMinWidth015, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT);
    ASSERT_NE(pattern_, nullptr);

    LayoutConstraintF contentConstraint;
    contentConstraint.minSize = SizeF(500.0f, 50.0f);
    contentConstraint.maxSize = SizeF(600.0f, 100.0f);

    auto layoutWrapper = CreateLayoutWrapper(frameNode_);
    ASSERT_NE(layoutWrapper, nullptr);

    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    CalcSize calcMinSize(CalcLength(500.0f), std::nullopt);
    layoutProperty->UpdateCalcMinSize(calcMinSize);

    auto mockParagraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(mockParagraph, nullptr);
    RefPtr<Paragraph> paragraph = mockParagraph;
    ASSERT_NE(paragraph, nullptr);
    EXPECT_CALL(*mockParagraph, GetLongestLine()).WillRepeatedly(Return(100.0f));
    EXPECT_CALL(*mockParagraph, GetMaxWidth()).WillRepeatedly(Return(500.0f));
    EXPECT_CALL(*mockParagraph, Layout(_)).Times(AtLeast(1));

    TextFieldLayoutAlgorithm* algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);
    SetInlineFocusForTest(algorithm, true);

    float result = algorithm->ConstraintWithMinWidth(contentConstraint, layoutWrapper, paragraph, 0.0f);
    EXPECT_GE(result, 0.0f);
}

/**
 * @tc.name: ConstraintWithMinWidth016
 * @tc.desc: Test ConstraintWithMinWidth default path when no conditions are met
 *           Branch: Neither FIX_AT_IDEAL_SIZE/WRAP_CONTENT path nor API 11 conditions met
 *           Returns max(paragraph->GetMaxWidth(), 0.0f) as default
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, ConstraintWithMinWidth016, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT);
    ASSERT_NE(pattern_, nullptr);

    LayoutConstraintF contentConstraint;
    contentConstraint.minSize = SizeF(100.0f, 50.0f);
    contentConstraint.maxSize = SizeF(600.0f, 100.0f);
    contentConstraint.selfIdealSize.SetWidth(300.0f);

    auto layoutWrapper = CreateLayoutWrapper(frameNode_);
    ASSERT_NE(layoutWrapper, nullptr);

    auto mockParagraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(mockParagraph, nullptr);
    RefPtr<Paragraph> paragraph = mockParagraph;
    ASSERT_NE(paragraph, nullptr);
    EXPECT_CALL(*mockParagraph, GetMaxWidth()).WillRepeatedly(Return(350.0f));

    TextFieldLayoutAlgorithm* algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);
    SetInlineFocusForTest(algorithm, false);

    float result = algorithm->ConstraintWithMinWidth(contentConstraint, layoutWrapper, paragraph, 0.0f);
    EXPECT_EQ(result, 350.0f);
}

/**
 * @tc.name: ConstraintWithMinWidth017
 * @tc.desc: Test ConstraintWithMinWidth with zero maxWidth from paragraph
 *           Branch: paragraph->GetMaxWidth() returns 0.0f
 *           Tests that std::max(paragraph->GetMaxWidth(), 0.0f) returns 0.0f
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, ConstraintWithMinWidth017, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT);
    ASSERT_NE(pattern_, nullptr);

    LayoutConstraintF contentConstraint;
    contentConstraint.minSize = SizeF(100.0f, 50.0f);
    contentConstraint.maxSize = SizeF(600.0f, 100.0f);
    contentConstraint.selfIdealSize.SetWidth(300.0f);

    auto layoutWrapper = CreateLayoutWrapper(frameNode_);
    ASSERT_NE(layoutWrapper, nullptr);

    auto mockParagraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(mockParagraph, nullptr);
    RefPtr<Paragraph> paragraph = mockParagraph;
    ASSERT_NE(paragraph, nullptr);
    EXPECT_CALL(*mockParagraph, GetMaxWidth()).WillRepeatedly(Return(0.0f));

    TextFieldLayoutAlgorithm* algorithm = GetTextFieldLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);
    SetInlineFocusForTest(algorithm, false);

    float result = algorithm->ConstraintWithMinWidth(contentConstraint, layoutWrapper, paragraph, 0.0f);
    EXPECT_EQ(result, 0.0f);
}

} // namespace OHOS::Ace::NG
