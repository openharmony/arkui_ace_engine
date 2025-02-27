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
#include "core/components_ng/manager/select_content_overlay/select_overlay_callback.h"
#include "core/components_ng/manager/select_content_overlay/select_overlay_holder.h"
#include "core/components_ng/manager/select_overlay/select_overlay_manager.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_pattern.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_property.h"
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

class MockSelectOverlayHolder : public SelectOverlayHolder, public SelectOverlayCallback {
    DECLARE_ACE_TYPE(MockSelectOverlayHolder, SelectOverlayHolder, SelectOverlayCallback);

public:
    MockSelectOverlayHolder() = default;
    ~MockSelectOverlayHolder() = default;

    void SetOwner(const RefPtr<FrameNode>& node)
    {
        node_ = node;
    }

    RefPtr<FrameNode> GetOwner()
    {
        return node_;
    }

    RefPtr<SelectOverlayCallback> GetCallback() override
    {
        return Claim(this);
    }

    void OnUpdateSelectOverlayInfo(SelectOverlayInfo& overlayInfo, int32_t requestCode)
    {
        overlayInfo.enableHandleLevel = true;
        overlayInfo.handleLevelMode = handleLevelMode_;
        overlayInfo.menuInfo.menuIsShow = true;
    }

    void OnHandleLevelModeChanged(HandleLevelMode mode) override
    {
        handleLevelMode_ = mode;
    }

    bool CheckSwitchToMode(HandleLevelMode mode) override
    {
        return allowSwitchMode_;
    }

    bool CheckTouchInHostNode(const PointF& touchPoint)
    {
        return false;
    }

private:
    HandleLevelMode handleLevelMode_ = HandleLevelMode::OVERLAY;
    bool allowSwitchMode_ = false;
    RefPtr<FrameNode> node_;
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
    auto textFrameNode =
        FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, 10, []() { return AceType::MakeRefPtr<TextPattern>(); });
    ASSERT_TRUE(textFrameNode);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_TRUE(textPattern);
    auto proxy = selectOverlayManager->CreateAndShowSelectOverlay(selectOverlayInfo, textPattern);
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
    auto proxy2 = selectOverlayManager->CreateAndShowSelectOverlay(selectOverlayInfo2, textPattern);
    ASSERT_TRUE(proxy2);
    auto id2 = selectOverlayManager->selectOverlayInfo_.singleLineHeight;
    EXPECT_EQ(id2, NODE_ID_2);

    /**
     * @tc.steps: step3. call CreateAndShowSelectOverlay again and change the param
     * @tc.expected: return the proxy which has the right SelectOverlayId
     */
    SelectOverlayInfo selectOverlayInfo3;
    selectOverlayInfo3.singleLineHeight = NODE_ID_3;
    auto proxy3 = selectOverlayManager->CreateAndShowSelectOverlay(selectOverlayInfo3, textPattern);
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
    EXPECT_FALSE(result);
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

/**
 * @tc.name: GetSelectOverlayInfo01
 * @tc.desc: test GetSelectOverlayInfo
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, GetSelectOverlayInfo01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init client and clientInfo
     */
    TextFieldPattern client;
    ClientOverlayInfo clientInfo;
    clientInfo.isUpdateMenu = false;

    /**
     * @tc.steps: step2.call GetSelectOverlayInfo
     * @tc.expected: handlerColor equals the default handlerColor
     */
    client.selectOverlayInfo_.handlerColor = Color::BLUE;
    auto selectOverlayInfo = client.GetSelectOverlayInfo(clientInfo);
    ASSERT_TRUE(selectOverlayInfo->handlerColor.has_value());
    EXPECT_TRUE(selectOverlayInfo->handlerColor.value() == client.selectOverlayInfo_.handlerColor.value());

    /**
     * @tc.steps: step3.set handlerColor and call GetSelectOverlayInfo
     * @tc.expected: handlerColor equals the setting handlerColor
     */
    clientInfo.handlerColor = Color::RED;
    selectOverlayInfo = client.GetSelectOverlayInfo(clientInfo);
    ASSERT_TRUE(selectOverlayInfo->handlerColor.has_value());
    EXPECT_TRUE(selectOverlayInfo->handlerColor.value() == Color::RED);
}

/**
 * @tc.name: InitSelectOverlay
 * @tc.desc: test InitSelectOverlay
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, InitSelectOverlay, TestSize.Level1)
{
    /**
     * @tc.steps: step1. InitSelectOverlay
     */
    TextFieldPattern client;
    client.InitSelectOverlay();
    client.selectOverlayInfo_.menuCallback.onCopy();
    EXPECT_FALSE(client.SelectOverlayIsOn());

    client.InitSelectOverlay();
    client.selectOverlayInfo_.menuCallback.onCut();
    EXPECT_FALSE(client.SelectOverlayIsOn());

    client.InitSelectOverlay();
    client.selectOverlayInfo_.menuCallback.onSelectAll();
    EXPECT_FALSE(client.SelectOverlayIsOn());

    client.InitSelectOverlay();
    client.selectOverlayInfo_.menuCallback.onPaste();
    EXPECT_FALSE(client.SelectOverlayIsOn());

    client.InitSelectOverlay();
    client.selectOverlayInfo_.menuCallback.onTranslate();
    EXPECT_FALSE(client.SelectOverlayIsOn());

    client.InitSelectOverlay();
    client.selectOverlayInfo_.menuCallback.onSearch();
    EXPECT_FALSE(client.SelectOverlayIsOn());

    client.InitSelectOverlay();
    client.selectOverlayInfo_.menuCallback.onShare();
    EXPECT_FALSE(client.SelectOverlayIsOn());

    client.InitSelectOverlay();
    client.selectOverlayInfo_.menuCallback.onCameraInput();
    EXPECT_FALSE(client.SelectOverlayIsOn());

    client.InitSelectOverlay();
    client.selectOverlayInfo_.menuCallback.onAIWrite();
    EXPECT_FALSE(client.SelectOverlayIsOn());

    bool isFirst = true;
    GestureEvent info;
    client.InitSelectOverlay();
    client.selectOverlayInfo_.onHandleMoveStart(info, isFirst);
    EXPECT_TRUE(isFirst);

    RectF area;
    area = RectF(1, 1, 1, 1);
    client.InitSelectOverlay();
    client.selectOverlayInfo_.onHandleMove(area, isFirst);
    EXPECT_TRUE(isFirst);

    area = RectF(1, 2, 2, 2);
    client.InitSelectOverlay();
    client.selectOverlayInfo_.onHandleMoveDone(area, isFirst);
    EXPECT_TRUE(isFirst);

    bool closedByGlobalEvent = true;
    client.InitSelectOverlay();
    client.selectOverlayInfo_.onClose(closedByGlobalEvent);
    EXPECT_TRUE(isFirst);
}

/**
 * @tc.name: RequestOpenSelectOverlay001
 * @tc.desc: test RequestOpenSelectOverlay001
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, RequestOpenSelectOverlay001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. RequestOpenSelectOverlay001
     */
    TextFieldPattern client;
    ClientOverlayInfo clientInfo;

    EXPECT_FALSE(client.SelectOverlayIsOn());
    client.RequestOpenSelectOverlay(clientInfo);
}

/**
 * @tc.name: RequestOpenSelectOverlay002
 * @tc.desc: test RequestOpenSelectOverlay002
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, RequestOpenSelectOverlay002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. RequestOpenSelectOverlay002
     */
    TextFieldPattern client;
    ClientOverlayInfo clientInfo;

    client.RequestOpenSelectOverlay(clientInfo);
    EXPECT_FALSE(client.SelectOverlayIsOn());
}

/**
 * @tc.name: CreateSelectOverlay01
 * @tc.desc: test CreateSelectOverlay01
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, CreateSelectOverlay01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. CreateSelectOverlay01
     */
    TextFieldPattern client;
    ClientOverlayInfo clientInfo;
    SelectOverlayInfo selectOverlayInfo;

    selectOverlayInfo.isUsingMouse = IS_USING_MOUSE;
    client.CreateSelectOverlay(clientInfo);
    EXPECT_TRUE(selectOverlayInfo.isUsingMouse);

    selectOverlayInfo.isUsingMouse = false;
    client.CreateSelectOverlay(clientInfo);
    EXPECT_FALSE(selectOverlayInfo.isUsingMouse);
}

/**
 * @tc.name: CreateSelectOverlay02
 * @tc.desc: test CreateSelectOverlay02
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, CreateSelectOverlay02, TestSize.Level1)
{
    /**
     * @tc.steps: step1. CreateSelectOverlay02
     */
    TextFieldPattern client;
    ClientOverlayInfo clientInfo;
    SelectOverlayInfo selectOverlayInfo;

    selectOverlayInfo.isUsingMouse = false;
    client.CreateSelectOverlay(clientInfo);
    EXPECT_FALSE(selectOverlayInfo.isUsingMouse);
}

/**
 * @tc.name: UpdateShowingSelectOverlay03
 * @tc.desc: test UpdateShowingSelectOverlay03
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, UpdateShowingSelectOverlay03, TestSize.Level1)
{
    /**
     * @tc.steps: step1. UpdateShowingSelectOverlay03
     */
    TextFieldPattern client;
    ClientOverlayInfo clientInfo;
    SelectHandleInfo handleInfo;
    SelectHandleInfo secondInfo;
    secondInfo.isShow = false;
    clientInfo.isShowMouseMenu = false;
    clientInfo.secondHandleInfo = secondInfo;

    clientInfo.isNewAvoid = true;
    client.UpdateShowingSelectOverlay(clientInfo);
    EXPECT_TRUE(clientInfo.isNewAvoid);

    clientInfo.isUpdateMenu = true;
    client.UpdateShowingSelectOverlay(clientInfo);

    clientInfo.firstHandleInfo = handleInfo;
    client.UpdateShowingSelectOverlay(clientInfo);
}

/**
 * @tc.name: UpdateSelectInfo
 * @tc.desc: test UpdateSelectInfo
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, UpdateSelectInfo, TestSize.Level1)
{
    /**
     * @tc.steps: step1. UpdateSelectInfo
     */
    TextFieldPattern client;
    SelectOverlayInfo selectOverlayInfo;
    const std::string selectInfo = "selectInfo";
    client.UpdateSelectInfo(selectInfo);
    selectOverlayInfo.selectText = selectInfo;
    EXPECT_EQ(selectOverlayInfo.selectText, selectInfo);
}

/**
 * @tc.name: UpdateSelectMenuInfo
 * @tc.desc: test UpdateSelectMenuInfo
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, UpdateSelectMenuInfo, TestSize.Level1)
{
    /**
     * @tc.steps: step1. UpdateSelectMenuInfo
     */
    TextFieldPattern client;
    SelectOverlayInfo selectOverlayInfo;
    std::function<void(SelectMenuInfo&)> updateAction;
    client.UpdateSelectMenuInfo(updateAction);
    EXPECT_FALSE(selectOverlayInfo.isUseOverlayNG);
}

/**
 * @tc.name: UpdateSelectMenuVisibility001
 * @tc.desc: test UpdateSelectMenuVisibility001
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, UpdateSelectMenuVisibility001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. UpdateSelectMenuVisibility001
     */
    TextFieldPattern client;
    SelectOverlayInfo selectOverlayInfo;
    bool isVisible = true;
    client.UpdateSelectMenuVisibility(isVisible);
    EXPECT_TRUE(isVisible);
}

/**
 * @tc.name: UpdateSelectMenuVisibility002
 * @tc.desc: test UpdateSelectMenuVisibility002
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, UpdateSelectMenuVisibility002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. UpdateSelectMenuVisibility002
     */
    TextFieldPattern client;
    SelectOverlayInfo selectOverlayInfo;
    bool isVisible = false;
    client.UpdateSelectMenuVisibility(isVisible);
    EXPECT_FALSE(isVisible);
}

/**
 * @tc.name: StartListeningScrollableParent001
 * @tc.desc: test StartListeningScrollableParent001
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, StartListeningScrollableParent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. StartListeningScrollableParent001
     */
    TextFieldPattern client;
    ScrollableParentInfo scrollableParentInfo;
    scrollableParentInfo.hasParent = true;
    client.StartListeningScrollableParent(root_);
    EXPECT_TRUE(scrollableParentInfo.hasParent);
}

/**
 * @tc.name: StopListeningScrollableParent
 * @tc.desc: test StopListeningScrollableParent
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, StopListeningScrollableParent, TestSize.Level1)
{
    /**
     * @tc.steps: step1. StopListeningScrollableParent
     */
    TextFieldPattern client;
    auto root = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    client.StopListeningScrollableParent(root);
    EXPECT_NE(root, nullptr);
}

/**
 * @tc.name: GetVisibleContentRect
 * @tc.desc: test GetVisibleContentRect
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, GetVisibleContentRect, TestSize.Level1)
{
    /**
     * @tc.steps: step1. GetVisibleContentRect
     */
    TextFieldPattern client;
    RectF visibleRect;
    visibleRect = RectF(1, 1, 1, 1);
    client.GetVisibleContentRect(root_, visibleRect);
    EXPECT_NE(visibleRect.GetY(), 0);
}

/**
 * @tc.name: SetHolder
 * @tc.desc: test SetHolder
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, SetHolder, TestSize.Level1)
{
    /**
     * @tc.steps: step1. SetHolder
     */
    auto content = SelectContentOverlayManager(root_);
    content.SetHolder(nullptr);

    auto holder = AceType::MakeRefPtr<SelectOverlayHolder>();
    content.SetHolder(holder);

    content.selectionHoldId_ = 1;
    content.SetHolder(holder);
    EXPECT_EQ(content.selectOverlayHolder_, holder);
}

/**
 * @tc.name: SetHolderInternal
 * @tc.desc: test SetHolderInternal
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, SetHolderInternal, TestSize.Level1)
{
    /**
     * @tc.steps: step1. SetHolderInternal
     */
    auto content = SelectContentOverlayManager(root_);
    content.SetHolderInternal(nullptr);

    auto holder = AceType::MakeRefPtr<SelectOverlayHolder>();
    content.SetHolder(holder);

    content.SetHolder(holder);
    content.SetHolderInternal(holder);
    EXPECT_EQ(content.selectionHoldId_, -1);
}

/**
 * @tc.name: HasHolder
 * @tc.desc: test HasHolder
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, HasHolder, TestSize.Level1)
{
    /**
     * @tc.steps: step1. HasHolder
     */
    auto content = SelectContentOverlayManager(root_);
    int32_t id = -1;
    bool hasHolder = content.HasHolder(id);
    EXPECT_FALSE(hasHolder);
}

/**
 * @tc.name: SelectContent Show
 * @tc.desc: test SelectContent Show
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, Show, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Show
     */
    auto content = SelectContentOverlayManager(root_);
    bool animation = true;
    auto holder = AceType::MakeRefPtr<SelectOverlayHolder>();
    content.SetHolder(holder);
    int32_t requestCode = -1;
    content.Show(animation, requestCode);
    EXPECT_EQ(content.selectionHoldId_, -1);
}

/**
 * @tc.name: SelectContent BuildSelectOverlayInfo
 * @tc.desc: test SelectContent BuildSelectOverlayInfo
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, BuildSelectOverlayInfo, TestSize.Level1)
{
    /**
     * @tc.steps: step1. BuildSelectOverlayInfo
     */
    auto content = SelectContentOverlayManager(root_);
    auto holder = AceType::MakeRefPtr<SelectOverlayHolder>();
    content.SetHolder(holder);
    int32_t requestCode = -1;
    content.BuildSelectOverlayInfo(requestCode);
    EXPECT_EQ(content.selectionHoldId_, -1);
}

/**
 * @tc.name: SelectContent UpdateStatusInfos
 * @tc.desc: test SelectContent UpdateStatusInfos
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, UpdateStatusInfos, TestSize.Level1)
{
    /**
     * @tc.steps: step1. UpdateStatusInfos
     */
    auto content = SelectContentOverlayManager(root_);
    auto holder = AceType::MakeRefPtr<SelectOverlayHolder>();
    content.SetHolder(holder);
    SelectOverlayInfo info;
    content.UpdateStatusInfos(info);
    EXPECT_NE(holder, nullptr);
}

/**
 * @tc.name: MarkInfoChange
 * @tc.desc: test MarkInfoChange
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, MarkInfoChange, TestSize.Level1)
{
    /**
     * @tc.steps: step1. MarkInfoChange
     */
    auto content = SelectContentOverlayManager(root_);
    SelectOverlayDirtyFlag dirty = 1;

    auto holder = AceType::MakeRefPtr<SelectOverlayHolder>();
    content.SetHolder(holder);
    content.MarkInfoChange(dirty);
    EXPECT_EQ(content.selectionHoldId_, -1);
}

/**
 * @tc.name: UpdateHandleInfosWithFlag
 * @tc.desc: test UpdateHandleInfosWithFlag
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, UpdateHandleInfosWithFlag, TestSize.Level1)
{
    /**
     * @tc.steps: step1. UpdateHandleInfosWithFlag
     */
    auto content = SelectContentOverlayManager(root_);
    int32_t updateFlag = 1;

    auto holder = AceType::MakeRefPtr<SelectOverlayHolder>();
    content.SetHolder(holder);
    content.UpdateHandleInfosWithFlag(updateFlag);

    updateFlag = 2;
    content.UpdateHandleInfosWithFlag(updateFlag);

    updateFlag = 3;
    content.UpdateHandleInfosWithFlag(updateFlag);
    EXPECT_EQ(content.selectionHoldId_, -1);
}

/**
 * @tc.name: CreateSelectOverlay
 * @tc.desc: test CreateSelectOverlay
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, CreateSelectOverlay, TestSize.Level1)
{
    /**
     * @tc.steps: step1. CreateSelectOverlay
     */
    auto content = SelectContentOverlayManager(root_);
    SelectOverlayInfo info;
    bool animation = true;
    content.CreateSelectOverlay(info, animation);
    EXPECT_EQ(content.selectionHoldId_, -1);
}

/**
 * @tc.name: MountNodeToRoot
 * @tc.desc: test MountNodeToRoot
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, MountNodeToRoot, TestSize.Level1)
{
    /**
     * @tc.steps: step1. MountNodeToRoot
     */
    auto content = SelectContentOverlayManager(root_);
    bool animation = true;
    content.MountNodeToRoot(root_, animation, NodeType::HANDLE);
    EXPECT_EQ(content.selectionHoldId_, -1);
}

/**
 * @tc.name: GetSelectOverlayRoot
 * @tc.desc: test GetSelectOverlayRoot
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, GetSelectOverlayRoot, TestSize.Level1)
{
    /**
     * @tc.steps: step1. GetSelectOverlayRoot
     */
    auto content = SelectContentOverlayManager(root_);
    auto rootNode = content.GetSelectOverlayRoot();
    EXPECT_EQ(rootNode, nullptr);
}

/**
 * @tc.name: CloseInternal
 * @tc.desc: test CloseInternal
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, CloseInternal, TestSize.Level1)
{
    /**
     * @tc.steps: step1. CloseInternal
     */
    auto content = SelectContentOverlayManager(root_);
    auto holder = AceType::MakeRefPtr<SelectOverlayHolder>();
    content.SetHolder(holder);
    int32_t id = 1;
    bool animation = true;
    CloseReason reason = CloseReason::CLOSE_REASON_NORMAL;
    content.CloseInternal(id, animation, reason);
    EXPECT_EQ(content.selectionHoldId_, -1);
}

/**
 * @tc.name: DestroySelectOverlayNode
 * @tc.desc: test DestroySelectOverlayNode
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, DestroySelectOverlayNode, TestSize.Level1)
{
    /**
     * @tc.steps: step1. DestroySelectOverlayNode
     */
    auto content = SelectContentOverlayManager(root_);
    content.DestroySelectOverlayNode(root_);
    content.ClearAllStatus();
    EXPECT_EQ(content.selectionHoldId_, -1);
}

/**
 * @tc.name: ClearAllStatus
 * @tc.desc: test ClearAllStatus
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, ClearAllStatus, TestSize.Level1)
{
    /**
     * @tc.steps: step1. ClearAllStatus
     */
    auto content = SelectContentOverlayManager(root_);
    auto holder = AceType::MakeRefPtr<SelectOverlayHolder>();
    content.SetHolder(holder);
    content.ClearAllStatus();
    EXPECT_NE(holder, nullptr);
}

/**
 * @tc.name: CloseCurrent
 * @tc.desc: test CloseCurrent
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, CloseCurrent, TestSize.Level1)
{
    /**
     * @tc.steps: step1. CloseCurrent
     */
    auto content = SelectContentOverlayManager(root_);
    auto holder = AceType::MakeRefPtr<SelectOverlayHolder>();
    content.SetHolder(holder);
    bool animation = true;
    CloseReason reason = CloseReason::CLOSE_REASON_NORMAL;
    bool isCloseCurrent = content.CloseCurrent(animation, reason);
    EXPECT_FALSE(isCloseCurrent);
}

/**
 * @tc.name: ShowOptionMenu
 * @tc.desc: test ShowOptionMenu
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, ShowOptionMenu, TestSize.Level1)
{
    /**
     * @tc.steps: step1. ShowOptionMenu
     */
    auto content = SelectContentOverlayManager(root_);
    auto holder = AceType::MakeRefPtr<SelectOverlayHolder>();
    content.SetHolder(holder);
    content.ShowOptionMenu();
    content.HideOptionMenu(true);
    content.ToggleOptionMenu();
    content.DisableMenu();
    content.EnableMenu();
    content.HideHandle();
    content.IsCreating();
    content.IsMenuShow();
    content.IsSingleHandle();
    bool isHandlesShow = content.IsHandlesShow();
    EXPECT_FALSE(isHandlesShow);
}

/**
 * @tc.name: IsHandleReverse
 * @tc.desc: test IsHandleReverse
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, IsHandleReverse, TestSize.Level1)
{
    /**
     * @tc.steps: step1. IsHandleReverse
     */
    auto content = SelectContentOverlayManager(root_);
    auto holder = AceType::MakeRefPtr<SelectOverlayHolder>();
    content.SetHolder(holder);
    bool isHandle = content.IsHandleReverse();
    EXPECT_FALSE(isHandle);
}

/**
 * @tc.name: RestartHiddenHandleTask
 * @tc.desc: test RestartHiddenHandleTask
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, RestartHiddenHandleTask, TestSize.Level1)
{
    /**
     * @tc.steps: step1. RestartHiddenHandleTask
     */
    auto content = SelectContentOverlayManager(root_);
    auto holder = AceType::MakeRefPtr<SelectOverlayHolder>();
    content.SetHolder(holder);
    bool isDelay = true;
    content.RestartHiddenHandleTask(isDelay);
    EXPECT_FALSE(content.isIntercept_);
}

/**
 * @tc.name: CancelHiddenHandleTask
 * @tc.desc: test RestartHiddenHandleTask
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, CancelHiddenHandleTask, TestSize.Level1)
{
    /**
     * @tc.steps: step1. CancelHiddenHandleTask
     */
    auto content = SelectContentOverlayManager(root_);
    auto holder = AceType::MakeRefPtr<SelectOverlayHolder>();
    content.SetHolder(holder);
    content.CancelHiddenHandleTask();
    EXPECT_FALSE(content.isIntercept_);
}

/**
 * @tc.name: GetSelectOverlayNode
 * @tc.desc: test GetSelectOverlayNode
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, GetSelectOverlayNode, TestSize.Level1)
{
    /**
     * @tc.steps: step1. GetSelectOverlayNode
     */
    auto content = SelectContentOverlayManager(root_);
    auto holder = AceType::MakeRefPtr<SelectOverlayHolder>();
    content.SetHolder(holder);
    auto selectOverlayNode = content.GetSelectOverlayNode();
    EXPECT_EQ(selectOverlayNode, nullptr);
}

/**
 * @tc.name: GetShowMenuType
 * @tc.desc: test GetShowMenuType
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, GetShowMenuType, TestSize.Level1)
{
    /**
     * @tc.steps: step1. GetShowMenuType
     */
    auto content = SelectContentOverlayManager(root_);
    auto holder = AceType::MakeRefPtr<SelectOverlayHolder>();
    content.SetHolder(holder);
    content.GetShowMenuType();
    EXPECT_FALSE(content.IsOpen());
}

/**
 * @tc.name: ContentHandleGlobalEvent
 * @tc.desc: test SelectContentOverlayManager HandleGlobalEvent
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, ContentHandleGlobalEvent, TestSize.Level1)
{
    /**
     * @tc.steps: step1. HandleGlobalEvent
     */
    Init();
    auto content = SelectContentOverlayManager(root_);
    auto holder = AceType::MakeRefPtr<SelectOverlayHolder>();
    content.SetHolder(holder);
    TouchEvent touchPoint;
    content.HandleGlobalEvent(touchPoint, ROOT_OFFSET);
    EXPECT_NE(touchPoint.type, TouchType::DOWN);
    /**
     * @tc.steps: step2. Change the TouchEvent and call HandleGlobalEvent
     */
    touchPoint.type = TouchType::DOWN;
    content.HandleGlobalEvent(touchPoint, ROOT_OFFSET);
    EXPECT_NE(touchPoint.type, TouchType::UP);

    touchPoint.type = TouchType::UP;
    content.HandleGlobalEvent(touchPoint, ROOT_OFFSET);
    EXPECT_NE(touchPoint.type, TouchType::MOVE);
}

/**
 * @tc.name: IsTouchInSelectOverlayArea
 * @tc.desc: test IsTouchInSelectOverlayArea
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, IsTouchInSelectOverlayArea, TestSize.Level1)
{
    /**
     * @tc.steps: step1. IsTouchInSelectOverlayArea
     */
    Init();
    auto content = SelectContentOverlayManager(root_);
    auto holder = AceType::MakeRefPtr<SelectOverlayHolder>();
    PointF point { 9.0f, 12.0f };
    content.SetHolder(holder);
    content.IsTouchInSelectOverlayArea(point);
    EXPECT_FALSE(content.IsOpen());
}

/**
 * @tc.name: HandleSelectionEvent
 * @tc.desc: test HandleSelectionEvent
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, HandleSelectionEvent, TestSize.Level1)
{
    /**
     * @tc.steps: step1. HandleSelectionEvent
     */
    Init();
    auto content = SelectContentOverlayManager(root_);
    auto holder = AceType::MakeRefPtr<SelectOverlayHolder>();
    PointF point { 9.0f, 12.0f };
    content.SetHolder(holder);
    TouchEvent touchPoint;
    touchPoint.type = TouchType::UP;
    content.HandleSelectionEvent(point, touchPoint);
    EXPECT_FALSE(content.IsOpen());
}

/**
 * @tc.name: ResetSelectionRect
 * @tc.desc: test ResetSelectionRect
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, ResetSelectionRect, TestSize.Level1)
{
    /**
     * @tc.steps: step1. ResetSelectionRect
     */
    Init();
    auto content = SelectContentOverlayManager(root_);
    auto holder = AceType::MakeRefPtr<SelectOverlayHolder>();
    content.SetHolder(holder);
    HoldSelectionInfo holdSelectionInfo_;
    holdSelectionInfo_ = {};
    content.ResetSelectionRect();
    EXPECT_EQ(content.selectionHoldId_, -1);
}

/**
 * @tc.name: SetHoldSelectionCallback
 * @tc.desc: test SetHoldSelectionCallback
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, SetHoldSelectionCallback, TestSize.Level1)
{
    /**
     * @tc.steps: step1. SetHoldSelectionCallback
     */
    Init();
    auto content = SelectContentOverlayManager(root_);
    int32_t id = -1;
    auto holder = AceType::MakeRefPtr<SelectOverlayHolder>();
    HoldSelectionInfo holdSelectionInfo_;
    holdSelectionInfo_ = {};
    content.SetHolder(holder);
    content.SetHoldSelectionCallback(id, holdSelectionInfo_);
    EXPECT_EQ(content.selectionHoldId_, -1);
    id = 1;
    content.SetHoldSelectionCallback(id, holdSelectionInfo_);
    EXPECT_EQ(content.selectionHoldId_, 1);
}

/**
 * @tc.name: RemoveHoldSelectionCallback
 * @tc.desc: test RemoveHoldSelectionCallback
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, RemoveHoldSelectionCallback, TestSize.Level1)
{
    /**
     * @tc.steps: step1. RemoveHoldSelectionCallback
     */
    Init();
    auto content = SelectContentOverlayManager(root_);
    HoldSelectionInfo holdSelectionInfo_;
    holdSelectionInfo_ = {};
    int32_t id = -1;
    auto holder = AceType::MakeRefPtr<SelectOverlayHolder>();
    content.SetHolder(holder);
    content.RemoveHoldSelectionCallback(id);
    id = 1;
    content.RemoveHoldSelectionCallback(id);
    EXPECT_EQ(content.selectionHoldId_, -1);
}

/**
 * @tc.name: SwitchToHandleMode
 * @tc.desc: test SwitchToHandleMode
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, SwitchToHandleMode, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Crate SelectContentOverlayManager and SelectOverlayHolder.
     */
    Init();
    auto content = AceType::MakeRefPtr<SelectContentOverlayManager>(root_);
    auto holder = AceType::MakeRefPtr<MockSelectOverlayHolder>();
    content->SetHolder(holder);
    content->Show(false, 0);
    EXPECT_NE(content->handleNode_.Upgrade(), nullptr);
    EXPECT_NE(content->menuNode_.Upgrade(), nullptr);
    /**
     * @tc.steps: step2. SwitchToHandleMode OVERLAY mode.
     */
    content->SwitchToHandleMode(HandleLevelMode::OVERLAY);
    EXPECT_EQ(holder->handleLevelMode_, HandleLevelMode::OVERLAY);

    /**
     * @tc.steps: step3. SwitchToHandleMode EMBED mode.
     */
    content->SwitchToHandleMode(HandleLevelMode::EMBED, false);
    EXPECT_EQ(holder->handleLevelMode_, HandleLevelMode::OVERLAY);
    holder->allowSwitchMode_ = true;
    holder->SetOwner(root_);
    content->SwitchToHandleMode(HandleLevelMode::EMBED, false);
    EXPECT_EQ(holder->handleLevelMode_, HandleLevelMode::EMBED);
}

/**
 * @tc.name: ClickAndSwitchToHandleMode
 * @tc.desc: test click to switch overlay mode.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, ClickAndSwitchToHandleMode, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Crate SelectContentOverlayManager and SelectOverlayHolder.
     */
    Init();
    auto content = AceType::MakeRefPtr<SelectContentOverlayManager>(root_);
    auto holder = AceType::MakeRefPtr<MockSelectOverlayHolder>();
    content->SetHolder(holder);
    content->Show(false, 0);
    ASSERT_NE(content->handleNode_.Upgrade(), nullptr);
    ASSERT_NE(content->menuNode_.Upgrade(), nullptr);
    /**
     * @tc.steps: step2. SwitchToHandleMode EMBED mode.
     */
    content->SwitchToHandleMode(HandleLevelMode::EMBED);
    EXPECT_EQ(holder->handleLevelMode_, HandleLevelMode::EMBED);

    /**
     * @tc.steps: step3. click handle to switch overlay mode.
     */
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(content->menuNode_.Upgrade());
    ASSERT_NE(selectOverlayNode, nullptr);
    auto selectOverlayPattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(selectOverlayPattern, nullptr);
    selectOverlayPattern->isFirstHandleTouchDown_ = true;
    selectOverlayPattern->isSecondHandleTouchDown_ = true;
    TouchEventInfo info("");
    TouchLocationInfo location(1);
    location.SetLocalLocation(Offset(0.0f, 0.0f));
    location.touchType_ = TouchType::UP;
    info.changedTouches_ = { location };
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto overlayManager = pipeline->GetSelectOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->selectContentManager_ = content;
    holder->allowSwitchMode_ = true;
    selectOverlayPattern->HandleTouchEvent(info);
    EXPECT_EQ(holder->handleLevelMode_, HandleLevelMode::OVERLAY);
}

/**
 * @tc.name: CreateSelectOverlay03
 * @tc.desc: test CreateSelectOverlay
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, CreateSelectOverlay03, TestSize.Level1)
{
    /**
     * @tc.steps: step1. CreateSelectOverlay
     */
    Init();
    auto content = AceType::MakeRefPtr<SelectContentOverlayManager>(root_);
    ASSERT_NE(content, nullptr);
    SelectOverlayInfo info;
    info.enableHandleLevel = false;
    info.enableSubWindowMenu = true;
    info.isUsingMouse = IS_USING_MOUSE;
    TextMenuOptions textMenuOptions_;
    textMenuOptions_.showMode = TextMenuShowMode::PREFER_WINDOW;
    selectOverlayManager_->SetTextMenuOptions(textMenuOptions_);
    EXPECT_EQ(selectOverlayManager_->GetMenuShowMode(), TextMenuShowMode::PREFER_WINDOW);
    bool animation = true;
    content->CreateSelectOverlay(info, animation);
    EXPECT_EQ(content->selectionHoldId_, -1);
}

/**
 * @tc.name: CreateSelectOverlay04
 * @tc.desc: test CreateSelectOverlay
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, CreateSelectOverlay04, TestSize.Level1)
{
    /**
     * @tc.steps: step1. CreateSelectOverlay
     */
    Init();
    auto content = AceType::MakeRefPtr<SelectContentOverlayManager>(root_);
    ASSERT_NE(content, nullptr);
    SelectOverlayInfo info;
    info.enableHandleLevel = true;
    info.enableSubWindowMenu = true;
    TextMenuOptions textMenuOptions_;
    textMenuOptions_.showMode = TextMenuShowMode::PREFER_WINDOW;
    selectOverlayManager_->SetTextMenuOptions(textMenuOptions_);
    EXPECT_EQ(selectOverlayManager_->GetMenuShowMode(), TextMenuShowMode::PREFER_WINDOW);
    bool animation = true;
    content->CreateSelectOverlay(info, animation);
    EXPECT_NE(content->handleNode_.Upgrade(), nullptr);
    EXPECT_NE(content->menuNode_.Upgrade(), nullptr);
}

/**
 * @tc.name: MountMenuNodeToSubWindow01
 * @tc.desc: test MountMenuNodeToSubWindow
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, MountMenuNodeToSubWindow01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init SelectContentOverlayManager
     */
    Init();
    auto content = AceType::MakeRefPtr<SelectContentOverlayManager>(root_);
    ASSERT_NE(content, nullptr);
    SelectOverlayInfo selectInfo;
    selectInfo.enableHandleLevel = true;
    selectInfo.enableSubWindowMenu = true;
    selectInfo.isUseOverlayNG = true;
    selectInfo.menuInfo.showCut = true;
    selectInfo.menuInfo.showCopy = true;
    TextMenuOptions textMenuOptions_;
    textMenuOptions_.showMode = TextMenuShowMode::PREFER_WINDOW;
    selectOverlayManager_->SetTextMenuOptions(textMenuOptions_);
    EXPECT_EQ(selectOverlayManager_->GetMenuShowMode(), TextMenuShowMode::PREFER_WINDOW);

    /**
     * @tc.steps: step2. CreateSelectOverlayNode
     */
    content->shareOverlayInfo_ = std::make_shared<SelectOverlayInfo>(selectInfo);
    ASSERT_NE(content->shareOverlayInfo_, nullptr);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(content->shareOverlayInfo_);
    ASSERT_NE(frameNode, nullptr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    /**
     * @tc.steps: step3. MountMenuNodeToSubWindow
     */
    bool animation = true;
    content->MountMenuNodeToSubWindow(selectOverlayNode, animation, NodeType::TOUCH_MENU);
    auto selectoverlayPattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(selectoverlayPattern, nullptr);
    EXPECT_EQ(selectoverlayPattern->GetIsMenuShowInSubWindow(), false);
}

/**
 * @tc.name: IsEnableSubWindowMenu01
 * @tc.desc: test IsEnableSubWindowMenu
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, IsEnableSubWindowMenu01, TestSize.Level1)
{
    Init();
    auto content = AceType::MakeRefPtr<SelectContentOverlayManager>(root_);
    ASSERT_NE(content, nullptr);
    SelectOverlayInfo info;
    info.enableHandleLevel = true;
    info.enableSubWindowMenu = true;
    TextMenuOptions textMenuOptions_;
    textMenuOptions_.showMode = TextMenuShowMode::PREFER_WINDOW;
    selectOverlayManager_->SetTextMenuOptions(textMenuOptions_);
    EXPECT_EQ(selectOverlayManager_->GetMenuShowMode(), TextMenuShowMode::PREFER_WINDOW);
    content->shareOverlayInfo_ = std::make_shared<SelectOverlayInfo>(info);
    EXPECT_EQ(content->IsEnableSubWindowMenu(), false);
}

/**
 * @tc.name: IsEnableSubWindowMenu02
 * @tc.desc: test IsEnableSubWindowMenu
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, IsEnableSubWindowMenu02, TestSize.Level1)
{
    Init();
    auto content = AceType::MakeRefPtr<SelectContentOverlayManager>(root_);
    ASSERT_NE(content, nullptr);
    SelectOverlayInfo info;
    info.enableHandleLevel = true;
    info.enableSubWindowMenu = true;
    EXPECT_EQ(selectOverlayManager_->GetMenuShowMode(), TextMenuShowMode::DEFAULT);
    content->shareOverlayInfo_ = std::make_shared<SelectOverlayInfo>(info);
    EXPECT_EQ(content->IsEnableSubWindowMenu(), false);
}

/**
 * @tc.name: IsRightClickSubWindowMenu01
 * @tc.desc: test IsRightClickSubWindowMenu
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, IsRightClickSubWindowMenu01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init SelectContentOverlayManager
     */
    Init();
    auto content = AceType::MakeRefPtr<SelectContentOverlayManager>(root_);
    ASSERT_NE(content, nullptr);
    SelectOverlayInfo info;
    info.enableHandleLevel = false;
    info.enableSubWindowMenu = true;
    info.isUsingMouse = IS_USING_MOUSE;
    info.isUseOverlayNG = true;
    TextMenuOptions textMenuOptions_;
    textMenuOptions_.showMode = TextMenuShowMode::PREFER_WINDOW;
    selectOverlayManager_->SetTextMenuOptions(textMenuOptions_);
    EXPECT_EQ(selectOverlayManager_->GetMenuShowMode(), TextMenuShowMode::PREFER_WINDOW);
    content->shareOverlayInfo_ = std::make_shared<SelectOverlayInfo>(info);
    ASSERT_NE(content->shareOverlayInfo_, nullptr);

    auto wrapperNode_ = FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MenuWrapperPattern>(1));
    ASSERT_NE(wrapperNode_, nullptr);
    content->selectOverlayNode_ = wrapperNode_;
    auto selectoverlayNode = content->selectOverlayNode_.Upgrade();
    ASSERT_NE(selectoverlayNode, nullptr);

    /**
     * @tc.steps: step2. Update menunode menuWrapperPattern
     */
    auto menuWrapperPattern = selectoverlayNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(menuWrapperPattern, nullptr);
    menuWrapperPattern->SetIsSelectOverlaySubWindowWrapper(true);
    EXPECT_EQ(menuWrapperPattern->GetIsSelectOverlaySubWindowWrapper(), true);
    EXPECT_EQ(content->IsRightClickSubWindowMenu(), true);
}

/**
 * @tc.name: IsRightClickSubWindowMenu02
 * @tc.desc: test IsRightClickSubWindowMenu
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, IsRightClickSubWindowMenu02, TestSize.Level1)
{
    /**
     * @tc.steps: step1. CreateSelectOverlay
     */
    Init();
    auto content = AceType::MakeRefPtr<SelectContentOverlayManager>(root_);
    ASSERT_NE(content, nullptr);
    SelectOverlayInfo info;
    info.enableHandleLevel = false;
    info.enableSubWindowMenu = true;
    info.isUsingMouse = IS_USING_MOUSE;
    TextMenuOptions textMenuOptions_;
    textMenuOptions_.showMode = TextMenuShowMode::PREFER_WINDOW;
    selectOverlayManager_->SetTextMenuOptions(textMenuOptions_);
    EXPECT_EQ(selectOverlayManager_->GetMenuShowMode(), TextMenuShowMode::PREFER_WINDOW);
    bool animation = true;
    content->CreateSelectOverlay(info, animation);
    EXPECT_EQ(content->IsRightClickSubWindowMenu(), false);
}

/**
 * @tc.name: IsSelectOverlaySubWindowMenu01
 * @tc.desc: test IsSelectOverlaySubWindowMenu
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, IsSelectOverlaySubWindowMenu01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. CreateSelectOverlay
     */
    Init();
    auto content = AceType::MakeRefPtr<SelectContentOverlayManager>(root_);
    ASSERT_NE(content, nullptr);
    SelectOverlayInfo info;
    info.enableHandleLevel = true;
    info.enableSubWindowMenu = true;
    info.isUseOverlayNG = true;
    TextMenuOptions textMenuOptions_;
    textMenuOptions_.showMode = TextMenuShowMode::PREFER_WINDOW;
    selectOverlayManager_->SetTextMenuOptions(textMenuOptions_);
    EXPECT_EQ(selectOverlayManager_->GetMenuShowMode(), TextMenuShowMode::PREFER_WINDOW);
    bool animation = true;
    content->CreateSelectOverlay(info, animation);
    EXPECT_NE(content->handleNode_.Upgrade(), nullptr);
    EXPECT_NE(content->menuNode_.Upgrade(), nullptr);

    /**
     * @tc.steps: step2. Update menunode selectOverlayPattern
     */
    RefPtr<Pattern> pattern = content->GetMenuPattern();
    ASSERT_NE(pattern, nullptr);
    auto selectOverlayPattern = AceType::DynamicCast<SelectOverlayPattern>(pattern);
    ASSERT_NE(selectOverlayPattern, nullptr);
    selectOverlayPattern->SetIsMenuShowInSubWindow(true);
    EXPECT_EQ(selectOverlayPattern->GetIsMenuShowInSubWindow(), true);
    EXPECT_EQ(content->IsSelectOverlaySubWindowMenu(), true);
}

/**
 * @tc.name: IsSelectOverlaySubWindowMenu02
 * @tc.desc: test IsSelectOverlaySubWindowMenu
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestNg, IsSelectOverlaySubWindowMenu02, TestSize.Level1)
{
    /**
     * @tc.steps: step1. CreateSelectOverlay
     */
    Init();
    auto content = AceType::MakeRefPtr<SelectContentOverlayManager>(root_);
    ASSERT_NE(content, nullptr);
    SelectOverlayInfo info;
    info.enableHandleLevel = true;
    info.enableSubWindowMenu = true;
    info.isUseOverlayNG = true;
    TextMenuOptions textMenuOptions_;
    textMenuOptions_.showMode = TextMenuShowMode::PREFER_WINDOW;
    selectOverlayManager_->SetTextMenuOptions(textMenuOptions_);
    EXPECT_EQ(selectOverlayManager_->GetMenuShowMode(), TextMenuShowMode::PREFER_WINDOW);
    bool animation = true;
    content->CreateSelectOverlay(info, animation);
    EXPECT_EQ(content->IsSelectOverlaySubWindowMenu(), false);
}
} // namespace OHOS::Ace::NG
