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

#include <cstdint>
#include <string>

#include "gtest/gtest.h"

#include "core/components_ng/base/async_load_config.h"
#include "core/components_ng/manager/async_load/async_load_manager.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t TEST_INSTANCE_ID = 100;
constexpr int32_t FIRST_NODE_ID = 1001;
constexpr int64_t FRAME_TIMESTAMP_NS = 1000000;
constexpr int64_t FRAME_PERIOD_NS = 8333333;
} // namespace

class AsyncLoadManagerTestNg : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        MockPipelineContext::SetUp();
    }

    static void TearDownTestSuite()
    {
        MockPipelineContext::TearDown();
    }

    void SetUp() override
    {
        manager_ = AceType::MakeRefPtr<AsyncLoadManager>(TEST_INSTANCE_ID);
        auto pipeline = MockPipelineContext::GetCurrent();
        if (pipeline) {
            manager_->SetPipelineContext(pipeline);
        }
    }

    void TearDown() override
    {
        manager_.Reset();
    }

    RefPtr<AsyncLoadManager> manager_;

    static AsyncLoadConfig MakeConfig(int32_t timeoutMs)
    {
        AsyncLoadConfig config;
        config.timeoutMs = timeoutMs;
        return config;
    }

    static AsyncLoadConfig MakePlaceholderConfig(const std::string& placeholderId, int32_t timeoutMs)
    {
        AsyncLoadConfig config;
        config.placeholderId = placeholderId;
        config.timeoutMs = timeoutMs;
        return config;
    }

    static AsyncLoadManager::ForceLoadCallback CountingCallback(int32_t* counter)
    {
        return [counter]() {
            if (counter) {
                (*counter)++;
            }
        };
    }

    void DrainFrame()
    {
        manager_->OnVsync(FRAME_TIMESTAMP_NS, FRAME_PERIOD_NS);
    }
};

/**
 * @tc.name: AsyncLoad_TimeoutZeroForceLoad
 * @tc.desc: A zero timeout does not wait: the entry is already expired when the next frame drains
 *           it, so the component is force-loaded without any timer.
 * @tc.type: FUNC
 */
HWTEST_F(AsyncLoadManagerTestNg, AsyncLoad_TimeoutZeroForceLoad, TestSize.Level1)
{
    int32_t forced = 0;
    manager_->Register(FIRST_NODE_ID, MakeConfig(0), CountingCallback(&forced));
    EXPECT_EQ(manager_->GetPendingCount(), 1u);
    EXPECT_EQ(manager_->GetExpiredCount(), 1u);

    DrainFrame();

    EXPECT_EQ(forced, 1);
    EXPECT_EQ(manager_->GetPendingCount(), 0u);
}

/**
 * @tc.name: AsyncLoad_TimeoutNegativeNeverForceLoads
 * @tc.desc: A negative timeout never times out. The entry stays queued across frames and is only
 *           removed by the component reporting completion.
 * @tc.type: FUNC
 */
HWTEST_F(AsyncLoadManagerTestNg, AsyncLoad_TimeoutNegativeNeverForceLoads, TestSize.Level1)
{
    int32_t forced = 0;
    manager_->Register(FIRST_NODE_ID, MakeConfig(-1), CountingCallback(&forced));

    DrainFrame();
    DrainFrame();

    EXPECT_EQ(forced, 0);
    EXPECT_EQ(manager_->GetExpiredCount(), 0u);
    EXPECT_EQ(manager_->GetPendingCount(), 1u);

    manager_->OnLoaded(FIRST_NODE_ID);
    EXPECT_EQ(manager_->GetPendingCount(), 0u);
}

/**
 * @tc.name: AsyncLoad_PositiveTimeoutWaitsForExpiry
 * @tc.desc: A positive timeout does not expire on registration; the entry waits for the delayed
 *           task rather than being force-loaded on the immediately following frame.
 * @tc.type: FUNC
 */
HWTEST_F(AsyncLoadManagerTestNg, AsyncLoad_PositiveTimeoutWaitsForExpiry, TestSize.Level1)
{
    int32_t forced = 0;
    manager_->Register(FIRST_NODE_ID, MakeConfig(AsyncLoadManager::DEFAULT_TIMEOUT_MS),
        CountingCallback(&forced));

    DrainFrame();

    EXPECT_EQ(forced, 0);
    EXPECT_EQ(manager_->GetExpiredCount(), 0u);
    EXPECT_EQ(manager_->GetPendingCount(), 1u);
}

/**
 * @tc.name: AsyncLoad_ForceLoadLimitPerFrame
 * @tc.desc: A burst of timeouts must not be force-loaded in one frame. At most
 *           FORCE_LOAD_LIMIT_PER_FRAME entries drain per frame, and the remainder follow on later
 *           frames until the queue is empty.
 * @tc.type: FUNC
 */
HWTEST_F(AsyncLoadManagerTestNg, AsyncLoad_ForceLoadLimitPerFrame, TestSize.Level1)
{
    constexpr int32_t TOTAL = 10;
    int32_t forced = 0;
    for (int32_t i = 0; i < TOTAL; i++) {
        manager_->Register(FIRST_NODE_ID + i, MakeConfig(0), CountingCallback(&forced));
    }
    EXPECT_EQ(manager_->GetPendingCount(), static_cast<size_t>(TOTAL));

    DrainFrame();
    EXPECT_EQ(forced, AsyncLoadManager::FORCE_LOAD_LIMIT_PER_FRAME);

    DrainFrame();
    EXPECT_EQ(forced, AsyncLoadManager::FORCE_LOAD_LIMIT_PER_FRAME * 2);

    DrainFrame();
    EXPECT_EQ(forced, TOTAL);
    EXPECT_EQ(manager_->GetPendingCount(), 0u);
}

/**
 * @tc.name: AsyncLoad_DestroyClearsQueue
 * @tc.desc: Destroying a component removes its entry, so no dangling entry survives to be
 *           force-loaded later against a node that is no longer on the tree.
 * @tc.type: FUNC
 */
HWTEST_F(AsyncLoadManagerTestNg, AsyncLoad_DestroyClearsQueue, TestSize.Level1)
{
    int32_t forced = 0;
    manager_->Register(FIRST_NODE_ID, MakeConfig(0), CountingCallback(&forced));
    manager_->OnNodeDestroyed(FIRST_NODE_ID);

    EXPECT_EQ(manager_->GetPendingCount(), 0u);
    DrainFrame();
    EXPECT_EQ(forced, 0);
}

/**
 * @tc.name: AsyncLoad_UntrackedNodeCallsAreNoops
 * @tc.desc: Reporting completion or destruction for a node that was never registered, or already
 *           removed, must not disturb the entries still queued.
 * @tc.type: FUNC
 */
HWTEST_F(AsyncLoadManagerTestNg, AsyncLoad_UntrackedNodeCallsAreNoops, TestSize.Level1)
{
    int32_t forced = 0;
    manager_->Register(FIRST_NODE_ID, MakeConfig(0), CountingCallback(&forced));

    manager_->OnLoaded(FIRST_NODE_ID + 1);
    manager_->OnNodeDestroyed(FIRST_NODE_ID + 2);

    EXPECT_EQ(manager_->GetPendingCount(), 1u);
    DrainFrame();
    EXPECT_EQ(forced, 1);
}

/**
 * @tc.name: AsyncLoad_RemountReplacesEntry
 * @tc.desc: A component that mounts twice must not end up with two entries; the second mount
 *           replaces the first so the one-entry-per-node invariant holds.
 * @tc.type: FUNC
 */
HWTEST_F(AsyncLoadManagerTestNg, AsyncLoad_RemountReplacesEntry, TestSize.Level1)
{
    int32_t firstCallback = 0;
    int32_t secondCallback = 0;
    manager_->Register(FIRST_NODE_ID, MakeConfig(0), CountingCallback(&firstCallback));
    manager_->Register(FIRST_NODE_ID, MakeConfig(0), CountingCallback(&secondCallback));

    EXPECT_EQ(manager_->GetPendingCount(), 1u);
    DrainFrame();
    EXPECT_EQ(firstCallback, 0);
    EXPECT_EQ(secondCallback, 1);
}

/**
 * @tc.name: AsyncLoad_PlaceholderAbsentWhenNotConfigured
 * @tc.desc: Without a placeholder id the manager produces no node, so the component stays
 *           invisible while loading instead of falling back to a system default placeholder.
 * @tc.type: FUNC
 */
HWTEST_F(AsyncLoadManagerTestNg, AsyncLoad_PlaceholderAbsentWhenNotConfigured, TestSize.Level1)
{
    EXPECT_EQ(manager_->CreatePlaceholder(MakeConfig(AsyncLoadManager::DEFAULT_TIMEOUT_MS)), nullptr);
}

/**
 * @tc.name: AsyncLoad_PlaceholderAbsentWhenIdUnregistered
 * @tc.desc: An id that the template registry does not know degrades to "not configured" rather
 *           than showing anything or throwing (spec EX-3).
 * @tc.type: FUNC
 */
HWTEST_F(AsyncLoadManagerTestNg, AsyncLoad_PlaceholderAbsentWhenIdUnregistered, TestSize.Level1)
{
    EXPECT_EQ(manager_->CreatePlaceholder(MakePlaceholderConfig("unregistered_template", 0)), nullptr);
}

/**
 * @tc.name: AsyncLoad_DetachPlaceholderToleratesNull
 * @tc.desc: Detaching a placeholder that was never created is a no-op, which keeps the
 *           completion path safe for components without a configured placeholder.
 * @tc.type: FUNC
 */
HWTEST_F(AsyncLoadManagerTestNg, AsyncLoad_DetachPlaceholderToleratesNull, TestSize.Level1)
{
    manager_->DetachPlaceholder(nullptr, nullptr);
    SUCCEED();
}

/**
 * @tc.name: AsyncLoad_EmptyQueueDoesNotForceLoad
 * @tc.desc: Driving frames with nothing queued must not invoke anything; this is the zero-overhead
 *           path taken by applications that never enable asynchronous loading.
 * @tc.type: FUNC
 */
HWTEST_F(AsyncLoadManagerTestNg, AsyncLoad_EmptyQueueDoesNotForceLoad, TestSize.Level1)
{
    EXPECT_EQ(manager_->GetPendingCount(), 0u);
    DrainFrame();
    EXPECT_EQ(manager_->GetExpiredCount(), 0u);
    EXPECT_EQ(manager_->GetPendingCount(), 0u);
}
} // namespace OHOS::Ace::NG
