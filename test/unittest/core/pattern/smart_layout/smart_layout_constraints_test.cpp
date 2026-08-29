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
 *           BoundingBox: (100,100,200,200), available area: 376x376
 *           upScale = 376/200 = 1.88
 *           Expected: child scaled to 376x376 centered at (12,12)
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutConstraintsTest, SmartLayoutConstraintsScaleUpTest001, TestSize.Level1)
{
    auto rootNode = SmartLayoutNode::CreateRootNode();
    rootNode->SetLayoutType(SmartLayoutType::COLUMN);
    rootNode->SetLayoutSize(400.0, 400.0);
    rootNode->SetFixedSizeConstraints(400.0, 400.0);
    rootNode->GetContext().contentPadding = 12.0;

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
    constraints.AddScaleUpConstraints(*rootNode);

    bool result = rootNode->SolveLayout();
    EXPECT_TRUE(result);

    // Verify scale: available 376x376, upScale = 376/200 = 1.88
    EXPECT_NEAR(rootNode->GetScaleInfo().sizeScale.value, 1.88, 0.01);

    // Verify child: size 376x376, centered at (12,12)
    auto& children = rootNode->GetChildren();
    EXPECT_EQ(children.size(), 1);
    auto& child = children[0];
    EXPECT_NEAR(child->GetSize().width.value, 376.0, 0.01);
    EXPECT_NEAR(child->GetSize().height.value, 376.0, 0.01);
    EXPECT_NEAR(child->GetPosition().offsetX.value, 12.0, 0.01);
    EXPECT_NEAR(child->GetPosition().offsetY.value, 12.0, 0.01);
}

/**
 * @tc.name: SmartLayoutConstraintsScaleUpTest002
 * @tc.desc: Test AddScaleUpConstraints - asymmetric (width-limited)
 *           Container: 600x400, Children BoundingBox: (200,150,200,100)
 *           Available area: 576x376
 *           maxScaleX=576/200=2.88, maxScaleY=376/100=3.76, upScale=2.88 (width-limited)
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutConstraintsTest, SmartLayoutConstraintsScaleUpTest002, TestSize.Level1)
{
    auto rootNode = SmartLayoutNode::CreateRootNode();
    rootNode->SetLayoutType(SmartLayoutType::ROW);
    rootNode->SetLayoutSize(600.0, 400.0);
    rootNode->SetFixedSizeConstraints(600.0, 400.0);
    rootNode->GetContext().contentPadding = 12.0;

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
    constraints.AddScaleUpConstraints(*rootNode);

    bool result = rootNode->SolveLayout();
    EXPECT_TRUE(result);

    // upScale = min(576/200, 376/100) = min(2.88, 3.76) = 2.88
    EXPECT_NEAR(rootNode->GetScaleInfo().sizeScale.value, 2.88, 0.01);

    // centerOffsetX = (600 - 200*2.88) / 2 = 12
    // centerOffsetY = (400 - 100*2.88) / 2 = 56
    auto& children = rootNode->GetChildren();
    EXPECT_EQ(children.size(), 2);

    // child1: relX=0, relY=0, newX=0*2.88+12=12, newY=0*2.88+56=56, size=288x288
    EXPECT_NEAR(children[0]->GetSize().width.value, 288.0, 0.01);
    EXPECT_NEAR(children[0]->GetSize().height.value, 288.0, 0.01);
    EXPECT_NEAR(children[0]->GetPosition().offsetX.value, 12.0, 0.01);
    EXPECT_NEAR(children[0]->GetPosition().offsetY.value, 56.0, 0.01);

    // child2: relX=100, relY=0, newX=100*2.88+12=300, newY=0*2.88+56=56, size=288x288
    EXPECT_NEAR(children[1]->GetSize().width.value, 288.0, 0.01);
    EXPECT_NEAR(children[1]->GetSize().height.value, 288.0, 0.01);
    EXPECT_NEAR(children[1]->GetPosition().offsetX.value, 300.0, 0.01);
    EXPECT_NEAR(children[1]->GetPosition().offsetY.value, 56.0, 0.01);
}

/**
 * @tc.name: SmartLayoutConstraintsScaleUpTest003
 * @tc.desc: Test AddScaleUpConstraints - no scale-up when bounding box is not
 *           smaller than the available area on both dimensions
 *           Container: 200x200, Child at (10,10) size 180x180
 *           BoundingBox: (10,10,180,180), available area: 176x176
 *           Expected: no scale-up applied, sizeScale remains 1.0
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutConstraintsTest, SmartLayoutConstraintsScaleUpTest003, TestSize.Level1)
{
    auto rootNode = SmartLayoutNode::CreateRootNode();
    rootNode->SetLayoutType(SmartLayoutType::COLUMN);
    rootNode->SetLayoutSize(200.0, 200.0);
    rootNode->SetFixedSizeConstraints(200.0, 200.0);
    rootNode->GetContext().contentPadding = 12.0;

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
    constraints.AddScaleUpConstraints(*rootNode);

    // Since the bounding box (180x180) is not smaller than the available area
    // (176x176) on both dimensions, no scale-up constraints are added.
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
 *           Available area: 376x176
 *           maxScaleX=376/200=1.88, maxScaleY=176/100=1.76, upScale=1.76
 *           centerOffset = (24, 12)
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutConstraintsTest, SmartLayoutConstraintsScaleUpTest004, TestSize.Level1)
{
    auto rootNode = SmartLayoutNode::CreateRootNode();
    rootNode->SetLayoutType(SmartLayoutType::ROW);
    rootNode->SetLayoutSize(400.0, 200.0);
    rootNode->SetFixedSizeConstraints(400.0, 200.0);
    rootNode->GetContext().contentPadding = 12.0;

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
    constraints.AddScaleUpConstraints(*rootNode);

    bool result = rootNode->SolveLayout();
    EXPECT_TRUE(result);

    // upScale = min(376/200, 176/100) = min(1.88, 1.76) = 1.76
    EXPECT_NEAR(rootNode->GetScaleInfo().sizeScale.value, 1.76, 0.01);

    // centerOffsetX = (400 - 200*1.76) / 2 = 24
    // centerOffsetY = (200 - 100*1.76) / 2 = 12
    auto& children = rootNode->GetChildren();
    EXPECT_EQ(children.size(), 2);

    // child1: relX=0, relY=0, newX=24, newY=12, size=176x176
    EXPECT_NEAR(children[0]->GetSize().width.value, 176.0, 0.01);
    EXPECT_NEAR(children[0]->GetSize().height.value, 176.0, 0.01);
    EXPECT_NEAR(children[0]->GetPosition().offsetX.value, 24.0, 0.01);
    EXPECT_NEAR(children[0]->GetPosition().offsetY.value, 12.0, 0.01);

    // child2: relX=100, relY=0, newX=100*1.76+24=200, newY=12, size=176x176
    EXPECT_NEAR(children[1]->GetSize().width.value, 176.0, 0.01);
    EXPECT_NEAR(children[1]->GetSize().height.value, 176.0, 0.01);
    EXPECT_NEAR(children[1]->GetPosition().offsetX.value, 200.0, 0.01);
    EXPECT_NEAR(children[1]->GetPosition().offsetY.value, 12.0, 0.01);
}

/**
 * @tc.name: SmartLayoutConstraintsScaleUpTest005
 * @tc.desc: Test AddScaleUpConstraints - no scale-up when the container is too
 *           small to reserve the content padding on each edge
 *           Container: 20x20, available area: 20-2*12 <= 0
 *           Expected: no scale-up applied, sizeScale remains 1.0
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutConstraintsTest, SmartLayoutConstraintsScaleUpTest005, TestSize.Level1)
{
    auto rootNode = SmartLayoutNode::CreateRootNode();
    rootNode->SetLayoutType(SmartLayoutType::COLUMN);
    rootNode->SetLayoutSize(20.0, 20.0);
    rootNode->SetFixedSizeConstraints(20.0, 20.0);
    rootNode->GetContext().contentPadding = 12.0;

    std::vector<ChildLayoutInfo> childInfos;
    ChildLayoutInfo info1;
    info1.id = 1;
    info1.width = 5.0;
    info1.height = 5.0;
    info1.offsetX = 0.0;
    info1.offsetY = 0.0;
    childInfos.push_back(info1);

    rootNode->CreateChildrenFromInfos(childInfos);

    auto boundingBox = rootNode->GetChildrenBoundingBox();
    rootNode->SetBoundingBox(boundingBox);

    SmartLayoutConstraints constraints;
    constraints.AddScaleUpConstraints(*rootNode);

    // Available area is non-positive, no scale-up constraints are added.
    // Only the 2 container size constraints remain, so SolveLayout returns false.
    bool result = rootNode->SolveLayout();
    EXPECT_FALSE(result);

    // sizeScale should remain at default (1.0) since no constraint was added
    EXPECT_NEAR(rootNode->GetScaleInfo().sizeScale.value, 1.0, 0.01);
}

/**
 * @tc.name: SmartLayoutConstraintsScaleUpTest006
 * @tc.desc: Test AddScaleUpConstraints - default zero content padding
 *           Container: 200x200, Child at (0,0) size 100x100
 *           contentPadding defaults to 0, available area = full container
 *           Expected: upScale = 200/100 = 2.0, child fills the container
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutConstraintsTest, SmartLayoutConstraintsScaleUpTest006, TestSize.Level1)
{
    auto rootNode = SmartLayoutNode::CreateRootNode();
    rootNode->SetLayoutType(SmartLayoutType::COLUMN);
    rootNode->SetLayoutSize(200.0, 200.0);
    rootNode->SetFixedSizeConstraints(200.0, 200.0);

    std::vector<ChildLayoutInfo> childInfos;
    ChildLayoutInfo info1;
    info1.id = 1;
    info1.width = 100.0;
    info1.height = 100.0;
    info1.offsetX = 0.0;
    info1.offsetY = 0.0;
    childInfos.push_back(info1);

    rootNode->CreateChildrenFromInfos(childInfos);

    auto boundingBox = rootNode->GetChildrenBoundingBox();
    rootNode->SetBoundingBox(boundingBox);

    SmartLayoutConstraints constraints;
    constraints.AddScaleUpConstraints(*rootNode);

    bool result = rootNode->SolveLayout();
    EXPECT_TRUE(result);

    // upScale = 200/100 = 2.0, scaled bb fills the container, centered at (0,0)
    EXPECT_NEAR(rootNode->GetScaleInfo().sizeScale.value, 2.0, 0.01);
    auto& children = rootNode->GetChildren();
    EXPECT_EQ(children.size(), 1);
    EXPECT_NEAR(children[0]->GetSize().width.value, 200.0, 0.01);
    EXPECT_NEAR(children[0]->GetSize().height.value, 200.0, 0.01);
    EXPECT_NEAR(children[0]->GetPosition().offsetX.value, 0.0, 0.01);
    EXPECT_NEAR(children[0]->GetPosition().offsetY.value, 0.0, 0.01);
}

} // namespace OHOS::Ace::NG
