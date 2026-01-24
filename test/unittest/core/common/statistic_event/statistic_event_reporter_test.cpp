/*
 * Copyright (c) 2025 iSoftStone Information Technology (Group) Co.,Ltd.
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

#define protected public
#define private public

#include "core/common/ace_application_info.h"
#include "core/common/statistic_event_reporter.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace {
constexpr int32_t MAX_PENDING_EVENT_COUNT = 20;
}
class StatisticEventReporterTest : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void StatisticEventReporterTest::SetUpTestSuite()
{
}

void StatisticEventReporterTest::TearDownTestSuite()
{
}

/**
 * @tc.name: StatisticEventReporterTest
 * @tc.desc: Test ConvertToEventName
 * @tc.type: FUNC
 */
HWTEST_F(StatisticEventReporterTest, ConvertToEventName001, TestSize.Level1)
{
    auto reporter = std::make_shared<StatisticEventReporter>();
    ASSERT_TRUE(reporter != nullptr);
    StatisticEventInfo event = reporter->ConvertToEvent(StatisticEventType::FA_APP_START);
    EXPECT_EQ(event.subEventName, "FA_APP_START");
}

/**
 * @tc.name: StatisticEventReporterTest
 * @tc.desc: Test ConvertToEventName of XCOMPONENT
 * @tc.type: FUNC
 */
HWTEST_F(StatisticEventReporterTest, ConvertToEventName002, TestSize.Level1)
{
    auto reporter = std::make_shared<StatisticEventReporter>();
    ASSERT_TRUE(reporter != nullptr);
    StatisticEventInfo event = reporter->ConvertToEvent(StatisticEventType::XCOMPONENT_TYPE_USE_STRING);
    EXPECT_EQ(event.eventName, "XCOMPONENT");
    EXPECT_EQ(event.subEventName, "TYPE_USE_STRING");

    event = reporter->ConvertToEvent(StatisticEventType::XCOMPONENT_SET_SURFACE_SIZE);
    EXPECT_EQ(event.eventName, "XCOMPONENT");
    EXPECT_EQ(event.subEventName, "SET_SURFACE_SIZE");

    event = reporter->ConvertToEvent(StatisticEventType::XCOMPONENT_TYPE_COMPONENT);
    EXPECT_EQ(event.eventName, "XCOMPONENT");
    EXPECT_EQ(event.subEventName, "TYPE_COMPONENT");

    event = reporter->ConvertToEvent(StatisticEventType::XCOMPONENT_TYPE_NODE);
    EXPECT_EQ(event.eventName, "XCOMPONENT");
    EXPECT_EQ(event.subEventName, "TYPE_NODE");

    event = reporter->ConvertToEvent(StatisticEventType::XCOMPONENT_NATIVE_ATTACH_NATIVE_ROOT_NODE);
    EXPECT_EQ(event.eventName, "XCOMPONENT");
    EXPECT_EQ(event.subEventName, "NATIVE_ATTACH_NATIVE_ROOT_NODE");

    event = reporter->ConvertToEvent(StatisticEventType::XCOMPONENT_NATIVE_DETACH_NATIVE_ROOT_NODE);
    EXPECT_EQ(event.eventName, "XCOMPONENT");
    EXPECT_EQ(event.subEventName, "NATIVE_DETACH_NATIVE_ROOT_NODE");

    event = reporter->ConvertToEvent(StatisticEventType::XCOMPONENT_SET_ATTRIBUTE_NODE_TYPE);
    EXPECT_EQ(event.eventName, "XCOMPONENT");
    EXPECT_EQ(event.subEventName, "SET_ATTRIBUTE_NODE_TYPE");

    event = reporter->ConvertToEvent(StatisticEventType::XCOMPONENT_SET_ATTRIBUTE_NODE_SURFACE_SIZE);
    EXPECT_EQ(event.eventName, "XCOMPONENT");
    EXPECT_EQ(event.subEventName, "SET_ATTRIBUTE_NODE_SURFACE_SIZE");
}

/**
 * @tc.name: StatisticEventReporterTest
 * @tc.desc: Test ConvertToEventName of CANVAS
 * @tc.type: FUNC
 */
HWTEST_F(StatisticEventReporterTest, ConvertToEventName003, TestSize.Level1)
{
    auto reporter = std::make_shared<StatisticEventReporter>();
    ASSERT_TRUE(reporter != nullptr);
    StatisticEventInfo event = reporter->ConvertToEvent(StatisticEventType::CANVAS_FILL_STYLE_GETTER);
    EXPECT_EQ(event.eventName, "CANVAS");
    EXPECT_EQ(event.subEventName, "FILL_STYLE_GETTER");

    event = reporter->ConvertToEvent(StatisticEventType::CANVAS_LINE_WIDTH_GETTER);
    EXPECT_EQ(event.eventName, "CANVAS");
    EXPECT_EQ(event.subEventName, "LINE_WIDTH_GETTER");

    event = reporter->ConvertToEvent(StatisticEventType::CANVAS_STROKE_STYLE_GETTER);
    EXPECT_EQ(event.eventName, "CANVAS");
    EXPECT_EQ(event.subEventName, "STROKE_STYLE_GETTER");

    event = reporter->ConvertToEvent(StatisticEventType::CANVAS_LINE_CAP_GETTER);
    EXPECT_EQ(event.eventName, "CANVAS");
    EXPECT_EQ(event.subEventName, "LINE_CAP_GETTER");

    event = reporter->ConvertToEvent(StatisticEventType::CANVAS_LINE_JOIN_GETTER);
    EXPECT_EQ(event.eventName, "CANVAS");
    EXPECT_EQ(event.subEventName, "LINE_JOIN_GETTER");

    event = reporter->ConvertToEvent(StatisticEventType::CANVAS_MITER_LIMIT_GETTER);
    EXPECT_EQ(event.eventName, "CANVAS");
    EXPECT_EQ(event.subEventName, "MITER_LIMIT_GETTER");

    event = reporter->ConvertToEvent(StatisticEventType::CANVAS_FONT_GETTER);
    EXPECT_EQ(event.eventName, "CANVAS");
    EXPECT_EQ(event.subEventName, "FONT_GETTER");

    event = reporter->ConvertToEvent(StatisticEventType::CANVAS_TEXT_ALIGN_GETTER);
    EXPECT_EQ(event.eventName, "CANVAS");
    EXPECT_EQ(event.subEventName, "TEXT_ALIGN_GETTER");

    event = reporter->ConvertToEvent(StatisticEventType::CANVAS_TEXT_BASELINE_GETTER);
    EXPECT_EQ(event.eventName, "CANVAS");
    EXPECT_EQ(event.subEventName, "TEXT_BASELINE_GETTER");

    event = reporter->ConvertToEvent(StatisticEventType::CANVAS_GLOBAL_ALPHA_GETTER);
    EXPECT_EQ(event.eventName, "CANVAS");
    EXPECT_EQ(event.subEventName, "GLOBAL_ALPHA_GETTER");

    event = reporter->ConvertToEvent(StatisticEventType::CANVAS_LINE_DASH_OFFSET_GETTER);
    EXPECT_EQ(event.eventName, "CANVAS");
    EXPECT_EQ(event.subEventName, "LINE_DASH_OFFSET_GETTER");

    event = reporter->ConvertToEvent(StatisticEventType::CANVAS_GLOBAL_COMPOSITE_OPERATION_GETTER);
    EXPECT_EQ(event.eventName, "CANVAS");
    EXPECT_EQ(event.subEventName, "GLOBAL_COMPOSITE_OPERATION_GETTER");

    event = reporter->ConvertToEvent(StatisticEventType::CANVAS_SHADOW_BLUR_GETTER);
    EXPECT_EQ(event.eventName, "CANVAS");
    EXPECT_EQ(event.subEventName, "SHADOW_BLUR_GETTER");

    event = reporter->ConvertToEvent(StatisticEventType::CANVAS_SHADOW_COLOR_GETTER);
    EXPECT_EQ(event.eventName, "CANVAS");
    EXPECT_EQ(event.subEventName, "SHADOW_COLOR_GETTER");

    event = reporter->ConvertToEvent(StatisticEventType::CANVAS_SHADOW_OFFSET_X_GETTER);
    EXPECT_EQ(event.eventName, "CANVAS");
    EXPECT_EQ(event.subEventName, "SHADOW_OFFSET_X_GETTER");

    event = reporter->ConvertToEvent(StatisticEventType::CANVAS_SHADOW_OFFSET_Y_GETTER);
    EXPECT_EQ(event.eventName, "CANVAS");
    EXPECT_EQ(event.subEventName, "SHADOW_OFFSET_Y_GETTER");

    event = reporter->ConvertToEvent(StatisticEventType::CANVAS_IMAGE_SMOOTHING_ENABLE_GETTER);
    EXPECT_EQ(event.eventName, "CANVAS");
    EXPECT_EQ(event.subEventName, "IMAGE_SMOOTHING_ENABLE_GETTER");

    event = reporter->ConvertToEvent(StatisticEventType::CANVAS_IMAGE_SMOOTHING_QUALITY_GETTER);
    EXPECT_EQ(event.eventName, "CANVAS");
    EXPECT_EQ(event.subEventName, "IMAGE_SMOOTHING_QUALITY_GETTER");

    event = reporter->ConvertToEvent(StatisticEventType::CANVAS_DIRECTION_GETTER);
    EXPECT_EQ(event.eventName, "CANVAS");
    EXPECT_EQ(event.subEventName, "DIRECTION_GETTER");

    event = reporter->ConvertToEvent(StatisticEventType::CANVAS_FILTER_GETTER);
    EXPECT_EQ(event.eventName, "CANVAS");
    EXPECT_EQ(event.subEventName, "FILTER_GETTER");

    event = reporter->ConvertToEvent(StatisticEventType::CANVAS_LETTER_SPACING_GETTER);
    EXPECT_EQ(event.eventName, "CANVAS");
    EXPECT_EQ(event.subEventName, "LETTER_SPACING_GETTER");
}

/**
 * @tc.name: StatisticEventReporterTest
 * @tc.desc: Test ConvertToEventName of CANVAS
 * @tc.type: FUNC
 */
HWTEST_F(StatisticEventReporterTest, ConvertToEventName004, TestSize.Level1)
{
    auto reporter = std::make_shared<StatisticEventReporter>();
    ASSERT_TRUE(reporter != nullptr);
    StatisticEventInfo event = reporter->ConvertToEvent(StatisticEventType::CANVAS_TASKS_OVERFLOW);
    EXPECT_EQ(event.eventName, "CANVAS");
    EXPECT_EQ(event.subEventName, "TASKS_OVERFLOW");

    event = reporter->ConvertToEvent(StatisticEventType::CANVAS_BITMAP_SIZE_EXCEED_LIMIT);
    EXPECT_EQ(event.eventName, "CANVAS");
    EXPECT_EQ(event.subEventName, "BITMAP_SIZE_EXCEED_LIMIT");

    event = reporter->ConvertToEvent(StatisticEventType::CANVAS_CUSTOM_FONT);
    EXPECT_EQ(event.eventName, "CANVAS");
    EXPECT_EQ(event.subEventName, "CUSTOM_FONT");

    event = reporter->ConvertToEvent(StatisticEventType::CANVAS_NAN_INFINITY_PARAM);
    EXPECT_EQ(event.eventName, "CANVAS");
    EXPECT_EQ(event.subEventName, "NAN_INFINITY_PARAM");

    event = reporter->ConvertToEvent(StatisticEventType::CANVAS_NINE_PARAM_DRAWIMAGE);
    EXPECT_EQ(event.eventName, "CANVAS");
    EXPECT_EQ(event.subEventName, "NINE_PARAM_DRAWIMAGE");

    event = reporter->ConvertToEvent(StatisticEventType::CANVAS_GLOBAL_ALPHA_MINUS_ONE);
    EXPECT_EQ(event.eventName, "CANVAS");
    EXPECT_EQ(event.subEventName, "GLOBAL_ALPHA_MINUS_ONE");
}

/**
 * @tc.name: StatisticEventReporterTest
 * @tc.desc: Test SendEvent
 * @tc.type: FUNC
 */
HWTEST_F(StatisticEventReporterTest, SendEvent001, TestSize.Level1)
{
    auto reporter = std::make_shared<StatisticEventReporter>();
    ASSERT_TRUE(reporter != nullptr);
    reporter->SendEvent(StatisticEventType::FA_APP_START);
    EXPECT_EQ(reporter->statisitcEventMap_.size(), 1);
    EXPECT_EQ(reporter->totalEventCount_, 1);
    reporter->SendEvent(StatisticEventType::FA_APP_START);
    EXPECT_EQ(reporter->statisitcEventMap_[StatisticEventType::FA_APP_START].eventCount, 2);
    EXPECT_EQ(reporter->totalEventCount_, 2);
}

/**
 * @tc.name: StatisticEventReporterTest
 * @tc.desc: Test ReportStatisticEvents
 * @tc.type: FUNC
 */
HWTEST_F(StatisticEventReporterTest, ReportStatisticEvents001, TestSize.Level1)
{
    auto reporter = std::make_shared<StatisticEventReporter>();
    ASSERT_TRUE(reporter != nullptr);
    std::map<StatisticEventType, StatisticEventInfo> events;
    reporter->ReportStatisticEvents(events);
    EXPECT_EQ(reporter->appInfo_.bundleName, AceApplicationInfo::GetInstance().GetPackageName());
}

/**
 * @tc.name: StatisticEventReporterTest
 * @tc.desc: Test TryReportStatisticEvents
 * @tc.type: FUNC
 */
HWTEST_F(StatisticEventReporterTest, TryReportStatisticEvents001, TestSize.Level1)
{
    auto reporter = std::make_shared<StatisticEventReporter>();
    ASSERT_TRUE(reporter != nullptr);
    reporter->totalEventCount_ = MAX_PENDING_EVENT_COUNT - 1;
    reporter->TryReportStatisticEvents(nullptr);
    EXPECT_EQ(reporter->totalEventCount_, MAX_PENDING_EVENT_COUNT - 1);
}

/**
 * @tc.name: StatisticEventReporterTest
 * @tc.desc: Test ForceReportStatisticEvents
 * @tc.type: FUNC
 */
HWTEST_F(StatisticEventReporterTest, ForceReportStatisticEvents001, TestSize.Level1)
{
    auto reporter = std::make_shared<StatisticEventReporter>();
    ASSERT_TRUE(reporter != nullptr);
    reporter->SendEvent(StatisticEventType::FA_APP_START);

    reporter->ForceReportStatisticEvents();
    EXPECT_EQ(reporter->totalEventCount_, 0);
}
} // namespace OHOS::Ace
