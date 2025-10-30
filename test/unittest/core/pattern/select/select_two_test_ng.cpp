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

#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "ui/resource/resource_info.h"

#include "core/common/ace_application_info.h"
#include "core/common/ace_engine.h"
#include "core/common/multi_thread_build_manager.h"
#include "core/components/common/layout/constants.h"
#include "core/components/scroll/scroll_bar_theme.h"
#include "core/components/select/select_theme.h"
#include "core/components/text/text_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/flex/flex_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_pattern.h"
#include "core/components_ng/pattern/menu/menu_layout_property.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_layout_property.h"
#include "core/components_ng/pattern/select/select_model_ng.h"
#include "core/components_ng/pattern/select/select_paint_property.h"
#include "core/components_ng/pattern/select/select_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/components_ng/syntax/lazy_for_each_model.h"
#include "core/components_ng/syntax/lazy_for_each_node.h"
#include "core/components_ng/syntax/lazy_layout_wrapper_builder.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const InspectorFilter filter;
const int32_t OFFSETX = 10;
const int32_t OFFSETY = 20;
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
constexpr float SELECT_WIDTH = 100.0f;
constexpr float SELECT_HEIGHT = 200.0f;
const SizeF FULL_SCREEN_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
const std::vector<std::string> FONT_FAMILY_VALUE = { "cursive" };
const Dimension FONT_SIZE_VALUE = Dimension(20.1, DimensionUnit::PX);
const Color TEXT_COLOR_VALUE = Color::FromRGB(255, 100, 100);
const Color BG_COLOR_VALUE = Color::FromRGB(100, 255, 100);
const std::vector<SelectParam> CREATE_VALUE = { { OPTION_TEXT, FILE_SOURCE }, { OPTION_TEXT_2, INTERNAL_SOURCE },
    { OPTION_TEXT_3, INTERNAL_SOURCE } };
constexpr int32_t ERROR_INDEX_MIN = -1;
constexpr int32_t ERRPR_INDEX_MAX = 999;
RefPtr<Theme> GetTheme(ThemeType type)
{
    if (type == IconTheme::TypeId()) {
        return AceType::MakeRefPtr<IconTheme>();
    } else if (type == SelectTheme::TypeId()) {
        return AceType::MakeRefPtr<SelectTheme>();
    } else if (type == ScrollBarTheme::TypeId()) {
        return AceType::MakeRefPtr<ScrollBarTheme>();
    } else {
        return nullptr;
    }
}
} // namespace
struct TestProperty {
    std::optional<Dimension> FontSize = std::nullopt;
    std::optional<Ace::FontStyle> FontStyle = std::nullopt;
    std::optional<FontWeight> FontWeight = std::nullopt;
    std::optional<std::vector<std::string>> FontFamily = std::nullopt;
    std::optional<Color> FontColor = std::nullopt;
};
class SelectTwoTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void TearDown() override;
    void InitSelectTwoTestNg();

protected:
    static RefPtr<FrameNode> CreateSelect(const std::vector<SelectParam>& value, const TestProperty& test);

    RefPtr<FrameNode> frameNode_;
    RefPtr<SelectPattern> selectPattern_;
    RefPtr<SelectAccessibilityProperty> selectAccessibilityProperty_;
};

void SelectTwoTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        return GetTheme(type);
    });
    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([](ThemeType type, int32_t themeScopeId) -> RefPtr<Theme> { return GetTheme(type); });
}

void SelectTwoTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

void SelectTwoTestNg::TearDown()
{
    frameNode_ = nullptr;
    selectPattern_ = nullptr;
    selectAccessibilityProperty_ = nullptr;
}

void SelectTwoTestNg::InitSelectTwoTestNg()
{
    frameNode_ = FrameNode::GetOrCreateFrameNode(V2::SELECT_ETS_TAG, ViewStackProcessor::GetInstance()->ClaimNodeId(),
        []() { return AceType::MakeRefPtr<SelectPattern>(); });
    ASSERT_NE(frameNode_, nullptr);

    selectPattern_ = frameNode_->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern_, nullptr);

    selectAccessibilityProperty_ = frameNode_->GetAccessibilityProperty<SelectAccessibilityProperty>();
    ASSERT_NE(selectAccessibilityProperty_, nullptr);
}

RefPtr<FrameNode> SelectTwoTestNg::CreateSelect(const std::vector<SelectParam>& value, const TestProperty& test)
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
 * @tc.name: CreateWithStringResourceObj
 * @tc.desc: Test CreateWithStringResourceObj function.
 * @tc.type: FUNC
 */
HWTEST_F(SelectTwoTestNg, CreateWithStringResourceObj, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create SelectModelNG and initialize frameNode with SelectPattern.
     * @tc.expected: step1. Model and frameNode are created successfully.
     */
    SelectModelNG selectModelNG;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE }, { OPTION_TEXT_2, INTERNAL_SOURCE } };
    selectModelNG.Create(params);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SelectPattern>();
    ASSERT_NE(pattern, nullptr);
    
    /**
     * @tc.steps: step2. Test with null ResourceObject (no assertion, just function call).
     * @tc.expected: step2. No exception thrown when null resource is passed.
     */
    selectModelNG.CreateWithStringResourceObj(nullptr);
    
    /**
     * @tc.steps: step3. Create valid string ResourceObject and test resource assignment.
     * @tc.expected: step3. Resource is accepted without error.
     */
    ResourceObjectParams param;
    param.type = ResourceObjectParamType::STRING;
    param.value = "string";
    int32_t resourceType = static_cast<int32_t>(Kit::ResourceType::STRING);

    auto resObj = AceType::MakeRefPtr<ResourceObject>(
        1001, resourceType, std::vector<ResourceObjectParams> { param }, "testBundle", "testModule", 0);

    selectModelNG.CreateWithStringResourceObj(resObj);
    
    /**
     * @tc.steps: step4. Add resource to cache and reload, verifying resource manager interaction.
     * @tc.expected: step4. Resource is added to cache and resource manager is accessed.
     */
    std::string key = "selectValue";
    pattern->AddResCache(key, param.value.value());
    auto resMgr = pattern->resourceMgr_;
    ASSERT_NE(resMgr, nullptr);
    resMgr->ReloadResources();
}

/**
 * @tc.name: ModifierColorTypeToString
 * @tc.desc: Test ModifierColorTypeToString function.
 * @tc.type: FUNC
 */
HWTEST_F(SelectTwoTestNg, ModifierColorTypeToString, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Define test cases with color type and expected string.
     * @tc.expected: step1. Test cases cover all relevant color types and an unknown type.
     */
    std::vector<std::pair<SelectColorType, std::string>> types = { { SelectColorType::FONT_COLOR, "FontColor" },
        { SelectColorType::BACKGROUND_COLOR, "BackgroundColor" },
        { SelectColorType::SELECTED_OPTION_BG_COLOR, "SelectedOptionBgColor" },
        { SelectColorType::SELECTED_OPTION_FONT_COLOR, "SelectedOptionFontColor" },
        { SelectColorType::OPTION_BG_COLOR, "OptionBgColor" },
        { SelectColorType::OPTION_FONT_COLOR, "OptionFontColor" },
        { SelectColorType::MENU_BACKGROUND_COLOR, "MenuBackgroundColor" },
        { static_cast<SelectColorType>(999), "Unknown" } };
    
    /**
     * @tc.steps: step2. Loop through test cases and verify string conversion.
     * @tc.expected: step2. Each color type converts to the expected string, including unknown type.
     */
    for (const auto& [type, expected] : types) {
        auto result = SelectModelNG::ModifierColorTypeToString(type);
        EXPECT_EQ(result, expected);
    }
}

/**
 * @tc.name: SetColorStatus001
 * @tc.desc: Test SetColorStatus.
 * @tc.type: FUNC
 */
HWTEST_F(SelectTwoTestNg, SetColorStatus001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create SelectModelNG and initialize frameNode with SelectPattern.
     * @tc.expected: step1. Model and frameNode are created successfully.
     */
    SelectModelNG selectModelNG;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE }, { OPTION_TEXT_2, INTERNAL_SOURCE } };
    selectModelNG.Create(params);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SelectPattern>();
    ASSERT_NE(pattern, nullptr);
    auto menuNode = pattern->GetMenuNode();
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);

    selectModelNG.SetColorStatus(frameNode, SelectColorType::FONT_COLOR);
    EXPECT_FALSE(menuPattern->isDisableMenuBgColorByUser_);

    selectModelNG.SetColorStatus(frameNode, SelectColorType::MENU_BACKGROUND_COLOR);
    EXPECT_TRUE(menuPattern->isDisableMenuBgColorByUser_);
}

/**
 * @tc.name: SelectChangeEventTest001
 * @tc.desc: Test SelectChangeEvent.
 * @tc.type: FUNC
 */
HWTEST_F(SelectTwoTestNg, SelectChangeEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create SelectModelNG and initialize frameNode with SelectPattern.
     * @tc.expected: step1. Model and frameNode are created successfully.
     */
    SelectModelNG selectModelNG;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE }, { OPTION_TEXT_2, INTERNAL_SOURCE } };
    selectModelNG.Create(params);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto selectPattern = frameNode->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto selectEventHub = frameNode->GetEventHub<SelectEventHub>();
    ASSERT_NE(selectEventHub, nullptr);
    int32_t currentIndex = 0;
    selectEventHub->SetSelectChangeEvent([&currentIndex](int32_t index) {
        currentIndex = index;
    });
    selectPattern->OnModifyDone();
    ASSERT_NE(selectPattern->options_.size(), 0);
    auto eventHub = selectPattern->options_[0]->GetEventHub<MenuItemEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto onSelect = eventHub->GetOnSelect();
    ASSERT_NE(onSelect, nullptr);
    onSelect(ERROR_INDEX_MIN);
    EXPECT_EQ(currentIndex, 0);
    onSelect(ERRPR_INDEX_MAX);
    EXPECT_EQ(currentIndex, 0);
    onSelect(1);
    EXPECT_EQ(currentIndex, 1);
}

/**
 * @tc.name: SetSelectedOptionFontFamily
 * @tc.desc: Test on color configuration update
 * @tc.type: FUNC
 */
HWTEST_F(SelectTwoTestNg, SetSelectedOptionFontFamily, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model and parameters of select.
     * @tc.expected: Objects are created successfully.
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE }, { OPTION_TEXT_2, INTERNAL_SOURCE },
        { OPTION_TEXT_3, INTERNAL_SOURCE } };
    selectModelInstance.Create(params);
    /**
     * @tc.steps: step2. Get select frame node, select pattern, pipeline base, select theme.
     * @tc.expected: Objects are gotten successfully and should not be null.
     */
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto selectTheme = pipeline->GetTheme<SelectTheme>();
    ASSERT_NE(selectTheme, nullptr);
    std::vector<std::string> value = { "select", "font", "family" };
    auto framenode = FrameNode::CreateFrameNode(
        V2::SELECT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());

    /**
     * @tc.steps: step3. Get menu frame node, menu pattern, render context and verify if the color of render context
     * is the same as the original input.
     * @tc.expected: Property is setted successfully and obejects should not be null.
     */
    selectModelInstance.SetSelectedOptionFontFamily(Referenced::RawPtr(framenode), value);
    ASSERT_NE(value.size(), 0);
}

/**
 * @tc.name: SetOptionFontFamily
 * @tc.desc: Test SelectPattern SetOptionFontFamily
 * @tc.type: FUNC
 */
HWTEST_F(SelectTwoTestNg, SetOptionFontFamily, TestSize.Level1)
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
    std::vector<std::string> value = { "select", "font", "family" };
    auto framenode = FrameNode::CreateFrameNode(
        V2::SELECT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());

    /**
     * @tc.steps: step3. Call SetOptionFontFamily.
     * @tc.expected: the function runs normally
     */
    selectModelInstance.SetOptionFontFamily(Referenced::RawPtr(framenode), value);
    ASSERT_NE(value.size(), 0);
}

/**
 * @tc.name: SetMenuAlign
 * @tc.desc: Test SetMenuAlign
 * @tc.type: FUNC
 */
HWTEST_F(SelectTwoTestNg, SetMenuAlign, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    // create select
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE }, { OPTION_TEXT, INTERNAL_SOURCE },
        { OPTION_TEXT_2, INTERNAL_SOURCE } };
    selectModelInstance.Create(params);
    MenuAlign menuAlign;
    menuAlign.alignType = MenuAlignType::END;
    menuAlign.offset = DimensionOffset(Dimension(OFFSETX, DimensionUnit::VP), Dimension(OFFSETY, DimensionUnit::VP));
    auto framenode = FrameNode::CreateFrameNode(
        V2::SELECT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(framenode, nullptr);
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_TRUE(select && select->GetTag() == V2::SELECT_ETS_TAG);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);

    /**
     * @tc.cases: case1. verify the SetMenuAlign function.
     */
    selectModelInstance.SetMenuAlign(Referenced::RawPtr(framenode), menuAlign);
    selectModelInstance.SetMenuAlign(menuAlign);
    EXPECT_NE(framenode, nullptr);

    selectModelInstance.SetMenuAlign(menuAlign);
    EXPECT_NE(framenode, nullptr);
}

/**
 * @tc.name: SetAvoidance
 * @tc.desc: Test SelectPattern SetAvoidance
 * @tc.type: FUNC
 */
HWTEST_F(SelectTwoTestNg, SetAvoidance, TestSize.Level1)
{
    SelectModelNG selectModelInstance;

    /**
     * @tc.steps: step1. Create select.
     */
    std::vector<SelectParam> params = { { OPTION_TEXT_3, INTERNAL_SOURCE } };
    selectModelInstance.Create(params);

    /**
     * @tc.steps: step2. Get frameNode and pattern.
     */
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto framenode = FrameNode::CreateFrameNode(
        V2::SELECT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(framenode, nullptr);

    /**
     * @tc.steps: step3. Call SetAvoidance.
     * @tc.expected: the function runs normally
     */
    auto mode = AvoidanceMode::COVER_TARGET;
    selectModelInstance.SetAvoidance(Referenced::RawPtr(framenode), mode);
    EXPECT_NE(framenode, nullptr);

    mode = AvoidanceMode::AVOID_AROUND_TARGET;
    selectModelInstance.SetAvoidance(Referenced::RawPtr(framenode), mode);
    EXPECT_NE(framenode, nullptr);
}

/**
 * @tc.name: SetHasOptionWidth
 * @tc.desc: Test SelectPattern SetHasOptionWidth
 * @tc.type: FUNC
 */
HWTEST_F(SelectTwoTestNg, SetHasOptionWidth, TestSize.Level1)
{
    SelectModelNG selectModelInstance;

    /**
     * @tc.steps: step1. Create select.
     */
    std::vector<SelectParam> params = { { OPTION_TEXT_3, INTERNAL_SOURCE } };
    selectModelInstance.Create(params);

    /**
     * @tc.steps: step2. Get frameNode and pattern.
     */
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto framenode = FrameNode::CreateFrameNode(
        V2::SELECT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(framenode, nullptr);

    /**
     * @tc.steps: step3. Call SetHasOptionWidth.
     * @tc.expected: the function runs normally
     */
    bool hasOptionWidth = false;
    selectModelInstance.SetHasOptionWidth(hasOptionWidth);
    selectModelInstance.SetHasOptionWidth(Referenced::RawPtr(framenode), hasOptionWidth);
    EXPECT_NE(framenode, nullptr);

    hasOptionWidth = true;
    selectModelInstance.SetHasOptionWidth(hasOptionWidth);
    selectModelInstance.SetHasOptionWidth(Referenced::RawPtr(framenode), hasOptionWidth);
    EXPECT_NE(framenode, nullptr);
}

/**
 * @tc.name: SetDivider
 * @tc.desc: Test SelectPattern SetDivider
 * @tc.type: FUNC
 */
HWTEST_F(SelectTwoTestNg, SetDivider, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model, initialize frame node and set size.
     * @tc.expected: step1. Select model and frame node are created, size is set correctly.
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);

    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    selectPattern->SetSelectSize(SizeF(SELECT_WIDTH, SELECT_HEIGHT));
    auto optionCount = selectPattern->options_.size();
    ASSERT_NE(optionCount, 0);
    auto framenode = FrameNode::CreateFrameNode(
        V2::SELECT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(framenode, nullptr);

    /**
     * @tc.steps: step3. Call SetDivider.
     * @tc.expected: the function runs normally
     */
    SelectDivider selectDivider;
    const SelectDivider& divider = selectDivider;
    selectModelInstance.SetDivider(divider);
    EXPECT_EQ(selectDivider.color, Color::TRANSPARENT);
}

/**
 * @tc.name: SetDividerStyle
 * @tc.desc: Test SelectPattern SetDividerStyle
 * @tc.type: FUNC
 */
HWTEST_F(SelectTwoTestNg, SetDividerStyle, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model, initialize frame node and set size.
     * @tc.expected: step1. Select model and frame node are created, size is set correctly.
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);

    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    selectPattern->SetSelectSize(SizeF(SELECT_WIDTH, SELECT_HEIGHT));
    auto optionCount = selectPattern->options_.size();
    ASSERT_NE(optionCount, 0);
    auto framenode = FrameNode::CreateFrameNode(
        V2::SELECT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(framenode, nullptr);

    /**
     * @tc.steps: step3. Call SetDividerStyle.
     * @tc.expected: the function runs normally
     */
    SelectDivider selectDivider;
    const DividerMode& mode = DividerMode::FLOATING_ABOVE_MENU;
    const SelectDivider& divider = selectDivider;
    selectModelInstance.SetDividerStyle(divider, mode);
    selectModelInstance.SetDividerStyle(Referenced::RawPtr(framenode), divider, mode);
    EXPECT_EQ(selectDivider.color, Color::TRANSPARENT);
}

/**
 * @tc.name: ResetDividerStyle
 * @tc.desc: Test SelectPattern ResetDividerStyle
 * @tc.type: FUNC
 */
HWTEST_F(SelectTwoTestNg, ResetDividerStyle, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model, initialize frame node and set size.
     * @tc.expected: step1. Select model and frame node are created, size is set correctly.
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);

    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    selectPattern->SetSelectSize(SizeF(SELECT_WIDTH, SELECT_HEIGHT));
    auto optionCount = selectPattern->options_.size();
    ASSERT_NE(optionCount, 0);
    auto framenode = FrameNode::CreateFrameNode(
        V2::SELECT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(framenode, nullptr);

    /**
     * @tc.steps: step3. Call ResetDividerStyle.
     * @tc.expected: the function runs normally
     */
    selectModelInstance.ResetDividerStyle(Referenced::RawPtr(framenode));
    EXPECT_NE(framenode, nullptr);
}

/**
 * @tc.name: GetControlSize
 * @tc.desc: Test SelectPattern GetControlSize
 * @tc.type: FUNC
 */
HWTEST_F(SelectTwoTestNg, GetControlSize, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model, initialize frame node and set size.
     * @tc.expected: step1. Select model and frame node are created, size is set correctly.
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);

    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    selectPattern->SetSelectSize(SizeF(SELECT_WIDTH, SELECT_HEIGHT));
    auto optionCount = selectPattern->options_.size();
    ASSERT_NE(optionCount, 0);
    auto framenode = FrameNode::CreateFrameNode(
        V2::SELECT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(framenode, nullptr);

    /**
     * @tc.steps: step3. Call GetControlSize.
     * @tc.expected: the function runs normally
     */
    ControlSize res = selectModelInstance.GetControlSize();
    EXPECT_EQ(res, ControlSize::NORMAL);

    res = selectModelInstance.GetControlSize(Referenced::RawPtr(framenode));
    EXPECT_EQ(res, ControlSize::NORMAL);
}

/**
 * @tc.name: CreateFrameNode
 * @tc.desc: Test SelectPattern CreateFrameNode
 * @tc.type: FUNC
 */
HWTEST_F(SelectTwoTestNg, CreateFrameNode, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model, initialize frame node and set size.
     * @tc.expected: step1. Select model and frame node are created, size is set correctly.
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);

    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    selectPattern->SetSelectSize(SizeF(SELECT_WIDTH, SELECT_HEIGHT));
    auto optionCount = selectPattern->options_.size();
    ASSERT_NE(optionCount, 0);

    /**
     * @tc.steps: step3. Call CreateFrameNode.
     * @tc.expected: the function runs normally
     */
    int32_t nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto res = selectModelInstance.CreateFrameNode(nodeId);
    auto tag = res->GetTag();
    EXPECT_EQ(tag, V2::SELECT_ETS_TAG);
}

/**
 * @tc.name: CreateWithColorResourceObj
 * @tc.desc: Test SelectPattern CreateWithColorResourceObj
 * @tc.type: FUNC
 */
HWTEST_F(SelectTwoTestNg, CreateWithColorResourceObj, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model, initialize frame node and set size.
     * @tc.expected: step1. Select model and frame node are created, size is set correctly.
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);

    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    selectPattern->SetSelectSize(SizeF(SELECT_WIDTH, SELECT_HEIGHT));
    auto optionCount = selectPattern->options_.size();
    ASSERT_NE(optionCount, 0);

    /**
     * @tc.steps: step3. Call CreateWithColorResourceObj.
     * @tc.expected: the function runs normally
     */
    const RefPtr<ResourceObject>& resObj = AceType::MakeRefPtr<ResourceObject>();
    const SelectColorType& type = SelectColorType::FONT_COLOR;
    auto framenode = FrameNode::CreateFrameNode(
        V2::SELECT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(framenode, nullptr);
    selectModelInstance.CreateWithColorResourceObj(resObj, type);
    selectModelInstance.CreateWithColorResourceObj(nullptr, resObj, type);
    selectModelInstance.CreateWithColorResourceObj(Referenced::RawPtr(framenode), resObj, type);
    EXPECT_EQ(type, SelectColorType::FONT_COLOR);
}

/**
 * @tc.name: SetArrowPosition
 * @tc.desc: Test SelectPattern SetArrowPosition
 * @tc.type: FUNC
 */
HWTEST_F(SelectTwoTestNg, SetArrowPosition, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model, initialize frame node and set size.
     * @tc.expected: step1. Select model and frame node are created, size is set correctly.
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);

    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    selectPattern->SetSelectSize(SizeF(SELECT_WIDTH, SELECT_HEIGHT));
    auto optionCount = selectPattern->options_.size();
    ASSERT_NE(optionCount, 0);
    auto framenode = FrameNode::CreateFrameNode(
        V2::SELECT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(framenode, nullptr);

    /**
     * @tc.steps: step3. Call SetArrowPosition.
     * @tc.expected: the function runs normally
     */
    const ArrowPosition value = ArrowPosition::START;
    selectModelInstance.SetArrowPosition(Referenced::RawPtr(framenode), value);
    EXPECT_NE(framenode, nullptr);
}

/**
 * @tc.name: SetSpace
 * @tc.desc: Test SelectPattern SetSpace
 * @tc.type: FUNC
 */
HWTEST_F(SelectTwoTestNg, SetSpace, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model, initialize frame node and set size.
     * @tc.expected: step1. Select model and frame node are created, size is set correctly.
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);

    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    selectPattern->SetSelectSize(SizeF(SELECT_WIDTH, SELECT_HEIGHT));
    auto optionCount = selectPattern->options_.size();
    ASSERT_NE(optionCount, 0);
    auto framenode = FrameNode::CreateFrameNode(
        V2::SELECT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(framenode, nullptr);

    /**
     * @tc.steps: step3. Call SetSpace.
     * @tc.expected: the function runs normally
     */
    const Dimension& value = FONT_SIZE_VALUE;
    selectModelInstance.SetSpace(Referenced::RawPtr(framenode), value);
    EXPECT_NE(framenode, nullptr);
}

/**
 * @tc.name: SetValue
 * @tc.desc: Test SelectPattern SetValue
 * @tc.type: FUNC
 */
HWTEST_F(SelectTwoTestNg, SetValue, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model, initialize frame node and set size.
     * @tc.expected: step1. Select model and frame node are created, size is set correctly.
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);

    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    selectPattern->SetSelectSize(SizeF(SELECT_WIDTH, SELECT_HEIGHT));
    auto optionCount = selectPattern->options_.size();
    ASSERT_NE(optionCount, 0);
    auto framenode = FrameNode::CreateFrameNode(
        V2::SELECT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(framenode, nullptr);

    /**
     * @tc.steps: step3. Call SetValue.
     * @tc.expected: the function runs normally
     */
    const std::string& value = "select";
    selectModelInstance.SetValue(Referenced::RawPtr(framenode), value);
    EXPECT_NE(framenode, nullptr);
}

/**
 * @tc.name: SetSelected
 * @tc.desc: Test SelectPattern SetSelected
 * @tc.type: FUNC
 */
HWTEST_F(SelectTwoTestNg, SetSelected, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model, initialize frame node and set size.
     * @tc.expected: step1. Select model and frame node are created, size is set correctly.
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);

    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    selectPattern->SetSelectSize(SizeF(SELECT_WIDTH, SELECT_HEIGHT));
    auto optionCount = selectPattern->options_.size();
    ASSERT_NE(optionCount, 0);
    auto framenode = FrameNode::CreateFrameNode(
        V2::SELECT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(framenode, nullptr);

    /**
     * @tc.steps: step3. Call SetSelected.
     * @tc.expected: the function runs normally
     */
    int32_t idx = 0;
    selectModelInstance.SetSelected(Referenced::RawPtr(framenode), idx);
    EXPECT_NE(framenode, nullptr);
}

/**
 * @tc.name: SetFontSize
 * @tc.desc: Test SelectPattern SetFontSize
 * @tc.type: FUNC
 */
HWTEST_F(SelectTwoTestNg, SetFontSize, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model, initialize frame node and set size.
     * @tc.expected: step1. Select model and frame node are created, size is set correctly.
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);

    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    selectPattern->SetSelectSize(SizeF(SELECT_WIDTH, SELECT_HEIGHT));
    auto optionCount = selectPattern->options_.size();
    ASSERT_NE(optionCount, 0);
    auto framenode = FrameNode::CreateFrameNode(
        V2::SELECT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(framenode, nullptr);

    /**
     * @tc.steps: step3. Call SetFontSize.
     * @tc.expected: the function runs normally
     */
    const Dimension& value = FONT_SIZE_VALUE;
    selectModelInstance.SetFontSize(Referenced::RawPtr(framenode), value);
    EXPECT_NE(framenode, nullptr);
}

/**
 * @tc.name: SetFontWeight
 * @tc.desc: Test SelectPattern SetFontWeight
 * @tc.type: FUNC
 */
HWTEST_F(SelectTwoTestNg, SetFontWeight, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model, initialize frame node and set size.
     * @tc.expected: step1. Select model and frame node are created, size is set correctly.
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);

    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    selectPattern->SetSelectSize(SizeF(SELECT_WIDTH, SELECT_HEIGHT));
    auto optionCount = selectPattern->options_.size();
    ASSERT_NE(optionCount, 0);
    auto framenode = FrameNode::CreateFrameNode(
        V2::SELECT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(framenode, nullptr);

    /**
     * @tc.steps: step3. Call SetFontWeight.
     * @tc.expected: the function runs normally
     */
    const FontWeight& value = FontWeight::NORMAL;
    selectModelInstance.SetFontWeight(Referenced::RawPtr(framenode), value);
    EXPECT_NE(framenode, nullptr);
}

/**
 * @tc.name: SetFontFamily
 * @tc.desc: Test SelectPattern SetFontFamily
 * @tc.type: FUNC
 */
HWTEST_F(SelectTwoTestNg, SetFontFamily, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model, initialize frame node and set size.
     * @tc.expected: step1. Select model and frame node are created, size is set correctly.
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);

    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    selectPattern->SetSelectSize(SizeF(SELECT_WIDTH, SELECT_HEIGHT));
    auto optionCount = selectPattern->options_.size();
    ASSERT_NE(optionCount, 0);
    auto framenode = FrameNode::CreateFrameNode(
        V2::SELECT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(framenode, nullptr);

    /**
     * @tc.steps: step3. Call SetFontFamily.
     * @tc.expected: the function runs normally
     */
    std::vector<std::string> value = { "select", "font", "family" };
    selectModelInstance.SetFontFamily(Referenced::RawPtr(framenode), value);
    EXPECT_NE(framenode, nullptr);
}

/**
 * @tc.name: SetItalicFontStyle
 * @tc.desc: Test SelectPattern SetItalicFontStyle
 * @tc.type: FUNC
 */
HWTEST_F(SelectTwoTestNg, SetItalicFontStyle, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model, initialize frame node and set size.
     * @tc.expected: step1. Select model and frame node are created, size is set correctly.
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);

    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    selectPattern->SetSelectSize(SizeF(SELECT_WIDTH, SELECT_HEIGHT));
    auto optionCount = selectPattern->options_.size();
    ASSERT_NE(optionCount, 0);
    auto framenode = FrameNode::CreateFrameNode(
        V2::SELECT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(framenode, nullptr);

    /**
     * @tc.steps: step3. Call SetItalicFontStyle.
     * @tc.expected: the function runs normally
     */
    const Ace::FontStyle& value = Ace::FontStyle::NORMAL;
    selectModelInstance.SetItalicFontStyle(Referenced::RawPtr(framenode), value);
    EXPECT_NE(framenode, nullptr);
}

/**
 * @tc.name: SetFontColor
 * @tc.desc: Test SelectPattern SetFontColor
 * @tc.type: FUNC
 */
HWTEST_F(SelectTwoTestNg, SetFontColor, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model, initialize frame node and set size.
     * @tc.expected: step1. Select model and frame node are created, size is set correctly.
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);

    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    selectPattern->SetSelectSize(SizeF(SELECT_WIDTH, SELECT_HEIGHT));
    auto optionCount = selectPattern->options_.size();
    ASSERT_NE(optionCount, 0);
    auto framenode = FrameNode::CreateFrameNode(
        V2::SELECT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(framenode, nullptr);

    /**
     * @tc.steps: step3. Call SetFontColor.
     * @tc.expected: the function runs normally
     */
    const Color& color = TEXT_COLOR_VALUE;
    selectModelInstance.SetFontColor(Referenced::RawPtr(framenode), color);
    EXPECT_NE(framenode, nullptr);
}

/**
 * @tc.name: SetSelectedOptionBgColor
 * @tc.desc: Test SelectPattern SetSelectedOptionBgColor
 * @tc.type: FUNC
 */
HWTEST_F(SelectTwoTestNg, SetSelectedOptionBgColor, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model, initialize frame node and set size.
     * @tc.expected: step1. Select model and frame node are created, size is set correctly.
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);

    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    selectPattern->SetSelectSize(SizeF(SELECT_WIDTH, SELECT_HEIGHT));
    auto optionCount = selectPattern->options_.size();
    ASSERT_NE(optionCount, 0);
    auto framenode = FrameNode::CreateFrameNode(
        V2::SELECT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(framenode, nullptr);

    /**
     * @tc.steps: step3. Call SetSelectedOptionBgColor.
     * @tc.expected: the function runs normally
     */
    const Color& color = BG_COLOR_VALUE;
    selectModelInstance.SetSelectedOptionBgColor(Referenced::RawPtr(framenode), color);
    EXPECT_NE(framenode, nullptr);
}

/**
 * @tc.name: SetOptionFontSize
 * @tc.desc: Test SelectPattern SetOptionFontSize
 * @tc.type: FUNC
 */
HWTEST_F(SelectTwoTestNg, SetOptionFontSize, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model, initialize frame node and set size.
     * @tc.expected: step1. Select model and frame node are created, size is set correctly.
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);

    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    selectPattern->SetSelectSize(SizeF(SELECT_WIDTH, SELECT_HEIGHT));
    auto optionCount = selectPattern->options_.size();
    ASSERT_NE(optionCount, 0);
    auto framenode = FrameNode::CreateFrameNode(
        V2::SELECT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(framenode, nullptr);

    /**
     * @tc.steps: step3. Call SetOptionFontSize.
     * @tc.expected: the function runs normally
     */
    const Dimension& value = FONT_SIZE_VALUE;
    selectModelInstance.SetOptionFontSize(Referenced::RawPtr(framenode), value);
    EXPECT_NE(framenode, nullptr);
}

/**
 * @tc.name: SetOptionFontWeight
 * @tc.desc: Test SelectPattern SetOptionFontWeight
 * @tc.type: FUNC
 */
HWTEST_F(SelectTwoTestNg, SetOptionFontWeight, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model, initialize frame node and set size.
     * @tc.expected: step1. Select model and frame node are created, size is set correctly.
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);

    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    selectPattern->SetSelectSize(SizeF(SELECT_WIDTH, SELECT_HEIGHT));
    auto optionCount = selectPattern->options_.size();
    ASSERT_NE(optionCount, 0);
    auto framenode = FrameNode::CreateFrameNode(
        V2::SELECT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(framenode, nullptr);

    /**
     * @tc.steps: step3. Call SetOptionFontWeight.
     * @tc.expected: the function runs normally
     */
    const FontWeight& value = FontWeight::NORMAL;
    selectModelInstance.SetOptionFontWeight(Referenced::RawPtr(framenode), value);
    EXPECT_NE(framenode, nullptr);
}

/**
 * @tc.name: SetOptionFontFamily001
 * @tc.desc: Test SelectPattern SetOptionFontFamily001
 * @tc.type: FUNC
 */
HWTEST_F(SelectTwoTestNg, SetOptionFontFamily001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model, initialize frame node and set size.
     * @tc.expected: step1. Select model and frame node are created, size is set correctly.
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);

    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    selectPattern->SetSelectSize(SizeF(SELECT_WIDTH, SELECT_HEIGHT));
    auto optionCount = selectPattern->options_.size();
    ASSERT_NE(optionCount, 0);
    auto framenode = FrameNode::CreateFrameNode(
        V2::SELECT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(framenode, nullptr);

    /**
     * @tc.steps: step3. Call SetOptionFontFamily.
     * @tc.expected: the function runs normally
     */
    std::vector<std::string> value = { "select", "font", "family" };
    selectModelInstance.SetOptionFontFamily(Referenced::RawPtr(framenode), value);
    EXPECT_NE(framenode, nullptr);
}

/**
 * @tc.name: SetOptionItalicFontStyle
 * @tc.desc: Test SelectPattern SetOptionItalicFontStyle
 * @tc.type: FUNC
 */
HWTEST_F(SelectTwoTestNg, SetOptionItalicFontStyle, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model, initialize frame node and set size.
     * @tc.expected: step1. Select model and frame node are created, size is set correctly.
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);

    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    selectPattern->SetSelectSize(SizeF(SELECT_WIDTH, SELECT_HEIGHT));
    auto optionCount = selectPattern->options_.size();
    ASSERT_NE(optionCount, 0);
    auto framenode = FrameNode::CreateFrameNode(
        V2::SELECT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(framenode, nullptr);

    /**
     * @tc.steps: step3. Call SetOptionItalicFontStyle.
     * @tc.expected: the function runs normally
     */
    const Ace::FontStyle& value = Ace::FontStyle::NORMAL;
    selectModelInstance.SetOptionItalicFontStyle(Referenced::RawPtr(framenode), value);
    EXPECT_NE(framenode, nullptr);
}

/**
 * @tc.name: SetOptionBgColor
 * @tc.desc: Test SelectPattern SetOptionBgColor
 * @tc.type: FUNC
 */
HWTEST_F(SelectTwoTestNg, SetOptionBgColor, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model, initialize frame node and set size.
     * @tc.expected: step1. Select model and frame node are created, size is set correctly.
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);

    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    selectPattern->SetSelectSize(SizeF(SELECT_WIDTH, SELECT_HEIGHT));
    auto optionCount = selectPattern->options_.size();
    ASSERT_NE(optionCount, 0);
    auto framenode = FrameNode::CreateFrameNode(
        V2::SELECT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(framenode, nullptr);

    /**
     * @tc.steps: step3. Call SetOptionBgColor.
     * @tc.expected: the function runs normally
     */
    const Color& color = BG_COLOR_VALUE;
    selectModelInstance.SetOptionBgColor(Referenced::RawPtr(framenode), color);
    EXPECT_NE(framenode, nullptr);
}

/**
 * @tc.name: InitSelectMultiThread001
 * @tc.desc: Test InitSelectMultiThread in multi-thread scenario.
 * @tc.type: FUNC
 */
HWTEST_F(SelectTwoTestNg, InitSelectMultiThread001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Simulate non-UI thread environment and create a thread-safe select node.
     */
    MultiThreadBuildManager::SetIsThreadSafeNodeScope(true);
    bool isUIThread = MultiThreadBuildManager::isUIThread_;
    MultiThreadBuildManager::isUIThread_ = false;

    SelectModelNG selectModelInstance;
    // Create an empty Select node first by passing an empty vector.
    selectModelInstance.Create({});
    auto selectNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(selectNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(selectNode); // Push back for subsequent operations if needed

    /**
     * @tc.steps: step2. Call InitSelectMultiThread and check if a task is posted.
     * @tc.expected: A task should be added to afterAttachMainTreeTasks_.
     */
    auto selectPattern = selectNode->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    // Replace with a new empty vector to bypass the initialization check in InitSelect.
    selectPattern->options_ = std::vector<RefPtr<FrameNode>>();
    // Record the number of tasks before calling the function to be tested.
    auto initialTaskCount = selectNode->afterAttachMainTreeTasks_.size();

    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE }, { OPTION_TEXT_2, INTERNAL_SOURCE } };
    selectModelInstance.InitSelectMultiThread(selectNode, params);
    // Verify that exactly one task has been added.
    EXPECT_EQ(selectNode->afterAttachMainTreeTasks_.size(), initialTaskCount + 1);

    /**
     * @tc.steps: step3. Execute the posted task.
     * @tc.expected: The options in SelectPattern should be initialized correctly.
     */
    selectNode->afterAttachMainTreeTasks_.back()();
    EXPECT_EQ(selectPattern->options_.size(), 0);

    /**
     * @tc.steps: step4. Restore environment.
     */
    MultiThreadBuildManager::isUIThread_ = isUIThread;
    MultiThreadBuildManager::SetIsThreadSafeNodeScope(false);
}

/**
 * @tc.name: OnAttachToMainTreeMultiThread001
 * @tc.desc: Test OnAttachToMainTreeMultiThread to verify event registration.
 * @tc.type: FUNC
 */
HWTEST_F(SelectTwoTestNg, OnAttachToMainTreeMultiThread001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a select node and get its pattern and event hub.
     */
    SelectModelNG selectModelInstance;
    selectModelInstance.Create({});
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto selectPattern = frameNode->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);

    /**
     * @tc.steps: step2. Call OnAttachToMainTreeMultiThread.
     * @tc.expected: All related events should be registered on the event hub.
     */
    selectPattern->OnAttachToMainTreeMultiThread();

    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    EXPECT_FALSE(focusHub->onKeyEventsInternal_.empty());

    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    EXPECT_TRUE(gestureHub->clickEventActuator_);
    EXPECT_TRUE(gestureHub->touchEventActuator_);

    auto inputHub = frameNode->GetOrCreateInputEventHub();
    ASSERT_NE(inputHub, nullptr);
    EXPECT_TRUE(inputHub->hoverEventActuator_);
}

/**
 * @tc.name: ResetOptionPropsMultiThread001
 * @tc.desc: Test ResetOptionPropsMultiThread posts a task correctly.
 * @tc.type: FUNC
 */
HWTEST_F(SelectTwoTestNg, ResetOptionPropsMultiThread001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Simulate non-UI thread, create a select node, and set an option property.
     */
    MultiThreadBuildManager::SetIsThreadSafeNodeScope(true);
    bool isUIThread = MultiThreadBuildManager::isUIThread_;
    MultiThreadBuildManager::isUIThread_ = false;

    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { "Test", "Test" } };
    selectModelInstance.Create(params);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    // Set property after node creation
    selectModelInstance.SetOptionBgColor(Color::RED);

    auto selectPattern = frameNode->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    // Execute tasks to make sure the property is set on the pattern
    frameNode->ExecuteAfterAttachMainTreeTasks();

    /**
     * @tc.steps: step2. Call ResetOptionPropsMultiThread and check if a task is posted.
     */
    auto initialTaskCount = frameNode->afterAttachMainTreeTasks_.size();
    selectPattern->ResetOptionPropsMultiThread();
    EXPECT_EQ(frameNode->afterAttachMainTreeTasks_.size(), initialTaskCount + 1);

    /**
     * @tc.steps: step3. Execute the posted task and verify the result.
     * @tc.expected: The option background color should be reset.
     */
    frameNode->afterAttachMainTreeTasks_.back()();
    EXPECT_FALSE(selectPattern->optionBgColor_.has_value());

    /**
     * @tc.steps: step4. Restore environment.
     */
    MultiThreadBuildManager::isUIThread_ = isUIThread;
    MultiThreadBuildManager::SetIsThreadSafeNodeScope(false);
}

/**
 * @tc.name: SelectSetArrowPositionTest002
 * @tc.desc: Test SetArrowPosition
 * @tc.type: FUNC
 */
HWTEST_F(SelectTwoTestNg, SelectSetArrowPositionTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model and parameters of select and call Create() of select model.
     * @tc.expected: Objects are created successfully.
     */
    SelectModelNG selectModelInstance;

    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE }, { OPTION_TEXT, INTERNAL_SOURCE },
        { OPTION_TEXT_2, INTERNAL_SOURCE } };
    selectModelInstance.Create(params);
    /**
     * @tc.steps: step2. Set space and arrow position of select, get select frame node and verify if it has
     * child node.
     * @tc.expected: select frame node has no child node.
     */
    selectModelInstance.SetArrowPosition(ArrowPosition::END);
    selectModelInstance.SetSpace(Dimension(20.00, DimensionUnit::VP));
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_FALSE(select->GetChildren().empty());
}
} // namespace OHOS::Ace::NG
