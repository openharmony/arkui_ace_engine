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
 * @tc.desc: Test GetSumOfAllChildHeight with empty children
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutConstraintsTest, SmartLayoutConstraintsTest001, TestSize.Level1)
{
    auto rootNode = SmartLayoutNode::CreateRootNode();
    double sum = SmartLayoutConstraints::GetSumOfAllChildHeight(*rootNode);
    EXPECT_EQ(sum, 0.0);
}

/**
 * @tc.name: SmartLayoutConstraintsTest002
 * @tc.desc: Test GetSumOfAllChildHeight with multiple children
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutConstraintsTest, SmartLayoutConstraintsTest002, TestSize.Level1)
{
    auto rootNode = SmartLayoutNode::CreateRootNode();
    rootNode->SetLayoutType(SmartLayoutType::COLUMN);
    rootNode->SetLayoutSize(200.0, 200.0);

    std::vector<ChildLayoutInfo> childInfos;

    ChildLayoutInfo info1;
    info1.id = 1;
    info1.width = 100.0;
    info1.height = 50.0;
    info1.offsetY = 0.0;
    childInfos.push_back(info1);

    ChildLayoutInfo info2;
    info2.id = 2;
    info2.width = 100.0;
    info2.height = 30.0;
    info2.offsetY = 60.0;
    childInfos.push_back(info2);

    ChildLayoutInfo info3;
    info3.id = 3;
    info3.width = 100.0;
    info3.height = 40.0;
    info3.offsetY = 100.0;
    childInfos.push_back(info3);

    rootNode->CreateChildrenFromInfos(childInfos);

    double sum = SmartLayoutConstraints::GetSumOfAllChildHeight(*rootNode);
    EXPECT_EQ(sum, 120.0);
}

/**
 * @tc.name: SmartLayoutConstraintsTest003
 * @tc.desc: Test GetSumOfAllChildWidth with empty children
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutConstraintsTest, SmartLayoutConstraintsTest003, TestSize.Level1)
{
    auto rootNode = SmartLayoutNode::CreateRootNode();
    double sum = SmartLayoutConstraints::GetSumOfAllChildWidth(*rootNode);
    EXPECT_EQ(sum, 0.0);
}

/**
 * @tc.name: SmartLayoutConstraintsTest004
 * @tc.desc: Test GetSumOfAllChildWidth with multiple children
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutConstraintsTest, SmartLayoutConstraintsTest004, TestSize.Level1)
{
    auto rootNode = SmartLayoutNode::CreateRootNode();
    rootNode->SetLayoutType(SmartLayoutType::ROW);
    rootNode->SetLayoutSize(400.0, 200.0);

    std::vector<ChildLayoutInfo> childInfos;

    ChildLayoutInfo info1;
    info1.id = 1;
    info1.width = 100.0;
    info1.height = 50.0;
    info1.offsetX = 0.0;
    childInfos.push_back(info1);

    ChildLayoutInfo info2;
    info2.id = 2;
    info2.width = 150.0;
    info2.height = 50.0;
    info2.offsetX = 110.0;
    childInfos.push_back(info2);

    ChildLayoutInfo info3;
    info3.id = 3;
    info3.width = 80.0;
    info3.height = 50.0;
    info3.offsetX = 270.0;
    childInfos.push_back(info3);

    rootNode->CreateChildrenFromInfos(childInfos);

    double sum = SmartLayoutConstraints::GetSumOfAllChildWidth(*rootNode);
    EXPECT_EQ(sum, 330.0);
}

/**
 * @tc.name: SmartLayoutConstraintsTest005
 * @tc.desc: Test GetMaxWidthOfAllChild with empty children
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutConstraintsTest, SmartLayoutConstraintsTest005, TestSize.Level1)
{
    auto rootNode = SmartLayoutNode::CreateRootNode();
    double maxWidth = SmartLayoutConstraints::GetMaxWidthOfAllChild(*rootNode);
    EXPECT_EQ(maxWidth, 0.0);
}

/**
 * @tc.name: SmartLayoutConstraintsTest006
 * @tc.desc: Test GetMaxWidthOfAllChild with multiple children
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutConstraintsTest, SmartLayoutConstraintsTest006, TestSize.Level1)
{
    auto rootNode = SmartLayoutNode::CreateRootNode();
    rootNode->SetLayoutType(SmartLayoutType::COLUMN);
    rootNode->SetLayoutSize(200.0, 200.0);

    std::vector<ChildLayoutInfo> childInfos;

    ChildLayoutInfo info1;
    info1.id = 1;
    info1.width = 80.0;
    info1.height = 50.0;
    childInfos.push_back(info1);

    ChildLayoutInfo info2;
    info2.id = 2;
    info2.width = 150.0;
    info2.height = 30.0;
    childInfos.push_back(info2);

    ChildLayoutInfo info3;
    info3.id = 3;
    info3.width = 100.0;
    info3.height = 40.0;
    childInfos.push_back(info3);

    rootNode->CreateChildrenFromInfos(childInfos);

    double maxWidth = SmartLayoutConstraints::GetMaxWidthOfAllChild(*rootNode);
    EXPECT_EQ(maxWidth, 150.0);
}

/**
 * @tc.name: SmartLayoutConstraintsTest007
 * @tc.desc: Test AddDefaultConstraints with simple setup
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutConstraintsTest, SmartLayoutConstraintsTest007, TestSize.Level1)
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

} // namespace OHOS::Ace::NG