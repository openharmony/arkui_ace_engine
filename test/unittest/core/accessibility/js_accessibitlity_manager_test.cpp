/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "accessibility_system_ability_client.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/log/dump_log.h"
#include "adapter/ohos/osal/js_accessibility_manager.h"
#include "frameworks/core/accessibility/accessibility_node.h"
#include "adapter/ohos/entrance/ace_container.h"

using namespace OHOS::Accessibility;
using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
namespace {
} // namespace

class MockAccessibilityChildTreeCallback : public AccessibilityChildTreeCallback {
public:
    explicit MockAccessibilityChildTreeCallback(int64_t accessibilityId)
        : AccessibilityChildTreeCallback(accessibilityId)
    {}

    ~MockAccessibilityChildTreeCallback() override = default;

    bool OnRegister(uint32_t windowId, int32_t treeId) override
    {
        return true;
    }

    bool OnDeregister() override
    {
        return true;
    }

    bool OnSetChildTree(int32_t childWindowId, int32_t childTreeId) override
    {
        return true;
    }

    bool OnDumpChildInfo(const std::vector<std::string>& params, std::vector<std::string>& info) override
    {
        return true;
    }

    void OnClearRegisterFlag() override
    {
        isReg_ = false;
    }

private:
    bool isReg_ = false;
};

class MockAccessibilitySAObserverCallback : public AccessibilitySAObserverCallback {
public:
    explicit MockAccessibilitySAObserverCallback(int64_t accessibilityId)
        : AccessibilitySAObserverCallback(accessibilityId)
    {}

    ~MockAccessibilitySAObserverCallback() override = default;

    bool OnState(bool state) override
    {
        return true;
    }
};

class JsAccessibilityManagerTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void JsAccessibilityManagerTest::SetUpTestCase()
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

void JsAccessibilityManagerTest::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

class MockJsAccessibilityManager : public Framework::JsAccessibilityManager {
public:
    MOCK_METHOD3(SendEventToAccessibilityWithNode,
        void(const AccessibilityEvent& accessibilityEvent,
            const RefPtr<AceType>& node, const RefPtr<PipelineBase>& context));
};

/**
 * @tc.name: JsAccessibilityManager001
 * @tc.desc: UpdateAccessibilityElementInfo
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTest, JsAccessibilityManager001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    Accessibility::AccessibilityElementInfo nodeInfo;
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
    accessibilityProperty->SetAccessibilityRole("test");
    accessibilityProperty->SetUserRangeCurrentValue(5);
    accessibilityProperty->SetUserRangeMinValue(1);
    accessibilityProperty->SetUserRangeMaxValue(10);
    accessibilityProperty->SetAccessibilityLevel("yes");
    jsAccessibilityManager->UpdateAccessibilityElementInfo(frameNode, nodeInfo);

    /**
    * @tc.steps: step2. init accessibilityProperty and set level yes.
    * @tc.expected: UpdateAccessibilityElementInfo nodeInfo level is yes.
    */
    EXPECT_EQ(nodeInfo.GetAccessibilityLevel(), "yes");
}

/**
 * @tc.name: JsAccessibilityManager002
 * @tc.desc: UpdateElementInfoTreeId
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTest, JsAccessibilityManager002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    Accessibility::AccessibilityElementInfo info;
    info.SetPageId(1);
    info.SetParent(0);
    info.SetBelongTreeId(10);
    info.SetAccessibilityId(11);
    jsAccessibilityManager->UpdateElementInfoTreeId(info);

    /**
    * @tc.steps: step2. init AccessibilityElementInfo and SetBelongTreeId 10, pageid 1, parent 0.
    * @tc.expected: UpdateElementInfoTreeId nodeInfo pageid is not equal 1.
    */
    EXPECT_NE(info.GetPageId(), 1);

    info.SetBelongTreeId(0);
    info.SetPageId(1);
    jsAccessibilityManager->UpdateElementInfoTreeId(info);

    /**
    * @tc.steps: step3. AccessibilityElementInfo and SetBelongTreeId 0
    * @tc.expected: UpdateElementInfoTreeId nodeInfo pageid is 1.
    */
    EXPECT_EQ(info.GetPageId(), 1);
}

/**
 * @tc.name: JsAccessibilityManager003
 * @tc.desc: UpdateAccessibilityVisible
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTest, JsAccessibilityManager003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), false);
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();

    /**
     * @tc.steps: step2. test UpdateAccessibilityVisible
     */
    Accessibility::AccessibilityElementInfo nodeInfo;
    // without parent node return visiable false
    jsAccessibilityManager->UpdateAccessibilityVisible(frameNode, nodeInfo);
    EXPECT_EQ(nodeInfo.GetAccessibilityVisible(), false);

    nodeInfo.SetParent(0);
    jsAccessibilityManager->UpdateAccessibilityVisible(frameNode, nodeInfo);
    EXPECT_EQ(nodeInfo.GetAccessibilityVisible(), false);
}

/**
 * @tc.name: JsAccessibilityManager004
 * @tc.desc: GenerateCommonProperty
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTest, JsAccessibilityManager004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::WINDOW_SCENE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    auto frameNode = FrameNode::CreateFrameNode("framenode", ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<Pattern>(), false);
    rootNode->AddChild(frameNode);
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    auto context = NG::PipelineContext::GetCurrentContext();
    jsAccessibilityManager->SetPipelineContext(context);
    jsAccessibilityManager->Register(true);
    jsAccessibilityManager->SetWindowId(1);

    /**
     * @tc.steps: step2. test GenerateCommonProperty
     */
    auto mainContext = context;
    Framework::CommonProperty commonProperty;
    jsAccessibilityManager->GenerateCommonProperty(context, commonProperty, mainContext, frameNode);
    EXPECT_EQ(commonProperty.innerWindowId, -1);

    jsAccessibilityManager->DumpTreeNodeCommonInfoNg(frameNode, commonProperty);
    jsAccessibilityManager->DumpTreeNodeSimplifyInfoNG(frameNode, 1, commonProperty, 1);
    jsAccessibilityManager->DumpTreeNG(frameNode, 1, frameNode->GetId(), true);
    jsAccessibilityManager->DumpTree(1, 1, true);

    jsAccessibilityManager->UpdateViewScale();
    EXPECT_EQ(jsAccessibilityManager->scaleX_, 1.0f);
}

/**
 * @tc.name: JsAccessibilityManager005
 * @tc.desc: dump func
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTest, JsAccessibilityManager005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<Pattern>(), false);
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    Accessibility::AccessibilityElementInfo nodeInfo;
    nodeInfo.SetAccessibilityId(1);
    jsAccessibilityManager->DumpAccessibilityPropertyNG(nodeInfo);
    jsAccessibilityManager->DumpCommonPropertyNG(nodeInfo, 1);

    /**
     * @tc.steps: step2. test DumpTreeNG
     */
    bool useWindowId = false;
    uint32_t windowId = 1;
    int64_t rootId = -1;
    bool isDumpSimplify = false;
    jsAccessibilityManager->DumpTreeNG(useWindowId, windowId, rootId, isDumpSimplify);

    rootId = 1;
    jsAccessibilityManager->SetWindowId(0);
    jsAccessibilityManager->DumpTreeNG(useWindowId, windowId, rootId, isDumpSimplify);

    jsAccessibilityManager->SetWindowId(1);
    jsAccessibilityManager->DumpTreeNG(useWindowId, windowId, rootId, isDumpSimplify);

    /**
     * @tc.steps: step3. test DumpHoverTestNG/DumpTreeNodeSafeAreaInfoNg
     */
    bool verbose = false;
    jsAccessibilityManager->DumpHoverTestNG(windowId, rootId, 100, 100, verbose);
    jsAccessibilityManager->DumpTreeNodeSafeAreaInfoNg(frameNode);
    EXPECT_EQ(nodeInfo.GetAccessibilityId(), 1);
}

/**
 * @tc.name: JsAccessibilityManager006
 * @tc.desc: UpdateVirtualNodeFocus
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTest, JsAccessibilityManager006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<Pattern>(), false);
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();

    /**
     * @tc.steps: step2. test UpdateVirtualNodeFocus
     */
    Accessibility::AccessibilityElementInfo nodeInfo;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    frameNode->SetGeometryNode(geometryNode);
    jsAccessibilityManager->SaveLast(0, frameNode);
    jsAccessibilityManager->UpdateVirtualNodeFocus();
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetAccessibilityFocusState(), false);
}

/**
 * @tc.name: JsAccessibilityManager007
 * @tc.desc: stateObserver
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTest, JsAccessibilityManager007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();

    /**
     * @tc.steps: step2. test SubscribeToastObserver
     */
    auto ret = jsAccessibilityManager->SubscribeToastObserver();
    EXPECT_EQ(ret, true);

    /**
     * @tc.steps: step3. test UnsubscribeToastObserver
     */
    ret = jsAccessibilityManager->UnsubscribeToastObserver();
    EXPECT_EQ(ret, true);

    /**
     * @tc.steps: step4. test SubscribeStateObserver
     */
    ret = jsAccessibilityManager->SubscribeStateObserver(16);
    EXPECT_EQ(ret, false);

    /**
     * @tc.steps: step5. test UnsubscribeStateObserver
     */
    ret = jsAccessibilityManager->UnsubscribeStateObserver(16);
    EXPECT_EQ(ret, false);
}

/**
 * @tc.name: JsAccessibilityManager008
 * @tc.desc: SendAccessibilitySyncEvent, TransferAccessibilityAsyncEvent
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTest, JsAccessibilityManager008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    auto context = NG::PipelineContext::GetCurrentContext();
    jsAccessibilityManager->SetPipelineContext(context);
    jsAccessibilityManager->Register(true);
    auto client = Accessibility::AccessibilitySystemAbilityClient::GetInstance();

    /**
     * @tc.steps: step2. test SendAccessibilitySyncEvent with register true
     */
    AccessibilityEvent accessibilityEvent;
    Accessibility::AccessibilityEventInfo eventInfo;
    auto ret = jsAccessibilityManager->SendAccessibilitySyncEvent(accessibilityEvent, eventInfo);
    if (client) {
        bool isEnabled = false;
        client->IsEnabled(isEnabled);
        EXPECT_EQ(ret, isEnabled);
    } else {
        EXPECT_EQ(ret, false);
    }

    /**
     * @tc.steps: step3. test TransferAccessibilityAsyncEvent with register true
     */
    int64_t uiExtensionOffset = 1000;
    ret = jsAccessibilityManager->TransferAccessibilityAsyncEvent(eventInfo, uiExtensionOffset);
    if (client) {
        bool isEnabled = false;
        client->IsEnabled(isEnabled);
        EXPECT_EQ(ret, isEnabled);
    } else {
        EXPECT_EQ(ret, false);
    }

    /**
     * @tc.steps: step4. test SendAccessibilitySyncEvent with register false
     */
    jsAccessibilityManager->Register(false);
    ret = jsAccessibilityManager->SendAccessibilitySyncEvent(accessibilityEvent, eventInfo);
    EXPECT_EQ(ret, false);
    /**
     * @tc.steps: step5. test TransferAccessibilityAsyncEvent with register false
     */
    ret = jsAccessibilityManager->TransferAccessibilityAsyncEvent(eventInfo, uiExtensionOffset);
    EXPECT_EQ(ret, false);
}

/**
 * @tc.name: JsAccessibilityManager009
 * @tc.desc: GetDelayTimeBeforeSendEvent
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTest, JsAccessibilityManager009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<Pattern>(), false);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
    accessibilityProperty->SetAccessibilityLevel("yes");
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    auto context = NG::PipelineContext::GetCurrentContext();
    jsAccessibilityManager->SetPipelineContext(context);
    jsAccessibilityManager->Register(true);

    /**
     * @tc.steps: step2. test GetPipelineByWindowId
     */
    AccessibilityEvent event;
    int64_t ret;
    ret = jsAccessibilityManager->GetDelayTimeBeforeSendEvent(event, frameNode);
    EXPECT_EQ(ret, 0);
    // test GetDelayTimeBeforeSendEvent with node selected, event type click, return 0
    event.type = AccessibilityEventType::CLICK;
    accessibilityProperty->SetUserSelected(true);
    ret = jsAccessibilityManager->GetDelayTimeBeforeSendEvent(event, frameNode);
    EXPECT_EQ(ret, 20);
    // test GetDelayTimeBeforeSendEvent with node not selected, return 0
    accessibilityProperty->SetUserSelected(false);
    ret = jsAccessibilityManager->GetDelayTimeBeforeSendEvent(event, frameNode);
    EXPECT_EQ(ret, 20);

    ret = jsAccessibilityManager->GetDelayTimeBeforeSendEvent(event, nullptr);
    EXPECT_EQ(ret, 0);
}

/**
 * @tc.name: JsAccessibilityManager010
 * @tc.desc: GetPipelineByWindowId
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTest, JsAccessibilityManager010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    auto context = NG::PipelineContext::GetCurrentContext();
    jsAccessibilityManager->SetPipelineContext(context);
    jsAccessibilityManager->Register(true);
    jsAccessibilityManager->SetWindowId(1);

    /**
     * @tc.steps: step2. test GetPipelineByWindowId
     */
    auto pattern = jsAccessibilityManager->GetPipelineByWindowId(1);
    EXPECT_NE(pattern, nullptr);

    pattern = jsAccessibilityManager->GetPipelineByWindowId(2);
    EXPECT_EQ(pattern, nullptr);
}

/**
 * @tc.name: JsAccessibilityManager011
 * @tc.desc: CheckDumpInfoParams,OnDumpInfoNG,CheckDumpHandleEventParams,DumpProperty
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTest, JsAccessibilityManager011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    std::vector<std::string> params = {};
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();

    /**
     * @tc.steps: step2. test CheckDumpInfoParams
     */
    auto ret = jsAccessibilityManager->CheckDumpInfoParams(params);
    EXPECT_EQ(ret, false);

    params = { "-inspector", "-accessibility", "-simplify"};
    ret = jsAccessibilityManager->CheckDumpInfoParams(params);
    EXPECT_EQ(ret, true);

    params = { "-inspector", "-accessibility"};
    ret = jsAccessibilityManager->CheckDumpInfoParams(params);
    EXPECT_EQ(ret, true);

    /**
     * @tc.steps: step3. test OnDumpInfoNG
     */
    params = { "-inspector", "-accessibility", "-simplify", "-w", "1"};
    jsAccessibilityManager->OnDumpInfoNG(params, 1, false);

    /**
     * @tc.steps: step4. test CheckDumpHandleEventParams
     */
    ret = jsAccessibilityManager->CheckDumpHandleEventParams(params);
    EXPECT_EQ(ret, true);

    /**
     * @tc.steps: step5. test DumpProperty
     */
    jsAccessibilityManager->DumpProperty(params);
}

/**
 * @tc.name: JsAccessibilityManager012
 * @tc.desc: Test UIExtensionManager ConvertActionTypeToBoolen
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTest, JsAccessibilityManager012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto context = NG::PipelineContext::GetCurrentContext();
    int64_t elementId = 0;

    /**
     * @tc.steps: step2. test ConvertActionTypeToBoolen
     */
    auto ret = jsAccessibilityManager->ConvertActionTypeToBoolen(ActionType::ACCESSIBILITY_ACTION_FOCUS,
        frameNode, elementId, context);
    EXPECT_EQ(ret, false);

    ret = jsAccessibilityManager->ConvertActionTypeToBoolen(ActionType::ACCESSIBILITY_ACTION_CLEAR_FOCUS,
        frameNode, elementId, context);
    EXPECT_EQ(ret, false);

    ret = jsAccessibilityManager->ConvertActionTypeToBoolen(ActionType::ACCESSIBILITY_ACTION_CLICK,
        frameNode, elementId, context);
    EXPECT_EQ(ret, false);

    ret = jsAccessibilityManager->ConvertActionTypeToBoolen(ActionType::ACCESSIBILITY_ACTION_LONG_CLICK,
        frameNode, elementId, context);
    EXPECT_EQ(ret, false);

    ret = jsAccessibilityManager->ConvertActionTypeToBoolen(ActionType::ACCESSIBILITY_ACTION_ACCESSIBILITY_FOCUS,
        frameNode, elementId, context);
    EXPECT_EQ(ret, true);

    ret = jsAccessibilityManager->ConvertActionTypeToBoolen(ActionType::ACCESSIBILITY_ACTION_CLEAR_ACCESSIBILITY_FOCUS,
        frameNode, elementId, context);
    EXPECT_EQ(ret, false);
}

/**
 * @tc.name: JsAccessibilityManager013
 * @tc.desc: Test UIExtensionManager SendEventToAccessibilityWithNode/SendEventToAccessibilityWithNodeInner
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTest, JsAccessibilityManager013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::WINDOW_SCENE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    auto frameNode = FrameNode::CreateFrameNode("framenode", ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<Pattern>(), false);
    rootNode->AddChild(frameNode);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
    accessibilityProperty->SetAccessibilityLevel("yes");
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();

    /**
     * @tc.steps: step2. test SendEventToAccessibilityWithNode
     */
    AccessibilityEvent accessibilityEvent;
    auto context = NG::PipelineContext::GetCurrentContext();
    EXPECT_EQ(jsAccessibilityManager->context_.Upgrade(), nullptr);
    jsAccessibilityManager->SetPipelineContext(context);
    EXPECT_NE(jsAccessibilityManager->context_.Upgrade(), nullptr);
    jsAccessibilityManager->SendEventToAccessibilityWithNode(accessibilityEvent, frameNode, context);

    /**
     * @tc.steps: step2. test SendEventToAccessibilityWithNodeInner
     */
    jsAccessibilityManager->SendEventToAccessibilityWithNodeInner(accessibilityEvent, frameNode, context);
}

/**
 * @tc.name: JsAccessibilityManager014
 * @tc.desc: Test UIExtensionManager RegisterSubWindowInteractionOperation/CanAccessibilityFocused
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTest, JsAccessibilityManager014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::WINDOW_SCENE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    auto frameNode = FrameNode::CreateFrameNode("framenode", ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<Pattern>(), false);
    rootNode->AddChild(frameNode);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
    accessibilityProperty->SetAccessibilityLevel("yes");
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();

    /**
     * @tc.steps: step2. test RegisterSubWindowInteractionOperation
     */
    jsAccessibilityManager->RegisterSubWindowInteractionOperation(0);

    /**
     * @tc.steps: step3. test CanAccessibilityFocused
     */
    auto node = jsAccessibilityManager->GetAccessibilityNodeFromPage(0);
    EXPECT_FALSE(jsAccessibilityManager->CanAccessibilityFocused(node));
}

/**
 * @tc.name: JsAccessibilityManager015
 * @tc.desc: Test UIExtensionManager NeedRegisterChildTree
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTest, JsAccessibilityManager015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();

    /**
     * @tc.steps: step2. test NeedRegisterChildTree
     */
    uint32_t parentWindowId = 0;
    int32_t parentTreeId = 0;
    int64_t parentElementId = 0;
    jsAccessibilityManager->parentWindowId_ = parentWindowId;
    jsAccessibilityManager->parentTreeId_ = parentTreeId;
    jsAccessibilityManager->parentElementId_ = parentElementId;
    EXPECT_TRUE(jsAccessibilityManager->NeedRegisterChildTree(parentWindowId, parentTreeId, parentElementId));

    jsAccessibilityManager->Register(true);
    EXPECT_FALSE(jsAccessibilityManager->NeedRegisterChildTree(parentWindowId, parentTreeId, parentElementId));

    jsAccessibilityManager->parentWindowId_ = 1;
    EXPECT_TRUE(jsAccessibilityManager->NeedRegisterChildTree(parentWindowId, parentTreeId, parentElementId));
    jsAccessibilityManager->parentTreeId_ = 1;
    EXPECT_TRUE(jsAccessibilityManager->NeedRegisterChildTree(parentWindowId, parentTreeId, parentElementId));
    jsAccessibilityManager->parentElementId_ = 1;
    EXPECT_TRUE(jsAccessibilityManager->NeedRegisterChildTree(parentWindowId, parentTreeId, parentElementId));
}

/**
 * @tc.name: JsAccessibilityManager016
 * @tc.desc: Test UIExtensionManager OnDumpChildInfoForThird/CheckIsChildElement
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTest, JsAccessibilityManager016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    std::vector<std::string> params = {};
    std::vector<std::string> info = {};

    /**
     * @tc.steps: step2. test CheckIsChildElement
     */
    int64_t elementId = 0;
    int64_t rootId = 0;
    EXPECT_FALSE(
        jsAccessibilityManager->CheckIsChildElement(elementId, params, info, Framework::DumpMode::TREE, rootId));
    EXPECT_FALSE(
        jsAccessibilityManager->CheckIsChildElement(elementId, params, info, Framework::DumpMode::NODE, rootId));
}

/**
 * @tc.name: JsAccessibilityManager017
 * @tc.desc: Test UIExtensionManager RegisterInteractionOperation
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTest, JsAccessibilityManager017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::WINDOW_SCENE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    auto frameNode = FrameNode::CreateFrameNode("framenode", ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<Pattern>(), false);
    rootNode->AddChild(frameNode);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
    accessibilityProperty->SetAccessibilityLevel("yes");
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    std::vector<std::string> params = {};
    std::vector<std::string> info = {};

    /**
     * @tc.steps: step2. test RegisterInteractionOperation
     */
    auto ret = jsAccessibilityManager->RegisterInteractionOperation(0);
    EXPECT_EQ(ret, false);
}

/**
 * @tc.name: JsAccessibilityManager018
 * @tc.desc: Test UIExtensionManager RegisterAccessibilityChildTreeCallback/DeregisterAccessibilityChildTreeCallback
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTest, JsAccessibilityManager018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    EXPECT_EQ(0, jsAccessibilityManager->childTreeCallbackMap_.size());

    /**
     * @tc.steps: step2. test RegisterAccessibilityChildTreeCallback
     */
    int64_t elementId0 = 0;
    auto callback0 = std::make_shared<MockAccessibilityChildTreeCallback>(0);
    jsAccessibilityManager->RegisterAccessibilityChildTreeCallback(elementId0, callback0);
    EXPECT_EQ(1, jsAccessibilityManager->childTreeCallbackMap_.size());
    EXPECT_EQ(callback0, jsAccessibilityManager->childTreeCallbackMap_[elementId0]);
    int64_t elementId1 = 1;
    auto callback1 = std::make_shared<MockAccessibilityChildTreeCallback>(1);
    jsAccessibilityManager->RegisterAccessibilityChildTreeCallback(elementId1, callback1);
    EXPECT_EQ(2, jsAccessibilityManager->childTreeCallbackMap_.size());
    EXPECT_EQ(callback1, jsAccessibilityManager->childTreeCallbackMap_[elementId1]);

    /**
     * @tc.steps: step3. test DeregisterAccessibilityChildTreeCallback
     */
    jsAccessibilityManager->DeregisterAccessibilityChildTreeCallback(elementId1);
    EXPECT_EQ(1, jsAccessibilityManager->childTreeCallbackMap_.size());
    EXPECT_EQ(callback0, jsAccessibilityManager->childTreeCallbackMap_[elementId0]);
    jsAccessibilityManager->DeregisterAccessibilityChildTreeCallback(elementId0);
    EXPECT_EQ(0, jsAccessibilityManager->childTreeCallbackMap_.size());
}

/**
 * @tc.name: JsAccessibilityManager019
 * @tc.desc: Test UIExtensionManager RegisterAccessibilitySAObserverCallback/DeregisterAccessibilitySAObserverCallback
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTest, JsAccessibilityManager019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    EXPECT_EQ(0, jsAccessibilityManager->componentSACallbackMap_.size());

    /**
     * @tc.steps: step2. test RegisterAccessibilitySAObserverCallback
     */
    int64_t elementId0 = 0;
    auto callback0 = std::make_shared<MockAccessibilitySAObserverCallback>(0);
    jsAccessibilityManager->RegisterAccessibilitySAObserverCallback(elementId0, callback0);
    EXPECT_EQ(1, jsAccessibilityManager->componentSACallbackMap_.size());
    EXPECT_EQ(callback0, jsAccessibilityManager->componentSACallbackMap_[elementId0]);
    int64_t elementId1 = 1;
    auto callback1 = std::make_shared<MockAccessibilitySAObserverCallback>(1);
    jsAccessibilityManager->RegisterAccessibilitySAObserverCallback(elementId1, callback1);
    EXPECT_EQ(2, jsAccessibilityManager->componentSACallbackMap_.size());
    EXPECT_EQ(callback1, jsAccessibilityManager->componentSACallbackMap_[elementId1]);

    /**
     * @tc.steps: step3. test DeregisterAccessibilitySAObserverCallback
     */
    jsAccessibilityManager->DeregisterAccessibilitySAObserverCallback(elementId1);
    EXPECT_EQ(1, jsAccessibilityManager->componentSACallbackMap_.size());
    EXPECT_EQ(callback0, jsAccessibilityManager->componentSACallbackMap_[elementId0]);
    jsAccessibilityManager->DeregisterAccessibilitySAObserverCallback(elementId0);
    EXPECT_EQ(0, jsAccessibilityManager->componentSACallbackMap_.size());
}
/**
 * @tc.name: UpdateWindowInfo001
 * @tc.desc: UpdateWindowInfo
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTest, UpdateWindowInfo001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct jsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);
    auto pipelineContext = MockContainer::Current()->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    jsAccessibilityManager->context_ = pipelineContext;

    /**
     * @tc.steps: step2. construct windowInfo
     */
    AccessibilityWindowInfo windowInfo;
    windowInfo.left = 10;
    windowInfo.top = 10;
    windowInfo.scaleX = 1.0f;
    windowInfo.scaleY = 1.0f;

    /**
     * @tc.steps: step3. call and test UpdateWindowInfo method
     */
    jsAccessibilityManager->UpdateWindowInfo(windowInfo, pipelineContext);
    EXPECT_EQ(windowInfo.left, 10);
    EXPECT_EQ(windowInfo.top, 10);
    EXPECT_EQ(windowInfo.scaleX, 1.0f);
    EXPECT_EQ(windowInfo.scaleY, 1.0f);

    auto container = Platform::AceContainer::GetContainer(pipelineContext->GetInstanceId());
    ASSERT_NE(container, nullptr);
    container->SetSingleHandTransform(Platform::SingleHandTransform(100.0f, 200.0f, 0.7f, 0.6f));

    jsAccessibilityManager->UpdateWindowInfo(windowInfo, pipelineContext);
    EXPECT_EQ(windowInfo.left, 107.0f);
    EXPECT_EQ(windowInfo.top, 206.0f);
    EXPECT_EQ(windowInfo.scaleX, 0.7f);
    EXPECT_EQ(windowInfo.scaleY, 0.6f);
}

/**
 * @tc.name: GenerateWindowInfo001
 * @tc.desc: GenerateWindowInfo
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTest, GenerateWindowInfo001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct jsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step3. call and test GenerateWindowInfo method
     */
    auto windowInfo = jsAccessibilityManager->GenerateWindowInfo(nullptr, nullptr);
    EXPECT_EQ(windowInfo.left, 0);
    EXPECT_EQ(windowInfo.top, 0);
    EXPECT_EQ(windowInfo.scaleX, 1.0f);
    EXPECT_EQ(windowInfo.scaleY, 1.0f);

    auto frameNode = FrameNode::CreateFrameNode("framenode", ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<Pattern>(), false);
    windowInfo = jsAccessibilityManager->GenerateWindowInfo(frameNode, nullptr);

    auto pipelineContext = MockContainer::Current()->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    jsAccessibilityManager->context_ = pipelineContext;
    auto container = Platform::AceContainer::GetContainer(pipelineContext->GetInstanceId());
    ASSERT_NE(container, nullptr);
    auto singleHandTransform = container->GetSingleHandTransform();
    container->SetSingleHandTransform(Platform::SingleHandTransform(0.0f, 0.0f, 1.0f, 1.0f));

    auto context = NG::PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    jsAccessibilityManager->getParentRectHandler_ = nullptr;
    jsAccessibilityManager->getParentRectHandlerNew_ = nullptr;
    windowInfo = jsAccessibilityManager->GenerateWindowInfo(nullptr, context);

    EXPECT_EQ(windowInfo.left, 0);
    EXPECT_EQ(windowInfo.top, 0);
    EXPECT_EQ(windowInfo.scaleX, 1.0f);
    EXPECT_EQ(windowInfo.scaleY, 1.0f);

    /**
     * @tc.steps: step4. mock SingleHandTransform, and then test GenerateWindowInfo method again
     */
    container->SetSingleHandTransform(Platform::SingleHandTransform(100.0f, 200.0f, 0.7f, 0.7f));

    jsAccessibilityManager->UpdateWindowInfo(windowInfo, pipelineContext);
    EXPECT_EQ(windowInfo.left, 100.0f);
    EXPECT_EQ(windowInfo.top, 200.0f);
    EXPECT_EQ(windowInfo.scaleX, 0.7f);
    EXPECT_EQ(windowInfo.scaleY, 0.7f);
}

/**
 * @tc.name: SingleHandTransformTest001
 * @tc.desc: SetSingleHandTransform & GetSingleHandTransform
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTest, SingleHandTransformTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct AceContainer
     */
    auto pipelineContext = MockContainer::Current()->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto container = Platform::AceContainer::GetContainer(pipelineContext->GetInstanceId());
    ASSERT_NE(container, nullptr);

    /**
     * @tc.steps: step2. test SetSingleHandTransform & GetSingleHandTransform
     */
    container->SetSingleHandTransform(Platform::SingleHandTransform(100.0f, 200.0f, 0.7f, 0.6f));
    auto singleHandTransform = container->GetSingleHandTransform();
    EXPECT_EQ(singleHandTransform.x_, 100.0f);
    EXPECT_EQ(singleHandTransform.y_, 200.0f);
    EXPECT_EQ(singleHandTransform.scaleX_, 0.7f);
    EXPECT_EQ(singleHandTransform.scaleY_, 0.6f);
}

/**
 * @tc.name: JsAccessibilityManager020
 * @tc.desc: dump event test  DumpProcessEventParameters
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTest, JsAccessibilityManager020, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    auto context = NG::PipelineContext::GetCurrentContext();
    jsAccessibilityManager->SetPipelineContext(context);
    jsAccessibilityManager->Register(true);
    bool ret;
    AccessibilityEvent accessibilityEvent;
    accessibilityEvent.nodeId = 1;
    accessibilityEvent.windowChangeTypes = WindowUpdateType::WINDOW_UPDATE_ACTIVE;
    accessibilityEvent.type = AccessibilityEventType::PAGE_CHANGE;
    // 1. parameter stackNodeId
    std::vector<std::string> params;
    params.push_back("-inspector");
    params.push_back("1");

    params.push_back("--stackNodeId");

    ret = jsAccessibilityManager->DumpProcessEventParameters(accessibilityEvent, params);
    EXPECT_EQ(ret, false);

    int64_t testStackId = 2;
    params.push_back(std::to_string(testStackId));
    ret = jsAccessibilityManager->DumpProcessEventParameters(accessibilityEvent, params);
    EXPECT_EQ(ret, true);
    EXPECT_EQ(accessibilityEvent.stackNodeId, testStackId);

    // 2. parameter beforeText
    params.push_back("--beforeText");
    ret = jsAccessibilityManager->DumpProcessEventParameters(accessibilityEvent, params);
    EXPECT_EQ(ret, false);

    std::string beforeText = "teststr1";
    params.push_back(beforeText);
    ret = jsAccessibilityManager->DumpProcessEventParameters(accessibilityEvent, params);
    EXPECT_EQ(ret, true);
    EXPECT_EQ(accessibilityEvent.beforeText, beforeText);
}

/**
 * @tc.name: JsAccessibilityManager020
 * @tc.desc: dump event test  DumpProcessEventParameters
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTest, JsAccessibilityManager0201, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    auto context = NG::PipelineContext::GetCurrentContext();
    jsAccessibilityManager->SetPipelineContext(context);
    jsAccessibilityManager->Register(true);
    bool ret;
    AccessibilityEvent accessibilityEvent;
    accessibilityEvent.nodeId = 1;
    accessibilityEvent.windowChangeTypes = WindowUpdateType::WINDOW_UPDATE_ACTIVE;
    accessibilityEvent.type = AccessibilityEventType::PAGE_CHANGE;
    std::vector<std::string> params;
    params.push_back("-inspector");
    params.push_back("1");

    // 3. parameter latestContent
    params.push_back("--latestContent");
    ret = jsAccessibilityManager->DumpProcessEventParameters(accessibilityEvent, params);
    EXPECT_EQ(ret, false);

    std::string latestContent = "teststr2";
    params.push_back(latestContent);
    ret = jsAccessibilityManager->DumpProcessEventParameters(accessibilityEvent, params);
    EXPECT_EQ(ret, true);
    EXPECT_EQ(accessibilityEvent.latestContent, latestContent);

    // 4. parameter latestContent
    params.push_back("--textAnnounced");
    ret = jsAccessibilityManager->DumpProcessEventParameters(accessibilityEvent, params);
    EXPECT_EQ(ret, false);

    std::string textAnnounced = "teststr3";
    params.push_back(textAnnounced);
    ret = jsAccessibilityManager->DumpProcessEventParameters(accessibilityEvent, params);
    EXPECT_EQ(ret, true);
    EXPECT_EQ(accessibilityEvent.textAnnouncedForAccessibility, textAnnounced);
}

/**
 * @tc.name: JsAccessibilityManager021
 * @tc.desc: dump event test  DumpProcessEventParameters
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTest, JsAccessibilityManager021, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto context = NG::PipelineContext::GetCurrentContext();

    MockJsAccessibilityManager mockJsManger;
    mockJsManger.SetPipelineContext(context);
    mockJsManger.Register(true);

    int64_t nodeId = 1;
    int32_t eventId = 2;
    // 1. check parameter fail
    std::vector<std::string> params;
    params.push_back("-inspector");
    params.push_back("1");
    params.push_back("--stackNodeId");
    EXPECT_CALL(mockJsManger, SendEventToAccessibilityWithNode(_, _, _))
        .Times(0);

    mockJsManger.DumpSendEventTest(nodeId, eventId, params);

    // 2. check parameter success
    int64_t testStackId = 2;
    params.push_back(std::to_string(testStackId));

    EXPECT_CALL(mockJsManger, SendEventToAccessibilityWithNode(_, _, _))
        .Times(1);

    mockJsManger.DumpSendEventTest(nodeId, eventId, params);
}

/**
 * @tc.name: JsAccessibilityManager022
 * @tc.desc: dump event test  OnDumpInfoNG
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTest, JsAccessibilityManager022, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto context = NG::PipelineContext::GetCurrentContext();
    MockJsAccessibilityManager mockJsManger;
    mockJsManger.SetPipelineContext(context);
    mockJsManger.Register(true);

    std::vector<std::string> params;

    // 1.  dump event
    params.push_back("-inspector");
    params.push_back("--event-test");
    params.push_back("1");
    params.push_back("2");

    EXPECT_CALL(mockJsManger, SendEventToAccessibilityWithNode(_, _, _))
        .Times(1);
    mockJsManger.OnDumpInfoNG(params, 1, false);
}

/**
 * @tc.name: JsAccessibilityManager023
 * @tc.desc: UpdateAccessibilityElementInfo ScrollTriggerable
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTest, JsAccessibilityManager023, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     * @tc.desc: Create a FrameNode object and initialize the JsAccessibilityManager object.
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    CHECK_NULL_VOID(frameNode);
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    Accessibility::AccessibilityElementInfo nodeInfo;

    // Update information in nodeInfo and verify that its default scrollable is true
    jsAccessibilityManager->UpdateAccessibilityElementInfo(frameNode, nodeInfo);
    CHECK_NULL_VOID(jsAccessibilityManager);
    EXPECT_EQ(nodeInfo.GetAccessibilityScrollable(), true);

    /**
    * @tc.steps: step2. Initialize accessibilityProperty and set ScrollTriggerable to false.
    * @tc.expected: The updated nodeInfo's ScrollTriggerable property should be false.
    */
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    accessibilityProperty->SetUserScrollTriggerable(false);
    jsAccessibilityManager->UpdateAccessibilityElementInfo(frameNode, nodeInfo);
    EXPECT_EQ(nodeInfo.GetAccessibilityScrollable(), false);

    /**
    * @tc.steps: step3. Reset the ScrollTriggerable property of accessibilityProperty.
    * @tc.expected: The updated nodeInfo's ScrollTriggerable property should be true.
    */
    accessibilityProperty->ResetUserScrollTriggerable();
    jsAccessibilityManager->UpdateAccessibilityElementInfo(frameNode, nodeInfo);
    EXPECT_EQ(nodeInfo.GetAccessibilityScrollable(), true);
}

class MockRenderContextTest : public RenderContext {
public:
    RectF GetPaintRectWithoutTransform() override
    {
        return *retf;
    }
    std::shared_ptr<RectF> retf;
};

/**
 * @tc.name: FrameNodeAccessibilityVisible02
 * @tc.desc: Test the function accessibilityVisible
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTest, FrameNodeAccessibilityVisible02, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create parent frameNode and set up its rect.
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    CHECK_NULL_VOID(frameNode);
    EXPECT_NE(frameNode->pattern_, nullptr);
    frameNode->isActive_ = true;
    auto pipeline = frameNode->GetContext();

    auto parentRender = AceType::MakeRefPtr<MockRenderContextTest>();
    CHECK_NULL_VOID(parentRender);
    auto parentRec = std::make_shared<RectF>(10.0, 10.0, 10.0, 5.0);
    parentRender->retf = parentRec;
    frameNode->renderContext_ = parentRender;

    /**
     * @tc.steps: step2. create child frameNode and set up its rect.
     */
    auto childNode = FrameNode::CreateFrameNode(
    "child", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    childNode->isActive_ = true;
    auto childRender = AceType::MakeRefPtr<MockRenderContextTest>();
    CHECK_NULL_VOID(childRender);
    auto childRec = std::make_shared<RectF>(10.0, 10.0, 10.0, 10.0);
    childRender->retf = childRec;
    childNode->renderContext_ = childRender;

    /**
     * @tc.steps: step3. add parent and child node to the pipeline context.
     */
    auto context = NG::PipelineContext::GetCurrentContext();
    context->GetRootElement()->AddChild(frameNode);
    frameNode->AddChild(childNode);

    /**
     * @tc.steps: step4. verify the child node's accessibilityVisible is true.
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    CHECK_NULL_VOID(jsAccessibilityManager);
    jsAccessibilityManager->SetPipelineContext(context);
    jsAccessibilityManager->Register(true);
    RefPtr<NG::PipelineContext> ngPipeline;
    ngPipeline = AceType::DynamicCast<NG::PipelineContext>(pipeline);
    std::list<AccessibilityElementInfo> extensionElementInfos;
    jsAccessibilityManager->SearchElementInfoByAccessibilityIdNG(
        childNode->GetAccessibilityId(), 1, extensionElementInfos, ngPipeline, 1);
    for (auto& extensionElementInfo : extensionElementInfos) {
        if (childNode->GetAccessibilityId() == extensionElementInfo.GetAccessibilityId()) {
            EXPECT_TRUE(extensionElementInfo.GetAccessibilityVisible());
        }
    }
}

/**
 * @tc.name: JsAccessibilityManager024
 * @tc.desc: RegisterGetParentRectHandler
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTest, JsAccessibilityManager024, TestSize.Level1)
{
    /**
    * @tc.steps: step1. construct JsAccessibilityManager
    */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);
    /**
    * @tc.steps: step2. test RegisterGetParentRectHandler
    */
    jsAccessibilityManager->uecRectInfo_.isChanged = false;
    jsAccessibilityManager->RegisterGetParentRectHandler();
    EXPECT_NE(jsAccessibilityManager->getParentRectHandlerNew_, nullptr);
}

/**
* @tc.name: JsAccessibilityManager025
* @tc.desc: GetFinalRealRectInfo
* @tc.type: FUNC
*/
HWTEST_F(JsAccessibilityManagerTest, JsAccessibilityManager025, TestSize.Level1)
{
    /**
    * @tc.steps: step1. construct JsAccessibilityManager
    */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(
        "frameNode", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. test GetFinalRealRectInfo
     */
    auto rectInfo = jsAccessibilityManager->GetFinalRealRectInfo(frameNode);
    EXPECT_EQ(rectInfo.Left(), 0);
    EXPECT_EQ(rectInfo.Top(), 0);
}
} // namespace OHOS::Ace::NG