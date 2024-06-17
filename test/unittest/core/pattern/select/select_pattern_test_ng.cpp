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

#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

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
#include "core/components_ng/pattern/menu/menu_layout_property.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/option/option_paint_property.h"
#include "core/components_ng/pattern/option/option_pattern.h"
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
const SizeF FULL_SCREEN_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
const std::vector<std::string> FONT_FAMILY_VALUE = { "cursive" };
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
};

void SelectPatternTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
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
}
} // namespace OHOS::Ace::NG
