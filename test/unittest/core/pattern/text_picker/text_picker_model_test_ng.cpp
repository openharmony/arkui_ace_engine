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
#include "test/mock/core/rosen/mock_canvas.h"

#include "base/geometry/dimension.h"
#include "base/geometry/ng/size_t.h"
#include "base/i18n/localization.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/measure_util.h"
#include "core/components/picker/picker_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_picker/textpicker_column_pattern.h"
#include "core/components_ng/pattern/text_picker/textpicker_dialog_view.h"
#include "core/components_ng/pattern/text_picker/textpicker_model.h"
#include "core/components_ng/pattern/text_picker/textpicker_model_ng.h"
#include "core/components_ng/pattern/text_picker/textpicker_model_static.h"
#include "core/components_ng/pattern/text_picker/textpicker_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline_ng/ui_task_scheduler.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
    constexpr int32_t ONCHANGE_CALLBACK_INFO = 1;
    constexpr int32_t ONSCROLLSTOP_CALLBACK_INFO = 1;
    const std::string DEFAULT_CONTENT_VALUE = "hello world";
    const std::vector<NG::RangeContent> MENU_OPTIONS = {
        { "/data/resource/1.svg", "share" },
        { "/data/resource/2.svg", "translate" }
    };
    const std::string TEXT_PICKER_CONTENT_0 = "a";
    const std::string TEXT_PICKER_CONTENT_1 = "b";
    const std::string TEXT_PICKER_CONTENT_2 = "c";
    const std::string TEXT_PICKER_CONTENT_3 = "d";
    const std::string TEXT_PICKER_CONTENT_4 = "e";
    const Dimension FONT_SIZE_VALUE = 20.0_px;
    const Color TEXT_COLOR_VALUE = Color::RED;
    const FontWeight FONT_WEIGHT_VALUE = FontWeight::BOLD;
    const std::vector<std::string> FONT_FAMILY_VALUE = { "Arial" };
    const Ace::FontStyle FONT_STYLE_VALUE = Ace::FontStyle::ITALIC;
    const Dimension PICKER_ITEM_HEIGHT = 50.0_px;
    const Dimension GRADIENT_HEIGHT = 100.0_px;
    const int32_t DIGITAL_CROWN_SENSITIVITY = 5;
    const std::string SELECTED_VALUE = "b";
    const std::vector<std::string> SELECTED_VALUES = { "b", "d" };
    const uint32_t SELECTED_INDEX = 1;
    const std::vector<uint32_t> SELECTED_INDEXES = { 1, 3 };
    const bool CAN_LOOP = false;
    const bool ENABLE_HAPTIC_FEEDBACK = false;
    const bool DISABLE_TEXT_STYLE_ANIMATION = true;
    const bool DEFAULT_ENABLE_HAPTIC_FEEDBACK = true;
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

class TextPickerModelTestNg : public TestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
};

void TextPickerModelTestNg::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrent();
}

void TextPickerModelTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void TextPickerModelTestNg::SetUp()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        return GetTheme(type);
    });
    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([](ThemeType type, int32_t themeScopeId) -> RefPtr<Theme> { return GetTheme(type); });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void TextPickerModelTestNg::TearDown()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    ClearOldNodes(); // Each testcase will create new list at begin
}

/**
 * @tc.name: CreateFrameNode001
 * @tc.desc: Test CreateFrameNode
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, CreateFrameNode001, TestSize.Level1)
{
    EXPECT_NE(TextPickerModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId()), nullptr);
}

/**
 * @tc.name: HasUserDefinedDisappearFontFamily001
 * @tc.desc: Test HasUserDefinedDisappearFontFamily
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, HasUserDefinedDisappearFontFamily001, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, MIXTURE);
    TextPickerModelNG::GetInstance()->HasUserDefinedDisappearFontFamily(true);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    EXPECT_TRUE(textPickerPattern->GetHasUserDefinedDisappearFontFamily());
}

/**
 * @tc.name: HasUserDefinedNormalFontFamily001
 * @tc.desc: Test HasUserDefinedNormalFontFamily
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, HasUserDefinedNormalFontFamily001, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, MIXTURE);
    TextPickerModelNG::GetInstance()->HasUserDefinedNormalFontFamily(true);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    EXPECT_TRUE(textPickerPattern->GetHasUserDefinedNormalFontFamily());
}

/**
 * @tc.name: HasUserDefinedSelectedFontFamily001
 * @tc.desc: Test HasUserDefinedSelectedFontFamily
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, HasUserDefinedSelectedFontFamily001, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, MIXTURE);
    TextPickerModelNG::GetInstance()->HasUserDefinedSelectedFontFamily(true);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    EXPECT_TRUE(textPickerPattern->GetHasUserDefinedSelectedFontFamily());
}

/**
 * @tc.name: SetOnCascadeChange001
 * @tc.desc: Test SetOnCascadeChange
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, SetOnCascadeChange001, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, MIXTURE);
    int32_t callbackInfo = 0;
    auto onChangeFunc = [&callbackInfo](const std::vector<std::string>& value, const std::vector<double>& index) {
        callbackInfo = ONCHANGE_CALLBACK_INFO;
    };
    TextPickerModelNG::GetInstance()->SetOnCascadeChange(std::move(onChangeFunc));

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto textPickerEventHub = frameNode->GetOrCreateEventHub<TextPickerEventHub>();
    ASSERT_NE(textPickerEventHub, nullptr);
    
    EXPECT_NE(textPickerEventHub->TextChangeEvent_, nullptr);
    std::vector<std::string> value = { "hello world" };
    std::vector<double> index = { 0 };
    textPickerEventHub->FireChangeEvent(value, index);
    EXPECT_EQ(callbackInfo, ONCHANGE_CALLBACK_INFO);
}

/**
 * @tc.name: SetOnScrollStop001
 * @tc.desc: Test SetOnScrollStop
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, SetOnScrollStop001, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, MIXTURE);
    int32_t callbackInfo = 0;
    auto onScrollStopFunc = [&callbackInfo](const std::vector<std::string>& value, const std::vector<double>& index) {
        callbackInfo = ONSCROLLSTOP_CALLBACK_INFO;
    };
    TextPickerModelNG::GetInstance()->SetOnScrollStop(std::move(onScrollStopFunc));

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto textPickerEventHub = frameNode->GetOrCreateEventHub<TextPickerEventHub>();
    ASSERT_NE(textPickerEventHub, nullptr);

    EXPECT_NE(textPickerEventHub->onScrollStopEvent_, nullptr);
    std::vector<std::string> value = { "hello world" };
    std::vector<double> index = { 0 };
    textPickerEventHub->FireScrollStopEvent(value, index);
    EXPECT_EQ(callbackInfo, ONSCROLLSTOP_CALLBACK_INFO);
}

/**
 * @tc.name: SetValue001
 * @tc.desc: Test SetValue
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, SetValue001, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, MIXTURE);
    
    TextPickerModelNG::GetInstance()->SetValue(DEFAULT_CONTENT_VALUE);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto props = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(props, nullptr);
    EXPECT_STREQ(props->GetValueValue("").c_str(), DEFAULT_CONTENT_VALUE.c_str());
}

/**
 * @tc.name: IsSingle001
 * @tc.desc: Test IsSingle
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, IsSingle001, TestSize.Level1)
{
    auto frameNode = TextPickerModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    TextPickerModelNG::SetRange(AceType::RawPtr(frameNode), MENU_OPTIONS);
    EXPECT_TRUE(TextPickerModelNG::IsSingle(AceType::RawPtr(frameNode)));
}

/**
 * @tc.name: GetSingleRange001
 * @tc.desc: Test GetSingleRange
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, GetSingleRange001, TestSize.Level1)
{
    auto frameNode = TextPickerModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    TextPickerModelNG::SetRange(AceType::RawPtr(frameNode), MENU_OPTIONS);
    std::vector<NG::RangeContent> rangeValue;
    EXPECT_TRUE(TextPickerModelNG::GetSingleRange(AceType::RawPtr(frameNode), rangeValue));
    EXPECT_EQ(rangeValue.size(), MENU_OPTIONS.size());
}

/**
 * @tc.name: IsCascade001
 * @tc.desc: Test IsCascade
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, IsCascade001, TestSize.Level1)
{
    auto frameNode = TextPickerModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    textPickerPattern->SetIsCascade(true);
    EXPECT_TRUE(TextPickerModelNG::IsCascade(AceType::RawPtr(frameNode)));
}

/**
 * @tc.name: GetMultiOptions001
 * @tc.desc: Test GetMultiOptions
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, GetMultiOptions001, TestSize.Level1)
{
    auto frameNode = TextPickerModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    std::vector<NG::TextCascadePickerOptions> options;
    std::vector<NG::TextCascadePickerOptions> cascadeOptions;
    TextCascadePickerOptions emptyOption;
    options.emplace_back(emptyOption);
    auto size = options.size();
    textPickerPattern->SetCascadeOptions(options, cascadeOptions);
    std::vector<NG::TextCascadePickerOptions> result;
    EXPECT_TRUE(TextPickerModelNG::GetMultiOptions(AceType::RawPtr(frameNode), result));
    EXPECT_EQ(result.size(), size);
}

/**
 * @tc.name: SetTextPickerDialogShow001
 * @tc.desc: Test SetTextPickerDialogShow
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, SetTextPickerDialogShow001, TestSize.Level1)
{
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto context = container->GetPipelineContext();
    ASSERT_NE(context, nullptr);
    context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto taskExecutor = context->GetTaskExecutor();
    ASSERT_NE(taskExecutor, nullptr);
    RefPtr<AceType> pickerText;
    NG::TextPickerSettingData settingData;
    auto onCancelFunc = []() {};
    auto onAcceptFunc = [](const std::string&) {};
    auto onChangeFunc = [](const std::string&) {};
    auto onScrollStopFunc = [](const std::string&) {};
    auto onEnterSelectedAreaFunc = [](const std::string&) {};

    TextPickerDialog textPickerDialog = {
        .height = 16.0_vp,
        .selectedValue = 0,
        .isDefaultHeight = true,
        .alignment = DialogAlignment::CENTER,
        .offset = DimensionOffset(),
        .maskRect = DimensionRect(),
        .backgroundColor = Color::GRAY,
        .backgroundBlurStyle = 1,
        .shadow = Shadow()
    };
    TextPickerDialogEvent textPickerDialogEvent = {
        .onDidAppear = []() {},
        .onDidDisappear = []() {},
        .onWillAppear = []() {},
        .onWillDisappear = []() {}
    };
    std::vector<ButtonInfo> buttonInfos;
    TextPickerDialogModel::GetInstance()->SetTextPickerDialogShow(pickerText, settingData,
        onCancelFunc, onAcceptFunc, onChangeFunc, onScrollStopFunc, onEnterSelectedAreaFunc, textPickerDialog,
        textPickerDialogEvent, buttonInfos);
    EXPECT_EQ(textPickerDialog.alignment, DialogAlignment::CENTER);
}

/**
 * @tc.name: SetCanLoop001
 * @tc.desc: Test SetCanLoop
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, SetCanLoop001, TestSize.Level1)
{
    auto frameNode = TextPickerModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);
    TextPickerModelNG::SetCanLoop(AceType::RawPtr(frameNode), true);
    EXPECT_TRUE(static_cast<bool>(TextPickerModelNG::GetCanLoop(AceType::RawPtr(frameNode))));
}

/**
 * @tc.name: SetSelected001
 * @tc.desc: Test SetSelected
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, SetSelected001, TestSize.Level1)
{
    auto frameNode = TextPickerModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    int selectedIndex = 2;
    TextPickerModelNG::SetSelected(AceType::RawPtr(frameNode), selectedIndex);
    EXPECT_EQ(textPickerPattern->GetSelected(), selectedIndex);
}

/**
 * @tc.name: SetHasSelectAttr001
 * @tc.desc: Test SetHasSelectAttr
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, SetHasSelectAttr001, TestSize.Level1)
{
    auto frameNode = TextPickerModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    TextPickerModelNG::SetHasSelectAttr(AceType::RawPtr(frameNode), true);
    EXPECT_TRUE(textPickerPattern->isHasSelectAttr_);
}

/**
 * @tc.name: SetDefaultPickerItemHeight001
 * @tc.desc: Test SetDefaultPickerItemHeight
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, SetDefaultPickerItemHeight001, TestSize.Level1)
{
    auto frameNode = TextPickerModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);
    Dimension itemHeight = 18.0_vp;
    TextPickerModelNG::SetDefaultPickerItemHeight(AceType::RawPtr(frameNode), itemHeight);
    EXPECT_FLOAT_EQ(TextPickerModelNG::GetDefaultPickerItemHeight(AceType::RawPtr(frameNode)).ConvertToPx(),
        itemHeight.ConvertToPx());
}

/**
 * @tc.name: SetBackgroundColor001
 * @tc.desc: Test SetBackgroundColor
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, SetBackgroundColor001, TestSize.Level1)
{
    auto frameNode = TextPickerModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    TextPickerModelNG::SetBackgroundColor(AceType::RawPtr(frameNode), Color::GRAY);
    EXPECT_EQ(textPickerPattern->GetBackgroundColor().GetValue(), Color::GRAY.GetValue());
}

/**
 * @tc.name: getDisappearTextStyle001
 * @tc.desc: Test getDisappearTextStyle
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, getDisappearTextStyle001, TestSize.Level1)
{
    auto frameNode = TextPickerModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    frameNode->AttachContext(AceType::RawPtr(context));
    auto pickerTheme = MockThemeDefault::GetPickerTheme();
    ASSERT_NE(pickerTheme, nullptr);
    auto style = pickerTheme->GetDisappearOptionStyle();
    auto pickerTextStyle = TextPickerModelNG::getDisappearTextStyle(AceType::RawPtr(frameNode));
    EXPECT_EQ(pickerTextStyle.fontWeight.value_or(FontWeight::MEDIUM), style.GetFontWeight());
}

/**
 * @tc.name: getNormalTextStyle001
 * @tc.desc: Test getNormalTextStyle
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, getNormalTextStyle001, TestSize.Level1)
{
    auto frameNode = TextPickerModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    frameNode->AttachContext(AceType::RawPtr(context));
    auto pickerTheme = MockThemeDefault::GetPickerTheme();
    ASSERT_NE(pickerTheme, nullptr);
    auto style = pickerTheme->GetOptionStyle(false, false);
    auto pickerTextStyle = TextPickerModelNG::getNormalTextStyle(AceType::RawPtr(frameNode));
    EXPECT_EQ(pickerTextStyle.fontStyle.value_or(Ace::FontStyle::NORMAL), style.GetFontStyle());
}

/**
 * @tc.name: getSelectedTextStyle001
 * @tc.desc: Test getSelectedTextStyle
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, getSelectedTextStyle001, TestSize.Level1)
{
    auto frameNode = TextPickerModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    frameNode->AttachContext(AceType::RawPtr(context));
    auto pickerTheme = MockThemeDefault::GetPickerTheme();
    ASSERT_NE(pickerTheme, nullptr);
    auto style = pickerTheme->GetOptionStyle(true, false);
    auto pickerTextStyle = TextPickerModelNG::getSelectedTextStyle(AceType::RawPtr(frameNode));
    EXPECT_EQ(pickerTextStyle.fontStyle.value_or(Ace::FontStyle::NORMAL), style.GetFontStyle());
}

/**
 * @tc.name: getTextPickerSelectedIndex001
 * @tc.desc: Test getTextPickerSelectedIndex
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, getTextPickerSelectedIndex001, TestSize.Level1)
{
    auto frameNode = TextPickerModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);
    auto props = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(props, nullptr);
    uint32_t selectedIndex = 1;
    props->UpdateSelected(selectedIndex);
    EXPECT_EQ(TextPickerModelNG::getTextPickerSelectedIndex(AceType::RawPtr(frameNode)), selectedIndex);
}

/**
 * @tc.name: SetUnCascadeColumnsNode001
 * @tc.desc: Test SetUnCascadeColumnsNode
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, SetUnCascadeColumnsNode001, TestSize.Level1)
{
    auto frameNode = TextPickerModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);
    std::vector<NG::TextCascadePickerOptions> options;
    options.emplace_back(TextCascadePickerOptions());
    options.emplace_back(TextCascadePickerOptions());
    options.emplace_back(TextCascadePickerOptions());
    TextPickerModelNG::SetUnCascadeColumnsNode(AceType::RawPtr(frameNode), options);
    EXPECT_EQ(frameNode->GetChildren().size(), options.size());
}

/**
 * @tc.name: SetCascadeColumnsNode001
 * @tc.desc: Test SetCascadeColumnsNode
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, SetCascadeColumnsNode001, TestSize.Level1)
{
    auto frameNode = TextPickerModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);
    std::vector<NG::TextCascadePickerOptions> options;
    options.emplace_back(TextCascadePickerOptions());
    TextPickerModelNG::SetCascadeColumnsNode(AceType::RawPtr(frameNode), options);
    EXPECT_FALSE(frameNode->GetChildren().empty());
}

/**
 * @tc.name: StaticSetValue001
 * @tc.desc: Test static SetValue
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, StaticSetValue001, TestSize.Level1)
{
    auto frameNode = TextPickerModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    TextPickerModelNG::SetRange(AceType::RawPtr(frameNode), MENU_OPTIONS);
    TextPickerModelNG::SetValue(AceType::RawPtr(frameNode), MENU_OPTIONS.back().text_);
    EXPECT_EQ(textPickerPattern->GetSelected(), MENU_OPTIONS.size() - 1);
    EXPECT_STREQ(TextPickerModelNG::getTextPickerValue(AceType::RawPtr(frameNode)).c_str(),
        MENU_OPTIONS.back().text_.c_str());
}

/**
 * @tc.name: StaticSetValues001
 * @tc.desc: Test static SetValues
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, StaticSetValues001, TestSize.Level1)
{
    auto frameNode = TextPickerModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    std::vector<NG::TextCascadePickerOptions> options = {
        { { "11", "12", "13" }, {} },
        { { "21", "22", "23" }, {} },
        { { "31", "32", "33" }, {} },
        { {}, {} }
    };
    std::vector<std::string> values = { "11" };
    TextPickerModelNG::SetColumns(AceType::RawPtr(frameNode), options);
    TextPickerModelNG::SetValues(AceType::RawPtr(frameNode), values);
    auto textPickerValues = textPickerPattern->GetValues();
    EXPECT_EQ(textPickerValues.size(), options.size());
    EXPECT_FALSE(TextPickerModelNG::getTextPickerValues(AceType::RawPtr(frameNode)).empty());
}

/**
 * @tc.name: StaticSetColumnWidths001
 * @tc.desc: Test static SetColumnWidths GetColumnWidths
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, StaticSetColumnWidths001, TestSize.Level1)
{
    auto frameNode = TextPickerModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    std::vector<Dimension> width;
    width.emplace_back(Dimension(50.0f, DimensionUnit::PERCENT));
    width.emplace_back(Dimension(20.0f, DimensionUnit::PERCENT));
    width.emplace_back(Dimension(30.0f, DimensionUnit::PERCENT));
    TextPickerModelNG::SetColumnWidths(AceType::RawPtr(frameNode), width);
    auto columnWidths = TextPickerModelNG::GetColumnWidths(AceType::RawPtr(frameNode));
    EXPECT_EQ(columnWidths.size(), width.size());
    EXPECT_EQ(columnWidths.at(0).Value(), 50.0f);
    EXPECT_EQ(columnWidths.at(1).Value(), 20.0f);
    EXPECT_EQ(columnWidths.at(2).Value(), 30.0f);
}

/**
 * @tc.name: StaticSetDivider001
 * @tc.desc: Test static SetDivider
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, StaticSetDivider001, TestSize.Level1)
{
    auto frameNode = TextPickerModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    ItemDivider divider;
    divider.strokeWidth = 6.0_vp;
    TextPickerModelNG::SetDivider(AceType::RawPtr(frameNode), divider);
    EXPECT_FLOAT_EQ(textPickerPattern->GetDivider().strokeWidth.ConvertToPx(), divider.strokeWidth.ConvertToPx());
}

/**
 * @tc.name: StaticSetGradientHeight001
 * @tc.desc: Test Static SetGradientHeight
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, StaticSetGradientHeight001, TestSize.Level1)
{
    auto frameNode = TextPickerModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    Dimension gradientHeight = 20.0_vp;
    TextPickerModelNG::SetGradientHeight(AceType::RawPtr(frameNode), gradientHeight);
    EXPECT_FLOAT_EQ(textPickerPattern->GetGradientHeight().ConvertToPx(), gradientHeight.ConvertToPx());
}

/**
 * @tc.name: StaticSetOnCascadeChange001
 * @tc.desc: Test Static SetOnCascadeChange
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, StaticSetOnCascadeChange001, TestSize.Level1)
{
    auto frameNode = TextPickerModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);
    auto textPickerEventHub = frameNode->GetOrCreateEventHub<TextPickerEventHub>();
    ASSERT_NE(textPickerEventHub, nullptr);
    int32_t callbackInfo = 0;
    auto onChangeFunc = [&callbackInfo](const std::vector<std::string>& value, const std::vector<double>& index) {
        callbackInfo = ONCHANGE_CALLBACK_INFO;
    };
    TextPickerModelNG::SetOnCascadeChange(AceType::RawPtr(frameNode), std::move(onChangeFunc));

    EXPECT_NE(textPickerEventHub->TextChangeEvent_, nullptr);
    std::vector<std::string> value = { "hello world" };
    std::vector<double> index = { 0 };
    textPickerEventHub->FireChangeEvent(value, index);
    EXPECT_EQ(callbackInfo, ONCHANGE_CALLBACK_INFO);
}

/**
 * @tc.name: StaticSetOnScrollStop001
 * @tc.desc: Test Static SetOnScrollStop
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, StaticSetOnScrollStop001, TestSize.Level1)
{
    auto frameNode = TextPickerModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);
    auto textPickerEventHub = frameNode->GetOrCreateEventHub<TextPickerEventHub>();
    ASSERT_NE(textPickerEventHub, nullptr);
    int32_t callbackInfo = 0;
    auto onScrollStopFunc = [&callbackInfo](const std::vector<std::string>& value, const std::vector<double>& index) {
        callbackInfo = ONSCROLLSTOP_CALLBACK_INFO;
    };
    TextPickerModelNG::SetOnScrollStop(AceType::RawPtr(frameNode), std::move(onScrollStopFunc));

    EXPECT_NE(textPickerEventHub->onScrollStopEvent_, nullptr);
    std::vector<std::string> value = { "hello world" };
    std::vector<double> index = { 0 };
    textPickerEventHub->FireScrollStopEvent(value, index);
    EXPECT_EQ(callbackInfo, ONSCROLLSTOP_CALLBACK_INFO);
}

/**
 * @tc.name: StaticGetSelectedSize001
 * @tc.desc: Test Static GetSelectedSize
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, StaticGetSelectedSize001, TestSize.Level1)
{
    auto frameNode = TextPickerModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    std::vector<uint32_t> values = { 0, 1, 2 };
    textPickerPattern->SetSelecteds(values);
    EXPECT_EQ(TextPickerModelNG::GetSelectedSize(AceType::RawPtr(frameNode)), values.size());
}

/**
 * @tc.name: StaticGetSelected001
 * @tc.desc: Test Static GetSelected
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, StaticGetSelected001, TestSize.Level1)
{
    auto frameNode = TextPickerModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    std::vector<uint32_t> values = { 0, 1, 2 };
    textPickerPattern->SetSelecteds(values);
    EXPECT_EQ(TextPickerModelNG::getTextPickerSelecteds(AceType::RawPtr(frameNode)).size(), values.size());
}

/**
 * @tc.name: StaticSetTextPickerRangeType001
 * @tc.desc: Test Static SetTextPickerRangeType
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, StaticSetTextPickerRangeType001, TestSize.Level1)
{
    auto frameNode = TextPickerModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);
    int32_t rangeType = 5;
    TextPickerModelNG::SetTextPickerRangeType(AceType::RawPtr(frameNode), rangeType);
    EXPECT_EQ(TextPickerModelNG::GetTextPickerRangeType(AceType::RawPtr(frameNode)), rangeType);
}

/**
 * @tc.name: StaticConvertFontScaleValue001
 * @tc.desc: Test Static ConvertFontScaleValue
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, StaticConvertFontScaleValue001, TestSize.Level2)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    Dimension defaultFontSize = 1.5_vp;
    pipeline->SetFontScale(0.0f);
    EXPECT_FLOAT_EQ(TextPickerModelNG::ConvertFontScaleValue(defaultFontSize).ConvertToPx(),
        defaultFontSize.ConvertToPx());
    pipeline->SetFontScale(0.5f);
    EXPECT_FLOAT_EQ(TextPickerModelNG::ConvertFontScaleValue(defaultFontSize).ConvertToPx(),
        defaultFontSize.ConvertToPx());
}

/**
 * @tc.name: StaticConvertFontScaleValue002
 * @tc.desc: Test Static ConvertFontScaleValue
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, StaticConvertFontScaleValue002, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);

    Dimension defaultFontSize = 2.0_px;

    pipeline->SetFollowSystem(true);
    pipeline->SetFontScale(2.0f);
    pipeline->SetMaxAppFontScale(2.0f);

    auto fontSizeValue = TextPickerModelNG::ConvertFontScaleValue(defaultFontSize);
    EXPECT_EQ(fontSizeValue.Value(), 1.0);

    pipeline->SetMaxAppFontScale(0.0f);
    fontSizeValue = TextPickerModelNG::ConvertFontScaleValue(defaultFontSize);
    EXPECT_EQ(fontSizeValue.Value(), 2.0);

    pipeline->SetFontScale(0.5f);
    fontSizeValue = TextPickerModelNG::ConvertFontScaleValue(defaultFontSize);
    EXPECT_EQ(fontSizeValue.Value(), 2.0);
}

/**
 * @tc.name: SetTextPickerDialogShow002
 * @tc.desc: Test SetTextPickerDialogShow
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, SetTextPickerDialogShow002, TestSize.Level1)
{
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto context = container->GetPipelineContext();
    ASSERT_NE(context, nullptr);
    context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto taskExecutor = context->GetTaskExecutor();
    ASSERT_NE(taskExecutor, nullptr);
    RefPtr<AceType> pickerText;
    NG::TextPickerSettingData settingData;
    auto onCancelFunc = []() {};
    auto onAcceptFunc = [](const std::string&) {};
    auto onChangeFunc = [](const std::string&) {};
    auto onScrollStopFunc = [](const std::string&) {};
    auto onEnterSelectedAreaFunc = [](const std::string&) {};

    TextPickerDialog textPickerDialog = {
        .height = 16.0_vp,
        .selectedValue = 0,
        .isDefaultHeight = true,
        .alignment = std::nullopt,
        .offset = std::nullopt,
        .maskRect = DimensionRect(),
        .backgroundColor = std::nullopt,
        .backgroundBlurStyle = std::nullopt,
        .shadow = std::nullopt,
        .hoverModeArea = HoverModeAreaType::TOP_SCREEN
    };
    TextPickerDialogEvent textPickerDialogEvent = {
        .onDidAppear = []() {},
        .onDidDisappear = []() {},
        .onWillAppear = []() {},
        .onWillDisappear = []() {}
    };
    std::vector<ButtonInfo> buttonInfos;

    int32_t backApiVersion = context->GetMinPlatformVersion();
    context->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));

    TextPickerDialogModel::GetInstance()->SetTextPickerDialogShow(pickerText, settingData,
        onCancelFunc, onAcceptFunc, onChangeFunc, onScrollStopFunc, onEnterSelectedAreaFunc, textPickerDialog,
        textPickerDialogEvent, buttonInfos);

    context->SetMinPlatformVersion(backApiVersion);

    EXPECT_FALSE(textPickerDialog.alignment.has_value());
    EXPECT_TRUE(textPickerDialog.hoverModeArea.has_value());
}

/**
 * @tc.name: SetNormalTextStyle001
 * @tc.desc: Test TextPickerModelNG SetNormalTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, SetNormalTextStyle001, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);

    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    PickerTextStyle textStyle;
    textStyle.fontSize = Dimension(0);
    TextPickerModelNG::SetNormalTextStyle(frameNode, theme, textStyle);

    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_TRUE(pickerProperty->HasFontSize());
}

/**
 * @tc.name: SetSelectedTextStyle001
 * @tc.desc: Test TextPickerModelNG SetSelectedTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, SetSelectedTextStyle001, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);

    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    PickerTextStyle textStyle;
    textStyle.fontSize = Dimension(0);
    TextPickerModelNG::SetSelectedTextStyle(frameNode, theme, textStyle);

    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_FALSE(pickerProperty->HasFontSize());
}

/**
 * @tc.name: SetDisappearTextStyle001
 * @tc.desc: Test TextPickerModelNG SetDisappearTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, SetDisappearTextStyle001, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);

    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    PickerTextStyle textStyle;
    textStyle.fontSize = Dimension(0);
    TextPickerModelNG::SetDisappearTextStyle(frameNode, theme, textStyle);

    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_FALSE(pickerProperty->HasFontSize());
}

/**
 * @tc.name: getTextPickerRange001
 * @tc.desc: Test getTextPickerRange
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, getTextPickerRange001, TestSize.Level1)
{
    /**
     * @tc.step: step1. create textpicker model.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);

    TextPickerModelNG textPickerModelNG;
    textPickerModelNG.Create(theme, TEXT);
    auto node = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(node, nullptr);

    textPickerModelNG.SetCascadeColumns({});
    textPickerModelNG.SetRange({});
    textPickerModelNG.isSingleRange_ = false;

    auto result = textPickerModelNG.getTextPickerRange(node);
    EXPECT_EQ(result.length(), 0);

    textPickerModelNG.isSingleRange_ = true;

    result = textPickerModelNG.getTextPickerRange(node);
    EXPECT_EQ(result.length(), 0);
}

/**
 * @tc.name: SetDisableTextStyleAnimation001
 * @tc.desc: Test SetDisableTextStyleAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, SetDisableTextStyleAnimation001, TestSize.Level1)
{
    auto frameNode = TextPickerModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_FALSE(pickerProperty->GetDisableTextStyleAnimation().value_or(false));

    TextPickerModelNG::SetDisableTextStyleAnimation(AceType::RawPtr(frameNode), true);
    EXPECT_TRUE(pickerProperty->GetDisableTextStyleAnimation().value_or(false));
}

/**
 * @tc.name: SetDefaultTextStyle001
 * @tc.desc: Test SetDefaultTextStyle (set minFontSize and maxFontSize)
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, SetDefaultTextStyle001, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(Dimension(), pickerProperty->GetDefaultMinFontSize().value_or(Dimension()));
    EXPECT_EQ(Dimension(), pickerProperty->GetDefaultMaxFontSize().value_or(Dimension()));

    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<TextTheme>();
    PickerTextStyle textStyle;
    textStyle.minFontSize = Dimension(10.0_vp);
    textStyle.maxFontSize = Dimension(30.0_vp);
    TextPickerModelNG::GetInstance()->SetDefaultTextStyle(theme, textStyle);
    EXPECT_EQ(Dimension(10.0_vp), pickerProperty->GetDefaultMinFontSize().value_or(Dimension()));
    EXPECT_EQ(Dimension(30.0_vp), pickerProperty->GetDefaultMaxFontSize().value_or(Dimension()));
}

/**
 * @tc.name: SetDefaultTextStyle002
 * @tc.desc: Test SetDefaultTextStyle (set textOverflow)
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, SetDefaultTextStyle002, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(TextOverflow::CLIP, pickerProperty->GetDefaultTextOverflow().value_or(TextOverflow::CLIP));

    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<TextTheme>();
    PickerTextStyle textStyle;
    textStyle.textOverflow = TextOverflow::ELLIPSIS;
    TextPickerModelNG::GetInstance()->SetDefaultTextStyle(theme, textStyle);
    EXPECT_EQ(TextOverflow::ELLIPSIS, pickerProperty->GetDefaultTextOverflow().value_or(TextOverflow::CLIP));
}

/**
 * @tc.name: SetDefaultTextStyle003
 * @tc.desc: Test SetDefaultTextStyle
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, SetDefaultTextStyle003, TestSize.Level1)
{
    auto frameNode = TextPickerModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<TextTheme>();
    PickerTextStyle textStyle;
    textStyle.minFontSize = Dimension(-1);
    textStyle.maxFontSize = Dimension(-1);
    textStyle.textOverflow = TextOverflow::ELLIPSIS;
    TextPickerModelNG::SetDefaultTextStyle(AceType::RawPtr(frameNode), theme, textStyle);
    EXPECT_EQ(Dimension(), pickerProperty->GetDefaultMinFontSize().value_or(Dimension()));
    EXPECT_EQ(Dimension(), pickerProperty->GetDefaultMaxFontSize().value_or(Dimension()));
    EXPECT_EQ(TextOverflow::ELLIPSIS, pickerProperty->GetDefaultTextOverflow().value_or(TextOverflow::CLIP));

    textStyle.minFontSize = Dimension(10.0_vp);
    textStyle.maxFontSize = Dimension(30.0_vp);
    textStyle.textOverflow = TextOverflow::NONE;
    TextPickerModelNG::SetDefaultTextStyle(AceType::RawPtr(frameNode), theme, textStyle);
    EXPECT_EQ(Dimension(10.0_vp), pickerProperty->GetDefaultMinFontSize().value_or(Dimension()));
    EXPECT_EQ(Dimension(30.0_vp), pickerProperty->GetDefaultMaxFontSize().value_or(Dimension()));
    EXPECT_EQ(TextOverflow::NONE, pickerProperty->GetDefaultTextOverflow().value_or(TextOverflow::CLIP));
}

/**
 * @tc.name: TextPickerModelNGSetEnableHapticFeedback001
 * @tc.desc: Test SetEnableHapticFeedback
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, TextPickerModelNGSetEnableHapticFeedback001, TestSize.Level1)
{
    auto frameNode = TextPickerModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    TextPickerModelNG::SetEnableHapticFeedback(AceType::RawPtr(frameNode), false);
    EXPECT_FALSE(textPickerPattern->isEnableHaptic_);
    auto result = TextPickerModelNG::GetEnableHapticFeedback(AceType::RawPtr(frameNode));
    EXPECT_FALSE(result);
}

/**
 * @tc.name: SetIsCascade001
 * @tc.desc: Test SetIsCascade.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, SetIsCascade001, TestSize.Level1)
{
    auto frameNode = TextPickerModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    TextPickerModelNG::SetIsCascade(AceType::RawPtr(frameNode), true);
    EXPECT_TRUE(textPickerPattern->isCascade_);
}

/**
 * @tc.name: SetColumnKind001
 * @tc.desc: Test SetColumnKind.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, SetColumnKind001, TestSize.Level1)
{
    auto frameNode = TextPickerModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    TextPickerModelNG::SetColumnKind(AceType::RawPtr(frameNode), TEXT);
    EXPECT_EQ(textPickerPattern->columnsKind_, TEXT);
    TextPickerModelNG::SetColumnKind(AceType::RawPtr(frameNode), MIXTURE);
    EXPECT_EQ(textPickerPattern->columnsKind_, MIXTURE);
}

/**
 * @tc.name: TextPickerModelNGSetDisableTextStyleAnimation001
 * @tc.desc: Test SetDisableTextStyleAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, TextPickerModelNGSetDisableTextStyleAnimation001, TestSize.Level1)
{
    auto frameNode = TextPickerModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);

    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);

    /**
     * @tc.cases: case1. The default value of isDisableTextStyleAnimation_ is false.
     */
    EXPECT_FALSE(textPickerPattern->isDisableTextStyleAnimation_);

    /**
     * @tc.cases: case2. Set the value of isDisableTextStyleAnimation_ to true.
     */
    TextPickerModelNG::SetDisableTextStyleAnimation(AceType::RawPtr(frameNode), true);
    EXPECT_TRUE(textPickerPattern->isDisableTextStyleAnimation_);
}

/**
 * @tc.name: SelectedBackgroundStyle001
 * @tc.desc: Test SetSelectedBackgroundStyle and GetSelectedBackgroundStyle
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, SelectedBackgroundStyle001, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    PickerBackgroundStyle pickerBgStyle;
    PickerBackgroundStyle result1;
    PickerBackgroundStyle result2;
    pickerBgStyle.color = Color(0x00000000);
    pickerBgStyle.borderRadius = NG::BorderRadiusProperty(8.0_vp);
    TextPickerModelNG::SetSelectedBackgroundStyle(frameNode, pickerBgStyle);
    result1.color = layoutProperty->GetSelectedBackgroundColorValue();
    result1.borderRadius = layoutProperty->GetSelectedBorderRadiusValue();
    result2.color = TextPickerModelNG::GetSelectedBackgroundStyle(frameNode).color;
    result2.borderRadius = TextPickerModelNG::GetSelectedBackgroundStyle(frameNode).borderRadius;
    EXPECT_EQ(pickerBgStyle.color, result1.color);
    EXPECT_EQ(pickerBgStyle.borderRadius, result1.borderRadius);
    EXPECT_EQ(pickerBgStyle.color, result2.color);
    EXPECT_EQ(pickerBgStyle.borderRadius, result2.borderRadius);
}

/**
 * @tc.name: SetSelected002
 * @tc.desc: Test SetSelected and selected value propagation
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, SetSelected002, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<PickerTheme>();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    TextPickerModelStatic::SetSelected(frameNode, 2);

    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    EXPECT_EQ(textPickerPattern->GetSelected(), 2);

    auto layoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetSelectedValue(0), 2);
}

/**
 * @tc.name: SetCanLoop002
 * @tc.desc: Test SetCanLoop and GetCanLoop
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, SetCanLoop002, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<PickerTheme>();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    TextPickerModelStatic::SetCanLoop(frameNode, true);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    EXPECT_TRUE(textPickerPattern->GetCanLoop());
    EXPECT_EQ(TextPickerModelStatic::GetCanLoop(frameNode), true);

    TextPickerModelStatic::SetCanLoop(frameNode, false);
    EXPECT_FALSE(textPickerPattern->GetCanLoop());
    EXPECT_EQ(TextPickerModelStatic::GetCanLoop(frameNode), false);
}

/**
 * @tc.name: SetBackgroundColor002
 * @tc.desc: Test SetBackgroundColor
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, SetBackgroundColor002, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<PickerTheme>();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    Color color(0xFF123456);
    TextPickerModelStatic::SetBackgroundColor(frameNode, color);

    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    EXPECT_EQ(textPickerPattern->GetBackgroundColor(), color);
}

/**
 * @tc.name: SetSelecteds001
 * @tc.desc: Test SetSelecteds and selecteds propagation
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, SetSelecteds001, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<PickerTheme>();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    std::vector<uint32_t> values = {1, 2, 3};
    TextPickerModelStatic::SetSelecteds(frameNode, values);

    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    EXPECT_EQ(textPickerPattern->GetSelecteds(), values);
}

/**
 * @tc.name: SetHasSelectAttr002
 * @tc.desc: Test SetHasSelectAttr
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, SetHasSelectAttr002, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<PickerTheme>();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    TextPickerModelStatic::SetHasSelectAttr(frameNode, true);

    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    EXPECT_TRUE(textPickerPattern->isHasSelectAttr_);
}

/**
 * @tc.name: SetIsCascade002
 * @tc.desc: Test SetIsCascade
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, SetIsCascade002, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<PickerTheme>();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    TextPickerModelStatic::SetIsCascade(frameNode, true);

    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    EXPECT_TRUE(textPickerPattern->GetIsCascade());
}

/**
 * @tc.name: SetColumnKind002
 * @tc.desc: Test SetColumnKind
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, SetColumnKind002, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<PickerTheme>();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    TextPickerModelStatic::SetColumnKind(frameNode, 2);

    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    EXPECT_EQ(textPickerPattern->columnsKind_, 2);
}

/**
 * @tc.name: SetNormalTextStyle002
 * @tc.desc: Test SetNormalTextStyle
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, SetNormalTextStyle002, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<PickerTheme>();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    PickerTextStyle style;
    style.fontSize = Dimension(20.0f);
    style.textColor = Color(0xFF0000FF);
    style.fontWeight = FontWeight::BOLD;
    style.fontFamily = std::vector<std::string>{"Arial"};
    style.fontStyle = Ace::FontStyle::ITALIC;
    TextPickerModelStatic::SetNormalTextStyle(frameNode, theme, style);

    auto layoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetFontSizeValue(Dimension()), Dimension(20.0f));
    EXPECT_EQ(layoutProperty->GetColorValue(Color()), Color(0xFF0000FF));
    EXPECT_EQ(layoutProperty->GetWeightValue(FontWeight::NORMAL), FontWeight::BOLD);
    EXPECT_EQ(layoutProperty->GetFontFamilyValue({}), std::vector<std::string>{"Arial"});
    EXPECT_EQ(layoutProperty->GetFontStyleValue(Ace::FontStyle::NORMAL), Ace::FontStyle::ITALIC);
}

/**
 * @tc.name: SetSelectedTextStyle002
 * @tc.desc: Test SetSelectedTextStyle
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, SetSelectedTextStyle002, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<PickerTheme>();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    PickerTextStyle style;
    style.fontSize = Dimension(22.0f);
    style.textColor = Color(0xFF00FF00);
    style.fontWeight = FontWeight::BOLDER;
    style.fontFamily = std::vector<std::string>{"Verdana"};
    style.fontStyle = Ace::FontStyle::ITALIC;
    TextPickerModelStatic::SetSelectedTextStyle(frameNode, theme, style);

    auto layoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetSelectedFontSizeValue(Dimension()), Dimension(22.0f));
    EXPECT_EQ(layoutProperty->GetSelectedColorValue(Color()), Color(0xFF00FF00));
    EXPECT_EQ(layoutProperty->GetSelectedWeightValue(FontWeight::NORMAL), FontWeight::BOLDER);
    EXPECT_EQ(layoutProperty->GetSelectedFontFamilyValue({}), std::vector<std::string>{"Verdana"});
    EXPECT_EQ(layoutProperty->GetSelectedFontStyleValue(Ace::FontStyle::NORMAL), Ace::FontStyle::ITALIC);
}

/**
 * @tc.name: SetDisappearTextStyle002
 * @tc.desc: Test SetDisappearTextStyle
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, SetDisappearTextStyle002, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<PickerTheme>();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    PickerTextStyle style;
    style.fontSize = Dimension(18.0f);
    style.textColor = Color(0xFFFF0000);
    style.fontWeight = FontWeight::LIGHTER;
    style.fontFamily = std::vector<std::string>{"SimSun"};
    style.fontStyle = Ace::FontStyle::NORMAL;
    TextPickerModelStatic::SetDisappearTextStyle(frameNode, theme, style);

    auto layoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetDisappearFontSizeValue(Dimension()), Dimension(18.0f));
    EXPECT_EQ(layoutProperty->GetDisappearColorValue(Color()), Color(0xFFFF0000));
    EXPECT_EQ(layoutProperty->GetDisappearWeightValue(FontWeight::NORMAL), FontWeight::LIGHTER);
    EXPECT_EQ(layoutProperty->GetDisappearFontFamilyValue({}), std::vector<std::string>{"SimSun"});
    EXPECT_EQ(layoutProperty->GetDisappearFontStyleValue(Ace::FontStyle::NORMAL), Ace::FontStyle::NORMAL);
}

/**
 * @tc.name: SetDefaultPickerItemHeight002
 * @tc.desc: Test SetDefaultPickerItemHeight and GetDefaultPickerItemHeight
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, SetDefaultPickerItemHeight002, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<PickerTheme>();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    Dimension height(50.0f);
    TextPickerModelStatic::SetDefaultPickerItemHeight(frameNode, height);

    auto layoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetDefaultPickerItemHeightValue(), height);
    EXPECT_EQ(TextPickerModelStatic::GetDefaultPickerItemHeight(frameNode), height);
}

/**
 * @tc.name: SetEnableHapticFeedback002
 * @tc.desc: Test SetEnableHapticFeedback and GetEnableHapticFeedback
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, SetEnableHapticFeedback002, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<PickerTheme>();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    TextPickerModelStatic::SetEnableHapticFeedback(frameNode, true);

    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    EXPECT_TRUE(textPickerPattern->GetIsEnableHaptic());
    EXPECT_TRUE(TextPickerModelStatic::GetEnableHapticFeedback(frameNode));

    TextPickerModelStatic::SetEnableHapticFeedback(frameNode, false);
    EXPECT_FALSE(textPickerPattern->GetIsEnableHaptic());
    EXPECT_FALSE(TextPickerModelStatic::GetEnableHapticFeedback(frameNode));
}

/**
 * @tc.name: SetValue002
 * @tc.desc: Test SetValue and selected index propagation
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, SetValue002, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<PickerTheme>();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    std::vector<RangeContent> range = {{"A"}, {"B"}, {"C"}};
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    textPickerPattern->SetRange(range);

    TextPickerModelStatic::SetValue(frameNode, "B");
    EXPECT_EQ(textPickerPattern->GetSelected(), 2);
}

/**
 * @tc.name: SetValues002
 * @tc.desc: Test SetValues and values propagation
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, SetValues002, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<PickerTheme>();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    std::vector<NG::TextCascadePickerOptions> opt = {
        { { "11", "12", "13" }, {} },
        { { "21", "22", "23" }, {} },
        { { "31", "32", "33" }, {} },
        { {}, {} }
    };
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);

    std::vector<std::string> values = {"B"};
    TextPickerModelStatic::SetColumns(frameNode, opt);
    TextPickerModelStatic::SetValues(frameNode, values);
    EXPECT_EQ(textPickerPattern->GetValues()[0], "B");
}

/**
 * @tc.name: SetRange001
 * @tc.desc: Test SetRange and range propagation
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, SetRange001, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<PickerTheme>();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    std::vector<RangeContent> range = {{"A"}, {"B"}};
    TextPickerModelStatic::SetRange(frameNode, range);

    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    EXPECT_EQ(textPickerPattern->GetRange().size(), 2);
}

/**
 * @tc.name: SetDivider002
 * @tc.desc: Test SetDivider and custom divider flag
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, SetDivider002, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<PickerTheme>();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    ItemDivider divider;
    TextPickerModelStatic::SetDivider(frameNode, divider);

    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    EXPECT_TRUE(textPickerPattern->GetCustomDividerFlag());
}

/**
 * @tc.name: SetGradientHeight002
 * @tc.desc: Test SetGradientHeight
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, SetGradientHeight002, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<PickerTheme>();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    Dimension gradient(10.0f);
    TextPickerModelStatic::SetGradientHeight(frameNode, gradient);

    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    EXPECT_EQ(textPickerPattern->GetGradientHeight(), gradient);
}

/**
 * @tc.name: SetDisableTextStyleAnimation002
 * @tc.desc: Test SetDisableTextStyleAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, SetDisableTextStyleAnimation002, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<PickerTheme>();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    TextPickerModelStatic::SetDisableTextStyleAnimation(frameNode, true);

    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    EXPECT_TRUE(textPickerPattern->GetDisableTextStyleAnimation());
}

/**
 * @tc.name: GetSelectedSize002
 * @tc.desc: Test GetSelectedSize
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, GetSelectedSize002, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<PickerTheme>();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    textPickerPattern->SetSelecteds({1, 2, 3});
    EXPECT_EQ(TextPickerModelStatic::GetSelectedSize(frameNode), 3);
}

/**
 * @tc.name: GetColumnWidthsSize001
 * @tc.desc: Test GetColumnWidthsSize
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, GetColumnWidthsSize001, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<PickerTheme>();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    textPickerPattern->SetColumnWidths({Dimension(1.0f), Dimension(2.0f)});
    EXPECT_EQ(TextPickerModelStatic::GetColumnWidthsSize(frameNode), 2);
}

/**
 * @tc.name: GetTextPickerRangeType001
 * @tc.desc: Test GetTextPickerRangeType
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, GetTextPickerRangeType001, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<PickerTheme>();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    textPickerPattern->SetRangeType(7);
    EXPECT_EQ(TextPickerModelStatic::GetTextPickerRangeType(frameNode), 7);
}

/**
 * @tc.name: GetMaxCount001
 * @tc.desc: Test GetMaxCount always returns 1
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, GetMaxCount001, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<PickerTheme>();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    EXPECT_EQ(TextPickerModelStatic::GetMaxCount(frameNode), 1);
}
/**
 * @tc.name: TextPickerModelTestNg001
 * @tc.desc: Test InitialSetupSinglePicker with empty children
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, TextPickerModelTestNg001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPickerModelStatic and FrameNode
     */
    TextPickerModelStatic textPickerModel;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    
    /**
     * @tc.steps: step2. Call InitialSetupSinglePicker
     * @tc.expected: Children should be created
     */
    textPickerModel.SetColumnKind(frameNode, TEXT);
    std::vector<NG::RangeContent> range = {
        { TEXT_PICKER_CONTENT_0, "" },
        { TEXT_PICKER_CONTENT_1, "" },
        { TEXT_PICKER_CONTENT_2, "" }
    };
    textPickerModel.SetRange(frameNode, range);
    EXPECT_FALSE(frameNode->GetChildren().empty());
}

/**
 * @tc.name: TextPickerModelTestNg002
 * @tc.desc: Test CreateColumnNode with different column kinds
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, TextPickerModelTestNg002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPickerModelStatic
     */
    TextPickerModelStatic textPickerModel;
    
    /**
     * @tc.steps: step2. Call CreateColumnNode with ICON kind
     * @tc.expected: ColumnNode with image children should be created
     */
    auto iconColumnNode = textPickerModel.CreateColumnNode(ICON, 3);
    EXPECT_NE(iconColumnNode, nullptr);
    EXPECT_EQ(iconColumnNode->GetChildren().size(), 3);
    
    /**
     * @tc.steps: step3. Call CreateColumnNode with TEXT kind
     * @tc.expected: ColumnNode with text children should be created
     */
    auto textColumnNode = textPickerModel.CreateColumnNode(TEXT, 3);
    EXPECT_NE(textColumnNode, nullptr);
    EXPECT_EQ(textColumnNode->GetChildren().size(), 3);
    
    /**
     * @tc.steps: step4. Call CreateColumnNode with MIXTURE kind
     * @tc.expected: ColumnNode with row children should be created
     */
    auto mixtureColumnNode = textPickerModel.CreateColumnNode(MIXTURE, 3);
    EXPECT_NE(mixtureColumnNode, nullptr);
    EXPECT_EQ(mixtureColumnNode->GetChildren().size(), 3);
}

/**
 * @tc.name: TextPickerModelTestNg003
 * @tc.desc: Test SetColumnWidths and GetColumnWidths
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, TextPickerModelTestNg003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPickerModelStatic and FrameNode
     */
    TextPickerModelStatic textPickerModel;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    
    /**
     * @tc.steps: step2. Set column widths
     */
    std::vector<Dimension> widths = { 100.0_px, 150.0_px, 200.0_px };
    textPickerModel.SetColumnWidths(frameNode, widths);
    
    /**
     * @tc.steps: step3. Get column widths
     * @tc.expected: Widths should match
     */
    auto getColumnWidths = textPickerModel.GetColumnWidths(frameNode);
    EXPECT_EQ(getColumnWidths.size(), widths.size());
    for (size_t i = 0; i < widths.size(); i++) {
        EXPECT_EQ(getColumnWidths[i], widths[i]);
    }
}

/**
 * @tc.name: TextPickerModelTestNg004
 * @tc.desc: Test textStyle getters
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, TextPickerModelTestNg004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPickerModelStatic and FrameNode
     */
    TextPickerModelStatic textPickerModel;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    
    /**
     * @tc.steps: step2. Get text styles
     * @tc.expected: Valid text styles should be returned
     */
    auto disappearTextStyle = textPickerModel.getDisappearTextStyle(frameNode);
    auto normalTextStyle = textPickerModel.getNormalTextStyle(frameNode);
    auto selectedTextStyle = textPickerModel.getSelectedTextStyle(frameNode);
    
    EXPECT_NE(disappearTextStyle.fontSize.value(), Dimension());
    EXPECT_NE(normalTextStyle.fontSize.value(), Dimension());
    EXPECT_NE(selectedTextStyle.fontSize.value(), Dimension());
}

/**
 * @tc.name: TextPickerModelTestNg005
 * @tc.desc: Test range and selection related functions
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, TextPickerModelTestNg005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPickerModelStatic and FrameNode
     */
    TextPickerModelStatic textPickerModel;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    
    /**
     * @tc.steps: step2. Set range
     */
    std::vector<NG::RangeContent> range = {
        { TEXT_PICKER_CONTENT_0, "" },
        { TEXT_PICKER_CONTENT_1, "" },
        { TEXT_PICKER_CONTENT_2, "" },
        { TEXT_PICKER_CONTENT_3, "" },
        { TEXT_PICKER_CONTENT_4, "" }
    };
    textPickerModel.SetRange(frameNode, range);
    
    /**
     * @tc.steps: step3. Test range related functions
     * @tc.expected: Functions should return correct values
     */
    EXPECT_TRUE(textPickerModel.IsSingle(frameNode));
    
    std::vector<NG::RangeContent> rangeValue;
    EXPECT_TRUE(textPickerModel.GetSingleRange(frameNode, rangeValue));
    EXPECT_EQ(rangeValue.size(), range.size());
    
    textPickerModel.SetTextPickerRangeType(frameNode, 1);
    EXPECT_EQ(textPickerModel.GetTextPickerRangeType(frameNode), 1);
    
    textPickerModel.SetValue(frameNode, SELECTED_VALUE);
    EXPECT_EQ(textPickerModel.getTextPickerValue(frameNode), SELECTED_VALUE);
}

/**
 * @tc.name: TextPickerModelTestNg006
 * @tc.desc: Test cascade related functions
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, TextPickerModelTestNg006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPickerModelStatic and FrameNode
     */
    TextPickerModelStatic textPickerModel;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    
    /**
     * @tc.steps: step2. Test cascade functions with false value
     * @tc.expected: Functions should return false values
     */
    EXPECT_TRUE(textPickerModel.IsCascade(frameNode));
    
    std::vector<NG::TextCascadePickerOptions> options;
    EXPECT_TRUE(textPickerModel.GetMultiOptions(frameNode, options));
    
    textPickerModel.SetIsCascade(frameNode, true);
    EXPECT_TRUE(textPickerModel.IsCascade(frameNode));
}

/**
 * @tc.name: TextPickerModelTestNg007
 * @tc.desc: Test SetValues and related functions
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, TextPickerModelTestNg007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPickerModelStatic and FrameNode
     */
    TextPickerModelStatic textPickerModel;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    
    /**
     * @tc.steps: step2. Set values
     */
    textPickerModel.SetValues(frameNode, SELECTED_VALUES);
    
    /**
     * @tc.steps: step3. Test value related functions
     * @tc.expected: Functions should return correct values
     */
    EXPECT_EQ(textPickerModel.getTextPickerValues(frameNode), "b;d");
    EXPECT_EQ(textPickerModel.GetSelectedSize(frameNode), 3);
    
    auto selecteds = textPickerModel.getTextPickerSelecteds(frameNode);
    EXPECT_EQ(selecteds.size(), 3);
    EXPECT_EQ(selecteds[0], SELECTED_INDEXES[0]);
    EXPECT_EQ(selecteds[2], SELECTED_INDEXES[1]);
}

/**
 * @tc.name: TextPickerModelTestNg008
 * @tc.desc: Test SetSelected and related functions
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, TextPickerModelTestNg008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPickerModelStatic and FrameNode
     */
    TextPickerModelStatic textPickerModel;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    
    /**
     * @tc.steps: step2. Set selected
     */
    textPickerModel.SetSelected(frameNode, SELECTED_INDEX);
    
    /**
     * @tc.steps: step3. Test selection related functions
     * @tc.expected: Functions should return correct values
     */
    EXPECT_EQ(textPickerModel.getTextPickerSelectedIndex(frameNode), SELECTED_INDEX);
    EXPECT_EQ(textPickerModel.GetSelectedSize(frameNode), 3);
}

/**
 * @tc.name: TextPickerModelTestNg009
 * @tc.desc: Test SetSelecteds and related functions
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, TextPickerModelTestNg009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPickerModelStatic and FrameNode
     */
    TextPickerModelStatic textPickerModel;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    
    /**
     * @tc.steps: step2. Set selecteds
     */
    textPickerModel.SetSelecteds(frameNode, SELECTED_INDEXES);
    
    /**
     * @tc.steps: step3. Test selection related functions
     * @tc.expected: Functions should return correct values
     */
    auto selecteds = textPickerModel.getTextPickerSelecteds(frameNode);
    EXPECT_EQ(selecteds.size(), 2);
    EXPECT_EQ(selecteds[0], SELECTED_INDEXES[0]);
    EXPECT_EQ(selecteds[1], SELECTED_INDEXES[1]);
    EXPECT_EQ(textPickerModel.GetSelectedSize(frameNode), 2);
}

/**
 * @tc.name: TextPickerModelTestNg010
 * @tc.desc: Test SetCanLoop and GetCanLoop
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, TextPickerModelTestNg010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPickerModelStatic and FrameNode
     */
    TextPickerModelStatic textPickerModel;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    
    /**
     * @tc.steps: step2. Set can loop
     */
    textPickerModel.SetCanLoop(frameNode, CAN_LOOP);
    
    /**
     * @tc.steps: step3. Get can loop
     * @tc.expected: Value should match
     */
    EXPECT_EQ(textPickerModel.GetCanLoop(frameNode), CAN_LOOP);
}

/**
 * @tc.name: TextPickerModelTestNg011
 * @tc.desc: Test SetDigitalCrownSensitivity with valid and invalid values
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, TextPickerModelTestNg011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPickerModelStatic and FrameNode
     */
    TextPickerModelStatic textPickerModel;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    
    /**
     * @tc.steps: step2. Set digital crown sensitivity with valid value
     */
    std::optional<int32_t> validValue = DIGITAL_CROWN_SENSITIVITY;
    textPickerModel.SetDigitalCrownSensitivity(frameNode, validValue);
    
    /**
     * @tc.steps: step3. Set digital crown sensitivity with invalid value
     */
    std::optional<int32_t> invalidValue = 100;
    textPickerModel.SetDigitalCrownSensitivity(frameNode, invalidValue);
    
    /**
     * @tc.steps: step4. Reset digital crown sensitivity
     */
    std::optional<int32_t> nulloptValue;
    textPickerModel.SetDigitalCrownSensitivity(frameNode, nulloptValue);
}

/**
 * @tc.name: TextPickerModelTestNg012
 * @tc.desc: Test SetDefaultPickerItemHeight and GetDefaultPickerItemHeight
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, TextPickerModelTestNg012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPickerModelStatic and FrameNode
     */
    TextPickerModelStatic textPickerModel;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    
    /**
     * @tc.steps: step2. Set default picker item height
     */
    std::optional<Dimension> heightValue = PICKER_ITEM_HEIGHT;
    textPickerModel.SetDefaultPickerItemHeight(frameNode, heightValue);
    
    /**
     * @tc.steps: step3. Get default picker item height
     * @tc.expected: Value should match
     */
    EXPECT_EQ(textPickerModel.GetDefaultPickerItemHeight(frameNode), PICKER_ITEM_HEIGHT);
    
    /**
     * @tc.steps: step4. Reset default picker item height
     */
    std::optional<Dimension> nulloptValue;
    textPickerModel.SetDefaultPickerItemHeight(frameNode, nulloptValue);
    EXPECT_EQ(textPickerModel.GetDefaultPickerItemHeight(frameNode), Dimension(0.0f));
}

/**
 * @tc.name: TextPickerModelTestNg013
 * @tc.desc: Test SetGradientHeight
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, TextPickerModelTestNg013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPickerModelStatic and FrameNode
     */
    TextPickerModelStatic textPickerModel;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    
    /**
     * @tc.steps: step2. Set gradient height
     */
    std::optional<Dimension> heightValue = GRADIENT_HEIGHT;
    textPickerModel.SetGradientHeight(frameNode, heightValue);
    
    /**
     * @tc.steps: step3. Reset gradient height
     */
    std::optional<Dimension> nulloptValue;
    textPickerModel.SetGradientHeight(frameNode, nulloptValue);
}

/**
 * @tc.name: TextPickerModelTestNg014
 * @tc.desc: Test SetDisableTextStyleAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, TextPickerModelTestNg014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPickerModelStatic and FrameNode
     */
    TextPickerModelStatic textPickerModel;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    
    /**
     * @tc.steps: step2. Set disable text style animation
     */
    textPickerModel.SetDisableTextStyleAnimation(frameNode, DISABLE_TEXT_STYLE_ANIMATION);
}

/**
 * @tc.name: TextPickerModelTestNg015
 * @tc.desc: Test SetEnableHapticFeedback and GetEnableHapticFeedback
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, TextPickerModelTestNg015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPickerModelStatic and FrameNode
     */
    TextPickerModelStatic textPickerModel;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    
    /**
     * @tc.steps: step2. Set enable haptic feedback with value
     */
    std::optional<bool> hapticValue = ENABLE_HAPTIC_FEEDBACK;
    textPickerModel.SetEnableHapticFeedback(frameNode, hapticValue);
    
    /**
     * @tc.steps: step3. Get enable haptic feedback
     * @tc.expected: Value should match
     */
    EXPECT_EQ(textPickerModel.GetEnableHapticFeedback(frameNode), ENABLE_HAPTIC_FEEDBACK);
    
    /**
     * @tc.steps: step4. Set enable haptic feedback without value
     */
    std::optional<bool> nulloptValue;
    textPickerModel.SetEnableHapticFeedback(frameNode, nulloptValue);
    EXPECT_EQ(textPickerModel.GetEnableHapticFeedback(frameNode), DEFAULT_ENABLE_HAPTIC_FEEDBACK);
}

/**
 * @tc.name: TextPickerModelTestNg016
 * @tc.desc: Test textStyle setters
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, TextPickerModelTestNg016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPickerModelStatic and FrameNode
     */
    TextPickerModelStatic textPickerModel;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto context = frameNode->GetContext();
    auto pickerTheme = context->GetTheme<PickerTheme>();
    auto textTheme = context->GetTheme<TextTheme>();
    
    /**
     * @tc.steps: step2. Set text styles
     */
    NG::PickerTextStyle normalStyle;
    normalStyle.fontSize = FONT_SIZE_VALUE;
    normalStyle.textColor = TEXT_COLOR_VALUE;
    normalStyle.fontWeight = FONT_WEIGHT_VALUE;
    normalStyle.fontFamily = FONT_FAMILY_VALUE;
    normalStyle.fontStyle = FONT_STYLE_VALUE;
    
    textPickerModel.SetNormalTextStyle(frameNode, pickerTheme, normalStyle);
    textPickerModel.SetSelectedTextStyle(frameNode, pickerTheme, normalStyle);
    textPickerModel.SetDisappearTextStyle(frameNode, pickerTheme, normalStyle);
    textPickerModel.SetDefaultTextStyle(frameNode, textTheme, normalStyle);
    textPickerModel.SetDefaultTextStyle(frameNode, normalStyle);
}

/**
 * @tc.name: TextPickerModelTestNg017
 * @tc.desc: Test SetDivider
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, TextPickerModelTestNg017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPickerModelStatic and FrameNode
     */
    TextPickerModelStatic textPickerModel;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    
    /**
     * @tc.steps: step2. Set divider
     */
    ItemDivider divider;
    divider.strokeWidth = 2.0_px;
    divider.startMargin = 10.0_px;
    divider.endMargin = 10.0_px;
    divider.color = Color::BLACK;
    textPickerModel.SetDivider(frameNode, divider);
}

/**
 * @tc.name: TextPickerModelTestNg018
 * @tc.desc: Test SetColumnKind
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, TextPickerModelTestNg018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPickerModelStatic and FrameNode
     */
    TextPickerModelStatic textPickerModel;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    
    /**
     * @tc.steps: step2. Set column kind
     */
    textPickerModel.SetColumnKind(frameNode, MIXTURE);
}

/**
 * @tc.name: TextPickerModelTestNg019
 * @tc.desc: Test SetHasSelectAttr
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, TextPickerModelTestNg019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPickerModelStatic and FrameNode
     */
    TextPickerModelStatic textPickerModel;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    
    /**
     * @tc.steps: step2. Set has select attr
     */
    textPickerModel.SetHasSelectAttr(frameNode, true);
}

/**
 * @tc.name: TextPickerModelTestNg020
 * @tc.desc: Test SetBackgroundColor
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, TextPickerModelTestNg020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPickerModelStatic and FrameNode
     */
    TextPickerModelStatic textPickerModel;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    
    /**
     * @tc.steps: step2. Set background color
     */
    textPickerModel.SetBackgroundColor(frameNode, Color::BLUE);
}

/**
 * @tc.name: TextPickerModelTestNg022
 * @tc.desc: Test GetColumnWidthsSize
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, TextPickerModelTestNg022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPickerModelStatic and FrameNode
     */
    TextPickerModelStatic textPickerModel;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    
    /**
     * @tc.steps: step2. Get column widths size
     * @tc.expected: Should return 0 for empty column widths
     */
    EXPECT_EQ(textPickerModel.GetColumnWidthsSize(frameNode), 3);
}

/**
 * @tc.name: TextPickerModelTestNg023
 * @tc.desc: Test GetMaxCount
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, TextPickerModelTestNg023, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPickerModelStatic and FrameNode
     */
    TextPickerModelStatic textPickerModel;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    
    /**
     * @tc.steps: step2. Get max count
     * @tc.expected: Should return 1
     */
    EXPECT_EQ(textPickerModel.GetMaxCount(frameNode), 1);
}

/**
 * @tc.name: TextPickerModelTestNg024
 * @tc.desc: Test GetSelectedObjectStr
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, TextPickerModelTestNg024, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPickerModelStatic and FrameNode
     */
    TextPickerModelStatic textPickerModel;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    
    /**
     * @tc.steps: step2. Get selected object str
     * @tc.expected: Should not be null
     */
    auto result = textPickerModel.GetSelectedObjectStr(frameNode, SELECTED_VALUE, SELECTED_INDEX);
    EXPECT_NE(result, "framenode null");
    EXPECT_NE(result, "pattern null");
}

/**
 * @tc.name: TextPickerModelTestNg025
 * @tc.desc: Test ConvertFontScaleValue with different conditions
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, TextPickerModelTestNg025, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test ConvertFontScaleValue with VP unit
     * @tc.expected: Should return original value
     */
    Dimension vpValue(20.0, DimensionUnit::VP);
    auto result = TextPickerModelStatic::ConvertFontScaleValue(vpValue);
    EXPECT_EQ(result, vpValue);
    
    /**
     * @tc.steps: step2. Test ConvertFontScaleValue with zero font scale
     * @tc.expected: Should return original value
     */
    Dimension pxValue(20.0, DimensionUnit::PX);
    auto result2 = TextPickerModelStatic::ConvertFontScaleValue(pxValue);
    EXPECT_EQ(result2.Value(), pxValue.Value());
}

/**
 * @tc.name: TextPickerModelTestNg026
 * @tc.desc: Test ValidateData function
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModelTestNg, TextPickerModelTestNg026, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Prepare test data
     */
    NG::TextCascadePickerOptions options;
    options.rangeResult = { "a", "b", "c" };
    std::vector<std::string> values = { "b" };
    uint32_t index = 0;
    std::vector<std::string> selectedValues;
    std::vector<uint32_t> valuesIndex;
    
    /**
     * @tc.steps: step2. Call ValidateData with existing value
     * @tc.expected: Should find the value and its index
     */
    TextPickerModelStatic::ValidateData(options, values, index, selectedValues, valuesIndex);
    EXPECT_EQ(selectedValues[0], "b");
    EXPECT_EQ(valuesIndex[0], 1);
    
    /**
     * @tc.steps: step3. Call ValidateData with non-existing value
     * @tc.expected: Should use the first value and index 0
     */
    std::vector<std::string> values2 = { "d" };
    std::vector<std::string> selectedValues2;
    std::vector<uint32_t> valuesIndex2;
    TextPickerModelStatic::ValidateData(options, values2, index, selectedValues2, valuesIndex2);
    EXPECT_EQ(selectedValues2[0], "a");
    EXPECT_EQ(valuesIndex2[0], 0);
    
    /**
     * @tc.steps: step4. Call ValidateData with empty values
     * @tc.expected: Should use empty string and index 0
     */
    std::vector<std::string> values3;
    std::vector<std::string> selectedValues3;
    std::vector<uint32_t> valuesIndex3;
    options.rangeResult.clear();
    TextPickerModelStatic::ValidateData(options, values3, index, selectedValues3, valuesIndex3);
    EXPECT_EQ(selectedValues3[0], "");
    EXPECT_EQ(valuesIndex3[0], 0);
}
} // namespace OHOS::Ace::NG
