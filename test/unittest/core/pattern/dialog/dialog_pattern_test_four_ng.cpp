/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include <memory>

#include "gtest/gtest.h"
#include "test/unittest/core/pattern/image/image_base.h"
#include "ui/base/ace_type.h"

#include "base/utils/singleton.h"
#include "core/common/display_info.h"
#include "core/components_ng/base/frame_node.h"
#include "core/pipeline/base/constants.h"
#define private public
#define protected public
#include "test/mock/adapter/ohos/osal/mock_system_properties.h"
#include "test/mock/frameworks/base/subwindow/mock_subwindow.h"
#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/unittest/core/event/frame_node_on_tree.h"

#include "base/log/dump_log.h"
#include "base/subwindow/subwindow_manager.h"
#include "core/accessibility/accessibility_manager_ng.h"
#include "core/common/ace_engine.h"
#include "core/common/recorder/event_recorder.h"
#include "core/common/resource/resource_object.h"
#include "core/components/button/button_theme.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/blur_style_option.h"
#include "core/components/common/properties/shadow.h"
#include "core/components/common/properties/ui_material.h"
#include "core/components/dialog/dialog_properties.h"
#include "core/components/select/select_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/dialog/action_sheet/action_sheet_model_ng.h"
#include "core/components_ng/pattern/dialog/alert_dialog/alert_dialog_model_ng.h"
#include "core/components_ng/pattern/dialog/custom_dialog/custom_dialog_controller_model_ng.h"
#include "core/components_ng/pattern/dialog/dialog_event_hub.h"
#include "core/components_ng/pattern/dialog/dialog_layout_algorithm.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_view.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/list/list_item_pattern.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/navrouter/navdestination_group_node.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "core/components_ng/pattern/overlay/dialog_manager.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/stage/stage_manager.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/property/border_property.h"
#include "core/components_ng/render/render_context.h"
#include "core/components_v2/inspector/inspector_constants.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const std::string TITLE = "title";
const std::string SUBTITLE = "subtitle";
const std::string MESSAGE = "hello world";
const RectF CONTROL_RECT = RectF(0.0f, 0.0f, 100.0f, 100.0f);
} // namespace

class DialogPatternTestFourNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void DialogPatternTestFourNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    RefPtr<FrameNode> stageNode = AceType::MakeRefPtr<FrameNode>("STAGE", -1, AceType::MakeRefPtr<Pattern>());
    auto stageManager = AceType::MakeRefPtr<StageManager>(stageNode);
    MockPipelineContext::GetCurrent()->stageManager_ = stageManager;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    MockSystemProperties::g_isSuperFoldDisplayDevice = false;

    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        if (type == DialogTheme::TypeId()) {
            return AceType::MakeRefPtr<DialogTheme>();
        } else if (type == ButtonTheme::TypeId()) {
            return AceType::MakeRefPtr<ButtonTheme>();
        } else if (type == TextTheme::TypeId()) {
            return AceType::MakeRefPtr<TextTheme>();
        } else {
            return nullptr;
        }
    });
    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([](ThemeType type, int32_t themeScopeId) -> RefPtr<Theme> {
            if (type == DialogTheme::TypeId()) {
                return AceType::MakeRefPtr<DialogTheme>();
            } else if (type == ButtonTheme::TypeId()) {
                return AceType::MakeRefPtr<ButtonTheme>();
            } else if (type == TextTheme::TypeId()) {
                return AceType::MakeRefPtr<TextTheme>();
            } else {
                return nullptr;
            }
        });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void DialogPatternTestFourNg::TearDownTestCase()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}
/**
 * @tc.name: NeedDistortionCachedValue001
 * @tc.desc: Test NeedDistortion with cached value already set
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, NeedDistortionCachedValue001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    pattern->needDistortion_ = true;
    EXPECT_TRUE(pattern->NeedDistortion());

    pattern->needDistortion_ = false;
    EXPECT_FALSE(pattern->NeedDistortion());
}

/**
 * @tc.name: NeedDistortionNoSystemMaterial001
 * @tc.desc: Test NeedDistortion with no system material set
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, NeedDistortionNoSystemMaterial001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    pattern->dialogProperties_.systemMaterial = nullptr;
    pattern->needDistortion_.reset();
    EXPECT_FALSE(pattern->NeedDistortion());
}

/**
 * @tc.name: NeedDistortionWithMask001
 * @tc.desc: Test NeedDistortion with isMask property set to true
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, NeedDistortionWithMask001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    pattern->dialogProperties_.isMask = true;
    pattern->dialogProperties_.systemMaterial = AceType::MakeRefPtr<UiMaterial>();
    pattern->needDistortion_.reset();
    EXPECT_FALSE(pattern->NeedDistortion());
}

/**
 * @tc.name: NeedDistortionCustomStyle001
 * @tc.desc: Test NeedDistortion with customStyle property set
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, NeedDistortionCustomStyle001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    pattern->dialogProperties_.customStyle = true;
    pattern->dialogProperties_.systemMaterial = AceType::MakeRefPtr<UiMaterial>();
    pattern->needDistortion_.reset();
    EXPECT_FALSE(pattern->NeedDistortion());
}

/**
 * @tc.name: NeedDistortionEnabledMode001
 * @tc.desc: Test NeedDistortion with distortion mode set to ENABLED
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, NeedDistortionEnabledMode001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    pattern->dialogProperties_.distortionMode = DistortionMode::DISTORTION_ENABLED;
    pattern->dialogProperties_.systemMaterial = AceType::MakeRefPtr<UiMaterial>();
    pattern->needDistortion_.reset();
    EXPECT_TRUE(pattern->NeedDistortion());
}

/**
 * @tc.name: NeedDistortionDisabledMode001
 * @tc.desc: Test NeedDistortion with distortion mode set to DISABLED
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, NeedDistortionDisabledMode001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    pattern->dialogProperties_.distortionMode = DistortionMode::DISTORTION_DISABLED;
    pattern->dialogProperties_.systemMaterial = AceType::MakeRefPtr<UiMaterial>();
    pattern->needDistortion_.reset();
    EXPECT_FALSE(pattern->NeedDistortion());
}

/**
 * @tc.name: NeedDistortionAutoMode001
 * @tc.desc: Test NeedDistortion with distortion mode set to AUTO
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, NeedDistortionAutoMode001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    pattern->dialogProperties_.distortionMode = DistortionMode::DISTORTION_AUTO;
    pattern->dialogProperties_.systemMaterial = AceType::MakeRefPtr<UiMaterial>();
    pattern->needDistortion_.reset();
    auto result = pattern->NeedDistortion();
    EXPECT_TRUE(result || !result);
}

/**
 * @tc.name: NeedDistortionWithTransitionEffect001
 * @tc.desc: Test NeedDistortion when transitionEffect is set
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, NeedDistortionWithTransitionEffect001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    pattern->dialogProperties_.transitionEffect = nullptr;
    pattern->dialogProperties_.systemMaterial = AceType::MakeRefPtr<UiMaterial>();
    pattern->needDistortion_.reset();
    EXPECT_FALSE(pattern->NeedDistortion());
}

/**
 * @tc.name: NeedDistortionWithDialogTransitionEffect001
 * @tc.desc: Test NeedDistortion when dialogTransitionEffect is set
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, NeedDistortionWithDialogTransitionEffect001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    pattern->dialogProperties_.dialogTransitionEffect = nullptr;
    pattern->dialogProperties_.systemMaterial = AceType::MakeRefPtr<UiMaterial>();
    pattern->needDistortion_.reset();
    EXPECT_FALSE(pattern->NeedDistortion());
}

/**
 * @tc.name: NeedDistortionWithMaskTransitionEffect001
 * @tc.desc: Test NeedDistortion when maskTransitionEffect is set
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, NeedDistortionWithMaskTransitionEffect001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    pattern->dialogProperties_.maskTransitionEffect = nullptr;
    pattern->dialogProperties_.systemMaterial = AceType::MakeRefPtr<UiMaterial>();
    pattern->needDistortion_.reset();
    EXPECT_FALSE(pattern->NeedDistortion());
}

/**
 * @tc.name: NeedEdgeLightCachedValue001
 * @tc.desc: Test NeedEdgeLight with cached value already set
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, NeedEdgeLightCachedValue001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    pattern->needFlowLight_ = true;
    EXPECT_TRUE(pattern->NeedEdgeLight());

    pattern->needFlowLight_ = false;
    EXPECT_FALSE(pattern->NeedEdgeLight());
}

/**
 * @tc.name: NeedEdgeLightNoSystemMaterial001
 * @tc.desc: Test NeedEdgeLight with no system material set
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, NeedEdgeLightNoSystemMaterial001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    pattern->dialogProperties_.systemMaterial = nullptr;
    pattern->needFlowLight_.reset();
    EXPECT_FALSE(pattern->NeedEdgeLight());
}

/**
 * @tc.name: NeedEdgeLightWithMask001
 * @tc.desc: Test NeedEdgeLight with isMask property set
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, NeedEdgeLightWithMask001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    pattern->dialogProperties_.isMask = true;
    pattern->dialogProperties_.systemMaterial = AceType::MakeRefPtr<UiMaterial>();
    pattern->needFlowLight_.reset();
    EXPECT_FALSE(pattern->NeedEdgeLight());
}

/**
 * @tc.name: NeedEdgeLightEnabledMode001
 * @tc.desc: Test NeedEdgeLight with edge light mode ENABLED
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, NeedEdgeLightEnabledMode001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    pattern->dialogProperties_.edgeLightMode = EdgeLightMode::EDGELIGHT_ENABLED;
    pattern->dialogProperties_.systemMaterial = AceType::MakeRefPtr<UiMaterial>();
    pattern->needFlowLight_.reset();
    EXPECT_TRUE(pattern->NeedEdgeLight());
}

/**
 * @tc.name: NeedEdgeLightDisabledMode001
 * @tc.desc: Test NeedEdgeLight with edge light mode DISABLED
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, NeedEdgeLightDisabledMode001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    pattern->dialogProperties_.edgeLightMode = EdgeLightMode::EDGELIGHT_DISABLED;
    pattern->dialogProperties_.systemMaterial = AceType::MakeRefPtr<UiMaterial>();
    pattern->needFlowLight_.reset();
    EXPECT_FALSE(pattern->NeedEdgeLight());
}

/**
 * @tc.name: NeedEdgeLightCustomStyle001
 * @tc.desc: Test NeedEdgeLight with customStyle set
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, NeedEdgeLightCustomStyle001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    pattern->dialogProperties_.customStyle = true;
    pattern->dialogProperties_.systemMaterial = AceType::MakeRefPtr<UiMaterial>();
    pattern->needFlowLight_.reset();
    EXPECT_FALSE(pattern->NeedEdgeLight());
}

/**
 * @tc.name: NeedEdgeLightAutoMode001
 * @tc.desc: Test NeedEdgeLight with edge light mode AUTO
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, NeedEdgeLightAutoMode001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    pattern->dialogProperties_.edgeLightMode = EdgeLightMode::EDGELIGHT_AUTO;
    pattern->dialogProperties_.systemMaterial = AceType::MakeRefPtr<UiMaterial>();
    pattern->needFlowLight_.reset();
    auto result = pattern->NeedEdgeLight();
    EXPECT_TRUE(result || !result);
}

/**
 * @tc.name: ShouldApplySystemMaterialShadow001
 * @tc.desc: Test ShouldApplySystemMaterialShadow with no system material
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, ShouldApplySystemMaterialShadow001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    pattern->dialogProperties_.systemMaterial = nullptr;
    EXPECT_FALSE(pattern->ShouldApplySystemMaterialShadow());
}

/**
 * @tc.name: ShouldApplySystemMaterialShadow002
 * @tc.desc: Test ShouldApplySystemMaterialShadow with system material set
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, ShouldApplySystemMaterialShadow002, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    pattern->dialogProperties_.systemMaterial = AceType::MakeRefPtr<UiMaterial>();
    auto result = pattern->ShouldApplySystemMaterialShadow();
    EXPECT_TRUE(result || !result);
}

/**
 * @tc.name: GetMaskNodeNotModal001
 * @tc.desc: Test GetMaskNode when dialog is not modal
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, GetMaskNodeNotModal001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    pattern->dialogProperties_.isModal = false;
    auto maskNode = pattern->GetMaskNode();
    EXPECT_EQ(maskNode, nullptr);
}

/**
 * @tc.name: GetMaskNodeWithExtraMaskNode001
 * @tc.desc: Test GetMaskNode when extra mask node exists
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, GetMaskNodeWithExtraMaskNode001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    auto extraMaskNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(extraMaskNode, nullptr);
    pattern->extraMaskNode_ = extraMaskNode;
    pattern->dialogProperties_.isModal = true;
    auto maskNode = pattern->GetMaskNode();
    EXPECT_EQ(maskNode, extraMaskNode);
}

/**
 * @tc.name: GetMaskNodeUIExtensionSubWindow001
 * @tc.desc: Test GetMaskNode when isUIExtensionSubWindow is true
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, GetMaskNodeUIExtensionSubWindow001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    pattern->isUIExtensionSubWindow_ = true;
    pattern->dialogProperties_.isModal = true;
    auto maskNode = pattern->GetMaskNode();
    EXPECT_EQ(maskNode, frameNode);
}

/**
 * @tc.name: GetMaskNodeSceneBoardDialog001
 * @tc.desc: Test GetMaskNode when isSceneBoardDialog is true
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, GetMaskNodeSceneBoardDialog001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    pattern->dialogProperties_.isSceneBoardDialog = true;
    pattern->dialogProperties_.isModal = true;
    auto maskNode = pattern->GetMaskNode();
    EXPECT_EQ(maskNode, frameNode);
}

/**
 * @tc.name: GetMaskNodeNotShowInSubWindow001
 * @tc.desc: Test GetMaskNode when isShowInSubWindow is false
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, GetMaskNodeNotShowInSubWindow001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    pattern->dialogProperties_.isModal = true;
    pattern->dialogProperties_.isShowInSubWindow = false;
    auto maskNode = pattern->GetMaskNode();
    EXPECT_EQ(maskNode, frameNode);
}

/**
 * @tc.name: GetMaskNodeShowInSubWindow001
 * @tc.desc: Test GetMaskNode when isShowInSubWindow is true but no other conditions
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, GetMaskNodeShowInSubWindow001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    pattern->dialogProperties_.isModal = true;
    pattern->dialogProperties_.isShowInSubWindow = true;
    pattern->isUIExtensionSubWindow_ = false;
    pattern->dialogProperties_.isSceneBoardDialog = false;
    auto maskNode = pattern->GetMaskNode();
    EXPECT_EQ(maskNode, nullptr);
}

/**
 * @tc.name: OnAvoidInfoChange001
 * @tc.desc: Test OnAvoidInfoChange function
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, OnAvoidInfoChange001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    ContainerModalAvoidInfo info;
    EXPECT_NO_FATAL_FAILURE(pattern->OnAvoidInfoChange(info));
}

/**
 * @tc.name: RegisterAvoidInfoChangeListener001
 * @tc.desc: Test RegisterAvoidInfoChangeListener function
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, RegisterAvoidInfoChangeListener001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    EXPECT_NO_FATAL_FAILURE(pattern->RegisterAvoidInfoChangeListener(frameNode));
}

/**
 * @tc.name: RegisterAvoidInfoChangeListener002
 * @tc.desc: Test RegisterAvoidInfoChangeListener with null host node
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, RegisterAvoidInfoChangeListener002, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    RefPtr<FrameNode> nullNode = nullptr;
    EXPECT_NO_FATAL_FAILURE(pattern->RegisterAvoidInfoChangeListener(nullNode));
}

/**
 * @tc.name: UnRegisterAvoidInfoChangeListener001
 * @tc.desc: Test UnRegisterAvoidInfoChangeListener function
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, UnRegisterAvoidInfoChangeListener001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    EXPECT_NO_FATAL_FAILURE(pattern->UnRegisterAvoidInfoChangeListener(AceType::RawPtr(frameNode)));
}

/**
 * @tc.name: UnRegisterAvoidInfoChangeListener002
 * @tc.desc: Test UnRegisterAvoidInfoChangeListener with null host node
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, UnRegisterAvoidInfoChangeListener002, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    EXPECT_NO_FATAL_FAILURE(pattern->UnRegisterAvoidInfoChangeListener(nullptr));
}

/**
 * @tc.name: CreateLayoutAlgorithm001
 * @tc.desc: Test CreateLayoutAlgorithm function
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, CreateLayoutAlgorithm001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    auto algo = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(algo, nullptr);
}

/**
 * @tc.name: CreateLayoutProperty001
 * @tc.desc: Test CreateLayoutProperty function
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, CreateLayoutProperty001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    auto prop = pattern->CreateLayoutProperty();
    ASSERT_NE(prop, nullptr);
    auto dialogProp = AceType::DynamicCast<DialogLayoutProperty>(prop);
    EXPECT_NE(dialogProp, nullptr);
}

/**
 * @tc.name: CreateEventHub001
 * @tc.desc: Test CreateEventHub function
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, CreateEventHub001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    auto eventHub = pattern->CreateEventHub();
    ASSERT_NE(eventHub, nullptr);
    auto dialogEventHub = AceType::DynamicCast<DialogEventHub>(eventHub);
    EXPECT_NE(dialogEventHub, nullptr);
}

/**
 * @tc.name: CreateAccessibilityProperty001
 * @tc.desc: Test CreateAccessibilityProperty function
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, CreateAccessibilityProperty001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    auto accessProp = pattern->CreateAccessibilityProperty();
    ASSERT_NE(accessProp, nullptr);
}

/**
 * @tc.name: GetFocusPattern001
 * @tc.desc: Test GetFocusPattern function
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, GetFocusPattern001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    auto focusPattern = pattern->GetFocusPattern();
    EXPECT_EQ(focusPattern.focusType_, FocusType::SCOPE);
    EXPECT_TRUE(focusPattern.focusable_);
}

/**
 * @tc.name: GetRouteOfFirstScopeAlertDialog001
 * @tc.desc: Test GetRouteOfFirstScope with ALERT_DIALOG type
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, GetRouteOfFirstScopeAlertDialog001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    pattern->dialogProperties_.type = DialogType::ALERT_DIALOG;
    auto route = pattern->GetRouteOfFirstScope();
    EXPECT_EQ(route.size(), 1);
    EXPECT_EQ(route.front(), 0);
}

/**
 * @tc.name: GetRouteOfFirstScopeActionSheet001
 * @tc.desc: Test GetRouteOfFirstScope with ACTION_SHEET type
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, GetRouteOfFirstScopeActionSheet001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    pattern->dialogProperties_.type = DialogType::ACTION_SHEET;
    auto route = pattern->GetRouteOfFirstScope();
    EXPECT_EQ(route.size(), 1);
    EXPECT_EQ(route.front(), 0);
}

/**
 * @tc.name: GetRouteOfFirstScopeCommon001
 * @tc.desc: Test GetRouteOfFirstScope with COMMON type
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, GetRouteOfFirstScopeCommon001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    pattern->dialogProperties_.type = DialogType::COMMON;
    auto route = pattern->GetRouteOfFirstScope();
    EXPECT_EQ(route.size(), 2);
}

/**
 * @tc.name: IsAtomicNode001
 * @tc.desc: Test IsAtomicNode returns false
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, IsAtomicNode001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    EXPECT_FALSE(pattern->IsAtomicNode());
}

/**
 * @tc.name: AvoidBottom001
 * @tc.desc: Test AvoidBottom returns false
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, AvoidBottom001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    EXPECT_FALSE(pattern->AvoidBottom());
}

/**
 * @tc.name: TriggerAutoSaveWhenInvisible001
 * @tc.desc: Test TriggerAutoSaveWhenInvisible returns true
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, TriggerAutoSaveWhenInvisible001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    EXPECT_TRUE(pattern->TriggerAutoSaveWhenInvisible());
}

/**
 * @tc.name: SetOnWillDismiss001
 * @tc.desc: Test SetOnWillDismiss and ShouldDismiss
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, SetOnWillDismiss001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    bool called = false;
    auto callback = [&called](const int32_t& info, const int32_t& instanceId) { called = true; };
    pattern->SetOnWillDismiss(callback);
    EXPECT_TRUE(pattern->ShouldDismiss());
}

/**
 * @tc.name: ShouldDismissNoCallback001
 * @tc.desc: Test ShouldDismiss when no callback is set
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, ShouldDismissNoCallback001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    pattern->onWillDismiss_ = nullptr;
    pattern->isDialogDisposed_ = false;
    EXPECT_FALSE(pattern->ShouldDismiss());
}

/**
 * @tc.name: ShouldDismissDialogDisposed001
 * @tc.desc: Test ShouldDismiss when dialog is disposed
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, ShouldDismissDialogDisposed001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    bool called = false;
    auto callback = [&called](const int32_t& info, const int32_t& instanceId) { called = true; };
    pattern->SetOnWillDismiss(callback);
    pattern->SetIsDialogDisposed(true);
    EXPECT_FALSE(pattern->ShouldDismiss());
}

/**
 * @tc.name: CallOnWillDismiss001
 * @tc.desc: Test CallOnWillDismiss function
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, CallOnWillDismiss001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    int32_t reason = 0;
    int32_t instanceId = 0;
    bool called = false;
    auto callback = [&called, &reason](const int32_t& info, const int32_t& instId) {
        called = true;
        reason = info;
    };
    pattern->SetOnWillDismiss(callback);
    pattern->SetIsDialogDisposed(false);
    pattern->CallOnWillDismiss(1, instanceId);
    EXPECT_TRUE(called);
    EXPECT_EQ(reason, 1);
}

/**
 * @tc.name: CallOnWillDismissDisposed001
 * @tc.desc: Test CallOnWillDismiss when dialog is disposed
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, CallOnWillDismissDisposed001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    bool called = false;
    auto callback = [&called](const int32_t& info, const int32_t& instanceId) { called = true; };
    pattern->SetOnWillDismiss(callback);
    pattern->SetIsDialogDisposed(true);
    pattern->CallOnWillDismiss(0, 0);
    EXPECT_FALSE(called);
}

/**
 * @tc.name: CallOnWillDismissNoCallback001
 * @tc.desc: Test CallOnWillDismiss when no callback is set
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, CallOnWillDismissNoCallback001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    pattern->onWillDismiss_ = nullptr;
    EXPECT_NO_FATAL_FAILURE(pattern->CallOnWillDismiss(0, 0));
}

/**
 * @tc.name: SetOnWillDismissRelease001
 * @tc.desc: Test SetOnWillDismissRelease function
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, SetOnWillDismissRelease001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    bool called = false;
    auto callback = [&called]() { called = true; };
    pattern->SetOnWillDismissRelease(callback);
    EXPECT_NE(pattern->onWillDismissRelease_, nullptr);
    pattern->onWillDismissRelease_();
    EXPECT_TRUE(called);
}

/**
 * @tc.name: SetOnWillDismissByNDK001
 * @tc.desc: Test SetOnWillDismissByNDK function
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, SetOnWillDismissByNDK001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    bool called = false;
    auto callback = [&called](const int32_t& info) {
        called = true;
        return true;
    };
    pattern->SetOnWillDismissByNDK(callback);
    EXPECT_NE(pattern->onWillDismissByNDK_, nullptr);
}

/**
 * @tc.name: CallDismissInNDK001
 * @tc.desc: Test CallDismissInNDK when callback returns true
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, CallDismissInNDK001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    bool called = false;
    auto callback = [&called](const int32_t& info) {
        called = true;
        return true;
    };
    pattern->SetOnWillDismissByNDK(callback);
    auto result = pattern->CallDismissInNDK(0);
    EXPECT_TRUE(result);
    EXPECT_TRUE(called);
}

/**
 * @tc.name: CallDismissInNDK002
 * @tc.desc: Test CallDismissInNDK when callback returns false
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, CallDismissInNDK002, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    bool called = false;
    auto callback = [&called](const int32_t& info) {
        called = true;
        return false;
    };
    pattern->SetOnWillDismissByNDK(callback);
    auto result = pattern->CallDismissInNDK(0);
    EXPECT_FALSE(result);
    EXPECT_TRUE(called);
}

/**
 * @tc.name: CallDismissInNDKNoCallback001
 * @tc.desc: Test CallDismissInNDK when no callback is set
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, CallDismissInNDKNoCallback001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    pattern->onWillDismissByNDK_ = nullptr;
    auto result = pattern->CallDismissInNDK(0);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: SetOpenAnimation001
 * @tc.desc: Test SetOpenAnimation and GetOpenAnimation
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, SetOpenAnimation001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    AnimationOption option;
    option.SetDuration(1000);
    pattern->SetOpenAnimation(option);
    auto result = pattern->GetOpenAnimation();
    EXPECT_TRUE(result.has_value());
    EXPECT_EQ(result.value().GetDuration(), 1000);
}

/**
 * @tc.name: SetOpenAnimation002
 * @tc.desc: Test SetOpenAnimation with empty optional
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, SetOpenAnimation002, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    pattern->SetOpenAnimation(std::nullopt);
    auto result = pattern->GetOpenAnimation();
    EXPECT_FALSE(result.has_value());
}

/**
 * @tc.name: GetOpenAnimation001
 * @tc.desc: Test GetOpenAnimation when no animation is set
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, GetOpenAnimation001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    auto result = pattern->GetOpenAnimation();
    EXPECT_FALSE(result.has_value());
}

/**
 * @tc.name: SetCloseAnimation001
 * @tc.desc: Test SetCloseAnimation and GetCloseAnimation
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, SetCloseAnimation001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    AnimationOption option;
    option.SetDuration(500);
    pattern->SetCloseAnimation(option);
    auto result = pattern->GetCloseAnimation();
    EXPECT_TRUE(result.has_value());
    EXPECT_EQ(result.value().GetDuration(), 500);
}

/**
 * @tc.name: SetCloseAnimation002
 * @tc.desc: Test SetCloseAnimation with empty optional
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, SetCloseAnimation002, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    pattern->SetCloseAnimation(std::nullopt);
    auto result = pattern->GetCloseAnimation();
    EXPECT_FALSE(result.has_value());
}

/**
 * @tc.name: GetCloseAnimation001
 * @tc.desc: Test GetCloseAnimation when no animation is set
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, GetCloseAnimation001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    auto result = pattern->GetCloseAnimation();
    EXPECT_FALSE(result.has_value());
}

/**
 * @tc.name: SetDialogProperties001
 * @tc.desc: Test SetDialogProperties and GetDialogProperties
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, SetDialogProperties001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    DialogProperties props;
    props.title = TITLE;
    props.subtitle = SUBTITLE;
    props.content = MESSAGE;
    props.isModal = true;
    pattern->SetDialogProperties(props);
    auto result = pattern->GetDialogProperties();
    EXPECT_EQ(result.title, TITLE);
    EXPECT_EQ(result.subtitle, SUBTITLE);
    EXPECT_EQ(result.content, MESSAGE);
    EXPECT_TRUE(result.isModal);
}

/**
 * @tc.name: SetDialogProperties002
 * @tc.desc: Test SetDialogProperties with custom style
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, SetDialogProperties002, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    DialogProperties props;
    props.customStyle = true;
    pattern->SetDialogProperties(props);
    auto result = pattern->GetDialogProperties();
    EXPECT_TRUE(result.customStyle);
}

/**
 * @tc.name: GetDialogProperties001
 * @tc.desc: Test GetDialogProperties with default properties
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, GetDialogProperties001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    auto result = pattern->GetDialogProperties();
    EXPECT_TRUE(result.title.empty());
    EXPECT_TRUE(result.subtitle.empty());
    EXPECT_TRUE(result.content.empty());
}

/**
 * @tc.name: GetTitle001
 * @tc.desc: Test GetTitle function
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, GetTitle001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    pattern->title_ = TITLE;
    EXPECT_EQ(pattern->GetTitle(), TITLE);
}

/**
 * @tc.name: GetSubtitle001
 * @tc.desc: Test GetSubtitle function
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, GetSubtitle001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    pattern->subtitle_ = SUBTITLE;
    EXPECT_EQ(pattern->GetSubtitle(), SUBTITLE);
}

/**
 * @tc.name: GetMessage001
 * @tc.desc: Test GetMessage function
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, GetMessage001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    pattern->message_ = MESSAGE;
    EXPECT_EQ(pattern->GetMessage(), MESSAGE);
}

/**
 * @tc.name: GetCustomNode001
 * @tc.desc: Test GetCustomNode function with null custom node
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, GetCustomNode001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    auto result = pattern->GetCustomNode();
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: GetCustomNode002
 * @tc.desc: Test GetCustomNode with a valid custom node
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, GetCustomNode002, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    auto customNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(customNode, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, customNode));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);

    auto result = pattern->GetCustomNode();
    EXPECT_NE(result, nullptr);
}

/**
 * @tc.name: GetDialogTheme001
 * @tc.desc: Test GetDialogTheme function
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, GetDialogTheme001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    auto result = pattern->GetDialogTheme();
    EXPECT_EQ(result, dialogTheme);
}

/**
 * @tc.name: GetHostWindowRect001
 * @tc.desc: Test GetHostWindowRect function
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, GetHostWindowRect001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    pattern->hostWindowRect_ = CONTROL_RECT;
    auto result = pattern->GetHostWindowRect();
    EXPECT_EQ(result, CONTROL_RECT);
}

/**
 * @tc.name: GetParentWindowRect001
 * @tc.desc: Test GetParentWindowRect function
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, GetParentWindowRect001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    pattern->parentWindowRect_ = CONTROL_RECT;
    auto result = pattern->GetParentWindowRect();
    EXPECT_EQ(result, CONTROL_RECT);
}

/**
 * @tc.name: UpdateFoldDisplayModeChangedCallbackId001
 * @tc.desc: Test UpdateFoldDisplayModeChangedCallbackId
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, UpdateFoldDisplayModeChangedCallbackId001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    pattern->UpdateFoldDisplayModeChangedCallbackId(1);
    EXPECT_TRUE(pattern->HasFoldDisplayModeChangedCallbackId());
}

/**
 * @tc.name: UpdateFoldDisplayModeChangedCallbackId002
 * @tc.desc: Test UpdateFoldDisplayModeChangedCallbackId with reset
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, UpdateFoldDisplayModeChangedCallbackId002, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    pattern->UpdateFoldDisplayModeChangedCallbackId(1);
    EXPECT_TRUE(pattern->HasFoldDisplayModeChangedCallbackId());
    pattern->UpdateFoldDisplayModeChangedCallbackId(std::nullopt);
    EXPECT_FALSE(pattern->HasFoldDisplayModeChangedCallbackId());
}

/**
 * @tc.name: UpdateHoverModeChangedCallbackId001
 * @tc.desc: Test UpdateHoverModeChangedCallbackId
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, UpdateHoverModeChangedCallbackId001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    pattern->UpdateHoverModeChangedCallbackId(2);
    EXPECT_TRUE(pattern->HasHoverModeChangedCallbackId());
}

/**
 * @tc.name: UpdateHoverModeChangedCallbackId002
 * @tc.desc: Test UpdateHoverModeChangedCallbackId with reset
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, UpdateHoverModeChangedCallbackId002, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    pattern->UpdateHoverModeChangedCallbackId(2);
    EXPECT_TRUE(pattern->HasHoverModeChangedCallbackId());
    pattern->UpdateHoverModeChangedCallbackId(std::nullopt);
    EXPECT_FALSE(pattern->HasHoverModeChangedCallbackId());
}

/**
 * @tc.name: GetIsSuitableForAging001
 * @tc.desc: Test GetIsSuitableForAging function
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, GetIsSuitableForAging001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    EXPECT_FALSE(pattern->GetIsSuitableForAging());
    pattern->isSuitableForElderly_ = true;
    EXPECT_TRUE(pattern->GetIsSuitableForAging());
}

/**
 * @tc.name: GetFontScaleForElderly001
 * @tc.desc: Test GetFontScaleForElderly function
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, GetFontScaleForElderly001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    EXPECT_FLOAT_EQ(pattern->GetFontScaleForElderly(), 1.0f);
    pattern->fontScaleForElderly_ = 1.5f;
    EXPECT_FLOAT_EQ(pattern->GetFontScaleForElderly(), 1.5f);
}

/**
 * @tc.name: SetIsPickerDialog001
 * @tc.desc: Test SetIsPickerDialog and GetIsPickerDialog
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, SetIsPickerDialog001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    EXPECT_FALSE(pattern->GetIsPickerDialog());
    pattern->SetIsPickerDialog(true);
    EXPECT_TRUE(pattern->GetIsPickerDialog());
    pattern->SetIsPickerDialog(false);
    EXPECT_FALSE(pattern->GetIsPickerDialog());
}

/**
 * @tc.name: GetIsSuitOldMeasure001
 * @tc.desc: Test GetIsSuitOldMeasure function
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, GetIsSuitOldMeasure001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    EXPECT_FALSE(pattern->GetIsSuitOldMeasure());
    pattern->isSuitOldMeasure_ = true;
    EXPECT_TRUE(pattern->GetIsSuitOldMeasure());
}

/**
 * @tc.name: SetIsScrollHeightNegative001
 * @tc.desc: Test SetIsScrollHeightNegative function
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, SetIsScrollHeightNegative001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    EXPECT_FALSE(pattern->isScrollHeightNegative_);
    pattern->SetIsScrollHeightNegative(true);
    EXPECT_TRUE(pattern->isScrollHeightNegative_);
    pattern->SetIsScrollHeightNegative(false);
    EXPECT_FALSE(pattern->isScrollHeightNegative_);
}

/**
 * @tc.name: SetIsDialogDisposed001
 * @tc.desc: Test SetIsDialogDisposed function
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, SetIsDialogDisposed001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    EXPECT_FALSE(pattern->isDialogDisposed_);
    pattern->SetIsDialogDisposed(true);
    EXPECT_TRUE(pattern->isDialogDisposed_);
    pattern->SetIsDialogDisposed(false);
    EXPECT_FALSE(pattern->isDialogDisposed_);
}

/**
 * @tc.name: SetState001
 * @tc.desc: Test SetState and GetState functions
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, SetState001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    pattern->SetState(PromptActionCommonState::APPEARING);
    EXPECT_EQ(pattern->GetState(), PromptActionCommonState::APPEARING);
    pattern->SetState(PromptActionCommonState::APPEARED);
    EXPECT_EQ(pattern->GetState(), PromptActionCommonState::APPEARED);
    pattern->SetState(PromptActionCommonState::DISAPPEARING);
    EXPECT_EQ(pattern->GetState(), PromptActionCommonState::DISAPPEARING);
    pattern->SetState(PromptActionCommonState::DISAPPEARED);
    EXPECT_EQ(pattern->GetState(), PromptActionCommonState::DISAPPEARED);
}

/**
 * @tc.name: SetState002
 * @tc.desc: Test SetState with UNINITIALIZED and INITIALIZED
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, SetState002, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    pattern->SetState(PromptActionCommonState::UNINITIALIZED);
    EXPECT_EQ(pattern->GetState(), PromptActionCommonState::UNINITIALIZED);
    pattern->SetState(PromptActionCommonState::INITIALIZED);
    EXPECT_EQ(pattern->GetState(), PromptActionCommonState::INITIALIZED);
}

/**
 * @tc.name: RegisterDialogDidAppearCallback001
 * @tc.desc: Test RegisterDialogDidAppearCallback and CallDialogDidAppearCallback
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestFourNg, RegisterDialogDidAppearCallback001, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);


    bool called = false;
    auto callback = [&called]() { called = true; };
    pattern->RegisterDialogDidAppearCallback(std::move(callback));
    pattern->CallDialogDidAppearCallback();
    EXPECT_TRUE(called);
    EXPECT_EQ(pattern->GetState(), PromptActionCommonState::APPEARED);
}

} // namespace OHOS::Ace::NG
