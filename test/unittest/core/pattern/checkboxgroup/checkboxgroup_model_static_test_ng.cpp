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

#include <optional>
#include <string>
#include <utility>

#include "gtest/gtest.h"

// Add the following two macro definitions to test the private and protected method.
#define private public
#define protected public
#include "test/mock/base/mock_system_properties.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/rosen/mock_canvas.h"

#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "core/components/checkable/checkable_component.h"
#include "core/components/checkable/checkable_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/checkbox/checkbox_model.h"
#include "core/components_ng/pattern/checkbox/checkbox_model_ng.h"
#include "core/components_ng/pattern/checkbox/checkbox_paint_property.h"
#include "core/components_ng/pattern/checkbox/checkbox_pattern.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_model_ng.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_model_static.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_paint_method.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_paint_property.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_pattern.h"
#include "core/components_ng/pattern/radio/radio_modifier.h"
#include "core/components_ng/pattern/stage/page_event_hub.h"
#include "core/components_ng/render/drawing_mock.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/event/key_event.h"
#include "core/event/touch_event.h"
#include "core/pipeline/base/render_node.h"
#include "core/pipeline_ng/pipeline_context.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const bool SELECTED = true;
const Color SELECTED_COLOR = Color::BLUE;
const Color UNSELECTED_COLOR = Color::RED;
const Color CHECK_MARK_COLOR = Color::GREEN;
constexpr Dimension CHECK_MARK_SIZE = Dimension(10.0);
constexpr Dimension CHECK_MARK_WIDTH = Dimension(5.0);
} // namespace

class CheckboxGroupStaticTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void CheckboxGroupStaticTestNg::SetUpTestCase()
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
void CheckboxGroupStaticTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}
void CheckboxGroupStaticTestNg::SetUp() {}
void CheckboxGroupStaticTestNg::TearDown() {}

/**
 * @tc.name: CheckboxGroupStaticTestNg001
 * @tc.desc: test checkbox SetSelect.
 * @tc.type: FUNC
 */
HWTEST_F(CheckboxGroupStaticTestNg, CheckboxGroupStaticTestNg001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create checkbox frameNode.
     */
    auto node = CheckBoxGroupModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::CHECKBOXGROUP_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    ASSERT_NE(node, nullptr);
    /**
     * @tc.steps: step2. create checkboxgroup paintProperty.
     */
    auto paintProperty = frameNode->GetPaintProperty<CheckBoxGroupPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    /**
     * @tc.steps: step3. test SetSelectAll.
     * @tc.expected: step3. the property value meet expectations.
     */
    std::optional<bool> selectAllValue = std::nullopt;
    CheckBoxGroupModelStatic::SetSelectAll(frameNode, selectAllValue);
    EXPECT_EQ(paintProperty->GetCheckBoxGroupSelect(), std::nullopt);
    selectAllValue = SELECTED;
    CheckBoxGroupModelStatic::SetSelectAll(frameNode, selectAllValue);
    EXPECT_EQ(paintProperty->GetCheckBoxGroupSelect(), SELECTED);
}

/**
 * @tc.name: CheckboxGroupStaticTestNg002
 * @tc.desc: test checkboxgroup SetSelectedColor.
 * @tc.type: FUNC
 */
HWTEST_F(CheckboxGroupStaticTestNg, CheckboxGroupStaticTestNg002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create checkboxgroup frameNode.
     */
    auto node = CheckBoxGroupModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::CHECKBOXGROUP_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    ASSERT_NE(node, nullptr);
    /**
     * @tc.steps: step2. create checkboxgroup paintProperty.
     */
    auto paintProperty = frameNode->GetPaintProperty<CheckBoxGroupPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    /**
     * @tc.steps: step3. test SetSelectedColor.
     * @tc.expected: step3. the property value meet expectations.
     */
    std::optional<Color> selectColor = std::nullopt;
    CheckBoxGroupModelStatic::SetSelectedColor(frameNode, selectColor);
    EXPECT_EQ(paintProperty->GetCheckBoxGroupSelectedColor(), std::nullopt);
    selectColor = SELECTED_COLOR;
    CheckBoxGroupModelStatic::SetSelectedColor(frameNode, selectColor);
    EXPECT_EQ(paintProperty->GetCheckBoxGroupSelectedColor(), SELECTED_COLOR);
}

/**
 * @tc.name: CheckboxGroupStaticTestNg003
 * @tc.desc: test checkboxgroup SetUnSelectedColor.
 * @tc.type: FUNC
 */
HWTEST_F(CheckboxGroupStaticTestNg, CheckboxGroupStaticTestNg003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create checkboxgroup frameNode.
     */
    auto node = CheckBoxGroupModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::CHECKBOXGROUP_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    ASSERT_NE(node, nullptr);
    /**
     * @tc.steps: step2. create checkboxgroup paintProperty.
     */
    auto paintProperty = frameNode->GetPaintProperty<CheckBoxGroupPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    /**
     * @tc.steps: step3. test SetUnSelectedColor.
     * @tc.expected: step3. the property value meet expectations.
     */
    std::optional<Color> unSelectColor = std::nullopt;
    CheckBoxGroupModelStatic::SetUnSelectedColor(frameNode, unSelectColor);
    EXPECT_EQ(paintProperty->GetCheckBoxGroupUnSelectedColor(), std::nullopt);
    unSelectColor = UNSELECTED_COLOR;
    CheckBoxGroupModelStatic::SetUnSelectedColor(frameNode, unSelectColor);
    EXPECT_EQ(paintProperty->GetCheckBoxGroupUnSelectedColor(), UNSELECTED_COLOR);
}

/**
 * @tc.name: CheckboxGroupStaticTestNg004
 * @tc.desc: test checkboxgroup SetCheckMarkColor.
 * @tc.type: FUNC
 */
HWTEST_F(CheckboxGroupStaticTestNg, CheckboxGroupStaticTestNg004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create checkboxgroup frameNode.
     */
    auto node = CheckBoxGroupModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::CHECKBOXGROUP_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    ASSERT_NE(node, nullptr);
    /**
     * @tc.steps: step2. create checkboxgroup paintProperty.
     */
    auto paintProperty = frameNode->GetPaintProperty<CheckBoxGroupPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    /**
     * @tc.steps: step3. test SetCheckMarkColor.
     * @tc.expected: step3. the property value meet expectations.
     */
    std::optional<Color> markColor = std::nullopt;
    CheckBoxGroupModelStatic::SetCheckMarkColor(frameNode, markColor);
    EXPECT_EQ(paintProperty->GetCheckBoxGroupCheckMarkColor(), std::nullopt);
    markColor = CHECK_MARK_COLOR;
    CheckBoxGroupModelStatic::SetCheckMarkColor(frameNode, markColor);
    EXPECT_EQ(paintProperty->GetCheckBoxGroupCheckMarkColor(), CHECK_MARK_COLOR);
}

/**
 * @tc.name: CheckboxGroupStaticTestNg005
 * @tc.desc: test checkboxgroup SetCheckMarkSize.
 * @tc.type: FUNC
 */
HWTEST_F(CheckboxGroupStaticTestNg, CheckboxGroupStaticTestNg005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create checkboxgroup frameNode.
     */
    auto node = CheckBoxGroupModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::CHECKBOXGROUP_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    ASSERT_NE(node, nullptr);
    /**
     * @tc.steps: step2. create checkboxgroup paintProperty.
     */
    auto paintProperty = frameNode->GetPaintProperty<CheckBoxGroupPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    /**
     * @tc.steps: step3. test SetCheckMarkSize.
     * @tc.expected: step3. the property value meet expectations.
     */
    std::optional<Dimension> markSize = std::nullopt;
    CheckBoxGroupModelStatic::SetCheckMarkSize(frameNode, markSize);
    EXPECT_EQ(paintProperty->GetCheckBoxGroupCheckMarkSize(), std::nullopt);
    markSize = CHECK_MARK_SIZE;
    CheckBoxGroupModelStatic::SetCheckMarkSize(frameNode, markSize);
    EXPECT_EQ(paintProperty->GetCheckBoxGroupCheckMarkSize(), CHECK_MARK_SIZE);
}

/**
 * @tc.name: CheckboxGroupStaticTestNg006
 * @tc.desc: test checkboxgroup SetCheckMarkWidth.
 * @tc.type: FUNC
 */
HWTEST_F(CheckboxGroupStaticTestNg, CheckboxGroupStaticTestNg006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create checkboxgroup frameNode.
     */
    auto node = CheckBoxGroupModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::CHECKBOXGROUP_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    ASSERT_NE(node, nullptr);
    /**
     * @tc.steps: step2. create checkboxgroup paintProperty.
     */
    auto paintProperty = frameNode->GetPaintProperty<CheckBoxGroupPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    /**
     * @tc.steps: step3. test SetCheckMarkWidth.
     * @tc.expected: step3. the property value meet expectations.
     */
    std::optional<Dimension> markWidth = std::nullopt;
    CheckBoxGroupModelStatic::SetCheckMarkWidth(frameNode, markWidth);
    EXPECT_EQ(paintProperty->GetCheckBoxGroupCheckMarkWidth(), std::nullopt);
    markWidth = CHECK_MARK_WIDTH;
    CheckBoxGroupModelStatic::SetCheckMarkWidth(frameNode, markWidth);
    EXPECT_EQ(paintProperty->GetCheckBoxGroupCheckMarkWidth(), CHECK_MARK_WIDTH);
}

/**
 * @tc.name: CheckboxGroupStaticTestNgt007
 * @tc.desc: test checkboxgroup SetCheckboxStyle.
 * @tc.type: FUNC
 */
HWTEST_F(CheckboxGroupStaticTestNg, CheckboxGroupStaticTestNg007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create checkboxgroup frameNode.
     */
    auto node = CheckBoxGroupModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::CHECKBOXGROUP_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    ASSERT_NE(node, nullptr);
    /**
     * @tc.steps: step2. create checkboxgroup paintProperty.
     */
    auto paintProperty = frameNode->GetPaintProperty<CheckBoxGroupPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    /**
     * @tc.steps: step3. test SetCheckboxStyle.
     * @tc.expected: step3. the property value meet expectations.
     */
    std::optional<CheckBoxStyle> checkboxStyle = std::nullopt;
    CheckBoxGroupModelStatic::SetCheckboxGroupStyle(frameNode, checkboxStyle);
    EXPECT_EQ(paintProperty->GetCheckBoxGroupSelectedStyle(), std::nullopt);
    checkboxStyle = std::make_optional(CheckBoxStyle::SQUARE_STYLE);
    CheckBoxGroupModelStatic::SetCheckboxGroupStyle(frameNode, checkboxStyle);
    EXPECT_EQ(paintProperty->GetCheckBoxGroupSelectedStyleValue(), CheckBoxStyle::SQUARE_STYLE);
}
} // namespace OHOS::Ace::NG
