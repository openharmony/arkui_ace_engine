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
#include "core/components_ng/pattern/menu/menu_layout_property.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/option/option_paint_property.h"
#include "core/components_ng/pattern/option/option_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_layout_property.h"
#include "core/components_ng/pattern/select/select_model_ng.h"
#include "core/components_ng/pattern/select/select_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"

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
}

void SelectPatternTestControlSizeNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

void SelectPatternTestControlSizeNg::SetUp() {}

void SelectPatternTestControlSizeNg::TearDown() {}

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
    EXPECT_EQ(pattern->GetControlSize(), settingControlSize);
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
    EXPECT_EQ(pattern->GetControlSize(), settingControlSize);
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
    EXPECT_EQ(pattern->GetControlSize(), settingControlSize);
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
    auto backupControlSize = pattern->GetControlSize();
    pattern->SetControlSize({});
    EXPECT_NE(pattern->GetControlSize(), backupControlSize);
}
} // namespace OHOS::Ace::NG
