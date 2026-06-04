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
#include "test/mock/frameworks/base/subwindow/mock_subwindow.h"
#include "test/mock/adapter/ohos/osal/mock_system_properties.h"
#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "core/accessibility/accessibility_manager_ng.h"
#include "base/log/dump_log.h"
#include "base/subwindow/subwindow_manager.h"
#include "core/common/recorder/event_recorder.h"
#include "core/components/dialog/dialog_properties.h"
#include "core/components/select/select_theme.h"
#include "core/components/button/button_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/action_sheet/action_sheet_model_ng.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/dialog/alert_dialog_model_ng.h"
#include "core/components_ng/pattern/dialog/custom_dialog_controller_model_ng.h"
#include "core/components_ng/pattern/dialog/dialog_event_hub.h"
#include "core/components_ng/pattern/dialog/dialog_layout_algorithm.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_view.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/navrouter/navdestination_group_node.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "core/components_ng/pattern/overlay/dialog_manager.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "test/unittest/core/event/frame_node_on_tree.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/list/list_item_pattern.h"
#include "core/common/ace_engine.h"
#include "core/common/resource/resource_object.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/blur_style_option.h"
#include "core/components/common/properties/shadow.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/property/border_property.h"
#include "core/components_ng/render/render_context.h"
#include "core/components_ng/pattern/stage/stage_manager.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "interfaces/inner_api/ace_kit/include/ui/properties/dirty_flag.h"
#include "core/components/common/properties/ui_material.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const double DIMENSIONVALUE = 1.0;
const std::string TITLE = "title";
const std::string SUBTITLE = "subtitle";
const std::string MESSAGE = "hello world";
const CalcDimension WIDTHDIMENSION = CalcDimension(DIMENSIONVALUE);
const CalcDimension HEIGHTDIMENSION = CalcDimension(DIMENSIONVALUE);
const NG::BorderWidthProperty BORDERWIDTH = { .leftDimen = Dimension(DIMENSIONVALUE) };
const BorderColorProperty BORDERCOLOR = { .bottomColor = Color::WHITE };
const NG::BorderRadiusProperty BORDERRADIUS = BorderRadiusProperty(Dimension(DIMENSIONVALUE));
const RectF CONTROL_RECT = RectF(0.0f, 0.0f, 100.0f, 100.0f);
} // namespace

class DialogPatternTestThreeNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();

private:
    RefPtr<FrameNode> CreateActionSheetList(RefPtr<DialogPattern> pattern);
    RefPtr<FrameNode> CreateButton(const std::string& text);
    RefPtr<FrameNode> CreateMenu(const std::vector<ButtonInfo>& buttons);

    DialogProperties actionSheetProp_ = {
        .type = DialogType::ACTION_SHEET, .title = TITLE,
        .subtitle = SUBTITLE, .content = MESSAGE,
        .isModal = false, .isShowInSubWindow = true,
        .backgroundColor = Color::BLUE, .height = 50,
        .isMenu = false, .sheetsInfo =  {{.title = "a"}, {.title = "b"}},
        .buttonDirection = DialogButtonDirection::HORIZONTAL,
        .buttons = {{ .text = "main button", .bgColor = Color::BLACK }},
    };
};

void DialogPatternTestThreeNg::SetUpTestCase()
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
            } else {
                return nullptr;
            }
        });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void DialogPatternTestThreeNg::TearDownTestCase()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

RefPtr<FrameNode> DialogPatternTestThreeNg::CreateActionSheetList(RefPtr<DialogPattern> pattern)
{
    auto list = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ListPattern>());
    for ([[maybe_unused]] auto&& item : pattern->dialogProperties_.sheetsInfo) {
        auto itemNode = FrameNode::CreateFrameNode(V2::LIST_ITEM_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(),
            AceType::MakeRefPtr<ListItemPattern>(nullptr, V2::ListItemStyle::NONE));
        auto itemRow = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            AceType::MakeRefPtr<LinearLayoutPattern>(false));
        itemRow->MountToParent(itemNode);
        list->AddChild(itemNode);
    }
    return list;
}

RefPtr<FrameNode> DialogPatternTestThreeNg::CreateButton(const std::string& text)
{
    auto buttonRow = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    auto buttonNode = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    auto textNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    textNode->GetOrCreateFocusHub()->SetFocusable(true);
    auto textProps = textNode->GetLayoutProperty<TextLayoutProperty>();
    textProps->UpdateContent(text);
    textNode->MountToParent(buttonNode);
    textNode->MarkModifyDone();
    buttonNode->MountToParent(buttonRow);
    return buttonRow;
}

RefPtr<FrameNode> DialogPatternTestThreeNg::CreateMenu(const std::vector<ButtonInfo>& buttons)
{
    auto menu = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    for (size_t i = 0; i < buttons.size(); ++i) {
        auto buttonRow = CreateButton(buttons[i].text);
        buttonRow->MountToParent(menu);
    }
    auto buttonRow = CreateButton("");
    buttonRow->MountToParent(menu);
    return menu;
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap_WithDistortionEnabled001
 * @tc.desc: Test OnDirtyLayoutWrapperSwap with distortion enabled
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestThreeNg, OnDirtyLayoutWrapperSwap_WithDistortionEnabled001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create dialog node and set up material properties for distortion
     * @tc.expected: The dialog node created successfully
     */
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create content node and mount to dialog
     * @tc.expected: Content node mounted successfully
     */
    auto contentNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(contentNode, nullptr);
    contentNode->MountToParent(frameNode);

    /**
     * @tc.steps: step3. Set distortion mode to ENABLED
     * @tc.expected: Distortion mode set successfully
     */
    pattern->dialogProperties_.distortionMode = DistortionMode::DISTORTION_ENABLED;
    pattern->dialogProperties_.systemMaterial = AceType::MakeRefPtr<UiMaterial>();

    /**
     * @tc.steps: step4. Create LayoutWrapper and DirtySwapConfig
     * @tc.expected: Wrapper and config created successfully
     */
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, layoutProperty);
    ASSERT_NE(layoutWrapper, nullptr);

    DirtySwapConfig config;
    config.skipMeasure = true;
    config.skipLayout = true;

    /**
     * @tc.steps: step5. Call OnDirtyLayoutWrapperSwap with distortion enabled
     * @tc.expected: Function returns true and distortion animation is triggered
     */
    auto result = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_TRUE(result);
    EXPECT_TRUE(pattern->isDistortAnimationExecuting_.has_value());
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap_WithDistortionAnimationExecuting001
 * @tc.desc: Test OnDirtyLayoutWrapperSwap when distortion animation is already executing
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestThreeNg, OnDirtyLayoutWrapperSwap_WithDistortionAnimationExecuting001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create dialog node and set up material properties
     * @tc.expected: The dialog node created successfully
     */
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create content node and mount to dialog
     * @tc.expected: Content node mounted successfully
     */
    auto contentNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(contentNode, nullptr);
    contentNode->MountToParent(frameNode);

    /**
     * @tc.steps: step3. Set distortion mode to ENABLED and mark animation as executing
     * @tc.expected: Properties set successfully
     */
    pattern->dialogProperties_.distortionMode = DistortionMode::DISTORTION_ENABLED;
    pattern->dialogProperties_.systemMaterial = AceType::MakeRefPtr<UiMaterial>();
    pattern->isDistortAnimationExecuting_ = true;

    /**
     * @tc.steps: step4. Create LayoutWrapper and DirtySwapConfig
     * @tc.expected: Wrapper and config created successfully
     */
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, layoutProperty);
    ASSERT_NE(layoutWrapper, nullptr);

    DirtySwapConfig config;
    config.skipMeasure = true;
    config.skipLayout = true;

    /**
     * @tc.steps: step5. Call OnDirtyLayoutWrapperSwap with distortion animation executing
     * @tc.expected: Function returns false because animation is still executing
     */
    auto result = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap_WithDistortionAutoMode001
 * @tc.desc: Test OnDirtyLayoutWrapperSwap with distortion AUTO mode and IMMERSIVE material
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestThreeNg, OnDirtyLayoutWrapperSwap_WithDistortionAutoMode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create dialog node and set up material properties
     * @tc.expected: The dialog node created successfully
     */
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create content node and mount to dialog
     * @tc.expected: Content node mounted successfully
     */
    auto contentNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(contentNode, nullptr);
    contentNode->MountToParent(frameNode);

    /**
     * @tc.steps: step3. Set distortion mode to AUTO with IMMERSIVE material and EXQUISITE level
     * @tc.expected: Properties set successfully
     */
    pattern->dialogProperties_.distortionMode = DistortionMode::DISTORTION_AUTO;
    pattern->dialogProperties_.systemMaterial = AceType::MakeRefPtr<UiMaterial>();
    auto isUiMaterialLevel = g_uiMaterialLevel;
    g_uiMaterialLevel = UiMaterialLevel::EXQUISITE;

    /**
     * @tc.steps: step4. Create LayoutWrapper and DirtySwapConfig
     * @tc.expected: Wrapper and config created successfully
     */
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, layoutProperty);
    ASSERT_NE(layoutWrapper, nullptr);

    DirtySwapConfig config;
    config.skipMeasure = true;
    config.skipLayout = true;

    /**
     * @tc.steps: step5. Call OnDirtyLayoutWrapperSwap with AUTO distortion mode
     * @tc.expected: Function returns true and distortion is triggered for IMMERSIVE material
     */
    auto result = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_TRUE(result);

    g_uiMaterialLevel = isUiMaterialLevel;
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap_WithEdgeLightEnabled001
 * @tc.desc: Test OnDirtyLayoutWrapperSwap with edge light enabled
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestThreeNg, OnDirtyLayoutWrapperSwap_WithEdgeLightEnabled001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create dialog node and set up material properties for edge light
     * @tc.expected: The dialog node created successfully
     */
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create content node and mount to dialog
     * @tc.expected: Content node mounted successfully
     */
    auto contentNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(contentNode, nullptr);
    contentNode->MountToParent(frameNode);

    /**
     * @tc.steps: step3. Set edge light mode to ENABLED
     * @tc.expected: Edge light mode set successfully
     */
    pattern->dialogProperties_.edgeLightMode = EdgeLightMode::EDGELIGHT_ENABLED;
    pattern->dialogProperties_.systemMaterial = AceType::MakeRefPtr<UiMaterial>();

    /**
     * @tc.steps: step4. Create LayoutWrapper and DirtySwapConfig
     * @tc.expected: Wrapper and config created successfully
     */
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, layoutProperty);
    ASSERT_NE(layoutWrapper, nullptr);

    DirtySwapConfig config;
    config.skipMeasure = true;
    config.skipLayout = true;

    /**
     * @tc.steps: step5. Call OnDirtyLayoutWrapperSwap with edge light enabled
     * @tc.expected: Function returns true and edge light animation is triggered
     */
    auto result = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap_WithEdgeLightAutoMode001
 * @tc.desc: Test OnDirtyLayoutWrapperSwap with edge light AUTO mode and IMMERSIVE material
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestThreeNg, OnDirtyLayoutWrapperSwap_WithEdgeLightAutoMode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create dialog node and set up material properties
     * @tc.expected: The dialog node created successfully
     */
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create content node and mount to dialog
     * @tc.expected: Content node mounted successfully
     */
    auto contentNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(contentNode, nullptr);
    contentNode->MountToParent(frameNode);

    /**
     * @tc.steps: step3. Set edge light mode to AUTO with IMMERSIVE material and EXQUISITE level
     * @tc.expected: Properties set successfully
     */
    pattern->dialogProperties_.edgeLightMode = EdgeLightMode::EDGELIGHT_AUTO;
    pattern->dialogProperties_.systemMaterial = AceType::MakeRefPtr<UiMaterial>();
    auto isUiMaterialLevel = g_uiMaterialLevel;
    g_uiMaterialLevel = UiMaterialLevel::EXQUISITE;

    /**
     * @tc.steps: step4. Create LayoutWrapper and DirtySwapConfig
     * @tc.expected: Wrapper and config created successfully
     */
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, layoutProperty);
    ASSERT_NE(layoutWrapper, nullptr);

    DirtySwapConfig config;
    config.skipMeasure = true;
    config.skipLayout = true;

    /**
     * @tc.steps: step5. Call OnDirtyLayoutWrapperSwap with AUTO edge light mode
     * @tc.expected: Function returns true and edge light is triggered for IMMERSIVE material
     */
    auto result = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_TRUE(result);

    g_uiMaterialLevel = isUiMaterialLevel;
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap_WithBothDistortionAndEdgeLight001
 * @tc.desc: Test OnDirtyLayoutWrapperSwap with both distortion and edge light enabled
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestThreeNg, OnDirtyLayoutWrapperSwap_WithBothDistortionAndEdgeLight001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create dialog node and set up material properties
     * @tc.expected: The dialog node created successfully
     */
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create content node and mount to dialog
     * @tc.expected: Content node mounted successfully
     */
    auto contentNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(contentNode, nullptr);
    contentNode->MountToParent(frameNode);

    /**
     * @tc.steps: step3. Enable both distortion and edge light
     * @tc.expected: Properties set successfully
     */
    pattern->dialogProperties_.distortionMode = DistortionMode::DISTORTION_ENABLED;
    pattern->dialogProperties_.edgeLightMode = EdgeLightMode::EDGELIGHT_ENABLED;
    pattern->dialogProperties_.systemMaterial = AceType::MakeRefPtr<UiMaterial>();

    /**
     * @tc.steps: step4. Create LayoutWrapper and DirtySwapConfig
     * @tc.expected: Wrapper and config created successfully
     */
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, layoutProperty);
    ASSERT_NE(layoutWrapper, nullptr);

    DirtySwapConfig config;
    config.skipMeasure = true;
    config.skipLayout = true;

    /**
     * @tc.steps: step5. Call OnDirtyLayoutWrapperSwap with both features enabled
     * @tc.expected: Function returns true and both animations are triggered
     */
    auto result = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: PlayDistortion_WithValidDialogNode001
 * @tc.desc: Test PlayDistortion with valid dialog node structure
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestThreeNg, PlayDistortion_WithValidDialogNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create dialog node with proper structure
     * @tc.expected: The dialog node created successfully
     */
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create content column node and mount to dialog
     * @tc.expected: Content column node mounted successfully
     */
    auto contentColumn = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(contentColumn, nullptr);
    contentColumn->MountToParent(frameNode);

    /**
     * @tc.steps: step3. Create text node as child of content column for render context
     * @tc.expected: Text node mounted successfully
     */
    auto textNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textNode, nullptr);
    textNode->MountToParent(contentColumn);

    /**
     * @tc.steps: step4. Set dialog properties to enable distortion
     * @tc.expected: Properties set successfully
     */
    pattern->dialogProperties_.systemMaterial = AceType::MakeRefPtr<UiMaterial>();

    /**
     * @tc.steps: step5. Call PlayDistortion
     * @tc.expected: No crash, distortion animation is applied
     */
    pattern->PlayDistortion();
    EXPECT_TRUE(pattern->isDistortAnimationExecuting_);
}

/**
 * @tc.name: PlayDistortion_WithMultipleChildNodes001
 * @tc.desc: Test PlayDistortion with multiple child nodes in content column
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternTestThreeNg, PlayDistortion_WithMultipleChildNodes001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create dialog node with proper structure
     * @tc.expected: The dialog node created successfully
     */
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create content column node and mount to dialog
     * @tc.expected: Content column node mounted successfully
     */
    auto contentColumn = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(contentColumn, nullptr);
    contentColumn->MountToParent(frameNode);

    /**
     * @tc.steps: step3. Create multiple child nodes
     * @tc.expected: All child nodes mounted successfully
     */
    auto textNode1 = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textNode1, nullptr);
    textNode1->MountToParent(contentColumn);

    auto textNode2 = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textNode2, nullptr);
    textNode2->MountToParent(contentColumn);

    /**
     * @tc.steps: step4. Set dialog properties
     * @tc.expected: Properties set successfully
     */
    pattern->dialogProperties_.systemMaterial = AceType::MakeRefPtr<UiMaterial>();

    /**
     * @tc.steps: step5. Call PlayDistortion
     * @tc.expected: No crash, distortion animation is applied to all child nodes
     */
    pattern->PlayDistortion();
    EXPECT_TRUE(pattern->isDistortAnimationExecuting_);
}

} // namespace OHOS::Ace::NG
