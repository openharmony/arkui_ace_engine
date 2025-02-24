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

#include "core/components_ng/pattern/button/button_pattern.h"
#define private public
#include "core/components_ng/pattern/web/richtext_model_ng.h"
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

class RichTextModelNGTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void RichTextModelNGTest::SetUpTestCase() {}
void RichTextModelNGTest::TearDownTestCase() {}
void RichTextModelNGTest::SetUp() {}
void RichTextModelNGTest::TearDown() {}

/**
 * @tc.name: Create_001
 * @tc.desc: Test function Create.
 * @tc.type: FUNC
 */
HWTEST_F(RichTextModelNGTest, Create_001, TestSize.Level1)
{
    RichTextModelNG richTextModelNG;
    const std::string data = "<h1>h1 text for test</h1>";
    richTextModelNG.Create(data);
    EXPECT_FALSE(richTextModelNG.isDataEmpty_);
}

/**
 * @tc.name: Create_002
 * @tc.desc: Test function Create.
 * @tc.type: FUNC
 */
HWTEST_F(RichTextModelNGTest, Create_002, TestSize.Level1)
{
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockPipelineContext::SetUp();

    RichTextModelNG richTextModelNG;
    const std::string data = "<h1>h1 text for test</h1>";
    richTextModelNG.Create(data);
    EXPECT_FALSE(richTextModelNG.isDataEmpty_);

    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: SetOnPageStart_001
 * @tc.desc: Test function SetOnPageStart.
 * @tc.type: FUNC
 */
HWTEST_F(RichTextModelNGTest, SetOnPageStart_001, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, nodeId, []() {
        return AceType::MakeRefPtr<ButtonPattern>();
    });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    RichTextModelNG richTextModelNG;
    auto onStartEvent = [](const BaseEventInfo* info) {};
    richTextModelNG.SetOnPageStart(onStartEvent);
}

/**
 * @tc.name: SetOnPageStart_002
 * @tc.desc: Test function SetOnPageStart.
 * @tc.type: FUNC
 */
HWTEST_F(RichTextModelNGTest, SetOnPageStart_002, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() {
        return AceType::MakeRefPtr<WebPattern>();
    });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    RichTextModelNG richTextModelNG;
    auto onStartEvent = [](const BaseEventInfo* info) {};
    richTextModelNG.SetOnPageStart(onStartEvent);
}

/**
 * @tc.name: SetOnPageFinish_001
 * @tc.desc: Test function SetOnPageFinish.
 * @tc.type: FUNC
 */
HWTEST_F(RichTextModelNGTest, SetOnPageFinish_001, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, nodeId, []() {
        return AceType::MakeRefPtr<ButtonPattern>();
    });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    RichTextModelNG richTextModelNG;
    auto onCompleteEvent = [](const BaseEventInfo* info) {};
    richTextModelNG.SetOnPageFinish(onCompleteEvent);
}

/**
 * @tc.name: SetOnPageFinish_002
 * @tc.desc: Test function SetOnPageFinish.
 * @tc.type: FUNC
 */
HWTEST_F(RichTextModelNGTest, SetOnPageFinish_002, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() {
        return AceType::MakeRefPtr<WebPattern>();
    });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    RichTextModelNG richTextModelNG;
    auto onCompleteEvent = [](const BaseEventInfo* info) {};
    richTextModelNG.SetOnPageFinish(onCompleteEvent);
}

} // namespace OHOS::Ace::NG
