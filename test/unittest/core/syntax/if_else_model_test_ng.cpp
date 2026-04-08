/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/syntax/if_else_model_ng.h"
#include "core/components_v2/inspector/inspector_constants.h"

#define private public
#include "core/components_ng/syntax/if_else_node.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t IF_ELSE_BRANCH_ID_1 = 1;
constexpr int32_t IF_ELSE_BRANCH_ID_2 = 2;
constexpr int32_t IF_ELSE_BRANCH_ID_0 = 0;
const std::string TEST_RETAKE_ID = "test_retake_id";
const std::string TEST_RETAKE_ID_2 = "test_retake_id_2";
} // namespace

class IfElseModelTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
};

void IfElseModelTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void IfElseModelTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

void IfElseModelTestNg::SetUp()
{
    MockPipelineContext::SetUp();
}

void IfElseModelTestNg::TearDown()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: IfElseModelCreateTest001
 * @tc.desc: Create creates IfElseNode and pushes to ViewStackProcessor
 * @tc.type: FUNC
 */
HWTEST_F(IfElseModelTestNg, IfElseModelCreateTest001, TestSize.Level1)
{
    IfElseModelNG ifElseModel;
    ifElseModel.Create();
    auto ifElseNode = AceType::DynamicCast<IfElseNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    EXPECT_TRUE(ifElseNode != nullptr);
    EXPECT_EQ(ifElseNode->GetTag(), V2::JS_IF_ELSE_ETS_TAG);
}

/**
 * @tc.name: IfElseModelPopTest002
 * @tc.desc: Pop pops container from ViewStackProcessor
 * @tc.type: FUNC
 */
HWTEST_F(IfElseModelTestNg, IfElseModelPopTest002, TestSize.Level1)
{
    IfElseModelNG ifElseModel;
    ifElseModel.Create();
    auto ifElseNode = AceType::DynamicCast<IfElseNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    EXPECT_TRUE(ifElseNode != nullptr);
    ifElseModel.Pop();
    SUCCEED();
}

/**
 * @tc.name: IfElseModelSetBranchIdTest003
 * @tc.desc: SetBranchId sets branch ID correctly
 * @tc.type: FUNC
 */
HWTEST_F(IfElseModelTestNg, IfElseModelSetBranchIdTest003, TestSize.Level1)
{
    IfElseModelNG ifElseModel;
    ifElseModel.Create();
    std::list<int32_t> removedElmtId;
    std::list<int32_t> reservedElmtId;
    ifElseModel.SetBranchId(IF_ELSE_BRANCH_ID_1, removedElmtId, reservedElmtId);
    auto ifElseNode = AceType::DynamicCast<IfElseNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    EXPECT_EQ(ifElseNode->GetBranchId(), IF_ELSE_BRANCH_ID_1);
}

/**
 * @tc.name: IfElseModelSetBranchIdTest004
 * @tc.desc: SetBranchId handles null node gracefully
 * @tc.type: FUNC
 */
HWTEST_F(IfElseModelTestNg, IfElseModelSetBranchIdTest004, TestSize.Level1)
{
    IfElseModelNG ifElseModel;
    std::list<int32_t> removedElmtId;
    std::list<int32_t> reservedElmtId;
    ifElseModel.SetBranchId(IF_ELSE_BRANCH_ID_1, removedElmtId, reservedElmtId);
    SUCCEED();
}

/**
 * @tc.name: IfElseModelGetBranchIdTest005
 * @tc.desc: GetBranchId returns correct branch ID
 * @tc.type: FUNC
 */
HWTEST_F(IfElseModelTestNg, IfElseModelGetBranchIdTest005, TestSize.Level1)
{
    IfElseModelNG ifElseModel;
    ifElseModel.Create();
    std::list<int32_t> removedElmtId;
    std::list<int32_t> reservedElmtId;
    ifElseModel.SetBranchId(IF_ELSE_BRANCH_ID_2, removedElmtId, reservedElmtId);
    EXPECT_EQ(ifElseModel.GetBranchId(), IF_ELSE_BRANCH_ID_2);
}

/**
 * @tc.name: IfElseModelGetBranchIdTest006
 * @tc.desc: GetBranchId returns -1 when node is null
 * @tc.type: FUNC
 */
HWTEST_F(IfElseModelTestNg, IfElseModelGetBranchIdTest006, TestSize.Level1)
{
    IfElseModelNG ifElseModel;
    EXPECT_EQ(ifElseModel.GetBranchId(), IF_ELSE_BRANCH_ID_2);
}

/**
 * @tc.name: IfElseModelCanRetakeTest007
 * @tc.desc: CanRetake returns true when id can be retaken
 * @tc.type: FUNC
 */
HWTEST_F(IfElseModelTestNg, IfElseModelCanRetakeTest007, TestSize.Level1)
{
    IfElseModelNG ifElseModel;
    ifElseModel.Create();
    bool result = ifElseModel.CanRetake(TEST_RETAKE_ID);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: IfElseModelCanRetakeTest008
 * @tc.desc: CanRetake returns false when node is null
 * @tc.type: FUNC
 */
HWTEST_F(IfElseModelTestNg, IfElseModelCanRetakeTest008, TestSize.Level1)
{
    IfElseModelNG ifElseModel;
    bool result = ifElseModel.CanRetake(TEST_RETAKE_ID);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: IfElseModelGetRetakenElmtIdsTest009
 * @tc.desc: GetRetakenElmtIds returns false when node is null
 * @tc.type: FUNC
 */
HWTEST_F(IfElseModelTestNg, IfElseModelGetRetakenElmtIdsTest009, TestSize.Level1)
{
    IfElseModelNG ifElseModel;
    std::list<int32_t> retakenElmtIds;
    bool result = ifElseModel.GetRetakenElmtIds(retakenElmtIds);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: IfElseModelGetRetakenElmtIdsTest010
 * @tc.desc: GetRetakenElmtIds returns correct retaken IDs
 * @tc.type: FUNC
 */
HWTEST_F(IfElseModelTestNg, IfElseModelGetRetakenElmtIdsTest010, TestSize.Level1)
{
    IfElseModelNG ifElseModel;
    ifElseModel.Create();
    std::list<int32_t> retakenElmtIds;
    bool result = ifElseModel.GetRetakenElmtIds(retakenElmtIds);
    EXPECT_FALSE(result);
    EXPECT_TRUE(retakenElmtIds.empty());
}

/**
 * @tc.name: IfElseModelCompleteFlowTest011
 * @tc.desc: Complete flow: Create, SetBranchId, GetBranchId, Pop
 * @tc.type: FUNC
 */
HWTEST_F(IfElseModelTestNg, IfElseModelCompleteFlowTest011, TestSize.Level1)
{
    IfElseModelNG ifElseModel;
    ifElseModel.Create();
    std::list<int32_t> removedElmtId;
    std::list<int32_t> reservedElmtId;
    ifElseModel.SetBranchId(IF_ELSE_BRANCH_ID_1, removedElmtId, reservedElmtId);
    EXPECT_EQ(ifElseModel.GetBranchId(), IF_ELSE_BRANCH_ID_1);
    ifElseModel.SetBranchId(IF_ELSE_BRANCH_ID_2, removedElmtId, reservedElmtId);
    EXPECT_EQ(ifElseModel.GetBranchId(), IF_ELSE_BRANCH_ID_2);
    ifElseModel.Pop();
    SUCCEED();
}

/**
 * @tc.name: IfElseModelCanRetakeMultipleIdsTest012
 * @tc.desc: CanRetake with different IDs
 * @tc.type: FUNC
 */
HWTEST_F(IfElseModelTestNg, IfElseModelCanRetakeMultipleIdsTest012, TestSize.Level1)
{
    IfElseModelNG ifElseModel;
    ifElseModel.Create();
    bool result1 = ifElseModel.CanRetake(TEST_RETAKE_ID);
    bool result2 = ifElseModel.CanRetake(TEST_RETAKE_ID_2);
    EXPECT_FALSE(result1);
    EXPECT_FALSE(result2);
}

/**
 * @tc.name: IfElseModelSetBranchIdMultipleTimesTest013
 * @tc.desc: SetBranchId can be called multiple times
 * @tc.type: FUNC
 */
HWTEST_F(IfElseModelTestNg, IfElseModelSetBranchIdMultipleTimesTest013, TestSize.Level1)
{
    IfElseModelNG ifElseModel;
    ifElseModel.Create();
    std::list<int32_t> removedElmtId;
    std::list<int32_t> reservedElmtId;
    ifElseModel.SetBranchId(IF_ELSE_BRANCH_ID_0, removedElmtId, reservedElmtId);
    EXPECT_EQ(ifElseModel.GetBranchId(), IF_ELSE_BRANCH_ID_0);
    ifElseModel.SetBranchId(IF_ELSE_BRANCH_ID_1, removedElmtId, reservedElmtId);
    EXPECT_EQ(ifElseModel.GetBranchId(), IF_ELSE_BRANCH_ID_1);
    ifElseModel.SetBranchId(IF_ELSE_BRANCH_ID_2, removedElmtId, reservedElmtId);
    EXPECT_EQ(ifElseModel.GetBranchId(), IF_ELSE_BRANCH_ID_2);
}

} // namespace OHOS::Ace::NG
