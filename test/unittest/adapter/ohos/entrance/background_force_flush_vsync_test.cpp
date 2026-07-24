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
#define private public
#define protected public

#include "test/mock/frameworks/core/common/mock_window.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace;

class BackgroundForceFlushVsyncTest : public testing::Test {
public:
    void SetUp() override
    {
        window_ = std::make_shared<NiceMock<MockWindow>>();
    }
    void TearDown() override {}

    std::shared_ptr<NiceMock<MockWindow>> window_;
};

/**
 * @tc.name: BackgroundForceFlushVsync001
 * @tc.desc: Test SetBackgroundForceFlushVsync state management:
 *           default values, enable/count, clamp to 10, disable, re-enable, edge cases.
 * @tc.type: FUNC
 */
HWTEST_F(BackgroundForceFlushVsyncTest, BackgroundForceFlushVsync001, TestSize.Level1)
{
    // Default values
    EXPECT_FALSE(window_->backgroundForceFlushEnabled_.load());
    EXPECT_EQ(window_->backgroundForceFlushCount_.load(), 0);

    // Enable with count=5
    window_->SetBackgroundForceFlushVsync(true, 5);
    EXPECT_TRUE(window_->backgroundForceFlushEnabled_.load());
    EXPECT_EQ(window_->backgroundForceFlushCount_.load(), 5);

    // Clamp count=15 to max 10
    window_->SetBackgroundForceFlushVsync(true, 15);
    EXPECT_TRUE(window_->backgroundForceFlushEnabled_.load());
    EXPECT_EQ(window_->backgroundForceFlushCount_.load(), 10);

    // Disable: enabled=false, count=0
    window_->SetBackgroundForceFlushVsync(false, 3);
    EXPECT_FALSE(window_->backgroundForceFlushEnabled_.load());
    EXPECT_EQ(window_->backgroundForceFlushCount_.load(), 0);

    // Re-enable after disable with count=3
    window_->SetBackgroundForceFlushVsync(true, 3);
    EXPECT_TRUE(window_->backgroundForceFlushEnabled_.load());
    EXPECT_EQ(window_->backgroundForceFlushCount_.load(), 3);

    // Edge: enable=true with count=0
    window_->SetBackgroundForceFlushVsync(true, 0);
    EXPECT_TRUE(window_->backgroundForceFlushEnabled_.load());
    EXPECT_EQ(window_->backgroundForceFlushCount_.load(), 0);

    // Edge: count=1 is minimum non-zero valid
    window_->SetBackgroundForceFlushVsync(true, 1);
    EXPECT_TRUE(window_->backgroundForceFlushEnabled_.load());
    EXPECT_EQ(window_->backgroundForceFlushCount_.load(), 1);
}

/**
 * @tc.name: BackgroundForceFlushVsync002
 * @tc.desc: Test OnShow/OnHide lifecycle interaction with background force flush state.
 * @tc.type: FUNC
 */
HWTEST_F(BackgroundForceFlushVsyncTest, BackgroundForceFlushVsync002, TestSize.Level1)
{
    // OnHide does not affect enabled state
    window_->SetBackgroundForceFlushVsync(true, 5);
    window_->Window::OnHide();
    EXPECT_TRUE(window_->backgroundForceFlushEnabled_.load());
    EXPECT_EQ(window_->backgroundForceFlushCount_.load(), 5);
    EXPECT_TRUE(window_->IsHide());

    // OnShow resets state to disabled
    window_->Window::OnShow();
    EXPECT_FALSE(window_->backgroundForceFlushEnabled_.load());
    EXPECT_EQ(window_->backgroundForceFlushCount_.load(), 0);

    // OnShow reset after multiple enable/disable cycles
    window_->SetBackgroundForceFlushVsync(true, 10);
    window_->SetBackgroundForceFlushVsync(false, 0);
    window_->SetBackgroundForceFlushVsync(true, 3);
    EXPECT_TRUE(window_->backgroundForceFlushEnabled_.load());
    EXPECT_EQ(window_->backgroundForceFlushCount_.load(), 3);

    window_->Window::OnShow();
    EXPECT_FALSE(window_->backgroundForceFlushEnabled_.load());
    EXPECT_EQ(window_->backgroundForceFlushCount_.load(), 0);
}
