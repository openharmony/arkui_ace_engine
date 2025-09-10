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
    root_->GetResponseRegionList(paintRect, 1);
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
    root_->GetResponseRegionList(paintRect, 1);
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
    root_->GetResponseRegionList(paintRect, 1);
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
    root_->GetResponseRegionList(paintRect, 1);
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
} // namespace OHOS::Ace::NG
