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
} // namespace

class UINodeTestNg : public testing::Test {
public:
    static void SetUpTestCase() {}
    static void TearDownTestCase() {}
};

/**
 * @tc.name: UINodeTestNg001
 * @tc.desc: Test ui node method
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. AddChild
     * @tc.expected: step1. children_.size = 2
     */
    ONE->AddChild(TWO, 1, false);
    ONE->AddChild(TWO, 1, false);
    ONE->AddChild(THREE, 1, false);
    EXPECT_EQ(ONE->children_.size(), 2);
    /**
     * @tc.steps: step2. remove child three
     * @tc.expected: step2. children_.size =
     */
    auto iter = ONE->RemoveChild(FOUR);
    EXPECT_EQ(iter, ONE->children_.end());
    auto nextIter = ONE->RemoveChild(THREE);
    EXPECT_EQ(nextIter, ONE->children_.end());
    /**
     * @tc.steps: step3. remove child two
     * @tc.expected: step3. distance = 0
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
     * @tc.expected: step1. children_.size = 0
     */
    ONE->RemoveChildAtIndex(0);
    EXPECT_EQ(ONE->children_.size(), 0);
    /**
     * @tc.steps: step2. GetChildAtIndex
     * @tc.expected: step2. return nullptr
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
     * @tc.expected: step1. size = 2
     */
    ONE->ReplaceChild(nullptr, THREE);
    ONE->ReplaceChild(TWO, FOUR);
    EXPECT_EQ(ONE->children_.size(), 2);
    /**
     * @tc.steps: step2. set TWO's hostPageId_ 1 and Clean
     * @tc.expected: step2. children_ = 0
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
     * @tc.expected: step1. parent is nullptr
     */
    auto frameNode = ONE->GetFocusParent();
    EXPECT_EQ(frameNode, nullptr);
    FocusType focusTypes[3] = { FocusType::SCOPE, FocusType::NODE, FocusType::DISABLE };
    auto parent = FrameNode::CreateFrameNode("parent", 2, AceType::MakeRefPtr<Pattern>());
    RefPtr<FrameNode> frameNodes[3] = { parent, nullptr, nullptr };
    /**
     * @tc.steps: step2. GetFocusParent adjust FocusType
     * @tc.expected: step2. result is parent and nullptr
     */
    for (int i = 0; i < 3; ++i) {
        auto eventHub = AceType::MakeRefPtr<EventHub>();
        auto focusHub = AceType::MakeRefPtr<FocusHub>(eventHub, focusTypes[i]);
        eventHub->focusHub_ = focusHub;
        parent->eventHub_ = eventHub;
        ONE->parent_ = parent;
        auto result = ONE->GetFocusParent();
        EXPECT_EQ(result, frameNodes[i]);
    }
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
     * @tc.expected: step1. THREE's children size is 2
     */
    std::list<RefPtr<FrameNode>> children;
    auto eventHubTwo = AceType::MakeRefPtr<EventHub>();
    auto focusHubTwo = AceType::MakeRefPtr<FocusHub>(eventHubTwo, FocusType::NODE);
    auto eventHubFour = AceType::MakeRefPtr<EventHub>();
    auto focusHubFour = AceType::MakeRefPtr<FocusHub>(eventHubFour, FocusType::DISABLE);
    eventHubTwo->focusHub_ = focusHubTwo;
    TWO->eventHub_ = eventHubTwo;
    eventHubFour->focusHub_ = focusHubFour;
    FOUR->eventHub_ = eventHubFour;
    THREE->AddChild(TWO, 1, false);
    THREE->AddChild(FOUR, 1, false);
    THREE->GetFocusChildren(children);
    EXPECT_EQ(THREE->children_.size(), 2);
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
     * @tc.expected: step1. onMainTree_ is false
     */
    bool mainTrees[2] = { true, false };
    TWO->AddChild(THREE, 1, false);
    for (int i = 0; i < 2; ++i) {
        TWO->onMainTree_ = mainTrees[i];
        TWO->AttachToMainTree();
        TWO->DetachFromMainTree();
        EXPECT_FALSE(TWO->onMainTree_);
    }
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
     * @tc.expected: step1. children_.size is 2
     */
    int32_t slots[3] = { -1, 1, 3 };
    THREE->AddChild(FOUR, 1, false);
    THREE->AddChild(FIVE, 1, false);
    TWO->parent_ = THREE;
    for (int i = 0; i < 3; ++i) {
        TWO->MovePosition(slots[i]);
    }
    EXPECT_EQ(TWO->children_.size(), 2);
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
    auto pipeline = UINode::GetContext();
    EXPECT_NE(pipeline, nullptr);
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
     * @tc.expected: step1. count is 2, pos is 0
     */
    int32_t count = ONE->FrameCount();
    EXPECT_EQ(count, 1);
    int32_t id1 = ONE->GetChildIndexById(4);
    int32_t id2 = ONE->GetChildIndexById(2);
    EXPECT_EQ(id1, -1);
    EXPECT_EQ(id2, 0);
    /**
     * @tc.steps: step2. GetChildFlatIndex
     * @tc.expected: step2. count is 2, pos is 0
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
     * @tc.expected: step1. the return value is -1
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
     * @tc.expected: step3. the return value is 1
     */
    ZERO->AddChild(TWO);
    retIndex = ZERO->GetChildIndex(TWO);
    EXPECT_EQ(retIndex, 1);
    /**
     * @tc.steps: step4. add three child for ZERO and call GetChildIndex
     * @tc.expected: step4. the return value is 2
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
     * @tc.steps: step1. call the MountToParent and set input is null
     * @tc.expected: step1. mount failure
     */
    ZERO->MountToParent(nullptr, 1, false);
    /**
     * @tc.steps: step2. call the MountToParent and set hostPageId_ is 0
     * @tc.expected: step2. mount failure
     */
    ZERO->hostPageId_ = 0;
    ONE->MountToParent(ZERO, 1, false);
    int retPageId = ONE->GetPageId();
    EXPECT_NE(retPageId, 0);
    ONE->Clean();
    /**
     * @tc.steps: step3. call the MountToParent and set hostPageId_ is 0
     * @tc.expected: step3. mount sucess and pageid is 1
     */
    ZERO->hostPageId_ = 1;
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
     * @tc.expected: step1. the return value is null
     */
    RefPtr<FocusHub> retFirstFocusHubChild = ZERO->GetFirstFocusHubChild();
    EXPECT_EQ(retFirstFocusHubChild, nullptr);
    /**
     * @tc.steps: step2. call the GetFirstFocusHubChild functionand and set focus type is DISABLE
     * @tc.expected: step2. the return value is null
     */
    auto eventHubZero = AceType::MakeRefPtr<EventHub>();
    auto focusHubZero = AceType::MakeRefPtr<FocusHub>(eventHubZero, FocusType::DISABLE);

    eventHubZero->focusHub_ = focusHubZero;
    ZERO->eventHub_ = eventHubZero;
    retFirstFocusHubChild = ZERO->GetFirstFocusHubChild();
    EXPECT_EQ(retFirstFocusHubChild, nullptr);
    /**
     * @tc.steps: step3. call the GetFirstFocusHubChild functionand set focus type is NODE
     * @tc.expected: step3. the return focusHub type is NODE
     */
    focusHubZero = AceType::MakeRefPtr<FocusHub>(eventHubZero, FocusType::NODE);

    eventHubZero->focusHub_ = focusHubZero;
    ZERO->eventHub_ = eventHubZero;
    retFirstFocusHubChild = ZERO->GetFirstFocusHubChild();
    EXPECT_EQ(retFirstFocusHubChild->GetFocusType(), FocusType::NODE);
    ZERO->Clean();
    /**
     * @tc.steps: step4. call the GetFirstFocusHubChild functionand set focus type is SCOPE
     * @tc.expected: step4. the return focusHub type is SCOPE
     */
    focusHubZero = AceType::MakeRefPtr<FocusHub>(eventHubZero, FocusType::SCOPE);

    eventHubZero->focusHub_ = focusHubZero;
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
     * @tc.expected: step1. the return focusHub type is NODE
     */
    auto eventHubZero = AceType::MakeRefPtr<EventHub>();
    auto focusHubZero = AceType::MakeRefPtr<FocusHub>(eventHubZero, FocusType::DISABLE);
    auto eventHubOne = AceType::MakeRefPtr<EventHub>();
    auto focusHubOne = AceType::MakeRefPtr<FocusHub>(eventHubOne, FocusType::NODE);

    eventHubZero->focusHub_ = focusHubZero;
    ZERO->eventHub_ = eventHubZero;
    eventHubOne->focusHub_ = focusHubOne;
    ONE->eventHub_ = eventHubOne;

    ZERO->AddChild(ONE, 1, false);
    RefPtr<FocusHub> retFirstFocusHubChild = ZERO->GetFirstFocusHubChild();
    EXPECT_EQ(retFirstFocusHubChild->GetFocusType(), FocusType::NODE);
    ZERO->Clean();
    /**
     * @tc.steps: step2. add one child to ZERO and set focus type is DISABLE
     * @tc.expected: step2. the return value is null
     */
    focusHubOne = AceType::MakeRefPtr<FocusHub>(eventHubOne, FocusType::DISABLE);

    eventHubOne->focusHub_ = focusHubOne;
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
     * @tc.expected: step1. the return focusHub type is SCOPE
     */
    auto eventHubZero = AceType::MakeRefPtr<EventHub>();
    auto focusHubZero = AceType::MakeRefPtr<FocusHub>(eventHubZero, FocusType::DISABLE);
    auto eventHubOne = AceType::MakeRefPtr<EventHub>();
    auto focusHubOne = AceType::MakeRefPtr<FocusHub>(eventHubOne, FocusType::SCOPE);

    eventHubZero->focusHub_ = focusHubZero;
    ZERO->eventHub_ = eventHubZero;
    eventHubOne->focusHub_ = focusHubOne;
    ONE->eventHub_ = eventHubOne;

    ZERO->AddChild(ONE, 1, false);
    RefPtr<FocusHub> retFirstFocusHubChild = ZERO->GetFirstFocusHubChild();
    EXPECT_EQ(retFirstFocusHubChild->GetFocusType(), FocusType::SCOPE);
    ZERO->Clean();
    /**
     * @tc.steps: step2. add one child to ZERO and set focus type is DISABLE
     * @tc.expected: step2. the return value is null
     */
    focusHubOne = AceType::MakeRefPtr<FocusHub>(eventHubOne, FocusType::DISABLE);

    eventHubOne->focusHub_ = focusHubOne;
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
     * @tc.expected: step1. parentNode is null
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
     * @tc.expected: step1. the MarkDirtyNode function is run ok and children_.size() is 1
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
     * @tc.expected: step2. the MarkDirtyNode function is run ok and children_.size() is 1
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
     * @tc.expected: step3. the MarkDirtyNode function is run ok and children_.size() is 1
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
     * @tc.expected: step1. the MarkNeedFrameFlushDirty function is run ok
     */
    PropertyChangeFlag extraFLAG = PROPERTY_UPDATE_NORMAL;
    ZERO->layoutProperty_->propertyChangeFlag_ = PROPERTY_UPDATE_NORMAL;
    ONE->layoutProperty_->propertyChangeFlag_ = PROPERTY_UPDATE_NORMAL;

    ZERO->UINode::MarkNeedFrameFlushDirty(extraFLAG);
    EXPECT_EQ(ZERO->parent_.Upgrade(), nullptr);
    /**
     * @tc.steps: step2. set one parent_ for ONE and call the MarkNeedFrameFlushDirty
     * @tc.expected: step2. the MarkNeedFrameFlushDirty function is run ok and parent_ is not null
     */
    ZERO->parent_ = ONE;
    ZERO->UINode::MarkNeedFrameFlushDirty(extraFLAG);
    ASSERT_NE(ZERO->parent_.Upgrade(), nullptr);
    ZERO->Clean();
    ZERO->parent_.Reset();
    /**
     * @tc.steps: step3. set propertyChangeFlag_ is PROPERTY_UPDATE_MEASURE and call the MarkNeedFrameFlushDirty
     * @tc.expected: step3. the MarkNeedFrameFlushDirty function is run ok
     */
    extraFLAG = PROPERTY_UPDATE_MEASURE;
    ZERO->layoutProperty_->propertyChangeFlag_ = PROPERTY_UPDATE_MEASURE;
    ONE->layoutProperty_->propertyChangeFlag_ = PROPERTY_UPDATE_MEASURE;

    ZERO->UINode::MarkNeedFrameFlushDirty(extraFLAG);
    EXPECT_EQ(ZERO->parent_.Upgrade(), nullptr);
    /**
     * @tc.steps: step4. set one parent_ for ONE and call the MarkNeedFrameFlushDirty
     * @tc.expected: step4. the MarkNeedFrameFlushDirty function is run ok and parent_ is not null
     */
    ZERO->parent_ = ONE;
    ZERO->UINode::MarkNeedFrameFlushDirty(extraFLAG);
    ASSERT_NE(ZERO->parent_.Upgrade(), nullptr);
    ZERO->Clean();
    ZERO->parent_.Reset();
    /**
     * @tc.steps: step5. set propertyChangeFlag_ is PROPERTY_UPDATE_LAYOUT and call the MarkNeedFrameFlushDirty
     * @tc.expected: step5. the MarkNeedFrameFlushDirty function is run ok
     */
    extraFLAG = PROPERTY_UPDATE_LAYOUT;
    ZERO->layoutProperty_->propertyChangeFlag_ = PROPERTY_UPDATE_LAYOUT;
    ONE->layoutProperty_->propertyChangeFlag_ = PROPERTY_UPDATE_LAYOUT;

    ZERO->UINode::MarkNeedFrameFlushDirty(extraFLAG);
    EXPECT_EQ(ZERO->parent_.Upgrade(), nullptr);
    /**
     * @tc.steps: step6. set one parent_ for ONE and call the MarkNeedFrameFlushDirty
     * @tc.expected: step6. the MarkNeedFrameFlushDirty function is run ok and parent_ is not null
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
     * @tc.expected: step1. the MarkNeedSyncRenderTree function is run ok
     */
    ZERO->UINode::MarkNeedSyncRenderTree();
    EXPECT_EQ(ZERO->parent_.Upgrade(), nullptr);
    /**
     * @tc.steps: step2. set ZERO->parent_ is null and call RebuildRenderContextTree
     * @tc.expected: step2. the RebuildRenderContextTree function is run ok
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
     * @tc.expected: step1. onMainTree_ is false
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
     * @tc.expected: step1. children_.size is 1 and the AdjustLayoutWrapperTree function is run ok
     */
    ZERO->AddChild(ONE, 1, false);
    RefPtr<LayoutWrapper> retLayoutWrapper = ZERO->UINode::CreateLayoutWrapper(true, true);
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
     * @tc.expected: step1. children_.size is 1 and the GenerateOneDepthVisibleFrame function is run ok
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
     * @tc.expected: step1. children_.size is 1 and the GenerateOneDepthAllFrame function is run ok
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
     * @tc.expected: step1. the return value is OUT_OF_REGION
     */
    TouchTestResult result;
    TouchRestrict restrict;

    const PointF GLOBAL_POINT { 20.0f, 20.0f };
    const PointF LOCAL_POINT { 15.0f, 15.0f };

    ZERO->AddChild(ONE, 1, false);
    HitTestResult retResult = ZERO->UINode::TouchTest(GLOBAL_POINT, LOCAL_POINT, std::move(restrict), result, 1);
    EXPECT_EQ(retResult, HitTestResult::OUT_OF_REGION);
    ZERO->Clean();
}

/**
 * @tc.name: UINodeTestNg024
 * @tc.desc: Test ui node method
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg024, TestSize.Level1)
{
    /**
     * @tc.steps: step1. add one child for ZERO and call TouchTest
     * @tc.expected: step1. the return value is OUT_OF_REGION
     */
    MouseTestResult onMouseResult;
    MouseTestResult onHoverResult;
    RefPtr<FrameNode> TEST_HOVERNODE =
        FrameNode::CreateFrameNode("hovernode", 100, AceType::MakeRefPtr<Pattern>(), true);

    const PointF GLOBAL_POINT { 20.0f, 20.0f };
    const PointF LOCAL_POINT { 15.0f, 15.0f };

    ZERO->AddChild(TEST_HOVERNODE, 1, false);
    HitTestResult retResult =
        ZERO->UINode::MouseTest(GLOBAL_POINT, LOCAL_POINT, onMouseResult, onHoverResult, TEST_HOVERNODE);
    EXPECT_EQ(retResult, HitTestResult::BUBBLING);
    ZERO->Clean();
}

/**
 * @tc.name: UINodeTestNg025
 * @tc.desc: Test ui node method
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNg, UINodeTestNg025, TestSize.Level1)
{
    /**
     * @tc.steps: step1. add one child for ZERO and call AxisTest
     * @tc.expected: step1. the return value is OUT_OF_REGION
     */
    AxisTestResult onAxisResult;

    const PointF GLOBAL_POINT { 20.0f, 20.0f };
    const PointF LOCAL_POINT { 15.0f, 15.0f };

    ZERO->AddChild(ONE, 1, false);
    HitTestResult retResult = ZERO->UINode::AxisTest(GLOBAL_POINT, LOCAL_POINT, onAxisResult);
    EXPECT_EQ(retResult, HitTestResult::OUT_OF_REGION);
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
     * @tc.expected: step1. the return retCount is 1
     */
    ZERO->AddChild(ONE, 1, false);
    int32_t retCount = ZERO->UINode::FrameCount();
    EXPECT_EQ(retCount, 1);
    /**
     * @tc.steps: step2. add two child for ZERO and call TotalChildCount
     * @tc.expected: step2. the return retCount is 2
     */
    ZERO->AddChild(TWO, 2, false);
    retCount = ZERO->TotalChildCount();
    EXPECT_EQ(retCount, 2);
    /**
     * @tc.steps: step3. add three child for ZERO and call TotalChildCount
     * @tc.expected: step3. the return retCount is 3
     */
    ZERO->AddChild(THREE, 3, false);
    retCount = ZERO->TotalChildCount();
    EXPECT_EQ(retCount, 3);
    /**
     * @tc.steps: step4add fourild for ZERO and call TotalChildCount
     * @tc.expected: step4 the return retCount is 4
     */
    ZERO->AddChild(FOUR, 4, false);
    retCount = ZERO->TotalChildCount();
    EXPECT_EQ(retCount, 4);
    ZERO->Clean();
    /**
     * @tc.steps: step5. clean ZERO's child and TotalChildCount
     * @tc.expected: step5. the return retCount is 0
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
     * @tc.expected: step1. the Build function is run ok
     */
    ZERO->AddChild(ONE, 1, false);
    ZERO->Build();
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
     * @tc.expected: step1. the SetActive function is run ok
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
     * @tc.steps: step1. add one child for ZERO and call OnVisibleChange
     * @tc.expected: step1. the OnVisibleChange function is run ok
     */
    ZERO->AddChild(ONE, 1, false);
    ZERO->UINode::OnVisibleChange(true);
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
     * @tc.expected: step1. the return pair1.first is true and pair1.second is 0
     */
    ZERO->AddChild(ONE, 1, false);
    auto pair = ZERO->GetChildFlatIndex(1);
    EXPECT_TRUE(pair.first);
    EXPECT_EQ(pair.second, 0);
    ZERO->Clean();
    /**
     * @tc.steps: step1. AddChild TESTUINode to ZERO and GetChildFlatIndex
     * @tc.expected: step1. the return pair1.first is false and pair1.second is 1
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
     * @tc.expected: step1. childrenUpdatedFrom_ is 1
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
     * @tc.expected: step1. the return retMark is false
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
     * @tc.expected: step1. children_.size = 0
     */
    ZERO->SetChildrenInDestroying();
    EXPECT_EQ(ZERO->children_.size(), 0);
    ZERO->Clean();
    /**
     * @tc.steps: step1. add two child to ZERO and call SetChildrenInDestroying
     * @tc.expected: step1. children_.size = 2
     */
    ZERO->AddChild(ONE, 1, false);
    ZERO->AddChild(TWO, 2, false);
    ZERO->SetChildrenInDestroying();
    EXPECT_EQ(ZERO->children_.size(), 2);
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
     * @tc.expected: step1. children_.size = 1
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
     * @tc.expected: step1. children_.size = 0
     */
    ZERO->AddChild(nullptr, 1, false);
    EXPECT_EQ(ZERO->children_.size(), 0);
    /**
     * @tc.steps: step2. AddChild
     * @tc.expected: step2. children_.size = 1
     */
    ZERO->AddChild(TWO, 1, false);
    EXPECT_EQ(ZERO->children_.size(), 1);
    /**
     * @tc.steps: step3. call the RemoveChild funtion and set input is null
     * @tc.expected: step3. the return value is children_.end()
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
     * @tc.expected: step1. the return value is return nullptr
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
     * @tc.expected: step1. children_.size() is 0
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
     * @tc.expected: step1. the MarkDirtyNode function is run ok.
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
     * @tc.expected: step1. the return value is null
     */
    RefPtr<LayoutWrapper> retLayoutWrapper = ZERO->UINode::CreateLayoutWrapper(true, true);
    EXPECT_EQ(retLayoutWrapper, nullptr);
    /**
     * @tc.steps: step1. add one child for ZERO and call CreateLayoutWrapper
     * @tc.expected: step1. the return value is null
     */
    ZERO->AddChild(ONE, 1, false);
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
     * @tc.expected: step1. children_.size() is 2
     */
    auto it = std::find(ZERO->children_.begin(), ZERO->children_.end(), ZERO);
    ZERO->onMainTree_ = true;
    ZERO->DoAddChild(it, ONE, false);
    ZERO->DoAddChild(it, TWO, true);
    EXPECT_EQ(ZERO->children_.size(), 2);
}
} // namespace OHOS::Ace::NG
