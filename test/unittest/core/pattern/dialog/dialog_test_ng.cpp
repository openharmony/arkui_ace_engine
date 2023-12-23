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
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components/button/button_theme.h"
#include "core/components/dialog/dialog_properties.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/dialog/dialog_event_hub.h"
#include "core/components_ng/pattern/dialog/dialog_layout_algorithm.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_view.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const std::string SHEET_TITLE = "sheet item";
const std::string SHEET_TITLE_2 = "sheet item 2";
const std::string SHEET_TITLE_3 = "sheet item 3";
const std::string INTERNAL_SOURCE = "$r('app.media.icon')";
const std::string FILE_SOURCE = "/common/icon.png";

const std::string TITLE = "This is title";
const std::string MESSAGE = "Message";
const int32_t buttonIdx = 1;
const double_t WIDTH_A = 16.0;
const double_t WIDTH_B = 48.0;
const double_t WIDTH_C = 64.0;
const double_t WIDTH_D = 80.0;
const double_t WIDTH_E = 112.0;
const double_t DIVISOR = 2.0;
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
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}
void DialogPatternTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}
void DialogPatternTestNg::SetDialogTheme()
{
    auto themeManager = AceType::DynamicCast<MockThemeManager>(MockPipelineContext::GetCurrent()->GetThemeManager());
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<MockDialogTheme>()));
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
    dialogEventHub->onCancel_ = nullptr;
    dialogEventHub->FireCancelEvent();
    EXPECT_EQ(dialogEventHub->onCancel_ == nullptr, true);
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
    auto dialogEventHub = AceType::MakeRefPtr<DialogEventHub>();
    dialogEventHub->onSuccess_ = nullptr;
    dialogEventHub->FireSuccessEvent(buttonIdx);
    EXPECT_EQ(dialogEventHub->onSuccess_ == nullptr, true);
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
}

/**
 * @tc.name: DialogAccessibilityProperty001
 * @tc.desc: Test Action Sheet Accessibility Property
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestNg, DialogAccessibilityProperty001, TestSize.Level1)
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
    auto accessibilityProperty = dialog->GetAccessibilityProperty<NG::AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(), TITLE + MESSAGE);
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
    pattern->ToJsonValue(json);
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
}

/**
 * @tc.name: DialogPatternTest001
 * @tc.desc: Test GetMaxWidthBasedOnGridType function
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestNg, DialogPatternTest001, TestSize.Level1)
{
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
 * @tc.name: DialogPatternTest003
 * @tc.desc: Test CreateDialogNode with customNode
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestNg, DialogPatternTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a custom node and childLayoutWrapper
     */
    auto customNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 100, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(customNode, nullptr);
    auto childLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        customNode, customNode->GetGeometryNode(), customNode->GetLayoutProperty());
    ASSERT_NE(childLayoutWrapper, nullptr);
    /**
     * @tc.steps: step2. create dialog with a custom node and layoutWrapper.
     * @tc.expected: the dialog node created successfully.
     */
    DialogProperties propsCustom;
    propsCustom.type = DialogType::ACTION_SHEET;
    propsCustom.title = "dialog test";
    propsCustom.content = "dialog content test";
    propsCustom.sheetsInfo = sheetItems;
    propsCustom.buttons = btnItems;
    auto dialogWithCustom = DialogView::CreateDialogNode(propsCustom, customNode);
    ASSERT_NE(dialogWithCustom, nullptr);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        dialogWithCustom, dialogWithCustom->GetGeometryNode(), dialogWithCustom->GetLayoutProperty());
    layoutWrapper->AppendChild(childLayoutWrapper);
    DialogLayoutAlgorithm dialogLayoutAlgorithm;
    dialogLayoutAlgorithm.Measure(layoutWrapper.rawPtr_);
    /**
     * @tc.steps: step3. change props to create dialog with a custom node.
     * @tc.expected: the dialog node and layoutWrapper2 created successfully.
     */
    propsCustom.customStyle = true;
    propsCustom.title = "";
    propsCustom.content = "";
    dialogWithCustom = DialogView::CreateDialogNode(propsCustom, customNode);
    ASSERT_NE(dialogWithCustom, nullptr);
    auto layoutWrapper2 = AceType::MakeRefPtr<LayoutWrapperNode>(
        dialogWithCustom, dialogWithCustom->GetGeometryNode(), dialogWithCustom->GetLayoutProperty());
    ASSERT_NE(layoutWrapper2, nullptr);
    layoutWrapper2->AppendChild(childLayoutWrapper);
    DialogLayoutAlgorithm dialogLayoutAlgorithm2;
    dialogLayoutAlgorithm2.Measure(layoutWrapper2.rawPtr_);
}

/**
 * @tc.name: DialogPatternTest004
 * @tc.desc: Test DialogLayoutAlgorithm::Measure function
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestNg, DialogPatternTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create DialogLayoutAlgorithm instance.
     */
    DialogLayoutAlgorithm dialogLayoutAlgorithm;
    for (auto& props : propsVectors) {
        /**
         * @tc.steps: step2. create dialog node and layoutWrapper.
         * @tc.expected: the dialog node created successfully.
         */
        auto dialog = DialogView::CreateDialogNode(props, nullptr);
        ASSERT_NE(dialog, nullptr);
        auto contentNode = AceType::DynamicCast<FrameNode>(dialog->GetFirstChild());
        ASSERT_NE(contentNode, nullptr);
        auto childLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
            contentNode, contentNode->GetGeometryNode(), contentNode->GetLayoutProperty());
        for (auto& node : contentNode->GetChildren()) {
            auto frameNode = AceType::DynamicCast<FrameNode>(node);
            auto grandsonLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
                frameNode, frameNode->GetGeometryNode(), frameNode->GetLayoutProperty());
            childLayoutWrapper->AppendChild(grandsonLayoutWrapper);
        }

        auto layoutWrapper =
            AceType::MakeRefPtr<LayoutWrapperNode>(dialog, dialog->GetGeometryNode(), dialog->GetLayoutProperty());
        layoutWrapper->AppendChild(childLayoutWrapper);
        /**
         * @tc.steps: step3. test DialogLayoutAlgorithm's Measure function.
         * @tc.expected: dialogLayoutAlgorithm.alignment_ equal to DialogAlignment::DEFAULT.
         */
        dialogLayoutAlgorithm.Measure(layoutWrapper.rawPtr_);
        dialogLayoutAlgorithm.Layout(layoutWrapper.rawPtr_);
        EXPECT_EQ(dialogLayoutAlgorithm.alignment_, DialogAlignment::DEFAULT);
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
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(AceType::MakeRefPtr<DialogTheme>()));
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
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(AceType::MakeRefPtr<DialogTheme>()));
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
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(AceType::MakeRefPtr<DialogTheme>()));
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
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(AceType::MakeRefPtr<DialogTheme>()));
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
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(AceType::MakeRefPtr<DialogTheme>()));
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
    CalcDimension widthDimen = CalcDimension(-1, DimensionUnit::PERCENT);
    CalcDimension heightDimen = CalcDimension(-1, DimensionUnit::PERCENT);
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
    mouseResponseRegion = gestureHub->GetMouseResponseRegion();
    EXPECT_EQ(mouseResponseRegion[0].GetWidth().Value(), Dimension(100.0_pct).Value());
    EXPECT_EQ(mouseResponseRegion[0].GetHeight().Value(), Dimension(100.0_pct).Value());
}

/**
 * @tc.name: DialogPatternTest010
 * @tc.desc: Test dialogLayoutAlgorithm.ProcessMaskRect function
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestNg, DialogPatternTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create DialogLayoutAlgorithm instance.
     * @tc.expected: the DialogLayoutAlgorithm created successfully.
     */
    DialogLayoutAlgorithm dialogLayoutAlgorithm;
    /**
     * @tc.steps: step2. create DialogProperties.
     * @tc.expected: the DialogProperties created successfully.
     */
    DialogProperties props;
    props.type = DialogType::ALERT_DIALOG;
    props.title = TITLE;
    props.content = MESSAGE;
    props.buttons = btnItems;
    props.isModal = false;
    props.isShowInSubWindow = true;
    /**
     * @tc.steps: step3. create dialog node and layoutWrapper.
     * @tc.expected: the dialog node and layoutWrapper created successfully.
     */
    auto dialog = DialogView::CreateDialogNode(props, nullptr);
    ASSERT_NE(dialog, nullptr);
    auto contentNode = AceType::DynamicCast<FrameNode>(dialog->GetFirstChild());
    ASSERT_NE(contentNode, nullptr);
    auto childLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        contentNode, contentNode->GetGeometryNode(), contentNode->GetLayoutProperty());
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(dialog, dialog->GetGeometryNode(), dialog->GetLayoutProperty());
    layoutWrapper->AppendChild(childLayoutWrapper);
    auto childSize = childLayoutWrapper->GetGeometryNode()->GetMarginFrameSize();
    OffsetF topLeftPoint_(0.0, 0.0);
    auto frameNode = layoutWrapper->GetHostNode();
    dialogLayoutAlgorithm.ProcessMaskRect(
        DimensionRect(Dimension(childSize.Width()), Dimension(childSize.Height()), DimensionOffset(topLeftPoint_)),
        frameNode);
    dialogLayoutAlgorithm.Measure(layoutWrapper.rawPtr_);
    dialogLayoutAlgorithm.Layout(layoutWrapper.rawPtr_);
    auto hub = dialog->GetEventHub<DialogEventHub>();
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    std::vector<DimensionRect> mouseResponseRegion;
    mouseResponseRegion = gestureHub->GetMouseResponseRegion();
    /**
     * @tc.steps: step4. test DialogLayoutAlgorithm's ProcessMaskRect function.
     * @tc.expected: childLayoutWrapper.MarginFrameSize.Width() equal to mouseResponseRegion.Width().
     */
    EXPECT_EQ(mouseResponseRegion[0].GetWidth().Value(), Dimension(childSize.Width()).Value());
    /**
     * @tc.steps: step5. test DialogLayoutAlgorithm's ProcessMaskRect function.
     * @tc.expected: childLayoutWrapper.MarginFrameSize.Height() equal to mouseResponseRegion.Height().
     */
    EXPECT_EQ(mouseResponseRegion[0].GetHeight().Value(), Dimension(childSize.Height()).Value());
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
    EXPECT_EQ(dialogNode->GetRenderContext()->GetBackgroundColorValue(Color::BLACK).GetValue(),
        Color::TRANSPARENT.GetValue());
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
    EXPECT_CALL(*MockPipelineContext::GetCurrent(), GetOverlayManager()).WillRepeatedly(Return(overlayManager));
    /**
     * @tc.steps: step5. test DialogPattern's PopDialog function.
     * @tc.expected: dialogMap_.size. equal to 1 after pattern->PopDialog.
     */
    pattern->PopDialog(0);
    EXPECT_EQ(overlayManager->dialogMap_.size(), 1);
}
} // namespace OHOS::Ace::NG
