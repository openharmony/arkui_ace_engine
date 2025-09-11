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
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/common/ace_application_info.h"
#include "core/common/ace_engine.h"
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
#include "core/components_ng/pattern/menu/menu_item/menu_item_pattern.h"
#include "core/components_ng/pattern/menu/menu_layout_property.h"
#include "core/components_ng/pattern/menu/menu_paint_property.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_layout_property.h"
#include "core/components_ng/pattern/select/select_model_ng.h"
#include "core/components_ng/pattern/select/select_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/components_ng/syntax/lazy_for_each_model.h"
#include "core/components_ng/syntax/lazy_for_each_node.h"
#include "core/components_ng/syntax/lazy_layout_wrapper_builder.h"

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

class SelectControlSizeNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
    RefPtr<FrameNode> frameNode_;
    RefPtr<SelectPattern> selectPattern_;

protected:
    static RefPtr<FrameNode> SelectPropertyConfig(SelectModelNG instance, const std::vector<SelectParam>& value,
        const TestProperty& test);
};

void SelectControlSizeNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
}

void SelectControlSizeNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

void SelectControlSizeNg::SetUp()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    MockContainer::SetUp();
}

void SelectControlSizeNg::TearDown()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
    frameNode_ = nullptr;
    selectPattern_ = nullptr;
}

RefPtr<FrameNode> SelectControlSizeNg::SelectPropertyConfig(SelectModelNG instance,
    const std::vector<SelectParam>& value, const TestProperty& test)
{
    if (test.FontSize.has_value()) {
        instance.SetFontSize(test.FontSize.value());
    }
    if (test.FontColor.has_value()) {
        instance.SetFontColor(test.FontColor.value());
    }
    if (test.FontStyle.has_value()) {
        instance.SetItalicFontStyle(test.FontStyle.value());
    }
    if (test.FontWeight.has_value()) {
        instance.SetFontWeight(test.FontWeight.value());
    }
    if (test.FontFamily.has_value()) {
        instance.SetFontFamily(test.FontFamily.value());
    }

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    return AceType::DynamicCast<FrameNode>(element);
}

/**
 * @tc.name: SetControlSize001
 * @tc.desc: Test SelectPattern ControlSize.
 * @tc.type: FUNC
 */
HWTEST_F(SelectControlSizeNg, SetControlSize001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model, select frame node and select pattern.
     * @tc.expected: Objects are created successfully.
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE }, { OPTION_TEXT_2, INTERNAL_SOURCE },
        { OPTION_TEXT_3, INTERNAL_SOURCE } };
    selectModelInstance.Create(params);

    TestProperty testProperty;
    testProperty.FontSize = std::make_optional(FONT_SIZE_VALUE);
    testProperty.FontStyle = std::make_optional(ITALIC_FONT_STYLE_VALUE);
    testProperty.FontWeight = std::make_optional(FONT_WEIGHT_VALUE);
    testProperty.FontColor = std::make_optional(TEXT_COLOR_VALUE);
    testProperty.FontFamily = std::make_optional(FONT_FAMILY_VALUE);
    auto frameNode = SelectPropertyConfig(selectModelInstance, CREATE_VALUE, testProperty);
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
 * @tc.desc: Test SelectPattern ControlSize.
 * @tc.type: FUNC
 */
HWTEST_F(SelectControlSizeNg, SetControlSize002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model, select frame node and select pattern.
     * @tc.expected: Objects are created successfully.
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE }, { OPTION_TEXT_2, INTERNAL_SOURCE },
        { OPTION_TEXT_3, INTERNAL_SOURCE } };
    selectModelInstance.Create(params);

    auto selectFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(selectFrameNode, nullptr);
    auto selectPattern = selectFrameNode->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);

    /**
     * @tc.steps: step2. Call SetControlSize and set ControlSize,
     * compare the set value with the ControlSize::SMALL.
     * @tc.expected: SelectPattern's ControlSize and the set value are equal. Restore the default value.
     */
    auto backupControlSize = selectPattern->GetControlSize();
    auto settingControlSize = ControlSize::SMALL;
    selectModelInstance.SetControlSize(settingControlSize);
    EXPECT_EQ(selectPattern->GetControlSize(), ControlSize::NORMAL);
    selectModelInstance.SetControlSize(backupControlSize);
    EXPECT_EQ(selectPattern->GetControlSize(), backupControlSize);
}

/**
 * @tc.name: SetControlSize003
 * @tc.desc: Test SelectPattern ControlSize.
 * @tc.type: FUNC
 */
HWTEST_F(SelectControlSizeNg, SetControlSize003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model, select frame node and select pattern.
     * @tc.expected: Objects are created successfully.
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE }, { OPTION_TEXT_2, INTERNAL_SOURCE },
        { OPTION_TEXT_3, INTERNAL_SOURCE } };
    selectModelInstance.Create(params);

    auto selectFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(selectFrameNode, nullptr);
    auto selectPattern = selectFrameNode->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);

    /**
     * @tc.steps: step2. Call SetControlSize and set ControlSize,
     * compare the set value with the ControlSize::NORMAL.
     * @tc.expected: SelectPattern's ControlSize and the set value are equal. Restore the default value.
     */
    auto backupControlSize = selectPattern->GetControlSize();
    auto settingControlSize = ControlSize::NORMAL;
    selectModelInstance.SetControlSize(settingControlSize);
    EXPECT_EQ(selectPattern->GetControlSize(), settingControlSize);
    selectModelInstance.SetControlSize(backupControlSize);
    EXPECT_EQ(selectPattern->GetControlSize(), backupControlSize);
}

/**
 * @tc.name: SetControlSize004
 * @tc.desc: Test SelectPattern ControlSize.
 * @tc.type: FUNC
 */
HWTEST_F(SelectControlSizeNg, SetControlSize004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model, select frame node and select pattern.
     * @tc.expected: Objects are created successfully.
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE }, { OPTION_TEXT_2, INTERNAL_SOURCE },
        { OPTION_TEXT_3, INTERNAL_SOURCE } };
    selectModelInstance.Create(params);

    auto selectFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(selectFrameNode, nullptr);
    auto selectPattern = selectFrameNode->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);

    /**
     * @tc.steps: step2. Call SetControlSize and set ControlSize with invalid value,
     * compare the set value with the ControlSize.
     * @tc.expected: SelectPattern's ControlSize and the set value are equal. Restore the default value.
     */
    auto backupControlSize = selectPattern->GetControlSize();
    auto settingControlSize = (OHOS::Ace::ControlSize)2; // invalid value
    selectModelInstance.SetControlSize(settingControlSize);
    EXPECT_EQ(selectPattern->GetControlSize(), ControlSize::NORMAL);
    selectModelInstance.SetControlSize(backupControlSize);
    EXPECT_EQ(selectPattern->GetControlSize(), backupControlSize);
}

/**
 * @tc.name: SetControlSize005
 * @tc.desc: Test SelectPattern ControlSize.
 * @tc.type: FUNC
 */
HWTEST_F(SelectControlSizeNg, SetControlSize005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model, select frame node and select pattern.
     * @tc.expected: Objects are created successfully.
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE }, { OPTION_TEXT_2, INTERNAL_SOURCE },
        { OPTION_TEXT_3, INTERNAL_SOURCE } };
    selectModelInstance.Create(params);

    auto selectFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(selectFrameNode, nullptr);
    auto selectPattern = selectFrameNode->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);

    /**
     * @tc.steps: step2. Call SetControlSize and set ControlSize with invalid value,
     * compare the set value with the ControlSize.
     * @tc.expected: SelectPattern's ControlSize and the set value are equal. Restore the default value.
     */
    auto backupControlSize = selectPattern->GetControlSize();
    auto settingControlSize = (OHOS::Ace::ControlSize)-1; // invalid value
    selectModelInstance.SetControlSize(settingControlSize);
    EXPECT_EQ(selectPattern->GetControlSize(), ControlSize::NORMAL);
    selectModelInstance.SetControlSize(backupControlSize);
    EXPECT_EQ(selectPattern->GetControlSize(), backupControlSize);
}

/**
 * @tc.name: SetControlSize006
 * @tc.desc: Test SelectPattern ControlSize.
 * @tc.type: FUNC
 */
HWTEST_F(SelectControlSizeNg, SetControlSize006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model, select frame node and select pattern.
     * @tc.expected: Objects are created successfully.
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE }, { OPTION_TEXT_2, INTERNAL_SOURCE },
        { OPTION_TEXT_3, INTERNAL_SOURCE } };
    selectModelInstance.Create(params);

    auto selectFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(selectFrameNode, nullptr);
    auto selectPattern = selectFrameNode->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);

    /**
     * @tc.steps: step2. Call SetControlSize and set ControlSize witch empty value,
     * compare the set value with the ControlSize.
     * @tc.expected: SelectPattern's ControlSize and the set value are equal.
     */
    auto backupControlSize = selectPattern->GetControlSize();
    int32_t setApiVersion = 11;
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    selectModelInstance.SetControlSize({}); // empty
    EXPECT_EQ(selectPattern->GetControlSize(), backupControlSize);
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: SetControlSize007
 * @tc.desc: Test SelectPattern ControlSize.
 * @tc.type: FUNC
 */
HWTEST_F(SelectControlSizeNg, SetControlSize007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model, select frame node and select pattern.
     * @tc.expected: Objects are created successfully.
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE }, { OPTION_TEXT_2, INTERNAL_SOURCE },
        { OPTION_TEXT_3, INTERNAL_SOURCE } };
    selectModelInstance.Create(params);

    auto selectFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(selectFrameNode, nullptr);
    auto selectPattern = selectFrameNode->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);

    /**
     * @tc.steps: step2. Call SetControlSize and set ControlSize,
     * compare the set value with the ControlSize::SMALL.
     * @tc.expected: SelectPattern's ControlSize and the set value are equal. Restore the default value.
     */
    auto backupControlSize = selectPattern->GetControlSize();
    auto settingControlSize = ControlSize::SMALL;
    SelectModelNG::SetControlSize(selectFrameNode, settingControlSize);
    EXPECT_EQ(selectPattern->GetControlSize(), ControlSize::NORMAL);
    SelectModelNG::SetControlSize(selectFrameNode, backupControlSize);
    EXPECT_EQ(selectPattern->GetControlSize(), backupControlSize);
}

/**
 * @tc.name: SetControlSize008
 * @tc.desc: Test SelectPattern ControlSize.
 * @tc.type: FUNC
 */
HWTEST_F(SelectControlSizeNg, SetControlSize008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model, select frame node and select pattern.
     * @tc.expected: Objects are created successfully.
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE }, { OPTION_TEXT_2, INTERNAL_SOURCE },
        { OPTION_TEXT_3, INTERNAL_SOURCE } };
    selectModelInstance.Create(params);

    auto selectFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(selectFrameNode, nullptr);
    auto selectPattern = selectFrameNode->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);

    /**
     * @tc.steps: step2. Call SetControlSize and set ControlSize,
     * compare the set value with the ControlSize::NORMAL.
     * @tc.expected: SelectPattern's ControlSize and the set value are equal. Restore the default value.
     */
    auto backupControlSize = selectPattern->GetControlSize();
    auto settingControlSize = ControlSize::NORMAL;
    SelectModelNG::SetControlSize(selectFrameNode, settingControlSize);
    EXPECT_EQ(selectPattern->GetControlSize(), settingControlSize);
    SelectModelNG::SetControlSize(selectFrameNode, backupControlSize);
    EXPECT_EQ(selectPattern->GetControlSize(), backupControlSize);
}

/**
 * @tc.name: SetControlSize009
 * @tc.desc: Test SelectPattern ControlSize.
 * @tc.type: FUNC
 */
HWTEST_F(SelectControlSizeNg, SetControlSize009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model, select frame node and select pattern.
     * @tc.expected: Objects are created successfully.
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE }, { OPTION_TEXT_2, INTERNAL_SOURCE },
        { OPTION_TEXT_3, INTERNAL_SOURCE } };
    selectModelInstance.Create(params);

    auto selectFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(selectFrameNode, nullptr);
    auto selectPattern = selectFrameNode->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);

    /**
     * @tc.steps: step2. Call SetControlSize and set ControlSize with invalid value,
     * compare the set value with the ControlSize.
     * @tc.expected: SelectPattern's ControlSize and the set value are equal. Restore the default value.
     */
    auto backupControlSize = selectPattern->GetControlSize();
    auto settingControlSize = (OHOS::Ace::ControlSize)2; // invalid value
    SelectModelNG::SetControlSize(selectFrameNode, settingControlSize);
    EXPECT_EQ(selectPattern->GetControlSize(), ControlSize::NORMAL);
    SelectModelNG::SetControlSize(selectFrameNode, backupControlSize);
    EXPECT_EQ(selectPattern->GetControlSize(), backupControlSize);
}

/**
 * @tc.name: SetControlSize010
 * @tc.desc: Test SelectPattern ControlSize.
 * @tc.type: FUNC
 */
HWTEST_F(SelectControlSizeNg, SetControlSize010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model, select frame node and select pattern.
     * @tc.expected: Objects are created successfully.
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE }, { OPTION_TEXT_2, INTERNAL_SOURCE },
        { OPTION_TEXT_3, INTERNAL_SOURCE } };
    selectModelInstance.Create(params);

    auto selectFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(selectFrameNode, nullptr);
    auto selectPattern = selectFrameNode->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);

    /**
     * @tc.steps: step2. Call SetControlSize and set ControlSize with invalid value,
     * compare the set value with the ControlSize.
     * @tc.expected: SelectPattern's ControlSize and the set value are equal. Restore the default value.
     */
    auto backupControlSize = selectPattern->GetControlSize();
    auto settingControlSize = (OHOS::Ace::ControlSize)-1; // invalid value
    SelectModelNG::SetControlSize(selectFrameNode, settingControlSize);
    EXPECT_EQ(selectPattern->GetControlSize(), ControlSize::NORMAL);
    SelectModelNG::SetControlSize(selectFrameNode, std::nullopt);
    EXPECT_EQ(selectPattern->GetControlSize(), backupControlSize);
}

/**
 * @tc.name: SetShowInSubWindow001
 * @tc.desc: Test SelectPattern SetShowInSubWindow.
 * @tc.type: FUNC
 */
HWTEST_F(SelectControlSizeNg, SetShowInSubWindow001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model, select frame node and select pattern.
     * @tc.expected: Objects are created successfully.
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE }, { OPTION_TEXT_2, INTERNAL_SOURCE },
        { OPTION_TEXT_3, INTERNAL_SOURCE } };
    selectModelInstance.Create(params);

    auto viewStackProcessor = ViewStackProcessor::GetInstance();
    ASSERT_NE(viewStackProcessor, nullptr);
    auto selectFrameNode = viewStackProcessor->GetMainFrameNode();
    ASSERT_NE(selectFrameNode, nullptr);
    auto selectLayoutProps = selectFrameNode->GetLayoutProperty<SelectLayoutProperty>();
    ASSERT_NE(selectLayoutProps, nullptr);

    /**
     * @tc.steps: step2. Call SetShowInSubWindow and set SetShowInSubWindow with bool value.
     * @tc.expected: SelectLayoutProperty's isShowInSubWindow_ and the set value are equal.
     */
    EXPECT_EQ(selectLayoutProps->GetShowInSubWindowValue(false), false);
    SelectModelNG::SetShowInSubWindow(selectFrameNode, true);
    EXPECT_EQ(selectLayoutProps->GetShowInSubWindowValue(false), true);
    SelectModelNG::SetShowInSubWindow(selectFrameNode, false);
    EXPECT_EQ(selectLayoutProps->GetShowInSubWindowValue(false), false);
}

/**
 * @tc.name: ResetShowInSubWindow001
 * @tc.desc: Test SelectPattern ResetShowInSubWindow.
 * @tc.type: FUNC
 */
HWTEST_F(SelectControlSizeNg, ResetShowInSubWindow001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model, select frame node and select pattern.
     * @tc.expected: Objects are created successfully.
     */
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto themeManager = AceType::DynamicCast<MockThemeManager>(pipeline->GetThemeManager());
    ASSERT_NE(themeManager, nullptr);
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillRepeatedly(Return(selectTheme));

    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE }, { OPTION_TEXT_2, INTERNAL_SOURCE },
        { OPTION_TEXT_3, INTERNAL_SOURCE } };
    selectModelInstance.Create(params);

    auto viewStackProcessor = ViewStackProcessor::GetInstance();
    ASSERT_NE(viewStackProcessor, nullptr);
    auto selectFrameNode = viewStackProcessor->GetMainFrameNode();
    ASSERT_NE(selectFrameNode, nullptr);
    auto selectPattern = selectFrameNode->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto selectLayoutProps = selectFrameNode->GetLayoutProperty<SelectLayoutProperty>();
    ASSERT_NE(selectLayoutProps, nullptr);

    MockContainer::SetUp();
    auto container = AceType::DynamicCast<MockContainer>(Container::Current());
    ASSERT_NE(container, nullptr);
    AceEngine::Get().AddContainer(Container::CurrentId(), container);

    /**
     * @tc.steps: step2. Call ResetShowInSubWindow.
     * @tc.expected: SelectLayoutProperty's isShowInSubWindow_ and the set value are equal.
     */
    ASSERT_NE(selectTheme, nullptr);
    selectTheme->expandDisplay_ = true;
    selectPattern->ResetShowInSubWindow();
    EXPECT_EQ(selectLayoutProps->GetShowInSubWindowValue(false), true);
    selectTheme->expandDisplay_ = false;
    selectPattern->ResetShowInSubWindow();
    EXPECT_EQ(selectLayoutProps->GetShowInSubWindowValue(false), false);

    AceEngine::Get().RemoveContainer(Container::CurrentId());
}

/**
 * @tc.name: OnColorConfigurationUpdateTest001
 * @tc.desc: Test OnColorConfigurationUpdate when ConfigChangePerform is false.
 * @tc.type: FUNC
 */
HWTEST_F(SelectControlSizeNg, OnColorConfigurationUpdateTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set up test conditions.
     * - SystemProperties::ConfigChangePerform() must return false to enter the target branch.
     * - Mock the theme to provide a specific background color.
     */
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto themeManager = AceType::DynamicCast<MockThemeManager>(pipeline->GetThemeManager());
    ASSERT_NE(themeManager, nullptr);
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    const Color themeBgColor = Color::BLUE;
    selectTheme->backgroundColor_ = themeBgColor;
    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillRepeatedly(Return(selectTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly(Return(selectTheme));

    /**
     * @tc.steps: step2. Create a Select component with options.
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE }, { OPTION_TEXT_2, INTERNAL_SOURCE },
        { OPTION_TEXT_3, INTERNAL_SOURCE } };
    selectModelInstance.Create(params);

    auto viewStackProcessor = ViewStackProcessor::GetInstance();
    ASSERT_NE(viewStackProcessor, nullptr);
    auto frameNode = viewStackProcessor->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto selectLayoutProps = frameNode->GetLayoutProperty<SelectLayoutProperty>();
    ASSERT_NE(selectLayoutProps, nullptr);
    auto pattern = frameNode->GetPattern<SelectPattern>();
    ASSERT_NE(pattern, nullptr);
    ASSERT_FALSE(pattern->GetOptions().empty());
    auto menuNode = pattern->GetMenuNode();
    ASSERT_NE(menuNode, nullptr);
    
    auto menuRenderContext = menuNode->GetRenderContext();
    ASSERT_NE(menuRenderContext, nullptr);
    menuRenderContext->UpdateBackgroundColor(Color::BLACK);
    auto firstOption = pattern->GetOptions().front();
    ASSERT_NE(firstOption, nullptr);
    auto optionPaintProperty = firstOption->GetPaintProperty<MenuItemPaintProperty>();
    ASSERT_NE(optionPaintProperty, nullptr);
    optionPaintProperty->UpdateOptionBgColor(Color::BLACK);

    /**
     * @tc.steps: step3. Call the function under test.
     */
    pattern->OnColorConfigurationUpdate();

    /**
     * @tc.steps: step4. Verify that the menu's background color and option's background color were updated.
     */
    EXPECT_EQ(menuRenderContext->GetBackgroundColorValue(Color::RED), themeBgColor);
    EXPECT_EQ(optionPaintProperty->GetOptionBgColorValue(Color::RED), themeBgColor);
    ViewStackProcessor::GetInstance()->ClearStack();
}

/**
 * @tc.name: SetShowDefaultSelectedIcon001
 * @tc.desc: Test SelectPattern SetShowDefaultSelectedIcon.
 * @tc.type: FUNC
 */
HWTEST_F(SelectControlSizeNg, SetShowDefaultSelectedIcon001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model, select frame node and select pattern.
     * @tc.expected: Objects are created successfully.
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE }, { OPTION_TEXT_2, INTERNAL_SOURCE },
        { OPTION_TEXT_3, INTERNAL_SOURCE } };
    selectModelInstance.Create(params);

    auto viewStackProcessor = ViewStackProcessor::GetInstance();
    ASSERT_NE(viewStackProcessor, nullptr);
    auto selectFrameNode = viewStackProcessor->GetMainFrameNode();
    ASSERT_NE(selectFrameNode, nullptr);
    auto selectLayoutProps = selectFrameNode->GetLayoutProperty<SelectLayoutProperty>();
    ASSERT_NE(selectLayoutProps, nullptr);

    /**
     * @tc.steps: step2. Call SetShowDefaultSelectedIcon and set SetShowDefaultSelectedIcon with bool value.
     * @tc.expected: SelectLayoutProperty's isShowInSubWindow_ and the set value are equal.
     */
    EXPECT_EQ(selectLayoutProps->GetShowDefaultSelectedIconValue(false), false);
    SelectModelNG::SetShowDefaultSelectedIcon(selectFrameNode, true);
    EXPECT_EQ(selectLayoutProps->GetShowDefaultSelectedIconValue(false), true);
    SelectModelNG::SetShowDefaultSelectedIcon(selectFrameNode, false);
    EXPECT_EQ(selectLayoutProps->GetShowDefaultSelectedIconValue(false), false);
}

/**
 * @tc.name: ResetShowDefaultSelectedIcon001
 * @tc.desc: Test SelectPattern ResetShowDefaultSelectedIcon
 * @tc.type: FUNC
 */
HWTEST_F(SelectControlSizeNg, ResetShowDefaultSelectedIcon001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model, select frame node and select pattern.
     * @tc.expected: Objects are created successfully.
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE }, { OPTION_TEXT_2, INTERNAL_SOURCE },
        { OPTION_TEXT_3, INTERNAL_SOURCE } };
    selectModelInstance.Create(params);

    auto viewStackProcessor = ViewStackProcessor::GetInstance();
    ASSERT_NE(viewStackProcessor, nullptr);
    auto selectFrameNode = viewStackProcessor->GetMainFrameNode();
    ASSERT_NE(selectFrameNode, nullptr);
    auto selectPattern = selectFrameNode->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto selectLayoutProps = selectFrameNode->GetLayoutProperty<SelectLayoutProperty>();
    ASSERT_NE(selectLayoutProps, nullptr);

    /**
     * @tc.steps: step2. Call ResetShowDefaultSelectedIcon
     * @tc.expected: SelectLayoutProperty's isShowInSubWindow_ and the set value are equal.
     */
    selectPattern->ResetShowDefaultSelectedIcon();
    EXPECT_EQ(selectLayoutProps->GetShowDefaultSelectedIconValue(false), false);
}

/**
 * @tc.name: UpdateSelectedProps001
 * @tc.desc: Test SelectPattern UpdateSelectedProps.
 * @tc.type: FUNC
 */
HWTEST_F(SelectControlSizeNg, UpdateSelectedProps001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model, select frame node and select pattern.
     * @tc.expected: Objects are created successfully.
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE }, { OPTION_TEXT_2, INTERNAL_SOURCE },
        { OPTION_TEXT_3, INTERNAL_SOURCE } };
    selectModelInstance.Create(params);

    auto selectFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(selectFrameNode, nullptr);
    auto selectPattern = selectFrameNode->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);

    /**
     * @tc.steps: step2. Call UpdateSelectedProps,
     * @tc.expected: Selected menuitem's properties are right.
     */
    SelectModelNG::SetShowDefaultSelectedIcon(selectFrameNode, true);
    int32_t index = 0;
    selectPattern->UpdateSelectedProps(index);
    auto newSelected = selectPattern->options_[index]->GetPattern<MenuItemPattern>();
    ASSERT_NE(newSelected, nullptr);
    EXPECT_EQ(newSelected->IsSelected(), true);
    auto checkMarkLayoutProps = newSelected->checkMarkNode_->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(checkMarkLayoutProps, nullptr);
    EXPECT_EQ(checkMarkLayoutProps->GetVisibilityValue(VisibleType::INVISIBLE), VisibleType::VISIBLE);
    auto newSelectedNode = newSelected->GetHost();
    ASSERT_NE(newSelectedNode, nullptr);
    auto newSelectedPros = newSelectedNode->GetPaintProperty<MenuItemPaintProperty>();
    ASSERT_NE(newSelectedPros, nullptr);
    EXPECT_EQ(newSelectedPros->GetNeedDividerValue(false), false);

    SelectModelNG::SetShowDefaultSelectedIcon(selectFrameNode, false);
    index = 1;
    selectPattern->UpdateSelectedProps(index);
    newSelected = selectPattern->options_[index]->GetPattern<MenuItemPattern>();
    ASSERT_NE(newSelected, nullptr);
    EXPECT_EQ(newSelected->IsSelected(), true);
    newSelectedNode = newSelected->GetHost();
    ASSERT_NE(newSelectedNode, nullptr);
    newSelectedPros = newSelectedNode->GetPaintProperty<MenuItemPaintProperty>();
    ASSERT_NE(newSelectedPros, nullptr);
    EXPECT_EQ(newSelectedPros->GetNeedDividerValue(false), false);
}

/**
 * @tc.name: UpdateSelectedProps002
 * @tc.desc: Test SelectPattern UpdateSelectedProps.
 * @tc.type: FUNC
 */
HWTEST_F(SelectControlSizeNg, UpdateSelectedProps002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model, select frame node and select pattern.
     * @tc.expected: Objects are created successfully.
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE }, { OPTION_TEXT_2, INTERNAL_SOURCE },
        { OPTION_TEXT_3, INTERNAL_SOURCE } };
    selectModelInstance.Create(params);

    auto selectFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(selectFrameNode, nullptr);
    auto selectPattern = selectFrameNode->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);

    /**
     * @tc.steps: step2. Call UpdateSelectedProps,
     * @tc.expected: Selected menuitem's properties are right.
     */
    SelectModelNG::SetShowDefaultSelectedIcon(selectFrameNode, true);
    int32_t index = 1;
    selectPattern->UpdateSelectedProps(index);
    auto newSelected = selectPattern->options_[index]->GetPattern<MenuItemPattern>();
    ASSERT_NE(newSelected, nullptr);
    EXPECT_EQ(newSelected->IsSelected(), true);
    auto checkMarkLayoutProps = newSelected->checkMarkNode_->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(checkMarkLayoutProps, nullptr);
    EXPECT_EQ(checkMarkLayoutProps->GetVisibilityValue(VisibleType::INVISIBLE), VisibleType::VISIBLE);
    auto newSelectedNode = newSelected->GetHost();
    ASSERT_NE(newSelectedNode, nullptr);
    auto newSelectedPros = newSelectedNode->GetPaintProperty<MenuItemPaintProperty>();
    ASSERT_NE(newSelectedPros, nullptr);
    EXPECT_EQ(newSelectedPros->GetNeedDividerValue(false), true);
}

/**
 * @tc.name: CheckSkipMenuShow001
 * @tc.desc: Test SelectPattern CheckSkipMenuShow.
 * @tc.type: FUNC
 */
HWTEST_F(SelectControlSizeNg, CheckSkipMenuShow001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model, select frame node and select pattern.
     * @tc.expected: Objects are created successfully.
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE }, { OPTION_TEXT_2, INTERNAL_SOURCE },
        { OPTION_TEXT_3, INTERNAL_SOURCE } };
    selectModelInstance.Create(params);

    auto selectFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(selectFrameNode, nullptr);
    auto selectPattern = selectFrameNode->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);

    /**
     * @tc.steps: step2. Call CheckSkipMenuShow with invalid value,
     * @tc.expected: SelectPattern's CheckSkipMenuShow return false with invalid value.
     */

    RefPtr<FrameNode> targetNode = nullptr;
    EXPECT_EQ(selectPattern->CheckSkipMenuShow(targetNode), false);
}
} // namespace OHOS::Ace::NG
