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

#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/base/mock_system_properties.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/common/recorder/event_recorder.h"
#include "core/common/resource/resource_parse_utils.h"
#include "core/components/dialog/dialog_properties.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
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
constexpr float CHILD_SIZE = 300.0f;
constexpr float CHILD_SIZE_2 = 600.0f;
constexpr float CHILD_SIZE_OVERFLOW = 1200.0f;
constexpr float OFFSET = 200.0f;
constexpr float OFFSET_TOP_OVERFLOW = -2000.0f;
constexpr float OFFSET_BOTTOM_OVERFLOW = 2000.0f;
const SizeF CONTAINER_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
const SizeF FIRST_ITEM_SIZE(FIRST_ITEM_WIDTH, FIRST_ITEM_HEIGHT);
const std::string TITLE = "title";
const std::string SUBTITLE = "subtitle";
const std::string MESSAGE = "hello world";
const std::string ICON_SOURCE = "$r('app.media.icon')";
const std::string BUTTON_TEXT = "button";
const Rect FOLD_CREASE_RECT = Rect(0.0, 300.0, 720.0, 80.0);
const Color COLORYELLOW = Color(0xffffff00);
} // namespace

class DialogModelTwoTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void DialogModelTwoTestNg::SetUpTestCase()
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

void DialogModelTwoTestNg::TearDownTestCase()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: DialogModelTwoTestNg032
 * @tc.desc: Test DialogLayoutAlgorithm.SetSubWindowHotarea/GetMaskRect function
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTwoTestNg, DialogModelTwoTestNg032, TestSize.Level1)
{
    auto layoutAlgorithm = AceType::MakeRefPtr<DialogLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);
    DialogProperties props;
    props.isShowInSubWindow = true;
    auto dialog = DialogView::CreateDialogNode(props, nullptr);
    ASSERT_NE(dialog, nullptr);
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(dialog, dialog->GetGeometryNode(), dialog->GetLayoutProperty());
    auto dialogProp = AceType::DynamicCast<DialogLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(dialogProp);

    auto childSize = SizeF(CHILD_SIZE, CHILD_SIZE);
    auto selfSize = SizeF(CHILD_SIZE_2, CHILD_SIZE_2);

    layoutAlgorithm->SetSubWindowHotarea(dialogProp, childSize, selfSize, dialog->GetId());
    auto maskRect = layoutAlgorithm->GetMaskRect(dialog);
    EXPECT_FALSE(maskRect.has_value());
 
    auto offset = DimensionOffset(CalcDimension(0, DimensionUnit::VP), CalcDimension(0, DimensionUnit::VP));
    layoutAlgorithm->isUIExtensionSubWindow_ = true;
    layoutAlgorithm->SetSubWindowHotarea(dialogProp, childSize, selfSize, dialog->GetId());
    maskRect = layoutAlgorithm->GetMaskRect(dialog);
    EXPECT_EQ(maskRect.value().GetOffset(), offset);
    EXPECT_EQ(maskRect.value().GetWidth(), CalcDimension(1, DimensionUnit::PERCENT));
    EXPECT_EQ(maskRect.value().GetHeight(), CalcDimension(1, DimensionUnit::PERCENT));
 
    layoutAlgorithm->expandDisplay_ = true;
    layoutAlgorithm->hostWindowRect_ = RectF(OffsetF(), SizeF(CHILD_SIZE, CHILD_SIZE));
    layoutAlgorithm->SetSubWindowHotarea(dialogProp, childSize, selfSize, dialog->GetId());
    maskRect = layoutAlgorithm->GetMaskRect(dialog);
    offset = DimensionOffset(CalcDimension(0, DimensionUnit::PX), CalcDimension(0, DimensionUnit::PX));
    EXPECT_EQ(maskRect.value().GetOffset(), offset);
    EXPECT_EQ(maskRect.value().GetWidth(), Dimension(CHILD_SIZE, DimensionUnit::PX));
    EXPECT_EQ(maskRect.value().GetHeight(), Dimension(CHILD_SIZE, DimensionUnit::PX));
}

/**
 * @tc.name: DialogModelTwoTestNg033
 * @tc.desc: Test DialogLayoutAlgorithm::UpdateChildMaxSizeHeight function
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTwoTestNg, DialogModelTwoTestNg033, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create DialogLayoutAlgorithm instance.
     */
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_THIRTEEN));
    auto dialogLayoutAlgorithm = AceType::MakeRefPtr<DialogLayoutAlgorithm>();
    ASSERT_NE(dialogLayoutAlgorithm, nullptr);

    auto maxSize = CONTAINER_SIZE;
    SafeAreaInsets::Inset insetLeftAndRight = {};
    SafeAreaInsets::Inset insetTopAndBottom = { .end = 100.f };
    SafeAreaInsets SYSTEM_SAFE_AREA_INSET = { insetLeftAndRight, insetTopAndBottom, insetLeftAndRight,
        insetTopAndBottom };
    dialogLayoutAlgorithm->foldCreaseRect = FOLD_CREASE_RECT;
    dialogLayoutAlgorithm->safeAreaInsets_ = SYSTEM_SAFE_AREA_INSET;
    dialogLayoutAlgorithm->isHoverMode_ = false;
    dialogLayoutAlgorithm->UpdateChildMaxSizeHeight(maxSize);
    EXPECT_EQ(maxSize.Height(), 936);
    dialogLayoutAlgorithm->isHoverMode_ = true;
    dialogLayoutAlgorithm->hoverModeArea_ = HoverModeAreaType::TOP_SCREEN;
    maxSize = CONTAINER_SIZE;
    dialogLayoutAlgorithm->UpdateChildMaxSizeHeight(maxSize);
    EXPECT_EQ(maxSize.Height(), 200);
    dialogLayoutAlgorithm->isKeyBoardShow_ = false;
    dialogLayoutAlgorithm->hoverModeArea_ = HoverModeAreaType::BOTTOM_SCREEN;
    maxSize = CONTAINER_SIZE;
    dialogLayoutAlgorithm->UpdateChildMaxSizeHeight(maxSize);
    EXPECT_EQ(maxSize.Height(), 656);
}

/**
 * @tc.name: DialogModelTwoTestNg034
 * @tc.desc: Test DialogLayoutAlgorithm::SetAlignmentSwitch function
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTwoTestNg, DialogModelTwoTestNg034, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create DialogLayoutAlgorithm instance.
     */
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_THIRTEEN));
    auto dialogLayoutAlgorithm = AceType::MakeRefPtr<DialogLayoutAlgorithm>();
    ASSERT_NE(dialogLayoutAlgorithm, nullptr);

    auto maxSize = CONTAINER_SIZE;
    auto childSize = SizeF(CHILD_SIZE, CHILD_SIZE);
    dialogLayoutAlgorithm->alignment_ = DialogAlignment::TOP;
    dialogLayoutAlgorithm->isHoverMode_ = true;
    dialogLayoutAlgorithm->foldCreaseRect = FOLD_CREASE_RECT;
    OffsetF topLeftPoint;

    /**
     * @tc.steps: step2. call SetAlignmentSwitch function.
     * @tc.expected: the results are correct.
     */
    dialogLayoutAlgorithm->alignBottomScreen_ = true;
    dialogLayoutAlgorithm->SetAlignmentSwitch(maxSize, childSize, topLeftPoint);
    dialogLayoutAlgorithm->AdjustChildPosition(topLeftPoint, topLeftPoint, childSize, true);
    EXPECT_EQ(topLeftPoint.GetY(), FOLD_CREASE_RECT.Bottom());
    dialogLayoutAlgorithm->alignBottomScreen_ = false;
    dialogLayoutAlgorithm->SetAlignmentSwitch(maxSize, childSize, topLeftPoint);
    dialogLayoutAlgorithm->AdjustChildPosition(topLeftPoint, topLeftPoint, childSize, true);
    EXPECT_EQ(topLeftPoint.GetY(), 0);
}

/**
 * @tc.name: DialogModelTwoTestNg035
 * @tc.desc: Test CreateDialogNode with dialogTransition effect and maskTransition effect.
 * @tc.type: FUNC
 */
 HWTEST_F(DialogModelTwoTestNg, DialogModelTwoTestNg035, TestSize.Level1)
 {
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    CHECK_NULL_VOID(rootNode);
    AnimationOption animationOption;
    animationOption.SetDelay(10);

    double opacity = 1.0;
    auto appearOpacityTransition = AceType::MakeRefPtr<NG::ChainedOpacityEffect>(opacity);
    NG::ScaleOptions scale(1.0f, 1.0f, 1.0f, 0.5_pct, 0.5_pct);
    auto disappearScaleTransition = AceType::MakeRefPtr<NG::ChainedScaleEffect>(scale);
    auto dialogTransitionEffect =
        AceType::MakeRefPtr<NG::ChainedAsymmetricEffect>(appearOpacityTransition, disappearScaleTransition);
    auto maskTransitionEffect =
        AceType::MakeRefPtr<NG::ChainedAsymmetricEffect>(appearOpacityTransition, disappearScaleTransition);
 
    DialogProperties dialogProps {
        .type = DialogType::ALERT_DIALOG,
        .title = TITLE,
        .content = MESSAGE,
        .openAnimation = animationOption,
        .dialogTransitionEffect = dialogTransitionEffect,
        .maskTransitionEffect = maskTransitionEffect,
    };
 
    ASSERT_NE(dialogProps.dialogTransitionEffect, nullptr);
    ASSERT_NE(dialogProps.maskTransitionEffect, nullptr);
    /**
     * @tc.steps: step2. Create DialogNode.
     * @tc.expected: DialogNode created successfully
     */
    CHECK_NULL_VOID(rootNode);
    rootNode->GetRenderContext()->UpdateChainedTransition(dialogProps.dialogTransitionEffect);
    ASSERT_NE(rootNode, nullptr);

    CHECK_NULL_VOID(rootNode);
    rootNode->GetRenderContext()->UpdateChainedTransition(dialogProps.maskTransitionEffect);
    ASSERT_NE(rootNode, nullptr);
}
 
 /**
  * @tc.name: DialogModelTwoTestNg036
  * @tc.desc: Test CreateDialogNode with no dialogTransition effect and maskTransition effect.
  * @tc.type: FUNC
  */
 HWTEST_F(DialogModelTwoTestNg, DialogModelTwoTestNg036, TestSize.Level1)
{
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    CHECK_NULL_VOID(rootNode);
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
        .dialogTransitionEffect = nullptr,
        .maskTransitionEffect = nullptr,
    };
 
    /**
     * @tc.steps: step2. Create DialogNode.
     * @tc.expected: DialogNode created successfully
     */
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    CHECK_NULL_VOID(overlayManager);
    auto customDialog = DialogView::CreateDialogNode(dialogProps, nullptr);
    ASSERT_NE(customDialog, nullptr);

    auto customDialogPattern = customDialog->GetPattern<DialogPattern>();
    CHECK_NULL_VOID(customDialogPattern);
    ASSERT_NE(customDialogPattern, nullptr);
    customDialogPattern->SetDialogProperties(dialogProps);

    /**
     * @tc.steps: step3. Call maskTransitionEffect from dialog.
     * @tc.expected: transitionEffect is not nullptr.
     */
    auto dialogTransitionEffect = customDialogPattern->GetDialogProperties().dialogTransitionEffect;
    ASSERT_EQ(dialogTransitionEffect, nullptr);
    auto maskTransitionEffect = customDialogPattern->GetDialogProperties().maskTransitionEffect;
    ASSERT_EQ(maskTransitionEffect, nullptr);
}

/**
 * @tc.name: DialogModelTwoTestNg037
 * @tc.desc: Test ActionSheetModelNG's ShowActionSheet.
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTwoTestNg, DialogModelTwoTestNg037, TestSize.Level1)
{
    /**
     * @tc.steps: step1.Mock data.
     */
    bool onWillAppearFlag = false;
    auto onWillAppearEvent = [&onWillAppearFlag]() { onWillAppearFlag = true; };
    bool onDidAppearFlag = false;
    auto onDidAppearEvent = [&onDidAppearFlag]() { onDidAppearFlag = true; };
    bool onWillDisappearFlag = false;
    auto onWillDisappearEvent = [&onWillDisappearFlag]() { onWillDisappearFlag = true; };
    bool onDidDisappearFlag = false;
    auto onDidDisappearEvent = [&onDidDisappearFlag]() { onDidDisappearFlag = true; };
    ActionSheetModelNG actionSheetModelNg;
    DialogProperties props {
        .onWillAppear = std::move(onWillAppearEvent),
        .onDidAppear = std::move(onDidAppearEvent),
        .onWillDisappear = std::move(onWillDisappearEvent),
        .onDidDisappear = std::move(onDidDisappearEvent),
    };
 
    /**
     * @tc.steps: step2. Call ShowActionSheet.
     * @tc.expected: Check ShowActionSheet.
     */
    actionSheetModelNg.ShowActionSheet(props);
    auto container = Container::Current();
    auto pipelineContext = container->GetPipelineContext();
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    auto overlayManager = context->GetOverlayManager();
    auto dialog = overlayManager->ShowDialog(props, nullptr, false);
    auto dialogPattern = dialog->GetPattern<DialogPattern>();
 
    dialogPattern->CallDialogWillAppearCallback();
    dialogPattern->CallDialogDidAppearCallback();
    dialogPattern->CallDialogWillDisappearCallback();
    dialogPattern->CallDialogDidDisappearCallback();
 
    EXPECT_EQ(onWillAppearFlag, true);
    EXPECT_EQ(onDidAppearFlag, true);
    EXPECT_EQ(onWillDisappearFlag, true);
    EXPECT_EQ(onDidDisappearFlag, true);
}
  
/**
 * @tc.name: DialogModelTwoTestNg038
 * @tc.desc: Test AlertDialogModelNG's SetShowDialog.
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTwoTestNg, DialogModelTwoTestNg038, TestSize.Level1)
{
    /**
     * @tc.steps: step1.Mock data.
     */
    bool onWillAppearFlag = false;
    auto onWillAppearEvent = [&onWillAppearFlag]() { onWillAppearFlag = true; };
    bool onDidAppearFlag = false;
    auto onDidAppearEvent = [&onDidAppearFlag]() { onDidAppearFlag = true; };
    bool onWillDisappearFlag = false;
    auto onWillDisappearEvent = [&onWillDisappearFlag]() { onWillDisappearFlag = true; };
    bool onDidDisappearFlag = false;
    auto onDidDisappearEvent = [&onDidDisappearFlag]() { onDidDisappearFlag = true; };
    AlertDialogModelNG alertDialogModelNg;
    DialogProperties props {
        .onWillAppear = std::move(onWillAppearEvent),
        .onDidAppear = std::move(onDidAppearEvent),
        .onWillDisappear = std::move(onWillDisappearEvent),
        .onDidDisappear = std::move(onDidDisappearEvent),
    };
  
    /**
     * @tc.steps: step2. Call SetShowDialog.
     * @tc.expected: Check SetShowDialog.
     */
    alertDialogModelNg.SetShowDialog(props);
    auto container = Container::Current();
    auto pipelineContext = container->GetPipelineContext();
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    auto overlayManager = context->GetOverlayManager();
    auto dialog = overlayManager->ShowDialog(props, nullptr, false);
    auto dialogPattern = dialog->GetPattern<DialogPattern>();
 
    dialogPattern->CallDialogWillAppearCallback();
    dialogPattern->CallDialogDidAppearCallback();
    dialogPattern->CallDialogWillDisappearCallback();
    dialogPattern->CallDialogDidDisappearCallback();
 
    EXPECT_EQ(onWillAppearFlag, true);
    EXPECT_EQ(onDidAppearFlag, true);
    EXPECT_EQ(onWillDisappearFlag, true);
    EXPECT_EQ(onDidDisappearFlag, true);
}
  
/**
 * @tc.name: DialogModelTwoTestNg039
 * @tc.desc: Test CustomDialogControllerModelNG's SetOpenDialog.
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTwoTestNg, DialogModelTwoTestNg039, TestSize.Level1)
{
    /**
     * @tc.steps: step1.Mock data.
     */
    bool onWillAppearFlag = false;
    auto onWillAppearEvent = [&onWillAppearFlag]() { onWillAppearFlag = true; };
    bool onDidAppearFlag = false;
    auto onDidAppearEvent = [&onDidAppearFlag]() { onDidAppearFlag = true; };
    bool onWillDisappearFlag = false;
    auto onWillDisappearEvent = [&onWillDisappearFlag]() { onWillDisappearFlag = true; };
    bool onDidDisappearFlag = false;
    auto onDidDisappearEvent = [&onDidDisappearFlag]() { onDidDisappearFlag = true; };
    CustomDialogControllerModelNG controllerModel;
    DialogProperties props {
        .onWillAppear = std::move(onWillAppearEvent),
        .onDidAppear = std::move(onDidAppearEvent),
        .onWillDisappear = std::move(onWillDisappearEvent),
        .onDidDisappear = std::move(onDidDisappearEvent),
    };
    WeakPtr<AceType> controller;
    std::vector<WeakPtr<AceType>> dialogs;
    bool pending;
    bool isShown;
    std::function<void()> cancelTask;
    std::function<void()> buildFunc;
    RefPtr<AceType> dialogComponent;
    RefPtr<AceType> customDialog;
    std::list<DialogOperation> dialogOperation;
    bool hasBind = false;
   
    /**
     * @tc.steps: step2. Call SetOpenDialog.
     * @tc.expected: Check SetOpenDialog.
     */
    controllerModel.SetOpenDialog(props, controller, dialogs, pending,
        isShown, std::move(cancelTask), std::move(buildFunc), dialogComponent, customDialog, dialogOperation, hasBind);
    auto container = Container::Current();
    auto pipelineContext = container->GetPipelineContext();
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    auto overlayManager = context->GetOverlayManager();
    auto dialog = overlayManager->ShowDialog(props, nullptr, false);
    auto dialogPattern = dialog->GetPattern<DialogPattern>();
    dialogPattern->CallDialogWillAppearCallback();
    dialogPattern->CallDialogDidAppearCallback();
    dialogPattern->CallDialogWillDisappearCallback();
    dialogPattern->CallDialogDidDisappearCallback();

    EXPECT_EQ(onWillAppearFlag, true);
    EXPECT_EQ(onDidAppearFlag, true);
    EXPECT_EQ(onWillDisappearFlag, true);
    EXPECT_EQ(onDidDisappearFlag, true);
}

/**
 * @tc.name: DialogModelTwoTestNg040
 * @tc.desc: Test AlertDialogModelNG's SetOnWillDismissRelease.
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTwoTestNg, DialogModelTwoTestNg040, TestSize.Level1)
{
    const std::function<void()> EMPTY_FUNC = nullptr;
    /**
     * @tc.steps: step1. Create DialogPattern instance
     */
    RefPtr<DialogTheme> dialogTheme;
    RefPtr<UINode> customNode;
    auto dialogPattern = AceType::MakeRefPtr<DialogPattern>(dialogTheme, customNode);

    /**
     * @tc.steps: step2. Call SetOnWillDismissRelease with empty function
     * @tc.expected: The internal callback should be set to empty function
     */
    dialogPattern->SetOnWillDismissRelease(EMPTY_FUNC);
    EXPECT_EQ(dialogPattern->onWillDismissRelease_, nullptr);
}

/**
 * @tc.name: DialogModelTwoTestNg041
 * @tc.desc: Test AlertDialogModelNG's SetOnWillDismissRelease.
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTwoTestNg, DialogModelTwoTestNg041, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create DialogPattern instance
     */
    RefPtr<DialogTheme> dialogTheme;
    RefPtr<UINode> customNode;
    auto dialogPattern = AceType::MakeRefPtr<DialogPattern>(dialogTheme, customNode);

    /**
     * @tc.steps: step2. Create a flag to check if callback is executed
     */
    bool isCalled = false;
    auto callback = [&isCalled]() { isCalled = true; };

    /**
     * @tc.steps: step3. Call SetOnWillDismissRelease with non-empty function
     * @tc.expected: The internal callback should be set properly
     */
    dialogPattern->SetOnWillDismissRelease(callback);
    EXPECT_NE(dialogPattern->onWillDismissRelease_, nullptr);

    /**
     * @tc.steps: step4. Execute the callback and verify
     * @tc.expected: The callback should be executed properly
     */
    if (dialogPattern->onWillDismissRelease_) {
        dialogPattern->onWillDismissRelease_();
    }
    EXPECT_TRUE(isCalled);
}

/**
 * @tc.name: CustomDialogControllerGetStateTest1
 * @tc.desc: Test CustomDialogControllerModelNG's SetOpenDialog.
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTwoTestNg, CustomDialogControllerGetStateTest1, TestSize.Level1)
{
    /**
     * @tc.steps: step1. mock rootNode,Dialog and FrameNode
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto dialogProps = DialogProperties {
        .title = "Test Title",
        .content = "Test Content",
        .controllerId = 1001
    };

    bool hasBind = false;
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    auto dialogNode =
        FrameNode::CreateFrameNode(V2::DIALOG_ETS_TAG, 2, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);

    dialogPattern->SetDialogProperties(dialogProps);
    dialogPattern->SetState(PromptActionCommonState::APPEARING);
    
    std::vector<WeakPtr<AceType>> dialogs;
    dialogs.emplace_back(WeakPtr<AceType>(dialogNode));

    CustomDialogControllerModelNG controller;
    PromptActionCommonState state = controller.GetState(dialogs, hasBind);
    EXPECT_EQ(state, PromptActionCommonState::APPEARING);

    dialogPattern->SetState(PromptActionCommonState::APPEARED);
    state = controller.GetState(dialogs, hasBind);
    EXPECT_EQ(state, PromptActionCommonState::APPEARED);
}

/**
 * @tc.name: CustomDialogControllerGetStateTest2
 * @tc.desc: Test CustomDialogControllerModelNG's SetOpenDialog.
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTwoTestNg, CustomDialogControllerGetStateTest2, TestSize.Level1)
{
    /**
     * @tc.steps: step1.mock rootNode,Dialog and FrameNode
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto dialogProps = DialogProperties {
        .title = "Test Title",
        .content = "Test Content",
        .controllerId = 1001
    };
    bool hasBind = true;
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();

    auto dialogNode =
        FrameNode::CreateFrameNode(V2::DIALOG_ETS_TAG, 2, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);

    dialogPattern->SetDialogProperties(dialogProps);
    dialogPattern->SetState(PromptActionCommonState::DISAPPEARING);
    
    std::vector<WeakPtr<AceType>> dialogs;
    dialogs.emplace_back(WeakPtr<AceType>(dialogNode));

    CustomDialogControllerModelNG controller;
    PromptActionCommonState state = controller.GetState(dialogs, hasBind);
    EXPECT_EQ(state, PromptActionCommonState::DISAPPEARING);

    dialogPattern->SetState(PromptActionCommonState::DISAPPEARED);
    state = controller.GetState(dialogs, hasBind);
    EXPECT_EQ(state, PromptActionCommonState::DISAPPEARED);
}

/**
 * @tc.name: ComputeInnerLayoutSizeParam001
 * @tc.desc: Test ComputeInnerLayoutSizeParam function
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTwoTestNg, ComputeInnerLayoutSizeParam001, TestSize.Level1)
{
    auto dialogLayoutAlgorithm = AceType::MakeRefPtr<DialogLayoutAlgorithm>();
    DialogProperties props;
    auto dialog = DialogView::CreateDialogNode(props, nullptr);
    ASSERT_NE(dialog, nullptr);
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(dialog, dialog->GetGeometryNode(), dialog->GetLayoutProperty());
    auto innerLayout = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    auto dialogProp = AceType::DynamicCast<DialogLayoutProperty>(layoutWrapper->GetLayoutProperty());
    dialogLayoutAlgorithm->gridCount_ = 1;
    EXPECT_EQ(dialogLayoutAlgorithm->ComputeInnerLayoutSizeParam(innerLayout, dialogProp), false);
}

/**
 * @tc.name: IsGetExpandDisplayValidHeight001
 * @tc.desc: Test IsGetExpandDisplayValidHeight function
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTwoTestNg, IsGetExpandDisplayValidHeight001, TestSize.Level1)
{
    auto dialogLayoutAlgorithm = AceType::MakeRefPtr<DialogLayoutAlgorithm>();
    ASSERT_NE(dialogLayoutAlgorithm, nullptr);
    dialogLayoutAlgorithm->expandDisplay_ = true;
    dialogLayoutAlgorithm->isShowInSubWindow_ = true;
    DialogProperties props;
    auto dialog = DialogView::CreateDialogNode(props, nullptr);
    ASSERT_NE(dialog, nullptr);
    auto dialogProp = dialog->GetLayoutProperty<DialogLayoutProperty>();
    ASSERT_NE(dialogProp, nullptr);
    EXPECT_FALSE(dialogLayoutAlgorithm->IsGetExpandDisplayValidHeight(dialogProp));
}

/**
 * @tc.name: GetMaxWidthBasedOnGridType001
 * @tc.desc: Test GetMaxWidthBasedOnGridType function
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTwoTestNg, GetMaxWidthBasedOnGridType001, TestSize.Level1)
{
    auto dialogLayoutAlgorithm = AceType::MakeRefPtr<DialogLayoutAlgorithm>();

    auto gridColumninfo = AceType::MakeRefPtr<GridColumnInfo>();
    auto parent = AceType::MakeRefPtr<GridContainerInfo>();
    parent->columns_ = 0;
    gridColumninfo->parent_ = parent;
    dialogLayoutAlgorithm->gridCount_ = 1;
    auto type = GridSizeType::UNDEFINED;
    auto deviceType = DeviceType::PHONE;
    EXPECT_EQ(dialogLayoutAlgorithm->GetMaxWidthBasedOnGridType(gridColumninfo, type, deviceType), 0);
}

/**
 * @tc.name: IsDialogTouchingBoundary001
 * @tc.desc: Test IsDialogTouchingBoundary function
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTwoTestNg, IsDialogTouchingBoundary001, TestSize.Level1)
{
    auto dialogLayoutAlgorithm = AceType::MakeRefPtr<DialogLayoutAlgorithm>();
    OffsetF topLeftPoint = OffsetF(100, -1);
    SizeF childSize = SizeF(500.0f, -1.0f);
    SizeF selfSize = SizeF(1.0f, 100.0f);
    dialogLayoutAlgorithm->IsDialogTouchingBoundary(topLeftPoint, childSize, selfSize);
    EXPECT_EQ(dialogLayoutAlgorithm->touchingBoundaryFlag_, TouchingBoundaryType::TouchRightBoundary);

    topLeftPoint = OffsetF(-1, -1);
    childSize = SizeF(-1.0f, -1.0f);
    selfSize = SizeF(100.0f, 100.0f);
    auto result = dialogLayoutAlgorithm->IsDialogTouchingBoundary(topLeftPoint, childSize, selfSize);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: SetOpenDialogWithNode001
 * @tc.desc: Test SetOpenDialogWithNode function
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTwoTestNg, SetOpenDialogWithNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create dialogModel with theme.
     */
    CustomDialogControllerModelNG controllerModel;

    DialogProperties props {
        .type = DialogType::ACTION_SHEET,
        .title = "dialog test",
        .content = "dialog content test",
    };
    /**
     * @tc.steps: step2.Build prerequisite conditions and operational parameters
     */
    controllerModel.SetOpenDialogWithNode(props, nullptr);
    props.isShowInSubWindow = true;
    props.isModal = true;
    props.isSceneBoardDialog = true;
    /**
     * @tc.steps: step3. Call  SetOpenDialogWithNode.
     * @tc.desc: Covering branch isSceneBoardDialog is true
     * @tc.expected: running result(dialog) is nullptr.
     */
    auto result = controllerModel.SetOpenDialogWithNode(props, nullptr);
    EXPECT_EQ(result, nullptr);
    EXPECT_TRUE(props.isShowInSubWindow);
    EXPECT_TRUE(props.isModal);
}

/**
 * @tc.name: SetOpenDialogWithNode002
 * @tc.desc: Test SetOpenDialogWithNode function
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTwoTestNg, SetOpenDialogWithNode002, TestSize.Level1)
{
    /**
    * @tc.steps: step1. Create dialogModel with theme.
    */
    CustomDialogControllerModelNG controllerModel;

    DialogProperties props {
        .type = DialogType::ACTION_SHEET,
        .title = "dialog test",
        .content = "dialog content test",
        .dialogLevelUniqueId = 1,
        .dialogLevelMode = LevelMode::EMBEDDED,
    };
    /**
     * @tc.steps: step2.Build prerequisite conditions and operational parameters
     */
    controllerModel.SetOpenDialogWithNode(props, nullptr);
    props.isShowInSubWindow = false;
    props.isModal = true;
    props.isSceneBoardDialog = true;
    /**
     * @tc.steps: step3. Call  SetOpenDialogWithNode.
     * @tc.desc: Covering branch dialogLevelMode is EMBEDDED
     */
    auto result = controllerModel.SetOpenDialogWithNode(props, nullptr);
    EXPECT_NE(result, nullptr);
    EXPECT_FALSE(props.isShowInSubWindow);
    EXPECT_TRUE(props.isModal);
}

/**
 * @tc.name: SetOpenDialogWithNode003
 * @tc.desc: Test SetOpenDialogWithNode function
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTwoTestNg, SetOpenDialogWithNode003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create dialogModel with theme.
     */
    CustomDialogControllerModelNG controllerModel;

    DialogProperties props {
        .type = DialogType::ACTION_SHEET,
        .title = "dialog test",
        .content = "dialog content test",
    };
    /**
     * @tc.steps: step2.Build prerequisite conditions and operational parameters
     */
    controllerModel.SetOpenDialogWithNode(props, nullptr);
    props.isShowInSubWindow = true;
    props.isModal = true;
    props.isSceneBoardDialog = false;
    /**
     * @tc.steps: step3. Call  SetOpenDialogWithNode.
     * @tc.desc: Covering branch isSceneBoardDialog is false
     * @tc.expected: running result(dialog) is nullptr.
     */
    auto result = controllerModel.SetOpenDialogWithNode(props, nullptr);
    EXPECT_EQ(result, nullptr);
    EXPECT_TRUE(props.isShowInSubWindow);
    EXPECT_TRUE(props.isModal);
}

/**
 * @tc.name: DialogPatternTest032
 * @tc.desc: Test dialogPattern.BuildTitle
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTwoTestNg, DialogPatternTest032, TestSize.Level1)
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
    props.isSysBlurStyle = true;
    BlurStyleOption blurStyleOption;
    blurStyleOption.policy = BlurStyleActivePolicy::FOLLOWS_WINDOW_ACTIVE_STATE;
    blurStyleOption.blurStyle = BlurStyle::COMPONENT_ULTRA_THICK;
    if (!props.blurStyleOption.has_value()) {
        props.blurStyleOption.emplace();
    }
    props.blurStyleOption.value() = blurStyleOption;

    pattern->UpdateContentRenderContext(dialogNode, props);
    auto renderContext = pattern->contentRenderContext_;
    ASSERT_NE(renderContext, nullptr);

    EXPECT_FALSE(renderContext->GetBackgroundEffect().has_value());
    EXPECT_TRUE(renderContext->GetBackBlurStyle().has_value());
    EXPECT_EQ(renderContext->GetBackBlurStyle().value(), blurStyleOption);
}

/**
 * @tc.name: DialogPatternTest033
 * @tc.desc: Test dialogPattern.BuildTitle
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTwoTestNg, DialogPatternTest033, TestSize.Level1)
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
    props.isSysBlurStyle = true;
    EffectOption effectOption;
    effectOption.policy = BlurStyleActivePolicy::FOLLOWS_WINDOW_ACTIVE_STATE;
    if (!props.effectOption.has_value()) {
        props.effectOption.emplace();
    }
    props.effectOption.value() = effectOption;

    pattern->UpdateContentRenderContext(dialogNode, props);
    auto renderContext = pattern->contentRenderContext_;
    ASSERT_NE(renderContext, nullptr);

    EXPECT_FALSE(renderContext->GetBackBlurStyle().has_value());
    EXPECT_TRUE(renderContext->GetBackgroundEffect().has_value());
    EXPECT_EQ(renderContext->GetBackgroundEffect().value(), effectOption);
}

/**
 * @tc.name: DialogPatternTest034
 * @tc.desc: Test dialogPattern.BuildTitle
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTwoTestNg, DialogPatternTest034, TestSize.Level1)
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
    props.isSysBlurStyle = true;

    BlurStyleOption blurStyleOption;
    blurStyleOption.policy = BlurStyleActivePolicy::FOLLOWS_WINDOW_ACTIVE_STATE;
    blurStyleOption.blurStyle = BlurStyle::COMPONENT_ULTRA_THICK;
    if (!props.blurStyleOption.has_value()) {
        props.blurStyleOption.emplace();
    }
    props.blurStyleOption.value() = blurStyleOption;

    EffectOption effectOption;
    effectOption.policy = BlurStyleActivePolicy::FOLLOWS_WINDOW_ACTIVE_STATE;
    if (!props.effectOption.has_value()) {
        props.effectOption.emplace();
    }
    props.effectOption.value() = effectOption;

    pattern->UpdateContentRenderContext(dialogNode, props);
    auto renderContext = pattern->contentRenderContext_;
    ASSERT_NE(renderContext, nullptr);

    EXPECT_FALSE(renderContext->GetBackBlurStyle().has_value());
    EXPECT_TRUE(renderContext->GetBackgroundEffect().has_value());
    EXPECT_EQ(renderContext->GetBackgroundEffect().value(), effectOption);
}

/**
 * @tc.name: DialogPatternTest035
 * @tc.desc: Test dialogPattern.BuildTitle
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTwoTestNg, DialogPatternTest035, TestSize.Level1)
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
    props.isSysBlurStyle = true;
    if (!props.backgroundBlurStyle.has_value()) {
        props.backgroundBlurStyle.emplace();
    }
    auto backgroundBlurStyle = static_cast<int>(BlurStyle::THIN);
    props.backgroundBlurStyle.value() = backgroundBlurStyle;

    pattern->UpdateContentRenderContext(dialogNode, props);
    auto renderContext = pattern->contentRenderContext_;
    ASSERT_NE(renderContext, nullptr);

    EXPECT_FALSE(renderContext->GetBackgroundEffect().has_value());
    EXPECT_TRUE(renderContext->GetBackBlurStyle().has_value());
    EXPECT_EQ(static_cast<int>(renderContext->GetBackBlurStyle().value().blurStyle), backgroundBlurStyle);
}

/**
 * @tc.name: DialogModelTwoTestNg051
 * @tc.desc: Test DialogLayoutAlgorithm.DialogOverflowAdjust function.
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTwoTestNg, DialogModelTwoTestNg051, TestSize.Level1) {
    /**
     * @tc.steps: step1. create layoutAlgorithm instance.
     */
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto layoutAlgorithm = AceType::MakeRefPtr<DialogLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);

    /**
     * @tc.steps: step2. Set safe area range.
     */
    SafeAreaInsets::Inset insetLeftAndRight = {};
    SafeAreaInsets::Inset insetTop = { .start = 0.f, .end = 100.f };
    SafeAreaInsets::Inset insetBottom = { .start = 1100.f, .end = 1200.f };
    SafeAreaInsets SYSTEM_SAFE_AREA_INSET = { insetLeftAndRight, insetTop, insetLeftAndRight,
        insetBottom };
    layoutAlgorithm->safeAreaInsets_ = SYSTEM_SAFE_AREA_INSET;
    
    /**
     * @tc.steps: step3. Call DialogOverflowAdjust with dialogCorrectionEnabled = false.
     * @tc.desc: Correction disabled — no adjustment logic is applied.
     * @tc.expected: childOffset and dialogChildSize_ remain unchanged.
     */
    auto childOffset = OffsetF(0.f, OFFSET_TOP_OVERFLOW);
    auto childSize = SizeF(CHILD_SIZE, CHILD_SIZE);
    bool dialogCorrectionEnabled = false;
    layoutAlgorithm->dialogChildSize_.SetHeight(CHILD_SIZE);

    layoutAlgorithm->DialogOverflowAdjust(childOffset, childSize, dialogCorrectionEnabled);
    EXPECT_EQ(childOffset.GetY(), OFFSET_TOP_OVERFLOW);
    EXPECT_EQ(layoutAlgorithm->dialogChildSize_.Height(), CHILD_SIZE);
    
    /**
     * @tc.steps: step4. Call DialogOverflowAdjust with dialogCorrectionEnabled = true.
     * @tc.desc: Correction enabled — adjustment logic runs to modify offset and size.
     * @tc.expected: childOffset and dialogChildSize_ are updated as asserted.
     */
    dialogCorrectionEnabled = true;

    layoutAlgorithm->DialogOverflowAdjust(childOffset, childSize, dialogCorrectionEnabled);
    EXPECT_EQ(childOffset.GetY(), 150.f);
    EXPECT_EQ(layoutAlgorithm->dialogChildSize_.Height(), CHILD_SIZE);

    childOffset.SetY(OFFSET_BOTTOM_OVERFLOW);
    layoutAlgorithm->DialogOverflowAdjust(childOffset, childSize, dialogCorrectionEnabled);
    EXPECT_EQ(childOffset.GetY(), 750.f);
    EXPECT_EQ(layoutAlgorithm->dialogChildSize_.Height(), CHILD_SIZE);

    childOffset.SetY(OFFSET);
    childSize.SetHeight(CHILD_SIZE_OVERFLOW);
    layoutAlgorithm->DialogOverflowAdjust(childOffset, childSize, dialogCorrectionEnabled);
    EXPECT_EQ(childOffset.GetY(), 150.f);
    EXPECT_EQ(layoutAlgorithm->dialogChildSize_.Height(), 900.f);

    childOffset.SetY(OFFSET_TOP_OVERFLOW);
    childSize.SetHeight(CHILD_SIZE_OVERFLOW);
    layoutAlgorithm->DialogOverflowAdjust(childOffset, childSize, dialogCorrectionEnabled);
    EXPECT_EQ(childOffset.GetY(), 150.f);
    EXPECT_EQ(layoutAlgorithm->dialogChildSize_.Height(), 900.f);

    childOffset.SetY(OFFSET_BOTTOM_OVERFLOW);
    childSize.SetHeight(CHILD_SIZE_OVERFLOW);
    layoutAlgorithm->DialogOverflowAdjust(childOffset, childSize, dialogCorrectionEnabled);
    EXPECT_EQ(childOffset.GetY(), 150.f);
    EXPECT_EQ(layoutAlgorithm->dialogChildSize_.Height(), 900.f);
}

/**
 * @tc.name: DialogModelTwoTestNg045
 * @tc.desc: Test DialogView's UpdateAndAddMaskColorCallback
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTwoTestNg, DialogModelTwoTestNg045, TestSize.Level1)
{
    auto isConfigChangePerform = g_isConfigChangePerform;
    g_isConfigChangePerform = true;
    MockContainer::SetMockColorMode(ColorMode::DARK);
    ResourceParseUtils::SetIsReloading(true);
    HasInvertColor hasInvertColor {
        .hasMaskColor = true,
    };
    DialogProperties props {
        .maskColor = Color::BLUE,
        .isMask = true,
        .hasInvertColor = hasInvertColor,
    };
    auto invertFunc = [](uint32_t color) { return ColorInverter::DefaultInverter(color); };
    ColorInverter::GetInstance().EnableColorInvert(Container::CurrentIdSafely(), "", std::move(invertFunc));
    auto contentNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 100, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(contentNode, nullptr);
    auto dialogNode = DialogView::CreateDialogNode(props, contentNode);
    ASSERT_NE(dialogNode, nullptr);
    auto pattern = dialogNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->resourceMgr_->ReloadResources();

    auto renderContext = dialogNode->GetRenderContext();
    auto resMaskColor = renderContext->GetBackgroundColor();
    EXPECT_TRUE(resMaskColor.has_value());
    EXPECT_EQ(resMaskColor.value(), COLORYELLOW);
    g_isConfigChangePerform = isConfigChangePerform;
}

/**
 * @tc.name: DialogModelTwoTestNg046
 * @tc.desc: Test DialogView's UpdateAndAddShadowCallback
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTwoTestNg, DialogModelTwoTestNg046, TestSize.Level1)
{
    auto isConfigChangePerform = g_isConfigChangePerform;
    g_isConfigChangePerform = true;
    MockContainer::SetMockColorMode(ColorMode::DARK);
    ResourceParseUtils::SetIsReloading(true);
    Shadow shadow;
    shadow.SetColor(Color::BLUE);
    HasInvertColor hasInvertColor {
        .hasShadowColor = true,
    };
    DialogProperties props {
        .shadow = shadow,
        .hasInvertColor = hasInvertColor,
    };
    auto invertFunc = [](uint32_t color) { return ColorInverter::DefaultInverter(color); };
    ColorInverter::GetInstance().EnableColorInvert(Container::CurrentIdSafely(), "", std::move(invertFunc));
    auto contentNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 100, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(contentNode, nullptr);
    auto dialogNode = DialogView::CreateDialogNode(props, contentNode);
    ASSERT_NE(dialogNode, nullptr);
    auto pattern = dialogNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->resourceMgr_->ReloadResources();

    auto contentColumn = AceType::DynamicCast<FrameNode>(dialogNode->GetFirstChild());
    auto contentColumnRenderContext = contentColumn->GetRenderContext();
    auto resShadow = contentColumnRenderContext->GetBackShadow();
    EXPECT_TRUE(resShadow.has_value());
    EXPECT_EQ(resShadow.value().GetColor(), COLORYELLOW);
    g_isConfigChangePerform = isConfigChangePerform;
}

/**
 * @tc.name: DialogModelTwoTestNg047
 * @tc.desc: Test DialogView's UpdateAndAddBackgroundColorCallback
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTwoTestNg, DialogModelTwoTestNg047, TestSize.Level1)
{
    auto isConfigChangePerform = g_isConfigChangePerform;
    g_isConfigChangePerform = true;
    MockContainer::SetMockColorMode(ColorMode::DARK);
    ResourceParseUtils::SetIsReloading(true);
    HasInvertColor hasInvertColor {
        .hasBackgroundColor = true,
    };
    DialogProperties props {
        .backgroundColor = Color::BLUE,
        .hasInvertColor = hasInvertColor,
    };
    auto invertFunc = [](uint32_t color) { return ColorInverter::DefaultInverter(color); };
    ColorInverter::GetInstance().EnableColorInvert(Container::CurrentIdSafely(), "", std::move(invertFunc));
    auto contentNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 100, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(contentNode, nullptr);
    auto dialogNode = DialogView::CreateDialogNode(props, contentNode);
    ASSERT_NE(dialogNode, nullptr);
    auto pattern = dialogNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->resourceMgr_->ReloadResources();

    auto contentColumn = AceType::DynamicCast<FrameNode>(dialogNode->GetFirstChild());
    auto contentColumnRenderContext = contentColumn->GetRenderContext();
    auto resBgColor = contentColumnRenderContext->GetBackgroundColor();
    EXPECT_TRUE(resBgColor.has_value());
    EXPECT_EQ(resBgColor.value(), COLORYELLOW);
    g_isConfigChangePerform = isConfigChangePerform;
}

/**
 * @tc.name: DialogModelTwoTestNg048
 * @tc.desc: Test DialogView's UpdateAndAddBorderColorCallback
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTwoTestNg, DialogModelTwoTestNg048, TestSize.Level1)
{
    auto isConfigChangePerform = g_isConfigChangePerform;
    g_isConfigChangePerform = true;
    MockContainer::SetMockColorMode(ColorMode::DARK);
    ResourceParseUtils::SetIsReloading(true);
    BorderColorProperty borderColor;
    borderColor.SetColor(Color::BLUE);
    HasInvertColor hasInvertColor {
        .hasBorderTopColor = true,
        .hasBorderBottomColor = true,
        .hasBorderLeftColor = true,
        .hasBorderRightColor = true,
    };
    DialogProperties props {
        .borderColor = borderColor,
        .hasInvertColor = hasInvertColor,
    };
    auto invertFunc = [](uint32_t color) { return ColorInverter::DefaultInverter(color); };
    ColorInverter::GetInstance().EnableColorInvert(Container::CurrentIdSafely(), "", std::move(invertFunc));
    auto contentNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 100, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(contentNode, nullptr);
    auto dialogNode = DialogView::CreateDialogNode(props, contentNode);
    ASSERT_NE(dialogNode, nullptr);
    auto pattern = dialogNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->resourceMgr_->ReloadResources();

    auto contentColumn = AceType::DynamicCast<FrameNode>(dialogNode->GetFirstChild());
    auto contentColumnRenderContext = contentColumn->GetRenderContext();
    auto resBorderColor = contentColumnRenderContext->GetBorderColor();
    EXPECT_TRUE(resBorderColor.has_value());
    EXPECT_TRUE(resBorderColor.value().topColor.has_value());
    EXPECT_EQ(resBorderColor.value().topColor.value(), COLORYELLOW);
    EXPECT_TRUE(resBorderColor.value().bottomColor.has_value());
    EXPECT_EQ(resBorderColor.value().bottomColor.value(), COLORYELLOW);
    EXPECT_TRUE(resBorderColor.value().leftColor.has_value());
    EXPECT_EQ(resBorderColor.value().leftColor.value(), COLORYELLOW);
    EXPECT_TRUE(resBorderColor.value().rightColor.has_value());
    EXPECT_EQ(resBorderColor.value().rightColor.value(), COLORYELLOW);
    g_isConfigChangePerform = isConfigChangePerform;
}

/**
 * @tc.name: DialogModelTwoTestNg049
 * @tc.desc: Test DialogView's UpdateAndAddBlurStyleOptionCallback
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTwoTestNg, DialogModelTwoTestNg049, TestSize.Level1)
{
    auto isConfigChangePerform = g_isConfigChangePerform;
    g_isConfigChangePerform = true;
    MockContainer::SetMockColorMode(ColorMode::DARK);
    ResourceParseUtils::SetIsReloading(true);
    BlurStyleOption blurStyleOption;
    blurStyleOption.inactiveColor = Color::BLUE;
    HasInvertColor hasInvertColor {
        .hasBlurStyleOptionInactiveColor = true,
    };
    DialogProperties props {
        .blurStyleOption = blurStyleOption,
        .hasInvertColor = hasInvertColor,
    };
    auto invertFunc = [](uint32_t color) { return ColorInverter::DefaultInverter(color); };
    ColorInverter::GetInstance().EnableColorInvert(Container::CurrentIdSafely(), "", std::move(invertFunc));
    auto contentNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 100, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(contentNode, nullptr);
    auto dialogNode = DialogView::CreateDialogNode(props, contentNode);
    ASSERT_NE(dialogNode, nullptr);
    auto pattern = dialogNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->resourceMgr_->ReloadResources();

    auto contentColumn = AceType::DynamicCast<FrameNode>(dialogNode->GetFirstChild());
    auto contentColumnRenderContext = contentColumn->GetRenderContext();
    auto resBlurStyleOption = contentColumnRenderContext->GetBackBlurStyle();
    EXPECT_TRUE(resBlurStyleOption.has_value());
    EXPECT_EQ(resBlurStyleOption.value().inactiveColor, COLORYELLOW);
    g_isConfigChangePerform = isConfigChangePerform;
}

/**
 * @tc.name: DialogModelTwoTestNg050
 * @tc.desc: Test DialogView's UpdateAndAddEffectOptionCallback
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTwoTestNg, DialogModelTwoTestNg050, TestSize.Level1)
{
    auto isConfigChangePerform = g_isConfigChangePerform;
    g_isConfigChangePerform = true;
    MockContainer::SetMockColorMode(ColorMode::DARK);
    ResourceParseUtils::SetIsReloading(true);
    EffectOption effectOption;
    effectOption.color = Color::BLUE;
    effectOption.inactiveColor = Color::BLUE;
    HasInvertColor hasInvertColor {
        .hasEffectOptionColor = true,
        .hasEffectOptionInactiveColor = true,
    };
    DialogProperties props {
        .effectOption = effectOption,
        .hasInvertColor = hasInvertColor,
    };
    auto invertFunc = [](uint32_t color) { return ColorInverter::DefaultInverter(color); };
    ColorInverter::GetInstance().EnableColorInvert(Container::CurrentIdSafely(), "", std::move(invertFunc));
    auto contentNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 100, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(contentNode, nullptr);
    auto dialogNode = DialogView::CreateDialogNode(props, contentNode);
    ASSERT_NE(dialogNode, nullptr);
    auto pattern = dialogNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->resourceMgr_->ReloadResources();

    auto contentColumn = AceType::DynamicCast<FrameNode>(dialogNode->GetFirstChild());
    auto contentColumnRenderContext = contentColumn->GetRenderContext();
    auto resEffectOption = contentColumnRenderContext->GetBackgroundEffect();
    EXPECT_TRUE(resEffectOption.has_value());
    EXPECT_EQ(resEffectOption.value().color, COLORYELLOW);
    EXPECT_EQ(resEffectOption.value().inactiveColor, COLORYELLOW);
    g_isConfigChangePerform = isConfigChangePerform;
}
} // namespace OHOS::Ace::NG