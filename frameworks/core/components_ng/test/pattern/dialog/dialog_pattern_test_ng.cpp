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
#include "core/components/dialog/dialog_properties.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/dialog/dialog_event_hub.h"
#include "core/components_ng/pattern/dialog/dialog_layout_algorithm.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_view.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"
#include "core/components/button/button_theme.h"

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
            .sheetsInfo = sheetItems,
        },
        DialogProperties {
            .content = "dialog content test",
        },
    };
};

void DialogPatternTestNg::SetUpTestCase()
{
    MockPipelineBase::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
}
void DialogPatternTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
}
void DialogPatternTestNg::SetDialogTheme()
{
    auto themeManager = AceType::DynamicCast<MockThemeManager>(MockPipelineBase::GetCurrent()->GetThemeManager());
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
    for (size_t i = 0; i < sizeof(aligns) / sizeof(aligns[0]); i++)
    {
        dialogLayoutAlgorithm->alignment_ = aligns[i];
        auto result = dialogLayoutAlgorithm->SetAlignmentSwitch(maxSize, childSize, topLeftPoint);
        if (dialogLayoutAlgorithm->alignment_ == DialogAlignment::DEFAULT) {
            EXPECT_EQ(result, false);
        } else {
            EXPECT_EQ(result, true);
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
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> dialog = FrameNode::CreateFrameNode(
        V2::ACTION_SHEET_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(dialog, nullptr);

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
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> dialog = FrameNode::CreateFrameNode(
        V2::ACTION_SHEET_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(dialog, nullptr);

    auto pattern = dialog->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->title_ = TITLE;
    pattern->message_ = MESSAGE;
    std::unique_ptr<JsonValue> json = JsonUtil::Create(true);
    pattern->ToJsonValue(json);
    EXPECT_EQ(json->GetKey(),"");
}

/**
 * @tc.name: PopDialog
 * @tc.desc: Dialog already in close
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestNg, PopDialog, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> dialog = FrameNode::CreateFrameNode(
        V2::ACTION_SHEET_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(dialog, nullptr);

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
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> dialog = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(dialog, nullptr);

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
    const ScreenSizeType types[] = {
        ScreenSizeType::SM,
        ScreenSizeType::MD,
        ScreenSizeType::LG,
        ScreenSizeType::UNDEFINED
    };
    const DeviceType deviceTypes[] = {
        DeviceType::WATCH,
        DeviceType::PHONE,
        DeviceType::CAR,
        DeviceType::UNKNOWN
    };
    auto columnInfo = GridSystemManager::GetInstance().GetInfoByType(GridColumnType::CAR_DIALOG);
    auto dialogLayoutAlgorithm = AceType::MakeRefPtr<DialogLayoutAlgorithm>();
    /**
     * @tc.steps: step2. call GetMaxWidthBasedOnGridType function.
     * @tc.expected: the result equal to WIDTH_A.
     */
    for (size_t i = 0; i < sizeof(deviceTypes) / sizeof(deviceTypes[0]); i++)
    {
        for (size_t j = 0; j < sizeof(types) / sizeof(types[0]); j++)
        {
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
    const DialogType types[] = {
        DialogType::ALERT_DIALOG,
        DialogType::ACTION_SHEET,
        DialogType::COMMON
    };
    SetDialogTheme();
    /**
     * @tc.steps: step2. call CreateDialogNode function with different props.
     * @tc.expected: the dialog node created successfully.
     */
    for (size_t i = 0; i < sizeof(types) / sizeof(types[0]); i++)
    {
        DialogProperties props;
        props.type = types[i];
        if (i == 1)
        {
            props.title = "dialog test";
            props.content = "dialog content test";
            props.customStyle = true;
            props.sheetsInfo = sheetItems;
            props.isMenu = true;
            props.buttons = btnItems;
        }else if (i == 0)
        {
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
    auto childLayoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(
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
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(
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
    auto layoutWrapper2 = AceType::MakeRefPtr<LayoutWrapper>(
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
    for (auto& props : propsVectors)
    {
        /**
         * @tc.steps: step2. create dialog node and layoutWrapper.
         * @tc.expected: the dialog node created successfully.
         */
        auto dialog = DialogView::CreateDialogNode(props, nullptr);
        ASSERT_NE(dialog, nullptr);
        auto contentNode = AceType::DynamicCast<FrameNode>(dialog->GetFirstChild());
        ASSERT_NE(contentNode, nullptr);
        auto childLayoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(
            contentNode, contentNode->GetGeometryNode(), contentNode->GetLayoutProperty());
        for (auto& node : contentNode->GetChildren()) {
            auto frameNode = AceType::DynamicCast<FrameNode>(node);
            auto grandsonLayoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(
                frameNode, frameNode->GetGeometryNode(), frameNode->GetLayoutProperty());
            childLayoutWrapper->AppendChild(grandsonLayoutWrapper);
        }

        auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(
            dialog, dialog->GetGeometryNode(), dialog->GetLayoutProperty());
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
} // namespace OHOS::Ace::NG
