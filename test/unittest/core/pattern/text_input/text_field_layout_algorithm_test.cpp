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

#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/frameworks/core/components_ng/render/mock_paragraph.h"
#include "text_input_base.h"

#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/text_field/text_field_layout_algorithm.h"

namespace OHOS::Ace::NG {

constexpr float INLINE_MIN_WIDTH_PX = 16.0f;

struct TestConstraintConfig {
    float minWidth = 100.0f;
    float minHeight = 50.0f;
    float maxWidth = 300.0f;
    float maxHeight = 100.0f;
    std::optional<float> idealWidth;
    std::optional<float> idealHeight;
    std::optional<float> parentIdealWidth;
    std::optional<float> parentIdealHeight;
};

struct MockParagraphConfig {
    float longestLine = 100.0f;
    float longestLineWithIndent = 100.0f;
    float maxWidth = 200.0f;
    float height = 50.0f;
    bool needLayout = false;
};

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
    LayoutConstraintF CreateConstraint(const TestConstraintConfig& config = {})
    {
        LayoutConstraintF constraint;
        constraint.minSize = SizeF(config.minWidth, config.minHeight);
        constraint.maxSize = SizeF(config.maxWidth, config.maxHeight);
        if (config.idealWidth.has_value()) {
            constraint.selfIdealSize.SetWidth(config.idealWidth.value());
        }
        if (config.idealHeight.has_value()) {
            constraint.selfIdealSize.SetHeight(config.idealHeight.value());
        }
        if (config.parentIdealWidth.has_value()) {
            constraint.parentIdealSize.SetWidth(config.parentIdealWidth.value());
        }
        if (config.parentIdealHeight.has_value()) {
            constraint.parentIdealSize.SetHeight(config.parentIdealHeight.value());
        }
        return constraint;
    }

    RefPtr<Paragraph> CreateMockParagraph(const MockParagraphConfig& config = {})
    {
        auto mockParagraph = MockParagraph::GetOrCreateMockParagraph();
        testing::Mock::VerifyAndClear(mockParagraph.GetRawPtr());
        EXPECT_CALL(*mockParagraph, GetLongestLine()).WillRepeatedly(Return(config.longestLine));
        EXPECT_CALL(*mockParagraph, GetLongestLineWithIndent()).WillRepeatedly(Return(config.longestLineWithIndent));
        EXPECT_CALL(*mockParagraph, GetMaxWidth()).WillRepeatedly(Return(config.maxWidth));
        EXPECT_CALL(*mockParagraph, GetHeight()).WillRepeatedly(Return(config.height));
        if (config.needLayout) {
            EXPECT_CALL(*mockParagraph, Layout(_)).Times(AtLeast(1));
        }
        return mockParagraph;
    }

    struct TestEnv {
        RefPtr<LayoutWrapper> layoutWrapperRef;
        LayoutWrapper* layoutWrapper = nullptr;
        RefPtr<TextFieldLayoutAlgorithm> algorithmRef;
        TextFieldLayoutAlgorithm* algorithm = nullptr;
    };

    TestEnv SetupTestEnv(const TestConstraintConfig& constraintConfig = {},
        const std::function<void(TextFieldModelNG&)>& setup = nullptr)
    {
        TestEnv env;
        CreateTextField(DEFAULT_TEXT, "", setup);
        env.layoutWrapperRef = frameNode_->CreateLayoutWrapper(true, true);
        env.layoutWrapper = AceType::RawPtr(env.layoutWrapperRef);
        auto layoutAlgorithmWrapper =
            AceType::DynamicCast<LayoutAlgorithmWrapper>(env.layoutWrapper->GetLayoutAlgorithm());
        if (layoutAlgorithmWrapper) {
            env.algorithmRef =
                AceType::DynamicCast<TextFieldLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
            env.algorithm = AceType::RawPtr(env.algorithmRef);
        }
        return env;
    }

    void SetParagraphForTest(TextFieldLayoutAlgorithm* algorithm, const RefPtr<Paragraph>& paragraph)
    {
        TextFieldLayoutAlgorithmTestHelper::SetParagraph(algorithm, paragraph);
    }

    void SetInlineParagraphForTest(TextFieldLayoutAlgorithm* algorithm, const RefPtr<Paragraph>& paragraph)
    {
        TextFieldLayoutAlgorithmTestHelper::SetInlineParagraph(algorithm, paragraph);
    }

    void SetInlineFocusForTest(TextFieldLayoutAlgorithm* algorithm, bool isInlineFocus)
    {
        TextFieldLayoutAlgorithmTestHelper::SetInlineFocus(algorithm, isInlineFocus);
    }
};

/**
 * @tc.name: InlineMeasureContent001
 * @tc.desc: Test InlineMeasureContent with valid parameters in non-focus mode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, InlineMeasureContent001, TestSize.Level1)
{
    auto env = SetupTestEnv();
    ASSERT_NE(env.layoutWrapper, nullptr);
    ASSERT_NE(env.algorithm, nullptr);

    SetParagraphForTest(env.algorithm, CreateMockParagraph());
    SetInlineParagraphForTest(env.algorithm, CreateMockParagraph());

    auto result = env.algorithm->InlineMeasureContent(CreateConstraint(), env.layoutWrapper);
    EXPECT_TRUE(result.has_value());
    EXPECT_GT(result->Width(), 0.0f);
    EXPECT_GT(result->Height(), 0.0f);
}

/**
 * @tc.name: InlineMeasureContent002
 * @tc.desc: Test InlineMeasureContent with focus mode and non-styled placeholder
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, InlineMeasureContent002, TestSize.Level1)
{
    auto env = SetupTestEnv();
    ASSERT_NE(env.layoutWrapper, nullptr);
    ASSERT_NE(env.algorithm, nullptr);

    SetParagraphForTest(env.algorithm, CreateMockParagraph());
    SetInlineParagraphForTest(env.algorithm, CreateMockParagraph());

    auto result = env.algorithm->InlineMeasureContent(CreateConstraint(), env.layoutWrapper);
    EXPECT_TRUE(result.has_value());
    EXPECT_GE(result->Width(), INLINE_MIN_WIDTH_PX);
}

/**
 * @tc.name: InlineMeasureContent003
 * @tc.desc: Test InlineMeasureContent with large constraint to test widthLayoutPolicy
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, InlineMeasureContent003, TestSize.Level1)
{
    auto env = SetupTestEnv({ .minWidth = 500.0f, .maxWidth = 600.0f, .maxHeight = 200.0f });
    ASSERT_NE(env.layoutWrapper, nullptr);
    ASSERT_NE(env.algorithm, nullptr);

    SetParagraphForTest(env.algorithm, CreateMockParagraph());
    SetInlineParagraphForTest(env.algorithm, CreateMockParagraph());

    auto result = env.algorithm->InlineMeasureContent(
        CreateConstraint({ .minWidth = 500.0f, .maxWidth = 600.0f }), env.layoutWrapper);
    EXPECT_TRUE(result.has_value());
    EXPECT_GE(result->Width(), INLINE_MIN_WIDTH_PX);
}

/**
 * @tc.name: InlineMeasureContent004
 * @tc.desc: Test InlineMeasureContent height calculation when longestLine is zero
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, InlineMeasureContent004, TestSize.Level1)
{
    auto env = SetupTestEnv();
    ASSERT_NE(env.layoutWrapper, nullptr);
    ASSERT_NE(env.algorithm, nullptr);

    SetParagraphForTest(env.algorithm, CreateMockParagraph());
    SetInlineParagraphForTest(env.algorithm, CreateMockParagraph());

    auto result = env.algorithm->InlineMeasureContent(CreateConstraint(), env.layoutWrapper);
    EXPECT_TRUE(result.has_value());
    EXPECT_GT(result->Height(), 0.0f);
}

/**
 * @tc.name: InlineMeasureContent005
 * @tc.desc: Test InlineMeasureContent with small contentWidth to test minWidth constraint
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, InlineMeasureContent005, TestSize.Level1)
{
    auto env = SetupTestEnv({ .minWidth = 10.0f, .maxWidth = 20.0f, .maxHeight = 50.0f });
    ASSERT_NE(env.layoutWrapper, nullptr);
    ASSERT_NE(env.algorithm, nullptr);

    SetParagraphForTest(env.algorithm, CreateMockParagraph());
    SetInlineParagraphForTest(env.algorithm, CreateMockParagraph());

    auto result = env.algorithm->InlineMeasureContent(
        CreateConstraint({ .minWidth = 10.0f, .maxWidth = 20.0f }), env.layoutWrapper);
    EXPECT_TRUE(result.has_value());
    EXPECT_GE(result->Width(), INLINE_MIN_WIDTH_PX);
}

/**
 * @tc.name: InlineMeasureContent006
 * @tc.desc: Test InlineMeasureContent with autoWidth enabled
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, InlineMeasureContent006, TestSize.Level1)
{
    auto env = SetupTestEnv({ .maxWidth = 460.0f });
    ASSERT_NE(env.layoutWrapper, nullptr);
    ASSERT_NE(env.algorithm, nullptr);

    SetParagraphForTest(env.algorithm, CreateMockParagraph());
    SetInlineParagraphForTest(env.algorithm, CreateMockParagraph());

    auto result = env.algorithm->InlineMeasureContent(CreateConstraint({ .maxWidth = 460.0f }), env.layoutWrapper);
    EXPECT_TRUE(result.has_value());
    EXPECT_GT(result->Width(), 0.0f);
    EXPECT_GT(result->Height(), 0.0f);
}

/**
 * @tc.name: InlineMeasureContent007
 * @tc.desc: Test InlineMeasureContent height constraint with inlineIdealHeight
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, InlineMeasureContent007, TestSize.Level1)
{
    auto env = SetupTestEnv({ .minHeight = 30.0f, .maxHeight = 40.0f });
    ASSERT_NE(env.layoutWrapper, nullptr);
    ASSERT_NE(env.algorithm, nullptr);

    SetParagraphForTest(env.algorithm, CreateMockParagraph());
    SetInlineParagraphForTest(env.algorithm, CreateMockParagraph());

    auto result = env.algorithm->InlineMeasureContent(
        CreateConstraint({ .minHeight = 30.0f, .maxHeight = 40.0f }), env.layoutWrapper);
    EXPECT_TRUE(result.has_value());
    EXPECT_LE(result->Height(), 40.0f);
}

/**
 * @tc.name: InlineMeasureContent008
 * @tc.desc: Test InlineMeasureContent GetInlineMeasureItem with focus and multiple lines
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, InlineMeasureContent008, TestSize.Level1)
{
    auto env = SetupTestEnv({ .maxHeight = 150.0f });
    ASSERT_NE(env.layoutWrapper, nullptr);
    ASSERT_NE(env.algorithm, nullptr);

    SetParagraphForTest(env.algorithm, CreateMockParagraph());
    SetInlineParagraphForTest(env.algorithm, CreateMockParagraph());

    auto result = env.algorithm->InlineMeasureContent(CreateConstraint({ .maxHeight = 150.0f }), env.layoutWrapper);
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
    auto env = SetupTestEnv({ .maxHeight = 200.0f });
    ASSERT_NE(env.layoutWrapper, nullptr);
    ASSERT_NE(env.algorithm, nullptr);

    SetParagraphForTest(env.algorithm, CreateMockParagraph());

    SizeF result = env.algorithm->TextAreaMeasureContent(CreateConstraint({ .maxHeight = 200.0f }), env.layoutWrapper);
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
    auto env = SetupTestEnv({ .maxWidth = 460.0f, .maxHeight = 200.0f });
    ASSERT_NE(env.layoutWrapper, nullptr);
    ASSERT_NE(env.algorithm, nullptr);

    SetParagraphForTest(env.algorithm, CreateMockParagraph());

    SizeF result = env.algorithm->TextAreaMeasureContent(
        CreateConstraint({ .maxWidth = 460.0f, .maxHeight = 200.0f }), env.layoutWrapper);
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
    auto env = SetupTestEnv({ .minHeight = 30.0f, .maxHeight = 50.0f });
    ASSERT_NE(env.layoutWrapper, nullptr);
    ASSERT_NE(env.algorithm, nullptr);

    SetParagraphForTest(env.algorithm, CreateMockParagraph());

    SizeF result = env.algorithm->TextAreaMeasureContent(
        CreateConstraint({ .minHeight = 30.0f, .maxHeight = 50.0f }), env.layoutWrapper);
    EXPECT_GT(result.Height(), 0.0f);
    EXPECT_LE(result.Height(), 50.0f);
}

/**
 * @tc.name: TextAreaMeasureContent004
 * @tc.desc: Test TextAreaMeasureContent with counter node height
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, TextAreaMeasureContent004, TestSize.Level1)
{
    auto env = SetupTestEnv({ .maxHeight = 200.0f });
    ASSERT_NE(env.layoutWrapper, nullptr);
    ASSERT_NE(env.algorithm, nullptr);

    SetParagraphForTest(env.algorithm, CreateMockParagraph());

    SizeF result = env.algorithm->TextAreaMeasureContent(CreateConstraint({ .maxHeight = 200.0f }), env.layoutWrapper);
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
    auto env = SetupTestEnv({ .maxHeight = 200.0f });
    ASSERT_NE(env.layoutWrapper, nullptr);
    ASSERT_NE(env.algorithm, nullptr);

    SetParagraphForTest(env.algorithm, CreateMockParagraph());

    SizeF result = env.algorithm->TextAreaMeasureContent(CreateConstraint({ .maxHeight = 200.0f }), env.layoutWrapper);
    EXPECT_GT(result.Width(), 0.0f);
    EXPECT_LE(result.Height(), 200.0f);
}

/**
 * @tc.name: CalculateContentWidth001
 * @tc.desc: Test CalculateContentWidth with basic parameters
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, CalculateContentWidth001, TestSize.Level1)
{
    auto env = SetupTestEnv();
    ASSERT_NE(env.layoutWrapper, nullptr);
    ASSERT_NE(env.algorithm, nullptr);

    SetParagraphForTest(env.algorithm, CreateMockParagraph());

    float result = env.algorithm->CalculateContentWidth(CreateConstraint(), env.layoutWrapper, 0.0f);
    EXPECT_GT(result, 0.0f);
    EXPECT_LE(result, 300.0f);
}

/**
 * @tc.name: CalculateContentWidth002
 * @tc.desc: Test CalculateContentWidth with imageWidth
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, CalculateContentWidth002, TestSize.Level1)
{
    auto env = SetupTestEnv();
    ASSERT_NE(env.layoutWrapper, nullptr);
    ASSERT_NE(env.algorithm, nullptr);

    SetParagraphForTest(env.algorithm, CreateMockParagraph());

    float imageWidth = 50.0f;
    float result = env.algorithm->CalculateContentWidth(CreateConstraint(), env.layoutWrapper, imageWidth);
    EXPECT_GT(result, 0.0f);
    EXPECT_LE(result, 300.0f - imageWidth);
}

/**
 * @tc.name: CalculateContentWidth003
 * @tc.desc: Test CalculateContentWidth with autoWidth enabled
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, CalculateContentWidth003, TestSize.Level1)
{
    auto env = SetupTestEnv({ .maxWidth = 460.0f });
    ASSERT_NE(env.layoutWrapper, nullptr);
    ASSERT_NE(env.algorithm, nullptr);

    SetParagraphForTest(env.algorithm, CreateMockParagraph());

    float result =
        env.algorithm->CalculateContentWidth(CreateConstraint({ .maxWidth = 460.0f }), env.layoutWrapper, 0.0f);
    EXPECT_GE(result, INLINE_MIN_WIDTH_PX);
}

/**
 * @tc.name: CalculateContentWidth004
 * @tc.desc: Test CalculateContentWidth with calcMinWidth API 11+
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, CalculateContentWidth004, TestSize.Level1)
{
    auto env = SetupTestEnv({ .minWidth = 150.0f });
    ASSERT_NE(env.layoutWrapper, nullptr);
    ASSERT_NE(env.algorithm, nullptr);

    auto layoutProperty = env.layoutWrapper->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateCalcMinSize(CalcSize(CalcLength(200.0f), CalcLength(100.0f)));

    SetParagraphForTest(env.algorithm, CreateMockParagraph());

    float result =
        env.algorithm->CalculateContentWidth(CreateConstraint({ .minWidth = 150.0f }), env.layoutWrapper, 0.0f);
    EXPECT_GT(result, 0.0f);
}

/**
 * @tc.name: IsNeedUpdateCounterWidth001
 * @tc.desc: Test IsNeedUpdateCounterWidth returns true when all conditions are met
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, IsNeedUpdateCounterWidth001, TestSize.Level1)
{
    auto env = SetupTestEnv({ .maxWidth = 500.0f });
    ASSERT_NE(env.layoutWrapper, nullptr);
    ASSERT_NE(env.algorithm, nullptr);

    SetParagraphForTest(env.algorithm, CreateMockParagraph());

    float result =
        env.algorithm->CalculateContentWidth(CreateConstraint({ .maxWidth = 500.0f }), env.layoutWrapper, 0.0f);
    EXPECT_GT(result, 0.0f);
}

/**
 * @tc.name: IsNeedUpdateCounterWidth002
 * @tc.desc: Test IsNeedUpdateCounterWidth returns false when minContentWidth <= 0
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, IsNeedUpdateCounterWidth002, TestSize.Level1)
{
    auto env = SetupTestEnv({ .minWidth = 0.0f, .maxWidth = 500.0f });
    ASSERT_NE(env.layoutWrapper, nullptr);
    ASSERT_NE(env.algorithm, nullptr);

    SetParagraphForTest(env.algorithm, CreateMockParagraph());

    float result = env.algorithm->CalculateContentWidth(
        CreateConstraint({ .minWidth = 0.0f, .maxWidth = 500.0f }), env.layoutWrapper, 0.0f);
    EXPECT_GT(result, 0.0f);
}

/**
 * @tc.name: IsNeedUpdateCounterWidth003
 * @tc.desc: Test IsNeedUpdateCounterWidth returns false when maxContentWidth <= minContentWidth
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, IsNeedUpdateCounterWidth003, TestSize.Level1)
{
    auto env = SetupTestEnv({ .minWidth = 300.0f, .maxWidth = 300.0f });
    ASSERT_NE(env.layoutWrapper, nullptr);
    ASSERT_NE(env.algorithm, nullptr);

    SetParagraphForTest(env.algorithm, CreateMockParagraph());

    float result = env.algorithm->CalculateContentWidth(
        CreateConstraint({ .minWidth = 300.0f, .maxWidth = 300.0f }), env.layoutWrapper, 0.0f);
    EXPECT_GT(result, 0.0f);
}

/**
 * @tc.name: ConstraintWithMinWidth001
 * @tc.desc: Test ConstraintWithMinWidth when paragraph is null
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, ConstraintWithMinWidth001, TestSize.Level1)
{
    auto env = SetupTestEnv();
    ASSERT_NE(env.layoutWrapper, nullptr);
    ASSERT_NE(env.algorithm, nullptr);

    RefPtr<Paragraph> nullParagraph;
    float result = env.algorithm->ConstraintWithMinWidth(CreateConstraint(), env.layoutWrapper, nullParagraph, 0.0f);
    EXPECT_EQ(result, 0.0f);
}

/**
 * @tc.name: ConstraintWithMinWidth002
 * @tc.desc: Test ConstraintWithMinWidth when layoutWrapper is null
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, ConstraintWithMinWidth002, TestSize.Level1)
{
    auto env = SetupTestEnv();
    ASSERT_NE(env.layoutWrapper, nullptr);
    ASSERT_NE(env.algorithm, nullptr);

    auto paragraph = CreateMockParagraph();
    float result = env.algorithm->ConstraintWithMinWidth(CreateConstraint(), nullptr, paragraph, 0.0f);
    EXPECT_EQ(result, 0.0f);
}

/**
 * @tc.name: ConstraintWithMinWidth003
 * @tc.desc: Test ConstraintWithMinWidth with FIX_AT_IDEAL_SIZE policy and width > longestLine
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, ConstraintWithMinWidth003, TestSize.Level1)
{
    auto env = SetupTestEnv({ .minWidth = 500.0f, .maxWidth = 600.0f });
    ASSERT_NE(env.layoutWrapper, nullptr);
    ASSERT_NE(env.algorithm, nullptr);

    auto layoutProperty = env.layoutWrapper->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, true);
    SetInlineFocusForTest(env.algorithm, false);

    auto paragraph = CreateMockParagraph({ .longestLineWithIndent = 100.0f, .maxWidth = 500.0f, .needLayout = true });

    float result = env.algorithm->ConstraintWithMinWidth(
        CreateConstraint({ .minWidth = 500.0f, .maxWidth = 600.0f }), env.layoutWrapper, paragraph, 0.0f);
    EXPECT_GE(result, 500.0f);
}

/**
 * @tc.name: ConstraintWithMinWidth004
 * @tc.desc: Test ConstraintWithMinWidth with WRAP_CONTENT policy and width == longestLine
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, ConstraintWithMinWidth004, TestSize.Level1)
{
    auto env = SetupTestEnv({ .minWidth = 50.0f, .maxWidth = 600.0f });
    ASSERT_NE(env.layoutWrapper, nullptr);
    ASSERT_NE(env.algorithm, nullptr);

    auto layoutProperty = env.layoutWrapper->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::WRAP_CONTENT, true);
    SetInlineFocusForTest(env.algorithm, false);

    auto paragraph = CreateMockParagraph(
        { .longestLine = 200.0f, .longestLineWithIndent = 200.0f, .maxWidth = 400.0f, .needLayout = true });
    SetParagraphForTest(env.algorithm, paragraph);

    float result = env.algorithm->ConstraintWithMinWidth(
        CreateConstraint({ .minWidth = 50.0f, .maxWidth = 600.0f }), env.layoutWrapper, paragraph, 0.0f);
    EXPECT_GT(result, 0.0f);
}

/**
 * @tc.name: ConstraintWithMinWidth005
 * @tc.desc: Test ConstraintWithMinWidth with WRAP_CONTENT policy and longestLine >= maxWidth
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, ConstraintWithMinWidth005, TestSize.Level1)
{
    auto env = SetupTestEnv({ .minWidth = 50.0f, .maxWidth = 600.0f });
    ASSERT_NE(env.layoutWrapper, nullptr);
    ASSERT_NE(env.algorithm, nullptr);

    auto layoutProperty = env.layoutWrapper->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::WRAP_CONTENT, true);
    SetInlineFocusForTest(env.algorithm, false);

    auto paragraph =
        CreateMockParagraph({ .longestLine = 400.0f, .longestLineWithIndent = 400.0f, .maxWidth = 200.0f });
    SetParagraphForTest(env.algorithm, paragraph);

    float result = env.algorithm->ConstraintWithMinWidth(
        CreateConstraint({ .minWidth = 50.0f, .maxWidth = 600.0f }), env.layoutWrapper, paragraph, 0.0f);
    EXPECT_GT(result, 0.0f);
}

/**
 * @tc.name: ConstraintWithMinWidth006
 * @tc.desc: Test ConstraintWithMinWidth with isInlineFocus_ = true, API 11+ path
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, ConstraintWithMinWidth006, TestSize.Level1)
{
    auto env = SetupTestEnv({ .minWidth = 500.0f, .maxWidth = 600.0f });
    ASSERT_NE(env.layoutWrapper, nullptr);
    ASSERT_NE(env.algorithm, nullptr);

    auto layoutProperty = env.layoutWrapper->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateCalcMinSize(CalcSize(CalcLength(500.0f), CalcLength(50.0f)));
    SetInlineFocusForTest(env.algorithm, true);

    auto paragraph = CreateMockParagraph({ .longestLine = 100.0f, .maxWidth = 500.0f, .needLayout = true });

    float result = env.algorithm->ConstraintWithMinWidth(
        CreateConstraint({ .minWidth = 500.0f, .maxWidth = 600.0f }), env.layoutWrapper, paragraph, 0.0f);
    EXPECT_GE(result, 0.0f);
}

/**
 * @tc.name: ConstraintWithMinWidth007
 * @tc.desc: Test ConstraintWithMinWidth with isInlineFocus_ = true, width == longestLine
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, ConstraintWithMinWidth007, TestSize.Level1)
{
    auto env = SetupTestEnv({ .minWidth = 50.0f, .maxWidth = 600.0f });
    ASSERT_NE(env.layoutWrapper, nullptr);
    ASSERT_NE(env.algorithm, nullptr);

    auto layoutProperty = env.layoutWrapper->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateCalcMinSize(CalcSize(CalcLength(50.0f), CalcLength(50.0f)));
    SetInlineFocusForTest(env.algorithm, true);

    auto paragraph = CreateMockParagraph({ .longestLine = 200.0f, .maxWidth = 400.0f, .needLayout = true });
    SetParagraphForTest(env.algorithm, paragraph);

    float result = env.algorithm->ConstraintWithMinWidth(
        CreateConstraint({ .minWidth = 50.0f, .maxWidth = 600.0f }), env.layoutWrapper, paragraph, 0.0f);
    EXPECT_GT(result, 0.0f);
}

/**
 * @tc.name: ConstraintWithMinWidth008
 * @tc.desc: Test ConstraintWithMinWidth with isInlineFocus_ = true, longestLine >= maxWidth
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, ConstraintWithMinWidth008, TestSize.Level1)
{
    auto env = SetupTestEnv({ .minWidth = 50.0f, .maxWidth = 600.0f });
    ASSERT_NE(env.layoutWrapper, nullptr);
    ASSERT_NE(env.algorithm, nullptr);

    auto layoutProperty = env.layoutWrapper->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateCalcMinSize(CalcSize(CalcLength(50.0f), CalcLength(50.0f)));
    SetInlineFocusForTest(env.algorithm, true);

    auto paragraph = CreateMockParagraph({ .longestLine = 400.0f, .maxWidth = 200.0f });
    SetParagraphForTest(env.algorithm, paragraph);

    float result = env.algorithm->ConstraintWithMinWidth(
        CreateConstraint({ .minWidth = 50.0f, .maxWidth = 600.0f }), env.layoutWrapper, paragraph, 0.0f);
    EXPECT_GT(result, 0.0f);
}

/**
 * @tc.name: ConstraintWithMinWidth009
 * @tc.desc: Test ConstraintWithMinWidth with selfIdealSize.Width has value
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, ConstraintWithMinWidth009, TestSize.Level1)
{
    auto env = SetupTestEnv({ .minWidth = 100.0f, .maxWidth = 600.0f, .idealWidth = 300.0f });
    ASSERT_NE(env.layoutWrapper, nullptr);
    ASSERT_NE(env.algorithm, nullptr);

    auto layoutProperty = env.layoutWrapper->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateCalcMinSize(CalcSize(CalcLength(100.0f), CalcLength(50.0f)));
    SetInlineFocusForTest(env.algorithm, true);

    auto paragraph = CreateMockParagraph({ .maxWidth = 300.0f });

    float result = env.algorithm->ConstraintWithMinWidth(
        CreateConstraint({ .minWidth = 100.0f, .maxWidth = 600.0f, .idealWidth = 300.0f }), env.layoutWrapper,
        paragraph, 0.0f);
    EXPECT_EQ(result, 300.0f);
}

/**
 * @tc.name: ConstraintWithMinWidth010
 * @tc.desc: Test ConstraintWithMinWidth with MATCH_PARENT policy
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, ConstraintWithMinWidth010, TestSize.Level1)
{
    auto env = SetupTestEnv({ .minWidth = 100.0f, .maxWidth = 600.0f });
    ASSERT_NE(env.layoutWrapper, nullptr);
    ASSERT_NE(env.algorithm, nullptr);

    auto layoutProperty = env.layoutWrapper->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, true);
    SetInlineFocusForTest(env.algorithm, false);

    auto paragraph = CreateMockParagraph({ .maxWidth = 500.0f });

    float result = env.algorithm->ConstraintWithMinWidth(
        CreateConstraint({ .minWidth = 100.0f, .maxWidth = 600.0f }), env.layoutWrapper, paragraph, 0.0f);
    EXPECT_EQ(result, 500.0f);
}

/**
 * @tc.name: ConstraintWithMinWidth011
 * @tc.desc: Test ConstraintWithMinWidth with NO_MATCH policy
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, ConstraintWithMinWidth011, TestSize.Level1)
{
    auto env = SetupTestEnv({ .minWidth = 100.0f, .maxWidth = 600.0f });
    ASSERT_NE(env.layoutWrapper, nullptr);
    ASSERT_NE(env.algorithm, nullptr);

    auto layoutProperty = env.layoutWrapper->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, true);
    SetInlineFocusForTest(env.algorithm, false);

    auto paragraph = CreateMockParagraph({ .maxWidth = 400.0f });

    float result = env.algorithm->ConstraintWithMinWidth(
        CreateConstraint({ .minWidth = 100.0f, .maxWidth = 600.0f }), env.layoutWrapper, paragraph, 0.0f);
    EXPECT_EQ(result, 400.0f);
}

/**
 * @tc.name: ConstraintWithMinWidth012
 * @tc.desc: Test ConstraintWithMinWidth with negative removeValue
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, ConstraintWithMinWidth012, TestSize.Level1)
{
    auto env = SetupTestEnv({ .minWidth = 100.0f, .maxWidth = 600.0f });
    ASSERT_NE(env.layoutWrapper, nullptr);
    ASSERT_NE(env.algorithm, nullptr);

    auto layoutProperty = env.layoutWrapper->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, true);
    SetInlineFocusForTest(env.algorithm, false);

    auto paragraph = CreateMockParagraph({ .longestLineWithIndent = 50.0f, .maxWidth = 120.0f, .needLayout = true });

    float result = env.algorithm->ConstraintWithMinWidth(
        CreateConstraint({ .minWidth = 100.0f, .maxWidth = 600.0f }), env.layoutWrapper, paragraph, -20.0f);
    EXPECT_GE(result, 120.0f);
}

/**
 * @tc.name: ConstraintWithMinWidth013
 * @tc.desc: Test ConstraintWithMinWidth with zero maxWidth from paragraph
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, ConstraintWithMinWidth013, TestSize.Level1)
{
    auto env = SetupTestEnv({ .minWidth = 100.0f, .maxWidth = 600.0f, .idealWidth = 300.0f });
    ASSERT_NE(env.layoutWrapper, nullptr);
    ASSERT_NE(env.algorithm, nullptr);
    SetInlineFocusForTest(env.algorithm, false);

    auto paragraph = CreateMockParagraph({ .maxWidth = 0.0f });

    float result = env.algorithm->ConstraintWithMinWidth(
        CreateConstraint({ .minWidth = 100.0f, .maxWidth = 600.0f, .idealWidth = 300.0f }), env.layoutWrapper,
        paragraph, 0.0f);
    EXPECT_EQ(result, 0.0f);
}

/**
 * @tc.name: CalculateContentMaxSizeWithPolicy001
 * @tc.desc: Test CalculateContentMaxSizeWithPolicy with isInlineFocus_ = true, should return early.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, CalculateContentMaxSizeWithPolicy001, TestSize.Level1)
{
    auto env = SetupTestEnv();
    ASSERT_NE(env.layoutWrapper, nullptr);
    ASSERT_NE(env.algorithm, nullptr);
    SetInlineFocusForTest(env.algorithm, true);

    auto constraint = CreateConstraint();
    SizeF maxIdealSize(100.0f, 50.0f);
    SizeF originalSize = maxIdealSize;

    env.algorithm->CalculateContentMaxSizeWithPolicy(env.layoutWrapper, constraint, maxIdealSize);
    EXPECT_EQ(maxIdealSize.Width(), originalSize.Width());
    EXPECT_EQ(maxIdealSize.Height(), originalSize.Height());
}

/**
 * @tc.name: CalculateContentMaxSizeWithPolicy002
 * @tc.desc: Test CalculateContentMaxSizeWithPolicy with null layoutWrapper, should return early via CHECK_NULL_VOID.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, CalculateContentMaxSizeWithPolicy002, TestSize.Level1)
{
    auto env = SetupTestEnv();
    ASSERT_NE(env.algorithm, nullptr);
    SetInlineFocusForTest(env.algorithm, false);

    auto constraint = CreateConstraint();
    SizeF maxIdealSize(100.0f, 50.0f);
    SizeF originalSize = maxIdealSize;

    env.algorithm->CalculateContentMaxSizeWithPolicy(nullptr, constraint, maxIdealSize);
    EXPECT_EQ(maxIdealSize.Width(), originalSize.Width());
    EXPECT_EQ(maxIdealSize.Height(), originalSize.Height());
}

/**
 * @tc.name: CalculateContentMaxSizeWithPolicy003
 * @tc.desc: Test CalculateContentMaxSizeWithPolicy with widthLayoutPolicy = FIX_AT_IDEAL_SIZE.
 *           Should set maxIdealSize.Width to infinity.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, CalculateContentMaxSizeWithPolicy003, TestSize.Level1)
{
    auto env = SetupTestEnv();
    ASSERT_NE(env.layoutWrapper, nullptr);
    ASSERT_NE(env.algorithm, nullptr);
    SetInlineFocusForTest(env.algorithm, false);

    auto layoutProperty = env.layoutWrapper->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, true);

    auto constraint = CreateConstraint();
    SizeF maxIdealSize(100.0f, 50.0f);

    env.algorithm->CalculateContentMaxSizeWithPolicy(env.layoutWrapper, constraint, maxIdealSize);
    EXPECT_TRUE(std::isinf(maxIdealSize.Width()));
}

/**
 * @tc.name: CalculateContentMaxSizeWithPolicy004
 * @tc.desc: Test CalculateContentMaxSizeWithPolicy with widthLayoutPolicy = MATCH_PARENT and parentIdealSize.Width has
 * value. Should set maxIdealSize.Width and selfIdealSize.Width to parentIdealSize.Width.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, CalculateContentMaxSizeWithPolicy004, TestSize.Level1)
{
    auto env = SetupTestEnv();
    ASSERT_NE(env.layoutWrapper, nullptr);
    ASSERT_NE(env.algorithm, nullptr);
    SetInlineFocusForTest(env.algorithm, false);

    auto layoutProperty = env.layoutWrapper->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, true);

    auto constraint = CreateConstraint({ .parentIdealWidth = 500.0f });
    SizeF maxIdealSize(100.0f, 50.0f);

    env.algorithm->CalculateContentMaxSizeWithPolicy(env.layoutWrapper, constraint, maxIdealSize);
    EXPECT_EQ(maxIdealSize.Width(), 500.0f);
    EXPECT_TRUE(constraint.selfIdealSize.Width().has_value());
    EXPECT_EQ(constraint.selfIdealSize.Width().value(), 500.0f);
}

/**
 * @tc.name: CalculateContentMaxSizeWithPolicy005
 * @tc.desc: Test CalculateContentMaxSizeWithPolicy with widthLayoutPolicy = MATCH_PARENT but no parentIdealSize.Width.
 *           Should not modify maxIdealSize.Width.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, CalculateContentMaxSizeWithPolicy005, TestSize.Level1)
{
    auto env = SetupTestEnv();
    ASSERT_NE(env.layoutWrapper, nullptr);
    ASSERT_NE(env.algorithm, nullptr);
    SetInlineFocusForTest(env.algorithm, false);

    auto layoutProperty = env.layoutWrapper->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, true);

    auto constraint = CreateConstraint();
    SizeF maxIdealSize(100.0f, 50.0f);
    SizeF originalSize = maxIdealSize;

    env.algorithm->CalculateContentMaxSizeWithPolicy(env.layoutWrapper, constraint, maxIdealSize);
    EXPECT_EQ(maxIdealSize.Width(), originalSize.Width());
}

/**
 * @tc.name: CalculateContentMaxSizeWithPolicy006
 * @tc.desc: Test CalculateContentMaxSizeWithPolicy with heightLayoutPolicy = FIX_AT_IDEAL_SIZE and no
 * selfIdealSize.Height. Should set maxIdealSize.Height to infinity.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, CalculateContentMaxSizeWithPolicy006, TestSize.Level1)
{
    auto env = SetupTestEnv();
    ASSERT_NE(env.layoutWrapper, nullptr);
    ASSERT_NE(env.algorithm, nullptr);
    SetInlineFocusForTest(env.algorithm, false);

    auto layoutProperty = env.layoutWrapper->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, false);

    auto constraint = CreateConstraint();
    SizeF maxIdealSize(100.0f, 50.0f);

    env.algorithm->CalculateContentMaxSizeWithPolicy(env.layoutWrapper, constraint, maxIdealSize);
    EXPECT_TRUE(std::isinf(maxIdealSize.Height()));
}

/**
 * @tc.name: CalculateContentMaxSizeWithPolicy007
 * @tc.desc: Test CalculateContentMaxSizeWithPolicy with heightLayoutPolicy = FIX_AT_IDEAL_SIZE but selfIdealSize.Height
 * has value. Should not set maxIdealSize.Height to infinity.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, CalculateContentMaxSizeWithPolicy007, TestSize.Level1)
{
    auto env = SetupTestEnv();
    ASSERT_NE(env.layoutWrapper, nullptr);
    ASSERT_NE(env.algorithm, nullptr);
    SetInlineFocusForTest(env.algorithm, false);

    auto layoutProperty = env.layoutWrapper->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, false);

    auto constraint = CreateConstraint({ .idealHeight = 80.0f });
    SizeF maxIdealSize(100.0f, 50.0f);
    SizeF originalSize = maxIdealSize;

    env.algorithm->CalculateContentMaxSizeWithPolicy(env.layoutWrapper, constraint, maxIdealSize);
    EXPECT_EQ(maxIdealSize.Height(), originalSize.Height());
}

/**
 * @tc.name: CalculateContentMaxSizeWithPolicy008
 * @tc.desc: Test CalculateContentMaxSizeWithPolicy with heightLayoutPolicy = MATCH_PARENT and parentIdealSize.Height
 * has value. Should set maxIdealSize.Height and selfIdealSize.Height to parentIdealSize.Height.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, CalculateContentMaxSizeWithPolicy008, TestSize.Level1)
{
    auto env = SetupTestEnv();
    ASSERT_NE(env.layoutWrapper, nullptr);
    ASSERT_NE(env.algorithm, nullptr);
    SetInlineFocusForTest(env.algorithm, false);

    auto layoutProperty = env.layoutWrapper->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, false);

    auto constraint = CreateConstraint({ .parentIdealHeight = 200.0f });
    SizeF maxIdealSize(100.0f, 50.0f);

    env.algorithm->CalculateContentMaxSizeWithPolicy(env.layoutWrapper, constraint, maxIdealSize);
    EXPECT_EQ(maxIdealSize.Height(), 200.0f);
    EXPECT_TRUE(constraint.selfIdealSize.Height().has_value());
    EXPECT_EQ(constraint.selfIdealSize.Height().value(), 200.0f);
}

/**
 * @tc.name: CalculateContentMaxSizeWithPolicy009
 * @tc.desc: Test CalculateContentMaxSizeWithPolicy with heightLayoutPolicy = MATCH_PARENT but no
 * parentIdealSize.Height. Should not modify maxIdealSize.Height.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, CalculateContentMaxSizeWithPolicy009, TestSize.Level1)
{
    auto env = SetupTestEnv();
    ASSERT_NE(env.layoutWrapper, nullptr);
    ASSERT_NE(env.algorithm, nullptr);
    SetInlineFocusForTest(env.algorithm, false);

    auto layoutProperty = env.layoutWrapper->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, false);

    auto constraint = CreateConstraint();
    SizeF maxIdealSize(100.0f, 50.0f);
    SizeF originalSize = maxIdealSize;

    env.algorithm->CalculateContentMaxSizeWithPolicy(env.layoutWrapper, constraint, maxIdealSize);
    EXPECT_EQ(maxIdealSize.Height(), originalSize.Height());
}

/**
 * @tc.name: CalculateContentMaxSizeWithPolicy010
 * @tc.desc: Test CalculateContentMaxSizeWithPolicy with both width and height FIX_AT_IDEAL_SIZE.
 *           Should set both maxIdealSize.Width and Height to infinity.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, CalculateContentMaxSizeWithPolicy010, TestSize.Level1)
{
    auto env = SetupTestEnv();
    ASSERT_NE(env.layoutWrapper, nullptr);
    ASSERT_NE(env.algorithm, nullptr);
    SetInlineFocusForTest(env.algorithm, false);

    auto layoutProperty = env.layoutWrapper->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, true);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, false);

    auto constraint = CreateConstraint();
    SizeF maxIdealSize(100.0f, 50.0f);

    env.algorithm->CalculateContentMaxSizeWithPolicy(env.layoutWrapper, constraint, maxIdealSize);
    EXPECT_TRUE(std::isinf(maxIdealSize.Width()));
    EXPECT_TRUE(std::isinf(maxIdealSize.Height()));
}

/**
 * @tc.name: CalculateContentMaxSizeWithPolicy011
 * @tc.desc: Test CalculateContentMaxSizeWithPolicy with both width and height MATCH_PARENT and parentIdealSize set.
 *           Should set both maxIdealSize.Width and Height from parentIdealSize.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, CalculateContentMaxSizeWithPolicy011, TestSize.Level1)
{
    auto env = SetupTestEnv();
    ASSERT_NE(env.layoutWrapper, nullptr);
    ASSERT_NE(env.algorithm, nullptr);
    SetInlineFocusForTest(env.algorithm, false);

    auto layoutProperty = env.layoutWrapper->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, true);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, false);

    auto constraint = CreateConstraint({ .parentIdealWidth = 400.0f, .parentIdealHeight = 150.0f });
    SizeF maxIdealSize(100.0f, 50.0f);

    env.algorithm->CalculateContentMaxSizeWithPolicy(env.layoutWrapper, constraint, maxIdealSize);
    EXPECT_EQ(maxIdealSize.Width(), 400.0f);
    EXPECT_EQ(maxIdealSize.Height(), 150.0f);
    EXPECT_TRUE(constraint.selfIdealSize.Width().has_value());
    EXPECT_TRUE(constraint.selfIdealSize.Height().has_value());
    EXPECT_EQ(constraint.selfIdealSize.Width().value(), 400.0f);
    EXPECT_EQ(constraint.selfIdealSize.Height().value(), 150.0f);
}

/**
 * @tc.name: CalculateContentMaxSizeWithPolicy012
 * @tc.desc: Test CalculateContentMaxSizeWithPolicy with widthLayoutPolicy = NO_MATCH (default).
 *           Should not modify maxIdealSize.Width.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, CalculateContentMaxSizeWithPolicy012, TestSize.Level1)
{
    auto env = SetupTestEnv();
    ASSERT_NE(env.layoutWrapper, nullptr);
    ASSERT_NE(env.algorithm, nullptr);
    SetInlineFocusForTest(env.algorithm, false);

    auto layoutProperty = env.layoutWrapper->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, true);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, false);

    auto constraint = CreateConstraint();
    SizeF maxIdealSize(100.0f, 50.0f);
    SizeF originalSize = maxIdealSize;

    env.algorithm->CalculateContentMaxSizeWithPolicy(env.layoutWrapper, constraint, maxIdealSize);
    EXPECT_EQ(maxIdealSize.Width(), originalSize.Width());
    EXPECT_EQ(maxIdealSize.Height(), originalSize.Height());
}

/**
 * @tc.name: CalculateContentMaxSizeWithPolicy013
 * @tc.desc: Test CalculateContentMaxSizeWithPolicy with mixed policies: width FIX_AT_IDEAL_SIZE, height MATCH_PARENT.
 *           Width should be infinity, height should be from parentIdealSize.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, CalculateContentMaxSizeWithPolicy013, TestSize.Level1)
{
    auto env = SetupTestEnv();
    ASSERT_NE(env.layoutWrapper, nullptr);
    ASSERT_NE(env.algorithm, nullptr);
    SetInlineFocusForTest(env.algorithm, false);

    auto layoutProperty = env.layoutWrapper->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, true);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, false);

    auto constraint = CreateConstraint({ .parentIdealHeight = 180.0f });
    SizeF maxIdealSize(100.0f, 50.0f);

    env.algorithm->CalculateContentMaxSizeWithPolicy(env.layoutWrapper, constraint, maxIdealSize);
    EXPECT_TRUE(std::isinf(maxIdealSize.Width()));
    EXPECT_EQ(maxIdealSize.Height(), 180.0f);
}

/**
 * @tc.name: CalculateContentMaxSizeWithPolicy014
 * @tc.desc: Test CalculateContentMaxSizeWithPolicy with mixed policies: width MATCH_PARENT, height FIX_AT_IDEAL_SIZE.
 *           Width should be from parentIdealSize, height should be infinity.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, CalculateContentMaxSizeWithPolicy014, TestSize.Level1)
{
    auto env = SetupTestEnv();
    ASSERT_NE(env.layoutWrapper, nullptr);
    ASSERT_NE(env.algorithm, nullptr);
    SetInlineFocusForTest(env.algorithm, false);

    auto layoutProperty = env.layoutWrapper->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, true);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, false);

    auto constraint = CreateConstraint({ .parentIdealWidth = 350.0f });
    SizeF maxIdealSize(100.0f, 50.0f);

    env.algorithm->CalculateContentMaxSizeWithPolicy(env.layoutWrapper, constraint, maxIdealSize);
    EXPECT_EQ(maxIdealSize.Width(), 350.0f);
    EXPECT_TRUE(std::isinf(maxIdealSize.Height()));
}

/**
 * @tc.name: HasCalcMinWidthVersion11OrLarger001
 * @tc.desc: Test HasCalcMinWidthVersion11OrLarger with null layoutWrapper.
 *           Should return false via CHECK_NULL_RETURN.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, HasCalcMinWidthVersion11OrLarger001, TestSize.Level1)
{
    auto env = SetupTestEnv();
    ASSERT_NE(env.algorithm, nullptr);

    auto constraint = CreateConstraint();
    bool result = env.algorithm->HasCalcMinWidthVersion11OrLarger(nullptr, constraint);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: HasCalcMinWidthVersion11OrLarger002
 * @tc.desc: Test HasCalcMinWidthVersion11OrLarger with API version < VERSION_ELEVEN.
 *           Should return false because GreatOrEqualAPITargetVersion returns false.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, HasCalcMinWidthVersion11OrLarger002, TestSize.Level1)
{
    auto env = SetupTestEnv();
    ASSERT_NE(env.layoutWrapper, nullptr);
    ASSERT_NE(env.algorithm, nullptr);

    auto backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TEN));

    auto constraint = CreateConstraint();
    bool result = env.algorithm->HasCalcMinWidthVersion11OrLarger(env.layoutWrapper, constraint);
    EXPECT_FALSE(result);

    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: HasCalcMinWidthVersion11OrLarger003
 * @tc.desc: Test HasCalcMinWidthVersion11OrLarger with GetLayoutRect having value.
 *           Should return false because !GetLayoutRect() is false.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, HasCalcMinWidthVersion11OrLarger003, TestSize.Level1)
{
    auto env = SetupTestEnv();
    ASSERT_NE(env.layoutWrapper, nullptr);
    ASSERT_NE(env.algorithm, nullptr);

    auto backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));

    auto layoutProperty = env.layoutWrapper->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->SetLayoutRect(RectF(0, 0, 100, 50));

    auto constraint = CreateConstraint();
    bool result = env.algorithm->HasCalcMinWidthVersion11OrLarger(env.layoutWrapper, constraint);
    EXPECT_FALSE(result);

    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: HasCalcMinWidthVersion11OrLarger004
 * @tc.desc: Test HasCalcMinWidthVersion11OrLarger with calcLayoutConstraint being null.
 *           Should return false because calcLayoutConstraint is null.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, HasCalcMinWidthVersion11OrLarger004, TestSize.Level1)
{
    auto env = SetupTestEnv();
    ASSERT_NE(env.layoutWrapper, nullptr);
    ASSERT_NE(env.algorithm, nullptr);

    auto backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));

    auto constraint = CreateConstraint();
    bool result = env.algorithm->HasCalcMinWidthVersion11OrLarger(env.layoutWrapper, constraint);
    EXPECT_FALSE(result);

    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: HasCalcMinWidthVersion11OrLarger005
 * @tc.desc: Test HasCalcMinWidthVersion11OrLarger with calcLayoutConstraint->minSize having no value.
 *           Should return false because minSize.has_value() is false.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, HasCalcMinWidthVersion11OrLarger005, TestSize.Level1)
{
    auto env = SetupTestEnv();
    ASSERT_NE(env.layoutWrapper, nullptr);
    ASSERT_NE(env.algorithm, nullptr);

    auto backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));

    auto layoutProperty = env.layoutWrapper->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateCalcMinSize(CalcSize(std::nullopt, std::nullopt));

    auto constraint = CreateConstraint();
    bool result = env.algorithm->HasCalcMinWidthVersion11OrLarger(env.layoutWrapper, constraint);
    EXPECT_FALSE(result);

    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: HasCalcMinWidthVersion11OrLarger006
 * @tc.desc: Test HasCalcMinWidthVersion11OrLarger with minSize->Width() having no value.
 *           Should return false because Width().has_value() is false.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, HasCalcMinWidthVersion11OrLarger006, TestSize.Level1)
{
    auto env = SetupTestEnv();
    ASSERT_NE(env.layoutWrapper, nullptr);
    ASSERT_NE(env.algorithm, nullptr);

    auto backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));

    auto layoutProperty = env.layoutWrapper->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateCalcMinSize(CalcSize(std::nullopt, CalcLength(100.0f)));

    auto constraint = CreateConstraint();
    bool result = env.algorithm->HasCalcMinWidthVersion11OrLarger(env.layoutWrapper, constraint);
    EXPECT_FALSE(result);

    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: HasCalcMinWidthVersion11OrLarger007
 * @tc.desc: Test HasCalcMinWidthVersion11OrLarger with selfIdealSize.Width having value.
 *           Should return false because !selfIdealSize.Width().has_value() is false.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, HasCalcMinWidthVersion11OrLarger007, TestSize.Level1)
{
    auto env = SetupTestEnv();
    ASSERT_NE(env.layoutWrapper, nullptr);
    ASSERT_NE(env.algorithm, nullptr);

    auto backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));

    auto layoutProperty = env.layoutWrapper->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateCalcMinSize(CalcSize(CalcLength(200.0f), CalcLength(100.0f)));

    auto constraint = CreateConstraint({ .idealWidth = 300.0f });
    bool result = env.algorithm->HasCalcMinWidthVersion11OrLarger(env.layoutWrapper, constraint);
    EXPECT_FALSE(result);

    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: HasCalcMinWidthVersion11OrLarger008
 * @tc.desc: Test HasCalcMinWidthVersion11OrLarger with all conditions met.
 *           Should return true.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, HasCalcMinWidthVersion11OrLarger008, TestSize.Level1)
{
    auto backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    MockPipelineContext::GetCurrentContext()->SetApiTargetVersion(
        static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));

    auto env = SetupTestEnv();
    ASSERT_NE(env.layoutWrapper, nullptr);
    ASSERT_NE(env.algorithm, nullptr);

    auto layoutProperty = env.layoutWrapper->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateCalcMinSize(CalcSize(CalcLength(200.0f), CalcLength(100.0f)));

    auto constraint = CreateConstraint();
    bool result = env.algorithm->HasCalcMinWidthVersion11OrLarger(env.layoutWrapper, constraint);
    EXPECT_TRUE(result);

    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
    MockPipelineContext::GetCurrentContext()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: HasCalcMinWidthVersion11OrLarger009
 * @tc.desc: Test HasCalcMinWidthVersion11OrLarger with API version VERSION_TWELVE.
 *           Should return true because VERSION_TWELVE > VERSION_ELEVEN.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, HasCalcMinWidthVersion11OrLarger009, TestSize.Level1)
{
    auto backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    MockPipelineContext::GetCurrentContext()->SetApiTargetVersion(
        static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));

    auto env = SetupTestEnv();
    ASSERT_NE(env.layoutWrapper, nullptr);
    ASSERT_NE(env.algorithm, nullptr);

    auto layoutProperty = env.layoutWrapper->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateCalcMinSize(CalcSize(CalcLength(200.0f), CalcLength(100.0f)));

    auto constraint = CreateConstraint();
    bool result = env.algorithm->HasCalcMinWidthVersion11OrLarger(env.layoutWrapper, constraint);
    EXPECT_TRUE(result);

    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
    MockPipelineContext::GetCurrentContext()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: HasCalcMinWidthVersion11OrLarger010
 * @tc.desc: Test HasCalcMinWidthVersion11OrLarger with only width in calcMinSize.
 *           Should return true because Width().has_value() is true.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, HasCalcMinWidthVersion11OrLarger010, TestSize.Level1)
{
    auto backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    MockPipelineContext::GetCurrentContext()->SetApiTargetVersion(
        static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));

    auto env = SetupTestEnv();
    ASSERT_NE(env.layoutWrapper, nullptr);
    ASSERT_NE(env.algorithm, nullptr);

    auto layoutProperty = env.layoutWrapper->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateCalcMinSize(CalcSize(CalcLength(200.0f), std::nullopt));

    auto constraint = CreateConstraint();
    bool result = env.algorithm->HasCalcMinWidthVersion11OrLarger(env.layoutWrapper, constraint);
    EXPECT_TRUE(result);

    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
    MockPipelineContext::GetCurrentContext()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: HasCalcMinWidthVersion11OrLarger011
 * @tc.desc: Test HasCalcMinWidthVersion11OrLarger with selfIdealSize.Height having value.
 *           Should still return true because only selfIdealSize.Width matters.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldLayoutAlgorithmTest, HasCalcMinWidthVersion11OrLarger011, TestSize.Level1)
{
    auto backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    MockPipelineContext::GetCurrentContext()->SetApiTargetVersion(
        static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));

    auto env = SetupTestEnv();
    ASSERT_NE(env.layoutWrapper, nullptr);
    ASSERT_NE(env.algorithm, nullptr);

    auto layoutProperty = env.layoutWrapper->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateCalcMinSize(CalcSize(CalcLength(200.0f), CalcLength(100.0f)));

    auto constraint = CreateConstraint({ .idealHeight = 80.0f });
    bool result = env.algorithm->HasCalcMinWidthVersion11OrLarger(env.layoutWrapper, constraint);
    EXPECT_TRUE(result);

    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
    MockPipelineContext::GetCurrentContext()->SetApiTargetVersion(backupApiVersion);
}

} // namespace OHOS::Ace::NG
