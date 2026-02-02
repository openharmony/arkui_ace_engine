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
#include "core/components_ng/pattern/picker/picker_theme.h"
#include "core/components/button/button_theme.h"
#include "core/components/dialog/dialog_theme.h"
#include "core/components_ng/pattern/picker/datepicker_model_ng.h"
#include "core/components_ng/pattern/picker/datepicker_pattern.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr double TEST_FONT_SIZE = 10.0;
const Dimension FONT_SIZE_VALUE_DIMENSION = Dimension(20.1, DimensionUnit::PX);
const std::vector<std::string> FONT_FAMILY_CURSIVE = { "cursive" };
const std::vector<std::string> FONT_FAMILY_ARIAL = { "arial" };
}

class DatePickerResourceTest : public testing::Test {
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

void DatePickerResourceTest::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void DatePickerResourceTest::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void DatePickerResourceTest::SetUp()
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

void DatePickerResourceTest::TearDown()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    ViewStackProcessor::GetInstance()->ClearStack();
}

RefPtr<Theme> DatePickerResourceTest::GetThemeByType(ThemeType type)
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
 * @tc.name: UpdateDisappearTextStyle001
 * @tc.desc: Test DatePickerPattern UpdateDisappearTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerResourceTest, UpdateDisappearTextStyle001, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->SetIsSystemColorChange(true);

    PickerTextStyle textStyle;
    textStyle.textColor = Color::RED;
    textStyle.fontSize = Dimension(TEST_FONT_SIZE);
    DatePickerModel::GetInstance()->SetDisappearTextStyle(theme, textStyle);

    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(pickerProperty->GetDisappearColor().value(), Color::RED);
    EXPECT_EQ(pickerProperty->GetDisappearFontSize().value(), Dimension(TEST_FONT_SIZE));

    textStyle.textColor = Color::GREEN;
    textStyle.fontSize = Dimension(TEST_FONT_SIZE + 1);
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    datePickerPattern->UpdateDisappearTextStyle(textStyle);

    EXPECT_EQ(pickerProperty->GetDisappearColor().value(), Color::GREEN);
    EXPECT_EQ(pickerProperty->GetDisappearFontSize().value(), Dimension(TEST_FONT_SIZE + 1));
}

/**
 * @tc.name: UpdateDisappearTextStyle002
 * @tc.desc: Test DatePickerPattern UpdateDisappearTextStyle, when the input parameter is invalid
 *           and the LayoutProperty has no value, the theme value will be used for setting.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerResourceTest, UpdateDisappearTextStyle002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create DatePicker.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->SetIsSystemColorChange(true);

    /**
     * @tc.steps: step2. Set the default value for the PickerTheme.
     */
    theme->disappearOptionStyle_.SetTextColor(Color::GREEN);
    theme->disappearOptionStyle_.SetFontSize(FONT_SIZE_VALUE_DIMENSION);
    theme->disappearOptionStyle_.SetFontFamilies(FONT_FAMILY_CURSIVE);

    /**
     * @tc.steps: step3. Call UpdateDisappearTextStyle with the parameter textStyle having no valid value.
     * @tc.expected: The value of PickerTheme will be used for setting.
     */
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    PickerTextStyle textStyle;
    datePickerPattern->UpdateDisappearTextStyle(textStyle);

    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(pickerProperty->GetDisappearColor().value(), Color::GREEN);
    EXPECT_EQ(pickerProperty->GetDisappearFontSize().value(), FONT_SIZE_VALUE_DIMENSION);
    EXPECT_EQ(pickerProperty->GetDisappearFontFamily().value(), FONT_FAMILY_CURSIVE);  
}

/**
 * @tc.name: UpdateDisappearTextStyle003
 * @tc.desc: Test DatePickerPattern UpdateDisappearTextStyle, when the input parameter is invalid
 *           and the LayoutProperty has value, the LayoutProperty value will be used for setting.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerResourceTest, UpdateDisappearTextStyle003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create DatePicker.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->SetIsSystemColorChange(true);

    /**
     * @tc.steps: step2. Set the default value for the PickerTheme.
     */
    theme->disappearOptionStyle_.SetTextColor(Color::GREEN);
    theme->disappearOptionStyle_.SetFontSize(FONT_SIZE_VALUE_DIMENSION);
    theme->disappearOptionStyle_.SetFontFamilies(FONT_FAMILY_CURSIVE);

    /**
     * @tc.steps: step3. SetDisappearTextStyle to ensure the LayoutProperty has value.
     */
    PickerTextStyle textStyle;
    textStyle.textColor = Color::RED;
    textStyle.fontSize = Dimension(TEST_FONT_SIZE, DimensionUnit::VP);
    textStyle.fontFamily = FONT_FAMILY_ARIAL;
    DatePickerModel::GetInstance()->SetDisappearTextStyle(theme, textStyle);

    /**
     * @tc.steps: step4. Call UpdateDisappearTextStyle with the parameter textStyle having no valid value.
     * @tc.expected: The value of LayoutProperty will be used for setting.
     */
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    PickerTextStyle newTextStyle;
    datePickerPattern->UpdateDisappearTextStyle(newTextStyle);

    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(pickerProperty->GetDisappearColor().value(), Color::RED);
    EXPECT_EQ(pickerProperty->GetDisappearFontSize().value(), Dimension(TEST_FONT_SIZE, DimensionUnit::VP));
    EXPECT_EQ(pickerProperty->GetDisappearFontFamily().value(), FONT_FAMILY_ARIAL);  
}

/**
 * @tc.name: UpdateNormalTextStyle001
 * @tc.desc: Test DatePickerPattern UpdateNormalTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerResourceTest, UpdateNormalTextStyle001, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->SetIsSystemColorChange(true);

    PickerTextStyle textStyle;
    textStyle.textColor = Color::RED;
    textStyle.fontSize = Dimension(TEST_FONT_SIZE);
    DatePickerModel::GetInstance()->SetNormalTextStyle(theme, textStyle);

    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(pickerProperty->GetColor().value(), Color::RED);
    EXPECT_EQ(pickerProperty->GetFontSize().value(), Dimension(TEST_FONT_SIZE));

    textStyle.textColor = Color::GREEN;
    textStyle.fontSize = Dimension(TEST_FONT_SIZE + 1);
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    datePickerPattern->UpdateNormalTextStyle(textStyle);

    EXPECT_EQ(pickerProperty->GetColor().value(), Color::GREEN);
    EXPECT_EQ(pickerProperty->GetFontSize().value(), Dimension(TEST_FONT_SIZE + 1));
}

/**
 * @tc.name: UpdateNormalTextStyle002
 * @tc.desc: Test DatePickerPattern UpdateNormalTextStyle, when the input parameter is invalid
 *           and the LayoutProperty has no value, the theme value will be used for setting.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerResourceTest, UpdateNormalTextStyle002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create DatePicker.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->SetIsSystemColorChange(true);

    /**
     * @tc.steps: step2. Set the default value for the PickerTheme.
     */
    theme->normalOptionStyle_.SetTextColor(Color::GREEN);
    theme->normalOptionStyle_.SetFontSize(FONT_SIZE_VALUE_DIMENSION);
    theme->normalOptionStyle_.SetFontFamilies(FONT_FAMILY_CURSIVE);

    /**
     * @tc.steps: step3. Call UpdateNormalTextStyle with the parameter textStyle having no valid value.
     * @tc.expected: The value of PickerTheme will be used for setting.
     */
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    PickerTextStyle textStyle;
    datePickerPattern->UpdateNormalTextStyle(textStyle);

    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(pickerProperty->GetColor().value(), Color::GREEN);
    EXPECT_EQ(pickerProperty->GetFontSize().value(), FONT_SIZE_VALUE_DIMENSION);
    EXPECT_EQ(pickerProperty->GetFontFamily().value(), FONT_FAMILY_CURSIVE);  
}

/**
 * @tc.name: UpdateNormalTextStyle003
 * @tc.desc: Test DatePickerPattern UpdateNormalTextStyle, when the input parameter is invalid
 *           and the LayoutProperty has value, the LayoutProperty value will be used for setting.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerResourceTest, UpdateNormalTextStyle003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create DatePicker.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->SetIsSystemColorChange(true);

    /**
     * @tc.steps: step2. Set the default value for the PickerTheme.
     */
    theme->normalOptionStyle_.SetTextColor(Color::GREEN);
    theme->normalOptionStyle_.SetFontSize(FONT_SIZE_VALUE_DIMENSION);
    theme->normalOptionStyle_.SetFontFamilies(FONT_FAMILY_CURSIVE);

    /**
     * @tc.steps: step3. SetNormalTextStyle to ensure the LayoutProperty has value.
     */
    PickerTextStyle textStyle;
    textStyle.textColor = Color::RED;
    textStyle.fontSize = Dimension(TEST_FONT_SIZE, DimensionUnit::VP);
    textStyle.fontFamily = FONT_FAMILY_ARIAL;
    DatePickerModel::GetInstance()->SetNormalTextStyle(theme, textStyle);

    /**
     * @tc.steps: step4. Call UpdateNormalTextStyle with the parameter textStyle having no valid value.
     * @tc.expected: The value of LayoutProperty will be used for setting.
     */
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    PickerTextStyle newTextStyle;
    datePickerPattern->UpdateNormalTextStyle(newTextStyle);

    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(pickerProperty->GetColor().value(), Color::RED);
    EXPECT_EQ(pickerProperty->GetFontSize().value(), Dimension(TEST_FONT_SIZE, DimensionUnit::VP));
    EXPECT_EQ(pickerProperty->GetFontFamily().value(), FONT_FAMILY_ARIAL);  
}

/**
 * @tc.name: UpdateSelectedTextStyle001
 * @tc.desc: Test DatePickerPattern UpdateSelectedTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerResourceTest, UpdateSelectedTextStyle001, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->SetIsSystemColorChange(true);

    PickerTextStyle textStyle;
    textStyle.textColor = Color::RED;
    textStyle.fontSize = Dimension(TEST_FONT_SIZE);
    DatePickerModel::GetInstance()->SetSelectedTextStyle(theme, textStyle);

    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(pickerProperty->GetSelectedColor().value(), Color::RED);
    EXPECT_EQ(pickerProperty->GetSelectedFontSize().value(), Dimension(TEST_FONT_SIZE));

    textStyle.textColor = Color::GREEN;
    textStyle.fontSize = Dimension(TEST_FONT_SIZE + 1);
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    datePickerPattern->UpdateSelectedTextStyle(textStyle);

    EXPECT_EQ(pickerProperty->GetSelectedColor().value(), Color::GREEN);
    EXPECT_EQ(pickerProperty->GetSelectedFontSize().value(), Dimension(TEST_FONT_SIZE + 1));
}

/**
 * @tc.name: UpdateSelectedTextStyle002
 * @tc.desc: Test DatePickerPattern UpdateSelectedTextStyle, when the input parameter is invalid
 *           and the LayoutProperty has no value, the theme value will be used for setting.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerResourceTest, UpdateSelectedTextStyle002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create DatePicker.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->SetIsSystemColorChange(true);

    /**
     * @tc.steps: step2. Set the default value for the PickerTheme.
     */
    theme->selectedOptionStyle_.SetTextColor(Color::GREEN);
    theme->selectedOptionStyle_.SetFontSize(FONT_SIZE_VALUE_DIMENSION);
    theme->selectedOptionStyle_.SetFontFamilies(FONT_FAMILY_CURSIVE);

    /**
     * @tc.steps: step3. Call UpdateSelectedTextStyle with the parameter textStyle having no valid value.
     * @tc.expected: The value of PickerTheme will be used for setting.
     */
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    PickerTextStyle textStyle;
    datePickerPattern->UpdateSelectedTextStyle(textStyle);

    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(pickerProperty->GetSelectedColor().value(), Color::GREEN);
    EXPECT_EQ(pickerProperty->GetSelectedFontSize().value(), FONT_SIZE_VALUE_DIMENSION);
    EXPECT_EQ(pickerProperty->GetSelectedFontFamily().value(), FONT_FAMILY_CURSIVE);  
}

/**
 * @tc.name: UpdateSelectedTextStyle003
 * @tc.desc: Test DatePickerPattern UpdateSelectedTextStyle, when the input parameter is invalid
 *           and the LayoutProperty has value, the LayoutProperty value will be used for setting.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerResourceTest, UpdateSelectedTextStyle003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create DatePicker.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->SetIsSystemColorChange(true);

    /**
     * @tc.steps: step2. Set the default value for the PickerTheme.
     */
    theme->selectedOptionStyle_.SetTextColor(Color::GREEN);
    theme->selectedOptionStyle_.SetFontSize(FONT_SIZE_VALUE_DIMENSION);
    theme->selectedOptionStyle_.SetFontFamilies(FONT_FAMILY_CURSIVE);

    /**
     * @tc.steps: step3. SetSelectedTextStyle to ensure the LayoutProperty has value.
     */
    PickerTextStyle textStyle;
    textStyle.textColor = Color::RED;
    textStyle.fontSize = Dimension(TEST_FONT_SIZE, DimensionUnit::VP);
    textStyle.fontFamily = FONT_FAMILY_ARIAL;
    DatePickerModel::GetInstance()->SetSelectedTextStyle(theme, textStyle);

    /**
     * @tc.steps: step4. Call UpdateSelectedTextStyle with the parameter textStyle having no valid value.
     * @tc.expected: The value of LayoutProperty will be used for setting.
     */
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    PickerTextStyle newTextStyle;
    datePickerPattern->UpdateSelectedTextStyle(newTextStyle);

    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(pickerProperty->GetSelectedColor().value(), Color::RED);
    EXPECT_EQ(pickerProperty->GetSelectedFontSize().value(), Dimension(TEST_FONT_SIZE, DimensionUnit::VP));
    EXPECT_EQ(pickerProperty->GetSelectedFontFamily().value(), FONT_FAMILY_ARIAL);  
}

} // namespace OHOS::Ace::NG
