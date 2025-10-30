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

#include <cstdint>
#include <functional>
#include <optional>
#include <utility>

#include "gtest/gtest-message.h"
#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_theme_default.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/rosen/mock_canvas.h"

#include "core/components/theme/icon_theme.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/time_picker/timepicker_column_pattern.h"
#include "core/components_ng/pattern/time_picker/timepicker_dialog_view.h"
#include "core/components_ng/pattern/time_picker/timepicker_model_ng.h"
#include "core/components_ng/pattern/time_picker/timepicker_row_pattern.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const InspectorFilter filter;
const int CURRENT_VALUE1 = 3;
const int SHOW_COUNT = 7;
const std::string TIME_AMPM = "01";
const PickerTime TIME_PICKED_PREFIXZERO = PickerTime(3, 3, 3);
const int32_t HOUR_PICKED = 1;
const uint32_t MINUTE_59 = 59;
const std::vector<int> DEFAULT_VALUE = { 0, 1, 2, 3, 4 };
const float TEXT_WEIGHT_NUMBER = 6.0f;
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
class TimePickerPaintTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void CreateTimePickerColumnNode();

    RefPtr<FrameNode> columnNode_;
    RefPtr<TimePickerColumnPattern> columnPattern_;
};

class TestNode : public UINode {
    DECLARE_ACE_TYPE(TestNode, UINode);

public:
    static RefPtr<TestNode> CreateTestNode(int32_t nodeId)
    {
        auto spanNode = MakeRefPtr<TestNode>(nodeId);
        return spanNode;
    }

    bool IsAtomicNode() const override
    {
        return true;
    }

    explicit TestNode(int32_t nodeId) : UINode("TestNode", nodeId) {}
    ~TestNode() override = default;
};

void TimePickerPaintTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void TimePickerPaintTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void TimePickerPaintTestNg::SetUp()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        return GetTheme(type);
    });
    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([](ThemeType type, int32_t themeScopeId) -> RefPtr<Theme> { return GetTheme(type); });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void TimePickerPaintTestNg::TearDown()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    ViewStackProcessor::GetInstance()->ClearStack();
}

void TimePickerPaintTestNg::CreateTimePickerColumnNode()
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto pickerFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(pickerFrameNode, nullptr);
    pickerFrameNode->MarkModifyDone();

    auto timePickerRowPattern = pickerFrameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    columnNode_ = allChildNode["minute"].Upgrade();
    ASSERT_NE(columnNode_, nullptr);
    columnPattern_ = columnNode_->GetPattern<TimePickerColumnPattern>();
    ASSERT_NE(columnPattern_, nullptr);
    columnPattern_->SetShowCount(SHOW_COUNT);
    columnPattern_->OnAttachToFrameNode();
    auto host = timePickerRowPattern->GetHost();
    EXPECT_NE(host, nullptr);
}

#ifdef ARKUI_WEARABLE
/**
 * @tc.name: TimePickerPaintTest001
 * @tc.desc: Test GetForegroundDrawFunction.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPaintTestNg, TimePickerPaintTest001, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerPaintProperty = frameNode->GetPaintProperty<PaintProperty>();
    auto timePickerPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerPattern, nullptr);
    auto timePickerPaintMethod =
        AceType::MakeRefPtr<TimePickerPaintMethod>(AceType::WeakClaim(AceType::RawPtr(timePickerPattern)));
    ASSERT_NE(timePickerPaintMethod, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    auto renderContext = frameNode->GetRenderContext();
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, pickerPaintProperty);
    ASSERT_NE(paintWrapper, nullptr);
    auto canvasDrawFunction = timePickerPaintMethod->GetForegroundDrawFunction(paintWrapper);
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    canvasDrawFunction(rsCanvas);
}

/**
 * @tc.name: TimePickerPaintTest002
 * @tc.desc: Test TimePickerColumnPattern UpdateSelectedTextColor.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPaintTestNg, TimePickerPaintTest002, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();

    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto minuteColumn = allChildNode["minute"].Upgrade();
    ASSERT_NE(minuteColumn, nullptr);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_NE(minuteColumnPattern, nullptr);
    auto child = minuteColumn->GetChildren();
    auto iter = child.begin();
    auto textNode = AceType::DynamicCast<FrameNode>(*iter);
    ASSERT_TRUE(textNode);
    auto textPattern = textNode->GetPattern<TextPattern>();
    ASSERT_TRUE(textPattern);
    RefPtr<TextLayoutProperty> textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_TRUE(textLayoutProperty);
    minuteColumnPattern->UpdateSelectedTextColor(theme);
    EXPECT_EQ(textLayoutProperty->GetTextColor(), Color::BLACK);
}

/**
 * @tc.name: TimePickerPaintTest003
 * @tc.desc: Test TimePickerColumnPattern SetDigitalCrownSensitivity.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPaintTestNg, TimePickerPaintTest003, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto minuteColumn = allChildNode["minute"].Upgrade();
    ASSERT_NE(minuteColumn, nullptr);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_NE(minuteColumnPattern, nullptr);
    EXPECT_NE(minuteColumnPattern->GetDigitalCrownSensitivity(), INVALID_CROWNSENSITIVITY);
    EXPECT_EQ(minuteColumnPattern->GetDigitalCrownSensitivity(), DEFAULT_CROWNSENSITIVITY);
    TimePickerModelNG::GetInstance()->SetDigitalCrownSensitivity(2);
    TimePickerModelNG::SetDigitalCrownSensitivity(frameNode, 2);
    EXPECT_EQ(minuteColumnPattern->GetDigitalCrownSensitivity(), 2);
}
#endif

/**
 * @tc.name: TimePickerPaintTest004
 * @tc.desc: Test InitOnCrownEvent
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPaintTestNg, TimePickerPaintTest004, TestSize.Level0)
{
#ifdef SUPPORT_DIGITAL_CROWN
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_TRUE(frameNode);
    frameNode->MarkModifyDone();
    auto eventHub = frameNode->GetEventHub<EventHub>();
    auto focusHub = eventHub->GetOrCreateFocusHub();

    CrownEvent crownEvent;
    crownEvent.action = OHOS::Ace::CrownAction::BEGIN;
    EXPECT_FALSE(focusHub->ProcessOnCrownEventInternal(crownEvent));
    crownEvent.action = OHOS::Ace::CrownAction::UPDATE;
    EXPECT_FALSE(focusHub->ProcessOnCrownEventInternal(crownEvent));
    crownEvent.action = OHOS::Ace::CrownAction::END;
    EXPECT_FALSE(focusHub->ProcessOnCrownEventInternal(crownEvent));
#endif
}

/**
 * @tc.name: TimePickerSetDefaultFocus001
 * @tc.desc: Test SetDefaultFocus
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPaintTestNg, TimePickerSetDefaultFocus001, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    theme->showCircleDial_ = true;
    timePickerRowPattern->selectedColumnId_ = "second";
    timePickerRowPattern->SetDefaultFocus();
    EXPECT_EQ(timePickerRowPattern->selectedColumnId_, "second");
    std::unordered_map<std::string, WeakPtr<FrameNode>> allChildNode = timePickerRowPattern->allChildNode_;
    timePickerRowPattern->allChildNode_.erase("hour");
    ASSERT_TRUE(timePickerRowPattern->allChildNode_.find("hour") == timePickerRowPattern->allChildNode_.end());
    timePickerRowPattern->SetDefaultFocus();
    timePickerRowPattern->allChildNode_ = allChildNode;
    timePickerRowPattern->SetDefaultFocus();
    allChildNode = timePickerRowPattern->GetAllChildNode();
    auto hourColumn = allChildNode["hour"].Upgrade();
    ASSERT_NE(hourColumn, nullptr);
}

/**
 * @tc.name: TimePickerClearFocus001
 * @tc.desc: Test ClearFocus
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPaintTestNg, TimePickerClearFocus001, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    theme->showCircleDial_ = true;
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
  
    timePickerRowPattern->selectedColumnId_ = "second";
    timePickerRowPattern->isClearFocus_ = true;
    timePickerRowPattern->SetDefaultFocus();
    timePickerRowPattern->ClearFocus();
    EXPECT_EQ(timePickerRowPattern->selectedColumnId_, "second");
}

/**
 * @tc.name: TimePickerClearFocus002
 * @tc.desc: Test ClearFocus
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPaintTestNg, TimePickerClearFocus002, TestSize.Level0)
{
    /**
     * @tc.step: step1. create frameNode and pattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    /**
     * @tc.step: step1. set default focus.
     */
    theme->showCircleDial_ = true;
    timePickerRowPattern->selectedColumnId_ = "second";
    timePickerRowPattern->SetDefaultFocus();

    /**
     * @tc.cases: case. selectedColumnId_ is null.
     */
    timePickerRowPattern->selectedColumnId_ = "";
    timePickerRowPattern->ClearFocus();
    EXPECT_EQ(timePickerRowPattern->selectedColumnId_, "");

    /**
     * @tc.cases: case. not clearfocus and has no second node.
     */
    timePickerRowPattern->selectedColumnId_ = "hour";
    timePickerRowPattern->isClearFocus_ = false;
    timePickerRowPattern->SetHasSecond(false);
    timePickerRowPattern->ClearFocus();
    EXPECT_EQ(timePickerRowPattern->selectedColumnId_, "hour");
}

#ifdef SUPPORT_DIGITAL_CROWN
/**
 * @tc.name: TimePickerPaintTest005
 * @tc.desc: Test GetContentDrawFunction
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPaintTestNg, TimePickerPaintTest005, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerPaintProperty = frameNode->GetPaintProperty<PaintProperty>();
    ASSERT_NE(pickerPaintProperty, nullptr);
    auto timePickerPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerPattern, nullptr);
    auto timePickerPaintMethod = AceType::MakeRefPtr<TimePickerPaintMethod>();
    ASSERT_NE(timePickerPaintMethod, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, pickerPaintProperty);
    ASSERT_NE(paintWrapper, nullptr);

    auto canvasDrawFunction = timePickerPaintMethod->GetContentDrawFunction(paintWrapper);
    ASSERT_NE(canvasDrawFunction, nullptr);
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    canvasDrawFunction(rsCanvas);
}

/**
 * @tc.name: TimePickerRotateCrown001
 * @tc.desc: Test OnCrownEvent
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPaintTestNg, TimePickerRotateCrown001, TestSize.Level0)
{
    TimePickerModelNG::GetInstance()->SetDigitalCrownSensitivity(CROWN_SENSITIVITY_MIN -1);
    TimePickerModelNG::GetInstance()->SetDigitalCrownSensitivity(CROWN_SENSITIVITY_MAX +1);
    TimePickerModelNG::SetDigitalCrownSensitivity(NULL, CROWN_SENSITIVITY_MAX);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_FALSE(frameNode);
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_TRUE(frameNode);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_TRUE(timePickerRowPattern);
    ASSERT_TRUE(timePickerRowPattern->IsCircle());
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto minuteColumn = allChildNode["minute"].Upgrade();
    ASSERT_TRUE(minuteColumn);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_NE(minuteColumnPattern, nullptr);
    minuteColumnPattern->SetSelectedMark();
    std::string select= minuteColumnPattern->GetSelectedColumnId();
    EXPECT_EQ(select, std::string("minute"));

    CrownEvent event;
    event.action = OHOS::Ace::CrownAction::BEGIN;
    ASSERT_TRUE(minuteColumnPattern ->OnCrownEvent(event));

    event.action = OHOS::Ace::CrownAction::UPDATE;
    event.angularVelocity = COLUMN_WIDTH;
    event.degree = OTHER_TEXTNODE_HEIGHT;
    ASSERT_TRUE(minuteColumnPattern ->OnCrownEvent(event));

    event.action = OHOS::Ace::CrownAction::END;
    event.angularVelocity = 0.0;
    event.degree = 0.0;
    ASSERT_TRUE(minuteColumnPattern ->OnCrownEvent(event));
    minuteColumnPattern->animationCreated_ = false;
    ASSERT_TRUE(minuteColumnPattern ->OnCrownEvent(event));
}

/**
 * @tc.name: TimePickerSetDefaultFocus002
 * @tc.desc: Test SetDefaultFocus
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPaintTestNg, TimePickerSetDefaultFocus002, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_TRUE(frameNode);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_TRUE(timePickerRowPattern);

    timePickerRowPattern->selectedColumnId_ = "second";
    timePickerRowPattern->SetDefaultFocus();
    std::unordered_map<std::string, WeakPtr<FrameNode>> allChildNode = timePickerRowPattern->allChildNode_;
    timePickerRowPattern->allChildNode_.erase("hour");
    ASSERT_TRUE(timePickerRowPattern->allChildNode_.find("hour") == timePickerRowPattern->allChildNode_.end());
    timePickerRowPattern->SetDefaultFocus();
    timePickerRowPattern->allChildNode_ = allChildNode;
    timePickerRowPattern->SetDefaultFocus();
    allChildNode = timePickerRowPattern->GetAllChildNode();
    auto hourColumn = allChildNode["hour"].Upgrade();
    ASSERT_NE(hourColumn, nullptr);

    auto hourColumnPattern = hourColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_NE(hourColumnPattern, nullptr);
    hourColumnPattern->SetSelectedMark();
    std::string select= hourColumnPattern->GetSelectedColumnId();
    EXPECT_EQ(select, std::string("hour"));
    timePickerRowPattern->selectedColumnId_ = "";
    timePickerRowPattern->ClearFocus();
    CrownEvent event;
    event.action = OHOS::Ace::CrownAction::UNKNOWN;
    ASSERT_FALSE(hourColumnPattern ->OnCrownEvent(event));
}

/**
 * @tc.name: TimePickerRestoreFrameNode001
 * @tc.desc: Test RestoreFrameNode
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPaintTestNg, TimePickerRestoreFrameNode001, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_TRUE(frameNode);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_TRUE(timePickerRowPattern);

    RefPtr<FocusHub> focusHub_ ;
    timePickerRowPattern->InitOnCrownEvent(focusHub_);
    focusHub_= frameNode->GetFocusHub();
    ASSERT_TRUE(focusHub_);
    frameNode ->focusHub_ = NULL;
    timePickerRowPattern->InitFocusEvent();
    timePickerRowPattern->DetachFromFrameNode(NULL);
    ASSERT_FALSE(timePickerRowPattern->IsCircle());
    timePickerRowPattern->InitFocusEvent();
    timePickerRowPattern->ClearFocus();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto minutePattern = allChildNode["minute"].Upgrade();
    ASSERT_NE(minutePattern, nullptr);
    auto minuteColumnPattern = minutePattern->GetPattern<TimePickerColumnPattern>();
    ASSERT_NE(minuteColumnPattern, nullptr);

    CrownEvent event;
    minuteColumnPattern->UpdateSelectedTextColor(theme);
    timePickerRowPattern->frameNode_ = frameNode;
    minuteColumnPattern->frameNode_ = NULL;
    timePickerRowPattern->SetDigitalCrownSensitivity(CROWN_SENSITIVITY_MIN);
    event.action = OHOS::Ace::CrownAction::BEGIN;
    ASSERT_TRUE(minuteColumnPattern->OnCrownEvent(event));
    event.action = OHOS::Ace::CrownAction::UPDATE;
    ASSERT_TRUE(minuteColumnPattern->OnCrownEvent(event));

    timePickerRowPattern->allChildNode_.clear();
    timePickerRowPattern->ClearFocus();
    WeakPtr<FrameNode> ptr;
    allChildNode["hour"] = ptr;
    timePickerRowPattern->ClearFocus();
    timePickerRowPattern->allChildNode_ = allChildNode;
    RefPtr<TimePickerColumnPattern> crownPickerColumnPattern;
    timePickerRowPattern->timePickerColumns_.push_back(ptr);
    timePickerRowPattern->SetDefaultFocus();

    event.action = OHOS::Ace::CrownAction::UNKNOWN;
    ASSERT_FALSE(minuteColumnPattern ->OnCrownEvent(event));
    delete minuteColumnPattern->circleUtils_;
    minuteColumnPattern->circleUtils_= NULL;
    ASSERT_FALSE(minuteColumnPattern ->OnCrownEvent(event));
}
#endif

/**
 * @tc.name: TimePickerColumnLayoutAlgorithmNeedAdaptForAging
 * @tc.desc: Test TimePickerColumnLayoutAlgorithm NeedAdaptForAging.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPaintTestNg, TimePickerColumnLayoutAlgorithmNeedAdaptForAging, TestSize.Level0)
{
    /**
     * @tc.step: step1. create frameNode and pattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);

    /**
     * @tc.cases: case. cover branch DeviceOrientation is LANDSCAPE.
     */
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_TRUE(frameNode);
    frameNode->MarkModifyDone();
    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    auto layoutConstraint = LayoutConstraintF();
    layoutConstraint.selfIdealSize.SetWidth(20);
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_TRUE(timePickerRowPattern);
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto minuteColumn = allChildNode["minute"].Upgrade();
    ASSERT_TRUE(minuteColumn);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_TRUE(minuteColumnPattern);
    auto columnBlend = AceType::DynamicCast<FrameNode>(minuteColumn->GetParent());
    ASSERT_TRUE(columnBlend);
    auto blendLayoutProperty = columnBlend->GetLayoutProperty();
    blendLayoutProperty->UpdateLayoutConstraint(layoutConstraint);
    blendLayoutProperty->UpdateContentConstraint();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(minuteColumn, minuteColumn->GetGeometryNode(), pickerProperty);

    /**
     * @tc.step: step2. initialize TimePickerColumnLayoutAlgorithm and call Measure
     *                  and Layout function.
     */
    TimePickerColumnLayoutAlgorithm timePickerColumnLayoutAlgorithm;
    timePickerColumnLayoutAlgorithm.Measure(&layoutWrapper);
    timePickerColumnLayoutAlgorithm.Layout(&layoutWrapper);
    double fontScale = 1.0f;
    MockPipelineContext::GetCurrent()->SetFontScale(fontScale);
    bool result = timePickerColumnLayoutAlgorithm.NeedAdaptForAging();
    EXPECT_EQ(false, result);

    fontScale = 2.0f;
    MockPipelineContext::GetCurrent()->SetFontScale(fontScale);
    result = timePickerColumnLayoutAlgorithm.NeedAdaptForAging();
    EXPECT_EQ(true, result);
}

/**
 * @tc.name: TimePickerColumnLayoutAlgorithmAdjustFontSizeScale
 * @tc.desc: Test TimePickerColumnLayoutAlgorithm AdjustFontSizeScale
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPaintTestNg, TimePickerColumnLayoutAlgorithmAdjustFontSizeScale, TestSize.Level0)
{
    /**
     * @tc.step: step1. create frameNode and pattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);

    /**
     * @tc.cases: case. cover branch DeviceOrientation is LANDSCAPE.
     */
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_TRUE(frameNode);
    frameNode->MarkModifyDone();
    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    auto layoutConstraint = LayoutConstraintF();
    layoutConstraint.selfIdealSize.SetWidth(20);
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_TRUE(timePickerRowPattern);
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto minuteColumn = allChildNode["minute"].Upgrade();
    ASSERT_TRUE(minuteColumn);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_TRUE(minuteColumnPattern);
    auto columnBlend = AceType::DynamicCast<FrameNode>(minuteColumn->GetParent());
    ASSERT_TRUE(columnBlend);
    auto blendLayoutProperty = columnBlend->GetLayoutProperty();
    blendLayoutProperty->UpdateLayoutConstraint(layoutConstraint);
    blendLayoutProperty->UpdateContentConstraint();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(minuteColumn, minuteColumn->GetGeometryNode(), pickerProperty);

    /**
     * @tc.step: step2. initialize TimePickerColumnLayoutAlgorithm and call Measure
     *                  and Layout function.
     */
    TimePickerColumnLayoutAlgorithm timePickerColumnLayoutAlgorithm;
    timePickerColumnLayoutAlgorithm.Measure(&layoutWrapper);
    timePickerColumnLayoutAlgorithm.Layout(&layoutWrapper);
    double fontScale = 1.0f;
    Dimension fontSizeValue(10.0);
    Dimension result = timePickerColumnLayoutAlgorithm.AdjustFontSizeScale(fontSizeValue, fontScale);
    EXPECT_EQ(result, fontSizeValue);
}

/**
 * @tc.name: TimePickerColumnLayoutAlgorithmGetPickerMaxHeight
 * @tc.desc: Test TimePickerColumnLayoutAlgorithm GetPickerMaxHeight.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPaintTestNg, TimePickerColumnLayoutAlgorithmGetPickerMaxHeight, TestSize.Level0)
{
    /**
     * @tc.step: step1. create frameNode and pattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);

    /**
     * @tc.cases: case. cover branch DeviceOrientation is LANDSCAPE.
     */
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_TRUE(frameNode);
    frameNode->MarkModifyDone();
    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    auto layoutConstraint = LayoutConstraintF();
    layoutConstraint.selfIdealSize.SetWidth(20);
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_TRUE(timePickerRowPattern);
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto minuteColumn = allChildNode["minute"].Upgrade();
    ASSERT_TRUE(minuteColumn);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_TRUE(minuteColumnPattern);
    auto columnBlend = AceType::DynamicCast<FrameNode>(minuteColumn->GetParent());
    ASSERT_TRUE(columnBlend);
    auto blendLayoutProperty = columnBlend->GetLayoutProperty();
    blendLayoutProperty->UpdateLayoutConstraint(layoutConstraint);
    blendLayoutProperty->UpdateContentConstraint();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(minuteColumn, minuteColumn->GetGeometryNode(), pickerProperty);

    /**
     * @tc.step: step2. initialize TimePickerColumnLayoutAlgorithm and call Measure
     *                  and Layout function.
     */
    TimePickerColumnLayoutAlgorithm timePickerColumnLayoutAlgorithm;
    timePickerColumnLayoutAlgorithm.Measure(&layoutWrapper);
    timePickerColumnLayoutAlgorithm.Layout(&layoutWrapper);

    /**
     * @tc.steps: step2. call MountSecondNode.
     * @tc.expected: set HasAmPmNode is true and language_ is not "ug".
     */
    std::optional<int32_t> temp;
    temp.emplace(100);
    timePickerRowPattern->secondId_ = temp;
    RefPtr<FrameNode> stackSecondNode = FrameNode::CreateFrameNode(TIME_AMPM, HOUR_PICKED, timePickerRowPattern);
    float result = timePickerColumnLayoutAlgorithm.GetPickerMaxHeight(layoutConstraint, stackSecondNode);
    ASSERT_NE(TEXT_WEIGHT_NUMBER, result);
}

/**
 * @tc.name: TimePickerModelNGHasUserDefinedDisappearFontFamily01
 * @tc.desc: Test TimePickerModelNG HasUserDefinedDisappearFontFamily.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPaintTestNg, TimePickerModelNGHasUserDefinedDisappearFontFamily01, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    TimePickerModelNG::GetInstance()->HasUserDefinedDisappearFontFamily(true);
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    ASSERT_TRUE(timePickerRowPattern->GetHasUserDefinedDisappearFontFamily());
    TimePickerModelNG::GetInstance()->HasUserDefinedDisappearFontFamily(false);
    ASSERT_FALSE(timePickerRowPattern->GetHasUserDefinedDisappearFontFamily());
}

/**
 * @tc.name: TimePickerModelNGHasUserDefinedDisappearFontFamily02
 * @tc.desc: Test TimePickerModelNG HasUserDefinedDisappearFontFamily.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPaintTestNg, TimePickerModelNGHasUserDefinedDisappearFontFamily02, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    TimePickerModelNG::GetInstance()->HasUserDefinedDisappearFontFamily(false);
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    ASSERT_FALSE(timePickerRowPattern->GetHasUserDefinedNormalFontFamily());
    TimePickerModelNG::GetInstance()->HasUserDefinedDisappearFontFamily(true);
    ASSERT_FALSE(timePickerRowPattern->GetHasUserDefinedNormalFontFamily());
}

/**
 * @tc.name: TimePickerModelNGHasUserDefinedNormalFontFamily01
 * @tc.desc: Test TimePickerModelNG HasUserDefinedNormalFontFamily.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPaintTestNg, TimePickerModelNGHasUserDefinedNormalFontFamily01, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    TimePickerModelNG::GetInstance()->HasUserDefinedNormalFontFamily(false);
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    ASSERT_FALSE(timePickerRowPattern->GetHasUserDefinedNormalFontFamily());
    TimePickerModelNG::GetInstance()->HasUserDefinedNormalFontFamily(true);
    ASSERT_TRUE(timePickerRowPattern->GetHasUserDefinedNormalFontFamily());
}

/**
 * @tc.name: TimePickerModelNGSetHour2401
 * @tc.desc: Test TimePickerModelNG SetHour24 true.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPaintTestNg, TimePickerModelNGSetHour2401, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_TRUE(frameNode);
    TimePickerModelNG::GetInstance()->SetHour24(true);
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    ASSERT_TRUE(timePickerRowPattern->GetHour24());
    TimePickerModelNG::GetInstance()->SetHour24(false);
    timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    ASSERT_FALSE(timePickerRowPattern->GetHour24());
}

/**
 * @tc.name: TimePickerModelNGgetNormalTextStyle01
 * @tc.desc: Test TimePickerModelNG getNormalTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPaintTestNg, TimePickerModelNGgetNormalTextStyle01, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_TRUE(frameNode);
    auto pickerTheme = MockThemeDefault::GetPickerTheme();
    ASSERT_NE(pickerTheme, nullptr);
    auto style = pickerTheme->GetOptionStyle(false, false);
    auto pickerTextStyle = TimePickerModelNG::getNormalTextStyle(frameNode);
    EXPECT_EQ(pickerTextStyle.fontStyle.value_or(Ace::FontStyle::NORMAL), style.GetFontStyle());
}

/**
 * @tc.name: TimePickerModelNGgetSelectedTextStyle01
 * @tc.desc: Test TimePickerModelNG getSelectedTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPaintTestNg, TimePickerModelNGgetSelectedTextStyle01, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_TRUE(frameNode);
    auto pickerTheme = MockThemeDefault::GetPickerTheme();
    ASSERT_NE(pickerTheme, nullptr);
    auto style = pickerTheme->GetOptionStyle(false, false);
    auto pickerTextStyle = TimePickerModelNG::getSelectedTextStyle(frameNode);
    EXPECT_EQ(pickerTextStyle.fontStyle.value_or(Ace::FontStyle::NORMAL), style.GetFontStyle());
}

/**
 * @tc.name: TimePickerModelNGgetTimepickerSelected01
 * @tc.desc: Test TimePickerModelNG getTimepickerSelected.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPaintTestNg, TimePickerModelNGgetTimepickerSelected01, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_TRUE(frameNode);
    auto pickerTheme = MockThemeDefault::GetPickerTheme();
    ASSERT_NE(pickerTheme, nullptr);
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    auto actualPickerTime = TimePickerModelNG::getTimepickerSelected(frameNode);
    EXPECT_EQ(timePickerRowPattern->GetCurrentTime().GetHour(), actualPickerTime.GetHour());
}

/**
 * @tc.name: TimePickerModelNGgetTimepickerBackgroundColor01
 * @tc.desc: Test TimePickerModelNG getTimepickerBackgroundColor.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPaintTestNg, TimePickerModelNGgetTimepickerBackgroundColor01, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_TRUE(frameNode);
    auto pickerTheme = MockThemeDefault::GetPickerTheme();
    ASSERT_NE(pickerTheme, nullptr);
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    auto result = TimePickerModelNG::getTimepickerBackgroundColor(frameNode);
    EXPECT_NE(result, MINUTE_59);
}

/**
 * @tc.name: TimePickerModelNGgetTimepickerUseMilitaryTime01
 * @tc.desc: Test TimePickerModelNG getTimepickerUseMilitaryTime.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPaintTestNg, TimePickerModelNGgetTimepickerUseMilitaryTime01, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_TRUE(frameNode);
    auto pickerTheme = MockThemeDefault::GetPickerTheme();
    ASSERT_NE(pickerTheme, nullptr);
    ASSERT_FALSE(TimePickerModelNG::getTimepickerUseMilitaryTime(frameNode));
}

/**
 * @tc.name: TimePickerModelNGGetIsEnableCascadeValue01
 * @tc.desc: Test TimePickerModelNG GetTimepickerEnableCascade.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPaintTestNg, TimePickerModelNGGetIsEnableCascadeValue01, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_TRUE(frameNode);
    auto pickerTheme = MockThemeDefault::GetPickerTheme();
    ASSERT_NE(pickerTheme, nullptr);
    ASSERT_FALSE(TimePickerModelNG::GetTimepickerEnableCascade(frameNode));
}

/**
 * @tc.name: TimePickerModelNGSetWheelModeEnabled
 * @tc.desc: Test TimePickerModelNG SetWheelModeEnabled.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPaintTestNg, TimePickerModelNGSetWheelModeEnabled, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_TRUE(frameNode);
    TimePickerModelNG::SetWheelModeEnabled(frameNode, false);
    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    EXPECT_EQ(timePickerRowPattern->GetWheelModeEnabled(), false);
    TimePickerModelNG::SetWheelModeEnabled(frameNode, true);
    EXPECT_EQ(timePickerRowPattern->GetWheelModeEnabled(), true);
}

/**
 * @tc.name: TimePickerModelNGSetDefaultAttributes
 * @tc.desc: Test TimePickerModelNG SetDefaultAttributes.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPaintTestNg, SetDefaultAttributes01, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto pickerTheme = MockThemeDefault::GetPickerTheme();
    RefPtr<FrameNode> frameNode;
    TimePickerModelNG::SetDefaultAttributes(frameNode, pickerTheme);
    ASSERT_NE(pickerTheme, nullptr);
    frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_TRUE(frameNode);
    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    ASSERT_FALSE(pickerProperty->HasSelectedColor());
}

/**
 * @tc.name: TimePickerModelNGHasUserDefinedSelectedFontFamily
 * @tc.desc: Test TimePickerModelNG HasUserDefinedSelectedFontFamily.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPaintTestNg, TimePickerModelNGHasUserDefinedSelectedFontFamily, TestSize.Level0)
{
    int32_t setApiVersion = 12;
    ZeroPrefixType showType = ZeroPrefixType::SHOW;
    ZeroPrefixType hideType = ZeroPrefixType::HIDE;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, true);
    TimePickerModelNG::GetInstance()->SetHour24(true);
    TimePickerModelNG::GetInstance()->SetSelectedTime(TIME_PICKED_PREFIXZERO);
    TimePickerModelNG::GetInstance()->SetDateTimeOptions(hideType, showType, hideType);
    TimePickerModelNG::GetInstance()->HasUserDefinedSelectedFontFamily(true);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_TRUE(frameNode);
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    ASSERT_TRUE(timePickerRowPattern->GetHasUserDefinedSelectedFontFamily());
    TimePickerModelNG::GetInstance()->HasUserDefinedSelectedFontFamily(false);
    ASSERT_FALSE(timePickerRowPattern->GetHasUserDefinedSelectedFontFamily());
}

/**
 * @tc.name: TimePickerDialogCreateNextPrevButtonNode
 * @tc.desc: Test TimePickerDialog CreateNextPrevButtonNode parameter null.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPaintTestNg, TimePickerDialogCreateNextPrevButtonNode, TestSize.Level0)
{
    std::function<void()> timePickerSwitchEvent = []() {};
    RefPtr<FrameNode> timeNode = nullptr;
    std::vector<ButtonInfo> buttonInfos;
    RefPtr<FrameNode> result = TimePickerDialogView::CreateNextPrevButtonNode(
        timePickerSwitchEvent, timeNode, buttonInfos);
    ASSERT_FALSE(result);
}

/**
 * @tc.name: TimePickerDialogCreateNextPrevButtonNode02
 * @tc.desc: Test TimePickerDialog CreateNextPrevButtonNode parameter non-null.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPaintTestNg, TimePickerDialogCreateNextPrevButtonNode02, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_TRUE(frameNode);
    auto pickerTheme = MockThemeDefault::GetPickerTheme();
    ASSERT_NE(pickerTheme, nullptr);
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    std::function<void()> timePickerSwitchEvent = []() {};
    std::optional<int32_t> temp;
    temp.emplace(100);
    timePickerRowPattern->secondId_ = temp;
    RefPtr<FrameNode> stackSecondNode = FrameNode::CreateFrameNode(TIME_AMPM, HOUR_PICKED, timePickerRowPattern);
    std::vector<ButtonInfo> buttonInfos;
    ASSERT_NE(stackSecondNode, nullptr);
    RefPtr<FrameNode> result = TimePickerDialogView::CreateNextPrevButtonNode(
        timePickerSwitchEvent, stackSecondNode, buttonInfos);
    ASSERT_NE(result, nullptr);
}

/**
 * @tc.name: TimePickerPaintTest006
 * @tc.desc: Test GetForegroundDrawFunction.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPaintTestNg, TimePickerPaintTest006, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    auto pickerPaintProperty = frameNode->GetPaintProperty<PaintProperty>();
    ASSERT_NE(pickerPaintProperty, nullptr);
    auto timePickerPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerPattern, nullptr);
    auto timePickerPaintMethod = AceType::MakeRefPtr<TimePickerPaintMethod>();
    ASSERT_NE(timePickerPaintMethod, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    std::unique_ptr<PaintWrapper> paintWrapper =
        std::make_unique<PaintWrapper>(renderContext, geometryNode, pickerPaintProperty);
    ASSERT_NE(paintWrapper, nullptr);
    auto canvasDrawFunction = timePickerPaintMethod->GetForegroundDrawFunction(paintWrapper.get());
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    canvasDrawFunction(rsCanvas);
}

/**
 * @tc.name: TimePickerPaintTest007
 * @tc.desc: Test GetForegroundDrawFunction.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPaintTestNg, TimePickerPaintTest007, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    auto pickerPaintProperty = frameNode->GetPaintProperty<PaintProperty>();
    ASSERT_NE(pickerPaintProperty, nullptr);
    auto timePickerPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerPattern, nullptr);
    auto timePickerPaintMethod = AceType::MakeRefPtr<TimePickerPaintMethod>();
    timePickerPaintMethod->SetEnabled(false);
    ASSERT_NE(timePickerPaintMethod, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    std::unique_ptr<PaintWrapper> paintWrapper =
        std::make_unique<PaintWrapper>(renderContext, geometryNode, pickerPaintProperty);
    ASSERT_NE(paintWrapper, nullptr);
    auto canvasDrawFunction = timePickerPaintMethod->GetForegroundDrawFunction(paintWrapper.get());
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawPath(_)).WillRepeatedly(Return());
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    canvasDrawFunction(rsCanvas);
}

/**
* @tc.name: ParseDirectionKey001
* @tc.desc: Test TimePickerTest ParseDirectionKey
* @tc.type: FUNC
*/
HWTEST_F(TimePickerPaintTestNg, ParseDirectionKey001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create columnNode and columnPattern.
     */
    CreateTimePickerColumnNode();
    ASSERT_NE(columnPattern_, nullptr);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pickerPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(pickerPattern, nullptr);
    auto host = pickerPattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto totalOptionCount = columnPattern_->GetOptionCount();
    auto currentIndex = columnPattern_->GetCurrentIndex();

    KeyCode code = KeyCode::KEY_UNKNOWN;

    code = KeyCode::KEY_DPAD_UP;
    columnPattern_->stopHaptic_ = false;
    pickerPattern->ParseDirectionKey(host, columnPattern_, code, currentIndex, totalOptionCount, 0);
    EXPECT_TRUE(columnPattern_->stopHaptic_);

    code = KeyCode::KEY_DPAD_DOWN;
    columnPattern_->stopHaptic_ = false;
    pickerPattern->ParseDirectionKey(host, columnPattern_, code, currentIndex, totalOptionCount, 0);
    EXPECT_TRUE(columnPattern_->stopHaptic_);

    code = KeyCode::KEY_DPAD_LEFT;
    columnPattern_->stopHaptic_ = false;
    pickerPattern->ParseDirectionKey(host, columnPattern_, code, currentIndex, totalOptionCount, 0);
    EXPECT_FALSE(columnPattern_->stopHaptic_);

    code = KeyCode::KEY_DPAD_RIGHT;
    columnPattern_->stopHaptic_ = false;
    pickerPattern->ParseDirectionKey(host, columnPattern_, code, currentIndex, totalOptionCount, 0);
    EXPECT_FALSE(columnPattern_->stopHaptic_);
}

/**
 * @tc.name: TimePickerGetCurrentOption001
 * @tc.desc: Test TimePickerColumnPattern GetCurrentOption
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPaintTestNg, TimePickerGetCurrentOption001, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto minuteColumnNode = allChildNode["minute"].Upgrade();
    ASSERT_NE(minuteColumnNode, nullptr);
    auto minuteColumnPattern = minuteColumnNode->GetPattern<TimePickerColumnPattern>();
    minuteColumnPattern->SetCurrentIndex(CURRENT_VALUE1);

    auto options = minuteColumnPattern->GetOptions();
    options[minuteColumnNode] = 0;
    minuteColumnPattern->SetOptions(options);
    EXPECT_EQ(minuteColumnPattern->GetCurrentOption(), "");

    options[minuteColumnNode] = DEFAULT_VALUE.size();
    minuteColumnPattern->SetOptions(options);
    EXPECT_NE(minuteColumnPattern->GetCurrentOption(), "");

    options.erase(minuteColumnNode);
    minuteColumnPattern->SetOptions(options);
    EXPECT_EQ(minuteColumnPattern->GetCurrentOption(), "");
}

/**
 * @tc.name: SetDateTimeOptionsTest001
 * @tc.desc: Test SetDateTimeOptions should update options when all types different.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPaintTestNg, SetDateTimeOptionsTest001, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, true);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    ZeroPrefixType hourType = ZeroPrefixType::SHOW;
    ZeroPrefixType minuteType = ZeroPrefixType::HIDE;
    ZeroPrefixType secondType = ZeroPrefixType::HIDE;
    TimePickerModelNG::GetInstance()->SetDateTimeOptions(hourType, minuteType, secondType);
    EXPECT_EQ(timePickerRowPattern->GetPrefixHour(), hourType);
    EXPECT_EQ(timePickerRowPattern->GetPrefixMinute(), minuteType);
    EXPECT_EQ(timePickerRowPattern->GetPrefixSecond(), secondType);
}

/**
 * @tc.name: SetHour24Test001
 * @tc.desc: Test SetHour24.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPaintTestNg, SetHour24Test001, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, true);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    TimePickerModelNG::GetInstance()->SetHour24(true);
    EXPECT_TRUE(timePickerRowPattern->GetCachedHour24());
    TimePickerModelNG::SetHour24(frameNode, false);
    EXPECT_FALSE(timePickerRowPattern->GetCachedHour24());
}

/**
 * @tc.name: IsNeedToRebuildColumn001
 * @tc.desc: Test IsNeedToRebuildColumn return true.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPaintTestNg, IsNeedToRebuildColumn001, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, true);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    EXPECT_TRUE(timePickerRowPattern->IsNeedToRebuildColumn(true, true, 0, 0, 0));
    EXPECT_TRUE(timePickerRowPattern->IsNeedToRebuildColumn(true, true, 1, 11, 0));
    EXPECT_TRUE(timePickerRowPattern->IsNeedToRebuildColumn(true, true, 0, 1, 0));
    EXPECT_TRUE(timePickerRowPattern->IsNeedToRebuildColumn(true, false, 1, 10, 0));
}

/**
 * @tc.name: IsNeedToRebuildColumn002
 * @tc.desc: Test IsNeedToRebuildColumn return false.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPaintTestNg, IsNeedToRebuildColumn002, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, true);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    EXPECT_FALSE(timePickerRowPattern->IsNeedToRebuildColumn(true, true, 1, 0, 0));
    EXPECT_FALSE(timePickerRowPattern->IsNeedToRebuildColumn(true, false, 0, 1, 0));
    EXPECT_FALSE(timePickerRowPattern->IsNeedToRebuildColumn(false, true, 0, 0, 0));
}
} // namespace OHOS::Ace::NG
