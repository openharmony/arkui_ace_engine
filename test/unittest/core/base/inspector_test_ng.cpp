/*
 * Copyright (c) 2023-2024 iSoftStone Information Technology (Group) Co.,Ltd.
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
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/stage/stage_manager.h"
#include "core/components_ng/pattern/stage/stage_pattern.h"
#include "core/components_ng/pattern/text/span_node.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
std::string key = "key";
}; // namespace

class InspectorTestNg : public testing::Test {
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
 * @tc.name: InspectorTestNg001
 * @tc.desc: Test the operation of Inspector
 * @tc.type: FUNC
 */
HWTEST_F(InspectorTestNg, InspectorTestNg001, TestSize.Level1)
{
    auto id = ElementRegister::GetInstance()->MakeUniqueId();
    RefPtr<FrameNode> ONE = FrameNode::CreateFrameNode("one", id, AceType::MakeRefPtr<Pattern>(), true);
    auto id2 = ElementRegister::GetInstance()->MakeUniqueId();
    const RefPtr<FrameNode> TWO = FrameNode::CreateFrameNode("two", id2, AceType::MakeRefPtr<Pattern>());
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
    auto id = ElementRegister::GetInstance()->MakeUniqueId();
    RefPtr<FrameNode> ONE = FrameNode::CreateFrameNode("one", id, AceType::MakeRefPtr<Pattern>(), true);
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
    auto id = ElementRegister::GetInstance()->MakeUniqueId();
    RefPtr<FrameNode> ONE = FrameNode::CreateFrameNode("one", id, AceType::MakeRefPtr<Pattern>(), true);
    auto context1 = PipelineContext::GetCurrentContext();
    ASSERT_NE(context1, nullptr);
    context1->stageManager_ = AceType::MakeRefPtr<StageManager>(ONE);
    auto id2 = ElementRegister::GetInstance()->MakeUniqueId();
    const RefPtr<FrameNode> TWO = FrameNode::CreateFrameNode("stage", id2, AceType::MakeRefPtr<Pattern>());
    ONE->AddChild(TWO);
    auto id3 = ElementRegister::GetInstance()->MakeUniqueId();
    const RefPtr<FrameNode> THREE = FrameNode::CreateFrameNode("three", id3, AceType::MakeRefPtr<Pattern>());
    THREE->AddChild(ONE);

    /**
     * @tc.steps: step2. call GetInspector
     * @tc.expected: the return value is empty string
     */
    auto test1 = Inspector::GetInspector(false);
    EXPECT_NE(test1, "");
    auto test3 = Inspector::GetInspector(true);
    EXPECT_NE(test3, "");
    auto test4 = Inspector::GetInspectorOfNode(TWO);
    EXPECT_NE(test4, "");

    RefPtr<MockPipelineContext> pipeline_bak = MockPipelineContext::pipeline_;
    MockPipelineContext::pipeline_ = nullptr;
    auto jsonRoot = JsonUtil::Create(true);
    const char inspectorType[] = "$type";
    const char inspectorRoot[] = "root";
    jsonRoot->Put(inspectorType, inspectorRoot);
    auto test5 = Inspector::GetInspector(false);
    EXPECT_EQ(test5, jsonRoot->ToString());
    MockPipelineContext::pipeline_ = pipeline_bak;

    InspectorFilter filter;
    std::string testId = "test";
    filter.SetFilterID(testId);
    bool needThrow = false;
    auto test6 = Inspector::GetInspector(false, filter, needThrow);
    auto rootNode = context1->GetStageManager()->GetLastPage();
    if (rootNode == nullptr) {
        EXPECT_EQ(test6, jsonRoot->ToString());
    } else {
        EXPECT_NE(test6, "");
    }
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
     * @tc.steps: step1. set rootNode and taskExecutor call SendEventByKey
     * @tc.expected: expect return true
     */
    auto context = NG::PipelineContext::GetCurrentContext();
    context->rootNode_ = FrameNode::CreateFrameNode("frameNode", 60, AceType::MakeRefPtr<Pattern>(), true);
    context->rootNode_->SetGeometryNode(AceType::MakeRefPtr<GeometryNode>());
    context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto test3 = Inspector::SendEventByKey("", static_cast<int>(AceAction::ACTION_CLICK), "params");
    EXPECT_EQ(test3, true);
    test3 = Inspector::SendEventByKey("", static_cast<int>(AceAction::ACTION_LONG_CLICK), "params");
    EXPECT_EQ(test3, true);
    test3 = Inspector::SendEventByKey("", 31, "params");
    EXPECT_EQ(test3, true);

    context->rootNode_ = nullptr;
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

    auto id = ElementRegister::GetInstance()->MakeUniqueId();
    RefPtr<FrameNode> ONE = FrameNode::CreateFrameNode("one", id, AceType::MakeRefPtr<Pattern>(), true);
    context1->stageManager_ = AceType::MakeRefPtr<StageManager>(ONE);

    /**
     * @tc.steps: step2 add child to two and create a temp node with tag "temp"
                call GetInspector
     * @tc.expected: the return value is empty string
     */
    auto id2 = ElementRegister::GetInstance()->MakeUniqueId();
    const RefPtr<FrameNode> TWO = FrameNode::CreateFrameNode("two", id2, AceType::MakeRefPtr<Pattern>());
    ONE->children_.clear();
    ONE->AddChild(TWO);
    auto stageParent = FrameNode::CreateFrameNode("stageParent", 5, AceType::MakeRefPtr<Pattern>(), true);
    stageParent->AddChild(ONE);

    const RefPtr<FrameNode> THREE = FrameNode::CreateFrameNode(
        "three", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    const RefPtr<FrameNode> STAGE = FrameNode::CreateFrameNode(
        "stage", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> PAGE = FrameNode::CreateFrameNode(
        "page", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
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

    PAGE->hostPageId_ = TWO->GetPageId() + 1;
    test2 = Inspector::GetInspector(false);
    EXPECT_NE(test2, "");

    TWO->children_.clear();
    auto test3 = Inspector::GetInspector(false);
    EXPECT_NE(test3, "");

    /**
     *  ONE(stageNode)--TWO(GetLastPage())--PAGE
     *                   |--THREE
     *                   |--STAGE--temp
     *                   |--frameNode
     *                   |--frameNode2--frameNode3
     */
    /**
     * @tc.steps: step3 add child to two and create a frame node tree
            call GetInspector
     * @tc.expected: the return value is not empty string
     */
    auto spanNode = SpanNode::GetOrCreateSpanNode(int32_t(191));
    TWO->AddChild(spanNode);

    auto frameNode = FrameNode::CreateFrameNode("frameNode", 6, AceType::MakeRefPtr<Pattern>(), true);
    TWO->AddChild(frameNode);
    frameNode->isActive_ = true;
    auto frameNode2 = FrameNode::CreateFrameNode("frameNode2", 62, AceType::MakeRefPtr<Pattern>(), true);
    TWO->AddChild(frameNode2);
    frameNode2->isActive_ = false;
    auto frameNode3 = FrameNode::CreateFrameNode("frameNode3", 63, AceType::MakeRefPtr<Pattern>(), true);
    frameNode2->AddChild(frameNode3);
    test3 = Inspector::GetInspector(false);
    EXPECT_NE(test3, "");
    context1->stageManager_ = nullptr;
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
    auto id = ElementRegister::GetInstance()->MakeUniqueId();
    RefPtr<FrameNode> ONE = FrameNode::CreateFrameNode("one", id, AceType::MakeRefPtr<Pattern>(), true);
    auto context1 = PipelineContext::GetCurrentContext();
    ASSERT_NE(context1, nullptr);
    context1->stageManager_ = AceType::MakeRefPtr<StageManager>(ONE);

    /**
     * @tc.steps: step2. callback pop_back
     * @tc.expected: expect clean children and pageRootNode is noll
     */
    auto pageRootNode = context1->GetStageManager()->GetLastPage();
    auto test = Inspector::GetInspector(false);
    auto str = "{\"$type\":\"root\",\"width\":\"720.000000\",\"height\":\"1280.000000\",\"$resolution\":\"1.000000\"}";
    EXPECT_EQ(test, str);

    context1->stageManager_ = nullptr;
}

/**
 * @tc.name: InspectorTestNg008
 * @tc.desc: Test the GetRectangleById
 * @tc.type: FUNC
 */
HWTEST_F(InspectorTestNg, InspectorTestNg008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. creat frameNode
     * @tc.expected: expect the function is run ok
     */
    auto id = ElementRegister::GetInstance()->MakeUniqueId();
    RefPtr<FrameNode> ONE = FrameNode::CreateFrameNode("one", id, AceType::MakeRefPtr<Pattern>(), true);
    auto context = NG::PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);

    /**
     * @tc.steps: step2. assign value to rootNode_
     * @tc.expected: rootNode_ pass non-null check.
     */
    context->rootNode_ = ONE;
    context->rootNode_->SetGeometryNode(AceType::MakeRefPtr<GeometryNode>());

    /**
     * @tc.steps: step3. construct assignments and call GetRectangleById.
     * @tc.expected: expect the GetRectangleById is run ok and result is expected.
     */
    OHOS::Ace::NG::Rectangle rect;
    string key = "";
    Inspector::GetRectangleById(key, rect);
    float zResult = 1.0f;
    EXPECT_EQ(rect.scale.z, zResult);
    context->rootNode_ = nullptr;
}

/**
 * @tc.name: InspectorTestNg009
 * @tc.desc: Test the GetFrameNodeByKey
 * @tc.type: FUNC
 */
HWTEST_F(InspectorTestNg, InspectorTestNg009, TestSize.Level1)
{
    auto id = ElementRegister::GetInstance()->MakeUniqueId();
    RefPtr<FrameNode> ONE = FrameNode::CreateFrameNode("one", id, AceType::MakeRefPtr<Pattern>(), true);
    auto id2 = ElementRegister::GetInstance()->MakeUniqueId();
    const RefPtr<FrameNode> TWO = FrameNode::CreateFrameNode("two", id2, AceType::MakeRefPtr<Pattern>());
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto nodePtr = Inspector::GetFrameNodeByKey(key);
    EXPECT_EQ(nodePtr, nullptr);

    Inspector::AddOffscreenNode(ONE);
    nodePtr = Inspector::GetFrameNodeByKey("one");
    EXPECT_EQ(nodePtr, 0);

    RefPtr<MockPipelineContext> pipeline_bak = MockPipelineContext::pipeline_;
    MockPipelineContext::pipeline_ = nullptr;
    context = PipelineContext::GetCurrentContext();
    EXPECT_EQ(context, nullptr);
    nodePtr = Inspector::GetFrameNodeByKey("two");
    EXPECT_EQ(nodePtr, nullptr);
    MockPipelineContext::pipeline_ = pipeline_bak;
}

/**
 * @tc.name: InspectorTestNg010
 * @tc.desc: Test the GetRectangleById
 * @tc.type: FUNC
 */
HWTEST_F(InspectorTestNg, InspectorTestNg010, TestSize.Level1)
{
    auto id = ElementRegister::GetInstance()->MakeUniqueId();
    RefPtr<FrameNode> ONE = FrameNode::CreateFrameNode("one", id, AceType::MakeRefPtr<Pattern>(), true);
    auto context = NG::PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->rootNode_ = ONE;
    context->rootNode_->SetGeometryNode(AceType::MakeRefPtr<GeometryNode>());
    std::string key = "key";
    OHOS::Ace::NG::Rectangle rect;
    Inspector::GetRectangleById(key, rect);
    EXPECT_EQ(rect.size.Width(), 0.0f);

    auto frameNode = Inspector::GetFrameNodeByKey("one");
    RefPtr<RenderContext> renderContextBak = ONE->renderContext_;
    ONE->renderContext_ = nullptr;
    Inspector::GetRectangleById("one", rect);
    EXPECT_EQ(rect.screenRect.Width(), 0.0f);
    ONE->renderContext_ = renderContextBak;
    EXPECT_EQ(rect.size.Width(), 0.0f);
}

/**
 * @tc.name: InspectorTestNg011
 * @tc.desc: Test the operation of GetSubWindowInspector
 * @tc.type: FUNC
 */
HWTEST_F(InspectorTestNg, InspectorTestNg011, TestSize.Level1)
{
    auto id = ElementRegister::GetInstance()->MakeUniqueId();
    RefPtr<FrameNode> ONE = FrameNode::CreateFrameNode("one", id, AceType::MakeRefPtr<Pattern>(), true);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->stageManager_ = AceType::MakeRefPtr<StageManager>(ONE);
    auto pageRootNode = context->GetStageManager()->GetLastPage();
    auto test = Inspector::GetSubWindowInspector(false);
    auto str = "";
    EXPECT_NE(test, str);
    context->stageManager_ = nullptr;
}

/**
 * @tc.name: InspectorTestNg012
 * @tc.desc: Test the operation of GetSimplifiedInspector
 * @tc.type: FUNC
 */
HWTEST_F(InspectorTestNg, InspectorTestNg012, TestSize.Level1)
{
    auto id = ElementRegister::GetInstance()->MakeUniqueId();
    RefPtr<FrameNode> ONE = FrameNode::CreateFrameNode("one", id, AceType::MakeRefPtr<Pattern>(), true);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->stageManager_ = AceType::MakeRefPtr<StageManager>(ONE);
    int32_t containerId = 1;
    std::string result = Inspector::GetSimplifiedInspector(containerId);
    EXPECT_NE(result, "");
    context->stageManager_ = nullptr;
}

/**
 * @tc.name: InspectorTestNg013
 * @tc.desc: Test the function of InspectorFilter
 * @tc.type: FUNC
 */
HWTEST_F(InspectorTestNg, InspectorTestNg013, TestSize.Level1)
{
    const char* hello = "hi";
    InspectorFilter testFilter;
    EXPECT_EQ(testFilter.CheckFilterAttr(FixedAttrBit::FIXED_ATTR_CONTENT, hello), true);
    testFilter.SetFilterDepth(1);
    std::string id = "id";
    testFilter.SetFilterID(id);
    testFilter.filterExt.emplace_back("abc");
    testFilter.AddFilterAttr("focusable");
    testFilter.AddFilterAttr("abc");
    testFilter.AddFilterAttr("def");
    EXPECT_EQ(testFilter.CheckFixedAttr(FixedAttrBit::FIXED_ATTR_CONTENT), false);
    EXPECT_EQ(testFilter.CheckExtAttr("zzz"), false);
    EXPECT_EQ(testFilter.CheckFilterAttr(FixedAttrBit::FIXED_ATTR_CONTENT, hello), false);
    EXPECT_EQ(testFilter.IsFastFilter(), false);
}

/**
 * @tc.name: InspectorTestNg014
 * @tc.desc: Test the function of InspectorFilter
 * @tc.type: FUNC
 */
HWTEST_F(InspectorTestNg, InspectorTestNg014, TestSize.Level1)
{
    const char* hello = "hi";
    InspectorFilter testFilter;
    testFilter.AddFilterAttr("focusable");
    EXPECT_EQ(testFilter.CheckFilterAttr(FixedAttrBit::FIXED_ATTR_FOCUSABLE, hello), true);
}

/**
 * @tc.name: InspectorTestNg015
 * @tc.desc: Test the function of InspectorFilter
 * @tc.type: FUNC
 */
HWTEST_F(InspectorTestNg, InspectorTestNg015, TestSize.Level1)
{
    const char* hello = "abc";
    InspectorFilter testFilter;
    testFilter.filterExt.emplace_back("abc");
    testFilter.AddFilterAttr("focusable");
    EXPECT_EQ(testFilter.CheckFilterAttr(FixedAttrBit::FIXED_ATTR_CONTENT, hello), true);
}

/**
 * @tc.name: InspectorTestNg016
 * @tc.desc: Test the operation of GetInspectorTree
 * @tc.type: FUNC
 */
HWTEST_F(InspectorTestNg, InspectorTestNg016, TestSize.Level1)
{
    // tc.steps: step1. callback GetInspectorTree
    // tc.expected: expect the function is run ok
    auto context1 = PipelineContext::GetCurrentContext();
    ASSERT_NE(context1, nullptr);

    auto id = ElementRegister::GetInstance()->MakeUniqueId();
    RefPtr<FrameNode> stageNode = FrameNode::CreateFrameNode("stage", id, AceType::MakeRefPtr<Pattern>(), true);
    context1->stageManager_ = AceType::MakeRefPtr<StageManager>(stageNode);

    // tc.steps: step2 add lastPage and create a frame node tree to lastPage
    auto id2 = ElementRegister::GetInstance()->MakeUniqueId();
    const RefPtr<FrameNode> lastPage = FrameNode::CreateFrameNode("two", id2, AceType::MakeRefPtr<Pattern>());
    stageNode->children_.clear();
    stageNode->AddChild(lastPage);
    auto stageParent = FrameNode::CreateFrameNode("stageParent", 5, AceType::MakeRefPtr<Pattern>(), true);
    stageParent->AddChild(stageNode);
    auto frameNode = FrameNode::CreateFrameNode("frameNode", 6, AceType::MakeRefPtr<Pattern>(), true);
    lastPage->AddChild(frameNode);
    frameNode->isActive_ = true;
    auto frameNode2 = FrameNode::CreateFrameNode("frameNode2", 62, AceType::MakeRefPtr<Pattern>(), true);
    lastPage->AddChild(frameNode2);
    frameNode2->isActive_ = false;
    auto frameNode3 = FrameNode::CreateFrameNode("frameNode3", 63, AceType::MakeRefPtr<Pattern>(), true);
    frameNode2->AddChild(frameNode3);
    NG::InspectorTreeMap treesInfos;
    Inspector::GetInspectorTree(treesInfos);
    EXPECT_TRUE(!treesInfos.empty());
    context1->stageManager_ = nullptr;
}

/**
 * @tc.name: AddOffscreenNode_001
 * @tc.desc: Test the operation of AddOffscreenNode
 * @tc.type: FUNC
 */
HWTEST_F(InspectorTestNg, AddOffscreenNode_001, TestSize.Level1)
{
    int32_t num = Inspector::offscreenNodes.size();
    RefPtr<FrameNode> one = nullptr;
    Inspector::AddOffscreenNode(one);
    EXPECT_EQ(Inspector::offscreenNodes.size(), num);

    auto id = ElementRegister::GetInstance()->MakeUniqueId();
    one = FrameNode::CreateFrameNode("one", id, AceType::MakeRefPtr<Pattern>(), true);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);

    context->stageManager_ = AceType::MakeRefPtr<StageManager>(one);
    num = Inspector::offscreenNodes.size();
    Inspector::AddOffscreenNode(one);
    EXPECT_EQ(Inspector::offscreenNodes.size(), num + 1);
    context->stageManager_ = nullptr;
}

/**
 * @tc.name: RemoveOffscreenNode_001
 * @tc.desc: Test the operation of RemoveOffscreenNode
 * @tc.type: FUNC
 */
HWTEST_F(InspectorTestNg, RemoveOffscreenNode_001, TestSize.Level1)
{
    int32_t num = Inspector::offscreenNodes.size();
    RefPtr<FrameNode> one = nullptr;
    Inspector::RemoveOffscreenNode(one);
    EXPECT_EQ(Inspector::offscreenNodes.size(), num);

    auto id = ElementRegister::GetInstance()->MakeUniqueId();
    one = FrameNode::CreateFrameNode("one", id, AceType::MakeRefPtr<Pattern>(), true);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->stageManager_ = AceType::MakeRefPtr<StageManager>(one);
    Inspector::AddOffscreenNode(one);
    num = Inspector::offscreenNodes.size();

    Inspector::RemoveOffscreenNode(one);
    EXPECT_EQ(Inspector::offscreenNodes.size(), num - 1);
    context->stageManager_ = nullptr;
}

/**
 * @tc.name: GetOffScreenTreeNodes_001
 * @tc.desc: Test the operation of GetOffScreenTreeNodes
 * @tc.type: FUNC
 */
HWTEST_F(InspectorTestNg, GetOffScreenTreeNodes_001, TestSize.Level1)
{
    auto id = ElementRegister::GetInstance()->MakeUniqueId();
    RefPtr<FrameNode> one = FrameNode::CreateFrameNode("one", id, AceType::MakeRefPtr<Pattern>(), true);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->stageManager_ = AceType::MakeRefPtr<StageManager>(one);
    Inspector::AddOffscreenNode(one);
    int32_t num = Inspector::offscreenNodes.size();
    NG::InspectorTreeMap offNodes;
    Inspector::GetOffScreenTreeNodes(offNodes);
    EXPECT_EQ(offNodes.size(), num);
    context->stageManager_ = nullptr;
}
} // namespace OHOS::Ace::NG
