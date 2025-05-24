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

#include "base/geometry/dimension.h"
#include "base/geometry/offset.h"
#include "base/geometry/point.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/animation/curves.h"
#include "core/components/common/properties/color.h"
#include "core/components/picker/picker_data.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/click_event.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/focus_hub.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/time_picker/timepicker_column_pattern.h"
#include "core/components_ng/pattern/time_picker/timepicker_dialog_view.h"
#include "core/components_ng/pattern/time_picker/timepicker_model_ng.h"
#include "core/components_ng/pattern/time_picker/timepicker_row_pattern.h"
#include "core/components_ng/pattern/picker_utils/toss_animation_controller.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/event/key_event.h"
#include "core/event/touch_event.h"
#include "core/gestures/gesture_info.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
std::unique_ptr<TimePickerModel> TimePickerModel::timePickerInstance_ = nullptr;
std::unique_ptr<TimePickerDialogModel> TimePickerDialogModel::timePickerDialogInstance_ = nullptr;
std::once_flag TimePickerModel::onceFlag_;
std::once_flag TimePickerDialogModel::onceFlag_;

TimePickerModel* TimePickerModel::GetInstance()
{
    std::call_once(onceFlag_, []() {
        timePickerInstance_.reset(new NG::TimePickerModelNG());
    });
    return timePickerInstance_.get();
}

TimePickerDialogModel* TimePickerDialogModel::GetInstance()
{
    std::call_once(onceFlag_, []() {
        timePickerDialogInstance_.reset(new NG::TimePickerDialogModelNG());
    });
    return timePickerDialogInstance_.get();
}
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
namespace {
const InspectorFilter filter;
constexpr double TOSS_DELTA = 20.0;
const int CURRENT_VALUE1 = 3;
const int CURRENT_VALUE3 = 4;
const int CURRENT_VALUE4 = 5;
const int CURRENT_VALUE5 = 6;
const int CURRENT_VALUE2 = 10;
const int MIDDLE_OF_COUNTS = 2;
const int SHOW_COUNT = 7;
const int DEFAULT_INDEX = -1;
const std::string AM = "AM ";
const std::string PM = "PM ";
const std::string COLON = ":";
const std::string ZERO = "0";
const std::string TIME_AMPM = "01";
const std::string AMPM_TIME = "10";
const PickerTime TIME_PICKED = PickerTime(14, 9, 10);
const PickerTime TIME_PICKED_PREFIXZERO = PickerTime(3, 3, 3);
const int32_t AM_PM_PICKED = 1;
const int32_t HOUR_PICKED = 1;
const int32_t HOUR24_PICKED = 14;
const int32_t MINUTE_PICKED = 9;
const int32_t SECOND_PICKED = 10;
const uint32_t MINUTE_59 = 59;
const std::vector<int> DEFAULT_VALUE = { 0, 1, 2, 3, 4 };
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
const float EXTRA_WIDTH = 50.0f;
const Dimension PRESS_INTERVAL = 4.0_vp;
const Dimension PRESS_RADIUS = 8.0_vp;
const uint32_t DEFAULT_YEAR = 1;
const uint32_t DEFAULT_MONTH = 2;
const uint32_t DEFAULT_DAY = 5;
constexpr uint32_t AM_PM_HOUR_12 = 12;
constexpr int32_t CHILD_WITH_AMPM_SIZE = 3;
const double YOFFSET_START1 = 0.0;
const double YOFFSET_END1 = 1000.0;
const double TIME_PLUS = 1 * 100.0;
const SizeF TEST_FRAME_SIZE { 20, 30 };
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
class TimePickerPatternTestNg : public testing::Test {
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

void TimePickerPatternTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void TimePickerPatternTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void TimePickerPatternTestNg::SetUp()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        return GetTheme(type);
    });
    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([](ThemeType type, int32_t themeScopeId) -> RefPtr<Theme> { return GetTheme(type); });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void TimePickerPatternTestNg::TearDown()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    ViewStackProcessor::GetInstance()->ClearStack();
}

void TimePickerPatternTestNg::CreateTimePickerColumnNode()
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
 * @tc.name: TimePickerPatternOnAttachToFrameNode001
 * @tc.desc: Test TimePickerRowPattern OnAttachToFrameNode.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerModelNGCreateTimePicker001, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);
    auto timePickerPattern = AceType::MakeRefPtr<TimePickerRowPattern>();
    timePickerPattern->AttachToFrameNode(frameNode);
    timePickerPattern->OnAttachToFrameNode();
    auto host = timePickerPattern->GetHost();
    EXPECT_NE(host, nullptr);
}

/**
 * @tc.name: TimePickerModelNGSetDisappearTextStyle001
 * @tc.desc: Test TimePickerModelNG SetDisappearTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerModelNGSetDisappearTextStyle001, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    PickerTextStyle data;
    TimePickerModelNG::GetInstance()->SetDisappearTextStyle(theme, data);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_TRUE(pickerProperty->HasDisappearFontSize());
    EXPECT_FALSE(pickerProperty->HasDisappearColor());
    EXPECT_TRUE(pickerProperty->HasDisappearWeight());
}

/**
 * @tc.name: TimePickerModelNGSetDisappearTextStyle002
 * @tc.desc: Test TimePickerModelNG SetDisappearTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerModelNGSetDisappearTextStyle002, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    PickerTextStyle data;
    data.fontSize = Dimension(10);
    data.textColor = Color::RED;
    data.fontWeight = Ace::FontWeight::BOLD;
    TimePickerModelNG::GetInstance()->SetDisappearTextStyle(theme, data);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(Color::RED, pickerProperty->GetDisappearColor().value());
    EXPECT_EQ(Dimension(10), pickerProperty->GetDisappearFontSize().value());
    EXPECT_EQ(Ace::FontWeight::BOLD, pickerProperty->GetDisappearWeight().value());
}

/**
 * @tc.name: TimePickerModelNGSetDisappearTextStyle003
 * @tc.desc: Test TimePickerModelNG SetDisappearTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerModelNGSetDisappearTextStyle003, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    PickerTextStyle data;
    data.fontSize = Dimension(0);
    TimePickerModelNG::GetInstance()->SetDisappearTextStyle(theme, data);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_TRUE(pickerProperty->HasDisappearFontSize());
}

/**
 * @tc.name: TimePickerModelNGSetDisappearTextStyle004
 * @tc.desc: Test TimePickerModelNG SetDisappearTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerModelNGSetDisappearTextStyle004, TestSize.Level1)
{
    TimePickerSettingData settingData;
    settingData.properties.disappearTextStyle_.textColor = Color::RED;
    settingData.properties.disappearTextStyle_.fontSize = Dimension(10);
    settingData.properties.disappearTextStyle_.fontWeight = Ace::FontWeight::BOLD;
    auto isUserSet = TimePickerDialogView::GetIsUserSetTextProperties(settingData.properties);
    EXPECT_EQ(isUserSet, true);
}

/**
 * @tc.name: TimePickerModelNGSetNormalTextStyle001
 * @tc.desc: Test TimePickerModelNG SetNormalTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerModelNGSetNormalTextStyle001, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    PickerTextStyle data;
    TimePickerModelNG::GetInstance()->SetNormalTextStyle(theme, data);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_TRUE(pickerProperty->HasFontSize());
    EXPECT_FALSE(pickerProperty->HasColor());
    EXPECT_TRUE(pickerProperty->HasWeight());
}

/**
 * @tc.name: TimePickerModelNGSetNormalTextStyle002
 * @tc.desc: Test TimePickerModelNG SetNormalTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerModelNGSetNormalTextStyle002, TestSize.Level1)
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
    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(Color::RED, pickerProperty->GetColor().value());
    EXPECT_EQ(Dimension(10), pickerProperty->GetFontSize().value());
    EXPECT_EQ(Ace::FontWeight::BOLD, pickerProperty->GetWeight().value());
}

/**
 * @tc.name: TimePickerModelNGSetNormalTextStyle003
 * @tc.desc: Test TimePickerModelNG SetNormalTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerModelNGSetNormalTextStyle003, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();

    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    PickerTextStyle data;
    data.fontSize = Dimension(0);
    TimePickerModelNG::GetInstance()->SetNormalTextStyle(theme, data);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_TRUE(pickerProperty->HasFontSize());
}

/**
 * @tc.name: TimePickerModelNGSetNormalTextStyle004
 * @tc.desc: Test TimePickerModelNG SetDisappearTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerModelNGSetNormalTextStyle004, TestSize.Level1)
{
    TimePickerSettingData settingData;
    settingData.properties.normalTextStyle_.textColor = Color::RED;
    settingData.properties.normalTextStyle_.fontSize = Dimension(10);
    settingData.properties.normalTextStyle_.fontWeight = Ace::FontWeight::BOLD;
    auto isUserSet = TimePickerDialogView::GetIsUserSetTextProperties(settingData.properties);
    EXPECT_EQ(isUserSet, true);
}

/**
 * @tc.name: TimePickerModelNGSetSelectedTextStyle001
 * @tc.desc: Test TimePickerModelNG SetSelectedTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerModelNGSetSelectedTextStyle001, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();

    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    PickerTextStyle data;
    TimePickerModelNG::GetInstance()->SetSelectedTextStyle(theme, data);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_TRUE(pickerProperty->HasSelectedFontSize());
    EXPECT_FALSE(pickerProperty->HasSelectedColor());
    EXPECT_TRUE(pickerProperty->HasSelectedWeight());
}

/**
 * @tc.name: TimePickerModelNGSetSelectedTextStyle002
 * @tc.desc: Test TimePickerModelNG SetSelectedTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerModelNGSetSelectedTextStyle002, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();

    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    PickerTextStyle data;
    data.fontSize = Dimension(10);
    data.textColor = Color::RED;
    data.fontWeight = Ace::FontWeight::BOLD;
    TimePickerModelNG::GetInstance()->SetSelectedTextStyle(theme, data);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(Color::RED, pickerProperty->GetSelectedColor().value());
    EXPECT_EQ(Dimension(10), pickerProperty->GetSelectedFontSize().value());
    EXPECT_EQ(Ace::FontWeight::BOLD, pickerProperty->GetSelectedWeight().value());
}

/**
 * @tc.name: TimePickerModelNGSetSelectedTextStyle003
 * @tc.desc: Test TimePickerModelNG SetSelectedTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerModelNGSetSelectedTextStyle003, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();

    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    PickerTextStyle data;
    data.fontSize = Dimension(0);
    TimePickerModelNG::GetInstance()->SetSelectedTextStyle(theme, data);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_TRUE(pickerProperty->HasSelectedFontSize());
}

/**
 * @tc.name: TimePickerModelNGSetSelectedTextStyle004
 * @tc.desc: Test TimePickerModelNG SetDisappearTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerModelNGSetSelectedTextStyle004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create TimePickerSettingData and call GetIsUserSetTextProperties.
     * @tc.expected: the third if condition is true and return true.
     */
    TimePickerSettingData settingData;
    settingData.properties.selectedTextStyle_.textColor = Color::RED;
    settingData.properties.selectedTextStyle_.fontSize = Dimension(10);
    settingData.properties.normalTextStyle_.fontWeight = Ace::FontWeight::BOLD;
    settingData.isUseMilitaryTime = false;
    auto isUserSet = TimePickerDialogView::GetIsUserSetTextProperties(settingData.properties);
    EXPECT_EQ(isUserSet, true);
    /**
     * @tc.steps: step1+. set TimePickerSettingData and call GetIsUserSetTextProperties.
     * @tc.expected: all of if conditions are false and return false.
     */
    settingData.properties.selectedTextStyle_.fontSize = Dimension(0);
    settingData.properties.normalTextStyle_.fontSize = Dimension(0);
    settingData.properties.disappearTextStyle_.fontSize = Dimension(0);
    isUserSet = TimePickerDialogView::GetIsUserSetTextProperties(settingData.properties);
    EXPECT_EQ(isUserSet, false);
}

/**
 * @tc.name: TimePickerColumnPattern001
 * @tc.desc: Test TimePickerColumnPattern FlushCurrentOptions.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerColumnPattern001, TestSize.Level1)
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
HWTEST_F(TimePickerPatternTestNg, TimePickerColumnPattern002, TestSize.Level1)
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
HWTEST_F(TimePickerPatternTestNg, TimePickerColumnPattern003, TestSize.Level1)
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
HWTEST_F(TimePickerPatternTestNg, TimePickerColumnPattern004, TestSize.Level1)
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
HWTEST_F(TimePickerPatternTestNg, TimePickerColumnPattern005, TestSize.Level1)
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
 * @tc.name: TimePickerDialogViewShow001
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewShow001, TestSize.Level1)
{
    TimePickerSettingData settingData;
    settingData.properties.disappearTextStyle_.textColor = Color::RED;
    settingData.properties.disappearTextStyle_.fontSize = Dimension(0);
    settingData.properties.disappearTextStyle_.fontWeight = Ace::FontWeight::BOLD;

    settingData.properties.normalTextStyle_.textColor = Color::RED;
    settingData.properties.normalTextStyle_.fontSize = Dimension(0);
    settingData.properties.normalTextStyle_.fontWeight = Ace::FontWeight::BOLD;

    settingData.properties.selectedTextStyle_.textColor = Color::RED;
    settingData.properties.selectedTextStyle_.fontSize = Dimension(0);
    settingData.properties.normalTextStyle_.fontWeight = Ace::FontWeight::BOLD;
    settingData.isUseMilitaryTime = false;

    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(1, 1, 1);

    DialogProperties dialogProperties;

    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;

    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode = TimePickerDialogView::Show(
        dialogProperties, settingData, buttonInfos, timePickerProperty, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
}

/**
 * @tc.name: TimePickerLayoutPropertyToJsonValue001
 * @tc.desc: Test TimePickerLayoutProperty ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerLayoutPropertyToJsonValue001, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();

    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    auto disappearFont = JsonUtil::Create(true);
    pickerProperty->ToJsonValue(disappearFont, filter);
    EXPECT_NE(disappearFont, nullptr);
}

/**
 * @tc.name: TimePickerLayoutPropertyReset001
 * @tc.desc: Test TimePickerLayoutProperty Reset.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerLayoutPropertyReset001, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();

    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    pickerProperty->Reset();
}

/**
 * @tc.name: TimePickerLayoutPropertyClone001
 * @tc.desc: Test TimePickerLayoutProperty Clone.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerLayoutPropertyClone001, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();

    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_NE(pickerProperty->Clone(), nullptr);
}

/**
 * @tc.name: TimePickerAccessibilityPropertyTestNg001
 * @tc.desc: Test the ItemCounts property of TimePickerColumnPattern
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerAccessibilityPropertyTestNg001, TestSize.Level1)
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
    auto options = minuteColumnPattern->GetOptions();
    options[minuteColumnNode] = DEFAULT_VALUE.size();
    minuteColumnPattern->SetOptions(options);
    auto accessibilityProperty = minuteColumnNode->GetAccessibilityProperty<TimePickerColumnAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetCollectionItemCounts(), static_cast<int32_t>(DEFAULT_VALUE.size()));

    options.erase(minuteColumnNode);
    minuteColumnPattern->SetOptions(options);
    EXPECT_EQ(accessibilityProperty->GetCollectionItemCounts(), 0);
}

/**
 * @tc.name: TimePickerAccessibilityPropertyTestNg002
 * @tc.desc: Test the IsScrollable property of TimePickerColumnPattern
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerAccessibilityPropertyTestNg002, TestSize.Level1)
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
    auto minuteColumn = allChildNode["minute"].Upgrade();
    ASSERT_NE(minuteColumn, nullptr);

    auto accessibilityProperty = minuteColumn->GetAccessibilityProperty<TimePickerColumnAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_TRUE(accessibilityProperty->IsScrollable());

    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    auto options = minuteColumnPattern->GetOptions();
    options[minuteColumn] = 0;
    minuteColumnPattern->SetOptions(options);
    EXPECT_FALSE(accessibilityProperty->IsScrollable());
}

/**
 * @tc.name: TimePickerAccessibilityPropertyTestNg003
 * @tc.desc: Test the Index properties of TimePickerColumnPattern
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerAccessibilityPropertyTestNg003, TestSize.Level1)
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
    auto minuteColumn = allChildNode["minute"].Upgrade();
    ASSERT_NE(minuteColumn, nullptr);

    auto accessibilityProperty = minuteColumn->GetAccessibilityProperty<TimePickerColumnAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    minuteColumnPattern->SetShowCount(SHOW_COUNT);
    minuteColumnPattern->SetCurrentIndex(CURRENT_VALUE1);
    EXPECT_EQ(accessibilityProperty->GetCurrentIndex(), CURRENT_VALUE1);

    auto itemCount = accessibilityProperty->GetCollectionItemCounts();
    EXPECT_EQ(accessibilityProperty->GetBeginIndex(),
        (itemCount + CURRENT_VALUE1 - SHOW_COUNT / MIDDLE_OF_COUNTS) % itemCount);
    EXPECT_EQ(
        accessibilityProperty->GetEndIndex(), (itemCount + CURRENT_VALUE1 + SHOW_COUNT / MIDDLE_OF_COUNTS) % itemCount);

    minuteColumnPattern->SetShowCount(itemCount + itemCount);
    EXPECT_EQ(accessibilityProperty->GetBeginIndex(), 0);
    EXPECT_EQ(accessibilityProperty->GetEndIndex(), itemCount - 1);

    auto options = minuteColumnPattern->GetOptions();
    options[minuteColumn] = 0;
    minuteColumnPattern->SetOptions(options);

    EXPECT_EQ(accessibilityProperty->GetBeginIndex(), DEFAULT_INDEX);
    EXPECT_EQ(accessibilityProperty->GetEndIndex(), DEFAULT_INDEX);
}

/**
 * @tc.name: TimePickerAccessibilityPropertyTestNg004
 * @tc.desc: Test the Text property of TimePickerColumnPattern
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerAccessibilityPropertyTestNg004, TestSize.Level1)
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
    auto accessibilityProperty = minuteColumnNode->GetAccessibilityProperty<TimePickerColumnAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(), "");

    options[minuteColumnNode] = DEFAULT_VALUE.size();
    minuteColumnPattern->SetOptions(options);
    EXPECT_EQ(accessibilityProperty->GetText(), "03");

    options.erase(minuteColumnNode);
    minuteColumnPattern->SetOptions(options);
    EXPECT_EQ(accessibilityProperty->GetText(), "");
}

/**
 * @tc.name: TimePickerAccessibilityPropertyTestNg005
 * @tc.desc: Test the SupportAction property of TimePickerPattern
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerAccessibilityPropertyTestNg005, TestSize.Level1)
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
    options[minuteColumnNode] = DEFAULT_VALUE.size();
    minuteColumnPattern->SetOptions(options);
    auto accessibilityProperty = minuteColumnNode->GetAccessibilityProperty<TimePickerColumnAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    accessibilityProperty->ResetSupportAction();
    std::unordered_set<AceAction> supportAceActions = accessibilityProperty->GetSupportAction();
    uint64_t actions = 0;
    uint64_t exptectActions = 0;
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_BACKWARD);
    for (auto action : supportAceActions) {
        actions |= 1UL << static_cast<uint32_t>(action);
    }
    EXPECT_EQ(actions, exptectActions);
}

/**
 * @tc.name: TimePickerAccessibilityPropertyTestNg006
 * @tc.desc: Test the Text property for of TimePickerRowPattern if it is MilitaryTime.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerAccessibilityPropertyTestNg006, TestSize.Level1)
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
    auto minuteColumn = allChildNode["minute"].Upgrade();
    ASSERT_NE(minuteColumn, nullptr);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    minuteColumnPattern->SetCurrentIndex(CURRENT_VALUE1);
    auto hourColumn = allChildNode["hour"].Upgrade();
    ASSERT_NE(hourColumn, nullptr);
    auto hourColumnPattern = hourColumn->GetPattern<TimePickerColumnPattern>();
    hourColumnPattern->SetCurrentIndex(CURRENT_VALUE1);

    auto accessibilityProperty = frameNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    timePickerRowPattern->SetHour24(true);
    EXPECT_EQ(accessibilityProperty->GetText(),
        ZERO + std::to_string(CURRENT_VALUE1) + COLON + ZERO + std::to_string(CURRENT_VALUE1));

    hourColumnPattern->SetCurrentIndex(CURRENT_VALUE2);
    minuteColumnPattern->SetCurrentIndex(CURRENT_VALUE2);
    EXPECT_EQ(
        accessibilityProperty->GetText(), std::to_string(CURRENT_VALUE2) + COLON + std::to_string(CURRENT_VALUE2));
}

/**
 * @tc.name: TimePickerAccessibilityPropertyTestNg007
 * @tc.desc: Test the Text property of TimePickerRowPattern if it is not MilitaryTime.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerAccessibilityPropertyTestNg007, TestSize.Level1)
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
    auto minuteColumn = allChildNode["minute"].Upgrade();
    ASSERT_NE(minuteColumn, nullptr);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    minuteColumnPattern->SetCurrentIndex(CURRENT_VALUE1);
    auto hourColumn = allChildNode["hour"].Upgrade();
    ASSERT_NE(hourColumn, nullptr);
    auto hourColumnPattern = hourColumn->GetPattern<TimePickerColumnPattern>();
    hourColumnPattern->SetCurrentIndex(CURRENT_VALUE1);
    auto amPmColumn = allChildNode["amPm"].Upgrade();
    ASSERT_NE(amPmColumn, nullptr);
    auto amPmPickerColumnPattern = amPmColumn->GetPattern<TimePickerColumnPattern>();

    auto accessibilityProperty = frameNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    amPmPickerColumnPattern->SetCurrentIndex(0);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + ZERO + std::to_string(CURRENT_VALUE1 + 1) + COLON + ZERO + std::to_string(CURRENT_VALUE1));
    amPmPickerColumnPattern->SetCurrentIndex(1);
    EXPECT_EQ(accessibilityProperty->GetText(),
        PM + ZERO + std::to_string(CURRENT_VALUE1 + 1) + COLON + ZERO + std::to_string(CURRENT_VALUE1));

    minuteColumnPattern->SetCurrentIndex(CURRENT_VALUE2);
    hourColumnPattern->SetCurrentIndex(CURRENT_VALUE2);

    amPmPickerColumnPattern->SetCurrentIndex(0);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + std::to_string(CURRENT_VALUE2 + 1) + COLON + std::to_string(CURRENT_VALUE2));
    amPmPickerColumnPattern->SetCurrentIndex(1);
    EXPECT_EQ(accessibilityProperty->GetText(),
        PM + std::to_string(CURRENT_VALUE2 + 1) + COLON + std::to_string(CURRENT_VALUE2));
}

/**
 * @tc.name: TimePickerAccessibilityPropertyTestNg008
 * @tc.desc: Test the Text property for leading zero of TimePickerRowPattern when time is MilitaryTime.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerAccessibilityPropertyTestNg008, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    ZeroPrefixType showType = ZeroPrefixType::SHOW;
    ZeroPrefixType hideType = ZeroPrefixType::HIDE;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, true);
    TimePickerModelNG::GetInstance()->SetHour24(true);
    TimePickerModelNG::GetInstance()->SetSelectedTime(TIME_PICKED_PREFIXZERO);
    TimePickerModelNG::GetInstance()->SetDateTimeOptions(hideType, showType, hideType);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();

    auto hourColumn = allChildNode["hour"].Upgrade();
    ASSERT_NE(hourColumn, nullptr);
    auto hourColumnPattern = hourColumn->GetPattern<TimePickerColumnPattern>();
    hourColumnPattern->SetCurrentIndex(CURRENT_VALUE1);

    auto minuteColumn = allChildNode["minute"].Upgrade();
    ASSERT_NE(minuteColumn, nullptr);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    minuteColumnPattern->SetCurrentIndex(CURRENT_VALUE1);

    auto secondColumn = allChildNode["second"].Upgrade();
    ASSERT_NE(secondColumn, nullptr);
    auto secondColumnPattern = secondColumn->GetPattern<TimePickerColumnPattern>();
    secondColumnPattern->SetCurrentIndex(CURRENT_VALUE1);

    auto accessibilityProperty = frameNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    EXPECT_EQ(accessibilityProperty->GetText(),
        std::to_string(CURRENT_VALUE1) + COLON +
        ZERO + std::to_string(CURRENT_VALUE1) + COLON +
        std::to_string(CURRENT_VALUE1));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerAccessibilityPropertyTestNg009
 * @tc.desc: Test the Text property for leading zero of TimePickerRowPattern when time is not MilitaryTime.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerAccessibilityPropertyTestNg009, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    ZeroPrefixType showType = ZeroPrefixType::SHOW;
    ZeroPrefixType hideType = ZeroPrefixType::HIDE;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, false);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    TimePickerModelNG::GetInstance()->SetSelectedTime(TIME_PICKED_PREFIXZERO);
    TimePickerModelNG::GetInstance()->SetDateTimeOptions(showType, hideType, showType);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();

    auto hourColumn = allChildNode["hour"].Upgrade();
    ASSERT_NE(hourColumn, nullptr);
    auto hourColumnPattern = hourColumn->GetPattern<TimePickerColumnPattern>();
    hourColumnPattern->SetCurrentIndex(CURRENT_VALUE1);

    auto minuteColumn = allChildNode["minute"].Upgrade();
    ASSERT_NE(minuteColumn, nullptr);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    minuteColumnPattern->SetCurrentIndex(CURRENT_VALUE1);

    auto amPmColumn = allChildNode["amPm"].Upgrade();
    ASSERT_NE(amPmColumn, nullptr);
    auto amPmPickerColumnPattern = amPmColumn->GetPattern<TimePickerColumnPattern>();

    auto accessibilityProperty = frameNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    amPmPickerColumnPattern->SetCurrentIndex(0);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + ZERO + std::to_string(CURRENT_VALUE1 + 1) + COLON + std::to_string(CURRENT_VALUE1));

    amPmPickerColumnPattern->SetCurrentIndex(1);
    EXPECT_EQ(accessibilityProperty->GetText(),
        PM + ZERO + std::to_string(CURRENT_VALUE1 + 1) + COLON + std::to_string(CURRENT_VALUE1));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerColumnPattern006
 * @tc.desc: Test mouse event callback and touch event callback
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerColumnPattern006, TestSize.Level1)
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
    EXPECT_TRUE(minuteColumnPattern->hoverd_);
    auto renderContext = buttonNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetBackgroundColorValue(), Color::BLACK);
    (*minuteColumnPattern->mouseEvent_)(false);
    EXPECT_FALSE(minuteColumnPattern->hoverd_);
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

    minuteColumnPattern->hoverd_ = true;
    (*minuteColumnPattern->touchListener_)(touchEventInfo);
    EXPECT_EQ(renderContext->GetBackgroundColorValue(), Color::BLACK);
    EXPECT_EQ(minuteColumnPattern->GetLocalDownDistance(), 0.0f);

    minuteColumnPattern->hoverd_ = false;
    (*minuteColumnPattern->touchListener_)(touchEventInfo);
    EXPECT_EQ(renderContext->GetBackgroundColorValue(), Color::TRANSPARENT);

    TouchLocationInfo touchLocationInfoMove(DEFAULT_FINGER_ID);
    touchLocationInfoMove.SetTouchType(TouchType::MOVE);
    touchLocationInfoMove.SetLocalLocation(offSet);
    touchEventInfo.touches_.clear();
    touchEventInfo.AddTouchLocationInfo(std::move(touchLocationInfoMove));

    minuteColumnPattern->hoverd_ = true;
    (*minuteColumnPattern->touchListener_)(touchEventInfo);
    EXPECT_EQ(renderContext->GetBackgroundColorValue(), Color::BLACK);
    minuteColumnPattern->hoverd_ = false;
    (*minuteColumnPattern->touchListener_)(touchEventInfo);
    EXPECT_EQ(renderContext->GetBackgroundColorValue(), Color::TRANSPARENT);
}

/**
 * @tc.name: TimePickerColumnPattern007
 * @tc.desc: Test OnDirtyLayoutWrapperSwap function
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerColumnPattern007, TestSize.Level1)
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
HWTEST_F(TimePickerPatternTestNg, TimePickerColumnPattern008, TestSize.Level1)
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
HWTEST_F(TimePickerPatternTestNg, TimePickerColumnPattern009, TestSize.Level1)
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
HWTEST_F(TimePickerPatternTestNg, TimePickerColumnPattern010, TestSize.Level1)
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

    auto eventHub = frameNode->GetOrCreateEventHub<EventHub>();
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
HWTEST_F(TimePickerPatternTestNg, TimePickerColumnPattern012, TestSize.Level1)
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
HWTEST_F(TimePickerPatternTestNg, TimePickerColumnPattern013, TestSize.Level1)
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
HWTEST_F(TimePickerPatternTestNg, TimePickerColumnPattern014, TestSize.Level1)
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
HWTEST_F(TimePickerPatternTestNg, TimePickerColumnPattern015, TestSize.Level1)
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

    auto eventHub = frameNode->GetOrCreateEventHub<EventHub>();
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
 * @tc.name: TimePickerRowPattern001
 * @tc.desc: Test TimePickerRowPattern OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerRowPattern001, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    frameNode->GetGeometryNode()->frame_.rect_.SetWidth(EXTRA_WIDTH);
    auto dirty = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), AceType::MakeRefPtr<LayoutProperty>());
    DirtySwapConfig config;
    config.frameSizeChange = true;
    EXPECT_TRUE(timePickerRowPattern->OnDirtyLayoutWrapperSwap(dirty, config));

    auto children = frameNode->GetChildren();
    auto height = theme->GetDividerSpacing();
    auto width = frameNode->GetGeometryNode()->GetFrameSize().Width() / static_cast<float>(children.size());
    auto defaultWidth = height.ConvertToPx() * 2;
    EXPECT_LT(width, defaultWidth);

    for (const auto& child : children) {
        auto childNode = AceType::DynamicCast<FrameNode>(child);
        CHECK_NULL_VOID(childNode);
        auto newWidth = childNode->GetGeometryNode()->GetFrameSize().Width();
        auto buttonNode = AceType::DynamicCast<FrameNode>(child->GetFirstChild());
        auto buttonLayoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
        EXPECT_EQ(buttonLayoutProperty->GetMeasureType(), MeasureType::MATCH_PARENT_MAIN_AXIS);
        EXPECT_EQ(buttonLayoutProperty->GetTypeValue(), ButtonType::NORMAL);
        auto calcSize = buttonLayoutProperty->GetCalcLayoutConstraint()->selfIdealSize.value();
        EXPECT_EQ(calcSize.Width().value(), CalcLength(newWidth - PRESS_INTERVAL.ConvertToPx()));
        EXPECT_EQ(calcSize.Height().value(), CalcLength(0.0f));
        auto buttonConfirmRenderContext = buttonNode->GetRenderContext();
        EXPECT_EQ(buttonConfirmRenderContext->GetBackgroundColorValue(), Color::TRANSPARENT);
    }
}

/**
 * @tc.name: TimePickerRowPattern002
 * @tc.desc: Test TimePickerRowPattern OnModifyDone while HasTitleNode
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerRowPattern002, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    auto titleNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    timePickerRowPattern->titleId_ = titleNodeId;
    auto* stack = ViewStackProcessor::GetInstance();
    auto textFrameNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXT_ETS_TAG, titleNodeId, []() { return AceType::MakeRefPtr<TextPattern>(); });
    stack->Push(textFrameNode);
    PickerDate pickerDate(DEFAULT_YEAR, DEFAULT_MONTH, DEFAULT_DAY);
    timePickerRowPattern->SetDialogTitleDate(pickerDate);

    timePickerRowPattern->OnModifyDone();
    auto textTitleNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXT_ETS_TAG, titleNodeId, []() { return AceType::MakeRefPtr<TextPattern>(); });
    auto textLayoutProperty = textTitleNode->GetLayoutProperty<TextLayoutProperty>();
}

/**
 * @tc.name: TimePickerRowPattern003
 * @tc.desc: Test TimePickerRowPattern CreateAmPmNode while AmPmButtonIdeaSize > 0
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerRowPattern003, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    auto children = frameNode->GetChildren();
    for (const auto& child : children) {
        auto buttonNode = AceType::DynamicCast<FrameNode>(child->GetFirstChild());
        buttonNode->GetGeometryNode()->frame_.rect_.SetWidth(EXTRA_WIDTH);
    }
    timePickerRowPattern->SetHour24(false);
    std::optional<int32_t> amPmId;
    timePickerRowPattern->amPmId_ = amPmId;

    timePickerRowPattern->CreateAmPmNode();
    EXPECT_GT(timePickerRowPattern->SetAmPmButtonIdeaSize(), 0);
}

/**
 * @tc.name: TimePickerRowPattern004
 * @tc.desc: Test TimePickerRowPattern GetCurrentTime using 12-hour system
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerRowPattern004, TestSize.Level1)
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

    amPmPickerColumnPattern->SetCurrentIndex(0);
    hourPickerColumnPattern->SetCurrentIndex(AM_PM_HOUR_12 - 1);
    EXPECT_EQ(timePickerRowPattern->GetCurrentTime().GetHour(), 0);
    EXPECT_EQ(timePickerRowPattern->GetCurrentTime().GetMinute(), minutePickerColumnPattern->GetCurrentIndex());

    hourPickerColumnPattern->SetCurrentIndex(AM_PM_HOUR_12 - 2);
    EXPECT_EQ(timePickerRowPattern->GetCurrentTime().GetHour(), AM_PM_HOUR_12 - 1);

    amPmPickerColumnPattern->SetCurrentIndex(1);
    EXPECT_EQ(timePickerRowPattern->GetCurrentTime().GetHour(), AM_PM_HOUR_12 * 2 - 1);

    hourPickerColumnPattern->SetCurrentIndex(AM_PM_HOUR_12 - 1);
    EXPECT_EQ(timePickerRowPattern->GetCurrentTime().GetHour(), AM_PM_HOUR_12);
}

/**
 * @tc.name: TimePickerRowPattern005
 * @tc.desc: Test TimePickerRowPattern HandleColumnChange
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerRowPattern005, TestSize.Level1)
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
    amPmPickerColumnPattern->SetCurrentIndex(0);
    auto tag = allChildNode["hour"].Upgrade();
    ASSERT_NE(tag, nullptr);
    timePickerRowPattern->HandleColumnChange(tag, true, 11, true);
    std::vector<RefPtr<FrameNode>> tags;
    timePickerRowPattern->OnDataLinking(tag, true, 11, tags);
    EXPECT_EQ(tags.size(), 1);
}

/**
 * @tc.name: TimePickerRowPattern006
 * @tc.desc: Test TimePickerRowPattern HandleHourColumnBuilding while AM PM column is null
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerRowPattern006, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    timePickerRowPattern->SetHour24(false);
    frameNode->RemoveChildAtIndex(0);
    timePickerRowPattern->HandleHourColumnBuilding();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    EXPECT_EQ(allChildNode["amPm"].Upgrade(), nullptr);
}

/**
 * @tc.name: TimePickerRowPattern007
 * @tc.desc: Test TimePickerRowPattern GetAllChildNode while using 24-hour system but has 3 child node
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerRowPattern007, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    timePickerRowPattern->SetHour24(true);
    EXPECT_EQ(frameNode->GetChildren().size(), CHILD_WITH_AMPM_SIZE);
    timePickerRowPattern->GetAllChildNode();
    EXPECT_EQ(frameNode->children_.size(), CHILD_WITH_AMPM_SIZE);
    EXPECT_TRUE(timePickerRowPattern->amPmId_.has_value());
}

/**
 * @tc.name: TimePickerRowPattern008
 * @tc.desc: Test TimePickerRowPattern HandleHour12Change
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerRowPattern008, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    std::vector<RefPtr<FrameNode>> tags;
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto amPm = allChildNode["amPm"].Upgrade();
    ASSERT_NE(amPm, nullptr);
    auto amPmPickerColumnPattern = amPm->GetPattern<TimePickerColumnPattern>();

    amPmPickerColumnPattern->SetCurrentIndex(0);
    timePickerRowPattern->HandleHour12Change(true, 11, tags);
    EXPECT_EQ(amPmPickerColumnPattern->GetCurrentIndex(), 1);
    EXPECT_EQ(tags.size(), 1);

    timePickerRowPattern->HandleHour12Change(true, 11, tags);
    EXPECT_EQ(amPmPickerColumnPattern->GetCurrentIndex(), 0);
    EXPECT_EQ(tags.size(), 2);

    timePickerRowPattern->HandleHour12Change(false, 10, tags);
    EXPECT_EQ(amPmPickerColumnPattern->GetCurrentIndex(), 1);
    EXPECT_EQ(tags.size(), 3);

    timePickerRowPattern->HandleHour12Change(false, 10, tags);
    EXPECT_EQ(amPmPickerColumnPattern->GetCurrentIndex(), 0);
    EXPECT_EQ(tags.size(), 4);
}

/**
 * @tc.name: TimePickerRowPattern009
 * @tc.desc: Test TimePickerRowPattern GetAmPmHour
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerRowPattern009, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    EXPECT_EQ(timePickerRowPattern->GetAmPmHour(0), AM_PM_HOUR_12);
    EXPECT_EQ(timePickerRowPattern->GetAmPmHour(AM_PM_HOUR_12), AM_PM_HOUR_12);
}

/**
 * @tc.name: TimePickerRowPattern010
 * @tc.desc: Test TimePickerRowPattern GetAmPmFormatString and AddZeroPrefix
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerRowPattern010, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    timePickerRowPattern->vecAmPm_.emplace_back("AM");
    timePickerRowPattern->vecAmPm_.emplace_back("PM");
    EXPECT_EQ(timePickerRowPattern->GetAmFormatString(), "AM");
    EXPECT_EQ(timePickerRowPattern->GetPmFormatString(), "PM");
    EXPECT_EQ(timePickerRowPattern->AddZeroPrefix("5"), "05");
}

/**
 * @tc.name: TimePickerRowPattern011
 * @tc.desc: Test TimePickerRowPattern InitOnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerRowPattern011, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    auto eventHub = frameNode->GetOrCreateEventHub<EventHub>();
    auto focusHub = eventHub->GetOrCreateFocusHub();
    timePickerRowPattern->InitOnKeyEvent(focusHub);
    auto getInnerFocusRectFunc = focusHub->getInnerFocusRectFunc_;

    KeyEvent keyEvent;
    keyEvent.action = KeyAction::UNKNOWN;
    keyEvent.code = KeyCode::KEY_DPAD_UP;
    EXPECT_FALSE(focusHub->ProcessOnKeyEventInternal(keyEvent));

    keyEvent.action = KeyAction::DOWN;
    auto stackChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(timePickerRowPattern->focusKeyID_));
    ASSERT_NE(stackChild, nullptr);
    auto blendChild = AceType::DynamicCast<FrameNode>(stackChild->GetLastChild());
    ASSERT_NE(blendChild, nullptr);
    auto pickerChild = AceType::DynamicCast<FrameNode>(blendChild->GetLastChild());
    ASSERT_NE(pickerChild, nullptr);
    auto pattern = pickerChild->GetPattern<TimePickerColumnPattern>();
    ASSERT_NE(pattern, nullptr);
    timePickerRowPattern->options_[pickerChild].clear();
    EXPECT_TRUE(focusHub->ProcessOnKeyEventInternal(keyEvent));

    timePickerRowPattern->options_[pickerChild][0] = "AM";
    timePickerRowPattern->options_[pickerChild][1] = "PM";
    auto currentIndex = pattern->GetCurrentIndex();
    auto totalOptionCount = timePickerRowPattern->GetOptionCount(pickerChild);
    EXPECT_TRUE(focusHub->ProcessOnKeyEventInternal(keyEvent));
    EXPECT_EQ(pattern->GetCurrentIndex(), (totalOptionCount + currentIndex - 1) % totalOptionCount);

    keyEvent.code = KeyCode::KEY_DPAD_DOWN;
    currentIndex = pattern->GetCurrentIndex();
    totalOptionCount = timePickerRowPattern->GetOptionCount(pickerChild);
    EXPECT_TRUE(focusHub->ProcessOnKeyEventInternal(keyEvent));
    EXPECT_EQ(pattern->GetCurrentIndex(), (totalOptionCount + currentIndex + 1) % totalOptionCount);

    keyEvent.code = KeyCode::KEY_MOVE_HOME;
    currentIndex = pattern->GetCurrentIndex();
    totalOptionCount = timePickerRowPattern->GetOptionCount(pickerChild);
    EXPECT_TRUE(focusHub->ProcessOnKeyEventInternal(keyEvent));
    EXPECT_EQ(pattern->GetCurrentIndex(), 0);

    keyEvent.code = KeyCode::KEY_MOVE_END;
    currentIndex = pattern->GetCurrentIndex();
    totalOptionCount = timePickerRowPattern->GetOptionCount(pickerChild);
    EXPECT_TRUE(focusHub->ProcessOnKeyEventInternal(keyEvent));
    EXPECT_EQ(pattern->GetCurrentIndex(), (totalOptionCount - 1));

    keyEvent.code = KeyCode::KEY_DPAD_RIGHT;
    EXPECT_TRUE(focusHub->ProcessOnKeyEventInternal(keyEvent));
    EXPECT_EQ(timePickerRowPattern->focusKeyID_, 1);

    keyEvent.code = KeyCode::KEY_DPAD_LEFT;
    EXPECT_TRUE(focusHub->ProcessOnKeyEventInternal(keyEvent));
    EXPECT_EQ(timePickerRowPattern->focusKeyID_, 0);

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto pickerTheme = AceType::MakeRefPtr<PickerTheme>();
    ASSERT_NE(pickerTheme, nullptr);
    pickerTheme->dividerSpacing_ = Dimension(OFFSET_X);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(pickerTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(pickerTheme));
    auto dividerSpacing = pickerTheme->GetDividerSpacing().ConvertToPx();

    // default focusWidth < columnWidth, focusWidth = columnWidth
    RoundRect paintRect;
    getInnerFocusRectFunc(paintRect);
    auto rect = paintRect.GetRect();
    Dimension offset = 2.0_vp;
    Dimension focusLineWidth = 1.5_vp;
    EXPECT_EQ(rect.GetX(), offset.ConvertToPx() + focusLineWidth.ConvertToPx());

    auto centerY =
        (frameNode->GetGeometryNode()->GetFrameSize().Height() - dividerSpacing) / 2 + offset.ConvertToPx() +
        focusLineWidth.ConvertToPx();
    EXPECT_EQ(rect.GetY(), centerY);

    auto expectWidth = pickerChild->GetGeometryNode()->GetFrameSize().Width() - offset.ConvertToPx() * 2 -
        focusLineWidth.ConvertToPx() * 2;
    EXPECT_EQ(rect.Width(), expectWidth);

    EXPECT_EQ(rect.Height(), dividerSpacing - offset.ConvertToPx() * 2 - focusLineWidth.ConvertToPx() * 2);

    EXPECT_EQ(paintRect.GetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS).x,
        static_cast<RSScalar>(PRESS_RADIUS.ConvertToPx()));
    EXPECT_EQ(paintRect.GetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS).y,
        static_cast<RSScalar>(PRESS_RADIUS.ConvertToPx()));
    EXPECT_EQ(paintRect.GetCornerRadius(RoundRect::CornerPos::TOP_RIGHT_POS).x,
        static_cast<RSScalar>(PRESS_RADIUS.ConvertToPx()));
    EXPECT_EQ(paintRect.GetCornerRadius(RoundRect::CornerPos::TOP_RIGHT_POS).y,
        static_cast<RSScalar>(PRESS_RADIUS.ConvertToPx()));
    EXPECT_EQ(paintRect.GetCornerRadius(RoundRect::CornerPos::BOTTOM_LEFT_POS).x,
        static_cast<RSScalar>(PRESS_RADIUS.ConvertToPx()));
    EXPECT_EQ(paintRect.GetCornerRadius(RoundRect::CornerPos::BOTTOM_LEFT_POS).y,
        static_cast<RSScalar>(PRESS_RADIUS.ConvertToPx()));
    EXPECT_EQ(paintRect.GetCornerRadius(RoundRect::CornerPos::BOTTOM_RIGHT_POS).x,
        static_cast<RSScalar>(PRESS_RADIUS.ConvertToPx()));
    EXPECT_EQ(paintRect.GetCornerRadius(RoundRect::CornerPos::BOTTOM_RIGHT_POS).y,
        static_cast<RSScalar>(PRESS_RADIUS.ConvertToPx()));

    // default focusWidth < columnWidth
    pickerChild->GetGeometryNode()->frame_.rect_.SetWidth(EXTRA_WIDTH);
    RoundRect paintRect2;
    timePickerRowPattern->GetInnerFocusPaintRect(paintRect2);
    auto rect2 = paintRect2.GetRect();
    
    EXPECT_EQ(rect2.GetX(), offset.ConvertToPx() + focusLineWidth.ConvertToPx());

    auto expectWidth2 = pickerChild->GetGeometryNode()->GetFrameSize().Width() - offset.ConvertToPx() * 2 -
        focusLineWidth.ConvertToPx() * 2;
    EXPECT_EQ(rect2.Width(), expectWidth2);
}

/**
 * @tc.name: TimePickerRowPattern012
 * @tc.desc: Test TimePickerRowPattern OnKeyEvent and HandleDirectionKey false
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerRowPattern012, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    KeyEvent keyEvent;
    keyEvent.action = KeyAction::DOWN;
    keyEvent.code = KeyCode::KEY_DPAD_CENTER;
    EXPECT_FALSE(timePickerRowPattern->OnKeyEvent(keyEvent));
    EXPECT_FALSE(timePickerRowPattern->HandleDirectionKey(KeyCode::KEY_DPAD_CENTER));
}

/**
 * @tc.name: TimePickerRowPattern013
 * @tc.desc: Test TimePickerRowPattern SetFocusDisable and SetFocusEnable
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerRowPattern013, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    auto host = timePickerRowPattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto focusHub = host->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    timePickerRowPattern->SetFocusDisable();
    timePickerRowPattern->SetFocusEnable();
}

/**
 * @tc.name: TimePickerRowPattern014
 * @tc.desc: Test OnLanguageConfigurationUpdate
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerRowPattern014, TestSize.Level1)
{
    const std::string language = "en";
    const std::string countryOrRegion = "US";
    std::string nodeInfo = "";
    const std::string script = "Latn";
    const std::string keywordsAndValues = "";
    auto dialogTheme = MockPipelineContext::GetCurrent()->GetTheme<DialogTheme>();
    auto contentColumn = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto timePickerNode = FrameNode::GetOrCreateFrameNode(
        V2::TIME_PICKER_ETS_TAG, 1, []() { return AceType::MakeRefPtr<TimePickerRowPattern>(); });
    auto timePickerPattern = timePickerNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerPattern, nullptr);
    timePickerNode->MountToParent(contentColumn);
    auto buttonConfirmNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NG::ButtonPattern>(); });
    auto timeConfirmNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(buttonConfirmNode, nullptr);
    ASSERT_NE(timeConfirmNode, nullptr);
    timeConfirmNode->MountToParent(buttonConfirmNode);
    timePickerPattern->SetConfirmNode(buttonConfirmNode);
    auto buttonCancelNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(buttonCancelNode, nullptr);
    auto timeCancelNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(timeCancelNode, nullptr);
    timeCancelNode->MountToParent(buttonCancelNode);
    timePickerPattern->SetCancelNode(buttonCancelNode);
    timePickerPattern->OnLanguageConfigurationUpdate();
    auto cancelNode = dialogTheme->GetCancelText();
    EXPECT_EQ(cancelNode, nodeInfo);
}

/**
 * @tc.name: TimePickerRowPattern015
 * @tc.desc: Test Column Pattern Init Haptic Controller
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerRowPattern015, TestSize.Level1)
{
    /**
     * @tc.step: step1. create row pattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    EXPECT_NE(timePickerRowPattern, nullptr);
    /**
     * @tc.steps: step2. call SetIsEnableHaptic.
     * @tc.expected: isHapticChanged is false.
     */
    bool value = true;
    timePickerRowPattern->SetIsEnableHaptic(value);
    EXPECT_FALSE(timePickerRowPattern->isHapticChanged_);
    /**
     * @tc.steps: step3. call SetIsEnableHaptic.
     * @tc.expected: isHapticChanged is true.
     */
    value = false;
    timePickerRowPattern->SetIsEnableHaptic(value);
    bool isEnableHaptic = timePickerRowPattern->GetIsEnableHaptic();
    EXPECT_FALSE(isEnableHaptic);
    EXPECT_TRUE(timePickerRowPattern->isHapticChanged_);
}

/**
 * @tc.name: TimePickerRowPattern016
 * @tc.desc: Test OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerRowPattern016, TestSize.Level1)
{
    /**
     * @tc.step: step1. create row pattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    EXPECT_NE(timePickerRowPattern, nullptr);
    /**
     * @tc.steps: step2. call OnModifyDone.
     * @tc.expected: set isHapticChanged is true and isForceUpdate_ is false and isFiredTimeChange_ is false.
     */
    timePickerRowPattern->isFiredTimeChange_ = true;
    timePickerRowPattern->isForceUpdate_ = false;
    timePickerRowPattern->isFiredTimeChange_ = false;
    timePickerRowPattern->OnModifyDone();
    EXPECT_FALSE(timePickerRowPattern->isFiredTimeChange_);
    /**
     * @tc.steps: step3. call SetIsEnableHaptic.
     * @tc.expected: set isHapticChanged is true and isForceUpdate_ is true and isFiredTimeChange_ is false.
     */
    timePickerRowPattern->isFiredTimeChange_ = true;
    timePickerRowPattern->isForceUpdate_ = true;
    timePickerRowPattern->isFiredTimeChange_ = false;
    timePickerRowPattern->OnModifyDone();
    EXPECT_FALSE(timePickerRowPattern->isFiredTimeChange_);
    /**
     * @tc.steps: step4. call SetIsEnableHaptic.
     * @tc.expected: set isHapticChanged is true and isForceUpdate_ is false and isFiredTimeChange_ is true.
     */
    timePickerRowPattern->isFiredTimeChange_ = true;
    timePickerRowPattern->isForceUpdate_ = false;
    timePickerRowPattern->isFiredTimeChange_ = true;
    timePickerRowPattern->OnModifyDone();
    EXPECT_FALSE(timePickerRowPattern->isFiredTimeChange_);
}

/**
 * @tc.name: TimePickerRowPattern017
 * @tc.desc: Test OnModifyDone2
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerRowPattern017, TestSize.Level1)
{
    /**
     * @tc.step: step1. create row pattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    EXPECT_NE(timePickerRowPattern, nullptr);
    /**
     * @tc.steps: step2. call OnModifyDone.
     * @tc.expected: set isHapticChanged is false and isForceUpdate_ is true and isFiredTimeChange_ is true.
     */
    timePickerRowPattern->isFiredTimeChange_ = false;
    timePickerRowPattern->isForceUpdate_ = true;
    timePickerRowPattern->isFiredTimeChange_ = true;
    timePickerRowPattern->OnModifyDone();
    EXPECT_TRUE(timePickerRowPattern->isFiredTimeChange_);
    /**
     * @tc.steps: step2. call OnModifyDone.
     * @tc.expected: set isHapticChanged is false and isForceUpdate_ is false and isFiredTimeChange_ is false.
     */
    timePickerRowPattern->isFiredTimeChange_ = false;
    timePickerRowPattern->isForceUpdate_ = false;
    timePickerRowPattern->isFiredTimeChange_ = false;
    timePickerRowPattern->OnModifyDone();
    EXPECT_FALSE(timePickerRowPattern->isFiredTimeChange_);
    /**
     * @tc.steps: step2. call OnModifyDone.
     * @tc.expected: set isHapticChanged is true and isForceUpdate_ is true and isFiredTimeChange_ is true.
     */
    timePickerRowPattern->isFiredTimeChange_ = true;
    timePickerRowPattern->isForceUpdate_ = true;
    timePickerRowPattern->isFiredTimeChange_ = true;
    timePickerRowPattern->OnModifyDone();
    EXPECT_TRUE(timePickerRowPattern->isFiredTimeChange_);
}

/**
 * @tc.name: TimePickerRowPattern018
 * @tc.desc: Test Init Disabled
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerRowPattern018, TestSize.Level1)
{
    /**
     * @tc.step: step1. create row pattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    EXPECT_NE(timePickerRowPattern, nullptr);
    /**
     * @tc.steps: step2. call InitDisabled.
     * @tc.expected: set eventHub is disenabled.
     */
    auto eventHub = frameNode->GetOrCreateEventHub<EventHub>();
    eventHub->enabled_ = false;
    timePickerRowPattern->InitDisabled();
    bool res = eventHub->IsEnabled();
    EXPECT_FALSE(res);
}

/**
 * @tc.name: TimePickerRowPattern019
 * @tc.desc: Test mount second Node
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerRowPattern019, TestSize.Level1)
{
    /**
     * @tc.step: step1. create row pattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    EXPECT_NE(timePickerRowPattern, nullptr);
    /**
     * @tc.steps: step2. call MountSecondNode.
     * @tc.expected: set HasAmPmNode is true and language_ is not "ug".
     */
    std::optional<int32_t> temp;
    temp.emplace(100);
    timePickerRowPattern->secondId_ = temp;
    bool hasValue = timePickerRowPattern->secondId_.has_value();
    std::string tag = "testNode";
    int32_t nodeId = 212;
    RefPtr<FrameNode> stackSecondNode = FrameNode::CreateFrameNode(tag, nodeId, timePickerRowPattern);
    timePickerRowPattern->amPmTimeOrder_ = "01";
    timePickerRowPattern->MountSecondNode(stackSecondNode);
    bool res = timePickerRowPattern->HasAmPmNode();
    EXPECT_TRUE(hasValue);
    EXPECT_TRUE(res);
    /**
     * @tc.steps: step2. call RemoveSecondNode.
     * @tc.expected: set HasAmPmNode is true and language_ is "ug".
     */
    timePickerRowPattern->amPmTimeOrder_ = "02";
    timePickerRowPattern->language_ = "ug";
    timePickerRowPattern->MountSecondNode(stackSecondNode);
    res = timePickerRowPattern->HasAmPmNode();
    EXPECT_TRUE(res);
}

/**
 * @tc.name: TimePickerRowPattern020
 * @tc.desc: Test mount second Node2
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerRowPattern020, TestSize.Level1)
{
    /**
     * @tc.step: step1. create row pattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    EXPECT_NE(timePickerRowPattern, nullptr);
    /**
     * @tc.steps: step2. call MountSecondNode.
     * @tc.expected: set HasAmPmNode is false and language_ is "ug".
     */
    timePickerRowPattern->amPmId_ = std::nullopt;
    bool hasValue = timePickerRowPattern->amPmId_.has_value();
    bool res = timePickerRowPattern->HasAmPmNode();

    std::string tag = "testNode";
    int32_t nodeId = 212;
    RefPtr<FrameNode> stackSecondNode = FrameNode::CreateFrameNode(tag, nodeId, timePickerRowPattern);
    timePickerRowPattern->amPmTimeOrder_ = "02";
    timePickerRowPattern->language_ = "ug";
    timePickerRowPattern->MountSecondNode(stackSecondNode);
    EXPECT_FALSE(hasValue);
    /**
     * @tc.steps: step2. call MountSecondNode.
     * @tc.expected: set HasAmPmNode is false and language_ is "ug".
     */
    timePickerRowPattern->language_ = "test";
    timePickerRowPattern->MountSecondNode(stackSecondNode);
    EXPECT_FALSE(res);
}

/**
 * @tc.name: TimePickerRowPattern021
 * @tc.desc: Test remove second Node
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerRowPattern021, TestSize.Level1)
{
    /**
     * @tc.step: step1. create row pattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    EXPECT_NE(timePickerRowPattern, nullptr);
    /**
     * @tc.steps: step2. call RemoveSecondNode.
     * @tc.expected: set HasAmPmNode is false and language_ is "ug".
     */
    timePickerRowPattern->amPmId_ = std::nullopt;
    bool hasValue = timePickerRowPattern->amPmId_.has_value();
    bool res = timePickerRowPattern->HasAmPmNode();
    timePickerRowPattern->amPmTimeOrder_ = "02";
    timePickerRowPattern->language_ = "ug";
    EXPECT_FALSE(hasValue);
    /**
     * @tc.steps: step2. call RemoveSecondNode.
     * @tc.expected: set language_ is not "ug".
     */
    timePickerRowPattern->RemoveSecondNode();
    timePickerRowPattern->language_ = "test";
    timePickerRowPattern->RemoveSecondNode();
    EXPECT_FALSE(res);
}

/**
 * @tc.name: TimePickerRowPattern022
 * @tc.desc: Test remove second Node
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerRowPattern022, TestSize.Level1)
{
    /**
     * @tc.step: step1. create row pattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    EXPECT_NE(timePickerRowPattern, nullptr);
    /**
     * @tc.steps: step2. call RemoveSecondNode.
     * @tc.expected: set HasAmPmNode is true and language_ is not "ug".
     */
    std::optional<int32_t> temp;
    temp.emplace(100);
    timePickerRowPattern->secondId_ = temp;
    bool hasValue = timePickerRowPattern->amPmId_.has_value();
    bool res = timePickerRowPattern->HasAmPmNode();
    timePickerRowPattern->amPmTimeOrder_ = "01";
    timePickerRowPattern->RemoveSecondNode();
    EXPECT_TRUE(hasValue);
    /**
     * @tc.steps: step2. call RemoveSecondNode.
     * @tc.expected: set language_ is "ug".
     */
    timePickerRowPattern->amPmTimeOrder_ = "02";
    timePickerRowPattern->language_ = "ug";
    timePickerRowPattern->RemoveSecondNode();
    EXPECT_TRUE(res);
}

/**
 * @tc.name: TimePickerRowPattern023
 * @tc.desc: On font Configuration Update
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerRowPattern023, TestSize.Level1)
{
    /**
     * @tc.step: step1. create row pattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    EXPECT_NE(timePickerRowPattern, nullptr);
    /**
     * @tc.steps: step2. call OnFontConfigurationUpdate.
     * @tc.expected: set close dialog event.
     */
    TimePickerSettingData settingData;
    settingData.properties.disappearTextStyle_.textColor = Color::RED;
    settingData.properties.disappearTextStyle_.fontSize = Dimension(0);
    settingData.properties.disappearTextStyle_.fontWeight = Ace::FontWeight::BOLD;
    settingData.isUseMilitaryTime = false;

    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(1, 1, 1);
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;

    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode = TimePickerDialogView::Show(
        dialogProperties, settingData, buttonInfos, timePickerProperty, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
    std::function<void()> closeDialogEvent = [weak = WeakPtr<FrameNode>(dialogNode), timePickerRowPattern]() {
        auto dialogNode = weak.Upgrade();
        auto pipeline = dialogNode->GetContext();
        auto overlayManager = pipeline->GetOverlayManager();
        overlayManager->CloseDialog(dialogNode);
        timePickerRowPattern->SetIsShowInDialog(false);
    };
    timePickerRowPattern->updateFontConfigurationEvent(closeDialogEvent);
    timePickerRowPattern->OnFontConfigurationUpdate();
    EXPECT_NE(closeDialogEvent, nullptr);
}

/**
 * @tc.name: TimePickerRowPattern024
 * @tc.desc: Test UpdateButtonMargin.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerRowPattern024, TestSize.Level1)
{
    /**
     * @tc.step: step1. create row pattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    EXPECT_NE(timePickerRowPattern, nullptr);
    /**
     * @tc.steps: step2. call UpdateButtonMargin.
     * @tc.expected: set api version is 10.
     */
    int32_t setApiVersion = 10;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t currApiVersion = MockContainer::Current()->GetApiTargetVersion();
    auto buttonCancelNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_NE(buttonCancelNode, nullptr);
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    timePickerRowPattern->UpdateButtonMargin(buttonCancelNode, dialogTheme, true);
    EXPECT_EQ(currApiVersion, setApiVersion);
    /**
     * @tc.steps: step3. call UpdateButtonMargin.
     * @tc.expected: set api version is 16.
     */
    setApiVersion = 16;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    currApiVersion = MockContainer::Current()->GetApiTargetVersion();
    timePickerRowPattern->UpdateButtonMargin(buttonCancelNode, dialogTheme, true);
    EXPECT_EQ(currApiVersion, setApiVersion);
}

/**
 * @tc.name: TimePickerRowPattern025
 * @tc.desc: Test OnLanguageConfigurationUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerRowPattern025, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    EXPECT_NE(timePickerRowPattern, nullptr);
    /**
     * @tc.steps: step1. call OnLanguageConfigurationUpdate.
     * @tc.expected: set timeOrder is "01" and isAmPmTimeOrderUpdate_ is true.
     */
    bool value = false;
    timePickerRowPattern->SetHour24(value);
    std::string timeOrder = "01";
    timePickerRowPattern->amPmTimeOrder_ = timeOrder;
    timePickerRowPattern->isAmPmTimeOrderUpdate_ = true;
    timePickerRowPattern->OnLanguageConfigurationUpdate();
    bool isHour24 = timePickerRowPattern->GetHour24();
    EXPECT_FALSE(isHour24);
    /**
     * @tc.steps: step2. call OnLanguageConfigurationUpdate.
     * @tc.expected: set timeOrder is "01" and isAmPmTimeOrderUpdate_ is false.
     */
    timePickerRowPattern->amPmTimeOrder_ = timeOrder;
    timePickerRowPattern->isAmPmTimeOrderUpdate_ = value;
    EXPECT_FALSE(timePickerRowPattern->isAmPmTimeOrderUpdate_);
    timePickerRowPattern->OnLanguageConfigurationUpdate();
    EXPECT_TRUE(timePickerRowPattern->isAmPmTimeOrderUpdate_);
    /**
     * @tc.steps: step3. call OnLanguageConfigurationUpdate.
     * @tc.expected: set timeOrder is "10" and isAmPmTimeOrderUpdate_ is true.
     */
    timeOrder = "10";
    timePickerRowPattern->amPmTimeOrder_ = timeOrder;
    EXPECT_EQ(timePickerRowPattern->amPmTimeOrder_, timeOrder);
    timePickerRowPattern->isAmPmTimeOrderUpdate_ = true;
    timePickerRowPattern->OnLanguageConfigurationUpdate();
    EXPECT_NE(timePickerRowPattern->amPmTimeOrder_, timeOrder);
    /**
     * @tc.steps: step4. call OnLanguageConfigurationUpdate.
     * @tc.expected: set timeOrder is "10" and isAmPmTimeOrderUpdate_ is false.
     */
    timePickerRowPattern->amPmTimeOrder_ = timeOrder;
    timePickerRowPattern->isAmPmTimeOrderUpdate_ = value;
    EXPECT_FALSE(timePickerRowPattern->isAmPmTimeOrderUpdate_);
    timePickerRowPattern->OnLanguageConfigurationUpdate();
    EXPECT_TRUE(timePickerRowPattern->isAmPmTimeOrderUpdate_);
}

/**
 * @tc.name: TimePickerRowPattern026
 * @tc.desc: Test UpdateNodePositionForUg.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerRowPattern026, TestSize.Level1)
{
    /**
     * @tc.step: step1. create row pattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    EXPECT_NE(timePickerRowPattern, nullptr);
    /**
     * @tc.steps: step2. call OnLanguageConfigurationUpdate.
     * @tc.expected: set language is "ug" and hasSecond is true.
     */
    std::string language = "ug";
    bool value = true;
    timePickerRowPattern->isPreLanguageUg_ = value;
    timePickerRowPattern->language_ = language;
    timePickerRowPattern->isAmPmTimeOrderUpdate_ = value;
    timePickerRowPattern->SetHasSecond(value);
    bool hasSecond = timePickerRowPattern->GetHasSecond();
    timePickerRowPattern->UpdateNodePositionForUg();
    EXPECT_TRUE(hasSecond);
    /**
     * @tc.steps: step3. call OnLanguageConfigurationUpdate.
     * @tc.expected: set language is "ug" and hasSecond is false.
     */
    timePickerRowPattern->SetHasSecond(false);
    hasSecond = timePickerRowPattern->GetHasSecond();
    timePickerRowPattern->UpdateNodePositionForUg();
    EXPECT_FALSE(hasSecond);
    /**
     * @tc.steps: step3. call OnLanguageConfigurationUpdate.
     * @tc.expected: set isAmPmTimeOrderUpdate_ is false and hasSecond is false.
     */
    timePickerRowPattern->isAmPmTimeOrderUpdate_ = false;
    timePickerRowPattern->SetHasSecond(false);
    timePickerRowPattern->UpdateNodePositionForUg();
    EXPECT_FALSE(timePickerRowPattern->isAmPmTimeOrderUpdate_);
    /**
     * @tc.steps: step3. call OnLanguageConfigurationUpdate.
     * @tc.expected: set isAmPmTimeOrderUpdate_ is false and hasSecond is true.
     */
    timePickerRowPattern->SetHasSecond(value);
    hasSecond = timePickerRowPattern->GetHasSecond();
    timePickerRowPattern->UpdateNodePositionForUg();
    EXPECT_TRUE(hasSecond);
}

/**
 * @tc.name: TimePickerRowPattern027
 * @tc.desc: Test UpdateButtonMargin.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerRowPattern027, TestSize.Level1)
{
    /**
     * @tc.step: step1. create row pattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    EXPECT_NE(timePickerRowPattern, nullptr);
    /**
     * @tc.steps: step2. call UpdateButtonMargin.
     * @tc.expected: set api version is 11.
     */
    int32_t setApiVersion = 11;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t currApiVersion = MockContainer::Current()->GetApiTargetVersion();
    auto buttonCancelNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_NE(buttonCancelNode, nullptr);
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    timePickerRowPattern->UpdateButtonMargin(buttonCancelNode, dialogTheme, false);
    EXPECT_EQ(currApiVersion, setApiVersion);
    /**
     * @tc.steps: step3. call UpdateButtonMargin.
     * @tc.expected: set api version is 16.
     */
    setApiVersion = 16;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    currApiVersion = MockContainer::Current()->GetApiTargetVersion();
    timePickerRowPattern->UpdateButtonMargin(buttonCancelNode, dialogTheme, false);
    EXPECT_EQ(currApiVersion, setApiVersion);
}

/**
 * @tc.name: TimePickerRowPattern028
 * @tc.desc: Test CalcLeftTotalColumnWidth.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerRowPattern028, TestSize.Level1)
{
    /**
     * @tc.step: step1. create row pattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    EXPECT_NE(timePickerRowPattern, nullptr);
    /**
     * @tc.steps: step2. call CalcLeftTotalColumnWidth.
     * @tc.expected: set the page layout mode is from right to left.
     */
    auto pipeline = PipelineBase::GetCurrentContextSafely();
    EXPECT_NE(pipeline, nullptr);
    bool isRtl = true;
    pipeline->SetIsRightToLeft(isRtl);
    float leftTotalColumnWidth = 50.0f;
    float childSize = 10.0f;
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    bool res = AceApplicationInfo::GetInstance().IsRightToLeft();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    columnNode_ = allChildNode["minute"].Upgrade();
    EXPECT_NE(columnNode_, nullptr);
    timePickerRowPattern->CalcLeftTotalColumnWidth(columnNode_, leftTotalColumnWidth, childSize);
    EXPECT_TRUE(res);
}

/**
 * @tc.name: TimePickerRowPattern029
 * @tc.desc: Test GetSecondFormatString.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerRowPattern029, TestSize.Level1)
{
    /**
     * @tc.step: step1. create row pattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    EXPECT_NE(timePickerRowPattern, nullptr);
    /**
     * @tc.steps: step2. call GetSecondFormatString.
     * @tc.expected: set Api Version is 15.
     */
    int32_t setApiVersion = 15;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t currApiVersion = MockContainer::Current()->GetApiTargetVersion();
    uint32_t second = 12;
    timePickerRowPattern->GetSecondFormatString(second);
    EXPECT_GT(currApiVersion, second);
}

/**
 * @tc.name: TimePickerRowPattern030
 * @tc.desc: Test CheckFocusID.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerRowPattern030, TestSize.Level1)
{
    /**
     * @tc.step: step1. create row pattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    EXPECT_NE(timePickerRowPattern, nullptr);
    /**
     * @tc.steps: step2. call CheckFocusID.
     * @tc.expected: set focusKeyID is greater than childSize.
     */
    int32_t value = 5;
    timePickerRowPattern->SetCurrentFocusKeyID(value);
    int32_t focusKeyID = timePickerRowPattern->GetCurrentFocusKeyID();
    EXPECT_EQ(focusKeyID, value);
    int32_t childSize = 3;
    EXPECT_GT(focusKeyID, childSize - 1);
    timePickerRowPattern->CheckFocusID(childSize);
    focusKeyID = timePickerRowPattern->GetCurrentFocusKeyID();
    EXPECT_EQ(focusKeyID, childSize - 1);
    /**
     * @tc.steps: step3. call CheckFocusID.
     * @tc.expected: set focusKeyID is less than childSize.
     */
    value = -1;
    childSize = 8;
    timePickerRowPattern->SetCurrentFocusKeyID(value);
    bool res = timePickerRowPattern->CheckFocusID(childSize);
    focusKeyID = timePickerRowPattern->GetCurrentFocusKeyID();
    EXPECT_FALSE(res);
    EXPECT_EQ(focusKeyID, 0);
}

/**
 * @tc.name: TimePickerRowPattern031
 * @tc.desc: Test TimePickerRowPattern GetAllChildNode while using 24-hour system but has 3 child node
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerRowPattern031, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    TimePickerModelNG::SetHour24(frameNode, false);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    TimePickerModelNG::SetHour24(frameNode, true);
    EXPECT_EQ(frameNode->GetChildren().size(), CHILD_WITH_AMPM_SIZE);
    timePickerRowPattern->GetAllChildNode();
    EXPECT_EQ(frameNode->children_.size(), CHILD_WITH_AMPM_SIZE);
    EXPECT_TRUE(timePickerRowPattern->amPmId_.has_value());
}

/**
 * @tc.name: TimePickerFireChangeEventTest001
 * @tc.desc: Test SetSelectedDate.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerFireChangeEventTest001, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);

    auto changeEvent = [](const BaseEventInfo* info) { EXPECT_EQ(info->GetType(), "DatePickerChangeEvent"); };
    TimePickerModelNG::GetInstance()->SetChangeEvent(std::move(changeEvent));
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->FireChangeEvent(true);
}

/**
 * @tc.name: TimePickerHasSecond001
 * @tc.desc: Test TimePickerRowPattern SetHasSecond true.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerHasSecond001, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, true);
    TimePickerModelNG::GetInstance()->SetHour24(true);
    TimePickerModelNG::GetInstance()->SetSelectedTime(TIME_PICKED);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    std::vector<RefPtr<FrameNode>> tags;
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();

    auto hourColumn = allChildNode["hour"].Upgrade();
    ASSERT_NE(hourColumn, nullptr);
    auto hourColumnPattern = hourColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_NE(hourColumnPattern, nullptr);
    EXPECT_EQ(hourColumnPattern->GetCurrentIndex(), HOUR24_PICKED);

    auto minuteColumn = allChildNode["minute"].Upgrade();
    ASSERT_NE(minuteColumn, nullptr);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_NE(minuteColumnPattern, nullptr);
    EXPECT_EQ(minuteColumnPattern->GetCurrentIndex(), MINUTE_PICKED);

    auto secondColumn = allChildNode["second"].Upgrade();
    ASSERT_NE(secondColumn, nullptr);
    auto secondColumnPattern = secondColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_NE(secondColumnPattern, nullptr);
    EXPECT_EQ(secondColumnPattern->GetCurrentIndex(), SECOND_PICKED);
}

/**
 * @tc.name: TimePickerHasSecond002
 * @tc.desc: Test TimePickerRowPattern SetHasSecond false.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerHasSecond002, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, false);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    TimePickerModelNG::GetInstance()->SetSelectedTime(TIME_PICKED);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();

    auto amPmColumn = allChildNode["amPm"].Upgrade();
    ASSERT_NE(amPmColumn, nullptr);
    auto amPmColumnPattern = amPmColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_NE(amPmColumnPattern, nullptr);
    EXPECT_EQ(amPmColumnPattern->GetCurrentIndex(), AM_PM_PICKED);

    auto hourColumn = allChildNode["hour"].Upgrade();
    ASSERT_NE(hourColumn, nullptr);
    auto hourColumnPattern = hourColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_NE(hourColumnPattern, nullptr);
    EXPECT_EQ(hourColumnPattern->GetCurrentIndex(), HOUR_PICKED);

    auto minuteColumn = allChildNode["minute"].Upgrade();
    ASSERT_NE(minuteColumn, nullptr);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_NE(minuteColumnPattern, nullptr);
    EXPECT_EQ(minuteColumnPattern->GetCurrentIndex(), MINUTE_PICKED);

    auto secondColumn = allChildNode["second"].Upgrade();
    ASSERT_EQ(secondColumn, nullptr);
}

/**
 * @tc.name: TimePickerHasSecond003
 * @tc.desc: Test TimePickerRowPattern SetHasSecond true first then false.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerHasSecond003, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    /**
     * @tc.steps: step1. create FrameNode and SetHasSecond(true).
     */
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, true);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    TimePickerModelNG::GetInstance()->SetSelectedTime(TIME_PICKED);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    std::vector<RefPtr<FrameNode>> tags;
    /**
     * @tc.steps: step2. check the secondColumn has been created.
     */
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto secondColumn = allChildNode["second"].Upgrade();
    ASSERT_NE(secondColumn, nullptr);
    /**
     * @tc.steps: step3. SetHasSecond(false) then check the secondColumn has been deleted.
     */
    timePickerRowPattern->SetHasSecond(false);
    frameNode->MarkModifyDone();
    EXPECT_EQ(frameNode->GetChildren().size(), CHILD_WITH_AMPM_SIZE);
}

/**
 * @tc.name: TimePickerWheelMode001
 * @tc.desc: Test TimePickerRowPattern SetWheelModeEnabled false.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerWheelMode001, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    TimePickerModelNG::GetInstance()->SetWheelModeEnabled(false);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();

    auto hourColumn = allChildNode["hour"].Upgrade();
    ASSERT_NE(hourColumn, nullptr);
    auto hourColumnPattern = hourColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_NE(hourColumnPattern, nullptr);
    EXPECT_EQ(hourColumnPattern->GetWheelModeEnabled(), false);
}

/**
 * @tc.name: TimePickerWheelMode002
 * @tc.desc: Test TimePickerRowPattern default wheelmode.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerWheelMode002, TestSize.Level1)
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

    auto hourColumn = allChildNode["hour"].Upgrade();
    ASSERT_NE(hourColumn, nullptr);
    auto hourColumnPattern = hourColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_NE(hourColumnPattern, nullptr);
    EXPECT_EQ(hourColumnPattern->GetWheelModeEnabled(), true);
}

/**
 * @tc.name: TimePickerWheelMode003
 * @tc.desc: Test TimePickerColumnPattern UpdateColumnChildPosition while wheelmode off.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerWheelMode003, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    TimePickerModelNG::GetInstance()->SetWheelModeEnabled(false);
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
    minuteColumnPattern->SetCurrentIndex(0);
    minuteColumnPattern->UpdateColumnChildPosition(TOSS_DELTA);
    EXPECT_EQ(minuteColumnPattern->GetCurrentIndex(), 0);
}

/**
 * @tc.name: TimePickerWheelMode004
 * @tc.desc: Test TimePickerColumnPattern UpdateColumnChildPosition while wheelmode on.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerWheelMode004, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    TimePickerModelNG::GetInstance()->SetWheelModeEnabled(true);
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
    minuteColumnPattern->SetCurrentIndex(0);
    minuteColumnPattern->UpdateColumnChildPosition(TOSS_DELTA);
    EXPECT_EQ(minuteColumnPattern->GetCurrentIndex(), MINUTE_59);
}

/**
 * @tc.name: PerformActionTest001
 * @tc.desc: TimePicker accessibilityProperty PerformAction test ScrollForward and ScrollBackward.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, PerformActionTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create timePicker and initialize related properties.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto pickerFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(pickerFrameNode, nullptr);

    /**
     * @tc.steps: step2. Get timePickerColumn frameNode and pattern, set callback function.
     * @tc.expected: Related function is called.
     */
    auto timePickerRowPattern = pickerFrameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto minuteColumn = allChildNode["minute"].Upgrade();
    ASSERT_NE(minuteColumn, nullptr);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_NE(minuteColumnPattern, nullptr);
    auto options = minuteColumnPattern->GetOptions();
    options[minuteColumn] = 0;
    minuteColumnPattern->SetOptions(options);
    minuteColumnPattern->SetAccessibilityAction();

    /**
     * @tc.steps: step3. Get timePickerColumn accessibilityProperty to call callback function.
     * @tc.expected: Related function is called.
     */
    auto accessibilityProperty = minuteColumn->GetAccessibilityProperty<TimePickerColumnAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    /**
     * @tc.steps: step4. When timePickerColumn can move, call the callback function in timePickerColumn
     *                   accessibilityProperty.
     * @tc.expected: Related function is called.
     */
    EXPECT_TRUE(accessibilityProperty->ActActionScrollForward());
    EXPECT_TRUE(accessibilityProperty->ActActionScrollBackward());

    /**
     * @tc.steps: step5. When timePickerColumn can not move, call the callback function in timePickerColumn
     *                   accessibilityProperty.
     * @tc.expected: Related function is called.
     */
    options = minuteColumnPattern->GetOptions();
    options[minuteColumn] = INDEX;
    minuteColumnPattern->SetOptions(options);
    minuteColumnPattern->SetCurrentIndex(1);
}

/**
 * @tc.name: TimePickerAlgorithmTest001
 * @tc.desc: Test Measure.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerAlgorithmTest001, TestSize.Level1)
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
    RefPtr<LayoutWrapperNode> subLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, nullptr, nullptr);
    EXPECT_NE(subLayoutWrapper, nullptr);
    RefPtr<LayoutWrapperNode> subTwoLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, nullptr, nullptr);
    EXPECT_NE(subTwoLayoutWrapper, nullptr);
    layoutWrapper.AppendChild(std::move(subLayoutWrapper));
    layoutWrapper.AppendChild(std::move(subTwoLayoutWrapper));
    EXPECT_EQ(layoutWrapper.GetTotalChildCount(), 2);


    /**
     * @tc.step: step2. initialize TimePickerColumnLayoutAlgorithm and call Measure
     *                  and Layout function.
     */
    TimePickerColumnLayoutAlgorithm timePickerColumnLayoutAlgorithm;
    timePickerColumnLayoutAlgorithm.Measure(&layoutWrapper);
    timePickerColumnLayoutAlgorithm.Layout(&layoutWrapper);
    auto frameSize = layoutWrapper.geometryNode_->GetFrameSize();
    EXPECT_EQ(frameSize, TEST_FRAME_SIZE);

    /**
     * @tc.step: step3. set SetDeviceOrientation and call Measure.
     * @tc.expected: call Measure and frameSize valus meet expectation.
     */
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    timePickerColumnLayoutAlgorithm.Measure(&layoutWrapper);
    timePickerColumnLayoutAlgorithm.Layout(&layoutWrapper);
    frameSize = layoutWrapper.geometryNode_->GetFrameSize();
    EXPECT_EQ(frameSize, TEST_FRAME_SIZE);
}

/**
 * @tc.name: TimePickerColumnPattern016
 * @tc.desc: Test TossAnimationController.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerColumnPattern016, TestSize.Level1)
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
HWTEST_F(TimePickerPatternTestNg, TimePickerColumnPattern019, TestSize.Level1)
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
HWTEST_F(TimePickerPatternTestNg, TimePickerColumnPattern020, TestSize.Level1)
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
HWTEST_F(TimePickerPatternTestNg, TimePickerColumnPattern021, TestSize.Level1)
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
 * @tc.name: TossAnimationControllerSetStart001
 * @tc.desc: Test SetStart.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TossAnimationControllerSetStart001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TimePickerColumn.
     */
    CreateTimePickerColumnNode();

    /**
     * @tc.steps: step2. Set velocity and call SetStart .
     */
    ASSERT_NE(columnPattern_, nullptr);
    columnPattern_->SetMainVelocity(COLUMN_VELOCITY);
    columnPattern_->touchBreak_ = true;
    auto toss = columnPattern_->GetToss();
    ASSERT_NE(toss, nullptr);
    toss->SetStart(YOFFSET_START1);
    EXPECT_EQ(toss->yStart_, YOFFSET_START1);
}

/**
 * @tc.name: TossAnimationControllerSetStart002
 * @tc.desc: Test SetStart.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TossAnimationControllerSetStart002, TestSize.Level1)
{
    /**
    * @tc.steps: step1. Create TimePickerColumn.
    */
    CreateTimePickerColumnNode();

    /**
    * @tc.steps: step2. Set velocity and call SetStart .
    */
    ASSERT_NE(columnPattern_, nullptr);
    columnPattern_->SetMainVelocity(COLUMN_VELOCITY);
    columnPattern_->touchBreak_ = true;
    auto toss = columnPattern_->GetToss();
    ASSERT_NE(toss, nullptr);

    /**
    * @tc.steps: step3. init property_.
    */
    auto propertyCallback = [](float offset) {};
    toss->property_ =
        AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0, std::move(propertyCallback));
    toss->SetStart(YOFFSET_START1);
    EXPECT_EQ(toss->yStart_, YOFFSET_START1);
    EXPECT_FALSE(columnPattern_->GetTossStatus());
}

/**
 * @tc.name: TossAnimationControllerSetEnd001
 * @tc.desc: Test SetEnd.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TossAnimationControllerSetEnd001, TestSize.Level1)
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
    EXPECT_EQ(toss->yEnd_, YOFFSET_END1);
}

/**
 * @tc.name: TossAnimationControllerSetEnd002
 * @tc.desc: Test SetEnd.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TossAnimationControllerSetEnd002, TestSize.Level1)
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

    /**
    * @tc.step: step3. step3. init property_ .
    */
    auto propertyCallback = [](float offset) {};
    toss->property_ =
        AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0, std::move(propertyCallback));
    EXPECT_EQ(toss->yEnd_, YOFFSET_END1);
    EXPECT_FALSE(columnPattern_->GetTossStatus());
}

/**
 * @tc.name: TimePickerColumnPattern022
 * @tc.desc: Test TimePickerColumnPattern AddHotZoneRectToText.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerColumnPattern022, TestSize.Level1)
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
 * @tc.name: OnColorConfigurationUpdate001
 * @tc.desc: Test TimePickerRowPattern OnColorConfigurationUpdate().
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, OnColorConfigurationUpdate001, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();

    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->UpdateAllChildNode();

    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    pickerProperty->contentConstraint_ = pickerProperty->CreateContentConstraint();

    /**
     * @tc.cases: case. cover branch dialogTheme pass non null check .
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto pickerTheme = AceType::MakeRefPtr<PickerTheme>();
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();

    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(pickerTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(pickerTheme));

    auto pickerPattern = frameNode->GetPattern<TimePickerRowPattern>();

    /**
     * @tc.cases: case. cover branch isPicker_ == false.
     */
    pickerPattern->SetPickerTag(false);

    /**
     * @tc.cases: case. cover branch contentRowNode_ is not null.
     */
    pickerPattern->OnColorConfigurationUpdate();
    ASSERT_EQ(Color::BLACK, dialogTheme->GetBackgroundColor());
}

/**
 * @tc.name: OnColorConfigurationUpdate002
 * @tc.desc: Test TimePickerRowPattern OnColorConfigurationUpdate().
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, OnColorConfigurationUpdate002, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();

    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->UpdateAllChildNode();

    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    pickerProperty->contentConstraint_ = pickerProperty->CreateContentConstraint();

    /**
     * @tc.cases: case. cover branch dialogTheme pass non null check .
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto pickerTheme = AceType::MakeRefPtr<PickerTheme>();
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();

    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(pickerTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(pickerTheme));

    auto pickerPattern = frameNode->GetPattern<TimePickerRowPattern>();

    /**
     * @tc.cases: case. cover branch isPicker_ == true.
     */
    pickerPattern->SetPickerTag(true);

    pickerPattern->OnColorConfigurationUpdate();
    ASSERT_EQ(Color::BLACK, dialogTheme->GetBackgroundColor());
}
/**
 * @tc.name: TimePickerDialogView001
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogView001, TestSize.Level1)
{
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.type = std::make_optional<ButtonType>(ButtonType::CAPSULE);
    buttonInfos.push_back(info1);

    size_t sizet = 0;

    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);

    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();

    auto buttonNode = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(buttonNode, nullptr);
    auto buttonLayoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(buttonLayoutProperty, nullptr);
    auto renderContext = buttonNode->GetRenderContext();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto buttonTheme = AceType::MakeRefPtr<ButtonTheme>();
    ASSERT_NE(buttonTheme, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(buttonTheme));
    TimePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, buttonLayoutProperty, renderContext);
    auto testval = buttonLayoutProperty->GetTypeValue();
    EXPECT_EQ(testval, ButtonType::CAPSULE);
}

/**
 * @tc.name: TimePickerDialogViewShow003
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewShow003, TestSize.Level1)
{
    TimePickerSettingData settingData;
    settingData.properties.disappearTextStyle_.textColor = Color::RED;
    settingData.properties.disappearTextStyle_.fontSize = Dimension(0);
    settingData.properties.disappearTextStyle_.fontWeight = Ace::FontWeight::BOLD;

    settingData.properties.normalTextStyle_.textColor = Color::RED;
    settingData.properties.normalTextStyle_.fontSize = Dimension(0);
    settingData.properties.normalTextStyle_.fontWeight = Ace::FontWeight::BOLD;

    settingData.properties.selectedTextStyle_.textColor = Color::RED;
    settingData.properties.selectedTextStyle_.fontSize = Dimension(0);
    settingData.properties.normalTextStyle_.fontWeight = Ace::FontWeight::BOLD;
    settingData.isUseMilitaryTime = false;

    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(1, 1, 1);

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
    info1.type = std::make_optional<ButtonType>(ButtonType::CAPSULE);
    buttonInfos.push_back(info1);

    auto dialogNode = TimePickerDialogView::Show(
        dialogProperties, settingData, buttonInfos, timePickerProperty, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
}

/**
 * @tc.name: TimePickerDialogViewUpdateButtonDefaultFocus001
 * @tc.desc: Test UpdateButtonDefaultFocus.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewUpdateButtonDefaultFocus001, TestSize.Level1)
{
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.isPrimary = true;
    info1.isAcceptButton = true;
    buttonInfos.push_back(info1);

    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(buttonNode, nullptr);

    TimePickerDialogView::UpdateButtonDefaultFocus(buttonInfos, buttonNode, true);
    auto focusHub = buttonNode->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    EXPECT_EQ(focusHub->IsDefaultFocus(), true);
}

/**
 * @tc.name: TimePickerDialogViewUpdateButtonDefaultFocus002
 * @tc.desc: Test UpdateButtonDefaultFocus.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewUpdateButtonDefaultFocus002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ButtonInfos[2] and Create Button Node.
     */
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.isPrimary = true;
    buttonInfos.push_back(info1);
    ButtonInfo info2;
    info2.isPrimary = true;
    buttonInfos.push_back(info2);

    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(buttonNode, nullptr);
    /**
     * @tc.steps: step2. call UpdateButtonDefaultFocus expect defaultfocus is false.
     */
    TimePickerDialogView::UpdateButtonDefaultFocus(buttonInfos, buttonNode, false);
    auto focusHub = buttonNode->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    EXPECT_EQ(focusHub->IsDefaultFocus(), false);
    /**
     * @tc.steps: step2+. set buttoninfos isPrimary is false call UpdateButtonDefaultFocus
     *  and set buttonnode is nullptr. IsDefaultFocus expects false.
     */
    buttonInfos[0].isPrimary = false;
    buttonInfos[1].isPrimary = false;
    TimePickerDialogView::UpdateButtonDefaultFocus(buttonInfos, nullptr, false);
    EXPECT_EQ(focusHub->IsDefaultFocus(), false);
}

/**
 * @tc.name: TimePickerDialogViewUpdateButtonDefaultFocus003
 * @tc.desc: Test UpdateButtonDefaultFocus.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewUpdateButtonDefaultFocus003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ButtonInfos[2] and Create Button Node set isPrimary true.
     */
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
    /**
     * @tc.steps: step2. call UpdateButtonDefaultFocus and isConfirm is true.
     * @tc.expected: button1.isPrimary = true and IsDefaultFocus expects true.
     */
    TimePickerDialogView::UpdateButtonDefaultFocus(buttonInfos, buttonNode, true);
    auto focusHub = buttonNode->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    EXPECT_EQ(focusHub->IsDefaultFocus(), true);
    /**
     * @tc.steps: step2+. call UpdateButtonDefaultFocus and isConfirm is false.
     * @tc.expected: button2.isPrimary = true and IsDefaultFocus expects true.
     */
    buttonInfos[0].isPrimary = false;
    buttonInfos[1].isPrimary = true;
    TimePickerDialogView::UpdateButtonDefaultFocus(buttonInfos, buttonNode, false);
    focusHub = buttonNode->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    EXPECT_EQ(focusHub->IsDefaultFocus(), true);
}

/**
 * @tc.name: TimePickerDialogViewShow004
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewShow004, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    TimePickerSettingData settingData;
    settingData.isUseMilitaryTime = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::SHOW;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::HIDE;
    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(3, 3, 1);
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode = TimePickerDialogView::Show(
        dialogProperties, settingData, buttonInfos, timePickerProperty, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + ZERO + std::to_string(CURRENT_VALUE1) + COLON + std::to_string(CURRENT_VALUE1));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow005
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewShow005, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    TimePickerSettingData settingData;
    settingData.isUseMilitaryTime = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::SHOW;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::SHOW;
    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(3, 3, 1);
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode = TimePickerDialogView::Show(
        dialogProperties, settingData, buttonInfos, timePickerProperty, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + ZERO + std::to_string(CURRENT_VALUE1) + COLON + ZERO + std::to_string(CURRENT_VALUE1));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow006
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewShow006, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    TimePickerSettingData settingData;
    settingData.isUseMilitaryTime = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::HIDE;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::SHOW;
    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(3, 3, 1);
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode = TimePickerDialogView::Show(
        dialogProperties, settingData, buttonInfos, timePickerProperty, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + std::to_string(CURRENT_VALUE1) + COLON + ZERO + std::to_string(CURRENT_VALUE1));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow007
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewShow007, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    TimePickerSettingData settingData;
    settingData.isUseMilitaryTime = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::HIDE;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::HIDE;
    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(3, 3, 1);
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode = TimePickerDialogView::Show(
        dialogProperties, settingData, buttonInfos, timePickerProperty, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + std::to_string(CURRENT_VALUE1) + COLON + std::to_string(CURRENT_VALUE1));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow008
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewShow008, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    TimePickerSettingData settingData;
    settingData.isUseMilitaryTime = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::SHOW;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::HIDE;
    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(3, 4, 1);
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode = TimePickerDialogView::Show(
        dialogProperties, settingData, buttonInfos, timePickerProperty, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + ZERO + std::to_string(CURRENT_VALUE1) + COLON + std::to_string(CURRENT_VALUE3));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow009
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewShow009, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    TimePickerSettingData settingData;
    settingData.isUseMilitaryTime = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::SHOW;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::SHOW;
    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(3, 4, 1);
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode = TimePickerDialogView::Show(
        dialogProperties, settingData, buttonInfos, timePickerProperty, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + ZERO + std::to_string(CURRENT_VALUE1) + COLON + ZERO + std::to_string(CURRENT_VALUE3));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow010
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewShow010, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    TimePickerSettingData settingData;
    settingData.isUseMilitaryTime = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::HIDE;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::SHOW;
    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(3, 4, 1);
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode = TimePickerDialogView::Show(
        dialogProperties, settingData, buttonInfos, timePickerProperty, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + std::to_string(CURRENT_VALUE1) + COLON + ZERO + std::to_string(CURRENT_VALUE3));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow011
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewShow011, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    TimePickerSettingData settingData;
    settingData.isUseMilitaryTime = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::HIDE;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::HIDE;
    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(3, 4, 1);
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode = TimePickerDialogView::Show(
        dialogProperties, settingData, buttonInfos, timePickerProperty, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + std::to_string(CURRENT_VALUE1) + COLON + std::to_string(CURRENT_VALUE3));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow012
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewShow012, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    TimePickerSettingData settingData;
    settingData.isUseMilitaryTime = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::SHOW;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::HIDE;
    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(3, 5, 1);
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode = TimePickerDialogView::Show(
        dialogProperties, settingData, buttonInfos, timePickerProperty, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + ZERO + std::to_string(CURRENT_VALUE1) + COLON + std::to_string(CURRENT_VALUE4));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow013
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewShow013, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    TimePickerSettingData settingData;
    settingData.isUseMilitaryTime = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::SHOW;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::SHOW;
    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(3, 5, 1);
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode = TimePickerDialogView::Show(
        dialogProperties, settingData, buttonInfos, timePickerProperty, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + ZERO + std::to_string(CURRENT_VALUE1) + COLON + ZERO + std::to_string(CURRENT_VALUE4));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow014
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewShow014, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    TimePickerSettingData settingData;
    settingData.isUseMilitaryTime = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::HIDE;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::SHOW;
    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(3, 5, 1);
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode = TimePickerDialogView::Show(
        dialogProperties, settingData, buttonInfos, timePickerProperty, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + std::to_string(CURRENT_VALUE1) + COLON + ZERO + std::to_string(CURRENT_VALUE4));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow015
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewShow015, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    TimePickerSettingData settingData;
    settingData.isUseMilitaryTime = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::HIDE;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::HIDE;
    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(3, 5, 1);
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode = TimePickerDialogView::Show(
        dialogProperties, settingData, buttonInfos, timePickerProperty, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + std::to_string(CURRENT_VALUE1) + COLON + std::to_string(CURRENT_VALUE4));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow016
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewShow016, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    TimePickerSettingData settingData;
    settingData.isUseMilitaryTime = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::SHOW;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::HIDE;
    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(3, 6, 1);
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode = TimePickerDialogView::Show(
        dialogProperties, settingData, buttonInfos, timePickerProperty, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + ZERO + std::to_string(CURRENT_VALUE1) + COLON + std::to_string(CURRENT_VALUE5));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow017
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewShow017, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    TimePickerSettingData settingData;
    settingData.isUseMilitaryTime = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::SHOW;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::SHOW;
    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(3, 6, 1);
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode = TimePickerDialogView::Show(
        dialogProperties, settingData, buttonInfos, timePickerProperty, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + ZERO + std::to_string(CURRENT_VALUE1) + COLON + ZERO + std::to_string(CURRENT_VALUE5));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow018
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewShow018, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    TimePickerSettingData settingData;
    settingData.isUseMilitaryTime = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::HIDE;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::SHOW;
    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(3, 6, 1);
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode = TimePickerDialogView::Show(
        dialogProperties, settingData, buttonInfos, timePickerProperty, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + std::to_string(CURRENT_VALUE1) + COLON + ZERO + std::to_string(CURRENT_VALUE5));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow019
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewShow019, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    TimePickerSettingData settingData;
    settingData.isUseMilitaryTime = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::HIDE;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::HIDE;
    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(3, 6, 1);
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode = TimePickerDialogView::Show(
        dialogProperties, settingData, buttonInfos, timePickerProperty, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + std::to_string(CURRENT_VALUE1) + COLON + std::to_string(CURRENT_VALUE5));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow020
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewShow020, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    TimePickerSettingData settingData;
    settingData.isUseMilitaryTime = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::SHOW;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::HIDE;
    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(5, 6, 1);
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode = TimePickerDialogView::Show(
        dialogProperties, settingData, buttonInfos, timePickerProperty, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + ZERO + std::to_string(CURRENT_VALUE4) + COLON + std::to_string(CURRENT_VALUE5));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow021
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewShow021, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    TimePickerSettingData settingData;
    settingData.isUseMilitaryTime = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::SHOW;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::SHOW;
    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(5, 6, 1);
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode = TimePickerDialogView::Show(
        dialogProperties, settingData, buttonInfos, timePickerProperty, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + ZERO + std::to_string(CURRENT_VALUE4) + COLON + ZERO + std::to_string(CURRENT_VALUE5));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow022
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewShow022, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    TimePickerSettingData settingData;
    settingData.isUseMilitaryTime = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::HIDE;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::SHOW;
    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(5, 6, 1);
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode = TimePickerDialogView::Show(
        dialogProperties, settingData, buttonInfos, timePickerProperty, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + std::to_string(CURRENT_VALUE4) + COLON + ZERO + std::to_string(CURRENT_VALUE5));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow023
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewShow023, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    TimePickerSettingData settingData;
    settingData.isUseMilitaryTime = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::HIDE;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::HIDE;
    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(5, 6, 1);
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode = TimePickerDialogView::Show(
        dialogProperties, settingData, buttonInfos, timePickerProperty, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + std::to_string(CURRENT_VALUE4) + COLON + std::to_string(CURRENT_VALUE5));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow024
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewShow024, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    TimePickerSettingData settingData;
    settingData.isUseMilitaryTime = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::SHOW;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::HIDE;
    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(4, 4, 1);
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode = TimePickerDialogView::Show(
        dialogProperties, settingData, buttonInfos, timePickerProperty, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + ZERO + std::to_string(CURRENT_VALUE3) + COLON + std::to_string(CURRENT_VALUE3));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow025
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewShow025, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    TimePickerSettingData settingData;
    settingData.isUseMilitaryTime = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::SHOW;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::SHOW;
    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(4, 4, 1);
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode = TimePickerDialogView::Show(
        dialogProperties, settingData, buttonInfos, timePickerProperty, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + ZERO + std::to_string(CURRENT_VALUE3) + COLON + ZERO + std::to_string(CURRENT_VALUE3));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow026
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewShow026, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    TimePickerSettingData settingData;
    settingData.isUseMilitaryTime = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::HIDE;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::SHOW;
    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(4, 4, 1);
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode = TimePickerDialogView::Show(
        dialogProperties, settingData, buttonInfos, timePickerProperty, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + std::to_string(CURRENT_VALUE3) + COLON + ZERO + std::to_string(CURRENT_VALUE3));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow027
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewShow027, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    TimePickerSettingData settingData;
    settingData.isUseMilitaryTime = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::HIDE;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::HIDE;
    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(4, 4, 1);
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode = TimePickerDialogView::Show(
        dialogProperties, settingData, buttonInfos, timePickerProperty, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + std::to_string(CURRENT_VALUE3) + COLON + std::to_string(CURRENT_VALUE3));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow028
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewShow028, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    TimePickerSettingData settingData;
    settingData.isUseMilitaryTime = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::SHOW;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::HIDE;
    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(4, 5, 1);
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode = TimePickerDialogView::Show(
        dialogProperties, settingData, buttonInfos, timePickerProperty, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + ZERO + std::to_string(CURRENT_VALUE3) + COLON + std::to_string(CURRENT_VALUE4));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow029
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewShow029, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    TimePickerSettingData settingData;
    settingData.isUseMilitaryTime = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::SHOW;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::SHOW;
    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(4, 5, 1);
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode = TimePickerDialogView::Show(
        dialogProperties, settingData, buttonInfos, timePickerProperty, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + ZERO + std::to_string(CURRENT_VALUE3) + COLON + ZERO + std::to_string(CURRENT_VALUE4));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow030
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewShow030, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    TimePickerSettingData settingData;
    settingData.isUseMilitaryTime = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::HIDE;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::SHOW;
    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(4, 5, 1);
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode = TimePickerDialogView::Show(
        dialogProperties, settingData, buttonInfos, timePickerProperty, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + std::to_string(CURRENT_VALUE3) + COLON + ZERO + std::to_string(CURRENT_VALUE4));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow031
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewShow031, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    TimePickerSettingData settingData;
    settingData.isUseMilitaryTime = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::HIDE;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::HIDE;
    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(4, 5, 1);
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode = TimePickerDialogView::Show(
        dialogProperties, settingData, buttonInfos, timePickerProperty, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + std::to_string(CURRENT_VALUE3) + COLON + std::to_string(CURRENT_VALUE4));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow032
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewShow032, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    TimePickerSettingData settingData;
    settingData.isUseMilitaryTime = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::SHOW;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::HIDE;
    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(4, 6, 1);
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode = TimePickerDialogView::Show(
        dialogProperties, settingData, buttonInfos, timePickerProperty, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + ZERO + std::to_string(CURRENT_VALUE3) + COLON + std::to_string(CURRENT_VALUE5));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow033
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewShow033, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    TimePickerSettingData settingData;
    settingData.isUseMilitaryTime = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::SHOW;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::SHOW;
    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(4, 6, 1);
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode = TimePickerDialogView::Show(
        dialogProperties, settingData, buttonInfos, timePickerProperty, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + ZERO + std::to_string(CURRENT_VALUE3) + COLON + ZERO + std::to_string(CURRENT_VALUE5));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow034
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewShow034, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    TimePickerSettingData settingData;
    settingData.isUseMilitaryTime = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::HIDE;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::SHOW;
    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(4, 6, 1);
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode = TimePickerDialogView::Show(
        dialogProperties, settingData, buttonInfos, timePickerProperty, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + std::to_string(CURRENT_VALUE3) + COLON + ZERO + std::to_string(CURRENT_VALUE5));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow035
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewShow035, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    TimePickerSettingData settingData;
    settingData.isUseMilitaryTime = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::HIDE;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::HIDE;
    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(4, 6, 1);
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode = TimePickerDialogView::Show(
        dialogProperties, settingData, buttonInfos, timePickerProperty, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + std::to_string(CURRENT_VALUE3) + COLON + std::to_string(CURRENT_VALUE5));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow036
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewShow036, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    TimePickerSettingData settingData;
    settingData.isUseMilitaryTime = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::SHOW;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::HIDE;
    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(5, 5, 1);
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode = TimePickerDialogView::Show(
        dialogProperties, settingData, buttonInfos, timePickerProperty, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + ZERO + std::to_string(CURRENT_VALUE4) + COLON + std::to_string(CURRENT_VALUE4));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow037
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewShow037, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    TimePickerSettingData settingData;
    settingData.isUseMilitaryTime = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::SHOW;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::SHOW;
    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(5, 5, 1);
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode = TimePickerDialogView::Show(
        dialogProperties, settingData, buttonInfos, timePickerProperty, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + ZERO + std::to_string(CURRENT_VALUE4) + COLON + ZERO + std::to_string(CURRENT_VALUE4));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow038
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewShow038, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    TimePickerSettingData settingData;
    settingData.isUseMilitaryTime = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::HIDE;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::SHOW;
    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(5, 5, 1);
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode = TimePickerDialogView::Show(
        dialogProperties, settingData, buttonInfos, timePickerProperty, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + std::to_string(CURRENT_VALUE4) + COLON + ZERO + std::to_string(CURRENT_VALUE4));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow039
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewShow039, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    TimePickerSettingData settingData;
    settingData.isUseMilitaryTime = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::HIDE;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::HIDE;
    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(5, 5, 1);
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode = TimePickerDialogView::Show(
        dialogProperties, settingData, buttonInfos, timePickerProperty, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + std::to_string(CURRENT_VALUE4) + COLON + std::to_string(CURRENT_VALUE4));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow040
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewShow040, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    TimePickerSettingData settingData;
    settingData.isUseMilitaryTime = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::SHOW;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::HIDE;
    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(6, 6, 1);
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode = TimePickerDialogView::Show(
        dialogProperties, settingData, buttonInfos, timePickerProperty, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + ZERO + std::to_string(CURRENT_VALUE5) + COLON + std::to_string(CURRENT_VALUE5));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow041
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewShow041, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    TimePickerSettingData settingData;
    settingData.isUseMilitaryTime = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::SHOW;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::SHOW;
    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(6, 6, 1);
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode = TimePickerDialogView::Show(
        dialogProperties, settingData, buttonInfos, timePickerProperty, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + ZERO + std::to_string(CURRENT_VALUE5) + COLON + ZERO + std::to_string(CURRENT_VALUE5));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow042
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewShow042, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    TimePickerSettingData settingData;
    settingData.isUseMilitaryTime = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::HIDE;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::SHOW;
    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(6, 6, 1);
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode = TimePickerDialogView::Show(
        dialogProperties, settingData, buttonInfos, timePickerProperty, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + std::to_string(CURRENT_VALUE5) + COLON + ZERO + std::to_string(CURRENT_VALUE5));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow043
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewShow043, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    TimePickerSettingData settingData;
    settingData.isUseMilitaryTime = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::HIDE;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::HIDE;
    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(6, 6, 1);
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode = TimePickerDialogView::Show(
        dialogProperties, settingData, buttonInfos, timePickerProperty, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + std::to_string(CURRENT_VALUE5) + COLON + std::to_string(CURRENT_VALUE5));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerEnableHapticFeedback001
 * @tc.desc: Test property enableHapticFeedback by default.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerEnableHapticFeedback001, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    EXPECT_TRUE(TimePickerModelNG::getEnableHapticFeedback(frameNode));
}

/**
 * @tc.name: TimePickerEnableHapticFeedback002
 * @tc.desc: Test property enableHapticFeedback by Setter API
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerEnableHapticFeedback002, TestSize.Level1)
{
    std::vector<bool> testValues = { false, true, true, false, false };
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);

    for (auto testValue : testValues) {
        TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
        auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
        ASSERT_NE(frameNode, nullptr);
        TimePickerModelNG::GetInstance()->SetIsEnableHapticFeedback(testValue);
        EXPECT_EQ(TimePickerModelNG::getEnableHapticFeedback(frameNode), static_cast<uint32_t>(testValue));
    }
}

/**
 * @tc.name: TimePickerEnableHapticFeedback003
 * @tc.desc: Test property enableHapticFeedback by Setter/Getter API
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerEnableHapticFeedback003, TestSize.Level1)
{
    std::vector<bool> testValues = { false, true, true, false, false };
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);

    for (auto testValue : testValues) {
        TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
        auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
        ASSERT_NE(frameNode, nullptr);
        TimePickerModelNG::GetInstance()->SetIsEnableHapticFeedback(testValue);
        auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
        ASSERT_NE(timePickerRowPattern, nullptr);
        EXPECT_EQ(timePickerRowPattern->GetIsEnableHaptic(), testValue);
    }
}

/**
 * @tc.name: TimePickerDialogViewConvertFontScaleValue001
 * @tc.desc: Test TimePickerDialogView ConvertFontScaleValue.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewConvertFontScaleValue001, TestSize.Level1)
{
    Dimension fontSizeValue = 50.0_vp;
    Dimension fontSizeLimit = 40.0_vp;

    auto result = TimePickerDialogView::ConvertFontScaleValue(fontSizeValue,
        fontSizeLimit, true);
    EXPECT_EQ(fontSizeLimit.Value(), result.Value());
}

/**
 * @tc.name: TimePickerDialogViewConvertFontScaleValue002
 * @tc.desc: Test TimePickerDialogView ConvertFontScaleValue.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewConvertFontScaleValue002, TestSize.Level1)
{
    Dimension fontSizeValue = 20.0_vp;
    Dimension fontSizeLimit = 40.0_vp;

    auto result = TimePickerDialogView::ConvertFontScaleValue(fontSizeValue,
        fontSizeLimit, true);
    EXPECT_EQ(fontSizeValue.Value(), result.Value());
}

/**
 * @tc.name: TimePickerDialogViewConvertFontSizeLimitTest001
 * @tc.desc: Test TimePickerDialogView ConvertFontSizeLimit.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewConvertFontSizeLimitTest001, TestSize.Level1)
{
    Dimension fontSizeValue(20.0);
    Dimension fontSizeLimit(30.0);
    bool isUserSetFont = false;
    Dimension result = TimePickerDialogView::ConvertFontSizeLimit(fontSizeValue,
        fontSizeLimit, isUserSetFont);
    EXPECT_EQ(result, fontSizeValue);
}

/**
 * @tc.name: TimePickerDialogViewConvertFontSizeLimitTest002
 * @tc.desc: Test TimePickerDialogView ConvertFontSizeLimit.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewConvertFontSizeLimitTest002, TestSize.Level1)
{
    Dimension fontSizeValue(20.0);
    Dimension fontSizeLimit(30.0);
    bool isUserSetFont = true;
    Dimension result = TimePickerDialogView::ConvertFontSizeLimit(fontSizeValue,
        fontSizeLimit, isUserSetFont);
    EXPECT_EQ(result, fontSizeValue);
}

/**
 * @tc.name: TimePickerDialogViewConvertFontSizeLimitTest003
 * @tc.desc: Test TimePickerDialogView ConvertFontSizeLimit.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewConvertFontSizeLimitTest003, TestSize.Level1)
{
    Dimension fontSizeValue(40.0);
    Dimension fontSizeLimit(30.0);
    bool isUserSetFont = true;
    double fontScale = 2.0f;
    MockPipelineContext::GetCurrent()->SetFontScale(fontScale);
    Dimension result = TimePickerDialogView::ConvertFontSizeLimit(fontSizeValue,
        fontSizeLimit, isUserSetFont);
    Dimension expected = fontSizeLimit / fontScale;
    EXPECT_EQ(result, expected);
}

/**
 * @tc.name: TimePickerDialogViewConvertFontSizeLimitTest004
 * @tc.desc: Test TimePickerDialogView ConvertFontSizeLimit.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewConvertFontSizeLimitTest004, TestSize.Level1)
{
    Dimension fontSizeValue(10.0);
    Dimension fontSizeLimit(30.0);
    bool isUserSetFont = true;
    double fontScale = 2.0f;
    MockPipelineContext::GetCurrent()->SetFontScale(fontScale);
    Dimension result = TimePickerDialogView::ConvertFontSizeLimit(fontSizeValue,
        fontSizeLimit, isUserSetFont);
    EXPECT_EQ(result, fontSizeValue);
}

/**
 * @tc.name: TimePickerDialogViewGetUserSettingLimitTest001
 * @tc.desc: Test TimePickerDialogView AdjustFontSizeScale.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewGetUserSettingLimitTest001, TestSize.Level1)
{
    double fontScale = 1.0f;
    Dimension fontSizeValue(10.0);
    Dimension result = TimePickerDialogView::AdjustFontSizeScale(fontSizeValue, fontScale);
    EXPECT_EQ(result, fontSizeValue * fontScale);
}

/**
 * @tc.name: TimePickerDialogViewGetUserSettingLimitTest002
 * @tc.desc: Test TimePickerDialogView AdjustFontSizeScale.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewGetUserSettingLimitTest002, TestSize.Level1)
{
    double fontScale = 1.75f;
    Dimension fontSizeValue(10.0);
    Dimension result = TimePickerDialogView::AdjustFontSizeScale(fontSizeValue, fontScale);
    EXPECT_EQ(result, fontSizeValue * fontScale);
}

/**
 * @tc.name: TimePickerDialogViewGetUserSettingLimitTest003
 * @tc.desc: Test TimePickerDialogView AdjustFontSizeScale.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewGetUserSettingLimitTest003, TestSize.Level1)
{
    double fontScale = 2.0f;
    Dimension fontSizeValue(10.0);
    Dimension result = TimePickerDialogView::AdjustFontSizeScale(fontSizeValue, fontScale);
    EXPECT_EQ(result, fontSizeValue * fontScale);
}

/**
 * @tc.name: TimePickerDialogViewGetUserSettingLimitTest004
 * @tc.desc: Test TimePickerDialogView AdjustFontSizeScale.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewGetUserSettingLimitTest004, TestSize.Level1)
{
    double fontScale = 3.2f;
    Dimension fontSizeValue(10.0);
    Dimension result = TimePickerDialogView::AdjustFontSizeScale(fontSizeValue, fontScale);
    EXPECT_NE(result, fontSizeValue * fontScale);
}

/**
 * @tc.name: TimePickerModelNGBackgroundColor001
 * @tc.desc: Test TimePickerPatternTestNg SetBackgroundColor and getTimepickerBackgroundColor.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerModelNGBackgroundColor001, TestSize.Level1)
{
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);

    auto theme = context->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    TimePickerModelNG::SetBackgroundColor(frameNode, Color::RED);
    EXPECT_EQ(TimePickerModelNG::getTimepickerBackgroundColor(frameNode), Color::RED.GetValue());
}

/**
 * @tc.name: TimePickerRowPatternCheckFocusID001
 * @tc.desc: Test CheckFocusID2.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerRowPatternCheckFocusID001, TestSize.Level1)
{
    /**
     * @tc.step: step1. create row pattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    EXPECT_NE(timePickerRowPattern, nullptr);
    /**
     * @tc.steps: step2. call CheckFocusID.
     * @tc.expected: set focusKeyID is less than childSize.
     */
    int32_t value = -1;
    int32_t childSize = 8;
    timePickerRowPattern->SetCurrentFocusKeyID(value);
    bool res = timePickerRowPattern->CheckFocusID(childSize);
    int32_t focusKeyID = timePickerRowPattern->GetCurrentFocusKeyID();
    EXPECT_FALSE(res);
    EXPECT_EQ(focusKeyID, 0);
    auto pipeline = PipelineBase::GetCurrentContextSafely();
    EXPECT_NE(pipeline, nullptr);
    float fontSize = 100.0f;
    pipeline->fontScale_ = fontSize;
    pipeline->rootHeight_ = fontSize;
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    EXPECT_NE(pickerTheme, nullptr);
    double pickerSize = 50.75;
    pickerTheme->pickerDialogMaxOneFontScale_ = pickerSize;
    pickerTheme->deviceHeightLimit_ = pickerSize;
    EXPECT_GT(pipeline->GetFontScale(), pickerTheme->GetMaxOneFontScale());
    timePickerRowPattern->SetCurrentPage(1);
    res = timePickerRowPattern->CheckFocusID(childSize);
    EXPECT_TRUE(res);
    /**
     * @tc.steps: step3. call CheckFocusID.
     * @tc.expected: set focusKeyID is less than childSize.
     */
    timePickerRowPattern->SetCurrentPage(0);
    res = timePickerRowPattern->CheckFocusID(childSize);
    EXPECT_NE(timePickerRowPattern->GetCurrentPage(), 1);
    EXPECT_TRUE(res);
}

/**
 * @tc.name: TimePickerColumnPatternScrollOption001
 * @tc.desc: Test TimePickerColumnPattern ScrollOption and HandleEnterSelectedArea.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerColumnPatternScrollOption001, TestSize.Level1)
{
    CreateTimePickerColumnNode();
    ASSERT_NE(columnPattern_, nullptr);
    ASSERT_NE(columnNode_, nullptr);
    auto childSize = static_cast<int32_t>(columnNode_->GetChildren().size());
    auto midSize = childSize / MIDDLE_OF_COUNTS;
    columnPattern_->optionProperties_[midSize].prevDistance = 5.0f;
    columnPattern_->optionProperties_[midSize].nextDistance = 7.0f;
    columnPattern_->SetCurrentIndex(2);
    columnPattern_->ScrollOption(10.0f);
    EXPECT_EQ(columnPattern_->GetEnterIndex(), 1);
}

#ifdef ARKUI_WEARABLE
/**
 * @tc.name: TimePickerPaintTest001
 * @tc.desc: Test GetForegroundDrawFunction.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerPaintTest001, TestSize.Level1)
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
HWTEST_F(TimePickerPatternTestNg, TimePickerPaintTest002, TestSize.Level1)
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
HWTEST_F(TimePickerPatternTestNg, TimePickerPaintTest003, TestSize.Level1)
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
HWTEST_F(TimePickerPatternTestNg, TimePickerPaintTest004, TestSize.Level1)
{
#ifdef SUPPORT_DIGITAL_CROWN
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_TRUE(frameNode);
    frameNode->MarkModifyDone();
    auto eventHub = frameNode->GetOrCreateEventHub<EventHub>();
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
HWTEST_F(TimePickerPatternTestNg, TimePickerSetDefaultFocus001, TestSize.Level1)
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
HWTEST_F(TimePickerPatternTestNg, TimePickerClearFocus001, TestSize.Level1)
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
HWTEST_F(TimePickerPatternTestNg, TimePickerClearFocus002, TestSize.Level1)
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
HWTEST_F(TimePickerPatternTestNg, TimePickerPaintTest005, TestSize.Level1)
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
HWTEST_F(TimePickerPatternTestNg, TimePickerRotateCrown001, TestSize.Level1)
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
HWTEST_F(TimePickerPatternTestNg, TimePickerSetDefaultFocus002, TestSize.Level1)
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
HWTEST_F(TimePickerPatternTestNg, TimePickerRestoreFrameNode001, TestSize.Level1)
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
HWTEST_F(TimePickerPatternTestNg, TimePickerColumnLayoutAlgorithmNeedAdaptForAging, TestSize.Level1)
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
HWTEST_F(TimePickerPatternTestNg, TimePickerColumnLayoutAlgorithmAdjustFontSizeScale, TestSize.Level1)
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
HWTEST_F(TimePickerPatternTestNg, TimePickerColumnLayoutAlgorithmGetPickerMaxHeight, TestSize.Level1)
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
HWTEST_F(TimePickerPatternTestNg, TimePickerModelNGHasUserDefinedDisappearFontFamily01, TestSize.Level1)
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
HWTEST_F(TimePickerPatternTestNg, TimePickerModelNGHasUserDefinedDisappearFontFamily02, TestSize.Level1)
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
HWTEST_F(TimePickerPatternTestNg, TimePickerModelNGHasUserDefinedNormalFontFamily01, TestSize.Level1)
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
HWTEST_F(TimePickerPatternTestNg, TimePickerModelNGSetHour2401, TestSize.Level1)
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
HWTEST_F(TimePickerPatternTestNg, TimePickerModelNGgetNormalTextStyle01, TestSize.Level1)
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
HWTEST_F(TimePickerPatternTestNg, TimePickerModelNGgetSelectedTextStyle01, TestSize.Level1)
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
HWTEST_F(TimePickerPatternTestNg, TimePickerModelNGgetTimepickerSelected01, TestSize.Level1)
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
HWTEST_F(TimePickerPatternTestNg, TimePickerModelNGgetTimepickerBackgroundColor01, TestSize.Level1)
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
HWTEST_F(TimePickerPatternTestNg, TimePickerModelNGgetTimepickerUseMilitaryTime01, TestSize.Level1)
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
 * @tc.desc: Test TimePickerModelNG getTimepickerEnableCascade.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerModelNGGetIsEnableCascadeValue01, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_TRUE(frameNode);
    auto pickerTheme = MockThemeDefault::GetPickerTheme();
    ASSERT_NE(pickerTheme, nullptr);
    ASSERT_FALSE(TimePickerModelNG::getTimepickerEnableCascade(frameNode));
}

/**
 * @tc.name: TimePickerModelNGSetWheelModeEnabled
 * @tc.desc: Test TimePickerModelNG SetWheelModeEnabled.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerModelNGSetWheelModeEnabled, TestSize.Level1)
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
HWTEST_F(TimePickerPatternTestNg, SetDefaultAttributes01, TestSize.Level1)
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
HWTEST_F(TimePickerPatternTestNg, TimePickerModelNGHasUserDefinedSelectedFontFamily, TestSize.Level1)
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
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogCreateNextPrevButtonNode, TestSize.Level1)
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
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogCreateNextPrevButtonNode02, TestSize.Level1)
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
HWTEST_F(TimePickerPatternTestNg, TimePickerPaintTest006, TestSize.Level1)
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
HWTEST_F(TimePickerPatternTestNg, TimePickerPaintTest007, TestSize.Level1)
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
 * @tc.name: TimePickerPatterntest001
 * @tc.desc: Test ColumnPatternInitHapticController.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerPatterntest001, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_TRUE(frameNode);
    auto pickerTheme = MockThemeDefault::GetPickerTheme();
    ASSERT_NE(pickerTheme, nullptr);
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    timePickerRowPattern->isHapticChanged_ = true;
    timePickerRowPattern->UpdateAllChildNode();
    timePickerRowPattern->ColumnPatternInitHapticController();
    EXPECT_FALSE(timePickerRowPattern->isHapticChanged_);
}
 
 /**
  * @tc.name: TimePickerPatterntest002
  * @tc.desc: Test ColumnPatternStopHaptic.
  * @tc.type: FUNC
  */
HWTEST_F(TimePickerPatternTestNg, TimePickerPatterntest002, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_TRUE(frameNode);
    auto pickerTheme = MockThemeDefault::GetPickerTheme();
    ASSERT_NE(pickerTheme, nullptr);
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    timePickerRowPattern->isEnableHaptic_ = true;
    timePickerRowPattern->UpdateAllChildNode();
    timePickerRowPattern->ColumnPatternStopHaptic();
    auto host = timePickerRowPattern->GetHost();
    CHECK_NULL_VOID(host);
    auto children = host->GetChildren();
    for (const auto& child : children) {
        auto stackNode = AceType::DynamicCast<FrameNode>(child);
        CHECK_NULL_VOID(stackNode);
        auto blendNode = AceType::DynamicCast<FrameNode>(stackNode->GetLastChild());
        CHECK_NULL_VOID(blendNode);
        auto childNode = blendNode->GetLastChild();
        CHECK_NULL_VOID(childNode);
        auto datePickerColumnPattern =
            AceType::DynamicCast<FrameNode>(childNode)->GetPattern<TimePickerColumnPattern>();
        CHECK_NULL_VOID(datePickerColumnPattern);
        datePickerColumnPattern->StopHaptic();
        ASSERT_TRUE(datePickerColumnPattern->stopHaptic_);
    }
}

/**
 * @tc.name: TimePickerPatternToJsonValue001
 * @tc.desc: Test TimePickerRowPattern ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerRowPatternToJsonValue001, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_TRUE(frameNode);
    auto pickerTheme = MockThemeDefault::GetPickerTheme();
    ASSERT_NE(pickerTheme, nullptr);
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    /**
     * @tc.steps: step1. set option value.
     */
    PickerTime startTime = PickerTime(0, 1, 1);
    PickerTime endTime = PickerTime(22, 58, 58);
    bool isEnableHaptic = true;
    timePickerRowPattern->SetStartTime(startTime);
    timePickerRowPattern->SetEndTime(endTime);
    timePickerRowPattern->SetIsEnableHaptic(isEnableHaptic);

    /**
     * @tc.steps: step2. call tojsonvalue funtion.
     */
    auto json = JsonUtil::Create(true);
    timePickerRowPattern->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("start"), startTime.ToString(false, false).c_str());
    EXPECT_EQ(json->GetString("end"), endTime.ToString(false, false).c_str());
    EXPECT_TRUE(json->GetBool("enableHapticFeedback"));
}

/**
 * @tc.name: TimePickerPatternToJsonValue002
 * @tc.desc: Test TimePickerRowPattern ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerRowPatternToJsonValue002, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_TRUE(frameNode);
    auto pickerTheme = MockThemeDefault::GetPickerTheme();
    ASSERT_NE(pickerTheme, nullptr);
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    /**
     * @tc.steps: step1. set option value.
     */
    PickerTime startTime = PickerTime(0, 0, 0);
    PickerTime endTime = PickerTime(23, 59, 59);
    bool isEnableHaptic = true;

    /**
     * @tc.steps: step2. call tojsonvalue funtion and judge default value.
     */
    auto json = JsonUtil::Create(true);
    timePickerRowPattern->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("start"), startTime.ToString(false, false).c_str());
    EXPECT_EQ(json->GetString("end"), endTime.ToString(false, false).c_str());
    EXPECT_EQ(json->GetBool("enableHapticFeedback"), isEnableHaptic);
}

/**
 * @tc.name: TimePickerLayoutPropertyToJsonValue002
 * @tc.desc: Test TimePickerLayoutProperty ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerLayoutPropertyToJsonValue002, TestSize.Level1)
{
    /**
    * @tc.step: step1. initialize LayoutProperty and TimePickerModelNG.
    */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    bool hasSecond = true;
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, hasSecond);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    pickerProperty->GetOrCreateDisappearTextStyle();
    pickerProperty->GetOrCreateTextStyle();
    pickerProperty->GetOrCreateSelectedTextStyle();
    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    pickerProperty->ToJsonValue(json, filter);
    EXPECT_FALSE(pickerProperty->HasIsUseMilitaryTime());
    EXPECT_FALSE(pickerProperty->HasLoop());

    /**
    * @tc.step: step2. call ToJsonValue() and check default value.
    */
    EXPECT_EQ(json->GetString("useMilitaryTime"), "false");
    EXPECT_EQ(json->GetString("loop"), "true");
    auto disappearTextStyle = json->GetObject("disappearTextStyle");
    ASSERT_NE(disappearTextStyle, nullptr);
    ASSERT_EQ(disappearTextStyle->GetString("color"), "#FF000000");
    auto disappearFont = disappearTextStyle->GetObject("font");
    ASSERT_NE(disappearFont, nullptr);
    EXPECT_EQ(disappearFont->GetString("size"), "0.00px");
    EXPECT_EQ(disappearFont->GetString("weight"), "FontWeight.Normal");

    auto textStyle = json->GetObject("textStyle");
    ASSERT_NE(textStyle, nullptr);
    ASSERT_EQ(textStyle->GetString("color"), "#FF000000");
    auto normalFont = textStyle->GetObject("font");
    ASSERT_NE(normalFont, nullptr);
    EXPECT_EQ(normalFont->GetString("size"), "0.00px");
    EXPECT_EQ(normalFont->GetString("weight"), "FontWeight.Normal");

    auto selectTextStyle = json->GetObject("selectedTextStyle");
    ASSERT_NE(selectTextStyle, nullptr);
    ASSERT_EQ(selectTextStyle->GetString("color"), "#FF000000");
    auto selectFont = textStyle->GetObject("font");
    ASSERT_NE(selectFont, nullptr);
    EXPECT_EQ(selectFont->GetString("size"), "0.00px");
    EXPECT_EQ(selectFont->GetString("weight"), "FontWeight.Normal");

    auto options = json->GetObject("dateTimeOptions");
    EXPECT_EQ(options->GetString("hour"), "numeric");
    EXPECT_EQ(
        options->GetString("minute"), TimeFormat::GetMinuteFormat(pickerProperty->GetPrefixMinuteValue(0)).c_str());
    if (pickerProperty->GetPrefixSecondValue(0) != static_cast<int32_t>(ZeroPrefixType::OFF)) {
        EXPECT_EQ(
            options->GetString("second"), TimeFormat::GetSecondFormat(pickerProperty->GetPrefixSecondValue(0)).c_str());
    }
}

/**
 * @tc.name: TimePickerLayoutPropertyToJsonValue003
 * @tc.desc: Test TimePickerLayoutProperty ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerLayoutPropertyToJsonValue003, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto timePickerModeNG = TimePickerModelNG::GetInstance();

    /**
     * @tc.cases: case. cover set isUseMilitaryTime and call ToJsonValue().
     */
    bool isUseMilitaryTime = true;
    timePickerModeNG->SetHour24(isUseMilitaryTime);

    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    pickerProperty->UpdateLoop(false);
    auto json = JsonUtil::Create(true);
    pickerProperty->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("useMilitaryTime"), "true");
    EXPECT_EQ(json->GetString("loop"), "false");

    /**
     * @tc.cases: case. cover update isUseMilitaryTime by layoutProperty and call ToJsonValue().
     */
    pickerProperty->UpdateIsUseMilitaryTime(true);
    pickerProperty->UpdateLoop(true);
    EXPECT_TRUE(pickerProperty->GetLoopValue());
    auto json2 = JsonUtil::Create(true);
    pickerProperty->ToJsonValue(json2, filter);
    EXPECT_TRUE(pickerProperty->HasLoop());
    EXPECT_EQ(json2->GetString("useMilitaryTime"), "true");
    EXPECT_EQ(json2->GetString("loop"), "true");
}

/**
 * @tc.name: TimePickerLayoutPropertyToJsonValue004
 * @tc.desc: Test TimePickerLayoutProperty SetNormalTextStyle and call ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerLayoutPropertyToJsonValue004, TestSize.Level1)
{
    /**
     * @tc.step: step1. initialize LayoutProperty and TimePickerModelNG.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto timePickerModeNG = TimePickerModelNG::GetInstance();
    ASSERT_NE(timePickerModeNG, nullptr);

    /**
     * @tc.step: step2 Set PickerTextStyle and call ToJsonValue().
     */
    PickerTextStyle data;
    data.fontSize = Dimension(10);
    data.textColor = Color::RED;
    data.fontWeight = Ace::FontWeight::BOLD;
    timePickerModeNG->SetNormalTextStyle(theme, data);
    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    pickerProperty->ToJsonValue(json, filter);

    /**
     * @tc.step: step3 check value of PickerTextStyle.
     */
    auto normalTextStyle = json->GetObject("textStyle");
    ASSERT_NE(normalTextStyle, nullptr);
    EXPECT_EQ(normalTextStyle->GetString("color"), "#FFFF0000");
    auto normalFont = normalTextStyle->GetObject("font");
    ASSERT_NE(normalFont, nullptr);
    EXPECT_EQ(normalFont->GetString("size"), "10.00px");
    EXPECT_EQ(normalFont->GetString("weight"), "FontWeight.Bold");

    /**
     * @tc.cases: case. cover call reset() and check selectedTextStyle.
     */
    pickerProperty->Reset();
    auto json2 = JsonUtil::Create(true);
    ASSERT_NE(json2, nullptr);
    pickerProperty->ToJsonValue(json2, filter);
    EXPECT_EQ(pickerProperty->GetTextStyle(), nullptr);
}

 /**
 * @tc.name: TimePickerLayoutPropertyToJsonValue005
 * @tc.desc: Test TimePickerLayoutProperty SetSelectTextStyle and call ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerLayoutPropertyToJsonValue005, TestSize.Level1)
{
    /**
    * @tc.step: step1. initialize LayoutProperty and TimePickerModelNG.
    */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto timePickerModeNG = TimePickerModelNG::GetInstance();
    ASSERT_NE(timePickerModeNG, nullptr);

    /**
     * @tc.step: step2 Set PickerTextStyle and call ToJsonValue().
     */
    PickerTextStyle data;
    data.fontSize = Dimension(10);
    data.textColor = Color::RED;
    data.fontWeight = Ace::FontWeight::BOLD;
    timePickerModeNG->SetSelectedTextStyle(theme, data);
    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    pickerProperty->ToJsonValue(json, filter);

    /**
     * @tc.step: step3 check value of selectedTextStyle.
     */
    auto selectedTextStyle = json->GetObject("selectedTextStyle");
    ASSERT_NE(selectedTextStyle, nullptr);
    EXPECT_EQ(selectedTextStyle->GetString("color"), "#FFFF0000");
    auto selectedFont = selectedTextStyle->GetObject("font");
    ASSERT_NE(selectedFont, nullptr);
    EXPECT_EQ(selectedFont->GetString("size"), "10.00px");
    EXPECT_EQ(selectedFont->GetString("weight"), "FontWeight.Bold");

    /**
     * @tc.cases: case. cover call reset() and check selectedTextStyle.
     */
    pickerProperty->Reset();
    auto json2 = JsonUtil::Create(true);
    ASSERT_NE(json2, nullptr);
    pickerProperty->ToJsonValue(json2, filter);
    EXPECT_EQ(pickerProperty->GetSelectedTextStyle(), nullptr);
}

/**
 * @tc.name: TimePickerLayoutPropertyToJsonValue006
 * @tc.desc: Test TimePickerLayoutProperty SetDisappearTextStyle and call ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerLayoutPropertyToJsonValue006, TestSize.Level1)
{
    /**
     * @tc.step: step1. initialize LayoutProperty and TimePickerModelNG.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto timePickerModeNG = TimePickerModelNG::GetInstance();
    ASSERT_NE(timePickerModeNG, nullptr);

    /**
     * @tc.step: step2 Set SetDisappearTextStyle and call ToJsonValue().
     */
    PickerTextStyle data;
    data.fontSize = Dimension(10);
    data.textColor = Color::RED;
    data.fontWeight = Ace::FontWeight::BOLD;
    timePickerModeNG->SetDisappearTextStyle(theme, data);
    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    pickerProperty->ToJsonValue(json, filter);

    /**
     * @tc.step: step3 check property of disappearTextStyle.
     */
    auto disappearTextStyle = json->GetObject("disappearTextStyle");
    ASSERT_NE(disappearTextStyle, nullptr);
    EXPECT_EQ(disappearTextStyle->GetString("color"), "#FFFF0000");
    auto disappearFont = disappearTextStyle->GetObject("font");
    ASSERT_NE(disappearFont, nullptr);
    EXPECT_EQ(disappearFont->GetString("size"), "10.00px");
    EXPECT_EQ(disappearFont->GetString("weight"), "FontWeight.Bold");

    /**
     * @tc.cases: case. cover call reset() and check disappearTextStyle Property.
     */
    pickerProperty->Reset();
    auto json2 = JsonUtil::Create(true);
    ASSERT_NE(json2, nullptr);
    pickerProperty->ToJsonValue(json2, filter);
    EXPECT_EQ(pickerProperty->GetDisappearTextStyle(), nullptr);
    EXPECT_FALSE(pickerProperty->HasLoop());
}

/**
 * @tc.name: TimePickerLayoutPropertyToJsonValue007
 * @tc.desc: Test TimePickerLayoutProperty dateTimeOptions and call ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerLayoutPropertyToJsonValue007, TestSize.Level1)
{
    /**
    * @tc.step: step1. initialize LayoutProperty and TimePickerModelNG.
    */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    bool hasSecond = true;
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, hasSecond);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto timePickerModeNG = TimePickerModelNG::GetInstance();
    ASSERT_NE(timePickerModeNG, nullptr);

    /**
     * @tc.step: step2 Set dateTimeOptions and call ToJsonValue().
     */
    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    bool isUseMilitaryTime = true;
    pickerProperty->UpdateIsUseMilitaryTime(isUseMilitaryTime);
    ASSERT_NE(pickerProperty, nullptr);
    int32_t typeHour = static_cast<int32_t>(ZeroPrefixType::AUTO);
    int32_t typeMinute = static_cast<int32_t>(ZeroPrefixType::HIDE);
    int32_t typeSecond = static_cast<int32_t>(ZeroPrefixType::SHOW);
    pickerProperty->UpdatePrefixHour(typeHour);
    pickerProperty->UpdatePrefixMinute(typeMinute);
    pickerProperty->UpdatePrefixSecond(typeSecond);
    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    pickerProperty->ToJsonValue(json, filter);

    /**
     * @tc.cases: case. cover call isUseMilitaryTime is true and check dateTimeOptions Property.
     */
    auto timeOption = json->GetObject("dateTimeOptions");
    ASSERT_NE(timeOption, nullptr);
    EXPECT_EQ(timeOption->GetString("hour"), TimeFormat::GetHourFormat(typeHour, isUseMilitaryTime));
    EXPECT_EQ(timeOption->GetString("minute"), TimeFormat::GetMinuteFormat(typeMinute));
    EXPECT_EQ(timeOption->GetString("second"), TimeFormat::GetSecondFormat(typeSecond));

    /**
     * @tc.cases: case. cover call isUseMilitaryTime is false and check dateTimeOptions Property.
     */
    isUseMilitaryTime = false;
    pickerProperty->UpdateIsUseMilitaryTime(isUseMilitaryTime);
    auto json2 = JsonUtil::Create(true);
    ASSERT_NE(json2, nullptr);
    pickerProperty->ToJsonValue(json2, filter);

    auto timeOption2 = json2->GetObject("dateTimeOptions");
    ASSERT_NE(timeOption2, nullptr);
    EXPECT_EQ(timeOption2->GetString("hour"), TimeFormat::GetHourFormat(typeHour, isUseMilitaryTime));
    EXPECT_EQ(timeOption2->GetString("minute"), TimeFormat::GetMinuteFormat(typeMinute));
    EXPECT_EQ(timeOption2->GetString("second"), TimeFormat::GetSecondFormat(typeSecond));
}

/**
 * @tc.name: TimePickerLayoutPropertyToJsonValue008
 * @tc.desc: Test TimePickerLayoutProperty dateTimeOptions and call ToJsonValue.
 * @tc.type: FUNC
 */
 HWTEST_F(TimePickerPatternTestNg, TimePickerLayoutPropertyToJsonValue008, TestSize.Level1)
 {
     /**
     * @tc.step: step1. initialize LayoutProperty and TimePickerModelNG.
     */
     auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
     bool hasSecond = true;
     TimePickerModelNG::GetInstance()->CreateTimePicker(theme, hasSecond);
     auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
     ASSERT_NE(frameNode, nullptr);
     auto timePickerModeNG = TimePickerModelNG::GetInstance();
     ASSERT_NE(timePickerModeNG, nullptr);

     /**
      * @tc.step: step2 Set dateTimeOptions exception value and call ToJsonValue().
      */
     auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
     bool isUseMilitaryTime = true;
     pickerProperty->UpdateIsUseMilitaryTime(isUseMilitaryTime);
     ASSERT_NE(pickerProperty, nullptr);
     const int32_t typeHour = 6; // is not ZeroPrefixType
     const int32_t typeMinute = 6;
     const int32_t typeSecond = 6;
     pickerProperty->UpdatePrefixHour(typeHour);
     pickerProperty->UpdatePrefixMinute(typeMinute);
     pickerProperty->UpdatePrefixSecond(typeSecond);
     auto json = JsonUtil::Create(true);
     ASSERT_NE(json, nullptr);
     pickerProperty->ToJsonValue(json, filter);
 
     /**
      * @tc.cases: case. cover call isUseMilitaryTime is true and check dateTimeOptions Property.
      */
     auto timeOption = json->GetObject("dateTimeOptions");
     ASSERT_NE(timeOption, nullptr);
     EXPECT_EQ(timeOption->GetString("hour"), "");
     EXPECT_EQ(timeOption->GetString("minute"), "");
     EXPECT_EQ(timeOption->GetString("second"), "");
 }
} // namespace OHOS::Ace::NG
