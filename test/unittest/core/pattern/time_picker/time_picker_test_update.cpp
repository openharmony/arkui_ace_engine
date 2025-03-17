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
#include <functional>
#include <optional>
#include <utility>

#include "gtest/gtest-message.h"
#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/core/common/mock_container.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_theme_default.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/geometry/dimension.h"
#include "base/geometry/offset.h"
#include "base/geometry/point.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/animation/curves.h"
#include "core/components/common/properties/color.h"
#include "core/components/picker/picker_data.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/click_event.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/focus_hub.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/time_picker/timepicker_column_pattern.h"
#include "core/components_ng/pattern/time_picker/timepicker_dialog_view.h"
#include "core/components_ng/pattern/time_picker/timepicker_model_ng.h"
#include "core/components_ng/pattern/time_picker/timepicker_row_pattern.h"
#include "core/components_ng/pattern/time_picker/toss_animation_controller.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/event/key_event.h"
#include "core/event/touch_event.h"
#include "core/gestures/gesture_info.h"
#include "bridge/common/utils/utils.h"
#include "core/components/common/properties/shadow_config.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const int HALF_VALUE = 2;
const int SHOW_COUNT = 7;
const Dimension FONT_VALUE_VP = 4.0_vp;
const Dimension FONT_VALUE_NOMARL = Dimension(10);
const double CURRENT_YOFFSET1 = -200.f;
const double CURRENT_YOFFSET2 = 200.f;
const double DEFAULT_YOFFSET1 = 1.f;
const double NEXT_DISTANCE = 7.f;
const double PREVIOUS_DISTANCE = 5.f;

RefPtr<Theme> GetTheme(ThemeType type)
{
    if (type == IconTheme::TypeId()) {
        return AceType::MakeRefPtr<IconTheme>();
    } else if (type == DialogTheme::TypeId()) {
        return AceType::MakeRefPtr<DialogTheme>();
    } else if (type == PickerTheme::TypeId()) {
        return MockThemeDefault::GetPickerTheme();
    } else if (type == ButtonTheme::TypeId()) {
        return AceType::MakeRefPtr<ButtonTheme>();
    } else {
        return nullptr;
    }
}
} // namespace
class TimePickerPatternTestUpdate : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void CreateTimePickerColumnNode();

    RefPtr<FrameNode> columnNode_;
    RefPtr<TimePickerColumnPattern> columnPattern_;
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

void TimePickerPatternTestUpdate::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void TimePickerPatternTestUpdate::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void TimePickerPatternTestUpdate::SetUp()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        return GetTheme(type);
    });
    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([](ThemeType type, int32_t themeScopeId) -> RefPtr<Theme> { return GetTheme(type); });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void TimePickerPatternTestUpdate::TearDown()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    ViewStackProcessor::GetInstance()->ClearStack();
}

void TimePickerPatternTestUpdate::CreateTimePickerColumnNode()
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto pickerFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(pickerFrameNode, nullptr);
    pickerFrameNode->MarkModifyDone();

    auto timePickerRowPattern = pickerFrameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    columnNode_ = allChildNode["minute"].Upgrade();
    ASSERT_NE(columnNode_, nullptr);
    columnPattern_ = columnNode_->GetPattern<TimePickerColumnPattern>();
    ASSERT_NE(columnPattern_, nullptr);
    columnPattern_->SetShowCount(SHOW_COUNT);
    columnPattern_->OnAttachToFrameNode();
    auto host = timePickerRowPattern->GetHost();
    EXPECT_NE(host, nullptr);
}
/**
 * @tc.name: TimePickerDialogView002
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestUpdate, TimePickerDialogView002, TestSize.Level1)
{
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    ButtonInfo info2;
    ButtonInfo info3;
    info1.fontWeight = FontWeight::W100;
    info2.fontWeight = FontWeight::W200;
    info3.fontWeight = FontWeight::W400;
    
    buttonInfos.push_back(info1);
    buttonInfos.push_back(info2);
    buttonInfos.push_back(info3);

    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    CHECK_NULL_VOID(buttonNode);
    auto layoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    auto renderContext = buttonNode->GetRenderContext();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto buttonTheme = AceType::MakeRefPtr<ButtonTheme>();
    ASSERT_NE(buttonTheme, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(buttonTheme));

    size_t sizet = 0;
    TimePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval = layoutProperty->GetFontWeightValue();
    EXPECT_EQ(testval, FontWeight::W100);
    sizet++;
    TimePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval2 = layoutProperty->GetFontWeightValue();
    EXPECT_EQ(testval2, FontWeight::W200);
    sizet++;
    TimePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval3 = layoutProperty->GetFontWeightValue();
    EXPECT_EQ(testval3, FontWeight::W400);
}
/**
 * @tc.name: TimePickerDialogView003
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestUpdate, TimePickerDialogView003, TestSize.Level1)
{
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontSize = Dimension(100);
    buttonInfos.push_back(info1);

    size_t sizet = 0;

    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    CHECK_NULL_VOID(buttonNode);
    auto layoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    
    auto renderContext = buttonNode->GetRenderContext();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto buttonTheme = AceType::MakeRefPtr<ButtonTheme>();
    ASSERT_NE(buttonTheme, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(buttonTheme));
    TimePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval = layoutProperty->GetFontSizeValue();
    EXPECT_EQ(testval, Dimension(100));
}

/**
 * @tc.name: TimePickerDialogView004
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestUpdate, TimePickerDialogView004, TestSize.Level1)
{
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontColor = Color::BLACK;
    buttonInfos.push_back(info1);

    size_t sizet = 0;

    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    CHECK_NULL_VOID(buttonNode);
    auto layoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    
    auto renderContext = buttonNode->GetRenderContext();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto buttonTheme = AceType::MakeRefPtr<ButtonTheme>();
    ASSERT_NE(buttonTheme, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(buttonTheme));
    TimePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);

    auto testval = layoutProperty->GetFontColorValue();
    EXPECT_EQ(testval, Color::BLACK);
}

/**
 * @tc.name: TimePickerDialogView005
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestUpdate, TimePickerDialogView005, TestSize.Level1)
{
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontStyle = Ace::FontStyle::ITALIC;
    buttonInfos.push_back(info1);

    size_t sizet = 0;

    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    CHECK_NULL_VOID(buttonNode);
    auto layoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    
    auto renderContext = buttonNode->GetRenderContext();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto buttonTheme = AceType::MakeRefPtr<ButtonTheme>();
    ASSERT_NE(buttonTheme, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(buttonTheme));

    TimePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    
    auto testval = layoutProperty->GetFontStyleValue();
    EXPECT_EQ(testval, Ace::FontStyle::ITALIC);
}

/**
 * @tc.name: TimePickerDialogView006
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestUpdate, TimePickerDialogView006, TestSize.Level1)
{
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.type = std::make_optional<ButtonType>(ButtonType::CIRCLE);
    buttonInfos.push_back(info1);

    size_t sizet = 0;

    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    CHECK_NULL_VOID(buttonNode);
    auto layoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    
    auto renderContext = buttonNode->GetRenderContext();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto buttonTheme = AceType::MakeRefPtr<ButtonTheme>();
    ASSERT_NE(buttonTheme, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(buttonTheme));

    TimePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    
    auto testval = layoutProperty->GetTypeValue();
    EXPECT_EQ(testval, ButtonType::CIRCLE);
}

/**
 * @tc.name: TimePickerDialogView007
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestUpdate, TimePickerDialogView007, TestSize.Level1)
{
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.buttonStyle = ButtonStyleMode::EMPHASIZE;
    buttonInfos.push_back(info1);

    size_t sizet = 0;

    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    CHECK_NULL_VOID(buttonNode);
    auto layoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    
    auto renderContext = buttonNode->GetRenderContext();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto buttonTheme = AceType::MakeRefPtr<ButtonTheme>();
    ASSERT_NE(buttonTheme, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(buttonTheme));

    TimePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    
    auto testval = layoutProperty->GetButtonStyleValue();
    EXPECT_EQ(testval, ButtonStyleMode::EMPHASIZE);
}

/**
 * @tc.name: TimePickerDialogView008
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestUpdate, TimePickerDialogView008, TestSize.Level1)
{
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.role = ButtonRole::ERROR;
    buttonInfos.push_back(info1);

    size_t sizet = 0;

    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    CHECK_NULL_VOID(buttonNode);
    auto layoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    
    auto renderContext = buttonNode->GetRenderContext();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto buttonTheme = AceType::MakeRefPtr<ButtonTheme>();
    ASSERT_NE(buttonTheme, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(buttonTheme));

    TimePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    
    auto testval = layoutProperty->GetButtonRoleValue();
    EXPECT_EQ(testval, ButtonRole::ERROR);
}

/**
 * @tc.name: TimePickerDialogView009
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestUpdate, TimePickerDialogView009, TestSize.Level1)
{
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    ButtonInfo info2;
    info1.role = ButtonRole::ERROR;
    info2.role = ButtonRole::NORMAL;
    buttonInfos.push_back(info1);
    buttonInfos.push_back(info2);

    size_t sizet = 0;

    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    CHECK_NULL_VOID(buttonNode);
    auto layoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    
    auto renderContext = buttonNode->GetRenderContext();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto buttonTheme = AceType::MakeRefPtr<ButtonTheme>();
    ASSERT_NE(buttonTheme, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(buttonTheme));

    TimePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval = layoutProperty->GetButtonRoleValue();
    EXPECT_EQ(testval, ButtonRole::ERROR);
    
    sizet++;
    TimePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval2 = layoutProperty->GetButtonRoleValue();
    EXPECT_EQ(testval2, ButtonRole::NORMAL);
}

/**
 * @tc.name: TimePickerDialogView010
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestUpdate, TimePickerDialogView010, TestSize.Level1)
{
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    ButtonInfo info2;
    info1.buttonStyle = ButtonStyleMode::EMPHASIZE;
    info2.buttonStyle = ButtonStyleMode::TEXT;
    buttonInfos.push_back(info1);
    buttonInfos.push_back(info2);

    size_t sizet = 0;

    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    CHECK_NULL_VOID(buttonNode);
    auto layoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    
    auto renderContext = buttonNode->GetRenderContext();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto buttonTheme = AceType::MakeRefPtr<ButtonTheme>();
    ASSERT_NE(buttonTheme, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(buttonTheme));

    TimePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval = layoutProperty->GetButtonStyleValue();
    EXPECT_EQ(testval, ButtonStyleMode::EMPHASIZE);
    
    sizet++;
    TimePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval2 = layoutProperty->GetButtonStyleValue();
    EXPECT_EQ(testval2, ButtonStyleMode::TEXT);
}

/**
 * @tc.name: TimePickerDialogView011
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestUpdate, TimePickerDialogView011, TestSize.Level1)
{
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    ButtonInfo info2;
    info1.type = std::make_optional<ButtonType>(ButtonType::CIRCLE);
    info2.type = std::make_optional<ButtonType>(ButtonType::CAPSULE);
    buttonInfos.push_back(info1);
    buttonInfos.push_back(info2);

    size_t sizet = 0;

    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    CHECK_NULL_VOID(buttonNode);
    auto layoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    
    auto renderContext = buttonNode->GetRenderContext();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto buttonTheme = AceType::MakeRefPtr<ButtonTheme>();
    ASSERT_NE(buttonTheme, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(buttonTheme));

    TimePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    
    auto testval = layoutProperty->GetTypeValue();
    EXPECT_EQ(testval, ButtonType::CIRCLE);

    sizet++;
    TimePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    
    auto testval2 = layoutProperty->GetTypeValue();
    EXPECT_EQ(testval2, ButtonType::CAPSULE);
}

/**
 * @tc.name: TimePickerDialogView012
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestUpdate, TimePickerDialogView012, TestSize.Level1)
{
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    ButtonInfo info2;
    info1.fontStyle = Ace::FontStyle::ITALIC;
    info2.fontStyle = Ace::FontStyle::NONE;
    buttonInfos.push_back(info1);
    buttonInfos.push_back(info2);

    size_t sizet = 0;

    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    CHECK_NULL_VOID(buttonNode);
    auto layoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    
    auto renderContext = buttonNode->GetRenderContext();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto buttonTheme = AceType::MakeRefPtr<ButtonTheme>();
    ASSERT_NE(buttonTheme, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(buttonTheme));

    TimePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    
    auto testval = layoutProperty->GetFontStyleValue();
    EXPECT_EQ(testval, Ace::FontStyle::ITALIC);

    sizet++;
    TimePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    
    auto testval2 = layoutProperty->GetFontStyleValue();
    EXPECT_EQ(testval2, Ace::FontStyle::NONE);
}

/**
 * @tc.name: TimePickerDialogView013
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestUpdate, TimePickerDialogView013, TestSize.Level1)
{
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontStyle = Ace::FontStyle::ITALIC;
    info1.fontWeight = FontWeight::W500;
    info1.fontColor = Color::BLACK;
    buttonInfos.push_back(info1);

    size_t sizet = 0;

    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    CHECK_NULL_VOID(buttonNode);
    auto layoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    
    auto renderContext = buttonNode->GetRenderContext();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto buttonTheme = AceType::MakeRefPtr<ButtonTheme>();
    ASSERT_NE(buttonTheme, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(buttonTheme));

    TimePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval = layoutProperty->GetFontStyleValue();
    EXPECT_EQ(testval, Ace::FontStyle::ITALIC);

    auto testval2 = layoutProperty->GetFontWeightValue();
    EXPECT_EQ(testval2, FontWeight::W500);

    auto testval3 = layoutProperty->GetFontColorValue();
    EXPECT_EQ(testval3, Color::BLACK);
}

/**
 * @tc.name: TimePickerDialogView014
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestUpdate, TimePickerDialogView014, TestSize.Level1)
{
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.type = std::make_optional<ButtonType>(ButtonType::CIRCLE);
    info1.buttonStyle = ButtonStyleMode::EMPHASIZE;
    info1.role = ButtonRole::NORMAL;
    buttonInfos.push_back(info1);

    size_t sizet = 0;

    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    CHECK_NULL_VOID(buttonNode);
    auto layoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    
    auto renderContext = buttonNode->GetRenderContext();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto buttonTheme = AceType::MakeRefPtr<ButtonTheme>();
    ASSERT_NE(buttonTheme, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(buttonTheme));

    TimePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval = layoutProperty->GetTypeValue();
    EXPECT_EQ(testval, ButtonType::CIRCLE);

    auto testval2 = layoutProperty->GetButtonStyleValue();
    EXPECT_EQ(testval2, ButtonStyleMode::EMPHASIZE);

    auto testval3 = layoutProperty->GetButtonRoleValue();
    EXPECT_EQ(testval3, ButtonRole::NORMAL);
}
/**
 * @tc.name: TimePickerDialogView015
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestUpdate, TimePickerDialogView015, TestSize.Level1)
{
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    ButtonInfo info2;
    info1.fontSize = Dimension(5);
    info2.fontSize = Dimension(10);
    buttonInfos.push_back(info1);
    buttonInfos.push_back(info2);

    size_t sizet = 0;

    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    CHECK_NULL_VOID(buttonNode);
    auto layoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    
    auto renderContext = buttonNode->GetRenderContext();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto buttonTheme = AceType::MakeRefPtr<ButtonTheme>();
    ASSERT_NE(buttonTheme, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(buttonTheme));
    TimePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval = layoutProperty->GetFontSizeValue();
    EXPECT_EQ(testval, Dimension(5));

    sizet++;
    TimePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval2 = layoutProperty->GetFontSizeValue();
    EXPECT_EQ(testval2, Dimension(10));
}
/**
 * @tc.name: TimePickerDialogView016
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestUpdate, TimePickerDialogView016, TestSize.Level1)
{
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontSize = Dimension(100);
    buttonInfos.push_back(info1);
    size_t sizet = 0;

    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    CHECK_NULL_VOID(buttonNode);
    auto layoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    
    auto renderContext = buttonNode->GetRenderContext();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto buttonTheme = AceType::MakeRefPtr<ButtonTheme>();
    ASSERT_NE(buttonTheme, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(buttonTheme));

    TimePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval = layoutProperty->GetFontSizeValue();
    EXPECT_EQ(testval, Dimension(100));
}
/**
 * @tc.name: TimePickerDialogView017
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestUpdate, TimePickerDialogView017, TestSize.Level1)
{
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontSize = Dimension(1);
    buttonInfos.push_back(info1);
    size_t sizet = 0;

    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    CHECK_NULL_VOID(buttonNode);
    auto layoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    
    auto renderContext = buttonNode->GetRenderContext();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto buttonTheme = AceType::MakeRefPtr<ButtonTheme>();
    ASSERT_NE(buttonTheme, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(buttonTheme));

    TimePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval = layoutProperty->GetFontSizeValue();
    EXPECT_EQ(testval, Dimension(1));
}
/**
 * @tc.name: TimePickerDialogView018
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestUpdate, TimePickerDialogView018, TestSize.Level1)
{
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontSize = Dimension(0);
    buttonInfos.push_back(info1);
    size_t sizet = 0;

    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    CHECK_NULL_VOID(buttonNode);
    auto layoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    
    auto renderContext = buttonNode->GetRenderContext();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto buttonTheme = AceType::MakeRefPtr<ButtonTheme>();
    ASSERT_NE(buttonTheme, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(buttonTheme));

    TimePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval = layoutProperty->GetFontSizeValue();
    EXPECT_EQ(testval, Dimension(0));
}
/**
 * @tc.name: TimePickerDialogView019
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestUpdate, TimePickerDialogView019, TestSize.Level1)
{
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    ButtonInfo info2;
    info1.fontSize = Dimension(0);
    info2.fontSize = Dimension(1);
    buttonInfos.push_back(info1);
    buttonInfos.push_back(info2);
    size_t sizet = 0;

    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    CHECK_NULL_VOID(buttonNode);
    auto layoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    
    auto renderContext = buttonNode->GetRenderContext();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto buttonTheme = AceType::MakeRefPtr<ButtonTheme>();
    ASSERT_NE(buttonTheme, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(buttonTheme));

    TimePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval = layoutProperty->GetFontSizeValue();
    EXPECT_EQ(testval, Dimension(0));

    sizet++;
    TimePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval2 = layoutProperty->GetFontSizeValue();
    EXPECT_EQ(testval2, Dimension(1));
}
/**
 * @tc.name: TimePickerDialogView020
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestUpdate, TimePickerDialogView020, TestSize.Level1)
{
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    ButtonInfo info2;
    info1.fontSize = Dimension(100);
    info2.fontSize = Dimension(0);
    buttonInfos.push_back(info1);
    buttonInfos.push_back(info2);
    size_t sizet = 0;

    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    CHECK_NULL_VOID(buttonNode);
    auto layoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    
    auto renderContext = buttonNode->GetRenderContext();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto buttonTheme = AceType::MakeRefPtr<ButtonTheme>();
    ASSERT_NE(buttonTheme, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(buttonTheme));

    TimePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval = layoutProperty->GetFontSizeValue();
    EXPECT_EQ(testval, Dimension(100));

    sizet++;
    TimePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval2 = layoutProperty->GetFontSizeValue();
    EXPECT_EQ(testval2, Dimension(0));
}
/**
 * @tc.name: TimePickerDialogView021
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestUpdate, TimePickerDialogView021, TestSize.Level1)
{
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    ButtonInfo info2;
    ButtonInfo info3;
    info1.fontSize = Dimension(0);
    info2.fontSize = Dimension(1);
    info3.fontSize = Dimension(100);
    buttonInfos.push_back(info1);
    buttonInfos.push_back(info2);
    buttonInfos.push_back(info3);
    size_t sizet = 0;

    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    CHECK_NULL_VOID(buttonNode);
    auto layoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    
    auto renderContext = buttonNode->GetRenderContext();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto buttonTheme = AceType::MakeRefPtr<ButtonTheme>();
    ASSERT_NE(buttonTheme, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(buttonTheme));

    TimePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval = layoutProperty->GetFontSizeValue();
    EXPECT_EQ(testval, Dimension(0));

    sizet++;
    TimePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval2 = layoutProperty->GetFontSizeValue();
    EXPECT_EQ(testval2, Dimension(1));

    sizet++;
    TimePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval3 = layoutProperty->GetFontSizeValue();
    EXPECT_EQ(testval3, Dimension(100));
}
/**
 * @tc.name: TimePickerDialogView022
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestUpdate, TimePickerDialogView022, TestSize.Level1)
{
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontSize = Dimension(0);
    info1.fontColor = Color::BLACK;
    buttonInfos.push_back(info1);
    size_t sizet = 0;

    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    CHECK_NULL_VOID(buttonNode);
    auto layoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    
    auto renderContext = buttonNode->GetRenderContext();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto buttonTheme = AceType::MakeRefPtr<ButtonTheme>();
    ASSERT_NE(buttonTheme, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(buttonTheme));

    TimePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval = layoutProperty->GetFontSizeValue();
    EXPECT_EQ(testval, Dimension(0));

    auto testval3 = layoutProperty->GetFontColorValue();
    EXPECT_EQ(testval3, Color::BLACK);
}
/**
 * @tc.name: TimePickerDialogView023
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestUpdate, TimePickerDialogView023, TestSize.Level1)
{
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontSize = Dimension(1);
    info1.fontColor = Color::GREEN;
    buttonInfos.push_back(info1);
    size_t sizet = 0;

    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    CHECK_NULL_VOID(buttonNode);
    auto layoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    
    auto renderContext = buttonNode->GetRenderContext();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto buttonTheme = AceType::MakeRefPtr<ButtonTheme>();
    ASSERT_NE(buttonTheme, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(buttonTheme));

    TimePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval = layoutProperty->GetFontSizeValue();
    EXPECT_EQ(testval, Dimension(1));
    
    auto testval3 = layoutProperty->GetFontColorValue();
    EXPECT_EQ(testval3, Color::GREEN);
}
/**
 * @tc.name: TimePickerDialogView024
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestUpdate, TimePickerDialogView024, TestSize.Level1)
{
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontSize = Dimension(100);
    info1.fontColor = Color::FOREGROUND;
    buttonInfos.push_back(info1);
    size_t sizet = 0;

    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    CHECK_NULL_VOID(buttonNode);
    auto layoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    
    auto renderContext = buttonNode->GetRenderContext();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto buttonTheme = AceType::MakeRefPtr<ButtonTheme>();
    ASSERT_NE(buttonTheme, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(buttonTheme));

    TimePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval = layoutProperty->GetFontSizeValue();
    EXPECT_EQ(testval, Dimension(100));
    
    auto testval3 = layoutProperty->GetFontColorValue();
    EXPECT_EQ(testval3, Color::FOREGROUND);
}
/**
 * @tc.name: TimePickerDialogView025
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestUpdate, TimePickerDialogView025, TestSize.Level1)
{
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    ButtonInfo info2;
    ButtonInfo info3;
    info1.fontSize = Dimension(100);
    info2.fontSize = Dimension(0);
    info3.fontSize = Dimension(1);
    buttonInfos.push_back(info1);
    buttonInfos.push_back(info2);
    buttonInfos.push_back(info3);
    size_t sizet = 0;

    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    CHECK_NULL_VOID(buttonNode);
    auto layoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    
    auto renderContext = buttonNode->GetRenderContext();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto buttonTheme = AceType::MakeRefPtr<ButtonTheme>();
    ASSERT_NE(buttonTheme, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(buttonTheme));

    TimePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval = layoutProperty->GetFontSizeValue();
    EXPECT_EQ(testval, Dimension(100));

    sizet++;
    TimePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval2 = layoutProperty->GetFontSizeValue();
    EXPECT_EQ(testval2, Dimension(0));

    sizet--;
    TimePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval3 = layoutProperty->GetFontSizeValue();
    EXPECT_EQ(testval3, Dimension(100));
}

/**
 * @tc.name: getRadius
 * @tc.desc: 提供TimePickerDialogView026用例使用
 * @tc.type: FUNC
 */
NG::BorderRadiusProperty getRadius()
{
    int calcvalue = 100;
    NG::BorderRadiusProperty radius;
    CalcDimension radiusCalc(calcvalue, static_cast<DimensionUnit>(1));
    radius.radiusTopLeft = radiusCalc;
    radius.radiusTopRight = radiusCalc;
    radius.radiusBottomLeft = radiusCalc;
    radius.radiusBottomRight = radiusCalc;
    radius.multiValued = true;
    return radius;
}

/**
 * @tc.name: TimePickerDialogView026
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestUpdate, TimePickerDialogView026, TestSize.Level1)
{
    uint32_t color = 0;
    Color colorVal = Color(color);
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    ButtonInfo info2;
    ButtonInfo info3;
    info1.fontSize = Dimension(100);
    info1.fontColor = Color::GREEN;
    info1.fontFamily = { "unknown" };
    info1.backgroundColor = colorVal;
    info1.borderRadius = getRadius();
    info2.fontSize = Dimension(0);
    info2.fontColor = Color::FOREGROUND;
    info3.fontSize = Dimension(1);
    info3.fontColor = Color::GRAY;
    buttonInfos.push_back(info1);
    buttonInfos.push_back(info2);
    buttonInfos.push_back(info3);
    size_t sizet = 0;
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    CHECK_NULL_VOID(buttonNode);

    auto layoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    auto renderContext = buttonNode->GetRenderContext();

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto buttonTheme = AceType::MakeRefPtr<ButtonTheme>();
    ASSERT_NE(buttonTheme, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(buttonTheme));

    TimePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval = layoutProperty->GetFontSizeValue();
    EXPECT_EQ(testval, Dimension(100));

    sizet++;
    TimePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval2 = layoutProperty->GetFontSizeValue();
    EXPECT_EQ(testval2, Dimension(0));

    sizet++;
    TimePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval3 = layoutProperty->GetFontSizeValue();
    EXPECT_EQ(testval3, Dimension(1));
}

/**
 * @tc.name: TimePickerDialogViewShow002
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestUpdate, TimePickerDialogViewShow002, TestSize.Level1)
{
    TimePickerSettingData settingData;
    settingData.properties.disappearTextStyle_.textColor = Color::GREEN;
    settingData.properties.disappearTextStyle_.fontSize = Dimension(1);
    settingData.properties.disappearTextStyle_.fontWeight = Ace::FontWeight::NORMAL;

    settingData.properties.normalTextStyle_.textColor = Color::GREEN;
    settingData.properties.normalTextStyle_.fontSize = Dimension(1);
    settingData.properties.normalTextStyle_.fontWeight = Ace::FontWeight::NORMAL;

    settingData.properties.selectedTextStyle_.textColor = Color::GREEN;
    settingData.properties.selectedTextStyle_.fontSize = Dimension(1);
    settingData.properties.normalTextStyle_.fontWeight = Ace::FontWeight::NORMAL;
    settingData.isUseMilitaryTime = true;

    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(2, 2, 2);

    DialogProperties dialogProperties;

    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;

    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.type = std::make_optional<ButtonType>(ButtonType::CAPSULE);
    buttonInfos.push_back(info1);

    auto dialogNode = TimePickerDialogView::Show(
        dialogProperties, settingData, buttonInfos, timePickerProperty, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
}

/**
 * @tc.name: TimePickerModelNGTest001
 * @tc.desc: Test TimePickerModelNG CreateFrameNode.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestUpdate, TimePickerModelNGTest001, TestSize.Level1)
{
    /**
     * @tc.step: step1. create timePickerModelNG.
     */
    CreateTimePickerColumnNode();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    TimePickerModelNG timePickerModelNG;
    /**
     * @tc.step: step1. create TimepickerNode.
     * @tc.expected: timePickerNode is not NULL.
     */
    auto timePickerNode = timePickerModelNG.CreateFrameNode(frameNode->GetId());
    EXPECT_NE(timePickerNode, nullptr);
}

/**
 * @tc.name: TimePickerModelNGTest002
 * @tc.desc: Test TimePickerModelNG SetTimePickerDialogShow.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestUpdate, TimePickerModelNGTest002, TestSize.Level1)
{
    /**
     * @tc.step: step1. create timePickerModelNG.
     */
    CreateTimePickerColumnNode();
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    auto pipeline = PipelineBase::GetCurrentContextSafely();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    TimePickerDialogModelNG timePickerDialogModelNG;

    PickerDialogInfo pickerDialog;
    NG::TimePickerSettingData settingData;
    std::function<void()> onCancel = []() {};
    std::function<void(const std::string&)> onAccept = [](const std::string&) {};
    std::function<void(const std::string&)> onChange = [](const std::string&) {};
    std::function<void(const std::string&)> onEnterSelectedArea = [](const std::string&) {};
    TimePickerDialogEvent timePickerDialogEvent;
    std::vector<ButtonInfo> buttonInfos;

    timePickerDialogModelNG.SetTimePickerDialogShow(pickerDialog, settingData, std::move(onCancel),
        std::move(onAccept), std::move(onChange), std::move(onEnterSelectedArea), timePickerDialogEvent, buttonInfos);
    ASSERT_NE(frameNode, nullptr);
}

/**
 * @tc.name: CreateFrameNode001
 * @tc.desc: Test TimePickerPatternTestUpdate CreateFrameNode.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestUpdate, CreateFrameNode001, TestSize.Level1)
{
    int32_t nodeId = 0;
    RefPtr<FrameNode> result = TimePickerModelNG::CreateFrameNode(nodeId);
    EXPECT_NE(result, nullptr);
    auto timePickerRowPattern = result->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->hourId_ = 1;
    timePickerRowPattern->minuteId_ = 1;
    TimePickerModelNG::CreateFrameNode(nodeId);
}

/**
 * @tc.name: SetDisappearTextStyle001
 * @tc.desc: Test TimePickerPatternTestUpdate SetDisappearTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestUpdate, SetDisappearTextStyle001, TestSize.Level1)
{
    std::string weight = "FontWeight.Medium";
    std::string fontFamily = "";
    std::string FORMAT_FONT = "%s|%s|%s";
    std::string fontSize = "20";
    std::string fontInfo =
        StringUtils::FormatString(FORMAT_FONT.c_str(), fontSize.c_str(), weight.c_str(), fontFamily.c_str());
    uint32_t color = 0;
    int32_t POS_0 = 0;
    const char delimiter = '|';
    int32_t style = 0;
    const std::vector<OHOS::Ace::FontStyle> FONT_STYLES = { OHOS::Ace::FontStyle::NORMAL,
        OHOS::Ace::FontStyle::ITALIC };
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    NG::PickerTextStyle textStyle;
    std::vector<std::string> res;
    std::string fontValues = std::string(fontInfo.c_str());
    StringUtils::StringSplitter(fontValues, delimiter, res);
    textStyle.fontSize = StringUtils::StringToCalcDimension(res[POS_0], false, DimensionUnit::FP);
    if (style >= 0 && style < static_cast<int32_t>(FONT_STYLES.size())) {
        textStyle.fontStyle = FONT_STYLES[style];
    } else {
        textStyle.fontStyle = FONT_STYLES[0];
    }
    textStyle.textColor = Color(color);
    TimePickerModelNG::SetDisappearTextStyle(frameNode, theme, textStyle);
}

/**
 * @tc.name: SetNormalTextStyle001
 * @tc.desc: Test TimePickerPatternTestUpdate SetNormalTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestUpdate, SetNormalTextStyle001, TestSize.Level1)
{
    std::string weight = "FontWeight.Medium";
    std::string fontFamily = "";
    std::string FORMAT_FONT = "%s|%s|%s";
    std::string fontSize = "20";
    std::string fontInfo =
        StringUtils::FormatString(FORMAT_FONT.c_str(), fontSize.c_str(), weight.c_str(), fontFamily.c_str());
    uint32_t color = 0;
    int32_t POS_0 = 0;
    const char delimiter = '|';
    int32_t style = 0;
    const std::vector<OHOS::Ace::FontStyle> FONT_STYLES = { OHOS::Ace::FontStyle::NORMAL,
        OHOS::Ace::FontStyle::ITALIC };
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    NG::PickerTextStyle textStyle;
    std::vector<std::string> res;
    std::string fontValues = std::string(fontInfo);
    StringUtils::StringSplitter(fontValues, delimiter, res);
    textStyle.fontSize = StringUtils::StringToCalcDimension(res[POS_0], false, DimensionUnit::FP);
    if (style >= 0 && style < static_cast<int32_t>(FONT_STYLES.size())) {
        textStyle.fontStyle = FONT_STYLES[style];
    } else {
        textStyle.fontStyle = FONT_STYLES[0];
    }
    textStyle.textColor = Color(color);
    TimePickerModelNG::SetNormalTextStyle(frameNode, theme, textStyle);
}

/**
 * @tc.name: SetNormalTextStyle002
 * @tc.desc: Test TimePickerPatternTestUpdate SetNormalTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestUpdate, SetNormalTextStyle002, TestSize.Level1)
{
    std::string weight = "FontWeight.Medium";
    std::string fontFamily = "";
    std::string FORMAT_FONT = "%s|%s|%s";
    std::string fontSize = "";
    std::string fontInfo =
        StringUtils::FormatString(FORMAT_FONT.c_str(), fontSize.c_str(), weight.c_str(), fontFamily.c_str());
    uint32_t color = 0;
    int32_t POS_0 = 0;
    const char delimiter = '|';
    int32_t style = 0;
    const std::vector<OHOS::Ace::FontStyle> FONT_STYLES = { OHOS::Ace::FontStyle::NORMAL,
        OHOS::Ace::FontStyle::ITALIC };
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    NG::PickerTextStyle textStyle;
    std::vector<std::string> res;
    std::string fontValues = std::string(fontInfo);
    StringUtils::StringSplitter(fontValues, delimiter, res);
    textStyle.fontSize = StringUtils::StringToCalcDimension(res[POS_0], false, DimensionUnit::FP);
    if (style >= 0 && style < static_cast<int32_t>(FONT_STYLES.size())) {
        textStyle.fontStyle = FONT_STYLES[style];
    } else {
        textStyle.fontStyle = FONT_STYLES[0];
    }
    textStyle.textColor = Color(color);
    TimePickerModelNG::SetNormalTextStyle(frameNode, theme, textStyle);
}

/**
 * @tc.name: SetSelectedTextStyle001
 * @tc.desc: Test TimePickerPatternTestUpdate SetSelectedTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestUpdate, SetSelectedTextStyle001, TestSize.Level1)
{
    std::string weight = "FontWeight.Medium";
    std::string fontFamily = "";
    std::string FORMAT_FONT = "%s|%s|%s";
    std::string fontSize = "20";
    std::string fontInfo =
        StringUtils::FormatString(FORMAT_FONT.c_str(), fontSize.c_str(), weight.c_str(), fontFamily.c_str());
    uint32_t color = 0;
    int32_t POS_0 = 0;
    const char delimiter = '|';
    int32_t style = 0;
    const std::vector<OHOS::Ace::FontStyle> FONT_STYLES = { OHOS::Ace::FontStyle::NORMAL,
        OHOS::Ace::FontStyle::ITALIC };
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    NG::PickerTextStyle textStyle;
    std::vector<std::string> res;
    std::string fontValues = std::string(fontInfo);
    StringUtils::StringSplitter(fontValues, delimiter, res);
    textStyle.fontSize = StringUtils::StringToCalcDimension(res[POS_0], false, DimensionUnit::FP);
    if (style >= 0 && style < static_cast<int32_t>(FONT_STYLES.size())) {
        textStyle.fontStyle = FONT_STYLES[style];
    } else {
        textStyle.fontStyle = FONT_STYLES[0];
    }
    textStyle.textColor = Color(color);
    TimePickerModelNG::SetSelectedTextStyle(frameNode, theme, textStyle);
}

/**
 * @tc.name: SetSelectedTextStyle002
 * @tc.desc: Test TimePickerPatternTestUpdate SetSelectedTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestUpdate, SetSelectedTextStyle002, TestSize.Level1)
{
    std::string weight = "FontWeight.Medium";
    std::string fontFamily = "";
    std::string FORMAT_FONT = "%s|%s|%s";
    std::string fontSize = "";
    std::string fontInfo =
        StringUtils::FormatString(FORMAT_FONT.c_str(), fontSize.c_str(), weight.c_str(), fontFamily.c_str());
    uint32_t color = 0;
    int32_t POS_0 = 0;
    const char delimiter = '|';
    int32_t style = 0;
    const std::vector<OHOS::Ace::FontStyle> FONT_STYLES = { OHOS::Ace::FontStyle::NORMAL,
        OHOS::Ace::FontStyle::ITALIC };
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    NG::PickerTextStyle textStyle;
    std::vector<std::string> res;
    std::string fontValues = std::string(fontInfo);
    StringUtils::StringSplitter(fontValues, delimiter, res);
    textStyle.fontSize = StringUtils::StringToCalcDimension(res[POS_0], false, DimensionUnit::FP);
    if (style >= 0 && style < static_cast<int32_t>(FONT_STYLES.size())) {
        textStyle.fontStyle = FONT_STYLES[style];
    } else {
        textStyle.fontStyle = FONT_STYLES[0];
    }
    textStyle.textColor = Color(color);
    TimePickerModelNG::SetSelectedTextStyle(frameNode, theme, textStyle);
}

/**
 * @tc.name: SetDateTimeOptions001
 * @tc.desc: Test TimePickerPatternTestUpdate SetDateTimeOptions.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestUpdate, SetDateTimeOptions001, TestSize.Level1)
{
    TimePickerModelNG timepickerModel;
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    ZeroPrefixType hideType = ZeroPrefixType::HIDE;
    ZeroPrefixType showType = ZeroPrefixType::SHOW;
    ZeroPrefixType offType = ZeroPrefixType::OFF;
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    timepickerModel.SetDateTimeOptions(frameNode, hideType, showType, hideType);
    EXPECT_FALSE(timePickerRowPattern->isDateTimeOptionUpdate_);
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->SetPrefixHour(showType);
    timePickerRowPattern->SetPrefixMinute(showType);
    timePickerRowPattern->SetPrefixSecond(showType);
    timepickerModel.SetDateTimeOptions(hideType, hideType, hideType);
    EXPECT_TRUE(timePickerRowPattern->isDateTimeOptionUpdate_);
    timepickerModel.SetDateTimeOptions(hideType, hideType, offType);
    EXPECT_TRUE(timePickerRowPattern->isDateTimeOptionUpdate_);
}

/**
 * @tc.name: GetSecondFormatString001
 * @tc.desc: Test TimePickerPatternTestUpdate GetSecondFormatString.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestUpdate, GetSecondFormatString001, TestSize.Level1)
{
    uint32_t second = 0;
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto pickerFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(pickerFrameNode, nullptr);
    pickerFrameNode->MarkModifyDone();

    auto timePickerRowPattern = pickerFrameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->GetSecondFormatString(second);
}

/**
 * @tc.name: OnAroundButtonClick001
 * @tc.desc: Test TimePickerPatternTestUpdate OnAroundButtonClick.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestUpdate, OnAroundButtonClick001, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto pickerFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(pickerFrameNode, nullptr);
    pickerFrameNode->MarkModifyDone();
    auto timePickerRowPattern = pickerFrameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    columnNode_ = allChildNode["minute"].Upgrade();
    ASSERT_NE(columnNode_, nullptr);
    columnPattern_ = columnNode_->GetPattern<TimePickerColumnPattern>();
    ASSERT_NE(columnPattern_, nullptr);
    auto host = timePickerRowPattern->GetHost();
    EXPECT_NE(host, nullptr);

    auto childSize = static_cast<int32_t>(host->GetChildren().size());
    for (int32_t i = 0; i < childSize; i++) {
        RefPtr<FrameNode> childNode = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(i));
        CHECK_NULL_VOID(childNode);

        RefPtr<TimePickerEventParam> param = AceType::MakeRefPtr<TimePickerEventParam>();
        param->instance_ = childNode;
        param->itemIndex_ = i;
        param->itemTotalCounts_ = childSize;
        columnPattern_->OnAroundButtonClick(param);
    }
}

/**
 * @tc.name: OnWindowHide001
 * @tc.desc: Test TimePickerPatternTestUpdate OnWindowHide.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestUpdate, OnWindowHide001, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto pickerFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(pickerFrameNode, nullptr);
    pickerFrameNode->MarkModifyDone();
    auto timePickerRowPattern = pickerFrameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    columnNode_ = allChildNode["minute"].Upgrade();
    ASSERT_NE(columnNode_, nullptr);
    columnPattern_ = columnNode_->GetPattern<TimePickerColumnPattern>();
    ASSERT_NE(columnPattern_, nullptr);

    columnPattern_->OnWindowHide();
}

/**
 * @tc.name: SetIsEnableHapticFeedback001
 * @tc.desc: Test TimePickerPatternTestUpdate SetIsEnableHapticFeedback.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestUpdate, SetIsEnableHapticFeedback001, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);

    bool isEnableHapticFeedback = true;
    TimePickerModelNG::GetInstance()->SetIsEnableHapticFeedback(isEnableHapticFeedback);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(TimePickerModelNG::getEnableHapticFeedback(frameNode), isEnableHapticFeedback);
}

/**
 * @tc.name: SetIsEnableHapticFeedback002
 * @tc.desc: Test TimePickerPatternTestUpdate SetIsEnableHapticFeedback.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestUpdate, SetIsEnableHapticFeedback002, TestSize.Level1)
{
    bool isEnableHapticFeedback = true;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    TimePickerModelNG::SetIsEnableHapticFeedback(frameNode, isEnableHapticFeedback);
    EXPECT_EQ(TimePickerModelNG::getEnableHapticFeedback(frameNode), isEnableHapticFeedback);
}

/**
 * @tc.name: GetCurrentTime001
 * @tc.desc: Test TimePickerPatternTestUpdate GetCurrentTime.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestUpdate, GetCurrentTime001, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto pickerFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(pickerFrameNode, nullptr);
    pickerFrameNode->MarkModifyDone();

    auto timePickerRowPattern = pickerFrameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->SetHasSecond(true);
    timePickerRowPattern->GetCurrentTime();
}
/**
 * @tc.name: TimePickerModelNGTest003
 * @tc.desc: Test TimePickerModelNG SetTimePickerDialogShow.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestUpdate, TimePickerModelNGTest003, TestSize.Level1)
{
    /**
     * @tc.step: step1. create timePickerModelNG.
     */
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(10);
    CreateTimePickerColumnNode();
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    TimePickerDialogModelNG timePickerDialogModelNG;

    PickerDialogInfo pickerDialog;
    NG::TimePickerSettingData settingData;
    std::function<void()> onCancel = []() {};
    std::function<void(const std::string&)> onAccept = [](const std::string&) {};
    std::function<void(const std::string&)> onChange = [](const std::string&) {};
    std::function<void(const std::string&)> onEnterSelectedArea = [](const std::string&) {};
    TimePickerDialogEvent timePickerDialogEvent;
    std::vector<ButtonInfo> buttonInfos;

    timePickerDialogModelNG.SetTimePickerDialogShow(pickerDialog, settingData, std::move(onCancel), std::move(onAccept),
        std::move(onChange), std::move(onEnterSelectedArea), timePickerDialogEvent, buttonInfos);
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
    ASSERT_NE(frameNode, nullptr);
    pickerDialog.alignment = DialogAlignment::CENTER;
    pickerDialog.backgroundColor = Color(100);
    pickerDialog.backgroundBlurStyle = 1;
    pickerDialog.shadow = ShadowConfig::DefaultShadowL;
    pickerDialog.offset = DimensionOffset(Offset(0, 1.0f));
    pickerDialog.isSelectedTime = true;
    timePickerDialogModelNG.SetTimePickerDialogShow(pickerDialog, settingData, std::move(onCancel), std::move(onAccept),
        std::move(onChange), std::move(onEnterSelectedArea), timePickerDialogEvent, buttonInfos);
    ASSERT_NE(frameNode, nullptr);
}
/**
 * @tc.name: TimePickerModelNGTest004
 * @tc.desc: Test TimePickerModelNG CreateTimePicker.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestUpdate, TimePickerModelNGTest004, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetFontScale(0);
    TimePickerModelNG timepickerModel;
    auto ret = timepickerModel.ConvertFontScaleValue(FONT_VALUE_NOMARL);
    EXPECT_EQ(ret, FONT_VALUE_NOMARL);

    pipeline->SetFontScale(10);
    ret = timepickerModel.ConvertFontScaleValue(FONT_VALUE_VP);
    EXPECT_EQ(ret, FONT_VALUE_VP);

    ret = timepickerModel.ConvertFontScaleValue(FONT_VALUE_NOMARL);
    EXPECT_EQ(ret, FONT_VALUE_NOMARL);
}
/**
 * @tc.name: TimePickerModelNGTest005
 * @tc.desc: Test TimePickerModelNG SetEnableCascade.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestUpdate, TimePickerModelNGTest005, TestSize.Level1)
{
    int32_t nodeId = 0;
    RefPtr<FrameNode> result = TimePickerModelNG::CreateFrameNode(nodeId);
    EXPECT_NE(result, nullptr);
    bool isEnableCascade = false;
    auto timePickerRowPattern = result->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->SetEnableCascade(isEnableCascade);
    bool ret = timePickerRowPattern->GetEnableCascade();
    EXPECT_EQ(ret, false);

    isEnableCascade = true;
    timePickerRowPattern->SetEnableCascade(isEnableCascade);
    ret = timePickerRowPattern->GetEnableCascade();
    EXPECT_EQ(ret, true);
}
/**
 * @tc.name: TimePickerModelNGTest006
 * @tc.desc: Test TimePickerModelNG SetStartTime and GetStartTime.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestUpdate, TimePickerModelNGTest006, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    PickerTime value { 0, 0, 0 };
    TimePickerModelNG::GetInstance()->SetStartTime(value);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    auto time = timePickerRowPattern->GetStartTime();
    EXPECT_EQ(time.hour_, 0);
    EXPECT_EQ(time.minute_, 0);
    EXPECT_EQ(time.second_, 0);

    PickerTime valuBoundary { 23, 59, 59 };
    TimePickerModelNG::GetInstance()->SetStartTime(valuBoundary);
    auto timeBoundary = timePickerRowPattern->GetStartTime();
    EXPECT_EQ(timeBoundary.hour_, 23);
    EXPECT_EQ(timeBoundary.minute_, 59);
    EXPECT_EQ(timeBoundary.second_, 59);

    PickerTime valuIllegal { 24, 61, 61 };
    TimePickerModelNG::GetInstance()->SetStartTime(valuIllegal);
    auto timeIllegal = timePickerRowPattern->GetStartTime();
    EXPECT_EQ(timeIllegal.hour_, 24);
    EXPECT_EQ(timeIllegal.minute_, 61);
    EXPECT_EQ(timeIllegal.second_, 61);
}
/**
 * @tc.name: TimePickerModelNGTest007
 * @tc.desc: Test TimePickerModelNG SetEndTime and GetEndTime.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestUpdate, TimePickerModelNGTest007, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    PickerTime value { 0, 0, 0 };
    TimePickerModelNG::GetInstance()->SetEndTime(value);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    auto time = timePickerRowPattern->GetEndTime();
    EXPECT_EQ(time.hour_, 0);
    EXPECT_EQ(time.minute_, 0);
    EXPECT_EQ(time.second_, 0);

    PickerTime valuBoundary { 23, 59, 59 };
    TimePickerModelNG::GetInstance()->SetEndTime(valuBoundary);
    auto timeBoundary = timePickerRowPattern->GetEndTime();
    EXPECT_EQ(timeBoundary.hour_, 23);
    EXPECT_EQ(timeBoundary.minute_, 59);
    EXPECT_EQ(timeBoundary.second_, 59);

    PickerTime valuIllegal { 24, 61, 61 };
    TimePickerModelNG::GetInstance()->SetEndTime(valuIllegal);
    auto timeIllegal = timePickerRowPattern->GetEndTime();
    EXPECT_EQ(timeIllegal.hour_, 24);
    EXPECT_EQ(timeIllegal.minute_, 61);
    EXPECT_EQ(timeIllegal.second_, 61);
}
/**
 * @tc.name: TimePickerModelNGTest008
 * @tc.desc: Test TimePickerModelNG SetStartTime and getTimepickerStart.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestUpdate, TimePickerModelNGTest008, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    PickerTime value { 0, 0, 0 };
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    TimePickerModelNG::SetStartTime(frameNode, value);
    auto time = TimePickerModelNG::getTimepickerStart(frameNode);

    EXPECT_EQ(time.hour_, 0);
    EXPECT_EQ(time.minute_, 0);
    EXPECT_EQ(time.second_, 0);

    PickerTime valuBoundary { 23, 59, 59 };
    TimePickerModelNG::SetStartTime(frameNode, valuBoundary);
    auto timeBoundary = TimePickerModelNG::getTimepickerStart(frameNode);
    EXPECT_EQ(timeBoundary.hour_, 23);
    EXPECT_EQ(timeBoundary.minute_, 59);
    EXPECT_EQ(timeBoundary.second_, 59);

    PickerTime valuIllegal { 24, 61, 61 };
    TimePickerModelNG::SetStartTime(frameNode, valuBoundary);
    auto timeIllegal = TimePickerModelNG::getTimepickerStart(frameNode);
    EXPECT_EQ(timeIllegal.hour_, 23);
    EXPECT_EQ(timeIllegal.minute_, 59);
    EXPECT_EQ(timeIllegal.second_, 59);
}
/**
 * @tc.name: TimePickerModelNGTest009
 * @tc.desc: Test TimePickerModelNG SetEndTime and getTimepickerEnd.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestUpdate, TimePickerModelNGTest009, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    PickerTime value { 0, 0, 0 };
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    TimePickerModelNG::SetEndTime(frameNode, value);
    auto time = TimePickerModelNG::getTimepickerEnd(frameNode);

    EXPECT_EQ(time.hour_, 0);
    EXPECT_EQ(time.minute_, 0);
    EXPECT_EQ(time.second_, 0);

    PickerTime valuBoundary { 23, 59, 59 };
    TimePickerModelNG::SetEndTime(frameNode, valuBoundary);
    auto timeBoundary = TimePickerModelNG::getTimepickerEnd(frameNode);
    EXPECT_EQ(timeBoundary.hour_, 23);
    EXPECT_EQ(timeBoundary.minute_, 59);
    EXPECT_EQ(timeBoundary.second_, 59);

    PickerTime valuIllegal { 24, 61, 61 };
    TimePickerModelNG::SetEndTime(frameNode, valuBoundary);
    auto timeIllegal = TimePickerModelNG::getTimepickerEnd(frameNode);
    EXPECT_EQ(timeIllegal.hour_, 23);
    EXPECT_EQ(timeIllegal.minute_, 59);
    EXPECT_EQ(timeIllegal.second_, 59);
}
/**
 * @tc.name: TimePickerModelNGTest010
 * @tc.desc: Test TimePickerModelNG ParseHourOf24.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestUpdate, TimePickerModelNGTest010, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    PickerTime value10 { 10, 40, 42 };
    auto hour = timePickerRowPattern->ParseHourOf24(value10.GetHour());
    EXPECT_EQ(hour, 10);
    PickerTime value23 { 23, 40, 42 };
    hour = timePickerRowPattern->ParseHourOf24(value23.GetHour());
    EXPECT_EQ(hour, 11);
}

/**
 * @tc.name: TimePickerColumnPattern001
 * @tc.desc: Test UpdateColumnChildPosition.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestUpdate, TimePickerColumnPattern001, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);

    /**
     * @tc.step: step1. create TimePicker's column pattern.
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto amPmColumn = allChildNode["amPm"].Upgrade();
    ASSERT_NE(amPmColumn, nullptr);
    auto amPmColumnPattern = amPmColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_NE(amPmColumnPattern, nullptr);
    amPmColumnPattern->SetCurrentIndex(0);
    EXPECT_TRUE(amPmColumnPattern->NotLoopOptions());

    auto host = amPmColumnPattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto options = amPmColumnPattern->GetOptions();
    auto totalOptionCount = options[host];
    EXPECT_EQ(totalOptionCount, HALF_VALUE);

    /**
     * @tc.step: step2. call UpdateColumnChildPosition, selected index is 0, not allow to slide down.
     * @tc.expected: yLast_ is CURRNET_YOFFSET2, offsetCurSet_ is DEFAULT_YOFFSET1, GetCurrentIndex is 0.
     */
    amPmColumnPattern->yOffset_ = 0.f;
    amPmColumnPattern->offsetCurSet_ = DEFAULT_YOFFSET1;
    amPmColumnPattern->yLast_ = DEFAULT_YOFFSET1;
    amPmColumnPattern->UpdateColumnChildPosition(CURRENT_YOFFSET2);

    EXPECT_EQ(amPmColumnPattern->yLast_, CURRENT_YOFFSET2);
    EXPECT_EQ(amPmColumnPattern->offsetCurSet_, DEFAULT_YOFFSET1);
    EXPECT_EQ(amPmColumnPattern->GetCurrentIndex(), 0);
}

/**
 * @tc.name: TimePickerColumnPattern002
 * @tc.desc: Test UpdateColumnChildPosition.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestUpdate, TimePickerColumnPattern002, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);

    /**
     * @tc.step: step1. create TimePicker's column pattern.
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto amPmColumn = allChildNode["amPm"].Upgrade();
    ASSERT_NE(amPmColumn, nullptr);
    auto amPmColumnPattern = amPmColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_NE(amPmColumnPattern, nullptr);
    amPmColumnPattern->SetCurrentIndex(0);
    EXPECT_TRUE(amPmColumnPattern->NotLoopOptions());

    auto host = amPmColumnPattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto options = amPmColumnPattern->GetOptions();
    auto totalOptionCount = options[host];
    EXPECT_EQ(totalOptionCount, HALF_VALUE);

    /**
     * @tc.step: step2. call UpdateColumnChildPosition, selected index is from 0 to 1 after sliding up.
     * @tc.expected: yOffset_ is 0.f, offsetCurSet_ is 0.f, GetCurrentIndex is 1.
     */
    auto midIndex = amPmColumnPattern->GetShowCount() / HALF_VALUE;
    amPmColumnPattern->optionProperties_[midIndex].prevDistance = PREVIOUS_DISTANCE;
    amPmColumnPattern->optionProperties_[midIndex].nextDistance = NEXT_DISTANCE;

    amPmColumnPattern->yLast_ = DEFAULT_YOFFSET1;
    amPmColumnPattern->yOffset_ = CURRENT_YOFFSET1;
    amPmColumnPattern->UpdateColumnChildPosition(CURRENT_YOFFSET1);

    EXPECT_EQ(amPmColumnPattern->yOffset_, 0.f);
    EXPECT_EQ(amPmColumnPattern->offsetCurSet_, 0.f);
    EXPECT_EQ(amPmColumnPattern->GetCurrentIndex(), 1);
}

/**
 * @tc.name: TimePickerUpdateButtonFocus001
 * @tc.desc: Test UpdateButtonDefaultFocus.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestUpdate, TimePickerUpdateButtonFocus001, TestSize.Level1)
{
    /**
     * @tc.step: step1. create TimePicker's button node.
     * @tc.expected: buttonNode is not null.
     */
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo buttonInfo;
    buttonInfo.text = "OK";
    buttonInfo.isPrimary = true;
    buttonInfo.isAcceptButton = true;
    buttonInfos.push_back(buttonInfo);

    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(buttonNode, nullptr);

    /**
     * @tc.step: step2. call UpdateButtonDefaultFocus, set buttonNode as default focus.
     * @tc.expected: focusHub is not default focus.
     */
    auto focusHub = buttonNode->GetOrCreateFocusHub();
    ASSERT_NE(buttonNode, nullptr);
    EXPECT_EQ(focusHub->IsDefaultFocus(), false);

    /**
     * @tc.step: step3. call UpdateButtonDefaultFocus, set buttonNode as default focus.
     * @tc.expected: focusHub is default focus.
     */
    TimePickerDialogView::UpdateButtonDefaultFocus(buttonInfos, buttonNode, true);
    focusHub = buttonNode->GetOrCreateFocusHub();
    ASSERT_NE(buttonNode, nullptr);
    EXPECT_EQ(focusHub->IsDefaultFocus(), true);
}
} // namespace OHOS::Ace::NG
