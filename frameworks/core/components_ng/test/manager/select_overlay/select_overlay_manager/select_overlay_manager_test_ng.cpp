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
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/manager/select_overlay/select_overlay_manager.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string ROOT_TAG("root");
constexpr int32_t NODE_ID = 143;
constexpr int32_t NODE_ID_2 = 601;
constexpr int32_t NODE_ID_3 = 707;
const OffsetF RIGHT_CLICK_OFFSET = OffsetF(10.0f, 10.0f);
const bool IS_USING_MOUSE = true;
} // namespace

class SelectOverlayManagerTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void SelectOverlayManagerTestNg::SetUpTestSuite()
{
    MockPipelineBase::SetUp();
    MockContainer::SetUp();
    auto taskExecutor = AceType::MakeRefPtr<MockTaskExecutor>();
    EXPECT_CALL(*(MockContainer::Current()), GetTaskExecutor()).WillRepeatedly(Return(taskExecutor));
}

void SelectOverlayManagerTestNg::TearDownTestSuite()
{
    MockPipelineBase::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: SelectOverlayManagerTest001
 * @tc.desc: test first CreateAndShowSelectOverlay
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, SelectOverlayManagerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a SelectOverlayManager
     */
    SelectOverlayInfo selectOverlayInfo;
    selectOverlayInfo.singleLineHeight = NODE_ID;
    auto root = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto selectOverlayManager = AceType::MakeRefPtr<SelectOverlayManager>(root);

    /**
     * @tc.steps: step2. call CreateAndShowSelectOverlay
     * @tc.expected: return the proxy which has the right SelectOverlayId
     */
    auto proxy = selectOverlayManager->CreateAndShowSelectOverlay(selectOverlayInfo, nullptr);
    auto id = proxy->GetSelectOverlayId();
    EXPECT_EQ(id, NODE_ID);

    /**
     * @tc.expected: root's children_list contains the selectOverlayNode we created
     */
    auto selectOverlayNode = root->GetChildren().back();
    ASSERT_TRUE(selectOverlayNode);
    auto node_id = selectOverlayNode->GetId();
    EXPECT_EQ(node_id, NODE_ID);
}

/**
 * @tc.name: SelectOverlayManagerTest002
 * @tc.desc: test DestroySelectOverlay(proxy) successfully
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, SelectOverlayManagerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a SelectOverlayManager and call CreateAndShowSelectOverlay
     */
    SelectOverlayInfo selectOverlayInfo;
    selectOverlayInfo.singleLineHeight = NODE_ID;
    auto root = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto selectOverlayManager = AceType::MakeRefPtr<SelectOverlayManager>(root);
    auto proxy = selectOverlayManager->CreateAndShowSelectOverlay(selectOverlayInfo, nullptr);

    /**
     * @tc.expected: root's children_list contains the selectOverlayNode we created
     */
    auto selectOverlayNode = root->GetChildren().back();
    ASSERT_TRUE(selectOverlayNode);
    auto node_id = selectOverlayNode->GetId();
    EXPECT_EQ(node_id, NODE_ID);

    /**
     * @tc.steps: step2. call DestroySelectOverlay
     * @tc.expected: root's children_list has removed the selectOverlayNode we created
     */
    selectOverlayManager->DestroySelectOverlay(proxy);
    auto children = root->GetChildren();
    EXPECT_TRUE(children.empty());
}

/**
 * @tc.name: SelectOverlayManagerTest003
 * @tc.desc: test CreateAndShowSelectOverlay while the selectOverlayItem_ has existed
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, SelectOverlayManagerTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a SelectOverlayManager and call CreateAndShowSelectOverlay
     * @tc.expected: return the proxy which has the right SelectOverlayId
     */
    SelectOverlayInfo selectOverlayInfo;
    selectOverlayInfo.singleLineHeight = NODE_ID;
    auto root = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto selectOverlayManager = AceType::MakeRefPtr<SelectOverlayManager>(root);
    auto proxy = selectOverlayManager->CreateAndShowSelectOverlay(selectOverlayInfo, nullptr);
    auto id = proxy->GetSelectOverlayId();
    EXPECT_EQ(id, NODE_ID);

    /**
     * @tc.steps: step2. call CreateAndShowSelectOverlay again and change the param
     * @tc.expected: return the proxy which has the right SelectOverlayId
     */
    SelectOverlayInfo selectOverlayInfo2;
    selectOverlayInfo2.singleLineHeight = NODE_ID_2;
    auto proxy2 = selectOverlayManager->CreateAndShowSelectOverlay(selectOverlayInfo2, nullptr);
    auto id2 = proxy2->GetSelectOverlayId();
    EXPECT_EQ(id2, NODE_ID_2);

    /**
     * @tc.steps: step3. call CreateAndShowSelectOverlay again and change the param
     * @tc.expected: return the proxy which has the right SelectOverlayId
     */
    SelectOverlayInfo selectOverlayInfo3;
    selectOverlayInfo3.isUsingMouse = IS_USING_MOUSE;
    selectOverlayInfo3.singleLineHeight = NODE_ID_3;
    auto proxy3 = selectOverlayManager->CreateAndShowSelectOverlay(selectOverlayInfo3, nullptr);
    auto id3 = proxy3->GetSelectOverlayId();
    EXPECT_EQ(id3, NODE_ID_3);
}

/**
 * @tc.name: SelectOverlayManagerTest004
 * @tc.desc: test DestroySelectOverlay fail
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, SelectOverlayManagerTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a SelectOverlayManager and call CreateAndShowSelectOverlay
     * @tc.expected: return the proxy which has the right SelectOverlayId
     */
    SelectOverlayInfo selectOverlayInfo;
    selectOverlayInfo.singleLineHeight = NODE_ID;
    auto root = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto selectOverlayManager = AceType::MakeRefPtr<SelectOverlayManager>(root);
    auto proxy = selectOverlayManager->CreateAndShowSelectOverlay(selectOverlayInfo, nullptr);
    auto id = proxy->GetSelectOverlayId();
    EXPECT_EQ(id, NODE_ID);

    /**
     * @tc.steps: step2. call DestroySelectOverlay with wrong param
     * @tc.expected: destroySelectOverlay fail and the proxy still has the original SelectOverlayId
     */
    selectOverlayManager->DestroySelectOverlay(NODE_ID_2);
    auto children = root->GetChildren();
    EXPECT_FALSE(children.empty());
    id = proxy->GetSelectOverlayId();
    EXPECT_EQ(id, NODE_ID);
}

/**
 * @tc.name: SelectOverlayManagerTest005
 * @tc.desc: test HasSelectOverlay
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, SelectOverlayManagerTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a SelectOverlayManager and call CreateAndShowSelectOverlay
     * @tc.expected: return the proxy which has the right SelectOverlayId
     */
    SelectOverlayInfo selectOverlayInfo;
    selectOverlayInfo.singleLineHeight = NODE_ID;
    auto root = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto selectOverlayManager = AceType::MakeRefPtr<SelectOverlayManager>(root);
    selectOverlayManager->CreateAndShowSelectOverlay(selectOverlayInfo, nullptr);

    /**
     * @tc.steps: step2. call HasSelectOverlay with the param of existed SelectOverlayId
     * @tc.expected: return true
     */
    auto flag1 = selectOverlayManager->HasSelectOverlay(NODE_ID);
    EXPECT_TRUE(flag1);

    /**
     * @tc.steps: step3. call HasSelectOverlay with the param of existed SelectOverlayId
     * @tc.expected: return false
     */
    auto flag2 = selectOverlayManager->HasSelectOverlay(NODE_ID_2);
    EXPECT_FALSE(flag2);
}

/**
 * @tc.name: SelectOverlayManagerTest006
 * @tc.desc: test GetSelectOverlayNode
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, SelectOverlayManagerTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a SelectOverlayManager
     */
    SelectOverlayInfo selectOverlayInfo;
    selectOverlayInfo.singleLineHeight = NODE_ID;
    auto root = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto selectOverlayManager = AceType::MakeRefPtr<SelectOverlayManager>(root);

    /**
     * @tc.steps: step2. call GetSelectOverlayNode without calling CreateAndShowSelectOverlay
     * @tc.expected: return nullptr
     */
    auto node1 = selectOverlayManager->GetSelectOverlayNode(NODE_ID);
    EXPECT_FALSE(node1);

    /**
     * @tc.steps: step3. call CreateAndShowSelectOverlay
     */
    selectOverlayManager->CreateAndShowSelectOverlay(selectOverlayInfo, nullptr);

    /**
     * @tc.steps: step4. call GetSelectOverlayNode with right overlayId
     * @tc.expected: return the selectOverlayNode with right nodeId
     */
    auto node2 = selectOverlayManager->GetSelectOverlayNode(NODE_ID);
    auto node2_id = node2->GetId();
    EXPECT_EQ(node2_id, NODE_ID);

    /**
     * @tc.steps: step5. call GetSelectOverlayNode with wrong overlayId
     * @tc.expected: return nullptr
     */
    auto node3 = selectOverlayManager->GetSelectOverlayNode(NODE_ID_2);
    EXPECT_FALSE(node3);
}

/**
 * @tc.name: SelectOverlayManagerTest007
 * @tc.desc: test IsSameSelectOverlayInfo
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, SelectOverlayManagerTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a SelectOverlayManager
     */
    SelectOverlayInfo selectOverlayInfo;
    selectOverlayInfo.singleLineHeight = NODE_ID;
    auto root = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto selectOverlayManager = AceType::MakeRefPtr<SelectOverlayManager>(root);

    /**
     * @tc.steps: step2. change menuInfo and call IsSameSelectOverlayInfo with different selectOverlayInfo
     * @tc.expected: return false
     */
    SelectOverlayInfo selectOverlayInfo2;
    SelectMenuInfo selectMenuInfo2;
    selectMenuInfo2.showCopy = false;
    selectOverlayInfo2.menuInfo = selectMenuInfo2;
    auto flag1 = selectOverlayManager->IsSameSelectOverlayInfo(selectOverlayInfo2);
    EXPECT_FALSE(flag1);

    /**
     * @tc.steps: step3. change isUsingMouse and call IsSameSelectOverlayInfo with different selectOverlayInfo
     * @tc.expected: return false
     */
    SelectOverlayInfo selectOverlayInfo3;
    selectOverlayInfo3.isUsingMouse = IS_USING_MOUSE;
    auto flag2 = selectOverlayManager->IsSameSelectOverlayInfo(selectOverlayInfo3);
    EXPECT_FALSE(flag2);

    /**
     * @tc.steps: step4. change rightClickOffset and call IsSameSelectOverlayInfo with different selectOverlayInfo
     * @tc.expected: return false
     */
    SelectOverlayInfo selectOverlayInfo4;
    selectOverlayInfo4.rightClickOffset = RIGHT_CLICK_OFFSET;
    auto flag3 = selectOverlayManager->IsSameSelectOverlayInfo(selectOverlayInfo4);
    EXPECT_FALSE(flag3);

    /**
     * @tc.steps: step5. call IsSameSelectOverlayInfo with right selectOverlayInfo
     * @tc.expected: return true
     */
    auto flag = selectOverlayManager->IsSameSelectOverlayInfo(selectOverlayInfo);
    EXPECT_TRUE(flag);
}

/**
 * @tc.name: SelectOverlayManagerTest008
 * @tc.desc: test DestroySelectOverlay
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, SelectOverlayManagerTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a SelectOverlayManager and call CreateAndShowSelectOverlay
     */
    SelectOverlayInfo selectOverlayInfo;
    selectOverlayInfo.singleLineHeight = NODE_ID;
    auto root = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto selectOverlayManager = AceType::MakeRefPtr<SelectOverlayManager>(root);
    auto proxy = selectOverlayManager->CreateAndShowSelectOverlay(selectOverlayInfo, nullptr);

    /**
     * @tc.expected: root's children_list contains the selectOverlayNode we created
     */
    auto selectOverlayNode = root->GetChildren().back();
    ASSERT_TRUE(selectOverlayNode);
    auto node_id = selectOverlayNode->GetId();
    EXPECT_EQ(node_id, NODE_ID);

    /**
     * @tc.steps: step2. call DestroySelectOverlay
     * @tc.expected: root's children_list has removed the selectOverlayNode we created
     */
    selectOverlayManager->DestroySelectOverlay();
    auto children = root->GetChildren();
    EXPECT_TRUE(children.empty());
}

/**
 * @tc.name: SelectOverlayManagerTest009
 * @tc.desc: test IsInSelectedOrSelectOverlayArea
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, SelectOverlayManagerTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a SelectOverlayManager and call CreateAndShowSelectOverlay
     */
    SelectOverlayInfo selectOverlayInfo;
    selectOverlayInfo.singleLineHeight = NODE_ID;
    auto root = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto selectOverlayManager = AceType::MakeRefPtr<SelectOverlayManager>(root);
    auto proxy = selectOverlayManager->CreateAndShowSelectOverlay(selectOverlayInfo, nullptr);

    /**
     * @tc.expected: root's children_list contains the selectOverlayNode we created
     */
    auto selectOverlayNode = root->GetChildren().back();
    ASSERT_TRUE(selectOverlayNode);
    auto node_id = selectOverlayNode->GetId();
    EXPECT_EQ(node_id, NODE_ID);

    /**
     * @tc.steps: step2. call IsInSelectedOrSelectOverlayArea
     * @tc.expected: return true
     */
    const NG::PointF point { 0.0f, 0.0f };
    auto result = selectOverlayManager->IsInSelectedOrSelectOverlayArea(point);
    EXPECT_TRUE(result);
}
} // namespace OHOS::Ace::NG
