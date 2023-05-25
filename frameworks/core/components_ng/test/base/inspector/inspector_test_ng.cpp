/*
 * Copyright (c) 2023 iSoftStone Information Technology (Group) Co.,Ltd.
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
#include <cstdint>
#include <functional>
#include <memory>
#include <optional>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

#define protected public
#define private public
#include "cJSON.h"
#include "interfaces/inner_api/ace/ui_content.h"
#include "test/mock/base/mock_task_executor.h"

#include "base/utils/utils.h"
#include "core/common/ace_application_info.h"
#include "core/components_ng/base/inspector.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/stage/stage_manager.h"
#include "core/components_ng/pattern/text/span_node.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const RefPtr<FrameNode> ONE = FrameNode::CreateFrameNode("one", 1, AceType::MakeRefPtr<Pattern>(), true);
const RefPtr<FrameNode> TWO = FrameNode::CreateFrameNode("two", 2, AceType::MakeRefPtr<Pattern>());
const RefPtr<FrameNode> THREE = FrameNode::CreateFrameNode("three", 3, AceType::MakeRefPtr<Pattern>());
const RefPtr<FrameNode> STAGE = FrameNode::CreateFrameNode("stage", 4, AceType::MakeRefPtr<Pattern>(), true);
const RefPtr<FrameNode> PAGE = FrameNode::CreateFrameNode("page", 5, AceType::MakeRefPtr<Pattern>(), true);
std::string key = "key";
}; // namespace

class InspectorTestNg : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        MockPipelineBase::SetUp();
    }
    static void TeardownTestSuite()
    {
        MockPipelineBase::TearDown();
    }
};

/**
 * @tc.name: InspectorTestNg001
 * @tc.desc: Test the operation of Inspector
 * @tc.type: FUNC
 */
HWTEST_F(InspectorTestNg, InspectorTestNg001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback GetFrameNodeByKey
     * @tc.expected: expect the function is run ok
     */
    auto nodePtr = Inspector::GetFrameNodeByKey(key);
    EXPECT_EQ(nodePtr, nullptr);

    /**
     * @tc.steps: step2. callback SetUp
     * @tc.expected: expect context1 is not null
     */
    auto context1 = PipelineContext::GetCurrentContext();
    ASSERT_NE(context1, nullptr);
    auto nodePtr1 = Inspector::GetFrameNodeByKey(key);
    EXPECT_EQ(nodePtr1, nullptr);

    /**
     * @tc.steps: step3. callback GetFrameNodeByKey
     * @tc.expected: expect nodePtr2 not null
     */
    context1->rootNode_ = ONE;
    context1->rootNode_->AddChild(TWO);
    auto rootNode = context1->GetRootElement();
    ASSERT_NE(rootNode, nullptr);
    auto nodePtr2 = Inspector::GetFrameNodeByKey(key);
    EXPECT_EQ(nodePtr2, nullptr);

    auto nodePtr3 = Inspector::GetFrameNodeByKey("");
    ASSERT_NE(nodePtr3, nullptr);
    context1->rootNode_ = nullptr;
}

/**
 * @tc.name: InspectorTestNg002
 * @tc.desc: Test the operation of Inspector
 * @tc.type: FUNC
 */
HWTEST_F(InspectorTestNg, InspectorTestNg002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback GetInspectorNodeByKey
     * @tc.expected: expect the function is run ok
     */
    auto test = Inspector::GetInspectorNodeByKey(key);
    EXPECT_EQ(test, "");

    /**
     * @tc.steps: step2. callback SetUp
     * @tc.expected: expect test1 is "".
     */
    auto context1 = PipelineContext::GetCurrentContext();
    ASSERT_NE(context1, nullptr);
    auto test1 = Inspector::GetInspectorNodeByKey(key);
    EXPECT_EQ(test1, "");

    /**
     * @tc.steps: step1. callback rootNode_
     * @tc.expected: expect the function GetInspectorNodeByKey is return null
     */
    context1->rootNode_ = ONE;
    ASSERT_NE(context1, nullptr);
    auto test2 = Inspector::GetInspectorNodeByKey(key);
    EXPECT_EQ(test2, "");
    /**
     * @tc.steps: step3. callback GetInspectorNodeByKey
     * @tc.expected: expect nodePtr2 not null
     */
    auto test3 = Inspector::GetInspectorNodeByKey("");
    context1->rootNode_ = nullptr;
}

/**
 * @tc.name: InspectorTestNg003
 * @tc.desc: Test the operation of Inspector
 * @tc.type: FUNC
 */
HWTEST_F(InspectorTestNg, InspectorTestNg003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback GetInspector
     * @tc.expected: expect the function is run ok
     */
    auto context1 = PipelineContext::GetCurrentContext();
    ASSERT_NE(context1, nullptr);
    context1->stageManager_ = AceType::MakeRefPtr<StageManager>(ONE);

    context1->GetStageManager()->GetLastPage()->GetParent()->SetParent(ONE);

    /**
     * @tc.steps: step2. call GetInspector
     * @tc.expected: the return value is empty string
     */
    auto test1 = Inspector::GetInspector(false);
    EXPECT_NE(test1, "");
    auto test3 = Inspector::GetInspector(true);
    EXPECT_NE(test3, "");
    context1->stageManager_ = nullptr;
}

/**
 * @tc.name: InspectorTestNg004
 * @tc.desc: Test the operation of View Inspector
 * @tc.type: FUNC
 */
HWTEST_F(InspectorTestNg, InspectorTestNg004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback SendEventByKey
     * @tc.expected: expect the function is run ok
     */
    int action = 1;
    std::string params = "params";
    auto test = Inspector::SendEventByKey(key, action, params);
    EXPECT_EQ(test, false);

    /**
     * @tc.steps: step2. callback SetUp
     * @tc.expected: expect SendEventByKey is return false.
     */
    auto context1 = PipelineContext::GetCurrentContext();
    auto test1 = Inspector::SendEventByKey(key, action, params);
    EXPECT_EQ(test1, false);

    /**
     * @tc.steps: step3. callback SendEventByKey
     * @tc.expected: expect nodePtr2 not null
     */
    context1->rootNode_ = ONE;
    auto rootNode = context1->GetRootElement();
    ASSERT_NE(rootNode, nullptr);
    auto test2 = Inspector::SendEventByKey(key, action, params);
    EXPECT_EQ(test2, false);
    context1->rootNode_ = nullptr;
}

/**
 * @tc.name: InspectorTestNg005
 * @tc.desc: Test the operation of View Inspector
 * @tc.type: FUNC
 */
HWTEST_F(InspectorTestNg, InspectorTestNg005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback HideAllMenus
     * @tc.expected: expect the function is run ok
     */
    Inspector::HideAllMenus();
    auto context = PipelineContext::GetCurrentContext();

    /**
     * @tc.steps: step2. callback SetUp
     * @tc.expected: step2. expect context1 is return null.
     */
    auto context1 = PipelineContext::GetCurrentContext();
    ASSERT_NE(context1, nullptr);
    Inspector::HideAllMenus();
}

/**
 * @tc.name: InspectorTestNg006
 * @tc.desc: Test the operation of Inspector
 * @tc.type: FUNC
 */
HWTEST_F(InspectorTestNg, InspectorTestNg006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback GetInspector
     * @tc.expected: expect the function is run ok
     */
    auto context1 = PipelineContext::GetCurrentContext();
    ASSERT_NE(context1, nullptr);
    context1->stageManager_ = AceType::MakeRefPtr<StageManager>(ONE);
    context1->GetStageManager()->GetLastPage()->GetParent()->SetParent(ONE);

    std::vector<RefPtr<NG::UINode>> children;
    children.push_back(TWO);

    auto test = Inspector::GetInspector(false);

    /**
     * @tc.steps: step2 add child to two and create a temp node with tag "temp"
                call GetInspector
     * @tc.expected: the return value is empty string
     */
    THREE->isInternal_ = true;
    TWO->AddChild(PAGE);
    TWO->AddChild(THREE);
    TWO->AddChild(STAGE);
    auto temp = FrameNode::CreateFrameNode("temp", 5, AceType::MakeRefPtr<Pattern>(), true);
    STAGE->AddChild(temp);
    ONE->tag_ = "stage";
    auto test1 = Inspector::GetInspector(false);
    EXPECT_NE(test1, "");

    PAGE->hostPageId_ = TWO->GetPageId();
    auto test2 = Inspector::GetInspector(false);
    EXPECT_NE(test2, "");

    TWO->children_.clear();
    auto test3 = Inspector::GetInspector(false);
    EXPECT_NE(test3, "");

    context1->stageManager_ = nullptr;
    ONE->tag_ = "one";
}

/**
 * @tc.name: InspectorTestNg007
 * @tc.desc: Test the operation of Inspector
 * @tc.type: FUNC
 */
HWTEST_F(InspectorTestNg, InspectorTestNg007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback GetInspector
     * @tc.expected: expect the function is run ok
     */
    auto context1 = PipelineContext::GetCurrentContext();
    ASSERT_NE(context1, nullptr);
    context1->stageManager_ = AceType::MakeRefPtr<StageManager>(ONE);

    /**
     * @tc.steps: step2. callback pop_back
     * @tc.expected: expect clean children and pageRootNode is noll
     */
    ONE->children_.pop_back();
    auto pageRootNode = context1->GetStageManager()->GetLastPage();
    auto test = Inspector::GetInspector(false);
    EXPECT_EQ(test, "{\"$type\":\"root\",\"width\":\"0.000000\",\"height\":\"0.000000\",\"$resolution\":\"0.000000\"}");
    context1->stageManager_ = nullptr;
}
} // namespace OHOS::Ace::NG
