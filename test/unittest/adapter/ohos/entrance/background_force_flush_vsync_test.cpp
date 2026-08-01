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
 * @tc.name: SetBackgroundForceFlushVsync001
 * @tc.desc: Test SetBackgroundForceFlushVsync state management:
 *           default values, enable/count, clamp to 10, disable, re-enable, edge cases.
 * @tc.type: FUNC
 */
HWTEST_F(BackgroundForceFlushVsyncTest, SetBackgroundForceFlushVsync001, TestSize.Level1)
{
    EXPECT_FALSE(window_->backgroundForceFlushEnabled_.load());
    EXPECT_EQ(window_->backgroundForceFlushCount_.load(), 0);

    window_->SetBackgroundForceFlushVsync(true, 5);
    EXPECT_TRUE(window_->backgroundForceFlushEnabled_.load());
    EXPECT_EQ(window_->backgroundForceFlushCount_.load(), 5);

    window_->SetBackgroundForceFlushVsync(true, 15);
    EXPECT_TRUE(window_->backgroundForceFlushEnabled_.load());
    EXPECT_EQ(window_->backgroundForceFlushCount_.load(), 10);

    window_->SetBackgroundForceFlushVsync(false, 3);
    EXPECT_FALSE(window_->backgroundForceFlushEnabled_.load());
    EXPECT_EQ(window_->backgroundForceFlushCount_.load(), 0);

    window_->SetBackgroundForceFlushVsync(true, 3);
    EXPECT_TRUE(window_->backgroundForceFlushEnabled_.load());
    EXPECT_EQ(window_->backgroundForceFlushCount_.load(), 3);

    window_->SetBackgroundForceFlushVsync(true, 0);
    EXPECT_TRUE(window_->backgroundForceFlushEnabled_.load());
    EXPECT_EQ(window_->backgroundForceFlushCount_.load(), 0);

    window_->SetBackgroundForceFlushVsync(true, 1);
    EXPECT_TRUE(window_->backgroundForceFlushEnabled_.load());
    EXPECT_EQ(window_->backgroundForceFlushCount_.load(), 1);
}

/**
 * @tc.name: OnShowOnHideLifecycle001
 * @tc.desc: Test OnShow/OnHide lifecycle: OnHide preserves state, OnShow resets it,
 *           including after partial consumption.
 * @tc.type: FUNC
 */
HWTEST_F(BackgroundForceFlushVsyncTest, OnShowOnHideLifecycle001, TestSize.Level1)
{
    window_->SetBackgroundForceFlushVsync(true, 5);
    window_->Window::OnHide();
    EXPECT_TRUE(window_->backgroundForceFlushEnabled_.load());
    EXPECT_EQ(window_->backgroundForceFlushCount_.load(), 5);
    EXPECT_TRUE(window_->IsHide());

    window_->Window::OnShow();
    EXPECT_FALSE(window_->backgroundForceFlushEnabled_.load());
    EXPECT_EQ(window_->backgroundForceFlushCount_.load(), 0);

    window_->SetBackgroundForceFlushVsync(true, 10);
    window_->SetBackgroundForceFlushVsync(false, 0);
    window_->SetBackgroundForceFlushVsync(true, 3);
    window_->Window::OnShow();
    EXPECT_FALSE(window_->backgroundForceFlushEnabled_.load());
    EXPECT_EQ(window_->backgroundForceFlushCount_.load(), 0);

    window_->SetBackgroundForceFlushVsync(true, 5);
    window_->ConsumeBackgroundForceFlushCount();
    window_->ConsumeBackgroundForceFlushCount();
    EXPECT_EQ(window_->backgroundForceFlushCount_.load(), 3);
    EXPECT_TRUE(window_->backgroundForceFlushEnabled_.load());

    window_->Window::OnShow();
    EXPECT_FALSE(window_->backgroundForceFlushEnabled_.load());
    EXPECT_EQ(window_->backgroundForceFlushCount_.load(), 0);
    EXPECT_FALSE(window_->HasBackgroundForceFlushQuota());
}

/**
 * @tc.name: QuotaAndConsume001
 * @tc.desc: Test HasBackgroundForceFlushQuota and ConsumeBackgroundForceFlushCount:
 *           quota requires enabled+count>0; consume decrements count-1 and disables
 *           when count reaches 0; re-enable after full consumption restores quota.
 * @tc.type: FUNC
 */
HWTEST_F(BackgroundForceFlushVsyncTest, QuotaAndConsume001, TestSize.Level1)
{
    EXPECT_FALSE(window_->HasBackgroundForceFlushQuota());
    EXPECT_FALSE(window_->ConsumeBackgroundForceFlushCount());

    window_->SetBackgroundForceFlushVsync(true, 0);
    EXPECT_FALSE(window_->HasBackgroundForceFlushQuota());

    window_->SetBackgroundForceFlushVsync(false, 5);
    EXPECT_FALSE(window_->HasBackgroundForceFlushQuota());
    EXPECT_FALSE(window_->ConsumeBackgroundForceFlushCount());

    window_->SetBackgroundForceFlushVsync(true, 3);
    EXPECT_TRUE(window_->HasBackgroundForceFlushQuota());
    EXPECT_TRUE(window_->ConsumeBackgroundForceFlushCount());
    EXPECT_EQ(window_->backgroundForceFlushCount_.load(), 2);
    EXPECT_TRUE(window_->HasBackgroundForceFlushQuota());

    EXPECT_TRUE(window_->ConsumeBackgroundForceFlushCount());
    EXPECT_EQ(window_->backgroundForceFlushCount_.load(), 1);
    EXPECT_TRUE(window_->backgroundForceFlushEnabled_.load());

    EXPECT_TRUE(window_->ConsumeBackgroundForceFlushCount());
    EXPECT_EQ(window_->backgroundForceFlushCount_.load(), 0);
    EXPECT_FALSE(window_->backgroundForceFlushEnabled_.load());
    EXPECT_FALSE(window_->HasBackgroundForceFlushQuota());
    EXPECT_FALSE(window_->ConsumeBackgroundForceFlushCount());

    window_->SetBackgroundForceFlushVsync(true, 1);
    EXPECT_TRUE(window_->ConsumeBackgroundForceFlushCount());
    EXPECT_EQ(window_->backgroundForceFlushCount_.load(), 0);
    EXPECT_FALSE(window_->backgroundForceFlushEnabled_.load());
    EXPECT_FALSE(window_->HasBackgroundForceFlushQuota());

    window_->SetBackgroundForceFlushVsync(true, 3);
    EXPECT_TRUE(window_->HasBackgroundForceFlushQuota());
    EXPECT_EQ(window_->backgroundForceFlushCount_.load(), 3);
}
