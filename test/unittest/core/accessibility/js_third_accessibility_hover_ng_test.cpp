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

#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/common/mock_frontend.h"
#include "test/mock/frameworks/core/components_ng/render/mock_render_context.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "accessibility_system_ability_client.h"
#include "frameworks/core/accessibility/accessibility_manager.h"
#include "adapter/ohos/osal/js_third_provider_interaction_operation.h"

#include "base/log/dump_log.h"
#include "frameworks/core/accessibility/accessibility_node.h"
#include "frameworks/core/accessibility/accessibility_utils.h"
#include "frameworks/core/components_ng/property/accessibility_property.h"
#include "frameworks/core/accessibility/native_interface_accessibility_provider.h"
#include "frameworks/core/components_ng/pattern/ui_extension/ui_extension_manager.h"
#include "js_third_provider_interaction_operation_test.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
namespace {
    const int32_t IGNORE_POSITION_TRANSITION_SWITCH = -990;
} // namespace

class JsThirdAccessibilityHoverNgTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void JsThirdAccessibilityHoverNgTest::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;
    auto context = NG::PipelineContext::GetCurrentContext();
    context->instanceId_ = IGNORE_POSITION_TRANSITION_SWITCH;
    std::unique_ptr<std::ostream> ostream = std::make_unique<std::ostringstream>();
    ASSERT_NE(ostream, nullptr);
    DumpLog::GetInstance().SetDumpFile(std::move(ostream));
}

void JsThirdAccessibilityHoverNgTest::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: JsThirdAccessibilityHoverNgTest001
 * @tc.desc: ClearFocusFromProvider
 * @tc.type: FUNC
 */
HWTEST_F(JsThirdAccessibilityHoverNgTest, JsThirdAccessibilityHoverNgTest001, TestSize.Level1)
{
    auto ohAccessibilityProvider
        = AceType::MakeRefPtr<MockOhAccessibilityProvider>();
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    auto context = NG::PipelineContext::GetCurrentContext();
    jsAccessibilityManager->SetPipelineContext(context);
    jsAccessibilityManager->Register(true);

    auto jsInteractionOperation = std::make_shared<Framework::JsThirdProviderInteractionOperation>(
        ohAccessibilityProvider, jsAccessibilityManager, frameNode);
    jsInteractionOperation->SetBelongTreeId(0);

    bool ret;

    int64_t elementId = 0;
    Accessibility::AccessibilityElementInfo info;
    int64_t hostElementId = 0;
    // 1 jsThirdProviderOperator not registered
    ret = jsAccessibilityManager->GetElementInfoForThird(elementId, info, hostElementId);
    EXPECT_EQ(ret, false);

    jsAccessibilityManager->RegisterJsThirdProviderInteractionOperation(hostElementId, jsInteractionOperation);
    // 2 FindAccessibilityNodeInfosByIdFromProvider not ok
    ohAccessibilityProvider->SetInjectResult(-1);
    ret = jsAccessibilityManager->GetElementInfoForThird(elementId, info, hostElementId);
    EXPECT_EQ(ret, false);

    // 3 FindAccessibilityNodeInfosByIdFromProvider ok, info equals to mock element info
    ohAccessibilityProvider->providerMockResult_.Reset();
    ret = jsAccessibilityManager->GetElementInfoForThird(elementId, info, hostElementId);
    EXPECT_EQ(ret, true);

    EXPECT_EQ(info.GetAccessibilityId(),
        ohAccessibilityProvider->providerMockResult_.elementInfosList_[elementId].GetElementId());
}

/**
 * @tc.name: JsThirdAccessibilityHoverNgTest001
 * @tc.desc: ClearFocusFromProvider
 * @tc.type: FUNC
 */
HWTEST_F(JsThirdAccessibilityHoverNgTest, JsThirdAccessibilityHoverNgTest002, TestSize.Level1)
{
    auto ohAccessibilityProvider
        = AceType::MakeRefPtr<MockOhAccessibilityProvider>();
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    auto context = NG::PipelineContext::GetCurrentContext();
    jsAccessibilityManager->SetPipelineContext(context);
    jsAccessibilityManager->Register(true);

    auto jsInteractionOperation = std::make_shared<Framework::JsThirdProviderInteractionOperation>(
        ohAccessibilityProvider, jsAccessibilityManager, frameNode);
    jsInteractionOperation->SetBelongTreeId(0);

    std::string hitTestMode = "HitTestMode.Block";
    bool shouldSearchSelf = true;
    bool shouldSearchChildren = true;
    // 1 HitTestMode.Block
    jsAccessibilityManager->UpdateSearchStrategyByHitTestModeStr(hitTestMode, shouldSearchSelf, shouldSearchChildren);
    EXPECT_EQ(shouldSearchSelf, true);
    EXPECT_EQ(shouldSearchChildren, false);

    // 2 HitTestMode.None
    hitTestMode = "HitTestMode.None";
    shouldSearchSelf = true;
    shouldSearchChildren = true;
    jsAccessibilityManager->UpdateSearchStrategyByHitTestModeStr(hitTestMode, shouldSearchSelf, shouldSearchChildren);
    EXPECT_EQ(shouldSearchSelf, false);
    EXPECT_EQ(shouldSearchChildren, true);

    // 3 HitTestMode.Default
    hitTestMode = "HitTestMode.Default";
    shouldSearchSelf = true;
    shouldSearchChildren = true;
    jsAccessibilityManager->UpdateSearchStrategyByHitTestModeStr(hitTestMode, shouldSearchSelf, shouldSearchChildren);
    EXPECT_EQ(shouldSearchSelf, true);
    EXPECT_EQ(shouldSearchChildren, true);
}

/**
 * @tc.name: JsThirdAccessibilityHoverNgTest003
 * @tc.desc: IsAccessibilityFocusable
 * @tc.type: FUNC
 */
HWTEST_F(JsThirdAccessibilityHoverNgTest, JsThirdAccessibilityHoverNgTest003, TestSize.Level1)
{
    auto ohAccessibilityProvider
        = AceType::MakeRefPtr<MockOhAccessibilityProvider>();
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    auto context = NG::PipelineContext::GetCurrentContext();
    jsAccessibilityManager->SetPipelineContext(context);
    jsAccessibilityManager->Register(true);

    auto jsInteractionOperation = std::make_shared<Framework::JsThirdProviderInteractionOperation>(
        ohAccessibilityProvider, jsAccessibilityManager, frameNode);
    jsInteractionOperation->SetBelongTreeId(0);

    bool ret;
    Accessibility::AccessibilityElementInfo nodeInfo;

    // level yes
    nodeInfo.SetAccessibilityLevel(NG::AccessibilityProperty::Level::YES_STR);
    ret = jsAccessibilityManager->IsAccessibilityFocusable(nodeInfo);
    EXPECT_EQ(ret, true);

    // level no
    nodeInfo.SetAccessibilityLevel(NG::AccessibilityProperty::Level::NO_STR);
    ret = jsAccessibilityManager->IsAccessibilityFocusable(nodeInfo);
    EXPECT_EQ(ret, false);
    nodeInfo.SetAccessibilityLevel(NG::AccessibilityProperty::Level::AUTO);

    // group true
    nodeInfo.SetAccessibilityGroup(true);
    ret = jsAccessibilityManager->IsAccessibilityFocusable(nodeInfo);
    EXPECT_EQ(ret, true);
}

/**
 * @tc.name: JsThirdAccessibilityHoverNgTest004
 * @tc.desc: IsAccessibilityFocusable
 * @tc.type: FUNC
 */
HWTEST_F(JsThirdAccessibilityHoverNgTest, JsThirdAccessibilityHoverNgTest004, TestSize.Level1)
{
    auto ohAccessibilityProvider
        = AceType::MakeRefPtr<MockOhAccessibilityProvider>();
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    auto context = NG::PipelineContext::GetCurrentContext();
    jsAccessibilityManager->SetPipelineContext(context);
    jsAccessibilityManager->Register(true);

    auto jsInteractionOperation = std::make_shared<Framework::JsThirdProviderInteractionOperation>(
        ohAccessibilityProvider, jsAccessibilityManager, frameNode);
    jsInteractionOperation->SetBelongTreeId(0);

    bool ret;
    Accessibility::AccessibilityElementInfo nodeInfo;

    bool shouldSearchSelf;
    bool shouldSearchChildren;
    std::pair<bool, bool> result;
    // level yes
    nodeInfo.SetAccessibilityLevel(NG::AccessibilityProperty::Level::YES_STR);
    result = jsAccessibilityManager->GetSearchStrategyForThird(nodeInfo);
    shouldSearchSelf = result.first;
    shouldSearchChildren = result.second;
    EXPECT_EQ(shouldSearchSelf, true);
    EXPECT_EQ(shouldSearchChildren, true);

    // level NO_HIDE_DESCENDANTS
    nodeInfo.SetAccessibilityLevel(NG::AccessibilityProperty::Level::NO_HIDE_DESCENDANTS);
    result = jsAccessibilityManager->GetSearchStrategyForThird(nodeInfo);
    shouldSearchSelf = result.first;
    shouldSearchChildren = result.second;
    EXPECT_EQ(shouldSearchSelf, false);
    EXPECT_EQ(shouldSearchChildren, false);

    // level NO  with AccessibilityText
    nodeInfo.SetAccessibilityLevel(NG::AccessibilityProperty::Level::NO_STR);
    nodeInfo.SetAccessibilityText("test");
    result = jsAccessibilityManager->GetSearchStrategyForThird(nodeInfo);
    shouldSearchSelf = result.first;
    shouldSearchChildren = result.second;
    EXPECT_EQ(shouldSearchSelf, false);
    EXPECT_EQ(shouldSearchChildren, true);

    // level NO
    nodeInfo.SetAccessibilityLevel(NG::AccessibilityProperty::Level::NO_STR);
    result = jsAccessibilityManager->GetSearchStrategyForThird(nodeInfo);
    shouldSearchSelf = result.first;
    shouldSearchChildren = result.second;
    EXPECT_EQ(shouldSearchSelf, false);
    EXPECT_EQ(shouldSearchChildren, true);
}

/**
 * @tc.name: JsThirdAccessibilityHoverNgTest004
 * @tc.desc: IsAccessibilityFocusable
 * @tc.type: FUNC
 */
HWTEST_F(JsThirdAccessibilityHoverNgTest, JsThirdAccessibilityHoverNgTest0041, TestSize.Level1)
{
    auto ohAccessibilityProvider
        = AceType::MakeRefPtr<MockOhAccessibilityProvider>();
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    auto context = NG::PipelineContext::GetCurrentContext();
    jsAccessibilityManager->SetPipelineContext(context);
    jsAccessibilityManager->Register(true);

    auto jsInteractionOperation = std::make_shared<Framework::JsThirdProviderInteractionOperation>(
        ohAccessibilityProvider, jsAccessibilityManager, frameNode);
    jsInteractionOperation->SetBelongTreeId(0);

    bool ret;
    Accessibility::AccessibilityElementInfo nodeInfo;

    bool shouldSearchSelf;
    bool shouldSearchChildren;
    std::pair<bool, bool> result;

    // level auto and not accessibility text and hit test mode default
    nodeInfo.SetAccessibilityLevel(NG::AccessibilityProperty::Level::AUTO);
    result = jsAccessibilityManager->GetSearchStrategyForThird(nodeInfo);
    shouldSearchSelf = result.first;
    shouldSearchChildren = result.second;
    EXPECT_EQ(shouldSearchSelf, true);
    EXPECT_EQ(shouldSearchChildren, true);

    // level auto and has accessibility text and hit test mode none
    nodeInfo.SetAccessibilityLevel(NG::AccessibilityProperty::Level::AUTO);
    nodeInfo.SetAccessibilityText("test");
    nodeInfo.SetHitTestBehavior("HitTestMode.None");
    result = jsAccessibilityManager->GetSearchStrategyForThird(nodeInfo);
    shouldSearchSelf = result.first;
    shouldSearchChildren = result.second;
    EXPECT_EQ(shouldSearchSelf, true);
    EXPECT_EQ(shouldSearchChildren, true);


    // level auto and has accessibility text and hit test mode default
    nodeInfo.SetAccessibilityLevel(NG::AccessibilityProperty::Level::AUTO);
    nodeInfo.SetAccessibilityText("");
    nodeInfo.SetHitTestBehavior("HitTestMode.None");
    result = jsAccessibilityManager->GetSearchStrategyForThird(nodeInfo);
    shouldSearchSelf = result.first;
    shouldSearchChildren = result.second;
    EXPECT_EQ(shouldSearchSelf, false);
    EXPECT_EQ(shouldSearchChildren, true);
}

/**
 * @tc.name: JsThirdAccessibilityHoverNgTest004
 * @tc.desc: IsAccessibilityFocusable
 * @tc.type: FUNC
 */
HWTEST_F(JsThirdAccessibilityHoverNgTest, JsThirdAccessibilityHoverNgTest005, TestSize.Level1)
{
    auto ohAccessibilityProvider
        = AceType::MakeRefPtr<MockOhAccessibilityProvider>();
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    auto context = NG::PipelineContext::GetCurrentContext();
    jsAccessibilityManager->SetPipelineContext(context);
    jsAccessibilityManager->Register(true);

    auto jsInteractionOperation = std::make_shared<Framework::JsThirdProviderInteractionOperation>(
        ohAccessibilityProvider, jsAccessibilityManager, frameNode);
    jsInteractionOperation->SetBelongTreeId(0);
    int64_t hostElementId = 0;
    jsAccessibilityManager->RegisterJsThirdProviderInteractionOperation(hostElementId, jsInteractionOperation);

    NG::PointF point(1, 1);
    auto elementInfoListSize = ohAccessibilityProvider->providerMockResult_.elementInfosList_.size();
    for (int32_t i = 0; i < elementInfoListSize; i++) {
        auto leftTopX = 0;
        auto leftTopY = 0;
        auto rightBottomX = 100;
        auto rightBottomY = 100;
        ArkUI_AccessibleRect screenRect {leftTopX, leftTopY, rightBottomX, rightBottomY};
        ohAccessibilityProvider->providerMockResult_.elementInfosList_[i].SetRect(screenRect);
    }
    Accessibility::AccessibilityElementInfo rootInfo;

    auto ret = jsAccessibilityManager->GetElementInfoForThird(-1, rootInfo, hostElementId);
    EXPECT_EQ(ret, true);
    auto path = jsAccessibilityManager->HoverPathForThird(hostElementId, point, rootInfo);
    EXPECT_EQ(path.size(), elementInfoListSize);
}

/**
 * @tc.name: JsThirdAccessibilityHoverNgTest004
 * @tc.desc: IsAccessibilityFocusable
 * @tc.type: FUNC
 */
HWTEST_F(JsThirdAccessibilityHoverNgTest, JsThirdAccessibilityHoverNgTest006, TestSize.Level1)
{
    auto ohAccessibilityProvider
        = AceType::MakeRefPtr<MockOhAccessibilityProvider>();
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    auto context = NG::PipelineContext::GetCurrentContext();
    jsAccessibilityManager->SetPipelineContext(context);
    jsAccessibilityManager->Register(true);

    auto jsInteractionOperation = std::make_shared<Framework::JsThirdProviderInteractionOperation>(
        ohAccessibilityProvider, jsAccessibilityManager, frameNode);
    jsInteractionOperation->SetBelongTreeId(0);
    int64_t hostElementId = 0;
    jsAccessibilityManager->RegisterJsThirdProviderInteractionOperation(hostElementId, jsInteractionOperation);

    bool ret;

    auto elementInfoListSize = ohAccessibilityProvider->providerMockResult_.elementInfosList_.size();
    for (int32_t i = 0; i < elementInfoListSize; i++) {
        auto leftTopX = 0;
        auto leftTopY = 0;
        auto rightBottomX = 100;
        auto rightBottomY = 100;
        ArkUI_AccessibleRect screenRect {leftTopX, leftTopY, rightBottomX, rightBottomY};
        ohAccessibilityProvider->providerMockResult_.elementInfosList_[i].SetRect(screenRect);
    }

    NG::PointF point(0, 0);
    SourceType sourceType = SourceType::NONE;
    NG::AccessibilityHoverEventType eventType = NG::AccessibilityHoverEventType::ENTER;
    TimeStamp time = std::chrono::high_resolution_clock::now();
    Framework::AccessibilityHoverForThirdConfig config
        {hostElementId, point, sourceType, eventType, time, context};

    jsAccessibilityManager->HandleAccessibilityHoverForThird(config);
    // tbm  mock client to check event;
    EXPECT_NE(frameNode, nullptr);
}


/**
 * @tc.name: JsThirdAccessibilityHoverNgTest007
 * @tc.desc: IsAccessibilityFocusable
 * @tc.type: FUNC
 */
HWTEST_F(JsThirdAccessibilityHoverNgTest, JsThirdAccessibilityHoverNgTest007, TestSize.Level1)
{
    auto ohAccessibilityProvider
        = AceType::MakeRefPtr<MockOhAccessibilityProvider>();
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    auto context = NG::PipelineContext::GetCurrentContext();
    jsAccessibilityManager->SetPipelineContext(context);
    jsAccessibilityManager->Register(true);

    auto jsInteractionOperation = std::make_shared<Framework::JsThirdProviderInteractionOperation>(
        ohAccessibilityProvider, jsAccessibilityManager, frameNode);
    jsInteractionOperation->SetBelongTreeId(0);
    int64_t hostElementId = 0;
    jsAccessibilityManager->RegisterJsThirdProviderInteractionOperation(hostElementId, jsInteractionOperation);

    std::vector<std::string> info;
    // 1. dump property
    std::vector<std::string> params;
    params.push_back("-inspector");
    params.push_back("1");

    jsAccessibilityManager->OnDumpChildInfoForThirdRecursive(hostElementId, params, info, jsAccessibilityManager);
    // tbm  make sure check method;
    EXPECT_NE(frameNode, nullptr);
    // 2. dump tree
    params.clear();
    params.push_back("-inspector");
    params.push_back("--root");
    params.push_back("1");
    params.push_back("2");

    jsAccessibilityManager->OnDumpChildInfoForThirdRecursive(hostElementId, params, info, jsAccessibilityManager);
    // tbm  make sure check method;
    EXPECT_NE(frameNode, nullptr);
}

namespace {
class MockThirdFocusJsAccessibilityManager : public Framework::JsAccessibilityManager {
public:
    MOCK_METHOD0(GenerateAccessibilityWorkMode, AccessibilityWorkMode());
};

void SetScreenReaderEnabledForThirdFocus(
    const RefPtr<Framework::JsAccessibilityManager>& manager, bool enabled)
{
    manager->isScreenReaderEnabled_ = enabled;
    manager->isScreenReaderEnabledInitialized_ = true;
}

void SetContextAccessibilityManagerForThirdFocus(
    const RefPtr<NG::PipelineContext>& context,
    const RefPtr<MockFrontend>& mockFrontend,
    const RefPtr<MockThirdFocusJsAccessibilityManager>& manager)
{
    RefPtr<AccessibilityManager> accessibilityManager = manager;
    ON_CALL(*mockFrontend, GetAccessibilityManager()).WillByDefault(testing::Return(accessibilityManager));
    context->weakFrontend_ = mockFrontend;
}
} // namespace

/**
 * @tc.name: ActThirdAccessibilityFocusKeepThirdProviderFocus002
 * @tc.desc: screen reader disabled, focusing one third node keeps other focused third provider nodes
 * @tc.type: FUNC
 */
HWTEST_F(JsThirdAccessibilityHoverNgTest, ActThirdAccessibilityFocusKeepThirdProviderFocus002, TestSize.Level1)
{
    auto context = NG::PipelineContext::GetCurrentContext();
    auto manager = AceType::MakeRefPtr<testing::NiceMock<MockThirdFocusJsAccessibilityManager>>();
    ON_CALL(*manager, GenerateAccessibilityWorkMode())
        .WillByDefault(testing::Return(AccessibilityWorkMode { .isTouchExplorationEnabled = true }));
    manager->SetPipelineContext(context);
    manager->Register(true);
    auto mockFrontend = AceType::MakeRefPtr<testing::NiceMock<MockFrontend>>();
    SetContextAccessibilityManagerForThirdFocus(context, mockFrontend, manager);
    SetScreenReaderEnabledForThirdFocus(manager, false);

    auto currentHost = FrameNode::CreateFrameNode("currentHost", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto otherHost = FrameNode::CreateFrameNode("otherHost", 2, AceType::MakeRefPtr<Pattern>(), true);
    auto currentRender = AceType::MakeRefPtr<MockRenderContext>();
    auto otherRender = AceType::MakeRefPtr<MockRenderContext>();
    currentHost->renderContext_ = currentRender;
    otherHost->renderContext_ = otherRender;

    auto currentProvider = AceType::MakeRefPtr<MockOhAccessibilityProvider>();
    currentProvider->providerMockResult_.receiveClear_ = false;
    auto otherProvider = AceType::MakeRefPtr<MockOhAccessibilityProvider>();
    otherProvider->providerMockResult_.receiveClear_ = false;
    auto currentOp = std::make_shared<Framework::JsThirdProviderInteractionOperation>(
        currentProvider, manager, currentHost);
    auto otherOp = std::make_shared<Framework::JsThirdProviderInteractionOperation>(
        otherProvider, manager, otherHost);
    currentOp->SetBelongTreeId(0);
    otherOp->SetBelongTreeId(0);
    manager->RegisterJsThirdProviderInteractionOperation(1, currentOp);
    manager->RegisterJsThirdProviderInteractionOperation(2, otherOp);

    otherRender->UpdateAccessibilityFocus(true);

    Accessibility::AccessibilityElementInfo nodeInfo;
    Accessibility::Rect screenRect(0, 0, 100, 100);
    nodeInfo.SetRectInScreen(screenRect);

    auto ret = manager->ActThirdAccessibilityFocus(2, nodeInfo, currentHost, context, false);

    EXPECT_EQ(ret, true);
    // screen reader disabled: other focused provider is kept
    EXPECT_EQ(otherProvider->providerMockResult_.receiveClear_, false);
    EXPECT_EQ(otherRender->GetAccessibilityFocus().value_or(false), true);
    // current host still gains focus
    EXPECT_EQ(currentRender->GetAccessibilityFocus().value_or(false), true);
}

/**
 * @tc.name: ActThirdAccessibilityFocusClearSelfOnly003
 * @tc.desc: clear focus action only clears the given node, never triggers provider focus clear
 * @tc.type: FUNC
 */
HWTEST_F(JsThirdAccessibilityHoverNgTest, ActThirdAccessibilityFocusClearSelfOnly003, TestSize.Level1)
{
    auto context = NG::PipelineContext::GetCurrentContext();
    auto manager = AceType::MakeRefPtr<testing::NiceMock<MockThirdFocusJsAccessibilityManager>>();
    ON_CALL(*manager, GenerateAccessibilityWorkMode())
        .WillByDefault(testing::Return(AccessibilityWorkMode { .isTouchExplorationEnabled = true }));
    manager->SetPipelineContext(context);
    manager->Register(true);
    auto mockFrontend = AceType::MakeRefPtr<testing::NiceMock<MockFrontend>>();
    SetContextAccessibilityManagerForThirdFocus(context, mockFrontend, manager);
    SetScreenReaderEnabledForThirdFocus(manager, true);

    auto currentHost = FrameNode::CreateFrameNode("currentHost", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto otherHost = FrameNode::CreateFrameNode("otherHost", 2, AceType::MakeRefPtr<Pattern>(), true);
    auto currentRender = AceType::MakeRefPtr<MockRenderContext>();
    auto otherRender = AceType::MakeRefPtr<MockRenderContext>();
    currentHost->renderContext_ = currentRender;
    otherHost->renderContext_ = otherRender;

    auto currentProvider = AceType::MakeRefPtr<MockOhAccessibilityProvider>();
    currentProvider->providerMockResult_.receiveClear_ = false;
    auto otherProvider = AceType::MakeRefPtr<MockOhAccessibilityProvider>();
    otherProvider->providerMockResult_.receiveClear_ = false;
    auto currentOp = std::make_shared<Framework::JsThirdProviderInteractionOperation>(
        currentProvider, manager, currentHost);
    auto otherOp = std::make_shared<Framework::JsThirdProviderInteractionOperation>(
        otherProvider, manager, otherHost);
    currentOp->SetBelongTreeId(0);
    otherOp->SetBelongTreeId(0);
    manager->RegisterJsThirdProviderInteractionOperation(1, currentOp);
    manager->RegisterJsThirdProviderInteractionOperation(2, otherOp);

    currentRender->UpdateAccessibilityFocus(true);
    otherRender->UpdateAccessibilityFocus(true);

    Accessibility::AccessibilityElementInfo nodeInfo;
    Accessibility::Rect screenRect(0, 0, 100, 100);
    nodeInfo.SetRectInScreen(screenRect);

    auto ret = manager->ActThirdAccessibilityFocus(1, nodeInfo, currentHost, context, true);

    EXPECT_EQ(ret, true);
    // only the given node focus is cleared, other focused provider is untouched
    EXPECT_EQ(currentRender->GetAccessibilityFocus().value_or(true), false);
    EXPECT_EQ(otherRender->GetAccessibilityFocus().value_or(false), true);
    EXPECT_EQ(otherProvider->providerMockResult_.receiveClear_, false);
    EXPECT_EQ(currentProvider->providerMockResult_.receiveClear_, false);
}

/**
 * @tc.name: ActThirdAccessibilityFocusSkipInvalidThirdProvider004
 * @tc.desc: null host, expired operator and unfocused host are skipped safely when clearing focus
 * @tc.type: FUNC
 */
HWTEST_F(JsThirdAccessibilityHoverNgTest, ActThirdAccessibilityFocusSkipInvalidThirdProvider004, TestSize.Level1)
{
    auto context = NG::PipelineContext::GetCurrentContext();
    auto manager = AceType::MakeRefPtr<testing::NiceMock<MockThirdFocusJsAccessibilityManager>>();
    ON_CALL(*manager, GenerateAccessibilityWorkMode())
        .WillByDefault(testing::Return(AccessibilityWorkMode { .isTouchExplorationEnabled = true }));
    manager->SetPipelineContext(context);
    manager->Register(true);
    auto mockFrontend = AceType::MakeRefPtr<testing::NiceMock<MockFrontend>>();
    SetContextAccessibilityManagerForThirdFocus(context, mockFrontend, manager);
    SetScreenReaderEnabledForThirdFocus(manager, true);

    auto currentHost = FrameNode::CreateFrameNode("currentHost", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto currentRender = AceType::MakeRefPtr<MockRenderContext>();
    currentHost->renderContext_ = currentRender;

    // 1. operator with null host
    auto nullHostProvider = AceType::MakeRefPtr<MockOhAccessibilityProvider>();
    nullHostProvider->providerMockResult_.receiveClear_ = false;
    RefPtr<FrameNode> nullHost;
    auto nullHostOp = std::make_shared<Framework::JsThirdProviderInteractionOperation>(
        nullHostProvider, manager, nullHost);
    nullHostOp->SetBelongTreeId(0);
    manager->RegisterJsThirdProviderInteractionOperation(10, nullHostOp);

    // 2. operator that will expire before the focus act
    {
        auto tempHost = FrameNode::CreateFrameNode("tempHost", 2, AceType::MakeRefPtr<Pattern>(), true);
        tempHost->renderContext_ = AceType::MakeRefPtr<MockRenderContext>();
        auto tempProvider = AceType::MakeRefPtr<MockOhAccessibilityProvider>();
        tempProvider->providerMockResult_.receiveClear_ = false;
        auto tempOp = std::make_shared<Framework::JsThirdProviderInteractionOperation>(
            tempProvider, manager, tempHost);
        tempOp->SetBelongTreeId(0);
        manager->RegisterJsThirdProviderInteractionOperation(11, tempOp);
        tempHost->renderContext_->UpdateAccessibilityFocus(true);
    }

    // 3. operator whose host is not accessibility focused
    auto unfocusedHost = FrameNode::CreateFrameNode("unfocusedHost", 3, AceType::MakeRefPtr<Pattern>(), true);
    unfocusedHost->renderContext_ = AceType::MakeRefPtr<MockRenderContext>();
    auto unfocusedProvider = AceType::MakeRefPtr<MockOhAccessibilityProvider>();
    unfocusedProvider->providerMockResult_.receiveClear_ = false;
    auto unfocusedOp = std::make_shared<Framework::JsThirdProviderInteractionOperation>(
        unfocusedProvider, manager, unfocusedHost);
    unfocusedOp->SetBelongTreeId(0);
    manager->RegisterJsThirdProviderInteractionOperation(12, unfocusedOp);

    Accessibility::AccessibilityElementInfo nodeInfo;
    Accessibility::Rect screenRect(0, 0, 100, 100);
    nodeInfo.SetRectInScreen(screenRect);

    auto ret = manager->ActThirdAccessibilityFocus(1, nodeInfo, currentHost, context, false);

    EXPECT_EQ(ret, true);
    // invalid operators are skipped without clearing
    EXPECT_EQ(nullHostProvider->providerMockResult_.receiveClear_, false);
    EXPECT_EQ(unfocusedProvider->providerMockResult_.receiveClear_, false);
    // current host still gains focus
    EXPECT_EQ(currentRender->GetAccessibilityFocus().value_or(false), true);
}

} // namespace OHOS::Ace::NG