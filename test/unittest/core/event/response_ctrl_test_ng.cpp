/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include <cstddef>
#include <cstdint>
#include <unistd.h>

#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/response_ctrl.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class ResponseCtrlTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void ResponseCtrlTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    GTEST_LOG_(INFO) << "ResponseCtrlTestNg SetUpTestCase";
}

void ResponseCtrlTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    GTEST_LOG_(INFO) << "ResponseCtrlTestNg TearDownTestCase";
}

/**
 * @tc.name: ResponseCtrlTest001
 * @tc.desc: Response ctrl test first valid node call shouldResponse
 * @tc.type: FUNC
 */
HWTEST_F(ResponseCtrlTestNg, ResponseCtrlTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ResponseCtrl.
     */
    auto responseCtrl = AceType::MakeRefPtr<ResponseCtrl>();

    /**
     * @tc.steps: step2. create frame nodes.
     */
    auto node = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());

    /**
     * @tc.steps: step3. Check ShouldResponse.
     * @tc.expected: first node should return true.
     */
    bool shouldResponse = responseCtrl->ShouldResponse(WeakPtr<FrameNode>(node));
    EXPECT_EQ(shouldResponse, true);
}

/**
 * @tc.name: ResponseCtrlTest002
 * @tc.desc: Response ctrl test first invalid node call shouldResponse
 * @tc.type: FUNC
 */
HWTEST_F(ResponseCtrlTestNg, ResponseCtrlTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ResponseCtrl.
     */
    auto responseCtrl = AceType::MakeRefPtr<ResponseCtrl>();

    /**
     * @tc.steps: step2. create empty node
     */
    RefPtr<FrameNode> emptyNode;

    /**
     * @tc.steps: step3. check ShouldResponse.
     * @tc.expected: invalid node should return true.
     */
    bool shouldResponse = responseCtrl->ShouldResponse(WeakPtr<FrameNode>(emptyNode));
    EXPECT_EQ(shouldResponse, true);
}

/**
 * @tc.name: ResponseCtrlTest003
 * @tc.desc: Response ctrl monopolize test
 * @tc.type: FUNC
 */
HWTEST_F(ResponseCtrlTestNg, ResponseCtrlTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ResponseCtrl.
     */
    auto responseCtrl = AceType::MakeRefPtr<ResponseCtrl>();

    /**
     * @tc.steps: step2. create frame nodes.
     */
    auto node1 = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());

    auto node2 = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());

    /**
     * @tc.steps: step3. first node Check ShouldResponse.
     * @tc.expected: first node should return true.
     */
    bool shouldResponse = responseCtrl->ShouldResponse(WeakPtr<FrameNode>(node1));
    EXPECT_EQ(shouldResponse, true);

    /**
     * @tc.steps: step4. first node Check ShouldResponse.
     * @tc.expected: state equal to ResponseCtrl::MonopolizeState::OFF.
     */
    responseCtrl->TrySetFirstResponse(WeakPtr<FrameNode>(node1));
    EXPECT_EQ(responseCtrl->state_, ResponseCtrl::MonopolizeState::OFF);
    /**
     * @tc.steps: step5. second node Check ShouldResponse.
     * @tc.expected: second node should return true.
     */
    shouldResponse = responseCtrl->ShouldResponse(WeakPtr<FrameNode>(node2));
    EXPECT_EQ(shouldResponse, true);
}

/**
 * @tc.name: ResponseCtrlTest004
 * @tc.desc: Response ctrl monopolize test
 * @tc.type: FUNC
 */
HWTEST_F(ResponseCtrlTestNg, ResponseCtrlTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ResponseCtrl.
     */
    auto responseCtrl = AceType::MakeRefPtr<ResponseCtrl>();

    /**
     * @tc.steps: step2. create frame nodes.
     */
    auto node1 = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());

    auto node2 = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());

    /**
     * @tc.steps: step3. set node1 monopolizeEvents.
     * @tc.expected: gestureEventHub is not nullptr.
     */
    auto gestureEventHub = node1->GetOrCreateGestureEventHub();
    EXPECT_NE(gestureEventHub, nullptr);
    gestureEventHub->monopolizeEvents_ = true;

    /**
     * @tc.steps: step4. first node Check ShouldResponse.
     * @tc.expected: first node should return true.
     */
    bool shouldResponse = responseCtrl->ShouldResponse(WeakPtr<FrameNode>(node1));
    EXPECT_EQ(shouldResponse, true);

    /**
     * @tc.steps: step5. first node SetFirstResponse.
     * @tc.expected: state equal to ResponseCtrl::MonopolizeState::ON.
     */
    responseCtrl->TrySetFirstResponse(WeakPtr<FrameNode>(node1));
    EXPECT_EQ(responseCtrl->state_, ResponseCtrl::MonopolizeState::ON);
    /**
     * @tc.steps: step6. second node Check ShouldResponse.
     * @tc.expected: second node should return false.
     */
    shouldResponse = responseCtrl->ShouldResponse(WeakPtr<FrameNode>(node2));
    EXPECT_EQ(shouldResponse, false);
}

/**
 * @tc.name: ResponseCtrlTest005
 * @tc.desc: Response ctrl monopolize test
 * @tc.type: FUNC
 */
HWTEST_F(ResponseCtrlTestNg, ResponseCtrlTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ResponseCtrl.
     */
    auto responseCtrl = AceType::MakeRefPtr<ResponseCtrl>();

    /**
     * @tc.steps: step2. create frame node.
     */
    auto node1 = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());

    /**
     * @tc.steps: step3. set node1 monopolizeEvents.
     * @tc.expected: gestureEventHub is not nullptr.
     */
    auto gestureEventHub = node1->GetOrCreateGestureEventHub();
    EXPECT_NE(gestureEventHub, nullptr);
    gestureEventHub->monopolizeEvents_ = true;

    /**
     * @tc.steps: step4. first node Check ShouldResponse.
     * @tc.expected: first node should return true.
     */
    bool shouldResponse = responseCtrl->ShouldResponse(WeakPtr<FrameNode>(node1));
    EXPECT_EQ(shouldResponse, true);

    /**
     * @tc.steps: step5. first node SetFirstResponse.
     * @tc.expected: state equal to ResponseCtrl::MonopolizeState::ON.
     */
    responseCtrl->TrySetFirstResponse(WeakPtr<FrameNode>(node1));
    EXPECT_EQ(responseCtrl->state_, ResponseCtrl::MonopolizeState::ON);
    /**
     * @tc.steps: step6. Check ShouldResponse twice.
     * @tc.expected: twice check should return true.
     */
    shouldResponse = responseCtrl->ShouldResponse(WeakPtr<FrameNode>(node1));
    EXPECT_EQ(shouldResponse, true);
}

/**
 * @tc.name: ResponseCtrlTest006
 * @tc.desc: Response ctrl monopolize test
 * @tc.type: FUNC
 */
HWTEST_F(ResponseCtrlTestNg, ResponseCtrlTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ResponseCtrl.
     */
    auto responseCtrl = AceType::MakeRefPtr<ResponseCtrl>();

    /**
     * @tc.steps: step2. create frame nodes.
     */
    RefPtr<FrameNode> node1;

    auto node2 = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());

    /**
     * @tc.steps: step3. first node SetFirstResponse.
     * @tc.expected: state equal to ResponseCtrl::MonopolizeState::INIT.
     */
    responseCtrl->TrySetFirstResponse(WeakPtr<FrameNode>(node1));
    EXPECT_EQ(responseCtrl->state_, ResponseCtrl::MonopolizeState::INIT);
    /**
     * @tc.steps: step4. Check ShouldResponse by node2.
     * @tc.expected: should return true.
     */
    bool shouldResponse = responseCtrl->ShouldResponse(WeakPtr<FrameNode>(node2));
    EXPECT_EQ(shouldResponse, true);
}

/**
 * @tc.name: ResponseCtrlTest007
 * @tc.desc: Response ctrl monopolize test
 * @tc.type: FUNC
 */
HWTEST_F(ResponseCtrlTestNg, ResponseCtrlTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ResponseCtrl.
     */
    auto responseCtrl = AceType::MakeRefPtr<ResponseCtrl>();

    RefPtr<FrameNode> node1;
    /**
     * @tc.steps: step2. create frame nodes.
     */
    auto node2 = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());

    /**
     * @tc.steps: step3. first node SetFirstResponse.
     * @tc.expected: state equal to ResponseCtrl::MonopolizeState::INIT.
     */
    responseCtrl->TrySetFirstResponse(WeakPtr<FrameNode>(node1));
    EXPECT_EQ(responseCtrl->state_, ResponseCtrl::MonopolizeState::INIT);
    /**
     * @tc.steps: step4. Check ShouldResponse.
     * @tc.expected: should return true.
     */
    bool shouldResponse = responseCtrl->ShouldResponse(WeakPtr<FrameNode>(node2));
    EXPECT_EQ(shouldResponse, true);

    /**
     * @tc.steps: step5. node2 SetFirstResponse.
     * @tc.expected: state equal to ResponseCtrl::MonopolizeState::OFF.
     */
    responseCtrl->TrySetFirstResponse(WeakPtr<FrameNode>(node2));
    EXPECT_EQ(responseCtrl->state_, ResponseCtrl::MonopolizeState::OFF);
}

/**
 * @tc.name: ResponseCtrlTest008
 * @tc.desc: Response ctrl monopolize test
 * @tc.type: FUNC
 */
HWTEST_F(ResponseCtrlTestNg, ResponseCtrlTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ResponseCtrl.
     */
    auto responseCtrl = AceType::MakeRefPtr<ResponseCtrl>();

    /**
     * @tc.steps: step2. create empty frame node.
     */
    RefPtr<FrameNode> node1;

    /**
     * @tc.steps: step3. create frame nodes.
     */
    auto node2 = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());

    auto node3 = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());

    /**
     * @tc.steps: step4. first node SetFirstResponse.
     * @tc.expected: state equal to ResponseCtrl::MonopolizeState::INIT.
     */
    responseCtrl->TrySetFirstResponse(WeakPtr<FrameNode>(node1));
    EXPECT_EQ(responseCtrl->state_, ResponseCtrl::MonopolizeState::INIT);
    /**
     * @tc.steps: step5. node2 check ShouldResponse.
     * @tc.expected: should return true.
     */
    bool shouldResponse = responseCtrl->ShouldResponse(WeakPtr<FrameNode>(node2));
    EXPECT_EQ(shouldResponse, true);

    /**
     * @tc.steps: step6. node2 SetFirstResponse.
     * @tc.expected: state equal to ResponseCtrl::MonopolizeState::OFF.
     */
    responseCtrl->TrySetFirstResponse(WeakPtr<FrameNode>(node2));
    EXPECT_EQ(responseCtrl->state_, ResponseCtrl::MonopolizeState::OFF);

    /**
     * @tc.steps: step7. node3 ShouldResponse.
     * @tc.expected: should return true.
     */
    shouldResponse = responseCtrl->ShouldResponse(WeakPtr<FrameNode>(node3));
    EXPECT_EQ(shouldResponse, true);
}

/**
 * @tc.name: ResponseCtrlTest009
 * @tc.desc: Response ctrl monopolize test
 * @tc.type: FUNC
 */
HWTEST_F(ResponseCtrlTestNg, ResponseCtrlTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ResponseCtrl.
     */
    auto responseCtrl = AceType::MakeRefPtr<ResponseCtrl>();

    /**
     * @tc.steps: step2. create frame nodes.
     * @tc.expected: frame node is not nullptr.
     */
    auto node1 = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());

    auto node2 = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());

    /**
     * @tc.steps: step3. get gesture event hub and set node1 monopolizeEvents true.
     * @tc.expected: gestureEventHub not nullptr
     */
    auto gestureEventHub = node1->GetOrCreateGestureEventHub();
    EXPECT_NE(gestureEventHub, nullptr);
    gestureEventHub->monopolizeEvents_ = true;

    /**
     * @tc.steps: step4. first node Check ShouldResponse.
     * @tc.expected: first node should return true.
     */
    bool shouldResponse = responseCtrl->ShouldResponse(WeakPtr<FrameNode>(node1));
    EXPECT_EQ(shouldResponse, true);

    /**
     * @tc.steps: step5. first node SetFirstResponse.
     * @tc.expected: state equal to ResponseCtrl::MonopolizeState::ON.
     */
    responseCtrl->TrySetFirstResponse(WeakPtr<FrameNode>(node1));
    EXPECT_EQ(responseCtrl->state_, ResponseCtrl::MonopolizeState::ON);
    /**
     * @tc.steps: step6. second node check ShouldResponse.
     * @tc.expected: second node should return false.
     */
    shouldResponse = responseCtrl->ShouldResponse(WeakPtr<FrameNode>(node2));
    EXPECT_EQ(shouldResponse, false);

    /**
     * @tc.steps: step7. response ctrl reset.
     * @tc.expected: state equal to ResponseCtrl::MonopolizeState::INIT.
     */
    responseCtrl->Reset();
    EXPECT_EQ(responseCtrl->state_, ResponseCtrl::MonopolizeState::INIT);

    /**
     * @tc.steps: step8. create new frame node.
     * @tc.expected: frame node is not nullptr.
     */
    auto node3 = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());

    /**
     * @tc.steps: step9. node3 Check ShouldResponse.
     * @tc.expected: should return true.
     */
    shouldResponse = responseCtrl->ShouldResponse(WeakPtr<FrameNode>(node3));
    EXPECT_EQ(shouldResponse, true);
}

/**
 * @tc.name: ResponseCtrlTest010
 * @tc.desc: Response ctrl monopolize test
 * @tc.type: FUNC
 */
HWTEST_F(ResponseCtrlTestNg, ResponseCtrlTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ResponseCtrl.
     */
    auto responseCtrl = AceType::MakeRefPtr<ResponseCtrl>();

    /**
     * @tc.steps: step2. create frame nodes.
     */
    auto node1 = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());

    auto node2 = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());

    /**
     * @tc.steps: step3. get gesture event hub and set node1 monopolizeEvents false.
     * @tc.expected: gestureEventHub is not nullptr
     */
    auto gestureEventHub = node1->GetOrCreateGestureEventHub();
    EXPECT_NE(gestureEventHub, nullptr);
    gestureEventHub->monopolizeEvents_ = false;

    /**
     * @tc.steps: step4. first node Check ShouldResponse.
     * @tc.expected: first node should return true.
     */
    bool shouldResponse = responseCtrl->ShouldResponse(WeakPtr<FrameNode>(node1));
    EXPECT_EQ(shouldResponse, true);

    /**
     * @tc.steps: step5. first node SetFirstResponse.
     * @tc.expected: state equal to ResponseCtrl::MonopolizeState::OFF.
     */
    responseCtrl->TrySetFirstResponse(WeakPtr<FrameNode>(node1));
    EXPECT_EQ(responseCtrl->state_, ResponseCtrl::MonopolizeState::OFF);
    /**
     * @tc.steps: step6. second node Check ShouldResponse.
     * @tc.expected: second node should return true.
     */
    shouldResponse = responseCtrl->ShouldResponse(WeakPtr<FrameNode>(node2));
    EXPECT_EQ(shouldResponse, true);

    /**
     * @tc.steps: step7. response ctrl reset.
     * @tc.expected: state equal to ResponseCtrl::MonopolizeState::INIT.
     */
    responseCtrl->Reset();
    EXPECT_EQ(responseCtrl->state_, ResponseCtrl::MonopolizeState::INIT);

    /**
     * @tc.steps: step8. create new frame node.
     */
    auto node3 = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());

    /**
     * @tc.steps: step9. node3 check ShouldResponse.
     * @tc.expected: should return true.
     */
    shouldResponse = responseCtrl->ShouldResponse(WeakPtr<FrameNode>(node3));
    EXPECT_EQ(shouldResponse, true);
}

/**
 * @tc.name: ResponseCtrlTest011
 * @tc.desc: Response ctrl monopolize test
 * @tc.type: FUNC
 */
HWTEST_F(ResponseCtrlTestNg, ResponseCtrlTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ResponseCtrl.
     */
    auto responseCtrl = AceType::MakeRefPtr<ResponseCtrl>();

    /**
     * @tc.steps: step2. create frame node.
     */
    auto node1 = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());

    /**
     * @tc.steps: step3. create empty frame node.
     */
    RefPtr<FrameNode> node2;

    /**
     * @tc.steps: step4. get gesture event hub and set node1 monopolizeEvents false.
     * @tc.expected: gestureEventHub not nullptr
     */
    auto gestureEventHub = node1->GetOrCreateGestureEventHub();
    EXPECT_NE(gestureEventHub, nullptr);
    gestureEventHub->monopolizeEvents_ = false;

    /**
     * @tc.steps: step5. first node Check ShouldResponse.
     * @tc.expected: first node should return true.
     */
    bool shouldResponse = responseCtrl->ShouldResponse(WeakPtr<FrameNode>(node1));
    EXPECT_EQ(shouldResponse, true);

    /**
     * @tc.steps: step6. first node SetFirstResponse.
     * @tc.expected: state equal to ResponseCtrl::MonopolizeState::OFF.
     */
    responseCtrl->TrySetFirstResponse(WeakPtr<FrameNode>(node1));
    EXPECT_EQ(responseCtrl->state_, ResponseCtrl::MonopolizeState::OFF);
    /**
     * @tc.steps: step7. second node Check ShouldResponse.
     * @tc.expected: second node should return true.
     */
    shouldResponse = responseCtrl->ShouldResponse(WeakPtr<FrameNode>(node2));
    EXPECT_EQ(shouldResponse, true);
}

/**
 * @tc.name: ResponseCtrlTest012
 * @tc.desc: Response ctrl monopolize test
 * @tc.type: FUNC
 */
HWTEST_F(ResponseCtrlTestNg, ResponseCtrlTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ResponseCtrl.
     */
    auto responseCtrl = AceType::MakeRefPtr<ResponseCtrl>();

    /**
     * @tc.steps: step2. create frame node.
     */
    auto node1 = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());

    /**
     * @tc.steps: step3. get gesture event hub and set node1 monopolizeEvents false.
     * @tc.expected: gestureEventHub not nullptr
     */
    auto gestureEventHub = node1->GetOrCreateGestureEventHub();
    EXPECT_NE(gestureEventHub, nullptr);
    gestureEventHub->monopolizeEvents_ = true;

    /**
     * @tc.steps: step4. first node Check ShouldResponse.
     * @tc.expected: first node should return true.
     */
    bool shouldResponse = responseCtrl->ShouldResponse(WeakPtr<FrameNode>(node1));
    EXPECT_EQ(shouldResponse, true);

    /**
     * @tc.steps: step5. first node SetFirstResponse.
     * @tc.expected: state equal to ResponseCtrl::MonopolizeState::ON.
     */
    responseCtrl->TrySetFirstResponse(WeakPtr<FrameNode>(node1));
    EXPECT_EQ(responseCtrl->state_, ResponseCtrl::MonopolizeState::ON);
    /**
     * @tc.steps: step6. reset response controller.
     * @tc.expected: state equal to ResponseCtrl::MonopolizeState::INIT.
     */
    responseCtrl->Reset();
    EXPECT_EQ(responseCtrl->state_, ResponseCtrl::MonopolizeState::INIT);
}

/**
 * @tc.name: ResponseCtrlTest013
 * @tc.desc: Response ctrl monopolize test
 * @tc.type: FUNC
 */
HWTEST_F(ResponseCtrlTestNg, ResponseCtrlTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ResponseCtrl.
     */
    auto responseCtrl = AceType::MakeRefPtr<ResponseCtrl>();

    /**
     * @tc.steps: step2. create frame node.
     */
    auto node1 = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());

    /**
     * @tc.steps: step3. get gesture event hub and set node1 monopolizeEvents false.
     * @tc.expected: gestureEventHub not nullptr
     */
    auto gestureEventHub = node1->GetOrCreateGestureEventHub();
    EXPECT_NE(gestureEventHub, nullptr);
    gestureEventHub->monopolizeEvents_ = false;

    /**
     * @tc.steps: step4. first node Check ShouldResponse.
     * @tc.expected: first node should return true.
     */
    bool shouldResponse = responseCtrl->ShouldResponse(WeakPtr<FrameNode>(node1));
    EXPECT_EQ(shouldResponse, true);

    /**
     * @tc.steps: step5. first node SetFirstResponse.
     * @tc.expected: state equal to ResponseCtrl::MonopolizeState::OFF.
     */
    responseCtrl->TrySetFirstResponse(WeakPtr<FrameNode>(node1));
    EXPECT_EQ(responseCtrl->state_, ResponseCtrl::MonopolizeState::OFF);
    /**
     * @tc.steps: step6. reset response controller.
     * @tc.expected: state equal to ResponseCtrl::MonopolizeState::INIT.
     */
    responseCtrl->Reset();
    EXPECT_EQ(responseCtrl->state_, ResponseCtrl::MonopolizeState::INIT);
}
} // namespace OHOS::Ace::NG
