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
#include "core/components_ng/pattern/pattern.h"
#include "frameworks/core/accessibility/utils/accessibility_action_function_utils.h"
#include "interfaces/inner_api/ace_kit/src/view/ui_context_impl.h"


using namespace OHOS::Accessibility;
using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
namespace {
} // namespace


class AccessibilityActionFunctionUtilsTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();

    bool processFlag1_ = false;
    bool processFlag2_ = false;
    bool processFlag3_ = false;

    int32_t processType1_ = -1;
    int32_t processType2_ = -1;
};

void AccessibilityActionFunctionUtilsTest::SetUpTestCase()
{
    std::unique_ptr<std::ostream> ostream = std::make_unique<std::ostringstream>();
    ASSERT_NE(ostream, nullptr);
    DumpLog::GetInstance().SetDumpFile(std::move(ostream));
}

void AccessibilityActionFunctionUtilsTest::TearDownTestCase()
{
}

/**
 * @tc.name: AccessibilityActionFunctionUtilsTest001
 * @tc.desc: AddMultipleNodes
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityActionFunctionUtilsTest, AccessibilityActionFunctionUtilsTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct framenodes
     */
    auto frameNode1 = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), false);
    CHECK_NULL_VOID(frameNode1);
    auto frameNode2 = FrameNode::CreateFrameNode("framenode", 2, AceType::MakeRefPtr<Pattern>(), false);
    CHECK_NULL_VOID(frameNode2);
    frameNode2->MountToParent(frameNode1);
    frameNode1->AddChild(frameNode2);
    auto frameNode3 = FrameNode::CreateFrameNode("framenode", 3, AceType::MakeRefPtr<Pattern>(), false);
    CHECK_NULL_VOID(frameNode3);
    frameNode3->MountToParent(frameNode2);
    frameNode2->AddChild(frameNode3);

    /**
    * @tc.steps: step2. framenode2 set callback.
    * @tc.expected: callback can be handled, when framenode3 HandleNotifyChildAction.
    */
    processFlag1_ = false;
    processFlag2_ = false;
    processType1_ = -1;
    processType2_ = -1;
    auto accessibilityProperty2 = frameNode2->GetAccessibilityProperty<NG::AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty2);
    accessibilityProperty2->SetNotifyChildAction([this] (const RefPtr<FrameNode>& node,
        NotifyChildActionType childActionType) {
            this->processFlag1_ = true;
            this->processType1_ = static_cast<int32_t>(childActionType);
            return AccessibilityActionResult::ACTION_OK;
        }
    );

    auto result =  AccessibilityFunctionUtils::HandleNotifyChildAction(frameNode3, NotifyChildActionType::ACTION_CLICK);
    EXPECT_TRUE(processFlag1_);
    EXPECT_EQ(processType1_, static_cast<int32_t>(NotifyChildActionType::ACTION_CLICK));
}

/**
 * @tc.name: AccessibilityActionFunctionUtilsTest002
 * @tc.desc: AddMultipleNodes
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityActionFunctionUtilsTest, AccessibilityActionFunctionUtilsTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct framenodes
     */
    auto frameNode0 = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), false);
    CHECK_NULL_VOID(frameNode0);
    auto frameNode1 = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), false);
    CHECK_NULL_VOID(frameNode1);
    frameNode1->MountToParent(frameNode0);
    frameNode0->AddChild(frameNode1);
    auto frameNode2 = FrameNode::CreateFrameNode("framenode", 2, AceType::MakeRefPtr<Pattern>(), false);
    CHECK_NULL_VOID(frameNode2);
    frameNode2->MountToParent(frameNode1);
    frameNode1->AddChild(frameNode2);
    auto frameNode3 = FrameNode::CreateFrameNode("framenode", 3, AceType::MakeRefPtr<Pattern>(), false);
    CHECK_NULL_VOID(frameNode3);
    frameNode3->MountToParent(frameNode2);
    frameNode2->AddChild(frameNode3);

    /**
    * @tc.steps: step2. framenode0 framenode2 set callback. framenode2 need to bubble up
    * @tc.expected: callback of framenode0 and framenode2 can be handled, when framenode3 HandleNotifyChildAction.
    */
    processFlag1_ = false;
    processFlag2_ = false;
    processType1_ = -1;
    processType2_ = -1;
    auto accessibilityProperty2 = frameNode2->GetAccessibilityProperty<NG::AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty2);
    accessibilityProperty2->SetNotifyChildAction([this] (const RefPtr<FrameNode>& node,
        NotifyChildActionType childActionType) {
            this->processFlag1_ = true;
            this->processType1_ = static_cast<int32_t>(childActionType);
            return AccessibilityActionResult::ACTION_RISE;
        }
    );

    auto accessibilityProperty0 = frameNode0->GetAccessibilityProperty<NG::AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty0);
    accessibilityProperty0->SetNotifyChildAction([this] (const RefPtr<FrameNode>& node,
        NotifyChildActionType childActionType) {
            this->processFlag2_ = true;
            this->processType2_ = static_cast<int32_t>(childActionType);
            return AccessibilityActionResult::ACTION_OK;
        }
    );

    auto result =  AccessibilityFunctionUtils::HandleNotifyChildAction(frameNode3, NotifyChildActionType::ACTION_CLICK);
    EXPECT_TRUE(processFlag1_);
    EXPECT_TRUE(processFlag2_);
    EXPECT_EQ(processType1_, static_cast<int32_t>(NotifyChildActionType::ACTION_CLICK));
    EXPECT_EQ(processType2_, static_cast<int32_t>(NotifyChildActionType::ACTION_CLICK));
}

/**
 * @tc.name: AccessibilityActionFunctionUtilsTest003
 * @tc.desc: AddMultipleNodes
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityActionFunctionUtilsTest, AccessibilityActionFunctionUtilsTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct framenodes
     */
    auto frameNode1 = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), false);
    CHECK_NULL_VOID(frameNode1);
    auto frameNode2 = FrameNode::CreateFrameNode("framenode", 2, AceType::MakeRefPtr<Pattern>(), false);
    CHECK_NULL_VOID(frameNode2);
    frameNode2->MountToParent(frameNode1);
    frameNode1->AddChild(frameNode2);
    auto frameNode3 = FrameNode::CreateFrameNode("framenode", 3, AceType::MakeRefPtr<Pattern>(), false);
    CHECK_NULL_VOID(frameNode3);
    frameNode3->MountToParent(frameNode2);
    frameNode2->AddChild(frameNode3);

    /**
    * @tc.steps: step2. framenode1 framenode2 set callback.
    * @tc.expected: callback of framenode0  framenode1 framenode2 framenode3 can be handled,
    * when no callcack is setted in framenode3.
    */

    processFlag1_ = false;
    processFlag2_ = false;
    processFlag3_ = false;

    auto accessibilityProperty1 = frameNode1->GetAccessibilityProperty<NG::AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty1);
    accessibilityProperty1->SetAccessibilityActionIntercept(
        [this] (AccessibilityInterfaceAction accessibilityInterfaceAction) {
            this->processFlag1_ = true;
            return AccessibilityActionInterceptResult::ACTION_CONTINUE;
        }
    );

    auto accessibilityProperty2 = frameNode2->GetAccessibilityProperty<NG::AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty2);
    accessibilityProperty2->SetAccessibilityActionIntercept(
        [this] (AccessibilityInterfaceAction accessibilityInterfaceAction) {
            this->processFlag2_ = true;
            return AccessibilityActionInterceptResult::ACTION_INTERCEPT;
        }
    );

    auto result =  AccessibilityFunctionUtils::HandleAccessibilityActionIntercept(frameNode3,
        AccessibilityInterfaceAction::ACCESSIBILITY_CLICK);
    EXPECT_FALSE(processFlag3_);
    EXPECT_FALSE(processFlag2_);
    EXPECT_FALSE(processFlag1_);
}

/**
 * @tc.name: AccessibilityActionFunctionUtilsTest004
 * @tc.desc: AddMultipleNodes
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityActionFunctionUtilsTest, AccessibilityActionFunctionUtilsTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct framenodes
     */
    auto frameNode1 = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), false);
    CHECK_NULL_VOID(frameNode1);
    auto frameNode2 = FrameNode::CreateFrameNode("framenode", 2, AceType::MakeRefPtr<Pattern>(), false);
    CHECK_NULL_VOID(frameNode2);
    frameNode2->MountToParent(frameNode1);
    frameNode1->AddChild(frameNode2);
    auto frameNode3 = FrameNode::CreateFrameNode("framenode", 3, AceType::MakeRefPtr<Pattern>(), false);
    CHECK_NULL_VOID(frameNode3);
    frameNode3->MountToParent(frameNode2);
    frameNode2->AddChild(frameNode3);

    /**
    * @tc.steps: step2. framenode0  framenode1 framenode2 framenode3 set callback. framenode3 need to bubble up
    * @tc.expected: callback of framenode1 can be handled, when framenode3 HandleAccessibilityActionIntercept.
    */

    processFlag1_ = false;
    processFlag2_ = false;
    processFlag3_ = false;

    auto accessibilityProperty1 = frameNode1->GetAccessibilityProperty<NG::AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty1);
    accessibilityProperty1->SetAccessibilityActionIntercept(
        [this] (AccessibilityInterfaceAction accessibilityInterfaceAction) {
            this->processFlag1_ = true;
            return AccessibilityActionInterceptResult::ACTION_CONTINUE;
        }
    );

    auto accessibilityProperty3 = frameNode3->GetAccessibilityProperty<NG::AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty3);
    accessibilityProperty3->SetAccessibilityActionIntercept(
        [this] (AccessibilityInterfaceAction accessibilityInterfaceAction) {
            this->processFlag3_ = true;
            return AccessibilityActionInterceptResult::ACTION_RISE;
        }
    );
    auto result =  AccessibilityFunctionUtils::HandleAccessibilityActionIntercept(frameNode3,
        AccessibilityInterfaceAction::ACCESSIBILITY_CLICK);
    EXPECT_TRUE(processFlag3_);
    EXPECT_TRUE(processFlag1_);
}
} // namespace OHOS::Ace::NG