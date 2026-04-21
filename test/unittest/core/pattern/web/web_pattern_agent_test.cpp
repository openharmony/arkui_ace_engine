
/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include <gmock/gmock.h>

#include "gtest/gtest.h"
#define private public
#include "core/components/web/resource/web_delegate.h"
#include "core/components_ng/pattern/web/web_pattern.h"
#undef private

#include "cJSON.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/web/web_dom_document.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class WebPatternAgentTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void WebPatternAgentTest::SetUpTestCase() {}
void WebPatternAgentTest::TearDownTestCase() {}
void WebPatternAgentTest::SetUp() {}
void WebPatternAgentTest::TearDown() {}

/**
 * @tc.name: OnQuickMenuDismissed001
 * @tc.desc: OnQuickMenuDismissed.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternAgentTest, HighlightSpecifiedContent001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern, nullptr);
    std::string content = "test string";
    std::vector<std::string> nodeIds = {"test string"};
    std::string configs = "test string";
    webPattern->HighlightSpecifiedContent(content, nodeIds, configs);
#endif
}

/**
 * @tc.name: GetLayoutModeStr001
 * @tc.desc: Test GetLayoutModeStr with NONE mode.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternAgentTest, GetLayoutModeStr001, TestSize.Level1)
{
    auto webPattern = AceType::MakeRefPtr<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->SetLayoutMode(WebLayoutMode::NONE);
    auto result = webPattern->GetLayoutModeStr();
    EXPECT_EQ(result, "NONE");
}

/**
 * @tc.name: GetLayoutModeStr002
 * @tc.desc: Test GetLayoutModeStr with FIT_CONTENT mode.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternAgentTest, GetLayoutModeStr002, TestSize.Level1)
{
    auto webPattern = AceType::MakeRefPtr<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->SetLayoutMode(WebLayoutMode::FIT_CONTENT);
    auto result = webPattern->GetLayoutModeStr();
    EXPECT_EQ(result, "FIT_CONTENT");
}
}