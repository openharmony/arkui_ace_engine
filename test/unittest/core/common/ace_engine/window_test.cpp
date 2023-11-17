/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include <csignal>
#include <memory>

#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/core/common/mock_container.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "test/mock/base/mock_task_executor.h"
#include "core/common/platform_window.h"
#include "core/common/watch_dog.h"
#include "core/common/window.h"
#include "core/components/test/unittest/mock/window_mock.h"
#include "core/pipeline/pipeline_context.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;
using ::testing::_;

namespace OHOS::Ace {
namespace {
RefPtr<MockTaskExecutor> MOCK_TASK_EXECUTOR;
} // namespace
class WindowTest : public testing::Test {};

/**
 * @tc.name: Window001
 * @tc.desc: Verify the RequestFrame.
 * @tc.type: FUNC
 */
HWTEST_F(WindowTest, Window001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a window object.
     */
    std::unique_ptr<PlatformWindow> platformWindow = std::make_unique<MockPlatformWindow>();
    Window window(std::move(platformWindow));
    EXPECT_TRUE(window.onShow_);
    EXPECT_FALSE(window.isRequestVsync_);

    window.RequestFrame();
    EXPECT_TRUE(window.isRequestVsync_);
}

/**
 * @tc.name: Window002
 * @tc.desc: Verify the OnVsync.
 * @tc.type: FUNC
 */
HWTEST_F(WindowTest, Window002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a window object.
     */
    std::unique_ptr<PlatformWindow> platformWindow = std::make_unique<MockPlatformWindow>();
    Window window(std::move(platformWindow));
    window.isRequestVsync_ = true;

    uint64_t nanoTimestamp = 10;
    uint32_t frameCount = 10;

    auto callback = [](uint64_t, uint32_t) -> void {};

    window.SetVsyncCallback(callback);
    window.OnVsync(nanoTimestamp, frameCount);
    EXPECT_FALSE(window.isRequestVsync_);
}
} // namespace OHOS::Ace
