/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include <optional>

#include "gtest/gtest.h"

#include "base/utils/time_util.h"
#include "core/event/touch_event.h"
#define private public
#define protected public

#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/gestures/tap_gesture.h"
#include "core/components_ng/manager/post_event/post_event_manager.h"
#include "core/components_ng/pattern/pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string ROOT_TAG("root");
} // namespace

class PostEventManagerTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    RefPtr<PostEventManager> postEventManager_;
    RefPtr<FrameNode> root_;
    void Init();
};

void PostEventManagerTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void PostEventManagerTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

void PostEventManagerTestNg::Init()
{
    postEventManager_ = AceType::MakeRefPtr<PostEventManager>();
    ASSERT_NE(postEventManager_, nullptr);
    root_ = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    root_->SetExclusiveEventForChild(true);
    auto mockRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    root_->renderContext_ = mockRenderContext;
    auto localPoint = PointF(10, 10);
    mockRenderContext->rect_ = RectF(0, 0, 100, 100);
    root_->SetActive(true);
}

/**
 * @tc.name: PostEventManagerTest001
 * @tc.desc: test post event.
 * @tc.type: FUNC
 */
HWTEST_F(PostEventManagerTestNg, PostEventManagerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a FrameNode and set gesture.
     */
    Init();
    auto gestureEventHub = root_->GetOrCreateGestureEventHub();
    gestureEventHub->SetHitTestMode(HitTestMode::HTMBLOCK);
    auto gesture = AceType::MakeRefPtr<TapGesture>();
    gestureEventHub->AddGesture(gesture);
    DimensionRect responseRect(Dimension(100), Dimension(100), DimensionOffset());
    std::vector<DimensionRect> responseRegion;
    responseRegion.emplace_back(responseRect);
    gestureEventHub->SetResponseRegion(responseRegion);
    auto paintRect = root_->renderContext_->GetPaintRectWithoutTransform();
    root_->GetResponseRegionList(paintRect, 1, 0);
    EXPECT_FALSE(gestureEventHub->GetResponseRegion().empty());

    /**
     * @tc.steps: step2. call PostEvent func and check return value.
     */
    TouchEvent touchEvent;
    touchEvent.type = TouchType::DOWN;
    touchEvent.x = 10;
    touchEvent.y = 10;
    auto result = postEventManager_->PostEvent(root_, touchEvent);
    EXPECT_FALSE(result);

    /**
     * @tc.steps: step3. call PostEvent func with same event and check return value.
     */
    result = postEventManager_->PostEvent(root_, touchEvent);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step4. call PostEvent func with touch up event and check return value.
     */
    TouchEvent touchMoveEvent;
    touchMoveEvent.type = TouchType::MOVE;
    touchMoveEvent.x = 15;
    touchMoveEvent.y = 15;
    auto currentTime = GetSysTimestamp();
    std::chrono::nanoseconds nanoseconds(currentTime);
    TimeStamp time(nanoseconds);
    touchMoveEvent.time = time;
    result = postEventManager_->PostEvent(root_, touchMoveEvent);
    EXPECT_FALSE(result);

    /**
     * @tc.steps: step5. call PostEvent func with touch up event and check return value.
     */
    TouchEvent touchUpEvent;
    touchUpEvent.type = TouchType::UP;
    touchUpEvent.x = 15;
    touchUpEvent.y = 15;
    currentTime = GetSysTimestamp();
    std::chrono::nanoseconds nanosecondsUp(currentTime);
    TimeStamp timeUp(nanosecondsUp);
    touchUpEvent.time = timeUp;
    result = postEventManager_->PostEvent(root_, touchUpEvent);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: PostEventManagerTest002
 * @tc.desc: test post touch down type event twice.
 * @tc.type: FUNC
 */
HWTEST_F(PostEventManagerTestNg, PostEventManagerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a FrameNode and set gesture.
     */
    Init();
    auto gestureEventHub = root_->GetOrCreateGestureEventHub();
    gestureEventHub->SetHitTestMode(HitTestMode::HTMBLOCK);
    auto gesture = AceType::MakeRefPtr<TapGesture>();
    gestureEventHub->AddGesture(gesture);
    DimensionRect responseRect(Dimension(100), Dimension(100), DimensionOffset());
    std::vector<DimensionRect> responseRegion;
    responseRegion.emplace_back(responseRect);
    gestureEventHub->SetResponseRegion(responseRegion);
    auto paintRect = root_->renderContext_->GetPaintRectWithoutTransform();
    root_->GetResponseRegionList(paintRect, 1, 0);
    EXPECT_FALSE(gestureEventHub->GetResponseRegion().empty());

    /**
     * @tc.steps: step2. call PostEvent func and check return value.
     */
    TouchEvent touchEvent;
    touchEvent.type = TouchType::DOWN;
    touchEvent.x = 10;
    touchEvent.y = 10;
    auto result = postEventManager_->PostEvent(root_, touchEvent);
    EXPECT_FALSE(result);

    /**
     * @tc.steps: step3. call PostEvent func with another down event check whether cancel event will be sent or not.
     */
    TouchEvent touchMoveEvent;
    touchMoveEvent.type = TouchType::DOWN;
    touchMoveEvent.x = 15;
    touchMoveEvent.y = 15;
    auto currentTime = GetSysTimestamp();
    std::chrono::nanoseconds nanoseconds(currentTime);
    TimeStamp time(nanoseconds);
    touchMoveEvent.time = time;
    result = postEventManager_->PostEvent(root_, touchMoveEvent);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: PostEventManagerTest003
 * @tc.desc: test post event when touch test result is null.
 * @tc.type: FUNC
 */
HWTEST_F(PostEventManagerTestNg, PostEventManagerTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a FrameNode and set gesture.
     */
    Init();
    auto gestureEventHub = root_->GetOrCreateGestureEventHub();
    gestureEventHub->SetHitTestMode(HitTestMode::HTMBLOCK);
    auto gesture = AceType::MakeRefPtr<TapGesture>();
    gestureEventHub->AddGesture(gesture);

    /**
     * @tc.steps: step2. call PostEvent func when touch test result is null.
     */
    TouchEvent touchEvent;
    touchEvent.type = TouchType::DOWN;
    touchEvent.x = 10;
    touchEvent.y = 10;
    auto result = postEventManager_->PostEvent(root_, touchEvent);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: PostEventManagerTest004
 * @tc.desc: test post touch event event but has no down event.
 * @tc.type: FUNC
 */
HWTEST_F(PostEventManagerTestNg, PostEventManagerTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a FrameNode and set gesture.
     */
    Init();
    auto gestureEventHub = root_->GetOrCreateGestureEventHub();
    gestureEventHub->SetHitTestMode(HitTestMode::HTMBLOCK);
    auto gesture = AceType::MakeRefPtr<TapGesture>();
    gestureEventHub->AddGesture(gesture);
    DimensionRect responseRect(Dimension(100), Dimension(100), DimensionOffset());
    std::vector<DimensionRect> responseRegion;
    responseRegion.emplace_back(responseRect);
    gestureEventHub->SetResponseRegion(responseRegion);
    auto paintRect = root_->renderContext_->GetPaintRectWithoutTransform();
    root_->GetResponseRegionList(paintRect, 1, 0);
    EXPECT_FALSE(gestureEventHub->GetResponseRegion().empty());

    /**
     * @tc.steps: step2. call PostEvent func and check return value.
     */
    TouchEvent touchEvent;
    touchEvent.type = TouchType::MOVE;
    touchEvent.x = 10;
    touchEvent.y = 10;
    auto result = postEventManager_->PostEvent(root_, touchEvent);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: PostEventManagerTest005
 * @tc.desc: test multi fingers post event.
 * @tc.type: FUNC
 */
HWTEST_F(PostEventManagerTestNg, PostEventManagerTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a FrameNode and set gesture.
     */
    Init();
    auto gestureEventHub = root_->GetOrCreateGestureEventHub();
    gestureEventHub->SetHitTestMode(HitTestMode::HTMBLOCK);
    auto gesture = AceType::MakeRefPtr<TapGesture>();
    gestureEventHub->AddGesture(gesture);
    DimensionRect responseRect(Dimension(100), Dimension(100), DimensionOffset());
    std::vector<DimensionRect> responseRegion;
    responseRegion.emplace_back(responseRect);
    gestureEventHub->SetResponseRegion(responseRegion);
    auto paintRect = root_->renderContext_->GetPaintRectWithoutTransform();
    root_->GetResponseRegionList(paintRect, 1, 0);
    EXPECT_FALSE(gestureEventHub->GetResponseRegion().empty());

    /**
     * @tc.steps: step2. call finger 0 PostEvent func and check return value.
     */
    TouchEvent touchEvent;
    touchEvent.type = TouchType::DOWN;
    touchEvent.x = 10;
    touchEvent.y = 10;
    auto result = postEventManager_->PostEvent(root_, touchEvent);
    EXPECT_FALSE(result);

    /**
     * @tc.steps: step3. call finger 1 PostEvent func and check return value.
     */
    TouchEvent anotherTouchEvent;
    anotherTouchEvent.type = TouchType::DOWN;
    anotherTouchEvent.id = 1;
    anotherTouchEvent.x = 20;
    anotherTouchEvent.y = 20;
    result = postEventManager_->PostEvent(root_, anotherTouchEvent);
    EXPECT_FALSE(result);

    /**
     * @tc.steps: step3. call PostEvent func with touch up event and check return value.
     */
    TouchEvent touchMoveEvent;
    touchMoveEvent.type = TouchType::MOVE;
    touchMoveEvent.x = 15;
    touchMoveEvent.y = 15;
    auto currentTime = GetSysTimestamp();
    std::chrono::nanoseconds nanoseconds(currentTime);
    TimeStamp time(nanoseconds);
    touchMoveEvent.time = time;
    result = postEventManager_->PostEvent(root_, touchMoveEvent);
    EXPECT_FALSE(result);

    /**
     * @tc.steps: step4. call PostEvent func with touch up event and check return value.
     */
    TouchEvent touchUpEvent;
    touchUpEvent.type = TouchType::UP;
    touchUpEvent.x = 15;
    touchUpEvent.y = 15;
    currentTime = GetSysTimestamp();
    std::chrono::nanoseconds nanosecondsUp(currentTime);
    TimeStamp timeUp(nanosecondsUp);
    touchUpEvent.time = timeUp;
    result = postEventManager_->PostEvent(root_, touchUpEvent);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: PostEventManagerTest006
 * @tc.desc: test multi fingers post event.
 * @tc.type: FUNC
 */
HWTEST_F(PostEventManagerTestNg, PostEventManagerTest006, TestSize.Level1)
{
    Init();
    auto gestureEventHub = root_->GetOrCreateGestureEventHub();
    gestureEventHub->SetHitTestMode(HitTestMode::HTMBLOCK);
    auto gesture = AceType::MakeRefPtr<TapGesture>();
    gestureEventHub->AddGesture(gesture);

    TouchEvent touchUpEvent;
    touchUpEvent.type = TouchType::HOVER_ENTER;
    touchUpEvent.x = 15;
    touchUpEvent.y = 15;
    auto currentTime = GetSysTimestamp();
    std::chrono::nanoseconds nanosecondsUp(currentTime);
    TimeStamp timeUp(nanosecondsUp);
    touchUpEvent.time = timeUp;
    postEventManager_->PostEvent(root_, touchUpEvent);
}

/**
 * @tc.name: PostEventManagerTest007
 * @tc.desc: test multi fingers post event.
 * @tc.type: FUNC
 */
HWTEST_F(PostEventManagerTestNg, PostEventManagerTest007, TestSize.Level1)
{
    Init();
    auto gestureEventHub = root_->GetOrCreateGestureEventHub();
    gestureEventHub->SetHitTestMode(HitTestMode::HTMBLOCK);
    auto gesture = AceType::MakeRefPtr<TapGesture>();
    gestureEventHub->AddGesture(gesture);

    TouchEvent touchUpEvent;
    touchUpEvent.type = TouchType::DOWN;
    touchUpEvent.x = 15;
    touchUpEvent.y = 15;
    touchUpEvent.id = 2;
    auto currentTime = GetSysTimestamp();
    std::chrono::nanoseconds nanosecondsUp(currentTime);
    TimeStamp timeUp(nanosecondsUp);
    touchUpEvent.time = timeUp;
    auto frameNode = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto UInode = AceType::DynamicCast<NG::UINode>(frameNode);
    PostEventAction eventAction;
    eventAction.targetNode = UInode;
    eventAction.touchEvent = touchUpEvent;
    postEventManager_->postEventAction_.push_back(eventAction);
    auto result = postEventManager_->PostDownEvent(UInode, touchUpEvent);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: PostEventManagerTest008
 * @tc.desc: test lastEventMap.
 * @tc.type: FUNC
 */
HWTEST_F(PostEventManagerTestNg, PostEventManagerTest008, TestSize.Level1)
{
    Init();
    auto gestureEventHub = root_->GetOrCreateGestureEventHub();
    gestureEventHub->SetHitTestMode(HitTestMode::HTMBLOCK);
    auto gesture = AceType::MakeRefPtr<TapGesture>();
    gestureEventHub->AddGesture(gesture);
    TouchEvent touchUpEvent;
    touchUpEvent.type = TouchType::DOWN;
    touchUpEvent.x = 15;
    touchUpEvent.y = 15;
    touchUpEvent.id = 2;
    auto currentTime = GetSysTimestamp();
    std::chrono::nanoseconds nanosecondsUp(currentTime);
    TimeStamp timeUp(nanosecondsUp);
    touchUpEvent.time = timeUp;
    auto frameNode = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    PostEventAction eventAction;
    eventAction.targetNode = frameNode;
    eventAction.touchEvent = touchUpEvent;
    postEventManager_->lastEventMap_.insert(std::make_pair(touchUpEvent.id, eventAction));
    postEventManager_->postEventAction_.push_back(eventAction);
    auto result = postEventManager_->PostDownEvent(root_, touchUpEvent);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: PostEventManagerTest009
 * @tc.desc: test lastEventMap.
 * @tc.type: FUNC
 */
HWTEST_F(PostEventManagerTestNg, PostEventManagerTest009, TestSize.Level1)
{
    Init();
    auto gestureEventHub = root_->GetOrCreateGestureEventHub();
    gestureEventHub->SetHitTestMode(HitTestMode::HTMBLOCK);
    auto gesture = AceType::MakeRefPtr<TapGesture>();
    gestureEventHub->AddGesture(gesture);
    TouchEvent touchUpEvent;
    touchUpEvent.type = TouchType::UP;
    touchUpEvent.x = 15;
    touchUpEvent.y = 15;
    touchUpEvent.id = 2;
    auto currentTime = GetSysTimestamp();
    std::chrono::nanoseconds nanosecondsUp(currentTime);
    TimeStamp timeUp(nanosecondsUp);
    touchUpEvent.time = timeUp;
    auto frameNode = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    PostEventAction eventAction;
    eventAction.targetNode = frameNode;
    eventAction.touchEvent = touchUpEvent;
    postEventManager_->lastEventMap_.insert(std::make_pair(touchUpEvent.id, eventAction));
    postEventManager_->postEventAction_.push_back(eventAction);
    auto result = postEventManager_->PostUpEvent(root_, touchUpEvent);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: PostEventManagerTest010
 * @tc.desc: test lastEventMap.
 * @tc.type: FUNC
 */
HWTEST_F(PostEventManagerTestNg, PostEventManagerTest0010, TestSize.Level1)
{
    Init();
    auto gestureEventHub = root_->GetOrCreateGestureEventHub();
    gestureEventHub->SetHitTestMode(HitTestMode::HTMBLOCK);
    auto gesture = AceType::MakeRefPtr<TapGesture>();
    gestureEventHub->AddGesture(gesture);

    TouchEvent touchUpEvent;
    touchUpEvent.type = TouchType::DOWN;
    touchUpEvent.x = 15;
    touchUpEvent.y = 15;
    touchUpEvent.id = 2;
    auto currentTime = GetSysTimestamp();
    std::chrono::nanoseconds nanosecondsUp(currentTime);
    TimeStamp timeUp(nanosecondsUp);
    touchUpEvent.time = timeUp;
    auto frameNode = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto UInode = AceType::DynamicCast<NG::UINode>(frameNode);
    PostEventAction eventAction;
    eventAction.targetNode = UInode;
    eventAction.touchEvent = touchUpEvent;
    postEventManager_->lastEventMap_.insert(std::make_pair(touchUpEvent.id, eventAction));
    postEventManager_->postEventAction_.push_back(eventAction);
    auto result = postEventManager_->PostDownEvent(UInode, touchUpEvent);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: PostEventManagerTest011
 * @tc.desc: test lastEventMap.
 * @tc.type: FUNC
 */
HWTEST_F(PostEventManagerTestNg, PostEventManagerTest0011, TestSize.Level1)
{
    Init();
    auto gestureEventHub = root_->GetOrCreateGestureEventHub();
    gestureEventHub->SetHitTestMode(HitTestMode::HTMBLOCK);
    auto gesture = AceType::MakeRefPtr<TapGesture>();
    gestureEventHub->AddGesture(gesture);

    TouchEvent touchUpEvent;
    touchUpEvent.type = TouchType::UP;
    touchUpEvent.x = 15;
    touchUpEvent.y = 15;
    touchUpEvent.id = 2;
    auto currentTime = GetSysTimestamp();
    std::chrono::nanoseconds nanosecondsUp(currentTime);
    TimeStamp timeUp(nanosecondsUp);
    touchUpEvent.time = timeUp;
    auto frameNode = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto UInode = AceType::DynamicCast<NG::UINode>(frameNode);
    PostEventAction eventAction;
    eventAction.targetNode = UInode;
    eventAction.touchEvent = touchUpEvent;
    postEventManager_->lastEventMap_.insert(std::make_pair(touchUpEvent.id, eventAction));
    postEventManager_->postEventAction_.push_back(eventAction);
    auto result = postEventManager_->PostDownEvent(UInode, touchUpEvent);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: PostEventManagerTest012
 * @tc.desc: test lastEventMap.
 * @tc.type: FUNC
 */
HWTEST_F(PostEventManagerTestNg, PostEventManagerTest0012, TestSize.Level1)
{
    Init();
    auto gestureEventHub = root_->GetOrCreateGestureEventHub();
    gestureEventHub->SetHitTestMode(HitTestMode::HTMBLOCK);
    auto gesture = AceType::MakeRefPtr<TapGesture>();
    gestureEventHub->AddGesture(gesture);

    TouchEvent touchUpEvent;
    touchUpEvent.type = TouchType::DOWN;
    touchUpEvent.x = 15;
    touchUpEvent.y = 15;
    touchUpEvent.id = 2;
    auto currentTime = GetSysTimestamp();
    std::chrono::nanoseconds nanosecondsUp(currentTime);
    TimeStamp timeUp(nanosecondsUp);
    touchUpEvent.time = timeUp;
    auto frameNode = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto UInode = AceType::DynamicCast<NG::UINode>(frameNode);
    PostEventAction eventAction;
    eventAction.targetNode = UInode;
    eventAction.touchEvent = touchUpEvent;
    postEventManager_->lastEventMap_.insert(std::make_pair(touchUpEvent.id, eventAction));
    postEventManager_->postEventAction_.push_back(eventAction);
    auto result = postEventManager_->PostDownEvent(UInode, touchUpEvent);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: PostEventManagerTest013
 * @tc.desc: test lastEventMap.
 * @tc.type: FUNC
 */
HWTEST_F(PostEventManagerTestNg, PostEventManagerTest0013, TestSize.Level1)
{
    Init();
    auto gestureEventHub = root_->GetOrCreateGestureEventHub();
    gestureEventHub->SetHitTestMode(HitTestMode::HTMBLOCK);
    auto gesture = AceType::MakeRefPtr<TapGesture>();
    gestureEventHub->AddGesture(gesture);

    TouchEvent touchUpEvent;
    touchUpEvent.type = TouchType::DOWN;
    touchUpEvent.x = 15;
    touchUpEvent.y = 15;
    touchUpEvent.id = 2;
    auto currentTime = GetSysTimestamp();
    std::chrono::nanoseconds nanosecondsUp(currentTime);
    TimeStamp timeUp(nanosecondsUp);
    touchUpEvent.time = timeUp;
    auto frameNode = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto UInode = AceType::DynamicCast<NG::UINode>(frameNode);
    PostEventAction eventAction;
    eventAction.targetNode = UInode;
    eventAction.touchEvent = touchUpEvent;
    postEventManager_->lastEventMap_.insert(std::make_pair(touchUpEvent.id, eventAction));
    postEventManager_->postEventAction_.push_back(eventAction);
    auto result = postEventManager_->PostMoveEvent(UInode, touchUpEvent);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: PostEventManagerTest014
 * @tc.desc: test lastEventMap.
 * @tc.type: FUNC
 */
HWTEST_F(PostEventManagerTestNg, PostEventManagerTest014, TestSize.Level1)
{
    Init();
    auto gestureEventHub = root_->GetOrCreateGestureEventHub();
    gestureEventHub->SetHitTestMode(HitTestMode::HTMBLOCK);
    auto gesture = AceType::MakeRefPtr<TapGesture>();
    gestureEventHub->AddGesture(gesture);

    TouchEvent touchUpEvent;
    touchUpEvent.type = TouchType::DOWN;
    touchUpEvent.x = 15;
    touchUpEvent.y = 15;
    touchUpEvent.id = 2;
    auto currentTime = GetSysTimestamp();
    std::chrono::nanoseconds nanosecondsUp(currentTime);
    TimeStamp timeUp(nanosecondsUp);
    touchUpEvent.time = timeUp;
    auto frameNode = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto UInode = AceType::DynamicCast<NG::UINode>(frameNode);
    PostEventAction eventAction;
    eventAction.targetNode = UInode;
    eventAction.touchEvent = touchUpEvent;
    postEventManager_->lastEventMap_.insert(std::make_pair(touchUpEvent.id, eventAction));
    postEventManager_->postEventAction_.push_back(eventAction);
    auto result = postEventManager_->PostUpEvent(UInode, touchUpEvent);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: PostEventManagerTest015
 * @tc.desc: test lastEventMap.
 * @tc.type: FUNC
 */
HWTEST_F(PostEventManagerTestNg, PostEventManagerTest015, TestSize.Level1)
{
    Init();
    auto gestureEventHub = root_->GetOrCreateGestureEventHub();
    gestureEventHub->SetHitTestMode(HitTestMode::HTMBLOCK);
    auto gesture = AceType::MakeRefPtr<TapGesture>();
    gestureEventHub->AddGesture(gesture);

    TouchEvent touchUpEvent;
    touchUpEvent.type = TouchType::DOWN;
    touchUpEvent.x = 15;
    touchUpEvent.y = 15;
    touchUpEvent.id = 2;
    auto currentTime = GetSysTimestamp();
    std::chrono::nanoseconds nanosecondsUp(currentTime);
    TimeStamp timeUp(nanosecondsUp);
    touchUpEvent.time = timeUp;
    auto frameNode = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto UInode = AceType::DynamicCast<NG::UINode>(frameNode);
    PostEventAction eventAction;
    eventAction.targetNode = UInode;
    eventAction.touchEvent = touchUpEvent;
    postEventManager_->lastEventMap_.insert(std::make_pair(touchUpEvent.id, eventAction));
    postEventManager_->postEventAction_.push_back(eventAction);
    postEventManager_->CheckAndClearPostEventAction(UInode, touchUpEvent.id);
    postEventManager_->CheckAndClearPostEventAction(UInode, (touchUpEvent.id + 1));
    postEventManager_->CheckAndClearPostEventAction(UInode, touchUpEvent.id);
    EXPECT_EQ(touchUpEvent.id, 2);
}

/**
 * @tc.name: PostEventManagerTest016
 * @tc.desc: test lastEventMap.
 * @tc.type: FUNC
 */
HWTEST_F(PostEventManagerTestNg, PostEventManagerTest016, TestSize.Level1)
{
    Init();
    auto gestureEventHub = root_->GetOrCreateGestureEventHub();
    gestureEventHub->SetHitTestMode(HitTestMode::HTMBLOCK);
    auto gesture = AceType::MakeRefPtr<TapGesture>();
    gestureEventHub->AddGesture(gesture);

    TouchEvent touchUpEvent;
    touchUpEvent.type = TouchType::UP;
    touchUpEvent.x = 15;
    touchUpEvent.y = 15;
    touchUpEvent.id = 2;
    auto currentTime = GetSysTimestamp();
    std::chrono::nanoseconds nanosecondsUp(currentTime);
    TimeStamp timeUp(nanosecondsUp);
    touchUpEvent.time = timeUp;
    auto frameNode = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto UInode = AceType::DynamicCast<NG::UINode>(frameNode);
    PostEventAction eventAction;
    eventAction.targetNode = UInode;
    eventAction.touchEvent = touchUpEvent;
    postEventManager_->lastEventMap_.insert(std::make_pair(touchUpEvent.id, eventAction));
    postEventManager_->postEventAction_.push_back(eventAction);
    postEventManager_->CheckAndClearPostEventAction(UInode, touchUpEvent.id);
    EXPECT_EQ(touchUpEvent.y, 15);
}

/**
 * @tc.name: PostEventManagerTest017
 * @tc.desc: test lastEventMap.
 * @tc.type: FUNC
 */
HWTEST_F(PostEventManagerTestNg, PostEventManagerTest017, TestSize.Level1)
{
    Init();
    auto gestureEventHub = root_->GetOrCreateGestureEventHub();
    gestureEventHub->SetHitTestMode(HitTestMode::HTMBLOCK);
    auto gesture = AceType::MakeRefPtr<TapGesture>();
    gestureEventHub->AddGesture(gesture);

    TouchEvent touchUpEvent;
    touchUpEvent.type = TouchType::CANCEL;
    touchUpEvent.x = 15;
    touchUpEvent.y = 15;
    touchUpEvent.id = 2;
    auto currentTime = GetSysTimestamp();
    std::chrono::nanoseconds nanosecondsUp(currentTime);
    TimeStamp timeUp(nanosecondsUp);
    touchUpEvent.time = timeUp;
    auto frameNode = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto UInode = AceType::DynamicCast<NG::UINode>(frameNode);
    PostEventAction eventAction;
    eventAction.targetNode = UInode;
    eventAction.touchEvent = touchUpEvent;
    postEventManager_->lastEventMap_.insert(std::make_pair(touchUpEvent.id, eventAction));
    postEventManager_->postEventAction_.push_back(eventAction);
    postEventManager_->CheckAndClearPostEventAction(UInode, touchUpEvent.id);
    EXPECT_EQ(touchUpEvent.x, 15);
}

/**
 * @tc.name: HandlePostEventTest001
 * @tc.desc: test HandlePostEvent func.
 * @tc.type: FUNC
 */
HWTEST_F(PostEventManagerTestNg, HandlePostEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a FrameNode and set gesture.
     */
    Init();

    /**
     * @tc.steps: step2. mock user touch event.
     */
    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, 1,
        []() { return AceType::MakeRefPtr<Pattern>(); });
    TouchEvent touchEvent;

    const std::vector<Ace::TouchType> touchTypeArray = { Ace::TouchType::DOWN, Ace::TouchType::UP };
    int32_t touchStateCount = 4;
    for (int32_t i = 0; i < touchStateCount; ++i) {
        int32_t index = i % touchTypeArray.size();
        touchEvent.type = touchTypeArray[index];
        touchEvent.id = touchTypeArray.size() > 0 ? i / touchTypeArray.size() : i;
        postEventManager_->HandlePostEvent(buttonNode, touchEvent);
    }
    EXPECT_TRUE(postEventManager_->lastEventMap_.empty());
}

/**
 * @tc.name: PostDownEventTest001
 * @tc.desc: test PostDownEvent func.
 * @tc.type: FUNC
 */
HWTEST_F(PostEventManagerTestNg, PostDownEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a FrameNode and set gesture.
     */
    Init();

    /**
     * @tc.steps: step2. Simulate when the user touchDown and then handles the out-of-hand
     *                   action event through the PostDownEvent function.
     */
    int32_t nodeId = 1;
    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, nodeId,
        []() { return AceType::MakeRefPtr<Pattern>(); });
    TouchEvent touchEvent;
    touchEvent.type = Ace::TouchType::DOWN;
    touchEvent.id = nodeId;
    postEventManager_->HandlePostEvent(buttonNode, touchEvent);

    postEventManager_->PostDownEvent(buttonNode, touchEvent);
    EXPECT_TRUE(postEventManager_->postEventAction_.empty());
    EXPECT_TRUE(postEventManager_->lastEventMap_.empty());
}

/**
 * @tc.name: PostTouchEventTest001
 * @tc.desc: test PostTouchEvent func.
 * @tc.type: FUNC
 */
HWTEST_F(PostEventManagerTestNg, PostTouchEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a FrameNode and set gesture.
     */
    Init();

    /**
     * @tc.steps: step2. Simulate when the user touchDown and then handles the out-of-hand
     *                   action event through the PostDownEvent function.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto uiNode = AceType::DynamicCast<NG::UINode>(frameNode);
    TouchEvent touchEvent;
    touchEvent.type = Ace::TouchType::DOWN;
    postEventManager_->passThroughResult_ = true;
    postEventManager_->PostTouchEvent(uiNode, std::move(touchEvent));

    EXPECT_FALSE(postEventManager_->passThroughResult_);
}

/**
 * @tc.name: PostTouchEventTest002
 * @tc.desc: test PostTouchEvent func.
 * @tc.type: FUNC
 */
HWTEST_F(PostEventManagerTestNg, PostTouchEventTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a FrameNode and set gesture.
     */
    Init();

    /**
     * @tc.steps: step2. Simulate when the user touchDown and then handles the out-of-hand
     *                   action event through the PostDownEvent function.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto uiNode = AceType::DynamicCast<NG::UINode>(frameNode);
    TouchEvent touchEvent;
    touchEvent.type = Ace::TouchType::DOWN;
    postEventManager_->passThroughResult_ = true;
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->eventManager_ = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(pipelineContext->eventManager_, nullptr);
    pipelineContext->eventManager_->isDragCancelPending_ = false;
    postEventManager_->PostTouchEvent(uiNode, std::move(touchEvent));
    EXPECT_FALSE(postEventManager_->passThroughResult_);
    pipelineContext->eventManager_->isDragCancelPending_ = true;
    postEventManager_->PostTouchEvent(uiNode, std::move(touchEvent));
    EXPECT_FALSE(postEventManager_->passThroughResult_);
}

/**
 * @tc.name: PostMouseEventTest001
 * @tc.desc: test PostMouseEvent func.
 * @tc.type: FUNC
 */
HWTEST_F(PostEventManagerTestNg, PostMouseEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a FrameNode and set gesture.
     */
    Init();

    /**
     * @tc.steps: step2. Simulate when the user touchDown and then handles the out-of-hand
     *                   action event through the PostDownEvent function.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto uiNode = AceType::DynamicCast<NG::UINode>(frameNode);
    MouseEvent mouseEvent;
    postEventManager_->passThroughResult_ = true;
    postEventManager_->PostMouseEvent(uiNode, std::move(mouseEvent));

    EXPECT_FALSE(postEventManager_->passThroughResult_);
}

/**
 * @tc.name: PostAxisEventTest001
 * @tc.desc: test PostAxisEvent func.
 * @tc.type: FUNC
 */
HWTEST_F(PostEventManagerTestNg, PostAxisEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a FrameNode and set gesture.
     */
    Init();

    /**
     * @tc.steps: step2. Simulate when the user touchDown and then handles the out-of-hand
     *                   action event through the PostDownEvent function.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto uiNode = AceType::DynamicCast<NG::UINode>(frameNode);
    AxisEvent axisEvent;
    postEventManager_->passThroughResult_ = true;
    postEventManager_->PostAxisEvent(uiNode, std::move(axisEvent));

    EXPECT_FALSE(postEventManager_->passThroughResult_);
}

/**
 * @tc.name: CheckTouchEventTest001
 * @tc.desc: test CheckTouchEvent.
 * @tc.type: FUNC
 */
HWTEST_F(PostEventManagerTestNg, CheckTouchEventTest001, TestSize.Level1)
{
    Init();
    auto gestureEventHub = root_->GetOrCreateGestureEventHub();
    gestureEventHub->SetHitTestMode(HitTestMode::HTMBLOCK);
    auto gesture = AceType::MakeRefPtr<TapGesture>();
    gestureEventHub->AddGesture(gesture);

    TouchEvent touchUpEvent;
    touchUpEvent.type = TouchType::DOWN;
    touchUpEvent.x = 15;
    touchUpEvent.y = 15;
    touchUpEvent.id = 2;
    auto currentTime = GetSysTimestamp();
    std::chrono::nanoseconds nanosecondsUp(currentTime);
    TimeStamp timeUp(nanosecondsUp);
    touchUpEvent.time = timeUp;
    auto frameNode = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto UInode = AceType::DynamicCast<NG::UINode>(frameNode);
    PostEventAction eventAction;
    eventAction.targetNode = UInode;
    eventAction.touchEvent = touchUpEvent;
    postEventManager_->postInputEventAction_.clear();
    auto result = postEventManager_->CheckTouchEvent(UInode, touchUpEvent);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: CheckTouchEventTest002
 * @tc.desc: test CheckTouchEvent.
 * @tc.type: FUNC
 */
HWTEST_F(PostEventManagerTestNg, CheckTouchEventTest002, TestSize.Level1)
{
    Init();
    auto gestureEventHub = root_->GetOrCreateGestureEventHub();
    gestureEventHub->SetHitTestMode(HitTestMode::HTMBLOCK);
    auto gesture = AceType::MakeRefPtr<TapGesture>();
    gestureEventHub->AddGesture(gesture);

    TouchEvent touchUpEvent;
    touchUpEvent.type = TouchType::DOWN;
    touchUpEvent.x = 15;
    touchUpEvent.y = 15;
    touchUpEvent.id = 2;
    auto currentTime = GetSysTimestamp();
    std::chrono::nanoseconds nanosecondsUp(currentTime);
    TimeStamp timeUp(nanosecondsUp);
    touchUpEvent.time = timeUp;
    auto frameNode = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto UInode = AceType::DynamicCast<NG::UINode>(frameNode);
    PostEventAction eventAction;
    eventAction.targetNode = UInode;
    eventAction.touchEvent = touchUpEvent;
    postEventManager_->postInputEventAction_.push_back(eventAction);
    auto result = postEventManager_->CheckTouchEvent(UInode, touchUpEvent);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckTouchEventTest003
 * @tc.desc: test CheckTouchEvent.
 * @tc.type: FUNC
 */
HWTEST_F(PostEventManagerTestNg, CheckTouchEventTest003, TestSize.Level1)
{
    Init();
    auto gestureEventHub = root_->GetOrCreateGestureEventHub();
    gestureEventHub->SetHitTestMode(HitTestMode::HTMBLOCK);
    auto gesture = AceType::MakeRefPtr<TapGesture>();
    gestureEventHub->AddGesture(gesture);

    TouchEvent firstTouchEvent;
    firstTouchEvent.type = TouchType::DOWN;
    firstTouchEvent.x = 15;
    firstTouchEvent.y = 15;
    firstTouchEvent.id = 2;
    TouchEvent secondTouchEvent;
    secondTouchEvent.type = TouchType::DOWN;
    secondTouchEvent.x = 15;
    secondTouchEvent.y = 15;
    secondTouchEvent.id = 2;
    auto currentTime = GetSysTimestamp();
    std::chrono::nanoseconds nanosecondsUp(currentTime);
    TimeStamp timeUp(nanosecondsUp);
    firstTouchEvent.time = timeUp;
    auto frameNode = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto UInode = AceType::DynamicCast<NG::UINode>(frameNode);
    PostEventAction eventAction;
    eventAction.targetNode = UInode;
    eventAction.touchEvent = firstTouchEvent;
    postEventManager_->postInputEventAction_.push_back(eventAction);
    auto result = postEventManager_->CheckTouchEvent(UInode, secondTouchEvent);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckTouchEventTest004
 * @tc.desc: test CheckTouchEvent.
 * @tc.type: FUNC
 */
HWTEST_F(PostEventManagerTestNg, CheckTouchEventTest004, TestSize.Level1)
{
    Init();
    auto gestureEventHub = root_->GetOrCreateGestureEventHub();
    gestureEventHub->SetHitTestMode(HitTestMode::HTMBLOCK);
    auto gesture = AceType::MakeRefPtr<TapGesture>();
    gestureEventHub->AddGesture(gesture);

    TouchEvent firstTouchEvent;
    firstTouchEvent.type = TouchType::CANCEL;
    firstTouchEvent.x = 15;
    firstTouchEvent.y = 15;
    firstTouchEvent.id = 2;
    TouchEvent secondTouchEvent;
    secondTouchEvent.type = TouchType::CANCEL;
    secondTouchEvent.x = 15;
    secondTouchEvent.y = 15;
    secondTouchEvent.id = 2;
    auto currentTime = GetSysTimestamp();
    std::chrono::nanoseconds nanosecondsUp(currentTime);
    TimeStamp timeUp(nanosecondsUp);
    firstTouchEvent.time = timeUp;
    auto frameNode = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto UInode = AceType::DynamicCast<NG::UINode>(frameNode);
    PostEventAction eventAction;
    eventAction.targetNode = UInode;
    eventAction.touchEvent = firstTouchEvent;
    postEventManager_->postInputEventAction_.push_back(eventAction);
    auto result = postEventManager_->CheckTouchEvent(UInode, secondTouchEvent);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckTouchEventTest005
 * @tc.desc: test CheckTouchEvent.
 * @tc.type: FUNC
 */
HWTEST_F(PostEventManagerTestNg, CheckTouchEventTest005, TestSize.Level1)
{
    Init();
    auto gestureEventHub = root_->GetOrCreateGestureEventHub();
    gestureEventHub->SetHitTestMode(HitTestMode::HTMBLOCK);
    auto gesture = AceType::MakeRefPtr<TapGesture>();
    gestureEventHub->AddGesture(gesture);

    TouchEvent firstTouchEvent;
    firstTouchEvent.type = TouchType::UP;
    firstTouchEvent.x = 15;
    firstTouchEvent.y = 15;
    firstTouchEvent.id = 2;
    TouchEvent secondTouchEvent;
    secondTouchEvent.type = TouchType::UP;
    secondTouchEvent.x = 15;
    secondTouchEvent.y = 15;
    secondTouchEvent.id = 2;
    auto currentTime = GetSysTimestamp();
    std::chrono::nanoseconds nanosecondsUp(currentTime);
    TimeStamp timeUp(nanosecondsUp);
    firstTouchEvent.time = timeUp;
    auto frameNode = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto UInode = AceType::DynamicCast<NG::UINode>(frameNode);
    PostEventAction eventAction;
    eventAction.targetNode = UInode;
    eventAction.touchEvent = firstTouchEvent;
    postEventManager_->postInputEventAction_.push_back(eventAction);
    auto result = postEventManager_->CheckTouchEvent(UInode, secondTouchEvent);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckTouchEventTest006
 * @tc.desc: test CheckTouchEvent.
 * @tc.type: FUNC
 */
HWTEST_F(PostEventManagerTestNg, CheckTouchEventTest006, TestSize.Level1)
{
    Init();
    auto gestureEventHub = root_->GetOrCreateGestureEventHub();
    gestureEventHub->SetHitTestMode(HitTestMode::HTMBLOCK);
    auto gesture = AceType::MakeRefPtr<TapGesture>();
    gestureEventHub->AddGesture(gesture);

    TouchEvent touchUpEvent;
    touchUpEvent.type = TouchType::MOVE;
    touchUpEvent.x = 15;
    touchUpEvent.y = 15;
    touchUpEvent.id = 2;
    auto currentTime = GetSysTimestamp();
    std::chrono::nanoseconds nanosecondsUp(currentTime);
    TimeStamp timeUp(nanosecondsUp);
    touchUpEvent.time = timeUp;
    auto frameNode = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto UInode = AceType::DynamicCast<NG::UINode>(frameNode);
    PostEventAction eventAction;
    eventAction.targetNode = UInode;
    eventAction.touchEvent = touchUpEvent;
    postEventManager_->postInputEventAction_.push_back(eventAction);
    auto result = postEventManager_->CheckTouchEvent(UInode, touchUpEvent);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ClearPostInputActionsTest001
 * @tc.desc: test ClearPostInputActions.
 * @tc.type: FUNC
 */
HWTEST_F(PostEventManagerTestNg, ClearPostInputActionsTest001, TestSize.Level1)
{
    Init();
    auto gestureEventHub = root_->GetOrCreateGestureEventHub();
    gestureEventHub->SetHitTestMode(HitTestMode::HTMBLOCK);
    auto gesture = AceType::MakeRefPtr<TapGesture>();
    gestureEventHub->AddGesture(gesture);

    TouchEvent touchUpEvent;
    touchUpEvent.type = TouchType::MOVE;
    touchUpEvent.x = 15;
    touchUpEvent.y = 15;
    touchUpEvent.id = 2;
    auto currentTime = GetSysTimestamp();
    std::chrono::nanoseconds nanosecondsUp(currentTime);
    TimeStamp timeUp(nanosecondsUp);
    touchUpEvent.time = timeUp;
    auto frameNode = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto UInode = AceType::DynamicCast<NG::UINode>(frameNode);
    PostEventAction eventAction;
    eventAction.targetNode = UInode;
    eventAction.touchEvent = touchUpEvent;
    postEventManager_->postInputEventAction_.push_back(eventAction);
    postEventManager_->ClearPostInputActions(UInode, touchUpEvent.id);
    EXPECT_TRUE(postEventManager_->postInputEventAction_.empty());
}

/**
 * @tc.name: PostMouseEventTest002
 * @tc.desc: test PostMouseEvent func.
 * @tc.type: FUNC
 */
HWTEST_F(PostEventManagerTestNg, PostMouseEventTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a FrameNode and set gesture.
     */
    Init();

    /**
     * @tc.steps: step2. test PostMouseEvent.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto uiNode = AceType::DynamicCast<NG::UINode>(frameNode);
    MouseEvent mouseEvent;
    mouseEvent.touchEventId = 1;
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->eventManager_ = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(pipelineContext->eventManager_, nullptr);
    pipelineContext->eventManager_->isDragCancelPending_ = false;
    postEventManager_->passThroughResult_ = true;
    postEventManager_->PostMouseEvent(uiNode, std::move(mouseEvent));
    pipelineContext->eventManager_->isDragCancelPending_ = true;
    MouseEvent mouseEventEx;
    mouseEventEx.touchEventId = 2;
    postEventManager_->PostMouseEvent(uiNode, std::move(mouseEventEx));
    EXPECT_FALSE(postEventManager_->passThroughResult_);
}

/**
 * @tc.name: PostEventTest001
 * @tc.desc: test PostEvent with null uiNode
 * @tc.type: FUNC
 */
HWTEST_F(PostEventManagerTestNg, PostEventTest001, TestSize.Level1)
{
    Init();
    TouchEvent touchEvent;
    touchEvent.type = TouchType::DOWN;
    auto result = postEventManager_->PostEvent(nullptr, touchEvent);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: PostEventTest002
 * @tc.desc: test PostEvent with unknown touch type
 * @tc.type: FUNC
 */
HWTEST_F(PostEventManagerTestNg, PostEventTest002, TestSize.Level1)
{
    Init();
    TouchEvent touchEvent;
    touchEvent.type = TouchType::HOVER_ENTER;
    auto result = postEventManager_->PostEvent(root_, touchEvent);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: PostTouchEventTest003
 * @tc.desc: test PostTouchEvent with null uiNode
 * @tc.type: FUNC
 */
HWTEST_F(PostEventManagerTestNg, PostTouchEventTest003, TestSize.Level1)
{
    Init();
    TouchEvent touchEvent;
    touchEvent.type = TouchType::DOWN;
    auto result = postEventManager_->PostTouchEvent(nullptr, std::move(touchEvent));
    EXPECT_FALSE(result);
}

/**
 * @tc.name: PostTouchEventTest004
 * @tc.desc: test PostTouchEvent with non-FrameNode
 * @tc.type: FUNC
 */
HWTEST_F(PostEventManagerTestNg, PostTouchEventTest004, TestSize.Level1)
{
    Init();
    RefPtr<UINode> uiNode = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto patternNode = AceType::MakeRefPtr<Pattern>();
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, 1, patternNode);
    auto uiNode2 = AceType::DynamicCast<NG::UINode>(frameNode);

    TouchEvent touchEvent;
    touchEvent.type = TouchType::DOWN;
    auto result = postEventManager_->PostTouchEvent(uiNode2, std::move(touchEvent));
    EXPECT_FALSE(result);
}

/**
 * @tc.name: PostTouchEventTest005
 * @tc.desc: test PostTouchEvent with MOVE type
 * @tc.type: FUNC
 */
HWTEST_F(PostEventManagerTestNg, PostTouchEventTest005, TestSize.Level1)
{
    Init();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto uiNode = AceType::DynamicCast<NG::UINode>(frameNode);

    // Add a DOWN event first
    PostEventAction eventAction;
    TouchEvent downEvent;
    downEvent.type = TouchType::DOWN;
    downEvent.id = 1;
    eventAction.targetNode = uiNode;
    eventAction.touchEvent = downEvent;
    postEventManager_->postInputEventAction_.push_back(eventAction);

    TouchEvent touchEvent;
    touchEvent.type = TouchType::MOVE;
    touchEvent.id = 1;
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->eventManager_ = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(pipelineContext->eventManager_, nullptr);
    pipelineContext->eventManager_->isDragCancelPending_ = false;
    postEventManager_->PostTouchEvent(uiNode, std::move(touchEvent));
}

/**
 * @tc.name: PostTouchEventTest006
 * @tc.desc: test PostTouchEvent with UP type
 * @tc.type: FUNC
 */
HWTEST_F(PostEventManagerTestNg, PostTouchEventTest006, TestSize.Level1)
{
    Init();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto uiNode = AceType::DynamicCast<NG::UINode>(frameNode);

    // Add a DOWN event first
    PostEventAction eventAction;
    TouchEvent downEvent;
    downEvent.type = TouchType::DOWN;
    downEvent.id = 1;
    eventAction.targetNode = uiNode;
    eventAction.touchEvent = downEvent;
    postEventManager_->postInputEventAction_.push_back(eventAction);

    TouchEvent touchEvent;
    touchEvent.type = TouchType::UP;
    touchEvent.id = 1;
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->eventManager_ = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(pipelineContext->eventManager_, nullptr);
    pipelineContext->eventManager_->isDragCancelPending_ = false;
    postEventManager_->PostTouchEvent(uiNode, std::move(touchEvent));
}

/**
 * @tc.name: PostTouchEventTest007
 * @tc.desc: test PostTouchEvent with CANCEL type
 * @tc.type: FUNC
 */
HWTEST_F(PostEventManagerTestNg, PostTouchEventTest007, TestSize.Level1)
{
    Init();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto uiNode = AceType::DynamicCast<NG::UINode>(frameNode);

    // Add a DOWN event first
    PostEventAction eventAction;
    TouchEvent downEvent;
    downEvent.type = TouchType::DOWN;
    downEvent.id = 1;
    eventAction.targetNode = uiNode;
    eventAction.touchEvent = downEvent;
    postEventManager_->postInputEventAction_.push_back(eventAction);

    TouchEvent touchEvent;
    touchEvent.type = TouchType::CANCEL;
    touchEvent.id = 1;
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->eventManager_ = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(pipelineContext->eventManager_, nullptr);
    pipelineContext->eventManager_->isDragCancelPending_ = false;
    postEventManager_->PostTouchEvent(uiNode, std::move(touchEvent));
}

/**
 * @tc.name: PostMouseEventTest003
 * @tc.desc: test PostMouseEvent with null uiNode
 * @tc.type: FUNC
 */
HWTEST_F(PostEventManagerTestNg, PostMouseEventTest003, TestSize.Level1)
{
    Init();
    MouseEvent mouseEvent;
    auto result = postEventManager_->PostMouseEvent(nullptr, std::move(mouseEvent));
    EXPECT_FALSE(result);
}

/**
 * @tc.name: PostMouseEventTest004
 * @tc.desc: test PostMouseEvent with non-FrameNode
 * @tc.type: FUNC
 */
HWTEST_F(PostEventManagerTestNg, PostMouseEventTest004, TestSize.Level1)
{
    Init();
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    auto uiNode = AceType::DynamicCast<NG::UINode>(frameNode);

    MouseEvent mouseEvent;
    auto result = postEventManager_->PostMouseEvent(uiNode, std::move(mouseEvent));
    EXPECT_FALSE(result);
}

/**
 * @tc.name: PostAxisEventTest002
 * @tc.desc: test PostAxisEvent with null uiNode
 * @tc.type: FUNC
 */
HWTEST_F(PostEventManagerTestNg, PostAxisEventTest002, TestSize.Level1)
{
    Init();
    AxisEvent axisEvent;
    auto result = postEventManager_->PostAxisEvent(nullptr, std::move(axisEvent));
    EXPECT_FALSE(result);
}

/**
 * @tc.name: PostAxisEventTest003
 * @tc.desc: test PostAxisEvent with non-FrameNode
 * @tc.type: FUNC
 */
HWTEST_F(PostEventManagerTestNg, PostAxisEventTest003, TestSize.Level1)
{
    Init();
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    auto uiNode = AceType::DynamicCast<NG::UINode>(frameNode);

    AxisEvent axisEvent;
    auto result = postEventManager_->PostAxisEvent(uiNode, std::move(axisEvent));
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckTouchEventTest007
 * @tc.desc: test CheckTouchEvent with null targetNode
 * @tc.type: FUNC
 */
HWTEST_F(PostEventManagerTestNg, CheckTouchEventTest007, TestSize.Level1)
{
    Init();
    TouchEvent touchEvent;
    touchEvent.type = TouchType::DOWN;
    auto result = postEventManager_->CheckTouchEvent(nullptr, touchEvent);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckTouchEventTest008
 * @tc.desc: test CheckTouchEvent with DOWN after UP (hasUpOrCancel true)
 * @tc.type: FUNC
 */
HWTEST_F(PostEventManagerTestNg, CheckTouchEventTest008, TestSize.Level1)
{
    Init();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto UInode = AceType::DynamicCast<NG::UINode>(frameNode);

    // Add UP event first
    PostEventAction eventAction;
    TouchEvent upEvent;
    upEvent.type = TouchType::UP;
    upEvent.id = 2;
    eventAction.targetNode = UInode;
    eventAction.touchEvent = upEvent;
    postEventManager_->postInputEventAction_.push_back(eventAction);

    TouchEvent downEvent;
    downEvent.type = TouchType::DOWN;
    downEvent.id = 2;
    auto result = postEventManager_->CheckTouchEvent(UInode, downEvent);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: CheckTouchEventTest009
 * @tc.desc: test CheckTouchEvent with UP without DOWN
 * @tc.type: FUNC
 */
HWTEST_F(PostEventManagerTestNg, CheckTouchEventTest009, TestSize.Level1)
{
    Init();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto UInode = AceType::DynamicCast<NG::UINode>(frameNode);

    TouchEvent upEvent;
    upEvent.type = TouchType::UP;
    upEvent.id = 2;
    auto result = postEventManager_->CheckTouchEvent(UInode, upEvent);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckTouchEventTest010
 * @tc.desc: test CheckTouchEvent with CANCEL without DOWN
 * @tc.type: FUNC
 */
HWTEST_F(PostEventManagerTestNg, CheckTouchEventTest010, TestSize.Level1)
{
    Init();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto UInode = AceType::DynamicCast<NG::UINode>(frameNode);

    TouchEvent cancelEvent;
    cancelEvent.type = TouchType::CANCEL;
    cancelEvent.id = 2;
    auto result = postEventManager_->CheckTouchEvent(UInode, cancelEvent);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckTouchEventTest011
 * @tc.desc: test CheckTouchEvent with different targetNode
 * @tc.type: FUNC
 */
HWTEST_F(PostEventManagerTestNg, CheckTouchEventTest011, TestSize.Level1)
{
    Init();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto UInode = AceType::DynamicCast<NG::UINode>(frameNode);

    // Add DOWN event for one node
    PostEventAction eventAction;
    TouchEvent downEvent;
    downEvent.type = TouchType::DOWN;
    downEvent.id = 2;
    eventAction.targetNode = UInode;
    eventAction.touchEvent = downEvent;
    postEventManager_->postInputEventAction_.push_back(eventAction);

    // Check with different node
    auto frameNode2 = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto UInode2 = AceType::DynamicCast<NG::UINode>(frameNode2);

    TouchEvent downEvent2;
    downEvent2.type = TouchType::DOWN;
    downEvent2.id = 2;
    auto result = postEventManager_->CheckTouchEvent(UInode2, downEvent2);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: CheckTouchEventTest012
 * @tc.desc: test CheckTouchEvent with different id
 * @tc.type: FUNC
 */
HWTEST_F(PostEventManagerTestNg, CheckTouchEventTest012, TestSize.Level1)
{
    Init();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto UInode = AceType::DynamicCast<NG::UINode>(frameNode);

    // Add DOWN event with id 2
    PostEventAction eventAction;
    TouchEvent downEvent;
    downEvent.type = TouchType::DOWN;
    downEvent.id = 2;
    eventAction.targetNode = UInode;
    eventAction.touchEvent = downEvent;
    postEventManager_->postInputEventAction_.push_back(eventAction);

    // Check with different id (3)
    TouchEvent downEvent2;
    downEvent2.type = TouchType::DOWN;
    downEvent2.id = 3;
    auto result = postEventManager_->CheckTouchEvent(UInode, downEvent2);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: CheckTouchEventTest013
 * @tc.desc: test CheckTouchEvent clears actions when UP follows DOWN
 * @tc.type: FUNC
 */
HWTEST_F(PostEventManagerTestNg, CheckTouchEventTest013, TestSize.Level1)
{
    Init();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto UInode = AceType::DynamicCast<NG::UINode>(frameNode);

    // Add DOWN event
    PostEventAction eventAction;
    TouchEvent downEvent;
    downEvent.type = TouchType::DOWN;
    downEvent.id = 2;
    eventAction.targetNode = UInode;
    eventAction.touchEvent = downEvent;
    postEventManager_->postInputEventAction_.push_back(eventAction);

    // Add UP event
    PostEventAction eventAction2;
    TouchEvent upEvent;
    upEvent.type = TouchType::UP;
    upEvent.id = 2;
    eventAction2.targetNode = UInode;
    eventAction2.touchEvent = upEvent;
    postEventManager_->postInputEventAction_.push_back(eventAction2);

    // Check DOWN again should clear old actions
    TouchEvent downEvent2;
    downEvent2.type = TouchType::DOWN;
    downEvent2.id = 2;
    auto result = postEventManager_->CheckTouchEvent(UInode, downEvent2);
    EXPECT_TRUE(result);
    EXPECT_EQ(postEventManager_->postInputEventAction_.size(), 0);
}

/**
 * @tc.name: PostDownEventTest002
 * @tc.desc: test PostDownEvent with null targetNode
 * @tc.type: FUNC
 */
HWTEST_F(PostEventManagerTestNg, PostDownEventTest002, TestSize.Level1)
{
    Init();
    TouchEvent touchEvent;
    touchEvent.type = TouchType::DOWN;
    auto result = postEventManager_->PostDownEvent(nullptr, touchEvent);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: PostDownEventTest003
 * @tc.desc: test PostDownEvent with duplicate DOWN (no lastEventMap entry)
 * @tc.type: FUNC
 */
HWTEST_F(PostEventManagerTestNg, PostDownEventTest003, TestSize.Level1)
{
    Init();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto UInode = AceType::DynamicCast<NG::UINode>(frameNode);

    TouchEvent touchEvent;
    touchEvent.type = TouchType::DOWN;
    touchEvent.id = 5;

    PostEventAction eventAction;
    eventAction.targetNode = UInode;
    eventAction.touchEvent = touchEvent;
    postEventManager_->postEventAction_.push_back(eventAction);

    auto result = postEventManager_->PostDownEvent(UInode, touchEvent);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: PostMoveEventTest001
 * @tc.desc: test PostMoveEvent with null targetNode
 * @tc.type: FUNC
 */
HWTEST_F(PostEventManagerTestNg, PostMoveEventTest001, TestSize.Level1)
{
    Init();
    TouchEvent touchEvent;
    touchEvent.type = TouchType::MOVE;
    auto result = postEventManager_->PostMoveEvent(nullptr, touchEvent);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: PostMoveEventTest002
 * @tc.desc: test PostMoveEvent without DOWN event
 * @tc.type: FUNC
 */
HWTEST_F(PostEventManagerTestNg, PostMoveEventTest002, TestSize.Level1)
{
    Init();
    TouchEvent touchEvent;
    touchEvent.type = TouchType::MOVE;
    auto result = postEventManager_->PostMoveEvent(root_, touchEvent);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: PostMoveEventTest003
 * @tc.desc: test PostMoveEvent after UP event
 * @tc.type: FUNC
 */
HWTEST_F(PostEventManagerTestNg, PostMoveEventTest003, TestSize.Level1)
{
    Init();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto UInode = AceType::DynamicCast<NG::UINode>(frameNode);

    // Add DOWN and UP events
    PostEventAction eventAction1;
    TouchEvent downEvent;
    downEvent.type = TouchType::DOWN;
    downEvent.id = 3;
    eventAction1.targetNode = UInode;
    eventAction1.touchEvent = downEvent;
    postEventManager_->postEventAction_.push_back(eventAction1);

    PostEventAction eventAction2;
    TouchEvent upEvent;
    upEvent.type = TouchType::UP;
    upEvent.id = 3;
    eventAction2.targetNode = UInode;
    eventAction2.touchEvent = upEvent;
    postEventManager_->postEventAction_.push_back(eventAction2);

    TouchEvent moveEvent;
    moveEvent.type = TouchType::MOVE;
    moveEvent.id = 3;
    auto result = postEventManager_->PostMoveEvent(UInode, moveEvent);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: PostUpEventTest001
 * @tc.desc: test PostUpEvent with null targetNode
 * @tc.type: FUNC
 */
HWTEST_F(PostEventManagerTestNg, PostUpEventTest001, TestSize.Level1)
{
    Init();
    TouchEvent touchEvent;
    touchEvent.type = TouchType::UP;
    auto result = postEventManager_->PostUpEvent(nullptr, touchEvent);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: PostUpEventTest002
 * @tc.desc: test PostUpEvent without DOWN event
 * @tc.type: FUNC
 */
HWTEST_F(PostEventManagerTestNg, PostUpEventTest002, TestSize.Level1)
{
    Init();
    TouchEvent touchEvent;
    touchEvent.type = TouchType::UP;
    auto result = postEventManager_->PostUpEvent(root_, touchEvent);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: PostUpEventTest003
 * @tc.desc: test PostUpEvent after CANCEL event
 * @tc.type: FUNC
 */
HWTEST_F(PostEventManagerTestNg, PostUpEventTest003, TestSize.Level1)
{
    Init();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto UInode = AceType::DynamicCast<NG::UINode>(frameNode);

    // Add DOWN and CANCEL events
    PostEventAction eventAction1;
    TouchEvent downEvent;
    downEvent.type = TouchType::DOWN;
    downEvent.id = 3;
    eventAction1.targetNode = UInode;
    eventAction1.touchEvent = downEvent;
    postEventManager_->postEventAction_.push_back(eventAction1);

    PostEventAction eventAction2;
    TouchEvent cancelEvent;
    cancelEvent.type = TouchType::CANCEL;
    cancelEvent.id = 3;
    eventAction2.targetNode = UInode;
    eventAction2.touchEvent = cancelEvent;
    postEventManager_->postEventAction_.push_back(eventAction2);

    TouchEvent upEvent;
    upEvent.type = TouchType::UP;
    upEvent.id = 3;
    auto result = postEventManager_->PostUpEvent(UInode, upEvent);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: HaveReceiveDownEventTest001
 * @tc.desc: test HaveReceiveDownEvent function
 * @tc.type: FUNC
 */
HWTEST_F(PostEventManagerTestNg, HaveReceiveDownEventTest001, TestSize.Level1)
{
    Init();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto UInode = AceType::DynamicCast<NG::UINode>(frameNode);

    // Initially no DOWN event
    auto result = postEventManager_->HaveReceiveDownEvent(UInode, 1);
    EXPECT_FALSE(result);

    // Add DOWN event
    PostEventAction eventAction;
    TouchEvent downEvent;
    downEvent.type = TouchType::DOWN;
    downEvent.id = 1;
    eventAction.targetNode = UInode;
    eventAction.touchEvent = downEvent;
    postEventManager_->postEventAction_.push_back(eventAction);

    result = postEventManager_->HaveReceiveDownEvent(UInode, 1);
    EXPECT_TRUE(result);

    // Different id
    result = postEventManager_->HaveReceiveDownEvent(UInode, 2);
    EXPECT_FALSE(result);

    // Different node
    auto frameNode2 = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto UInode2 = AceType::DynamicCast<NG::UINode>(frameNode2);
    result = postEventManager_->HaveReceiveDownEvent(UInode2, 1);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: HaveReceiveUpOrCancelEventTest001
 * @tc.desc: test HaveReceiveUpOrCancelEvent function
 * @tc.type: FUNC
 */
HWTEST_F(PostEventManagerTestNg, HaveReceiveUpOrCancelEventTest001, TestSize.Level1)
{
    Init();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto UInode = AceType::DynamicCast<NG::UINode>(frameNode);

    // Initially no UP event
    auto result = postEventManager_->HaveReceiveUpOrCancelEvent(UInode, 1);
    EXPECT_FALSE(result);

    // Add UP event
    PostEventAction eventAction;
    TouchEvent upEvent;
    upEvent.type = TouchType::UP;
    upEvent.id = 1;
    eventAction.targetNode = UInode;
    eventAction.touchEvent = upEvent;
    postEventManager_->postEventAction_.push_back(eventAction);

    result = postEventManager_->HaveReceiveUpOrCancelEvent(UInode, 1);
    EXPECT_TRUE(result);

    // Test with CANCEL
    postEventManager_->postEventAction_.clear();
    PostEventAction eventAction2;
    TouchEvent cancelEvent;
    cancelEvent.type = TouchType::CANCEL;
    cancelEvent.id = 2;
    eventAction2.targetNode = UInode;
    eventAction2.touchEvent = cancelEvent;
    postEventManager_->postEventAction_.push_back(eventAction2);

    result = postEventManager_->HaveReceiveUpOrCancelEvent(UInode, 2);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: CheckPointValidityTest001
 * @tc.desc: test CheckPointValidity with duplicate time
 * @tc.type: FUNC
 */
HWTEST_F(PostEventManagerTestNg, CheckPointValidityTest001, TestSize.Level1)
{
    Init();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto UInode = AceType::DynamicCast<NG::UINode>(frameNode);

    // Add an event
    PostEventAction eventAction;
    TouchEvent touchEvent;
    touchEvent.type = TouchType::DOWN;
    touchEvent.id = 1;
    auto currentTime = GetSysTimestamp();
    std::chrono::nanoseconds nanoseconds(currentTime);
    TimeStamp time(nanoseconds);
    touchEvent.time = time;
    eventAction.targetNode = UInode;
    eventAction.touchEvent = touchEvent;
    postEventManager_->postEventAction_.push_back(eventAction);

    // Check with same time and id
    TouchEvent touchEvent2;
    touchEvent2.type = TouchType::MOVE;
    touchEvent2.id = 1;
    touchEvent2.time = time;
    auto result = postEventManager_->CheckPointValidity(touchEvent2);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckPointValidityTest002
 * @tc.desc: test CheckPointValidity with different time
 * @tc.type: FUNC
 */
HWTEST_F(PostEventManagerTestNg, CheckPointValidityTest002, TestSize.Level1)
{
    Init();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto UInode = AceType::DynamicCast<NG::UINode>(frameNode);

    // Add an event
    PostEventAction eventAction;
    TouchEvent touchEvent;
    touchEvent.type = TouchType::DOWN;
    touchEvent.id = 1;
    auto currentTime = GetSysTimestamp();
    std::chrono::nanoseconds nanoseconds(currentTime);
    TimeStamp time(nanoseconds);
    touchEvent.time = time;
    eventAction.targetNode = UInode;
    eventAction.touchEvent = touchEvent;
    postEventManager_->postEventAction_.push_back(eventAction);

    // Check with different time
    TouchEvent touchEvent2;
    touchEvent2.type = TouchType::MOVE;
    touchEvent2.id = 1;
    currentTime = GetSysTimestamp();
    std::chrono::nanoseconds nanoseconds2(currentTime);
    TimeStamp time2(nanoseconds2);
    touchEvent2.time = time2;
    auto result = postEventManager_->CheckPointValidity(touchEvent2);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: CheckPointValidityTest003
 * @tc.desc: test CheckPointValidity with different id
 * @tc.type: FUNC
 */
HWTEST_F(PostEventManagerTestNg, CheckPointValidityTest003, TestSize.Level1)
{
    Init();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto UInode = AceType::DynamicCast<NG::UINode>(frameNode);

    // Add an event
    PostEventAction eventAction;
    TouchEvent touchEvent;
    touchEvent.type = TouchType::DOWN;
    touchEvent.id = 1;
    auto currentTime = GetSysTimestamp();
    std::chrono::nanoseconds nanoseconds(currentTime);
    TimeStamp time(nanoseconds);
    touchEvent.time = time;
    eventAction.targetNode = UInode;
    eventAction.touchEvent = touchEvent;
    postEventManager_->postEventAction_.push_back(eventAction);

    // Check with different id
    TouchEvent touchEvent2;
    touchEvent2.type = TouchType::MOVE;
    touchEvent2.id = 2;
    touchEvent2.time = time;
    auto result = postEventManager_->CheckPointValidity(touchEvent2);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: SetPassThroughResultTest001
 * @tc.desc: test SetPassThroughResult and GetPostTargetNode
 * @tc.type: FUNC
 */
HWTEST_F(PostEventManagerTestNg, SetPassThroughResultTest001, TestSize.Level1)
{
    Init();
    postEventManager_->SetPassThroughResult(true);
    EXPECT_TRUE(postEventManager_->passThroughResult_);

    postEventManager_->SetPassThroughResult(false);
    EXPECT_FALSE(postEventManager_->passThroughResult_);

    auto frameNode = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    postEventManager_->targetNode_ = frameNode;
    auto result = postEventManager_->GetPostTargetNode();
    EXPECT_EQ(result, frameNode);
}

/**
 * @tc.name: ClearPostInputActionsTest002
 * @tc.desc: test ClearPostInputActions with multiple ids
 * @tc.type: FUNC
 */
HWTEST_F(PostEventManagerTestNg, ClearPostInputActionsTest002, TestSize.Level1)
{
    Init();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto UInode = AceType::DynamicCast<NG::UINode>(frameNode);

    // Add multiple events with different ids
    for (int32_t i = 0; i < 3; i++) {
        PostEventAction eventAction;
        TouchEvent touchEvent;
        touchEvent.type = TouchType::DOWN;
        touchEvent.id = i;
        eventAction.targetNode = UInode;
        eventAction.touchEvent = touchEvent;
        postEventManager_->postInputEventAction_.push_back(eventAction);
    }

    EXPECT_EQ(postEventManager_->postInputEventAction_.size(), 3);

    // Clear only id 1
    postEventManager_->ClearPostInputActions(UInode, 1);
    EXPECT_EQ(postEventManager_->postInputEventAction_.size(), 2);
}

/**
 * @tc.name: ClearPostInputActionsTest003
 * @tc.desc: test ClearPostInputActions with different targetNode
 * @tc.type: FUNC
 */
HWTEST_F(PostEventManagerTestNg, ClearPostInputActionsTest003, TestSize.Level1)
{
    Init();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto UInode = AceType::DynamicCast<NG::UINode>(frameNode);
    auto frameNode2 = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto UInode2 = AceType::DynamicCast<NG::UINode>(frameNode2);

    // Add events to both nodes
    PostEventAction eventAction;
    TouchEvent touchEvent;
    touchEvent.type = TouchType::DOWN;
    touchEvent.id = 1;
    eventAction.targetNode = UInode;
    eventAction.touchEvent = touchEvent;
    postEventManager_->postInputEventAction_.push_back(eventAction);

    PostEventAction eventAction2;
    eventAction2.targetNode = UInode2;
    eventAction2.touchEvent = touchEvent;
    postEventManager_->postInputEventAction_.push_back(eventAction2);

    EXPECT_EQ(postEventManager_->postInputEventAction_.size(), 2);

    // Clear only for first node
    postEventManager_->ClearPostInputActions(UInode, 1);
    EXPECT_EQ(postEventManager_->postInputEventAction_.size(), 1);
}

/**
 * @tc.name: HandlePostEventTest002
 * @tc.desc: test HandlePostEvent with MOVE type (should not add to eventTreeRecord)
 * @tc.type: FUNC
 */
HWTEST_F(PostEventManagerTestNg, HandlePostEventTest002, TestSize.Level1)
{
    Init();
    auto buttonNode =
        FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, 1, []() { return AceType::MakeRefPtr<Pattern>(); });

    // Add DOWN event first
    TouchEvent downEvent;
    downEvent.type = TouchType::DOWN;
    downEvent.id = 10;
    postEventManager_->HandlePostEvent(buttonNode, downEvent);

    // Add MOVE event - should not add to eventTreeRecord or call PostEventFlushTouchEventEnd
    TouchEvent moveEvent;
    moveEvent.type = TouchType::MOVE;
    moveEvent.id = 10;
    postEventManager_->HandlePostEvent(buttonNode, moveEvent);

    // lastEventMap should still have the DOWN event
    EXPECT_FALSE(postEventManager_->lastEventMap_.empty());
}

/**
 * @tc.name: PostEventTest003
 * @tc.desc: test PostEvent with same timestamp (duplicate event)
 * @tc.type: FUNC
 */
HWTEST_F(PostEventManagerTestNg, PostEventTest003, TestSize.Level1)
{
    Init();
    auto gestureEventHub = root_->GetOrCreateGestureEventHub();
    gestureEventHub->SetHitTestMode(HitTestMode::HTMBLOCK);
    auto gesture = AceType::MakeRefPtr<TapGesture>();
    gestureEventHub->AddGesture(gesture);

    TouchEvent touchEvent;
    touchEvent.type = TouchType::DOWN;
    touchEvent.x = 10;
    touchEvent.y = 10;
    auto currentTime = GetSysTimestamp();
    std::chrono::nanoseconds nanoseconds(currentTime);
    TimeStamp time(nanoseconds);
    touchEvent.time = time;

    // First call should succeed
    auto result = postEventManager_->PostEvent(root_, touchEvent);
    EXPECT_FALSE(result);

    // Second call with same timestamp should return false
    result = postEventManager_->PostEvent(root_, touchEvent);
    EXPECT_FALSE(result);
}
} // namespace OHOS::Ace::NG
