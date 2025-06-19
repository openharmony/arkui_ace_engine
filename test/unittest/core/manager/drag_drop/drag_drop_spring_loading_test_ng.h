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

#ifndef TEST_UNITTEST_CORE_MANAGER_DRAG_DROP_DRAG_DROP_SPRING_LOADING_TEST_NG_H
#define TEST_UNITTEST_CORE_MANAGER_DRAG_DROP_DRAG_DROP_SPRING_LOADING_TEST_NG_H

#include "gtest/gtest.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/unittest/core/manager/drag_drop_manager_test_ng.h"

#include "core/components_ng/manager/drag_drop/drag_drop_spring_loading/drag_drop_spring_loading_state_base.h"
#include "core/components_ng/manager/drag_drop/drag_drop_spring_loading/drag_drop_spring_loading_state_machine.h"

namespace OHOS::Ace::NG {
const Point DEFAULT_POINT(50, 50);
const std::string DROP_INFO("DragSpringLoadingTestNg");

enum class DragDropSpringLoadingReceivedInput {
    NOTIFY_MOVE = 1 << 0,
    NOTIFY_INTERCEPT = 1 << 1,
    THRESHOLD = 1 << 2,
    INTERCEPT = 1 << 3,
    BEGIN_ONENTER = 1 << 4,
    UPDATE_ONENTER = 1 << 5,
    END_ONENTER = 1 << 6,
    CANCEL_ONENTER = 1 << 7,
    IDLE_ONENTER = 1 << 8,
};

constexpr int32_t DRAG_DROP_SPRING_LOADING_DETECTOR_SET_USERCONFIG = 240;

struct SpringLoadingParamsTestCase {
    bool hasFrameNode = true;
    bool hasEventHub = true;

    SpringLoadingParamsTestCase(bool hasFrameNode, bool hasEventHub)
        : hasFrameNode(hasFrameNode), hasEventHub(hasEventHub)
    {}
};

struct SpringLoadingPreInfoTestCase {
    bool hasPreTimeStamp = false;
    bool hasPreMovePoint = false;

    SpringLoadingPreInfoTestCase(bool hasPreTimeStamp, bool hasPreMovePoint)
        : hasPreTimeStamp(hasPreTimeStamp), hasPreMovePoint(hasPreMovePoint)
    {}
};

struct DragDropSpringLoadingStateTestCase {
    DragDropSpringLoadingState originStatus = DragDropSpringLoadingState::IDLE;
    DragDropSpringLoadingReceivedInput receivedInput = DragDropSpringLoadingReceivedInput::NOTIFY_MOVE;
    DragDropSpringLoadingState expectStatus = DragDropSpringLoadingState::IDLE;
    bool hasCallback = true;
    std::string extraInfo = DROP_INFO;
    DragDropSpringLoadingStateTestCase(DragDropSpringLoadingReceivedInput receivedInput,
        DragDropSpringLoadingState originStatus, DragDropSpringLoadingState expectStatus, bool hasCallback,
        std::string extraInfo = DROP_INFO)
        : originStatus(originStatus), receivedInput(receivedInput), expectStatus(expectStatus),
          hasCallback(hasCallback), extraInfo(extraInfo)
    {}
};

struct DragDropSpringLoadingDetectorTestCase : public DragDropSpringLoadingStateTestCase {
    int32_t notifySequence = 0;
    Point movePoint;
    bool isMovementExceedThreshold = false;
    bool hasDefaultFrameNode = false;
    SpringLoadingParamsTestCase paramsTestCase;
    SpringLoadingPreInfoTestCase preInfoTestCase;
    DragDropSpringLoadingDetectorTestCase(DragDropSpringLoadingReceivedInput receivedInput,
        DragDropSpringLoadingState originStatus, DragDropSpringLoadingState expectStatus, int32_t notifySequence,
        Point movePoint = DEFAULT_POINT, bool hasCallback = true, bool isMovementExceedThreshold = false,
        bool hasDefaultFrameNode = false,
        SpringLoadingParamsTestCase paramsTestCase = SpringLoadingParamsTestCase(true, true),
        SpringLoadingPreInfoTestCase preInfoTestCase = SpringLoadingPreInfoTestCase(false, false))
        : DragDropSpringLoadingStateTestCase(receivedInput, originStatus, expectStatus, hasCallback),
          notifySequence(notifySequence), movePoint(movePoint), isMovementExceedThreshold(isMovementExceedThreshold),
          hasDefaultFrameNode(hasDefaultFrameNode), paramsTestCase(paramsTestCase), preInfoTestCase(preInfoTestCase)
    {}
};

struct DragDropSpringLoadingStateHandler : public DragDropSpringLoadingStateTestCase {
    int32_t notifySequence = 0;
    bool abort = false;
    bool transitionFailed = false;
    int32_t updateNotifyCount = DEFAULT_UPDATE_NOTIFY_COUNT;
    DragDropSpringLoadingStateHandler(DragDropSpringLoadingReceivedInput receivedInput,
        DragDropSpringLoadingState originStatus, DragDropSpringLoadingState expectStatus, bool hasCallback,
        int32_t notifySequence, bool abort = false, bool transitionFailed = false,
        int32_t updateNotifyCount = DEFAULT_UPDATE_NOTIFY_COUNT)
        : DragDropSpringLoadingStateTestCase(receivedInput, originStatus, expectStatus, hasCallback),
          notifySequence(notifySequence), abort(abort), transitionFailed(transitionFailed),
          updateNotifyCount(updateNotifyCount)
    {}
};

class DragSpringLoadingTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp();
    void TearDown() {};

protected:
    RefPtr<FrameNode> dragFrameNode_;
    RefPtr<FrameNode> dropFrameNode_;
    RefPtr<DragDropSpringLoadingDetector> detector_;
    uint64_t curTimeStamp_ = 0;

    static testing::AssertionResult CheckDragDropSpringLoadingStatus(
        int32_t caseNum, DragDropSpringLoadingState dragStatus, DragDropSpringLoadingState expectStatus);
    static testing::AssertionResult CheckDragDropSpringLoadingNotifySequence(
        int32_t caseNum, int32_t notifySequence, int32_t expectnotifySequence);

    void HandleMoveInput(const DragDropSpringLoadingDetectorTestCase& testCase);
    void HandleNotifyInterceptInput(const DragDropSpringLoadingDetectorTestCase& testCase);
    void HandleThresholdInput(const DragDropSpringLoadingDetectorTestCase& testCase);
};
} // namespace OHOS::Ace::NG
#endif
