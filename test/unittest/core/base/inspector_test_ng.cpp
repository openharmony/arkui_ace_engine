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
std::string key = "key";
const std::string TEXT_NODE_TYPE = "Text";
const std::string TEST_TEXT = "SomeText";
const char INSPECTOR_TYPE[] = "$type";
const char INSPECTOR_ID[] = "$ID";
const char INSPECTOR_DEBUGLINE[] = "$debugLine";
const char INSPECTOR_ATTRS[] = "$attrs";
const char INSPECTOR_CHILDREN[] = "$children";

class InspectorTestNode : public UINode {
    DECLARE_ACE_TYPE(InspectorTestNode, UINode);

public:
    static RefPtr<InspectorTestNode> CreateTestNode(int32_t nodeId)
    {
        auto node = MakeRefPtr<InspectorTestNode>(nodeId);
        return node;
    }

    bool IsAtomicNode() const override
    {
        return true;
    }

    explicit InspectorTestNode(int32_t nodeId) : UINode("InspectorTestNode", nodeId) {}
    ~InspectorTestNode() override = default;
};
}; // namespace

class MockStageManager : public StageManager {
public:
    explicit MockStageManager(const RefPtr<FrameNode>& stage)
        : StageManager(stage)
    {}

    ~MockStageManager() override = default;

    MOCK_METHOD(RefPtr<FrameNode>, GetLastPage, (), (const));
};

class MockOverlayManager : public OverlayManager {
public:
    explicit MockOverlayManager(const RefPtr<FrameNode>& rootNode)
        : OverlayManager(rootNode)
    {}

    ~MockOverlayManager() override = default;

    MOCK_METHOD(const WeakPtr<UINode>, GetRootNode, (), (const));
};

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
 * @tc.name: InspectorTestNg017
 * @tc.desc: Test the operation of GetFrameNodeByKey
 * @tc.type: FUNC
 */
HWTEST_F(InspectorTestNg, InspectorTestNg017, TestSize.Level1)
{
    // tc.steps: step1. add frameNode to arkui tree with inspector id text1
    // tc.expected: expect the function GetFrameNodeByKey get the frameNode
    std::string inspectorId = "text1";
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    frameNode->UpdateInspectorId(inspectorId);
    auto context = PipelineContext::GetCurrentContext();
    context->rootNode_ = rootNode;
    rootNode->AddChild(frameNode);
    auto searchedNode = Inspector::GetFrameNodeByKey(inspectorId);
    EXPECT_EQ(frameNode, searchedNode);
    
    // tc.steps:    add offScreencreenNode to off screencreen node with inspector id text1
    // tc.expected: expect the function GetFrameNodeByKey get the offScreencreenNode
    auto offScreencreenNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    offScreencreenNode->UpdateInspectorId(inspectorId);
    Inspector::AddOffscreenNode(offScreencreenNode);
    searchedNode = Inspector::GetFrameNodeByKey(inspectorId);
    EXPECT_EQ(offScreencreenNode, searchedNode);
    
    // tc.steps:    execute GetFrameNodeByKey when skipoffscreenNodes set true
    // tc.expected: expect the function GetFrameNodeByKey get the frameNode
    searchedNode = Inspector::GetFrameNodeByKey(inspectorId, false, true);
    EXPECT_EQ(frameNode, searchedNode);
    
    // tc.steps:    execute GetFrameNodeByKey when remove offScreencreenNode
    // tc.expected: expect the function GetFrameNodeByKey get the frameNode
    Inspector::RemoveOffscreenNode(offScreencreenNode);
    searchedNode = Inspector::GetFrameNodeByKey(inspectorId);
    EXPECT_EQ(frameNode, searchedNode);
}

/**
 * @tc.name: InspectorTestNg018
 * @tc.desc: Test the operation of GetInspectorNodeByKey
 * @tc.type: FUNC
 */
HWTEST_F(InspectorTestNg, InspectorTestNg018, TestSize.Level1)
{
    // tc.steps: step1. add frameNode to arkui tree with inspector id text1
    // tc.expected: expect the function GetInspectorNodeByKey get the frameNode
    std::string inspectorId = "text1";
    int32_t textNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        textNodeId, AceType::MakeRefPtr<Pattern>());
    frameNode->UpdateInspectorId(inspectorId);
    auto context = PipelineContext::GetCurrentContext();
    context->rootNode_ = rootNode;
    rootNode->AddChild(frameNode);
    std::string searchedNodeStr = Inspector::GetInspectorNodeByKey(inspectorId);
    auto searchedNode = JsonUtil::ParseJsonString(searchedNodeStr);
    EXPECT_TRUE(searchedNode->IsValid());
    
    std::string nodeType = searchedNode->GetString(INSPECTOR_TYPE);
    EXPECT_EQ(nodeType, TEXT_NODE_TYPE);
    
    int32_t nodeId = searchedNode->GetInt(INSPECTOR_ID);
    EXPECT_EQ(textNodeId, nodeId);
    
    std::string debugLine = searchedNode->GetString(INSPECTOR_DEBUGLINE);
    EXPECT_EQ(debugLine, "");
    
    auto attrJson = searchedNode->GetObject(INSPECTOR_ATTRS);
    std::string accessibilityTextAttr = attrJson->GetString("accessibilityText");
    EXPECT_EQ(accessibilityTextAttr, "");
    
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    accessibilityProperty->SetAccessibilityText(TEST_TEXT);
    searchedNodeStr = Inspector::GetInspectorNodeByKey(inspectorId);
    searchedNode = JsonUtil::ParseJsonString(searchedNodeStr);
    EXPECT_TRUE(searchedNode->IsValid());
    attrJson = searchedNode->GetObject(INSPECTOR_ATTRS);
    accessibilityTextAttr = attrJson->GetString("accessibilityText");
    EXPECT_EQ(accessibilityTextAttr, TEST_TEXT);
}

/**
 * @tc.name: InspectorTestNg020
 * @tc.desc: Test the operation of GetInspector
 * @tc.type: FUNC
 */
HWTEST_F(InspectorTestNg, InspectorTestNg020, TestSize.Level1)
{
    auto context = PipelineContext::GetCurrentContext();
    RefPtr<FrameNode> stageNode = FrameNode::CreateFrameNode(
        "stage", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    context->stageManager_ = AceType::MakeRefPtr<StageManager>(stageNode);
    const RefPtr<FrameNode> PAGE = FrameNode::CreateFrameNode(
        "page", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    auto customNode = CustomNode::CreateCustomNode(1, "custom");
    stageNode->AddChild(PAGE);
    PAGE->AddChild(customNode);

    // tc.steps:    execute GetInspector when param isLayoutInspector is false
    // tc.expected: expect the function GetInspector result without customNode
    std::string searchedNodesStr = Inspector::GetInspector();
    auto searchedNodes = JsonUtil::ParseJsonString(searchedNodesStr);
    EXPECT_TRUE(searchedNodes->IsValid());
    auto attrJson = searchedNodes->GetObject(INSPECTOR_CHILDREN);
    EXPECT_TRUE(attrJson->IsNull());
}

/**
 * @tc.name: InspectorTestNg021
 * @tc.desc: Test the operation of ParseWindowIdFromMsg
 * @tc.type: FUNC
 */
HWTEST_F(InspectorTestNg, InspectorTestNg021, TestSize.Level1)
{
    std::string inspectorMsg = "";
    auto result = Inspector::ParseWindowIdFromMsg(inspectorMsg);
    EXPECT_EQ(result.first, 0);
    EXPECT_EQ(result.second, -1);

    inspectorMsg = "invalid message";
    result = Inspector::ParseWindowIdFromMsg(inspectorMsg);
    EXPECT_EQ(result.first, 0);
    EXPECT_EQ(result.second, -1);

    inspectorMsg = "{\"method\":\"ArkUI.xxx\", \"params\":{\"windowId\":\"10\"}}";
    result = Inspector::ParseWindowIdFromMsg(inspectorMsg);
    EXPECT_EQ(result.first, 0);
    EXPECT_EQ(result.second, -1);

    inspectorMsg = "{\"method\":\"ArkUI.tree\", \"params\":{\"windowIds\":\"10\"}}";
    result = Inspector::ParseWindowIdFromMsg(inspectorMsg);
    EXPECT_EQ(result.first, 0);
    EXPECT_EQ(result.second, 0);

    inspectorMsg = "{\"method\":\"ArkUI.tree\", \"paramss\":{\"windowId\":\"10\"}}";
    result = Inspector::ParseWindowIdFromMsg(inspectorMsg);
    EXPECT_EQ(result.first, 0);
    EXPECT_EQ(result.second, 0);

    inspectorMsg = "{\"method\":\"ArkUI.tree\", \"params\":{\"windowId\":\"10\"}}";
    result = Inspector::ParseWindowIdFromMsg(inspectorMsg);
    EXPECT_EQ(result.first, 10);
    EXPECT_EQ(result.second, 0);

    inspectorMsg = "{\"method\":\"ArkUI.tree.3D\", \"params\":{\"windowId\":\"10\"}}";
    result = Inspector::ParseWindowIdFromMsg(inspectorMsg);
    EXPECT_EQ(result.first, 10);
    EXPECT_EQ(result.second, 1);
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

/**
 * @tc.name: GetRecordAllPagesNodes_001
 * @tc.desc: Test the operation of GetRecordAllPagesNodes
 * (stageNode)--PageA--PageB--PageC
 *                              |--frameNode
 *                              |--frameNode1--frameNode3
 *                              |--frameNode2
 * @tc.type: FUNC
 */
HWTEST_F(InspectorTestNg, GetRecordAllPagesNodes_001, TestSize.Level1)
{
    // tc.steps: step1. call GetRecordAllPagesNodes
    // tc.expected: expect the function is run ok
    auto context1 = PipelineContext::GetCurrentContext();
    ASSERT_NE(context1, nullptr);

    auto id = ElementRegister::GetInstance()->MakeUniqueId();
    RefPtr<FrameNode> stageNode = FrameNode::CreateFrameNode("sageNode", id, AceType::MakeRefPtr<Pattern>(), true);
    context1->stageManager_ = AceType::MakeRefPtr<StageManager>(stageNode);
    stageNode->children_.clear();

    // tc.steps: step2 add lastPage and create a frame node tree to lastPage
    auto id2 = ElementRegister::GetInstance()->MakeUniqueId();
    const RefPtr<FrameNode> pageA = FrameNode::CreateFrameNode("PageA", id2,
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    stageNode->AddChild(pageA);
    auto id3 = ElementRegister::GetInstance()->MakeUniqueId();
    const RefPtr<FrameNode> pageB = FrameNode::CreateFrameNode("PageB", id3,
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    stageNode->AddChild(pageB);
    auto id4 = ElementRegister::GetInstance()->MakeUniqueId();
    const RefPtr<FrameNode> pageC = FrameNode::CreateFrameNode("PageC", id4,
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    stageNode->AddChild(pageC);

    auto frameNode = FrameNode::CreateFrameNode("frameNode0", 5, AceType::MakeRefPtr<Pattern>(), true);
    pageC->AddChild(frameNode);
    auto frameNode1 = FrameNode::CreateFrameNode("frameNode1", 6, AceType::MakeRefPtr<Pattern>(), true);
    pageC->AddChild(frameNode1);
    auto frameNode2 = FrameNode::CreateFrameNode("frameNode2", 62, AceType::MakeRefPtr<Pattern>(), true);
    pageC->AddChild(frameNode2);
    frameNode2->isActive_ = false;
    auto frameNode3 = FrameNode::CreateFrameNode("frameNode3", 63, AceType::MakeRefPtr<Pattern>(), true);
    frameNode1->AddChild(frameNode3);
    frameNode3->isActive_ = true;
    NG::InspectorTreeMap treesInfos;
    Inspector::GetRecordAllPagesNodes(treesInfos);
    EXPECT_TRUE(!treesInfos.empty());
    context1->stageManager_ = nullptr;
    auto node3 = treesInfos[63];
    EXPECT_TRUE(node3 != nullptr);
    EXPECT_EQ(node3->GetParentId(), 6);
}

HWTEST_F(InspectorTestNg, GetRecordAllPagesNodes_002, TestSize.Level1)
{
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    // STEP1:Create stageNode->pageA->frameNode
    RefPtr<FrameNode> stageNode = FrameNode::CreateFrameNode("stageNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    context->stageManager_ = AceType::MakeRefPtr<StageManager>(stageNode);
    stageNode->children_.clear();
    const RefPtr<FrameNode> pageA = FrameNode::CreateFrameNode("pageA", 2,
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    stageNode->AddChild(pageA);
    auto frameNode = FrameNode::CreateFrameNode("frameNode0", 5, AceType::MakeRefPtr<Pattern>(), true);
    pageA->AddChild(frameNode);
    // STEP2:parent is CustomNode,stageNode->pageA->frameNode->customNode->customNodeChild
    auto customNode = CustomNode::CreateCustomNode(100, "custom");
    auto customNodeChild = FrameNode::CreateFrameNode("customNodeChild", 103, AceType::MakeRefPtr<Pattern>(), true);
    customNodeChild->isActive_ = true;
    customNode->AddChild(customNodeChild);
    frameNode->AddChild(customNode);
    // STEP3:parent is SpanNode,stageNode->pageA->frameNode->spanNode->spanNodeChild
    auto spanNode = SpanNode::GetOrCreateSpanNode(int32_t(101));
    auto spanNodeChild = FrameNode::CreateFrameNode("spanNodeChild", 104, AceType::MakeRefPtr<Pattern>(), true);
    spanNodeChild->isActive_ = true;
    spanNode->AddChild(spanNodeChild);
    frameNode->AddChild(spanNode);
    // STEP4:parent is TestNode,stageNode->pageA->frameNode->testNode->testNodeChild
    auto testNode = InspectorTestNode::CreateTestNode(102);
    auto testNodeChild = FrameNode::CreateFrameNode("testNodeChild", 105, AceType::MakeRefPtr<Pattern>(), true);
    testNodeChild->isActive_ = true;
    testNode->AddChild(testNodeChild);
    frameNode->AddChild(testNode);
    NG::InspectorTreeMap treesInfos;
    Inspector::GetRecordAllPagesNodes(treesInfos);
    auto treeNode = treesInfos[102];
    EXPECT_TRUE(treeNode == nullptr);
    treeNode = treesInfos[103];
    EXPECT_TRUE(treeNode != nullptr);
    EXPECT_EQ(treeNode->GetParentId(), 100);
    treeNode = treesInfos[104];
    EXPECT_TRUE(treeNode != nullptr);
    EXPECT_EQ(treeNode->GetParentId(), 101);
    treeNode = treesInfos[105];
    EXPECT_TRUE(treeNode != nullptr);
    EXPECT_EQ(treeNode->GetParentId(), 5);
}

/**
 * @tc.name: InspectorTestNg022
 * @tc.desc: Test the method GetInspectorChildrenInfo
 * @tc.type: FUNC
 */
HWTEST_F(InspectorTestNg, InspectorTestNg022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. test GetInspectorChildrenInfo
     */
    auto spanNode = SpanNode::GetOrCreateSpanNode(int32_t(191));
    NG::InspectorTreeMap treesInfos;
    EXPECT_TRUE(AceType::InstanceOf<SpanNode>(spanNode));
    Inspector::GetInspectorChildrenInfo(spanNode, treesInfos, 1, 1);

    auto customNode = CustomNode::CreateCustomNode(1, "custom");
    EXPECT_TRUE(AceType::InstanceOf<CustomNode>(customNode));
    Inspector::GetInspectorChildrenInfo(spanNode, treesInfos, 1, 1);

    Inspector::GetInspectorChildrenInfo(spanNode, treesInfos, 1, 0);
}

/**
 * @tc.name: InspectorTestNg023
 * @tc.desc: Test the method GetCustomNodeInfo
 * @tc.type: FUNC
 */
HWTEST_F(InspectorTestNg, InspectorTestNg023, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize context and create stage/page nodes
     * @tc.expected: Context should be valid, stage/page nodes created successfully
     */
    auto context = PipelineContext::GetCurrentContext();
    EXPECT_NE(context, nullptr);
    auto stageId = ElementRegister::GetInstance()->MakeUniqueId();
    auto stageNode = FrameNode::CreateFrameNode("stage", stageId, AceType::MakeRefPtr<Pattern>(), true);
    context->stageManager_ = AceType::MakeRefPtr<StageManager>(stageNode);
    auto pageNode = FrameNode::CreateFrameNode("page", 100, AceType::MakeRefPtr<Pattern>(), true);
    stageNode->AddChild(pageNode);

    /**
     * @tc.steps: step2. Build test node hierarchy
     */
    auto customNode = CustomNode::CreateCustomNode(101, V2::JS_VIEW_ETS_TAG);
    customNode->UpdateInspectorId("custom_node_id");
    customNode->extraInfo_ = { "pages", 15, 20 };
    pageNode->AddChild(customNode);
    auto frameNode = FrameNode::CreateFrameNode("button", 102, AceType::MakeRefPtr<Pattern>(), true);
    frameNode->tag_ = V2::JS_VIEW_ETS_TAG;
    customNode->AddChild(frameNode);
    auto customNode2 = CustomNode::CreateCustomNode(103, V2::JS_VIEW_ETS_TAG);
    frameNode->AddChild(customNode2);

    /**
     * @tc.steps: step3. Execute inspection with ID filter
     * @tc.expected: Should return valid JSON without error flag
     */
    bool needThrow = false;
    InspectorFilter filter;
    std::string id = "custom_node_id";
    filter.SetFilterID(id);
    std::string result = Inspector::GetInspector(true, filter, needThrow);
    EXPECT_FALSE(needThrow);

    /**
     * @tc.steps: step4. Verify frame node inspection data
     * @tc.expected: Should return non-empty valid JSON
     */
    auto resultFrameNode = Inspector::GetInspectorOfNode(frameNode);
    auto jsonFrameNode = JsonUtil::ParseJsonString(resultFrameNode);
    ASSERT_NE(resultFrameNode, "");
    EXPECT_STREQ(jsonFrameNode->GetValue(INSPECTOR_DEBUGLINE)->GetString().c_str(), "");

    /**
     * @tc.steps: step5. Verify CustomNode specific attributes
     * @tc.expected: CustomNode should show debug info, FrameNode as build-in type
     */
    auto jsonValue = JsonUtil::ParseJsonString(result);
    ASSERT_NE(jsonValue, nullptr);
    EXPECT_STREQ(jsonValue->GetValue("type")->GetString().c_str(), "root");
    auto content = jsonValue->GetValue("content");
    ASSERT_FALSE(content->IsNull());
    auto childrenArray = content->GetValue(INSPECTOR_CHILDREN);
    ASSERT_TRUE(childrenArray->IsArray());
    bool foundCustomNode = false;
    for (int32_t i = 0; i < childrenArray->GetArraySize(); ++i) {
        auto node = childrenArray->GetArrayItem(i);
        if (node->GetValue(INSPECTOR_ID)->GetInt() == 101) {
            auto debugLine = JsonUtil::ParseJsonString(node->GetValue(INSPECTOR_DEBUGLINE)->GetString());
            EXPECT_STREQ("pages(15:20)", debugLine->GetValue("$line")->GetString().c_str());
            foundCustomNode = true;
        } else if (node->GetValue(INSPECTOR_ID)->GetInt() == 102) {
            EXPECT_STREQ("build-in", node->GetValue("type")->GetString().c_str());
        }
    }
    EXPECT_TRUE(foundCustomNode);
    context->stageManager_ = nullptr;
}

/**
 * @tc.name: InspectorTestNg024
 * @tc.desc: Test the GetRectangleById
 * @tc.type: FUNC
 */
HWTEST_F(InspectorTestNg, InspectorTestNg024, TestSize.Level1)
{
    // tc.steps: step1. add frameNode to arkui tree with inspector id test
    // tc.expected: expect the function GetFrameNodeByKey get the frameNode
    std::string inspectorId = "test";
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    frameNode->UpdateInspectorId(inspectorId);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->rootNode_ = rootNode;
    context->rootNode_->SetGeometryNode(AceType::MakeRefPtr<GeometryNode>());
    rootNode->AddChild(frameNode);
    auto searchedNode = Inspector::GetFrameNodeByKey(inspectorId, true);
    EXPECT_NE(searchedNode, nullptr);

    OHOS::Ace::NG::Rectangle rect;
    Inspector::GetRectangleById(inspectorId, rect);
    EXPECT_EQ(rect.size.Width(), 0.0f);
    auto renderContext = searchedNode->GetRenderContext();
    EXPECT_NE(renderContext, nullptr);

    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    container->isDynamicRender_ = false;
    auto pipeline = searchedNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    Offset offfset(1.0, 1.0);
    pipeline->SetHostParentOffsetToWindow(Offset(offfset.GetX(), offfset.GetY()));

    Inspector::GetRectangleById(inspectorId, rect);
    EXPECT_EQ(rect.windowOffset, searchedNode->GetOffsetRelativeToWindow());

    container->isDynamicRender_ = true;
    container->uIContentType_ = UIContentType::UNDEFINED;
    Inspector::GetRectangleById(inspectorId, rect);
    EXPECT_EQ(rect.windowOffset, searchedNode->GetOffsetRelativeToWindow());

    container->uIContentType_ = UIContentType::DYNAMIC_COMPONENT;
    pipeline->GetHostParentOffsetToWindow();
    Inspector::GetRectangleById(inspectorId, rect);
    EXPECT_NE(rect.windowOffset, searchedNode->GetOffsetRelativeToWindow());
}

/**
 * @tc.name: InspectorTestNg025
 * @tc.desc: Test the GetRectangleById
 * @tc.type: FUNC
 */
HWTEST_F(InspectorTestNg, InspectorTestNg025, TestSize.Level1)
{
    // tc.steps: step1. add frameNode to arkui tree with inspector id test
    // tc.expected: expect the function GetFrameNodeByKey get the frameNode
    std::string inspectorId = "test";
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    frameNode->UpdateInspectorId(inspectorId);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->rootNode_ = rootNode;
    context->rootNode_->SetGeometryNode(AceType::MakeRefPtr<GeometryNode>());
    rootNode->AddChild(frameNode);
    auto searchedNode = Inspector::GetFrameNodeByKey(inspectorId, true);
    EXPECT_NE(searchedNode, nullptr);

    OHOS::Ace::NG::Rectangle rect;
    Inspector::GetRectangleById(inspectorId, rect);
    EXPECT_EQ(rect.size.Width(), 0.0f);
    auto renderContext = AceType::DynamicCast<MockRenderContext>(searchedNode->GetRenderContext());
    EXPECT_NE(renderContext, nullptr);

    const double halfDimension = 200.0;
    renderContext->paintRect_ = { 2.0f, 2.0f, 3.0f, 3.0f };
    DimensionOffset offset = DimensionOffset(
        Dimension(halfDimension, DimensionUnit::PX), Dimension(halfDimension, DimensionUnit::PX));
    renderContext->UpdateTransformCenter(offset);
    EXPECT_TRUE(renderContext->GetTransformCenter().has_value());
    Inspector::GetRectangleById(inspectorId, rect);
    EXPECT_EQ(rect.scale.centerX, offset.GetX().ConvertToVp());
    EXPECT_EQ(rect.scale.centerY, offset.GetY().ConvertToVp());

    offset = DimensionOffset(
        Dimension(halfDimension, DimensionUnit::PX), Dimension(halfDimension, DimensionUnit::PERCENT));
    renderContext->UpdateTransformCenter(offset);
    Inspector::GetRectangleById(inspectorId, rect);
    EXPECT_EQ(rect.scale.centerX, offset.GetX().ConvertToVp());
    EXPECT_NE(rect.scale.centerY, offset.GetY().ConvertToVp());

    offset = DimensionOffset(
        Dimension(halfDimension, DimensionUnit::PERCENT), Dimension(halfDimension, DimensionUnit::PERCENT));
    renderContext->UpdateTransformCenter(offset);
    Inspector::GetRectangleById(inspectorId, rect);
    EXPECT_NE(rect.scale.centerX, offset.GetX().ConvertToVp());
    EXPECT_NE(rect.scale.centerY, offset.GetY().ConvertToVp());
}

/**
 * @tc.name: InspectorTestNg026
 * @tc.desc: Test the GetRectangleById
 * @tc.type: FUNC
 */
HWTEST_F(InspectorTestNg, InspectorTestNg026, TestSize.Level1)
{
    // tc.steps: step1. add frameNode to arkui tree with inspector id test
    // tc.expected: expect the function GetFrameNodeByKey get the frameNode
    std::string inspectorId = "test";
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    frameNode->UpdateInspectorId(inspectorId);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->rootNode_ = rootNode;
    context->rootNode_->SetGeometryNode(AceType::MakeRefPtr<GeometryNode>());
    rootNode->AddChild(frameNode);
    auto searchedNode = Inspector::GetFrameNodeByKey(inspectorId, true);
    EXPECT_NE(searchedNode, nullptr);

    OHOS::Ace::NG::Rectangle rect;
    Inspector::GetRectangleById(inspectorId, rect);
    EXPECT_EQ(rect.size.Width(), 0.0f);
    auto renderContext = AceType::DynamicCast<MockRenderContext>(searchedNode->GetRenderContext());
    EXPECT_NE(renderContext, nullptr);

    CalcDimension x(30, DimensionUnit::VP);
    CalcDimension y(20, DimensionUnit::VP);
    CalcDimension z(20, DimensionUnit::VP);
    renderContext->UpdateTransformTranslate(TranslateOptions(x, y, z));
    Inspector::GetRectangleById(inspectorId, rect);
    EXPECT_EQ(rect.translate.x, x.ConvertToVp());
    EXPECT_EQ(rect.translate.y, y.ConvertToVp());

    CalcDimension x2(30, DimensionUnit::PERCENT);
    CalcDimension y2(20, DimensionUnit::PERCENT);
    CalcDimension z2(20, DimensionUnit::PERCENT);
    renderContext->UpdateTransformTranslate(TranslateOptions(x2, y2, z2));
    Inspector::GetRectangleById(inspectorId, rect);
    EXPECT_NE(rect.translate.x, x.ConvertToVp());
    EXPECT_NE(rect.translate.y, y.ConvertToVp());
}

/**
 * @tc.name: InspectorInvalid001
 * @tc.desc: Test the SendEventByKey
 * @tc.type: FUNC
 */
HWTEST_F(InspectorTestNg, InspectorInvalid001, TestSize.Level1)
{
    // 设置PipelineContext返回空指针
    RefPtr<MockPipelineContext> pipeline_bak = MockPipelineContext::pipeline_;
    MockPipelineContext::pipeline_ = nullptr;
    bool result = Inspector::SendEventByKey("testKey", 0, "");
    MockPipelineContext::pipeline_ = pipeline_bak;
    EXPECT_FALSE(result);
}

/**
 * @tc.name: InspectorInvalid002
 * @tc.desc: Test the SendEventByKey
 * @tc.type: FUNC
 */
HWTEST_F(InspectorTestNg, InspectorInvalid002, TestSize.Level1)
{
    auto context = PipelineContext::GetCurrentContext();
    auto rootNode = context->rootNode_;
    context->rootNode_ = nullptr;
    bool result = Inspector::SendEventByKey("testKey", 0, "");
    context->rootNode_ = rootNode;
    EXPECT_FALSE(result);
}

/**
 * @tc.name: InspectorInvalid003
 * @tc.desc: Test the operation of GetInspectorNodeByKey
 * @tc.type: FUNC
 */
HWTEST_F(InspectorTestNg, InspectorInvalid003, TestSize.Level1)
{
    // 设置PipelineContext返回空指针
    RefPtr<MockPipelineContext> pipeline_bak = MockPipelineContext::pipeline_;
    MockPipelineContext::pipeline_ = nullptr;
    std::string result = Inspector::GetInspectorNodeByKey("testKey");
    MockPipelineContext::pipeline_ = pipeline_bak;
    EXPECT_EQ(result, "");
}

/**
 * @tc.name: InspectorInvalid004
 * @tc.desc: Test the operation of GetInspectorNodeByKey
 * @tc.type: FUNC
 */
HWTEST_F(InspectorTestNg, InspectorInvalid004, TestSize.Level1)
{
    auto context = PipelineContext::GetCurrentContext();
    auto rootNode = context->rootNode_;
    context->rootNode_ = nullptr;
    std::string result = Inspector::GetInspectorNodeByKey("testKey");
    context->rootNode_ = rootNode;
    EXPECT_EQ(result, "");
}

/**
 * @tc.name: InspectorInvalid005
 * @tc.desc: Test the operation of GetRectangleById
 * @tc.type: FUNC
 */
HWTEST_F(InspectorTestNg, InspectorInvalid005, TestSize.Level1)
{
    // 设置PipelineContext返回空指针
    RefPtr<MockPipelineContext> pipeline_bak = MockPipelineContext::pipeline_;
    MockPipelineContext::pipeline_ = nullptr;
    OHOS::Ace::NG::Rectangle rect;
    Inspector::GetRectangleById("testKey", rect);
    MockPipelineContext::pipeline_ = pipeline_bak;
    EXPECT_EQ(rect.screenRect.height_, 0.0);
    EXPECT_EQ(rect.screenRect.width_, 0.0);
    EXPECT_EQ(rect.screenRect.x_, 0.0);
    EXPECT_EQ(rect.screenRect.y_, 0.0);
}

/**
 * @tc.name: InspectorInvalid006
 * @tc.desc: Test the operation of GetRectangleById
 * @tc.type: FUNC
 */
HWTEST_F(InspectorTestNg, InspectorInvalid006, TestSize.Level1)
{
    auto context = PipelineContext::GetCurrentContext();
    auto rootNode = context->rootNode_;
    context->rootNode_ = nullptr;
    OHOS::Ace::NG::Rectangle rect;
    Inspector::GetRectangleById("testKey", rect);
    context->rootNode_ = rootNode;
    EXPECT_EQ(rect.screenRect.height_, 0.0);
    EXPECT_EQ(rect.screenRect.width_, 0.0);
    EXPECT_EQ(rect.screenRect.x_, 0.0);
    EXPECT_EQ(rect.screenRect.y_, 0.0);
}

/**
 * @tc.name: InspectorInvalid007
 * @tc.desc: Test the operation of GetInspector
 * @tc.type: FUNC
 */
HWTEST_F(InspectorTestNg, InspectorInvalid007, TestSize.Level1)
{
    // 设置PipelineContext返回空指针
    RefPtr<MockPipelineContext> pipeline_bak = MockPipelineContext::pipeline_;
    MockPipelineContext::pipeline_ = nullptr;
    auto result = Inspector::GetInspector(false);
    MockPipelineContext::pipeline_ = pipeline_bak;
    EXPECT_EQ(result, "{\"$type\":\"root\"}");
}

/**
 * @tc.name: InspectorInvalid008
 * @tc.desc: Test the operation of GetInspector
 * @tc.type: FUNC
 */
HWTEST_F(InspectorTestNg, InspectorInvalid008, TestSize.Level1)
{
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    auto context = MockPipelineContext::GetCurrentContext();
    RefPtr<MockStageManager> stageManager = AceType::MakeRefPtr<MockStageManager>(stageNode);
    auto stageManagerBak = context->stageManager_;
    context->stageManager_ = stageManager;
    RefPtr<FrameNode> nullNode = nullptr;
    EXPECT_CALL(*stageManager, GetLastPage()).Times(1).WillOnce(Return(nullNode));
    auto result = Inspector::GetInspector(false);
    context->stageManager_ = stageManagerBak;
    EXPECT_EQ(result, "{\"$type\":\"root\",\"width\":\"720.000000\",\"height\":\"1280.000000\",\"$resolution\":\"1.000000\"}");
}

/**
 * @tc.name: InspectorInvalid009
 * @tc.desc: Test the operation of GetInspectorOfNode
 * @tc.type: FUNC
 */
HWTEST_F(InspectorTestNg, InspectorInvalid009, TestSize.Level1)
{
    // 设置PipelineContext返回空指针
    RefPtr<MockPipelineContext> pipeline_bak = MockPipelineContext::pipeline_;
    MockPipelineContext::pipeline_ = nullptr;
    auto frameNode = FrameNode::CreateFrameNode("button", 102, AceType::MakeRefPtr<Pattern>(), true);
    auto result = Inspector::GetInspectorOfNode(frameNode);
    MockPipelineContext::pipeline_ = pipeline_bak;
    EXPECT_EQ(result, "{}");
}

/**
 * @tc.name: InspectorInvalid010
 * @tc.desc: Test the operation of GetInspectorOfNode
 * @tc.type: FUNC
 */
HWTEST_F(InspectorTestNg, InspectorInvalid010, TestSize.Level1)
{
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    auto context = MockPipelineContext::GetCurrentContext();
    RefPtr<MockStageManager> stageManager = AceType::MakeRefPtr<MockStageManager>(stageNode);
    auto stageManagerBak = context->stageManager_;
    context->stageManager_ = stageManager;
    RefPtr<FrameNode> nullNode = nullptr;
    EXPECT_CALL(*stageManager, GetLastPage()).Times(1).WillOnce(Return(nullNode));
    auto frameNode = FrameNode::CreateFrameNode("button", 102, AceType::MakeRefPtr<Pattern>(), true);
    auto result = Inspector::GetInspectorOfNode(frameNode);
    context->stageManager_ = stageManagerBak;
    EXPECT_EQ(result, "{\"width\":\"720.000000\",\"height\":\"1280.000000\",\"$resolution\":\"1.000000\"}");
}

/**
 * @tc.name: InspectorInvalid011
 * @tc.desc: Test the operation of GetInspectorOfNode
 * @tc.type: FUNC
 */
HWTEST_F(InspectorTestNg, InspectorInvalid011, TestSize.Level1)
{
    auto result = Inspector::GetInspectorOfNode(nullptr);
    EXPECT_EQ(result, "{\"width\":\"720.000000\",\"height\":\"1280.000000\",\"$resolution\":\"1.000000\"}");
}

/**
 * @tc.name: InspectorInvalid012
 * @tc.desc: Test the operation of GetSubWindowInspector
 * @tc.type: FUNC
 */
HWTEST_F(InspectorTestNg, InspectorInvalid012, TestSize.Level1)
{
    // 设置PipelineContext返回空指针
    RefPtr<MockPipelineContext> pipeline_bak = MockPipelineContext::pipeline_;
    MockPipelineContext::pipeline_ = nullptr;
    auto result = Inspector::GetSubWindowInspector();
    MockPipelineContext::pipeline_ = pipeline_bak;
    EXPECT_EQ(result, "{\"$type\":\"root\"}");
}

/**
 * @tc.name: InspectorInvalid013
 * @tc.desc: Test the operation of GetSubWindowInspector
 * @tc.type: FUNC
 */
HWTEST_F(InspectorTestNg, InspectorInvalid013, TestSize.Level1)
{
    // auto rootNode = FrameNode::CreateFrameNode(
    //     V2::OVERLAY_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    auto context = MockPipelineContext::GetCurrentContext();
    RefPtr<MockOverlayManager> overlayManager = AceType::MakeRefPtr<MockOverlayManager>(nullptr);
    overlayManager->rootNodeWeak_ = nullptr;
    auto overlayManagerBak = context->overlayManager_;
    context->overlayManager_ = overlayManager;
    auto result = Inspector::GetSubWindowInspector();
    context->overlayManager_ = overlayManagerBak;
    EXPECT_EQ(result, "{\"$type\":\"root\",\"width\":\"720.000000\",\"height\":\"1280.000000\",\"$resolution\":\"1.000000\"}");
}

/**
 * @tc.name: InspectorInvalid014
 * @tc.desc: Test the operation of GetInspectorTree
 * @tc.type: FUNC
 */
HWTEST_F(InspectorTestNg, InspectorInvalid014, TestSize.Level1)
{
    // 设置PipelineContext返回空指针
    RefPtr<MockPipelineContext> pipeline_bak = MockPipelineContext::pipeline_;
    MockPipelineContext::pipeline_ = nullptr;
    NG::InspectorTreeMap treesInfos;
    Inspector::GetInspectorTree(treesInfos);
    EXPECT_TRUE(treesInfos.empty());
    MockPipelineContext::pipeline_ = pipeline_bak;
}

/**
 * @tc.name: InspectorInvalid015
 * @tc.desc: Test the operation of GetInspectorTree
 * @tc.type: FUNC
 */
HWTEST_F(InspectorTestNg, InspectorInvalid015, TestSize.Level1)
{
    // 设置StageManager返回空指针
    auto context = MockPipelineContext::GetCurrentContext();
    auto stageManagerBak = context->stageManager_;
    context->stageManager_ = nullptr;
    NG::InspectorTreeMap treesInfos;
    Inspector::GetInspectorTree(treesInfos);
    EXPECT_TRUE(treesInfos.empty());
    context->stageManager_ = stageManagerBak;
}

/**
 * @tc.name: InspectorInvalid016
 * @tc.desc: Test the operation of GetInspectorTree
 * @tc.type: FUNC
 */
HWTEST_F(InspectorTestNg, InspectorInvalid016, TestSize.Level1)
{
    // 设置StageManager GetLastPage方法返回空指针
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    auto context = MockPipelineContext::GetCurrentContext();
    RefPtr<MockStageManager> stageManager = AceType::MakeRefPtr<MockStageManager>(stageNode);
    auto stageManagerBak = context->stageManager_;
    context->stageManager_ = stageManager;
    RefPtr<FrameNode> nullNode = nullptr;
    EXPECT_CALL(*stageManager, GetLastPage()).Times(1).WillOnce(Return(nullNode));
    NG::InspectorTreeMap treesInfos;
    Inspector::GetInspectorTree(treesInfos);
    EXPECT_TRUE(treesInfos.empty());
    context->stageManager_ = stageManagerBak;
}

/**
 * @tc.name: InspectorInvalid017
 * @tc.desc: Test the operation of GetInspectorTree
 * @tc.type: FUNC
 */
HWTEST_F(InspectorTestNg, InspectorInvalid017, TestSize.Level1)
{
    // 设置PipelineContext返回空指针
    RefPtr<MockPipelineContext> pipeline_bak = MockPipelineContext::pipeline_;
    MockPipelineContext::pipeline_ = nullptr;
    NG::InspectorTreeMap treesInfos;
    Inspector::GetRecordAllPagesNodes(treesInfos);
    EXPECT_TRUE(treesInfos.empty());
    MockPipelineContext::pipeline_ = pipeline_bak;
}

/**
 * @tc.name: InspectorInvalid018
 * @tc.desc: Test the operation of GetInspectorTree
 * @tc.type: FUNC
 */
HWTEST_F(InspectorTestNg, InspectorInvalid018, TestSize.Level1)
{
    // 设置StageManager返回空指针
    auto context = MockPipelineContext::GetCurrentContext();
    auto stageManagerBak = context->stageManager_;
    context->stageManager_ = nullptr;
    NG::InspectorTreeMap treesInfos;
    Inspector::GetRecordAllPagesNodes(treesInfos);
    EXPECT_TRUE(treesInfos.empty());
    context->stageManager_ = stageManagerBak;
}

/**
 * @tc.name: InspectorInvalid019
 * @tc.desc: Test the operation of GetInspectorTree
 * @tc.type: FUNC
 */
HWTEST_F(InspectorTestNg, InspectorInvalid019, TestSize.Level1)
{
    // 设置StageManager GetStageNode方法返回空指针
    auto context = MockPipelineContext::GetCurrentContext();
    RefPtr<MockStageManager> stageManager = AceType::MakeRefPtr<MockStageManager>(nullptr);
    auto stageManagerBak = context->stageManager_;
    context->stageManager_ = stageManager;
    NG::InspectorTreeMap treesInfos;
    Inspector::GetInspectorTree(treesInfos);
    EXPECT_TRUE(treesInfos.empty());
    context->stageManager_ = stageManagerBak;
}

/**
 * @tc.name: InspectorFilterTest001
 * @tc.desc: Test the operation of FilterEmptyInitially
 * @tc.type: FUNC
 */
HWTEST_F(InspectorTestNg, InspectorFilterTest001, TestSize.Level1)
{
    auto filter = std::make_unique<InspectorFilter>();
    EXPECT_TRUE(filter->FilterEmpty());
}
 
/**
* @tc.name: InspectorFilterTest002
* @tc.desc: Test the operation of FilterEmptyInitially
* @tc.type: FUNC
*/
HWTEST_F(InspectorTestNg, InspectorFilterTest002, TestSize.Level1)
{
    auto filter = std::make_unique<InspectorFilter>();
    EXPECT_TRUE(filter->CheckFixedAttr(FIXED_ATTR_ID));
}

/**
* @tc.name: InspectorFilterTest003
* @tc.desc: Test the operation of FilterEmptyInitially
* @tc.type: FUNC
*/
HWTEST_F(InspectorTestNg, InspectorFilterTest003, TestSize.Level1)
{
    auto filter = std::make_unique<InspectorFilter>();
    EXPECT_TRUE(filter->CheckExtAttr("some_attr"));
}

/**
* @tc.name: InspectorFilterTest004
* @tc.desc: Test the operation of FilterEmptyInitially
* @tc.type: FUNC
*/
HWTEST_F(InspectorTestNg, InspectorFilterTest004, TestSize.Level1)
{
    auto filter = std::make_unique<InspectorFilter>();
    filter->AddFilterAttr("id");
    EXPECT_TRUE(filter->CheckFixedAttr(FIXED_ATTR_ID));
    EXPECT_FALSE(filter->CheckFixedAttr(FIXED_ATTR_CONTENT));
}

/**
* @tc.name: InspectorFilterTest005
* @tc.desc: Test the operation of FilterEmptyInitially
* @tc.type: FUNC
*/
HWTEST_F(InspectorTestNg, InspectorFilterTest005, TestSize.Level1)
{
    auto filter = std::make_unique<InspectorFilter>();
    filter->AddFilterAttr("id");
    filter->AddFilterAttr("content");
    
    EXPECT_TRUE(filter->CheckFixedAttr(FIXED_ATTR_ID));
    EXPECT_TRUE(filter->CheckFixedAttr(FIXED_ATTR_CONTENT));
    EXPECT_FALSE(filter->CheckFixedAttr(FIXED_ATTR_SRC));
}

/**
* @tc.name: InspectorFilterTest006
* @tc.desc: Test the operation of FilterEmptyInitially
* @tc.type: FUNC
*/
HWTEST_F(InspectorTestNg, InspectorFilterTest006, TestSize.Level1)
{
    auto filter = std::make_unique<InspectorFilter>();
    filter->AddFilterAttr("custom_attr");
    
    EXPECT_TRUE(filter->CheckExtAttr("custom_attr"));
    EXPECT_FALSE(filter->CheckExtAttr("other_attr"));
}

/**
* @tc.name: InspectorFilterTest007
* @tc.desc: Test the operation of FilterEmptyInitially
* @tc.type: FUNC
*/
HWTEST_F(InspectorTestNg, InspectorFilterTest007, TestSize.Level1)
{
    auto filter = std::make_unique<InspectorFilter>();
    filter->AddFilterAttr("id");
    
    EXPECT_TRUE(filter->CheckFilterAttr(FIXED_ATTR_ID, nullptr));
    EXPECT_FALSE(filter->CheckFilterAttr(FIXED_ATTR_CONTENT, nullptr));
}

/**
* @tc.name: InspectorFilterTest008
* @tc.desc: Test the operation of FilterEmptyInitially
* @tc.type: FUNC
*/
HWTEST_F(InspectorTestNg, InspectorFilterTest008, TestSize.Level1)
{
    auto filter = std::make_unique<InspectorFilter>();
    filter->AddFilterAttr("custom_attr");
    
    EXPECT_TRUE(filter->CheckFilterAttr(FIXED_ATTR_ID, "custom_attr"));
    EXPECT_FALSE(filter->CheckFilterAttr(FIXED_ATTR_ID, "other_attr"));
}

/**
* @tc.name: InspectorFilterTest009
* @tc.desc: Test the operation of FilterEmptyInitially
* @tc.type: FUNC
*/
HWTEST_F(InspectorTestNg, InspectorFilterTest009, TestSize.Level1)
{
    auto filter = std::make_unique<InspectorFilter>();
    filter->AddFilterAttr("id");
    filter->AddFilterAttr("content");
   
   EXPECT_TRUE(filter->IsFastFilter());
}

/**
* @tc.name: InspectorFilterTest010
* @tc.desc: Test the operation of FilterEmptyInitially
* @tc.type: FUNC
*/
HWTEST_F(InspectorTestNg, InspectorFilterTest010, TestSize.Level1)
{
    auto filter = std::make_unique<InspectorFilter>();
    filter->AddFilterAttr("custom_attr");
   
    EXPECT_FALSE(filter->IsFastFilter());
}

/**
* @tc.name: InspectorFilterTest011
* @tc.desc: Test the operation of FilterEmptyInitially
* @tc.type: FUNC
*/
HWTEST_F(InspectorTestNg, InspectorFilterTest011, TestSize.Level1)
{
    auto filter = std::make_unique<InspectorFilter>();
    std::string id = "test_id";
    filter->SetFilterID(id);
   
    EXPECT_EQ(id, filter->GetFilterID());
}

/**
* @tc.name: InspectorFilterTest012
* @tc.desc: Test the operation of FilterEmptyInitially
* @tc.type: FUNC
*/
HWTEST_F(InspectorTestNg, InspectorFilterTest012, TestSize.Level1)
{
    auto filter = std::make_unique<InspectorFilter>();
    size_t depth = 5;
    filter->SetFilterDepth(depth);
    EXPECT_EQ(depth, filter-> GetFilterDepth());
}

/**
* @tc.name: SimplifiedInspectorTest001
* @tc.desc: Test the operation of FilterEmptyInitially
* @tc.type: FUNC
*/
HWTEST_F(InspectorTestNg, SimplifiedInspectorTest001, TestSize.Level1)
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
            // EXPECT_EQ(*result, "{\"$type\":\"root\",\"width\":\"720.000000\",\"height\":\"1280.000000\",\"$resolution\":\"0.000000\",\"pageUrl\":\"page/Index\",\"navDstName\":\"\",\"$childrenCount\":1}");
        },
        false);
    inspector->GetInspectorBackgroundAsync(collector);
    auto result = collector->GetJson()->ToString();
    EXPECT_EQ(result, "{}");
    context->stageManager_ = nullptr;
}

/**
* @tc.name: SimplifiedInspectorTest002
* @tc.desc: Test the operation of FilterEmptyInitially
* @tc.type: FUNC
*/
HWTEST_F(InspectorTestNg, SimplifiedInspectorTest002, TestSize.Level1)
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
* @tc.name: SimplifiedInspectorTest003
* @tc.desc: Test the operation of FilterEmptyInitially
* @tc.type: FUNC
*/
HWTEST_F(InspectorTestNg, SimplifiedInspectorTest003, TestSize.Level1)
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
    EXPECT_TRUE(inspector->isBackground_);
    EXPECT_TRUE(inspector->isAsync_);
}

bool HasInternalIds(const std::unique_ptr<JsonValue>& children)
{
    auto hasInternalIds = false;
    CHECK_NULL_RETURN(children, false);
    for (size_t i = 0; i < children->GetArraySize(); i++) {
        auto child = children->GetArrayItem(i);
        if (child->GetValue("$type")->GetString() == "button") {
            auto internal = child->Contains("$INTERNAL_IDS");
            if (internal) {
                hasInternalIds = true;
                break;
            }
        }
    }
    return hasInternalIds;
}

/**
 * @tc.name: InspectorTestNg027
 * @tc.desc: Test the operation of GetInspector
 * @tc.type: FUNC
 */
HWTEST_F(InspectorTestNg, InspectorTestNg027, TestSize.Level1)
{
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);

    auto id = ElementRegister::GetInstance()->MakeUniqueId();
    RefPtr<FrameNode> stageNode = FrameNode::CreateFrameNode("sageNode", id, AceType::MakeRefPtr<Pattern>(), true);
    context->stageManager_ = AceType::MakeRefPtr<StageManager>(stageNode);
    stageNode->children_.clear();

    auto id2 = ElementRegister::GetInstance()->MakeUniqueId();
    const RefPtr<FrameNode> pageA = FrameNode::CreateFrameNode("PageA", id2,
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    stageNode->AddChild(pageA);
    auto id3 = ElementRegister::GetInstance()->MakeUniqueId();
    
    auto button = FrameNode::CreateFrameNode("button", id3, AceType::MakeRefPtr<Pattern>(), true);
    pageA->AddChild(button);

    auto id4 = ElementRegister::GetInstance()->MakeUniqueId();
    auto text = FrameNode::CreateFrameNode("text", id4, AceType::MakeRefPtr<Pattern>(), true);
    button->AddChild(text);
    button->isActive_ = true;

    std::string tree = Inspector::GetInspector();
    auto jsonRoot  = JsonUtil::ParseJsonString(tree);
    ASSERT_NE(jsonRoot, nullptr);
    
    auto children = jsonRoot->GetValue("$children");
    ASSERT_TRUE(children->IsArray());
    auto hasInternalIds = HasInternalIds(children);
    ASSERT_FALSE(hasInternalIds);

    text->SetInternal();
    tree = Inspector::GetInspector();
    jsonRoot  = JsonUtil::ParseJsonString(tree);
    ASSERT_NE(jsonRoot, nullptr);
    
    children = jsonRoot->GetValue("$children");
    ASSERT_TRUE(children->IsArray());
    hasInternalIds = HasInternalIds(children);
    ASSERT_TRUE(hasInternalIds);
}

/**
 * @tc.name: GetOverlayNode_001
 * @tc.desc: Test the operation of GetOverlayNode in stage  overlay
 * column
 *    |--stage
 *       |--PageA
 *         |--frameNode
 *    |--overlay
 * @tc.type: FUNC
 */
HWTEST_F(InspectorTestNg, GetOverlayNode_001, TestSize.Level1)
{
    // tc.steps: step1. build tree
    auto context1 = PipelineContext::GetCurrentContext();
    ASSERT_NE(context1, nullptr);
    auto id0 = ElementRegister::GetInstance()->MakeUniqueId();
    RefPtr<FrameNode> columnNode = FrameNode::CreateFrameNode("Column", id0, AceType::MakeRefPtr<Pattern>(), false);

    auto id = ElementRegister::GetInstance()->MakeUniqueId();
    RefPtr<FrameNode> stageNode = FrameNode::CreateFrameNode("stage", id, AceType::MakeRefPtr<Pattern>(), false);
    context1->stageManager_ = AceType::MakeRefPtr<StageManager>(stageNode);
    stageNode->children_.clear();
    columnNode->AddChild(stageNode);

    auto overlayNode = FrameNode::CreateFrameNode(
        "overlayNode", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), false);
    columnNode->AddChild(overlayNode);
    auto testNode = FrameNode::CreateFrameNode(
        "testNode", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), false);
    overlayNode->AddChild(testNode);

    // tc.steps: step2 GetOverlayNode in containermodal
    auto id2 = ElementRegister::GetInstance()->MakeUniqueId();
    const RefPtr<FrameNode> pageA = FrameNode::CreateFrameNode("PageA", id2,
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    stageNode->AddChild(pageA);

    auto frameNode = FrameNode::CreateFrameNode(
        "frameNode0", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), false);
    pageA->AddChild(frameNode);
    NG::InspectorTreeMap treesInfos;
    Inspector::GetInspectorTree(treesInfos);
    auto it = treesInfos.find(testNode->GetId());
    EXPECT_TRUE(it != treesInfos.end());

    context1->stageManager_ = nullptr;
}

/**
 * @tc.name: GetOverlayNode_001
 * @tc.desc: Test the operation of GetOverlayNode in containermodal  overlay
 * column
 *    |--ContainerModal
 *       |--stage
 *          |--PageA
 *             |--frameNode
 *    |--overlay
 * @tc.type: FUNC
 */
HWTEST_F(InspectorTestNg, GetOverlayNode_002, TestSize.Level1)
{
    // tc.steps: step1. build tree
    auto context1 = PipelineContext::GetCurrentContext();
    ASSERT_NE(context1, nullptr);

    auto columnNode = FrameNode::CreateFrameNode(
        "Column", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), false);

    auto id0 = ElementRegister::GetInstance()->MakeUniqueId();
    RefPtr<FrameNode> contianerNode
        = FrameNode::CreateFrameNode(V2::CONTAINER_MODAL_ETS_TAG, id0, AceType::MakeRefPtr<Pattern>(), false);
    columnNode->AddChild(contianerNode);

    auto id = ElementRegister::GetInstance()->MakeUniqueId();
    RefPtr<FrameNode> stageNode = FrameNode::CreateFrameNode("stage", id, AceType::MakeRefPtr<Pattern>(), false);
    context1->stageManager_ = AceType::MakeRefPtr<StageManager>(stageNode);
    stageNode->children_.clear();
    contianerNode->AddChild(stageNode);

    auto overlayNode = FrameNode::CreateFrameNode(
        "overlayNode", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), false);
    columnNode->AddChild(overlayNode);

    auto testNode = FrameNode::CreateFrameNode(
        "testNode", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), false);
    overlayNode->AddChild(testNode);

    // tc.steps: step2 GetOverlayNode in containermodal
    auto id2 = ElementRegister::GetInstance()->MakeUniqueId();
    const RefPtr<FrameNode> pageA = FrameNode::CreateFrameNode("PageA", id2,
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    stageNode->AddChild(pageA);

    auto frameNode = FrameNode::CreateFrameNode(
        "frameNode0", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), false);
    pageA->AddChild(frameNode);

    NG::InspectorTreeMap treesInfos;
    Inspector::GetInspectorTree(treesInfos);

    auto it = treesInfos.find(testNode->GetId());
    EXPECT_TRUE(it != treesInfos.end());

    context1->stageManager_ = nullptr;
}
} // namespace OHOS::Ace::NG
