/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/view_stack_processor.h"
// Add the following two macro definitions to test the private and protected method.
#define private public
#define protected public
#include "core/components_ng/pattern/navrouter/navrouter_model_ng.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
class NavrouterPatternTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void NavrouterPatternTestNg::SetUpTestCase() {}
void NavrouterPatternTestNg::TearDownTestCase() {}
void NavrouterPatternTestNg::SetUp() {}
void NavrouterPatternTestNg::TearDown() {}

/**
 * @tc.name: NavrouterModelNGTest001
 * @tc.desc: Test Navrouter Create And Get Data
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterPatternTestNg, NavrouterModelNGTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init NavrouterModelNG object
     */
    NavRouterModelNG NavRouterModelNG;
    NavRouterModelNG.Create();
    /**
     * @tc.steps: step2. Get NavrouterPatternTestNg frameNode and check
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
}

/**
 * @tc.name: NavrouterModelNGTest002
 * @tc.desc: Test Navrouter Create And Get Do Something result
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterPatternTestNg, NavrouterModelNGTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init NavrouterModelNG object
     */
    NavRouterModelNG NavRouterModelNG;
    NavRouterModelNG.Create();
    /**
     * @tc.steps: step2. Set call methods
     * @tc.expected: step2. Check the NavrouterPatternTestNg pattern value
     */
    auto onStateChange = [](const bool) {};
    NavRouterModelNG.SetOnStateChange(std::move(onStateChange));
    auto frameNodeonStateChange = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNodeonStateChange, nullptr);
}
} // namespace OHOS::Ace::NG