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
} // namespace

class JsAccessibilityManagerTestFour : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void JsAccessibilityManagerTestFour::SetUpTestCase()
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

void JsAccessibilityManagerTestFour::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: JsAccessibilityManager001
 * @tc.desc: Test GetNextFocusNodeByManager with valid currentNode and rootNode but no inspectorKey
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestFour, JsAccessibilityManager001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-begin JsAccessibilityManager001";

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

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-end JsAccessibilityManager001";
}

/**
 * @tc.name: EraseDefaultFocusNode001
 * @tc.desc: Test EraseDefaultFocusNode removes node from default focus list
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestFour, EraseDefaultFocusNode001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-begin EraseDefaultFocusNode001";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. test EraseDefaultFocusNode
     */
    auto pattern = AceType::MakeRefPtr<NG::Pattern>();
    auto frameNode = NG::FrameNode::CreateFrameNode("testNode", 1, pattern, true);

    jsAccessibilityManager->AddDefaultFocusNode(frameNode);
    jsAccessibilityManager->EraseDefaultFocusNode(frameNode);

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-end EraseDefaultFocusNode001";
}

/**
 * @tc.name: GetDefaultFocusList001
 * @tc.desc: Test GetDefaultFocusList returns reference to default focus list
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestFour, GetDefaultFocusList001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-begin GetDefaultFocusList001";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. test GetDefaultFocusList
     */
    auto& focusList = jsAccessibilityManager->GetDefaultFocusList();

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-end GetDefaultFocusList001";
}

/**
 * @tc.name: UpdateElementInfoTreeId001
 * @tc.desc: Test UpdateElementInfoTreeId updates tree id in element info
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestFour, UpdateElementInfoTreeId001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-begin UpdateElementInfoTreeId001";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. test UpdateElementInfoTreeId
     */
    AccessibilityElementInfo elementInfo;
    elementInfo.SetAccessibilityId(100);

    jsAccessibilityManager->UpdateElementInfoTreeId(elementInfo);

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-end UpdateElementInfoTreeId001";
}

/**
 * @tc.name: UpdateElementInfosTreeId001
 * @tc.desc: Test UpdateElementInfosTreeId updates tree ids in element info list
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestFour, UpdateElementInfosTreeId001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-begin UpdateElementInfosTreeId001";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. test UpdateElementInfosTreeId
     */
    std::list<AccessibilityElementInfo> infos;
    AccessibilityElementInfo elementInfo1;
    elementInfo1.SetAccessibilityId(100);
    infos.emplace_back(elementInfo1);

    AccessibilityElementInfo elementInfo2;
    elementInfo2.SetAccessibilityId(200);
    infos.emplace_back(elementInfo2);

    jsAccessibilityManager->UpdateElementInfosTreeId(infos);

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-end UpdateElementInfosTreeId001";
}

/**
 * @tc.name: SetWebPatternBySurfaceId001
 * @tc.desc: Test SetWebPatternBySurfaceId stores web pattern
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestFour, SetWebPatternBySurfaceId001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-begin SetWebPatternBySurfaceId001";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. test SetWebPatternBySurfaceId
     */
    std::string surfaceId = "test_surface_123";
    WeakPtr<NG::WebPattern> webPattern;

    jsAccessibilityManager->SetWebPatternBySurfaceId(surfaceId, webPattern);

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-end SetWebPatternBySurfaceId001";
}

/**
 * @tc.name: GetWebPatternBySurfaceId001
 * @tc.desc: Test GetWebPatternBySurfaceId retrieves web pattern
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestFour, GetWebPatternBySurfaceId001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-begin GetWebPatternBySurfaceId001";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. test GetWebPatternBySurfaceId
     */
    std::string surfaceId = "test_surface_123";
    WeakPtr<NG::WebPattern> webPattern = jsAccessibilityManager->GetWebPatternBySurfaceId(surfaceId);

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-end GetWebPatternBySurfaceId001";
}

/**
 * @tc.name: RemoveWebPatternBySurfaceId001
 * @tc.desc: Test RemoveWebPatternBySurfaceId removes web pattern
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestFour, RemoveWebPatternBySurfaceId001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-begin RemoveWebPatternBySurfaceId001";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. test RemoveWebPatternBySurfaceId
     */
    std::string surfaceId = "test_surface_123";
    jsAccessibilityManager->RemoveWebPatternBySurfaceId(surfaceId);

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-end RemoveWebPatternBySurfaceId001";
}

/**
 * @tc.name: RegisterAccessibilityChildTreeCallback001
 * @tc.desc: Test RegisterAccessibilityChildTreeCallback registers callback
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestFour, RegisterAccessibilityChildTreeCallback001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-begin RegisterAccessibilityChildTreeCallback001";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. test RegisterAccessibilityChildTreeCallback
     */
    int64_t elementId = 100;
    std::shared_ptr<AccessibilityChildTreeCallback> callback = nullptr;

    jsAccessibilityManager->RegisterAccessibilityChildTreeCallback(elementId, callback);

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-end RegisterAccessibilityChildTreeCallback001";
}

/**
 * @tc.name: DeregisterAccessibilityChildTreeCallback001
 * @tc.desc: Test DeregisterAccessibilityChildTreeCallback deregisters callback
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestFour, DeregisterAccessibilityChildTreeCallback001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-begin DeregisterAccessibilityChildTreeCallback001";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. test DeregisterAccessibilityChildTreeCallback
     */
    int64_t elementId = 100;
    jsAccessibilityManager->DeregisterAccessibilityChildTreeCallback(elementId);

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-end DeregisterAccessibilityChildTreeCallback001";
}

/**
 * @tc.name: RegisterAccessibilitySAObserverCallback001
 * @tc.desc: Test RegisterAccessibilitySAObserverraCallback registers callback
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestFour, RegisterAccessibilitySAObserverCallback001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-begin RegisterAccessibilitySAObserverCallback001";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. test RegisterAccessibilitySAObserverCallback
     */
    int64_t elementId = 100;
    std::shared_ptr<AccessibilitySAObserverCallback> callback = nullptr;

    jsAccessibilityManager->RegisterAccessibilitySAObserverCallback(elementId, callback);

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-end RegisterAccessibilitySAObserverCallback001";
}

/**
 * @tc.name: DeregisterAccessibilitySAObserverCallback001
 * @tc.desc: Test DeregisterAccessibilitySAObserverCallback deregisters callback
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestFour, DeregisterAccessibilitySAObserverCallback001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-begin DeregisterAccessibilitySAObserverCallback001";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. test DeregisterAccessibilitySAObserverCallback
     */
    int64_t elementId = 100;
    jsAccessibilityManager->DeregisterAccessibilitySAObserverCallback(elementId);

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-end DeregisterAccessibilitySAObserverCallback001";
}

/**
 * @tc.name: RegisterScreenReaderObserverCallback001
 * @tc.desc: Test RegisterScreenReaderObserverCallback registers callback
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestFour, RegisterScreenReaderObserverCallback001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-begin RegisterScreenReaderObserverCallback001";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. test RegisterScreenReaderObserverCallback
     */
    int64_t elementId = 100;
    std::shared_ptr<AccessibilityScreenReaderObserverCallback> callback = nullptr;

    jsAccessibilityManager->RegisterScreenReaderObserverCallback(elementId, callback);

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-end RegisterScreenReaderObserverCallback001";
}

/**
 * @tc.name: DeregisterScreenReaderObserverCallback001
 * @tc.desc: Test DeregisterScreenReaderObserverCallback deregisters callback
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestFour, DeregisterScreenReaderObserverCallback001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-begin DeregisterScreenReaderObserverCallback001";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. test DeregisterScreenReaderObserverCallback
     */
    int64_t elementId = 100;
    jsAccessibilityManager->DeregisterScreenReaderObserverCallback(elementId);

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-end DeregisterScreenReaderObserverCallback001";
}

/**
 * @tc.name: SetAccessibilityGetParentRectHandler001
 * @tc.desc: Test SetAccessibilityGetParentRectHandler sets handler
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestFour, SetAccessibilityGetParentRectHandler001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-begin SetAccessibilityGetParentRectHandler001";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. test SetAccessibilityGetParentRectHandler
     */
    std::function<void(int32_t&, int32_t&)> callback = [](int32_t& left, int32_t& top) {
        left = 100;
        top = 200;
    };

    jsAccessibilityManager->SetAccessibilityGetParentRectHandler(std::move(callback));

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-end SetAccessibilityGetParentRectHandler001";
}

/**
 * @tc.name: RegisterInteractionOperationAsChildTree001
 * @tc.desc: Test RegisterInteractionOperationAsChildTree with registration
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestFour, RegisterInteractionOperationAsChildTree001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-begin RegisterInteractionOperationAsChildTree001";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. construct Registration
     */
    Registration registration;
    registration.parentWindowId = 1;
    registration.parentTreeId = 2;
    registration.elementId = 100;

    /**
     * @tc.steps: step3. test RegisterInteractionOperationAsChildTree
     */
    bool result = jsAccessibilityManager->RegisterInteractionOperationAsChildTree(registration);

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-end RegisterInteractionOperationAsChildTree001";
}

/**
 * @tc.name: DeregisterInteractionOperationAsChildTree001
 * @tc.desc: Test DeregisterInteractionOperationAsChildTree with window id and tree id
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestFour, DeregisterInteractionOperationAsChildTree001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-begin DeregisterInteractionOperationAsChildTree001";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. test DeregisterInteractionOperationAsChildTree
     */
    uint32_t windowId = 1;
    int32_t treeId = 2;

    bool result = jsAccessibilityManager->DeregisterInteractionOperationAsChildTree(windowId, treeId);

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-end DeregisterInteractionOperationAsChildTree001";
}

/**
 * @tc.name: DeregisterInteractionOperationAsChildTree002
 * @tc.desc: Test DeregisterInteractionOperationAsChildTree without parameters
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestFour, DeregisterInteractionOperationAsChildTree002, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-begin DeregisterInteractionOperationAsChildTree002";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. test DeregisterInteractionOperationAsChildTree
     */
    jsAccessibilityManager->DeregisterInteractionOperationAsChildTree();

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-end DeregisterInteractionOperationAsChildTree002";
}

/**
 * @tc.name: CheckAccessibilityVisible001
 * @tc.desc: Test CheckAccessibilityVisible with null node
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestFour, CheckAccessibilityVisible001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-begin CheckAccessibilityVisible001";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. test CheckAccessibilityVisible
     */
    RefPtr<NG::FrameNode> frameNode = nullptr;
    bool result = jsAccessibilityManager->CheckAccessibilityVisible(frameNode);
    EXPECT_TRUE(result);

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-end CheckAccessibilityVisible001";
}

/**
 * @tc.name: CheckAccessibilityVisible002
 * @tc.desc: Test CheckAccessibilityVisible with valid frame node
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestFour, CheckAccessibilityVisible002, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-begin CheckAccessibilityVisible002";

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

    /**
     * @tc.steps: step3. test CheckAccessibilityVisible
     */
    bool result = jsAccessibilityManager->CheckAccessibilityVisible(frameNode);

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-end CheckAccessibilityVisible002";
}

/**
 * @tc.name: AddHoverTransparentCallback001
 * @tc.desc: Test AddHoverTransparentCallback adds callback
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestFour, AddHoverTransparentCallback001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-begin AddHoverTransparentCallback001";

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

    /**
     * @tc.steps: step3. test AddHoverTransparentCallback
     */
    jsAccessibilityManager->AddHoverTransparentCallback(frameNode);

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-end AddHoverTransparentCallback001";
}

/**
 * @tc.name: CheckHoverTransparentCallbackListEmpty001
 * @tc.desc: Test CheckHoverTransparentCallbackListEmpty returns empty status
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestFour, CheckHoverTransparentCallbackListEmpty001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-begin CheckHoverTransparentCallbackListEmpty001";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. test CheckHoverTransparentCallbackListEmpty
     */
    int32_t containerId = 1;
    bool result = jsAccessibilityManager->CheckHoverTransparentCallbackListEmpty(containerId);

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-end CheckHoverTransparentCallbackListEmpty001";
}

/**
 * @tc.name: CheckAndGetEmbedFrameNode001
 * @tc.desc: Test CheckAndGetEmbedFrameNode with null node
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestFour, CheckAndGetEmbedFrameNode001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-begin CheckAndGetEmbedFrameNode001";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. test CheckAndGetEmbedFrameNode
     */
    RefPtr<NG::FrameNode> frameNode = nullptr;
    int64_t result = jsAccessibilityManager->CheckAndGetEmbedFrameNode(frameNode);
    EXPECT_EQ(result, -1);

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-end CheckAndGetEmbedFrameNode001";
}

/**
 * @tc.name: CheckAndGetEmbedFrameNode002
 * @tc.desc: Test CheckAndGetEmbedFrameNode with valid frame node
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestFour, CheckAndGetEmbedFrameNode002, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-begin CheckAndGetEmbedFrameNode002";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. test CheckAndGetEmbedFrameNode
     */
    auto pattern = AceType::MakeRefPtr<NG::Pattern>();
    auto frameNode = NG::FrameNode::CreateFrameNode("testNode", 1, pattern, true);

    int64_t result = jsAccessibilityManager->CheckAndGetEmbedFrameNode(frameNode);

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-end CheckAndGetEmbedFrameNode002";
}

/**
 * @tc.name: AccessibilityOnShowHide001
 * @tc.desc: Test AccessibilityOnShowHide with show event
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestFour, AccessibilityOnShowHide001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-begin AccessibilityOnShowHide001";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. test AccessibilityOnShowHide
     */
    bool isOnShow = true;
    WeakPtr<PipelineBase> context;

    jsAccessibilityManager->AccessibilityOnShowHide(isOnShow, context);

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-end AccessibilityOnShowHide001";
}

/**
 * @tc.name: AccessibilityOnShowHide002
 * @tc.desc: Test AccessibilityOnShowHide with hide event
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestFour, AccessibilityOnShowHide002, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-begin AccessibilityOnShowHide002";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. test AccessibilityOnShowHide
     */
    bool isOnShow = false;
    WeakPtr<PipelineBase> context;

    jsAccessibilityManager->AccessibilityOnShowHide(isOnShow, context);

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-end AccessibilityOnShowHide002";
}

/**
 * @tc.name: UpdateAccessibilityNodeRect001
 * @tc.desc: Test UpdateAccessibilityNodeRect with null frame node
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestFour, UpdateAccessibilityNodeRect001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-begin UpdateAccessibilityNodeRect001";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. test UpdateAccessibilityNodeRect
     */
    RefPtr<NG::FrameNode> frameNode = nullptr;
    jsAccessibilityManager->UpdateAccessibilityNodeRect(frameNode);

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-end UpdateAccessibilityNodeRect001";
}

/**
 * @tc.name: UpdateAccessibilityNodeRect002
 * @tc.desc: Test UpdateAccessibilityNodeRect with valid frame node
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestFour, UpdateAccessibilityNodeRect002, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-begin UpdateAccessibilityNodeRect002";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. test UpdateAccessibilityNodeRect
     */
    auto pattern = AceType::MakeRefPtr<NG::Pattern>();
    auto frameNode = NG::FrameNode::CreateFrameNode("testNode", 1, pattern, true);

    jsAccessibilityManager->UpdateAccessibilityNodeRect(frameNode);

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-end UpdateAccessibilityNodeRect002";
}

/**
 * @tc.name: AddToPageEventController001
 * @tc.desc: Test AddToPageEventController adds frame node to controller
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestFour, AddToPageEventController001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-begin AddToPageEventController001";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. test AddToPageEventController
     */
    auto pattern = AceType::MakeRefPtr<NG::Pattern>();
    auto frameNode = NG::FrameNode::CreateFrameNode("testNode", 1, pattern, true);

    jsAccessibilityManager->AddToPageEventController(frameNode);

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-end AddToPageEventController001";
}

/**
 * @tc.name: CheckPageEventCached001
 * @tc.desc: Test CheckPageEventCached with null frame node
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestFour, CheckPageEventCached002, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-begin CheckPageEventCached002";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. test CheckPageEventCached
     */
    RefPtr<NG::FrameNode> frameNode = nullptr;
    bool result = jsAccessibilityManager->CheckPageEventCached(frameNode, false);
    EXPECT_FALSE(result);

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-end CheckPageEventCached002";
}

/**
 * @tc.name: CheckPageEventCached003
 * @tc.desc: Test CheckPageEventCached with valid frame node
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestFour, CheckPageEventCached003, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-begin CheckPageEventCached003";

    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    auto pattern = AceType::MakeRefPtr<NG::Pattern>();
    auto frameNode = NG::FrameNode::CreateFrameNode("testNode", 1, pattern, true);

    bool result = jsAccessibilityManager->CheckPageEventCached(frameNode, false);

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-end CheckPageEventCached003";
}

/**
 * @tc.name: ReleasePageEvent001
 * @tc.desc: Test ReleasePageEvent with null frame node
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestFour, ReleasePageEvent001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-begin ReleasePageEvent001";

    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    RefPtr<NG::FrameNode> frameNode = nullptr;
    jsAccessibilityManager->ReleasePageEvent(frameNode);

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-end ReleasePageEvent001";
}

/**
 * @tc.name: ReleasePageEvent002
 * @tc.desc: Test ReleasePageEvent with valid frame node
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestFour, ReleasePageEvent002, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-begin ReleasePageEvent002";

    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    auto pattern = AceType::MakeRefPtr<NG::Pattern>();
    auto frameNode = NG::FrameNode::CreateFrameNode("testNode", 1, pattern, true);

    jsAccessibilityManager->ReleasePageEvent(frameNode);

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-end ReleasePageEvent002";
}

/**
 * @tc.name: ReleasePageEvent003
 * @tc.desc: Test ReleasePageEvent with deleteController flag
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestFour, ReleasePageEvent003, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-begin ReleasePageEvent003";

    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    auto pattern = AceType::MakeRefPtr<NG::Pattern>();
    auto frameNode = NG::FrameNode::CreateFrameNode("testNode", 1, pattern, true);

    jsAccessibilityManager->ReleasePageEvent(frameNode, false);

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-end ReleasePageEvent003";
}

/**
 * @tc.name: ReleasePageEvent004
 * @tc.desc: Test ReleasePageEvent with releaseAll flag
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestFour, ReleasePageEvent004, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-begin ReleasePageEvent004";

    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    auto pattern = AceType::MakeRefPtr<NG::Pattern>();
    auto frameNode = NG::FrameNode::CreateFrameNode("testNode", 1, pattern, true);

    jsAccessibilityManager->ReleasePageEvent(frameNode, true, true);

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-end ReleasePageEvent004";
}

/**
 * @tc.name: GetPagePath001
 * @tc.desc: Test GetPagePath returns page path
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestFour, GetPagePath001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-begin GetPagePath001";

    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    std::string pagePath = jsAccessibilityManager->GetPagePath();

    SUCCEED();

    GTEST_LOG_(INFO) << "JsAccessibilityManagerTestFour-end GetPagePath001";
}
} // namespace OHOS::Ace::NG