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


#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_default.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/rosen/mock_canvas.h"

#include "core/components/theme/icon_theme.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_view.h"
#include "core/components_ng/pattern/picker/date_time_animation_controller.h"
#include "core/components_ng/pattern/picker/datepicker_dialog_view.h"
#include "core/components_ng/pattern/picker/datepicker_model_ng.h"
#include "core/components_ng/pattern/picker/datepicker_pattern.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

namespace {
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

class DatePickerTestUpdate : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void CreateDatePickerColumnNode();

    RefPtr<FrameNode> columnNode_;
    RefPtr<DatePickerColumnPattern> columnPattern_;
    PickerDate limitStartDate_ = PickerDate(1900, 1, 31); //1900, 1, 31 is the limit start date
    PickerDate limitEndDate_ = PickerDate(2100, 12, 31); //2100, 12, 31 is the limit end date
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
    MockContainer::SetUp();
}

void DatePickerTestUpdate::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void DatePickerTestUpdate::SetUp()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        return GetTheme(type);
    });
    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([](ThemeType type, int32_t themeScopeId) -> RefPtr<Theme> { return GetTheme(type); });
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

/* @tc.name: DataPickerViewUpdate001
 * @tc.desc: Test DatePickerModel update datepicker view.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestUpdate, DataPickerViewUpdate001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create datepicker
     * @tc.expected: Property has no value
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();

    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_FALSE(pickerProperty->HasColor());
    EXPECT_FALSE(pickerProperty->HasFontSize());
    EXPECT_FALSE(pickerProperty->HasWeight());

    /**
     * @tc.steps: step2. update normalTextStyle
     * @tc.expected: normalTextStyle is correct.
     */
    PickerTextStyle data;
    data.fontSize = Dimension(10); //10 is fontsize of datepicker
    data.textColor = Color::RED;
    data.fontWeight = Ace::FontWeight::BOLD;
    DatePickerModel::GetInstance()->SetNormalTextStyle(theme, data);

    pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(Color::RED, pickerProperty->GetColor().value());
    EXPECT_EQ(Dimension(10), pickerProperty->GetFontSize().value()); //10 is fontsize of datepicker
    EXPECT_EQ(Ace::FontWeight::BOLD, pickerProperty->GetWeight().value());

    /**
     * @tc.steps: step3. update normalTextStyle invalid value
     * @tc.expected: normalTextStyle is correct.
     */
    auto selectedStyle = theme->GetOptionStyle(true, false);
    data.fontSize = Dimension(-1); //-1 is fontsize of datepicker
    data.textColor = Color::BLUE;
    data.fontWeight = Ace::FontWeight::MEDIUM;
    DatePickerModel::GetInstance()->SetNormalTextStyle(theme, data);

    pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(Color::BLUE, pickerProperty->GetColor().value());
    EXPECT_EQ(selectedStyle.GetFontSize(), pickerProperty->GetFontSize().value());
    EXPECT_EQ(Ace::FontWeight::MEDIUM, pickerProperty->GetWeight().value());

    /**
     * @tc.steps: step4. update normalTextStyle all 0
     * @tc.expected: normalTextStyle is correct.
     */
    data.fontSize = Dimension(0);
    data.textColor = Color(0x00000000);
    data.fontWeight = Ace::FontWeight::MEDIUM;
    DatePickerModel::GetInstance()->SetNormalTextStyle(theme, data);

    pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(Color(0x00000000), pickerProperty->GetColor().value());
    EXPECT_EQ(selectedStyle.GetFontSize(), pickerProperty->GetFontSize().value());
    EXPECT_EQ(Ace::FontWeight::MEDIUM, pickerProperty->GetWeight().value());
}

/**
 * @tc.name: DataPickerViewUpdate002
 * @tc.desc: Test DatePickerModel update datepicker view.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestUpdate, DataPickerViewUpdate002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create datepicker
     * @tc.expected: Property has no value
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();

    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_FALSE(pickerProperty->HasDisappearColor());
    EXPECT_FALSE(pickerProperty->HasDisappearFontSize());
    EXPECT_FALSE(pickerProperty->HasDisappearWeight());

    /**
     * @tc.steps: step2. update disappearTextStyle
     * @tc.expected: disappearTextStyle is correct.
     */
    PickerTextStyle data;
    data.fontSize = Dimension(10); //10 is fontsize of datepicker
    data.textColor = Color::RED;
    data.fontWeight = Ace::FontWeight::BOLD;
    DatePickerModel::GetInstance()->SetDisappearTextStyle(theme, data);

    pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(Color::RED, pickerProperty->GetDisappearColor().value());
    EXPECT_EQ(Dimension(10), pickerProperty->GetDisappearFontSize().value()); //10 is fontsize of datepicker
    EXPECT_EQ(Ace::FontWeight::BOLD, pickerProperty->GetDisappearWeight().value());

    /**
     * @tc.steps: step3. update disappearTextStyle  invalid value
     * @tc.expected: disappearTextStyle is correct.
     */
    auto selectedStyle = theme->GetOptionStyle(true, false);
    data.fontSize = Dimension(-1); //-1 is fontsize of datepicker
    data.textColor = Color::BLUE;
    data.fontWeight = Ace::FontWeight::MEDIUM;
    DatePickerModel::GetInstance()->SetDisappearTextStyle(theme, data);

    pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(Color::BLUE, pickerProperty->GetDisappearColor().value());
    EXPECT_EQ(selectedStyle.GetFontSize(), pickerProperty->GetDisappearFontSize().value());
    EXPECT_EQ(Ace::FontWeight::MEDIUM, pickerProperty->GetDisappearWeight().value());

    /**
     * @tc.steps: step4. update disappearTextStyle all 0
     * @tc.expected: disappearTextStyle is correct.
     */
    data.fontSize = Dimension(0);
    data.textColor = Color(0x00000000);
    data.fontWeight = Ace::FontWeight::MEDIUM;
    DatePickerModel::GetInstance()->SetDisappearTextStyle(theme, data);

    pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(Color(0x00000000), pickerProperty->GetDisappearColor().value());
    EXPECT_EQ(selectedStyle.GetFontSize(), pickerProperty->GetDisappearFontSize().value());
    EXPECT_EQ(Ace::FontWeight::MEDIUM, pickerProperty->GetDisappearWeight().value());
}

/**
 * @tc.name: DataPickerViewUpdate003
 * @tc.desc: Test DatePickerModel update datepicker view.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestUpdate, DataPickerViewUpdate003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create datepicker
     * @tc.expected: Property has no value
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();

    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_FALSE(pickerProperty->HasSelectedColor());
    EXPECT_FALSE(pickerProperty->HasSelectedFontSize());
    EXPECT_FALSE(pickerProperty->HasSelectedWeight());

    /**
     * @tc.steps: step2. update selectedTextStyle
     * @tc.expected: selectedTextStyle is correct.
     */
    PickerTextStyle data;
    data.fontSize = Dimension(10); //10 is fontsize of datepicker
    data.textColor = Color::RED;
    data.fontWeight = Ace::FontWeight::BOLD;
    DatePickerModel::GetInstance()->SetSelectedTextStyle(theme, data);

    pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(Color::RED, pickerProperty->GetSelectedColor().value());
    EXPECT_EQ(Dimension(10), pickerProperty->GetSelectedFontSize().value()); //10 is fontsize of datepicker
    EXPECT_EQ(Ace::FontWeight::BOLD, pickerProperty->GetSelectedWeight().value());

    /**
     * @tc.steps: step3. update selectedTextStyle invalid value
     * @tc.expected: selectedTextStyle is correct.
     */
    auto selectedStyle = theme->GetOptionStyle(true, false);
    data.fontSize = Dimension(-1); //-1 is fontsize of datepicker
    data.textColor = Color::BLUE;
    data.fontWeight = Ace::FontWeight::MEDIUM;
    DatePickerModel::GetInstance()->SetSelectedTextStyle(theme, data);

    pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(Color::BLUE, pickerProperty->GetSelectedColor().value());
    EXPECT_EQ(selectedStyle.GetFontSize(), pickerProperty->GetSelectedFontSize().value());
    EXPECT_EQ(Ace::FontWeight::MEDIUM, pickerProperty->GetSelectedWeight().value());

    /**
     * @tc.steps: step4. update selectedTextStyle all 0
     * @tc.expected: selectedTextStyle is correct.
     */
    data.fontSize = Dimension(0);
    data.textColor = Color(0x00000000);
    data.fontWeight = Ace::FontWeight::MEDIUM;
    DatePickerModel::GetInstance()->SetSelectedTextStyle(theme, data);

    pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(Color(0x00000000), pickerProperty->GetSelectedColor().value());
    EXPECT_EQ(selectedStyle.GetFontSize(), pickerProperty->GetSelectedFontSize().value());
    EXPECT_EQ(Ace::FontWeight::MEDIUM, pickerProperty->GetSelectedWeight().value());
}

/**
 * @tc.name: DataPickerViewUpdate004
 * @tc.desc: Test DatePickerModel update datepicker view.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestUpdate, DataPickerViewUpdate004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create datepicker
     * @tc.expected: Property has no value
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();

    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_FALSE(pickerProperty->HasLunar());

    /**
     * @tc.steps: step2. update showLunar
     * @tc.expected: showLunar is correct.
     */
    DatePickerModel::GetInstance()->SetShowLunar(true);

    pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(true, pickerProperty->GetLunar().value());

    DatePickerModel::GetInstance()->SetShowLunar(false);

    pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(false, pickerProperty->GetLunar().value());
}

/**
 * @tc.name: DataPickerViewUpdate005
 * @tc.desc: Test DatePickerModel update datepicker view.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestUpdate, DataPickerViewUpdate005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create datepicker
     * @tc.expected: Property has no value
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();

    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    EXPECT_EQ(datePickerPattern->backgroundColor_, Color::WHITE);

    /**
     * @tc.steps: step2. update backgroundColor
     * @tc.expected: backgroundColor is correct.
     */
    DatePickerModel::GetInstance()->SetBackgroundColor(Color::BLACK);
    datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    EXPECT_EQ(datePickerPattern->backgroundColor_, Color::BLACK);

    DatePickerModel::GetInstance()->SetBackgroundColor(Color(0x00000000));
    datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    EXPECT_EQ(datePickerPattern->backgroundColor_, Color(0x00000000));
}

/**
 * @tc.name: DataPickerViewUpdate006
 * @tc.desc: Test DatePickerModel update datepicker view.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestUpdate, DataPickerViewUpdate006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create datepicker
     * @tc.expected: Property has no value
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();

    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_FALSE(pickerProperty->HasStartDate());
    EXPECT_FALSE(pickerProperty->HasEndDate());

    /**
     * @tc.steps: step2. update startDate and endDate
     * @tc.expected: startDate and endDate are correct.
     */
    DatePickerModel::GetInstance()->SetStartDate(PickerDate(1990, 1, 1)); //1990 is year of start date
    DatePickerModel::GetInstance()->SetEndDate(PickerDate(2090, 1, 1));   //2090 is year of end date
    pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(1990, pickerProperty->GetStartDate()->year); //1990 is year of start date
    EXPECT_EQ(1, pickerProperty->GetStartDate()->month);
    EXPECT_EQ(1, pickerProperty->GetStartDate()->day);
    EXPECT_EQ(2090, pickerProperty->GetEndDate()->year); //2090 is year of end date
    EXPECT_EQ(1, pickerProperty->GetEndDate()->month);
    EXPECT_EQ(1, pickerProperty->GetEndDate()->day);

    /**
     * @tc.steps: step3. update startDate and endDate invalid value
     * @tc.expected: startDate and endDate are correct.
     */
    DatePickerModel::GetInstance()->SetStartDate(PickerDate(0, 0, 0));
    DatePickerModel::GetInstance()->SetEndDate(PickerDate(3000, 13, 32)); //3000, 13, 32 is the end date
    pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(limitStartDate_.GetYear(), pickerProperty->GetStartDate()->year);
    EXPECT_EQ(limitStartDate_.GetMonth(), pickerProperty->GetStartDate()->month);
    EXPECT_EQ(limitStartDate_.GetDay(), pickerProperty->GetStartDate()->day);
    EXPECT_EQ(limitEndDate_.GetYear(), pickerProperty->GetEndDate()->year);
    EXPECT_EQ(limitEndDate_.GetMonth(), pickerProperty->GetEndDate()->month);
    EXPECT_EQ(limitEndDate_.GetDay(), pickerProperty->GetEndDate()->day);

    /**
     * @tc.steps: step4. update startDate and endDate limited value
     * @tc.expected: startDate and endDate are correct.
     */
    DatePickerModel::GetInstance()->SetStartDate(limitStartDate_);
    DatePickerModel::GetInstance()->SetEndDate(limitEndDate_);
    pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(limitStartDate_.GetYear(), pickerProperty->GetStartDate()->year);
    EXPECT_EQ(limitStartDate_.GetMonth(), pickerProperty->GetStartDate()->month);
    EXPECT_EQ(limitStartDate_.GetDay(), pickerProperty->GetStartDate()->day);
    EXPECT_EQ(limitEndDate_.GetYear(), pickerProperty->GetEndDate()->year);
    EXPECT_EQ(limitEndDate_.GetMonth(), pickerProperty->GetEndDate()->month);
    EXPECT_EQ(limitEndDate_.GetDay(), pickerProperty->GetEndDate()->day);
}

/**
 * @tc.name: DataPickerViewUpdate007
 * @tc.desc: Test DatePickerModel update datepicker view.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestUpdate, DataPickerViewUpdate007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create datepicker
     * @tc.expected: Property has no value
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();

    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_FALSE(pickerProperty->HasSelectedDate());

    /**
     * @tc.steps: step2. update selectedDate
     * @tc.expected: selectedDate is correct.
     */
    DatePickerModel::GetInstance()->SetSelectedDate(PickerDate(1990, 1, 1)); //1990 is year of start date
    pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(1990, pickerProperty->GetSelectedDate()->year); //1990 is year of start date
    EXPECT_EQ(1, pickerProperty->GetSelectedDate()->month);
    EXPECT_EQ(1, pickerProperty->GetSelectedDate()->day);

    /**
     * @tc.steps: step3. update selectedDate all 0
     * @tc.expected: selectedDate is correct.
     */
    DatePickerModel::GetInstance()->SetSelectedDate(PickerDate(0, 0, 0));
    auto selectedDate = PickerDate::Current();
    pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(selectedDate.GetYear(), pickerProperty->GetSelectedDate()->year);
    EXPECT_EQ(selectedDate.GetMonth(), pickerProperty->GetSelectedDate()->month);
    EXPECT_EQ(selectedDate.GetDay(), pickerProperty->GetSelectedDate()->day);

    /**
     * @tc.steps: step4. update selectedDate invalid value
     * @tc.expected: selectedDate is correct.
     */
    DatePickerModel::GetInstance()->SetSelectedDate(PickerDate(3000, 13, 32)); //3000, 13, 32 is the end date
    pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(limitEndDate_.GetYear(), pickerProperty->GetSelectedDate()->year);
    EXPECT_EQ(limitEndDate_.GetMonth(), pickerProperty->GetSelectedDate()->month);
    EXPECT_EQ(limitEndDate_.GetDay(), pickerProperty->GetSelectedDate()->day);

    /**
     * @tc.steps: step5. update selectedDate limited value
     * @tc.expected: selectedDate is correct.
     */
    DatePickerModel::GetInstance()->SetSelectedDate(limitStartDate_);
    pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(theme->GetDefaultStartDate().GetYear(), pickerProperty->GetSelectedDate()->year);
    EXPECT_EQ(theme->GetDefaultStartDate().GetMonth(), pickerProperty->GetSelectedDate()->month);
    EXPECT_EQ(theme->GetDefaultStartDate().GetDay(), pickerProperty->GetSelectedDate()->day);

    DatePickerModel::GetInstance()->SetSelectedDate(limitEndDate_);
    pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(limitEndDate_.GetYear(), pickerProperty->GetSelectedDate()->year);
    EXPECT_EQ(limitEndDate_.GetMonth(), pickerProperty->GetSelectedDate()->month);
    EXPECT_EQ(limitEndDate_.GetDay(), pickerProperty->GetSelectedDate()->day);
}

/**
 * @tc.name: DatePickerModelNGTest001
 * @tc.desc: Test SetSelectedTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestUpdate, DatePickerModelNGTest001, TestSize.Level1)
{
    CreateDatePickerColumnNode();
    DatePickerModelNG datePickerModelNG;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    PickerTextStyle value;

    datePickerModelNG.SetSelectedTextStyle(theme, value);
    EXPECT_TRUE(pickerProperty->HasSelectedFontSize());
    datePickerModelNG.SetSelectedTextStyle(frameNode, theme, value);
    EXPECT_TRUE(pickerProperty->HasSelectedFontSize());
}

/**
 * @tc.name: DatePickerPatternTest001
 * @tc.desc: Test FillLunarMonthDaysOptions.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestUpdate, DatePickerPatternTest001, TestSize.Level1)
{
    /**
     * @tc.step: step1. create datePickerPattern.
     */
    CreateDatePickerColumnNode();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    RefPtr<FrameNode> monthDaysColumn = datePickerPattern->GetColumn(columnNode_->GetId());
    LunarDate lunarDate;
    /**
     * @tc.step: step2. Set default date.
     * @tc.expected: the result of CurrentIndex is correct.
     */
    lunarDate.year = 1900;
    lunarDate.month = 12;
    lunarDate.day = 1;
    lunarDate.isLeapMonth = false;
    datePickerPattern->FillLunarMonthDaysOptions(lunarDate, monthDaysColumn);
    EXPECT_NE(columnPattern_->GetCurrentIndex(), 0);
    /**
     * @tc.step: step3. Set lunar date.
     * @tc.expected: the result of CurrentIndex is correct.
     */
    lunarDate.year = 1903;
    lunarDate.month = 5;
    lunarDate.day = 1;
    lunarDate.isLeapMonth = true;
    datePickerPattern->FillLunarMonthDaysOptions(lunarDate, monthDaysColumn);
    EXPECT_NE(columnPattern_->GetCurrentIndex(), 0);
}

/**
 * @tc.name: DatePickerDialogViewTest001
 * @tc.desc: Test SwitchPickerPage.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestUpdate, DatePickerDialogViewTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pickeDialog.
     */
    DatePickerSettingData settingData;
    settingData.isLunar = false;
    settingData.showTime = true;
    settingData.useMilitary = true;
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
    info1.fontWeight = FontWeight::W400;
    buttonInfos.push_back(info1);
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(dialogNode, nullptr);

    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto pickerStack = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto dateNode = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(0));
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));
    auto monthDaysNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(0));
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(1));
    /**
     * @tc.steps: step2.call CreateButtonNodeForAging.
     * @tc.expected:CreateButtonNodeForAging is executed correctly.
     */
    auto contentColumn = AceType::DynamicCast<NG::FrameNode>(customNode);
    RefPtr<DateTimeAnimationController> animationController = AceType::MakeRefPtr<DateTimeAnimationController>();
    DatePickerDialogView::isUserSetFont_ = false;
    auto pipeline = MockPipelineContext::GetCurrent();
    pipeline->fontScale_ = 2.0f;
    DatePickerDialogView::SwitchPickerPage(pickerStack, contentColumn, animationController, true);
    EXPECT_TRUE(DatePickerDialogView::switchFlag_);
    DatePickerDialogView::SwitchPickerPage(pickerStack, contentColumn, animationController, false);
    EXPECT_FALSE(DatePickerDialogView::switchFlag_);
}

/**
 * @tc.name: CreateFrameNode001
 * @tc.desc: Test DatePickerTestUpdate CreateFrameNode.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestUpdate, CreateFrameNode001, TestSize.Level1)
{
    int32_t nodeId = 0;
    RefPtr<FrameNode> frameNode = DatePickerModelNG::CreateFrameNode(nodeId);
    EXPECT_NE(frameNode, nullptr);
}

/**
 * @tc.name: SetSelectedTextStyle001
 * @tc.desc: Test DatePickerTestUpdate SetSelectedTextStyle
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestUpdate, SetSelectedTextStyle001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create datepicker
     * @tc.expected: Property has no value
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();

    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_FALSE(pickerProperty->HasSelectedColor());
    EXPECT_FALSE(pickerProperty->HasSelectedFontSize());
    EXPECT_FALSE(pickerProperty->HasSelectedWeight());

    /**
     * @tc.steps: step2. update selectedTextStyle
     * @tc.expected: selectedTextStyle is correct.
     */
    PickerTextStyle data;
    data.fontSize = Dimension(10); // 10 is fontsize of datepicker
    data.textColor = Color::RED;
    data.fontWeight = Ace::FontWeight::BOLD;
    DatePickerModelNG::SetSelectedTextStyle(frameNode, theme, data);

    pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(Color::RED, pickerProperty->GetSelectedColor().value());
    EXPECT_EQ(Dimension(10), pickerProperty->GetSelectedFontSize().value()); // 10 is fontsize of datepicker
    EXPECT_EQ(Ace::FontWeight::BOLD, pickerProperty->GetSelectedWeight().value());

    /**
     * @tc.steps: step3. update selectedTextStyle invalid value
     * @tc.expected: selectedTextStyle is correct.
     */
    auto selectedStyle = theme->GetOptionStyle(true, false);
    data.fontSize = Dimension(-1); //-1 is fontsize of datepicker
    data.textColor = Color::BLUE;
    data.fontWeight = Ace::FontWeight::MEDIUM;
    DatePickerModelNG::SetSelectedTextStyle(frameNode, theme, data);

    pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(Color::BLUE, pickerProperty->GetSelectedColor().value());
    EXPECT_EQ(selectedStyle.GetFontSize(), pickerProperty->GetSelectedFontSize().value());
    EXPECT_EQ(Ace::FontWeight::MEDIUM, pickerProperty->GetSelectedWeight().value());

    /**
     * @tc.steps: step4. update selectedTextStyle all 0
     * @tc.expected: selectedTextStyle is correct.
     */
    data.fontSize = Dimension(0);
    data.textColor = Color(0x00000000);
    data.fontWeight = Ace::FontWeight::MEDIUM;
    DatePickerModelNG::SetSelectedTextStyle(frameNode, theme, data);

    pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(Color(0x00000000), pickerProperty->GetSelectedColor().value());
    EXPECT_EQ(selectedStyle.GetFontSize(), pickerProperty->GetSelectedFontSize().value());
    EXPECT_EQ(Ace::FontWeight::MEDIUM, pickerProperty->GetSelectedWeight().value());
}

/* @tc.name: SetNormalTextStyle001
 * @tc.desc: Test DatePickerTestUpdate SetNormalTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestUpdate, SetNormalTextStyle001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create datepicker
     * @tc.expected: Property has no value
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();

    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_FALSE(pickerProperty->HasColor());
    EXPECT_FALSE(pickerProperty->HasFontSize());
    EXPECT_FALSE(pickerProperty->HasWeight());

    /**
     * @tc.steps: step2. update normalTextStyle
     * @tc.expected: normalTextStyle is correct.
     */
    PickerTextStyle data;
    data.fontSize = Dimension(10); // 10 is fontsize of datepicker
    data.textColor = Color::RED;
    data.fontWeight = Ace::FontWeight::BOLD;
    DatePickerModelNG::SetNormalTextStyle(frameNode, theme, data);

    pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(Color::RED, pickerProperty->GetColor().value());
    EXPECT_EQ(Dimension(10), pickerProperty->GetFontSize().value()); // 10 is fontsize of datepicker
    EXPECT_EQ(Ace::FontWeight::BOLD, pickerProperty->GetWeight().value());

    /**
     * @tc.steps: step3. update normalTextStyle invalid value
     * @tc.expected: normalTextStyle is correct.
     */
    auto selectedStyle = theme->GetOptionStyle(true, false);
    data.fontSize = Dimension(-1); //-1 is fontsize of datepicker
    data.textColor = Color::BLUE;
    data.fontWeight = Ace::FontWeight::MEDIUM;
    DatePickerModelNG::SetNormalTextStyle(frameNode, theme, data);

    pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(Color::BLUE, pickerProperty->GetColor().value());
    EXPECT_EQ(selectedStyle.GetFontSize(), pickerProperty->GetFontSize().value());
    EXPECT_EQ(Ace::FontWeight::MEDIUM, pickerProperty->GetWeight().value());

    /**
     * @tc.steps: step4. update normalTextStyle all 0
     * @tc.expected: normalTextStyle is correct.
     */
    data.fontSize = Dimension(0);
    data.textColor = Color(0x00000000);
    data.fontWeight = Ace::FontWeight::MEDIUM;
    DatePickerModelNG::SetNormalTextStyle(frameNode, theme, data);

    pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(Color(0x00000000), pickerProperty->GetColor().value());
    EXPECT_EQ(selectedStyle.GetFontSize(), pickerProperty->GetFontSize().value());
    EXPECT_EQ(Ace::FontWeight::MEDIUM, pickerProperty->GetWeight().value());
}

/**
 * @tc.name: DisappearTextStyle001
 * @tc.desc: Test DatePickerTestUpdate DisappearTextStyle001.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestUpdate, DisappearTextStyle001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create datepicker
     * @tc.expected: Property has no value
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();

    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_FALSE(pickerProperty->HasDisappearColor());
    EXPECT_FALSE(pickerProperty->HasDisappearFontSize());
    EXPECT_FALSE(pickerProperty->HasDisappearWeight());

    /**
     * @tc.steps: step2. update disappearTextStyle
     * @tc.expected: disappearTextStyle is correct.
     */
    PickerTextStyle data;
    data.fontSize = Dimension(10); // 10 is fontsize of datepicker
    data.textColor = Color::RED;
    data.fontWeight = Ace::FontWeight::BOLD;
    DatePickerModelNG::SetDisappearTextStyle(frameNode, theme, data);

    pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(Color::RED, pickerProperty->GetDisappearColor().value());
    EXPECT_EQ(Dimension(10), pickerProperty->GetDisappearFontSize().value()); // 10 is fontsize of datepicker
    EXPECT_EQ(Ace::FontWeight::BOLD, pickerProperty->GetDisappearWeight().value());

    /**
     * @tc.steps: step3. update disappearTextStyle  invalid value
     * @tc.expected: disappearTextStyle is correct.
     */
    auto selectedStyle = theme->GetOptionStyle(true, false);
    data.fontSize = Dimension(-1); //-1 is fontsize of datepicker
    data.textColor = Color::BLUE;
    data.fontWeight = Ace::FontWeight::MEDIUM;
    DatePickerModelNG::SetDisappearTextStyle(frameNode, theme, data);

    pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(Color::BLUE, pickerProperty->GetDisappearColor().value());
    EXPECT_EQ(selectedStyle.GetFontSize(), pickerProperty->GetDisappearFontSize().value());
    EXPECT_EQ(Ace::FontWeight::MEDIUM, pickerProperty->GetDisappearWeight().value());

    /**
     * @tc.steps: step4. update disappearTextStyle all 0
     * @tc.expected: disappearTextStyle is correct.
     */
    data.fontSize = Dimension(0);
    data.textColor = Color(0x00000000);
    data.fontWeight = Ace::FontWeight::MEDIUM;
    DatePickerModelNG::SetDisappearTextStyle(frameNode, theme, data);

    pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(Color(0x00000000), pickerProperty->GetDisappearColor().value());
    EXPECT_EQ(selectedStyle.GetFontSize(), pickerProperty->GetDisappearFontSize().value());
    EXPECT_EQ(Ace::FontWeight::MEDIUM, pickerProperty->GetDisappearWeight().value());
}

/**
 * @tc.name: ShowContentRowButton001
 * @tc.desc: Test DatePickerTestUpdate ShowContentRowButton.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestUpdate, ShowContentRowButton001, TestSize.Level1)
{
    bool isFirstPage = true;
    CreateDatePickerColumnNode();
    DatePickerDialogView::ShowContentRowButton(columnNode_, isFirstPage);
    EXPECT_EQ(AceType::DynamicCast<FrameNode>(columnNode_->GetFirstChild())
                  ->GetLayoutProperty<LayoutProperty>()
                  ->propVisibility_,
        VisibleType::VISIBLE);
}

/**
 * @tc.name: ShowContentRowButton002
 * @tc.desc: Test DatePickerTestUpdate ShowContentRowButton.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestUpdate, ShowContentRowButton002, TestSize.Level1)
{
    bool isFirstPage = false;
    CreateDatePickerColumnNode();
    DatePickerDialogView::ShowContentRowButton(columnNode_, isFirstPage);
    EXPECT_EQ(AceType::DynamicCast<FrameNode>(columnNode_->GetChildAtIndex(2))
                  ->GetLayoutProperty<LayoutProperty>()
                  ->propVisibility_,
        VisibleType::VISIBLE);
}

/**
 * @tc.name: UpdateNextButtonMargin001
 * @tc.desc: Test DatePickerTestUpdate UpdateNextButtonMargin.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestUpdate, UpdateNextButtonMargin001, TestSize.Level1)
{
    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    CHECK_NULL_VOID(buttonNode);
    auto layoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    RefPtr<ButtonLayoutProperty> buttonLayoutProperty = AceType::DynamicCast<ButtonLayoutProperty>(layoutProperty);
    ASSERT_NE(buttonLayoutProperty, nullptr);
    DatePickerDialogView::UpdateNextButtonMargin(buttonLayoutProperty);
    ASSERT_NE(buttonLayoutProperty->GetMarginProperty(), nullptr);
}

/**
 * @tc.name: HandleMouseEvent001
 * @tc.desc: Test DatePickerTestUpdate HandleMouseEvent.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestUpdate, HandleMouseEvent001, TestSize.Level1)
{
    bool isHover = true;
    auto titleButtonRow = DatePickerDialogView::CreateTitleButtonRowNode();
    DatePickerDialogView::HandleMouseEvent(titleButtonRow, isHover);
    EXPECT_EQ(AceType::DynamicCast<FrameNode>(titleButtonRow)->GetRenderContext()->GetBackgroundColor(),
        PipelineBase::GetCurrentContext()->GetTheme<PickerTheme>()->GetHoverColor());
}

/**
 * @tc.name: HandleMouseEvent002
 * @tc.desc: Test DatePickerTestUpdate HandleMouseEvent.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestUpdate, HandleMouseEvent002, TestSize.Level1)
{
    bool isHover = false;
    auto titleButtonRow = DatePickerDialogView::CreateTitleButtonRowNode();
    DatePickerDialogView::HandleMouseEvent(titleButtonRow, isHover);
    EXPECT_EQ(
        AceType::DynamicCast<FrameNode>(titleButtonRow)->GetRenderContext()->GetBackgroundColor(), Color::TRANSPARENT);
}

/**
 * @tc.name: HandleLunarDayChange001
 * @tc.desc: Test DatePickerTestUpdate HandleLunarDayChange.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestUpdate, HandleLunarDayChange001, TestSize.Level1)
{
    uint32_t index = 0;
    bool isAdd = true;
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    datePickerPattern->HandleLunarDayChange(isAdd, index);
}

/**
 * @tc.name: HandleLunarDayChange002
 * @tc.desc: Test DatePickerTestUpdate HandleLunarDayChange.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestUpdate, HandleLunarDayChange002, TestSize.Level1)
{
    uint32_t index = 0;
    bool isAdd = false;
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    datePickerPattern->HandleLunarDayChange(isAdd, index);
}

/**
 * @tc.name: DatePickerPatternTest019
 * @tc.desc: Test SetMode method.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestUpdate, DatePickerPatternTest019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create datePickerModelNG.
     */
    CreateDatePickerColumnNode();
    DatePickerModelNG datePickerModelNG;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. Set DatePickerMode::DATE and ASSERT mode
     */
    DatePickerMode valueMode = DatePickerMode::DATE;
    datePickerModelNG.SetMode(valueMode);
    auto pattern = frameNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto mode = datePickerModelNG.getMode(frameNode);
    EXPECT_EQ(mode, valueMode);
    /**
     * @tc.steps: step3. Set DatePickerMode::YEAR_AND_MONTH and ASSERT mode
     */
    valueMode = DatePickerMode::YEAR_AND_MONTH;
    datePickerModelNG.SetMode(valueMode);
    mode = datePickerModelNG.getMode(frameNode);
    EXPECT_EQ(mode, valueMode);
    /**
     * @tc.steps: step4. Set DatePickerMode::MONTH_AND_DAY and ASSERT mode
     */
    valueMode = DatePickerMode::MONTH_AND_DAY;
    datePickerModelNG.SetMode(valueMode);
    mode = datePickerModelNG.getMode(frameNode);
    EXPECT_EQ(mode, valueMode);
}

/**
 * @tc.name: DatePickerPatternTest020
 * @tc.desc: Test SetMode method with frameNode
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestUpdate, DatePickerPatternTest020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create datePickerModelNG.
     */
    CreateDatePickerColumnNode();
    DatePickerModelNG datePickerModelNG;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. Set DatePickerMode::DATE and ASSERT mode
     */
    DatePickerMode valueMode = DatePickerMode::DATE;
    datePickerModelNG.SetMode(frameNode, valueMode);
    auto mode = datePickerModelNG.getMode(frameNode);
    EXPECT_EQ(mode, valueMode);
    /**
     * @tc.steps: step3. Set DatePickerMode::YEAR_AND_MONTH and ASSERT mode
     */
    valueMode = DatePickerMode::YEAR_AND_MONTH;
    datePickerModelNG.SetMode(frameNode, valueMode);
    mode = datePickerModelNG.getMode(frameNode);
    EXPECT_EQ(mode, valueMode);
    /**
     * @tc.steps: step4. Set DatePickerMode::MONTH_AND_DAY and ASSERT mode
     */
    valueMode = DatePickerMode::MONTH_AND_DAY;
    datePickerModelNG.SetMode(frameNode, valueMode);
    mode = datePickerModelNG.getMode(frameNode);
    EXPECT_EQ(mode, valueMode);
}

/**
 * @tc.name: DatePickerPatternTest021
 * @tc.desc: Test SetMode method abnormal value
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestUpdate, DatePickerPatternTest021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create datePickerModelNG.
     */
    CreateDatePickerColumnNode();
    DatePickerModelNG datePickerModelNG;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. Set 0 and ASSERT mode
     */
    int32_t mockMode = 0;
    DatePickerMode valueMode = static_cast<DatePickerMode>(mockMode);
    datePickerModelNG.SetMode(frameNode, valueMode);
    auto mode = datePickerModelNG.getMode(frameNode);
    EXPECT_EQ(mode, valueMode);
    /**
     * @tc.steps: step3. Set 1 and ASSERT mode
     */
    mockMode = 1;
    valueMode = static_cast<DatePickerMode>(mockMode);
    datePickerModelNG.SetMode(frameNode, valueMode);
    mode = datePickerModelNG.getMode(frameNode);
    EXPECT_EQ(mode, valueMode);
    /**
     * @tc.steps: step4. Set 2 and ASSERT mode
     */
    mockMode = 2;
    valueMode = static_cast<DatePickerMode>(mockMode);
    datePickerModelNG.SetMode(frameNode, valueMode);
    mode = datePickerModelNG.getMode(frameNode);
    EXPECT_EQ(mode, valueMode);
    /**
     * @tc.steps: step5. Set 100 and ASSERT mode
     */
    mockMode = 100;
    valueMode = static_cast<DatePickerMode>(mockMode);
    datePickerModelNG.SetMode(frameNode, valueMode);
    mode = datePickerModelNG.getMode(frameNode);
    EXPECT_EQ(mode, valueMode);
}

/**
 * @tc.name: DatePickerPatternTest022
 * @tc.desc: Test the ShowColumnByDatePickMode to correctly set the hidden column
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestUpdate, DatePickerPatternTest022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create datePickerNode.
     */
    CreateDatePickerColumnNode();
    DatePickerModelNG datePickerModelNG;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetMode(DatePickerMode::DATE);
    pattern->ShowColumnByDatePickMode();
    /**
     * @tc.steps: step2. Get year/month/day node.
     */
    RefPtr<FrameNode> stackYear;
    RefPtr<FrameNode> stackMonth;
    RefPtr<FrameNode> stackDay;
    pattern->OrderAllChildNode(stackYear, stackMonth, stackDay);
    ASSERT_NE(stackYear, nullptr);
    ASSERT_NE(stackMonth, nullptr);
    ASSERT_NE(stackDay, nullptr);
    /**
     * @tc.steps: step3. ASSERT all is VISIBLE.
     */
    auto yearBlendColumn = AceType::DynamicCast<FrameNode>(stackYear->GetLastChild());
    ASSERT_NE(yearBlendColumn, nullptr);
    auto yearColumnNodeLayoutProperty = yearBlendColumn->GetLayoutProperty<LayoutProperty>();
    ASSERT_NE(yearColumnNodeLayoutProperty, nullptr);
    auto yearVisibility = yearColumnNodeLayoutProperty->GetVisibility();
    EXPECT_EQ(yearVisibility, VisibleType::VISIBLE);

    auto monthBlendColumn = AceType::DynamicCast<FrameNode>(stackMonth->GetLastChild());
    ASSERT_NE(monthBlendColumn, nullptr);
    auto monthColumnNodeLayoutProperty = monthBlendColumn->GetLayoutProperty<LayoutProperty>();
    ASSERT_NE(monthColumnNodeLayoutProperty, nullptr);
    auto mouthVisibility = monthColumnNodeLayoutProperty->GetVisibility();
    EXPECT_EQ(mouthVisibility, VisibleType::VISIBLE);

    auto dayBlendColumn = AceType::DynamicCast<FrameNode>(stackDay->GetLastChild());
    ASSERT_NE(dayBlendColumn, nullptr);
    auto dayColumnNodeLayoutProperty = dayBlendColumn->GetLayoutProperty<LayoutProperty>();
    ASSERT_NE(dayColumnNodeLayoutProperty, nullptr);
    auto dayVisibility = dayColumnNodeLayoutProperty->GetVisibility();
    EXPECT_EQ(dayVisibility, VisibleType::VISIBLE);
}

/**
 * @tc.name: DatePickerPatternTest023
 * @tc.desc: Test the ShowColumnByDatePickMode to correctly set the hidden column
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestUpdate, DatePickerPatternTest023, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create datePickerNode.
     */
    CreateDatePickerColumnNode();
    DatePickerModelNG datePickerModelNG;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetMode(DatePickerMode::YEAR_AND_MONTH);
    pattern->ShowColumnByDatePickMode();
    /**
     * @tc.steps: step2. Get year/month/day node.
     */
    RefPtr<FrameNode> stackYear;
    RefPtr<FrameNode> stackMonth;
    RefPtr<FrameNode> stackDay;
    pattern->OrderAllChildNode(stackYear, stackMonth, stackDay);
    ASSERT_NE(stackYear, nullptr);
    ASSERT_NE(stackMonth, nullptr);
    ASSERT_NE(stackDay, nullptr);
    /**
     * @tc.steps: step3. ASSERT year is VISIBLE.
     */
    auto yearBlendColumn = AceType::DynamicCast<FrameNode>(stackYear->GetLastChild());
    ASSERT_NE(yearBlendColumn, nullptr);
    auto yearColumnNodeLayoutProperty = yearBlendColumn->GetLayoutProperty<LayoutProperty>();
    ASSERT_NE(yearColumnNodeLayoutProperty, nullptr);
    auto yearVisibility = yearColumnNodeLayoutProperty->GetVisibility();
    EXPECT_EQ(yearVisibility, VisibleType::VISIBLE);
    /**
     * @tc.steps: step4. ASSERT month is VISIBLE.
     */
    auto monthBlendColumn = AceType::DynamicCast<FrameNode>(stackMonth->GetLastChild());
    ASSERT_NE(monthBlendColumn, nullptr);
    auto monthColumnNodeLayoutProperty = monthBlendColumn->GetLayoutProperty<LayoutProperty>();
    ASSERT_NE(monthColumnNodeLayoutProperty, nullptr);
    auto mouthVisibility = monthColumnNodeLayoutProperty->GetVisibility();
    EXPECT_EQ(mouthVisibility, VisibleType::VISIBLE);
    /**
     * @tc.steps: step5. ASSERT month is GONE.
     */
    auto dayBlendColumn = AceType::DynamicCast<FrameNode>(stackDay->GetLastChild());
    ASSERT_NE(dayBlendColumn, nullptr);
    auto dayColumnNodeLayoutProperty = dayBlendColumn->GetLayoutProperty<LayoutProperty>();
    ASSERT_NE(dayColumnNodeLayoutProperty, nullptr);
    auto dayVisibility = dayColumnNodeLayoutProperty->GetVisibility();
    EXPECT_EQ(dayVisibility, VisibleType::GONE);
}

/**
 * @tc.name: DatePickerPatternTest024
 * @tc.desc: Test the ShowColumnByDatePickMode to correctly set the hidden column
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestUpdate, DatePickerPatternTest024, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create datePickerNode.
     */
    CreateDatePickerColumnNode();
    DatePickerModelNG datePickerModelNG;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetMode(DatePickerMode::MONTH_AND_DAY);
    pattern->ShowColumnByDatePickMode();
    /**
     * @tc.steps: step2. Get year/month/day node.
     */
    RefPtr<FrameNode> stackYear;
    RefPtr<FrameNode> stackMonth;
    RefPtr<FrameNode> stackDay;
    pattern->OrderAllChildNode(stackYear, stackMonth, stackDay);
    ASSERT_NE(stackYear, nullptr);
    ASSERT_NE(stackMonth, nullptr);
    ASSERT_NE(stackDay, nullptr);
    /**
     * @tc.steps: step3. ASSERT year is GONE.
     */
    auto yearBlendColumn = AceType::DynamicCast<FrameNode>(stackYear->GetLastChild());
    ASSERT_NE(yearBlendColumn, nullptr);
    auto yearColumnNodeLayoutProperty = yearBlendColumn->GetLayoutProperty<LayoutProperty>();
    ASSERT_NE(yearColumnNodeLayoutProperty, nullptr);
    auto yearVisibility = yearColumnNodeLayoutProperty->GetVisibility();
    EXPECT_EQ(yearVisibility, VisibleType::GONE);
    /**
     * @tc.steps: step4. ASSERT month is VISIBLE.
     */
    auto monthBlendColumn = AceType::DynamicCast<FrameNode>(stackMonth->GetLastChild());
    ASSERT_NE(monthBlendColumn, nullptr);
    auto monthColumnNodeLayoutProperty = monthBlendColumn->GetLayoutProperty<LayoutProperty>();
    ASSERT_NE(monthColumnNodeLayoutProperty, nullptr);
    auto mouthVisibility = monthColumnNodeLayoutProperty->GetVisibility();
    EXPECT_EQ(mouthVisibility, VisibleType::VISIBLE);
    /**
     * @tc.steps: step5. ASSERT month is VISIBLE.
     */
    auto dayBlendColumn = AceType::DynamicCast<FrameNode>(stackDay->GetLastChild());
    ASSERT_NE(dayBlendColumn, nullptr);
    auto dayColumnNodeLayoutProperty = dayBlendColumn->GetLayoutProperty<LayoutProperty>();
    ASSERT_NE(dayColumnNodeLayoutProperty, nullptr);
    auto dayVisibility = dayColumnNodeLayoutProperty->GetVisibility();
    EXPECT_EQ(dayVisibility, VisibleType::VISIBLE);
}

/**
 * @tc.name: DatePickerPatternTest025
 * @tc.desc: Test the GetVisibleColumnsText text is not null
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestUpdate, DatePickerPatternTest025, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create datePickerNode.
     */
    CreateDatePickerColumnNode();
    DatePickerModelNG datePickerModelNG;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. Set YEAR_AND_MONTH, GetColumnText is not null.
     */
    pattern->SetMode(DatePickerMode::YEAR_AND_MONTH);
    auto str = pattern->GetVisibleColumnsText();
    auto host = pattern->GetHost();
    pattern->GetColumnText(host, str);
    EXPECT_EQ(str.empty(), false);
    /**
     * @tc.steps: step3. Set MONTH_AND_DAY, GetColumnText is not null.
     */
    pattern->SetMode(DatePickerMode::MONTH_AND_DAY);
    auto strOther = pattern->GetVisibleColumnsText();
    pattern->GetColumnText(host, strOther);
    EXPECT_EQ(strOther.empty(), false);
}
} // namespace OHOS::Ace::NG
