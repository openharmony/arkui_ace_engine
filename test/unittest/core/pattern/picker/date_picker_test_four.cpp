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
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_default.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/picker/datepicker_pattern.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const InspectorFilter filter;
constexpr double UP_FONT_SIZE = 5.0;
constexpr double TEST_FONT_SIZE = 10.0;
constexpr double DOWN_FONT_SIZE = 20.0;
constexpr int32_t START_YEAR_BEFORE = 1990;
constexpr int32_t START_YEAR = 1980;
constexpr int32_t SELECTED_YEAR = 2000;
constexpr int32_t END_YEAR = 2090;
constexpr int32_t CURRENT_DAY = 5;
const int BIG_SHOWCOUNT = 5;
const int SMALL_SHOWCOUNT = 3;
const int MIDDLE_OF_COUNTS = 2;
const vector<int> DEFAULT_DATE = { 1999, 9, 9 };
const std::string CONNECTER = "-";
const std::vector<int> DEFAULT_VALUE = { 1970, 1971, 1972 };
const double OFFSET_Y = 8.0;
const SizeF TEST_FRAME_SIZE1 { 20, 50 };
const SizeF TEST_FRAME_SIZE2 { 0, 0 };
const std::string SELECTED_DATE_STRING = R"({"year":2000,"month":5,"day":6,"hour":1,"minute":1,"status":-1})";
constexpr double COLUMN_WIDTH = 200.0;
constexpr double SECLECTED_TEXTNODE_HEIGHT = 84.0;
constexpr double OTHER_TEXTNODE_HEIGHT = 54.0;
const std::string AM = "上午";
const std::string PM = "下午";
const std::string COLON = ":";
const std::string ZERO = "0";
} // namespace

class DatePickerTestFour : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void CreateDatePickerColumnNode();
    DatePickerSettingData CreateDatePickerSettingData();

    RefPtr<FrameNode> columnNode_;
    RefPtr<DatePickerColumnPattern> columnPattern_;
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

void DatePickerTestFour::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void DatePickerTestFour::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void DatePickerTestFour::SetUp()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
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
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void DatePickerTestFour::TearDown()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    ViewStackProcessor::GetInstance()->ClearStack();
}

void DatePickerTestFour::CreateDatePickerColumnNode()
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();

    auto stackNode = AceType::DynamicCast<FrameNode>(frameNode->GetFirstChild());
    ASSERT_NE(stackNode, nullptr);
    auto blendNode = AceType::DynamicCast<FrameNode>(stackNode->GetLastChild());
    ASSERT_NE(blendNode, nullptr);
    columnNode_ = AceType::DynamicCast<FrameNode>(blendNode->GetLastChild());
    ASSERT_NE(columnNode_, nullptr);
    columnNode_->MarkModifyDone();
    columnPattern_ = columnNode_->GetPattern<DatePickerColumnPattern>();
    ASSERT_NE(columnPattern_, nullptr);
    columnPattern_->OnAttachToFrameNode();
}

DatePickerSettingData DatePickerTestFour::CreateDatePickerSettingData()
{
    DatePickerSettingData settingData;
    settingData.datePickerProperty["start"] = PickerDate(START_YEAR_BEFORE, 1, 1);
    settingData.datePickerProperty["end"] = PickerDate(END_YEAR, 1, 1);
    settingData.datePickerProperty["selected"] = PickerDate(SELECTED_YEAR, CURRENT_DAY, CURRENT_DAY);
    settingData.timePickerProperty["selected"] = PickerTime(1, 1, 1);
    settingData.isLunar = false;
    settingData.showTime = true;
    return settingData;
}

/**
 * @tc.name: DateTimeAnimationControllerTest001
 * @tc.desc: Test DateTimeAnimationController PlayOldColumnOpacityInAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestFour, DateTimeAnimationControllerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set DatePickerSettingData and create dateNode.
     */
    DatePickerSettingData settingData = CreateDatePickerSettingData();
    auto dateNode = DatePickerDialogView::CreateDateNode(ElementRegister::GetInstance()->MakeUniqueId(),
        settingData.datePickerProperty, settingData.properties, settingData.isLunar, false);
    ASSERT_NE(dateNode, nullptr);
    auto monthDaysNode = DatePickerDialogView::CreateDateNode(ElementRegister::GetInstance()->MakeUniqueId(),
        settingData.datePickerProperty, settingData.properties, settingData.isLunar, true);
    ASSERT_NE(monthDaysNode, nullptr);
    auto timeNode = DatePickerDialogView::CreateTimeNode(
        settingData.timePickerProperty, settingData.properties, settingData.useMilitary);
    ASSERT_NE(timeNode, nullptr);

    /**
     * @tc.steps: step2. PlayOldColumnOpacityInAnimation without datePicker.
     * @tc.expected: Opacity of render is set.
     */
    auto dateTimeAnimationController = AceType::MakeRefPtr<DateTimeAnimationController>();
    dateTimeAnimationController->SetMonthDays(monthDaysNode);
    dateTimeAnimationController->SetTimePicker(timeNode);
    auto monthDays = dateTimeAnimationController->monthDays_.Upgrade();
    ASSERT_NE(monthDays, nullptr);
    auto monthDaysRender = monthDays->GetRenderContext();
    ASSERT_NE(monthDaysRender, nullptr);
    auto timePicker = dateTimeAnimationController->timePicker_.Upgrade();
    ASSERT_NE(timePicker, nullptr);
    auto timePickerRender = timePicker->GetRenderContext();
    ASSERT_NE(timePickerRender, nullptr);
    dateTimeAnimationController->PlayOldColumnOpacityInAnimation();
    EXPECT_FLOAT_EQ(monthDaysRender->GetOpacityValue(), 0);
    EXPECT_FLOAT_EQ(timePickerRender->GetOpacityValue(), 0);

    /**
     * @tc.steps: step3. Set datePicker.
     */
    auto tempChildren = dateNode->children_;
    dateNode->children_.clear();
    dateTimeAnimationController->SetDatePicker(dateNode);
    dateNode->children_ = tempChildren;
    dateTimeAnimationController->SetDatePicker(dateNode);
    auto datePicker = dateTimeAnimationController->datePicker_.Upgrade();
    ASSERT_NE(datePicker, nullptr);
    auto datePickerLayoutProperty = datePicker->GetLayoutProperty<LayoutProperty>();
    ASSERT_NE(datePickerLayoutProperty, nullptr);

    /**
     * @tc.steps: step4. PlayOldColumnOpacityInAnimation with datePicker.
     * @tc.expected: datePicker's visibility is set visible.
     */
    monthDaysRender->UpdateOpacity(0.0f);
    timePickerRender->UpdateOpacity(0.0f);
    dateTimeAnimationController->PlayOldColumnOpacityInAnimation();
    EXPECT_FLOAT_EQ(monthDaysRender->GetOpacityValue(), 0);
    EXPECT_FLOAT_EQ(timePickerRender->GetOpacityValue(), 0);
    EXPECT_EQ(datePickerLayoutProperty->GetVisibilityValue(), VisibleType::VISIBLE);

    /**
     * @tc.steps: step5. PlayOldColumnOpacityInAnimation without datePicker layoutProperty.
     * @tc.expected: datePicker's visibility is not set.
     */
    datePicker->layoutProperty_ = nullptr;
    monthDaysRender->UpdateOpacity(0.0f);
    timePickerRender->UpdateOpacity(0.0f);
    dateTimeAnimationController->PlayOldColumnOpacityInAnimation();
    EXPECT_FLOAT_EQ(monthDaysRender->GetOpacityValue(), 0);
    EXPECT_FLOAT_EQ(timePickerRender->GetOpacityValue(), 0);
}

/**
 * @tc.name: DateTimeAnimationControllerTest002
 * @tc.desc: Test DateTimeAnimationController PlayOldColumnOpacityInAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestFour, DateTimeAnimationControllerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set DatePickerSettingData and create dateNode.
     */
    DatePickerSettingData settingData;
    settingData.datePickerProperty["start"] = PickerDate(START_YEAR_BEFORE, 1, 1);
    settingData.datePickerProperty["end"] = PickerDate(END_YEAR, 1, 1);
    settingData.datePickerProperty["selected"] = PickerDate(SELECTED_YEAR, CURRENT_DAY, CURRENT_DAY);
    settingData.timePickerProperty["selected"] = PickerTime(1, 1, 1);
    settingData.isLunar = false;
    settingData.showTime = true;
    auto dateNode = DatePickerDialogView::CreateDateNode(ElementRegister::GetInstance()->MakeUniqueId(),
        settingData.datePickerProperty, settingData.properties, settingData.isLunar, false);
    ASSERT_NE(dateNode, nullptr);
    auto monthDaysNode = DatePickerDialogView::CreateDateNode(ElementRegister::GetInstance()->MakeUniqueId(),
        settingData.datePickerProperty, settingData.properties, settingData.isLunar, true);
    ASSERT_NE(monthDaysNode, nullptr);
    auto timeNode = DatePickerDialogView::CreateTimeNode(
        settingData.timePickerProperty, settingData.properties, settingData.useMilitary);
    ASSERT_NE(timeNode, nullptr);

    /**
     * @tc.steps: step2. StopOldColumnOpacityAnimation while oldColumnOpacityAnimation not set.
     */
    auto dateTimeAnimationController = AceType::MakeRefPtr<DateTimeAnimationController>();
    dateTimeAnimationController->StopOldColumnOpacityInAnimation();
    dateTimeAnimationController->StopOldColumnOpacityOutAnimation();

    /**
     * @tc.steps: step3. StopOldColumnOpacityAnimation after oldColumnOpacityAnimation set.
     * @tc.expected: OldColumnOpacityAnimations is clear.
     */
    dateTimeAnimationController->SetMonthDays(monthDaysNode);
    dateTimeAnimationController->SetTimePicker(timeNode);
    dateTimeAnimationController->PlayOldColumnOpacityInAnimation();
    dateTimeAnimationController->PlayOldColumnOpacityOutAnimation();

    /**
     * @tc.steps: step4. Play animation.
     * @tc.expected: isInAnimationPlaying_ or isOutAnimationPlaying_ is set.
     */
    dateTimeAnimationController->SetDatePicker(dateNode);
    dateTimeAnimationController->created_ = false;
    dateTimeAnimationController->Play(true);
    EXPECT_TRUE(dateTimeAnimationController->created_);
    EXPECT_FALSE(dateTimeAnimationController->isInAnimationPlaying_);
    dateTimeAnimationController->isInAnimationPlaying_ = false;
    dateTimeAnimationController->Play(false);
    EXPECT_FALSE(dateTimeAnimationController->isOutAnimationPlaying_);
}

/**
 * @tc.name: DatePickerColumnPatternTest008
 * @tc.desc: Test DatePickerColumnPattern InitMouseAndPressEvent.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestFour, DatePickerColumnPatternTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. InitMouseAndPressEvent while mouseEvent_ or touchListener_ is null.
     * @tc.expected: Function called successfully.
     */
    CreateDatePickerColumnNode();
    ASSERT_NE(columnNode_, nullptr);
    ASSERT_NE(columnPattern_, nullptr);
    columnPattern_->mouseEvent_ = AceType::MakeRefPtr<InputEvent>([](bool isHover) {});
    columnPattern_->touchListener_ = nullptr;
    columnPattern_->InitMouseAndPressEvent();
    columnPattern_->mouseEvent_ = nullptr;
    columnPattern_->touchListener_ = AceType::MakeRefPtr<TouchEventImpl>([](const TouchEventInfo& info) {});
    columnPattern_->InitMouseAndPressEvent();

    /**
     * @tc.steps: step2. Get touchListener.
     */
    columnPattern_->mouseEvent_ = nullptr;
    columnPattern_->touchListener_ = nullptr;
    auto columnEventHub = columnNode_->GetEventHub<EventHub>();
    ASSERT_NE(columnEventHub, nullptr);
    auto columnGesture = columnEventHub->GetOrCreateGestureEventHub();
    ASSERT_NE(columnGesture, nullptr);
    columnPattern_->InitMouseAndPressEvent();
    auto touchListener = columnGesture->touchEventActuator_->touchEvents_.back()->callback_;

    /**
     * @tc.steps: step3. Set TouchType DOWN and call callback.
     * @tc.expected: animationBreak_ and clickBreak_ are set false.
     */
    TouchEventInfo touchEventInfo("touch");
    TouchLocationInfo localLocationInfo(1);
    localLocationInfo.SetTouchType(TouchType::DOWN);
    std::list<TouchLocationInfo> touches;
    touches.emplace_back(localLocationInfo);
    touchEventInfo.touches_ = touches;
    touchListener(touchEventInfo);
    EXPECT_FALSE(columnPattern_->animationBreak_);
    EXPECT_FALSE(columnPattern_->clickBreak_);

    /**
     * @tc.steps: step4. Set tossStatus true and call callback.
     * @tc.expected: touchBreak_ animationBreak_ and clickBreak_ are set true.
     */
    columnPattern_->SetTossStatus(true);

    auto toss = columnPattern_->GetToss();
    ASSERT_NE(toss, nullptr);
    auto propertyCallback = [](float position) {};
    toss->property_ = AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0, std::move(propertyCallback));
    toss->end_ = OFFSET_Y;
    touchListener(touchEventInfo);
    EXPECT_TRUE(columnPattern_->touchBreak_);
    EXPECT_TRUE(columnPattern_->animationBreak_);
    EXPECT_TRUE(columnPattern_->clickBreak_);
    EXPECT_FLOAT_EQ(columnPattern_->yLast_, OFFSET_Y);

    /**
     * @tc.steps: step5. Set TouchType UP and call callback.
     * @tc.expected: touchBreak_ is set false.
     */
    localLocationInfo.SetTouchType(TouchType::UP);
    touches.clear();
    touches.emplace_back(localLocationInfo);
    touchEventInfo.touches_ = touches;
    columnPattern_->animationBreak_ = false;
    touchListener(touchEventInfo);
    EXPECT_FALSE(columnPattern_->touchBreak_);

    /**
     * @tc.steps: step5. Set animationBreak_ true and call callback.
     * @tc.expected: yOffset_ is set 0.
     */
    columnPattern_->animationBreak_ = true;
    touchListener(touchEventInfo);
    EXPECT_FLOAT_EQ(columnPattern_->yOffset_, 0.0f);
}

/**
 * @tc.name: DatePickerColumnPatternTest009
 * @tc.desc: Test DatePickerColumnPattern FlushAnimationTextProperties.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestFour, DatePickerColumnPatternTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Add random dateTextProperties to animationProperties_.
     */
    CreateDatePickerColumnNode();
    ASSERT_NE(columnPattern_, nullptr);
    DateTextProperties dateTextProperties;
    dateTextProperties.upFontSize = Dimension(UP_FONT_SIZE);
    dateTextProperties.fontSize = Dimension(TEST_FONT_SIZE);
    dateTextProperties.downFontSize = Dimension(DOWN_FONT_SIZE);
    dateTextProperties.upColor = Color::RED;
    dateTextProperties.currentColor = Color::BLUE;
    dateTextProperties.downColor = Color::GREEN;
    columnPattern_->animationProperties_.clear();
    columnPattern_->animationProperties_.emplace_back(dateTextProperties);

    /**
     * @tc.steps: step2. Call AddAnimationTextProperties function.
     * @tc.expected: animationProperties_'s size is added to 2.
     */
    auto textLayoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    textLayoutProperty->UpdateFontSize(Dimension(TEST_FONT_SIZE));
    columnPattern_->optionProperties_.clear();
    columnPattern_->AddAnimationTextProperties(0, textLayoutProperty);
    EXPECT_EQ(columnPattern_->animationProperties_.size(), 2);

    /**
     * @tc.steps: step3. Call FlushAnimationTextProperties function.
     * @tc.expected: animationProperties_'s properties is changed.
     */
    columnPattern_->FlushAnimationTextProperties(false);
    EXPECT_EQ(columnPattern_->animationProperties_[1].upFontSize, Dimension(UP_FONT_SIZE));
    EXPECT_EQ(columnPattern_->animationProperties_[1].fontSize, Dimension(TEST_FONT_SIZE));
    EXPECT_EQ(columnPattern_->animationProperties_[1].downFontSize, Dimension(DOWN_FONT_SIZE));
    EXPECT_EQ(columnPattern_->animationProperties_[1].upColor, Color::RED);
    EXPECT_EQ(columnPattern_->animationProperties_[1].currentColor, Color::BLUE);
    EXPECT_EQ(columnPattern_->animationProperties_[1].downColor, Color::GREEN);
    EXPECT_EQ(columnPattern_->animationProperties_[0].upFontSize, Dimension());
    EXPECT_EQ(columnPattern_->animationProperties_[0].fontSize, Dimension(UP_FONT_SIZE));
    EXPECT_EQ(columnPattern_->animationProperties_[0].downFontSize, Dimension(TEST_FONT_SIZE));
    EXPECT_EQ(columnPattern_->animationProperties_[0].upColor, Color());
    auto colorEvaluator = AceType::MakeRefPtr<LinearEvaluator<Color>>();
    EXPECT_EQ(
        columnPattern_->animationProperties_[0].currentColor, colorEvaluator->Evaluate(Color(), Color::BLUE, 0.5));
    EXPECT_EQ(columnPattern_->animationProperties_[0].downColor, Color::BLUE);
}

/**
 * @tc.name: DatePickerColumnPatternTest010
 * @tc.desc: Test DatePickerColumnPattern TextPropertiesLinearAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestFour, DatePickerColumnPatternTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Add random dateTextProperties to animationProperties_.
     */
    CreateDatePickerColumnNode();
    ASSERT_NE(columnPattern_, nullptr);
    DateTextProperties dateTextProperties;
    dateTextProperties.upFontSize = Dimension(UP_FONT_SIZE);
    dateTextProperties.fontSize = Dimension(TEST_FONT_SIZE);
    dateTextProperties.downFontSize = Dimension(DOWN_FONT_SIZE);
    dateTextProperties.upFontWeight = FontWeight::BOLD;
    dateTextProperties.fontWeight = FontWeight::BOLDER;
    dateTextProperties.downFontWeight = FontWeight::LIGHTER;
    dateTextProperties.upColor = Color::RED;
    dateTextProperties.currentColor = Color::BLUE;
    dateTextProperties.downColor = Color::GREEN;
    columnPattern_->animationProperties_.clear();
    columnPattern_->animationProperties_.emplace_back(dateTextProperties);
    columnPattern_->animationProperties_.emplace_back(dateTextProperties);

    /**
     * @tc.steps: step2. Call TextPropertiesLinearAnimation while index is equal to midIndex.
     * @tc.expected: textLayoutProperty's properties is changed.
     */
    auto textLayoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    columnPattern_->TextPropertiesLinearAnimation(textLayoutProperty, 2, 0, false, 0.0f);
    columnPattern_->TextPropertiesLinearAnimation(textLayoutProperty, 1, 4, true, 0.0f);
    columnPattern_->TextPropertiesLinearAnimation(textLayoutProperty, 1, 4, true, 1.0f);
    columnPattern_->TextPropertiesLinearAnimation(textLayoutProperty, 1, 2, true, 0.0f);
    columnPattern_->TextPropertiesLinearAnimation(textLayoutProperty, 1, 2, true, 1.0f);
    EXPECT_EQ(textLayoutProperty->GetFontWeight().value(), FontWeight::BOLD);
    Dimension updateSize = columnPattern_->LinearFontSize(
        Dimension(TEST_FONT_SIZE), Dimension(UP_FONT_SIZE), columnPattern_->distancePercent_);
    EXPECT_EQ(textLayoutProperty->GetFontSize().value(), updateSize);
    Color updateColor = AceType::MakeRefPtr<LinearEvaluator<Color>>()->Evaluate(
        Color::BLUE, Color::RED, static_cast<float>(columnPattern_->distancePercent_));
    EXPECT_EQ(textLayoutProperty->GetTextColor(), updateColor);

    /**
     * @tc.steps: step3. Call TextPropertiesLinearAnimation while index is one bigger than midIndex.
     * @tc.expected: textLayoutProperty's properties is changed.
     */
    columnPattern_->TextPropertiesLinearAnimation(textLayoutProperty, 1, 0, true, 0.0f);
    columnPattern_->TextPropertiesLinearAnimation(textLayoutProperty, 1, 0, true, 1.0f);
    EXPECT_EQ(textLayoutProperty->GetFontWeight().value(), FontWeight::BOLD);
    updateSize = columnPattern_->LinearFontSize(
        Dimension(TEST_FONT_SIZE), Dimension(UP_FONT_SIZE), columnPattern_->distancePercent_);
    EXPECT_EQ(textLayoutProperty->GetFontSize().value(), updateSize);
    updateColor = AceType::MakeRefPtr<LinearEvaluator<Color>>()->Evaluate(
        Color::BLUE, Color::RED, static_cast<float>(columnPattern_->distancePercent_));
    EXPECT_EQ(textLayoutProperty->GetTextColor(), updateColor);
}

/**
 * @tc.name: DatePickerColumnPatternTest011
 * @tc.desc: Test DatePickerColumnPattern infrequent branches.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestFour, DatePickerColumnPatternTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create columnNode and columnPattern.
     */
    CreateDatePickerColumnNode();
    ASSERT_NE(columnNode_, nullptr);
    ASSERT_NE(columnPattern_, nullptr);
    columnPattern_->UpdateTextPropertiesLinear(true, 2.0f);
    columnPattern_->showCount_ = 1;
    columnPattern_->UpdateTextPropertiesLinear(true, 0.5f);

    /**
     * @tc.steps: step2. Call HandleDragMove while inputEventType is AXIS and sourceTool is MOUSE.
     * @tc.expected: animationBreak_ is set false.
     */
    auto eventHub = columnNode_->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto gestureHub = eventHub->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    columnPattern_->InitPanEvent(gestureHub);
    auto actionEndTask = columnPattern_->panEvent_->actionEnd_;
    GestureEvent info;
    info.SetInputEventType(InputEventType::AXIS);
    info.SetSourceTool(SourceTool::MOUSE);
    actionEndTask(info);
    columnPattern_->HandleDragMove(info);
    EXPECT_FALSE(columnPattern_->animationBreak_);

    /**
     * @tc.steps: step3. Call HandleDragMove while inputEventType is AXIS and sourceTool is FINGER.
     * @tc.expected: yLast_ is changed.
     */
    info.SetSourceTool(SourceTool::FINGER);
    Point globalPoint(1.0f, 1.0f);
    info.SetGlobalPoint(globalPoint);
    info.SetOffsetX(1.0f);
    info.SetOffsetY(1.0f);
    columnPattern_->yLast_ = 0.0f;
    columnPattern_->pressed_ = true;
    columnPattern_->HandleDragMove(info);
    EXPECT_FLOAT_EQ(columnPattern_->yLast_, 2.0f);
}

/**
 * @tc.name: DatePickerColumnPatternTest014
 * @tc.desc: Test DatePickerColumnPattern UpdateFinishToss.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestFour, DatePickerColumnPatternTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create columnNode and columnPattern.
     */
    CreateDatePickerColumnNode();
    ASSERT_NE(columnPattern_, nullptr);
    auto options = columnPattern_->GetOptions();
    auto pickerDates = options[columnNode_];
    pickerDates.clear();
    pickerDates.emplace_back(PickerDateF::CreateYear(START_YEAR));
    pickerDates.emplace_back(PickerDateF::CreateYear(START_YEAR));
    pickerDates.emplace_back(PickerDateF::CreateYear(START_YEAR));
    options[columnNode_] = pickerDates;
    columnPattern_->options_ = options;

    /**
     * @tc.steps: step2. Call UpdateFinishToss while scroll can move.
     * @tc.expected: ScrollDelta_ is added.
     */
    columnPattern_->showCount_ = pickerDates.size() * 2;
    columnPattern_->SetCurrentIndex(5);
    columnPattern_->UpdateFinishToss(OFFSET_Y);
    EXPECT_FALSE(columnPattern_->CanMove(true));
    columnPattern_->SetCurrentIndex(1);
    EXPECT_TRUE(columnPattern_->CanMove(true));
    DatePickerOptionProperty datePickerOptionProperty;
    datePickerOptionProperty.prevDistance = 0.0f;
    datePickerOptionProperty.nextDistance = 1.0f;
    columnPattern_->optionProperties_.clear();
    columnPattern_->optionProperties_.emplace_back(datePickerOptionProperty);
    columnPattern_->optionProperties_.emplace_back(datePickerOptionProperty);
    columnPattern_->optionProperties_.emplace_back(datePickerOptionProperty);
    columnPattern_->optionProperties_.emplace_back(datePickerOptionProperty);
    columnPattern_->yLast_ = 0.0f;
    columnPattern_->UpdateFinishToss(OFFSET_Y);
    EXPECT_EQ(columnPattern_->scrollDelta_, 1.0f);
}

/**
 * @tc.name: DatePickerColumnPatternTest015
 * @tc.desc: Test DatePickerColumnPattern CalcScrollIndex.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestFour, DatePickerColumnPatternTest015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create columnNode and columnPattern.
     */
    CreateDatePickerColumnNode();
    ASSERT_NE(columnPattern_, nullptr);

    /**
     * @tc.steps: step2. Call CalcScrollIndex with different parameters.
     * @tc.expected: Function return correct index.
     */
    EXPECT_EQ(
        columnPattern_->CalcScrollIndex(MIDDLE_OF_COUNTS, BIG_SHOWCOUNT, false, SMALL_SHOWCOUNT), MIDDLE_OF_COUNTS - 1);
    EXPECT_EQ(columnPattern_->CalcScrollIndex(MIDDLE_OF_COUNTS, BIG_SHOWCOUNT, false, -SMALL_SHOWCOUNT),
        BIG_SHOWCOUNT - SMALL_SHOWCOUNT);
    EXPECT_EQ(columnPattern_->CalcScrollIndex(MIDDLE_OF_COUNTS, BIG_SHOWCOUNT, false, 0), BIG_SHOWCOUNT);
    EXPECT_EQ(columnPattern_->CalcScrollIndex(MIDDLE_OF_COUNTS, BIG_SHOWCOUNT, true, SMALL_SHOWCOUNT), 0);
    EXPECT_EQ(columnPattern_->CalcScrollIndex(0, BIG_SHOWCOUNT, true, SMALL_SHOWCOUNT), BIG_SHOWCOUNT);
}

/**
 * @tc.name: DatePickerColumnPatternTest016
 * @tc.desc: Test DatePickerColumnPattern GetShiftDistanceForLandscape.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestFour, DatePickerColumnPatternTest016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create columnPattern and set pickerTheme.
     */
    CreateDatePickerColumnNode();
    ASSERT_NE(columnPattern_, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto pickerTheme = AceType::MakeRefPtr<PickerTheme>();
    ASSERT_NE(pickerTheme, nullptr);
    pickerTheme->showOptionCount_ = -2;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(pickerTheme));

    /**
     * @tc.steps: step2. Call GetShiftDistanceForLandscape in different situation.
     * @tc.expected: Function return correct distance.
     */
    EXPECT_FLOAT_EQ(columnPattern_->GetShiftDistanceForLandscape(0, DatePickerScrollDirection::DOWN), 0.0f);
    pickerTheme->showOptionCount_ = 1;
    DatePickerOptionProperty datePickerOptionProperty;
    datePickerOptionProperty.height = DOWN_FONT_SIZE;
    datePickerOptionProperty.fontheight = TEST_FONT_SIZE;
    columnPattern_->optionProperties_.clear();
    columnPattern_->optionProperties_.emplace_back(datePickerOptionProperty);
    columnPattern_->optionProperties_.emplace_back(datePickerOptionProperty);
    columnPattern_->optionProperties_.emplace_back(datePickerOptionProperty);
    EXPECT_FLOAT_EQ(columnPattern_->GetShiftDistanceForLandscape(0, DatePickerScrollDirection::UP), -DOWN_FONT_SIZE);
    EXPECT_FLOAT_EQ(columnPattern_->GetShiftDistanceForLandscape(0, DatePickerScrollDirection::DOWN), 25.0f);
    EXPECT_FLOAT_EQ(columnPattern_->GetShiftDistanceForLandscape(1, DatePickerScrollDirection::DOWN), 25.0f);
    EXPECT_FLOAT_EQ(columnPattern_->GetShiftDistanceForLandscape(2, DatePickerScrollDirection::DOWN), DOWN_FONT_SIZE);
    EXPECT_FLOAT_EQ(columnPattern_->GetShiftDistanceForLandscape(2, DatePickerScrollDirection::UP), -25.0f);
    EXPECT_FLOAT_EQ(columnPattern_->GetShiftDistanceForLandscape(3, DatePickerScrollDirection::UP), 0.0f);
}

/**
 * @tc.name: DatePickerColumnPatternTest017
 * @tc.desc: Test DatePickerColumnPattern UpdateColumnChildPosition.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestFour, DatePickerColumnPatternTest017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create columnPattern.
     */
    CreateDatePickerColumnNode();
    ASSERT_NE(columnPattern_, nullptr);
    auto options = columnPattern_->GetOptions();
    auto pickerDates = options[columnNode_];
    pickerDates.clear();
    pickerDates.emplace_back(PickerDateF::CreateYear(START_YEAR));
    pickerDates.emplace_back(PickerDateF::CreateYear(START_YEAR));
    pickerDates.emplace_back(PickerDateF::CreateYear(START_YEAR));
    options[columnNode_] = pickerDates;
    columnPattern_->options_ = options;

    /**
     * @tc.steps: step2. Call UpdateColumnChildPosition in different situation.
     * @tc.expected: offsetCurSet_ and yOffset_ is set.
     */
    columnPattern_->SetCurrentIndex(5);
    columnPattern_->UpdateColumnChildPosition(OFFSET_Y);
    DatePickerOptionProperty datePickerOptionProperty;
    datePickerOptionProperty.prevDistance = TEST_FONT_SIZE;
    datePickerOptionProperty.nextDistance = DOWN_FONT_SIZE;
    columnPattern_->optionProperties_.clear();
    columnPattern_->optionProperties_.emplace_back(datePickerOptionProperty);
    columnPattern_->showCount_ = 0;
    columnPattern_->yLast_ = 0.0f;
    columnPattern_->yOffset_ = 0.0f;
    columnPattern_->UpdateColumnChildPosition(OFFSET_Y);
    EXPECT_FLOAT_EQ(columnPattern_->offsetCurSet_, OFFSET_Y);
    EXPECT_FLOAT_EQ(columnPattern_->yOffset_, OFFSET_Y);
}

/**
 * @tc.name: DatePickerColumnPatternTest020
 * @tc.desc: Test DatePickerColumnPattern AddHotZoneRectToText.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestFour, DatePickerColumnPatternTest020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create columnPattern and Set text node height.
     */
    CreateDatePickerColumnNode();
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
 * @tc.name: DataPickerDialogViewUpdateButtonStyles001
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestFour, DataPickerDialogViewUpdateButtonStyles001, TestSize.Level1)
{
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontWeight = FontWeight::W400;
    buttonInfos.push_back(info1);

    size_t sizet = 0;

    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    CHECK_NULL_VOID(buttonNode);
    auto layoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    
    auto renderContext = buttonNode->GetRenderContext();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto buttonTheme = AceType::MakeRefPtr<ButtonTheme>();
    ASSERT_NE(buttonTheme, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(buttonTheme));
    DatePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval = layoutProperty->GetFontWeightValue();
    EXPECT_EQ(testval, FontWeight::W400);
}

/**
 * @tc.name: DatePickerDialogViewUpdateButtonDefaultFocus001
 * @tc.desc: Test UpdateButtonDefaultFocus.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestFour, DatePickerDialogViewUpdateButtonDefaultFocus001, TestSize.Level1)
{
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.isPrimary = true;
    info1.isAcceptButton = true;
    buttonInfos.push_back(info1);

    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(buttonNode, nullptr);

    DatePickerDialogView::UpdateButtonDefaultFocus(buttonInfos, buttonNode, true);
    auto focusHub = buttonNode->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    EXPECT_EQ(focusHub->IsDefaultFocus(), true);
}

/**
 * @tc.name: DatePickerDialogViewUpdateButtonDefaultFocus002
 * @tc.desc: Test UpdateButtonDefaultFocus.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestFour, DatePickerDialogViewUpdateButtonDefaultFocus002, TestSize.Level1)
{
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.isPrimary = true;
    buttonInfos.push_back(info1);

    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(buttonNode, nullptr);

    DatePickerDialogView::UpdateButtonDefaultFocus(buttonInfos, buttonNode, false);
    auto focusHub = buttonNode->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    EXPECT_EQ(focusHub->IsDefaultFocus(), true);
}

/**
 * @tc.name: DatePickerDialogViewUpdateButtonDefaultFocus003
 * @tc.desc: Test UpdateButtonDefaultFocus.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestFour, DatePickerDialogViewUpdateButtonDefaultFocus003, TestSize.Level1)
{
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.isPrimary = true;
    info1.isAcceptButton = true;
    buttonInfos.push_back(info1);

    ButtonInfo info2;
    buttonInfos.push_back(info2);

    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(buttonNode, nullptr);

    DatePickerDialogView::UpdateButtonDefaultFocus(buttonInfos, buttonNode, true);
    auto focusHub = buttonNode->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    EXPECT_EQ(focusHub->IsDefaultFocus(), true);
}

/**
 * @tc.name: DatePickerDialogViewUpdateButtonDefaultFocus004
 * @tc.desc: Test UpdateButtonDefaultFocus.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestFour, DatePickerDialogViewUpdateButtonDefaultFocus004, TestSize.Level1)
{
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.isPrimary = true;
    info1.isAcceptButton = true;
    buttonInfos.push_back(info1);

    ButtonInfo info2;
    buttonInfos.push_back(info2);

    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_COMPONENT_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(buttonNode, nullptr);

    DatePickerDialogView::UpdateButtonDefaultFocus(buttonInfos, buttonNode, true);
    auto focusHub = buttonNode->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    EXPECT_EQ(focusHub->IsDefaultFocus(), true);
}

/**
 * @tc.name: DatePickerDialogViewUpdateButtonDefaultFocus005
 * @tc.desc: Test UpdateButtonDefaultFocus.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestFour, DatePickerDialogViewUpdateButtonDefaultFocus005, TestSize.Level1)
{
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.isPrimary = true;
    info1.isAcceptButton = true;
    buttonInfos.push_back(info1);

    ButtonInfo info2;
    buttonInfos.push_back(info2);

    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_COMPONENT_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(buttonNode, nullptr);
    /**
     * @tc.steps: steps1. setDefaultFocus is true and call UpdateButtonDefaultFocus;
     * @tc.expected: The texts of IsDefaultFocus is equal to true;
     */
    DatePickerDialogView::UpdateButtonDefaultFocus(buttonInfos, buttonNode, true);
    auto focusHub = buttonNode->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    EXPECT_EQ(focusHub->IsDefaultFocus(), true);
}


/**
 * @tc.name: DatePickerPatternTest001
 * @tc.desc: Test OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestFour, DatePickerPatternTest111, TestSize.Level1)
{
    const std::string language = "en";
    const std::string countryOrRegion = "US";
    const std::string script = "Latn";
    const std::string keywordsAndValues = "";
    auto pickerStack = DatePickerDialogView::CreateStackNode();
    ASSERT_NE(pickerStack, nullptr);
    auto datePickerNode = FrameNode::GetOrCreateFrameNode(
        V2::DATE_PICKER_ETS_TAG, 1, []() { return AceType::MakeRefPtr<DatePickerPattern>(); });
    datePickerNode->MountToParent(pickerStack);
    auto buttonConfirmNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NG::ButtonPattern>(); });
    auto textConfirmNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto textLayoutProperty = textConfirmNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    textLayoutProperty->UpdateContent(Localization::GetInstance()->GetEntryLetters("common.ok"));
    textConfirmNode->MountToParent(buttonConfirmNode);
    auto datePickerPattern = datePickerNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    datePickerPattern->OnModifyDone();

    datePickerPattern->isFiredDateChange_ = true;
    datePickerPattern->OnModifyDone();

    datePickerPattern->isFiredDateChange_ = false;
    datePickerPattern->showMonthDays_ = true;
    datePickerPattern->OnModifyDone();
    auto children = buttonConfirmNode->GetChildren();
    EXPECT_EQ(children.size(), 1);
}

/**
 * @tc.name: DatePickerDialogViewConvertFontScaleValue001
 * @tc.desc: Test DatePickerDialogView ConvertFontScaleValue.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestFour, DatePickerDialogViewConvertFontScaleValue001, TestSize.Level1)
{
    Dimension fontSizeValue = 50.0_vp;
    Dimension fontSizeLimit = 40.0_vp;

    auto result = DatePickerDialogView::ConvertFontScaleValue(fontSizeValue, fontSizeLimit, true);
    EXPECT_EQ(fontSizeLimit.Value(), result.Value());
}

/**
 * @tc.name: DatePickerDialogViewConvertFontScaleValue002
 * @tc.desc: Test DatePickerDialogView ConvertFontScaleValue.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestFour, DatePickerDialogViewConvertFontScaleValue002, TestSize.Level1)
{
    Dimension fontSizeValue = 20.0_vp;
    Dimension fontSizeLimit = 40.0_vp;

    auto result = DatePickerDialogView::ConvertFontScaleValue(fontSizeValue, fontSizeLimit, true);
    EXPECT_EQ(fontSizeValue.Value(), result.Value());
}

/**
 * @tc.name: DatePickerDialogViewConvertFontSizeLimitTest001
 * @tc.desc: Test DatePickerDialogView ConvertFontSizeLimit.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestFour, DatePickerDialogViewConvertFontSizeLimitTest001, TestSize.Level1)
{
    Dimension fontSizeValue(20.0);
    Dimension fontSizeLimit(30.0);
    bool isUserSetFont = false;
    Dimension result = DatePickerDialogView::ConvertFontSizeLimit(fontSizeValue, fontSizeLimit, isUserSetFont);
    EXPECT_EQ(result, fontSizeValue);
}

/**
 * @tc.name: DatePickerDialogViewConvertFontSizeLimitTest002
 * @tc.desc: Test DatePickerDialogView ConvertFontSizeLimit.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestFour, DatePickerDialogViewConvertFontSizeLimitTest002, TestSize.Level1)
{
    Dimension fontSizeValue(20.0);
    Dimension fontSizeLimit(30.0);
    bool isUserSetFont = true;
    Dimension result = DatePickerDialogView::ConvertFontSizeLimit(fontSizeValue, fontSizeLimit, isUserSetFont);
    EXPECT_EQ(result, fontSizeValue);
}

/**
 * @tc.name: DatePickerDialogViewConvertFontSizeLimitTest003
 * @tc.desc: Test DatePickerDialogView ConvertFontSizeLimit.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestFour, DatePickerDialogViewConvertFontSizeLimitTest003, TestSize.Level1)
{
    Dimension fontSizeValue(40.0);
    Dimension fontSizeLimit(30.0);
    bool isUserSetFont = true;
    double fontScale = 2.0f;
    MockPipelineContext::GetCurrent()->SetFontScale(fontScale);
    Dimension result = DatePickerDialogView::ConvertFontSizeLimit(fontSizeValue, fontSizeLimit, isUserSetFont);
    Dimension expected = fontSizeLimit / fontScale;
    EXPECT_EQ(result, expected);
}

/**
 * @tc.name: DatePickerDialogViewConvertFontSizeLimitTest004
 * @tc.desc: Test DatePickerDialogView ConvertFontSizeLimit.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestFour, DatePickerDialogViewConvertFontSizeLimitTest004, TestSize.Level1)
{
    Dimension fontSizeValue(10.0);
    Dimension fontSizeLimit(30.0);
    bool isUserSetFont = true;
    double fontScale = 2.0f;
    MockPipelineContext::GetCurrent()->SetFontScale(fontScale);
    Dimension result = DatePickerDialogView::ConvertFontSizeLimit(fontSizeValue, fontSizeLimit, isUserSetFont);
    EXPECT_EQ(result, fontSizeValue);
}

/**
 * @tc.name: DatePickerDialogViewGetUserSettingLimitTest001
 * @tc.desc: Test DatePickerDialogView AdjustFontSizeScale.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestFour, DatePickerDialogViewGetUserSettingLimitTest001, TestSize.Level1)
{
    double fontScale = 1.0f;
    Dimension fontSizeValue(10.0);
    Dimension result = DatePickerDialogView::AdjustFontSizeScale(fontSizeValue, fontScale);
    EXPECT_EQ(result, fontSizeValue * fontScale);
}

/**
 * @tc.name: DatePickerDialogViewGetUserSettingLimitTest002
 * @tc.desc: Test DatePickerDialogView AdjustFontSizeScale.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestFour, DatePickerDialogViewGetUserSettingLimitTest002, TestSize.Level1)
{
    double fontScale = 1.75f;
    Dimension fontSizeValue(10.0);
    Dimension result = DatePickerDialogView::AdjustFontSizeScale(fontSizeValue, fontScale);
    EXPECT_EQ(result, fontSizeValue * fontScale);
}

/**
 * @tc.name: DatePickerDialogViewGetUserSettingLimitTest003
 * @tc.desc: Test DatePickerDialogView AdjustFontSizeScale.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestFour, DatePickerDialogViewGetUserSettingLimitTest003, TestSize.Level1)
{
    double fontScale = 2.0f;
    Dimension fontSizeValue(10.0);
    Dimension result = DatePickerDialogView::AdjustFontSizeScale(fontSizeValue, fontScale);
    EXPECT_EQ(result, fontSizeValue * fontScale);
}

/**
 * @tc.name: DatePickerDialogViewGetUserSettingLimitTest004
 * @tc.desc: Test DatePickerDialogView AdjustFontSizeScale.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestFour, DatePickerDialogViewGetUserSettingLimitTest004, TestSize.Level1)
{
    double fontScale = 3.2f;
    Dimension fontSizeValue(10.0);
    Dimension result = DatePickerDialogView::AdjustFontSizeScale(fontSizeValue, fontScale);
    EXPECT_NE(result, fontSizeValue * fontScale);
}

/**
 * @tc.name: DatePickerPatternTest019
 * @tc.desc: Test OnLanguageConfigurationUpdate
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestFour, DatePickerPatternTest019, TestSize.Level1)
{
    const std::string language = "en";
    const std::string countryOrRegion = "US";
    const std::string script = "Latn";
    const std::string keywordsAndValues = "";
    auto pickerStack = DatePickerDialogView::CreateStackNode();
    ASSERT_NE(pickerStack, nullptr);
    auto datePickerNode = FrameNode::GetOrCreateFrameNode(
        V2::DATE_PICKER_ETS_TAG, 1, []() { return AceType::MakeRefPtr<DatePickerPattern>(); });
    datePickerNode->MountToParent(pickerStack);
    auto buttonConfirmNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NG::ButtonPattern>(); });
    auto textConfirmNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto textLayoutProperty = textConfirmNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    textLayoutProperty->UpdateContent(Localization::GetInstance()->GetEntryLetters("common.ok"));
    textConfirmNode->MountToParent(buttonConfirmNode);
    auto datePickerPattern = datePickerNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    datePickerPattern->SetConfirmNode(buttonConfirmNode);

    auto buttonCancelNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(buttonCancelNode, nullptr);
    auto textCancelNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textCancelNode, nullptr);
    auto textCancelLayoutProperty = textCancelNode->GetLayoutProperty<TextLayoutProperty>();
    textCancelLayoutProperty->UpdateContent(Localization::GetInstance()->GetEntryLetters("common.cancel"));
    ASSERT_NE(textCancelLayoutProperty, nullptr);
    textCancelNode->MountToParent(buttonCancelNode);
    datePickerPattern->SetCancelNode(buttonCancelNode);
    datePickerPattern->OnLanguageConfigurationUpdate();
    AceApplicationInfo::GetInstance().SetLocale(language, countryOrRegion, script, keywordsAndValues);
    std::string nodeInfo = "";
    auto cancel = Localization::GetInstance()->GetEntryLetters("common.cancel");
    EXPECT_EQ(cancel, nodeInfo);
}

} // namespace OHOS::Ace::NG