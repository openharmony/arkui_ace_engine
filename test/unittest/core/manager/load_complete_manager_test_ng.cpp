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
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#define private public
#include "core/components_ng/manager/load_complete/load_complete_manager.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr int32_t TEST_NODE_ID_1 = 100;
constexpr int32_t TEST_NODE_ID_2 = 200;
constexpr int32_t TEST_NODE_ID_3 = 300;
const std::string TEST_PAGE_URL = "test_page_url";
} // namespace

class LoadCompleteManagerTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void LoadCompleteManagerTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void LoadCompleteManagerTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: LoadCompleteManagerTest001
 * @tc.desc: Test AddLoadComponent and nodeSet_ state
 * @tc.type: FUNC
 */
HWTEST_F(LoadCompleteManagerTestNg, LoadCompleteManagerTest001, TestSize.Level1)
{
    auto loadCompleteManager = std::make_shared<LoadCompleteManager>();
    ASSERT_NE(loadCompleteManager, nullptr);

    loadCompleteManager->StartCollect(TEST_PAGE_URL);

    loadCompleteManager->AddLoadComponent(TEST_NODE_ID_1);
    loadCompleteManager->AddLoadComponent(TEST_NODE_ID_2);
    EXPECT_EQ(loadCompleteManager->nodeSet_.size(), 2);
    EXPECT_EQ(loadCompleteManager->nodeNum_, 2);
}

/**
 * @tc.name: LoadCompleteManagerTest002
 * @tc.desc: Test DeleteLoadComponent when nodeId exists in nodeSet_
 * @tc.type: FUNC
 */
HWTEST_F(LoadCompleteManagerTestNg, LoadCompleteManagerTest002, TestSize.Level1)
{
    auto loadCompleteManager = std::make_shared<LoadCompleteManager>();
    ASSERT_NE(loadCompleteManager, nullptr);

    loadCompleteManager->StartCollect(TEST_PAGE_URL);
    loadCompleteManager->AddLoadComponent(TEST_NODE_ID_1);
    loadCompleteManager->AddLoadComponent(TEST_NODE_ID_2);

    int64_t beforeTimestamp = loadCompleteManager->lastLoadComponent;

    sleep(1);
    loadCompleteManager->DeleteLoadComponent(TEST_NODE_ID_1);

    EXPECT_EQ(loadCompleteManager->nodeSet_.size(), 1);
    EXPECT_GT(loadCompleteManager->lastLoadComponent, beforeTimestamp);
}

/**
 * @tc.name: LoadCompleteManagerTest003
 * @tc.desc: Test DeleteLoadComponent when nodeId does not exist in nodeSet_
 * @tc.type: FUNC
 */
HWTEST_F(LoadCompleteManagerTestNg, LoadCompleteManagerTest003, TestSize.Level1)
{
    auto loadCompleteManager = std::make_shared<LoadCompleteManager>();
    ASSERT_NE(loadCompleteManager, nullptr);

    loadCompleteManager->StartCollect(TEST_PAGE_URL);
    loadCompleteManager->AddLoadComponent(TEST_NODE_ID_1);

    int64_t beforeTimestamp = loadCompleteManager->lastLoadComponent;

    sleep(1);
    loadCompleteManager->DeleteLoadComponent(TEST_NODE_ID_2);

    EXPECT_EQ(loadCompleteManager->nodeSet_.size(), 1);
    EXPECT_EQ(loadCompleteManager->lastLoadComponent, beforeTimestamp);
}

/**
 * @tc.name: LoadCompleteManagerTest004
 * @tc.desc: Test DeleteLoadComponent when collectStatus is COMPLETE
 * @tc.type: FUNC
 */
HWTEST_F(LoadCompleteManagerTestNg, LoadCompleteManagerTest004, TestSize.Level1)
{
    auto loadCompleteManager = std::make_shared<LoadCompleteManager>();
    ASSERT_NE(loadCompleteManager, nullptr);

    loadCompleteManager->StartCollect(TEST_PAGE_URL);
    loadCompleteManager->AddLoadComponent(TEST_NODE_ID_1);

    loadCompleteManager->collectStatus_ = CollectStatus::COMPLETE;

    int64_t beforeTimestamp = loadCompleteManager->lastLoadComponent;

    sleep(1);
    loadCompleteManager->DeleteLoadComponent(TEST_NODE_ID_1);

    EXPECT_EQ(loadCompleteManager->nodeSet_.size(), 1);
    EXPECT_EQ(loadCompleteManager->lastLoadComponent, beforeTimestamp);
}

/**
 * @tc.name: LoadCompleteManagerTest005
 * @tc.desc: Test CompleteLoadComponent when nodeId exists in nodeSet_
 * @tc.type: FUNC
 */
HWTEST_F(LoadCompleteManagerTestNg, LoadCompleteManagerTest005, TestSize.Level1)
{
    auto loadCompleteManager = std::make_shared<LoadCompleteManager>();
    ASSERT_NE(loadCompleteManager, nullptr);

    loadCompleteManager->StartCollect(TEST_PAGE_URL);
    loadCompleteManager->AddLoadComponent(TEST_NODE_ID_1);
    loadCompleteManager->AddLoadComponent(TEST_NODE_ID_2);

    int64_t beforeTimestamp = loadCompleteManager->lastLoadComponent;

    sleep(1);
    loadCompleteManager->CompleteLoadComponent(TEST_NODE_ID_1);

    EXPECT_EQ(loadCompleteManager->nodeSet_.size(), 1);
    EXPECT_GT(loadCompleteManager->lastLoadComponent, beforeTimestamp);
}

/**
 * @tc.name: LoadCompleteManagerTest006
 * @tc.desc: Test CompleteLoadComponent when nodeId does not exist in nodeSet_
 * @tc.type: FUNC
 */
HWTEST_F(LoadCompleteManagerTestNg, LoadCompleteManagerTest006, TestSize.Level1)
{
    auto loadCompleteManager = std::make_shared<LoadCompleteManager>();
    ASSERT_NE(loadCompleteManager, nullptr);

    loadCompleteManager->StartCollect(TEST_PAGE_URL);
    loadCompleteManager->AddLoadComponent(TEST_NODE_ID_1);

    int64_t beforeTimestamp = loadCompleteManager->lastLoadComponent;

    sleep(1);
    loadCompleteManager->CompleteLoadComponent(TEST_NODE_ID_2);

    EXPECT_EQ(loadCompleteManager->nodeSet_.size(), 1);
    EXPECT_EQ(loadCompleteManager->lastLoadComponent, beforeTimestamp);
}

/**
 * @tc.name: LoadCompleteManagerTest007
 * @tc.desc: Test CompleteLoadComponent when collectStatus is COMPLETE
 * @tc.type: FUNC
 */
HWTEST_F(LoadCompleteManagerTestNg, LoadCompleteManagerTest007, TestSize.Level1)
{
    auto loadCompleteManager = std::make_shared<LoadCompleteManager>();
    ASSERT_NE(loadCompleteManager, nullptr);

    loadCompleteManager->StartCollect(TEST_PAGE_URL);
    loadCompleteManager->AddLoadComponent(TEST_NODE_ID_1);

    loadCompleteManager->collectStatus_ = CollectStatus::COMPLETE;

    int64_t beforeTimestamp = loadCompleteManager->lastLoadComponent;

    sleep(1);
    loadCompleteManager->CompleteLoadComponent(TEST_NODE_ID_1);

    EXPECT_EQ(loadCompleteManager->nodeSet_.size(), 1);
    EXPECT_EQ(loadCompleteManager->lastLoadComponent, beforeTimestamp);
}

/**
 * @tc.name: LoadCompleteManagerTest008
 * @tc.desc: Test multiple DeleteLoadComponent calls
 * @tc.type: FUNC
 */
HWTEST_F(LoadCompleteManagerTestNg, LoadCompleteManagerTest008, TestSize.Level1)
{
    auto loadCompleteManager = std::make_shared<LoadCompleteManager>();
    ASSERT_NE(loadCompleteManager, nullptr);

    loadCompleteManager->StartCollect(TEST_PAGE_URL);
    loadCompleteManager->AddLoadComponent(TEST_NODE_ID_1);
    loadCompleteManager->AddLoadComponent(TEST_NODE_ID_2);
    loadCompleteManager->AddLoadComponent(TEST_NODE_ID_3);

    int64_t beforeTimestamp1 = loadCompleteManager->lastLoadComponent;
    sleep(1);
    loadCompleteManager->DeleteLoadComponent(TEST_NODE_ID_1);
    int64_t timestamp1 = loadCompleteManager->lastLoadComponent;

    int64_t beforeTimestamp2 = loadCompleteManager->lastLoadComponent;
    sleep(1);
    loadCompleteManager->DeleteLoadComponent(TEST_NODE_ID_2);
    int64_t timestamp2 = loadCompleteManager->lastLoadComponent;

    int64_t beforeTimestamp3 = loadCompleteManager->lastLoadComponent;
    sleep(1);
    loadCompleteManager->DeleteLoadComponent(TEST_NODE_ID_3);
    int64_t timestamp3 = loadCompleteManager->lastLoadComponent;

    EXPECT_EQ(loadCompleteManager->nodeSet_.size(), 0);
    EXPECT_GT(timestamp1, beforeTimestamp1);
    EXPECT_GT(timestamp2, beforeTimestamp2);
    EXPECT_GT(timestamp3, beforeTimestamp3);
}

/**
 * @tc.name: LoadCompleteManagerTest009
 * @tc.desc: Test multiple CompleteLoadComponent calls
 * @tc.type: FUNC
 */
HWTEST_F(LoadCompleteManagerTestNg, LoadCompleteManagerTest009, TestSize.Level1)
{
    auto loadCompleteManager = std::make_shared<LoadCompleteManager>();
    ASSERT_NE(loadCompleteManager, nullptr);

    loadCompleteManager->StartCollect(TEST_PAGE_URL);
    loadCompleteManager->AddLoadComponent(TEST_NODE_ID_1);
    loadCompleteManager->AddLoadComponent(TEST_NODE_ID_2);
    loadCompleteManager->AddLoadComponent(TEST_NODE_ID_3);

    int64_t beforeTimestamp1 = loadCompleteManager->lastLoadComponent;
    sleep(1);
    loadCompleteManager->CompleteLoadComponent(TEST_NODE_ID_1);
    int64_t timestamp1 = loadCompleteManager->lastLoadComponent;

    int64_t beforeTimestamp2 = loadCompleteManager->lastLoadComponent;
    sleep(1);
    loadCompleteManager->CompleteLoadComponent(TEST_NODE_ID_2);
    int64_t timestamp2 = loadCompleteManager->lastLoadComponent;

    int64_t beforeTimestamp3 = loadCompleteManager->lastLoadComponent;
    sleep(1);
    loadCompleteManager->CompleteLoadComponent(TEST_NODE_ID_3);
    int64_t timestamp3 = loadCompleteManager->lastLoadComponent;

    EXPECT_EQ(loadCompleteManager->nodeSet_.size(), 0);
    EXPECT_GT(timestamp1, beforeTimestamp1);
    EXPECT_GT(timestamp2, beforeTimestamp2);
    EXPECT_GT(timestamp3, beforeTimestamp3);
}

/**
 * @tc.name: LoadCompleteManagerTest010
 * @tc.desc: Test mixed DeleteLoadComponent and CompleteLoadComponent calls
 * @tc.type: FUNC
 */
HWTEST_F(LoadCompleteManagerTestNg, LoadCompleteManagerTest010, TestSize.Level1)
{
    auto loadCompleteManager = std::make_shared<LoadCompleteManager>();
    ASSERT_NE(loadCompleteManager, nullptr);

    loadCompleteManager->StartCollect(TEST_PAGE_URL);
    loadCompleteManager->AddLoadComponent(TEST_NODE_ID_1);
    loadCompleteManager->AddLoadComponent(TEST_NODE_ID_2);
    loadCompleteManager->AddLoadComponent(TEST_NODE_ID_3);

    int64_t beforeTimestamp1 = loadCompleteManager->lastLoadComponent;
    sleep(1);
    loadCompleteManager->DeleteLoadComponent(TEST_NODE_ID_1);
    int64_t timestamp1 = loadCompleteManager->lastLoadComponent;

    int64_t beforeTimestamp2 = loadCompleteManager->lastLoadComponent;
    sleep(1);
    loadCompleteManager->CompleteLoadComponent(TEST_NODE_ID_2);
    int64_t timestamp2 = loadCompleteManager->lastLoadComponent;

    int64_t beforeTimestamp3 = loadCompleteManager->lastLoadComponent;
    sleep(1);
    loadCompleteManager->DeleteLoadComponent(TEST_NODE_ID_3);
    int64_t timestamp3 = loadCompleteManager->lastLoadComponent;

    EXPECT_EQ(loadCompleteManager->nodeSet_.size(), 0);
    EXPECT_GT(timestamp1, beforeTimestamp1);
    EXPECT_GT(timestamp2, beforeTimestamp2);
    EXPECT_GT(timestamp3, beforeTimestamp3);
}
} // namespace OHOS::Ace::NG
