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
#include "test/mock/base/mock_system_properties.h"

#include "core/components/theme/icon_theme.h"
#include "core/components_ng/pattern/picker/picker_theme.h"
#include "core/components/button/button_theme.h"
#include "core/components/dialog/dialog_theme.h"
#include "core/components_ng/pattern/text_picker/textpicker_model_ng.h"
#include "core/components_ng/pattern/text_picker/textpicker_pattern.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr uint32_t SELECTED_INDEX_1 = 1;
constexpr double TEST_FONT_SIZE = 10.0;
constexpr double TEST_MIN_FONT_SIZE = 9.0;
constexpr double TEST_MAX_FONT_SIZE = 20.0;
const Dimension FONT_SIZE_VALUE_DIMENSION = Dimension(20.1, DimensionUnit::PX);
const std::vector<std::string> FONT_FAMILY_CURSIVE = { "cursive" };
const std::vector<std::string> FONT_FAMILY_ARIAL = { "arial" };
} // namespace

class TextPickerResourceTest : public testing::Test {
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
    RefPtr<TextTheme> textTheme_;
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

void TextPickerResourceTest::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void TextPickerResourceTest::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void TextPickerResourceTest::SetUp()
{
    iconThem_ = AceType::MakeRefPtr<IconTheme>();
    dialogTheme_ = AceType::MakeRefPtr<DialogTheme>();
    pickerThem_ = MockThemeDefault::GetPickerTheme();
    buttonTheme_ = AceType::MakeRefPtr<ButtonTheme>();
    textTheme_ = AceType::MakeRefPtr<TextTheme>();

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);

    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillRepeatedly([this](ThemeType type) -> RefPtr<Theme> {return GetThemeByType(type);});

    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([this](ThemeType type, int32_t themeScopeId) -> RefPtr<Theme> {return GetThemeByType(type);});
}

void TextPickerResourceTest::TearDown()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    ViewStackProcessor::GetInstance()->ClearStack();
}

RefPtr<Theme> TextPickerResourceTest::GetThemeByType(ThemeType type)
{
    if (type == IconTheme::TypeId()) {
        return iconThem_;
    } else if (type == DialogTheme::TypeId()) {
        return dialogTheme_;
    } else if (type == PickerTheme::TypeId()) {
        return pickerThem_;
    } else if (type == ButtonTheme::TypeId()) {
        return buttonTheme_;
    } else if (type == TextTheme::TypeId()) {
        return textTheme_;
    } else {
        return nullptr;
    }
}

/**
 * @tc.name: ParseCascadeRangeOptions001
 * @tc.desc: Test ParseCascadeRangeOptions when option size is zero.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerResourceTest, ParseCascadeRangeOptions001, TestSize.Level1)
{
    std::vector<NG::TextCascadePickerOptions> options;
    TextPickerPattern textPickerPattern;
    textPickerPattern.ParseCascadeRangeOptions(options);
    EXPECT_EQ(options.size(), 0);
}

/**
 * @tc.name: ParseCascadeRangeOptions002
 * @tc.desc: Test ParseCascadeRangeOptions when option size is not zero, rangeResultResObj is null.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerResourceTest, ParseCascadeRangeOptions002, TestSize.Level1)
{
    std::vector<NG::TextCascadePickerOptions> options;
    NG::TextCascadePickerOptions option1;
    option1.rangeResult = { "11", "12", "13" };
    option1.rangeResultResObj = nullptr;
    options.emplace_back(option1);
    NG::TextCascadePickerOptions option2;
    option2.rangeResult = { "21", "22", "23" };
    option2.rangeResultResObj = nullptr;
    options.emplace_back(option2);

    std::vector<std::string> expectValue1 = { "11", "12", "13" };
    std::vector<std::string> expectValue2 = { "21", "22", "23" };

    TextPickerPattern textPickerPattern;
    textPickerPattern.ParseCascadeRangeOptions(options);
    EXPECT_EQ(options.size(), 2);
    EXPECT_EQ(options[0].rangeResult, expectValue1);
    EXPECT_EQ(options[1].rangeResult, expectValue2);
}

/**
 * @tc.name: ParseSingleIconTextResourceObj001
 * @tc.desc: Test ParseSingleIconTextResourceObj when resObj is null.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerResourceTest, ParseSingleIconTextResourceObj001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPicker.
     */
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();

    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    std::vector<NG::RangeContent> oldRange = { { "", "Text1" }, { "", "Text2" }, { "", "Text3" } };
    TextPickerModelNG::GetInstance()->SetRange(oldRange);
    TextPickerModelNG::GetInstance()->SetSelected(SELECTED_INDEX_1);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Set g_isConfigChangePerform to true.
     */
    g_isConfigChangePerform = true;
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->resourceMgr_ = AceType::MakeRefPtr<PatternResourceManager>();
    ASSERT_NE(pattern->resourceMgr_, nullptr);

    /**
     * @tc.steps: step3. Call ParseSingleIconTextResourceObj to register the resourceObject callback function.
     */
    std::vector<NG::RangeContent> newRange = { { "", "" }, { "", "" }, { "", "" } };
    TextPickerModelNG::GetInstance()->ParseSingleIconTextResourceObj(newRange);
    pattern->resourceMgr_->ReloadResources();

    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    std::vector<NG::RangeContent> resultRange = textPickerPattern->GetRange();
    EXPECT_EQ(resultRange.size(), oldRange.size());
    for (uint32_t i = 0; i < resultRange.size(); i++) {
        EXPECT_EQ(resultRange[i].text_, oldRange[i].text_);
    }
}

/**
 * @tc.name: ParseSingleIconTextResourceObj002
 * @tc.desc: Test ParseSingleIconTextResourceObj when resObj is not null but is invalid.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerResourceTest, ParseSingleIconTextResourceObj002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPicker.
     */
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();

    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    std::vector<NG::RangeContent> oldRange = { { "", "Text1" }, { "", "Text2" }, { "", "Text3" } };
    TextPickerModelNG::GetInstance()->SetRange(oldRange);
    TextPickerModelNG::GetInstance()->SetSelected(SELECTED_INDEX_1);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Set g_isConfigChangePerform to true.
     */
    g_isConfigChangePerform = true;
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->resourceMgr_ = AceType::MakeRefPtr<PatternResourceManager>();
    ASSERT_NE(pattern->resourceMgr_, nullptr);

    /**
     * @tc.steps: step3. Call ParseSingleIconTextResourceObj to register the resourceObject callback function.
     * @tc.expected: Dut to resourceObject is invalid, range will be set to default value.
     */
    std::vector<NG::RangeContent> newRange = {
        { "", "1", AceType::MakeRefPtr<ResourceObject>(), AceType::MakeRefPtr<ResourceObject>() },
        { "", "2", AceType::MakeRefPtr<ResourceObject>(), AceType::MakeRefPtr<ResourceObject>() },
        { "", "3", AceType::MakeRefPtr<ResourceObject>(), AceType::MakeRefPtr<ResourceObject>() },
        { "", "4", AceType::MakeRefPtr<ResourceObject>(), AceType::MakeRefPtr<ResourceObject>() }
    };
    TextPickerModelNG::GetInstance()->ParseSingleIconTextResourceObj(newRange);
    pattern->resourceMgr_->ReloadResources();

    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    std::vector<NG::RangeContent> resultRange = textPickerPattern->GetRange();
    EXPECT_EQ(resultRange.size(), newRange.size());
    for (uint32_t i = 0; i < resultRange.size(); i++) {
        EXPECT_EQ(resultRange[i].text_, "");
    }
}

/**
 * @tc.name: ParseDividerResObj001
 * @tc.desc: Test ParseDividerResObj when divider resourceObj is null.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerResourceTest, ParseDividerResObj001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPicker.
     */
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);

    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    std::vector<NG::RangeContent> oldRange = { { "", "Text1" }, { "", "Text2" }, { "", "Text3" } };
    TextPickerModelNG::GetInstance()->SetRange(oldRange);
    TextPickerModelNG::GetInstance()->SetSelected(SELECTED_INDEX_1);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Set g_isConfigChangePerform to true.
     */
    g_isConfigChangePerform = true;
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->resourceMgr_ = AceType::MakeRefPtr<PatternResourceManager>();
    ASSERT_NE(pattern->resourceMgr_, nullptr);
    auto& resMap = pattern->resourceMgr_->resMap_;

    /**
     * @tc.steps: step3. Call ParseDividerResObj to register the resourceObject callback function.
     * @tc.expected: Dut to divider is null, the value will not be changed.
     */
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    NG::ItemDivider newDivider;
    newDivider.isDefaultColor = true;
    newDivider.strokeWidth = 0.0_vp;
    TextPickerModelNG::ParseDividerResObj(frameNode, newDivider);
    EXPECT_TRUE(resMap.find("textPicker.divider") == resMap.end());
}

/**
 * @tc.name: ParseDividerResObj002
 * @tc.desc: Test ParseDividerResObj when divider resourceObj is not null.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerResourceTest, ParseDividerResObj002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPicker.
     */
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);

    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    std::vector<NG::RangeContent> oldRange = { { "", "Text1" }, { "", "Text2" }, { "", "Text3" } };
    TextPickerModelNG::GetInstance()->SetRange(oldRange);
    TextPickerModelNG::GetInstance()->SetSelected(SELECTED_INDEX_1);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Set g_isConfigChangePerform to true.
     */
    g_isConfigChangePerform = true;
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->resourceMgr_ = AceType::MakeRefPtr<PatternResourceManager>();
    ASSERT_NE(pattern->resourceMgr_, nullptr);

    /**
     * @tc.steps: step3. Call ParseDividerResObj to register the resourceObject callback function.
     * @tc.expected: Dut to divider is not null, the value will be changed.
     */
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    NG::ItemDivider newDivider;
    newDivider.isDefaultColor = false;
    newDivider.colorResObj = AceType::MakeRefPtr<ResourceObject>();
    newDivider.strokeWidth = 0.0_vp;
    TextPickerModelNG::ParseDividerResObj(frameNode, newDivider);
    pattern->resourceMgr_->ReloadResources();
    NG::ItemDivider curDivider = textPickerPattern->GetDivider();
    EXPECT_EQ(curDivider.strokeWidth, theme->GetDividerThickness());
}

/**
 * @tc.name: UpdateDisappearTextStyle001
 * @tc.desc: Test TextPickerPattern UpdateDisappearTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerResourceTest, UpdateDisappearTextStyle001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPicker.
     */
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();

    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    std::vector<NG::RangeContent> oldRange = { { "", "Text1" }, { "", "Text2" }, { "", "Text3" } };
    TextPickerModelNG::GetInstance()->SetRange(oldRange);
    TextPickerModelNG::GetInstance()->SetSelected(SELECTED_INDEX_1);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->SetIsSystemColorChange(true);

    PickerTextStyle textStyle;
    textStyle.textColor = Color::RED;
    textStyle.fontSize = Dimension(TEST_FONT_SIZE);
    TextPickerModelNG::GetInstance()->SetDisappearTextStyle(theme, textStyle);

    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(pickerProperty->GetDisappearColor().value(), Color::RED);
    EXPECT_EQ(pickerProperty->GetDisappearFontSize().value(), Dimension(TEST_FONT_SIZE));

    textStyle.textColor = Color::GREEN;
    textStyle.fontSize = Dimension(TEST_FONT_SIZE + 1);
    auto pickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);
    pickerPattern->UpdateDisappearTextStyle(textStyle);

    EXPECT_EQ(pickerProperty->GetDisappearColor().value(), Color::GREEN);
    EXPECT_EQ(pickerProperty->GetDisappearFontSize().value(), Dimension(TEST_FONT_SIZE + 1));
}

/**
 * @tc.name: UpdateDisappearTextStyle002
 * @tc.desc: Test TextPickerPattern UpdateDisappearTextStyle, when the input parameter is invalid
 *           and the LayoutProperty has no value, the theme value will be used for setting.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerResourceTest, UpdateDisappearTextStyle002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPicker.
     */
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    std::vector<NG::RangeContent> oldRange = { { "", "Text1" }, { "", "Text2" }, { "", "Text3" } };
    TextPickerModelNG::GetInstance()->SetRange(oldRange);
    TextPickerModelNG::GetInstance()->SetSelected(SELECTED_INDEX_1);
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
    auto pickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);
    PickerTextStyle textStyle;
    pickerPattern->UpdateDisappearTextStyle(textStyle);

    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(pickerProperty->GetDisappearColor().value(), Color::GREEN);
    EXPECT_EQ(pickerProperty->GetDisappearFontSize().value(), FONT_SIZE_VALUE_DIMENSION);
    EXPECT_EQ(pickerProperty->GetDisappearFontFamily().value(), FONT_FAMILY_CURSIVE);  
}

/**
 * @tc.name: UpdateDisappearTextStyle003
 * @tc.desc: Test TextPickerPattern UpdateDisappearTextStyle, when the input parameter is invalid
 *           and the LayoutProperty has no value, the theme value will be used for setting.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerResourceTest, UpdateDisappearTextStyle003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPicker.
     */
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    std::vector<NG::RangeContent> oldRange = { { "", "Text1" }, { "", "Text2" }, { "", "Text3" } };
    TextPickerModelNG::GetInstance()->SetRange(oldRange);
    TextPickerModelNG::GetInstance()->SetSelected(SELECTED_INDEX_1);
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
    TextPickerModelNG::GetInstance()->SetDisappearTextStyle(theme, textStyle);

    /**
     * @tc.steps: step4. Call UpdateDisappearTextStyle with the parameter textStyle having no valid value.
     * @tc.expected: The value of PickerTheme will be used for setting.
     */
    auto pickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);
    PickerTextStyle newTextStyle;
    pickerPattern->UpdateDisappearTextStyle(newTextStyle);

    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(pickerProperty->GetDisappearColor().value(), Color::RED);
    EXPECT_EQ(pickerProperty->GetDisappearFontSize().value(), Dimension(TEST_FONT_SIZE, DimensionUnit::VP));
    EXPECT_EQ(pickerProperty->GetDisappearFontFamily().value(), FONT_FAMILY_ARIAL);    
}

/**
 * @tc.name: UpdateNormalTextStyle001
 * @tc.desc: Test TextPickerPattern UpdateNormalTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerResourceTest, UpdateNormalTextStyle001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPicker.
     */
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();

    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    std::vector<NG::RangeContent> oldRange = { { "", "Text1" }, { "", "Text2" }, { "", "Text3" } };
    TextPickerModelNG::GetInstance()->SetRange(oldRange);
    TextPickerModelNG::GetInstance()->SetSelected(SELECTED_INDEX_1);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->SetIsSystemColorChange(true);

    PickerTextStyle textStyle;
    textStyle.textColor = Color::RED;
    textStyle.fontSize = Dimension(TEST_FONT_SIZE);
    TextPickerModelNG::GetInstance()->SetNormalTextStyle(theme, textStyle);

    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(pickerProperty->GetColor().value(), Color::RED);
    EXPECT_EQ(pickerProperty->GetFontSize().value(), Dimension(TEST_FONT_SIZE));

    textStyle.textColor = Color::GREEN;
    textStyle.fontSize = Dimension(TEST_FONT_SIZE + 1);
    auto pickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);
    pickerPattern->UpdateNormalTextStyle(textStyle);

    EXPECT_EQ(pickerProperty->GetColor().value(), Color::GREEN);
    EXPECT_EQ(pickerProperty->GetFontSize().value(), Dimension(TEST_FONT_SIZE + 1));
}

/**
 * @tc.name: UpdateNormalTextStyle002
 * @tc.desc: Test TextPickerPattern UpdateNormalTextStyle, when the input parameter is invalid
 *           and the LayoutProperty has no value, the theme value will be used for setting.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerResourceTest, UpdateNormalTextStyle002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPicker.
     */
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    std::vector<NG::RangeContent> oldRange = { { "", "Text1" }, { "", "Text2" }, { "", "Text3" } };
    TextPickerModelNG::GetInstance()->SetRange(oldRange);
    TextPickerModelNG::GetInstance()->SetSelected(SELECTED_INDEX_1);
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
    auto pickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);
    PickerTextStyle textStyle;
    pickerPattern->UpdateNormalTextStyle(textStyle);

    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(pickerProperty->GetColor().value(), Color::GREEN);
    EXPECT_EQ(pickerProperty->GetFontSize().value(), FONT_SIZE_VALUE_DIMENSION);
    EXPECT_EQ(pickerProperty->GetFontFamily().value(), FONT_FAMILY_CURSIVE);  
}

/**
 * @tc.name: UpdateNormalTextStyle003
 * @tc.desc: Test TextPickerPattern UpdateNormalTextStyle, when the input parameter is invalid
 *           and the LayoutProperty has no value, the theme value will be used for setting.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerResourceTest, UpdateNormalTextStyle003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPicker.
     */
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    std::vector<NG::RangeContent> oldRange = { { "", "Text1" }, { "", "Text2" }, { "", "Text3" } };
    TextPickerModelNG::GetInstance()->SetRange(oldRange);
    TextPickerModelNG::GetInstance()->SetSelected(SELECTED_INDEX_1);
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
    TextPickerModelNG::GetInstance()->SetNormalTextStyle(theme, textStyle);

    /**
     * @tc.steps: step4. Call UpdateNormalTextStyle with the parameter textStyle having no valid value.
     * @tc.expected: The value of PickerTheme will be used for setting.
     */
    auto pickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);
    PickerTextStyle newTextStyle;
    pickerPattern->UpdateNormalTextStyle(newTextStyle);

    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(pickerProperty->GetColor().value(), Color::RED);
    EXPECT_EQ(pickerProperty->GetFontSize().value(), Dimension(TEST_FONT_SIZE, DimensionUnit::VP));
    EXPECT_EQ(pickerProperty->GetFontFamily().value(), FONT_FAMILY_ARIAL);    
}

/**
 * @tc.name: UpdateSelectedTextStyle001
 * @tc.desc: Test TextPickerPattern UpdateSelectedTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerResourceTest, UpdateSelectedTextStyle001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPicker.
     */
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();

    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    std::vector<NG::RangeContent> oldRange = { { "", "Text1" }, { "", "Text2" }, { "", "Text3" } };
    TextPickerModelNG::GetInstance()->SetRange(oldRange);
    TextPickerModelNG::GetInstance()->SetSelected(SELECTED_INDEX_1);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->SetIsSystemColorChange(true);

    PickerTextStyle textStyle;
    textStyle.textColor = Color::RED;
    textStyle.fontSize = Dimension(TEST_FONT_SIZE);
    TextPickerModelNG::GetInstance()->SetSelectedTextStyle(theme, textStyle);

    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(pickerProperty->GetSelectedColor().value(), Color::RED);
    EXPECT_EQ(pickerProperty->GetSelectedFontSize().value(), Dimension(TEST_FONT_SIZE));

    textStyle.textColor = Color::GREEN;
    textStyle.fontSize = Dimension(TEST_FONT_SIZE + 1);
    auto pickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);
    pickerPattern->UpdateSelectedTextStyle(textStyle);

    EXPECT_EQ(pickerProperty->GetSelectedColor().value(), Color::GREEN);
    EXPECT_EQ(pickerProperty->GetSelectedFontSize().value(), Dimension(TEST_FONT_SIZE + 1));
}

/**
 * @tc.name: UpdateSelectedTextStyle002
 * @tc.desc: Test TextPickerPattern UpdateSelectedTextStyle, when the input parameter is invalid
 *           and the LayoutProperty has no value, the theme value will be used for setting.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerResourceTest, UpdateSelectedTextStyle002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPicker.
     */
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    std::vector<NG::RangeContent> oldRange = { { "", "Text1" }, { "", "Text2" }, { "", "Text3" } };
    TextPickerModelNG::GetInstance()->SetRange(oldRange);
    TextPickerModelNG::GetInstance()->SetSelected(SELECTED_INDEX_1);
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
    auto pickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);
    PickerTextStyle textStyle;
    pickerPattern->UpdateSelectedTextStyle(textStyle);

    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(pickerProperty->GetSelectedColor().value(), Color::GREEN);
    EXPECT_EQ(pickerProperty->GetSelectedFontSize().value(), FONT_SIZE_VALUE_DIMENSION);
    EXPECT_EQ(pickerProperty->GetSelectedFontFamily().value(), FONT_FAMILY_CURSIVE);  
}

/**
 * @tc.name: UpdateSelectedTextStyle003
 * @tc.desc: Test TextPickerPattern UpdateSelectedTextStyle, when the input parameter is invalid
 *           and the LayoutProperty has no value, the theme value will be used for setting.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerResourceTest, UpdateSelectedTextStyle003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPicker.
     */
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    std::vector<NG::RangeContent> oldRange = { { "", "Text1" }, { "", "Text2" }, { "", "Text3" } };
    TextPickerModelNG::GetInstance()->SetRange(oldRange);
    TextPickerModelNG::GetInstance()->SetSelected(SELECTED_INDEX_1);
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
    TextPickerModelNG::GetInstance()->SetSelectedTextStyle(theme, textStyle);

    /**
     * @tc.steps: step4. Call UpdateSelectedTextStyle with the parameter textStyle having no valid value.
     * @tc.expected: The value of PickerTheme will be used for setting.
     */
    auto pickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);
    PickerTextStyle newTextStyle;
    pickerPattern->UpdateSelectedTextStyle(newTextStyle);

    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(pickerProperty->GetSelectedColor().value(), Color::RED);
    EXPECT_EQ(pickerProperty->GetSelectedFontSize().value(), Dimension(TEST_FONT_SIZE, DimensionUnit::VP));
    EXPECT_EQ(pickerProperty->GetSelectedFontFamily().value(), FONT_FAMILY_ARIAL);    
}

/**
 * @tc.name: SetDefaultTextStyle001
 * @tc.desc: Test SetDefaultTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerResourceTest, SetDefaultTextStyle001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPicker.
     */
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();

    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    std::vector<NG::RangeContent> oldRange = { { "", "Text1" }, { "", "Text2" }, { "", "Text3" } };
    TextPickerModelNG::GetInstance()->SetRange(oldRange);
    TextPickerModelNG::GetInstance()->SetSelected(SELECTED_INDEX_1);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->SetIsSystemColorChange(true);

    /**
     * @tc.steps: step2. Call SetDefaultTextStyle function.
     */
    PickerTextStyle textStyle;
    textStyle.textColor = Color::RED;
    textStyle.fontSize = Dimension(TEST_FONT_SIZE);
    auto textTheme = pipeline->GetTheme<TextTheme>();
    TextPickerModelNG::GetInstance()->SetDefaultTextStyle(textTheme, textStyle);

    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(pickerProperty->GetDefaultColor().value(), Color::RED);
    EXPECT_EQ(pickerProperty->GetDefaultFontSize().value(), Dimension(TEST_FONT_SIZE));

    textStyle.textColor = Color::GREEN;
    textStyle.fontSize = Dimension(TEST_FONT_SIZE + 1);
    textStyle.minFontSize = Dimension(TEST_MIN_FONT_SIZE);
    textStyle.maxFontSize = Dimension(TEST_MAX_FONT_SIZE);
    auto pickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);
    pickerPattern->UpdateDefaultTextStyle(textStyle);

    EXPECT_EQ(pickerProperty->GetDefaultColor().value(), Color::GREEN);
    EXPECT_EQ(pickerProperty->GetDefaultFontSize().value(), Dimension(TEST_FONT_SIZE + 1));
    EXPECT_EQ(pickerProperty->GetDefaultMinFontSize().value(), Dimension(TEST_MIN_FONT_SIZE));
    EXPECT_EQ(pickerProperty->GetDefaultMaxFontSize().value(), Dimension(TEST_MAX_FONT_SIZE));
}

/**
 * @tc.name: UpdateDefaultTextStyle002
 * @tc.desc: Test UpdateDefaultTextStyle, when the input parameter is invalid
 *           and the LayoutProperty has no value, the theme value will be used for setting.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerResourceTest, UpdateDefaultTextStyle002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPicker.
     */
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    std::vector<NG::RangeContent> oldRange = { { "", "Text1" }, { "", "Text2" }, { "", "Text3" } };
    TextPickerModelNG::GetInstance()->SetRange(oldRange);
    TextPickerModelNG::GetInstance()->SetSelected(SELECTED_INDEX_1);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->SetIsSystemColorChange(true);

    /**
     * @tc.steps: step2. Set the default value for the PickerTheme.
     */
    auto textTheme = pipeline->GetTheme<TextTheme>();
    ASSERT_NE(textTheme, nullptr);
    textTheme->textStyle_.SetTextColor(Color::GREEN);
    textTheme->textStyle_.SetFontSize(FONT_SIZE_VALUE_DIMENSION);
    textTheme->textStyle_.SetFontFamilies(FONT_FAMILY_CURSIVE);

    /**
     * @tc.steps: step3. Call UpdateDefaultTextStyle with the parameter textStyle having no valid value.
     * @tc.expected: The value of PickerTheme will be used for setting.
     */
    auto pickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);
    PickerTextStyle textStyle;
    pickerPattern->UpdateDefaultTextStyle(textStyle);

    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(pickerProperty->GetDefaultColor().value(), Color::GREEN);
    EXPECT_EQ(pickerProperty->GetDefaultFontSize().value(), FONT_SIZE_VALUE_DIMENSION);
    EXPECT_EQ(pickerProperty->GetDefaultFontFamily().value(), FONT_FAMILY_CURSIVE);
}

/**
 * @tc.name: UpdateDefaultTextStyle003
 * @tc.desc: Test UpdateDefaultTextStyle, when the input parameter is invalid
 *           and the LayoutProperty has value, the LayoutProperty value will be used for setting.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerResourceTest, UpdateDefaultTextStyle003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPicker.
     */
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    std::vector<NG::RangeContent> oldRange = { { "", "Text1" }, { "", "Text2" }, { "", "Text3" } };
    TextPickerModelNG::GetInstance()->SetRange(oldRange);
    TextPickerModelNG::GetInstance()->SetSelected(SELECTED_INDEX_1);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->SetIsSystemColorChange(true);

    /**
     * @tc.steps: step2. Set the default value for the PickerTheme.
     */
    auto textTheme = pipeline->GetTheme<TextTheme>();
    ASSERT_NE(textTheme, nullptr);
    textTheme->textStyle_.SetTextColor(Color::GREEN);
    textTheme->textStyle_.SetFontSize(FONT_SIZE_VALUE_DIMENSION);
    textTheme->textStyle_.SetFontFamilies(FONT_FAMILY_CURSIVE);

    /**
     * @tc.steps: step3. SetDefaultTextStyle to ensure the LayoutProperty has value.
     */
    PickerTextStyle textStyle;
    textStyle.textColor = Color::RED;
    textStyle.fontSize = Dimension(TEST_FONT_SIZE, DimensionUnit::VP);
    textStyle.fontFamily = FONT_FAMILY_ARIAL;
    TextPickerModelNG::GetInstance()->SetDefaultTextStyle(textTheme, textStyle);

    /**
     * @tc.steps: step4. Call UpdateDefaultTextStyle with the parameter textStyle having no valid value.
     * @tc.expected: The value of PickerTheme will be used for setting.
     */
    auto pickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);
    PickerTextStyle newTextStyle;
    pickerPattern->UpdateDefaultTextStyle(newTextStyle);

    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(pickerProperty->GetDefaultColor().value(), Color::RED);
    EXPECT_EQ(pickerProperty->GetDefaultFontSize().value(), Dimension(TEST_FONT_SIZE, DimensionUnit::VP));
    EXPECT_EQ(pickerProperty->GetDefaultFontFamily().value(), FONT_FAMILY_ARIAL);  
}

/**
 * @tc.name: SelectedBackgroundStyle001
 * @tc.desc: Test GetCanLoopFromLayoutProperty.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerResourceTest, SelectedBackgroundStyle001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPicker.
     */
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);

    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    std::vector<NG::RangeContent> oldRange = { { "", "Text1" }, { "", "Text2" }, { "", "Text3" } };
    TextPickerModelNG::GetInstance()->SetRange(oldRange);
    TextPickerModelNG::GetInstance()->SetSelected(SELECTED_INDEX_1);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Set g_isConfigChangePerform to true.
     */
    g_isConfigChangePerform = true;
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->resourceMgr_ = AceType::MakeRefPtr<PatternResourceManager>();
    ASSERT_NE(pattern->resourceMgr_, nullptr);

    NG::PickerBackgroundStyle pickerBgStyle;
    pickerBgStyle.color = Color::RED;
    pickerBgStyle.borderRadius = NG::BorderRadiusProperty(8.0_vp);
    TextPickerModelNG::SetSelectedBackgroundStyle(frameNode, pickerBgStyle);

    NG::PickerBackgroundStyle result1;
    NG::PickerBackgroundStyle result2;
    auto layoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    result1.color = layoutProperty->GetSelectedBackgroundColorValue();
    result1.borderRadius = layoutProperty->GetSelectedBorderRadiusValue();
    result2.color = TextPickerModelNG::GetSelectedBackgroundStyle(frameNode).color;
    result2.borderRadius = TextPickerModelNG::GetSelectedBackgroundStyle(frameNode).borderRadius;
    EXPECT_EQ(pickerBgStyle.color, result1.color);
    EXPECT_EQ(pickerBgStyle.borderRadius, result1.borderRadius);
    EXPECT_EQ(pickerBgStyle.color, result2.color);
    EXPECT_EQ(pickerBgStyle.borderRadius, result2.borderRadius);

    /**
     * @tc.steps: step3. Call ParseBackgroundStyleColorResObj and ParseBackgroundStyleRadiusResObj
     * to register the resourceObject callback function.
     * @tc.expected: Dut to color is set by user, the value will not be changed.
     */
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);

    pickerBgStyle.textColorSetByUser = true;
    pickerBgStyle.colorResObj = AceType::MakeRefPtr<ResourceObject>();
    pickerBgStyle.borderRadiusResObj = AceType::MakeRefPtr<ResourceObject>();
    TextPickerModelNG::ParseBackgroundStyleColorResObj(frameNode, pickerBgStyle);
    TextPickerModelNG::ParseBackgroundStyleRadiusResObj(frameNode, pickerBgStyle);
    pattern->resourceMgr_->ReloadResources();
    result1.color = layoutProperty->GetSelectedBackgroundColorValue();
    result2.color = TextPickerModelNG::GetSelectedBackgroundStyle(frameNode).color;
    EXPECT_EQ(pickerBgStyle.color, result1.color);
    EXPECT_EQ(pickerBgStyle.color, result2.color);
}

/**
 * @tc.name: SelectedBackgroundStyle002
 * @tc.desc: Test GetCanLoopFromLayoutProperty.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerResourceTest, SelectedBackgroundStyle002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPicker.
     */
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);

    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    std::vector<NG::RangeContent> oldRange = { { "", "Text1" }, { "", "Text2" }, { "", "Text3" } };
    TextPickerModelNG::GetInstance()->SetRange(oldRange);
    TextPickerModelNG::GetInstance()->SetSelected(SELECTED_INDEX_1);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Set g_isConfigChangePerform to true.
     */
    g_isConfigChangePerform = true;
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->resourceMgr_ = AceType::MakeRefPtr<PatternResourceManager>();
    ASSERT_NE(pattern->resourceMgr_, nullptr);

    NG::PickerBackgroundStyle pickerBgStyle;
    pickerBgStyle.color = Color::RED;
    pickerBgStyle.borderRadius = NG::BorderRadiusProperty(8.0_vp);
    TextPickerModelNG::GetInstance()->SetSelectedBackgroundStyle(pickerBgStyle);

    NG::PickerBackgroundStyle result1;
    NG::PickerBackgroundStyle result2;
    auto layoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    result1.color = layoutProperty->GetSelectedBackgroundColorValue();
    result1.borderRadius = layoutProperty->GetSelectedBorderRadiusValue();
    result2.color = TextPickerModelNG::GetSelectedBackgroundStyle(frameNode).color;
    result2.borderRadius = TextPickerModelNG::GetSelectedBackgroundStyle(frameNode).borderRadius;
    EXPECT_EQ(pickerBgStyle.color, result1.color);
    EXPECT_EQ(pickerBgStyle.borderRadius, result1.borderRadius);
    EXPECT_EQ(pickerBgStyle.color, result2.color);
    EXPECT_EQ(pickerBgStyle.borderRadius, result2.borderRadius);

    /**
     * @tc.steps: step3. Call ParseBackgroundStyleColorResObj and ParseBackgroundStyleRadiusResObj
     * to register the resourceObject callback function.
     * @tc.expected: Dut to color is set by user, the value will not be changed.
     */
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    pickerBgStyle.textColorSetByUser = true;
    pickerBgStyle.colorResObj = AceType::MakeRefPtr<ResourceObject>();
    pickerBgStyle.borderRadiusResObj = AceType::MakeRefPtr<ResourceObject>();
    TextPickerModelNG::ParseBackgroundStyleColorResObj(frameNode, pickerBgStyle);
    TextPickerModelNG::ParseBackgroundStyleRadiusResObj(frameNode, pickerBgStyle);
    pattern->resourceMgr_->ReloadResources();
    result1.color = layoutProperty->GetSelectedBackgroundColorValue();
    result2.color = TextPickerModelNG::GetSelectedBackgroundStyle(frameNode).color;
    EXPECT_EQ(pickerBgStyle.color, result1.color);
    EXPECT_EQ(pickerBgStyle.color, result2.color);
}

/**
 * @tc.name: SelectedBackgroundStyle003
 * @tc.desc: Test GetCanLoopFromLayoutProperty.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerResourceTest, SelectedBackgroundStyle003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPicker.
     */
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);

    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    std::vector<NG::RangeContent> oldRange = { { "", "Text1" }, { "", "Text2" }, { "", "Text3" } };
    TextPickerModelNG::GetInstance()->SetRange(oldRange);
    TextPickerModelNG::GetInstance()->SetSelected(SELECTED_INDEX_1);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Set g_isConfigChangePerform to true.
     */
    g_isConfigChangePerform = true;
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->resourceMgr_ = AceType::MakeRefPtr<PatternResourceManager>();
    ASSERT_NE(pattern->resourceMgr_, nullptr);

    NG::PickerBackgroundStyle pickerBgStyle;
    pickerBgStyle.color = Color::RED;
    pickerBgStyle.borderRadius = NG::BorderRadiusProperty(8.0_vp);
    TextPickerModelNG::GetInstance()->SetSelectedBackgroundStyle(pickerBgStyle);

    NG::PickerBackgroundStyle result1;
    NG::PickerBackgroundStyle result2;
    auto layoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    result1.color = layoutProperty->GetSelectedBackgroundColorValue();
    result1.borderRadius = layoutProperty->GetSelectedBorderRadiusValue();
    result2.color = TextPickerModelNG::GetSelectedBackgroundStyle(frameNode).color;
    result2.borderRadius = TextPickerModelNG::GetSelectedBackgroundStyle(frameNode).borderRadius;
    EXPECT_EQ(pickerBgStyle.color, result1.color);
    EXPECT_EQ(pickerBgStyle.borderRadius, result1.borderRadius);
    EXPECT_EQ(pickerBgStyle.color, result2.color);
    EXPECT_EQ(pickerBgStyle.borderRadius, result2.borderRadius);

    /**
     * @tc.steps: step3. Call ParseBackgroundStyleColorResObj and ParseBackgroundStyleRadiusResObj
     * to register the resourceObject callback function.
     * @tc.expected: Dut to color is not set by user, the value will not be changed.
     */
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    pickerBgStyle.textColorSetByUser = false;
    pickerBgStyle.colorResObj = AceType::MakeRefPtr<ResourceObject>();
    pickerBgStyle.borderRadiusResObj = AceType::MakeRefPtr<ResourceObject>();
    TextPickerModelNG::ParseBackgroundStyleColorResObj(frameNode, pickerBgStyle);
    TextPickerModelNG::ParseBackgroundStyleRadiusResObj(frameNode, pickerBgStyle);
    pattern->resourceMgr_->ReloadResources();
    Color newColor = theme->GetSelectedBackgroundColor();
    result1.color = layoutProperty->GetSelectedBackgroundColorValue();
    result2.color = TextPickerModelNG::GetSelectedBackgroundStyle(frameNode).color;
    EXPECT_EQ(newColor, result1.color);
    EXPECT_EQ(newColor, result2.color);
    EXPECT_NE(newColor, pickerBgStyle.color);
}

} // namespace OHOS::Ace::NG