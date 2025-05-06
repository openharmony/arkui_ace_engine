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
#include "core/components_ng/pattern/picker/datepicker_column_layout_algorithm.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class DatePickerColumnLayoutAlgorithmTest : public testing::Test {
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

void DatePickerColumnLayoutAlgorithmTest::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void DatePickerColumnLayoutAlgorithmTest::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void DatePickerColumnLayoutAlgorithmTest::SetUp()
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

void DatePickerColumnLayoutAlgorithmTest::TearDown()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    ViewStackProcessor::GetInstance()->ClearStack();
}

RefPtr<Theme> DatePickerColumnLayoutAlgorithmTest::GetThemeByType(ThemeType type)
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
HWTEST_F(DatePickerColumnLayoutAlgorithmTest, ReCalcItemHeightScale001, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create pipeline and pickerTheme.
    */
    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipeline, nullptr);

    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    EXPECT_NE(pickerTheme, nullptr);
    DatePickerColumnLayoutAlgorithm datePickerColumnLayoutAlgorithm;

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
    float res = datePickerColumnLayoutAlgorithm.ReCalcItemHeightScale(userSetHeight, isDividerSpacing);
    EXPECT_EQ(res, expectValue);

    /**
     * @tc.cases: case2. isDividerSpacing is false.
     */
    expectValue = pickerTheme->GetPickerDialogFontPadding().ConvertToPx() * 2 /
                  pickerTheme->GetGradientHeight().ConvertToPx();
    isDividerSpacing = false;
    res = datePickerColumnLayoutAlgorithm.ReCalcItemHeightScale(userSetHeight, isDividerSpacing);
    EXPECT_EQ(res, expectValue);
}

/**
 * @tc.name: ReCalcItemHeightScale002
 * @tc.desc: Test ReCalcItemHeightScale when fontScale,
 *           pickerDialogNormalFontScale_, pickerDialogMaxTwoFontScale_ are zero.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerColumnLayoutAlgorithmTest, ReCalcItemHeightScale002, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create pipeline and pickerTheme.
    */
    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipeline, nullptr);

    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    EXPECT_NE(pickerTheme, nullptr);
    DatePickerColumnLayoutAlgorithm datePickerColumnLayoutAlgorithm;

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
    float res = datePickerColumnLayoutAlgorithm.ReCalcItemHeightScale(userSetHeight, isDividerSpacing);
    EXPECT_EQ(res, 1.0f);

    /**
     * @tc.cases: case2. isDividerSpacing is false.
     */
    isDividerSpacing = false;
    res = datePickerColumnLayoutAlgorithm.ReCalcItemHeightScale(userSetHeight, isDividerSpacing);
    EXPECT_EQ(res, 1.0f);
}

/**
 * @tc.name: ReCalcItemHeightScale003
 * @tc.desc: Test ReCalcItemHeightScale when GreatOrEqualCustomPrecision() is false.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerColumnLayoutAlgorithmTest, ReCalcItemHeightScale003, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create pipeline and pickerTheme.
    */
    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipeline, nullptr);

    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    EXPECT_NE(pickerTheme, nullptr);
    DatePickerColumnLayoutAlgorithm datePickerColumnLayoutAlgorithm;
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
    float res = datePickerColumnLayoutAlgorithm.ReCalcItemHeightScale(userSetHeight, isDividerSpacing);
    EXPECT_EQ(res, expectValue);

    /**
     * @tc.cases: case2. isDividerSpacing is true, pickerDialogFontPadding < dividerSpacingHeightLimit_.
     */
    pickerTheme->pickerDialogFontPadding_ = 28.0_vp;
    pickerTheme->gradientHeightLimit_ = 28.0_vp;
    pickerTheme->dividerSpacingHeightLimit_ = 64.0_vp;
    pickerTheme->dividerSpacing_ = Dimension(8.0, DimensionUnit::PX);

    isDividerSpacing = true;
    res = datePickerColumnLayoutAlgorithm.ReCalcItemHeightScale(userSetHeight, isDividerSpacing);
    EXPECT_EQ(res, expectValue);
}

/**
 * @tc.name: ReCalcItemHeightScale004
 * @tc.desc: Test ReCalcItemHeightScale when GreatOrEqualCustomPrecision() is true.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerColumnLayoutAlgorithmTest, ReCalcItemHeightScale004, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create pipeline and pickerTheme.
    */
    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipeline, nullptr);

    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    EXPECT_NE(pickerTheme, nullptr);
    DatePickerColumnLayoutAlgorithm datePickerColumnLayoutAlgorithm;
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
    float res = datePickerColumnLayoutAlgorithm.ReCalcItemHeightScale(userSetHeight, isDividerSpacing);
    EXPECT_EQ(res, expectValue);

    /**
     * @tc.cases: case2. isDividerSpacing is true, pickerDialogFontPadding >= dividerSpacingHeightLimit_.
     */
    pickerTheme->pickerDialogFontPadding_ = 28.0_vp;
    pickerTheme->gradientHeightLimit_ = 48.0_vp;
    pickerTheme->dividerSpacingHeightLimit_ = 20.0_vp;
    pickerTheme->dividerSpacing_ = Dimension(8.0, DimensionUnit::PX);

    isDividerSpacing = true;
    res = datePickerColumnLayoutAlgorithm.ReCalcItemHeightScale(userSetHeight, isDividerSpacing);
    EXPECT_EQ(res, expectValue);
}

/**
 * @tc.name: ReCalcItemHeightScale005
 * @tc.desc: Test HandleMonthChange.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerColumnLayoutAlgorithmTest, ReCalcItemHeightScale005, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create pipeline and pickerTheme.
    */
    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipeline, nullptr);

    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    EXPECT_NE(pickerTheme, nullptr);
    DatePickerColumnLayoutAlgorithm datePickerColumnLayoutAlgorithm;
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
    float res = datePickerColumnLayoutAlgorithm.ReCalcItemHeightScale(userSetHeight, isDividerSpacing);
    EXPECT_EQ(res, expectValue);

    /**
     * @tc.cases: case2. isDividerSpacing is true, and dividerSpacing_ is zero.
     */
    pickerTheme->dividerSpacing_ = Dimension(0.0, DimensionUnit::PX);
    pickerTheme->gradientHeight_ = Dimension(10.0, DimensionUnit::PX);

    isDividerSpacing = true;
    res = datePickerColumnLayoutAlgorithm.ReCalcItemHeightScale(userSetHeight, isDividerSpacing);
    EXPECT_EQ(res, expectValue);
}
} // namespace OHOS::Ace::NG
