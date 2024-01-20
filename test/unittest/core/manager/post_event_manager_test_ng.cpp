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
} // namespace OHOS::Ace::NG
