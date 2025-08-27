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
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components/popup/popup_theme.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
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
} // namespace OHOS::Ace
