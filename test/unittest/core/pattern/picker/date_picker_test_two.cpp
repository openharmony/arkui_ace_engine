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


#include "gtest/gtest.h"
#include "test/unittest/core/pattern/test_ng.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_default.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/rosen/mock_canvas.h"

#include "core/components/theme/icon_theme.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_view.h"
#include "core/components_ng/pattern/picker/date_time_animation_controller.h"
#include "core/components_ng/pattern/picker/datepicker_dialog_view.h"
#include "core/components_ng/pattern/picker/datepicker_model_ng.h"
#include "core/components_ng/pattern/picker/datepicker_pattern.h"
#include "core/components_ng/property/measure_property.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {

namespace {
constexpr int32_t START_YEAR = 1980;
const InspectorFilter filter;
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

class DatePickerTestTwoNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void CreateDatePickerColumnNode();

    RefPtr<FrameNode> columnNode_;
    RefPtr<DatePickerColumnPattern> columnPattern_;
    std::unique_ptr<DatePickerModelNG> datePickerNg_ = nullptr;
    std::unique_ptr<DatePickerDialogModelNG> datePickerDialogNg_ = nullptr;
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

void DatePickerTestTwoNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void DatePickerTestTwoNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void DatePickerTestTwoNg::SetUp()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        return GetTheme(type);
    });
    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([](ThemeType type, int32_t themeScopeId) -> RefPtr<Theme> { return GetTheme(type); });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    if (datePickerNg_ == nullptr) {
        datePickerNg_.reset(new DatePickerModelNG());
    }
    if (datePickerDialogNg_ == nullptr) {
        datePickerDialogNg_.reset(new DatePickerDialogModelNG());
    }
}

void DatePickerTestTwoNg::TearDown()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    ViewStackProcessor::GetInstance()->ClearStack();
    if (datePickerNg_) {
        auto item = datePickerNg_.release();
        datePickerNg_.reset();
        delete item;
    }
    if (datePickerDialogNg_) {
        auto item = datePickerDialogNg_.release();
        datePickerDialogNg_.reset();
        delete item;
    }
}

void DatePickerTestTwoNg::CreateDatePickerColumnNode()
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

/**
 * @tc.name: SetDatePickerDialogShow001
 * @tc.desc: Test SetDatePickerDialogShow.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestTwoNg, SetDatePickerDialogShow001, TestSize.Level1)
{
    std::function<void()> cancelEvent;
    std::function<void(const std::string&)> acceptEvent;
    std::function<void(const std::string&)> changeEvent;
    std::function<void(const std::string&)> dateChangeEvent;
    std::function<void(const std::string&)> dateAcceptEvent;
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    cancelEvent = []{ std::cout << "cancelEvent successed."<< std::endl; };
    acceptEvent = [](const std::string& dateString) {
        std::cout << "acceptEvent dateString is " << dateString << std::endl; };
    changeEvent = [](const std::string& dateString) {
        std::cout << "changeEvent dateString is " << dateString << std::endl; };
    dateChangeEvent = [](const std::string& dateString) {
        std::cout << "dateChangeEvent dateString is " << dateString << std::endl; };
    dateAcceptEvent = [](const std::string& dateString) {
        std::cout << "dateAcceptEvent dateString is " << dateString << std::endl; };
    PickerDialogInfo pickerDialog;
    std::vector<ButtonInfo> buttonInfos;
    NG::DatePickerSettingData settingData;
    DatePickerType pickerType = DatePickerType::DATE;
    PickerDialogEvent pickerDialogEvent { nullptr, nullptr, nullptr, nullptr };
    datePickerDialogNg_->SetDatePickerDialogShow(pickerDialog, settingData, std::move(cancelEvent),
        std::move(acceptEvent), std::move(changeEvent), std::move(dateAcceptEvent), std::move(dateChangeEvent),
        pickerType, pickerDialogEvent, buttonInfos);
    EXPECT_FALSE(pickerDialog.alignment.has_value());
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto tmpVersion = pipeline->minPlatformVersion_;
    pipeline->minPlatformVersion_ = 0;
    auto container = MockContainer::Current();
    container->pipelineContext_ = MockPipelineContext::GetCurrent();
    container->pipelineContext_->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    datePickerDialogNg_->SetDatePickerDialogShow(pickerDialog, settingData, std::move(cancelEvent),
        std::move(acceptEvent), std::move(changeEvent), std::move(dateAcceptEvent), std::move(dateChangeEvent),
        pickerType, pickerDialogEvent, buttonInfos);
    pipeline->minPlatformVersion_ = tmpVersion;
    EXPECT_FALSE(pickerDialog.alignment.has_value());
}

/**
 * @tc.name: SetDatePickerDialogShow002
 * @tc.desc: Test SetDatePickerDialogShow.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestTwoNg, SetDatePickerDialogShow002, TestSize.Level1)
{
    std::function<void()> cancelEvent;
    std::function<void(const std::string&)> acceptEvent;
    std::function<void(const std::string&)> changeEvent;
    std::function<void(const std::string&)> dateChangeEvent;
    std::function<void(const std::string&)> dateAcceptEvent;
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    cancelEvent = []{ std::cout << "cancelEvent successed."<< std::endl; };
    acceptEvent = [](const std::string& dateString) {
        std::cout << "acceptEvent dateString is " << dateString << std::endl; };
    changeEvent = [](const std::string& dateString) {
        std::cout << "changeEvent dateString is " << dateString << std::endl; };
    dateChangeEvent = [](const std::string& dateString) {
        std::cout << "dateChangeEvent dateString is " << dateString << std::endl; };
    dateAcceptEvent = [](const std::string& dateString) {
        std::cout << "dateAcceptEvent dateString is " << dateString << std::endl; };
    DatePickerType pickerType = DatePickerType::DATE;
    PickerDialogInfo pickerDialog;
    std::vector<ButtonInfo> buttonInfos;
    NG::DatePickerSettingData settingData;
    PickerDialogEvent pickerDialogEvent { nullptr, nullptr, nullptr, nullptr };
    Shadow textShadow;
    textShadow.SetOffsetX(5.0);
    textShadow.SetOffsetY(5.0);
    textShadow.SetBlurRadius(0.0);
    textShadow.SetColor(Color::BLUE);
    pickerDialog.isEndDate = true;
    pickerDialog.isStartDate = true;
    pickerDialog.shadow = textShadow;
    pickerDialog.isSelectedDate = true;
    pickerDialog.backgroundBlurStyle = 2;
    pickerDialog.alignment = DialogAlignment::DEFAULT;
    pickerDialog.offset = DimensionOffset(Offset(0, -1.0f));
    pickerDialog.backgroundColor = Color::FromString("#FFFF0000");
    auto container = MockContainer::Current();
    container->pipelineContext_ = MockPipelineContext::GetCurrent();
    container->pipelineContext_->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    datePickerDialogNg_->SetDatePickerDialogShow(pickerDialog, settingData, std::move(cancelEvent),
        std::move(acceptEvent), std::move(changeEvent), std::move(dateAcceptEvent), std::move(dateChangeEvent),
        pickerType, pickerDialogEvent, buttonInfos);
    auto it = settingData.datePickerProperty.find("end");
    EXPECT_EQ(it != settingData.datePickerProperty.end(), true);
}

/**
 * @tc.name: ConvertFontScaleValue001
 * @tc.desc: Test SetDatePickerDialogShow.  3
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestTwoNg, ConvertFontScaleValue001, TestSize.Level1)
{
    Dimension tstDimension;
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    float tstScale = pipeline->fontScale_;
    pipeline->fontScale_ = 0;
    datePickerNg_->ConvertFontScaleValue(tstDimension);
    EXPECT_EQ(pipeline->GetFontScale(), 0);
    tstDimension.SetUnit(DimensionUnit::VP);
    datePickerNg_->ConvertFontScaleValue(tstDimension);
    EXPECT_EQ(tstDimension.Unit() == DimensionUnit::VP, true);
    pipeline->fontScale_ = 0.6f;
    datePickerNg_->ConvertFontScaleValue(tstDimension);
    pipeline->fontScale_ = tstScale;
    EXPECT_TRUE(GreatOrEqualCustomPrecision(pipeline->fontScale_, 1.0f));
}

/**
 * @tc.name: CreateFrameNode001
 * @tc.desc: Test DatePickerModel CreateFrameNode.  5
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestTwoNg, CreateFrameNode001, TestSize.Level1)
{
    auto ret = datePickerNg_->CreateFrameNode(1);
    ASSERT_NE(ret, nullptr);
}

/**
 * @tc.name: CreateDatePicker001
 * @tc.desc: Test DatePickerModel CreateDatePicker.  10
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestTwoNg, CreateDatePicker001, TestSize.Level1)
{
    auto tstTheme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(tstTheme, nullptr);
    datePickerNg_->CreateDatePicker(tstTheme);
    auto ret = ViewStackProcessor::GetInstance()->GetMainElementNode();
    ASSERT_NE(ret, nullptr);
}

/**
 * @tc.name: CreateDatePicker002
 * @tc.desc: Test DatePickerModel CreateDatePicker.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestTwoNg, CreateDatePicker002, TestSize.Level1)
{
    auto tstTheme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(tstTheme, nullptr);
    auto tmpLanguage = AceApplicationInfo::GetInstance().GetLanguage();
    AceApplicationInfo::GetInstance().language_ = "ug";
    datePickerNg_->CreateDatePicker(tstTheme);
    auto ret = ViewStackProcessor::GetInstance()->GetMainElementNode();
    AceApplicationInfo::GetInstance().language_ = tmpLanguage;
    ASSERT_NE(ret, nullptr);
}

/**
* @tc.name: ParseDirectionKey001
* @tc.desc: Test DatePickerTest ParseDirectionKey
* @tc.type: FUNC
*/
HWTEST_F(DatePickerTestTwoNg, ParseDirectionKey001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create columnNode and columnPattern.
     */
    CreateDatePickerColumnNode();
    ASSERT_NE(columnPattern_, nullptr);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pickerPattern = frameNode->GetPattern<DatePickerPattern>();
    auto totalOptionCount = columnPattern_->GetOptionCount();

    KeyCode code = KeyCode::KEY_UNKNOWN;

    code = KeyCode::KEY_DPAD_UP;
    columnPattern_->stopHaptic_ = false;
    pickerPattern->ParseDirectionKey(columnPattern_, code, totalOptionCount, 0);
    EXPECT_TRUE(columnPattern_->stopHaptic_);

    code = KeyCode::KEY_DPAD_DOWN;
    columnPattern_->stopHaptic_ = false;
    pickerPattern->ParseDirectionKey(columnPattern_, code, totalOptionCount, 0);
    EXPECT_TRUE(columnPattern_->stopHaptic_);

    code = KeyCode::KEY_DPAD_LEFT;
    columnPattern_->stopHaptic_ = false;
    pickerPattern->ParseDirectionKey(columnPattern_, code, totalOptionCount, 0);
    EXPECT_FALSE(columnPattern_->stopHaptic_);

    code = KeyCode::KEY_DPAD_RIGHT;
    columnPattern_->stopHaptic_ = false;
    pickerPattern->ParseDirectionKey(columnPattern_, code, totalOptionCount, 0);
    EXPECT_FALSE(columnPattern_->stopHaptic_);
}

/**
 * @tc.name: DatePickerCanLoopTest001
 * @tc.desc: Test SetCanLoop.
 * @tc.type: FUNC
 */
 HWTEST_F(DatePickerTestTwoNg, DatePickerCanLoopTest001, TestSize.Level1)
 {
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();

    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    DatePickerModel::GetInstance()->SetCanLoop(false);
    EXPECT_FALSE(pickerProperty->GetCanLoopValue());
 }

 /**
 * @tc.name: DatePickerCanLoopTest002
 * @tc.desc: Test DatePickerColumnPattern CanMove when canLoop is true and false.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestTwoNg, DatePickerCanLoopTest002, TestSize.Level1)
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
    columnPattern_->showCount_ = pickerDates.size();

    /**
     * @tc.steps: step2. Call CanMove while canLoop is false.
     * @tc.expected: CanMove returns false when scrolled down at column end.
     */
    DatePickerModel::GetInstance()->SetCanLoop(false);
    columnPattern_->SetCurrentIndex(2);
    EXPECT_FALSE(columnPattern_->CanMove(true));
    columnPattern_->SetCurrentIndex(1);
    EXPECT_TRUE(columnPattern_->CanMove(true));

    /**
     * @tc.steps: step3. Call CanMove while canLoop is true.
     * @tc.expected: CanMove returns true when scrolled down at column end.
     */
    DatePickerModel::GetInstance()->SetCanLoop(true);
    columnPattern_->SetCurrentIndex(2);
    EXPECT_TRUE(columnPattern_->CanMove(true));
}

/**
 * @tc.name: DatePickerCanLoopTest003
 * @tc.desc: test ToJsonValue contains canLoop
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestTwoNg, DatePickerCanLoopTest003, TestSize.Level1)
{
    /**
    * @tc.step: step1. create picker framenode and pattern.
    */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto jsonValue = JsonUtil::Create(true);
    auto jsonValue2 = JsonUtil::Create(true);
    auto pickerPattern = frameNode->GetPattern<DatePickerPattern>();
    auto rowLayoutProperty = pickerPattern->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(rowLayoutProperty, nullptr);
    /**
    * @tc.step: step2. call pattern's ToJsonValue method.
    * @tc.expected: jsonValue2->GetBool("canLoop") is not nullptr.
    */
    rowLayoutProperty->ToJsonValue(jsonValue, filter);
    ASSERT_NE(jsonValue->GetValue("canLoop"), nullptr);
    ASSERT_EQ(jsonValue->GetValue("canLoop")->GetString(), "true");
    /**
    * cover branch canLoop == false
    */
    DatePickerModel::GetInstance()->SetCanLoop(false);
    rowLayoutProperty->ToJsonValue(jsonValue2, filter);
    ASSERT_NE(jsonValue2->GetValue("canLoop"), nullptr);
    ASSERT_EQ(jsonValue2->GetValue("canLoop")->GetString(), "false");
}

/**
 * @tc.name: DatePickerCanLoopTest004
 * @tc.desc: Test DatePickerColumnPattern scroll option.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestTwoNg, DatePickerCanLoopTest004, TestSize.Level1)
{
    /**
    * @tc.steps: step1. Create columnNode and columnPattern.
    */
    CreateDatePickerColumnNode();
    ASSERT_NE(columnNode_, nullptr);
    ASSERT_NE(columnPattern_, nullptr);
    DatePickerModel::GetInstance()->SetCanLoop(false);
    columnPattern_->showCount_ = 3;
    columnPattern_->UpdateTextPropertiesLinear(true, 2.0f);
    auto options = columnPattern_->GetOptions();
    auto pickerDates = options[columnNode_];
    pickerDates.clear();
    pickerDates.emplace_back(PickerDateF::CreateYear(START_YEAR));
    pickerDates.emplace_back(PickerDateF::CreateYear(START_YEAR+1));
    pickerDates.emplace_back(PickerDateF::CreateYear(START_YEAR+2));
    options[columnNode_] = pickerDates;
    columnPattern_->options_ = options;
    columnPattern_->OnModifyDone();

    /**
    * @tc.steps: step2. Call HandleDragMove while inputEventType is AXIS and sourceTool is FINGER.
    * @tc.expected: index is reduced.
    */
    auto eventHub = columnNode_->GetOrCreateEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto gestureHub = eventHub->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    columnPattern_->InitPanEvent(gestureHub);
    columnPattern_->SetCurrentIndex(2);
    EXPECT_EQ(columnPattern_->GetCurrentIndex(), 2);

    auto actionEndTask = columnPattern_->panEvent_->actionEnd_;
    GestureEvent info;
    info.SetSourceTool(SourceTool::FINGER);
    info.SetInputEventType(InputEventType::AXIS);
    actionEndTask(info);
    info.SetOffsetX(1.0f);
    
    Point globalPoint1 = Point(1.0f, 1.0f);
    info.SetGlobalPoint(globalPoint1);
    info.SetOffsetY(200.0f);
    columnPattern_->yLast_ = 0.0f;
    columnPattern_->pressed_ = true;
    columnPattern_->HandleDragMove(info);
    EXPECT_FLOAT_EQ(columnPattern_->yLast_, 201.0f);
    EXPECT_EQ(columnPattern_->GetCurrentIndex(), 1);
    
    Point globalPoint2 = Point(1.0f, 201.0f);
    info.SetGlobalPoint(globalPoint2);
    columnPattern_->pressed_ = true;
    columnPattern_->HandleDragMove(info);
    EXPECT_FLOAT_EQ(columnPattern_->yLast_, 401.0f);
    EXPECT_EQ(columnPattern_->GetCurrentIndex(), 0);

    Point globalPoint3 = Point(1.0f, 401.0f);
    info.SetGlobalPoint(globalPoint3);
    columnPattern_->pressed_ = true;
    columnPattern_->HandleDragMove(info);
    EXPECT_FLOAT_EQ(columnPattern_->yLast_, 601.0f);
    EXPECT_EQ(columnPattern_->GetCurrentIndex(), 0);
}

/**
 * @tc.name: DatePickerCanLoopTest005
 * @tc.desc: test Reset canLoop
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestTwoNg, DatePickerCanLoopTest005, TestSize.Level1)
{
    /**
    * @tc.step: step1. create picker framenode and pattern.
    */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pickerPattern = frameNode->GetPattern<DatePickerPattern>();
    auto rowLayoutProperty = pickerPattern->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(rowLayoutProperty, nullptr);
    DatePickerModel::GetInstance()->SetCanLoop(false);
    ASSERT_FALSE(rowLayoutProperty->GetCanLoopValue(true));
    /**
    * @tc.step: step2. call pattern's Reset method.
    * @tc.expected: rowLayoutProperty->GetCanLoopValue is false.
    */
    rowLayoutProperty->Reset();
    ASSERT_TRUE(rowLayoutProperty->GetCanLoopValue(true));
}

/**
 * @tc.name: DatePickerCanLoopTest006
 * @tc.desc: test Clone canLoop
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestTwoNg, DatePickerCanLoopTest006, TestSize.Level1)
{
    /**
    * @tc.step: step1. create picker framenode and pattern.
    */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pickerPattern = frameNode->GetPattern<DatePickerPattern>();
    auto rowLayoutProperty = pickerPattern->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(rowLayoutProperty, nullptr);
    DatePickerModel::GetInstance()->SetCanLoop(false);
    ASSERT_FALSE(rowLayoutProperty->GetCanLoopValue(true));
    /**
    * @tc.step: step2. call pattern's Clone method.
    * @tc.expected: rowLayoutProperty2->GetCanLoopValue is false.
    */
    auto rowLayoutProperty2 = AceType::DynamicCast<DataPickerRowLayoutProperty>(rowLayoutProperty->Clone());
    ASSERT_FALSE(rowLayoutProperty2->GetCanLoopValue(true));
}

/**
 * @tc.name: DatePickerCanLoopTest007
 * @tc.desc: Test SetCanLoop with framenode.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestTwoNg, DatePickerCanLoopTest007, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();

    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    DatePickerModelNG::SetCanLoop(frameNode, false);
    EXPECT_FALSE(pickerProperty->GetCanLoopValue());
}

/**
 * @tc.name: DatePickerCanLoopTest008
 * @tc.desc: Test GetCanLoopFromLayoutProperty.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestTwoNg, DatePickerCanLoopTest008, TestSize.Level1)
{
    /**
    * @tc.steps: step1. Create columnNode and default canLoop is true.
    */
    CreateDatePickerColumnNode();
    ASSERT_NE(columnNode_, nullptr);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_TRUE(columnPattern_->GetCanLoopFromLayoutProperty());

    /**
    * @tc.steps: step2. Set canLoop value to false.
    */
    DatePickerModelNG::SetCanLoop(frameNode, false);

    /**
    * @tc.steps: step3. GetCanLoopFromLayoutProperty.
    */
    EXPECT_FALSE(columnPattern_->GetCanLoopFromLayoutProperty());
}

/**
 * @tc.name: DatePickerCanLoopTest009
 * @tc.desc: Test OnKeyEvent.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestTwoNg, DatePickerCanLoopTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create columnNode and default canLoop is true.
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
    columnPattern_->showCount_ = pickerDates.size();
 
    /**
     * @tc.steps: step2. Call OnKeyEvent while canLoop is true.
     * @tc.expected: CurrentIndex changes.
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    
    KeyEvent keyEventUp(KeyCode::KEY_DPAD_UP, KeyAction::DOWN);
    columnPattern_->SetCurrentIndex(0);
    datePickerPattern->OnKeyEvent(keyEventUp);
    EXPECT_EQ(columnPattern_->GetCurrentIndex(), 2);

    /**
     * @tc.steps: step3. Call OnKeyEvent while canLoop is false.
     * @tc.expected: CurrentIndex does not change.
     */
    DatePickerModel::GetInstance()->SetCanLoop(false);
    columnPattern_->SetCurrentIndex(0);
    datePickerPattern->OnKeyEvent(keyEventUp);
    EXPECT_EQ(columnPattern_->GetCurrentIndex(), 0);
}

/**
 * @tc.name: DatePickerFocusRectWithPadding
 * @tc.desc: Test datePicker focus rect normal when padding is set.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestTwoNg, DatePickerFocusRectWithPadding, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pickerPattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pickerPattern = frameNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    /**
     * @tc.steps: step2. Get default focus rect.
     */
    RoundRect rect;
    pickerPattern->GetInnerFocusPaintRect(rect);
    EXPECT_EQ(rect.GetRect().GetX(), 3.5f);

    /**
     * @tc.steps: step3. Set padding.
     */
    PaddingPropertyF testPadding;
    testPadding.left = 10.0f;
    testPadding.right = 10.0f;
    testPadding.top = 10.0f;
    testPadding.bottom = 10.0f;
    auto host = pickerPattern->GetHost();
    CHECK_NULL_VOID(host);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    geometryNode->UpdatePaddingWithBorder(testPadding);
    pickerPattern->GetInnerFocusPaintRect(rect);
    EXPECT_EQ(rect.GetRect().GetX(), 13.5f);
}

/**
 * @tc.name: DatePickerDialogCanLoop001
 * @tc.desc: Test timePickerNode in DatePickerDialog when canLoop is false.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestTwoNg, DatePickerDialogCanLoop001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pickeDialog.
     */
    DatePickerSettingData settingData;
    settingData.isLunar = false;
    settingData.showTime = true;
    settingData.canLoop = false;
    settingData.useMilitary = false;
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontWeight = FontWeight::W400;
    buttonInfos.push_back(info1);
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(dialogNode, nullptr);

    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto pickerStack = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(1));
    /**
     * @tc.steps: step2.call CanMove.
     * @tc.expected:timePickerNode cannot loop when at top.
     */
    bool tested = false;
    for (uint32_t i = 0; i < timePickerNode->GetChildren().size(); i++) {
        auto childStackNode = AceType::DynamicCast<FrameNode>(timePickerNode->GetChildAtIndex(i));
        CHECK_NULL_VOID(childStackNode);
        auto layoutProperty = childStackNode->GetLayoutProperty<LayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        layoutProperty->UpdateAlignment(Alignment::CENTER);
        for (uint32_t j = 0; j < childStackNode->GetChildren().size(); j++) {
            auto childNode = AceType::DynamicCast<FrameNode>(childStackNode->GetChildAtIndex(j));
            CHECK_NULL_VOID(childNode);
            auto timePickerColumnPattern = childNode->GetPattern<TimePickerColumnPattern>();
            CHECK_NULL_VOID(timePickerColumnPattern);
            timePickerColumnPattern->SetCurrentIndex(0);
            EXPECT_FALSE(timePickerColumnPattern->CanMove(false));
            EXPECT_TRUE(timePickerColumnPattern->CanMove(true));
            tested = true;
        }
    }
    EXPECT_TRUE(tested);
}

/**
 * @tc.name: DatePickerDialogCanLoop002
 * @tc.desc: Test timePickerNode in DatePickerDialog when canLoop is true.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestTwoNg, DatePickerDialogCanLoop002, TestSize.Level1)
{
    /**
    * @tc.steps: step1. Create pickeDialog.
    */
    DatePickerSettingData settingData;
    settingData.isLunar = false;
    settingData.showTime = true;
    settingData.canLoop = true;
    settingData.useMilitary = false;
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontWeight = FontWeight::W400;
    buttonInfos.push_back(info1);
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(dialogNode, nullptr);

    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto pickerStack = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(1));
    /**
    * @tc.steps: step2.call CanMove.
    * @tc.expected:timePickerNode can loop when at top.
    */
    bool tested = false;
    for (uint32_t i = 0; i < timePickerNode->GetChildren().size(); i++) {
        auto childStackNode = AceType::DynamicCast<FrameNode>(timePickerNode->GetChildAtIndex(i));
        CHECK_NULL_VOID(childStackNode);
        auto layoutProperty = childStackNode->GetLayoutProperty<LayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        layoutProperty->UpdateAlignment(Alignment::CENTER);
        for (uint32_t j = 0; j < childStackNode->GetChildren().size(); j++) {
            auto childNode = AceType::DynamicCast<FrameNode>(childStackNode->GetChildAtIndex(j));
            CHECK_NULL_VOID(childNode);
            auto timePickerColumnPattern = childNode->GetPattern<TimePickerColumnPattern>();
            CHECK_NULL_VOID(timePickerColumnPattern);
            timePickerColumnPattern->SetCurrentIndex(0);
            EXPECT_FALSE(timePickerColumnPattern->CanMove(true));
            EXPECT_TRUE(timePickerColumnPattern->CanMove(true));
            tested = true;
        }
    }
    EXPECT_TRUE(tested);
}

/**
 * @tc.name: DatePickerPatternTest022
 * @tc.desc: Test OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestTwoNg, DatePickerPatternTest022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pickerPattern.
     */
    CreateDatePickerColumnNode();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();

    auto pickerPattern = frameNode->GetPattern<DatePickerPattern>();
    auto host = pickerPattern->GetHost();
    auto optionCount = pickerPattern->datePickerColumns_.size();
    EXPECT_EQ(optionCount, 3);
    RefPtr<FrameNode> stackYear;
    RefPtr<FrameNode> stackMonth;
    RefPtr<FrameNode> stackDay;
    pickerPattern->OrderAllChildNode(stackYear, stackMonth, stackDay);
    for (const auto& child : stackDay->GetChildren()) {
        auto frameNodeChild = AceType::DynamicCast<NG::FrameNode>(child);
        CHECK_NULL_VOID(frameNodeChild);
        auto layoutProperty = frameNodeChild->GetLayoutProperty();
        EXPECT_EQ(layoutProperty->GetVisibilityValue(VisibleType::INVISIBLE), VisibleType::VISIBLE);
    }
    /**
     * @tc.steps: step2.call OnModifyDone.
     * @tc.expected:all branch of OnModifyDone is executed correctly.
     */
    auto datePickerRowLayoutProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(datePickerRowLayoutProperty, nullptr);

    pickerPattern->isFiredDateChange_ = true;
    pickerPattern->SetMode(DatePickerMode::YEAR_AND_MONTH);
    pickerPattern->OnModifyDone();
    pickerPattern->OrderAllChildNode(stackYear, stackMonth, stackDay);
    bool tested = false;
    for (const auto& child : stackDay->GetChildren()) {
        auto frameNodeChild = AceType::DynamicCast<NG::FrameNode>(child);
        CHECK_NULL_VOID(frameNodeChild);
        auto layoutProperty = frameNodeChild->GetLayoutProperty();
        EXPECT_EQ(layoutProperty->GetVisibilityValue(VisibleType::INVISIBLE), VisibleType::GONE);
        tested = true;
    }
    EXPECT_TRUE(tested);
}
} // namespace OHOS::Ace::NG