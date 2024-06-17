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

#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/common/recorder/event_recorder.h"
#include "core/components/dialog/dialog_properties.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/action_sheet/action_sheet_model_ng.h"
#include "core/components_ng/pattern/dialog/alert_dialog_model_ng.h"
#include "core/components_ng/pattern/dialog/custom_dialog_controller_model_ng.h"
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
const InspectorFilter filter;
const string PROPERTY_STR = "confirm";
constexpr float FULL_SCREEN_WIDTH = 720.0f;
constexpr float FULL_SCREEN_HEIGHT = 1136.0f;
constexpr float FIRST_ITEM_WIDTH = 100.0f;
constexpr float FIRST_ITEM_HEIGHT = 50.0f;
const SizeF CONTAINER_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
const SizeF FIRST_ITEM_SIZE(FIRST_ITEM_WIDTH, FIRST_ITEM_HEIGHT);
const std::string TITLE = "title";
const std::string SUBTITLE = "subtitle";
const std::string MESSAGE = "hello world";
const std::string ICON_SOURCE = "$r('app.media.icon')";
const Dimension BORDER_WIDTH(5.0, DimensionUnit::PX);
} // namespace

class DialogModelTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void DialogModelTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    RefPtr<FrameNode> stageNode = AceType::MakeRefPtr<FrameNode>("STAGE", -1, AceType::MakeRefPtr<Pattern>());
    auto stageManager = AceType::MakeRefPtr<StageManager>(stageNode);
    MockPipelineContext::GetCurrent()->stageManager_ = stageManager;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();

    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        if (type == DialogTheme::TypeId()) {
            return AceType::MakeRefPtr<DialogTheme>();
        } else {
            return nullptr;
        }
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void DialogModelTestNg::TearDownTestCase()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: DialogModelTestNg001
 * @tc.desc: Test DialogEventHub's GetOrCreateGestureEventHub
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTestNg, DialogModelTestNg001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create dialogNode and dialogTheme instance.
     * @tc.expected: The dialogNode and dialogNode created successfully.
     */
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create EventHub.
     * @tc.expected: EventHub created successfully.
     */
    auto eventHub = pattern->GetEventHub<DialogEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->MarkModifyDone();
    /**
     * @tc.steps: step3. Get EventHub's properties.
     * @tc.expected: These properties are null when GetOrCreateEventHub functions have not been invoked.
     */
    EXPECT_EQ(eventHub->GetGestureEventHub(), nullptr);
    EXPECT_EQ(eventHub->GetInputEventHub(), nullptr);
    EXPECT_EQ(eventHub->GetOnDragStart(), nullptr);

    /**
     * @tc.steps: step4. Invoke GetOrCreateEventHub functions.
     * @tc.expected: These eventHub properties are not null.
     */
    eventHub->GetOrCreateGestureEventHub();
    eventHub->GetOrCreateInputEventHub();
    eventHub->GetOrCreateFocusHub();
    EXPECT_NE(eventHub->GetGestureEventHub(), nullptr);
    EXPECT_NE(eventHub->GetInputEventHub(), nullptr);
    EXPECT_NE(eventHub->GetFocusHub(), nullptr);
}

/**
 * @tc.name: DialogModelTestNg002
 * @tc.desc: Test AlertDialogModelNG's SetOnWillDismiss.
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTestNg, DialogModelTestNg002, TestSize.Level1)
{
    /**
     * @tc.steps: step1.Mock data.
     */
    AlertDialogModelNG alertDialogModelNg;
    DialogProperties properties;
    std::function<void(int32_t)> onWillDismiss = [](int32_t reason) {};

    /**
     * @tc.steps: step2. Call SetOnWillDismiss.
     * @tc.expected: Check propery onWillDismiss.
     */
    alertDialogModelNg.SetOnWillDismiss(std::move(onWillDismiss), properties);
    ASSERT_NE(properties.onWillDismiss, nullptr);
}

/**
 * @tc.name: DialogModelTestNg003
 * @tc.desc: Test ActionSheetModelNG's SetOnWillDismiss.
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTestNg, DialogModelTestNg003, TestSize.Level1)
{
    /**
     * @tc.steps: step1.Mock data.
     */
    ActionSheetModelNG actionSheetModelNg;
    DialogProperties properties;
    std::function<void(int32_t)> onWillDismiss = [](int32_t reason) {};

    /**
     * @tc.steps: step2. Call SetOnWillDismiss.
     * @tc.expected: Check propery onWillDismiss.
     */
    actionSheetModelNg.SetOnWillDismiss(std::move(onWillDismiss), properties);
    ASSERT_NE(properties.onWillDismiss, nullptr);
}

/**
 * @tc.name: DialogModelTestNg004
 * @tc.desc: Test AlertDialogModelNG's SetOnCancel.
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTestNg, DialogModelTestNg004, TestSize.Level1)
{
    /**
     * @tc.steps: step1.Mock data.
     */
    AlertDialogModelNG alertDialogModelNg;
    DialogProperties props;

    /**
     * @tc.steps: step2. Call SetOnCancel.
     * @tc.expected: Check onCancel.
     */
    bool cancelFlag = false;
    auto cancelEvent = [&cancelFlag]() { cancelFlag = !cancelFlag; };
    alertDialogModelNg.SetOnCancel(std::move(cancelEvent), props);
    ASSERT_NE(props.onCancel, nullptr);
}

/**
 * @tc.name: DialogModelTestNg005
 * @tc.desc: Test ActionSheetModelNG's SetOnCancel.
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTestNg, DialogModelTestNg005, TestSize.Level1)
{
    /**
     * @tc.steps: step1.Mock data.
     */
    ActionSheetModelNG actionSheetModelNg;
    DialogProperties props;

    /**
     * @tc.steps: step3. Call SetOnCancel.
     * @tc.expected: Check onCancel.
     */
    bool cancelFlag = false;
    auto cancelEvent = [&cancelFlag]() { cancelFlag = !cancelFlag; };
    actionSheetModelNg.SetCancel(std::move(cancelEvent), props);
    ASSERT_NE(props.onCancel, nullptr);
}

/**
 * @tc.name: DialogModelTestNg006
 * @tc.desc: Test AlertDialogModelNG's SetShowDialog.
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTestNg, DialogModelTestNg006, TestSize.Level1)
{
    /**
     * @tc.cases: step1. Mock data.
     */
    AlertDialogModelNG alertDialogModelNg;
    DialogProperties props;
    props.isModal = true;
    /**
     * @tc.steps: step2. Call SetShowDialog when isShowInSubWindow is true.
     */
    props.isShowInSubWindow = true;
    alertDialogModelNg.SetShowDialog(props);
    /**
     * @tc.steps: step2. Call SetShowDialog when isShowInSubWindow is false.
     */
    props.isShowInSubWindow = false;
    alertDialogModelNg.SetShowDialog(props);
}

/**
 * @tc.name: DialogModelTestNg007
 * @tc.desc: Test ActionSheetModelNG's SetAction.
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTestNg, DialogModelTestNg007, TestSize.Level1)
{
    /**
     * @tc.steps: step1.Mock data.
     */
    ActionSheetModelNG actionSheetModelNg;
    DialogProperties props {
        .type = DialogType::ACTION_SHEET,
        .title = "test",
        .content = "content test",
        .isModal = true,
        .isShowInSubWindow = true,
    };
    ActionSheetInfo info;
    GestureEventFunc eventFunc;

    /**
     * @tc.steps: step2. Call SetAction.
     * @tc.expected: Check action.
     */
    actionSheetModelNg.SetAction(std::move(eventFunc), info);
    ASSERT_NE(info.action, nullptr);
}

/**
 * @tc.name: DialogModelTestNg008
 * @tc.desc: Test ActionSheetModelNG's ShowActionSheet.
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTestNg, DialogModelTestNg008, TestSize.Level1)
{
    /**
     * @tc.steps: step1.Mock data.
     */
    ActionSheetModelNG actionSheetModelNg;
    DialogProperties props {
        .type = DialogType::ACTION_SHEET,
        .title = TITLE,
        .content = MESSAGE,
        .isShowInSubWindow = true,
        .width = 300,
        .height = 350,
    };

    /**
     * @tc.steps: step3. Call ShowActionSheet when isShowInSubWindow is true.
     */
    actionSheetModelNg.ShowActionSheet(props);

    /**
     * @tc.steps: step3. Call ShowActionSheet when isShowInSubWindow is false.
     */
    props.isShowInSubWindow = false;
    actionSheetModelNg.ShowActionSheet(props);
}

/**
 * @tc.name: DialogModelTestNg009
 * @tc.desc: Test ActionSheetModelNG's SetConfirm.
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTestNg, DialogModelTestNg009, TestSize.Level1)
{
    /**
     * @tc.steps: step1.Mock data.
     */
    ActionSheetModelNG actionSheetModelNg;
    DialogProperties props {
        .type = DialogType::ACTION_SHEET,
        .title = TITLE,
        .content = MESSAGE,
        .isShowInSubWindow = false,
        .width = 200,
        .height = 300,
    };
    GestureEventFunc tapEventFunc;
    bool cancelFlag = false;
    auto cancelEvent = [&cancelFlag]() { cancelFlag = !cancelFlag; };
    ButtonInfo info;
    /**
     * @tc.steps: step2. Call SetConfirm.
     * @tc.expected: Check ButtonInfo's action.
     */
    actionSheetModelNg.SetConfirm(std::move(tapEventFunc), cancelEvent, info, props);
    ASSERT_NE(info.action, nullptr);
}

/**
 * @tc.name: DialogModelTestNg010
 * @tc.desc: Test DialogAccessibilityProperty's GetText
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTestNg, DialogModelTestNg010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the dialog node.
     * @tc.expected: The node created successfully.
     */
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    auto dialog =
        FrameNode::CreateFrameNode(V2::DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(dialog, nullptr);

    /**
     * @tc.steps: step2. Create pattern.
     * @tc.expected: The pattern created successfully.
     */
    auto dialogPattern = dialog->GetPattern<DialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);
    dialogPattern->title_ = TITLE;
    dialogPattern->message_ = MESSAGE;

    /**
     * @tc.steps: step3. Call DialogAccessibilityProperty's GetText.
     * @tc.expected: The result is set as expected.
     */
    auto accessibilityProperty = dialog->GetAccessibilityProperty<DialogAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(), TITLE + MESSAGE);
}

/**
 * @tc.name: DialogModelTestNg011
 * @tc.desc: Test DialogView's CreateDialogNode
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTestNg, DialogModelTestNg011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Define VERSION_TWELVE version and save.
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));

    /**
     * @tc.steps: step2. create a custom node
     */
    auto contentNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 100, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(contentNode, nullptr);

    /**
     * @tc.steps: step3. create dialog and layoutWrapper.
     * @tc.expected: the dialog node created successfully.
     */
    DialogProperties props {
        .type = DialogType::ACTION_SHEET,
        .title = TITLE,
        .content = MESSAGE,
        .width = 200,
        .height = 300,
    };
    NG::BorderWidthProperty borderWidth;
    borderWidth.SetBorderWidth(BORDER_WIDTH);
    props.borderWidth = borderWidth;
    auto dialogNode = DialogView::CreateDialogNode(props, contentNode);
    ASSERT_NE(dialogNode, nullptr);

    /**
     * @tc.steps: step4. Get childNode.
     * @tc.expected: successfully.
     */
    auto childNode = AceType::DynamicCast<FrameNode>(dialogNode->GetFirstChild());
    ASSERT_NE(childNode, nullptr);

    /**
     * @tc.steps: step5. Test childNode's RenderContext's BackBlurStyle value.
     * @tc.expected: The blurStyle is COMPONENT_ULTRA_THICK.
     */
    EXPECT_EQ(childNode->GetRenderContext()->GetBackBlurStyle()->blurStyle, BlurStyle::COMPONENT_ULTRA_THICK);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: DialogModelTestNg012
 * @tc.desc: Test CreateDialogNode with no transition effect.
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTestNg, DialogModelTestNg012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and dialogProperties.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    AnimationOption animationOption;
    animationOption.SetDelay(10);
    DialogProperties dialogProps {
        .type = DialogType::ALERT_DIALOG,
        .title = TITLE,
        .content = MESSAGE,
        .openAnimation = animationOption,
    };

    /**
     * @tc.steps: step2. create DialogNode.
     * @tc.expected: DialogNode created successfully
     */
    auto dialog = DialogView::CreateDialogNode(dialogProps, nullptr);
    ASSERT_NE(dialog, nullptr);

    /**
     * @tc.steps: step3. Get transitionEffect from dialog.
     * @tc.expected: The transitionEffect is nullptr.
     */
    auto dialogPattern = dialog->GetPattern<DialogPattern>();
    auto openAnimation = dialogPattern->GetDialogProperties().openAnimation;
    EXPECT_EQ(openAnimation.has_value(), true);
}

/**
 * @tc.name: DialogModelTestNg013
 * @tc.desc: Test CreateDialogNode with transition effect.
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTestNg, DialogModelTestNg013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and dialogProps.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    AnimationOption animationOption;
    animationOption.SetDelay(10);

    double opacity = 1.0;
    auto appearOpacityTransition = AceType::MakeRefPtr<NG::ChainedOpacityEffect>(opacity);
    NG::ScaleOptions scale(1.0f, 1.0f, 1.0f, 0.5_pct, 0.5_pct);
    auto disappearScaleTransition = AceType::MakeRefPtr<NG::ChainedScaleEffect>(scale);
    DialogProperties dialogProps {
        .type = DialogType::ALERT_DIALOG,
        .title = TITLE,
        .content = MESSAGE,
        .openAnimation = animationOption,
        .transitionEffect =
            AceType::MakeRefPtr<NG::ChainedAsymmetricEffect>(appearOpacityTransition, disappearScaleTransition),
    };

    /**
     * @tc.steps: step2. Create DialogNode.
     * @tc.expected: DialogNode created successfully
     */
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto dialog = overlayManager->ShowDialog(dialogProps, nullptr, false);
    ASSERT_NE(dialog, nullptr);

    auto dialogPattern = dialog->GetPattern<DialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);
    dialogPattern->SetDialogProperties(dialogProps);

    /**
     * @tc.steps: step3. Call transitionEffect from dialog.
     * @tc.expected: transitionEffect is nullptr.
     */
    auto transitionEffect = dialogPattern->GetDialogProperties().transitionEffect;
    ASSERT_NE(transitionEffect, nullptr);
}

/**
 * @tc.name: DialogModelTestNg014
 * @tc.desc: Test DialogView's CreateDialogNode
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTestNg, DialogModelTestNg014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Define VERSION_TWELVE version and save.
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));

    /**
     * @tc.steps: step2. Create a content node
     */
    auto contentNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 100, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(contentNode, nullptr);

    /**
     * @tc.steps: step3.Create dialog and layoutWrapper.
     * @tc.expected: The dialog node created successfully.
     */
    DialogProperties props {
        .title = TITLE,
        .content = MESSAGE,
        .width = 300,
        .height = 200,
    };
    NG::BorderWidthProperty borderWidth;
    borderWidth.SetBorderWidth(BORDER_WIDTH);
    props.borderWidth = borderWidth;
    auto dialogNode = DialogView::CreateDialogNode(props, contentNode);
    ASSERT_NE(dialogNode, nullptr);

    /**
     * @tc.steps: step4.Call GetLayoutProperty.
     * @tc.expected: Check the width and height value.
     */
    auto dialogLayoutProp = AceType::DynamicCast<DialogLayoutProperty>(dialogNode->GetLayoutProperty());
    ASSERT_NE(dialogLayoutProp, nullptr);
    EXPECT_EQ(dialogLayoutProp->GetWidth(), props.width);
    EXPECT_EQ(dialogLayoutProp->GetHeight(), props.height);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: DialogModelTestNg015
 * @tc.desc: Test DialogView's CreateDialogNode
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTestNg, DialogModelTestNg015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Define VERSION_TWELVE version and save.
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));

    /**
     * @tc.steps: step2. Create a custom node
     */
    auto contentNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 100, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(contentNode, nullptr);

    /**
     * @tc.steps: step3. Create dialog and layoutWrapper.
     * @tc.expected: The dialog node created successfully.
     */
    DialogProperties props {
        .title = TITLE,
        .content = MESSAGE,
        .height = 200,
        .gridCount = 3,
    };
    NG::BorderWidthProperty borderWidth;
    borderWidth.SetBorderWidth(BORDER_WIDTH);
    props.borderWidth = borderWidth;
    auto dialogNode = DialogView::CreateDialogNode(props, contentNode);
    ASSERT_NE(dialogNode, nullptr);

    /**
     * @tc.steps: step4.Call GetLayoutProperty.
     * @tc.expected: Check the gridCount and height value.
     */
    auto dialogLayoutProp = AceType::DynamicCast<DialogLayoutProperty>(dialogNode->GetLayoutProperty());
    ASSERT_NE(dialogLayoutProp, nullptr);
    EXPECT_EQ(dialogLayoutProp->GetGridCount(), props.gridCount);
    EXPECT_EQ(dialogLayoutProp->GetHeight(), props.height);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: DialogModelTestNg016
 * @tc.desc: Test DialogPattern's SetOnWillDismiss and ShouldDismiss.
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTestNg, DialogModelTestNg016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode.
     */
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    auto frameNode =
        FrameNode::CreateFrameNode(V2::DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnAttachToFrameNode();

    /**
     * @tc.steps: step2. Call onWillDismiss and ShouldDismiss.
     * @tc.expected: return value is true.
     */
    std::function<void(int32_t)> onWillDismiss = [](int32_t info) {};
    pattern->SetOnWillDismiss(std::move(onWillDismiss));
    EXPECT_TRUE(pattern->ShouldDismiss());

    /**
     * @tc.steps: step3. Call HandleClickEvent.
     * @tc.expected: Return value is false.
     */
    GestureEvent info;
    info.SetLocalLocation(Offset(1.0f, 1.0f));
    info.deviceType_ = SourceType::MOUSE;
    pattern->HandleClick(info);
}

/**
 * @tc.name: DialogModelTestNg017
 * @tc.desc: Test DialogPattern's OnDetachFromFrameNode.
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTestNg, DialogModelTestNg017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode.
     */
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    auto frameNode =
        FrameNode::CreateFrameNode(V2::DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto stageManager = AceType::MakeRefPtr<StageManager>(frameNode);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->stageManager_ = stageManager;

    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step3. Call OnDetachFromFrameNode.
     * @tc.expected: Check the stageNode_.
     */
    pattern->OnDetachFromFrameNode(AceType::RawPtr(frameNode));
    EXPECT_NE(stageManager->stageNode_, nullptr);
}

/**
 * @tc.name: DialogModelTestNg018
 * @tc.desc: Test dialog UpdateContentRenderContext.
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTestNg, DialogModelTestNg018, TestSize.Level1)
{
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    /**
     * @tc.steps: step1. Create dialogNode with theme.
     * @tc.expected: The dialogNode created successfully.
     */
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> dialogNode =
        FrameNode::CreateFrameNode(V2::DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(dialogNode, nullptr);

    /**
     * @tc.steps: step2. Create pattern.
     * @tc.expected: the pattern created successfully.
     */
    auto pattern = dialogNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step3. Mock props and call UpdateContentRenderContext.
     */
    DialogProperties props;
    props.type = DialogType::ALERT_DIALOG;
    props.title = TITLE;
    props.content = MESSAGE;
    props.isModal = false;
    props.isShowInSubWindow = true;
    props.backgroundColor = Color::BLUE;
    Shadow shadow;
    shadow.SetBlurRadius(-0.1f);
    shadow.SetOffsetX(10);
    shadow.SetOffsetY(10);
    shadow.SetColor(Color(Color::RED));
    shadow.SetShadowType(ShadowType::COLOR);
    props.shadow = shadow;

    pattern->UpdateContentRenderContext(dialogNode, props);

    /**
     * @tc.steps: step4. Test dialogNode's BackgroundColorValue value.
     * @tc.expected: equal TRANSPARENT.
     */
    auto dialogContext = dialogNode->GetRenderContext();
    EXPECT_NE(dialogContext, nullptr);
    EXPECT_EQ(dialogContext->GetBackgroundColorValue(Color::BLACK).GetValue(), Color::BLUE.GetValue());

    /**
     * @tc.steps: step5. test dialogNode's shadow value.
     * @tc.expected: The result is set as expected.
     */
    auto backShadow = dialogContext->GetBackShadow();
    EXPECT_NE(backShadow, std::nullopt);
    EXPECT_EQ(backShadow.has_value(), true);
    EXPECT_EQ(backShadow.value(), shadow);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: DialogModelTestNg019
 * @tc.desc: Test ToJsonValue and OnLanguageConfigurationUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTestNg, DialogModelTestNg019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create dialogNode with theme.
     * @tc.expected: The dialogNode created successfully.
     */
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> dialogNode = FrameNode::CreateFrameNode(
        V2::ACTION_SHEET_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(dialogNode, nullptr);

    /**
     * @tc.steps: step2. Create pattern.
     * @tc.expected: the pattern created successfully.
     */
    auto pattern = dialogNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step3. Mock props and call UpdateContentRenderContext.
     */
    vector<ActionSheetInfo> sheetItems = {
        ActionSheetInfo {
            .title = TITLE,
            .icon = ICON_SOURCE,
        },
    };
    DialogProperties props {
        .type = DialogType::ACTION_SHEET,
        .title = TITLE,
        .subtitle = SUBTITLE,
        .content = MESSAGE,
        .isModal = false,
        .isShowInSubWindow = true,
        .backgroundColor = Color::BLUE,
        .height = FIRST_ITEM_HEIGHT,
        .isMenu = false,
        .sheetsInfo = sheetItems,
        .buttonDirection = DialogButtonDirection::HORIZONTAL,
    };
    ButtonInfo info;
    props.buttons.push_back(info);

    /**
     * @tc.steps: step4. Test dialogNode's BuildChild.
     * @tc.expected: Check contentNodeMap_ value.
    */
    pattern->BuildChild(props);
    EXPECT_TRUE(pattern->contentNodeMap_.size() > 0);
    pattern->customNode_ = dialogNode;
    EXPECT_NE(pattern->GetCustomNode(), nullptr);
    /**
     * @tc.steps: step5. Test dialogNode's ToJsonValue.
     * @tc.expected: Check value.
    */
    auto json = JsonUtil::Create(true);
    pattern->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("title"), TITLE);
    EXPECT_EQ(json->GetString("subtitle"), SUBTITLE);
    EXPECT_EQ(json->GetString("message"), MESSAGE);

    /**
     * @tc.steps: step5. Test dialogNode's OnLanguageConfigurationUpdate.
     * @tc.expected: The result is set as expected.
    */
    pattern->OnLanguageConfigurationUpdate();
    EXPECT_EQ(pattern->title_, TITLE);
    EXPECT_EQ(pattern->subtitle_, SUBTITLE);
    EXPECT_EQ(pattern->message_, MESSAGE);
}

/**
 * @tc.name: DialogModelTestNg020
 * @tc.desc: Test OnWindowSizeChanged Function
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTestNg, DialogModelTestNg020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create dialogNode with theme.
     * @tc.expected: The dialogNode created successfully.
     */
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> dialogNode = FrameNode::CreateFrameNode(
        V2::ACTION_SHEET_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(dialogNode, nullptr);

    /**
     * @tc.steps: step2. Create pattern.
     * @tc.expected: the pattern created successfully.
     */
    auto pattern = dialogNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);
    DialogProperties props {
        .type = DialogType::ACTION_SHEET,
        .title = TITLE,
        .subtitle = SUBTITLE,
        .content = MESSAGE,
        .isModal = false,
        .isShowInSubWindow = true,
        .height = FIRST_ITEM_HEIGHT,
        .isMenu = false,
        .buttonDirection = DialogButtonDirection::HORIZONTAL,
    };
    pattern->SetDialogProperties(props);

    /**
     * @tc.steps: step3. Call OnWindowSizeChanged.
     */
    pattern->OnWindowSizeChanged(100, 200, WindowSizeChangeReason::ROTATION);
}

/**
 * @tc.name: DialogModelTestNg021
 * @tc.desc: Test DialogLayoutProperty.
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTestNg, DialogModelTestNg021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create dialog and layoutWrapper.
     * @tc.expected: the dialog node created successfully.
     */
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ACTION_SHEET_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);

    auto contentNode = AceType::DynamicCast<FrameNode>(frameNode->GetFirstChild());
    DialogProperties props {
        .title = TITLE,
        .content = MESSAGE,
        .contentNode = contentNode,
        .alignment = DialogAlignment::TOP_START,
    };
    auto dialogNode = DialogView::CreateDialogNode(props, contentNode);
    ASSERT_NE(dialogNode, nullptr);

    /**
     * @tc.steps: step2 call GetLayoutProperty.
     * @tc.expected: dialogLayoutProp is correct.
     */
    auto layoutProp = AceType::DynamicCast<DialogLayoutProperty>(dialogNode->GetLayoutProperty());
    EXPECT_NE(layoutProp, nullptr);
    EXPECT_EQ(layoutProp->propDialogAlignment_, DialogAlignment::TOP_START);
    EXPECT_EQ(layoutProp->propDialogOffset_, DimensionOffset(Dimension(0.0), Dimension(0.0)));
}

/**
 * @tc.name: DialogModelTestNg022s
 * @tc.desc: Test OnModifyDone Function
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTestNg, DialogModelTestNg022, TestSize.Level1)
{
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    /**
     * @tc.steps: step1. Create dialogNode with theme.
     * @tc.expected: The dialogNode created successfully.
     */
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> dialogNode = FrameNode::CreateFrameNode(
        V2::ACTION_SHEET_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(dialogNode, nullptr);
    /**
     * @tc.steps: step2. Create pattern.
     * @tc.expected: the pattern created successfully.
     */
    auto pattern = dialogNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);
    DialogProperties props {
        .type = DialogType::ACTION_SHEET,
        .title = TITLE,
        .subtitle = SUBTITLE,
        .content = MESSAGE,
        .isModal = false,
        .isShowInSubWindow = true,
        .height = FIRST_ITEM_HEIGHT,
        .isMenu = false,
        .buttonDirection = DialogButtonDirection::HORIZONTAL,
    };

    pattern->SetDialogProperties(props);
    auto dialogLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(dialogLayoutAlgorithm, nullptr);
    RefPtr<DialogLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<DialogLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);
    /**
     * @tc.steps: step3call Call OnModifyDone.
     */
    pattern->OnModifyDone();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: DialogModelTestNg023
 * @tc.desc: Test DialogLayoutAlgorithm's Measure
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTestNg, DialogModelTestNg023, TestSize.Level1)
{
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));

    /**
     * @tc.steps: step1. Create dialogNode with theme.
     * @tc.expected: The dialogNode created successfully.
     */
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> dialogNode = FrameNode::CreateFrameNode(
        V2::ACTION_SHEET_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(dialogNode, nullptr);

    /**
     * @tc.steps: step2. Create pattern.
     * @tc.expected: the pattern created successfully.
     */
    auto pattern = dialogNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);
    DialogProperties props {
        .type = DialogType::ACTION_SHEET,
        .title = TITLE,
        .subtitle = SUBTITLE,
        .content = MESSAGE,
        .isModal = false,
        .isShowInSubWindow = true,
        .width = FIRST_ITEM_WIDTH,
        .height = FIRST_ITEM_HEIGHT,
        .isMenu = false,
        .buttonDirection = DialogButtonDirection::HORIZONTAL,
    };

    /**
     * @tc.steps: step3. Create dialog LayoutAlgorithm.
     * @tc.expected: the dialog LayoutAlgorithm created successfully.
     */
    auto dialogLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(dialogLayoutAlgorithm, nullptr);
    RefPtr<DialogLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<DialogLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);

    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        dialogNode, dialogNode->GetGeometryNode(), dialogNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    /**
     * @tc.steps: step4. Call  Measure.
     * @tc.expected: Check the topLeftPoint_ and isShowInSubWindow_.
     */
    layoutAlgorithm->Measure(layoutWrapper.rawPtr_);
    layoutAlgorithm->expandDisplay_ = true;
    layoutAlgorithm->Layout(layoutWrapper.rawPtr_);
    EXPECT_EQ(layoutAlgorithm->topLeftPoint_.GetX(), 0.0);
    EXPECT_EQ(layoutAlgorithm->topLeftPoint_.GetY(), 0.0);
    EXPECT_EQ(layoutAlgorithm->isShowInSubWindow_, false);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}
} // namespace OHOS::Ace::NG