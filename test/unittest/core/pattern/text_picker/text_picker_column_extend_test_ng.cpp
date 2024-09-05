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
#include <functional>
#include <optional>

#include "gtest/gtest.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "base/geometry/dimension.h"
#include "base/geometry/ng/size_t.h"
#include "base/i18n/localization.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/measure_util.h"
#include "core/components/picker/picker_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
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
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_font_manager.h"
#include "test/mock/core/common/mock_theme_default.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/rosen/mock_canvas.h"


using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t ONCANCEL_CALLBACK_INFO = 1;
constexpr double FONT_SIZE_10 = 10.0;
constexpr float COMPONENT_WIDTH = 45.0f;
constexpr float COMPONENT_HEIGHT = 36.0f;
constexpr float MAX_WIDTH = 100.0f;
constexpr float MAX_HEIGHT = 100.0f;
const Dimension DEFAULT_GRADIENT_HEIGHT = 20.0_vp;
const Dimension DEFAULT_PICKER_ITEM_HEIGHT = 12.0_vp;
} // namespace

class TextPickerColumnExtendTestNg : public TestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    RefPtr<FrameNode> GetOrCreateTextPickerFrameNodeTree();
    RefPtr<TextPickerColumnPattern> GetTextPickerColumnPatternFromNodeTree();
    std::shared_ptr<PickerTextProperties> CreateDefaultPickerTextProperties();
    std::shared_ptr<TextPickerSettingData> CreateDefaultTextPickerSettingData();
    RefPtr<FrameNode> FindContentRowNodeTree(const RefPtr<FrameNode>& dialogNode);
    void SetColumnNodeIdealSize();

private:
    RefPtr<FrameNode> textPickerNode_;
};

void TextPickerColumnExtendTestNg::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrent();
}

void TextPickerColumnExtendTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void TextPickerColumnExtendTestNg::SetUp()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
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
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void TextPickerColumnExtendTestNg::TearDown()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    textPickerNode_ = nullptr;
    ClearOldNodes(); // Each testcase will create new list at begin
}

RefPtr<FrameNode> TextPickerColumnExtendTestNg::GetOrCreateTextPickerFrameNodeTree()
{
    if (!textPickerNode_) {
        ResetElmtId();
        ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(GetElmtId());
        auto pipeline = MockPipelineContext::GetCurrent();
        CHECK_NULL_RETURN(pipeline, nullptr);
        auto theme = pipeline->GetTheme<PickerTheme>();
        TextPickerModelNG::GetInstance()->Create(theme, TEXT);
        textPickerNode_ = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    }
    return textPickerNode_;
}

RefPtr<TextPickerColumnPattern> TextPickerColumnExtendTestNg::GetTextPickerColumnPatternFromNodeTree()
{
    auto textPickerNode = GetOrCreateTextPickerFrameNodeTree();
    CHECK_NULL_RETURN(textPickerNode, nullptr);
    auto stackNode = textPickerNode->GetLastChild();
    CHECK_NULL_RETURN(stackNode, nullptr);
    auto columnBlendNode = stackNode->GetLastChild();
    CHECK_NULL_RETURN(columnBlendNode, nullptr);
    auto textPickerColumnNode = AceType::DynamicCast<FrameNode>(columnBlendNode->GetLastChild());
    CHECK_NULL_RETURN(textPickerColumnNode, nullptr);
    return textPickerColumnNode->GetPattern<TextPickerColumnPattern>();
}

void TextPickerColumnExtendTestNg::SetColumnNodeIdealSize()
{
    CHECK_NULL_VOID(textPickerNode_);
    auto stackNode = AceType::DynamicCast<FrameNode>(textPickerNode_->GetFirstChild());
    CHECK_NULL_VOID(stackNode);
    auto textPickerLayoutProperty = textPickerNode_->GetLayoutProperty<TextPickerLayoutProperty>();
    CHECK_NULL_VOID(textPickerLayoutProperty);
    auto stackLayoutProperty = stackNode->GetLayoutProperty();
    CHECK_NULL_VOID(stackLayoutProperty);

    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.minSize = SizeF(0, 0);
    layoutConstraintSize.maxSize = SizeF(MAX_WIDTH, MAX_HEIGHT);
    layoutConstraintSize.selfIdealSize.SetWidth(COMPONENT_WIDTH);
    layoutConstraintSize.selfIdealSize.SetHeight(COMPONENT_HEIGHT);
    textPickerLayoutProperty->UpdateLayoutConstraint(layoutConstraintSize);
    textPickerLayoutProperty->UpdateContentConstraint();

    layoutConstraintSize.parentIdealSize.SetWidth(COMPONENT_WIDTH);
    layoutConstraintSize.parentIdealSize.SetHeight(COMPONENT_HEIGHT);
    stackLayoutProperty->UpdateLayoutConstraint(layoutConstraintSize);
    stackLayoutProperty->UpdateContentConstraint();
}

std::shared_ptr<PickerTextProperties> TextPickerColumnExtendTestNg::CreateDefaultPickerTextProperties()
{
    auto properties = std::make_shared<PickerTextProperties>();
    properties->disappearTextStyle_.textColor = Color::RED;
    properties->disappearTextStyle_.fontSize = Dimension(FONT_SIZE_10);
    properties->disappearTextStyle_.fontWeight = Ace::FontWeight::BOLD;

    properties->normalTextStyle_.textColor = Color::RED;
    properties->normalTextStyle_.fontSize = Dimension(FONT_SIZE_10);
    properties->normalTextStyle_.fontWeight = Ace::FontWeight::BOLD;

    properties->selectedTextStyle_.textColor = Color::RED;
    properties->selectedTextStyle_.fontSize = Dimension(FONT_SIZE_10);
    properties->normalTextStyle_.fontWeight = Ace::FontWeight::BOLD;
    return properties;
}

std::shared_ptr<TextPickerSettingData> TextPickerColumnExtendTestNg::CreateDefaultTextPickerSettingData()
{
    auto settingData = std::make_shared<TextPickerSettingData>();
    settingData->columnKind = MIXTURE;
    settingData->height = Dimension(FONT_SIZE_10);
    auto properties = CreateDefaultPickerTextProperties();
    if (properties) {
        settingData->properties = *properties;
    }
    settingData->rangeVector = { { "", "1" }, { "", "2" }, { "", "3" } };
    settingData->selected = 0;
    return settingData;
}

RefPtr<FrameNode> TextPickerColumnExtendTestNg::FindContentRowNodeTree(const RefPtr<FrameNode>& dialogNode)
{
    CHECK_NULL_RETURN(dialogNode, nullptr);
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    CHECK_NULL_RETURN(dialogPattern, nullptr);
    auto customNode = dialogPattern->GetCustomNode();
    CHECK_NULL_RETURN(customNode, nullptr);
    auto children = customNode->GetChildren();
    for (auto it = children.rbegin(); it != children.rend(); ++it) {
        auto targetNode = AceType::DynamicCast<FrameNode>(*it);
        if (targetNode && targetNode->GetTag() == V2::COLUMN_ETS_TAG) {
            auto pattern = targetNode->GetPattern<LinearLayoutPattern>();
            if (pattern && !pattern->GetIsVertical()) {
                return targetNode;
            }
        }
    }
    return nullptr;
}

/**
 * @tc.name: PlayTossAnimation001
 * @tc.desc: Test PlayTossAnimation scene.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnExtendTestNg, PlayTossAnimation001, TestSize.Level1)
{
    /**
     * @tc.step: step1. create frameNode tree and init TextPickerOptionProperty.
     */
    auto textPickerColumnPattern = GetTextPickerColumnPatternFromNodeTree();
    ASSERT_NE(textPickerColumnPattern, nullptr);
    auto toss = textPickerColumnPattern->GetToss();
    ASSERT_NE(toss, nullptr);
    textPickerColumnPattern->OnModifyDone();
    textPickerColumnPattern->SetMainVelocity(500);

    /**
     * @tc.step: step2. Drag to create toss AnimatableProperty and fire finish callback.
     * @tc.expected: AnimatableProperty is not NULL
     */
    GestureEvent eventInfo;
    textPickerColumnPattern->HandleDragStart(eventInfo);
    toss->timeStart_ = toss->GetCurrentTime();
    eventInfo.SetGlobalPoint(Point(0, 5.0));
    textPickerColumnPattern->HandleDragMove(eventInfo);
    double dragTimeStep = 3.0;
    toss->timeEnd_ = toss->GetCurrentTime() + dragTimeStep;
    textPickerColumnPattern->HandleDragEnd();
    auto nodeAnimatablePropertyFloat = toss->GetTossNodeAnimation();
    ASSERT_NE(nodeAnimatablePropertyFloat, nullptr);
    auto property = AceType::DynamicCast<AnimatablePropertyFloat>(nodeAnimatablePropertyFloat->GetProperty());
    ASSERT_NE(property, nullptr);
    auto callback = property->GetUpdateCallback();
    ASSERT_NE(callback, nullptr);
    callback(1.0f);

    /**
     * @tc.step: step3. Drag anagin to stop last toss animation and excute current animation.
     * @tc.expected: tossStatus is false
     */
    textPickerColumnPattern->HandleDragStart(eventInfo);
    toss->timeStart_ = toss->GetCurrentTime();
    eventInfo.SetGlobalPoint(Point(0, 10.0));
    textPickerColumnPattern->HandleDragMove(eventInfo);
    toss->timeEnd_ = toss->GetCurrentTime() + dragTimeStep;
    textPickerColumnPattern->HandleDragEnd();
    EXPECT_FALSE(textPickerColumnPattern->GetTossStatus());
}

/**
 * @tc.name: PerformLayout001
 * @tc.desc: Test performlayout when user set GradientFont.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnExtendTestNg, PerformLayout001, TestSize.Level1)
{
    /**
     * @tc.step: step1. create frameNode tree and init update layoutProperty.
     */
    auto textPickerNode = GetOrCreateTextPickerFrameNodeTree();
    ASSERT_NE(textPickerNode, nullptr);
    auto textPickerPattern = textPickerNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    auto pickerProperty = textPickerNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    auto textPickerColumnPattern = GetTextPickerColumnPatternFromNodeTree();
    ASSERT_NE(textPickerColumnPattern, nullptr);
    auto columnNode = textPickerColumnPattern->GetHost();
    ASSERT_NE(columnNode, nullptr);
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);

    context->SetFontScale(2.0f);
    pickerProperty->UpdateDefaultPickerItemHeight(DEFAULT_PICKER_ITEM_HEIGHT);
    pickerProperty->UpdateGradientHeight(DEFAULT_GRADIENT_HEIGHT);
    auto pickerTextProperties = CreateDefaultPickerTextProperties();
    textPickerPattern->SetTextProperties(*pickerTextProperties);
    textPickerPattern->SetGradientHeight(DEFAULT_GRADIENT_HEIGHT);
    textPickerPattern->SetIsShowInDialog(true);
    textPickerPattern->OnModifyDone();
    textPickerColumnPattern->OnModifyDone();

    /**
     * @tc.step: step2. create layoutAlgorithm and performLayout.
     * @tc.expected: textPickColumn node size is rational.
     */
    SetColumnNodeIdealSize();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(columnNode, columnNode->GetGeometryNode(), pickerProperty);
    for (const auto& child : columnNode->GetChildren()) {
        auto childFrameNode = AceType::DynamicCast<FrameNode>(child);
        if (!childFrameNode) {
            continue;
        }
        RefPtr<LayoutWrapperNode> childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
            childFrameNode, childFrameNode->GetGeometryNode(), childFrameNode->GetLayoutProperty());
        layoutWrapper.AppendChild(childWrapper);
    }
    EXPECT_GT(layoutWrapper.GetTotalChildCount(), 0);
    auto textPickerLayoutAlgorithm = textPickerColumnPattern->CreateLayoutAlgorithm();
    textPickerLayoutAlgorithm->Measure(&layoutWrapper);
    textPickerLayoutAlgorithm->Layout(&layoutWrapper);
    EXPECT_FLOAT_EQ(layoutWrapper.GetGeometryNode()->GetFrameSize().Width(), COMPONENT_WIDTH);
}

/**
 * @tc.name: TextPickerDialogViewShow001
 * @tc.desc: Test TextPickerDialogView Show(column kind is MIXTURE) for API12.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnExtendTestNg, TextPickerDialogViewShow001, TestSize.Level1)
{
    /**
     * @tc.step: step1. Invoke show function to create dialog Node tree.
     */
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));

    auto func = [](const std::string& /* info */) {};
    std::map<std::string, NG::DialogTextEvent> dialogEvent;
    dialogEvent["changeId"] = func;
    dialogEvent["acceptId"] = func;

    int32_t cancelCallbackInfo = 0;
    auto cancelFunc = [&cancelCallbackInfo](
                          const GestureEvent& /* info */) { cancelCallbackInfo = ONCANCEL_CALLBACK_INFO; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;

    auto settingData = CreateDefaultTextPickerSettingData();
    ASSERT_NE(settingData, nullptr);
    DialogProperties dialogProperties;
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode =
        TextPickerDialogView::Show(dialogProperties, *settingData, buttonInfos, dialogEvent, dialogCancelEvent);

    /**
     * @tc.step: step2. Get cancel button node to mock onclick event.
     * @tc.expected: fire oncancel callback.
     */
    auto contentRow = FindContentRowNodeTree(dialogNode);
    ASSERT_NE(contentRow, nullptr);
    auto cancelButtonNode = AceType::DynamicCast<FrameNode>(contentRow->GetFirstChild());
    ASSERT_NE(cancelButtonNode, nullptr);

    auto focusHub = cancelButtonNode->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    auto gestureEventFunc = focusHub->GetOnClickCallback();
    ASSERT_NE(gestureEventFunc, nullptr);
    GestureEvent info;
    gestureEventFunc(info);
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(backupApiVersion));
    EXPECT_EQ(cancelCallbackInfo, ONCANCEL_CALLBACK_INFO);
}

/**
 * @tc.name: TextPickerDialogViewShow002
 * @tc.desc: Test TextPickerDialogView Show (textpicker user set options) for API12.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnExtendTestNg, TextPickerDialogViewShow002, TestSize.Level1)
{
    /**
     * @tc.step: step1. Invoke show function to create dialog Node tree.
     */
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    auto pipeline = PipelineContext::GetCurrentContextSafely();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetFontScale(2.0f);

    std::map<std::string, NG::DialogTextEvent> dialogEvent;
    int32_t cancelCallbackInfo = 0;
    auto cancelFunc = [&cancelCallbackInfo](
                          const GestureEvent& /* info */) { cancelCallbackInfo = ONCANCEL_CALLBACK_INFO; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;

    auto settingData = CreateDefaultTextPickerSettingData();
    ASSERT_NE(settingData, nullptr);
    settingData->options = { { { "11", "12", "13" }, {} }, { { "21", "22", "23" }, {} }, { { "31", "32", "33" }, {} } };
    DialogProperties dialogProperties;
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode =
        TextPickerDialogView::Show(dialogProperties, *settingData, buttonInfos, dialogEvent, dialogCancelEvent);

    /**
     * @tc.step: step2. Get all button nodes to mock onclick event.
     * @tc.expected: At last fire close callback.
     */
    auto contentRow = FindContentRowNodeTree(dialogNode);
    ASSERT_NE(contentRow, nullptr);
    for (const auto& child : contentRow->GetChildren()) {
        if (child && child->GetTag() == V2::BUTTON_ETS_TAG) {
            auto buttonNode = AceType::DynamicCast<FrameNode>(child);
            ASSERT_NE(buttonNode, nullptr);
            auto focusHub = buttonNode->GetOrCreateFocusHub();
            ASSERT_NE(focusHub, nullptr);
            auto gestureEventFunc = focusHub->GetOnClickCallback();
            ASSERT_NE(gestureEventFunc, nullptr);
            GestureEvent info;
            gestureEventFunc(info);
        }
    }
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(backupApiVersion));
    EXPECT_EQ(cancelCallbackInfo, ONCANCEL_CALLBACK_INFO);
}
} // namespace OHOS::Ace::NG
