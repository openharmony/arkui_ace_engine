/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/picker/picker_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/divider/divider_pattern.h"
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

class TextPickerTestUpdate : public testing::Test {
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

void TextPickerTestUpdate::DestroyTextPickerTestNgObject()
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

void TextPickerTestUpdate::InitTextPickerTestNg()
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

void TextPickerTestUpdate::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
}

void TextPickerTestUpdate::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void TextPickerTestUpdate::SetUp()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        return GetTheme(type);
    });
    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([](ThemeType type, int32_t themeScopeId) -> RefPtr<Theme> { return GetTheme(type); });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void TextPickerTestUpdate::TearDown()
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
 * @tc.name: TextPickerDialogViewShow0013
 * @tc.desc: Test TextPickerDialogView Show(column kind is invalid).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestUpdate, TextPickerDialogViewShow0013, TestSize.Level1)
{
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;

    TextPickerSettingData settingData;
    settingData.columnKind = 0;
    settingData.height = Dimension(10.0);
    settingData.selected = 0;

    DialogProperties dialogProperties;
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(0);
    std::map<std::string, NG::DialogTextEvent> dialogEvent;
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontWeight = FontWeight::W100;
    buttonInfos.push_back(info1);

    auto frameNode =
        TextPickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    EXPECT_EQ(frameNode, nullptr);
}

/**
 * @tc.name: TextPickerDialogViewShow0014
 * @tc.desc: Test TextPickerDialogView Show(column kind is invalid).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestUpdate, TextPickerDialogViewShow0014, TestSize.Level1)
{
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;

    TextPickerSettingData settingData;
    settingData.columnKind = 0;
    settingData.height = Dimension(10.0);
    settingData.rangeVector = { { "", "1" }, { "", "2" }, { "", "3" } };
    settingData.canLoop = false;
    settingData.selected = 0;

    DialogProperties dialogProperties;
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(0);
    std::map<std::string, NG::DialogTextEvent> dialogEvent;
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontWeight = FontWeight::W100;
    buttonInfos.push_back(info1);

    auto frameNode =
        TextPickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);

    ASSERT_NE(frameNode, nullptr);
}

/**
 * @tc.name: TextPickerDialogViewCreateAgingButtonNode001
 * @tc.desc: Test CreateAgingButtonNode
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestUpdate, TextPickerDialogViewCreateAgingButtonNode001, TestSize.Level1)
{
    /**
     * @tc.step: step1. create frameNode.
     */
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_PICKER_ETS_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<TextPickerPattern>(); });
    ASSERT_NE(frameNode, nullptr);

    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontColor = Color::BLACK;
    buttonInfos.push_back(info1);
    std::map<std::string, NG::DialogTextEvent> dialogEvent;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    auto moveForwardFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogMoveForwardEvent;
    dialogMoveForwardEvent["moveForwardId"] = moveForwardFunc;
    auto moveBackwardFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogMoveBackwardEvent;
    dialogMoveBackwardEvent["moveBackwardId"] = moveBackwardFunc;
    auto closeCallback = [](const GestureEvent& info) { (void)info; };
    auto nextCallBack = [](const GestureEvent& info) { (void)info; };
    auto previousCallBack = [](const GestureEvent& info) { (void)info; };
    /**
     * @tc.step: step2. call CreateAgingButtonNode.
     * @tc.expected: contentRow is successfully created.
     */
    auto contentRow =
        TextPickerDialogView::CreateAgingButtonNode(frameNode, buttonInfos, dialogEvent, dialogCancelEvent,
            dialogMoveForwardEvent, dialogMoveBackwardEvent, closeCallback, nextCallBack, previousCallBack);
    ASSERT_NE(contentRow, nullptr);
}

/**
 * @tc.name: TextPickerDialogViewSetSingleDividerNodeActive001
 * @tc.desc: Test SetSingleDividerNodeActive
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestUpdate, TextPickerDialogViewSetSingleDividerNodeActive001, TestSize.Level1)
{
    /**
     * @tc.step: step1. create dividerNode.
     */
    auto dividerNode = FrameNode::GetOrCreateFrameNode(V2::DIVIDER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<DividerPattern>(); });
    ASSERT_NE(dividerNode, nullptr);
    /**
     * @tc.step: step2. call SetSingleDividerNodeActive and dividerActive is true.
     * @tc.expected: Visibility is VISIBLE.
     */
    auto dividerLayoutProperty = dividerNode->GetLayoutProperty<LayoutProperty>();
    TextPickerDialogView::SetSingleDividerNodeActive(dividerNode, true);
    EXPECT_EQ(dividerLayoutProperty->GetVisibility(), VisibleType::VISIBLE);
    /**
     * @tc.step: step3. call SetSingleDividerNodeActive and dividerActive is false.
     * @tc.expected: Visibility is GONE.
     */
    TextPickerDialogView::SetSingleDividerNodeActive(dividerNode, false);
    EXPECT_EQ(dividerLayoutProperty->GetVisibility(), VisibleType::GONE);
}

/**
 * @tc.name: TextPickerDialogViewUpdateForwardButtonMargin001
 * @tc.desc: Test UpdateForwardButtonMargin
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestUpdate, TextPickerDialogViewUpdateForwardButtonMargin001, TestSize.Level1)
{
    /**
     * @tc.step: step1. create buttonForwardNode.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<DialogTheme>();
    ASSERT_NE(theme, nullptr);
    InitTextPickerTestNg();
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontColor = Color::BLACK;
    buttonInfos.push_back(info1);
    auto moveForwardFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogMoveForwardEvent;
    dialogMoveForwardEvent["moveForwardId"] = moveForwardFunc;
    auto moveForwardEvent = dialogMoveForwardEvent["moveForwardId"];
    auto buttonForwardNode = TextPickerDialogView::CreateForwardNode(moveForwardEvent, frameNode_, buttonInfos);
    ASSERT_NE(buttonForwardNode, nullptr);
    /**
     * @tc.step: step2. call UpdateForwardButtonMargin.
     * @tc.expected: margin_ is not null.
     */
    TextPickerDialogView::UpdateForwardButtonMargin(buttonForwardNode, theme);
    EXPECT_NE(buttonForwardNode->GetLayoutProperty()->margin_, nullptr);
}

/**
 * @tc.name: TextPickerDialogViewUpdateForwardButtonMargin002
 * @tc.desc: Test UpdateForwardButtonMargin
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestUpdate, TextPickerDialogViewUpdateForwardButtonMargin002, TestSize.Level1)
{
    /**
     * @tc.step: step1. create buttonForwardNode and set API version 12.
     */
    int32_t settingApiVersion = 12;
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<DialogTheme>();
    ASSERT_NE(theme, nullptr);
    InitTextPickerTestNg();
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontColor = Color::BLACK;
    buttonInfos.push_back(info1);
    auto moveForwardFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogMoveForwardEvent;
    dialogMoveForwardEvent["moveForwardId"] = moveForwardFunc;
    auto moveForwardEvent = dialogMoveForwardEvent["moveForwardId"];
    auto buttonForwardNode = TextPickerDialogView::CreateForwardNode(moveForwardEvent, frameNode_, buttonInfos);
    ASSERT_NE(buttonForwardNode, nullptr);
    /**
     * @tc.step: step2. call UpdateForwardButtonMargin.
     * @tc.expected: margin_ is not null.
     */
    TextPickerDialogView::UpdateForwardButtonMargin(buttonForwardNode, theme);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
    EXPECT_NE(buttonForwardNode->GetLayoutProperty()->margin_, nullptr);
}

/**
 * @tc.name: TextPickerDialogViewUpdateBackwardButtonMargin001
 * @tc.desc: Test UpdateBackwardButtonMargin
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestUpdate, TextPickerDialogViewUpdateBackwardButtonMargin001, TestSize.Level1)
{
    /**
     * @tc.step: step1. create buttonBackwardNode.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<DialogTheme>();
    ASSERT_NE(theme, nullptr);
    InitTextPickerTestNg();
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontColor = Color::BLACK;
    buttonInfos.push_back(info1);
    auto moveBackwardFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogMoveBackwardEvent;
    dialogMoveBackwardEvent["moveBackwardId"] = moveBackwardFunc;
    auto moveBackwardEvent = dialogMoveBackwardEvent["moveBackwardId"];
    auto buttonBackwardNode = TextPickerDialogView::CreateBackwardNode(moveBackwardEvent, frameNode_, buttonInfos);
    ASSERT_NE(buttonBackwardNode, nullptr);
    /**
     * @tc.step: step2. call UpdateForwardButtonMargin.
     * @tc.expected: margin_ is not null.
     */
    TextPickerDialogView::UpdateBackwardButtonMargin(buttonBackwardNode, theme);
    EXPECT_NE(buttonBackwardNode->GetLayoutProperty()->margin_, nullptr);
}

/**
 * @tc.name: TextPickerDialogViewUpdateBackwardButtonMargin002
 * @tc.desc: Test UpdateBackwardButtonMargin
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestUpdate, TextPickerDialogViewUpdateBackwardButtonMargin002, TestSize.Level1)
{
    /**
     * @tc.step: step1. create buttonBackwardNode and set API version 12.
     */
    int32_t settingApiVersion = 12;
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<DialogTheme>();
    ASSERT_NE(theme, nullptr);
    InitTextPickerTestNg();
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontColor = Color::BLACK;
    buttonInfos.push_back(info1);
    auto moveBackwardFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogMoveBackwardEvent;
    dialogMoveBackwardEvent["moveBackwardId"] = moveBackwardFunc;
    auto moveBackwardEvent = dialogMoveBackwardEvent["moveBackwardId"];
    auto buttonBackwardNode = TextPickerDialogView::CreateBackwardNode(moveBackwardEvent, frameNode_, buttonInfos);
    ASSERT_NE(buttonBackwardNode, nullptr);
    /**
     * @tc.step: step2. call UpdateForwardButtonMargin.
     * @tc.expected: margin_ is not null.
     */
    TextPickerDialogView::UpdateBackwardButtonMargin(buttonBackwardNode, theme);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
    EXPECT_NE(buttonBackwardNode->GetLayoutProperty()->margin_, nullptr);
}

/*
 * @tc.name: UpdateForwardButtonMargin001
 * @tc.desc: Test TextPickerDialogView UpdateForwardButtonMargin
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestUpdate, UpdateForwardButtonMargin001, TestSize.Level1)
{
    auto buttonForwardNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto pipeline = PipelineContext::GetCurrentContext();
    auto dialogTheme = pipeline->GetTheme<DialogTheme>();
    TextPickerDialogView::UpdateForwardButtonMargin(buttonForwardNode, dialogTheme);
    EXPECT_NE(buttonForwardNode->GetLayoutProperty()->margin_, nullptr);
}

/**
 * @tc.name: DialogViewUpdateButtonBackwardLayoutProperty001
 * @tc.desc: Test UpdateButtonBackwardLayoutProperty
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestUpdate, DialogViewUpdateButtonBackwardLayoutProperty001, TestSize.Level1)
{
    int32_t settingApiVersion = 14;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    auto pipelineContext = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipelineContext, nullptr);

    /**
     * @tc.step: step1. create buttonBackwardNode.
     */
    InitTextPickerTestNg();
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info;
    info.fontColor = Color::BLACK;
    buttonInfos.push_back(info);

    auto moveBackwardFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogMoveBackwardEvent;
    dialogMoveBackwardEvent["moveBackwardId"] = moveBackwardFunc;
    auto moveBackwardEvent = dialogMoveBackwardEvent["moveBackwardId"];

    ASSERT_NE(frameNode_, nullptr);
    auto buttonBackwardNode = TextPickerDialogView::CreateBackwardNode(moveBackwardEvent, frameNode_, buttonInfos);
    ASSERT_NE(buttonBackwardNode, nullptr);
    auto buttonBackwardLayoutProperty = buttonBackwardNode->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(buttonBackwardLayoutProperty, nullptr);

    /**
     * @tc.step: step2. call UpdateButtonForwardLayoutProperty.
     * @tc.expected: ButtonType is CAPSULE.
     */
    TextPickerDialogView::UpdateButtonBackwardLayoutProperty(buttonBackwardNode, pipelineContext);
    EXPECT_EQ(buttonBackwardLayoutProperty->GetType(), ButtonType::CAPSULE);
}

/**
 * @tc.name: DialogViewUpdateButtonForwardLayoutProperty001
 * @tc.desc: Test UpdateButtonForwardLayoutProperty
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestUpdate, DialogViewUpdateButtonForwardLayoutProperty001, TestSize.Level1)
{
    int32_t settingApiVersion = 14;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    auto pipelineContext = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipelineContext, nullptr);

    /**
     * @tc.step: step1. create buttonForwardNode.
     */
    InitTextPickerTestNg();
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info;
    info.fontColor = Color::BLACK;
    buttonInfos.push_back(info);

    auto moveForwardFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogMoveForwardEvent;
    dialogMoveForwardEvent["moveForwardId"] = moveForwardFunc;
    auto moveForwardEvent = dialogMoveForwardEvent["moveForwardId"];

    ASSERT_NE(frameNode_, nullptr);
    auto buttonForwardNode = TextPickerDialogView::CreateForwardNode(moveForwardEvent, frameNode_, buttonInfos);
    ASSERT_NE(buttonForwardNode, nullptr);
    auto buttonForwardLayoutProperty = buttonForwardNode->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(buttonForwardLayoutProperty, nullptr);

    /**
     * @tc.step: step2. call UpdateButtonForwardLayoutProperty.
     * @tc.expected: ButtonType is CAPSULE.
     */
    TextPickerDialogView::UpdateButtonForwardLayoutProperty(buttonForwardNode, pipelineContext);
    EXPECT_EQ(buttonForwardLayoutProperty->GetType(), ButtonType::CAPSULE);
}

/**
 * @tc.name: DialogViewUpdateButtonCancelLayoutProperty001
 * @tc.desc: Test UpdateButtonCancelLayoutProperty
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestUpdate, DialogViewUpdateButtonCancelLayoutProperty001, TestSize.Level1)
{
    int32_t settingApiVersion = 14;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    auto pipelineContext = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipelineContext, nullptr);

    /**
     * @tc.step: step1. create cancelNode.
     */
    InitTextPickerTestNg();
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info;
    info.fontColor = Color::BLACK;
    buttonInfos.push_back(info);

    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    auto cancelEvent = dialogCancelEvent["cancelId"];

    ASSERT_NE(frameNode_, nullptr);
    auto cancelNode = TextPickerDialogView::CreateCancelNode(cancelEvent, frameNode_, buttonInfos);
    ASSERT_NE(cancelNode, nullptr);
    auto buttonCancelLayoutProperty = cancelNode->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(buttonCancelLayoutProperty, nullptr);

    /**
     * @tc.step: step2. call UpdateButtonCancelLayoutProperty.
     * @tc.expected: ButtonType is CAPSULE.
     */
    TextPickerDialogView::UpdateButtonCancelLayoutProperty(cancelNode, pipelineContext);
    EXPECT_EQ(buttonCancelLayoutProperty->GetType(), ButtonType::CAPSULE);
}

/**
 * @tc.name: DialogViewUpdateButtonConfirmLayoutProperty001
 * @tc.desc: Test UpdateButtonConfirmLayoutProperty
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestUpdate, DialogViewUpdateButtonConfirmLayoutProperty001, TestSize.Level1)
{
    int32_t settingApiVersion = 14;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;

    /**
     * @tc.step: step1. create confirmNode.
     */
    InitTextPickerTestNg();
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info;
    info.fontColor = Color::BLACK;
    buttonInfos.push_back(info);

    auto func = [](const std::string& /* info */) {};
    std::map<std::string, NG::DialogTextEvent> dialogEvent;
    dialogEvent["acceptId"] = func;
    auto acceptEvent = dialogEvent["acceptId"];

    ASSERT_NE(frameNode_, nullptr);
    auto buttonConfirmNode = TextPickerDialogView::CreateConfirmNode(frameNode_, frameNode_, buttonInfos, acceptEvent);
    ASSERT_NE(buttonConfirmNode, nullptr);
    auto buttonConfirmLayoutProperty = buttonConfirmNode->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(buttonConfirmLayoutProperty, nullptr);

    /**
     * @tc.step: step2. call UpdateButtonConfirmLayoutProperty.
     * @tc.expected: ButtonType is CAPSULE.
     */
    TextPickerDialogView::UpdateButtonConfirmLayoutProperty(buttonConfirmNode, theme);
    EXPECT_EQ(buttonConfirmLayoutProperty->GetType(), ButtonType::CAPSULE);
}

/**
 * @tc.name: UpdateButtonDefaultFocus001
 * @tc.desc: Test UpdateButtonDefaultFocus
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestUpdate, UpdateButtonDefaultFocus001, TestSize.Level1)
{
    /**
     * @tc.step: step1. create confirmNode.
     */
    InitTextPickerTestNg();
    std::vector<ButtonInfo> buttonInfos;

    ButtonInfo info1;
    info1.isPrimary = true;
    buttonInfos.push_back(info1);
    ButtonInfo info2;
    info2.isPrimary = true;
    buttonInfos.push_back(info2);

    auto func = [](const std::string& /* info */) {};
    std::map<std::string, NG::DialogTextEvent> dialogEvent;
    dialogEvent["acceptId"] = func;
    auto acceptEvent = dialogEvent["acceptId"];

    ASSERT_NE(frameNode_, nullptr);
    auto buttonConfirmNode = TextPickerDialogView::CreateConfirmNode(frameNode_, frameNode_, buttonInfos, acceptEvent);
    ASSERT_NE(buttonConfirmNode, nullptr);

    auto focusHub = buttonConfirmNode->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);

    buttonInfos[0].isPrimary = false;
    TextPickerDialogView::UpdateButtonDefaultFocus(buttonInfos, buttonConfirmNode, true);
    EXPECT_FALSE(focusHub->IsDefaultFocus());

    buttonInfos[1].isPrimary = false;
    TextPickerDialogView::UpdateButtonDefaultFocus(buttonInfos, buttonConfirmNode, true);
    EXPECT_FALSE(focusHub->IsDefaultFocus());

    TextPickerDialogView::UpdateButtonDefaultFocus(buttonInfos, nullptr, true);
    EXPECT_FALSE(focusHub->IsDefaultFocus());

    buttonInfos[0].isPrimary = true;
    TextPickerDialogView::UpdateButtonDefaultFocus(buttonInfos, nullptr, true);
    EXPECT_FALSE(focusHub->IsDefaultFocus());
}

/**
 * @tc.name: SetDialogButtonActive001
 * @tc.desc: Test TextPickerDialogView SetDialogButtonActive
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestUpdate, SetDialogButtonActive001, TestSize.Level1)
{
    auto contentColumn = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    TextPickerDialogView::SetDialogButtonActive(contentColumn, 0, 0);
    EXPECT_EQ(contentColumn->GetLastChild(), nullptr);
}

/**
 * @tc.name: SeparatedOptionsShow001
 * @tc.desc: Test TextPickerDialogView SeparatedOptionsShow
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestUpdate, SeparatedOptionsShow001, TestSize.Level1)
{
    InitTextPickerTestNg();
    auto contentColumn = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    frameNode_->MountToParent(contentColumn);
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontWeight = FontWeight::W100;
    buttonInfos.push_back(info1);
    auto textNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textPickerNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXT_PICKER_ETS_TAG, textNodeId, []() { return AceType::MakeRefPtr<TextPickerPattern>(); });
    TextPickerSettingData settingData;
    settingData.columnKind = 0;
    settingData.height = Dimension(10.0);
    settingData.selected = 0;
    std::map<std::string, NG::DialogTextEvent> dialogEvent;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    float scale = 1.00;
    auto closeCallback = [](const GestureEvent& info) { (void)info; };

    RefPtr<FrameNode> dialogNode = TextPickerDialogView::SeparatedOptionsShow(contentColumn, textPickerNode,
        buttonInfos, settingData, dialogEvent, dialogCancelEvent, scale, closeCallback, frameNode_);
    ASSERT_NE(dialogNode, nullptr);
}

/**
 * @tc.name: SetRange001
 * @tc.desc: Test TextPickerModelNG SetRange
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestUpdate, SetRange001, TestSize.Level1)
{
    std::vector<NG::RangeContent> range = { { "", "1" }, { "", "2" }, { "", "3" } };
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    TextPickerModelNG::SetRange(frameNode, range);
    ASSERT_FALSE(frameNode->GetPattern<TextPickerPattern>()->GetRange().empty());
}

/**
 * @tc.name: SetValue001
 * @tc.desc: Test TextPickerModelNG SetValue
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestUpdate, SetValue001, TestSize.Level1)
{
    std::string value = "";
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    TextPickerModelNG::SetValue(frameNode, value);
    EXPECT_EQ(frameNode->GetPattern<TextPickerPattern>()->GetSelected(), 0);
}

/**
 * @tc.name: SetValues001
 * @tc.desc: Test TextPickerModelNG SetValues
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestUpdate, SetValues001, TestSize.Level1)
{
    std::vector<std::string> value;
    value.push_back("1");
    value.push_back("2");
    value.push_back("3");
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    TextPickerModelNG::SetValues(frameNode, value);
    EXPECT_EQ(frameNode->GetPattern<TextPickerPattern>()->GetSelected(), 0);
}
} // namespace OHOS::Ace::NG
