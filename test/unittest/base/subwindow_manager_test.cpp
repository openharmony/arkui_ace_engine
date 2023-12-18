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

#include "base/subwindow/subwindow_manager.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace {
    // SUB_WINDOW_MANAGER = 
} // namespace

class SubwindowManagerTest : public testing::Test {
public:
    void SetUp() override {};
    void TearDown() override {};
};

/**
 * @tc.name: SubwindowManagerTest_ShowPreviewNG001
 * @tc.desc: Test frame node method ShowPreviewNG
 * @tc.type: FUNC
 */
HWTEST_F(SubwindowManagerTest, ShowPreviewNG001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get subwindowManager.
     */
    auto manager = SubwindowManager::GetInstance();
    ASSERT_NE(manager, nullptr);

    /**
     * @tc.steps: step2. 
     * @tc.expected: expect ShowPreviewNG return result which is not nullptr.
     */
    EXPECT_NE(manager->ShowPreviewNG(), nullptr);
}

/**
 * @tc.name: SubwindowManagerTest_HidePreviewNG001
 * @tc.desc: Test frame node method HidePreviewNG
 * @tc.type: FUNC
 */
HWTEST_F(SubwindowManagerTest, HidePreviewNG001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get subwindowManager, and initialize parameters.
     */
    auto manager = SubwindowManager::GetInstance();
    ASSERT_NE(manager, nullptr);
    auto subwindow = manager->ShowPreviewNG();
    ASSERT_NE(subwindow, nullptr);
    manager->SetCurrentSubwindow(subwindow);
    ASSERT_NE(manager->GetCurrentWindow(), nullptr);

    /**
     * @tc.steps: step2. call HidePreviewNG.
     * @tc.expected: expect HidePreviewNG run ok, and current window is not nullptr.
     */
    manager->HidePreviewNG();
    EXPECT_NE(manager->GetCurrentWindow(), nullptr);
}
}