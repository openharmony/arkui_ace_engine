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

#include <memory>
#include <ostream>
#include <utility>

#include "gtest/gtest.h"

#define protected public
#define private public

#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/log/dump_log.h"
#include "base/log/log_wrapper.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/focus_hub.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/property/property.h"
#include "core/pipeline_ng/pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const RefPtr<FrameNode> TEN0 = FrameNode::CreateFrameNode("zero", 10, AceType::MakeRefPtr<Pattern>(), true);
const RefPtr<FrameNode> ZERO = FrameNode::CreateFrameNode("zero", 0, AceType::MakeRefPtr<Pattern>(), true);
const RefPtr<FrameNode> ONE = FrameNode::CreateFrameNode("one", 1, AceType::MakeRefPtr<Pattern>(), true);
const RefPtr<FrameNode> TWO = FrameNode::CreateFrameNode("two", 2, AceType::MakeRefPtr<Pattern>());
const RefPtr<FrameNode> THREE = FrameNode::CreateFrameNode("three", 3, AceType::MakeRefPtr<Pattern>());
const RefPtr<FrameNode> FOUR = FrameNode::CreateFrameNode("four", 4, AceType::MakeRefPtr<Pattern>());
const RefPtr<FrameNode> FIVE = FrameNode::CreateFrameNode("five", 5, AceType::MakeRefPtr<Pattern>());
const RefPtr<FrameNode> F_ONE = FrameNode::CreateFrameNode("one", 5, AceType::MakeRefPtr<Pattern>());
const int32_t TEST_ID_ONE = 21;
const int32_t TEST_ID_TWO = 22;
} // namespace

class TestNode : public UINode {
    DECLARE_ACE_TYPE(TestNode, UINode);

public:
    static RefPtr<TestNode> CreateTestNode(int32_t nodeId)
    {
        auto spanNode = MakeRefPtr<TestNode>(nodeId);
        return spanNode;
    }

    bool IsAtomicNode() const override
    {
        return true;
    }

    explicit TestNode(int32_t nodeId) : UINode("TestNode", nodeId) {}

    HitTestResult TouchTest(const PointF& globalPoint, const PointF& parentLocalPoint, const PointF& parentRevertPoint,
        TouchRestrict& touchRestrict, TouchTestResult& result, int32_t touchId, ResponseLinkResult& responseLinkResult,
        bool isDispatch = false) override
    {
        return hitTestResult_;
    }

    HitTestResult MouseTest(const PointF& globalPoint, const PointF& parentLocalPoint, MouseTestResult& onMouseResult,
        MouseTestResult& onHoverResult, RefPtr<FrameNode>& hoverNode) override
    {
        return hitTestResult_;
    }

    HitTestResult AxisTest(const PointF &globalPoint, const PointF &parentLocalPoint, const PointF &parentRevertPoint,
        TouchRestrict &touchRestrict, AxisTestResult &axisResult) override
    {
        return hitTestResult_;
    }

    ~TestNode() override = default;

private:
    HitTestResult hitTestResult_;
};

class UINodeTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void UINodeTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void UINodeTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: UINodeTestNg001
 * @tc.desc: Test ui node method
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. AddChild
     * @tc.expected: children_.size = 2
     */
    ONE->AddChild(TWO, 1, false);
    auto testNode = TestNode::CreateTestNode(TEST_ID_ONE);
    auto testNode2 = TestNode::CreateTestNode(TEST_ID_TWO);
    ONE->AddChild(testNode, 1, false);
    ONE->AddChild(testNode, 1, false);
    ONE->AddChild(testNode2, 1, false);
    EXPECT_EQ(ONE->children_.size(), 3);
    /**
     * @tc.steps: step2. remove child three
     */
    auto iter = ONE->RemoveChild(FOUR);
    EXPECT_EQ(iter, ONE->children_.end());
    ONE->RemoveChild(testNode);
    ONE->RemoveChild(testNode2, true);
    /**
     * @tc.steps: step3. remove child two
     * @tc.expected: distance = 0
     */
    auto distance = ONE->RemoveChildAndReturnIndex(TWO);
    EXPECT_EQ(distance, 0);
}

/**
 * @tc.name: UINodeTestNg002
 * @tc.desc: Test ui node method
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg002, TestSize.Level1)
{
    ONE->RemoveChildAtIndex(-1);
    ONE->AddChild(TWO, 1, false);
    /**
     * @tc.steps: step1. RemoveChildAtIndex
     * @tc.expected: children_.size = 0
     */
    ONE->RemoveChildAtIndex(0);
    EXPECT_EQ(ONE->children_.size(), 0);
    /**
     * @tc.steps: step2. GetChildAtIndex
     * @tc.expected: return nullptr
     */
    auto result = ONE->GetChildAtIndex(0);
    EXPECT_EQ(result, nullptr);
    ONE->AddChild(TWO, 1, false);
    auto node = ONE->GetChildAtIndex(0);
    EXPECT_EQ(strcmp(node->GetTag().c_str(), "two"), 0);
}

/**
 * @tc.name: UINodeTestNg003
 * @tc.desc: Test ui node method
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg003, TestSize.Level1)
{
    ONE->AddChild(TWO, 1, false);
    /**
     * @tc.steps: step1. ReplaceChild
     * @tc.expected: size = 2
     */
    ONE->ReplaceChild(nullptr, THREE);
    ONE->ReplaceChild(TWO, FOUR);
    EXPECT_EQ(ONE->children_.size(), 2);
    /**
     * @tc.steps: step2. set TWO's hostPageId_ 1 and Clean
     * @tc.expected: children_ = 0
     */
    TWO->hostPageId_ = 1;
    ONE->MountToParent(TWO, 1, false);
    ONE->Clean();
    EXPECT_EQ(ONE->children_.size(), 0);
}

/**
 * @tc.name: UINodeTestNg004
 * @tc.desc: Test ui node method
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. GetFocusParent
     * @tc.expected: parent is nullptr
     */
    auto frameNode = ONE->GetFocusParent();
    EXPECT_EQ(frameNode, nullptr);
    FocusType focusTypes[3] = { FocusType::SCOPE, FocusType::NODE, FocusType::DISABLE };
    auto parent = FrameNode::CreateFrameNode("parent", 2, AceType::MakeRefPtr<Pattern>());
    RefPtr<FrameNode> frameNodes[3] = { parent, nullptr, nullptr };
    /**
     * @tc.steps: step2. GetFocusParent adjust FocusType
     * @tc.expected: result is parent and nullptr
     */
    for (int i = 0; i < 3; ++i) {
        RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
        auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)), focusTypes[i]);
        parent->focusHub_ = focusHub;
        parent->eventHub_ = eventHub;
        ONE->parent_ = parent;
        auto result = ONE->GetFocusParent();
        EXPECT_EQ(result, frameNodes[i]);
    }
    /**
     * @tc.steps: step3. create test node and try GetFirstFocusHubChild
     * @tc.expected: result is null
     */
    auto testNode = TestNode::CreateTestNode(TEST_ID_ONE);
    EXPECT_EQ(testNode->GetFirstFocusHubChild(), nullptr);
    /**
     * @tc.steps: step4. config node parent and GetFocusParent;
     * @tc.expected: result is null
     */
    ONE->parent_ = testNode;
    testNode->parent_ = parent;
    auto result = ONE->GetFocusParent();
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: UINodeTestNg005
 * @tc.desc: Test ui node method
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. GetFocusChildren
     * @tc.expected: THREE's children size is 2
     */
    std::list<RefPtr<FrameNode>> children;
    RefPtr<EventHub> eventHubTwo = AceType::MakeRefPtr<EventHub>();
    auto focusHubTwo = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHubTwo)), FocusType::NODE);
    RefPtr<EventHub> eventHubFour = AceType::MakeRefPtr<EventHub>();
    auto focusHubFour = AceType::MakeRefPtr<FocusHub>(
        AceType::WeakClaim(AceType::RawPtr(eventHubFour)), FocusType::DISABLE);
    TWO->focusHub_ = focusHubTwo;
    TWO->eventHub_ = eventHubTwo;
    FOUR->focusHub_ = focusHubFour;
    FOUR->eventHub_ = eventHubFour;
    THREE->AddChild(TWO, 1, false);
    THREE->AddChild(FOUR, 1, false);
    THREE->AddChild(TestNode::CreateTestNode(TEST_ID_ONE), 1, false);
    THREE->GetFocusChildren(children);
    EXPECT_EQ(THREE->children_.size(), 3);
    THREE->Clean();
}

/**
 * @tc.name: UINodeTestNg006
 * @tc.desc: Test ui node method
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. AttachToMainTree and DetachFromMainTree
     * @tc.expected: onMainTree_ is false
     */
    bool mainTrees[2] = { true, false };
    TWO->AddChild(THREE, 1, false);
    for (int i = 0; i < 2; ++i) {
        TWO->onMainTree_ = mainTrees[i];
        TWO->AttachToMainTree();
        TWO->DetachFromMainTree();
        EXPECT_FALSE(TWO->onMainTree_);
    }
    TWO->Clean();
}

/**
 * @tc.name: UINodeTestNg007
 * @tc.desc: Test ui node method
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. MovePosition
     * @tc.expected: children_.size is 2
     */
    int32_t slots[4] = { 1, -1, 1, 2 };
    THREE->AddChild(FOUR);
    THREE->AddChild(FIVE);
    TWO->parent_ = THREE;
    for (int i = 0; i < 4; ++i) {
        TWO->MovePosition(slots[i]);
    }
    EXPECT_EQ(THREE->children_.size(), 3);
    THREE->Clean();
}

/**
 * @tc.name: UINodeTestNg008
 * @tc.desc: Test ui node method
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg008, TestSize.Level1)
{
    PropertyChangeFlag FLAG = 1;
    ONE->children_.clear();
    TWO->children_.clear();
    THREE->children_.clear();
    ONE->AddChild(TWO, 1, false);
    ONE->parent_ = THREE;
    ONE->UINode::UpdateLayoutPropertyFlag();
    ONE->UINode::AdjustParentLayoutFlag(FLAG);
    ONE->UINode::MarkNeedSyncRenderTree();
    ONE->UINode::RebuildRenderContextTree();
    ONE->DumpTree(0);
    EXPECT_EQ(ONE->children_.size(), 1);
}

/**
 * @tc.name: UINodeTestNg009
 * @tc.desc: Test ui node method
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. FrameCount and GetChildIndexById
     * @tc.expected: count is 2, pos is 0
     */
    int32_t count = ONE->FrameCount();
    EXPECT_EQ(count, 1);
    int32_t id1 = ONE->GetChildIndexById(4);
    int32_t id2 = ONE->GetChildIndexById(2);
    EXPECT_EQ(id1, -1);
    EXPECT_EQ(id2, 0);
    /**
     * @tc.steps: step2. GetChildFlatIndex
     * @tc.expected: count is 2, pos is 0
     */
    auto pair1 = ONE->GetChildFlatIndex(1);
    EXPECT_EQ(pair1.second, 0);
    auto pair2 = ONE->GetChildFlatIndex(2);
    EXPECT_EQ(pair2.second, 0);
}

/**
 * @tc.name: UINodeTestNg010
 * @tc.desc: Test ui node method
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call the GetChildIndex and set input is null
     * @tc.expected: the return value is -1
     */
    int retIndex = ZERO->GetChildIndex(nullptr);
    EXPECT_EQ(retIndex, -1);
    /**
     * @tc.steps: step2. add one child for ZERO and call GetChildIndex
     * @tc.expected: step2. the return value is 0
     */
    ZERO->AddChild(ONE);
    retIndex = ZERO->GetChildIndex(ONE);
    EXPECT_EQ(retIndex, 0);
    /**
     * @tc.steps: step3. add two child for ZERO and call GetChildIndex
     * @tc.expected: the return value is 1
     */
    ZERO->AddChild(TWO);
    retIndex = ZERO->GetChildIndex(TWO);
    EXPECT_EQ(retIndex, 1);
    /**
     * @tc.steps: step4. add three child for ZERO and call GetChildIndex
     * @tc.expected: the return value is 2
     */
    ZERO->AddChild(THREE);
    retIndex = ZERO->GetChildIndex(THREE);
    EXPECT_EQ(retIndex, 2);
    ZERO->Clean();
}

/**
 * @tc.name: UINodeTestNg011
 * @tc.desc: Test ui node method
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call the MountToParent and set hostPageId_ is 0
     * @tc.expected: step2. mount failure
     */
    ZERO->hostPageId_ = 0;
    ONE->MountToParent(ZERO, 1, false);
    int retPageId = ONE->GetPageId();
    EXPECT_NE(retPageId, 0);
    ONE->Clean();
    /**
     * @tc.steps: step2. call the MountToParent and set hostPageId_ is 0
     * @tc.expected: mount sucess and pageid is 1
     */
    ZERO->hostPageId_ = 1;
    ZERO->SetInDestroying();
    ONE->MountToParent(ZERO, 1, false);
    retPageId = ONE->GetPageId();
    EXPECT_EQ(retPageId, 1);
    ONE->Clean();
    ZERO->Clean();
}

/**
 * @tc.name: UINodeTestNg012
 * @tc.desc: Test ui node method
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call the GetFirstFocusHubChild function
     * @tc.expected: the return value is null
     */
    RefPtr<FocusHub> retFirstFocusHubChild = ZERO->GetFirstFocusHubChild();
    EXPECT_EQ(retFirstFocusHubChild, nullptr);
    /**
     * @tc.steps: step2. call the GetFirstFocusHubChild functionand and set focus type is DISABLE
     * @tc.expected: the return value is null
     */
    RefPtr<EventHub> eventHubZero = AceType::MakeRefPtr<EventHub>();
    auto focusHubZero = AceType::MakeRefPtr<FocusHub>(
        AceType::WeakClaim(AceType::RawPtr(eventHubZero)), FocusType::DISABLE);

    ZERO->focusHub_ = focusHubZero;
    ZERO->eventHub_ = eventHubZero;
    retFirstFocusHubChild = ZERO->GetFirstFocusHubChild();
    EXPECT_EQ(retFirstFocusHubChild, nullptr);
    /**
     * @tc.steps: step3. call the GetFirstFocusHubChild functionand set focus type is NODE
     * @tc.expected: the return focusHub type is NODE
     */
    focusHubZero = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHubZero)), FocusType::NODE);

    ZERO->focusHub_ = focusHubZero;
    ZERO->eventHub_ = eventHubZero;
    retFirstFocusHubChild = ZERO->GetFirstFocusHubChild();
    EXPECT_EQ(retFirstFocusHubChild->GetFocusType(), FocusType::NODE);
    ZERO->Clean();
    /**
     * @tc.steps: step4. call the GetFirstFocusHubChild functionand set focus type is SCOPE
     * @tc.expected: the return focusHub type is SCOPE
     */
    focusHubZero = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHubZero)), FocusType::SCOPE);

    ZERO->focusHub_ = focusHubZero;
    ZERO->eventHub_ = eventHubZero;
    retFirstFocusHubChild = ZERO->GetFirstFocusHubChild();
    EXPECT_EQ(retFirstFocusHubChild->GetFocusType(), FocusType::SCOPE);
    ZERO->Clean();
}

/**
 * @tc.name: UINodeTestNg013
 * @tc.desc: Test ui node method
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. add one child to ZERO and set focus type is NODE
     * @tc.expected: the return focusHub type is NODE
     */
    RefPtr<EventHub> eventHubZero = AceType::MakeRefPtr<EventHub>();
    auto focusHubZero = AceType::MakeRefPtr<FocusHub>(
        AceType::WeakClaim(AceType::RawPtr(eventHubZero)), FocusType::DISABLE);
    RefPtr<EventHub> eventHubOne = AceType::MakeRefPtr<EventHub>();
    auto focusHubOne = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHubOne)), FocusType::NODE);

    ZERO->focusHub_ = focusHubZero;
    ZERO->eventHub_ = eventHubZero;
    ONE->focusHub_ = focusHubOne;
    ONE->eventHub_ = eventHubOne;

    ZERO->AddChild(ONE, 1, false);
    RefPtr<FocusHub> retFirstFocusHubChild = ZERO->GetFirstFocusHubChild();
    EXPECT_EQ(retFirstFocusHubChild->GetFocusType(), FocusType::NODE);
    ZERO->Clean();
    /**
     * @tc.steps: step2. add one child to ZERO and set focus type is DISABLE
     * @tc.expected: the return value is null
     */
    focusHubOne = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHubOne)), FocusType::DISABLE);

    ONE->focusHub_ = focusHubOne;
    ONE->eventHub_ = eventHubOne;
    ZERO->AddChild(ONE, 1, false);
    retFirstFocusHubChild = ZERO->GetFirstFocusHubChild();
    EXPECT_EQ(retFirstFocusHubChild, nullptr);
    ZERO->Clean();
}

/**
 * @tc.name: UINodeTestNg014
 * @tc.desc: Test ui node method
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. add one child to ZERO and set focus type is SCOPE
     * @tc.expected: the return focusHub type is SCOPE
     */
    RefPtr<EventHub> eventHubZero = AceType::MakeRefPtr<EventHub>();
    auto focusHubZero = AceType::MakeRefPtr<FocusHub>(
        AceType::WeakClaim(AceType::RawPtr(eventHubZero)), FocusType::DISABLE);
    RefPtr<EventHub> eventHubOne = AceType::MakeRefPtr<EventHub>();
    auto focusHubOne = AceType::MakeRefPtr<FocusHub>(
        AceType::WeakClaim(AceType::RawPtr(eventHubOne)), FocusType::SCOPE);

    ZERO->focusHub_ = focusHubZero;
    ZERO->eventHub_ = eventHubZero;
    ONE->focusHub_ = focusHubOne;
    ONE->eventHub_ = eventHubOne;

    ZERO->AddChild(ONE, 1, false);
    RefPtr<FocusHub> retFirstFocusHubChild = ZERO->GetFirstFocusHubChild();
    EXPECT_EQ(retFirstFocusHubChild->GetFocusType(), FocusType::SCOPE);
    ZERO->Clean();
    /**
     * @tc.steps: step2. add one child to ZERO and set focus type is DISABLE
     * @tc.expected: the return value is null
     */
    focusHubOne = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHubOne)), FocusType::DISABLE);

    ONE->focusHub_ = focusHubOne;
    ONE->eventHub_ = eventHubOne;
    ZERO->AddChild(ONE, 1, false);
    retFirstFocusHubChild = ZERO->GetFirstFocusHubChild();
    EXPECT_EQ(retFirstFocusHubChild, nullptr);
    ZERO->Clean();
}

/**
 * @tc.name: UINodeTestNg015
 * @tc.desc: Test ui node method
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call the MovePosition and set parent_ is null
     * @tc.expected: parentNode is null
     */
    ZERO->parent_ = nullptr;
    ZERO->MovePosition(1);
    RefPtr<UINode> retParent = ZERO->GetParent();
    EXPECT_EQ(retParent, nullptr);
}

/**
 * @tc.name: UINodeTestNg016
 * @tc.desc: Test ui node method
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set propertyChangeFlag_ is PROPERTY_UPDATE_NORMAL and call the MarkDirtyNode
     * @tc.expected: the MarkDirtyNode function is run ok and children_.size() is 1
     */
    PropertyChangeFlag extraFLAG = PROPERTY_UPDATE_NORMAL;
    ZERO->layoutProperty_->propertyChangeFlag_ = PROPERTY_UPDATE_NORMAL;
    ONE->layoutProperty_->propertyChangeFlag_ = PROPERTY_UPDATE_NORMAL;

    ZERO->AddChild(ONE, 1, false);
    ZERO->UINode::MarkDirtyNode(extraFLAG);
    EXPECT_EQ(ZERO->children_.size(), 1);
    ZERO->Clean();
    /**
     * @tc.steps: step2. set propertyChangeFlag_ is PROPERTY_UPDATE_MEASURE and call the MarkDirtyNode
     * @tc.expected: the MarkDirtyNode function is run ok and children_.size() is 1
     */
    extraFLAG = PROPERTY_UPDATE_MEASURE;
    ZERO->layoutProperty_->propertyChangeFlag_ = PROPERTY_UPDATE_MEASURE;
    ONE->layoutProperty_->propertyChangeFlag_ = PROPERTY_UPDATE_MEASURE;
    ZERO->AddChild(ONE, 1, false);
    ZERO->UINode::MarkDirtyNode(extraFLAG);
    EXPECT_EQ(ZERO->children_.size(), 1);
    ZERO->Clean();
    /**
     * @tc.steps: step3. set propertyChangeFlag_ is PROPERTY_UPDATE_LAYOUT and call the MarkDirtyNode
     * @tc.expected: the MarkDirtyNode function is run ok and children_.size() is 1
     */
    extraFLAG = PROPERTY_UPDATE_LAYOUT;
    ZERO->layoutProperty_->propertyChangeFlag_ = PROPERTY_UPDATE_LAYOUT;
    ONE->layoutProperty_->propertyChangeFlag_ = PROPERTY_UPDATE_LAYOUT;
    ZERO->AddChild(ONE, 1, false);
    ZERO->UINode::MarkDirtyNode(extraFLAG);
    EXPECT_EQ(ZERO->children_.size(), 1);
    ZERO->Clean();
}

/**
 * @tc.name: UINodeTestNg017
 * @tc.desc: Test ui node method
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set propertyChangeFlag_ is PROPERTY_UPDATE_NORMAL and call the MarkNeedFrameFlushDirty
     * @tc.expected: the MarkNeedFrameFlushDirty function is run ok
     */
    PropertyChangeFlag extraFLAG = PROPERTY_UPDATE_NORMAL;
    ZERO->layoutProperty_->propertyChangeFlag_ = PROPERTY_UPDATE_NORMAL;
    ONE->layoutProperty_->propertyChangeFlag_ = PROPERTY_UPDATE_NORMAL;

    ZERO->UINode::MarkNeedFrameFlushDirty(extraFLAG);
    EXPECT_EQ(ZERO->parent_.Upgrade(), nullptr);
    /**
     * @tc.steps: step2. set one parent_ for ONE and call the MarkNeedFrameFlushDirty
     * @tc.expected: the MarkNeedFrameFlushDirty function is run ok and parent_ is not null
     */
    ZERO->parent_ = ONE;
    ZERO->UINode::MarkNeedFrameFlushDirty(extraFLAG);
    ASSERT_NE(ZERO->parent_.Upgrade(), nullptr);
    ZERO->Clean();
    ZERO->parent_.Reset();
    /**
     * @tc.steps: step3. set propertyChangeFlag_ is PROPERTY_UPDATE_MEASURE and call the MarkNeedFrameFlushDirty
     * @tc.expected: the MarkNeedFrameFlushDirty function is run ok
     */
    extraFLAG = PROPERTY_UPDATE_MEASURE;
    ZERO->layoutProperty_->propertyChangeFlag_ = PROPERTY_UPDATE_MEASURE;
    ONE->layoutProperty_->propertyChangeFlag_ = PROPERTY_UPDATE_MEASURE;

    ZERO->UINode::MarkNeedFrameFlushDirty(extraFLAG);
    EXPECT_EQ(ZERO->parent_.Upgrade(), nullptr);
    /**
     * @tc.steps: step4. set one parent_ for ONE and call the MarkNeedFrameFlushDirty
     * @tc.expected: the MarkNeedFrameFlushDirty function is run ok and parent_ is not null
     */
    ZERO->parent_ = ONE;
    ZERO->UINode::MarkNeedFrameFlushDirty(extraFLAG);
    ASSERT_NE(ZERO->parent_.Upgrade(), nullptr);
    ZERO->Clean();
    ZERO->parent_.Reset();
    /**
     * @tc.steps: step5. set propertyChangeFlag_ is PROPERTY_UPDATE_LAYOUT and call the MarkNeedFrameFlushDirty
     * @tc.expected: the MarkNeedFrameFlushDirty function is run ok
     */
    extraFLAG = PROPERTY_UPDATE_LAYOUT;
    ZERO->layoutProperty_->propertyChangeFlag_ = PROPERTY_UPDATE_LAYOUT;
    ONE->layoutProperty_->propertyChangeFlag_ = PROPERTY_UPDATE_LAYOUT;

    ZERO->UINode::MarkNeedFrameFlushDirty(extraFLAG);
    EXPECT_EQ(ZERO->parent_.Upgrade(), nullptr);
    /**
     * @tc.steps: step6. set one parent_ for ONE and call the MarkNeedFrameFlushDirty
     * @tc.expected: the MarkNeedFrameFlushDirty function is run ok and parent_ is not null
     */
    ZERO->parent_ = ONE;
    ZERO->UINode::MarkNeedFrameFlushDirty(extraFLAG);
    ASSERT_NE(ZERO->parent_.Upgrade(), nullptr);
    ZERO->Clean();
    ZERO->parent_.Reset();
}

/**
 * @tc.name: UINodeTestNg018
 * @tc.desc: Test ui node method
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set ZERO->parent_ is null and call MarkNeedSyncRenderTree
     * @tc.expected: the MarkNeedSyncRenderTree function is run ok
     */
    ZERO->UINode::MarkNeedSyncRenderTree();
    EXPECT_EQ(ZERO->parent_.Upgrade(), nullptr);
    /**
     * @tc.steps: step2. set ZERO->parent_ is null and call RebuildRenderContextTree
     * @tc.expected: the RebuildRenderContextTree function is run ok
     */
    ZERO->UINode::RebuildRenderContextTree();
    EXPECT_EQ(ZERO->parent_.Upgrade(), nullptr);
}

/**
 * @tc.name: UINodeTestNg019
 * @tc.desc: Test ui node method
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call the DetachFromMainTree
     * @tc.expected: onMainTree_ is false
     */
    bool mainTree = true;
    ZERO->onMainTree_ = mainTree;
    ZERO->DetachFromMainTree();
    EXPECT_FALSE(ZERO->onMainTree_);
    ZERO->Clean();
    ZERO->UINode::OnDetachFromMainTree();
}

/**
 * @tc.name: UINodeTestNg020
 * @tc.desc: Test ui node method
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. add one child for ZERO and call AdjustLayoutWrapperTree
     * @tc.expected: children_.size is 1 and the AdjustLayoutWrapperTree function is run ok
     */
    ZERO->AddChild(ONE, 1, false);
    RefPtr<LayoutWrapperNode> retLayoutWrapper = ZERO->UINode::CreateLayoutWrapper(true, true);
    ZERO->UINode::AdjustLayoutWrapperTree(retLayoutWrapper, true, true);
    EXPECT_EQ(ZERO->children_.size(), 1);
    ZERO->Clean();
}

/**
 * @tc.name: UINodeTestNg021
 * @tc.desc: Test ui node method
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. add one child for ZERO and call GenerateOneDepthVisibleFrame
     * @tc.expected: children_.size is 1 and the GenerateOneDepthVisibleFrame function is run ok
     */
    std::list<RefPtr<FrameNode>> visibleList;

    ZERO->AddChild(ONE, 1, false);
    ZERO->GenerateOneDepthVisibleFrame(visibleList);
    EXPECT_EQ(ZERO->children_.size(), 1);
    ZERO->Clean();
}

/**
 * @tc.name: UINodeTestNg022
 * @tc.desc: Test ui node method
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. add one child for ZERO and call GenerateOneDepthAllFrame
     * @tc.expected: children_.size is 1 and the GenerateOneDepthAllFrame function is run ok
     */
    std::list<RefPtr<FrameNode>> visibleList;

    ZERO->AddChild(ONE, 1, false);
    ZERO->GenerateOneDepthAllFrame(visibleList);
    EXPECT_EQ(ZERO->children_.size(), 1);
    ZERO->Clean();
}

/**
 * @tc.name: UINodeTestNg023
 * @tc.desc: Test ui node method
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg023, TestSize.Level1)
{
    /**
     * @tc.steps: step1. add one child for ZERO and call TouchTest
     * @tc.expected: the return value is meetings expectations
     */
    TouchTestResult result;
    ResponseLinkResult responseLinkResult;
    TouchRestrict restrict;
    const PointF GLOBAL_POINT { 20.0f, 20.0f };
    const PointF LOCAL_POINT { 15.0f, 15.0f };
    auto testNode = TestNode::CreateTestNode(TEST_ID_ONE);
    ZERO->AddChild(testNode, 1, false);
    HitTestResult retResult =
        ZERO->UINode::TouchTest(GLOBAL_POINT, LOCAL_POINT, LOCAL_POINT, restrict, result, 1, responseLinkResult);
    EXPECT_EQ(retResult, HitTestResult::OUT_OF_REGION);
    testNode->hitTestResult_ = HitTestResult::STOP_BUBBLING;
    retResult =
        ZERO->UINode::TouchTest(GLOBAL_POINT, LOCAL_POINT, LOCAL_POINT, restrict, result, 1, responseLinkResult);
    EXPECT_EQ(retResult, HitTestResult::STOP_BUBBLING);
    testNode->hitTestResult_ = HitTestResult::BUBBLING;
    retResult =
        ZERO->UINode::TouchTest(GLOBAL_POINT, LOCAL_POINT, LOCAL_POINT, restrict, result, 1, responseLinkResult);
    EXPECT_EQ(retResult, HitTestResult::BUBBLING);
    ZERO->Clean();
}

/**
 * @tc.name: UINodeTestNg026
 * @tc.desc: Test ui node method
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg026, TestSize.Level1)
{
    /**
     * @tc.steps: step1. add one child for ZERO and call TotalChildCount
     * @tc.expected: the return retCount is 1
     */
    ZERO->AddChild(ONE, 1, false);
    int32_t retCount = ZERO->UINode::FrameCount();
    EXPECT_EQ(retCount, 1);
    /**
     * @tc.steps: step2. add two child for ZERO and call TotalChildCount
     * @tc.expected: the return retCount is 2
     */
    ZERO->AddChild(TWO, 2, false);
    retCount = ZERO->TotalChildCount();
    EXPECT_EQ(retCount, 2);
    /**
     * @tc.steps: step3. add three child for ZERO and call TotalChildCount
     * @tc.expected: the return retCount is 3
     */
    ZERO->AddChild(THREE, 3, false);
    retCount = ZERO->TotalChildCount();
    EXPECT_EQ(retCount, 3);
    /**
     * @tc.steps: step4. add four child for ZERO and call TotalChildCount
     * @tc.expected: the return retCount is 4
     */
    ZERO->AddChild(FOUR, 4, false);
    retCount = ZERO->TotalChildCount();
    EXPECT_EQ(retCount, 4);
    ZERO->Clean();
    /**
     * @tc.steps: step5. clean ZERO's child and TotalChildCount
     * @tc.expected: the return retCount is 0
     */
    retCount = ZERO->TotalChildCount();
    EXPECT_EQ(retCount, 0);
}

/**
 * @tc.name: UINodeTestNg027
 * @tc.desc: Test ui node method
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg027, TestSize.Level1)
{
    /**
     * @tc.steps: step1. add one child for ZERO and call Build
     * @tc.expected: the Build function is run ok
     */
    ZERO->AddChild(ONE, 1, false);
    ZERO->Build(nullptr);
    EXPECT_EQ(ZERO->children_.size(), 1);
    ZERO->Clean();
}

/**
 * @tc.name: UINodeTestNg028
 * @tc.desc: Test ui node method
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg028, TestSize.Level1)
{
    /**
     * @tc.steps: step1. add one child for ZERO and call SetActive
     * @tc.expected: the SetActive function is run ok
     */
    ZERO->AddChild(ONE, 1, false);
    ZERO->UINode::SetActive(true);
    EXPECT_EQ(ZERO->children_.size(), 1);
    ZERO->Clean();
}

/**
 * @tc.name: UINodeTestNg029
 * @tc.desc: Test ui node method
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg029, TestSize.Level1)
{
    /**
     * @tc.steps: step1. add one child for ZERO and call TryVisibleChangeOnDescendant
     * @tc.expected: the TryVisibleChangeOnDescendant function is run ok
     */
    ZERO->AddChild(ONE, 1, false);
    ZERO->UINode::TryVisibleChangeOnDescendant(VisibleType::INVISIBLE, VisibleType::VISIBLE);
    EXPECT_EQ(ZERO->children_.size(), 1);
    ZERO->Clean();
}

/**
 * @tc.name: UINodeTestNg030
 * @tc.desc: Test ui node method
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg030, TestSize.Level1)
{
    /**
     * @tc.steps: step1. add ONE child for ZERO and call GetChildFlatIndex
     * @tc.expected: pair1.second is 0
     */
    ZERO->AddChild(ONE, 1, false);
    auto pair = ZERO->GetChildFlatIndex(1);
    EXPECT_TRUE(pair.first);
    EXPECT_EQ(pair.second, 0);
    ZERO->Clean();
    /**
     * @tc.steps: step1. AddChild TESTUINode to ZERO and GetChildFlatIndex
     * @tc.expected: the return pair1.first is false and pair1.second is 1
     */
    ZERO->AddChild(TEN0, 1, false);
    pair = ZERO->GetChildFlatIndex(10);
    EXPECT_FALSE(pair.first);
    EXPECT_EQ(pair.second, 1);
    ZERO->Clean();
}

/**
 * @tc.name: UINodeTestNg031
 * @tc.desc: Test ui node method
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg031, TestSize.Level1)
{
    /**
     * @tc.steps: step1. add one child to ZERO and ChildrenUpdatedFrom
     * @tc.expected: childrenUpdatedFrom_ is 1
     */
    ZERO->ChildrenUpdatedFrom(1);
    EXPECT_EQ(ZERO->childrenUpdatedFrom_, 1);
    ZERO->Clean();
}

/**
 * @tc.name: UINodeTestNg032
 * @tc.desc: Test ui node method
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg032, TestSize.Level1)
{
    /**
     * @tc.steps: step1. add one child to ZERO and MarkRemoving
     * @tc.expected: the return retMark is false
     */
    ZERO->AddChild(ONE, 1, false);
    bool retMark = ZERO->UINode::MarkRemoving();
    EXPECT_FALSE(retMark);
    ZERO->Clean();
}

/**
 * @tc.name: UINodeTestNg033
 * @tc.desc: Test ui node method
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg033, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call the SetChildrenInDestroying
     * @tc.expected: children_.size = 0
     */
    ZERO->SetChildrenInDestroying();
    EXPECT_EQ(ZERO->children_.size(), 0);
    ZERO->Clean();
    /**
     * @tc.steps: step1. add two child to ZERO and call SetChildrenInDestroying
     * @tc.expected: step1. children_.size = 3
     */
    ZERO->AddChild(ONE, 1, false);
    ZERO->AddChild(TWO, 2, false);
    ZERO->children_.emplace_back(nullptr);
    ZERO->SetChildrenInDestroying();
    EXPECT_EQ(ZERO->children_.size(), 3);
    ZERO->children_.clear();
    ZERO->Clean();
}

/**
 * @tc.name: UINodeTestNg034
 * @tc.desc: Test ui node method
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg034, TestSize.Level1)
{
    /**
     * @tc.steps: step1. add two child to ZERO and call RemoveChildAtIndex
     * @tc.expected: children_.size = 1
     */
    ZERO->AddChild(ONE, 1, false);
    ZERO->RemoveChildAtIndex(1);
    EXPECT_EQ(ZERO->children_.size(), 1);
    ZERO->Clean();
}

/**
 * @tc.name: UINodeTestNg035
 * @tc.desc: Test ui node method
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg035, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call the AddChild funtion and set child is null
     * @tc.expected: children_.size = 0
     */
    ZERO->AddChild(nullptr, 1, false);
    EXPECT_EQ(ZERO->children_.size(), 0);
    /**
     * @tc.steps: step2. AddChild
     * @tc.expected: children_.size = 1
     */
    ZERO->AddChild(TWO, 1, false);
    EXPECT_EQ(ZERO->children_.size(), 1);
    /**
     * @tc.steps: step3. call the RemoveChild funtion and set input is null
     * @tc.expected: the return value is children_.end()
     */
    auto interator = ZERO->RemoveChild(nullptr);
    EXPECT_EQ(interator, ZERO->children_.end());
    ZERO->Clean();
}

/**
 * @tc.name: UINodeTestNg036
 * @tc.desc: Test ui node method
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg036, TestSize.Level1)
{
    /**
     * @tc.steps: step1. GetChildAtIndex and set input is -1
     * @tc.expected: the return value is return nullptr
     */
    RefPtr<UINode> retChildAtIndex = ZERO->GetChildAtIndex(-1);
    EXPECT_EQ(retChildAtIndex, nullptr);
}

/**
 * @tc.name: UINodeTestNg037
 * @tc.desc: Test ui node method
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg037, TestSize.Level1)
{
    /**
     * @tc.steps: step1. ReplaceChild
     * @tc.expected: children_.size() is 0
     */
    ZERO->ReplaceChild(nullptr, nullptr);
    EXPECT_EQ(ZERO->children_.size(), 0);
}

/**
 * @tc.name: UINodeTestNg038
 * @tc.desc: Test ui node method
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg038, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call the MarkDirtyNode.
     * @tc.expected: the MarkDirtyNode function is run ok.
     */
    PropertyChangeFlag FLAG = PROPERTY_UPDATE_NORMAL;
    ZERO->layoutProperty_->propertyChangeFlag_ = PROPERTY_UPDATE_NORMAL;
    ONE->layoutProperty_->propertyChangeFlag_ = PROPERTY_UPDATE_NORMAL;
    TWO->layoutProperty_->propertyChangeFlag_ = PROPERTY_UPDATE_NORMAL;

    ONE->parent_ = ZERO;
    TWO->parent_ = ONE;
    ZERO->MarkNeedFrameFlushDirty(FLAG);
    EXPECT_NE(ONE->parent_.Upgrade(), nullptr);
    EXPECT_NE(TWO->parent_.Upgrade(), nullptr);
    ZERO->Clean();
}

/**
 * @tc.name: UINodeTestNg039
 * @tc.desc: Test ui node method
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg039, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call the CreateLayoutWrapper
     * @tc.expected: the return value is null
     */
    RefPtr<LayoutWrapperNode> retLayoutWrapper = ZERO->UINode::CreateLayoutWrapper(true, true);
    EXPECT_EQ(retLayoutWrapper, nullptr);
    /**
     * @tc.steps: step2. add one child for ZERO and call CreateLayoutWrapper
     * @tc.expected: the return value is null
     */
    auto testNode = TestNode::CreateTestNode(TEST_ID_ONE);
    ZERO->AddChild(testNode, 1, false);
    retLayoutWrapper = ZERO->UINode::CreateLayoutWrapper(true, true);
    testNode->AddChild(ONE, 1, false);
    retLayoutWrapper = ZERO->UINode::CreateLayoutWrapper(true, true);
    EXPECT_NE(retLayoutWrapper, nullptr);
    ZERO->Clean();
}

/**
 * @tc.name: UINodeTestNg040
 * @tc.desc: Test ui node method
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg040, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set onMainTree_ is true and call AddChild
     * @tc.expected: children_.size() is 2
     */
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    auto it = std::find(ZERO->children_.begin(), ZERO->children_.end(), ZERO);
    ZERO->onMainTree_ = true;
    ZERO->context_ = AceType::RawPtr(context);
    ZERO->DoAddChild(it, ONE, false);
    ZERO->DoAddChild(it, TWO, true);
    EXPECT_EQ(ZERO->children_.size(), 2);
    ZERO->onMainTree_ = false;
    ZERO->context_ = nullptr;
}

/**
 * @tc.name: UINodeTestNg042
 * @tc.desc: Test ui node method
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg042, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create some node
     */
    auto parent = FrameNode::CreateFrameNode(V2::COMMON_VIEW_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>(), true);
    auto child = FrameNode::CreateFrameNode(V2::COMMON_VIEW_ETS_TAG, 3, AceType::MakeRefPtr<Pattern>());
    auto child2 = FrameNode::CreateFrameNode(V2::COMMON_VIEW_ETS_TAG, 4, AceType::MakeRefPtr<Pattern>());
    /**
     * @tc.steps: step2. call AddDisappearingChild with different condition
     * @tc.expected: disappearingChildren_.size() is 2
     */
    parent->AddDisappearingChild(child);
    child2->isDisappearing_ = true;
    parent->AddDisappearingChild(child2);
    parent->AddDisappearingChild(child);
    EXPECT_EQ(parent->disappearingChildren_.size(), 2);
    /**
     * @tc.steps: step3. call RemoveDisappearingChild with different condition
     * @tc.expected: disappearingChildren_.size() is 1
     */
    parent->RemoveDisappearingChild(child);
    child->isDisappearing_ = true;
    parent->RemoveDisappearingChild(child);
    EXPECT_EQ(parent->disappearingChildren_.size(), 1);
}

/**
 * @tc.name: UINodeTestNg043
 * @tc.desc: Test ui node method
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg043, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create some node
     */
    auto parent = FrameNode::CreateFrameNode("parent", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto child = FrameNode::CreateFrameNode("child", 3, AceType::MakeRefPtr<Pattern>());
    parent->AddChild(child);
    /**
     * @tc.steps: step2. call GetFrameChildByIndex
     * @tc.expected: return nullptr
     */

    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize.SetWidth(0);
    parentLayoutConstraint.maxSize.SetHeight(0);
    PerformanceCheckNodeMap un_Map;
    un_Map.emplace(0, PerformanceCheckNode());
    parent->UINode::OnSetCacheCount(3, parentLayoutConstraint);
    parent->UINode::DoRemoveChildInRenderTree(0, true);
    parent->UINode::DoRemoveChildInRenderTree(0, false);
    parent->UINode::DoRemoveChildInRenderTree(5, false);
    parent->UINode::GetFrameChildByIndex(0, false);
    EXPECT_FALSE(parent->UINode::GetDisappearingChildById("", 0));
    EXPECT_FALSE(parent->UINode::GetFrameChildByIndex(5, false));
}

/**
 * @tc.name: UINodeTestNg044
 * @tc.desc: Test ui node method of instanceid
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg044, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a uinode
     */
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    auto testNode = TestNode::CreateTestNode(TEST_ID_ONE);
    ASSERT_NE(testNode, nullptr);

    int32_t testId = 0;
    testNode->RegisterUpdateJSInstanceCallback([&testId](int32_t newId) { testId = newId; });

    /**
     * @tc.steps: step2. attach context
     */
    testNode->AttachContext(AceType::RawPtr(context), true);
    EXPECT_EQ(testNode->context_, AceType::RawPtr(context));
    EXPECT_EQ(testNode->instanceId_, context->GetInstanceId());
    EXPECT_EQ(testId, context->GetInstanceId());

    /**
     * @tc.steps: step3. detach context
     */
    testNode->DetachContext(true);
    EXPECT_EQ(testNode->context_, nullptr);
}

/**
 * @tc.name: GetCurrentCustomNodeInfo001
 * @tc.desc: Test ui node method GetCurrentCustomNodeInfo
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, GetCurrentCustomNodeInfo001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto parentId = ElementRegister::GetInstance()->MakeUniqueId();
    auto childId = ElementRegister::GetInstance()->MakeUniqueId();
    auto parent = FrameNode::CreateFrameNode("parent_test", parentId, AceType::MakeRefPtr<Pattern>(), true);
    auto child = FrameNode::CreateFrameNode("child_test", childId, AceType::MakeRefPtr<Pattern>());
    parent->AddChild(child);

    /**
     * @tc.steps: step2. call GetCurrentCustomNodeInfo
     * @tc.expected: return ""
     */
    std::string rusult = parent->UINode::GetCurrentCustomNodeInfo();
    EXPECT_EQ(rusult, "");
}

/**
 * @tc.name: GetCurrentCustomNodeInfo002
 * @tc.desc: Test ui node method GetCurrentCustomNodeInfo
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, GetCurrentCustomNodeInfo002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create custome node
     */
    auto parentId = ElementRegister::GetInstance()->MakeUniqueId();
    auto childId = ElementRegister::GetInstance()->MakeUniqueId();
    auto childTwoId = ElementRegister::GetInstance()->MakeUniqueId();
    auto parent = CustomNode::CreateCustomNode(parentId, "parent");
    auto child = CustomNode::CreateCustomNode(childId, "child");
    auto childTwo = CustomNode::CreateCustomNode(childTwoId, "child_two");
    parent->AddChild(child);
    parent->AddChild(childTwo);

    /**
     * @tc.steps: step2. cover branch parent is custome and call GetCurrentCustomNodeInfo
     * @tc.expected: return ""
     */
    std::string rusult = parent->UINode::GetCurrentCustomNodeInfo();
    EXPECT_EQ(rusult, "");
}

/**
 * @tc.name: GetPerformanceCheckData001
 * @tc.desc: Test ui node method GetCurrentCustomNodeInfo
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, GetPerformanceCheckData001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto parentId = ElementRegister::GetInstance()->MakeUniqueId();
    auto parent = FrameNode::CreateFrameNode("parent", parentId, AceType::MakeRefPtr<Pattern>(), true);
    parent->tag_ = V2::COMMON_VIEW_ETS_TAG;
    parent->nodeInfo_ = std::make_unique<PerformanceCheckNode>();

    /**
     * @tc.steps: step2. construct parameter performanceCheckNodeMap and call GetPerformanceCheckData
     * @tc.expected: isBuildByJS_ is false
     */
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    PerformanceCheckNodeMap nodeMap;
    PerformanceCheckNode performanceCheckNode = PerformanceCheckNode();
    nodeMap.emplace(nodeId, performanceCheckNode);

    parent->UINode::GetPerformanceCheckData(nodeMap);
    EXPECT_FALSE(parent->isBuildByJS_);

    /**
     * @tc.steps: step3. change parent tag_ and call GetPerformanceCheckData
     * @tc.expected: isBuildByJS_ is true
     */
    parent->tag_ = V2::MENU_ETS_TAG;
    parent->SetBuildByJs(true);
    parent->UINode::GetPerformanceCheckData(nodeMap);
    EXPECT_TRUE(parent->isBuildByJS_);
}

/**
 * @tc.name: GetPerformanceCheckData002
 * @tc.desc: Test ui node method GetCurrentCustomNodeInfo
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, GetPerformanceCheckData002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create parent and childframe node
     */
    auto parentId = ElementRegister::GetInstance()->MakeUniqueId();
    auto childId = ElementRegister::GetInstance()->MakeUniqueId();
    auto parent = FrameNode::CreateFrameNode("parent", parentId, AceType::MakeRefPtr<Pattern>(), true);
    auto child = FrameNode::CreateFrameNode("child", childId, AceType::MakeRefPtr<Pattern>(), true);

    parent->tag_ = V2::JS_FOR_EACH_ETS_TAG;
    parent->nodeInfo_ = std::make_unique<PerformanceCheckNode>();
    child->tag_ = V2::COMMON_VIEW_ETS_TAG;
    child->nodeInfo_ = std::make_unique<PerformanceCheckNode>();
    parent->AddChild(child);

    /**
     * @tc.steps: step2.  construct parameter performanceCheckNodeMap and call GetPerformanceCheckData
     * @tc.expected: isBuildByJS_ is false
     */
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    PerformanceCheckNodeMap nodeMap;
    PerformanceCheckNode performanceCheckNode = PerformanceCheckNode();
    nodeMap.emplace(nodeId, performanceCheckNode);

    parent->UINode::GetPerformanceCheckData(nodeMap);
    EXPECT_FALSE(parent->isBuildByJS_);

    /**
     * @tc.steps: step3. change child tag_ and call GetPerformanceCheckData
     * @tc.expected: isBuildByJS_ is false
     */
    child->tag_ = V2::JS_FOR_EACH_ETS_TAG;
    parent->UINode::GetPerformanceCheckData(nodeMap);
    EXPECT_FALSE(parent->isBuildByJS_);
}

/**
 * @tc.name: GetPerformanceCheckData003
 * @tc.desc: Test ui node method GetCurrentCustomNodeInfo
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, GetPerformanceCheckData003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto parentId = ElementRegister::GetInstance()->MakeUniqueId();
    auto childId = ElementRegister::GetInstance()->MakeUniqueId();
    auto childTwoId = ElementRegister::GetInstance()->MakeUniqueId();
    auto parent = FrameNode::CreateFrameNode("parent", parentId, AceType::MakeRefPtr<Pattern>(), true);
    auto child = FrameNode::CreateFrameNode("child", childId, AceType::MakeRefPtr<Pattern>(), true);
    auto childTwo = FrameNode::CreateFrameNode("childTwo", childTwoId, AceType::MakeRefPtr<Pattern>(), true);
    parent->tag_ = V2::JS_FOR_EACH_ETS_TAG;
    parent->nodeInfo_ = std::make_unique<PerformanceCheckNode>();
    child->tag_ = V2::COMMON_VIEW_ETS_TAG;
    child->nodeInfo_ = std::make_unique<PerformanceCheckNode>();
    childTwo->tag_ = V2::COMMON_VIEW_ETS_TAG;
    childTwo->nodeInfo_ = std::make_unique<PerformanceCheckNode>();
    parent->AddChild(child);
    parent->AddChild(childTwo);

    /**
     * @tc.steps: step2.  construct parameter performanceCheckNodeMap and call GetPerformanceCheckData
     * @tc.expected: isBuildByJS_ is false
     */
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    PerformanceCheckNodeMap nodeMap;
    PerformanceCheckNode performanceCheckNode = PerformanceCheckNode();
    nodeMap.emplace(nodeId, performanceCheckNode);

    parent->UINode::GetPerformanceCheckData(nodeMap);
    EXPECT_FALSE(parent->isBuildByJS_);

    /**
     * @tc.steps: step3. change child tag_ and call GetPerformanceCheckData
     * @tc.expected: isBuildByJS_ is false
     */
    child->tag_ = V2::JS_FOR_EACH_ETS_TAG;
    parent->UINode::GetPerformanceCheckData(nodeMap);
    EXPECT_FALSE(parent->isBuildByJS_);
}

/**
 * @tc.name: UpdateConfigurationUpdate001
 * @tc.desc: Test ui node method UpdateConfigurationUpdate
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UpdateConfigurationUpdate001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto parentId = ElementRegister::GetInstance()->MakeUniqueId();
    auto parent = FrameNode::CreateFrameNode("parent", parentId, AceType::MakeRefPtr<Pattern>(), true);
    parent->tag_ = V2::COMMON_VIEW_ETS_TAG;
    parent->nodeInfo_ = std::make_unique<PerformanceCheckNode>();

    /**
     * @tc.steps: step2.  construct parameter configurationChange and call UpdateConfigurationUpdate
     * @tc.expected: cover branch needCallChildrenUpdate_ is true
     */
    ConfigurationChange configurationChange;
    parent->UINode::UpdateConfigurationUpdate(configurationChange);
    EXPECT_TRUE(parent->needCallChildrenUpdate_);

    /**
     * @tc.steps: step3. create child frame node and call UpdateConfigurationUpdate
     * @tc.expected: cover branch children is not empty
     */
    auto childId = ElementRegister::GetInstance()->MakeUniqueId();
    auto childTwoId = ElementRegister::GetInstance()->MakeUniqueId();
    auto child = FrameNode::CreateFrameNode("child", childId, AceType::MakeRefPtr<Pattern>(), true);
    auto childTwo = FrameNode::CreateFrameNode("childTwo", childTwoId, AceType::MakeRefPtr<Pattern>(), true);
    child->tag_ = V2::COMMON_VIEW_ETS_TAG;
    child->nodeInfo_ = std::make_unique<PerformanceCheckNode>();
    childTwo->tag_ = V2::COMMON_VIEW_ETS_TAG;
    childTwo->nodeInfo_ = std::make_unique<PerformanceCheckNode>();
    parent->AddChild(child);
    parent->AddChild(childTwo);
    parent->UINode::UpdateConfigurationUpdate(configurationChange);
    EXPECT_TRUE(parent->needCallChildrenUpdate_);

    /**
     * @tc.steps: step4. set needCallChildrenUpdate_ and call UpdateConfigurationUpdate
     * @tc.expected: cover branch needCallChildrenUpdate_ is false
     */
    parent->SetNeedCallChildrenUpdate(false);
    parent->UINode::UpdateConfigurationUpdate(configurationChange);
    EXPECT_FALSE(parent->needCallChildrenUpdate_);
}

/**
 * @tc.name: DumpTreeById001
 * @tc.desc: Test ui node method DumpTreeById
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, DumpTreeById001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto parentId = ElementRegister::GetInstance()->MakeUniqueId();
    auto childId = ElementRegister::GetInstance()->MakeUniqueId();
    auto parent = FrameNode::CreateFrameNode("parent", parentId, AceType::MakeRefPtr<Pattern>(), true);
    auto child = FrameNode::CreateFrameNode("child", childId, AceType::MakeRefPtr<Pattern>(), true);

    parent->tag_ = V2::JS_FOR_EACH_ETS_TAG;
    parent->nodeInfo_ = std::make_unique<PerformanceCheckNode>();
    child->tag_ = V2::COMMON_VIEW_ETS_TAG;
    child->nodeInfo_ = std::make_unique<PerformanceCheckNode>();
    parent->AddChild(child);

    /**
     * @tc.steps: step2. call DumpTreeById
     * @tc.expected: cover branch GetDumpFile is nullptr and result is false
     */
    bool result = parent->UINode::DumpTreeById(0, "");
    EXPECT_FALSE(result);

    /**
     * @tc.steps: step3. set DumpFile and call DumpTreeById
     * @tc.expected: cover branch GetDumpFile is not nullptr and result is true
     */
    std::unique_ptr<std::ostream> ostream = std::make_unique<std::ostringstream>();
    ASSERT_NE(ostream, nullptr);
    DumpLog::GetInstance().SetDumpFile(std::move(ostream));

    result = parent->UINode::DumpTreeById(0, "");
    EXPECT_TRUE(result);
}

/**
 * @tc.name: DumpTreeById002
 * @tc.desc: Test ui node method DumpTreeById
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, DumpTreeById002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto parentId = ElementRegister::GetInstance()->MakeUniqueId();
    auto childId = ElementRegister::GetInstance()->MakeUniqueId();
    auto parent = FrameNode::CreateFrameNode("parent", parentId, AceType::MakeRefPtr<Pattern>(), true);
    auto child = FrameNode::CreateFrameNode("child", childId, AceType::MakeRefPtr<Pattern>(), true);

    parent->tag_ = V2::JS_FOR_EACH_ETS_TAG;
    parent->nodeInfo_ = std::make_unique<PerformanceCheckNode>();
    child->tag_ = V2::COMMON_VIEW_ETS_TAG;
    child->nodeInfo_ = std::make_unique<PerformanceCheckNode>();
    parent->AddChild(child);

    std::unique_ptr<std::ostream> ostream = std::make_unique<std::ostringstream>();
    ASSERT_NE(ostream, nullptr);
    DumpLog::GetInstance().SetDumpFile(std::move(ostream));

    /**
     * @tc.steps: step2. construt parameter and call DumpTreeById
     * @tc.expected: result is false
     */
    bool result = parent->UINode::DumpTreeById(0, "DumpTreeById002");
    EXPECT_FALSE(result);

    /**
     * @tc.steps: step3. change parameter and call DumpTreeById
     * @tc.expected: result is false
     */
    result = parent->UINode::DumpTreeById(1, "");
    EXPECT_TRUE(result);
}

/**
 * @tc.name: UINodeTestNg045
 * @tc.desc: IsContextTransparent()、GetPageNodeCountAndDepth()
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg045, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto parentId = ElementRegister::GetInstance()->MakeUniqueId();
    auto childId = ElementRegister::GetInstance()->MakeUniqueId();
    auto parent = FrameNode::CreateFrameNode("parent", parentId, AceType::MakeRefPtr<Pattern>(), true);
    auto child = FrameNode::CreateFrameNode("child", childId, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step2. call IsContextTransparent
     * @tc.expected: result is True
     */
    parent->AddChild(child);
    EXPECT_TRUE(parent->UINode::IsContextTransparent());
    int32_t count = 0;
    int32_t depth = 0;

    parent->GetPageNodeCountAndDepth(&count, &depth);
    EXPECT_EQ(parent->depth_, 1);
    EXPECT_EQ(parent->depth_, 1);

    auto child1 = FrameNode::CreateFrameNode(
        "child1", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    auto child2 = FrameNode::CreateFrameNode(
        "child2", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    child2->tag_ = V2::JS_VIEW_ETS_TAG;
    child1->AddChild(child2);
    child1->AddChild(ONE);
    std::list<int32_t> removedElmtId;
    parent->UINode::CollectRemovedChildren(child1->GetChildren(), removedElmtId, true);
    parent->UINode::GetFrameChildByIndexWithoutExpanded(0);
    parent->UINode::SetJSViewActive(false);
    parent->UINode::RenderCustomChild(0);
    std::vector<RefPtr<UINode>> res;
    parent->DFSAllChild(child1, res);
    EXPECT_EQ(res.size(), 2);
}

/**
 * @tc.name: UINodeTestNg046
 * @tc.desc: IsContextTransparent()、GetPageNodeCountAndDepth()
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg046, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto parentId = ElementRegister::GetInstance()->MakeUniqueId();
    auto childId = ElementRegister::GetInstance()->MakeUniqueId();
    auto parent = FrameNode::CreateFrameNode("parent", parentId, AceType::MakeRefPtr<Pattern>(), true);
    auto child = FrameNode::CreateFrameNode("child", childId, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step2. call IsContextTransparent
     * @tc.expected: result is True
     */
    parent->AddChild(child);
    parent->AddChild(ONE);

    auto child1 = FrameNode::CreateFrameNode(
        "child1", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    auto child2 = FrameNode::CreateFrameNode(
        "child2", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    child2->tag_ = V2::JS_VIEW_ETS_TAG;
    child1->AddChild(child2);
    std::list<int32_t> removedElmtId;
    EXPECT_TRUE(parent->UINode::GetContextWithCheck());
    EXPECT_EQ(parent->UINode::GetFrameNodeIndex(child, true), 0);
    EXPECT_EQ(parent->UINode::GetFrameNodeIndex(child1, false), -1);
}

/**
 * @tc.name: UINodeTestNg047
 * @tc.desc: Test ui node method AddChildBefore
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg047, TestSize.Level1)
{
    /**
     * @tc.steps: step1. AddChild,child not exsit and siblingNode exsit
     * @tc.expected: children_.size = 3
     */
    EXPECT_EQ(ONE->children_.size(), 0);
    ONE->Clean();
    EXPECT_EQ(ONE->children_.size(), 0);
    ONE->AddChild(TWO, 1, false);
    auto testNode = TestNode::CreateTestNode(TEST_ID_ONE);
    auto testNode2 = TestNode::CreateTestNode(TEST_ID_TWO);
    ONE->AddChild(testNode, 1, false);
    ONE->AddChildBefore(testNode2, testNode);
    EXPECT_EQ(ONE->children_.size(), 3);
    ONE->Clean();

    /**
     * @tc.steps: step2. AddChild, both child and siblingNode not exsit
     * @tc.expected: children_.size = 3
     */
    ONE->AddChild(TWO, 1, false);
    const int32_t testId3 = 23;
    auto testNode3 = TestNode::CreateTestNode(testId3);
    ONE->AddChild(testNode, 1, false);
    ONE->AddChildBefore(testNode3, testNode2);
    EXPECT_EQ(ONE->children_.size(), 3);
    ONE->Clean();

    /**
     * @tc.steps: step3. AddChild,  child  exsit
     * @tc.expected: children_.size = 3
     */
    ONE->AddChild(TWO, 1, false);
    ONE->AddChild(testNode, 1, false);
    ONE->AddChild(testNode3, 1, false);
    ONE->AddChildBefore(testNode, testNode3);
    EXPECT_EQ(ONE->children_.size(), 3);
    ONE->Clean();
}

/**
 * @tc.name: UINodeTestNg048
 * @tc.desc: Test ui node method AddChildAfter
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg048, TestSize.Level1)
{
    /**
     * @tc.steps: step1. AddChild,child exsit
     * @tc.expected: children_.size = 3
     */
    EXPECT_EQ(ONE->children_.size(), 0);
    ONE->Clean();
    EXPECT_EQ(ONE->children_.size(), 0);
    ONE->AddChild(TWO, 1, false);
    auto testNode = TestNode::CreateTestNode(TEST_ID_ONE);
    auto testNode2 = TestNode::CreateTestNode(TEST_ID_TWO);
    ONE->AddChild(testNode, 1, false);
    ONE->AddChildAfter(testNode2, testNode);
    EXPECT_EQ(ONE->children_.size(), 3);
    ONE->Clean();

    /**
     * @tc.steps: step3. AddChild, both child and siblingNode not exsit
     * @tc.expected: children_.size = 3
     */
    ONE->AddChild(TWO, 1, false);
    const int32_t testId3 = 23;
    auto testNode3 = TestNode::CreateTestNode(testId3);
    ONE->AddChild(testNode, 1, false);
    ONE->AddChildBefore(testNode3, testNode2);
    EXPECT_EQ(ONE->children_.size(), 3);
    ONE->Clean();

    /**
     * @tc.steps: step2. AddChild, addModalUiextension is false and modalUiextensionCount_ > 0
     * @tc.expected: children_.size = 0
     */
    ONE->UpdateModalUiextensionCount(true);
    ONE->AddChild(TWO, 1, false, false, false);
    ONE->RemoveImmediately();
    EXPECT_EQ(ONE->children_.size(), 1);
}

/**
 * @tc.name: UINodeTestNg050
 * @tc.desc: Test ui node method GetContextWithCheck
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg050, TestSize.Level1)
{
    /**
     * @tc.steps: step1. add child and GetContextWithCheck
     * @tc.expected: ret != nullptr
     */
    ONE->AddChild(TWO, 1, false);
    PipelineContext* ret = ONE->GetContextWithCheck();
    ASSERT_TRUE(ret != nullptr);
    ONE->Clean();
}

/**
 * @tc.name: UINodeTestNg051
 * @tc.desc: Test ui node method CurrentFrameCount/GenerateAccessibilityId
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg051, TestSize.Level1)
{
    /**
     * @tc.steps: step1. add child and excute CurrentFrameCount
     * @tc.expected: count == 0
     */
    ONE->AddChild(TWO, 1, false);
    int32_t count = ONE->CurrentFrameCount();
    ASSERT_TRUE(count == 1);
    int64_t idCurrent = ONE->GenerateAccessibilityId();
    int64_t id = ONE->GenerateAccessibilityId();
    ASSERT_TRUE(id == idCurrent + 1);
    ONE->Clean();
}

/**
 * @tc.name: UINodeTestNg052
 * @tc.desc: Test ui node method of AttachContext
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg052, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a uinode
     */
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    auto testNode = TestNode::CreateTestNode(TEST_ID_ONE);
    ASSERT_NE(testNode, nullptr);
    testNode->AddChild(TWO, 1, false);
    /**
     * @tc.steps: step2. attach context
     */
    testNode->AttachContext(AceType::RawPtr(context), true);
    EXPECT_EQ(testNode->context_, AceType::RawPtr(context));
    /**
     * @tc.steps: step3. detach context
     */
    testNode->DetachContext(true);
    EXPECT_EQ(testNode->context_, nullptr);
}

/**
 * @tc.name: UINodeTestNg053
 * @tc.desc: Test ui node method GetBestBreakPoint1
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg053, TestSize.Level1)
{
    /**
     * @tc.steps: step1. GetChildAtIndex and retParent nullptr  0000
     * @tc.expected: GetChildAtIndex and retParent nullptr
     */
    ZERO->parent_ = nullptr;
    RefPtr<UINode> retParent = ZERO->GetParent();
    RefPtr<UINode> retChildAtIndex = ZERO->GetChildAtIndex(-1);
    ZERO->GetBestBreakPoint(retChildAtIndex, retParent);
    EXPECT_EQ(retParent, nullptr);
    EXPECT_EQ(retChildAtIndex, nullptr);

    /**
     * @tc.steps: step2. GetChildAtIndex and retParent not nullptr 1100
     * @tc.expected: retParent2 nullptr and retChildAtIndex2 point to ZERO
     */
    ZERO->parent_ = nullptr;
    auto testNode25 = TestNode::CreateTestNode(25);
    ZERO->AddChild(testNode25, 1, false);
    RefPtr<UINode> retChildAtIndex2 = ZERO->GetChildAtIndex(0);
    RefPtr<UINode> retParent2 = ZERO;
    testNode25->GetBestBreakPoint(retChildAtIndex2, retParent2);
    EXPECT_EQ(retParent2, 0);
    EXPECT_EQ(retChildAtIndex2->GetTag(), ZERO->GetTag());
    ZERO->Clean();

    /**
     * @tc.steps: step3. GetChildAtIndex and retParent not nullptr,child IsDisappearing is true 1010
     * @tc.expected: retParent3  and retChildAtIndex3 point to ZERO
     */
    ASSERT_TRUE(ZERO->children_.size() == 0);
    ZERO->parent_ = nullptr;
    ZERO->AddChild(ONE, 1, false);
    ZERO->AddDisappearingChild(ONE, 0);
    RefPtr<UINode> retChildAtIndex3 = ZERO->GetChildAtIndex(0);
    RefPtr<UINode> retParent3 = ONE->GetParent();
    ONE->GetBestBreakPoint(retChildAtIndex3, retParent3);
    EXPECT_EQ(retParent3, 1);
    EXPECT_EQ(retChildAtIndex3->GetTag(), ONE->GetTag());
    ZERO->Clean();

    /**
     * @tc.steps: step4. GetChildAtIndex and retParent not nullptr, child testNode IsDisappearing is true 1110
     * @tc.expected: retParent4 point to ZERO and retChildAtIndex4 point to testNode
     */
    ZERO->parent_ = nullptr;
    auto testNode = TestNode::CreateTestNode(TEST_ID_ONE);
    ZERO->AddChild(testNode, 1, false);
    testNode->AddChild(TWO, 1, false);
    ZERO->AddDisappearingChild(testNode, 0);
    RefPtr<UINode> retChildAtIndex4 = testNode->GetChildAtIndex(0);
    RefPtr<UINode> retParent4 = testNode;
    TWO->GetBestBreakPoint(retChildAtIndex4, retParent4);
    EXPECT_EQ(retParent4->GetTag(), ZERO->GetTag());
    EXPECT_EQ(retChildAtIndex4->GetTag(), testNode->GetTag());
    ZERO->Clean();

    /**
     * @tc.steps: step5. GetChildAtIndex and retParent not nullptr,all child  Disappearing  true 1011
     * @tc.expected: retParent5  and retChildAtIndex5 do not change
     */
    ZERO->parent_ = nullptr;
    auto testNode1 = TestNode::CreateTestNode(TEST_ID_ONE);
    ZERO->AddChild(testNode1, 1, false);
    testNode1->AddChild(TWO, 1, false);
    ZERO->AddDisappearingChild(testNode1, 0);
    testNode1->AddDisappearingChild(TWO, 0);
    RefPtr<UINode> retChildAtIndex5 = testNode1->GetChildAtIndex(0);
    RefPtr<UINode> retParent5 = testNode1;
    TWO->GetBestBreakPoint(retChildAtIndex5, retParent5);
    EXPECT_EQ(retParent5->GetTag(), testNode1->GetTag());
    EXPECT_EQ(retChildAtIndex5->GetTag(), TWO->GetTag());
    ZERO->Clean();
}

/**
 * @tc.name: UINodeTestNg054
 * @tc.desc: Test ui node method GetBestBreakPoint2
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg054, TestSize.Level1)
{
    /**
     * @tc.steps: step1. GetChildAtIndex and retParent not nullptr,all child  Disappearing  true 1111
     * @tc.expected: retParent point to  testNode3 and retChildAtIndex point to  testNode4
     */
    ZERO->parent_ = nullptr;
    auto testNode3 = TestNode::CreateTestNode(TEST_ID_ONE);
    auto testNode4 = TestNode::CreateTestNode(TEST_ID_TWO);
    auto testNode5 = TestNode::CreateTestNode(23);
    ZERO->AddChild(testNode3, 1, false);
    testNode3->AddChild(testNode4, 1, false);
    testNode4->AddChild(testNode5, 1, false);
    ZERO->AddDisappearingChild(testNode3, 0);
    testNode3->AddDisappearingChild(testNode4, 0);
    RefPtr<UINode> retChildAtIndex = testNode4->GetChildAtIndex(0);
    RefPtr<UINode> retParent = testNode4;
    testNode4->GetBestBreakPoint(retChildAtIndex, retParent);
    EXPECT_EQ(retParent->GetTag(), testNode3->GetTag());
    EXPECT_EQ(retChildAtIndex->GetTag(), testNode4->GetTag());
    ZERO->Clean();
}

/**
 * @tc.name: UINodeTestNg055
 * @tc.desc: Test ui node method RemoveFromParentCleanly
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg055, TestSize.Level1)
{
    /**
     * @tc.steps: step1. child isDisappearing_ is false, not in ModifyChildren
     * @tc.expected: testNode3 has been deleted
     */
    ZERO->parent_ = nullptr;
    auto testNode1 = TestNode::CreateTestNode(TEST_ID_ONE);
    auto testNode2 = TestNode::CreateTestNode(TEST_ID_TWO);
    const RefPtr<FrameNode> testNode3 =
        FrameNode::CreateFrameNode("testNode1", 1, AceType::MakeRefPtr<Pattern>(), true);
    ZERO->AddChild(testNode1, 1, false);
    testNode1->AddChild(testNode2, 1, false);
    testNode2->AddChild(testNode3, 1, false);
    testNode3->RemoveFromParentCleanly(testNode3, testNode2);
    EXPECT_EQ(testNode2->children_.size(), 0);
    const RefPtr<FrameNode> testNode4 =
        FrameNode::CreateFrameNode("testNode4", 1, AceType::MakeRefPtr<Pattern>(), true);
    testNode2->AddChild(testNode3, 1, false);
    testNode4->RemoveFromParentCleanly(testNode4, testNode2);
    EXPECT_EQ(testNode2->children_.size(), 1);
    ZERO->Clean();

    /**
     * @tc.steps: step2. child isDisappearing_ is true
     * @tc.expected: child isDisappearing_ is false
     */
    ZERO->parent_ = nullptr;
    auto testNode5 = TestNode::CreateTestNode(25);
    auto testNode6 = TestNode::CreateTestNode(26);
    const RefPtr<FrameNode> testNode7 =
        FrameNode::CreateFrameNode("testNode7", 1, AceType::MakeRefPtr<Pattern>(), true);
    ZERO->AddChild(testNode5, 1, false);
    testNode5->AddChild(testNode6, 1, false);
    testNode6->AddChild(testNode7, 1, false);
    testNode6->AddDisappearingChild(testNode7, 0);
    testNode7->RemoveFromParentCleanly(testNode7, testNode6);
    EXPECT_EQ(testNode7->isDisappearing_, false);
    ZERO->Clean();
}

/**
 * @tc.name: UINodeTestNg057
 * @tc.desc: Test ui node method DumpViewDataPageNodes
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg057, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a uinode and add child,skipSubAutoFillContainer is false
     * @tc.expected: expect no exception
     */
    const RefPtr<FrameNode> testNode1 =
        FrameNode::CreateFrameNode("testNode1", 1, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode2 =
        FrameNode::CreateFrameNode("testNode2", 1, AceType::MakeRefPtr<Pattern>(), true);
    testNode1->AddChild(testNode2, 1, false);
    testNode1->AddChild(nullptr, 1, false);
    auto viewDataWrap = ViewDataWrap::CreateViewDataWrap();
    testNode1->DumpViewDataPageNodes(viewDataWrap, false);
    ZERO->Clean();

    /**
     * @tc.steps: step2. construct a uinode and add child,skipSubAutoFillContainer is true
     * @tc.expected: expect no exception
     */
    const RefPtr<FrameNode> testNode3 =
        FrameNode::CreateFrameNode("testNode1", 1, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode4 =
        FrameNode::CreateFrameNode("testNode2", 1, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNodePage = FrameNode::CreateFrameNode("page", 1, AceType::MakeRefPtr<Pattern>(), true);
    testNode3->AddChild(testNode4, 1, false);
    testNode3->AddChild(nullptr, 1, false);
    testNode3->AddChild(testNodePage, 1, false);
    auto viewDataWrap2 = ViewDataWrap::CreateViewDataWrap();
    testNode3->DumpViewDataPageNodes(viewDataWrap2, true);
    ZERO->Clean();
    EXPECT_TRUE(DumpLog::GetInstance().result_.find("testNode2"));
}

/**
 * @tc.name: UINodeTestNg058
 * @tc.desc: Test ui node method DumpTree
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg058, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a FrameNode with Disappearing child and OverlayNode child
     * @tc.expected: expect no exception
     */
    ZERO->parent_ = nullptr;
    const RefPtr<FrameNode> testNode1 =
        FrameNode::CreateFrameNode("testNode1", 1, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode2 =
        FrameNode::CreateFrameNode("testNode2", 1, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode3 =
        FrameNode::CreateFrameNode("testNode3", 1, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode4 =
        FrameNode::CreateFrameNode("testNode4", 1, AceType::MakeRefPtr<Pattern>(), true);
    ZERO->AddChild(testNode1, 1, false);
    ZERO->AddChild(testNode2, 1, false);
    ZERO->AddDisappearingChild(testNode1, 0);
    testNode1->SetOverlayNode(testNode3);
    testNode1->AddDisappearingChild(testNode4, 0);
    testNode1->DumpTree(0);
    ZERO->Clean();
    EXPECT_TRUE(DumpLog::GetInstance().result_.find("testNode1"));
}

/**
 * @tc.name: UINodeTestNg059
 * @tc.desc: Test ui node method DumpTreeById
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg059, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a FrameNode with Disappearing child
     * @tc.expected: expect no exception
     */
    ZERO->parent_ = nullptr;
    const RefPtr<FrameNode> testNode1 =
        FrameNode::CreateFrameNode("testNode1", 1, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode2 =
        FrameNode::CreateFrameNode("testNode2", 2, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode3 =
        FrameNode::CreateFrameNode("testNode3", 3, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode4 =
        FrameNode::CreateFrameNode("testNode4", 4, AceType::MakeRefPtr<Pattern>(), true);
    ZERO->AddChild(testNode1, 1, false);
    ZERO->AddChild(testNode2, 1, false);
    ZERO->AddDisappearingChild(testNode1, 0);
    testNode1->AddChild(testNode3, 0);
    testNode1->AddDisappearingChild(testNode4, 0);
    testNode1->DumpTreeById(0, "3");
    testNode1->DumpTreeById(0, "4");
    ZERO->Clean();
    EXPECT_TRUE(DumpLog::GetInstance().result_.find("testNode1"));
}

/**
 * @tc.name: UINodeTestNg060
 * @tc.desc: Test ui node method AdjustLayoutWrapperTree
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg060, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a FrameNode with child
     * @tc.expected: expect no exception
     */
    const RefPtr<FrameNode> testNode1 =
        FrameNode::CreateFrameNode("testNode1", 1, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode2 =
        FrameNode::CreateFrameNode("testNode2", 2, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode3 =
        FrameNode::CreateFrameNode("testNode3", 3, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode4 =
        FrameNode::CreateFrameNode("testNode4", 4, AceType::MakeRefPtr<Pattern>(), true);
    testNode1->AddChild(testNode2, 1, false);
    testNode1->AddChild(testNode3, 1, false);
    testNode1->AddChild(testNode4, 1, false);
    RefPtr<LayoutWrapperNode> retLayoutWrapper = testNode1->UINode::CreateLayoutWrapper(true, true);
    testNode1->UINode::AdjustLayoutWrapperTree(retLayoutWrapper, false, false);
    EXPECT_EQ(testNode1->GetChildren().size(), 3);
}

/**
 * @tc.name: UINodeTestNg061
 * @tc.desc: Test ui node method CreateExportTextureInfoIfNeeded
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg061, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a FrameNode
     * @tc.expected: expect no exception
     */
    const RefPtr<FrameNode> testNode1 =
        FrameNode::CreateFrameNode("testNode1", 1, AceType::MakeRefPtr<Pattern>(), true);
    testNode1->UINode::CreateExportTextureInfoIfNeeded();
    EXPECT_EQ(testNode1->GetExportTextureInfo() != nullptr, true);
    testNode1->UINode::CreateExportTextureInfoIfNeeded();
    EXPECT_EQ(testNode1->GetExportTextureInfo() != nullptr, true);
}

/**
 * @tc.name: UINodeTestNg062
 * @tc.desc: Test ui node method SetJSViewActive
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg062, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create custome node,SetIsV2 false,isLazyForEachNode true
     */
    auto parentId = ElementRegister::GetInstance()->MakeUniqueId();
    auto childId = ElementRegister::GetInstance()->MakeUniqueId();
    auto childTwoId = ElementRegister::GetInstance()->MakeUniqueId();
    auto parent = CustomNode::CreateCustomNode(parentId, "parent");
    auto child = CustomNode::CreateCustomNode(childId, "child");
    auto childTwo = CustomNode::CreateCustomNode(childTwoId, "child_two");
    parent->AddChild(child);
    parent->AddChild(childTwo);
    parent->UINode::SetJSViewActive(true, true);
    child->SetIsV2(true);
    parent->UINode::SetJSViewActive(true, true);
    EXPECT_TRUE(child->GetJsActive());
}

/**
 * @tc.name: UINodeTestNg063
 * @tc.desc: Test ui node method OnRecycle/OnReuse/PaintDebugBoundaryTreeAll/IsContextTransparent
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg063, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create custome node,SetIsV2 false,isLazyForEachNode true
     */
    const RefPtr<FrameNode> testNode1 =
        FrameNode::CreateFrameNode("testNode1", 1, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode2 =
        FrameNode::CreateFrameNode("testNode2", 2, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode3 =
        FrameNode::CreateFrameNode("testNode3", 3, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode4 =
        FrameNode::CreateFrameNode("testNode4", 4, AceType::MakeRefPtr<Pattern>(), true);
    testNode1->AddChild(testNode2, 1, false);
    testNode1->AddChild(testNode3, 1, false);
    testNode1->AddChild(testNode4, 1, false);
    testNode1->OnRecycle();
    testNode1->OnReuse();
    testNode1->PaintDebugBoundaryTreeAll(true);
    bool ret = testNode1->IsContextTransparent();
    EXPECT_EQ(ret, true);
}

/**
 * @tc.name: UINodeTestNg064
 * @tc.desc: Test ui node method DFSAllChild
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg064, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create node without child
     */
    const RefPtr<FrameNode> testNode1 =
        FrameNode::CreateFrameNode("testNode1", 1, AceType::MakeRefPtr<Pattern>(), true);
    std::vector<RefPtr<UINode>> ret;
    testNode1->DFSAllChild(testNode1, ret);
    EXPECT_EQ(ret.size(), 1);
    ret.clear();

    /**
     * @tc.steps: step2. create node with child
     */
    const RefPtr<FrameNode> testNode2 =
        FrameNode::CreateFrameNode("testNode2", 2, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode3 =
        FrameNode::CreateFrameNode("testNode3", 3, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode4 =
        FrameNode::CreateFrameNode("testNode4", 4, AceType::MakeRefPtr<Pattern>(), true);
    testNode1->AddChild(testNode2, 1, false);
    testNode1->AddChild(testNode3, 1, false);
    testNode1->AddChild(testNode4, 1, false);
    testNode1->DFSAllChild(testNode1, ret);
    EXPECT_EQ(ret.size(), 3);
    ret.clear();
}

/**
 * @tc.name: UINodeTestNg065
 * @tc.desc: Test ui node method GetPageNodeCountAndDepth
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg065, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create FrameNode with child
     */
    const RefPtr<FrameNode> testNode1 =
        FrameNode::CreateFrameNode("testNode1", 1, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode2 =
        FrameNode::CreateFrameNode("testNode2", 2, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode3 =
        FrameNode::CreateFrameNode("testNode3", 3, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode4 =
        FrameNode::CreateFrameNode("testNode4", 4, AceType::MakeRefPtr<Pattern>(), true);
    testNode1->AddChild(testNode2, 1, false);
    testNode1->AddChild(testNode3, 1, false);
    testNode1->AddChild(testNode4, 1, false);
    int32_t* count = new int32_t(0);
    int32_t* depth = new int32_t(0);
    testNode1->GetPageNodeCountAndDepth(count, depth);
    EXPECT_EQ(*count, 4);
    delete count;
    delete depth;
}

/**
 * @tc.name: UINodeTestNg066
 * @tc.desc: Test ui node method CollectRemovedChildren/UpdateNodeStatus
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg066, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create FrameNode with child
     */
    const RefPtr<FrameNode> testNode1 =
        FrameNode::CreateFrameNode("testNode1", 1, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode2 =
        FrameNode::CreateFrameNode("testNode2", 2, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode3 =
        FrameNode::CreateFrameNode("testNode3", 3, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode4 =
        FrameNode::CreateFrameNode("testNode4", 4, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode5 =
        FrameNode::CreateFrameNode("testNode5", 5, AceType::MakeRefPtr<Pattern>(), true);
    testNode1->AddChild(testNode2, 1, false);
    testNode1->AddChild(testNode3, 1, false);
    testNode1->AddChild(testNode4, 1, false);
    testNode2->AddChild(testNode5, 1, false);
    testNode2->SetIsRootBuilderNode(true);
    std::list<int32_t> removedElmtId;
    testNode1->CollectRemovedChildren(testNode1->GetChildren(), removedElmtId, true);
    EXPECT_EQ(removedElmtId.size(), 2);
    testNode2->CollectRemovedChildren(testNode2->GetChildren(), removedElmtId, true);
    EXPECT_EQ(removedElmtId.size(), 3);
}

/**
 * @tc.name: UINodeTestNg067
 * @tc.desc: Test ui node method GetFrameChildByIndexWithoutExpanded
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg067, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create FrameNode with child
     */
    auto testNode1 = TestNode::CreateTestNode(21);
    auto testNode2 = TestNode::CreateTestNode(22);
    auto testNode3 = TestNode::CreateTestNode(23);
    auto testNode4 = TestNode::CreateTestNode(24);
    testNode1->AddChild(testNode2, 1, false);
    testNode1->AddChild(testNode3, 1, false);
    testNode1->AddChild(testNode4, 1, false);
    RefPtr<UINode> ret = testNode1->GetFrameChildByIndexWithoutExpanded(4);
    EXPECT_EQ(ret == nullptr, true);
}

/**
 * @tc.name: UINodeTestNg068
 * @tc.desc: Test ui node method Build
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg068, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create custome node,SetIsV2 false,isLazyForEachNode true
     */
    auto parentId = ElementRegister::GetInstance()->MakeUniqueId();
    auto childId = ElementRegister::GetInstance()->MakeUniqueId();
    auto childTwoId = ElementRegister::GetInstance()->MakeUniqueId();
    auto parent = CustomNode::CreateCustomNode(parentId, "parent");
    auto child = CustomNode::CreateCustomNode(childId, "child");
    auto childTwo = CustomNode::CreateCustomNode(childTwoId, "child_two");
    auto childThree = TestNode::CreateTestNode(24);
    ExtraInfo extraInfo;
    extraInfo.page = "1";
    childTwo->SetExtraInfo(extraInfo);
    parent->AddChild(child);
    parent->AddChild(childTwo);
    parent->AddChild(childThree);
    std::shared_ptr<std::list<ExtraInfo>> extraInfos;
    parent->UINode::Build(extraInfos);
    extraInfos = std::make_shared<std::list<ExtraInfo>>();
    parent->UINode::Build(extraInfos);
    EXPECT_EQ(parent->GetChildren().size(), 3);
}

/**
 * @tc.name: UINodeTestNg069
 * @tc.desc: Test ui node method GenerateOneDepthVisibleFrameWithTransition/GenerateOneDepthVisibleFrameWithOffset
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg069, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create FrameNode node,AddChild,AddDisappearingChild
     */
    const RefPtr<FrameNode> testNode1 =
        FrameNode::CreateFrameNode("testNode1", 1, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode2 =
        FrameNode::CreateFrameNode("testNode2", 2, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode3 =
        FrameNode::CreateFrameNode("testNode3", 3, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode4 =
        FrameNode::CreateFrameNode("testNode4", 4, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode5 =
        FrameNode::CreateFrameNode("testNode5", 5, AceType::MakeRefPtr<Pattern>(), true);
    testNode1->AddChild(testNode2, 1, false);
    testNode1->AddChild(testNode3, 1, false);
    testNode1->AddChild(testNode4, 1, false);
    OffsetT<float> offset;
    std::list<RefPtr<FrameNode>> visibleList;
    testNode1->GenerateOneDepthVisibleFrameWithOffset(visibleList, offset);
    testNode1->AddDisappearingChild(testNode2, 1);
    testNode1->AddDisappearingChild(testNode3, 2);
    testNode1->AddDisappearingChild(testNode4, 3);
    testNode1->AddDisappearingChild(testNode5, 4);
    testNode1->GenerateOneDepthVisibleFrameWithTransition(visibleList);
    testNode1->GenerateOneDepthVisibleFrameWithOffset(visibleList, offset);
    EXPECT_EQ(testNode1->GetChildren().size(), 3);
}

/**
 * @tc.name: UINodeTestNg070
 * @tc.desc: Test ui node method TouchTest/MouseTest
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg070, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create FrameNode node and construct params
     */
    auto testNode1 = TestNode::CreateTestNode(21);
    const RefPtr<FrameNode> testNode2 =
        FrameNode::CreateFrameNode("testNode2", 2, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode3 =
        FrameNode::CreateFrameNode("testNode3", 3, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode4 =
        FrameNode::CreateFrameNode("testNode4", 4, AceType::MakeRefPtr<Pattern>(), true);
    testNode1->AddChild(testNode2, 1, false);
    testNode1->AddChild(testNode3, 1, false);
    testNode1->AddChild(testNode4, 1, false);
    PointT<float> globalPoint;
    PointT<float> parentLocalPoint;
    PointT<float> parentRevertPoint;
    TouchRestrict touchRestrict;
    MouseTestResult onMouseResult;
    MouseTestResult onHoverResult;
    RefPtr<FrameNode> hoverNode;
    HitTestResult ret =
        testNode1->UINode::MouseTest(globalPoint, parentLocalPoint, onMouseResult, onHoverResult, hoverNode);
    EXPECT_EQ(ret == HitTestResult::BUBBLING, true);
    AxisTestResult onAxisResult;
    HitTestResult ret2 =
        testNode1->UINode::AxisTest(globalPoint, parentLocalPoint, parentRevertPoint, touchRestrict, onAxisResult);
    EXPECT_EQ(ret2 == HitTestResult::OUT_OF_REGION, true);
}

/**
 * @tc.name: UINodeTestNg071
 * @tc.desc: Test ui node method SetAccessibilityNodeVirtual
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg071, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create FrameNode node and construct params
     */
    auto testNode1 = TestNode::CreateTestNode(21);
    auto child = TestNode::CreateTestNode(22);
    testNode1->SetAccessibilityNodeVirtual();
    EXPECT_EQ(testNode1->IsAccessibilityVirtualNode(), true);
    testNode1->SetAccessibilityVirtualNodeParent(child);
    auto weakResult = testNode1->GetVirtualNodeParent();
    auto result = weakResult.Upgrade();
    ASSERT_NE(result, nullptr);
}

/**
 * @tc.name: GetPerformanceCheckData004
 * @tc.desc: Test ui node method GetPerformanceCheckData
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, GetPerformanceCheckData004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create parent and childframe node
     */
    auto parentId = ElementRegister::GetInstance()->MakeUniqueId();
    auto childId = ElementRegister::GetInstance()->MakeUniqueId();
    auto childIdId2 = ElementRegister::GetInstance()->MakeUniqueId();
    auto parent = FrameNode::CreateFrameNode("parent", parentId, AceType::MakeRefPtr<Pattern>(), true);
    auto child = FrameNode::CreateFrameNode("child", childId, AceType::MakeRefPtr<Pattern>(), true);
    auto child2 = FrameNode::CreateFrameNode("child2", childIdId2, AceType::MakeRefPtr<Pattern>(), true);

    parent->tag_ = V2::JS_FOR_EACH_ETS_TAG;
    parent->nodeInfo_ = std::make_unique<PerformanceCheckNode>();
    child->tag_ = V2::COMMON_VIEW_ETS_TAG;
    child->nodeInfo_ = std::make_unique<PerformanceCheckNode>();
    parent->AddChild(child);

    /**
     * @tc.steps: step2.  construct parameter performanceCheckNodeMap and call GetPerformanceCheckData
     * @tc.expected: isBuildByJS_ is false
     */
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    PerformanceCheckNodeMap nodeMap;
    PerformanceCheckNode performanceCheckNode = PerformanceCheckNode();
    nodeMap.emplace(nodeId, performanceCheckNode);
    child->UINode::GetPerformanceCheckData(nodeMap);
    child2->tag_ = V2::COMMON_VIEW_ETS_TAG;
    child2->nodeInfo_ = std::make_unique<PerformanceCheckNode>();
    child->AddChild(child2, 1, false);
    auto childId4 = ElementRegister::GetInstance()->MakeUniqueId();
    auto child4 = FrameNode::CreateFrameNode("child4", childId4, AceType::MakeRefPtr<Pattern>(), true);
    child4->tag_ = V2::JS_FOR_EACH_ETS_TAG;
    child4->nodeInfo_ = std::make_unique<PerformanceCheckNode>();
    child->AddChild(child4, 1, false);
    // grandChildren exist
    auto childIdId3 = ElementRegister::GetInstance()->MakeUniqueId();
    auto child3 = FrameNode::CreateFrameNode("child3", childIdId3, AceType::MakeRefPtr<Pattern>(), true);
    child3->nodeInfo_ = std::make_unique<PerformanceCheckNode>();
    child2->AddChild(child3);
    child->UINode::GetPerformanceCheckData(nodeMap);

    /**
     * @tc.steps: step3. change child tag_ and call GetPerformanceCheckData
     * @tc.expected: isBuildByJS_ is false
     */
    child->tag_ = V2::JS_FOR_EACH_ETS_TAG;
    child->UINode::GetPerformanceCheckData(nodeMap);
    EXPECT_EQ(child->nodeInfo_->nodeTag, "ForEach");
}

/**
 * @tc.name: CollectRemovedChildren001
 * @tc.desc: Test ui node method CollectRemovedChildren
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, CollectRemovedChildren001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create FrameNode with child
     */
    const RefPtr<FrameNode> testNode1 =
        FrameNode::CreateFrameNode("testNode1", 1, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode2 =
        FrameNode::CreateFrameNode("testNode2", 2, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode3 =
        FrameNode::CreateFrameNode("testNode3", 3, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode4 =
        FrameNode::CreateFrameNode("testNode4", 4, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode5 =
        FrameNode::CreateFrameNode("testNode5", 5, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step2. add child
     */
    testNode1->AddChild(testNode2, 1, false);
    testNode1->AddChild(testNode3, 1, false);
    testNode1->AddChild(testNode4, 1, false);
    testNode2->AddChild(testNode5, 1, false);

    /**
     * @tc.steps: step3. set API12.
     */
    int originApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TWELVE);

    /**
     * @tc.steps: step4. test CollectRemovedChildren.
     */
    testNode2->isDisappearing_ = true;
    std::list<int32_t> removedElmtId1;
    testNode1->CollectRemovedChildren(testNode1->GetChildren(), removedElmtId1, true);
    EXPECT_EQ(removedElmtId1.size(), 2);
    testNode2->CollectRemovedChildren(testNode2->GetChildren(), removedElmtId1, true);
    EXPECT_EQ(removedElmtId1.size(), 3);

    /**
     * @tc.steps: step5. revert to the origin API.
     */
    AceApplicationInfo::GetInstance().SetApiTargetVersion(originApiVersion);
}

/**
 * @tc.name: CollectRemovedChildren002
 * @tc.desc: Test ui node method CollectRemovedChildren
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, CollectRemovedChildren002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create FrameNode with child
     */
    const RefPtr<FrameNode> testNode1 =
        FrameNode::CreateFrameNode("testNode1", 1, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode2 =
        FrameNode::CreateFrameNode("testNode2", 2, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode3 =
        FrameNode::CreateFrameNode("testNode3", 3, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode4 =
        FrameNode::CreateFrameNode("testNode4", 4, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode5 =
        FrameNode::CreateFrameNode("testNode5", 5, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step2. add child
     */
    testNode1->AddChild(testNode2, 1, false);
    testNode1->AddChild(testNode3, 1, false);
    testNode1->AddChild(testNode4, 1, false);
    testNode2->AddChild(testNode5, 1, false);

    /**
     * @tc.steps: step3. set API13.
     */
    int originApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_THIRTEEN);

    /**
     * @tc.steps: step4. test CollectRemovedChildren.
     */
    testNode2->isDisappearing_ = true;
    std::list<int32_t> removedElmtId2;
    testNode1->CollectRemovedChildren(testNode1->GetChildren(), removedElmtId2, true);
    EXPECT_EQ(removedElmtId2.size(), 4);
    testNode2->CollectRemovedChildren(testNode2->GetChildren(), removedElmtId2, false);
    EXPECT_EQ(removedElmtId2.size(), 5);
    
    /**
     * @tc.steps: step5. revert to the origin API.
     */
    AceApplicationInfo::GetInstance().SetApiTargetVersion(originApiVersion);
}
} // namespace OHOS::Ace::NG
