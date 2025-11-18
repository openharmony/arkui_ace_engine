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
#include "test/unittest/core/event/event_manager_test_ng.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/mock/core/common/mock_window.h"
#include "test/mock/core/common/mock_frontend.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {

class MouseEventTargetTest : public MouseEventTarget {
    DECLARE_ACE_TYPE(MouseEventTargetTest, MouseEventTarget);

public:
    MouseEventTargetTest(
        const std::string& nodeName, int32_t nodeId, bool setStopPropagation = false, int32_t expectedResult = 0)
        : MouseEventTarget(nodeName, nodeId), expectedResult_(expectedResult)
    {
        SetCallback([setStopPropagation, this](MouseInfo& info) {
            info.SetStopPropagation(setStopPropagation);
            callbackInvokeCount_++;
        });
    }

    int32_t GetCallbackInvokeCount() const
    {
        return callbackInvokeCount_;
    }

    void ResetCallbackInvokeCount()
    {
        callbackInvokeCount_ = 0;
    }

    int32_t GetExpectedResult() const
    {
        return expectedResult_;
    }

private:
    int32_t callbackInvokeCount_ = 0;
    int32_t expectedResult_ = 0;
};

class EventManagerDispatchMouseEventNGTwoTest : public EventManagerTestNg {
public:
    static void SetUpTestSuite()
    {
        EventManagerTestNg::SetUpTestSuite();
    }
    static void TearDownTestSuite()
    {
        EventManagerTestNg::TearDownTestSuite();
    }
};

class APIVersionGuard final {
public:
    explicit APIVersionGuard(int32_t apiVersion)
    {
        backupApiVersion_ = AceApplicationInfo::GetInstance().GetApiTargetVersion();
        AceApplicationInfo::GetInstance().SetApiTargetVersion(apiVersion);
    }

    ~APIVersionGuard()
    {
        AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion_);
    }

private:
    int32_t backupApiVersion_ = 0;
};

/**
 * @tc.name: EventManagerDispatchMouseEventNGTest010
 * @tc.desc: API level greater and equal to 13, all kinds of MouseButton event can dispatch to pressedTestResult.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerDispatchMouseEventNGTwoTest, EventManagerDispatchMouseEventNGTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set API level 13.
     * @tc.expected: current API level equal to 13.
     */
    APIVersionGuard aPIVersionGuard(static_cast<int32_t>(PlatformVersion::VERSION_THIRTEEN));
    ASSERT_EQ(static_cast<int32_t>(PlatformVersion::VERSION_THIRTEEN),
        AceApplicationInfo::GetInstance().GetApiTargetVersion());

    const std::vector<MockMouseEvent> mockMouseEvents = {
        { MouseAction::PRESS, MouseButton::NONE_BUTTON, false },
        { MouseAction::PRESS, MouseButton::LEFT_BUTTON, true },
        { MouseAction::PRESS, MouseButton::RIGHT_BUTTON, true },
        { MouseAction::PRESS, MouseButton::MIDDLE_BUTTON, true },
        { MouseAction::PRESS, MouseButton::BACK_BUTTON, true },
        { MouseAction::PRESS, MouseButton::FORWARD_BUTTON, true },
        { MouseAction::PRESS, MouseButton::SIDE_BUTTON, true },
        { MouseAction::PRESS, MouseButton::EXTRA_BUTTON, true },
        { MouseAction::PRESS, MouseButton::TASK_BUTTON, true },
    };

    /**
     * @tc.steps: step2. Inject mock mouse event contains MouseButton and MouseAction == MouseAction::PRESS.
     * @tc.expected: currMouseTestResultsMap_[0] equals to pressMouseTestResultsMap_[button]
     */
    for (auto mockMouseEvent : mockMouseEvents) {
        MouseEvent event;
        event.action = mockMouseEvent.action;
        event.button = mockMouseEvent.button;

        std::vector<RefPtr<MouseEventTargetTest>> testCases = {
            AceType::MakeRefPtr<MouseEventTargetTest>("0", 0, false),
            AceType::MakeRefPtr<MouseEventTargetTest>("1", 1, false),
            AceType::MakeRefPtr<MouseEventTargetTest>("2", 2, false),
        };

        /**
         * @tc.steps: step3. Create EventManager.
         * @tc.expected: eventManager is not null.
         */
        auto eventManager = AceType::MakeRefPtr<EventManager>();
        ASSERT_NE(eventManager, nullptr);
        eventManager->currMouseTestResultsMap_[0].emplace_back(testCases[0]);
        eventManager->currMouseTestResultsMap_[0].emplace_back(testCases[1]);
        eventManager->currMouseTestResultsMap_[0].emplace_back(testCases[2]);
        eventManager->DispatchMouseEventNG(event);
        PressMouseInfo key { 0, event.button };
        EXPECT_EQ(eventManager->pressMouseTestResultsMap_[key] == eventManager->currMouseTestResultsMap_[0],
            mockMouseEvent.expectedResult);
    }
}

/**
 * @tc.name: EventManagerDispatchMouseEventNGTest011
 * @tc.desc: DispatchMouseEventNG only work for six kinds(press/release/move/window_enter/window_leave/cancel) mouse
 * action.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerDispatchMouseEventNGTwoTest, EventManagerDispatchMouseEventNGTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create mock mouse event with all kind of MouseAction.
     */
    const std::vector<MockMouseEvent> mockMouseEvents = {
        { MouseAction::NONE, MouseButton::NONE_BUTTON, false },
        { MouseAction::PRESS, MouseButton::LEFT_BUTTON, true },
        { MouseAction::RELEASE, MouseButton::RIGHT_BUTTON, true },
        { MouseAction::MOVE, MouseButton::MIDDLE_BUTTON, true },
        { MouseAction::WINDOW_ENTER, MouseButton::BACK_BUTTON, true },
        { MouseAction::WINDOW_LEAVE, MouseButton::FORWARD_BUTTON, true },
        { MouseAction::HOVER, MouseButton::SIDE_BUTTON, false },
        { MouseAction::HOVER_ENTER, MouseButton::EXTRA_BUTTON, false },
        { MouseAction::HOVER_MOVE, MouseButton::TASK_BUTTON, false },
        { MouseAction::HOVER_EXIT, MouseButton::NONE_BUTTON, false },
        { MouseAction::PULL_DOWN, MouseButton::LEFT_BUTTON, false },
        { MouseAction::PULL_MOVE, MouseButton::RIGHT_BUTTON, false },
        { MouseAction::PULL_UP, MouseButton::MIDDLE_BUTTON, false },
        { MouseAction::CANCEL, MouseButton::BACK_BUTTON, true },
    };

    /**
     * @tc.steps: step2. traversal all kinds of MouseAction,inject mock mouse event into EventManager.
     * @tc.expected: result of invoke DispatchMouseEventNG equal to expected result.
     */
    for (auto mockMouseEvent : mockMouseEvents) {
        MouseEvent event;
        event.action = mockMouseEvent.action;
        event.button = mockMouseEvent.button;

        std::vector<RefPtr<MouseEventTargetTest>> testCases = {
            AceType::MakeRefPtr<MouseEventTargetTest>("0", 0, true),
            AceType::MakeRefPtr<MouseEventTargetTest>("1", 1, true),
            AceType::MakeRefPtr<MouseEventTargetTest>("2", 2, true),
        };

        /**
         * @tc.steps: step3. Create eventManager.
         * @tc.expected: eventManager not equal to nullptr.
         */
        auto eventManager = AceType::MakeRefPtr<EventManager>();
        ASSERT_NE(eventManager, nullptr);

        eventManager->currMouseTestResultsMap_[0].emplace_back(testCases[0]);
        eventManager->currMouseTestResultsMap_[0].emplace_back(testCases[1]);
        eventManager->currMouseTestResultsMap_[0].emplace_back(testCases[2]);

        auto result = eventManager->DispatchMouseEventNG(event);
        EXPECT_EQ(result, mockMouseEvent.expectedResult) << static_cast<int32_t>(event.action);
    }
}

/**
 * @tc.name: GetOrRefreshMatrixFromCache
 * @tc.desc: Test GetOrRefreshMatrixFromCache func
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerDispatchMouseEventNGTwoTest, GetOrRefreshMatrixFromCacheNGTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create
     * @tc.expected: expect The function return value is true when width or height is nearZero.
     */
    MockPipelineContext::SetUp();
    RefPtr<FrameNode> node = FrameNode::CreateFrameNode("0", 0, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(node, nullptr);
    auto mockRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    ASSERT_NE(mockRenderContext, nullptr);
    auto pipeline = NG::PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    node->renderContext_ = mockRenderContext;
    node->context_ = AceType::RawPtr(pipeline);

    node->cacheMatrixInfo_ = CacheMatrixInfo();
    mockRenderContext->paintRect_ = RectF(0, 0, 10, 0);
    CacheMatrixInfo cacheMatrixInfo = node->GetOrRefreshMatrixFromCache();
    EXPECT_EQ(cacheMatrixInfo.paintRectWithTransform.Width(), 0);

    node->isTransformNotChanged_ = false;
    mockRenderContext->rect_ = RectF(0, 0, 10, 0);
    mockRenderContext->paintRect_ = RectF(0, 0, 10, 0);
    cacheMatrixInfo = node->GetOrRefreshMatrixFromCache();
    EXPECT_EQ(cacheMatrixInfo.paintRectWithTransform.Width(), 10);
    EXPECT_EQ(node->isTransformNotChanged_, true);

    node->isTransformNotChanged_ = false;
    cacheMatrixInfo = node->GetOrRefreshMatrixFromCache(true);
    EXPECT_EQ(cacheMatrixInfo.paintRectWithTransform.Width(), 10);
    EXPECT_EQ(node->isTransformNotChanged_, true);

    node->cacheMatrixInfo_ = CacheMatrixInfo();
    node->isTransformNotChanged_ = false;
    cacheMatrixInfo = node->GetOrRefreshMatrixFromCache();
    EXPECT_EQ(cacheMatrixInfo.paintRectWithTransform.Width(), 10);
    EXPECT_EQ(node->isTransformNotChanged_, true);
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: DispatchTouchEventAndCheck
 * @tc.desc: Test DispatchTouchEventAndCheck func
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerDispatchMouseEventNGTwoTest, DispatchTouchEventAndCheckTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    auto resultId = ElementRegister::GetInstance()->MakeUniqueId();
    TouchTestResult touchTestResults;
    auto panRecognizer = AceType::MakeRefPtr<PanRecognizer>(
        DEFAULT_PAN_FINGER, PanDirection { PanDirection::NONE }, DEFAULT_PAN_DISTANCE.ConvertToPx());
    panRecognizer->OnPending();
    touchTestResults.push_back(panRecognizer);
    eventManager->touchTestResults_.emplace(resultId, touchTestResults);
    TouchEvent event;
    event.id = resultId;
    event.type = TouchType::DOWN;
    RefPtr<GestureScope> scope = AceType::MakeRefPtr<GestureScope>(resultId);
    ASSERT_NE(scope, nullptr);
    ASSERT_NE(eventManager->refereeNG_, nullptr);
    scope->AddMember(panRecognizer);
    eventManager->refereeNG_->gestureScopes_.insert(std::make_pair(resultId, scope));
    eventManager->DispatchTouchEventAndCheck(event, false);
    EXPECT_EQ(panRecognizer->GetRefereeState(), RefereeState::FAIL);
}
} // namespace OHOS::Ace::NG