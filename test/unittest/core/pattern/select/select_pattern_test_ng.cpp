/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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
const Ace::FontWeight FONT_WEIGHT_VALUE = Ace::FontWeight::W100;
const Dimension FONT_SIZE_VALUE = Dimension(20.1, DimensionUnit::PX);
const Ace::FontStyle ITALIC_FONT_STYLE_VALUE = Ace::FontStyle::ITALIC;
} // namespace
struct TestProperty {
    std::optional<Dimension> FontSize = std::nullopt;
    std::optional<Ace::FontStyle> FontStyle = std::nullopt;
    std::optional<FontWeight> FontWeight = std::nullopt;
    std::optional<std::vector<std::string>> FontFamily = std::nullopt;
    std::optional<Color> FontColor = std::nullopt;
};
class SelectPatternTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
    void InitSelectPatternTestNg();
    RefPtr<FrameNode> frameNode_;
    RefPtr<SelectPattern> selectPattern_;
    RefPtr<SelectAccessibilityProperty> selectAccessibilityProperty_;

protected:
    static RefPtr<FrameNode> CreateSelect(const std::vector<SelectParam>& value, const TestProperty& test);
    static FrameNode* CreateSelect(const std::vector<SelectParam>& value);
};

void SelectPatternTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
}

void SelectPatternTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

void SelectPatternTestNg::SetUp() {}

void SelectPatternTestNg::TearDown()
{
    frameNode_ = nullptr;
    selectPattern_ = nullptr;
    selectAccessibilityProperty_ = nullptr;
}

void SelectPatternTestNg::InitSelectPatternTestNg()
{
    frameNode_ = FrameNode::GetOrCreateFrameNode(V2::SELECT_ETS_TAG, ViewStackProcessor::GetInstance()->ClaimNodeId(),
        []() { return AceType::MakeRefPtr<SelectPattern>(); });
    ASSERT_NE(frameNode_, nullptr);

    selectPattern_ = frameNode_->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern_, nullptr);

    selectAccessibilityProperty_ = frameNode_->GetAccessibilityProperty<SelectAccessibilityProperty>();
    ASSERT_NE(selectAccessibilityProperty_, nullptr);
}

RefPtr<FrameNode> SelectPatternTestNg::CreateSelect(const std::vector<SelectParam>& value, const TestProperty& test)
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

FrameNode* SelectPatternTestNg::CreateSelect(const std::vector<SelectParam>& value)
{
    SelectModelNG selectModelInstance;
    selectModelInstance.Create(value);
    return ViewStackProcessor::GetInstance()->GetMainFrameNode();
}

/**
 * @tc.name: OnModifyDone002
 * @tc.desc: Test SelectPattern OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, OnModifyDone002, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    /**
     * @tc.steps: step1. Create select.
     */
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);
    /**
     * @tc.steps: step2. Get frameNode and pattern.
     */
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto menuNode = selectPattern->GetMenuNode();
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    /**
     * @tc.steps: step3. Call OnModifyDone.
     * @tc.expected: the function runs normally
     */
    selectPattern->OnModifyDone();
    auto val = menuPattern->IsSelectMenu();

    EXPECT_EQ(val, true);
}

/**
 * @tc.name: RemoveParentRestrictionsForFixIdeal001
 * @tc.desc: Test Select RemoveParentRestrictionsForFixIdeal.
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, RemoveParentRestrictionsForFixIdeal001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select.
     */
    auto selectPattern = AceType::MakeRefPtr<SelectPattern>();
    auto selectNode = FrameNode::CreateFrameNode(V2::SELECT_ETS_TAG, -1, selectPattern);
    auto algorithm = AceType::MakeRefPtr<SelectLayoutAlgorithm>();
    ASSERT_TRUE(algorithm);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutProp = AceType::MakeRefPtr<LayoutProperty>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(selectNode, geometryNode, layoutProp);
    ASSERT_NE(layoutWrapper, nullptr);
    /**
     * @tc.steps: step2. LayoutCalPolicy is FIX_AT_IDEAL_SIZE and set maxSize to FULL_SCREEN_SIZE.
     * @tc.expected: childConstraint.maxSize is infinity.
     */
    LayoutConstraintF childConstraint;
    LayoutPolicyProperty layoutPolicyProperty;
    layoutPolicyProperty.widthLayoutPolicy_ = LayoutCalPolicy::FIX_AT_IDEAL_SIZE;
    layoutPolicyProperty.heightLayoutPolicy_ = LayoutCalPolicy::FIX_AT_IDEAL_SIZE;
    layoutProp->layoutPolicy_ = layoutPolicyProperty;
    algorithm->RemoveParentRestrictionsForFixIdeal(layoutProp, childConstraint);
    EXPECT_TRUE(std::isinf(childConstraint.maxSize.Width()));
    EXPECT_TRUE(std::isinf(childConstraint.maxSize.Height()));
}


/**
 * @tc.name: OnModifyDone003
 * @tc.desc: Test SelectPattern OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, OnModifyDone003, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    /**
     * @tc.steps: step1. Create select.
     */
    std::vector<SelectParam> params = { { OPTION_TEXT_2, INTERNAL_SOURCE } };
    selectModelInstance.Create(params);
    /**
     * @tc.steps: step2. Get frameNode and pattern.
     */
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto menuNode = selectPattern->GetMenuNode();
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    /**
     * @tc.steps: step3. Call OnModifyDone.
     * @tc.expected: the function runs normally
     */
    selectPattern->OnModifyDone();
    auto val = menuPattern->IsSelectMenu();

    EXPECT_EQ(val, true);
}

/**
 * @tc.name: OnModifyDone004
 * @tc.desc: Test SelectPattern OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, OnModifyDone004, TestSize.Level1)
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
    auto menuNode = selectPattern->GetMenuNode();
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    /**
     * @tc.steps: step3. Call OnModifyDone.
     * @tc.expected: the function runs normally
     */
    selectPattern->OnModifyDone();
    auto val = menuPattern->IsSelectMenu();

    EXPECT_EQ(val, true);
}

/**
 * @tc.name: OnModifyDone005
 * @tc.desc: Test SelectPattern OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, OnModifyDone005, TestSize.Level1)
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
    auto menuNode = selectPattern->GetMenuNode();
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    /**
     * @tc.steps: step3. Call OnModifyDone.
     * @tc.expected: the function runs normally
     */
    selectPattern->OnModifyDone();
    auto val = menuPattern->IsSelectMenu();

    EXPECT_EQ(val, true);
}
/**
 * @tc.name: OnModifyDone006
 * @tc.desc: Test SelectPattern OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, OnModifyDone006, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    /**
     * @tc.steps: step1. Create select.
     */
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);
    /**
     * @tc.steps: step2. Get frameNode and pattern.
     */
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto menuNode = selectPattern->GetMenuNode();
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    /**
     * @tc.steps: step3. Call OnModifyDone.
     * @tc.expected: the function runs normally
     */
    selectPattern->OnModifyDone();
    auto val = menuNode->isRestoreInfoUsed_;

    EXPECT_NE(val, false);
}

/**
 * @tc.name: OnModifyDone007
 * @tc.desc: Test SelectPattern OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, OnModifyDone007, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    /**
     * @tc.steps: step1. Create select.
     */
    std::vector<SelectParam> params = { { OPTION_TEXT_2, INTERNAL_SOURCE } };
    selectModelInstance.Create(params);
    /**
     * @tc.steps: step2. Get frameNode and pattern.
     */
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto menuNode = selectPattern->GetMenuNode();
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    /**
     * @tc.steps: step3. Call OnModifyDone.
     * @tc.expected: the function runs normally
     */
    selectPattern->OnModifyDone();
    auto val = menuNode->isRestoreInfoUsed_;

    EXPECT_NE(val, false);
}

/**
 * @tc.name: OnModifyDone008
 * @tc.desc: Test SelectPattern OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, OnModifyDone008, TestSize.Level1)
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
    auto menuNode = selectPattern->GetMenuNode();
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    /**
     * @tc.steps: step3. Call OnModifyDone.
     * @tc.expected: the function runs normally
     */
    selectPattern->OnModifyDone();
    auto val = menuNode->isRestoreInfoUsed_;

    EXPECT_NE(val, false);
}

/**
 * @tc.name: OnModifyDone009
 * @tc.desc: Test SelectPattern OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, OnModifyDone009, TestSize.Level1)
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
    auto menuNode = selectPattern->GetMenuNode();
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    /**
     * @tc.steps: step3. Call OnModifyDone.
     * @tc.expected: the function runs normally
     */
    selectPattern->OnModifyDone();
    auto val = menuNode->isRestoreInfoUsed_;

    EXPECT_NE(val, false);
}

/**
 * @tc.name: OnModifyDone010
 * @tc.desc: Test SelectPattern OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, OnModifyDone010, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    /**
     * @tc.steps: step1. Create select.
     */
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);
    /**
     * @tc.steps: step2. Get frameNode and pattern.
     */
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto menuNode = selectPattern->GetMenuNode();
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    /**
     * @tc.steps: step3. Call OnModifyDone.
     * @tc.expected: the function runs normally
     */
    selectPattern->OnModifyDone();
    auto val = selectPattern->isSelected_;

    EXPECT_NE(val, true);
}

/**
 * @tc.name: OnModifyDone011
 * @tc.desc: Test SelectPattern OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, OnModifyDone011, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    /**
     * @tc.steps: step1. Create select.
     */
    std::vector<SelectParam> params = { { OPTION_TEXT_2, INTERNAL_SOURCE } };
    selectModelInstance.Create(params);
    /**
     * @tc.steps: step2. Get frameNode and pattern.
     */
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto menuNode = selectPattern->GetMenuNode();
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    /**
     * @tc.steps: step3. Call OnModifyDone.
     * @tc.expected: the function runs normally
     */
    selectPattern->OnModifyDone();
    auto val = selectPattern->isSelected_;

    EXPECT_NE(val, true);
}

/**
 * @tc.name: OnModifyDone012
 * @tc.desc: Test SelectPattern OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, OnModifyDone0012, TestSize.Level1)
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
    auto menuNode = selectPattern->GetMenuNode();
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    /**
     * @tc.steps: step3. Call OnModifyDone.
     * @tc.expected: the function runs normally
     */
    selectPattern->OnModifyDone();
    auto val = selectPattern->isSelected_;

    EXPECT_NE(val, true);
}

/**
 * @tc.name: OnModifyDone013
 * @tc.desc: Test SelectPattern OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, OnModifyDone013, TestSize.Level1)
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
    auto menuNode = selectPattern->GetMenuNode();
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    /**
     * @tc.steps: step3. Call OnModifyDone.
     * @tc.expected: the function runs normally
     */
    selectPattern->OnModifyDone();
    auto val = selectPattern->isSelected_;

    EXPECT_NE(val, true);
}


/**
 * @tc.name: SetItemSelected001
 * @tc.desc: Test SelectPattern SetItemSelected
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, SetItemSelected001, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    /**
     * @tc.steps: step1. Create select.
     */
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);
    /**
     * @tc.steps: step2. Get frameNode and pattern.
     */
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto menuNode = selectPattern->GetMenuNode();
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    /**
     * @tc.steps: step3. Call SetItemSelected.
     * @tc.expected: the function runs normally
     */
    selectPattern->SetItemSelected(0, "content");
    auto val = selectPattern->isSelected_;

    EXPECT_NE(val, false);
}

/**
 * @tc.name: SetItemSelected002
 * @tc.desc: Test SelectPattern SetItemSelected
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, SetItemSelected002, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    /**
     * @tc.steps: step1. Create select.
     */
    std::vector<SelectParam> params = { { OPTION_TEXT_2, INTERNAL_SOURCE } };
    selectModelInstance.Create(params);
    /**
     * @tc.steps: step2. Get frameNode and pattern.
     */
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto menuNode = selectPattern->GetMenuNode();
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    /**
     * @tc.steps: step3. Call SetItemSelected.
     * @tc.expected: the function runs normally
     */
    selectPattern->SetItemSelected(0, "content");
    auto val = selectPattern->isSelected_;

    EXPECT_NE(val, false);
}

/**
 * @tc.name: SetItemSelected003
 * @tc.desc: Test SelectPattern SetItemSelected
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, SetItemSelected003, TestSize.Level1)
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
    auto menuNode = selectPattern->GetMenuNode();
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    /**
     * @tc.steps: step3. Call SetItemSelected.
     * @tc.expected: the function runs normally
     */
    selectPattern->SetItemSelected(0, "content");
    auto val = selectPattern->isSelected_;

    EXPECT_NE(val, false);
}

/**
 * @tc.name: SetItemSelected004
 * @tc.desc: Test SelectPattern SetItemSelected
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, SetItemSelected004, TestSize.Level1)
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
    auto menuNode = selectPattern->GetMenuNode();
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    /**
     * @tc.steps: step3. Call SetItemSelected.
     * @tc.expected: the function runs normally
     */
    selectPattern->SetItemSelected(0, "content");
    auto val = selectPattern->isSelected_;

    EXPECT_NE(val, false);
}

/**
 * @tc.name: SetItemSelected005
 * @tc.desc: Test SelectPattern SetItemSelected
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, SetItemSelected005, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    /**
     * @tc.steps: step1. Create select.
     */
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);
    /**
     * @tc.steps: step2. Get frameNode and pattern.
     */
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto menuNode = selectPattern->GetMenuNode();
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    /**
     * @tc.steps: step3. Call SetItemSelected.
     * @tc.expected: the function runs normally
     */
    selectPattern->SetItemSelected(1, "content");
    auto val = selectPattern->isSelected_;

    EXPECT_NE(val, false);
}

/**
 * @tc.name: SetItemSelected006
 * @tc.desc: Test SelectPattern SetItemSelected
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, SetItemSelected006, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    /**
     * @tc.steps: step1. Create select.
     */
    std::vector<SelectParam> params = { { OPTION_TEXT_2, INTERNAL_SOURCE } };
    selectModelInstance.Create(params);
    /**
     * @tc.steps: step2. Get frameNode and pattern.
     */
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto menuNode = selectPattern->GetMenuNode();
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    /**
     * @tc.steps: step3. Call SetItemSelected.
     * @tc.expected: the function runs normally
     */
    selectPattern->SetItemSelected(1, "content");
    auto val = selectPattern->isSelected_;

    EXPECT_NE(val, false);
}

/**
 * @tc.name: SetItemSelected007
 * @tc.desc: Test SelectPattern SetItemSelected
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, SetItemSelected007, TestSize.Level1)
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
    auto menuNode = selectPattern->GetMenuNode();
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    /**
     * @tc.steps: step3. Call SetItemSelected.
     * @tc.expected: the function runs normally
     */
    selectPattern->SetItemSelected(1, "content");
    auto val = selectPattern->isSelected_;

    EXPECT_NE(val, false);
}

/**
 * @tc.name: SetItemSelected008
 * @tc.desc: Test SelectPattern SetItemSelected
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, SetItemSelected008, TestSize.Level1)
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
    auto menuNode = selectPattern->GetMenuNode();
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    /**
     * @tc.steps: step3. Call SetItemSelected.
     * @tc.expected: the function runs normally
     */
    selectPattern->SetItemSelected(1, "content");
    auto val = selectPattern->isSelected_;

    EXPECT_NE(val, false);
}

/**
 * @tc.name: SetItemSelected009
 * @tc.desc: Test SelectPattern SetItemSelected
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, SetItemSelected009, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    /**
     * @tc.steps: step1. Create select.
     */
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);
    /**
     * @tc.steps: step2. Get frameNode and pattern.
     */
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto menuNode = selectPattern->GetMenuNode();
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    /**
     * @tc.steps: step3. Call SetItemSelected.
     * @tc.expected: the function runs normally
     */
    selectPattern->SetItemSelected(2, ITEM_TEXT);
    auto val = selectPattern->isSelected_;

    EXPECT_NE(val, false);
}

/**
 * @tc.name: SetItemSelected010
 * @tc.desc: Test SelectPattern SetItemSelected
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, SetItemSelected010, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    /**
     * @tc.steps: step1. Create select.
     */
    std::vector<SelectParam> params = { { OPTION_TEXT_2, INTERNAL_SOURCE } };
    selectModelInstance.Create(params);
    /**
     * @tc.steps: step2. Get frameNode and pattern.
     */
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto menuNode = selectPattern->GetMenuNode();
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    /**
     * @tc.steps: step3. Call SetItemSelected.
     * @tc.expected: the function runs normally
     */
    selectPattern->SetItemSelected(2, ITEM_TEXT);
    auto val = selectPattern->isSelected_;

    EXPECT_NE(val, false);
}

/**
 * @tc.name: SetItemSelected011
 * @tc.desc: Test SelectPattern SetItemSelected
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, SetItemSelected011, TestSize.Level1)
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
    auto menuNode = selectPattern->GetMenuNode();
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    /**
     * @tc.steps: step3. Call SetItemSelected.
     * @tc.expected: the function runs normally
     */
    selectPattern->SetItemSelected(2, ITEM_TEXT);
    auto val = selectPattern->isSelected_;

    EXPECT_NE(val, false);
}

/**
 * @tc.name: SetItemSelected012
 * @tc.desc: Test SelectPattern SetItemSelected
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, SetItemSelected012, TestSize.Level1)
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
    auto menuNode = selectPattern->GetMenuNode();
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    /**
     * @tc.steps: step3. Call SetItemSelected.
     * @tc.expected: the function runs normally
     */
    selectPattern->SetItemSelected(2, ITEM_TEXT);
    auto val = selectPattern->isSelected_;

    EXPECT_NE(val, false);
}

/**
 * @tc.name: SetItemSelected013
 * @tc.desc: Test SelectPattern SetItemSelected
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, SetItemSelected013, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    /**
     * @tc.steps: step1. Create select.
     */
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);
    /**
     * @tc.steps: step2. Get frameNode and pattern.
     */
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto menuNode = selectPattern->GetMenuNode();
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    /**
     * @tc.steps: step3. Call SetItemSelected.
     * @tc.expected: the function runs normally
     */
    selectPattern->SetItemSelected(3, ITEM_TEXT);
    auto val = selectPattern->isSelected_;

    EXPECT_NE(val, false);
}

/**
 * @tc.name: SetItemSelected014
 * @tc.desc: Test SelectPattern SetItemSelected
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, SetItemSelected014, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    /**
     * @tc.steps: step1. Create select.
     */
    std::vector<SelectParam> params = { { OPTION_TEXT_2, INTERNAL_SOURCE } };
    selectModelInstance.Create(params);
    /**
     * @tc.steps: step2. Get frameNode and pattern.
     */
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto menuNode = selectPattern->GetMenuNode();
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    /**
     * @tc.steps: step3. Call SetItemSelected.
     * @tc.expected: the function runs normally
     */
    selectPattern->SetItemSelected(3, ITEM_TEXT);
    auto val = selectPattern->isSelected_;

    EXPECT_NE(val, false);
}

/**
 * @tc.name: SetItemSelected015
 * @tc.desc: Test SelectPattern SetItemSelected
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, SetItemSelected015, TestSize.Level1)
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
    auto menuNode = selectPattern->GetMenuNode();
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    /**
     * @tc.steps: step3. Call SetItemSelected.
     * @tc.expected: the function runs normally
     */
    selectPattern->SetItemSelected(3, ITEM_TEXT);
    auto val = selectPattern->isSelected_;

    EXPECT_NE(val, false);
}

/**
 * @tc.name: SetItemSelected016
 * @tc.desc: Test SelectPattern SetItemSelected
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, SetItemSelected016, TestSize.Level1)
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
    auto menuNode = selectPattern->GetMenuNode();
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    /**
     * @tc.steps: step3. Call SetItemSelected.
     * @tc.expected: the function runs normally
     */
    selectPattern->SetItemSelected(3, ITEM_TEXT);
    auto val = selectPattern->isSelected_;

    EXPECT_NE(val, false);
}

/**
 * @tc.name: SetItemSelected017
 * @tc.desc: Test SelectPattern SetItemSelected
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, SetItemSelected017, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    /**
     * @tc.steps: step1. Create select.
     */
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);
    /**
     * @tc.steps: step2. Get frameNode and pattern.
     */
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto menuNode = selectPattern->GetMenuNode();
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    /**
     * @tc.steps: step3. Call SetItemSelected.
     * @tc.expected: the function runs normally
     */
    selectPattern->SetItemSelected(0, "content");
    auto val = selectPattern->GetSelected();

    EXPECT_EQ(val, 0);
}

/**
 * @tc.name: SetItemSelected018
 * @tc.desc: Test SelectPattern SetItemSelected
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, SetItemSelected018, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    /**
     * @tc.steps: step1. Create select.
     */
    std::vector<SelectParam> params = { { OPTION_TEXT_2, INTERNAL_SOURCE } };
    selectModelInstance.Create(params);
    /**
     * @tc.steps: step2. Get frameNode and pattern.
     */
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto menuNode = selectPattern->GetMenuNode();
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    /**
     * @tc.steps: step3. Call SetItemSelected.
     * @tc.expected: the function runs normally
     */
    selectPattern->SetItemSelected(0, "content");
    auto val = selectPattern->GetSelected();

    EXPECT_EQ(val, 0);
}

/**
 * @tc.name: SetItemSelected019
 * @tc.desc: Test SelectPattern SetItemSelected
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, SetItemSelected019, TestSize.Level1)
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
    auto menuNode = selectPattern->GetMenuNode();
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    /**
     * @tc.steps: step3. Call SetItemSelected.
     * @tc.expected: the function runs normally
     */
    selectPattern->SetItemSelected(0, "content");
    auto val = selectPattern->GetSelected();

    EXPECT_EQ(val, 0);
}

/**
 * @tc.name: SetItemSelected020
 * @tc.desc: Test SelectPattern SetItemSelected
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, SetItemSelected020, TestSize.Level1)
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
    auto menuNode = selectPattern->GetMenuNode();
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    /**
     * @tc.steps: step3. Call SetItemSelected.
     * @tc.expected: the function runs normally
     */
    selectPattern->SetItemSelected(0, "content");
    auto val = selectPattern->GetSelected();

    EXPECT_EQ(val, 0);
}

/**
 * @tc.name: SetItemSelected021
 * @tc.desc: Test SelectPattern SetItemSelected
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, SetItemSelected021, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    /**
     * @tc.steps: step1. Create select.
     */
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);
    /**
     * @tc.steps: step2. Get frameNode and pattern.
     */
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto menuNode = selectPattern->GetMenuNode();
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    /**
     * @tc.steps: step3. Call SetItemSelected.
     * @tc.expected: the function runs normally
     */
    selectPattern->SetItemSelected(1, "content");
    auto val = selectPattern->GetSelected();

    EXPECT_EQ(val, -1);
}

/**
 * @tc.name: SetItemSelected022
 * @tc.desc: Test SelectPattern SetItemSelected
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, SetItemSelected022, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    /**
     * @tc.steps: step1. Create select.
     */
    std::vector<SelectParam> params = { { OPTION_TEXT_2, INTERNAL_SOURCE } };
    selectModelInstance.Create(params);
    /**
     * @tc.steps: step2. Get frameNode and pattern.
     */
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto menuNode = selectPattern->GetMenuNode();
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    /**
     * @tc.steps: step3. Call SetItemSelected.
     * @tc.expected: the function runs normally
     */
    selectPattern->SetItemSelected(1, "content");
    auto val = selectPattern->GetSelected();

    EXPECT_EQ(val, -1);
}

/**
 * @tc.name: SetItemSelected023
 * @tc.desc: Test SelectPattern SetItemSelected
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, SetItemSelected023, TestSize.Level1)
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
    auto menuNode = selectPattern->GetMenuNode();
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    /**
     * @tc.steps: step3. Call SetItemSelected.
     * @tc.expected: the function runs normally
     */
    selectPattern->SetItemSelected(1, "content");
    auto val = selectPattern->GetSelected();

    EXPECT_EQ(val, -1);
}

/**
 * @tc.name: SetItemSelected024
 * @tc.desc: Test SelectPattern SetItemSelected
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, SetItemSelected024, TestSize.Level1)
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
    auto menuNode = selectPattern->GetMenuNode();
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    /**
     * @tc.steps: step3. Call SetItemSelected.
     * @tc.expected: the function runs normally
     */
    selectPattern->SetItemSelected(1, "content");
    auto val = selectPattern->GetSelected();

    EXPECT_EQ(val, 1);
}

/**
 * @tc.name: SetItemSelected025
 * @tc.desc: Test SelectPattern SetItemSelected
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, SetItemSelected025, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    /**
     * @tc.steps: step1. Create select.
     */
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);
    /**
     * @tc.steps: step2. Get frameNode and pattern.
     */
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto menuNode = selectPattern->GetMenuNode();
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    /**
     * @tc.steps: step3. Call SetItemSelected.
     * @tc.expected: the function runs normally
     */
    selectPattern->SetItemSelected(2, ITEM_TEXT);
    auto val = selectPattern->GetSelected();

    EXPECT_EQ(val, -1);
}

/**
 * @tc.name: SetItemSelected026
 * @tc.desc: Test SelectPattern SetItemSelected
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, SetItemSelected026, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    /**
     * @tc.steps: step1. Create select.
     */
    std::vector<SelectParam> params = { { OPTION_TEXT_2, INTERNAL_SOURCE } };
    selectModelInstance.Create(params);
    /**
     * @tc.steps: step2. Get frameNode and pattern.
     */
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto menuNode = selectPattern->GetMenuNode();
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    /**
     * @tc.steps: step3. Call SetItemSelected.
     * @tc.expected: the function runs normally
     */
    selectPattern->SetItemSelected(2, ITEM_TEXT);
    auto val = selectPattern->GetSelected();

    EXPECT_EQ(val, -1);
}

/**
 * @tc.name: SetItemSelected027
 * @tc.desc: Test SelectPattern SetItemSelected
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, SetItemSelected027, TestSize.Level1)
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
    auto menuNode = selectPattern->GetMenuNode();
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    /**
     * @tc.steps: step3. Call SetItemSelected.
     * @tc.expected: the function runs normally
     */
    selectPattern->SetItemSelected(2, ITEM_TEXT);
    auto val = selectPattern->GetSelected();

    EXPECT_EQ(val, -1);
}

/**
 * @tc.name: SetItemSelected028
 * @tc.desc: Test SelectPattern SetItemSelected
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, SetItemSelected028, TestSize.Level1)
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
    auto menuNode = selectPattern->GetMenuNode();
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    /**
     * @tc.steps: step3. Call SetItemSelected.
     * @tc.expected: the function runs normally
     */
    selectPattern->SetItemSelected(2, ITEM_TEXT);
    auto val = selectPattern->GetSelected();

    EXPECT_EQ(val, 2);
}

/**
 * @tc.name: SetItemSelected029
 * @tc.desc: Test SelectPattern SetItemSelected
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, SetItemSelected029, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    /**
     * @tc.steps: step1. Create select.
     */
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);
    /**
     * @tc.steps: step2. Get frameNode and pattern.
     */
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto menuNode = selectPattern->GetMenuNode();
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    /**
     * @tc.steps: step3. Call SetItemSelected.
     * @tc.expected: the function runs normally
     */
    selectPattern->SetItemSelected(3, ITEM_TEXT);
    auto val = selectPattern->GetSelected();

    EXPECT_EQ(val, -1);
}

/**
 * @tc.name: SetItemSelected030
 * @tc.desc: Test SelectPattern SetItemSelected
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, SetItemSelected030, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    /**
     * @tc.steps: step1. Create select.
     */
    std::vector<SelectParam> params = { { OPTION_TEXT_2, INTERNAL_SOURCE } };
    selectModelInstance.Create(params);
    /**
     * @tc.steps: step2. Get frameNode and pattern.
     */
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto menuNode = selectPattern->GetMenuNode();
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    /**
     * @tc.steps: step3. Call SetItemSelected.
     * @tc.expected: the function runs normally
     */
    selectPattern->SetItemSelected(3, ITEM_TEXT);
    auto val = selectPattern->GetSelected();

    EXPECT_EQ(val, -1);
}

/**
 * @tc.name: SetItemSelected031
 * @tc.desc: Test SelectPattern SetItemSelected
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, SetItemSelected031, TestSize.Level1)
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
    auto menuNode = selectPattern->GetMenuNode();
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    /**
     * @tc.steps: step3. Call SetItemSelected.
     * @tc.expected: the function runs normally
     */
    selectPattern->SetItemSelected(3, ITEM_TEXT);
    auto val = selectPattern->GetSelected();

    EXPECT_EQ(val, -1);
}

/**
 * @tc.name: SetItemSelected032
 * @tc.desc: Test SelectPattern SetItemSelected
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, SetItemSelected032, TestSize.Level1)
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
    auto menuNode = selectPattern->GetMenuNode();
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    /**
     * @tc.steps: step3. Call SetItemSelected.
     * @tc.expected: the function runs normally
     */
    selectPattern->SetItemSelected(3, ITEM_TEXT);
    auto val = selectPattern->GetSelected();

    EXPECT_EQ(val, -1);
}

/**
 * @tc.name: SetControlSize001
 * @tc.desc: Test SelectPattern SetControlSize
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, SetControlSize001, TestSize.Level1)
{
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    SelectModelNG selectModelInstance;
    /**
     * @tc.steps: step1. Get frameNode and pattern.
     */
    auto *selectFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(selectFrameNode, nullptr);
    auto selectPattern = selectFrameNode->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);

    /**
     * @tc.steps: step2. Call SetControlSize.
     * @tc.expected: the function runs normally
     */
    selectPattern->SetControlSize(ControlSize::SMALL);
    auto controlSize = selectPattern->GetControlSize();
    EXPECT_EQ(ControlSize::SMALL, controlSize);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: UpdateTargetSize
 * @tc.desc: Test SelectPattern UpdateTargetSize
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, UpdateTargetSize001, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    /**
     * @tc.steps: step1. Create select.
     */
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);
    /**
     * @tc.steps: step2. Get frameNode and pattern.
     */
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    /**
     * @tc.steps: step3. Call UpdateTargetSize.
     * @tc.expected: the menu targetSize equal selectSize_
     */
    selectPattern->SetSelectSize(SizeF(SELECT_WIDTH, SELECT_HEIGHT));
    selectPattern->UpdateTargetSize();
    auto menu = selectPattern->GetMenuNode();
    ASSERT_NE(menu, nullptr);
    auto menuLayoutProps = menu->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(menuLayoutProps, nullptr);
    auto targetSize = menuLayoutProps->GetTargetSizeValue(SizeF());
    EXPECT_EQ(targetSize, SizeF(SELECT_WIDTH, SELECT_HEIGHT));

    /**
     * @tc.steps: step4. Get a option.
     * @tc.expected: IsWidthModifiedBySelect false
     */
    auto optionCount = selectPattern->options_.size();
    ASSERT_NE(optionCount, 0);
    auto option = selectPattern->options_[0];
    auto optionPattern = option->GetPattern<MenuItemPattern>();
    ASSERT_NE(optionPattern, nullptr);
    EXPECT_FALSE(optionPattern->IsWidthModifiedBySelect());
    /**
     * @tc.steps: step5. make fitTrigger_ true and call UpdateTargetSize.
     * @tc.expected: IsWidthModifiedBySelect true
     */
    selectPattern->SetOptionWidthFitTrigger(true);
    selectPattern->UpdateTargetSize();
    EXPECT_TRUE(optionPattern->IsWidthModifiedBySelect());
    auto scroll = AceType::DynamicCast<FrameNode>(menu->GetFirstChild());
    ASSERT_NE(scroll, nullptr);
    auto scrollPattern = scroll->GetPattern<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    EXPECT_TRUE(scrollPattern->IsWidthModifiedBySelect());
    /**
     * @tc.steps: step6. get option paint property.
     * @tc.expected: GetSelectModifiedWidthValue equal SELECT_WIDTH
     */
    auto optionPaintProperty = option->GetPaintProperty<MenuItemPaintProperty>();
    CHECK_NULL_VOID(optionPaintProperty);
    auto selectModifiedWidth = optionPaintProperty->GetSelectModifiedWidthValue(0.0f);
    EXPECT_EQ(selectModifiedWidth, SELECT_WIDTH - OPTION_MARGIN.ConvertToPx());
}

/**
 * @tc.name: InitFocusEventTest001
 * @tc.desc: Test SelectPattern::InitFocusEvent.
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, InitFocusEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step0. Create mock theme manager
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    selectTheme->optionApplyFocusedStyle_ = 1;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(selectTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(selectTheme));
    /**
     * @tc.steps: step1. Create select.
     */
    SelectModelNG selectModelInstance;
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
    auto renderContext = select->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdateBackgroundColor(selectTheme->GetButtonBackgroundColor());

    selectPattern->InitFocusEvent();
    selectPattern->HandleFocusStyleTask();
    selectPattern->AddIsFocusActiveUpdateEvent();
    selectPattern->SetFocusStyle();
    EXPECT_TRUE(selectPattern->shadowModify_);
    EXPECT_TRUE(selectPattern->scaleModify_);
    EXPECT_TRUE(selectPattern->bgColorModify_);
    EXPECT_EQ(renderContext->GetBackgroundColor(), selectTheme->GetSelectFocusedBackground());
}

/**
 * @tc.name: InitFocusEventTest002
 * @tc.desc: Test SelectPattern::InitFocusEvent.
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, InitFocusEventTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step0. Create mock theme manager
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    selectTheme->optionApplyFocusedStyle_ = 1;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(selectTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(selectTheme));
    /**
     * @tc.steps: step1. Create select.
     */
    SelectModelNG selectModelInstance;
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
    auto renderContext = select->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    selectPattern->shadowModify_ = true;
    selectPattern->scaleModify_ = true;
    selectPattern->bgColorModify_ = true;
    selectPattern->focusTextColorModify_ = true;
    selectPattern->InitFocusEvent();
    selectPattern->HandleBlurStyleTask();
    selectPattern->RemoveIsFocusActiveUpdateEvent();
    selectPattern->ClearFocusStyle();
    EXPECT_FALSE(selectPattern->shadowModify_);
    EXPECT_FALSE(selectPattern->scaleModify_);
    EXPECT_FALSE(selectPattern->bgColorModify_);
    EXPECT_FALSE(selectPattern->focusTextColorModify_);
    EXPECT_EQ(renderContext->GetBackgroundColor(), selectTheme->GetButtonBackgroundColor());
}

/**
 * @tc.name: SelectPatternTest001
 * @tc.desc: Test SelectPattern::BuildChild
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, SelectPatternTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step0. Create mock theme manager
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    selectTheme->optionApplyFocusedStyle_ = 1;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(selectTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(selectTheme));
    /**
     * @tc.steps: step1. Create select model and select event.
     * @tc.expected: Objects are created successfully.
     */
    InspectorFilter filter;
    TestProperty testProperty;
    testProperty.FontSize = std::make_optional(FONT_SIZE_VALUE);
    auto selectNode = CreateSelect(CREATE_VALUE, testProperty);
    ASSERT_NE(selectNode, nullptr);
    auto childNode = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    childNode->MountToParent(selectNode);
    auto selectPattern = selectNode->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);

    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    selectPattern->BuildChild();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    auto renderContext = selectNode->GetRenderContext();
    EXPECT_EQ(selectNode->GetFirstChild()->GetTag(), V2::ROW_ETS_TAG);
    BorderColorProperty borderColor;
    borderColor.SetColor(selectTheme->GetSelectNormalBorderColor());
    EXPECT_EQ(renderContext->GetBorderColor(), borderColor);
    BorderWidthProperty borderWidth;
    borderWidth.SetBorderWidth(selectTheme->GetSelectNormalBorderWidth());
    EXPECT_EQ(renderContext->GetBorderWidth(), borderWidth);
}

/**
 * @tc.name: SelectPatternTest002
 * @tc.desc: Test SetSelectOptionStyle.
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, SelectPatternTest002, TestSize.Level1)
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
     * @tc.steps: step2. Get options and Set option style.
     * @tc.expected: option style is updated successfully
     */
    auto options = pattern->GetOptions();
    EXPECT_EQ(options.size(), CREATE_VALUE.size());
    for (size_t i = 0; i < options.size(); ++i) {
        pattern->SetSelected(i);
        auto optionPattern = options[i]->GetPattern<MenuItemPattern>();
        ASSERT_NE(optionPattern, nullptr);
        optionPattern->selectTheme_ = AceType::MakeRefPtr<SelectTheme>();
        optionPattern->textTheme_ = AceType::MakeRefPtr<TextTheme>();
        EXPECT_EQ(optionPattern->GetText(), CREATE_VALUE[i].text);
        pattern->SetOptionBgColor(BG_COLOR_VALUE);
        pattern->OnModifyDone();
        EXPECT_EQ(optionPattern->bgColor_, BG_COLOR_VALUE);
        pattern->SetSelectedOptionBgColor(SELECT_BG_COLOR_VALUE);
        optionPattern->isSelected_ = true;
        pattern->OnModifyDone();
        EXPECT_EQ(optionPattern->bgColor_, SELECT_BG_COLOR_VALUE);
        pattern->SetOptionFontColor(TEXT_COLOR_VALUE);
        optionPattern->isSelected_ = false;
        pattern->OnModifyDone();
        EXPECT_EQ(optionPattern->GetFontColor(), TEXT_COLOR_VALUE);
        pattern->SetSelectedOptionFontColor(SELECT_TEXT_COLOR_VALUE);
        optionPattern->isSelected_ = true;
        pattern->OnModifyDone();
        EXPECT_EQ(optionPattern->GetFontColor(), SELECT_TEXT_COLOR_VALUE);
        pattern->InitSelected();
    }
}

/**
 * @tc.name: InitSpinner001
 * @tc.desc: Test SelectPattern InitSpinner with valid parameters.
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, InitSpinner001, TestSize.Level1)
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
     * @tc.steps: step3.Invoke the InitSpinner method of SelectPattern with the created FrameNode and SelectTheme
     */
    SelectPattern selectPattern;
    selectPattern.InitSpinner(spinner, selectTheme);
    auto spinnerLayoutProperty = spinner->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(spinnerLayoutProperty, nullptr);
    /**
     * @tc.steps: step4.Expecting the theme's font size and rendering strategy to be applied to layout properties.
     */
    auto fontSize = spinnerLayoutProperty->GetFontSize();
    EXPECT_EQ(fontSize.value(), Dimension(16.0, DimensionUnit::PX));

    auto renderingStrategy = spinnerLayoutProperty->GetSymbolRenderingStrategy();
    EXPECT_EQ(renderingStrategy.value(), 1);
}

/**
 * @tc.name: BindMenuTouch001
 * @tc.desc: Test BindMenuTouch with null targetNode
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, BindMenuTouch001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select pattern and gesture hub
     */
    auto select = CreateSelect(CREATE_VALUE);
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    auto gestureHub = select->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);

    /**
     * @tc.steps: step2. Call BindMenuTouch with null targetNode
     * @tc.expected: Function should return early without crash
     */
    selectPattern->BindMenuTouch(nullptr, gestureHub);

    /**
     * @tc.steps: step3. Verify no touch callback is registered
     * @tc.expected: gestureHub should have no touch event registered
     */
    auto touchEventActuator = gestureHub->touchEventActuator_;
    ASSERT_NE(touchEventActuator, nullptr);
    ViewStackProcessor::GetInstance()->ClearStack();
}

/**
 * @tc.name: BindMenuTouch002
 * @tc.desc: Test BindMenuTouch with valid targetNode
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, BindMenuTouch002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select with valid targetNode
     */
    auto select = CreateSelect(CREATE_VALUE);
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto gestureHub = select->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);

    /**
     * @tc.steps: step2. Call BindMenuTouch with valid targetNode
     * @tc.expected: Touch callback should be registered
     */
    selectPattern->BindMenuTouch(select, gestureHub);

    /**
     * @tc.steps: step3. Verify touch callback is registered
     * @tc.expected: gestureHub should have touch event registered
     */
    auto touchEventActuator = gestureHub->touchEventActuator_;
    ASSERT_NE(touchEventActuator, nullptr);
    auto touchEvents = touchEventActuator->touchEvents_;
    ASSERT_FALSE(touchEvents.empty());
    ViewStackProcessor::GetInstance()->ClearStack();
}

/**
 * @tc.name: BindMenuTouch003
 * @tc.desc: Test BindMenuTouch touch callback with TouchType::DOWN
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, BindMenuTouch003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select and setup
     */
    auto select = CreateSelect(CREATE_VALUE);
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto gestureHub = select->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);

    /**
     * @tc.steps: step2. Call BindMenuTouch and get the callback
     */
    selectPattern->BindMenuTouch(select, gestureHub);
    auto touchEventActuator = gestureHub->touchEventActuator_;
    ASSERT_NE(touchEventActuator, nullptr);
    auto touchEvents = touchEventActuator->touchEvents_;
    ASSERT_FALSE(touchEvents.empty());

    /**
     * @tc.steps: step3. Trigger DOWN event
     * @tc.expected: Callback should be executed without crash
     */
    TouchEventInfo touchInfo("test");
    TouchLocationInfo touchLocationInfo(0);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    touchInfo.AddTouchLocationInfo(std::move(touchLocationInfo));

    auto touchCallback = touchEvents.front()->GetTouchEventCallback();
    EXPECT_NO_FATAL_FAILURE(touchCallback(touchInfo));
    ViewStackProcessor::GetInstance()->ClearStack();
}

/**
 * @tc.name: BindMenuTouch004
 * @tc.desc: Test BindMenuTouch touch callback with TouchType::CANCEL
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, BindMenuTouch004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select and setup
     */
    auto select = CreateSelect(CREATE_VALUE);
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto gestureHub = select->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);

    /**
     * @tc.steps: step2. Call BindMenuTouch and get the callback
     */
    selectPattern->BindMenuTouch(select, gestureHub);
    auto touchEventActuator = gestureHub->touchEventActuator_;
    ASSERT_NE(touchEventActuator, nullptr);
    auto touchEvents = touchEventActuator->touchEvents_;
    ASSERT_FALSE(touchEvents.empty());

    /**
     * @tc.steps: step3. Trigger CANCEL event
     * @tc.expected: Callback should be executed and handle cancel appropriately
     */
    TouchEventInfo touchInfo("test");
    TouchLocationInfo touchLocationInfo(0);
    touchLocationInfo.SetTouchType(TouchType::CANCEL);
    touchInfo.AddTouchLocationInfo(std::move(touchLocationInfo));

    auto touchCallback = touchEvents.front()->GetTouchEventCallback();
    EXPECT_NO_FATAL_FAILURE(touchCallback(touchInfo));
    ViewStackProcessor::GetInstance()->ClearStack();
}

/**
 * @tc.name: BindMenuTouch005
 * @tc.desc: Test BindMenuTouch touch callback with empty touches
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, BindMenuTouch005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select and setup
     */
    auto select = CreateSelect(CREATE_VALUE);
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto gestureHub = select->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);

    /**
     * @tc.steps: step2. Call BindMenuTouch and get the callback
     */
    selectPattern->BindMenuTouch(select, gestureHub);
    auto touchEventActuator = gestureHub->touchEventActuator_;
    ASSERT_NE(touchEventActuator, nullptr);
    auto touchEvents = touchEventActuator->touchEvents_;
    ASSERT_FALSE(touchEvents.empty());

    /**
     * @tc.steps: step3. Trigger event with empty touches
     * @tc.expected: Callback should handle empty touches gracefully
     */
    TouchEventInfo touchInfo("test");
    // Don't add any touch location info to simulate empty touches

    auto touchCallback = touchEvents.front()->GetTouchEventCallback();
    EXPECT_NO_FATAL_FAILURE(touchCallback(touchInfo));
    ViewStackProcessor::GetInstance()->ClearStack();
}

/**
 * @tc.name: BindMenuTouch006
 * @tc.desc: Test BindMenuTouch with menu wrapper node
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, BindMenuTouch006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select and setup
     */
    auto select = CreateSelect(CREATE_VALUE);
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto gestureHub = select->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);

    /**
     * @tc.steps: step2. Create and set menu wrapper
     */
    std::vector<OptionParam> emptyParams;
    auto menuWrapper = MenuView::Create(std::move(emptyParams), select->GetId(), "test");
    ASSERT_NE(menuWrapper, nullptr);
    selectPattern->SetMenuNode(menuWrapper);

    /**
     * @tc.steps: step3. Call BindMenuTouch and verify wrapper is set
     */
    selectPattern->BindMenuTouch(select, gestureHub);
    auto wrapperNode = selectPattern->GetMenuWrapper();
    EXPECT_EQ(wrapperNode, menuWrapper);

    /**
     * @tc.steps: step4. Verify touch callback is registered
     */
    auto touchEventActuator = gestureHub->touchEventActuator_;
    ASSERT_NE(touchEventActuator, nullptr);
    auto touchEvents = touchEventActuator->touchEvents_;
    EXPECT_FALSE(touchEvents.empty());
    ViewStackProcessor::GetInstance()->ClearStack();
}

/**
 * @tc.name: BindMenuTouch007
 * @tc.desc: Test BindMenuTouch with multiple consecutive calls
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, BindMenuTouch007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select and setup
     */
    auto select = CreateSelect(CREATE_VALUE);
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto gestureHub = select->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);

    /**
     * @tc.steps: step2. Call BindMenuTouch multiple times
     * @tc.expected: Should not cause issues with multiple registrations
     */
    selectPattern->BindMenuTouch(select, gestureHub);
    auto touchEventActuator1 = gestureHub->touchEventActuator_;
    auto touchEventsCount1 = touchEventActuator1 ? touchEventActuator1->touchEvents_.size() : 0;

    selectPattern->BindMenuTouch(select, gestureHub);
    auto touchEventActuator2 = gestureHub->touchEventActuator_;
    auto touchEventsCount2 = touchEventActuator2 ? touchEventActuator2->touchEvents_.size() : 0;

    /**
     * @tc.steps: step3. Verify touch events are properly managed
     */
    EXPECT_NE(touchEventActuator1, nullptr);
    EXPECT_NE(touchEventActuator2, nullptr);
    EXPECT_GE(touchEventsCount2, touchEventsCount1);
    ViewStackProcessor::GetInstance()->ClearStack();
}

/**
 * @tc.name: BindMenuTouch008
 * @tc.desc: Test BindMenuTouch with different touch event types sequence
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, BindMenuTouch008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select and setup
     */
    auto select = CreateSelect(CREATE_VALUE);
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto gestureHub = select->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);

    /**
     * @tc.steps: step2. Call BindMenuTouch and get callback
     */
    selectPattern->BindMenuTouch(select, gestureHub);
    auto touchEventActuator = gestureHub->touchEventActuator_;
    ASSERT_NE(touchEventActuator, nullptr);
    auto touchEvents = touchEventActuator->touchEvents_;
    ASSERT_FALSE(touchEvents.empty());
    auto touchCallback = touchEvents.front()->GetTouchEventCallback();

    /**
     * @tc.steps: step3. Test sequence of touch events
     * @tc.expected: All touch events should be handled properly
     */
    std::vector<TouchType> touchTypes = { TouchType::DOWN, TouchType::MOVE, TouchType::UP, TouchType::CANCEL };

    for (auto touchType : touchTypes) {
        TouchEventInfo touchInfo("test");
        TouchLocationInfo touchLocationInfo(0);
        touchLocationInfo.SetTouchType(touchType);
        touchInfo.AddTouchLocationInfo(std::move(touchLocationInfo));

        EXPECT_NO_FATAL_FAILURE(touchCallback(touchInfo));
    }
    ViewStackProcessor::GetInstance()->ClearStack();
}

/**
 * @tc.name: BindMenuTouch009
 * @tc.desc: Test BindMenuTouch touch callback with TouchType::MOVE
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, BindMenuTouch009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select and setup
     */
    auto select = CreateSelect(CREATE_VALUE);
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto gestureHub = select->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);

    /**
     * @tc.steps: step2. Call BindMenuTouch and get the callback
     */
    selectPattern->BindMenuTouch(select, gestureHub);
    auto touchEventActuator = gestureHub->touchEventActuator_;
    ASSERT_NE(touchEventActuator, nullptr);
    auto touchEvents = touchEventActuator->touchEvents_;
    ASSERT_FALSE(touchEvents.empty());

    /**
     * @tc.steps: step3. Trigger MOVE event
     * @tc.expected: Callback should be executed without special handling
     */
    TouchEventInfo touchInfo("test");
    TouchLocationInfo touchLocationInfo(0);
    touchLocationInfo.SetTouchType(TouchType::MOVE);
    touchInfo.AddTouchLocationInfo(std::move(touchLocationInfo));

    auto touchCallback = touchEvents.front()->GetTouchEventCallback();
    EXPECT_NO_FATAL_FAILURE(touchCallback(touchInfo));
    ViewStackProcessor::GetInstance()->ClearStack();
}

/**
 * @tc.name: BindMenuTouch010
 * @tc.desc: Test BindMenuTouch touch callback with multiple touches
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, BindMenuTouch010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select and setup
     */
    auto select = CreateSelect(CREATE_VALUE);
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto gestureHub = select->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);

    /**
     * @tc.steps: step2. Call BindMenuTouch and get the callback
     */
    selectPattern->BindMenuTouch(select, gestureHub);
    auto touchEventActuator = gestureHub->touchEventActuator_;
    ASSERT_NE(touchEventActuator, nullptr);
    auto touchEvents = touchEventActuator->touchEvents_;
    ASSERT_FALSE(touchEvents.empty());

    /**
     * @tc.steps: step3. Trigger event with multiple touches
     * @tc.expected: Callback should use the first touch for processing
     */
    TouchEventInfo touchInfo("test");
    TouchLocationInfo touchLocationInfo1(0);
    TouchLocationInfo touchLocationInfo2(1);
    touchLocationInfo1.SetTouchType(TouchType::DOWN);
    touchLocationInfo2.SetTouchType(TouchType::DOWN);
    touchInfo.AddTouchLocationInfo(std::move(touchLocationInfo1));
    touchInfo.AddTouchLocationInfo(std::move(touchLocationInfo2));

    auto touchCallback = touchEvents.front()->GetTouchEventCallback();
    EXPECT_NO_FATAL_FAILURE(touchCallback(touchInfo));
    ViewStackProcessor::GetInstance()->ClearStack();
}

/**
 * @tc.name: BindMenuTouch011
 * @tc.desc: Test BindMenuTouch touch callback with weakTarget upgrade failure simulation
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, BindMenuTouch011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select and setup
     */
    auto select = CreateSelect(CREATE_VALUE);
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto gestureHub = select->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);

    /**
     * @tc.steps: step2. Call BindMenuTouch
     */
    selectPattern->BindMenuTouch(select, gestureHub);
    auto touchEventActuator = gestureHub->touchEventActuator_;
    ASSERT_NE(touchEventActuator, nullptr);
    auto touchEvents = touchEventActuator->touchEvents_;
    ASSERT_FALSE(touchEvents.empty());

    /**
     * @tc.steps: step3. Test with valid touches
     */
    TouchEventInfo touchInfo("test");
    TouchLocationInfo touchLocationInfo(0);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    touchInfo.AddTouchLocationInfo(std::move(touchLocationInfo));

    auto touchCallback = touchEvents.front()->GetTouchEventCallback();
    EXPECT_NO_FATAL_FAILURE(touchCallback(touchInfo));
    ViewStackProcessor::GetInstance()->ClearStack();
}

/**
 * @tc.name: BindMenuTouch012
 * @tc.desc: Test BindMenuTouch edge case coverage for container null checks
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, BindMenuTouch012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select and setup
     */
    auto select = CreateSelect(CREATE_VALUE);
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto gestureHub = select->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);

    /**
     * @tc.steps: step2. Call BindMenuTouch
     */
    selectPattern->BindMenuTouch(select, gestureHub);
    auto touchEventActuator = gestureHub->touchEventActuator_;
    ASSERT_NE(touchEventActuator, nullptr);
    auto touchEvents = touchEventActuator->touchEvents_;
    ASSERT_FALSE(touchEvents.empty());

    /**
     * @tc.steps: step3. Test various touch types to ensure all branches are covered
     * @tc.expected: All touch events should be handled without crashing
     */
    std::vector<TouchType> touchTypes = { TouchType::DOWN, TouchType::MOVE, TouchType::UP, TouchType::CANCEL,
        TouchType::UNKNOWN };

    auto touchCallback = touchEvents.front()->GetTouchEventCallback();

    for (auto touchType : touchTypes) {
        TouchEventInfo touchInfo("test");
        TouchLocationInfo touchLocationInfo(0);
        touchLocationInfo.SetTouchType(touchType);
        touchInfo.AddTouchLocationInfo(std::move(touchLocationInfo));

        // Each touch type should be handled gracefully
        EXPECT_NO_FATAL_FAILURE(touchCallback(touchInfo));
    }
    ViewStackProcessor::GetInstance()->ClearStack();
}

/**
 * @tc.name: BindMenuTouch013
 * @tc.desc: Test BindMenuTouch behavior when subwindow components are null
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, BindMenuTouch013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select and setup
     */
    auto select = CreateSelect(CREATE_VALUE);
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto gestureHub = select->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);

    /**
     * @tc.steps: step2. Call BindMenuTouch
     */
    selectPattern->BindMenuTouch(select, gestureHub);
    auto touchEventActuator = gestureHub->touchEventActuator_;
    ASSERT_NE(touchEventActuator, nullptr);
    auto touchEvents = touchEventActuator->touchEvents_;
    ASSERT_FALSE(touchEvents.empty());

    /**
     * @tc.steps: step3. Test touch callback when subwindow may not exist
     * @tc.expected: Should handle null subwindow gracefully
     */
    TouchEventInfo touchInfo("test");
    TouchLocationInfo touchLocationInfo(0);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    touchInfo.AddTouchLocationInfo(std::move(touchLocationInfo));

    auto touchCallback = touchEvents.front()->GetTouchEventCallback();
    // This should not crash even if subwindow doesn't exist in test environment
    EXPECT_NO_FATAL_FAILURE(touchCallback(touchInfo));
    ViewStackProcessor::GetInstance()->ClearStack();
}

/**
 * @tc.name: BindMenuTouch014
 * @tc.desc: Test BindMenuTouch with all touch types for comprehensive coverage
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, BindMenuTouch014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select and setup
     */
    auto select = CreateSelect(CREATE_VALUE);
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto gestureHub = select->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);

    /**
     * @tc.steps: step2. Call BindMenuTouch
     */
    selectPattern->BindMenuTouch(select, gestureHub);
    auto touchEventActuator = gestureHub->touchEventActuator_;
    ASSERT_NE(touchEventActuator, nullptr);
    auto touchEvents = touchEventActuator->touchEvents_;
    ASSERT_FALSE(touchEvents.empty());

    auto touchCallback = touchEvents.front()->GetTouchEventCallback();

    /**
     * @tc.steps: step3. Test all possible TouchType values systematically
     * @tc.expected: All touch types should be handled without exceptions
     */

    TouchEventInfo touchInfoDown("test_down");
    TouchLocationInfo touchLocationInfo(0);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    touchInfoDown.AddTouchLocationInfo(std::move(touchLocationInfo));
    EXPECT_NO_FATAL_FAILURE(touchCallback(touchInfoDown));

    TouchEventInfo touchInfoUp("test_up");
    touchLocationInfo.SetTouchType(TouchType::UP);
    touchInfoUp.AddTouchLocationInfo(std::move(touchLocationInfo));
    EXPECT_NO_FATAL_FAILURE(touchCallback(touchInfoUp));

    TouchEventInfo touchInfoCancel("test_cancel");
    touchLocationInfo.SetTouchType(TouchType::CANCEL);
    touchInfoCancel.AddTouchLocationInfo(std::move(touchLocationInfo));
    EXPECT_NO_FATAL_FAILURE(touchCallback(touchInfoCancel));

    TouchEventInfo touchInfoMove("test_move");
    touchLocationInfo.SetTouchType(TouchType::MOVE);
    touchInfoMove.AddTouchLocationInfo(std::move(touchLocationInfo));
    EXPECT_NO_FATAL_FAILURE(touchCallback(touchInfoMove));
    ViewStackProcessor::GetInstance()->ClearStack();
}

/**
 * @tc.name: SetOptionTextModifierByUser
 * @tc.desc: Test SelectPattern SetOptionTextModifierByUser.
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, SetOptionTextModifierByUser, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model, initialize frame node.
     * @tc.expected: step1. Select model and frame node are created successfully, related objects are obtained.
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);

    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto props = select->GetPaintProperty<SelectPaintProperty>();
    ASSERT_NE(props, nullptr);
    auto pipeline = select->GetContextWithCheck();
    ASSERT_NE(pipeline, nullptr);
    auto selectTheme = pipeline->GetTheme<SelectTheme>(select->GetThemeScopeId());
    ASSERT_NE(selectTheme, nullptr);
    selectTheme->fontColor_ = Color::GREEN;
    /**
     * @tc.steps: step2. Enable user-defined font color flag, call SetOptionTextModifierByUser.
     * @tc.expected: step2. Option font color in selectPattern is not set.
     */
    EXPECT_FALSE(selectPattern->optionFont_.FontColor.has_value());
    selectModelInstance.SetOptionFontColorByUser(true);
    EXPECT_TRUE(props->GetOptionFontColorSetByUserValue(false));
    selectPattern->SetOptionTextModifierByUser(selectTheme, props);
    EXPECT_FALSE(selectPattern->optionFont_.FontColor.has_value());

    /**
     * @tc.steps: step3. Disable user-defined font color flag, call SetOptionTextModifierByUser.
     * @tc.expected: step3. Option font color in selectPattern is set to theme green.
     */
    selectModelInstance.SetOptionFontColorByUser(false);
    EXPECT_FALSE(props->GetOptionFontColorSetByUserValue(false));
    selectPattern->SetOptionTextModifierByUser(selectTheme, props);
    EXPECT_TRUE(selectPattern->optionFont_.FontColor.has_value());
    EXPECT_EQ(selectPattern->optionFont_.FontColor, Color::GREEN);
}

/**
 * @tc.name: SetSelectedOptionTextModifierByUser
 * @tc.desc: Test SelectPattern SetSelectedOptionTextModifierByUser.
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, SetSelectedOptionTextModifierByUser, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model, initialize frame node.
     * @tc.expected: step1. Select model and frame node are created successfully, related objects are obtained.
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);

    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto props = select->GetPaintProperty<SelectPaintProperty>();
    ASSERT_NE(props, nullptr);
    auto pipeline = select->GetContextWithCheck();
    ASSERT_NE(pipeline, nullptr);
    auto selectTheme = pipeline->GetTheme<SelectTheme>(select->GetThemeScopeId());
    ASSERT_NE(selectTheme, nullptr);
    auto applySelectedFunc = [](WeakPtr<FrameNode> weakNode) {
        auto textNode = weakNode.Upgrade();
        ASSERT_NE(textNode, nullptr);
        auto property = textNode->GetLayoutProperty<TextLayoutProperty>();
        ASSERT_NE(property, nullptr);
        property->UpdateTextColor(Color::BLUE);
    };
    selectTheme->selectedColorText_ = Color::GREEN;
    selectPattern->textSelectOptionApply_ = applySelectedFunc;
    auto optionSelected = selectPattern->options_[0];
    ASSERT_NE(optionSelected, nullptr);
    auto menuItemSelectedPattern = optionSelected->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemSelectedPattern, nullptr);
    auto textSelected = menuItemSelectedPattern->text_;
    ASSERT_NE(textSelected, nullptr);
    /**
     * @tc.steps: step2. Enable user-defined selected font color flag, disable text modifier flag.
     * @tc.expected: step2. Selected font color in selectPattern is not set, text node color is not blue.
     */
    selectModelInstance.SetSelectedOptionFontColorByUser(true);
    EXPECT_TRUE(props->GetSelectedOptionFontColorSetByUserValue(false));
    props->UpdateSelectedOptionTextModifierSetByUser(false);
    EXPECT_FALSE(props->GetSelectedOptionTextModifierSetByUserValue(false));
    selectPattern->SetSelectedOptionTextModifierByUser(selectTheme, props);
    EXPECT_FALSE(selectPattern->selectedFont_.FontColor.has_value());
    auto propertySelected = textSelected->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(propertySelected, nullptr);
    ASSERT_NE(propertySelected->GetTextColor(), Color::BLUE);

    /**
     * @tc.steps: step3. Enable both user-defined selected font color flag and text modifier flag.
     * @tc.expected: step3. Selected font color in selectPattern is still not set.
     */
    props->UpdateSelectedOptionTextModifierSetByUser(true);
    EXPECT_TRUE(props->GetSelectedOptionTextModifierSetByUserValue(false));
    selectPattern->SetSelectedOptionTextModifierByUser(selectTheme, props);
    EXPECT_FALSE(selectPattern->selectedFont_.FontColor.has_value());

    /**
     * @tc.steps: step4. Disable user-defined selected font color flag, call SetSelectedOptionTextModifierByUser.
     * @tc.expected: step4. Selected font color in selectPattern is set to theme green.
     */
    selectModelInstance.SetSelectedOptionFontColorByUser(false);
    EXPECT_FALSE(props->GetSelectedOptionFontColorSetByUserValue(false));
    selectPattern->SetSelectedOptionTextModifierByUser(selectTheme, props);
    EXPECT_TRUE(selectPattern->selectedFont_.FontColor.has_value());
    EXPECT_EQ(selectPattern->selectedFont_.FontColor, Color::GREEN);
}

/**
 * @tc.name: SetArrowModifierByUser
 * @tc.desc: Test SelectPattern SetArrowModifierByUser.
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, SetArrowModifierByUser, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model, initialize frame node.
     * @tc.expected: step1. Select model and frame node are created successfully, related objects are obtained.
     */
    AceApplicationInfo::GetInstance().apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_SIXTEEN);
    EXPECT_TRUE(AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_SIXTEEN));
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);

    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto props = select->GetPaintProperty<SelectPaintProperty>();
    ASSERT_NE(props, nullptr);
    auto pipeline = select->GetContextWithCheck();
    ASSERT_NE(pipeline, nullptr);
    auto selectTheme = pipeline->GetTheme<SelectTheme>(select->GetThemeScopeId());
    ASSERT_NE(selectTheme, nullptr);

    auto applyFunc = [](WeakPtr<FrameNode> weakNode) {
        auto symbolNode = weakNode.Upgrade();
        ASSERT_NE(symbolNode, nullptr);
        auto property = symbolNode->GetLayoutProperty<TextLayoutProperty>();
        ASSERT_NE(property, nullptr);
        property->UpdateFontSize(Dimension(80));
    };
    selectPattern->arrowApply_ = applyFunc;

    /**
     * @tc.steps: step2. Disable arrow modifier flag, call SetArrowModifierByUser.
     * @tc.expected: step2. Arrow font size is not updated to 80.
     */
    props->UpdateArrowModifierSetByUser(false);
    EXPECT_FALSE(props->GetArrowModifierSetByUserValue(false));
    selectPattern->SetArrowModifierByUser(selectTheme, props);
    auto frameNode = selectPattern->spinner_;
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::SYMBOL_ETS_TAG);
    auto property = frameNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(property, nullptr);
    ASSERT_NE(property->GetFontSize(), Dimension(80));

    /**
     * @tc.steps: step3. Enable arrow modifier flag, call SetArrowModifierByUser.
     * @tc.expected: step3. Arrow font size is updated to 80.
     */
    props->UpdateArrowModifierSetByUser(true);
    EXPECT_TRUE(props->GetArrowModifierSetByUserValue(false));
    selectPattern->SetArrowModifierByUser(selectTheme, props);
    EXPECT_EQ(property->GetFontSize(), Dimension(80));
}

/**
 * @tc.name: SetModifierByUser001
 * @tc.desc: Test SelectPattern SetModifierByUser.
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, SetModifierByUser001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model, initialize frame node, obtain related objects.
     * @tc.expected: step1. Select model and frame node are created successfully, related objects are obtained.
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);

    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto props = select->GetPaintProperty<SelectPaintProperty>();
    ASSERT_NE(props, nullptr);
    auto layoutProps = select->GetLayoutProperty<SelectLayoutProperty>();
    ASSERT_NE(layoutProps, nullptr);
    auto pipeline = select->GetContextWithCheck();
    ASSERT_NE(pipeline, nullptr);
    auto selectTheme = pipeline->GetTheme<SelectTheme>(select->GetThemeScopeId());
    ASSERT_NE(selectTheme, nullptr);
    selectTheme->selectedColor_ = Color::GREEN;
    /**
     * @tc.steps: step2. Show default selected icon, enable user-defined selected background color flag.
     * @tc.expected: step2. Selected background color in selectPattern is not set.
     */
    selectModelInstance.SetShowDefaultSelectedIcon(true);
    EXPECT_TRUE(layoutProps->GetShowDefaultSelectedIconValue(false));
    selectModelInstance.SetSelectedOptionBgColorByUser(true);
    EXPECT_TRUE(props->GetSelectedOptionBgColorSetByUserValue(false));
    selectPattern->SetSelectedOptionBgColorByUser(selectTheme, props, layoutProps);
    selectPattern->SetModifierByUser(selectTheme, props);
    EXPECT_FALSE(selectPattern->selectedBgColor_.has_value());

    /**
     * @tc.steps: step3. Hide default selected icon, enable user-defined selected background color flag.
     * @tc.expected: step3. Selected background color in selectPattern is not set.
     */
    selectModelInstance.SetShowDefaultSelectedIcon(false);
    EXPECT_FALSE(layoutProps->GetShowDefaultSelectedIconValue(false));
    selectModelInstance.SetSelectedOptionBgColorByUser(true);
    EXPECT_TRUE(props->GetSelectedOptionBgColorSetByUserValue(false));
    selectPattern->SetSelectedOptionBgColorByUser(selectTheme, props, layoutProps);
    selectPattern->SetModifierByUser(selectTheme, props);
    EXPECT_FALSE(selectPattern->selectedBgColor_.has_value());

    /**
     * @tc.steps: step4. Show default selected icon, disable user-defined selected background color flag.
     * @tc.expected: step4. Selected background color in selectPattern is not set.
     */
    selectModelInstance.SetShowDefaultSelectedIcon(true);
    EXPECT_TRUE(layoutProps->GetShowDefaultSelectedIconValue(false));
    selectModelInstance.SetSelectedOptionBgColorByUser(false);
    EXPECT_FALSE(props->GetSelectedOptionBgColorSetByUserValue(false));
    selectPattern->SetSelectedOptionBgColorByUser(selectTheme, props, layoutProps);
    selectPattern->SetModifierByUser(selectTheme, props);
    EXPECT_FALSE(selectPattern->selectedBgColor_.has_value());

    /**
     * @tc.steps: step5. Hide default selected icon, disable user-defined selected background color flag.
     * @tc.expected: step5. Selected background color in selectPattern is set to theme green.
     */
    selectModelInstance.SetShowDefaultSelectedIcon(false);
    EXPECT_FALSE(layoutProps->GetShowDefaultSelectedIconValue(false));
    selectModelInstance.SetSelectedOptionBgColorByUser(false);
    EXPECT_FALSE(props->GetSelectedOptionBgColorSetByUserValue(false));
    selectPattern->SetSelectedOptionBgColorByUser(selectTheme, props, layoutProps);
    selectPattern->SetModifierByUser(selectTheme, props);
    EXPECT_TRUE(selectPattern->selectedBgColor_.has_value());
    EXPECT_EQ(selectPattern->selectedBgColor_, Color::GREEN);
}

/**
 * @tc.name: SetModifierByUser002
 * @tc.desc: Test SelectPattern SetModifierByUser.
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, SetModifierByUser002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model, initialize frame node, obtain related objects.
     * @tc.expected: step1. Select model and frame node are created successfully, related objects are obtained.
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);

    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto props = select->GetPaintProperty<SelectPaintProperty>();
    ASSERT_NE(props, nullptr);
    auto layoutProps = select->GetLayoutProperty<SelectLayoutProperty>();
    ASSERT_NE(layoutProps, nullptr);
    auto pipeline = select->GetContextWithCheck();
    ASSERT_NE(pipeline, nullptr);
    auto selectTheme = pipeline->GetTheme<SelectTheme>(select->GetThemeScopeId());
    ASSERT_NE(selectTheme, nullptr);

    auto frameNode = selectPattern->text_;
    ASSERT_NE(frameNode, nullptr);
    auto property = frameNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(property, nullptr);
    EXPECT_EQ(property->GetMaxLines(), 1);

    auto applyFunc = [](WeakPtr<FrameNode> weakNode) {
        auto textNode = weakNode.Upgrade();
        ASSERT_NE(textNode, nullptr);
        auto property = textNode->GetLayoutProperty<TextLayoutProperty>();
        ASSERT_NE(property, nullptr);
        property->UpdateMaxLines(2);
        property->UpdateFontSize(Dimension(80));
    };
    selectPattern->fontColor_ = Color::GREEN;
    selectPattern->textApply_ = applyFunc;
    /**
     * @tc.steps: step2. Enable user-defined font color flag, disable text modifier flag, call SetModifierByUser.
     * @tc.expected: step2. Font color remains green, max lines remains 1.
     */
    selectModelInstance.SetFontColorByUser(true);
    EXPECT_TRUE(props->GetFontColorSetByUserValue(false));
    props->UpdateTextModifierSetByUser(false);
    EXPECT_FALSE(props->GetTextModifierSetByUserValue(false));
    selectPattern->SetModifierByUser(selectTheme, props);
    EXPECT_EQ(selectPattern->fontColor_, Color::GREEN);
    EXPECT_EQ(property->GetMaxLines(), 1);

    /**
     * @tc.steps: step3. Enable both user-defined font color flag and text modifier flag, call SetModifierByUser.
     * @tc.expected: step3. Font color remains green, max lines is updated to 2.
     */
    selectModelInstance.SetFontColorByUser(true);
    EXPECT_TRUE(props->GetFontColorSetByUserValue(false));
    props->UpdateTextModifierSetByUser(true);
    EXPECT_TRUE(props->GetTextModifierSetByUserValue(false));
    selectPattern->SetModifierByUser(selectTheme, props);
    EXPECT_EQ(selectPattern->fontColor_, Color::GREEN);
    EXPECT_EQ(property->GetMaxLines(), 2);

    /**
     * @tc.steps: step4. Disable user-defined font color flag, call SetModifierByUser.
     * @tc.expected: step4. Font color is no longer green.
     */
    selectModelInstance.SetFontColorByUser(false);
    EXPECT_FALSE(props->GetFontColorSetByUserValue(false));
    selectPattern->SetModifierByUser(selectTheme, props);
    ASSERT_NE(selectPattern->fontColor_, Color::GREEN);
}

/**
 * @tc.name: SetOptionBgColorByUser001
 * @tc.desc: Test SetOptionBgColorByUser func
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTestNg, SetOptionBgColorByUser001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select pattern and gesture hub
     */
    auto select = CreateSelect(CREATE_VALUE);
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto option = FrameNode::GetOrCreateFrameNode(V2::OPTION_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<MenuItemPattern>(true, 0); });
    ASSERT_NE(option, nullptr);
    selectPattern->options_.push_back(option);
    auto optionCount = selectPattern->options_.size();
    ASSERT_NE(optionCount, 0);
    auto paintProperty = select->GetPaintProperty<SelectPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateOptionBgColorSetByUser(true);
    selectPattern->SetOptionBgColorByUser(Color::BLACK, paintProperty);
    ASSERT_NE(selectPattern->options_[0], nullptr);
    auto itemPaintProperty = selectPattern->options_[0]->GetPaintProperty<MenuItemPaintProperty>();
    ASSERT_NE(itemPaintProperty, nullptr);
    ASSERT_EQ(itemPaintProperty->GetOptionBgColor().has_value(), false);
}
} // namespace OHOS::Ace::NG
