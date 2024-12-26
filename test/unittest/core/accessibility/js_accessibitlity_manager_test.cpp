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

#include "gtest/gtest.h"

#define private public
#define protected public

#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/log/dump_log.h"
#include "adapter/ohos/osal/js_accessibility_manager.h"
#include "frameworks/core/accessibility/accessibility_node.h"
using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
namespace {
} // namespace


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

/**
 * @tc.name: JsAccessibilityManager001
 * @tc.desc: UpdateAccessibilityElementInfo
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTest, JsAccessibilityManager001, TestSize.Level1)
{
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
    * @tc.steps: step0. init accessibilityProperty and set level yes.
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
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    Accessibility::AccessibilityElementInfo info;
    info.SetPageId(1);
    info.SetParent(0);
    info.SetBelongTreeId(10);
    info.SetAccessibilityId(11);
    jsAccessibilityManager->UpdateElementInfoTreeId(info);
    /**
    * @tc.steps: step0. init AccessibilityElementInfo and SetBelongTreeId 10, pageid 1, parent 0.
    * @tc.expected: UpdateElementInfoTreeId nodeInfo pageid is not equal 1.
    */
    EXPECT_NE(info.GetPageId(), 1);

    info.SetBelongTreeId(0);
    info.SetPageId(1);
    jsAccessibilityManager->UpdateElementInfoTreeId(info);
    /**
    * @tc.steps: step1. AccessibilityElementInfo and SetBelongTreeId 0
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
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), false);
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
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
 * @tc.desc: GenerateCommonProperty,UpdateVirtualNodeChildAccessibilityElementInfo
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTest, JsAccessibilityManager004, TestSize.Level1)
{
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
    auto frameNode = FrameNode::CreateFrameNode("framenode", ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<Pattern>(), false);
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    Accessibility::AccessibilityElementInfo nodeInfo;
    nodeInfo.SetAccessibilityId(1);
    jsAccessibilityManager->DumpAccessibilityPropertyNG(nodeInfo);
    jsAccessibilityManager->DumpCommonPropertyNG(nodeInfo, 1);

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
    auto frameNode = FrameNode::CreateFrameNode("framenode", ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<Pattern>(), false);
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
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
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    auto ret = jsAccessibilityManager->SubscribeToastObserver();
    EXPECT_EQ(ret, true);

    ret = jsAccessibilityManager->UnsubscribeToastObserver();
    EXPECT_EQ(ret, true);

    ret = jsAccessibilityManager->SubscribeStateObserver(16);
    EXPECT_EQ(ret, false);

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
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    auto context = NG::PipelineContext::GetCurrentContext();
    jsAccessibilityManager->SetPipelineContext(context);
    jsAccessibilityManager->Register(true);
    AccessibilityEvent accessibilityEvent;
    Accessibility::AccessibilityEventInfo eventInfo;
    auto ret = jsAccessibilityManager->SendAccessibilitySyncEvent(accessibilityEvent, eventInfo);
    EXPECT_EQ(ret, false);

    int64_t uiExtensionOffset = 1000;
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
    auto frameNode = FrameNode::CreateFrameNode("framenode", ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<Pattern>(), false);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
    accessibilityProperty->SetAccessibilityLevel("yes");
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    auto context = NG::PipelineContext::GetCurrentContext();
    jsAccessibilityManager->SetPipelineContext(context);
    jsAccessibilityManager->Register(true);
    
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
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    auto context = NG::PipelineContext::GetCurrentContext();
    jsAccessibilityManager->SetPipelineContext(context);
    jsAccessibilityManager->Register(true);
    jsAccessibilityManager->SetWindowId(1);
    auto pattern = jsAccessibilityManager->GetPipelineByWindowId(1);
    EXPECT_NE(pattern, nullptr);

    pattern = jsAccessibilityManager->GetPipelineByWindowId(2);
    EXPECT_EQ(pattern, nullptr);
}

/**
 * @tc.name: JsAccessibilityManager011
 * @tc.desc: CheckDumpInfoParams,OnDumpInfoNG,DumpProperty
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTest, JsAccessibilityManager011, TestSize.Level1)
{
    std::vector<std::string> params = {};
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    auto ret = jsAccessibilityManager->CheckDumpInfoParams(params);
    EXPECT_EQ(ret, false);

    params = { "-inspector", "-accessibility", "-simplify"};
    ret = jsAccessibilityManager->CheckDumpInfoParams(params);
    EXPECT_EQ(ret, true);

    params = { "-inspector", "-accessibility"};
    ret = jsAccessibilityManager->CheckDumpInfoParams(params);
    EXPECT_EQ(ret, true);

    params = { "-inspector", "-accessibility", "-simplify", "-w", "1"};
    jsAccessibilityManager->OnDumpInfoNG(params, 1, false);

    ret = jsAccessibilityManager->CheckDumpHandleEventParams(params);
    EXPECT_EQ(ret, true);

    jsAccessibilityManager->DumpProperty(params);
}

} // namespace OHOS::Ace::NG