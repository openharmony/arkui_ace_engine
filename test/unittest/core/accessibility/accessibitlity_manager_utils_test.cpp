/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "adapter/ohos/entrance/ace_container.h"
#include "base/log/dump_log.h"
#include "frameworks/core/accessibility/utils/accessibility_manager_utils.h"
#include "interfaces/inner_api/ace_kit/src/view/ui_context_impl.h"

using namespace OHOS::Accessibility;
using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
namespace {
} // namespace


class AccessibilityManagerUtilsTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void AccessibilityManagerUtilsTest::SetUpTestCase()
{
    std::unique_ptr<std::ostream> ostream = std::make_unique<std::ostringstream>();
    ASSERT_NE(ostream, nullptr);
    DumpLog::GetInstance().SetDumpFile(std::move(ostream));
}

void AccessibilityManagerUtilsTest::TearDownTestCase()
{
}

/**
 * @tc.name: AccessibilityManagerUtilsTest001
 * @tc.desc: controller.Add
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTest, AccessibilityManagerUtilsTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    PageEventController controller;
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), false);
    auto context = AceType::MakeRefPtr<NG::PipelineContext>();
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(context);
    context->instanceId_ = 1;
    frameNode->AttachContext(AceType::RawPtr(context), false);
    /**
    * @tc.steps: step2. add controller with instanceId 1.
    * @tc.expected: Check instanceId 1 is not empty , other instanceId is empty.
    */
    controller.Add(frameNode);
    EXPECT_FALSE(controller.CheckEmpty(1));
    EXPECT_TRUE(controller.CheckEmpty(2));
}

/**
 * @tc.name: AccessibilityManagerUtilsTest002
 * @tc.desc: AddMultipleNodes
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTest, AccessibilityManagerUtilsTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    PageEventController controller;
    auto frameNode1 = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), false);
    auto context1 = AceType::MakeRefPtr<NG::PipelineContext>();
    CHECK_NULL_VOID(frameNode1);
    CHECK_NULL_VOID(context1);
    context1->instanceId_ = 1;
    frameNode1->AttachContext(AceType::RawPtr(context1), false);

    auto frameNode2 = FrameNode::CreateFrameNode("framenode", 2, AceType::MakeRefPtr<Pattern>(), false);
    auto context2 = AceType::MakeRefPtr<NG::PipelineContext>();
    CHECK_NULL_VOID(frameNode2);
    CHECK_NULL_VOID(context2);
    context2->instanceId_ = 2;
    frameNode2->AttachContext(AceType::RawPtr(context2), false);

    auto frameNode3 = FrameNode::CreateFrameNode("framenode", 3, AceType::MakeRefPtr<Pattern>(), false);
    auto context3 = AceType::MakeRefPtr<NG::PipelineContext>();
    CHECK_NULL_VOID(frameNode3);
    CHECK_NULL_VOID(context3);
    context3->instanceId_ = 3;
    frameNode3->AttachContext(AceType::RawPtr(context3), false);

    /**
    * @tc.steps: step2. add controller with three different node.
    * @tc.expected: all node can be checked in controller.
    */
    controller.Add(frameNode1);
    controller.Add(frameNode2);
    controller.Add(frameNode3);
    EXPECT_TRUE(controller.CheckNode(frameNode1, false));
    EXPECT_TRUE(controller.CheckNode(frameNode2, false));
    EXPECT_TRUE(controller.CheckNode(frameNode3, false));
}

/**
 * @tc.name: AccessibilityManagerUtilsTest003
 * @tc.desc: CheckExistingNode
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTest, AccessibilityManagerUtilsTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    PageEventController controller;
    auto frameNode1 = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), false);
    auto context1 = AceType::MakeRefPtr<NG::PipelineContext>();
    CHECK_NULL_VOID(frameNode1);
    CHECK_NULL_VOID(context1);
    context1->instanceId_ = 1;
    frameNode1->AttachContext(AceType::RawPtr(context1), false);

    auto frameNode2 = FrameNode::CreateFrameNode("framenode", 2, AceType::MakeRefPtr<Pattern>(), false);
    auto context2 = AceType::MakeRefPtr<NG::PipelineContext>();
    CHECK_NULL_VOID(frameNode2);
    CHECK_NULL_VOID(context2);
    context2->instanceId_ = 2;
    frameNode2->AttachContext(AceType::RawPtr(context2), false);

    /**
    * @tc.steps: step2. add controller one node .
    * @tc.expected: only added node can be checked in controller.
    */
    controller.Add(frameNode1);
    EXPECT_TRUE(controller.CheckNode(frameNode1, false));
    EXPECT_FALSE(controller.CheckNode(frameNode2, false));
}


/**
 * @tc.name: AccessibilityManagerUtilsTest004
 * @tc.desc: DeleteNodeOnCheck
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTest, AccessibilityManagerUtilsTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    PageEventController controller;
    auto frameNode1 = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), false);
    auto context1 = AceType::MakeRefPtr<NG::PipelineContext>();
    CHECK_NULL_VOID(frameNode1);
    CHECK_NULL_VOID(context1);
    context1->instanceId_ = 1;
    frameNode1->AttachContext(AceType::RawPtr(context1), false);

    /**
    * @tc.steps: step2. add controller one node and check node with delete process .
    * @tc.expected: the first time can be checked and turns to empty after checking process.
    */
    controller.Add(frameNode1);
    EXPECT_TRUE(controller.CheckNode(frameNode1, true));
    EXPECT_FALSE(controller.CheckNode(frameNode1, false));
    EXPECT_TRUE(controller.CheckEmpty(1));
}

/**
 * @tc.name: AccessibilityManagerUtilsTest005
 * @tc.desc: UpdateClearsInvalidNodes
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTest, AccessibilityManagerUtilsTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    PageEventController controller;
    
    {
        auto frameNode1 = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), false);
        auto context1 = AceType::MakeRefPtr<NG::PipelineContext>();
        CHECK_NULL_VOID(frameNode1);
        CHECK_NULL_VOID(context1);
        context1->instanceId_ = 1;
        frameNode1->AttachContext(AceType::RawPtr(context1), false);
        controller.Add(frameNode1);
    }
    
    /**
    * @tc.steps: step2. update and check node  when node is null.
    * @tc.expected: update can delete null node and  controller will be empty.
    */
    controller.Update();
    EXPECT_TRUE(controller.CheckEmpty(3));
}

/**
 * @tc.name: AccessibilityManagerUtilsTest006
 * @tc.desc: UpdateKeepsValidNodes
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTest, AccessibilityManagerUtilsTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    PageEventController controller;
    auto frameNode1 = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), false);
    auto context1 = AceType::MakeRefPtr<NG::PipelineContext>();
    CHECK_NULL_VOID(frameNode1);
    CHECK_NULL_VOID(context1);
    context1->instanceId_ = 1;
    frameNode1->AttachContext(AceType::RawPtr(context1), false);

    /**
    * @tc.steps: step2. update and check node  when node is Valid.
    * @tc.expected: update will not delete null node and  controller is not empty.
    */
    controller.Add(frameNode1);
    controller.Update();
    EXPECT_TRUE(controller.CheckNode(frameNode1, false));
}

/**
 * @tc.name: AccessibilityManagerUtilsTest007
 * @tc.desc: CheckEmptyForNonExistingContainer
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTest, AccessibilityManagerUtilsTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    PageEventController controller;
    /**
    * @tc.steps: step2. controller keeps empty when containerId is large.
    * @tc.expected: controller keeps empty.
    */
    EXPECT_TRUE(controller.CheckEmpty(999));
}

/**
 * @tc.name: AccessibilityManagerUtilsTest008
 * @tc.desc: MultipleContainerManagement
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTest, AccessibilityManagerUtilsTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    PageEventController controller;
    auto frameNode1 = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), false);
    auto context1 = AceType::MakeRefPtr<NG::PipelineContext>();
    CHECK_NULL_VOID(frameNode1);
    CHECK_NULL_VOID(context1);
    context1->instanceId_ = 1;
    frameNode1->AttachContext(AceType::RawPtr(context1), false);

    auto frameNode2 = FrameNode::CreateFrameNode("framenode", 2, AceType::MakeRefPtr<Pattern>(), false);
    auto context2 = AceType::MakeRefPtr<NG::PipelineContext>();
    CHECK_NULL_VOID(frameNode2);
    CHECK_NULL_VOID(context2);
    context2->instanceId_ = 3;
    frameNode2->AttachContext(AceType::RawPtr(context2), false);
    /**
    * @tc.steps: step2. add nodes with different containerID.
    * @tc.expected: the correct containerID check will not be empty, wrong containerID will be empty.
    */
    controller.Add(frameNode1);
    controller.Add(frameNode2);
    EXPECT_FALSE(controller.CheckEmpty(1));
    EXPECT_TRUE(controller.CheckEmpty(2));
    EXPECT_FALSE(controller.CheckEmpty(3));
}

/**
 * @tc.name: AccessibilityManagerUtilsTest009
 * @tc.desc: AddSameNodeMultipleTimes
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTest, AccessibilityManagerUtilsTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    PageEventController controller;
    auto frameNode1 = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), false);
    auto context1 = AceType::MakeRefPtr<NG::PipelineContext>();
    CHECK_NULL_VOID(frameNode1);
    CHECK_NULL_VOID(context1);
    context1->instanceId_ = 1;
    frameNode1->AttachContext(AceType::RawPtr(context1), false);

    /**
    * @tc.steps: step2. add same node with multiple times.
    * @tc.expected: Check instanceId 1 is not empty , other instanceId is empty.
    */
    controller.Add(frameNode1);
    controller.Add(frameNode1);
    EXPECT_TRUE(controller.CheckNode(frameNode1, true));
    EXPECT_FALSE(controller.CheckNode(frameNode1, false));
}

/**
 * @tc.name: AccessibilityManagerUtilsTest010
 * @tc.desc: CrossContainerOperations
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTest, AccessibilityManagerUtilsTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    PageEventController controller;
    auto frameNode1 = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), false);
    auto context1 = AceType::MakeRefPtr<NG::PipelineContext>();
    CHECK_NULL_VOID(frameNode1);
    CHECK_NULL_VOID(context1);
    context1->instanceId_ = 1;
    frameNode1->AttachContext(AceType::RawPtr(context1), false);
    auto frameNode2 = FrameNode::CreateFrameNode("framenode", 2, AceType::MakeRefPtr<Pattern>(), false);
    auto context2 = AceType::MakeRefPtr<NG::PipelineContext>();
    CHECK_NULL_VOID(frameNode2);
    CHECK_NULL_VOID(context2);
    context2->instanceId_ = 2;
    frameNode2->AttachContext(AceType::RawPtr(context2), false);
    /**
    * @tc.steps: step2. add controller with instanceId 1.
    * @tc.expected: check node with delete process will delete nodes, next time check will be empty.
    */
    controller.Add(frameNode1);
    controller.Add(frameNode2);
    EXPECT_TRUE(controller.CheckNode(frameNode1, true));
    EXPECT_TRUE(controller.CheckNode(frameNode2, false));
}
} // namespace OHOS::Ace::NG