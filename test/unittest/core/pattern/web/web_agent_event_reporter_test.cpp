/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/unittest/core/pattern/web/mock_web_delegate.h"

#include "adapter/ohos/entrance/ace_container.h"
#include "core/components/web/resource/web_delegate.h"
#include "core/components/web/web_property.h"
#include "core/components_ng/pattern/web/web_pattern.h"
#include "frameworks/core/pipeline/pipeline_base.h"
#undef protected
#undef private

#include "interfaces/inner_api/ui_session/ui_session_manager.h"

#include "core/components_ng/base/view_stack_processor.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
RefPtr<WebPattern> g_webPattern = nullptr;

class MockReporterForSpecificEvent : public WebAgentEventReporter {
public:
    using WebAgentEventReporter::WebAgentEventReporter;
    MOCK_METHOD(RectF, ConvertToWindow, (const RectF& rect, bool addComponentOffset), (override));
    MOCK_METHOD(void, ReportEventImediately, (const std::shared_ptr<InspectorJsonValue>& eventJson), (override));
    MOCK_METHOD(void, ProcessScrollQueue, (), (override));
};

class MockReporterForAddEvent : public WebAgentEventReporter {
public:
    using WebAgentEventReporter::WebAgentEventReporter;
    MOCK_METHOD(void, AddTapEvent, (const std::unique_ptr<JsonValue>& tapEventJson), (override));
    MOCK_METHOD(void, AddLongPressEvent, (const std::unique_ptr<JsonValue>& longPressEventJson), (override));
    MOCK_METHOD(void, AddPinchEvent, (const std::unique_ptr<JsonValue>& pinchEventJson), (override));
    MOCK_METHOD(void, AddScrollEvent, (const std::unique_ptr<JsonValue>& scrollEventJson), (override));
};

// A helper mock that overrides Update and Handle so the real ProcessScrollQueue
// implementation can be tested while controlling Update/Handle outcomes.
class MockReporterUpdateHandle : public WebAgentEventReporter {
public:
    using WebAgentEventReporter::WebAgentEventReporter;
    MOCK_METHOD(bool, UpdateScrollEventInfoFromTree, (ScrollEventInfo & info), (override));
    MOCK_METHOD(ScrollEndEventAction, HandleUpdatedScrollEndEvent, (ScrollEventInfo & info), (override));
};
} // namespace

class WebAgentEventReporterTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void WebAgentEventReporterTest::SetUpTestCase()
{
#ifdef OHOS_STANDARD_SYSTEM
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;

    std::string src = "web_test";
    RefPtr<WebController> controller = AceType::MakeRefPtr<WebController>();
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::WEB_ETS_TAG, nodeId, [src, controller]() { return AceType::MakeRefPtr<WebPattern>(src, controller); });
    stack->Push(frameNode);

    g_webPattern = frameNode->GetPattern<WebPattern>();
    CHECK_NULL_VOID(g_webPattern);
    g_webPattern->OnModifyDone();
#endif
}

void WebAgentEventReporterTest::TearDownTestCase()
{
#ifdef OHOS_STANDARD_SYSTEM
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
    g_webPattern = nullptr;
#endif
}

void WebAgentEventReporterTest::SetUp()
{
#ifdef OHOS_STANDARD_SYSTEM
    OHOS::Ace::SetReturnStatus("");
#endif
}

void WebAgentEventReporterTest::TearDown()
{
#ifdef OHOS_STANDARD_SYSTEM
    OHOS::Ace::SetReturnStatus("");
#endif
}

/**
 * @tc.name: GetAgentEventReporter
 * @tc.desc: Test GetAgentEventReporter.
 * @tc.type: FUNC
 */
HWTEST_F(WebAgentEventReporterTest, GetAgentEventReporter, TestSize.Level0)
{
#ifdef OHOS_STANDARD_SYSTEM
    EXPECT_NE(g_webPattern->GetAgentEventReporter(), nullptr);
    EXPECT_NE(g_webPattern->GetAgentEventReporter(), nullptr);
#endif
}

/**
 * @tc.name: AddEvent
 * @tc.desc: Test AddEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebAgentEventReporterTest, AddEvent, TestSize.Level0)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto reporter = AceType::MakeRefPtr<MockReporterForAddEvent>(AceType::WeakClaim(AceType::RawPtr(g_webPattern)));
    // invalid json
    {
        EXPECT_CALL(*reporter, AddTapEvent).Times(0);
        EXPECT_CALL(*reporter, AddLongPressEvent).Times(0);
        EXPECT_CALL(*reporter, AddPinchEvent).Times(0);
        EXPECT_CALL(*reporter, AddScrollEvent).Times(0);
        reporter->AddEvent("");
        reporter->AddEvent("[]");
    }
    // switch
    {
        EXPECT_CALL(*reporter, AddTapEvent).Times(1);
        EXPECT_CALL(*reporter, AddLongPressEvent).Times(1);
        EXPECT_CALL(*reporter, AddPinchEvent).Times(1);
        EXPECT_CALL(*reporter, AddScrollEvent).Times(2);
        reporter->AddEvent(R"({"EventType":"Tap"})");
        reporter->AddEvent(R"({"EventType":"LongPress"})");
        reporter->AddEvent(R"({"EventType":"PinchEnd"})");
        reporter->AddEvent(R"({"EventType":"ScrollStart"})");
        reporter->AddEvent(R"({"EventType":"ScrollEnd"})");
        // unknown
        reporter->AddEvent(R"({"EventType":"Unknown"})");
    }
#endif
}

/**
 * @tc.name: AddTapEvent
 * @tc.desc: Test AddTapEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebAgentEventReporterTest, AddTapEvent, TestSize.Level0)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto reporter =
        AceType::MakeRefPtr<MockReporterForSpecificEvent>(AceType::WeakClaim(AceType::RawPtr(g_webPattern)));
    // no need to check json validity
    {
        EXPECT_CALL(*reporter, ConvertToWindow).Times(0);
        reporter->AddTapEvent(JsonUtil::ParseJsonString(R"({"EventType": "Tap"})"));
        reporter->AddTapEvent(JsonUtil::ParseJsonString(R"({"EventType": "Tap", "point": 1})"));
        reporter->AddTapEvent(JsonUtil::ParseJsonString(R"({"EventType": "Tap", "point": [1]})"));
    }
    {
        EXPECT_CALL(*reporter, ConvertToWindow).Times(1);
        EXPECT_CALL(*reporter, ReportEventImediately).Times(1);
        reporter->AddTapEvent(JsonUtil::ParseJsonString(R"({"EventType": "Tap", "point": [1, 2]})"));
    }
#endif
}

/**
 * @tc.name: AddLongPressEvent
 * @tc.desc: Test AddLongPressEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebAgentEventReporterTest, AddLongPressEvent, TestSize.Level0)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto reporter =
        AceType::MakeRefPtr<MockReporterForSpecificEvent>(AceType::WeakClaim(AceType::RawPtr(g_webPattern)));
    // no need to check json validity
    {
        EXPECT_CALL(*reporter, ConvertToWindow).Times(0);
        reporter->AddLongPressEvent(JsonUtil::ParseJsonString(R"({"EventType": "LongPress"})"));
        reporter->AddLongPressEvent(JsonUtil::ParseJsonString(R"({"EventType": "LongPress", "point": {}})"));
        reporter->AddLongPressEvent(JsonUtil::ParseJsonString(R"({"EventType": "LongPress", "point": [1, 2, 3]})"));
    }
    {
        EXPECT_CALL(*reporter, ConvertToWindow).Times(1);
        EXPECT_CALL(*reporter, ReportEventImediately).Times(1);
        reporter->AddLongPressEvent(JsonUtil::ParseJsonString(R"({"EventType": "LongPress", "point": [1, 2]})"));
    }
#endif
}

/**
 * @tc.name: AddPinchEvent
 * @tc.desc: Test AddPinchEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebAgentEventReporterTest, AddPinchEvent, TestSize.Level0)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto reporter =
        AceType::MakeRefPtr<MockReporterForSpecificEvent>(AceType::WeakClaim(AceType::RawPtr(g_webPattern)));
    // no need to check json validity
    {
        EXPECT_CALL(*reporter, ReportEventImediately).Times(1);
        reporter->AddPinchEvent(JsonUtil::ParseJsonString(R"({"EventType": "PinchEnd"})"));
    }
#endif
}

/**
 * @tc.name: ConvertToWindow
 * @tc.desc: Test ConvertToWindow.
 * @tc.type: FUNC
 */
HWTEST_F(WebAgentEventReporterTest, ConvertToWindow, TestSize.Level0)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto reporter = AceType::MakeRefPtr<WebAgentEventReporter>(AceType::WeakClaim(AceType::RawPtr(g_webPattern)));
    RectF rect(0.0f, 0.0f, 100.0f, 200.0f);
    double old = g_webPattern->density_;
    g_webPattern->density_ = 2.0f;
    RectF rectInScreen = reporter->ConvertToWindow(rect, false);
    EXPECT_TRUE(NearEqual(rectInScreen.Width(), 200.0f));
    EXPECT_TRUE(NearEqual(rectInScreen.Height(), 400.0f));

    rectInScreen = reporter->ConvertToWindow(rectInScreen, true);
    EXPECT_TRUE(NearEqual(rectInScreen.Width(), 400.0f));
    EXPECT_TRUE(NearEqual(rectInScreen.Height(), 800.0f));

    g_webPattern->density_ = old;
#endif
}

/**
 * @tc.name: AddScrollEvent
 * @tc.desc: Test AddScrollEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebAgentEventReporterTest, AddScrollEvent, TestSize.Level0)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto reporter =
        AceType::MakeRefPtr<MockReporterForSpecificEvent>(AceType::WeakClaim(AceType::RawPtr(g_webPattern)));
    // no need to check json validity
    {
        EXPECT_CALL(*reporter, ConvertToWindow).Times(0);
        EXPECT_CALL(*reporter, ProcessScrollQueue).Times(0);
        reporter->AddScrollEvent(JsonUtil::ParseJsonString(R"({"EventType": "ScrollStart"})"));
        reporter->AddScrollEvent(JsonUtil::ParseJsonString(R"({"EventType": "ScrollStart", "offset": "hello"})"));
        reporter->AddScrollEvent(JsonUtil::ParseJsonString(R"({"EventType": "ScrollEnd", "offset": []})"));
    }
    {
        EXPECT_CALL(*reporter, ConvertToWindow(_, ::testing::Eq(false))).Times(1);
        EXPECT_CALL(*reporter, ProcessScrollQueue).Times(1);
        reporter->AddScrollEvent(JsonUtil::ParseJsonString(R"({"EventType": "ScrollEnd", "offset": [1, 2]})"));
        int cnt = 0;
        for (; !reporter->scrollQueue_.empty(); reporter->scrollQueue_.pop()) {
            ++cnt;
        }
        EXPECT_EQ(cnt, 1);
    }
#endif
}

/**
 * @tc.name: ProcessScrollQueue_AlreadyProcessing
 * @tc.desc: When already processing, function should return immediately.
 * @tc.type: FUNC
 */
HWTEST_F(WebAgentEventReporterTest, ProcessScrollQueue_AlreadyProcessing, TestSize.Level0)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto reporter = AceType::MakeRefPtr<WebAgentEventReporter>(AceType::WeakClaim(AceType::RawPtr(g_webPattern)));
    // set processing to true and push an item
    reporter->processingScroll_ = true;
    WebAgentEventReporter::ScrollEventInfo info;
    info.eventType = "ScrollStart";
    info.id = 1;
    info.scrollRect = RectF(1.0, 2.0, 0.0, 0.0);
    reporter->scrollQueue_.push(info);

    reporter->ProcessScrollQueue();

    // should have returned immediately, leaving queue and processing flag unchanged
    EXPECT_TRUE(reporter->processingScroll_);
    EXPECT_EQ(static_cast<size_t>(1), reporter->scrollQueue_.size());
#endif
}

/**
 * @tc.name: ProcessScrollQueue_EmptyQueue
 * @tc.desc: When queue is empty, should log and return without changing state.
 * @tc.type: FUNC
 */
HWTEST_F(WebAgentEventReporterTest, ProcessScrollQueue_EmptyQueue, TestSize.Level0)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto reporter = AceType::MakeRefPtr<WebAgentEventReporter>(AceType::WeakClaim(AceType::RawPtr(g_webPattern)));
    reporter->processingScroll_ = false;
    // ensure queue empty
    while (!reporter->scrollQueue_.empty())
        reporter->scrollQueue_.pop();

    reporter->ProcessScrollQueue();

    EXPECT_FALSE(reporter->processingScroll_);
    EXPECT_EQ(static_cast<size_t>(0), reporter->scrollQueue_.size());
#endif
}

/**
 * @tc.name: ProcessScrollQueue_Continue
 * @tc.desc: When a scroll start event is processed, the queue should advance.
 * @tc.type: FUNC
 */
HWTEST_F(WebAgentEventReporterTest, ProcessScrollQueue_Continue, TestSize.Level0)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto reporter = AceType::MakeRefPtr<MockReporterUpdateHandle>(AceType::WeakClaim(AceType::RawPtr(g_webPattern)));
    WebAgentEventReporter::ScrollEventInfo info;
    info.eventType = "ScrollStart";
    info.id = 10;
    info.scrollRect = RectF(3.0, 4.0, 0.0, 0.0);
    reporter->scrollQueue_.push(info);

    reporter->processingScroll_ = true;

    EXPECT_CALL(*reporter, UpdateScrollEventInfoFromTree(_)).Times(1).WillOnce(Return(false));
    EXPECT_CALL(*reporter, HandleUpdatedScrollEndEvent(_)).Times(0);

    reporter->ContinueScrollProcessing();

    EXPECT_FALSE(reporter->processingScroll_);
    EXPECT_EQ(static_cast<size_t>(0), reporter->scrollQueue_.size());
#endif
}

/**
 * @tc.name: ProcessScrollQueue_ScrollStart
 * @tc.desc: When a scroll start event is processed, the queue should advance.
 * @tc.type: FUNC
 */
HWTEST_F(WebAgentEventReporterTest, ProcessScrollQueue_StartEvent, TestSize.Level0)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto reporter = AceType::MakeRefPtr<MockReporterUpdateHandle>(AceType::WeakClaim(AceType::RawPtr(g_webPattern)));
    WebAgentEventReporter::ScrollEventInfo info;
    info.eventType = "ScrollStart";
    info.id = 10;
    info.scrollRect = RectF(3.0, 4.0, 0.0, 0.0);
    reporter->scrollQueue_.push(info);

    EXPECT_CALL(*reporter, UpdateScrollEventInfoFromTree(_)).Times(1).WillOnce(Return(true));
    EXPECT_CALL(*reporter, HandleUpdatedScrollEndEvent(_)).Times(0);
    reporter->ProcessScrollQueue();

    EXPECT_FALSE(reporter->processingScroll_);
    EXPECT_EQ(static_cast<size_t>(0), reporter->scrollQueue_.size());
#endif
}

/**
 * @tc.name: ProcessScrollQueue_EndEventDrop
 * @tc.desc: When an updated end event is processed and HandleUpdatedScrollEndEvent returns DROP,
 *        the event should be dropped and the queue should advance.
 * @tc.type: FUNC
 */
HWTEST_F(WebAgentEventReporterTest, ProcessScrollQueue_EndEventDrop, TestSize.Level0)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto reporter = AceType::MakeRefPtr<MockReporterUpdateHandle>(AceType::WeakClaim(AceType::RawPtr(g_webPattern)));
    WebAgentEventReporter::ScrollEventInfo info;
    info.eventType = "ScrollEnd";
    info.id = 10;
    info.scrollRect = RectF(3.0, 4.0, 0.0, 0.0);
    reporter->scrollQueue_.push(info);

    EXPECT_CALL(*reporter, UpdateScrollEventInfoFromTree(_)).Times(1).WillOnce(Return(true));
    EXPECT_CALL(*reporter, HandleUpdatedScrollEndEvent(_))
        .Times(1)
        .WillOnce(Return(WebAgentEventReporter::ScrollEndEventAction::DROP));

    reporter->ProcessScrollQueue();

    EXPECT_FALSE(reporter->processingScroll_);
    EXPECT_EQ(static_cast<size_t>(0), reporter->scrollQueue_.size());
#endif
}

/**
 * @tc.name: ProcessScrollQueue_EndEventRetry
 * @tc.desc: When an updated end event is processed and it matches startRecords and offsets don't
 *        change, HandleUpdatedScrollEndEvent should schedule a retry (RETRY) and leave the
 *        event in the queue with an incremented retry count.
 * @tc.type: FUNC
 */
HWTEST_F(WebAgentEventReporterTest, ProcessScrollQueue_EndEventRetry, TestSize.Level0)
{
#ifdef OHOS_STANDARD_SYSTEM
    // In tests the postTask has no effect; we mock HandleUpdatedScrollEndEvent to return RETRY
    auto reporter = AceType::MakeRefPtr<MockReporterUpdateHandle>(AceType::WeakClaim(AceType::RawPtr(g_webPattern)));
    WebAgentEventReporter::ScrollEventInfo info;
    info.eventType = "ScrollEnd";
    info.id = 20;
    info.scrollRect = RectF(5.0, 6.0, 0.0, 0.0);
    reporter->scrollQueue_.push(info);

    // put a matching start record so HandleUpdatedScrollEndEvent will schedule a retry
    reporter->startRecords_[info.id] = info;

    EXPECT_CALL(*reporter, UpdateScrollEventInfoFromTree(_)).Times(1).WillOnce(Return(true));
    EXPECT_CALL(*reporter, HandleUpdatedScrollEndEvent(_))
        .Times(1)
        .WillOnce(Return(WebAgentEventReporter::ScrollEndEventAction::RETRY));

    reporter->ProcessScrollQueue();

    // When RETRY is returned, ProcessScrollQueue returns early keeping processingScroll_ true
    // and leaving the queue intact (postTask is a no-op in test environment).
    EXPECT_TRUE(reporter->processingScroll_);
    EXPECT_EQ(reporter->startRecords_.count(info.id), 1);
    EXPECT_EQ(static_cast<size_t>(1), reporter->scrollQueue_.size());
#endif
}

/**
 * @tc.name: ProcessScrollQueue_EndEventPROCEED
 * @tc.desc: When an updated end event is processed and it matches startRecords and offsets change,
 *        HandleUpdatedScrollEndEvent should proceed (PROCEED) and remove the event from the queue.
 * @tc.type: FUNC
 */
HWTEST_F(WebAgentEventReporterTest, ProcessScrollQueue_EndEventPROCEED, TestSize.Level0)
{
#ifdef OHOS_STANDARD_SYSTEM
    // In tests the postTask has no effect; we mock HandleUpdatedScrollEndEvent to return RETRY
    auto reporter = AceType::MakeRefPtr<MockReporterUpdateHandle>(AceType::WeakClaim(AceType::RawPtr(g_webPattern)));
    WebAgentEventReporter::ScrollEventInfo info;
    info.eventType = "ScrollEnd";
    info.id = 20;
    info.scrollRect = RectF(5.0, 6.0, 0.0, 0.0);
    reporter->scrollQueue_.push(info);

    // put a matching start record so HandleUpdatedScrollEndEvent will schedule a retry
    reporter->startRecords_[info.id] = info;

    EXPECT_CALL(*reporter, UpdateScrollEventInfoFromTree(_)).Times(1).WillOnce(Return(true));
    EXPECT_CALL(*reporter, HandleUpdatedScrollEndEvent(_))
        .Times(1)
        .WillOnce(Return(WebAgentEventReporter::ScrollEndEventAction::PROCEED));

    reporter->ProcessScrollQueue();

    EXPECT_FALSE(reporter->processingScroll_);
    EXPECT_EQ(reporter->startRecords_.count(info.id), 0);
    EXPECT_EQ(static_cast<size_t>(0), reporter->scrollQueue_.size());
#endif
}

/**
 * @tc.name: HandleUpdatedScrollEndEvent_NoStartRecord
 * @tc.desc: If there's no matching start record, should return DROP.
 * @tc.type: FUNC
 */
HWTEST_F(WebAgentEventReporterTest, HandleUpdatedScrollEndEvent_NoStartRecord, TestSize.Level0)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto reporter = AceType::MakeRefPtr<WebAgentEventReporter>(AceType::WeakClaim(AceType::RawPtr(g_webPattern)));
    WebAgentEventReporter::ScrollEventInfo info;
    info.eventType = "ScrollEnd";
    info.id = 101;
    info.scrollRect = RectF(1.0, 1.0, 0.0, 0.0);

    auto action = reporter->HandleUpdatedScrollEndEvent(info);
    EXPECT_EQ(action, WebAgentEventReporter::ScrollEndEventAction::DROP);
#endif
}

/**
 * @tc.name: HandleUpdatedScrollEndEvent_ProceedWhenDifferentOffset
 * @tc.desc: If matching start record exists but offsets differ, should PROCEED.
 * @tc.type: FUNC
 */
HWTEST_F(WebAgentEventReporterTest, HandleUpdatedScrollEndEvent_ProceedWhenDifferentOffset, TestSize.Level0)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto reporter = AceType::MakeRefPtr<WebAgentEventReporter>(AceType::WeakClaim(AceType::RawPtr(g_webPattern)));
    WebAgentEventReporter::ScrollEventInfo startInfo;
    startInfo.eventType = "ScrollStart";
    startInfo.id = 102;
    startInfo.scrollRect = RectF(0.0, 0.0, 0.0, 0.0);
    reporter->startRecords_[startInfo.id] = startInfo;

    WebAgentEventReporter::ScrollEventInfo endInfo;
    endInfo.eventType = "ScrollEnd";
    endInfo.id = 102;
    endInfo.scrollRect = RectF(10.0, 10.0, 0.0, 0.0); // different from start

    auto action = reporter->HandleUpdatedScrollEndEvent(endInfo);
    EXPECT_EQ(action, WebAgentEventReporter::ScrollEndEventAction::PROCEED);
#endif
}

/**
 * @tc.name: HandleUpdatedScrollEndEvent_RetryAndMax
 * @tc.desc: If offsets same and retry < max, should increment retry and return RETRY; when retry >= max, PROCEED.
 * @tc.type: FUNC
 */
HWTEST_F(WebAgentEventReporterTest, HandleUpdatedScrollEndEvent_RetryAndMax, TestSize.Level0)
{
#ifdef OHOS_STANDARD_SYSTEM
    // Ensure delayed tasks do not execute immediately in this test
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>(true);
    MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;

    auto reporter = AceType::MakeRefPtr<WebAgentEventReporter>(AceType::WeakClaim(AceType::RawPtr(g_webPattern)));
    WebAgentEventReporter::ScrollEventInfo startInfo;
    startInfo.eventType = "ScrollStart";
    startInfo.id = 103;
    startInfo.scrollRect = RectF(2.0, 2.0, 0.0, 0.0);
    reporter->startRecords_[startInfo.id] = startInfo;

    WebAgentEventReporter::ScrollEventInfo endInfo;
    endInfo.eventType = "ScrollEnd";
    endInfo.id = 103;
    endInfo.scrollRect = RectF(2.0, 2.0, 0.0, 0.0); // same as start
    endInfo.retry = 0;

    auto action = reporter->HandleUpdatedScrollEndEvent(endInfo);
    EXPECT_EQ(action, WebAgentEventReporter::ScrollEndEventAction::RETRY);
    EXPECT_EQ(endInfo.retry, 1);

    // when retry reaches MAX, it should PROCEED
    endInfo.retry = WebAgentEventReporter::MAX_SCROLL_EVENT_UPDATE_RETRY;
    action = reporter->HandleUpdatedScrollEndEvent(endInfo);
    EXPECT_EQ(action, WebAgentEventReporter::ScrollEndEventAction::PROCEED);
#endif
}

/**
 * @tc.name: ReportAndAdvanceScrollQueue_StartAndEnd
 * @tc.desc: Verify ReportAndAdvanceScrollQueue updates startRecords and advances queue for start/end events.
 * @tc.type: FUNC
 */
HWTEST_F(WebAgentEventReporterTest, ReportAndAdvanceScrollQueue_StartAndEnd, TestSize.Level0)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto reporter = AceType::MakeRefPtr<WebAgentEventReporter>(AceType::WeakClaim(AceType::RawPtr(g_webPattern)));

    // Test start event: should add to startRecords and pop queue
    WebAgentEventReporter::ScrollEventInfo startInfo;
    startInfo.eventType = "ScrollStart";
    startInfo.id = 200;
    startInfo.scrollRect = RectF(7.0, 8.0, 0.0, 0.0);
    reporter->scrollQueue_.push(startInfo);
    EXPECT_EQ(static_cast<size_t>(1), reporter->scrollQueue_.size());

    reporter->ReportAndAdvanceScrollQueue(startInfo, true);
    EXPECT_EQ(static_cast<size_t>(0), reporter->scrollQueue_.size());
    auto it = reporter->startRecords_.find(startInfo.id);
    EXPECT_NE(it, reporter->startRecords_.end());
    EXPECT_EQ(it->second.scrollRect.Left(), startInfo.scrollRect.Left());

    // Test end event: should erase startRecords and pop queue
    WebAgentEventReporter::ScrollEventInfo endInfo;
    endInfo.eventType = "ScrollEnd";
    endInfo.id = 200;
    endInfo.scrollRect = RectF(7.0, 8.0, 0.0, 0.0);
    reporter->startRecords_[endInfo.id] = startInfo; // reinsert
    reporter->scrollQueue_.push(endInfo);
    EXPECT_EQ(static_cast<size_t>(1), reporter->scrollQueue_.size());

    reporter->ReportAndAdvanceScrollQueue(endInfo, false);
    EXPECT_EQ(static_cast<size_t>(0), reporter->scrollQueue_.size());
    EXPECT_EQ(reporter->startRecords_.find(endInfo.id), reporter->startRecords_.end());
#endif
}

} // namespace OHOS::Ace::NG
