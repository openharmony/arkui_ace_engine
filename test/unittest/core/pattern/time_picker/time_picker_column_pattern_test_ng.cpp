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
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/time_picker/timepicker_column_pattern.h"
#include "core/components_ng/pattern/time_picker/timepicker_model_ng.h"
#include "core/components_ng/pattern/time_picker/timepicker_row_pattern.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const InspectorFilter filter;
constexpr double TOSS_DELTA = 20.0;
const int MIDDLE_OF_COUNTS = 2;
const int SHOW_COUNT = 7;
const std::string AM = "AM ";
const std::string PM = "PM ";
const PickerTime TIME_PICKED = PickerTime(14, 9, 10);
const double OFFSET_X = 6.0;
const double OFFSET_Y = 8.0;
const double OFFSET_Y_0 = 0.0;
const double OFFSET_DISTANCE = 10.0;
const int32_t DEFAULT_FINGER_ID = 1;
const uint32_t INVALID_SHOW_COUNT = 1;
const uint32_t INDEX = 7;
const double SCALE = 1.0;
const double DEFAULT_JUMP_INTERVAL = 2.0;
const int32_t OPTION_COUNT_PHONE_LANDSCAPE = 3;
const float TEXT_HEIGHT_NUMBER = 3.0f;
const float TEXT_WEIGHT_NUMBER = 6.0f;
constexpr uint32_t AM_PM_HOUR_12 = 12;
const double YOFFSET_START1 = 0.0;
const double YOFFSET_END1 = 1000.0;
const double TIME_PLUS = 1 * 100.0;
constexpr double COLUMN_VELOCITY = 2000.0;
const double FONT_SIZE_5 = 5.0;
const double FONT_SIZE_10 = 10.0;
const double FONT_SIZE_20 = 20.0;
constexpr double COLUMN_WIDTH = 200.0;
constexpr double SECLECTED_TEXTNODE_HEIGHT = 84.0;
constexpr double OTHER_TEXTNODE_HEIGHT = 54.0;
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
class TimePickerColumnPatternTestNg : public testing::Test {
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

void TimePickerColumnPatternTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void TimePickerColumnPatternTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void TimePickerColumnPatternTestNg::SetUp()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        return GetTheme(type);
    });
    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([](ThemeType type, int32_t themeScopeId) -> RefPtr<Theme> { return GetTheme(type); });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void TimePickerColumnPatternTestNg::TearDown()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    ViewStackProcessor::GetInstance()->ClearStack();
}

void TimePickerColumnPatternTestNg::CreateTimePickerColumnNode()
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


/**
 * @tc.name: TimePickerColumnPattern001
 * @tc.desc: Test TimePickerColumnPattern FlushCurrentOptions.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerColumnPatternTestNg, TimePickerColumnPattern001, TestSize.Level0)
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
    minuteColumnPattern->FlushCurrentOptions(true, true);
    minuteColumnPattern->FlushCurrentOptions(false, true);
}

/**
 * @tc.name: TimePickerColumnPattern002
 * @tc.desc: Test TimePickerColumnPattern FlushCurrentOptions.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerColumnPatternTestNg, TimePickerColumnPattern002, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);

    PickerTextStyle data;
    data.fontSize = Dimension(10);
    data.textColor = Color::RED;
    data.fontWeight = Ace::FontWeight::BOLD;
    TimePickerModelNG::GetInstance()->SetDisappearTextStyle(theme, data);
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
    minuteColumnPattern->FlushCurrentOptions(true, true);
    SystemProperties::SetDeviceType(DeviceType::UNKNOWN);
}

/**
 * @tc.name: TimePickerColumnPattern003
 * @tc.desc: Test TimePickerColumnPattern FlushCurrentOptions.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerColumnPatternTestNg, TimePickerColumnPattern003, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);

    PickerTextStyle data;
    data.fontSize = Dimension(10);
    data.textColor = Color::RED;
    data.fontWeight = Ace::FontWeight::BOLD;
    TimePickerModelNG::GetInstance()->SetNormalTextStyle(theme, data);
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
    minuteColumnPattern->FlushCurrentOptions(true, true);
    minuteColumnPattern->FlushCurrentOptions(false, true);
    minuteColumnPattern->UpdateToss(TOSS_DELTA);
}

/**
 * @tc.name: TimePickerColumnPattern004
 * @tc.desc: Test TimePickerColumnPattern UpdateToss.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerColumnPatternTestNg, TimePickerColumnPattern004, TestSize.Level0)
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
    minuteColumnPattern->UpdateToss(TOSS_DELTA);
}

/**
 * @tc.name: TimePickerColumnPattern005
 * @tc.desc: Test TimePickerColumnPattern UpdateToss.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerColumnPatternTestNg, TimePickerColumnPattern005, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);

    PickerTextStyle data;
    data.fontSize = Dimension(10);
    TimePickerModelNG::GetInstance()->SetSelectedTextStyle(theme, data);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto minuteColumn = allChildNode["minute"].Upgrade();
    ASSERT_NE(minuteColumn, nullptr);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_NE(minuteColumnPattern, nullptr);
    minuteColumnPattern->UpdateToss(0 - TOSS_DELTA);
    minuteColumnPattern->TossStoped();
}

/**
 * @tc.name: TimePickerColumnPattern006
 * @tc.desc: Test mouse event callback and touch event callback
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerColumnPatternTestNg, TimePickerColumnPattern006, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_TRUE(frameNode);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_TRUE(timePickerRowPattern);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto minuteColumn = allChildNode["minute"].Upgrade();
    ASSERT_TRUE(minuteColumn);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_TRUE(minuteColumnPattern);

    auto blendNode = minuteColumn->GetParent();
    ASSERT_NE(blendNode, nullptr);
    auto stackNode = blendNode->GetParent();
    ASSERT_NE(stackNode, nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto buttonNode = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    stackNode->children_.emplace_front(buttonNode);

    minuteColumnPattern->hoverColor_ = Color::BLACK;
    minuteColumnPattern->pressColor_ = Color::BLUE;

    minuteColumnPattern->InitMouseAndPressEvent();
    (*minuteColumnPattern->mouseEvent_)(true);
    EXPECT_TRUE(minuteColumnPattern->hovered_);
    auto renderContext = buttonNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetBackgroundColorValue(), Color::BLACK);
    (*minuteColumnPattern->mouseEvent_)(false);
    EXPECT_FALSE(minuteColumnPattern->hovered_);
    renderContext = buttonNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetBackgroundColorValue(), Color::TRANSPARENT);

    TouchEventInfo touchEventInfo("default");
    TouchLocationInfo touchLocationInfoDown(DEFAULT_FINGER_ID);
    touchLocationInfoDown.SetTouchType(TouchType::DOWN);
    const Offset offSet(OFFSET_X, OFFSET_Y);
    touchLocationInfoDown.SetLocalLocation(offSet);
    touchEventInfo.AddTouchLocationInfo(std::move(touchLocationInfoDown));

    (*minuteColumnPattern->touchListener_)(touchEventInfo);
    EXPECT_EQ(renderContext->GetBackgroundColorValue(), Color::BLUE);
    EXPECT_EQ(minuteColumnPattern->GetLocalDownDistance(), OFFSET_DISTANCE);

    TouchLocationInfo touchLocationInfoUp(DEFAULT_FINGER_ID);
    touchLocationInfoUp.SetTouchType(TouchType::UP);
    touchLocationInfoUp.SetLocalLocation(offSet);
    touchEventInfo.touches_.clear();
    touchEventInfo.AddTouchLocationInfo(std::move(touchLocationInfoUp));

    minuteColumnPattern->hovered_ = true;
    (*minuteColumnPattern->touchListener_)(touchEventInfo);
    EXPECT_EQ(renderContext->GetBackgroundColorValue(), Color::BLACK);
    EXPECT_EQ(minuteColumnPattern->GetLocalDownDistance(), 0.0f);

    minuteColumnPattern->hovered_ = false;
    (*minuteColumnPattern->touchListener_)(touchEventInfo);
    EXPECT_EQ(renderContext->GetBackgroundColorValue(), Color::TRANSPARENT);

    TouchLocationInfo touchLocationInfoMove(DEFAULT_FINGER_ID);
    touchLocationInfoMove.SetTouchType(TouchType::MOVE);
    touchLocationInfoMove.SetLocalLocation(offSet);
    touchEventInfo.touches_.clear();
    touchEventInfo.AddTouchLocationInfo(std::move(touchLocationInfoMove));

    minuteColumnPattern->hovered_ = true;
    (*minuteColumnPattern->touchListener_)(touchEventInfo);
    EXPECT_EQ(renderContext->GetBackgroundColorValue(), Color::BLACK);
    minuteColumnPattern->hovered_ = false;
    (*minuteColumnPattern->touchListener_)(touchEventInfo);
    EXPECT_EQ(renderContext->GetBackgroundColorValue(), Color::TRANSPARENT);
}

/**
 * @tc.name: TimePickerColumnPattern007
 * @tc.desc: Test OnDirtyLayoutWrapperSwap function
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerColumnPatternTestNg, TimePickerColumnPattern007, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_TRUE(frameNode);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_TRUE(timePickerRowPattern);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto minuteColumn = allChildNode["minute"].Upgrade();
    ASSERT_TRUE(minuteColumn);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_TRUE(minuteColumnPattern);

    auto* stack = ViewStackProcessor::GetInstance();
    auto buttonNode = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto weakNode = AceType::WeakClaim(AceType::RawPtr(buttonNode));
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        weakNode, AceType::MakeRefPtr<GeometryNode>(), AceType::MakeRefPtr<LayoutProperty>());
    DirtySwapConfig dirtySwapConfig;
    EXPECT_FALSE(minuteColumnPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig));
    dirtySwapConfig.frameSizeChange = true;
    EXPECT_TRUE(minuteColumnPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig));
    EXPECT_FALSE(minuteColumnPattern->OnDirtyLayoutWrapperSwap(nullptr, dirtySwapConfig));
}

/**
 * @tc.name: TimePickerColumnPattern008
 * @tc.desc: Test FlushCurrentOptions and UpdateTextPropertiesLinear function while the amount of child nodes
 * not equal to showOptionCount
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerColumnPatternTestNg, TimePickerColumnPattern008, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_TRUE(frameNode);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_TRUE(timePickerRowPattern);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto minuteColumn = allChildNode["minute"].Upgrade();
    ASSERT_TRUE(minuteColumn);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_TRUE(minuteColumnPattern);

    minuteColumnPattern->SetShowCount(INVALID_SHOW_COUNT);
    auto showOptionCount = minuteColumnPattern->GetShowCount();
    auto child = minuteColumn->GetChildren();
    EXPECT_NE(showOptionCount, child.size());
    minuteColumnPattern->FlushCurrentOptions();
    minuteColumnPattern->UpdateTextPropertiesLinear(true, SCALE);
}

/**
 * @tc.name: TimePickerColumnPattern009
 * @tc.desc: Test TextPropertiesLinearAnimation function while indexes greater than the amount of animation properties
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerColumnPatternTestNg, TimePickerColumnPattern009, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_TRUE(frameNode);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_TRUE(timePickerRowPattern);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto minuteColumn = allChildNode["minute"].Upgrade();
    ASSERT_TRUE(minuteColumn);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_TRUE(minuteColumnPattern);

    EXPECT_GE(INDEX, minuteColumnPattern->animationProperties_.size());
    minuteColumnPattern->TextPropertiesLinearAnimation(
        AceType::MakeRefPtr<TextLayoutProperty>(), INDEX, SHOW_COUNT, true, SCALE);
}

/**
 * @tc.name: TimePickerColumnPattern010
 * @tc.desc: Test pan event actions
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerColumnPatternTestNg, TimePickerColumnPattern010, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_TRUE(frameNode);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_TRUE(timePickerRowPattern);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto minuteColumn = allChildNode["minute"].Upgrade();
    ASSERT_TRUE(minuteColumn);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_TRUE(minuteColumnPattern);

    auto eventHub = frameNode->GetEventHub<EventHub>();
    auto gestureHub = eventHub->GetOrCreateGestureEventHub();
    minuteColumnPattern->InitPanEvent(gestureHub);
    auto panEvent = minuteColumnPattern->panEvent_;

    // action start
    GestureEvent gestureEvent;
    Point point(OFFSET_X, OFFSET_Y);
    gestureEvent.SetGlobalPoint(point);
    panEvent->actionStart_(gestureEvent);
    EXPECT_EQ(minuteColumnPattern->GetToss()->yStart_, OFFSET_Y);
    EXPECT_EQ(minuteColumnPattern->yOffset_, YOFFSET_START1);
    EXPECT_EQ(minuteColumnPattern->yLast_, OFFSET_Y);
    EXPECT_TRUE(minuteColumnPattern->pressed_);

    // action update
    auto options = minuteColumnPattern->GetOptions();
    auto totalOptionCount = options[minuteColumn];

    gestureEvent.SetInputEventType(InputEventType::AXIS);
    gestureEvent.SetSourceTool(SourceTool::MOUSE);
    Offset deltaOffset(0.0, -1.0);
    gestureEvent.SetDelta(deltaOffset);
    auto preIndex = minuteColumnPattern->GetCurrentIndex();
    panEvent->actionUpdate_(gestureEvent);
    auto currentIndex = minuteColumnPattern->GetCurrentIndex();
    EXPECT_EQ(currentIndex, (preIndex + 1) % totalOptionCount);

    deltaOffset.SetY(1.0);
    gestureEvent.SetDelta(deltaOffset);
    preIndex = minuteColumnPattern->GetCurrentIndex();
    panEvent->actionUpdate_(gestureEvent);
    currentIndex = minuteColumnPattern->GetCurrentIndex();
    EXPECT_EQ(currentIndex, (preIndex + totalOptionCount - 1) % totalOptionCount);

    point.SetY(OFFSET_Y + 2);
    gestureEvent.SetGlobalPoint(point);
    gestureEvent.SetInputEventType(InputEventType::MOUSE_BUTTON);
    minuteColumnPattern->SetCurrentIndex(totalOptionCount);
    panEvent->actionUpdate_(gestureEvent);
    EXPECT_EQ(minuteColumnPattern->GetToss()->yEnd_, OFFSET_Y + 2);
    EXPECT_TRUE(minuteColumnPattern->CanMove(true));

    minuteColumnPattern->SetCurrentIndex(totalOptionCount - 1);
    panEvent->actionUpdate_(gestureEvent);

    // action end
    minuteColumnPattern->scrollDelta_ = TOSS_DELTA;
    minuteColumnPattern->animationCreated_ = false;
    panEvent->actionEnd_(gestureEvent);
    EXPECT_FALSE(minuteColumnPattern->pressed_);
    EXPECT_EQ(minuteColumnPattern->yOffset_, 0.0);
    EXPECT_EQ(minuteColumnPattern->yLast_, 0.0);
    EXPECT_EQ(minuteColumnPattern->scrollDelta_, 0.0);

    minuteColumnPattern->scrollDelta_ = TOSS_DELTA;
    minuteColumnPattern->animationCreated_ = true;
    panEvent->actionEnd_(gestureEvent);

    minuteColumnPattern->pressed_ = true;
    minuteColumnPattern->yOffset_ = OFFSET_Y;
    minuteColumnPattern->yLast_ = OFFSET_Y;
    gestureEvent.SetInputEventType(InputEventType::AXIS);
    panEvent->actionEnd_(gestureEvent);
    EXPECT_EQ(minuteColumnPattern->yOffset_, OFFSET_Y);
    EXPECT_EQ(minuteColumnPattern->yLast_, OFFSET_Y);
    EXPECT_TRUE(minuteColumnPattern->pressed_);

    // action cancel
    minuteColumnPattern->animationCreated_ = false;
    panEvent->actionCancel_();
    EXPECT_FALSE(minuteColumnPattern->pressed_);
    EXPECT_EQ(minuteColumnPattern->yOffset_, 0.0);
    EXPECT_EQ(minuteColumnPattern->yLast_, 0.0);
    EXPECT_EQ(minuteColumnPattern->scrollDelta_, 0.0);

    // action end for OnAccessibilityEvent
    minuteColumnPattern->SetShowCount(0);
    EXPECT_FALSE(minuteColumnPattern->NotLoopOptions());
    auto toss = minuteColumnPattern->GetToss();
    toss->SetStart(YOFFSET_START1);
    toss->SetEnd(YOFFSET_END1);
    toss->timeEnd_ = toss->GetCurrentTime() + TIME_PLUS;
    EXPECT_FALSE(toss->Play());
    gestureEvent.SetInputEventType(InputEventType::TOUCH_SCREEN);
    panEvent->actionEnd_(gestureEvent);
    EXPECT_FALSE(minuteColumnPattern->pressed_);
}

/**
 * @tc.name: TimePickerColumnPattern012
 * @tc.desc: Test ScrollOption function
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerColumnPatternTestNg, TimePickerColumnPattern012, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_TRUE(frameNode);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_TRUE(timePickerRowPattern);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto minuteColumn = allChildNode["minute"].Upgrade();
    ASSERT_TRUE(minuteColumn);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_TRUE(minuteColumnPattern);

    minuteColumnPattern->jumpInterval_ = 0;
    minuteColumnPattern->ScrollOption(TOSS_DELTA);

    auto child = minuteColumn->GetChildren();
    auto iter = child.begin();
    auto textNode = AceType::DynamicCast<FrameNode>(*iter);
    ASSERT_TRUE(textNode);
    auto textPattern = textNode->GetPattern<TextPattern>();
    ASSERT_TRUE(textPattern);
    RefPtr<TextLayoutProperty> textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_TRUE(textLayoutProperty);

    minuteColumnPattern->jumpInterval_ = DEFAULT_JUMP_INTERVAL;
    minuteColumnPattern->ScrollOption(TOSS_DELTA);
    double scale = fabs(TOSS_DELTA) / (DEFAULT_JUMP_INTERVAL * 2);
    uint32_t showCount = minuteColumnPattern->GetShowCount();
    for (uint32_t index = 0; index < showCount; index++) {
        Dimension startFontSize = minuteColumnPattern->animationProperties_[index].fontSize;
        Dimension endFontSize = minuteColumnPattern->animationProperties_[index].downFontSize;
        Dimension updatedFontSize = textLayoutProperty->GetFontSizeValue(startFontSize);
        EXPECT_EQ(startFontSize + (endFontSize - startFontSize) * scale, updatedFontSize);
    }
}

/**
 * @tc.name: TimePickerColumnPattern013
 * @tc.desc: Test SetDividerHeight function
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerColumnPatternTestNg, TimePickerColumnPattern013, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_TRUE(frameNode);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_TRUE(timePickerRowPattern);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto minuteColumn = allChildNode["minute"].Upgrade();
    ASSERT_TRUE(minuteColumn);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_TRUE(minuteColumnPattern);

    auto gradientHeight = theme->GetGradientHeight().Value();
    auto dividerSpacing = theme->GetDividerSpacing().Value();

    minuteColumnPattern->SetDividerHeight(OPTION_COUNT_PHONE_LANDSCAPE + 1);
    EXPECT_EQ(minuteColumnPattern->gradientHeight_, gradientHeight * TEXT_HEIGHT_NUMBER);
    EXPECT_EQ(
        minuteColumnPattern->dividerHeight_, minuteColumnPattern->gradientHeight_ + gradientHeight + dividerSpacing);
    EXPECT_EQ(minuteColumnPattern->dividerSpacingWidth_, dividerSpacing * TEXT_WEIGHT_NUMBER);
}

/**
 * @tc.name: TimePickerColumnPattern014
 * @tc.desc: Test UpdateColumnChildPosition function abnormal situation
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerColumnPatternTestNg, TimePickerColumnPattern014, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_TRUE(frameNode);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_TRUE(timePickerRowPattern);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto minuteColumn = allChildNode["minute"].Upgrade();
    ASSERT_TRUE(minuteColumn);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_TRUE(minuteColumnPattern);

    minuteColumnPattern->yOffset_ = OFFSET_Y;
    auto options = minuteColumnPattern->GetOptions();
    int totalOptionCount = static_cast<int>(options[minuteColumn]);
    minuteColumnPattern->SetCurrentIndex(totalOptionCount);
    minuteColumnPattern->UpdateColumnChildPosition(OFFSET_X);
    EXPECT_TRUE(minuteColumnPattern->CanMove(true));
}

/**
 * @tc.name: TimePickerColumnPattern015
 * @tc.desc: Test OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerColumnPatternTestNg, TimePickerColumnPattern015, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_TRUE(frameNode);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_TRUE(timePickerRowPattern);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto minuteColumn = allChildNode["minute"].Upgrade();
    ASSERT_TRUE(minuteColumn);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_TRUE(minuteColumnPattern);

    auto eventHub = frameNode->GetEventHub<EventHub>();
    auto focusHub = eventHub->GetOrCreateFocusHub();
    minuteColumnPattern->InitOnKeyEvent(focusHub);

    KeyEvent keyEvent(KeyCode::KEY_DPAD_UP, KeyAction::UP);
    EXPECT_FALSE(focusHub->ProcessOnKeyEventInternal(keyEvent));
    keyEvent.action = KeyAction::DOWN;
    EXPECT_TRUE(focusHub->ProcessOnKeyEventInternal(keyEvent));
    keyEvent.code = KeyCode::KEY_DPAD_DOWN;
    EXPECT_TRUE(focusHub->ProcessOnKeyEventInternal(keyEvent));
    keyEvent.code = KeyCode::KEY_DPAD_CENTER;
    EXPECT_FALSE(focusHub->ProcessOnKeyEventInternal(keyEvent));
}

/**
 * @tc.name: TimePickerColumnPattern016
 * @tc.desc: Test TossAnimationController.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerColumnPatternTestNg, TimePickerColumnPattern016, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create TimePickerColumn.
     */
    CreateTimePickerColumnNode();

    /**
     * @tc.steps: step2. Set velocity and toss offset .
     */
    ASSERT_NE(columnPattern_, nullptr);
    columnPattern_->SetMainVelocity(COLUMN_VELOCITY);
    auto toss = columnPattern_->GetToss();
    ASSERT_NE(toss, nullptr);
    toss->SetStart(YOFFSET_START1);
    toss->SetEnd(YOFFSET_END1);
    toss->timeEnd_ = toss->timeStart_ + TIME_PLUS;

    /**
     * @tc.step: step3. call toss::Play and check yStart_ and yEnd_.
     * @tc.expected: yStart_ and yEnd_ same as setting, return value is true.
     */
    auto ret = toss->Play();
    EXPECT_EQ(toss->yStart_, YOFFSET_START1);
    EXPECT_EQ(toss->yEnd_, YOFFSET_END1);
    EXPECT_TRUE(ret);
    toss->StopTossAnimation();
    EXPECT_FALSE(columnPattern_->GetTossStatus());
}

/**
 * @tc.name: TimePickerColumnPattern019
 * @tc.desc: Test FlushAnimationTextProperties.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerColumnPatternTestNg, TimePickerColumnPattern019, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);

    /**
     * @tc.step: step1. create column pattern.
     */
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

    /**
     * @tc.step: step2. create cloumn pattern and call FlushAnimationTextProperties.
     * @tc.expected: cover branch animationProperties_ size is 0.
     */
    minuteColumnPattern->animationProperties_.clear();
    minuteColumnPattern->FlushAnimationTextProperties(false);
    EXPECT_EQ(0, minuteColumnPattern->animationProperties_.size());

    /**
     * @tc.step: step3. construct columnPattern animationProperties_ and call FlushAnimationTextProperties.
     * @tc.expected: cover branch animationProperties_ size is 1 and fontSize meet expectation.
     */
    std::vector<TextProperties> animationProperties;
    TextProperties properties1;
    properties1.upFontSize = Dimension(FONT_SIZE_5);
    properties1.fontSize = Dimension(FONT_SIZE_20);
    properties1.downFontSize = Dimension(FONT_SIZE_5);
    properties1.upColor = Color::RED;
    properties1.currentColor = Color::RED;
    properties1.downColor = Color::RED;
    animationProperties.emplace_back(properties1);
    minuteColumnPattern->animationProperties_ = animationProperties;

    minuteColumnPattern->FlushAnimationTextProperties(false);
    Dimension result = minuteColumnPattern->animationProperties_[0].fontSize;
    EXPECT_EQ(Dimension(FONT_SIZE_10), result);
    minuteColumnPattern->FlushAnimationTextProperties(true);
    result = minuteColumnPattern->animationProperties_[0].fontSize;
    EXPECT_EQ(Dimension(FONT_SIZE_5), result);

    /**
     * @tc.step: step4. add construct columnPattern animationProperties_ and call FlushAnimationTextProperties.
     * @tc.expected: cover branch animationProperties_ size is more than 1 and fontSize meet expectation.
     */
    TextProperties properties2;
    properties2.upFontSize = Dimension(FONT_SIZE_10);
    properties2.fontSize = Dimension(FONT_SIZE_20);
    properties2.downFontSize = Dimension(FONT_SIZE_10);
    properties2.upColor = Color::RED;
    properties2.currentColor = Color::RED;
    properties2.downColor = Color::RED;
    animationProperties.emplace_back(properties2);
    minuteColumnPattern->animationProperties_ = animationProperties;

    minuteColumnPattern->FlushAnimationTextProperties(false);
    result = minuteColumnPattern->animationProperties_[0].fontSize;
    EXPECT_EQ(Dimension(FONT_SIZE_10), result);
    minuteColumnPattern->FlushAnimationTextProperties(true);
    result = minuteColumnPattern->animationProperties_[0].fontSize;
    EXPECT_EQ(Dimension(FONT_SIZE_20), result);
}

/**
 * @tc.name: TimePickerColumnPattern020
 * @tc.desc: Test UpdateFinishToss.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerColumnPatternTestNg, TimePickerColumnPattern020, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);

    /**
     * @tc.step: step1. create column pattern.
     */
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

    /**
     * @tc.step: step2. call UpdateFinishToss.
     * @tc.expected: call UpdateFinishToss and CanMove() meet expectation.
     */
    minuteColumnPattern->UpdateFinishToss(OFFSET_Y);
    bool result = minuteColumnPattern->CanMove(false);
    EXPECT_TRUE(result);
    minuteColumnPattern->UpdateFinishToss(OFFSET_Y_0);
    result = minuteColumnPattern->CanMove(false);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: TimePickerColumnPattern021
 * @tc.desc: Test PlayRestAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerColumnPatternTestNg, TimePickerColumnPattern021, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);

    /**
     * @tc.step: step1. create column pattern.
     */
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

    /**
     * @tc.step: step2. call UpdatPlayRestAnimation.
     * @tc.expected: call UpdatPlayRestAnimation and scrollDelta_ valus meet expectation.
     */
    minuteColumnPattern->PlayRestAnimation();
    EXPECT_EQ(0.0f, minuteColumnPattern->scrollDelta_);

    /**
     * @tc.step: step3. set scrollDelta_ value and call UpdatPlayRestAnimation.
     * @tc.expected: call UpdatPlayRestAnimation and scrollDelta_ valus meet expectation.
     */
    minuteColumnPattern->scrollDelta_ = 20;
    minuteColumnPattern->PlayRestAnimation();
    EXPECT_EQ(10.0f, minuteColumnPattern->scrollDelta_);
}

/**
 * @tc.name: TimePickerColumnPattern022
 * @tc.desc: Test TimePickerColumnPattern AddHotZoneRectToText.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerColumnPatternTestNg, TimePickerColumnPattern022, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create columnPattern and Set text node height.
     */
    CreateTimePickerColumnNode();
    ASSERT_NE(columnPattern_, nullptr);
    ASSERT_NE(columnNode_, nullptr);
    auto childSize = static_cast<int32_t>(columnNode_->GetChildren().size());
    auto midSize = childSize / MIDDLE_OF_COUNTS;
    columnPattern_->optionProperties_[midSize].height = SECLECTED_TEXTNODE_HEIGHT;
    columnPattern_->optionProperties_[midSize - 1].height = OTHER_TEXTNODE_HEIGHT;

    /**
     * @tc.steps: step2. Set height 50.0 for column and call AddHotZoneRectToText.
     * @tc.expected: The middle textnode hot zone set is correct.
     */
    float height = 50.0f;
    columnPattern_->size_.SetWidth(COLUMN_WIDTH);
    columnPattern_->size_.SetHeight(height);
    columnPattern_->AddHotZoneRectToText();
    auto childNode = AceType::DynamicCast<FrameNode>(columnNode_->GetChildAtIndex(midSize));
    ASSERT_NE(childNode, nullptr);
    auto gestureEventHub = childNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);
    auto responseRegion = gestureEventHub->GetResponseRegion().back();
    EXPECT_EQ(responseRegion.GetWidth().Value(), COLUMN_WIDTH);
    EXPECT_EQ(responseRegion.GetHeight().Value(), height);

    /**
     * @tc.steps: step3. Set height 100.0 for column and call AddHotZoneRectToText.
     * @tc.expected: The candidate textnode hot zone set is correct.
     */
    height = 100.0f;
    columnPattern_->size_.SetHeight(height);
    columnPattern_->AddHotZoneRectToText();
    childNode = AceType::DynamicCast<FrameNode>(columnNode_->GetChildAtIndex(midSize - 1));
    ASSERT_NE(childNode, nullptr);
    gestureEventHub = childNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);
    responseRegion = gestureEventHub->GetResponseRegion().back();
    EXPECT_EQ(responseRegion.GetWidth().Value(), COLUMN_WIDTH);
    EXPECT_EQ(responseRegion.GetHeight().Value(), (height - SECLECTED_TEXTNODE_HEIGHT) / MIDDLE_OF_COUNTS);

    /**
     * @tc.steps: step4. Set height 200.0 for column and call AddHotZoneRectToText.
     * @tc.expected: The disappear textnode hot zone set is correct.
     */
    height = 200.0f;
    columnPattern_->size_.SetHeight(height);
    columnPattern_->AddHotZoneRectToText();
    childNode = AceType::DynamicCast<FrameNode>(columnNode_->GetChildAtIndex(midSize - MIDDLE_OF_COUNTS));
    ASSERT_NE(childNode, nullptr);
    gestureEventHub = childNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);
    responseRegion = gestureEventHub->GetResponseRegion().back();
    EXPECT_EQ(responseRegion.GetWidth().Value(), COLUMN_WIDTH);
    EXPECT_EQ(responseRegion.GetHeight().Value(),
        (height - SECLECTED_TEXTNODE_HEIGHT - MIDDLE_OF_COUNTS * OTHER_TEXTNODE_HEIGHT) / MIDDLE_OF_COUNTS);
}

/**
 * @tc.name: TimePickerColumnPattern023
 * @tc.desc: Test TimePickerColumnPattern AddHotZoneRectToText.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerColumnPatternTestNg, TimePickerColumnPattern023, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create columnPattern and clear optionProperties_.
     */
    CreateTimePickerColumnNode();
    ASSERT_NE(columnPattern_, nullptr);
    ASSERT_NE(columnNode_, nullptr);
    for (int32_t i = 0; i < SHOW_COUNT; i++) {
        columnNode_->RemoveChildAtIndex(0);
    }
    /**
     * @tc.steps: step2. Call AddHotZoneRectToText.
     * @tc.expected: No crash.
     */
    columnPattern_->AddHotZoneRectToText();

    /**
     * @tc.steps: step3. Create columnPattern and clear optionProperties_.
     */
    CreateTimePickerColumnNode();
    ASSERT_NE(columnPattern_, nullptr);
    ASSERT_NE(columnNode_, nullptr);
    constexpr float height = 100.0f;
    auto childSize = static_cast<int32_t>(columnNode_->GetChildren().size());
    auto midSize = childSize / MIDDLE_OF_COUNTS;

    /**
     * @tc.steps: step4. Call AddHotZoneRectToText.
     * @tc.expected: No crash.
     */
    columnPattern_->size_.SetHeight(height);
    columnPattern_->optionProperties_.clear();
    columnPattern_->AddHotZoneRectToText();
    auto childNode = AceType::DynamicCast<FrameNode>(columnNode_->GetChildAtIndex(midSize));
    ASSERT_NE(childNode, nullptr);
    auto gestureEventHub = childNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);
    EXPECT_TRUE(gestureEventHub->GetResponseRegion().empty());
}

/**
 * @tc.name: TimePickerRowPattern032
 * @tc.desc: Test TimePickerRowPattern GetCurrentEnterTime using 12-hour system
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerColumnPatternTestNg, TimePickerRowPattern032, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    timePickerRowPattern->SetHour24(false);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto amPmColumn = allChildNode["amPm"].Upgrade();
    ASSERT_NE(amPmColumn, nullptr);
    auto amPmPickerColumnPattern = amPmColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_NE(amPmPickerColumnPattern, nullptr);
    auto hourColumn = allChildNode["hour"].Upgrade();
    ASSERT_NE(hourColumn, nullptr);
    auto hourPickerColumnPattern = hourColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_NE(hourPickerColumnPattern, nullptr);
    auto minuteColumn = allChildNode["minute"].Upgrade();
    ASSERT_NE(minuteColumn, nullptr);
    auto minutePickerColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_NE(minutePickerColumnPattern, nullptr);

    amPmPickerColumnPattern->SetEnterIndex(0);
    hourPickerColumnPattern->SetEnterIndex(AM_PM_HOUR_12 - 1);
    minutePickerColumnPattern->SetEnterIndex(0);
    EXPECT_EQ(timePickerRowPattern->GetCurrentEnterTime().GetHour(), 0);
    EXPECT_EQ(timePickerRowPattern->GetCurrentEnterTime().GetMinute(), minutePickerColumnPattern->GetEnterIndex());

    hourPickerColumnPattern->SetEnterIndex(AM_PM_HOUR_12 - 2);
    EXPECT_EQ(timePickerRowPattern->GetCurrentEnterTime().GetHour(), AM_PM_HOUR_12 - 1);

    amPmPickerColumnPattern->SetEnterIndex(1);
    EXPECT_EQ(timePickerRowPattern->GetCurrentEnterTime().GetHour(), AM_PM_HOUR_12 * 2 - 1);

    hourPickerColumnPattern->SetEnterIndex(AM_PM_HOUR_12 - 1);
    EXPECT_EQ(timePickerRowPattern->GetCurrentEnterTime().GetHour(), AM_PM_HOUR_12);
}
} // namespace OHOS::Ace::NG
