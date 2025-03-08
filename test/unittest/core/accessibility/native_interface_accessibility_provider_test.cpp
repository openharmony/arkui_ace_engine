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

#include "frameworks/core/accessibility/accessibility_node.h"
#include "frameworks/core/accessibility/accessibility_utils.h"
#include "frameworks/core/accessibility/native_interface_accessibility_provider.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
class MockOhAccessibilityProvider : public AccessibilityProvider {
    DECLARE_ACE_TYPE(MockOhAccessibilityProvider, AccessibilityProvider);
public:
    MockOhAccessibilityProvider() = default;
    int32_t FindAccessibilityNodeInfosById(
        const int64_t elementId, const int32_t mode, const int32_t requestId,
        std::vector<ArkUI_AccessibilityElementInfo>& infos) override
    {
        return 0;
    }
    int32_t FindAccessibilityNodeInfosByText(
        const int64_t elementId, std::string text, const int32_t requestId,
        std::vector<ArkUI_AccessibilityElementInfo>& infos) override
    {
        return 0;
    }
    int32_t FindFocusedAccessibilityNode(
        const int64_t elementId, int32_t focusType, const int32_t requestId,
        ArkUI_AccessibilityElementInfo& elementInfo) override
    {
        return 0;
    }
    int32_t FindNextFocusAccessibilityNode(
        const int64_t elementId, int32_t direction, const int32_t requestId,
        ArkUI_AccessibilityElementInfo& elementInfo) override
    {
        return 0;
    }
    int32_t ExecuteAccessibilityAction(
        const int64_t elementId, int32_t action, const int32_t requestId,
        const std::map<std::string, std::string>& actionArguments) override
    {
        return 0;
    }
    int32_t ClearFocusedAccessibilityNode() override
    {
        return 0;
    }
    int32_t GetAccessibilityNodeCursorPosition(
        const int64_t elementId,
        const int32_t requestId,
        int32_t &cursorPosition) override
    {
        return 0;
    }
    int32_t SendAccessibilityAsyncEvent(
        const ArkUI_AccessibilityEventInfo& accessibilityEvent,
        void (*callback)(int32_t errorCode)) override
    {
        GTEST_LOG_(INFO) << "SendAccessibilityAsyncEvent";
        return 0;
    }
    void SendThirdAccessibilityProvider(
        const std::weak_ptr<ThirdAccessibilityManager>& thirdAccessibilityManager)
        override {}
};
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
namespace {
std::string TEST_CONTENT_STR = "testForFindByText";
constexpr const char* INSTANCE_ID = "fake_instance_id";
constexpr int32_t MAX_TEST_PARAMETER = 20;
constexpr int32_t MAX_TEST_ELEMENT_COUNT = 10;
constexpr int32_t SEND_EVENT_FAILED = -1;
constexpr int32_t SEND_EVENT_SUCCESS = 0;
constexpr int32_t TEST_PARAMETER_OFFSET1 = 1;
constexpr int32_t TEST_PARAMETER_OFFSET2 = 2;
constexpr int32_t TEST_PARAMETER_OFFSET3 = 3;

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
            mode_ = ARKUI_ACCESSIBILITY_NATIVE_SEARCH_MODE_PREFETCH_CURRENT;
            requestId_ = 0;
            focusType_ = ARKUI_ACCESSIBILITY_NATIVE_FOCUS_TYPE_INVALID;
            direction_ = ARKUI_ACCESSIBILITY_NATIVE_DIRECTION_INVALID;
            action_ = ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_INVALID;
            receiveClear_ = false;
            errorCode_ = 0;
            instanceId_ = "";
        }

    public:
        int64_t elementId_;
        ArkUI_AccessibilitySearchMode mode_;
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
        std::string instanceId_;
};

ProviderMockResult g_providerMockResult;

int32_t MockFindAccessibilityNodeInfosById(
    int64_t elementId,
    ArkUI_AccessibilitySearchMode mode,
    int32_t requestId,
    ArkUI_AccessibilityElementInfoList* elementList)
{
    g_providerMockResult.elementId_ = elementId;
    g_providerMockResult.mode_ = mode;
    g_providerMockResult.requestId_ = requestId;

    ArkUI_AccessibilityElementInfo* tempElementInfo;
    for (const auto &elementInfo: g_providerMockResult.elementInfosList_) {
        tempElementInfo = elementList->AddAndGetElementInfo();
        tempElementInfo->SetElementId(elementInfo.GetElementId());
    }

    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t MockFindAccessibilityNodeInfosByIdWithInstance(
    const char* instanceId,
    int64_t elementId,
    ArkUI_AccessibilitySearchMode mode,
    int32_t requestId,
    ArkUI_AccessibilityElementInfoList* elementList)
{
    g_providerMockResult.instanceId_ = instanceId;
    return MockFindAccessibilityNodeInfosById(elementId, mode, requestId, elementList);
}

int32_t MockFindAccessibilityNodeInfosByIdCopyFail(
    int64_t elementId,
    ArkUI_AccessibilitySearchMode mode,
    int32_t requestId,
    ArkUI_AccessibilityElementInfoList* elementList)
{
    g_providerMockResult.elementId_ = elementId;
    g_providerMockResult.mode_ = mode;
    g_providerMockResult.requestId_ = requestId;
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t MockFindAccessibilityNodeInfosByText(
    int64_t elementId,
    const char* text,
    int32_t requestId,
    ArkUI_AccessibilityElementInfoList* elementList)
{
    g_providerMockResult.elementId_ = elementId;
    g_providerMockResult.requestId_ = requestId;

    ArkUI_AccessibilityElementInfo* tempElementInfo;
    std::string textStr(text);
    for (const auto &elementInfo: g_providerMockResult.elementInfosList_) {
        if (elementInfo.GetContents() == textStr) {
            tempElementInfo = elementList->AddAndGetElementInfo();
            tempElementInfo->SetElementId(elementInfo.GetElementId());
        }
    }
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t MockFindAccessibilityNodeInfosByTextWithInstanceId(
    const char* instanceId,
    int64_t elementId,
    const char* text,
    int32_t requestId,
    ArkUI_AccessibilityElementInfoList* elementList)
{
    g_providerMockResult.instanceId_ = instanceId;
    return MockFindAccessibilityNodeInfosByText(elementId, text, requestId, elementList);
}

int32_t MockFindAccessibilityNodeInfosByTextCopyFail(
    int64_t elementId,
    const char* text,
    int32_t requestId,
    ArkUI_AccessibilityElementInfoList* elementList)
{
    g_providerMockResult.elementId_ = elementId;
    g_providerMockResult.requestId_ = requestId;
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t MockFindFocusedAccessibilityNode(
    int64_t elementId,
    ArkUI_AccessibilityFocusType focusType,
    int32_t requestId,
    ArkUI_AccessibilityElementInfo* elementInfo)
{
    g_providerMockResult.elementId_ = elementId;
    g_providerMockResult.focusType_ = focusType;
    g_providerMockResult.requestId_ = requestId;
    elementInfo->SetElementId(
        g_providerMockResult.focusElementInfo_.GetElementId());
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t MockFindFocusedAccessibilityNodeWithInstance(
    const char* instanceId,
    int64_t elementId,
    ArkUI_AccessibilityFocusType focusType,
    int32_t requestId,
    ArkUI_AccessibilityElementInfo* elementInfo)
{
    g_providerMockResult.instanceId_ = instanceId;
    return MockFindFocusedAccessibilityNode(elementId, focusType, requestId, elementInfo);
}

int32_t MockFindNextFocusAccessibilityNode(
    int64_t elementId,
    ArkUI_AccessibilityFocusMoveDirection direction,
    int32_t requestId,
    ArkUI_AccessibilityElementInfo* elementInfo)
{
    g_providerMockResult.elementId_ = elementId;
    g_providerMockResult.direction_ = direction;
    g_providerMockResult.requestId_ = requestId;
    elementInfo->SetElementId(
        g_providerMockResult.nextFocusElementInfo_.GetElementId());
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t MockFindNextFocusAccessibilityNodeWithInstance(
    const char* instanceId,
    int64_t elementId,
    ArkUI_AccessibilityFocusMoveDirection direction,
    int32_t requestId,
    ArkUI_AccessibilityElementInfo* elementInfo)
{
    g_providerMockResult.instanceId_ = instanceId;
    return MockFindNextFocusAccessibilityNode(elementId, direction, requestId, elementInfo);
}

int32_t MockExecuteAccessibilityAction(
    int64_t elementId,
    ArkUI_Accessibility_ActionType action,
    ArkUI_AccessibilityActionArguments *actionArguments,
    int32_t requestId)
{
    g_providerMockResult.action_ = action;
    g_providerMockResult.requestId_ = requestId;

    g_providerMockResult.resultActionArguments_.clear();
    for (auto &pair: g_providerMockResult.originActionArguments_) {
        auto value = actionArguments->FindValueByKey(pair.first.c_str());
        if (value) {
            std::string textStr(value);
            g_providerMockResult.resultActionArguments_.emplace(
                pair.first, textStr);
        }
    }

    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t MockExecuteAccessibilityActionWithInstance(
    const char* instanceId,
    int64_t elementId,
    ArkUI_Accessibility_ActionType action,
    ArkUI_AccessibilityActionArguments *actionArguments,
    int32_t requestId)
{
    g_providerMockResult.instanceId_ = instanceId;
    return MockExecuteAccessibilityAction(elementId, action, actionArguments, requestId);
}

int32_t MockClearFocusedFocusAccessibilityNode()
{
    g_providerMockResult.receiveClear_ = true;
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t MockClearFocusedFocusAccessibilityNodeWithInstance(const char* instanceId)
{
    g_providerMockResult.instanceId_ = instanceId;
    return MockClearFocusedFocusAccessibilityNode();
}

int32_t MockGetAccessibilityNodeCursorPosition(
    int64_t elementId,
    int32_t requestId,
    int32_t* index)
{
    g_providerMockResult.elementId_ = elementId;
    g_providerMockResult.requestId_ = requestId;
    *index = g_providerMockResult.cursorPosition_;
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t MockGetAccessibilityNodeCursorPositionWithInstance(
    const char* instanceId,
    int64_t elementId,
    int32_t requestId,
    int32_t* index)
{
    g_providerMockResult.instanceId_ = instanceId;
    return MockGetAccessibilityNodeCursorPosition(elementId, requestId, index);
}

void MockRegisterCallback(bool isRegistered)
{
    g_providerMockResult.registerResult_ = isRegistered;
}

void MockEventCallBack(int32_t errorCode)
{
    g_providerMockResult.errorCode_ = errorCode;
}

void BuildMockCallBack(ArkUI_AccessibilityProviderCallbacks &callBacks)
{
    // register success
    callBacks.findAccessibilityNodeInfosById =
        MockFindAccessibilityNodeInfosById;
    callBacks.findAccessibilityNodeInfosByText =
        MockFindAccessibilityNodeInfosByText;
    callBacks.findFocusedAccessibilityNode =
        MockFindFocusedAccessibilityNode;
    callBacks.findNextFocusAccessibilityNode =
        MockFindNextFocusAccessibilityNode;
    callBacks.executeAccessibilityAction =
        MockExecuteAccessibilityAction;
    callBacks.clearFocusedFocusAccessibilityNode =
        MockClearFocusedFocusAccessibilityNode;
    callBacks.getAccessibilityNodeCursorPosition =
        MockGetAccessibilityNodeCursorPosition;
}

void BuildMockCallBackWithInstance(ArkUI_AccessibilityProviderCallbacksWithInstance &callBacks)
{
    // register success
    callBacks.findAccessibilityNodeInfosById = MockFindAccessibilityNodeInfosByIdWithInstance;
    callBacks.findAccessibilityNodeInfosByText = MockFindAccessibilityNodeInfosByTextWithInstanceId;
    callBacks.findFocusedAccessibilityNode = MockFindFocusedAccessibilityNodeWithInstance;
    callBacks.findNextFocusAccessibilityNode = MockFindNextFocusAccessibilityNodeWithInstance;
    callBacks.executeAccessibilityAction = MockExecuteAccessibilityActionWithInstance;
    callBacks.clearFocusedFocusAccessibilityNode = MockClearFocusedFocusAccessibilityNodeWithInstance;
    callBacks.getAccessibilityNodeCursorPosition = MockGetAccessibilityNodeCursorPositionWithInstance;
}
} // namespace

class AccessibilityProviderTestNg : public testing::Test {
public:
    static void SetUpTestCase()
    {
        g_providerMockResult.Reset();
    }
    static void TearDownTestCase() {};
};


/**
 * @tc.name: accessibilityTest001
 * @tc.desc: AccessibilityProviderRegisterCallback abnormal
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityProviderTestNg, AccessibilityProviderTest001, TestSize.Level1)
{
    g_providerMockResult.Reset();
    ArkUI_AccessibilityProvider accessibilityProvider;
    int32_t ret;
    ArkUI_AccessibilityProviderCallbacks callBacks;
    // callback null
    ret = accessibilityProvider.AccessibilityProviderRegisterCallback(nullptr);
    EXPECT_EQ(ret, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    EXPECT_EQ(accessibilityProvider.IsRegister(), false);
    // findAccessibilityNodeInfosById null
    ret = accessibilityProvider.AccessibilityProviderRegisterCallback(&callBacks);
    EXPECT_EQ(ret, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    EXPECT_EQ(accessibilityProvider.IsRegister(), false);
    // findAccessibilityNodeInfosByText null
    callBacks.findAccessibilityNodeInfosById = MockFindAccessibilityNodeInfosById;
    ret = accessibilityProvider.AccessibilityProviderRegisterCallback(&callBacks);
    EXPECT_EQ(ret, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    EXPECT_EQ(accessibilityProvider.IsRegister(), false);
    // findFocusedAccessibilityNode null
    callBacks.findAccessibilityNodeInfosByText =
        MockFindAccessibilityNodeInfosByText;
    ret = accessibilityProvider.AccessibilityProviderRegisterCallback(&callBacks);
    EXPECT_EQ(ret, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    EXPECT_EQ(accessibilityProvider.IsRegister(), false);
    // findNextFocusAccessibilityNode null
    callBacks.findFocusedAccessibilityNode = MockFindFocusedAccessibilityNode;
    ret = accessibilityProvider.AccessibilityProviderRegisterCallback(&callBacks);
    EXPECT_EQ(ret, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    EXPECT_EQ(accessibilityProvider.IsRegister(), false);

    // executeAccessibilityAction null
    callBacks.findNextFocusAccessibilityNode = MockFindNextFocusAccessibilityNode;
    ret = accessibilityProvider.AccessibilityProviderRegisterCallback(&callBacks);
    EXPECT_EQ(ret, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    EXPECT_EQ(accessibilityProvider.IsRegister(), false);
    // clearFocusedFocusAccessibilityNode null
    callBacks.executeAccessibilityAction = MockExecuteAccessibilityAction;
    ret = accessibilityProvider.AccessibilityProviderRegisterCallback(&callBacks);
    EXPECT_EQ(ret, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    EXPECT_EQ(accessibilityProvider.IsRegister(), false);
    // getAccessibilityNodeCursorPosition null
    callBacks.clearFocusedFocusAccessibilityNode =
        MockClearFocusedFocusAccessibilityNode;
    ret = accessibilityProvider.AccessibilityProviderRegisterCallback(&callBacks);
    EXPECT_EQ(ret, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    EXPECT_EQ(accessibilityProvider.IsRegister(), false);
    callBacks.getAccessibilityNodeCursorPosition =
        MockGetAccessibilityNodeCursorPosition;
}

/**
 * @tc.name: accessibilityTest002
 * @tc.desc: AccessibilityProviderRegisterCallback abnormal
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityProviderTestNg, AccessibilityProviderTest002, TestSize.Level1)
{
    g_providerMockResult.Reset();
    ArkUI_AccessibilityProvider accessibilityProvider;
    int32_t ret;
    ArkUI_AccessibilityProviderCallbacks callBacks;
    accessibilityProvider.SetRegisterCallback(MockRegisterCallback);
    // register success
    BuildMockCallBack(callBacks);
    ret = accessibilityProvider.AccessibilityProviderRegisterCallback(&callBacks);
    EXPECT_EQ(ret, ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL);
    EXPECT_EQ(g_providerMockResult.registerResult_, true);
    EXPECT_EQ(accessibilityProvider.IsRegister(), true);

    // then register fail, call registercallback false
    callBacks.findAccessibilityNodeInfosById = nullptr;
    ret = accessibilityProvider.AccessibilityProviderRegisterCallback(&callBacks);
    EXPECT_EQ(ret, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    EXPECT_EQ(g_providerMockResult.registerResult_, false);
}

/**
 * @tc.name: accessibilityTest003
 * @tc.desc: FindAccessibilityNodeInfosById
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityProviderTestNg, AccessibilityProviderTest003, TestSize.Level1)
{
    g_providerMockResult.Reset();
    ArkUI_AccessibilityProvider accessibilityProvider;
    int32_t ret;
    ArkUI_AccessibilityProviderCallbacks callBacks;
    accessibilityProvider.SetRegisterCallback(MockRegisterCallback);

    auto now = std::chrono::system_clock::now();
    int32_t testParameter =
        std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch())
        .count();
    testParameter = testParameter % MAX_TEST_PARAMETER;
    int64_t elementId = testParameter;
    int32_t mode = testParameter + TEST_PARAMETER_OFFSET1;
    int32_t requestId = testParameter + TEST_PARAMETER_OFFSET2;
    std::vector<ArkUI_AccessibilityElementInfo> infos;

    // register fail
    ret = accessibilityProvider.FindAccessibilityNodeInfosById(
        elementId, mode, requestId, infos);
    EXPECT_EQ(ret, AccessibilityProviderOperatorErrorCode::NOT_REGISTERED);

    // register success
    BuildMockCallBack(callBacks);
    ret = accessibilityProvider.AccessibilityProviderRegisterCallback(&callBacks);
    EXPECT_EQ(ret, ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL);

    ret = accessibilityProvider.FindAccessibilityNodeInfosById(
        elementId, mode, requestId, infos);
    EXPECT_EQ(ret, ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL);
    EXPECT_EQ(g_providerMockResult.elementId_, elementId);
    EXPECT_EQ(g_providerMockResult.mode_, mode);
    EXPECT_EQ(g_providerMockResult.requestId_, requestId);
    // id equals to prepared ids
    for (int64_t i = 0; i < g_providerMockResult.elementInfosList_.size(); i++) {
        EXPECT_EQ(g_providerMockResult.elementInfosList_[i].GetElementId(),
            infos[i].GetElementId());
    }

    // copy fail
    ArkUI_AccessibilityProvider accessibilityProvider2;
    accessibilityProvider2.SetRegisterCallback(MockRegisterCallback);
    callBacks.findAccessibilityNodeInfosById =
        MockFindAccessibilityNodeInfosByIdCopyFail;
    ret = accessibilityProvider2.AccessibilityProviderRegisterCallback(&callBacks);
    EXPECT_EQ(ret, ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL);
    ret = accessibilityProvider2.FindAccessibilityNodeInfosById(
        elementId, mode, requestId, infos);
    EXPECT_EQ(ret, AccessibilityProviderOperatorErrorCode::COPY_FAILED);
}

/**
 * @tc.name: accessibilityTest004
 * @tc.desc: FindAccessibilityNodeInfosByText
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityProviderTestNg, AccessibilityProviderTest004, TestSize.Level1)
{
    g_providerMockResult.Reset();
    ArkUI_AccessibilityProvider accessibilityProvider;
    int32_t ret;
    ArkUI_AccessibilityProviderCallbacks callBacks;
    accessibilityProvider.SetRegisterCallback(MockRegisterCallback);

    auto now = std::chrono::system_clock::now();
    int32_t testParameter =
        std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch())
        .count();
    testParameter = testParameter % MAX_TEST_PARAMETER;
    int64_t elementId = testParameter;
    int32_t requestId = testParameter + TEST_PARAMETER_OFFSET1;
    std::vector<ArkUI_AccessibilityElementInfo> infos;
    std::string text = TEST_CONTENT_STR;

    // register fail
    ret = accessibilityProvider.FindAccessibilityNodeInfosByText(
        elementId, text, requestId, infos);
    EXPECT_EQ(ret, AccessibilityProviderOperatorErrorCode::NOT_REGISTERED);

    // register success
    BuildMockCallBack(callBacks);
    ret = accessibilityProvider.AccessibilityProviderRegisterCallback(&callBacks);
    EXPECT_EQ(ret, ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL);

    ret = accessibilityProvider.FindAccessibilityNodeInfosByText(
        elementId, text, requestId, infos);
    EXPECT_EQ(ret, ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL);
    EXPECT_EQ(g_providerMockResult.elementId_, elementId);
    EXPECT_EQ(g_providerMockResult.requestId_, requestId);
    // all elementInfo's text matched
    for (int64_t i = 0; i < g_providerMockResult.elementInfosList_.size(); i++) {
        EXPECT_EQ(g_providerMockResult.elementInfosList_[i].GetElementId(),
            infos[i].GetElementId());
    }

    // copy fail
    ArkUI_AccessibilityProvider accessibilityProvider2;
    accessibilityProvider2.SetRegisterCallback(MockRegisterCallback);
    callBacks.findAccessibilityNodeInfosByText =
        MockFindAccessibilityNodeInfosByTextCopyFail;
    ret = accessibilityProvider2.AccessibilityProviderRegisterCallback(&callBacks);
    EXPECT_EQ(ret, ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL);
    ret = accessibilityProvider2.FindAccessibilityNodeInfosByText(
        elementId, text, requestId, infos);
    EXPECT_EQ(ret, AccessibilityProviderOperatorErrorCode::COPY_FAILED);
}

/**
 * @tc.name: accessibilityTest005
 * @tc.desc: FindFocusedAccessibilityNode and FindNextFocusAccessibilityNode
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityProviderTestNg, AccessibilityProviderTest005, TestSize.Level1)
{
    g_providerMockResult.Reset();
    ArkUI_AccessibilityProvider accessibilityProvider;
    int32_t ret;
    ArkUI_AccessibilityProviderCallbacks callBacks;
    accessibilityProvider.SetRegisterCallback(MockRegisterCallback);

    auto now = std::chrono::system_clock::now();
    int32_t testParameter =
        std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch())
        .count();
    testParameter = testParameter % MAX_TEST_PARAMETER;
    int64_t elementId = testParameter;
    int32_t focusType = testParameter + TEST_PARAMETER_OFFSET1;
    int32_t requestId = testParameter + TEST_PARAMETER_OFFSET2;
    int32_t direction = testParameter + TEST_PARAMETER_OFFSET3;
    ArkUI_AccessibilityElementInfo elementInfo;

    // register fail
    ret = accessibilityProvider.FindFocusedAccessibilityNode(
        elementId, focusType, requestId, elementInfo);
    EXPECT_EQ(ret, AccessibilityProviderOperatorErrorCode::NOT_REGISTERED);
    ret = accessibilityProvider.FindNextFocusAccessibilityNode(
        elementId, direction, requestId, elementInfo);
    EXPECT_EQ(ret, AccessibilityProviderOperatorErrorCode::NOT_REGISTERED);


    // register success
    BuildMockCallBack(callBacks);
    ret = accessibilityProvider.AccessibilityProviderRegisterCallback(&callBacks);
    EXPECT_EQ(ret, ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL);

    ret = accessibilityProvider.FindFocusedAccessibilityNode(
        elementId, focusType, requestId, elementInfo);
    EXPECT_EQ(ret, ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL);
    EXPECT_EQ(g_providerMockResult.elementId_, elementId);
    EXPECT_EQ(g_providerMockResult.focusType_, focusType);
    EXPECT_EQ(g_providerMockResult.requestId_, requestId);
    EXPECT_EQ(g_providerMockResult.focusElementInfo_.GetElementId(),
        elementInfo.GetElementId());

    ret = accessibilityProvider.FindNextFocusAccessibilityNode(
        elementId, direction, requestId, elementInfo);
    EXPECT_EQ(ret, ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL);
    EXPECT_EQ(g_providerMockResult.elementId_, elementId);
    EXPECT_EQ(g_providerMockResult.direction_, direction);
    EXPECT_EQ(g_providerMockResult.requestId_, requestId);
    EXPECT_EQ(g_providerMockResult.nextFocusElementInfo_.GetElementId(),
        elementInfo.GetElementId());
}

/**
 * @tc.name: accessibilityTest006
 * @tc.desc: ExecuteAccessibilityAction
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityProviderTestNg, AccessibilityProviderTest006, TestSize.Level1)
{
    g_providerMockResult.Reset();
    ArkUI_AccessibilityProvider accessibilityProvider;
    int32_t ret;
    ArkUI_AccessibilityProviderCallbacks callBacks;
    accessibilityProvider.SetRegisterCallback(MockRegisterCallback);

    auto now = std::chrono::system_clock::now();
    int32_t testParameter =
        std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch())
        .count();
    testParameter = testParameter % MAX_TEST_PARAMETER;
    int64_t elementId = testParameter;
    int32_t action = testParameter + TEST_PARAMETER_OFFSET1;
    int32_t requestId = testParameter + TEST_PARAMETER_OFFSET2;
    std::map<std::string, std::string> actionArguments =
        g_providerMockResult.originActionArguments_;
    // register fail
    ret = accessibilityProvider.ExecuteAccessibilityAction(
        elementId, action, requestId, actionArguments);
    EXPECT_EQ(ret, AccessibilityProviderOperatorErrorCode::NOT_REGISTERED);

    // register success
    BuildMockCallBack(callBacks);
    ret = accessibilityProvider.AccessibilityProviderRegisterCallback(&callBacks);
    EXPECT_EQ(ret, ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL);

    ret = accessibilityProvider.ExecuteAccessibilityAction(
        elementId, action, requestId, actionArguments);
    EXPECT_EQ(ret, ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL);
    EXPECT_EQ(actionArguments, g_providerMockResult.resultActionArguments_);
}

/**
 * @tc.name: accessibilityTest007
 * @tc.desc: ClearFocusedAccessibilityNode
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityProviderTestNg, AccessibilityProviderTest007, TestSize.Level1)
{
    g_providerMockResult.Reset();
    ArkUI_AccessibilityProvider accessibilityProvider;
    int32_t ret;
    ArkUI_AccessibilityProviderCallbacks callBacks;
    accessibilityProvider.SetRegisterCallback(MockRegisterCallback);

    // register fail
    ret = accessibilityProvider.ClearFocusedAccessibilityNode();
    EXPECT_EQ(ret, AccessibilityProviderOperatorErrorCode::NOT_REGISTERED);

    // register success
    BuildMockCallBack(callBacks);
    ret = accessibilityProvider.AccessibilityProviderRegisterCallback(&callBacks);
    EXPECT_EQ(ret, ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL);

    ret = accessibilityProvider.ClearFocusedAccessibilityNode();
    EXPECT_EQ(ret, ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL);
    EXPECT_EQ(g_providerMockResult.receiveClear_, true);
}

/**
 * @tc.name: accessibilityTest008
 * @tc.desc: GetAccessibilityNodeCursorPosition
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityProviderTestNg, AccessibilityProviderTest008, TestSize.Level1)
{
    g_providerMockResult.Reset();
    ArkUI_AccessibilityProvider accessibilityProvider;
    int32_t ret;
    ArkUI_AccessibilityProviderCallbacks callBacks;
    accessibilityProvider.SetRegisterCallback(MockRegisterCallback);

    auto now = std::chrono::system_clock::now();
    int32_t testParameter =
        std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch())
        .count();
    testParameter = testParameter % MAX_TEST_PARAMETER;
    int64_t elementId = testParameter;
    int32_t requestId = testParameter + TEST_PARAMETER_OFFSET1;
    int32_t cursorPosition;
    std::map<std::string, std::string> actionArguments =
        g_providerMockResult.originActionArguments_;
    // register fail
    ret = accessibilityProvider.GetAccessibilityNodeCursorPosition(
        elementId, requestId, cursorPosition);
    EXPECT_EQ(ret, AccessibilityProviderOperatorErrorCode::NOT_REGISTERED);

    // register success
    BuildMockCallBack(callBacks);
    ret = accessibilityProvider.AccessibilityProviderRegisterCallback(&callBacks);
    EXPECT_EQ(ret, ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL);

    ret = accessibilityProvider.GetAccessibilityNodeCursorPosition(
        elementId, requestId, cursorPosition);
    EXPECT_EQ(ret, ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL);
    EXPECT_EQ(cursorPosition, g_providerMockResult.cursorPosition_);
}

/**
 * @tc.name: accessibilityTest009
 * @tc.desc: SendAccessibilityAsyncEvent
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityProviderTestNg, AccessibilityProviderTest009, TestSize.Level1)
{
    g_providerMockResult.Reset();
    ArkUI_AccessibilityProvider accessibilityProvider;
    int32_t ret;

    // 1.1 event null and callback null
    ret = accessibilityProvider.SendAccessibilityAsyncEvent(nullptr, nullptr);
    EXPECT_EQ(ret, SEND_EVENT_FAILED);

    // 1.2 event null and callback not null
    ret = accessibilityProvider.SendAccessibilityAsyncEvent(
        nullptr, MockEventCallBack);
    EXPECT_EQ(ret, SEND_EVENT_FAILED);
    EXPECT_EQ(g_providerMockResult.errorCode_, SEND_EVENT_FAILED);

    // 2.1 event not null and OH accessibilityProvider null and callback null
    ArkUI_AccessibilityEventInfo accessibilityEvent;
    ret = accessibilityProvider.SendAccessibilityAsyncEvent(
        &accessibilityEvent, nullptr);
    EXPECT_EQ(ret, SEND_EVENT_FAILED);
    // 2.2 event not null and  accessibilityProvider null and callback not null
    ret = accessibilityProvider.SendAccessibilityAsyncEvent(
        &accessibilityEvent, MockEventCallBack);
    EXPECT_EQ(ret, SEND_EVENT_FAILED);
    EXPECT_EQ(g_providerMockResult.errorCode_, SEND_EVENT_FAILED);


    // 3 event not null and  OH accessibilityProvider not null
    auto ohAccessibilityProvider
        = AceType::MakeRefPtr<MockOhAccessibilityProvider>();
    accessibilityProvider.SetInnerAccessibilityProvider(ohAccessibilityProvider);
    ret = accessibilityProvider.SendAccessibilityAsyncEvent(
        &accessibilityEvent, MockEventCallBack);
    EXPECT_EQ(ret, SEND_EVENT_SUCCESS);
}

/**
 * @tc.name: accessibilityTest010
 * @tc.desc: AccessibilityProviderRegisterCallbackWithInstance test
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityProviderTestNg, AccessibilityProviderTest010, TestSize.Level1)
{
    ArkUI_AccessibilityProvider accessibilityProvider;
    int32_t ret = 0;
    ArkUI_AccessibilityProviderCallbacksWithInstance callBacks;
    // callback null
    ret = accessibilityProvider.AccessibilityProviderRegisterCallback(nullptr);
    EXPECT_EQ(ret, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    EXPECT_EQ(accessibilityProvider.IsRegister(), false);
    // findAccessibilityNodeInfosById null
    ret = accessibilityProvider.AccessibilityProviderRegisterCallbackWithInstance(INSTANCE_ID, &callBacks);
    EXPECT_EQ(ret, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    EXPECT_EQ(accessibilityProvider.IsRegister(), false);
    // findAccessibilityNodeInfosByText null
    callBacks.findAccessibilityNodeInfosById = MockFindAccessibilityNodeInfosByIdWithInstance;
    ret = accessibilityProvider.AccessibilityProviderRegisterCallbackWithInstance(INSTANCE_ID, &callBacks);
    EXPECT_EQ(ret, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    EXPECT_EQ(accessibilityProvider.IsRegister(), false);
    // findFocusedAccessibilityNode null
    callBacks.findAccessibilityNodeInfosByText =MockFindAccessibilityNodeInfosByTextWithInstanceId;
    ret = accessibilityProvider.AccessibilityProviderRegisterCallbackWithInstance(INSTANCE_ID, &callBacks);
    EXPECT_EQ(ret, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    EXPECT_EQ(accessibilityProvider.IsRegister(), false);
    // findNextFocusAccessibilityNode null
    callBacks.findFocusedAccessibilityNode = MockFindFocusedAccessibilityNodeWithInstance;
    ret = accessibilityProvider.AccessibilityProviderRegisterCallbackWithInstance(INSTANCE_ID, &callBacks);
    EXPECT_EQ(ret, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    EXPECT_EQ(accessibilityProvider.IsRegister(), false);

    // executeAccessibilityAction null
    callBacks.findNextFocusAccessibilityNode = MockFindNextFocusAccessibilityNodeWithInstance;
    ret = accessibilityProvider.AccessibilityProviderRegisterCallbackWithInstance(INSTANCE_ID, &callBacks);
    EXPECT_EQ(ret, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    EXPECT_EQ(accessibilityProvider.IsRegister(), false);
    // clearFocusedFocusAccessibilityNode null
    callBacks.executeAccessibilityAction = MockExecuteAccessibilityActionWithInstance;
    ret = accessibilityProvider.AccessibilityProviderRegisterCallbackWithInstance(INSTANCE_ID, &callBacks);
    EXPECT_EQ(ret, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    EXPECT_EQ(accessibilityProvider.IsRegister(), false);
    // getAccessibilityNodeCursorPosition null
    callBacks.clearFocusedFocusAccessibilityNode = MockClearFocusedFocusAccessibilityNodeWithInstance;
    ret = accessibilityProvider.AccessibilityProviderRegisterCallbackWithInstance(INSTANCE_ID, &callBacks);
    EXPECT_EQ(ret, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    EXPECT_EQ(accessibilityProvider.IsRegister(), false);
    callBacks.getAccessibilityNodeCursorPosition = MockGetAccessibilityNodeCursorPositionWithInstance;
    ret = accessibilityProvider.AccessibilityProviderRegisterCallbackWithInstance(INSTANCE_ID, &callBacks);
    EXPECT_EQ(ret, ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL);
    EXPECT_EQ(accessibilityProvider.IsRegister(), true);
    EXPECT_EQ(g_providerMockResult.registerResult_, true);
}

/**
 * @tc.name: accessibilityTest011
 * @tc.desc: FindAccessibilityNodeInfosByIdWithInstance
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityProviderTestNg, AccessibilityProviderTest011, TestSize.Level1)
{
    ArkUI_AccessibilityProvider accessibilityProvider;
    int32_t ret;
    ArkUI_AccessibilityProviderCallbacks callBacks;
    ArkUI_AccessibilityProviderCallbacksWithInstance callBacksWithInstance;
    accessibilityProvider.SetRegisterCallback(MockRegisterCallback);

    auto now = std::chrono::system_clock::now();
    int32_t testParameter =
        std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch())
        .count();
    testParameter = testParameter % MAX_TEST_PARAMETER;
    int64_t elementId = testParameter;
    int32_t mode = testParameter + TEST_PARAMETER_OFFSET1;
    int32_t requestId = testParameter + TEST_PARAMETER_OFFSET2;
    std::vector<ArkUI_AccessibilityElementInfo> infos;

    // register fail
    ret = accessibilityProvider.FindAccessibilityNodeInfosById(
        elementId, mode, requestId, infos);
    EXPECT_EQ(ret, AccessibilityProviderOperatorErrorCode::NOT_REGISTERED);

    // register success
    BuildMockCallBack(callBacks);
    BuildMockCallBackWithInstance(callBacksWithInstance);
    
    ret = accessibilityProvider.AccessibilityProviderRegisterCallback(&callBacks);
    EXPECT_EQ(ret, ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL);
    ret = accessibilityProvider.AccessibilityProviderRegisterCallbackWithInstance(INSTANCE_ID, &callBacksWithInstance);
    EXPECT_EQ(ret, ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL);

    ret = accessibilityProvider.FindAccessibilityNodeInfosById(
        elementId, mode, requestId, infos);
    EXPECT_EQ(ret, ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL);
    EXPECT_EQ(g_providerMockResult.elementId_, elementId);
    EXPECT_EQ(g_providerMockResult.mode_, mode);
    EXPECT_EQ(g_providerMockResult.requestId_, requestId);
    EXPECT_EQ(g_providerMockResult.instanceId_, INSTANCE_ID);
}
} // namespace OHOS::Ace::NG
