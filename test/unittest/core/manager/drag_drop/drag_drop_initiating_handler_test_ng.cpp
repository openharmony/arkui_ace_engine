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

#include "gtest/gtest.h"
#include "test/unittest/core/manager/drag_drop/drag_drop_initiating_test_ng.h"
#define private public
#include "core/components_ng/manager/drag_drop/drag_drop_initiating/drag_drop_initiating_handler.h"
#undef private

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string CUSTOM_DRAG_END_EVENT_TYPE = "custom drag end";
const std::string DRAG_END_EVENT_TYPE = "drag end";
} // namespace

void DragDropInitiatingHandlerTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void DragDropInitiatingHandlerTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: IsNeedGatherTestNG001
 * @tc.desc: Test IsNeedGather Function When initiatingFlow_ is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropInitiatingHandlerTestNg, IsNeedGatherTestNG001, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto dragDropInitiatingHandler = AceType::MakeRefPtr<DragDropInitiatingHandler>(frameNode);
    ASSERT_NE(dragDropInitiatingHandler, nullptr);
    dragDropInitiatingHandler->initiatingFlow_ = nullptr;
    EXPECT_FALSE(dragDropInitiatingHandler->IsNeedGather());
    dragDropInitiatingHandler = AceType::MakeRefPtr<DragDropInitiatingHandler>(frameNode);
    ASSERT_NE(dragDropInitiatingHandler->initiatingFlow_, nullptr);
    dragDropInitiatingHandler->initiatingFlow_->GetDragDropInitiatingParams().isNeedGather = true;
    EXPECT_TRUE(dragDropInitiatingHandler->IsNeedGather());
}

/**
 * @tc.name: GetDragDropInitiatingStatusTestNG001
 * @tc.desc: Test GetDragDropInitiatingStatus Function When initiatingFlow_ is not nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropInitiatingHandlerTestNg, GetDragDropInitiatingStatusTestNG001, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto dragDropInitiatingHandler = AceType::MakeRefPtr<DragDropInitiatingHandler>(frameNode);
    ASSERT_NE(dragDropInitiatingHandler, nullptr);
    ASSERT_NE(dragDropInitiatingHandler->initiatingFlow_, nullptr);
    EXPECT_EQ(dragDropInitiatingHandler->GetDragDropInitiatingStatus(),
        dragDropInitiatingHandler->initiatingFlow_->GetDragDropInitiatingStatus());
}

/**
 * @tc.name: GetDragDropInitiatingStatusTestNG002
 * @tc.desc: Test GetDragDropInitiatingStatus Function When initiatingFlow_ is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropInitiatingHandlerTestNg, GetDragDropInitiatingStatusTestNG002, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto dragDropInitiatingHandler = AceType::MakeRefPtr<DragDropInitiatingHandler>(frameNode);
    ASSERT_NE(dragDropInitiatingHandler, nullptr);
    dragDropInitiatingHandler->initiatingFlow_ = nullptr;
    EXPECT_EQ(dragDropInitiatingHandler->GetDragDropInitiatingStatus(), DragDropInitiatingStatus::IDLE);
}

/**
 * @tc.name: DragDropInitiatingHandlerTestNG001
 * @tc.desc: Test DragDropInitiatingHandler Function When initiatingFlow_ is not nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropInitiatingHandlerTestNg, DragDropInitiatingHandlerTestNG001, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto dragDropInitiatingHandler = AceType::MakeRefPtr<DragDropInitiatingHandler>(frameNode);
    ASSERT_NE(dragDropInitiatingHandler, nullptr);
    EXPECT_NE(dragDropInitiatingHandler->initiatingFlow_, nullptr);
}

/**
 * @tc.name: SetThumbnailCallbackNG001
 * @tc.desc: Test DragDropInitiatingHandler Function When initiatingFlow_ is not nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropInitiatingHandlerTestNg, SetThumbnailCallbackNG001, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto dragDropInitiatingHandler = AceType::MakeRefPtr<DragDropInitiatingHandler>(frameNode);
    ASSERT_NE(dragDropInitiatingHandler, nullptr);
    EXPECT_NE(dragDropInitiatingHandler->initiatingFlow_, nullptr);
    dragDropInitiatingHandler->SetThumbnailCallback([](const Offset&) {});
    EXPECT_NE(dragDropInitiatingHandler->initiatingFlow_->dragDropInitiatingParams_.getTextThumbnailPixelMapCallback,
        nullptr);
}

/**
 * @tc.name: FireCustomerOnDragEndNG001
 * @tc.desc: Test DragDropInitiatingHandler Function When initiatingFlow_ is not nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropInitiatingHandlerTestNg, FireCustomerOnDragEndNG001, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto dragDropInitiatingHandler = AceType::MakeRefPtr<DragDropInitiatingHandler>(frameNode);
    ASSERT_NE(dragDropInitiatingHandler, nullptr);
    EXPECT_NE(dragDropInitiatingHandler->initiatingFlow_, nullptr);
    auto machine = dragDropInitiatingHandler->initiatingFlow_;
    ASSERT_NE(machine, nullptr);
    machine->InitializeState();
    machine->currentState_ = static_cast<int32_t>(DragDropInitiatingStatus::IDLE);
    DragDropGlobalController::GetInstance().SetDragStartRequestStatus(DragStartRequestStatus::WAITING);
    DragDropGlobalController::GetInstance().UpdateDragDropInitiatingStatus(frameNode, DragDropInitiatingStatus::MOVING);
    EXPECT_EQ(DragDropGlobalController::GetInstance().currentDragNode_, frameNode);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    auto eventHub = frameNode->GetOrCreateEventHub<EventHub>();
    std::string customerDragEventType;
    std::string dragEventType;
    auto customerOnDragEnd = [&customerDragEventType](const RefPtr<OHOS::Ace::DragEvent>& info) {
        EXPECT_EQ(info->GetResult(), DragRet::DRAG_FAIL);
        customerDragEventType = CUSTOM_DRAG_END_EVENT_TYPE;
    };
    eventHub->SetCustomerOnDragFunc(DragFuncType::DRAG_END, customerOnDragEnd);
    auto onDragEnd = [&dragEventType](const RefPtr<OHOS::Ace::DragEvent>& info) {
        EXPECT_EQ(info->GetResult(), DragRet::DRAG_FAIL);
        dragEventType = DRAG_END_EVENT_TYPE;
    };
    eventHub->SetOnDragEnd(onDragEnd);
    ASSERT_NE(machine->dragDropInitiatingState_[machine->currentState_], nullptr);
    machine->dragDropInitiatingState_[machine->currentState_]->Init(machine->currentState_);
    EXPECT_EQ(DragDropGlobalController::GetInstance().currentDragNode_, nullptr);
    EXPECT_EQ(customerDragEventType, CUSTOM_DRAG_END_EVENT_TYPE);
    EXPECT_EQ(dragEventType, DRAG_END_EVENT_TYPE);
}

/**
 * @tc.name: IsAllowedDragNG001
 * @tc.desc: Test DragDropInitiatingHandler Function When initiatingFlow_ is not nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropInitiatingHandlerTestNg, IsAllowedDragNG001, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto dragDropInitiatingHandler = AceType::MakeRefPtr<DragDropInitiatingHandler>(frameNode);
    ASSERT_NE(dragDropInitiatingHandler, nullptr);
    EXPECT_NE(dragDropInitiatingHandler->initiatingFlow_, nullptr);
    auto machine = dragDropInitiatingHandler->initiatingFlow_;
    ASSERT_NE(machine, nullptr);
    machine->InitializeState();
    machine->currentState_ = static_cast<int32_t>(DragDropInitiatingStatus::IDLE);
    ASSERT_NE(machine->dragDropInitiatingState_[machine->currentState_], nullptr);
    EXPECT_TRUE(machine->dragDropInitiatingState_[machine->currentState_]->IsAllowedDrag());
}
} // namespace OHOS::Ace::NG