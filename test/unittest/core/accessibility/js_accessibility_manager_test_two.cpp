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
    GetInfoByNodeId infoOfNode;
    infoOfNode.componentType = "Stack";
    infoOfNode.pageId = 666;
    info.nodeInstanceId = 777;
    jsAccessibilityManager->GetComponentTypeAndPageIdByNodeId(-1LL, context, infoOfNode);
    EXPECT_EQ(infoOfNode.componentType, "Stack");
    EXPECT_EQ(infoOfNode.pageId, 666);
    EXPECT_EQ(infoOfNode.nodeInstanceId, 777);

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestTwo-end GetComponentTypeAndPageIdByNodeIdTest001";
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
} // namespace OHOS::Ace::NG