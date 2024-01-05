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

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
class UiEventTest : public testing::Test {
public:
    static void SetUpTestCase() {}
    static void TearDownTestCase() {}
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
    EXPECT_TRUE(result);
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
    EXPECT_TRUE(result);
}
} // namespace OHOS::Ace