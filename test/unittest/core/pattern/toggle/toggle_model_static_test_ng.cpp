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
#define protected public
#define private public
#include "base/geometry/dimension.h"
#include "core/components/checkable/checkable_theme.h"
#include "core/components/toggle/toggle_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/toggle_button_event_hub.h"
#include "core/components_ng/pattern/button/toggle_button_paint_property.h"
#include "core/components_ng/pattern/button/toggle_button_pattern.h"
#include "core/components_ng/pattern/checkbox/checkbox_event_hub.h"
#include "core/components_ng/pattern/checkbox/checkbox_paint_property.h"
#include "core/components_ng/pattern/checkbox/checkbox_pattern.h"
#include "core/components_ng/pattern/toggle/switch_event_hub.h"
#include "core/components_ng/pattern/toggle/switch_paint_method.h"
#include "core/components_ng/pattern/toggle/switch_paint_property.h"
#include "core/components_ng/pattern/toggle/switch_pattern.h"
#include "core/components_ng/pattern/toggle/toggle_model.h"
#include "core/components_ng/pattern/toggle/toggle_model_ng.h"
#include "core/components_ng/pattern/toggle/toggle_model_static.h"
#include "test/mock/base/mock_system_properties.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "core/components_ng/pattern/root/root_pattern.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const Color UNSELECTED_COLOR = Color::RED;
constexpr Dimension SWITCH_PONIT_RADIUS = Dimension(10.0);
constexpr Dimension SWITCH_TRACK_BORDER_RADIUS = Dimension(5.0);
} // namespace

class ToggleStaticTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();

protected:
    static PaddingPropertyF CreatePadding(Dimension length);
};

void ToggleStaticTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
}

void ToggleStaticTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: ToggleStaticTestNg001
 * @tc.desc: test toggle SetPointRadius.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleStaticTestNg, ToggleStaticTestNg001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toggle frameNode.
     */
    auto node =
        ToggleModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId(), NG::ToggleType::SWITCH, false);
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::TOGGLE_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. create toggle paintProperty.
     */
    auto togglePaintProperty = frameNode->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(togglePaintProperty, nullptr);

    /**
     * @tc.steps: step3. test SetPointRadius.
     * @tc.expected: step3. the property value meet expectations.
     */
    std::optional<Dimension> switchPointRadius = std::nullopt;
    ToggleModelStatic::SetPointRadius(frameNode, switchPointRadius);
    EXPECT_EQ(togglePaintProperty->GetPointRadius(), std::nullopt);
    switchPointRadius = SWITCH_PONIT_RADIUS;
    ToggleModelStatic::SetPointRadius(frameNode, switchPointRadius);
    EXPECT_EQ(togglePaintProperty->GetPointRadius(), SWITCH_PONIT_RADIUS);
}

/**
 * @tc.name: ToggleStaticTestNg002
 * @tc.desc: test toggle SetUnselectedColor.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleStaticTestNg, ToggleStaticTestNg002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toggle frameNode.
     */
    auto node =
        ToggleModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId(), NG::ToggleType::SWITCH, false);
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::TOGGLE_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. create toggle paintProperty.
     */
    auto togglePaintProperty = frameNode->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(togglePaintProperty, nullptr);

    /**
     * @tc.steps: step3. test SetUnselectedColor.
     * @tc.expected: step3. the property value meet expectations.
     */
    std::optional<Color> unSelectColor = std::nullopt;
    ToggleModelStatic::SetUnselectedColor(frameNode, unSelectColor);
    EXPECT_EQ(togglePaintProperty->GetUnselectedColor(), std::nullopt);
    unSelectColor = UNSELECTED_COLOR;
    ToggleModelStatic::SetUnselectedColor(frameNode, unSelectColor);
    EXPECT_EQ(togglePaintProperty->GetUnselectedColor(), UNSELECTED_COLOR);
}

/**
 * @tc.name: ToggleStaticTestNg003
 * @tc.desc: test toggle SetTrackBorderRadius.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleStaticTestNg, ToggleStaticTestNg003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toggle frameNode.
     */
    auto node =
        ToggleModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId(), NG::ToggleType::SWITCH, false);
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::TOGGLE_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. create toggle paintProperty.
     */
    auto togglePaintProperty = frameNode->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(togglePaintProperty, nullptr);

    /**
     * @tc.steps: step3. test SetTrackBorderRadius.
     * @tc.expected: step3. the property value meet expectations.
     */
    std::optional<Dimension> trackBorderRadius = std::nullopt;
    ToggleModelStatic::SetTrackBorderRadius(frameNode, trackBorderRadius);
    EXPECT_EQ(togglePaintProperty->GetTrackBorderRadius(), std::nullopt);
    trackBorderRadius = SWITCH_TRACK_BORDER_RADIUS;
    ToggleModelStatic::SetTrackBorderRadius(frameNode, trackBorderRadius);
    EXPECT_EQ(togglePaintProperty->GetTrackBorderRadius(), SWITCH_TRACK_BORDER_RADIUS);
}

/**
 * @tc.name: ToggleStaticTestNg004
 * @tc.desc: test toggle CreateFrameNode and OnChangeEvent with type switch.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleStaticTestNg, ToggleStaticTestNg004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toggle frameNode.
     */
    auto node = ToggleModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId(),
                                                   NG::ToggleType::SWITCH);
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::TOGGLE_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. create toggle paintProperty.
     */
    auto togglePaintProperty = frameNode->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(togglePaintProperty, nullptr);

    /**
     * @tc.steps: step3. test OnChangeEvent.
     * @tc.expected: step3. the property value meet expectations.
     */
    bool isChecked = false;
    auto onChange = [&isChecked](bool select) { isChecked = select; };
    ToggleModelStatic::OnChangeEvent(frameNode, std::move(onChange));
    auto eventHub = frameNode->GetEventHub<SwitchEventHub>();
    ASSERT_NE(eventHub, nullptr);
    EXPECT_NE(eventHub->onChangeEvent_, nullptr);
}

/**
 * @tc.name: ToggleStaticTestNg005
 * @tc.desc: test toggle CreateFrameNode and OnChangeEvent with type button.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleStaticTestNg, ToggleStaticTestNg005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toggle frameNode.
     */
    auto node = ToggleModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId(),
                                                   NG::ToggleType::BUTTON);
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::TOGGLE_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. create toggle paintProperty.
     */
    auto togglePaintProperty = frameNode->GetPaintProperty<ToggleButtonPaintProperty>();
    ASSERT_NE(togglePaintProperty, nullptr);

    /**
     * @tc.steps: step3. test OnChangeEvent.
     * @tc.expected: step3. the property value meet expectations.
     */
    bool isChecked = false;
    auto onChange = [&isChecked](bool select) { isChecked = select; };
    ToggleModelStatic::OnChangeEvent(frameNode, std::move(onChange));
    auto eventHub = frameNode->GetEventHub<ToggleButtonEventHub>();
    ASSERT_NE(eventHub, nullptr);
    EXPECT_NE(eventHub->onChangeEvent_, nullptr);
    eventHub->UpdateChangeEvent(true);
    EXPECT_EQ(isChecked, true);
}

/**
 * @tc.name: ToggleStaticTestNg006
 * @tc.desc: test toggle CreateFrameNode and OnChangeEvent with type checkbox.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleStaticTestNg, ToggleStaticTestNg006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toggle frameNode.
     */
    auto node = ToggleModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId(),
                                                   NG::ToggleType::CHECKBOX);
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::TOGGLE_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. create toggle paintProperty.
     */
    auto togglePaintProperty = frameNode->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(togglePaintProperty, nullptr);

    /**
     * @tc.steps: step3. test OnChangeEvent.
     */
    bool isChecked = false;
    auto onChange = [&isChecked](bool select) { isChecked = select; };
    ToggleModelStatic::OnChangeEvent(frameNode, std::move(onChange));
    auto eventHub = frameNode->GetEventHub<CheckBoxEventHub>();
    ASSERT_NE(eventHub, nullptr);
    EXPECT_NE(eventHub->selectChangeEvent_, nullptr);
}

/**
 * @tc.name: ToggleStaticTestNg007
 * @tc.desc: test toggle TriggerChange with type switch.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleStaticTestNg, ToggleStaticTestNg007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toggle frameNode.
     */
    auto node =
        ToggleModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId(), NG::ToggleType::SWITCH, false);
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::TOGGLE_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. create toggle paintProperty.
     */
    auto togglePaintProperty = frameNode->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(togglePaintProperty, nullptr);

    /**
     * @tc.steps: step3. test TriggerChange.
     */
    ToggleModelStatic::TriggerChange(frameNode, true);
    auto pattern = frameNode->GetPattern<SwitchPattern>();
    ASSERT_NE(pattern, nullptr);
}

/**
 * @tc.name: ToggleStaticTestNg008
 * @tc.desc: test toggle TriggerChange with type button.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleStaticTestNg, ToggleStaticTestNg008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toggle frameNode.
     */
    auto node =
        ToggleModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId(), NG::ToggleType::BUTTON, false);
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::TOGGLE_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. create toggle paintProperty.
     */
    auto togglePaintProperty = frameNode->GetPaintProperty<ToggleButtonPaintProperty>();
    ASSERT_NE(togglePaintProperty, nullptr);

    /**
     * @tc.steps: step3. test TriggerChange.
     */
    ToggleModelStatic::TriggerChange(frameNode, true);
    auto pattern = frameNode->GetPattern<ToggleButtonPattern>();
    ASSERT_NE(pattern, nullptr);
}

/**
 * @tc.name: ToggleStaticTestNg009
 * @tc.desc: test toggle TriggerChange with type checkbox.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleStaticTestNg, ToggleStaticTestNg009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toggle frameNode.
     */
    auto node = ToggleModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId(),
                                               NG::ToggleType::CHECKBOX, false);
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::TOGGLE_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. create toggle paintProperty.
     */
    auto togglePaintProperty = frameNode->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(togglePaintProperty, nullptr);

    /**
     * @tc.steps: step3. test TriggerChange.
     */
    ToggleModelStatic::TriggerChange(frameNode, true);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
}

} // namespace OHOS::Ace::NG
