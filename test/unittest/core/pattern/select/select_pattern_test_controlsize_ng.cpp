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

#include <cstdint>
#include <iostream>
#include <optional>
#include <string>

#include "gtest/gtest.h"

#define protected public
#define private public
#include "test/mock/core/common/mock_container.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/common/ace_application_info.h"
#include "core/components/common/layout/constants.h"
#include "core/components/select/select_theme.h"
#include "core/components/text/text_theme.h"
#include "core/components/text_field/textfield_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/flex/flex_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_paint_property.h"
#include "core/components_ng/pattern/menu/menu_layout_property.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_layout_property.h"
#include "core/components_ng/pattern/select/select_model_ng.h"
#include "core/components_ng/pattern/select/select_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "base/geometry/dimension.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace::NG {
namespace {
const std::string SELECT_TEXT = "select";
const std::string OPTION_TEXT = "aaa";
const std::string OPTION_TEXT_2 = "BBB";
const std::string OPTION_TEXT_3 = "CCC";
const std::string INTERNAL_SOURCE = "$r('app.media.icon')";
const std::string FILE_SOURCE = "/common/icon.png";
const std::string DEFAULT_STR("2.0");
const std::string TEXT_VALUE = "test";
const CalcLength MARGIN_LENGTH = CalcLength("8vp");
const CalcSize TEXT_IDEAL_SIZE = CalcSize(CalcLength("50vp"), std::nullopt);
constexpr float FULL_SCREEN_WIDTH = 720.0f;
constexpr float FULL_SCREEN_HEIGHT = 1136.0f;
const SizeF FULL_SCREEN_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
const std::vector<std::string> FONT_FAMILY_VALUE = { "cursive" };
const Dimension FONT_SIZE_VALUE = Dimension(20.1, DimensionUnit::PX);
const Ace::FontStyle ITALIC_FONT_STYLE_VALUE = Ace::FontStyle::ITALIC;
const Ace::FontWeight FONT_WEIGHT_VALUE = Ace::FontWeight::W100;
const Color TEXT_COLOR_VALUE = Color::FromRGB(255, 100, 100);
const Color BG_COLOR_VALUE = Color::FromRGB(100, 255, 100);
const std::vector<SelectParam> CREATE_VALUE = { { OPTION_TEXT, FILE_SOURCE }, { OPTION_TEXT_2, INTERNAL_SOURCE },
    { OPTION_TEXT_3, INTERNAL_SOURCE } };
constexpr float TEST_SIZE_WIDTH = 10.0f;
constexpr float TEST_SIZE_HEIGHT = 10.0f;
const SizeF SELECT_TEXT_SIZE(TEST_SIZE_WIDTH, TEST_SIZE_HEIGHT);
} // namespace

struct TestProperty {
    std::optional<Dimension> FontSize = std::nullopt;
    std::optional<Ace::FontStyle> FontStyle = std::nullopt;
    std::optional<FontWeight> FontWeight = std::nullopt;
    std::optional<std::vector<std::string>> FontFamily = std::nullopt;
    std::optional<Color> FontColor = std::nullopt;
};

class SelectPatternTestControlSizeNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
    RefPtr<FrameNode> frameNode_;
    RefPtr<SelectPattern> selectPattern_;

protected:
    static RefPtr<FrameNode> CreateSelect(const std::vector<SelectParam>& value, const TestProperty& test);
};

void SelectPatternTestControlSizeNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
}

void SelectPatternTestControlSizeNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void SelectPatternTestControlSizeNg::SetUp()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    MockContainer::SetUp();
}

void SelectPatternTestControlSizeNg::TearDown()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

RefPtr<FrameNode> SelectPatternTestControlSizeNg::CreateSelect(const std::vector<SelectParam>& value,
    const TestProperty& test)
{
    SelectModelNG selectModelInstance;
    selectModelInstance.Create(value);
    if (test.FontSize.has_value()) {
        selectModelInstance.SetFontSize(test.FontSize.value());
    }
    if (test.FontColor.has_value()) {
        selectModelInstance.SetFontColor(test.FontColor.value());
    }
    if (test.FontStyle.has_value()) {
        selectModelInstance.SetItalicFontStyle(test.FontStyle.value());
    }
    if (test.FontWeight.has_value()) {
        selectModelInstance.SetFontWeight(test.FontWeight.value());
    }
    if (test.FontFamily.has_value()) {
        selectModelInstance.SetFontFamily(test.FontFamily.value());
    }

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    return AceType::DynamicCast<FrameNode>(element);
}

/**
 * @tc.name: SetControlSizeTest001
 * @tc.desc: Test SelectPattern ControlSize.
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestControlSizeNg, SetControlSize001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model, select frame node and select pattern.
     * @tc.expected: Objects are created successfully.
     */
    TestProperty testProperty;
    testProperty.FontSize = std::make_optional(FONT_SIZE_VALUE);
    testProperty.FontStyle = std::make_optional(ITALIC_FONT_STYLE_VALUE);
    testProperty.FontWeight = std::make_optional(FONT_WEIGHT_VALUE);
    testProperty.FontColor = std::make_optional(TEXT_COLOR_VALUE);
    testProperty.FontFamily = std::make_optional(FONT_FAMILY_VALUE);
    auto frameNode = CreateSelect(CREATE_VALUE, testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SelectPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Get ControlSize, compare the default value with the ControlSize::NORMAL.
     * @tc.expected: SelectPattern's default ControlSize and ControlSize::NORMAL are equal.
     */
    EXPECT_EQ(pattern->GetControlSize(), ControlSize::NORMAL);
}

/**
 * @tc.name: SetControlSize002
 * @tc.desc: Test SelectPattern SetControlSize
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestControlSizeNg, SetControlSize002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model, select frame node and select pattern.
     * @tc.expected: Objects are created successfully.
     */
    TestProperty testProperty;
    testProperty.FontSize = std::make_optional(FONT_SIZE_VALUE);
    testProperty.FontStyle = std::make_optional(ITALIC_FONT_STYLE_VALUE);
    testProperty.FontWeight = std::make_optional(FONT_WEIGHT_VALUE);
    testProperty.FontColor = std::make_optional(TEXT_COLOR_VALUE);
    testProperty.FontFamily = std::make_optional(FONT_FAMILY_VALUE);
    auto frameNode = CreateSelect(CREATE_VALUE, testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SelectPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Get ControlSize, compare the set value with the ControlSize.
     * @tc.expected: SelectPattern's ControlSize and the set value are equal. Restore the default value.
     */
    auto backupControlSize = pattern->GetControlSize();
    auto settingControlSize = ControlSize::SMALL;
    pattern->SetControlSize(settingControlSize);
    EXPECT_EQ(pattern->GetControlSize(), ControlSize::NORMAL);
    pattern->SetControlSize(backupControlSize);
    EXPECT_EQ(pattern->GetControlSize(), backupControlSize);
}

/**
 * @tc.name: SetControlSize003
 * @tc.desc: Test SelectPattern SetControlSize
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestControlSizeNg, SetControlSize003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model, select frame node and select pattern.
     * @tc.expected: Objects are created successfully.
     */
    TestProperty testProperty;
    testProperty.FontSize = std::make_optional(FONT_SIZE_VALUE);
    testProperty.FontStyle = std::make_optional(ITALIC_FONT_STYLE_VALUE);
    testProperty.FontWeight = std::make_optional(FONT_WEIGHT_VALUE);
    testProperty.FontColor = std::make_optional(TEXT_COLOR_VALUE);
    testProperty.FontFamily = std::make_optional(FONT_FAMILY_VALUE);
    auto frameNode = CreateSelect(CREATE_VALUE, testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SelectPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Get ControlSize, compare the set value with the ControlSize.
     * @tc.expected: SelectPattern's ControlSize and the set value are equal. Restore the default value.
     */
    auto backupControlSize = pattern->GetControlSize();
    auto settingControlSize = ControlSize::NORMAL;
    pattern->SetControlSize(settingControlSize);
    EXPECT_EQ(pattern->GetControlSize(), settingControlSize);
    pattern->SetControlSize(backupControlSize);
    EXPECT_EQ(pattern->GetControlSize(), backupControlSize);
}

/**
 * @tc.name: SetControlSize004
 * @tc.desc: Test SelectPattern SetControlSize
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestControlSizeNg, SetControlSize004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model, select frame node and select pattern.
     * @tc.expected: Objects are created successfully.
     */
    TestProperty testProperty;
    testProperty.FontSize = std::make_optional(FONT_SIZE_VALUE);
    testProperty.FontStyle = std::make_optional(ITALIC_FONT_STYLE_VALUE);
    testProperty.FontWeight = std::make_optional(FONT_WEIGHT_VALUE);
    testProperty.FontColor = std::make_optional(TEXT_COLOR_VALUE);
    testProperty.FontFamily = std::make_optional(FONT_FAMILY_VALUE);
    auto frameNode = CreateSelect(CREATE_VALUE, testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SelectPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Get ControlSize, compare the set value with the ControlSize.
     * @tc.expected: SelectPattern's ControlSize and the set value are equal. Restore the default value.
     */
    auto backupControlSize = pattern->GetControlSize();
    auto settingControlSize = (OHOS::Ace::ControlSize)2; // invalid value
    pattern->SetControlSize(settingControlSize);
    EXPECT_EQ(pattern->GetControlSize(), ControlSize::NORMAL);
    pattern->SetControlSize(backupControlSize);
    EXPECT_EQ(pattern->GetControlSize(), backupControlSize);
}

/**
 * @tc.name: SetControlSize005
 * @tc.desc: Test SelectPattern SetControlSize
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestControlSizeNg, SetControlSize005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model, select frame node and select pattern.
     * @tc.expected: Objects are created successfully.
     */
    TestProperty testProperty;
    testProperty.FontSize = std::make_optional(FONT_SIZE_VALUE);
    testProperty.FontStyle = std::make_optional(ITALIC_FONT_STYLE_VALUE);
    testProperty.FontWeight = std::make_optional(FONT_WEIGHT_VALUE);
    testProperty.FontColor = std::make_optional(TEXT_COLOR_VALUE);
    testProperty.FontFamily = std::make_optional(FONT_FAMILY_VALUE);
    auto frameNode = CreateSelect(CREATE_VALUE, testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SelectPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Get ControlSize, compare the set value with the ControlSize.
     * @tc.expected: SelectPattern's ControlSize and the set value are equal. Restore the default value.
     */
    auto backupControlSize = pattern->GetControlSize();
    auto settingControlSize = (OHOS::Ace::ControlSize)-1; // invalid value
    pattern->SetControlSize(settingControlSize);
    EXPECT_EQ(pattern->GetControlSize(), ControlSize::NORMAL);
    pattern->SetControlSize(backupControlSize);
    EXPECT_EQ(pattern->GetControlSize(), backupControlSize);
}

/**
 * @tc.name: SetControlSize006
 * @tc.desc: Test SelectPattern SetControlSize
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestControlSizeNg, SetControlSize006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model, select frame node and select pattern.
     * @tc.expected: Objects are created successfully.
     */
    TestProperty testProperty;
    testProperty.FontSize = std::make_optional(FONT_SIZE_VALUE);
    testProperty.FontStyle = std::make_optional(ITALIC_FONT_STYLE_VALUE);
    testProperty.FontWeight = std::make_optional(FONT_WEIGHT_VALUE);
    testProperty.FontColor = std::make_optional(TEXT_COLOR_VALUE);
    testProperty.FontFamily = std::make_optional(FONT_FAMILY_VALUE);
    auto frameNode = CreateSelect(CREATE_VALUE, testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SelectPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Get ControlSize, compare the set value with the ControlSize.
     * @tc.expected: SelectPattern's ControlSize and the set value are equal. Restore the default value.
     */
    pattern->SetControlSize({});
    EXPECT_NE(pattern->GetControlSize(), ControlSize::SMALL);
}

/**
 * @tc.name: SelectLayoutAlgorithmTest001
 * @tc.desc: Test SelectLayoutAlgorithm::Measure.
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestControlSizeNg, SelectLayoutAlgorithmTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get frameNode and geometryNode.
     */
    TestProperty testProperty;
    testProperty.FontSize = std::make_optional(FONT_SIZE_VALUE);
    auto frameNode = CreateSelect(CREATE_VALUE, testProperty);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    /**
     * @tc.steps: step2. Get layoutWrapper and Call Measure when has no layoutConstraint.
     * @tc.expected: the function exits normally
     */
    auto layoutProperty = frameNode->GetLayoutProperty();
    LayoutWrapperNode* layoutWrapper = new LayoutWrapperNode(frameNode, geometryNode, layoutProperty);
    auto childlayoutWrapper = layoutWrapper->GetOrCreateChildByIndex(0, false);
    auto layoutAlgorithm = AceType::MakeRefPtr<SelectLayoutAlgorithm>();
    layoutAlgorithm->Measure(layoutWrapper);
    auto rowWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    EXPECT_EQ(rowWrapper, nullptr);
}
/**
 * @tc.name: SelectLayoutAlgorithmTest002
 * @tc.desc: Test SelectLayoutAlgorithm::MeasureAndGetTextSize.
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestControlSizeNg, SelectLayoutAlgorithmTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get frameNode and geometryNode.
     */
    TestProperty testProperty;
    testProperty.FontSize = std::make_optional(FONT_SIZE_VALUE);
    auto frameNode = CreateSelect(CREATE_VALUE, testProperty);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    /**
     * @tc.steps: step2. Get layoutWrapper and Call MeasureAndGetTextSize.
     * @tc.expected: the function exits normally
     */
    auto layoutProperty = frameNode->GetLayoutProperty();
    LayoutWrapperNode* layoutWrapper = new LayoutWrapperNode(frameNode, geometryNode, layoutProperty);
    auto layoutAlgorithm = AceType::MakeRefPtr<SelectLayoutAlgorithm>();
    bool testReult = false;
    SizeF fTextSize(TEST_SIZE_WIDTH, TEST_SIZE_HEIGHT);
    layoutAlgorithm->MeasureAndGetTextSize(20, fTextSize, testReult);
    EXPECT_TRUE(testReult);
    auto rowWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    /**
     * @tc.steps: step2+. Get layoutWrapper and Call MeasureAndGetTextSize.
     * @tc.expected: the function exits normally
     */
    EXPECT_EQ(rowWrapper, nullptr);
    layoutAlgorithm->MeasureAndGetTextSize(5, fTextSize, testReult);
    EXPECT_TRUE(testReult);
}
/**
 * @tc.name: SelectLayoutAlgorithmTest003
 * @tc.desc: Test SelectLayoutAlgorithm::MeasureAndGetDefaultHeight.
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestControlSizeNg, SelectLayoutAlgorithmTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get frameNode and geometryNode.
     */
    TestProperty testProperty;
    testProperty.FontSize = std::make_optional(FONT_SIZE_VALUE);
    auto frameNode = CreateSelect(CREATE_VALUE, testProperty);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    /**
     * @tc.steps: step2. Get layoutWrapper and Call MeasureAndGetDefaultHeight.
     * @tc.expected: the function exits normally
     */
    auto layoutProperty = frameNode->GetLayoutProperty();
    LayoutWrapperNode* layoutWrapper = new LayoutWrapperNode(frameNode, geometryNode, layoutProperty);
    auto layoutAlgorithm = AceType::MakeRefPtr<SelectLayoutAlgorithm>();
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto selectTheme = pipeline->GetTheme<SelectTheme>();
    ASSERT_NE(selectTheme, nullptr);
    layoutAlgorithm->MeasureAndGetDefaultHeight(layoutProperty, selectTheme);
    /**
     * @tc.steps: step2+. set min api is 12.
     * @tc.expected: the function exits normally
     */
    int32_t setApiVersion = 12;
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    layoutAlgorithm->MeasureAndGetDefaultHeight(layoutProperty, selectTheme);
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
    auto rowWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    EXPECT_EQ(rowWrapper, nullptr);
}
/**
 * @tc.name: SelectModelngTest001
 * @tc.desc: Test SelectModelNG::GetControlSize
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestControlSizeNg, SelectModelngTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model and select event.
     * @tc.expected: Objects are created successfully.
     */
    SelectModelNG selectModelInstance;
    SelectEvent eventOnSelect = [](int32_t intValue, const std::string& isSelect) {};
    /**
     * @tc.steps: step2. Initialize the value of paddings and parameters of select.
     * @tc.expected: Objects are initialized successfully.
     */
    CalcDimension width = -20.0_vp;
    CalcDimension height = -20.0_vp;
    CalcDimension top = -20.0_vp;
    CalcDimension bottom = -20.0_vp;
    CalcDimension left = -20.0_vp;
    CalcDimension right = -20.0_vp;

    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(100);
    /**
     * @tc.steps: step3. Call the member methods of select model to set the geometry properties of select.
     * @tc.expected: Settings are successful..
     */
    selectModelInstance.SetWidth(width);
    selectModelInstance.SetHeight(height);
    selectModelInstance.SetSize(width, height);
    selectModelInstance.SetPaddings(top, bottom, left, right);
    selectModelInstance.SetPadding(CalcDimension(20.00, DimensionUnit::VP));
    selectModelInstance.SetPaddingLeft(CalcDimension(20.00, DimensionUnit::VP));
    selectModelInstance.SetPaddingTop(CalcDimension(20.00, DimensionUnit::VP));
    selectModelInstance.SetPaddingRight(CalcDimension(20.00, DimensionUnit::VP));
    selectModelInstance.SetPaddingBottom(CalcDimension(20.00, DimensionUnit::VP));
    /**
     * @tc.steps: step4. Get the select frame node, select pattern and menu frame node.
     * @tc.expected: Objects are gotten successfully and should not be null.
     */
    int32_t setApiVersion = 11;
    int32_t setApiVersionMax = 13;
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    auto testResult = selectModelInstance.GetControlSize();
    MockContainer::Current()->SetApiTargetVersion(setApiVersionMax);
    testResult = selectModelInstance.GetControlSize();
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
    EXPECT_EQ(testResult, ControlSize::NORMAL);
}
/**
 * @tc.name: SelectPatternExTest001
 * @tc.desc: Test SelectPattern::RegisterOnHover
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestControlSizeNg, SelectPatternExTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model and select event.
     * @tc.expected: Objects are created successfully.
     */
    TestProperty testProperty;
    testProperty.FontSize = std::make_optional(FONT_SIZE_VALUE);
    auto selectNode = CreateSelect(CREATE_VALUE, testProperty);
    ASSERT_NE(selectNode, nullptr);
    auto selectPattern = selectNode->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    bool bIsHover = false;
    selectPattern->SetIsHover(bIsHover);
    selectPattern->RegisterOnHover();
    auto inputHub = selectNode->GetOrCreateInputEventHub();
    ASSERT_NE(inputHub->hoverEventActuator_, nullptr);
}
/**
 * @tc.name: SelectPatternExTest002
 * @tc.desc: Test SelectPattern::OnLanguageConfigurationUpdate
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestControlSizeNg, SelectPatternExTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model and select event.
     * @tc.expected: Objects are created successfully.
     */
    TestProperty testProperty;
    testProperty.FontSize = std::make_optional(FONT_SIZE_VALUE);
    auto selectNode = CreateSelect(CREATE_VALUE, testProperty);
    ASSERT_NE(selectNode, nullptr);
    auto selectPattern = selectNode->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    selectPattern->OnLanguageConfigurationUpdate();
    auto inputHub = selectNode->GetOrCreateInputEventHub();
    ASSERT_NE(inputHub->hoverEventActuator_, nullptr);
}
/**
 * @tc.name: SelectPatternExTest003
 * @tc.desc: Test SelectPattern::ToJsonDivider
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestControlSizeNg, SelectPatternExTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model and select event.
     * @tc.expected: Objects are created successfully.
     */
    InspectorFilter filter;
    TestProperty testProperty;
    testProperty.FontSize = std::make_optional(FONT_SIZE_VALUE);
    auto selectNode = CreateSelect(CREATE_VALUE, testProperty);
    ASSERT_NE(selectNode, nullptr);
    auto selectPattern = selectNode->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);

    auto json = JsonUtil::Create(true);
    selectPattern->ToJsonDivider(json, filter);
    EXPECT_EQ(json->GetString("divider"), "");
    /**
     * @tc.steps: step1+. Create vector options_[0] props HasDivider.
     * @tc.expected: Objects are created successfully.
     */
    auto props = selectPattern->options_[0]->GetPaintProperty<MenuItemPaintProperty>();
    NG::SelectDivider divider;
    divider.color = Color(1);
    props->UpdateDivider(divider);
    selectPattern->ToJsonDivider(json, filter);
    /**
     * @tc.steps: step2. set vector options_ is empty.
     * @tc.expected: Objects are created successfully.
     */
    selectPattern->options_.clear();
    selectPattern->ToJsonDivider(json, filter);
    EXPECT_EQ(json->GetString("divider"), "");

    /**
     * @tc.steps: step3. set filter is FastFilter.
     * @tc.expected: Objects are created successfully.
     */
    filter.filterExt.clear();
    filter.filterFixed = 1;
    selectPattern->ToJsonDivider(json, filter);
    EXPECT_TRUE(filter.IsFastFilter());
}
/**
 * @tc.name: SelectPatternExTest004
 * @tc.desc: Test SelectPattern::ToJsonMenuBackgroundStyle
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestControlSizeNg, SelectPatternExTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model and select event.
     * @tc.expected: Objects are created successfully.
     */
    InspectorFilter filter;
    TestProperty testProperty;
    testProperty.FontSize = std::make_optional(FONT_SIZE_VALUE);
    auto selectNode = CreateSelect(CREATE_VALUE, testProperty);
    ASSERT_NE(selectNode, nullptr);
    auto selectPattern = selectNode->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);

    auto json = JsonUtil::Create(true);
    selectPattern->ToJsonMenuBackgroundStyle(json, filter);
    /**
     * @tc.steps: step1+. Create select model and select event.
     * @tc.expected: Objects are created successfully.
     */
    auto menu = selectPattern->GetMenuNode();
    CHECK_NULL_VOID(menu);
    auto menuRenderContext = menu->GetRenderContext();
    CHECK_NULL_VOID(menuRenderContext);
    BlurStyleOption styleOption;
    styleOption.blurStyle = BlurStyle::COMPONENT_THICK;
    menuRenderContext->UpdateBackBlurStyle(styleOption);
    selectPattern->ToJsonMenuBackgroundStyle(json, filter);
    selectPattern->ToJsonArrowAndText(json, filter);
    /**
     * @tc.steps: step2. set filter is FastFilter.
     * @tc.expected: filter is seted successfully.
     */
    filter.filterExt.clear();
    filter.filterFixed = 1;
    selectPattern->ToJsonMenuBackgroundStyle(json, filter);
    EXPECT_TRUE(filter.IsFastFilter());
}
/**
 * @tc.name: SelectPatternExTest005
 * @tc.desc: Test SelectPattern::ToJsonArrowAndText
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestControlSizeNg, SelectPatternExTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model and select event.
     * @tc.expected: Objects are created successfully.
     */
    InspectorFilter filter;
    TestProperty testProperty;
    testProperty.FontSize = std::make_optional(FONT_SIZE_VALUE);
    auto selectNode = CreateSelect(CREATE_VALUE, testProperty);
    ASSERT_NE(selectNode, nullptr);
    auto childNode = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    childNode->MountToParent(selectNode);
    auto selectPattern = selectNode->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);

    auto json = JsonUtil::Create(true);
    selectPattern->ToJsonArrowAndText(json, filter);
    /**
     * @tc.steps: step2. set filter is FastFilter.
     * @tc.expected: filter is seted successfully.
     */
    filter.filterExt.clear();
    filter.filterFixed = 1;
    selectPattern->ToJsonArrowAndText(json, filter);
    EXPECT_TRUE(filter.IsFastFilter());
}
/**
 * @tc.name: SelectPatternExTest006
 * @tc.desc: Test SelectPattern::ToJsonArrowAndText
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestControlSizeNg, SelectPatternExTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model and select event.
     * @tc.expected: Objects are created successfully.
     */
    InspectorFilter filter;
    TestProperty testProperty;
    testProperty.FontSize = std::make_optional(FONT_SIZE_VALUE);
    auto selectNode = CreateSelect(CREATE_VALUE, testProperty);
    ASSERT_NE(selectNode, nullptr);
    auto childNode = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    childNode->MountToParent(selectNode);
    auto selectPattern = selectNode->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);

    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    selectPattern->BuildChild();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    auto renderContext = selectNode->GetRenderContext();
    EXPECT_EQ(selectNode->GetFirstChild()->GetTag(), V2::ROW_ETS_TAG);
}
/**
 * @tc.name: SelectPatternExTest007
 * @tc.desc: Test SelectPattern::ToJsonArrowAndText
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestControlSizeNg, SelectPatternExTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model and select event.
     * @tc.expected: Objects are created successfully.
     */
    InspectorFilter filter;
    TestProperty testProperty;
    testProperty.FontSize = std::make_optional(FONT_SIZE_VALUE);
    auto selectNode = CreateSelect(CREATE_VALUE, testProperty);
    ASSERT_NE(selectNode, nullptr);
    auto selectPattern = selectNode->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);

    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    /**
     * @tc.steps: step1+. set id hav value and call BuildChild.
     * @tc.expected: Objects are created successfully.
     */
    selectPattern->rowId_ = std::nullopt;
    selectPattern->spinnerId_ = std::nullopt;
    selectPattern->textId_ = std::nullopt;
    selectPattern->BuildChild();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    auto childnode = selectNode->GetFirstChild();
    EXPECT_EQ(selectNode->GetFirstChild()->GetTag(), V2::ROW_ETS_TAG);
    EXPECT_EQ(childnode->GetFirstChild()->GetTag(), V2::TEXT_ETS_TAG);
}
} // namespace OHOS::Ace::NG
