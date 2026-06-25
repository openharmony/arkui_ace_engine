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

#include "core/components_ng/event/drag_drop_event.h"
#include "core/components_ng/manager/drag_drop/drag_drop_manager.h"
#include "frameworks/base/window/drag_window.h"
#include "test/mock/frameworks/core/common/mock_container.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
struct GestureEventHubContext {
    RefPtr<FrameNode> frameNode;
    RefPtr<EventHub> eventHub;
    RefPtr<GestureEventHub> gestureEventHub;
};

class GestureEventHubIncrementalCoverageNg : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        MockContainer::SetUp();
        MOCK_DRAG_WINDOW = DragWindow::CreateDragWindow("", 0, 0, 0, 0);
        MOCK_TASK_EXECUTOR = AceType::MakeRefPtr<MockTaskExecutor>();
    }

    static void TearDownTestSuite()
    {
        MockContainer::TearDown();
        MOCK_DRAG_WINDOW = nullptr;
        MOCK_TASK_EXECUTOR = nullptr;
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
} // namespace

/**
 * @tc.name: GestureEventHubCheckNeedDragDropFrameworkStatusCoverage001
 * @tc.desc: Test drag framework routing for old and new drag paths.
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubIncrementalCoverageNg, GestureEventHubCheckNeedDragDropFrameworkStatusCoverage001,
    TestSize.Level1)
{
    auto createGestureEventHub = [](const std::string& tag) -> GestureEventHubContext {
        GestureEventHubContext context;
        context.frameNode = FrameNode::CreateFrameNode(
            tag, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
        context.eventHub = context.frameNode->GetEventHub<EventHub>();
        if (context.eventHub) {
            context.eventHub->AttachHost(context.frameNode);
            context.gestureEventHub = context.frameNode->GetOrCreateGestureEventHub();
        }
        return context;
    };

    SystemProperties::dragDropFrameworkStatus_ = 0;
    auto webContext = createGestureEventHub(V2::WEB_ETS_TAG);
    auto webGestureHub = webContext.gestureEventHub;
    ASSERT_NE(webGestureHub, nullptr);
    webGestureHub->InitDragDropEvent();
    ASSERT_NE(webGestureHub->dragEventActuator_, nullptr);
    EXPECT_EQ(AceType::DynamicCast<DragDropEventActuator>(webGestureHub->dragEventActuator_), nullptr);
    EXPECT_FALSE(webGestureHub->dragEventActuator_->GetIsNewFwk());
    EXPECT_FALSE(webGestureHub->IsDragNewFwk());

    auto textContext = createGestureEventHub(V2::TEXT_ETS_TAG);
    auto textGestureHub = textContext.gestureEventHub;
    ASSERT_NE(textGestureHub, nullptr);
    textGestureHub->InitDragDropEvent();
    ASSERT_NE(textGestureHub->dragEventActuator_, nullptr);
    EXPECT_EQ(AceType::DynamicCast<DragDropEventActuator>(textGestureHub->dragEventActuator_), nullptr);
    EXPECT_FALSE(textGestureHub->dragEventActuator_->GetIsNewFwk());
    EXPECT_FALSE(textGestureHub->IsDragNewFwk());

    auto buttonContext = createGestureEventHub(V2::BUTTON_ETS_TAG);
    auto buttonGestureHub = buttonContext.gestureEventHub;
    ASSERT_NE(buttonGestureHub, nullptr);
    buttonGestureHub->InitDragDropEvent();
    ASSERT_NE(buttonGestureHub->dragEventActuator_, nullptr);
    EXPECT_NE(AceType::DynamicCast<DragDropEventActuator>(buttonGestureHub->dragEventActuator_), nullptr);
    EXPECT_TRUE(buttonGestureHub->IsDragNewFwk());

    SystemProperties::dragDropFrameworkStatus_ = 1;
    auto webNewStatusContext = createGestureEventHub(V2::WEB_ETS_TAG);
    auto webGestureHubNewStatus = webNewStatusContext.gestureEventHub;
    ASSERT_NE(webGestureHubNewStatus, nullptr);
    webGestureHubNewStatus->InitDragDropEvent();
    ASSERT_NE(webGestureHubNewStatus->dragEventActuator_, nullptr);
    EXPECT_EQ(AceType::DynamicCast<DragDropEventActuator>(webGestureHubNewStatus->dragEventActuator_), nullptr);
    EXPECT_FALSE(webGestureHubNewStatus->dragEventActuator_->GetIsNewFwk());
    EXPECT_FALSE(webGestureHubNewStatus->IsDragNewFwk());

    auto buttonNewStatusContext = createGestureEventHub(V2::BUTTON_ETS_TAG);
    auto buttonGestureHubNewStatus = buttonNewStatusContext.gestureEventHub;
    ASSERT_NE(buttonGestureHubNewStatus, nullptr);
    buttonGestureHubNewStatus->InitDragDropEvent();
    ASSERT_NE(buttonGestureHubNewStatus->dragEventActuator_, nullptr);
    EXPECT_NE(AceType::DynamicCast<DragDropEventActuator>(buttonGestureHubNewStatus->dragEventActuator_), nullptr);
    EXPECT_TRUE(buttonGestureHubNewStatus->IsDragNewFwk());

    SystemProperties::dragDropFrameworkStatus_ = 3;
    auto anyContext = createGestureEventHub(V2::TEXT_ETS_TAG);
    auto anyGestureHub = anyContext.gestureEventHub;
    ASSERT_NE(anyGestureHub, nullptr);
    anyGestureHub->InitDragDropEvent();
    ASSERT_NE(anyGestureHub->dragEventActuator_, nullptr);
    EXPECT_EQ(AceType::DynamicCast<DragDropEventActuator>(anyGestureHub->dragEventActuator_), nullptr);
    EXPECT_FALSE(anyGestureHub->dragEventActuator_->GetIsNewFwk());
    EXPECT_FALSE(anyGestureHub->IsDragNewFwk());

    SystemProperties::dragDropFrameworkStatus_ = 0;
}

/**
 * @tc.name: GestureEventHubStartDragTaskForWebCoverage001
 * @tc.desc: Test StartDragTaskForWeb and ResetDragActionForWeb.
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubIncrementalCoverageNg, GestureEventHubStartDragTaskForWebCoverage001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(
        V2::WEB_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->AttachHost(frameNode);
    auto gestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);

    EXPECT_FALSE(gestureEventHub->StartDragTaskForWeb());

    gestureEventHub->isReceivedDragGestureInfo_ = true;
    MockPipelineContext::TearDown();
    EXPECT_FALSE(gestureEventHub->StartDragTaskForWeb());

    MockPipelineContext::SetUp();
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetTaskExecutor(nullptr);
    gestureEventHub->isReceivedDragGestureInfo_ = true;
    EXPECT_FALSE(gestureEventHub->StartDragTaskForWeb());

    pipeline->SetTaskExecutor(AceType::MakeRefPtr<MockTaskExecutor>());
    pipeline->dragDropManager_ = AceType::MakeRefPtr<DragDropManager>();
    gestureEventHub->InitDragDropEvent();
    ASSERT_NE(gestureEventHub->dragEventActuator_, nullptr);
    gestureEventHub->gestureInfoForWeb_ = std::make_shared<GestureEvent>();
    gestureEventHub->isReceivedDragGestureInfo_ = true;
    EXPECT_TRUE(gestureEventHub->StartDragTaskForWeb());
    EXPECT_FALSE(gestureEventHub->isReceivedDragGestureInfo_);

    auto dragDropManager = pipeline->GetDragDropManager();
    ASSERT_NE(dragDropManager, nullptr);
    dragDropManager->ResetDragging(DragDropMgrState::DRAGGING);
    gestureEventHub->dragEventActuator_->isReceivedLongPress_ = true;
    gestureEventHub->isReceivedDragGestureInfo_ = true;
    gestureEventHub->ResetDragActionForWeb();
    EXPECT_FALSE(gestureEventHub->dragEventActuator_->isReceivedLongPress_);
    EXPECT_FALSE(gestureEventHub->isReceivedDragGestureInfo_);
    EXPECT_FALSE(dragDropManager->IsDragging());
}
} // namespace OHOS::Ace::NG
