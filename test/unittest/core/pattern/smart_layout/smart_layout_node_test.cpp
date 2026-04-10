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

#include <gtest/gtest.h>

#define private public
#define protected public
#include "core/components_ng/pattern/smart_layout/engine/smart_layout_node.h"
#include "core/components_ng/pattern/smart_layout/engine/smart_layout_context.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class SmartLayoutNodeTest : public testing::Test {
public:
    static void SetUpTestSuite() {}
    static void TearDownTestSuite() {}
    void SetUp() override {}
    void TearDown() override {}
};

/**
 * @tc.name: SmartLayoutNodeTest001
 * @tc.desc: Test CreateRootNode with default name
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutNodeTest, SmartLayoutNodeTest001, TestSize.Level1)
{
    auto rootNode = SmartLayoutNode::CreateRootNode();
    EXPECT_NE(rootNode, nullptr);
    EXPECT_NE(rootNode->GetEngine(), nullptr);
    EXPECT_EQ(rootNode->GetName(), "root");
}

/**
 * @tc.name: SmartLayoutNodeTest002
 * @tc.desc: Test CreateRootNode with custom name
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutNodeTest, SmartLayoutNodeTest002, TestSize.Level1)
{
    auto rootNode = SmartLayoutNode::CreateRootNode("custom_root");
    EXPECT_NE(rootNode, nullptr);
    EXPECT_NE(rootNode->GetEngine(), nullptr);
    EXPECT_EQ(rootNode->GetName(), "custom_root");
}

/**
 * @tc.name: SmartLayoutNodeTest003
 * @tc.desc: Test SetFixedSize
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutNodeTest, SmartLayoutNodeTest003, TestSize.Level1)
{
    auto rootNode = SmartLayoutNode::CreateRootNode("test");
    rootNode->SetFixedSize(100.0, 200.0);

    auto size = rootNode->GetSize();
    EXPECT_EQ(size.width.value, 100.0);
    EXPECT_EQ(size.height.value, 200.0);
}

/**
 * @tc.name: SmartLayoutNodeTest004
 * @tc.desc: Test SetInitialPosition
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutNodeTest, SmartLayoutNodeTest004, TestSize.Level1)
{
    auto rootNode = SmartLayoutNode::CreateRootNode("test");
    rootNode->SetInitialPosition(10.0, 20.0);

    auto position = rootNode->GetPosition();
    EXPECT_EQ(position.offsetX.value, 10.0);
    EXPECT_EQ(position.offsetY.value, 20.0);
}

/**
 * @tc.name: SmartLayoutNodeTest005
 * @tc.desc: Test SetFixedSizeConstraints
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutNodeTest, SmartLayoutNodeTest005, TestSize.Level1)
{
    auto rootNode = SmartLayoutNode::CreateRootNode("test");
    rootNode->SetFixedSizeConstraints(300.0, 400.0);

    auto size = rootNode->GetSize();
    EXPECT_EQ(size.width.value, 300.0);
    EXPECT_EQ(size.height.value, 400.0);
}

/**
 * @tc.name: SmartLayoutNodeTest006
 * @tc.desc: Test LayoutContext default values
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutNodeTest, SmartLayoutNodeTest006, TestSize.Level1)
{
    auto rootNode = SmartLayoutNode::CreateRootNode();
    auto& context = rootNode->GetContext();

    EXPECT_EQ(context.layoutType, SmartLayoutType::UNKNOWN);
    EXPECT_EQ(context.mainAxisAlign, SmartLayoutAlign::FLEX_START);
    EXPECT_EQ(context.crossAxisAlign, SmartLayoutAlign::CENTER);
    EXPECT_EQ(context.size.Width(), 0.0);
    EXPECT_EQ(context.size.Height(), 0.0);
}

/**
 * @tc.name: SmartLayoutNodeTest007
 * @tc.desc: Test SetLayoutType
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutNodeTest, SmartLayoutNodeTest007, TestSize.Level1)
{
    auto rootNode = SmartLayoutNode::CreateRootNode();
    rootNode->SetLayoutType(SmartLayoutType::COLUMN);
    EXPECT_EQ(rootNode->GetLayoutType(), SmartLayoutType::COLUMN);

    rootNode->SetLayoutType(SmartLayoutType::ROW);
    EXPECT_EQ(rootNode->GetLayoutType(), SmartLayoutType::ROW);
}

/**
 * @tc.name: SmartLayoutNodeTest008
 * @tc.desc: Test SetMainAxisAlign and SetCrossAxisAlign
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutNodeTest, SmartLayoutNodeTest008, TestSize.Level1)
{
    auto rootNode = SmartLayoutNode::CreateRootNode();

    rootNode->SetMainAxisAlign(SmartLayoutAlign::CENTER);
    EXPECT_EQ(rootNode->GetMainAxisAlign(), SmartLayoutAlign::CENTER);

    rootNode->SetCrossAxisAlign(SmartLayoutAlign::FLEX_END);
    EXPECT_EQ(rootNode->GetCrossAxisAlign(), SmartLayoutAlign::FLEX_END);
}

/**
 * @tc.name: SmartLayoutNodeTest009
 * @tc.desc: Test SetLayoutSize
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutNodeTest, SmartLayoutNodeTest009, TestSize.Level1)
{
    auto rootNode = SmartLayoutNode::CreateRootNode();

    rootNode->SetLayoutSize(500.0, 600.0);
    auto size = rootNode->GetLayoutSize();
    EXPECT_EQ(size.Width(), 500.0);
    EXPECT_EQ(size.Height(), 600.0);

    SmartLayoutSize newSize(100.0, 200.0);
    rootNode->SetLayoutSize(newSize);
    EXPECT_EQ(rootNode->GetLayoutSize().Width(), 100.0);
    EXPECT_EQ(rootNode->GetLayoutSize().Height(), 200.0);
}

/**
 * @tc.name: SmartLayoutNodeTest010
 * @tc.desc: Test CreateChildNode with non-Blank child
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutNodeTest, SmartLayoutNodeTest010, TestSize.Level1)
{
    auto rootNode = SmartLayoutNode::CreateRootNode();
    rootNode->SetLayoutType(SmartLayoutType::COLUMN);

    ChildLayoutInfo info;
    info.id = 100;
    info.width = 50.0;
    info.height = 30.0;
    info.offsetX = 0.0;
    info.offsetY = 0.0;
    info.isBlank = false;

    EdgesSpaces spaces;
    spaces.top = 10.0;
    spaces.bottom = 10.0;

    auto childNode = rootNode->CreateChildNode(info, spaces);
    EXPECT_NE(childNode, nullptr);
    EXPECT_EQ(childNode->GetNodeId(), 100);
    EXPECT_EQ(childNode->GetSize().width.value, 50.0);
    EXPECT_EQ(childNode->GetSize().height.value, 30.0);
}

/**
 * @tc.name: SmartLayoutNodeTest011
 * @tc.desc: Test CreateChildNode with Blank child in Column layout
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutNodeTest, SmartLayoutNodeTest011, TestSize.Level1)
{
    auto rootNode = SmartLayoutNode::CreateRootNode();
    rootNode->SetLayoutType(SmartLayoutType::COLUMN);

    ChildLayoutInfo info;
    info.id = 200;
    info.width = 50.0;
    info.height = 30.0;
    info.isBlank = true;

    EdgesSpaces spaces;
    auto childNode = rootNode->CreateChildNode(info, spaces);

    EXPECT_NE(childNode, nullptr);
    EXPECT_EQ(childNode->GetSize().width.value, 50.0);
    EXPECT_EQ(childNode->GetSize().height.value, 0.0);
}

/**
 * @tc.name: SmartLayoutNodeTest012
 * @tc.desc: Test CreateChildNode with Blank child in Row layout
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutNodeTest, SmartLayoutNodeTest012, TestSize.Level1)
{
    auto rootNode = SmartLayoutNode::CreateRootNode();
    rootNode->SetLayoutType(SmartLayoutType::ROW);

    ChildLayoutInfo info;
    info.id = 300;
    info.width = 50.0;
    info.height = 30.0;
    info.isBlank = true;

    EdgesSpaces spaces;
    auto childNode = rootNode->CreateChildNode(info, spaces);

    EXPECT_NE(childNode, nullptr);
    EXPECT_EQ(childNode->GetSize().width.value, 0.0);
    EXPECT_EQ(childNode->GetSize().height.value, 30.0);
}

/**
 * @tc.name: SmartLayoutNodeTest013
 * @tc.desc: Test SetChildren
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutNodeTest, SmartLayoutNodeTest013, TestSize.Level1)
{
    auto rootNode = SmartLayoutNode::CreateRootNode();
    rootNode->SetLayoutType(SmartLayoutType::COLUMN);

    ChildLayoutInfo info1;
    info1.id = 1;
    info1.width = 100.0;
    info1.height = 50.0;

    ChildLayoutInfo info2;
    info2.id = 2;
    info2.width = 100.0;
    info2.height = 50.0;

    EdgesSpaces spaces;
    auto child1 = rootNode->CreateChildNode(info1, spaces);
    auto child2 = rootNode->CreateChildNode(info2, spaces);

    std::vector<std::shared_ptr<SmartLayoutNode>> children = {child1, child2};
    rootNode->SetChildren(children);

    auto& nodeChildren = rootNode->GetChildren();
    EXPECT_EQ(nodeChildren.size(), 2);
    EXPECT_EQ(nodeChildren[0]->GetNodeId(), 1);
    EXPECT_EQ(nodeChildren[1]->GetNodeId(), 2);
    EXPECT_EQ(nodeChildren[0]->GetParent(), rootNode.get());
    EXPECT_EQ(nodeChildren[1]->GetParent(), rootNode.get());
}

/**
 * @tc.name: SmartLayoutNodeTest014
 * @tc.desc: Test CreateChildrenFromInfos
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutNodeTest, SmartLayoutNodeTest014, TestSize.Level1)
{
    auto rootNode = SmartLayoutNode::CreateRootNode();
    rootNode->SetLayoutType(SmartLayoutType::COLUMN);
    rootNode->SetLayoutSize(200.0, 200.0);

    std::vector<ChildLayoutInfo> childInfos;

    ChildLayoutInfo info1;
    info1.id = 10;
    info1.width = 100.0;
    info1.height = 50.0;
    info1.offsetX = 0.0;
    info1.offsetY = 0.0;
    childInfos.push_back(info1);

    ChildLayoutInfo info2;
    info2.id = 20;
    info2.width = 100.0;
    info2.height = 50.0;
    info2.offsetX = 0.0;
    info2.offsetY = 60.0;
    childInfos.push_back(info2);

    rootNode->CreateChildrenFromInfos(childInfos);

    auto& children = rootNode->GetChildren();
    EXPECT_EQ(children.size(), 2);
    EXPECT_EQ(children[0]->GetNodeId(), 10);
    EXPECT_EQ(children[1]->GetNodeId(), 20);
}

/**
 * @tc.name: SmartLayoutNodeTest015
 * @tc.desc: Test CreateChildrenFromInfos with empty vector
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutNodeTest, SmartLayoutNodeTest015, TestSize.Level1)
{
    auto rootNode = SmartLayoutNode::CreateRootNode();
    rootNode->SetLayoutType(SmartLayoutType::COLUMN);

    std::vector<ChildLayoutInfo> emptyInfos;
    rootNode->CreateChildrenFromInfos(emptyInfos);

    auto& children = rootNode->GetChildren();
    EXPECT_EQ(children.size(), 0);
}

/**
 * @tc.name: SmartLayoutNodeTest016
 * @tc.desc: Test CalculateChildSpacing for Column layout
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutNodeTest, SmartLayoutNodeTest016, TestSize.Level1)
{
    auto rootNode = SmartLayoutNode::CreateRootNode();

    ChildLayoutInfo child1;
    child1.offsetY = 0.0;
    child1.height = 50.0;

    ChildLayoutInfo child2;
    child2.offsetY = 70.0;
    child2.height = 30.0;

    double spacing = rootNode->CalculateChildSpacing(child1, child2, SmartLayoutType::COLUMN);
    EXPECT_EQ(spacing, 20.0);
}

/**
 * @tc.name: SmartLayoutNodeTest017
 * @tc.desc: Test CalculateChildSpacing for Row layout
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutNodeTest, SmartLayoutNodeTest017, TestSize.Level1)
{
    auto rootNode = SmartLayoutNode::CreateRootNode();

    ChildLayoutInfo child1;
    child1.offsetX = 0.0;
    child1.width = 100.0;

    ChildLayoutInfo child2;
    child2.offsetX = 120.0;
    child2.width = 50.0;

    double spacing = rootNode->CalculateChildSpacing(child1, child2, SmartLayoutType::ROW);
    EXPECT_EQ(spacing, 20.0);
}

/**
 * @tc.name: SmartLayoutNodeTest018
 * @tc.desc: Test GetChildrenBoundingBox with no children
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutNodeTest, SmartLayoutNodeTest018, TestSize.Level1)
{
    auto rootNode = SmartLayoutNode::CreateRootNode();
    auto boundingBox = rootNode->GetChildrenBoundingBox();

    EXPECT_EQ(boundingBox.offsetX, 0.0);
    EXPECT_EQ(boundingBox.offsetY, 0.0);
    EXPECT_EQ(boundingBox.width, 0.0);
    EXPECT_EQ(boundingBox.height, 0.0);
    EXPECT_FALSE(boundingBox.IsValid());
}

/**
 * @tc.name: SmartLayoutNodeTest019
 * @tc.desc: Test SolveLayout with simple constraints
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutNodeTest, SmartLayoutNodeTest019, TestSize.Level1)
{
    auto rootNode = SmartLayoutNode::CreateRootNode();
    rootNode->SetFixedSizeConstraints(100.0, 200.0);

    bool result = rootNode->SolveLayout();
    EXPECT_TRUE(result);

    rootNode->SyncData();
    EXPECT_EQ(rootNode->GetSize().width.value, 100.0);
    EXPECT_EQ(rootNode->GetSize().height.value, 200.0);
}

/**
 * @tc.name: SmartLayoutNodeTest020
 * @tc.desc: Test SolveLayout returns false for null engine
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutNodeTest, SmartLayoutNodeTest020, TestSize.Level1)
{
    auto rootNode = SmartLayoutNode::CreateRootNode();
    rootNode->engine_ = nullptr;

    bool result = rootNode->SolveLayout();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: SmartLayoutNodeTest021
 * @tc.desc: Test SetSpace and GetMutableSpace
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutNodeTest, SmartLayoutNodeTest021, TestSize.Level1)
{
    auto rootNode = SmartLayoutNode::CreateRootNode();

    EdgesSpaces spaces;
    spaces.left = 5.0;
    spaces.right = 10.0;
    spaces.top = 15.0;
    spaces.bottom = 20.0;

    rootNode->SetSpace(spaces);
    auto& nodeSpace = rootNode->GetSpace();
    EXPECT_EQ(nodeSpace.left, 5.0);
    EXPECT_EQ(nodeSpace.right, 10.0);
    EXPECT_EQ(nodeSpace.top, 15.0);
    EXPECT_EQ(nodeSpace.bottom, 20.0);

    auto& mutableSpace = rootNode->GetMutableSpace();
    mutableSpace.left = 25.0;
    EXPECT_EQ(rootNode->GetSpace().left, 25.0);
}

/**
 * @tc.name: SmartLayoutNodeTest022
 * @tc.desc: Test GetSharedEngine
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutNodeTest, SmartLayoutNodeTest022, TestSize.Level1)
{
    auto rootNode = SmartLayoutNode::CreateRootNode();
    auto sharedEngine = rootNode->GetSharedEngine();
    EXPECT_NE(sharedEngine, nullptr);
    EXPECT_EQ(sharedEngine.get(), rootNode->GetEngine());
}

} // namespace OHOS::Ace::NG