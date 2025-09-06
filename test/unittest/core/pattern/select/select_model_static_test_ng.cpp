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

#include <cstdint>
#include <iostream>
#include <optional>
#include <string>

#include "gtest/gtest.h"

#define protected public
#define private public
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/geometry/dimension.h"
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
#include "core/components_ng/pattern/menu/menu_item/menu_item_pattern.h"
#include "core/components_ng/pattern/menu/menu_layout_property.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_layout_property.h"
#include "core/components_ng/pattern/select/select_model_ng.h"
#include "core/components_ng/pattern/select/select_model_static.h"
#include "core/components_ng/pattern/select/select_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace::NG {
namespace {
const std::string OPTION_TEXT = "option";
const std::string FILE_SOURCE = "/common/icon.png";

} // namespace
class SelectModelStaticTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    static void SetUpThemeManager();
    void SetUp() override;
    void TearDown() override;

protected:
    static RefPtr<FrameNode> CreateSelect(const std::vector<SelectParam>& value, const TestProperty& test);
};

void SelectModelStaticTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    SetUpThemeManager();
}

void SelectModelStaticTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void SelectModelStaticTestNg::SetUpThemeManager()
{
    auto themeManager = AceType::DynamicCast<MockThemeManager>(MockPipelineContext::GetCurrent()->GetThemeManager());
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        if (type == IconTheme::TypeId()) {
            return AceType::MakeRefPtr<IconTheme>();
        } else if (type == SelectTheme::TypeId()) {
            return AceType::MakeRefPtr<SelectTheme>();
        } else if (type == MenuTheme::TypeId()) {
            return AceType::MakeRefPtr<MenuTheme>();
        } else {
            return nullptr;
        }
    });
    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([](ThemeType type, int32_t themeScopeId) -> RefPtr<Theme> {
            if (type == IconTheme::TypeId()) {
                return AceType::MakeRefPtr<IconTheme>();
            } else if (type == SelectTheme::TypeId()) {
                return AceType::MakeRefPtr<SelectTheme>();
            } else if (type == MenuTheme::TypeId()) {
                return AceType::MakeRefPtr<MenuTheme>();
            } else {
                return nullptr;
            }
        });
}

void SelectModelStaticTestNg::SetUp() {}

void SelectModelStaticTestNg::TearDown() {}

/**
 * @tc.name: SetDivider
 * @tc.desc: Test SelectPattern SetDivider.
 * @tc.type: FUNC
 */
HWTEST_F(SelectModelStaticTestNg, SetDividerTest, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    /**
     * @tc.steps: step1. Create select.
     */
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto pattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(pattern->options_.size(), 0);
    auto option = pattern->options_[0];
    ASSERT_NE(option, nullptr);
    auto paintProperty = option->GetPaintProperty<MenuItemPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_EQ(paintProperty->GetDivider(), std::nullopt);
    /**
     * @tc.steps: step2. call set divider nullopt.
     * @tc.expected: dividier has value.
     */
    auto themeManager = AceType::DynamicCast<MockThemeManager>(MockPipelineContext::GetCurrent()->GetThemeManager());
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(nullptr));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(nullptr));
    SelectModelStatic::SetDivider(select, std::nullopt);
    SetUpThemeManager();
    SelectModelStatic::SetDivider(select, std::nullopt);
    EXPECT_NE(paintProperty->GetDivider(), std::nullopt);
    /**
     * @tc.steps: step3. set divider color red.
     * @tc.expected: get divider color is red.
     */
    NG::SelectDivider divider = SelectModelStatic::GetDefaultDivider(select);
    divider.color = Color::RED;
    std::optional<NG::SelectDivider> dividerOption = divider;
    SelectModelStatic::SetDivider(select, dividerOption);
    EXPECT_NE(paintProperty->GetDivider(), std::nullopt);
    EXPECT_EQ(paintProperty->GetDividerValue().color, Color::RED);
}

/**
 * @tc.name: SetArrowPosition
 * @tc.desc: Test SelectPattern SetArrowPosition.
 * @tc.type: FUNC
 */
HWTEST_F(SelectModelStaticTestNg, SetArrowPosition, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    /**
     * @tc.steps: step1. Create select.
     */
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto pattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(pattern->options_.size(), 0);
    auto option = pattern->options_[0];
    ASSERT_NE(option, nullptr);
    SelectModelStatic::SetArrowPosition(select, std::nullopt);
    auto row = AceType::DynamicCast<FrameNode>(select->GetFirstChild());
    ASSERT_NE(row, nullptr);
    auto rowProps = row->GetLayoutProperty<FlexLayoutProperty>();
    ASSERT_NE(rowProps, nullptr);
    EXPECT_EQ(rowProps->GetFlexDirectionValue(FlexDirection::ROW), FlexDirection::ROW);
    ArrowPosition position = ArrowPosition::START;
    std::optional<ArrowPosition> optionPosition = position;
    SelectModelStatic::SetArrowPosition(select, optionPosition);
    EXPECT_EQ(rowProps->GetFlexDirectionValue(FlexDirection::ROW), FlexDirection::ROW_REVERSE);
}

/**
 * @tc.name: SetSpace
 * @tc.desc: Test SelectPattern SetSpace.
 * @tc.type: FUNC
 */
HWTEST_F(SelectModelStaticTestNg, SetSpace, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    /**
     * @tc.steps: step1. Create select.
     */
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto pattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(pattern, nullptr);
    SelectModelStatic::SetSpace(select, std::nullopt);
    auto row = AceType::DynamicCast<FrameNode>(select->GetFirstChild());
    ASSERT_NE(row, nullptr);
    auto rowProps = row->GetLayoutProperty<FlexLayoutProperty>();
    ASSERT_NE(rowProps, nullptr);
    EXPECT_NE(rowProps->GetSpaceValue(Dimension()).Value(), 1);
    Dimension dimension = Dimension(1, DimensionUnit::VP);
    std::optional<Dimension> optionValue = dimension;
    SelectModelStatic::SetSpace(select, optionValue);
    EXPECT_EQ(rowProps->GetSpaceValue(Dimension()).Value(), 1);
}

/**
 * @tc.name: SetValue
 * @tc.desc: Test SelectPattern SetValue.
 * @tc.type: FUNC
 */
HWTEST_F(SelectModelStaticTestNg, SetValue, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    /**
     * @tc.steps: step1. Create select.
     */
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto pattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(pattern, nullptr);
    SelectModelStatic::SetValue(select, std::nullopt);
}

/**
 * @tc.name: SetSelected
 * @tc.desc: Test SelectPattern SetSelected.
 * @tc.type: FUNC
 */
HWTEST_F(SelectModelStaticTestNg, SetSelected, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    /**
     * @tc.steps: step1. Create select.
     */
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto pattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(pattern, nullptr);
    SelectModelStatic::SetSelected(select, std::nullopt);
}

/**
 * @tc.name: SetFontSize
 * @tc.desc: Test SelectPattern SetFontSize.
 * @tc.type: FUNC
 */
HWTEST_F(SelectModelStaticTestNg, SetFontSize, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    /**
     * @tc.steps: step1. Create select.
     */
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto pattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(pattern, nullptr);
    SelectModelStatic::SetFontSize(select, std::nullopt);
    auto props = pattern->text_->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(props, nullptr);
    Dimension dimension = Dimension(1, DimensionUnit::FP);
    std::optional<Dimension> optionValue = dimension;
    SelectModelStatic::SetFontSize(select, optionValue);
    EXPECT_EQ(props->GetFontSizeValue(Dimension()).Value(), 1);
}

/**
 * @tc.name: SetFontWeight
 * @tc.desc: Test SelectPattern SetFontWeight.
 * @tc.type: FUNC
 */
HWTEST_F(SelectModelStaticTestNg, SetFontWeight, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    /**
     * @tc.steps: step1. Create select.
     */
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto pattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(pattern, nullptr);
    SelectModelStatic::SetFontWeight(select, std::nullopt);
}

/**
 * @tc.name: SetItalicFontStyle
 * @tc.desc: Test SelectPattern SetItalicFontStyle.
 * @tc.type: FUNC
 */
HWTEST_F(SelectModelStaticTestNg, SetItalicFontStyle, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    /**
     * @tc.steps: step1. Create select.
     */
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto pattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(pattern, nullptr);
    SelectModelStatic::SetItalicFontStyle(select, std::nullopt);
    auto props = pattern->text_->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(props, nullptr);
    Ace::FontStyle fontStyle = Ace::FontStyle::ITALIC;
    std::optional<Ace::FontStyle> optionValue = fontStyle;
    SelectModelStatic::SetItalicFontStyle(select, optionValue);
    EXPECT_EQ(props->GetItalicFontStyleValue(Ace::FontStyle::NORMAL), Ace::FontStyle::ITALIC);
}

/**
 * @tc.name: SetFontColor
 * @tc.desc: Test SelectPattern SetFontColor.
 * @tc.type: FUNC
 */
HWTEST_F(SelectModelStaticTestNg, SetFontColor, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    /**
     * @tc.steps: step1. Create select.
     */
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto pattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(pattern, nullptr);
    SelectModelStatic::SetFontColor(select, std::nullopt);
    EXPECT_FALSE(pattern->fontColor_.has_value());
    std::optional<Color> optionValue = Color::RED;
    SelectModelStatic::SetFontColor(select, optionValue);
    ASSERT_TRUE(pattern->fontColor_.has_value());
    EXPECT_EQ(pattern->fontColor_.value(), Color::RED);
}

/**
 * @tc.name: SetSelectedOptionBgColor
 * @tc.desc: Test SelectPattern SetSelectedOptionBgColor.
 * @tc.type: FUNC
 */
HWTEST_F(SelectModelStaticTestNg, SetSelectedOptionBgColor, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    /**
     * @tc.steps: step1. Create select.
     */
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto pattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(pattern, nullptr);
    SelectModelStatic::SetSelectedOptionBgColor(select, std::nullopt);
    std::optional<Color> optionValue = Color::RED;
    SelectModelStatic::SetSelectedOptionBgColor(select, optionValue);
    ASSERT_TRUE(pattern->selectedBgColor_.has_value());
    EXPECT_EQ(pattern->selectedBgColor_.value(), Color::RED);
}

/**
 * @tc.name: SetOptionFontSize
 * @tc.desc: Test SelectPattern SetOptionFontSize.
 * @tc.type: FUNC
 */
HWTEST_F(SelectModelStaticTestNg, SetOptionFontSize, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    /**
     * @tc.steps: step1. Create select.
     */
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto pattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(pattern, nullptr);
    SelectModelStatic::SetOptionFontSize(select, std::nullopt);
    Dimension dimension = Dimension(1, DimensionUnit::FP);
    std::optional<Dimension> optionValue = dimension;
    SelectModelStatic::SetOptionFontSize(select, optionValue);
    ASSERT_TRUE(pattern->optionFont_.FontSize.has_value());
    EXPECT_EQ(pattern->optionFont_.FontSize.value().Value(), 1);
}

/**
 * @tc.name: SetOptionFontWeight
 * @tc.desc: Test SelectPattern SetOptionFontWeight.
 * @tc.type: FUNC
 */
HWTEST_F(SelectModelStaticTestNg, SetOptionFontWeight, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    /**
     * @tc.steps: step1. Create select.
     */
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto pattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(pattern, nullptr);
    SelectModelStatic::SetOptionFontWeight(select, std::nullopt);
}

/**
 * @tc.name: SetOptionItalicFontStyle
 * @tc.desc: Test SelectPattern SetOptionItalicFontStyle.
 * @tc.type: FUNC
 */
HWTEST_F(SelectModelStaticTestNg, SetOptionItalicFontStyle, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    /**
     * @tc.steps: step1. Create select.
     */
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto pattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(pattern, nullptr);
    SelectModelStatic::SetOptionItalicFontStyle(select, std::nullopt);
    Ace::FontStyle fontStyle = Ace::FontStyle::ITALIC;
    std::optional<Ace::FontStyle> optionValue = fontStyle;
    SelectModelStatic::SetOptionItalicFontStyle(select, optionValue);
    ASSERT_TRUE(pattern->optionFont_.FontStyle.has_value());
    EXPECT_EQ(pattern->optionFont_.FontStyle.value(), Ace::FontStyle::ITALIC);
}

/**
 * @tc.name: SetOptionBgColor
 * @tc.desc: Test SelectPattern SetOptionBgColor.
 * @tc.type: FUNC
 */
HWTEST_F(SelectModelStaticTestNg, SetOptionBgColor, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    /**
     * @tc.steps: step1. Create select.
     */
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto pattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(pattern, nullptr);
    SelectModelStatic::SetOptionBgColor(select, std::nullopt);
    std::optional<Color> optionValue = Color::RED;
    SelectModelStatic::SetOptionBgColor(select, optionValue);
    ASSERT_TRUE(pattern->optionBgColor_.has_value());
    EXPECT_EQ(pattern->optionBgColor_.value(), Color::RED);
}

/**
 * @tc.name: SetSelectedOptionFontColor
 * @tc.desc: Test SelectPattern SetSelectedOptionFontColor.
 * @tc.type: FUNC
 */
HWTEST_F(SelectModelStaticTestNg, SetSelectedOptionFontColor, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    /**
     * @tc.steps: step1. Create select.
     */
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto pattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(pattern, nullptr);
    SelectModelStatic::SetSelectedOptionFontColor(select, std::nullopt);
    std::optional<Color> optionValue = Color::RED;
    SelectModelStatic::SetSelectedOptionFontColor(select, optionValue);
    ASSERT_TRUE(pattern->selectedFont_.FontColor.has_value());
    EXPECT_EQ(pattern->selectedFont_.FontColor.value(), Color::RED);
}

/**
 * @tc.name: SetSelectedOptionFontSize
 * @tc.desc: Test SelectPattern SetSelectedOptionFontSize.
 * @tc.type: FUNC
 */
HWTEST_F(SelectModelStaticTestNg, SetSelectedOptionFontSize, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    /**
     * @tc.steps: step1. Create select.
     */
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto pattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(pattern, nullptr);
    SelectModelStatic::SetSelectedOptionFontSize(select, std::nullopt);
    Dimension dimension = Dimension(1, DimensionUnit::FP);
    std::optional<Dimension> optionValue = dimension;
    SelectModelStatic::SetSelectedOptionFontSize(select, optionValue);
    ASSERT_TRUE(pattern->selectedFont_.FontSize.has_value());
    EXPECT_EQ(pattern->selectedFont_.FontSize.value().Value(), 1);
}

/**
 * @tc.name: SetSelectedOptionFontWeight
 * @tc.desc: Test SelectPattern SetSelectedOptionFontWeight.
 * @tc.type: FUNC
 */
HWTEST_F(SelectModelStaticTestNg, SetSelectedOptionFontWeight, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    /**
     * @tc.steps: step1. Create select.
     */
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto pattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(pattern, nullptr);
    SelectModelStatic::SetSelectedOptionFontWeight(select, std::nullopt);
}

/**
 * @tc.name: SetSelectedOptionItalicFontStyle
 * @tc.desc: Test SelectPattern SetSelectedOptionItalicFontStyle.
 * @tc.type: FUNC
 */
HWTEST_F(SelectModelStaticTestNg, SetSelectedOptionItalicFontStyle, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    /**
     * @tc.steps: step1. Create select.
     */
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto pattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(pattern, nullptr);
    SelectModelStatic::SetSelectedOptionItalicFontStyle(select, std::nullopt);
    Ace::FontStyle fontStyle = Ace::FontStyle::ITALIC;
    std::optional<Ace::FontStyle> optionValue = fontStyle;
    SelectModelStatic::SetSelectedOptionItalicFontStyle(select, optionValue);
    ASSERT_TRUE(pattern->selectedFont_.FontStyle.has_value());
    EXPECT_EQ(pattern->selectedFont_.FontStyle.value(), Ace::FontStyle::ITALIC);
}

/**
 * @tc.name: SetOptionFontColor
 * @tc.desc: Test SelectPattern SetOptionFontColor.
 * @tc.type: FUNC
 */
HWTEST_F(SelectModelStaticTestNg, SetOptionFontColor, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    /**
     * @tc.steps: step1. Create select.
     */
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto pattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(pattern, nullptr);
    SelectModelStatic::SetOptionFontColor(select, std::nullopt);
    std::optional<Color> optionValue = Color::RED;
    SelectModelStatic::SetOptionFontColor(select, optionValue);
    ASSERT_TRUE(pattern->optionFont_.FontColor.has_value());
    EXPECT_EQ(pattern->optionFont_.FontColor.value(), Color::RED);
}

/**
 * @tc.name: SetOptionWidth
 * @tc.desc: Test SelectPattern SetOptionWidth.
 * @tc.type: FUNC
 */
HWTEST_F(SelectModelStaticTestNg, SetOptionWidth, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    /**
     * @tc.steps: step1. Create select.
     */
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto pattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(pattern, nullptr);
    SelectModelStatic::SetOptionWidth(select, std::nullopt);
}

/**
 * @tc.name: SetOptionHeight
 * @tc.desc: Test SelectPattern SetOptionHeight.
 * @tc.type: FUNC
 */
HWTEST_F(SelectModelStaticTestNg, SetOptionHeight, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    /**
     * @tc.steps: step1. Create select.
     */
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto pattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(pattern, nullptr);
    SelectModelStatic::SetOptionHeight(select, std::nullopt);
    Dimension dimension = Dimension(1, DimensionUnit::VP);
    std::optional<Dimension> optionValue = dimension;
    SelectModelStatic::SetOptionHeight(select, optionValue);
    auto menu = pattern->GetMenuNode();
    ASSERT_NE(menu, nullptr);
    auto menuLayoutProps = menu->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(menuLayoutProps, nullptr);
    ASSERT_TRUE(menuLayoutProps->HasSelectModifiedHeight());
    EXPECT_EQ(menuLayoutProps->GetSelectModifiedHeightValue(0.0f), dimension.ConvertToPx());
}

/**
 * @tc.name: SetOptionWidthFitTrigger
 * @tc.desc: Test SelectPattern SetOptionWidthFitTrigger.
 * @tc.type: FUNC
 */
HWTEST_F(SelectModelStaticTestNg, SetOptionWidthFitTrigger, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    /**
     * @tc.steps: step1. Create select.
     */
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto pattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(pattern, nullptr);
    SelectModelStatic::SetOptionWidthFitTrigger(select, std::nullopt);
    std::optional<bool> optionValue = true;
    SelectModelStatic::SetOptionWidthFitTrigger(select, optionValue);
    EXPECT_EQ(pattern->isFitTrigger_, true);
}

/**
 * @tc.name: SetMenuBackgroundColor
 * @tc.desc: Test SelectPattern SetMenuBackgroundColor.
 * @tc.type: FUNC
 */
HWTEST_F(SelectModelStaticTestNg, SetMenuBackgroundColor, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    /**
     * @tc.steps: step1. Create select.
     */
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto pattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(pattern, nullptr);
    SelectModelStatic::SetMenuBackgroundColor(select, std::nullopt);
}

/**
 * @tc.name: SetSelectChangeEvent
 * @tc.desc: Test SelectPattern SetSelectChangeEvent.
 * @tc.type: FUNC
 */
HWTEST_F(SelectModelStaticTestNg, SetSelectChangeEvent, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    /**
     * @tc.steps: step1. Create select.
     */
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto pattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(pattern, nullptr);
    SelectModelStatic::SetSelectChangeEvent(select, nullptr);
}

/**
 * @tc.name: SetValueChangeEvent
 * @tc.desc: Test SelectPattern SetValueChangeEvent.
 * @tc.type: FUNC
 */
HWTEST_F(SelectModelStaticTestNg, SetValueChangeEvent, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    /**
     * @tc.steps: step1. Create select.
     */
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto pattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(pattern, nullptr);
    SelectModelStatic::SetValueChangeEvent(select, nullptr);
}

/**
 * @tc.name: SetDividerStyle
 * @tc.desc: Test SelectPattern SetDividerStyle.
 * @tc.type: FUNC
 */
HWTEST_F(SelectModelStaticTestNg, SetDividerStyle, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    /**
     * @tc.steps: step1. Create select.
     */
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto pattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(pattern->options_.size(), 0);
    auto option = pattern->options_[0];
    ASSERT_NE(option, nullptr);
    auto paintProperty = option->GetPaintProperty<MenuItemPaintProperty>();
    EXPECT_EQ(paintProperty->GetDivider(), std::nullopt);
    SelectModelStatic::SetDividerStyle(select, std::nullopt, std::nullopt);
    NG::SelectDivider divider = SelectModelStatic::GetDefaultDivider(select);
    divider.color = Color::RED;
    std::optional<NG::SelectDivider> dividerOption = divider;
    SelectModelStatic::SetDividerStyle(select, dividerOption, std::nullopt);
    EXPECT_NE(paintProperty->GetDivider(), std::nullopt);
    EXPECT_EQ(paintProperty->GetDividerValue().color, Color::RED);
}

/**
 * @tc.name: SetMenuOutline
 * @tc.desc: Test SelectPattern SetMenuOutline.
 * @tc.type: FUNC
 */
HWTEST_F(SelectModelStaticTestNg, SetMenuOutline, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    /**
     * @tc.steps: step1. Create select.
     */
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto pattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(pattern, nullptr);
    SelectModelStatic::SetMenuOutline(select, std::nullopt);
}

/**
 * @tc.name: SetControlSize
 * @tc.desc: Test SelectPattern SetControlSize.
 * @tc.type: FUNC
 */
HWTEST_F(SelectModelStaticTestNg, SetControlSize, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    /**
     * @tc.steps: step1. Create select.
     */
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto pattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(pattern, nullptr);
    SelectModelStatic::SetControlSize(select, std::nullopt);
    std::optional<ControlSize> optionValue = ControlSize::SMALL;
    int32_t setApiVersion = 12;
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    SelectModelStatic::SetControlSize(select, optionValue);
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
    EXPECT_EQ(pattern->controlSize_, ControlSize::SMALL);
    ViewStackProcessor::GetInstance()->ClearStack();
}
} // namespace OHOS::Ace::NG