/*
 * Copyright (c) 2025 iSoftStone Information Technology (Group) Co.,Ltd.
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
#include <fcntl.h>
#include <functional>
#include <memory>
#include <optional>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

#define protected public
#define private public
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/utils/utils.h"
#include "core/common/ace_application_info.h"
#include "core/components_ng/base/inspector.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/base/simplified_inspector.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/stage/stage_manager.h"
#include "core/components_ng/pattern/stage/stage_pattern.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/components_ng/pattern/text/span_node.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "base/json/json_util.h"
#include "core/components_ng/pattern/custom/custom_node.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/mock/core/render/mock_rosen_render_context.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
}; // namespace-*//


class SimplifiedInspectorTestNg : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        MockPipelineContext::SetUp();
    }
    static void TearDownTestSuite()
    {
        MockPipelineContext::TearDown();
    }
};

/**
 * @tc.name: SimplifiedInspectorTestNg001
 * @tc.desc: Test the operation of GetSimplifiedInspector
 * @tc.type: FUNC
 */
HWTEST_F(SimplifiedInspectorTestNg, SimplifiedInspectorTestNg001, TestSize.Level1)
{
    auto id = ElementRegister::GetInstance()->MakeUniqueId();
    RefPtr<FrameNode> ONE = FrameNode::CreateFrameNode("one", id, AceType::MakeRefPtr<Pattern>(), true);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->stageManager_ = AceType::MakeRefPtr<StageManager>(ONE);
    int32_t containerId = 1;
    TreeParams params { false };
    auto inspector = std::make_shared<SimplifiedInspector>(containerId, params);
    auto collector = std::make_shared<Recorder::InspectorTreeCollector>(
        [](const std::shared_ptr<std::string> result) {
            ASSERT_NE(result, nullptr);
            EXPECT_NE(result->c_str(), "");
        },
        false);
    inspector->GetInspectorAsync(collector);
    auto result = inspector->GetInspector();
    EXPECT_NE(result, "");
    context->stageManager_ = nullptr;
}

/**
* @tc.name: SimplifiedInspectorTestNg002
* @tc.desc: Test the operation of FilterEmptyInitially
* @tc.type: FUNC
*/
HWTEST_F(SimplifiedInspectorTestNg, SimplifiedInspectorTestNg002, TestSize.Level1)
{
    auto id = ElementRegister::GetInstance()->MakeUniqueId();
    RefPtr<FrameNode> stageNode = FrameNode::CreateFrameNode("one", id, AceType::MakeRefPtr<Pattern>(), true);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    context->stageManager_ = AceType::MakeRefPtr<StageManager>(stageNode);
    auto pageId = ElementRegister::GetInstance()->MakeUniqueId();
    const RefPtr<FrameNode> pageA = FrameNode::CreateFrameNode("PageA", pageId,
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>(10, "page/Index", "page/Index")));
    stageNode->AddChild(pageA);
    int32_t containerId = 100;
    TreeParams params { false };
    auto inspector = std::make_shared<SimplifiedInspector>(containerId, params);
    auto collector = std::make_shared<Recorder::InspectorTreeCollector>(
        [](const std::shared_ptr<std::string> result) {
            ASSERT_NE(result, nullptr);
            auto inspectorJson = JsonUtil::ParseJsonString(*result);
            EXPECT_EQ(inspectorJson->GetValue("pageUrl")->GetString(), "page/Index");
        },
        false);
    inspector->GetInspectorBackgroundAsync(collector);
    auto result = collector->GetJson()->ToString();
    EXPECT_EQ(result, "{}");
    context->stageManager_ = nullptr;
}

/**
* @tc.name: SimplifiedInspectorTestNg003
* @tc.desc: Test the operation of FilterEmptyInitially
* @tc.type: FUNC
*/
HWTEST_F(SimplifiedInspectorTestNg, SimplifiedInspectorTestNg003, TestSize.Level1)
{
    auto id = ElementRegister::GetInstance()->MakeUniqueId();
    RefPtr<FrameNode> stageNode = FrameNode::CreateFrameNode("one", id, AceType::MakeRefPtr<Pattern>(), true);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    context->stageManager_ = AceType::MakeRefPtr<StageManager>(stageNode);
    int32_t containerId = 100;
    TreeParams params { false };
    auto inspector = std::make_shared<SimplifiedInspector>(containerId, params);
    auto collector = std::make_shared<Recorder::InspectorTreeCollector>(
        [](const std::shared_ptr<std::string> result) {}, false);
    inspector->GetInspectorBackgroundAsync(collector);
    auto result = collector->GetJson()->ToString();
    EXPECT_EQ(result, "{}");
}

/**
* @tc.name: SimplifiedInspectorTestNg004
* @tc.desc: Test the operation of FilterEmptyInitially
* @tc.type: FUNC
*/
HWTEST_F(SimplifiedInspectorTestNg, SimplifiedInspectorTestNg004, TestSize.Level1)
{
    auto id = ElementRegister::GetInstance()->MakeUniqueId();
    RefPtr<FrameNode> stageNode = FrameNode::CreateFrameNode("one", id, AceType::MakeRefPtr<Pattern>(), true);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    context->stageManager_ = AceType::MakeRefPtr<StageManager>(stageNode);
    int32_t containerId = 100;
    TreeParams params { true };
    auto inspector = std::make_shared<SimplifiedInspector>(containerId, params);
    auto collector = std::make_shared<Recorder::InspectorTreeCollector>(
        [](const std::shared_ptr<std::string> result) {}, false);
    inspector->GetInspectorBackgroundAsync(collector);
    EXPECT_FALSE(inspector->isBackground_);
    EXPECT_TRUE(inspector->isAsync_);
}
} // namespace OHOS::Ace::NG
