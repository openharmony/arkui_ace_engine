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

} // namespace OHOS::Ace::NG