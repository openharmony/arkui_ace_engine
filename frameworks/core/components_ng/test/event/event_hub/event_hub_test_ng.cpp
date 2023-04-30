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

#include "gtest/gtest.h"

#include "base/geometry/ng/offset_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace {
bool OHOS::Ace::SystemProperties::GetDebugEnabled()
{
    return false;
}
} // namespace OHOS::Ace
namespace OHOS::Ace::NG {
namespace {
constexpr bool EVENT_HUB_ENABLE = false;
const std::string DRAG_STARR_EVENT_TYPE = "drag start";
const std::string DRAG_ENTER_EVENT_TYPE = "drag enter";
const std::string DRAG_LEAVE_EVENT_TYPE = "drag leave";
const std::string DRAG_MOVE_EVENT_TYPE = "drag move";
const std::string DRAG_DROP_EVENT_TYPE = "drag drop";

const float OLD_X_VALUE = 10.9f;
const float OLD_Y_VALUE = 11.0f;
const float OLD_WIDTH = 400.0f;
const float OLD_HEIGHT = 400.0f;
const RectF OLD_RECT = RectF(OLD_X_VALUE, OLD_Y_VALUE, OLD_WIDTH, OLD_HEIGHT);
const OffsetF OLD_ORIGIN = OffsetF(OLD_WIDTH, OLD_HEIGHT);

const float NEW_X_VALUE = 15.9f;
const float NEW_Y_VALUE = 15.0f;
const float NEW_WIDTH = 500.0f;
const float NEW_HEIGHT = 500.0f;
const RectF NEW_RECT = RectF(NEW_X_VALUE, NEW_Y_VALUE, NEW_WIDTH, NEW_HEIGHT);
const OffsetF NEW_ORIGIN = OffsetF(NEW_WIDTH, NEW_HEIGHT);
} // namespace

class EventHubTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
};

void EventHubTestNg::SetUpTestSuite()
{
    GTEST_LOG_(INFO) << "EventHubTestNg SetUpTestCase";
}

void EventHubTestNg::TearDownTestSuite()
{
    GTEST_LOG_(INFO) << "EventHubTestNg TearDownTestCase";
}

void EventHubTestNg::SetUp()
{
    MockPipelineBase::SetUp();
}

void EventHubTestNg::TearDown()
{
    MockPipelineBase::TearDown();
}

/**
 * @tc.name: EventHubCreateTest001
 * @tc.desc: Create EventHub.
 * @tc.type: FUNC
 */
HWTEST_F(EventHubTestNg, EventHubCreateTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventHub.
     * @tc.expected: eventHub is not null.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->MarkModifyDone();
    EXPECT_NE(eventHub, nullptr);

    /**
     * @tc.steps: step2. Get EventHub's properties.
     * @tc.expected: These properties are null when GetOrCreateEventHub functions have not been invoked.
     */
    EXPECT_EQ(eventHub->GetGestureEventHub(), nullptr);
    EXPECT_EQ(eventHub->GetInputEventHub(), nullptr);
    EXPECT_EQ(eventHub->GetFocusHub(), nullptr);
    EXPECT_EQ(eventHub->GetFrameNode(), nullptr);
    EXPECT_EQ(eventHub->GetOnDragStart(), nullptr);

    /**
     * @tc.steps: step3. Test EventHub's default properties.
     */
    EXPECT_TRUE(!eventHub->HasOnAreaChanged());
    EXPECT_TRUE(!eventHub->HasOnDragStart());
    EXPECT_TRUE(!eventHub->HasOnDrop());
    EXPECT_TRUE(eventHub->IsEnabled());
}

/**
 * @tc.name: EventHubPropertyTest002
 * @tc.desc: Create EventHub and invoke GetOrCreateEventHub functions.
 * @tc.type: FUNC
 */
HWTEST_F(EventHubTestNg, EventHubPropertyTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventHub.
     * @tc.expected: eventHub is not null.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    EXPECT_NE(eventHub, nullptr);

    /**
     * @tc.steps: step2. Invoke GetOrCreateEventHub functions.
     * @tc.expected: These eventHub properties are not null.
     */
    eventHub->GetOrCreateGestureEventHub();
    eventHub->GetOrCreateInputEventHub();
    eventHub->GetOrCreateFocusHub();
    EXPECT_NE(eventHub->GetGestureEventHub(), nullptr);
    EXPECT_NE(eventHub->GetInputEventHub(), nullptr);
    EXPECT_NE(eventHub->GetFocusHub(), nullptr);

    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    EXPECT_TRUE(eventHub->GetFrameNode() != nullptr && eventHub->GetFrameNode()->GetTag() == V2::TEXT_ETS_TAG);
    eventHub->OnContextAttached();
    eventHub->SetEnabled(EVENT_HUB_ENABLE);
    EXPECT_TRUE(!eventHub->IsEnabled());
}

/**
 * @tc.name: EventHubPropertyTest003
 * @tc.desc: Create EventHub and set/fire onAreaChanged, onAppear and onDisappear function.
 * @tc.type: FUNC
 */
HWTEST_F(EventHubTestNg, EventHubPropertyTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventHub.
     * @tc.expected: eventHub is not null.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    EXPECT_NE(eventHub, nullptr);

    /**
     * @tc.steps: step2. Set EventHub OnAreaChanged function and fire it.
     * @tc.expected: onAreaChanged is invoked and the temp values are assigned with correct values.
     */
    RectF tempOldRect;
    OffsetF tempOldOrigin;
    RectF tempNewRect;
    OffsetF tempNewOrigin;
    auto onAreaChanged = [&tempOldRect, &tempOldOrigin, &tempNewRect, &tempNewOrigin](
                             const RectF& oldRect, const OffsetF& oldOrigin, const RectF& rect, const OffsetF& origin) {
        tempOldRect = oldRect;
        tempOldOrigin = oldOrigin;
        tempNewRect = rect;
        tempNewOrigin = origin;
    };

    eventHub->SetOnAreaChanged(onAreaChanged);
    eventHub->FireOnAreaChanged(OLD_RECT, OLD_ORIGIN, NEW_RECT, NEW_ORIGIN);
    EXPECT_TRUE(eventHub->HasOnAreaChanged());
    EXPECT_EQ(tempOldRect, OLD_RECT);
    EXPECT_EQ(tempOldOrigin, OLD_ORIGIN);
    EXPECT_EQ(tempNewRect, NEW_RECT);
    EXPECT_EQ(tempNewOrigin, NEW_ORIGIN);

    /**
     * @tc.steps: step3. Set/fire EventHub onAppear and onDisappear function.
     * @tc.expected: isAppear is assigned with correct value.
     */
    eventHub->SetOnAppear([]() {});
    eventHub->FireOnAppear();

    eventHub->SetOnDisappear([]() {});
    eventHub->FireOnDisappear();
}

/**
 * @tc.name: EventHubDragEventsTest004
 * @tc.desc: Create EventHub and set/fire drag related functions.
 * @tc.type: FUNC
 */
HWTEST_F(EventHubTestNg, EventHubDragEventsTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventHub.
     * @tc.expected: eventHub is not null.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    EXPECT_NE(eventHub, nullptr);

    /**
     * @tc.steps: step2. Set EventHub OnDragStart event and fire it.
     * @tc.expected: OnDragStart is invoked and the temp values are assigned with correct values.
     */
    auto dragEvent = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    std::string dragEventType;
    auto OnDragStartFunc = [&dragEventType](const RefPtr<OHOS::Ace::DragEvent>& /* dragEvent */,
                               const std::string& eventType) -> DragDropInfo {
        dragEventType = eventType;
        return {};
    };
    eventHub->SetOnDragStart(OnDragStartFunc);
    EXPECT_TRUE(eventHub->HasOnDragStart());
    EXPECT_NE(eventHub->GetOnDragStart(), nullptr);
    eventHub->GetOnDragStart()(dragEvent, DRAG_STARR_EVENT_TYPE);
    EXPECT_EQ(dragEventType, DRAG_STARR_EVENT_TYPE);

    /**
     * @tc.steps: step3. Set EventHub OnDragEnter event and fire it.
     * @tc.expected: OnDragEnter is invoked and the temp values are assigned with correct values.
     */
    auto OnDragFunc = [&dragEventType](const RefPtr<OHOS::Ace::DragEvent>& /* dragEvent */,
                          const std::string& eventType) { dragEventType = eventType; };
    auto onDragEnter = OnDragFunc;
    eventHub->SetOnDragEnter(onDragEnter);
    eventHub->FireOnDragEnter(dragEvent, DRAG_ENTER_EVENT_TYPE);
    EXPECT_EQ(dragEventType, DRAG_ENTER_EVENT_TYPE);

    /**
     * @tc.steps: step4. Set EventHub OnDragLeave event and fire it.
     * @tc.expected: OnDragLeave is invoked and the temp values are assigned with correct values.
     */
    auto onDragLeave = OnDragFunc;
    eventHub->SetOnDragLeave(onDragLeave);
    eventHub->FireOnDragLeave(dragEvent, DRAG_LEAVE_EVENT_TYPE);
    EXPECT_EQ(dragEventType, DRAG_LEAVE_EVENT_TYPE);

    /**
     * @tc.steps: step5. Set EventHub OnDragMove event and fire it.
     * @tc.expected: OnDragMove is invoked and the temp values are assigned with correct values.
     */
    auto onDragMove = OnDragFunc;
    eventHub->SetOnDragMove(onDragMove);
    eventHub->FireOnDragMove(dragEvent, DRAG_MOVE_EVENT_TYPE);
    EXPECT_EQ(dragEventType, DRAG_MOVE_EVENT_TYPE);

    /**
     * @tc.steps: step6. Set EventHub OnDrop event and fire it.
     * @tc.expected: OnDrop is invoked and the temp values are assigned with correct values.
     */
    auto onDragDrop = OnDragFunc;
    eventHub->SetOnDrop(onDragDrop);
    eventHub->FireOnDragMove(dragEvent, DRAG_DROP_EVENT_TYPE);
    EXPECT_TRUE(eventHub->HasOnDrop());
    EXPECT_EQ(dragEventType, DRAG_DROP_EVENT_TYPE);
}
} // namespace OHOS::Ace::NG
