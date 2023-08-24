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

#include "gtest/gtest.h"

#define protected public
#define private public

#include "core/components_ng/base/distributed_ui.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {} // namespace
class DistributedUiTestNg : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        MockPipelineBase::SetUp();
    }
    static void TearDownTestSuite()
    {
        MockPipelineBase::TearDown();
    }

    void Init();
};

void DistributedUiTestNg::Init()
{
    auto parentNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    auto childNode = FrameNode::CreateFrameNode(
        "child", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    parentNode->AddChild(childNode);
    auto stageManager = AceType::MakeRefPtr<StageManager>(parentNode);
    MockPipelineBase::GetCurrent()->stageManager_ = stageManager;
}

/**
 * @tc.name: DistributedUiTestNg001
 * @tc.desc: DistributedUi of tests
 * @tc.type: FUNC
 */
HWTEST_F(DistributedUiTestNg, DistributedUiTestNg001, TestSize.Level1)
{
    auto parentNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    auto childNode = FrameNode::CreateFrameNode(
        "child", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    parentNode->AddChild(childNode);
    auto thirdGenerationNode = FrameNode::CreateFrameNode(
        "thirdGenerationNode", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    auto stageManager = AceType::MakeRefPtr<StageManager>(parentNode);
    MockPipelineBase::GetCurrent()->stageManager_ = stageManager;

    /**
     * @tc.steps: step1. creat distributedUI and creat parentNode add childNode
     * @tc.expected: step1. call DumpUITree() return SerializeableObjectArray
     */
    DistributedUI distributedUI;
    auto array = distributedUI.DumpUITree();
    EXPECT_EQ(distributedUI.status_, DistributedUI::StateMachine::SOURCE_START);
    EXPECT_FALSE(array.empty());

    /**
     * @tc.steps: step2. childNode add thirdGenerationNode
     * @tc.expected: step2. call DumpUITree() return SerializeableObjectArray
     */
    childNode->AddChild(thirdGenerationNode);
    array = distributedUI.DumpUITree();
    EXPECT_EQ(distributedUI.status_, DistributedUI::StateMachine::SOURCE_START);
    EXPECT_FALSE(array.empty());

    /**
     * @tc.steps: step3. creat fun.
     * @tc.expected: step3. distributedUI.onUpdateCb_ is not null
     */

    std::function<void(int32_t, SerializeableObjectArray&)> fun = [](int32_t num, SerializeableObjectArray& array) {};

    distributedUI.SubscribeUpdate(fun);
    EXPECT_TRUE(distributedUI.onUpdateCb_);
    /**
     * @tc.steps: step4. call UnSubscribeUpdate
     * @tc.expected: step4. distributedUI.onUpdateCb_ is destroy.
     */

    distributedUI.UnSubscribeUpdate();
    EXPECT_FALSE(distributedUI.onUpdateCb_);
    EXPECT_EQ(distributedUI.status_, DistributedUI::StateMachine::STOP);
}

/**
 * @tc.name: DistributedUiTestNg002
 * @tc.desc: DistributedUi of tests
 * @tc.type: FUNC
 */
HWTEST_F(DistributedUiTestNg, DistributedUiTestNg002, TestSize.Level1)
{
    Init();
    /**
     * @tc.steps: step1. creat distributedUI and creat parentNode add childNode
     * @tc.expected: step1. call DumpUITree() return SerializeableObjectArray
     */
    DistributedUI distributedUI;
    auto array = distributedUI.DumpUITree();
    EXPECT_EQ(distributedUI.status_, DistributedUI::StateMachine::SOURCE_START);
    EXPECT_TRUE(!array.empty());

    /**
     * @tc.steps: step2. call AddNode
     * @tc.expected: step2. DistributedUI::StateMachine state determines whether to add nodes
     */
    distributedUI.ProcessSerializeableInputEvent(array);
    distributedUI.AddDeletedNode(0);
    distributedUI.AddNewNode(0);
    distributedUI.AddDirtyCustomNode(0);
    distributedUI.AddDirtyRenderNode(0);
    distributedUI.AddDirtyLayoutNode(0);
    EXPECT_TRUE(distributedUI.deletedNodes_.empty());

    std::function<void(int32_t, SerializeableObjectArray&)> fun = [](int32_t num, SerializeableObjectArray& array) {};
    distributedUI.SubscribeUpdate(fun);
    EXPECT_TRUE(distributedUI.onUpdateCb_);
    distributedUI.AddDeletedNode(0);
    distributedUI.AddNewNode(0);
    distributedUI.AddDirtyCustomNode(0);
    distributedUI.AddDirtyRenderNode(0);
    distributedUI.AddDirtyLayoutNode(0);
    EXPECT_EQ(distributedUI.deletedNodes_.size(), 1);
}

/**
 * @tc.name: DistributedUiTestNg003
 * @tc.desc: DistributedUi of tests
 * @tc.type: FUNC
 */
HWTEST_F(DistributedUiTestNg, DistributedUiTestNg003, TestSize.Level1)
{
    Init();

    /**
     * @tc.steps: step1. creat distributedUI and creat parentNode add childNode
     * @tc.expected: step1. call DumpUITree() return SerializeableObjectArray
     */
    DistributedUI distributedUI;
    auto array = distributedUI.DumpUITree();
    EXPECT_EQ(distributedUI.status_, DistributedUI::StateMachine::SOURCE_START);
    EXPECT_TRUE(!array.empty());

    /**
     * @tc.steps: step2. call OnTreeUpdate.
     * @tc.expected: step2. distributedUI.pageChangeFlag_ change.
     */
    distributedUI.OnTreeUpdate();
    std::function<void(int32_t, SerializeableObjectArray&)> fun = [](int32_t num, SerializeableObjectArray& array) {};
    distributedUI.SubscribeUpdate(fun);
    EXPECT_TRUE(distributedUI.onUpdateCb_);
    distributedUI.OnPageChanged(0);
    EXPECT_TRUE(distributedUI.pageChangeFlag_);
    distributedUI.OnTreeUpdate();
    EXPECT_FALSE(distributedUI.pageChangeFlag_);
    distributedUI.OnTreeUpdate();
    EXPECT_TRUE(distributedUI.onUpdateCb_);

    distributedUI.status_ = DistributedUI::StateMachine::STOP;
    distributedUI.OnPageChanged(distributedUI.GetCurrentPageId());
    EXPECT_FALSE(distributedUI.pageChangeFlag_);
}

/**
 * @tc.name: DistributedUiTestNg004
 * @tc.desc: DistributedUi of tests
 * @tc.type: FUNC
 */
HWTEST_F(DistributedUiTestNg, DistributedUiTestNg004, TestSize.Level1)
{
    Init();
    /**
     * @tc.steps: step1. creat distributedUI and creat parentNode add childNode
     * @tc.expected: step1. call DumpUITree() return SerializeableObjectArray
     */
    DistributedUI distributedUI;
    auto array = distributedUI.DumpUITree();
    EXPECT_EQ(distributedUI.status_, DistributedUI::StateMachine::SOURCE_START);
    EXPECT_TRUE(!array.empty());

    /**
     * @tc.steps: step2. call SubscribeInputEventProcess
     * @tc.expected: step2. creat eventFun and eventFun destroy
     */
    std::function<void(SerializeableObjectArray&)> eventFun = [](SerializeableObjectArray& array) {};
    distributedUI.SubscribeInputEventProcess(eventFun);
    TouchEvent touchEvent;
    distributedUI.BypassEvent(touchEvent, false);
    distributedUI.status_ = DistributedUI::StateMachine::SINK_START;
    EXPECT_TRUE(distributedUI.onEventCb_);
    EXPECT_TRUE(distributedUI.IsSinkMode());
    distributedUI.UnSubscribeInputEventProcess();
    distributedUI.BypassEvent(touchEvent, false);
    EXPECT_FALSE(distributedUI.onEventCb_);
    EXPECT_FALSE(distributedUI.IsSinkMode());
}

/**
 * @tc.name: DistributedUiTestNg005
 * @tc.desc: DistributedUi of tests
 * @tc.type: FUNC
 */
HWTEST_F(DistributedUiTestNg, DistributedUiTestNg005, TestSize.Level1)
{
    auto parentNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    auto childNode = FrameNode::CreateFrameNode(
        "child", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    parentNode->AddChild(childNode);
    auto stageManager = AceType::MakeRefPtr<StageManager>(parentNode);
    MockPipelineBase::GetCurrent()->stageManager_ = stageManager;
    /**
     * @tc.steps: step1. creat distributedUI and creat parentNode add childNode
     * @tc.expected: step1. call DumpUITree() return SerializeableObjectArray
     */
    DistributedUI distributedUI;
    auto array = distributedUI.DumpUITree();
    EXPECT_EQ(distributedUI.status_, DistributedUI::StateMachine::SOURCE_START);
    EXPECT_TRUE(!array.empty());

    /**
     * @tc.steps: step2. call DumpUpdate().
     * @tc.expected: step2. return SerializeableObjectArray is not empty.
     */
    std::function<void(int32_t, SerializeableObjectArray&)> fun = [](int32_t num, SerializeableObjectArray& array) {};
    distributedUI.SubscribeUpdate(fun);
    EXPECT_TRUE(distributedUI.onUpdateCb_);
    distributedUI.AddDeletedNode(parentNode->GetId());
    distributedUI.AddNewNode(parentNode->GetId());
    distributedUI.AddDirtyCustomNode(parentNode->GetId());
    distributedUI.AddDirtyRenderNode(parentNode->GetId());
    distributedUI.AddDirtyLayoutNode(parentNode->GetId());
    distributedUI.AddDeletedNode(100);
    distributedUI.AddNewNode(100);
    distributedUI.AddDirtyCustomNode(100);
    distributedUI.AddDirtyRenderNode(100);
    distributedUI.AddDirtyLayoutNode(100);
    EXPECT_TRUE(distributedUI.IsNewNode(100));
    auto newArray = distributedUI.DumpUpdate();
    EXPECT_TRUE(!newArray.empty());
    distributedUI.ResetDirtyNodes();
    EXPECT_TRUE(distributedUI.newNodes_.empty());
    EXPECT_FALSE(distributedUI.IsNewNode(100));
}
} // namespace OHOS::Ace::NG