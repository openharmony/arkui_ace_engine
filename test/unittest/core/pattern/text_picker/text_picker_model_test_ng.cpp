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
        if (type == IconTheme::TypeId()) {
            return AceType::MakeRefPtr<IconTheme>();
        } else if (type == DialogTheme::TypeId()) {
            return AceType::MakeRefPtr<DialogTheme>();
        } else if (type == PickerTheme::TypeId()) {
            return MockThemeDefault::GetPickerTheme();
        } else {
            return nullptr;
        }
    });
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
    auto textPickerEventHub = frameNode->GetEventHub<TextPickerEventHub>();
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
    auto textPickerEventHub = frameNode->GetEventHub<TextPickerEventHub>();
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
        onCancelFunc, onAcceptFunc, onChangeFunc, onScrollStopFunc, textPickerDialog, textPickerDialogEvent,
        buttonInfos);
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
    auto textPickerEventHub = frameNode->GetEventHub<TextPickerEventHub>();
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
    auto textPickerEventHub = frameNode->GetEventHub<TextPickerEventHub>();
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
} // namespace OHOS::Ace::NG
