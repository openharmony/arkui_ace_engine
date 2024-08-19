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
#include "test/mock/core/rosen/mock_canvas.h"

#include "base/geometry/dimension.h"
#include "base/geometry/ng/size_t.h"
#include "base/i18n/localization.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/measure_util.h"
#include "core/components/picker/picker_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_picker/textpicker_column_pattern.h"
#include "core/components_ng/pattern/text_picker/textpicker_dialog_view.h"
#include "core/components_ng/pattern/text_picker/textpicker_model.h"
#include "core/components_ng/pattern/text_picker/textpicker_model_ng.h"
#include "core/components_ng/pattern/text_picker/textpicker_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline_ng/ui_task_scheduler.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
std::unique_ptr<TextPickerModel> TextPickerModel::textPickerInstance_ = nullptr;
std::unique_ptr<TextPickerDialogModel> TextPickerDialogModel::textPickerDialogInstance_ = nullptr;

TextPickerModel* TextPickerModel::GetInstance()
{
    if (!textPickerInstance_) {
        if (!textPickerInstance_) {
            textPickerInstance_.reset(new NG::TextPickerModelNG());
        }
    }
    return textPickerInstance_.get();
}

TextPickerDialogModel* TextPickerDialogModel::GetInstance()
{
    if (!textPickerDialogInstance_) {
        if (!textPickerDialogInstance_) {
            textPickerDialogInstance_.reset(new NG::TextPickerDialogModelNG());
        }
    }
    return textPickerDialogInstance_.get();
}
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t BUFFER_NODE_NUMBER = 2;
constexpr size_t FIVE_CHILDREN = 5;
constexpr size_t THREE = 3;
constexpr uint32_t SELECTED_INDEX_1 = 1;
constexpr double FONT_SIZE_10 = 10.0;
constexpr double FONT_SIZE_INVALID = -1.0;
const std::string EMPTY_TEXT = "";
const std::string TEXT_PICKER_CONTENT = "text";
const OffsetF CHILD_OFFSET(0.0f, 10.0f);
const SizeF TEST_TEXT_FRAME_SIZE { 100.0f, 10.0f };
const SizeF COLUMN_SIZE { 100.0f, 200.0f };
const Dimension ICON_TEXT_SPACE = 8.0_vp;
} // namespace

class TextPickerTestNg : public testing::Test {
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

void TextPickerTestNg::DestroyTextPickerTestNgObject()
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

void TextPickerTestNg::InitTextPickerTestNg()
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

void TextPickerTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
}

void TextPickerTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void TextPickerTestNg::SetUp()
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

void TextPickerTestNg::TearDown()
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
 * @tc.name: TextPickerDialogViewShow001
 * @tc.desc: Test TextPickerDialogView Show(column kind is MIXTURE).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerDialogViewShow001, TestSize.Level1)
{
    PickerTextProperties properties;
    properties.disappearTextStyle_.textColor = Color::RED;
    properties.disappearTextStyle_.fontSize = Dimension(FONT_SIZE_10);
    properties.disappearTextStyle_.fontWeight = Ace::FontWeight::BOLD;

    properties.normalTextStyle_.textColor = Color::RED;
    properties.normalTextStyle_.fontSize = Dimension(FONT_SIZE_10);
    properties.normalTextStyle_.fontWeight = Ace::FontWeight::BOLD;

    properties.selectedTextStyle_.textColor = Color::RED;
    properties.selectedTextStyle_.fontSize = Dimension(FONT_SIZE_10);
    properties.normalTextStyle_.fontWeight = Ace::FontWeight::BOLD;

    auto func = [](const std::string& info) { (void)info; };
    std::map<std::string, NG::DialogTextEvent> dialogEvent;
    dialogEvent["changeId"] = func;
    dialogEvent["acceptId"] = func;

    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;

    TextPickerSettingData settingData;
    settingData.columnKind = MIXTURE;
    settingData.height = Dimension(FONT_SIZE_10);
    settingData.properties = properties;
    settingData.rangeVector = { { "", "1" }, { "", "2" }, { "", "3" } };
    settingData.selected = 0;

    DialogProperties dialogProperties;
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    std::vector<ButtonInfo> buttonInfos;
    auto frameNode =
        TextPickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(frameNode, nullptr);
}

/**
 * @tc.name: TextPickerDialogViewShow002
 * @tc.desc: Test TextPickerDialogView Show(do not set callback).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerDialogViewShow002, TestSize.Level1)
{
    PickerTextProperties properties;
    properties.disappearTextStyle_.textColor = Color::RED;
    properties.disappearTextStyle_.fontSize = Dimension(FONT_SIZE_10);
    properties.disappearTextStyle_.fontWeight = Ace::FontWeight::BOLD;

    properties.normalTextStyle_.textColor = Color::RED;
    properties.normalTextStyle_.fontSize = Dimension(FONT_SIZE_10);
    properties.normalTextStyle_.fontWeight = Ace::FontWeight::BOLD;

    properties.selectedTextStyle_.textColor = Color::RED;
    properties.selectedTextStyle_.fontSize = Dimension(FONT_SIZE_10);
    properties.normalTextStyle_.fontWeight = Ace::FontWeight::BOLD;

    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;

    TextPickerSettingData settingData;
    settingData.columnKind = MIXTURE;
    settingData.height = Dimension(FONT_SIZE_10);
    settingData.properties = properties;
    settingData.rangeVector = { { "", "1" }, { "", "2" }, { "", "3" } };
    settingData.selected = 0;

    DialogProperties dialogProperties;
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(0);
    std::map<std::string, NG::DialogTextEvent> dialogEvent;
    std::vector<ButtonInfo> buttonInfos;
    auto frameNode =
        TextPickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(frameNode, nullptr);
}

/**
 * @tc.name: TextPickerDialogViewShow003
 * @tc.desc: Test TextPickerDialogView Show(do not set properties).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerDialogViewShow003, TestSize.Level1)
{
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;

    TextPickerSettingData settingData;
    settingData.columnKind = MIXTURE;
    settingData.height = Dimension(FONT_SIZE_10);
    settingData.rangeVector = { { "", "1" }, { "", "2" }, { "", "3" } };
    settingData.selected = 0;

    DialogProperties dialogProperties;
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(0);
    std::map<std::string, NG::DialogTextEvent> dialogEvent;
    std::vector<ButtonInfo> buttonInfos;
    auto frameNode =
        TextPickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(frameNode, nullptr);
}

/**
 * @tc.name: TextPickerDialogViewShow004
 * @tc.desc: Test TextPickerDialogView Show(column kind is TEXT).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerDialogViewShow004, TestSize.Level1)
{
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;

    TextPickerSettingData settingData;
    settingData.columnKind = TEXT;
    settingData.height = Dimension(FONT_SIZE_10);
    settingData.rangeVector = { { "", "1" }, { "", "2" }, { "", "3" } };
    settingData.selected = 0;

    DialogProperties dialogProperties;
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(0);
    std::map<std::string, NG::DialogTextEvent> dialogEvent;
    std::vector<ButtonInfo> buttonInfos;
    auto frameNode =
        TextPickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(frameNode, nullptr);
}

/**
 * @tc.name: TextPickerDialogViewShow005
 * @tc.desc: Test TextPickerDialogView Show(column kind is ICON).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerDialogViewShow005, TestSize.Level1)
{
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;

    TextPickerSettingData settingData;
    settingData.columnKind = ICON;
    settingData.height = Dimension(FONT_SIZE_10);
    settingData.rangeVector = { { "", "1" }, { "", "2" }, { "", "3" } };
    settingData.selected = 0;

    DialogProperties dialogProperties;
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(0);
    std::map<std::string, NG::DialogTextEvent> dialogEvent;
    std::vector<ButtonInfo> buttonInfos;
    auto frameNode =
        TextPickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(frameNode, nullptr);
}

/**
 * @tc.name: TextPickerDialogViewShow006
 * @tc.desc: Test TextPickerDialogView Show(column kind is invalid).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerDialogViewShow006, TestSize.Level1)
{
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;

    TextPickerSettingData settingData;
    settingData.columnKind = 0;
    settingData.height = Dimension(FONT_SIZE_10);
    settingData.rangeVector = { { "", "1" }, { "", "2" }, { "", "3" } };
    settingData.selected = 0;

    DialogProperties dialogProperties;
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(0);
    std::map<std::string, NG::DialogTextEvent> dialogEvent;
    std::vector<ButtonInfo> buttonInfos;
    auto frameNode =
        TextPickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(frameNode, nullptr);
}

/**
 * @tc.name: TextPickerDialogViewShow007
 * @tc.desc: Test TextPickerDialogView Show(Invailid font size).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerDialogViewShow007, TestSize.Level1)
{
    PickerTextProperties properties;
    properties.disappearTextStyle_.textColor = Color::RED;
    properties.disappearTextStyle_.fontSize = Dimension(FONT_SIZE_INVALID);
    properties.disappearTextStyle_.fontWeight = Ace::FontWeight::BOLD;

    properties.normalTextStyle_.textColor = Color::RED;
    properties.normalTextStyle_.fontSize = Dimension(FONT_SIZE_INVALID);
    properties.normalTextStyle_.fontWeight = Ace::FontWeight::BOLD;

    properties.selectedTextStyle_.textColor = Color::RED;
    properties.selectedTextStyle_.fontSize = Dimension(FONT_SIZE_INVALID);
    properties.normalTextStyle_.fontWeight = Ace::FontWeight::BOLD;

    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;

    TextPickerSettingData settingData;
    settingData.columnKind = MIXTURE;
    settingData.height = Dimension(FONT_SIZE_10);
    settingData.properties = properties;
    settingData.rangeVector = { { "", "1" }, { "", "2" }, { "", "3" } };
    settingData.selected = 0;

    DialogProperties dialogProperties;
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(0);
    std::map<std::string, NG::DialogTextEvent> dialogEvent;
    std::vector<ButtonInfo> buttonInfos;
    auto frameNode =
        TextPickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(frameNode, nullptr);
}

/**
 * @tc.name: TextPickerDialogViewShow008
 * @tc.desc: Test TextPickerDialogView Show(Multi Column).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerDialogViewShow008, TestSize.Level1)
{
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;

    TextPickerSettingData settingData;
    settingData.columnKind = TEXT;
    settingData.height = Dimension(FONT_SIZE_10);
    settingData.selectedValues = { 0, 0, 0 };
    settingData.attr.isCascade = false;
    /**
     * @tc.step: step1. create multi TextCascadePickerOptions of settingData
     */
    NG::TextCascadePickerOptions options1;
    options1.rangeResult = { "11", "12", "13" };
    settingData.options.emplace_back(options1);
    NG::TextCascadePickerOptions options2;
    options2.rangeResult = { "21", "22", "23" };
    settingData.options.emplace_back(options2);
    NG::TextCascadePickerOptions options3;
    options3.rangeResult = { "31", "32", "33" };
    settingData.options.emplace_back(options3);
    DialogProperties dialogProperties;
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(0);
    std::map<std::string, NG::DialogTextEvent> dialogEvent;
    /**
     * @tc.step: step2. call Show of TextPickerDialogView
     * @tc.expected: the function of show can generate framenode.
     */
    std::vector<ButtonInfo> buttonInfos;
    auto frameNode =
        TextPickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(frameNode, nullptr);
}

/**
 * @tc.name: TextPickerDialogViewShow009
 * @tc.desc: Test TextPickerDialogView Show(Cascade Column).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerDialogViewShow009, TestSize.Level1)
{
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;

    TextPickerSettingData settingData;
    settingData.columnKind = TEXT;
    settingData.height = Dimension(FONT_SIZE_10);
    settingData.selectedValues = { 0, 0 };
    settingData.attr.isCascade = true;
    /**
     * @tc.step: step1. create cascade TextCascadePickerOptions of settingData
     */
    NG::TextCascadePickerOptions options1;
    NG::TextCascadePickerOptions options1Child;
    options1Child.rangeResult = { "11", "12" };
    options1.rangeResult = { "1" };
    options1.children.emplace_back(options1Child);
    settingData.options.emplace_back(options1);
    NG::TextCascadePickerOptions options2;
    NG::TextCascadePickerOptions options2Child;
    options2Child.rangeResult = { "21", "22" };
    options2.rangeResult = { "2" };
    options2.children.emplace_back(options2Child);
    settingData.options.emplace_back(options2);
    NG::TextCascadePickerOptions options3;
    NG::TextCascadePickerOptions options3Child;
    options3Child.rangeResult = { "31", "32" };
    options3.rangeResult = { "3" };
    options3.children.emplace_back(options3Child);
    settingData.options.emplace_back(options3);
    DialogProperties dialogProperties;
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(0);
    std::map<std::string, NG::DialogTextEvent> dialogEvent;
    /**
     * @tc.step: step2. call Show of TextPickerDialogView
     * @tc.expected: the function of show can generate framenode.
     */
    std::vector<ButtonInfo> buttonInfos;
    auto frameNode =
        TextPickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(frameNode, nullptr);
}

/**
 * @tc.name: TextPickerDialogViewShow010
 * @tc.desc: Test TextPickerDialogView Show(Cascade Column Supply Zero Child).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerDialogViewShow010, TestSize.Level1)
{
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;

    TextPickerSettingData settingData;
    settingData.columnKind = TEXT;
    settingData.height = Dimension(FONT_SIZE_10);
    settingData.selectedValues = { 0, 0, 0 };
    settingData.attr.isCascade = true;
    /**
     * @tc.step: step1. create cascade TextCascadePickerOptions of settingData(Zero Child)
     */
    NG::TextCascadePickerOptions options1;
    NG::TextCascadePickerOptions options1Child;
    options1Child.rangeResult = { "11", "12" };
    options1.rangeResult = { "1" };
    options1.children.emplace_back(options1Child);
    settingData.options.emplace_back(options1);
    NG::TextCascadePickerOptions options2;
    NG::TextCascadePickerOptions options2Child;
    NG::TextCascadePickerOptions options2Child2Child;
    options2Child2Child.rangeResult = { "221", "222" };
    options2Child.rangeResult = { "21" };
    options2Child.children.emplace_back(options2Child2Child);
    options2.rangeResult = { "2" };
    options2.children.emplace_back(options2Child);
    settingData.options.emplace_back(options2);
    NG::TextCascadePickerOptions options3;
    NG::TextCascadePickerOptions options3Child;
    options3Child.rangeResult = { "31", "32" };
    options3.rangeResult = { "3" };
    options3.children.emplace_back(options3Child);
    settingData.options.emplace_back(options3);
    DialogProperties dialogProperties;
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(0);
    std::map<std::string, NG::DialogTextEvent> dialogEvent;
    /**
     * @tc.step: step2. call Show of TextPickerDialogView
     * @tc.expected: the function of show can generate framenode.
     */
    std::vector<ButtonInfo> buttonInfos;
    auto frameNode =
        TextPickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(frameNode, nullptr);
}

/**
 * @tc.name: TextPickerDialogViewShow011
 * @tc.desc: Test TextPickerDialogView Show(rangeVector is empty).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerDialogViewShow011, TestSize.Level1)
{
    TextPickerDialogView::dialogNode_ = nullptr;
    // when rangeVector and multi selection are both empty, dialog will not display
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    TextPickerSettingData settingData;
    settingData.rangeVector = {};
    settingData.options = {};

    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogTextEvent> dialogEvent;
    std::vector<ButtonInfo> buttonInfos;
    auto frameNode1 =
        TextPickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    EXPECT_EQ(frameNode1, nullptr);

    // when one of rangeVector and multi selection is valid, dialog will display
    settingData.rangeVector = { { "", "1" }, { "", "2" }, { "", "3" } };
    auto frameNode2 =
        TextPickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    EXPECT_NE(frameNode2, nullptr);
    TextPickerDialogView::dialogNode_ = nullptr;
    settingData.rangeVector = {};
    NG::TextCascadePickerOptions options1;
    NG::TextCascadePickerOptions options1Child;
    options1Child.rangeResult = { "11", "12" };
    options1.rangeResult = { "1" };
    options1.children.emplace_back(options1Child);
    settingData.options.emplace_back(options1);
    NG::TextCascadePickerOptions options2;
    NG::TextCascadePickerOptions options2Child;
    NG::TextCascadePickerOptions options2Child2Child;
    options2Child2Child.rangeResult = { "221", "222" };
    options2Child.rangeResult = { "21" };
    options2Child.children.emplace_back(options2Child2Child);
    options2.rangeResult = { "2" };
    options2.children.emplace_back(options2Child);
    settingData.options.emplace_back(options2);
    auto frameNode3 =
        TextPickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    EXPECT_NE(frameNode3, nullptr);
}

/**
 * @tc.name: TextPickerPatternOnAttachToFrameNode001
 * @tc.desc: Test TextPickerPattern OnAttachToFrameNode.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelNGCreateTextPicker001, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, ICON);

    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);

    auto textPickerPattern = AceType::MakeRefPtr<TextPickerPattern>();
    textPickerPattern->AttachToFrameNode(frameNode);
    textPickerPattern->OnAttachToFrameNode();
    auto host = textPickerPattern->GetHost();
    ASSERT_NE(host, nullptr);
}

/**
 * @tc.name: TextPickerModelNGSetDisappearTextStyle001
 * @tc.desc: Test TextPickerModelNG SetDisappearTextStyle(set Color).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelNGSetDisappearTextStyle001, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    PickerTextStyle textStyle;
    textStyle.textColor = Color::RED;
    TextPickerModelNG::GetInstance()->SetDisappearTextStyle(theme, textStyle);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    ASSERT_TRUE(pickerProperty->HasDisappearColor());
    EXPECT_EQ(Color::RED, pickerProperty->GetDisappearColor().value());
}

/**
 * @tc.name: TextPickerModelNGSetDisappearTextStyle002
 * @tc.desc: Test TextPickerModelNG SetDisappearTextStyle(set FontSize).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelNGSetDisappearTextStyle002, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    PickerTextStyle textStyle;
    textStyle.fontSize = Dimension(FONT_SIZE_10);
    TextPickerModelNG::GetInstance()->SetDisappearTextStyle(theme, textStyle);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    ASSERT_TRUE(pickerProperty->HasDisappearFontSize());
    EXPECT_EQ(Dimension(FONT_SIZE_10), pickerProperty->GetDisappearFontSize().value());
}

/**
 * @tc.name: TextPickerModelNGSetDisappearTextStyle003
 * @tc.desc: Test TextPickerModelNG SetDisappearTextStyle(set FontSize 0).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelNGSetDisappearTextStyle003, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    PickerTextStyle textStyle;
    textStyle.fontSize = Dimension(0);
    TextPickerModelNG::GetInstance()->SetDisappearTextStyle(theme, textStyle);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_TRUE(pickerProperty->HasDisappearFontSize());
}

/**
 * @tc.name: TextPickerModelNGSetDisappearTextStyle004
 * @tc.desc: Test TextPickerModelNG SetDisappearTextStyle(set FontWeight).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelNGSetDisappearTextStyle004, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    PickerTextStyle textStyle;
    textStyle.fontWeight = Ace::FontWeight::BOLD;
    TextPickerModelNG::GetInstance()->SetDisappearTextStyle(theme, textStyle);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    ASSERT_TRUE(pickerProperty->HasDisappearWeight());
    EXPECT_EQ(Ace::FontWeight::BOLD, pickerProperty->GetDisappearWeight().value());
}

/**
 * @tc.name: TextPickerModelNGSetNormalTextStyle001
 * @tc.desc: Test TextPickerModelNG SetNormalTextStyle(set Color).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelNGSetNormalTextStyle001, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    PickerTextStyle textStyle;
    textStyle.textColor = Color::RED;
    TextPickerModelNG::GetInstance()->SetNormalTextStyle(theme, textStyle);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    ASSERT_TRUE(pickerProperty->HasColor());
    EXPECT_EQ(Color::RED, pickerProperty->GetColor().value());
}

/**
 * @tc.name: TextPickerModelNGSetNormalTextStyle002
 * @tc.desc: Test TextPickerModelNG SetNormalTextStyle(set FontSize).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelNGSetNormalTextStyle002, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    PickerTextStyle textStyle;
    textStyle.fontSize = Dimension(FONT_SIZE_10);
    TextPickerModelNG::GetInstance()->SetNormalTextStyle(theme, textStyle);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    ASSERT_TRUE(pickerProperty->HasFontSize());
    EXPECT_EQ(Dimension(FONT_SIZE_10), pickerProperty->GetFontSize().value());
}

/**
 * @tc.name: TextPickerModelNGSetNormalTextStyle003
 * @tc.desc: Test TextPickerModelNG SetNormalTextStyle(set FontSize 0).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelNGSetNormalTextStyle003, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    PickerTextStyle textStyle;
    textStyle.fontSize = Dimension(0);
    TextPickerModelNG::GetInstance()->SetNormalTextStyle(theme, textStyle);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_TRUE(pickerProperty->HasFontSize());
}

/**
 * @tc.name: TextPickerModelNGSetNormalTextStyle004
 * @tc.desc: Test TextPickerModelNG SetNormalTextStyle(set FontWeight).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelNGSetNormalTextStyle004, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    PickerTextStyle textStyle;
    textStyle.fontWeight = Ace::FontWeight::BOLD;
    TextPickerModelNG::GetInstance()->SetNormalTextStyle(theme, textStyle);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    ASSERT_TRUE(pickerProperty->HasWeight());
    EXPECT_EQ(Ace::FontWeight::BOLD, pickerProperty->GetWeight().value());
}

/**
 * @tc.name: TextPickerModelNGSetSelectedTextStyle001
 * @tc.desc: Test TextPickerModelNG SetSelectedTextStyle(set Color).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelNGSetSelectedTextStyle001, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    PickerTextStyle textStyle;
    textStyle.textColor = Color::RED;
    TextPickerModelNG::GetInstance()->SetSelectedTextStyle(theme, textStyle);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    ASSERT_TRUE(pickerProperty->HasSelectedColor());
    EXPECT_EQ(Color::RED, pickerProperty->GetSelectedColor().value());
}

/**
 * @tc.name: TextPickerModelNGSetSelectedTextStyle002
 * @tc.desc: Test TextPickerModelNG SetSelectedTextStyle(set FontSize).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelNGSetSelectedTextStyle002, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    PickerTextStyle textStyle;
    textStyle.fontSize = Dimension(FONT_SIZE_10);
    TextPickerModelNG::GetInstance()->SetSelectedTextStyle(theme, textStyle);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    ASSERT_TRUE(pickerProperty->HasSelectedFontSize());
    EXPECT_EQ(Dimension(FONT_SIZE_10), pickerProperty->GetSelectedFontSize().value());
}

/**
 * @tc.name: TextPickerModelNGSetSelectedTextStyle003
 * @tc.desc: Test TextPickerModelNG SetSelectedTextStyle(set FontSize 0).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelNGSetSelectedTextStyle003, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    PickerTextStyle textStyle;
    textStyle.fontSize = Dimension(0);
    TextPickerModelNG::GetInstance()->SetSelectedTextStyle(theme, textStyle);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_TRUE(pickerProperty->HasSelectedFontSize());
}

/**
 * @tc.name: TextPickerModelNGSetSelectedTextStyle004
 * @tc.desc: Test TextPickerModelNG SetSelectedTextStyle(set FontWeight).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelNGSetSelectedTextStyle004, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    PickerTextStyle textStyle;
    textStyle.fontWeight = Ace::FontWeight::BOLD;
    TextPickerModelNG::GetInstance()->SetSelectedTextStyle(theme, textStyle);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    ASSERT_TRUE(pickerProperty->HasSelectedWeight());
    EXPECT_EQ(Ace::FontWeight::BOLD, pickerProperty->GetSelectedWeight().value());
}

/**
 * @tc.name: TextPickerModelNGSetSelected001
 * @tc.desc: Test TextPickerModelNG SetSelected.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelNGSetSelected001, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    std::vector<NG::RangeContent> range = { { "", "1" }, { "", "2" }, { "", "3" } };
    TextPickerModelNG::GetInstance()->SetRange(range);
    TextPickerModelNG::GetInstance()->SetSelected(SELECTED_INDEX_1);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    ASSERT_TRUE(pickerProperty->HasSelected());
    EXPECT_EQ(1, pickerProperty->GetSelected().value());
}

/**
 * @tc.name: TextPickerModelNGSetRange001
 * @tc.desc: Test TextPickerModelNG SetRange.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelNGSetRange001, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    std::vector<NG::RangeContent> range = { { "", "1" }, { "", "2" }, { "", "3" } };
    TextPickerModelNG::GetInstance()->SetRange(range);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto pickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);
    EXPECT_EQ(THREE, pickerPattern->GetRange().size());
}

/**
 * @tc.name: TextPickerModelNGSetRange002
 * @tc.desc: Test TextPickerModelNG SetRange.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelNGSetRange002, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    std::vector<NG::RangeContent> range;
    TextPickerModelNG::GetInstance()->SetRange(range);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto pickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);
    EXPECT_TRUE(pickerPattern->GetRange().empty());
}

/**
 * @tc.name: TextPickerModelNGCreate001
 * @tc.desc: Test TextPickerModelNG Create(DeviceType::PHONE, DeviceOrientation::LANDSCAPE).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelNGCreate001, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    TextPickerModelNG::GetInstance()->Create(theme, ICON);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto stackNode = AceType::DynamicCast<FrameNode>(frameNode->GetFirstChild());
    ASSERT_NE(stackNode, nullptr);
    auto blendNode = AceType::DynamicCast<FrameNode>(stackNode->GetLastChild());
    ASSERT_NE(blendNode, nullptr);
    auto columnNode = AceType::DynamicCast<FrameNode>(blendNode->GetLastChild());
    ASSERT_NE(columnNode, nullptr);
    auto columnChildren = columnNode->GetChildren();
    EXPECT_EQ(FIVE_CHILDREN + BUFFER_NODE_NUMBER, columnChildren.size());
}

/**
 * @tc.name: TextPickerModelNGCreate002
 * @tc.desc: Test TextPickerModelNG Create(DeviceType::PHONE, DeviceOrientation::0).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelNGCreate002, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(0);
    TextPickerModelNG::GetInstance()->Create(theme, MIXTURE);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto stackNode = AceType::DynamicCast<FrameNode>(frameNode->GetFirstChild());
    ASSERT_NE(stackNode, nullptr);
    auto blendNode = AceType::DynamicCast<FrameNode>(stackNode->GetLastChild());
    ASSERT_NE(blendNode, nullptr);
    auto columnNode = AceType::DynamicCast<FrameNode>(blendNode->GetLastChild());
    ASSERT_NE(columnNode, nullptr);
    auto columnChildren = columnNode->GetChildren();
    EXPECT_EQ(FIVE_CHILDREN + BUFFER_NODE_NUMBER, columnChildren.size());
}

/**
 * @tc.name: TextPickerModelNGSetDefaultAttributes001
 * @tc.desc: Test TextPickerModelNG SetDefaultAttributes.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelNGSetDefaultAttributes001, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();

    theme->selectedOptionStyle_.SetTextColor(Color(0x007DFF));
    theme->selectedOptionStyle_.SetFontSize(Dimension(20, DimensionUnit::VP));
    theme->selectedOptionStyle_.SetFontWeight(FontWeight::MEDIUM);

    theme->normalOptionStyle_.SetTextColor(Color(0xff182431));
    theme->normalOptionStyle_.SetFontSize(Dimension(16, DimensionUnit::FP));
    theme->normalOptionStyle_.SetFontWeight(FontWeight::REGULAR);

    theme->disappearOptionStyle_.SetTextColor(Color(0xff182431));
    theme->disappearOptionStyle_.SetFontSize(Dimension(14, DimensionUnit::FP));
    theme->disappearOptionStyle_.SetFontWeight(FontWeight::REGULAR);

    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    TextPickerModelNG::GetInstance()->SetDefaultAttributes(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    ASSERT_TRUE(pickerProperty->HasSelectedColor());

    EXPECT_EQ(Color(0x007DFF), pickerProperty->GetSelectedColor().value());
    double fontSize = pickerProperty->GetSelectedFontSize().value().Value();
    EXPECT_EQ(20, fontSize);
    EXPECT_EQ(FontWeight::MEDIUM, pickerProperty->GetSelectedWeight().value());

    EXPECT_EQ(Color(0xff182431), pickerProperty->GetColor().value());
    fontSize = pickerProperty->GetFontSize().value().Value();
    EXPECT_EQ(16, fontSize);
    EXPECT_EQ(FontWeight::REGULAR, pickerProperty->GetWeight().value());

    EXPECT_EQ(Color(0xff182431), pickerProperty->GetDisappearColor().value());
    fontSize = pickerProperty->GetDisappearFontSize().value().Value();
    EXPECT_EQ(14, fontSize);
    EXPECT_EQ(FontWeight::REGULAR, pickerProperty->GetDisappearWeight().value());
}

/**
 * @tc.name: TextPickerModelNGMultiInit001
 * @tc.desc: Test TextPickerModelNG MultiInit.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelNGMultiInit001, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    /**
     * @tc.step: step1. create textpicker pattern.
     */
    TextPickerModelNG::GetInstance()->MultiInit(theme);

    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);

    auto textPickerPattern = AceType::MakeRefPtr<TextPickerPattern>();
    textPickerPattern->AttachToFrameNode(frameNode);
    textPickerPattern->OnAttachToFrameNode();
    auto host = textPickerPattern->GetHost();
    ASSERT_NE(host, nullptr);
}

/**
 * @tc.name: TextPickerModelNGSetIsCascade001
 * @tc.desc: Test TextPickerModelNG SetIsCascade.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelNGSetIsCascade001, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    /**
     * @tc.step: step1. create textpicker pattern.
     */
    TextPickerModelNG::GetInstance()->MultiInit(theme);
    TextPickerModelNG::GetInstance()->SetIsCascade(true);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.step: step2. Get textpicker pattern and Call the interface.
     * @tc.expected: the result of isCascade is correct.
     */
    auto pickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);
    EXPECT_TRUE(pickerPattern->GetIsCascade());
}

/**
 * @tc.name: TextPickerModelNGSetSelecteds001
 * @tc.desc: Test TextPickerModelNG SetSelecteds.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelNGSetSelecteds001, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    /**
     * @tc.step: step1. create textpicker pattern.
     */
    TextPickerModelNG::GetInstance()->MultiInit(theme);
    std::vector<uint32_t> selecteds = { 0, 1, 2 };
    TextPickerModelNG::GetInstance()->SetSelecteds(selecteds);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.step: step2. Get pickerProperty and compare the result.
     * @tc.expected: the result of SetSelecteds is correct.
     */
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    ASSERT_TRUE(pickerProperty->HasSelecteds());
    EXPECT_EQ(0, pickerProperty->GetSelecteds().value().at(0));
    EXPECT_EQ(1, pickerProperty->GetSelecteds().value().at(1));
    EXPECT_EQ(2, pickerProperty->GetSelecteds().value().at(2));
}

/**
 * @tc.name: TextPickerModelNGSetSelecteds002
 * @tc.desc: Test TextPickerModelNG SetSelecteds.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelNGSetSelecteds002, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->MultiInit(theme);

    /**
     * @tc.cases: case. cover branch isHasSelectAttr_ == false.
     */

    TextPickerModel::GetInstance()->SetHasSelectAttr(false);

    /**
     * @tc.cases: case. cover isCascade_ == true
     */
    TextPickerModel::GetInstance()->SetIsCascade(true);

    /**
     * @tc.cases: case. cover branch ProcessCascadeOptions values_ size more than 0.
     */
    std::vector<std::string> values;
    values.emplace_back("1");
    values.emplace_back("2");
    TextPickerModelNG::GetInstance()->SetValues(values);

    std::vector<NG::TextCascadePickerOptions> options;
    NG::TextCascadePickerOptions options1;
    options1.rangeResult = { "11", "12", "13" };
    options.emplace_back(options1);
    NG::TextCascadePickerOptions options2;
    options2.rangeResult = { "21", "22", "23" };
    options.emplace_back(options2);
    TextPickerModelNG::GetInstance()->SetColumns(options);

    std::vector<uint32_t> selecteds = { 0, 1, 2 };
    TextPickerModelNG::GetInstance()->SetSelecteds(selecteds);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.step: step. Get pickerProperty and compare the result.
     * @tc.expected: the result of SetSelecteds is correct.
     */
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    ASSERT_TRUE(pickerProperty->HasSelecteds());
    EXPECT_EQ(2, pickerProperty->GetSelecteds().value().at(2));
}

/**
 * @tc.name: TextPickerModelNGSetSelecteds003
 * @tc.desc: Test TextPickerModelNG SetSelecteds.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelNGSetSelecteds003, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->MultiInit(theme);

    /**
     * @tc.cases: case. cover branch isHasSelectAttr_ == true.
     */
    TextPickerModel::GetInstance()->SetHasSelectAttr(true);

    /**
     * @tc.cases: case. cover isCascade_ == true
     */
    TextPickerModel::GetInstance()->SetIsCascade(true);

    std::vector<NG::TextCascadePickerOptions> options;
    NG::TextCascadePickerOptions options1;
    options1.rangeResult = { "11", "12", "13" };
    options.emplace_back(options1);
    NG::TextCascadePickerOptions options2;
    options2.rangeResult = { "21", "22", "23" };
    options.emplace_back(options2);
    TextPickerModelNG::GetInstance()->SetColumns(options);
    std::vector<uint32_t> selecteds = { 1, 3, 5 };
    TextPickerModelNG::GetInstance()->SetSelecteds(selecteds);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.step: step. Get pickerProperty and compare the result.
     * @tc.expected: the result of SetSelecteds is correct.
     */
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    ASSERT_TRUE(pickerProperty->HasSelecteds());
    EXPECT_EQ(3, pickerProperty->GetSelecteds().value().at(1));
    EXPECT_EQ(5, pickerProperty->GetSelecteds().value().at(2));
}

/**
 * @tc.name: TextPickerModelNGSetValues001
 * @tc.desc: Test TextPickerModelNG SetValues.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelNGSetValues001, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    /**
     * @tc.step: step1. create textpicker pattern.
     */
    TextPickerModelNG::GetInstance()->MultiInit(theme);
    std::vector<std::string> values = { "0", "1", "2" };
    TextPickerModelNG::GetInstance()->SetValues(values);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.step: step2. Get pickerProperty and compare the result.
     * @tc.expected: the result of SetValues is correct.
     */
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    ASSERT_TRUE(pickerProperty->HasValues());
    EXPECT_EQ("0", pickerProperty->GetValues().value().at(0));
    EXPECT_EQ("1", pickerProperty->GetValues().value().at(1));
    EXPECT_EQ("2", pickerProperty->GetValues().value().at(2));
}

/**
 * @tc.name: TextPickerModelNGSetColumns001
 * @tc.desc: Test TextPickerModelNG SetColumns(Multi).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelNGSetColumns001, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    /**
     * @tc.step: step1. create textpicker pattern.
     */
    TextPickerModelNG::GetInstance()->MultiInit(theme);
    TextPickerModelNG::GetInstance()->SetIsCascade(false);
    std::vector<NG::TextCascadePickerOptions> options;
    NG::TextCascadePickerOptions options1;
    options1.rangeResult = { "11", "12", "13" };
    options.emplace_back(options1);
    NG::TextCascadePickerOptions options2;
    options2.rangeResult = { "21", "22", "23" };
    options.emplace_back(options2);
    NG::TextCascadePickerOptions options3;
    options3.rangeResult = { "31", "32", "33" };
    options.emplace_back(options3);
    /**
     * @tc.step: step2. Set Multi Columns and compare the result.
     * @tc.expected: the result of SetColumns is correct.
     */
    TextPickerModelNG::GetInstance()->SetColumns(options);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto pickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);
    EXPECT_EQ(THREE, pickerPattern->GetCascadeOptionCount());
}

/**
 * @tc.name: TextPickerModelNGSetColumns002
 * @tc.desc: Test TextPickerModelNG SetColumns(Cascade).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelNGSetColumns002, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    /**
     * @tc.step: step1. create textpicker pattern.
     */
    TextPickerModelNG::GetInstance()->MultiInit(theme);
    TextPickerModelNG::GetInstance()->SetIsCascade(false);
    std::vector<NG::TextCascadePickerOptions> options;
    NG::TextCascadePickerOptions options1;
    NG::TextCascadePickerOptions options1Child;
    options1Child.rangeResult = { "11", "12" };
    options1.rangeResult = { "1" };
    options1.children.emplace_back(options1Child);
    options.emplace_back(options1);
    NG::TextCascadePickerOptions options2;
    NG::TextCascadePickerOptions options2Child;
    options2Child.rangeResult = { "21", "22" };
    options2.rangeResult = { "2" };
    options2.children.emplace_back(options2Child);
    options.emplace_back(options2);
    NG::TextCascadePickerOptions options3;
    NG::TextCascadePickerOptions options3Child;
    options3Child.rangeResult = { "31", "32" };
    options3.rangeResult = { "3" };
    options3.children.emplace_back(options3Child);
    options.emplace_back(options3);
    /**
     * @tc.step: step2. Set Cascade Columns and compare the result.
     * @tc.expected: the result of SetColumns is correct.
     */
    TextPickerModelNG::GetInstance()->SetColumns(options);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto pickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);
    EXPECT_EQ(THREE, pickerPattern->GetCascadeOptionCount());
}

/**
 * @tc.name: TextPickerModelNGSetColumns003
 * @tc.desc: Test TextPickerModelNG SetColumns(Cascade Supply Zero Child).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelNGSetColumns003, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    /**
     * @tc.step: step1. create textpicker pattern.
     */
    TextPickerModelNG::GetInstance()->MultiInit(theme);
    TextPickerModelNG::GetInstance()->SetIsCascade(false);
    std::vector<NG::TextCascadePickerOptions> options;
    NG::TextCascadePickerOptions options1;
    NG::TextCascadePickerOptions options1Child;
    options1Child.rangeResult = { "11", "12" };
    options1.rangeResult = { "1" };
    options1.children.emplace_back(options1Child);
    options.emplace_back(options1);
    NG::TextCascadePickerOptions options2;
    NG::TextCascadePickerOptions options2Child;
    NG::TextCascadePickerOptions options2Child2Child;
    options2Child2Child.rangeResult = { "221", "222" };
    options2Child.rangeResult = { "21" };
    options2Child.children.emplace_back(options2Child2Child);
    options2.rangeResult = { "2" };
    options2.children.emplace_back(options2Child);
    options.emplace_back(options2);
    NG::TextCascadePickerOptions options3;
    NG::TextCascadePickerOptions options3Child;
    options3Child.rangeResult = { "31", "32" };
    options3.rangeResult = { "3" };
    options3.children.emplace_back(options3Child);
    options.emplace_back(options3);
    /**
     * @tc.step: step2. Set Cascade Columns and compare the result.
     * @tc.expected: the result of SetColumns is correct.
     */
    TextPickerModelNG::GetInstance()->SetColumns(options);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto pickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);
    EXPECT_EQ(THREE, pickerPattern->GetCascadeOptionCount());
}

/**
 * @tc.name: TextPickerAlgorithmTest
 * @tc.desc: Test Layout.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerAlgorithmTest, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild()->GetLastChild()->GetLastChild());
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    pickerProperty->UpdateDefaultPickerItemHeight(Dimension(10));
    pickerProperty->contentConstraint_ = pickerProperty->CreateContentConstraint();

    auto subNode = AceType::DynamicCast<FrameNode>(columnNode->GetFirstChild());
    ASSERT_NE(subNode, nullptr);
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(columnNode, columnNode->GetGeometryNode(), pickerProperty);
    RefPtr<LayoutWrapperNode> subLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(subNode, subNode->GetGeometryNode(), nullptr);
    EXPECT_NE(subLayoutWrapper, nullptr);
    layoutWrapper.AppendChild(std::move(subLayoutWrapper));
    EXPECT_EQ(layoutWrapper.GetTotalChildCount(), 1);
    TextPickerLayoutAlgorithm textPickerLayoutAlgorithm;
    textPickerLayoutAlgorithm.currentOffset_.emplace_back(0.0f);

    /**
     * @tc.cases: case. cover branch isDefaultPickerItemHeight_ is true.
     */
    textPickerLayoutAlgorithm.isDefaultPickerItemHeight_ = true;
    textPickerLayoutAlgorithm.Layout(&layoutWrapper);
    auto childGeometryNode = subLayoutWrapper->GetGeometryNode();
    childGeometryNode->SetMarginFrameOffset(CHILD_OFFSET);
    EXPECT_EQ(childGeometryNode->GetMarginFrameOffset(), OffsetF(0.0f, 10.0f));
}

/**
 * @tc.name: TextPickerAlgorithmTest001
 * @tc.desc: Test Measure.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerAlgorithmTest001, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild()->GetLastChild()->GetLastChild());
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(columnNode, columnNode->GetGeometryNode(), pickerProperty);
    RefPtr<LayoutWrapperNode> subLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, nullptr, nullptr);
    EXPECT_NE(subLayoutWrapper, nullptr);
    RefPtr<LayoutWrapperNode> subTwoLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, nullptr, nullptr);
    EXPECT_NE(subTwoLayoutWrapper, nullptr);
    layoutWrapper.AppendChild(std::move(subLayoutWrapper));
    layoutWrapper.AppendChild(std::move(subTwoLayoutWrapper));
    EXPECT_EQ(layoutWrapper.GetTotalChildCount(), 2);
    TextPickerLayoutAlgorithm textPickerLayoutAlgorithm;
    textPickerLayoutAlgorithm.Measure(&layoutWrapper);
}

/**
 * @tc.name: TextPickerAlgorithmTest002
 * @tc.desc: Test Layout.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerAlgorithmTest002, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild()->GetLastChild()->GetLastChild());
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    auto subNode = AceType::DynamicCast<FrameNode>(columnNode->GetFirstChild());
    ASSERT_NE(subNode, nullptr);
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(columnNode, columnNode->GetGeometryNode(), pickerProperty);
    RefPtr<LayoutWrapperNode> subLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(subNode, subNode->GetGeometryNode(), nullptr);
    EXPECT_NE(subLayoutWrapper, nullptr);
    layoutWrapper.AppendChild(std::move(subLayoutWrapper));
    EXPECT_EQ(layoutWrapper.GetTotalChildCount(), 1);
    TextPickerLayoutAlgorithm textPickerLayoutAlgorithm;
    textPickerLayoutAlgorithm.currentOffset_.emplace_back(0.0f);
    textPickerLayoutAlgorithm.Layout(&layoutWrapper);
    auto childGeometryNode = subLayoutWrapper->GetGeometryNode();
    childGeometryNode->SetMarginFrameOffset(CHILD_OFFSET);
    EXPECT_EQ(childGeometryNode->GetMarginFrameOffset(), OffsetF(0.0f, 10.0f));
}

/**
 * @tc.name: TextPickerAlgorithmTest003
 * @tc.desc: Test Measure.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerAlgorithmTest003, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild()->GetLastChild()->GetLastChild());
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    pickerProperty->UpdateDefaultPickerItemHeight(Dimension(10));
    SizeF value(400.0f, 300.0f);
    pickerProperty->UpdateMarginSelfIdealSize(value);
    pickerProperty->contentConstraint_ = pickerProperty->CreateContentConstraint();

    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(columnNode, columnNode->GetGeometryNode(), pickerProperty);
    RefPtr<LayoutWrapperNode> subLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, nullptr, nullptr);
    EXPECT_NE(subLayoutWrapper, nullptr);
    RefPtr<LayoutWrapperNode> subTwoLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, nullptr, nullptr);
    EXPECT_NE(subTwoLayoutWrapper, nullptr);
    layoutWrapper.AppendChild(std::move(subLayoutWrapper));
    layoutWrapper.AppendChild(std::move(subTwoLayoutWrapper));
    EXPECT_EQ(layoutWrapper.GetTotalChildCount(), 2);
    TextPickerLayoutAlgorithm textPickerLayoutAlgorithm;
    textPickerLayoutAlgorithm.Measure(&layoutWrapper);
}

/**
 * @tc.name: TextPickerAlgorithmTest004
 * @tc.desc: Test Layout.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerAlgorithmTest004, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild()->GetLastChild()->GetLastChild());
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    pickerProperty->UpdateDefaultPickerItemHeight(Dimension(10));
    SizeF value(400.0f, 300.0f);
    pickerProperty->UpdateMarginSelfIdealSize(value);
    pickerProperty->contentConstraint_ = pickerProperty->CreateContentConstraint();

    auto subNode = AceType::DynamicCast<FrameNode>(columnNode->GetFirstChild());
    ASSERT_NE(subNode, nullptr);

    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(columnNode, columnNode->GetGeometryNode(), pickerProperty);
    RefPtr<LayoutWrapperNode> subLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(subNode, subNode->GetGeometryNode(), nullptr);
    EXPECT_NE(subLayoutWrapper, nullptr);
    layoutWrapper.AppendChild(std::move(subLayoutWrapper));
    EXPECT_EQ(layoutWrapper.GetTotalChildCount(), 1);
    TextPickerLayoutAlgorithm textPickerLayoutAlgorithm;
    textPickerLayoutAlgorithm.currentOffset_.emplace_back(0.0f);
    textPickerLayoutAlgorithm.Layout(&layoutWrapper);
    auto childGeometryNode = subLayoutWrapper->GetGeometryNode();
    childGeometryNode->SetMarginFrameOffset(CHILD_OFFSET);
    EXPECT_EQ(childGeometryNode->GetMarginFrameOffset(), OffsetF(0.0f, 10.0f));
}

/**
 * @tc.name: TextPickerAlgorithmTest005
 * @tc.desc: Test Measure.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerAlgorithmTest005, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild()->GetLastChild()->GetLastChild());
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    pickerProperty->UpdateDefaultPickerItemHeight(Dimension(10));
    SizeF value(400.0f, 300.0f);
    pickerProperty->UpdateMarginSelfIdealSize(value);
    pickerProperty->contentConstraint_ = pickerProperty->CreateContentConstraint();

    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(columnNode, columnNode->GetGeometryNode(), pickerProperty);
    RefPtr<LayoutWrapperNode> subLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, nullptr, nullptr);
    EXPECT_NE(subLayoutWrapper, nullptr);
    RefPtr<LayoutWrapperNode> subTwoLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, nullptr, nullptr);
    EXPECT_NE(subTwoLayoutWrapper, nullptr);
    layoutWrapper.AppendChild(std::move(subLayoutWrapper));
    layoutWrapper.AppendChild(std::move(subTwoLayoutWrapper));
    EXPECT_EQ(layoutWrapper.GetTotalChildCount(), 2);

    TextPickerLayoutAlgorithm textPickerLayoutAlgorithm;
    textPickerLayoutAlgorithm.Measure(&layoutWrapper);
}

/**
 * @tc.name: TextPickerAlgorithmTest006
 * @tc.desc: Test Measure.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerAlgorithmTest006, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    /**
     * @tc.cases: case. cover branch DeviceOrientation is LANDSCAPE.
     */
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();

    /**
     * @tc.cases: case. cover branch isShowInDialog_ is true .
     */
    auto pickerPattern = frameNode->GetPattern<TextPickerPattern>();
    pickerPattern->SetIsShowInDialog(true);
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild()->GetLastChild()->GetLastChild());
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);

    SizeF value(400.0f, 300.0f);
    pickerProperty->UpdateMarginSelfIdealSize(value);
    pickerProperty->contentConstraint_ = pickerProperty->CreateContentConstraint();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(columnNode, columnNode->GetGeometryNode(), pickerProperty);
    RefPtr<LayoutWrapperNode> subLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, nullptr, nullptr);
    EXPECT_NE(subLayoutWrapper, nullptr);
    RefPtr<LayoutWrapperNode> subTwoLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, nullptr, nullptr);
    EXPECT_NE(subTwoLayoutWrapper, nullptr);
    layoutWrapper.AppendChild(std::move(subLayoutWrapper));
    layoutWrapper.AppendChild(std::move(subTwoLayoutWrapper));
    EXPECT_EQ(layoutWrapper.GetTotalChildCount(), 2);

    /**
     * @tc.cases: case. cover branch dialogTheme pass non null check .
     */
    TextPickerLayoutAlgorithm textPickerLayoutAlgorithm;
    textPickerLayoutAlgorithm.Measure(&layoutWrapper);
}

/**
 * @tc.name: TextPickerAlgorithmTest007
 * @tc.desc: Test Measure.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerAlgorithmTest007, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();

    /**
     * @tc.cases: case. cover branch isShowInDialog_ is true .
     */
    auto pickerPattern = frameNode->GetPattern<TextPickerPattern>();
    pickerPattern->SetIsShowInDialog(true);
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild()->GetLastChild()->GetLastChild());
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);

    /**
     * @tc.cases: case. cover branch defaultPickerItemHeightValue LessOrEqual 0 .
     */
    pickerProperty->UpdateDefaultPickerItemHeight(Dimension(-10.0f));
    SizeF value(400.0f, 300.0f);
    pickerProperty->UpdateMarginSelfIdealSize(value);
    pickerProperty->contentConstraint_ = pickerProperty->CreateContentConstraint();

    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(columnNode, columnNode->GetGeometryNode(), pickerProperty);
    RefPtr<LayoutWrapperNode> subLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, nullptr, nullptr);
    EXPECT_NE(subLayoutWrapper, nullptr);
    RefPtr<LayoutWrapperNode> subTwoLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, nullptr, nullptr);
    EXPECT_NE(subTwoLayoutWrapper, nullptr);
    layoutWrapper.AppendChild(std::move(subLayoutWrapper));
    layoutWrapper.AppendChild(std::move(subTwoLayoutWrapper));
    EXPECT_EQ(layoutWrapper.GetTotalChildCount(), 2);

    /**
     * @tc.cases: case. cover branch dialogTheme pass non null check .
     */
    TextPickerLayoutAlgorithm textPickerLayoutAlgorithm;
    textPickerLayoutAlgorithm.Measure(&layoutWrapper);
}

/**
 * @tc.name: TextPickerDialogViewOnKeyEvent
 * @tc.desc: Test TextPickerDialogView OnKeyEvent.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerDialogViewOnKeyEvent, TestSize.Level1)
{
    KeyEvent event;

    /**
     * @tc.cases: case. cover KeyAction is not DOWN.
     */
    event.action = KeyAction::UP;
    event.code = KeyCode::KEY_TAB;
    bool result = TextPickerDialogView::OnKeyEvent(event);
    EXPECT_FALSE(result);

    /**
     * @tc.cases: case. cover KeyCode is KEY_ESCAPE.
     */
    event.action = KeyAction::DOWN;
    event.code = KeyCode::KEY_ESCAPE;
    result = TextPickerDialogView::OnKeyEvent(event);
    EXPECT_FALSE(result);

    /**
     * @tc.cases: case. cover KeyCode is not KEY_ESCAPE.
     */
    event.action = KeyAction::DOWN;
    event.code = KeyCode::KEY_FORWARD_DEL;
    result = TextPickerDialogView::OnKeyEvent(event);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: TextPickerModelTest001
 * @tc.desc: Test SetDefaultPickerItemHeight, SetCanLoop, SetBackgroundColor
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelTest001, TestSize.Level1)
{
    /**
     * @tc.step: step1. create textpicker framenode and textPickerLayoutProperty.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode =ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto textPickerLayoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    /**
     * test method SetDefaultPickerItemHeight.
     */
    Dimension dimension(20.0);
    TextPickerModelNG::GetInstance()->SetDefaultPickerItemHeight(dimension);
    EXPECT_EQ(textPickerLayoutProperty->GetDefaultPickerItemHeight(), dimension);
    /**
     * test method SetCanLoop.
     */
    TextPickerModelNG::GetInstance()->SetCanLoop(true);
    EXPECT_TRUE(textPickerLayoutProperty->GetCanLoop());
    /**
     * test method SetBackgroundColor.
     */
    Color color;
    TextPickerModelNG::GetInstance()->SetBackgroundColor(color);
    EXPECT_EQ(textPickerPattern->backgroundColor_, color);
}

/**
 * @tc.name: TextPickerModelTest002
 * @tc.desc: Test GetSingleRange, GetMultiOptions
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelTest002, TestSize.Level1)
{
    /**
     * @tc.step: step1. create textpicker framenode.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto textPickerLayoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    /**
     * test method GetSingleRange.
     */
    std::vector<NG::RangeContent> range = { { "", "1" }, { "", "2" }, { "", "3" } };
    TextPickerModelNG::GetInstance()->SetRange(range);
    std::vector<NG::RangeContent> rangeValue;
    auto ret = TextPickerModelNG::GetInstance()->GetSingleRange(rangeValue);
    EXPECT_TRUE(ret);
    EXPECT_EQ(rangeValue.size(), 3);

    EXPECT_TRUE(TextPickerModelNG::GetInstance()->IsSingle());
    /**
     * test method GetMultiOptions.
     */
    std::vector<TextCascadePickerOptions> options;
    TextCascadePickerOptions options1;
    options1.rangeResult = { "11", "12", "13" };
    options.emplace_back(options1);
    TextPickerModelNG::GetInstance()->SetColumns(options);
    std::vector<NG::TextCascadePickerOptions> multiOptions;
    ret = TextPickerModelNG::GetInstance()->GetMultiOptions(multiOptions);
    EXPECT_TRUE(ret);
    EXPECT_EQ(multiOptions.size(), 1);
}


/**
 * @tc.name: TextPickerModelTest003
 * @tc.desc: Test SetDivider
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelTest003, TestSize.Level1)
{
    /**
     * @tc.step: step1. create textpicker framenode and textPickerLayoutProperty.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto textPickerLayoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    /**
     * test method SetDefaultPickerItemHeight.
     */
    ItemDivider divider;
    divider.color = Color::TRANSPARENT;
    divider.strokeWidth = 10.0_vp;
    divider.startMargin = 10.0_vp;
    divider.endMargin = 10.0_vp;
    TextPickerModelNG::GetInstance()->SetDivider(divider);
    EXPECT_EQ(textPickerLayoutProperty->GetDivider(), divider);
}

/**
 * @tc.name: TextPickerModelTest004
 * @tc.desc: Test SetTextPickerDialogShow
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelTest004, TestSize.Level1)
{
    /**
     * @tc.step: step1. create textpicker dialog model.
     */
    TextPickerDialogModelNG textPickerDialogModel;
    RefPtr<AceType> pickerText = AceType::MakeRefPtr<AceType>();
    TextPickerSettingData settingData;
    std::function<void()> onCancel = []() {};
    std::function<void(const std::string&)> onAccept = [](const std::string&) {};
    std::function<void(const std::string&)> onChange = [](const std::string&) {};
    TextPickerDialog textPickerDialog;
    textPickerDialog.alignment = DialogAlignment::CENTER;
    TextPickerDialogEvent textPickerDialogEvent;
    std::vector<ButtonInfo> buttonInfos;

    /**
     * test method SetTextPickerDialogShow.
     */
    textPickerDialogModel.SetTextPickerDialogShow(pickerText, settingData, std::move(onCancel),
        std::move(onAccept), std::move(onChange), textPickerDialog, textPickerDialogEvent, buttonInfos);
    EXPECT_EQ(textPickerDialog.alignment, DialogAlignment::CENTER);
}

/**
 * @tc.name: TextPickerModelTest005
 * @tc.desc: Test SetNormalTextStyle
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelTest005, TestSize.Level1)
{
    /**
     * @tc.step: step1. create textpicker model.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto node = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(node, nullptr);
    PickerTextStyle pickerTextStyle;
    TextPickerModelNG::SetNormalTextStyle(node, theme, pickerTextStyle);
    TextPickerModelNG::SetSelectedTextStyle(node, theme, pickerTextStyle);
    TextPickerModelNG::SetDisappearTextStyle(node, theme, pickerTextStyle);

    /**
     * @tc.steps: step2. execute SetNormalTextStyle
     * @tc.expected: prop is set as expected
     */
    Dimension fontSize(10.0f);
    pickerTextStyle.fontSize = fontSize;
    TextPickerModelNG::SetNormalTextStyle(node, theme, pickerTextStyle);
    TextPickerModelNG::SetSelectedTextStyle(node, theme, pickerTextStyle);
    TextPickerModelNG::SetDisappearTextStyle(node, theme, pickerTextStyle);

    auto textPickerLayoutProperty = node->GetLayoutProperty<TextPickerLayoutProperty>();
    EXPECT_EQ(textPickerLayoutProperty->GetFontSizeValue(Dimension(0)).Value(), 10.0f);
}

/**
 * @tc.name: TextPickerModelTest006
 * @tc.desc: Test SetColumns
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelTest006, TestSize.Level1)
{
    /**
     * @tc.step: step1. create textpicker model.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto node = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(node, nullptr);
    std::vector<NG::TextCascadePickerOptions> options;
    TextPickerModelNG::SetColumns(node, options);
    TextPickerModelNG::getTextPickerRange(node);

    /**
     * @tc.steps: step2. execute SetColumns
     * @tc.expected: prop is set as expected
     */
    TextPickerModelNG::isCascade_ = !TextPickerModelNG::isCascade_;
    TextPickerModelNG::isSingleRange_ = !TextPickerModelNG::isSingleRange_;
    NG::TextCascadePickerOptions options1;
    options1.rangeResult = { "11", "12", "13" };
    options.emplace_back(options1);
    TextPickerModelNG::SetColumns(node, options);
    TextPickerModelNG::getTextPickerRange(node);
    EXPECT_EQ(TextPickerModelNG::isCascade_, true);
    EXPECT_EQ(TextPickerModelNG::isSingleRange_, false);
}


/**
 * @tc.name: TextPickerModelTest007
 * @tc.desc: Test TextPickerModelTest.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelTest007, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();

    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(0);
    TextPickerModelNG::GetInstance()->Create(theme, MIXTURE);
    std::vector<NG::RangeContent> range = { { "/demo/demo1.jpg", "test1" }, { "/demo/demo2.jpg", "test2" },
        { "/demo/demo3.jpg", "test3" } };
    TextPickerModelNG::GetInstance()->SetRange(range);
    TextPickerModelNG::GetInstance()->SetSelected(SELECTED_INDEX_1);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(false);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    textPickerPattern->OnModifyDone();
    auto child = textPickerPattern->GetColumnNode();
    ASSERT_NE(child, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(child)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    columnPattern->FlushCurrentOptions(false, false);
    auto linearLayoutNode = AceType::DynamicCast<FrameNode>(child->GetFirstChild());
    ASSERT_NE(linearLayoutNode, nullptr);
    auto imageNode = AceType::DynamicCast<FrameNode>(linearLayoutNode->GetFirstChild());
    ASSERT_NE(imageNode, nullptr);
    auto imagePattern = imageNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    auto imageLayoutProperty = imagePattern->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    EXPECT_FALSE(imageLayoutProperty->HasImageSourceInfo());
    EXPECT_EQ(imageLayoutProperty->GetMarginProperty()->left, CalcLength(ICON_TEXT_SPACE));
}

/**
 * @tc.name: TextPickerDialogViewConvertFontScaleValue001
 * @tc.desc: Test TextPickerDialogView ConvertFontScaleValue.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerDialogViewConvertFontScaleValue001, TestSize.Level1)
{
    Dimension fontSizeValue = 50.0_vp;
    Dimension fontSizeLimit = 40.0_vp;

    auto result = TextPickerDialogView::ConvertFontScaleValue(fontSizeValue, fontSizeLimit, true);
    EXPECT_EQ(fontSizeLimit.Value(), result.Value());
}

/**
 * @tc.name: TextPickerDialogViewConvertFontScaleValue002
 * @tc.desc: Test TextPickerDialogView ConvertFontScaleValue.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerDialogViewConvertFontScaleValue002, TestSize.Level1)
{
    Dimension fontSizeValue = 20.0_vp;
    Dimension fontSizeLimit = 40.0_vp;

    auto result = TextPickerDialogView::ConvertFontScaleValue(fontSizeValue, fontSizeLimit, true);
    EXPECT_EQ(fontSizeValue.Value(), result.Value());
}

/**
 * @tc.name: TextPickerDialogViewConvertFontSizeLimitTest001
 * @tc.desc: Test TextPickerDialogView ConvertFontSizeLimit.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerDialogViewConvertFontSizeLimitTest001, TestSize.Level1)
{
    Dimension fontSizeValue(20.0);
    Dimension fontSizeLimit(30.0);
    bool isUserSetFont = false;
    Dimension result = TextPickerDialogView::ConvertFontSizeLimit(fontSizeValue, fontSizeLimit, isUserSetFont);
    EXPECT_EQ(result, fontSizeValue);
}

/**
 * @tc.name: TextPickerDialogViewConvertFontSizeLimitTest002
 * @tc.desc: Test TextPickerDialogView ConvertFontSizeLimit.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerDialogViewConvertFontSizeLimitTest002, TestSize.Level1)
{
    Dimension fontSizeValue(20.0);
    Dimension fontSizeLimit(30.0);
    bool isUserSetFont = true;
    Dimension result = TextPickerDialogView::ConvertFontSizeLimit(fontSizeValue, fontSizeLimit, isUserSetFont);
    EXPECT_EQ(result, fontSizeValue);
}

/**
 * @tc.name: TextPickerDialogViewConvertFontSizeLimitTest003
 * @tc.desc: Test TextPickerDialogView ConvertFontSizeLimit.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerDialogViewConvertFontSizeLimitTest003, TestSize.Level1)
{
    Dimension fontSizeValue(40.0);
    Dimension fontSizeLimit(30.0);
    bool isUserSetFont = true;
    double fontScale = 2.0f;
    MockPipelineContext::GetCurrent()->SetFontScale(fontScale);
    Dimension result = TextPickerDialogView::ConvertFontSizeLimit(fontSizeValue, fontSizeLimit, isUserSetFont);
    Dimension expected = fontSizeLimit / fontScale;
    EXPECT_EQ(result, expected);
}

/**
 * @tc.name: TextPickerDialogViewConvertFontSizeLimitTest004
 * @tc.desc: Test TextPickerDialogView ConvertFontSizeLimit.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerDialogViewConvertFontSizeLimitTest004, TestSize.Level1)
{
    Dimension fontSizeValue(10.0);
    Dimension fontSizeLimit(30.0);
    bool isUserSetFont = true;
    double fontScale = 2.0f;
    MockPipelineContext::GetCurrent()->SetFontScale(fontScale);
    Dimension result = TextPickerDialogView::ConvertFontSizeLimit(fontSizeValue, fontSizeLimit, isUserSetFont);
    EXPECT_EQ(result, fontSizeValue);
}

/**
 * @tc.name: TextPickerDialogViewGetUserSettingLimitTest001
 * @tc.desc: Test TextPickerDialogView AdjustFontSizeScale.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerDialogViewGetUserSettingLimitTest001, TestSize.Level1)
{
    double fontScale = 1.0f;
    Dimension fontSizeValue(10.0);
    Dimension result = TextPickerDialogView::AdjustFontSizeScale(fontSizeValue, fontScale);
    EXPECT_EQ(result, fontSizeValue * fontScale);
}

/**
 * @tc.name: TextPickerDialogViewGetUserSettingLimitTest002
 * @tc.desc: Test TextPickerDialogView AdjustFontSizeScale.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerDialogViewGetUserSettingLimitTest002, TestSize.Level1)
{
    double fontScale = 1.75f;
    Dimension fontSizeValue(10.0);
    Dimension result = TextPickerDialogView::AdjustFontSizeScale(fontSizeValue, fontScale);
    EXPECT_EQ(result, fontSizeValue * fontScale);
}

/**
 * @tc.name: TextPickerDialogViewGetUserSettingLimitTest003
 * @tc.desc: Test TextPickerDialogView AdjustFontSizeScale.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerDialogViewGetUserSettingLimitTest003, TestSize.Level1)
{
    double fontScale = 2.0f;
    Dimension fontSizeValue(10.0);
    Dimension result = TextPickerDialogView::AdjustFontSizeScale(fontSizeValue, fontScale);
    EXPECT_EQ(result, fontSizeValue * fontScale);
}

/**
 * @tc.name: TextPickerDialogViewGetUserSettingLimitTest004
 * @tc.desc: Test TextPickerDialogView AdjustFontSizeScale.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerDialogViewGetUserSettingLimitTest004, TestSize.Level1)
{
    double fontScale = 3.2f;
    Dimension fontSizeValue(10.0);
    Dimension result = TextPickerDialogView::AdjustFontSizeScale(fontSizeValue, fontScale);
    EXPECT_NE(result, fontSizeValue * fontScale);
}

} // namespace OHOS::Ace::NG
