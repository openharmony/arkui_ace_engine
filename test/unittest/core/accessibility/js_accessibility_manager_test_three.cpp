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

class JsAccessibilityManagerTestThree : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void JsAccessibilityManagerTestThree::SetUpTestCase()
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

void JsAccessibilityManagerTestThree::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: IsTagInEmbedComponent001
 * @tc.desc: Test IsTagInEmbedComponent with embed component tag
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestThree, IsTagInEmbedComponent001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-begin IsTagInEmbedComponent001";

    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    std::string embedTag = "embeddedObject";
    bool result = jsAccessibilityManager->IsTagInEmbedComponent(embedTag);
    EXPECT_TRUE(result);

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-end IsTagInEmbedComponent001";
}

/**
 * @tc.name: IsTagInEmbedComponent002
 * @tc.desc: Test IsTagInEmbedComponent with non-embed component tag
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestThree, IsTagInEmbedComponent002, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-begin IsTagInEmbedComponent002";

    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    std::string nonEmbedTag = "text";
    bool result = jsAccessibilityManager->IsTagInEmbedComponent(nonEmbedTag);
    EXPECT_FALSE(result);

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-end IsTagInEmbedComponent002";
}

/**
 * @tc.name: IsTagInEmbedComponent003
 * @tc.desc: Test IsTagInEmbedComponent with empty tag
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestThree, IsTagInEmbedComponent003, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-begin IsTagInEmbedComponent003";

    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    std::string emptyTag = "";
    bool result = jsAccessibilityManager->IsTagInEmbedComponent(emptyTag);
    EXPECT_FALSE(result);

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-end IsTagInEmbedComponent003";
}

/**
 * @tc.name: UpdateVirtualNodeFocus001
 * @tc.desc: Test UpdateVirtualNodeFocus with null lastFrameNode_
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestThree, UpdateVirtualNodeFocus001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-begin UpdateVirtualNodeFocus001";

    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    jsAccessibilityManager->lastFrameNode_.Reset();
    jsAccessibilityManager->UpdateVirtualNodeFocus();

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-end UpdateVirtualNodeFocus001";
}

/**
 * @tc.name: GetUECAccessibilityParentRectInfo001
 * @tc.desc: Test GetUECAccessibilityParentRectInfo with default values
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestThree, GetUECAccessibilityParentRectInfo001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-begin GetUECAccessibilityParentRectInfo001";

    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    AccessibilityParentRectInfo rectInfo = jsAccessibilityManager->GetUECAccessibilityParentRectInfo();

    EXPECT_EQ(rectInfo.left, 0);
    EXPECT_EQ(rectInfo.top, 0);
    EXPECT_EQ(rectInfo.scaleX, 1.0f);
    EXPECT_EQ(rectInfo.scaleY, 1.0f);

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-end GetUECAccessibilityParentRectInfo001";
}

/**
 * @tc.name: UpdateUECAccessibilityParentRectInfo001
 * @tc.desc: Test UpdateUECAccessibilityParentRectInfo with custom values
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestThree, UpdateUECAccessibilityParentRectInfo001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-begin UpdateUECAccessibilityParentRectInfo001";

    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    AccessibilityParentRectInfo inputRectInfo;
    inputRectInfo.left = 100;
    inputRectInfo.top = 200;
    inputRectInfo.scaleX = 1.5f;
    inputRectInfo.scaleY = 2.0f;
    inputRectInfo.isChanged = true;

    jsAccessibilityManager->UpdateUECAccessibilityParentRectInfo(inputRectInfo);

    AccessibilityParentRectInfo resultRectInfo = jsAccessibilityManager->GetUECAccessibilityParentRectInfo();

    EXPECT_TRUE(IsParentRectInfoEqual(inputRectInfo, resultRectInfo));

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-end UpdateUECAccessibilityParentRectInfo001";
}

/**
 * @tc.name: ConvertAceAction001
 * @tc.desc: Test ConvertAceAction with valid AceAction values
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestThree, ConvertAceAction001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-begin ConvertAceAction001";

    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    Accessibility::ActionType result = jsAccessibilityManager->ConvertAceAction(AceAction::ACTION_CLICK);
    EXPECT_EQ(result, Accessibility::ActionType::ACCESSIBILITY_ACTION_CLICK);

    result = jsAccessibilityManager->ConvertAceAction(AceAction::ACTION_LONG_CLICK);
    EXPECT_EQ(result, Accessibility::ActionType::ACCESSIBILITY_ACTION_LONG_CLICK);

    result = jsAccessibilityManager->ConvertAceAction(AceAction::ACTION_FOCUS);
    EXPECT_EQ(result, Accessibility::ActionType::ACCESSIBILITY_ACTION_FOCUS);

    result = jsAccessibilityManager->ConvertAceAction(AceAction::ACTION_CLEAR_FOCUS);
    EXPECT_EQ(result, Accessibility::ActionType::ACCESSIBILITY_ACTION_CLEAR_FOCUS);

    result = jsAccessibilityManager->ConvertAceAction(AceAction::ACTION_ACCESSIBILITY_FOCUS);
    EXPECT_EQ(result, Accessibility::ActionType::ACCESSIBILITY_ACTION_ACCESSIBILITY_FOCUS);

    result = jsAccessibilityManager->ConvertAceAction(AceAction::ACTION_CLEAR_ACCESSIBILITY_FOCUS);
    EXPECT_EQ(result, Accessibility::ActionType::ACCESSIBILITY_ACTION_CLEAR_ACCESSIBILITY_FOCUS);

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-end ConvertAceAction001";
}

/**
 * @tc.name: ConvertAceAction002
 * @tc.desc: Test ConvertAceAction with scroll actions
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestThree, ConvertAceAction002, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-begin ConvertAceAction002";

    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    Accessibility::ActionType result = jsAccessibilityManager->ConvertAceAction(AceAction::ACTION_SCROLL_FORWARD);
    EXPECT_EQ(result, Accessibility::ActionType::ACCESSIBILITY_ACTION_SCROLL_FORWARD);

    result = jsAccessibilityManager->ConvertAceAction(AceAction::ACTION_SCROLL_BACKWARD);
    EXPECT_EQ(result, Accessibility::ActionType::ACCESSIBILITY_ACTION_SCROLL_BACKWARD);

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-end ConvertAceAction002";
}

/**
 * @tc.name: ConvertAceAction003
 * @tc.desc: Test ConvertAceAction with text manipulation actions
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestThree, ConvertAceAction003, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-begin ConvertAceAction003";

    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    Accessibility::ActionType result = jsAccessibilityManager->ConvertAceAction(AceAction::ACTION_SET_TEXT);
    EXPECT_EQ(result, Accessibility::ActionType::ACCESSIBILITY_ACTION_SET_TEXT);

    result = jsAccessibilityManager->ConvertAceAction(AceAction::ACTION_COPY);
    EXPECT_EQ(result, Accessibility::ActionType::ACCESSIBILITY_ACTION_COPY);

    result = jsAccessibilityManager->ConvertAceAction(AceAction::ACTION_PASTE);
    EXPECT_EQ(result, Accessibility::ActionType::ACCESSIBILITY_ACTION_PASTE);

    result = jsAccessibilityManager->ConvertAceAction(AceAction::ACTION_CUT);
    EXPECT_EQ(result, Accessibility::ActionType::ACCESSIBILITY_ACTION_CUT);

    result = jsAccessibilityManager->ConvertAceAction(AceAction::ACTION_SELECT);
    EXPECT_EQ(result, Accessibility::ActionType::ACCESSIBILITY_ACTION_SELECT);

    result = jsAccessibilityManager->ConvertAceAction(AceAction::ACTION_CLEAR_SELECTION);
    EXPECT_EQ(result, Accessibility::ActionType::ACCESSIBILITY_ACTION_CLEAR_SELECTION);

    result = jsAccessibilityManager->ConvertAceAction(AceAction::ACTION_SET_SELECTION);
    EXPECT_EQ(result, Accessibility::ActionType::ACCESSIBILITY_ACTION_SET_SELECTION);

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-end ConvertAceAction003";
}

/**
 * @tc.name: ConvertAceAction004
 * @tc.desc: Test ConvertAceAction with text navigation actions
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestThree, ConvertAceAction004, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-begin ConvertAceAction004";

    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    Accessibility::ActionType result = jsAccessibilityManager->ConvertAceAction(AceAction::ACTION_NEXT_AT_MOVEMENT_GRANULARITY);
    EXPECT_EQ(result, Accessibility::ActionType::ACCESSIBILITY_ACTION_NEXT_TEXT);

    result = jsAccessibilityManager->ConvertAceAction(AceAction::ACTION_PREVIOUS_AT_MOVEMENT_GRANULARITY);
    EXPECT_EQ(result, Accessibility::ActionType::ACCESSIBILITY_ACTION_PREVIOUS_TEXT);

    result = jsAccessibilityManager->ConvertAceAction(AceAction::ACTION_SET_CURSOR_POSITION);
    EXPECT_EQ(result, Accessibility::ActionType::ACCESSIBILITY_ACTION_SET_CURSOR_POSITION);

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-end ConvertAceAction004";
}

/**
 * @tc.name: ConvertAceAction005
 * @tc.desc: Test ConvertAceAction with invalid action
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestThree, ConvertAceAction005, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-begin ConvertAceAction005";

    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    Accessibility::ActionType result = jsAccessibilityManager->ConvertAceAction(static_cast<AceAction>(999));
    EXPECT_EQ(result, Accessibility::ActionType::ACCESSIBILITY_ACTION_INVALID);

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-end ConvertAceAction005";
}

/**
 * @tc.name: SubscribeToastObserver001
 * @tc.desc: Test SubscribeToastObserver creates observer and subscribes
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestThree, SubscribeToastObserver001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-begin SubscribeToastObserver001";

    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    bool result = jsAccessibilityManager->SubscribeToastObserver();

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-end SubscribeToastObserver001";
}

/**
 * @tc.name: UnsubscribeToastObserver001
 * @tc.desc: Test UnsubscribeToastObserver with existing observer
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestThree, UnsubscribeToastObserver001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-begin UnsubscribeToastObserver001";

    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    jsAccessibilityManager->SubscribeToastObserver();
    bool result = jsAccessibilityManager->UnsubscribeToastObserver();

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-end UnsubscribeToastObserver001";
}

/**
 * @tc.name: SubscribeStateObserver001
 * @tc.desc: Test SubscribeStateObserver with context set
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestThree, SubscribeStateObserver001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-begin SubscribeStateObserver001";

    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    auto context = MockPipelineContext::GetCurrentContext();
    jsAccessibilityManager->SetPipelineContext(context);

    uint32_t eventType = AccessibilityStateEventType::EVENT_ACCESSIBILITY_STATE_CHANGED;
    bool result = jsAccessibilityManager->SubscribeStateObserver(eventType);

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-end SubscribeStateObserver001";
}

/**
 * @tc.name: UnsubscribeStateObserver001
 * @tc.desc: Test UnsubscribeStateObserver with subscribed observer
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestThree, UnsubscribeStateObserver001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-begin UnsubscribeStateObserver001";

    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    auto context = MockPipelineContext::GetCurrentContext();
    jsAccessibilityManager->SetPipelineContext(context);

    uint32_t eventType = AccessibilityStateEventType::EVENT_ACCESSIBILITY_STATE_CHANGED;
    jsAccessibilityManager->SubscribeStateObserver(eventType);
    bool result = jsAccessibilityManager->UnsubscribeStateObserver(eventType);

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-end UnsubscribeStateObserver001";
}

/**
 * @tc.name: GenerateAccessibilityWorkMode001
 * @tc.desc: Test GenerateAccessibilityWorkMode returns valid work mode
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestThree, GenerateAccessibilityWorkMode001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-begin GenerateAccessibilityWorkMode001";

    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    AccessibilityWorkMode workMode = jsAccessibilityManager->GenerateAccessibilityWorkMode();

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-end GenerateAccessibilityWorkMode001";
}

/**
 * @tc.name: GetScaleX001
 * @tc.desc: Test GetScaleX returns default value
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestThree, GetScaleX001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-begin GetScaleX001";

    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    float scaleX = jsAccessibilityManager->GetScaleX();
    EXPECT_EQ(scaleX, 1.0f);

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-end GetScaleX001";
}

/**
 * @tc.name: GetScaleY001
 * @tc.desc: Test GetScaleY returns default value
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestThree, GetScaleY001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-begin GetScaleY001";

    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    float scaleY = jsAccessibilityManager->GetScaleY();
    EXPECT_EQ(scaleY, 1.0f);

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-end GetScaleY001";
}

/**
 * @tc.name: GetWindowId001
 * @tc.desc: Test GetWindowId returns default value
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestThree, GetWindowId001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-begin GetWindowId001";

    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    uint32_t windowId = jsAccessibilityManager->GetWindowId();
    EXPECT_EQ(windowId, 0);

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-end GetWindowId001";
}

/**
 * @tc.name: SetWindowId001
 * @tc.desc: Test SetWindowId and GetWindowId
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestThree, SetWindowId001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-begin SetWindowId001";

    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    uint32_t testWindowId = 12345;
    jsAccessibilityManager->SetWindowId(testWindowId);

    uint32_t windowId = jsAccessibilityManager->GetWindowId();
    EXPECT_EQ(windowId, testWindowId);

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-end SetWindowId001";
}

/**
 * @tc.name: IsReentrantLimit001
 * @tc.desc: Test IsReentrantLimit returns default value
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestThree, IsReentrantLimit001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-begin IsReentrantLimit001";

    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    bool isReentrantLimit = jsAccessibilityManager->IsReentrantLimit();
    EXPECT_FALSE(isReentrantLimit);

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-end IsReentrantLimit001";
}

/**
 * @tc.name: SetReentrantLimit001
 * @tc.desc: Test SetReentrantLimit and IsReentrantLimit
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestThree, SetReentrantLimit001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-begin SetReentrantLimit001";

    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    jsAccessibilityManager->SetReentrantLimit(true);
    EXPECT_TRUE(jsAccessibilityManager->IsReentrantLimit());

    jsAccessibilityManager->SetReentrantLimit(false);
    EXPECT_FALSE(jsAccessibilityManager->IsReentrantLimit());

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-end SetReentrantLimit001";
}

/**
 * @tc.name: GetIsIgnoreAllAction001
 * @tc.desc: Test GetIsIgnoreAllAction returns default value
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestThree, GetIsIgnoreAllAction001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-begin GetIsIgnoreAllAction001";

    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    bool isIgnoreAllAction = jsAccessibilityManager->GetIsIgnoreAllAction();
    EXPECT_FALSE(isIgnoreAllAction);

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-end GetIsIgnoreAllAction001";
}

/**
 * @tc.name: SetIsIgnoreAllAction001
 * @tc.desc: Test SetIsIgnoreAllAction and GetIsIgnoreAllAction
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestThree, SetIsIgnoreAllAction001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-begin SetIsIgnoreAllAction001";

    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    jsAccessibilityManager->SetIsIgnoreAllAction(true);
    EXPECT_TRUE(jsAccessibilityManager->GetIsIgnoreAllAction());

    jsAccessibilityManager->SetIsIgnoreAllAction(false);
    EXPECT_FALSE(jsAccessibilityManager->GetIsIgnoreAllAction());

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-end SetIsIgnoreAllAction001";
}

/**
 * @tc.name: SaveLast001
 * @tc.desc: Test SaveLast stores elementId and frameNode
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestThree, SaveLast001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-begin SaveLast001";

    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    int64_t testElementId = 999;
    auto pattern = AceType::MakeRefPtr<NG::Pattern>();
    auto frameNode = NG::FrameNode::CreateFrameNode("testNode", 1, pattern, true);

    jsAccessibilityManager->SaveLast(testElementId, frameNode);

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-end SaveLast001";
}

/**
 * @tc.name: SaveCurrentFocusNodeSize001
 * @tc.desc: Test SaveCurrentFocusNodeSize with virtual node
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestThree, SaveCurrentFocusNodeSize001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-begin SaveCurrentFocusNodeSize001";

    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    auto pattern = AceType::MakeRefPtr<NG::Pattern>();
    auto frameNode = NG::FrameNode::CreateFrameNode("testNode", 1, pattern, true);

    jsAccessibilityManager->SaveCurrentFocusNodeSize(frameNode);

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-end SaveCurrentFocusNodeSize001";
}

/**
 * @tc.name: UpdateViewScale001
 * @tc.desc: Test UpdateViewScale updates scale values
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestThree, UpdateViewScale001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-begin UpdateViewScale001";

    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    auto context = MockPipelineContext::GetCurrentContext();
    jsAccessibilityManager->SetPipelineContext(context);

    jsAccessibilityManager->UpdateViewScale();

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-end UpdateViewScale001";
}

/**
 * @tc.name: UpdatePageMode001
 * @tc.desc: Test UpdatePageMode updates page mode
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestThree, UpdatePageMode001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-begin UpdatePageMode001";

    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    std::string testPageMode = "FULL_SILENT";
    jsAccessibilityManager->UpdatePageMode(testPageMode);

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-end UpdatePageMode001";
}

/**
 * @tc.name: GetTreeId001
 * @tc.desc: Test GetTreeId returns default tree id
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestThree, GetTreeId001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-begin GetTreeId001";

    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    int32_t treeId = jsAccessibilityManager->GetTreeId();
    EXPECT_EQ(treeId, 0);

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-end GetTreeId001";
}

/**
 * @tc.name: GetTreeId002
 * @tc.desc: Test GetTreeId with specific instance id
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestThree, GetTreeId002, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-begin GetTreeId002";

    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    int32_t instanceId = 1;
    int32_t treeId = jsAccessibilityManager->GetTreeId(instanceId);

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-end GetTreeId002";
}

/**
 * @tc.name: IsScreenReaderEnabled001
 * @tc.desc: Test IsScreenReaderEnabled returns default value
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestThree, IsScreenReaderEnabled001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-begin IsScreenReaderEnabled001";

    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    bool isEnabled = jsAccessibilityManager->IsScreenReaderEnabled();
    EXPECT_FALSE(isEnabled);

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-end IsScreenReaderEnabled001";
}

/**
 * @tc.name: ClearCurrentFocus001
 * @tc.desc: Test ClearCurrentFocus with context set
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestThree, ClearCurrentFocus001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-begin ClearCurrentFocus001";

    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    auto context = MockPipelineContext::GetCurrentContext();
    jsAccessibilityManager->SetPipelineContext(context);

    bool result = jsAccessibilityManager->ClearCurrentFocus();

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-end ClearCurrentFocus001";
}

/**
 * @tc.name: ShouldSkipAccessibilityStateChange001
 * @tc.desc: Test ShouldSkipAccessibilityStateChange with null pipeline
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestThree, ShouldSkipAccessibilityStateChange001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-begin ShouldSkipAccessibilityStateChange001";

    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    RefPtr<PipelineBase> nullPipeline = nullptr;
    bool result = jsAccessibilityManager->ShouldSkipAccessibilityStateChange(nullPipeline);
    EXPECT_TRUE(result);

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-end ShouldSkipAccessibilityStateChange001";
}

/**
 * @tc.name: ShouldSkipAccessibilityStateChange002
 * @tc.desc: Test ShouldSkipAccessibilityStateChange with valid pipeline
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestThree, ShouldSkipAccessibilityStateChange002, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-begin ShouldSkipAccessibilityStateChange002";

    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    auto context = MockPipelineContext::GetCurrentContext();
    jsAccessibilityManager->SetPipelineContext(context);

    bool result = jsAccessibilityManager->ShouldSkipAccessibilityStateChange(context);

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-end ShouldSkipAccessibilityStateChange002";
}

/**
 * @tc.name: ReleaseCacheEvent001
 * @tc.desc: Test ReleaseCacheEvent clears cached events
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestThree, ReleaseCacheEvent001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-begin ReleaseCacheEvent001";

    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    jsAccessibilityManager->ReleaseCacheEvent();

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-end ReleaseCacheEvent001";
}

/**
 * @tc.name: ReleaseUIExtCacheEvent001
 * @tc.desc: Test ReleaseUIExtCacheEvent clears UI extension cached events
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestThree, ReleaseUIExtCacheEvent001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-begin ReleaseUIExtCacheEvent001";

    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    jsAccessibilityManager->ReleaseUIExtCacheEvent();

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-end ReleaseUIExtCacheEvent001";
}

/**
 * @tc.name: ResetBlockedEvent001
 * @tc.desc: Test ResetBlockedEvent resets blocked event state
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestThree, ResetBlockedEvent001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-begin ResetBlockedEvent001";

    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    jsAccessibilityManager->ResetBlockedEvent();

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-end ResetBlockedEvent001";
}

/**
 * @tc.name: AddFrameNodeToUecStatusVec001
 * @tc.desc: Test AddFrameNodeToUecStatusVec adds frame node to status vector
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestThree, AddFrameNodeToUecStatusVec001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-begin AddFrameNodeToUecStatusVec001";

    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    auto pattern = AceType::MakeRefPtr<NG::Pattern>();
    auto frameNode = NG::FrameNode::CreateFrameNode("testNode", 1, pattern, true);

    jsAccessibilityManager->AddFrameNodeToUecStatusVec(frameNode);

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-end AddFrameNodeToUecStatusVec001";
}

/**
 * @tc.name: AddFrameNodeToDefaultFocusList001
 * @tc.desc: Test AddFrameNodeToDefaultFocusList adds frame node to default focus list
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestThree, AddFrameNodeToDefaultFocusList001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-begin AddFrameNodeToDefaultFocusList001";

    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    auto pattern = AceType::MakeRefPtr<NG::Pattern>();
    auto frameNode = NG::FrameNode::CreateFrameNode("testNode", 1, pattern, true);

    jsAccessibilityManager->AddFrameNodeToDefaultFocusList(frameNode, true);

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-end AddFrameNodeToDefaultFocusList001";
}

/**
 * @tc.name: AddDefaultFocusNode001
 * @tc.desc: Test AddDefaultFocusNode adds node to default focus list
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestThree, AddDefaultFocusNode001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-begin AddDefaultFocusNode001";

    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    auto pattern = AceType::MakeRefPtr<NG::Pattern>();
    auto frameNode = NG::FrameNode::CreateFrameNode("testNode", 1, pattern, true);

    jsAccessibilityManager->AddDefaultFocusNode(frameNode);

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestThree-end AddDefaultFocusNode001";
}
} // namespace OHOS::Ace::NG
