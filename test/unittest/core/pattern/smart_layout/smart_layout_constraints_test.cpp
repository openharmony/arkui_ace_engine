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
#include "core/components_ng/pattern/smart_layout/engine/smart_layout_constraints.h"
#include "core/components_ng/pattern/smart_layout/engine/smart_layout_node.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class SmartLayoutConstraintsTest : public testing::Test {
public:
    static void SetUpTestSuite() {}
    static void TearDownTestSuite() {}
    void SetUp() override {}
    void TearDown() override {}
};

/**
 * @tc.name: SmartLayoutConstraintsTest001
 * @tc.desc: Test AddDefaultConstraints with simple setup
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutConstraintsTest, SmartLayoutConstraintsTest001, TestSize.Level1)
{
    auto rootNode = SmartLayoutNode::CreateRootNode();
    rootNode->SetLayoutType(SmartLayoutType::COLUMN);
    rootNode->SetFixedSizeConstraints(200.0, 300.0);

    std::vector<ChildLayoutInfo> childInfos;

    ChildLayoutInfo info;
    info.id = 1;
    info.width = 100.0;
    info.height = 50.0;
    info.offsetX = 0.0;
    info.offsetY = 0.0;
    childInfos.push_back(info);

    rootNode->CreateChildrenFromInfos(childInfos);

    SmartLayoutConstraints constraints;
    constraints.AddDefaultConstraints(*rootNode);

    bool result = rootNode->SolveLayout();
    EXPECT_TRUE(result);

    rootNode->SyncData();
    auto& children = rootNode->GetChildren();
    EXPECT_EQ(children.size(), 1);

    auto& child = children[0];
    child->SyncData();
    EXPECT_GE(child->GetSize().width.value, 0.0);
    EXPECT_GE(child->GetSize().height.value, 0.0);
    EXPECT_GE(child->GetPosition().offsetX.value, 0.0);
    EXPECT_GE(child->GetPosition().offsetY.value, 0.0);
}

/**
 * @tc.name: SmartLayoutConstraintsTest002
 * @tc.desc: Test AddColumnConstraints with multiple children
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutConstraintsTest, SmartLayoutConstraintsTest002, TestSize.Level1)
{
    auto rootNode = SmartLayoutNode::CreateRootNode();
    rootNode->SetLayoutType(SmartLayoutType::COLUMN);
    rootNode->SetLayoutSize(200.0, 400.0);

    std::vector<ChildLayoutInfo> childInfos;

    ChildLayoutInfo info1;
    info1.id = 1;
    info1.width = 100.0;
    info1.height = 80.0;
    info1.offsetX = 0.0;
    info1.offsetY = 0.0;
    childInfos.push_back(info1);

    ChildLayoutInfo info2;
    info2.id = 2;
    info2.width = 90.0;
    info2.height = 100.0;
    info2.offsetX = 0.0;
    info2.offsetY = 100.0;
    childInfos.push_back(info2);

    ChildLayoutInfo info3;
    info3.id = 3;
    info3.width = 80.0;
    info3.height = 60.0;
    info3.offsetX = 0.0;
    info3.offsetY = 210.0;
    childInfos.push_back(info3);

    rootNode->CreateChildrenFromInfos(childInfos);

    SmartLayoutConstraints constraints;
    constraints.AddColumnConstraints(*rootNode);

    bool result = rootNode->SolveLayout();
    EXPECT_TRUE(result);

    rootNode->SyncData();
    auto& children = rootNode->GetChildren();
    EXPECT_EQ(children.size(), 3);

    // Verify children are properly positioned
    for (auto& child : children) {
        child->SyncData();
        EXPECT_GE(child->GetSize().width.value, 0.0);
        EXPECT_GE(child->GetSize().height.value, 0.0);
        EXPECT_GE(child->GetPosition().offsetX.value, 0.0);
        EXPECT_GE(child->GetPosition().offsetY.value, 0.0);
    }
}

/**
 * @tc.name: SmartLayoutConstraintsTest003
 * @tc.desc: Test AddRowConstraints with multiple children
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutConstraintsTest, SmartLayoutConstraintsTest003, TestSize.Level1)
{
    auto rootNode = SmartLayoutNode::CreateRootNode();
    rootNode->SetLayoutType(SmartLayoutType::ROW);
    rootNode->SetLayoutSize(500.0, 100.0);

    std::vector<ChildLayoutInfo> childInfos;

    ChildLayoutInfo info1;
    info1.id = 1;
    info1.width = 150.0;
    info1.height = 50.0;
    info1.offsetX = 0.0;
    info1.offsetY = 0.0;
    childInfos.push_back(info1);

    ChildLayoutInfo info2;
    info2.id = 2;
    info2.width = 200.0;
    info2.height = 60.0;
    info2.offsetX = 160.0;
    info2.offsetY = 0.0;
    childInfos.push_back(info2);

    ChildLayoutInfo info3;
    info3.id = 3;
    info3.width = 100.0;
    info3.height = 40.0;
    info3.offsetX = 370.0;
    info3.offsetY = 0.0;
    childInfos.push_back(info3);

    rootNode->CreateChildrenFromInfos(childInfos);

    SmartLayoutConstraints constraints;
    constraints.AddRowConstraints(*rootNode);

    bool result = rootNode->SolveLayout();
    EXPECT_TRUE(result);

    rootNode->SyncData();
    auto& children = rootNode->GetChildren();
    EXPECT_EQ(children.size(), 3);

    // Verify children are properly positioned horizontally
    for (auto& child : children) {
        child->SyncData();
        EXPECT_GE(child->GetSize().width.value, 0.0);
        EXPECT_GE(child->GetSize().height.value, 0.0);
        EXPECT_GE(child->GetPosition().offsetX.value, 0.0);
        EXPECT_GE(child->GetPosition().offsetY.value, 0.0);
    }
}

/**
 * @tc.name: SmartLayoutConstraintsTest004
 * @tc.desc: Test CalculateChildStatistics with multiple children
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutConstraintsTest, SmartLayoutConstraintsTest004, TestSize.Level1)
{
    auto rootNode = SmartLayoutNode::CreateRootNode();
    rootNode->SetLayoutType(SmartLayoutType::COLUMN);

    std::vector<ChildLayoutInfo> childInfos;

    ChildLayoutInfo info1;
    info1.id = 1;
    info1.width = 100.0;
    info1.height = 50.0;
    childInfos.push_back(info1);

    ChildLayoutInfo info2;
    info2.id = 2;
    info2.width = 80.0;
    info2.height = 120.0;
    childInfos.push_back(info2);

    ChildLayoutInfo info3;
    info3.id = 3;
    info3.width = 150.0;
    info3.height = 30.0;
    childInfos.push_back(info3);

    rootNode->CreateChildrenFromInfos(childInfos);

    ChildStatistics stats = SmartLayoutConstraints::CalculateChildStatistics(*rootNode);
    EXPECT_EQ(stats.childCount, 3);
    EXPECT_EQ(stats.sumOfAllChildHeight, 200.0);
    EXPECT_EQ(stats.sumOfAllChildWidth, 330.0);
    EXPECT_EQ(stats.maxChildWidth, 150.0);
    EXPECT_EQ(stats.maxChildHeight, 120.0);
}

/**
 * @tc.name: SmartLayoutConstraintsTest005
 * @tc.desc: Test CalculateChildStatistics with empty children
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutConstraintsTest, SmartLayoutConstraintsTest005, TestSize.Level1)
{
    auto rootNode = SmartLayoutNode::CreateRootNode();
    rootNode->SetLayoutType(SmartLayoutType::COLUMN);

    ChildStatistics stats = SmartLayoutConstraints::CalculateChildStatistics(*rootNode);
    EXPECT_EQ(stats.childCount, 0);
    EXPECT_EQ(stats.sumOfAllChildHeight, 0.0);
    EXPECT_EQ(stats.sumOfAllChildWidth, 0.0);
    EXPECT_EQ(stats.maxChildWidth, 0.0);
    EXPECT_EQ(stats.maxChildHeight, 0.0);
}

/**
 * @tc.name: SmartLayoutConstraintsTest006
 * @tc.desc: Test AddRowConstraints with overflow children
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutConstraintsTest, SmartLayoutConstraintsTest006, TestSize.Level1)
{
    auto rootNode = SmartLayoutNode::CreateRootNode();
    rootNode->SetLayoutType(SmartLayoutType::ROW);
    rootNode->SetLayoutSize(300.0, 100.0);

    std::vector<ChildLayoutInfo> childInfos;

    ChildLayoutInfo info1;
    info1.id = 1;
    info1.width = 150.0;
    info1.height = 50.0;
    info1.offsetX = 0.0;
    info1.offsetY = 0.0;
    childInfos.push_back(info1);

    ChildLayoutInfo info2;
    info2.id = 2;
    info2.width = 200.0;
    info2.height = 60.0;
    info2.offsetX = 160.0;
    info2.offsetY = 0.0;
    childInfos.push_back(info2);

    ChildLayoutInfo info3;
    info3.id = 3;
    info3.width = 100.0;
    info3.height = 40.0;
    info3.offsetX = 370.0;
    info3.offsetY = 0.0;
    childInfos.push_back(info3);

    rootNode->CreateChildrenFromInfos(childInfos);

    SmartLayoutConstraints constraints;
    constraints.AddRowConstraints(*rootNode);

    bool result = rootNode->SolveLayout();
    EXPECT_TRUE(result);

    rootNode->SyncData();
    auto& children = rootNode->GetChildren();
    EXPECT_EQ(children.size(), 3);

    for (auto& child : children) {
        child->SyncData();
        EXPECT_GE(child->GetSize().width.value, 0.0);
        EXPECT_GE(child->GetSize().height.value, 0.0);
    }
}

/**
 * @tc.name: SmartLayoutConstraintsScaleUpTest001
 * @tc.desc: Test AddScaleUpConstraints - basic symmetric scale-up
 *           Container: 400x400, Child at (100,100) size 200x200
 *           BoundingBox: (100,100,200,200), emptyRatio=0.75 > 0.3
 *           With 10% margin: upScale=min(400*0.9/200)=1.8
 *           Expected: child scaled to 360x360 centered at (20,20)
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutConstraintsTest, SmartLayoutConstraintsScaleUpTest001, TestSize.Level1)
{
    auto rootNode = SmartLayoutNode::CreateRootNode();
    rootNode->SetLayoutType(SmartLayoutType::COLUMN);
    rootNode->SetLayoutSize(400.0, 400.0);
    rootNode->SetFixedSizeConstraints(400.0, 400.0);

    std::vector<ChildLayoutInfo> childInfos;
    ChildLayoutInfo info1;
    info1.id = 1;
    info1.width = 200.0;
    info1.height = 200.0;
    info1.offsetX = 100.0;
    info1.offsetY = 100.0;
    childInfos.push_back(info1);

    rootNode->CreateChildrenFromInfos(childInfos);

    // Set bounding box
    auto boundingBox = rootNode->GetChildrenBoundingBox();
    EXPECT_TRUE(boundingBox.IsValid());
    EXPECT_DOUBLE_EQ(boundingBox.offsetX, 100.0);
    EXPECT_DOUBLE_EQ(boundingBox.offsetY, 100.0);
    EXPECT_DOUBLE_EQ(boundingBox.width, 200.0);
    EXPECT_DOUBLE_EQ(boundingBox.height, 200.0);
    rootNode->SetBoundingBox(boundingBox);

    // Apply scale-up constraints
    SmartLayoutConstraints constraints;
    constraints.AddScaleUpConstraints(*rootNode, 0.3);

    bool result = rootNode->SolveLayout();
    EXPECT_TRUE(result);

    // Verify scale: min(400*0.9/200, 400*0.9/200) = 1.8
    EXPECT_NEAR(rootNode->GetScaleInfo().sizeScale.value, 1.8, 0.01);

    // Verify child: size 360x360, centered at (20,20)
    auto& children = rootNode->GetChildren();
    EXPECT_EQ(children.size(), 1);
    auto& child = children[0];
    EXPECT_NEAR(child->GetSize().width.value, 360.0, 0.01);
    EXPECT_NEAR(child->GetSize().height.value, 360.0, 0.01);
    EXPECT_NEAR(child->GetPosition().offsetX.value, 20.0, 0.01);
    EXPECT_NEAR(child->GetPosition().offsetY.value, 20.0, 0.01);
}

/**
 * @tc.name: SmartLayoutConstraintsScaleUpTest002
 * @tc.desc: Test AddScaleUpConstraints - asymmetric (width-limited)
 *           Container: 600x400, Children BoundingBox: (200,150,200,100)
 *           emptyRatio = 1 - 20000/240000 = 0.917 > 0.3
 *           With 10% margin: maxScaleX=2.7, maxScaleY=3.6, upScale=2.7 (width-limited)
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutConstraintsTest, SmartLayoutConstraintsScaleUpTest002, TestSize.Level1)
{
    auto rootNode = SmartLayoutNode::CreateRootNode();
    rootNode->SetLayoutType(SmartLayoutType::ROW);
    rootNode->SetLayoutSize(600.0, 400.0);
    rootNode->SetFixedSizeConstraints(600.0, 400.0);

    std::vector<ChildLayoutInfo> childInfos;
    ChildLayoutInfo info1;
    info1.id = 1;
    info1.width = 100.0;
    info1.height = 100.0;
    info1.offsetX = 200.0;
    info1.offsetY = 150.0;
    childInfos.push_back(info1);

    ChildLayoutInfo info2;
    info2.id = 2;
    info2.width = 100.0;
    info2.height = 100.0;
    info2.offsetX = 300.0;
    info2.offsetY = 150.0;
    childInfos.push_back(info2);

    rootNode->CreateChildrenFromInfos(childInfos);

    auto boundingBox = rootNode->GetChildrenBoundingBox();
    EXPECT_TRUE(boundingBox.IsValid());
    EXPECT_DOUBLE_EQ(boundingBox.offsetX, 200.0);
    EXPECT_DOUBLE_EQ(boundingBox.offsetY, 150.0);
    EXPECT_DOUBLE_EQ(boundingBox.width, 200.0);
    EXPECT_DOUBLE_EQ(boundingBox.height, 100.0);
    rootNode->SetBoundingBox(boundingBox);

    SmartLayoutConstraints constraints;
    constraints.AddScaleUpConstraints(*rootNode, 0.3);

    bool result = rootNode->SolveLayout();
    EXPECT_TRUE(result);

    // upScale = min(600*0.9/200, 400*0.9/100) = min(2.7, 3.6) = 2.7
    EXPECT_NEAR(rootNode->GetScaleInfo().sizeScale.value, 2.7, 0.01);

    // centerOffsetX = (600 - 200*2.7) / 2 = 30
    // centerOffsetY = (400 - 100*2.7) / 2 = 65
    auto& children = rootNode->GetChildren();
    EXPECT_EQ(children.size(), 2);

    // child1: relX=0, relY=0, newX=0*2.7+30=30, newY=0*2.7+65=65, size=270x270
    EXPECT_NEAR(children[0]->GetSize().width.value, 270.0, 0.01);
    EXPECT_NEAR(children[0]->GetSize().height.value, 270.0, 0.01);
    EXPECT_NEAR(children[0]->GetPosition().offsetX.value, 30.0, 0.01);
    EXPECT_NEAR(children[0]->GetPosition().offsetY.value, 65.0, 0.01);

    // child2: relX=100, relY=0, newX=100*2.7+30=300, newY=0*2.7+65=65, size=270x270
    EXPECT_NEAR(children[1]->GetSize().width.value, 270.0, 0.01);
    EXPECT_NEAR(children[1]->GetSize().height.value, 270.0, 0.01);
    EXPECT_NEAR(children[1]->GetPosition().offsetX.value, 300.0, 0.01);
    EXPECT_NEAR(children[1]->GetPosition().offsetY.value, 65.0, 0.01);
}

/**
 * @tc.name: SmartLayoutConstraintsScaleUpTest003
 * @tc.desc: Test AddScaleUpConstraints - no scale-up when emptyRatio below threshold
 *           Container: 200x200, Child at (10,10) size 180x180
 *           BoundingBox: (10,10,180,180), emptyRatio = 1 - 32400/40000 = 0.19 < 0.3
 *           Expected: no scale-up applied, sizeScale remains 1.0
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutConstraintsTest, SmartLayoutConstraintsScaleUpTest003, TestSize.Level1)
{
    auto rootNode = SmartLayoutNode::CreateRootNode();
    rootNode->SetLayoutType(SmartLayoutType::COLUMN);
    rootNode->SetLayoutSize(200.0, 200.0);
    rootNode->SetFixedSizeConstraints(200.0, 200.0);

    std::vector<ChildLayoutInfo> childInfos;
    ChildLayoutInfo info1;
    info1.id = 1;
    info1.width = 180.0;
    info1.height = 180.0;
    info1.offsetX = 10.0;
    info1.offsetY = 10.0;
    childInfos.push_back(info1);

    rootNode->CreateChildrenFromInfos(childInfos);

    auto boundingBox = rootNode->GetChildrenBoundingBox();
    rootNode->SetBoundingBox(boundingBox);

    SmartLayoutConstraints constraints;
    constraints.AddScaleUpConstraints(*rootNode, 0.3);

    // Since emptyRatio (0.19) < threshold (0.3), no scale-up constraints are added.
    // Only the 2 container size constraints remain, so SolveLayout returns false.
    bool result = rootNode->SolveLayout();
    EXPECT_FALSE(result);

    // sizeScale should remain at default (1.0) since no constraint was added
    EXPECT_NEAR(rootNode->GetScaleInfo().sizeScale.value, 1.0, 0.01);
}

/**
 * @tc.name: SmartLayoutConstraintsScaleUpTest004
 * @tc.desc: Test AddScaleUpConstraints - height-limited scale-up with centering
 *           Container: 400x200, Children BoundingBox: (0,0,200,100)
 *           emptyRatio = 1 - 20000/80000 = 0.75 > 0.3
 *           With 10% margin: maxScaleX=1.8, maxScaleY=1.8, upScale=1.8
 *           centerOffset = (20, 10)
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutConstraintsTest, SmartLayoutConstraintsScaleUpTest004, TestSize.Level1)
{
    auto rootNode = SmartLayoutNode::CreateRootNode();
    rootNode->SetLayoutType(SmartLayoutType::ROW);
    rootNode->SetLayoutSize(400.0, 200.0);
    rootNode->SetFixedSizeConstraints(400.0, 200.0);

    std::vector<ChildLayoutInfo> childInfos;
    ChildLayoutInfo info1;
    info1.id = 1;
    info1.width = 100.0;
    info1.height = 100.0;
    info1.offsetX = 0.0;
    info1.offsetY = 0.0;
    childInfos.push_back(info1);

    ChildLayoutInfo info2;
    info2.id = 2;
    info2.width = 100.0;
    info2.height = 100.0;
    info2.offsetX = 100.0;
    info2.offsetY = 0.0;
    childInfos.push_back(info2);

    rootNode->CreateChildrenFromInfos(childInfos);

    auto boundingBox = rootNode->GetChildrenBoundingBox();
    EXPECT_DOUBLE_EQ(boundingBox.offsetX, 0.0);
    EXPECT_DOUBLE_EQ(boundingBox.offsetY, 0.0);
    EXPECT_DOUBLE_EQ(boundingBox.width, 200.0);
    EXPECT_DOUBLE_EQ(boundingBox.height, 100.0);
    rootNode->SetBoundingBox(boundingBox);

    SmartLayoutConstraints constraints;
    constraints.AddScaleUpConstraints(*rootNode, 0.3);

    bool result = rootNode->SolveLayout();
    EXPECT_TRUE(result);

    // upScale = min(400*0.9/200, 200*0.9/100) = min(1.8, 1.8) = 1.8
    EXPECT_NEAR(rootNode->GetScaleInfo().sizeScale.value, 1.8, 0.01);

    // centerOffsetX = (400 - 200*1.8) / 2 = 20
    // centerOffsetY = (200 - 100*1.8) / 2 = 10
    auto& children = rootNode->GetChildren();
    EXPECT_EQ(children.size(), 2);

    // child1: relX=0, relY=0, newX=20, newY=10, size=180x180
    EXPECT_NEAR(children[0]->GetSize().width.value, 180.0, 0.01);
    EXPECT_NEAR(children[0]->GetSize().height.value, 180.0, 0.01);
    EXPECT_NEAR(children[0]->GetPosition().offsetX.value, 20.0, 0.01);
    EXPECT_NEAR(children[0]->GetPosition().offsetY.value, 10.0, 0.01);

    // child2: relX=100, relY=0, newX=100*1.8+20=200, newY=10, size=180x180
    EXPECT_NEAR(children[1]->GetSize().width.value, 180.0, 0.01);
    EXPECT_NEAR(children[1]->GetSize().height.value, 180.0, 0.01);
    EXPECT_NEAR(children[1]->GetPosition().offsetX.value, 200.0, 0.01);
    EXPECT_NEAR(children[1]->GetPosition().offsetY.value, 10.0, 0.01);
}

} // namespace OHOS::Ace::NG
