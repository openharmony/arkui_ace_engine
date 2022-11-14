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

#include <optional>

#include "gtest/gtest.h"

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/manager/select_overlay/select_overlay_manager.h"
#include "frameworks/core/components_ng/pattern/pattern.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace {
bool OHOS::Ace::SystemProperties::GetDebugEnabled()
{
    return false;
}
} // namespace OHOS::Ace
namespace OHOS::Ace::NG {
namespace {
const std::string ROOT_TAG("root");
const int32_t NODE_ID = 143;
const int32_t NODE_ID_2 = 601;
} // namespace
class SelectOverlayManagerTestNg : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};

protected:
};

/**
 * @tc.name: SelectOverlayManagerTest001
 * @tc.desc: test first CreateAndShowSelectOverlay
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SelectOverlayManagerTestNg, SelectOverlayManagerTest001, TestSize.Level1)
{
    SelectOverlayInfo selectOverlayInfo;
    // just use singleLineHeight to replace the nodeId for test
    selectOverlayInfo.singleLineHeight = NODE_ID;
    auto root = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto selectOverlayManager = AceType::MakeRefPtr<SelectOverlayManager>(root);

    // check the selectOverlayProxy's id = NODE_ID
    auto proxy = selectOverlayManager->CreateAndShowSelectOverlay(selectOverlayInfo);
    auto id = proxy->GetSelectOverlayId();
    EXPECT_EQ(id, NODE_ID);

    // check the root's children list contains selectOverlayNode
    auto selectOverlayNode = root->GetChildren().back();
    ASSERT_TRUE(selectOverlayNode);
    auto node_id = selectOverlayNode->GetId();
    EXPECT_EQ(node_id, NODE_ID);
}

/**
 * @tc.name: SelectOverlayManagerTest002
 * @tc.desc: test DestroySelectOverlay(proxy) successfully
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SelectOverlayManagerTestNg, SelectOverlayManagerTest002, TestSize.Level1)
{
    SelectOverlayInfo selectOverlayInfo;
    // just use singleLineHeight to replace the nodeId for test
    selectOverlayInfo.singleLineHeight = NODE_ID;
    auto root = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto selectOverlayManager = AceType::MakeRefPtr<SelectOverlayManager>(root);
    auto proxy = selectOverlayManager->CreateAndShowSelectOverlay(selectOverlayInfo);

    // before destroy: the root's children list has selectOverlayNode
    auto selectOverlayNode = root->GetChildren().back();
    ASSERT_TRUE(selectOverlayNode);
    auto node_id = selectOverlayNode->GetId();
    EXPECT_EQ(node_id, NODE_ID);

    selectOverlayManager->DestroySelectOverlay(proxy);

    // after destroy: the root's children list hasn't selectOverlayNode
    auto children = root->GetChildren();
    EXPECT_TRUE(children.empty());
}

/**
 * @tc.name: SelectOverlayManagerTest003
 * @tc.desc: test CreateAndShowSelectOverlay while the selectOverlayItem_ has existed
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SelectOverlayManagerTestNg, SelectOverlayManagerTest003, TestSize.Level1)
{
    SelectOverlayInfo selectOverlayInfo;
    // just use singleLineHeight to replace the nodeId for test
    selectOverlayInfo.singleLineHeight = NODE_ID;
    auto root = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto selectOverlayManager = AceType::MakeRefPtr<SelectOverlayManager>(root);
    auto proxy = selectOverlayManager->CreateAndShowSelectOverlay(selectOverlayInfo);
    auto id = proxy->GetSelectOverlayId();
    // CreateAndShowSelectOverlay success
    EXPECT_EQ(id, NODE_ID);

    // call CreateAndShowSelectOverlay again
    SelectOverlayInfo selectOverlayInfo2;
    selectOverlayInfo2.singleLineHeight = NODE_ID_2;
    auto proxy2 = selectOverlayManager->CreateAndShowSelectOverlay(selectOverlayInfo2);
    auto id2 = proxy2->GetSelectOverlayId();
    // prevent selectOverlayItem_ has reset and new selectOverlayItem_ created successfully
    EXPECT_EQ(id2, NODE_ID_2);
}

/**
 * @tc.name: SelectOverlayManagerTest004
 * @tc.desc: test DestroySelectOverlay fail
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SelectOverlayManagerTestNg, SelectOverlayManagerTest004, TestSize.Level1)
{
    SelectOverlayInfo selectOverlayInfo;
    // just use singleLineHeight to replace the nodeId for test
    selectOverlayInfo.singleLineHeight = NODE_ID;
    auto root = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto selectOverlayManager = AceType::MakeRefPtr<SelectOverlayManager>(root);
    auto proxy = selectOverlayManager->CreateAndShowSelectOverlay(selectOverlayInfo);
    auto id = proxy->GetSelectOverlayId();
    // CreateAndShowSelectOverlay success
    EXPECT_EQ(id, NODE_ID);

    // call DestroySelectOverlay the wrong overlayID
    selectOverlayManager->DestroySelectOverlay(NODE_ID_2);
    // DestroySelectOverlay fail
    auto children = root->GetChildren();
    EXPECT_FALSE(children.empty());
    id = proxy->GetSelectOverlayId();
    EXPECT_EQ(id, NODE_ID);
}

/**
 * @tc.name: SelectOverlayManagerTest005
 * @tc.desc: test HasSelectOverlay
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SelectOverlayManagerTestNg, SelectOverlayManagerTest005, TestSize.Level1)
{
    SelectOverlayInfo selectOverlayInfo;
    // just use singleLineHeight to replace the nodeId for test
    selectOverlayInfo.singleLineHeight = NODE_ID;
    auto root = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto selectOverlayManager = AceType::MakeRefPtr<SelectOverlayManager>(root);
    selectOverlayManager->CreateAndShowSelectOverlay(selectOverlayInfo);

    // OverlayId exists
    auto flag1 = selectOverlayManager->HasSelectOverlay(NODE_ID);
    EXPECT_TRUE(flag1);
    // OverlayId not exists
    auto flag2 = selectOverlayManager->HasSelectOverlay(NODE_ID_2);
    EXPECT_FALSE(flag2);
}

/**
 * @tc.name: SelectOverlayManagerTest006
 * @tc.desc: test GetSelectOverlayNode
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SelectOverlayManagerTestNg, SelectOverlayManagerTest006, TestSize.Level1)
{
    SelectOverlayInfo selectOverlayInfo;
    // just use singleLineHeight to replace the nodeId for test
    selectOverlayInfo.singleLineHeight = NODE_ID;
    auto root = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto selectOverlayManager = AceType::MakeRefPtr<SelectOverlayManager>(root);
    
    // selectOverlayItem_ is nullptr
    auto node1 = selectOverlayManager->GetSelectOverlayNode(NODE_ID);
    EXPECT_FALSE(node1);

    // selectOverlayItem_ is not nullptr
    selectOverlayManager->CreateAndShowSelectOverlay(selectOverlayInfo);

    // use right overlayId to get overlayNode
    auto node2 = selectOverlayManager->GetSelectOverlayNode(NODE_ID);
    auto node2_id = node2->GetId();
    EXPECT_EQ(node2_id, NODE_ID);

    // use wrong overlayId to get overlayNode
    auto node3 = selectOverlayManager->GetSelectOverlayNode(NODE_ID_2);
    EXPECT_FALSE(node3);
}
} // namespace OHOS::Ace::NG
