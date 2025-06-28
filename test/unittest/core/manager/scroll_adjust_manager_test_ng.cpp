/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include <optional>

#include "gtest/gtest.h"

#include "test/unittest/core/pattern/scrollable/mock_scrollable.h"
#include "core/components_ng/manager/scroll_adjust/scroll_adjust_manager.h"
#include "core/components_ng/pattern/scrollable/scrollable_properties.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {

class ScrollAdjustmanagerTestNg : public testing::Test {
public:
    void SetUp() override;
    void TearDown() override;

    RefPtr<ScrollAdjustmanager> scrollAdjustmanager_;
};

void ScrollAdjustmanagerTestNg::SetUp()
{
    scrollAdjustmanager_ = Referenced::MakeRefPtr<ScrollAdjustmanager>();
}

void ScrollAdjustmanagerTestNg::TearDown()
{
    scrollAdjustmanager_ = nullptr;
}

/**
 * @tc.name: ChangeScrollStateIfNeedTest
 * @tc.desc: ChangeScrollStateIfNeedTest
 * @tc.type: FUNC
 */
HWTEST_F(ScrollAdjustmanagerTestNg, ChangeScrollStateIfNeedTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. if current state is ScrollState::SCROLL, get ScrollState is need change.
     * @tc.expected: step1. current back is false.
     */
    bool testResult = true;
    bool actual = scrollAdjustmanager_->ChangeScrollStateIfNeed(ScrollState::SCROLL);
    EXPECT_EQ(actual, testResult);
    
    /**
     * @tc.steps: step2. if current state is ScrollState::FLING, get ScrollState is need change.
     * @tc.expected: step2. current back is false.
     */
    testResult = false;
    actual = scrollAdjustmanager_->ChangeScrollStateIfNeed(ScrollState::FLING);
    EXPECT_EQ(actual, testResult);

    /**
     * @tc.steps: step3. if current state is ScrollState::IDLE, get ScrollState is need change.
     * @tc.expected: step3. current back is false.
     */
    testResult = false;
    actual = scrollAdjustmanager_->ChangeScrollStateIfNeed(ScrollState::IDLE);
    EXPECT_EQ(actual, testResult);
}

/**
 * @tc.name: AdjustEndIndexTest
 * @tc.desc: AdjustEndIndexTest
 * @tc.type: FUNC
 */
HWTEST_F(ScrollAdjustmanagerTestNg, AdjustEndIndexTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. adjust endindex, get adjust result.
     * @tc.expected: step1. adjust result.
     */
    int32_t testResult = 1;
    EXPECT_EQ(scrollAdjustmanager_->AdjustEndIndex(0), testResult);
    
    /**
     * @tc.steps: step1. adjust endindex, get adjust result.
     * @tc.expected: step1. adjust result.
     */
    testResult = 3;
    EXPECT_EQ(scrollAdjustmanager_->AdjustEndIndex(2), testResult);

    /**
     * @tc.steps: step1. adjust endindex, get adjust result.
     * @tc.expected: step1. adjust result.
     */
    testResult = 0;
    EXPECT_EQ(scrollAdjustmanager_->AdjustEndIndex(-1), testResult);
}

/**
 * @tc.name: AdjustCachedCountTest
 * @tc.desc: AdjustCachedCountTest
 * @tc.type: FUNC
 */
HWTEST_F(ScrollAdjustmanagerTestNg, AdjustCachedCountTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. adjust cachecount, get adjust result.
     * @tc.expected: step1. adjust result.
     */
    int32_t testResult = 1;
    EXPECT_EQ(scrollAdjustmanager_->AdjustCachedCount(0), testResult);
    
    /**
     * @tc.steps: step1. adjust cachecount, get adjust result.
     * @tc.expected: step1. adjust result.
     */
    testResult = 3;
    EXPECT_EQ(scrollAdjustmanager_->AdjustCachedCount(2), testResult);

    /**
     * @tc.steps: step1. adjust cachecount, get adjust result.
     * @tc.expected: step1. adjust result.
     */
    testResult = 0;
    EXPECT_EQ(scrollAdjustmanager_->AdjustCachedCount(-1), testResult);
}
}
