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

#include <functional>
#include <optional>

#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/core/common/mock_theme_default.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"

#include "core/components/picker/picker_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/text_picker/textpicker_column_pattern.h"
#include "core/components_ng/pattern/text_picker/textpicker_dialog_view.h"
#include "core/components_ng/pattern/text_picker/textpicker_model_ng.h"
#include "core/components_ng/pattern/text_picker/textpicker_pattern.h"
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

class TextPickerTestUpdateButton : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void InitTextPickerTestNg();
    void DestroyTextPickerTestNgObject();

    RefPtr<FrameNode> frameNode_;
    RefPtr<TextPickerPattern> textPickerPattern_;
    RefPtr<TextPickerAccessibilityProperty> textPickerAccessibilityProperty_;
    RefPtr<TextPickerRowAccessibilityProperty> textPickerRowAccessibilityProperty_;
    RefPtr<FrameNode> stackNode_;
    RefPtr<FrameNode> blendNode_;
    RefPtr<FrameNode> columnNode_;
    RefPtr<TextPickerColumnPattern> textPickerColumnPattern_;
    RefPtr<FrameNode> stackNodeNext_;
    RefPtr<FrameNode> blendNodeNext_;
    RefPtr<FrameNode> columnNodeNext_;
    RefPtr<TextPickerColumnPattern> textPickerColumnPatternNext_;
    RefPtr<TextPickerAccessibilityProperty> textPickerAccessibilityPropertyNext_;
};

void TextPickerTestUpdateButton::DestroyTextPickerTestNgObject()
{
    frameNode_ = nullptr;
    textPickerPattern_ = nullptr;
    textPickerAccessibilityProperty_ = nullptr;
    textPickerRowAccessibilityProperty_ = nullptr;
    stackNode_ = nullptr;
    blendNode_ = nullptr;
    columnNode_ = nullptr;
    textPickerColumnPattern_ = nullptr;
    stackNodeNext_ = nullptr;
    blendNodeNext_ = nullptr;
    columnNodeNext_ = nullptr;
    textPickerColumnPatternNext_ = nullptr;
    textPickerAccessibilityPropertyNext_ = nullptr;
}

void TextPickerTestUpdateButton::InitTextPickerTestNg()
{
    frameNode_ = FrameNode::GetOrCreateFrameNode(V2::TEXT_PICKER_ETS_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<TextPickerPattern>(); });
    ASSERT_NE(frameNode_, nullptr);
    textPickerRowAccessibilityProperty_ = frameNode_->GetAccessibilityProperty<TextPickerRowAccessibilityProperty>();
    ASSERT_NE(textPickerRowAccessibilityProperty_, nullptr);
    textPickerPattern_ = frameNode_->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern_, nullptr);
    stackNode_ = FrameNode::GetOrCreateFrameNode(V2::STACK_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<StackPattern>(); });
    ASSERT_NE(stackNode_, nullptr);
    blendNode_ = FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(blendNode_, nullptr);
    columnNode_ = FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPickerColumnPattern>(); });
    ASSERT_NE(columnNode_, nullptr);
    textPickerAccessibilityProperty_ = columnNode_->GetAccessibilityProperty<TextPickerAccessibilityProperty>();
    ASSERT_NE(textPickerAccessibilityProperty_, nullptr);
    textPickerColumnPattern_ = columnNode_->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(textPickerColumnPattern_, nullptr);
    columnNode_->MountToParent(blendNode_);
    blendNode_->MountToParent(stackNode_);
    stackNode_->MountToParent(frameNode_);

    stackNodeNext_ = FrameNode::GetOrCreateFrameNode(V2::STACK_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<StackPattern>(); });
    ASSERT_NE(stackNodeNext_, nullptr);
    blendNodeNext_ = FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(blendNodeNext_, nullptr);
    columnNodeNext_ =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<TextPickerColumnPattern>(); });
    ASSERT_NE(columnNodeNext_, nullptr);
    textPickerAccessibilityPropertyNext_ = columnNode_->GetAccessibilityProperty<TextPickerAccessibilityProperty>();
    ASSERT_NE(textPickerAccessibilityPropertyNext_, nullptr);
    textPickerColumnPatternNext_ = columnNodeNext_->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(textPickerColumnPatternNext_, nullptr);
    columnNodeNext_->MountToParent(blendNodeNext_);
    blendNodeNext_->MountToParent(stackNodeNext_);
    stackNodeNext_->MountToParent(frameNode_);
}

void TextPickerTestUpdateButton::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
}

void TextPickerTestUpdateButton::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void TextPickerTestUpdateButton::SetUp()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        return GetTheme(type);
    });
    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([](ThemeType type, int32_t themeScopeId) -> RefPtr<Theme> { return GetTheme(type); });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void TextPickerTestUpdateButton::TearDown()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    ViewStackProcessor::GetInstance()->ClearStack();
}

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
/**
 * @tc.name: TextPickerDialogViewUpdateButtonStyles002
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestUpdateButton, TextPickerDialogViewUpdateButtonStyles002, TestSize.Level1)
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
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
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
    TextPickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval = layoutProperty->GetFontWeightValue();
    EXPECT_EQ(testval, FontWeight::W100);
    sizet++;
    TextPickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval2 = layoutProperty->GetFontWeightValue();
    EXPECT_EQ(testval2, FontWeight::W200);
    sizet++;
    TextPickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval3 = layoutProperty->GetFontWeightValue();
    EXPECT_EQ(testval3, FontWeight::W400);
}

/**
 * @tc.name: TextPickerDialogViewUpdateButtonStyles003
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestUpdateButton, TextPickerDialogViewUpdateButtonStyles003, TestSize.Level1)
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
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
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
    TextPickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval = layoutProperty->GetFontSizeValue();
    EXPECT_EQ(testval, Dimension(100));
}

/**
 * @tc.name: TextPickerDialogViewUpdateButtonStyles004
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestUpdateButton, TextPickerDialogViewUpdateButtonStyles004, TestSize.Level1)
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
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
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
    TextPickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);

    auto testval = layoutProperty->GetFontColorValue();
    EXPECT_EQ(testval, Color::BLACK);
}

/**
 * @tc.name: TextPickerDialogViewUpdateButtonStyles005
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestUpdateButton, TextPickerDialogViewUpdateButtonStyles005, TestSize.Level1)
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
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
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

    TextPickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    
    auto testval = layoutProperty->GetFontStyleValue();
    EXPECT_EQ(testval, Ace::FontStyle::ITALIC);
}

/**
 * @tc.name: TextPickerDialogViewUpdateButtonStyles006
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestUpdateButton, TextPickerDialogViewUpdateButtonStyles006, TestSize.Level1)
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
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
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

    TextPickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    
    auto testval = layoutProperty->GetTypeValue();
    EXPECT_EQ(testval, ButtonType::CIRCLE);
}

/**
 * @tc.name: TextPickerDialogViewUpdateButtonStyles007
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestUpdateButton, TextPickerDialogViewUpdateButtonStyles007, TestSize.Level1)
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
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
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

    TextPickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    
    auto testval = layoutProperty->GetButtonStyleValue();
    EXPECT_EQ(testval, ButtonStyleMode::EMPHASIZE);
}

/**
 * @tc.name: TextPickerDialogViewUpdateButtonStyles008
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestUpdateButton, TextPickerDialogViewUpdateButtonStyles008, TestSize.Level1)
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
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
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

    TextPickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    
    auto testval = layoutProperty->GetButtonRoleValue();
    EXPECT_EQ(testval, ButtonRole::ERROR);
}

/**
 * @tc.name: TextPickerDialogViewUpdateButtonStyles009
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestUpdateButton, TextPickerDialogViewUpdateButtonStyles009, TestSize.Level1)
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
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
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

    TextPickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval = layoutProperty->GetButtonRoleValue();
    EXPECT_EQ(testval, ButtonRole::ERROR);
    
    sizet++;
    TextPickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval2 = layoutProperty->GetButtonRoleValue();
    EXPECT_EQ(testval2, ButtonRole::NORMAL);
}

/**
 * @tc.name: TextPickerDialogViewUpdateButtonStyles010
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestUpdateButton, TextPickerDialogViewUpdateButtonStyles010, TestSize.Level1)
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
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
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

    TextPickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval = layoutProperty->GetButtonStyleValue();
    EXPECT_EQ(testval, ButtonStyleMode::EMPHASIZE);
    
    sizet++;
    TextPickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval2 = layoutProperty->GetButtonStyleValue();
    EXPECT_EQ(testval2, ButtonStyleMode::TEXT);
}

/**
 * @tc.name: TextPickerDialogViewUpdateButtonStyles011
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestUpdateButton, TextPickerDialogViewUpdateButtonStyles011, TestSize.Level1)
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
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
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

    TextPickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    
    auto testval = layoutProperty->GetTypeValue();
    EXPECT_EQ(testval, ButtonType::CIRCLE);

    sizet++;
    TextPickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    
    auto testval2 = layoutProperty->GetTypeValue();
    EXPECT_EQ(testval2, ButtonType::CAPSULE);
}

/**
 * @tc.name: TextPickerDialogViewUpdateButtonStyles012
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestUpdateButton, TextPickerDialogViewUpdateButtonStyles012, TestSize.Level1)
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
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
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

    TextPickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    
    auto testval = layoutProperty->GetFontStyleValue();
    EXPECT_EQ(testval, Ace::FontStyle::ITALIC);

    sizet++;
    TextPickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    
    auto testval2 = layoutProperty->GetFontStyleValue();
    EXPECT_EQ(testval2, Ace::FontStyle::NONE);
}

/**
 * @tc.name: TextPickerDialogViewUpdateButtonStyles013
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestUpdateButton, TextPickerDialogViewUpdateButtonStyles013, TestSize.Level1)
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
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
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

    TextPickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval = layoutProperty->GetFontStyleValue();
    EXPECT_EQ(testval, Ace::FontStyle::ITALIC);

    auto testval2 = layoutProperty->GetFontWeightValue();
    EXPECT_EQ(testval2, FontWeight::W500);

    auto testval3 = layoutProperty->GetFontColorValue();
    EXPECT_EQ(testval3, Color::BLACK);
}

/**
 * @tc.name: TextPickerDialogViewUpdateButtonStyles014
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestUpdateButton, TextPickerDialogViewUpdateButtonStyles014, TestSize.Level1)
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
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
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

    TextPickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval = layoutProperty->GetTypeValue();
    EXPECT_EQ(testval, ButtonType::CIRCLE);

    auto testval2 = layoutProperty->GetButtonStyleValue();
    EXPECT_EQ(testval2, ButtonStyleMode::EMPHASIZE);

    auto testval3 = layoutProperty->GetButtonRoleValue();
    EXPECT_EQ(testval3, ButtonRole::NORMAL);
}

/**
 * @tc.name: TextPickerDialogViewUpdateButtonStyles015
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestUpdateButton, TextPickerDialogViewUpdateButtonStyles015, TestSize.Level1)
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
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
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
    TextPickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval = layoutProperty->GetFontSizeValue();
    EXPECT_EQ(testval, Dimension(0));
}

/**
 * @tc.name: TextPickerDialogViewUpdateButtonStyles016
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestUpdateButton, TextPickerDialogViewUpdateButtonStyles016, TestSize.Level1)
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
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
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
    TextPickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval = layoutProperty->GetFontSizeValue();
    EXPECT_EQ(testval, Dimension(1));
}

/**
 * @tc.name: TextPickerDialogViewUpdateButtonStyles017
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestUpdateButton, TextPickerDialogViewUpdateButtonStyles017, TestSize.Level1)
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
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
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
    TextPickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval = layoutProperty->GetFontSizeValue();
    EXPECT_EQ(testval, Dimension(100));
}

/**
 * @tc.name: TextPickerDialogViewUpdateButtonStyles018
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestUpdateButton, TextPickerDialogViewUpdateButtonStyles018, TestSize.Level1)
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
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
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
    TextPickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval = layoutProperty->GetFontSizeValue();
    EXPECT_EQ(testval, Dimension(100));

    sizet++;
    TextPickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval2 = layoutProperty->GetFontSizeValue();
    EXPECT_EQ(testval2, Dimension(0));
}

/**
 * @tc.name: TextPickerDialogViewUpdateButtonStyles019
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestUpdateButton, TextPickerDialogViewUpdateButtonStyles019, TestSize.Level1)
{
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    ButtonInfo info2;
    info1.fontSize = Dimension(1);
    info2.fontSize = Dimension(100);
    buttonInfos.push_back(info1);
    buttonInfos.push_back(info2);
    size_t sizet = 0;

    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
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
    TextPickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval = layoutProperty->GetFontSizeValue();
    EXPECT_EQ(testval, Dimension(1));

    sizet++;
    TextPickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval2 = layoutProperty->GetFontSizeValue();
    EXPECT_EQ(testval2, Dimension(100));
}

/**
 * @tc.name: TextPickerDialogViewUpdateButtonStyles020
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestUpdateButton, TextPickerDialogViewUpdateButtonStyles020, TestSize.Level1)
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
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
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
    TextPickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval = layoutProperty->GetFontSizeValue();
    EXPECT_EQ(testval, Dimension(0));

    sizet++;
    TextPickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval2 = layoutProperty->GetFontSizeValue();
    EXPECT_EQ(testval2, Dimension(1));

    sizet++;
    TextPickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval3 = layoutProperty->GetFontSizeValue();
    EXPECT_EQ(testval3, Dimension(100));
}

/**
 * @tc.name: TextPickerDialogViewUpdateButtonStyles021
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestUpdateButton, TextPickerDialogViewUpdateButtonStyles021, TestSize.Level1)
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
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
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

    TextPickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval = layoutProperty->GetFontSizeValue();
    EXPECT_EQ(testval, Dimension(0));

    auto testval2 = layoutProperty->GetFontColorValue();
    EXPECT_EQ(testval2, Color::BLACK);
}

/**
 * @tc.name: TextPickerDialogViewUpdateButtonStyles022
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestUpdateButton, TextPickerDialogViewUpdateButtonStyles022, TestSize.Level1)
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
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
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

    TextPickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval = layoutProperty->GetFontSizeValue();
    EXPECT_EQ(testval, Dimension(1));

    auto testval2 = layoutProperty->GetFontColorValue();
    EXPECT_EQ(testval2, Color::GREEN);
}

/**
 * @tc.name: TextPickerDialogViewUpdateButtonStyles023
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestUpdateButton, TextPickerDialogViewUpdateButtonStyles023, TestSize.Level1)
{
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontSize = Dimension(100);
    info1.fontColor = Color::GRAY;
    buttonInfos.push_back(info1);
    size_t sizet = 0;

    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
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

    TextPickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval = layoutProperty->GetFontSizeValue();
    EXPECT_EQ(testval, Dimension(100));

    auto testval2 = layoutProperty->GetFontColorValue();
    EXPECT_EQ(testval2, Color::GRAY);
}

/**
 * @tc.name: TextPickerDialogViewUpdateButtonStyles024
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestUpdateButton, TextPickerDialogViewUpdateButtonStyles024, TestSize.Level1)
{
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    ButtonInfo info2;
    info1.fontSize = Dimension(100);
    info1.fontColor = Color::GRAY;
    info2.fontSize = Dimension(0);
    info2.fontColor = Color::FOREGROUND;
    buttonInfos.push_back(info1);
    buttonInfos.push_back(info2);
    size_t sizet = 0;

    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
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

    TextPickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval = layoutProperty->GetFontSizeValue();
    EXPECT_EQ(testval, Dimension(100));
    auto testval2 = layoutProperty->GetFontColorValue();
    EXPECT_EQ(testval2, Color::GRAY);

    sizet++;
    TextPickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval3 = layoutProperty->GetFontSizeValue();
    EXPECT_EQ(testval3, Dimension(0));
    auto testval4 = layoutProperty->GetFontColorValue();
    EXPECT_EQ(testval4, Color::FOREGROUND);
}

/**
 * @tc.name: TextPickerDialogViewUpdateButtonStyles025
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestUpdateButton, TextPickerDialogViewUpdateButtonStyles025, TestSize.Level1)
{
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    ButtonInfo info2;
    info1.fontSize = Dimension(100);
    info1.fontColor = Color::GRAY;
    info2.fontSize = Dimension(0);
    info2.fontColor = Color::FOREGROUND;
    buttonInfos.push_back(info1);
    size_t sizet = 0;

    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
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

    TextPickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval = layoutProperty->GetFontSizeValue();
    EXPECT_EQ(testval, Dimension(100));
    auto testval2 = layoutProperty->GetFontColorValue();
    EXPECT_EQ(testval2, Color::GRAY);

    sizet++;
    TextPickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval3 = layoutProperty->GetFontSizeValue();
    EXPECT_EQ(testval3, Dimension(100));
    auto testval4 = layoutProperty->GetFontColorValue();
    EXPECT_EQ(testval4, Color::GRAY);
}

/**
 * @tc.name: getRadius
 * @tc.desc: 提供TextPickerDialogViewUpdateButtonStyles026用例使用
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
 * @tc.name: TextPickerDialogViewUpdateButtonStyles026
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestUpdateButton, TextPickerDialogViewUpdateButtonStyles026, TestSize.Level1)
{
    Color colorVal = Color(0);
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    ButtonInfo info2;
    ButtonInfo info3;
    info1.fontSize = Dimension(1);
    info1.fontColor = Color::GRAY;
    info1.fontFamily = { "unknown" };
    info1.backgroundColor = colorVal;
    info1.borderRadius = getRadius();
    info2.fontSize = Dimension(0);
    info2.fontColor = Color::FOREGROUND;
    info3.fontSize = Dimension(100);
    info3.fontColor = Color::GREEN;
    buttonInfos.push_back(info1);
    buttonInfos.push_back(info2);
    buttonInfos.push_back(info3);
    size_t sizet = 0;
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
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
    TextPickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval = layoutProperty->GetFontSizeValue();
    EXPECT_EQ(testval, Dimension(1));
    auto testval2 = layoutProperty->GetFontColorValue();
    EXPECT_EQ(testval2, Color::GRAY);
    sizet++;
    TextPickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    sizet--;
    TextPickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval5 = layoutProperty->GetFontSizeValue();
    EXPECT_EQ(testval5, Dimension(1));
    auto testval6 = layoutProperty->GetFontColorValue();
    EXPECT_EQ(testval6, Color::GRAY);
}

// /**
//  * @tc.name: TextPickerDialogViewUpdateButtonStyleAndRole002
//  * @tc.desc: Test UpdateButtonStyleAndRole.
//  * @tc.type: FUNC
//  */
HWTEST_F(TextPickerTestUpdateButton, TextPickerDialogViewUpdateButtonStyleAndRole002, TestSize.Level1)
{
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.type = std::make_optional<ButtonType>(ButtonType::TEXT);
    info1.buttonStyle = ButtonStyleMode::NORMAL;
    info1.role = ButtonRole::ERROR;
    buttonInfos.push_back(info1);

    size_t sizet = 0;

    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
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

    TextPickerDialogView::UpdateButtonStyleAndRole(buttonInfos, sizet, layoutProperty, renderContext, buttonTheme);

    auto testval = layoutProperty->GetButtonRoleValue();
    EXPECT_EQ(testval, ButtonRole::ERROR);
}

// /**
//  * @tc.name: TextPickerDialogViewUpdateButtonStyleAndRole001
//  * @tc.desc: Test UpdateButtonStyleAndRole.
//  * @tc.type: FUNC
//  */
HWTEST_F(TextPickerTestUpdateButton, TextPickerDialogViewUpdateButtonStyleAndRole001, TestSize.Level1)
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
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
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

    TextPickerDialogView::UpdateButtonStyleAndRole(buttonInfos, sizet, layoutProperty, renderContext, buttonTheme);

    auto testval = layoutProperty->GetButtonRoleValue();
    EXPECT_EQ(testval, ButtonRole::NORMAL);
}
} // namespace OHOS::Ace::NG
