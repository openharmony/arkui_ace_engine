/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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
#include "adapter/ohos/test/unittest/mock/common.h"
#include "adapter/ohos/test/unittest/mock/mock_event_report_data.h"
#include "frameworks/core/common/ace_application_info.h"

using namespace testing::ext;

namespace OHOS::Ace {
namespace {
const EventInfo EVENT_INFO = { .eventType = "EventReport_type", .pageUrl = "adapter/ohos/osal" };
const std::string MAX_PACKAGE_NAME_INFO("EventReportTest_EventReportTest_EventReportTest_EventReportTest_"
    "EventReportTest_EventReportTest_EventReportTest");
} // namespace

class EventReportTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
    RefPtr<MockEventReportData> eventReportData_;
};

void EventReportTest::SetUpTestCase() {}

void EventReportTest::TearDownTestCase() {}

void EventReportTest::SetUp()
{
    eventReportData_ = AceType::MakeRefPtr<MockEventReportData>();
    AceApplicationInfo::GetInstance().SetPackageName("EventReportTest");
}

void EventReportTest::TearDown()
{
    eventReportData_ = nullptr;
}

/**
 * @tc.name: EventReportTest_SendEvent_001
 * @tc.desc: Verify whether the SendEvent function is called successfully
 * @tc.type: FUNC
 */
HWTEST_F(EventReportTest, EventReportTest_SendEvent_001, TestSize.Level1)
{
    CHECK_PTR_NULL_VOID(eventReportData_);
    auto result = eventReportData_->SendEvent(EVENT_INFO);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: EventReportTest_SendEvent_002
 * @tc.desc: Verify whether the SendEvent function is successfully called when the super long eventinfo
 * @tc.type: FUNC
 */
HWTEST_F(EventReportTest, EventReportTest_SendEvent_002, TestSize.Level1)
{
    CHECK_PTR_NULL_VOID(eventReportData_);
    auto result = eventReportData_->SendEvent(EVENT_INFO);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: EventReportTest_SendJsCardRenderTimeEvent_001
 * @tc.desc: Verify whether the SendJsCardRenderTimeEvent function is called successfully
 * @tc.type: FUNC
 */
HWTEST_F(EventReportTest, EventReportTest_SendJsCardRenderTimeEvent_001, TestSize.Level1)
{
    CHECK_PTR_NULL_VOID(eventReportData_);
    uint64_t timeDelay = 0;
    auto result = eventReportData_->SendJsCardRenderTimeEvent("sessionID", "timeType", timeDelay);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: EventReportTest_SendComponentException_001
 * @tc.desc: Verify whether the SendComponentException function is called successfully
 * @tc.type: FUNC
 */
HWTEST_F(EventReportTest, EventReportTest_SendComponentException_001, TestSize.Level1)
{
    CHECK_PTR_NULL_VOID(eventReportData_);
    auto result = eventReportData_->SendComponentException(ComponentExcepType::DOM_NODE_NOT_FOUND);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: EventReportTest_SendAPIChannelException_001
 * @tc.desc: Verify whether the SendAPIChannelException function is called successfully
 * @tc.type: FUNC
 */
HWTEST_F(EventReportTest, EventReportTest_SendAPIChannelException_001, TestSize.Level1)
{
    CHECK_PTR_NULL_VOID(eventReportData_);
    auto result = eventReportData_->SendAPIChannelException(APIChannelExcepType::SET_FUNCTION_ERR);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: EventReportTest_SendJsException_001
 * @tc.desc: Verify whether the SendJsException function is called successfully
 * @tc.type: FUNC
 */
HWTEST_F(EventReportTest, EventReportTest_SendJsException_001, TestSize.Level1)
{
    CHECK_PTR_NULL_VOID(eventReportData_);
    auto result = eventReportData_->SendJsException(JsExcepType::CREATE_DOM_BODY_ERR);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: EventReportTest_SendAnimationException_001
 * @tc.desc: Verify whether the SendAnimationException function is called successfully
 * @tc.type: FUNC
 */
HWTEST_F(EventReportTest, EventReportTest_SendAnimationException_001, TestSize.Level1)
{
    CHECK_PTR_NULL_VOID(eventReportData_);
    auto result = eventReportData_->SendAnimationException(AnimationExcepType::ANIMATION_PAGE_ERR);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: EventReportTest_SendInternalException_001
 * @tc.desc: Verify whether the SendInternalException function is called successfully
 * @tc.type: FUNC
 */
HWTEST_F(EventReportTest, EventReportTest_SendInternalException_001, TestSize.Level1)
{
    CHECK_PTR_NULL_VOID(eventReportData_);
    auto result = eventReportData_->SendInternalException(InternalExcepType::CHANGE_LOCALE_ERR);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: EventReportTest_SendAccessibilityException_001
 * @tc.desc: Verify whether the SendAccessibilityException function is called successfully
 * @tc.type: FUNC
 */
HWTEST_F(EventReportTest, EventReportTest_SendAccessibilityException_001, TestSize.Level1)
{
    CHECK_PTR_NULL_VOID(eventReportData_);
    auto result = eventReportData_->SendAccessibilityException(AccessibilityExcepType::GET_NODE_ERR);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: EventReportTest_SendFormException_001
 * @tc.desc: Verify whether the SendAccessibilityException function is called successfully
 * @tc.type: FUNC
 */
HWTEST_F(EventReportTest, EventReportTest_SendFormException_001, TestSize.Level1)
{
    CHECK_PTR_NULL_VOID(eventReportData_);
    auto result = eventReportData_->SendFormException(FormExcepType::UPDATE_PAGE_ERR);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: EventReportTest_JsEventReport_001
 * @tc.desc: Verify whether the JsEventReport function is called successfully
 * @tc.type: FUNC
 */
HWTEST_F(EventReportTest, EventReportTest_JsEventReport_001, TestSize.Level1)
{
    CHECK_PTR_NULL_VOID(eventReportData_);
    int32_t eventType = -1;
    std::string jsonStr = "bundle_name: EventReportTest, test_dir: event_report_test,"
        "test_case: EventReportTest_JsEventReport_001";
    auto result = eventReportData_->JsEventReport(eventType, jsonStr);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: EventReportTest_JsErrReport_001
 * @tc.desc: Verify whether the JsErrReport function is called successfully
 * @tc.type: FUNC
 */
HWTEST_F(EventReportTest, EventReportTest_JsErrReport_001, TestSize.Level1)
{
    CHECK_PTR_NULL_VOID(eventReportData_);
    std::string packageName = "EventReportTest";
    std::string reason = "reason";
    std::string summary = "summary";
    auto result = eventReportData_->JsErrReport(packageName, reason, summary);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: EventReportTest_ANRRawReport_001
 * @tc.desc: Verify whether the ANRRawReport function is called successfully
 * @tc.type: FUNC
 */
HWTEST_F(EventReportTest, EventReportTest_ANRRawReport_001, TestSize.Level1)
{
    CHECK_PTR_NULL_VOID(eventReportData_);
    int32_t default_uid = 1000;
    auto result = eventReportData_->ANRRawReport(RawEventType::WARNING, default_uid, "EventReportTest",
        "EventReportTest", " ");
    EXPECT_TRUE(result);

    result = eventReportData_->ANRRawReport(RawEventType::FREEZE, default_uid, "EventReportTest",
        "EventReportTest", " ");
    EXPECT_TRUE(result);

    result = eventReportData_->ANRRawReport(RawEventType::RECOVER, default_uid, "EventReportTest",
        "EventReportTest", " ");
    EXPECT_TRUE(result);
}

/**
 * @tc.name: EventReportTest_ANRShowDialog_001
 * @tc.desc: Verify whether the ANRShowDialog function is called successfully
 * @tc.type: FUNC
 */
HWTEST_F(EventReportTest, EventReportTest_ANRShowDialog_001, TestSize.Level1)
{
    CHECK_PTR_NULL_VOID(eventReportData_);
    int32_t default_uid = 1000;
    auto result = eventReportData_->ANRShowDialog(default_uid, "EventReportTest", "EventReportTest", "");
    EXPECT_TRUE(result);
}
} // namespace OHOS::Ace
