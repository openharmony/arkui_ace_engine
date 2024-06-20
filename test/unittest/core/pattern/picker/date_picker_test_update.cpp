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

#include <functional>
#include <optional>
#include <utility>

#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/core/common/mock_theme_default.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/rosen/mock_canvas.h"

#include "base/geometry/dimension.h"
#include "base/geometry/dimension_offset.h"
#include "base/geometry/point.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/system_properties.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/dialog/dialog_properties.h"
#include "core/components/picker/picker_data.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/input_event.h"
#include "core/components_ng/event/touch_event.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_view.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/picker/date_time_animation_controller.h"
#include "core/components_ng/pattern/picker/datepicker_column_pattern.h"
#include "core/components_ng/pattern/picker/datepicker_dialog_view.h"
#include "core/components_ng/pattern/picker/datepicker_model_ng.h"
#include "core/components_ng/pattern/picker/datepicker_pattern.h"
#include "core/components_ng/pattern/picker/picker_model.h"
#include "core/components_ng/pattern/picker/picker_type_define.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/event/ace_events.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class DatePickerTestUpdate : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void CreateDatePickerColumnNode();

    RefPtr<FrameNode> columnNode_;
    RefPtr<DatePickerColumnPattern> columnPattern_;
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

void DatePickerTestUpdate::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void DatePickerTestUpdate::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

void DatePickerTestUpdate::SetUp()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        if (type == IconTheme::TypeId()) {
            return AceType::MakeRefPtr<IconTheme>();
        } else if (type == DialogTheme::TypeId()) {
            return AceType::MakeRefPtr<DialogTheme>();
        } else if (type == PickerTheme::TypeId()) {
            return MockThemeDefault::GetPickerTheme();
        } else {
            return nullptr;
        }
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void DatePickerTestUpdate::TearDown()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    ViewStackProcessor::GetInstance()->ClearStack();
}

void DatePickerTestUpdate::CreateDatePickerColumnNode()
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();

    auto stackNode = AceType::DynamicCast<FrameNode>(frameNode->GetFirstChild());
    ASSERT_NE(stackNode, nullptr);
    auto blendNode = AceType::DynamicCast<FrameNode>(stackNode->GetLastChild());
    ASSERT_NE(blendNode, nullptr);
    columnNode_ = AceType::DynamicCast<FrameNode>(blendNode->GetLastChild());
    ASSERT_NE(columnNode_, nullptr);
    columnNode_->MarkModifyDone();
    columnPattern_ = columnNode_->GetPattern<DatePickerColumnPattern>();
    ASSERT_NE(columnPattern_, nullptr);
    columnPattern_->OnAttachToFrameNode();
}
/**
 * @tc.name: DataPickerDialogViewUpdateButtonStyles002
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestUpdate, DataPickerDialogViewUpdateButtonStyles002, TestSize.Level1)
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
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
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

    size_t sizet = 0;
    DatePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval = layoutProperty->GetFontWeightValue();
    EXPECT_EQ(testval, FontWeight::W100);
    sizet++;
    DatePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval2 = layoutProperty->GetFontWeightValue();
    EXPECT_EQ(testval2, FontWeight::W200);
    sizet++;
    DatePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval3 = layoutProperty->GetFontWeightValue();
    EXPECT_EQ(testval3, FontWeight::W400);
}

/**
 * @tc.name: DataPickerDialogViewUpdateButtonStyles003
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestUpdate, DataPickerDialogViewUpdateButtonStyles003, TestSize.Level1)
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
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
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
    DatePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval = layoutProperty->GetFontSizeValue();
    EXPECT_EQ(testval, Dimension(100));
}

/**
 * @tc.name: DataPickerDialogViewUpdateButtonStyles004
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestUpdate, DataPickerDialogViewUpdateButtonStyles004, TestSize.Level1)
{
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontColor = std::make_optional<Color>(Color::BLACK);
    buttonInfos.push_back(info1);

    size_t sizet = 0;

    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
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
    DatePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);

    auto testval = layoutProperty->GetFontColorValue();
    EXPECT_EQ(testval, Color::BLACK);
}

/**
 * @tc.name: DataPickerDialogViewUpdateButtonStyles005
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestUpdate, DataPickerDialogViewUpdateButtonStyles005, TestSize.Level1)
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
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
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

    DatePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    
    auto testval = layoutProperty->GetFontStyleValue();
    EXPECT_EQ(testval, Ace::FontStyle::ITALIC);
}

/**
 * @tc.name: DataPickerDialogViewUpdateButtonStyles006
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestUpdate, DataPickerDialogViewUpdateButtonStyles006, TestSize.Level1)
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
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
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

    DatePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    
    auto testval = layoutProperty->GetTypeValue();
    EXPECT_EQ(testval, ButtonType::CIRCLE);
}

/**
 * @tc.name: DataPickerDialogViewUpdateButtonStyles007
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestUpdate, DataPickerDialogViewUpdateButtonStyles007, TestSize.Level1)
{
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.buttonStyle = std::make_optional<ButtonStyleMode>(ButtonStyleMode::EMPHASIZE);
    buttonInfos.push_back(info1);

    size_t sizet = 0;

    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
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

    DatePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    
    auto testval = layoutProperty->GetButtonStyleValue();
    EXPECT_EQ(testval, ButtonStyleMode::EMPHASIZE);
}

/**
 * @tc.name: DataPickerDialogViewUpdateButtonStyles008
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestUpdate, DataPickerDialogViewUpdateButtonStyles008, TestSize.Level1)
{
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.role = std::make_optional<ButtonRole>(ButtonRole::ERROR);
    buttonInfos.push_back(info1);

    size_t sizet = 0;

    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
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

    DatePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    
    auto testval = layoutProperty->GetButtonRoleValue();
    EXPECT_EQ(testval, ButtonRole::ERROR);
}

/**
 * @tc.name: DataPickerDialogViewUpdateButtonStyles009
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestUpdate, DataPickerDialogViewUpdateButtonStyles009, TestSize.Level1)
{
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    ButtonInfo info2;
    info1.role = std::make_optional<ButtonRole>(ButtonRole::ERROR);
    info2.role = std::make_optional<ButtonRole>(ButtonRole::NORMAL);
    buttonInfos.push_back(info1);
    buttonInfos.push_back(info2);

    size_t sizet = 0;

    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
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

    DatePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval = layoutProperty->GetButtonRoleValue();
    EXPECT_EQ(testval, ButtonRole::ERROR);
    
    sizet++;
    DatePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval2 = layoutProperty->GetButtonRoleValue();
    EXPECT_EQ(testval2, ButtonRole::NORMAL);
}

/**
 * @tc.name: DataPickerDialogViewUpdateButtonStyles010
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestUpdate, DataPickerDialogViewUpdateButtonStyles010, TestSize.Level1)
{
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    ButtonInfo info2;
    info1.buttonStyle = std::make_optional<ButtonStyleMode>(ButtonStyleMode::EMPHASIZE);
    info2.buttonStyle = ButtonStyleMode::TEXT;
    buttonInfos.push_back(info1);
    buttonInfos.push_back(info2);

    size_t sizet = 0;

    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
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

    DatePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval = layoutProperty->GetButtonStyleValue();
    EXPECT_EQ(testval, ButtonStyleMode::EMPHASIZE);
    
    sizet++;
    DatePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval2 = layoutProperty->GetButtonStyleValue();
    EXPECT_EQ(testval2, ButtonStyleMode::TEXT);
}

/**
 * @tc.name: DataPickerDialogViewUpdateButtonStyles011
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestUpdate, DataPickerDialogViewUpdateButtonStyles011, TestSize.Level1)
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
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
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

    DatePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    
    auto testval = layoutProperty->GetTypeValue();
    EXPECT_EQ(testval, ButtonType::CIRCLE);

    sizet++;
    DatePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    
    auto testval2 = layoutProperty->GetTypeValue();
    EXPECT_EQ(testval2, ButtonType::CAPSULE);
}

/**
 * @tc.name: DataPickerDialogViewUpdateButtonStyles012
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestUpdate, DataPickerDialogViewUpdateButtonStyles012, TestSize.Level1)
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
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
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

    DatePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    
    auto testval = layoutProperty->GetFontStyleValue();
    EXPECT_EQ(testval, Ace::FontStyle::ITALIC);

    sizet++;
    DatePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    
    auto testval2 = layoutProperty->GetFontStyleValue();
    EXPECT_EQ(testval2, Ace::FontStyle::NONE);
}

/**
 * @tc.name: DataPickerDialogViewUpdateButtonStyles013
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestUpdate, DataPickerDialogViewUpdateButtonStyles013, TestSize.Level1)
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
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
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

    DatePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval = layoutProperty->GetFontStyleValue();
    EXPECT_EQ(testval, Ace::FontStyle::ITALIC);

    auto testval2 = layoutProperty->GetFontWeightValue();
    EXPECT_EQ(testval2, FontWeight::W500);

    auto testval3 = layoutProperty->GetFontColorValue();
    EXPECT_EQ(testval3, Color::BLACK);
}

/**
 * @tc.name: DataPickerDialogViewUpdateButtonStyles014
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestUpdate, DataPickerDialogViewUpdateButtonStyles014, TestSize.Level1)
{
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.type = std::make_optional<ButtonType>(ButtonType::CIRCLE);
    info1.buttonStyle = std::make_optional<ButtonStyleMode>(ButtonStyleMode::EMPHASIZE);
    info1.role = std::make_optional<ButtonRole>(ButtonRole::NORMAL);
    buttonInfos.push_back(info1);

    size_t sizet = 0;

    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
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

    DatePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval = layoutProperty->GetTypeValue();
    EXPECT_EQ(testval, ButtonType::CIRCLE);

    auto testval2 = layoutProperty->GetButtonStyleValue();
    EXPECT_EQ(testval2, ButtonStyleMode::EMPHASIZE);

    auto testval3 = layoutProperty->GetButtonRoleValue();
    EXPECT_EQ(testval3, ButtonRole::NORMAL);
}

/**
 * @tc.name: DataPickerDialogViewUpdateButtonStyles015
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestUpdate, DataPickerDialogViewUpdateButtonStyles015, TestSize.Level1)
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
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
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
    DatePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval = layoutProperty->GetFontSizeValue();
    EXPECT_EQ(testval, Dimension(0));
}

/**
 * @tc.name: DataPickerDialogViewUpdateButtonStyles016
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestUpdate, DataPickerDialogViewUpdateButtonStyles016, TestSize.Level1)
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
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
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
    DatePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval = layoutProperty->GetFontSizeValue();
    EXPECT_EQ(testval, Dimension(100));
}

/**
 * @tc.name: DataPickerDialogViewUpdateButtonStyles017
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestUpdate, DataPickerDialogViewUpdateButtonStyles017, TestSize.Level1)
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
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
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
    DatePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval = layoutProperty->GetFontSizeValue();
    EXPECT_EQ(testval, Dimension(1));
}

/**
 * @tc.name: DataPickerDialogViewUpdateButtonStyles018
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestUpdate, DataPickerDialogViewUpdateButtonStyles018, TestSize.Level1)
{
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontSize = Dimension(1);
    info1.fontColor = Color::BLACK;
    buttonInfos.push_back(info1);
    size_t sizet = 0;

    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
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
    DatePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);

    auto testval = layoutProperty->GetFontSizeValue();
    EXPECT_EQ(testval, Dimension(1));
    
    auto testval3 = layoutProperty->GetFontColorValue();
    EXPECT_EQ(testval3, Color::BLACK);
}

/**
 * @tc.name: DataPickerDialogViewUpdateButtonStyles019
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestUpdate, DataPickerDialogViewUpdateButtonStyles019, TestSize.Level1)
{
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontSize = Dimension(0);
    info1.fontColor = Color::GREEN;
    buttonInfos.push_back(info1);
    size_t sizet = 0;

    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
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
    DatePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);

    auto testval = layoutProperty->GetFontSizeValue();
    EXPECT_EQ(testval, Dimension(0));
    
    auto testval3 = layoutProperty->GetFontColorValue();
    EXPECT_EQ(testval3, Color::GREEN);
}

/**
 * @tc.name: DataPickerDialogViewUpdateButtonStyles020
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestUpdate, DataPickerDialogViewUpdateButtonStyles020, TestSize.Level1)
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
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
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
    DatePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);

    auto testval = layoutProperty->GetFontSizeValue();
    EXPECT_EQ(testval, Dimension(100));
    
    auto testval3 = layoutProperty->GetFontColorValue();
    EXPECT_EQ(testval3, Color::FOREGROUND);
}

/**
 * @tc.name: DataPickerDialogViewUpdateButtonStyles021
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestUpdate, DataPickerDialogViewUpdateButtonStyles021, TestSize.Level1)
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
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
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

    DatePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval = layoutProperty->GetFontSizeValue();
    EXPECT_EQ(testval, Dimension(0));

    sizet++;
    DatePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval2 = layoutProperty->GetFontSizeValue();
    EXPECT_EQ(testval2, Dimension(1));
}

/**
 * @tc.name: DataPickerDialogViewUpdateButtonStyles022
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestUpdate, DataPickerDialogViewUpdateButtonStyles022, TestSize.Level1)
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
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
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
    DatePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);

    auto testval = layoutProperty->GetFontSizeValue();
    EXPECT_EQ(testval, Dimension(100));

    sizet++;
    DatePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval2 = layoutProperty->GetFontSizeValue();
    EXPECT_EQ(testval2, Dimension(0));
}

/**
 * @tc.name: DataPickerDialogViewUpdateButtonStyles023
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestUpdate, DataPickerDialogViewUpdateButtonStyles023, TestSize.Level1)
{
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    ButtonInfo info2;
    ButtonInfo info3;
    info1.fontSize = Dimension(20);
    info2.fontSize = Dimension(100);
    info3.fontSize = Dimension(0);
    buttonInfos.push_back(info1);
    buttonInfos.push_back(info2);
    buttonInfos.push_back(info3);
    size_t sizet = 0;

    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
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
    DatePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);

    auto testval = layoutProperty->GetFontSizeValue();
    EXPECT_EQ(testval, Dimension(20));

    sizet++;
    DatePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval2 = layoutProperty->GetFontSizeValue();
    EXPECT_EQ(testval2, Dimension(100));

    sizet++;
    DatePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval3 = layoutProperty->GetFontSizeValue();
    EXPECT_EQ(testval3, Dimension(0));
}

/**
 * @tc.name: DataPickerDialogViewUpdateButtonStyles024
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestUpdate, DataPickerDialogViewUpdateButtonStyles024, TestSize.Level1)
{
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    ButtonInfo info2;
    info1.fontSize = Dimension(100);
    info1.fontColor = Color::FOREGROUND;
    info2.fontSize = Dimension(1);
    info2.fontColor = Color::GREEN;
    buttonInfos.push_back(info1);
    buttonInfos.push_back(info2);
    size_t sizet = 0;

    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
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

    DatePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval = layoutProperty->GetFontSizeValue();
    EXPECT_EQ(testval, Dimension(100));
    auto testval2 = layoutProperty->GetFontColorValue();
    EXPECT_EQ(testval2, Color::FOREGROUND);

    sizet++;
    DatePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval3 = layoutProperty->GetFontSizeValue();
    EXPECT_EQ(testval3, Dimension(1));
    auto testval4 = layoutProperty->GetFontColorValue();
    EXPECT_EQ(testval4, Color::GREEN);
}

/**
 * @tc.name: DataPickerDialogViewUpdateButtonStyles025
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestUpdate, DataPickerDialogViewUpdateButtonStyles025, TestSize.Level1)
{
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    ButtonInfo info2;
    info1.fontSize = Dimension(0);
    info1.fontColor = Color::GREEN;
    info2.fontColor = Color::FOREGROUND;
    info2.fontSize = Dimension(20);
    buttonInfos.push_back(info1);
    buttonInfos.push_back(info2);
    size_t sizet = 0;

    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
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

    DatePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval = layoutProperty->GetFontSizeValue();
    EXPECT_EQ(testval, Dimension(0));
    auto testval2 = layoutProperty->GetFontColorValue();
    EXPECT_EQ(testval2, Color::GREEN);

    sizet++;
    DatePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval3 = layoutProperty->GetFontSizeValue();
    EXPECT_EQ(testval3, Dimension(20));
    auto testval4 = layoutProperty->GetFontColorValue();
    EXPECT_EQ(testval4, Color::FOREGROUND);
}
} // namespace OHOS::Ace::NG