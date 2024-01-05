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

#include "gtest/gtest.h"

#include "core/components_ng/manager/display_sync/ui_display_sync.h"
#include "core/components_ng/manager/display_sync/ui_display_sync_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {

class DisplaySyncManagerTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void DisplaySyncManagerTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
}

void DisplaySyncManagerTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: DisplaySyncManagerTest001
 * @tc.desc: DisplaySyncManager adds and deletes a DisplaySync.
 * @tc.type: FUNC
 */
HWTEST_F(DisplaySyncManagerTestNg, DisplaySyncManagerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get DisplaySyncManager from PipelineContext.
     * @tc.expected: step1. Check the number of DisplaySync initially managed by the DisplaySyncManager is 0.
     */
    auto pipeline = PipelineContext::GetCurrentContext();
    auto displaySyncManager = pipeline->GetOrCreateUIDisplaySyncManager();

    int32_t initSize = 0;
    EXPECT_EQ(initSize, displaySyncManager->GetUIDisplaySyncMap().size());

    /**
     * @tc.steps: step2. Construct DisplaySync and set the callback function and expected frame rate.
     */
    RefPtr<UIDisplaySync> displaySync = AceType::MakeRefPtr<UIDisplaySync>();
    displaySync->RegisterOnFrame([] () {});
    displaySync->SetExpectedFrameRateRange({0, 120, 60});

    /**
     * @tc.steps: step3. Add a DisplaySync to DisplaySyncManager for management.
     */
    displaySync->AddToPipelineOnContainer();

    /**
     * @tc.steps: step4. Check whether DisplaySync is added to the DisplaySyncManager and whether the
     *                   number of DisplaySync to be managed is correct.
     */
    int32_t capacity1 = displaySyncManager->GetUIDisplaySyncMap().size();
    EXPECT_EQ(initSize + 1, capacity1);

    bool isExisted1 = displaySyncManager->HasDisplaySync(displaySync);
    EXPECT_TRUE(isExisted1);

    /**
     * @tc.steps: step5. Remove DisplaySync from DisplaySyncManager.
     */
    displaySync->DelFromPipelineOnContainer();

    /**
     * @tc.steps: step6. Check whether DisplaySync is added to the DisplaySyncManager and whether the
     *                   number of DisplaySync to be managed is correct.
     */
    int32_t capacity2 = displaySyncManager->GetUIDisplaySyncMap().size();
    EXPECT_EQ(initSize, capacity2);

    bool isExisted2 = displaySyncManager->HasDisplaySync(displaySync);
    EXPECT_FALSE(isExisted2);
}

/**
 * @tc.name: DisplaySyncManagerTest002
 * @tc.desc: DisplaySyncManager adds and deletes multiple DisplaySync.
 * @tc.type: FUNC
 */
HWTEST_F(DisplaySyncManagerTestNg, DisplaySyncManagerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get DisplaySyncManager from PipelineContext.
     * @tc.expected: step1. Check the number of DisplaySync initially managed by the DisplaySyncManager is 0.
     */
    auto pipeline = PipelineContext::GetCurrentContext();
    auto displaySyncManager = pipeline->GetOrCreateUIDisplaySyncManager();

    int32_t initSize = 0;
    EXPECT_EQ(initSize, displaySyncManager->GetUIDisplaySyncMap().size());

    /**
     * @tc.steps: step2. Construct three DisplaySync and set the callback function and expected frame rate.
     */
    RefPtr<UIDisplaySync> displaySync1 = AceType::MakeRefPtr<UIDisplaySync>();
    displaySync1->RegisterOnFrame([] () {});
    displaySync1->SetExpectedFrameRateRange({0, 120, 60});

    RefPtr<UIDisplaySync> displaySync2 = AceType::MakeRefPtr<UIDisplaySync>();
    displaySync2->RegisterOnFrame([] () {});
    displaySync2->SetExpectedFrameRateRange({0, 120, 60});

    RefPtr<UIDisplaySync> displaySync3 = AceType::MakeRefPtr<UIDisplaySync>();
    displaySync3->RegisterOnFrame([] () {});
    displaySync3->SetExpectedFrameRateRange({0, 120, 60});

    /**
     * @tc.steps: step3. Add a DisplaySync to DisplaySyncManager for management.
     */
    displaySync1->AddToPipelineOnContainer();
    displaySync2->AddToPipelineOnContainer();
    displaySync3->AddToPipelineOnContainer();

    /**
     * @tc.steps: step4. Check whether DisplaySync is added to the DisplaySyncManager and whether the
     *                   number of DisplaySync to be managed is correct.
     */
    int32_t capacity1 = displaySyncManager->GetUIDisplaySyncMap().size();
    EXPECT_EQ(initSize + 3, capacity1);

    bool isExisted1 = displaySyncManager->HasDisplaySync(displaySync1);
    EXPECT_TRUE(isExisted1);

    bool isExisted2 = displaySyncManager->HasDisplaySync(displaySync2);
    EXPECT_TRUE(isExisted2);

    bool isExisted3 = displaySyncManager->HasDisplaySync(displaySync3);
    EXPECT_TRUE(isExisted3);

    /**
     * @tc.steps: step5. Remove a DisplaySync from DisplaySyncManager.
     */
    displaySync2->DelFromPipelineOnContainer();

    /**
     * @tc.steps: step6. Check whether DisplaySync is added to the DisplaySyncManager and whether the
     *                   number of DisplaySync to be managed is correct.
     */
    int32_t capacity2 = displaySyncManager->GetUIDisplaySyncMap().size();
    EXPECT_EQ(initSize + 2, capacity2);

    bool isExisted4 = displaySyncManager->HasDisplaySync(displaySync2);
    EXPECT_FALSE(isExisted4);

        /**
     * @tc.steps: step7. Remove two DisplaySync from DisplaySyncManager.
     */
    displaySync1->DelFromPipelineOnContainer();
    displaySync3->DelFromPipelineOnContainer();

    /**
     * @tc.steps: step8. Check whether DisplaySync is added to the DisplaySyncManager and whether the
     *                   number of DisplaySync to be managed is correct.
     */
    int32_t capacity3 = displaySyncManager->GetUIDisplaySyncMap().size();
    EXPECT_EQ(initSize, capacity3);

    bool isExisted5 = displaySyncManager->HasDisplaySync(displaySync1);
    EXPECT_FALSE(isExisted5);

    bool isExisted6 = displaySyncManager->HasDisplaySync(displaySync3);
    EXPECT_FALSE(isExisted6);
}

/**
 * @tc.name: DisplaySyncManagerTest003
 * @tc.desc: DisplaySync call callback function.
 * @tc.type: FUNC
 */
HWTEST_F(DisplaySyncManagerTestNg, DisplaySyncManagerTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get DisplaySyncManager from PipelineContext.
     * @tc.expected: step1. Check the number of DisplaySync initially managed by the DisplaySyncManager is 0.
     */
    auto pipeline = PipelineContext::GetCurrentContext();
    auto displaySyncManager = pipeline->GetOrCreateUIDisplaySyncManager();

    int32_t initSize = 0;
    EXPECT_EQ(initSize, displaySyncManager->GetUIDisplaySyncMap().size());

    /**
     * @tc.steps: step2. Construct DisplaySync and set the callback function and expected frame rate.
     */
    int32_t count = 0;
    int32_t countCopy = count;
    RefPtr<UIDisplaySync> displaySync = AceType::MakeRefPtr<UIDisplaySync>();
    displaySync->RegisterOnFrame([&count] () {
        count++;
    });
    displaySync->SetExpectedFrameRateRange({0, 120, 60});

    displaySync->AddToPipelineOnContainer();

    /**
     * @tc.steps: step3. DisplaySync call the callback function.
     */
    int32_t onFrameTimes = 5;

    for (int32_t i = 0; i < onFrameTimes; ++i) {
        displaySync->OnFrame();
    }

    /**
     * @tc.steps: step4. Check the count value and remove DisplaySync from DisplaySyncManager.
     * @tc.expected: step4. Check whether the computed count involved in the callback function is correct.
     */
    EXPECT_EQ(countCopy + onFrameTimes, count);
    displaySync->DelFromPipelineOnContainer();
}

/**
 * @tc.name: DisplaySyncManagerTest004
 * @tc.desc: DisplaySyncManager sets the frame rate of the pipeline.
 * @tc.type: FUNC
 */
HWTEST_F(DisplaySyncManagerTestNg, DisplaySyncManagerTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get DisplaySyncManager from PipelineContext.
     * @tc.expected: step1. Check the number of DisplaySync initially managed by the DisplaySyncManager is 0.
     */
    auto pipeline = PipelineContext::GetCurrentContext();
    auto displaySyncManager = pipeline->GetOrCreateUIDisplaySyncManager();

    int32_t initSize = 0;
    EXPECT_EQ(initSize, displaySyncManager->GetUIDisplaySyncMap().size());

    /**
     * @tc.steps: step2. Set the valid frame rate (A) of the DisplaySyncManager currently applied.
     * @tc.expected: step2. The current frame rate should be equal to frame rate (A).
     */
    int32_t vsyncRate1 = 72;
    displaySyncManager->SetVsyncRate(vsyncRate1);
    EXPECT_EQ(vsyncRate1, displaySyncManager->GetVsyncRate());

    /**
     * @tc.steps: step3. Set the valid frame rate (B) of the DisplaySyncManager currently applied.
     * @tc.expected: step3. The current frame rate should be equal to frame rate (B).
     */
    int32_t vsyncRate2 = 120;
    displaySyncManager->SetVsyncRate(vsyncRate2);
    EXPECT_EQ(vsyncRate2, displaySyncManager->GetVsyncRate());

    /**
     * @tc.steps: step4. Set the invalid frame rate (C) of the DisplaySyncManager currently applied.
     * @tc.expected: step4. The current frame rate should be equal to frame rate (B).
     */
    int32_t vsyncRate3 = -10;
    displaySyncManager->SetVsyncRate(vsyncRate3);
    EXPECT_EQ(vsyncRate2, displaySyncManager->GetVsyncRate());
}

/**
 * @tc.name: DisplaySyncManagerTest005
 * @tc.desc: DisplaySyncManager sets the vsync period of the pipeline.
 * @tc.type: FUNC
 */
HWTEST_F(DisplaySyncManagerTestNg, DisplaySyncManagerTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get DisplaySyncManager from PipelineContext.
     * @tc.expected: step1. Check the number of DisplaySync initially managed by the DisplaySyncManager is 0.
     */
    auto pipeline = PipelineContext::GetCurrentContext();
    auto displaySyncManager = pipeline->GetOrCreateUIDisplaySyncManager();

    int32_t initSize = 0;
    EXPECT_EQ(initSize, displaySyncManager->GetUIDisplaySyncMap().size());

    /**
     * @tc.steps: step2. Set the valid vsync period (A) of the DisplaySyncManager currently applied.
     * @tc.expected: step2. The vsync period should be equal to vsync period (A).
     */
    int64_t vsyncPeriod1 = 16666667;
    displaySyncManager->SetVsyncPeriod(vsyncPeriod1);
    EXPECT_EQ(vsyncPeriod1, displaySyncManager->GetVsyncPeriod());

    /**
     * @tc.steps: step3. Set the valid vsync period (B) of the DisplaySyncManager currently applied.
     * @tc.expected: step3. The vsync period should be equal to vsync period (B).
     */
    int64_t vsyncPeriod2 = 16666677;
    displaySyncManager->SetVsyncPeriod(vsyncPeriod2);
    EXPECT_EQ(vsyncPeriod2, displaySyncManager->GetVsyncPeriod());

    /**
     * @tc.steps: step4. Set the invalid vsync period (C) of the DisplaySyncManager currently applied.
     * @tc.expected: step4. The vsync period should be equal to vsync period (C).
     */
    int64_t vsyncPeriod3 = -10;
    displaySyncManager->SetVsyncPeriod(vsyncPeriod3);
    EXPECT_EQ(vsyncPeriod2, displaySyncManager->GetVsyncPeriod());
}

/**
 * @tc.name: DisplaySyncManagerTest006
 * @tc.desc: DisplaySyncManager sets the refresh rate mode of the pipeline.
 * @tc.type: FUNC
 */
HWTEST_F(DisplaySyncManagerTestNg, DisplaySyncManagerTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get DisplaySyncManager from PipelineContext.
     * @tc.expected: step1. Check the number of DisplaySync initially managed by the DisplaySyncManager is 0.
     */
    auto pipeline = PipelineContext::GetCurrentContext();
    auto displaySyncManager = pipeline->GetOrCreateUIDisplaySyncManager();

    int32_t initSize = 0;
    EXPECT_EQ(initSize, displaySyncManager->GetUIDisplaySyncMap().size());

    /**
     * @tc.steps: step2. Set the valid refresh rate mode (B) of the DisplaySyncManager currently applied.
     * @tc.expected: step2. The refresh rate mode should be equal to refresh rate mode (A).
     */
    int32_t refreshRateMode1 = 1;
    displaySyncManager->SetRefreshRateMode(refreshRateMode1);
    EXPECT_EQ(refreshRateMode1, displaySyncManager->GetRefreshRateMode());

    /**
     * @tc.steps: step3. Set the valid refresh rate mode (B) of the DisplaySyncManager currently applied.
     * @tc.expected: step3. The refresh rate mode should be equal to refresh rate mode (B).
     */
    int32_t refreshRateMode2 = -1;
    displaySyncManager->SetRefreshRateMode(refreshRateMode2);
    EXPECT_EQ(refreshRateMode2, displaySyncManager->GetRefreshRateMode());

    /**
     * @tc.steps: step4. Set the invalid refresh rate mode (C) of the DisplaySyncManager currently applied.
     * @tc.expected: step4. The refresh rate mode should be equal to refresh rate mode (B).
     */
    int32_t refreshRateMode3 = -10;
    displaySyncManager->SetRefreshRateMode(refreshRateMode3);
    EXPECT_EQ(refreshRateMode2, displaySyncManager->GetRefreshRateMode());
}

/**
 * @tc.name: DisplaySyncManagerTest007
 * @tc.desc: DisplaySyncManager determines the DisplaySync frame rate on the UI, excluding invalid frame rate.
 * @tc.type: FUNC
 */
HWTEST_F(DisplaySyncManagerTestNg, DisplaySyncManagerTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get DisplaySyncManager from PipelineContext.
     * @tc.expected: step1. Check the number of DisplaySync initially managed by the DisplaySyncManager is 0.
     */
    auto pipeline = PipelineContext::GetCurrentContext();
    auto displaySyncManager = pipeline->GetOrCreateUIDisplaySyncManager();
    int32_t initSize = 0;
    EXPECT_EQ(initSize, displaySyncManager->GetUIDisplaySyncMap().size());

    /**
     * @tc.steps: step2. Construct DisplaySync and set the callback function and different expected frame rate.
     */
    uint64_t nanoTimestamp = 0;
    RefPtr<UIDisplaySync> displaySync1 = AceType::MakeRefPtr<UIDisplaySync>();
    displaySync1->SetExpectedFrameRateRange({0, 120, 30});
    displaySync1->AddToPipelineOnContainer();

    RefPtr<UIDisplaySync> displaySync2 = AceType::MakeRefPtr<UIDisplaySync>();
    displaySync2->SetExpectedFrameRateRange({0, 120, 60});
    displaySync2->AddToPipelineOnContainer();

    /**
     * @tc.steps: step3. DisplaySyncManager do distribution and decision operations.
     */
    displaySyncManager->DispatchFunc(nanoTimestamp);
    int32_t displaySyncRate1 = displaySyncManager->GetDisplaySyncRate();
    EXPECT_EQ(60, displaySyncRate1);

    displaySync2->DelFromPipelineOnContainer();
    displaySyncManager->DispatchFunc(nanoTimestamp);
    int32_t displaySyncRate2 = displaySyncManager->GetDisplaySyncRate();

    /**
     * @tc.steps: step4. Check the decision frame rate in DisplaySyncManager.
     * @tc.expected: step4. The decision frame rate should be equal to the maximum valid frame rate.
     */
    EXPECT_EQ(30, displaySyncRate2);

    displaySync1->DelFromPipelineOnContainer();
    displaySyncManager->DispatchFunc(nanoTimestamp);
    int32_t displaySyncRate3 = displaySyncManager->GetDisplaySyncRate();

    EXPECT_EQ(0, displaySyncRate3);
}

/**
 * @tc.name: DisplaySyncManagerTest008
 * @tc.desc: DisplaySyncManager determines the DisplaySync frame rate on the UI, including invalid frame rate.
 * @tc.type: FUNC
 */
HWTEST_F(DisplaySyncManagerTestNg, DisplaySyncManagerTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get DisplaySyncManager from PipelineContext.
     * @tc.expected: step1. Check the number of DisplaySync initially managed by the DisplaySyncManager is 0.
     */
    auto pipeline = PipelineContext::GetCurrentContext();
    auto displaySyncManager = pipeline->GetOrCreateUIDisplaySyncManager();
    int32_t initSize = 0;
    EXPECT_EQ(initSize, displaySyncManager->GetUIDisplaySyncMap().size());

    /**
     * @tc.steps: step2. Construct DisplaySync and set the callback function and different expected frame rate.
     */
    uint64_t nanoTimestamp = 0;
    RefPtr<UIDisplaySync> displaySync1 = AceType::MakeRefPtr<UIDisplaySync>();
    displaySync1->SetExpectedFrameRateRange({0, 10, 30});
    displaySync1->AddToPipelineOnContainer();

    RefPtr<UIDisplaySync> displaySync2 = AceType::MakeRefPtr<UIDisplaySync>();
    displaySync2->SetExpectedFrameRateRange({0, 120, 60});
    displaySync2->AddToPipelineOnContainer();

    /**
     * @tc.steps: step3. DisplaySyncManager do distribution and decision operations.
     */
    displaySyncManager->DispatchFunc(nanoTimestamp);
    int32_t displaySyncRate1 = displaySyncManager->GetDisplaySyncRate();
    EXPECT_EQ(60, displaySyncRate1);

    displaySync2->DelFromPipelineOnContainer();
    displaySyncManager->DispatchFunc(nanoTimestamp);
    int32_t displaySyncRate2 = displaySyncManager->GetDisplaySyncRate();

    /**
     * @tc.steps: step4. Check the decision frame rate in DisplaySyncManager.
     * @tc.expected: step4. The decision frame rate should be equal to the maximum valid frame rate.
     */
    EXPECT_EQ(0, displaySyncRate2);

    displaySync1->DelFromPipelineOnContainer();
    displaySyncManager->DispatchFunc(nanoTimestamp);
    int32_t displaySyncRate3 = displaySyncManager->GetDisplaySyncRate();

    EXPECT_EQ(0, displaySyncRate3);
}
} // namespace OHOS::Ace::NG
