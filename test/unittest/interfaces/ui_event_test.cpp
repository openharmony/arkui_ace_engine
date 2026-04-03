/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "ace_forward_compatibility.h"
#include "interfaces/inner_api/ace/ui_event.h"
#include "interfaces/inner_api/ace/ui_event_func.h"
#include "interfaces/inner_api/ace/ui_event_observer.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "core/components/popup/popup_theme.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace {
bool g_registerObserverCalled = false;
bool g_unregisterObserverCalled = false;
bool g_getNodePropertyCalled = false;
bool g_getTreeCalled = false;
bool g_getTreeAsyncCalled = false;
bool g_executeCommandCalled = false;
bool g_getComponentInfoCalled = false;

void MockRegisterUIEventObserver(const std::string&, const std::shared_ptr<UIEventObserver>&)
{
    g_registerObserverCalled = true;
}

void MockUnregisterUIEventObserver(const std::shared_ptr<UIEventObserver>&)
{
    g_unregisterObserverCalled = true;
}

void MockGetNodeProperty(const std::string&, std::unordered_map<std::string, std::string>& nodeProperties)
{
    g_getNodePropertyCalled = true;
    nodeProperties["result"] = "ok";
}

void MockGetSimplifiedInspectorTree(const TreeParams&, std::string& tree)
{
    g_getTreeCalled = true;
    tree = "mock_tree";
}

void MockGetSimplifiedInspectorTreeAsync(const TreeParams&, OnInspectorTreeResult&& callback)
{
    g_getTreeAsyncCalled = true;
    callback(std::make_shared<std::string>("mock_async_tree"));
}

void MockExecuteCommandAsync(const UICommandParams&, UICommandResult&& callback)
{
    g_executeCommandCalled = true;
    callback(std::make_shared<std::string>("mock_command"));
}

void MockGetComponentImageInfo(const ComponentParams&, std::shared_ptr<ComponentResult>& result)
{
    g_getComponentInfoCalled = true;
    result->isOk = true;
}

void ResetUIEventFuncForTest(UIEventFunc& func)
{
    func.registerFunc_ = nullptr;
    func.unregisterFunc_ = nullptr;
    func.getPropFunc_ = nullptr;
    func.getTreeFunc_ = nullptr;
    func.getTreeAsyncFunc_ = nullptr;
    func.executeCommandAsyncFunc_ = nullptr;
    func.getComponentInfoFuncFunc_ = nullptr;
    func.handle_ = nullptr;
}
} // namespace

class UiEventTest : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        NG::MockPipelineContext::SetUp();
        MockContainer::SetUp();
        MockContainer::Current()->pipelineContext_ = PipelineBase::GetCurrentContext();
        auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
        PipelineBase::GetCurrentContext()->SetThemeManager(themeManager);
        PipelineBase::GetCurrentContext()->SetEventManager(AceType::MakeRefPtr<EventManager>());
        EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<PopupTheme>()));
    }
    static void TearDownTestSuite()
    {
        MockContainer::Current()->pipelineContext_ = nullptr;
        NG::MockPipelineContext::TearDown();
    }
    void SetUp() {}
    void TearDown() {}
};

/**
 * @tc.name: UiEventTest001
 * @tc.desc: test UIEvent GetNodeProperty
 * @tc.type: FUNC
 */
HWTEST_F(UiEventTest, UiEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    std::string pageUrl = "Pages/Index";
    auto nodeProperties = std::unordered_map<std::string, std::string>();

    /**
     * @tc.steps2: Call the function GetNodeProperty.
     * @tc.expected: The function is run ok and IsAvailable() is true.
     */
    UIEvent::GetNodeProperty(pageUrl, nodeProperties);

    bool result = UIEventFunc::Get().IsAvailable();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: UiEventTest002
 * @tc.desc: test UIEvent GetSimplifiedInspectorTree
 * @tc.type: FUNC
 */
HWTEST_F(UiEventTest, UiEventTest002, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    std::string tree = "treeTest";

    /**
     * @tc.steps2: Call the function GetSimplifiedInspectorTree.
     * @tc.expected: The function is run ok and IsAvailable() is true.
     */
    UIEvent::GetSimplifiedInspectorTree(tree);
    bool result = UIEventFunc::Get().IsAvailable();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: UiEventTest003
 * @tc.desc: test UIEventFunc RegisterUIEventObserver/UnregisterUIEventObserver
 * @tc.type: FUNC
 */
HWTEST_F(UiEventTest, UiEventTest003, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters Call the function RegisterUIEventObserver.
     */
    std::string config = "configTest";
    const std::shared_ptr<UIEventObserver> observer = nullptr;
    UIEventFunc::RegisterUIEventObserver(config, observer);
    bool result = UIEventFunc::Get().IsAvailable();
    EXPECT_FALSE(result);

    /**
     * @tc.steps2: Call the function UnregisterUIEventObserver.
     * @tc.expected: The function is run ok and IsAvailable() is true.
     */
    UIEventFunc::UnregisterUIEventObserver(observer);
    bool result2 = UIEventFunc::Get().IsAvailable();
    EXPECT_FALSE(result2);
}

/**
 * @tc.name: UiEventTest004
 * @tc.desc: test UIEvent GetSimplifiedInspectorTree
 * @tc.type: FUNC
 */
HWTEST_F(UiEventTest, UiEventTest004, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    std::string tree = "treeTest";

    /**
     * @tc.steps2: Call the function GetSimplifiedInspectorTree.
     * @tc.expected: The function is run ok and IsAvailable() is true.
     */
    UIEvent::GetSimplifiedInspectorTree({ false }, tree);
    bool result = UIEventFunc::Get().IsAvailable();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: UiEventTest005
 * @tc.desc: test UIEvent GetSimplifiedInspectorTree
 * @tc.type: FUNC
 */
HWTEST_F(UiEventTest, UiEventTest005, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    std::string tree = "treeTest";

    /**
     * @tc.steps2: Call the function GetSimplifiedInspectorTree.
     * @tc.expected: The function is run ok and IsAvailable() is true.
     */
    UIEvent::GetSimplifiedInspectorTreeAsync({ false }, [](const std::shared_ptr<std::string> result) {});
    bool result = UIEventFunc::Get().IsAvailable();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: UiEventTest006
 * @tc.desc: test UIEvent GetSimplifiedInspectorTree
 * @tc.type: FUNC
 */
HWTEST_F(UiEventTest, UiEventTest006, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    std::string tree = "treeTest";

    /**
     * @tc.steps2: Call the function GetSimplifiedInspectorTree.
     * @tc.expected: The function is run ok.
     */
    TreeParams params;
    params.infoType = InspectorInfoType::PAGE_PARAM;
    UIEvent::GetSimplifiedInspectorTree(params, tree);
    EXPECT_FALSE(tree.empty());
}

/**
 * @tc.name: UiEventTest007
 * @tc.desc: test UIEvent ExecuteCommandAsync
 * @tc.type: FUNC
 */
HWTEST_F(UiEventTest, UiEventTest007, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    UICommandParams params = { "test" };

    /**
     * @tc.steps2: Call the function ExecuteCommandAsync.
     * @tc.expected: The function is run ok and IsAvailable() is true.
     */
    UIEvent::ExecuteCommandAsync(params, [](const std::shared_ptr<std::string> result) {});
    bool result = UIEventFunc::Get().IsAvailable();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: UiEventTest008
 * @tc.desc: test UIEvent GetComponentImageInfo
 * @tc.type: FUNC
 */
HWTEST_F(UiEventTest, UiEventTest008, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    ComponentParams params = { 0, 0 };
    auto result = std::make_shared<ComponentResult>();

    /**
     * @tc.steps2: Call the function GetComponentImageInfo.
     * @tc.expected: IsAvailable() is false.
     */
    UIEvent::GetComponentImageInfo(params, result);
    bool ret = UIEventFunc::Get().IsAvailable();
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: UiEventTest009
 * @tc.desc: test UIEventFunc wrappers with injected function pointers
 * @tc.type: FUNC
 */
HWTEST_F(UiEventTest, UiEventTest009, TestSize.Level1)
{
    auto& func = UIEventFunc::Get();
    ResetUIEventFuncForTest(func);
    func.registerFunc_ = MockRegisterUIEventObserver;
    func.unregisterFunc_ = MockUnregisterUIEventObserver;
    func.getPropFunc_ = MockGetNodeProperty;
    func.getTreeFunc_ = MockGetSimplifiedInspectorTree;
    func.getTreeAsyncFunc_ = MockGetSimplifiedInspectorTreeAsync;
    func.executeCommandAsyncFunc_ = MockExecuteCommandAsync;
    func.getComponentInfoFuncFunc_ = MockGetComponentImageInfo;

    g_registerObserverCalled = false;
    g_unregisterObserverCalled = false;
    g_getNodePropertyCalled = false;
    g_getTreeCalled = false;
    g_getTreeAsyncCalled = false;
    g_executeCommandCalled = false;
    g_getComponentInfoCalled = false;

    EXPECT_TRUE(func.IsAvailable());

    UIEventFunc::RegisterUIEventObserver("config", nullptr);
    UIEventFunc::UnregisterUIEventObserver(nullptr);

    std::unordered_map<std::string, std::string> nodeProperties;
    UIEventFunc::GetNodeProperty("page", nodeProperties);
    EXPECT_EQ(nodeProperties["result"], "ok");

    std::string tree;
    UIEventFunc::GetSimplifiedInspectorTree({ false }, tree);
    EXPECT_EQ(tree, "mock_tree");

    bool treeAsyncCallbackCalled = false;
    UIEventFunc::GetSimplifiedInspectorTreeAsync({ false }, [&treeAsyncCallbackCalled](
                                                              const std::shared_ptr<std::string> result) {
        treeAsyncCallbackCalled = result && *result == "mock_async_tree";
    });

    bool commandCallbackCalled = false;
    UIEventFunc::ExecuteCommandAsync({ "test" }, [&commandCallbackCalled](const std::shared_ptr<std::string> result) {
        commandCallbackCalled = result && *result == "mock_command";
    });

    auto componentResult = std::make_shared<ComponentResult>();
    UIEventFunc::GetComponentImageInfo({ 1, 1 }, componentResult);

    EXPECT_TRUE(g_registerObserverCalled);
    EXPECT_TRUE(g_unregisterObserverCalled);
    EXPECT_TRUE(g_getNodePropertyCalled);
    EXPECT_TRUE(g_getTreeCalled);
    EXPECT_TRUE(g_getTreeAsyncCalled);
    EXPECT_TRUE(treeAsyncCallbackCalled);
    EXPECT_TRUE(g_executeCommandCalled);
    EXPECT_TRUE(commandCallbackCalled);
    EXPECT_TRUE(g_getComponentInfoCalled);
    EXPECT_TRUE(componentResult->isOk);

    ResetUIEventFuncForTest(func);
}

/**
 * @tc.name: UiEventTest010
 * @tc.desc: test GetComponentImageInfo no-op branch does not affect availability
 * @tc.type: FUNC
 */
HWTEST_F(UiEventTest, UiEventTest010, TestSize.Level1)
{
    auto& func = UIEventFunc::Get();
    ResetUIEventFuncForTest(func);
    func.registerFunc_ = MockRegisterUIEventObserver;
    func.unregisterFunc_ = MockUnregisterUIEventObserver;
    func.getPropFunc_ = MockGetNodeProperty;
    func.getTreeFunc_ = MockGetSimplifiedInspectorTree;
    func.getTreeAsyncFunc_ = MockGetSimplifiedInspectorTreeAsync;
    func.executeCommandAsyncFunc_ = MockExecuteCommandAsync;
    func.getComponentInfoFuncFunc_ = nullptr;

    g_getComponentInfoCalled = false;
    auto componentResult = std::make_shared<ComponentResult>();
    componentResult->isOk = false;

    EXPECT_TRUE(func.IsAvailable());
    UIEventFunc::GetComponentImageInfo({ 2, 2 }, componentResult);
    EXPECT_FALSE(g_getComponentInfoCalled);
    EXPECT_FALSE(componentResult->isOk);

    ResetUIEventFuncForTest(func);
}
} // namespace OHOS::Ace
