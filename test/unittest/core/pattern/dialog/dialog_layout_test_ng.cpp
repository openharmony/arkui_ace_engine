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
#include "core/components_ng/pattern/dialog/custom_dialog_controller_model_ng.h"
#include "core/components_ng/pattern/dialog/dialog_event_hub.h"
#include "core/components_ng/pattern/dialog/dialog_layout_algorithm.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_view.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
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
const Dimension DIMENSION_RADIUS(10.0, DimensionUnit::PX);
const Dimension DIMENSION_WIDTH(2.0, DimensionUnit::PX);
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
    EXPECT_FALSE(property->GetIsScenceBoardDialog().value_or(false));
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
} // namespace OHOS::Ace::NG
