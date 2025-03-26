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
} // namespace OHOS::Ace::NG