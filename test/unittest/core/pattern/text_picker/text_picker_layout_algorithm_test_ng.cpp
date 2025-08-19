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
#define private public
#define protected public
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_default.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components/theme/icon_theme.h"
#include "core/components/picker/picker_theme.h"
#include "core/components/button/button_theme.h"
#include "core/components/dialog/dialog_theme.h"
#include "core/components_ng/pattern/text_picker/textpicker_layout_algorithm.h"
#include "core/components_ng/pattern/text_picker/textpicker_pattern.h"
#include "core/components_ng/pattern/text_picker/textpicker_model_ng.h"
#include "core/components_ng/pattern/flex/flex_layout_property.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
    constexpr float USER_IDEAL_SIZE_0 = 0.0f;
    constexpr float USER_IDEAL_SIZE_400 = 400.0f;
    constexpr uint32_t SELECTED_INDEX_1 = 1;
    constexpr float USER_IDEAL_SIZE_100 = 100.0f;
    constexpr float USER_IDEAL_SIZE_80 = 80.0f;
}

class TextPickerLayoutAlgorithmTest : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    RefPtr<Theme> GetThemeByType(ThemeType type);
    void CreateSingleTextPicker();

    RefPtr<IconTheme> iconThem_;
    RefPtr<DialogTheme> dialogTheme_;
    RefPtr<PickerTheme> pickerThem_;
    RefPtr<ButtonTheme> buttonTheme_;

    RefPtr<FrameNode> frameNode_;
};

class TestNode : public UINode {
    DECLARE_ACE_TYPE(TestNode, UINode);

public:
    static RefPtr<TestNode> CreateTestNode(int32_t nodeId)
    {
        auto spanNode = MakeRefPtr<TestNode>(nodeId);
        return spanNode;
    }

    bool IsAtomicNode() const override
    {
        return true;
    }

    explicit TestNode(int32_t nodeId) : UINode("TestNode", nodeId) {}
    ~TestNode() override = default;
};

void TextPickerLayoutAlgorithmTest::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void TextPickerLayoutAlgorithmTest::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void TextPickerLayoutAlgorithmTest::SetUp()
{
    iconThem_ = AceType::MakeRefPtr<IconTheme>();
    dialogTheme_ = AceType::MakeRefPtr<DialogTheme>();
    pickerThem_ = MockThemeDefault::GetPickerTheme();
    buttonTheme_ = AceType::MakeRefPtr<ButtonTheme>();

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);

    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillRepeatedly([this](ThemeType type) -> RefPtr<Theme> {return GetThemeByType(type);});

    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([this](ThemeType type, int32_t themeScopeId) -> RefPtr<Theme> {return GetThemeByType(type);});
}

void TextPickerLayoutAlgorithmTest::TearDown()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    ViewStackProcessor::GetInstance()->ClearStack();
}

RefPtr<Theme> TextPickerLayoutAlgorithmTest::GetThemeByType(ThemeType type)
{
    if (type == IconTheme::TypeId()) {
        return iconThem_;
    } else if (type == DialogTheme::TypeId()) {
        return dialogTheme_;
    } else if (type == PickerTheme::TypeId()) {
        return pickerThem_;
    } else if (type == ButtonTheme::TypeId()) {
        return buttonTheme_;
    } else {
        return nullptr;
    }
}

void TextPickerLayoutAlgorithmTest::CreateSingleTextPicker()
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    std::vector<NG::RangeContent> range = { { "", "Text1" }, { "", "Text2" }, { "", "Text3" } };
    TextPickerModelNG::GetInstance()->SetRange(range);
    TextPickerModelNG::GetInstance()->SetSelected(SELECTED_INDEX_1);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    ASSERT_NE(element, nullptr);
    EXPECT_EQ(element->GetTag(), V2::TEXT_PICKER_ETS_TAG);
    frameNode_ = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode_, nullptr);
    frameNode_->MarkModifyDone();
}

/**
 * @tc.name: ReCalcItemHeightScale001
 * @tc.desc: Test ReCalcItemHeightScale when AdjustFontSizeScale return 0.0_vp.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerLayoutAlgorithmTest, ReCalcItemHeightScale001, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create pipeline and pickerTheme.
    */
    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipeline, nullptr);

    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    EXPECT_NE(pickerTheme, nullptr);
    TextPickerLayoutAlgorithm textPickerLayoutAlgorithm;

    /**
    * @tc.steps: step2. Call ReCalcItemHeightScale.
    * @tc.expected: set fontScale is zero, and AdjustFontSizeScale will return 0.0_vp.
    */
    Dimension userSetHeight = 10.0_vp;
    pipeline->fontScale_ = 0.0f;

    /**
     * @tc.cases: case1. isDividerSpacing is true.
     */
    float expectValue = pickerTheme->GetPickerDialogFontPadding().ConvertToPx() * 2 /
                        pickerTheme->GetDividerSpacing().ConvertToPx();
    bool isDividerSpacing = true;
    float res = textPickerLayoutAlgorithm.ReCalcItemHeightScale(userSetHeight, isDividerSpacing);
    EXPECT_EQ(res, expectValue);

    /**
     * @tc.cases: case2. isDividerSpacing is false.
     */
    expectValue = pickerTheme->GetPickerDialogFontPadding().ConvertToPx() * 2 /
                  pickerTheme->GetGradientHeight().ConvertToPx();
    isDividerSpacing = false;
    res = textPickerLayoutAlgorithm.ReCalcItemHeightScale(userSetHeight, isDividerSpacing);
    EXPECT_EQ(res, expectValue);
}

/**
 * @tc.name: ReCalcItemHeightScale002
 * @tc.desc: Test ReCalcItemHeightScale when fontScale,
 *           pickerDialogNormalFontScale_, pickerDialogMaxTwoFontScale_ are zero.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerLayoutAlgorithmTest, ReCalcItemHeightScale002, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create pipeline and pickerTheme.
    */
    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipeline, nullptr);

    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    EXPECT_NE(pickerTheme, nullptr);
    TextPickerLayoutAlgorithm textPickerLayoutAlgorithm;

    /**
    * @tc.steps: step2. Call ReCalcItemHeightScale.
    * @tc.expected: set fontScale, pickerDialogNormalFontScale_, pickerDialogMaxTwoFontScale_ are zero.
    */
    Dimension userSetHeight = 10.0_vp;
    pipeline->fontScale_ = 0.0f;
    pickerTheme->pickerDialogNormalFontScale_ = 0.00;
    pickerTheme->pickerDialogMaxTwoFontScale_ = 0.00;

    /**
     * @tc.cases: case1. isDividerSpacing is true.
     */
    bool isDividerSpacing = true;
    float res = textPickerLayoutAlgorithm.ReCalcItemHeightScale(userSetHeight, isDividerSpacing);
    EXPECT_EQ(res, 1.0f);

    /**
     * @tc.cases: case2. isDividerSpacing is false.
     */
    isDividerSpacing = false;
    res = textPickerLayoutAlgorithm.ReCalcItemHeightScale(userSetHeight, isDividerSpacing);
    EXPECT_EQ(res, 1.0f);
}

/**
 * @tc.name: ReCalcItemHeightScale003
 * @tc.desc: Test ReCalcItemHeightScale when GreatOrEqualCustomPrecision() is false.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerLayoutAlgorithmTest, ReCalcItemHeightScale003, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create pipeline and pickerTheme.
    */
    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipeline, nullptr);

    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    EXPECT_NE(pickerTheme, nullptr);
    TextPickerLayoutAlgorithm textPickerLayoutAlgorithm;
    float expectValue = 7.3f;

    /**
    * @tc.steps: step2. Call ReCalcItemHeightScale.
    * @tc.expected: GreatOrEqualCustomPrecision() is false.
    */
    Dimension userSetHeight = 10.0_vp;
    pipeline->fontScale_ = 5.0f;
    pickerTheme->pickerDialogNormalFontScale_ = 0.00;
    pickerTheme->pickerDialogMaxTwoFontScale_ = 10.00;

    /**
     * @tc.cases: case1. isDividerSpacing is false, pickerDialogFontPadding < gradientHeightLimit_.
     */
    pickerTheme->pickerDialogFontPadding_ = 28.0_vp;
    pickerTheme->gradientHeightLimit_ = 64.0_vp;
    pickerTheme->dividerSpacingHeightLimit_ = 28.0_vp;
    pickerTheme->gradientHeight_ = Dimension(8.0, DimensionUnit::PX);

    bool isDividerSpacing = false;
    float res = textPickerLayoutAlgorithm.ReCalcItemHeightScale(userSetHeight, isDividerSpacing);
    EXPECT_EQ(res, expectValue);

    /**
     * @tc.cases: case2. isDividerSpacing is true, pickerDialogFontPadding < dividerSpacingHeightLimit_.
     */
    pickerTheme->pickerDialogFontPadding_ = 28.0_vp;
    pickerTheme->gradientHeightLimit_ = 28.0_vp;
    pickerTheme->dividerSpacingHeightLimit_ = 64.0_vp;
    pickerTheme->dividerSpacing_ = Dimension(8.0, DimensionUnit::PX);

    isDividerSpacing = true;
    res = textPickerLayoutAlgorithm.ReCalcItemHeightScale(userSetHeight, isDividerSpacing);
    EXPECT_EQ(res, expectValue);
}

/**
 * @tc.name: ReCalcItemHeightScale004
 * @tc.desc: Test ReCalcItemHeightScale when GreatOrEqualCustomPrecision() is true.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerLayoutAlgorithmTest, ReCalcItemHeightScale004, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create pipeline and pickerTheme.
    */
    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipeline, nullptr);

    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    EXPECT_NE(pickerTheme, nullptr);
    TextPickerLayoutAlgorithm textPickerLayoutAlgorithm;
    float expectValue = 2.5f;

    /**
    * @tc.steps: step2. Call ReCalcItemHeightScale.
    * @tc.expected: GreatOrEqualCustomPrecision() is true.
    */
    Dimension userSetHeight = 10.0_vp;
    pipeline->fontScale_ = 5.0f;
    pickerTheme->pickerDialogNormalFontScale_ = 0.00;
    pickerTheme->pickerDialogMaxTwoFontScale_ = 10.00;

    /**
     * @tc.cases: case1. isDividerSpacing is false, pickerDialogFontPadding >= gradientHeightLimit_.
     */
    pickerTheme->pickerDialogFontPadding_ = 28.0_vp;
    pickerTheme->gradientHeightLimit_ = 20.0_vp;
    pickerTheme->dividerSpacingHeightLimit_ = 48.0_vp;
    pickerTheme->gradientHeight_ = Dimension(8.0, DimensionUnit::PX);

    bool isDividerSpacing = false;
    float res = textPickerLayoutAlgorithm.ReCalcItemHeightScale(userSetHeight, isDividerSpacing);
    EXPECT_EQ(res, expectValue);

    /**
     * @tc.cases: case2. isDividerSpacing is true, pickerDialogFontPadding >= dividerSpacingHeightLimit_.
     */
    pickerTheme->pickerDialogFontPadding_ = 28.0_vp;
    pickerTheme->gradientHeightLimit_ = 48.0_vp;
    pickerTheme->dividerSpacingHeightLimit_ = 20.0_vp;
    pickerTheme->dividerSpacing_ = Dimension(8.0, DimensionUnit::PX);

    isDividerSpacing = true;
    res = textPickerLayoutAlgorithm.ReCalcItemHeightScale(userSetHeight, isDividerSpacing);
    EXPECT_EQ(res, expectValue);
}

/**
 * @tc.name: ReCalcItemHeightScale005
 * @tc.desc: Test HandleMonthChange.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerLayoutAlgorithmTest, ReCalcItemHeightScale005, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create pipeline and pickerTheme.
    */
    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipeline, nullptr);

    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    EXPECT_NE(pickerTheme, nullptr);
    TextPickerLayoutAlgorithm textPickerLayoutAlgorithm;
    float expectValue = 1.0f;

    /**
    * @tc.steps: step2. Call ReCalcItemHeightScale.
    * @tc.expected: set fontScale is not zero.
    */
    Dimension userSetHeight = 10.0_vp;
    pipeline->fontScale_ = 5.0f;
    pickerTheme->pickerDialogNormalFontScale_ = 0.00;
    pickerTheme->pickerDialogMaxTwoFontScale_ = 10.00;

    /**
     * @tc.cases: case1. isDividerSpacing is false, and gradientHeight_ is zero.
     */
    pickerTheme->dividerSpacing_ = Dimension(10.0, DimensionUnit::PX);
    pickerTheme->gradientHeight_ = Dimension(0.0, DimensionUnit::PX);

    bool isDividerSpacing = false;
    float res = textPickerLayoutAlgorithm.ReCalcItemHeightScale(userSetHeight, isDividerSpacing);
    EXPECT_EQ(res, expectValue);

    /**
     * @tc.cases: case2. isDividerSpacing is true, and dividerSpacing_ is zero.
     */
    pickerTheme->dividerSpacing_ = Dimension(0.0, DimensionUnit::PX);
    pickerTheme->gradientHeight_ = Dimension(10.0, DimensionUnit::PX);

    isDividerSpacing = true;
    res = textPickerLayoutAlgorithm.ReCalcItemHeightScale(userSetHeight, isDividerSpacing);
    EXPECT_EQ(res, expectValue);
}

/**
 * @tc.name: BeforeCreateLayoutWrapper001
 * @tc.desc: Test BeforeCreateLayoutWrapper when layoutPolicy is WRAP_CONTENT.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerLayoutAlgorithmTest, BeforeCreateLayoutWrapper001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create TextPicker.
     */
    CreateSingleTextPicker();
    auto pickerPattern = frameNode_->GetPattern<TextPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);
    pickerPattern->OnModifyDone();
    auto layoutAlgorithm = pickerPattern->CreateLayoutAlgorithm();

    /**
     * @tc.steps: step2. Set a specified size for the TextPicker.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, frameNode_->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));

    auto pickerProperty = frameNode_->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    pickerProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(USER_IDEAL_SIZE_400),
        CalcLength(USER_IDEAL_SIZE_400)));
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_TRUE(layoutProperty->calcLayoutConstraint_->selfIdealSize.has_value());
    EXPECT_EQ(layoutProperty->calcLayoutConstraint_->selfIdealSize->Width().value(), CalcLength(USER_IDEAL_SIZE_400));
    EXPECT_EQ(layoutProperty->calcLayoutConstraint_->selfIdealSize->Height().value(), CalcLength(USER_IDEAL_SIZE_400));

    /**
     * @tc.steps: step3. Set widthLayoutPolicy_ and heightLayoutPolicy_ to LayoutCalPolicy::WRAP_CONTENT.
     */
    LayoutPolicyProperty layoutPolicyProperty;
    layoutPolicyProperty.widthLayoutPolicy_ = LayoutCalPolicy::WRAP_CONTENT;
    layoutPolicyProperty.heightLayoutPolicy_ = LayoutCalPolicy::WRAP_CONTENT;
    layoutProperty->layoutPolicy_ = layoutPolicyProperty;

    /**
     * @tc.steps: step4. Call BeforeCreateLayoutWrapper function.
     * @tc.expected: The width and height of the TextPicker will be set to 0.
     */
    pickerPattern->BeforeCreateLayoutWrapper();
    EXPECT_TRUE(layoutProperty->calcLayoutConstraint_->selfIdealSize.has_value());
    EXPECT_EQ(layoutProperty->calcLayoutConstraint_->selfIdealSize->Width().value(), CalcLength(USER_IDEAL_SIZE_0));
    EXPECT_EQ(layoutProperty->calcLayoutConstraint_->selfIdealSize->Height().value(), CalcLength(USER_IDEAL_SIZE_0));
}

/**
 * @tc.name: BeforeCreateLayoutWrapper002
 * @tc.desc: Test BeforeCreateLayoutWrapper when layoutPolicy is FIX_AT_IDEAL_SIZE.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerLayoutAlgorithmTest, BeforeCreateLayoutWrapper002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create TextPicker.
     */
    CreateSingleTextPicker();
    auto pickerPattern = frameNode_->GetPattern<TextPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);
    pickerPattern->OnModifyDone();
    auto layoutAlgorithm = pickerPattern->CreateLayoutAlgorithm();

    /**
     * @tc.steps: step2. Set a specified size for the TextPicker.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, frameNode_->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));

    auto pickerProperty = frameNode_->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    pickerProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(USER_IDEAL_SIZE_400),
        CalcLength(USER_IDEAL_SIZE_400)));
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_TRUE(layoutProperty->calcLayoutConstraint_->selfIdealSize.has_value());
    EXPECT_EQ(layoutProperty->calcLayoutConstraint_->selfIdealSize->Width().value(), CalcLength(USER_IDEAL_SIZE_400));
    EXPECT_EQ(layoutProperty->calcLayoutConstraint_->selfIdealSize->Height().value(), CalcLength(USER_IDEAL_SIZE_400));

    /**
     * @tc.steps: step3. Set widthLayoutPolicy_ and heightLayoutPolicy_ to LayoutCalPolicy::FIX_AT_IDEAL_SIZE.
     */
    LayoutPolicyProperty layoutPolicyProperty;
    layoutPolicyProperty.widthLayoutPolicy_ = LayoutCalPolicy::FIX_AT_IDEAL_SIZE;
    layoutPolicyProperty.heightLayoutPolicy_ = LayoutCalPolicy::FIX_AT_IDEAL_SIZE;
    layoutProperty->layoutPolicy_ = layoutPolicyProperty;

    /**
     * @tc.steps: step4. Call BeforeCreateLayoutWrapper function.
     * @tc.expected: The width and height of the TextPicker will be set to 0.
     */
    pickerPattern->BeforeCreateLayoutWrapper();
    EXPECT_TRUE(layoutProperty->calcLayoutConstraint_->selfIdealSize.has_value());
    EXPECT_EQ(layoutProperty->calcLayoutConstraint_->selfIdealSize->Width().value(), CalcLength(USER_IDEAL_SIZE_0));
    EXPECT_EQ(layoutProperty->calcLayoutConstraint_->selfIdealSize->Height().value(), CalcLength(USER_IDEAL_SIZE_0));
}

/**
 * @tc.name: BeforeCreateLayoutWrapper003
 * @tc.desc: Test BeforeCreateLayoutWrapper when layoutPolicy is MATCH_PARENT.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerLayoutAlgorithmTest, BeforeCreateLayoutWrapper003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create TextPicker.
     */
    CreateSingleTextPicker();
    auto pickerPattern = frameNode_->GetPattern<TextPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);
    pickerPattern->OnModifyDone();
    auto layoutAlgorithm = pickerPattern->CreateLayoutAlgorithm();

    /**
     * @tc.steps: step2. Set a specified size for the TextPicker.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, frameNode_->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));

    auto pickerProperty = frameNode_->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    pickerProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(USER_IDEAL_SIZE_400),
        CalcLength(USER_IDEAL_SIZE_400)));
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_TRUE(layoutProperty->calcLayoutConstraint_->selfIdealSize.has_value());
    EXPECT_EQ(layoutProperty->calcLayoutConstraint_->selfIdealSize->Width().value(), CalcLength(USER_IDEAL_SIZE_400));
    EXPECT_EQ(layoutProperty->calcLayoutConstraint_->selfIdealSize->Height().value(), CalcLength(USER_IDEAL_SIZE_400));

    /**
     * @tc.steps: step3. Set widthLayoutPolicy_ and heightLayoutPolicy_ to LayoutCalPolicy::MATCH_PARENT.
     */
    LayoutPolicyProperty layoutPolicyProperty;
    layoutPolicyProperty.widthLayoutPolicy_ = LayoutCalPolicy::MATCH_PARENT;
    layoutPolicyProperty.heightLayoutPolicy_ = LayoutCalPolicy::MATCH_PARENT;
    layoutProperty->layoutPolicy_ = layoutPolicyProperty;

    /**
     * @tc.steps: step4. Call BeforeCreateLayoutWrapper function.
     * @tc.expected: The width and height of the TextPicker will not be changed.
     */
    pickerPattern->BeforeCreateLayoutWrapper();
    EXPECT_TRUE(layoutProperty->calcLayoutConstraint_->selfIdealSize.has_value());
    EXPECT_EQ(layoutProperty->calcLayoutConstraint_->selfIdealSize->Width().value(), CalcLength(USER_IDEAL_SIZE_400));
    EXPECT_EQ(layoutProperty->calcLayoutConstraint_->selfIdealSize->Height().value(), CalcLength(USER_IDEAL_SIZE_400));
}

/**
 * @tc.name: BeforeCreateLayoutWrapper004
 * @tc.desc: Test BeforeCreateLayoutWrapper when layoutPolicy is NO_MATCH.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerLayoutAlgorithmTest, BeforeCreateLayoutWrapper004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create TextPicker.
     */
    CreateSingleTextPicker();
    auto pickerPattern = frameNode_->GetPattern<TextPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);
    pickerPattern->OnModifyDone();
    auto layoutAlgorithm = pickerPattern->CreateLayoutAlgorithm();

    /**
     * @tc.steps: step2. Set a specified size for the TextPicker.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, frameNode_->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));

    auto pickerProperty = frameNode_->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    pickerProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(USER_IDEAL_SIZE_400),
        CalcLength(USER_IDEAL_SIZE_400)));
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_TRUE(layoutProperty->calcLayoutConstraint_->selfIdealSize.has_value());
    EXPECT_EQ(layoutProperty->calcLayoutConstraint_->selfIdealSize->Width().value(), CalcLength(USER_IDEAL_SIZE_400));
    EXPECT_EQ(layoutProperty->calcLayoutConstraint_->selfIdealSize->Height().value(), CalcLength(USER_IDEAL_SIZE_400));

    /**
     * @tc.steps: step3. Set widthLayoutPolicy_ and heightLayoutPolicy_ to LayoutCalPolicy::NO_MATCH.
     */
    LayoutPolicyProperty layoutPolicyProperty;
    layoutPolicyProperty.widthLayoutPolicy_ = LayoutCalPolicy::NO_MATCH;
    layoutPolicyProperty.heightLayoutPolicy_ = LayoutCalPolicy::NO_MATCH;
    layoutProperty->layoutPolicy_ = layoutPolicyProperty;

    /**
     * @tc.steps: step4. Call BeforeCreateLayoutWrapper function.
     * @tc.expected: The width and height of the TextPicker will not be changed.
     */
    pickerPattern->BeforeCreateLayoutWrapper();
    EXPECT_TRUE(layoutProperty->calcLayoutConstraint_->selfIdealSize.has_value());
    EXPECT_EQ(layoutProperty->calcLayoutConstraint_->selfIdealSize->Width().value(), CalcLength(USER_IDEAL_SIZE_400));
    EXPECT_EQ(layoutProperty->calcLayoutConstraint_->selfIdealSize->Height().value(), CalcLength(USER_IDEAL_SIZE_400));
}

/**
 * @tc.name: CheckAndUpdateColumnSizeWithMatch
 * @tc.desc: Test CheckAndUpdateColumnSize when layoutPolicy is MATCH_PARENT.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerLayoutAlgorithmTest, CheckAndUpdateColumnSizeWithMatch, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create TextPicker.
     */
    CreateSingleTextPicker();
    auto pickerPattern = frameNode_->GetPattern<TextPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);
    pickerPattern->OnModifyDone();

    /**
     * @tc.steps: step2. Set a specified size for the parentIdealSize.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, frameNode_->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutAlgorithm = pickerPattern->CreateLayoutAlgorithm();
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));

    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    LayoutConstraintF constraint;
    constraint.UpdateParentIdealSizeWithCheck({USER_IDEAL_SIZE_400, USER_IDEAL_SIZE_400});
    layoutProperty->UpdateLayoutConstraint(constraint);

    /**
     * @tc.steps: step3. Set widthLayoutPolicy_ and heightLayoutPolicy_ to LayoutCalPolicy::MATCH_PARENT.
     */
    LayoutPolicyProperty layoutPolicyProperty;
    layoutPolicyProperty.widthLayoutPolicy_ = LayoutCalPolicy::MATCH_PARENT;
    layoutPolicyProperty.heightLayoutPolicy_ = LayoutCalPolicy::MATCH_PARENT;
    layoutProperty->layoutPolicy_ = layoutPolicyProperty;

    /**
     * @tc.steps: step4. Call CheckAndUpdateColumnSize function.
     * @tc.expected: The width of the TextPicker will be set to USER_IDEAL_SIZE_400.
     */
    auto columnNodes = pickerPattern->GetColumnNodes();
    ASSERT_GT(columnNodes.size(), 0);
    SizeF size = SizeF(USER_IDEAL_SIZE_100, USER_IDEAL_SIZE_100);
    pickerPattern->CheckAndUpdateColumnSize(size, columnNodes[0], false);
    EXPECT_EQ(size.Width(), USER_IDEAL_SIZE_400);
    EXPECT_EQ(size.Height(), USER_IDEAL_SIZE_100);
}

/**
 * @tc.name: CheckAndUpdateColumnSizeWithNoMatch
 * @tc.desc: Test CheckAndUpdateColumnSize when layoutPolicy is NO_MATCH.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerLayoutAlgorithmTest, CheckAndUpdateColumnSizeWithNoMatch, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create TextPicker.
     */
    CreateSingleTextPicker();
    auto pickerPattern = frameNode_->GetPattern<TextPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);
    pickerPattern->OnModifyDone();

    /**
     * @tc.steps: step2. Set a specified size for the parentIdealSize.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, frameNode_->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutAlgorithm = pickerPattern->CreateLayoutAlgorithm();
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));

    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    LayoutConstraintF constraint;
    constraint.UpdateParentIdealSizeWithCheck({USER_IDEAL_SIZE_400, USER_IDEAL_SIZE_400});
    layoutProperty->UpdateLayoutConstraint(constraint);

    /**
     * @tc.steps: step3. Set a size for the stack node of the TextPicker.
     */
    auto stackNode = AceType::DynamicCast<FrameNode>(frameNode_->GetFirstChild());
    ASSERT_NE(stackNode, nullptr);
    auto stackLayoutProperty = stackNode->GetLayoutProperty();
    ASSERT_NE(stackLayoutProperty, nullptr);
    LayoutConstraintF stackConstraint;
    stackConstraint.UpdateParentIdealSizeWithCheck({USER_IDEAL_SIZE_80, USER_IDEAL_SIZE_80});
    stackLayoutProperty->UpdateLayoutConstraint(stackConstraint);

    /**
     * @tc.steps: step4. Set widthLayoutPolicy_ and heightLayoutPolicy_ to LayoutCalPolicy::NO_MATCH.
     */
    LayoutPolicyProperty layoutPolicyProperty;
    layoutPolicyProperty.widthLayoutPolicy_ = LayoutCalPolicy::NO_MATCH;
    layoutPolicyProperty.heightLayoutPolicy_ = LayoutCalPolicy::NO_MATCH;
    layoutProperty->layoutPolicy_ = layoutPolicyProperty;

    /**
     * @tc.steps: step5. Call CheckAndUpdateColumnSize function.
     * @tc.expected: The width and height of the TextPicker will be changed.
     */
    auto columnNodes = pickerPattern->GetColumnNodes();
    ASSERT_GT(columnNodes.size(), 0);
    SizeF size = SizeF(USER_IDEAL_SIZE_100, USER_IDEAL_SIZE_100);
    pickerPattern->CheckAndUpdateColumnSize(size, columnNodes[0], false);
    EXPECT_EQ(size.Width(), USER_IDEAL_SIZE_80);
    EXPECT_EQ(size.Height(), USER_IDEAL_SIZE_80);
}

} // namespace OHOS::Ace::NG
