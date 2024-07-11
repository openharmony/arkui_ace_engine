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

#include <memory>

#include "gtest/gtest.h"

#include "base/json/json_util.h"

#define protected public
#define private public

#include "base/json/node_object.h"
#include "core/components_ng/base/distributed_ui.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const char DISTRIBUTE_UI_ID[] = "$ID";
const char DISTRIBUTE_UI_DEPTH[] = "$depth";
const char DISTRIBUTE_UI_ATTRS[] = "$attrs";
} // namespace
class DistributedUiTestNg : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        MockPipelineContext::SetUp();
    }
    static void TearDownTestSuite()
    {
        MockPipelineContext::TearDown();
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
    MockPipelineContext::GetCurrent()->stageManager_ = stageManager;
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
    MockPipelineContext::GetCurrent()->stageManager_ = stageManager;

    /**
     * @tc.steps: step1. creat distributedUI and creat parentNode add childNode
     * @tc.expected: step1. call DumpUITree() return SerializeableObjectArray
     */
    DistributedUI distributedUI;
    auto array = distributedUI.DumpUITree();
    EXPECT_EQ(distributedUI.status_, DistributedUI::StateMachine::SOURCE_START);

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

    /**
     * @tc.steps: step2. call AddNode
     * @tc.expected: step2. DistributedUI::StateMachine state determines whether to add nodes
     */
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
    MockPipelineContext::GetCurrent()->stageManager_ = stageManager;
    /**
     * @tc.steps: step1. creat distributedUI and creat parentNode add childNode
     * @tc.expected: step1. call DumpUITree() return SerializeableObjectArray
     */
    DistributedUI distributedUI;
    auto array = distributedUI.DumpUITree();
    EXPECT_EQ(distributedUI.status_, DistributedUI::StateMachine::SOURCE_START);

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

/**
 * @tc.name: DistributedUiTestNg006
 * @tc.desc: DistributedUi of tests
 * @tc.type: FUNC
 */
HWTEST_F(DistributedUiTestNg, DistributedUiTestNg006, TestSize.Level1)
{
    auto parentNode = FrameNode::CreateFrameNode(
        V2::JS_SYNTAX_ITEM_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    auto childNode = FrameNode::CreateFrameNode(
        "child", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    parentNode->AddChild(childNode);
    auto stageManager = AceType::MakeRefPtr<StageManager>(parentNode);
    MockPipelineContext::GetCurrent()->stageManager_ = stageManager;
    /**
     * @tc.steps: step1. creat distributedUI and creat parentNode add childNode
     * @tc.expected: step1. call DumpUITree() return SerializeableObjectArray
     */
    DistributedUI distributedUI;
    auto array = distributedUI.DumpUITree();
    EXPECT_EQ(distributedUI.status_, DistributedUI::StateMachine::SOURCE_START);

    /**
     * @tc.steps: step2. call SetIdMapping
     * @tc.expected: step2. nodeIdMapping_.size() > 0
     */
    int32_t srcNodeId = 0;
    int32_t sinkNodeId = 0;
    distributedUI.SetIdMapping(srcNodeId, sinkNodeId);
    EXPECT_EQ(distributedUI.GetIdMapping(srcNodeId), sinkNodeId);
    /**
     * @tc.steps: step3. call SetIdMapping
     * @tc.expected: step3. set same numerals fix value price
     */
    distributedUI.SetIdMapping(srcNodeId, sinkNodeId + 1);
    EXPECT_EQ(distributedUI.nodeIdMapping_.size(), 1);
    /**
     * @tc.steps: step4. call GetIdMapping
     * @tc.expected: step4. Enter a value that does not exist and return -1
     */
    EXPECT_EQ(distributedUI.GetIdMapping(10), -1);

    /**
     * @tc.steps: step5. call IsRecordHash
     * @tc.expected: step5. Returns false or true to determine whether a value already exists
     */
    distributedUI.AddNodeHash(0, 0);
    EXPECT_FALSE(distributedUI.IsRecordHash(0, 0));
    EXPECT_TRUE(distributedUI.IsRecordHash(10, 0));
    EXPECT_TRUE(distributedUI.IsRecordHash(0, 10));
    EXPECT_TRUE(distributedUI.IsRecordHash(10, 10));

    /**
     * @tc.steps: step6. call IsInCurrentPage
     * @tc.expected: step6. Returns false or true to determine whether a value already exists
     */
    EXPECT_TRUE(distributedUI.IsInCurrentPage(parentNode, 0));
    EXPECT_TRUE(distributedUI.IsInCurrentPage(childNode, 0));
    EXPECT_FALSE(distributedUI.IsInCurrentPage(childNode, 5));
}

/**
 * @tc.name: DistributedUiTestNg007
 * @tc.desc: DistributedUi of tests
 * @tc.type: FUNC
 */
HWTEST_F(DistributedUiTestNg, DistributedUiTestNg007, TestSize.Level1)
{
    auto parentNode = FrameNode::CreateFrameNode(
        V2::JS_SYNTAX_ITEM_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    auto childNode = FrameNode::CreateFrameNode(
        "child", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    parentNode->AddChild(childNode);
    auto stageManager = AceType::MakeRefPtr<StageManager>(parentNode);
    MockPipelineContext::GetCurrent()->stageManager_ = stageManager;

    auto nodeObject = std::make_unique<OHOS::Ace::NodeObject>();
    /**
     * @tc.steps: step1. creat distributedUI and creat parentNode add childNode
     * @tc.expected: step1. call AttachToTree() return SerializeableObjectArray
     */
    DistributedUI distributedUI;
    distributedUI.AttachToTree(parentNode, childNode, nodeObject);
    EXPECT_TRUE(distributedUI.IsInCurrentPage(parentNode, 0));

    nodeObject->Put(DISTRIBUTE_UI_DEPTH, 1);
    distributedUI.AttachToTree(parentNode, childNode, nodeObject);
    EXPECT_TRUE(distributedUI.IsInCurrentPage(parentNode, 0));
}

/**
 * @tc.name: DistributedUiTestNg008
 * @tc.desc: DistributedUi of tests
 * @tc.type: FUNC
 */
HWTEST_F(DistributedUiTestNg, DistributedUiTestNg008, TestSize.Level1)
{
    auto parentNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto parentNode =
        FrameNode::CreateFrameNode(V2::JS_SYNTAX_ITEM_ETS_TAG, parentNodeId, AceType::MakeRefPtr<Pattern>());
    auto childNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto childNode = FrameNode::CreateFrameNode("child", childNodeId, AceType::MakeRefPtr<Pattern>());
    parentNode->AddChild(childNode);
    auto stageManager = AceType::MakeRefPtr<StageManager>(parentNode);
    MockPipelineContext::GetCurrent()->stageManager_ = stageManager;

    auto nodeObject = std::make_unique<OHOS::Ace::NodeObject>();
    nodeObject->Put(DISTRIBUTE_UI_ID, childNodeId);
    /**
     * @tc.steps: step1. creat distributedUI and creat parentNode add childNode
     * @tc.expected: step1. call AttachToTree() return SerializeableObjectArray
     */
    DistributedUI distributedUI;
    distributedUI.DelNode(nodeObject);
    EXPECT_FALSE(parentNode->GetChildren().empty());

    distributedUI.SetIdMapping(childNodeId, childNodeId);
    distributedUI.DelNode(nodeObject);
    EXPECT_TRUE(parentNode->GetChildren().empty());

    distributedUI.DelNode(nodeObject);
    EXPECT_EQ(childNode->GetParent(), nullptr);
}

/**
 * @tc.name: DistributedUiTestNg009
 * @tc.desc: DistributedUi of tests
 * @tc.type: FUNC
 */
HWTEST_F(DistributedUiTestNg, DistributedUiTestNg009, TestSize.Level1)
{
    auto parentNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto parentNode =
        FrameNode::CreateFrameNode(V2::JS_SYNTAX_ITEM_ETS_TAG, parentNodeId, AceType::MakeRefPtr<Pattern>());
    auto childNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto childNode = FrameNode::CreateFrameNode("child", childNodeId, AceType::MakeRefPtr<Pattern>());
    parentNode->AddChild(childNode);
    auto stageManager = AceType::MakeRefPtr<StageManager>(parentNode);
    MockPipelineContext::GetCurrent()->stageManager_ = stageManager;

    auto nodeObject = std::make_unique<OHOS::Ace::NodeObject>();
    nodeObject->Put(DISTRIBUTE_UI_ID, childNodeId);

    auto attrValue = "{padding: 1px}";
    nodeObject->Put(DISTRIBUTE_UI_ATTRS, OHOS::Ace::JsonUtil::ParseJsonString(attrValue));
    /**
     * @tc.steps: step1. creat distributedUI and creat parentNode add childNode
     * @tc.expected: step1. call AttachToTree() return SerializeableObjectArray
     */
    DistributedUI distributedUI;
    distributedUI.ModNode(nodeObject);
    EXPECT_NE(childNode, nullptr);

    distributedUI.SetIdMapping(childNodeId, childNodeId);
    distributedUI.ModNode(nodeObject);
    EXPECT_NE(childNode->GetLayoutProperty()->GetPaddingProperty()->left->calcValue_, "0.0");
}

/**
 * @tc.name: DistributedUiTestNg010
 * @tc.desc: DistributedUi UpdateUITree
 * @tc.type: FUNC
 */
HWTEST_F(DistributedUiTestNg, DistributedUiTestNg010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. statement distributedUI and SerializeableObjectArray
     */
    SerializeableObjectArray array;
    DistributedUI distributedUI;

    /**
     * @tc.steps: step2. call UpdateUITree()
     * @tc.expected: step2. call AttachToTree() and cover branch status_ is INIT
     */
    distributedUI.UpdateUITree(array);
    EXPECT_EQ(distributedUI.status_, DistributedUI::StateMachine::INIT);

    /**
     * @tc.steps: step3. call UpdateUITree()
     * @tc.expected: step3. call AttachToTree() and cover branch status_ is not INIT
     */
    distributedUI.status_ = DistributedUI::StateMachine::SINK_START;
    distributedUI.UpdateUITree(array);
    EXPECT_NE(distributedUI.status_, DistributedUI::StateMachine::INIT);
}

/**
 * @tc.name: DistributedUiTestNg011
 * @tc.desc: DistributedUi UpdateUITree
 * @tc.type: FUNC
 */
HWTEST_F(DistributedUiTestNg, DistributedUiTestNg011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. statement distributedUI and SerializeableObjectArray
     */
    DistributedUI distributedUI;
    distributedUI.ApplyOneUpdate();
    EXPECT_EQ(distributedUI.pendingUpdates_.size() == 0, true);
    SerializeableObjectArray array;
    std::unique_ptr<SerializeableObject> value = std::make_unique<JsonValue>();
    array.push_back(std::move(value));
    distributedUI.RestoreUITree(array);
    distributedUI.UpdateUITree(array);
    EXPECT_EQ(distributedUI.pendingUpdates_.size() == 1, true);
    distributedUI.ApplyOneUpdate();
    EXPECT_EQ(distributedUI.pendingUpdates_.size() == 0, true);
}
} // namespace OHOS::Ace::NG