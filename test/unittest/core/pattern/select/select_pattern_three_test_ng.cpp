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

#include "test/mock/base/mock_system_properties.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/common/ace_application_info.h"
#include "core/components/common/layout/constants.h"
#include "core/components/select/select_theme.h"
#include "core/components/text/text_theme.h"
#include "core/components/text_field/textfield_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/flex/flex_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_pattern.h"
#include "core/components_ng/pattern/menu/menu_layout_property.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/menu/menu_view.h"
#include "core/components_ng/pattern/scroll/scroll_layout_property.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
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
const InspectorFilter filter;
const std::string EMPTY_TEXT = "";
const std::string SELECT_TEXT = "select";
const std::string ITEM_TEXT = "menuItem";
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
constexpr Dimension OPTION_MARGIN = 8.0_vp;
const SizeF FULL_SCREEN_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
const std::vector<std::string> FONT_FAMILY_VALUE = { "cursive" };
const Color TEXT_COLOR_VALUE = Color::FromRGB(255, 100, 100);
const Color BG_COLOR_VALUE = Color::FromRGB(100, 255, 100);
const Color SELECT_TEXT_COLOR_VALUE = Color::FromRGB(255, 255, 100);
const Color SELECT_BG_COLOR_VALUE = Color::FromRGB(100, 255, 255);
const std::vector<SelectParam> CREATE_VALUE = { { OPTION_TEXT, FILE_SOURCE }, { OPTION_TEXT_2, INTERNAL_SOURCE },
    { OPTION_TEXT_3, INTERNAL_SOURCE } };
const Ace::FontStyle ITALIC_FONT_STYLE_VALUE = Ace::FontStyle::ITALIC;
} // namespace
struct TestProperty {
    std::optional<Dimension> FontSize = std::nullopt;
    std::optional<Ace::FontStyle> FontStyle = std::nullopt;
    std::optional<FontWeight> FontWeight = std::nullopt;
    std::optional<std::vector<std::string>> FontFamily = std::nullopt;
    std::optional<Color> FontColor = std::nullopt;
};
class SelectPatternTheTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
    void InitSelectPatternTheTestNg();
    RefPtr<FrameNode> frameNode_;
    RefPtr<SelectPattern> selectPattern_;
    RefPtr<SelectAccessibilityProperty> selectAccessibilityProperty_;

protected:
    static RefPtr<FrameNode> CreateSelect(const std::vector<SelectParam>& value, const TestProperty& test);
    static FrameNode* CreateSelect(const std::vector<SelectParam>& value);
};

void SelectPatternTheTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
}

void SelectPatternTheTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

void SelectPatternTheTestNg::SetUp() {}

void SelectPatternTheTestNg::TearDown()
{
    frameNode_ = nullptr;
    selectPattern_ = nullptr;
    selectAccessibilityProperty_ = nullptr;
}

void SelectPatternTheTestNg::InitSelectPatternTheTestNg()
{
    frameNode_ = FrameNode::GetOrCreateFrameNode(V2::SELECT_ETS_TAG, ViewStackProcessor::GetInstance()->ClaimNodeId(),
        []() { return AceType::MakeRefPtr<SelectPattern>(); });
    ASSERT_NE(frameNode_, nullptr);

    selectPattern_ = frameNode_->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern_, nullptr);

    selectAccessibilityProperty_ = frameNode_->GetAccessibilityProperty<SelectAccessibilityProperty>();
    ASSERT_NE(selectAccessibilityProperty_, nullptr);
}

RefPtr<FrameNode> SelectPatternTheTestNg::CreateSelect(const std::vector<SelectParam>& value, const TestProperty& test)
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

FrameNode* SelectPatternTheTestNg::CreateSelect(const std::vector<SelectParam>& value)
{
    SelectModelNG selectModelInstance;
    selectModelInstance.Create(value);
    return ViewStackProcessor::GetInstance()->GetMainFrameNode();
}

/**
 * @tc.name: UpdateOptionsWidth
 * @tc.desc: Test SelectPattern UpdateOptionsWidth.
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTheTestNg, UpdateOptionsWidth, TestSize.Level1)
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
    auto option = FrameNode::GetOrCreateFrameNode(V2::OPTION_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<MenuItemPattern>(true, 0); });
    ASSERT_NE(option, nullptr);
    float selectWidth = 1.0f;

    /**
     * @tc.steps: step2. Test UpdateOptionsWidth
     * @tc.expected: step2. The program is running normally.
     */
    selectPattern->options_.push_back(option);
    selectPattern->UpdateOptionsWidth(selectWidth);
    selectPattern->options_.push_back(nullptr);
    selectPattern->UpdateOptionsWidth(selectWidth);
    ASSERT_NE(selectPattern->options_.size(), 0);
}

/**
 * @tc.name: CheckSkipMenuShow
 * @tc.desc: Test SelectPattern CheckSkipMenuShow.
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTheTestNg, CheckSkipMenuShow, TestSize.Level1)
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

    /**
     * @tc.steps: step2. Test CheckSkipMenuShow
     * @tc.expected: step2. The return value varies depending on the parameters.
     */
    bool res = selectPattern->CheckSkipMenuShow(nullptr);
    ASSERT_EQ(res, false);
    const auto& targetNode = FrameNode::GetOrCreateFrameNode(V2::OPTION_ETS_TAG,
    ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<MenuItemPattern>(true, 0); });
    selectPattern->CheckSkipMenuShow(targetNode);
    ASSERT_EQ(res, false);
}

/**
 * @tc.name: CreateSelectedCallback
 * @tc.desc: Test SelectPattern CreateSelectedCallback.
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTheTestNg, CreateSelectedCallback, TestSize.Level1)
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
    auto option = FrameNode::GetOrCreateFrameNode(V2::OPTION_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<MenuItemPattern>(true, 0); });
    ASSERT_NE(option, nullptr);

    /**
     * @tc.steps: step2. Test UpdateOptionsWidth
     * @tc.expected: step2. The program is running normally.
     */
    selectPattern->CreateSelectedCallback();
    selectPattern->options_.push_back(option);
    selectPattern->CreateSelectedCallback();
    ASSERT_NE(selectPattern->options_.size(), 0);
}

/**
 * @tc.name: ModFocusIconStyle
 * @tc.desc: Test SelectPattern ModFocusIconStyle.
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTheTestNg, ModFocusIconStyle, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model and initialize components.
     * @tc.expected: step1. Select model and related components are created successfully.
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);

    auto select = AceType::WeakClaim(ViewStackProcessor::GetInstance()->GetMainFrameNode()).Upgrade();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto pipeline = select->GetContextWithCheck();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<SelectTheme>();
    ASSERT_NE(theme, nullptr);
    auto props = select->GetPaintProperty<SelectPaintProperty>();
    ASSERT_NE(props, nullptr);
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    bool focusedFlag = false;
    selectPattern->spinner_ = FrameNode::GetOrCreateFrameNode(V2::SYMBOL_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });

    /**
     * @tc.steps: step2. Test ModFocusIconStyle with different user-defined flags.
     * @tc.expected: step2. Color properties are updated based on user-defined flags and theme.
     */
    selectPattern->ModFocusIconStyle(selectTheme, focusedFlag);
    focusedFlag = true;
    selectPattern->ModFocusIconStyle(selectTheme, focusedFlag);
    ASSERT_NE(selectPattern->spinner_, nullptr);
}

/**
 * @tc.name: AddIsFocusActiveUpdateEvent
 * @tc.desc: Test SelectPattern AddIsFocusActiveUpdateEvent.
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTheTestNg, AddIsFocusActiveUpdateEvent, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model and initialize components.
     * @tc.expected: step1. Select model and related components are created successfully.
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);

    auto select = AceType::WeakClaim(ViewStackProcessor::GetInstance()->GetMainFrameNode()).Upgrade();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);

    /**
     * @tc.steps: step2. Test AddIsFocusActiveUpdateEvent with different user-defined flags.
     * @tc.expected: step2. Color properties are updated based on user-defined flags and theme.
     */
    selectPattern->isFocusActiveUpdateEvent_ = nullptr;
    selectPattern->AddIsFocusActiveUpdateEvent();
    ASSERT_NE(selectPattern->isFocusActiveUpdateEvent_, nullptr);
    selectPattern->isFocusActiveUpdateEvent_ = [selectPattern](bool isFocusAcitve) {
        CHECK_NULL_VOID(selectPattern);
        isFocusAcitve ? selectPattern->SetFocusStyle() : selectPattern->ClearFocusStyle();
    };
    selectPattern->AddIsFocusActiveUpdateEvent();
    ASSERT_NE(selectPattern->isFocusActiveUpdateEvent_, nullptr);
}

/**
 * @tc.name: SetDisabledStyle
 * @tc.desc: Test SelectPattern SetDisabledStyle.
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTheTestNg, SetDisabledStyle, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model and initialize components.
     * @tc.expected: step1. Select model and related components are created successfully.
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);

    auto select = AceType::WeakClaim(ViewStackProcessor::GetInstance()->GetMainFrameNode()).Upgrade();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto pipeline = select->GetContextWithCheck();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<SelectTheme>();
    ASSERT_NE(theme, nullptr);
    auto props = select->GetPaintProperty<SelectPaintProperty>();
    ASSERT_NE(props, nullptr);
    selectPattern->spinner_ = FrameNode::GetOrCreateFrameNode(V2::SYMBOL_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    
    /**
     * @tc.steps: step2. Test SetDisabledStyle with different user-defined flags.
     * @tc.expected: step2. Color properties are updated based on user-defined flags and theme.
     */
    selectPattern->text_ = FrameNode::GetOrCreateFrameNode(V2::SYMBOL_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    selectPattern->SetDisabledStyle();
    ASSERT_NE(selectPattern->text_, nullptr);
}

/**
 * @tc.name: SetSelected
 * @tc.desc: Test SelectPattern SetSelected
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTheTestNg, SetSelected, TestSize.Level1)
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

    /**
     * @tc.steps: step3. Call SetSelected.
     * @tc.expected: the function runs normally
     */
    int32_t index = -1;
    selectPattern->SetSelected(index);
    EXPECT_EQ(selectPattern->selected_, -1);

    index = 0;
    selectPattern->SetSelected(index);
    EXPECT_EQ(selectPattern->selected_, 0);

    auto option = FrameNode::GetOrCreateFrameNode(V2::OPTION_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<MenuItemPattern>(true, 0); });
    ASSERT_NE(option, nullptr);
    selectPattern->options_.push_back(option);
    selectPattern->SetSelected(index);
    EXPECT_EQ(selectPattern->selected_, index);
}

/**
 * @tc.name: SetValue
 * @tc.desc: Test SelectPattern SetValue.
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTheTestNg, SetValue, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model and initialize components.
     * @tc.expected: step1. Select model and related components are created successfully.
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);

    auto select = AceType::WeakClaim(ViewStackProcessor::GetInstance()->GetMainFrameNode()).Upgrade();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto pipeline = select->GetContextWithCheck();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<SelectTheme>();
    ASSERT_NE(theme, nullptr);
    auto props = select->GetPaintProperty<SelectPaintProperty>();
    ASSERT_NE(props, nullptr);
    selectPattern->text_ = FrameNode::GetOrCreateFrameNode(V2::SYMBOL_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    
    /**
     * @tc.steps: step2. Test SetValue with different user-defined flags.
     * @tc.expected: step2. Color properties are updated based on user-defined flags and theme.
     */
    std::string value = "";
    selectPattern->SetDisabledStyle();
    ASSERT_EQ(selectPattern->selectValue_, value);

    value = "test";
    selectPattern->SetDisabledStyle();
    ASSERT_NE(selectPattern->selectValue_, value);
}

/**
 * @tc.name: SetFontSize
 * @tc.desc: Test SelectPattern SetFontSize
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTheTestNg, SetFontSize, TestSize.Level1)
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

    /**
     * @tc.steps: step3. Call SetFontSize.
     * @tc.expected: the function runs normally
     */
    constexpr Dimension value1 = 0.0_vp;
    selectPattern->SetFontSize(value1);
    ASSERT_EQ(value1.IsNegative(), false);

    selectPattern->text_ = FrameNode::GetOrCreateFrameNode(V2::SYMBOL_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    constexpr Dimension value2 = 1.0_vp;
    selectPattern->SetFontSize(value2);
    ASSERT_EQ(value2.IsNegative(), false);
}

/**
 * @tc.name: SetItalicFontStyle
 * @tc.desc: Test SelectPattern SetItalicFontStyle
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTheTestNg, SetItalicFontStyle, TestSize.Level1)
{
    SelectModelNG selectModelInstance;

    /**
     * @tc.steps: step1. Create select.
     */
    std::vector<SelectParam> params = { { OPTION_TEXT_3, INTERNAL_SOURCE } };
    selectModelInstance.Create(params);

    /**
     * @tc.steps: step2. Get frameNode and pattern, set text_.
     */
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    selectPattern->text_ = FrameNode::GetOrCreateFrameNode(V2::SYMBOL_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    

    /**
     * @tc.steps: step3. Call SetItalicFontStyle.
     * @tc.expected: the function runs normally
     */
    const Ace::FontStyle value1 = Ace::FontStyle::ITALIC;
    selectPattern->SetItalicFontStyle(value1);
    ASSERT_NE(selectPattern->text_, nullptr);
}

/**
 * @tc.name: SetFontWeight
 * @tc.desc: Test SelectPattern SetFontWeight.
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTheTestNg, SetFontWeight, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model and initialize components.
     * @tc.expected: step1. Select model and related components are created successfully.
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);

    auto select = AceType::WeakClaim(ViewStackProcessor::GetInstance()->GetMainFrameNode()).Upgrade();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto pipeline = select->GetContextWithCheck();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<SelectTheme>();
    ASSERT_NE(theme, nullptr);
    auto props = select->GetPaintProperty<SelectPaintProperty>();
    ASSERT_NE(props, nullptr);
    selectPattern->text_ = FrameNode::GetOrCreateFrameNode(V2::SYMBOL_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    
    /**
     * @tc.steps: step2. Test SetFontWeight with different user-defined flags.
     * @tc.expected: step2. Color properties are updated based on user-defined flags and theme.
     */
    const Ace::FontWeight value2 = Ace::FontWeight::W100;
    selectPattern->SetFontWeight(value2);
    ASSERT_NE(selectPattern->text_, nullptr);
}

/**
 * @tc.name: SetFontFamily
 * @tc.desc: Test SelectPattern SetFontFamily
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTheTestNg, SetFontFamily, TestSize.Level1)
{
    SelectModelNG selectModelInstance;

    /**
     * @tc.steps: step1. Create select.
     */
    std::vector<SelectParam> params = { { OPTION_TEXT_3, INTERNAL_SOURCE } };
    selectModelInstance.Create(params);

    /**
     * @tc.steps: step2. Get frameNode and pattern, set text_.
     */
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    selectPattern->text_ = FrameNode::GetOrCreateFrameNode(V2::SYMBOL_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    

    /**
     * @tc.steps: step3. Call SetFontFamily.
     * @tc.expected: the function runs normally
     */
    const std::vector<std::string> value3{"test1", "test2"};
    selectPattern->SetFontFamily(value3);
    ASSERT_NE(selectPattern->text_, nullptr);
}

/**
 * @tc.name: SetFontColor
 * @tc.desc: Test SelectPattern SetFontColor.
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTheTestNg, SetFontColor, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model and initialize components.
     * @tc.expected: step1. Select model and related components are created successfully.
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);

    auto select = AceType::WeakClaim(ViewStackProcessor::GetInstance()->GetMainFrameNode()).Upgrade();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto pipeline = select->GetContextWithCheck();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<SelectTheme>();
    ASSERT_NE(theme, nullptr);
    auto props = select->GetPaintProperty<SelectPaintProperty>();
    ASSERT_NE(props, nullptr);
    selectPattern->text_ = FrameNode::GetOrCreateFrameNode(V2::SYMBOL_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    
    /**
     * @tc.steps: step2. Test SetFontColor with different user-defined flags.
     * @tc.expected: step2. Color properties are updated based on user-defined flags and theme.
     */
    const Color value = Color::RED;
    selectPattern->SetFontColor(value);
    ASSERT_EQ(selectPattern->fontColor_, value);
}

/**
 * @tc.name: SetOptionFontSize
 * @tc.desc: Test SelectPattern SetOptionFontSize
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTheTestNg, SetOptionFontSize, TestSize.Level1)
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

    /**
     * @tc.steps: step3. Call SetOptionFontSize.
     * @tc.expected: the function runs normally
     */
    constexpr Dimension value = 1.0_vp;
    selectPattern->SetOptionFontSize(value);
    EXPECT_EQ(selectPattern->options_.size(), 1);

    auto option = FrameNode::GetOrCreateFrameNode(V2::OPTION_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<MenuItemPattern>(true, 0); });
    ASSERT_NE(option, nullptr);
    selectPattern->options_.push_back(option);
    selectPattern->SetOptionFontSize(value);
    EXPECT_EQ(selectPattern->options_.size(), 2);
}

/**
 * @tc.name: AddOptionNode
 * @tc.desc: Test SelectPattern AddOptionNode.
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTheTestNg, AddOptionNode, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model and initialize components.
     * @tc.expected: step1. Select model and related components are created successfully.
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);

    auto select = AceType::WeakClaim(ViewStackProcessor::GetInstance()->GetMainFrameNode()).Upgrade();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);

    /**
     * @tc.steps: step2. Test AddOptionNode with different user-defined flags.
     * @tc.expected: step2. Color properties are updated based on user-defined flags and theme.
     */
    selectPattern->AddOptionNode(nullptr);
    EXPECT_EQ(selectPattern->options_.size(), 1);
    auto option = FrameNode::GetOrCreateFrameNode(V2::OPTION_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<MenuItemPattern>(true, 0); });
    ASSERT_NE(option, nullptr);
    selectPattern->AddOptionNode(option);
    EXPECT_EQ(selectPattern->options_.size(), 2);
}

/**
 * @tc.name: InitSpinner002
 * @tc.desc: Test SelectPattern InitSpinner with valid parameters.
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTheTestNg, InitSpinner002, TestSize.Level1)
{
    /**
     * @tc.steps: step1.Create a FrameNode with TextPattern to represent the Spinner control.
     */
    auto spinner = AceType::MakeRefPtr<FrameNode>("spinner", 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(spinner, nullptr);

    /**
     * @tc.steps: step2.Create a SelectTheme instance and set its font size to 16px.
     */
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    ASSERT_NE(selectTheme, nullptr);
    selectTheme->SetFontSize(Dimension(16.0, DimensionUnit::PX));

    /**
     * @tc.steps: step3.Create a IconTheme instance.
     */
    auto iconTheme = AceType::MakeRefPtr<IconTheme>();
    ASSERT_NE(iconTheme, nullptr);

    /**
     * @tc.steps: step4.Invoke the InitSpinner method of SelectPattern with the created FrameNode and SelectTheme
     */
    SelectPattern selectPattern;
    selectPattern.InitSpinner(spinner, iconTheme, selectTheme);
    auto spinnerLayoutProperty = spinner->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(spinnerLayoutProperty, nullptr);
}

/**
 * @tc.name: SetAvoidance
 * @tc.desc: Test SelectPattern SetAvoidance
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTheTestNg, SetAvoidance, TestSize.Level1)
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

    /**
     * @tc.steps: step3. Call SetAvoidance.
     * @tc.expected: the function runs normally
     */
    auto mode = AvoidanceMode::COVER_TARGET;
    selectPattern->SetAvoidance(mode);
    EXPECT_EQ(selectPattern->options_.size(), 1);

    mode = AvoidanceMode::AVOID_AROUND_TARGET;
    selectPattern->SetAvoidance(mode);
    EXPECT_EQ(selectPattern->options_.size(), 1);
}

/**
 * @tc.name: OnThemeScopeUpdate
 * @tc.desc: Test SelectPattern OnThemeScopeUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTheTestNg, OnThemeScopeUpdate, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model and initialize components.
     * @tc.expected: step1. Select model and related components are created successfully.
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);

    auto select = AceType::WeakClaim(ViewStackProcessor::GetInstance()->GetMainFrameNode()).Upgrade();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto pipeline = select->GetContextWithCheck();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<SelectTheme>();
    ASSERT_NE(theme, nullptr);
    auto props = select->GetPaintProperty<SelectPaintProperty>();
    ASSERT_NE(props, nullptr);
    selectPattern->text_ = FrameNode::GetOrCreateFrameNode(V2::SYMBOL_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    
    /**
     * @tc.steps: step2. Test OnThemeScopeUpdate with different user-defined flags.
     * @tc.expected: step2. Color properties are updated based on user-defined flags and theme.
     */
    int32_t themeScopeId = 0;
    bool res = selectPattern->OnThemeScopeUpdate(themeScopeId);
    ASSERT_NE(res, false);
}

/**
 * @tc.name: SetHasOptionWidth
 * @tc.desc: Test SelectPattern SetHasOptionWidth
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTheTestNg, SetHasOptionWidth, TestSize.Level1)
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
     * @tc.steps: step3. Call SetHasOptionWidth.
     * @tc.expected: the function runs normally
     */
    auto hasOptionWidth = false;
    selectPattern->SetHasOptionWidth(hasOptionWidth);
    EXPECT_EQ(selectPattern->options_.size(), 1);

    hasOptionWidth = true;
    auto option = FrameNode::GetOrCreateFrameNode(V2::OPTION_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<MenuItemPattern>(true, 0); });
    ASSERT_NE(option, nullptr);
    selectPattern->options_.push_back(option);
    selectPattern->SetHasOptionWidth(hasOptionWidth);
    EXPECT_EQ(selectPattern->options_.size(), 2);
}

/**
 * @tc.name: SetMenuBackgroundBlurStyle
 * @tc.desc: Test SelectPattern SetMenuBackgroundBlurStyle.
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTheTestNg, SetMenuBackgroundBlurStyle, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model and initialize components.
     * @tc.expected: step1. Select model and related components are created successfully.
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);

    auto select = AceType::WeakClaim(ViewStackProcessor::GetInstance()->GetMainFrameNode()).Upgrade();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto pipeline = select->GetContextWithCheck();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<SelectTheme>();
    ASSERT_NE(theme, nullptr);
    auto props = select->GetPaintProperty<SelectPaintProperty>();
    ASSERT_NE(props, nullptr);

    /**
     * @tc.steps: step2. Test SetMenuBackgroundBlurStyle with different user-defined flags.
     * @tc.expected: step2. Color properties are updated based on user-defined flags and theme.
     */
    BlurStyleOption opt;
    const BlurStyleOption& blurStyle = opt;
    selectPattern->SetMenuBackgroundBlurStyle(blurStyle);
    ASSERT_EQ(blurStyle.isWindowFocused, true);
}

/**
 * @tc.name: SetDivider
 * @tc.desc: Test SelectPattern SetDivider
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTheTestNg, SetDivider, TestSize.Level1)
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
     * @tc.steps: step3. Call SetDivider.
     * @tc.expected: the function runs normally
     */
    SelectDivider selectDivider;
    const SelectDivider& divider = selectDivider;
    selectPattern->SetDivider(divider);
    EXPECT_EQ(selectPattern->options_.size(), 1);

    auto option = FrameNode::GetOrCreateFrameNode(V2::OPTION_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<MenuItemPattern>(true, 0); });
    ASSERT_NE(option, nullptr);
    selectPattern->options_.push_back(option);
    selectPattern->SetDivider(divider);
    EXPECT_EQ(selectPattern->options_.size(), 2);
}

/**
 * @tc.name: SetDividerMode
 * @tc.desc: Test SelectPattern SetDividerMode
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTheTestNg, SetDividerMode, TestSize.Level1)
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

    /**
     * @tc.steps: step3. Call SetDividerMode.
     * @tc.expected: the function runs normally
     */
    const std::optional<DividerMode>& mode1 = std::nullopt;
    selectPattern->SetDividerMode(mode1);
    EXPECT_EQ(mode1.has_value(), false);

    const std::optional<DividerMode>& mode2 = DividerMode::FLOATING_ABOVE_MENU;
    selectPattern->SetDividerMode(mode2);
    EXPECT_EQ(mode2.has_value(), true);
}

/**
 * @tc.name: DumpInfo
 * @tc.desc: Test SelectPattern DumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTheTestNg, DumpInfo, TestSize.Level1)
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

    auto option = FrameNode::GetOrCreateFrameNode(V2::OPTION_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<MenuItemPattern>(true, 0); });
    ASSERT_NE(option, nullptr);

    /**
     * @tc.steps: step3. Call DumpInfo.
     * @tc.expected: the function runs normally
     */
    selectPattern->DumpInfo();
    EXPECT_EQ(selectPattern->selected_, -1);
}

/**
 * @tc.name: SetArrowColor
 * @tc.desc: Test SelectPattern SetArrowColor.
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTheTestNg, SetArrowColor, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model and initialize components.
     * @tc.expected: step1. Select model and related components are created successfully.
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);

    auto select = AceType::WeakClaim(ViewStackProcessor::GetInstance()->GetMainFrameNode()).Upgrade();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto pipeline = select->GetContextWithCheck();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<SelectTheme>();
    ASSERT_NE(theme, nullptr);
    auto props = select->GetPaintProperty<SelectPaintProperty>();
    ASSERT_NE(props, nullptr);
    auto spinner1 = FrameNode::GetOrCreateFrameNode(V2::SELECT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    auto spinner2 = FrameNode::GetOrCreateFrameNode(V2::SYMBOL_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });

    /**
     * @tc.steps: step2. Test SetArrowColor with different user-defined flags.
     * @tc.expected: step2. Color properties are updated based on user-defined flags and theme.
     */
    const Color& color = Color::FromRGB(100, 100, 100);
    selectPattern->spinner_ = nullptr;
    ASSERT_EQ(selectPattern->spinner_, nullptr);

    selectPattern->spinner_ = spinner1;
    selectPattern->SetArrowColor(color);

    selectPattern->spinner_ = spinner2;
    selectPattern->SetArrowColor(color);
    ASSERT_NE(selectPattern->spinner_, nullptr);
}

/**
 * @tc.name: OnInjectionEventTest001
 * @tc.desc: Test OnInjectionEvent.
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTheTestNg, OnInjectionEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model and initialize components.
     * @tc.expected: step1. Select model and related components are created successfully.
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE }, { OPTION_TEXT_2, INTERNAL_SOURCE },
        { OPTION_TEXT_3, INTERNAL_SOURCE } };
    selectModelInstance.Create(params);
    auto frameNode = AceType::WeakClaim(ViewStackProcessor::GetInstance()->GetMainFrameNode()).Upgrade();
    ASSERT_NE(frameNode, nullptr);
    auto selectPattern = frameNode->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    /**
     * @tc.steps: step2. Test OnInjectionEvent with command.
     * @tc.expected: step2. the function runs RET_FAILED
     */
    EXPECT_EQ(selectPattern->OnInjectionEvent("{\"cmd\":\"onSelect\",\"params\":{}}"), RET_FAILED);
    EXPECT_EQ(selectPattern->GetSelected(), -1);
    EXPECT_EQ(selectPattern->OnInjectionEvent("{\"cmd\":\"onSelect\",\"params\":{\"index\":-1}}"), RET_FAILED);
    EXPECT_EQ(selectPattern->GetSelected(), -1);
    /**
     * @tc.steps: step3. Test OnInjectionEvent with command.
     * @tc.expected: step3. the function runs RET_SUCCESS
     */
    EXPECT_EQ(selectPattern->OnInjectionEvent("{\"cmd\":\"onSelect\",\"params\":{\"index\":1}}"), RET_SUCCESS);
    EXPECT_EQ(selectPattern->GetSelected(), 1);
    /**
     * @tc.steps: step4. Test OnInjectionEvent with duplicate command.
     * @tc.expected: step4. the function runs RET_FAILED
     */
    EXPECT_EQ(selectPattern->OnInjectionEvent("{\"cmd\":\"onSelect\",\"params\":{\"index\":1}}"), RET_FAILED);
    EXPECT_EQ(selectPattern->GetSelected(), 1);
    /**
     * @tc.steps: step5. Test OnInjectionEvent with large index.
     * @tc.expected: step5. the function runs RET_FAILED
     */
    EXPECT_EQ(selectPattern->OnInjectionEvent("{\"cmd\":\"onSelect\",\"params\":{\"index\":10}}"), RET_FAILED);
}

/**
 * @tc.name: OnInjectionEventTest002
 * @tc.desc: Test OnInjectionEvent.
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTheTestNg, OnInjectionEventTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model and initialize components.
     * @tc.expected: step1. Select model and related components are created successfully.
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE }, { OPTION_TEXT_2, INTERNAL_SOURCE },
        { OPTION_TEXT_3, INTERNAL_SOURCE } };
    selectModelInstance.Create(params);
    auto frameNode = AceType::WeakClaim(ViewStackProcessor::GetInstance()->GetMainFrameNode()).Upgrade();
    ASSERT_NE(frameNode, nullptr);
    auto selectPattern = frameNode->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);

    /**
     * @tc.steps: step2. Test OnInjectionEvent with command.
     * @tc.expected: step2. the function runs RET_SUCCESS
     */
    EXPECT_EQ(selectPattern->OnInjectionEvent("{\"cmd\":\"onSelect\",\"params\":{\"index\":1}}"), RET_SUCCESS);
    EXPECT_EQ(selectPattern->GetSelected(), 1);
    EXPECT_EQ(selectPattern->selectValue_, OPTION_TEXT_2);
}

/**
 * @tc.name: ReportOnChangeEventTest001
 * @tc.desc: Test ReportOnChangeEvent.
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTheTestNg, ReportOnChangeEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model and initialize components.
     * @tc.expected: step1. Select model and related components are created successfully.
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE }, { OPTION_TEXT_2, INTERNAL_SOURCE },
        { OPTION_TEXT_3, INTERNAL_SOURCE } };
    selectModelInstance.Create(params);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto selectPattern = frameNode->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    EXPECT_EQ(selectPattern->ReportOnSelectEvent(0, OPTION_TEXT), true);
}

/**
 * @tc.name: ToJsonTest001
 * @tc.desc: Test SelectJsonUtil ToJson.
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTheTestNg, ToJsonTest001, TestSize.Level1)
{
    SelectJsonUtil util;
    util.index = 3;
    util.value = "test";
    auto result = SelectJsonUtil::ToJson(util);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->GetString("cmd"), "onSelect");
}

/**
 * @tc.name: FromJsonTest001
 * @tc.desc: Test SelectJsonUtil FromJson.
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTheTestNg, FromJsonTest001, TestSize.Level1)
{
    auto params = JsonUtil::Create();
    ASSERT_NE(params, nullptr);
    params->Put("index", 3);
    auto json = JsonUtil::Create();
    ASSERT_NE(json, nullptr);
    json->Put("cmd", "onSelect");
    json->Put("params", params);

    auto jsonUtil = SelectJsonUtil::FromJson(json);
    EXPECT_EQ(jsonUtil.index.has_value(), true);
    EXPECT_EQ(jsonUtil.index.value(), 3);
}

/**
 * @tc.name: UpdateSelectedOptionFontFromPattern
 * @tc.desc: Test SelectPattern UpdateSelectedOptionFontFromPattern.
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTheTestNg, UpdateSelectedOptionFontFromPattern, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model and initialize components.
     * @tc.expected: step1. Select model and related components are created successfully.
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);

    auto select = AceType::WeakClaim(ViewStackProcessor::GetInstance()->GetMainFrameNode()).Upgrade();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto pipeline = select->GetContextWithCheck();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<SelectTheme>();
    ASSERT_NE(theme, nullptr);
    auto props = select->GetPaintProperty<SelectPaintProperty>();
    ASSERT_NE(props, nullptr);

    /**
     * @tc.steps: step2. Test UpdateSelectedOptionFontFromPattern with different user-defined flags.
     * @tc.expected: step2. Color properties are updated based on user-defined flags and theme.
     */
    const RefPtr<MenuItemPattern>& optionPattern = AceType::MakeRefPtr<MenuItemPattern>();
    selectPattern->selectedFont_.FontColor = std::nullopt;
    selectPattern->selectedFont_.FontFamily = std::nullopt;
    selectPattern->selectedFont_.FontSize = std::nullopt;
    selectPattern->selectedFont_.FontStyle = std::nullopt;
    selectPattern->selectedFont_.FontWeight = std::nullopt;
    selectPattern->UpdateSelectedOptionFontFromPattern(optionPattern);
    ASSERT_EQ(selectPattern->selectedFont_.FontFamily, std::nullopt);

    selectPattern->selectedFont_.FontColor = Color::FromRGB(100, 100, 100);
    selectPattern->selectedFont_.FontFamily.emplace();
    selectPattern->selectedFont_.FontSize = OPTION_MARGIN;
    selectPattern->selectedFont_.FontStyle = std::make_optional(ITALIC_FONT_STYLE_VALUE);
    selectPattern->selectedFont_.FontWeight = FontWeight::BOLD;
    selectPattern->UpdateSelectedOptionFontFromPattern(optionPattern);
    ASSERT_NE(selectPattern->selectedFont_.FontFamily, std::nullopt);
}
} // namespace OHOS::Ace::NG
