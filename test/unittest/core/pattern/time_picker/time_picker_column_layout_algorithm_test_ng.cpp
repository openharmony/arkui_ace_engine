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
#include "core/components_ng/pattern/time_picker/timepicker_column_layout_algorithm.h"
#include "core/components_ng/pattern/time_picker/timepicker_row_pattern.h"
#include "core/components_ng/pattern/time_picker/timepicker_model_ng.h"
#include "core/components_ng/pattern/flex/flex_layout_property.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
    constexpr float USER_IDEAL_SIZE_0 = 0.0f;
    constexpr float USER_IDEAL_SIZE_400 = 400.0f;
}

class TimePickerColumnLayoutAlgorithmTest : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    RefPtr<Theme> GetThemeByType(ThemeType type);

    RefPtr<IconTheme> iconThem_;
    RefPtr<DialogTheme> dialogTheme_;
    RefPtr<PickerTheme> pickerThem_;
    RefPtr<ButtonTheme> buttonTheme_;
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

void TimePickerColumnLayoutAlgorithmTest::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void TimePickerColumnLayoutAlgorithmTest::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void TimePickerColumnLayoutAlgorithmTest::SetUp()
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

void TimePickerColumnLayoutAlgorithmTest::TearDown()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    ViewStackProcessor::GetInstance()->ClearStack();
}

RefPtr<Theme> TimePickerColumnLayoutAlgorithmTest::GetThemeByType(ThemeType type)
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

/**
 * @tc.name: ReCalcItemHeightScale001
 * @tc.desc: Test ReCalcItemHeightScale when AdjustFontSizeScale return 0.0_vp.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerColumnLayoutAlgorithmTest, ReCalcItemHeightScale001, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create pipeline and pickerTheme.
    */
    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipeline, nullptr);

    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    EXPECT_NE(pickerTheme, nullptr);
    TimePickerColumnLayoutAlgorithm timePickerColumnLayoutAlgorithm;

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
    float res = timePickerColumnLayoutAlgorithm.ReCalcItemHeightScale(userSetHeight, isDividerSpacing);
    EXPECT_EQ(res, expectValue);

    /**
     * @tc.cases: case2. isDividerSpacing is false.
     */
    expectValue = pickerTheme->GetPickerDialogFontPadding().ConvertToPx() * 2 /
                  pickerTheme->GetGradientHeight().ConvertToPx();
    isDividerSpacing = false;
    res = timePickerColumnLayoutAlgorithm.ReCalcItemHeightScale(userSetHeight, isDividerSpacing);
    EXPECT_EQ(res, expectValue);
}

/**
 * @tc.name: ReCalcItemHeightScale002
 * @tc.desc: Test ReCalcItemHeightScale when fontScale,
 *           pickerDialogNormalFontScale_, pickerDialogMaxTwoFontScale_ are zero.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerColumnLayoutAlgorithmTest, ReCalcItemHeightScale002, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create pipeline and pickerTheme.
    */
    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipeline, nullptr);

    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    EXPECT_NE(pickerTheme, nullptr);
    TimePickerColumnLayoutAlgorithm timePickerColumnLayoutAlgorithm;

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
    float res = timePickerColumnLayoutAlgorithm.ReCalcItemHeightScale(userSetHeight, isDividerSpacing);
    EXPECT_EQ(res, 1.0f);

    /**
     * @tc.cases: case2. isDividerSpacing is false.
     */
    isDividerSpacing = false;
    res = timePickerColumnLayoutAlgorithm.ReCalcItemHeightScale(userSetHeight, isDividerSpacing);
    EXPECT_EQ(res, 1.0f);
}

/**
 * @tc.name: ReCalcItemHeightScale003
 * @tc.desc: Test ReCalcItemHeightScale when GreatOrEqualCustomPrecision() is false.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerColumnLayoutAlgorithmTest, ReCalcItemHeightScale003, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create pipeline and pickerTheme.
    */
    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipeline, nullptr);

    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    EXPECT_NE(pickerTheme, nullptr);
    TimePickerColumnLayoutAlgorithm timePickerColumnLayoutAlgorithm;
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
    float res = timePickerColumnLayoutAlgorithm.ReCalcItemHeightScale(userSetHeight, isDividerSpacing);
    EXPECT_EQ(res, expectValue);

    /**
     * @tc.cases: case2. isDividerSpacing is true, pickerDialogFontPadding < dividerSpacingHeightLimit_.
     */
    pickerTheme->pickerDialogFontPadding_ = 28.0_vp;
    pickerTheme->gradientHeightLimit_ = 28.0_vp;
    pickerTheme->dividerSpacingHeightLimit_ = 64.0_vp;
    pickerTheme->dividerSpacing_ = Dimension(8.0, DimensionUnit::PX);

    isDividerSpacing = true;
    res = timePickerColumnLayoutAlgorithm.ReCalcItemHeightScale(userSetHeight, isDividerSpacing);
    EXPECT_EQ(res, expectValue);
}

/**
 * @tc.name: ReCalcItemHeightScale004
 * @tc.desc: Test ReCalcItemHeightScale when GreatOrEqualCustomPrecision() is true.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerColumnLayoutAlgorithmTest, ReCalcItemHeightScale004, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create pipeline and pickerTheme.
    */
    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipeline, nullptr);

    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    EXPECT_NE(pickerTheme, nullptr);
    TimePickerColumnLayoutAlgorithm timePickerColumnLayoutAlgorithm;
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
    float res = timePickerColumnLayoutAlgorithm.ReCalcItemHeightScale(userSetHeight, isDividerSpacing);
    EXPECT_EQ(res, expectValue);

    /**
     * @tc.cases: case2. isDividerSpacing is true, pickerDialogFontPadding >= dividerSpacingHeightLimit_.
     */
    pickerTheme->pickerDialogFontPadding_ = 28.0_vp;
    pickerTheme->gradientHeightLimit_ = 48.0_vp;
    pickerTheme->dividerSpacingHeightLimit_ = 20.0_vp;
    pickerTheme->dividerSpacing_ = Dimension(8.0, DimensionUnit::PX);

    isDividerSpacing = true;
    res = timePickerColumnLayoutAlgorithm.ReCalcItemHeightScale(userSetHeight, isDividerSpacing);
    EXPECT_EQ(res, expectValue);
}

/**
 * @tc.name: ReCalcItemHeightScale005
 * @tc.desc: Test HandleMonthChange.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerColumnLayoutAlgorithmTest, ReCalcItemHeightScale005, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create pipeline and pickerTheme.
    */
    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipeline, nullptr);

    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    EXPECT_NE(pickerTheme, nullptr);
    TimePickerColumnLayoutAlgorithm timePickerColumnLayoutAlgorithm;
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
    float res = timePickerColumnLayoutAlgorithm.ReCalcItemHeightScale(userSetHeight, isDividerSpacing);
    EXPECT_EQ(res, expectValue);

    /**
     * @tc.cases: case2. isDividerSpacing is true, and dividerSpacing_ is zero.
     */
    pickerTheme->dividerSpacing_ = Dimension(0.0, DimensionUnit::PX);
    pickerTheme->gradientHeight_ = Dimension(10.0, DimensionUnit::PX);

    isDividerSpacing = true;
    res = timePickerColumnLayoutAlgorithm.ReCalcItemHeightScale(userSetHeight, isDividerSpacing);
    EXPECT_EQ(res, expectValue);
}

/**
 * @tc.name: BeforeCreateLayoutWrapper001
 * @tc.desc: Test BeforeCreateLayoutWrapper when layoutPolicy is WRAP_CONTENT.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerColumnLayoutAlgorithmTest, BeforeCreateLayoutWrapper001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create TimePicker.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModel::GetInstance()->CreateTimePicker(theme);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::TIME_PICKER_ETS_TAG);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();

    auto pickerPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(pickerPattern, nullptr);
    pickerPattern->OnModifyDone();
    auto layoutAlgorithm = pickerPattern->CreateLayoutAlgorithm();

    /**
     * @tc.steps: step2. Set a specified size for the TimePicker.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));

    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
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
     * @tc.expected: The width and height of the TimePicker will be set to 0.
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
HWTEST_F(TimePickerColumnLayoutAlgorithmTest, BeforeCreateLayoutWrapper002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create TimePicker.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModel::GetInstance()->CreateTimePicker(theme);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::TIME_PICKER_ETS_TAG);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();

    auto pickerPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(pickerPattern, nullptr);
    pickerPattern->OnModifyDone();
    auto layoutAlgorithm = pickerPattern->CreateLayoutAlgorithm();

    /**
     * @tc.steps: step2. Set a specified size for the TimePicker.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));

    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
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
     * @tc.expected: The width and height of the TimePicker will be set to 0.
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
HWTEST_F(TimePickerColumnLayoutAlgorithmTest, BeforeCreateLayoutWrapper003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create TimePicker.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModel::GetInstance()->CreateTimePicker(theme);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::TIME_PICKER_ETS_TAG);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();

    auto pickerPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(pickerPattern, nullptr);
    pickerPattern->OnModifyDone();
    auto layoutAlgorithm = pickerPattern->CreateLayoutAlgorithm();

    /**
     * @tc.steps: step2. Set a specified size for the TimePicker.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));

    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
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
     * @tc.expected: The width and height of the TimePicker will not be changed.
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
HWTEST_F(TimePickerColumnLayoutAlgorithmTest, BeforeCreateLayoutWrapper004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create TimePicker.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModel::GetInstance()->CreateTimePicker(theme);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::TIME_PICKER_ETS_TAG);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();

    auto pickerPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(pickerPattern, nullptr);
    pickerPattern->OnModifyDone();
    auto layoutAlgorithm = pickerPattern->CreateLayoutAlgorithm();

    /**
     * @tc.steps: step2. Set a specified size for the TimePicker.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));

    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
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
     * @tc.expected: The width and height of the TimePicker will not be changed.
     */
    pickerPattern->BeforeCreateLayoutWrapper();
    EXPECT_TRUE(layoutProperty->calcLayoutConstraint_->selfIdealSize.has_value());
    EXPECT_EQ(layoutProperty->calcLayoutConstraint_->selfIdealSize->Width().value(), CalcLength(USER_IDEAL_SIZE_400));
    EXPECT_EQ(layoutProperty->calcLayoutConstraint_->selfIdealSize->Height().value(), CalcLength(USER_IDEAL_SIZE_400));
}

} // namespace OHOS::Ace::NG
