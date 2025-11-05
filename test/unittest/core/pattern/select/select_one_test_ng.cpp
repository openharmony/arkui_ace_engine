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
#include "test/mock/base/mock_task_executor.h"
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
#include "core/components_ng/layout/layout_wrapper_node.h"
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
const Color TEXT_COLOR_VALUE = Color::FromRGB(255, 100, 100);
const Color BG_COLOR_VALUE = Color::FromRGB(100, 255, 100);
const std::vector<SelectParam> CREATE_VALUE = { { OPTION_TEXT, FILE_SOURCE }, { OPTION_TEXT_2, INTERNAL_SOURCE },
    { OPTION_TEXT_3, INTERNAL_SOURCE } };
constexpr int32_t PLATFORM_VERSION_ELEVEN = 11;
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
class SelectOneTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void TearDown() override;
    void InitSelectOneTestNg();

protected:
    static RefPtr<FrameNode> CreateSelect(const std::vector<SelectParam>& value, const TestProperty& test);

    RefPtr<FrameNode> frameNode_;
    RefPtr<SelectPattern> selectPattern_;
    RefPtr<SelectAccessibilityProperty> selectAccessibilityProperty_;
};

void SelectOneTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        return GetTheme(type);
    });
    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([](ThemeType type, int32_t themeScopeId) -> RefPtr<Theme> { return GetTheme(type); });
}

void SelectOneTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

void SelectOneTestNg::TearDown()
{
    frameNode_ = nullptr;
    selectPattern_ = nullptr;
    selectAccessibilityProperty_ = nullptr;
}

void SelectOneTestNg::InitSelectOneTestNg()
{
    frameNode_ = FrameNode::GetOrCreateFrameNode(V2::SELECT_ETS_TAG, ViewStackProcessor::GetInstance()->ClaimNodeId(),
        []() { return AceType::MakeRefPtr<SelectPattern>(); });
    ASSERT_NE(frameNode_, nullptr);
    selectPattern_ = frameNode_->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern_, nullptr);
    selectAccessibilityProperty_ = frameNode_->GetAccessibilityProperty<SelectAccessibilityProperty>();
    ASSERT_NE(selectAccessibilityProperty_, nullptr);
}

RefPtr<FrameNode> SelectOneTestNg::CreateSelect(const std::vector<SelectParam>& value, const TestProperty& test)
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
 * @tc.name: SelectOption001
 * @tc.desc: Test SelectModelNG SetOptionWidth.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOneTestNg, SelectOption001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model, select frame node and select pattern, call SetOptionWidth.
     * @tc.expected: Objects are created successfully.
     */
    Dimension OPTION_WIDTH = Dimension(150.0f, DimensionUnit::VP);
    Dimension OPTION_MARGIN = Dimension(8.0f, DimensionUnit::VP);
    SelectModelNG selectModelInstance;

    selectModelInstance.SetOptionWidth(OPTION_WIDTH);
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto selectPattern = select->GetPattern<SelectPattern>();
    /**
     * @tc.steps: step2. Get menu frame node and menu layout property,
     * compare the original value with the width.
     * @tc.expected: Setting is successful, width of menu and original value are equal.
     */
    auto menu = selectPattern->GetMenuNode();
    auto menuLayoutProperty = menu->GetLayoutProperty<MenuLayoutProperty>();
    EXPECT_EQ(menuLayoutProperty->GetSelectMenuModifiedWidth().value(),
        OPTION_WIDTH.ConvertToPx() + OPTION_MARGIN.ConvertToPx());
    /**
     * @tc.steps: step3. Get scroll frame node and scroll layout property,
     * compare the original value with the width.
     * @tc.expected: Setting is successful, width of scroll and original value are equal.
     */
    auto scroll = AceType::DynamicCast<FrameNode>(menu->GetFirstChild());
    auto scrollLayoutProperty = scroll->GetLayoutProperty<ScrollLayoutProperty>();
    EXPECT_EQ(scrollLayoutProperty->GetScrollWidth().value(), OPTION_WIDTH.ConvertToPx() + OPTION_MARGIN.ConvertToPx());
    /**
     * @tc.steps: step4. Get option frame node and option paint property,
     * compare the original value with the width.
     * @tc.expected: Setting is successful, width of option plus margin is equal to the original value.
     */
    auto options = selectPattern->GetOptions();
    if (options.size() > 0) {
        auto optionPaintProperty = options[0]->GetPaintProperty<MenuItemPaintProperty>();
        EXPECT_EQ(optionPaintProperty->GetSelectModifiedWidth().value(), OPTION_WIDTH.ConvertToPx());
    }
}

/**
 * @tc.name: ShowSelectMenuTest002
 * @tc.desc: Test ShowSelectMenu of the SelectPattern when the width of select menu fit the width of
 * select button.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOneTestNg, ShowSelectMenuTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get select model, select frame node, test property and select pattern. Set the
     * options to fit the trigger.
     * @tc.expected: Get pattern successfully.
     */
    SelectModelNG selectModelInstance;
    selectModelInstance.SetOptionWidthFitTrigger(true);
    TestProperty testProperty;
    testProperty.FontSize = std::make_optional(FONT_SIZE_VALUE);
    auto frameNode = CreateSelect(CREATE_VALUE, testProperty);
    auto pattern = frameNode->GetPattern<SelectPattern>();
    EXPECT_TRUE(pattern);
    /**
     * @tc.steps: step2. Call ShowSelectMenu and compare the ordinate of offset with the height of selectSize_,
     * which is a member of select pattern.
     * @tc.expected: Ordinate of offset and the height of offset of selectSize_ are equal.
     */
    pattern->ShowSelectMenu();
    auto offset = pattern->GetHost()->GetPaintRectOffset();
    EXPECT_EQ(offset.GetY(), pattern->selectSize_.Height());
}

/**
 * @tc.name: SetSelectDefaultThemeTest001
 * @tc.desc: Test SelectPattern SetSelectDefaultTheme to verify the default visual effect of select button.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOneTestNg, SetSelectDefaultThemeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build select frame node, select theme, select pattern.
     * @tc.expected: Objects are created successfully.
     */
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    /**
     * @tc.steps: step2. build render context, pipeline and select theme.
     * @tc.expected: Objects are created successfully.
     */
    auto renderContext = select->GetRenderContext();
    auto pipeline = PipelineBase::GetCurrentContext();
    auto selectTheme = pipeline->GetTheme<SelectTheme>();
    ASSERT_NE(selectTheme, nullptr);
    /**
     * @tc.steps: step3. compare the attributes in render context with the attributes in select theme.
     * @tc.expected: Attributes are equal.
     */
    EXPECT_EQ(
        renderContext->GetBorderRadius().value().radiusTopLeft.value(), selectTheme->GetSelectDefaultBorderRadius());
    EXPECT_EQ(
        renderContext->GetBorderRadius().value().radiusTopRight.value(), selectTheme->GetSelectDefaultBorderRadius());
    EXPECT_EQ(renderContext->GetBorderRadius().value().radiusBottomRight.value(),
        selectTheme->GetSelectDefaultBorderRadius());
    EXPECT_EQ(
        renderContext->GetBorderRadius().value().radiusBottomLeft.value(), selectTheme->GetSelectDefaultBorderRadius());
}

/**
 * @tc.name: GetFontSizeTest001
 * @tc.desc: Test SelectPattern GetFontSize.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOneTestNg, GetFontSizeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build select frame node, select pattern, pipeline and select theme.
     * @tc.expected: Objects are created successfully.
     */
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto selectPattern = select->GetPattern<SelectPattern>();
    auto pipeline = PipelineBase::GetCurrentContext();
    auto selectTheme = pipeline->GetTheme<SelectTheme>();
    /**
     * @tc.steps: step2. Build the text frame node and assign it to be the member of select pattern.
     * @tc.expected: Object is created successfully.
     */
    selectPattern->text_ = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    /**
     * @tc.steps: step3. build text layout property, respectively get the font size from text layout property and
     * select pattern and compare them.
     * @tc.expected: Two sizes should be equal.
     */
    auto textLayoutProps = selectPattern->text_->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_EQ(textLayoutProps->GetFontSize().value_or(selectTheme->GetFontSize()), selectPattern->GetFontSize());
}

/**
 * @tc.name: SelectPadding001
 * @tc.desc: Test Select Default padding
 * @tc.type: FUNC
 */
HWTEST_F(SelectOneTestNg, SelectPadding001, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(PLATFORM_VERSION_ELEVEN);
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(100);
    selectModelInstance.Create(params);
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto layoutProps = select->GetLayoutProperty();
    ASSERT_NE(layoutProps, nullptr);
    const auto& padding = layoutProps->GetPaddingProperty();
    ASSERT_NE(padding, nullptr);
    EXPECT_EQ(padding->left.value().GetDimension().ConvertToVp(), 8.0);
    EXPECT_EQ(padding->right.value().GetDimension().ConvertToVp(), 8.0);
}

/**
 * @tc.name: SelectOptionHeight001
 * @tc.desc: Test SelectModelNG SetOptionHeight.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOneTestNg, SelectOptionHeight001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build select model instance an parameters.
     * @tc.expected: Objects are created successfully.
     */
    Dimension OPTION_HEIGHT = Dimension(150.0f, DimensionUnit::VP);
    SelectModelNG selectModelInstance;
    /**
     * @tc.steps: step2. Call SetOptionHeight.
     */
    selectModelInstance.SetOptionHeight(OPTION_HEIGHT);
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto selectPattern = select->GetPattern<SelectPattern>();
    /**
     * @tc.steps: step3. Call SetOptionHeight.
     * @tc.expected: Attributes are called successfully.
     */
    auto menu = selectPattern->GetMenuNode();
    auto menuLayoutProperty = menu->GetLayoutProperty<MenuLayoutProperty>();
    EXPECT_EQ(menuLayoutProperty->GetSelectModifiedHeight().value(),
    OPTION_HEIGHT.ConvertToPx());
}

/**
 * @tc.name: SetSelectedOptionFontColor001
 * @tc.desc: Test SelectModelNG SetSelectedOptionFontColor
 * @tc.type: FUNC
 */
HWTEST_F(SelectOneTestNg, SetSelectedOptionFontColor001, TestSize.Level1)
{
    RefPtr<SelectPattern> pattern = AceType::MakeRefPtr<SelectPattern>();
    ASSERT_NE(pattern, nullptr);
    FrameNode frameNode = FrameNode(V2::SELECT_ETS_TAG, 1, pattern);
    frameNode_ = FrameNode::GetOrCreateFrameNode(V2::SELECT_ETS_TAG, ViewStackProcessor::GetInstance()->ClaimNodeId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    ASSERT_NE(frameNode_, nullptr);
    pattern->text_ = frameNode_;
    pattern->text_->SetLayoutProperty(AceType::MakeRefPtr<TextLayoutProperty>());
    SelectModelNG::SetSelectedOptionFontColor(&frameNode, Color::BLACK);
    EXPECT_EQ(pattern->GetSelected(), -1);
}

/**
 * @tc.name: SetSelectedOptionFontColor002
 * @tc.desc: Test SelectPattern SetSelectedOptionFontColor
 * @tc.type: FUNC
 */
HWTEST_F(SelectOneTestNg, SetSelectedOptionFontColor002, TestSize.Level1)
{
    RefPtr<SelectPattern> pattern = AceType::MakeRefPtr<SelectPattern>();
    ASSERT_NE(pattern, nullptr);
    FrameNode frameNode = FrameNode(V2::SELECT_ETS_TAG, 1, pattern);
    frameNode_ = FrameNode::GetOrCreateFrameNode(V2::SELECT_ETS_TAG, ViewStackProcessor::GetInstance()->ClaimNodeId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    ASSERT_NE(frameNode_, nullptr);
    pattern->text_ = frameNode_;
    pattern->text_->SetLayoutProperty(AceType::MakeRefPtr<TextLayoutProperty>());
    pattern->selected_ = 0;
    pattern->SetSelectedOptionFontColor(Color::BLACK);
    EXPECT_EQ(pattern->GetSelected(), 0);
}

/**
 * @tc.name: SetSelectedOptionFontSize001
 * @tc.desc: Test SelectModelNG SetSelectedOptionFontSize
 * @tc.type: FUNC
 */
HWTEST_F(SelectOneTestNg, SetSelectedOptionFontSize001, TestSize.Level1)
{
    RefPtr<SelectPattern> pattern = AceType::MakeRefPtr<SelectPattern>();
    ASSERT_NE(pattern, nullptr);
    FrameNode frameNode = FrameNode(V2::SELECT_ETS_TAG, 1, pattern);
    frameNode_ = FrameNode::GetOrCreateFrameNode(V2::SELECT_ETS_TAG, ViewStackProcessor::GetInstance()->ClaimNodeId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    ASSERT_NE(frameNode_, nullptr);
    pattern->text_ = frameNode_;
    pattern->text_->SetLayoutProperty(AceType::MakeRefPtr<TextLayoutProperty>());
    SelectModelNG::SetSelectedOptionFontSize(&frameNode, Dimension(20.00, DimensionUnit::VP));
    EXPECT_EQ(pattern->GetSelected(), -1);
}

/**
 * @tc.name: SetSelectedOptionFontSize002
 * @tc.desc: Test SelectModelNG SetSelectedOptionFontSize
 * @tc.type: FUNC
 */
HWTEST_F(SelectOneTestNg, SetSelectedOptionFontSize002, TestSize.Level1)
{
    RefPtr<SelectPattern> pattern = AceType::MakeRefPtr<SelectPattern>();
    ASSERT_NE(pattern, nullptr);
    FrameNode frameNode = FrameNode(V2::SELECT_ETS_TAG, 1, pattern);
    frameNode_ = FrameNode::GetOrCreateFrameNode(V2::SELECT_ETS_TAG, ViewStackProcessor::GetInstance()->ClaimNodeId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    ASSERT_NE(frameNode_, nullptr);
    pattern->text_ = frameNode_;
    pattern->text_->SetLayoutProperty(AceType::MakeRefPtr<TextLayoutProperty>());
    pattern->selected_ = 1;
    auto option = FrameNode::GetOrCreateFrameNode(V2::OPTION_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<MenuItemPattern>(true, 0); });
    ASSERT_NE(option, nullptr);
    pattern->options_.push_back(option);
    pattern->options_.push_back(option);
    pattern->SetSelectedOptionFontSize(Dimension(20.00, DimensionUnit::VP));
    EXPECT_NE(pattern->options_[pattern->selected_]->GetPattern<MenuItemPattern>(), nullptr);
}

/**
 * @tc.name: SetSelectedOptionFontWeight001
 * @tc.desc: Test SelectModelNG SetSelectedOptionFontWeight001
 * @tc.type: FUNC
 */
HWTEST_F(SelectOneTestNg, SetSelectedOptionFontWeight001, TestSize.Level1)
{
    RefPtr<SelectPattern> pattern = AceType::MakeRefPtr<SelectPattern>();
    ASSERT_NE(pattern, nullptr);
    FrameNode frameNode = FrameNode(V2::SELECT_ETS_TAG, 1, pattern);
    frameNode_ = FrameNode::GetOrCreateFrameNode(V2::SELECT_ETS_TAG, ViewStackProcessor::GetInstance()->ClaimNodeId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    ASSERT_NE(frameNode_, nullptr);
    pattern->text_ = frameNode_;
    pattern->text_->SetLayoutProperty(AceType::MakeRefPtr<TextLayoutProperty>());
    SelectModelNG::SetSelectedOptionFontWeight(&frameNode, FontWeight::NORMAL);
    EXPECT_EQ(pattern->GetSelected(), -1);
}

/**
 * @tc.name: SetSelectedOptionFontWeight002
 * @tc.desc: Test SelectPattern SetSelectedOptionFontWeight
 * @tc.type: FUNC
 */
HWTEST_F(SelectOneTestNg, SetSelectedOptionFontWeight002, TestSize.Level1)
{
    RefPtr<SelectPattern> pattern = AceType::MakeRefPtr<SelectPattern>();
    ASSERT_NE(pattern, nullptr);
    FrameNode frameNode = FrameNode(V2::SELECT_ETS_TAG, 1, pattern);
    frameNode_ = FrameNode::GetOrCreateFrameNode(V2::SELECT_ETS_TAG, ViewStackProcessor::GetInstance()->ClaimNodeId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    ASSERT_NE(frameNode_, nullptr);
    pattern->text_ = frameNode_;
    pattern->text_->SetLayoutProperty(AceType::MakeRefPtr<TextLayoutProperty>());
    pattern->selected_ = 0;
    auto option = FrameNode::GetOrCreateFrameNode(V2::OPTION_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<MenuItemPattern>(true, 0); });
    ASSERT_NE(option, nullptr);
    pattern->options_.push_back(option);
    pattern->SetSelectedOptionFontWeight(FontWeight::NORMAL);
    EXPECT_NE(pattern->options_[pattern->selected_]->GetPattern<MenuItemPattern>(), nullptr);
}

/**
 * @tc.name: SetSelectedOptionFontFamily002
 * @tc.desc: Test SelectPattern SetSelectedOptionFontFamily
 * @tc.type: FUNC
 */
HWTEST_F(SelectOneTestNg, SetSelectedOptionFontFamily002, TestSize.Level1)
{
    RefPtr<SelectPattern> pattern = AceType::MakeRefPtr<SelectPattern>();
    ASSERT_NE(pattern, nullptr);
    FrameNode frameNode = FrameNode(V2::SELECT_ETS_TAG, 1, pattern);
    frameNode_ = FrameNode::GetOrCreateFrameNode(V2::SELECT_ETS_TAG, ViewStackProcessor::GetInstance()->ClaimNodeId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    ASSERT_NE(frameNode_, nullptr);
    pattern->text_ = frameNode_;
    pattern->text_->SetLayoutProperty(AceType::MakeRefPtr<TextLayoutProperty>());
    std::vector<std::string> value = { "select", "font", "family" };
    pattern->SetSelectedOptionFontFamily(value);
    EXPECT_EQ(pattern->GetSelected(), -1);
}

/**
 * @tc.name: InspectorGetSelectedFont001
 * @tc.desc: Test SelectPattern InspectorGetSelectedFont001
 * @tc.type: FUNC
 */
HWTEST_F(SelectOneTestNg, InspectorGetSelectedFont001, TestSize.Level1)
{
    SelectModelNG model;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    model.Create(params);
    ViewAbstract::SetWidth(CalcLength(100.f));
    ViewAbstract::SetHeight(CalcLength(40.f));
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    auto pattern = frameNode->GetPattern<SelectPattern>();
    frameNode->SetActive();
    frameNode->isLayoutDirtyMarked_ = true;
    frameNode->CreateLayoutTask();
    frameNode->SetActive(false);
    pattern->SetSelectedOptionItalicFontStyle(Ace::FontStyle::NORMAL);
    std::vector<std::string> selectParams = { "select", "font", "family" };
    pattern->SetSelectedOptionFontFamily(selectParams);
    pattern->SetSelectedOptionFontSize(Dimension(20.00, DimensionUnit::VP));
    pattern->SetSelectedOptionFontWeight(FontWeight::NORMAL);
    pattern->InspectorGetSelectedFont();
    EXPECT_TRUE(pattern->selectedFont_.FontStyle.has_value());
    EXPECT_TRUE(pattern->selectedFont_.FontSize.has_value());
    EXPECT_TRUE(pattern->selectedFont_.FontFamily.has_value());
    EXPECT_TRUE(pattern->selectedFont_.FontWeight.has_value());
}

/**
 * @tc.name: SetSelectedOptionFontFamily003
 * @tc.desc: Test SelectPattern SetSelectedOptionFontFamily
 * @tc.type: FUNC
 */
HWTEST_F(SelectOneTestNg, SetSelectedOptionFontFamily003, TestSize.Level1)
{
    RefPtr<SelectPattern> pattern = AceType::MakeRefPtr<SelectPattern>();
    ASSERT_NE(pattern, nullptr);
    FrameNode frameNode = FrameNode(V2::SELECT_ETS_TAG, 1, pattern);
    frameNode_ = FrameNode::GetOrCreateFrameNode(V2::SELECT_ETS_TAG, ViewStackProcessor::GetInstance()->ClaimNodeId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    ASSERT_NE(frameNode_, nullptr);
    pattern->text_ = frameNode_;
    pattern->text_->SetLayoutProperty(AceType::MakeRefPtr<TextLayoutProperty>());
    std::vector<std::string> value = { "select", "font", "family" };
    pattern->selected_ = 0;
    auto option = FrameNode::GetOrCreateFrameNode(V2::OPTION_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<MenuItemPattern>(true, 0); });
    ASSERT_NE(option, nullptr);
    pattern->options_.push_back(option);
    pattern->SetSelectedOptionFontFamily(value);
    EXPECT_NE(pattern->options_[pattern->selected_]->GetPattern<MenuItemPattern>(), nullptr);
}

/**
 * @tc.name: SetSelectedOptionItalicFontStyle001
 * @tc.desc: Test SelectModelNG SetSelectedOptionItalicFontStyle
 * @tc.type: FUNC
 */
HWTEST_F(SelectOneTestNg, SetSelectedOptionItalicFontStyle001, TestSize.Level1)
{
    RefPtr<SelectPattern> pattern = AceType::MakeRefPtr<SelectPattern>();
    ASSERT_NE(pattern, nullptr);
    FrameNode frameNode = FrameNode(V2::SELECT_ETS_TAG, 1, pattern);
    frameNode_ = FrameNode::GetOrCreateFrameNode(V2::SELECT_ETS_TAG, ViewStackProcessor::GetInstance()->ClaimNodeId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    ASSERT_NE(frameNode_, nullptr);
    pattern->text_ = frameNode_;
    pattern->text_->SetLayoutProperty(AceType::MakeRefPtr<TextLayoutProperty>());
    SelectModelNG::SetSelectedOptionItalicFontStyle(&frameNode, Ace::FontStyle::NORMAL);
    EXPECT_EQ(pattern->GetSelected(), -1);
}

/**
 * @tc.name: SetSelectedOptionItalicFontStyle002
 * @tc.desc: Test SelectPattern SetSelectedOptionItalicFontStyle
 * @tc.type: FUNC
 */
HWTEST_F(SelectOneTestNg, SetSelectedOptionItalicFontStyle002, TestSize.Level1)
{
    RefPtr<SelectPattern> pattern = AceType::MakeRefPtr<SelectPattern>();
    ASSERT_NE(pattern, nullptr);
    FrameNode frameNode = FrameNode(V2::SELECT_ETS_TAG, 1, pattern);
    frameNode_ = FrameNode::GetOrCreateFrameNode(V2::SELECT_ETS_TAG, ViewStackProcessor::GetInstance()->ClaimNodeId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    ASSERT_NE(frameNode_, nullptr);
    pattern->text_ = frameNode_;
    pattern->text_->SetLayoutProperty(AceType::MakeRefPtr<TextLayoutProperty>());
    pattern->selected_ = 0;
    pattern->SetSelectedOptionItalicFontStyle(Ace::FontStyle::NORMAL);
    EXPECT_EQ(pattern->GetSelected(), 0);
}

/**
 * @tc.name: SetSelectedOptionItalicFontStyle003
 * @tc.desc: Test SelectPattern SetSelectedOptionItalicFontStyle
 * @tc.type: FUNC
 */
HWTEST_F(SelectOneTestNg, SetSelectedOptionItalicFontStyle003, TestSize.Level1)
{
    RefPtr<SelectPattern> pattern = AceType::MakeRefPtr<SelectPattern>();
    ASSERT_NE(pattern, nullptr);
    FrameNode frameNode = FrameNode(V2::SELECT_ETS_TAG, 1, pattern);
    frameNode_ = FrameNode::GetOrCreateFrameNode(V2::SELECT_ETS_TAG, ViewStackProcessor::GetInstance()->ClaimNodeId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    pattern->text_ = frameNode_;
    pattern->text_->SetLayoutProperty(AceType::MakeRefPtr<TextLayoutProperty>());
    pattern->selected_ = 0;
    auto option = FrameNode::GetOrCreateFrameNode(V2::OPTION_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<MenuItemPattern>(true, 0); });
    ASSERT_NE(option, nullptr);
    pattern->options_.push_back(option);
    pattern->SetSelectedOptionItalicFontStyle(Ace::FontStyle::NORMAL);
    EXPECT_NE(pattern->options_[pattern->selected_]->GetPattern<MenuItemPattern>(), nullptr);
}

/**
 * @tc.name: SetOptionFontColor001
 * @tc.desc: Test SelectModelNG SetOptionFontColor
 * @tc.type: FUNC
 */
HWTEST_F(SelectOneTestNg, SetOptionFontColor001, TestSize.Level1)
{
    RefPtr<SelectPattern> pattern = AceType::MakeRefPtr<SelectPattern>();
    ASSERT_NE(pattern, nullptr);
    FrameNode frameNode = FrameNode(V2::SELECT_ETS_TAG, 1, pattern);
    frameNode_ = FrameNode::GetOrCreateFrameNode(V2::SELECT_ETS_TAG, ViewStackProcessor::GetInstance()->ClaimNodeId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    ASSERT_NE(frameNode_, nullptr);
    pattern->text_ = frameNode_;
    pattern->text_->SetLayoutProperty(AceType::MakeRefPtr<TextLayoutProperty>());
    SelectModelNG::SetOptionFontColor(&frameNode, Color::BLACK);
    EXPECT_EQ(pattern->GetSelected(), -1);
}

/**
 * @tc.name: OnAfterModifyDone001
 * @tc.desc: Test SelectModelNG OnAfterModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(SelectOneTestNg, OnAfterModifyDone001, TestSize.Level1)
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
     * @tc.steps: step3. Call OnAfterModifyDone.
     * @tc.expected: the function runs normally
     */
    selectPattern->OnAfterModifyDone();
    auto host = selectPattern->GetHost();
    EXPECT_NE(host->GetEventHub<SelectEventHub>(), nullptr);
}

/**
 * @tc.name: ShowSelectMenuTest003
 * @tc.desc: Test SelectModelNG ShowSelectMenuTest
 * @tc.type: FUNC
 */
HWTEST_F(SelectOneTestNg, ShowSelectMenuTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get frameNode and pattern.
     */
    TestProperty testProperty;
    testProperty.FontSize = std::make_optional(FONT_SIZE_VALUE);
    auto frameNode = CreateSelect(CREATE_VALUE, testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SelectPattern>();
    pattern->isFitTrigger_ = true;
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
 * @tc.name: SetDisabledStyle001
 * @tc.desc: Test SelectModelNG SetDisabledStyle
 * @tc.type: FUNC
 */
HWTEST_F(SelectOneTestNg, SetDisabledStyle001, TestSize.Level1)
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
    pattern->SetDisabledStyle();
    auto offset = pattern->GetHost()->GetPaintRectOffset();
    EXPECT_EQ(offset.GetY(), pattern->selectSize_.Height());
}

/**
 * @tc.name: UpdateLastSelectedProps001
 * @tc.desc: Test SelectPattern UpdateLastSelectedProps
 * @tc.type: FUNC
 */
HWTEST_F(SelectOneTestNg, UpdateLastSelectedProps001, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE }, { OPTION_TEXT, INTERNAL_SOURCE },
        { OPTION_TEXT_2, INTERNAL_SOURCE } };
    selectModelInstance.Create(params);
    auto select = AceType::MakeRefPtr<FrameNode>(V2::SELECT_ETS_TAG, 1, AceType::MakeRefPtr<SelectPattern>());
    EXPECT_TRUE(select && select->GetTag() == V2::SELECT_ETS_TAG);
    auto pattern = select->GetPattern<SelectPattern>();
    pattern->frameNode_ = AceType::WeakClaim(AceType::RawPtr(select));
    EXPECT_TRUE(pattern);
    pattern->selected_ = 1;
    auto option = FrameNode::GetOrCreateFrameNode(V2::OPTION_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<MenuItemPattern>(true, 0); });
    ASSERT_NE(option, nullptr);
    pattern->options_.push_back(option);
    pattern->UpdateLastSelectedProps(0);
    EXPECT_NE(pattern->options_[0]->GetPattern<MenuItemPattern>(), nullptr);
}

/**
 * @tc.name: UpdateLastSelectedProps002
 * @tc.desc: Test SelectPattern UpdateLastSelectedProps
 * @tc.type: FUNC
 */
HWTEST_F(SelectOneTestNg, UpdateLastSelectedProps002, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE }, { OPTION_TEXT, INTERNAL_SOURCE },
        { OPTION_TEXT_2, INTERNAL_SOURCE } };
    selectModelInstance.Create(params);
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_TRUE(select && select->GetTag() == V2::SELECT_ETS_TAG);
    auto pattern = select->GetPattern<SelectPattern>();
    EXPECT_TRUE(pattern);
    pattern->selected_ = 1;
    auto option = FrameNode::GetOrCreateFrameNode(V2::OPTION_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<MenuItemPattern>(true, 0); });
    ASSERT_NE(option, nullptr);
    pattern->options_.push_back(option);
    EXPECT_NE(pattern->options_.size(), 0);
    pattern->UpdateLastSelectedProps(3);
    EXPECT_EQ(pattern->options_[pattern->selected_]->GetPattern<MenuItemPattern>(), 1);
}

/**
 * @tc.name: UpdateText001
 * @tc.desc: Test SelectPattern UpdateText
 * @tc.type: FUNC
 */
HWTEST_F(SelectOneTestNg, UpdateText001, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE }, { OPTION_TEXT, INTERNAL_SOURCE },
        { OPTION_TEXT_2, INTERNAL_SOURCE } };
    selectModelInstance.Create(params);
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_TRUE(select && select->GetTag() == V2::SELECT_ETS_TAG);
    auto pattern = select->GetPattern<SelectPattern>();
    EXPECT_TRUE(pattern);
    const int32_t index = -1;
    pattern->UpdateText(index);
    EXPECT_EQ(pattern->selectValue_, "");
}

/**
 * @tc.name: UpdateText002
 * @tc.desc: Test SelectPattern UpdateText
 * @tc.type: FUNC
 */
HWTEST_F(SelectOneTestNg, UpdateText002, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE }, { OPTION_TEXT, INTERNAL_SOURCE },
        { OPTION_TEXT_2, INTERNAL_SOURCE } };
    selectModelInstance.Create(params);
    auto select = AceType::MakeRefPtr<FrameNode>(V2::SELECT_ETS_TAG, 1, AceType::MakeRefPtr<SelectPattern>());
    EXPECT_TRUE(select && select->GetTag() == V2::SELECT_ETS_TAG);
    auto pattern = select->GetPattern<SelectPattern>();
    pattern->text_ = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    EXPECT_TRUE(pattern);
    const int32_t index = 1;
    auto option = FrameNode::GetOrCreateFrameNode(V2::OPTION_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<MenuItemPattern>(true, 0); });
    ASSERT_NE(option, nullptr);
    pattern->options_.push_back(option);
    EXPECT_EQ(pattern->options_.size(), 1);
    pattern->UpdateText(index);
    EXPECT_EQ(pattern->selectValue_, "");
}

/**
 * @tc.name: ToJsonValue001
 * @tc.desc: Test SelectPattern ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(SelectOneTestNg, ToJsonValue001, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE }, { OPTION_TEXT, INTERNAL_SOURCE },
        { OPTION_TEXT_2, INTERNAL_SOURCE } };
    selectModelInstance.Create(params);
    auto select = AceType::MakeRefPtr<FrameNode>(V2::SELECT_ETS_TAG, 1, AceType::MakeRefPtr<SelectPattern>());
    EXPECT_TRUE(select && select->GetTag() == V2::SELECT_ETS_TAG);
    auto pattern = select->GetPattern<SelectPattern>();
    pattern->frameNode_ = AceType::WeakClaim(AceType::RawPtr(select));
    pattern->text_ = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    std::unique_ptr<JsonValue> jsonValue = std::make_unique<JsonValue>();
    ASSERT_NE(jsonValue, nullptr);
    pattern->ToJsonValue(jsonValue, filter);
    EXPECT_TRUE(pattern->options_.empty());
}

/**
 * @tc.name: ToJsonValue002
 * @tc.desc: Test SelectPattern ToJsonValue002
 * @tc.type: FUNC
 */
HWTEST_F(SelectOneTestNg, ToJsonValue002, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE }, { OPTION_TEXT, INTERNAL_SOURCE },
        { OPTION_TEXT_2, INTERNAL_SOURCE } };
    selectModelInstance.Create(params);
    auto select = AceType::MakeRefPtr<FrameNode>(V2::SELECT_ETS_TAG, 1, AceType::MakeRefPtr<SelectPattern>());
    EXPECT_TRUE(select && select->GetTag() == V2::SELECT_ETS_TAG);
    auto pattern = select->GetPattern<SelectPattern>();
    pattern->frameNode_ = AceType::WeakClaim(AceType::RawPtr(select));
    pattern->text_ = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    std::unique_ptr<JsonValue> jsonValue = std::make_unique<JsonValue>();
    ASSERT_NE(jsonValue, nullptr);
    auto option = FrameNode::GetOrCreateFrameNode(V2::OPTION_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<MenuItemPattern>(true, 0); });
    ASSERT_NE(option, nullptr);
    pattern->options_.push_back(option);
    pattern->menuWrapper_ = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    pattern->ToJsonValue(jsonValue, filter);
    EXPECT_FALSE(pattern->options_.empty());
}

/**
 * @tc.name: ToJsonValue003
 * @tc.desc: Test SelectPattern ToJsonDividerMode
 * @tc.type: FUNC
 */
HWTEST_F(SelectOneTestNg, ToJsonValue003, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE }, { OPTION_TEXT, INTERNAL_SOURCE },
        { OPTION_TEXT_2, INTERNAL_SOURCE } };
    selectModelInstance.Create(params);
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto pattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(pattern, nullptr);
    auto menuNode = pattern->GetMenuNode();
    ASSERT_NE(menuNode, nullptr);
    auto menuLayoutProps = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(menuLayoutProps, nullptr);
    auto json = JsonUtil::Create(true);
    pattern->ToJsonDividerMode(json);
    EXPECT_EQ(json->GetString("dividerMode", ""), "");
    menuLayoutProps->UpdateItemDividerMode(DividerMode::FLOATING_ABOVE_MENU);
    pattern->ToJsonDividerMode(json);
    EXPECT_EQ(json->GetString("dividerMode", ""), "FLOATING_ABOVE_MENU");
    json->Delete("dividerMode");
    menuLayoutProps->UpdateItemDividerMode(DividerMode::EMBEDDED_IN_MENU);
    pattern->ToJsonDividerMode(json);
    EXPECT_EQ(json->GetString("dividerMode", ""), "EMBEDDED_IN_MENU");
}

HWTEST_F(SelectOneTestNg, SelectLayoutPropertyTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get frameNode and geometryNode.
     */
    TestProperty testProperty;
    testProperty.FontSize = std::make_optional(FONT_SIZE_VALUE);
    auto frameNode = CreateSelect(CREATE_VALUE, testProperty);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    /**
     * @tc.steps: step2. Get layoutWrapper and Call Measure.
     * @tc.expected: the function exits normally
     */
    auto layoutProperty = frameNode->GetLayoutProperty();
    LayoutWrapperNode* layoutWrapper = new LayoutWrapperNode(frameNode, geometryNode, layoutProperty);
    auto text = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    RefPtr<GeometryNode> geometryNode2 = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapperNode = AceType::MakeRefPtr<LayoutWrapperNode>(text, geometryNode2, text->GetLayoutProperty());
    auto layoutAlgorithm = AceType::MakeRefPtr<SelectLayoutAlgorithm>();
    layoutWrapper->childrenMap_.insert({ 0, layoutWrapperNode });
    layoutWrapper->childrenMap_.insert({ 1, layoutWrapperNode });
    layoutWrapper->currentChildCount_ = layoutWrapper->childrenMap_.size();
    RefPtr<LazyForEachActuator> actuator = AceType::MakeRefPtr<LazyForEachActuator>();
    auto builder = AceType::DynamicCast<LazyForEachBuilder>(actuator);
    constexpr int32_t NODE_ID_1 = 1;
    RefPtr<LazyForEachNode> host_ = AceType::MakeRefPtr<LazyForEachNode>(NODE_ID_1, builder);
    WeakPtr<LazyForEachNode> host(host_);
    RefPtr<LazyLayoutWrapperBuilder> wrapperBuilder = AceType::MakeRefPtr<LazyLayoutWrapperBuilder>(builder, host);
    layoutWrapper->layoutWrapperBuilder_ = wrapperBuilder;
    layoutAlgorithm->Measure(layoutWrapper);
    EXPECT_NE(layoutWrapper->GetOrCreateChildByIndex(0), nullptr);
}


HWTEST_F(SelectOneTestNg, selectMenuPatterntTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get frameNode and geometryNode.
     */
    SelectModelNG selectModelNG;
    std::vector<SelectParam> params;
    SelectParam sparam_one;
    sparam_one.text = "100";
    sparam_one.icon = "icon_one";
    params.push_back(sparam_one);
    selectModelNG.Create(params);
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    auto node = [params](MenuItemConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(params[0].text, config.value_);
        EXPECT_EQ(params[0].icon, config.icon_);
    return nullptr;
    };
    selectModelNG.SetBuilderFunc(select, node);
    auto menuNode = selectPattern->GetMenuNode();
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    for (int i = 0; i < params.size(); i++) {
        menuPattern->BuildContentModifierNode(i);
    }
}

/**
 * @tc.name: SelectLayoutPropertyTest007
 * @tc.desc: Test Select Create with Symbol.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOneTestNg, SelectLayoutPropertyTest007, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params;
    SelectParam sparam_one;
    sparam_one.text = "100";
    sparam_one.icon = "icon_one";
    auto onApply = [](WeakPtr<NG::FrameNode> frameNode) {
        auto node = frameNode.Upgrade();
        EXPECT_NE(node, nullptr);
    };
    sparam_one.symbolIcon = onApply;
    params.push_back(sparam_one);
    selectModelInstance.Create(params);
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_TRUE(select && select->GetTag() == V2::SELECT_ETS_TAG);
    auto pattern = select->GetPattern<SelectPattern>();
    EXPECT_TRUE(pattern);
    auto options = pattern->GetOptions();
    EXPECT_EQ(options.size(), params.size());
    RefPtr<FrameNode> row =
        options[0]->GetChildAtIndex(0) ? AceType::DynamicCast<FrameNode>(options[0]->GetChildAtIndex(0)) : nullptr;
    EXPECT_NE(row, nullptr);
    RefPtr<FrameNode> icon =
        row->GetChildAtIndex(0) ? AceType::DynamicCast<FrameNode>(row->GetChildAtIndex(0)) : nullptr;
    EXPECT_NE(icon, nullptr);
    EXPECT_EQ(icon->GetTag(), V2::SYMBOL_ETS_TAG);
}

/**
 * @tc.name: SelectLayoutPropertyTest008
 * @tc.desc: Test Select set textDirection.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOneTestNg, SelectLayoutPropertyTest008, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    // create select
    std::vector<SelectParam> params = { {OPTION_TEXT, FILE_SOURCE }, { OPTION_TEXT, INTERNAL_SOURCE},
        { OPTION_TEXT_2, INTERNAL_SOURCE } };
    selectModelInstance.Create(params);
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    /**
     * @tc.cases: case1. verify the SetLayoutDirection function.
     */
    selectPattern->SetLayoutDirection(TextDirection::RTL);
    auto layoutProps = selectPattern->GetLayoutProperty<LayoutProperty>();
    ASSERT_NE(layoutProps, nullptr);
    auto direction = layoutProps->GetNonAutoLayoutDirection();
    ASSERT_EQ(direction, TextDirection::RTL);
}

/**
 * @tc.name: SelectMenuOutline001
 * @tc.desc: Test SelectModelNG SelectMenuOutline.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOneTestNg, SelectMenuOutline001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build select model instance an parameters.
     * @tc.expected: Objects are created successfully.
     */
    Dimension outlineWidthVaule = Dimension(10.0f, DimensionUnit::VP);
    Color outlineColorValue = Color::RED;
    MenuParam menuParam;
    menuParam.outlineWidth->SetBorderWidth(outlineWidthVaule);
    menuParam.outlineColor->SetColor(outlineColorValue);
    SelectModelNG selectModelInstance;
    /**
     * @tc.steps: step2. Call SetMenuOutline.
     */
    selectModelInstance.SetMenuOutline(menuParam);
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto selectPattern = select->GetPattern<SelectPattern>();
    /**
     * @tc.steps: step3. Call SetMenuOutline.
     * @tc.expected: Attributes are called successfully.
     */
    auto menu = selectPattern->GetMenuNode();
    auto renderContext = menu->GetRenderContext();
    EXPECT_EQ(renderContext->GetOuterBorderColor(), menuParam.outlineColor);
    EXPECT_EQ(renderContext->GetOuterBorderWidth(), menuParam.outlineWidth);
}

/**
 * @tc.name: GetSelectTheme001
 * @tc.desc: Test GetSelectTheme with valid frameNode and valid context, expect correct SelectTheme returned.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOneTestNg, GetSelectTheme001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FrameNode with SelectPattern and MockPipelineContext.
     * @tc.expected: step1. FrameNode and context are created successfully.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SELECT_ETS_TAG, 1, AceType::MakeRefPtr<SelectPattern>());
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    auto pipelineContext = MockPipelineContext::GetCurrent();
    pipelineContext->SetThemeManager(themeManager);
    
    /**
     * @tc.steps: step2. Prepare SelectTheme and mock themeManager to return it.
     * @tc.expected: step2. Mocked themeManager returns the prepared SelectTheme.
     */
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(selectTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(selectTheme));
    frameNode->DetachContext(pipelineContext);
    
    /**
     * @tc.steps: step3. Call GetSelectTheme and verify the result.
     * @tc.expected: step3. The returned SelectTheme matches the prepared one.
     */
    auto result = SelectModelNG::GetSelectTheme(frameNode.GetRawPtr());
    EXPECT_EQ(result, selectTheme);
}

/**
 * @tc.name: ResetComponentColor001
 * @tc.desc: Test ResetSelectComponentColor.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOneTestNg, ResetComponentColor001, TestSize.Level1)
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
     * @tc.steps: step2. Setup MockThemeManager and SelectTheme.
     * @tc.expected: step2. ThemeManager and theme are initialized.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    auto pipelineContext = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->SetThemeManager(themeManager);
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    ASSERT_NE(selectTheme, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(selectTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(selectTheme));
    auto host = pattern->GetHost();
    ASSERT_NE(host, nullptr);
    
    /**
     * @tc.steps: step3. Set theme colors and pattern font color, then reset colors for different types.
     * @tc.expected: step3. All component colors are reset to theme's RED value.
     */
    selectTheme->fontColor_ = Color::RED;
    selectTheme->backgroundColor_ = Color::RED;
    selectTheme->selectedColor_ = Color::RED;
    selectTheme->selectedColorText_ = Color::RED;
    selectTheme->menuFontColor_ = Color::RED;
    selectTheme->menuBlendBgColor_ = true;
    pattern->SetMenuBackgroundColor(Color::RED);
    pattern->SetOptionFontColor(Color::RED);
    std::vector<SelectColorType> colorTypes = { SelectColorType::FONT_COLOR, SelectColorType::BACKGROUND_COLOR,
        SelectColorType::SELECTED_OPTION_BG_COLOR, SelectColorType::SELECTED_OPTION_FONT_COLOR,
        SelectColorType::OPTION_BG_COLOR, SelectColorType::OPTION_FONT_COLOR, SelectColorType::MENU_BACKGROUND_COLOR,
        static_cast<SelectColorType>(999) };
    for (const auto& type : colorTypes) {
        SelectModelNG::ResetComponentColor(frameNode, type);
    }
    
    /**
     * @tc.steps: step4. Verify reset colors match the theme's RED value.
     * @tc.expected: step4. All verified colors are RED.
     */
    EXPECT_EQ(pattern->selectedBgColor_, Color::RED);
    EXPECT_EQ(pattern->selectedFont_.FontColor, Color::RED);
    EXPECT_EQ(pattern->optionFont_.FontColor, Color::RED);
    EXPECT_EQ(pattern->menuBackgroundColor_, Color::RED);
}

/**
 * @tc.name: ResetComponentColor002
 * @tc.desc: Test ResetSelectComponentColor.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOneTestNg, ResetComponentColor002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Select and get pattern.
     * @tc.expected: SelectPattern created successfully.
     */
    SelectModelNG selectModelNG;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE }, { OPTION_TEXT_2, INTERNAL_SOURCE } };
    selectModelNG.Create(params);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SelectPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Setup mock theme and pipeline context.
     * @tc.expected: Mock theme injected.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    auto pipelineContext = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->SetThemeManager(themeManager);
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    ASSERT_NE(selectTheme, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(selectTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(selectTheme));

    /**
     * @tc.steps: step3. Set theme colors and override pattern colors.
     * @tc.expected: pattern colors set to RED, theme colors are GREEN.
     */
    auto selectLayoutProps = frameNode->GetLayoutProperty<SelectLayoutProperty>();
    ASSERT_NE(selectLayoutProps, nullptr);
    selectTheme->selectedColor_ = Color::GREEN;
    pattern->SetSelectedOptionBgColor(Color::RED);
    SelectModelNG::SetShowDefaultSelectedIcon(frameNode, true);
    SelectModelNG::ResetComponentColor(frameNode, SelectColorType::SELECTED_OPTION_BG_COLOR);

    /**
     * @tc.steps: step4. Validate that colors were not changed (reset skipped).
     */
    EXPECT_EQ(selectLayoutProps->GetShowDefaultSelectedIconValue(false), true);
    EXPECT_EQ(pattern->selectedBgColor_, Color::RED);
}

/**
 * @tc.name: CreateWithValueIconResourceObj
 * @tc.desc: Test CreateWithValueIconResourceObj with null and valid ResourceObject.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOneTestNg, CreateWithValueIconResourceObj, TestSize.Level1)
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
     * @tc.steps: step2. Test with null ResourceObject params.
     * @tc.expected: step2. No exception thrown when null params are passed.
     */
    SelectResObjParam nullObjParam;
    nullObjParam.valueResObj = nullptr;
    nullObjParam.iconResObj = nullptr;
    selectModelNG.CreateWithValueIconResourceObj({ nullObjParam });
    
    /**
     * @tc.steps: step3. Create valid value and icon ResourceObjects.
     * @tc.expected: step3. ResourceObjects are created with valid parameters.
     */
    ResourceObjectParams valueParam;
    valueParam.type = ResourceObjectParamType::STRING;
    valueParam.value = "TEXT";
    auto valueResObj = AceType::MakeRefPtr<ResourceObject>(1001, static_cast<int32_t>(Kit::ResourceType::STRING),
        std::vector<ResourceObjectParams> { valueParam }, "bundle", "module", 0);

    ResourceObjectParams iconParam;
    iconParam.type = ResourceObjectParamType::STRING;
    iconParam.value = "ICON.svg";
    auto iconResObj = AceType::MakeRefPtr<ResourceObject>(1002, static_cast<int32_t>(Kit::ResourceType::MEDIA),
        std::vector<ResourceObjectParams> { iconParam }, "bundle", "module", 0);
    
    /**
     * @tc.steps: step4. Test with valid params and verify menu pattern state.
     * @tc.expected: step4. MenuPattern's isSelectMenu_ is set to true after valid resource creation.
     */
    SelectResObjParam validObjParam;
    validObjParam.valueResObj = valueResObj;
    validObjParam.iconResObj = iconResObj;
    auto menuNode = pattern->GetMenuNode();
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    selectModelNG.CreateWithValueIconResourceObj({ validObjParam });
    EXPECT_TRUE(menuPattern->isSelectMenu_);
}

/**
 * @tc.name: CreateWithIntegerResourceObj
 * @tc.desc: Test CreateWithIntegerResourceObj.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOneTestNg, CreateWithIntegerResourceObj, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create SelectModelNG and initialize frameNode with SelectPattern.
     * @tc.expected: step1. Model and frameNode are created successfully.
     */
    SelectModelNG selectModelNG;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE }, { OPTION_TEXT, INTERNAL_SOURCE },
        { OPTION_TEXT_2, INTERNAL_SOURCE } };
    selectModelNG.Create(params);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    RefPtr<SelectPattern> pattern = AceType::MakeRefPtr<SelectPattern>();
    ASSERT_NE(pattern, nullptr);
    
    /**
     * @tc.steps: step2. Test with null ResourceObject and verify selected value is not zero.
     * @tc.expected: step2. GetSelected() does not return zero when null resource is passed.
     */
    selectModelNG.CreateWithIntegerResourceObj(nullptr);
    EXPECT_NE(pattern->GetSelected(), 0);
    
    /**
     * @tc.steps: step3. Create valid integer ResourceObject and test selected value.
     * @tc.expected: step3. GetSelected() returns -1 when valid resource with "-1" is passed.
     */
    ResourceObjectParams param;
    param.type = ResourceObjectParamType::INT;
    param.value = "-1";
    int32_t resourceType = static_cast<int32_t>(Kit::ResourceType::INTEGER);
    auto resObj = AceType::MakeRefPtr<ResourceObject>(
        1001, resourceType, std::vector<ResourceObjectParams> { param }, "testBundle", "testModule", 0);
    selectModelNG.CreateWithIntegerResourceObj(resObj);
    EXPECT_EQ(pattern->GetSelected(), -1);
    
    /**
     * @tc.steps: step4. Add resource to cache and reload, verifying resource manager interaction.
     * @tc.expected: step4. Resource is added to cache and resource manager is accessed.
     */
    std::string key = "selectSelected";
    pattern->AddResCache(key, param.value.value());
    auto resMgr = pattern->resourceMgr_;
    ASSERT_NE(resMgr, nullptr);
    resMgr->ReloadResources();
}

/**
 * @tc.name: InitSelect
 * @tc.desc: Test InitSelect function.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOneTestNg, InitSelect, TestSize.Level1)
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
    auto pipeline = frameNode->GetContextWithCheck();
    ASSERT_NE(pipeline, nullptr);
    auto selectTheme = pipeline->GetTheme<SelectTheme>(frameNode->GetThemeScopeId());
    ASSERT_NE(selectTheme, nullptr);
    
    auto* stack = ViewStackProcessor::GetInstance();
    int32_t nodeId = (stack == nullptr ? 0 : stack->ClaimNodeId());
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::SELECT_ETS_TAG, nodeId);
    auto select = FrameNode::GetOrCreateFrameNode(
        V2::SELECT_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<SelectPattern>(); });
    ViewStackProcessor::GetInstance()->Push(select);

    selectTheme->selectLeftMarginMap_.insert(std::pair<ControlSize, Dimension>(ControlSize::NORMAL, 8.0_px));
    selectTheme->selectRightMarginMap_.insert(std::pair<ControlSize, Dimension>(ControlSize::NORMAL, 8.0_px));

    selectModelNG.InitSelect(AceType::RawPtr(select), params);

    auto padding = ViewAbstract::GetPadding(frameNode);
    EXPECT_EQ(padding.left.value().GetDimension().ConvertToPx(), 8.0);
    EXPECT_EQ(padding.right.value().GetDimension().ConvertToPx(), 8.0);
}

/**
 * @tc.name: OnModifyDone001
 * @tc.desc: Test SelectPattern OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(SelectOneTestNg, OnModifyDone001, TestSize.Level1)
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
 * @tc.name: OnModifyDone014
 * @tc.desc: Test SelectPattern OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(SelectOneTestNg, OnModifyDone014, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto menuNode = selectPattern->GetMenuNode();
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    auto pipeline = select->GetContextWithCheck();
    ASSERT_NE(pipeline, nullptr);
    auto selectTheme = pipeline->GetTheme<SelectTheme>(select->GetThemeScopeId());
    ASSERT_NE(selectTheme, nullptr);
    auto host = selectPattern->GetHost();
    auto eventHub = host->GetEventHub<SelectEventHub>();
    EXPECT_NE(eventHub, nullptr);
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    eventHub->SetEnabled(false);
    selectTheme->isTV_ = true;
    selectPattern->OnModifyDone();
    auto val = menuPattern->IsSelectMenu();
    EXPECT_EQ(val, true);
    selectTheme->isTV_ = false;
    selectPattern->OnModifyDone();
    val = menuPattern->IsSelectMenu();
    EXPECT_EQ(val, true);

    eventHub->SetEnabled(true);
    selectTheme->isTV_ = true;
    selectPattern->OnModifyDone();
    val = menuPattern->IsSelectMenu();
    EXPECT_EQ(val, true);
    selectTheme->isTV_ = false;
    selectPattern->OnModifyDone();
    val = menuPattern->IsSelectMenu();
    EXPECT_EQ(val, true);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}
} // namespace OHOS::Ace::NG
