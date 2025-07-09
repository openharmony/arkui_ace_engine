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

#include "test/unittest/core/event/event_manager_test_ng.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {

/**
 * @tc.name: PenHoverTest001
 * @tc.desc: Test PenHoverTest function.
 */
HWTEST_F(EventManagerTestNg, PenHoverTest001, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    const int nodeId = 10008;
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::LOCATION_BUTTON_ETS_TAG, nodeId, nullptr);
    ASSERT_NE(frameNode, nullptr);
    TouchRestrict touchRestrict;
    TouchEvent touchEvent;
    int32_t eventId = 1;
    touchEvent.SetX(100.0).SetY(100.0).SetOriginalId(eventId).SetId(eventId);
    touchEvent.sourceTool = SourceTool::PEN;

    touchEvent.SetType(TouchType::PROXIMITY_IN);
    auto hoverEventTarget = AceType::MakeRefPtr<HoverEventTarget>(V2::LOCATION_BUTTON_ETS_TAG, nodeId);
    eventManager->curPenHoverResultsMap_[eventId].push_back(hoverEventTarget);
    eventManager->PenHoverTest(touchEvent, frameNode, touchRestrict);
    EXPECT_FALSE(eventManager->lastPenHoverResultsMap_.empty());
    EXPECT_FALSE(eventManager->curPenHoverResultsMap_.empty());
    EXPECT_FALSE(eventManager->curPenHoverMoveResultsMap_.empty());
}

/**
 * @tc.name: PenHoverTest002
 * @tc.desc: Test PenHoverTest function.
 */
HWTEST_F(EventManagerTestNg, PenHoverTest002, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    const int nodeId = 10008;
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::LOCATION_BUTTON_ETS_TAG, nodeId, nullptr);
    ASSERT_NE(frameNode, nullptr);
    TouchRestrict touchRestrict;
    TouchEvent touchEvent;
    int32_t eventId = 1;
    touchEvent.SetX(100.0).SetY(100.0).SetOriginalId(eventId).SetId(eventId);
    touchEvent.sourceTool = SourceTool::PEN;

    touchEvent.SetType(TouchType::PROXIMITY_OUT);
    auto hoverEventTarget = AceType::MakeRefPtr<HoverEventTarget>(V2::LOCATION_BUTTON_ETS_TAG, nodeId);
    eventManager->curPenHoverResultsMap_[eventId].push_back(hoverEventTarget);
    eventManager->PenHoverTest(touchEvent, frameNode, touchRestrict);
    EXPECT_FALSE(eventManager->lastPenHoverResultsMap_.empty());
    EXPECT_FALSE(eventManager->curPenHoverResultsMap_.empty());
    EXPECT_FALSE(eventManager->curPenHoverMoveResultsMap_.empty());
}

/**
 * @tc.name: PenHoverTest003
 * @tc.desc: Test PenHoverTest function.
 */
HWTEST_F(EventManagerTestNg, PenHoverTest003, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    const int nodeId = 10008;
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::LOCATION_BUTTON_ETS_TAG, nodeId, nullptr);
    ASSERT_NE(frameNode, nullptr);
    TouchRestrict touchRestrict;
    TouchEvent touchEvent;
    int32_t eventId = 1;
    touchEvent.SetX(100.0).SetY(100.0).SetOriginalId(eventId).SetId(eventId);
    touchEvent.sourceTool = SourceTool::PEN;

    touchEvent.SetType(TouchType::HOVER_MOVE);
    auto hoverEventTarget = AceType::MakeRefPtr<HoverEventTarget>(V2::LOCATION_BUTTON_ETS_TAG, nodeId);
    eventManager->curPenHoverResultsMap_[eventId].push_back(hoverEventTarget);
    eventManager->PenHoverTest(touchEvent, frameNode, touchRestrict);
    EXPECT_FALSE(eventManager->lastPenHoverResultsMap_.empty());
    EXPECT_FALSE(eventManager->curPenHoverResultsMap_.empty());
    EXPECT_FALSE(eventManager->curPenHoverMoveResultsMap_.empty());
}

/**
 * @tc.name: DispatchPenHoverMoveEventNG004
 * @tc.desc: Test DispatchPenHoverMoveEventNG function.
 */
HWTEST_F(EventManagerTestNg, DispatchPenHoverMoveEventNG004, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    const int nodeId = 10008;
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::LOCATION_BUTTON_ETS_TAG, nodeId, nullptr);
    ASSERT_NE(frameNode, nullptr);
    TouchRestrict touchRestrict;
    TouchEvent touchEvent;
    int32_t eventId = 1;
    touchEvent.SetX(100.0).SetY(100.0).SetOriginalId(eventId).SetId(eventId);
    touchEvent.sourceTool = SourceTool::PEN;
    int32_t doneId = 0;

    auto hoverEventTarget = AceType::MakeRefPtr<HoverEventTarget>(V2::LOCATION_BUTTON_ETS_TAG, nodeId);
    hoverEventTarget->onPenHoverMoveEventCallback_ = nullptr;
    eventManager->curPenHoverMoveResultsMap_[eventId].push_back(hoverEventTarget);
    eventManager->DispatchPenHoverMoveEventNG(touchEvent);
    EXPECT_FALSE(eventManager->curPenHoverMoveResultsMap_.empty());

    eventManager->curPenHoverMoveResultsMap_.clear();
    hoverEventTarget->onPenHoverMoveEventCallback_ = [&doneId](HoverInfo& hoverInfo) {
        hoverInfo.SetStopPropagation(false);
        ++doneId;
    };
    eventManager->curPenHoverMoveResultsMap_[eventId].push_back(hoverEventTarget);
    eventManager->DispatchPenHoverMoveEventNG(touchEvent);
    EXPECT_EQ(doneId, 1);

    eventManager->curPenHoverMoveResultsMap_.clear();
    auto hoverEventTarget2 = AceType::MakeRefPtr<HoverEventTarget>(V2::LOCATION_BUTTON_ETS_TAG, nodeId);
    hoverEventTarget2->onPenHoverMoveEventCallback_ = [&doneId](HoverInfo& hoverInfo) {
        hoverInfo.SetStopPropagation(false);
        ++doneId;
    };
    eventManager->curPenHoverMoveResultsMap_[eventId - 1].push_back(hoverEventTarget2);
    eventManager->DispatchPenHoverMoveEventNG(touchEvent);
    EXPECT_EQ(doneId, 1);
}


/**
 * @tc.name: DispatchPenHoverEventNG005
 * @tc.desc: Test DispatchPenHoverEventNG function.
 */
HWTEST_F(EventManagerTestNg, DispatchPenHoverEventNG005, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    TouchEvent touchEvent;
    int32_t eventId = 1;
    touchEvent.SetX(100.0).SetY(100.0).SetOriginalId(eventId).SetId(eventId);

    int32_t doneId = 0;
    const int nodeId1 = 10007;
    const int nodeId2 = 10008;
    const int nodeId3 = 10009;
    const int nodeId4 = 10010;
    auto hoverEventTarget1 = AceType::MakeRefPtr<HoverEventTarget>(V2::LOCATION_BUTTON_ETS_TAG, nodeId1);
    auto hoverEventTarget2 = AceType::MakeRefPtr<HoverEventTarget>(V2::LOCATION_BUTTON_ETS_TAG, nodeId2);
    auto hoverEventTarget3 = AceType::MakeRefPtr<HoverEventTarget>(V2::LOCATION_BUTTON_ETS_TAG, nodeId3);
    auto hoverEventTarget4 = AceType::MakeRefPtr<HoverEventTarget>(V2::LOCATION_BUTTON_ETS_TAG, nodeId4);
    hoverEventTarget2->onPenHoverEventCallback_ = nullptr;
    hoverEventTarget3->onPenHoverEventCallback_ = [&doneId](bool isHovered, HoverInfo& hoverInfo) {
        hoverInfo.SetStopPropagation(false);
        ++doneId;
    };

    std::vector<std::unordered_map<int32_t, HoverTestResult>> lastPenHoverResultsMap = {
        {},
        {{0, {hoverEventTarget1}}},
        {{eventId, {hoverEventTarget1}}},
        {{eventId, {hoverEventTarget1, hoverEventTarget2}}},
        {{eventId, {hoverEventTarget1, hoverEventTarget2, hoverEventTarget3}}}
    };
    std::vector<std::unordered_map<int32_t, HoverTestResult>> curPenHoverResultsMap = {
        {{0, {hoverEventTarget1}}},
        {{eventId, {hoverEventTarget2}}},
        {{eventId, {hoverEventTarget2, hoverEventTarget3}}},
        {{eventId, {hoverEventTarget2, hoverEventTarget3, hoverEventTarget4}}}
    };
    std::vector<int> lastPenHoverDispatchLength = {0, 1, 2, 3};

    for (auto& lastMap : lastPenHoverResultsMap) {
        for (auto& curMap : curPenHoverResultsMap) {
            for (auto& len : lastPenHoverDispatchLength) {
                eventManager->lastPenHoverResultsMap_ = lastMap;
                eventManager->curPenHoverResultsMap_ = curMap;
                eventManager->lastPenHoverDispatchLength_ = len;
                eventManager->DispatchPenHoverEventNG(touchEvent);
            }
        }
    }
    ASSERT_EQ(doneId, 8);
}

/**
 * @tc.name: UpdatePenHoverMoveNode006
 * @tc.desc: Test UpdatePenHoverMoveNode function.
 */
HWTEST_F(EventManagerTestNg, UpdatePenHoverMoveNode006, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    const int nodeId = 10008;

    TouchEvent touchEvent;
    int32_t eventId = 1;
    touchEvent.SetX(100.0).SetY(100.0).SetOriginalId(eventId).SetId(eventId);
    touchEvent.SetType(TouchType::HOVER_MOVE);

    auto hoverEventTarget = AceType::MakeRefPtr<HoverEventTarget>(V2::LOCATION_BUTTON_ETS_TAG, nodeId);
    eventManager->curPenHoverResultsMap_[eventId].push_back(hoverEventTarget);

    TouchTestResult testResult;
    auto eventTarget = AceType::MakeRefPtr<MockTouchEventTarget>();
    testResult.push_back(eventTarget);
    eventManager->UpdatePenHoverNode(touchEvent, testResult);
    eventManager->UpdatePenHoverMoveNode(touchEvent, testResult);

    EXPECT_FALSE(eventManager->lastPenHoverResultsMap_.empty());
    EXPECT_FALSE(eventManager->curPenHoverResultsMap_.empty());
    EXPECT_FALSE(eventManager->curPenHoverMoveResultsMap_.empty());
}

/**
 * @tc.name: UpdatePenHoverMoveNode007
 * @tc.desc: Test UpdatePenHoverMoveNode function.
 */
HWTEST_F(EventManagerTestNg, UpdatePenHoverMoveNode007, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    const int nodeId1 = 10008;
    const int nodeId2 = 10009;

    TouchEvent touchEvent;
    int32_t eventId = 1;
    touchEvent.SetX(100.0).SetY(100.0).SetOriginalId(eventId).SetId(eventId);
    touchEvent.SetType(TouchType::HOVER_MOVE);

    auto hoverEventTarget = AceType::MakeRefPtr<HoverEventTarget>(V2::LOCATION_BUTTON_ETS_TAG, nodeId1);
    eventManager->curPenHoverResultsMap_[eventId].push_back(hoverEventTarget);

    TouchTestResult testResult;
    auto eventTarget = AceType::MakeRefPtr<HoverEventTarget>(V2::LOCATION_BUTTON_ETS_TAG, nodeId2);
    eventTarget->SetPenHoverCallback(nullptr);
    testResult.push_back(eventTarget);

    eventManager->UpdatePenHoverNode(touchEvent, testResult);
    eventManager->UpdatePenHoverMoveNode(touchEvent, testResult);

    EXPECT_FALSE(eventManager->lastPenHoverResultsMap_.empty());
    EXPECT_FALSE(eventManager->curPenHoverResultsMap_.empty());
    EXPECT_FALSE(eventManager->curPenHoverMoveResultsMap_.empty());
}

/**
 * @tc.name: UpdatePenHoverMoveNode008
 * @tc.desc: Test UpdatePenHoverMoveNode function.
 */
HWTEST_F(EventManagerTestNg, UpdatePenHoverMoveNode008, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    const int nodeId1 = 10008;
    const int nodeId2 = 10009;

    TouchEvent touchEvent;
    int32_t eventId = 1;
    touchEvent.SetX(100.0).SetY(100.0).SetOriginalId(eventId).SetId(eventId);
    touchEvent.SetType(TouchType::HOVER_MOVE);

    auto hoverEventTarget = AceType::MakeRefPtr<HoverEventTarget>(V2::LOCATION_BUTTON_ETS_TAG, nodeId1);
    eventManager->curPenHoverResultsMap_[eventId].push_back(hoverEventTarget);

    TouchTestResult testResult;
    auto eventTarget = AceType::MakeRefPtr<HoverEventTarget>(V2::LOCATION_BUTTON_ETS_TAG, nodeId2);
    const OnHoverFunc onHover = [](bool, HoverInfo) {};
    eventTarget->SetPenHoverCallback(onHover);
    testResult.push_back(eventTarget);

    eventManager->UpdatePenHoverNode(touchEvent, testResult);
    eventManager->UpdatePenHoverMoveNode(touchEvent, testResult);

    EXPECT_FALSE(eventManager->lastPenHoverResultsMap_.empty());
    EXPECT_FALSE(eventManager->curPenHoverResultsMap_.empty());
    EXPECT_FALSE(eventManager->curPenHoverMoveResultsMap_.empty());
}

/**
 * @tc.name: UpdatePenHoverMoveNode009
 * @tc.desc: Test UpdatePenHoverMoveNode function.
 */
HWTEST_F(EventManagerTestNg, UpdatePenHoverMoveNode009, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    const int nodeId1 = 10008;
    const int nodeId2 = 10009;

    TouchEvent touchEvent;
    int32_t eventId = 1;
    touchEvent.SetX(100.0).SetY(100.0).SetOriginalId(eventId).SetId(eventId);
    touchEvent.SetType(TouchType::HOVER_MOVE);

    auto hoverEventTarget = AceType::MakeRefPtr<HoverEventTarget>(V2::LOCATION_BUTTON_ETS_TAG, nodeId1);
    eventManager->curPenHoverResultsMap_[eventId].push_back(hoverEventTarget);

    TouchTestResult testResult;
    auto eventTarget = AceType::MakeRefPtr<HoverEventTarget>(V2::LOCATION_BUTTON_ETS_TAG, nodeId2);
    const OnHoverMoveFunc onHover = [](HoverInfo) {};
    eventTarget->SetPenHoverMoveCallback(onHover);
    testResult.push_back(eventTarget);

    eventManager->UpdatePenHoverNode(touchEvent, testResult);
    eventManager->UpdatePenHoverMoveNode(touchEvent, testResult);

    EXPECT_FALSE(eventManager->lastPenHoverResultsMap_.empty());
    EXPECT_FALSE(eventManager->curPenHoverResultsMap_.empty());
    EXPECT_FALSE(eventManager->curPenHoverMoveResultsMap_.empty());
}
} // namespace OHOS::Ace::NG