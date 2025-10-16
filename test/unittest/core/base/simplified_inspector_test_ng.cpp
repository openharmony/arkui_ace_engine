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
#include "test/mock/core/render/mock_canvas_image.h"
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
    /**
     * @tc.steps: step1. context
     * @tc.expected: expect context not nullptr
     */
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

/**
* @tc.name: SimplifiedInspectorTestNg005
* @tc.desc: Test GetWebContentIfNeed
* @tc.type: FUNC
*/
HWTEST_F(SimplifiedInspectorTestNg, SimplifiedInspectorTestNg005, TestSize.Level1)
{
    auto id = ElementRegister::GetInstance()->MakeUniqueId();
    RefPtr<FrameNode> stageNode = FrameNode::CreateFrameNode("one", id, AceType::MakeRefPtr<Pattern>(), true);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    context->stageManager_ = AceType::MakeRefPtr<StageManager>(stageNode);
    int32_t containerId = 100;
    TreeParams params { true };
    params.isVisibleOnly = false;
    params.enableWeb = true;
    params.webContentJs = "hello";
    auto inspector = std::make_shared<SimplifiedInspector>(containerId, params);
    auto collector = std::make_shared<Recorder::InspectorTreeCollector>(
        [](const std::shared_ptr<std::string> result) {}, false);
    inspector->isAsync_ = true;
    inspector->collector_ = collector;
    stageNode->tag_ = V2::WEB_ETS_TAG;
    inspector->GetWebContentIfNeed(stageNode);
    EXPECT_FALSE(inspector->isBackground_);
}

/**
* @tc.name: SimplifiedInspectorTestNg006
* @tc.desc: Test GetComponentImageInfo
* @tc.type: FUNC
*/
HWTEST_F(SimplifiedInspectorTestNg, SimplifiedInspectorTestNg006, TestSize.Level1)
{
    auto stageNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    RefPtr<FrameNode> stageNode = FrameNode::CreateFrameNode("one", stageNodeId, AceType::MakeRefPtr<Pattern>(), true);
    auto pageNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto pageNode = NG::FrameNode::GetOrCreateFrameNode("page", pageNodeId, []() {
        return AceType::MakeRefPtr<NG::PagePattern>(AceType::MakeRefPtr<NG::PageInfo>(1, "index", "index.js"));
    });
    stageNode->AddChild(pageNode);
    auto rowId = ElementRegister::GetInstance()->MakeUniqueId();
    auto rowNode =
        NG::FrameNode::GetOrCreateFrameNode("Row", rowId, []() { return AceType::MakeRefPtr<NG::Pattern>(); });
    pageNode->AddChild(rowNode);
    auto imgId = ElementRegister::GetInstance()->MakeUniqueId();
    auto imgNode =
        NG::FrameNode::GetOrCreateFrameNode("Image", imgId, []() { return AceType::MakeRefPtr<NG::Pattern>(); });
    rowNode->AddChild(imgNode);

    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    context->stageManager_ = AceType::MakeRefPtr<StageManager>(stageNode);

    ComponentParams params;
    params.mode = 0;
    params.aceId = imgId;
    auto result = std::make_shared<ComponentResult>();
    result->callback = [](const std::pair<int32_t, std::shared_ptr<Media::PixelMap>>& pixelMapInfo){};
    auto inspector = std::make_shared<SimplifiedInspector>(0, params);
    inspector->GetComponentImageInfo(result);
    ASSERT_FALSE(result->isOk);

    params.mode = 1;
    params.aceId = imgId;
    inspector = std::make_shared<SimplifiedInspector>(0, params);
    inspector->GetComponentImageInfo(result);
    ASSERT_FALSE(result->isOk);

    params.mode = 2;
    params.aceId = imgId;
    inspector = std::make_shared<SimplifiedInspector>(0, params);
    inspector->GetComponentImageInfo(result);
    ASSERT_TRUE(result->isOk);

    params.mode = 3;
    params.aceId = imgId;
    inspector = std::make_shared<SimplifiedInspector>(0, params);
    inspector->GetComponentImageInfo(result);
    ASSERT_TRUE(result->isOk);
}

/**
* @tc.name: SimplifiedInspectorTestNg006
* @tc.desc: Test GetImagePixelMap
* @tc.type: FUNC
*/
HWTEST_F(SimplifiedInspectorTestNg, SimplifiedInspectorTestNg007, TestSize.Level1)
{
    auto imgId = ElementRegister::GetInstance()->MakeUniqueId();
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    pattern->image_ = AceType::MakeRefPtr<MockCanvasImage>();
    auto imgNode = NG::FrameNode::GetOrCreateFrameNode("Image", imgId, [pattern]() { return pattern; });
    ComponentParams params;
    params.mode = 0;
    params.aceId = imgId;
    auto inspector = std::make_shared<SimplifiedInspector>(0, params);
    auto ret = inspector->GetImagePixelMap(imgNode);
    ASSERT_EQ(ret, nullptr);
}
} // namespace OHOS::Ace::NG
