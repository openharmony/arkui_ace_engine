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
#include "core/components_ng/pattern/smart_layout/engine/smart_layout_constraints.h"
#include "core/components_ng/pattern/smart_layout/engine/smart_layout_types.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class SmartLayoutTestCore : public testing::Test {
public:
    static void SetUpTestSuite() {}
    static void TearDownTestSuite() {}
    void SetUp() override {}
    void TearDown() override {}
};

/**
 * @tc.name: SmartLayoutTestCore001
 * @tc.desc: Test basic SmartLayoutNode creation and solving
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutTestCore, SmartLayoutTestCore001, TestSize.Level1)
{
    auto rootNode = SmartLayoutNode::CreateRootNode();
    EXPECT_NE(rootNode, nullptr);
    EXPECT_NE(rootNode->GetEngine(), nullptr);
    EXPECT_EQ(rootNode->GetName(), "root");
}

/**
 * @tc.name: SmartLayoutTestCore002
 * @tc.desc: Test SmartLayoutNode with constraints solving
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutTestCore, SmartLayoutTestCore002, TestSize.Level1)
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
 * @tc.name: SmartLayoutTestCore003
 * @tc.desc: Test SmartLayoutTypes default values
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutTestCore, SmartLayoutTestCore003, TestSize.Level1)
{
    SmartLayoutSize size;
    EXPECT_EQ(size.Width(), 0.0);
    EXPECT_EQ(size.Height(), 0.0);

    ChildLayoutInfo info;
    EXPECT_EQ(info.id, 0);
    EXPECT_EQ(info.width, 0.0);
    EXPECT_EQ(info.height, 0.0);
    EXPECT_FALSE(info.isBlank);

    SmartLayoutRect rect;
    EXPECT_FALSE(rect.IsValid());

    EdgesSpaces spaces;
    EXPECT_EQ(spaces.left, 0.0);
    EXPECT_EQ(spaces.right, 0.0);
    EXPECT_EQ(spaces.top, 0.0);
    EXPECT_EQ(spaces.bottom, 0.0);
}

/**
 * @tc.name: SmartLayoutTestCore004
 * @tc.desc: Test SmartLayoutNode child creation
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutTestCore, SmartLayoutTestCore004, TestSize.Level1)
{
    auto rootNode = SmartLayoutNode::CreateRootNode();
    rootNode->SetLayoutType(SmartLayoutType::COLUMN);

    ChildLayoutInfo info;
    info.id = 100;
    info.width = 50.0;
    info.height = 30.0;
    info.isBlank = false;

    EdgesSpaces spaces;
    auto childNode = rootNode->CreateChildNode(info, spaces);

    EXPECT_NE(childNode, nullptr);
    EXPECT_EQ(childNode->GetNodeId(), 100);
    EXPECT_EQ(childNode->GetSize().width.value, 50.0);
    EXPECT_EQ(childNode->GetSize().height.value, 30.0);
}

} // namespace OHOS::Ace::NG