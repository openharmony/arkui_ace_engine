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

#include "accessibility_system_ability_client.h"
#include "frameworks/core/accessibility/accessibility_manager.h"
#include "adapter/ohos/osal/js_third_provider_interaction_operation.h"

#include "base/log/dump_log.h"
#include "frameworks/core/accessibility/accessibility_node.h"
#include "frameworks/core/accessibility/accessibility_utils.h"
#include "frameworks/core/accessibility/native_interface_accessibility_provider.h"
#include "frameworks/core/components_ng/pattern/ui_extension/ui_extension_manager.h"
#include "js_third_provider_interaction_operation_test.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
namespace {
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
    NG::OffsetF hostOffset(0, 0);
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
    auto path = jsAccessibilityManager->HoverPathForThird(hostElementId, point, rootInfo, hostOffset);
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
        {hostElementId, point, sourceType, eventType, time, frameNode, context};

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

/**
 * @tc.name: JsAccessibilityManager001
 * @tc.desc: UpdateElementInfoTreeId
 * @tc.type: FUNC
 */
HWTEST_F(JsThirdAccessibilityHoverNgTest, JsAccessibilityManager001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    Accessibility::AccessibilityElementInfo info;
    info.SetPageId(1);
    info.SetParent(0);
    info.SetBelongTreeId(10);
    info.SetAccessibilityId(11);
    jsAccessibilityManager->UpdateElementInfoTreeId(info);
    EXPECT_NE(info.GetPageId(), 1);

    info.SetBelongTreeId(0);
    info.SetPageId(1);
    jsAccessibilityManager->UpdateElementInfoTreeId(info);
    EXPECT_EQ(info.GetPageId(), 1);
}

/**
 * @tc.name: JsAccessibilityManager002
 * @tc.desc: UpdateAccessibilityVisible
 * @tc.type: FUNC
 */
HWTEST_F(JsThirdAccessibilityHoverNgTest, JsAccessibilityManager002, TestSize.Level1)
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
} // namespace OHOS::Ace::NG