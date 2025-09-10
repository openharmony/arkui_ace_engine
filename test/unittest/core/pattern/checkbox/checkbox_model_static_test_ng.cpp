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

// Add the following two macro definitions to test the private and protected method.
#define private public
#define protected public
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/rosen/mock_canvas.h"

#include "core/components/checkable/checkable_theme.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/checkbox/checkbox_accessibility_property.h"
#include "core/components_ng/pattern/checkbox/checkbox_model_ng.h"
#include "core/components_ng/pattern/checkbox/checkbox_model_static.h"
#include "core/components_ng/pattern/checkbox/checkbox_paint_property.h"
#include "core/components_ng/pattern/checkbox/checkbox_pattern.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_model_ng.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_paint_property.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_pattern.h"
#include "core/components_ng/pattern/linear_layout/column_model_ng.h"
#include "core/components_ng/pattern/stage/page_event_hub.h"
#include "core/components_ng/pattern/stage/stage_manager.h"
#include "core/components_ng/pattern/stage/stage_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

using namespace testing;
using namespace testing::ext;
using CheckboxBuilderFunc = std::optional<std::function<void()>>;

namespace OHOS::Ace::NG {
namespace {
const bool SELECTED = true;
const Color SELECTED_COLOR = Color::BLUE;
const Color UNSELECTED_COLOR = Color::RED;
const Color CHECK_MARK_COLOR = Color::GREEN;
constexpr Dimension CHECK_MARK_SIZE = Dimension(10.0);
constexpr Dimension CHECK_MARK_WIDTH = Dimension(5.0);
} // namespace

class CheckboxStaticTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    CheckboxBuilderFunc CheckboxBuilder();
};

void CheckboxStaticTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<CheckboxTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<CheckboxTheme>()));

    RefPtr<FrameNode> stageNode = AceType::MakeRefPtr<FrameNode>("STAGE", -1, AceType::MakeRefPtr<Pattern>());
    auto stageManager = AceType::MakeRefPtr<StageManager>(stageNode);
    MockPipelineContext::GetCurrent()->stageManager_ = stageManager;
}

void CheckboxStaticTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

CheckboxBuilderFunc CheckboxStaticTestNg::CheckboxBuilder()
{
    return []() {
        ColumnModelNG colModel;
        colModel.Create(Dimension(0), nullptr, "");
        ViewAbstract::SetWidth(CalcLength(10.f));
        ViewAbstract::SetHeight(CalcLength(10.f));
    };
}

/**
 * @tc.name: CheckboxStaticTestNgt001
 * @tc.desc: test checkbox SetSelect.
 * @tc.type: FUNC
 */
HWTEST_F(CheckboxStaticTestNg, CheckboxStaticTestNg001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create checkbox frameNode.
     */
    auto node = CheckBoxModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::CHECK_BOX_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    ASSERT_NE(node, nullptr);
    /**
     * @tc.steps: step2. create checkbox paintProperty.
     */
    auto checkBoxPaintProperty = frameNode->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);

    /**
     * @tc.steps: step3. test SetSelect.
     * @tc.expected: step3. the property value meet expectations.
     */
    std::optional<bool> selectValue = std::nullopt;
    CheckBoxModelStatic::SetSelect(frameNode, selectValue);
    EXPECT_EQ(checkBoxPaintProperty->GetCheckBoxSelect(), std::nullopt);
    selectValue = SELECTED;
    CheckBoxModelStatic::SetSelect(frameNode, selectValue);
    EXPECT_EQ(checkBoxPaintProperty->GetCheckBoxSelect(), SELECTED);
}

/**
 * @tc.name: CheckboxStaticTestNgt002
 * @tc.desc: test checkbox SetSelectedColor.
 * @tc.type: FUNC
 */
HWTEST_F(CheckboxStaticTestNg, CheckboxStaticTestNg002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create checkbox frameNode.
     */
    auto node = CheckBoxModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::CHECK_BOX_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    ASSERT_NE(node, nullptr);
    /**
     * @tc.steps: step2. create checkbox paintProperty.
     */
    auto checkBoxPaintProperty = frameNode->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);

    /**
     * @tc.steps: step3. test SetSelect.
     * @tc.expected: step3. the property value meet expectations.
     */
    std::optional<Color> selectColor = std::nullopt;
    CheckBoxModelStatic::SetSelectedColor(frameNode, selectColor);
    EXPECT_EQ(checkBoxPaintProperty->GetCheckBoxSelectedColor(), std::nullopt);
    selectColor = SELECTED_COLOR;
    CheckBoxModelStatic::SetSelectedColor(frameNode, selectColor);
    EXPECT_EQ(checkBoxPaintProperty->GetCheckBoxSelectedColor(), SELECTED_COLOR);
}

/**
 * @tc.name: CheckboxStaticTestNgt003
 * @tc.desc: test checkbox SetUnSelectedColor.
 * @tc.type: FUNC
 */
HWTEST_F(CheckboxStaticTestNg, CheckboxStaticTestNg003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create checkbox frameNode.
     */
    auto node = CheckBoxModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::CHECK_BOX_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    ASSERT_NE(node, nullptr);
    /**
     * @tc.steps: step2. create checkbox paintProperty.
     */
    auto checkBoxPaintProperty = frameNode->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);

    /**
     * @tc.steps: step3. test SetUnSelectedColor.
     * @tc.expected: step3. the property value meet expectations.
     */
    std::optional<Color> unSelectColor = std::nullopt;
    CheckBoxModelStatic::SetUnSelectedColor(frameNode, unSelectColor);
    EXPECT_EQ(checkBoxPaintProperty->GetCheckBoxUnSelectedColor(), std::nullopt);
    unSelectColor = UNSELECTED_COLOR;
    CheckBoxModelStatic::SetUnSelectedColor(frameNode, unSelectColor);
    EXPECT_EQ(checkBoxPaintProperty->GetCheckBoxUnSelectedColor(), UNSELECTED_COLOR);
}

/**
 * @tc.name: CheckboxStaticTestNgt004
 * @tc.desc: test checkbox SetCheckMarkColor.
 * @tc.type: FUNC
 */
HWTEST_F(CheckboxStaticTestNg, CheckboxStaticTestNg004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create checkbox frameNode.
     */
    auto node = CheckBoxModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::CHECK_BOX_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    ASSERT_NE(node, nullptr);
    /**
     * @tc.steps: step2. create checkbox paintProperty.
     */
    auto checkBoxPaintProperty = frameNode->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);

    /**
     * @tc.steps: step3. test SetCheckMarkColor.
     * @tc.expected: step3. the property value meet expectations.
     */
    std::optional<Color> markColor = std::nullopt;
    CheckBoxModelStatic::SetCheckMarkColor(frameNode, markColor);
    EXPECT_EQ(checkBoxPaintProperty->GetCheckBoxCheckMarkColor(), std::nullopt);
    markColor = CHECK_MARK_COLOR;
    CheckBoxModelStatic::SetCheckMarkColor(frameNode, markColor);
    EXPECT_EQ(checkBoxPaintProperty->GetCheckBoxCheckMarkColor(), CHECK_MARK_COLOR);
}

/**
 * @tc.name: CheckboxStaticTestNgt005
 * @tc.desc: test checkbox SetCheckMarkSize.
 * @tc.type: FUNC
 */
HWTEST_F(CheckboxStaticTestNg, CheckboxStaticTestNg005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create checkbox frameNode.
     */
    auto node = CheckBoxModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::CHECK_BOX_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    ASSERT_NE(node, nullptr);
    /**
     * @tc.steps: step2. create checkbox paintProperty.
     */
    auto checkBoxPaintProperty = frameNode->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);

    /**
     * @tc.steps: step3. test SetCheckMarkSize.
     * @tc.expected: step3. the property value meet expectations.
     */
    std::optional<Dimension> markSize = std::nullopt;
    CheckBoxModelStatic::SetCheckMarkSize(frameNode, markSize);
    EXPECT_EQ(checkBoxPaintProperty->GetCheckBoxCheckMarkSize(), std::nullopt);
    markSize = CHECK_MARK_SIZE;
    CheckBoxModelStatic::SetCheckMarkSize(frameNode, markSize);
    EXPECT_EQ(checkBoxPaintProperty->GetCheckBoxCheckMarkSize(), CHECK_MARK_SIZE);
}

/**
 * @tc.name: CheckboxStaticTestNgt006
 * @tc.desc: test checkbox SetCheckMarkWidth.
 * @tc.type: FUNC
 */
HWTEST_F(CheckboxStaticTestNg, CheckboxStaticTestNg006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create checkbox frameNode.
     */
    auto node = CheckBoxModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::CHECK_BOX_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    ASSERT_NE(node, nullptr);
    /**
     * @tc.steps: step2. create checkbox paintProperty.
     */
    auto checkBoxPaintProperty = frameNode->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);

    /**
     * @tc.steps: step3. test SetCheckMarkWidth.
     * @tc.expected: step3. the property value meet expectations.
     */
    std::optional<Dimension> markWidth = std::nullopt;
    CheckBoxModelStatic::SetCheckMarkWidth(frameNode, markWidth);
    EXPECT_EQ(checkBoxPaintProperty->GetCheckBoxCheckMarkWidth(), std::nullopt);
    markWidth = CHECK_MARK_WIDTH;
    CheckBoxModelStatic::SetCheckMarkWidth(frameNode, markWidth);
    EXPECT_EQ(checkBoxPaintProperty->GetCheckBoxCheckMarkWidth(), CHECK_MARK_WIDTH);
}

/**
 * @tc.name: CheckboxStaticTestNgt007
 * @tc.desc: test checkbox SetCheckboxStyle.
 * @tc.type: FUNC
 */
HWTEST_F(CheckboxStaticTestNg, CheckboxStaticTestNg007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create checkbox frameNode.
     */
    auto node = CheckBoxModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::CHECK_BOX_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    ASSERT_NE(node, nullptr);
    /**
     * @tc.steps: step2. create checkbox paintProperty.
     */
    auto checkBoxPaintProperty = frameNode->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);

    /**
     * @tc.steps: step3. test SetCheckboxStyle.
     * @tc.expected: step3. the property value meet expectations.
     */
    std::optional<CheckBoxStyle> checkboxStyle = std::nullopt;
    CheckBoxModelStatic::SetCheckboxStyle(frameNode, checkboxStyle);
    EXPECT_EQ(checkBoxPaintProperty->GetCheckBoxSelectedStyle(), std::nullopt);
    checkboxStyle = std::make_optional(CheckBoxStyle::SQUARE_STYLE);
    CheckBoxModelStatic::SetCheckboxStyle(frameNode, checkboxStyle);
    EXPECT_EQ(checkBoxPaintProperty->GetCheckBoxSelectedStyleValue(), CheckBoxStyle::SQUARE_STYLE);
}
} // namespace OHOS::Ace::NG
