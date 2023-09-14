/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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
#include <optional>
#include <string>

#include "gtest/gtest.h"

#define protected public
#define private public
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
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/option/option_pattern.h"
#include "core/components_ng/pattern/select/select_model_ng.h"
#include "core/components_ng/pattern/select/select_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace::NG {
namespace {
const int32_t OFFSETX = 10;
const int32_t OFFSETY = 20;
constexpr int32_t SELECT_ERROR = -1;
constexpr int32_t CURRENT_INDEX = 10;
const std::string EMPTY_TEXT = "";
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
class SelectPropertyTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
    void InitSelectTestNg();
    RefPtr<FrameNode> frameNode_;
    RefPtr<SelectPattern> selectPattern_;
    RefPtr<SelectAccessibilityProperty> selectAccessibilityProperty_;

protected:
    static RefPtr<FrameNode> CreateSelect(const std::vector<SelectParam>& value, const TestProperty& test);
};

void SelectPropertyTestNg::SetUpTestCase()
{
    MockPipelineBase::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
}

void SelectPropertyTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
}

void SelectPropertyTestNg::SetUp() {}

void SelectPropertyTestNg::TearDown()
{
    frameNode_ = nullptr;
    selectPattern_ = nullptr;
    selectAccessibilityProperty_ = nullptr;
}

void SelectPropertyTestNg::InitSelectTestNg()
{
    frameNode_ = FrameNode::GetOrCreateFrameNode(V2::SELECT_ETS_TAG, ViewStackProcessor::GetInstance()->ClaimNodeId(),
        []() { return AceType::MakeRefPtr<SelectPattern>(); });
    ASSERT_NE(frameNode_, nullptr);

    selectPattern_ = frameNode_->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern_, nullptr);

    selectAccessibilityProperty_ = frameNode_->GetAccessibilityProperty<SelectAccessibilityProperty>();
    ASSERT_NE(selectAccessibilityProperty_, nullptr);
}

RefPtr<FrameNode> SelectPropertyTestNg::CreateSelect(const std::vector<SelectParam>& value, const TestProperty& test)
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
 * @tc.name: SelectLayoutPropertyTest001
 * @tc.desc: Create Select.
 * @tc.type: FUNC
 */
HWTEST_F(SelectPropertyTestNg, SelectLayoutPropertyTest001, TestSize.Level1)
{
    SelectModelNG selectModelInstance;

    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE }, { OPTION_TEXT, INTERNAL_SOURCE },
        { OPTION_TEXT_2, INTERNAL_SOURCE } };
    selectModelInstance.Create(params);
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_TRUE(select && select->GetTag() == V2::SELECT_ETS_TAG);
    auto pattern = select->GetPattern<SelectPattern>();
    EXPECT_TRUE(pattern);

    auto options = pattern->GetOptions();
    EXPECT_EQ(options.size(), params.size());
    for (size_t i = 0; i < options.size(); ++i) {
        auto optionPattern = options[i]->GetPattern<OptionPattern>();
        EXPECT_EQ(optionPattern->GetText(), params[i].first);
    }
}

/**
 * @tc.name: SelectLayoutPropertyTest002
 * @tc.desc: Test Select OnDirtyLayoutWrapperSwap.
 * @tc.type: FUNC
 */
HWTEST_F(SelectPropertyTestNg, SelectLayoutPropertyTest002, TestSize.Level1)
{
    SelectModelNG selectModelInstance;

    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE }, { OPTION_TEXT, INTERNAL_SOURCE },
        { OPTION_TEXT_2, INTERNAL_SOURCE } };
    selectModelInstance.Create(params);
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_TRUE(select && select->GetTag() == V2::SELECT_ETS_TAG);
    auto pattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(pattern, nullptr);

    DirtySwapConfig config;
    config.skipMeasure = true;
    auto layoutWrapper = select->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    EXPECT_FALSE(pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config));
}

/**
 * @tc.name: SelectLayoutPropertyTest003
 * @tc.desc: Test Select Layout Algorithm MeasureAndGetSize width.
 * @tc.type: FUNC
 */
HWTEST_F(SelectPropertyTestNg, SelectLayoutPropertyTest003, TestSize.Level1)
{
    auto text = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_TRUE(text);

    auto textProps = text->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_TRUE(textProps);
    MarginProperty margin;
    margin.left = MARGIN_LENGTH;
    textProps->UpdateMargin(margin);
    textProps->UpdateUserDefinedIdealSize(TEXT_IDEAL_SIZE);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(text, geometryNode, text->GetLayoutProperty());

    LayoutConstraintF constraint;
    constraint.maxSize = FULL_SCREEN_SIZE;
    constraint.percentReference = FULL_SCREEN_SIZE;

    auto layoutAlgorithm = AceType::MakeRefPtr<SelectLayoutAlgorithm>();
    auto size = layoutAlgorithm->MeasureAndGetSize(layoutWrapper, constraint);
    auto expectWidth =
        MARGIN_LENGTH.GetDimension().ConvertToPx() + TEXT_IDEAL_SIZE.Width()->GetDimension().ConvertToPx();
    EXPECT_EQ(size.Width(), static_cast<float>(expectWidth));
}

/**
 * @tc.name: SelectSetMenuAlign001
 * @tc.desc: Test SelectSetMenuAlign
 * @tc.type: FUNC
 */
HWTEST_F(SelectPropertyTestNg, SelectSetMenuAlign001, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    // create select
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE }, { OPTION_TEXT, INTERNAL_SOURCE },
        { OPTION_TEXT_2, INTERNAL_SOURCE } };
    selectModelInstance.Create(params);
    MenuAlign menuAlign;
    /**
     * @tc.cases: case1. verify the SetMenuAlign function.
     */
    menuAlign.alignType = MenuAlignType::END;
    menuAlign.offset = DimensionOffset(Dimension(OFFSETX, DimensionUnit::VP), Dimension(OFFSETY, DimensionUnit::VP));
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_TRUE(select->GetChildren().empty());
    EXPECT_TRUE(select && select->GetTag() == V2::SELECT_ETS_TAG);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    /**
     * @tc.cases: case1. verify the SetMenuAlign function.
     */
    selectPattern->SetMenuAlign(menuAlign);
    auto menuAlign2 = selectPattern->menuAlign_.alignType;
    auto menuAlign3 = selectPattern->menuAlign_.offset;
    ASSERT_EQ(menuAlign.alignType, menuAlign2);
    ASSERT_EQ(menuAlign.offset, menuAlign3);
}
/**
 * @tc.name: SelectEvent001
 * @tc.desc: Test SelectPattern PlayBgColorAnimation and OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(SelectPropertyTestNg, SelectEvent001, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    /**
     * @tc.steps: step1. Create select.
     */
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE }, { OPTION_TEXT_2, INTERNAL_SOURCE },
        { OPTION_TEXT_3, INTERNAL_SOURCE } };
    selectModelInstance.Create(params);
    /**
     * @tc.steps: step2. Get frameNode and pattern.
     */
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    /**
     * @tc.steps: step3. Call PlayBgColorAnimation.
     * @tc.expected: the function runs normally
     */
    bool isHoverChange[2] = { false, true };
    for (int turn = 0; turn < 2; turn++) {
        selectPattern->PlayBgColorAnimation(isHoverChange[turn]);
        EXPECT_EQ(selectPattern->options_.size(), params.size());
    }
    /**
     * @tc.steps: step4. construct keyEvent.
     * @tc.expected: the function runs normally
     */
    KeyEvent event;
    EXPECT_FALSE(selectPattern->OnKeyEvent(event));
    event.action = KeyAction::DOWN;
    EXPECT_FALSE(selectPattern->OnKeyEvent(event));
    event.code = KeyCode::KEY_ENTER;
    EXPECT_TRUE(selectPattern->OnKeyEvent(event));
}
/**
 * @tc.name: OnModifyDone001
 * @tc.desc: Test SelectPattern OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(SelectPropertyTestNg, OnModifyDone001, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    /**
     * @tc.steps: step1. Create select.
     */
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE }, { OPTION_TEXT_2, INTERNAL_SOURCE },
        { OPTION_TEXT_3, INTERNAL_SOURCE } };
    selectModelInstance.Create(params);
    /**
     * @tc.steps: step2. Get frameNode and pattern.
     */
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    /**
     * @tc.steps: step3. Call OnModifyDone.
     * @tc.expected: the function runs normally
     */
    selectPattern->OnModifyDone();
    auto host = selectPattern->GetHost();
    EXPECT_NE(host->GetEventHub<SelectEventHub>(), nullptr);
}
/**
 * @tc.name: UpdateSelectedProps001
 * @tc.desc: Test SelectPattern UpdateSelectedProps
 * @tc.type: FUNC
 */
HWTEST_F(SelectPropertyTestNg, UpdateSelectedProps001, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    /**
     * @tc.steps: step1. Create select.
     */
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE }, { OPTION_TEXT_2, INTERNAL_SOURCE },
        { OPTION_TEXT_3, INTERNAL_SOURCE } };
    selectModelInstance.Create(params);
    /**
     * @tc.steps: step2. Get frameNode and pattern.
     */
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    /**
     * @tc.steps: step3. not selected.
     * @tc.expected: the function of SetSelectedOptionFontFamily exits normally
     */
    selectPattern->SetSelectedOptionFontFamily(FONT_FAMILY_VALUE);
    EXPECT_EQ(selectPattern->GetSelected(), -1);
    /**
     * @tc.steps: step4. select first option.
     * @tc.expected: the font family of first option is setted successfully
     */
    selectPattern->SetSelected(0);
    EXPECT_EQ(selectPattern->GetSelected(), 0);
    selectPattern->SetSelectedOptionFontFamily(FONT_FAMILY_VALUE);
    selectPattern->UpdateSelectedProps(0);
    EXPECT_EQ(selectPattern->selectedFont_.FontFamily, FONT_FAMILY_VALUE);
    /**
     * @tc.steps: step5. Invalid selection or repeated selection.
     * @tc.expected: the function of SetSelected exits normally
     */
    selectPattern->SetSelected(0);
    EXPECT_EQ(selectPattern->GetSelected(), 0);
    selectPattern->SetSelected(4);
    EXPECT_EQ(selectPattern->GetSelected(), -1);
}
/**
 * @tc.name: UpdateSelectedProps002
 * @tc.desc: Test SelectPattern UpdateSelectedProps
 * @tc.type: FUNC
 */
HWTEST_F(SelectPropertyTestNg, UpdateSelectedProps002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize testProperty and Create select frameNode.
     */
    TestProperty testProperty;
    testProperty.FontSize = std::make_optional(FONT_SIZE_VALUE);
    testProperty.FontStyle = std::make_optional(ITALIC_FONT_STYLE_VALUE);
    testProperty.FontWeight = std::make_optional(FONT_WEIGHT_VALUE);
    testProperty.FontColor = std::make_optional(TEXT_COLOR_VALUE);
    auto frameNode = CreateSelect(CREATE_VALUE, testProperty);
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. Get pattern.
     */
    auto selectPattern = frameNode->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    /**
     * @tc.steps: step3. select option.
     * @tc.expected: text style is updated when selected
     */
    selectPattern->SetSelected(1);
    selectPattern->SetSelectedOptionFontColor(TEXT_COLOR_VALUE);
    selectPattern->SetSelectedOptionFontWeight(FONT_WEIGHT_VALUE);
    selectPattern->SetSelectedOptionItalicFontStyle(ITALIC_FONT_STYLE_VALUE);
    selectPattern->SetSelectedOptionFontSize(FONT_SIZE_VALUE);
    selectPattern->selectedBgColor_ = BG_COLOR_VALUE;
    selectPattern->UpdateSelectedProps(1);
    EXPECT_NE(selectPattern->selectedFont_.FontFamily, FONT_FAMILY_VALUE);
    EXPECT_EQ(selectPattern->selectedFont_.FontSize, FONT_SIZE_VALUE);
    EXPECT_EQ(selectPattern->selectedFont_.FontStyle, ITALIC_FONT_STYLE_VALUE);
    EXPECT_EQ(selectPattern->selectedFont_.FontWeight, FONT_WEIGHT_VALUE);
    EXPECT_EQ(selectPattern->selectedFont_.FontColor, TEXT_COLOR_VALUE);
}
/**
 * @tc.name: SelectLayoutPropertyTest004
 * @tc.desc: Test SetSelectOptionFont.
 * @tc.type: FUNC
 */
HWTEST_F(SelectPropertyTestNg, SelectLayoutPropertyTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get frameNode and pattern.
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
    EXPECT_TRUE(pattern);
    /**
     * @tc.steps: step2. Get options and Set optionFont.
     * @tc.expected: option style is updated successfully
     */
    auto options = pattern->GetOptions();
    EXPECT_EQ(options.size(), CREATE_VALUE.size());
    for (size_t i = 0; i < options.size(); ++i) {
        pattern->SetSelected(i);
        auto optionPattern = options[i]->GetPattern<OptionPattern>();
        optionPattern->selectTheme_ = AceType::MakeRefPtr<SelectTheme>();
        optionPattern->textTheme_ = AceType::MakeRefPtr<TextTheme>();
        EXPECT_EQ(optionPattern->GetText(), CREATE_VALUE[i].first);
        pattern->SetOptionBgColor(BG_COLOR_VALUE);
        EXPECT_EQ(optionPattern->bgColor_, BG_COLOR_VALUE);
        pattern->SetOptionFontFamily(FONT_FAMILY_VALUE);
        pattern->SetOptionFontSize(FONT_SIZE_VALUE);
        pattern->SetOptionItalicFontStyle(ITALIC_FONT_STYLE_VALUE);
        pattern->SetOptionFontColor(TEXT_COLOR_VALUE);
        pattern->SetOptionFontWeight(FONT_WEIGHT_VALUE);
        EXPECT_EQ(optionPattern->GetFontColor(), TEXT_COLOR_VALUE);
        EXPECT_EQ(optionPattern->GetFontSize(), FONT_SIZE_VALUE);
        EXPECT_EQ(optionPattern->GetFontFamily(), FONT_FAMILY_VALUE);
        EXPECT_EQ(optionPattern->GetItalicFontStyle(), ITALIC_FONT_STYLE_VALUE);
        EXPECT_EQ(optionPattern->GetFontWeight(), FONT_WEIGHT_VALUE);
        pattern->InitSelected();
    }
}
/**
 * @tc.name: ShowSelectMenuTest001
 * @tc.desc: Test SelectPattern ShowSelectMenu.
 * @tc.type: FUNC
 */
HWTEST_F(SelectPropertyTestNg, ShowSelectMenuTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get frameNode and pattern.
     */
    TestProperty testProperty;
    testProperty.FontSize = std::make_optional(FONT_SIZE_VALUE);
    auto frameNode = CreateSelect(CREATE_VALUE, testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SelectPattern>();
    EXPECT_TRUE(pattern);
    /**
     * @tc.steps: step2. call ShowSelectMenu function.
     * @tc.expected: the function exits normally
     */
    pattern->ShowSelectMenu();
    auto offset = pattern->GetHost()->GetPaintRectOffset();
    EXPECT_EQ(offset.GetY(), pattern->selectSize_.Height());
}
/**
 * @tc.name: SelectLayoutPropertyTest005
 * @tc.desc: Test Select Layout Algorithm Measure.
 * @tc.type: FUNC
 */
HWTEST_F(SelectPropertyTestNg, SelectLayoutPropertyTest005, TestSize.Level1)
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
    auto layoutAlgorithm = AceType::MakeRefPtr<SelectLayoutAlgorithm>();
    layoutAlgorithm->Measure(layoutWrapper);
    auto rowWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    EXPECT_EQ(rowWrapper, nullptr);
}

/**
 * @tc.name: SelectDistributedTest001
 * @tc.desc: Test the distributed capability of Select.
 * @tc.type: FUNC
 */
HWTEST_F(SelectPropertyTestNg, SelectDistributedTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init select node
     */
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_TRUE(select && select->GetTag() == V2::SELECT_ETS_TAG);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);

    /**
     * @tc.steps: step2. Get pattern and set value.
     * @tc.expected: Function ProvideRestoreInfo is called.
     */
    selectPattern->selected_ = 2;
    selectPattern->isSelected_ = false;
    std::string ret = selectPattern->ProvideRestoreInfo();
    EXPECT_TRUE(ret == R"({"selected":2,"isSelected":false})");

    /**
     * @tc.steps: step3. Function OnRestoreInfo is called.
     * @tc.expected: Passing invalid & valid JSON format.
     */
    std::string restoreInfo_ = R"({"selected":2,"isSelected":false})";
    selectPattern->OnRestoreInfo(restoreInfo_);
    EXPECT_EQ(selectPattern->GetSelected(), 2);
    restoreInfo_ = R"({"selected":2,"isSelected":true})";
    selectPattern->OnRestoreInfo(restoreInfo_);
    EXPECT_EQ(selectPattern->GetSelected(), 2);
    restoreInfo_ = "invalid_json_string";
    selectPattern->OnRestoreInfo(restoreInfo_);
    EXPECT_EQ(selectPattern->GetSelected(), 2);
}

/**
 * @tc.name: SelectAccessibilityPropertyGetCurrentIndex001
 * @tc.desc: Test GetCurrentIndex of select.
 * @tc.type: FUNC
 */
HWTEST_F(SelectPropertyTestNg, SelectAccessibilityPropertyGetCurrentIndex001, TestSize.Level1)
{
    InitSelectTestNg();

    EXPECT_EQ(selectAccessibilityProperty_->GetCurrentIndex(), SELECT_ERROR);

    selectPattern_->selected_ = CURRENT_INDEX;
    EXPECT_EQ(selectAccessibilityProperty_->GetCurrentIndex(), CURRENT_INDEX);
}

/**
 * @tc.name: SelectAccessibilityPropertyGetBeginIndex001
 * @tc.desc: Test GetBeginIndex of select.
 * @tc.type: FUNC
 */
HWTEST_F(SelectPropertyTestNg, SelectAccessibilityPropertyGetBeginIndex001, TestSize.Level1)
{
    InitSelectTestNg();

    EXPECT_EQ(selectAccessibilityProperty_->GetBeginIndex(), SELECT_ERROR);

    auto option = FrameNode::GetOrCreateFrameNode(V2::OPTION_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<OptionPattern>(0); });
    ASSERT_NE(option, nullptr);

    selectPattern_->options_.push_back(option);
    EXPECT_EQ(selectAccessibilityProperty_->GetBeginIndex(), 0);
}

/**
 * @tc.name: SelectAccessibilityPropertyGetEndIndex001
 * @tc.desc: Test GetEndIndex of select.
 * @tc.type: FUNC
 */
HWTEST_F(SelectPropertyTestNg, SelectAccessibilityPropertyGetEndIndex001, TestSize.Level1)
{
    InitSelectTestNg();

    EXPECT_EQ(selectAccessibilityProperty_->GetEndIndex(), SELECT_ERROR);

    auto option = FrameNode::GetOrCreateFrameNode(V2::OPTION_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<OptionPattern>(0); });
    ASSERT_NE(option, nullptr);

    selectPattern_->options_.push_back(option);
    selectPattern_->options_.push_back(option);
    EXPECT_EQ(selectAccessibilityProperty_->GetEndIndex(), 1);
}

/**
 * @tc.name: SelectAccessibilityPropertyGetText001
 * @tc.desc: Test GetText of select.
 * @tc.type: FUNC
 */
HWTEST_F(SelectPropertyTestNg, SelectAccessibilityPropertyGetText001, TestSize.Level1)
{
    InitSelectTestNg();

    EXPECT_EQ(selectAccessibilityProperty_->GetText(), EMPTY_TEXT);

    selectPattern_->text_ = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(selectPattern_->text_, nullptr);

    selectPattern_->SetValue(SELECT_TEXT);
    EXPECT_EQ(selectAccessibilityProperty_->GetText(), SELECT_TEXT);
}

/**
 * @tc.name: SelectAccessibilityPropertyGetCollectionItemCounts001
 * @tc.desc: Test GetCollectionItemCounts of select.
 * @tc.type: FUNC
 */
HWTEST_F(SelectPropertyTestNg, SelectAccessibilityPropertyGetCollectionItemCounts001, TestSize.Level1)
{
    InitSelectTestNg();

    EXPECT_EQ(selectAccessibilityProperty_->GetCollectionItemCounts(), SELECT_ERROR);

    auto option = FrameNode::GetOrCreateFrameNode(V2::OPTION_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<OptionPattern>(0); });
    ASSERT_NE(option, nullptr);

    for (int i = 0; i < CURRENT_INDEX; i++) {
        selectPattern_->options_.push_back(option);
    }
    EXPECT_EQ(selectAccessibilityProperty_->GetCollectionItemCounts(), CURRENT_INDEX);
}

/**
 * @tc.name: SelectSetSpaceTest001
 * @tc.desc: setSpace
 * @tc.type: FUNC
 */
HWTEST_F(SelectPropertyTestNg, SelectSetSpaceTest001, TestSize.Level1)
{
    SelectModelNG selectModelInstance;

    auto select = FrameNode::GetOrCreateFrameNode(V2::SELECT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<SelectPattern>(); });
    ASSERT_NE(select, nullptr);

    auto row = FrameNode::GetOrCreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    ASSERT_NE(row, nullptr);

    auto text = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(text, nullptr);

    auto spinner = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(spinner, nullptr);

    text->MountToParent(row);
    spinner->MountToParent(row);
    row->MountToParent(select);
    ViewStackProcessor::GetInstance()->Push(select);

    selectModelInstance.SetSpace(Dimension(20.00, DimensionUnit::VP));
    ASSERT_FALSE(select->GetChildren().empty());
    row = FrameNode::GetFrameNode(select->GetFirstChild()->GetTag(), select->GetFirstChild()->GetId());
    ASSERT_NE(row, nullptr);
    auto rowProps = row->GetLayoutProperty<FlexLayoutProperty>();
    ASSERT_NE(rowProps, nullptr);
    ASSERT_TRUE(rowProps->GetSpace()->Value() == 20);
}

/**
 * @tc.name: SelectSetArrowPositionTest001
 * @tc.desc: Test SetArrowPosition
 * @tc.type: FUNC
 */
HWTEST_F(SelectPropertyTestNg, SelectSetArrowPositionTest001, TestSize.Level1)
{
    SelectModelNG selectModelInstance;

    auto select = FrameNode::GetOrCreateFrameNode(V2::SELECT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<SelectPattern>(); });
    ASSERT_NE(select, nullptr);

    auto row = FrameNode::GetOrCreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    ASSERT_NE(row, nullptr);

    auto text = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(text, nullptr);

    auto spinner = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(spinner, nullptr);

    text->MountToParent(row);
    spinner->MountToParent(row);
    row->MountToParent(select);
    ViewStackProcessor::GetInstance()->Push(select);

    selectModelInstance.SetArrowPosition(ArrowPosition::END);
    ASSERT_FALSE(select->GetChildren().empty());
    row = FrameNode::GetFrameNode(select->GetFirstChild()->GetTag(), select->GetFirstChild()->GetId());
    ASSERT_NE(row, nullptr);
    auto rowProps = row->GetLayoutProperty<FlexLayoutProperty>();
    ASSERT_STREQ(V2::ConvertFlexDirectionToStirng(rowProps->GetFlexDirection().value()).c_str(), "FlexDirection.Row");

    selectModelInstance.SetArrowPosition(ArrowPosition::START);
    ASSERT_FALSE(select->GetChildren().empty());
    row = FrameNode::GetFrameNode(select->GetFirstChild()->GetTag(), select->GetFirstChild()->GetId());
    ASSERT_NE(row, nullptr);
    rowProps = row->GetLayoutProperty<FlexLayoutProperty>();
    ASSERT_STREQ(
        V2::ConvertFlexDirectionToStirng(rowProps->GetFlexDirection().value()).c_str(), "FlexDirection.RowReverse");
}

/**
 * @tc.name: SelectSetArrowPositionTest002
 * @tc.desc: Test SetArrowPosition
 * @tc.type: FUNC
 */
HWTEST_F(SelectPropertyTestNg, SelectSetArrowPositionTest002, TestSize.Level1)
{
    SelectModelNG selectModelInstance;

    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE }, { OPTION_TEXT, INTERNAL_SOURCE },
        { OPTION_TEXT_2, INTERNAL_SOURCE } };
    selectModelInstance.Create(params);
    selectModelInstance.SetArrowPosition(ArrowPosition::END);
    selectModelInstance.SetSpace(Dimension(20.00, DimensionUnit::VP));
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_TRUE(select->GetChildren().empty());
}

/**
 * @tc.name: CreateMenu001
 * @tc.desc: Test create menu
 * @tc.type: FUNC
 */
HWTEST_F(SelectPropertyTestNg, CreateMenu001, TestSize.Level1)
{
    SelectModelNG selectModelInstance;

    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(100);
    selectModelInstance.Create(params);
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto pattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(pattern->GetMenuNode(), nullptr);

    // Create again
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(100);
    selectModelInstance.Create(params);
    select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    pattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(pattern->GetMenuNode(), nullptr);
}

/**
 * @tc.name: OnColorConfigurationUpdate001
 * @tc.desc: Test on color configuration update
 * @tc.type: FUNC
 */
HWTEST_F(SelectPropertyTestNg, OnColorConfigurationUpdate001, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE }, { OPTION_TEXT_2, INTERNAL_SOURCE },
        { OPTION_TEXT_3, INTERNAL_SOURCE } };
    selectModelInstance.Create(params);
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto selectTheme = pipeline->GetTheme<SelectTheme>();
    ASSERT_NE(selectTheme, nullptr);
    selectTheme->backgroundColor_ = Color::BLACK;
    selectPattern->OnColorConfigurationUpdate();
    EXPECT_TRUE(selectPattern->isColorConfigurationUpdate_);
    auto menuNode = selectPattern->GetMenuNode();
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    auto renderContext = menuNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetBackgroundColor(), Color::BLACK);
}

/**
 * @tc.name: SelectModel001
 * @tc.desc: Test Select Model
 * @tc.type: FUNC
 */
HWTEST_F(SelectPropertyTestNg, SelectModel001, TestSize.Level1)
{
    SelectModelNG selectModelInstance;

    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(100);
    selectModelInstance.Create(params);
    selectModelInstance.SetSelected(0);
    selectModelInstance.SetValue("select");
    selectModelInstance.SetFontSize(Dimension(20.00, DimensionUnit::VP));
    selectModelInstance.SetFontWeight(FontWeight::NORMAL);
    selectModelInstance.SetItalicFontStyle(Ace::FontStyle::NORMAL);
    selectModelInstance.SetFontColor(Color::BLACK);
    selectModelInstance.SetSelectedOptionBgColor(Color::BLACK);
    selectModelInstance.SetSelectedOptionFontSize(Dimension(20.00, DimensionUnit::VP));
    selectModelInstance.SetSelectedOptionFontWeight(FontWeight::NORMAL);
    selectModelInstance.SetSelectedOptionItalicFontStyle(Ace::FontStyle::NORMAL);
    selectModelInstance.SetSelectedOptionFontColor(Color::BLACK);
    selectModelInstance.SetOptionBgColor(Color::BLACK);
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto pattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(pattern->GetMenuNode(), nullptr);
}

/**
 * @tc.name: SelectModel002
 * @tc.desc: Test Select Model
 * @tc.type: FUNC
 */
HWTEST_F(SelectPropertyTestNg, SelectModel002, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    SelectEvent eventOnSelect = [](int32_t intValue, const std::string& isSelect) {};
    CalcDimension width = 20.0_vp;
    CalcDimension height = 20.0_vp;
    CalcDimension top = 20.0_vp;
    CalcDimension bottom = 20.0_vp;
    CalcDimension left = 20.0_vp;
    CalcDimension right = 20.0_vp;

    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(100);
    selectModelInstance.SetOptionFontSize(Dimension(20.00, DimensionUnit::VP));
    selectModelInstance.SetOptionFontWeight(FontWeight::NORMAL);
    selectModelInstance.SetOptionItalicFontStyle(Ace::FontStyle::NORMAL);
    selectModelInstance.SetOptionFontColor(Color::BLACK);
    selectModelInstance.SetOnSelect(std::move(eventOnSelect));
    selectModelInstance.SetWidth(width);
    selectModelInstance.SetHeight(height);
    selectModelInstance.SetSize(width, height);
    selectModelInstance.SetPaddings(top, bottom, left, right);
    selectModelInstance.SetPadding(CalcDimension(20.00, DimensionUnit::VP));
    selectModelInstance.SetPaddingLeft(CalcDimension(20.00, DimensionUnit::VP));
    selectModelInstance.SetPaddingTop(CalcDimension(20.00, DimensionUnit::VP));
    selectModelInstance.SetPaddingRight(CalcDimension(20.00, DimensionUnit::VP));
    selectModelInstance.SetPaddingBottom(CalcDimension(20.00, DimensionUnit::VP));
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto pattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(pattern->GetMenuNode(), nullptr);
}

/**
 * @tc.name: SelectModel003
 * @tc.desc: Test Select Model
 * @tc.type: FUNC
 */
HWTEST_F(SelectPropertyTestNg, SelectModel003, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    SelectEvent eventOnSelect = [](int32_t intValue, const std::string& isSelect) {};
    CalcDimension width = -20.0_vp;
    CalcDimension height = -20.0_vp;
    CalcDimension top = -20.0_vp;
    CalcDimension bottom = -20.0_vp;
    CalcDimension left = -20.0_vp;
    CalcDimension right = -20.0_vp;

    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(100);

    selectModelInstance.SetWidth(width);
    selectModelInstance.SetHeight(height);
    selectModelInstance.SetSize(width, height);
    selectModelInstance.SetPaddings(top, bottom, left, right);
    selectModelInstance.SetPadding(CalcDimension(20.00, DimensionUnit::VP));
    selectModelInstance.SetPaddingLeft(CalcDimension(20.00, DimensionUnit::VP));
    selectModelInstance.SetPaddingTop(CalcDimension(20.00, DimensionUnit::VP));
    selectModelInstance.SetPaddingRight(CalcDimension(20.00, DimensionUnit::VP));
    selectModelInstance.SetPaddingBottom(CalcDimension(20.00, DimensionUnit::VP));
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto pattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(pattern->GetMenuNode(), nullptr);
}

/**
 * @tc.name: SelectModel004
 * @tc.desc: Test Select Model
 * @tc.type: FUNC
 */
HWTEST_F(SelectPropertyTestNg, SelectModel004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectModelInstance.
     */
    SelectModelNG selectModelInstance;
    SelectEvent eventOnSelect = [](int32_t intValue, const std::string& isSelect) {};

    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(100);
    selectModelInstance.Create(params);
    /**
     * @tc.steps: step2. initialize paddings.
     * @tc.steps: the values of select which is setted successfully.
     */
    CalcDimension calcDimension(DEFAULT_STR);
    CalcDimension width = -20.0_vp;
    CalcDimension height = -20.0_vp;
    selectModelInstance.SetSize(width, height);
    selectModelInstance.SetPaddingLeft(CalcDimension(DEFAULT_STR));
    selectModelInstance.SetPaddingTop(CalcDimension(DEFAULT_STR));
    selectModelInstance.SetPaddingRight(CalcDimension(DEFAULT_STR));
    selectModelInstance.SetPaddingBottom(CalcDimension(DEFAULT_STR));
    selectModelInstance.SetPaddings(calcDimension, calcDimension, calcDimension, calcDimension);
    selectModelInstance.SetPadding(calcDimension);
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto pattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(pattern, nullptr);
    auto menu = pattern->GetMenuNode();
    ASSERT_NE(menu, nullptr);
    EXPECT_EQ(width.Value(), 0.0);
    EXPECT_EQ(height.Value(), 0.0);
}
} // namespace OHOS::Ace::NG
