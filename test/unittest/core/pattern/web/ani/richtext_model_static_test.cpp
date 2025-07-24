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

#include "gtest/gtest.h"

#define private public
#include "core/components_ng/pattern/web/ani/richtext_model_static.h"
#undef private
#include "core/components_ng/pattern/web/web_pattern.h"
#include "test/mock/base/mock_task_executor.h"
#define private public
#include "test/mock/core/common/mock_container.h"
#undef private
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace;

namespace OHOS::Ace::NG {

class RichTextModelStaticTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void RichTextModelStaticTest::SetUpTestCase() {}
void RichTextModelStaticTest::TearDownTestCase() {}
void RichTextModelStaticTest::SetUp() {}
void RichTextModelStaticTest::TearDown() {}

/**
 * @tc.name: Create_001
 * @tc.desc: Test function Create.
 * @tc.type: FUNC
 */
HWTEST_F(RichTextModelStaticTest, Create_001, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();

    auto frameNode = RichTextModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    const std::string data = "<h1>h1 text for test</h1>";
    RichTextModelStatic::SetRichTextOptions(AccessibilityManager::RawPtr(frameNode), data);
    auto webData = webPattern->GetWebData();
    EXPECT_EQ(webData.has_value(), true);
    EXPECT_EQ(webData.value(), data);
}

/**
 * @tc.name: SetOnPageStart_001
 * @tc.desc: Test function SetOnPageStart.
 * @tc.type: FUNC
 */
HWTEST_F(RichTextModelStaticTest, SetOnPageStart_001, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();

    auto frameNode = RichTextModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    auto onStartEvent = [](const BaseEventInfo* info) {};
    RichTextModelStatic::SetOnPageStart(AccessibilityManager::RawPtr(frameNode), onStartEvent);
}

/**
 * @tc.name: SetOnPageFinish_001
 * @tc.desc: Test function SetOnPageFinish.
 * @tc.type: FUNC
 */
HWTEST_F(RichTextModelStaticTest, SetOnPageFinish_001, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();

    auto frameNode = RichTextModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    auto onCompleteEvent = [](const BaseEventInfo* info) {};
    RichTextModelStatic::SetOnPageFinish(AccessibilityManager::RawPtr(frameNode), onCompleteEvent);
}
} // namespace OHOS::Ace::NG
