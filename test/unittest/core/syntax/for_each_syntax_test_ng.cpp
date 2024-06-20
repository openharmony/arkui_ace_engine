/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include <utility>

#include "gtest/gtest.h"

#include "base/memory/ace_type.h"

#define private public
#define protected public
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/syntax/for_each_model_ng.h"
#include "core/components_ng/syntax/for_each_node.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string NODE_TAG("node");
const std::string LIST_TAG("List");
constexpr bool IS_ATOMIC_NODE = false;
const std::list<std::string> ID_ARRAY = { "0" };
const std::list<std::string> FOR_EACH_ARRAY = { "0", "1", "2", "3" };
const std::list<std::string> FOR_EACH_IDS = { "0", "1", "2", "3", "4", "5" };
constexpr int32_t FOR_EACH_NODE_ID = 1;
} // namespace

class ForEachSyntaxTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void ForEachSyntaxTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void ForEachSyntaxTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

void SetOnMoveTestNg(int32_t a, int32_t b) {}

/**
 * @tc.name: ForEachSyntaxCreateTest001
 * @tc.desc: Create ForEach.
 * @tc.type: FUNC
 */
HWTEST_F(ForEachSyntaxTestNg, ForEachSyntaxTest001, TestSize.Level1)
{
    ForEachModelNG forEach;
    forEach.Create();
    auto forEachNode = AceType::DynamicCast<ForEachNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(forEachNode != nullptr && forEachNode->GetTag() == V2::JS_FOR_EACH_ETS_TAG);
    EXPECT_EQ(forEachNode->IsAtomicNode(), IS_ATOMIC_NODE);
}

/**
 * @tc.name: ForEachSyntaxTest002
 * @tc.desc: Create ForEach.
 * @tc.type: FUNC
 */
HWTEST_F(ForEachSyntaxTestNg, ForEachSyntaxTest002, TestSize.Level1)
{
    ForEachModelNG forEach;
    forEach.Create();
    forEach.Pop();
    auto node = ViewStackProcessor::GetInstance()->GetMainElementNode();
    // ViewStackProcessor will not pop when it's size equals 1.
    EXPECT_FALSE(ViewStackProcessor::GetInstance()->GetMainElementNode() == nullptr);
    // ViewStackProcessor will not pop when it's size equals 1.
    EXPECT_TRUE(ViewStackProcessor::GetInstance()->GetMainFrameNode() == nullptr);
}

/**
 * @tc.name: ForEachSyntaxIdTest003
 * @tc.desc: Create ForEach and set its ids.
 * @tc.type: FUNC
 */
HWTEST_F(ForEachSyntaxTestNg, ForEachSyntaxIdTest003, TestSize.Level1)
{
    ForEachModelNG forEach;
    forEach.Create();
    std::list<std::string> ids = FOR_EACH_IDS;
    forEach.SetNewIds(std::move(ids));

    auto forEachNode = AceType::DynamicCast<ForEachNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(forEachNode != nullptr && forEachNode->GetTag() == V2::JS_FOR_EACH_ETS_TAG);

    // tempIds_ is empty.
    auto tempIds = forEachNode->GetTempIds();
    EXPECT_TRUE(tempIds.empty());
    // CreateTempItems, swap ids_ and tempIds_.
    forEachNode->CreateTempItems();
    EXPECT_EQ(forEachNode->GetTempIds(), FOR_EACH_IDS);
}

/**
 * @tc.name: ForEachSyntaxUpdateTest004
 * @tc.desc: Create ForEach and update children.
 * @tc.type: FUNC
 */
HWTEST_F(ForEachSyntaxTestNg, ForEachSyntaxUpdateTest004, TestSize.Level1)
{
    ForEachModelNG forEach;
    forEach.Create();
    std::list<std::string> ids = FOR_EACH_IDS;
    forEach.SetNewIds(std::move(ids));

    auto forEachNode = AceType::DynamicCast<ForEachNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(forEachNode != nullptr && forEachNode->GetTag() == V2::JS_FOR_EACH_ETS_TAG);

    /**
    // corresponding ets code:
    //     ForEach(this.arr,
    //         (item: number) => {
    //             Blank()
    //         })
    */
    for (auto iter = FOR_EACH_ARRAY.begin(); iter != FOR_EACH_ARRAY.end(); iter++) {
        auto childFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
        forEachNode->AddChild(childFrameNode);
    }
    EXPECT_EQ(forEachNode->GetChildren().size(), FOR_EACH_ARRAY.size());

    // tempIds_ is empty.
    auto tempIds = forEachNode->GetTempIds();
    EXPECT_TRUE(tempIds.empty());
    // CreateTempItems, swap ids_ and tempIds_, children_ and tempChildren_.
    forEachNode->CreateTempItems();
    EXPECT_EQ(forEachNode->GetTempIds(), FOR_EACH_IDS);
}

/**
 * @tc.name: ForEachSyntaxUpdateTest005
 * @tc.desc: Create ForEach and update children.
 * @tc.type: FUNC
 */
HWTEST_F(ForEachSyntaxTestNg, ForEachSyntaxUpdateTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set branch id which is same as before.
     */
    ForEachModelNG forEach;
    forEach.Create();
    std::list<std::string> ids = FOR_EACH_ARRAY;
    forEach.SetNewIds(std::move(ids));
    auto forEachNode = AceType::DynamicCast<ForEachNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(forEachNode != nullptr && forEachNode->GetTag() == V2::JS_FOR_EACH_ETS_TAG);

    /**
     * @tc.steps: step2. CompareAndUpdateChildren when newIds and oldIds are same.
     */
    forEachNode->CreateTempItems();
    std::list<std::string> ids2 = ID_ARRAY;
    forEachNode->SetIds(std::move(ids2));
    forEachNode->onMainTree_ = true;
    auto node = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    forEachNode->SetParent(node);
    forEachNode->children_ = { node };
    forEachNode->CompareAndUpdateChildren();
    forEachNode->FlushUpdateAndMarkDirty();
    auto tempIds = forEachNode->GetTempIds();
    EXPECT_TRUE(tempIds.empty());
}

/**
 * @tc.name: ForEachSyntaxUpdateTest006
 * @tc.desc: FlushUpdateAndMarkDirty
 * @tc.type: FUNC
 */
HWTEST_F(ForEachSyntaxTestNg, ForEachSyntaxUpdateTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set branch id which is same as before.
     */
    ForEachModelNG forEach;
    forEach.Create();
    std::list<std::string> ids = FOR_EACH_ARRAY;
    forEach.SetNewIds(std::move(ids));
    auto forEachNode = AceType::DynamicCast<ForEachNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(forEachNode != nullptr && forEachNode->GetTag() == V2::JS_FOR_EACH_ETS_TAG);

    /**
     * @tc.steps: step2. CompareAndUpdateChildren when newIds and oldIds are same.
     */
    forEachNode->CreateTempItems();
    std::list<std::string> ids2 = ID_ARRAY;
    forEachNode->SetIds(std::move(ids2));
    forEachNode->onMainTree_ = true;
    auto node = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    forEachNode->SetParent(node);
    forEachNode->children_ = { node };
    forEachNode->CompareAndUpdateChildren();
    forEachNode->ids_ = forEachNode->tempIds_;
    forEachNode->FlushUpdateAndMarkDirty();
    auto tempIds = forEachNode->GetTempIds();
    EXPECT_TRUE(tempIds.empty());
}

/**
 * @tc.name: ForEachSyntaxCreateTest006
 * @tc.desc: Create ForEach with same node id.
 * @tc.type: FUNC
 */
HWTEST_F(ForEachSyntaxTestNg, ForEachSyntaxTest006, TestSize.Level1)
{
    auto forEachNode = ForEachNode::GetOrCreateForEachNode(FOR_EACH_NODE_ID);
    auto anotherForEachNode = ForEachNode::GetOrCreateForEachNode(FOR_EACH_NODE_ID);
    EXPECT_EQ(forEachNode, anotherForEachNode);
}

/**
 * @tc.name: ForEachSyntaxUpdateTest007
 * @tc.desc: Create ForEach and update children.
 * @tc.type: FUNC
 */
HWTEST_F(ForEachSyntaxTestNg, ForEachSyntaxUpdateTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set branch id which is same as before.
     */
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    ForEachModelNG forEach;
    forEach.Create();
    std::list<std::string> ids = FOR_EACH_ARRAY;
    forEach.SetNewIds(std::move(ids));
    auto forEachNode = AceType::DynamicCast<ForEachNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(forEachNode != nullptr && forEachNode->GetTag() == V2::JS_FOR_EACH_ETS_TAG);

    /**
     * @tc.steps: step2. CompareAndUpdateChildren when newIds and oldIds are same.
     */
    forEachNode->CreateTempItems();
    std::list<std::string> ids2 = FOR_EACH_IDS;
    forEachNode->SetIds(std::move(ids2));
    forEachNode->context_ = AceType::RawPtr(context);
    forEachNode->onMainTree_ = true;
    auto node = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    forEachNode->SetParent(node);
    auto childNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    forEachNode->children_ = { childNode };
    forEachNode->CompareAndUpdateChildren();
    forEachNode->FlushUpdateAndMarkDirty();
    auto tempIds = forEachNode->GetTempIds();
    EXPECT_TRUE(tempIds.empty());
}

/**
 * @tc.name: ForEachGetOrCreateRepeatNodeTest001
 * @tc.desc: Create ForEach and update children.
 * @tc.type: FUNC
 */
HWTEST_F(ForEachSyntaxTestNg, ForEachGetOrCreateRepeatNodeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set branch id which is same as before.
     */
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    ForEachModelNG forEach;
    forEach.Create();
    std::list<std::string> ids = FOR_EACH_ARRAY;
    forEach.SetNewIds(std::move(ids));
    auto forEachNode = AceType::DynamicCast<ForEachNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(forEachNode != nullptr && forEachNode->GetTag() == V2::JS_FOR_EACH_ETS_TAG);

    /**
     * @tc.steps: step2. CompareAndUpdateChildren when newIds and oldIds are same.
     */
    forEachNode->CreateTempItems();
    std::list<std::string> ids2 = FOR_EACH_IDS;
    forEachNode->SetIds(std::move(ids2));
    forEachNode->context_ = AceType::RawPtr(context);
    forEachNode->onMainTree_ = true;
    auto node = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    forEachNode->SetParent(node);
    auto childNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    forEachNode->children_ = { childNode };
    forEachNode->CompareAndUpdateChildren();
    forEachNode->FlushUpdateAndMarkDirty();
    forEachNode->GetOrCreateRepeatNode(0);
}

/**
 * @tc.name: ForEachCreateTempItemsTest001
 * @tc.desc: Create ForEach and update children.
 * @tc.type: FUNC
 */
HWTEST_F(ForEachSyntaxTestNg, ForEachCreateTempItemsTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set branch id which is same as before.
     */
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    ForEachModelNG forEach;
    forEach.Create();
    std::list<std::string> ids = FOR_EACH_ARRAY;
    forEach.SetNewIds(std::move(ids));
    auto forEachNode = AceType::DynamicCast<ForEachNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(forEachNode != nullptr && forEachNode->GetTag() == V2::JS_FOR_EACH_ETS_TAG);

    /**
     * @tc.steps: step2. CompareAndUpdateChildren when newIds and oldIds are same.
     */
    forEachNode->isThisRepeatNode_= true;
    forEachNode->CreateTempItems();
}

/**
 * @tc.name: ForEachCompareAndUpdateChildrenTest001
 * @tc.desc: Create ForEach and update children.
 * @tc.type: FUNC
 */
HWTEST_F(ForEachSyntaxTestNg, ForEachCompareAndUpdateChildrenTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set branch id which is same as before.
     */
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    ForEachModelNG forEach;
    forEach.Create();
    std::list<std::string> ids = FOR_EACH_ARRAY;
    forEach.SetNewIds(std::move(ids));
    auto forEachNode = AceType::DynamicCast<ForEachNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(forEachNode != nullptr && forEachNode->GetTag() == V2::JS_FOR_EACH_ETS_TAG);

    /**
     * @tc.steps: step2. CompareAndUpdateChildren when newIds and oldIds are same.
     */
    forEachNode->isThisRepeatNode_= true;
    forEachNode->CompareAndUpdateChildren();

    forEachNode->isThisRepeatNode_= false;
    forEachNode->CreateTempItems();
    std::list<std::string> ids2 = ID_ARRAY;
    forEachNode->SetIds(std::move(ids2));
    forEachNode->onMainTree_ = true;
    auto node = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    forEachNode->SetParent(node);
    forEachNode->children_ = { node };
    forEachNode->CompareAndUpdateChildren();
}

/**
 * @tc.name: ForEachFinishRepeatRenderTest001
 * @tc.desc: Create ForEach and update children.
 * @tc.type: FUNC
 */
HWTEST_F(ForEachSyntaxTestNg, ForEachFinishRepeatRenderTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set branch id which is same as before.
     */
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    ForEachModelNG forEach;
    forEach.Create();
    std::list<std::string> ids = FOR_EACH_ARRAY;
    forEach.SetNewIds(std::move(ids));
    auto forEachNode = AceType::DynamicCast<ForEachNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(forEachNode != nullptr && forEachNode->GetTag() == V2::JS_FOR_EACH_ETS_TAG);

    /**
     * @tc.steps: step2. CompareAndUpdateChildren when newIds and oldIds are same.
     */
    
    for (auto iter = FOR_EACH_ARRAY.begin(); iter != FOR_EACH_ARRAY.end(); iter++) {
        auto childFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
        forEachNode->AddChild(childFrameNode);
    }
    forEachNode->isThisRepeatNode_= true;
    forEachNode->CreateTempItems();
    std::list<std::string> ids2 = ID_ARRAY;
    forEachNode->SetIds(std::move(ids2));
    forEachNode->onMainTree_ = true;
    auto node = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    forEachNode->SetParent(node);
    forEachNode->children_ = { node };
    forEachNode->CompareAndUpdateChildren();
    forEachNode->FlushUpdateAndMarkDirty();
    std::list<int32_t> arr;
    arr.push_back(0);
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    arr.push_back(4);
    forEachNode->FinishRepeatRender(arr);
}

/**
 * @tc.name: ForEachMoveChildTest001
 * @tc.desc: Create ForEach and update children.
 * @tc.type: FUNC
 */
HWTEST_F(ForEachSyntaxTestNg, ForEachMoveChildTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set branch id which is same as before.
     */
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    ForEachModelNG forEach;
    forEach.Create();
    std::list<std::string> ids = FOR_EACH_ARRAY;
    forEach.SetNewIds(std::move(ids));
    auto forEachNode = AceType::DynamicCast<ForEachNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(forEachNode != nullptr && forEachNode->GetTag() == V2::JS_FOR_EACH_ETS_TAG);

    /**
     * @tc.steps: step2. CompareAndUpdateChildren when newIds and oldIds are same.
     */
    
    for (auto iter = FOR_EACH_ARRAY.begin(); iter != FOR_EACH_ARRAY.end(); iter++) {
        auto childFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
        forEachNode->AddChild(childFrameNode);
    }
    forEachNode->isThisRepeatNode_= true;
    forEachNode->CreateTempItems();
    std::list<std::string> ids2 = ID_ARRAY;
    forEachNode->SetIds(std::move(ids2));
    forEachNode->onMainTree_ = true;
    auto node = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    forEachNode->SetParent(node);
    forEachNode->children_ = { node };
    forEachNode->CompareAndUpdateChildren();
    forEachNode->FlushUpdateAndMarkDirty();
    forEachNode->MoveChild(1);
    forEachNode->MoveChild(4);
}

/**
 * @tc.name: ForEachSetOnMoveTest001
 * @tc.desc: Create ForEach and update children.
 * @tc.type: FUNC
 */
HWTEST_F(ForEachSyntaxTestNg, ForEachSetOnMoveTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set branch id which is same as before.
     */
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    ForEachModelNG forEach;
    forEach.Create();
    std::list<std::string> ids = FOR_EACH_ARRAY;
    forEach.SetNewIds(std::move(ids));
    auto forEachNode = AceType::DynamicCast<ForEachNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(forEachNode != nullptr && forEachNode->GetTag() == V2::JS_FOR_EACH_ETS_TAG);

    /**
     * @tc.steps: step2. CompareAndUpdateChildren when newIds and oldIds are same.
     */
    
    forEachNode->SetOnMove(SetOnMoveTestNg);
    
    for (auto iter = FOR_EACH_ARRAY.begin(); iter != FOR_EACH_ARRAY.end(); iter++) {
        auto childFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
        forEachNode->AddChild(childFrameNode);
    }
    forEachNode->isThisRepeatNode_= true;
    forEachNode->CreateTempItems();
    std::list<std::string> ids2 = ID_ARRAY;
    forEachNode->SetIds(std::move(ids2));
    forEachNode->onMainTree_ = true;
    auto node = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    forEachNode->SetParent(node);
    forEachNode->children_ = { node };
    forEachNode->CompareAndUpdateChildren();
    forEachNode->FlushUpdateAndMarkDirty();
    forEachNode->SetOnMove(SetOnMoveTestNg);
    forEachNode->SetOnMove(nullptr);
}

/**
 * @tc.name: ForEachMoveDataTest001
 * @tc.desc: Create ForEach and update children.
 * @tc.type: FUNC
 */
HWTEST_F(ForEachSyntaxTestNg, ForEachMoveDataTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set branch id which is same as before.
     */
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    ForEachModelNG forEach;
    forEach.Create();
    std::list<std::string> ids = FOR_EACH_ARRAY;
    forEach.SetNewIds(std::move(ids));
    auto forEachNode = AceType::DynamicCast<ForEachNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(forEachNode != nullptr && forEachNode->GetTag() == V2::JS_FOR_EACH_ETS_TAG);

    /**
     * @tc.steps: step2. CompareAndUpdateChildren when newIds and oldIds are same.
     */
    
    for (auto iter = FOR_EACH_ARRAY.begin(); iter != FOR_EACH_ARRAY.end(); iter++) {
        auto childFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
        forEachNode->AddChild(childFrameNode);
    }
    forEachNode->isThisRepeatNode_= true;
    forEachNode->CreateTempItems();
    std::list<std::string> ids2 = ID_ARRAY;
    forEachNode->SetIds(std::move(ids2));
    forEachNode->onMainTree_ = true;
    auto node = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    forEachNode->SetParent(node);
    forEachNode->children_ = { node };
    forEachNode->CompareAndUpdateChildren();
    forEachNode->FlushUpdateAndMarkDirty();
    forEachNode->MoveData(0, 5);
    forEachNode->MoveData(1, 1);
}

/**
 * @tc.name: ForEachGetFrameNodeTest001
 * @tc.desc: Create ForEach and update children.
 * @tc.type: FUNC
 */
HWTEST_F(ForEachSyntaxTestNg, ForEachGetFrameNodeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set branch id which is same as before.
     */
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    ForEachModelNG forEach;
    forEach.Create();
    std::list<std::string> ids = FOR_EACH_ARRAY;
    forEach.SetNewIds(std::move(ids));
    auto forEachNode = AceType::DynamicCast<ForEachNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(forEachNode != nullptr && forEachNode->GetTag() == V2::JS_FOR_EACH_ETS_TAG);

    /**
     * @tc.steps: step2. CompareAndUpdateChildren when newIds and oldIds are same.
     */
   
    forEachNode->GetFrameNode(1);
}

/**
 * @tc.name: ForEachInitDragManagerTest001
 * @tc.desc: Create ForEach and update children.
 * @tc.type: FUNC
 */
HWTEST_F(ForEachSyntaxTestNg, ForEachInitDragManagerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set branch id which is same as before.
     */
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    ForEachModelNG forEach;
    forEach.Create();
    std::list<std::string> ids = FOR_EACH_ARRAY;
    forEach.SetNewIds(std::move(ids));
    auto forEachNode = AceType::DynamicCast<ForEachNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(forEachNode != nullptr && forEachNode->GetTag() == V2::JS_FOR_EACH_ETS_TAG);

    /**
     * @tc.steps: step2. CompareAndUpdateChildren when newIds and oldIds are same.
     */
   
    for (auto iter = FOR_EACH_ARRAY.begin(); iter != FOR_EACH_ARRAY.end(); iter++) {
        auto childFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
        forEachNode->AddChild(childFrameNode);
    }
    forEachNode->isThisRepeatNode_= true;
    forEachNode->CreateTempItems();
    std::list<std::string> ids2 = ID_ARRAY;
    forEachNode->SetIds(std::move(ids2));
    forEachNode->onMainTree_ = true;
    auto list_tag = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    forEachNode->SetParent(list_tag);
    forEachNode->children_ = { list_tag };
    forEachNode->CompareAndUpdateChildren();
    forEachNode->FlushUpdateAndMarkDirty();
    forEachNode->SetOnMove(SetOnMoveTestNg);
    forEachNode->InitDragManager(list_tag);
    
    auto node_tag = AceType::MakeRefPtr<FrameNode>(LIST_TAG, -1, AceType::MakeRefPtr<Pattern>());
    forEachNode->SetParent(node_tag);
    forEachNode->children_ = { node_tag };
    forEachNode->CompareAndUpdateChildren();
    forEachNode->FlushUpdateAndMarkDirty();
    forEachNode->SetOnMove(SetOnMoveTestNg);
    forEachNode->InitDragManager(node_tag);
}

/**
 * @tc.name: ForEachInitAllChildrenDragManagerTest001
 * @tc.desc: Create ForEach and update children.
 * @tc.type: FUNC
 */
HWTEST_F(ForEachSyntaxTestNg, ForEachInitAllChildrenDragManagerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set branch id which is same as before.
     */
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    ForEachModelNG forEach;
    forEach.Create();
    std::list<std::string> ids = FOR_EACH_ARRAY;
    forEach.SetNewIds(std::move(ids));
    auto forEachNode = AceType::DynamicCast<ForEachNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(forEachNode != nullptr && forEachNode->GetTag() == V2::JS_FOR_EACH_ETS_TAG);

    /**
     * @tc.steps: step2. CompareAndUpdateChildren when newIds and oldIds are same.
     */
   
    for (auto iter = FOR_EACH_ARRAY.begin(); iter != FOR_EACH_ARRAY.end(); iter++) {
        auto childFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
        forEachNode->AddChild(childFrameNode);
    }
    forEachNode->isThisRepeatNode_= true;
    forEachNode->CreateTempItems();
    std::list<std::string> ids2 = ID_ARRAY;
    forEachNode->SetIds(std::move(ids2));
    forEachNode->onMainTree_ = true;
    auto childFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    auto list_tag = AceType::MakeRefPtr<FrameNode>(LIST_TAG, -1, AceType::MakeRefPtr<Pattern>());
    list_tag->AddChild(childFrameNode, DEFAULT_NODE_SLOT, true);
    forEachNode->SetParent(list_tag);
    forEachNode->children_ = { list_tag };
    forEachNode->CompareAndUpdateChildren();
    forEachNode->FlushUpdateAndMarkDirty();
    forEachNode->SetOnMove(SetOnMoveTestNg);
    forEachNode->InitAllChildrenDragManager(true);
    
    auto node_tag = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    forEachNode->SetParent(node_tag);
    forEachNode->InitAllChildrenDragManager(true);

    forEachNode->children_.clear();
    auto list_tag1 = AceType::MakeRefPtr<FrameNode>(LIST_TAG, -1, AceType::MakeRefPtr<Pattern>());
    forEachNode->SetParent(list_tag1);
    forEachNode->children_ = { list_tag1 };
    forEachNode->CompareAndUpdateChildren();
    forEachNode->FlushUpdateAndMarkDirty();
    forEachNode->SetOnMove(SetOnMoveTestNg);
    forEachNode->InitAllChildrenDragManager(true);
}
} // namespace OHOS::Ace::NG
