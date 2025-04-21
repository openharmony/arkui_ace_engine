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
#include "core/components_ng/pattern/dialog/custom_dialog_controller_model_ng.h"
#include "core/components_ng/pattern/dialog/dialog_event_hub.h"
#include "core/components_ng/pattern/dialog/dialog_layout_algorithm.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_view.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
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
constexpr float DEFAULT_WIDTH = 600.0f;
constexpr float DEFAULT_HEIGHT = 1000.0f;
constexpr float FIRST_ITEM_WIDTH = 100.0f;
constexpr float FIRST_ITEM_HEIGHT = 50.0f;
const SizeF FIRST_ITEM_SIZE(FIRST_ITEM_WIDTH, FIRST_ITEM_HEIGHT);
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

class DialogLayoutTestNg : public testing::Test {
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

void DialogLayoutTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}
void DialogLayoutTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}
void DialogLayoutTestNg::SetDialogTheme()
{
    auto themeManager = AceType::DynamicCast<MockThemeManager>(MockPipelineContext::GetCurrent()->GetThemeManager());
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<MockDialogTheme>()));
}

RefPtr<LayoutWrapperNode> CreatlayoutWrapper()
{
    auto rowFrameNode = FrameNode::CreateFrameNode("test", 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();

    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());
    return layoutWrapper;
}

/**
 * @tc.name: DialogPatternTest003
 * @tc.desc: Test CreateDialogNode with customNode
 * @tc.type: FUNC
 */
HWTEST_F(DialogLayoutTestNg, DialogPatternTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a custom node and childLayoutWrapper
     */
    SetDialogTheme();
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
HWTEST_F(DialogLayoutTestNg, DialogPatternTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create DialogLayoutAlgorithm instance.
     */
    SetDialogTheme();
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
 * @tc.name: DialogPatternTest010
 * @tc.desc: Test dialogLayoutAlgorithm.ProcessMaskRect function
 * @tc.type: FUNC
 */
HWTEST_F(DialogLayoutTestNg, DialogPatternTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create DialogLayoutAlgorithm instance.
     * @tc.expected: the DialogLayoutAlgorithm created successfully.
     */
    SetDialogTheme();
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
    DimensionRect Rect(Dimension(childSize.Width()), Dimension(childSize.Height()), DimensionOffset(topLeftPoint_));
    std::vector<DimensionRect> initMouseResponseRegion;
    initMouseResponseRegion.push_back(Rect);
    gestureHub->SetMouseResponseRegion(initMouseResponseRegion);
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
 * @tc.name: DialogLayoutAlgorithm001
 * @tc.desc: Test DialogLayoutAlgorithm::ComputeInnerLayoutParam function
 * @tc.type: FUNC
 */
HWTEST_F(DialogLayoutTestNg, DialogLayoutAlgorithm001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create DialogLayoutAlgorithm instance.
     */
    SetDialogTheme();
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    SystemProperties::SetDeviceType(DeviceType::CAR);
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
    param.maskColor = Color::BLACK;
    param.type = DialogType::ACTION_SHEET;
    auto dialogWithCustom = DialogView::CreateDialogNode(param, customNode);
    ASSERT_NE(dialogWithCustom, nullptr);
    auto property = dialogWithCustom->GetLayoutProperty<DialogLayoutProperty>();
    DialogLayoutAlgorithm dialogLayoutAlgorithm;
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        dialogWithCustom, dialogWithCustom->GetGeometryNode(), dialogWithCustom->GetLayoutProperty());
    layoutWrapper->AppendChild(childLayoutWrapper);
    /**
     * @tc.steps: step3. test DialogLayoutAlgorithm's Measure function.
     * @tc.expected: dialogLayoutAlgorithm.alignment_ equal to DialogAlignment::DEFAULT.
     */
    dialogLayoutAlgorithm.Measure(layoutWrapper.rawPtr_);
    dialogLayoutAlgorithm.expandDisplay_ = true;
    dialogLayoutAlgorithm.Layout(layoutWrapper.rawPtr_);
    EXPECT_EQ(dialogLayoutAlgorithm.topLeftPoint_.GetX(), 10.0);
    EXPECT_EQ(dialogLayoutAlgorithm.topLeftPoint_.GetY(), 10.0);
}
/**
 * @tc.name: DialogLayoutAlgorithm002
 * @tc.desc: Test DialogLayoutAlgorithm::ComputeInnerLayoutParam function
 * @tc.type: FUNC
 */
HWTEST_F(DialogLayoutTestNg, DialogLayoutAlgorithm002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create DialogLayoutAlgorithm instance.
     */
    SetDialogTheme();
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::orientation_ = DeviceOrientation::LANDSCAPE;
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
        .isShowInSubWindow = false,
        .offset = DimensionOffset(Dimension(10.0), Dimension(10.0)),
    };
    param.maskColor = Color::BLACK;
    param.type = DialogType::ACTION_SHEET;
    auto dialogWithCustom = DialogView::CreateDialogNode(param, customNode);
    ASSERT_NE(dialogWithCustom, nullptr);
    auto property = dialogWithCustom->GetLayoutProperty<DialogLayoutProperty>();
    DialogLayoutAlgorithm dialogLayoutAlgorithm;
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        dialogWithCustom, dialogWithCustom->GetGeometryNode(), dialogWithCustom->GetLayoutProperty());
    layoutWrapper->AppendChild(childLayoutWrapper);
    /**
     * @tc.steps: step3. test DialogLayoutAlgorithm's Measure function.
     * @tc.expected: dialogLayoutAlgorithm.alignment_ equal to DialogAlignment::DEFAULT.
     */
    dialogLayoutAlgorithm.Measure(layoutWrapper.rawPtr_);
    dialogLayoutAlgorithm.Layout(layoutWrapper.rawPtr_);
    EXPECT_FALSE(property->GetIsSceneBoardDialog().value_or(false));
}

/**
 * @tc.name: DialogPatternTest018
 * @tc.desc: Verify function Measure
 * @tc.type: FUNC
 */
HWTEST_F(DialogLayoutTestNg, DialogPatternTest018, TestSize.Level1)
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
HWTEST_F(DialogLayoutTestNg, DialogPatternTest019, TestSize.Level1)
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

/**
 * @tc.name: DialogLayoutAlgorithm023
 * @tc.desc: Test DialogLayoutAlgorithm::ComputeInnerLayoutParam function
 * @tc.type: FUNC
 */
HWTEST_F(DialogLayoutTestNg, DialogLayoutAlgorithm023, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create DialogLayoutAlgorithm instance.
     */
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    SystemProperties::SetDeviceType(DeviceType::CAR);
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
        .alignment = DialogAlignment::CENTER_START,
    };
    param.maskColor = Color::BLACK;
    param.type = DialogType::ACTION_SHEET;
    auto dialogWithCustom = DialogView::CreateDialogNode(param, customNode);
    ASSERT_NE(dialogWithCustom, nullptr);
    auto property = dialogWithCustom->GetLayoutProperty<DialogLayoutProperty>();

    // isRightToLeft is true
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;

    DialogLayoutAlgorithm dialogLayoutAlgorithm;
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        dialogWithCustom, dialogWithCustom->GetGeometryNode(), dialogWithCustom->GetLayoutProperty());
    layoutWrapper->AppendChild(childLayoutWrapper);
    /**
     * @tc.steps: step3. test DialogLayoutAlgorithm's Measure function.
     * @tc.expected: dialogLayoutAlgorithm.alignment_ equal to DialogAlignment::CENTER_START.
     */
    dialogLayoutAlgorithm.Measure(layoutWrapper.rawPtr_);
    dialogLayoutAlgorithm.expandDisplay_ = true;
    dialogLayoutAlgorithm.Layout(layoutWrapper.rawPtr_);
    EXPECT_EQ(dialogLayoutAlgorithm.alignment_, DialogAlignment::CENTER_START);
}

/**
 * @tc.name: DialogLayoutAlgorithm024
 * @tc.desc: Test DialogLayoutAlgorithm::ComputeInnerLayoutParam function
 * @tc.type: FUNC
 */
HWTEST_F(DialogLayoutTestNg, DialogLayoutAlgorithm024, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create DialogLayoutAlgorithm instance.
     */
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    SystemProperties::SetDeviceType(DeviceType::CAR);
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
        .alignment = DialogAlignment::CENTER_END,
    };
    param.maskColor = Color::BLACK;
    param.type = DialogType::ACTION_SHEET;
    auto dialogWithCustom = DialogView::CreateDialogNode(param, customNode);
    ASSERT_NE(dialogWithCustom, nullptr);
    auto property = dialogWithCustom->GetLayoutProperty<DialogLayoutProperty>();

    // isRightToLeft is true
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;

    DialogLayoutAlgorithm dialogLayoutAlgorithm;
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        dialogWithCustom, dialogWithCustom->GetGeometryNode(), dialogWithCustom->GetLayoutProperty());
    layoutWrapper->AppendChild(childLayoutWrapper);
    /**
     * @tc.steps: step3. test DialogLayoutAlgorithm's Measure function.
     * @tc.expected: dialogLayoutAlgorithm.alignment_ equal to DialogAlignment::CENTER_END.
     */
    dialogLayoutAlgorithm.Measure(layoutWrapper.rawPtr_);
    dialogLayoutAlgorithm.expandDisplay_ = true;
    dialogLayoutAlgorithm.Layout(layoutWrapper.rawPtr_);
    EXPECT_EQ(dialogLayoutAlgorithm.alignment_, DialogAlignment::CENTER_END);
}

/**
 * @tc.name: DialogLayoutAlgorithm025
 * @tc.desc: Test DialogLayoutAlgorithm::ComputeInnerLayoutParam function
 * @tc.type: FUNC
 */
HWTEST_F(DialogLayoutTestNg, DialogLayoutAlgorithm025, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create DialogLayoutAlgorithm instance.
     */
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    SystemProperties::SetDeviceType(DeviceType::CAR);
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
        .alignment = DialogAlignment::BOTTOM_START,
    };
    param.maskColor = Color::BLACK;
    param.type = DialogType::ACTION_SHEET;
    auto dialogWithCustom = DialogView::CreateDialogNode(param, customNode);
    ASSERT_NE(dialogWithCustom, nullptr);
    auto property = dialogWithCustom->GetLayoutProperty<DialogLayoutProperty>();

    // isRightToLeft is true
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;

    DialogLayoutAlgorithm dialogLayoutAlgorithm;
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        dialogWithCustom, dialogWithCustom->GetGeometryNode(), dialogWithCustom->GetLayoutProperty());
    layoutWrapper->AppendChild(childLayoutWrapper);
    /**
     * @tc.steps: step3. test DialogLayoutAlgorithm's Measure function.
     * @tc.expected: dialogLayoutAlgorithm.alignment_ equal to DialogAlignment::BOTTOM_START.
     */
    dialogLayoutAlgorithm.Measure(layoutWrapper.rawPtr_);
    dialogLayoutAlgorithm.expandDisplay_ = true;
    dialogLayoutAlgorithm.Layout(layoutWrapper.rawPtr_);
    EXPECT_EQ(dialogLayoutAlgorithm.alignment_, DialogAlignment::BOTTOM_START);
}

/**
 * @tc.name: DialogLayoutAlgorithm026
 * @tc.desc: Test DialogLayoutAlgorithm::ComputeInnerLayoutParam function
 * @tc.type: FUNC
 */
HWTEST_F(DialogLayoutTestNg, DialogLayoutAlgorithm026, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create DialogLayoutAlgorithm instance.
     */
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    SystemProperties::SetDeviceType(DeviceType::CAR);
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
        .alignment = DialogAlignment::BOTTOM_END,
    };
    param.maskColor = Color::BLACK;
    param.type = DialogType::ACTION_SHEET;
    auto dialogWithCustom = DialogView::CreateDialogNode(param, customNode);
    ASSERT_NE(dialogWithCustom, nullptr);
    auto property = dialogWithCustom->GetLayoutProperty<DialogLayoutProperty>();

    // isRightToLeft is true
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;

    DialogLayoutAlgorithm dialogLayoutAlgorithm;
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        dialogWithCustom, dialogWithCustom->GetGeometryNode(), dialogWithCustom->GetLayoutProperty());
    layoutWrapper->AppendChild(childLayoutWrapper);
    /**
     * @tc.steps: step3. test DialogLayoutAlgorithm's Measure function.
     * @tc.expected: dialogLayoutAlgorithm.alignment_ equal to DialogAlignment::BOTTOM_END.
     */
    dialogLayoutAlgorithm.Measure(layoutWrapper.rawPtr_);
    dialogLayoutAlgorithm.expandDisplay_ = true;
    dialogLayoutAlgorithm.Layout(layoutWrapper.rawPtr_);
    EXPECT_EQ(dialogLayoutAlgorithm.alignment_, DialogAlignment::BOTTOM_END);
}

/**
 * @tc.name: DialogLayoutAlgorithm027
 * @tc.desc: Test DialogLayoutAlgorithm::ComputeInnerLayoutParam function offset
 * @tc.type: FUNC
 */
HWTEST_F(DialogLayoutTestNg, DialogLayoutAlgorithm027, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create DialogLayoutAlgorithm instance.
     */
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    SystemProperties::SetDeviceType(DeviceType::CAR);
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
    param.maskColor = Color::BLACK;
    param.type = DialogType::ACTION_SHEET;
    auto dialogWithCustom = DialogView::CreateDialogNode(param, customNode);
    ASSERT_NE(dialogWithCustom, nullptr);
    auto property = dialogWithCustom->GetLayoutProperty<DialogLayoutProperty>();

    // isRightToLeft is true
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;

    DialogLayoutAlgorithm dialogLayoutAlgorithm;
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        dialogWithCustom, dialogWithCustom->GetGeometryNode(), dialogWithCustom->GetLayoutProperty());
    layoutWrapper->AppendChild(childLayoutWrapper);
    /**
     * @tc.steps: step3. test DialogLayoutAlgorithm's Measure function.
     * @tc.expected: dialogLayoutAlgorithm.topLeftPoint_.GetX() equal to 10.0.
     */
    dialogLayoutAlgorithm.Measure(layoutWrapper.rawPtr_);
    dialogLayoutAlgorithm.expandDisplay_ = true;
    dialogLayoutAlgorithm.Layout(layoutWrapper.rawPtr_);
    EXPECT_EQ(dialogLayoutAlgorithm.topLeftPoint_.GetX(), 10.0);
    EXPECT_EQ(dialogLayoutAlgorithm.topLeftPoint_.GetY(), 10.0);
}

/**
 * @tc.name: DialogLayoutAlgorithm030
 * @tc.desc: Test DialogLayoutAlgorithm::ComputeInnerLayoutParam function
 * @tc.type: FUNC
 */
HWTEST_F(DialogLayoutTestNg, DialogLayoutAlgorithm030, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create DialogLayoutAlgorithm instance.
     */
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    SystemProperties::SetDeviceType(DeviceType::CAR);
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
        .alignment = DialogAlignment::TOP_START,
    };
    param.maskColor = Color::BLACK;
    param.type = DialogType::ACTION_SHEET;
    auto dialogWithCustom = DialogView::CreateDialogNode(param, customNode);
    ASSERT_NE(dialogWithCustom, nullptr);
    auto property = dialogWithCustom->GetLayoutProperty<DialogLayoutProperty>();

    // isRightToLeft is true
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;

    DialogLayoutAlgorithm dialogLayoutAlgorithm;
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        dialogWithCustom, dialogWithCustom->GetGeometryNode(), dialogWithCustom->GetLayoutProperty());
    layoutWrapper->AppendChild(childLayoutWrapper);
    /**
     * @tc.steps: step3. test DialogLayoutAlgorithm's Measure function.
     * @tc.expected: dialogLayoutAlgorithm.alignment_ equal to DialogAlignment::TOP_START.
     */
    dialogLayoutAlgorithm.Measure(layoutWrapper.rawPtr_);
    dialogLayoutAlgorithm.expandDisplay_ = true;
    dialogLayoutAlgorithm.Layout(layoutWrapper.rawPtr_);
    EXPECT_EQ(dialogLayoutAlgorithm.alignment_, DialogAlignment::TOP_START);
}

/**
 * @tc.name: DialogLayoutAlgorithm031
 * @tc.desc: Test DialogLayoutAlgorithm::ComputeInnerLayoutParam function
 * @tc.type: FUNC
 */
HWTEST_F(DialogLayoutTestNg, DialogLayoutAlgorithm031, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create DialogLayoutAlgorithm instance.
     */
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    SystemProperties::SetDeviceType(DeviceType::CAR);
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
        .alignment = DialogAlignment::TOP_END,
    };
    param.maskColor = Color::BLACK;
    param.type = DialogType::ACTION_SHEET;
    auto dialogWithCustom = DialogView::CreateDialogNode(param, customNode);
    ASSERT_NE(dialogWithCustom, nullptr);
    auto property = dialogWithCustom->GetLayoutProperty<DialogLayoutProperty>();

    // isRightToLeft is true
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;

    DialogLayoutAlgorithm dialogLayoutAlgorithm;
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        dialogWithCustom, dialogWithCustom->GetGeometryNode(), dialogWithCustom->GetLayoutProperty());
    layoutWrapper->AppendChild(childLayoutWrapper);
    /**
     * @tc.steps: step3. test DialogLayoutAlgorithm's Measure function.
     * @tc.expected: dialogLayoutAlgorithm.alignment_ equal to DialogAlignment::TOP_END.
     */

    dialogLayoutAlgorithm.Measure(layoutWrapper.rawPtr_);
    dialogLayoutAlgorithm.expandDisplay_ = true;
    dialogLayoutAlgorithm.Layout(layoutWrapper.rawPtr_);
    EXPECT_EQ(dialogLayoutAlgorithm.alignment_, DialogAlignment::TOP_END);
}

/**
 * @tc.name: DialogLayoutAlgorithm032
 * @tc.desc: Test CreateDialogNode with customNode
 * @tc.type: FUNC
 */
HWTEST_F(DialogLayoutTestNg, DialogLayoutAlgorithm032, TestSize.Level1)
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
    /**
     * @tc.steps: step3. change props to create dialog with a custom node.
     * @tc.expected: the dialog node and layoutWrapper2 created successfully.
     */
    propsCustom.customStyle = true;
    propsCustom.title = "dialog title";
    propsCustom.subtitle = "";
    propsCustom.content = "";
    dialogWithCustom = DialogView::CreateDialogNode(propsCustom, customNode);
    ASSERT_NE(dialogWithCustom, nullptr);
    auto layoutWrapper2 = AceType::MakeRefPtr<LayoutWrapperNode>(
        dialogWithCustom, dialogWithCustom->GetGeometryNode(), dialogWithCustom->GetLayoutProperty());
    ASSERT_NE(layoutWrapper2, nullptr);
    layoutWrapper2->AppendChild(childLayoutWrapper);
    DialogLayoutAlgorithm dialogLayoutAlgorithm2;
    dialogLayoutAlgorithm2.Measure(layoutWrapper2.rawPtr_);
    /**
     * @tc.steps: step4. change props to create dialog with a custom node.
     * @tc.expected: the dialog node and layoutWrapper2 created successfully.
     */
    propsCustom.title = "";
    propsCustom.subtitle = "dialog subtitle";
    propsCustom.content = "";
    dialogWithCustom = DialogView::CreateDialogNode(propsCustom, customNode);
    ASSERT_NE(dialogWithCustom, nullptr);
    auto layoutWrapper3 = AceType::MakeRefPtr<LayoutWrapperNode>(
        dialogWithCustom, dialogWithCustom->GetGeometryNode(), dialogWithCustom->GetLayoutProperty());
    ASSERT_NE(layoutWrapper3, nullptr);
    layoutWrapper3->AppendChild(childLayoutWrapper);
    DialogLayoutAlgorithm dialogLayoutAlgorithm3;
    dialogLayoutAlgorithm3.Measure(layoutWrapper3.rawPtr_);
}

/**
 * @tc.name: DialogLayoutAlgorithm033
 * @tc.desc: Test CreateDialogNode with customNode
 * @tc.type: FUNC
 */
HWTEST_F(DialogLayoutTestNg, DialogLayoutAlgorithm033, TestSize.Level1)
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
HWTEST_F(DialogLayoutTestNg, DialogViewTest001, TestSize.Level1)
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
    DialogProperties param { .type = DialogType::ACTION_SHEET,
        .title = "dialog test",
        .content = "dialog content test",
        .width = 320,
        .height = 320,
        .backgroundColor = Color::TRANSPARENT,
        .alignment = DialogAlignment::DEFAULT,
        .hoverModeArea = HoverModeAreaType::TOP_SCREEN,
        .isSceneBoardDialog = true,
        .maskTransitionEffect = maskTransitionEffect,
        .dialogTransitionEffect = dialogTransitionEffect };
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
 * @tc.name: CustomDialogControllerModelTest001
 * @tc.desc: Test CustomDialogControllerModel::SetOpenDialogWithNode function
 * @tc.type: FUNC
 */
HWTEST_F(DialogLayoutTestNg, CustomDialogControllerModelTest001, TestSize.Level1)
{
    DialogProperties props { .type = DialogType::ACTION_SHEET,
        .title = "dialog test",
        .content = "dialog content test",
        .dialogLevelMode = LevelMode::EMBEDDED };
    CustomDialogControllerModelNG controllerModel;
    controllerModel.SetOpenDialogWithNode(props, nullptr);
}

/**
 * @tc.name: CustomDialogControllerModelTest002
 * @tc.desc: Test CustomDialogControllerModel::SetCloseDialogForNDK function
 * @tc.type: FUNC
 */
HWTEST_F(DialogLayoutTestNg, CustomDialogControllerModelTest002, TestSize.Level1)
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
HWTEST_F(DialogLayoutTestNg, DialogLayoutAlgorithmGetEmbeddedDialogOffsetY, TestSize.Level1)
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
HWTEST_F(DialogLayoutTestNg, DialogLayoutAlgorithmAdjustHeightForKeyboard001, TestSize.Level1)
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
HWTEST_F(DialogLayoutTestNg, DialogLayoutAlgorithmAdjustHeightForKeyboard002, TestSize.Level1)
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
 * @tc.name: DialogLayoutAlgorithmCaculateMaxSize
 * @tc.desc: Test DialogLayoutAlgorithm::CaculateMaxSize function
 * @tc.type: FUNC
 */
HWTEST_F(DialogLayoutTestNg, DialogLayoutAlgorithmCaculateMaxSize, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create DialogLayoutAlgorithm instance.
     */
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    DialogLayoutAlgorithm dialogLayoutAlgorithm;
    SizeF maxSize = SizeF(10.0f, 10.0f);
    dialogLayoutAlgorithm.safeAreaBottomLength_ = 1.0f;
    /**
     * @tc.steps: step2. test DialogLayoutAlgorithm functions.
     * @tc.expected: These properties are matched.
     */
    dialogLayoutAlgorithm.customSize_ = true;
    dialogLayoutAlgorithm.CaculateMaxSize(maxSize);
    EXPECT_EQ(maxSize.Height(), 10.0f);

    dialogLayoutAlgorithm.customSize_ = false;
    dialogLayoutAlgorithm.isHoverMode_ = true;
    dialogLayoutAlgorithm.hoverModeArea_ = HoverModeAreaType::TOP_SCREEN;
    dialogLayoutAlgorithm.CaculateMaxSize(maxSize);
    EXPECT_EQ(maxSize.Height(), 0.0f);
}

/**
 * @tc.name: DialogLayoutAlgorithmIsEmbeddedDialog
 * @tc.desc: Test DialogLayoutAlgorithm::IsEmbeddedDialog function
 * @tc.type: FUNC
 */
HWTEST_F(DialogLayoutTestNg, DialogLayoutAlgorithmIsEmbeddedDialog, TestSize.Level1)
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
HWTEST_F(DialogLayoutTestNg, DialogLayoutAlgorithmUpdateIsScrollHeightNegative, TestSize.Level1)
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
HWTEST_F(DialogLayoutTestNg, DialogLayoutAlgorithmUpdateSafeArea, TestSize.Level1)
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
HWTEST_F(DialogLayoutTestNg, DialogLayoutAlgorithmSetAlignmentSwitchLessThanAPITwelve, TestSize.Level1)
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
 * @tc.name: DialogLayoutAlgorithmSetSubWindowHotarea
 * @tc.desc: Test DialogLayoutAlgorithm::SetSubWindowHotarea function
 * @tc.type: FUNC
 */
HWTEST_F(DialogLayoutTestNg, DialogLayoutAlgorithmSetSubWindowHotarea, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create DialogLayoutAlgorithm instance.
     */
    DialogLayoutAlgorithm dialogLayoutAlgorithm;
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
    auto dialogProp = dialogWithCustom->GetLayoutProperty<DialogLayoutProperty>();
    ASSERT_NE(dialogProp, nullptr);
    dialogProp->propShowInSubWindow_ = true;
    dialogProp->propIsSceneBoardDialog_ = true;
    dialogLayoutAlgorithm.isUIExtensionSubWindow_ = true;
    dialogLayoutAlgorithm.isModal_ = false;
    SizeF childSize = SizeT(10.0f, 10.0f);
    SizeF selfSize = SizeT(1.0f, 1.0f);
    /**
     * @tc.steps: step2. test DialogLayoutAlgorithm functions.
     * @tc.expected: These properties are matched.
     */
    dialogLayoutAlgorithm.SetSubWindowHotarea(dialogProp, childSize, selfSize, 0);
    EXPECT_TRUE(dialogProp->GetShowInSubWindowValue(false));
    EXPECT_TRUE(dialogProp->GetIsSceneBoardDialog().value_or(false));
}

/**
 * @tc.name: DialogLayoutAlgorithmComputeInnerLayoutParam
 * @tc.desc: Test DialogLayoutAlgorithm::ComputeInnerLayoutParam function
 * @tc.type: FUNC
 */
HWTEST_F(DialogLayoutTestNg, DialogLayoutAlgorithmComputeInnerLayoutParam, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create DialogLayoutAlgorithm instance.
     */
    DialogLayoutAlgorithm dialogLayoutAlgorithm;
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
    auto dialogProp = dialogWithCustom->GetLayoutProperty<DialogLayoutProperty>();
    ASSERT_NE(dialogProp, nullptr);
    LayoutConstraintF innerLayout = {
        .minSize = { 1, 1 },
        .maxSize = { 10, 10 },        // 10 is the maxSize of width and height
        .percentReference = { 5, 5 }, // 5 is the percentReference of width and height
        .parentIdealSize = { 2, 2 },  // 2 is the parentIdealSize of width and height
    };
    dialogLayoutAlgorithm.gridCount_ = 1;
    EXPECT_FALSE(dialogLayoutAlgorithm.ComputeInnerLayoutSizeParam(innerLayout, dialogProp));
    /**
     * @tc.steps: step2. test DialogLayoutAlgorithm functions.
     * @tc.expected: These properties are matched.
     */
    SystemProperties::deviceType_ = DeviceType::WATCH;
    dialogLayoutAlgorithm.expandDisplay_ = true;
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->minPlatformVersion_ = 12;
    EXPECT_TRUE(Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN));
    dialogLayoutAlgorithm.ComputeInnerLayoutParam(innerLayout, dialogProp);
}

/**
 * @tc.name: DialogLayoutAlgorithmGetCurrentPipelineContext
 * @tc.desc: Test DialogLayoutAlgorithm::GetCurrentPipelineContext function
 * @tc.type: FUNC
 */
HWTEST_F(DialogLayoutTestNg, DialogLayoutAlgorithmGetCurrentPipelineContext, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create DialogLayoutAlgorithm instance.
     */
    DialogLayoutAlgorithm dialogLayoutAlgorithm;
    Container::UpdateCurrent(COMPONENT_SUBWINDOW_CONTAINER * CONTAINER_ID_DIVIDE_SIZE + 1);
    /**
     * @tc.steps: step2. test DialogLayoutAlgorithm functions.
     * @tc.expected: These properties are matched.
     */
    EXPECT_TRUE(Container::CurrentId() >= MIN_SUBCONTAINER_ID);
    dialogLayoutAlgorithm.GetCurrentPipelineContext();
}

/**
 * @tc.name: DialogLayoutAlgorithmIsGetExpandDisplayValidHeight
 * @tc.desc: Test DialogLayoutAlgorithm::IsGetExpandDisplayValidHeight function
 * @tc.type: FUNC
 */
HWTEST_F(DialogLayoutTestNg, DialogLayoutAlgorithmIsGetExpandDisplayValidHeight, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create DialogLayoutAlgorithm instance.
     */
    DialogLayoutAlgorithm dialogLayoutAlgorithm;
    dialogLayoutAlgorithm.expandDisplay_ = true;
    dialogLayoutAlgorithm.isShowInSubWindow_ = true;
    Container::UpdateCurrent(0);
    auto pipelineContext = dialogLayoutAlgorithm.GetCurrentPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->UpdateDisplayAvailableRect(Rect(1.0f, 1.0f, 1.0f, 1.0f));
    /**
     * @tc.steps: step2. test DialogLayoutAlgorithm functions.
     * @tc.expected: These properties are matched.
     */
    EXPECT_TRUE(dialogLayoutAlgorithm.IsGetExpandDisplayValidHeight());
}

/**
 * @tc.name: DialogLayoutAlgorithmUpdateChildMaxSizeHeight
 * @tc.desc: Test DialogLayoutAlgorithm::UpdateChildMaxSizeHeight function
 * @tc.type: FUNC
 */
HWTEST_F(DialogLayoutTestNg, DialogLayoutAlgorithmUpdateChildMaxSizeHeight, TestSize.Level1)
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
 * @tc.name: DialogLayoutAlgorithmComputeInnerLayoutSizeParam001
 * @tc.desc: Test DialogLayoutAlgorithm::ComputeInnerLayoutSizeParam function
 * @tc.type: FUNC
 */
HWTEST_F(DialogLayoutTestNg, DialogLayoutAlgorithmComputeInnerLayoutSizeParam001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create DialogLayoutAlgorithm instance.
     */
    DialogLayoutAlgorithm dialogLayoutAlgorithm;
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
    auto dialogProp = dialogWithCustom->GetLayoutProperty<DialogLayoutProperty>();
    ASSERT_NE(dialogProp, nullptr);
    LayoutConstraintF innerLayout = {
        .minSize = { 1, 1 },
        .maxSize = { 10, 10 },        // 10 is the maxSize of width and height
        .percentReference = { 5, 5 }, // 5 is the percentReference of width and height
        .parentIdealSize = { 2, 2 },  // 2 is the parentIdealSize of width and height
    };
    dialogLayoutAlgorithm.gridCount_ = -1;
    /**
     * @tc.steps: step2. test DialogLayoutAlgorithm functions.
     * @tc.expected: These properties are matched.
     */
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->minPlatformVersion_ = 16;
    EXPECT_TRUE(dialogLayoutAlgorithm.ComputeInnerLayoutSizeParam(innerLayout, dialogProp));

    dialogProp->propHeight_ = CalcDimension(DEFAULT_STR);
    dialogProp->propWidth_ = CalcDimension(DEFAULT_STR);
    dialogLayoutAlgorithm.isSuitableForElderly_ = true;
    EXPECT_TRUE(dialogLayoutAlgorithm.ComputeInnerLayoutSizeParam(innerLayout, dialogProp));
}

/**
 * @tc.name: DialogLayoutAlgorithmComputeInnerLayoutSizeParam002
 * @tc.desc: Test DialogLayoutAlgorithm::ComputeInnerLayoutSizeParam function
 * @tc.type: FUNC
 */
HWTEST_F(DialogLayoutTestNg, DialogLayoutAlgorithmComputeInnerLayoutSizeParam002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create DialogLayoutAlgorithm instance.
     */
    DialogLayoutAlgorithm dialogLayoutAlgorithm;
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
    auto dialogProp = dialogWithCustom->GetLayoutProperty<DialogLayoutProperty>();
    ASSERT_NE(dialogProp, nullptr);
    LayoutConstraintF innerLayout = {
        .minSize = { 1, 1 },
        .maxSize = { 10, 10 },        // 10 is the maxSize of width and height
        .percentReference = { 5, 5 }, // 5 is the percentReference of width and height
        .parentIdealSize = { 2, 2 },  // 2 is the parentIdealSize of width and height
    };
    dialogLayoutAlgorithm.gridCount_ = -1;
    /**
     * @tc.steps: step2. test DialogLayoutAlgorithm functions.
     * @tc.expected: These properties are matched.
     */
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->minPlatformVersion_ = 16;
    dialogProp->propHeight_ = Dimension(1.0f, DimensionUnit::PERCENT);
    dialogProp->propWidth_ = Dimension(1.0f, DimensionUnit::PERCENT);
    EXPECT_TRUE(dialogLayoutAlgorithm.ComputeInnerLayoutSizeParam(innerLayout, dialogProp));
}

/**
 * @tc.name: DialogLayoutAlgorithmAnalysisLayoutOfContent001
 * @tc.desc: Test DialogLayoutAlgorithm::AnalysisLayoutOfContent function
 * @tc.type: FUNC
 */
HWTEST_F(DialogLayoutTestNg, DialogLayoutAlgorithmAnalysisLayoutOfContent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create DialogLayoutAlgorithm instance.
     */
    DialogLayoutAlgorithm dialogLayoutAlgorithm;
    auto customNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 100, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(customNode, nullptr);
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
    RefPtr<LayoutWrapperNode> scroll = customNode->CreateLayoutWrapper(true, true);
    ASSERT_NE(scroll, nullptr);
    auto layoutWrapperNode = dialogWithCustom->CreateLayoutWrapper(true, true);
    auto layoutWrapper = reinterpret_cast<LayoutWrapper*>(Referenced::RawPtr(layoutWrapperNode));
    ASSERT_NE(layoutWrapper, nullptr);
    auto textNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXT_ETS_TAG, textNodeId, []() { return AceType::MakeRefPtr<TextPattern>(); });
    RefPtr<GeometryNode> textGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    textGeometryNode->Reset();
    RefPtr<LayoutWrapperNode> textLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textNode, textGeometryNode, textNode->GetLayoutProperty());
    auto textPattern = textNode->GetPattern<TextPattern>();
    auto textLayoutAlgorithm = textPattern->CreateLayoutAlgorithm();
    textLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(textLayoutAlgorithm));
    textLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    scroll->AppendChild(textLayoutWrapper);
    auto hostNode = layoutWrapper->GetHostNode();
    ASSERT_NE(hostNode, nullptr);
    auto dialogPattern = hostNode->GetPattern<DialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);
    dialogPattern->title_ = "";
    EXPECT_TRUE(dialogPattern->GetTitle().empty());
    /**
     * @tc.steps: step2. test DialogLayoutAlgorithm functions.
     * @tc.expected: These properties are matched.
     */
    dialogPattern->subtitle_ = TITLE;
    dialogLayoutAlgorithm.AnalysisLayoutOfContent(layoutWrapper, scroll);
    dialogPattern->subtitle_ = "";
    EXPECT_TRUE(dialogPattern->GetSubtitle().empty());
    dialogLayoutAlgorithm.AnalysisLayoutOfContent(layoutWrapper, scroll);
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->minPlatformVersion_ = 12;
    EXPECT_TRUE(Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN));
    dialogLayoutAlgorithm.AnalysisLayoutOfContent(layoutWrapper, scroll);
}

/**
 * @tc.name: DialogLayoutAlgorithmAnalysisLayoutOfContent002
 * @tc.desc: Test DialogLayoutAlgorithm::AnalysisLayoutOfContent function
 * @tc.type: FUNC
 */
HWTEST_F(DialogLayoutTestNg, DialogLayoutAlgorithmAnalysisLayoutOfContent002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create DialogLayoutAlgorithm instance.
     */
    DialogLayoutAlgorithm dialogLayoutAlgorithm;
    auto customNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 100, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(customNode, nullptr);
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
    RefPtr<LayoutWrapperNode> scroll = customNode->CreateLayoutWrapper(true, true);
    ASSERT_NE(scroll, nullptr);
    auto layoutWrapperNode = dialogWithCustom->CreateLayoutWrapper(true, true);
    auto layoutWrapper = reinterpret_cast<LayoutWrapper*>(Referenced::RawPtr(layoutWrapperNode));
    ASSERT_NE(layoutWrapper, nullptr);
    auto textNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXT_ETS_TAG, textNodeId, []() { return AceType::MakeRefPtr<TextPattern>(); });
    RefPtr<GeometryNode> textGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    textGeometryNode->Reset();
    RefPtr<LayoutWrapperNode> textLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textNode, textGeometryNode, textNode->GetLayoutProperty());
    auto textPattern = textNode->GetPattern<TextPattern>();
    auto textLayoutAlgorithm = textPattern->CreateLayoutAlgorithm();
    textLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(textLayoutAlgorithm));
    textLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    scroll->AppendChild(textLayoutWrapper);
    auto hostNode = layoutWrapper->GetHostNode();
    ASSERT_NE(hostNode, nullptr);
    auto dialogPattern = hostNode->GetPattern<DialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto dialogTheme = pipelineContext->GetTheme<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    dialogTheme->text_align_content_ = 1;
    /**
     * @tc.steps: step2. test DialogLayoutAlgorithm functions.
     * @tc.expected: These properties are matched.
     */
    dialogLayoutAlgorithm.AnalysisLayoutOfContent(layoutWrapper, scroll);

    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->minPlatformVersion_ = 12;
    EXPECT_TRUE(Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN));
    dialogLayoutAlgorithm.AnalysisLayoutOfContent(layoutWrapper, scroll);
}

/**
 * @tc.name: DialogLayoutAlgorithmMeasure001
 * @tc.desc: Test DialogLayoutAlgorithm::Measure function
 * @tc.type: FUNC
 */
HWTEST_F(DialogLayoutTestNg, DialogLayoutAlgorithmMeasure001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create DialogLayoutAlgorithm instance.
     */
    DialogLayoutAlgorithm dialogLayoutAlgorithm;
    auto customNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 100, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(customNode, nullptr);
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
    std::list<RefPtr<LayoutWrapper>> childList;
    auto layoutWrapper2 = CreatlayoutWrapper();
    layoutWrapper2->GetLayoutProperty()->propVisibility_ = VisibleType::GONE;
    childList.push_front(layoutWrapper2);
    auto hostNode = layoutWrapper->GetHostNode();
    ASSERT_NE(hostNode, nullptr);
    auto parentNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 99, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(parentNode, nullptr);
    parentNode->tag_ = V2::PAGE_ETS_TAG;
    hostNode->MountToParent(parentNode);
    auto dialogPattern = hostNode->GetPattern<DialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);
    auto dialogContext = hostNode->GetPattern<Pattern>()->GetContext();
    ASSERT_NE(dialogContext, nullptr);
    /**
     * @tc.steps: step2. test DialogLayoutAlgorithm functions.
     * @tc.expected: These properties are matched.
     */
    dialogPattern->isPickerDialog_ = true;
    dialogContext->fontScale_ = 2.0f;
    dialogLayoutAlgorithm.Measure(layoutWrapper);
    EXPECT_FALSE(dialogLayoutAlgorithm.isSuitableForElderly_);
    dialogPattern->dialogProperties_.dialogImmersiveMode = ImmersiveMode::EXTEND;
    dialogLayoutAlgorithm.Measure(layoutWrapper);
}

/**
 * @tc.name: DialogLayoutAlgorithmMeasure002
 * @tc.desc: Test DialogLayoutAlgorithm::Measure function
 * @tc.type: FUNC
 */
HWTEST_F(DialogLayoutTestNg, DialogLayoutAlgorithmMeasure002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create DialogLayoutAlgorithm instance.
     */
    DialogLayoutAlgorithm dialogLayoutAlgorithm;
    auto customNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 100, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(customNode, nullptr);
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
    auto hostNode = layoutWrapper->GetHostNode();
    ASSERT_NE(hostNode, nullptr);
    auto parentNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 99, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(parentNode, nullptr);
    parentNode->tag_ = V2::PAGE_ETS_TAG;
    hostNode->MountToParent(parentNode);
    /**
     * @tc.steps: step2. test DialogLayoutAlgorithm functions.
     * @tc.expected: These properties are matched.
     */
    auto& layoutConstraint =
        AceType::DynamicCast<LayoutProperty>(layoutWrapper->GetLayoutProperty())->layoutConstraint_;
    auto& parentIdealSize = layoutConstraint->parentIdealSize;
    parentIdealSize.SetSize(SizeT<float>(2.0f, 2.0f));
    OptionalSizeF realSize;
    // dialog size fit screen.
    realSize.UpdateIllegalSizeWithCheck(parentIdealSize);
    EXPECT_TRUE(realSize.IsValid());
    dialogLayoutAlgorithm.Measure(layoutWrapper);
}
} // namespace OHOS::Ace::NG
