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
#define private public
#define protected public

#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/manager/select_overlay/select_overlay_manager.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/text/text_base.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/components_ng/property/property.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string ROOT_TAG("root");
constexpr int32_t NODE_ID = 143;
constexpr int32_t NODE_ID_2 = 601;
constexpr int32_t NODE_ID_3 = 707;
const OffsetF RIGHT_CLICK_OFFSET = OffsetF(10.0f, 10.0f);
const OffsetF ROOT_OFFSET = OffsetF(10.0f, 10.0f);
const bool IS_USING_MOUSE = true;
} // namespace

class SelectOverlayManagerTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    RefPtr<SelectOverlayManager> selectOverlayManager_;
    RefPtr<SelectOverlayProxy> proxy_;
    RefPtr<FrameNode> root_;
    void Init();
};

void SelectOverlayManagerTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
}

void SelectOverlayManagerTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void SelectOverlayManagerTestNg::Init()
{
    SelectOverlayInfo selectOverlayInfo;
    selectOverlayInfo.singleLineHeight = NODE_ID;
    root_ = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    selectOverlayManager_ = AceType::MakeRefPtr<SelectOverlayManager>(root_);
    ASSERT_NE(selectOverlayManager_, nullptr);
    proxy_ = selectOverlayManager_->CreateAndShowSelectOverlay(selectOverlayInfo, nullptr);
    ASSERT_NE(proxy_, nullptr);
}
/**
 * @tc.name: SelectOverlayManagerTest001
 * @tc.desc: test first CreateAndShowSelectOverlay
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, SelectOverlayManagerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call CreateAndShowSelectOverlay
     * @tc.expected: return the proxy which has the right SelectOverlayId
     */
    Init();
    auto id = proxy_->GetSelectOverlayId();
    EXPECT_EQ(id, 2);

    /**
     * @tc.expected: root's children_list contains the selectOverlayNode we created
     */
    auto selectOverlayNode = root_->GetChildren().back();
    ASSERT_TRUE(selectOverlayNode);
    auto node_id = selectOverlayNode->GetId();
    EXPECT_EQ(node_id, 2);
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
    auto node_id = selectOverlayManager->selectOverlayInfo_.singleLineHeight;
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
    ASSERT_TRUE(proxy);
    auto id = selectOverlayManager->selectOverlayInfo_.singleLineHeight;
    EXPECT_EQ(id, NODE_ID);
    selectOverlayManager->DestroySelectOverlay(34);

    /**
     * @tc.steps: step2. call CreateAndShowSelectOverlay again and change the param
     * @tc.expected: return the proxy which has the right SelectOverlayId
     */
    SelectOverlayInfo selectOverlayInfo2;
    selectOverlayInfo2.singleLineHeight = NODE_ID_2;
    auto proxy2 = selectOverlayManager->CreateAndShowSelectOverlay(selectOverlayInfo2, nullptr);
    ASSERT_TRUE(proxy2);
    auto id2 = selectOverlayManager->selectOverlayInfo_.singleLineHeight;
    EXPECT_EQ(id2, NODE_ID_2);

    /**
     * @tc.steps: step3. call CreateAndShowSelectOverlay again and change the param
     * @tc.expected: return the proxy which has the right SelectOverlayId
     */
    SelectOverlayInfo selectOverlayInfo3;
    selectOverlayInfo3.singleLineHeight = NODE_ID_3;
    auto proxy3 = selectOverlayManager->CreateAndShowSelectOverlay(selectOverlayInfo3, nullptr);
    ASSERT_TRUE(proxy3);
    auto id3 = selectOverlayManager->selectOverlayInfo_.singleLineHeight;
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
    ASSERT_TRUE(proxy);
    auto id = selectOverlayManager->selectOverlayInfo_.singleLineHeight;
    EXPECT_EQ(id, NODE_ID);

    /**
     * @tc.steps: step2. call DestroySelectOverlay with wrong param
     * @tc.expected: destroySelectOverlay fail and the proxy still has the original SelectOverlayId
     */
    selectOverlayManager->DestroySelectOverlay(NODE_ID_2);
    auto children = root->GetChildren();
    EXPECT_FALSE(children.empty());
    id = selectOverlayManager->selectOverlayInfo_.singleLineHeight;
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
    EXPECT_FALSE(flag1);

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
    ASSERT_TRUE(proxy);

    /**
     * @tc.expected: root's children_list contains the selectOverlayNode we created
     */
    auto selectOverlayNode = root->GetChildren().back();
    ASSERT_TRUE(selectOverlayNode);
    auto node_id = selectOverlayManager->selectOverlayInfo_.singleLineHeight;
    EXPECT_EQ(node_id, NODE_ID);

    /**
     * @tc.steps: step2. call DestroySelectOverlay
     * @tc.expected: root's children_list has removed the selectOverlayNode we created
     */
    selectOverlayManager->DestroySelectOverlay();
    auto children = root->GetChildren();
    EXPECT_TRUE(children.empty());
    /**
     * @tc.steps: step3. call DestroySelectOverlay again when current node is invalid
     * @tc.expected: function exits normally
     */
    PropertyChangeFlag flag = PROPERTY_UPDATE_NORMAL;
    selectOverlayManager->MarkDirty(flag);
    TouchEvent touchPoint;
    selectOverlayManager->HandleGlobalEvent(touchPoint, ROOT_OFFSET);
    selectOverlayManager->NotifyOverlayClosed();
    selectOverlayManager->DestroySelectOverlay(NODE_ID);
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
    auto node_id = selectOverlayManager->selectOverlayInfo_.singleLineHeight;
    EXPECT_EQ(node_id, NODE_ID);

    /**
     * @tc.steps: step2. call IsInSelectedOrSelectOverlayArea
     * @tc.expected: return true
     */
    PropertyChangeFlag flag = PROPERTY_UPDATE_NORMAL;
    selectOverlayManager->MarkDirty(flag);
    const NG::PointF point { 0.0f, 0.0f };
    auto result = selectOverlayManager->IsInSelectedOrSelectOverlayArea(point);
    EXPECT_TRUE(result);
}
/**
 * @tc.name: SelectOverlayManagerTest010
 * @tc.desc: test IsTouchInCallerArea
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, SelectOverlayManagerTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call IsTouchInCallerArea when touchTestResults_ is empty
     * @tc.expected: return false
     */
    Init();
    auto result1 = selectOverlayManager_->IsTouchInCallerArea();
    EXPECT_FALSE(result1);
    /**
     * @tc.steps: step2. call HandleGlobalEvent
     */
    TouchEvent touchPoint;
    selectOverlayManager_->HandleGlobalEvent(touchPoint, ROOT_OFFSET);
    /**
     * @tc.steps: step3. call DestroySelectOverlay with animation
     * @tc.expected: root's children_list has removed the selectOverlayNode we created
     */
    selectOverlayManager_->DestroySelectOverlay(true);
    auto children = root_->GetChildren();
    EXPECT_TRUE(children.empty());
}

/**
 * @tc.name: FindWindowScene001
 * @tc.desc: test FindWindowScene
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, FindWindowScene001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a SelectOverlayManager
     */
    SelectOverlayInfo selectOverlayInfo;
    selectOverlayInfo.singleLineHeight = NODE_ID;
    auto root = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto selectOverlayManager = AceType::MakeRefPtr<SelectOverlayManager>(root);
    /**
     * @tc.steps: step2. call FindWindowScene
     */
    auto rootNode = selectOverlayManager->FindWindowScene(nullptr);
    EXPECT_TRUE(rootNode);
}

/**
 * @tc.name: HandleGlobalEvent01
 * @tc.desc: test HandleGlobalEvent
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, HandleGlobalEvent01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call IsTouchInCallerArea when touchTestResults_ is empty
     * @tc.expected: return false
     */
    Init();
    auto result1 = selectOverlayManager_->IsTouchInCallerArea();
    EXPECT_FALSE(result1);
    /**
     * @tc.steps: step2. Change the properties of the TouchEvent and call HandleGlobalEvent
     */
    TouchEvent touchPoint;
    touchPoint.type = TouchType::DOWN;
    selectOverlayManager_->HandleGlobalEvent(touchPoint, OffsetF(0.0f, 0.0f));
    EXPECT_NE(touchPoint.sourceType, SourceType::TOUCH);
    /**
     * @tc.steps: step3. call DestroySelectOverlay with animation
     * @tc.expected: root's children_list has removed the selectOverlayNode we created
     */
    selectOverlayManager_->DestroySelectOverlay(true);
    auto children = root_->GetChildren();
    EXPECT_TRUE(children.empty());
}

/**
 * @tc.name: HandleGlobalEvent02
 * @tc.desc: test HandleGlobalEvent
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, HandleGlobalEvent02, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call IsTouchInCallerArea when touchTestResults_ is empty
     * @tc.expected: return false
     */
    Init();
    auto result1 = selectOverlayManager_->IsTouchInCallerArea();
    EXPECT_FALSE(result1);
    /**
     * @tc.steps: step2. Change the properties of the TouchEvent and call HandleGlobalEvent
     */
    TouchEvent touchPoint;
    touchPoint.sourceType = SourceType::TOUCH;
    selectOverlayManager_->HandleGlobalEvent(touchPoint, OffsetF(0.0f, 0.0f));
    EXPECT_NE(touchPoint.type, TouchType::DOWN);
    /**
     * @tc.steps: step3. call DestroySelectOverlay with animation
     * @tc.expected: root's children_list has removed the selectOverlayNode we created
     */
    selectOverlayManager_->DestroySelectOverlay(true);
    auto children = root_->GetChildren();
    EXPECT_TRUE(children.empty());
}

/**
 * @tc.name: HandleGlobalEvent03
 * @tc.desc: test HandleGlobalEvent
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, HandleGlobalEvent03, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call IsTouchInCallerArea when touchTestResults_ is empty
     * @tc.expected: return false
     */
    Init();
    auto result1 = selectOverlayManager_->IsTouchInCallerArea();
    EXPECT_FALSE(result1);
    /**
     * @tc.steps: step2. Change the properties of the TouchEvent and call HandleGlobalEvent
     */
    TouchEvent touchPoint;
    touchPoint.type = TouchType::MOVE;
    selectOverlayManager_->HandleGlobalEvent(touchPoint, OffsetF(0.0f, 0.0f));
    EXPECT_NE(touchPoint.sourceType, SourceType::TOUCH);
    /**
     * @tc.steps: step3. call DestroySelectOverlay with animation
     * @tc.expected: root's children_list has removed the selectOverlayNode we created
     */
    selectOverlayManager_->DestroySelectOverlay(true);
    auto children = root_->GetChildren();
    EXPECT_TRUE(children.empty());
}

/**
 * @tc.name: HandleGlobalEvent04
 * @tc.desc: test HandleGlobalEvent
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, HandleGlobalEvent04, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call IsTouchInCallerArea when touchTestResults_ is empty
     * @tc.expected: return false
     */
    Init();
    auto result1 = selectOverlayManager_->IsTouchInCallerArea();
    EXPECT_FALSE(result1);
    /**
     * @tc.steps: step2. Change the properties of the TouchEvent and call HandleGlobalEvent
     */
    TouchEvent touchPoint;
    touchPoint.type = TouchType::MOVE;
    touchPoint.sourceType = SourceType::TOUCH;
    selectOverlayManager_->touchDownPoints_.emplace_back(touchPoint);
    selectOverlayManager_->HandleGlobalEvent(touchPoint, OffsetF(0.0f, 0.0f));
    EXPECT_NE(touchPoint.sourceType, SourceType::MOUSE);
    /**
     * @tc.steps: step3. call DestroySelectOverlay with animation
     * @tc.expected: root's children_list has removed the selectOverlayNode we created
     */
    selectOverlayManager_->DestroySelectOverlay(true);
    auto children = root_->GetChildren();
    EXPECT_TRUE(children.empty());
}

/**
 * @tc.name: HandleGlobalEvent05
 * @tc.desc: test HandleGlobalEvent
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, HandleGlobalEvent05, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call IsTouchInCallerArea when touchTestResults_ is empty
     * @tc.expected: return false
     */
    Init();
    auto result1 = selectOverlayManager_->IsTouchInCallerArea();
    EXPECT_FALSE(result1);
    /**
     * @tc.steps: step2. Change the properties of the TouchEvent and call HandleGlobalEvent
     */
    TouchEvent touchPoint;
    TouchEvent touchPointerror;
    touchPointerror.id = 5;
    touchPointerror.x = 5;
    touchPointerror.y = 5;
    touchPoint.type = TouchType::MOVE;
    touchPoint.sourceType = SourceType::TOUCH;
    selectOverlayManager_->touchDownPoints_.emplace_back(touchPointerror);
    selectOverlayManager_->HandleGlobalEvent(touchPoint, OffsetF(0.0f, 0.0f));
    EXPECT_NE(touchPoint.sourceType, SourceType::MOUSE);
    /**
     * @tc.steps: step3. call DestroySelectOverlay with animation
     * @tc.expected: root's children_list has removed the selectOverlayNode we created
     */
    selectOverlayManager_->DestroySelectOverlay(true);
    auto children = root_->GetChildren();
    EXPECT_TRUE(children.empty());
}

/**
 * @tc.name: HandleGlobalEvent06
 * @tc.desc: test HandleGlobalEvent
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, HandleGlobalEvent06, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call IsTouchInCallerArea when touchTestResults_ is empty
     * @tc.expected: return false
     */
    Init();
    auto result1 = selectOverlayManager_->IsTouchInCallerArea();
    EXPECT_FALSE(result1);
    /**
     * @tc.steps: step2. Change the properties of the TouchEvent and call HandleGlobalEvent
     */
    TouchEvent touchPoint;
    TouchEvent touchPointerror;
    touchPointerror.id = 5;
    touchPoint.type = TouchType::MOVE;
    touchPoint.sourceType = SourceType::TOUCH;
    selectOverlayManager_->touchDownPoints_.emplace_back(touchPointerror);
    selectOverlayManager_->HandleGlobalEvent(touchPoint, OffsetF(0.0f, 0.0f));
    EXPECT_NE(touchPoint.sourceType, SourceType::MOUSE);
    /**
     * @tc.steps: step3. call DestroySelectOverlay with animation
     * @tc.expected: root's children_list has removed the selectOverlayNode we created
     */
    selectOverlayManager_->DestroySelectOverlay(true);
    auto children = root_->GetChildren();
    EXPECT_TRUE(children.empty());
}

/**
 * @tc.name: HandleGlobalEvent07
 * @tc.desc: test HandleGlobalEvent
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, HandleGlobalEvent07, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call IsTouchInCallerArea when touchTestResults_ is empty
     * @tc.expected: return false
     */
    Init();
    auto result1 = selectOverlayManager_->IsTouchInCallerArea();
    EXPECT_FALSE(result1);
    /**
     * @tc.steps: step2. Change the properties of the TouchEvent and call HandleGlobalEvent
     */
    TouchEvent touchPoint;
    touchPoint.type = TouchType::DOWN;
    touchPoint.sourceType = SourceType::TOUCH;
    selectOverlayManager_->touchDownPoints_.emplace_back(touchPoint);
    selectOverlayManager_->HandleGlobalEvent(touchPoint, OffsetF(0.0f, 0.0f));
    EXPECT_NE(touchPoint.sourceType, SourceType::MOUSE);
    /**
     * @tc.steps: step3. call DestroySelectOverlay with animation
     * @tc.expected: root's children_list has removed the selectOverlayNode we created
     */
    selectOverlayManager_->DestroySelectOverlay(true);
    auto children = root_->GetChildren();
    EXPECT_TRUE(children.empty());
}

/**
 * @tc.name: HandleGlobalEvent08
 * @tc.desc: test HandleGlobalEvent
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, HandleGlobalEvent08, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call IsTouchInCallerArea when touchTestResults_ is empty
     * @tc.expected: return false
     */
    Init();
    auto result1 = selectOverlayManager_->IsTouchInCallerArea();
    EXPECT_FALSE(result1);
    /**
     * @tc.steps: step2. Change the properties of the TouchEvent and call HandleGlobalEvent
     */
    TouchEvent touchPoint;
    touchPoint.type = TouchType::DOWN;
    touchPoint.sourceType = SourceType::TOUCH;
    selectOverlayManager_->touchDownPoints_.clear();
    touchPoint.x = 1.1f;
    touchPoint.y = 1.1f;
    selectOverlayManager_->HandleGlobalEvent(touchPoint, OffsetF(0.0f, 0.0f));
    EXPECT_NE(touchPoint.sourceType, SourceType::MOUSE);
    /**
     * @tc.steps: step3. call DestroySelectOverlay with animation
     * @tc.expected: root's children_list has removed the selectOverlayNode we created
     */
    selectOverlayManager_->DestroySelectOverlay(true);
    auto children = root_->GetChildren();
    EXPECT_TRUE(children.empty());
}

/**
 * @tc.name: HandleGlobalEvent09
 * @tc.desc: test HandleGlobalEvent
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, HandleGlobalEvent09, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call IsTouchInCallerArea when touchTestResults_ is empty
     * @tc.expected: return false
     */
    Init();
    auto result1 = selectOverlayManager_->IsTouchInCallerArea();
    EXPECT_FALSE(result1);
    /**
     * @tc.steps: step2. Change the properties of the TouchEvent and call HandleGlobalEvent
     */
    TouchEvent touchPoint;
    touchPoint.type = TouchType::DOWN;
    touchPoint.sourceType = SourceType::TOUCH;
    selectOverlayManager_->touchDownPoints_.clear();
    auto selectOverlayNode = root_->GetChildren().back();
    auto id = std::to_string(selectOverlayNode->GetId());
    selectOverlayManager_->touchTestResults_.emplace_back(id);
    selectOverlayManager_->HandleGlobalEvent(touchPoint, OffsetF(0.0f, 0.0f));
    EXPECT_NE(touchPoint.sourceType, SourceType::MOUSE);
    /**
     * @tc.steps: step3. call DestroySelectOverlay with animation
     * @tc.expected: root's children_list has removed the selectOverlayNode we created
     */
    selectOverlayManager_->DestroySelectOverlay(true);
    auto children = root_->GetChildren();
    EXPECT_TRUE(children.empty());
}

/**
 * @tc.name: HandleGlobalEvent10
 * @tc.desc: test HandleGlobalEvent
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, HandleGlobalEvent10, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call IsTouchInCallerArea when touchTestResults_ is empty
     * @tc.expected: return false
     */
    Init();
    auto result1 = selectOverlayManager_->IsTouchInCallerArea();
    EXPECT_FALSE(result1);
    /**
     * @tc.steps: step2. Change the properties of the TouchEvent and call HandleGlobalEvent
     */
    TouchEvent touchPoint;
    TouchEvent touchPointerror;
    touchPoint.type = TouchType::MOVE;
    touchPoint.sourceType = SourceType::TOUCH;
    selectOverlayManager_->touchDownPoints_.clear();
    selectOverlayManager_->HandleGlobalEvent(touchPoint, OffsetF(0.0f, 0.0f));
    EXPECT_NE(touchPoint.sourceType, SourceType::MOUSE);
    /**
     * @tc.steps: step3. call DestroySelectOverlay with animation
     * @tc.expected: root's children_list has removed the selectOverlayNode we created
     */
    selectOverlayManager_->DestroySelectOverlay(true);
    auto children = root_->GetChildren();
    EXPECT_TRUE(children.empty());
}

/**
 * @tc.name: HandleGlobalEvent11
 * @tc.desc: test HandleGlobalEvent
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, HandleGlobalEvent11, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call IsTouchInCallerArea when touchTestResults_ is empty
     * @tc.expected: return false
     */
    Init();
    auto result1 = selectOverlayManager_->IsTouchInCallerArea();
    EXPECT_FALSE(result1);
    /**
     * @tc.steps: step2. Change the properties of the TouchEvent and call HandleGlobalEvent
     */
    TouchEvent touchPoint;
    touchPoint.type = TouchType::UP;
    touchPoint.sourceType = SourceType::TOUCH;
    selectOverlayManager_->touchDownPoints_.emplace_back(touchPoint);
    selectOverlayManager_->HandleGlobalEvent(touchPoint, OffsetF(0.0f, 0.0f));
    EXPECT_TRUE(selectOverlayManager_->touchDownPoints_.empty());
    /**
     * @tc.steps: step3. call DestroySelectOverlay with animation
     * @tc.expected: root's children_list has removed the selectOverlayNode we created
     */
    selectOverlayManager_->DestroySelectOverlay(true);
    auto children = root_->GetChildren();
    EXPECT_TRUE(children.empty());
}

/**
 * @tc.name: HandleGlobalEvent12
 * @tc.desc: test HandleGlobalEvent
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, HandleGlobalEvent12, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call IsTouchInCallerArea when touchTestResults_ is empty
     * @tc.expected: return false
     */
    Init();
    auto result1 = selectOverlayManager_->IsTouchInCallerArea();
    EXPECT_FALSE(result1);
    /**
     * @tc.steps: step2. Change the properties of the TouchEvent and call HandleGlobalEvent
     */
    TouchEvent touchPoint;
    touchPoint.type = TouchType::DOWN;
    touchPoint.sourceType = SourceType::MOUSE;
    touchPoint.x = 1.1f;
    touchPoint.y = 1.1f;
    selectOverlayManager_->HandleGlobalEvent(touchPoint, OffsetF(0.0f, 0.0f));
    EXPECT_NE(touchPoint.sourceType, SourceType::TOUCH);
    /**
     * @tc.steps: step3. call DestroySelectOverlay with animation
     * @tc.expected: root's children_list has removed the selectOverlayNode we created
     */
    selectOverlayManager_->DestroySelectOverlay(true);
    auto children = root_->GetChildren();
    EXPECT_TRUE(children.empty());
}

/**
 * @tc.name: HandleGlobalEvent13
 * @tc.desc: test HandleGlobalEvent
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, HandleGlobalEvent13, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call IsTouchInCallerArea when touchTestResults_ is empty
     * @tc.expected: return false
     */
    Init();
    auto result1 = selectOverlayManager_->IsTouchInCallerArea();
    EXPECT_FALSE(result1);
    /**
     * @tc.steps: step2. Change the properties of the TouchEvent and call HandleGlobalEvent
     */
    TouchEvent touchPoint;
    touchPoint.type = TouchType::UP;
    touchPoint.sourceType = SourceType::TOUCH;
    selectOverlayManager_->HandleGlobalEvent(touchPoint, OffsetF(0.0f, 0.0f));
    EXPECT_TRUE(selectOverlayManager_->touchDownPoints_.empty());
    /**
     * @tc.steps: step3. call DestroySelectOverlay with animation
     * @tc.expected: root's children_list has removed the selectOverlayNode we created
     */
    selectOverlayManager_->DestroySelectOverlay(true);
    auto children = root_->GetChildren();
    EXPECT_TRUE(children.empty());
}

/**
 * @tc.name: HandleGlobalEvent14
 * @tc.desc: test HandleGlobalEvent
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, HandleGlobalEvent14, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call IsTouchInCallerArea when touchTestResults_ is empty
     * @tc.expected: return false
     */
    Init();
    auto result1 = selectOverlayManager_->IsTouchInCallerArea();
    EXPECT_FALSE(result1);
    /**
     * @tc.steps: step2. Change the properties of the TouchEvent and call HandleGlobalEvent
     */
    TouchEvent touchPoint;
    TouchEvent touchPointerror;
    touchPointerror.id = 5;
    touchPoint.type = TouchType::UP;
    touchPoint.sourceType = SourceType::TOUCH;
    selectOverlayManager_->touchDownPoints_.emplace_back(touchPointerror);
    selectOverlayManager_->HandleGlobalEvent(touchPoint, OffsetF(0.0f, 0.0f));
    EXPECT_FALSE(selectOverlayManager_->touchDownPoints_.empty());
    /**
     * @tc.steps: step3. call DestroySelectOverlay with animation
     * @tc.expected: root's children_list has removed the selectOverlayNode we created
     */
    selectOverlayManager_->DestroySelectOverlay(true);
    auto children = root_->GetChildren();
    EXPECT_TRUE(children.empty());
}

/**
 * @tc.name: IsTouchInCallerArea01
 * @tc.desc: test NotifyOverlayClosed and IsTouchInCallerArea
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, IsTouchInCallerArea01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call IsTouchInCallerArea when touchTestResults_ is !empty
     * @tc.expected: return true
     */
    Init();
    SelectOverlayInfo selectOverlayInfo;
    selectOverlayInfo.singleLineHeight = NODE_ID;
    auto root = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto selectOverlayManager = AceType::MakeRefPtr<SelectOverlayManager>(root);
    auto proxy = selectOverlayManager->CreateAndShowSelectOverlay(selectOverlayInfo, nullptr);
    auto selectOverlayNode = root_->GetChildren().back();
    auto id = std::to_string(selectOverlayNode->GetId());
    selectOverlayManager_->touchTestResults_.emplace_back(id);
    auto result1 = selectOverlayManager_->IsTouchInCallerArea();
    /**
     * @tc.steps: step2. call NotifyOverlayClosed
     */
    selectOverlayManager->NotifyOverlayClosed(true);
    EXPECT_FALSE(result1);
}

/**
 * @tc.name: NotifyOnScrollCallback01
 * @tc.desc: test NotifyOnScrollCallback and RemoveScrollCallback
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, NotifyOnScrollCallback01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call CreateAndShowSelectOverlay
     * @tc.expected: return true
     */
    Init();
    SelectOverlayInfo selectOverlayInfo;
    selectOverlayInfo.singleLineHeight = NODE_ID;
    auto root = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto selectOverlayManager = AceType::MakeRefPtr<SelectOverlayManager>(root);
    auto proxy = selectOverlayManager->CreateAndShowSelectOverlay(selectOverlayInfo, nullptr);
    EXPECT_TRUE(proxy);
    /**
     * @tc.steps: step2. call NotifyOnScrollCallback and RemoveScrollCallback
     * @tc.expected: return true
     */
    selectOverlayManager->NotifyOnScrollCallback(5, Axis::VERTICAL, 0.0, 0);
    selectOverlayManager->RemoveScrollCallback(9);
    EXPECT_TRUE(selectOverlayManager->parentScrollCallbacks_.empty());
}

/**
 * @tc.name: NotifyOnScrollCallback02
 * @tc.desc: test NotifyOnScrollCallback
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, NotifyOnScrollCallback02, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call CreateAndShowSelectOverlay
     * @tc.expected: return true
     */
    Init();
    SelectOverlayInfo selectOverlayInfo;
    selectOverlayInfo.singleLineHeight = NODE_ID;
    auto root = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto selectOverlayManager = AceType::MakeRefPtr<SelectOverlayManager>(root);
    auto proxy = selectOverlayManager->CreateAndShowSelectOverlay(selectOverlayInfo, nullptr);
    EXPECT_TRUE(proxy);
    /**
     * @tc.steps: step2. Init func ScrollableParentCallback and insert toparentScrollCallbacks_
     */
    ScrollableParentCallback callback = [&](Axis axis, float value, int32_t id) {
        axis = Axis::HORIZONTAL;
        value = 0.0;
        id = 5;
    };
    selectOverlayManager->RegisterScrollCallback(5, 5, std::move(callback));
    /**
     * @tc.steps: step3. call NotifyOnScrollCallback
     * @tc.expected: return false
     */
    selectOverlayManager->NotifyOnScrollCallback(5, Axis::VERTICAL, 0.0, 0);
    EXPECT_FALSE(selectOverlayManager->parentScrollCallbacks_.empty());
}

/**
 * @tc.name: NotifyOnScrollCallback03
 * @tc.desc: test NotifyOnScrollCallback
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, NotifyOnScrollCallback03, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call CreateAndShowSelectOverlay
     * @tc.expected: return true
     */
    Init();
    SelectOverlayInfo selectOverlayInfo;
    selectOverlayInfo.singleLineHeight = NODE_ID;
    auto root = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto selectOverlayManager = AceType::MakeRefPtr<SelectOverlayManager>(root);
    auto proxy = selectOverlayManager->CreateAndShowSelectOverlay(selectOverlayInfo, nullptr);
    EXPECT_TRUE(proxy);
    /**
     * @tc.steps: step2. Init func ScrollableParentCallback and insert toparentScrollCallbacks_
     */
    ScrollableParentCallback callback = [&](Axis axis, float value, int32_t id) {
        axis = Axis::HORIZONTAL;
        value = 0.0;
        id = 5;
    };
    selectOverlayManager->RegisterScrollCallback(0, 5, std::move(callback));
    /**
     * @tc.steps: step3. call NotifyOnScrollCallback
     * @tc.expected: return false
     */
    selectOverlayManager->NotifyOnScrollCallback(5, Axis::VERTICAL, 0.0, 0);
    EXPECT_FALSE(selectOverlayManager->parentScrollCallbacks_.empty());
}

/**
 * @tc.name: RemoveScrollCallback01
 * @tc.desc: test RemoveScrollCallback
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, RemoveScrollCallback01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call CreateAndShowSelectOverlay
     * @tc.expected: return true
     */
    Init();
    SelectOverlayInfo selectOverlayInfo;
    selectOverlayInfo.singleLineHeight = NODE_ID;
    auto root = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto selectOverlayManager = AceType::MakeRefPtr<SelectOverlayManager>(root);
    auto proxy = selectOverlayManager->CreateAndShowSelectOverlay(selectOverlayInfo, nullptr);
    EXPECT_TRUE(proxy);
    /**
     * @tc.steps: step2. Init func ScrollableParentCallback and insert toparentScrollCallbacks_
     */
    ScrollableParentCallback callback = [&](Axis axis, float value, int32_t id) {
        axis = Axis::HORIZONTAL;
        value = 0.0;
        id = 5;
    };
    selectOverlayManager->RegisterScrollCallback(5, 5, std::move(callback));
    /**
     * @tc.steps: step3. call RemoveScrollCallback
     * @tc.expected: return true
     */
    selectOverlayManager->RemoveScrollCallback(5);
    EXPECT_TRUE(selectOverlayManager->parentScrollCallbacks_.empty());
}

/**
 * @tc.name: RemoveScrollCallback02
 * @tc.desc: test RemoveScrollCallback
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, RemoveScrollCallback02, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call CreateAndShowSelectOverlay
     * @tc.expected: return true
     */
    Init();
    SelectOverlayInfo selectOverlayInfo;
    selectOverlayInfo.singleLineHeight = NODE_ID;
    auto root = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto selectOverlayManager = AceType::MakeRefPtr<SelectOverlayManager>(root);
    auto proxy = selectOverlayManager->CreateAndShowSelectOverlay(selectOverlayInfo, nullptr);
    EXPECT_TRUE(proxy);
    /**
     * @tc.steps: step2. Init func ScrollableParentCallback and insert toparentScrollCallbacks_
     */
    ScrollableParentCallback callback = [&](Axis axis, float value, int32_t id) {
        axis = Axis::HORIZONTAL;
        value = 0.0;
        id = 5;
    };
    selectOverlayManager->RegisterScrollCallback(5, 5, std::move(callback));
    /**
     * @tc.steps: step3. call RemoveScrollCallback
     * @tc.expected: return false
     */
    selectOverlayManager->RemoveScrollCallback(0);
    EXPECT_FALSE(selectOverlayManager->parentScrollCallbacks_.empty());
}

/**
 * @tc.name: RemoveScrollCallback03
 * @tc.desc: test RemoveScrollCallback
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, RemoveScrollCallback03, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call CreateAndShowSelectOverlay
     * @tc.expected: return true
     */
    Init();
    SelectOverlayInfo selectOverlayInfo;
    selectOverlayInfo.singleLineHeight = NODE_ID;
    auto root = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto selectOverlayManager = AceType::MakeRefPtr<SelectOverlayManager>(root);
    auto proxy = selectOverlayManager->CreateAndShowSelectOverlay(selectOverlayInfo, nullptr);
    EXPECT_TRUE(proxy);
    /**
     * @tc.steps: step2. Init func ScrollableParentCallback and insert toparentScrollCallbacks_
     */
    ScrollableParentCallback callback = [&](Axis axis, float value, int32_t id) {
        axis = Axis::HORIZONTAL;
        value = 0.0;
        id = 5;
    };
    selectOverlayManager->RegisterScrollCallback(5, 5, std::move(callback));
    selectOverlayManager->RegisterScrollCallback(8, 5, std::move(callback));
    /**
     * @tc.steps: step3. call RemoveScrollCallback
     * @tc.expected: return false
     */
    selectOverlayManager->RemoveScrollCallback(9);
    EXPECT_FALSE(selectOverlayManager->parentScrollCallbacks_.empty());
}

/**
 * @tc.name: UpdateShowingSelectOverlay01
 * @tc.desc: test UpdateShowingSelectOverlay
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, UpdateShowingSelectOverlay01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init client and clientInfo
     */
    TextFieldPattern client;
    ClientOverlayInfo clientInfo;
    SelectHandleInfo handleInfo;
    SelectHandleInfo secondInfo;
    secondInfo.isShow = false;
    clientInfo.isShowMouseMenu = false;
    clientInfo.firstHandleInfo = handleInfo;
    clientInfo.secondHandleInfo = secondInfo;

    /**
     * @tc.steps: step2.call UpdateShowingSelectOverlay
     * @tc.expected: isUpdateMenu is true
     */
    client.UpdateShowingSelectOverlay(clientInfo);
    EXPECT_TRUE(clientInfo.isUpdateMenu);
}

/**
 * @tc.name: UpdateShowingSelectOverlay02
 * @tc.desc: test UpdateShowingSelectOverlay
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, UpdateShowingSelectOverlay02, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init client and clientInfo
     */
    TextFieldPattern client;
    ClientOverlayInfo clientInfo;
    clientInfo.isShowMouseMenu = true;

    /**
     * @tc.steps: step2.call UpdateShowingSelectOverlay
     * @tc.expected: isUpdateMenu is true
     */
    client.UpdateShowingSelectOverlay(clientInfo);
    EXPECT_TRUE(clientInfo.isUpdateMenu);
}
} // namespace OHOS::Ace::NG
