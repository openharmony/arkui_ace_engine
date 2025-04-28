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
#include <functional>
#include <optional>

#include "gtest/gtest.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "adapter/ohos/entrance/picker/picker_haptic_factory.h"
#include "base/geometry/dimension.h"
#include "base/geometry/ng/size_t.h"
#include "base/i18n/localization.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/measure_util.h"
#include "core/components/picker/picker_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_picker/textpicker_column_pattern.h"
#include "core/components_ng/pattern/text_picker/textpicker_dialog_view.h"
#include "core/components_ng/pattern/text_picker/textpicker_model.h"
#include "core/components_ng/pattern/text_picker/textpicker_model_ng.h"
#include "core/components_ng/pattern/text_picker/textpicker_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline_ng/ui_task_scheduler.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_font_manager.h"
#include "test/mock/core/common/mock_theme_default.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "test/mock/core/pattern/mock_picker_haptic_impl.h"


using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t ONCANCEL_CALLBACK_INFO = 1;
constexpr double FONT_SIZE_10 = 10.0;
constexpr float COMPONENT_WIDTH = 45.0f;
constexpr float COMPONENT_HEIGHT = 36.0f;
constexpr float MAX_WIDTH = 100.0f;
constexpr float MAX_HEIGHT = 100.0f;
const Dimension DEFAULT_GRADIENT_HEIGHT = 20.0_vp;
const Dimension DEFAULT_PICKER_ITEM_HEIGHT = 12.0_vp;
constexpr size_t ACCEPT_BUTTON_INDEX = 0;
RefPtr<Theme> GetTheme(ThemeType type)
{
    if (type == IconTheme::TypeId()) {
        return AceType::MakeRefPtr<IconTheme>();
    } else if (type == DialogTheme::TypeId()) {
        return AceType::MakeRefPtr<DialogTheme>();
    } else if (type == PickerTheme::TypeId()) {
        return MockThemeDefault::GetPickerTheme();
    } else if (type == ButtonTheme::TypeId()) {
        return AceType::MakeRefPtr<ButtonTheme>();
    } else {
        return nullptr;
    }
}
} // namespace

class TextPickerColumnExtendTestNg : public TestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    RefPtr<FrameNode> GetOrCreateTextPickerFrameNodeTree();
    RefPtr<TextPickerColumnPattern> GetTextPickerColumnPatternFromNodeTree();
    std::shared_ptr<PickerTextProperties> CreateDefaultPickerTextProperties();
    std::shared_ptr<TextPickerSettingData> CreateDefaultTextPickerSettingData();
    RefPtr<FrameNode> FindContentRowNodeTree(const RefPtr<FrameNode>& dialogNode);
    void SetColumnNodeIdealSize();

private:
    RefPtr<FrameNode> textPickerNode_;
};

void TextPickerColumnExtendTestNg::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrent();
}

void TextPickerColumnExtendTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void TextPickerColumnExtendTestNg::SetUp()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        return GetTheme(type);
    });
    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([](ThemeType type, int32_t themeScopeId) -> RefPtr<Theme> { return GetTheme(type); });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void TextPickerColumnExtendTestNg::TearDown()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    textPickerNode_ = nullptr;
    ClearOldNodes(); // Each testcase will create new list at begin
}

RefPtr<FrameNode> TextPickerColumnExtendTestNg::GetOrCreateTextPickerFrameNodeTree()
{
    if (!textPickerNode_) {
        ResetElmtId();
        ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(GetElmtId());
        auto pipeline = MockPipelineContext::GetCurrent();
        CHECK_NULL_RETURN(pipeline, nullptr);
        auto theme = pipeline->GetTheme<PickerTheme>();
        TextPickerModelNG::GetInstance()->Create(theme, TEXT);
        textPickerNode_ = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    }
    return textPickerNode_;
}

RefPtr<TextPickerColumnPattern> TextPickerColumnExtendTestNg::GetTextPickerColumnPatternFromNodeTree()
{
    auto textPickerNode = GetOrCreateTextPickerFrameNodeTree();
    CHECK_NULL_RETURN(textPickerNode, nullptr);
    auto stackNode = textPickerNode->GetLastChild();
    CHECK_NULL_RETURN(stackNode, nullptr);
    auto columnBlendNode = stackNode->GetLastChild();
    CHECK_NULL_RETURN(columnBlendNode, nullptr);
    auto textPickerColumnNode = AceType::DynamicCast<FrameNode>(columnBlendNode->GetLastChild());
    CHECK_NULL_RETURN(textPickerColumnNode, nullptr);
    return textPickerColumnNode->GetPattern<TextPickerColumnPattern>();
}

void TextPickerColumnExtendTestNg::SetColumnNodeIdealSize()
{
    CHECK_NULL_VOID(textPickerNode_);
    auto stackNode = AceType::DynamicCast<FrameNode>(textPickerNode_->GetFirstChild());
    CHECK_NULL_VOID(stackNode);
    auto textPickerLayoutProperty = textPickerNode_->GetLayoutProperty<TextPickerLayoutProperty>();
    CHECK_NULL_VOID(textPickerLayoutProperty);
    auto stackLayoutProperty = stackNode->GetLayoutProperty();
    CHECK_NULL_VOID(stackLayoutProperty);

    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.minSize = SizeF(0, 0);
    layoutConstraintSize.maxSize = SizeF(MAX_WIDTH, MAX_HEIGHT);
    layoutConstraintSize.selfIdealSize.SetWidth(COMPONENT_WIDTH);
    layoutConstraintSize.selfIdealSize.SetHeight(COMPONENT_HEIGHT);
    textPickerLayoutProperty->UpdateLayoutConstraint(layoutConstraintSize);
    textPickerLayoutProperty->UpdateContentConstraint();

    layoutConstraintSize.parentIdealSize.SetWidth(COMPONENT_WIDTH);
    layoutConstraintSize.parentIdealSize.SetHeight(COMPONENT_HEIGHT);
    stackLayoutProperty->UpdateLayoutConstraint(layoutConstraintSize);
    stackLayoutProperty->UpdateContentConstraint();
}

std::shared_ptr<PickerTextProperties> TextPickerColumnExtendTestNg::CreateDefaultPickerTextProperties()
{
    auto properties = std::make_shared<PickerTextProperties>();
    properties->disappearTextStyle_.textColor = Color::RED;
    properties->disappearTextStyle_.fontSize = Dimension(FONT_SIZE_10);
    properties->disappearTextStyle_.fontWeight = Ace::FontWeight::BOLD;

    properties->normalTextStyle_.textColor = Color::RED;
    properties->normalTextStyle_.fontSize = Dimension(FONT_SIZE_10);
    properties->normalTextStyle_.fontWeight = Ace::FontWeight::BOLD;

    properties->selectedTextStyle_.textColor = Color::RED;
    properties->selectedTextStyle_.fontSize = Dimension(FONT_SIZE_10);
    properties->normalTextStyle_.fontWeight = Ace::FontWeight::BOLD;
    return properties;
}

std::shared_ptr<TextPickerSettingData> TextPickerColumnExtendTestNg::CreateDefaultTextPickerSettingData()
{
    auto settingData = std::make_shared<TextPickerSettingData>();
    settingData->columnKind = MIXTURE;
    settingData->height = Dimension(FONT_SIZE_10);
    auto properties = CreateDefaultPickerTextProperties();
    if (properties) {
        settingData->properties = *properties;
    }
    settingData->rangeVector = { { "", "1" }, { "", "2" }, { "", "3" } };
    settingData->selected = 0;
    return settingData;
}

RefPtr<FrameNode> TextPickerColumnExtendTestNg::FindContentRowNodeTree(const RefPtr<FrameNode>& dialogNode)
{
    CHECK_NULL_RETURN(dialogNode, nullptr);
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    CHECK_NULL_RETURN(dialogPattern, nullptr);
    auto customNode = dialogPattern->GetCustomNode();
    CHECK_NULL_RETURN(customNode, nullptr);
    auto children = customNode->GetChildren();
    for (auto it = children.rbegin(); it != children.rend(); ++it) {
        auto targetNode = AceType::DynamicCast<FrameNode>(*it);
        if (targetNode && targetNode->GetTag() == V2::COLUMN_ETS_TAG) {
            auto pattern = targetNode->GetPattern<LinearLayoutPattern>();
            if (pattern && !pattern->GetIsVertical()) {
                return targetNode;
            }
        }
    }
    return nullptr;
}

/**
 * @tc.name: PlayTossAnimation001
 * @tc.desc: Test PlayTossAnimation scene.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnExtendTestNg, PlayTossAnimation001, TestSize.Level1)
{
    /**
     * @tc.step: step1. create frameNode tree and init TextPickerOptionProperty.
     */
    auto textPickerColumnPattern = GetTextPickerColumnPatternFromNodeTree();
    ASSERT_NE(textPickerColumnPattern, nullptr);
    auto toss = textPickerColumnPattern->GetToss();
    ASSERT_NE(toss, nullptr);
    textPickerColumnPattern->OnModifyDone();
    textPickerColumnPattern->SetMainVelocity(500);

    /**
     * @tc.step: step2. Drag to create toss AnimatableProperty and fire finish callback.
     * @tc.expected: AnimatableProperty is not NULL
     */
    GestureEvent eventInfo;
    textPickerColumnPattern->HandleDragStart(eventInfo);
    toss->timeStart_ = toss->GetCurrentTime();
    eventInfo.SetGlobalPoint(Point(0, 5.0));
    textPickerColumnPattern->HandleDragMove(eventInfo);
    double dragTimeStep = 3.0;
    toss->timeEnd_ = toss->GetCurrentTime() + dragTimeStep;
    textPickerColumnPattern->HandleDragEnd();
    auto nodeAnimatablePropertyFloat = toss->GetTossNodeAnimation();
    ASSERT_NE(nodeAnimatablePropertyFloat, nullptr);
    auto property = AceType::DynamicCast<AnimatablePropertyFloat>(nodeAnimatablePropertyFloat->GetProperty());
    ASSERT_NE(property, nullptr);
    auto callback = property->GetUpdateCallback();
    ASSERT_NE(callback, nullptr);
    callback(1.0f);

    /**
     * @tc.step: step3. Drag anagin to stop last toss animation and excute current animation.
     * @tc.expected: tossStatus is false
     */
    textPickerColumnPattern->HandleDragStart(eventInfo);
    toss->timeStart_ = toss->GetCurrentTime();
    eventInfo.SetGlobalPoint(Point(0, 10.0));
    textPickerColumnPattern->HandleDragMove(eventInfo);
    toss->timeEnd_ = toss->GetCurrentTime() + dragTimeStep;
    textPickerColumnPattern->HandleDragEnd();
    EXPECT_FALSE(textPickerColumnPattern->GetTossStatus());
}

/**
 * @tc.name: SetColumnWidths001
 * @tc.desc: Test SetColumnWidths when the unit is PERCENT, PX or VP.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnExtendTestNg, SetColumnWidths001, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto textPickerNode = GetOrCreateTextPickerFrameNodeTree();
    ASSERT_NE(textPickerNode, nullptr);
    auto textPickerPattern = textPickerNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    auto pickerProperty = textPickerNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    auto textPickerColumnPattern = GetTextPickerColumnPatternFromNodeTree();
    ASSERT_NE(textPickerColumnPattern, nullptr);
    auto columnNode = textPickerColumnPattern->GetHost();
    ASSERT_NE(columnNode, nullptr);
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(columnNode, columnNode->GetGeometryNode(), pickerProperty);
    auto textPickerLayoutAlgorithm = textPickerColumnPattern->CreateLayoutAlgorithm();

    std::vector<Dimension> width;
    width.emplace_back(Dimension(50.0f, DimensionUnit::PERCENT));
    TextPickerModelNG::GetInstance()->SetColumnWidths(width);
    textPickerPattern->OnModifyDone();
    SetColumnNodeIdealSize();
    textPickerLayoutAlgorithm->Measure(&layoutWrapper);
    EXPECT_EQ(textPickerPattern->GetColumnWidths().at(0).Value(), COMPONENT_WIDTH / 2.0f);

    width.pop_back();
    width.emplace_back(Dimension(10.0f, DimensionUnit::PX));
    TextPickerModelNG::GetInstance()->SetColumnWidths(width);
    textPickerPattern->OnModifyDone();
    SetColumnNodeIdealSize();
    textPickerLayoutAlgorithm->Measure(&layoutWrapper);
    EXPECT_EQ(textPickerPattern->GetColumnWidths().at(0).Value(), 10.0f);

    width.pop_back();
    width.emplace_back(Dimension(10.0f, DimensionUnit::VP));
    TextPickerModelNG::GetInstance()->SetColumnWidths(width);
    textPickerPattern->OnModifyDone();
    SetColumnNodeIdealSize();
    textPickerLayoutAlgorithm->Measure(&layoutWrapper);
    EXPECT_EQ(textPickerPattern->GetColumnWidths().at(0).Value(), Dimension(10.0f, DimensionUnit::VP).ConvertToPx());
}

/**
 * @tc.name: SetColumnWidths002
 * @tc.desc: Test SetColumnWidths when the unit is LPX, FP or the width is negative.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnExtendTestNg, SetColumnWidths002, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto textPickerNode = GetOrCreateTextPickerFrameNodeTree();
    ASSERT_NE(textPickerNode, nullptr);
    auto textPickerPattern = textPickerNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    auto pickerProperty = textPickerNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    auto textPickerColumnPattern = GetTextPickerColumnPatternFromNodeTree();
    ASSERT_NE(textPickerColumnPattern, nullptr);
    auto columnNode = textPickerColumnPattern->GetHost();
    ASSERT_NE(columnNode, nullptr);
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(columnNode, columnNode->GetGeometryNode(), pickerProperty);
    auto textPickerLayoutAlgorithm = textPickerColumnPattern->CreateLayoutAlgorithm();

    std::vector<Dimension> width;
    width.emplace_back(Dimension(10.0f, DimensionUnit::LPX));
    TextPickerModelNG::GetInstance()->SetColumnWidths(width);
    textPickerPattern->OnModifyDone();
    SetColumnNodeIdealSize();
    textPickerLayoutAlgorithm->Measure(&layoutWrapper);
    EXPECT_EQ(textPickerPattern->GetColumnWidths().at(0).Value(), Dimension(10.0f, DimensionUnit::LPX).ConvertToPx());

    width.pop_back();
    width.emplace_back(Dimension(10.0f, DimensionUnit::FP));
    TextPickerModelNG::GetInstance()->SetColumnWidths(width);
    textPickerPattern->OnModifyDone();
    SetColumnNodeIdealSize();
    textPickerLayoutAlgorithm->Measure(&layoutWrapper);
    EXPECT_EQ(textPickerPattern->GetColumnWidths().at(0).Value(), Dimension(10.0f, DimensionUnit::FP).ConvertToPx());

    width.pop_back();
    width.emplace_back(Dimension(-10.0f, DimensionUnit::PX));
    TextPickerModelNG::GetInstance()->SetColumnWidths(width);
    textPickerPattern->OnModifyDone();
    SetColumnNodeIdealSize();
    textPickerLayoutAlgorithm->Measure(&layoutWrapper);
    EXPECT_EQ(textPickerPattern->GetColumnWidths().at(0).Value(), COMPONENT_WIDTH);
}

/**
 * @tc.name: SetColumnWidths003
 * @tc.desc: Test SetColumnWidths when width.size() is less than the number of options.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnExtendTestNg, SetColumnWidths003, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto textPickerNode = GetOrCreateTextPickerFrameNodeTree();
    ASSERT_NE(textPickerNode, nullptr);
    auto textPickerPattern = textPickerNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    auto pickerProperty = textPickerNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    auto textPickerColumnPattern = GetTextPickerColumnPatternFromNodeTree();
    ASSERT_NE(textPickerColumnPattern, nullptr);
    auto columnNode = textPickerColumnPattern->GetHost();
    ASSERT_NE(columnNode, nullptr);
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(columnNode, columnNode->GetGeometryNode(), pickerProperty);
    auto textPickerLayoutAlgorithm = textPickerColumnPattern->CreateLayoutAlgorithm();

    std::vector<Dimension> width;
    TextPickerModelNG::GetInstance()->SetColumnWidths(width);
    textPickerPattern->OnModifyDone();
    SetColumnNodeIdealSize();
    textPickerLayoutAlgorithm->Measure(&layoutWrapper);
    EXPECT_EQ(textPickerPattern->GetColumnWidths().at(0).Value(), COMPONENT_WIDTH);
}

/**
 * @tc.name: SetColumnWidths004
 * @tc.desc: Test SetColumnWidths when width.size() is greater than the number of options.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnExtendTestNg, SetColumnWidths004, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto textPickerNode = GetOrCreateTextPickerFrameNodeTree();
    ASSERT_NE(textPickerNode, nullptr);
    auto textPickerPattern = textPickerNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    auto pickerProperty = textPickerNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    auto textPickerColumnPattern = GetTextPickerColumnPatternFromNodeTree();
    ASSERT_NE(textPickerColumnPattern, nullptr);
    auto columnNode = textPickerColumnPattern->GetHost();
    ASSERT_NE(columnNode, nullptr);
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(columnNode, columnNode->GetGeometryNode(), pickerProperty);
    auto textPickerLayoutAlgorithm = textPickerColumnPattern->CreateLayoutAlgorithm();

    std::vector<Dimension> width;
    width.emplace_back(Dimension(COMPONENT_WIDTH, DimensionUnit::PX));
    width.emplace_back(Dimension(30.0f, DimensionUnit::PX));
    TextPickerModelNG::GetInstance()->SetColumnWidths(width);
    textPickerPattern->OnModifyDone();
    SetColumnNodeIdealSize();
    textPickerLayoutAlgorithm->Measure(&layoutWrapper);
    EXPECT_EQ(textPickerPattern->GetColumnWidths().at(0).Value(), COMPONENT_WIDTH);
}

/**
 * @tc.name: SetColumnWidths005
 * @tc.desc: Test SetColumnWidths when there are multiple options.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnExtendTestNg, SetColumnWidths005, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TextPickerModelNG::GetInstance()->MultiInit(theme);
    TextPickerModelNG::GetInstance()->SetIsCascade(true);
    std::vector<NG::TextCascadePickerOptions> options;
    NG::TextCascadePickerOptions options1;
    options1.rangeResult = { "11", "12", "13" };
    options.emplace_back(options1);
    NG::TextCascadePickerOptions options2;
    options2.rangeResult = { "21", "22", "23" };
    options.emplace_back(options2);
    NG::TextCascadePickerOptions options3;
    options3.rangeResult = { "31", "32", "33" };
    options.emplace_back(options3);
    TextPickerModelNG::GetInstance()->SetColumns(options);

    auto textPickerNode = GetOrCreateTextPickerFrameNodeTree();
    ASSERT_NE(textPickerNode, nullptr);
    auto textPickerPattern = textPickerNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    auto pickerProperty = textPickerNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    auto textPickerColumnPattern = GetTextPickerColumnPatternFromNodeTree();
    ASSERT_NE(textPickerColumnPattern, nullptr);
    auto columnNode = textPickerColumnPattern->GetHost();
    ASSERT_NE(columnNode, nullptr);
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(columnNode, columnNode->GetGeometryNode(), pickerProperty);
    auto textPickerLayoutAlgorithm = textPickerColumnPattern->CreateLayoutAlgorithm();

    std::vector<Dimension> width;
    width.emplace_back(Dimension(15.0f, DimensionUnit::PX));
    width.emplace_back(Dimension(15.0f, DimensionUnit::PX));
    width.emplace_back(Dimension(15.0f, DimensionUnit::PX));
    TextPickerModelNG::GetInstance()->SetColumnWidths(width);
    textPickerPattern->OnModifyDone();
    SetColumnNodeIdealSize();
    textPickerLayoutAlgorithm->Measure(&layoutWrapper);
    auto widthSize = textPickerPattern->GetColumnWidths().size();
    EXPECT_EQ(widthSize, 3);
    EXPECT_EQ(textPickerPattern->GetColumnWidths().at(0).Value(), 15.0f);
    EXPECT_EQ(textPickerPattern->GetColumnWidths().at(1).Value(), 15.0f);
    EXPECT_EQ(textPickerPattern->GetColumnWidths().at(2).Value(), 15.0f);
}

/**
 * @tc.name: PerformLayout001
 * @tc.desc: Test performlayout when user set GradientFont.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnExtendTestNg, PerformLayout001, TestSize.Level1)
{
    /**
     * @tc.step: step1. create frameNode tree and init update layoutProperty.
     */
    auto textPickerNode = GetOrCreateTextPickerFrameNodeTree();
    ASSERT_NE(textPickerNode, nullptr);
    auto textPickerPattern = textPickerNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    auto pickerProperty = textPickerNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    auto textPickerColumnPattern = GetTextPickerColumnPatternFromNodeTree();
    ASSERT_NE(textPickerColumnPattern, nullptr);
    auto columnNode = textPickerColumnPattern->GetHost();
    ASSERT_NE(columnNode, nullptr);
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);

    context->SetFontScale(2.0f);
    pickerProperty->UpdateDefaultPickerItemHeight(DEFAULT_PICKER_ITEM_HEIGHT);
    pickerProperty->UpdateGradientHeight(DEFAULT_GRADIENT_HEIGHT);
    auto pickerTextProperties = CreateDefaultPickerTextProperties();
    textPickerPattern->SetTextProperties(*pickerTextProperties);
    textPickerPattern->SetGradientHeight(DEFAULT_GRADIENT_HEIGHT);
    textPickerPattern->SetIsShowInDialog(true);
    textPickerPattern->OnModifyDone();
    textPickerColumnPattern->OnModifyDone();

    /**
     * @tc.step: step2. create layoutAlgorithm and performLayout.
     * @tc.expected: textPickColumn node size is rational.
     */
    SetColumnNodeIdealSize();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(columnNode, columnNode->GetGeometryNode(), pickerProperty);
    for (const auto& child : columnNode->GetChildren()) {
        auto childFrameNode = AceType::DynamicCast<FrameNode>(child);
        if (!childFrameNode) {
            continue;
        }
        RefPtr<LayoutWrapperNode> childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
            childFrameNode, childFrameNode->GetGeometryNode(), childFrameNode->GetLayoutProperty());
        layoutWrapper.AppendChild(childWrapper);
    }
    EXPECT_GT(layoutWrapper.GetTotalChildCount(), 0);
    auto textPickerLayoutAlgorithm = textPickerColumnPattern->CreateLayoutAlgorithm();
    textPickerLayoutAlgorithm->Measure(&layoutWrapper);
    textPickerLayoutAlgorithm->Layout(&layoutWrapper);
    EXPECT_FLOAT_EQ(layoutWrapper.GetGeometryNode()->GetFrameSize().Width(), COMPONENT_WIDTH);
}

/**
 * @tc.name: TextPickerDialogViewShow001
 * @tc.desc: Test TextPickerDialogView Show(column kind is MIXTURE) for API12.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnExtendTestNg, TextPickerDialogViewShow001, TestSize.Level1)
{
    /**
     * @tc.step: step1. Invoke show function to create dialog Node tree.
     */
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));

    auto func = [](const std::string& /* info */) {};
    std::map<std::string, NG::DialogTextEvent> dialogEvent;
    dialogEvent["changeId"] = func;
    dialogEvent["acceptId"] = func;
    dialogEvent["scrollStopId"] = func;

    int32_t cancelCallbackInfo = 0;
    auto cancelFunc = [&cancelCallbackInfo](
                          const GestureEvent& /* info */) { cancelCallbackInfo = ONCANCEL_CALLBACK_INFO; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;

    auto settingData = CreateDefaultTextPickerSettingData();
    ASSERT_NE(settingData, nullptr);
    DialogProperties dialogProperties;
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode =
        TextPickerDialogView::Show(dialogProperties, *settingData, buttonInfos, dialogEvent, dialogCancelEvent);

    /**
     * @tc.step: step2. Get cancel button node to mock onclick event.
     * @tc.expected: fire oncancel callback.
     */
    auto contentRow = FindContentRowNodeTree(dialogNode);
    ASSERT_NE(contentRow, nullptr);
    auto cancelButtonNode = AceType::DynamicCast<FrameNode>(contentRow->GetFirstChild());
    ASSERT_NE(cancelButtonNode, nullptr);

    auto focusHub = cancelButtonNode->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    auto gestureEventFunc = focusHub->GetOnClickCallback();
    ASSERT_NE(gestureEventFunc, nullptr);
    GestureEvent info;
    gestureEventFunc(info);
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(backupApiVersion));
    EXPECT_EQ(cancelCallbackInfo, ONCANCEL_CALLBACK_INFO);
}

/**
 * @tc.name: TextPickerDialogViewShow002
 * @tc.desc: Test TextPickerDialogView Show (textpicker user set options) for API12.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnExtendTestNg, TextPickerDialogViewShow002, TestSize.Level1)
{
    /**
     * @tc.step: step1. Invoke show function to create dialog Node tree.
     */
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    auto pipeline = PipelineContext::GetCurrentContextSafely();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetFontScale(2.0f);

    std::map<std::string, NG::DialogTextEvent> dialogEvent;
    int32_t cancelCallbackInfo = 0;
    auto cancelFunc = [&cancelCallbackInfo](
                          const GestureEvent& /* info */) { cancelCallbackInfo = ONCANCEL_CALLBACK_INFO; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;

    auto settingData = CreateDefaultTextPickerSettingData();
    ASSERT_NE(settingData, nullptr);
    settingData->options = { { { "11", "12", "13" }, {} }, { { "21", "22", "23" }, {} }, { { "31", "32", "33" }, {} } };
    DialogProperties dialogProperties;
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode =
        TextPickerDialogView::Show(dialogProperties, *settingData, buttonInfos, dialogEvent, dialogCancelEvent);

    /**
     * @tc.step: step2. Get all button nodes to mock onclick event.
     * @tc.expected: At last fire close callback.
     */
    auto contentRow = FindContentRowNodeTree(dialogNode);
    ASSERT_NE(contentRow, nullptr);
    for (const auto& child : contentRow->GetChildren()) {
        if (child && child->GetTag() == V2::BUTTON_ETS_TAG) {
            auto buttonNode = AceType::DynamicCast<FrameNode>(child);
            ASSERT_NE(buttonNode, nullptr);
            auto focusHub = buttonNode->GetOrCreateFocusHub();
            ASSERT_NE(focusHub, nullptr);
            auto gestureEventFunc = focusHub->GetOnClickCallback();
            ASSERT_NE(gestureEventFunc, nullptr);
            GestureEvent info;
            gestureEventFunc(info);
        }
    }
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(backupApiVersion));
    EXPECT_EQ(cancelCallbackInfo, ONCANCEL_CALLBACK_INFO);
}

/**
 * @tc.name: DialogViewConvertFontScaleValue001
 * @tc.desc: Test TextPickerDialogView ConvertFontScaleValue.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnExtendTestNg, DialogViewConvertFontScaleValue001, TestSize.Level1)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    Dimension fontSizeValue = 20.0_px;
    Dimension fontSizeLimit = 40.0_vp;

    pipeline->SetFollowSystem(true);
    pipeline->SetMaxAppFontScale(0.0f);
    auto fontSizeValueResult = TextPickerDialogView::ConvertFontScaleValue(fontSizeValue, fontSizeLimit, false);
    EXPECT_EQ(fontSizeValueResult.Value(), 10.0);

    pipeline->SetFollowSystem(false);
    fontSizeValueResult = TextPickerDialogView::ConvertFontScaleValue(fontSizeValue, fontSizeLimit, false);
    EXPECT_EQ(fontSizeValueResult.Value(), 10.0);

    pipeline->SetFollowSystem(true);
    pipeline->SetMaxAppFontScale(2.0f);
    fontSizeValueResult = TextPickerDialogView::ConvertFontScaleValue(fontSizeValue, fontSizeLimit, false);
    EXPECT_EQ(fontSizeValueResult.Value(), 20.0);

    pipeline->rootHeight_ = 700.0;
    pipeline->fontScale_ = 2.0f;
    fontSizeValueResult = TextPickerDialogView::ConvertFontScaleValue(fontSizeValue, fontSizeLimit, true);
    EXPECT_EQ(fontSizeValueResult.Value(), 20.0);

    fontSizeLimit = 60.0_vp;
    fontSizeValueResult = TextPickerDialogView::ConvertFontScaleValue(fontSizeValue, fontSizeLimit, true);
    EXPECT_EQ(fontSizeValueResult.Value(), 20.0);

    fontSizeValueResult = TextPickerDialogView::ConvertFontScaleValue(fontSizeValue, fontSizeLimit, false);
    EXPECT_EQ(fontSizeValueResult.Value(), 20.0);

    pipeline->fontScale_ = 4.0f;
    pipeline->SetMaxAppFontScale(4.0f);
    fontSizeValueResult = TextPickerDialogView::ConvertFontScaleValue(fontSizeValue, fontSizeLimit, false);
    EXPECT_EQ(fontSizeValueResult.Value(), 12.5);

    pipeline->SetFollowSystem(false);
    fontSizeValueResult = TextPickerDialogView::ConvertFontScaleValue(fontSizeValue, fontSizeLimit, false);
    EXPECT_EQ(fontSizeValueResult.Value(), 5.0);

    pipeline->fontScale_ = 1.0f;
    fontSizeValueResult = TextPickerDialogView::ConvertFontScaleValue(fontSizeValue, fontSizeLimit, false);
    EXPECT_EQ(fontSizeValueResult.Value(), 20.0);

    pipeline->fontScale_ = 0.0f;
    fontSizeValueResult = TextPickerDialogView::ConvertFontScaleValue(fontSizeValue, fontSizeLimit, false);
    EXPECT_EQ(fontSizeValueResult.Value(), 20.0);
}

/**
 * @tc.name: DialogViewConvertFontSizeLimit001
 * @tc.desc: Test TextPickerDialogView ConvertFontSizeLimit.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnExtendTestNg, DialogViewConvertFontSizeLimit001, TestSize.Level1)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);

    Dimension fontSizeValue = 20.0_px;
    Dimension fontSizeLimit = 0.0_vp;
    pipeline->fontScale_ = 0.0f;

    auto fontSizeValueResult = TextPickerDialogView::ConvertFontSizeLimit(fontSizeValue, fontSizeLimit, true);
    EXPECT_EQ(fontSizeValueResult.Value(), 20.0);
}

/*
 * @tc.name: UpdateConfirmButtonTextLayoutProperty001
 * @tc.desc: Test TextPickerDialogView UpdateConfirmButtonTextLayoutProperty
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnExtendTestNg, UpdateConfirmButtonTextLayoutProperty001, TestSize.Level1)
{
    auto textConfirmNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());

    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    ASSERT_NE(pickerTheme, nullptr);
    auto fontSize = pickerTheme->GetOptionStyle(false, false).GetFontSize();

    pipeline->SetFollowSystem(true);
    pipeline->rootHeight_ = 700.0;
    pipeline->fontScale_ = 2.0f;
    pipeline->SetMaxAppFontScale(2.0f);

    TextPickerDialogView::UpdateConfirmButtonTextLayoutProperty(textConfirmNode, pickerTheme);

    auto textLayoutProperty = textConfirmNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_EQ(textLayoutProperty->GetFontSize(), fontSize);
}

/*
 * @tc.name: UpdateCancelButtonTextLayoutProperty001
 * @tc.desc: Test TextPickerDialogView UpdateCancelButtonTextLayoutProperty
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnExtendTestNg, UpdateCancelButtonTextLayoutProperty001, TestSize.Level1)
{
    auto textCancelNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());

    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    ASSERT_NE(pickerTheme, nullptr);
    auto fontSize = pickerTheme->GetOptionStyle(false, false).GetFontSize();

    pipeline->SetFollowSystem(true);
    pipeline->rootHeight_ = 700.0;
    pipeline->fontScale_ = 2.0f;
    pipeline->SetMaxAppFontScale(2.0f);

    TextPickerDialogView::UpdateCancelButtonTextLayoutProperty(textCancelNode, pickerTheme);

    auto textCancelLayoutProperty = textCancelNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textCancelLayoutProperty, nullptr);
    EXPECT_EQ(textCancelLayoutProperty->GetFontSize(), fontSize);
}

/*
 * @tc.name: UpdateButtonStyleAndRole001
 * @tc.desc: Test TextPickerDialogView UpdateButtonStyleAndRole
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnExtendTestNg, UpdateButtonStyleAndRole001, TestSize.Level1)
{
    auto buttonConfirmNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });

    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);

    auto buttonTheme = pipeline->GetTheme<ButtonTheme>();
    ASSERT_NE(buttonTheme, nullptr);

    std::vector<ButtonInfo> buttonInfos;

    auto buttonConfirmLayoutProperty = buttonConfirmNode->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(buttonConfirmLayoutProperty, nullptr);

    auto buttonConfirmRenderContext = buttonConfirmNode->GetRenderContext();
    ASSERT_NE(buttonConfirmRenderContext, nullptr);

    TextPickerDialogView::UpdateButtonStyleAndRole(
        buttonInfos, ACCEPT_BUTTON_INDEX, buttonConfirmLayoutProperty, buttonConfirmRenderContext, buttonTheme);
    EXPECT_EQ(buttonInfos.size(), ACCEPT_BUTTON_INDEX);

    ButtonInfo info;
    info.buttonStyle = ButtonStyleMode::NORMAL;
    buttonInfos.push_back(info);

    TextPickerDialogView::UpdateButtonStyleAndRole(
        buttonInfos, ACCEPT_BUTTON_INDEX, buttonConfirmLayoutProperty, buttonConfirmRenderContext, buttonTheme);
    EXPECT_EQ(buttonConfirmLayoutProperty->GetButtonStyle(), ButtonStyleMode::NORMAL);
}

/**
 * @tc.name: GetGradientPercent001
 * @tc.desc: Test GetGradientPercent.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnExtendTestNg, GetGradientPercent001, TestSize.Level1)
{
    /**
     * @tc.step: step1. create frameNode tree.
     */
    auto textPickerNode = GetOrCreateTextPickerFrameNodeTree();
    ASSERT_NE(textPickerNode, nullptr);
    auto textPickerPattern = textPickerNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    auto pickerProperty = textPickerNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    auto textPickerColumnPattern = GetTextPickerColumnPatternFromNodeTree();
    ASSERT_NE(textPickerColumnPattern, nullptr);
    auto columnNode = textPickerColumnPattern->GetHost();
    ASSERT_NE(columnNode, nullptr);

    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    ASSERT_NE(pickerTheme, nullptr);

    auto layoutAlgorithm = textPickerColumnPattern->CreateLayoutAlgorithm();
    ASSERT_NE(layoutAlgorithm, nullptr);
    auto textPickerLayoutAlgorithm = AceType::DynamicCast<TextPickerLayoutAlgorithm>(layoutAlgorithm);
    ASSERT_NE(textPickerLayoutAlgorithm, nullptr);

    auto defaultPickerItemHeightValue = Dimension(1.0, DimensionUnit::LPX);
    textPickerLayoutAlgorithm->UpdateDefaultPickerItemHeightLPX(textPickerNode, defaultPickerItemHeightValue);

    SizeF frameSize = { 1.0f, 1.0f };
    auto value = Dimension(-1.0);

    textPickerPattern->SetGradientHeight(value);
    auto gradientPercent = textPickerLayoutAlgorithm->GetGradientPercent(
        pickerProperty, textPickerPattern, frameSize, pickerTheme);
    EXPECT_EQ(gradientPercent, 10.0f);

    value = Dimension(1.0, DimensionUnit::PERCENT);
    textPickerPattern->SetGradientHeight(value);
    pickerProperty->UpdateGradientHeight(value);
    frameSize.SetHeight(100.0f);

    gradientPercent = textPickerLayoutAlgorithm->GetGradientPercent(
        pickerProperty, textPickerPattern, frameSize, pickerTheme);
    EXPECT_EQ(gradientPercent, 0.5f);
}

/**
 * @tc.name: OnDetachFromFrameNodeTest001
 * @tc.desc: Test OnDetachFromFrameNode haptic->stop && UnregisterWindowStateChangedCallback.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnExtendTestNg, OnDetachFromFrameNodeTest001, TestSize.Level1)
{
    auto textPickerColumnPattern = GetTextPickerColumnPatternFromNodeTree();
    ASSERT_NE(textPickerColumnPattern, nullptr);
    auto columnNode = textPickerColumnPattern->GetHost();
    ASSERT_NE(columnNode, nullptr);
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    FrameNode& ref = *columnNode;
    auto pipeline = columnNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    auto onWindowStateChangedCallbacks = pipeline->onWindowStateChangedCallbacks_.size();
    textPickerColumnPattern->OnDetachFromFrameNode(&ref);
    EXPECT_EQ(pipeline->onWindowStateChangedCallbacks_.size(), onWindowStateChangedCallbacks - 1);
}

/**
 * @tc.name: OnDetachFromFrameNodeTest002
 * @tc.desc: Test OnDetachFromFrameNode  haptic->stop && UnregisterWindowStateChangedCallback. .
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnExtendTestNg, OnDetachFromFrameNodeTest002, TestSize.Level1)
{
    auto textPickerColumnPattern = GetTextPickerColumnPatternFromNodeTree();
    ASSERT_NE(textPickerColumnPattern, nullptr);
    auto columnNode = textPickerColumnPattern->GetHost();
    ASSERT_NE(columnNode, nullptr);
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    FrameNode& ref = *columnNode;
    textPickerColumnPattern->hapticController_ = PickerAudioHapticFactory::GetInstance();
    auto pipeline = columnNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    auto onWindowStateChangedCallbacks = pipeline->onWindowStateChangedCallbacks_.size();
    textPickerColumnPattern->OnDetachFromFrameNode(&ref);
    EXPECT_EQ(pipeline->onWindowStateChangedCallbacks_.size(), onWindowStateChangedCallbacks - 1);
}

/**
 * @tc.name: InitHapticControllerTest001
 * @tc.desc: Test InitHapticController.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnExtendTestNg, InitHapticControllerTest001, TestSize.Level1)
{
    auto textPickerColumnPattern = GetTextPickerColumnPatternFromNodeTree();
    ASSERT_NE(textPickerColumnPattern, nullptr);
    auto columnNode = textPickerColumnPattern->GetHost();
    ASSERT_NE(columnNode, nullptr);
    textPickerColumnPattern->InitHapticController(columnNode);
    EXPECT_EQ(textPickerColumnPattern->hapticController_, nullptr);
}

/**
 * @tc.name: InitHapticControllerTest002
 * @tc.desc: Test InitHapticController.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnExtendTestNg, InitHapticControllerTest002, TestSize.Level1)
{
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));
    auto textPickerColumnPattern = GetTextPickerColumnPatternFromNodeTree();
    ASSERT_NE(textPickerColumnPattern, nullptr);
    auto columnNode = textPickerColumnPattern->GetHost();
    ASSERT_NE(columnNode, nullptr);
    textPickerColumnPattern->InitHapticController(columnNode);
    EXPECT_NE(textPickerColumnPattern->hapticController_, nullptr);
}

/**
 * @tc.name: InitHapticControllerTest003
 * @tc.desc: Test InitHapticController.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnExtendTestNg, InitHapticControllerTest003, TestSize.Level1)
{
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));
    auto textPickerColumnPattern = GetTextPickerColumnPatternFromNodeTree();
    ASSERT_NE(textPickerColumnPattern, nullptr);
    auto columnNode = textPickerColumnPattern->GetHost();
    ASSERT_NE(columnNode, nullptr);
    textPickerColumnPattern->hapticController_ = PickerAudioHapticFactory::GetInstance();
    textPickerColumnPattern->InitHapticController(columnNode);
    EXPECT_TRUE(textPickerColumnPattern->isEnableHaptic_);
}

/**
 * @tc.name: InitHapticControllerTest004
 * @tc.desc: Test InitHapticController.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnExtendTestNg, InitHapticControllerTest004, TestSize.Level1)
{
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));
    auto textPickerColumnPattern = GetTextPickerColumnPatternFromNodeTree();
    ASSERT_NE(textPickerColumnPattern, nullptr);
    auto columnNode = textPickerColumnPattern->GetHost();
    ASSERT_NE(columnNode, nullptr);
    auto blendNode = AceType::DynamicCast<FrameNode>(columnNode->GetParent());
    ASSERT_NE(blendNode, nullptr);
    auto stackNode = AceType::DynamicCast<FrameNode>(blendNode->GetParent());
    ASSERT_NE(stackNode, nullptr);
    auto parentNode = AceType::DynamicCast<FrameNode>(stackNode->GetParent());
    ASSERT_NE(parentNode, nullptr);
    auto textPickerPattern = parentNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    textPickerPattern->isEnableHaptic_ = false;
    textPickerColumnPattern->hapticController_ = PickerAudioHapticFactory::GetInstance();
    textPickerColumnPattern->InitHapticController(columnNode);
    EXPECT_FALSE(textPickerColumnPattern->isEnableHaptic_);
}

/**
 * @tc.name: InitHapticControllerTest005
 * @tc.desc: Test InitHapticController.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnExtendTestNg, InitHapticControllerTest005, TestSize.Level1)
{
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));
    auto textPickerColumnPattern = GetTextPickerColumnPatternFromNodeTree();
    ASSERT_NE(textPickerColumnPattern, nullptr);
    auto columnNode = textPickerColumnPattern->GetHost();
    ASSERT_NE(columnNode, nullptr);
    auto blendNode = AceType::DynamicCast<FrameNode>(columnNode->GetParent());
    ASSERT_NE(blendNode, nullptr);
    auto stackNode = AceType::DynamicCast<FrameNode>(blendNode->GetParent());
    ASSERT_NE(stackNode, nullptr);
    auto parentNode = AceType::DynamicCast<FrameNode>(stackNode->GetParent());
    ASSERT_NE(parentNode, nullptr);
    auto textPickerPattern = parentNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    textPickerPattern->isEnableHaptic_ = false;
    textPickerColumnPattern->hapticController_ = nullptr;
    textPickerColumnPattern->InitHapticController(columnNode);
    EXPECT_EQ(textPickerColumnPattern->hapticController_, nullptr);
}

/**
 * @tc.name: RegisterWindowStateChangedCallbackTest001
 * @tc.desc: Test RegisterWindowStateChangedCallback & UnregisterWindowStateChangedCallback
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnExtendTestNg, RegisterWindowStateChangedCallbackTest001, TestSize.Level1)
{
    auto textPickerColumnPattern = GetTextPickerColumnPatternFromNodeTree();
    ASSERT_NE(textPickerColumnPattern, nullptr);
    auto columnNode = textPickerColumnPattern->GetHost();
    ASSERT_NE(columnNode, nullptr);
    auto pipeline = columnNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    pipeline->onWindowStateChangedCallbacks_.clear();
    textPickerColumnPattern->RegisterWindowStateChangedCallback();
    EXPECT_EQ(pipeline->onWindowStateChangedCallbacks_.size(), 1);
    textPickerColumnPattern->UnregisterWindowStateChangedCallback(columnNode.rawPtr_);
    EXPECT_EQ(pipeline->onWindowStateChangedCallbacks_.size(), 0);
}

/**
 * @tc.name: OnWindowHideTest001
 * @tc.desc: Test OnWindowHide &  OnWindowShow
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnExtendTestNg, OnWindowHideTest001, TestSize.Level1)
{
    auto textPickerColumnPattern = GetTextPickerColumnPatternFromNodeTree();
    ASSERT_NE(textPickerColumnPattern, nullptr);
    textPickerColumnPattern->OnWindowHide();
    EXPECT_FALSE(textPickerColumnPattern->isShow_);
    textPickerColumnPattern->hapticController_ = PickerAudioHapticFactory::GetInstance();
    textPickerColumnPattern->OnWindowHide();
    EXPECT_FALSE(textPickerColumnPattern->isShow_);
    textPickerColumnPattern->OnWindowShow();
    EXPECT_TRUE(textPickerColumnPattern->isShow_);
}

/**
 * @tc.name: HandleDragEndTest001
 * @tc.desc: Test HandleDragEnd
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnExtendTestNg, HandleDragEndTest001, TestSize.Level1)
{
    auto textPickerColumnPattern = GetTextPickerColumnPatternFromNodeTree();
    ASSERT_NE(textPickerColumnPattern, nullptr);
    textPickerColumnPattern->HandleDragEnd();
    EXPECT_FALSE(textPickerColumnPattern->pressed_);
    textPickerColumnPattern->hapticController_ = PickerAudioHapticFactory::GetInstance();
    textPickerColumnPattern->HandleDragEnd();
    EXPECT_FALSE(textPickerColumnPattern->pressed_);
}

/**
 * @tc.name: TossAnimationStopedTest001
 * @tc.desc: Test TossAnimationStoped
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnExtendTestNg, TossAnimationStopedTest001, TestSize.Level1)
{
    auto textPickerColumnPattern = GetTextPickerColumnPatternFromNodeTree();
    ASSERT_NE(textPickerColumnPattern, nullptr);
    textPickerColumnPattern->TossAnimationStoped();
    EXPECT_EQ(textPickerColumnPattern->yLast_, 0.0f);
    textPickerColumnPattern->hapticController_ = PickerAudioHapticFactory::GetInstance();
    textPickerColumnPattern->TossAnimationStoped();
    EXPECT_EQ(textPickerColumnPattern->yLast_, 0.0f);
}

/**
 * @tc.name: UpdateColumnChildPositionTest001
 * @tc.desc: Test UpdateColumnChildPosition
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnExtendTestNg, UpdateColumnChildPositionTest001, TestSize.Level1)
{
    auto textPickerColumnPattern = GetTextPickerColumnPatternFromNodeTree();
    ASSERT_NE(textPickerColumnPattern, nullptr);
    double offset = 50.0;
    textPickerColumnPattern->UpdateColumnChildPosition(offset);
    EXPECT_EQ(textPickerColumnPattern->yLast_, 50.0f);
    textPickerColumnPattern->hapticController_ = PickerAudioHapticFactory::GetInstance();
    textPickerColumnPattern->isShow_ = false;
    auto pickerAudioHapticController =
        std::static_pointer_cast<MockPickerAudioHapticImpl>(textPickerColumnPattern->hapticController_);
    ASSERT_NE(pickerAudioHapticController, nullptr);
    pickerAudioHapticController->playThreadStatus_ = MockPickerAudioHapticImpl::ThreadStatus::NONE;
    textPickerColumnPattern->UpdateColumnChildPosition(offset);
    EXPECT_EQ(pickerAudioHapticController->playThreadStatus_, MockPickerAudioHapticImpl::ThreadStatus::NONE);
    textPickerColumnPattern->isShow_ = true;
    textPickerColumnPattern->UpdateColumnChildPosition(offset);
    EXPECT_EQ(pickerAudioHapticController->playThreadStatus_, MockPickerAudioHapticImpl::ThreadStatus::NONE);
    textPickerColumnPattern->isEnableHaptic_ = false;
    pickerAudioHapticController->playThreadStatus_ = MockPickerAudioHapticImpl::ThreadStatus::NONE;
    textPickerColumnPattern->UpdateColumnChildPosition(offset);
    EXPECT_EQ(pickerAudioHapticController->playThreadStatus_, MockPickerAudioHapticImpl::ThreadStatus::NONE);
}

/**
 * @tc.name: TextPickerModelNGSetEnableHapticFeedback001
 * @tc.desc: Test TextPickerModelNG SetEnableHapticFeedback.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnExtendTestNg, TextPickerModelNGSetEnableHapticFeedback001, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->MultiInit(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    TextPickerModelNG::GetInstance()->SetEnableHapticFeedback(false);
    EXPECT_FALSE(textPickerPattern->isEnableHaptic_);
}

/**
 * @tc.name: TextPickerDialogViewShowTest002
 * @tc.desc: Test TextPickerDialogView Show for API16.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnExtendTestNg, TextPickerDialogViewShowTest002, TestSize.Level1)
{
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));

    auto func = [](const std::string& /* info */) {};
    std::map<std::string, NG::DialogTextEvent> dialogEvent;
    dialogEvent["changeId"] = func;
    dialogEvent["acceptId"] = func;
    dialogEvent["scrollStopId"] = func;

    int32_t cancelCallbackInfo = 0;
    auto cancelFunc = [&cancelCallbackInfo](
                          const GestureEvent& /* info */) { cancelCallbackInfo = ONCANCEL_CALLBACK_INFO; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;

    auto settingData = CreateDefaultTextPickerSettingData();
    ASSERT_NE(settingData, nullptr);
    settingData->isEnableHapticFeedback = false;
    DialogProperties dialogProperties;
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode =
        TextPickerDialogView::Show(dialogProperties, *settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);
    auto customNode = dialogPattern->GetCustomNode();
    ASSERT_NE(customNode, nullptr);
    RefPtr<FrameNode> textPickerNode = nullptr;
    auto children = customNode->GetChildren();
    for (auto it = children.rbegin(); it != children.rend(); ++it) {
        auto targetNode = AceType::DynamicCast<FrameNode>(*it);
        if (targetNode && targetNode->GetTag() == V2::TEXT_PICKER_ETS_TAG) {
            textPickerNode = targetNode;
            break;
        }
    }
    ASSERT_NE(textPickerNode, nullptr);
    auto textPickerPattern = textPickerNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    EXPECT_FALSE(textPickerPattern->isEnableHaptic_);
}

/**
 * @tc.name: InnerHandleScrollTest001
 * @tc.desc: Test TextPickerColumnPattern InnerHandleScroll001
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnExtendTestNg, InnerHandleScrollTest001, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(0);
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(true);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    textPickerPattern->OnModifyDone();
    auto child = textPickerPattern->GetColumnNode();
    ASSERT_NE(child, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(child)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    columnPattern->GetParentLayout()->UpdateCanLoop(true);
    RangeContent tstContentOne = { "test1", "test1" };
    columnPattern->options_.push_back(tstContentOne);
    columnPattern->isEnableHaptic_ = false;
    columnPattern->hapticController_ = nullptr;
    bool result = columnPattern->InnerHandleScroll(true);
    EXPECT_TRUE(result);
    columnPattern->hapticController_ = PickerAudioHapticFactory::GetInstance();
    auto pickerAudioHapticController =
        std::static_pointer_cast<MockPickerAudioHapticImpl>(columnPattern->hapticController_);
    ASSERT_NE(pickerAudioHapticController, nullptr);
    columnPattern->InnerHandleScroll(true);
    EXPECT_EQ(pickerAudioHapticController->playThreadStatus_, MockPickerAudioHapticImpl::ThreadStatus::NONE);
    columnPattern->isEnableHaptic_ = true;
    columnPattern->InnerHandleScroll(true);
    EXPECT_EQ(pickerAudioHapticController->playThreadStatus_, MockPickerAudioHapticImpl::ThreadStatus::PLAY_ONCE);
}

/**
 * @tc.name: ColumnPatternInitHapticController001
 * @tc.desc: Test ColumnPatternInitHapticController
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnExtendTestNg, ColumnPatternInitHapticController001, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_PICKER_ETS_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<TextPickerPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    textPickerPattern->ColumnPatternInitHapticController();
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));
    textPickerPattern->isHapticChanged_ = false;
    textPickerPattern->ColumnPatternInitHapticController();
    EXPECT_FALSE(textPickerPattern->isHapticChanged_);
    textPickerPattern->isHapticChanged_ = true;
    textPickerPattern->ColumnPatternInitHapticController();
    EXPECT_FALSE(textPickerPattern->isHapticChanged_);
    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(buttonNode, nullptr);
    auto buttonNodeTwo = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(buttonNodeTwo, nullptr);
    auto columnNode =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<TextPickerColumnPattern>(); });
    ASSERT_NE(columnNode, nullptr);
    auto blendNode = FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(blendNode, nullptr);
    auto stackNode = FrameNode::GetOrCreateFrameNode(V2::STACK_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<StackPattern>(); });
    ASSERT_NE(stackNode, nullptr);
    auto geometryNode = stackNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    buttonNode->MountToParent(stackNode);
    buttonNodeTwo->MountToParent(blendNode);
    columnNode->MountToParent(blendNode);
    blendNode->MountToParent(stackNode);
    stackNode->MountToParent(frameNode);
    textPickerPattern->isHapticChanged_ = true;
    textPickerPattern->ColumnPatternInitHapticController();
    EXPECT_FALSE(textPickerPattern->isHapticChanged_);
}
} // namespace OHOS::Ace::NG
