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

#include "frameworks/core/accessibility/accessibility_node.h"
#include "frameworks/core/accessibility/accessibility_utils.h"
#include "frameworks/core/accessibility/native_interface_accessibility_provider.h"
#include "frameworks/core/components_ng/pattern/ui_extension/ui_extension_manager.h"
#include "frameworks/core/components_ng/pattern/stage/page_pattern.h"
#include "adapter/ohos/osal/js_accessibility_manager.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Accessibility;

namespace OHOS::Ace {
int32_t g_mockErrorCode = -1;

std::string TEST_CONTENT_STR = "testForFindByText";
constexpr int32_t MAX_TEST_ELEMENT_COUNT = 10;
constexpr int32_t TEST_PARAMETER_OFFSET1 = 1;
constexpr int32_t TEST_PARAMETER_OFFSET2 = 2;
constexpr int32_t TEST_PARAMETER_OFFSET3 = 3;
constexpr int32_t SPECIAL_CURSOR_POSTION = 100;

class ProviderMockResult {
    public:
        ProviderMockResult()
        {
            for (int32_t i = 0; i < MAX_TEST_ELEMENT_COUNT; i++) {
                ArkUI_AccessibilityElementInfo tempElementInfo;
                tempElementInfo.SetElementId(i);
                tempElementInfo.SetContents(TEST_CONTENT_STR);
                elementInfosList_.push_back(tempElementInfo);
            }

            focusElementInfo_.SetElementId(
                MAX_TEST_ELEMENT_COUNT + TEST_PARAMETER_OFFSET1);
            nextFocusElementInfo_.SetElementId(
                MAX_TEST_ELEMENT_COUNT + TEST_PARAMETER_OFFSET2);

            originActionArguments_.emplace("action0", "1");
            originActionArguments_.emplace("action1", "2");
            cursorPosition_ = MAX_TEST_ELEMENT_COUNT + TEST_PARAMETER_OFFSET3;
        }
        ~ProviderMockResult() = default;

        void Reset()
        {
            elementId_ = 0;
            mode_ = static_cast<int32_t>(ARKUI_ACCESSIBILITY_NATIVE_SEARCH_MODE_PREFETCH_CURRENT);
            requestId_ = 0;
            focusType_ = ARKUI_ACCESSIBILITY_NATIVE_FOCUS_TYPE_INVALID;
            direction_ = ARKUI_ACCESSIBILITY_NATIVE_DIRECTION_INVALID;
            action_ = ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_INVALID;
            receiveClear_ = false;
            errorCode_ = 0;
            injectResult_ = 0;
            injectActionResult_ = 0;
        }

    public:
        int64_t elementId_;
        int32_t mode_;
        int32_t requestId_;
        std::vector<ArkUI_AccessibilityElementInfo> elementInfosList_;
        ArkUI_AccessibilityFocusType focusType_;
        ArkUI_AccessibilityElementInfo focusElementInfo_;
        ArkUI_AccessibilityElementInfo nextFocusElementInfo_;
        ArkUI_AccessibilityFocusMoveDirection direction_;
        ArkUI_Accessibility_ActionType action_;
        std::map<std::string, std::string> originActionArguments_;
        std::map<std::string, std::string> resultActionArguments_;
        int32_t cursorPosition_;
        bool receiveClear_;

        bool registerResult_;

        int32_t errorCode_;
        int32_t injectResult_ = 0;
        int32_t injectActionResult_ = 0;
        ArkUI_AccessibilityElementInfo elementInfo_;
};

class MockOhAccessibilityProvider : public AccessibilityProvider {
    DECLARE_ACE_TYPE(MockOhAccessibilityProvider, AccessibilityProvider);
public:
    MockOhAccessibilityProvider() = default;
    int32_t FindAccessibilityNodeInfosById(
        const int64_t elementId, const int32_t mode, const int32_t requestId,
        std::vector<ArkUI_AccessibilityElementInfo>& infos) override
    {
        providerMockResult_.elementId_ = elementId;
        providerMockResult_.mode_ = mode;
        providerMockResult_.requestId_ = requestId;

        infos = providerMockResult_.elementInfosList_;
        return providerMockResult_.injectResult_;
    }
    int32_t FindAccessibilityNodeInfosByText(
        const int64_t elementId, std::string text, const int32_t requestId,
        std::vector<ArkUI_AccessibilityElementInfo>& infos) override
    {
        providerMockResult_.elementId_ = elementId;
        providerMockResult_.requestId_ = requestId;

        std::string textStr(text);
        for (const auto &elementInfo: providerMockResult_.elementInfosList_) {
            if (elementInfo.GetContents() == textStr) {
                infos.push_back(elementInfo);
            }
        }

        return providerMockResult_.injectResult_;
    }
    int32_t FindFocusedAccessibilityNode(
        const int64_t elementId, int32_t focusType, const int32_t requestId,
        ArkUI_AccessibilityElementInfo& elementInfo) override
    {
        elementInfo = providerMockResult_.focusElementInfo_;
        return providerMockResult_.injectResult_;
    }
    int32_t FindNextFocusAccessibilityNode(
        const int64_t elementId, int32_t direction, const int32_t requestId,
        ArkUI_AccessibilityElementInfo& elementInfo) override
    {
        elementInfo = providerMockResult_.nextFocusElementInfo_;
        return providerMockResult_.injectResult_;
    }
    int32_t ExecuteAccessibilityAction(
        const int64_t elementId, int32_t action, const int32_t requestId,
        const std::map<std::string, std::string>& actionArguments) override
    {
        return providerMockResult_.injectActionResult_;
    }
    int32_t ClearFocusedAccessibilityNode() override
    {
        providerMockResult_.receiveClear_ = true;
        return providerMockResult_.injectResult_;
    }
    int32_t GetAccessibilityNodeCursorPosition(
        const int64_t elementId,
        const int32_t requestId,
        int32_t &cursorPosition) override
    {
        cursorPosition = SPECIAL_CURSOR_POSTION;
        return providerMockResult_.injectResult_;
    }
    int32_t SendAccessibilityAsyncEvent(
        const ArkUI_AccessibilityEventInfo& accessibilityEvent,
        void (*callback)(int32_t errorCode)) override
    {
        return providerMockResult_.injectResult_;
    }
    void SendThirdAccessibilityProvider(
        const std::weak_ptr<ThirdAccessibilityManager>& thirdAccessibilityManager)
        override {}

public:
    void SetInjectResult(int32_t injectResult)
    {
        providerMockResult_.injectResult_ = injectResult;
    }

    void SetInjectActionResult(int32_t injectResult)
    {
        providerMockResult_.injectActionResult_ = injectResult;
    }

    ProviderMockResult providerMockResult_;
};

class MockAccessibilityElementOperatorCallback : public Accessibility::AccessibilityElementOperatorCallback {
public:
    ~MockAccessibilityElementOperatorCallback() = default;

    void SetSearchElementInfoByAccessibilityIdResult(const std::list<Accessibility::AccessibilityElementInfo> &infos,
        const int32_t requestId)  override
    {
        mockInfos_ = infos;
        mockRequestId = requestId;
    }

    void SetSearchElementInfoByTextResult(const std::list<Accessibility::AccessibilityElementInfo> &infos,
        const int32_t requestId) override
    {
        mockInfos_ = infos;
        mockRequestId = requestId;
    }

    void SetFindFocusedElementInfoResult(
        const Accessibility::AccessibilityElementInfo &info,
        const int32_t requestId) override
    {
        mockInfo_ = info;
        mockRequestId = requestId;
    }

    void SetFocusMoveSearchResult(const Accessibility::AccessibilityElementInfo &info, const int32_t requestId) override
    {
        mockInfo_ = info;
        mockRequestId = requestId;
    }

    void SetExecuteActionResult(const bool succeeded, const int32_t requestId) override
    {
        mockSucceeded_ = succeeded;
        mockRequestId = requestId;
    }

    void SetCursorPositionResult(const int32_t cursorPosition, const int32_t requestId) override
    {
        mockCursorPosition_ = cursorPosition;
        mockRequestId = requestId;
    }

    std::list<Accessibility::AccessibilityElementInfo> mockInfos_;
    Accessibility::AccessibilityElementInfo mockInfo_;
    int32_t mockRequestId = 0;
    bool mockSucceeded_ = false;
    int32_t mockCursorPosition_ = 0;
};
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
namespace {
} // namespace

class JsThirdProviderInteractionOperationTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void JsThirdProviderInteractionOperationTest::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;
}

void JsThirdProviderInteractionOperationTest::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: JsThirdProviderInteractionOperationTest001
 * @tc.desc: ClearFocusFromProvider
 * @tc.type: FUNC
 */
HWTEST_F(JsThirdProviderInteractionOperationTest, JsThirdProviderInteractionOperationTest001, TestSize.Level1)
{
    auto ohAccessibilityProvider
        = AceType::MakeRefPtr<MockOhAccessibilityProvider>();

    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    auto jsInteractionOperation = AceType::MakeRefPtr<Framework::JsThirdProviderInteractionOperation>(
        ohAccessibilityProvider, jsAccessibilityManager, frameNode);

    auto ret =jsInteractionOperation->ClearFocusFromProvider();
    jsInteractionOperation->ClearFocus();
    EXPECT_EQ(ret, true);
    EXPECT_EQ(ohAccessibilityProvider->providerMockResult_.receiveClear_, true);
}

/**
 * @tc.name: JsThirdProviderInteractionOperationTest002
 * @tc.desc: SearchElementInfoByAccessibilityId
 * @tc.type: FUNC
 */
HWTEST_F(JsThirdProviderInteractionOperationTest, JsThirdProviderInteractionOperationTest002, TestSize.Level1)
{
    auto ohAccessibilityProvider
        = AceType::MakeRefPtr<MockOhAccessibilityProvider>();
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    auto context = NG::PipelineContext::GetCurrentContext();
    jsAccessibilityManager->SetPipelineContext(context);
    jsAccessibilityManager->Register(true);

    auto jsInteractionOperation = AceType::MakeRefPtr<Framework::JsThirdProviderInteractionOperation>(
        ohAccessibilityProvider, jsAccessibilityManager, frameNode);
    jsInteractionOperation->SetBelongTreeId(0);

    int64_t elementId = -1;
    int32_t requestId = 2;
    int32_t mode = 0;
    MockAccessibilityElementOperatorCallback operatorCallback;

    // 1 provider abnormal, callback should receive same request id and empty infos
    ohAccessibilityProvider->SetInjectResult(-1);
    jsInteractionOperation->SearchElementInfoByAccessibilityId(
        elementId, requestId,
        operatorCallback, mode);

    EXPECT_EQ(operatorCallback.mockInfos_.size(), 0);
    EXPECT_EQ(operatorCallback.mockRequestId, requestId);

    // 2 provider normal,callback should receive same request id and same infos as provider
    ohAccessibilityProvider->providerMockResult_.Reset();
    jsInteractionOperation->SearchElementInfoByAccessibilityId(
        elementId, requestId,
        operatorCallback, mode);
    EXPECT_EQ(operatorCallback.mockInfos_.size(),
        ohAccessibilityProvider->providerMockResult_.elementInfosList_.size());
    EXPECT_EQ(operatorCallback.mockRequestId, requestId);
}

/**
 * @tc.name: JsThirdProviderInteractionOperationTest003
 * @tc.desc: earchElementInfosByText
 * @tc.type: FUNC
 */
HWTEST_F(JsThirdProviderInteractionOperationTest, JsThirdProviderInteractionOperationTest003, TestSize.Level1)
{
    auto ohAccessibilityProvider
        = AceType::MakeRefPtr<MockOhAccessibilityProvider>();
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    auto context = NG::PipelineContext::GetCurrentContext();
    jsAccessibilityManager->SetPipelineContext(context);
    jsAccessibilityManager->Register(true);

    auto jsInteractionOperation = AceType::MakeRefPtr<Framework::JsThirdProviderInteractionOperation>(
        ohAccessibilityProvider, jsAccessibilityManager, frameNode);
    jsInteractionOperation->SetBelongTreeId(0);

    int64_t elementId = -1;
    int32_t requestId = 2;
    std::string& text = TEST_CONTENT_STR;
    MockAccessibilityElementOperatorCallback operatorCallback;

    // 1 provider abnormal, callback should receive same request id and empty infos
    ohAccessibilityProvider->SetInjectResult(-1);
    jsInteractionOperation->SearchElementInfosByText(
        elementId, text, requestId, operatorCallback);

    EXPECT_EQ(operatorCallback.mockRequestId, requestId);

    // 2 provider normal,callback should receive same request id and same infos as provider
    ohAccessibilityProvider->providerMockResult_.Reset();
    jsInteractionOperation->SearchElementInfosByText(
        elementId, text, requestId, operatorCallback);
    EXPECT_EQ(operatorCallback.mockInfos_.size(),
        ohAccessibilityProvider->providerMockResult_.elementInfosList_.size());
    EXPECT_EQ(operatorCallback.mockRequestId, requestId);
}

/**
 * @tc.name: JsThirdProviderInteractionOperationTest004
 * @tc.desc: FindFocusedElementInfo
 * @tc.type: FUNC
 */
HWTEST_F(JsThirdProviderInteractionOperationTest, JsThirdProviderInteractionOperationTest004, TestSize.Level1)
{
    auto ohAccessibilityProvider
        = AceType::MakeRefPtr<MockOhAccessibilityProvider>();
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    auto context = NG::PipelineContext::GetCurrentContext();
    jsAccessibilityManager->SetPipelineContext(context);
    jsAccessibilityManager->Register(true);

    auto jsInteractionOperation = AceType::MakeRefPtr<Framework::JsThirdProviderInteractionOperation>(
        ohAccessibilityProvider, jsAccessibilityManager, frameNode);
    jsInteractionOperation->SetBelongTreeId(0);

    int64_t elementId = -1;
    int32_t requestId = 2;
    int32_t focusType = 3;
    MockAccessibilityElementOperatorCallback operatorCallback;

    // 1 provider abnormal, callback should receive same request id and empty info
    ohAccessibilityProvider->SetInjectResult(-1);
    jsInteractionOperation->FindFocusedElementInfo(
        elementId, focusType, requestId, operatorCallback);

    EXPECT_EQ(operatorCallback.mockInfo_.GetAccessibilityId(), -1);
    EXPECT_EQ(operatorCallback.mockRequestId, requestId);

    // 2 provider normal,callback should receive same request id and same info as provider
    ohAccessibilityProvider->providerMockResult_.Reset();
    jsInteractionOperation->FindFocusedElementInfo(
        elementId, focusType, requestId, operatorCallback);
    EXPECT_EQ(operatorCallback.mockInfo_.GetAccessibilityId(),
        ohAccessibilityProvider->providerMockResult_.focusElementInfo_.GetElementId());
    EXPECT_EQ(operatorCallback.mockRequestId, requestId);
}

/**
 * @tc.name: JsThirdProviderInteractionOperationTest005
 * @tc.desc: FocusMoveSearch
 * @tc.type: FUNC
 */
HWTEST_F(JsThirdProviderInteractionOperationTest, JsThirdProviderInteractionOperationTest005, TestSize.Level1)
{
    auto ohAccessibilityProvider
        = AceType::MakeRefPtr<MockOhAccessibilityProvider>();
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    auto context = NG::PipelineContext::GetCurrentContext();
    jsAccessibilityManager->SetPipelineContext(context);
    jsAccessibilityManager->Register(true);

    auto jsInteractionOperation = AceType::MakeRefPtr<Framework::JsThirdProviderInteractionOperation>(
        ohAccessibilityProvider, jsAccessibilityManager, frameNode);
    jsInteractionOperation->SetBelongTreeId(0);

    int64_t elementId = -1;
    int32_t requestId = 2;
    int32_t direction = 3;
    MockAccessibilityElementOperatorCallback operatorCallback;

    // 1 provider abnormal, callback should receive same request id and empty info
    ohAccessibilityProvider->SetInjectResult(-1);
    jsInteractionOperation->FocusMoveSearch(
        elementId, direction, requestId, operatorCallback);
    EXPECT_EQ(operatorCallback.mockInfo_.GetAccessibilityId(), -1);
    EXPECT_EQ(operatorCallback.mockRequestId, requestId);

    // 2 provider normal,callback should receive same request id and same info as provider
    ohAccessibilityProvider->providerMockResult_.Reset();
    jsInteractionOperation->FocusMoveSearch(
        elementId, direction, requestId, operatorCallback);
    EXPECT_EQ(operatorCallback.mockInfo_.GetAccessibilityId(),
        ohAccessibilityProvider->providerMockResult_.nextFocusElementInfo_.GetElementId());
    EXPECT_EQ(operatorCallback.mockRequestId, requestId);
}

/**
 * @tc.name: JsThirdProviderInteractionOperationTest006
 * @tc.desc: ExecuteAction
 * @tc.type: FUNC
 */
HWTEST_F(JsThirdProviderInteractionOperationTest, JsThirdProviderInteractionOperationTest006, TestSize.Level1)
{
    auto ohAccessibilityProvider
        = AceType::MakeRefPtr<MockOhAccessibilityProvider>();
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    auto context = NG::PipelineContext::GetCurrentContext();
    jsAccessibilityManager->SetPipelineContext(context);
    jsAccessibilityManager->Register(true);

    auto jsInteractionOperation = AceType::MakeRefPtr<Framework::JsThirdProviderInteractionOperation>(
        ohAccessibilityProvider, jsAccessibilityManager, frameNode);
    jsInteractionOperation->SetBelongTreeId(0);
    int64_t elementId = 0;
    int32_t requestId = 2;
    int32_t action = -1;
    std::map<std::string, std::string> actionArguments =
        ohAccessibilityProvider->providerMockResult_.originActionArguments_;

    MockAccessibilityElementOperatorCallback operatorCallback;

    // 1 FindAccessibilityNode abnormal, callback should receive same request id and false
    ohAccessibilityProvider->SetInjectResult(-1);
    operatorCallback.mockSucceeded_ = true;
    jsInteractionOperation->ExecuteAction(
        elementId, action, actionArguments, requestId, operatorCallback);
    EXPECT_EQ(operatorCallback.mockSucceeded_, false);
    EXPECT_EQ(operatorCallback.mockRequestId, requestId);

    // 2 ExecuteAccessibilityAction abnormal, callback should receive same request id and false
    ohAccessibilityProvider->providerMockResult_.Reset();
    ohAccessibilityProvider->SetInjectActionResult(-1);
    operatorCallback.mockSucceeded_ = true;
    jsInteractionOperation->ExecuteAction(
        elementId, action, actionArguments, requestId, operatorCallback);
    EXPECT_EQ(operatorCallback.mockSucceeded_, false);
    EXPECT_EQ(operatorCallback.mockRequestId, requestId);

    // 3 ExecuteAccessibilityAction normal, callback should receive same request id and true
    ohAccessibilityProvider->providerMockResult_.Reset();
    jsInteractionOperation->ExecuteAction(
        elementId, action, actionArguments, requestId, operatorCallback);
    EXPECT_EQ(operatorCallback.mockSucceeded_, true);
    EXPECT_EQ(operatorCallback.mockRequestId, requestId);
}

/**
 * @tc.name: JsThirdProviderInteractionOperationTest007
 * @tc.desc: GetCursorPosition
 * @tc.type: FUNC
 */
HWTEST_F(JsThirdProviderInteractionOperationTest, JsThirdProviderInteractionOperationTest007, TestSize.Level1)
{
    auto ohAccessibilityProvider
        = AceType::MakeRefPtr<MockOhAccessibilityProvider>();
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    auto context = NG::PipelineContext::GetCurrentContext();
    jsAccessibilityManager->SetPipelineContext(context);
    jsAccessibilityManager->Register(true);

    auto jsInteractionOperation = AceType::MakeRefPtr<Framework::JsThirdProviderInteractionOperation>(
        ohAccessibilityProvider, jsAccessibilityManager, frameNode);
    jsInteractionOperation->SetBelongTreeId(0);

    int64_t elementId = -1;
    int32_t requestId = 2;
    MockAccessibilityElementOperatorCallback operatorCallback;

    // 1 provider abnormal, callback should receive same request id and CursorPosition default
    ohAccessibilityProvider->SetInjectResult(-1);
    jsInteractionOperation->GetCursorPosition(
        elementId, requestId, operatorCallback);
    EXPECT_EQ(operatorCallback.mockCursorPosition_, -1);
    EXPECT_EQ(operatorCallback.mockRequestId, requestId);

    // 2 provider normal,callback should receive same request id and same CursorPosition as provider
    ohAccessibilityProvider->providerMockResult_.Reset();
    jsInteractionOperation->GetCursorPosition(
        elementId, requestId, operatorCallback);
    EXPECT_EQ(operatorCallback.mockCursorPosition_, SPECIAL_CURSOR_POSTION);
    EXPECT_EQ(operatorCallback.mockRequestId, requestId);
}

/**
 * @tc.name: JsThirdProviderInteractionOperationTest008
 * @tc.desc: GetCursorPosition
 * @tc.type: FUNC
 */
HWTEST_F(JsThirdProviderInteractionOperationTest, JsThirdProviderInteractionOperationTest008, TestSize.Level1)
{
    auto ohAccessibilityProvider
        = AceType::MakeRefPtr<MockOhAccessibilityProvider>();
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    auto context = NG::PipelineContext::GetCurrentContext();
    jsAccessibilityManager->SetPipelineContext(context);
    jsAccessibilityManager->Register(true);

    auto jsInteractionOperation = AceType::MakeRefPtr<Framework::JsThirdProviderInteractionOperation>(
        ohAccessibilityProvider, jsAccessibilityManager, frameNode);
    jsInteractionOperation->SetBelongTreeId(0);

    ArkUI_AccessibilityEventInfo event;

    event.SetEventType(ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_ACCESSIBILITY_FOCUSED);
    event.SetPageId(1);
    int32_t requestFocusId = 0;
    event.SetRequestFocusId(requestFocusId);
    ArkUI_AccessibilityElementInfo elementInfo;
    event.SetElementInfo(&elementInfo);
    std::string textAnnouncedForAccessibility = "textAnnouncedForAccessibility";
    event.SetTextAnnouncedForAccessibility(textAnnouncedForAccessibility);

    g_mockErrorCode = -1;

    auto callback = [](int32_t errorCode) { g_mockErrorCode = errorCode; };

    // 1 send event  and callback receive 0
    jsInteractionOperation->SendAccessibilityAsyncEvent(
        event, callback);

    EXPECT_EQ(g_mockErrorCode, 0);
}

/**
 * @tc.name: JsThirdProviderInteractionOperationTest009
 * @tc.desc: element info transform by host node's info
 * @tc.type: FUNC
 */
HWTEST_F(JsThirdProviderInteractionOperationTest, JsThirdProviderInteractionOperationTest009, TestSize.Level1)
{
    auto ohAccessibilityProvider
        = AceType::MakeRefPtr<MockOhAccessibilityProvider>();
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    auto context = NG::PipelineContext::GetCurrentContext();
    jsAccessibilityManager->SetPipelineContext(context);
    jsAccessibilityManager->Register(true);

    auto jsInteractionOperation = AceType::MakeRefPtr<Framework::JsThirdProviderInteractionOperation>(
        ohAccessibilityProvider, jsAccessibilityManager, frameNode);

    int32_t treeId = 3;
    jsInteractionOperation->SetBelongTreeId(treeId);
    int32_t pageId = 4;
    frameNode->SetHostPageId(pageId);
    int32_t windowId = 5;
    context->SetRealHostWindowId(windowId);
    std::string bundleName = "com.example.myapplication";
    AceApplicationInfo::GetInstance().SetPackageName(bundleName);

    int64_t elementId = -1;
    int32_t requestId = 2;
    int32_t mode = 0;

    MockAccessibilityElementOperatorCallback operatorCallback;

    // 1 provider normal,callback should receive same request id and info's detail is transformed by host node's detail
    ohAccessibilityProvider->providerMockResult_.Reset();
    jsInteractionOperation->SearchElementInfoByAccessibilityId(
        elementId, requestId,
        operatorCallback, mode);
    EXPECT_EQ(operatorCallback.mockRequestId, requestId);
    EXPECT_EQ(operatorCallback.mockInfos_.size(),
        ohAccessibilityProvider->providerMockResult_.elementInfosList_.size());

    std::vector<Accessibility::AccessibilityElementInfo> mockInfosVector;
    for (Accessibility::AccessibilityElementInfo &elementInfo : operatorCallback.mockInfos_) {
        mockInfosVector.push_back(elementInfo);
    }
    for (int32_t i = 0; i < operatorCallback.mockInfos_.size(); i++) {
        int64_t splitElementId = Accessibility::AccessibilityElementInfo::UNDEFINED_ACCESSIBILITY_ID;
        int32_t splitTreeId = Accessibility::AccessibilityElementInfo::UNDEFINED_TREE_ID;

        Accessibility::AccessibilitySystemAbilityClient::GetTreeIdAndElementIdBySplitElementId(
             mockInfosVector[i].GetAccessibilityId(), splitElementId, splitTreeId);
        EXPECT_EQ(splitTreeId, treeId);
        EXPECT_EQ(splitElementId,
            ohAccessibilityProvider->providerMockResult_.elementInfosList_[i].GetElementId());
        EXPECT_EQ(mockInfosVector[i].GetBelongTreeId(), treeId);
        EXPECT_EQ(mockInfosVector[i].GetPageId(), pageId);
        EXPECT_EQ(mockInfosVector[i].GetWindowId(), windowId);
        EXPECT_EQ(mockInfosVector[i].GetParentWindowId(), windowId);
        EXPECT_EQ(mockInfosVector[i].GetBundleName(), bundleName);
    }
}

/**
 * @tc.name: JsThirdProviderInteractionOperationTest010
 * @tc.desc: SendAccessibilityAsyncEventForThird
 * @tc.type: FUNC
 */
HWTEST_F(JsThirdProviderInteractionOperationTest, JsThirdProviderInteractionOperationTest010, TestSize.Level1)
{
    auto ohAccessibilityProvider
        = AceType::MakeRefPtr<MockOhAccessibilityProvider>();
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    auto context = NG::PipelineContext::GetCurrentContext();
    jsAccessibilityManager->SetPipelineContext(context);
    jsAccessibilityManager->Register(true);

    auto jsInteractionOperation = AceType::MakeRefPtr<Framework::JsThirdProviderInteractionOperation>(
        ohAccessibilityProvider, jsAccessibilityManager, frameNode);
    jsInteractionOperation->SetBelongTreeId(0);

    int32_t ret = 0;

    int64_t thirdElementId = 1;
    Accessibility::EventType eventType = Accessibility::EventType::TYPE_VIEW_ACCESSIBILITY_FOCUSED_EVENT;

    // 1 provider abnormal, return -1
    ohAccessibilityProvider->SetInjectResult(-1);
    ret = jsInteractionOperation->SendAccessibilityAsyncEventForThird(
        thirdElementId, eventType);
    EXPECT_EQ(ret, -1);
    // 2 provider normal ; TBM check  send  client 's event is right
    ohAccessibilityProvider->providerMockResult_.Reset();
    ret = jsInteractionOperation->SendAccessibilityAsyncEventForThird(
        thirdElementId, eventType);
    EXPECT_EQ(ret, 0);
}

/**
 * @tc.name: JsThirdProviderInteractionOperationTest011
 * @tc.desc: HandleEventByFramework ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_FOCUS_NODE_UPDATE
 * @tc.type: FUNC
 */
HWTEST_F(JsThirdProviderInteractionOperationTest, JsThirdProviderInteractionOperationTest011, TestSize.Level1)
{
    auto ohAccessibilityProvider
        = AceType::MakeRefPtr<MockOhAccessibilityProvider>();
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    auto context = NG::PipelineContext::GetCurrentContext();
    jsAccessibilityManager->SetPipelineContext(context);
    jsAccessibilityManager->Register(true);

    auto jsInteractionOperation = AceType::MakeRefPtr<Framework::JsThirdProviderInteractionOperation>(
        ohAccessibilityProvider, jsAccessibilityManager, frameNode);
    jsInteractionOperation->SetBelongTreeId(0);

    ArkUI_AccessibilityEventInfo event;

    event.SetEventType(ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_FOCUS_NODE_UPDATE);
    event.SetPageId(1);
    int32_t requestFocusId = 0;
    event.SetRequestFocusId(requestFocusId);
    ArkUI_AccessibilityElementInfo elementInfo;
    event.SetElementInfo(&elementInfo);
    std::string textAnnouncedForAccessibility = "textAnnouncedForAccessibility";
    event.SetTextAnnouncedForAccessibility(textAnnouncedForAccessibility);

    g_mockErrorCode = -1;

    auto callback = [](int32_t errorCode) { g_mockErrorCode = errorCode; };

    // TBM check not send event to client
    jsInteractionOperation->SendAccessibilityAsyncEvent(
        event, callback);

    EXPECT_EQ(g_mockErrorCode, 0);
}

/**
 * @tc.name: FrameNodeAccessibilityVisible01
 * @tc.desc: Test the function accessibilityVisible
 * @tc.type: FUNC
 */
HWTEST_F(JsThirdProviderInteractionOperationTest, FrameNodeAccessibilityVisible01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("page", 1, AceType::MakeRefPtr<PagePattern>(nullptr), true);
    EXPECT_NE(frameNode->pattern_, nullptr);
    frameNode->isActive_ = false;
    auto pattern = frameNode->GetPattern<PagePattern>();
    pattern->isOnShow_ = true;
    auto pipeline = frameNode->GetContext();
    auto overlayManager = pipeline->GetOverlayManager();

    /**
     * @tc.steps: step2. Bind keyboard.
     */
    auto keyboardThd = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    overlayManager->BindKeyboardWithNode(keyboardThd, frameNode->GetId());
    overlayManager->UpdateCustomKeyboardPosition();
    overlayManager->AvoidCustomKeyboard(1, 1.0);

    /**
     * @tc.steps: step3. create childNode.
     */
    auto childNode = FrameNode::CreateFrameNode(
    "child", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    auto nodeGeometry = frameNode->GetGeometryNode();
    NG::RectF testRect = { 10.0f, nodeGeometry->GetFrameRect().Height() - 10.0f, 10.0f, 10.0f };
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    layoutProperty->SetLayoutRect(testRect);
    childNode->SetLayoutProperty(layoutProperty);
    frameNode->AddChild(childNode);

    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    auto context = NG::PipelineContext::GetCurrentContext();
    jsAccessibilityManager->SetPipelineContext(context);
    jsAccessibilityManager->Register(true);
    RefPtr<NG::PipelineContext> ngPipeline;
    ngPipeline = AceType::DynamicCast<NG::PipelineContext>(pipeline);
    std::list<AccessibilityElementInfo> extensionElementInfos;
    jsAccessibilityManager->SearchElementInfoByAccessibilityIdNG(
        childNode->GetAccessibilityId(), 1, extensionElementInfos, ngPipeline, 1);
    for (auto& extensionElementInfo : extensionElementInfos) {
        if (childNode->GetAccessibilityId() == extensionElementInfo.GetAccessibilityId()) {
            EXPECT_FALSE(childNode->GetAccessibilityVisible());
        }
    }

    /**
     * @tc.steps: step4. close Keyboard.
     */
    overlayManager->CloseKeyboard(frameNode->GetId());
}
} // namespace OHOS::Ace::NG
