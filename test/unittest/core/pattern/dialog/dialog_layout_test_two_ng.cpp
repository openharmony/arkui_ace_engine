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
#include "ui/base/geometry/ng/size_t.h"

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
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/dialog/custom_dialog_controller_model_ng.h"
#include "core/components_ng/pattern/dialog/dialog_event_hub.h"
#include "core/components_ng/pattern/dialog/dialog_layout_algorithm.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_view.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/components_ng/pattern/overlay/dialog_manager.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/text/text_layout_algorithm.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const InspectorFilter filter;
const std::string SHEET_TITLE = "sheet item";
const std::string SHEET_TITLE_2 = "sheet item 2";
const std::string SHEET_TITLE_3 = "sheet item 3";
const std::string INTERNAL_SOURCE = "$r('app.media.icon')";
const std::string TITLE = "This is title";
const std::string MESSAGE = "Message";
const std::string DEFAULT_STR("2.0");
constexpr Dimension SCROLL_MIN_HEIGHT_SUITOLD = 100.0_vp;
const Dimension DIMENSION_RADIUS(10.0, DimensionUnit::PX);
const Dimension DIMENSION_WIDTH(2.0, DimensionUnit::PX);
constexpr float FIRST_ITEM_WIDTH = 100.0f;
constexpr float FIRST_ITEM_HEIGHT = 50.0f;
const SizeF FIRST_ITEM_SIZE(FIRST_ITEM_WIDTH, FIRST_ITEM_HEIGHT);
constexpr float DEFAULT_WIDTH = 600.0f;
constexpr float DEFAULT_HEIGHT = 1000.0f;
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

class DialogLayoutTwoTestNg : public testing::Test {
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

void DialogLayoutTwoTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}
void DialogLayoutTwoTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}
void DialogLayoutTwoTestNg::SetDialogTheme()
{
    auto themeManager = AceType::DynamicCast<MockThemeManager>(MockPipelineContext::GetCurrent()->GetThemeManager());
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<MockDialogTheme>()));
}

RefPtr<LayoutWrapperNode> CreatlayoutWrapperTwo()
{
    auto rowFrameNode = FrameNode::CreateFrameNode("test", 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();

    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());
    return layoutWrapper;
}

/**
 * @tc.name: DialogLayoutAlgorithmUpdateChildMaxSizeHeight
 * @tc.desc: Test DialogLayoutAlgorithm::UpdateChildMaxSizeHeight function
 * @tc.type: FUNC
 */
HWTEST_F(DialogLayoutTwoTestNg, DialogLayoutAlgorithmUpdateChildMaxSizeHeight, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create DialogLayoutAlgorithm instance.
     */
    DialogLayoutAlgorithm dialogLayoutAlgorithm;
    dialogLayoutAlgorithm.isHoverMode_ = false;
    dialogLayoutAlgorithm.gridCount_ = 1;
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->minPlatformVersion_ = 12;
    SizeT<float> maxSize = SizeT(1.0f, 1.0f);
    /**
     * @tc.steps: step2. test DialogLayoutAlgorithm functions.
     * @tc.expected: These properties are matched.
     */
    EXPECT_TRUE(Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN));
    EXPECT_FALSE(LessNotEqual(dialogLayoutAlgorithm.gridCount_, 0));
    dialogLayoutAlgorithm.ResizeDialogSubwindow(false, true, true);
    dialogLayoutAlgorithm.ResizeDialogSubwindow(true, false, true);
    dialogLayoutAlgorithm.ResizeDialogSubwindow(true, true, false);
    dialogLayoutAlgorithm.UpdateChildMaxSizeHeight(maxSize);
}


/**
 * @tc.name: DialogLayoutAlgorithm033
 * @tc.desc: Test CreateDialogNode with customNode
 * @tc.type: FUNC
 */
HWTEST_F(DialogLayoutTwoTestNg, DialogLayoutAlgorithm033, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a custom node and childLayoutWrapper
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    dialogTheme->text_align_title_ = 1;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(dialogTheme));
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
    propsCustom.title = "dialog title";
    propsCustom.subtitle = "dialog subtitle";
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
    dialogLayoutAlgorithm.ResizeDialogSubwindow(true, true, true);
}

/**
 * @tc.name: DialogViewTest001
 * @tc.desc: Test DialogView::CreateDialogNode function
 * @tc.type: FUNC
 */
HWTEST_F(DialogLayoutTwoTestNg, DialogViewTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a child node and childLayoutWrapper
     * @tc.expected: the child node created successfully.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    dialogTheme->alignDialog_ = 1;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(dialogTheme));
    RefPtr<FrameNode> childNode = FrameNode::CreateFrameNode(
        V2::ACTION_SHEET_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(nullptr, nullptr));
    ASSERT_NE(childNode, nullptr);
    auto childLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(childNode, childNode->GetGeometryNode(), childNode->GetLayoutProperty());
    ASSERT_NE(childLayoutWrapper, nullptr);

    double opacity = 1.0;
    auto appearOpacityTransition = AceType::MakeRefPtr<NG::ChainedOpacityEffect>(opacity);
    NG::ScaleOptions scale(1.0f, 1.0f, 1.0f, 0.5_pct, 0.5_pct);
    auto disappearScaleTransition = AceType::MakeRefPtr<NG::ChainedScaleEffect>(scale);
    auto dialogTransitionEffect =
        AceType::MakeRefPtr<NG::ChainedAsymmetricEffect>(appearOpacityTransition, disappearScaleTransition);
    auto maskTransitionEffect =
        AceType::MakeRefPtr<NG::ChainedAsymmetricEffect>(appearOpacityTransition, disappearScaleTransition);

    /**
     * @tc.steps: step3. create dialog with a dialog node and layoutWrapper.
     * @tc.expected: the dialog node created successfully.
     */
    DialogProperties param {
        .type = DialogType::ACTION_SHEET,
        .title = "dialog test",
        .content = "dialog content test",
        .width = 320,
        .height = 320,
        .backgroundColor = Color::TRANSPARENT,
        .alignment = DialogAlignment::DEFAULT,
        .hoverModeArea = HoverModeAreaType::TOP_SCREEN,
        .isSceneBoardDialog = true,
        .maskTransitionEffect = maskTransitionEffect,
        .dialogTransitionEffect = dialogTransitionEffect
    };
    NG::BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(DIMENSION_RADIUS);
    param.borderRadius = borderRadius;
    NG::BorderWidthProperty borderWidth;
    borderWidth.SetBorderWidth(DIMENSION_WIDTH);
    param.borderWidth = borderWidth;
    NG::BorderColorProperty borderColor;
    borderColor.SetColor(Color::BLACK);
    param.borderColor = borderColor;
    auto dialog = DialogView::CreateDialogNode(param, childNode);
    ASSERT_NE(dialog, nullptr);
}

/**
 * @tc.name: CustomDialogControllerModelTest002
 * @tc.desc: Test CustomDialogControllerModel::SetCloseDialogForNDK function
 * @tc.type: FUNC
 */
HWTEST_F(DialogLayoutTwoTestNg, CustomDialogControllerModelTest002, TestSize.Level1)
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
    RefPtr<FrameNode> dialogNode =
        FrameNode::CreateFrameNode(V2::DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(dialogNode, nullptr);

    /**
     * @tc.steps: step3. call CustomDialogControllerModel::SetCloseDialogForNDK function.
     * @tc.expected: the function called successfully.
     */
    CustomDialogControllerModelNG controllerModel;
    controllerModel.SetCloseDialogForNDK(dialogNode.rawPtr_);
}

/**
 * @tc.name: DialogLayoutAlgorithmGetEmbeddedDialogOffsetY
 * @tc.desc: Test DialogLayoutAlgorithm::GetEmbeddedDialogOffsetY function
 * @tc.type: FUNC
 */
HWTEST_F(DialogLayoutTwoTestNg, DialogLayoutAlgorithmGetEmbeddedDialogOffsetY, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create DialogLayoutAlgorithm instance.
     */
    auto customNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 100, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(customNode, nullptr);
    auto parentNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 99, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(parentNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameOffset(OffsetF(1.0f, 1.0f));
    RectF parentAdjust = RectT(10.0f, 10.0f, 10.0f, 10.0f);
    geometryNode->SetParentAdjust(parentAdjust);
    customNode->MountToParent(parentNode);
    parentNode->tag_ = V2::BUTTON_ETS_TAG;
    DialogLayoutAlgorithm dialogLayoutAlgorithm;
    /**
     * @tc.steps: step2. test DialogLayoutAlgorithm functions.
     * @tc.expected: These properties are matched.
     */
    EXPECT_EQ(dialogLayoutAlgorithm.GetEmbeddedDialogOffsetY(customNode), 0.0f);

    parentNode->tag_ = V2::PAGE_ETS_TAG;
    parentNode->geometryNode_ = geometryNode;
    EXPECT_EQ(dialogLayoutAlgorithm.GetEmbeddedDialogOffsetY(customNode), 1.0f);

    parentNode->tag_ = V2::NAVDESTINATION_VIEW_ETS_TAG;
    EXPECT_EQ(dialogLayoutAlgorithm.GetEmbeddedDialogOffsetY(customNode), 10.0f);
}

/**
 * @tc.name: DialogLayoutAlgorithmAdjustHeightForKeyboard001
 * @tc.desc: Test DialogLayoutAlgorithm::AdjustHeightForKeyboard function
 * @tc.type: FUNC
 */
HWTEST_F(DialogLayoutTwoTestNg, DialogLayoutAlgorithmAdjustHeightForKeyboard001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create DialogLayoutAlgorithm instance.
     */
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_SIXTEEN));
    DialogLayoutAlgorithm dialogLayoutAlgorithm;
    dialogLayoutAlgorithm.dialogChildSize_.SetHeight(1.0f);
    dialogLayoutAlgorithm.dialogChildSize_.SetWidth(1.0f);
    auto customNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 100, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(customNode, nullptr);
    auto childLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        customNode, customNode->GetGeometryNode(), customNode->GetLayoutProperty());
    ASSERT_NE(childLayoutWrapper, nullptr);
    DialogProperties param {
        .type = DialogType::ACTION_SHEET,
        .title = "dialog test",
        .content = "dialog content test",
        .sheetsInfo = sheetItems,
        .isShowInSubWindow = true,
        .offset = DimensionOffset(Dimension(10.0), Dimension(10.0)),
    };
    auto dialogWithCustom = DialogView::CreateDialogNode(param, customNode);
    ASSERT_NE(dialogWithCustom, nullptr);
    RefPtr<LayoutWrapper> child = customNode->CreateLayoutWrapper(true, true);
    ASSERT_NE(child, nullptr);
    auto layoutWrapperNode = dialogWithCustom->CreateLayoutWrapper(true, true);
    auto layoutWrapper = reinterpret_cast<LayoutWrapper*>(Referenced::RawPtr(layoutWrapperNode));
    ASSERT_NE(layoutWrapper, nullptr);
    /**
     * @tc.steps: step2. test DialogLayoutAlgorithm functions.
     * @tc.expected: These properties are matched.
     */
    dialogLayoutAlgorithm.AdjustHeightForKeyboard(layoutWrapper, nullptr);

    dialogLayoutAlgorithm.AdjustHeightForKeyboard(layoutWrapper, child);

    dialogLayoutAlgorithm.resizeFlag_ = true;
    dialogLayoutAlgorithm.AdjustHeightForKeyboard(layoutWrapper, child);

    dialogLayoutAlgorithm.keyboardAvoidMode_ = KeyboardAvoidMode::NONE;
    dialogLayoutAlgorithm.AdjustHeightForKeyboard(layoutWrapper, child);
}

/**
 * @tc.name: DialogLayoutAlgorithmAdjustHeightForKeyboard002
 * @tc.desc: Test DialogLayoutAlgorithm::AdjustHeightForKeyboard function
 * @tc.type: FUNC
 */
HWTEST_F(DialogLayoutTwoTestNg, DialogLayoutAlgorithmAdjustHeightForKeyboard002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create DialogLayoutAlgorithm instance.
     */
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_SIXTEEN));
    DialogLayoutAlgorithm dialogLayoutAlgorithm;
    dialogLayoutAlgorithm.dialogChildSize_.SetHeight(1.0f);
    dialogLayoutAlgorithm.dialogChildSize_.SetWidth(1.0f);
    auto customNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 100, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(customNode, nullptr);
    auto childLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        customNode, customNode->GetGeometryNode(), customNode->GetLayoutProperty());
    ASSERT_NE(childLayoutWrapper, nullptr);
    DialogProperties param {
        .type = DialogType::ACTION_SHEET,
        .title = "dialog test",
        .content = "dialog content test",
        .sheetsInfo = sheetItems,
        .isShowInSubWindow = true,
        .offset = DimensionOffset(Dimension(10.0), Dimension(10.0)),
    };
    auto dialogWithCustom = DialogView::CreateDialogNode(param, customNode);
    ASSERT_NE(dialogWithCustom, nullptr);
    RefPtr<LayoutWrapper> child = customNode->CreateLayoutWrapper(true, true);
    ASSERT_NE(child, nullptr);
    auto layoutWrapperNode = dialogWithCustom->CreateLayoutWrapper(true, true);
    auto layoutWrapper = reinterpret_cast<LayoutWrapper*>(Referenced::RawPtr(layoutWrapperNode));
    ASSERT_NE(layoutWrapper, nullptr);
    /**
     * @tc.steps: step2. test DialogLayoutAlgorithm functions.
     * @tc.expected: These properties are matched.
     */
    dialogLayoutAlgorithm.resizeFlag_ = true;
    dialogLayoutAlgorithm.keyboardAvoidMode_ = KeyboardAvoidMode::DEFAULT;
    auto childLayoutProperty = child->GetLayoutProperty();
    auto dialogProp = AceType::DynamicCast<DialogLayoutProperty>(layoutWrapper->GetLayoutProperty());
    auto renderContext = child->GetHostNode()->GetRenderContext();
    ASSERT_NE(childLayoutProperty, nullptr);
    ASSERT_NE(dialogProp, nullptr);
    ASSERT_NE(renderContext, nullptr);

    EXPECT_FALSE(dialogProp->GetHeight().has_value());
    EXPECT_FALSE(dialogProp->GetWidth().has_value());
    dialogLayoutAlgorithm.AdjustHeightForKeyboard(layoutWrapper, child);

    dialogProp->propHeight_ = CalcDimension(DEFAULT_STR);
    dialogProp->propWidth_ = CalcDimension(DEFAULT_STR);
    EXPECT_TRUE(dialogProp->GetHeight().has_value());
    EXPECT_TRUE(dialogProp->GetWidth().has_value());
    dialogLayoutAlgorithm.AdjustHeightForKeyboard(layoutWrapper, child);

    dialogLayoutAlgorithm.customSize_ = true;
    dialogLayoutAlgorithm.AdjustHeightForKeyboard(layoutWrapper, child);
}

/**
 * @tc.name: DialogLayoutAlgorithmIsEmbeddedDialog
 * @tc.desc: Test DialogLayoutAlgorithm::IsEmbeddedDialog function
 * @tc.type: FUNC
 */
HWTEST_F(DialogLayoutTwoTestNg, DialogLayoutAlgorithmIsEmbeddedDialog, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create DialogLayoutAlgorithm instance.
     */
    auto customNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 100, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(customNode, nullptr);
    auto parentNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 99, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(parentNode, nullptr);
    customNode->MountToParent(parentNode);
    DialogLayoutAlgorithm dialogLayoutAlgorithm;
    /**
     * @tc.steps: step2. test DialogLayoutAlgorithm functions.
     * @tc.expected: These properties are matched.
     */
    EXPECT_FALSE(dialogLayoutAlgorithm.IsEmbeddedDialog(customNode));

    parentNode->tag_ = V2::PAGE_ETS_TAG;
    EXPECT_TRUE(dialogLayoutAlgorithm.IsEmbeddedDialog(customNode));

    parentNode->tag_ = V2::NAVDESTINATION_VIEW_ETS_TAG;
    EXPECT_TRUE(dialogLayoutAlgorithm.IsEmbeddedDialog(customNode));
}

/**
 * @tc.name: DialogLayoutAlgorithmUpdateIsScrollHeightNegative
 * @tc.desc: Test DialogLayoutAlgorithm::UpdateIsScrollHeightNegative function
 * @tc.type: FUNC
 */
HWTEST_F(DialogLayoutTwoTestNg, DialogLayoutAlgorithmUpdateIsScrollHeightNegative, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create DialogLayoutAlgorithm instance.
     */
    DialogLayoutAlgorithm dialogLayoutAlgorithm;
    auto frameNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<LayoutWrapper> child = frameNode->CreateLayoutWrapper(true, true);
    ASSERT_NE(child, nullptr);
    auto layoutWrapperNode = frameNode->CreateLayoutWrapper(true, true);
    auto layoutWrapper = reinterpret_cast<LayoutWrapper*>(Referenced::RawPtr(layoutWrapperNode));
    ASSERT_NE(layoutWrapper, nullptr);
    /**
     * @tc.steps: step2. test DialogLayoutAlgorithm functions.
     * @tc.expected: These properties are matched.
     */
    dialogLayoutAlgorithm.UpdateIsScrollHeightNegative(layoutWrapper, SCROLL_MIN_HEIGHT_SUITOLD.ConvertToPx());
}

/**
 * @tc.name: DialogLayoutAlgorithmUpdateSafeArea
 * @tc.desc: Test DialogLayoutAlgorithm::UpdateSafeArea function
 * @tc.type: FUNC
 */
HWTEST_F(DialogLayoutTwoTestNg, DialogLayoutAlgorithmUpdateSafeArea, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create DialogLayoutAlgorithm instance.
     */
    DialogLayoutAlgorithm dialogLayoutAlgorithm;
    auto frameNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode, nullptr);
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto displayInfo = container->GetDisplayInfo();
    ASSERT_NE(displayInfo, nullptr);
    displayInfo->currentFoldCreaseRegion_.clear();
    auto foldCreaseRects = displayInfo->GetCurrentFoldCreaseRegion();
    auto customNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 100, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(customNode, nullptr);
    auto parentNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 99, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(parentNode, nullptr);
    customNode->MountToParent(parentNode);
    parentNode->tag_ = V2::PAGE_ETS_TAG;
    dialogLayoutAlgorithm.isHoverMode_ = true;
    /**
     * @tc.steps: step2. test DialogLayoutAlgorithm functions.
     * @tc.expected: These properties are matched.
     */
    EXPECT_TRUE(dialogLayoutAlgorithm.IsEmbeddedDialog(customNode));
    EXPECT_TRUE(displayInfo->GetCurrentFoldCreaseRegion().empty());
    dialogLayoutAlgorithm.UpdateSafeArea(frameNode);
    displayInfo->currentFoldCreaseRegion_.emplace_back(Rect(10.0f, 10.0f, 10.0f, 10.0f));
    EXPECT_FALSE(displayInfo->GetCurrentFoldCreaseRegion().empty());
    dialogLayoutAlgorithm.UpdateSafeArea(frameNode);
}

/**
 * @tc.name: DialogLayoutAlgorithmSetAlignmentSwitchLessThanAPITwelve
 * @tc.desc: Test DialogLayoutAlgorithm::SetAlignmentSwitchLessThanAPITwelve function
 * @tc.type: FUNC
 */
HWTEST_F(DialogLayoutTwoTestNg, DialogLayoutAlgorithmSetAlignmentSwitchLessThanAPITwelve, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create DialogLayoutAlgorithm instance.
     */
    DialogLayoutAlgorithm dialogLayoutAlgorithm;
    auto frameNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode, nullptr);
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto displayInfo = container->GetDisplayInfo();
    ASSERT_NE(displayInfo, nullptr);
    displayInfo->isFoldable_ = true;
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->minPlatformVersion_ = 12;
    EXPECT_TRUE(Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN));
    SizeF maxSize = SizeT(10.0f, 10.0f);
    SizeF childSize = SizeT(1.0f, 1.0f);
    OffsetF topLeftPoint = OffsetT(1.0f, 1.0f);
    SystemProperties::deviceType_ = DeviceType::PHONE;
    /**
     * @tc.steps: step2. test DialogLayoutAlgorithm functions.
     * @tc.expected: These properties are matched.
     */
    displayInfo->foldStatus_ = FoldStatus::EXPAND;
    EXPECT_TRUE(dialogLayoutAlgorithm.SetAlignmentSwitchLessThanAPITwelve(maxSize, childSize, topLeftPoint));

    displayInfo->foldStatus_ = FoldStatus::HALF_FOLD;
    EXPECT_TRUE(dialogLayoutAlgorithm.SetAlignmentSwitchLessThanAPITwelve(maxSize, childSize, topLeftPoint));

    displayInfo->foldStatus_ = FoldStatus::UNKNOWN;
    SystemProperties::orientation_ = DeviceOrientation::PORTRAIT;
    EXPECT_TRUE(dialogLayoutAlgorithm.SetAlignmentSwitchLessThanAPITwelve(maxSize, childSize, topLeftPoint));

    SystemProperties::orientation_ = DeviceOrientation::ORIENTATION_UNDEFINED;
    EXPECT_FALSE(dialogLayoutAlgorithm.SetAlignmentSwitchLessThanAPITwelve(maxSize, childSize, topLeftPoint));
}

/**
 * @tc.name: DialogPatternTest018
 * @tc.desc: Verify function Measure
 * @tc.type: FUNC
 */
HWTEST_F(DialogLayoutTwoTestNg, DialogPatternTest018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a child node and childLayoutWrapper
     * @tc.expected: created successfully.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<DialogTheme>()));
    RefPtr<FrameNode> dialogNode = FrameNode::CreateFrameNode(
        V2::ACTION_SHEET_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(nullptr, nullptr));
    ASSERT_NE(dialogNode, nullptr);
    auto childLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        dialogNode, dialogNode->GetGeometryNode(), dialogNode->GetLayoutProperty());
    ASSERT_NE(childLayoutWrapper, nullptr);

    /**
     * @tc.steps: step2. create dialog with a dialog node and layoutWrapper.
     * @tc.expected: the dialog node created successfully.
     */
    DialogProperties dialogProps { .type = DialogType::ACTION_SHEET,
        .title = "dialog test",
        .content = "dialog content test",
        .sheetsInfo = sheetItems,
        .buttons = btnItems,
        .width = -24,
        .backgroundColor = Color::TRANSPARENT };
    NG::BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(DIMENSION_RADIUS);
    dialogProps.borderRadius = borderRadius;
    NG::BorderWidthProperty borderWidth;
    borderWidth.SetBorderWidth(DIMENSION_WIDTH);
    dialogProps.borderWidth = borderWidth;
    NG::BorderColorProperty borderColor;
    borderColor.SetColor(Color::BLACK);
    dialogProps.borderColor = borderColor;
    auto dialog = DialogView::CreateDialogNode(dialogProps, nullptr);
    ASSERT_NE(dialog, nullptr);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.parentIdealSize = { DEFAULT_WIDTH, DEFAULT_HEIGHT };
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(dialog, dialog->GetGeometryNode(), dialog->GetLayoutProperty());
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();
    layoutWrapper->AppendChild(childLayoutWrapper);

    /**
     * @tc.steps: step3.execute Measure() and Layout()
     * @tc.expected: prop is set as expected.
     */
    DialogLayoutAlgorithm dialogLayoutAlgorithm;
    dialogLayoutAlgorithm.Measure(layoutWrapper.rawPtr_);
    dialogLayoutAlgorithm.Layout(layoutWrapper.rawPtr_);
    EXPECT_EQ(layoutWrapper->GetTotalChildCount(), 1);
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize().Width(), DEFAULT_WIDTH);
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize().Height(), DEFAULT_HEIGHT);
}

/**
 * @tc.name: DialogPatternTest019
 * @tc.desc: Verify function Measure
 * @tc.type: FUNC
 */
HWTEST_F(DialogLayoutTwoTestNg, DialogPatternTest019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a child node and childLayoutWrapper
     * @tc.expected: the child node created successfully.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<DialogTheme>()));
    RefPtr<FrameNode> childNode = FrameNode::CreateFrameNode(
        V2::ACTION_SHEET_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(nullptr, nullptr));
    ASSERT_NE(childNode, nullptr);
    auto childLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(childNode, childNode->GetGeometryNode(), childNode->GetLayoutProperty());
    ASSERT_NE(childLayoutWrapper, nullptr);

    /**
     * @tc.steps: step2. create dialog with a dialog node and layoutWrapper.
     * @tc.expected: the dialog node created successfully.
     */
    DialogProperties param { .type = DialogType::ACTION_SHEET,
        .title = "dialog test",
        .content = "dialog content test",
        .width = 320,
        .height = 320,
        .backgroundColor = Color::TRANSPARENT };
    NG::BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(DIMENSION_RADIUS);
    param.borderRadius = borderRadius;
    NG::BorderWidthProperty borderWidth;
    borderWidth.SetBorderWidth(DIMENSION_WIDTH);
    param.borderWidth = borderWidth;
    NG::BorderColorProperty borderColor;
    borderColor.SetColor(Color::BLACK);
    param.borderColor = borderColor;
    auto dialog = DialogView::CreateDialogNode(param, nullptr);
    ASSERT_NE(dialog, nullptr);

    auto dialogLayoutProps = dialog->GetLayoutProperty<DialogLayoutProperty>();
    ASSERT_NE(dialogLayoutProps, nullptr);
    dialogLayoutProps->UpdateWidth(param.width.value());
    dialogLayoutProps->UpdateHeight(param.height.value());
    SizeF size(param.width.value().ConvertToPx(), param.height.value().ConvertToPx());
    dialogLayoutProps->UpdateMarginSelfIdealSize(size);

    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(dialog, dialog->GetGeometryNode(), dialog->GetLayoutProperty());
    LayoutConstraintF layoutConstraint;
    layoutConstraint.parentIdealSize = OptionalSizeF(size);
    layoutConstraint.selfIdealSize = OptionalSizeF(size);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();
    dialog->AddChild(childNode);
    layoutWrapper->AppendChild(childLayoutWrapper);

    /**
     * @tc.steps: step3.execute Measure() and Layout()
     * @tc.expected: prop is set as expected.
     */
    DialogLayoutAlgorithm dialogLayoutAlgorithm;
    dialogLayoutAlgorithm.Measure(layoutWrapper.rawPtr_);
    dialogLayoutAlgorithm.Layout(layoutWrapper.rawPtr_);
    EXPECT_EQ(layoutWrapper->GetTotalChildCount(), 1);
    EXPECT_EQ(dialog->GetGeometryNode()->GetFrameSize().Height(), param.height.value().ConvertToPx());
}
} // namespace OHOS::Ace::NG