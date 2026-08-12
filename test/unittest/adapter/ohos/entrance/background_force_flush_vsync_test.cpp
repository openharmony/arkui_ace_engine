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

#include <climits>
#include <thread>
#include <vector>

#include "gtest/gtest.h"
#define private public
#define protected public

#include "core/components_ng/render/adapter/rosen_window.h"
#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "wm/window.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
class BackgroundForceFlushVsyncTest : public testing::Test {
public:
    void SetUp() override
    {
        sptr<Rosen::WindowOption> option = new Rosen::WindowOption();
        option->SetWindowType(Rosen::WindowType::WINDOW_TYPE_TRANSPARENT_VIEW);
        rsWindow_ = Rosen::Window::Create("background_force_flush_vsync_test", option);
        ASSERT_NE(rsWindow_, nullptr);
        taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>(true);
        window_ = std::make_shared<RosenWindow>(rsWindow_, taskExecutor_, 0);
    }

    void TearDown() override
    {
        window_.reset();
        if (rsWindow_) {
            EXPECT_EQ(rsWindow_->Destroy(), Rosen::WMError::WM_OK);
            rsWindow_ = nullptr;
        }
    }

    sptr<Rosen::Window> rsWindow_;
    RefPtr<MockTaskExecutor> taskExecutor_;
    std::shared_ptr<RosenWindow> window_;
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

/**
 * @tc.name: RequestFrame001
 * @tc.desc: Test RosenWindow::RequestFrame with all background force-flush paths:
 *           1) hidden window consumes quota per request and stops when exhausted;
 *           2) foreground window (onShow_=true) does not consume quota;
 *           3) forceVsync_=true on hidden window does not consume quota;
 *           4) rsWindow_=null skips VSync request and does not consume quota;
 *           5) isRequestVsync_=true skips the request via CHECK_NULL_VOID.
 * @tc.type: FUNC
 */
HWTEST_F(BackgroundForceFlushVsyncTest, RequestFrame001, TestSize.Level1)
{
    // 1) Hidden window: consumes quota per request, stops when exhausted
    window_->Window::OnHide();
    window_->SetBackgroundForceFlushVsync(true, 2);

    window_->RequestFrame();
    EXPECT_TRUE(window_->GetIsRequestFrame());
    EXPECT_EQ(window_->backgroundForceFlushCount_.load(), 1);
    EXPECT_TRUE(window_->backgroundForceFlushEnabled_.load());

    window_->OnVsync(0, 0);
    EXPECT_FALSE(window_->GetIsRequestFrame());

    window_->RequestFrame();
    EXPECT_TRUE(window_->GetIsRequestFrame());
    EXPECT_EQ(window_->backgroundForceFlushCount_.load(), 0);
    EXPECT_FALSE(window_->backgroundForceFlushEnabled_.load());

    window_->OnVsync(0, 0);
    window_->RequestFrame();
    EXPECT_FALSE(window_->GetIsRequestFrame());

    // 2) Foreground window: does not consume quota
    window_->Window::OnShow();
    window_->SetBackgroundForceFlushVsync(true, 3);
    EXPECT_TRUE(window_->onShow_);

    window_->RequestFrame();
    EXPECT_TRUE(window_->GetIsRequestFrame());
    EXPECT_EQ(window_->backgroundForceFlushCount_.load(), 3);
    EXPECT_TRUE(window_->backgroundForceFlushEnabled_.load());

    window_->OnVsync(0, 0);
    EXPECT_EQ(window_->backgroundForceFlushCount_.load(), 3);

    // 3) forceVsync_=true on hidden window: does not consume quota
    window_->Window::OnHide();
    window_->SetBackgroundForceFlushVsync(true, 3);
    window_->forceVsync_ = true;

    window_->RequestFrame();
    EXPECT_TRUE(window_->GetIsRequestFrame());
    EXPECT_EQ(window_->backgroundForceFlushCount_.load(), 3);
    EXPECT_TRUE(window_->backgroundForceFlushEnabled_.load());
    EXPECT_FALSE(window_->forceVsync_);

    window_->OnVsync(0, 0);

    // 4) rsWindow_=null: skips VSync request, does not consume quota
    window_->SetBackgroundForceFlushVsync(true, 3);
    window_->rsWindow_ = nullptr;

    window_->RequestFrame();
    EXPECT_FALSE(window_->GetIsRequestFrame());
    EXPECT_EQ(window_->backgroundForceFlushCount_.load(), 3);
    EXPECT_TRUE(window_->backgroundForceFlushEnabled_.load());

    window_->rsWindow_ = rsWindow_;

    // 5) isRequestVsync_=true: skips request via CHECK_NULL_VOID
    window_->Window::OnShow();
    window_->SetBackgroundForceFlushVsync(true, 3);
    window_->isRequestVsync_ = true;

    window_->RequestFrame();
    EXPECT_EQ(window_->backgroundForceFlushCount_.load(), 3);

    window_->isRequestVsync_ = false;
}

/**
 * @tc.name: SetBackgroundForceFlushVsyncCountMax
 * @tc.desc: Test SetBackgroundForceFlushVsync with SIZE_MAX count is clamped to 10.
 * @tc.type: FUNC
 */
HWTEST_F(BackgroundForceFlushVsyncTest, SetBackgroundForceFlushVsyncCountMax, TestSize.Level1)
{
    window_->SetBackgroundForceFlushVsync(true, SIZE_MAX);
    EXPECT_TRUE(window_->backgroundForceFlushEnabled_.load());
    EXPECT_EQ(window_->backgroundForceFlushCount_.load(), 10);
}

/**
 * @tc.name: ForegroundSetBackgroundForceFlushVsync
 * @tc.desc: Test SetBackgroundForceFlushVsync called on foreground window takes effect,
 *           and RequestFrame on foreground does not consume quota; after switching to
 *           background, quota is consumed normally.
 * @tc.type: FUNC
 */
HWTEST_F(BackgroundForceFlushVsyncTest, ForegroundSetBackgroundForceFlushVsync, TestSize.Level1)
{
    window_->SetBackgroundForceFlushVsync(true, 5);
    EXPECT_TRUE(window_->backgroundForceFlushEnabled_.load());
    EXPECT_EQ(window_->backgroundForceFlushCount_.load(), 5);
    EXPECT_TRUE(window_->onShow_);

    window_->RequestFrame();
    EXPECT_EQ(window_->backgroundForceFlushCount_.load(), 5);
    window_->OnVsync(0, 0);

    window_->Window::OnHide();
    EXPECT_TRUE(window_->backgroundForceFlushEnabled_.load());
    EXPECT_EQ(window_->backgroundForceFlushCount_.load(), 5);
    window_->RequestFrame();
    EXPECT_EQ(window_->backgroundForceFlushCount_.load(), 4);
}

/**
 * @tc.name: OnShowOnHideFastSwitch
 * @tc.desc: Test rapid foreground/background switching: OnShow always resets,
 *           OnHide preserves state, and re-enable after switch works correctly.
 * @tc.type: FUNC
 */
HWTEST_F(BackgroundForceFlushVsyncTest, OnShowOnHideFastSwitch, TestSize.Level1)
{
    window_->Window::OnHide();
    window_->SetBackgroundForceFlushVsync(true, 5);
    EXPECT_EQ(window_->backgroundForceFlushCount_.load(), 5);

    window_->Window::OnShow();
    EXPECT_FALSE(window_->backgroundForceFlushEnabled_.load());
    EXPECT_EQ(window_->backgroundForceFlushCount_.load(), 0);

    window_->Window::OnHide();
    window_->SetBackgroundForceFlushVsync(true, 3);
    EXPECT_EQ(window_->backgroundForceFlushCount_.load(), 3);

    window_->Window::OnShow();
    EXPECT_FALSE(window_->backgroundForceFlushEnabled_.load());
    EXPECT_EQ(window_->backgroundForceFlushCount_.load(), 0);

    window_->Window::OnHide();
    window_->SetBackgroundForceFlushVsync(true, 2);
    window_->RequestFrame();
    EXPECT_EQ(window_->backgroundForceFlushCount_.load(), 1);
}

/**
 * @tc.name: OnShowResetThenReenableOnHide
 * @tc.desc: Test OnShow resets consumed quota, then re-enable on hide with new count
 *           and verify full consumption to auto-disable.
 * @tc.type: FUNC
 */
HWTEST_F(BackgroundForceFlushVsyncTest, OnShowResetThenReenableOnHide, TestSize.Level1)
{
    window_->Window::OnHide();
    window_->SetBackgroundForceFlushVsync(true, 5);
    window_->ConsumeBackgroundForceFlushCount();
    window_->ConsumeBackgroundForceFlushCount();
    EXPECT_EQ(window_->backgroundForceFlushCount_.load(), 3);

    window_->Window::OnShow();
    EXPECT_EQ(window_->backgroundForceFlushCount_.load(), 0);
    EXPECT_FALSE(window_->backgroundForceFlushEnabled_.load());

    window_->Window::OnHide();
    window_->SetBackgroundForceFlushVsync(true, 2);
    EXPECT_EQ(window_->backgroundForceFlushCount_.load(), 2);

    EXPECT_TRUE(window_->ConsumeBackgroundForceFlushCount());
    EXPECT_EQ(window_->backgroundForceFlushCount_.load(), 1);
    EXPECT_TRUE(window_->ConsumeBackgroundForceFlushCount());
    EXPECT_EQ(window_->backgroundForceFlushCount_.load(), 0);
    EXPECT_FALSE(window_->backgroundForceFlushEnabled_.load());
}

/**
 * @tc.name: ConsumeBackgroundForceFlushCountConcurrent
 * @tc.desc: Test concurrent ConsumeBackgroundForceFlushCount: total successful
 *           consumes equals initial count, no over-consumption.
 * @tc.type: FUNC
 */
HWTEST_F(BackgroundForceFlushVsyncTest, ConsumeBackgroundForceFlushCountConcurrent, TestSize.Level1)
{
    window_->SetBackgroundForceFlushVsync(true, 5);
    constexpr int threadCount = 8;
    std::atomic<int> successCount{0};
    std::vector<std::thread> threads;
    for (int i = 0; i < threadCount; i++) {
        threads.emplace_back([&]() {
            if (window_->ConsumeBackgroundForceFlushCount()) {
                successCount.fetch_add(1);
            }
        });
    }
    for (auto& t : threads) {
        t.join();
    }
    EXPECT_EQ(successCount.load(), 5);
    EXPECT_EQ(window_->backgroundForceFlushCount_.load(), 0);
    EXPECT_FALSE(window_->backgroundForceFlushEnabled_.load());
}

/**
 * @tc.name: DisableCountParameterIgnored
 * @tc.desc: Test when enable=false, the count parameter is ignored and count is set to 0.
 * @tc.type: FUNC
 */
HWTEST_F(BackgroundForceFlushVsyncTest, DisableCountParameterIgnored, TestSize.Level1)
{
    window_->SetBackgroundForceFlushVsync(true, 5);
    EXPECT_EQ(window_->backgroundForceFlushCount_.load(), 5);

    window_->SetBackgroundForceFlushVsync(false, 100);
    EXPECT_FALSE(window_->backgroundForceFlushEnabled_.load());
    EXPECT_EQ(window_->backgroundForceFlushCount_.load(), 0);

    window_->SetBackgroundForceFlushVsync(false, 50);
    EXPECT_EQ(window_->backgroundForceFlushCount_.load(), 0);
}

/**
 * @tc.name: MultipleEnableOverwriteCount
 * @tc.desc: Test consecutive SetBackgroundForceFlushVsync(true, N) calls overwrite
 *           the count each time, including after partial consumption.
 * @tc.type: FUNC
 */
HWTEST_F(BackgroundForceFlushVsyncTest, MultipleEnableOverwriteCount, TestSize.Level1)
{
    window_->SetBackgroundForceFlushVsync(true, 5);
    EXPECT_EQ(window_->backgroundForceFlushCount_.load(), 5);

    window_->SetBackgroundForceFlushVsync(true, 3);
    EXPECT_EQ(window_->backgroundForceFlushCount_.load(), 3);

    window_->SetBackgroundForceFlushVsync(true, 10);
    EXPECT_EQ(window_->backgroundForceFlushCount_.load(), 10);

    window_->SetBackgroundForceFlushVsync(true, 1);
    EXPECT_EQ(window_->backgroundForceFlushCount_.load(), 1);

    window_->ConsumeBackgroundForceFlushCount();
    EXPECT_EQ(window_->backgroundForceFlushCount_.load(), 0);

    window_->SetBackgroundForceFlushVsync(true, 7);
    EXPECT_EQ(window_->backgroundForceFlushCount_.load(), 7);
}

/**
 * @tc.name: SameVsyncPeriodNoExtraConsume
 * @tc.desc: Test that within the same vsync period (isRequestVsync_=true), multiple
 *           RequestFrame calls do not consume extra quota.
 * @tc.type: FUNC
 */
HWTEST_F(BackgroundForceFlushVsyncTest, SameVsyncPeriodNoExtraConsume, TestSize.Level1)
{
    window_->Window::OnHide();
    window_->SetBackgroundForceFlushVsync(true, 3);

    window_->RequestFrame();
    EXPECT_EQ(window_->backgroundForceFlushCount_.load(), 2);

    window_->RequestFrame();
    EXPECT_EQ(window_->backgroundForceFlushCount_.load(), 2);

    window_->OnVsync(0, 0);

    window_->RequestFrame();
    EXPECT_EQ(window_->backgroundForceFlushCount_.load(), 1);
}
} // namespace OHOS::Ace::NG
