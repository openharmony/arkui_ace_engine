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
#include "core/common/event_dump.h"
#include "test/unittest/core/event/event_manager_test_ng.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr size_t MAX_EVENT_TREE_RECORD_CNT = 5;
constexpr int32_t MAX_EVENT_TREE_TOUCH_DOWN_CNT = 10;
constexpr int32_t MAX_EVENT_TREE_TOUCH_POINT_CNT = 20;
constexpr int32_t MAX_EVENT_TREE_AXIS_UPDATE_CNT = 20;
constexpr int32_t MAX_EVENT_TREE_AXIS_CNT = 20;
constexpr int32_t PARENT_NODEID = 0;
constexpr int32_t DEFAULT_HITTEST_MODE = 0;
constexpr int32_t DEFAULT_DEPTH = 1;
constexpr int64_t DEFAULT_TIME_STAMP = 65536;
const std::string JSON_KEY_COM_ID = "comId";
const std::string ID_0 = "0x0";
const std::string ID_1 = "0x1";
const std::string PARENT_ID_0 = "0x0";
const std::string PARENT_ID_1 = "0x1";
const std::string TAG = "column";
} // namespace

class EventDumpTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;

    std::shared_ptr<FrameNodeSnapshot> CreateFrameNodeSnapshotWithInitValue();
    std::shared_ptr<TouchPointSnapshot> CreateTouchPointSnapshot(const TouchEvent& event);
    std::shared_ptr<AxisSnapshot> CreateAxisSnapshot(const AxisEvent& event);
    std::shared_ptr<EventTreeRecord> CreateEventTreeRecord();
    void FillTouchDownEventToEventTree(std::shared_ptr<EventTreeRecord> eventTreeRecord, const TouchEvent& event,
        int32_t eventTreeRecordCount = 0, int32_t touchDownCount = 0, int32_t touchPointCount = 0);
    void FillAxisUpdateEventToEventTree(std::shared_ptr<EventTreeRecord> eventTreeRecord, const AxisEvent& event,
        int32_t eventTreeRecordCount = 0, int32_t axisUpdateCount = 0, int32_t AxisCount = 0);
};

void EventDumpTestNg::SetUp()
{}

void EventDumpTestNg::TearDown()
{}

void EventDumpTestNg::SetUpTestSuite()
{}

void EventDumpTestNg::TearDownTestSuite()
{}

std::shared_ptr<FrameNodeSnapshot> EventDumpTestNg::CreateFrameNodeSnapshotWithInitValue()
{
    auto frameNodeSnapshotInstance = std::make_shared<FrameNodeSnapshot>();
    CHECK_NULL_RETURN(frameNodeSnapshotInstance, nullptr);
    frameNodeSnapshotInstance->nodeId = NODEID;
    frameNodeSnapshotInstance->parentNodeId = PARENT_NODEID;
    frameNodeSnapshotInstance->tag = TAG;
    frameNodeSnapshotInstance->comId = "comId_01";
    frameNodeSnapshotInstance->monopolizeEvents = true;
    frameNodeSnapshotInstance->isHit = true;
    frameNodeSnapshotInstance->hitTestMode = DEFAULT_HITTEST_MODE;
    frameNodeSnapshotInstance->responseRegionList = { RectF(0, 0, 20, 10), RectF(25, 0, 20, 10) };
    return frameNodeSnapshotInstance;
}

std::shared_ptr<TouchPointSnapshot> EventDumpTestNg::CreateTouchPointSnapshot(const TouchEvent& event)
{
    return std::make_shared<TouchPointSnapshot>(event);
}

std::shared_ptr<AxisSnapshot> EventDumpTestNg::CreateAxisSnapshot(const AxisEvent& event)
{
    return std::make_shared<AxisSnapshot>(event);
}

std::shared_ptr<EventTreeRecord> EventDumpTestNg::CreateEventTreeRecord()
{
    return std::make_shared<EventTreeRecord>();
}

void EventDumpTestNg::FillTouchDownEventToEventTree(std::shared_ptr<EventTreeRecord> eventTreeRecord,
    const TouchEvent& event, const int32_t eventTreeRecordCount, int32_t touchDownCount, int32_t touchPointCount)
{
    if (!eventTreeRecord || event.type != Ace::TouchType::DOWN) {
        return;
    }
    eventTreeRecord->eventTreeList.clear();
    for (int32_t i = 0; i < eventTreeRecordCount; ++i) {
        eventTreeRecord->eventTreeList.emplace_back(EventTree());
    }
    if (!eventTreeRecord->eventTreeList.empty()) {
        for (int32_t i = 0; i < touchPointCount; ++i) {
            eventTreeRecord->eventTreeList.back().touchPoints.emplace_back(TouchPointSnapshot(event));
        }
        eventTreeRecord->eventTreeList.back().touchDownCount = touchDownCount;
    }
}

void EventDumpTestNg::FillAxisUpdateEventToEventTree(std::shared_ptr<EventTreeRecord> eventTreeRecord,
    const AxisEvent& event, const int32_t eventTreeRecordCount, int32_t axisUpdateCount, int32_t AxisCount)
{
    if (!eventTreeRecord || event.action != Ace::AxisAction::BEGIN) {
        return;
    }
    eventTreeRecord->eventTreeList.clear();
    for (int32_t i = 0; i < eventTreeRecordCount; ++i) {
        eventTreeRecord->eventTreeList.emplace_back(EventTree());
    }
    if (!eventTreeRecord->eventTreeList.empty()) {
        for (int32_t i = 0; i < AxisCount; ++i) {
            eventTreeRecord->eventTreeList.back().axis.emplace_back(AxisSnapshot(event));
        }
        eventTreeRecord->eventTreeList.back().axisUpdateCount = axisUpdateCount;
    }
}


/**
 * @tc.name: EventDumpTestNg001
 * @tc.desc: FrameNodeSnapshot dump function test.
 * @tc.type: FUNC
 */
HWTEST_F(EventDumpTestNg, EventDumpTestNg001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create FrameNodeSnapshot instance and init value.
     */
    auto frameNodeSnapshotInstance = CreateFrameNodeSnapshotWithInitValue();

    /**
     * @tc.steps: step2. Invoke dump function.
     * @tc.expected: dump list exist data, size is not empty.
     */
    ASSERT_NE(frameNodeSnapshotInstance, nullptr);
    std::list<std::pair<int32_t, std::string>> dumpList;
    EXPECT_TRUE(dumpList.empty());
    frameNodeSnapshotInstance->Dump(dumpList, DEFAULT_DEPTH);
    EXPECT_FALSE(dumpList.empty());
}

/**
 * @tc.name: EventDumpTestNg002
 * @tc.desc: TouchPointSnapshot dump function test.
 * @tc.type: FUNC
 */
HWTEST_F(EventDumpTestNg, EventDumpTestNg002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create TouchPointSnapshot instance and init value.
     */
    TouchEvent event;
    auto touchPointSnapshot = CreateTouchPointSnapshot(event);

    /**
     * @tc.steps: step2. Invoke dump function.
     * @tc.expected: dump list exist data, size is not empty.
     */
    ASSERT_NE(touchPointSnapshot, nullptr);
    std::list<std::pair<int32_t, std::string>> dumpList;
    EXPECT_TRUE(dumpList.empty());
    touchPointSnapshot->Dump(dumpList, DEFAULT_DEPTH);
    EXPECT_FALSE(dumpList.empty());

    std::unique_ptr<JsonValue> dumpJson = JsonUtil::Create(true);
    touchPointSnapshot->Dump(dumpJson);
    EXPECT_TRUE(dumpJson->Contains("isInjected"));
}

/**
 * @tc.name: EventDumpTestNg003
 * @tc.desc: EventTreeRecord AddTouchPoint function test.
 * @tc.type: FUNC
 */
HWTEST_F(EventDumpTestNg, EventDumpTestNg003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create EventTreeRecord instance.
     */
    auto eventTreeRecord = CreateEventTreeRecord();
    ASSERT_NE(eventTreeRecord, nullptr);

    /**
     * @tc.steps: step2. mock touch event DOWN to UP.
     * @tc.expected: touchDownCount is zero.
     */
    const std::vector<Ace::TouchType> touchTypeArray = { Ace::TouchType::DOWN, Ace::TouchType::UP };
    TouchEvent event;
    int32_t eventTreeRecordCount = 1;
    int32_t touchDownCount = 4;
    for (int32_t i = 0; i < eventTreeRecordCount * touchDownCount; ++i) {
        int32_t index = i % touchTypeArray.size();
        event.type = touchTypeArray[index];
        event.id = touchTypeArray.size() > 0 ? i / touchTypeArray.size() : i;
        eventTreeRecord->AddTouchPoint(event);
    }
    ASSERT_FALSE(eventTreeRecord->eventTreeList.empty());
    EXPECT_EQ(eventTreeRecord->eventTreeList.back().touchDownCount, (eventTreeRecordCount * touchDownCount) % 2);
}

/**
 * @tc.name: EventDumpTestNg004
 * @tc.desc: EventTreeRecord AddTouchPoint function test.
 * @tc.type: FUNC
 */
HWTEST_F(EventDumpTestNg, EventDumpTestNg004, TestSize.Level2)
{
    /**
     * @tc.steps: step1. create EventTreeRecord instance.
     */
    auto eventTreeRecord = CreateEventTreeRecord();
    ASSERT_NE(eventTreeRecord, nullptr);
    TouchEvent event;
    event.type = Ace::TouchType::DOWN;
    event.id = 1;

    /**
     * @tc.steps: step2. fill touch event vale to eventTree.
     * @tc.expected: list is not empty.
     */
    FillTouchDownEventToEventTree(eventTreeRecord, event, MAX_EVENT_TREE_RECORD_CNT + 1,
        MAX_EVENT_TREE_TOUCH_DOWN_CNT, MAX_EVENT_TREE_TOUCH_POINT_CNT + 1);
    eventTreeRecord->AddTouchPoint(event);
    ASSERT_FALSE(eventTreeRecord->eventTreeList.empty());
    EXPECT_EQ(eventTreeRecord->eventTreeList.size(), MAX_EVENT_TREE_RECORD_CNT);
}

/**
 * @tc.name: EventDumpTestNg005
 * @tc.desc: EventTreeRecord AddGestureSnapshot function test.
 * @tc.type: FUNC
 */
HWTEST_F(EventDumpTestNg, EventDumpTestNg005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create EventTreeRecord instance and fill touch event vale to eventTree.
     */
    auto eventTreeRecord = CreateEventTreeRecord();
    ASSERT_NE(eventTreeRecord, nullptr);
    TouchEvent event;
    event.type = Ace::TouchType::DOWN;
    event.id = 1;
    eventTreeRecord->AddTouchPoint(event);

    /**
     * @tc.steps: step2. Invoke AddGestureSnapshot function.
     * @tc.expected: list is not empty.
     */
    auto gestureSnapshot = AceType::MakeRefPtr<GestureSnapshot>();
    int32_t finger = 0;
    eventTreeRecord->AddGestureSnapshot(finger, std::move(gestureSnapshot));
    
    EXPECT_FALSE(eventTreeRecord->eventTreeList.back().gestureTree.empty());
    EXPECT_FALSE(eventTreeRecord->eventTreeList.back().gestureMap.empty());
}

/**
 * @tc.name: EventDumpTestNg006
 * @tc.desc: EventTreeRecord AddGestureSnapshot function test.
 * @tc.type: FUNC
 */
HWTEST_F(EventDumpTestNg, EventDumpTestNg006, TestSize.Level2)
{
    /**
     * @tc.steps: step1. create EventTreeRecord instance and fill touch event vale to eventTree.
     */
    auto eventTreeRecord = CreateEventTreeRecord();
    ASSERT_NE(eventTreeRecord, nullptr);
    TouchEvent event;
    event.type = Ace::TouchType::DOWN;
    event.id = 1;

    /**
     * @tc.steps: step2. Invoke AddGestureSnapshot function.
     * @tc.expected: list is empty.
     */
    FillTouchDownEventToEventTree(eventTreeRecord, event, MAX_EVENT_TREE_RECORD_CNT + 1,
        MAX_EVENT_TREE_TOUCH_DOWN_CNT, MAX_EVENT_TREE_TOUCH_POINT_CNT + 1);

    int32_t finger = 0;
    eventTreeRecord->AddGestureSnapshot(finger, nullptr);
    EXPECT_TRUE(eventTreeRecord->eventTreeList.empty());
}

/**
 * @tc.name: EventDumpTestNg007
 * @tc.desc: EventTreeRecord AddGestureProcedure function test.
 * @tc.type: FUNC
 */
HWTEST_F(EventDumpTestNg, EventDumpTestNg007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create EventTreeRecord instance and fill touch event vale to eventTree.
     */
    auto eventTreeRecord = CreateEventTreeRecord();
    ASSERT_NE(eventTreeRecord, nullptr);
    TouchEvent event;
    event.type = Ace::TouchType::DOWN;
    event.id = 1;
    eventTreeRecord->AddTouchPoint(event);
    auto gestureSnapshot = AceType::MakeRefPtr<GestureSnapshot>();
    int32_t finger = 0;
    eventTreeRecord->AddGestureSnapshot(finger, std::move(gestureSnapshot));

    /**
     * @tc.steps: step2. Invoke AddGestureProcedure function.
     * @tc.expected: stateHistory is not empty.
     */
    std::string procedure = "HandleTouchDown";
    std::string state = "current";
    std::string disposal = "mainThread";

    eventTreeRecord->AddGestureProcedure(finger + 1, procedure, "", state, disposal, DEFAULT_TIME_STAMP);
    ASSERT_FALSE(eventTreeRecord->eventTreeList.empty());
    auto iter0 = eventTreeRecord->eventTreeList.back().gestureMap.find(finger + 1);
    EXPECT_TRUE(iter0 == eventTreeRecord->eventTreeList.back().gestureMap.end());

    eventTreeRecord->AddGestureProcedure(finger, procedure, "", state, disposal, DEFAULT_TIME_STAMP);
    ASSERT_FALSE(eventTreeRecord->eventTreeList.empty());
    auto iter = eventTreeRecord->eventTreeList.back().gestureMap.find(finger);
    ASSERT_TRUE(iter != eventTreeRecord->eventTreeList.back().gestureMap.end());
    ASSERT_TRUE(iter->second != nullptr);
    EXPECT_FALSE(iter->second->stateHistory.empty());
}

/**
 * @tc.name: EventDumpTestNg008
 * @tc.desc: EventTreeRecord AddGestureProcedure function test.
 * @tc.type: FUNC
 */
HWTEST_F(EventDumpTestNg, EventDumpTestNg008, TestSize.Level2)
{
    /**
     * @tc.steps: step1. create EventTreeRecord instance and fill touch event vale to eventTree.
     */
    auto eventTreeRecord = CreateEventTreeRecord();
    ASSERT_NE(eventTreeRecord, nullptr);
    TouchEvent event;
    event.type = Ace::TouchType::DOWN;
    event.id = 1;
    eventTreeRecord->AddTouchPoint(event);
    auto gestureSnapshot = AceType::MakeRefPtr<GestureSnapshot>();
    gestureSnapshot->type = "TouchEventActuator";
    int32_t finger = 0;
    eventTreeRecord->AddGestureSnapshot(finger, std::move(gestureSnapshot));

    /**
     * @tc.steps: step2. Invoke AddGestureProcedure function.
     * @tc.expected: stateHistory is empty.
     */
    std::string procedure = "HandleTouchMove";
    std::string state = "current";
    std::string disposal = "mainThread";
    eventTreeRecord->AddGestureProcedure(finger, procedure, "", state, disposal, DEFAULT_TIME_STAMP);
    ASSERT_FALSE(eventTreeRecord->eventTreeList.empty());
    auto iter = eventTreeRecord->eventTreeList.back().gestureMap.find(finger);
    ASSERT_TRUE(iter != eventTreeRecord->eventTreeList.back().gestureMap.end());
    ASSERT_TRUE(iter->second != nullptr);
    EXPECT_TRUE(iter->second->stateHistory.empty());
}

/**
 * @tc.name: EventDumpTestNg009
 * @tc.desc: EventTreeRecord AddGestureProcedure function test.
 * @tc.type: FUNC
 */
HWTEST_F(EventDumpTestNg, EventDumpTestNg009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create EventTreeRecord instance and fill touch event vale to eventTree.
     */
    auto eventTreeRecord = CreateEventTreeRecord();
    ASSERT_NE(eventTreeRecord, nullptr);
    TouchEvent event;
    event.type = Ace::TouchType::DOWN;
    event.id = 1;
    eventTreeRecord->AddTouchPoint(event);

    /**
     * @tc.steps: step2. Invoke AddGestureProcedure function.
     * @tc.expected: stateHistory is not empty.
     */
    auto gestureSnapshot = AceType::MakeRefPtr<GestureSnapshot>();
    int32_t finger = 0;
    eventTreeRecord->AddGestureSnapshot(finger, std::move(gestureSnapshot));
    std::string state = "current";
    std::string disposal = "mainThread";

    eventTreeRecord->AddGestureProcedure(finger + 1, event, "", state, disposal, DEFAULT_TIME_STAMP);
    ASSERT_FALSE(eventTreeRecord->eventTreeList.empty());
    auto iter0 = eventTreeRecord->eventTreeList.back().gestureMap.find(finger + 1);
    EXPECT_TRUE(iter0 == eventTreeRecord->eventTreeList.back().gestureMap.end());

    eventTreeRecord->AddGestureProcedure(finger, event, "", state, disposal, DEFAULT_TIME_STAMP);
    ASSERT_FALSE(eventTreeRecord->eventTreeList.empty());
    auto iter = eventTreeRecord->eventTreeList.back().gestureMap.find(finger);
    ASSERT_TRUE(iter != eventTreeRecord->eventTreeList.back().gestureMap.end());
    ASSERT_TRUE(iter->second != nullptr);
    EXPECT_FALSE(iter->second->stateHistory.empty());
}

/**
 * @tc.name: EventDumpTestNg010
 * @tc.desc: EventTreeRecord dump function test.
 * @tc.type: FUNC
 */
HWTEST_F(EventDumpTestNg, EventDumpTestNg010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create EventTreeRecord instance and fill touch event vale to eventTree.
     */
    auto eventTreeRecord = CreateEventTreeRecord();
    ASSERT_NE(eventTreeRecord, nullptr);
    TouchEvent event;
    event.type = Ace::TouchType::DOWN;
    event.id = 1;
    eventTreeRecord->AddTouchPoint(event);
    auto frameNodeSnapshotInstance = CreateFrameNodeSnapshotWithInitValue();
    ASSERT_NE(frameNodeSnapshotInstance, nullptr);
    eventTreeRecord->AddFrameNodeSnapshot(std::move(*frameNodeSnapshotInstance));
    auto gestureSnapshot = AceType::MakeRefPtr<GestureSnapshot>();
    int32_t finger = 0;
    eventTreeRecord->AddGestureSnapshot(finger, std::move(gestureSnapshot));
    std::string state = "current";
    std::string disposal = "mainThread";
    eventTreeRecord->AddGestureProcedure(finger, event, "", state, disposal, DEFAULT_TIME_STAMP);

    /**
     * @tc.steps: step2. Invoke dump function.
     * @tc.expected: dump list exist data, size is not empty.
     */
    std::list<std::pair<int32_t, std::string>> dumpList;
    EXPECT_TRUE(dumpList.empty());
    eventTreeRecord->Dump(dumpList, DEFAULT_DEPTH);
    EXPECT_FALSE(dumpList.empty());

    std::unique_ptr<JsonValue> dumpJson = JsonUtil::Create(true);
    int32_t depth = 0;
    int32_t startNumber = -1;
    std::string header = "event tree_0";
    eventTreeRecord->Dump(dumpJson, depth, startNumber);
    EXPECT_FALSE(dumpJson->Contains(header));
}

/**
 * @tc.name: EventDumpTestNg011
 * @tc.desc: FrameNodeSnapshot Dump function test.
 * @tc.type: FUNC
 */
HWTEST_F(EventDumpTestNg, EventDumpTestNg011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create FrameNodeSnapshot instance and init value.
     */
    auto frameNodeSnapshotInstance = CreateFrameNodeSnapshotWithInitValue();

    /**
     * @tc.steps: step2. set frameNodeSnapshotInstance->comId is "" and call Dump function.
     * @tc.expected: comId does not exist in json.
     */
    ASSERT_NE(frameNodeSnapshotInstance, nullptr);
    std::unique_ptr<JsonValue> json = JsonUtil::Create(true);
    frameNodeSnapshotInstance->comId = "";
    frameNodeSnapshotInstance->Dump(json);
    EXPECT_FALSE(json->Contains(JSON_KEY_COM_ID));

    /**
     * @tc.steps: step3. set frameNodeSnapshotInstance->comId is "comId_02" and call Dump function.
     * @tc.expected: comId exists in json.
     */
    frameNodeSnapshotInstance->comId = "comId_02";
    frameNodeSnapshotInstance->Dump(json);
    EXPECT_TRUE(json->Contains(JSON_KEY_COM_ID));
}

/**
 * @tc.name: EventDumpTestNg012
 * @tc.desc: MountToParent function test.
 * @tc.type: FUNC
 */
HWTEST_F(EventDumpTestNg, EventDumpTestNg012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create EventTreeRecord instance.
     */
    auto eventTreeRecord = CreateEventTreeRecord();
    ASSERT_NE(eventTreeRecord, nullptr);

    /**
     * @tc.steps: step2. call MountToParent function.
     * @tc.expected: expected value does not exist in json.
     */
    std::vector<std::pair<std::string, std::pair<std::string, std::unique_ptr<JsonValue>>>> stateInfoList;
    std::unique_ptr<JsonValue> json = JsonUtil::Create(true);
    eventTreeRecord->MountToParent(std::move(stateInfoList), json);
    EXPECT_FALSE(json->Contains(("detail_" + ID_0).c_str()));

    /**
     * @tc.steps: step3. set stateInfoList not empty and call MountToParent function.
     * @tc.expected: expected value exists in json.
     */
    stateInfoList.push_back(std::make_pair(ID_0, std::make_pair(PARENT_ID_0, JsonUtil::Create(true))));
    stateInfoList.push_back(std::make_pair(ID_1, std::make_pair(PARENT_ID_1, JsonUtil::Create(true))));
    eventTreeRecord->MountToParent(std::move(stateInfoList), json);
    EXPECT_TRUE(json->Contains(("detail_" + ID_0).c_str()));
}

/**
 * @tc.name: EventDumpTestNg013
 * @tc.desc: EventTreeRecord Dump function test.
 * @tc.type: FUNC
 */
HWTEST_F(EventDumpTestNg, EventDumpTestNg013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create EventTreeRecord instance and fill touch event vale to eventTree.
     */
    auto eventTreeRecord = CreateEventTreeRecord();
    ASSERT_NE(eventTreeRecord, nullptr);
    TouchEvent event;
    event.type = Ace::TouchType::DOWN;
    event.id = 1;
    FillTouchDownEventToEventTree(eventTreeRecord, event, MAX_EVENT_TREE_RECORD_CNT + 1, 0, 0);

    /**
     * @tc.steps: step2. set startNumber is -1 and call Dump function.
     * @tc.expected: "event tree_0" exists in json.
     */
    std::unique_ptr<JsonValue> json = JsonUtil::Create(true);
    int32_t depth = 0;
    int32_t startNumber = -1;
    std::string header = "event tree_0";
    eventTreeRecord->Dump(json, depth, startNumber);
    EXPECT_FALSE(json->Contains(header));

    /**
     * @tc.steps: step3. set startNumber is 1 and call Dump function.
     * @tc.expected: "event tree_1" exists in json.
     */
    startNumber = 1;
    header = "event tree_1";
    eventTreeRecord->Dump(json, depth, startNumber);
    EXPECT_TRUE(json->Contains(header));
}

/**
 * @tc.name: EventDumpTestNg014
 * @tc.desc: BuildGestureTree function test.
 * @tc.type: FUNC
 */
HWTEST_F(EventDumpTestNg, EventDumpTestNg014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create EventTreeRecord instance.
     */
    auto eventTreeRecord = CreateEventTreeRecord();
    ASSERT_NE(eventTreeRecord, nullptr);

    /**
     * @tc.steps: step2. call BuildGestureTree function.
     * @tc.expected: "event procedures" exists in json.
     */
    auto gestureSnapshot = AceType::MakeRefPtr<GestureSnapshot>();
    std::list<RefPtr<GestureSnapshot>> gestureSnapshotList;
    gestureSnapshotList.push_back(gestureSnapshot);

    std::map<int32_t, std::list<RefPtr<GestureSnapshot>>> gestureTreeMap;
    gestureTreeMap.insert({1, gestureSnapshotList});
    std::unique_ptr<JsonValue> json = JsonUtil::Create(true);
    eventTreeRecord->BuildGestureTree(gestureTreeMap, json);
    EXPECT_TRUE(json->Contains("event procedures"));
}

/**
 * @tc.name: EventDumpTestNg015
 * @tc.desc: FrameNodeSnapshot Dump function test.
 * @tc.type: FUNC
 */
HWTEST_F(EventDumpTestNg, EventDumpTestNg015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create FrameNodeSnapshot instance and init value.
     */
    auto frameNodeSnapshotInstance = CreateFrameNodeSnapshotWithInitValue();
    ASSERT_NE(frameNodeSnapshotInstance, nullptr);

    /**
     * @tc.steps: step2. set comId is "" and call Dump function.
     * @tc.expected: dump list exist data, size is not empty.
     */
    frameNodeSnapshotInstance->comId = "";
    std::list<std::pair<int32_t, std::string>> dumpList;
    frameNodeSnapshotInstance->Dump(dumpList, DEFAULT_DEPTH);
    EXPECT_FALSE(dumpList.empty());
}

/**
 * @tc.name: EventDumpTestNg016
 * @tc.desc: EventTreeRecord Dump function test.
 * @tc.type: FUNC
 */
HWTEST_F(EventDumpTestNg, EventDumpTestNg016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create EventTreeRecord instance and fill touch event vale to eventTree.
     */
    auto eventTreeRecord = CreateEventTreeRecord();
    ASSERT_NE(eventTreeRecord, nullptr);
    TouchEvent event;
    event.type = Ace::TouchType::DOWN;
    event.id = 1;
    FillTouchDownEventToEventTree(eventTreeRecord, event, MAX_EVENT_TREE_RECORD_CNT + 1, 0, 0);

    /**
     * @tc.steps: step2. call Dump function.
     * @tc.expected: dump list exist data, size is not empty.
     */
    std::list<std::pair<int32_t, std::string>> dumpList;
    EXPECT_TRUE(dumpList.empty());
    int32_t startNumber = 1;
    eventTreeRecord->Dump(dumpList, DEFAULT_DEPTH, startNumber);
    EXPECT_FALSE(dumpList.empty());

    std::unique_ptr<JsonValue> dumpJson = JsonUtil::Create(true);
    int32_t depth = 0;
    std::string header = "event tree_0";
    eventTreeRecord->Dump(dumpJson, depth, startNumber);
    EXPECT_TRUE(dumpJson->Contains(header));
}

/**
 * @tc.name: EventDumpTestNg017
 * @tc.desc: AxisSnapshot dump function test.
 * @tc.type: FUNC
 */
HWTEST_F(EventDumpTestNg, EventDumpTestNg017, TestSize.Level1)
{
    AxisEvent event;
    const std::vector<Ace::AxisAction> axisActionArray = {Ace::AxisAction::BEGIN, Ace::AxisAction::UPDATE,
        Ace::AxisAction::END, Ace::AxisAction::CANCEL};
    std::unique_ptr<JsonValue> dumpJson = JsonUtil::Create(true);
    std::list<std::pair<int32_t, std::string>> dumpList;
    EXPECT_TRUE(dumpList.empty());

    for (int32_t i = 0; i < axisActionArray.size(); ++i) {
        event.action = axisActionArray[i];
        auto axisSnapshot = CreateAxisSnapshot(event);
        ASSERT_NE(axisSnapshot, nullptr);
        axisSnapshot->Dump(dumpList, DEFAULT_DEPTH + i);
        axisSnapshot->Dump(dumpJson);
    }
    EXPECT_FALSE(dumpList.empty());
    EXPECT_TRUE(dumpJson->Contains("isInjected"));
}

/**
 * @tc.name: EventDumpTestNg018
 * @tc.desc: TouchPointSnapshot dump function test.
 * @tc.type: FUNC
 */
HWTEST_F(EventDumpTestNg, EventDumpTestNg018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create TouchPointSnapshot instance and init value.
     */
    MockPipelineContext::SetUp();
    auto pipeline = NG::PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto eventManager = pipeline->GetEventManager();
    ASSERT_NE(eventManager, nullptr);
    int32_t fingerId = 1;
    eventManager->downFingerIds_[fingerId] = 1;
    TouchEvent event;
    auto touchPointSnapshot = CreateTouchPointSnapshot(event);
    ASSERT_NE(touchPointSnapshot, nullptr);
    EXPECT_FALSE(touchPointSnapshot->downFingerIds.empty());

    /**
     * @tc.steps: step2. Invoke dump function.
     * @tc.expected: dump list exist data, size is not empty.
     */
    std::list<std::pair<int32_t, std::string>> dumpList;
    EXPECT_TRUE(dumpList.empty());
    touchPointSnapshot->Dump(dumpList, DEFAULT_DEPTH);
    EXPECT_FALSE(dumpList.empty());

    std::unique_ptr<JsonValue> dumpJson = JsonUtil::Create(true);
    touchPointSnapshot->Dump(dumpJson);
    EXPECT_TRUE(dumpJson->Contains("downFingerIds"));

    MockPipelineContext::TearDown();
}

/**
 * @tc.name: EventDumpTestNg019
 * @tc.desc: EventTreeRecord AddAxis function test.
 * @tc.type: FUNC
 */
HWTEST_F(EventDumpTestNg, EventDumpTestNg019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create EventTreeRecord instance.
     */
    auto eventTreeRecord = CreateEventTreeRecord();
    ASSERT_NE(eventTreeRecord, nullptr);

    /**
     * @tc.steps: step2. mock Axis event BEGIN to END.
     */
    const std::vector<Ace::AxisAction> axisActionArray = {Ace::AxisAction::BEGIN, Ace::AxisAction::END,
        Ace::AxisAction::BEGIN, Ace::AxisAction::CANCEL};
    AxisEvent event;
    int32_t eventTreeRecordCount = 1;
    int32_t axisUpdateCount = 8;
    for (int32_t i = 0; i < eventTreeRecordCount * axisUpdateCount; ++i) {
        int32_t index = i % axisActionArray.size();
        event.action = axisActionArray[index];
        event.id = axisActionArray.size() > 0 ? i / axisActionArray.size() : i;
        eventTreeRecord->AddAxis(event);
    }
    ASSERT_FALSE(eventTreeRecord->eventTreeList.empty());
    EXPECT_EQ(eventTreeRecord->eventTreeList.back().axisUpdateCount, (eventTreeRecordCount * axisUpdateCount) % 2);
}

/**
 * @tc.name: EventDumpTestNg020
 * @tc.desc: EventTreeRecord AddAxis function test.
 * @tc.type: FUNC
 */
HWTEST_F(EventDumpTestNg, EventDumpTestNg020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create EventTreeRecord instance.
     */
    auto eventTreeRecord = CreateEventTreeRecord();
    ASSERT_NE(eventTreeRecord, nullptr);
    AxisEvent event;
    event.action = Ace::AxisAction::BEGIN;
    event.id = 1;

    /**
     * @tc.steps: step2. fill touch event vale to eventTree.
     * @tc.expected: list is not empty.
     */
    FillAxisUpdateEventToEventTree(eventTreeRecord, event, MAX_EVENT_TREE_RECORD_CNT + 1,
        MAX_EVENT_TREE_AXIS_UPDATE_CNT, MAX_EVENT_TREE_AXIS_CNT + 1);
    eventTreeRecord->AddAxis(event);
    ASSERT_FALSE(eventTreeRecord->eventTreeList.empty());
    EXPECT_EQ(eventTreeRecord->eventTreeList.size(), MAX_EVENT_TREE_RECORD_CNT);
}

/**
 * @tc.name: EventDumpTestNg021
 * @tc.desc: EventTreeRecord AddAxis function test.
 * @tc.type: FUNC
 */
HWTEST_F(EventDumpTestNg, EventDumpTestNg021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create EventTreeRecord instance.
     */
    auto eventTreeRecord = CreateEventTreeRecord();
    ASSERT_NE(eventTreeRecord, nullptr);

    /**
     * @tc.steps: step2. mock Axis event END.
     */
    AxisEvent event;
    event.action = Ace::AxisAction::END;
    eventTreeRecord->AddAxis(event);
    EXPECT_TRUE(eventTreeRecord->eventTreeList.empty());
}

/**
 * @tc.name: EventDumpTestNg022
 * @tc.desc: EventTreeRecord AddTouchPoint function test.
 * @tc.type: FUNC
 */
HWTEST_F(EventDumpTestNg, EventDumpTestNg022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create EventTreeRecord instance.
     */
    auto eventTreeRecord = CreateEventTreeRecord();
    ASSERT_NE(eventTreeRecord, nullptr);

    /**
     * @tc.steps: step2. mock touch event UP.
     */
    TouchEvent event;
    event.type = Ace::TouchType::UP;
    eventTreeRecord->AddTouchPoint(event);
    EXPECT_TRUE(eventTreeRecord->eventTreeList.empty());
}

/**
 * @tc.name: EventDumpTestNg023
 * @tc.desc: EventTreeRecord AddGestureProcedure function test.
 * @tc.type: FUNC
 */
HWTEST_F(EventDumpTestNg, EventDumpTestNg023, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create EventTreeRecord instance and fill touch event vale to eventTree.
     */
    auto eventTreeRecord = CreateEventTreeRecord();
    ASSERT_NE(eventTreeRecord, nullptr);
    AxisEvent event;
    event.action = Ace::AxisAction::BEGIN;
    event.id = 1;
    eventTreeRecord->AddAxis(event);
    AxisEvent event2;
    event2.action = Ace::AxisAction::UPDATE;
    event2.id = 2;
    eventTreeRecord->AddAxis(event2);
    AxisEvent event3;
    event3.action = Ace::AxisAction::UPDATE;
    event3.id = 3;
    eventTreeRecord->AddAxis(event3);

    /**
     * @tc.steps: step2. Invoke AddGestureProcedure function.
     */
    auto gestureSnapshot = AceType::MakeRefPtr<GestureSnapshot>();
    int32_t finger = 0;
    eventTreeRecord->AddGestureSnapshot(finger, std::move(gestureSnapshot));

    std::string state = "current";
    std::string disposal = "mainThread";
    std::string state2 = "current2";
    std::string disposal2 = "mainThread2";
    eventTreeRecord->AddGestureProcedure(finger + 1, event, "", state, disposal, DEFAULT_TIME_STAMP);
    ASSERT_FALSE(eventTreeRecord->eventTreeList.empty());
    auto iter = eventTreeRecord->eventTreeList.back().gestureMap.find(finger + 1);
    EXPECT_TRUE(iter == eventTreeRecord->eventTreeList.back().gestureMap.end());

    eventTreeRecord->AddGestureProcedure(finger, event, "", state, disposal, DEFAULT_TIME_STAMP);
    eventTreeRecord->AddGestureProcedure(finger, event2, "", state, disposal, DEFAULT_TIME_STAMP);
    eventTreeRecord->AddGestureProcedure(finger, event3, "", state2, disposal2, DEFAULT_TIME_STAMP);

    ASSERT_FALSE(eventTreeRecord->eventTreeList.empty());
    iter = eventTreeRecord->eventTreeList.back().gestureMap.find(finger);
    ASSERT_TRUE(iter != eventTreeRecord->eventTreeList.back().gestureMap.end());
    ASSERT_TRUE(iter->second != nullptr);
    EXPECT_FALSE(iter->second->stateHistory.empty());

    std::list<std::pair<int32_t, std::string>> dumpList;
    EXPECT_TRUE(dumpList.empty());
    eventTreeRecord->Dump(dumpList, DEFAULT_DEPTH);
    EXPECT_FALSE(dumpList.empty());

    std::unique_ptr<JsonValue> dumpJson = JsonUtil::Create(true);
    int32_t depth = 0;
    int32_t startNumber = -1;
    std::string header = "event tree_0";
    eventTreeRecord->Dump(dumpJson, depth, startNumber);
    EXPECT_FALSE(dumpJson->Contains(header));
}
} // namespace OHOS::Ace::NG
