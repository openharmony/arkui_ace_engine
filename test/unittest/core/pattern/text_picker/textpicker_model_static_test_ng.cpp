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

#include <functional>
#include <optional>
#include <string>

#include "test/unittest/core/pattern/test_ng.h"

#define private public
#define protected public
#include "test/mock/core/common/mock_theme_default.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"

#include "core/components_ng/pattern/picker/picker_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/text_picker/textpicker_model_static.h"
#include "core/components_ng/pattern/text_picker/textpicker_pattern.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
    constexpr int32_t ONCHANGE_CALLBACK_INFO = 1;
    constexpr int32_t ONSCROLLSTOP_CALLBACK_INFO = 2;
    constexpr int32_t ONENTERSELECTEDAREA_CALLBACK_INFO = 3;
    constexpr int32_t ONVALUECHANGE_CALLBACK_INFO = 4;
    constexpr int32_t ONSELECTEDCHANGE_CALLBACK_INFO = 5;
    const std::string DEFAULT_CONTENT_VALUE = "hello world";
    const std::vector<NG::RangeContent> MENU_OPTIONS = {
        { "/data/resource/1.svg", "share" },
        { "/data/resource/2.svg", "translate" },
        { "/data/resource/3.svg", "delete" }
    };
    RefPtr<Theme> GetTheme(ThemeType type)
    {
        if (type == IconTheme::TypeId()) {
            return AceType::MakeRefPtr<IconTheme>();
        } else if (type == DialogTheme::TypeId()) {
            return AceType::MakeRefPtr<DialogTheme>();
        } else if (type == PickerTheme::TypeId()) {
            return MockThemeDefault::GetPickerTheme();
        } else if (type == ButtonTheme::TypeId()) {
            return AceType::MakeRefPtr<ButtonTheme>();
        } else if (type == TextTheme::TypeId()) {
            return AceType::MakeRefPtr<TextTheme>();
        } else {
            return nullptr;
        }
    }
} // namespace

class TextPickerModelStaticTestNg : public TestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
};

void TextPickerModelStaticTestNg::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrent();
}

void TextPickerModelStaticTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void TextPickerModelStaticTestNg::SetUp()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        return GetTheme(type);
    });
    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([](ThemeType type, int32_t themeScopeId) -> RefPtr<Theme> { return GetTheme(type); });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void TextPickerModelStaticTestNg::TearDown()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    ClearOldNodes();
}

/**
 * @tc.name: TextPickerModelStaticCreateFrameNode001
 * @tc.desc: Test CreateFrameNode
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelStaticTestNg, TextPickerModelStaticCreateFrameNode001, TestSize.Level1)
{
    auto frameNode = TextPickerModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    EXPECT_NE(frameNode, nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    EXPECT_NE(textPickerPattern, nullptr);
}

/**
 * @tc.name: TextPickerModelStaticSetSingleRange001
 * @tc.desc: Test SetTextPickerSingeRange and GetTextPickerSingeRange
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelStaticTestNg, TextPickerModelStaticSetSingleRange001, TestSize.Level1)
{
    TextPickerModelStatic::SetTextPickerSingeRange(true);
    EXPECT_TRUE(TextPickerModelStatic::GetTextPickerSingeRange());

    TextPickerModelStatic::SetTextPickerSingeRange(false);
    EXPECT_FALSE(TextPickerModelStatic::GetTextPickerSingeRange());
}

/**
 * @tc.name: TextPickerModelStaticInitialSetupSinglePicker001
 * @tc.desc: Test InitialSetupSinglePicker with TEXT type
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelStaticTestNg, TextPickerModelStaticInitialSetupSinglePicker001, TestSize.Level1)
{
    auto frameNode = TextPickerModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);

    TextPickerModelStatic::InitialSetupSinglePicker(AceType::RawPtr(frameNode), TEXT);

    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    EXPECT_FALSE(frameNode->GetChildren().empty());
}

/**
 * @tc.name: TextPickerModelStaticInitialSetupSinglePicker002
 * @tc.desc: Test InitialSetupSinglePicker with ICON type
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelStaticTestNg, TextPickerModelStaticInitialSetupSinglePicker002, TestSize.Level1)
{
    auto frameNode = TextPickerModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);

    TextPickerModelStatic::InitialSetupSinglePicker(AceType::RawPtr(frameNode), ICON);

    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    EXPECT_FALSE(frameNode->GetChildren().empty());
}

/**
 * @tc.name: TextPickerModelStaticInitialSetupSinglePicker003
 * @tc.desc: Test InitialSetupSinglePicker with MIXTURE type
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelStaticTestNg, TextPickerModelStaticInitialSetupSinglePicker003, TestSize.Level1)
{
    auto frameNode = TextPickerModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);

    TextPickerModelStatic::InitialSetupSinglePicker(AceType::RawPtr(frameNode), MIXTURE);

    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    EXPECT_FALSE(frameNode->GetChildren().empty());
}

/**
 * @tc.name: TextPickerModelStaticSetCanLoop001
 * @tc.desc: Test SetCanLoop and GetCanLoop
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelStaticTestNg, TextPickerModelStaticSetCanLoop001, TestSize.Level1)
{
    auto frameNode = TextPickerModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);

    TextPickerModelStatic::SetCanLoop(AceType::RawPtr(frameNode), true);
    EXPECT_TRUE(TextPickerModelStatic::GetCanLoop(AceType::RawPtr(frameNode)));

    TextPickerModelStatic::SetCanLoop(AceType::RawPtr(frameNode), false);
    EXPECT_FALSE(TextPickerModelStatic::GetCanLoop(AceType::RawPtr(frameNode)));
}

/**
 * @tc.name: TextPickerModelStaticSetDigitalCrownSensitivity001
 * @tc.desc: Test SetDigitalCrownSensitivity with valid value
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelStaticTestNg, TextPickerModelStaticSetDigitalCrownSensitivity001, TestSize.Level1)
{
    auto frameNode = TextPickerModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);

    std::optional<int32_t> sensitivity = 1;
    TextPickerModelStatic::SetDigitalCrownSensitivity(AceType::RawPtr(frameNode), sensitivity);

    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
}

/**
 * @tc.name: TextPickerModelStaticSetDigitalCrownSensitivity002
 * @tc.desc: Test SetDigitalCrownSensitivity with out of range value (should not be set)
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelStaticTestNg, TextPickerModelStaticSetDigitalCrownSensitivity002, TestSize.Level1)
{
    auto frameNode = TextPickerModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);

    std::optional<int32_t> sensitivity = 10; // Out of range
    TextPickerModelStatic::SetDigitalCrownSensitivity(AceType::RawPtr(frameNode), sensitivity);

    // Should not crash, value should be ignored
}

/**
 * @tc.name: TextPickerModelStaticSetDigitalCrownSensitivity003
 * @tc.desc: Test SetDigitalCrownSensitivity with nullopt (reset)
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelStaticTestNg, TextPickerModelStaticSetDigitalCrownSensitivity003, TestSize.Level1)
{
    auto frameNode = TextPickerModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);

    std::optional<int32_t> sensitivity = std::nullopt;
    TextPickerModelStatic::SetDigitalCrownSensitivity(AceType::RawPtr(frameNode), sensitivity);

    // Should not crash
}

/**
 * @tc.name: TextPickerModelStaticSetSelected001
 * @tc.desc: Test SetSelected
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelStaticTestNg, TextPickerModelStaticSetSelected001, TestSize.Level1)
{
    auto frameNode = TextPickerModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);

    uint32_t selectedValue = 2;
    TextPickerModelStatic::SetSelected(AceType::RawPtr(frameNode), selectedValue);

    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    EXPECT_EQ(textPickerPattern->GetSelected(), selectedValue);
}

/**
 * @tc.name: TextPickerModelStaticSetSelecteds001
 * @tc.desc: Test SetSelecteds
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelStaticTestNg, TextPickerModelStaticSetSelecteds001, TestSize.Level1)
{
    auto frameNode = TextPickerModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);

    std::vector<uint32_t> selectedValues = {0, 1, 2};
    TextPickerModelStatic::SetSelecteds(AceType::RawPtr(frameNode), selectedValues);

    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    EXPECT_EQ(textPickerPattern->GetSelecteds().size(), selectedValues.size());
}

/**
 * @tc.name: TextPickerModelStaticSetHasSelectAttr001
 * @tc.desc: Test SetHasSelectAttr
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelStaticTestNg, TextPickerModelStaticSetHasSelectAttr001, TestSize.Level1)
{
    auto frameNode = TextPickerModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);

    TextPickerModelStatic::SetHasSelectAttr(AceType::RawPtr(frameNode), true);

    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    EXPECT_TRUE(textPickerPattern->isHasSelectAttr_);
}

/**
 * @tc.name: TextPickerModelStaticSetIsCascade001
 * @tc.desc: Test SetIsCascade and IsCascade
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelStaticTestNg, TextPickerModelStaticSetIsCascade001, TestSize.Level1)
{
    auto frameNode = TextPickerModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);

    TextPickerModelStatic::SetIsCascade(AceType::RawPtr(frameNode), true);
    EXPECT_TRUE(TextPickerModelStatic::IsCascade(AceType::RawPtr(frameNode)));

    TextPickerModelStatic::SetIsCascade(AceType::RawPtr(frameNode), false);
    EXPECT_FALSE(TextPickerModelStatic::IsCascade(AceType::RawPtr(frameNode)));
}

/**
 * @tc.name: TextPickerModelStaticSetColumnKind001
 * @tc.desc: Test SetColumnKind
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelStaticTestNg, TextPickerModelStaticSetColumnKind001, TestSize.Level1)
{
    auto frameNode = TextPickerModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);

    TextPickerModelStatic::SetColumnKind(AceType::RawPtr(frameNode), TEXT);

    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    EXPECT_EQ(textPickerPattern->columnsKind_, TEXT);

    TextPickerModelStatic::SetColumnKind(AceType::RawPtr(frameNode), MIXTURE);
    EXPECT_EQ(textPickerPattern->columnsKind_, MIXTURE);
}

/**
 * @tc.name: TextPickerModelStaticSetColumnWidths001
 * @tc.desc: Test SetColumnWidths and GetColumnWidths
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelStaticTestNg, TextPickerModelStaticSetColumnWidths001, TestSize.Level1)
{
    auto frameNode = TextPickerModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);

    std::vector<Dimension> widths = {Dimension(50.0f, DimensionUnit::VP),
                                      Dimension(30.0f, DimensionUnit::VP),
                                      Dimension(20.0f, DimensionUnit::VP)};
    TextPickerModelStatic::SetColumnWidths(AceType::RawPtr(frameNode), widths);

    auto resultWidths = TextPickerModelStatic::GetColumnWidths(AceType::RawPtr(frameNode));
    EXPECT_EQ(resultWidths.size(), widths.size());
    for (size_t i = 0; i < widths.size(); i++) {
        EXPECT_FLOAT_EQ(resultWidths[i].Value(), widths[i].Value());
    }
}

/**
 * @tc.name: TextPickerModelStaticGetColumnWidthsSize001
 * @tc.desc: Test GetColumnWidthsSize
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelStaticTestNg, TextPickerModelStaticGetColumnWidthsSize001, TestSize.Level1)
{
    auto frameNode = TextPickerModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);

    EXPECT_EQ(TextPickerModelStatic::GetColumnWidthsSize(AceType::RawPtr(frameNode)), 0);

    std::vector<Dimension> widths = {Dimension(50.0f, DimensionUnit::VP),
                                      Dimension(30.0f, DimensionUnit::VP)};
    TextPickerModelStatic::SetColumnWidths(AceType::RawPtr(frameNode), widths);

    EXPECT_EQ(TextPickerModelStatic::GetColumnWidthsSize(AceType::RawPtr(frameNode)), widths.size());
}

/**
 * @tc.name: TextPickerModelStaticSetNormalTextStyle001
 * @tc.desc: Test SetNormalTextStyle
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelStaticTestNg, TextPickerModelStaticSetNormalTextStyle001, TestSize.Level1)
{
    auto frameNode = TextPickerModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    frameNode->AttachContext(AceType::RawPtr(context));
    auto pickerTheme = MockThemeDefault::GetPickerTheme();
    ASSERT_NE(pickerTheme, nullptr);

    PickerTextStyle textStyle;
    textStyle.fontSize = Dimension(20.0_vp);
    textStyle.textColor = Color::RED;
    textStyle.fontWeight = FontWeight::BOLD;

    TextPickerModelStatic::SetNormalTextStyle(AceType::RawPtr(frameNode), pickerTheme, textStyle);

    auto layoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
}

/**
 * @tc.name: TextPickerModelStaticSetSelectedTextStyle001
 * @tc.desc: Test SetSelectedTextStyle
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelStaticTestNg, TextPickerModelStaticSetSelectedTextStyle001, TestSize.Level1)
{
    auto frameNode = TextPickerModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    frameNode->AttachContext(AceType::RawPtr(context));
    auto pickerTheme = MockThemeDefault::GetPickerTheme();
    ASSERT_NE(pickerTheme, nullptr);

    PickerTextStyle textStyle;
    textStyle.fontSize = Dimension(22.0_vp);
    textStyle.textColor = Color::BLUE;
    textStyle.fontWeight = FontWeight::MEDIUM;

    TextPickerModelStatic::SetSelectedTextStyle(AceType::RawPtr(frameNode), pickerTheme, textStyle);

    auto layoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
}

/**
 * @tc.name: TextPickerModelStaticSetDisappearTextStyle001
 * @tc.desc: Test SetDisappearTextStyle
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelStaticTestNg, TextPickerModelStaticSetDisappearTextStyle001, TestSize.Level1)
{
    auto frameNode = TextPickerModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    frameNode->AttachContext(AceType::RawPtr(context));
    auto pickerTheme = MockThemeDefault::GetPickerTheme();
    ASSERT_NE(pickerTheme, nullptr);

    PickerTextStyle textStyle;
    textStyle.fontSize = Dimension(16.0_vp);
    textStyle.textColor = Color::GRAY;
    textStyle.fontWeight = FontWeight::NORMAL;

    TextPickerModelStatic::SetDisappearTextStyle(AceType::RawPtr(frameNode), pickerTheme, textStyle);

    auto layoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
}

/**
 * @tc.name: TextPickerModelStaticSetDefaultTextStyle001
 * @tc.desc: Test SetDefaultTextStyle with PickerTextStyle
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelStaticTestNg, TextPickerModelStaticSetDefaultTextStyle001, TestSize.Level1)
{
    auto frameNode = TextPickerModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    frameNode->AttachContext(AceType::RawPtr(context));

    PickerTextStyle textStyle;
    textStyle.fontSize = Dimension(18.0_vp);
    textStyle.textColor = Color::BLACK;
    textStyle.fontWeight = FontWeight::REGULAR;

    TextPickerModelStatic::SetDefaultTextStyle(AceType::RawPtr(frameNode), textStyle);

    auto layoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
}

/**
 * @tc.name: TextPickerModelStaticSetSelectedBackgroundStyle001
 * @tc.desc: Test SetSelectedBackgroundStyle
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelStaticTestNg, TextPickerModelStaticSetSelectedBackgroundStyle001, TestSize.Level1)
{
    auto frameNode = TextPickerModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);

    PickerBackgroundStyle bgStyle;
    bgStyle.color = Color(0xFFFF0000);
    bgStyle.borderRadius = BorderRadiusProperty(8.0_vp);

    TextPickerModelStatic::SetSelectedBackgroundStyle(AceType::RawPtr(frameNode), bgStyle);

    auto layoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
}

/**
 * @tc.name: TextPickerModelStaticSetDefaultPickerItemHeight001
 * @tc.desc: Test SetDefaultPickerItemHeight and GetDefaultPickerItemHeight
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelStaticTestNg, TextPickerModelStaticSetDefaultPickerItemHeight001, TestSize.Level1)
{
    auto frameNode = TextPickerModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);

    Dimension height = 40.0_vp;
    TextPickerModelStatic::SetDefaultPickerItemHeight(AceType::RawPtr(frameNode), height);

    auto resultHeight = TextPickerModelStatic::GetDefaultPickerItemHeight(AceType::RawPtr(frameNode));
    EXPECT_FLOAT_EQ(resultHeight.ConvertToPx(), height.ConvertToPx());
}

/**
 * @tc.name: TextPickerModelStaticSetDefaultPickerItemHeight002
 * @tc.desc: Test SetDefaultPickerItemHeight with nullopt (reset)
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelStaticTestNg, TextPickerModelStaticSetDefaultPickerItemHeight002, TestSize.Level1)
{
    auto frameNode = TextPickerModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);

    std::optional<Dimension> height = std::nullopt;
    TextPickerModelStatic::SetDefaultPickerItemHeight(AceType::RawPtr(frameNode), height);

    // Should not crash
}

/**
 * @tc.name: TextPickerModelStaticSetBackgroundColor001
 * @tc.desc: Test SetBackgroundColor
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelStaticTestNg, TextPickerModelStaticSetBackgroundColor001, TestSize.Level1)
{
    auto frameNode = TextPickerModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);

    TextPickerModelStatic::SetBackgroundColor(AceType::RawPtr(frameNode), Color::GRAY);

    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    EXPECT_EQ(textPickerPattern->GetBackgroundColor().GetValue(), Color::GRAY.GetValue());
}

/**
 * @tc.name: TextPickerModelStaticSetRange001
 * @tc.desc: Test SetRange and IsSingle/GetSingleRange
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelStaticTestNg, TextPickerModelStaticSetRange001, TestSize.Level1)
{
    auto frameNode = TextPickerModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);

    TextPickerModelStatic::SetRange(AceType::RawPtr(frameNode), MENU_OPTIONS);

    EXPECT_TRUE(TextPickerModelStatic::IsSingle(AceType::RawPtr(frameNode)));

    std::vector<NG::RangeContent> rangeValue;
    EXPECT_TRUE(TextPickerModelStatic::GetSingleRange(AceType::RawPtr(frameNode), rangeValue));
    EXPECT_EQ(rangeValue.size(), MENU_OPTIONS.size());
}

/**
 * @tc.name: TextPickerModelStaticSetValue001
 * @tc.desc: Test SetValue and getTextPickerValue
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelStaticTestNg, TextPickerModelStaticSetValue001, TestSize.Level1)
{
    auto frameNode = TextPickerModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);

    TextPickerModelStatic::SetRange(AceType::RawPtr(frameNode), MENU_OPTIONS);

    TextPickerModelStatic::SetValue(AceType::RawPtr(frameNode), MENU_OPTIONS[1].text_);

    auto value = TextPickerModelStatic::getTextPickerValue(AceType::RawPtr(frameNode));
    EXPECT_EQ(value, MENU_OPTIONS[1].text_);
}

/**
 * @tc.name: TextPickerModelStaticSetColumns001
 * @tc.desc: Test SetColumns for non-cascade picker
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelStaticTestNg, TextPickerModelStaticSetColumns001, TestSize.Level1)
{
    auto frameNode = TextPickerModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);

    std::vector<NG::TextCascadePickerOptions> options;
    NG::TextCascadePickerOptions option1;
    option1.rangeResult = {"11", "12", "13"};
    options.push_back(option1);
    NG::TextCascadePickerOptions option2;
    option2.rangeResult = {"21", "22", "23"};
    options.push_back(option2);

    TextPickerModelStatic::SetColumns(AceType::RawPtr(frameNode), options);

    EXPECT_FALSE(TextPickerModelStatic::IsCascade(AceType::RawPtr(frameNode)));
}

/**
 * @tc.name: TextPickerModelStaticSetColumns002
 * @tc.desc: Test SetColumns for cascade picker
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelStaticTestNg, TextPickerModelStaticSetColumns002, TestSize.Level1)
{
    auto frameNode = TextPickerModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);

    TextPickerModelStatic::SetIsCascade(AceType::RawPtr(frameNode), true);

    std::vector<NG::TextCascadePickerOptions> options;
    NG::TextCascadePickerOptions option1;
    option1.rangeResult = {"11"};
    NG::TextCascadePickerOptions childOption;
    childOption.rangeResult = {"12", "13"};
    option1.children.push_back(childOption);
    options.push_back(option1);

    TextPickerModelStatic::SetColumns(AceType::RawPtr(frameNode), options);

    EXPECT_TRUE(TextPickerModelStatic::IsCascade(AceType::RawPtr(frameNode)));
}

/**
 * @tc.name: TextPickerModelStaticGetMultiOptions001
 * @tc.desc: Test GetMultiOptions
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelStaticTestNg, TextPickerModelStaticGetMultiOptions001, TestSize.Level1)
{
    auto frameNode = TextPickerModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);

    std::vector<NG::TextCascadePickerOptions> options;
    NG::TextCascadePickerOptions option1;
    option1.rangeResult = {"11", "12", "13"};
    options.push_back(option1);
    NG::TextCascadePickerOptions option2;
    option2.rangeResult = {"21", "22", "23"};
    options.push_back(option2);

    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    std::vector<NG::TextCascadePickerOptions> cascadeOptions;
    textPickerPattern->SetCascadeOptions(options, cascadeOptions);

    std::vector<NG::TextCascadePickerOptions> result;
    EXPECT_TRUE(TextPickerModelStatic::GetMultiOptions(AceType::RawPtr(frameNode), result));
}

/**
 * @tc.name: TextPickerModelStaticSetValues001
 * @tc.desc: Test SetValues for non-cascade picker
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelStaticTestNg, TextPickerModelStaticSetValues001, TestSize.Level1)
{
    auto frameNode = TextPickerModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);

    std::vector<NG::TextCascadePickerOptions> options;
    NG::TextCascadePickerOptions option1;
    option1.rangeResult = {"11", "12", "13"};
    options.push_back(option1);
    NG::TextCascadePickerOptions option2;
    option2.rangeResult = {"21", "22", "23"};
    options.push_back(option2);

    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    std::vector<NG::TextCascadePickerOptions> cascadeOptions;
    textPickerPattern->SetCascadeOptions(options, cascadeOptions);

    std::vector<std::string> values = {"11", "21"};
    TextPickerModelStatic::SetValues(AceType::RawPtr(frameNode), values);

    auto resultValues = TextPickerModelStatic::getTextPickerValues(AceType::RawPtr(frameNode));
    EXPECT_FALSE(resultValues.empty());
}

/**
 * @tc.name: TextPickerModelStaticGetMaxCount001
 * @tc.desc: Test GetMaxCount
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelStaticTestNg, TextPickerModelStaticGetMaxCount001, TestSize.Level1)
{
    auto frameNode = TextPickerModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);

    EXPECT_EQ(TextPickerModelStatic::GetMaxCount(AceType::RawPtr(frameNode)), 1);
}

/**
 * @tc.name: TextPickerModelStaticGetDisappearTextStyle001
 * @tc.desc: Test getDisappearTextStyle
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelStaticTestNg, TextPickerModelStaticGetDisappearTextStyle001, TestSize.Level1)
{
    auto frameNode = TextPickerModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    frameNode->AttachContext(AceType::RawPtr(context));

    auto textStyle = TextPickerModelStatic::getDisappearTextStyle(AceType::RawPtr(frameNode));
    EXPECT_TRUE(textStyle.fontSize.has_value() || textStyle.textColor.has_value());
}

/**
 * @tc.name: TextPickerModelStaticGetNormalTextStyle001
 * @tc.desc: Test getNormalTextStyle
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelStaticTestNg, TextPickerModelStaticGetNormalTextStyle001, TestSize.Level1)
{
    auto frameNode = TextPickerModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    frameNode->AttachContext(AceType::RawPtr(context));

    auto textStyle = TextPickerModelStatic::getNormalTextStyle(AceType::RawPtr(frameNode));
    EXPECT_TRUE(textStyle.fontSize.has_value() || textStyle.textColor.has_value());
}

/**
 * @tc.name: TextPickerModelStaticGetSelectedTextStyle001
 * @tc.desc: Test getSelectedTextStyle
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelStaticTestNg, TextPickerModelStaticGetSelectedTextStyle001, TestSize.Level1)
{
    auto frameNode = TextPickerModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    frameNode->AttachContext(AceType::RawPtr(context));

    auto textStyle = TextPickerModelStatic::getSelectedTextStyle(AceType::RawPtr(frameNode));
    EXPECT_TRUE(textStyle.fontSize.has_value() || textStyle.textColor.has_value());
}

/**
 * @tc.name: TextPickerModelStaticGetTextPickerSelectedIndex001
 * @tc.desc: Test getTextPickerSelectedIndex
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelStaticTestNg, TextPickerModelStaticGetTextPickerSelectedIndex001, TestSize.Level1)
{
    auto frameNode = TextPickerModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);

    uint32_t selectedIndex = 3;
    auto layoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateSelected(selectedIndex);

    EXPECT_EQ(TextPickerModelStatic::getTextPickerSelectedIndex(AceType::RawPtr(frameNode)), selectedIndex);
}

/**
 * @tc.name: TextPickerModelStaticGetTextPickerRange001
 * @tc.desc: Test getTextPickerRange
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelStaticTestNg, TextPickerModelStaticGetTextPickerRange001, TestSize.Level1)
{
    auto frameNode = TextPickerModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);

    TextPickerModelStatic::SetRange(AceType::RawPtr(frameNode), MENU_OPTIONS);

    auto range = TextPickerModelStatic::getTextPickerRange(AceType::RawPtr(frameNode));
    EXPECT_FALSE(range.empty());
}

/**
 * @tc.name: TextPickerModelStaticSetDivider001
 * @tc.desc: Test SetDivider
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelStaticTestNg, TextPickerModelStaticSetDivider001, TestSize.Level1)
{
    auto frameNode = TextPickerModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);

    ItemDivider divider;
    divider.strokeWidth = 2.0_vp;
    divider.startMargin = 4.0_vp;
    divider.endMargin = 4.0_vp;
    divider.color = Color::GRAY;

    TextPickerModelStatic::SetDivider(AceType::RawPtr(frameNode), divider);

    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
}

/**
 * @tc.name: TextPickerModelStaticSetGradientHeight001
 * @tc.desc: Test SetGradientHeight
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelStaticTestNg, TextPickerModelStaticSetGradientHeight001, TestSize.Level1)
{
    auto frameNode = TextPickerModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    frameNode->AttachContext(AceType::RawPtr(context));

    Dimension gradientHeight = 30.0_vp;
    TextPickerModelStatic::SetGradientHeight(AceType::RawPtr(frameNode), gradientHeight);

    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
}

/**
 * @tc.name: TextPickerModelStaticSetDisableTextStyleAnimation001
 * @tc.desc: Test SetDisableTextStyleAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelStaticTestNg, TextPickerModelStaticSetDisableTextStyleAnimation001, TestSize.Level1)
{
    auto frameNode = TextPickerModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);

    TextPickerModelStatic::SetDisableTextStyleAnimation(AceType::RawPtr(frameNode), true);

    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
}

/**
 * @tc.name: TextPickerModelStaticSetOnCascadeChange001
 * @tc.desc: Test SetOnCascadeChange event
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelStaticTestNg, TextPickerModelStaticSetOnCascadeChange001, TestSize.Level1)
{
    auto frameNode = TextPickerModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);

    int32_t callbackInfo = 0;
    auto onChangeFunc = [&callbackInfo](const std::vector<std::string>& value, const std::vector<double>& index) {
        callbackInfo = ONCHANGE_CALLBACK_INFO;
    };
    TextPickerModelStatic::SetOnCascadeChange(AceType::RawPtr(frameNode), std::move(onChangeFunc));

    auto eventHub = frameNode->GetEventHub<TextPickerEventHub>();
    ASSERT_NE(eventHub, nullptr);

    std::vector<std::string> value = {"hello"};
    std::vector<double> index = {0.0};
    eventHub->FireChangeEvent(value, index);
    EXPECT_EQ(callbackInfo, ONCHANGE_CALLBACK_INFO);
}

/**
 * @tc.name: TextPickerModelStaticSetOnScrollStop001
 * @tc.desc: Test SetOnScrollStop event
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelStaticTestNg, TextPickerModelStaticSetOnScrollStop001, TestSize.Level1)
{
    auto frameNode = TextPickerModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);

    int32_t callbackInfo = 0;
    auto onScrollStopFunc = [&callbackInfo](const std::vector<std::string>& value, const std::vector<double>& index) {
        callbackInfo = ONSCROLLSTOP_CALLBACK_INFO;
    };
    TextPickerModelStatic::SetOnScrollStop(AceType::RawPtr(frameNode), std::move(onScrollStopFunc));

    auto eventHub = frameNode->GetEventHub<TextPickerEventHub>();
    ASSERT_NE(eventHub, nullptr);

    std::vector<std::string> value = {"hello"};
    std::vector<double> index = {0.0};
    eventHub->FireScrollStopEvent(value, index);
    EXPECT_EQ(callbackInfo, ONSCROLLSTOP_CALLBACK_INFO);
}

/**
 * @tc.name: TextPickerModelStaticSetOnEnterSelectedArea001
 * @tc.desc: Test SetOnEnterSelectedArea event
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelStaticTestNg, TextPickerModelStaticSetOnEnterSelectedArea001, TestSize.Level1)
{
    auto frameNode = TextPickerModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);

    int32_t callbackInfo = 0;
    auto onEnterSelectedAreaFunc = [&callbackInfo](
        const std::vector<std::string>& value, const std::vector<double>& index) {
        callbackInfo = ONENTERSELECTEDAREA_CALLBACK_INFO;
    };
    TextPickerModelStatic::SetOnEnterSelectedArea(AceType::RawPtr(frameNode), std::move(onEnterSelectedAreaFunc));

    auto eventHub = frameNode->GetEventHub<TextPickerEventHub>();
    ASSERT_NE(eventHub, nullptr);

    std::vector<std::string> value = {"hello"};
    std::vector<double> index = {0.0};
    eventHub->FireEnterSelectedAreaEvent(value, index);
    EXPECT_EQ(callbackInfo, ONENTERSELECTEDAREA_CALLBACK_INFO);
}

/**
 * @tc.name: TextPickerModelStaticSetOnValueChangeEvent001
 * @tc.desc: Test SetOnValueChangeEvent event
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelStaticTestNg, TextPickerModelStaticSetOnValueChangeEvent001, TestSize.Level1)
{
    auto frameNode = TextPickerModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);

    int32_t callbackInfo = 0;
    auto onValueChangeFunc = [&callbackInfo](const std::vector<std::string>& value) {
        callbackInfo = ONVALUECHANGE_CALLBACK_INFO;
    };
    TextPickerModelStatic::SetOnValueChangeEvent(AceType::RawPtr(frameNode), std::move(onValueChangeFunc));

    auto eventHub = frameNode->GetEventHub<TextPickerEventHub>();
    ASSERT_NE(eventHub, nullptr);

    std::vector<std::string> value = {"hello"};
    std::vector<double> index = {0.0};
    eventHub->FireChangeEvent(value, index);
    EXPECT_EQ(callbackInfo, ONVALUECHANGE_CALLBACK_INFO);
}

/**
 * @tc.name: TextPickerModelStaticSetOnSelectedChangeEvent001
 * @tc.desc: Test SetOnSelectedChangeEvent event
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelStaticTestNg, TextPickerModelStaticSetOnSelectedChangeEvent001, TestSize.Level1)
{
    auto frameNode = TextPickerModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);

    int32_t callbackInfo = 0;
    auto onSelectedChangeFunc = [&callbackInfo](const std::vector<double>& index) {
        callbackInfo = ONSELECTEDCHANGE_CALLBACK_INFO;
    };
    TextPickerModelStatic::SetOnSelectedChangeEvent(AceType::RawPtr(frameNode), std::move(onSelectedChangeFunc));

    auto eventHub = frameNode->GetEventHub<TextPickerEventHub>();
    ASSERT_NE(eventHub, nullptr);

    std::vector<std::string> value = {"hello"};
    std::vector<double> index = {0.0};
    eventHub->FireChangeEvent(value, index);
    EXPECT_EQ(callbackInfo, ONSELECTEDCHANGE_CALLBACK_INFO);
}

/**
 * @tc.name: TextPickerModelStaticGetSelectedSize001
 * @tc.desc: Test GetSelectedSize
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelStaticTestNg, TextPickerModelStaticGetSelectedSize001, TestSize.Level1)
{
    auto frameNode = TextPickerModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);

    std::vector<uint32_t> selectedValues = {0, 1, 2};
    TextPickerModelStatic::SetSelecteds(AceType::RawPtr(frameNode), selectedValues);

    EXPECT_EQ(TextPickerModelStatic::GetSelectedSize(AceType::RawPtr(frameNode)), selectedValues.size());
}

/**
 * @tc.name: TextPickerModelStaticGetTextPickerValues001
 * @tc.desc: Test getTextPickerValues
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelStaticTestNg, TextPickerModelStaticGetTextPickerValues001, TestSize.Level1)
{
    auto frameNode = TextPickerModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);

    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);

    std::vector<std::string> values = {"value1", "value2", "value3"};
    textPickerPattern->SetValues(values);

    auto result = TextPickerModelStatic::getTextPickerValues(AceType::RawPtr(frameNode));
    EXPECT_FALSE(result.empty());
}

/**
 * @tc.name: TextPickerModelStaticGetTextPickerSelecteds001
 * @tc.desc: Test getTextPickerSelecteds
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelStaticTestNg, TextPickerModelStaticGetTextPickerSelecteds001, TestSize.Level1)
{
    auto frameNode = TextPickerModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);

    std::vector<uint32_t> selectedValues = {0, 1, 2};
    TextPickerModelStatic::SetSelecteds(AceType::RawPtr(frameNode), selectedValues);

    auto result = TextPickerModelStatic::getTextPickerSelecteds(AceType::RawPtr(frameNode));
    EXPECT_EQ(result.size(), selectedValues.size());
}

/**
 * @tc.name: TextPickerModelStaticSetTextPickerRangeType001
 * @tc.desc: Test SetTextPickerRangeType and GetTextPickerRangeType
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelStaticTestNg, TextPickerModelStaticSetTextPickerRangeType001, TestSize.Level1)
{
    auto frameNode = TextPickerModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);

    int32_t rangeType = 5;
    TextPickerModelStatic::SetTextPickerRangeType(AceType::RawPtr(frameNode), rangeType);

    EXPECT_EQ(TextPickerModelStatic::GetTextPickerRangeType(AceType::RawPtr(frameNode)), rangeType);
}

/**
 * @tc.name: TextPickerModelStaticSetEnableHapticFeedback001
 * @tc.desc: Test SetEnableHapticFeedback and GetEnableHapticFeedback
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelStaticTestNg, TextPickerModelStaticSetEnableHapticFeedback001, TestSize.Level1)
{
    auto frameNode = TextPickerModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);

    TextPickerModelStatic::SetEnableHapticFeedback(AceType::RawPtr(frameNode), false);
    EXPECT_FALSE(TextPickerModelStatic::GetEnableHapticFeedback(AceType::RawPtr(frameNode)));

    TextPickerModelStatic::SetEnableHapticFeedback(AceType::RawPtr(frameNode), true);
    EXPECT_TRUE(TextPickerModelStatic::GetEnableHapticFeedback(AceType::RawPtr(frameNode)));
}

/**
 * @tc.name: TextPickerModelStaticSetEnableHapticFeedback002
 * @tc.desc: Test SetEnableHapticFeedback with nullopt (default)
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelStaticTestNg, TextPickerModelStaticSetEnableHapticFeedback002, TestSize.Level1)
{
    auto frameNode = TextPickerModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);

    std::optional<bool> hapticFeedback = std::nullopt;
    TextPickerModelStatic::SetEnableHapticFeedback(AceType::RawPtr(frameNode), hapticFeedback);

    // Should default to true
    EXPECT_TRUE(TextPickerModelStatic::GetEnableHapticFeedback(AceType::RawPtr(frameNode)));
}

/**
 * @tc.name: TextPickerModelStaticConvertFontScaleValue001
 * @tc.desc: Test ConvertFontScaleValue with zero font scale
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelStaticTestNg, TextPickerModelStaticConvertFontScaleValue001, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);

    Dimension fontSize = 20.0_px;
    pipeline->SetFontScale(0.0f);

    auto result = TextPickerModelStatic::ConvertFontScaleValue(fontSize);
    EXPECT_FLOAT_EQ(result.Value(), fontSize.Value());
}

/**
 * @tc.name: TextPickerModelStaticConvertFontScaleValue002
 * @tc.desc: Test ConvertFontScaleValue with VP unit (should not convert)
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelStaticTestNg, TextPickerModelStaticConvertFontScaleValue002, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);

    Dimension fontSize = 20.0_vp;
    pipeline->SetFontScale(1.5f);

    auto result = TextPickerModelStatic::ConvertFontScaleValue(fontSize);
    EXPECT_FLOAT_EQ(result.Value(), fontSize.Value());
}

/**
 * @tc.name: TextPickerModelStaticConvertFontScaleValue003
 * @tc.desc: Test ConvertFontScaleValue with font scale and follow system
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelStaticTestNg, TextPickerModelStaticConvertFontScaleValue003, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);

    Dimension fontSize = 20.0_px;
    pipeline->SetFollowSystem(true);
    pipeline->SetFontScale(1.0f);
    pipeline->SetMaxAppFontScale(2.0f);

    auto result = TextPickerModelStatic::ConvertFontScaleValue(fontSize);
    EXPECT_FLOAT_EQ(result.Value(), fontSize.Value());
}

/**
 * @tc.name: TextPickerModelStaticConvertFontScaleValue004
 * @tc.desc: Test ConvertFontScaleValue with font scale greater than max
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelStaticTestNg, TextPickerModelStaticConvertFontScaleValue004, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);

    Dimension fontSize = 20.0_px;
    pipeline->SetFollowSystem(true);
    pipeline->SetFontScale(2.0f);
    pipeline->SetMaxAppFontScale(2.0f);

    auto result = TextPickerModelStatic::ConvertFontScaleValue(fontSize);
    EXPECT_FLOAT_EQ(result.Value(), 10.0f);
}

/**
 * @tc.name: TextPickerModelStaticNullFrameNode001
 * @tc.desc: Test methods with null frame node
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelStaticTestNg, TextPickerModelStaticNullFrameNode001, TestSize.Level1)
{
    FrameNode* nullNode = nullptr;

    TextPickerModelStatic::SetCanLoop(nullNode, true);
    EXPECT_EQ(TextPickerModelStatic::GetCanLoop(nullNode), 1);

    TextPickerModelStatic::SetSelected(nullNode, 0);
    TextPickerModelStatic::SetSelecteds(nullNode, {0, 1});
    TextPickerModelStatic::SetHasSelectAttr(nullNode, true);
    TextPickerModelStatic::SetIsCascade(nullNode, true);
    TextPickerModelStatic::SetColumnKind(nullNode, TEXT);

    EXPECT_FALSE(TextPickerModelStatic::IsSingle(nullNode));
    EXPECT_FALSE(TextPickerModelStatic::IsCascade(nullNode));
    EXPECT_EQ(TextPickerModelStatic::GetMaxCount(nullNode), 1);
    EXPECT_EQ(TextPickerModelStatic::GetSelectedSize(nullNode), 0);
    EXPECT_EQ(TextPickerModelStatic::GetColumnWidthsSize(nullNode), 0);

    EXPECT_EQ(TextPickerModelStatic::getTextPickerValue(nullNode), "");
    EXPECT_EQ(TextPickerModelStatic::getTextPickerRange(nullNode), "");
    EXPECT_EQ(TextPickerModelStatic::getTextPickerValues(nullNode), "");
}

/**
 * @tc.name: TextPickerModelStaticEdgeCases001
 * @tc.desc: Test edge cases for SetValues with empty/mismatched values
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelStaticTestNg, TextPickerModelStaticEdgeCases001, TestSize.Level1)
{
    auto frameNode = TextPickerModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);

    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);

    std::vector<NG::TextCascadePickerOptions> options;
    NG::TextCascadePickerOptions option1;
    option1.rangeResult = {"11", "12"};
    options.push_back(option1);
    NG::TextCascadePickerOptions option2;
    option2.rangeResult = {"21", "22"};
    options.push_back(option2);

    std::vector<NG::TextCascadePickerOptions> cascadeOptions;
    textPickerPattern->SetCascadeOptions(options, cascadeOptions);

    // Test with fewer values than options
    std::vector<std::string> values = {"11"};
    TextPickerModelStatic::SetValues(AceType::RawPtr(frameNode), values);

    // Should not crash
}

/**
 * @tc.name: TextPickerModelStaticEdgeCases002
 * @tc.desc: Test edge case for SetValue with non-existent value
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelStaticTestNg, TextPickerModelStaticEdgeCases002, TestSize.Level1)
{
    auto frameNode = TextPickerModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);

    TextPickerModelStatic::SetRange(AceType::RawPtr(frameNode), MENU_OPTIONS);

    // Try to set a value that doesn't exist in range
    TextPickerModelStatic::SetValue(AceType::RawPtr(frameNode), "non_existent_value");

    // Should not crash, selected should remain unchanged
}

/**
 * @tc.name: TextPickerModelStaticEdgeCases003
 * @tc.desc: Test empty options for GetMultiOptions
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelStaticTestNg, TextPickerModelStaticEdgeCases003, TestSize.Level1)
{
    auto frameNode = TextPickerModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);

    std::vector<NG::TextCascadePickerOptions> result;
    EXPECT_TRUE(TextPickerModelStatic::GetMultiOptions(AceType::RawPtr(frameNode), result));
    EXPECT_TRUE(result.empty());
}

} // namespace OHOS::Ace::NG