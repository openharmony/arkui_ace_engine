/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "test/unittest/core/event/gesture_event_hub_test_ng.h"

#include <utility>

#include "frameworks/base/window/drag_window.h"
#include "core/components_ng/event/drag_drop_event.h"
#include "core/components_ng/manager/drag_drop/drag_drop_manager.h"
#include "core/components_ng/manager/drag_drop/drag_drop_initiating/drag_drop_initiating_handler.h"
#include "core/components_ng/pattern/pattern.h"
#include "test/mock/frameworks/core/common/mock_container.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
class DefaultSupportDragPattern : public Pattern {
    DECLARE_ACE_TYPE(DefaultSupportDragPattern, Pattern);

public:
    explicit DefaultSupportDragPattern(bool supportDrag) : supportDrag_(supportDrag) {}
    ~DefaultSupportDragPattern() override = default;

    bool DefaultSupportDrag() override
    {
        return supportDrag_;
    }

private:
    bool supportDrag_ = false;
};

class CapturingTaskExecutor : public TaskExecutor {
    DECLARE_ACE_TYPE(CapturingTaskExecutor, TaskExecutor);

public:
    CapturingTaskExecutor() = default;
    ~CapturingTaskExecutor() override = default;

    void RunPendingTasks()
    {
        auto tasks = std::move(tasks_);
        tasks_.clear();
        for (auto& task : tasks) {
            if (task) {
                task();
            }
        }
    }

    size_t GetPendingTaskSize() const
    {
        return tasks_.size();
    }

    void AddTaskObserver(Task&& callback) override {}

    void RemoveTaskObserver() override {}

    bool WillRunOnCurrentThread(TaskType type) const override
    {
        return true;
    }

    void RemoveTask(TaskType type, const std::string& name) override {}

protected:
    bool OnPostTask(Task&& task, TaskType type, uint32_t delayTime, const std::string& name,
        PriorityType priorityType = PriorityType::LOW,
        VsyncBarrierOption barrierOption = VsyncBarrierOption::NO_BARRIER) const override
    {
        tasks_.emplace_back(std::move(task));
        return true;
    }

    Task WrapTaskWithTraceId(Task&& task, int32_t id) const override
    {
        return task;
    }

    bool OnPostTaskWithoutTraceId(Task&& task, TaskType type, uint32_t delayTime, const std::string& name,
        PriorityType priorityType = PriorityType::LOW) const override
    {
        tasks_.emplace_back(std::move(task));
        return true;
    }

private:
    mutable std::vector<Task> tasks_;
};

struct GestureEventHubContext {
    RefPtr<FrameNode> frameNode;
    RefPtr<EventHub> eventHub;
    RefPtr<GestureEventHub> gestureEventHub;
};

GestureEventHubContext CreateGestureEventHubWithPattern(const std::string& tag, const RefPtr<Pattern>& pattern)
{
    GestureEventHubContext context;
    context.frameNode = FrameNode::CreateFrameNode(
        tag, ElementRegister::GetInstance()->MakeUniqueId(), pattern, false);
    EXPECT_NE(context.frameNode, nullptr);
    context.eventHub = context.frameNode->GetEventHub<EventHub>();
    EXPECT_NE(context.eventHub, nullptr);
    context.eventHub->AttachHost(context.frameNode);
    context.gestureEventHub = context.frameNode->GetOrCreateGestureEventHub();
    EXPECT_NE(context.gestureEventHub, nullptr);
    return context;
}

RefPtr<DragEvent> CreateBasicDragEvent()
{
    auto action = [](GestureEvent& info) {};
    auto cancel = []() {};
    return AceType::MakeRefPtr<DragEvent>(
        GestureEventFunc(action), GestureEventFunc(action), GestureEventFunc(action), GestureEventNoParameter(cancel));
}

GestureEventHubContext CreateOldWebGestureHub()
{
    auto context = CreateGestureEventHubWithPattern(V2::WEB_ETS_TAG, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(context.gestureEventHub, nullptr);
    context.gestureEventHub->SetCustomDragEvent(CreateBasicDragEvent(), PAN_DIRECTION_ALL, FINGERS, DISTANCE);
    EXPECT_NE(context.gestureEventHub->dragEventActuator_, nullptr);
    EXPECT_EQ(AceType::DynamicCast<DragDropEventActuator>(context.gestureEventHub->dragEventActuator_), nullptr);
    return context;
}
} // namespace

class GestureEventHubBranchCoverageNg : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        MockContainer::SetUp();
    }

    static void TearDownTestSuite()
    {
        MockContainer::TearDown();
    }

    void SetUp() override
    {
        MockPipelineContext::SetUp();
    }

    void TearDown() override
    {
        SystemProperties::dragDropFrameworkStatus_ = 0;
        MockPipelineContext::TearDown();
    }
};

/**
 * @tc.name: GestureEventHubIsAllowedDragCoverage001
 * @tc.desc: Cover IsAllowedDrag guards for missing host, user-set nodes, drag callback and pattern defaults.
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubBranchCoverageNg, GestureEventHubIsAllowedDragCoverage001, TestSize.Level1)
{
    auto detachedEventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(detachedEventHub, nullptr);
    auto detachedGestureHub = AceType::MakeRefPtr<GestureEventHub>(detachedEventHub);
    ASSERT_NE(detachedGestureHub, nullptr);
    EXPECT_FALSE(detachedGestureHub->IsAllowedDrag(detachedEventHub));

    auto draggableContext =
        CreateGestureEventHubWithPattern("drag_false", AceType::MakeRefPtr<DefaultSupportDragPattern>(false));
    auto draggableHub = draggableContext.gestureEventHub;
    ASSERT_NE(draggableHub, nullptr);
    auto draggableEventHub = draggableContext.eventHub;
    ASSERT_NE(draggableEventHub, nullptr);
    auto draggableFrameNode = draggableContext.frameNode;
    ASSERT_NE(draggableFrameNode, nullptr);
    draggableFrameNode->draggable_ = true;
    EXPECT_FALSE(draggableHub->IsAllowedDrag(draggableEventHub));

    auto defaultSupportContext =
        CreateGestureEventHubWithPattern("drag_true", AceType::MakeRefPtr<DefaultSupportDragPattern>(true));
    auto defaultSupportHub = defaultSupportContext.gestureEventHub;
    ASSERT_NE(defaultSupportHub, nullptr);
    auto defaultSupportEventHub = defaultSupportContext.eventHub;
    ASSERT_NE(defaultSupportEventHub, nullptr);
    auto defaultSupportFrameNode = defaultSupportContext.frameNode;
    ASSERT_NE(defaultSupportFrameNode, nullptr);
    defaultSupportFrameNode->draggable_ = true;
    EXPECT_TRUE(defaultSupportHub->IsAllowedDrag(defaultSupportEventHub));

    auto userSetContext =
        CreateGestureEventHubWithPattern("user_set", AceType::MakeRefPtr<DefaultSupportDragPattern>(true));
    auto userSetHub = userSetContext.gestureEventHub;
    ASSERT_NE(userSetHub, nullptr);
    auto userSetEventHub = userSetContext.eventHub;
    ASSERT_NE(userSetEventHub, nullptr);
    auto userSetFrameNode = userSetContext.frameNode;
    ASSERT_NE(userSetFrameNode, nullptr);
    userSetFrameNode->userSet_ = true;
    userSetFrameNode->draggable_ = false;
    EXPECT_FALSE(userSetHub->IsAllowedDrag(userSetEventHub));

    auto callbackContext =
        CreateGestureEventHubWithPattern("callback_true", AceType::MakeRefPtr<DefaultSupportDragPattern>(false));
    auto callbackHub = callbackContext.gestureEventHub;
    ASSERT_NE(callbackHub, nullptr);
    auto callbackEventHub = callbackContext.eventHub;
    ASSERT_NE(callbackEventHub, nullptr);
    auto callbackFrameNode = callbackContext.frameNode;
    ASSERT_NE(callbackFrameNode, nullptr);
    callbackFrameNode->draggable_ = false;
    callbackFrameNode->userSet_ = false;
    auto onDragStart = [](const RefPtr<OHOS::Ace::DragEvent>& event, const std::string& extraParams) {
        return DragDropInfo();
    };
    callbackEventHub->SetOnDragStart(std::move(onDragStart));
    EXPECT_TRUE(callbackHub->IsAllowedDrag(callbackEventHub));
}

/**
 * @tc.name: GestureEventHubStartLongPressActionForWebCoverage002
 * @tc.desc: Cover StartLongPressActionForWeb with missing pipeline, missing executor and async actuator guard.
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubBranchCoverageNg, GestureEventHubStartLongPressActionForWebCoverage002, TestSize.Level1)
{
    auto context = CreateOldWebGestureHub();
    auto gestureEventHub = context.gestureEventHub;
    ASSERT_NE(gestureEventHub, nullptr);
    auto dragEventActuator = gestureEventHub->dragEventActuator_;
    ASSERT_NE(dragEventActuator, nullptr);

    int32_t updateCount = 0;
    dragEventActuator->longPressUpdate_ = [&updateCount](GestureEvent& info) {
        ++updateCount;
    };

    dragEventActuator->isReceivedLongPress_ = true;
    MockPipelineContext::TearDown();
    gestureEventHub->StartLongPressActionForWeb();
    EXPECT_EQ(updateCount, 0);
    EXPECT_TRUE(dragEventActuator->isReceivedLongPress_);

    MockPipelineContext::SetUp();
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetTaskExecutor(nullptr);
    dragEventActuator->isReceivedLongPress_ = true;
    gestureEventHub->StartLongPressActionForWeb();
    EXPECT_EQ(updateCount, 0);
    EXPECT_TRUE(dragEventActuator->isReceivedLongPress_);

    pipeline->SetTaskExecutor(AceType::MakeRefPtr<MockTaskExecutor>());
    dragEventActuator->isReceivedLongPress_ = true;
    gestureEventHub->StartLongPressActionForWeb();
    EXPECT_EQ(updateCount, 1);
    EXPECT_FALSE(dragEventActuator->isReceivedLongPress_);

    auto capturingExecutor = AceType::MakeRefPtr<CapturingTaskExecutor>();
    pipeline->SetTaskExecutor(capturingExecutor);
    dragEventActuator->isReceivedLongPress_ = true;
    gestureEventHub->dragEventActuator_ = dragEventActuator;
    gestureEventHub->StartLongPressActionForWeb();
    ASSERT_EQ(capturingExecutor->GetPendingTaskSize(), 1UL);
    gestureEventHub->dragEventActuator_ = nullptr;
    capturingExecutor->RunPendingTasks();
    EXPECT_EQ(updateCount, 1);
    EXPECT_TRUE(dragEventActuator->isReceivedLongPress_);
}

/**
 * @tc.name: GestureEventHubCancelDragForWebCoverage001
 * @tc.desc: Cover CancelDragForWeb with missing pipeline, missing executor and async actuator guard.
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubBranchCoverageNg, GestureEventHubCancelDragForWebCoverage001, TestSize.Level1)
{
    auto context = CreateOldWebGestureHub();
    auto gestureEventHub = context.gestureEventHub;
    ASSERT_NE(gestureEventHub, nullptr);
    auto dragEventActuator = gestureEventHub->dragEventActuator_;
    ASSERT_NE(dragEventActuator, nullptr);

    int32_t cancelCount = 0;
    dragEventActuator->actionCancel_ = [&cancelCount](GestureEvent& info) {
        ++cancelCount;
    };

    MockPipelineContext::TearDown();
    gestureEventHub->CancelDragForWeb();
    EXPECT_EQ(cancelCount, 0);

    MockPipelineContext::SetUp();
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetTaskExecutor(nullptr);
    gestureEventHub->CancelDragForWeb();
    EXPECT_EQ(cancelCount, 0);

    pipeline->SetTaskExecutor(AceType::MakeRefPtr<MockTaskExecutor>());
    gestureEventHub->CancelDragForWeb();
    EXPECT_EQ(cancelCount, 1);

    auto capturingExecutor = AceType::MakeRefPtr<CapturingTaskExecutor>();
    pipeline->SetTaskExecutor(capturingExecutor);
    gestureEventHub->dragEventActuator_ = dragEventActuator;
    gestureEventHub->CancelDragForWeb();
    ASSERT_EQ(capturingExecutor->GetPendingTaskSize(), 1UL);
    gestureEventHub->dragEventActuator_ = nullptr;
    capturingExecutor->RunPendingTasks();
    EXPECT_EQ(cancelCount, 1);
}

/**
 * @tc.name: GestureEventHubStartDragTaskForWebCoverage002
 * @tc.desc: Cover StartDragTaskForWeb async lambda guards for missing gesture info and actuator.
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubBranchCoverageNg, GestureEventHubStartDragTaskForWebCoverage002, TestSize.Level1)
{
    auto context = CreateOldWebGestureHub();
    auto gestureEventHub = context.gestureEventHub;
    ASSERT_NE(gestureEventHub, nullptr);
    auto dragEventActuator = gestureEventHub->dragEventActuator_;
    ASSERT_NE(dragEventActuator, nullptr);

    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto capturingExecutor = AceType::MakeRefPtr<CapturingTaskExecutor>();
    pipeline->SetTaskExecutor(capturingExecutor);

    int32_t actionStartCount = 0;
    dragEventActuator->actionStart_ = [&actionStartCount](GestureEvent& info) {
        ++actionStartCount;
    };

    gestureEventHub->gestureInfoForWeb_ = std::make_shared<GestureEvent>();
    gestureEventHub->isReceivedDragGestureInfo_ = true;
    EXPECT_TRUE(gestureEventHub->StartDragTaskForWeb());
    ASSERT_EQ(capturingExecutor->GetPendingTaskSize(), 1UL);
    gestureEventHub->gestureInfoForWeb_.reset();
    capturingExecutor->RunPendingTasks();
    EXPECT_EQ(actionStartCount, 0);

    gestureEventHub->gestureInfoForWeb_ = std::make_shared<GestureEvent>();
    gestureEventHub->dragEventActuator_ = dragEventActuator;
    gestureEventHub->isReceivedDragGestureInfo_ = true;
    EXPECT_TRUE(gestureEventHub->StartDragTaskForWeb());
    ASSERT_EQ(capturingExecutor->GetPendingTaskSize(), 1UL);
    gestureEventHub->dragEventActuator_ = nullptr;
    capturingExecutor->RunPendingTasks();
    EXPECT_EQ(actionStartCount, 0);
}

/**
 * @tc.name: GestureEventHubResetDragActionForWebCoverage002
 * @tc.desc: Cover ResetDragActionForWeb with null actuator, missing pipeline, missing manager and normal reset.
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubBranchCoverageNg, GestureEventHubResetDragActionForWebCoverage002, TestSize.Level1)
{
    auto context = CreateOldWebGestureHub();
    auto gestureEventHub = context.gestureEventHub;
    ASSERT_NE(gestureEventHub, nullptr);

    gestureEventHub->isReceivedDragGestureInfo_ = true;
    auto oldActuator = gestureEventHub->dragEventActuator_;
    gestureEventHub->dragEventActuator_ = nullptr;
    gestureEventHub->ResetDragActionForWeb();
    EXPECT_FALSE(gestureEventHub->isReceivedDragGestureInfo_);

    gestureEventHub->dragEventActuator_ = oldActuator;
    oldActuator->isReceivedLongPress_ = true;
    gestureEventHub->isReceivedDragGestureInfo_ = true;
    MockPipelineContext::TearDown();
    gestureEventHub->ResetDragActionForWeb();
    EXPECT_FALSE(gestureEventHub->isReceivedDragGestureInfo_);
    EXPECT_FALSE(oldActuator->isReceivedLongPress_);

    MockPipelineContext::SetUp();
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    pipeline->dragDropManager_ = nullptr;
    oldActuator->isReceivedLongPress_ = true;
    gestureEventHub->isReceivedDragGestureInfo_ = true;
    gestureEventHub->ResetDragActionForWeb();
    EXPECT_FALSE(gestureEventHub->isReceivedDragGestureInfo_);
    EXPECT_FALSE(oldActuator->isReceivedLongPress_);

    pipeline->dragDropManager_ = AceType::MakeRefPtr<DragDropManager>();
    auto dragDropManager = pipeline->GetDragDropManager();
    ASSERT_NE(dragDropManager, nullptr);
    dragDropManager->ResetDragging(DragDropMgrState::DRAGGING);
    oldActuator->isReceivedLongPress_ = true;
    gestureEventHub->isReceivedDragGestureInfo_ = true;
    gestureEventHub->ResetDragActionForWeb();
    EXPECT_FALSE(gestureEventHub->isReceivedDragGestureInfo_);
    EXPECT_FALSE(oldActuator->isReceivedLongPress_);
    EXPECT_FALSE(dragDropManager->IsDragging());
}

/**
 * @tc.name: GestureEventHubDragActuatorLifecycleCoverage001
 * @tc.desc: Cover old/new drag actuator routing, removal and thumbnail callback persistence.
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubBranchCoverageNg, GestureEventHubDragActuatorLifecycleCoverage001, TestSize.Level1)
{
    auto context = CreateGestureEventHubWithPattern(V2::BUTTON_ETS_TAG, AceType::MakeRefPtr<Pattern>());
    auto gestureEventHub = context.gestureEventHub;
    ASSERT_NE(gestureEventHub, nullptr);

    EXPECT_FALSE(gestureEventHub->HasDragEvent());
    gestureEventHub->RemoveDragEvent();
    EXPECT_EQ(gestureEventHub->dragEventActuator_, nullptr);

    auto dragEvent = CreateBasicDragEvent();
    gestureEventHub->SetDragEvent(dragEvent, PAN_DIRECTION_ALL, FINGERS, DISTANCE);
    ASSERT_NE(gestureEventHub->dragEventActuator_, nullptr);
    EXPECT_TRUE(gestureEventHub->HasDragEvent());
    EXPECT_FALSE(gestureEventHub->IsDragNewFwk());
    EXPECT_EQ(AceType::DynamicCast<DragDropEventActuator>(gestureEventHub->dragEventActuator_), nullptr);

    auto oldActuator = gestureEventHub->dragEventActuator_;
    gestureEventHub->RemoveDragEvent();
    EXPECT_NE(gestureEventHub->dragEventActuator_, nullptr);
    EXPECT_EQ(gestureEventHub->dragEventActuator_, oldActuator);
    EXPECT_FALSE(gestureEventHub->HasDragEvent());

    gestureEventHub->SetDragDropEvent();
    auto dragDropEventActuator = AceType::DynamicCast<DragDropEventActuator>(gestureEventHub->dragEventActuator_);
    ASSERT_NE(dragDropEventActuator, nullptr);
    EXPECT_TRUE(gestureEventHub->HasDragEvent());
    EXPECT_TRUE(gestureEventHub->IsDragNewFwk());
    EXPECT_TRUE(dragDropEventActuator->GetIsNewFwk());

    int32_t thumbnailCount = 0;
    auto thumbnailCallback = [&thumbnailCount](Offset offset) {
        ++thumbnailCount;
    };
    gestureEventHub->SetThumbnailCallback(std::move(thumbnailCallback));
    auto handler = dragDropEventActuator->dragDropInitiatingHandler_;
    ASSERT_NE(handler, nullptr);
    auto machine = handler->initiatingFlow_;
    ASSERT_NE(machine, nullptr);
    auto& params = machine->GetDragDropInitiatingParams();
    ASSERT_TRUE(static_cast<bool>(params.getTextThumbnailPixelMapCallback));
    params.getTextThumbnailPixelMapCallback(Offset(3.0, 5.0));
    EXPECT_EQ(thumbnailCount, 1);

    gestureEventHub->RemoveDragEvent();
    EXPECT_EQ(gestureEventHub->dragEventActuator_, nullptr);
    EXPECT_FALSE(gestureEventHub->HasDragEvent());

    gestureEventHub->SetCustomDragEvent(dragEvent, PAN_DIRECTION_ALL, FINGERS, DISTANCE);
    ASSERT_NE(gestureEventHub->dragEventActuator_, nullptr);
    EXPECT_EQ(AceType::DynamicCast<DragDropEventActuator>(gestureEventHub->dragEventActuator_), nullptr);
    EXPECT_FALSE(gestureEventHub->IsDragNewFwk());

    gestureEventHub->dragEventActuator_ = nullptr;
    auto emptyThumbnailCallback = [](Offset offset) {};
    gestureEventHub->SetThumbnailCallback(std::move(emptyThumbnailCallback));
    EXPECT_EQ(gestureEventHub->dragEventActuator_, nullptr);
}

/**
 * @tc.name: GestureEventHubFrameworkRoutingCoverage002
 * @tc.desc: Cover drag framework routing for unexpected system status and null host fallback.
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubBranchCoverageNg, GestureEventHubFrameworkRoutingCoverage002, TestSize.Level1)
{
    auto verifyRouting = [](const std::string& tag, bool expectNewFramework) {
        auto context = CreateGestureEventHubWithPattern(tag, AceType::MakeRefPtr<Pattern>());
        auto gestureEventHub = context.gestureEventHub;
        ASSERT_NE(gestureEventHub, nullptr);
        gestureEventHub->InitDragDropEvent();
        ASSERT_NE(gestureEventHub->dragEventActuator_, nullptr);
        auto dragDropEventActuator = AceType::DynamicCast<DragDropEventActuator>(gestureEventHub->dragEventActuator_);
        if (expectNewFramework) {
            EXPECT_NE(dragDropEventActuator, nullptr);
            EXPECT_TRUE(gestureEventHub->IsDragNewFwk());
        } else {
            EXPECT_EQ(dragDropEventActuator, nullptr);
            EXPECT_FALSE(gestureEventHub->IsDragNewFwk());
        }
    };

    SystemProperties::dragDropFrameworkStatus_ = 2;
    verifyRouting(V2::WEB_ETS_TAG, true);
    verifyRouting(V2::TEXT_ETS_TAG, true);
    verifyRouting(V2::BUTTON_ETS_TAG, true);

    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    ASSERT_NE(gestureEventHub, nullptr);
    gestureEventHub->InitDragDropEvent();
    ASSERT_NE(gestureEventHub->dragEventActuator_, nullptr);
    EXPECT_EQ(AceType::DynamicCast<DragDropEventActuator>(gestureEventHub->dragEventActuator_), nullptr);
    EXPECT_FALSE(gestureEventHub->IsDragNewFwk());
}
} // namespace OHOS::Ace::NG
