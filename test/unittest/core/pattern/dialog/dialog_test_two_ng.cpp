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
#include "test/mock/base/mock_system_properties.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "core/common/recorder/event_recorder.h"

#include "core/components/button/button_theme.h"
#include "core/components/dialog/dialog_properties.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/dialog/dialog_event_hub.h"
#include "core/components_ng/pattern/dialog/dialog_layout_algorithm.h"
#include "core/components_ng/pattern/dialog/custom_dialog_controller_model_ng.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_view.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/components_ng/pattern/button/button_layout_property.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const InspectorFilter filter;

const std::string SHEET_TITLE = "sheet item";
const std::string SHEET_TITLE_2 = "sheet item 2";
const std::string SHEET_TITLE_3 = "sheet item 3";
const std::string INTERNAL_SOURCE = "$r('app.media.icon')";
const std::string FILE_SOURCE = "/common/icon.png";

const std::string TITLE = "This is title";
const std::string SUBTITLE = "This is subtitle";
const std::string MESSAGE = "Message";
constexpr int BUTTONINDEX_TEST_2 = -1;
constexpr int BUTTONINDEX_TEST_3 = -2;
constexpr int DIALOG_TITLE_AVE_BY_2 = 2;
const Dimension DIALOG_TITLE_PADDING { 10.0, DimensionUnit::VP };
const Dimension BORDER_WIDTH_PX_A { 10.0, DimensionUnit::PX };
const Dimension BORDER_WIDTH_PX_B { 20.0, DimensionUnit::PX };
const Dimension BORDER_WIDTH_PX_C { 30.0, DimensionUnit::PX };
const Dimension BORDER_WIDTH_PX_D { 40.0, DimensionUnit::PX };
const Dimension DIALOG_BUTTON_BORDER_RADIUS { 20.0, DimensionUnit::VP };
constexpr float FONT_MAX_SIZE_SCALE = 2.0f;
constexpr float FONT_SIZE_SCALE_TEST1 = 1.75f;
constexpr float FONT_SIZE_SCALE_TEST2 = 3.20f;
} // namespace

class MockDialogTheme : public DialogTheme, public ButtonTheme {
    DECLARE_ACE_TYPE(MockDialogTheme, DialogTheme, ButtonTheme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;

        RefPtr<MockDialogTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const
        {
            RefPtr<MockDialogTheme> theme = AceType::MakeRefPtr<MockDialogTheme>();
            return theme;
        }
    };

    ~MockDialogTheme() override = default;

protected:
    MockDialogTheme() = default;
};

class DialogPatternTwoTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetDialogTheme();
    void UpdateDialogProperties(DialogProperties& props);
    void CheckTextMarquee(RefPtr<FrameNode> buttonNode);

protected:
    RefPtr<FrameNode> CreateDialog();

private:
    vector<ActionSheetInfo> sheetItems = {
        ActionSheetInfo {
            .title = SHEET_TITLE,
            .icon = INTERNAL_SOURCE,
        },
        ActionSheetInfo {
            .title = SHEET_TITLE_2,
            .icon = INTERNAL_SOURCE,
        },
        ActionSheetInfo {
            .title = SHEET_TITLE_3,
            .icon = INTERNAL_SOURCE,
        },
    };
    vector<ButtonInfo> btnItems = {
        ButtonInfo {
            .text = "main button",
            .bgColor = Color::BLACK,
        },
        ButtonInfo {
            .text = "second button",
            .bgColor = Color::BLUE,
        },
    };
    vector<ButtonInfo> btnItems1 = {
        ButtonInfo {
            .text = "main button",
            .isBgColorSetted = true,
            .enabled = false,
            .defaultFocus = true,
        },
        ButtonInfo {
            .text = "second button",
            .bgColor = Color::BLUE,
            .enabled = false,
            .defaultFocus = false,
        },
    };
    vector<ButtonInfo> btnItems2 = {
        ButtonInfo {
            .text = "main button",
            .bgColor = Color::BLUE,
            .defaultFocus = true,
            .dlgButtonStyle = DialogButtonStyle::DEFAULT,
        },
        ButtonInfo {
            .text = "second button",
            .bgColor = Color::BLUE,
            .defaultFocus = false,
            .dlgButtonStyle = DialogButtonStyle::HIGHTLIGHT,
        },
    };
    vector<DialogProperties> propsVectors = {
        DialogProperties {
            .type = DialogType::ACTION_SHEET,
            .title = "dialog test",
            .content = "dialog content test",
            .sheetsInfo = sheetItems,
        },
        DialogProperties {
            .type = DialogType::ACTION_SHEET,
            .title = "dialog test",
            .subtitle = "subtitle dialog test",
            .sheetsInfo = sheetItems,
        },
        DialogProperties {
            .content = "dialog content test",
        },
        DialogProperties {
            .type = DialogType::ACTION_SHEET,
            .title = "",
            .subtitle = "subtitle dialog test",
            .content = "dialog content test",
            .sheetsInfo = sheetItems,
        },
    };
};

void DialogPatternTwoTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}
void DialogPatternTwoTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}
void DialogPatternTwoTestNg::SetDialogTheme()
{
    auto themeManager = AceType::DynamicCast<MockThemeManager>(MockPipelineContext::GetCurrent()->GetThemeManager());
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<MockDialogTheme>()));
}

void DialogPatternTwoTestNg::UpdateDialogProperties(DialogProperties& props)
{
    /**
     * @tc.steps: step0. Update DialogProperties.
     */
    props.type = DialogType::ALERT_DIALOG;
    props.title = TITLE;
    props.subtitle = SUBTITLE;
    props.content = MESSAGE;
    props.buttonDirection = DialogButtonDirection::HORIZONTAL;
    vector<ButtonInfo> btnItems = {
        ButtonInfo {
            .text = "main button",
            .bgColor = Color::BLACK,
        },
        ButtonInfo {
            .text = "second button",
            .bgColor = Color::BLUE,
        },
        ButtonInfo {
            .text = "three button",
            .bgColor = Color::BLUE,
        },
    };
    props.buttons = btnItems;
}

void DialogPatternTwoTestNg::CheckTextMarquee(RefPtr<FrameNode> buttonNode)
{
    ASSERT_NE(buttonNode, nullptr);
    auto buttonProp = AceType::DynamicCast<ButtonLayoutProperty>(buttonNode->GetLayoutProperty());
    ASSERT_NE(buttonProp, nullptr);
    auto textNode = AceType::DynamicCast<FrameNode>(buttonNode->GetChildAtIndex(0));
    ASSERT_NE(textNode, nullptr);
    auto textProps = AceType::DynamicCast<TextLayoutProperty>(textNode->GetLayoutProperty());
    ASSERT_NE(textProps, nullptr);
    EXPECT_EQ(buttonProp->GetButtonStyle(), ButtonStyleMode::NORMAL);
    EXPECT_EQ(textProps->GetTextOverflow(), TextOverflow::MARQUEE);
    EXPECT_EQ(textProps->GetTextMarqueeStartPolicy(), MarqueeStartPolicy::ON_FOCUS);
    EXPECT_TRUE(textProps->GetTextMarqueeFadeout());
    NG::BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(DIALOG_BUTTON_BORDER_RADIUS);
    EXPECT_EQ(buttonProp->GetBorderRadius(), borderRadius);
}


/**
 * @tc.name: DialogPatternTest017
 * @tc.desc: fullfill DialogPattern function branch
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTwoTestNg, DialogPatternTest017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GestureEvent and DialogProperties.
     * @tc.expected: the GestureEvent and DialogProperties created successfully.
     */
    GestureEvent info;
    Offset globalLocation(10, 6);
    OffsetF translate(10, 5);
    DialogProperties param;
    param.autoCancel = true;
    param.buttons = btnItems;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<DialogTheme>()));
    /**
     * @tc.steps: step2. create dialog node.
     * @tc.expected: the dialog node created successfully.
     */
    auto child = FrameNode::GetOrCreateFrameNode(
        V2::CUSTOM_DIALOG_COMPONENT_TAG, 0, []() { return AceType::MakeRefPtr<DialogPattern>(nullptr, nullptr); });
    auto Dialog = DialogView::CreateDialogNode(param, child);
    EXPECT_TRUE(Dialog);
    ASSERT_NE(Dialog, nullptr);
    child->GetGeometryNode()->SetMarginFrameOffset(translate);
    EXPECT_EQ(Dialog->TotalChildCount(), 1);
    /**
     * @tc.steps: step3. create dialogPattern.
     * @tc.expected: the dialogPattern created successfully.
     */
    Recorder::EventParamsBuilder builderTest1;
    builderTest1.SetEventType(Recorder::EventType::DIALOG_CANCEL);
    Recorder::EventParamsBuilder builderTest2;
    builderTest2.SetEventType(Recorder::EventType::DIALOG_ACTION);
    auto dialogPattern = Dialog->GetPattern<DialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);
    ASSERT_NE(dialogPattern, nullptr);
    info.SetGlobalLocation(globalLocation);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(Dialog);
    CHECK_NULL_VOID(overlayManager);
    auto index = static_cast<int32_t>(Recorder::EventCategory::CATEGORY_COMPONENT);
    Recorder::EventRecorder::Get().eventSwitch_[index] = true;
    Recorder::EventRecorder::Get().globalSwitch_[index] = true;
    dialogPattern->RecordEvent(BUTTONINDEX_TEST_2);
    EXPECT_EQ(builderTest1.GetEventType(), Recorder::EventType::DIALOG_CANCEL);

    dialogPattern->RecordEvent(BUTTONINDEX_TEST_3);
    EXPECT_EQ(builderTest2.GetEventType(), Recorder::EventType::DIALOG_ACTION);
}

/**
 * @tc.name: DialogPatternTest020
 * @tc.desc: Test dialogPattern.UpdatePropertyForElderly function
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTwoTestNg, DialogPatternTest020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create DialogProperties.
     * @tc.expected: the DialogProperties created successfully.
     */
    DialogProperties props;
    props.type = DialogType::ALERT_DIALOG;
    props.title = TITLE;
    props.content = MESSAGE;
    props.buttonDirection = DialogButtonDirection::HORIZONTAL;
    vector<ButtonInfo> btnItems = {
        ButtonInfo {
            .text = "main button",
            .bgColor = Color::BLACK,
        },
        ButtonInfo {
            .text = "second button",
            .bgColor = Color::BLUE,
        },
        ButtonInfo {
            .text = "three button",
            .bgColor = Color::BLUE,
        },
    };
    props.buttons = btnItems;
    /**
     * @tc.steps: step2. create dialog node and dialogForOld node.
     * @tc.expected: the dialog node and dialogForOld node created successfully.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<DialogTheme>()));
    auto dialog = DialogView::CreateDialogNode(props, nullptr);
    ASSERT_NE(dialog, nullptr);
    auto dialogPattern = dialog->GetPattern<DialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);
    float expectedFontScale = 2.0f;
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetFontScale(expectedFontScale);
    SystemProperties::orientation_ = DeviceOrientation::LANDSCAPE;
    MockPipelineContext::GetCurrent()->windowManager_ = AceType::MakeRefPtr<WindowManager>();
    MockPipelineContext::GetCurrent()->windowManager_->SetWindowGetModeCallBack(
        []() -> WindowMode { return WindowMode::WINDOW_MODE_FULLSCREEN; });
    auto dialogForOld = DialogView::CreateDialogNode(props, nullptr);
    ASSERT_NE(dialogForOld, nullptr);
    auto dialogPatternOld = dialogForOld->GetPattern<DialogPattern>();
    ASSERT_NE(dialogPatternOld, nullptr);

    EXPECT_EQ(dialogPattern->isSuitableForElderly_, false);
    EXPECT_EQ(dialogPattern->notAdapationAging_, false);

    EXPECT_EQ(dialogPatternOld->isSuitableForElderly_, false);
    EXPECT_EQ(dialogPatternOld->notAdapationAging_, true);
}

/**
 * @tc.name: DialogPatternTest021
 * @tc.desc: Test dialogPattern.NeedsButtonDirectionChange function
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTwoTestNg, DialogPatternTest021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create DialogProperties.
     * @tc.expected: the DialogProperties created successfully.
     */
    DialogProperties props;
    props.type = DialogType::ALERT_DIALOG;
    props.title = TITLE;
    props.content = MESSAGE;
    props.buttonDirection = DialogButtonDirection::HORIZONTAL;
    vector<ButtonInfo> btnItems = {
        ButtonInfo {
            .text = "main button",
            .bgColor = Color::BLACK,
        },
        ButtonInfo {
            .text = "second button",
            .bgColor = Color::BLUE,
        },
        ButtonInfo {
            .text = "three button",
            .bgColor = Color::BLUE,
        },
    };
    props.buttons = btnItems;
    /**
     * @tc.steps: step2. create dialog node.
     * @tc.expected: the dialog node created successfully.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<DialogTheme>()));
    auto dialog = DialogView::CreateDialogNode(props, nullptr);
    ASSERT_NE(dialog, nullptr);
    auto dialogPattern = dialog->GetPattern<DialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);
    EXPECT_EQ(dialogPattern->buttonContainer_->GetTag(), V2::ROW_ETS_TAG);
    
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<ButtonTheme>()));
    dialogPattern->isSuitableForElderly_ = true;
    dialogPattern->AddButtonAndDivider(btnItems, dialogPattern->buttonContainer_, false);
    SystemProperties::orientation_ = DeviceOrientation::PORTRAIT;
    dialogPattern->BuildChild(props);
    EXPECT_EQ(dialogPattern->buttonContainer_->GetTag(), V2::COLUMN_ETS_TAG);
}

/**
 * @tc.name: DialogPatternTest022
 * @tc.desc: Test dialogPattern.UpdateDeviceOrientation function
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTwoTestNg, DialogPatternTest022, TestSize.Level1)
{
    /**
     * @tc.steps: step2. create DialogProperties.
     * @tc.expected: the DialogProperties created successfully.
     */
    DialogProperties props;
    props.type = DialogType::ALERT_DIALOG;
    props.title = TITLE;
    props.content = MESSAGE;
    props.buttonDirection = DialogButtonDirection::HORIZONTAL;
    vector<ButtonInfo> btnItems = {
        ButtonInfo {
            .text = "main button",
            .bgColor = Color::BLACK,
        },
        ButtonInfo {
            .text = "second button",
            .bgColor = Color::BLUE,
        },
    };
    props.buttons = btnItems;

    /**
     * @tc.steps: step3. create dialog node.
     * @tc.expected: the dialog node created successfully.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<DialogTheme>()));
    float expectedFontScale = 3.0f;
    float actualFontScale = 2.0f;
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetFontScale(expectedFontScale);
    auto dialog = DialogView::CreateDialogNode(props, nullptr);
    ASSERT_NE(dialog, nullptr);
    auto dialogPattern = dialog->GetPattern<DialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);
    dialogPattern->deviceOrientation_ = DeviceOrientation::PORTRAIT;
    SystemProperties::orientation_ = DeviceOrientation::LANDSCAPE;
    auto dialogLayoutProps = dialog->GetLayoutProperty<DialogLayoutProperty>();
    auto buttonLayoutConstraint = dialogLayoutProps->GetLayoutConstraint();
    dialog->Measure(buttonLayoutConstraint);
    CHECK_NULL_VOID(dialogPattern->titleContainer_);
    auto children = dialogPattern->titleContainer_->GetChildren();
    for (auto child : children) {
        auto textNode = AceType::DynamicCast<FrameNode>(dialogPattern->titleContainer_->GetChildAtIndex(0));
        CHECK_NULL_VOID(textNode);
        auto titleProp = AceType::DynamicCast<TextLayoutProperty>(textNode->GetLayoutProperty());
        CHECK_NULL_VOID(titleProp);
        EXPECT_EQ(titleProp->GetMaxFontScale().value_or(1.0), actualFontScale);
    }
}

/**
 * @tc.name: DialogPatternTest028
 * @tc.desc: DialogPattern borderWidth
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTwoTestNg, DialogPatternTest028, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GestureEvent and DialogProperties.
     * @tc.expected: the GestureEvent and DialogProperties created successfully.
     */
    DialogProperties param;
    BorderWidthPropertyT<Dimension> testPropertyT;

    testPropertyT.leftDimen = BORDER_WIDTH_PX_A;
    testPropertyT.rightDimen = BORDER_WIDTH_PX_B;
    testPropertyT.topDimen = BORDER_WIDTH_PX_C;
    testPropertyT.bottomDimen = BORDER_WIDTH_PX_D;

    param.borderWidth = testPropertyT;

    // isRightToLeft is true
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<DialogTheme>()));
    /**
     * @tc.steps: step2. create dialog node.
     * @tc.expected: the dialog node created successfully.
     */
    auto child = FrameNode::GetOrCreateFrameNode(
        V2::CUSTOM_DIALOG_COMPONENT_TAG, 0, []() { return AceType::MakeRefPtr<DialogPattern>(nullptr, nullptr); });

    auto Dialog = DialogView::CreateDialogNode(param, child);
    EXPECT_TRUE(Dialog);
    ASSERT_NE(Dialog, nullptr);
    EXPECT_EQ(Dialog->TotalChildCount(), 1);
    /**
     * @tc.steps: step3. create dialogPattern.
     * @tc.expected: pattern->dialogProperties_.borderWidth.value() equal to testPropertyT .
     */
    auto pattern = Dialog->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->dialogProperties_.borderWidth.value(), testPropertyT);
}


/**
 * @tc.name: DialogPatternTest029
 * @tc.desc: Test CreateDialogNode function with maskRect.
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTwoTestNg, DialogPatternTest029, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set maskRect width and height in positive number.
     * @tc.expected: step1. Create maskRect successfully.
     */
    DialogLayoutAlgorithm dialogLayoutAlgorithm;
    DialogProperties props;
    /**
     * @tc.steps: step2. Create Dialog and get DialogPattern.
     * @tc.expected: step2. Create Dialog and DialogPattern successfully.
     */
    auto dialog = DialogView::CreateDialogNode(props, nullptr);
    ASSERT_NE(dialog, nullptr);
    //isRightToLeft is true
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    OffsetF topLeftPoint_(30.0, 10.0);

    auto contentNode = AceType::DynamicCast<FrameNode>(dialog->GetFirstChild());
    ASSERT_NE(contentNode, nullptr);
    auto childLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        contentNode, contentNode->GetGeometryNode(), contentNode->GetLayoutProperty());
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(dialog, dialog->GetGeometryNode(), dialog->GetLayoutProperty());
    layoutWrapper->AppendChild(childLayoutWrapper);
    auto frameNode = layoutWrapper->GetHostNode();
    auto childSize = childLayoutWrapper->GetGeometryNode()->GetMarginFrameSize();

    dialogLayoutAlgorithm.ProcessMaskRect(
        DimensionRect(Dimension(childSize.Width()), Dimension(childSize.Height()), DimensionOffset(topLeftPoint_)),
        frameNode);

    /**
     * @tc.steps: step3. test GetMouseResponseRegion function.
     * @tc.expected: step3. return width equal to widthDimen.
     */
    auto hub = dialog->GetEventHub<DialogEventHub>();
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    std::vector<DimensionRect> mouseResponseRegion;
    mouseResponseRegion = gestureHub->GetMouseResponseRegion();
    EXPECT_EQ(mouseResponseRegion[0].GetOffset().GetX().Value(), 30.0);
}

/**
 * @tc.name: DialogPatternTest030
 * @tc.desc: Test dialogPattern.BuildTitle
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTwoTestNg, DialogPatternTest030, TestSize.Level1)
{
    /**
     * @tc.steps: step0. create and update DialogProperties.
     * @tc.expected: the DialogProperties created and update successfully.
     */
    DialogProperties props;
    UpdateDialogProperties(props);
    props.subtitle = "";
    /**
     * @tc.steps: step1. Create mock theme manager
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto textTheme = AceType::MakeRefPtr<TextTheme>();
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    auto buttonTheme = AceType::MakeRefPtr<ButtonTheme>();
    textTheme->isTextFadeout_ = true;
    dialogTheme->paddingSingleTitle_ = DIALOG_TITLE_PADDING;
    dialogTheme->button_type_ = 1;
    dialogTheme->buttonTextSize_ = 0.0_vp;
    dialogTheme->buttonBorderRadius_= DIALOG_BUTTON_BORDER_RADIUS;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([=](ThemeType type) -> RefPtr<Theme> {
        if (type == TextTheme::TypeId()) {
            return textTheme;
        } else if (type == DialogTheme::TypeId()) {
            return dialogTheme;
        } else {
            return buttonTheme;
        }
    });
    /**
     * @tc.steps: step2. create dialog node.
     * @tc.expected: the dialog node created successfully.
     */
    auto dialog = DialogView::CreateDialogNode(props, nullptr);
    ASSERT_NE(dialog, nullptr);
    auto dialogPattern = dialog->GetPattern<DialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);
    dialogPattern->isSuitableForElderly_ = true;
    dialogPattern->AddButtonAndDivider(btnItems, dialogPattern->buttonContainer_, false);
    SystemProperties::orientation_ = DeviceOrientation::PORTRAIT;
    dialogPattern->BuildChild(props);
    EXPECT_EQ(dialogPattern->titleContainer_->GetTag(), V2::ROW_ETS_TAG);
    /**
     * @tc.steps: step2. get titleTextNode && subTitleTextNode.
     * @tc.expected: The text padding is equal to dialogTheme_->GetPaddingSingleTitle().ConvertToPx() /
     * DIALOG_TITLE_AVE_BY_2 when only have title.
     */
    auto titleTextNode = AceType::DynamicCast<FrameNode>(dialogPattern->titleContainer_->GetChildAtIndex(0));
    ASSERT_NE(titleTextNode, nullptr);
    auto titleProp = AceType::DynamicCast<TextLayoutProperty>(titleTextNode->GetLayoutProperty());
    ASSERT_NE(titleProp, nullptr);
    const auto& titlePadding = titleProp->GetPaddingProperty();
    auto topPadding = titlePadding->top.value_or(CalcLength(0.0_vp)).GetDimension().ConvertToPx();
    auto bottomPadding = titlePadding->bottom.value_or(CalcLength(0.0_vp)).GetDimension().ConvertToPx();
    auto padding = DIALOG_TITLE_PADDING.ConvertToPx() / DIALOG_TITLE_AVE_BY_2;
    EXPECT_EQ(topPadding, padding);
    EXPECT_EQ(bottomPadding, padding);
    /**
     * @tc.steps: step2. get ButtonNode.
     * @tc.expected: Check the param value
     */
    EXPECT_EQ(dialogPattern->buttonContainer_->GetTag(), V2::COLUMN_ETS_TAG);
    for (auto child : dialogPattern->buttonContainer_->GetChildren()) {
        if (child->GetTag() != V2::BUTTON_ETS_TAG) {
            continue;
        }
        CheckTextMarquee(AceType::DynamicCast<FrameNode>(child));
    }
}

/**
 * @tc.name: DialogPatternTest031
 * @tc.desc: Test dialogPattern.BuildTitle
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTwoTestNg, DialogPatternTest031, TestSize.Level1)
{
    /**
     * @tc.steps: step0. create and update DialogProperties.
     * @tc.expected: the DialogProperties created and update successfully.
     */
    DialogProperties props;
    UpdateDialogProperties(props);
    /**
     * @tc.steps: step1. Create mock theme manager
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto textTheme = AceType::MakeRefPtr<TextTheme>();
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    auto buttonTheme = AceType::MakeRefPtr<ButtonTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([=](ThemeType type) -> RefPtr<Theme> {
        if (type == TextTheme::TypeId()) {
            return textTheme;
        } else if (type == DialogTheme::TypeId()) {
            return dialogTheme;
        } else {
            return buttonTheme;
        }
    });
    /**
     * @tc.steps: step2. create dialog node.
     * @tc.expected: the dialog node created successfully.
     */
    auto dialog = DialogView::CreateDialogNode(props, nullptr);
    ASSERT_NE(dialog, nullptr);
    auto dialogPattern = dialog->GetPattern<DialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);
    dialogPattern->BuildChild(props);
    ASSERT_NE(dialogPattern->titleContainer_, nullptr);
    EXPECT_EQ(dialogPattern->titleContainer_->GetTag(), V2::COLUMN_ETS_TAG);
    auto titleNode = AceType::DynamicCast<FrameNode>(dialogPattern->titleContainer_->GetChildAtIndex(0));
    auto subTitleNode = AceType::DynamicCast<FrameNode>(dialogPattern->titleContainer_->GetChildAtIndex(1));
    ASSERT_NE(titleNode, nullptr);
    ASSERT_NE(subTitleNode, nullptr);
    EXPECT_EQ(titleNode->GetTag(), V2::ROW_ETS_TAG);
    EXPECT_EQ(subTitleNode->GetTag(), V2::ROW_ETS_TAG);
    /**
     * @tc.steps: step2. get titleTextNode && subTitleTextNode.
     * @tc.expected: The text padding is equal to dialogTheme->GetPaddingTopTitle() when have title && subTitle.
     */
    auto titleTextNode = AceType::DynamicCast<FrameNode>(titleNode->GetChildAtIndex(0));
    auto subTitleTextNode = AceType::DynamicCast<FrameNode>(subTitleNode->GetChildAtIndex(0));
    ASSERT_NE(titleTextNode, nullptr);
    ASSERT_NE(subTitleTextNode, nullptr);
    EXPECT_EQ(titleTextNode->GetTag(), V2::TEXT_ETS_TAG);
    EXPECT_EQ(subTitleTextNode->GetTag(), V2::TEXT_ETS_TAG);
    auto titleProp = AceType::DynamicCast<TextLayoutProperty>(titleTextNode->GetLayoutProperty());
    auto subTitleProp = AceType::DynamicCast<TextLayoutProperty>(subTitleTextNode->GetLayoutProperty());
    ASSERT_NE(titleProp, nullptr);
    ASSERT_NE(subTitleProp, nullptr);
    const auto& titlePadding = titleProp->GetPaddingProperty();
    const auto& subTitlePadding = subTitleProp->GetPaddingProperty();
    auto topPadding = titlePadding->top.value_or(CalcLength(0.0_vp)).GetDimension().ConvertToPx();
    auto bottomPadding = subTitlePadding->bottom.value_or(CalcLength(0.0_vp)).GetDimension().ConvertToPx();
    EXPECT_EQ(topPadding, dialogTheme->GetPaddingTopTitle().ConvertToPx());
    EXPECT_EQ(bottomPadding, dialogTheme->GetPaddingTopTitle().ConvertToPx());
}

/**
 * @tc.name: DialogPatternTest034
 * @tc.desc: Test AdjustHoverModeForWaterfall
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTwoTestNg, DialogPatternTest034, TestSize.Level1)
{
    DialogLayoutAlgorithm dialogLayoutAlgorithm;
    auto frameNode = AceType::MakeRefPtr<FrameNode>("test1", 1, AceType::MakeRefPtr<DialogPattern>(nullptr, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto dialogLayoutProperty = AceType::MakeRefPtr<DialogLayoutProperty>();
    ASSERT_NE(dialogLayoutProperty, nullptr);
    dialogLayoutProperty->UpdateEnableHoverMode(true);
    frameNode->layoutProperty_ = dialogLayoutProperty;
    dialogLayoutAlgorithm.AdjustHoverModeForWaterfall(frameNode);
    EXPECT_FALSE(dialogLayoutAlgorithm.isHoverMode_);
    MockSystemProperties::g_isSuperFoldDisplayDevice = true;
    RefPtr<MockContainer> containerOne = AceType::MakeRefPtr<MockContainer>();
    RefPtr<MockContainer> containerTwo = AceType::MakeRefPtr<MockContainer>();
    MockContainer::Current()->GetMockDisplayInfo()->SetFoldStatus(FoldStatus::HALF_FOLD);
    AceEngine::Get().AddContainer(0, containerOne);
    AceEngine::Get().AddContainer(1, containerTwo);
    dialogLayoutAlgorithm.expandDisplay_ = true;
    dialogLayoutAlgorithm.AdjustHoverModeForWaterfall(frameNode);
    EXPECT_FALSE(dialogLayoutAlgorithm.isHoverMode_);
}

/**
 * @tc.name: DialogPatternTest032
 * @tc.desc: Test dialogPattern.BuildTitle
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTwoTestNg, DialogPatternTest032, TestSize.Level1)
{
    /**
     * @tc.steps: step0. create and update DialogProperties.
     * @tc.expected: the DialogProperties created and update successfully.
     */
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetFollowSystem(true);
    pipeline->SetMaxAppFontScale(FONT_SIZE_SCALE_TEST2);
    DialogProperties props;
    UpdateDialogProperties(props);
    /**
     * @tc.steps: step1. Create mock theme manager
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto textTheme = AceType::MakeRefPtr<TextTheme>();
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    auto buttonTheme = AceType::MakeRefPtr<ButtonTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([=](ThemeType type) -> RefPtr<Theme> {
        if (type == TextTheme::TypeId()) {
            return textTheme;
        } else if (type == DialogTheme::TypeId()) {
            return dialogTheme;
        } else {
            return buttonTheme;
        }
    });
    /**
     * @tc.steps: step2. create dialog node.
     * @tc.expected: the dialog node created successfully.
     */
    auto dialog = DialogView::CreateDialogNode(props, nullptr);
    ASSERT_NE(dialog, nullptr);
    auto dialogPattern = dialog->GetPattern<DialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);
    dialogPattern->BuildChild(props);
    ASSERT_NE(dialogPattern->titleContainer_, nullptr);
    EXPECT_EQ(dialogPattern->titleContainer_->GetTag(), V2::COLUMN_ETS_TAG);
    auto titleNode = AceType::DynamicCast<FrameNode>(dialogPattern->titleContainer_->GetChildAtIndex(0));
    auto subTitleNode = AceType::DynamicCast<FrameNode>(dialogPattern->titleContainer_->GetChildAtIndex(1));
    ASSERT_NE(titleNode, nullptr);
    ASSERT_NE(subTitleNode, nullptr);
    EXPECT_EQ(titleNode->GetTag(), V2::ROW_ETS_TAG);
    EXPECT_EQ(subTitleNode->GetTag(), V2::ROW_ETS_TAG);
    /**
     * @tc.steps: step3. get titleTextNode && subTitleTextNode.
     * @tc.expected: The text padding is equal to dialogTheme->GetPaddingTopTitle() when have title && subTitle.
     */
    auto titleTextNode = AceType::DynamicCast<FrameNode>(titleNode->GetChildAtIndex(0));
    auto subTitleTextNode = AceType::DynamicCast<FrameNode>(subTitleNode->GetChildAtIndex(0));
    ASSERT_NE(titleTextNode, nullptr);
    ASSERT_NE(subTitleTextNode, nullptr);
    EXPECT_EQ(titleTextNode->GetTag(), V2::TEXT_ETS_TAG);
    EXPECT_EQ(subTitleTextNode->GetTag(), V2::TEXT_ETS_TAG);
    auto titleProp = AceType::DynamicCast<TextLayoutProperty>(titleTextNode->GetLayoutProperty());
    auto subTitleProp = AceType::DynamicCast<TextLayoutProperty>(subTitleTextNode->GetLayoutProperty());
    ASSERT_NE(titleProp, nullptr);
    ASSERT_NE(subTitleProp, nullptr);
    EXPECT_EQ(titleProp->GetMaxFontScale().value(), FONT_MAX_SIZE_SCALE);
    EXPECT_EQ(subTitleProp->GetMaxFontScale().value(), FONT_MAX_SIZE_SCALE);
}

/**
 * @tc.name: DialogPatternTest033
 * @tc.desc: Test dialogPattern.BuildTitle
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTwoTestNg, DialogPatternTest033, TestSize.Level1)
{
    /**
     * @tc.steps: step0. create and update DialogProperties.
     * @tc.expected: the DialogProperties created and update successfully.
     */
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetFollowSystem(true);
    pipeline->SetMaxAppFontScale(FONT_SIZE_SCALE_TEST1);
    DialogProperties props;
    UpdateDialogProperties(props);
    /**
     * @tc.steps: step1. create dialog node.
     * @tc.expected: the dialog node created successfully.
     */
    auto dialog = DialogView::CreateDialogNode(props, nullptr);
    ASSERT_NE(dialog, nullptr);
    auto dialogPattern = dialog->GetPattern<DialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);
    dialogPattern->BuildChild(props);
    ASSERT_NE(dialogPattern->titleContainer_, nullptr);
    EXPECT_EQ(dialogPattern->titleContainer_->GetTag(), V2::COLUMN_ETS_TAG);
    auto titleNode = AceType::DynamicCast<FrameNode>(dialogPattern->titleContainer_->GetChildAtIndex(0));
    auto subTitleNode = AceType::DynamicCast<FrameNode>(dialogPattern->titleContainer_->GetChildAtIndex(1));
    ASSERT_NE(titleNode, nullptr);
    ASSERT_NE(subTitleNode, nullptr);
    EXPECT_EQ(titleNode->GetTag(), V2::ROW_ETS_TAG);
    EXPECT_EQ(subTitleNode->GetTag(), V2::ROW_ETS_TAG);
    /**
     * @tc.steps: step2. get titleTextNode && subTitleTextNode.
     * @tc.expected: The text padding is equal to dialogTheme->GetPaddingTopTitle() when have title && subTitle.
     */
    auto titleTextNode = AceType::DynamicCast<FrameNode>(titleNode->GetChildAtIndex(0));
    auto subTitleTextNode = AceType::DynamicCast<FrameNode>(subTitleNode->GetChildAtIndex(0));
    ASSERT_NE(titleTextNode, nullptr);
    ASSERT_NE(subTitleTextNode, nullptr);
    EXPECT_EQ(titleTextNode->GetTag(), V2::TEXT_ETS_TAG);
    EXPECT_EQ(subTitleTextNode->GetTag(), V2::TEXT_ETS_TAG);
    auto titleProp = AceType::DynamicCast<TextLayoutProperty>(titleTextNode->GetLayoutProperty());
    auto subTitleProp = AceType::DynamicCast<TextLayoutProperty>(subTitleTextNode->GetLayoutProperty());
    ASSERT_NE(titleProp, nullptr);
    ASSERT_NE(subTitleProp, nullptr);
    EXPECT_EQ(titleProp->GetMaxFontScale().value(), FONT_SIZE_SCALE_TEST1);
    EXPECT_EQ(subTitleProp->GetMaxFontScale().value(), FONT_SIZE_SCALE_TEST1);
}
} // namespace OHOS::Ace::NG
