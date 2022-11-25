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
} // namespace OHOS::Ace::NG
