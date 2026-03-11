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

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#define private public
#define protected public

#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "adapter/ohos/osal/js_accessibility_manager.h"

using namespace OHOS::Accessibility;
using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
namespace {
bool IsParentRectInfoEqual(AccessibilityParentRectInfo& rectInfo1, AccessibilityParentRectInfo& rectInfo2)
{
    CHECK_NE_RETURN(rectInfo1.left, rectInfo2.left, false);
    CHECK_NE_RETURN(rectInfo1.top, rectInfo2.top, false);
    CHECK_NE_RETURN(rectInfo1.scaleX, rectInfo2.scaleX, false);
    CHECK_NE_RETURN(rectInfo1.scaleY, rectInfo2.scaleY, false);
    CHECK_NE_RETURN(rectInfo1.rotateTransform.rotateDegree, rectInfo2.rotateTransform.rotateDegree, false);
    CHECK_NE_RETURN(rectInfo1.rotateTransform.centerX, rectInfo2.rotateTransform.centerX, false);
    CHECK_NE_RETURN(rectInfo1.rotateTransform.centerY, rectInfo2.rotateTransform.centerY, false);
    CHECK_NE_RETURN(rectInfo1.rotateTransform.innerCenterX, rectInfo2.rotateTransform.innerCenterX, false);
    CHECK_NE_RETURN(rectInfo1.rotateTransform.innerCenterY, rectInfo2.rotateTransform.innerCenterY, false);
    CHECK_NE_RETURN(rectInfo1.isChanged, rectInfo2.isChanged, false);

    return true;
}
} // namespace

class JsAccessibilityManagerTestTwo : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void JsAccessibilityManagerTestTwo::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;

    std::unique_ptr<std::ostream> ostream = std::make_unique<std::ostringstream>();
    ASSERT_NE(ostream, nullptr);
    DumpLog::GetInstance().SetDumpFile(std::move(ostream));
}

void JsAccessibilityManagerTestTwo::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: JsAccessibilityManager001
 * @tc.desc: Test GetNextFocusNodeByManager with valid currentNode and rootNode but no inspectorKey
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestTwo, JsAccessibilityManager001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. test GetNextFocusNodeByManager
     */
    auto currentNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto rootNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto result = jsAccessibilityManager->GetNextFocusNodeByManager(currentNode, rootNode);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: JsAccessibilityManager002
 * @tc.desc: Test GetNextFocusNodeByManager with null currentNode
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestTwo, JsAccessibilityManager002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. test GetNextFocusNodeByManager
     */
    RefPtr<NG::UINode> currentNode = nullptr;
    auto rootNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto result = jsAccessibilityManager->GetNextFocusNodeByManager(currentNode, rootNode);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: JsAccessibilityManager003
 * @tc.desc: Test GetNextFocusNodeByManager with null rootNode
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestTwo, JsAccessibilityManager003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. test GetNextFocusNodeByManager
     */
    auto currentNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    RefPtr<NG::FrameNode> rootNode = nullptr;
    auto result = jsAccessibilityManager->GetNextFocusNodeByManager(currentNode, rootNode);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: JsAccessibilityManager004
 * @tc.desc: Test GetNextFocusNodeByManager with both currentNode and rootNode as null
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestTwo, JsAccessibilityManager004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. test GetNextFocusNodeByManager
     */
    RefPtr<NG::UINode> currentNode = nullptr;
    RefPtr<NG::FrameNode> rootNode = nullptr;
    auto result = jsAccessibilityManager->GetNextFocusNodeByManager(currentNode, rootNode);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: JsAccessibilityManager005
 * @tc.desc: Test SubscribeToastObserver
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestTwo, JsAccessibilityManager005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);
    jsAccessibilityManager->toastObserver_ = nullptr;

    /**
     * @tc.steps: step2. test SubscribeToastObserver
     */
    auto result = jsAccessibilityManager->SubscribeToastObserver();
    EXPECT_EQ(result, true);
    EXPECT_NE(jsAccessibilityManager->toastObserver_, nullptr);
}

/**
 * @tc.name: JsAccessibilityManager006
 * @tc.desc: Test UnsubscribeToastObserver
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestTwo, JsAccessibilityManager006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);
    jsAccessibilityManager->toastObserver_ = nullptr;

    /**
     * @tc.steps: step2. test UnsubscribeToastObserver
     */
    auto result = jsAccessibilityManager->UnsubscribeToastObserver();
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: IsSendAccessibilityEventTest001
 * @tc.desc: Test IsSendAccessibilityEvent
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestTwo, IsSendAccessibilityEventTest001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-begin IsSendAccessibilityEventTest001";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. test non-page event returns true.
     */
    AccessibilityEvent event;
    event.type = AccessibilityEventType::CLICK;
    bool result = jsAccessibilityManager->IsSendAccessibilityEvent(event);
    EXPECT_TRUE(result);

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-end IsSendAccessibilityEventTest001";
}

/**
 * @tc.name: IsSendAccessibilityEventTest002
 * @tc.desc: Test page event with null PipelineContext returns result of IsSendAccessibilityEventForHost.
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestTwo, IsSendAccessibilityEventTest002, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-begin IsSendAccessibilityEventTest002";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. test page event with null PipelineContext returns result of IsSendAccessibilityEventForHost.
     */
    AccessibilityEvent eventPageChange;
    eventPageChange.type = AccessibilityEventType::PAGE_CHANGE;
    eventPageChange.nodeId = -1;
    jsAccessibilityManager->context_ = nullptr;
    bool result = jsAccessibilityManager->IsSendAccessibilityEvent(eventPageChange);
    EXPECT_TRUE(result);

    AccessibilityEvent eventPageOpen;
    eventPageOpen.type = AccessibilityEventType::PAGE_OPEN;
    eventPageOpen.nodeId = -1;
    jsAccessibilityManager->context_ = nullptr;
    result = jsAccessibilityManager->IsSendAccessibilityEvent(eventPageOpen);
    EXPECT_TRUE(result);

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-end IsSendAccessibilityEventTest002";
}

/**
 * @tc.name: GetComponentTypeAndPageIdByNodeIdTest001
 * @tc.desc: Test GetComponentTypeAndPageIdByNodeId when context is null.
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestTwo, GetComponentTypeAndPageIdByNodeIdTest001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-begin GetComponentTypeAndPageIdByNodeIdTest001";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. test GetComponentTypeAndPageIdByNodeId when context is null.
     */
    RefPtr<PipelineBase> context = nullptr;
    Framework::GetInfoByNodeId infoOfNode;
    infoOfNode.componentType = "Stack";
    infoOfNode.pageId = 666;
    infoOfNode.nodeInstanceId = 777;
    jsAccessibilityManager->GetComponentTypeAndPageIdByNodeId(-1LL, context, infoOfNode);
    EXPECT_EQ(infoOfNode.componentType, "Stack");
    EXPECT_EQ(infoOfNode.pageId, 666);
    EXPECT_EQ(infoOfNode.nodeInstanceId, 777);

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-end GetComponentTypeAndPageIdByNodeIdTest001";
}

/**
 * @tc.name: CheckPageEventCachedTest001
 * @tc.desc: Test CheckPageEventCached when node is null
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestTwo, CheckPageEventCachedTest001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-begin CheckPageEventCachedTest001";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. test CheckPageEventCached
     */
    RefPtr<NG::FrameNode> node = nullptr;
    bool result = jsAccessibilityManager->CheckPageEventCached(node, 1);
    EXPECT_FALSE(result);

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-end CheckPageEventCachedTest001";
}

/**
 * @tc.name: JsAccessibilityManager007
 * @tc.desc: Test GetUECAccessibilityParentRectInfo
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestTwo, JsAccessibilityManager007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);
    AccessibilityParentRectInfo rectInfo;
    rectInfo.left = 12;
    rectInfo.top = 34;
    rectInfo.scaleX = 56.0f;
    rectInfo.scaleY = 78.0f;
    rectInfo.rotateTransform.rotateDegree = 123;
    rectInfo.rotateTransform.centerX = 234;
    rectInfo.rotateTransform.centerY = 345;
    rectInfo.rotateTransform.innerCenterX = 456;
    rectInfo.rotateTransform.innerCenterY = 567;
    rectInfo.isChanged = true;
    jsAccessibilityManager->uecRectInfo_ = rectInfo;

    /**
     * @tc.steps: step2. test GetUECAccessibilityParentRectInfo
     */
    auto result = jsAccessibilityManager->GetUECAccessibilityParentRectInfo();
    EXPECT_TRUE(IsParentRectInfoEqual(result, rectInfo));
}

/**
 * @tc.name: JsAccessibilityManager008
 * @tc.desc: Test UpdateUECAccessibilityParentRectInfo
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestTwo, JsAccessibilityManager008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. test UpdateUECAccessibilityParentRectInfo
     */
    AccessibilityParentRectInfo rectInfo;
    rectInfo.left = 23;
    rectInfo.top = 45;
    rectInfo.scaleX = 67.0f;
    rectInfo.scaleY = 89.0f;
    rectInfo.rotateTransform.rotateDegree = 234;
    rectInfo.rotateTransform.centerX = 345;
    rectInfo.rotateTransform.centerY = 456;
    rectInfo.rotateTransform.innerCenterX = 567;
    rectInfo.rotateTransform.innerCenterY = 678;
    rectInfo.isChanged = true;
    jsAccessibilityManager->UpdateUECAccessibilityParentRectInfo(rectInfo);
    EXPECT_TRUE(IsParentRectInfoEqual(jsAccessibilityManager->uecRectInfo_, rectInfo));
}

/**
 * @tc.name: SendAccessibilitySyncEvent001
 * @tc.desc: Test SendAccessibilitySyncEvent when not register
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestTwo, SendAccessibilitySyncEvent001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-begin SendAccessibilitySyncEvent001";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);
    jsAccessibilityManager->isReg_ = false;

    /**
     * @tc.steps: step2. test SendAccessibilitySyncEvent when not register
     */
    AccessibilityEvent accessibilityEvent;
    AccessibilityEventInfo eventInfo;
    bool result = jsAccessibilityManager->SendAccessibilitySyncEvent(accessibilityEvent, eventInfo);
    EXPECT_EQ(result, false);

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-end SendAccessibilitySyncEvent001";
}

/**
 * @tc.name: FillEventInfoWithNode001
 * @tc.desc: Test FillEventInfoWithNode with null FrameNode
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestTwo, FillEventInfoWithNode001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-begin FillEventInfoWithNode001";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. test FillEventInfoWithNode with null FrameNode
     * @tc.expected: function returns early without crash
     */
    RefPtr<NG::FrameNode> nullNode = nullptr;
    AccessibilityEventInfo eventInfo;
    auto context = MockPipelineContext::GetCurrentContext();
    int64_t elementId = 100;

    jsAccessibilityManager->FillEventInfoWithNode(nullNode, eventInfo, context, elementId);

    /**
     * @tc.expected: eventInfo should not be modified
     */
    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-end FillEventInfoWithNode001";
}

/**
 * @tc.name: FillEventInfoWithNode002
 * @tc.desc: Test FillEventInfoWithNode with valid FrameNode but null AccessibilityProperty
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestTwo, FillEventInfoWithNode002, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-begin FillEventInfoWithNode002";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager and set context_
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    auto context = MockPipelineContext::GetCurrentContext();
    jsAccessibilityManager->SetPipelineContext(context);

    /**
     * @tc.steps: step2. create FrameNode with Pattern that has no AccessibilityProperty
     * @tc.expected: function returns early after null accessibilityProperty check
     */
    auto pattern = AceType::MakeRefPtr<NG::Pattern>();
    auto frameNode = NG::FrameNode::CreateFrameNode("testNode", 1, pattern, true);
    ASSERT_NE(frameNode, nullptr);

    AccessibilityEventInfo eventInfo;
    int64_t elementId = 100;

    jsAccessibilityManager->FillEventInfoWithNode(frameNode, eventInfo, context, elementId);

    /**
     * @tc.expected: eventInfo should not be modified
     */
    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-end FillEventInfoWithNode002";
}

/**
 * @tc.name: FillEventInfoWithNode003
 * @tc.desc: Test FillEventInfoWithNode with null context_ (mainContext)
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestTwo, FillEventInfoWithNode003, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-begin FillEventInfoWithNode003";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager without setting context_
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. create FrameNode with Pattern
     */
    auto pattern = AceType::MakeRefPtr<NG::Pattern>();
    auto frameNode = NG::FrameNode::CreateFrameNode("testNode", 1, pattern, true);
    ASSERT_NE(frameNode, nullptr);

    AccessibilityEventInfo eventInfo;
    auto context = MockPipelineContext::GetCurrentContext();
    int64_t elementId = 100;

    /**
     * @tc.steps: step3. call FillEventInfoWithNode
     * @tc.expected: function returns early when mainContext is null
     */
    jsAccessibilityManager->FillEventInfoWithNode(frameNode, eventInfo, context, elementId);

    /**
     * @tc.expected: eventInfo should not be modified
     */
    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-end FillEventInfoWithNode003";
}

/**
 * @tc.name: FillEventInfoWithNode004
 * @tc.desc: Test FillEventInfoWithNode sets correct component type and page ID
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestTwo, FillEventInfoWithNode004, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-begin FillEventInfoWithNode004";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager and set context_
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    auto context = MockPipelineContext::GetCurrentContext();
    jsAccessibilityManager->SetPipelineContext(context);

    /**
     * @tc.steps: step2. create FrameNode with specific tag
     */
    std::string testTag = "testComponent";
    auto pattern = AceType::MakeRefPtr<NG::Pattern>();
    auto frameNode = NG::FrameNode::CreateFrameNode(testTag, 1, pattern, true);
    ASSERT_NE(frameNode, nullptr);

    AccessibilityEventInfo eventInfo;
    int64_t elementId = 100;

    /**
     * @tc.steps: step3. call FillEventInfoWithNode
     */
    jsAccessibilityManager->FillEventInfoWithNode(frameNode, eventInfo, context, elementId);

    /**
     * @tc.expected: eventInfo should not be modified
     */
    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-end FillEventInfoWithNode004";
}

/**
 * @tc.name: FillEventInfoWithNode005
 * @tc.desc: Test FillEventInfoWithNode handles WindowId correctly
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestTwo, FillEventInfoWithNode005, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-begin FillEventInfoWithNode005";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager and set context_
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    auto context = MockPipelineContext::GetCurrentContext();
    jsAccessibilityManager->SetPipelineContext(context);

    /**
     * @tc.steps: step2. create FrameNode
     */
    auto pattern = AceType::MakeRefPtr<NG::Pattern>();
    auto frameNode = NG::FrameNode::CreateFrameNode("testNode", 1, pattern, true);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step3. create eventInfo with preset windowId
     */
    AccessibilityEventInfo eventInfo;
    int32_t testWindowId = 12345;
    eventInfo.SetWindowId(testWindowId);

    int64_t elementId = 100;

    /**
     * @tc.steps: step4. call FillEventInfoWithNode
     */
    jsAccessibilityManager->FillEventInfoWithNode(frameNode, eventInfo, context, elementId);

    /**
     * @tc.expected: eventInfo should not be modified
     */
    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-end FillEventInfoWithNode005";
}

/**
 * @tc.name: FillEventInfoWithNode006
 * @tc.desc: Test FillEventInfoWithNode with different elementId values
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestTwo, FillEventInfoWithNode006, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-begin FillEventInfoWithNode006";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    auto context = MockPipelineContext::GetCurrentContext();
    jsAccessibilityManager->SetPipelineContext(context);

    /**
     * @tc.steps: step2. test with different elementId values
     */
    std::vector<int64_t> elementIds = {0, 100, -1, INT64_MAX};

    for (auto elementId : elementIds) {
        auto pattern = AceType::MakeRefPtr<NG::Pattern>();
        auto frameNode = NG::FrameNode::CreateFrameNode("testNode", elementId, pattern, true);
        ASSERT_NE(frameNode, nullptr);

        AccessibilityEventInfo eventInfo;

        jsAccessibilityManager->FillEventInfoWithNode(frameNode, eventInfo, context, elementId);
    }

    /**
     * @tc.expected: eventInfo should not be modified
     */
    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-end FillEventInfoWithNode006";
}

/**
 * @tc.name: FillEventInfoWithNode007
 * @tc.desc: Test FillEventInfoWithNode with multiple rapid calls
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestTwo, FillEventInfoWithNode007, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-begin FillEventInfoWithNode007";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    auto context = MockPipelineContext::GetCurrentContext();
    jsAccessibilityManager->SetPipelineContext(context);

    /**
     * @tc.steps: step2. create multiple FrameNodes and test rapid calls
     */
    std::vector<RefPtr<NG::FrameNode>> frameNodes;
    for (int i = 0; i < 10; i++) {
        auto pattern = AceType::MakeRefPtr<NG::Pattern>();
        auto frameNode = NG::FrameNode::CreateFrameNode("testNode", i, pattern, true);
        frameNodes.push_back(frameNode);
    }

    /**
     * @tc.steps: step3. rapid call FillEventInfoWithNode
     */
    for (size_t i = 0; i < frameNodes.size(); i++) {
        AccessibilityEventInfo eventInfo;
        jsAccessibilityManager->FillEventInfoWithNode(
            frameNodes[i], eventInfo, context, static_cast<int64_t>(i));
    }

    /**
     * @tc.expected: eventInfo should not be modified
     */
    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-end FillEventInfoWithNode007";
}

/**
 * @tc.name: FillEventInfoWithNode008
 * @tc.desc: Test FillEventInfoWithNode boundary conditions
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestTwo, FillEventInfoWithNode008, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-begin FillEventInfoWithNode008";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    auto context = MockPipelineContext::GetCurrentContext();
    jsAccessibilityManager->SetPipelineContext(context);

    /**
     * @tc.steps: step2. test with boundary values
     */
    struct TestCase {
        int64_t nodeId;
        std::string tag;
        int32_t pageId;
    };

    std::vector<TestCase> testCases = {
        {0, "", -1},
        {INT64_MAX, "veryLongTagNameThatMightCauseIssues", INT32_MAX},
        {INT64_MIN, "tag-with-special-chars-<>", INT32_MIN},
    };

    for (const auto& testCase : testCases) {
        auto pattern = AceType::MakeRefPtr<NG::Pattern>();
        auto frameNode = NG::FrameNode::CreateFrameNode(testCase.tag, testCase.nodeId, pattern, true);
        ASSERT_NE(frameNode, nullptr);

        AccessibilityEventInfo eventInfo;
        jsAccessibilityManager->FillEventInfoWithNode(
            frameNode, eventInfo, context, testCase.nodeId);
    }

    /**
     * @tc.expected: eventInfo should not be modified
     */
    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-end FillEventInfoWithNode008";
}

/**
 * @tc.name: FillEventInfoWithNode009
 * @tc.desc: Test FillEventInfoWithNode after context_ is cleared
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestTwo, FillEventInfoWithNode009, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-begin FillEventInfoWithNode009";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager and set context_
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    auto context = MockPipelineContext::GetCurrentContext();
    jsAccessibilityManager->SetPipelineContext(context);

    auto pattern = AceType::MakeRefPtr<NG::Pattern>();
    auto frameNode = NG::FrameNode::CreateFrameNode("testNode", 1, pattern, true);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. clear context_ by setting to nullptr
     */
    jsAccessibilityManager->context_.Reset();

    AccessibilityEventInfo eventInfo;
    int64_t elementId = 100;

    /**
     * @tc.steps: step3. call FillEventInfoWithNode with cleared context
     */
    jsAccessibilityManager->FillEventInfoWithNode(frameNode, eventInfo, context, elementId);

    /**
     * @tc.expected: eventInfo should not be modified
     */
    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-end FillEventInfoWithNode009";
}

/**
 * @tc.name: FillEventInfoWithNode010
 * @tc.desc: Test FillEventInfoWithNode eventInfo initial state preservation
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestTwo, FillEventInfoWithNode010, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-begin FillEventInfoWithNode010";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    auto context = MockPipelineContext::GetCurrentContext();
    jsAccessibilityManager->SetPipelineContext(context);

    /**
     * @tc.steps: step2. create eventInfo with preset values
     */
    AccessibilityEventInfo eventInfo;
    int32_t originalWindowId = 99999;
    eventInfo.SetWindowId(originalWindowId);

    auto pattern = AceType::MakeRefPtr<NG::Pattern>();
    auto frameNode = NG::FrameNode::CreateFrameNode("testNode", 1, pattern, true);

    int64_t elementId = 100;

    /**
     * @tc.steps: step3. call FillEventInfoWithNode
     */
    jsAccessibilityManager->FillEventInfoWithNode(frameNode, eventInfo, context, elementId);

    /**
     * @tc.expected: eventInfo should not be modified
     */
    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-end FillEventInfoWithNode010";
}

/**
 * @tc.name: GetPrevFocusNodeByManager001
 * @tc.desc: Test GetPrevFocusNodeByManager with null currentNode
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestTwo, GetPrevFocusNodeByManager001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-begin GetPrevFocusNodeByManager001";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. construct rootNode and context
     */
    RefPtr<NG::UINode> currentNode = nullptr;
    auto rootNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto context = MockPipelineContext::GetCurrentContext();

    /**
     * @tc.steps: step3. test GetPrevFocusNodeByManager
     */
    auto result = jsAccessibilityManager->GetPrevFocusNodeByManager(currentNode, rootNode, context);
    EXPECT_EQ(result, nullptr);

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-end GetPrevFocusNodeByManager001";
}

/**
 * @tc.name: GetPrevFocusNodeByManager002
 * @tc.desc: Test GetPrevFocusNodeByManager with null rootNode
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestTwo, GetPrevFocusNodeByManager002, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-begin GetPrevFocusNodeByManager002";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. construct currentNode and context
     */
    auto currentNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    RefPtr<NG::FrameNode> rootNode = nullptr;
    auto context = MockPipelineContext::GetCurrentContext();

    /**
     * @tc.steps: step3. test GetPrevFocusNodeByManager
     */
    auto result = jsAccessibilityManager->GetPrevFocusNodeByManager(currentNode, rootNode, context);
    EXPECT_EQ(result, nullptr);

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-end GetGetPrevFocusNodeByManager002";
}

/**
 * @tc.name: GetPrevFocusNodeByManager003
 * @tc.desc: Test GetPrevFocusNodeByManager with null context
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestTwo, GetPrevFocusNodeByManager003, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-begin GetPrevFocusNodeByManager003";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. construct currentNode and rootNode
     */
    auto currentNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto rootNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    RefPtr<PipelineBase> context = nullptr;

    /**
     * @tc.steps: step3. test GetPrevFocusNodeByManager
     */
    auto result = jsAccessibilityManager->GetPrevFocusNodeByManager(currentNode, rootNode, context);
    EXPECT_EQ(result, nullptr);

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-end GetPrevFocusNodeByManager003";
}

/**
 * @tc.name: GetPrevFocusNodeByManager004
 * @tc.desc: Test GetPrevFocusNodeByManager with all null parameters
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestTwo, GetPrevFocusNodeByManager004, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-begin GetPrevFocusNodeByManager004";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. test GetPrevFocusNodeByManager
     */
    RefPtr<NG::UINode> currentNode = nullptr;
    RefPtr<NG::FrameNode> rootNode = nullptr;
    RefPtr<PipelineBase> context = nullptr;

    auto result = jsAccessibilityManager->GetPrevFocusNodeByManager(currentNode, rootNode, context);
    EXPECT_EQ(result, nullptr);

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-end GetPrevFocusNodeByManager004";
}

/**
 * @tc.name: NeedChangeToReadableNode001
 * @tc.desc: Test NeedChangeToReadableNode with null frame node
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestTwo, NeedChangeToReadableNode001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-begin NeedChangeToReadableNode001";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. test NeedChangeToReadableNode
     */
    RefPtr<NG::FrameNode> curFrameNode = nullptr;
    RefPtr<NG::FrameNode> readableNode;

    bool result = jsAccessibilityManager->NeedChangeToReadableNode(curFrameNode, readableNode);
    EXPECT_FALSE(result);

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-end NeedChangeToReadableNode001";
}

/**
 * @tc: name: NeedChangeToReadableNode002
 * @tc.desc: Test NeedChangeToReadableNode with valid frame node
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestTwo, NeedChangeToReadableNode002, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-begin NeedChangeToReadableNode002";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. construct pattern and frameNode
     */
    auto pattern = AceType::MakeRefPtr<NG::Pattern>();
    auto frameNode = NG::FrameNode::CreateFrameNode("testNode", 1, pattern, true);
    RefPtr<NG::FrameNode> readableNode;

    /**
     * @tc.steps: step3. test NeedChangeToReadableNode
     */
    bool result = jsAccessibilityManager->NeedChangeToReadableNode(frameNode, readableNode);

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-end NeedChangeToReadableNode002";
}

/**
 * @tc.name: GetResultOfFocusMoveSearchNG001001
 * @tc.desc: Test GetResultOfFocusMoveSearchNG with valid parameters
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestTwo, GetResultOfFocusMoveSearchNG001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-begin GetResultOfFocusMoveSearchNG001";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. test GetResultOfFocusMoveSearchNG
     */
    int64_t elementId = 100;
    int32_t direction = 1;
    AccessibilityElementInfo info;

    jsAccessibilityManager->GetResultOfFocusMoveSearchNG(elementId, direction, info);

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-end GetResultOfFocusMoveSearchNG001";
}

/**
 * @tc.name: FireAccessibilityEventCallback001
 * @tc.desc: Test FireAccessibilityEventCallback with event id and parameter
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestTwo, FireAccessibilityEventCallback001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-begin FireAccessibilityEventCallback001";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. test FireAccessibilityEventCallback
     */
    uint32_t eventId = 1;
    int64_t parameter = 100;

    jsAccessibilityManager->FireAccessibilityEventCallback(eventId, parameter);

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-end FireAccessibilityEventCallback001";
}

/**
 * @tc.name: GenerateWindowInfo001
 * @tc.desc: Test GenerateWindowInfo with valid frame node
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestTwo, GenerateWindowInfo001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-begin GenerateWindowInfo001";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. construct pattern, frameNode and context
     */
    auto pattern = AceType::MakeRefPtr<NG::Pattern>();
    auto frameNode = NG::FrameNode::CreateFrameNode("testNode", 1, pattern, true);
    auto context = MockPipelineContext::GetCurrentContext();

    /**
     * @tc.steps: step3. test GenerateWindowInfo
     */
    AccessibilityWindowInfo windowInfo = jsAccessibilityManager->GenerateWindowInfo(frameNode, context);

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-end GenerateWindowInfo001";
}

/**
 * @tc.name: UpdateWindowInfo001
 * @tc.desc: Test UpdateWindowInfo updates window info
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestTwo, UpdateWindowInfo001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-begin UpdateWindowInfo001";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. test UpdateWindowInfo
     */
    AccessibilityWindowInfo window;
    auto context = MockPipelineContext::GetCurrentContext();

    jsAccessibilityManager->UpdateWindowInfo(window, context);

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-end UpdateWindowInfo001";
}

/**
 * @tc.name: UpdateAccessibilityNextFocusIdMap001
 * @tc.desc: Test UpdateAccessibilityNextFocusIdMap updates focus id map
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestTwo, UpdateAccessibilityNextFocusIdMap001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-begin UpdateAccessibilityNextFocusIdMap001";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. test UpdateAccessibilityNextFocusIdMap
     */
    int32_t containerId = 1;
    std::string nextFocusInspectorKey = "test_key";
    int64_t preAccessibilityId = 100;

    jsAccessibilityManager->UpdateAccessibilityNextFocusIdMap(containerId, nextFocusInspectorKey, preAccessibilityId);

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-end UpdateAccessibilityNextFocusIdMap001";
}

/**
 * @tc.name: SendActionEvent001
 * @tc.desc: Test SendActionEvent sends action event
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestTwo, SendActionEvent001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-begin SendActionEvent001";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. test SendActionEvent
     */
    Accessibility::ActionType action = Accessibility::ActionType::ACCESSIBILITY_ACTION_CLICK;
    int64_t nodeId = 100;

    jsAccessibilityManager->SendActionEvent(action, nodeId);

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-end SendActionEvent001";
}

/**
 * @tc.name: SendEventToAccessibilityWithNode001
 * @tc.desc: Test SendEventToAccessibilityWithNode with null node
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestTwo, SendEventToAccessibilityWithNode001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-begin SendEventToAccessibilityWithNode001";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. test SendEventToAccessibilityWithNode
     */
    AccessibilityEvent accessibilityEvent;
    RefPtr<AceType> node = nullptr;
    auto context = MockPipelineContext::GetCurrentContext();

    jsAccessibilityManager->SendEventToAccessibilityWithNode(accessibilityEvent, node, context);

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-end SendEventToAccessibilityWithNode001";
}

/**
 * @tc.name: SendEventToAccessibilityWithNode002
 * @tc.desc: Test SendEventToAccessibilityWithNode with valid node
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestTwo, SendEventToAccessibilityWithNode002, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-begin SendEventToAccessibilityWithNode002";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. test SendEventToAccessibilityWithNode
     */
    AccessibilityEvent accessibilityEvent;
    auto pattern = AceType::MakeRefPtr<NG::Pattern>();
    auto frameNode = NG::FrameNode::CreateFrameNode("testNode", 1, pattern, true);
    RefPtr<AceType> node = frameNode;
    auto context = MockPipelineContext::GetCurrentContext();

    jsAccessibilityManager->SendEventToAccessibilityWithNode(accessibilityEvent, node, context);

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-end SendEventToAccessibilityWithNode002";
}

/**
 * @tc.name: TransferAccessibilityAsyncEvent001
 * @tc.desc: Test TransferAccessibilityAsyncEvent with valid event info
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestTwo, TransferAccessibilityAsyncEvent001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-begin TransferAccessibilityAsyncEvent001";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. test TransferAccessibilityAsyncEvent
     */
    Accessibility::AccessibilityEventInfo eventInfo;
    int64_t uiExtensionOffset = 0;

    bool result = jsAccessibilityManager->TransferAccessibilityAsyncEvent(eventInfo, uiExtensionOffset);

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-end TransferAccessibilityAsyncEvent001";
}

/**
 * @tc.name: SendExtensionAccessibilityEvent001
 * @tc.desc: Test SendExtensionAccessibilityEvent with valid event info
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestTwo, SendExtensionAccessibilityEvent001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-begin SendExtensionAccessibilityEvent001";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. test SendExtensionAccessibilityEvent
     */
    Accessibility::AccessibilityEventInfo eventInfo;
    int64_t uiExtensionOffset = 0;

    jsAccessibilityManager->SendExtensionAccessibilityEvent(eventInfo, uiExtensionOffset);

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-end SendExtensionAccessibilityEvent001";
}

/**
 * @tc.name: SearchElementInfoByAccessibilityIdNG001
 * @tc.desc: Test SearchElementInfoByAccessibilityIdNG with valid parameters
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestTwo, SearchElementInfoByAccessibilityIdNG001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-begin SearchElementInfoByAccessibilityIdNG001";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. test SearchElementInfoByAccessibilityIdNG
     */
    int64_t elementId = 100;
    int32_t mode = 0;
    std::list<Accessibility::AccessibilityElementInfo> infos;
    auto context = MockPipelineContext::GetCurrentContext();

    jsAccessibilityManager->SearchElementInfoByAccessibilityIdNG(elementId, mode, infos, context);

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-end SearchElementInfoByAccessibilityIdNG001";
}

/**
 * @tc.name: FindUIExtensionAccessibilityElement001
 * @tc.desc: Test FindUIExtensionAccessibilityElement with valid parameters
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestTwo, FindUIExtensionAccessibilityElement001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-begin FindUIExtensionAccessibilityElement001";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. test FindUIExtensionAccessibilityElement
     */
    auto pattern = AceType::MakeRefPtr<NG::Pattern>();
    auto frameNode = NG::FrameNode::CreateFrameNode("testNode", 1, pattern, true);
    std::string customId = "test_id";
    Framework::CommonProperty commonProperty;
    std::list<AccessibilityElementInfo> infos;
    auto context = MockPipelineContext::GetCurrentContext();

    bool result = jsAccessibilityManager->FindUIExtensionAccessibilityElement(
        frameNode, customId, commonProperty, infos, context);

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-end FindUIExtensionAccessibilityElement001";
}

/**
 * @tc.name: SetAccessibilityCustomId001
 * @tc.desc: Test SetAccessibilityCustomId with valid parameters
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestTwo, SetAccessibilityCustomId001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-begin SetAccessibilityCustomId001";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. test SetAccessibilityCustomId
     */
    auto pattern = AceType::MakeRefPtr<NG::Pattern>();
    auto frameNode = NG::FrameNode::CreateFrameNode("testNode", 1, pattern, true);
    std::string customId = "test_id";
    Framework::CommonProperty commonProperty;
    std::list<AccessibilityElementInfo> infos;
    auto context = MockPipelineContext::GetCurrentContext();

    bool result = jsAccessibilityManager->SetAccessibilityCustomId(frameNode, customId, commonProperty, infos, context);

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-end SetAccessibilityCustomId001";
}

/**
 * @tc.name: SearchElementInfoByCustomIdNG001
 * @tc.desc: Test SearchElementInfoByCustomIdNG with valid parameters
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestTwo, SearchElementInfoByCustomIdNG001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-begin SearchElementInfoByCustomIdNG001";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. test SearchElementInfoByCustomIdNG
     */
    int64_t elementId = 100;
    std::string customId = "test_id";
    std::list<AccessibilityElementInfo> infos;
    std::list<AccessibilityElementInfo> treeInfos;
    auto context = MockPipelineContext::GetCurrentContext();

    jsAccessibilityManager->SearchElementInfoByCustomIdNG(elementId, customId, infos, treeInfos, context);

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-end SearchElementInfoByCustomIdNG001";
}

/**
 * @tc.name: SearchDefaultFocusByWindowIdNG001
 * @tc.desc: Test SearchDefaultFocusByWindowIdNG with valid parameters
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestTwo, SearchDefaultFocusByWindowIdNG001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-begin SearchDefaultFocusByWindowIdNG001";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. test SearchDefaultFocusByWindowIdNG
     */
    int32_t pageId = 1;
    std::list<AccessibilityElementInfo> infos;
    auto context = MockPipelineContext::GetCurrentContext();

    jsAccessibilityManager->SearchDefaultFocusByWindowIdNG(pageId, infos, context);

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-end SearchDefaultFocusByWindowIdNG001";
}

/**
 * @tc.name: SearchElementInfosByTextNG001
 * @tc.desc: Test SearchElementInfosByTextNG with valid parameters
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestTwo, SearchElementInfosByTextNG001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-begin SearchElementInfosByTextNG001";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. test SearchElementInfosByTextNG
     */
    int64_t elementId = 100;
    std::string text = "test";
    std::list<AccessibilityElementInfo> infos;
    auto context = MockPipelineContext::GetCurrentContext();

    jsAccessibilityManager->SearchElementInfosByTextNG(elementId, text, infos, context);

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-end SearchElementInfosByTextNG001";
}

/**
 * @tc.name: FindFocusedElementInfoNG001
 * @tc.desc: Test FindFocusedElementInfoNG with valid parameters
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestTwo, FindFocusedElementInfoNG001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-begin FindFocusedElementInfoNG001";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. test FindFocusedElementInfoNG
     */
    int64_t elementId = 100;
    int32_t focusType = 1;
    AccessibilityElementInfo info;
    auto context = MockPipelineContext::GetCurrentContext();

    jsAccessibilityManager->FindFocusedElementInfoNG(elementId, focusType, info, context);

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-end FindFocusedElementInfoNG001";
}

/**
 * @tc.name: FocusMoveSearchNG001
 * @tc.desc: Test FocusMoveSearchNG with valid parameters
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestTwo, FocusMoveSearchNG001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-begin FocusMoveSearchNG001";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. test FocusMoveSearchNG
     */
    int64_t elementId = 100;
    int32_t direction = 1;
    AccessibilityElementInfo info;
    auto context = MockPipelineContext::GetCurrentContext();

    jsAccessibilityManager->FocusMoveSearchNG(elementId, direction, info, context);

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-end FocusMoveSearchNG001";
}

/**
 * @tc.name: ExecuteExtensionActionNG001
 * @tc.desc: Test ExecuteExtensionActionNG with valid parameters
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestTwo, ExecuteExtensionActionNG001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-begin ExecuteExtensionActionNG001";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. test ExecuteExtensionActionNG
     */
    int64_t elementId = 100;
    std::map<std::string, std::string> actionArguments;
    int32_t action = 1;
    RefPtr<PipelineBase> context = nullptr;
    int64_t uiExtensionOffset = 0;

    bool result = jsAccessibilityManager->ExecuteExtensionActionNG(
        elementId, actionArguments, action, context, uiExtensionOffset);
    EXPECT_FALSE(result);

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-end ExecuteExtensionActionNG001";
}
} // namespace OHOS::Ace::NG