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
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "core/common/recorder/event_recorder.h"

#include "core/components/button/button_theme.h"
#include "core/components/dialog/dialog_properties.h"
#include "core/components_ng/base/view_stack_processor.h"
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
const int32_t buttonIdx = 1;
const double_t WIDTH_A = 16.0;
const double_t WIDTH_B = 48.0;
const double_t WIDTH_C = 64.0;
const double_t WIDTH_D = 80.0;
const double_t WIDTH_E = 112.0;
const double_t DIVISOR = 2.0;
const Dimension DIMENSION_RADIUS(10.0, DimensionUnit::PX);
constexpr int BUTTONINDEX_TEST_1 = 1;
constexpr int BUTTONINDEX_TEST_2 = -1;
constexpr int BUTTONINDEX_TEST_3 = -2;
constexpr int DIALOG_TITLE_AVE_BY_2 = 2;
const Dimension DIALOG_TITLE_PADDING { 10.0, DimensionUnit::VP };
const Dimension BORDER_WIDTH_PX_A { 10.0, DimensionUnit::PX };
const Dimension BORDER_WIDTH_PX_B { 20.0, DimensionUnit::PX };
const Dimension BORDER_WIDTH_PX_C { 30.0, DimensionUnit::PX };
const Dimension BORDER_WIDTH_PX_D { 40.0, DimensionUnit::PX };
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
            RefPtr<MockDialogTheme> theme = AceType::Claim(new MockDialogTheme());
            return theme;
        }
    };

    ~MockDialogTheme() override = default;

protected:
    MockDialogTheme() = default;
};

class DialogPatternTestNg : public testing::Test {
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

void DialogPatternTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}
void DialogPatternTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}
void DialogPatternTestNg::SetDialogTheme()
{
    auto themeManager = AceType::DynamicCast<MockThemeManager>(MockPipelineContext::GetCurrent()->GetThemeManager());
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<MockDialogTheme>()));
}

void DialogPatternTestNg::UpdateDialogProperties(DialogProperties& props)
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

void DialogPatternTestNg::CheckTextMarquee(RefPtr<FrameNode> buttonNode)
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
}

/**
 * @tc.name: DialogFrameNodeCreator004
 * @tc.desc: Test AlertDialog with button color and text color
 * @tc.type: FUNC
 * @tc.author: zhoutianer
 */
HWTEST_F(DialogPatternTestNg, DialogFrameNodeCreator004, TestSize.Level1)
{
    auto dialogEventHub = AceType::MakeRefPtr<DialogEventHub>();
    bool isCalled = false;
    dialogEventHub->SetOnCancel([&isCalled]() { isCalled = true; });
    dialogEventHub->FireCancelEvent();
    EXPECT_EQ(true, isCalled);
}

/**
 * @tc.name: DialogFrameNodeCreator005
 * @tc.desc: Test AlertDialog with button color and text color
 * @tc.type: FUNC
 * @tc.author: zhoutianer
 */
HWTEST_F(DialogPatternTestNg, DialogFrameNodeCreator005, TestSize.Level1)
{
    auto dialogEventHub = AceType::MakeRefPtr<DialogEventHub>();
    dialogEventHub->FireCancelEvent();
    EXPECT_EQ(dialogEventHub->onCancel_ == nullptr, true);
}

/**
 * @tc.name: DialogFrameNodeCreator006
 * @tc.desc: Test AlertDialog with button color and text color
 * @tc.type: FUNC
 * @tc.author: zhoutianer
 */
HWTEST_F(DialogPatternTestNg, DialogFrameNodeCreator006, TestSize.Level1)
{
    bool isCalled = false;
    auto dialogEventHub = AceType::MakeRefPtr<DialogEventHub>();
    dialogEventHub->SetOnSuccess([&isCalled](int32_t, int32_t) { isCalled = true; });
    dialogEventHub->FireSuccessEvent(0);
    EXPECT_TRUE(isCalled);
}

/**
 * @tc.name: DialogFrameNodeCreator0007
 * @tc.desc: Test AlertDialog with button color and text color
 * @tc.type: FUNC
 * @tc.author: zhoutianer
 */
HWTEST_F(DialogPatternTestNg, DialogFrameNodeCreator0007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create dialogEventHub object.
     * tc.expected:the dialogEventHub created successfully.
     */
    auto dialogEventHub = AceType::MakeRefPtr<DialogEventHub>();
    dialogEventHub->FireSuccessEvent(buttonIdx);
    EXPECT_EQ(dialogEventHub->onSuccess_ == nullptr, true);
}

/**
 * @tc.name: DialogFrameNodeCreator0020
 * @tc.desc: Test AlertDialog with button color and text color
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestNg, DialogFrameNodeCreator0020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create params and DialogLayoutAlgorithm object.
     * tc.expected: the params and DialogLayoutAlgorithm created successfully.
     */
    const DialogAlignment aligns[] = {
        DialogAlignment::TOP,
        DialogAlignment::CENTER,
        DialogAlignment::BOTTOM,
        DialogAlignment::DEFAULT,
        DialogAlignment::TOP_START,
        DialogAlignment::TOP_END,
        DialogAlignment::CENTER_START,
        DialogAlignment::CENTER_END,
        DialogAlignment::BOTTOM_START,
        DialogAlignment::BOTTOM_END,
    };
    auto maxSize = SizeF(WIDTH_B, WIDTH_C);
    auto childSize = SizeF(WIDTH_D, WIDTH_E);
    auto dialogLayoutAlgorithm = AceType::MakeRefPtr<DialogLayoutAlgorithm>();
    OffsetF topLeftPoint =
        OffsetF(maxSize.Width() - childSize.Width(), maxSize.Height() - childSize.Height()) / DIVISOR;
    /**
     * @tc.steps: step2. call SetAlignmentSwitch function.
     * @tc.expected: the results are correct.
     */
    for (size_t i = 0; i < sizeof(aligns) / sizeof(aligns[0]); i++) {
        dialogLayoutAlgorithm->alignment_ = aligns[i];
        auto result = dialogLayoutAlgorithm->SetAlignmentSwitch(maxSize, childSize, topLeftPoint);
        if (i == 3) {
            EXPECT_FALSE(result);
        } else {
            EXPECT_TRUE(result);
        }
    }

    /**
     * @tc.steps: step3. call SetAlignmentSwitch function in api version 12.
     * @tc.expected: the results are correct.
     */
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    for (size_t i = 0; i < sizeof(aligns) / sizeof(aligns[0]); i++) {
        dialogLayoutAlgorithm->alignment_ = aligns[i];
        auto result = dialogLayoutAlgorithm->SetAlignmentSwitch(maxSize, childSize, topLeftPoint);
        EXPECT_TRUE(result);
    }
}

/**
 * @tc.name: DialogFrameNodeCreator0021
 * @tc.desc: Test Dialog IsAlignmentByWholeScreen
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestNg, DialogFrameNodeCreator0021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create params and DialogLayoutAlgorithm object.
     * tc.expected: the params and DialogLayoutAlgorithm created successfully.
     */
    const DialogAlignment aligns[] = {
        DialogAlignment::TOP,
        DialogAlignment::CENTER,
        DialogAlignment::BOTTOM,
        DialogAlignment::DEFAULT,
        DialogAlignment::TOP_START,
        DialogAlignment::TOP_END,
        DialogAlignment::CENTER_START,
        DialogAlignment::CENTER_END,
        DialogAlignment::BOTTOM_START,
        DialogAlignment::BOTTOM_END,
    };
    auto dialogLayoutAlgorithm = AceType::MakeRefPtr<DialogLayoutAlgorithm>();
    /**
     * @tc.steps: step2. call IsAlignmentByWholeScreen function in api version 11.
     * @tc.expected: the results are correct.
     */
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    for (size_t i = 0; i < sizeof(aligns) / sizeof(aligns[0]); i++) {
        dialogLayoutAlgorithm->alignment_ = aligns[i];
        auto result = dialogLayoutAlgorithm->IsAlignmentByWholeScreen();
        EXPECT_FALSE(result);
    }

    /**
     * @tc.steps: step3. call IsAlignmentByWholeScreen function in api version 12.
     * @tc.expected: the results are correct.
     */
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    for (size_t i = 0; i < sizeof(aligns) / sizeof(aligns[0]); i++) {
        dialogLayoutAlgorithm->alignment_ = aligns[i];
        auto result = dialogLayoutAlgorithm->IsAlignmentByWholeScreen();
        if (i == 1 || i == 3 || i == 6 || i == 7) {
            EXPECT_TRUE(result);
        } else {
            EXPECT_FALSE(result);
        }
    }
}

/**
 * @tc.name: DialogAccessibilityProperty001
 * @tc.desc: Test Action Sheet Accessibility Property
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestNg, DialogAccessibilityProperty001, TestSize.Level1)
{
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    /**
     * @tc.steps: step1. create dialogNode and dialogTheme instance.
     * @tc.expected: the dialogNode and dialogNode created successfully.
     */
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> dialog = FrameNode::CreateFrameNode(
        V2::ACTION_SHEET_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(dialog, nullptr);
    /**
     * @tc.steps: step2. create dialogPattern and do PopDialog.
     * @tc.expected: the dialogPattern  created successfully.
     */
    auto pattern = dialog->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->title_ = TITLE;
    pattern->message_ = MESSAGE;
    auto accessibilityProperty = dialog->GetAccessibilityProperty<NG::AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(), TITLE + MESSAGE);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: ToJsonValue
 * @tc.desc: Test AlertDialog with button color and text color
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestNg, ToJsonValue, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create dialogNode and dialogTheme instance.
     * @tc.expected: the dialogNode and dialogNode created successfully.
     */
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> dialog = FrameNode::CreateFrameNode(
        V2::ACTION_SHEET_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(dialog, nullptr);
    /**
     * @tc.steps: step2. create dialogPattern and do PopDialog.
     * @tc.expected: the dialogPattern  created successfully.
     */
    auto pattern = dialog->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->title_ = TITLE;
    pattern->message_ = MESSAGE;
    /**
     * @tc.steps: step3. test AlertDialog with button color and text color
     * @tc.expected: json->GetKey() equal to "".
     */
    std::unique_ptr<JsonValue> json = JsonUtil::Create(true);
    pattern->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetKey(), "");
}

/**
 * @tc.name: PopDialog
 * @tc.desc: Dialog already in close
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestNg, PopDialog, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create dialogNode and dialogTheme instance.
     * @tc.expected: the dialogNode and dialogNode created successfully.
     */
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> dialog = FrameNode::CreateFrameNode(
        V2::ACTION_SHEET_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(dialog, nullptr);
    /**
     * @tc.steps: step2. create dialogPattern and do PopDialog.
     * @tc.expected: the dialogPattern  created successfully.
     */
    auto pattern = dialog->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->title_ = TITLE;
    pattern->message_ = MESSAGE;
    pattern->PopDialog(0);
}

/**
 * @tc.name: DialogAccessibilityProperty002
 * @tc.desc: Test Alert Accessibility Property
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestNg, DialogAccessibilityProperty002, TestSize.Level1)
{
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    /**
     * @tc.steps: step1. create dialogNode and dialogTheme instance.
     * @tc.expected: the dialogNode and dialogNode created successfully.
     */
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> dialog = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(dialog, nullptr);
    /**
     * @tc.steps: step2. create dialogPattern and do PopDialog.
     * @tc.expected: the dialogPattern  created successfully.
     */
    auto pattern = dialog->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->title_ = TITLE;
    pattern->message_ = MESSAGE;
    auto accessibilityProperty = dialog->GetAccessibilityProperty<NG::AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(), TITLE + MESSAGE);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: DialogPatternTest001
 * @tc.desc: Test GetMaxWidthBasedOnGridType function
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestNg, DialogPatternTest001, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(dialogTheme));
    /**
     * @tc.steps: step1. create params and DialogLayoutAlgorithm object.
     */
    const ScreenSizeType types[] = { ScreenSizeType::SM, ScreenSizeType::MD, ScreenSizeType::LG,
        ScreenSizeType::UNDEFINED };
    const DeviceType deviceTypes[] = { DeviceType::WATCH, DeviceType::PHONE, DeviceType::CAR, DeviceType::UNKNOWN };
    auto columnInfo = GridSystemManager::GetInstance().GetInfoByType(GridColumnType::CAR_DIALOG);
    auto dialogLayoutAlgorithm = AceType::MakeRefPtr<DialogLayoutAlgorithm>();

    /**
     * @tc.steps: step2. call GetMaxWidthBasedOnGridType function.
     * @tc.expected: the result equal to WIDTH_A.
     */
    for (size_t i = 0; i < sizeof(deviceTypes) / sizeof(deviceTypes[0]); i++) {
        for (size_t j = 0; j < sizeof(types) / sizeof(types[0]); j++) {
            auto Width = dialogLayoutAlgorithm->GetMaxWidthBasedOnGridType(columnInfo, types[j], deviceTypes[i]);
            EXPECT_EQ(Width, WIDTH_A);
        }
    }
}

/**
 * @tc.name: DialogPatternTest002
 * @tc.desc: Test CreateDialogNode
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestNg, DialogPatternTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set properties
     */
    const DialogType types[] = { DialogType::ALERT_DIALOG, DialogType::ACTION_SHEET, DialogType::COMMON };
    SetDialogTheme();
    /**
     * @tc.steps: step2. call CreateDialogNode function with different props.
     * @tc.expected: the dialog node created successfully.
     */
    for (size_t i = 0; i < sizeof(types) / sizeof(types[0]); i++) {
        DialogProperties props;
        props.type = types[i];
        if (i == 1) {
            props.title = "dialog test";
            props.content = "dialog content test";
            props.customStyle = true;
            props.sheetsInfo = sheetItems;
            props.isMenu = true;
            props.buttons = btnItems;
        } else if (i == 0) {
            props.buttons = btnItems;
        }
        auto dialog = DialogView::CreateDialogNode(props, nullptr);
        ASSERT_NE(dialog, nullptr);
        /**
         * @tc.steps: step3. call keyEvent callback.
         * @tc.expected: the results of keyEevnts are correct.
         */
        auto focusHub = dialog->GetOrCreateFocusHub();
        ASSERT_NE(focusHub, nullptr);
        KeyEvent keyEvent(KeyCode::KEY_0, KeyAction::CLICK);
        KeyEvent keyEvent2(KeyCode::KEY_ESCAPE, KeyAction::DOWN);
        KeyEvent keyEvent3(KeyCode::KEY_0, KeyAction::DOWN);
        auto ret = focusHub->ProcessOnKeyEventInternal(keyEvent);
        auto ret2 = focusHub->ProcessOnKeyEventInternal(keyEvent2);
        auto ret3 = focusHub->ProcessOnKeyEventInternal(keyEvent3);
        EXPECT_FALSE(ret);
        EXPECT_FALSE(ret2);
        EXPECT_FALSE(ret3);
    }
}

/**
 * @tc.name: CustomDialogTestNg001
 * @tc.desc: Verify function CreateDialogNode
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestNg, CustomDialogTestNg001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create DialogProperties.
     * @tc.expected: the DialogProperties created successfully.
     */
    DialogProperties param;
    param.maskColor = Color::BLACK;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<DialogTheme>()));
    /**
     * @tc.steps: step2. create dialog node.
     * @tc.expected: the dialog node created successfully.
     */
    auto result = DialogView::CreateDialogNode(param, nullptr);
    EXPECT_TRUE(result);
    if (result) {
        EXPECT_EQ(result->GetRenderContext()->GetBackgroundColorValue(Color::TRANSPARENT).GetValue(),
            Color::BLACK.GetValue());
    }
}

/**
 * @tc.name: CustomDialogTestNg002
 * @tc.desc: Verify function CreateDialogNode
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestNg, CustomDialogTestNg002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create DialogProperties.
     * @tc.expected: the DialogProperties created successfully.
     */
    DialogProperties param;
    param.maskColor = Color::BLACK;
    param.type = DialogType::ALERT_DIALOG;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<DialogTheme>()));
    /**
     * @tc.steps: step2. create dialog node.
     * @tc.expected: the dialog node created successfully.
     */
    auto result = DialogView::CreateDialogNode(param, nullptr);
    EXPECT_TRUE(result);
    if (result) {
        EXPECT_EQ(result->GetRenderContext()->GetBackgroundColorValue(Color::TRANSPARENT).GetValue(),
            Color::BLACK.GetValue());
    }
}

/**
 * @tc.name: CustomDialogTestNg003
 * @tc.desc: Verify function CreateDialogNode
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestNg, CustomDialogTestNg003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create DialogProperties.
     * @tc.expected: the DialogProperties created successfully.
     */
    DialogProperties param;
    param.maskColor = Color::BLACK;
    param.type = DialogType::ACTION_SHEET;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<DialogTheme>()));
    /**
     * @tc.steps: step2. create dialog node.
     * @tc.expected: the dialog node created successfully.
     */
    auto result = DialogView::CreateDialogNode(param, nullptr);
    EXPECT_TRUE(result);
    if (result) {
        EXPECT_EQ(result->GetRenderContext()->GetBackgroundColorValue(Color::TRANSPARENT).GetValue(),
            Color::BLACK.GetValue());
    }
}

/**
 * @tc.name: CustomDialogTestNg004
 * @tc.desc: Verify function GetCloseAnimation and GetOpenAnimation
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestNg, CustomDialogTestNg004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create DialogProperties.
     * @tc.expected: the DialogProperties created successfully.
     */
    DialogProperties param;
    AnimationOption animationOption;
    animationOption.SetDelay(10);
    param.openAnimation = animationOption;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<DialogTheme>()));
    /**
     * @tc.steps: step2. create dialog node.
     * @tc.expected: the dialog node created successfully.
     */
    auto result = DialogView::CreateDialogNode(param, nullptr);
    EXPECT_TRUE(result);
    if (!result) {
        return;
    }
    /**
     * @tc.steps: step3. create dialogPattern.
     * @tc.expected: the dialogPattern created successfully.
     */
    auto dialogPattern = result->GetPattern<DialogPattern>();
    EXPECT_TRUE(dialogPattern);
    if (!dialogPattern) {
        return;
    }
    if (dialogPattern->GetOpenAnimation().has_value()) {
        EXPECT_EQ(dialogPattern->GetOpenAnimation().value().GetDelay(), animationOption.GetDelay());
    }

    if (dialogPattern->GetCloseAnimation().has_value()) {
        EXPECT_EQ(dialogPattern->GetCloseAnimation().value().GetDelay(), animationOption.GetDelay());
    }
}

/**
 * @tc.name: CustomDialogTestNg005
 * @tc.desc: Verify function HandleClick
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestNg, CustomDialogTestNg005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GestureEvent and DialogProperties.
     * @tc.expected: the GestureEvent and DialogProperties created successfully.
     */
    GestureEvent info;
    Offset globalLocation(10, 6);
    OffsetF translate(10, 5);
    DialogProperties param;
    param.autoCancel = false;
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
    auto dialogPattern = Dialog->GetPattern<DialogPattern>();
    EXPECT_TRUE(dialogPattern);
    ASSERT_NE(dialogPattern, nullptr);
    info.SetGlobalLocation(globalLocation);
    dialogPattern->HandleClick(info);
}

/**
 * @tc.name: CustomDialogTestNg006
 * @tc.desc: Verify function HandleClick
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestNg, CustomDialogTestNg006, TestSize.Level1)
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
    auto dialogPattern = Dialog->GetPattern<DialogPattern>();
    EXPECT_TRUE(dialogPattern);
    ASSERT_NE(dialogPattern, nullptr);
    info.SetGlobalLocation(globalLocation);
    dialogPattern->HandleClick(info);
}

/**
 * @tc.name: DialogPatternTest005
 * @tc.desc: CreateDialogNode
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestNg, DialogPatternTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set properties
     */
    const DialogType types[] = { DialogType::ALERT_DIALOG, DialogType::ACTION_SHEET, DialogType::COMMON };
    SetDialogTheme();
    /**
     * @tc.steps: step2. call CreateDialogNode function with different props.
     * @tc.expected: the dialog node created successfully.
     */
    for (size_t i = 0; i < sizeof(types) / sizeof(types[0]); i++) {
        DialogProperties props;
        props.type = types[i];
        if (i == 1) {
            props.title = "dialog test";
            props.content = "dialog content test";
            props.customStyle = true;
            props.sheetsInfo = sheetItems;
            props.isMenu = true;
            props.buttons = btnItems2;
            props.backgroundColor = Color::BLACK;
            props.borderRadius->radiusTopLeft = Dimension('20PX');
            props.borderRadius->radiusTopRight = Dimension('20PX');
            props.borderRadius->radiusBottomRight = Dimension('20PX');
            props.borderRadius->radiusBottomLeft = Dimension('20PX');
            props.borderRadius->multiValued = false;
        } else if (i == 0) {
            props.buttons = btnItems1;
        }
        auto dialog = DialogView::CreateDialogNode(props, nullptr);
        ASSERT_NE(dialog, nullptr);
        auto dialogPattern = dialog->GetPattern<DialogPattern>();
        EXPECT_TRUE(dialogPattern);
        ASSERT_NE(dialogPattern, nullptr);
        dialogPattern->GetSubtitle();
    }
}

/**
 * @tc.name: DialogPatternTest006
 * @tc.desc: CreateDialogNode
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestNg, DialogPatternTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set properties
     */
    const DialogButtonDirection directions[] = { DialogButtonDirection::AUTO, DialogButtonDirection::HORIZONTAL,
        DialogButtonDirection::VERTICAL };
    SetDialogTheme();
    /**
     * @tc.steps: step2. call CreateDialogNode function with different props.
     * @tc.expected: the dialog node created successfully.
     */
    for (size_t i = 0; i < sizeof(directions) / sizeof(directions[0]); i++) {
        DialogProperties props;
        props.type = DialogType::ALERT_DIALOG;
        props.title = "dialog test";
        props.content = "dialog content test";
        props.buttons = btnItems2;
        props.buttonDirection = directions[i];
        auto dialog = DialogView::CreateDialogNode(props, nullptr);
        ASSERT_NE(dialog, nullptr);
        auto dialogPattern = dialog->GetPattern<DialogPattern>();
        EXPECT_TRUE(dialogPattern);
        ASSERT_NE(dialogPattern, nullptr);
        EXPECT_EQ(dialogPattern->GetDialogProperties().buttonDirection, directions[i]);
    }
}

/**
 * @tc.name: DialogPatternTest007
 * @tc.desc: Test DialogPattern OnColorConfigurationUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestNg, DialogPatternTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set properties
     * @tc.expected: step1. Create Dialog and get DialogPattern successfully.
     */
    SetDialogTheme();
    DialogProperties props;
    props.type = DialogType::ALERT_DIALOG;
    props.title = TITLE;
    props.content = MESSAGE;
    props.buttons = btnItems;
    auto dialog = DialogView::CreateDialogNode(props, nullptr);
    ASSERT_NE(dialog, nullptr);
    auto dialogPattern = dialog->GetPattern<DialogPattern>();
    EXPECT_TRUE(dialogPattern);
    ASSERT_NE(dialogPattern, nullptr);
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    /**
     * @tc.steps: step2. Call OnColorConfigurationUpdate
     * @tc.expected: step2. cover branch customStyle == false.
     */
    dialogPattern->OnColorConfigurationUpdate();
    EXPECT_EQ(dialogTheme->GetBackgroundColor(), Color::BLACK);
    /**
     * @tc.steps: step3. set isMenu is true.
     */
    props.type = DialogType::ACTION_SHEET;
    props.customStyle = true;
    props.sheetsInfo = sheetItems;
    props.isMenu = true;
    dialog = DialogView::CreateDialogNode(props, nullptr);
    ASSERT_NE(dialog, nullptr);
    dialogPattern = dialog->GetPattern<DialogPattern>();
    EXPECT_TRUE(dialogPattern);
    ASSERT_NE(dialogPattern, nullptr);
    /**
     * @tc.steps: step4. Call OnColorConfigurationUpdate
     * @tc.expected: step4. cover branch menuNode_ is not null.
     */
    dialogPattern->OnColorConfigurationUpdate();
    EXPECT_EQ(dialogTheme->GetBackgroundColor(), Color::BLACK);
}

/**
 * @tc.name: DialogPatternTest008
 * @tc.desc: Test CreateDialogNode function with maskRect.
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestNg, DialogPatternTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set maskRect width and height in positive number.
     * @tc.expected: step1. Create maskRect successfully.
     */
    DialogProperties props;
    CalcDimension xDimen = CalcDimension(0.0, DimensionUnit::VP);
    CalcDimension yDimen = CalcDimension(0.0, DimensionUnit::VP);
    CalcDimension widthDimen = CalcDimension(0.5, DimensionUnit::PERCENT);
    CalcDimension heightDimen = CalcDimension(0.5, DimensionUnit::PERCENT);
    DimensionOffset offsetDimen(xDimen, yDimen);
    DimensionRect Rect(widthDimen, heightDimen, offsetDimen);
    props.maskRect = Rect;
    /**
     * @tc.steps: step2. Create Dialog and get DialogPattern.
     * @tc.expected: step2. Create Dialog and DialogPattern successfully.
     */
    auto dialog = DialogView::CreateDialogNode(props, nullptr);
    ASSERT_NE(dialog, nullptr);
    auto dialogPattern = dialog->GetPattern<DialogPattern>();
    EXPECT_TRUE(dialogPattern);
    ASSERT_NE(dialogPattern, nullptr);
    /**
     * @tc.steps: step3. test GetMouseResponseRegion function.
     * @tc.expected: step3. return width equal to widthDimen.
     */
    auto hub = dialog->GetEventHub<DialogEventHub>();
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    std::vector<DimensionRect> mouseResponseRegion;
    std::vector<DimensionRect> initMouseResponseRegion;
    initMouseResponseRegion.push_back(Rect);
    gestureHub->SetMouseResponseRegion(initMouseResponseRegion);
    mouseResponseRegion = gestureHub->GetMouseResponseRegion();
    EXPECT_EQ(mouseResponseRegion[0].GetWidth().Value(), widthDimen.Value());
    EXPECT_EQ(mouseResponseRegion[0].GetHeight().Value(), heightDimen.Value());
}

/**
 * @tc.name: DialogPatternTest009
 * @tc.desc: Test CreateDialogNode function with maskRect.
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestNg, DialogPatternTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set maskRect width and height in negative number.
     * @tc.expected: the maskRect created successfully.
     */
    DialogProperties props;
    CalcDimension xDimen = CalcDimension(0.0, DimensionUnit::VP);
    CalcDimension yDimen = CalcDimension(0.0, DimensionUnit::VP);
    CalcDimension widthDimen = CalcDimension(100, DimensionUnit::PERCENT);
    CalcDimension heightDimen = CalcDimension(100, DimensionUnit::PERCENT);
    DimensionOffset offsetDimen(xDimen, yDimen);
    DimensionRect Rect(widthDimen, heightDimen, offsetDimen);
    props.maskRect = Rect;
    /**
     * @tc.steps: step2. Create Dialog and get DialogPattern.
     * @tc.expected: the Dialog and DialogPattern created successfully.
     */
    auto dialog = DialogView::CreateDialogNode(props, nullptr);
    ASSERT_NE(dialog, nullptr);
    auto dialogPattern = dialog->GetPattern<DialogPattern>();
    EXPECT_TRUE(dialogPattern);
    ASSERT_NE(dialogPattern, nullptr);
    /**
     * @tc.steps: step3. test GetMouseResponseRegion function.
     * @tc.expected: step3. return width equal to 100.0_pct.
     */
    auto hub = dialog->GetEventHub<DialogEventHub>();
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    std::vector<DimensionRect> mouseResponseRegion;
    std::vector<DimensionRect> initMouseResponseRegion;
    initMouseResponseRegion.push_back(Rect);
    gestureHub->SetMouseResponseRegion(initMouseResponseRegion);
    mouseResponseRegion = gestureHub->GetMouseResponseRegion();
    EXPECT_EQ(mouseResponseRegion[0].GetWidth().Value(), Dimension(100.0_pct).Value());
    EXPECT_EQ(mouseResponseRegion[0].GetHeight().Value(), Dimension(100.0_pct).Value());
}

/**
 * @tc.name: DialogPatternTest011
 * @tc.desc: Test dialogLayoutAlgorithm.MultipleDialog function.
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestNg, DialogPatternTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create overlayManager and DialogLayoutAlgorithm instance.
     * @tc.expected: the overlayManager created successfully.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    /**
     * @tc.steps: step2. create DialogProperties.
     * @tc.expected: the DialogProperties created successfully.
     */
    DialogLayoutAlgorithm dialogLayoutAlgorithm;
    DialogProperties props;
    props.type = DialogType::ALERT_DIALOG;
    props.title = TITLE;
    props.content = MESSAGE;
    props.buttons = btnItems;
    props.isModal = false;
    props.isShowInSubWindow = true;
    SizeF childSize(100.0, 100.0);
    SizeF selfSize(300.0, 200.0);
    /**
     * @tc.steps: step3. test DialogLayoutAlgorithm's MultipleDialog function.
     * @tc.expected: dialogLayoutAlgorithm.touchingBoundaryFlag_. equal to TouchingBoundaryType::NotTouchBoundary.
     */
    EXPECT_EQ(dialogLayoutAlgorithm.touchingBoundaryFlag_, TouchingBoundaryType::NotTouchBoundary);
    /**
     * @tc.steps: step4 create dialog node with overlayManager.
     * @tc.expected: the dialog node created successfully.
     */
    for (int i = 0; i < 6; i++) {
        auto dialog = overlayManager->ShowDialog(props, nullptr);
        ASSERT_NE(dialog, nullptr);
        auto dialogProp = AceType::DynamicCast<DialogLayoutProperty>(dialog->GetLayoutProperty());
        dialogLayoutAlgorithm.MultipleDialog(dialogProp, childSize, selfSize, overlayManager);
    }
    /**
     * @tc.steps: step5. test DialogLayoutAlgorithm's MultipleDialog function.
     * @tc.expected: dialogLayoutAlgorithm.touchingBoundaryFlag_. equal to TouchingBoundaryType::TouchBottomBoundary.
     */
    EXPECT_EQ(dialogLayoutAlgorithm.touchingBoundaryFlag_, TouchingBoundaryType::TouchBottomBoundary);
}

/**
 * @tc.name: DialogPatternTest012
 * @tc.desc: Test dialog UpdateContentRenderContext.
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestNg, DialogPatternTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. mock PlatformVersion VERSION_ELEVEN.
     * @tc.expected: mock successfully.
     */
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    /**
     * @tc.steps: step2. create dialogTheme.
     * @tc.expected: the dialogTheme created successfully.
     */
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    /**
     * @tc.steps: step3. create dialogNode.
     * @tc.expected: the dialogNode created successfully.
     */
    RefPtr<FrameNode> dialogNode =
        FrameNode::CreateFrameNode(V2::DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(dialogNode, nullptr);
    /**
     * @tc.steps: step4. create pattern.
     * @tc.expected: the pattern created successfully.
     */
    auto pattern = dialogNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step5. execute UpdateContentRenderContext.
     * @tc.expected: UpdateContentRenderContext successfully.
     */
    DialogProperties props;
    props.backgroundColor = Color::BLUE;
    pattern->UpdateContentRenderContext(dialogNode, props);
    /**
     * @tc.steps: step6. test dialogNode's RenderContext's BackgroundColorValue value.
     * @tc.expected: equal TRANSPARENT.
     */
    EXPECT_EQ(dialogNode->GetRenderContext()->GetBackgroundColorValue(Color::BLACK).GetValue(), Color::BLUE.GetValue());
    /**
     * @tc.steps: step7. mock PlatformVersion TEN.
     * @tc.expected: mock successfully.
     */
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TEN));
    pattern->UpdateContentRenderContext(dialogNode, props);
    /**
     * @tc.steps: step8. test dialogNode's RenderContext's BackgroundColorValue value.
     * @tc.expected: equal BLUE.
     */
    EXPECT_EQ(dialogNode->GetRenderContext()->GetBackgroundColorValue(Color::BLACK).GetValue(), Color::BLUE.GetValue());
}

/**
 * @tc.name: PopDialog02
 * @tc.desc: Dialog already in close
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestNg, PopDialog02, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create DialogLayoutAlgorithm and overlayManager instance.
     * @tc.expected: the DialogLayoutAlgorithm and overlayManager created successfully.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    DialogLayoutAlgorithm dialogLayoutAlgorithm;
    /**
     * @tc.steps: step2. create DialogProperties.
     * @tc.expected: the DialogLayoutAlgorithm and overlayManager created successfully.
     */
    DialogProperties props;
    props.type = DialogType::ALERT_DIALOG;
    props.title = TITLE;
    props.content = MESSAGE;
    props.buttons = btnItems;
    props.isModal = false;
    props.isShowInSubWindow = true;
    DialogProperties props2;
    props2.type = DialogType::ALERT_DIALOG;
    props2.title = TITLE;
    props2.content = MESSAGE;
    props2.buttons = btnItems;
    props2.isModal = false;
    props2.isShowInSubWindow = true;
    props2.isMask = true;
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    /**
     * @tc.steps: step3. create dialog node with overlayManager.
     * @tc.expected: the dialog node created successfully.
     */
    auto dialog = overlayManager->ShowDialog(props, nullptr);
    ASSERT_NE(dialog, nullptr);
    auto mask = overlayManager->ShowDialog(props2, nullptr);
    ASSERT_NE(mask, nullptr);
    EXPECT_EQ(overlayManager->dialogMap_.size(), 2);
    /**
     * @tc.steps: step4. create dialogPattern and do PopDialog.
     * @tc.expected: the dialogPattern  created successfully.
     */
    auto pattern = dialog->GetPattern<DialogPattern>();
    overlayManager->CloseDialog(mask);
    ASSERT_NE(pattern, nullptr);
    pattern->title_ = TITLE;
    pattern->message_ = MESSAGE;
    pattern->dialogProperties_.isShowInSubWindow = true;
    pattern->dialogProperties_.isModal = true;
    MockPipelineContext::GetCurrent()->overlayManager_ = overlayManager;
    /**
     * @tc.steps: step5. test DialogPattern's PopDialog function.
     * @tc.expected: dialogMap_.size. equal to 0 after pattern->PopDialog.
     */
    pattern->PopDialog(0);
    EXPECT_EQ(overlayManager->dialogMap_.size(), 0);
}

/**
 * @tc.name: DialogPatternTest013
 * @tc.desc: Test dialog UpdateContentRenderContext.
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestNg, DialogPatternTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create dialogTheme.
     * @tc.expected: the dialogTheme created successfully.
     */
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    /**
     * @tc.steps: step2. create dialogNode.
     * @tc.expected: the dialogNode created successfully.
     */
    RefPtr<FrameNode> dialogNode = FrameNode::CreateFrameNode(V2::ALERT_DIALOG_ETS_TAG, 1,
        AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(dialogNode, nullptr);
    /**
     * @tc.steps: step3. create pattern.
     * @tc.expected: the pattern created successfully.
     */
    auto pattern = dialogNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step4. execute UpdateContentRenderContext.
     * @tc.expected: UpdateContentRenderContext successfully.
     */
    DialogProperties props;
    NG::BorderColorProperty borderColor;
    borderColor.SetColor(Color::BLUE);
    props.borderColor = borderColor;
    NG::BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(DIMENSION_RADIUS);
    props.borderRadius = borderRadius;
    auto borderStyle = NG::BorderStyleProperty({BorderStyle::SOLID,
        BorderStyle::SOLID, BorderStyle::SOLID, BorderStyle::SOLID});
    props.borderStyle = borderStyle;
    pattern->UpdateContentRenderContext(dialogNode, props);
    /**
     * @tc.steps: step5. test dialogNode's RenderContext's border values.
     * @tc.expected: equal borderRadius or borderColor or borderStyle.
     */
    auto dialogRender = dialogNode->GetRenderContext();
    ASSERT_NE(dialogRender, nullptr);
    EXPECT_EQ(dialogRender->GetBorderRadius().value(), borderRadius);
    EXPECT_EQ(dialogRender->GetBorderColor().value(), borderColor);
    EXPECT_EQ(dialogRender->GetBorderStyle().value(), borderStyle);
}

/**
 * @tc.name: DialogLayoutAlgorithm003
 * @tc.desc: Test DialogLayoutAlgorithm::Distribute function
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestNg, DialogLayoutAlgorithm003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create DialogLayoutAlgorithm instance.
     */
    DialogLayoutAlgorithm algorithm;

    /**
     * @tc.steps: step2. execute Distribute
     * @tc.expected: prop is set as expected
     */
    float scrollHeight = 10.0f, listHeight = 10.0f, restHeight = 4.0f;
    algorithm.Distribute(scrollHeight, listHeight, restHeight);
    EXPECT_EQ(scrollHeight, 2.0f);
    scrollHeight = 10.0f, listHeight = 0.0f;
    algorithm.Distribute(scrollHeight, listHeight, restHeight);
    EXPECT_EQ(scrollHeight, 4.0f);
    scrollHeight = 0.0f, listHeight = 10.0f;
    algorithm.Distribute(scrollHeight, listHeight, restHeight);
    EXPECT_EQ(listHeight, 4.0f);
    scrollHeight = 0.0f, listHeight = 0.0f;
    algorithm.Distribute(scrollHeight, listHeight, restHeight);
    EXPECT_EQ(listHeight, 0.0f);
}
/**
 * @tc.name: DialogPatternTest014
 * @tc.desc: fullfill DialogPattern function branch
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestNg, DialogPatternTest014, TestSize.Level1)
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
    auto dialogPattern = Dialog->GetPattern<DialogPattern>();
    EXPECT_TRUE(dialogPattern);
    ASSERT_NE(dialogPattern, nullptr);
    info.SetGlobalLocation(globalLocation);
    info.SetSourceDevice(SourceType::KEYBOARD);
    dialogPattern->HandleClick(info);
    EXPECT_EQ(info.GetSourceDevice(), SourceType::KEYBOARD);
}
/**
 * @tc.name: DialogPatternTest015
 * @tc.desc: fullfill DialogPattern function branch
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestNg, DialogPatternTest015, TestSize.Level1)
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
    auto dialogPattern = Dialog->GetPattern<DialogPattern>();
    EXPECT_TRUE(dialogPattern);
    ASSERT_NE(dialogPattern, nullptr);
    info.SetGlobalLocation(globalLocation);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(Dialog);
    CHECK_NULL_VOID(overlayManager);

    auto host = dialogPattern->GetHost();
    host->isRemoving_ = true;
    dialogPattern->HandleClick(info);
}
/**
 * @tc.name: DialogPatternTest016
 * @tc.desc: fullfill DialogPattern function branch
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestNg, DialogPatternTest016, TestSize.Level1)
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
    auto dialogPattern = Dialog->GetPattern<DialogPattern>();
    EXPECT_TRUE(dialogPattern);
    ASSERT_NE(dialogPattern, nullptr);
    info.SetGlobalLocation(globalLocation);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(Dialog);
    CHECK_NULL_VOID(overlayManager);
    auto index = static_cast<int32_t>(Recorder::EventCategory::CATEGORY_COMPONENT);
    Recorder::EventRecorder::Get().eventSwitch_[index] = true;
    Recorder::EventRecorder::Get().globalSwitch_[index] = true;
    dialogPattern->RecordEvent(BUTTONINDEX_TEST_1);
    EXPECT_EQ(dialogPattern->dialogProperties_.buttons.at(BUTTONINDEX_TEST_1).text, "second button");
}
/**
 * @tc.name: DialogPatternTest017
 * @tc.desc: fullfill DialogPattern function branch
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestNg, DialogPatternTest017, TestSize.Level1)
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
 * @tc.name: CustomDialogControllerModelNGTest001
 * @tc.desc: Test CustomDialogControllerModelNG SetOpenDialog
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestNg, CustomDialogControllerModelNGTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CustomDialogControllerModelNG.
     */
    CustomDialogControllerModelNG controllerModel;
    DialogProperties props{
            .type = DialogType::ACTION_SHEET,
            .title = "dialog test",
            .content = "dialog content test",
        };
    bool pending = true, isShown = true;
    auto controller = AceType::MakeRefPtr<AceType>();
    std::vector<WeakPtr<AceType>> dialogs;
    auto dialogComponent = AceType::MakeRefPtr<AceType>();
    auto customDialog = AceType::MakeRefPtr<AceType>();
    std::list<DialogOperation> dialogOperation;

    /**
     * @tc.steps: step2. execute SetOpenDialog and SetCloseDialog
     * @tc.expected: prop is set as expected
     */
    controllerModel.SetOpenDialog(props, controller, dialogs, pending, isShown,
        []() {}, []() {}, dialogComponent, customDialog, dialogOperation);
    props.onStatusChanged(true);
    props.onStatusChanged(false);
    controllerModel.SetCloseDialog(props, controller, dialogs, pending, isShown,
        []() {}, dialogComponent, customDialog, dialogOperation);

    props.isShowInSubWindow = true;
    props.isModal = false;
    controllerModel.SetOpenDialog(props, controller, dialogs, pending, isShown,
        []() {}, []() {}, dialogComponent, customDialog, dialogOperation);
    controllerModel.SetCloseDialog(props, controller, dialogs, pending, isShown,
        []() {}, dialogComponent, customDialog, dialogOperation);
    EXPECT_TRUE(props.isShowInSubWindow);
    EXPECT_FALSE(props.isModal);
}

/**
 * @tc.name: CustomDialogControllerModelNGTest002
 * @tc.desc: Test CustomDialogControllerModelNG SetOpenDialogWithNode
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestNg, CustomDialogControllerModelNGTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CustomDialogControllerModelNG.
     */
    CustomDialogControllerModelNG controllerModel;
    DialogProperties props{
            .type = DialogType::ACTION_SHEET,
            .title = "dialog test",
            .content = "dialog content test",
        };

    /**
     * @tc.steps: step2. execute SetOpenDialogWithNode
     * @tc.expected: prop is set as expected
     */
    controllerModel.SetOpenDialogWithNode(props, nullptr);
    props.isShowInSubWindow = true;
    controllerModel.SetOpenDialogWithNode(props, nullptr);
    props.isModal = true;
    props.isSceneBoardDialog = false;
    controllerModel.SetOpenDialogWithNode(props, nullptr);
    EXPECT_TRUE(props.isShowInSubWindow);
}

/**
 * @tc.name: DialogPatternTest020
 * @tc.desc: Test dialogPattern.UpdatePropertyForElderly function
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestNg, DialogPatternTest020, TestSize.Level1)
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
HWTEST_F(DialogPatternTestNg, DialogPatternTest021, TestSize.Level1)
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
HWTEST_F(DialogPatternTestNg, DialogPatternTest022, TestSize.Level1)
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
HWTEST_F(DialogPatternTestNg, DialogPatternTest028, TestSize.Level1)
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
HWTEST_F(DialogPatternTestNg, DialogPatternTest029, TestSize.Level1)
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
HWTEST_F(DialogPatternTestNg, DialogPatternTest030, TestSize.Level1)
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
        auto buttonNode = AceType::DynamicCast<FrameNode>(child);
        CheckTextMarquee(buttonNode);
    }
}

/**
 * @tc.name: DialogPatternTest031
 * @tc.desc: Test dialogPattern.BuildTitle
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestNg, DialogPatternTest031, TestSize.Level1)
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
} // namespace OHOS::Ace::NG
